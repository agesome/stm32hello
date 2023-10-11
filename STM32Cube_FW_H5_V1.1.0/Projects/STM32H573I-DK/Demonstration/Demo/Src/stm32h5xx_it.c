/**
  ******************************************************************************
  * @file    stm32h5xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_it.h"
#include "stm32h5xx_ll_exti.h"
#include "usbpd.h"
#include "tracer_emb.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern DMA_HandleTypeDef DAC_DMAHandle;
extern RTC_HandleTypeDef RtcHandle;

extern DMA_HandleTypeDef handle_GPDMA1_Channel2;
extern UART_HandleTypeDef huart1;
extern HCD_HandleTypeDef hhcd_USB_DRD_FS;
extern PCD_HandleTypeDef hpcd_USB_DRD_FS;
extern TIM_HandleTypeDef htim6;
extern uint8_t Host;


/* Private function prototypes -----------------------------------------------*/
#if defined(TCPP0203_SUPPORT)
void EXTI8_IRQHandler(void);
#endif /* TCPP0203_SUPPORT */
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M33 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief This function handles EXTI Line13 interrupt.
  */
void EXTI13_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI13_IRQn 0 */

  /* USER CODE END EXTI13_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI13_IRQn 1 */

  /* USER CODE END EXTI13_IRQn 1 */
}

#if defined(TCPP0203_SUPPORT)
/**
  * @brief  This function handles external line interrupt request.
  *         (Associated to FLGn line in case of TCPP0203 management)
  * @retval None
  */

void EXTI1_IRQHandler(void)
{
  /* Manage Flags */
  if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_1) != RESET)

  {
    /* Call BSP USBPD PWR callback */
    BSP_USBPD_PWR_EventCallback(USBPD_PWR_TYPE_C_PORT_1);

    /* Clear Flag */
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_1);

  }
}

#endif /* TCPP0203_SUPPORT */


/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  TRACER_EMB_IRQHandlerUSART();
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USB DRD FS global interrupt.
  */
void USB_DRD_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */
  if (hhcd_USB_DRD_FS.State == HAL_HCD_STATE_READY)
  {
    /* USER CODE END OTG_FS_IRQn 0 */
    HAL_HCD_IRQHandler(&hhcd_USB_DRD_FS);
  }

  if (hpcd_USB_DRD_FS.State == HAL_PCD_STATE_READY)
  {
    HAL_PCD_IRQHandler(&hpcd_USB_DRD_FS);
  }
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}



/**
  * @brief This function handles UCPD1 global interrupt.
  */
void UCPD1_IRQHandler(void)
{
  /* USER CODE BEGIN UCPD1_IRQn 0 */

  /* USER CODE END UCPD1_IRQn 0 */
  USBPD_PORT0_IRQHandler();

  /* USER CODE BEGIN UCPD1_IRQn 1 */

  /* USER CODE END UCPD1_IRQn 1 */
}


/**
  * @brief This function handles GPDMA1 Channel 1 global interrupt.
  */
void GPDMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN GPDMA1_Channel2_IRQn 0 */

  /* USER CODE END GPDMA1_Channel2_IRQn 0 */
  TRACER_EMB_IRQHandlerDMA();
  /* USER CODE BEGIN GPDMA1_Channel2_IRQn 1 */

  /* USER CODE END GPDMA1_Channel2_IRQn 1 */
}



/**
  * @brief This function handles TIM6 global interrupt.
  */
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */
  USBPD_DPM_TimerCounter();
#if defined(_GUI_INTERFACE)
  GUI_TimerCounter();
#endif /* _GUI_INTERFACE */
  /* USER CODE END TIM6_IRQn 1 */
}

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
/*
void PendSV_Handler(void)
{
  while (1)
  {
  }
}
*/

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

/*
 void SysTick_Handler(void)
{
  HAL_IncTick();
}
*/

/******************************************************************************/
/*                 STM32H5xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32h5xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles External line 7 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI7_IRQHandler(void)
{
  BSP_TS_IRQHandler(0);
}

/**
  * @brief  This function handles SDMMC1 interrupt request.
  * @param  None
  * @retval None
  */
void SDMMC1_IRQHandler(void)
{
  HAL_SD_IRQHandler(&hsd_sdmmc[0]);
}


/* Audio Module */

/**
  * @brief  This function handles GPDMA1 Channel2 interrupt request.
  * @retval None
  */
void GPDMA1_Channel2_IRQHandler(void)
{
  BSP_AUDIO_OUT_IRQHandler(0, AUDIO_OUT_DEVICE_HEADPHONE);
}

/**
  * @brief  This function handles GPDMA1 Channel3 interrupt request.
  * @retval None
  */
void GPDMA1_Channel3_IRQHandler(void)
{
  BSP_AUDIO_IN_IRQHandler(1,AUDIO_IN_DEVICE_DIGITAL_MIC);
}

/**
  * @brief  This function handles RTC interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
  HAL_RTCEx_WakeUpTimerIRQHandler(&RtcHandle);
  HAL_RTC_AlarmIRQHandler(&RtcHandle);
}
