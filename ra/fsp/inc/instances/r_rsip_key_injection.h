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

/*******************************************************************************************************************//**
 * @addtogroup RSIP_KEY_INJECTION
 * @{
 **********************************************************************************************************************/

#ifndef R_RSIP_KEY_INJECTION_H
#define R_RSIP_KEY_INJECTION_H

#include "bsp_api.h"
#include "r_rsip_key_injection_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rsip_key_injection_api_t g_rsip_key_injection_on_rsip;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_RSIP_AES128_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                       uint8_t const * const           p_wrapped_user_factory_programming_key,
                                       uint8_t const * const           p_initial_vector,
                                       uint8_t const * const           p_user_key,
                                       rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_AES192_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                       uint8_t const * const           p_wrapped_user_factory_programming_key,
                                       uint8_t const * const           p_initial_vector,
                                       uint8_t const * const           p_user_key,
                                       rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_AES256_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                       uint8_t const * const           p_wrapped_user_factory_programming_key,
                                       uint8_t const * const           p_initial_vector,
                                       uint8_t const * const           p_user_key,
                                       rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_RSA2048_InitialPublicKeyWrap(rsip_key_injection_type_t const           key_injection_type,
                                              uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                              uint8_t const * const                     p_initial_vector,
                                              uint8_t const * const                     p_user_key,
                                              rsip_rsa2048_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA2048_InitialPrivateKeyWrap(rsip_key_injection_type_t const            key_injection_type,
                                               uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                      p_initial_vector,
                                               uint8_t const * const                      p_user_key,
                                               rsip_rsa2048_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA3072_InitialPublicKeyWrap(rsip_key_injection_type_t const           key_injection_type,
                                              uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                              uint8_t const * const                     p_initial_vector,
                                              uint8_t const * const                     p_user_key,
                                              rsip_rsa3072_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA3072_InitialPrivateKeyWrap(rsip_key_injection_type_t const            key_injection_type,
                                               uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                      p_initial_vector,
                                               uint8_t const * const                      p_user_key,
                                               rsip_rsa3072_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA4096_InitialPublicKeyWrap(rsip_key_injection_type_t const           key_injection_type,
                                              uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                              uint8_t const * const                     p_initial_vector,
                                              uint8_t const * const                     p_user_key,
                                              rsip_rsa4096_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA4096_InitialPrivateKeyWrap(rsip_key_injection_type_t const            key_injection_type,
                                               uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                      p_initial_vector,
                                               uint8_t const * const                      p_user_key,
                                               rsip_rsa4096_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp256r1_InitialPublicKeyWrap(rsip_key_injection_type_t const       key_injection_type,
                                                    uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                    uint8_t const * const                 p_initial_vector,
                                                    uint8_t const * const                 p_user_key,
                                                    rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp256r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                     uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                  p_initial_vector,
                                                     uint8_t const * const                  p_user_key,
                                                     rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp384r1_InitialPublicKeyWrap(rsip_key_injection_type_t const       key_injection_type,
                                                    uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                    uint8_t const * const                 p_initial_vector,
                                                    uint8_t const * const                 p_user_key,
                                                    rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp384r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                     uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                  p_initial_vector,
                                                     uint8_t const * const                  p_user_key,
                                                     rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp256k1_InitialPublicKeyWrap(rsip_key_injection_type_t const       key_injection_type,
                                                    uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                    uint8_t const * const                 p_initial_vector,
                                                    uint8_t const * const                 p_user_key,
                                                    rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp256k1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                     uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                  p_initial_vector,
                                                     uint8_t const * const                  p_user_key,
                                                     rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_brainpoolP256r1_InitialPublicKeyWrap(rsip_key_injection_type_t const       key_injection_type,
                                                          uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                          uint8_t const * const                 p_initial_vector,
                                                          uint8_t const * const                 p_user_key,
                                                          rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_brainpoolP256r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                           uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                  p_initial_vector,
                                                           uint8_t const * const                  p_user_key,
                                                           rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_brainpoolP384r1_InitialPublicKeyWrap(rsip_key_injection_type_t const       key_injection_type,
                                                          uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                          uint8_t const * const                 p_initial_vector,
                                                          uint8_t const * const                 p_user_key,
                                                          rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_brainpoolP384r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                           uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                  p_initial_vector,
                                                           uint8_t const * const                  p_user_key,
                                                           rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_RSIP_KEY_INJECTION_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_KEY_INJECTION)
 **********************************************************************************************************************/
