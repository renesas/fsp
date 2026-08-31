/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_SelfCheck1SubSub (void)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_138H, 0xf597806AU);
    WR1_PROG(REG_10CH, 0x00010001U);

    WR1_PROG(REG_10H, 0x01234567U);
    WR1_PROG(REG_7CH, 0x00000001U);
    WR1_PROG(REG_78H, 0x00008007U);
    WR1_PROG(REG_134H, 0x76543210U);
    HW_SCE_p_func054(change_endian_long(0x00003008U), change_endian_long(0x00003018U));
    WAIT_STS(REG_00H, 31, 0);

    HW_SCE_p_func050(change_endian_long(0x00010001U));

    WAIT_STS(REG_64H, 11, 0);
    WR1_PROG(REG_64H, 0x00000008U);
    WR1_PROG(REG_68H, 0x00000417U);
    WR1_PROG(REG_6CH, 0xabcdef01U);
    HW_SCE_p_func054(change_endian_long(0x10003008U), change_endian_long(0x10003018U));
    WAIT_STS(REG_00H, 31, 0);

    HW_SCE_p_func050(change_endian_long(0x00000001U));

    WR1_PROG(REG_28H, 0x00000001U);
    WR1_PROG(REG_3CH, 0x00010173U);
    WR1_PROG(REG_4CH, 0x23456789U);
    WR1_PROG(REG_80H, 0x00000001U);
    WR1_PROG(REG_8CH, 0x000080BBU);
    WR1_PROG(REG_94H, 0xabcdef01U);
    WR1_PROG(REG_7CH, 0x00000001U);
    WR1_PROG(REG_78H, 0x0000011fU);
    WAIT_STS(REG_64H, 11, 0);
    WR1_PROG(REG_64H, 0x00000008U);
    WR1_PROG(REG_68H, 0x00000017U);
    HW_SCE_p_func054(change_endian_long(0x72f01007U), change_endian_long(0x72f01017U));
    WAIT_STS(REG_00H, 31, 0);

    for (iLoop = 0U; iLoop < 6; iLoop++)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001U));

        HW_SCE_p_func054(change_endian_long(0x72f03007U), change_endian_long(0x72f03017U));
        WAIT_STS(REG_00H, 31, 0);
    }

    for (iLoop = 0U; iLoop < 6; iLoop++)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001U));

        WR1_PROG(REG_28H, 0x00000001U);
        WR1_PROG(REG_80H, 0x00000001U);
        WR1_PROG(REG_7CH, 0x00000001U);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000008U);
        HW_SCE_p_func054(change_endian_long(0x72f03007U), change_endian_long(0x72f03017U));
        WAIT_STS(REG_00H, 31, 0);
    }

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001U));

        WR1_PROG(REG_28H, 0x00000001U);
        WR1_PROG(REG_3CH, 0x00010173U);
        WR1_PROG(REG_80H, 0x00000001U);
        WR1_PROG(REG_B0H, 0x40000010U);
        WR1_PROG(REG_D0H, 0x40000010U);
        WR1_PROG(REG_A4H, 0x00008000U);
        WR1_PROG(REG_C4H, 0x00008000U);
        WR1_PROG(REG_8CH, 0x0000888BU);
        WR1_PROG(REG_7CH, 0x00000001U);
        WR1_PROG(REG_78H, 0x00000007U);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000008U);
        WR1_PROG(REG_68H, 0x00000017U);
        HW_SCE_p_func054(change_endian_long(0x7af03007U), change_endian_long(0x7af03017U));
        WAIT_STS(REG_00H, 31, 0);
    }

    HW_SCE_p_func051();

    WR1_PROG(REG_28H, 0x00000001U);
    WR1_PROG(REG_3CH, 0x00810173U);
    HW_SCE_p_func054(change_endian_long(0x00003008U), change_endian_long(0x00003018U));
    WAIT_STS(REG_00H, 31, 0);

    for (iLoop = 0U; iLoop < 6; iLoop++)
    {
        HW_SCE_p_func052(change_endian_long(0x00810173U));
    }

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        HW_SCE_p_func052(change_endian_long(0x0080197fU));
    }

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        HW_SCE_p_func052(change_endian_long(0x00fe017bU));
    }

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        HW_SCE_p_func052(change_endian_long(0x00af091FU));
    }

    HW_SCE_p_func053(change_endian_long(0x000380BBU));

    for (iLoop = 0U; iLoop < 6; iLoop++)
    {
        HW_SCE_p_func053(change_endian_long(0x000380BBU));
    }

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        HW_SCE_p_func053(change_endian_long(0x000191BBU));
    }

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        HW_SCE_p_func053(change_endian_long(0x000185B7U));
    }
}
