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

void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
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
        HW_SCE_p_func100(0xf2720436u, 0x566f8ebfu, 0x8600badfu, 0x8b943ad3u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000010u;
        SCE->REG_A4H = 0x00008a86u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x1726c41eu, 0xdc246ce5u, 0x66981e2bu, 0x3d2adcdcu);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000010u;
        SCE->REG_A4H = 0x0000ca86u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0xc605e562u, 0xaea80e58u, 0xf22f88fau, 0x30d5a7c1u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000010u;
        SCE->REG_A4H = 0x00008e96u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x8af836f5u, 0x6e503bd4u, 0xb28a1123u, 0x81021aafu);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000010u;
        SCE->REG_A4H = 0x0000c9a6u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x4b9602acu, 0xc9a8ee92u, 0x9dc351f8u, 0x5e9a52d7u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_B0H = 0x40000010u;
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
        HW_SCE_p_func101(0x229f460cu, 0xfcdaec64u, 0xd2d073dbu, 0xf5b19467u);
    }
    else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x61db0a12u, 0x60c99b33u, 0xea6949b8u, 0x2be8ef9bu);
    }
    else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xfa0454c5u, 0x974a12ccu, 0x2a23dddbu, 0xe2ef57bdu);
    }
    else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x96e87ddcu, 0x869f5434u, 0xf6eec13fu, 0x408a88e2u);
    }
    else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x9332c1e8u, 0xf702f588u, 0xca87649cu, 0xafc9c1feu);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p89u.prc
***********************************************************************************************************************/
