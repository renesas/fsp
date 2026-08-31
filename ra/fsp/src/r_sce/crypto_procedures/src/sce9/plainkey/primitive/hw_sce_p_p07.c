/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00000702U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p07_func100_001[] =
    {
        0x95582d71U, 0x39635633U, 0x15288f50U, 0x17f47b88U,
    };
    HW_SCE_p_func100(Param_p07_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000007U);

    static const uint32_t Param_p07_func101_001[] =
    {
        0x41eb044fU, 0xd0879d0fU, 0x836bd0a6U, 0xdd94cd7aU,
    };
    HW_SCE_p_func101(Param_p07_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000005U, 0x00000058U, 0x800103a0U, 0x00000007U);

    static const uint32_t Param_p07_func101_002[] =
    {
        0x83e1178eU, 0x3dd77044U, 0x3cd5df94U, 0x9ce47099U,
    };
    HW_SCE_p_func101(Param_p07_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p07_func100_002[] =
    {
        0xeae16410U, 0x81a2bb97U, 0x822b834eU, 0x1611ebcaU,
    };
    HW_SCE_p_func100(Param_p07_func100_002);
    WR1_PROG(REG_E0H, 0x81010000U);
    WR1_PROG(REG_04H, 0x00000606U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &OutData_KeyIndex[0]);

    static const uint32_t Param_p07_func100_003[] =
    {
        0xf2419c1cU, 0xefb76c05U, 0x2d1e5187U, 0xe3503335U,
    };
    HW_SCE_p_func100(Param_p07_func100_003);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    HW_SCE_p_func_sub010(0x80040000U, 0x00008213U);

    WR1_PROG(REG_D0H, 0x40000000U);
    WR1_PROG(REG_C4H, 0x02e487b5U);
    HW_SCE_p_func_sub010(0x81040000U, 0x00002813U);

    static const uint32_t Param_p07_func100_004[] =
    {
        0x248dcc14U, 0x40944f2bU, 0x3a2a8f3fU, 0x66cf1e3fU,
    };
    HW_SCE_p_func100(Param_p07_func100_004);
    HW_SCE_p_func_sub018(0x00000352U, 0x40000000U, 0x000089c5U);
    WR4_PROG(REG_100H,
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000000U),
             change_endian_long(0x00000001U));

    WR1_PROG(REG_04H, 0x00000222U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_KeyIndex[1]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_KeyIndex[5]);

    static const uint32_t Param_p07_func102_001[] =
    {
        0x8728d316U, 0xba08805aU, 0x85a1e7e1U, 0xc29c1790U,
    };
    HW_SCE_p_func102(Param_p07_func102_001);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
