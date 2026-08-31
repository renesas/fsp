/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes192RandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00001502U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p15_func100_001[] =
    {
        0x8a3f7abfU, 0x7a0fe242U, 0x2449afa3U, 0xb83f77f7U,
    };
    HW_SCE_p_func100(Param_p15_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000015U);

    static const uint32_t Param_p15_func101_001[] =
    {
        0x22bac565U, 0x0cf2f0ecU, 0xe2e27d12U, 0xc9ed944cU,
    };
    HW_SCE_p_func101(Param_p15_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000006U, 0x00000058U, 0x800103a0U, 0x00000015U);

    static const uint32_t Param_p15_func101_002[] =
    {
        0x43a602beU, 0xa4429645U, 0xfc3db196U, 0xd7ddd670U,
    };
    HW_SCE_p_func101(Param_p15_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p15_func100_002[] =
    {
        0x594fe665U, 0x313bef0dU, 0xbab591bcU, 0x02e355f5U,
    };
    HW_SCE_p_func100(Param_p15_func100_002);
    WR1_PROG(REG_E0H, 0x81010000U);
    WR1_PROG(REG_04H, 0x00000606U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &OutData_KeyIndex[0]);

    static const uint32_t Param_p15_func100_003[] =
    {
        0x0b19c726U, 0x20c53570U, 0x6e8e367fU, 0x0ed1140eU,
    };
    HW_SCE_p_func100(Param_p15_func100_003);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    HW_SCE_p_func_sub010(0x80080000U, 0x00008213U);
    static const uint32_t Param_p15_func100_004[] =
    {
        0x78784c0bU, 0x3dea15d3U, 0x5a6e702aU, 0x1e3b4f1aU,
    };
    HW_SCE_p_func100(Param_p15_func100_004);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00008213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    static const uint32_t Param_p15_func100_005[] =
    {
        0xbe7d9f88U, 0x8bf3700fU, 0x4e302cbdU, 0xc15dac08U,
    };
    HW_SCE_p_func100(Param_p15_func100_005);
    WR1_PROG(REG_D0H, 0x40000100U);
    WR1_PROG(REG_C4H, 0x02e487b7U);
    HW_SCE_p_func_sub010(0x81060000U, 0x0000281bU);
    WR1_PROG(REG_00H, 0x0000200bU);
    HW_SCE_p_func_sub003(0x00000352U, 0x40000000U, 0x000089c5U);
    WR4_PROG(REG_100H,
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000002U));

    WR1_PROG(REG_04H, 0x00000232U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_KeyIndex[1]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_KeyIndex[5]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_KeyIndex[9]);

    static const uint32_t Param_p15_func102_001[] =
    {
        0x51a7e640U, 0x3745d3b6U, 0x46baf5d7U, 0x6b52b63aU,
    };
    HW_SCE_p_func102(Param_p15_func102_001);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
