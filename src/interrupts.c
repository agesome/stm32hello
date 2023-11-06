#include <stdint.h>
#include <stdio.h>
#include <stm32h5xx_hal.h>

#include <FreeRTOS.h>
#include <portasm.h>

#include <lvgl.h>

void _start(void);
extern uint8_t __stack[];

void SysTick_Handler();

void hardfault_handler()
{
    for(;;) {}
}

void memmanage_handler()
{
    for(;;) {}
}

void busfault_handler()
{
    for(;;) {}
}

void usagefault_handler()
{
    for(;;) {}
}

void systick_handler()
{
    SysTick_Handler();
    HAL_IncTick();
    lv_tick_inc(1);
}

void default_handler()
{
    for(;;) {}
}

#define entry(addr,value) [(addr)/4] = (void(*)(void)) value

void ADC1_IRQHandler();
void GPDMA1_Channel0_IRQHandler();

__attribute__((__section__(".data.init.enter")))
void (* const __interrupt_vector[256])(void) __attribute((aligned(128))) =
{
    entry(0x00, __stack),
    entry(0x04, _start),
    entry(0x08, default_handler),
    entry(0x0c, hardfault_handler),
    entry(0x10, memmanage_handler),
    entry(0x14, busfault_handler),
    entry(0x18, usagefault_handler),
    entry(0x2c, SVC_Handler), // svc
    entry(0x30, default_handler), // debugmon
    entry(0x38, PendSV_Handler), // pendsv
    entry(0x3c, systick_handler),
    [ADC1_IRQn + NVIC_USER_IRQ_OFFSET] = ADC1_IRQHandler,
    [GPDMA1_Channel0_IRQn + NVIC_USER_IRQ_OFFSET] = GPDMA1_Channel0_IRQHandler
};
