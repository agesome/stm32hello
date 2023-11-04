#include <stm32h5xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include <type_traits>

#include "util.h"
#include "spi.h"

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
        uint8_t g:6;
        uint8_t b:5;
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

static void select(uint16_t xstart, uint16_t ystart, uint16_t width, uint16_t height)
{
    const uint16_t xend = xstart + width;
    const uint16_t yend = ystart + height;

    send(0x2a, bytes{(uint8_t)(xstart >> 8), (uint8_t)(xstart & 0xFF), (uint8_t)(xend >> 8), (uint8_t)(xend & 0xFF)});
    send(0x2b, bytes{(uint8_t)(ystart >> 8), (uint8_t)(ystart & 0xFF), (uint8_t)(yend >> 8), (uint8_t)(yend & 0xFF)});
}

static void fill(const pixel p)
{
    send(0x2c);
    mode(Mode::Data);
    chipselect_low(SpiDevice::Display);
    for (auto i = 0; i < kWidth * kHeight; ++i)
    {
        spi_write(p.value);
    }
    chipselect_high(SpiDevice::Display);
}

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

    send(0x3a, bytes{0x55});
    send(0x11);
    vTaskDelay(120);
    send(0x29);

    select(100, 100, 100, 100);

    for (;;)
    {
        fill(kColorRed);
        vTaskDelay(1000);

        backlight(true);

        fill(kColorGreen);
        vTaskDelay(1000);

        fill(kColorBlue);
        vTaskDelay(1000);
    }
}