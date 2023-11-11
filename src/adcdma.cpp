#include <stm32h5xx_hal.h>
#include <stm32h5xx_ll_rcc.h>

#include <stdio.h>

#include "util.h"

const auto adc_ref_voltage = 3300;
volatile uint32_t adc_error = 0;

extern DMA_HandleTypeDef dma_handle;

volatile uint16_t adc_value;

ADC_HandleTypeDef adc_handle = 
{
    .Instance = ADC1,
    .Init = 
    {
        .ClockPrescaler = ADC_CLOCK_ASYNC_DIV64,
        .Resolution = ADC_RESOLUTION_8B,
        .EOCSelection = ADC_EOC_SINGLE_CONV,
        .ExternalTrigConv = ADC_SOFTWARE_START,
    },
};

DMA_HandleTypeDef dma_handle = 
{
    .Instance = GPDMA1_Channel0,
    .InitLinkedList = 
    {
        .Priority = DMA_HIGH_PRIORITY,
        .LinkStepMode = DMA_LSM_FULL_EXECUTION,
        .LinkAllocatedPort = DMA_LINK_ALLOCATED_PORT0,
        .TransferEventMode = DMA_TCEM_BLOCK_TRANSFER,
        .LinkedListMode = DMA_LINKEDLIST_CIRCULAR,
    },
    .Parent = &adc_handle
};

extern "C" void ADC1_IRQHandler()
{
    HAL_ADC_IRQHandler(&adc_handle);
}

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    adc_value = HAL_ADC_GetValue(hadc);
    HAL_ADC_Start_IT(hadc);
    // sum += __LL_ADC_CALC_DATA_TO_VOLTAGE(adc_ref_voltage, buffer[i], LL_ADC_RESOLUTION_12B);
}

extern "C" void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
    adc_error = hadc->ErrorCode;
}

// extern "C" void GPDMA1_Channel0_IRQHandler()
// {
//     HAL_DMA_IRQHandler(&dma_handle);
// }

void adc_init()
{
    LL_RCC_SetADCDACClockSource(LL_RCC_ADCDAC_CLKSOURCE_HCLK);

    __HAL_RCC_ADC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    const GPIO_InitTypeDef gpio = 
    {
        .Pin = GPIO_PIN_0,
        .Mode = GPIO_MODE_ANALOG
    };
    HAL_GPIO_Init(GPIOA, &gpio);

    check(HAL_ADC_Init(&adc_handle), "ADC init");

    const ADC_ChannelConfTypeDef channel = 
    {
        .Channel = ADC_CHANNEL_0,
        .Rank = ADC_REGULAR_RANK_1,
        .SamplingTime = ADC_SAMPLETIME_640CYCLES_5,
        .SingleDiff = ADC_SINGLE_ENDED,
        .OffsetNumber = ADC_OFFSET_NONE,
    };

    check(HAL_ADC_ConfigChannel(&adc_handle, &channel), "ADC channel config");
    check(HAL_ADCEx_Calibration_Start(&adc_handle, ADC_SINGLE_ENDED), "ADC calibration");

    extern ADC_HandleTypeDef adc_handle;
    HAL_ADC_Start_IT(&adc_handle);
}

void dma_init()
{
    __HAL_RCC_GPDMA1_CLK_ENABLE();
    HAL_NVIC_EnableIRQ(GPDMA1_Channel0_IRQn);

    DMA_NodeConfTypeDef node_config =
    {
        .NodeType = DMA_GPDMA_LINEAR_NODE,
        .Init =
        {
            .Request = GPDMA1_REQUEST_ADC1,
            .DestInc = DMA_DINC_INCREMENTED,
            .SrcDataWidth = DMA_SRC_DATAWIDTH_HALFWORD,
            .DestDataWidth = DMA_DEST_DATAWIDTH_HALFWORD,
            .SrcBurstLength = 1,
            .DestBurstLength = 64,
            .TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0|DMA_DEST_ALLOCATED_PORT0
        }
    };

    static DMA_NodeTypeDef node;
    static DMA_QListTypeDef list;

    check(HAL_DMAEx_List_BuildNode(&node_config, &node), "DMA build node");
    check(HAL_DMAEx_List_InsertNode_Tail(&list, &node), "DMA insert node");
    check(HAL_DMAEx_List_SetCircularModeConfig(&list, &node), "DMA make list circular");

    check(HAL_DMAEx_List_Init(&dma_handle), "DMA init");
    check(HAL_DMAEx_List_LinkQ(&dma_handle, &list), "DMA link list to handle");
}
