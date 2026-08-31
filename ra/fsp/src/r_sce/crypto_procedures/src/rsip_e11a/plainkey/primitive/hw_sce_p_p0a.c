/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateSha224HmacRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x000a0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p0a_func100_001[] =
    {
        0x3d03389eU, 0x3e942d5cU, 0x150c492bU, 0xd5cd8aacU,
    };
    HW_SCE_p_func100(Param_p0a_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub002(0x03410005U);
    HW_SCE_p_func_sub002(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000aU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p0a_func101_001[] =
    {
        0x2eb385dbU, 0x30b9c4aeU, 0xbfef9e5eU, 0xdae0ba86U,
    };
    HW_SCE_p_func101(Param_p0a_func101_001);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x0000001aU);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000aU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p0a_func101_002[] =
    {
        0xc966bac0U, 0x26c56014U, 0x858c22adU, 0x15645302U,
    };
    HW_SCE_p_func101(Param_p0a_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p0a_func100_002[] =
    {
        0x7998b9e4U, 0x9359eb32U, 0x2b780124U, 0xe48ce084U,
    };
    HW_SCE_p_func100(Param_p0a_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p0a_func100_003[] =
    {
        0x370e575eU, 0x5c09600bU, 0xe61ca789U, 0x827e89e1U,
    };
    HW_SCE_p_func100(Param_p0a_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub002(0x03410011U);

    HW_SCE_p_func103();

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub013(0x80840001U);
    HW_SCE_p_func_sub002(0x03410011U);

    static const uint32_t Param_p0a_func100_004[] =
    {
        0x867c9ac1U, 0x1da428fdU, 0x608476d6U, 0xfc18f782U,
    };
    HW_SCE_p_func100(Param_p0a_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub016(0xe7009d07U, 0x00000821U, 0x81870001U);
    HW_SCE_p_func_sub002(0x0049001dU);
    HW_SCE_p_func_sub002(0x00400005U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p0a_func100_005[] =
    {
        0xa7614708U, 0xe4b1eeb1U, 0xe081ab12U, 0x250239e3U,
    };
    HW_SCE_p_func100(Param_p0a_func100_005);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub002(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    static const uint32_t Param_p0a_func100_006[] =
    {
        0x11c0e314U, 0x7ac17292U, 0x4db64ef6U, 0x7aff2f05U,
    };
    HW_SCE_p_func100(Param_p0a_func100_006);
    HW_SCE_p_func_sub012(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p0a_func102_001[] =
    {
        0xcc763ac4U, 0x5d2ba2e7U, 0x64764c61U, 0x9208f165U,
    };
    HW_SCE_p_func102(Param_p0a_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
