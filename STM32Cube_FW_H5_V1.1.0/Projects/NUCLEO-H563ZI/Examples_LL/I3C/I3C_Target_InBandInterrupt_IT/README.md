## <b>I3C_Target_InBandInterrupt_IT Example Description</b>
How to handle an In-Band-Interrupt event to an I3C Controller

      - Board: NUCLEO-H563ZI's (embeds a STM32H563ZI device)
      - SCL Pin: PB8 (Arduino SCL/D15 CN6 pin 2, Morpho CN5 pin3) to PB8 (Arduino SCL/D15 CN6 pin 2, Morpho CN5 pin3)
      - SDA Pin: PB9 (Arduino SDA/D14 CN6 pin 4, Morpho CN5 pin5) to PB9 (Arduino SDA/D14 CN6 pin 4, Morpho CN5 pin5)
      Connect GND between each board
      Use short wire as possible between the boards or twist an independent ground wire on each I3C lines
      mean one GND twist around SCL and one GND twist around SDA to help communication at 12.5Mhz.

At the beginning of the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 250 MHz.

The I3C peripheral configuration and I3C resources (CLOCK, GPIO and NVIC) are ensured by the MX_I3C1_Init() function.
User may update this function to change I3C configuration.

The I3C communication is then initiated.
The project is split in two workspaces:
the Controller Board (I3C_Controller_InBandInterrupt_IT) and the Target Boards (I3C_Target_InBandInterrupt_IT)

- Target Boards
  The HAL_I3C_Tgt_Config(), the HAL_I3C_SetConfigFifo(), and the HAL_I3C_ActivateNotification() functions
  allow respectively the configuration of the Target descriptor,
  the configuration of the internal hardware FIFOs and the enabling of Asynchronous catching event in Target mode using Interrupt.

  The MX_I3C1_Init() function allow the configuration of the internal hardware FIFOs,
  the configuration of the Target own specific parameter, and the enabling of Asynchronous
  catching event in Target mode using Interrupt.
  The configuration of Interrupt allow the Target application to be inform when the Controller
  assign a Dynamic Address, and when Controller acknowledge the IBI request.
  The Controller send data at 12.5Mhz during Push-pull phase.
  
  The Handle_IBI_Target() functions allow the request of the In-Band-Interrupt request in Target mode using Interrupt.

Target side:
In a first step until Dynamic Address Assignment procedure from the Controller, the Target wait in a no activity loop.
Then, at reception of the Dynamic Address Assignment procedure from the Controller, the Target start the sending of its payload.
The end of reception of a Dynamic address is monitored by the reception of Target_Event_Treatment_Callback() on Target side.

In a second step, the user press the USER push-button on a Target Board,
I3C Target starts the communication by sending the In-Band-Interrupt request through Handle_IBI_Target() to the Controller.

This second action can be done at the same time or independently on one or other Targets.
In fact, after this starting In-Band-Interrupt procedure, the I3C Controller catch the event and request
a private communication with the Target which have send and have get acknowledge of the In-Band-Interrupt event.

The end of IBI communication is monitored by the reception of Target_Event_Treatment_Callback() on Target side.

The whole IBI process is in an infinite loop for the Target to be able to send other IBI requests to the Controller.

NUCLEO-H563ZI's LEDs can be used to monitor the transfer status:
 - LED1 is toggle each time an In-Band-Interrupt process is completed.
 - LED1 is toggle slowly when there is an error in In-Band-Interrupt process. .

### <b>Keywords</b>

Connectivity, Communication, I3C, Interrupt, Controller, Target, Dynamic Address Assignment, In Band Interrupt

### <b>Directory contents</b>

  - I3C/I3C_Target_InBandInterrupt_IT/Inc/stm32h5xx_it.h            I3C interrupt handlers header file
  - I3C/I3C_Target_InBandInterrupt_IT/Inc/main.h                    Header for main.c module
  - I3C/I3C_Target_InBandInterrupt_IT/Inc/stm32_assert.h            Template file to include assert_failed function
  - I3C/I3C_Target_InBandInterrupt_IT/Src/stm32h5xx_it.c            I3C interrupt handlers
  - I3C/I3C_Target_InBandInterrupt_IT/Src/main.c                    Main program
  - I3C/I3C_Target_InBandInterrupt_IT/Src/system_stm32h5xx.c        stm32h5xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32H563ZI devices.

  - This example has been tested with NUCLEO-H563ZI board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-H563ZI Set-up

    - Use short wire as possible between the boards or twist an independent ground wire on each I3C lines
      mean one GND twist around SCL and one GND twist around SDA to help communication at 12.5Mhz.
    - Connect I3C_SCL line of Controller board (PB8 Arduino SCL/D15 CN6 pin 2, Morpho CN5 pin3) to I3C_SCL line of Target Board (PB8 Arduino SCL/D15 CN6 pin 2, Morpho CN5 pin3).
    - Connect I3C_SDA line of Controller board (PB9 Arduino SDA/D14 CN6 pin 4, Morpho CN5 pin5) to I3C_SDA line of Target Board (PB9 Arduino SDA/D14 CN6 pin 4, Morpho CN5 pin5).
    - Connect GND of Controller board to GND of Target Boards.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into Controller memory (I3C_Controller_InBandInterrupt_IT)
 - Then rebuild all files and load your image into Target memory (I3C_Target_InBandInterrupt_IT)
 - Run the Controller before run the Target.
 This sequence will prevent a false startup phase on Target side
 as there is no high level on the bus, if the Target is started before the Controller.
