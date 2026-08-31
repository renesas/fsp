/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00001702U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p17_func100_001[] =
    {
        0x737bb4a5U, 0xbff6a348U, 0xaeb16686U, 0xe2d29c1aU,
    };
    HW_SCE_p_func100(Param_p17_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000017U);

    static const uint32_t Param_p17_func101_001[] =
    {
        0x4815a41cU, 0x00916820U, 0xbe01c103U, 0x1dec006aU,
    };
    HW_SCE_p_func101(Param_p17_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000009U, 0x00000058U, 0x800103a0U, 0x00000017U);

    static const uint32_t Param_p17_func101_002[] =
    {
        0xd842bfd1U, 0xd2970d65U, 0xbc2702f7U, 0x02db49feU,
    };
    HW_SCE_p_func101(Param_p17_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p17_func100_002[] =
    {
        0xf7d92364U, 0x5552bf8aU, 0x97e251cdU, 0xecbc6a8cU,
    };
    HW_SCE_p_func100(Param_p17_func100_002);
    WR1_PROG(REG_E0H, 0x81010000U);
    WR1_PROG(REG_04H, 0x00000606U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &OutData_KeyIndex[0]);

    static const uint32_t Param_p17_func100_003[] =
    {
        0x9393aedfU, 0x0a40b1f7U, 0x05756c3aU, 0x1b56ba0cU,
    };
    HW_SCE_p_func100(Param_p17_func100_003);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    HW_SCE_p_func_sub010(0x80100000U, 0x00008213U);

    static const uint32_t Param_p17_func100_004[] =
    {
        0xac85b8abU, 0xee4cd758U, 0xa30bc79dU, 0x400754d0U,
    };
    HW_SCE_p_func100(Param_p17_func100_004);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00008213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    static const uint32_t Param_p17_func100_005[] =
    {
        0x72864ca0U, 0xa02a9463U, 0x51458194U, 0x25480ca7U,
    };
    HW_SCE_p_func100(Param_p17_func100_005);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00008213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    static const uint32_t Param_p17_func100_006[] =
    {
        0xca854ddfU, 0x013d0d2bU, 0xbae6953fU, 0x203b2168U,
    };
    HW_SCE_p_func100(Param_p17_func100_006);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00008213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    static const uint32_t Param_p17_func100_007[] =
    {
        0x98a0b10bU, 0xbc9e675fU, 0xc7c22bccU, 0xc608476eU,
    };
    HW_SCE_p_func100(Param_p17_func100_007);
    WR1_PROG(REG_D0H, 0x40000300U);
    WR1_PROG(REG_C4H, 0x02e487b7U);
    WR1_PROG(REG_E0H, 0x81100000U);
    WR1_PROG(REG_00H, 0x00002843U);

    WR1_PROG(REG_04H, 0x00000242U);
    for (iLoop = 1; iLoop < 17; )
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_KeyIndex[iLoop]);
        iLoop = iLoop + 4U;
    }

    static const uint32_t Param_p17_func100_008[] =
    {
        0x6d2f16f6U, 0xa21672b3U, 0x54a9986cU, 0xb2894ec7U,
    };
    HW_SCE_p_func100(Param_p17_func100_008);
    HW_SCE_p_func_sub018(0x00000352U, 0x40000000U, 0x000089c5U);
    WR4_PROG(REG_100H,
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000004U));

    WR1_PROG(REG_04H, 0x00000212U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_KeyIndex[iLoop]);

    static const uint32_t Param_p17_func102_001[] =
    {
        0xe907d5eeU, 0x06fc1a87U, 0x4695e21dU, 0x9b334c1dU,
    };
    HW_SCE_p_func102(Param_p17_func102_001);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
