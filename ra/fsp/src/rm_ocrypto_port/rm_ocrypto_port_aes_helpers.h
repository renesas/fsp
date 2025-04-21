/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_OCRYPTO_PORT_AES_HELPERS_H
#define RM_OCRYPTO_PORT_AES_HELPERS_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "bsp_api.h"
#include "hw_sce_ra_private.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define OCRYPTO_PORT_BYTES_TO_WORDS(x)       ((x) / 4U)
#define OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES    16U
#define OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS    OCRYPTO_PORT_BYTES_TO_WORDS(OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES)
#define OCRYPTO_PORT_AES_32BIT_ALIGNED(x)    !((x) & 0x03)

/***********************************************************************************************************************
 * Type defines
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
void ocrypto_aes_helper_init(size_t aes_size, const uint32_t * sce_cmd, const uint32_t * xkey, const uint32_t * iv);
void ocrypto_aes_helper_update(size_t aes_size, const uint32_t * in_data, uint32_t * out_data,
                               const uint32_t data_size);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_OCRYPTO_PORT_AES_HELPERS_H */
