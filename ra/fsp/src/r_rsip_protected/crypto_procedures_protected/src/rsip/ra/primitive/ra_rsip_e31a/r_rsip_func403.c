/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func403 (void)
{
    r_rsip_func_sub001(0x00690064U, 0x00820005U, 0x04040005U);

    r_rsip_func_sub001(0x00870082U, 0x00280000U, 0x0404000aU);

    r_rsip_func_sub001(0x00820028U, 0x00230005U, 0x04040002U);

    r_rsip_func_sub001(0x00870064U, 0x00820000U, 0x0404000aU);
    r_rsip_func_sub001(0x00820064U, 0x00280005U, 0x04040002U);

    r_rsip_func_sub001(0x00870069U, 0x00820000U, 0x0404000aU);
    r_rsip_func_sub001(0x00820069U, 0x002d0005U, 0x04040002U);

    r_rsip_func_sub001(0x0028000fU, 0x00320005U, 0x04040002U);

    r_rsip_func_sub001(0x002d0032U, 0x00370005U, 0x04040005U);

    r_rsip_func_sub001(0x0087006eU, 0x00820000U, 0x0404000aU);

    r_rsip_func_sub001(0x0082006eU, 0x003c0005U, 0x04040002U);

    r_rsip_func_sub001(0x003c0037U, 0x00550005U, 0x04040006U);

    r_rsip_func_sub001(0x003c0055U, 0x005a0005U, 0x04040006U);

    r_rsip_func_sub001(0x005a0037U, 0x005f0005U, 0x04040002U);

    r_rsip_func_sub001(0x00280023U, 0x003c0005U, 0x04040006U);

    r_rsip_func_sub001(0x002d003cU, 0x00230005U, 0x04040006U);

    r_rsip_func_sub001(0x005a0023U, 0x00550005U, 0x04040002U);

    r_rsip_func_sub001(0x002d0032U, 0x003c0005U, 0x04040006U);

    r_rsip_func_sub001(0x003c0037U, 0x005a0005U, 0x04040002U);
}
