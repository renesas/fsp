/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

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
 #include "mbedtls/error.h"

 #include <string.h>

 #if defined(MBEDTLS_ECP_ALT)

  #if defined(MBEDTLS_PLATFORM_C)
   #include "mbedtls/platform.h"
  #else
   #include <stdlib.h>
   #include <stdio.h>
   #define mbedtls_printf    printf
   #define mbedtls_calloc    calloc
   #define mbedtls_free      free
  #endif

  #include "psa/crypto.h"
  #include "hw_sce_private.h"
  #include "hw_sce_ecc_private.h"
  #include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ECC_256WrappedScalarMultiplication (const uint32_t * InData_CurveType,
                                                     const uint32_t * InData_Cmd,
                                                     const uint32_t * InData_KeyIndex,
                                                     const uint32_t * InData_P,
                                                     const uint32_t * Domain_Param,
                                                     uint32_t       * OutData_R)
{
    return HW_SCE_Ecc256ScalarMultiplicationSubAdaptor(InData_CurveType,
                                                       InData_Cmd,
                                                       InData_KeyIndex,
                                                       InData_P,
                                                       Domain_Param,
                                                       OutData_R);
}

fsp_err_t HW_SCE_ECC_384WrappedScalarMultiplication (const uint32_t * InData_CurveType,
                                                     const uint32_t * InData_Cmd,
                                                     const uint32_t * InData_KeyIndex,
                                                     const uint32_t * InData_P,
                                                     const uint32_t * Domain_Param,
                                                     uint32_t       * OutData_R)
{
    return HW_SCE_Ecc384ScalarMultiplicationSubAdaptor(InData_CurveType,
                                                       InData_Cmd,
                                                       InData_KeyIndex,
                                                       InData_P,
                                                       Domain_Param,
                                                       OutData_R);
}

  #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
fsp_err_t HW_SCE_ECC_521WrappedScalarMultiplication (const uint32_t * InData_CurveType,
                                                     const uint32_t * InData_Cmd,
                                                     const uint32_t * InData_KeyIndex,
                                                     const uint32_t * InData_P,
                                                     const uint32_t * Domain_Param,
                                                     uint32_t       * OutData_R)
{
    return HW_SCE_Ecc521ScalarMultiplicationSubAdaptor(InData_CurveType,
                                                       InData_Cmd,
                                                       InData_KeyIndex,
                                                       InData_P,
                                                       Domain_Param,
                                                       OutData_R);
}

  #endif

fsp_err_t HW_SCE_ECC_ED25519WrappedScalarMultiplication (const uint32_t * InData_CurveType,
                                                         const uint32_t * InData_Cmd,
                                                         const uint32_t * InData_KeyIndex,
                                                         const uint32_t * InData_P,
                                                         const uint32_t * Domain_Param,
                                                         uint32_t       * OutData_R)
{
    return HW_SCE_EccEd25519ScalarMultiplicationSubAdaptor(InData_CurveType,
                                                           InData_Cmd,
                                                           InData_KeyIndex,
                                                           InData_P,
                                                           Domain_Param,
                                                           OutData_R);
}

static const hw_sce_ecc_scalarmultiplication_t g_ecp_scalar_multiplication_lookup[][2] =
{
  #if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) || defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_256WrappedScalarMultiplication,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_256WrappedScalarMultiplication,
   #endif
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_384WrappedScalarMultiplication,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_384WrappedScalarMultiplication,
   #endif
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_521_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_521WrappedScalarMultiplication,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_521_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_521WrappedScalarMultiplication,
   #endif
  #endif
};

static const hw_sce_ecc_scalarmultiplication_t g_ecp_edscalar_multiplication_lookup[][2] =
{
  #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_25519_PRIVATE_KEY_LENGTH_BITS + 1U)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_ED25519WrappedScalarMultiplication,
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX((ECC_25519_PRIVATE_KEY_LENGTH_BITS))][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_ED25519WrappedScalarMultiplication,
  #endif
  #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_25519_PRIVATE_KEY_LENGTH_BITS + 1U)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_ED25519WrappedScalarMultiplication,
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX((ECC_25519_PRIVATE_KEY_LENGTH_BITS))][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_ED25519WrappedScalarMultiplication,
  #endif
};

/*
 * Generate a private key
 */
extern int ecp_load_parameters_sce(const mbedtls_ecp_group * grp, uint8_t * p_curve_params_buff);
extern int ecp_can_do_sce(mbedtls_ecp_group_id gid);
extern int ecp_load_curve_attributes_sce(const mbedtls_ecp_group * grp,
                                         uint32_t                * p_curve_type,
                                         uint32_t                * p_cmd,
                                         sce_oem_cmd_t           * oem_priv_cmd,
                                         uint32_t               ** pp_domain_param);

uint32_t ecp_load_key_size(bool wrapped_mode_ctx, const mbedtls_ecp_group * grp);
uint32_t ed_ecp_load_key_size(bool wrapped_mode_ctx, const mbedtls_ecp_group * grp);

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
            key_size_words =
                R_SCE_BYTES_TO_WORDS(HW_SCE_ECC_WRAPPED_KEY_ADJUST(R_SCE_WORDS_TO_BYTES(
                                                                       ECC_256_PRIVATE_KEY_LENGTH_WORDS)));
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
            key_size_words =
                R_SCE_BYTES_TO_WORDS(HW_SCE_ECC_WRAPPED_KEY_ADJUST(R_SCE_WORDS_TO_BYTES(
                                                                       ECC_384_PRIVATE_KEY_LENGTH_WORDS)));
            ;
        }
        else
        {
            key_size_words = curve_bytes / 4;
        }
    }
    else
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
    if (ECC_521_PRIVATE_KEY_LENGTH_BITS == grp->pbits)
    {
        if (wrapped_mode_ctx == true)
        {
            /* Store size of wrapped private key */
            key_size_words =
                R_SCE_BYTES_TO_WORDS(HW_SCE_ECC_WRAPPED_KEY_ADJUST(R_SCE_WORDS_TO_BYTES(
                                                                       ECC_521_PRIVATE_KEY_LENGTH_WORDS)));
            ;
        }
        else
        {
            key_size_words = curve_bytes / 4;
        }
    }
    else
  #endif
  #if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
    if ((ECC_25519_PRIVATE_KEY_LENGTH_BITS == grp->pbits) || ((ECC_25519_PRIVATE_KEY_LENGTH_BITS - 1) == grp->pbits))
    {
        if (wrapped_mode_ctx == true)
        {
            /* Store size of wrapped private key */
            key_size_words =
                R_SCE_BYTES_TO_WORDS(HW_SCE_ECC_WRAPPED_KEY_ADJUST(R_SCE_WORDS_TO_BYTES(
                                                                       ECC_25519_PRIVATE_KEY_LENGTH_WORDS)));
            ;
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

uint32_t ed_ecp_load_key_size (bool wrapped_mode_ctx, const mbedtls_ecp_group * grp)
{
    uint32_t key_size_words = 0;
  #if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
    size_t curve_bytes = PSA_BITS_TO_BYTES(grp->pbits);
    if (wrapped_mode_ctx == true)
    {
        /* Store size of wrapped private key */
        key_size_words =
            R_SCE_BYTES_TO_WORDS(HW_SCE_ECC_WRAPPED_KEY_ADJUST(R_SCE_WORDS_TO_BYTES(ECC_25519_PRIVATE_KEY_LENGTH_WORDS)));
        ;
    }
    else
    {
        key_size_words = curve_bytes / 4;
    }

  #else
    (void) wrapped_mode_ctx;
    (void) grp;
  #endif

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

    uint32_t * p_private_key_buff_32;
    uint32_t * p_common_buff_32;
    uint32_t   private_key_size_words = 0;
    uint32_t   wrapped_key[RM_PSA_CRYPTO_LARGEST_WRAPPED_ECC_PRIVATE_KEY_WORDS] = {0};
    uint32_t   indata_key_type = 0;
    uint8_t    padding         = 0U;

  #if !(BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_SCE9_SUPPORTED)
    if ((bool) (grp->vendor_ctx) == false)
    {

        /* ECC plaintext key generation is not supported currently. */
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }
  #endif

    /* Fail cleanly on curves that HW doesn't support */
    if ((!ecp_can_do_sce(grp->id)) || (grp->N.p == NULL))
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

  #if defined(MBEDTLS_CHECK_PARAMS)
   #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
    if ((ECC_256_PRIVATE_KEY_LENGTH_BITS != grp->pbits) && (ECC_384_PRIVATE_KEY_LENGTH_BITS != grp->pbits) &&
        (ECC_521_PRIVATE_KEY_LENGTH_BITS != grp->pbits) && (ECC_25519_PRIVATE_KEY_LENGTH_BITS != grp->pbits))
   #else
    if ((ECC_256_PRIVATE_KEY_LENGTH_BITS != grp->pbits) && (ECC_384_PRIVATE_KEY_LENGTH_BITS != grp->pbits))
   #endif
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }
  #endif

    if (MBEDTLS_ECP_DP_CURVE25519 == grp->id)
    {
        private_key_size_words = ed_ecp_load_key_size((bool) grp->vendor_ctx, grp);
    }
    else
    {
        private_key_size_words = ecp_load_key_size((bool) grp->vendor_ctx, grp);
    }

    if (0 == private_key_size_words)
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    size_t curve_bytes = PSA_BITS_TO_BYTES(grp->pbits);

    if (ECC_521_PRIVATE_KEY_LENGTH_BITS == grp->pbits)
    {
        padding = 14U;                 /* 14bytes of padding is required for ECC 521 */
    }

    /* Obtain a common 32-bit aligned buffer. It will be used for all the following items in this order:
     * Private Key (D) of size private_key_size_words
     * Public Key (Q) of size ECC_PUBLIC_KEY_SIZE_BYTES */
    p_common_buff_32 =
        mbedtls_calloc((((ECC_PUBLIC_KEY_SIZE_BYTES(curve_bytes) + (padding * 2U))) / 4) + private_key_size_words,
                       sizeof(uint32_t));

    if (NULL == p_common_buff_32)
    {
        return MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }

    p_private_key_buff_32 = p_common_buff_32;

    uint32_t   curve_type;
    uint32_t   cmd;
    uint32_t * p_domain_param = NULL;
    ret = ecp_load_curve_attributes_sce(grp, &curve_type, &cmd, NULL, &p_domain_param);
    if (ret == 0)
    {
        if ((ECC_256_PRIVATE_KEY_LENGTH_BITS == grp->pbits) && (MBEDTLS_ECP_DP_CURVE25519 != grp->id))
        {
            uint32_t dummy[sizeof(sce_ecc_public_key_index_t)] = {0};
            if (FSP_SUCCESS !=
                HW_SCE_GenerateEccRandomKeyIndexSubAdaptor(&curve_type, &cmd, &indata_key_type,
                                                           (const uint32_t *) p_domain_param, dummy, dummy,
                                                           (uint32_t *) wrapped_key, dummy))
            {
                ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            }
            else
            {
                memcpy(p_private_key_buff_32, wrapped_key, private_key_size_words * 4U);
            }
        }

  #if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
        else if (ECC_384_PRIVATE_KEY_LENGTH_BITS == grp->pbits)
        {
            sce_ecc384_public_key_index_t public_key = {0};
            if (FSP_SUCCESS !=
                HW_SCE_GenerateEccP384RandomKeyIndexSubAdaptor(&curve_type, &indata_key_type, p_domain_param,
                                                               (uint32_t *) &public_key.value,
                                                               (uint32_t *) &public_key.plain_value,
                                                               (uint32_t *) wrapped_key,
                                                               (uint32_t *) &public_key.plain_value))
            {
                ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            }
            else
            {
                memcpy(p_private_key_buff_32, wrapped_key, private_key_size_words * 4U);
            }
        }
  #endif

  #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
   #if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
        else if (ECC_521_PRIVATE_KEY_LENGTH_BITS == grp->pbits)
        {
            sce_ecc521_public_key_index_t public_key = {0};
            if (FSP_SUCCESS !=
                HW_SCE_GenerateEccP521RandomKeyIndexSubAdaptor(&indata_key_type, p_domain_param,
                                                               (uint32_t *) &public_key.value, (uint32_t *) wrapped_key,
                                                               NULL))
            {
                ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            }
            else
            {
                memcpy(p_private_key_buff_32, wrapped_key, private_key_size_words * 4U);
            }
        }
   #endif
   #if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
        else if (MBEDTLS_ECP_DP_CURVE25519 == grp->id)
        {
            sce_ecc25519_public_key_index_t public_key = {0};
            if (FSP_SUCCESS !=
                HW_SCE_GenerateEccEd25519RandomKeyIndexSub(&indata_key_type, p_domain_param,
                                                           (uint32_t *) &public_key.value, (uint32_t *) wrapped_key,
                                                           NULL))
            {
                ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            }
            else
            {
                memcpy(p_private_key_buff_32, wrapped_key, private_key_size_words * 4U);
            }
        }
   #endif
  #endif

        else
        {
            ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
        }

        /* Public key generated within p_public_key_buff_32 is unused.
         * The caller, if needed, generates the public key using scalar multiply
         * */
        if (0 == ret)
        {
            if (FSP_SUCCESS !=
                mbedtls_mpi_read_binary(d, (uint8_t *) p_private_key_buff_32, private_key_size_words * 4))
            {
                ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
            }
        }
        else
        {
        }
    }

    /* Clear out the allocated buffer */
    memset(p_common_buff_32, 0, (ECC_PUBLIC_KEY_SIZE_BYTES(curve_bytes) + (private_key_size_words * 4)));
    mbedtls_free(p_common_buff_32);

    return ret;
}

int mbedtls_ecp_mul_restartable (mbedtls_ecp_group * grp,
                                 mbedtls_ecp_point * R,
                                 const mbedtls_mpi * m,
                                 const mbedtls_ecp_point * P,
                                 int (* f_rng)(void *, unsigned char *, size_t),
                                 void * p_rng,
                                 mbedtls_ecp_restart_ctx * rs_ctx)
{
    (void) f_rng;
    (void) p_rng;
    (void) rs_ctx;

    int       ret = 0;
    fsp_err_t err = FSP_SUCCESS;
    hw_sce_ecc_scalarmultiplication_t p_hw_sce_ecc_scalarmultiplication = NULL;

    uint32_t * p_point_buff_P_32;
    uint32_t * p_integer_buff_m_32;
    uint32_t * p_point_result_buff_R_32;
    uint32_t * p_common_buff_32;
    uint8_t    padding = 0U;

    /* Fail cleanly on curves that HW doesn't support.
     * Fail if the point co-ordinates are in Jacobian format (only Affine is supported).
     * See description of mbedtls_ecp_point for more information.
     */
    if ((!ecp_can_do_sce(grp->id)) || (grp->N.p == NULL) || (P->Z.n != 1) || (*(P->Z.p) == 0))
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    if (MBEDTLS_ECP_DP_CURVE25519 == grp->id)
    {
        p_hw_sce_ecc_scalarmultiplication =
            g_ecp_edscalar_multiplication_lookup[RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(grp->pbits)][(bool) grp->vendor_ctx];
    }
    else
    {
        p_hw_sce_ecc_scalarmultiplication =
            g_ecp_scalar_multiplication_lookup[RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(grp->pbits)][(bool) grp->vendor_ctx];
    }

    if (NULL == p_hw_sce_ecc_scalarmultiplication)
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    size_t curve_bytes = PSA_BITS_TO_BYTES(grp->pbits);

    /* Scalar multiply only accepts wrapped scalars. */
    uint32_t m_size_wrapped_words = ecp_load_key_size((bool) true, grp);
    if (0 == m_size_wrapped_words)
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    uint32_t m_size_words = ecp_load_key_size((bool) grp->vendor_ctx, grp);
    if (0 == m_size_words)
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    if (ECC_521_PRIVATE_KEY_LENGTH_BITS == grp->pbits)
    {
        padding = 14U;                 /* 14bytes of padding is required for HW ECC 521 */
    }

    /* Obtain a common 32-bit aligned buffer. It will be used for all the following items in this order:
     * Multiplication point (P) of size curve_bytes * 2 in format (Px|Py)
     * Multiplication result (R) of size curve_bytes * 2 in format (Rx|Ry)
     * Input scalar (m) of size m_size_words
     * Input wrapped scalar (m) of size m_size_wrapped_words */
    p_common_buff_32 =
        mbedtls_calloc((((curve_bytes + padding) * 4) / 4) + m_size_wrapped_words + m_size_words, sizeof(uint32_t));

    if (NULL == p_common_buff_32)
    {
        return MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }

    p_point_buff_P_32        = p_common_buff_32;
    p_point_result_buff_R_32 = (uint32_t *) (((uint8_t *) p_point_buff_P_32) + ((curve_bytes + padding) * 2));
    p_integer_buff_m_32      = (uint32_t *) (((uint8_t *) p_point_result_buff_R_32) + ((curve_bytes + padding) * 2));
    uint32_t * p_integer_buff_m_wrapped_32 = p_integer_buff_m_32 + m_size_words;

    uint32_t      curve_type;
    uint32_t      cmd;
    sce_oem_cmd_t oem_cmd;
    uint32_t    * p_domain_param = NULL;
    ret = ecp_load_curve_attributes_sce(grp, &curve_type, &cmd, &oem_cmd, &p_domain_param);
    if (0 == ret)
    {
        ret = mbedtls_mpi_write_binary(m, (uint8_t *) p_integer_buff_m_32, m_size_words * 4);
    }

    if (m_size_words != m_size_wrapped_words)
    {
        /* Install the plaintext private key to get the wrapped private key */
        err = HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                oem_cmd,
                                                NULL,
                                                NULL,
                                                (const uint8_t *) p_integer_buff_m_32,
                                                p_integer_buff_m_wrapped_32);
    }
    else
    {
        memcpy(p_integer_buff_m_wrapped_32, p_integer_buff_m_32, m_size_wrapped_words * 4);
    }

    if ((FSP_SUCCESS != err) || (0 != ret))
    {
        ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
    }
    /* Write Px into the buffer in reverse */
    else if (0 !=
             mbedtls_mpi_write_binary(&P->X, (((uint8_t *) p_point_buff_P_32) + padding), curve_bytes))
    {
        ret = MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }
    /* Write Py into the buffer in reverse */
    else if (0 !=
             mbedtls_mpi_write_binary(&P->Y, (((uint8_t *) p_point_buff_P_32) + (curve_bytes + (padding * 2))),
                                      curve_bytes))
    {
        ret = MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }
    else if (FSP_SUCCESS !=
             p_hw_sce_ecc_scalarmultiplication(&curve_type, &cmd, p_integer_buff_m_wrapped_32, p_point_buff_P_32,
                                               p_domain_param, p_point_result_buff_R_32))
    {
        ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
    }
    else if (0 !=
             mbedtls_mpi_read_binary(&R->X, ((uint8_t *) p_point_result_buff_R_32) + padding, curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else if (0 !=
             mbedtls_mpi_read_binary(&R->Y, (((uint8_t *) p_point_result_buff_R_32) + curve_bytes + (padding * 2)),
                                     curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else
    {
        ret = 0;
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
