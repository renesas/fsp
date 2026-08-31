/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateRandomNumberSub (uint32_t OutData_Text[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00002002U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_p20_func100_001[] =
    {
        0xcc566a95U, 0xd54b495bU, 0x13b7c5d5U, 0xf9a0c228U,
    };
    HW_SCE_p_func100(Param_p20_func100_001);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    static const uint32_t Param_p20_func100_002[] =
    {
        0xf90a114aU, 0x4d146fe5U, 0x5da04d77U, 0xef4683f4U,
    };
    HW_SCE_p_func100(Param_p20_func100_002);

    WR1_PROG(REG_04H, 0x00000213U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_Text[0]);

    static const uint32_t Param_p20_func102_001[] =
    {
        0x5cf23bfeU, 0x974c37aeU, 0xb6dfffc7U, 0xb05e02eeU,
    };
    HW_SCE_p_func102(Param_p20_func102_001);

    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
