#include <stm32h5xx_hal.h>
#include <stm32h5xx_ll_spi.h>

#include "spi.h"
#include "util.h"

#define kSpiPort GPIOA

#define kSpiClkPin GPIO_PIN_5
#define kSpiMisoPin GPIO_PIN_6
#define kSpiMosiPin GPIO_PIN_7

#define kChipSelectPort GPIOB
#define kTouchChipSelectPin GPIO_PIN_5
#define kSdCardChipSelectPin GPIO_PIN_4

#define kLcdChipSelectPort GPIOC
#define kLcdChipSelectPin GPIO_PIN_9

SPI_HandleTypeDef spi = 
{
    .Instance = SPI1,
    .Init = 
    {
        .Mode = SPI_MODE_MASTER,
        .DataSize = SPI_DATASIZE_8BIT,
        .NSS = SPI_NSS_SOFT,
        .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2,
    }
};

void spi_change_speed()
{
    LL_SPI_SetBaudRatePrescaler(SPI1, SPI_BAUDRATEPRESCALER_128);
}

void spi_write(const uint8_t *data, size_t size)
{
    extern SPI_HandleTypeDef spi;
    if (HAL_SPI_Transmit(&spi, data, size, kSpiTimeout) != HAL_OK)
    {
        message("spi_write %u bytes NOK!", size);
    }
}

void spi_write(uint16_t data)
{
    extern SPI_HandleTypeDef spi;

    LL_SPI_StartMasterTransfer(spi.Instance);
    while(!LL_SPI_IsActiveFlag_TXP(spi.Instance));
    LL_SPI_TransmitData16(spi.Instance, data);
    while(!LL_SPI_IsActiveFlag_TXC(spi.Instance));
}


uint8_t spi_read_byte()
{
    return spi_read<1>()[0];
}

void spi_init()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef data = 
    {
        .Pin = kSpiMosiPin | kSpiMisoPin,
        .Mode = GPIO_MODE_AF_PP,
        .Speed = GPIO_SPEED_FREQ_HIGH,
        .Alternate = GPIO_AF5_SPI1,
    };
    HAL_GPIO_Init(kSpiPort, &data);

    GPIO_InitTypeDef spiclk = 
    {
        .Pin = kSpiClkPin,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_PULLDOWN,
        .Speed = GPIO_SPEED_FREQ_HIGH,
        .Alternate = GPIO_AF5_SPI1,
    };
    HAL_GPIO_Init(kSpiPort, &spiclk);

    const RCC_PeriphCLKInitTypeDef clk = 
    {
        .PeriphClockSelection = RCC_PERIPHCLK_SPI1,
        .Spi1ClockSelection = RCC_SPI1CLKSOURCE_PLL1Q
    };
    check(HAL_RCCEx_PeriphCLKConfig(&clk), "SPI clock config");

    __HAL_RCC_SPI1_CLK_ENABLE();
    check(HAL_SPI_Init(&spi), "SPI HAL init");

    __HAL_RCC_GPIOB_CLK_ENABLE();
    chipselect_high(SpiDevice::Touch);
    chipselect_high(SpiDevice::SDcard);
    const GPIO_InitTypeDef chipselect = 
    {
        .Pin = kTouchChipSelectPin | kSdCardChipSelectPin,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = GPIO_SPEED_FREQ_HIGH,
    };
    HAL_GPIO_Init(kChipSelectPort, &chipselect);

    __HAL_RCC_GPIOC_CLK_ENABLE();
    chipselect_high(SpiDevice::Display);
    const GPIO_InitTypeDef lcd_chipselect = 
    {
        .Pin = kLcdChipSelectPin,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = GPIO_SPEED_FREQ_HIGH,
    };
    HAL_GPIO_Init(kLcdChipSelectPort, &lcd_chipselect);

    LL_SPI_Enable(spi.Instance);
}

static uint16_t chipselect_pins[] = {kLcdChipSelectPin, kTouchChipSelectPin, kSdCardChipSelectPin};

void chipselect_high(SpiDevice d)
{
    HAL_GPIO_WritePin((d == SpiDevice::Display) ? kLcdChipSelectPort : kChipSelectPort,
        chipselect_pins[static_cast<size_t>(d)], GPIO_PIN_SET);
}

void chipselect_low(SpiDevice d)
{
    HAL_GPIO_WritePin((d == SpiDevice::Display) ? kLcdChipSelectPort : kChipSelectPort,
        chipselect_pins[static_cast<size_t>(d)], GPIO_PIN_RESET);
}
