#include <stdio.h>
#include <stdbool.h>
#include <stm32h5xx_hal.h>
#include <FreeRTOS.h>
#include <queue.h>

static UART_HandleTypeDef uart = 
{
    .Instance = USART3,
    .Init = 
    {
        .BaudRate = 250000,
        .Mode = UART_MODE_TX_RX,
        .OverSampling = UART_OVERSAMPLING_8,
        .ClockPrescaler = UART_PRESCALER_DIV1,
    }
};

QueueHandle_t uart_queue;

void uart_task(void *arg)
{
    for(;;)
    {
        char *msg{};
        if (xQueueReceive(uart_queue, &msg, portMAX_DELAY) == pdTRUE && msg != nullptr)
        {
            printf("%s\n", msg);
            free(msg);
        }
    }
}

void uart_init()
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART3_CLK_ENABLE();

    GPIO_InitTypeDef gpio = 
    {
        .Pin = GPIO_PIN_3 | GPIO_PIN_4,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_HIGH,
        .Alternate = GPIO_AF13_USART3
    };
    HAL_GPIO_Init(GPIOA, &gpio);
    HAL_UART_Init(&uart);

    uart_queue = xQueueCreate(64, sizeof(char*));
    xTaskCreate(uart_task, "uart_io", 64, NULL, tskIDLE_PRIORITY, NULL);
    printf("UART init OK\n");
}

static int uart_putc(char c, FILE *)
{
    HAL_UART_Transmit(&uart, (uint8_t *) &c, 1, 1000);
	return c;
}

static FILE __stdio = FDEV_SETUP_STREAM(uart_putc, NULL, NULL, _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio; __strong_reference(stdin, stdout); __strong_reference(stdin, stderr);
