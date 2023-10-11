/**
  ******************************************************************************
  * @file    fwu.c
  * @author  MCD Application Team
  * @brief   NS FWU program
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
#include "fwu.h"
#include "psa/client.h"
#include "com.h"
#include "common.h"
#include "ymodem.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ARM_DRIVER_OK 0 /* < Operation succeeded */
#define IMAGE_SIZE_MAX 0xA0000
#define FLASH0_PROG_UNIT 0x10
#define IMAGE_ID(slot,type) (((uint8_t)slot) | (type << 8));

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t m_uFileSizeYmodem = 0U;    /* !< Ymodem File size*/
static uint32_t m_uNbrBlocksYmodem = 0U;   /* !< Ymodem Number of blocks*/
static uint32_t m_uPacketsReceived = 0U;   /* !< Ymodem packets received*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void FW_APP_FWU_PrintMenu(void);
static void FW_UPDATE_APP_IMAGE(psa_image_id_t image_id);
static HAL_StatusTypeDef FW_UPDATE_DownloadNewFirmware(uint32_t uMaxFwSize, psa_image_id_t imageId);
static void FW_QUERY_ALL(void);
static void FW_VALIDATION(psa_image_id_t image_id);
static void FW_ABORT(psa_image_id_t image_id);


/**
  * @brief  Display the FWU Menu choices on HyperTerminal
  * @param  None.
  * @retval None.
  */
void FW_APP_FWU_PrintMenu(void)
{
  (void)printf("\r\n================= Firmware Update Menu ===================\r\n\n");
  (void)printf("  Applications Status ---------------------------------- 1\r\n\n");
  (void)printf("  Installation Application ----------------------------- 2\r\n\n");
  (void)printf("  Download Non-Secure App ------------------------------ 3\r\n\n");
  (void)printf("  Validation Non-Secure App ---------------------------- 4\r\n\n");
  (void)printf("  Abort Download Non Secure App ------------------------ 5\r\n\n");
  (void)printf("  Download Secure Manager ------------------------------ 6\r\n\n");
  (void)printf("  Validation Secure Manager ---------------------------- 7\r\n\n");
  (void)printf("  Abort Download Secure Manager ------------------------ 8\r\n\n");
  (void)printf("  Download STuRoT -------------------------------------- 9\r\n\n");
  (void)printf("  Abort Download STuRoT -------------------------------- A\r\n\n");
#if NB_MODULE > 0
  (void)printf("  Download Module 0 ------------------------------------ B\r\n\n");
  (void)printf("  Validation Module 0 ---------------------------------- C\r\n\n");
  (void)printf("  Abort Download Module 0 ------------------------------ D\r\n\n");
#endif /* NB_MODULE > 0 */
  (void)printf("  Previous menu ---------------------------------------- x\r\n\n");
  (void)printf("  Selection :\r\n\n");
  (void)printf("  ");
}

/**
  * @brief  Run the FWU example
  * @param  None.
  * @retval None.
  */
void FW_APP_FWU_Run(void)
{
  uint8_t key = 0U;
  uint8_t exit = 0U;

  psa_status_t psa_status;
  uint32_t image_id;

  /* Print Menu message*/
  FW_APP_FWU_PrintMenu();

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
        case '1':
          /* Display status of all code images (active and download slot) */
          FW_QUERY_ALL();
          break;
        case '2':
          /* Installation of images in pending install (swap) */
          (void)printf("\nPSA API tested : \r\n");
          (void)printf("psa_fwu_request_reboot() \r\n");
          psa_status = psa_fwu_request_reboot();
          (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
          break;
        case '3':
          /* Download Non Secure image in download slot */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_NONSECURE);
          FW_UPDATE_APP_IMAGE(image_id);
          break;
        case '4':
          /* Confirm Non Secure image */
          image_id =IMAGE_ID(PSA_FWU_SLOT_ID_ACTIVE, PSA_FWU_TYPE_ID_NONSECURE);
          FW_VALIDATION(image_id);
          break;
        case '5':
          /* Erase Non Secure Secondary slot after the case '3' only */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_NONSECURE);
          FW_ABORT(image_id);
          break;
        case '6':
          /* Download Secure Manager image in download slot */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_SECURE);
          FW_UPDATE_APP_IMAGE(image_id);
          break;
        case '7':
          /* Confirm Secure Manager image */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_ACTIVE, PSA_FWU_TYPE_ID_SECURE);
          FW_VALIDATION(image_id);
          break;
        case '8':
          /* Erase Secure Manager Secondary slot after the case '6' only */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_SECURE);
          FW_ABORT(image_id);
          break;
        case '9':
          /* Download STuRoT image in download slot */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_BL);
          FW_UPDATE_APP_IMAGE(image_id);
          break;
        case 'a':
        case 'A':
          /* Erase STuRoT Secondary slot after the case '9' only */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_BL);
          FW_ABORT(image_id);
          break;
#if NB_MODULE > 0
        case 'b':
        case 'B':
          /* Download Module0 image in download slot */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_MODULE_0);
          FW_UPDATE_APP_IMAGE(image_id);
          break;
        case 'c':
        case 'C':
          /* Confirm Module0 image */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_ACTIVE, PSA_FWU_TYPE_ID_MODULE_0);
          FW_VALIDATION(image_id);
          break;
        case 'd':
        case 'D':
          /* Erase Module0 Secondary slot after the case 'C''c' only */
          image_id = IMAGE_ID(PSA_FWU_SLOT_ID_DL, PSA_FWU_TYPE_ID_MODULE_0);
          FW_ABORT(image_id);
          break;
#endif /* NB_MODULE > 0 */

        case 'X' :
        case 'x' :
          exit = 1U;
          break;

        default :
          (void)printf("\rInvalid Number !\r\n");
          break;
      }

      if (exit == 0U)
      {
        /* Print Main Menu message */
        FW_APP_FWU_PrintMenu();
      }
    }
  }
}

/**
  * @brief  print image info
  * @param  psa_image_info_t info
  * @retval None.
  */
void print_image_info(psa_image_info_t info, psa_status_t psa_status)
{
  if(psa_status == PSA_SUCCESS)
  {
    (void)printf("[FU Client] State = 0x%x\r\n", info.state);
    (void)printf("[FU Client] Image ID = 0x%x\r\n", (int)info.image_id);
    (void)printf("[FU Client] Version (Major.Minor.Revision) = %d.%d.%d\r\n", \
                  info.version.iv_major, info.version.iv_minor, info.version.iv_revision);
    (void)printf("[FU Client] Size Max = 0x%x\r\n", info.staging.max_size);
  }
}

/**
  * @brief  Run FW Update process.
  * @param  psa_image_id_t image_id
  * @retval HAL Status.
  */
static void FW_UPDATE_APP_IMAGE(psa_image_id_t image_id)
{
  HAL_StatusTypeDef ret;

  /* Print PSA API info */
  (void)printf("PSA API tested : \r\n");
  (void)printf("psa_fwu_write() \r\n");
  (void)printf("psa_fwu_install() \r\n");
  (void)printf("psa_fwu_query() \r\n");

  /* Print Firmware Update welcome message */
  (void)printf("Download Image\r\n");

  /* Download new firmware image*/
  ret = FW_UPDATE_DownloadNewFirmware(IMAGE_SIZE_MAX, image_id);

  if (ret == HAL_OK)
  {
    (void)printf("  -- Image correctly downloaded \r\n\n");
    HAL_Delay(1000U);
    (void)printf("\r\nTEST PASSED\r\n");
  }
  else
  {
    (void)printf("\r\nTEST FAILED : %d \r\n", ret);
  }
}

/**
  * @brief Download a new Firmware from the host.
  * @retval HAL status
  */
static HAL_StatusTypeDef FW_UPDATE_DownloadNewFirmware(uint32_t uMaxFwSize, psa_image_id_t imageId)
{
  HAL_StatusTypeDef ret;
  COM_StatusTypeDef e_result;

  uint32_t u_fw_size;
  psa_status_t status;
  psa_image_id_t dependency_uuid;
  psa_image_version_t dependency_version;
  psa_image_info_t info;

  (void)printf("  -- Send Firmware \r\n\n");

  /* Download binary */
  (void)printf("  -- -- File> Transfer> YMODEM> Send \t\n");

  /*Init of Ymodem*/
  Ymodem_Init();

  u_fw_size = uMaxFwSize;
  /*Receive through Ymodem*/
  e_result = Ymodem_Receive(&u_fw_size, imageId);
  (void)printf("\r\n\n");

  if ((e_result == COM_OK))
  {
    (void)printf("  -- -- Programming Completed Successfully!\r\n\n");
    (void)printf("  -- -- Bytes: %u\r\n\n", (int)u_fw_size);
    ret = HAL_OK;
    status = psa_fwu_install(imageId, &dependency_uuid, &dependency_version);

    /* In the currently implementation, image verification is deferred to
     * reboot, so PSA_SUCCESS_REBOOT is returned when success.
     */
    if ((status != PSA_SUCCESS_REBOOT) &&
        (status != PSA_ERROR_DEPENDENCY_NEEDED))
    {
      (void)printf("\rInstall should not fail after write\r\n\n");
      ret = HAL_ERROR;
    }

    /* Query the staging image. */
    if (psa_fwu_query(imageId, &info) != PSA_SUCCESS)
    {
      (void)printf("\rQuery should success\r\n\n");
      ret = HAL_ERROR;
    }

    /* Check the image state. */
    if ((status == PSA_SUCCESS_REBOOT) &&
        (info.state != (uint8_t)PSA_IMAGE_REBOOT_NEEDED))
    {
      (void)printf("\rImage should be in REBOOT_NEEDED state if PSA_SUCCESS_REBOOT is returned in install\r\n\n");
      ret = HAL_ERROR;
    }
  }
  else if (e_result == COM_ABORT)
  {
    (void)printf("  -- -- !!Aborted by user!!\r\n\n");
    (void)COM_Flush();
    ret = HAL_ERROR;
  }
  else
  {
    (void)printf("  -- -- !!Error during file download!!\r\n\n");
    ret = HAL_ERROR;
    HAL_Delay(500U);
    (void)COM_Flush();
  }

  return ret;
}


/**
  * @}
  */

/** @defgroup FW_UPDATE_Callback_Functions Callback Functions
  * @{
  */

/**
  * @brief  Ymodem Header Packet Transfer completed callback.
  * @param  uFileSize Dimension of the file that will be received (Bytes).
  * @retval None
  */
HAL_StatusTypeDef Ymodem_HeaderPktRxCpltCallback(psa_image_id_t imageId, uint32_t uOffset, uint32_t uFileSize)
{
  UNUSED(uOffset);
  UNUSED(imageId);
  /*Reset of the ymodem variables */
  m_uFileSizeYmodem = 0U;
  m_uPacketsReceived = 0U;
  m_uNbrBlocksYmodem = 0U;

  /*Filesize information is stored*/
  m_uFileSizeYmodem = uFileSize;

  /* compute the number of 1K blocks */
  m_uNbrBlocksYmodem = (m_uFileSizeYmodem + (PACKET_1K_SIZE - 1U)) / PACKET_1K_SIZE;

  /* NOTE : delay inserted for Ymodem protocol*/
  HAL_Delay(1000);
  return HAL_OK;
}

extern uint32_t total_size_received;
/**
  * @brief  Ymodem Data Packet Transfer completed callback.
  * @param  pData Pointer to the buffer.
  * @param  uSize Packet dimension (Bytes).
  * @retval None
  */
HAL_StatusTypeDef Ymodem_DataPktRxCpltCallback(uint8_t *pData, psa_image_id_t imageId, uint32_t uOffset, uint32_t uSize)
{
  int32_t ret;
  uint32_t size = uSize;
  m_uPacketsReceived++;
  psa_status_t status;

  /*Increase the number of received packets*/
  if (m_uPacketsReceived == m_uNbrBlocksYmodem) /*Last Packet*/
  {
    /*Extracting actual payload from last packet*/
    if ((m_uFileSizeYmodem % PACKET_1K_SIZE) == 0U)
    {
      /* The last packet must be fully considered */
      size = PACKET_1K_SIZE;
    }
    else
    {
      /* The last packet is not full, drop the extra bytes */
      size = m_uFileSizeYmodem - ((uint32_t)(m_uFileSizeYmodem / PACKET_1K_SIZE) * PACKET_1K_SIZE);
    }

    m_uPacketsReceived = 0U;
  }

  /* Write the data block with block_offset 0. */
  status = psa_fwu_write(imageId, uOffset, pData, size);
  if (status != PSA_SUCCESS)
  {
    (void)printf("Write should not fail");
    return HAL_ERROR;
  }
  else
  {
    ret = ARM_DRIVER_OK;
  }
  if (ret != ARM_DRIVER_OK)
  {
    /*Reset of the ymodem variables */
    m_uFileSizeYmodem = 0U;
    m_uPacketsReceived = 0U;
    m_uNbrBlocksYmodem = 0U;
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  retrieve images status in active and download slot
            (Non Secure, Secure Manager, STuRoT and Module0)
  * @param  pData Pointer to the buffer.
  * @param  uSize Packet dimension (Bytes).
  * @retval None
  */

static void FW_QUERY_ALL(void)
{
  psa_status_t psa_status;
  psa_image_info_t info  = { 0 };
  uint32_t image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_ACTIVE) | (PSA_FWU_TYPE_ID_NONSECURE << 8));

  (void)printf("\n Non-Secure Active Slot : \r\n");
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);

  (void)printf("\n Non-Secure Download Slot : \r\n");
  image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_DL) | (PSA_FWU_TYPE_ID_NONSECURE << 8));
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);

  (void)printf("\n Secure Manager Active Slot : \r\n");
  image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_ACTIVE) | (PSA_FWU_TYPE_ID_SECURE << 8));
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);

  (void)printf("\n Secure Manager Download Slot : \r\n");
  image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_DL) | (PSA_FWU_TYPE_ID_SECURE << 8));
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);

  (void)printf("\n STuRoT Active Slot : \r\n");
  image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_ACTIVE) | (PSA_FWU_TYPE_ID_BL << 8));
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);

  (void)printf("\n STuRoT Download Slot : \r\n");
  image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_DL) | (PSA_FWU_TYPE_ID_BL << 8));
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);

#if NB_MODULE > 0
  (void)printf("\n Module 0 Active Slot : \r\n");
  image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_ACTIVE) | (PSA_FWU_TYPE_ID_MODULE_0 << 8));
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);

  (void)printf("\n Module 0 Download Slot : \r\n");
  image_id_active = (((uint8_t)PSA_FWU_SLOT_ID_DL) | (PSA_FWU_TYPE_ID_MODULE_0 << 8));
  psa_status = psa_fwu_query(image_id_active, &info);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
  print_image_info(info, psa_status);
#endif /* NB_MODULE > 0 */

}

/**
  * @brief  Confirm updated image
  * @param  psa_image_id_t image_id of the image to confirm
  * @retval None
  */
static void FW_VALIDATION(psa_image_id_t image_id)
{
  psa_status_t psa_status;
  psa_image_info_t info  = { 0 };

  /* Print PSA API */
  (void)printf("\nPSA API tested : \r\n");
  (void)printf("psa_fwu_accept() \r\n");
  (void)printf("psa_fwu_query() \r\n");

  (void)psa_fwu_query(image_id, &info);
  (void)printf(" \rState before validation : 0x%x \r\n", info.state);

  psa_status = psa_fwu_accept(image_id);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);

  (void)psa_fwu_query(image_id, &info);
  (void)printf("\rState after validation : 0x%x \r\n", info.state);
}

/**
  * @brief  Abort downloaded image
  * @param  psa_image_id_t image_id of the image to abort
  * @retval None
  */
static void FW_ABORT(psa_image_id_t image_id)
{
  psa_status_t psa_status;

  /* Print PSA API */
  (void)printf("\nPSA API tested : \r\n");
  (void)printf("psa_fwu_abort() \r\n");

  psa_status = psa_fwu_abort(image_id);
  (psa_status == PSA_SUCCESS) ? (void)printf("\rTEST PASSED\r\n") : (void)printf("\rTEST FAILED:%d\r\n", (int)psa_status);
}

