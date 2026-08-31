/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateSha512_224HmacRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x003e0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p3e_func100_001[] =
    {
        0x2bcb8042U, 0xad05d7d0U, 0x63b18e85U, 0x7c37376bU,
    };
    HW_SCE_p_func100(Param_p3e_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003eU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3e_func101_001[] =
    {
        0x4b75cbe1U, 0x3eaa5ae7U, 0x7846f86cU, 0x7cee6799U,
    };
    HW_SCE_p_func101(Param_p3e_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x0000002aU);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003eU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3e_func101_002[] =
    {
        0x5e4c01aeU, 0xdfaa81bbU, 0xb9eded4dU, 0x51562a5aU,
    };
    HW_SCE_p_func101(Param_p3e_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p3e_func100_002[] =
    {
        0x7616541eU, 0x1b1a89e6U, 0x4f57956eU, 0xe7d072a9U,
    };
    HW_SCE_p_func100(Param_p3e_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p3e_func100_003[] =
    {
        0x1173f140U, 0x3060660bU, 0xd64ad920U, 0x3dd0bceeU,
    };
    HW_SCE_p_func100(Param_p3e_func100_003);
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

    static const uint32_t Param_p3e_func100_004[] =
    {
        0x8b95a372U, 0x4e3040e1U, 0xa45e9c93U, 0x610c059fU,
    };
    HW_SCE_p_func100(Param_p3e_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p3e_func100_005[] =
    {
        0xa4913652U, 0x24c8175fU, 0x7fb96201U, 0x85003f15U,
    };
    HW_SCE_p_func100(Param_p3e_func100_005);
    HW_SCE_p_func103();

    static const uint32_t Param_p3e_func100_006[] =
    {
        0x103d11edU, 0x1cc559d6U, 0x8d411fb6U, 0x11fa7a26U,
    };
    HW_SCE_p_func100(Param_p3e_func100_006);
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

    static const uint32_t Param_p3e_func100_007[] =
    {
        0xaa84c7eaU, 0x4db1ad3cU, 0x5f3f6bb2U, 0x21a09f9cU,
    };
    HW_SCE_p_func100(Param_p3e_func100_007);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7008d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[13]);

    static const uint32_t Param_p3e_func100_008[] =
    {
        0xf3938813U, 0x2fc4c840U, 0x8df3c011U, 0xc2f82d02U,
    };
    HW_SCE_p_func100(Param_p3e_func100_008);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[17]);

    static const uint32_t Param_p3e_func100_009[] =
    {
        0xa59e61ddU, 0xbd56cf91U, 0x31f43b5fU, 0x8c5dbf5eU,
    };
    HW_SCE_p_func100(Param_p3e_func100_009);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p3e_func102_001[] =
    {
        0xd7fa743cU, 0xd03d980eU, 0x7fcb1434U, 0x9b8f36e8U,
    };
    HW_SCE_p_func102(Param_p3e_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
