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

rsip_ret_t r_rsip_pe4 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e40001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x00000080U);

    r_rsip_func100(bswap_32big(0xd5f125f5U),
                   bswap_32big(0xf7c17f87U),
                   bswap_32big(0x3079980dU),
                   bswap_32big(0x7aa272ccU));
    WR1_PROG(REG_1600H, 0x00007c04U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x015c5d71U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000008U));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x01b41ce9U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x80010120U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000008U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe7db7d16U), bswap_32big(0x47d17c8dU), bswap_32big(0xe98e2e9eU),
                       bswap_32big(0x437236aeU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x0165e3d8U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000000cU));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x0199f119U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x80010120U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000000cU));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x09d28fa7U), bswap_32big(0x49bd886eU), bswap_32big(0x2453bfd7U),
                       bswap_32big(0xf77100b1U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x01ea2366U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000014U));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x0000b500U);
        WR1_PROG(REG_1600H, 0x01b4cab0U);

        r_rsip_func101(bswap_32big(0x0f5c4b8aU), bswap_32big(0x596cfa9eU), bswap_32big(0xcc0121f7U),
                       bswap_32big(0xcf95d633U));
    }

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x000000e4U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x3fc5e441U),
                   bswap_32big(0xb5c7d2fcU),
                   bswap_32big(0x04706163U),
                   bswap_32big(0x7b3250a3U));
    r_rsip_func407(InData_EncSecret);

    r_rsip_func100(bswap_32big(0x931c5b02U),
                   bswap_32big(0xf9413ac0U),
                   bswap_32big(0x87526a56U),
                   bswap_32big(0x2a2c4c57U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x0426806bU), bswap_32big(0x87c13f95U), bswap_32big(0xc597726aU),
                       bswap_32big(0xe2e2252dU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38008880U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x52c1c885U), bswap_32big(0x74c0903aU), bswap_32big(0xd3b54501U),
                       bswap_32big(0x91ddcbffU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_2000H, 0x00000001U);

            WR1_PROG(REG_2004H, 0x000000b0U);

            WR1_PROG(REG_2014H, 0x00000000U);
            WR1_PROG(REG_2010H, 0x00000210U);

            r_rsip_func408();

            WR1_PROG(REG_1600H, 0x000008a5U);

            WR1_PROG(REG_1608H, 0x81910005U);
            WR1_PROG(REG_1400H, 0x01490045U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WAIT_STS(REG_2030H, 8, 0);
            WR1_PROG(REG_143CH, 0x00001600U);

            WR1_PROG(REG_1608H, 0x80900005U);
            WR1_PROG(REG_1400H, 0x03450041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func101(bswap_32big(0x48a2c017U), bswap_32big(0x05449a11U), bswap_32big(0xcb8f6bcfU),
                           bswap_32big(0x7580b256U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x6223ae3eU), bswap_32big(0xc7588bb3U), bswap_32big(0xedeab21cU),
                           bswap_32big(0x9f2bcfe0U));
            WR1_PROG(REG_1608H, 0x81010120U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            for (iLoop = S_RAM[0]; iLoop < 16U; )
            {
                WR1_PROG(REG_1608H, 0x80840005U);
                WR1_PROG(REG_1400H, 0x03400011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000a4e0U);
                WR1_PROG(REG_1600H, 0x00000004U);

                WR1_PROG(REG_1600H, 0x0000a4a0U);
                WR1_PROG(REG_1600H, 0x00000010U);

                r_rsip_func101(bswap_32big(0x22c46f05U),
                               bswap_32big(0xeabd6d34U),
                               bswap_32big(0xe06a5f4fU),
                               bswap_32big(0x75117038U));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x380088e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xff08fe16U), bswap_32big(0xff16525cU), bswap_32big(0x36078c43U),
                           bswap_32big(0x09a58395U));
        }

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x000000e4U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xdcc62c05U), bswap_32big(0xee9ca8f6U), bswap_32big(0x1b41e61dU),
                       bswap_32big(0xb59bcc06U));
        r_rsip_func103();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1608H, 0x80010000U);
        WR1_PROG(REG_1400H, 0x03420005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x000034e0U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x000000e4U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x6c1d6fb2U), bswap_32big(0x5f449d72U), bswap_32big(0xda70c5a5U),
                       bswap_32big(0x911509b0U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x000034e8U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x000000e4U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x6b3ab4beU), bswap_32big(0xd886991aU), bswap_32big(0xc245b521U),
                       bswap_32big(0xc8e2b593U));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0x4e85b904U), bswap_32big(0xc3dfba74U), bswap_32big(0x17571f6cU),
                       bswap_32big(0x92d82d0aU));
        WR1_PROG(REG_1600H, 0x000008a5U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xe7009d07U);
        WR1_PROG(REG_1608H, 0x81900005U);
        WR1_PROG(REG_1400H, 0x00890021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002022U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

        r_rsip_func100(bswap_32big(0x25d9af11U), bswap_32big(0x2741f014U), bswap_32big(0x441910dcU),
                       bswap_32big(0x2087bd83U));
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xe7008d07U);
        WR1_PROG(REG_1400H, 0x00890021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002022U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_KeyIndex[9]);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_KeyIndex[13]);

        r_rsip_func100(bswap_32big(0xacc36738U), bswap_32big(0x12ede9c3U), bswap_32big(0x3715382fU),
                       bswap_32big(0xf837907aU));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x09108105U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_KeyIndex[17]);

        r_rsip_func100(bswap_32big(0x4ad190fdU), bswap_32big(0x0c4229d9U), bswap_32big(0xbc068aa0U),
                       bswap_32big(0xeb4c7341U));
        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

        r_rsip_func102(bswap_32big(0x6e22f4d9U), bswap_32big(0x9584fd4bU), bswap_32big(0x46c38572U),
                       bswap_32big(0xb34526ecU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
}
