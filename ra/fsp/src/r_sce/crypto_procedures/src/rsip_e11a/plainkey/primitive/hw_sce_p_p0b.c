/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateSha256HmacRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x000b0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p0b_func100_001[] =
    {
        0xb2ff2993U, 0x35eaaae5U, 0xf4edb773U, 0x515f2cbeU,
    };
    HW_SCE_p_func100(Param_p0b_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub002(0x03410005U);
    HW_SCE_p_func_sub002(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000bU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p0b_func101_001[] =
    {
        0x2ae8fa9fU, 0x8f3d71cfU, 0xd8d1d12dU, 0x257c2c13U,
    };
    HW_SCE_p_func101(Param_p0b_func101_001);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x0000001bU);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000bU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p0b_func101_002[] =
    {
        0x9eb92e18U, 0x8fbba1b5U, 0xee2a046fU, 0x6ff8504cU,
    };
    HW_SCE_p_func101(Param_p0b_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p0b_func100_002[] =
    {
        0xfd74a9caU, 0x5c8b629aU, 0xdbca744aU, 0xfed5278cU,
    };
    HW_SCE_p_func100(Param_p0b_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p0b_func100_003[] =
    {
        0x5830c41bU, 0x18120532U, 0x4e8497cdU, 0x4bf82543U,
    };
    HW_SCE_p_func100(Param_p0b_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub002(0x03410011U);

    HW_SCE_p_func103();

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub013(0x80840001U);
    HW_SCE_p_func_sub002(0x03410011U);

    static const uint32_t Param_p0b_func100_004[] =
    {
        0x2fbe90caU, 0x0be9c19bU, 0x1ee37c1cU, 0x941e4e5dU,
    };
    HW_SCE_p_func100(Param_p0b_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub016(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub002(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p0b_func100_005[] =
    {
        0xe2895ea7U, 0xe532fcf7U, 0x962a836dU, 0xf53bb6adU,
    };
    HW_SCE_p_func100(Param_p0b_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub002(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    static const uint32_t Param_p0b_func100_006[] =
    {
        0x4416d9e2U, 0x7849ca00U, 0x00f8d7f5U, 0x4758751cU,
    };
    HW_SCE_p_func100(Param_p0b_func100_006);
    HW_SCE_p_func_sub012(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p0b_func102_001[] =
    {
        0x178e0545U, 0x399e4496U, 0x8052180fU, 0xa952c998U,
    };
    HW_SCE_p_func102(Param_p0b_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
