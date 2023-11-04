#include <stm32h5xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include <type_traits>

#include "util.h"
#include "spi.h"

#include <lvgl.h>

#define kLcdResetPort GPIOC
#define kLcdResetPin GPIO_PIN_7

#define kLcdDataCommandPort GPIOA
#define kLcdDataCommandPin GPIO_PIN_8

enum class Mode
{
    Data,
    Command
};

union pixel
{
    pixel(uint8_t r, uint8_t g, uint8_t b)
    : color{r, g, b} {}
    struct __attribute__((packed))
    {
        uint8_t r:5;
        uint8_t b:6;
        uint8_t g:5;
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
    chipselect_low(SpiDevice::Display);
    mode(Mode::Command);
    spi_write(bytes{0, cmd});
    chipselect_high(SpiDevice::Display);
}

template<size_t N>
static std::enable_if<(N > 0)>::type send(uint8_t cmd, bytes<N> d)
{
    send(cmd);
    mode(Mode::Data);
    for (const auto byte : d)
    {
        chipselect_low(SpiDevice::Display);
        spi_write(bytes{0, byte});
        chipselect_high(SpiDevice::Display);
    }
}

static void select(uint16_t ystart, uint16_t xstart, uint16_t yend, uint16_t xend)
{
    send(0x2a, bytes{(uint8_t)(xstart >> 8), (uint8_t)(xstart & 0xFF), (uint8_t)(xend >> 8), (uint8_t)(xend & 0xFF)});
    send(0x2b, bytes{(uint8_t)(ystart >> 8), (uint8_t)(ystart & 0xFF), (uint8_t)(yend >> 8), (uint8_t)(yend & 0xFF)});
}

uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

static void fill(const pixel p)
{
    send(0x2c);
    mode(Mode::Data);
    chipselect_low(SpiDevice::Display);
    for (auto i = 0; i < kWidth * kHeight; ++i)
    {
        spi_write(color565(0x0, 0x0, 0xff));
    }
    chipselect_high(SpiDevice::Display);
}

void flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    int32_t x, y;

    // taskENTER_CRITICAL();
    select(area->y1, area->x1, area->y2, area->x2);
    send(0x2c);
    mode(Mode::Data);
    chipselect_low(SpiDevice::Display);
    pixel p{0, 0, 0};
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            p.color.r = color_p->ch.red;
            p.color.g = color_p->ch.green;
            p.color.b = color_p->ch.blue;
            // spi_write(color_p->full);
            spi_write(p.value);
            color_p++;
        }
    }
    chipselect_high(SpiDevice::Display);
    lv_disp_flush_ready(disp);
    // taskEXIT_CRITICAL();
}

static void update_task(void*)
{
    message("start update task");
    for (;;)
    {
        lv_timer_handler();
        // taskYIELD();
        vTaskDelay(1);
    }
}

#include <cstdio>

void lcd_init()
{
    init_pins();
    reset();

    send(0xc0, bytes{0x19, 0x1a});
    send(0xc1, bytes{0x45, 0x00});
    send(0xc2, bytes{0x44});
    send(0xc5, bytes{0x00, 0x28});
    send(0xb1, bytes{0xd0, 0x11});
    send(0xb4, bytes{0x02});

    send(0xb7, bytes{0x07});
    send(0xe0, bytes{0x1f, 0x25, 0x22, 0x0b, 0x06, 0x0a, 0x4e, 0xc6, 0x39, 0, 0, 0, 0, 0, 0});
    send(0xe1, bytes{0x1f, 0x3F, 0x3F, 0x0F, 0x1F, 0x0F, 0x46, 0x49, 0x31, 0x05, 0x09, 0x03, 0x1C, 0x1A, 0x00});

    send(0x3a, bytes{0x05});

    send(0xB6, bytes{0x00, 0x02, 0xff});
    send(0x36, bytes{(1 << 5) | (1 << 4)});

    send(0x11);
    vTaskDelay(120);
    send(0x29);

    backlight(true);
    
#if 1
    message("start init");
    lv_init();

    static lv_disp_draw_buf_t draw_buf;
    lv_color_t *buf1 = new lv_color_t[kWidth * 2];
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, kWidth * 2);

    message("buf init ok");

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    message("drv init ok");

    disp_drv.flush_cb = flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = kWidth;
    disp_drv.ver_res = kHeight;
    auto *disp = lv_disp_drv_register(&disp_drv);

    disp->theme = lv_theme_basic_init(disp);

    message("init done");

    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label, 10, 10);                            /*Set its position*/
    lv_obj_set_size(label, 120, 50);                          /*Set its size*/

    // lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    // lv_label_set_text(label, "Button");                     /*Set the labels text*/
    // lv_obj_center(label);

    // lv_obj_t * bar = lv_bar_create(lv_scr_act());
    // lv_obj_set_pos(bar, 240, 160);
    // lv_obj_set_size(bar, 120, 50); 
    // lv_bar_set_range(bar, 0, 100);
    // lv_bar_set_start_value(bar, 0, LV_ANIM_OFF);
    // lv_bar_set_mode(bar, LV_BAR_MODE_RANGE);

    // auto *led = lv_led_create(lv_scr_act());
    // lv_obj_center(led);

    auto *meter = lv_meter_create(lv_scr_act());
    lv_obj_center(meter);
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);
    
    lv_meter_indicator_t * indic;

    /*Add a blue arc to the start*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    /*Make the tick lines blue at the start of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE),
                                     false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    /*Add a red arc to the end*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    /*Make the tick lines red at the end of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false,
                                     0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

    xTaskCreate(update_task, "update_task", 512, NULL, tskIDLE_PRIORITY + 1, NULL);

    static char buf[64];
    int v = 0;
    bool d = false;
    for(;;)
    {
        message("%d", v);
        lv_meter_set_indicator_value(meter, indic, v);
        // lv_bar_set_value(bar, p, LV_ANIM_OFF);
        // lv_led_set_brightness(led, p);
        // lv_led_toggle(led);
        // sprintf(buf, "value: %d", p);
        // lv_label_set_text(label, buf);
        // lv_label_set_text_static(label, buf);
        lv_label_set_text_fmt(label, "value: %d", v);
        // taskYIELD();
        d ? --v : ++v;
        if (v == 100)
            d = true;
        if (v == 0)
            d = false;
        vTaskDelay(1);
        // lv_label_set_text(label, "Down");
    }

    // for (;;)
    // 
        // message("60");
        // lv_bar_set_value(bar, 60, LV_ANIM_OFF);
        // lv_timer_handler();
        // vTaskDelay(5000);
        // message("10");
        // lv_bar_set_value(bar, 10, LV_ANIM_OFF);
        // lv_timer_handler();
        // vTaskDelay(50);
        // message("%d", i % 100);
    // }

#endif

#if 0
    select(0, 0, 320, 480);

    for (;;)
    {
        message("red");
        fill(kColorRed);
        vTaskDelay(1000);
   
        // message("green");
        // fill(kColorGreen);
        // vTaskDelay(1000);

        // message("blue");
        // fill(kColorBlue);
        // vTaskDelay(1000);
    }
#endif
}