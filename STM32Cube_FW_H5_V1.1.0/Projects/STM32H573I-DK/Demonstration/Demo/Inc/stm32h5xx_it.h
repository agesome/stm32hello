/**
  ******************************************************************************
  * @file    stm32u5xx_it.h
  * @author  MCD Application Team
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_IT_H
#define STM32H5xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx.h"
#include "stm32h573i_discovery.h"
#include "stm32h573i_discovery_audio.h"
#include "stm32h573i_discovery_sd.h"
#include "stm32h573i_discovery_ts.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI1_IRQHandler(void);
void EXTI5_IRQHandler(void);
void EXTI13_IRQHandler(void);
void EXTI7_IRQHandler(void);
void EXTI15_IRQHandler(void);
void GPDMA1_Channel0_IRQHandler(void);
void GPDMA1_Channel1_IRQHandler(void);
void GPDMA1_Channel2_IRQHandler(void);
void GPDMA1_Channel6_IRQHandler(void);
void SDMMC1_IRQHandler(void);
void RTC_IRQHandler(void);


void GPDMA1_Channel3_IRQHandler(void);
void GPDMA1_Channel5_IRQHandler(void);
void TIM6_IRQHandler(void);
void USART1_IRQHandler(void);
void USB_DRD_FS_IRQHandler(void);
void UCPD1_IRQHandler(void);



#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_IT_H */
