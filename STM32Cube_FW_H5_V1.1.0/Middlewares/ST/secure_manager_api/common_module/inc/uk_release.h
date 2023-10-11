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
 * @file          uk_release.h
 * @brief         uKernel API - uKernel Release definitions.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 * This file contains the uKernel Release definitions exposed in the uKernel
 *  API relative to the uKernel Release used.
 * A uKernel Release definition is a constant value providing information on
 *  the elements used for compiling the uKernel Release (uKernel Core code
 *  version, ...), as well as the elements associated to the Customer to which
 *  is aimed the uKernel Release.
 *
 * The purpose of having some of these uKernel Release definitions part of the
 *  uKernel API is that they may be of interest for:
 *  - ukApp code: they allow to adapt and fine tune the ukApp implementation
 *   by using the same C-Constant parameters definitions than the ones of the
 *   uKernel Release used.
 *
 * Example of uKernel Release definitions:
 *  - uKernel version, corresponding to the uKernel Core implementation used.
 *  - Customer Configuration used for the uKernel Release.
 *  - uKernel Core Descriptor versions relative to uKernel Core implementation
 *   used.
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Release for a selected Customer.
 *
 * @robustness The uKernel Release definitions are taken into account only
 *  during the compilation of the uKernel Release used. It enforces that
 *  internal checks relative to the uKernel Release are 'hard-coded' in a
 *  uKernel Release code (this participates to minimize the attack surface of
 *  the uKernel).
 *
 * @warning This file is specific to a given uKernel Release.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Release.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @implementation During uKernel compilation for a given uKernel Release
 *  <target>, the "uk_release.h" file is placed in the directory
 *  "ukernel_api/target/<target>/uk/include/".
 *
 * @usage This file SHALL BE included before any other uKernel Configuration
 *  file present in the directory
 *  "ukernel_api/target/<target>/uk/include/config".
 ******************************************************************************
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_RELEASE_H)

/*__________________________________________________________________________*/
/* Enforces that the 'uk_config.h' file has already been included. */
#if !defined(UK_CONFIG_H)
 #error 'The "uk_release.h" include file shall be included only after the "uk_config.h" file'
#endif /* !defined(UK_CONFIG_H) */


/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_RELEASE_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_RELEASE_H_INSIDE



/* ######################################################################## */
/*                              UKERNEL RELEASE                             */
/* ######################################################################## */
/* Hereafter are defined the uKernel Release definitions that are part of the
 *  uKernel API of the uKernel Release used.
 * Each of the uKernel Release definition is defined as a C-Constant value.
 * The definition is casting the value with the C-Type associated to the nature
 *  of the uKernel Release, excepted when defining a number of supported
 *  elements (as then the value may be used for defining arrays or tables, and
 *  typed values are not supported by C-Compiler in such definitions).
 * @implementation A uKernel Release definition <rrr> is defined by associating
 *  its corresponding label DukRELEASE_<rrr> to the wanted parameter value
 *  using the C-Preprocessor '#define'.
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                  UKERNEL RELEASE - CUSTOMER CONFIGURATION                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Release C-Constant defining the <Customer> field of the
 *  Version of the ukApp Configuration file "ukapp_config_descriptor.h".
 *
 * Definition of the uKernel Release C-Constant for the <Customer> field of
 *  the Version of the ukApp Configuration file "ukapp_config_descriptor.h".
 */
#define DukRELEASE_CUSTOMER_CONFIG_CUSTOMER     0x53542D4DULL /* 'ST-M' */

/**
 * @brief uKernel Release C-Constant defining the <Project> field of the
 *  Customer Configuration of the uKernel Release used.
 *
 * Definition of the uKernel Release C-Constant for the <Project> field of the
 *  Customer Configuration of the uKernel Release used.
 */
#define DukRELEASE_CUSTOMER_CONFIG_PROJECT      0x0002U


/**
 * @brief uKernel Release C-Constant defining the <Revision> field of the
 *  Customer Configuration of the uKernel Release used.
 *
 * Definition of the uKernel Release C-Constant for the <Revision> field of the
 *  Customer Configuration of the uKernel Release used.
 */
#define DukRELEASE_CUSTOMER_CONFIG_REVISION     0x0004U

/**
 * @brief uKernel Release C-Constant defining the Customer Configuration of the
 *  uKernel Release used.
 *
 * Definition of the uKernel Release C-Constant for the Customer Configuration
 *  (see TukCUSTOMER_CONFIG) of the uKernel Release used.
 *
 * The Customer Configuration allows to track the different uKernel Release
 *  issued with the same Version (see DukRELEASE_UKERNEL_VERSION), but with
 *  different uKernel Features and Options in function a given Project of a
 *  Customer.
 *
 * @usage A ukApp Descriptor is valid if the value of its field
 *  <ReleaseCustomerConfiguration> is as follows:
 *  - Fields <Customer> and <Project> shall be equal to the ones of this
 *   C-Constant.
 *  - Field <Revision> shall be lower or equal to the one of this C-Constant.
 */
#define DukRELEASE_CUSTOMER_CONFIG                                            \
        MukVAL_TYPED(TukCUSTOMER_CONFIG,                                      \
            (                                                                 \
               (DukRELEASE_CUSTOMER_CONFIG_CUSTOMER     <<                    \
                    DukCUSTOMER_CONFIG_CUSTOMER_FIELD_LSb)                  | \
               (DukRELEASE_CUSTOMER_CONFIG_PROJECT      <<                    \
                    DukCUSTOMER_CONFIG_PROJECT_FIELD_LSb)                   | \
               (DukRELEASE_CUSTOMER_CONFIG_REVISION     <<                    \
                    DukCUSTOMER_CONFIG_REVISION_FIELD_LSb)                    \
            )                                                                 \
                                                )


/* //////////////////////////////////////////////////////////////////////// */
/*                      UKERNEL RELEASE - UKERNEL VERSION                   */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief uKernel Release C-Constant defining the <Major> field of the Version
 *  of the uKernel Core code used for the uKernel Release.
 *
 * Definition of the uKernel Release C-Constant for the <Major> field of
 *  the Version of the uKernel Core code used for the uKernel Release.
 */
#define DukRELEASE_UKERNEL_VERSION_MAJOR        0x04U

/**
 * @brief uKernel Release C-Constant defining the <Minor> field of the Version
 *  of the uKernel Core code used for the uKernel Release.
 *
 * Definition of the uKernel Release C-Constant for the <Minor> field of
 *  the Version of the uKernel Core code used for the uKernel Release.
 */
#define DukRELEASE_UKERNEL_VERSION_MINOR        0x03U

/**
 * @brief uKernel Release C-Constant defining the <Micro> field of the Version
 *  of the uKernel Core code used for the uKernel Release.
 *
 * Definition of the uKernel Release C-Constant for the <Micro> field of
 *  the Version of the uKernel Core code used for the uKernel Release.
 */
#define DukRELEASE_UKERNEL_VERSION_MICRO        0x0001U


/**
 * @brief uKernel Release C-Constant defining the Version (see TukVERSION) of
 *  the uKernel Core code used for the uKernel Release.
 *
 * Definition of the uKernel Release C-Constant for the Version of the uKernel
 *  Core code used for the uKernel Release.
 *
 * @implementation This Version is defined using separate definitions made for
 *  each field of the Version (see TukVersion). These separated definitions
 *  allow using the C-Preprocessor for performing needed checks.
 *
 * @usage A ukApp Descriptor is valid if the value of its field
 *  <ReleaseuKernelVersion> is as follows:
 *  - Fields <Major> and <Minor> shall be equal to the ones of this C-Constant.
 *  - Field <Micro> shall be lower or equal to the one of this C-Constant.
 */
#define DukRELEASE_UKERNEL_VERSION                                            \
    MukVAL_TYPED(TukVERSION,                                                  \
        (                                                                     \
            (DukRELEASE_UKERNEL_VERSION_MAJOR                                 \
              << DukVERSION_MAJOR_FIELD_LSb) |                                \
            (DukRELEASE_UKERNEL_VERSION_MINOR                                 \
              << DukVERSION_MINOR_FIELD_LSb) |                                \
            (DukRELEASE_UKERNEL_VERSION_MICRO                                 \
              << DukVERSION_MICRO_FIELD_LSb)                                  \
        )                                                                     \
                )


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL RELEASE - UKERNEL FILES VERSION                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Release C-Constant defining the <Major> field of the Version
 *  of the ukApp Configuration file "ukapp_config_descriptor.h".
 *
 * Definition of the uKernel Release C-Constant for the <Major> field of
 *  the Version of the ukApp Configuration file "ukapp_config_descriptor.h".
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MAJOR     0x03U

/**
 * @brief uKernel Release C-Constant defining the <Minor> field of the Version
 *  of the ukApp Configuration file "ukapp_config_descriptor.h".
 *
 * Definition of the uKernel Release C-Constant for the <Minor> field of
 *  the Version of the ukApp Configuration file "ukapp_config_descriptor.h".
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MINOR     0x09U

/**
 * @brief uKernel Release C-Constant defining the <Micro> field of the Version
 *  of the ukApp Configuration file "ukapp_config_descriptor.h".
 *
 * Definition of the uKernel Release C-Constant for the <Micro> field of
 *  the Version of the ukApp Configuration file "ukapp_config_descriptor.h".
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MICRO     0x0001U


/**
 * @brief uKernel Release C-Constant defining the Version of the ukApp
 *  Configuration file "ukapp_config_descriptor.h".
 *
 * Definition of the uKernel Release C-Constant for the Version the ukApp
 *  Configuration file "ukapp_config_descriptor.h" which has to be used when
 *  compiling ukApp code for this uKernel Release.
 *
 * @note See TukVERSION for the structure of the version value.
 *
 * @implementation This Version is defined using separate definitions made for
 *  each field of the Version (see TukVersion). These separated definitions
 *  allow using the C-Preprocessor for performing needed checks.
 *
 * @usage This Version is checked in the file "uk_app.c", and a C-Compiler
 *  warning is issued in case the version used for the file is not the one
 *  defined by this C-Constant. Only a warning is issued, as in order to ease
 *  uKernel Release upgrade, default definition when needed will be provided
 *  in case of previous version used in a ukApp implementation.
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION                     \
    MukVAL_TYPED(TukVERSION,                                                  \
        (                                                                     \
            (DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MAJOR          \
              << DukVERSION_MAJOR_FIELD_LSb) |                                \
            (DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MINOR          \
              << DukVERSION_MINOR_FIELD_LSb) |                                \
            (DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MICRO          \
              << DukVERSION_MICRO_FIELD_LSb)                                  \
        )                                                                     \
                )


/**
 * @brief uKernel Release C-Constant defining the <Major> field of the Version
 *  of the ukApp Configuration file "ukapp_config_options.h".
 *
 * Definition of the uKernel Release C-Constant for the <Major> field of
 *  the Version of the ukApp Configuration file "ukapp_config_options.h".
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MAJOR    0x03U

/**
 * @brief uKernel Release C-Constant defining the <Minor> field of the Version
 *  of the ukApp Configuration file "ukapp_config_options.h".
 *
 * Definition of the uKernel Release C-Constant for the <Minor> field of
 *  the Version of the ukApp Configuration file "ukapp_config_options.h".
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MINOR    0x00U

/**
 * @brief uKernel Release C-Constant defining the <Micro> field of the Version
 *  of the ukApp Configuration file "ukapp_config_options.h".
 *
 * Definition of the uKernel Release C-Constant for the <Micro> field of
 *  the Version of the ukApp Configuration file "ukapp_config_options.h".
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MICRO    0x0000U



/**
 * @brief uKernel Release C-Constant defining the Version of the ukApp
 *  Configuration file "ukapp_config_options.h".
 *
 * Definition of the uKernel Release C-Constant for the Version of the ukApp
 *  Configuration file "ukapp_config_options.h" which has to be used when
 *  compiling ukApp code for this uKernel Release.
 *
 * @note See TukVERSION for the structure of the version value.
 *
 * @implementation This Version is defined using separate definitions made for
 *  each field of the Version (see TukVersion). These separated definitions
 *  allow using the C-Preprocessor for performing needed checks.
 *
 * @usage This Version is checked in the file "uk_app.c", and a C-Compiler
 *  warning is issued in case the version used for the file is not the one
 *  defined by this C-Constant. Only a warning is issued, as in order to ease
 *  uKernel Release upgrade, default definition when needed will be provided
 *  in case of previous version used in a ukApp implementation.
 */
#define DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION                        \
    MukVAL_TYPED(TukVERSION,                                                  \
        (                                                                     \
            (DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MAJOR             \
              << DukVERSION_MAJOR_FIELD_LSb) |                                \
            (DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MINOR             \
              << DukVERSION_MINOR_FIELD_LSb) |                                \
            (DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MICRO             \
              << DukVERSION_MICRO_FIELD_LSb)                                  \
        )                                                                     \
                )



/* //////////////////////////////////////////////////////////////////////// */
/*               UKERNEL RELEASE - UKERNEL DESCRIPTOR VERSION               */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief uKernel Release C-Constant defining the Version of the uKernel
 *  Configuration Descriptor.
 *
 * Definition of the uKernel Release C-Constant for the Version of the uKernel
 *  Configuration Descriptor.
 *
 * @note See TukVERSION for the structure of the version value.
 *
 * @usage This Version value is placed at the beginning of the uKernel
 *  Configuration Descriptor structure (see TukUKERNEL_CONFIG_DESCRIPTOR). It
 *  is used by the tools in charge of uKernel Configuration for indicating to
 *  the uKernel which structure has been used for uKernel Configuration.
 */
#define DukRELEASE_UKERNEL_CONFIG_DESCRIPTOR_VERSION                          \
                                                MukVAL_TYPED(TukVERSION,      \
            (                                                                 \
                 (0x03U     << DukVERSION_MAJOR_FIELD_LSb) |                  \
                 (0x07U     << DukVERSION_MINOR_FIELD_LSb) |                  \
                 (0x0001U   << DukVERSION_MICRO_FIELD_LSb)                    \
            )                                                                 \
                                                            )


/**
 * @brief uKernel Release C-Constant defining the Version of the ukApp
 *  Descriptor.
 *
 * Definition of the uKernel Release C-Constant for the Version of the ukApp
 *  Descriptor.
 *
 * @note See TukVERSION for the structure of the version value.
 *
 * @usage This Version value is placed at the beginning of the ukApp
 *  Descriptor structure (see TukUKAPP_DESCRIPTOR). It is used by the tools in
 *  charge of processing and packaging ukApps to use proper structure to access
 *  to the ukApps fields in their ukApp Descriptor.
 */
#define DukRELEASE_UKAPP_DESCRIPTOR_VERSION                                   \
                                                MukVAL_TYPED(TukVERSION,      \
            (                                                                 \
                 (0x03U     << DukVERSION_MAJOR_FIELD_LSb) |                  \
                 (0x09U     << DukVERSION_MINOR_FIELD_LSb) |                  \
                 (0x0001U   << DukVERSION_MICRO_FIELD_LSb)                    \
            )                                                                 \
                                                            )


/**
 * @brief uKernel Release C-Constant defining the Version of the uKernel Core
 *  Code Descriptor.
 *
 * Definition of the uKernel Release C-Constant for the Version of the uKernel
 *  Core Code Descriptor.
 *
 * @note See TukVERSION for the structure of the version value.
 *
 * @usage This Version value is placed at the beginning of the uKernel Core
 *  Descriptor structure (see TukUKERNEL_CORE_DESCRIPTOR). It is used by the
 *  uKernel Bootloader and by the tools in charge of building uKernel Image to
 *  adapt accordingly to corresponding uKernel Core Code Descriptor contents.
 */
#define DukRELEASE_UKERNEL_CORE_DESCRIPTOR_VERSION                            \
                                                MukVAL_TYPED(TukVERSION,      \
            (                                                                 \
                 (0x03      << DukVERSION_MAJOR_FIELD_LSb) |                  \
                 (0x00      << DukVERSION_MINOR_FIELD_LSb) |                  \
                 (0x0001    << DukVERSION_MICRO_FIELD_LSb)                    \
            )                                                                 \
                                                            )



/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL RELEASE - UKERNEL CORE DESCRIPTOR                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Definition of the SHA256 of the uKernel Core Code Body Block.
 *
 * This value defines the SHA256 computed on the uKernel Core Code Body Block.
 *
 * This SHA256 value shall be computed on the whole contents of the uKernel
 *  Core Code Body Block defined as the following Address Block:
 *  [ (<MemoryRegionCodeAddressStart> + sizeof(TukUKERNEL_CORE_DESCRIPTOR)) ...
 *    (<MemoryRegionCodeAddressStart> + <MemoryRegionCodeSize> - 1) ].
 *
 * @implementation The following checks are done during uKernel Initialization:
 *  - The <UKernelCoreCodeBodyBlockSHA256> field shall be equal to the SHA256
 *   value computed by the uKernel on the whole contents of the uKernel Core
 *   Code Body Block.
 *   If not equal, the uKernel Core Code Block is not genuine: if uKernel
 *   Feature SukCONFIG_FEATURE_PRODUCTION_RELEASE is supported, it is a uKernel
 *   FATAL Error.
 *
 * @usage The SHA256 value computed on the uKernel Core Code Body Block is
 *  printed in the uKernel Debug Trace: the printed value can be used to fill
 *  in this field with proper value.
 */
#define DukRELEASE_UKERNEL_CORE_CODE_BODY_BLOCK_SHA256  {                     \
            0x5A5A5A5A, 0x1CCCCCC1, 0x2CCCCCC2, 0x3CCCCCC3,                   \
            0x4CCCCCC4, 0x5CCCCCC5, 0x6CCCCCC6, 0x5A5A5A5A                    \
                                                        }

/**
 * @brief Definition of the SHA256 of the uKernel Core Code Descriptor.
 *
 * This value defines the SHA256 computed on the uKernel Core Code Descriptor.
 *
 * This SHA256 value shall be computed on the contents of the uKernel Core Code
 *  Descriptor from its start up to the field <UKernelCoreDescriptorSHA256>
 *  (not included), that is on the following Address Block:
 *  [ (<MemoryRegionCodeAddressStart> + sizeof(TukUKAPP_DESCRIPTOR)) ...
 *    (<MemoryRegionCodeAddressStart> +
 *     sizeof(TukUKAPP_DESCRIPTOR) -
 *     sizeof(TukHASH_SHA256)
 *     - 1) ].
 *
 * @implementation The following checks are done during uKernel Initialization:
 *  - The <UKernelCoreDescriptorSHA256> field shall be equal to the SHA256
 *   value computed by the uKernel on the whole contents of the uKernel Core
 *   Descriptor.
 *   If not equal, the uKernel Core Code Block is not genuine: if uKernel
 *   Feature SukCONFIG_FEATURE_PRODUCTION_RELEASE is supported, it is a uKernel
 *   FATAL Error.
 *
 * @usage The SHA256 value computed on the uKernel Core Descriptor is printed
 *  in the uKernel Debug Trace: the printed value can be used to fill in this
 *  field with proper value.
 */
#define DukRELEASE_UKERNEL_CORE_DESCRIPTOR_SHA256       {                     \
            0x5A5A5A5A, 0x1DDDDDD1, 0x2DDDDDD2, 0x3DDDDDD3,                   \
            0x4DDDDDD4, 0x5DDDDDD5, 0x6DDDDDD6, 0x5A5A5A5A                    \
                                                        }


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_RELEASE_H_INSIDE
#endif /* !defined(UK_RELEASE_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

