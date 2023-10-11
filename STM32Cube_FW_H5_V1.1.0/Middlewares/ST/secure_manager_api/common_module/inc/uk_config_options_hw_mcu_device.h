/**
 * @copyright
 * COPYRIGHT NOTICE:
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 * @file          uk_config_options_hw_mcu_device.h
 * @brief         uKernel API - Platform's MCU Device specific uKernel Options.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This configuration file contains the Platform's MCU Device specific uKernel
 *  Options, that is C-Constant values for uKernel internal parameters that
 *  are dependent of the uKernel Target, of the MCU Device used, and of its
 *  associated MCU Family and MCU Core.
 * This file is part of the ukApp SDK (the defined uKernel Options are made
 *  available to ukApps for their compilation) and is specific to a given
 *  uKernel Target and a given Platform.
 *
 * As example, some Platform's MCU Device specific uKernel Options are:
 *  - MCU Clocks Parameters configuration.
 *  - Debug LED Configuration.
 *
 * This file supports the following Platform MCU Device:
 *   - STMicroelectronics
 *    + STM32Hx family
 *     --- STM32H573xx
 *
 * @warning This file is specific to a given uKernel Target and MCU Device.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target and Platform.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @implementation To ease uKernel Configuration definition and maintenance
 *  for several Platform MCU Devices, the definitions relative to the MCU
 *  Family and the definitions relative to MCU Core are done in dedicated
 *  separate include files (which are included at the end of this file).
 *
 * @implementation This configuration file "uk_config_options_hw_mcu_device.h"
 *  is selected for inclusion by adding the following directory in the compiler
 *  include files configuration:
 *   "ukernel_api/target/<target>/uk/include/config/hw/mcu/device/<vendor>/<family>/<device>"
 *  This directory, which is set only in the configuration of the compiler
 *  include files (no reference in source code), is built using the following
 *  directory definitions (all in lower case):
 *   - <target>: Target Name
 *     Eclipse Build Variable: BVukTARGET_NAME__lc
 *   - <vendor>: Device vendor shortname
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_VENDOR__lc
 *   - <family>: Device family shortname
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_FAMILY__lc
 *   - <device>: Device name
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_DEVICE__lc
 *
 * @implementation This file has a similar purpose and usage as the
 *  "uk_config_options.h" file, but it contains only the uKernel Options that
 *  may depend on the chosen Platform MCU Device (see "uk_config_options.h"
 *  file for more details on its contents and usage).
 * It is a child file of "uk_config_options.h" file and shall be only included
 *  by it.
 ******************************************************************************
 * @addtogroup    uKernelAPI
 * @{
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_CONFIG_OPTIONS_HW_MCU_DEVICE_H)

/* Enforces that this file is included by 'uk_config_options.h' file. */
#if !defined(UK_CONFIG_OPTIONS_H_INSIDE)
#error 'The "uk_config_options_hw_mcu_device.h" include file shall be included only in the "uk_config_options.h" file'
#endif /* !defined(UK_CONFIG_OPTIONS_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_CONFIG_OPTIONS_HW_MCU_DEVICE_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONFIG_OPTIONS_HW_MCU_DEVICE_H_INSIDE

/*__________________________________________________________________________*/
/* Source the include files needed by the uKernel Configuration file. */

/* Add inclusion of parent include file of the Code Module only to help IDE
 *  parsing. */
#include "uk_config_options.h"


/* ######################################################################## */
/*            PLATFORM MCU DEVICE SPECIFIC - CONFIGURATION CHECK            */
/* ######################################################################## */
/* Platform MCU Device specific consistency and implementation checks. */

/* Enforce that this file supports the used MCU Device. */
#if defined(SukCONFIG_HW_MCU_DEVICE_STM_STM32H5XX_STM32H573)
#else
  #error "This include file supports only the following MCU Device: STM32H573"
#endif


/* ######################################################################## */
/*                    UKERNEL OPTIONS / MCU DEVICE SPECIFIC                 */
/* ######################################################################## */
/* Hereafter are defined the Platform's MCU Device specific uKernel Options
 *  (i.e. C-Constant values of uKernel configuration parameters depending of
 *  the MCU Device) that are part of the uKernel API of the uKernel Target
 *  used.
 * Each of the uKernel Option is defined as a C-Constant value. The definition
 *  is casting the value with the C-Type associated to the nature of the
 *  uKernel Options, excepted when defining a number of supported elements (as
 *  then the value may be used for defining arrays or tables, and typed values
 *  are not supported by C-Compiler in such definitions).
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @implementation A Platform specific uKernel Option <ooo> is defined by
 *  associating its corresponding label DukCONFIG_OPTION_HW_<ooo> to the wanted
 *  parameter value using the C-Preprocessor '#define'.
 * @implementation A specific file section below is reserved for the Platform
 *  specific uKernel Debug Options.
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Target used.
 */


/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL OPTIONS / MCU DEVICE - CLOCK CONFIGURATION            */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the count of defined MCU Clocks
 *  Sets.
 *
 * Definition of the uKernel Option C-Constant of the count of defined MCU
 *  Clocks Sets in uKernel Configuration.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_LIST.
 *
 * Default value: /.
 * Supported values: [1 ... 16].
 */
#define DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_COUNT                              \
    MukVAL_TYPED(TukCOUNT8,                                                   \
                 1                                                            \
                )

/**
 * @brief uKernel Option constant C-Array defining the list of MCU Clocks Set
 *  supported.
 *
 * Definition of the uKernel Option constant C-Array containing the list of
 *   MCU Clocks Set supported for the used MCU Family.
 * Each entry in this list contains an MCU Clocks Set. The entry index in this
 *  list corresponds to the MCU Clocks Set Index (see TukMCU_CLOCKS_SET_IDX).
 *
 * Each MCU Clocks Set contains an MCU Device's specific set of parameters
 *  for the MCU hardware clock module to configure the different clocks inside
 *  the MCU, and notably the CPU Core Clock used by the uKernel for its
 *  internal timings.
 *
 * @note: The documentation for this is ST RM0481, 11 RCC
 *
 * The set of parameters for this MCU Device contains the following elements:
 *  - (TukMAGIC32)EntryMagicStart32: Magic Number identifying the start of a
 *   MCU Clock Set Entry. It shall be equal to the value 0x8F79A510.
 *  - (TukFREQ32_hz)HSE: Frequency value of the HSE (external clock)
 *   in Hertz (Hz). If the HSI (internal oscillator) has to be used, then this
 *   value shall be set to null (0).
 *  - (TukUINT8)PLLM: Division Factor for the main PLL input clock.
 *   If the PLL is not used, then the Division Factor shall be set to null (0).
 *   The PLL input clock after this divider SHALL BE in the range
 *    [ 1Mhz ... 2Mhz ] (and as close as possible of 2Mhz). It is possible to
 *    use values outside this range, but we don't require or support it.
 *   Supported values is either 0 (PLL not used) or in the range [1 ... 63].
 *  - (TukUINT6)PLLN: Main multiplier value of the PLL VCO.
 *   The resulting PLL VCO frequency SHALL BE in the range
 *    [ 150Mhz ... 420Mhz ].
 *   Supported values in the range [3 ... 511].
 *  - (TukUINT8)PLLP: Output Divider value of the PLL for the main System
 *   Clock <SYSCLK>.
 *   Supported values in the range [ 2; 4 ... 128 ].
 *  - (TukUINT8)PLLQ: Output Divider value of the PLL for
 *   Supported values in the set [1 ... 128].
 *  - (TukUINT8)PLLR: Output Divider value of the PLL for
 *   Supported values in the range [1 ... 128].
 *  - (TukUINT8)AHB: AHB Prescaler for dividing main System Clock SYSCLK to
 *   provide HCLK and MCU Core Clocks.
 *   Supported values in the set { 1, 2, 4, 8, 16, 64, 128, 256, 512 }.
 *  - (TukUINT8)APB1: APB1 Prescaler for dividing HCLK to provide PCLK1
 *   Clock.
 *   Supported values in the set { 1, 2, 4, 8, 16 }.
 *  - (TukUINT8)APB2: APB2 Prescaler for dividing HCLK to provide PCLK2
 *   Clock.
 *   Supported values in the set { 1, 2, 4, 8, 16 }.
 *  - (TukUINT8)APB3: APB3 Prescaler for dividing HCLK to provide PCLK2
 *   Clock.
 *   Supported values in the set { 1, 2, 4, 8, 16 }.
 *  - (TukUINT8)FLAT: FLASH Latency in Wait State.
 *   Supported values in the range [0 ... 15].
 *  - (TukMAGIC32)EntryMagicEnd32: Magic Number identifying the end of a
 *   MCU Clock Set Entry. It shall be equal to the value (~0x8F79A510).
 *
 * The resulting CPU Core Clock Frequency from each parameters set SHALL BE
 *  higher than 1Mhz and lower than:
 *  - STM32H573xx: 250Mhz.
 *
 * @warning In case of an invalid entry in this list (valid set of parameters
 *  can be retrieved from MCU device documentation),the uKernel Initialization
 *  will fail with Fatal Error.
 *
 * @robustness The number of entries in this list is checked to be equal to
 *  DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_COUNT.
 *
 * @implementation If uKernel Low Power Mode is supported by the uKernel
 *  Target, then the uKernel may lower or disable some MCU Clocks for managing
 *  this uKernel Low Power Mode. It will automatically restore the MCU Clocks
 *  to the ones defined by the last MPU Clocks Set Index used once returning to
 *  uKernel Nominal Power Mode.
 *
 * @implementation The set of parameters of each entry depends of the MCU
 *  Device and of the Platform used, and thus may differs in regards of their
 *  counts and interpretation of their contents in function of the MCU Device
 *  and Platform used.
 *
 * @implementation In case of an invalid entry in this list, the uKernel
 *  Initialization will fail with uKernel FATAL Error.
 *
 * @usage The entry of index 0 is the default one used during uKernel
 *  Initialization.
 *  To change MCU Clocks configuration, another entry index can afterwards be
 *  selected by a ukProc with the appropriate credentials using uKernel
 *  Privileged Services (see ukPlatformSetAttribute() and
 *  DukPLATFORM_ATTRIBUTE_TAG_MCU_CLOCKS_SET_IDX).
 */
#define DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_LIST              {                \
  /* CLOCK IDX 0:
   *     SYSCLK = 250MhZ   Core = 250Mhz
   *     PCLK1 = 250Mhz    PCLK2 = 250Mhz
   *     FLASH LATENCY = 5 (This depends on the voltage, see 7.3.4)
   */                                                                         \
      {                                                                       \
      /* Magic Start    */              0x8F79A510UL,                         \
      /* HSE (Hz)       */              0,                                    \
      /* PLLM           */              32,                                   \
      /* PLLN           */              250,                                  \
      /* PLLP           */              2,                                    \
      /* PLLQ           */              2,                                    \
      /* PLLR           */              2,                                    \
      /* AHB            */              1,                                    \
      /* APB1           */              1,                                    \
      /* APB2           */              1,                                    \
      /* APB3           */              1,                                    \
      /* FLAT           */              5,                                    \
      /* Magic End      */              ~0x8F79A510UL,                        \
      },                                                                      \
                                                             }


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL OPTIONS / MCU DEVICE - SCHEDULING                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximal execution time
 *  authorized for a uKernel Call in CPU Core Clock ticks.
 *
 * Definition of the uKernel Option C-Constant defining the maximal execution
 *  time authorized for a uKernel Call in CPU Core Clock ticks.
 * If this execution time is exceeded, it will trigger a uKernel FATAL Error.
 *
 * @robustness If this uKernel Option C-Constant is defined, then this maximal
 *  execution time is enforced upon each uKernel Call.
 *
 * @warning If this uKernel Option C-Constant value is defined, the uKernel
 *  will enforce that the Systick period in CPU Core Clock ticks unit is at
 *  least two times this value. If an updated Systick period does not respect
 *  this condition, the update will be rejected.
 *
 * @implementation This execution time is in CPU Core Clock ticks unit in order
 *  to be independent of the MCU Clocks parameters chosen (as the code remains
 *  the same whatever the CPU Core Clock, the number of ticks is also roughly
 *  constant, excepting possible additional wait states required above a
 *  certain CPU Core Clock frequency).
 *
 * @usage This maximal execution time allows to enforce the maximal reaction
 *  time of the uKernel upon various events (Peripheral IRQ, ukProc scheduling
 *  switch, ...), and thus can be used to predict maximal latency of a ukProc.
 *
 * @usage If there is no need of monitoring maximal execution time, then this
 *  uKernel Option C-Constant may not be defined (if not defined, it will
 *  disable the associated control mechanism).
 *
 * Default value: 100000
 * Supported values: (undefined), [1000 ... 1000000].
 */
#define DukCONFIG_OPTION_HW_UKERNEL_CALL_TIME_LIMIT_cputick                   \
    MukVAL_TYPED(TukTIME32_tick, 150000UL)



/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL OPTIONS / MCU DEVICE - EXTRA ADDRESS BLOCK            */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the count of defined Address
 *  Blocks Authorized for Extra Address Blocks.
 *
 * Definition of the uKernel Option Constant of the count of defined Address
 *  Blocks Authorized for Extra Address Blocks.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_OPTION_HW_ADDRESSBLOCK_EXTRA_AUTHORIZED_LIST.
 *
 * Default value: /.
 * Supported values: [0 ... 32].
 */
#define DukCONFIG_OPTION_HW_ADDRESSBLOCK_EXTRA_AUTHORIZED_COUNT               \
            MukVAL_TYPED(TukCOUNT8,                                           \
                         1                                                    \
                        )

/**
 * @brief uKernel Option constant C-Array defining the list of Address Block
 *  Authorized for Extra Address Blocks used by a ukApp.
 *
 * Definition of the uKernel Option constant C-Array containing the list of
 *  Address Blocks Authorized for the Extra Address Blocks used by a ukApp
 *  for the used MCU Family.
 *
 * Each entry in the C-Array defines an Address Block Authorized of C-Type
 *  TukADDRESSBLOCK containing the following fields:
 *  - (TukADDRESS32)Start32: Start address of the Address Block.
 *  - (TukLENGTH32)Length32: Length in bytes of the Address Block.
 *
 * @robustness The number of entries in this list is checked to be equal to
 *  DukCONFIG_OPTION_HW_ADDRESSBLOCK_EXTRA_AUTHORIZED_COUNT.
 *
 * @implementation If an Address Block entry has its field <AddressStart>
 *  equals to DukADDRESS_IGNORE, then the entry is ignored.
 *
 * @implementation In case of an invalid entry in this list, the uKernel
 *  Initialization will fail with uKernel FATAL Error.
 *  An invalid entry may be due to the following reasons:
 *   - Defined Address Block not fully aligned on 32-bit.
 *   - Defined Address Block not in the MCU Peripheral Block.
 *
 * @usage If an Extra Address Block defined in a ukApp Descriptor has not its
 *  address range fully contained in one of the Address Block defined in this
 *  list, then the ukApp Descriptor to which it belongs is invalid.
 */
#define DukCONFIG_OPTION_HW_ADDRESSBLOCK_EXTRA_AUTHORIZED_LIST   {            \
            /* #01:               */   {                                      \
            /*  - Start32        */        (TukADDRESS32)0x50000000UL,        \
            /*  - Length32       */        (TukLENGTH32) 0x0FFFFFFFUL         \
                                       }                                      \
                                                                 }


/**
 * @brief uKernel Option constant C-Array defining the list of Address Blocks
 *  reserved for the kernel.
 *
 * Definition of the uKernel Option constant containing the list of Address
 *  Blocks reserved for the kernel.
 *
 * The address blocks in this list are not allowed to appear in the ukApp
 *  Extra Address Blocks.
 *
 * Each entry in the C-Array defines an Address Block Authorized of C-Type
 *  TukADDRESSBLOCK containing the following fields:
 *  - (TukADDRESS32)Start32: Start address of the Address Block.
 *  - (TukLENGTH32)Length32: Length in bytes of the Address Block.
 *
 * @implementation In case no Address Block needs to be prevented from
 *  appearing in ukApp Descriptors, this list can simply be 0 initialized.
 */
#define DukCONFIG_OPTION_HW_ADDRESSBLOCK_EXTRA_RESERVED_LIST {                \
    {                                                                         \
        .Start32  = RCC_BASE,                                                 \
        .Length32 = 0x400UL,                                                  \
    },                                                                        \
    {                                                                         \
        .Start32  = GPIOA_BASE,        /* Starting at GPIOA */                \
        .Length32 = 0x2400UL,          /* All 9 ports (A-I) */                \
    },                                                                        \
                                                             }


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL OPTIONS / MCU DEVICE - MCU REGISTERS              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the count of authorized MCU
 *  Register Ranges that are defined.
 *
 * Definition of the uKernel Option C-Constant defining the count of authorized
 *  MCU Register Ranges that are defined.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_OPTION_HW_MCUREGRANGE_AUTHORIZED_LIST.
 *
 * Default value: /.
 * Supported values: [0 ... 64].
 */
#define DukCONFIG_OPTION_HW_MCUREGRANGE_AUTHORIZED_COUNT                      \
    MukVAL_TYPED(TukCOUNT8,                                                   \
                 26                                                           \
                )

/**
 * @brief uKernel Option constant C-Array defining the list of MCU Register
 *  Ranges authorized for ukProcs.
 *
 * Definition of the uKernel Option constant C-Array containing the list of MCU
 *  Register Ranges authorized for ukProcs.
 *
 * The MCU Register whose access is restricted to CPU Privileged Execution Mode
 *  can be made accessible to ukProc through uKernel Privileged Services by
 *  being defined in this list (direct access is not possible from ukApp code,
 *  as ukProc are running in CPU User Execution Mode).
 *
 * Each entry in the C-Array defines an MCU Register Descriptor of C-Type
 *  TukMCUREGRANGE_DESCRIPTOR containing the following fields:
 *  - (TukADDRESS32)MCURegRangeFirstAddress: 32-bit address of the first MCU
 *   Register allowed to be accessed from ukApp code.
 *  - (TukADDRESS32)MCURegRangeLastAddress: 32-bit address of the last MCU
 *   Register allowed to be accessed from ukApp code.
 *  - (TukBITMASK32)MCURegisterReadBitmask32: 32-bit bitmask where each bit
 *   set to 1 corresponds to a bit allowed to be read from the MCU Registers.
 *  - (TukBITMASK32)MCURegisterWriteBitmask32: 32-bit bitmask where each bit
 *   set to 1 corresponds to a bit allowed to be written in the MCU Registers.
 *
 * @robustness The number of entries in this list is checked to be equal to
 *  DukCONFIG_OPTION_HW_MCUREGRANGE_AUTHORIZED_COUNT.
 *
 * @implementation In case of an invalid entry in this list, the uKernel
 *  Initialization will fail with uKernel FATAL Error.
 *  An invalid entry may be due to the following reasons:
 *   - Defined MCU Register Address usage exclusively reserved for uKernel (i.e.
 *    MCU Systick or MCU MPU).
 *   - Defined MCU Register Address not in the MCU System Control Block or
 *    MCU Peripheral Block.
 *
 * @usage The MCU Registers Authorized contained in this list are used to
 *  define the MCU Registers that can be accessed through the following uKernel
 *  Privileged Services:
 *  - ukMCURegisterRead()
 *  - ukMCURegisterWrite()
 */
#define DukCONFIG_OPTION_HW_MCUREGRANGE_AUTHORIZED_LIST {                     \
    /* #01:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->OPTSR_CUR,    \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->OPTSR_CUR,    \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #02:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->NSEPOCHR_CUR, \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->NSEPOCHR_CUR, \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #03:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->SECEPOCHR_CUR,\
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->SECEPOCHR_CUR,\
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #04:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->OPTSR2_CUR,   \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->OPTSR2_CUR,   \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #05:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->NSBOOTR_CUR,  \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->NSBOOTR_CUR,  \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #06:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->SECBOOTR_CUR, \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->SECBOOTR_CUR, \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #07:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->SECWM1R_CUR,  \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->SECWM1R_CUR,  \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #08:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->WRP1R_CUR,    \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->WRP1R_CUR,    \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #09:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->SECWM2R_CUR,  \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->SECWM2R_CUR,  \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #10:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &FLASH->WRP2R_CUR,    \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &FLASH->WRP2R_CUR,    \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000000UL, },                     \
    /* #11:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOA->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOA->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #12:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOB->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOB->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #13:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOC->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOC->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #14:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOD->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOD->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #15:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOE->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOE->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #16:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOF->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOF->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #17:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOG->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOG->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #18:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOH->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOH->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #19:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &GPIOI->MODER,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &GPIOI->HSLVR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #20:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &RCC->AHB1ENR,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &RCC->AHB1ENR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x0038D100UL, },                     \
    /* #21:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &RCC->AHB2ENR,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &RCC->AHB2ENR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x001F19FFUL, },                     \
    /* #22:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &RCC->AHB4ENR,        \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &RCC->AHB4ENR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00111880UL, },                     \
    /* #23:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &RCC->APB1LENR,       \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &RCC->APB1LENR,       \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,  /* Not WDG */         \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFF7FFUL, },                     \
    /* #24:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &RCC->APB1HENR,       \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &RCC->APB3ENR,        \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
    /* #25:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &DWT->CTRL,           \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &DWT->CTRL,           \
    /*  - MCURegisterReadBitmask32  */   0x00000001UL,                        \
    /*  - MCURegisterWriteBitmask32 */   0x00000001UL, },                     \
    /* #26:                         */ {                                      \
    /*  - MCURegRangeFirstAddress   */   (TukADDRESS32) &DWT->CYCCNT,         \
    /*  - MCURegRangeLastAddress    */   (TukADDRESS32) &DWT->CYCCNT,         \
    /*  - MCURegisterReadBitmask32  */   0xFFFFFFFFUL,                        \
    /*  - MCURegisterWriteBitmask32 */   0xFFFFFFFFUL, },                     \
}

/**
 * @brief uKernel Option C-Constant defining the total count of authorized MCU
 *  Registers that are defined.
 *
 * Definition of the uKernel Option C-Constant defining the total count of
 *  authorized MCU Registers that are defined.
 *
 * @usage This count SHALL correspond to the sum of the number of MCU Registers
 *  in all the ranges.
 *
 * Default value: /.
 * Supported values: [0 ... 2048].
 */
#define DukCONFIG_OPTION_HW_MCUREGISTER_AUTHORIZED_COUNT                      \
    MukVAL_TYPED(TukCOUNT32,                                                  \
                 127                                                          \
                )


/* //////////////////////////////////////////////////////////////////////// */
/*                  UKERNEL OPTIONS / MCU DEVICE - MCU FLASH                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the length of the Flash Sectors
 *  used for the ukApps Bundle Data Persistent Shared Block.
 *
 * Definition of the uKernel Option C-Constant of the length of the Flash
 *  Sectors used for the ukApps Bundle Data Persistent Shared Block.
 *
 * @implementation All the Flash Sectors in the uKernel ukApps Bundle Data
 *  Persistent Shared Block have this same length.
 *
 * Default value: /.
 * Supported values: { 2^<n> }, with <n> in [3 ... 24].
 */
#define DukCONFIG_OPTION_HW_UKAPPBUNDLE_DATA_PERSISTENT_SHARED_FLASH_SECTOR_LENGTH \
                                    MukVAL_TYPED(TukLENGTH16, 8192U)


/* //////////////////////////////////////////////////////////////////////// */
/*     UKERNEL OPTIONS / MCU DEVICE SPECIFIC - UKERNEL IMAGE UPDATE         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Configuration C-Constant defining the count of Address Blocks
 *  composing the uKernel Image Update Storage.
 *
 * Definition of the uKernel Configuration C-Constant of the count of Address
 *  Blocks composing the uKernel Image Update Storage in the Flash memory of
 *  the MCU Device.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_LIST.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE is supported.
 *
 * Default value: /.
 * Supported values: [0 ... 16].
 */
#define DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_COUNT   \
                                    MukVAL_TYPED(TukCOUNT8, 0U)


/**
 * @brief uKernel Option constant C-Array defining the list of Address Blocks
 *  composing the uKernel Image Update Storage.
 *
 * Definition of the uKernel Option constant C-Array containing the list of
 *  Address Blocks composing the uKernel Image Update Storage. Each Address
 *  Block part of the uKernel Update Image Storage shall be fully contained in
 *  only one Flash Bank (see DukCONFIG_HW_MCU_DEVICE_FLASH_BANK_LIST for the
 *  definition of the Flash Banks part of the MCU Flash memory of the used MCU
 *  Device).
 *
 * Each entry in the C-Array defines an Address Block of C-Type TukADDRESSBLOCK
 *  containing the following fields:
 *  - (TukADDRESS32)Start32: Start address of the Address Block.
 *  - (TukLENGTH32)Length32: Length in bytes of the Address Block.
 *
 * @robustness The number of entries in this list is checked to be equal to
 *  DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_COUNT.
 *
 * @implementation In case of an invalid entry in this list, the uKernel
 *  Initialization will fail with uKernel FATAL Error.
 *  An invalid entry may be due to the following reasons:
 *   - Defined Address Block is not fully aligned on 32-bit.
 *   - Previous Address Block entry has a higher Start Address than current
 *    entry.
 *   - Defined Address Block is not fully contained in a Flash Bank part of
 *    MCU Flash memory (see DukCONFIG_HW_MCU_DEVICE_FLASH_BANK_LIST for the
 *    definition of the Flash Banks part of the MCU Flash memory of the used
 *    MCU Device).
 *   - Defined Address Block is overlapping with one already used for other
 *    purpose by the uKernel Target:
 *     -- uKernel Core Code Block
 *     -- uKernel Configuration Custom Block
 *     -- ukApps Bundle Code Block
 *     -- ukApps Bundle Shared Data Block
 *     -- ukApps Bundle Persistent Data Block
 *
 * @usage The uKernel Image Update Storage Size is computed by adding the
 *  length of all the Address Blocks in this list.
 */
#define DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_LIST  { \
    /* #nn:              */                                                   \
    /*  - Start32        */                                                   \
    /*  - Length32       */                                                   \
                                                                    }


/* ######################################################################## */
/*              UKERNEL OPTIONS / MCU DEVICE SPECIFIC - DEBUG               */
/* ######################################################################## */
/* Hereafter are defined the Platform's MCU Device specific uKernel Debug
 *  Options (i.e. C-Constant values of uKernel configuration debug parameters
 *  depending of the MCU Device) that are part of the uKernel API of the
 *  uKernel Target used and of the debug functionalities offered by the
 *  uKernel.
 * These definitions are similar to the Platform's MCU Device specific uKernel
 *  Options above (and can also be used by the uKernel Core and ukApp
 *  implementations), but care has to be taken that they are NOT defined for
 *  a uKernel Target that is a Production Target.
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @implementation A Platform specific uKernel Debug Option <ooo> is defined by
 *  associating its corresponding label DukCONFIG_OPTION_HW_DEBUG_<ooo> to the
 *  wanted parameter value using the C-Preprocessor '#define'.
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Target used.
 * @note These options don't come from the MCU family obviously, but rather
 *  from the board that the MCU is place on.
 */

/* ROBUSTNESS: None of the uKernel Debug Options defined hereafter are
 *  supported if the uKernel compilation is aiming a Production Target. */
#if !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE)


/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL OPTIONS / MCU DEVICE - DEBUG - UART              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the count of defined UART Pin Map
 *  for UART Devices used as uKernel Reporting Device.
 *
 * Definition of the uKernel Option C-Constant of the count of defined UART Pin
 *  Map for UART Devices used as uKernel Reporting Device in uKernel
 *  Configuration.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_UART_PIN_MAP_LIST.
 *
 * Default value: /
 * Supported values: [0 ... 15].
 */
#define DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_UART_PIN_MAP_COUNT         \
    MukVAL_TYPED(TukCOUNT8,                                                   \
                 1                                                            \
                )

/**
 * @brief uKernel Option constant C-Array containing the list of UART Pin Maps
 *  for the UART Devices used as uKernel Reporting Devices.
 *
 * Definition of the uKernel Option constant C-Array containing the list of
 *  UART Pin Maps for the UART Devices used as uKernel Reporting Devices.
 *
 * The entries of this C-Array are used as follows for the uKernel Reporting
 *  Devices:
 *  - [0]: UART Debug Trace Interface (see uKernel Features
 *          SukcoreCONFIG_FEATURE_DEBUG_TRACE_UKERNEL_INTERFACE_UART,
 *          SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC_INTERFACE_UART).
 *
 * @warning In case of invalid configuration provided for a uKernel Reporting
 *  Device (invalid Port Label or Pin Number for the selected Platform, ...),
 *  the uKernel Initialization will fail with Fatal Error.
 *
 * @implementation The definition in this list are used in function of the
 *  uKernel Features selected: if an entry is not used, its contents is fully
 *  ignored (no check is performed on its validity).
 *
 * @implementation The structure used for the list in this uKernel Option
 *  shall be the same one as C-Type TukdevUART_PIN_MAP_DESCRIPTOR_ENTRY.
 *
 * @implementation The number of entries in this C-Array SHALL BE equal to
 *  DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_UART_PIN_MAP_COUNT.
 *
 * @note The values below are a reflection of a decision in the use of
 *  the resources of the Nucleo-H563 board.
 *
 * @note The alternate port configuration is found in the datasheet (ST
 *  DB4267), which is MCU package-specific.
 */
#if !defined(DUKBUILD_SPMH5_NUCLEO)
#define DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_UART_PIN_MAP_LIST    {     \
/* PIN MAP INDEX 0 */           {                                             \
    /*  UART Pin Map Magic Start */     DukdevUART_PIN_MAP_ENTRY_MAGIC32,     \
    /*  UART HW Entity ID        */     1,               /* USART1 */         \
    /*  GPIO Alternate           */     7,               /* ALTERNATE 7 */    \
    /*  GPIO Pin Name TX         */     { 'A', 9 },      /* PA9 */            \
    /*  GPIO Pin Name RX         */     { 'A', 10},      /* PA10*/            \
    /*  UART Pin Map Magic End   */     ~DukdevUART_PIN_MAP_ENTRY_MAGIC32,    \
                                },                                            \
                                                                        }
#else
#define DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_UART_PIN_MAP_LIST    {     \
/* PIN MAP INDEX 0 */           {                                             \
    /*  UART Pin Map Magic Start */     DukdevUART_PIN_MAP_ENTRY_MAGIC32,     \
    /*  UART HW Entity ID        */     3,               /* USART3 */         \
    /*  GPIO Alternate           */     7,               /* ALTERNATE 7 */    \
    /*  GPIO Pin Name TX         */     { 'D', 8 },      /* PD8 */            \
    /*  GPIO Pin Name RX         */     { 'D', 9 },      /* PD9 */            \
    /*  UART Pin Map Magic End   */     ~DukdevUART_PIN_MAP_ENTRY_MAGIC32,    \
                                },                                            \
                                                                        }
#endif


/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL OPTIONS / MCU DEVICE - DEBUG - SPI               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the count of SPI Pin Maps defined
 *  for SPIs Devices used as uKernel Reporting Device.
 *
 * Definition of the uKernel Option C-Constant of the count of SPI Pin Maps
 *  defined for SPI Devices used as uKernel Reporting Device in uKernel
 *  Configuration.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_SPI_PIN_MAP_LIST.
 *
 * Default value: /
 * Supported values: [0 ... 15].
 */
#define DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_SPI_PIN_MAP_COUNT          \
    MukVAL_TYPED(TukCOUNT8,                                                   \
                 0                                                            \
                )

/**
 * @brief uKernel Option constant C-Array containing the list of SPI Pin Map
 *  for the SPI Devices used as uKernel Reporting Devices.
 *
 * Definition of the uKernel Option constant C-Array containing the list of SPI
 *  Pin Map for the SPI Devices used as uKernel Reporting Devices.
 *
 * The entries of this C-Array are used as follows for the uKernel Reporting
 *  Devices:
 *  - (none)
 *
 * @warning In case of invalid configuration provided for an SPI Reporting
 *  Device (invalid Port Label or Pin Number for the selected Platform, ...),
 *  the uKernel Initialization will fail with Fatal Error.
 *
 * @implementation The definition in this list are used in function of the
 *  uKernel Features selected: if an entry is not used, its contents is fully
 *  ignored (no check is performed on its validity).
 *
 * @implementation The structure used for the list in this uKernel Option
 *  shall be the same one as C-Type TukdevSPI_PIN_MAP_DESCRIPTOR_ENTRY.
 *
 * @implementation The number of entries in this C-Array SHALL BE equal to
 *  DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_SPI_PIN_MAP_COUNT.
 */
#define DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_SPI_PIN_MAP_LIST     {     \
    /* PIN MAP INDEX N */                                                     \
    /*    SPI Pin Map Magic Start  */                                         \
    /*    SPI HW Entity ID         */                                         \
    /*    GPIO Alternate           */                                         \
    /*    GPIO Pin Name SCK        */                                         \
    /*    GPIO Pin Name MOSI       */                                         \
    /*    GPIO Pin Name MISO       */                                         \
    /*    GPIO Pin Name CS[DukdevCONFIG_OPTION_SPI_CS_LINE_COUNT] */          \
                                                                              \
                                                                              \
                                                                              \
                                                                              \
                                                                              \
                                                                              \
    /*    SPI Pin Map Magic End    */                                         \
                                                                              \
                                                                         }


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL OPTIONS / MCU DEVICE - DEBUG - LED                */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_DEBUG_LED)

/**
 * @brief uKernel Option C-Constant defining the count of defined Debug LED.
 *
 * Definition of the uKernel Option C-Constant of the count of defined Debug
 *  LED part of Debug LED Set.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_OPTION_HW_DEBUG_LED_LIST.
 *
 * Default value: /.
 * Supported values: [1 ... 16].
 */
#define DukCONFIG_OPTION_HW_DEBUG_LED_COUNT                                   \
    MukVAL_TYPED(TukCOUNT8,                                                   \
                 1                                                            \
                )

/**
 * @brief uKernel Option constant C-Array containing the list of Debug LEDs
 *  part of Debug LED Set.
 *
 * Definition of the uKernel Option constant C-Array containing the list of
 *  Debug LEDs part of Debug LED Set.
 * This list contains the configuration of each Debug LED which consists in the
 *  GPIO Pin to which it is connected to.
 * The index in this list corresponds to the Debug LED Index (see
 *  TukDEBUG_LED_IDX) of the defined Debug LED.
 *
 * Each entry in the C-Array defines a GPIO Pin of C-Type TukdevGPIO_PIN_NAME
 *  containing the following fields:
 *  - (TukCHAR)PortLabelASCII: 8-bit ASCII character referencing the GPIO port
 *   where the Debug LED is connected. The ASCII character is the suffix (in
 *   uppercase) used in the GPIO port name. The list of valid suffix depends
 *   of the selected Platform.
 *   The special value of a space character (' ') shall be used to
 *   indicate that no GPIO port is selected (no Debug LED is connected) for the
 *   corresponding index.
 *   Example of ASCII character referencing GPIO port name:
 *    + 'A': port GPIO A
 *    + 'H': port GPIO H
 *    + '0': port GPIO 0
 *    + ' ': No GPIO port selected (no Debug LED connected)
 *  - (TukIDX8)PinNumber: 8-bit index referencing the Pin Number in the GPIO
 *   port where the Debug LED is connected. The index range goes from 0 (first
 *   pin) up to the number of pin minus one of the selected GPIO port (in
 *   general GPIO ports support 16 or 32 pins; this is MCU and GPIO port
 *   dependent).
 *
 * @robustness The number of entries in this list is checked to be equal to
 *  DukCONFIG_OPTION_HW_DEBUG_LED_COUNT.
 *
 * @implementation In case of invalid configuration provided for a Debug LED
 *  (invalid GPIO Port Label or Pin Number for the selected Platform), the
 *  uKernel Initialization will fail with Fatal Error.
 */
#define DukCONFIG_OPTION_HW_DEBUG_LED_LIST {                                  \
         /*                     {  PortLabelASCII , PinNumber } */            \
         /*                     ------------------------------- */            \
         /*     LED IDX 0 */    {       ' '       ,     4     },              \
                                          }

#endif /* defined(SukCONFIG_FEATURE_DEBUG_LED) */

#endif /* !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE) */


/* ######################################################################## */
/*             UKERNEL OPTIONS / PLATFORM'S MCU FAMILY SPECIFIC             */
/* ######################################################################## */
/* Hereafter are sourced the definitions of the uKernel Options relative
 *  to the MCU Family to which belongs selected MCU Device.
 *
 * NOTE: To ease uKernel Configuration definition and maintenance for several
 *  MCU Devices, these definitions are managed in a dedicated include file
 *  for each MCU Family.
 */
#include "uk_config_options_hw_mcu_family_stm_stm32h5xx.h"


/* ######################################################################## */
/*              UKERNEL OPTIONS / PLATFORM'S MCU CORE SPECIFIC              */
/* ######################################################################## */
/* Hereafter are sourced the definitions of the uKernel Options relative
 *  to the MCU Core used in the selected MCU Device.
 *
 * NOTE: To ease uKernel Configuration definition and maintenance for several
 *  MCU Devices, these definitions are managed in a dedicated include file
 *  for each MCU Core.
 */
#include "uk_config_options_hw_mcu_core_arm_cmx.h"


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONFIG_OPTIONS_HW_MCU_DEVICE_H_INSIDE
#endif /* !defined(UK_CONFIG_OPTIONS_HW_MCU_DEVICE_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */
