/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha256HmacInitSub (const uint32_t InData_KeyType[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Cmd[],
                                    const uint32_t InData_MsgLen[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00760001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);

    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_2004H, 0x00000050U);

    WR1_PROG(REG_2008H, 0x00000013U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0xc0d3f2c5U, 0x6d9c3a04U, 0xd1d1f387U, 0xcacf5181U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x1639f1c8U, 0x1b88d053U, 0x1f5b431aU, 0x8eecd896U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x38008800U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xc1751294U, 0x6150d804U, 0xe12ab83dU, 0x43fff3a8U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x38000c00U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xf4259d04U, 0x5ee7f6c6U, 0x48474e4aU, 0x434f0debU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x177d87b2U, 0x1094473fU, 0x82887e34U, 0x6382553fU);
                HW_SCE_p_func043_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x0000001bU);

                HW_SCE_p_func101(0x2e695bafU, 0xf65e04b3U, 0x6cfc088bU, 0x02072946U);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010140U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x23d77a5bU, 0x9515c063U, 0xe1374bbfU, 0x19f96c83U);
                HW_SCE_p_func068_r1();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0xb6e3697fU);

                HW_SCE_p_func101(0xc20c85f1U, 0x6c08e2b6U, 0x04158dc0U, 0x162ccec1U);
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x0b07b776U, 0x799de06aU, 0xaf4578b3U, 0x043c88dbU);
            HW_SCE_p_func044_r1();

            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xf7009d07U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

            WR1_PROG(REG_1400H, 0x01420021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000b760U);
            WR1_PROG(REG_1600H, 0x00003000U);

            HW_SCE_p_func101(0xfbd37369U, 0xdf05a1baU, 0x34886580U, 0xa1e15c85U);
        }
        else
        {
            WR1_PROG(REG_1600H, 0x38008800U);
            WR1_PROG(REG_1600H, 0x00000001U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0xb9daa27fU, 0x3cbbb3e4U, 0x312791e9U, 0x330f223dU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000003c7U);
                WR1_PROG(REG_1608H, 0x80040000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[1]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[2]);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[3]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00000bdeU);

                WR1_PROG(REG_1600H, 0x000037e0U);

                WR1_PROG(REG_1600H, 0x00008fe0U);
                WR1_PROG(REG_1600H, 0x00ff0000U);
                WR1_PROG(REG_1600H, 0x38008be0U);
                WR1_PROG(REG_1600H, 0x00020000U);
                WR1_PROG(REG_1600H, 0x1000d3c0U);

                WR1_PROG(REG_1600H, 0x000037e0U);

                WR1_PROG(REG_1600H, 0x38008fe0U);
                WR1_PROG(REG_1600H, 0x00003000U);
                WR1_PROG(REG_1600H, 0x2000d3c1U);
                WR1_PROG(REG_1600H, 0x00003760U);
                WR1_PROG(REG_1600H, 0x00008f60U);
                WR1_PROG(REG_1600H, 0x00003000U);

                WR1_PROG(REG_1600H, 0x000037e0U);

                WR1_PROG(REG_1600H, 0x00008fe0U);
                WR1_PROG(REG_1600H, 0x000000feU);

                WR1_PROG(REG_1600H, 0x38008be0U);
                WR1_PROG(REG_1600H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x1000d3c2U);

                WR1_PROG(REG_1600H, 0x38008bc0U);
                WR1_PROG(REG_1600H, 0x00000007U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                WR1_PROG(REG_1600H, 0x00003540U);
                WR1_PROG(REG_1600H, 0x00003561U);
                WR1_PROG(REG_1600H, 0x00003582U);
                WR1_PROG(REG_1600H, 0x000035a3U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xfbeee1acU, 0xdfc071c3U, 0x21ce0662U, 0xac133887U);
                HW_SCE_p_func059_r1();

                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[4]);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[8]);

                WR1_PROG(REG_1400H, 0x01420021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[12]);

                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                HW_SCE_p_func101(0xb00e7028U, 0xb6a01584U, 0xb29674ccU, 0xbdb19aaeU);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Cmd[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010280U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00003554U);

                WR1_PROG(REG_1600H, 0x000036a0U);

                WR1_PROG(REG_1600H, 0x0000b6c0U);
                WR1_PROG(REG_1600H, 0x01249674U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xe87571dcU, 0xbac77a89U, 0x142c4c95U, 0x6b508c3fU);
                HW_SCE_p_func092_r1();

                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1600H, 0x00003000U);

                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

                WR1_PROG(REG_1400H, 0x01420021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                HW_SCE_p_func101(0xf4c2cb1fU, 0x44d444d6U, 0xe52497c2U, 0x8197264bU);
            }

            HW_SCE_p_func101(0x01d9eda1U, 0x4f1ab3cdU, 0x8f734c7fU, 0xc5272f73U);
        }

        HW_SCE_p_func100(0x207c754bU, 0x9c341ed8U, 0x5f359042U, 0x85ecf528U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x8799e705U, 0xbe7e68faU, 0xf9d5d3a3U, 0xa32a5c37U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
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

                HW_SCE_p_func101(0x312ac86dU, 0x2b203894U, 0x320feb06U, 0x229c4e25U);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, InData_MsgLen[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, InData_MsgLen[1]);

                WR1_PROG(REG_200CH, 0x00000001U);

                HW_SCE_p_func101(0x1aac2855U, 0x37843e26U, 0x1e2e9891U, 0xc13a84f3U);
            }

            return FSP_SUCCESS;
        }
    }
}
