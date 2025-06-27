/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256OutputKeyForDotfSub (const uint32_t InData_KeyMode[],
                                            const uint32_t InData_KeyIndex[],
                                            const uint32_t InData_Key[],
                                            const uint32_t InData_DOTFSEED[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x002e0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyMode[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x7959c71bU, 0x5f700190U, 0xa19425eaU, 0xa133a64dU);
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
        WR1_PROG(REG_1420H, change_endian_long(0x0000002eU));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x501001bbU, 0x27c34b56U, 0xc0a4c0d2U, 0x6e124f5aU);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000007U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x0000002eU));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x71c0a329U, 0x307eb17cU, 0xbd2374e0U, 0xf33819c1U);
        HW_SCE_p_func044_r1();

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1608H, 0x80880001U);
        WR1_PROG(REG_1400H, 0x03420021U);
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

        HW_SCE_p_func101(0xe627265bU, 0x34f48d1aU, 0xfb17456bU, 0x4a5dc6f1U);
    }
    else
    {
        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1444H, 0x000007c7U);
        WR1_PROG(REG_1608H, 0x80880001U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Key[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Key[4]);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x99e7703bU, 0x9f00e534U, 0xa3bb0f22U, 0x1feb4075U);
    }

    HW_SCE_p_func100(0x541bffa3U, 0x18b9bb25U, 0x9ddc0bb5U, 0x53bb9a4fU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xb383a298U, 0x389afddcU, 0x2691c80dU, 0x5d693030U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x22ff40d3U, 0x484928a9U, 0xa7a01b67U, 0x6ef0b7b7U);
        WR1_PROG(REG_1438H, 0x40000100U);

        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1600H, 0x00000002U);

        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1400H, 0x02090005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0xbcfcd4b9U, 0x9c9e8774U, 0x5f392a04U, 0x95b4f842U);
        WR1_PROG(REG_1438H, 0x40000110U);

        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1608H, 0x81880001U);
        WR1_PROG(REG_1400H, 0x02090021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000001c7U);
        WR1_PROG(REG_1608H, 0x80020000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_DOTFSEED[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_DOTFSEED[1]);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x53c7f3fbU, 0x2f9c9f1cU, 0xdbf2980eU, 0x6a40b7aaU);
        WR1_PROG(REG_1438H, 0x40000140U);

        WR1_PROG(REG_1608H, 0x81020000U);
        WR1_PROG(REG_1400H, 0x02090009U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func102(0x2732bfd2U, 0xe5c6b145U, 0x29302cb7U, 0x53facdbcU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
}
