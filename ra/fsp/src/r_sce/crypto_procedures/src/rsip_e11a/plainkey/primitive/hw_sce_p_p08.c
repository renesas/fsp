/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00080001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p08_func100_001[] =
    {
        0xe627f5a6U, 0x13a2dc85U, 0xdd7be0dbU, 0x30af1342U,
    };
    HW_SCE_p_func100(Param_p08_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub002(0x03410005U);
    HW_SCE_p_func_sub002(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000008U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p08_func101_001[] =
    {
        0x265be13fU, 0xf09fafc2U, 0x77c46b81U, 0xa217f390U,
    };
    HW_SCE_p_func101(Param_p08_func101_001);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000008U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p08_func101_002[] =
    {
        0xae4013f8U, 0xe3659fa1U, 0x227dd32fU, 0x3a94cacbU,
    };
    HW_SCE_p_func101(Param_p08_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p08_func100_002[] =
    {
        0x766ee5c4U, 0xd369993cU, 0x92bc35ecU, 0x944b73f3U,
    };
    HW_SCE_p_func100(Param_p08_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p08_func100_003[] =
    {
        0x2ff8cbefU, 0x49373096U, 0x65de3d45U, 0x845a80f1U,
    };
    HW_SCE_p_func100(Param_p08_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub002(0x03410011U);

    HW_SCE_p_func103();

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub013(0x80840001U);
    HW_SCE_p_func_sub002(0x03410011U);

    static const uint32_t Param_p08_func100_004[] =
    {
        0xd9c764b6U, 0xe9e9cf44U, 0x74c8234cU, 0xbbf87a30U,
    };
    HW_SCE_p_func100(Param_p08_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub016(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub002(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p08_func100_005[] =
    {
        0xf83c4765U, 0xd0918766U, 0xcbe6b4cdU, 0x58eb7b12U,
    };
    HW_SCE_p_func100(Param_p08_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub002(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    static const uint32_t Param_p08_func100_006[] =
    {
        0xff07558eU, 0xf23fc230U, 0xbc66b4e3U, 0x34807c94U,
    };
    HW_SCE_p_func100(Param_p08_func100_006);
    HW_SCE_p_func_sub012(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p08_func102_001[] =
    {
        0xec72d13eU, 0xc399374cU, 0x448595cdU, 0xb5da4e36U,
    };
    HW_SCE_p_func102(Param_p08_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
