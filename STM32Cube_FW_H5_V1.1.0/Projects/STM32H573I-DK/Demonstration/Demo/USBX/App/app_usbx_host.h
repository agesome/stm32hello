/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx_host.h
  * @author  MCD Application Team
  * @brief   USBX Host applicative header file
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
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_USBX_HOST_H__
#define __APP_USBX_HOST_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ux_api.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_hcd_stm32.h"
#include "ux_host_class_hid.h"
#include "ux_host_class_hid_mouse.h"
#include "app_azure_rtos_config.h"
#if defined(_TRACE)
#include "usbpd_trace.h"
#endif /* _TRACE */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#if defined(_TRACE)
#define DPM_USER_DEBUG_TRACE_SIZE       50u

#define USBH_UsrLog(...)  do {                                                             \
    char _str[DPM_USER_DEBUG_TRACE_SIZE];                                                  \
    uint8_t _size = snprintf(_str, DPM_USER_DEBUG_TRACE_SIZE, __VA_ARGS__);                \
    if (_size < DPM_USER_DEBUG_TRACE_SIZE)                                                 \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, strlen(_str));              \
    else                                                                                   \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, DPM_USER_DEBUG_TRACE_SIZE); \
  } while(0)

#define  USBH_ErrLog(...)   do {                                                           \
    char _str[DPM_USER_DEBUG_TRACE_SIZE];                                                  \
    uint8_t _size = snprintf(_str, DPM_USER_DEBUG_TRACE_SIZE, __VA_ARGS__);                \
    if (_size < DPM_USER_DEBUG_TRACE_SIZE)                                                 \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, strlen(_str));              \
    else                                                                                   \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, 0, 0, (uint8_t*)_str, DPM_USER_DEBUG_TRACE_SIZE); \
  } while(0)
#else
#define USBH_UsrLog(...)   printf(__VA_ARGS__);\
                           printf("\n");

#define USBH_ErrLog(...)   printf("ERROR: ") ;\
                           printf(__VA_ARGS__);\
                           printf("\n");
#endif /* _TRACE */
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
UINT MX_USBX_Host_Init(VOID *memory_ptr);

/* USER CODE BEGIN EFP */
UINT  App_USBX_Host_Init(void);
UINT  App_USBX_Host_DeInit(void);
void  usbx_host_app_thread_entry(ULONG arg);
void  ucpd_app_thread_entry(ULONG arg);
void  hid_mouse_thread_entry(ULONG arg);
void  MenuUSBPD_thread_entry(ULONG arg);
UINT  ux_host_event_callback(ULONG event, UX_HOST_CLASS *Current_class, VOID *Current_instance);
VOID  ux_host_error_callback(UINT system_level, UINT system_context, UINT error_code);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* USER CODE BEGIN 1 */

typedef enum
{
LEFT_Button_Pressed=1,
RIGHT_Button_Pressed,
MIDDLE_Button_Pressed,
Button_Reset,
} Button_State;


typedef enum
{
  USB_VBUS_FALSE = 0,
  USB_VBUS_TRUE,
} USB_VBUS_State;


typedef enum
{
  Mouse_Device = 1,
  Keyboard_Device,
  Unknown_Device,
} HID_Device_Type;


typedef enum
{
  Device_disconnected = 1,
  Device_connected,
  No_Device,
} Device_state;

typedef struct
{
  HID_Device_Type Device_Type;
  Device_state Dev_state;
} ux_app_devInfotypeDef;

/* USER CODE BEGIN 1 */
typedef enum
{
  STOP_USB_HOST = 1,
  START_USB_HOST,
} USB_HOST_MODE_STATE;


typedef struct
{
  uint8_t HostState;
  uint8_t DeviceState;
} USB_DRD_ModeMsg_TypeDef;
/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __APP_USBX_HOST_H__ */
