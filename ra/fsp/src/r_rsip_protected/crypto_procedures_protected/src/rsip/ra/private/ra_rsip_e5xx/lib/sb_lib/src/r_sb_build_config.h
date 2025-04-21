/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_sb_build_config.h
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file defines macros for build configuration.
**********************************************************************************************************************/
#ifndef R_SB_BUILD_CONFIG_H
/* Multiple inclusion protection macro */
#define R_SB_BUILD_CONFIG_H

/*!***********************************************************
 * \addtogroup  SBLIBBC
 * \{
 * \addtogroup  SBLIBBCDefines   BuildConfiguration Definitions
 * \}********************************************************/

/*=====================================================================================================================
 Public macro definitions
=====================================================================================================================*/
/*!*********************************************************
 * \addtogroup  SBLIBBCDefines
 * \{*******************************************************/
/** Select whether to check the setting value of the build configuration \n
    - 1: This config is valid
    - 0: This config is invalid */
#define SB_CFG_PARAM_CHECKING_ENABLE           (0U)

/** Select whether to enable or disable Secure Boot function by Mac verification \n
    - 1: This config is valid
    - 0: This config is invalid */
#define SB_CFG_SB_MAC_VERIFICATION             (1U)

/** Select whether to enable or disable Secure Boot function by Certificate chain verification \n
    - 1: This config is valid
    - 0: This config is invalid */
#define SB_CFG_SB_CERT_CHAIN_VERIFICATION      (0U)

/** Select whether to enable or disable Certificate chain verification using the IMG PK of the previous stage \n
    - 1: This config is valid
    - 0: This config is invalid */
#define SB_CFG_SB_CERT_CHAIN_USE_IMG_PK        (0U)

/** Select whether to enable or disable Image Encryption / Decryption function
    and Tenporary Encrypted Image Decryption function \n
    - 1: This config is valid
    - 0: This config is invalid */
#define SB_CFG_IMAGE_ENC_DEC                   (0U)

/** Select whether to enable or disable CRC check function \n
    - 1: This config is valid
    - 0: This config is invalid */
#define SB_CFG_CHECK_CRC                       (1U)

/** Select whether to enable or disable Integrity check function that use in Flash programmer stage \n
    - 1: This config is valid
    - 0: This config is invalid */
#define SB_CFG_CHECK_INTEGRITY                 (1U)

/*! \}*/

/*=====================================================================================================================
 Public type definitions
=====================================================================================================================*/

/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Public global functions
=====================================================================================================================*/

#endif  /* R_SB_BUILD_CONFIG_H */
/*=====================================================================================================================
 End of File
=====================================================================================================================*/
