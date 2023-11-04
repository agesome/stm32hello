#include <stdio.h>
#include <stdarg.h>

#include <stm32h5xx_hal.h>

#include <FreeRTOS.h>
#include <task.h>

#include "util.h"
#include "spi.h"
#include "sdcard.h"

void adc_init();
void dma_init();
void clock_init();
void uart_init();
void lcd_init();

const auto adc_ref_voltage = 3300;
volatile uint32_t adc_error = 0;
volatile uint32_t conversions = 0;
volatile uint32_t adc_sum = 0;

const size_t buflen = 128;
uint16_t buffer[buflen];

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

void mainloop(void *arg)
{
    message("enter mainloop");
    for(;;)
    {
        vTaskDelay(500);
    }
}

void spi_change_speed();

void init_task(void *arg)
{
    clock_init();
    HAL_Init();
    uart_init();

    // adc_init();
    // dma_init();

    HAL_ICACHE_Enable();
    
    // extern ADC_HandleTypeDef adc_handle;
    // HAL_ADC_Start_DMA(&adc_handle, (uint32_t *) &buffer, buflen);

    spi_init();
    lcd_init();

#if 0
    if (sdcard_init())
    {
        spi_change_speed();
        sdcard_get_cid();
    }
    else
    {
        message("sdcard init NOK");
    }
#endif

    xTaskCreate(mainloop, "mainloop", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    vTaskDelete(NULL);
}

int main(void)
{
    xTaskCreate(init_task, "init_task", 2048, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    for (;;) {}

    return 0;
}