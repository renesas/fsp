/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef RM_PSA_CRYPTO_H
 #define RM_PSA_CRYPTO_H

 #define PSA_KEY_TYPE_AES_WRAPPED                  (PSA_KEY_TYPE_VENDOR_FLAG | PSA_KEY_TYPE_AES)
 #define PSA_KEY_TYPE_RSA_KEY_PAIR_WRAPPED         (PSA_KEY_TYPE_VENDOR_FLAG | PSA_KEY_TYPE_RSA_KEY_PAIR)
 #define PSA_KEY_TYPE_ECC_KEY_PAIR_BASE_WRAPPED    (PSA_KEY_TYPE_VENDOR_FLAG | PSA_KEY_TYPE_ECC_KEY_PAIR_BASE)

/** Elliptic curve key pair.
 *
 * \param curve     A value that identifies the  ECC curve to be used.
 */
 #define PSA_KEY_TYPE_ECC_KEY_PAIR_WRAPPED(curve)      (PSA_KEY_TYPE_ECC_KEY_PAIR_BASE_WRAPPED | (curve))

/** Whether a key type is a wrapped RSA key pair. */
 #define PSA_KEY_TYPE_IS_RSA_KEY_PAIR_WRAPPED(type)    (type == (PSA_KEY_TYPE_RSA_KEY_PAIR | PSA_KEY_TYPE_VENDOR_FLAG))

/** Whether a key type is wrapped elliptic curve key pair. */
 #define PSA_KEY_TYPE_IS_ECC_KEY_PAIR_WRAPPED(type)    (((type) & ~PSA_KEY_TYPE_ECC_CURVE_MASK) ==  \
		 	 	 	 	 	 	 	 	 	 	 	 	 PSA_KEY_TYPE_ECC_KEY_PAIR_BASE_WRAPPED)

 #if defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)

  #include <string.h>
  #include "bsp_api.h"
  #include "hw_sce_private.h"
  #include "hw_sce_trng_private.h"

// Define the maximum number of attempts by the TRNG to generate dissimilar data
  #define RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS    2

/*******************************************************************************************************************/ /**
 * @addtogroup RM_PSA_CRYPTO
 * @{
 **********************************************************************************************************************/
fsp_err_t RM_PSA_CRYPTO_TRNG_Read(uint8_t * const p_rngbuf, uint32_t num_req_bytes, uint32_t * p_num_gen_bytes);

  #ifdef __cplusplus
extern "C"
{
  #endif

  #ifdef __cplusplus
}
  #endif
 #endif                                /* MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT */

/*******************************************************************************************************************/ /**
 * @} (end addtogroup PSA_CRYPTO)
 **********************************************************************************************************************/
#endif                                 /* RM_PSA_CRYPTO_H */
