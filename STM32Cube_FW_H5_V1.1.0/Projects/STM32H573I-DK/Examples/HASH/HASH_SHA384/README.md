## <b>HASH_SHA384 example Description</b>

This example provides a short description of how to use the HASH peripheral to 
hash data using SHA_384 Algorithm.

**HASH_SHA384 configuration:**

For this example, DMA is not used for data transfer, the CPU is using HASH peripheral in
polling mode.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock (SYSCLK) to run at 250 MHz.

The SHA384 message digest result is a 384 bit (48 bytes) data.

Since we are using NIST vector, the expected HASH digests is already given.
The digests value is compared to the computed by the HASH peripheral.
In case of digest computation mismatch or initialization issue the LED3 is blinking (200 ms period).
In case the SHA384 digest is computed correctly the LED1 is turned ON.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

System, Security, HASH, HMAC, SHA384, digest

### <b>Directory contents</b>

  - HASH/HASH_SHA384/Inc/stm32h573i_discovery_conf.h    BSP configuration file
      - HASH/HASH_SHA384/Inc/stm32h5xx_hal_conf.h       HAL configuration file
      - HASH/HASH_SHA384/Inc/stm32h5xx_it.h             Interrupt handlers header file
      - HASH/HASH_SHA384/Inc/main.h                     Header for main.c module  
      - HASH/HASH_SHA384/Src/stm32h5xx_it.c             Interrupt handlers
      - HASH/HASH_SHA384/Src/main.c                     Main program
      - HASH/HASH_SHA384/Src/stm32h5xx_hal_msp.c        HAL MSP module
      - HASH/HASH_SHA384/Src/system_stm32h5xx.c         STM32H5xx system source file


### <b>Hardware and Software environment</b>

  - This example runs on STM32H573IIKxQ devices.

  - This example has been tested with a STM32H573IIKxQ embedded on an
    STM32H573I-DK board and can be easily tailored to any other supported
    device and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 