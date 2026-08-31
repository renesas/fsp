/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func058 (const uint32_t ARG1[], uint32_t ARG2)
{
    static const uint32_t Param_func058_func100_001[] =
    {
        0xbbbfda21U, 0x17944ed0U, 0x0a552a41U, 0x49492666U,
    };
    HW_SCE_p_func100(Param_func058_func100_001);
    HW_SCE_p_func_sub010(0x4a070044U, 0x00000000U);

    HW_SCE_p_func_sub010(0x0e0704c4U, 0x017a1b82U);

    static const uint32_t Param_func058_func100_002[] =
    {
        0x789979acU, 0x30731f75U, 0x9f18dd36U, 0xa2776335U,
    };
    HW_SCE_p_func100(Param_func058_func100_002);
    WR1_PROG(REG_94H, 0x00009020U);
    WR1_PROG(REG_94H, 0x01000000U);

    HW_SCE_p_func_sub010(0x4a040044U, 0x00000000U);

    WR1_PROG(REG_D0H, 0x0e0404c4U);
    WR1_PROG(REG_9CH, 0x81010020U);
    HW_SCE_p_func_sub002(0x00490005U);

    static const uint32_t Param_func058_func100_003[] =
    {
        0x607b3f38U, 0xd59a5b21U, 0x23c741c9U, 0xabb8971dU,
    };
    HW_SCE_p_func100(Param_func058_func100_003);
    WR1_PROG(REG_D0H, 0xf7041c85U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &S_FLASH[ARG2]);

    static const uint32_t Param_func058_func100_004[] =
    {
        0x40cc7015U, 0x5f864117U, 0x59d85843U, 0x9823a95dU,
    };
    HW_SCE_p_func100(Param_func058_func100_004);
    WR1_PROG(REG_D0H, 0x07040d05U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &S_FLASH[ARG2 + 4]);

    WR1_PROG(REG_D0H, 0x8c100005U);
    HW_SCE_p_func_sub002(0x00410011U);

    HW_SCE_p_func_sub008(0x000003c1U, 0x0a0000adU);
    WR4_ADDR(REG_2CH, &ARG1[0]);

    static const uint32_t Param_func058_func100_005[] =
    {
        0xc37244c7U, 0x3ef27430U, 0xe87665dfU, 0x12ce27fbU,
    };
    HW_SCE_p_func100(Param_func058_func100_005);
    HW_SCE_p_func_sub008(0x000003c1U, 0x0a0000bdU);
    WR4_ADDR(REG_2CH, &ARG1[4]);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
