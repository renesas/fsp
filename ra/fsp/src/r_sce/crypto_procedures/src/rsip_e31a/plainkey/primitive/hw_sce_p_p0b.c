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
        0x0fd26f72U, 0x7249bd4aU, 0x19a096b3U, 0x752394abU,
    };
    HW_SCE_p_func100(Param_p0b_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000bU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p0b_func101_001[] =
    {
        0xf8fa78cbU, 0xc6ba01e0U, 0x81eef512U, 0xd841d258U,
    };
    HW_SCE_p_func101(Param_p0b_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x0000001bU);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000bU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p0b_func101_002[] =
    {
        0x2f686fe8U, 0x9defb5e0U, 0x8ae4dca3U, 0xb362b2dcU,
    };
    HW_SCE_p_func101(Param_p0b_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p0b_func100_002[] =
    {
        0xf051041aU, 0x369d98beU, 0xb51780afU, 0xa89548ccU,
    };
    HW_SCE_p_func100(Param_p0b_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p0b_func100_003[] =
    {
        0x6f39bfa1U, 0x9176c9daU, 0xd38db904U, 0x271150ffU,
    };
    HW_SCE_p_func100(Param_p0b_func100_003);
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

    static const uint32_t Param_p0b_func100_004[] =
    {
        0x6c3f57cfU, 0x0131f70aU, 0x21c56721U, 0xdc87b2dbU,
    };
    HW_SCE_p_func100(Param_p0b_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p0b_func100_005[] =
    {
        0x2e80a643U, 0x5bd14684U, 0xb335ac78U, 0xc64a4740U,
    };
    HW_SCE_p_func100(Param_p0b_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    static const uint32_t Param_p0b_func100_006[] =
    {
        0x79e7b93aU, 0x9e5f7755U, 0x94a74f6eU, 0xd4a8a36bU,
    };
    HW_SCE_p_func100(Param_p0b_func100_006);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p0b_func102_001[] =
    {
        0x26962779U, 0x1df1a0bdU, 0x405d3371U, 0x217c4cb6U,
    };
    HW_SCE_p_func102(Param_p0b_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
