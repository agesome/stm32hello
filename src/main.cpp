#include <stdio.h>
#include <stdarg.h>

#include <stm32h5xx_hal.h>

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>

ADC_HandleTypeDef * adc_init();
DMA_HandleTypeDef * dma_init();
void clock_init();

ADC_HandleTypeDef * adc_handle{};
DMA_HandleTypeDef * dma_handle{};

const auto adc_ref_voltage = 3300;
volatile uint32_t adc_error = 0;
volatile uint32_t conversions = 0;
volatile uint32_t adc_sum = 0;

const size_t buflen = 128;
uint16_t buffer[buflen];

QueueHandle_t uart_queue;// = xQueueCreate(32, sizeof(char*));

void log(const char *format, ...)
{
    const size_t log_buflen = 512;
    char *buf = (char*) malloc(log_buflen);

    va_list args;
    va_start(args, format);
    vsnprintf(buf, log_buflen, format, args);
    va_end(args);
    xQueueSend(uart_queue, &buf, portMAX_DELAY);
}

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

void led_task(void *arg)
{
    for(;;)
    {
        vTaskDelay(500);
        // BSP_LED_Toggle(LED2);
    }
}

void uart_io(void *arg)
{
    for(;;)
    {
        char *msg{};
        xQueueReceive(uart_queue, &msg, portMAX_DELAY);
        if (msg)
        {
            printf("%s\n", msg);
            free(msg);
        }
    }
}

extern "C" void uart_init();

void init_task(void *arg)
{
    // BSP_LED_Init(LED2);
    // BSP_LED_On(LED2);

    clock_init();
    uart_init();

    // COM_InitTypeDef init = { .BaudRate = 115200 };
    // BSP_COM_Init(COM1, &init);
    // BSP_COM_SelectLogPort(COM1);
    
    adc_handle = adc_init();
    dma_handle = dma_init();
    adc_handle->DMA_Handle = dma_handle;
    dma_handle->Parent = adc_handle;

    HAL_ICACHE_Enable();
    
    HAL_ADC_Start_DMA(adc_handle, (uint32_t *) &buffer, buflen);

    vTaskDelete(NULL);
}

int main(void)
{
    // xTaskCreate(init_task, "init_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
    // xTaskCreate(uart_io, "uart_io", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
    // xTaskCreate(led_task, "blinky", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    SystemInit();
    clock_init();
    HAL_Init();
    uart_init();

    // NVIC_SetVector(GPDMA1_Channel0_IRQn, (uint32_t) GPDMA1_Channel0_IRQHandler);
    // NVIC_SetVector(ADC1_IRQn, (uint32_t) ADC1_IRQHandler);

    adc_handle = adc_init();
    dma_handle = dma_init();
    adc_handle->DMA_Handle = dma_handle;
    dma_handle->Parent = adc_handle;

    HAL_ICACHE_Enable();
    
    HAL_ADC_Start_DMA(adc_handle, (uint32_t *) &buffer, buflen);

    // vTaskStartScheduler();

    for (;;)
    {
        printf("hello? %u\n", HAL_RCC_GetHCLKFreq());
        HAL_Delay(1000);
    }

    return 0;
}