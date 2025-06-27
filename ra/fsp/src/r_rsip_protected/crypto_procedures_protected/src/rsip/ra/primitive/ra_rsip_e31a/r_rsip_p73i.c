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

rsip_ret_t r_rsip_p73i (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00730001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00F0H, 0x00000001U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0x909ac921U),
                   bswap_32big(0x00d2d1beU),
                   bswap_32big(0x8d6e21ceU),
                   bswap_32big(0xce587e11U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x5c57a08eU), bswap_32big(0x38aa694bU), bswap_32big(0xe7fc39bdU),
                       bswap_32big(0x88f8e66eU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x072e9c18U), bswap_32big(0xbf4fa3e0U), bswap_32big(0x83056207U),
                       bswap_32big(0x1b9aa55bU));
        WR1_PROG(REG_0094H, 0x3420a800U);
        WR1_PROG(REG_0094H, 0x00000007U);
        WR1_PROG(REG_0094H, 0x2000b400U);
        WR1_PROG(REG_0094H, 0x00000006U);

        WR1_PROG(REG_0094H, 0x00007c00U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_00F4H, 0x00000040U);

            r_rsip_func101(bswap_32big(0x6e8d9c91U), bswap_32big(0x89404aa5U), bswap_32big(0xf542815eU),
                           bswap_32big(0x031cea6fU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_00F4H, 0x00000050U);

            r_rsip_func101(bswap_32big(0x33d53a44U), bswap_32big(0x57eee603U), bswap_32big(0xa5a162b5U),
                           bswap_32big(0x62cd5c1dU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_00F4H, 0x00000080U);

            r_rsip_func101(bswap_32big(0x15f05247U), bswap_32big(0xaef43d75U), bswap_32big(0x3e969f17U),
                           bswap_32big(0xe6198ae0U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_00F4H, 0x00000090U);

            r_rsip_func101(bswap_32big(0x98f7db5eU), bswap_32big(0x10ebd48dU), bswap_32big(0x225a04feU),
                           bswap_32big(0x8b6f9ed7U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_00F4H, 0x000000a0U);

            r_rsip_func101(bswap_32big(0xdeda3998U), bswap_32big(0xf182bf88U), bswap_32big(0x744d8a32U),
                           bswap_32big(0xd90e9855U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_00F4H, 0x000000b0U);

            r_rsip_func101(bswap_32big(0x60a19657U), bswap_32big(0x305bcd22U), bswap_32big(0xfa4c989cU),
                           bswap_32big(0xcfb2fe76U));
        }

        if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
        {
            WR1_PROG(REG_00FCH, 0x00000100U);

            r_rsip_func101(bswap_32big(0x3b079f3eU), bswap_32big(0xb376ca65U), bswap_32big(0x823af9f0U),
                           bswap_32big(0xf3e46298U));
        }
        else
        {
            WR1_PROG(REG_0014H, 0x00000040U);
            WR1_PROG(REG_0104H, InData_MsgLen[0]);
            WR1_PROG(REG_0014H, 0x00000040U);
            WR1_PROG(REG_0100H, InData_MsgLen[1]);

            r_rsip_func101(bswap_32big(0x37e554cbU), bswap_32big(0x9153eb17U), bswap_32big(0x9402a051U),
                           bswap_32big(0x3d667edeU));
        }

        return RSIP_RET_PASS;
    }
}
