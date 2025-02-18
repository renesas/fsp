/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
