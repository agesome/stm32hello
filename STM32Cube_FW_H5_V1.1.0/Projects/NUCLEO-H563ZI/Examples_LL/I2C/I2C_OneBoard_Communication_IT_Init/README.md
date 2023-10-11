## <b>I2C_OneBoard_Communication_IT_Init Example Description</b>

How to handle the reception of one data byte from an I2C slave device
by an I2C master device. Both devices operate in interrupt mode. The peripheral is initialized
with LL initialization function to demonstrate LL init usage.

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using only one NUCLEO-H563ZI.

The user can disable internal pull-up by opening ioc file.
For that, user can follow the procedure :

1- Double click on the I2C_OneBoard_Communication_IT_Init.ioc file

2- When CUBEMX tool is opened, select System Core category

3- Then in the configuration of GPIO/I2C1, change Pull-up to No pull-up and no pull-down for the both pins

4- Same action in the configuration of GPIO/I2C2, change Pull-up to No pull-up and no pull-down for the both pins

5- Last step, generate new code thanks to button "GENERATE CODE"

The example is updated with no pull on each pin used for I2C communication

I2C1 Peripheral is configured in Slave mode with EXTI (Clock 400Khz, Own address 7-bit enabled).
I2C2 Peripheral is configured in Master mode with EXTI (Clock 400Khz).
GPIO associated to User push-button is linked with EXTI.

LED1 blinks quickly to wait for user-button press.

Example execution:

Press the USER push-button to initiate a read request by Master.
This action will generate an I2C start condition with the Slave address and a read bit condition.
When address Slave match code is received on I2C1, an ADDR interrupt occurs.
I2C1 IRQ Handler routine is then checking Address Match Code and direction Read.
This will allow Slave to enter in transmitter mode and then send a byte when TXIS interrupt occurs.
When byte is received on I2C2, an RXNE interrupt occurs.
When RXDR register is read, Master auto-generate a NACK and STOP condition
to inform the Slave that the transfer is finished.
The NACK condition generate a NACK interrupt in Slave side treated in the I2C1 IRQ handler routine by a clear of NACK flag.
The STOP condition generate a STOP interrupt in both side (Slave and Master). I2C1 and I2C2 IRQ handler routine are then
clearing the STOP flag in both side.

LED1 is On if data is well received.

In case of errors, LED1 is blinking slowly (1s).

### <b>Keywords</b>

Connectivity, Communication, I2C, Master, Slave, Transmission, Reception, Fast mode

### <b>Directory contents</b>

  - I2C/I2C_OneBoard_Communication_IT_Init/Inc/stm32h5xx_it.h          Interrupt handlers header file
  - I2C/I2C_OneBoard_Communication_IT_Init/Inc/main.h                  Header for main.c module
  - I2C/I2C_OneBoard_Communication_IT_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_OneBoard_Communication_IT_Init/Src/stm32h5xx_it.c          Interrupt handlers
  - I2C/I2C_OneBoard_Communication_IT_Init/Src/main.c                  Main program
  - I2C/I2C_OneBoard_Communication_IT_Init/Src/system_stm32h5xx.c      STM32H5xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32H563ZITx devices.

  - This example has been tested with NUCLEO-H563ZI board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-H563ZI Set-up
    - Connect GPIOs connected to I2C1 SCL/SDA (PB.6 and PB.7)
    to respectively SCL and SDA pins of I2C2 (PF.1 and PF.0).
      - I2C1_SCL  PB.6 (CN8, pin 14) : connected to I2C2_SCL PF.1 (CN9, pin 19)
      - I2C1_SDA  PB.7 (CN8, pin 16) : connected to I2C2_SDA PF.0 (CN9, pin 21)

  - Launch the program
  - Press USER push-button to initiate a read request by Master
    then Slave send a byte.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

