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

rsip_ret_t r_rsip_p29i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00290001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000005U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00002901U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xb8c95dfaU),
                   bswap_32big(0x26346072U),
                   bswap_32big(0x1ea7cc01U),
                   bswap_32big(0xc1d23e86U));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x1f4082a7U),
                   bswap_32big(0xbc26aed5U),
                   bswap_32big(0x9b74cee5U),
                   bswap_32big(0x11b69b68U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x10203742U), bswap_32big(0x6fba1dc2U), bswap_32big(0xb598bef1U),
                       bswap_32big(0xa122495aU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100a0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x38000ca5U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0xb0226955U), bswap_32big(0xe0e6e374U), bswap_32big(0x21357aa4U),
                       bswap_32big(0xaa7df27bU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            WR1_PROG(REG_00B0H, 0x00000401U);
            WR1_PROG(REG_0000H, 0x00c10009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000402U);
            WR1_PROG(REG_0000H, 0x00c10009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0xa7c167afU), bswap_32big(0xddbd352aU), bswap_32big(0xbbf363e1U),
                           bswap_32big(0x7aa2a957U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00002902U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x1c5bd2cfU), bswap_32big(0xa3a10b38U), bswap_32big(0xb309c89dU),
                           bswap_32big(0x87243e35U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xbd2ac25aU), bswap_32big(0xeeae7d02U), bswap_32big(0x070c95c7U),
                           bswap_32big(0xae54bc65U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x36c07422U),
                               bswap_32big(0x3bbabe6aU),
                               bswap_32big(0x12e445e7U),
                               bswap_32big(0xca317c5cU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xfe97af4fU),
                               bswap_32big(0x24338431U),
                               bswap_32big(0xa3ecc029U),
                               bswap_32big(0xbbd9edeaU));
            }
        }

        r_rsip_func100(bswap_32big(0xb81d7e60U), bswap_32big(0x4619f588U), bswap_32big(0x1c3cfe8eU),
                       bswap_32big(0x610cdc13U));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_009CH, 0x81840000U);
        WR1_PROG(REG_0000H, 0x00490011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_009CH, 0x80840000U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x240757f7U), bswap_32big(0x57a79af1U), bswap_32big(0xc2f702f9U),
                       bswap_32big(0xf46d40c1U));
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0a0000a4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0xc0f5d505U), bswap_32big(0xba22e2e3U), bswap_32big(0xc49c97a4U),
                       bswap_32big(0x888c9928U));

        return RSIP_RET_PASS;
    }
}
