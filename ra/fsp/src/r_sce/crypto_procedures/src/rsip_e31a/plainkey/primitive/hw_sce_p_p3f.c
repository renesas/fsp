/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateSha512_256HmacRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x003f0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p3f_func100_001[] =
    {
        0x04c91cd6U, 0x051d2741U, 0x8b668028U, 0x06adc053U,
    };
    HW_SCE_p_func100(Param_p3f_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003fU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3f_func101_001[] =
    {
        0xe4d71888U, 0x3f36b612U, 0x1666be46U, 0x56b67358U,
    };
    HW_SCE_p_func101(Param_p3f_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x0000002bU);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003fU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3f_func101_002[] =
    {
        0x105f804aU, 0xb71cf476U, 0xdc423d9fU, 0xe4fd3b9cU,
    };
    HW_SCE_p_func101(Param_p3f_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p3f_func100_002[] =
    {
        0x10bb0ca8U, 0xbf808d45U, 0xc13f3c6dU, 0x6088d459U,
    };
    HW_SCE_p_func100(Param_p3f_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p3f_func100_003[] =
    {
        0xbb5bcd3bU, 0x65b32cd3U, 0xd69b7421U, 0x38465753U,
    };
    HW_SCE_p_func100(Param_p3f_func100_003);
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

    static const uint32_t Param_p3f_func100_004[] =
    {
        0xb813cf09U, 0x969b1139U, 0x20455e80U, 0x9f08b48bU,
    };
    HW_SCE_p_func100(Param_p3f_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p3f_func100_005[] =
    {
        0x22d0f30eU, 0xd892da03U, 0x2bb71b01U, 0x17b3ab10U,
    };
    HW_SCE_p_func100(Param_p3f_func100_005);
    HW_SCE_p_func103();

    static const uint32_t Param_p3f_func100_006[] =
    {
        0x792fc4e5U, 0xfaee0887U, 0xb9385f98U, 0x47ffe9afU,
    };
    HW_SCE_p_func100(Param_p3f_func100_006);
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

    static const uint32_t Param_p3f_func100_007[] =
    {
        0x1116b956U, 0x81f47dd5U, 0x7f5ed3dcU, 0xf9d65601U,
    };
    HW_SCE_p_func100(Param_p3f_func100_007);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7008d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[13]);

    static const uint32_t Param_p3f_func100_008[] =
    {
        0x3180e737U, 0xea3b8103U, 0x0593ead1U, 0xbe69c06fU,
    };
    HW_SCE_p_func100(Param_p3f_func100_008);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[17]);

    static const uint32_t Param_p3f_func100_009[] =
    {
        0x5a56d801U, 0x93d6c469U, 0xdccb9489U, 0xa36414c0U,
    };
    HW_SCE_p_func100(Param_p3f_func100_009);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p3f_func102_001[] =
    {
        0x85bab92aU, 0x6ed873f8U, 0xff4cf9daU, 0xf7c801d6U,
    };
    HW_SCE_p_func102(Param_p3f_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
