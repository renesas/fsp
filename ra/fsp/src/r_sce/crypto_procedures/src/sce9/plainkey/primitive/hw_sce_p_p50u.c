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

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
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
    if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x12fec111u, 0x837686bcu, 0x29da676fu, 0x2a15b6c6u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x00008a86u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x57bd8fe5u, 0x5a462c45u, 0x9678f8abu, 0x95526c3fu);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x0000ca86u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x587a8d69u, 0xa2d8f37eu, 0xc55267b3u, 0x7b67886cu);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x00008e96u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0xb2c8f072u, 0x646e4af5u, 0xa7435e98u, 0x59950484u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x0000c9a6u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x6e63e543u, 0x0b1c2b84u, 0x13059a4fu, 0xe340fb26u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000000u;
        SCE->REG_A4H = 0x000087b6u;
        SCE->REG_04H = 0x0000c100u;
    }
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Text[0];
    SCE->REG_100H = InData_Text[1];
    SCE->REG_100H = InData_Text[2];
    SCE->REG_100H = InData_Text[3];
    for (iLoop = 4; iLoop < MAX_CNT ; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Text[iLoop + 0];
        SCE->REG_100H = InData_Text[iLoop + 1];
        SCE->REG_100H = InData_Text[iLoop + 2];
        SCE->REG_100H = InData_Text[iLoop + 3];
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_Text[iLoop-4 + 0] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 1] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 2] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_Text[MAX_CNT-4 + 0] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 1] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 2] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 3] = SCE->REG_100H;
    if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xb89f76b5u, 0xee125499u, 0x98999e50u, 0x3ea99faau);
    }
    else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xf861eaa0u, 0xb24c5d5du, 0x3e2a924cu, 0x5c7ad83bu);
    }
    else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x279da2a4u, 0x7268bac3u, 0xe5d5d986u, 0xb26c9b0fu);
    }
    else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xf1bdb534u, 0x2313da8du, 0x7fd36cd2u, 0x78f418cau);
    }
    else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x2db3fdb1u, 0xe0c0ef7fu, 0x665c0a8du, 0xd752d49eu);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p50u_r1.prc
***********************************************************************************************************************/
