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

rsip_ret_t r_rsip_p75f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Msg[],
                        const uint32_t InData_MAC[],
                        const uint32_t InData_length[],
                        uint32_t       MAX_CNT,
                        uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_2030H, 0, 1);

    WR1_PROG(REG_1444H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_2030H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001600U);

    WAIT_STS(REG_2030H, 4, 1);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0xc44e575fU),
                   bswap_32big(0xb39d73feU),
                   bswap_32big(0x3129abb9U),
                   bswap_32big(0xefe727d9U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func100(bswap_32big(0xc47987c4U), bswap_32big(0x77e43a73U), bswap_32big(0xfb0db761U),
                       bswap_32big(0x37e78ca7U));

        WR1_PROG(REG_1600H, 0x00007c04U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func100(bswap_32big(0x4387084cU), bswap_32big(0x039b42dcU), bswap_32big(0x91e98272U),
                           bswap_32big(0x64ff31d4U));
            WR1_PROG(REG_1408H, 0x0000401eU);
            WAIT_STS(REG_1408H, 30, 1);
            RD7_ADDR(REG_1420H, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0xfaa1e43fU), bswap_32big(0x7c268b13U), bswap_32big(0x2e363126U),
                           bswap_32big(0x3bfa9bd2U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            r_rsip_func100(bswap_32big(0x22dc5cd1U), bswap_32big(0x3346fef7U), bswap_32big(0x3a0fbc41U),
                           bswap_32big(0x7009ed0fU));
            WR1_PROG(REG_1408H, 0x00004022U);
            WAIT_STS(REG_1408H, 30, 1);
            RD8_ADDR(REG_1420H, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0x0960b3c3U), bswap_32big(0xacd09037U), bswap_32big(0x3c995204U),
                           bswap_32big(0xb984ea7aU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
        {
            r_rsip_func100(bswap_32big(0x90ed49e7U), bswap_32big(0x098bd813U), bswap_32big(0xa6d6f145U),
                           bswap_32big(0x235ebf98U));
            WR1_PROG(REG_1408H, 0x00004032U);
            WAIT_STS(REG_1408H, 30, 1);
            RD12_ADDR(REG_1420H, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0x352f38c8U), bswap_32big(0xee4e235fU), bswap_32big(0xd2dbdcb1U),
                           bswap_32big(0xc84455c8U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
        {
            r_rsip_func100(bswap_32big(0x4a510798U), bswap_32big(0xfc029359U), bswap_32big(0x290d7027U),
                           bswap_32big(0xf32f787aU));
            WR1_PROG(REG_1408H, 0x00004042U);
            WAIT_STS(REG_1408H, 30, 1);
            RD16_ADDR(REG_1420H, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0xc15fdafaU), bswap_32big(0x628a9928U), bswap_32big(0x29f19258U),
                           bswap_32big(0x4e26e728U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }

        return RSIP_RET_PASS;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x935beb89U), bswap_32big(0x093d4062U), bswap_32big(0xf3193d07U),
                       bswap_32big(0x377e81c4U));

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010020U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_length[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00007c04U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_1600H, 0x0000b440U);
            WR1_PROG(REG_1600H, 0x0000001cU);

            r_rsip_func101(bswap_32big(0x39248654U), bswap_32big(0x2b2ead69U), bswap_32big(0x51bf0030U),
                           bswap_32big(0x0af1a03cU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_1600H, 0x0000b440U);
            WR1_PROG(REG_1600H, 0x00000020U);

            r_rsip_func101(bswap_32big(0x015e4f5eU), bswap_32big(0x93ac7d35U), bswap_32big(0x505b42c2U),
                           bswap_32big(0xe78a74abU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_1600H, 0x0000b440U);
            WR1_PROG(REG_1600H, 0x00000030U);

            r_rsip_func101(bswap_32big(0x0f420d9cU), bswap_32big(0x67696037U), bswap_32big(0xa556cea6U),
                           bswap_32big(0xf938003dU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_1600H, 0x0000b440U);
            WR1_PROG(REG_1600H, 0x00000040U);

            r_rsip_func101(bswap_32big(0x445b7f11U), bswap_32big(0x7dfda686U), bswap_32big(0xd59d7715U),
                           bswap_32big(0x0c6b8496U));
        }

        WR1_PROG(REG_1600H, 0x3420a820U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x34202841U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x288cc714U), bswap_32big(0xb2576d89U), bswap_32big(0x51b3dbd5U),
                       bswap_32big(0x74dda411U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xa591d5d6U), bswap_32big(0x0db6ba0aU), bswap_32big(0xc58cd089U),
                           bswap_32big(0xe475a057U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x8baea9e4U), bswap_32big(0x7d429282U), bswap_32big(0x074aeb80U),
                           bswap_32big(0xbe27aba0U));

            WR1_PROG(REG_1600H, 0x000008c6U);

            WR1_PROG(REG_1600H, 0x000008a5U);

            WR1_PROG(REG_1600H, 0x0000a440U);
            WR1_PROG(REG_1600H, 0x0000000fU);
            WR1_PROG(REG_1600H, 0x00046842U);
            WR1_PROG(REG_1600H, 0x00026c42U);

            WR1_PROG(REG_1608H, 0x81010040U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; )
            {
                r_rsip_func100(bswap_32big(0xda719471U),
                               bswap_32big(0x7b6e23daU),
                               bswap_32big(0x84d9cf3bU),
                               bswap_32big(0x9e8619abU));

                WR1_PROG(REG_1600H, 0x000008e7U);

                WR1_PROG(REG_1600H, 0x00000863U);

                WR1_PROG(REG_1600H, 0x380088c0U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1600H, 0x2000d060U);

                WR1_PROG(REG_1600H, 0x38008880U);
                WR1_PROG(REG_1600H, 0x00000001U);
                WR1_PROG(REG_1600H, 0x2000d060U);

                WR1_PROG(REG_1600H, 0x00007c03U);
                WR1_PROG(REG_143CH, 0x00600000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_1608H, 0x80830007U);
                    WR1_PROG(REG_1400H, 0x0345000dU);

                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1444H, 0x000002c1U);
                    WR1_PROG(REG_1824H, 0x08000045U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR3_ADDR(REG_1420H, &InData_MAC[iLoop]);
                    WR1_PROG(REG_1444H, 0x000000a1U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                    r_rsip_func101(bswap_32big(0x29f7ab0aU),
                                   bswap_32big(0xad41feb8U),
                                   bswap_32big(0x65713280U),
                                   bswap_32big(0xfd39715eU));
                }
                else
                {
                    WR1_PROG(REG_1608H, 0x80840007U);
                    WR1_PROG(REG_1400H, 0x03450011U);

                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1444H, 0x000003c1U);
                    WR1_PROG(REG_1824H, 0x08000045U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_MAC[iLoop]);

                    r_rsip_func101(bswap_32big(0x771de06aU),
                                   bswap_32big(0x427323c3U),
                                   bswap_32big(0x5f6f85f0U),
                                   bswap_32big(0x57bd697cU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00000800U);
                for (jLoop = 0U; jLoop < 16U; jLoop++)
                {
                    WR1_PROG(REG_1600H, 0x3c0028a1U);
                    WR1_PROG(REG_1600H, 0x12003c07U);
                    WR1_PROG(REG_1600H, 0x00002ce0U);
                    WR1_PROG(REG_1600H, 0x00002ca0U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1824H, 0x9c000005U);
                WR1_PROG(REG_1600H, 0x000008e7U);
                WR1_PROG(REG_1608H, 0x81840007U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000a4c0U);
                WR1_PROG(REG_1600H, 0x00000004U);

                r_rsip_func101(bswap_32big(0x298e2ab0U),
                               bswap_32big(0x9a2d1b27U),
                               bswap_32big(0xec3c2ceaU),
                               bswap_32big(0xd524cbf6U));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1600H, 0x000008c2U);

            WR1_PROG(REG_1600H, 0x00007c06U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func100(bswap_32big(0xaf6f5e67U), bswap_32big(0x773f2216U), bswap_32big(0x094b1d18U),
                           bswap_32big(0x8548d3f2U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x252b31a1U),
                               bswap_32big(0x91cc3fbfU),
                               bswap_32big(0x7447417eU),
                               bswap_32big(0x435514d4U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x5b1ad2ecU),
                               bswap_32big(0x7e0c8e9cU),
                               bswap_32big(0x85adf7f4U),
                               bswap_32big(0xe831d6deU));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
