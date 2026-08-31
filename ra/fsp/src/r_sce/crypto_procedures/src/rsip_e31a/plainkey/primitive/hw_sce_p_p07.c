/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00070001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p07_func100_001[] =
    {
        0x6b8831dcU, 0x565618e5U, 0x987f49c2U, 0xb28b09a3U,
    };
    HW_SCE_p_func100(Param_p07_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000007U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p07_func101_001[] =
    {
        0x7304f8ceU, 0x5d60bc5eU, 0xa4cadb5bU, 0x40f9202aU,
    };
    HW_SCE_p_func101(Param_p07_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000007U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p07_func101_002[] =
    {
        0x74e84a79U, 0x71174020U, 0x4c38b38bU, 0x39b8594bU,
    };
    HW_SCE_p_func101(Param_p07_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p07_func100_002[] =
    {
        0x442cc6a2U, 0xd8d473e5U, 0x0cfb555dU, 0x6dd5a904U,
    };
    HW_SCE_p_func100(Param_p07_func100_002);
    HW_SCE_p_func103();

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub003(0x03410011U);

    static const uint32_t Param_p07_func100_003[] =
    {
        0xc93ab9aeU, 0xc6a4d5b2U, 0x4bf2398aU, 0x0d8ae1d7U,
    };
    HW_SCE_p_func100(Param_p07_func100_003);
    WR1_PROG(REG_D4H, 0x40000000U);
    HW_SCE_p_func_sub013(0xe7009d05U, 0x00000821U, 0x81840001U);
    HW_SCE_p_func_sub003(0x00490011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);

    static const uint32_t Param_p07_func100_004[] =
    {
        0x0781fd32U, 0x469476ecU, 0x6c31561fU, 0xda9732faU,
    };
    HW_SCE_p_func100(Param_p07_func100_004);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p07_func100_005[] =
    {
        0x270e1155U, 0xb92ec8c7U, 0x8fa13de6U, 0x66593009U,
    };
    HW_SCE_p_func100(Param_p07_func100_005);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p07_func102_001[] =
    {
        0xa6109911U, 0x4f3338c9U, 0x6e924b97U, 0xfae6e892U,
    };
    HW_SCE_p_func102(Param_p07_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
