#include <stdio.h>
#include <stm32h5xx_hal.h>

static UART_HandleTypeDef uart = 
{
    .Instance = USART3,
    .Init = 
    {
        .BaudRate = 115200,
        .Mode = UART_MODE_TX_RX,
        .OverSampling = UART_OVERSAMPLING_8,
        .ClockPrescaler = UART_PRESCALER_DIV1,
    }
};

void uart_init()
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART3_CLK_ENABLE();

    GPIO_InitTypeDef gpio = 
    {
        .Pin = GPIO_PIN_4,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_HIGH,
        .Alternate = GPIO_AF13_USART3
    };
    HAL_GPIO_Init(GPIOA, &gpio);

    gpio.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOA, &gpio);

    HAL_UART_Init(&uart);
}


static int uart_putc(char c, FILE *)
{
    HAL_UART_Transmit(&uart, (uint8_t *) &c, 1, 1000);
	return c;
}

static FILE __stdio = FDEV_SETUP_STREAM(uart_putc, NULL, NULL, _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio; __strong_reference(stdin, stdout); __strong_reference(stdin, stderr);
