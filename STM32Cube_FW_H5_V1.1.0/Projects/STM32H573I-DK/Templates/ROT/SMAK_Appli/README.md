## <b>SMAK_Appli Template Description</b>

This project provides a Secure Manager boot path reference template. Boot is performed through Secure Manager boot path after authenticity and integrity checks of the project firmware
images.

This project template is based on the STM32Cube HAL API.

At the beginning of the main program, the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.

The SystemClock_Config() function is used to configure the system clock (SYSCLK)
  
This project is targeted to build a <u>non-secure application</u> that can be used after having installed the Secure Manager Package.

Please remember that on system with security enabled, the system always boots in secure and
the secure application is responsible for launching the non-secure application. 

This project mainly shows how to configure a non-secure application for Secure Manager boot path:
  - Linker file (Code and sram placement)
  - System Clock configuration (SystemInit() and SystemClock_Config())
  - IDE settings: Flash loader (TZ-Closed), Software Reset
  - IDE Postbuild command (TPC)

The maximum system clock frequency at 250Mhz is configured.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.
 
### <b>Keywords</b>

TrustZone, Secure Manager, SMAK, Boot path, Root Of Trust

### <b>Directory contents</b>

  - SMAK_Appli/Inc/main.h                      Header for main.c module
  - SMAK_Appli/Inc/stm32h5xx_hal_conf.h        HAL configuration file
  - SMAK_Appli/Inc/stm32h5xx_it.h              Interrupt handlers header file
  - SMAK_Appli/Inc/stm32h573i_discovery_conf.h BSP configuration file
  - SMAK_Appli/Src/main.c                      Main program
  - SMAK_Appli/Src/stm32h5xx_hal_msp.c         HAL MSP file
  - SMAK_Appli/Src/stm32h5xx_it.c              Interrupt handlers
  - SMAK_Appli/Src/system_stm32h5xx_ns.c       STM32H5xx system source file
  - SMAK_Appli/Binary                          Application firmware image (application binary + MCUBoot header and metadata)
  
### <b>Hardware and Software environment</b>

  - This template runs on STM32H573xx devices with Secure Manager Package
  - This template has been tested with STMicroelectronics STM32H573I-DK (MB1677)
    board and can be easily tailored to any other supported device
    and development board.  
	
### <b>How to use it ?</b>

This project is targeted to boot through <b>Secure Manager boot path</b>.

<u>Before compiling the project, you should first start the Secure Manager Package provisioning process</u>.

The <b>provisioning process</b> (ROT_Provisioning/SM/provisioning.bat) is divided in 2 majors steps :

  - Step 1 : Configuration
     - General configuration
     - OEM keys configuration
     - DA configuration
     - Option Bytes configuration
	 - SFI keys configuration
     - SFI generation

  - Step 2 : Installation
     - Option Bytes programming
     - Secure installation of the Secure Manager Package

After these steps, the Secure Manager Package is installed on the device, and the product state is TZ-CLOSED. 

It is now possible to build, flash and debug Non-Secure application, thanks to a integrated prebuild command in the application that makes it compatible with the Secure Manager boot path.
In order to make the program work, you must do the following :

 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

It is still possible to execute a regression with the Debug Authentication feature.
To do it, scripts (regression.bat & dbg_auth.bat) are available in the ROT_provisioning/DA folder.

For more details, refer to Wiki article available here : https://wiki.st.com/stm32mcu/wiki/Category:Security

     
