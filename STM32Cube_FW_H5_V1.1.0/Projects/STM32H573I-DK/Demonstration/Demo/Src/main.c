/**
******************************************************************************
* @file    main.c
* @author  MCD Application Team
* @brief   This file provides main program functions
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
#include "k_config.h"
#include "app_main.h"
#include "app_threadx.h"
#include "usbpd.h"
#include "stm32h5xx_ll_cortex.h"

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
volatile uint8_t User_Button_State = 0;
static void kDemo_Initialization(void);
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
uint32_t RccBootFlags = 0;
uint32_t PwrSBFlag = 0;
uint8_t  dummy=0;
HCD_HandleTypeDef hhcd_USB_DRD_FS;
PCD_HandleTypeDef hpcd_USB_DRD_FS;
DMA_HandleTypeDef handle_GPDMA1_Channel2;
__IO uint8_t TsStateCallBack;
__IO int Ts_MouseCallback;
TS_State_t TS_State;
extern const tMenu MainMenu;
RTC_HandleTypeDef RtcHandle = {0};
/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Main program
  * @retval int
  */
int main(void)
{
  HAL_Init();

  /* Enable the Instruction Cache */
  CACHE_Enable();

  /* Configure the system clock @ 250 MHz (PLL ON) */
  SystemClock_Config();
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */
  MX_GPIO_Init();
  /* LED init */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);

  /* Enable RTC & backup domain access */
  RTC_Config();

  /* Call PreOsInit function */
  USBPD_PreInitOs();

  /* demo initialization */
  kDemo_Initialization();

  /* Start the scheduling */
  MX_ThreadX_Init();

  /* we should not reach here */
  while(1);
}

/** @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  User_Button_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
}

/** @brief Demonstration kernel initialization
  * @retval None
  */
static void kDemo_Initialization(void)
{
  uint32_t pXSize;

  /* Initialize the LCD */
  if (BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE) != BSP_ERROR_NONE)
  {
    /* Initialization Error */
    Error_Handler();
  }

  UTIL_LCD_SetFuncDriver(&LCD_Driver); /* SetFunc before setting device */
  UTIL_LCD_SetDevice(0);            /* SetDevice after funcDriver is set */
  UTIL_LCD_SetFont(&UTIL_LCD_DEFAULT_FONT);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  /* Set the display on */
  if (BSP_LCD_DisplayOn(0) != BSP_ERROR_NONE)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Display the demonstration window */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(0, 0, pXSize, UTIL_LCD_DEFAULT_FONT.Height*2, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt( 0,              0,      (uint8_t *)DK_BOARD, CENTER_MODE);
  UTIL_LCD_DisplayStringAt( 0,  UTIL_LCD_DEFAULT_FONT.Height  , (uint8_t *)"DEMONSTRATION", CENTER_MODE);

  BSP_LCD_FillRGBRect(0, (uint32_t)35, (uint32_t)60, (uint8_t *)STLogo, 170, 170);

  /* Let time user to see information */
  HAL_Delay(2000);

  AppMainExec();
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  assert_failed
  *         Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  File pointer to the source file name
  * @param  Line assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line
  number,ex: printf("Wrong parameters value: file %s on line %d\r\n",
  file, line) */

  /* Infinite loop */
  while (1)
  {}
}

#endif



/* Private functions ---------------------------------------------------------*/

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSE BYPASS)
  *            SYSCLK(Hz)                     = 250000000  (CPU Clock)
  *            HCLK(Hz)                       = 250000000  (Bus matrix and AHBs Clock)
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1 (APB1 Clock  250MHz)
  *            APB2 Prescaler                 = 1 (APB2 Clock  250MHz)
  *            APB3 Prescaler                 = 1 (APB3 Clock  250MHz)
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 5
  *            PLL_N                          = 100
  *            PLL_P                          = 2
  *            PLL_Q                          = 10
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIGITAL;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 10;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Enable ICACHE with 1-way set-associative configuration.
  * @param  None
  * @retval None
  */
void CACHE_Enable(void)
{
  /** Enable instruction cache (default 2-ways set associative cache)
  */
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }

  /* MPU should be used to disable local cacheability due to accessing Flash read-only (RO) area */

  /* Disable MPU before perloading and config update */
  LL_MPU_Disable();

  /* Define Not cacheable memory via MPU */
  LL_MPU_ConfigAttributes(LL_MPU_ATTRIBUTES_NUMBER1, LL_MPU_NOT_CACHEABLE);

  /* BaseAddress-LimitAddress configuration for RO area*/
  LL_MPU_EnableRegion(LL_MPU_REGION_NUMBER1);
  LL_MPU_ConfigRegion(LL_MPU_REGION_NUMBER1,LL_MPU_REGION_ALL_RO,LL_MPU_ATTRIBUTES_NUMBER1, 0x08FFF800UL, 0x08FFFFFFUL);

  /* Enable MPU */
  LL_MPU_Enable(LL_MPU_CTRL_HFNMI_PRIVDEF);
}

/**
  * @brief  Disable ICACHE with 1-way set-associative configuration.
  * @param  None
  * @retval None
  */
void CACHE_Disable(void)
{
  /** Disable the Instruction Cache */

  if (HAL_ICACHE_Disable() != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Configures the RTC & backup domain access
  * @param  None
  * @retval None
  */
void RTC_Config(void)
{
  /* Allow Access to RTC Backup domaine */
  HAL_PWR_EnableBkUpAccess();

  /* Set the RTC time base to 1s */
  RtcHandle.Instance = RTC;
  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RtcHandle.Init.AsynchPrediv = 0x7Fu;
  RtcHandle.Init.SynchPrediv = 0x00FFu;
  RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if(HAL_RTC_Init(&RtcHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Set Calendar Ultra-Low power mode */
  if (HAL_RTCEx_SetLowPowerCalib(&RtcHandle, RTC_LPCAL_SET) != HAL_OK)
  {
    Error_Handler();
  }
}

void RTC_UnConfig(void)
{
  if(HAL_RTC_DeInit(&RtcHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}


/**
  * @brief  Error Handler.
  * @retval None
  */
void Error_Handler(void)
{
  while(1)
  {
    HAL_Delay(100);
    BSP_LED_Toggle(LED_RED);
  }
}


/**
  * @brief  BSP TS Callback.
  * @param  Instance TS Instance.
  * @retval None.
  */
void BSP_TS_Callback(uint32_t Instance)
{
  if (Instance == 0)
  {
    BSP_TS_GetState(0, &TS_State);
    if(TS_State.TouchDetected == 1)
    {
      TsStateCallBack = 1;
      Ts_MouseCallback = 1;
    }
    else
    {
      Ts_MouseCallback = 0;
    }
  }
}

/**
* @brief USB_DRD_FS Initialization Function
* @param None
* @retval None
*/
void MX_USB_DRD_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_DRD_FS_Init 0 */

  /* USER CODE END USB_DRD_FS_Init 0 */

  /* USER CODE BEGIN USB_DRD_FS_Init 1 */

  /* USER CODE END USB_DRD_FS_Init 1 */
  hpcd_USB_DRD_FS.Instance = USB_DRD_FS;
  hpcd_USB_DRD_FS.Init.dev_endpoints = 8;
  hpcd_USB_DRD_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_DRD_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.battery_charging_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.vbus_sensing_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_DRD_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_DRD_FS_Init 2 */

  /* USER CODE END USB_DRD_FS_Init 2 */

}

/**
* @brief USB_DRD_FS Initialization Function
* @param None
* @retval None
*/
void MX_USB_DRD_FS_HCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hhcd_USB_DRD_FS.Instance = USB_DRD_FS;
  hhcd_USB_DRD_FS.Init.dev_endpoints = 8;
  hhcd_USB_DRD_FS.Init.Host_channels = 8;
  hhcd_USB_DRD_FS.Init.speed = USBD_FS_SPEED;
  hhcd_USB_DRD_FS.Init.phy_itface = HCD_PHY_EMBEDDED;
  hhcd_USB_DRD_FS.Init.Sof_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.low_power_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.vbus_sensing_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.bulk_doublebuffer_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.iso_singlebuffer_enable = DISABLE;
  if (HAL_HCD_Init(&hhcd_USB_DRD_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */
  USB_DisableGlobalInt(hhcd_USB_DRD_FS.Instance);
  /* USER CODE END USB_Init 2 */

}



/**
* @brief  Period elapsed callback in non blocking mode
* @note   This function is called  when TIM6 interrupt took place, inside
* HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
* a global variable "uwTick" used as application time base.
* @param  htim : TIM handle
* @retval None
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}


/**
* @brief GPIO Initialization Function
* @param None
* @retval None
*/
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI13_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(EXTI13_IRQn);
}


void Display_Thread_Entry(ULONG arg)
{
  while(1)
  {
    kDemo_Start();
  }
}
