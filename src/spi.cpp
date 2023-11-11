#include <stm32h5xx_hal.h>
#include <stm32h5xx_ll_rcc.h>

#include <stm32h5xx.h>

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

#define kGpioSpeed GPIO_SPEED_FREQ_VERY_HIGH

constexpr auto kSpiTimeout{5};

static SemaphoreHandle_t spi_semaphore{};

static SPI_HandleTypeDef spi = 
{
    .Instance = SPI1,
    .Init = 
    {
        .Mode = SPI_MODE_MASTER,
        .DataSize = SPI_DATASIZE_16BIT,
        .NSS = SPI_NSS_SOFT,
        .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4,
        .MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE
    },
};

static DMA_HandleTypeDef dma = 
{
    .Instance = GPDMA1_Channel0,
    .Init = 
    {
        .Request = GPDMA1_REQUEST_SPI1_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .SrcInc = DMA_SINC_INCREMENTED,
        .SrcDataWidth = DMA_SRC_DATAWIDTH_HALFWORD,
        .DestDataWidth = DMA_DEST_DATAWIDTH_HALFWORD,
        .Priority = DMA_HIGH_PRIORITY,
        .SrcBurstLength = 1,
        .DestBurstLength = 1,
        .TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0|DMA_DEST_ALLOCATED_PORT0,
    },
};

void spi_change_speed()
{
    LL_SPI_SetBaudRatePrescaler(SPI1, SPI_BAUDRATEPRESCALER_128);
}

extern "C" void SPI1_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&spi);
}

extern "C" void GPDMA1_Channel0_IRQHandler()
{
    HAL_DMA_IRQHandler(&dma);
}

extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    BaseType_t do_yield{};
    xSemaphoreGiveFromISR(spi_semaphore, &do_yield);
    portYIELD_FROM_ISR(do_yield);
}

extern "C" void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    message("SPI error; halt");
    assert_failed();
}

void spi_write(uint16_t data)
{
    if (HAL_SPI_Transmit_DMA(&spi, (uint8_t *) &data, 1) != HAL_OK)
    {
        message("spi_write uint16_t NOK");
    }
}

void spi_write(uint16_t const *data, size_t size)
{
    xSemaphoreTake(spi_semaphore, portMAX_DELAY);
    if (HAL_SPI_Transmit_DMA(&spi, (uint8_t *) data, size) != HAL_OK)
    {
        message("spi_write uint16_t NOK");
    }
    xSemaphoreTake(spi_semaphore, portMAX_DELAY);
    xSemaphoreGive(spi_semaphore);
}

void spi_write_async(uint16_t const *data, size_t size)
{
    xSemaphoreTake(spi_semaphore, portMAX_DELAY);
    if (HAL_SPI_Transmit_DMA(&spi, (uint8_t *) data, size) != HAL_OK)
    {
        message("spi_write uint16_t NOK");
    }

}

void spi_write_async_wait()
{
    xSemaphoreTake(spi_semaphore, portMAX_DELAY);
    xSemaphoreGive(spi_semaphore);
}


// uint8_t spi_read_byte()
// {
//     return spi_read<1>()[0];
// }

void spi_init()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef data = 
    {
        .Pin = kSpiMosiPin | kSpiMisoPin,
        .Mode = GPIO_MODE_AF_PP,
        .Speed = kGpioSpeed,
        .Alternate = GPIO_AF5_SPI1,
    };
    HAL_GPIO_Init(kSpiPort, &data);

    GPIO_InitTypeDef spiclk = 
    {
        .Pin = kSpiClkPin,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_PULLUP,
        .Speed = kGpioSpeed,
        .Alternate = GPIO_AF5_SPI1,
    };
    HAL_GPIO_Init(kSpiPort, &spiclk);

    __HAL_RCC_PLL1_CLKOUT_ENABLE(RCC_PLL1_DIVQ);
    LL_RCC_SetSPIClockSource(LL_RCC_SPI1_CLKSOURCE_PLL1Q);
    __HAL_RCC_SPI1_CLK_ENABLE();
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
    check(HAL_SPI_Init(&spi), "SPI HAL init");

    __HAL_RCC_GPIOB_CLK_ENABLE();
    chipselect_high(SpiDevice::Touch);
    chipselect_high(SpiDevice::SDcard);
    const GPIO_InitTypeDef chipselect = 
    {
        .Pin = kTouchChipSelectPin | kSdCardChipSelectPin,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = kGpioSpeed,
    };
    HAL_GPIO_Init(kChipSelectPort, &chipselect);

    __HAL_RCC_GPIOC_CLK_ENABLE();
    chipselect_high(SpiDevice::Display);
    const GPIO_InitTypeDef lcd_chipselect = 
    {
        .Pin = kLcdChipSelectPin,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = kGpioSpeed,
    };
    HAL_GPIO_Init(kLcdChipSelectPort, &lcd_chipselect);

    __HAL_RCC_GPDMA1_CLK_ENABLE();
    HAL_NVIC_EnableIRQ(GPDMA1_Channel0_IRQn);
    check(HAL_DMA_Init(&dma), "DMA init");
    __HAL_LINKDMA(&spi, hdmatx, dma);

    spi_semaphore = xSemaphoreCreateCounting(2, 1);

    message("SPI init done");
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
