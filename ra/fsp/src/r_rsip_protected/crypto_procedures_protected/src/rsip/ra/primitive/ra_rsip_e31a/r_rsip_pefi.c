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

rsip_ret_t r_rsip_pefi (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
{
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
        WR1_PROG(REG_00F4H, 0x00000050U);

        r_rsip_func101(bswap_32big(0x5ab6d0e5U), bswap_32big(0x7f3af3f4U), bswap_32big(0x62206a1cU),
                       bswap_32big(0x1593d603U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_00F4H, 0x000000a0U);

        r_rsip_func101(bswap_32big(0x1f1f7124U), bswap_32big(0xbe429551U), bswap_32big(0x7964ba0cU),
                       bswap_32big(0x2177bd3eU));
    }

    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    WR1_PROG(REG_0094H, 0x00003c01U);

    if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
    {
        WR1_PROG(REG_00FCH, 0x00000100U);

        r_rsip_func101(bswap_32big(0x11f562daU), bswap_32big(0xd6132db3U), bswap_32big(0xf2d846b8U),
                       bswap_32big(0xd8f560d7U));
    }
    else
    {
        WR1_PROG(REG_0014H, 0x00000040U);
        WR1_PROG(REG_0104H, InData_MsgLen[0]);
        WR1_PROG(REG_0014H, 0x00000040U);
        WR1_PROG(REG_0100H, InData_MsgLen[1]);

        r_rsip_func101(bswap_32big(0x1af3fa18U), bswap_32big(0xf89ca8e0U), bswap_32big(0x34d44bf7U),
                       bswap_32big(0x6685241fU));
    }

    return RSIP_RET_PASS;
}
