/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_ERR_H
#define R_RSIP_ERR_H

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Return code of internal function */
typedef enum e_rsip_ret
{
    /* Success */
    RSIP_RET_PASS,

    /* Branching */
    RSIP_RET_PASS_0,
    RSIP_RET_PASS_1,

    /* Error */
    RSIP_RET_RESOURCE_CONFLICT,
    RSIP_RET_RETRY,
    RSIP_RET_FAIL,
    RSIP_RET_KEY_FAIL,
    RSIP_RET_PARAM_FAIL,
    RSIP_RET_VERIFICATION_FAIL,
    RSIP_RET_AUTH_FAIL,
    RSIP_RET_UNKNOWN
} rsip_ret_t;

#endif                                 /* R_RSIP_ERR_H */
