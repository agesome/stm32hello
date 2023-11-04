#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

void vApplicationMallocFailedHook(void)
{
    printf("malloc failed!\n");
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    printf("stack overflow in task: %s\n", pcTaskName);
}