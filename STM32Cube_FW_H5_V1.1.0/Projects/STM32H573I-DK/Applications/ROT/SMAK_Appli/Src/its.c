/**
  ******************************************************************************
  * @file    its.c
  * @author  MCD Application Team
  * @brief   NS ITS program
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
#include "com.h"
#include "its.h"
#include "psa/client.h"
#include "psa/internal_trusted_storage.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void FW_APP_ITS_PrintMenu(void);

/**
  * @brief  Display the ITS Menu choices on HyperTerminal
  * @param  None.
  * @retval None.
  */
void FW_APP_ITS_PrintMenu(void)
{
  (void)printf("\r\n============= Internal Trusted Storage Menu ==============\r\n\n");
  (void)printf("  psa_its_set() ---------------------------------------- 1\r\n\n");
  (void)printf("  psa_its_get() ---------------------------------------- 2\r\n\n");
  (void)printf("  psa_its_get_info() ----------------------------------- 3\r\n\n");
  (void)printf("  psa_its_remove() ------------------------------------- 4\r\n\n");
  (void)printf("  Previous menu ---------------------------------------- x\r\n\n");
  (void)printf("  Selection :\r\n\n");
  (void)printf("  ");
}

/**
  * @brief  Run the ITS example
  * @param  None.
  * @retval None.
  */
void FW_APP_ITS_Run(void)
{
  uint8_t key = 0U;
  uint8_t exit = 0U;

  psa_status_t psa_status;
  size_t data_length = 16U;
  uint32_t data[4];
  uint32_t dataout[4];
  data[0] = 0xAABBCCDDU;
  data[1] = 0xEEFF0011U;
  data[2] = 0x22334455;
  data[3] = 0x66778899;
  psa_storage_create_flags_t flags = PSA_STORAGE_FLAG_NO_CONFIDENTIALITY;
  struct psa_storage_info_t  storage_info;

  /* Print Menu message*/
  FW_APP_ITS_PrintMenu();

  while (exit == 0U)
  {
    /* Clean the input path */
    (void)COM_Flush();

    /* Receive key */
    if (COM_Receive(&key, 1U, RX_TIMEOUT) == HAL_OK)
    {
      (void)printf("%c\r\n", key);
      switch (key)
      {
        case '1' :
          psa_status = psa_its_set(0x30, data_length, &data, flags);
          if (psa_status == PSA_SUCCESS)
          {
            (void)printf("\r\nTEST PASSED\r\n");
            (void)printf("\nWritten Data :\r\n");
            for (int32_t i = 0; i < 4; i++)
            {
              (void)printf("%x\r\n", (int)data[i]);
            }
          }
          else
          {
            (void)printf("\r\nTEST FAILED : %d\r\n", (int)psa_status);
          }
          break;

        case '2' :
          psa_status = psa_its_get(0x30, 0u, data_length, (void *)&dataout, &data_length);
          ((psa_status == PSA_SUCCESS) &&
           (data[0] == dataout[0]) &&
           (data[1] == dataout[1]) &&
           (data[2] == dataout[2]) &&
           (data[3] == dataout[3])) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
          if (psa_status == PSA_SUCCESS)
          {
            (void)printf("\nData :\r\n");
            for (int32_t i = 0; i < 4; i++)
            {
              (void)printf("%x\r\n", (int)dataout[i]);
            }
          }
          break;

        case '3' :
          psa_status = psa_its_get_info(0x30, &storage_info);
          (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
          if (psa_status == PSA_SUCCESS)
          {
            (void)printf("\nStorage info capacity 0x%x\r\n", storage_info.capacity);
            (void)printf("Storage info size     0x%x\r\n", storage_info.size);
            (void)printf("Storage info flags    0x%x\r\n", (int)storage_info.flags);
          }
          break;

        case '4' :
          psa_status = psa_its_remove(0x30);
          (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
          break;

        case 'X' :
        case 'x' :
          exit = 1U;
          break;

        default:
          (void)printf("\r\nInvalid Number !\r\n");
          break;
      }

      if (exit == 0U)
      {
        /* Print Main Menu message */
        FW_APP_ITS_PrintMenu();
      }
    }
  }
}
