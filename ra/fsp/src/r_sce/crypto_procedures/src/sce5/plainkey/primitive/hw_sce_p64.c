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

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
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
        HW_SCE_func001(0x624aadcbU, 0xe50f8155U, 0x4711c39cU, 0xfd2ef7b1U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000888eU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0xc4422ed7U, 0x384f3f12U, 0x38eb866fU, 0x68b545e7U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000c88eU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0x32d07d47U, 0x3dd04bfbU, 0x9032f3fdU, 0x62191c6eU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x00008c9eU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0x99a6263aU, 0xe91d3aa8U, 0x104e62bcU, 0xcd57cfa6U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x0000c9aeU;
        SCE->REG_04H = 0x0000c100U;
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        SCE->REG_104H = 0x00000361U;
        HW_SCE_func001(0x5dffe167U, 0x69f359d3U, 0xb3fa7680U, 0x8792a6a3U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x000086beU;
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
        HW_SCE_func002(0xff48cf0eU, 0xc56d4fb1U, 0x690b30c9U, 0xec43e750U);
    }
    else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0xd3fc3930U, 0x1ad2ed42U, 0xaf63893cU, 0x7cf9d506U);
    }
    else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0xfcb04506U, 0xdfd7fbebU, 0xac25a3fbU, 0x3025878eU);
    }
    else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0xe54e9a91U, 0x5cf3e032U, 0x7fd66d73U, 0x2b438f10U);
    }
    else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
    {
        HW_SCE_func206();
        HW_SCE_func002(0x144f6b8bU, 0x0696d7b6U, 0x13c8804cU, 0x40bbcfbdU);
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p64.prc
***********************************************************************************************************************/
