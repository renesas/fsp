/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes128XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00160001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p16_func100_001[] =
    {
        0x1553867dU, 0x2e1640b4U, 0xef605578U, 0x13564b33U,
    };
    HW_SCE_p_func100(Param_p16_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000016U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p16_func101_001[] =
    {
        0xd0895498U, 0xf53add7eU, 0xb42f275dU, 0x9e4a90a3U,
    };
    HW_SCE_p_func101(Param_p16_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000008U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000016U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p16_func101_002[] =
    {
        0xa0412cddU, 0x02a29711U, 0xe7adc2edU, 0x4997abc0U,
    };
    HW_SCE_p_func101(Param_p16_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p16_func100_002[] =
    {
        0x7f810f1fU, 0xfe84fd3dU, 0x6405441dU, 0xc4d22380U,
    };
    HW_SCE_p_func100(Param_p16_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p16_func100_003[] =
    {
        0x813447d6U, 0x7549de93U, 0x38b7ed77U, 0x3d57393cU,
    };
    HW_SCE_p_func100(Param_p16_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub003(0x03410011U);

    HW_SCE_p_func103();

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x0000b420U);
    WR1_PROG(REG_94H, 0x00000010U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub003(0x03410011U);

    static const uint32_t Param_p16_func100_004[] =
    {
        0xc5a1b25aU, 0x74568e9eU, 0xe34bf3c5U, 0xe69b0809U,
    };
    HW_SCE_p_func100(Param_p16_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p16_func100_005[] =
    {
        0x5c7bfdc1U, 0x7a0677c2U, 0xf5d79595U, 0xee2973b3U,
    };
    HW_SCE_p_func100(Param_p16_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    static const uint32_t Param_p16_func100_006[] =
    {
        0x2e334394U, 0x0f67ae14U, 0x1e51fd33U, 0xd23d3ff4U,
    };
    HW_SCE_p_func100(Param_p16_func100_006);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p16_func102_001[] =
    {
        0x02ff9b97U, 0xffee78e8U, 0xb76f08e4U, 0x5d4415b9U,
    };
    HW_SCE_p_func102(Param_p16_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
