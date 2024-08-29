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

void HW_SCE_p_func000(uint32_t *InData_PaddedMsg, int32_t MAX_CNT)
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
    SCE->REG_104H = 0x000000b4U;
    for (iLoop = 0; iLoop < (uint32_t)MAX_CNT; iLoop = iLoop + 16)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_PaddedMsg[iLoop + 0];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 1];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 2];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 3];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 4];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 5];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 6];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 7];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 8];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 9];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 10];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 11];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 12];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 13];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 14];
        SCE->REG_100H = InData_PaddedMsg[iLoop + 15];
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000000U;
    SCE->REG_1CH = 0x00001600U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func000.prc
***********************************************************************************************************************/
