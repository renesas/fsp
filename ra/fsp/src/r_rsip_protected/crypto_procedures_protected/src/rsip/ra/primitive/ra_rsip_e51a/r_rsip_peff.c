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

rsip_ret_t r_rsip_peff (const uint32_t InData_Msg1[],
                        const uint32_t InData_Msg1Length[],
                        const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[],
                        const uint32_t InData_Msg2[],
                        const uint32_t InData_Msg2Length[],
                        uint32_t       OutData_KDFInfo[])
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

    r_rsip_func100(bswap_32big(0x912b85b6U),
                   bswap_32big(0xc9c65800U),
                   bswap_32big(0x0ecf516cU),
                   bswap_32big(0xb7d4a2c8U));
    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1600H, 0x38008c80U);
        WR1_PROG(REG_1600H, 0xfffffff7U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func101(bswap_32big(0x0a2f296eU), bswap_32big(0xc606cf0bU), bswap_32big(0x9affb101U),
                       bswap_32big(0x7e1e7e36U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1600H, 0x38008c80U);
        WR1_PROG(REG_1600H, 0xfffffff3U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func101(bswap_32big(0xbe2a64bdU), bswap_32big(0x83dc2d76U), bswap_32big(0x822e6f50U),
                       bswap_32big(0xb361d02bU));
    }

    r_rsip_func100(bswap_32big(0xa75ea818U),
                   bswap_32big(0x90e4b2c7U),
                   bswap_32big(0x72d98995U),
                   bswap_32big(0x9b71096bU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x036781c8U), bswap_32big(0x9f77c096U), bswap_32big(0x24876c15U),
                       bswap_32big(0xc3fce0e3U));
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

        r_rsip_func100(bswap_32big(0x17e6f7b5U), bswap_32big(0x2326a538U), bswap_32big(0xd1c2e2afU),
                       bswap_32big(0xe3ba47e2U));
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
            WR1_PROG(REG_1420H, bswap_32big(0x0000ef02U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xf8ad8543U), bswap_32big(0xb60379ecU), bswap_32big(0xf31ef472U),
                           bswap_32big(0x3f52931aU));
            r_rsip_func043();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x01799093U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000ef02U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xbf6fe5b4U), bswap_32big(0x6d602e23U), bswap_32big(0xd6043141U),
                           bswap_32big(0x00e9a965U));
            r_rsip_func044();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1600H, 0x000038a7U);

            r_rsip_func100(bswap_32big(0x86a9c72cU), bswap_32big(0x59f68636U), bswap_32big(0x658afa86U),
                           bswap_32big(0x75cb3ea4U));

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

                r_rsip_func101(bswap_32big(0x04512293U),
                               bswap_32big(0xd03dd040U),
                               bswap_32big(0xb0ffbdc5U),
                               bswap_32big(0x5bb5a28eU));
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

                r_rsip_func101(bswap_32big(0x7da17820U),
                               bswap_32big(0x3dc3c98dU),
                               bswap_32big(0x33620ba5U),
                               bswap_32big(0x8d267a3eU));
            }

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0x4f6ef73aU), bswap_32big(0x7877b4bbU), bswap_32big(0xb8e03eb4U),
                           bswap_32big(0x3b2cec27U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00002c20U);
                r_rsip_func101(bswap_32big(0x488fd84dU),
                               bswap_32big(0x6ab92535U),
                               bswap_32big(0x7c734030U),
                               bswap_32big(0x028b0329U));
            }

            r_rsip_func101(bswap_32big(0xacb377d6U), bswap_32big(0xf7eab2e3U), bswap_32big(0x0992b677U),
                           bswap_32big(0xeac7afaaU));
        }

        WR1_PROG(REG_1600H, 0x38000c21U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x88ba8b6aU), bswap_32big(0x0c08c1e4U), bswap_32big(0x33c85669U),
                       bswap_32big(0x8edf50f8U));
        WR1_PROG(REG_143CH, 0x00400000U);
        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xb21eadebU), bswap_32big(0x78879f51U), bswap_32big(0x5d3b12deU),
                           bswap_32big(0x30c6729cU));
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

            r_rsip_func100(bswap_32big(0x7d890719U), bswap_32big(0xc5c3b34fU), bswap_32big(0x3e89f683U),
                           bswap_32big(0x4cd6c80bU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000c4U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Msg1[0]);

                r_rsip_func101(bswap_32big(0x501f8b00U),
                               bswap_32big(0x5e170e1eU),
                               bswap_32big(0xc13a5fd4U),
                               bswap_32big(0x6df67ceeU));
            }

            WR1_PROG(REG_1600H, 0x38000c84U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            r_rsip_func100(bswap_32big(0xe2b05523U), bswap_32big(0xcd9ac643U), bswap_32big(0x202624f6U),
                           bswap_32big(0x4467a339U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func100(bswap_32big(0x3f7c9559U),
                               bswap_32big(0x1cb2f266U),
                               bswap_32big(0x1ed18246U),
                               bswap_32big(0x44906e2dU));

                WR1_PROG(REG_1600H, 0x00007c05U);
                WR1_PROG(REG_143CH, 0x00600000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_1404H, 0x10000000U);
                    WR1_PROG(REG_1400H, 0x01430021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    r_rsip_func101(bswap_32big(0x2df5a0d4U),
                                   bswap_32big(0x5f54bdd2U),
                                   bswap_32big(0x5c573239U),
                                   bswap_32big(0xbf216d24U));
                }
                else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
                {
                    WR1_PROG(REG_1404H, 0x10000000U);
                    WR1_PROG(REG_1400H, 0x01430031U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    r_rsip_func101(bswap_32big(0x700ec984U),
                                   bswap_32big(0x50d7688aU),
                                   bswap_32big(0xc52af0c3U),
                                   bswap_32big(0x5e28323dU));
                }

                r_rsip_func101(bswap_32big(0x41819c42U),
                               bswap_32big(0x4fb29b8bU),
                               bswap_32big(0xd16b3cb0U),
                               bswap_32big(0x0c412750U));
            }

            r_rsip_func100(bswap_32big(0x52796222U), bswap_32big(0xfed00517U), bswap_32big(0xbad5c650U),
                           bswap_32big(0x48fa0f45U));

            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x800100a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Msg2Length[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1608H, 0x810100a0U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_1444H, 0x00020064U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Msg2[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x00000000U);
            WAIT_STS(REG_2030H, 8, 0);
            WR1_PROG(REG_143CH, 0x00001600U);

            WAIT_STS(REG_2030H, 4, 1);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1600H, 0x00003801U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x000000efU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x0b2da105U), bswap_32big(0xaa38adb9U), bswap_32big(0xdfe8408aU),
                           bswap_32big(0x1dc7e855U));
            r_rsip_func103();

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1608H, 0x80010020U);
            WR1_PROG(REG_1400H, 0x03420005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x000034e1U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000ef03U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xb7920be7U), bswap_32big(0xc312de92U), bswap_32big(0x409425a8U),
                           bswap_32big(0xed7f5f8bU));
            r_rsip_func043();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x01799093U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000ef03U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x011c06d2U), bswap_32big(0xdc4be9c6U), bswap_32big(0xadc89543U),
                           bswap_32big(0x6102e536U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0x054b0e03U), bswap_32big(0x71cfd4c5U), bswap_32big(0xb2a0c86dU),
                           bswap_32big(0x87c222a7U));
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000044U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000054U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1600H, 0x00007c00U);
            WR1_PROG(REG_143CH, 0x00600000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
            {
                r_rsip_func100(bswap_32big(0xef20b281U),
                               bswap_32big(0x56b0b01aU),
                               bswap_32big(0xf7d53e08U),
                               bswap_32big(0xbcb036a3U));
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xe7009d07U);
                WR1_PROG(REG_1400H, 0x00850021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1408H, 0x00002022U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[1]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[5]);

                r_rsip_func100(bswap_32big(0xb3e26965U),
                               bswap_32big(0xa7b6d986U),
                               bswap_32big(0x9bdd98bcU),
                               bswap_32big(0xbb8bccf0U));
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
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[9]);

                r_rsip_func101(bswap_32big(0x08c90d6fU),
                               bswap_32big(0xf5d0ec43U),
                               bswap_32big(0x7553999bU),
                               bswap_32big(0x67e888beU));
            }
            else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
            {
                r_rsip_func100(bswap_32big(0xad1b458fU),
                               bswap_32big(0x43784c70U),
                               bswap_32big(0x7655bfc3U),
                               bswap_32big(0x9f05da3fU));
                WR1_PROG(REG_1A2CH, 0x40000200U);
                WR1_PROG(REG_1A24H, 0xe7009d07U);
                WR1_PROG(REG_1400H, 0x00850031U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1408H, 0x00002032U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[1]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[5]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[9]);

                r_rsip_func100(bswap_32big(0x4123d9a2U),
                               bswap_32big(0x19d41800U),
                               bswap_32big(0x6e094d6dU),
                               bswap_32big(0xf1da9dbaU));
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
                RD4_ADDR(REG_1420H, &OutData_KDFInfo[13]);

                r_rsip_func101(bswap_32big(0x27f4521cU),
                               bswap_32big(0x678099edU),
                               bswap_32big(0x37e88438U),
                               bswap_32big(0x2d4a9601U));
            }

            r_rsip_func100(bswap_32big(0x6ea82957U), bswap_32big(0x243be52dU), bswap_32big(0x0ac00f8eU),
                           bswap_32big(0xf231232eU));
            WR1_PROG(REG_1608H, 0x81010020U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_KDFInfo[0]);

            r_rsip_func102(bswap_32big(0x37543e22U), bswap_32big(0x1c3ee44bU), bswap_32big(0x867b3852U),
                           bswap_32big(0xe9f5ef60U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
