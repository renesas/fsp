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

void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
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
        HW_SCE_p_func100(0xf2720436U, 0x566f8ebfU, 0x8600badfU, 0x8b943ad3U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000010U;
        SCE->REG_A4H = 0x00008a86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x1726c41eU, 0xdc246ce5U, 0x66981e2bU, 0x3d2adcdcU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000010U;
        SCE->REG_A4H = 0x0000ca86U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0xc605e562U, 0xaea80e58U, 0xf22f88faU, 0x30d5a7c1U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000010U;
        SCE->REG_A4H = 0x00008e96U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x8af836f5U, 0x6e503bd4U, 0xb28a1123U, 0x81021aafU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000010U;
        SCE->REG_A4H = 0x0000c9a6U;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000362U;
        HW_SCE_p_func100(0x4b9602acU, 0xc9a8ee92U, 0x9dc351f8U, 0x5e9a52d7U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000010U;
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
        HW_SCE_p_func101(0x229f460cU, 0xfcdaec64U, 0xd2d073dbU, 0xf5b19467U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x61db0a12U, 0x60c99b33U, 0xea6949b8U, 0x2be8ef9bU);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0xfa0454c5U, 0x974a12ccU, 0x2a23dddbU, 0xe2ef57bdU);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x96e87ddcU, 0x869f5434U, 0xf6eec13fU, 0x408a88e2U);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x9332c1e8U, 0xf702f588U, 0xca87649cU, 0xafc9c1feU);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p89u.prc
***********************************************************************************************************************/
