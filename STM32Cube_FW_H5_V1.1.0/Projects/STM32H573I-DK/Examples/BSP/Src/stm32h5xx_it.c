/**
  ******************************************************************************
  * @file    stm32h5xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "main.h"
#include "stm32h5xx_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M33 Processor Exceptions Handlers                         */
/******************************************************************************/

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
void PendSV_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32H5xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32H5xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles External line 7 interrupt request.
  * @retval None
  */
void EXTI7_IRQHandler(void)
{
  BSP_TS_IRQHandler(0);
}

/**
  * @brief  This function handles External line 13 interrupt request.
  * @retval None
  */
void EXTI13_IRQHandler(void)
{
  BSP_PB_IRQHandler(BUTTON_USER);
}

/**
  * @brief  This function handles External line 14 interrupt request.
  * @retval None
  */
void EXTI14_IRQHandler(void)
{
  BSP_SD_DETECT_IRQHandler(0);
}

/**
  * @brief  This function handles GPDMA1 Channel1 interrupt request.
  * @retval None
  */
void GPDMA1_Channel1_IRQHandler(void)
{
  BSP_AUDIO_IN_IRQHandler(0,AUDIO_IN_DEVICE_DIGITAL_MIC);
}

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
  BSP_AUDIO_IN_IRQHandler(0,AUDIO_IN_DEVICE_DIGITAL_MIC);
}

/**
  * @brief  This function handles SDMMC1 interrupt request.
  * @retval None
  */
void SDMMC1_IRQHandler(void)
{
  BSP_SD_IRQHandler(0);
}