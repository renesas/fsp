/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

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
#define RSIP_PRV_BYTE_SIZE_ECC_256_PARAM                    (32U)
#define RSIP_PRV_BYTE_SIZE_ECC_384_PARAM                    (48U)
#define RSIP_PRV_BYTE_SIZE_ECC_512_PARAM                    (64U)
#define RSIP_PRV_BYTE_SIZE_ECC_521_PARAM                    (66U)

/* RSA */
#define RSIP_PRV_BYTE_SIZE_RSA_1024_N                       (128U)
#define RSIP_PRV_BYTE_SIZE_RSA_2048_N                       (256U)
#define RSIP_PRV_BYTE_SIZE_RSA_3072_N                       (384U)
#define RSIP_PRV_BYTE_SIZE_RSA_4096_N                       (512U)
#define RSIP_PRV_BYTE_SIZE_RSA_E                            (4U)

/* SHA */
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA1                      (20U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA224                    (28U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA256                    (32U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA384                    (48U)
#define RSIP_PRV_BYTE_SIZE_DIGEST_SHA512                    (64U)

#define RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA1_SHA224_SHA256    (64U)
#define RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA384_SHA512         (128U)

/* RNG */
#define RSIP_PRV_BYTE_SIZE_RNG                              (16U)

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
 * Clears handle.
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE void r_rsip_handle_reset (rsip_handle_t * handle)
{
    memset(handle, 0, sizeof(rsip_handle_t));
}

RSIP_PRV_STATIC_INLINE rsip_alg_t r_rsip_key_type_to_alg (rsip_key_type_t key_type)
{
    return (rsip_alg_t) ((key_type >> 8) & 0xff);
}

RSIP_PRV_STATIC_INLINE uint8_t r_rsip_key_type_to_subtype (rsip_key_type_t key_type)
{
    return (uint8_t) (key_type & 0xff);
}

RSIP_PRV_STATIC_INLINE rsip_alg_t r_rsip_key_pair_type_to_public_alg (rsip_key_pair_type_t key_pair_type)
{
    return (rsip_alg_t) ((key_pair_type >> 16) & 0xff);
}

RSIP_PRV_STATIC_INLINE rsip_alg_t r_rsip_key_pair_type_to_private_alg (rsip_key_pair_type_t key_pair_type)
{
    return (rsip_alg_t) ((key_pair_type >> 8) & 0xff);
}

RSIP_PRV_STATIC_INLINE uint8_t r_rsip_key_pair_type_to_subtype (rsip_key_pair_type_t key_pair_type)
{
    return (uint8_t) (key_pair_type & 0xff);
}

#endif                                 /* R_RSIP_COMMON_H */
