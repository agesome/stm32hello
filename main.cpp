#include <stm32h5xx_hal.h>
#include <stm32h5xx_nucleo.h>
#include <stdio.h>

#define check(F,D) do { if(F != HAL_OK) { printf(D" failed\n"); } else { printf (D" OK\n"); } } while(0)

ADC_HandleTypeDef adc_handle = {};

uint16_t adc_ref_voltage = 0;

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
        uint32_t value = __LL_ADC_CALC_DATA_TO_VOLTAGE(adc_ref_voltage, HAL_ADC_GetValue(hadc), LL_ADC_RESOLUTION_12B);
        printf("ADC conv callback: %lumv\n", value);
    }

    void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
    {
        printf("ADC error callback\n");
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
    adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    adc_handle.Init.LowPowerAutoWait = DISABLE;
    adc_handle.Init.ContinuousConvMode = DISABLE;
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
    channel.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
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

int main(void)
{
    HAL_Init();

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

    for (;;)
    {
        HAL_Delay(1000);
        BSP_LED_Toggle(LED2);
        HAL_ADC_Start_IT(&adc_handle);
    }

    return 0;
}