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

void HW_SCE_Aes256EncryptDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT)
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
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x2ea43b6aU, 0xb703a421U, 0x983d7d93U, 0xc4baf315U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00008a86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0xbde84985U, 0x55ed9e62U, 0x61f3398aU, 0xbf72e4b4U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000ca86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0xfa67f90dU, 0x21d69571U, 0x30ddf9c4U, 0x81eb442fU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00008e96U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x9d804d67U, 0x9b9b4cefU, 0xfd9f77c3U, 0x31fa99f5U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000c9a6U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0xeaff5895U, 0xda7090e7U, 0x59979607U, 0x0a79320fU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x000087b6U;
        SCE->REG_04H = 0x0000c100U;
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
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
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Text[iLoop + 0];
        SCE->REG_100H = InData_Text[iLoop + 1];
        SCE->REG_100H = InData_Text[iLoop + 2];
        SCE->REG_100H = InData_Text[iLoop + 3];
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_Text[iLoop-4 + 0] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 1] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 2] = SCE->REG_100H;
        OutData_Text[iLoop-4 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_Text[MAX_CNT-4 + 0] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 1] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 2] = SCE->REG_100H;
    OutData_Text[MAX_CNT-4 + 3] = SCE->REG_100H;
    if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xe614be6cU, 0xa2f58ca8U, 0xfc73bcc6U, 0xbcba72e6U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xb9fbf89cU, 0x43c4dfc7U, 0xfb2f9d48U, 0xc5fca7a3U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x60869e23U, 0x330b38c2U, 0xa14a865dU, 0xc6424cd0U);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x1a0aca75U, 0x714a0200U, 0xf5878a83U, 0x4cf77272U);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x912f3543U, 0x045a8328U, 0x3c8bf290U, 0xa641205bU);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p50u.prc
***********************************************************************************************************************/
