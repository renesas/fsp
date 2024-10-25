/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes192OutputKeyForDotfSub (uint32_t InData_KeyIndex[], uint32_t InData_DOTFSEED[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x002d0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, 0);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0xc3f8aba5U, 0x5f16d2ebU, 0xee41afadU, 0xabafce35U);
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
        WR1_PROG(REG_1420H, change_endian_long(0x0000002dU));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xac8beeafU, 0x90ce0bb4U, 0x7e2f468cU, 0x049ba83dU);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x00000006U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x0000002dU));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x1d6947caU, 0xa8767707U, 0x1aefd2f1U, 0x3a6ae15dU);
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

        HW_SCE_p_func101(0x42665561U, 0xf2a05f6fU, 0xc02bf570U, 0xaa6dd8f1U);
    }

    HW_SCE_p_func100(0xeb9a8865U, 0x747d265dU, 0x13c133f5U, 0x42e196ebU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xac2efcf2U, 0xf2caabf0U, 0x2e2cfefdU, 0x163d5955U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x326cf88fU, 0x110c2ca0U, 0x5f2278c2U, 0x80aed16cU);
        WR1_PROG(REG_1438H, 0x40000100U);

        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1600H, 0x00000001U);

        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1400H, 0x02090005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0xd852480aU, 0xca956af3U, 0xc8cc3d1fU, 0xb6289b8fU);
        WR1_PROG(REG_1438H, 0x40000110U);

        WR1_PROG(REG_1400H, 0x02000009U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0xeba2f11cU, 0x5b60edd4U, 0xd3cca0f2U, 0xa169fa76U);
        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1608H, 0x81860001U);
        WR1_PROG(REG_1400H, 0x02090019U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000001c7U);
        WR1_PROG(REG_1608H, 0x80020000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_DOTFSEED[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_DOTFSEED[1]);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0xc4d9a145U, 0x220542ccU, 0x62d6cd1aU, 0x7f479897U);
        WR1_PROG(REG_1438H, 0x40000140U);

        WR1_PROG(REG_1608H, 0x81020000U);
        WR1_PROG(REG_1400H, 0x02090009U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func102(0xe95c770dU, 0xc27b8eecU, 0x6556f195U, 0x0c00d495U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
}

