/**
  ******************************************************************************
  * @file    Examples/BSP/Src/audio.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the audio feature in the
  *          STM32H573I-DK driver
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
#include "audio_16khz_wav.h"

/** @addtogroup STM32H5xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */
/* Private define ------------------------------------------------------------*/

/* Display */
#define  CIRCLE_RADIUS        28
#define  LINE_LENGHT          28
#define  HEADBAND_HEIGHT      64
/* Audio Play */
#define AUDIO_BUFFER_SIZE       2048
#define AUDIO_DEFAULT_VOLUME    70
#define AUDIO_BLOCK_SIZE        ((uint32_t)0xFFFE)
#define AUDIO_NB_BLOCKS         ((uint32_t)4)
#define AUDIO_FILE_SIZE         BYTES_IN_AUDIO_WAV
/* Audio Record PDM */
#define PDM_SAMPLES_AT_EACH_CALL 16*2*20
#define AUDIO_REC_BUFFER_SIZE  (PDM_SAMPLES_AT_EACH_CALL * 16)
#define AUDIO_PLAY_BUFFER_SIZE (PDM_SAMPLES_AT_EACH_CALL * 4)

/* Private macro -------------------------------------------------------------*/
#define  CIRCLE_XPOS(i)       (((i == 1) | (i == 3)) ?  40 : 200)
#define  CIRCLE_YPOS(i)       (((i == 1) | (i == 2)) ? 100 : 200)

/* Private typedef -----------------------------------------------------------*/
typedef enum {
  AUDIO_STATE_IDLE = 0,
  AUDIO_STATE_INIT,
  AUDIO_STATE_PLAYING,
}AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

typedef struct {
  uint8_t buff[AUDIO_BUFFER_SIZE];
  uint32_t fptr;
  BUFFER_StateTypeDef state;
  uint32_t AudioFileSize;
  uint32_t *SrcAddress;
}AUDIO_BufferTypeDef;

typedef enum {
  AUDIO_ERROR_NONE = 0,
  AUDIO_ERROR_NOTREADY,
  AUDIO_ERROR_IO,
  AUDIO_ERROR_EOF,
}AUDIO_ErrorTypeDef;

typedef enum {
  TS_ACT_NONE = 0,
  TS_ACT_FREQ_DOWN,
  TS_ACT_FREQ_UP,
  TS_ACT_VOLUME_DOWN,
  TS_ACT_VOLUME_UP,
  TS_ACT_PAUSE = 0xFE
}TS_ActionTypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
BSP_AUDIO_Init_t             AudioOutInit;
BSP_AUDIO_Init_t             AudioInInit;
uint16_t                     PlayBuffer[AUDIO_BUFFER_SIZE];
uint8_t                      RecBuff[AUDIO_REC_BUFFER_SIZE];
uint16_t                     PlayBuff[AUDIO_PLAY_BUFFER_SIZE];
uint32_t                     RecHalfBuffCplt  = 0;
uint32_t                     RecBuffCplt      = 0;
uint32_t                     PlayHalfBuffCplt  = 0;
uint32_t                     PlayBuffCplt      = 0;
uint32_t                     ChannelsNumber;
__IO uint32_t                PauseResume = 0;
__IO uint32_t                StopStart = 0;
__IO uint32_t                uwPauseEnabledStatus = 0;
__IO uint16_t                x_old = 0, y_old = 0;

uint32_t playbackPtr = 0;
uint32_t PlaybackStarted = 0;
uint32_t AudioBufferOffset;
uint32_t uwVolume;

static AUDIO_BufferTypeDef  buffer_ctl;
static AUDIO_PLAYBACK_StateTypeDef  audio_state;
static uint32_t AudioFreq[8] = {8000 ,11025, 16000, 22050, 32000, 44100, 48000, 96000};
/* PDM filters params */
static PDM_Filter_Handler_t            PDM_FilterHandler[2];
static PDM_Filter_Config_t             PDM_FilterConfig[2];

static TS_ActionTypeDef ts_action = TS_ACT_NONE;
/* Private function prototypes -----------------------------------------------*/
static void Audio_SetHint(void);
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData);
AUDIO_ErrorTypeDef AUDIO_Start(uint32_t *psrc_address, uint32_t file_size);
static void Touchscreen_DrawBackground_Circles(uint8_t state);
static uint8_t TouchScreen_GetTouchButtonPosition(void);
static uint8_t Get_ButtonNum(uint16_t x1, uint16_t y1);
static int32_t Playback_Init(void);
static int32_t Record_Init(void);
static int32_t BSP_AUDIO_IN_PDMToPCM_Init(uint32_t Instance, uint32_t AudioFreq, uint32_t ChnlNbrIn, uint32_t ChnlNbrOut);

static void Test_AudioPlay (void);
static void Test_AudioRecordAnalog (void);
static void Test_AudioRecordPDM (void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Test Audio features
  * @param  None
  * @retval None
  */
void Test_Audio(void)
{
  StepBack = 0;
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
  UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)" Test Audio  ", CENTER_MODE);
  BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);
  UTIL_LCD_FillRect(35, 60, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_FillRect(35, 120, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_FillRect(35, 180, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);  
  UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"AUDIO PLAY", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 130, (uint8_t *)"RECORD ANALOG", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 190, (uint8_t *)"RECORD PDM DIG", CENTER_MODE);

  /* Initialize User button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  while (StepBack != 1)
  {
    if(TouchPressed > 0)
    {
      TouchPressed = 0;
      /* Test Audio Play */
      if ((TS_State.TouchX > 35) && (TS_State.TouchX < 200)&&(TS_State.TouchY > 60) && (TS_State.TouchY < 100))
      {
        Test_AudioPlay();
      }
      /* Test Audio Record Analog */
      if ((TS_State.TouchX > 35) && (TS_State.TouchX < 200)&&(TS_State.TouchY > 120) && (TS_State.TouchY < 160))
      {
        Test_AudioRecordAnalog();
      }
      /* Test Audio Record SAI PDM */
      if ((TS_State.TouchX > 35) && (TS_State.TouchX < 200)&&(TS_State.TouchY > 180) && (TS_State.TouchY < 220))
      {
        Test_AudioRecordPDM();
      }      
      /* Quit the Test */
      if ((TS_State.TouchX > 200) && (TS_State.TouchX < 240)&&(TS_State.TouchY > 0) && (TS_State.TouchY < 40))
      {
        StepBack = 1;
        /* De-Initialize User button */
        if (BSP_PB_DeInit(BUTTON_USER) != BSP_ERROR_NONE) Error_Handler();
        Menu_Display();
      }      
    }
  } 
}

/**
  * @brief  Audio Play demo
  * @param  None
  * @retval None
  */
static void Test_AudioPlay (void)
{
  uint32_t *AudioFreq_ptr;
  AudioFreq_ptr = AudioFreq+2; /*AF_48K*/
  uint8_t frequency_str[256] = {0};
  uint8_t volume_str[256] = {0};
  
  /* Clear LCD */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  uwVolume = 60;
  UserButtonPressed = RESET;
  Audio_SetHint();

  AudioOutInit.Device = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioOutInit.ChannelsNbr = 2;
  AudioOutInit.SampleRate = 16000;
  AudioOutInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioOutInit.Volume = uwVolume;

  if(BSP_AUDIO_OUT_Init(0, &AudioOutInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
  AudioFreq_ptr = AudioFreq+2;
  if(BSP_AUDIO_OUT_SetSampleRate(0, *AudioFreq_ptr) != BSP_ERROR_NONE) Error_Handler();

  /*
  Start playing the file from a circular buffer, once the DMA is enabled, it is
  always in running state. Application has to fill the buffer with the audio data
  using Transfer complete and/or half transfer complete interrupts callbacks
  (BSP_AUDIO_OUT_TransferComplete_CallBack() or BSP_AUDIO_OUT_HalfTransfer_CallBack()...
  */
  AUDIO_Start((uint32_t *)audio_wav + 11, (uint32_t)AUDIO_FILE_SIZE);

  /* Display the state on the screen */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
  UTIL_LCD_DisplayStringAt(0, 160, (uint8_t *)"Push Button to Exit", CENTER_MODE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DisplayStringAt(0, 130, (uint8_t *)"PLAYING...", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 145, (uint8_t *)"Touch to Pause", CENTER_MODE); 
  
  sprintf((char*)volume_str,"    VOL:    %lu ",uwVolume);
  UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)volume_str, CENTER_MODE);

  sprintf((char*)frequency_str,"      FREQ: %lu     ",*AudioFreq_ptr);
  UTIL_LCD_DisplayStringAt(0, 215, (uint8_t *)frequency_str, CENTER_MODE);

  Touchscreen_DrawBackground_Circles(16);
  UTIL_LCD_SetFont(&Font12);

  /* Infinite loop */
  while (1)
  {
    /* IMPORTANT: AUDIO_Process() should be called within a periodic process */
    AUDIO_Process();

      /* Get the TouchScreen State */
      ts_action = (TS_ActionTypeDef) TouchScreen_GetTouchButtonPosition();

      switch (ts_action)
      {
      case TS_ACT_VOLUME_UP:
        TS_State.TouchDetected = 0;
        if(uwPauseEnabledStatus != 1)
        {
          /* Increase volume by 5% */
          if (uwVolume < 95)
            uwVolume += 5;
          else
            uwVolume = 100;

          if(BSP_AUDIO_OUT_SetVolume(0, uwVolume) != BSP_ERROR_NONE) Error_Handler();
          sprintf((char*)volume_str,"  VOL:    %lu ",uwVolume);
          UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)volume_str, CENTER_MODE);
        }
        break;

      case TS_ACT_VOLUME_DOWN:
        if(uwPauseEnabledStatus != 1)
        {
          /* Decrease volume by 5% */
          if (uwVolume > 5)
            uwVolume -= 5;
          else
            uwVolume = 0;

          if(BSP_AUDIO_OUT_SetVolume(0, uwVolume) != BSP_ERROR_NONE) Error_Handler();
          sprintf((char*)volume_str,"  VOL:    %lu ",uwVolume);
          UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)volume_str, CENTER_MODE);
        }
        break;

      case TS_ACT_FREQ_DOWN:
        /*Decrease Frequency */
        if ((*AudioFreq_ptr != 8000) && (uwPauseEnabledStatus != 1))
        {
          AudioFreq_ptr--;
          if(BSP_AUDIO_OUT_Stop(0) != BSP_ERROR_NONE) Error_Handler();
          if(BSP_AUDIO_OUT_SetSampleRate(0, *AudioFreq_ptr) != BSP_ERROR_NONE) Error_Handler();
          AUDIO_Start((uint32_t *)audio_wav + 11, (uint32_t)AUDIO_FILE_SIZE);
          sprintf((char*)frequency_str, " FREQ: %6lu ", *AudioFreq_ptr);
          UTIL_LCD_DisplayStringAt(0, 215, (uint8_t *)frequency_str, CENTER_MODE);
        }

        break;
      case TS_ACT_FREQ_UP:
        /* Increase Frequency */
        if ((*AudioFreq_ptr != 96000) && (uwPauseEnabledStatus != 1))
        {
          AudioFreq_ptr++;
          if(BSP_AUDIO_OUT_Stop(0) != BSP_ERROR_NONE) Error_Handler();
          if(BSP_AUDIO_OUT_SetSampleRate(0, *AudioFreq_ptr) != BSP_ERROR_NONE) Error_Handler();
          AUDIO_Start((uint32_t *)audio_wav + 11, (uint32_t)AUDIO_FILE_SIZE);
          sprintf((char*)frequency_str, " FREQ: %6lu ", *AudioFreq_ptr);
          UTIL_LCD_DisplayStringAt(0, 215, (uint8_t *)frequency_str, CENTER_MODE);
        }
        break;
      case TS_ACT_PAUSE:
        TS_State.TouchDetected = 0;
        /* Set Pause / Resume */
        if (uwPauseEnabledStatus == 1)
        { /* Pause is enabled, call Resume */
          if(BSP_AUDIO_OUT_Resume(0) != BSP_ERROR_NONE) Error_Handler();
          uwPauseEnabledStatus = 0;
          UTIL_LCD_DisplayStringAt(0, 130, (uint8_t *)"PLAYING...", CENTER_MODE);
          UTIL_LCD_DisplayStringAt(0, 145, (uint8_t *)"Touch to Pause", CENTER_MODE);
        }
        else
        { /* Pause the playback */
          if(BSP_AUDIO_OUT_Pause(0) != BSP_ERROR_NONE) Error_Handler();
          uwPauseEnabledStatus = 1;
          UTIL_LCD_DisplayStringAt(0, 130, (uint8_t *)"PAUSE  ...", CENTER_MODE);
          UTIL_LCD_DisplayStringAt(0, 145, (uint8_t *)"Touch to Play ", CENTER_MODE);
        }
        HAL_Delay(200);
        break;

      default:
        break;
      }
      while(TouchPressed == 1)
      {
        BSP_TS_GetState(0, &TS_State);
        if(TS_State.TouchDetected == 0)
        {
          TouchPressed = 0;
        }
      }

    if (UserButtonPressed == SET)
    {      
      if(BSP_AUDIO_OUT_Stop(0) != BSP_ERROR_NONE) Error_Handler();
      HAL_Delay(100);
      if(BSP_AUDIO_OUT_DeInit(0) != BSP_ERROR_NONE) Error_Handler();
      
      UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
      UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
      UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)" Test Audio  ", CENTER_MODE);
      BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);
      UTIL_LCD_FillRect(35, 60, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_FillRect(35, 120, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_FillRect(35, 180, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);  
      UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"AUDIO PLAY", CENTER_MODE);
      UTIL_LCD_DisplayStringAt(0, 130, (uint8_t *)"RECORD ANALOG", CENTER_MODE);
      UTIL_LCD_DisplayStringAt(0, 190, (uint8_t *)"RECORD PDM DIG", CENTER_MODE);
      break;
    }
  }
}

/**
  * @brief  Audio Record from Analog MIC and Play back
  * @param  None
  * @retval None
  */  
static void Test_AudioRecordAnalog (void)
{
  UserButtonPressed = RESET;
  
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
  UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)"Audio Record Analog", CENTER_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);

  AudioOutInit.Device = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioOutInit.ChannelsNbr = 1;
  AudioOutInit.SampleRate = AUDIO_FREQUENCY_16K;
  AudioOutInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioOutInit.Volume = 100;
  
  AudioInInit.Device = AUDIO_IN_DEVICE_ANALOG_MIC;
  AudioInInit.ChannelsNbr = 1;
  AudioInInit.SampleRate = AUDIO_FREQUENCY_16K;
  AudioInInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioInInit.Volume = 100;
  
  if(BSP_AUDIO_OUT_Init(0, &AudioOutInit) != BSP_ERROR_NONE) Error_Handler();
  
  /* Initialize Audio Recorder */
  if (BSP_AUDIO_IN_Init(0, &AudioInInit) != BSP_ERROR_NONE)
  {
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED); 
    UTIL_LCD_DisplayStringAt(0, 100, (uint8_t *)"INITIALIZATION FAIL", CENTER_MODE);
    UTIL_LCD_DisplayStringAt(0, 120, (uint8_t *)"Try to reset board", CENTER_MODE);
    Error_Handler();
  }
  
  AudioBufferOffset = BUFFER_OFFSET_NONE;
  
  /* Display the state on the screen */
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN); 
  UTIL_LCD_DisplayStringAt(0, 100, (uint8_t *)"RECORDING and PLAYING", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 120, (uint8_t *)"back from analog MIC...", CENTER_MODE);  
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
  
  UTIL_LCD_DisplayStringAt(0, 160, (uint8_t *)"Press USER Button", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"To Exit the test", CENTER_MODE);
  
  /* Start Recording: Size in number of bytes */
  if(BSP_AUDIO_IN_Record(0, (uint8_t*)PlayBuffer, 2*AUDIO_BUFFER_SIZE) != BSP_ERROR_NONE) Error_Handler();
  
  while (1)
  {
    if(AudioBufferOffset == BUFFER_OFFSET_HALF)
    {
      if(PlaybackStarted == 0)
      {
        /* Play the recorded buffer*/
        if(BSP_AUDIO_OUT_Play(0, (uint8_t*)PlayBuffer, 2*AUDIO_BUFFER_SIZE) != BSP_ERROR_NONE) Error_Handler();
        PlaybackStarted = 1;
      }
      AudioBufferOffset  = BUFFER_OFFSET_NONE;
    }
    
    if (UserButtonPressed == SET)
    {
      if(BSP_AUDIO_IN_Stop(0) != BSP_ERROR_NONE) Error_Handler();
      if(BSP_AUDIO_IN_DeInit(0) != BSP_ERROR_NONE) Error_Handler();      
      if(BSP_AUDIO_OUT_Stop(0) != BSP_ERROR_NONE) Error_Handler();
      if(BSP_AUDIO_OUT_DeInit(0) != BSP_ERROR_NONE) Error_Handler();


      UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
      UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
      UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)" Test Audio  ", CENTER_MODE);
      BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);
      UTIL_LCD_FillRect(35, 60, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_FillRect(35, 120, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_FillRect(35, 180, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);  
      UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"AUDIO PLAY", CENTER_MODE);
      UTIL_LCD_DisplayStringAt(0, 130, (uint8_t *)"RECORD ANALOG", CENTER_MODE);
      UTIL_LCD_DisplayStringAt(0, 190, (uint8_t *)"RECORD PDM DIG", CENTER_MODE);      
      PlaybackStarted = 0;
      break;
    }
  }
}

/**
  * @brief  Audio Record from digital MIC via SAI PDM and Play back
  * @param  None
  * @retval None
  */  
static void Test_AudioRecordPDM (void)
{
  UserButtonPressed = RESET;
  uint32_t GetData;
  Point     triangle1[3] = {{140, 90}, {200, 120}, {140, 150}};
  uint32_t x_pos = 0, y_pos = 0, i;

    /* Initialize User button */
  UserButtonPressed = RESET;

  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
  UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)"Audio Record PDM", CENTER_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
  
  UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"Press USER Button", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)"To Exit the test", CENTER_MODE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_FillRect(140, 90, 28, 60, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillRect(172, 90, 28, 60, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillRect(40, 90, 60, 60, UTIL_LCD_COLOR_GRAY);

  ChannelsNumber = 2;

  /* Initialize record */
  if(Record_Init() != 0) Error_Handler();
  
  /* Initialize playback */
  if(Playback_Init() != 0) Error_Handler();

  if(BSP_AUDIO_IN_PDMToPCM_Init(1, AUDIO_FREQUENCY_16K, ChannelsNumber, ChannelsNumber) != 0) Error_Handler();
  HAL_Delay(1000);

  /* Start record */
  if (BSP_AUDIO_IN_RecordPDM(1, (uint8_t *) RecBuff, AUDIO_REC_BUFFER_SIZE) != BSP_ERROR_NONE) Error_Handler();

  /* Start loopback */
  while(1)
  {    

    BSP_TS_GetState(0, &TS_State);
    
    if(TS_State.TouchDetected > 0)
    {
      x_pos = TS_State.TouchX;
      y_pos = TS_State.TouchY;
    }
    
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
        UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"RECORDING/PLAYING", CENTER_MODE);
        PlaybackStarted = 1;
      }

      RecBuffCplt = 0;
    }
    /* Pause */
    if ((x_pos > 140) && (x_pos < 200)&&(y_pos > 90) && (y_pos < 150) && (PauseResume == 0))
    {
      UTIL_LCD_FillRect(140, 90, 60, 60, UTIL_LCD_COLOR_WHITE);
      UTIL_LCD_FillPolygon(triangle1, 3, UTIL_LCD_COLOR_GREEN);
      UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"      PAUSED     ", CENTER_MODE);
      /* Pause record and stop playback */
      if (BSP_AUDIO_OUT_Stop(0) != BSP_ERROR_NONE) Error_Handler();

      if (BSP_AUDIO_IN_Pause(1) != BSP_ERROR_NONE) Error_Handler();

      /* Test of state */
      if (BSP_AUDIO_IN_GetState(1, &GetData) != BSP_ERROR_NONE) Error_Handler();
      if (GetData != AUDIO_IN_STATE_PAUSE) Error_Handler();
      /* Wait a little delay for pending dma */
      HAL_Delay(1000);
      /* Reset global variable */
      PlaybackStarted = 0;
      RecBuffCplt = 0;
      RecHalfBuffCplt = 0;
      PauseResume = 1;
      x_pos = 0;
      y_pos = 0;
    }
    /* Resume */
    if ((x_pos > 140) && (x_pos < 200)&&(y_pos > 90) && (y_pos < 150) && (PauseResume == 1))
    {
      UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"RECORDING/PLAYING", CENTER_MODE);
      UTIL_LCD_FillRect(140, 90, 60, 60, UTIL_LCD_COLOR_WHITE);
      UTIL_LCD_FillRect(140, 90, 28, 60, UTIL_LCD_COLOR_GREEN);
      UTIL_LCD_FillRect(172, 90, 28, 60, UTIL_LCD_COLOR_GREEN);
      
      /* Resume record */
      if (BSP_AUDIO_IN_Resume(1) != BSP_ERROR_NONE) Error_Handler();

      HAL_Delay(100);
      /* Test of state */
      if (BSP_AUDIO_IN_GetState(1, &GetData) != BSP_ERROR_NONE) Error_Handler();
      if (GetData != AUDIO_IN_STATE_RECORDING) Error_Handler();
      PauseResume = 0;
      x_pos = 0;
      y_pos = 0;
    }
    /* Stop */
    if ((x_pos > 40) && (x_pos < 100)&&(y_pos > 90) && (y_pos < 150) && (StopStart == 0))
    {
      UTIL_LCD_FillRect(42, 92, 56, 56, UTIL_LCD_COLOR_RED);
      UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"     STOPPED     ", CENTER_MODE);
      /* Stop record and stop playback */
      if (BSP_AUDIO_OUT_Stop(0) != BSP_ERROR_NONE) Error_Handler();
      if (BSP_AUDIO_IN_Stop(1) != BSP_ERROR_NONE) Error_Handler();
      
      /* Test of state */
      if (BSP_AUDIO_IN_GetState(1, &GetData) != BSP_ERROR_NONE) Error_Handler();
      if (GetData != AUDIO_IN_STATE_STOP) Error_Handler();
      /* Wait a little delay for pending dma */
      HAL_Delay(1000);
      /* Reset global variable */
      PlaybackStarted = 0;
      RecBuffCplt = 0;
      RecHalfBuffCplt = 0;
      playbackPtr = 0;
      StopStart = 1;
      x_pos = 0;
      y_pos = 0;      
    }
    /* Start */
    if ((x_pos > 40) && (x_pos < 100)&&(y_pos > 90) && (y_pos < 150) && (StopStart == 1))
    {
      UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"RECORDING/PLAYING", CENTER_MODE);
      
      UTIL_LCD_FillRect(40, 90, 60, 60, UTIL_LCD_COLOR_GRAY);
      /* Restart record */
      if(BSP_AUDIO_IN_RecordPDM(1, (uint8_t *) RecBuff, AUDIO_REC_BUFFER_SIZE) != BSP_ERROR_NONE) Error_Handler();

      HAL_Delay(100);
      /* Test of state */
      if (BSP_AUDIO_IN_GetState(1, &GetData) != BSP_ERROR_NONE) Error_Handler();
      if (GetData != AUDIO_IN_STATE_RECORDING) Error_Handler();
      
      StopStart = 0;
      x_pos = 0;
      y_pos = 0; 
    }
    /* De-Init then re-start */
    if (UserButtonPressed == SET)
    {
      /* Stop record and stop playback */
      if (BSP_AUDIO_OUT_Stop(0) != BSP_ERROR_NONE) Error_Handler();
      if (BSP_AUDIO_IN_Stop(1) != BSP_ERROR_NONE) Error_Handler();
      
      /* Test of state */
      if (BSP_AUDIO_IN_GetState(1, &GetData) != BSP_ERROR_NONE) Error_Handler();
      if (GetData != AUDIO_IN_STATE_STOP) Error_Handler();
      /* Wait a little delay for pending dma */
      HAL_Delay(1000);
      /* Reset global variable */
      PlaybackStarted = 0;
      RecBuffCplt = 0;
      RecHalfBuffCplt = 0;

      /* De initialize record and stop playback */
      if (BSP_AUDIO_OUT_DeInit(0) != BSP_ERROR_NONE) Error_Handler();
      if (BSP_AUDIO_IN_DeInit(1) != BSP_ERROR_NONE) Error_Handler();

      /* Test of state */
      if (BSP_AUDIO_IN_GetState(1, &GetData) != BSP_ERROR_NONE) Error_Handler();
      if (GetData != AUDIO_IN_STATE_RESET) Error_Handler();
      
      UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
      UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
      UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)" Test Audio  ", CENTER_MODE);
      BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);
      UTIL_LCD_FillRect(35, 60, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_FillRect(35, 120, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_FillRect(35, 180, 165, 40, UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_YELLOW);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);  
      UTIL_LCD_DisplayStringAt(0, 70, (uint8_t *)"AUDIO PLAY", CENTER_MODE);
      UTIL_LCD_DisplayStringAt(0, 130, (uint8_t *)"RECORD ANALOG", CENTER_MODE);
      UTIL_LCD_DisplayStringAt(0, 190, (uint8_t *)"RECORD PDM DIG", CENTER_MODE);
      break; 
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
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetState(1, &GetData))  Error_Handler();
  if (GetData != AUDIO_IN_STATE_RESET) Error_Handler();
  AudioInit.Device        = AUDIO_IN_DEVICE_DIGITAL_MIC;
  AudioInit.SampleRate    = AUDIO_FREQUENCY_16K;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_8B;
  AudioInit.ChannelsNbr   = ChannelsNumber;
  AudioInit.Volume        = 80; /* Not used */

  if (BSP_ERROR_NONE != BSP_AUDIO_IN_Init(1, &AudioInit)) Error_Handler();

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
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetState(1, &GetData)) Error_Handler();
  if (GetData != AUDIO_IN_STATE_STOP) Error_Handler();
 
  AudioInit.Device        = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioInit.SampleRate    = AUDIO_FREQUENCY_16K;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioInit.ChannelsNbr   = ChannelsNumber;
  AudioInit.Volume        = 80;

  if (BSP_ERROR_NONE != BSP_AUDIO_OUT_Init(0, &AudioInit)) Error_Handler();

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
  * @brief  Display Audio demo hint
  * @param  None
  * @retval None
  */
static void Audio_SetHint(void)
{
  uint32_t x_size;

  BSP_LCD_GetXSize(0, &x_size);

  /* Clear the LCD */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  /* Set Audio Demo description */
  UTIL_LCD_FillRect(0, 0, x_size, HEADBAND_HEIGHT, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"AUDIO PLAY", CENTER_MODE);
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_DisplayStringAt(0, 20, (uint8_t *)" Touch       | pause / resume ", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(0, 35, (uint8_t *)" Touch       | change Volume/Freq", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(0, 50, (uint8_t *)" User Button | Exit Test ", LEFT_MODE);
}


/**
  * @brief  Starts Audio streaming.
  * @param  psrc_address : buffer start address
  * @param  file_size : buffer size in bytes
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Start(uint32_t *psrc_address, uint32_t file_size)
{
  uint32_t bytesread;

  buffer_ctl.state = BUFFER_OFFSET_NONE;
  buffer_ctl.AudioFileSize = file_size;
  buffer_ctl.SrcAddress = psrc_address;

  bytesread = GetData( (void *)psrc_address,
                       0,
                       (uint8_t*)&PlayBuffer[0],
                       AUDIO_BUFFER_SIZE);
  if(bytesread > 0)
  {
    BSP_AUDIO_OUT_Play(0, (uint8_t *)PlayBuffer, 2*AUDIO_BUFFER_SIZE);
    audio_state = AUDIO_STATE_PLAYING;
    buffer_ctl.fptr = bytesread;
    return AUDIO_ERROR_NONE;
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Manages Audio process.
  * @param  None
  * @retval Audio error
  */
uint8_t AUDIO_Process(void)
{
  uint32_t bytesread;
  AUDIO_ErrorTypeDef error_state = AUDIO_ERROR_NONE;

  switch(audio_state)
  {
  case AUDIO_STATE_PLAYING:

    if(buffer_ctl.fptr >= buffer_ctl.AudioFileSize)
    {
      /* Play audio sample again ... */
      buffer_ctl.fptr = 0;
      error_state = AUDIO_ERROR_EOF;
    }

    /* 1st half buffer played; so fill it and continue playing from bottom*/
    if(buffer_ctl.state == BUFFER_OFFSET_HALF)
    {
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          (uint8_t*)&PlayBuffer[0],
                          AUDIO_BUFFER_SIZE );

      if( bytesread >0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread;
      }
    }

    /* 2nd half buffer played; so fill it and continue playing from top */
    if(buffer_ctl.state == BUFFER_OFFSET_FULL)
    {
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          (uint8_t*)&PlayBuffer[AUDIO_BUFFER_SIZE /2],
                          AUDIO_BUFFER_SIZE );
      if( bytesread > 0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread;
      }
    }
    break;

  default:
    error_state = AUDIO_ERROR_NOTREADY;
    break;
  }
  return (uint8_t) error_state;
}

/**
  * @brief  Gets Data from storage unit.
  * @param  None
  * @retval None
  */
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData)
{
  uint8_t *lptr = pdata;
  uint32_t ReadDataNbr;

  ReadDataNbr = 0;
  while(((offset + ReadDataNbr) < buffer_ctl.AudioFileSize) && (ReadDataNbr < NbrOfData))
  {
    pbuf[ReadDataNbr]= lptr [offset + ReadDataNbr];
    ReadDataNbr++;
  }
  return ReadDataNbr;
}

/*------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm32h573i_discovery_audio.c file
           and their implementation should be done the user code if they are needed.
           Below some examples of callback implementations.
  ----------------------------------------------------------------------------*/
/**
  * @brief  Manages the DMA Full Transfer complete interrupt.
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(uint32_t Instance)
{
  if(Instance == 1U)
  {
    RecBuffCplt = 1;
  }
  else
  {
    AudioBufferOffset = BUFFER_OFFSET_FULL;
  } 
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @retval None
  */
void BSP_AUDIO_IN_HalfTransfer_CallBack(uint32_t Instance)
{
  if(Instance == 1U)
  {
    RecHalfBuffCplt = 1;
  }
  else
  {
    AudioBufferOffset = BUFFER_OFFSET_HALF;
  }
}

/**
  * @brief  Manages the full Transfer complete event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance)
{
  if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 2nd part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_FULL;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance)
{
  if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 1st part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_HALF;
  }
}

/**
  * @brief  Manages the DMA FIFO error event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance)
{
  /* Display message on the LCD screen */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
  UTIL_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"       DMA  ERROR     ", CENTER_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);

  /* Stop the program with an infinite loop */
  while (BSP_PB_GetState(BUTTON_USER) != RESET)
  { return;}

  /* could also generate a system reset to recover from the error */
  /* .... */
}


/**
  * @brief  Draw Touchscreen Background
  * @param  state : touch zone state
  * @retval None
  */
static void Touchscreen_DrawBackground_Circles(uint8_t state)
{
  uint32_t x_size, y_size;
  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetXSize(0, &y_size);
  
  UTIL_LCD_FillCircle(CIRCLE_XPOS(1), CIRCLE_YPOS(1), CIRCLE_RADIUS, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_FillCircle(CIRCLE_XPOS(2), CIRCLE_YPOS(2), CIRCLE_RADIUS, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_FillCircle(CIRCLE_XPOS(3), CIRCLE_YPOS(3), CIRCLE_RADIUS, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_FillCircle(CIRCLE_XPOS(4), CIRCLE_YPOS(3), CIRCLE_RADIUS, UTIL_LCD_COLOR_BLUE);
  
  UTIL_LCD_FillCircle(CIRCLE_XPOS(1), CIRCLE_YPOS(1), CIRCLE_RADIUS - 2, UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillCircle(CIRCLE_XPOS(2), CIRCLE_YPOS(2), CIRCLE_RADIUS - 2, UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillCircle(CIRCLE_XPOS(3), CIRCLE_YPOS(3), CIRCLE_RADIUS - 2, UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillCircle(CIRCLE_XPOS(4), CIRCLE_YPOS(3), CIRCLE_RADIUS - 2, UTIL_LCD_COLOR_WHITE);
  
  UTIL_LCD_DrawHLine(CIRCLE_XPOS(1)-LINE_LENGHT, CIRCLE_YPOS(1), 2*LINE_LENGHT, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawHLine(CIRCLE_XPOS(2)-LINE_LENGHT, CIRCLE_YPOS(2), 2*LINE_LENGHT, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawVLine(CIRCLE_XPOS(2), CIRCLE_YPOS(2)-LINE_LENGHT, 2*LINE_LENGHT, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawHLine(CIRCLE_XPOS(3)-LINE_LENGHT, CIRCLE_YPOS(3), 2*LINE_LENGHT, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawHLine(CIRCLE_XPOS(4)-LINE_LENGHT, CIRCLE_YPOS(4), 2*LINE_LENGHT, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawVLine(CIRCLE_XPOS(4), CIRCLE_YPOS(4)-LINE_LENGHT, 2*LINE_LENGHT, UTIL_LCD_COLOR_BLUE);  
}

/**
  * @brief  TouchScreen get touch position
  * @param  None
  * @retval None
  */
static uint8_t TouchScreen_GetTouchButtonPosition(void)
{
  uint16_t x1, y1;
  uint8_t buttonnum = 0;


  /* Check in polling mode in touch screen the touch status and coordinates */
  /* of touches if touch occurred                                           */
  BSP_TS_GetState(0, &TS_State);

    /* Get X and Y position of the first */
    x1 = TS_State.TouchX;
    y1 = TS_State.TouchY;

  if(TS_State.TouchDetected)
  {
    if((x_old != x1) || (y_old != y1))
    {
      x_old = x1;
      y_old = y1;
      buttonnum = Get_ButtonNum(x1, y1);
    }
  }
  return buttonnum;
}

static uint8_t Get_ButtonNum(uint16_t x1, uint16_t y1)
{
  uint8_t buttonnum = 0;
  
  if ((y1 < 130))
  {
    if ((x1 > 10) && (x1 < 85))
    {
      
      buttonnum = 3; /* Vol - */
    }
    else if ((x1 > 170) && (x1 < 240))
    {
      
      buttonnum = 4; /* Vol + */
    }
  }
  else if ((y1 > 115) && (y1 < 190))
  {
    if ((x1 > 90) && (x1 < 190))
    {
      
      buttonnum = 0xFE; /* Pause/Play */
    }
  }
  else  if (y1 > 200)
  {
    if ((x1 > 10) && (x1 < 80))
    {
      
      buttonnum = 1; /* freq - */
    }
    
    else if ((x1 > 170) && (x1 < 240))
    {
      
      buttonnum = 2; /* freq+ */
    }
  }
  else
  {
    buttonnum = 0xFF;
  }
  
  return buttonnum;
}

/**
  * @}
  */

/**
  * @}
  */

