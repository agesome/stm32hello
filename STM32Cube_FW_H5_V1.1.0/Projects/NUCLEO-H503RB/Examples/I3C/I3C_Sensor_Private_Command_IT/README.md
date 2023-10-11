## <b>I3C_Sensor_Private_Command_IT Example Description</b>

How to handle I3C as Controller data buffer transmission/reception between STM32H5xx Nucleo and X-NUCLEO-IKS01A3,
using interrupt.

Goal of this example is to demonstrate a simple communication with the sensor LSM6DSO present on X-NUCLEO-IKS01A3

      - Board: NUCLEO-H503RB (embeds a STM32H503RB device)
      - SCL Pin: PB6 (Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3)
      - SDA Pin: PB7 (Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5)

      - Plug a X-NUCLEO-IKS01A3 (https://www.st.com/en/ecosystems/x-nucleo-iks01a3.html) expansion board
        on arduino connector

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 250 MHz.

The I3C peripheral configuration is ensured by the HAL_I3C_Init() function.
This later is calling the HAL_I3C_MspInit()function which core is implementing
the configuration of the needed I3C resources according to the used hardware (CLOCK, GPIO and NVIC).
User may update this function to change I3C configuration.
To have a better signal startup, the user must adapt the parameter BusFreeDuration
depends on its hardware constraint. The value of BusFreeDuration set on this example
is link to Nucleo hardware environment.

Note: To manage properly the data transfer, the value HAL_I3C_TXFIFO_THRESHOLD_4_4 in FIFO configuration
is not allowed when there is multiple transmit in the same descriptor.

The I3C communication is then initiated with a I3C Bus timing at 1Mhz as LSM6DSO start in I2C mode at Reset.

In a first communication step, the HAL_I3C_Ctrl_TransmitCCC_IT() function allow the Controller to transfer
the aBroadcast_CCC descriptor, which consist to disable the LSM6DSO interrupt then Reset the Dynamic address.

In a second communication step, the HAL_I3C_Ctrl_TransmitCCC_IT() function allow the Controller to transfer
the aDirect_CCC descriptor, which consist to assign a Dynamic address assignment through the LSM6DSO Static address.

After a dynamic address has been assigned, the sensor is recognized as an I3C device,
the controller checks the presence of the sensor by sending the new dynamic address through the
HAL_I3C_Ctrl_IsDeviceI3C_Ready() function.

Then controller waiting the ACK of address.

At this step, the I3C_CtrlTimingComputation() and HAL_I3C_Ctrl_BusCharacteristicConfig() function allow the I3C
Controller to set bus speed to 5MHz as on IKS01A3 is the maximum allowed speed due to the level shifters.

Then controller waiting user action.

The user press the USER push-button on the Controller Board, the I3C Controller initiate
the communication by sending aTxBuffer through HAL_I3C_Ctrl_Transmit_IT() to config the LSM6DSO.

The Controller is informed at fully transfer of CCC element through HAL_I3C_CtrlMultipleXferCpltCallback().

The end of each of those steps are monitored through the HAL_I3C_GetState() function
result.

Then, in an infinite loop, the I3C Controller intiate sensor communication to retrieve the LSM6DSO Temperature,
Gyroscope and Magnetometer data.

The HAL_I3C_Ctrl_MultipleTransfer_IT() function allow the I3C Controller to send and receive an amount of data
to or from the LSM6DSO Temperature, Gyroscope and Magnetometer by using the same descriptor context.

This mean that the HAL_I3C_Ctrl_MultipleTransfer_IT() function allow the I3C Controller to send a aTxBuffer
which contain the register address of the  data, and to retrieve and fill the data into aRxBuffer.

The end of each of those steps are monitored through the HAL_I3C_GetState() function
result.

At this step, Controller compute the data receive through aRxBuffer and
print it through Terminal I/O through DisplayValue() at each display refresh time.

NUCLEO-H503RB's LEDs can be used to monitor the transfer status:

 - LED2 is ON when the transmission process is complete.
 - LED2 is OFF when the reception process is complete.
 - LED2 toggle slowly when there is an error in transmission/reception process.

Terminal I/O watch the list of Get Command Code sent by Controller and associated Target data with IDE in debug mode.
Depending of IDE, to watch content of Terminal I/O note that
 - When resorting to EWARM IAR IDE:
   Command Code is displayed on debugger as follows: View --> Terminal I/O

 - When resorting to MDK-ARM KEIL IDE:
   Command Code is displayed on debugger as follows: View --> Serial Viewer --> Debug (printf) Viewer

 - When resorting to STM32CubeIDE:
   Command Code is displayed on debugger as follows: Window--> Show View--> Console.
   In Debug configuration :
   - Window\Debugger, select the Debug probe : ST-LINK(OpenOCD)
   - Window\Startup,add the command "monitor arm semihosting enable"

#### <b>Notes</b>

  1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

  2. The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

### <b>Keywords</b>

Connectivity, Communication, I3C, Interrupt, Controller, Target, Dynamic Address Assignment, Private,
Transmission, Reception, Multiple transfer.

### <b>Directory contents</b>

  - I3C/I3C_Sensor_Private_Command_IT/Inc/desc_target1.h            Target Descriptor
  - I3C/I3C_Sensor_Private_Command_IT/Inc/stm32h5xx_nucleo_conf.h   BSP configuration file
  - I3C/I3C_Sensor_Private_Command_IT/Inc/stm32h5xx_hal_conf.h      HAL configuration file
  - I3C/I3C_Sensor_Private_Command_IT/Inc/stm32h5xx_it.h            I3C interrupt handlers header file
  - I3C/I3C_Sensor_Private_Command_IT/Inc/main.h                    Header for main.c module
  - I3C/I3C_Sensor_Private_Command_IT/Src/stm32h5xx_it.c            I3C interrupt handlers
  - I3C/I3C_Sensor_Private_Command_IT/Src/main.c                    Main program
  - I3C/I3C_Sensor_Private_Command_IT/Src/system_stm32h5xx.c        STM32H5xx system source file
  - I3C/I3C_Sensor_Private_Command_IT/Src/stm32h5xx_hal_msp.c       HAL MSP file

### <b>Hardware and Software environment</b>

  - This example runs on STM32H503RB devices.

  - This example has been tested with NUCLEO-H503RB board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-H503RB Set-up

    - Plug a X-NUCLEO-IKS01A3 (https://www.st.com/en/ecosystems/x-nucleo-iks01a3.html) expansion board
      on arduino connector.

  - In case of example I3C_Sensor_Direct_Command_DMA have been launched before, prefer to unplug then plug the USB cable to
    reset the sensor, and prevent side effect of CCC MRL, MWL value too short for this example.
  - Launch the program in debug mode on Controller board side to benefit of Terminal I/O information on Controller side.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - In case of example I3C_Sensor_Direct_Command_DMA have been launched before, prefer to unplug then plug the USB cable to
   reset the sensor, and prevent side effect of CCC MRL, MWL value too short for this example.
 - Open your preferred toolchain
 - Rebuild all files and load your image into Controller memory (I3C_Sensor_Private_Command_IT).
