/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_COMMON_H
#define R_RSIP_COMMON_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip.h"
#include "r_rsip_private.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "RSIP" in ASCII, used to determine if channel is open. */
#define RSIP_OPEN    (0x52534950U)

/* Various lengths */

/* RSIP_PRV_BYTE_SIZE_AES_BLOCK is defined in r_rsip.h */

/* ECC */
#define RSIP_PRV_BYTE_SIZE_ECC_256_PARAM                           (32U)
#define RSIP_PRV_BYTE_SIZE_ECC_384_PARAM                           (48U)
#define RSIP_PRV_BYTE_SIZE_ECC_512_PARAM                           (64U)
#define RSIP_PRV_BYTE_SIZE_ECC_521_PARAM                           (66U)

#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QX            (0U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QY            (32U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_384_QX            (0U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_384_QY            (48U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_512_QX            (0U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_512_QY            (64U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_521_QX            (14U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_521_QY            (94U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_EDWARDS25519_Q    (0U)

/* RSA */
#define RSIP_PRV_BYTE_SIZE_RSA_1024_N                              (128U)
#define RSIP_PRV_BYTE_SIZE_RSA_2048_N                              (256U)
#define RSIP_PRV_BYTE_SIZE_RSA_3072_N                              (384U)
#define RSIP_PRV_BYTE_SIZE_RSA_4096_N                              (512U)
#define RSIP_PRV_BYTE_SIZE_RSA_E                                   (4U)

#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_N                 (0U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_1024_E            (128U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_2048_E            (256U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_3072_E            (384U)
#define RSIP_PRV_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_4096_E            (512U)

/* SHA */
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA1                             (20U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA224                           (28U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA256                           (32U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA384                           (48U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA512                           (64U)

#define RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA1_SHA224_SHA256           (64U)
#define RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA384_SHA512                (128U)

/* RNG */
#define RSIP_PRV_BYTE_SIZE_RNG                                     (16U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

/* r_rsip.c */
fsp_err_t r_rsip_random_number_generate(rsip_ctrl_t * const p_ctrl, uint8_t * const p_random);

/* r_rsip_sha.c */
fsp_err_t r_rsip_sha_init(rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type);
fsp_err_t r_rsip_sha_update(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message, uint32_t const message_length);
fsp_err_t r_rsip_sha_finish(rsip_ctrl_t * const p_ctrl, uint8_t * const p_digest);

/*******************************************************************************************************************//**
 * Resets handle.
 *
 * @param[in] handle Pointer to handle.
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE void r_rsip_handle_reset (rsip_handle_t * handle)
{
    memset(handle, 0, sizeof(rsip_handle_t));
}

#endif                                 /* R_RSIP_COMMON_H */
