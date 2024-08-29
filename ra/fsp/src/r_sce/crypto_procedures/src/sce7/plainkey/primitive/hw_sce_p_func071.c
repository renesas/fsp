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

void HW_SCE_p_func071(uint32_t ARG1)
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
    SCE->REG_ECH = 0x017d423aU;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0163c737U;
    SCE->REG_ECH = 0x00070040U;
    SCE->REG_ECH = 0x30003380U;
    SCE->REG_ECH = 0x00070020U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0xd07c67d8U;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0xcf26ddb5U;
    SCE->REG_ECH = 0x00050040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x5abcfa36U;
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
    SCE->REG_104H = 0x00003f62U;
    SCE->REG_D0H = 0x00000f00U;
    SCE->REG_C4H = 0x02f087bfU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[0+ARG1 + 0];
    SCE->REG_100H = S_FLASH[0+ARG1 + 1];
    SCE->REG_100H = S_FLASH[0+ARG1 + 2];
    SCE->REG_100H = S_FLASH[0+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[4+ARG1 + 0];
    SCE->REG_100H = S_FLASH[4+ARG1 + 1];
    SCE->REG_100H = S_FLASH[4+ARG1 + 2];
    SCE->REG_100H = S_FLASH[4+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000001aU;
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
    SCE->REG_100H = S_FLASH[8+ARG1 + 0];
    SCE->REG_100H = S_FLASH[8+ARG1 + 1];
    SCE->REG_100H = S_FLASH[8+ARG1 + 2];
    SCE->REG_100H = S_FLASH[8+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[12+ARG1 + 0];
    SCE->REG_100H = S_FLASH[12+ARG1 + 1];
    SCE->REG_100H = S_FLASH[12+ARG1 + 2];
    SCE->REG_100H = S_FLASH[12+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000001bU;
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
    SCE->REG_100H = S_FLASH[16+ARG1 + 0];
    SCE->REG_100H = S_FLASH[16+ARG1 + 1];
    SCE->REG_100H = S_FLASH[16+ARG1 + 2];
    SCE->REG_100H = S_FLASH[16+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[20+ARG1 + 0];
    SCE->REG_100H = S_FLASH[20+ARG1 + 1];
    SCE->REG_100H = S_FLASH[20+ARG1 + 2];
    SCE->REG_100H = S_FLASH[20+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000098U;
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
    SCE->REG_100H = S_FLASH[24+ARG1 + 0];
    SCE->REG_100H = S_FLASH[24+ARG1 + 1];
    SCE->REG_100H = S_FLASH[24+ARG1 + 2];
    SCE->REG_100H = S_FLASH[24+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[28+ARG1 + 0];
    SCE->REG_100H = S_FLASH[28+ARG1 + 1];
    SCE->REG_100H = S_FLASH[28+ARG1 + 2];
    SCE->REG_100H = S_FLASH[28+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000099U;
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
    SCE->REG_100H = S_FLASH[32+ARG1 + 0];
    SCE->REG_100H = S_FLASH[32+ARG1 + 1];
    SCE->REG_100H = S_FLASH[32+ARG1 + 2];
    SCE->REG_100H = S_FLASH[32+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[36+ARG1 + 0];
    SCE->REG_100H = S_FLASH[36+ARG1 + 1];
    SCE->REG_100H = S_FLASH[36+ARG1 + 2];
    SCE->REG_100H = S_FLASH[36+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000094U;
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
    SCE->REG_100H = S_FLASH[40+ARG1 + 0];
    SCE->REG_100H = S_FLASH[40+ARG1 + 1];
    SCE->REG_100H = S_FLASH[40+ARG1 + 2];
    SCE->REG_100H = S_FLASH[40+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[44+ARG1 + 0];
    SCE->REG_100H = S_FLASH[44+ARG1 + 1];
    SCE->REG_100H = S_FLASH[44+ARG1 + 2];
    SCE->REG_100H = S_FLASH[44+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000095U;
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
    SCE->REG_100H = S_FLASH[48+ARG1 + 0];
    SCE->REG_100H = S_FLASH[48+ARG1 + 1];
    SCE->REG_100H = S_FLASH[48+ARG1 + 2];
    SCE->REG_100H = S_FLASH[48+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[52+ARG1 + 0];
    SCE->REG_100H = S_FLASH[52+ARG1 + 1];
    SCE->REG_100H = S_FLASH[52+ARG1 + 2];
    SCE->REG_100H = S_FLASH[52+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000009cU;
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
    SCE->REG_100H = S_FLASH[56+ARG1 + 0];
    SCE->REG_100H = S_FLASH[56+ARG1 + 1];
    SCE->REG_100H = S_FLASH[56+ARG1 + 2];
    SCE->REG_100H = S_FLASH[56+ARG1 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[60+ARG1 + 0];
    SCE->REG_100H = S_FLASH[60+ARG1 + 1];
    SCE->REG_100H = S_FLASH[60+ARG1 + 2];
    SCE->REG_100H = S_FLASH[60+ARG1 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000009dU;
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
    SCE->REG_100H = S_FLASH[64+ARG1 + 0];
    SCE->REG_100H = S_FLASH[64+ARG1 + 1];
    SCE->REG_100H = S_FLASH[64+ARG1 + 2];
    SCE->REG_100H = S_FLASH[64+ARG1 + 3];
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_func071.prc
***********************************************************************************************************************/
