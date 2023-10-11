## <b>SD_ReadWrite_DMALinkedList Example Description</b>

This example performs some write and read transfers to SD Card with SDMMC IP internal
DMA mode based on Linked list feature.

**Note :** This example works with Normal SD Card.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock for STM32H573AIIx Devices :
The CPU at 250 MHz.

The transfer clock is set at 24Mhz (SDMMC_CLK / Clock_DIV * 2) and configured within the
SD Handle init parameters.
Next, prepare linked list nodes for write buffers and start the writing transfer to SD Card.
Then prepare linked list nodes for read buffers to write and start the reading transfer from SD Card.

STM32H573I-DK board's LEDs can be used to monitor the transfer status:

 - LED1  is ON when write/read transfer is ongoing.
 - LED1 is Toggling  when write and read transfer is completed and check buffers are OK.
 - LED3 is Toggling  when there is an error in transfer process or initialization.


#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Storage, SD, SDMMC, Read Write, Block, Sector, DMA, Linked List

### <b>Directory contents</b>

  - SD/SD_ReadWrite_DMALinkedList/Inc/stm32h5xx_hal_conf.h    		HAL configuration file
  - SD/SD_ReadWrite_DMALinkedList/Inc/stm32h5xx_it.h          		Interrupt handlers header file
  - SD/SD_ReadWrite_DMALinkedList/Inc/main.h                  		Header for main.c module
  - SD/SD_ReadWrite_DMALinkedList/Src/stm32h5xx_it.c          		Interrupt handlers
  - SD/SD_ReadWrite_DMALinkedList/Src/main.c                  		Main program
  - SD/SD_ReadWrite_DMALinkedList/Src/stm32h5xx_hal_msp.c     		HAL MSP module
  - SD/SD_ReadWrite_DMALinkedList/Src/system_stm32h5xx.c      		STM32H5xx system source file
  - SD/SD_ReadWrite_DMALinkedList/Inc/stm32h573i_discovery_conf.h   HAL configuration file


### <b>Hardware and Software environment</b>

  - This example runs on STM32H573IIKxQ devices.

  - This example has been tested with STM32H573I-DK board and can be
    easily tailored to any other supported device and development board.

  STM32H573I-DK Set-up :

  - Connect the uSD Card to the Micro SD connector (CN5).


### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Plug the SD Card in the STM32H573I-DK
 - Run the example


