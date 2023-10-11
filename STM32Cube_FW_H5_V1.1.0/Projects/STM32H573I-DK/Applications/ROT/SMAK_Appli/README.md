## <b>SMAK_Appli application Description</b>

This project provides a Secure Manager boot path application example. Boot is performed through Secure Manager boot path after authenticity and integrity checks of the project firmware
images.

This project is targeted to build a <u>non secure application</u>, that can be used after having installed the Secure Manager Package.

On system with security enabled, the system always boots in secure and 
the secure application is responsible for launching the non-secure application. 

This project mainly shows how to use Secure Services offered by the Secure Manager to Non-Secure application, through
PSA APIs: Internal Trusted Storage, Cryptography, Initial Attestation, Firmware Update.

The application will display a menu on the console allowing to use the Secure Services.

The maximum system clock frequency at 250Mhz is configured.

### <b>Keywords</b>

TrustZone, Secure Manager, SMAK, Boot path, Root Of Trust, PSA API

### <b>Directory contents</b>


  - ROT/SMAK_Appli/Src/com.c                              Communication
  - ROT/SMAK_Appli/Src/common.c                           Common
  - ROT/SMAK_Appli/Src/cryp.c                             Cryptography main menu test
  - ROT/SMAK_Appli/Src/crypto_tests_common.c              Cryptography  test
  - ROT/SMAK_Appli/Src/eat.c                              Initial attestation test
  - ROT/SMAK_Appli/Src/fwu.c                              Firmware update test
  - ROT/SMAK_Appli/Src/its.c                              Internal trusted storage test
  - ROT/SMAK_Appli/Src/main.c                             Secure Main program
  - ROT/SMAK_Appli/Src/stm32h5xx_hal_msp.c                HAL MSP function
  - ROT/SMAK_Appli/Src/stm32h5xx_it.c                     Interrupt handlers
  - ROT/SMAK_Appli/Src/system_stm32h5xx_ns.c              Non-secure STM32H5xx system clock configuration file
  - ROT/SMAK_Appli/Src/ymodem.c                           Protocol ymodem
  - ROT/SMAK_Appli/Inc/com.h                              Communication header file
  - ROT/SMAK_Appli/Inc/common.h                           Common header file
  - ROT/SMAK_Appli/Inc/cryp.h                             Cryptography main menu test header file
  - ROT/SMAK_Appli/Inc/crypto_tests_common.h              Cryptography  test header file
  - ROT/SMAK_Appli/Inc/crypto_tests_config.h              Cryptography  test config
  - ROT/SMAK_Appli/Inc/eat.h                              Initial attestation test header file
  - ROT/SMAK_Appli/Inc/fwu.h                              Firmware update test header file
  - ROT/SMAK_Appli/Inc/its.h                              Internal trusted storage test header file
  - ROT/SMAK_Appli/Inc/main.h                             Main program header file
  - ROT/SMAK_Appli/Inc/stm32h5xx_hal_conf.h               HAL Configuration file
  - ROT/SMAK_Appli/Inc/stm32h5xx_it.h                     Interrupt handlers header file
  - ROT/SMAK_Appli/Inc/test_framework.h                   General test APIs
  - ROT/SMAK_Appli/Inc/test_framework_error_codes.h       General test errors code
  - ROT/SMAK_Appli/Inc/updatelinker.h                     Variable definition for linker file
  - ROT/SMAK_Appli/Inc/ymodem.h                           Protocol ymodem header file
  - ROT/SMAK_Appli/Binary                                 Application firmware image (application binary + MCUBoot header and metadata)
  
### <b>Hardware and Software environment</b>

  - This application runs on STM32H573xx devices with Secure Manager Package
  - This application has been tested with STMicroelectronics STM32H573I-DK (MB1677)
    board and can be easily tailored to any other supported device
    and development board.  
  - To print the application menu in your UART console you have to configure it using these parameters:
    Speed: 115200, Data: 8bits, Parity: None, stop bits: 1, Flow control: none.

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

After application startup, check in your "UART console" the menu is well displayed:
  ```
  =================== Main Menu =============================
   Internal Trusted Storage ----------------------------- 1
   Cryptography ----------------------------------------- 2
   Initial Attestation ---------------------------------- 3
   Firmware Update -------------------------------------- 4
   Selection :
  ```

To use the different secure services, select the function of your choice.

For more details, refer to Wiki article available here : https://wiki.st.com/stm32mcu/wiki/Category:Security
