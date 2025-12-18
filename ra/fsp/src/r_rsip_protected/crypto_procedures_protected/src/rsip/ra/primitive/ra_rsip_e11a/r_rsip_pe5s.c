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

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

rsip_ret_t r_rsip_pe5s (uint32_t OutData_State[])
{
    WR1_PROG(REG_00F4H, 0x00000100U);

    r_rsip_func100(bswap_32big(0x14a2147eU),
                   bswap_32big(0x13600ca5U),
                   bswap_32big(0x61e9f225U),
                   bswap_32big(0xbdea0b27U));
    WR1_PROG(REG_00F4H, 0x00000020U);

    WR1_PROG(REG_0008H, 0x00004022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD8_ADDR(REG_002CH, &OutData_State[0]);

    r_rsip_func102(bswap_32big(0x0bb48185U),
                   bswap_32big(0x3c0fd44bU),
                   bswap_32big(0xebb719bcU),
                   bswap_32big(0x944f39a1U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
