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

rsip_ret_t r_rsip_pefu (const uint32_t InData_Msg1[],
                        const uint32_t InData_Msg1Length[],
                        const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[],
                        const uint32_t InData_Msg2[],
                        const uint32_t InData_Msg2Length[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1444H, 0x000002c7U);
    WR1_PROG(REG_1608H, 0x80030060U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Msg1Length[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_EncMsgLength[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Msg2Length[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008c60U);
    WR1_PROG(REG_1600H, 0xfffffffeU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x00002423U);
    WR1_PROG(REG_1600H, 0x00002424U);
    WR1_PROG(REG_1600H, 0x00002425U);

    r_rsip_func100(bswap_32big(0x1c49160aU),
                   bswap_32big(0x7fe24e0fU),
                   bswap_32big(0xc384a3bdU),
                   bswap_32big(0x768406deU));
    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1600H, 0x38008c80U);
        WR1_PROG(REG_1600H, 0xfffffff7U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        WR1_PROG(REG_1600H, 0x38008c20U);
        WR1_PROG(REG_1600H, 0x0000000fU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func101(bswap_32big(0x1cef1d86U), bswap_32big(0x3fb53619U), bswap_32big(0x6d633336U),
                       bswap_32big(0x17338866U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1600H, 0x38008c80U);
        WR1_PROG(REG_1600H, 0xfffffff3U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        WR1_PROG(REG_1600H, 0x38008c20U);
        WR1_PROG(REG_1600H, 0x0000001fU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func101(bswap_32big(0xfff41ebeU), bswap_32big(0x7693f902U), bswap_32big(0x13da4941U),
                       bswap_32big(0x708917a7U));
    }

    r_rsip_func100(bswap_32big(0xdf3b3537U),
                   bswap_32big(0xff9e4402U),
                   bswap_32big(0x76d5381bU),
                   bswap_32big(0x45e54921U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x94f24b7bU), bswap_32big(0x5adde9deU), bswap_32big(0x629a27a7U),
                       bswap_32big(0xf4c22bf6U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x00000821U);

        WR1_PROG(REG_1600H, 0x00003405U);

        WR1_PROG(REG_1600H, 0x38000c84U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x17e531a9U), bswap_32big(0x4dd1b1b6U), bswap_32big(0x21bb2f5cU),
                       bswap_32big(0x4c74e2d6U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x800100e0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_EncMsg[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000ef01U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x523d1173U), bswap_32big(0x462beca5U), bswap_32big(0xb2cfe07cU),
                           bswap_32big(0xc37b7158U));
            r_rsip_func043();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x01799093U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000ef01U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x4a3cb98eU), bswap_32big(0x4d794415U), bswap_32big(0xd8b528ffU),
                           bswap_32big(0x142012d1U));
            r_rsip_func044();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1600H, 0x000038a7U);

            r_rsip_func100(bswap_32big(0x17bd9c23U), bswap_32big(0x813e23d0U), bswap_32big(0x8921e85eU),
                           bswap_32big(0x772983c6U));

            WR1_PROG(REG_1600H, 0x00007c05U);
            WR1_PROG(REG_143CH, 0x00600000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
            {
                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_EncMsg[1]);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_EncMsg[5]);

                WR1_PROG(REG_1404H, 0x10000000U);
                WR1_PROG(REG_1400H, 0x00c20021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_EncMsg[9]);

                r_rsip_func101(bswap_32big(0xad13ae01U),
                               bswap_32big(0xe9ccdee6U),
                               bswap_32big(0xbcdb1f08U),
                               bswap_32big(0x338d143aU));
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
            {
                WR1_PROG(REG_1444H, 0x00000bc2U);
                WR1_PROG(REG_1A2CH, 0x40000200U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);

                for (iLoop = 0U; iLoop < 12U; )
                {
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_EncMsg[1 + iLoop]);
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1404H, 0x10000000U);
                WR1_PROG(REG_1400H, 0x00c20031U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_EncMsg[13]);

                r_rsip_func101(bswap_32big(0xb963669fU),
                               bswap_32big(0x41453a72U),
                               bswap_32big(0xe5c6220aU),
                               bswap_32big(0xa2758202U));
            }

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0x7bc7555bU), bswap_32big(0xc2bfa16bU), bswap_32big(0x150655d5U),
                           bswap_32big(0x94ad17e1U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00002c20U);
                r_rsip_func101(bswap_32big(0x220aae16U),
                               bswap_32big(0x8761fa71U),
                               bswap_32big(0xe0369152U),
                               bswap_32big(0x68c7e246U));
            }

            r_rsip_func101(bswap_32big(0x27e7d387U), bswap_32big(0x94fe36e6U), bswap_32big(0x9017d7bdU),
                           bswap_32big(0xbc18f312U));
        }

        WR1_PROG(REG_1600H, 0x38000c21U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x42700e5eU), bswap_32big(0x8fb54b9bU), bswap_32big(0xd44313ecU),
                       bswap_32big(0x81e83bbeU));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x7bc54fc3U), bswap_32big(0x6240d020U), bswap_32big(0x7e292cb8U),
                           bswap_32big(0x5f5fb6caU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WAIT_STS(REG_2030H, 0, 1);

            WR1_PROG(REG_1600H, 0x38000c63U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x1a427d46U), bswap_32big(0x63db502eU), bswap_32big(0x9cadf6d2U),
                           bswap_32big(0x3d065d25U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000c4U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Msg1[0]);

                r_rsip_func101(bswap_32big(0xeb3f2e4cU),
                               bswap_32big(0x342bb020U),
                               bswap_32big(0x11383c25U),
                               bswap_32big(0xc4b583a9U));
            }

            WR1_PROG(REG_1600H, 0x38000c84U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x92a3fdc3U), bswap_32big(0xd97d08bdU), bswap_32big(0x4ced105bU),
                           bswap_32big(0xa9a349c7U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func100(bswap_32big(0xd9753f61U),
                               bswap_32big(0x5a4498b5U),
                               bswap_32big(0x50c902fbU),
                               bswap_32big(0xcf683ddeU));

                WR1_PROG(REG_1600H, 0x00007c05U);
                WR1_PROG(REG_143CH, 0x00600000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_1404H, 0x10000000U);
                    WR1_PROG(REG_1400H, 0x01430021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    r_rsip_func101(bswap_32big(0xebc76093U),
                                   bswap_32big(0xd25821b0U),
                                   bswap_32big(0x7b4f2340U),
                                   bswap_32big(0x01c279dbU));
                }
                else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_1404H, 0x10000000U);
                    WR1_PROG(REG_1400H, 0x01430031U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    r_rsip_func101(bswap_32big(0x110d28faU),
                                   bswap_32big(0x5d2d66bcU),
                                   bswap_32big(0x4615e1f0U),
                                   bswap_32big(0xae1ac68eU));
                }

                r_rsip_func101(bswap_32big(0x63dd2833U),
                               bswap_32big(0x8d5f6f8aU),
                               bswap_32big(0x5fad6ca0U),
                               bswap_32big(0xf2ef5838U));
            }

            r_rsip_func100(bswap_32big(0xbbebbd41U), bswap_32big(0x115ea27dU), bswap_32big(0x0585a162U),
                           bswap_32big(0xfae7f1eeU));

            WR1_PROG(REG_1608H, 0x81010000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_1444H, 0x00020064U);

            WAIT_STS(REG_1444H, 31, 1);
            for (iLoop = 0; iLoop < (S_RAM[0] & 0x0000000fU); iLoop++)
            {
                WR1_PROG(REG_1420H, InData_Msg2[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WAIT_STS(REG_1444H, 31, 1);
            for (iLoop = (S_RAM[0] & 0x0000000fU); iLoop < S_RAM[0]; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR16_ADDR(REG_1420H, &InData_Msg2[iLoop]);
                iLoop = iLoop + 16U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x00000000U);
            WAIT_STS(REG_2030H, 8, 0);
            WR1_PROG(REG_143CH, 0x00001600U);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1600H, 0x00003801U);

            r_rsip_func101(bswap_32big(0x1d50d86fU), bswap_32big(0xca4de9f8U), bswap_32big(0xadaa5f11U),
                           bswap_32big(0xe8524ff6U));

            return RSIP_RET_PASS;
        }
    }
}
