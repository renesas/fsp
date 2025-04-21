/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : r_tsip_rx_private.h
 * Description  : TSIP function private header file.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_cip_drv_if.h"
#include "r_cip_drv_api.h"

#ifndef R_CIP_PRIVATE_HEADER_FILE
    #define R_CIP_PRIVATE_HEADER_FILE

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
#define R_SHIP_SHIP_BYTE_SWAP_SET              (0x00010001U)
#define R_CIP_DRV_HMAC_SHA256_TLV              (0x30184008)

#define R_SHIP_SRAM_WORD_SIZE                 (256U)
#define R_SHIP_SHA256_HASH_LENGTH_BYTE_SIZE    (64U)
#define R_SHIP_SHA256_HASH_LENGTH_WORD_SIZE    (16U)
#define R_SHIP_CODE_CART_SIG_BYTE_SIZE         (64U)
#define R_SHIP_CART_TLV_BYTE_SIZE              (4U)
#define R_SHIP_CART_TLV_WORD_SIZE              ((uint32_t) 1U)

#define R_SHIP_WORD_BYTE_ROUND                 ((uint32_t) 3U)

#define R_SHIP_BIT_TO_BYTE_CHANGE_LOWER        (0x1FFFFFFFU)
#define R_SHIP_BIT_TO_BYTE_CHANGE_UPPER        (0xE0000000U)
#define R_SHIP_BIT_TO_BYTE_SHIFT_LOWER         (3U)
#define R_SHIP_BIT_TO_BYTE_SHIFT_UPPER        (29U)
#define R_SHIP_BIT_BUFFER_SIZE                 (2U)

#define R_SHIP_OEM_BL_MIN_SIZE                 (64U)

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif /* R_CIP_PRIVATE_HEADER_FILE */
