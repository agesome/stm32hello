#include "util.h"

void clock_init()
{
    // high voltage scale for high clocks
    check_silent(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0));

    // HSE -> PLL1 at 250MHz
    const RCC_OscInitTypeDef init =
    {
        .OscillatorType = RCC_OSCILLATORTYPE_HSE,
        .HSEState = RCC_HSE_ON,
        .PLL = 
        {
            .PLLState = RCC_PLL_ON,
            .PLLSource = RCC_PLL1_SOURCE_HSE,
            .PLLM = 12,
            .PLLN = 250,
            .PLLP = 2,
            .PLLQ = 4,
            .PLLR = 2,
            .PLLRGE = RCC_PLL1_VCIRANGE_1,
            .PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE,
            .PLLFRACN = 0
        }
    };

    check_silent(HAL_RCC_OscConfig(&init));

    // all clocks from PLL1
    const RCC_ClkInitTypeDef clocks =
    {
        .ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2|RCC_CLOCKTYPE_PCLK3,
        .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
        .AHBCLKDivider = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV1,
        .APB2CLKDivider = RCC_HCLK_DIV1,
        .APB3CLKDivider = RCC_HCLK_DIV1
    };

    check_silent(HAL_RCC_ClockConfig(&clocks, FLASH_LATENCY_5));
}
