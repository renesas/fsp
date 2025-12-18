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

void r_rsip_p36t (void)
{
    WR1_PROG(REG_00D0H, 0x08000045U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    r_rsip_func_sub003(0x81840001U, 0x00490011U);

    r_rsip_func_sub008(0x000000a1U, 0x40000020U, 0x07008c04U);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
}
