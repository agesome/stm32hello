/**
  ******************************************************************************
  * @file    audio_recplay.c
  * @author  MCD Application Team
  * @brief   Audio recorder/player implementation
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
#include "audio_recplay.h"

/* Private typedef -----------------------------------------------------------*/
#define PDM_SAMPLES_AT_EACH_CALL 16*2*20
#define AUDIO_REC_BUFFER_SIZE  (PDM_SAMPLES_AT_EACH_CALL * 16)
#define AUDIO_PLAY_BUFFER_SIZE (PDM_SAMPLES_AT_EACH_CALL * 4)
/* Private constants ---------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
uint8_t                      RecBuff[AUDIO_REC_BUFFER_SIZE];
uint16_t                     PlayBuff[AUDIO_PLAY_BUFFER_SIZE];
uint32_t                     RecHalfBuffCplt  = 0;
uint32_t                     RecBuffCplt      = 0;
uint32_t                     ChannelsNumber;
__IO uint32_t                PauseResume = 0;
__IO uint32_t                StopStart = 0;
uint32_t                     playbackPtr = 0;
uint32_t                     PlaybackStarted;

extern __IO uint8_t TsStateCallBack;
extern TS_State_t TS_State;
extern TX_THREAD                       Display_thread_entry;
extern TX_THREAD                       au_app_thread;
/* PDM filters params */
static PDM_Filter_Handler_t            PDM_FilterHandler[2];
static PDM_Filter_Config_t             PDM_FilterConfig[2];

/* Private function prototypes -----------------------------------------------*/
static int32_t Playback_Init(void);
static int32_t Record_Init(void);
static int32_t BSP_AUDIO_IN_PDMToPCM_Init(uint32_t Instance, uint32_t AudioFreq, uint32_t ChnlNbrIn, uint32_t ChnlNbrOut);

/* Exported functions --------------------------------------------------------*/
void Audio_Recplay_Demo(void)
{
  uint32_t i;
  Point     triangle1[3] = {{150, 100}, {190, 120}, {150, 140}};

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  /* Initialize User button */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  /* Set the display font */
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_FillCircle(170, 120, 35, UTIL_LCD_COLOR_DARKBLUE);
  UTIL_LCD_FillRect(150, 100, 15, 40, UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillRect(175, 100, 15, 40, UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_FillCircle(70, 120, 35, UTIL_LCD_COLOR_DARKBLUE);
  UTIL_LCD_FillRect(50, 100, 40, 40, UTIL_LCD_COLOR_RED);
  UTIL_LCD_DisplayStringAt(0, 10, (uint8_t *)"AUDIO PDM REC/PLAY", LEFT_MODE);
  BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);

  ChannelsNumber = 2;
  /* Reset global variable */
  PlaybackStarted = 0;
  RecBuffCplt = 0;
  RecHalfBuffCplt = 0;

  /* Initialize record */
  Record_Init();

  /* Initialize playback */
  Playback_Init();

  BSP_AUDIO_IN_PDMToPCM_Init(1, AUDIO_FREQUENCY_16K, ChannelsNumber, ChannelsNumber);
  HAL_Delay(100);

  /* Start record */
  BSP_AUDIO_IN_RecordPDM(1, (uint8_t *) RecBuff, AUDIO_REC_BUFFER_SIZE);

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
  /* Set the display font */
  UTIL_LCD_SetFont(&Font24);

  /* Start loopback */
  while(1)
  {
    if (RecHalfBuffCplt == 1)
    {
      /* Store values on Play buff */
      for(i = 0; i < ChannelsNumber; i++)
      {
        PDM_Filter(&RecBuff[i], &PlayBuff[playbackPtr + i], &PDM_FilterHandler[i]);
      }
      playbackPtr += PDM_SAMPLES_AT_EACH_CALL;
      if(playbackPtr >= AUDIO_PLAY_BUFFER_SIZE)
      {
        playbackPtr = 0;
      }

      RecHalfBuffCplt = 0;
    }
    if (RecBuffCplt == 1)
    {
      /* Store values on Play buff */
      for(i = 0; i < ChannelsNumber; i++)
      {
        PDM_Filter(&RecBuff[(AUDIO_REC_BUFFER_SIZE / 2) + i], &PlayBuff[playbackPtr + i], &PDM_FilterHandler[i]);
      }
      playbackPtr += PDM_SAMPLES_AT_EACH_CALL;
      if(playbackPtr >= AUDIO_PLAY_BUFFER_SIZE)
      {
        playbackPtr = 0;
      }

      if ((PlaybackStarted == 0) && (playbackPtr == AUDIO_PLAY_BUFFER_SIZE/2))
      {
        if (BSP_ERROR_NONE != BSP_AUDIO_OUT_Play(0, (uint8_t *) PlayBuff, AUDIO_PLAY_BUFFER_SIZE*2))
        {
          Error_Handler();
        }
        UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"RECORDING/PLAYING", CENTER_MODE);
        PlaybackStarted = 1;
      }

      RecBuffCplt = 0;
    }

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;
      /* Pause */
      if ((TS_State.TouchX > 140) && (TS_State.TouchX < 200)&&(TS_State.TouchY > 90) && (TS_State.TouchY < 150) && (PauseResume == 0))
      {
        UTIL_LCD_FillCircle(170, 120, 35, UTIL_LCD_COLOR_DARKBLUE);
        UTIL_LCD_FillPolygon(triangle1, 3, UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"     PAUSED      ", CENTER_MODE);

        /* Pause record and stop playback */
        BSP_AUDIO_OUT_Stop(0);

        BSP_AUDIO_IN_Pause(1);

        /* Wait a little delay for pending dma */
        HAL_Delay(100);
        /* Reset global variable */
        PlaybackStarted = 0;
        RecBuffCplt = 0;
        RecHalfBuffCplt = 0;
        PauseResume = 1;
        TS_State.TouchX = 0;
        TS_State.TouchY = 0;
      }
      /* Resume */
      else if ((TS_State.TouchX > 140) && (TS_State.TouchX < 200)&&(TS_State.TouchY > 90) && (TS_State.TouchY < 150) && (PauseResume == 1))
      {
        UTIL_LCD_FillCircle(170, 120, 35, UTIL_LCD_COLOR_DARKBLUE);
        UTIL_LCD_FillRect(150, 100, 15, 40, UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_FillRect(175, 100, 15, 40, UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"RECORDING/PLAYING", CENTER_MODE);

        /* Resume record */
        BSP_AUDIO_IN_Resume(1);

        PauseResume = 0;
        TS_State.TouchX = 0;
        TS_State.TouchY = 0;
      }
      /* Stop */
      else if ((TS_State.TouchX > 40) && (TS_State.TouchX < 100)&&(TS_State.TouchY > 90) && (TS_State.TouchY < 150) && (StopStart == 0))
      {
        UTIL_LCD_FillCircle(70, 120, 35, UTIL_LCD_COLOR_DARKBLUE);
        UTIL_LCD_FillRect(50, 100, 40, 40, UTIL_LCD_COLOR_GREEN);
        UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"     STOPPED      ", CENTER_MODE);

        /* Stop record and stop playback */
        BSP_AUDIO_OUT_Stop(0);
        BSP_AUDIO_IN_Stop(1);

        /* Wait a little delay for pending dma */
        HAL_Delay(100);

        /* Reset global variable */
        PlaybackStarted = 0;
        RecBuffCplt = 0;
        RecHalfBuffCplt = 0;
        playbackPtr = 0;

        StopStart = 1;
        TS_State.TouchX = 0;
        TS_State.TouchY = 0;
      }
      /* Start */
      else if ((TS_State.TouchX > 40) && (TS_State.TouchX < 100)&&(TS_State.TouchY > 90) && (TS_State.TouchY < 150) && (StopStart == 1))
      {
        UTIL_LCD_FillCircle(70, 120, 35, UTIL_LCD_COLOR_DARKBLUE);
        UTIL_LCD_FillRect(50, 100, 40, 40, UTIL_LCD_COLOR_RED);
        UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"RECORDING/PLAYING", CENTER_MODE);
        /* Restart record */
        BSP_AUDIO_IN_RecordPDM(1, (uint8_t *) RecBuff, AUDIO_REC_BUFFER_SIZE);

        StopStart = 0;
        TS_State.TouchX = 0;
        TS_State.TouchY = 0;
      }
      /* De-Init */
      else if ((TS_State.TouchX > 200) && (TS_State.TouchY < 40))
      {
        /* Stop record and stop playback */
        BSP_AUDIO_OUT_Stop(0);
        BSP_AUDIO_IN_Stop(1);

        /* De initialize record and stop playback */
        BSP_AUDIO_OUT_DeInit(0);
        BSP_AUDIO_IN_DeInit(1);

        TsStateCallBack = 0;
        tx_thread_terminate(&Display_thread_entry);
        tx_thread_reset(&Display_thread_entry);
        tx_thread_resume(&Display_thread_entry);/* back touch */
        tx_thread_suspend(&au_app_thread);
      }
    }
  }
}

/**
  * @brief  Record initialization
  * @param  None
  * @retval None
  */
static int32_t Record_Init(void)
{
  BSP_AUDIO_Init_t AudioInit;
  uint32_t         GetData;
  int32_t result = 0;

  /* Test of state */
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetState(1, &GetData))  result++;
  if (GetData != AUDIO_IN_STATE_RESET) result++;
  AudioInit.Device        = AUDIO_IN_DEVICE_DIGITAL_MIC;
  AudioInit.SampleRate    = AUDIO_FREQUENCY_16K;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_8B;
  AudioInit.ChannelsNbr   = ChannelsNumber;
  AudioInit.Volume        = 80; /* Not used */

  if (BSP_ERROR_NONE != BSP_AUDIO_IN_Init(1, &AudioInit)) result++;

  return result;
}

/**
  * @brief  Playback initialization
  * @param  None
  * @retval None
  */
static int32_t Playback_Init(void)
{
  BSP_AUDIO_Init_t AudioInit;
  uint32_t         GetData;
  int32_t result = 0;

  /* Test of state */
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetState(1, &GetData)) result++;
  if (GetData != AUDIO_IN_STATE_STOP) result++;

  AudioInit.Device        = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioInit.SampleRate    = AUDIO_FREQUENCY_16K;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioInit.ChannelsNbr   = ChannelsNumber;
  AudioInit.Volume        = 80;

  if (BSP_ERROR_NONE != BSP_AUDIO_OUT_Init(0, &AudioInit)) result++;

  return result;
}

/**
  * @brief  Initialize the PDM library.
  * @param Instance    AUDIO IN Instance
  * @param  AudioFreq  Audio sampling frequency
  * @param  ChnlNbrIn  Number of input audio channels in the PDM buffer
  * @param  ChnlNbrOut Number of desired output audio channels in the  resulting PCM buffer
  * @retval BSP status
  */
static int32_t BSP_AUDIO_IN_PDMToPCM_Init(uint32_t Instance, uint32_t AudioFreq, uint32_t ChnlNbrIn, uint32_t ChnlNbrOut)
{
  uint32_t index = 0;

  if(Instance != 1U)
  {
    return BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Enable CRC peripheral to unlock the PDM library */
    __HAL_RCC_CRC_CLK_ENABLE();

    for(index = 0; index < ChnlNbrIn; index++)
    {
      /* Init PDM filters */
      PDM_FilterHandler[index].bit_order  = PDM_FILTER_BIT_ORDER_MSB;
      PDM_FilterHandler[index].endianness = PDM_FILTER_ENDIANNESS_LE;
      PDM_FilterHandler[index].high_pass_tap = 2122358088;
      PDM_FilterHandler[index].out_ptr_channels = ChnlNbrOut;
      PDM_FilterHandler[index].in_ptr_channels  = ChnlNbrIn;
      PDM_Filter_Init((PDM_Filter_Handler_t *)(&PDM_FilterHandler[index]));

      /* PDM lib config phase */
      PDM_FilterConfig[index].output_samples_number = (AudioFreq/1000)*20;
      PDM_FilterConfig[index].mic_gain = 24;
      PDM_FilterConfig[index].decimation_factor = PDM_FILTER_DEC_FACTOR_64;
      PDM_Filter_setConfig((PDM_Filter_Handler_t *)&PDM_FilterHandler[index], &PDM_FilterConfig[index]);
    }
  }

  return BSP_ERROR_NONE;
}

/**
  * @brief  Manages the DMA Full Transfer complete interrupt.
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(uint32_t Instance)
{
  RecBuffCplt = 1;
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @retval None
  */
void BSP_AUDIO_IN_HalfTransfer_CallBack(uint32_t Instance)
{
  RecHalfBuffCplt = 1;
}




