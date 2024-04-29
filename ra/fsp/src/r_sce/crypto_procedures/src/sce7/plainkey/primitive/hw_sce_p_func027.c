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

void HW_SCE_p_func027_r1(uint32_t ARG1)
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
    SCE->REG_ECH = 0x38000f5aU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0xc1305c44U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0142859dU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_C4H = 0x000c3b0cU;
    SCE->REG_E0H = 0x810103c0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00003b62U;
    SCE->REG_D0H = 0x00000e00U;
    SCE->REG_C4H = 0x02f087bfU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+28 + 0];
    SCE->REG_100H = S_FLASH[ARG1+28 + 1];
    SCE->REG_100H = S_FLASH[ARG1+28 + 2];
    SCE->REG_100H = S_FLASH[ARG1+28 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+32 + 0];
    SCE->REG_100H = S_FLASH[ARG1+32 + 1];
    SCE->REG_100H = S_FLASH[ARG1+32 + 2];
    SCE->REG_100H = S_FLASH[ARG1+32 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+36 + 0];
    SCE->REG_100H = S_FLASH[ARG1+36 + 1];
    SCE->REG_100H = S_FLASH[ARG1+36 + 2];
    SCE->REG_100H = S_FLASH[ARG1+36 + 3];
    SCE->REG_00H = 0x00003233U;
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
    SCE->REG_100H = S_FLASH[ARG1+40 + 0];
    SCE->REG_100H = S_FLASH[ARG1+40 + 1];
    SCE->REG_100H = S_FLASH[ARG1+40 + 2];
    SCE->REG_100H = S_FLASH[ARG1+40 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+44 + 0];
    SCE->REG_100H = S_FLASH[ARG1+44 + 1];
    SCE->REG_100H = S_FLASH[ARG1+44 + 2];
    SCE->REG_100H = S_FLASH[ARG1+44 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+48 + 0];
    SCE->REG_100H = S_FLASH[ARG1+48 + 1];
    SCE->REG_100H = S_FLASH[ARG1+48 + 2];
    SCE->REG_100H = S_FLASH[ARG1+48 + 3];
    SCE->REG_00H = 0x00003233U;
    SCE->REG_2CH = 0x00000013U;
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
    SCE->REG_100H = S_FLASH[ARG1+52 + 0];
    SCE->REG_100H = S_FLASH[ARG1+52 + 1];
    SCE->REG_100H = S_FLASH[ARG1+52 + 2];
    SCE->REG_100H = S_FLASH[ARG1+52 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+56 + 0];
    SCE->REG_100H = S_FLASH[ARG1+56 + 1];
    SCE->REG_100H = S_FLASH[ARG1+56 + 2];
    SCE->REG_100H = S_FLASH[ARG1+56 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+60 + 0];
    SCE->REG_100H = S_FLASH[ARG1+60 + 1];
    SCE->REG_100H = S_FLASH[ARG1+60 + 2];
    SCE->REG_100H = S_FLASH[ARG1+60 + 3];
    SCE->REG_00H = 0x00003233U;
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
    SCE->REG_100H = S_FLASH[ARG1+64 + 0];
    SCE->REG_100H = S_FLASH[ARG1+64 + 1];
    SCE->REG_100H = S_FLASH[ARG1+64 + 2];
    SCE->REG_100H = S_FLASH[ARG1+64 + 3];
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
    SCE->REG_00H = 0x00003233U;
    SCE->REG_2CH = 0x0000001cU;
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
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+84 + 0];
    SCE->REG_100H = S_FLASH[ARG1+84 + 1];
    SCE->REG_100H = S_FLASH[ARG1+84 + 2];
    SCE->REG_100H = S_FLASH[ARG1+84 + 3];
    SCE->REG_00H = 0x00003233U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000b62U;
    SCE->REG_D0H = 0x00000200U;
    SCE->REG_C4H = 0x00f087bfU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+88 + 0];
    SCE->REG_100H = S_FLASH[ARG1+88 + 1];
    SCE->REG_100H = S_FLASH[ARG1+88 + 2];
    SCE->REG_100H = S_FLASH[ARG1+88 + 3];
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
    SCE->REG_00H = 0x00003233U;
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
    SCE->REG_100H = S_FLASH[ARG1+100 + 0];
    SCE->REG_100H = S_FLASH[ARG1+100 + 1];
    SCE->REG_100H = S_FLASH[ARG1+100 + 2];
    SCE->REG_100H = S_FLASH[ARG1+100 + 3];
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_func027_r1.prc
***********************************************************************************************************************/
