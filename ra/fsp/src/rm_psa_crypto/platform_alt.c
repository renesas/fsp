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

#if !defined(MBEDTLS_CONFIG_FILE)
 #include "mbedtls/config.h"
#else
 #include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)
 #include "mbedtls/platform.h"
 #include "hw_sce_private.h"

 #if defined(CONFIG_MEDTLS_USE_AFR_MEMORY) && defined(MBEDTLS_PLATFORM_MEMORY) && \
    !(defined(MBEDTLS_PLATFORM_CALLOC_MACRO) && defined(MBEDTLS_PLATFORM_FREE_MACRO))
extern void * pvCalloc(size_t xNumElements, size_t xSize);
extern void   vPortFree(void * pv);

 #endif

/*******************************************************************************************************************//**
 * @addtogroup RM_PSA_CRYPTO
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This function initializes the SCE and the TRNG. It **must** be invoked before the crypto library can be used.
 * This implementation is used if MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT is defined.
 *
 * Example:
 * @snippet rm_psa_crypto_example.c PSA_CRYPTO-PLATFORM-SETUP
 *
 * @retval 0                                        Initialization was successful.
 * @retval MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED     SCE Initialization error.
 **********************************************************************************************************************/
int mbedtls_platform_setup (mbedtls_platform_context * ctx)
{
    (void) ctx;

    fsp_err_t iret = FSP_ERR_CRYPTO_SCE_FAIL;

 #if defined(CONFIG_MEDTLS_USE_AFR_MEMORY) && defined(MBEDTLS_PLATFORM_MEMORY) && \
    !(defined(MBEDTLS_PLATFORM_CALLOC_MACRO) && defined(MBEDTLS_PLATFORM_FREE_MACRO))
    mbedtls_platform_set_calloc_free(pvCalloc, vPortFree);
 #endif

    iret = HW_SCE_McuSpecificInit();

    if (iret != FSP_SUCCESS)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return 0;
}

/*******************************************************************************************************************//**
 * This implementation is used if MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT is defined.
 * It is intended to de-initialize any items that were initialized in the mbedtls_platform_setup() function, but
 * currently is only a placeholder function.
 *
 * Example:
 * @snippet rm_psa_crypto_example.c PSA_CRYPTO-PLATFORM-TEARDOWN
 *
 * @retval  N/A
 **********************************************************************************************************************/
void mbedtls_platform_teardown (mbedtls_platform_context * ctx)
{
    (void) ctx;

    // Nothing to do to close the SCE
    // Nothing to do to close the TRNG
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_PSA_CRYPTO)
 **********************************************************************************************************************/

#endif                                 /* MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT */
