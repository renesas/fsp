/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00000802U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p08_func100_001[] =
    {
        0x486a111dU, 0x29f6d6daU, 0xce91597dU, 0xc63a80a5U,
    };
    HW_SCE_p_func100(Param_p08_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000008U);

    static const uint32_t Param_p08_func101_001[] =
    {
        0x9d1d30efU, 0x04e6289bU, 0x0e7f730cU, 0x678b980cU,
    };
    HW_SCE_p_func101(Param_p08_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000007U, 0x00000058U, 0x800103a0U, 0x00000008U);

    static const uint32_t Param_p08_func101_002[] =
    {
        0x6c226c1bU, 0xb630a761U, 0xa2d8c6f3U, 0x672d12aeU,
    };
    HW_SCE_p_func101(Param_p08_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p08_func100_002[] =
    {
        0x6079276cU, 0x59d50fb9U, 0xbd4e561aU, 0x86e05366U,
    };
    HW_SCE_p_func100(Param_p08_func100_002);
    WR1_PROG(REG_E0H, 0x81010000U);
    WR1_PROG(REG_04H, 0x00000606U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &OutData_KeyIndex[0]);

    static const uint32_t Param_p08_func100_003[] =
    {
        0xe69703ebU, 0xba7394ccU, 0x4cb5d6e4U, 0xb4745793U,
    };
    HW_SCE_p_func100(Param_p08_func100_003);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    HW_SCE_p_func_sub010(0x80080000U, 0x00008213U);
    static const uint32_t Param_p08_func100_004[] =
    {
        0xbd01dcc1U, 0x16cd31d6U, 0x6634e7beU, 0xff62b791U,
    };
    HW_SCE_p_func100(Param_p08_func100_004);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00008213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
    static const uint32_t Param_p08_func100_005[] =
    {
        0x78c9115aU, 0xc5dd48b9U, 0x7e7ed9a3U, 0xe62efcacU,
    };
    HW_SCE_p_func100(Param_p08_func100_005);

    WR1_PROG(REG_D0H, 0x40000100U);
    WR1_PROG(REG_C4H, 0x02e487b7U);
    WR1_PROG(REG_E0H, 0x81080000U);
    WR1_PROG(REG_00H, 0x00002823U);
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

    static const uint32_t Param_p08_func102_001[] =
    {
        0x3b696d5fU, 0x686352f3U, 0x37f6ff6fU, 0x9a7c40c2U,
    };
    HW_SCE_p_func102(Param_p08_func102_001);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
