#include <stm32h5xx_hal.h>
#include <stdio.h>

#define check(F,D) do { if(F != HAL_OK) { printf(D" failed\n"); } else { printf (D" OK\n"); } } while(0)

ADC_HandleTypeDef & adc_init()
{
    __HAL_RCC_ADC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    GPIO_InitTypeDef gpio = 
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
            .ClockPrescaler = ADC_CLOCK_ASYNC_DIV2,
            .Resolution = ADC_RESOLUTION_12B,
            .EOCSelection = ADC_EOC_SEQ_CONV,
            .ContinuousConvMode = ENABLE,
            .DMAContinuousRequests = ENABLE,
        }
    };

    check(HAL_ADC_Init(&handle), "ADC init");

    ADC_ChannelConfTypeDef channel = 
    {
        .Channel = ADC_CHANNEL_0,
        .Rank = ADC_REGULAR_RANK_1,
        .SamplingTime = ADC_SAMPLETIME_6CYCLES_5,
        .SingleDiff = ADC_SINGLE_ENDED,
        .OffsetNumber = ADC_OFFSET_NONE,
    };

    check(HAL_ADC_ConfigChannel(&handle, &channel), "ADC channel config");
    check(HAL_ADCEx_Calibration_Start(&handle, ADC_SINGLE_ENDED), "ADC calibration");

    return handle;
}

DMA_HandleTypeDef & dma_init()
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
            .DestBurstLength = 64, // ???
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
        // .Parent = &adc_handle;
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

    return handle;
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