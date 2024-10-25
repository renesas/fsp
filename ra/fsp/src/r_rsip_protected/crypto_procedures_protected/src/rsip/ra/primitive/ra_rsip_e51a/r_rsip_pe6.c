/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_pe6 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataLength[],
                       uint32_t       OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e60001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000002c7U);
    WR1_PROG(REG_1608H, 0x80030080U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KDFInfo_Count[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_OutDataLength[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xeda84baeU), bswap_32big(0x11e4cf57U), bswap_32big(0xa1996aedU), bswap_32big(0xbf2ddc83U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xb7b03eedU), bswap_32big(0x6999d79fU), bswap_32big(0x0e7349fdU), bswap_32big(0x4e71630aU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1600H, 0x380088a0U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);

        WR1_PROG(REG_1600H, 0x380088a0U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);

        WR1_PROG(REG_1600H, 0x38000fffU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0xbb5d04b8U), bswap_32big(0x84a2ff39U), bswap_32big(0x3d8ec700U), bswap_32big(0x47fb57fcU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x1f3fba51U), bswap_32big(0xe695bda5U), bswap_32big(0xd4bece39U), bswap_32big(0xe9373417U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x00003545U);
            WR1_PROG(REG_1600H, 0x00056d4aU);

            WR1_PROG(REG_1600H, 0x3420a8c0U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_1600H, 0x34202946U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0xc0d315b4U), bswap_32big(0x421950b9U), bswap_32big(0x5b89ba11U), bswap_32big(0xecfed1b0U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xc9264e56U), bswap_32big(0x70b76542U), bswap_32big(0x998a6591U), bswap_32big(0xcb9c0fd4U));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x5fc2fec2U), bswap_32big(0x3167d66cU), bswap_32big(0xc55b1750U), bswap_32big(0x144cee0aU));
                WR1_PROG(REG_1608H, 0x810100a0U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1600H, 0x00000908U);

                WR1_PROG(REG_1600H, 0x00000929U);

                WR1_PROG(REG_1600H, 0x000009ceU);

                WR1_PROG(REG_1600H, 0x000009efU);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x34202905U);
                    WR1_PROG(REG_1600H, 0x2000d1e0U);
                    WR1_PROG(REG_1600H, 0x00007c0fU);
                    WR1_PROG(REG_143CH, 0x00602000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x800100e0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, InData_KDFInfo[iLoop * 13]);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e601U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x58f37dc5U), bswap_32big(0x5592e2c6U), bswap_32big(0x94b19136U), bswap_32big(0x520fdbcfU));
                    r_rsip_func043();

                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1600H, 0x01799093U);
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e601U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x5d60f3faU), bswap_32big(0x2db9487aU), bswap_32big(0xe10967efU), bswap_32big(0xfa6b512eU));
                    r_rsip_func044();

                    WR1_PROG(REG_1444H, 0x000007c2U);
                    WR1_PROG(REG_1A2CH, 0x40000100U);
                    WR1_PROG(REG_1A24H, 0xf7009d07U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 13 + 1]);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 13 + 5]);

                    WR1_PROG(REG_1608H, 0x80880009U);
                    WR1_PROG(REG_1400H, 0x03420021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1444H, 0x000003c2U);
                    WR1_PROG(REG_1A2CH, 0x40000000U);
                    WR1_PROG(REG_1A24H, 0x07008d05U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 13 + 9]);

                    WR1_PROG(REG_1A24H, 0x9c100005U);
                    WR1_PROG(REG_1400H, 0x00820011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002d00U);

                    WR1_PROG(REG_1600H, 0x0000a520U);
                    WR1_PROG(REG_1600H, 0x00000020U);

                    r_rsip_func100(bswap_32big(0xc75003e9U), bswap_32big(0x595b5208U), bswap_32big(0x2b9ccd46U), bswap_32big(0x877c9953U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x0000d1c0U);
                        r_rsip_func101(bswap_32big(0x0493bfe2U), bswap_32big(0x2bd02703U), bswap_32big(0xe397b330U), bswap_32big(0x68c4f4a0U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xb2b48e37U), bswap_32big(0x483d2f49U), bswap_32big(0x423c7e03U), bswap_32big(0x3e0d13a5U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);
                }

                WR1_PROG(REG_1600H, 0x38000905U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000dceU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);
                r_rsip_func100(bswap_32big(0xe8babcc0U), bswap_32big(0xa4868ecbU), bswap_32big(0xeff0367aU), bswap_32big(0xed7c8154U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x31f7e590U), bswap_32big(0x91c8a207U), bswap_32big(0x0cbfae64U), bswap_32big(0xe1346b96U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xaea501f6U), bswap_32big(0x85a8445dU), bswap_32big(0x3907ebfeU), bswap_32big(0x12ceb557U));
                    WR1_PROG(REG_1608H, 0x810100c0U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &S_RAM[0]);
                    S_RAM[0] = bswap_32big(S_RAM[0]);

                    WR1_PROG(REG_1600H, 0x0000094aU);

                    WR1_PROG(REG_1600H, 0x0000b560U);
                    WR1_PROG(REG_1600H, 0x00000040U);
                    WR1_PROG(REG_1600H, 0x00002966U);

                    WR1_PROG(REG_1600H, 0x00000908U);
                    WR1_PROG(REG_1600H, 0x00003526U);

                    for (iLoop = S_RAM[0]; iLoop < 64U; iLoop++)
                    {
                        WR1_PROG(REG_1600H, 0x02003d49U);
                        WR1_PROG(REG_1600H, 0x00002d00U);
                        WR1_PROG(REG_1600H, 0x00002d20U);
                        r_rsip_func101(bswap_32big(0x7712b89eU), bswap_32big(0x9b9abec1U), bswap_32big(0x59e02ae2U), bswap_32big(0x12044e6eU));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x3800090bU);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func100(bswap_32big(0xfd0ef90fU), bswap_32big(0x2569bdc4U), bswap_32big(0x453440e4U), bswap_32big(0xe5bfdb5fU));
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
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e602U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0xb455c518U), bswap_32big(0xd30588d5U), bswap_32big(0xf7989243U), bswap_32big(0x2a9a9dcdU));
                    r_rsip_func043();

                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1600H, 0x01b41ce9U);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e602U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x818b786aU), bswap_32big(0xeba5df0eU), bswap_32big(0x1b32ffd2U), bswap_32big(0x6f1c82f1U));
                    r_rsip_func044();

                    r_rsip_func100(bswap_32big(0x5b824665U), bswap_32big(0x31202ed1U), bswap_32big(0x929e7270U), bswap_32big(0x17a91801U));
                    WR1_PROG(REG_1600H, 0x00000929U);
                    WR1_PROG(REG_1A2CH, 0x40000100U);
                    WR1_PROG(REG_1A24H, 0xe7009d07U);

                    WR1_PROG(REG_1608H, 0x81900009U);
                    WR1_PROG(REG_1400H, 0x00890021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1408H, 0x00002022U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

                    r_rsip_func100(bswap_32big(0x03e2f623U), bswap_32big(0x9931a480U), bswap_32big(0xdd19d07aU), bswap_32big(0xb96ead96U));
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

                    r_rsip_func100(bswap_32big(0x05855d7aU), bswap_32big(0x59e3f930U), bswap_32big(0xa1cc8cd3U), bswap_32big(0xe596233bU));
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

                    r_rsip_func100(bswap_32big(0x0c3a9da3U), bswap_32big(0xce12cd51U), bswap_32big(0x40140142U), bswap_32big(0x2d298f8eU));
                    WR1_PROG(REG_1608H, 0x81010000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x7b06b4eeU), bswap_32big(0xfd66a282U), bswap_32big(0xbb25d0ffU), bswap_32big(0xe5dd99f1U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
