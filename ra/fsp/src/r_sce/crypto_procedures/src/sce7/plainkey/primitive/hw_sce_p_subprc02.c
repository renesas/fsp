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

void HW_SCE_SelfCheck2SubSub(void)
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
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000B50U;
    SCE->REG_ECH = 0x00000842U;
    SCE->REG_ECH = 0x000008c6U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x0000b4a0U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x00000863U;
    SCE->REG_C4H = 0x41001e5eU;
    SCE->REG_00H = 0x80002401U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001200U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B30)
    {
        /* waiting */
    }
    SCE->REG_00H = 0x00000001U;
    SCE->REG_C4H = 0x00000000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x0010B008U;
    SCE->REG_ECH = 0x00000800U;
    SCE->REG_E0H = 0x80900000U;
    SCE->REG_00H = 0x00008443U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    for(iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x01003804U;
        SCE->REG_ECH = 0x340028e0U;
        SCE->REG_ECH = 0x10005066U;
        SCE->REG_ECH = 0x00002440U;
        SCE->REG_ECH = 0x00002cc0U;
        SCE->REG_ECH = 0x00002485U;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_subprc02.prc
***********************************************************************************************************************/
