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

rsip_ret_t r_rsip_p41i (const uint32_t InData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00410001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000005U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000041U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x1142c72bU),
                   bswap_32big(0x5a0d3e95U),
                   bswap_32big(0x0ba49b89U),
                   bswap_32big(0x5cb7c012U));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x6238acb3U),
                   bswap_32big(0x4b626921U),
                   bswap_32big(0xee36318dU),
                   bswap_32big(0xdd07d18aU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x46f4f2dbU), bswap_32big(0xafd766e0U), bswap_32big(0x0c3fe143U),
                       bswap_32big(0x514dda5eU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x36d8a8ddU), bswap_32big(0x483ba6bdU), bswap_32big(0x1cba0811U),
                       bswap_32big(0xf0b3c4e5U));

        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        return RSIP_RET_PASS;
    }
}
