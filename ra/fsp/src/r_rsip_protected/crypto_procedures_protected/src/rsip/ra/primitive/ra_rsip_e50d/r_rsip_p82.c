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

rsip_ret_t r_rsip_p82 (void)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00820001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b070194U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x01c7ba56U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b070184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x01fd9cb7U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000074U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x3000a820U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WAIT_STS(REG_1708H, 0, 0);
    WR1_PROG(REG_143CH, 0x00001200U);
    WAIT_STS(REG_1708H, 0, 0);
    WR1_PROG(REG_1704H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x00000863U);

    WR1_PROG(REG_1600H, 0x0000b540U);
    WR1_PROG(REG_1600H, 0x00000028U);

    for (jLoop = 0U; jLoop < 3U; jLoop++)
    {
        r_rsip_func100(bswap_32big(0xa77e3c75U), bswap_32big(0xe488ce93U), bswap_32big(0x8404d3f7U),
                       bswap_32big(0xa49c7658U));
        WR1_PROG(REG_1600H, 0x00000884U);

        WR1_PROG(REG_1600H, 0x000008a5U);

        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000013U);

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000355U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x000000aaU);

        WR1_PROG(REG_1600H, 0x00007c01U);
        WR1_PROG(REG_143CH, 0x00600000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            WAIT_STS(REG_1708H, 0, 0);
            WAIT_STS(REG_1708H, 0, 0);
            WR1_PROG(REG_1704H, 0x00200007U);

            r_rsip_func101(bswap_32big(0x2ea36172U), bswap_32big(0xb612e170U), bswap_32big(0x1384ad46U),
                           bswap_32big(0x7be9d812U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            WAIT_STS(REG_1708H, 0, 0);
            WAIT_STS(REG_1708H, 0, 0);
            WR1_PROG(REG_1704H, 0x00200005U);

            r_rsip_func101(bswap_32big(0x39d1acebU), bswap_32big(0xd3094a50U), bswap_32big(0x21dc54ccU),
                           bswap_32big(0xced222ceU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            WAIT_STS(REG_1708H, 0, 0);
            WAIT_STS(REG_1708H, 0, 0);
            WR1_PROG(REG_1704H, 0x00200006U);

            r_rsip_func101(bswap_32big(0xcec77843U), bswap_32big(0xae9def84U), bswap_32big(0x35eab8f1U),
                           bswap_32big(0x1e65445dU));
        }

        WR1_PROG(REG_1A2CH, 0x40000700U);
        WR1_PROG(REG_1A24H, 0x0e3c8407U);
        WR1_PROG(REG_1400H, 0x00840081U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1708H, 2, 1);
        WR1_PROG(REG_143CH, 0x00001200U);

        WAIT_STS(REG_1A28H, 6, 0);
        WR1_PROG(REG_143CH, 0x00000a00U);
        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1608H, 0x808a0000U);
        WR1_PROG(REG_1400H, 0x03440029U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x000038a0U);
        WR1_PROG(REG_1600H, 0x00003405U);
        WR1_PROG(REG_1600H, 0x00002804U);

        WR1_PROG(REG_1600H, 0x342028e0U);
        WR1_PROG(REG_1600H, 0x10005066U);

        WR1_PROG(REG_1600H, 0x34202808U);
        WR1_PROG(REG_1600H, 0x10005066U);

        WR1_PROG(REG_1600H, 0x00003485U);

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x0000005AU);

        WR1_PROG(REG_1600H, 0x00000842U);

        WR1_PROG(REG_1600H, 0x000008c6U);

        WR1_PROG(REG_1600H, 0x0000b480U);
        WR1_PROG(REG_1600H, 0x00000004U);

        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000002U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x01003804U);

            WR1_PROG(REG_1600H, 0x342028e0U);
            WR1_PROG(REG_1600H, 0x10005066U);

            WR1_PROG(REG_1600H, 0x00002440U);

            WR1_PROG(REG_1600H, 0x00002cc0U);

            WR1_PROG(REG_1600H, 0x00002485U);
        }

        WR1_PROG(REG_1600H, 0x38008840U);
        WR1_PROG(REG_1600H, 0x00000100U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_143CH, 0x00402000U);

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000037U);

        WR1_PROG(REG_1600H, 0x0000b480U);
        WR1_PROG(REG_1600H, 0x00000024U);

        WR1_PROG(REG_1600H, 0x01003804U);

        WR1_PROG(REG_1600H, 0x342028e0U);
        WR1_PROG(REG_1600H, 0x10005066U);

        WR1_PROG(REG_1600H, 0x00002cc0U);

        WR1_PROG(REG_1600H, 0x0000b480U);
        WR1_PROG(REG_1600H, 0x00000026U);

        WR1_PROG(REG_1600H, 0x01003804U);

        WR1_PROG(REG_1600H, 0x342028e0U);
        WR1_PROG(REG_1600H, 0x10005066U);

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c300104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1608H, 0x8084000aU);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000a540U);
        WR1_PROG(REG_1600H, 0x00000010U);

        WAIT_STS(REG_1708H, 0, 0);
        WR1_PROG(REG_143CH, 0x00001200U);
        WAIT_STS(REG_1708H, 0, 0);
        WR1_PROG(REG_1704H, 0x00000080U);

        r_rsip_func101(bswap_32big(0xbab72790U), bswap_32big(0xfb0c6732U), bswap_32big(0x811e0c23U),
                       bswap_32big(0xd0bff33eU));
    }

    WR1_PROG(REG_1600H, 0x38008940U);
    WR1_PROG(REG_1600H, 0x00000058U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_143CH, 0x00402000U);

    WR1_PROG(REG_1600H, 0x00002c20U);

    WR1_PROG(REG_1600H, 0x38008860U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xd5280305U),
                   bswap_32big(0x5ec838a5U),
                   bswap_32big(0x90bea9beU),
                   bswap_32big(0x256d53e4U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xf507c391U), bswap_32big(0x78d1eee7U), bswap_32big(0xfd5e3a3eU),
                       bswap_32big(0x1da36422U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_RETRY;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xfe11703cU), bswap_32big(0xa74f70e6U), bswap_32big(0xd54d9ce6U),
                       bswap_32big(0xbc64834cU));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x080000a4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0x78d85999U), bswap_32big(0x9b1eb53aU), bswap_32big(0xa6c5fb76U),
                       bswap_32big(0xba500f61U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x080000b4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0x6a6d91c8U), bswap_32big(0xd200e279U), bswap_32big(0x37bf43beU),
                       bswap_32big(0x7e2b3a4bU));
        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x08000075U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000000U),
                 bswap_32big(0x00000001U));

        WR1_PROG(REG_1A2CH, 0x40000200U);
        WR1_PROG(REG_1A24H, 0x07328d07U);
        WR1_PROG(REG_1600H, 0x0000b540U);
        WR1_PROG(REG_1600H, 0x00000028U);
        WR1_PROG(REG_1608H, 0x818c000aU);
        WR1_PROG(REG_1400H, 0x00890031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A24H, 0x080000b5U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x02cabe3fU), bswap_32big(0xb73fe20fU), bswap_32big(0xfefa233cU),
                       bswap_32big(0x2cd272b2U));
        WR1_PROG(REG_1A24H, 0x08000075U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A24H, 0x080000a5U);
        WR1_PROG(REG_1608H, 0x81040000U);
        WR1_PROG(REG_1400H, 0x00890011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00008201U));

        r_rsip_func101(bswap_32big(0xdb1ca3daU), bswap_32big(0x0d8bc17dU), bswap_32big(0x6dd1eae6U),
                       bswap_32big(0x05e952ecU));
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0xaf8c71bbU), bswap_32big(0x15be5a17U), bswap_32big(0x48e8cf97U),
                       bswap_32big(0xc3e545cdU));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c2000d4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00008202U));

        r_rsip_func101(bswap_32big(0xe6492cc9U), bswap_32big(0xc153eb3aU), bswap_32big(0x09045a7aU),
                       bswap_32big(0xd7677e44U));
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0x001d4e5aU), bswap_32big(0x4cd977afU), bswap_32big(0xb6bff34dU),
                       bswap_32big(0x3df768d8U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &S_RAM[16]);
        S_RAM[16] = bswap_32big(S_RAM[16]);
        S_RAM[17] = bswap_32big(S_RAM[17]);
        S_RAM[18] = bswap_32big(S_RAM[18]);
        S_RAM[19] = bswap_32big(S_RAM[19]);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00008203U));

        r_rsip_func101(bswap_32big(0xe1921c22U), bswap_32big(0x8f2f5ccfU), bswap_32big(0xc40c04f3U),
                       bswap_32big(0x160998c8U));
        r_rsip_func103();
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1404H, 0x20000000U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x10000000U);
        WR1_PROG(REG_1400H, 0x00c01001U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1B00H, 0x00008002U);
        WR1_PROG(REG_1B08H, 0x00000d01U);

        WR1_PROG(REG_1B00H, 0x00008001U);

        WR1_PROG(REG_1B08H, 0x00000214U);

        r_rsip_func102(bswap_32big(0x2aee58bcU), bswap_32big(0xa1214cddU), bswap_32big(0x30944b8bU),
                       bswap_32big(0x64f0fc69U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
}
