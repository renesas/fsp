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

void HW_SCE_p_func070(uint32_t ARG1)
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
    SCE->REG_ECH = 0x30003340U;
    SCE->REG_ECH = 0x00050020U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0131ec45U;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x014bb610U;
    SCE->REG_ECH = 0x00070040U;
    SCE->REG_ECH = 0x30003380U;
    SCE->REG_ECH = 0x00070020U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x94542614U;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0xf5ba24feU;
    SCE->REG_ECH = 0x00050040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x98bb59d6U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_C4H = 0x000c3b0cU;
    SCE->REG_E0H = 0x810103c0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00002f62U;
    SCE->REG_D0H = 0x00000b00U;
    SCE->REG_C4H = 0x02f087bfU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+68 + 0];
    SCE->REG_100H = S_FLASH[ARG1+68 + 1];
    SCE->REG_100H = S_FLASH[ARG1+68 + 2];
    SCE->REG_100H = S_FLASH[ARG1+68 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+72 + 0];
    SCE->REG_100H = S_FLASH[ARG1+72 + 1];
    SCE->REG_100H = S_FLASH[ARG1+72 + 2];
    SCE->REG_100H = S_FLASH[ARG1+72 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000015U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+76 + 0];
    SCE->REG_100H = S_FLASH[ARG1+76 + 1];
    SCE->REG_100H = S_FLASH[ARG1+76 + 2];
    SCE->REG_100H = S_FLASH[ARG1+76 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+80 + 0];
    SCE->REG_100H = S_FLASH[ARG1+80 + 1];
    SCE->REG_100H = S_FLASH[ARG1+80 + 2];
    SCE->REG_100H = S_FLASH[ARG1+80 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000009aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+84 + 0];
    SCE->REG_100H = S_FLASH[ARG1+84 + 1];
    SCE->REG_100H = S_FLASH[ARG1+84 + 2];
    SCE->REG_100H = S_FLASH[ARG1+84 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+88 + 0];
    SCE->REG_100H = S_FLASH[ARG1+88 + 1];
    SCE->REG_100H = S_FLASH[ARG1+88 + 2];
    SCE->REG_100H = S_FLASH[ARG1+88 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000001dU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+92 + 0];
    SCE->REG_100H = S_FLASH[ARG1+92 + 1];
    SCE->REG_100H = S_FLASH[ARG1+92 + 2];
    SCE->REG_100H = S_FLASH[ARG1+92 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+96 + 0];
    SCE->REG_100H = S_FLASH[ARG1+96 + 1];
    SCE->REG_100H = S_FLASH[ARG1+96 + 2];
    SCE->REG_100H = S_FLASH[ARG1+96 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000009dU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+100 + 0];
    SCE->REG_100H = S_FLASH[ARG1+100 + 1];
    SCE->REG_100H = S_FLASH[ARG1+100 + 2];
    SCE->REG_100H = S_FLASH[ARG1+100 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+104 + 0];
    SCE->REG_100H = S_FLASH[ARG1+104 + 1];
    SCE->REG_100H = S_FLASH[ARG1+104 + 2];
    SCE->REG_100H = S_FLASH[ARG1+104 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+108 + 0];
    SCE->REG_100H = S_FLASH[ARG1+108 + 1];
    SCE->REG_100H = S_FLASH[ARG1+108 + 2];
    SCE->REG_100H = S_FLASH[ARG1+108 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+112 + 0];
    SCE->REG_100H = S_FLASH[ARG1+112 + 1];
    SCE->REG_100H = S_FLASH[ARG1+112 + 2];
    SCE->REG_100H = S_FLASH[ARG1+112 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000001aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_C4H = 0x000007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+116 + 0];
    SCE->REG_100H = S_FLASH[ARG1+116 + 1];
    SCE->REG_100H = S_FLASH[ARG1+116 + 2];
    SCE->REG_100H = S_FLASH[ARG1+116 + 3];
    SCE->REG_C4H = 0x00800c45U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_func070.prc
***********************************************************************************************************************/
