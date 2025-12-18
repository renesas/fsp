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

rsip_ret_t r_rsip_p44i (const uint32_t InData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub014(0x00440001U, 0x00000007U);

    r_rsip_func_sub002(0x800100e0U, 0x00000044U);

    r_rsip_func101(bswap_32big(0x44aaf80bU),
                   bswap_32big(0xf9c37becU),
                   bswap_32big(0xe33a1511U),
                   bswap_32big(0xf92b3cadU));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0xdf63e886U),
                   bswap_32big(0x7dd7e8c7U),
                   bswap_32big(0x5cf6bca1U),
                   bswap_32big(0x854c149dU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x46b05563U), bswap_32big(0x7b69b924U), bswap_32big(0x2aa7f408U),
                       bswap_32big(0x02f642e7U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xeabf717fU), bswap_32big(0x3dc2f958U), bswap_32big(0xd0a402f0U),
                       bswap_32big(0x590a636fU));

        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub004(0x0000181eU, 0x00430011U);

        r_rsip_func100(bswap_32big(0x8f3db3a0U), bswap_32big(0x99f2c39aU), bswap_32big(0xb8cd1248U),
                       bswap_32big(0x39c49f14U));
        r_rsip_func_sub006(0x08000095U, 0x00430011U);

        r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

        return RSIP_RET_PASS;
    }
}
