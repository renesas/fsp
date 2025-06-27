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

rsip_ret_t r_rsip_pefr (const uint32_t InData_HashType[], const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00ef0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00F0H, 0x00000001U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3000a800U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b400U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_0094H, 0x00000080U);

    r_rsip_func100(bswap_32big(0x520a7deeU),
                   bswap_32big(0xad0c4a9dU),
                   bswap_32big(0xd0e29c27U),
                   bswap_32big(0xc9403158U));

    WR1_PROG(REG_0094H, 0x00007c00U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_00F4H, 0x00001050U);

        r_rsip_func101(bswap_32big(0x72414ae6U), bswap_32big(0xc2309f0eU), bswap_32big(0x76cb4f4bU),
                       bswap_32big(0x2e126603U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_00F4H, 0x000010a0U);

        r_rsip_func101(bswap_32big(0x35c29730U), bswap_32big(0x1b547c11U), bswap_32big(0x8f96f079U),
                       bswap_32big(0xa1336502U));
    }

    WR1_PROG(REG_0014H, 0x00000040U);
    WR1_PROG(REG_0104H, InData_State[18]);
    WR1_PROG(REG_0014H, 0x00000040U);
    WR1_PROG(REG_0100H, InData_State[19]);

    for (iLoop = 0U; iLoop < 18U; iLoop++)
    {
        WR1_PROG(REG_0014H, 0x00000040U);
        WR1_PROG(REG_0110H, InData_State[iLoop]);
    }

    r_rsip_func101(bswap_32big(0x3963587cU),
                   bswap_32big(0xd508a020U),
                   bswap_32big(0xee8c985dU),
                   bswap_32big(0x6ef33315U));

    return RSIP_RET_PASS;
}
