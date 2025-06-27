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

rsip_ret_t r_rsip_p73r (const uint32_t InData_HashType[], const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

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
            WR1_PROG(REG_00F4H, 0x00001040U);

            r_rsip_func101(bswap_32big(0xd21f9e46U), bswap_32big(0xcd4817a6U), bswap_32big(0xc1b10b75U),
                           bswap_32big(0x99126488U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_00F4H, 0x00001050U);

            r_rsip_func101(bswap_32big(0x172b20f9U), bswap_32big(0x03e34d06U), bswap_32big(0x69f51978U),
                           bswap_32big(0xa4ccdd9eU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_00F4H, 0x00001080U);

            r_rsip_func101(bswap_32big(0x6b6a0864U), bswap_32big(0xbf88b3f1U), bswap_32big(0xc89126a5U),
                           bswap_32big(0xf1a39ff0U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_00F4H, 0x00001090U);

            r_rsip_func101(bswap_32big(0x44037066U), bswap_32big(0x75aac28bU), bswap_32big(0x2924e92fU),
                           bswap_32big(0xb462a447U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_00F4H, 0x000010a0U);

            r_rsip_func101(bswap_32big(0x5812bdecU), bswap_32big(0x874e01d2U), bswap_32big(0x954f5e02U),
                           bswap_32big(0x0f36a76fU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_00F4H, 0x000010b0U);

            r_rsip_func101(bswap_32big(0xb976c145U), bswap_32big(0x53f67fe8U), bswap_32big(0x05e2d1caU),
                           bswap_32big(0xe0c64b6dU));
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

        r_rsip_func101(bswap_32big(0xd3ef283cU), bswap_32big(0xea509580U), bswap_32big(0xaca673d4U),
                       bswap_32big(0x677c7c0dU));

        return RSIP_RET_PASS;
    }
}
