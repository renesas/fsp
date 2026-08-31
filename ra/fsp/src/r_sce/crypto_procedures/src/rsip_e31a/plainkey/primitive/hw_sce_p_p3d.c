/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateSha512HmacRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x003d0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p3d_func100_001[] =
    {
        0xa5b9dde6U, 0xa8d55e35U, 0xd47609e5U, 0x1f5cd3b6U,
    };
    HW_SCE_p_func100(Param_p3d_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003dU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3d_func101_001[] =
    {
        0x125be6b2U, 0xe3079d46U, 0xa0713846U, 0x4be774ffU,
    };
    HW_SCE_p_func101(Param_p3d_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000029U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003dU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3d_func101_002[] =
    {
        0xb1cd8676U, 0x258f267bU, 0x33784246U, 0x4f8c44a1U,
    };
    HW_SCE_p_func101(Param_p3d_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p3d_func100_002[] =
    {
        0xd2958e89U, 0xb66e6b93U, 0x1a040aa7U, 0x5bd5164eU,
    };
    HW_SCE_p_func100(Param_p3d_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p3d_func100_003[] =
    {
        0xc74be279U, 0x0e74ce27U, 0xccb3e891U, 0xab3e4efaU,
    };
    HW_SCE_p_func100(Param_p3d_func100_003);
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

    static const uint32_t Param_p3d_func100_004[] =
    {
        0x6e8018a2U, 0xcf3e12b2U, 0x35abcaaeU, 0xc85d096dU,
    };
    HW_SCE_p_func100(Param_p3d_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p3d_func100_005[] =
    {
        0x1f8e8088U, 0x86e01bdeU, 0xb99a1baeU, 0x7ec2ef6fU,
    };
    HW_SCE_p_func100(Param_p3d_func100_005);
    HW_SCE_p_func103();

    static const uint32_t Param_p3d_func100_006[] =
    {
        0x580fcd27U, 0x9e0355d9U, 0x9d838098U, 0x9e1d1babU,
    };
    HW_SCE_p_func100(Param_p3d_func100_006);
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

    static const uint32_t Param_p3d_func100_007[] =
    {
        0x27a22cc9U, 0x80c01daaU, 0x08205dd2U, 0xecc89693U,
    };
    HW_SCE_p_func100(Param_p3d_func100_007);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7008d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[13]);

    static const uint32_t Param_p3d_func100_008[] =
    {
        0x8ea5d7abU, 0x7c3e8fb2U, 0xaf60ee2dU, 0x78b0967bU,
    };
    HW_SCE_p_func100(Param_p3d_func100_008);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[17]);

    static const uint32_t Param_p3d_func100_009[] =
    {
        0x3f3197a3U, 0x0c3e1185U, 0xb356a163U, 0x33259a3bU,
    };
    HW_SCE_p_func100(Param_p3d_func100_009);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p3d_func102_001[] =
    {
        0xa01a5183U, 0x8d852b9eU, 0x7fc22198U, 0xd91c7da0U,
    };
    HW_SCE_p_func102(Param_p3d_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
