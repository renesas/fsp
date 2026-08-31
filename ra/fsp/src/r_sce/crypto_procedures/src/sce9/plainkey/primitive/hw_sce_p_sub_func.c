/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
void HW_SCE_p_func_sub001 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_24H, ARG1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, ARG2);
    WR1_PROG(REG_24H, ARG3);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, ARG4);
    WAIT_STS(REG_24H, 21, 0);
}

void HW_SCE_p_func_sub002 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_ECH, ARG1);
    WR1_PROG(REG_E0H, ARG2);
    WR1_PROG(REG_00H, ARG3);
    WR1_PROG(REG_2CH, ARG4);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}

void HW_SCE_p_func_sub003 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
    WR1_PROG(REG_104H, ARG1);
    WR1_PROG(REG_D0H, ARG2);
    WR1_PROG(REG_C4H, ARG3);
    WAIT_STS(REG_104H, 31, 1);
}

void HW_SCE_p_func_sub004 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_24H, ARG1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_104H, 0x00000058U);
    WR1_PROG(REG_E0H, 0x80010020U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(ARG2));
}

void HW_SCE_p_func_sub005 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_ECH, ARG1);
    WR1_PROG(REG_104H, ARG2);
    WR1_PROG(REG_E0H, ARG3);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(ARG4));
}

void HW_SCE_p_func_sub006 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_24H, ARG1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, ARG2);
    WR1_PROG(REG_24H, ARG3);
    WAIT_STS(REG_24H, 21, 0);
}

void HW_SCE_p_func_sub007 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_ECH, ARG1);
    WR1_PROG(REG_ECH, ARG2);
    WR1_PROG(REG_ECH, ARG3);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, ARG4);
}

void HW_SCE_p_func_sub008 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_28H, ARG1);
    WR1_PROG(REG_104H, 0x00000058U);
    WR1_PROG(REG_E0H, 0x80010020U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(ARG2));
}

void HW_SCE_p_func_sub009 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_104H, 0x00000058U);
    WR1_PROG(REG_E0H, ARG1);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(ARG2));
}

void HW_SCE_p_func_sub010 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_E0H, ARG1);
    WR1_PROG(REG_00H, ARG2);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}

void HW_SCE_p_func_sub011 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_00H, ARG1);
    WR1_PROG(REG_2CH, ARG2);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}

void HW_SCE_p_func_sub012 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_104H, ARG1);
    WR1_PROG(REG_C4H, ARG2);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(ARG3));
}

void HW_SCE_p_func_sub013 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_C4H, ARG1);
    WR1_PROG(REG_00H, ARG2);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}

void HW_SCE_p_func_sub014 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_ECH, ARG1);
    WR1_PROG(REG_ECH, ARG2);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, ARG3);
}

void HW_SCE_p_func_sub015 (uint32_t ARG1, uint32_t ARG2)
{
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, ARG1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, ARG2);
}

void HW_SCE_p_func_sub016 (uint32_t ARG1, uint32_t ARG2)
{
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, ARG1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_ECH, ARG2);
}

void HW_SCE_p_func_sub017 (uint32_t ARG1, uint32_t ARG2)
{
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, ARG1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, ARG2);
}

void HW_SCE_p_func_sub018 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_104H, ARG1);
    WR1_PROG(REG_D0H, ARG2);
    WR1_PROG(REG_C4H, ARG3);
    WAIT_STS(REG_104H, 31, 1);
}

void HW_SCE_p_func_sub019 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_A4H, ARG1);
    WR1_PROG(REG_00H, ARG2);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}

void HW_SCE_p_func_sub020 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_28H, ARG1);
    WR1_PROG(REG_24H, ARG2);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, ARG3);
}

void HW_SCE_p_func_sub021 (uint32_t ARG1)
{
    WR1_PROG(REG_104H, 0x00000051U);
    WR1_PROG(REG_A4H, ARG1);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));
}

void HW_SCE_p_func_sub022 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_ECH, ARG1);
    WR1_PROG(REG_ECH, ARG2);
    WR1_PROG(REG_ECH, ARG3);
    WR1_PROG(REG_ECH, ARG4);
}

void HW_SCE_p_func_sub023 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_24H, ARG1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, ARG2);
    WAIT_STS(REG_24H, 21, 0);
}
