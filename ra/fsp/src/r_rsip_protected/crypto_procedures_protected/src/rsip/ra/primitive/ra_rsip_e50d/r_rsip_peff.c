/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

rsip_ret_t r_rsip_peff (const uint32_t InData_Msg1[],
                        const uint32_t InData_Msg1Length[],
                        const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[],
                        const uint32_t InData_Msg2[],
                        const uint32_t InData_Msg2Length[],
                        uint32_t       OutData_KDFInfo[])
{
    uint32_t iLoop = 0U;

    r_rsip_func_sub010(0x000002c7U, 0x80030060U);
    WR1_PROG(REG_1420H, InData_Msg1Length[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_EncMsgLength[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Msg2Length[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func_sub006(0x38008c60U, 0xfffffffeU, 0x00A60000U);

    r_rsip_func_sub021(0x000034c3U, 0x00026cc6U, 0x000024c4U, 0x000024c5U);

    static const uint32_t Param_peff_func100_001[] =
    {
        BSWAP_32BIG_C(0xc06a06f8U), BSWAP_32BIG_C(0x4b161a0fU), BSWAP_32BIG_C(0x26608c68U), BSWAP_32BIG_C(0x7f7a35e4U), 
    };
    r_rsip_func100(Param_peff_func100_001);
    r_rsip_func_sub014(0x00007c00U, 0x00600000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func_sub006(0x38008c80U, 0xffffffdfU, 0x00A60000U);

        static const uint32_t Param_peff_func101_001[] =
        {
            BSWAP_32BIG_C(0x180b2d14U), BSWAP_32BIG_C(0x804a5c39U), BSWAP_32BIG_C(0x1f931ae9U), BSWAP_32BIG_C(0x5b3c299dU), 
        };
        r_rsip_func101(Param_peff_func101_001);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func_sub022(0x38000c84U, 0x00020020U, 0x38008880U);
        r_rsip_func_sub006(0x00000030U, 0x00000080U, 0x00A60000U);

        static const uint32_t Param_peff_func101_002[] =
        {
            BSWAP_32BIG_C(0x69ba62c9U), BSWAP_32BIG_C(0xfaac70ebU), BSWAP_32BIG_C(0x54fcdb20U), BSWAP_32BIG_C(0xd01942faU), 
        };
        r_rsip_func101(Param_peff_func101_002);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func_sub021(0x38008c80U, 0xffffffbfU, 0x00020020U, 0x38008880U);
        r_rsip_func_sub006(0x00000042U, 0x00000080U, 0x00A60000U);

        static const uint32_t Param_peff_func101_003[] =
        {
            BSWAP_32BIG_C(0xc8fd6015U), BSWAP_32BIG_C(0xe2121a2eU), BSWAP_32BIG_C(0xdab65791U), BSWAP_32BIG_C(0x9db1161bU), 
        };
        r_rsip_func101(Param_peff_func101_003);
    }

    static const uint32_t Param_peff_func100_002[] =
    {
        BSWAP_32BIG_C(0xa75ea818U), BSWAP_32BIG_C(0x90e4b2c7U), BSWAP_32BIG_C(0x72d98995U), BSWAP_32BIG_C(0x9b71096bU), 
    };
    r_rsip_func100(Param_peff_func100_002);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        static const uint32_t Param_peff_func102_001[] =
        {
            BSWAP_32BIG_C(0x036781c8U), BSWAP_32BIG_C(0x9f77c096U), BSWAP_32BIG_C(0x24876c15U), BSWAP_32BIG_C(0xc3fce0e3U), 
        };
        r_rsip_func102(Param_peff_func102_001);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func_sub006(0x00003505U, 0x38000c84U, 0x00A60000U);

        static const uint32_t Param_peff_func100_003[] =
        {
            BSWAP_32BIG_C(0xa97d2852U), BSWAP_32BIG_C(0x619326eaU), BSWAP_32BIG_C(0x8123a5b4U), BSWAP_32BIG_C(0x6741a1d1U), 
        };
        r_rsip_func100(Param_peff_func100_003);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func_sub003(0x800103a0U, 0x0000ef02U);

            static const uint32_t Param_peff_func101_004[] =
            {
                BSWAP_32BIG_C(0x6becb4f3U), BSWAP_32BIG_C(0x6f721f95U), BSWAP_32BIG_C(0x307d0a20U), BSWAP_32BIG_C(0x2c5ba1d8U), 
            };
            r_rsip_func101(Param_peff_func101_004);
            r_rsip_func415(InData_EncMsg);

            static const uint32_t Param_peff_func101_005[] =
            {
                BSWAP_32BIG_C(0x8ba4c50eU), BSWAP_32BIG_C(0x08ad6b16U), BSWAP_32BIG_C(0xb6f7e854U), BSWAP_32BIG_C(0x3a5488d9U), 
            };
            r_rsip_func101(Param_peff_func101_005);
        }

        static const uint32_t Param_peff_func100_004[] =
        {
            BSWAP_32BIG_C(0x03cf3dedU), BSWAP_32BIG_C(0xa2de6396U), BSWAP_32BIG_C(0xf9567482U), BSWAP_32BIG_C(0xc47fa7bcU), 
        };
        r_rsip_func100(Param_peff_func100_004);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            static const uint32_t Param_peff_func102_002[] =
            {
                BSWAP_32BIG_C(0xeb62e6e0U), BSWAP_32BIG_C(0x2450741fU), BSWAP_32BIG_C(0x3a795af3U), BSWAP_32BIG_C(0xad3261ccU), 
            };
            r_rsip_func102(Param_peff_func102_002);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func_sub003(0x800103a0U, 0x0000ef02U);

            static const uint32_t Param_peff_func101_006[] =
            {
                BSWAP_32BIG_C(0xef2d2011U), BSWAP_32BIG_C(0x673df5a7U), BSWAP_32BIG_C(0xe1b767eeU), BSWAP_32BIG_C(0x19307e95U), 
            };
            r_rsip_func101(Param_peff_func101_006);
            r_rsip_func416(InData_Msg1, InData_Msg2);

            r_rsip_func_sub006(0x08008cc0U, 0x00000003U, 0x00A60000U);

            static const uint32_t Param_peff_func100_005[] =
            {
                BSWAP_32BIG_C(0x579e7a25U), BSWAP_32BIG_C(0xe6fa8c5eU), BSWAP_32BIG_C(0xe2ca8a94U), BSWAP_32BIG_C(0xd27ad97fU), 
            };
            r_rsip_func100(Param_peff_func100_005);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                static const uint32_t Param_peff_func100_006[] =
                {
                    BSWAP_32BIG_C(0xe2540e89U), BSWAP_32BIG_C(0x9d2efa03U), BSWAP_32BIG_C(0x82317174U), BSWAP_32BIG_C(0x2c1a8b07U), 
                };
                r_rsip_func100(Param_peff_func100_006);
                r_rsip_func_sub022(0x0000b7e0U, 0x00000004U, 0x00002be6U);

                r_rsip_func_sub016(0x810103e0U, 0x00005006U);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    r_rsip_func_sub001(0x11400005U);
                    WR1_PROG(REG_1600H, 0x000033e0U);

                    static const uint32_t Param_peff_func101_007[] =
                    {
                        BSWAP_32BIG_C(0x49d507f2U), BSWAP_32BIG_C(0x71457e64U), BSWAP_32BIG_C(0x633263bdU), BSWAP_32BIG_C(0xe6939f50U), 
                    };
                    r_rsip_func101(Param_peff_func101_007);
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func_sub014(0x00007c1fU, 0x00602000U);

                static const uint32_t Param_peff_func101_008[] =
                {
                    BSWAP_32BIG_C(0x06855e8dU), BSWAP_32BIG_C(0xbcdc7652U), BSWAP_32BIG_C(0xd1e1c039U), BSWAP_32BIG_C(0xf00ca29bU), 
                };
                r_rsip_func101(Param_peff_func101_008);
            }

            WAIT_STS(REG_2030H, 8, 0);
            WR1_PROG(REG_143CH, 0x00001600U);

            WAIT_STS(REG_2030H, 4, 1);

            r_rsip_func_sub022(0x0000b420U, 0x00000010U, 0x00003801U);

            r_rsip_func_sub003(0x800103a0U, 0x000000efU);

            static const uint32_t Param_peff_func101_009[] =
            {
                BSWAP_32BIG_C(0x436aa71eU), BSWAP_32BIG_C(0x320d3f48U), BSWAP_32BIG_C(0x032b871cU), BSWAP_32BIG_C(0xd641e61eU), 
            };
            r_rsip_func101(Param_peff_func101_009);
            r_rsip_func103();

            r_rsip_func_sub004(0x0c200104U, 0x00000000U);

            WR1_PROG(REG_1608H, 0x80010020U);
            r_rsip_func_sub001(0x03420005U);
            r_rsip_func_sub001(0x0002000dU);

            WR1_PROG(REG_1600H, 0x000034e1U);

            r_rsip_func_sub003(0x800103a0U, 0x0000ef03U);

            static const uint32_t Param_peff_func101_010[] =
            {
                BSWAP_32BIG_C(0xb7920be7U), BSWAP_32BIG_C(0xc312de92U), BSWAP_32BIG_C(0x409425a8U), BSWAP_32BIG_C(0xed7f5f8bU), 
            };
            r_rsip_func101(Param_peff_func101_010);
            r_rsip_func043();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x01799093U);

            r_rsip_func_sub003(0x800103a0U, 0x0000ef03U);

            static const uint32_t Param_peff_func101_011[] =
            {
                BSWAP_32BIG_C(0x011c06d2U), BSWAP_32BIG_C(0xdc4be9c6U), BSWAP_32BIG_C(0xadc89543U), BSWAP_32BIG_C(0x6102e536U), 
            };
            r_rsip_func101(Param_peff_func101_011);
            r_rsip_func044();

            static const uint32_t Param_peff_func100_007[] =
            {
                BSWAP_32BIG_C(0x054b0e03U), BSWAP_32BIG_C(0x71cfd4c5U), BSWAP_32BIG_C(0xb2a0c86dU), BSWAP_32BIG_C(0x87c222a7U), 
            };
            r_rsip_func100(Param_peff_func100_007);
            r_rsip_func_sub004(0x08000044U, 0x00000000U);

            r_rsip_func_sub004(0x08000054U, 0x00000000U);

            r_rsip_func_sub014(0x00007c00U, 0x00600000U);

            if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
            {
                static const uint32_t Param_peff_func100_008[] =
                {
                    BSWAP_32BIG_C(0xef20b281U), BSWAP_32BIG_C(0x56b0b01aU), BSWAP_32BIG_C(0xf7d53e08U), BSWAP_32BIG_C(0xbcb036a3U), 
                };
                r_rsip_func100(Param_peff_func100_008);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xe7009d07U);
                r_rsip_func_sub001(0x00850021U);

                WR1_PROG(REG_1408H, 0x00002022U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[1]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[5]);

                static const uint32_t Param_peff_func100_009[] =
                {
                    BSWAP_32BIG_C(0xb3e26965U), BSWAP_32BIG_C(0xa7b6d986U), BSWAP_32BIG_C(0x9bdd98bcU), BSWAP_32BIG_C(0xbb8bccf0U), 
                };
                r_rsip_func100(Param_peff_func100_009);
                r_rsip_func_sub004(0x0c000104U, 0x00000000U);

                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x09108105U);
                r_rsip_func_sub001(0x00820011U);

                WR1_PROG(REG_1408H, 0x00002012U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[9]);

                static const uint32_t Param_peff_func101_012[] =
                {
                    BSWAP_32BIG_C(0x08c90d6fU), BSWAP_32BIG_C(0xf5d0ec43U), BSWAP_32BIG_C(0x7553999bU), BSWAP_32BIG_C(0x67e888beU), 
                };
                r_rsip_func101(Param_peff_func101_012);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
            {
                static const uint32_t Param_peff_func100_010[] =
                {
                    BSWAP_32BIG_C(0xad1b458fU), BSWAP_32BIG_C(0x43784c70U), BSWAP_32BIG_C(0x7655bfc3U), BSWAP_32BIG_C(0x9f05da3fU), 
                };
                r_rsip_func100(Param_peff_func100_010);
                WR1_PROG(REG_1A2CH, 0x40000200U);
                WR1_PROG(REG_1A24H, 0xe7009d07U);
                r_rsip_func_sub001(0x00850031U);

                WR1_PROG(REG_1408H, 0x00002032U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[1]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[5]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[9]);

                static const uint32_t Param_peff_func100_011[] =
                {
                    BSWAP_32BIG_C(0x4123d9a2U), BSWAP_32BIG_C(0x19d41800U), BSWAP_32BIG_C(0x6e094d6dU), BSWAP_32BIG_C(0xf1da9dbaU), 
                };
                r_rsip_func100(Param_peff_func100_011);
                r_rsip_func_sub004(0x0c000104U, 0x00000000U);

                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x09108105U);
                r_rsip_func_sub001(0x00820011U);

                WR1_PROG(REG_1408H, 0x00002012U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[13]);

                static const uint32_t Param_peff_func101_013[] =
                {
                    BSWAP_32BIG_C(0x27f4521cU), BSWAP_32BIG_C(0x678099edU), BSWAP_32BIG_C(0x37e88438U), BSWAP_32BIG_C(0x2d4a9601U), 
                };
                r_rsip_func101(Param_peff_func101_013);
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
            {
                static const uint32_t Param_peff_func100_012[] =
                {
                    BSWAP_32BIG_C(0x2ec912e6U), BSWAP_32BIG_C(0xb5de665eU), BSWAP_32BIG_C(0x8ce1e6ecU), BSWAP_32BIG_C(0xd1b841b8U), 
                };
                r_rsip_func100(Param_peff_func100_012);
                WR1_PROG(REG_1A2CH, 0x40000200U);
                WR1_PROG(REG_1A24H, 0xe7009d07U);
                r_rsip_func_sub001(0x00850031U);

                WR1_PROG(REG_1408H, 0x00002032U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[1]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[5]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[9]);

                static const uint32_t Param_peff_func100_013[] =
                {
                    BSWAP_32BIG_C(0xc93aa478U), BSWAP_32BIG_C(0x48ea67b5U), BSWAP_32BIG_C(0x210da8f3U), BSWAP_32BIG_C(0x694da1c1U), 
                };
                r_rsip_func100(Param_peff_func100_013);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0xe7008d05U);
                r_rsip_func_sub001(0x00850011U);

                WR1_PROG(REG_1408H, 0x00002012U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[13]);

                static const uint32_t Param_peff_func100_014[] =
                {
                    BSWAP_32BIG_C(0x47ba62f2U), BSWAP_32BIG_C(0xa601884bU), BSWAP_32BIG_C(0x100a9752U), BSWAP_32BIG_C(0x34f435e9U), 
                };
                r_rsip_func100(Param_peff_func100_014);
                r_rsip_func_sub004(0x0c000104U, 0x00000000U);

                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x09108105U);
                r_rsip_func_sub001(0x00820011U);

                WR1_PROG(REG_1408H, 0x00002012U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[17]);

                static const uint32_t Param_peff_func101_014[] =
                {
                    BSWAP_32BIG_C(0x9cdc393bU), BSWAP_32BIG_C(0xb0454583U), BSWAP_32BIG_C(0x13ff90f1U), BSWAP_32BIG_C(0x0f998ac5U), 
                };
                r_rsip_func101(Param_peff_func101_014);
            }

            static const uint32_t Param_peff_func100_015[] =
            {
                BSWAP_32BIG_C(0x6ea82957U), BSWAP_32BIG_C(0x243be52dU), BSWAP_32BIG_C(0x0ac00f8eU), BSWAP_32BIG_C(0xf231232eU), 
            };
            r_rsip_func100(Param_peff_func100_015);
            r_rsip_func_sub016(0x81010020U, 0x00005006U);
            RD1_ADDR(REG_1420H, &OutData_KDFInfo[0]);

            static const uint32_t Param_peff_func102_003[] =
            {
                BSWAP_32BIG_C(0x37543e22U), BSWAP_32BIG_C(0x1c3ee44bU), BSWAP_32BIG_C(0x867b3852U), BSWAP_32BIG_C(0xe9f5ef60U), 
            };
            r_rsip_func102(Param_peff_func102_003);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
