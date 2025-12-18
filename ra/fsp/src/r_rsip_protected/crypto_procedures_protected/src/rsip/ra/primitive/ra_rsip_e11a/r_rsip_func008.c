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

void r_rsip_func008 (void)
{
    r_rsip_func_sub001(0x0037000fU, 0x00190005U, 0x04040002U);

    r_rsip_func_sub001(0x00370014U, 0x001e0005U, 0x04040002U);

    r_rsip_func_sub001(0x00190019U, 0x000f0005U, 0x04040002U);

    r_rsip_func_sub001(0x005f000fU, 0x00140005U, 0x04040005U);

    r_rsip_func_sub001(0x00190014U, 0x000f0005U, 0x04040002U);

    r_rsip_func_sub001(0x0064000fU, 0x00140005U, 0x04040005U);

    r_rsip_func_sub001(0x001e001eU, 0x000f0005U, 0x04040002U);

    r_rsip_func_sub001(0x0014000fU, 0x00230000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func_sub001(0x000f0014U, 0x00230000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);
}
