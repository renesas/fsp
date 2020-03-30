/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#if !defined(MBEDTLS_CONFIG_FILE)
 #include "mbedtls/config.h"
#else
 #include MBEDTLS_CONFIG_FILE
#endif

/**
 * \brief Function level alternative implementation.
 *
 * The MBEDTLS_ECP_INTERNAL_ALT macro enables alternative implementations to
 * replace certain functions in this module. The alternative implementations are
 * typically hardware accelerators and need to activate the hardware before the
 * computation starts and deactivate it after it finishes. The
 * mbedtls_internal_ecp_init() and mbedtls_internal_ecp_free() functions serve
 * this purpose.
 *
 * To preserve the correct functionality the following conditions must hold:
 *
 * - The alternative implementation must be activated by
 *   mbedtls_internal_ecp_init() before any of the replaceable functions is
 *   called.
 * - mbedtls_internal_ecp_free() must \b only be called when the alternative
 *   implementation is activated.
 * - mbedtls_internal_ecp_init() must \b not be called when the alternative
 *   implementation is activated.
 * - Public functions must not return while the alternative implementation is
 *   activated.
 * - Replaceable functions are guarded by \c MBEDTLS_ECP_XXX_ALT macros and
 *   before calling them an \code if( mbedtls_internal_ecp_grp_capable( grp ) )
 *   \endcode ensures that the alternative implementation supports the current
 *   group.
 */
#if defined(MBEDTLS_ECP_INTERNAL_ALT)
#endif

#if defined(MBEDTLS_ECP_C)

 #include "mbedtls/ecp.h"
 #include "mbedtls/threading.h"
 #include "mbedtls/platform_util.h"

 #include <string.h>

 #if defined(MBEDTLS_ECP_ALT)

/* Parameter validation macros based on platform_util.h */
  #define ECP_VALIDATE_RET(cond) \
    MBEDTLS_INTERNAL_VALIDATE_RET(cond, MBEDTLS_ERR_ECP_BAD_INPUT_DATA)
  #define ECP_VALIDATE(cond) \
    MBEDTLS_INTERNAL_VALIDATE(cond)

  #if defined(MBEDTLS_PLATFORM_C)
   #include "mbedtls/platform.h"
  #else
   #include <stdlib.h>
   #include <stdio.h>
   #define mbedtls_printf    printf
   #define mbedtls_calloc    calloc
   #define mbedtls_free      free
  #endif

  #include "mbedtls/ecp_internal.h"
  #include "psa/crypto.h"

static const hw_sce_ecc_generatekey_t g_ecp_keygen_lookup[][2] =
{
  #if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) || defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_256GenerateKey,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_256HrkGenerateKey,
   #endif
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_384GenerateKey,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_384HrkGenerateKey,
   #endif
  #endif
};

static const hw_sce_ecc_scalarmultiplication_t g_ecp_scalar_multiplication_lookup[][2] =
{
  #if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) || defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_256ScalarMultiplication,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_256HrkScalarMultiplication,
   #endif
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_384ScalarMultiplication,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_384HrkScalarMultiplication,
   #endif
  #endif
};

/*
 * Generate a private key
 */
extern int ecp_load_parameters_sce(const mbedtls_ecp_group * grp, uint8_t * p_curve_params_buff);
extern int ecp_can_do_sce(mbedtls_ecp_group_id gid);

uint32_t ecp_load_key_size(bool wrapped_mode_ctx, const mbedtls_ecp_group * grp);

uint32_t ecp_load_key_size (bool wrapped_mode_ctx, const mbedtls_ecp_group * grp)
{
    uint32_t key_size_words = 0;
    size_t   curve_bytes    = PSA_BITS_TO_BYTES(grp->pbits);
  #if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) || defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
    if (ECC_256_PRIVATE_KEY_LENGTH_BITS == grp->pbits)
    {
        if (wrapped_mode_ctx == true)
        {
            /* Store size of wrapped private key */
            key_size_words = ECC_256_PRIVATE_KEY_HRK_LENGTH_WORDS;
        }
        else
        {
            key_size_words = curve_bytes / 4;
        }
    }
    else
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
    if (ECC_384_PRIVATE_KEY_LENGTH_BITS == grp->pbits)
    {
        if (wrapped_mode_ctx == true)
        {
            /* Store size of wrapped private key */
            key_size_words = ECC_384_PRIVATE_KEY_HRK_LENGTH_WORDS;
        }
        else
        {
            key_size_words = curve_bytes / 4;
        }
    }
    else
  #endif
    {
        key_size_words = 0;
    }

    return key_size_words;             // NOLINT(readability-misleading-indentation)
}

int mbedtls_ecp_gen_privkey (const mbedtls_ecp_group * grp,
                             mbedtls_mpi * d,
                             int (* f_rng)(void *, unsigned char *, size_t),
                             void * p_rng)
{
    (void) f_rng;
    (void) p_rng;

    int ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;

    ECP_VALIDATE_RET(grp != NULL);
    ECP_VALIDATE_RET(d != NULL);

    uint32_t               * p_curve_params_buff_32;
    uint32_t               * p_public_key_buff_32;
    uint32_t               * p_private_key_buff_32;
    uint32_t               * p_common_buff_32;
    uint32_t                 private_key_size_words   = 0;
    hw_sce_ecc_generatekey_t p_hw_sce_ecc_generatekey = NULL;

    /* Fail cleanly on curves that HW doesn't support */
    if ((!ecp_can_do_sce(grp->id)) || (grp->N.p == NULL))
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

  #if defined(MBEDTLS_CHECK_PARAMS)
    if ((ECC_256_PRIVATE_KEY_LENGTH_BITS != grp->pbits) && (ECC_384_PRIVATE_KEY_LENGTH_BITS != grp->pbits))
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }
  #endif

    p_hw_sce_ecc_generatekey =
        g_ecp_keygen_lookup[RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(grp->pbits)][(bool) grp->vendor_ctx];

    if (NULL == p_hw_sce_ecc_generatekey)
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    private_key_size_words = ecp_load_key_size((bool) grp->vendor_ctx, grp);
    if (0 == private_key_size_words)
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    size_t curve_bytes = PSA_BITS_TO_BYTES(grp->pbits);

    /* Obtain a common 32-bit aligned buffer. It will be used for all the following items in this order:
     * Curve parameters a, b, p, n, Gx, Gy. Each of the 6 fields are of size curve_bytes = PSA_BITS_TO_BYTES( ecp->grp.pbits )
     * Private Key (D) of size private_key_size_words
     * Public Key (Q) of size curve_bytes * 2 */
    p_common_buff_32 = mbedtls_calloc(((curve_bytes * 8) / 4) + private_key_size_words, sizeof(uint32_t));

    if (NULL == p_common_buff_32)
    {
        return MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }

    p_curve_params_buff_32 = p_common_buff_32;
    p_private_key_buff_32  = p_curve_params_buff_32 + ((curve_bytes * 6) / 4);
    p_public_key_buff_32   = p_private_key_buff_32 + private_key_size_words;

    ret = ecp_load_parameters_sce(grp, (uint8_t *) p_curve_params_buff_32);
    if (ret)
    {
    }
    else if (FSP_SUCCESS !=
             p_hw_sce_ecc_generatekey(p_curve_params_buff_32, p_curve_params_buff_32 + ((curve_bytes * 4) / 4),
                                      p_private_key_buff_32, p_public_key_buff_32))
    {
        ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
    }
    else if (0 !=
             mbedtls_mpi_read_binary(d, (uint8_t *) p_private_key_buff_32, private_key_size_words * 4))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else
    {
        ret = 0;
    }

    /* Clear out the allocated buffer */
    memset(p_common_buff_32, 0, ((curve_bytes * 8) + (private_key_size_words * 4)));

    mbedtls_free(p_common_buff_32);

    return ret;
}

int mbedtls_ecp_mul (mbedtls_ecp_group * grp,
                     mbedtls_ecp_point * R,
                     const mbedtls_mpi * m,
                     const mbedtls_ecp_point * P,
                     int (* f_rng)(void *, unsigned char *, size_t),
                     void * p_rng)
{
    (void) f_rng;
    (void) p_rng;

    ECP_VALIDATE_RET(grp != NULL);
    ECP_VALIDATE_RET(R != NULL);
    ECP_VALIDATE_RET(m != NULL);
    ECP_VALIDATE_RET(P != NULL);

    int       ret = 0;
    fsp_err_t err;
    hw_sce_ecc_scalarmultiplication_t p_hw_sce_ecc_scalarmultiplication = NULL;

    uint32_t * p_curve_params_buff_32;
    uint32_t * p_point_buff_P_32;
    uint32_t * p_integer_buff_m_32;
    uint32_t * p_point_result_buff_R_32;
    uint32_t * p_common_buff_32;
    uint32_t   integer_size_words = 0;

    /* Fail cleanly on curves that HW doesn't support.
     * Fail if the point co-ordinates are in Jacobian format (only Affine is supported).
     * See description of mbedtls_ecp_point for more information.
     */
    if ((!ecp_can_do_sce(grp->id)) || (grp->N.p == NULL) || (P->Z.n != 1) || (*(P->Z.p) == 0))
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    p_hw_sce_ecc_scalarmultiplication =
        g_ecp_scalar_multiplication_lookup[RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(grp->pbits)][(bool) grp->vendor_ctx];
    if (NULL == p_hw_sce_ecc_scalarmultiplication)
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    integer_size_words = ecp_load_key_size((bool) grp->vendor_ctx, grp);
    if (0 == integer_size_words)
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    size_t curve_bytes = PSA_BITS_TO_BYTES(grp->pbits);

    /* Obtain a common 32-bit aligned buffer. It will be used for all the following items in this order:
     * Curve parameters a, b, p, n, Gx, Gy. Each of the 6 fields are of size curve_bytes = PSA_BITS_TO_BYTES( ecp->grp.pbits )
     * Multiplication point (P) of size curve_bytes * 2 in format (Px|Py)
     * Multiplication result (R) of size curve_bytes * 2 in format (Rx|Ry)
     * Input scalar (m) of size integer_size_words */
    p_common_buff_32 = mbedtls_calloc(((curve_bytes * 10) / 4) + integer_size_words, sizeof(uint32_t));

    if (NULL == p_common_buff_32)
    {
        return MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }

    p_curve_params_buff_32   = p_common_buff_32;
    p_point_buff_P_32        = p_curve_params_buff_32 + ((curve_bytes * 6) / 4);
    p_point_result_buff_R_32 = p_point_buff_P_32 + ((curve_bytes * 2) / 4);
    p_integer_buff_m_32      = p_point_result_buff_R_32 + ((curve_bytes * 2) / 4);

    ret = ecp_load_parameters_sce(grp, (uint8_t *) p_curve_params_buff_32);
    if (ret)
    {
    }
    /* Write the integer to be multiplied into the buffer in reverse */
    else if (0 !=
             mbedtls_mpi_write_binary(m, (uint8_t *) p_integer_buff_m_32, integer_size_words * 4))
    {
        ret = MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }
    /* Write Px into the buffer in reverse */
    else if (0 !=
             mbedtls_mpi_write_binary(&P->X, (uint8_t *) p_point_buff_P_32, curve_bytes))
    {
        ret = MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }
    /* Write Py into the buffer in reverse */
    else if (0 !=
             mbedtls_mpi_write_binary(&P->Y, (uint8_t *) (p_point_buff_P_32 + ((curve_bytes) / 4)), curve_bytes))
    {
        ret = MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }
    else
    {
        err =
            p_hw_sce_ecc_scalarmultiplication(p_curve_params_buff_32,
                                              p_integer_buff_m_32,
                                              p_point_buff_P_32,
                                              p_point_result_buff_R_32);
        if (FSP_SUCCESS != err)
        {
            ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
        }
        else if (0 !=
                 mbedtls_mpi_read_binary(&R->X, (uint8_t *) p_point_result_buff_R_32, curve_bytes))
        {
            ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }
        else if (0 !=
                 mbedtls_mpi_read_binary(&R->Y, (uint8_t *) (p_point_result_buff_R_32 + ((curve_bytes) / 4)),
                                         curve_bytes))
        {
            ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
        }
        else
        {
            ret = 0;
        }
    }

    /*
     * For Affine format, copy the input Z value to the output.
     * This is only necessary since the mbedCrypto test suites check this value.
     */
    if (0 == ret)
    {
        ret = mbedtls_mpi_copy(&R->Z, &P->Z);
    }

    mbedtls_free(p_common_buff_32);

    return ret;
}

 #endif                                /* !MBEDTLS_ECP_ALT */

#endif                                 /* MBEDTLS_ECP_C */
