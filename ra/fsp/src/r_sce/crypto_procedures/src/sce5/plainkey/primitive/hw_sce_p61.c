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

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
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
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0xc099fa80U, 0x55f8d7e7U, 0xb1b81cd1U, 0xe45dc05cU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x0000088eU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0xc4afbe43U, 0xfbe23476U, 0x3869f8fbU, 0xa1ddf110U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x0000488eU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0x222a7ebeU, 0xfa5080beU, 0x9dc5000cU, 0x2cb50d11U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x00000c9eU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0x96b0d912U, 0x5f0ba5e6U, 0x3ffcce56U, 0xbd9481eeU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x000049aeU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0xec8fa4d2U, 0x1a6dc8d2U, 0x4067dba7U, 0x266ae636U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_A4H = 0x000006beU;
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
        HW_SCE_func206();
        HW_SCE_func002(0x6d31fdbeU, 0xf4147098U, 0x7a374888U, 0xbb9e479cU);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0x797ba3d2U, 0x4de21909U, 0x07e3a19dU, 0xb981a166U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0x2debffd0U, 0x75734739U, 0xf9eabd2dU, 0x004be10eU);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0x4cfe8eb3U, 0xb71cf565U, 0x8714d05fU, 0x093a1f3dU);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0xa919894bU, 0x90f11cf5U, 0x3cdb87c5U, 0x8882d91fU);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p61.prc
***********************************************************************************************************************/
