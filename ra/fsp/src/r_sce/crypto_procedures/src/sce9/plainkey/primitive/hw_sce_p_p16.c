/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes128XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00001602U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p16_func100_001[] =
    {
        0x23abec22U, 0x8cf54808U, 0xc13237e2U, 0x9a50f88eU,
    };
    HW_SCE_p_func100(Param_p16_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000016U);

    static const uint32_t Param_p16_func101_001[] =
    {
        0xe3d75acdU, 0x11fa95d0U, 0x508ff661U, 0xcd3dfd25U,
    };
    HW_SCE_p_func101(Param_p16_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000008U, 0x00000058U, 0x800103a0U, 0x00000016U);

    static const uint32_t Param_p16_func101_002[] =
    {
        0x0a880954U, 0x2767556eU, 0x46025dcaU, 0x03f28176U,
    };
    HW_SCE_p_func101(Param_p16_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p16_func100_002[] =
    {
        0x78fddeb7U, 0xcd696f78U, 0x248a93b6U, 0xdb183ccaU,
    };
    HW_SCE_p_func100(Param_p16_func100_002);
    WR1_PROG(REG_E0H, 0x81010000U);
    WR1_PROG(REG_04H, 0x00000606U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &OutData_KeyIndex[0]);

    static const uint32_t Param_p16_func100_003[] =
    {
        0xc3dfa0c4U, 0xe272767cU, 0x89df66a4U, 0x60ea4544U,
    };
    HW_SCE_p_func100(Param_p16_func100_003);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    HW_SCE_p_func_sub010(0x80080000U, 0x00008213U);

    static const uint32_t Param_p16_func100_004[] =
    {
        0x5ed79631U, 0x284935b8U, 0xc863a7c0U, 0x60086c93U,
    };
    HW_SCE_p_func100(Param_p16_func100_004);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00008213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    static const uint32_t Param_p16_func100_005[] =
    {
        0x18ecfd57U, 0xcfc37c4dU, 0x13576bd2U, 0x9a282ac0U,
    };
    HW_SCE_p_func100(Param_p16_func100_005);
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

    static const uint32_t Param_p16_func102_001[] =
    {
        0x047a9547U, 0xe7880d65U, 0xc7a1f12bU, 0xe56f2361U,
    };
    HW_SCE_p_func102(Param_p16_func102_001);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
