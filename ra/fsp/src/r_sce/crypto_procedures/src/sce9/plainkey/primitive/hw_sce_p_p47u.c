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

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
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
        HW_SCE_p_func100(0x9c2bad13u, 0x79b50416u, 0x08b4a371u, 0xa6936ecau);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x00000a86u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x1f26deedu, 0x56986197u, 0x4d36f8e9u, 0xd2396fe3u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x00004a86u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0x46890128u, 0xa4bea142u, 0x46108c23u, 0x5eb9e253u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x00000e96u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0xf1e2c1c3u, 0xabc1c083u, 0xb30732a7u, 0x8c59ae8du);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x000049a6u;
        SCE->REG_04H = 0x0000c100u;
    }
    else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
    {
        SCE->REG_104H = 0x00000362u;
        HW_SCE_p_func100(0xb0e543a4u, 0xa63ab851u, 0xb0bb040bu, 0x54ffef58u);
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x000007b6u;
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
        HW_SCE_p_func101(0x3e045906u, 0x3dab084bu, 0x7f066ce2u, 0xc6491214u);
    }
    else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xfb0d3b5cu, 0x665b5756u, 0xf6d445c4u, 0xf1f34104u);
    }
    else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xbee7945au, 0x9846b5c0u, 0x2a31d3d7u, 0xa5080511u);
    }
    else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xe585a470u, 0xf5c70a3au, 0x81d43f35u, 0xe506b30fu);
    }
    else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x115cf208u, 0xb5af7fdeu, 0x2d878176u, 0xb6d311d0u);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p47u_r1.prc
***********************************************************************************************************************/
