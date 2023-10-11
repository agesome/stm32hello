#include <stm32h5xx_hal.h>
#include <stm32h5xx_nucleo.h>
#include <stdio.h>

#define check(F,D) do { if(F != HAL_OK) { printf(D" failed\n"); } else { printf (D" OK\n"); } } while(0)

ADC_HandleTypeDef adc_handle = {};

uint16_t adc_ref_voltage = 0;
volatile uint32_t adc_error = 0;

volatile uint16_t adc_value = 0;
volatile uint64_t conversions = 0;
volatile uint64_t adc_sum = 0;

extern "C"
{
    void SysTick_Handler(void)
    {
        HAL_IncTick();
    }

    void BSP_PB_Callback(Button_TypeDef button)
    {
        printf("button pressed: %d\n", button);
    }

    void EXTI13_IRQHandler()
    {
        BSP_PB_IRQHandler(BUTTON_USER);
    }

    void ADC1_IRQHandler()
    {
        HAL_ADC_IRQHandler(&adc_handle);
    }

    void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
    {
        uint16_t value = __LL_ADC_CALC_DATA_TO_VOLTAGE(adc_ref_voltage, HAL_ADC_GetValue(hadc), LL_ADC_RESOLUTION_12B);
        adc_sum += value;
        // adc_value = value;
        ++conversions;
    }

    void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
    {
        adc_error = hadc->ErrorCode;
    }
}

void ADC_init()
{
    __HAL_RCC_ADC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    GPIO_InitTypeDef gpio = {};
    gpio.Pin = GPIO_PIN_0;
    gpio.Mode = GPIO_MODE_ANALOG;

    HAL_GPIO_Init(GPIOA, &gpio);

    adc_handle.Instance = ADC1;
    adc_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
    adc_handle.Init.Resolution = ADC_RESOLUTION_12B;
    adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;
    adc_handle.Init.EOCSelection = ADC_EOC_SEQ_CONV;
    adc_handle.Init.LowPowerAutoWait = DISABLE;
    adc_handle.Init.ContinuousConvMode = ENABLE;
    adc_handle.Init.NbrOfConversion = 1;
    adc_handle.Init.DiscontinuousConvMode = DISABLE;
    adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adc_handle.Init.DMAContinuousRequests = DISABLE;
    adc_handle.Init.SamplingMode = ADC_SAMPLING_MODE_NORMAL;
    adc_handle.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    adc_handle.Init.OversamplingMode = DISABLE;

    check(HAL_ADC_Init(&adc_handle), "ADC init");

    ADC_ChannelConfTypeDef channel = {};
    channel.Channel = ADC_CHANNEL_VREFINT;
    channel.Rank = ADC_REGULAR_RANK_1;
    channel.SamplingTime = ADC_SAMPLETIME_6CYCLES_5;
    channel.SingleDiff = ADC_SINGLE_ENDED;
    channel.OffsetNumber = ADC_OFFSET_NONE;
    channel.Offset = 0;

    check(HAL_ADC_ConfigChannel(&adc_handle, &channel), "ADC channel config");
    check(HAL_ADCEx_Calibration_Start(&adc_handle, ADC_SINGLE_ENDED), "ADC calibration");

    HAL_ADC_Start(&adc_handle);
    check(HAL_ADC_PollForConversion(&adc_handle, 5000UL), "wait for vfref conversion");
    adc_ref_voltage = __LL_ADC_CALC_VREFANALOG_VOLTAGE(HAL_ADC_GetValue(&adc_handle), ADC_RESOLUTION_12B);
    printf("Vref/VDDA: %umv\n", adc_ref_voltage);
    HAL_ADC_Stop(&adc_handle);

    channel.Channel = ADC_CHANNEL_0;
    check(HAL_ADC_ConfigChannel(&adc_handle, &channel), "ADC channel config");
}

void clock_init()
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);
    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 12;
    RCC_OscInitStruct.PLL.PLLN = 250;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_1;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    check(HAL_RCC_OscConfig(&RCC_OscInitStruct), "RCC config");

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                                |RCC_CLOCKTYPE_PCLK3;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

    check(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5), "Clock config");
    HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_1);
}

int main(void)
{
    HAL_Init();
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    clock_init();

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
    
    printf("hello world\n");

    ////

    ADC_init();

    HAL_ICACHE_Enable();

    BSP_LED_On(LED2);
    HAL_ADC_Start_IT(&adc_handle);

    const unsigned delay = 1000;

    for (;;)
    {
        HAL_Delay(delay);
        if (adc_error != HAL_ADC_ERROR_NONE)
        {
            printf("ADC error: %lu\n", adc_error);
            adc_error = HAL_ADC_ERROR_NONE;
        }
        printf("conv/sec: %llu\n", conversions);
        printf("adc avg: %llu\n", adc_sum / conversions);
        conversions = 0;
        adc_sum = 0;
    }

    return 0;
}