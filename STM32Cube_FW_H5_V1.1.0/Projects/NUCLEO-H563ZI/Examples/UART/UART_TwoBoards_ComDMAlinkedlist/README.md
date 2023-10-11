## <b>UART_TwoBoards_ComDMAlinkedlist Example Description</b>

UART transmission (transmit/receive) in DMA mode using linkedlist between two boards.

    Board: NUCLEO-H563ZI (embeds a STM32H563ZI device)
    UART Instance : USART1
    Tx Pin: PB14 (pin 28 CN5)
    Rx Pin: PB15 (pin 26 CN5)

    Two identical boards are connected as shown on the picture above.
    Board 1: transmitting then receiving board
    Board 2: receiving then transmitting board

The user presses the User push-button on board 1.
Then, board 1 sends in DMA mode using linkedlist three message to board 2 that sends it back to
board 1 in DMA mode with linkedlist as well.
Finally, board 1 and 2 compare the received messages to that sent.
If the messages are the same, the test passes.

WARNING: as both boards do not behave the same way, "TRANSMITTER_BOARD" compilation
switch is defined in /Src/main.c and must be enabled
at compilation time before loading the executable in the board that first transmits
then receives.
The receiving then transmitting board needs to be loaded with an executable
software obtained with TRANSMITTER_BOARD disabled.

NUCLEO-H563ZI board LEDs are used to monitor the transfer status:

- While board 1 is waiting for the user to press the User push-button, its LED2 is
  blinking rapidly (100 ms period).
- While board 2 is waiting for the message from board 1, its LED2 is emitting
  a couple of flashes every half-second.
- When the test passes, LED1 on both boards is turned on, otherwise the test has failed.
- Once the transmission/reception processes are completed LED1 is turned on.
- If there is an initialization or transfer error, LED3 is turned on.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock for STM32U575xx Devices :
The CPU at 250 MHz.
The HCLK for AHB peripherals to run at 250 MHz.
The APB clock dividers APB1, APB2, APB3 peripherals to run at 250 MHz.

The UART is configured as follows:

    - BaudRate = 9600 baud
    - Word Length = 8 bits (8 data bits, no parity bit)
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Reception and transmission are enabled in the time

#### <b>Notes</b>

 1. When the parity is enabled, the computed parity is inserted at the MSB
    position of the transmitted data.

 2. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 3. The application need to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Connectivity, UART/USART, baud rate, RS-232, full-duplex, DMA, parity, stop bit,
Transmitter, Receiver, Asynchronous

### <b>Directory contents</b>

  - UART/UART_TwoBoards_ComDMAlinkedlist/Inc/linked_list.h           Linked list header file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Inc/main.h                  Main program header file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Inc/stm32h5xx_hal_conf.h    HAL configuration file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Inc/stm32h5xx_it.h          Interrupt handlers header file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Inc/stm32h5xx_nucleo_conf.h BSP Configuration file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Src/linked_list.c           Linked list source file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Src/main.c                  Main program source file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Src/stm32h5xx_hal_msp.c     HAL MSP module
  - UART/UART_TwoBoards_ComDMAlinkedlist/Src/stm32h5xx_it.c          Interrupt handlers source file
  - UART/UART_TwoBoards_ComDMAlinkedlist/Src/system_stm32h5xx.c      STM32H5xx system source file

### <b>Hardware and Software environment</b>

  - This example runs on STM32H563ZITx devices.

  - This example has been tested with two NUCLEO-H563ZI boards embedding
    a STM32H563ZITx device and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-H563ZI set-up
  
    - Connect a wire between 1st board PB14 pin (Uart Tx) and 2nd board PB15 pin (Uart Rx)
    - Connect a wire between 1st board PB15 pin (Uart Rx) and 2nd board PB14 pin (Uart Tx)
    - Connect 1st board GND to 2nd Board GND

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

- Open your preferred toolchain
- Rebuild all files and load your image into target memory
- Run the example

