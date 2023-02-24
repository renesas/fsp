/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/***********************************************************************************************************************
 * File Name    : nx_crypto_ec_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_ECC_ALT)
 #include "rm_netx_secure_crypto.h"
 #include "nx_crypto_ec.h"

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Dummy functions to set valid function pointer
 **********************************************************************************************************************/
VOID sce_nx_crypto_ec_fp_affine_add_subtract (NX_CRYPTO_EC       * curve,
                                              NX_CRYPTO_EC_POINT * left,
                                              NX_CRYPTO_EC_POINT * right,
                                              HN_UBASE           * scratch)
{
    NX_CRYPTO_PARAMETER_NOT_USED(curve);
    NX_CRYPTO_PARAMETER_NOT_USED(left);
    NX_CRYPTO_PARAMETER_NOT_USED(right);
    NX_CRYPTO_PARAMETER_NOT_USED(scratch);
}

VOID sce_nx_crypto_ec_fp_projective_multiple (NX_CRYPTO_EC          * curve,
                                              NX_CRYPTO_EC_POINT    * g,
                                              NX_CRYPTO_HUGE_NUMBER * d,
                                              NX_CRYPTO_EC_POINT    * r,
                                              HN_UBASE              * scratch)
{
    NX_CRYPTO_PARAMETER_NOT_USED(curve);
    NX_CRYPTO_PARAMETER_NOT_USED(g);
    NX_CRYPTO_PARAMETER_NOT_USED(d);
    NX_CRYPTO_PARAMETER_NOT_USED(r);
    NX_CRYPTO_PARAMETER_NOT_USED(scratch);
}

VOID sce_nx_crypto_ec_secpr1_reduce (NX_CRYPTO_EC * curve, NX_CRYPTO_HUGE_NUMBER * value, HN_UBASE * scratch)
{
    NX_CRYPTO_PARAMETER_NOT_USED(curve);
    NX_CRYPTO_PARAMETER_NOT_USED(value);
    NX_CRYPTO_PARAMETER_NOT_USED(scratch);
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

#endif
