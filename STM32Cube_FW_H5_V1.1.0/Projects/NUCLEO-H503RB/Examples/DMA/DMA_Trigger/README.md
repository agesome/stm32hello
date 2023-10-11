## <b>DMA_Trigger Example Description</b>

How to configure and use the DMA HAL API to perform DMA triggered transactions.

This project is targeted to run on STM32H503RBTx devices on NUCLEO-H503RB board from STMicroelectronics.

The project configures the maximum system clock frequency at 250 MHz.

The triggering DMA transfer is started by software.
When this transfer ends, its transfer complete signal will be used to trigger another DMA transfer in a different DMA channel.

The triggering DMA channel performs transactions from source buffer "aSRC_Buffer" to destination buffer
"aDST_TriggerChannel_Buffer" with block size equal to 4 bytes and generates a transfer complete signal when transaction ends.
The triggered channel performs transaction from source buffer "aDST_TriggerChannel_Buffer" to
destination buffer "aDST_TriggeredChannel_Buffer" with block size equal to 128 bytes.
At each trigger signal generation, the triggered channel performs a single data transaction (4 bytes).

NUCLEO-H503RB board's LED can be used to monitor the transfers status:

 - LED2 toggle when no error detected.
 - LED2 is ON when any error occurred.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Memory, DMA, Trigger

### <b>Directory contents</b>

  - DMA/DMA_RepeatedBlock/Src/main.c                  Main program
  - DMA/DMA_RepeatedBlock/Src/system_stm32h5xx.c      STM32H5xx system clock configuration file
  - DMA/DMA_RepeatedBlock/Src/stm32h5xx_it.c          Interrupt handlers
-   DMA/DMA_RepeatedBlock/Src/stm32h5xx_hal_msp.c     HAL MSP module
  - DMA/DMA_RepeatedBlock/Inc/main.h                  Main program header file
  - DMA/DMA_RepeatedBlock/Inc/stm32h5xx_nucleo_conf.h BSP Configuration file
  - DMA/DMA_RepeatedBlock/Inc/stm32h5xx_hal_conf.h    HAL Configuration file
  - DMA/DMA_RepeatedBlock/Inc/stm32h5xx_it.h          Interrupt handlers header file

### <b>Hardware and Software environment</b>

  - This example runs on STM32H503RBTx devices.

  - This example has been tested with STMicroelectronics NUCLEO-H503RB
    board and can be easily tailored to any other supported device
    and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

