#include <stdio.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <queue>

#include "util.h"

void check(HAL_StatusTypeDef status, const char desc[])
{
    if (status != HAL_OK)
    {
        message("%s failed", desc);
    }
    else
    {
        message("%s OK", desc);
    }
}

void check_silent(HAL_StatusTypeDef status)
{
    if (status != HAL_OK)
    {
        for (;;) {}
    }
}

void message(const char *format, ...)
{
    const size_t log_buflen = 512;
    static thread_local char buf[log_buflen];

    va_list args;
    va_start(args, format);
    vsnprintf(buf, log_buflen, format, args);
    va_end(args);

    char *msg = (char*) calloc(strlen(buf) + 1, sizeof(char));
    strcpy(msg, buf);

    extern QueueHandle_t uart_queue;
    if (xQueueSend(uart_queue, &msg, portMAX_DELAY) != pdTRUE)
    {
        for(;;) {}
    }
}
