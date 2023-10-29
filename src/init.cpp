#include <stm32h5xx_hal.h>
#include <stdio.h>
// printf(D" failed\n");  printf (D" OK\n");
#define check(F,D) do { if(F != HAL_OK) { } else {  } } while(0)

ADC_HandleTypeDef * adc_init()
{
    __HAL_RCC_ADC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    const GPIO_InitTypeDef gpio = 
    {
        .Pin =  GPIO_PIN_0,
        .Mode = GPIO_MODE_ANALOG
    };
    HAL_GPIO_Init(GPIOA, &gpio);

    static ADC_HandleTypeDef handle = 
    {
        .Instance = ADC1,
        .Init = 
        {
            .ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
            .Resolution = ADC_RESOLUTION_12B,
            .EOCSelection = ADC_EOC_SEQ_CONV,
            .ContinuousConvMode = ENABLE,
            .DMAContinuousRequests = ENABLE,
        }
    };

    check(HAL_ADC_Init(&handle), "ADC init");

    const ADC_ChannelConfTypeDef channel = 
    {
        .Channel = ADC_CHANNEL_0,
        .Rank = ADC_REGULAR_RANK_1,
        .SamplingTime = ADC_SAMPLETIME_3CYCLES_5,
        .SingleDiff = ADC_SINGLE_ENDED,
        .OffsetNumber = ADC_OFFSET_NONE,
    };

    check(HAL_ADC_ConfigChannel(&handle, &channel), "ADC channel config");
    check(HAL_ADCEx_Calibration_Start(&handle, ADC_SINGLE_ENDED), "ADC calibration");

    return &handle;
}

DMA_HandleTypeDef * dma_init()
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

    static DMA_HandleTypeDef handle = 
    {
        .Instance = GPDMA1_Channel0,
        .InitLinkedList = 
        {
            .Priority = DMA_HIGH_PRIORITY,
            .LinkStepMode = DMA_LSM_FULL_EXECUTION,
            .LinkAllocatedPort = DMA_LINK_ALLOCATED_PORT0,
            .TransferEventMode = DMA_TCEM_BLOCK_TRANSFER,
            .LinkedListMode = DMA_LINKEDLIST_CIRCULAR,
        }
    };

    check(HAL_DMAEx_List_Init(&handle), "DMA init");
    check(HAL_DMAEx_List_LinkQ(&handle, &list), "DMA link list to handle");

    return &handle;
}

void clock_init()
{
    // high voltage scale for high clocks
    check(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0), "set voltage scale");

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
            .PLLQ = 2,
            .PLLR = 2,
            .PLLRGE = RCC_PLL1_VCIRANGE_1,
            .PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE,
            .PLLFRACN = 0
        }
    };

    check(HAL_RCC_OscConfig(&init), "RCC config");

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

    check(HAL_RCC_ClockConfig(&clocks, FLASH_LATENCY_5), "Clock config");
}

////



