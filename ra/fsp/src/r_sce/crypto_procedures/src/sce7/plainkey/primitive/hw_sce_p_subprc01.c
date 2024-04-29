/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 05.10.2020 1.00        First Release.
 *         : 02.12.2020 1.01        Added new functions such as the Brainpool curve.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_sce_if.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

void HW_SCE_SelfCheck1SubSub(void)
{
    uint32_t iLoop    = 0U;
    uint32_t iLoop1   = 0U;
    uint32_t iLoop2   = 0U;
    int32_t  jLoop    = 0U;
    uint32_t kLoop    = 0U;
    uint32_t oLoop    = 0U;
    uint32_t oLoop1   = 0U;
    uint32_t oLoop2   = 0U;
    uint32_t dummy    = 0U;
    uint32_t KEY_ADR  = 0U;
    uint32_t OFS_ADR  = 0U;
    uint32_t MAX_CNT2 = 0U;
    (void)iLoop;
    (void)iLoop1;
    (void)iLoop2;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)oLoop1;
    (void)oLoop2;
    (void)dummy;
    (void)KEY_ADR;
    (void)OFS_ADR;
    (void)MAX_CNT2;
    SCE->REG_138H = 0xf597806AU;
    SCE->REG_10CH = 0x00010001U;
    SCE->REG_10H = 0x01234567U;
    SCE->REG_7CH = 0x00000001U;
    SCE->REG_78H = 0x00008007U;
    SCE->REG_134H = 0x76543210U;
    HW_SCE_p_func054(change_endian_long(0x00003008U), change_endian_long(0x00003018U));
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    HW_SCE_p_func050(change_endian_long(0x00010001U));
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_68H = 0x00000417U;
    SCE->REG_6CH = 0xabcdef01U;
    HW_SCE_p_func054(change_endian_long(0x10003008U), change_endian_long(0x10003018U));
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    HW_SCE_p_func050(change_endian_long(0x00000001U));
    SCE->REG_28H = 0x00000001U;
    SCE->REG_3CH = 0x00010173U;
    SCE->REG_4CH = 0x23456789U;
    SCE->REG_80H = 0x00000001U;
    SCE->REG_8CH = 0x000080BBU;
    SCE->REG_94H = 0xabcdef01U;
    SCE->REG_7CH = 0x00000001U;
    SCE->REG_78H = 0x0000011fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_68H = 0x00000017U;
    HW_SCE_p_func054(change_endian_long(0x72f01007U), change_endian_long(0x72f01017U));
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001U));
        HW_SCE_p_func054(change_endian_long(0x72f03007U), change_endian_long(0x72f03017U));
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B31)
        {
            /* waiting */
        }
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001U));
        SCE->REG_28H = 0x00000001U;
        SCE->REG_80H = 0x00000001U;
        SCE->REG_7CH = 0x00000001U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008U;
        HW_SCE_p_func054(change_endian_long(0x72f03007U), change_endian_long(0x72f03017U));
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B31)
        {
            /* waiting */
        }
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001U));
        SCE->REG_28H = 0x00000001U;
        SCE->REG_3CH = 0x00010173U;
        SCE->REG_80H = 0x00000001U;
        SCE->REG_B0H = 0x40000010U;
        SCE->REG_D0H = 0x40000010U;
        SCE->REG_A4H = 0x00008000U;
        SCE->REG_C4H = 0x00008000U;
        SCE->REG_8CH = 0x0000888BU;
        SCE->REG_7CH = 0x00000001U;
        SCE->REG_78H = 0x00000007U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008U;
        SCE->REG_68H = 0x00000017U;
        HW_SCE_p_func054(change_endian_long(0x7af03007U), change_endian_long(0x7af03017U));
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B31)
        {
            /* waiting */
        }
    }
    HW_SCE_p_func051();
    SCE->REG_28H = 0x00000001U;
    SCE->REG_3CH = 0x00810173U;
    HW_SCE_p_func054(change_endian_long(0x00003008U), change_endian_long(0x00003018U));
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x00810173U));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x0080197fU));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x00fe017bU));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x00af091FU));
    }
    HW_SCE_p_func053(change_endian_long(0x000380BBU));
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func053(change_endian_long(0x000380BBU));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func053(change_endian_long(0x000191BBU));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func053(change_endian_long(0x000185B7U));
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_subprc01.prc
***********************************************************************************************************************/
