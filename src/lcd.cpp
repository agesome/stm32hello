#include <stm32h5xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include <type_traits>

#include "util.h"
#include "spi.h"

#include <lvgl.h>
#include <vector>

#define kLcdResetPort GPIOC
#define kLcdResetPin GPIO_PIN_7

#define kLcdDataCommandPort GPIOA
#define kLcdDataCommandPin GPIO_PIN_8

SemaphoreHandle_t lvgl_semaphore{};

enum class Mode
{
    Data,
    Command
};

union pixel
{
    pixel(uint8_t r, uint8_t g, uint8_t b)
    : color{b, g, r} {}
    struct __attribute__((packed))
    {
        uint8_t b:5;
        uint8_t g:6;
        uint8_t r:5;
    } color;
    uint16_t value;
};

static const pixel kColorRed  {31,    0,  0};
static const pixel kColorGreen{0,     63, 0};
static const pixel kColorBlue {0,     0,  31};
static const pixel kColorWhite{31,    63, 31};
static const pixel kColorBlack{0,     0,  0};

const auto kWidth{480};
const auto kHeight{320};

static void reset()
{
    HAL_GPIO_WritePin(kLcdResetPort, kLcdResetPin, GPIO_PIN_SET);
    vTaskDelay(5);
    HAL_GPIO_WritePin(kLcdResetPort, kLcdResetPin, GPIO_PIN_RESET);
    vTaskDelay(20);
    HAL_GPIO_WritePin(kLcdResetPort, kLcdResetPin, GPIO_PIN_SET);
    vTaskDelay(80);
}

static void mode(Mode m)
{
    HAL_GPIO_WritePin(kLcdDataCommandPort, kLcdDataCommandPin, m == Mode::Command ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void backlight(bool on)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static void init_pins()
{
    const GPIO_InitTypeDef reset = 
    {
        .Pin = kLcdResetPin,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = GPIO_SPEED_FREQ_HIGH
    };
    HAL_GPIO_Init(kLcdResetPort, &reset);

    const GPIO_InitTypeDef dc = 
    {
        .Pin = kLcdDataCommandPin,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = GPIO_SPEED_FREQ_HIGH
    };
    HAL_GPIO_Init(kLcdDataCommandPort, &dc);
 
    const GPIO_InitTypeDef bl = 
    {
        .Pin = GPIO_PIN_6,
        .Mode = GPIO_MODE_OUTPUT_PP,
    };
    HAL_GPIO_Init(GPIOC, &bl);
    backlight(false);
}

static void send(uint8_t cmd)
{
    mode(Mode::Command);
    chipselect_low(SpiDevice::Display);
    uint16_t v = cmd;
    spi_write(&v, 1);
    chipselect_high(SpiDevice::Display);
}

template<size_t N>
static std::enable_if<(N > 0)>::type send(uint8_t cmd, bytes<N> data)
{
    send(cmd);
    mode(Mode::Data);
    chipselect_low(SpiDevice::Display);
    spi_write(data);
    chipselect_high(SpiDevice::Display);
}   

static void select(uint16_t ystart, uint16_t xstart, uint16_t yend, uint16_t xend)
{
    send(0x2a, bytes{(uint8_t)(xstart >> 8), (uint8_t)(xstart & 0xFF), (uint8_t)(xend >> 8), (uint8_t)(xend & 0xFF)});
    send(0x2b, bytes{(uint8_t)(ystart >> 8), (uint8_t)(ystart & 0xFF), (uint8_t)(yend >> 8), (uint8_t)(yend & 0xFF)});
}

static void fill(pixel p)
{
    send(0x2c);
    chipselect_low(SpiDevice::Display);
    mode(Mode::Data);
    std::vector<uint16_t> line(kWidth, p.value);
    for (auto i = 0; i < kHeight; ++i)
    {
        spi_write(line.data(), line.size());
    }
    chipselect_high(SpiDevice::Display);
}

struct write_item
{
    const lv_area_t *area;
    const lv_color_t *color;
};

lv_disp_drv_t disp_drv{};

QueueHandle_t spi_queue;

static void flush_callback(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color)
{
#if 1
    write_item w {area, color};
    if (xQueueSend(spi_queue, &w, portMAX_DELAY) != pdTRUE)
    {
        message("queue send failed");
    }
#else
    select(area->y1, area->x1, area->y2, area->x2);
    send(0x2c);
    chipselect_low(SpiDevice::Display);
    mode(Mode::Data);
    const size_t count = (area->y2 - area->y1 + 1) * (area->x2 - area->x1 + 1);
    spi_write((uint16_t*)color, count);
    chipselect_high(SpiDevice::Display);
    lv_disp_flush_ready(disp);
#endif
}

static void spi_writer(void*)
{
    for(;;)
    {
        write_item w{};
        if (xQueueReceive(spi_queue, &w, portMAX_DELAY) == pdTRUE)
        {
            select(w.area->y1, w.area->x1, w.area->y2, w.area->x2);
            send(0x2c);
            chipselect_low(SpiDevice::Display);
            mode(Mode::Data);
            const size_t count = (w.area->y2 - w.area->y1 + 1) * (w.area->x2 - w.area->x1 + 1);
            spi_write((uint16_t*)w.color, count);
            chipselect_high(SpiDevice::Display);
            lv_disp_flush_ready(&disp_drv);
        }
    }
}

static void lvgl_render(void*)
{
    message("start lvgl init");
    lv_init();

    const auto bufsize = kWidth * 5;

    lv_disp_draw_buf_t draw_buf{};
    lv_disp_draw_buf_init(&draw_buf, new lv_color_t[bufsize], new lv_color_t[bufsize], bufsize);
    
    lv_disp_drv_init(&disp_drv);

    disp_drv.flush_cb = flush_callback;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = kWidth;
    disp_drv.ver_res = kHeight;

    lv_disp_drv_register(&disp_drv);

    message("lvgl init done");

    xSemaphoreTake(lvgl_semaphore, portMAX_DELAY);

    message("start update loop");
    xSemaphoreGive(lvgl_semaphore);
    for (;;)
    {
        if (xSemaphoreTake(lvgl_semaphore, 1))
        {
            auto v = lv_timer_handler();
            xSemaphoreGive(lvgl_semaphore);
            vTaskDelay((v == LV_NO_TIMER_READY) ? 1 : v);
        }
    }
}

void lcd_init()
{
    init_pins();
    reset();

    send(0xc0, bytes{0x19, 0x1a});
    send(0xc1, bytes{0x45, 0x00});
    send(0xc2, bytes{0x44});
    send(0xc5, bytes{0x00, 0x28});
    send(0xb1, bytes{0xc0, 0x10});
    send(0xb4, bytes{0x02});

    send(0xb7, bytes{0x07});
    send(0xe0, bytes{0x1f, 0x25, 0x22, 0x0b, 0x06, 0x0a, 0x4e, 0xc6, 0x39, 0, 0, 0, 0, 0, 0});
    send(0xe1, bytes{0x1f, 0x3F, 0x3F, 0x0F, 0x1F, 0x0F, 0x46, 0x49, 0x31, 0x05, 0x09, 0x03, 0x1C, 0x1A, 0x00});

    send(0x3a, bytes{0x05});

    send(0xB6, bytes{0x00, 0x02, 0xff});
    send(0x36, bytes{(1 << 5) | (1 << 3)});

    send(0x11);
    vTaskDelay(120);
    send(0x29);

    backlight(true);

    message("LCD init done");

#if 1
    lvgl_semaphore = xSemaphoreCreateBinary();
    spi_queue = xQueueCreate(8, sizeof(write_item));
    xTaskCreate(spi_writer, "spi", 256, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(lvgl_render, "render", 1024, NULL, tskIDLE_PRIORITY + 2, NULL);
#else
    select(0, 0, 320, 480);

    for (;;)
    {
        message("red");
        fill(kColorRed);
        vTaskDelay(1000);
   
        message("green");
        fill(kColorGreen);
        vTaskDelay(1000);

        message("blue");
        fill(kColorBlue);
        vTaskDelay(1000);
    }
#endif
}