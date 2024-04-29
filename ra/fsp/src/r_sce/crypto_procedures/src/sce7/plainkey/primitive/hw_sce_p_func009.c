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

void HW_SCE_p_func009(void)
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
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000004U;
    SCE->REG_38H = 0x000000b0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000000U;
    SCE->REG_34H = 0x00000002U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000880cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000020U;
    SCE->REG_24H = 0x80007cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00004c0cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000010U;
    SCE->REG_24H = 0x800098d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000ac0cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x8000a8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x8000c8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00029008U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000094aU;
    SCE->REG_E0H = 0x8088000aU;
    SCE->REG_00H = 0x00008323U;
    SCE->REG_2CH = 0x000000a5U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b540U;
    SCE->REG_ECH = 0x00000020U;
    SCE->REG_E0H = 0x8088000aU;
    SCE->REG_00H = 0x00008323U;
    SCE->REG_2CH = 0x00000025U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b540U;
    SCE->REG_ECH = 0x00000040U;
    SCE->REG_E0H = 0x8088000aU;
    SCE->REG_00H = 0x00008323U;
    SCE->REG_2CH = 0x0000002aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b540U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_E0H = 0x8088000aU;
    SCE->REG_00H = 0x00008323U;
    SCE->REG_2CH = 0x000000adU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x0000080cU;
    SCE->REG_24H = 0x8000f4d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000810U;
    SCE->REG_24H = 0x80009cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000808U;
    SCE->REG_24H = 0x80009008U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000808U;
    SCE->REG_24H = 0x8000b0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_func009.prc
***********************************************************************************************************************/
