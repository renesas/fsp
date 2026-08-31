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
        0xa126d95eU, 0x7c9b58c2U, 0xa08a31b9U, 0x776770c8U,
    };
    HW_SCE_p_func100(Param_p07_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    WR1_PROG(REG_9CH, 0x80010000U);
    HW_SCE_p_func_sub002(0x03410005U);
    HW_SCE_p_func_sub002(0x0001000dU);

    WR1_PROG(REG_94H, 0x000034c0U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000007U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p07_func101_001[] =
    {
        0x26c31b4bU, 0x74230415U, 0x4b5fbd5cU, 0xb822f63fU,
    };
    HW_SCE_p_func101(Param_p07_func101_001);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000007U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p07_func101_002[] =
    {
        0x43a6dfceU, 0xdd39fb89U, 0x492fce71U, 0x7e3f57dfU,
    };
    HW_SCE_p_func101(Param_p07_func101_002);
    HW_SCE_p_func044();

    static const uint32_t Param_p07_func100_002[] =
    {
        0xdb310a39U, 0x303ac451U, 0x485052c9U, 0x228508faU,
    };
    HW_SCE_p_func100(Param_p07_func100_002);
    HW_SCE_p_func103();

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    HW_SCE_p_func_sub002(0x03410011U);

    static const uint32_t Param_p07_func100_003[] =
    {
        0xcec3a6afU, 0x2dd7d901U, 0x456fd12bU, 0x510f32fcU,
    };
    HW_SCE_p_func100(Param_p07_func100_003);
    WR1_PROG(REG_D4H, 0x40000000U);
    HW_SCE_p_func_sub016(0xe7009d05U, 0x00000821U, 0x81840001U);
    HW_SCE_p_func_sub002(0x00490011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);

    static const uint32_t Param_p07_func100_004[] =
    {
        0x2e95ffa8U, 0x6600abafU, 0xe836fcabU, 0xb6a5e1f3U,
    };
    HW_SCE_p_func100(Param_p07_func100_004);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub002(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    static const uint32_t Param_p07_func100_005[] =
    {
        0x1345978aU, 0x84f650e5U, 0xdbcbe8a5U, 0x9ba76eb2U,
    };
    HW_SCE_p_func100(Param_p07_func100_005);
    HW_SCE_p_func_sub012(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    static const uint32_t Param_p07_func102_001[] =
    {
        0xe61be1ddU, 0x5cf527e7U, 0x1980189cU, 0xb587fe80U,
    };
    HW_SCE_p_func102(Param_p07_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
