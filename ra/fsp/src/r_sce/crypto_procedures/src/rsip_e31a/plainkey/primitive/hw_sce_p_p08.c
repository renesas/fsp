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
        0xb50591dbU, 0xb7b44f30U, 0x8885d5a2U, 0x7eeca29eU,
    };
    HW_SCE_p_func100(Param_p08_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000008U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p08_func101_001[] =
    {
        0x7d1dc500U, 0x384714dbU, 0xa703349bU, 0x70103564U,
    };
    HW_SCE_p_func101(Param_p08_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000008U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p08_func101_002[] =
    {
        0xfdba2b87U, 0x58799176U, 0xdcb3b489U, 0x6bf2f93aU,
    };
    HW_SCE_p_func101(Param_p08_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p08_func100_002[] =
    {
        0xb7127084U, 0xba5d2fe1U, 0xe66c9d80U, 0x558a3286U,
    };
    HW_SCE_p_func100(Param_p08_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p08_func100_003[] =
    {
        0xd0b88675U, 0x60e09d9cU, 0xb92f9a38U, 0xea140150U,
    };
    HW_SCE_p_func100(Param_p08_func100_003);
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

    static const uint32_t Param_p08_func100_004[] =
    {
        0x94752467U, 0x3a2639d1U, 0x60f0f22aU, 0xe6bd6804U,
    };
    HW_SCE_p_func100(Param_p08_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p08_func100_005[] =
    {
        0x7f4c12b0U, 0xaa569979U, 0xa26d3e76U, 0x1bdef976U,
    };
    HW_SCE_p_func100(Param_p08_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    static const uint32_t Param_p08_func100_006[] =
    {
        0xa3ad86bdU, 0x31c726d5U, 0xdd38f8ccU, 0xd5ccb303U,
    };
    HW_SCE_p_func100(Param_p08_func100_006);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p08_func102_001[] =
    {
        0xf8c92e61U, 0xe5622993U, 0xf54fd134U, 0xe2e6eaaeU,
    };
    HW_SCE_p_func102(Param_p08_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
