#include <stm32h5xx_hal.h>
#include <stm32h5xx_nucleo.h>
#include <stdio.h>

volatile unsigned delay = 100;

extern "C"
{
    void SysTick_Handler(void)
    {
        HAL_IncTick();
    }

    void BSP_PB_Callback(Button_TypeDef button)
    {
        delay += 100;
        delay %= 1000;
        printf("button pressed: %d\n", button);
    }

    void EXTI13_IRQHandler(void)
    {
        BSP_PB_IRQHandler(BUTTON_USER);
    }
}

int main(void)
{
    BSP_LED_Init(LED2);
    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);
    COM_InitTypeDef init =
    {
        .BaudRate = 115200,
        .WordLength = COM_WORDLENGTH_8B,
        .StopBits = COM_STOPBITS_1,
        .Parity = COM_PARITY_NONE,
        .HwFlowCtl = COM_HWCONTROL_NONE
    };
    BSP_COM_Init(COM1, &init);
    BSP_COM_SelectLogPort(COM1);
    
    HAL_Init();

    printf("hello world\n");

    for (;;)
    {
        HAL_Delay(300);
        BSP_LED_Toggle(LED2);
    }

    return 0;
}