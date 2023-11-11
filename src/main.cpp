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
void ui_init();
void timebase_init();

void mainloop(void *arg)
{
    message("start mainloop");
    for(;;)
    {
        vTaskDelay(500);
    }
}

void init_task(void *arg)
{
    clock_init();
    HAL_Init();
    HAL_ICACHE_Enable();
    
    uart_init();
    timebase_init();
    adc_init();
    spi_init();
    lcd_init();
    ui_init();

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

    xTaskCreate(mainloop, "mainloop", 128, NULL, tskIDLE_PRIORITY, NULL);
    vTaskDelete(NULL);
}

int main(void)
{
    xTaskCreate(init_task, "init_task", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    return 0;
}