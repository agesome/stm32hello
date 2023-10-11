/**
  ******************************************************************************
  * @file    app_crypto.c
  * @author  MCD Application Team
  * @brief   crypto application implementation.
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
#ifndef __APP_CRYPTO_C
#define __APP_CRYPTO_C

/* Includes ------------------------------------------------------------------*/
#include "k_config.h"
#include "app_crypto.h"

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define OSPI_PLAIN_CODE_START_OFFSET_ADD       0x3000
#define OSPI_CIPHER_CODE_START_OFFSET_ADD      0
#define REGION_SIZE 0x0CFFFFFF
#define CRYPTO_APP_STACK_SIZE                  (1024)
#define AXES_OFFSET                            (3000)

/* Private macro -------------------------------------------------------------*/
#if defined(__ICCARM__)
#pragma section =".ospi_ext_mem1_init"
#pragma section =".ospi_ext_mem1"
#pragma section =".ospi_ext_mem2_init"
#pragma section =".ospi_ext_mem2"
#elif defined(__ARMCC_VERSION)
extern uint32_t Load$$OSPI_EXT_MEM1$$Base;
extern uint32_t Load$$OSPI_EXT_MEM1$$Length;
extern uint32_t Load$$OSPI_EXT_MEM2$$Base;
extern uint32_t Load$$OSPI_EXT_MEM2$$Length;
#elif defined(__GNUC__)
extern uint32_t _ospi_ext_mem1_init_base;
extern uint32_t _ospi_ext_mem1_init_length;
extern uint32_t _ospi_ext_mem2_init_base;
extern uint32_t _ospi_ext_mem2_init_length;
extern uint32_t _ospi_ext_cipher_data_base;
extern uint32_t _ospi_ext_cipher_data_length;
extern uint32_t _ospi_ext_plain_data_base;
extern uint32_t _ospi_ext_plain_dataa_length;
#endif
BSP_OSPI_NOR_Init_t NOR_init;

complex Tab1Clpx[8][8] = {0};
__IO uint32_t *ospi_mem_addr;

static const uint32_t matrix1[8][8] = {{0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF},
                                       {0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF},
                                       {0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF},
                                       {0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF},
                                       {0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF},
                                       {0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF},
                                       {0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF},
                                       {0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEFF, 0xFABCDEFF, 0xFFABCDEF, 0xFFFABCDE, 0xFABCDEF}};

static const uint32_t matrix2[8][8] = {{0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55},
                                       {0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55},
                                       {0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55},
                                       {0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55},
                                       {0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55},
                                       {0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55},
                                       {0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55},
                                       {0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55, 0xFABCDE11, 0x88ABCDEF, 0x44FABCDE, 0xFABCDE55}};
#if defined ( __ICCARM__ )
#pragma default_variable_attributes = @ ".ospi_ext_plain_data"
static uint32_t matrix1_1[8][8];
static uint32_t matrix2_1[8][8];
#pragma default_variable_attributes =

#pragma default_variable_attributes = @ ".ospi_ext_cipher_data"
static uint32_t matrix1_0[8][8];
static uint32_t matrix2_0[8][8];
#pragma default_variable_attributes =

#elif defined ( __GNUC__ )
static uint32_t matrix1_1[8][8] __attribute__((section (".ospi_ext_plain_data")));
static uint32_t matrix2_1[8][8] __attribute__((section (".ospi_ext_plain_data")));
static uint32_t matrix1_0[8][8] __attribute__((section (".ospi_ext_cipher_data")));
static uint32_t matrix2_0[8][8] __attribute__((section (".ospi_ext_cipher_data")));
#endif

/* Private function prototypes -----------------------------------------------*/
void  cr_app_thread_entry(ULONG arg);
static void Initialize_Data(void);
static complex * ExecuteCipherCode(void);
static complex * ExecutePlainCode(void);
static uint8_t CRC_PlainCode(uint32_t * keyin);
static uint8_t CRC_CipherCode(uint32_t * keyin);
static void Crypt_Code(uint32_t *Plain, uint32_t *Cipher);
static void Decrypt_Code(void);
static uint8_t Ref_CRC_computation(uint32_t * keyin);

/* Private Variable ----------------------------------------------------------*/
extern __IO uint8_t TsStateCallBack;
extern TS_State_t TS_State;
uint8_t *flash_ciphered_code_addr;
uint8_t *flash_plain_code_addr;
uint32_t max_size_cipher;
uint32_t max_size_plain;
uint32_t PlainCode[512]={0};
uint32_t CryptedCode[512]={0};
uint32_t tick_cipher, tick_plain;
uint32_t tick_cipher1, tick_plain1;
uint32_t tick_cipher2, tick_plain2;
uint32_t width_cipher = 0, width_plain = 0;
/* OTFDEC variables ----------------------------------------------------------*/
uint32_t Key [4]  = { 0x71234567, 0x89ABCDEF, 0x71234567, 0x89ABCDEF };

TX_THREAD                                cr_app_thread;
/* Private typedef -----------------------------------------------------------*/
OTFDEC_HandleTypeDef hotfdec_crypt = {0};
OTFDEC_RegionConfigTypeDef Config_crypt= {0};
OTFDEC_HandleTypeDef hotfdec_decrypt = {0};
OTFDEC_RegionConfigTypeDef Config_decrypt = {0};

/* External variables --------------------------------------------------------*/
extern TX_THREAD                         Display_thread_entry;
/* function prototypes -----------------------------------------------*/

/**
* @brief  Application About Demo Initialization.
* @param memory_ptr: memory pointer
* @retval int
*/
UINT Crypto_Init_pool(VOID *memory_ptr)
{
  UINT ret = UX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_USBX_Host_MEM_POOL */
#if (USE_MEMORY_POOL_ALLOCATION == 1)
  CHAR *pointer;

  /* Allocate the stack for crypto App thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       (CRYPTO_APP_STACK_SIZE * 2), TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the main App thread. */
  if (tx_thread_create(&cr_app_thread, "cr_app_thread", cr_app_thread_entry, 0,
                       pointer, (CRYPTO_APP_STACK_SIZE * 2), 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

#endif
  /* USER CODE END MX_USBX_Host_Init */

  return ret;
}

/**
  * @brief  Application_thread_entry .
  * @param  ULONG arg
  * @retval Void
  */
void  cr_app_thread_entry(ULONG arg)
{
  uint8_t exit = 0;

  /* disable cache to prevent cacheable instructions for plain and Cipher code */
  CACHE_Disable();

  /* Set font */
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 80, (uint8_t *)"On The Fly Decrypt and run from", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 100, (uint8_t *)"external memory (Ciphered Code)", CENTER_MODE);
  UTIL_LCD_DrawCircle(80, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(100, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(120, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(140, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(160, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);

  /* Crypt the code to be Preloaded in external ospi memory  */
  /* Init OCTOSPI */
  Ospi_Nor_Ctx[0].IsInitialized = OSPI_ACCESS_NONE;
  NOR_init.InterfaceMode = BSP_OSPI_NOR_OPI_MODE;
  NOR_init.TransferRate  = BSP_OSPI_NOR_STR_TRANSFER;
  BSP_OSPI_NOR_Init(0, &NOR_init);

  /* Erase external memory Block (64KByte)*/
  BSP_OSPI_NOR_Erase_Block(0, OSPI_CIPHER_CODE_START_OFFSET_ADD, BSP_OSPI_NOR_ERASE_64K);

  /* Initialize the variables for the data writing */
  Initialize_Data();

  /* Crypt code */
  Crypt_Code((uint32_t *)flash_ciphered_code_addr, CryptedCode);

  /* Preload external ospi memory with ciphred code into dedicated address*/
  BSP_OSPI_NOR_Write(0, (uint8_t *)CryptedCode, OSPI_CIPHER_CODE_START_OFFSET_ADD, max_size_cipher);

  /* Preload external ospi memory with plain code into dedicated address*/
  BSP_OSPI_NOR_Write(0, (uint8_t *)flash_plain_code_addr, OSPI_PLAIN_CODE_START_OFFSET_ADD, max_size_plain);

  /* Activate memory mapping */
  BSP_OSPI_NOR_EnableMemoryMappedMode(0);

  /* Crypt the code to be Preloaded in external flash  */
  Decrypt_Code();

  /* according to SysTick configuration within tx_initialize_low_level.s, _tx_timer_system_clock is incremented each 1 ms */
  tick_cipher1 = tx_time_get(); /* Current time in milliseconds */

  /* On The Fly Decrypt code from external ospi memory ----------------------*/
  ExecuteCipherCode();

  tick_cipher2 = tx_time_get();

  tick_cipher = tick_cipher2 - tick_cipher1 - AXES_OFFSET;

  width_cipher = tick_cipher/(1000/80);

  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(0, 80, (uint8_t *)"Run from external", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 100, (uint8_t *)"memory (Plain code)", CENTER_MODE);
  UTIL_LCD_DrawCircle(80, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(100, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(120, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(140, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DrawCircle(160, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);

  /* Execute the plain code from external ospi memory ------------------------*/

  tick_plain1 = tx_time_get();

  ExecutePlainCode();

  tick_plain2 = tx_time_get();

  tick_plain = tick_plain2 - tick_plain1 - AXES_OFFSET;

  width_plain = tick_plain/(1000/80);

  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  for(uint32_t i = 0; i < 6; i++)
  {
    UTIL_LCD_DrawHLine(40, 200 - 40*i, 200, UTIL_LCD_COLOR_LIGHTGRAY);
    UTIL_LCD_DrawVLine(240 - 40*i, 00, 200, UTIL_LCD_COLOR_LIGHTGRAY);
  }

  /* Set font */
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(5, 188, (uint8_t *)" 3,0", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(5, 148, (uint8_t *)" 3,5", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(5, 108, (uint8_t *)" 4,0", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(5, 68,  (uint8_t *)" 4,5", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(5, 28,  (uint8_t *)" 5,0", LEFT_MODE);

  /* result cannot be displayed in the screen */
  if(width_plain >= 200)
  {
    width_plain = 200;
    width_cipher = 200;
  }

  UTIL_LCD_FillRect(165, 200-width_plain, 30, width_plain, UTIL_LCD_COLOR_ST_PINK);
  UTIL_LCD_FillRect(85, 200-width_cipher, 30, width_cipher, UTIL_LCD_COLOR_ST_BLUE);
  UTIL_LCD_DisplayStringAt(80, 210, (uint8_t *)"Cipher     Plain", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(80, 222, (uint8_t *)"Code       Code", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(5, 8,  (uint8_t *)"Execution time in seconds", LEFT_MODE);
  if(width_plain == 200)
  {
    UTIL_LCD_DisplayStringAt(0, 88,  (uint8_t *)"Execution time takes", CENTER_MODE);
    UTIL_LCD_DisplayStringAt(0, 100,  (uint8_t *)"more than 5,5 seconds", CENTER_MODE);
  }
  else
  {
    UTIL_LCD_DrawHLine(80, 200-width_plain, 120, UTIL_LCD_COLOR_RED);
  }
  /* Display go back icon */
  BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);

  /* Wait a press to the return position */
  while (exit == 0U)
  {
    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(50);

      TsStateCallBack = 0 ;

      if((TS_State.TouchX > 200) && (TS_State.TouchY > 200))
      {
        exit = 1;
      }
    }
  }

  BSP_OSPI_NOR_DeInit(0);

  TsStateCallBack = 0;
  CACHE_Enable();
  tx_thread_terminate(&Display_thread_entry);
  tx_thread_reset(&Display_thread_entry);
  tx_thread_resume(&Display_thread_entry);
  tx_thread_suspend(&cr_app_thread);

}

/**
  * @brief  this code will be executed from external memory
  * @param  None
  * @retval None
  */

#if defined(__ICCARM__)
static complex * ExecuteCipherCode(void) @ ".ospi_ext_mem1"
#elif defined(__GNUC__)
static complex __attribute__((section(".ospi_ext_mem1"), noinline)) * ExecuteCipherCode(void)
#endif
{
  uint32_t iteration = 0;
  uint32_t k=0,i=0,j=0;
  uint32_t index = 0;

  do
  {
    for (k = 0; k<210; k++)
    {
      for (i = 0; i<8; i++)
      {
        for (j = 0; j<8; j++)
        {
          Tab1Clpx[i][j].imag = matrix1_0[i][j] * matrix2_0[i][j];
          Tab1Clpx[i][j].real = matrix1_0[i][j] / matrix2_0[i][j];
        }
      }
    }

    if(CRC_CipherCode(Key) == 0x71)
    {
      do
      {
        index++;
      }while(index != 10000);
    }

    index = 0;

    iteration++;
    if(iteration == 35)
    {
      UTIL_LCD_FillCircle(80, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 70)
    {
      UTIL_LCD_FillCircle(100, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 105)
    {
      UTIL_LCD_FillCircle(120, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 140)
    {
      UTIL_LCD_FillCircle(140, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 175)
    {
      UTIL_LCD_FillCircle(160, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
  } while(iteration != 210);

  return &Tab1Clpx[0][0];
}

#if defined(__ICCARM__)
static uint8_t CRC_PlainCode(uint32_t * keyin) @ ".ospi_ext_mem2"
#elif defined(__GNUC__)
static uint8_t __attribute__((section(".ospi_ext_mem2"), noinline)) CRC_PlainCode(uint32_t * keyin)
#endif
{
  uint8_t CRC7_POLY = 0x7;
  uint32_t key_strobe[4] = {0xAA55AA55, 0x3, 0x18, 0xC0};
  uint8_t  i = 0, j = 0, k = 0, crc = 0;
  uint32_t  keyval = 0;

  for (j = 0; j < 4; j++)
  {
    keyval = *(keyin+j);
    if (j == 0)
    {
      keyval ^= key_strobe[0];
    }
    else
    {
      keyval ^= (key_strobe[j] << 24) | (crc << 16) | (key_strobe[j] << 8) | crc;
    }

    for (i = 0, crc = 0; i < 32; i++)
    {
      k = ((crc >> 7) ^ (((keyval >> (31-i)))&(0xF))) & (1);
      crc <<= 1;
      if (k)
      {
        crc ^= CRC7_POLY;
      }
    }
    crc^=0x55;
  }

  return crc;
}


#if defined(__ICCARM__)
static uint8_t CRC_CipherCode(uint32_t * keyin) @ ".ospi_ext_mem1"
#elif defined(__GNUC__)
static uint8_t __attribute__((section(".ospi_ext_mem1"), noinline)) CRC_CipherCode(uint32_t * keyin)
#endif
{
  uint8_t CRC7_POLY = 0x7;
  uint32_t key_strobe[4] = {0xAA55AA55, 0x3, 0x18, 0xC0};
  uint8_t  i = 0, j = 0, k = 0, crc = 0;
  uint32_t  keyval = 0;

  for (j = 0; j < 4; j++)
  {
    keyval = *(keyin+j);
    if (j == 0)
    {
      keyval ^= key_strobe[0];
    }
    else
    {
      keyval ^= (key_strobe[j] << 24) | (crc << 16) | (key_strobe[j] << 8) | crc;
    }

    for (i = 0, crc = 0; i < 32; i++)
    {
    	k = ((crc >> 7) ^ (((keyval >> (31-i)))&(0xF))) & (1);
      crc <<= 1;
      if (k)
      {
        crc ^= CRC7_POLY;
      }
    }
    crc^=0x55;
  }

  return crc;
}

/**
  * @brief  this code will be executed from external memory
  * @param  None
  * @retval None
  */

#if defined(__ICCARM__)
static complex * ExecutePlainCode(void) @ ".ospi_ext_mem2"
#elif defined(__GNUC__)
static complex __attribute__((section(".ospi_ext_mem2"), noinline)) * ExecutePlainCode(void)
#endif
{
  uint32_t index = 0;
  uint32_t i=0, j=0, k=0;
  uint32_t iteration = 0;

  do
  {

    for (k = 0; k<210; k++)
    {
      for (i = 0; i<8; i++)
      {
        for (j = 0; j<8; j++)
        {
          Tab1Clpx[i][j].imag = matrix1_1[i][j] * matrix2_1[i][j];
          Tab1Clpx[i][j].real = matrix1_1[i][j] / matrix2_1[i][j];
        }
      }
    }

    if(CRC_PlainCode(Key) == 0x71)
    {
      do
      {
        index++;
      }while(index != 10000);
    }

    index = 0;

    iteration++;
    if(iteration == 35)
    {
      UTIL_LCD_FillCircle(80, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 70)
    {
      UTIL_LCD_FillCircle(100, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 105)
    {
      UTIL_LCD_FillCircle(120, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 140)
    {
      UTIL_LCD_FillCircle(140, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
    if(iteration == 175)
    {
      UTIL_LCD_FillCircle(160, 140, 6, UTIL_LCD_COLOR_ST_YELLOW);
    }
  } while(iteration != 210);

  return &Tab1Clpx[0][0];
}

/* OTFDEC functions -----------------------------------------------*/

/**
  * @brief  This function is used to crypt code present in Plain buffer and store it in Cipher buffer
  * @param  Plain: Plain buffer
  * @param  Cipher: Cipher buffer
  * @retval None
  */
static void Crypt_Code(uint32_t * Plain, uint32_t * Cipher)
{
  uint16_t j = 0;
  /*Init OTFDEC*/
  hotfdec_crypt.Instance = OTFDEC1;

  /* Enable OTFDEC1 clock */
  __HAL_RCC_OTFDEC1_CLK_ENABLE();

  /* Force the OTFDEC1 Periheral Reset */
  __HAL_RCC_OTFDEC1_FORCE_RESET();
  __HAL_RCC_OTFDEC1_RELEASE_RESET();

  HAL_OTFDEC_DeInit(&hotfdec_crypt);
  if (HAL_OTFDEC_Init(&hotfdec_crypt) != HAL_OK)
  {
    Error_Handler();
  }

  __HAL_OTFDEC_ENABLE_IT(&hotfdec_crypt, OTFDEC_ALL_INT);

  /* Set OTFDEC Mode */
  if (HAL_OTFDEC_RegionSetMode(&hotfdec_crypt, 0, OTFDEC_REG_MODE_INSTRUCTION_OR_DATA_ACCESSES) != HAL_OK)
  {
    Error_Handler();
  }

  /* Set OTFDEC Key */
  if (HAL_OTFDEC_RegionSetKey(&hotfdec_crypt, 0, Key)  != HAL_OK)
  {
    Error_Handler();
  }

  /* Retrieve Key CRC from OTFDEC Peripheral and compare it with the expected CRC computed by software */
  if ((uint8_t)(HAL_OTFDEC_RegionGetKeyCRC(&hotfdec_crypt, 0 )) !=  Ref_CRC_computation(Key))
  {
    Error_Handler();
  }

  /* Activate OTFDEC Encrypt */
  Config_crypt.Nonce[0]     = CIPHER_ZONE_NONCE0;
  Config_crypt.Nonce[1]     = CIPHER_ZONE_NONCE1;
  Config_crypt.StartAddress = CIPHER_ZONE__START_ADRESS;
  Config_crypt.EndAddress   = CIPHER_ZONE__END_ADRESS;
  Config_crypt.Version      = CIPHER_ZONE_FIRMWARE_VERSION;

  /* Enable Encrypt */
  HAL_OTFDEC_EnableEnciphering(&hotfdec_crypt);
  if (HAL_OTFDEC_RegionConfig(&hotfdec_crypt, 0, &Config_crypt, OTFDEC_REG_CONFIGR_LOCK_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /* At this level any writed data to MultiRange_ex address will be encrypted */
  ospi_mem_addr= (uint32_t *)(OCTOSPI1_BASE);
  for (j = 0; j < 512; j++)
  {
    /* writing the TX buffer in OTFDEC area range for that OSPI is not activated */
    *ospi_mem_addr = Plain[j];

    /* The OTFDEC should be responsible to crypt on the fly present data in the MultiRange_ex area which is the OTFDEC area */
    Cipher[j] = *ospi_mem_addr;
    ospi_mem_addr++;
  }

  /* Disable Encrypt */
  HAL_OTFDEC_DisableEnciphering(&hotfdec_crypt);

  /* Reset OTFDEC Periheral  */
  HAL_OTFDEC_DeInit(&hotfdec_crypt);
}

/**
  * @brief  This function is used to decrypt code present in external memory
  * @param  None
  * @retval None
  */
static void Decrypt_Code(void)
{
  /* Init OTFDEC */
  hotfdec_decrypt.Instance = OTFDEC1;
  HAL_OTFDEC_DeInit(&hotfdec_decrypt);
  if (HAL_OTFDEC_Init(&hotfdec_decrypt) != HAL_OK)
  {
    Error_Handler();
  }

  __HAL_OTFDEC_ENABLE_IT(&hotfdec_decrypt, OTFDEC_ALL_INT);

  /* Set OTFDEC Mode */
  if (HAL_OTFDEC_RegionSetMode(&hotfdec_decrypt, 0, OTFDEC_REG_MODE_INSTRUCTION_OR_DATA_ACCESSES) != HAL_OK)
  {
    Error_Handler();
  }

  /* Set OTFDEC Key */
  if (HAL_OTFDEC_RegionSetKey(&hotfdec_decrypt, 0, Key)  != HAL_OK)
  {
    Error_Handler();
  }

  /* Retrieve Key CRC from OTFDEC Peripheral and compare it with the expected CRC computed by software */
  if ((uint8_t)(HAL_OTFDEC_RegionGetKeyCRC(&hotfdec_decrypt, 0 )) !=  Ref_CRC_computation(Key))
  {
    Error_Handler();
  }

  /* Activate OTFDEC Encrypt */
  Config_decrypt.Nonce[0]     = CIPHER_ZONE_NONCE0;
  Config_decrypt.Nonce[1]     = CIPHER_ZONE_NONCE1;
  Config_decrypt.StartAddress = CIPHER_ZONE__START_ADRESS;
  Config_decrypt.EndAddress   = CIPHER_ZONE__END_ADRESS;
  Config_decrypt.Version      = CIPHER_ZONE_FIRMWARE_VERSION;

  /* Enable Decrypt */
  if (HAL_OTFDEC_RegionConfig(&hotfdec_decrypt, 0, &Config_decrypt, OTFDEC_REG_CONFIGR_LOCK_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is used to compare with the result of the computation provided by OTFDEC in KEYCRC bitfield after loading the keys in OTFDEC_RxKEYR registers..
  * @param  keyin
  * @retval crc
  */
static uint8_t Ref_CRC_computation(uint32_t * keyin)
{
  uint8_t CRC7_POLY = 0x7;
  uint32_t key_strobe[4] = {0xAA55AA55, 0x3, 0x18, 0xC0};
  uint8_t  i = 0, j = 0, k = 0, crc = 0;
  uint32_t  keyval = 0;

  for (j = 0; j < 4; j++)
  {
    keyval = *(keyin+j);
    if (j == 0)
    {
      keyval ^= key_strobe[0];
    }
    else
    {
      keyval ^= (key_strobe[j] << 24) | (crc << 16) | (key_strobe[j] << 8) | crc;
    }

    for (i = 0, crc = 0; i < 32; i++)
    {
    	k = ((crc >> 7) ^ (((keyval >> (31-i)))&(0xF))) & (1);
      crc <<= 1;
      if (k)
      {
        crc ^= CRC7_POLY;
      }
    }
    crc^=0x55;
  }

  return crc;
}

/**
  * Get cipher section size, get plain section size
  * Get flash ciphered code address, get flash plain code address
  * Initialize data to be used by Cipher and Plain Code:
  *
  */
static void Initialize_Data(void)
{
#if defined(__ICCARM__)
 max_size_cipher = __section_size(".ospi_ext_mem1_init");
 flash_ciphered_code_addr = (uint8_t *)(__section_begin(".ospi_ext_mem1_init"));
 max_size_plain = __section_size(".ospi_ext_mem2_init");
 flash_plain_code_addr = (uint8_t *)(__section_begin(".ospi_ext_mem2_init"));
 
#elif defined(__ARMCC_VERSION)
max_size_cipher = (uint32_t)(&Load$$OSPI_EXT_MEM1$$Length);
flash_ciphered_code_addr = (uint8_t *)(&Load$$OSPI_EXT_MEM1$$Base);
max_size_plain = (uint32_t)(&Load$$OSPI_EXT_MEM2$$Length);
flash_plain_code_addr= (uint8_t*)(&Load$$OSPI_EXT_MEM2$$Base) ;

#elif defined(__GNUC__)
 max_size_cipher = (uint32_t)(&_ospi_ext_mem1_init_length);
 flash_ciphered_code_addr = (uint8_t*)(&_ospi_ext_mem1_init_base) ;
 max_size_plain= (uint32_t)(&_ospi_ext_mem2_init_length);
 flash_plain_code_addr= (uint8_t*)(&_ospi_ext_mem2_init_base) ;
#endif

  BSP_OSPI_NOR_Write(0, (uint8_t *)matrix1, (uint32_t)(&matrix1_0 - OCTOSPI1_BASE),sizeof(matrix1));

  BSP_OSPI_NOR_Write(0, (uint8_t *)matrix2,(uint32_t)(&matrix2_0 - OCTOSPI1_BASE), sizeof(matrix2));

  BSP_OSPI_NOR_Write(0, (uint8_t *)matrix1,(uint32_t)(&matrix1_1 - OCTOSPI1_BASE), sizeof(matrix1));

  BSP_OSPI_NOR_Write(0, (uint8_t *)matrix1,(uint32_t)(&matrix2_1 - OCTOSPI1_BASE), sizeof(matrix2));
}

#undef __APP_CRYPTO_C
#endif
