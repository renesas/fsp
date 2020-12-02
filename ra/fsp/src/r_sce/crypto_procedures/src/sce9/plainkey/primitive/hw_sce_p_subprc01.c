/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED  AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
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
    uint32_t iLoop = 0u, iLoop1 = 0u, iLoop2 = 0u, jLoop = 0u, kLoop = 0u, oLoop = 0u, oLoop1 = 0u, oLoop2 = 0u, KEY_ADR = 0u, OFS_ADR = 0u, MAX_CNT2 = 0u;
    uint32_t dummy = 0u;
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
    SCE->REG_138H = 0xf597806Au;
    SCE->REG_10CH = 0x00010001u;
    SCE->REG_10H = 0x01234567u;
    SCE->REG_7CH = 0x00000001u;
    SCE->REG_78H = 0x00008007u;
    SCE->REG_134H = 0x76543210u;
    HW_SCE_p_func054(change_endian_long(0x00003008u), change_endian_long(0x00003018u));
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    HW_SCE_p_func050(change_endian_long(0x00010001u));
    /* WAIT_LOOP */
    while (0u != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008u;
    SCE->REG_68H = 0x00000417u;
    SCE->REG_6CH = 0xabcdef01u;
    HW_SCE_p_func054(change_endian_long(0x10003008u), change_endian_long(0x10003018u));
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    HW_SCE_p_func050(change_endian_long(0x00000001u));
    SCE->REG_28H = 0x00000001u;
    SCE->REG_3CH = 0x00010173u;
    SCE->REG_4CH = 0x23456789u;
    SCE->REG_80H = 0x00000001u;
    SCE->REG_8CH = 0x000080BBu;
    SCE->REG_94H = 0xabcdef01u;
    SCE->REG_7CH = 0x00000001u;
    SCE->REG_78H = 0x0000011fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008u;
    SCE->REG_68H = 0x00000017u;
    HW_SCE_p_func054(change_endian_long(0x72f01007u), change_endian_long(0x72f01017u));
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001u));
        HW_SCE_p_func054(change_endian_long(0x72f03007u), change_endian_long(0x72f03017u));
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B31)
        {
            /* waiting */
        }
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001u));
        SCE->REG_28H = 0x00000001u;
        SCE->REG_80H = 0x00000001u;
        SCE->REG_7CH = 0x00000001u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008u;
        HW_SCE_p_func054(change_endian_long(0x72f03007u), change_endian_long(0x72f03017u));
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B31)
        {
            /* waiting */
        }
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func050(change_endian_long(0x00000001u));
        SCE->REG_28H = 0x00000001u;
        SCE->REG_3CH = 0x00010173u;
        SCE->REG_80H = 0x00000001u;
        SCE->REG_B0H = 0x40000010u;
        SCE->REG_D0H = 0x40000010u;
        SCE->REG_A4H = 0x00008000u;
        SCE->REG_C4H = 0x00008000u;
        SCE->REG_8CH = 0x0000888Bu;
        SCE->REG_7CH = 0x00000001u;
        SCE->REG_78H = 0x00000007u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_64H_b.B11)
        {
            /* waiting */
        }
        SCE->REG_64H = 0x00000008u;
        SCE->REG_68H = 0x00000017u;
        HW_SCE_p_func054(change_endian_long(0x7af03007u), change_endian_long(0x7af03017u));
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B31)
        {
            /* waiting */
        }
    }
    HW_SCE_p_func051();
    SCE->REG_28H = 0x00000001u;
    SCE->REG_3CH = 0x00810173u;
    HW_SCE_p_func054(change_endian_long(0x00003008u), change_endian_long(0x00003018u));
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x00810173u));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x0080197fu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x00fe017bu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func052(change_endian_long(0x00af091Fu));
    }
    HW_SCE_p_func053(change_endian_long(0x000380BBu));
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        HW_SCE_p_func053(change_endian_long(0x000380BBu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func053(change_endian_long(0x000191BBu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        HW_SCE_p_func053(change_endian_long(0x000185B7u));
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_subprc01.prc
***********************************************************************************************************************/
