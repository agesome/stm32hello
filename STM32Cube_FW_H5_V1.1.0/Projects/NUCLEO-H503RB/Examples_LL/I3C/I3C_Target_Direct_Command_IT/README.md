## <b>I3C_Target_Direct_Command_IT Example Description</b>

How to handle a Direct Command procedure between an I3C Controller and an I3C Target,
using Controller in Interrupt.

      - Board: NUCLEO-H503RB's (embeds a STM32H503RB device)
      - SCL Pin: PB6 (Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3) to PB6 (Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3)
      - SDA Pin: PB7 (Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5) to PB7 (Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5)
      Connect GND between each board
      Use short wire as possible between the boards or twist an independent ground wire on each I3C lines
      mean one GND twist around SCL and one GND twist around SDA to help communication at 12.5Mhz.

At the beginning of the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 250 MHz.

The I3C peripheral configuration and I3C resources (CLOCK, GPIO and NVIC) are ensured by the MX_I3C1_Init() function.
User may update this function to change I3C configuration.

The I3C communication is then initiated.
The project is split in two workspaces:
the Controller Board (I3C_Controller_Direct_Command_IT) and the Target Board (I3C_Target_Direct_Command_IT)

- Target Board
  The MX_I3C1_Init() function allow the configuration of the internal hardware FIFOs,
  the configuration of the Target own specific parameter, and the enabling of Asynchronous
  catching event in Target mode using Interrupt.
  The configuration of Interrupt allow the Target application to be inform when the Controller
  assign a Dynamic Address, Get or Set CCC command code.

  The Controller send data at 12.5Mhz during Push-pull phase.

In a first step the Target wait the assignation of a proper associated Dynamic Address from the Controller.

In a second step, until Common Command Code procedure from the Controller,
the Target wait in a no activity loop.
Then, at reception of the first Common Code procedure from the Controller,
the Target start the sending or receiving of the CCC additional data depending of Common Command Code.

This sending or receiving of additional data is totally manage by internal hardware state machine,
only end of CCC procedure is treated on software part through the callback Target_Event_Treatment_Callback().

Each time a Set CCC command is confirmed treated through Target_Event_Treatment_Callback(),
the associated data is compared with the expected value.

Each time a Get or Set CCC command is confirmed treated through Target_Event_Treatment_Callback(), the LED2 is toggle.

NUCLEO-H503RB's LEDs can be used to monitor the transfer status:
 - LED2 is toggle each time a Command Code process is treated on hardware side.
 - LED2 is toggle slowly when there is an error in Command Code process.  

### <b>Keywords</b>

Connectivity, Communication, I3C, Interrupt, Controller, Target, Dynamic Address Assignment, Direct Command,
Transmission, Reception

### <b>Directory contents</b>

  - I3C/I3C_Target_Direct_Command_IT/Inc/stm32h5xx_it.h            I3C interrupt handlers header file
  - I3C/I3C_Target_Direct_Command_IT/Inc/main.h                    Header for main.c module
  - I3C/I3C_Target_Direct_Command_IT/Inc/stm32_assert.h            Template file to include assert_failed function
  - I3C/I3C_Target_Direct_Command_IT/Src/stm32h5xx_it.c            I3C interrupt handlers
  - I3C/I3C_Target_Direct_Command_IT/Src/main.c                    Main program
  - I3C/I3C_Target_Direct_Command_IT/Src/system_stm32h5xx.c        STM32H5xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32H503RB devices.

  - This example has been tested with NUCLEO-H503RB board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-H503RB Set-up

    - Use short wire as possible between the boards or twist an independent ground wire on each I3C lines
      mean one GND twist around SCL and one GND twist around SDA to help communication at 12.5Mhz.
    - Connect I3C_SCL line of Controller board (PB6 Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3) to I3C_SCL line of
      Target Board (PB6 Arduino SCL/D15 CN5 pin 10, Morpho CN10 pin3).
    - Connect I3C_SDA line of Controller board (PB7 Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5) to I3C_SDA line of
      Target Board (PB7 Arduino SDA/D14 CN5 pin 9, Morpho CN10 pin5).
    - Connect GND of Controller board to GND of Target Board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following:

 - Open your preferred toolchain
 - Rebuild all files and load your image into Controller memory (I3C_Controller_Direct_Command_IT)
 - Then rebuild all files and load your image into Target memory (I3C_Target_Direct_Command_IT)
 - Run the Controller in debug mode before run the Target in normal mode.
 This sequence will prevent a false startup phase on Target side
 as there is no high level on the bus, if the Target is started before the Controller.
