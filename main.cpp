#include <stm32h5xx_hal.h>
#include <stm32h5xx_nucleo.h>
#include <stdio.h>

ADC_HandleTypeDef * adc_init();
DMA_HandleTypeDef * dma_init();
void clock_init();

ADC_HandleTypeDef * adc_handle{};
DMA_HandleTypeDef * dma_handle{};

const auto adc_ref_voltage = 3300;
volatile uint32_t adc_error = 0;
volatile uint32_t conversions = 0;
volatile uint32_t adc_sum = 0;

const size_t buflen = 12288;
uint16_t buffer[buflen];

extern "C" void ADC1_IRQHandler()
{
    HAL_ADC_IRQHandler(adc_handle);
}

extern "C" void GPDMA1_Channel0_IRQHandler()
{
    HAL_DMA_IRQHandler(dma_handle);
}

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint32_t sum{};
    for (size_t i = buflen / 2; i < buflen; ++i)
    {
        sum += __LL_ADC_CALC_DATA_TO_VOLTAGE(adc_ref_voltage, buffer[i], LL_ADC_RESOLUTION_12B);
    }
    adc_sum = adc_sum + sum;
    conversions = conversions + buflen;
}

extern "C" void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint32_t sum{};
    for (size_t i = 0; i < buflen / 2; ++i)
    {
        sum += __LL_ADC_CALC_DATA_TO_VOLTAGE(adc_ref_voltage, buffer[i], LL_ADC_RESOLUTION_12B);
    }
    adc_sum = adc_sum + sum;
}

extern "C" void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
    adc_error = hadc->ErrorCode;
}

int main(void)
{
    HAL_Init();

    BSP_LED_Init(LED2);
    BSP_LED_On(LED2);

    clock_init();

    COM_InitTypeDef init = { .BaudRate = 115200 };
    BSP_COM_Init(COM1, &init);
    BSP_COM_SelectLogPort(COM1);
    
    printf("%s\n", BSP_GetBoardName());

    adc_handle = adc_init();
    dma_handle = dma_init();
    adc_handle->DMA_Handle = dma_handle;
    dma_handle->Parent = adc_handle;

    HAL_ICACHE_Enable();

    uint32_t tick = HAL_GetTick();
    HAL_ADC_Start_DMA(adc_handle, (uint32_t *) &buffer, buflen);

    for (;;)
    {
        HAL_Delay(1000);
        if (adc_error != HAL_ADC_ERROR_NONE)
        {
            printf("ADC error: %lu\n", adc_error);
            adc_error = HAL_ADC_ERROR_NONE;
        }
        printf("conv/msec: %lu\n", conversions / (HAL_GetTick() - tick));
        // printf("adc avg: %llu\n", adc_sum / conversions);
        // conversions = 0;
        // adc_sum = 0;
    }

    return 0;
}