/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00170001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p17_func100_001[] =
    {
        0xc8c9faa6U, 0x2eb24b33U, 0x59c240faU, 0x68fb03a7U,
    };
    HW_SCE_p_func100(Param_p17_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000017U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p17_func101_001[] =
    {
        0x94ab16faU, 0xb131dfa4U, 0xbd60096eU, 0x3685ff8fU,
    };
    HW_SCE_p_func101(Param_p17_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000009U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000017U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p17_func101_002[] =
    {
        0xc2829a76U, 0xf94adee1U, 0xf7952883U, 0x934aef50U,
    };
    HW_SCE_p_func101(Param_p17_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p17_func100_002[] =
    {
        0xfaa39432U, 0xe166026cU, 0xfa7079b9U, 0x73bc6268U,
    };
    HW_SCE_p_func100(Param_p17_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p17_func100_003[] =
    {
        0x08eb29afU, 0xba3135e6U, 0x0d6728c0U, 0xfffd5a86U,
    };
    HW_SCE_p_func100(Param_p17_func100_003);
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

    static const uint32_t Param_p17_func100_004[] =
    {
        0x4a684fe0U, 0x00a441a1U, 0xaa8a3710U, 0x5821ac70U,
    };
    HW_SCE_p_func100(Param_p17_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p17_func100_005[] =
    {
        0xb5044f3fU, 0x1bcacd6aU, 0x49da4378U, 0xd853e724U,
    };
    HW_SCE_p_func100(Param_p17_func100_005);
    HW_SCE_p_func103();

    static const uint32_t Param_p17_func100_006[] =
    {
        0x0bb18ae5U, 0x1b261f50U, 0x67719504U, 0x2f7bec31U,
    };
    HW_SCE_p_func100(Param_p17_func100_006);
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

    static const uint32_t Param_p17_func100_007[] =
    {
        0xe39b45e6U, 0xdd535717U, 0xb6190d63U, 0xfc97cb44U,
    };
    HW_SCE_p_func100(Param_p17_func100_007);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7008d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[13]);

    static const uint32_t Param_p17_func100_008[] =
    {
        0x0e768cd7U, 0x6e0df69aU, 0x3db5e4eeU, 0x837f1882U,
    };
    HW_SCE_p_func100(Param_p17_func100_008);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[17]);

    static const uint32_t Param_p17_func100_009[] =
    {
        0xf74c152dU, 0x007f1a06U, 0x2f300fddU, 0x18ff0663U,
    };
    HW_SCE_p_func100(Param_p17_func100_009);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p17_func102_001[] =
    {
        0xc0a6c66cU, 0x2d0e5831U, 0xef40b2b8U, 0x89c549ceU,
    };
    HW_SCE_p_func102(Param_p17_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
