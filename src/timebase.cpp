#include <stm32h5xx_hal.h>

#include "util.h"

static TIM_HandleTypeDef timer = 
{
    .Instance = TIM2,
    .Init =
    {
        .Prescaler = __HAL_TIM_CALC_PSC(250000000, 100000),
        .Period = __HAL_TIM_CALC_PERIOD(250000000, __HAL_TIM_CALC_PSC(250000000, 100000), 50000),
    },
    .Channel = HAL_TIM_ACTIVE_CHANNEL_1
};

volatile uint32_t timebase{};

extern "C" void TIM2_IRQHandler()
{
    HAL_TIM_IRQHandler(&timer);
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    timebase = timebase + 1;
}


void timebase_init()
{
    __HAL_RCC_TIM2_CLK_ENABLE();
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    check(HAL_TIM_Base_Init(&timer), "TIM2 init");
    HAL_TIM_Base_Start_IT(&timer);
}