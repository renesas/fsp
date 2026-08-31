/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateSha384HmacRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x003c0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    static const uint32_t Param_p3c_func100_001[] =
    {
        0xf7dad53dU, 0xd2403e63U, 0xccf6c130U, 0xcebd17ffU,
    };
    HW_SCE_p_func100(Param_p3c_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003cU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3c_func101_001[] =
    {
        0x72a96ab8U, 0xded2cb2dU, 0xcf5ae6ebU, 0x1fdec224U,
    };
    HW_SCE_p_func101(Param_p3c_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000028U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000003cU));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p3c_func101_002[] =
    {
        0x5136bcdeU, 0x2419e3a5U, 0x166668e8U, 0xa429b725U,
    };
    HW_SCE_p_func101(Param_p3c_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p3c_func100_002[] =
    {
        0x0f70bab7U, 0x552c0b14U, 0xc7fa2455U, 0xa878c019U,
    };
    HW_SCE_p_func100(Param_p3c_func100_002);
    HW_SCE_p_func103();

    static const uint32_t Param_p3c_func100_003[] =
    {
        0x7c1f1622U, 0x9c4b76a2U, 0x0279d1bbU, 0x04ebc43bU,
    };
    HW_SCE_p_func100(Param_p3c_func100_003);
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

    static const uint32_t Param_p3c_func100_004[] =
    {
        0x7e25896dU, 0x748c911dU, 0xe8366938U, 0x6343fac0U,
    };
    HW_SCE_p_func100(Param_p3c_func100_004);
    WR1_PROG(REG_D4H, 0x40000100U);
    HW_SCE_p_func_sub013(0xe7009d07U, 0x00000821U, 0x81880001U);
    HW_SCE_p_func_sub003(0x00490021U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p3c_func100_005[] =
    {
        0x673f784bU, 0xae6da958U, 0x08ff6ba8U, 0xb0511c5fU,
    };
    HW_SCE_p_func100(Param_p3c_func100_005);
    HW_SCE_p_func103();

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub003(0x03410011U);

    static const uint32_t Param_p3c_func100_006[] =
    {
        0xabe77c87U, 0x7b266be9U, 0x8fe04c86U, 0x788cf19fU,
    };
    HW_SCE_p_func100(Param_p3c_func100_006);
    WR1_PROG(REG_D4H, 0x40000000U);
    HW_SCE_p_func_sub013(0xe7008d05U, 0x00000821U, 0x81840001U);
    HW_SCE_p_func_sub003(0x00490011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    static const uint32_t Param_p3c_func100_007[] =
    {
        0x157d625cU, 0xea21b47eU, 0xb170f68cU, 0xd2f9ec7eU,
    };
    HW_SCE_p_func100(Param_p3c_func100_007);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[13]);

    static const uint32_t Param_p3c_func100_008[] =
    {
        0xcb75c39bU, 0x9db638c6U, 0x1f705f05U, 0x1919e7faU,
    };
    HW_SCE_p_func100(Param_p3c_func100_008);
    HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p3c_func102_001[] =
    {
        0x0e1ab193U, 0x7e113ffdU, 0x943939e0U, 0x89ab1546U,
    };
    HW_SCE_p_func102(Param_p3c_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
