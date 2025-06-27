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

rsip_ret_t r_rsip_pe5i (const uint32_t InData_KeyType[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_MsgLen[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e50001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000001c7U);
    WR1_PROG(REG_1608H, 0x800200a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_2000H, 0x00000001U);

    r_rsip_func100(bswap_32big(0x0cbb78cdU),
                   bswap_32big(0x4aa20986U),
                   bswap_32big(0x1f395d0bU),
                   bswap_32big(0x9964ccc5U));
    WR1_PROG(REG_1600H, 0x3420a8c0U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x2000b4c0U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1600H, 0x00007c06U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00000050U);

        WR1_PROG(REG_1600H, 0x0000b5e0U);
        WR1_PROG(REG_1600H, 0x00000008U);

        r_rsip_func101(bswap_32big(0xfe3ecd34U), bswap_32big(0x33737111U), bswap_32big(0xbd751474U),
                       bswap_32big(0x4dea6e5dU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x000000a0U);

        WR1_PROG(REG_1600H, 0x0000b5e0U);
        WR1_PROG(REG_1600H, 0x0000000cU);

        r_rsip_func101(bswap_32big(0x96614930U), bswap_32big(0x0d7e985dU), bswap_32big(0xc165abc0U),
                       bswap_32big(0x88546956U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x000000b0U);

        WR1_PROG(REG_1600H, 0x0000b5e0U);
        WR1_PROG(REG_1600H, 0x00000010U);

        r_rsip_func101(bswap_32big(0xe4e8284dU), bswap_32big(0xe0eb7cf5U), bswap_32big(0xb2c9e2d9U),
                       bswap_32big(0xcf184edaU));
    }

    WR1_PROG(REG_2008H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x38000ca5U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x6c3b9d72U),
                   bswap_32big(0xc33928c6U),
                   bswap_32big(0xde2c9bceU),
                   bswap_32big(0x04c3e575U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1600H, 0x300030c0U);
        WR1_PROG(REG_1600H, 0x00070020U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x0000001bU);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x00000008U);

        WR1_PROG(REG_1600H, 0x00030040U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000028U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x0000000cU);

        WR1_PROG(REG_1600H, 0x00050040U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000029U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x00000010U);

        WR1_PROG(REG_1600H, 0x00000080U);
        r_rsip_func101(bswap_32big(0x91825c5aU), bswap_32big(0x6ce3a2b5U), bswap_32big(0xe4f579aaU),
                       bswap_32big(0x1ad7037fU));
    }
    else
    {
        WR1_PROG(REG_1600H, 0x300030c0U);
        WR1_PROG(REG_1600H, 0x00070020U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x01b41ce9U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x00000010U);

        WR1_PROG(REG_1600H, 0x00030040U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x0199f119U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x00000010U);

        WR1_PROG(REG_1600H, 0x00050040U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x01b4cab0U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x00000010U);

        WR1_PROG(REG_1600H, 0x00000080U);
        r_rsip_func101(bswap_32big(0x91927292U), bswap_32big(0x3c1a7908U), bswap_32big(0x33c017d8U),
                       bswap_32big(0x263aa7a1U));
    }

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000e501U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x7aac6cefU),
                   bswap_32big(0xd2d33543U),
                   bswap_32big(0x7a29cc7eU),
                   bswap_32big(0x95eaea5aU));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x000034e5U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000e501U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x5ba5844cU),
                   bswap_32big(0x721d7f04U),
                   bswap_32big(0x1d57dac6U),
                   bswap_32big(0x0c2df8b8U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x710840adU),
                   bswap_32big(0xeacfebffU),
                   bswap_32big(0x84b86d05U),
                   bswap_32big(0x2e05a482U));
    WR1_PROG(REG_1608H, 0x81010100U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_1600H, 0x00000929U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    for (iLoop = 0U; iLoop < S_RAM[0]; )
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xf7008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
        WR1_PROG(REG_1400H, 0x01420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000a520U);
        WR1_PROG(REG_1600H, 0x00000004U);
        r_rsip_func101(bswap_32big(0xe592ddabU), bswap_32big(0x88eb6311U), bswap_32big(0x5fa8d0a0U),
                       bswap_32big(0x09fd2a62U));
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000909U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    r_rsip_func100(bswap_32big(0xabe6dfcdU),
                   bswap_32big(0xf5ac1900U),
                   bswap_32big(0x15a859dbU),
                   bswap_32big(0x3186e75dU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe2c3950dU), bswap_32big(0xc8b2db48U), bswap_32big(0x0a9a1ba1U),
                       bswap_32big(0x56287b76U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
        {
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2014H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2010H, 0x00000080U);

            WR1_PROG(REG_200CH, 0x00000001U);

            WAIT_STS(REG_2030H, 8, 0);

            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2014H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2010H, 0x00000000U);

            WR1_PROG(REG_200CH, 0x00000100U);

            r_rsip_func101(bswap_32big(0x2c7c2ac4U), bswap_32big(0x7f4b33dfU), bswap_32big(0xcb61ad34U),
                           bswap_32big(0xae0c057cU));
        }
        else
        {
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, InData_MsgLen[0]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, InData_MsgLen[1]);

            WR1_PROG(REG_200CH, 0x00000001U);

            r_rsip_func101(bswap_32big(0xc9b6e2c3U), bswap_32big(0x31d41c34U), bswap_32big(0x22f8cb2fU),
                           bswap_32big(0x16f0834bU));
        }

        return RSIP_RET_PASS;
    }
}
