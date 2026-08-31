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
    WR1_PROG(REG_94H, ARG1);
    WR1_PROG(REG_94H, ARG2);
    WR1_PROG(REG_94H, ARG3);
    WR1_PROG(REG_94H, ARG4);
}

void HW_SCE_p_func_sub002 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_B4H, ARG1);
    WR1_PROG(REG_B8H, ARG2);
    WR1_PROG(REG_A4H, ARG3);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);
}

void HW_SCE_p_func_sub003 (uint32_t ARG1)
{
    WR1_PROG(REG_00H, ARG1);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
}

void HW_SCE_p_func_sub004 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_14H, ARG1);
    WR1_PROG(REG_D0H, ARG2);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(ARG3));
}

void HW_SCE_p_func_sub005 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_14H, ARG1);
    WR1_PROG(REG_9CH, ARG2);
    WAIT_STS(REG_14H, 31, 1);
}

void HW_SCE_p_func_sub006 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_94H, ARG1);
    WR1_PROG(REG_94H, ARG2);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, ARG3);
}

void HW_SCE_p_func_sub007 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_14H, ARG1);
    WR1_PROG(REG_D4H, ARG2);
    WR1_PROG(REG_D0H, ARG3);
    WAIT_STS(REG_14H, 31, 1);
}

void HW_SCE_p_func_sub008 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_14H, ARG1);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(ARG2));
}

void HW_SCE_p_func_sub009 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_9CH, ARG1);
    WR1_PROG(REG_08H, ARG2);
    WAIT_STS(REG_08H, 30, 1);
}

void HW_SCE_p_func_sub010 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_94H, ARG1);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, ARG2);
}

void HW_SCE_p_func_sub011 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_14H, ARG1);
    WR1_PROG(REG_D0H, ARG2);
    WAIT_STS(REG_14H, 31, 1);
}

void HW_SCE_p_func_sub012 (void)
{
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);
}

void HW_SCE_p_func_sub013 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_D0H, ARG1);
    WR1_PROG(REG_94H, ARG2);
    WR1_PROG(REG_9CH, ARG3);
}

void HW_SCE_p_func_sub014 (uint32_t ARG1)
{
    WR1_PROG(REG_94H, 0x0000a4a0U);
    WR1_PROG(REG_94H, 0x00000008U);
    WR1_PROG(REG_B0H, ARG1);
    WR1_PROG(REG_9CH, 0x80820005U);
}

void HW_SCE_p_func_sub015 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_B0H, ARG1);
    WR1_PROG(REG_08H, ARG2);
    WAIT_STS(REG_08H, 30, 1);
}

void HW_SCE_p_func_sub016 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_14H, ARG1);
    WR1_PROG(REG_D4H, ARG2);
    WR1_PROG(REG_D0H, ARG3);
}

void HW_SCE_p_func_sub017 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_14H, ARG1);
    WR1_PROG(REG_B0H, ARG2);
    WAIT_STS(REG_14H, 31, 1);
}

void HW_SCE_p_func_sub018 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_D0H, ARG1);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(ARG2));
}

void HW_SCE_p_func_sub019 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_B4H, ARG1);
    WR1_PROG(REG_B8H, ARG2);
    WR1_PROG(REG_A4H, ARG3);
    WR1_PROG(REG_08H, 0x00020000U);
}

void HW_SCE_p_func_sub020 (uint32_t ARG1)
{
    WR1_PROG(REG_24H, 0x00000000U);
    WR1_PROG(REG_94H, 0x0000b4a0U);
    WR1_PROG(REG_94H, ARG1);
}

void HW_SCE_p_func_sub021 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_D4H, ARG1);
    WR1_PROG(REG_D0H, ARG2);
    WR1_PROG(REG_9CH, ARG3);
}

void HW_SCE_p_func_sub022 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3)
{
    WR1_PROG(REG_94H, ARG1);
    WR1_PROG(REG_94H, ARG2);
    WR1_PROG(REG_94H, ARG3);
}

void HW_SCE_p_func_sub100 (const uint32_t        ARG1[],
                           const uint32_t        ARG2[],
                           const uint32_t        PARAM[],
                           rsip_sel_bit_length_t bit_len)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(&PARAM[0]);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, ARG1[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(PARAM[4]));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(&PARAM[5]);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x000034c5U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(PARAM[9]));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(&PARAM[10]);
        HW_SCE_p_func044();

        if (bit_len == RSIP_SEL_BIT_LENGTH_256)
        {
            WR1_PROG(REG_14H, 0x000007c1U);
            WR1_PROG(REG_D4H, 0x40000100U);
            WR1_PROG(REG_D0H, 0xf7009d07U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &ARG1[1]);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &ARG1[5]);

            WR1_PROG(REG_B0H, PARAM[14]);
            WR1_PROG(REG_00H, 0x00c10021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x07008d05U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &ARG1[9]);
        }
        else
        {
            WR1_PROG(REG_14H, 0x00000bc1U);
            WR1_PROG(REG_D4H, 0x40000200U);
            WR1_PROG(REG_D0H, 0xf7009d07U);

            for (iLoop = 0U; iLoop < 12U; )
            {
                WAIT_STS(REG_14H, 31, 1);
                WR4_ADDR(REG_2CH, &ARG1[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_B0H, PARAM[14]);
            WR1_PROG(REG_00H, 0x00c10031U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x07008d05U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &ARG1[1 + iLoop]);
        }

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(&PARAM[15]);
    }
    else
    {
        if (bit_len == RSIP_SEL_BIT_LENGTH_256)
        {
            WR1_PROG(REG_14H, 0x000007c5U);
            WR1_PROG(REG_B0H, PARAM[19]);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &ARG2[0]);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &ARG2[4]);
        }
        else
        {
            WR1_PROG(REG_14H, 0x00000bc5U);
            WR1_PROG(REG_B0H, PARAM[19]);
            WAIT_STS(REG_14H, 31, 1);
            WR12_ADDR(REG_2CH, &ARG2[0]);
        }

        HW_SCE_p_func101(&PARAM[20]);
    }
}
