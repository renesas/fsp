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

void HW_SCE_p_func025_r1(uint32_t ARG1)
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
    SCE->REG_ECH = 0x01001d9dU;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0107c0e5U;
    SCE->REG_ECH = 0x00070040U;
    SCE->REG_ECH = 0x30003380U;
    SCE->REG_ECH = 0x00070020U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x1f8473b6U;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x32ab9622U;
    SCE->REG_ECH = 0x00050040U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x5d38e816U;
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
    SCE->REG_100H = S_FLASH[ARG1+120 + 0];
    SCE->REG_100H = S_FLASH[ARG1+120 + 1];
    SCE->REG_100H = S_FLASH[ARG1+120 + 2];
    SCE->REG_100H = S_FLASH[ARG1+120 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+124 + 0];
    SCE->REG_100H = S_FLASH[ARG1+124 + 1];
    SCE->REG_100H = S_FLASH[ARG1+124 + 2];
    SCE->REG_100H = S_FLASH[ARG1+124 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000104U;
    SCE->REG_24H = 0x800011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+128 + 0];
    SCE->REG_100H = S_FLASH[ARG1+128 + 1];
    SCE->REG_100H = S_FLASH[ARG1+128 + 2];
    SCE->REG_100H = S_FLASH[ARG1+128 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+132 + 0];
    SCE->REG_100H = S_FLASH[ARG1+132 + 1];
    SCE->REG_100H = S_FLASH[ARG1+132 + 2];
    SCE->REG_100H = S_FLASH[ARG1+132 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000018U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000108U;
    SCE->REG_24H = 0x800012c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+136 + 0];
    SCE->REG_100H = S_FLASH[ARG1+136 + 1];
    SCE->REG_100H = S_FLASH[ARG1+136 + 2];
    SCE->REG_100H = S_FLASH[ARG1+136 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+140 + 0];
    SCE->REG_100H = S_FLASH[ARG1+140 + 1];
    SCE->REG_100H = S_FLASH[ARG1+140 + 2];
    SCE->REG_100H = S_FLASH[ARG1+140 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000091U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000304U;
    SCE->REG_24H = 0x800015c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+144 + 0];
    SCE->REG_100H = S_FLASH[ARG1+144 + 1];
    SCE->REG_100H = S_FLASH[ARG1+144 + 2];
    SCE->REG_100H = S_FLASH[ARG1+144 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+148 + 0];
    SCE->REG_100H = S_FLASH[ARG1+148 + 1];
    SCE->REG_100H = S_FLASH[ARG1+148 + 2];
    SCE->REG_100H = S_FLASH[ARG1+148 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000019U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000308U;
    SCE->REG_24H = 0x800016c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+152 + 0];
    SCE->REG_100H = S_FLASH[ARG1+152 + 1];
    SCE->REG_100H = S_FLASH[ARG1+152 + 2];
    SCE->REG_100H = S_FLASH[ARG1+152 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+156 + 0];
    SCE->REG_100H = S_FLASH[ARG1+156 + 1];
    SCE->REG_100H = S_FLASH[ARG1+156 + 2];
    SCE->REG_100H = S_FLASH[ARG1+156 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000092U;
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
    SCE->REG_100H = S_FLASH[ARG1+160 + 0];
    SCE->REG_100H = S_FLASH[ARG1+160 + 1];
    SCE->REG_100H = S_FLASH[ARG1+160 + 2];
    SCE->REG_100H = S_FLASH[ARG1+160 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+164 + 0];
    SCE->REG_100H = S_FLASH[ARG1+164 + 1];
    SCE->REG_100H = S_FLASH[ARG1+164 + 2];
    SCE->REG_100H = S_FLASH[ARG1+164 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x00000093U;
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
    SCE->REG_100H = S_FLASH[ARG1+168 + 0];
    SCE->REG_100H = S_FLASH[ARG1+168 + 1];
    SCE->REG_100H = S_FLASH[ARG1+168 + 2];
    SCE->REG_100H = S_FLASH[ARG1+168 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+172 + 0];
    SCE->REG_100H = S_FLASH[ARG1+172 + 1];
    SCE->REG_100H = S_FLASH[ARG1+172 + 2];
    SCE->REG_100H = S_FLASH[ARG1+172 + 3];
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
    SCE->REG_100H = S_FLASH[ARG1+176 + 0];
    SCE->REG_100H = S_FLASH[ARG1+176 + 1];
    SCE->REG_100H = S_FLASH[ARG1+176 + 2];
    SCE->REG_100H = S_FLASH[ARG1+176 + 3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+180 + 0];
    SCE->REG_100H = S_FLASH[ARG1+180 + 1];
    SCE->REG_100H = S_FLASH[ARG1+180 + 2];
    SCE->REG_100H = S_FLASH[ARG1+180 + 3];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000009bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000362U;
    SCE->REG_C4H = 0x000007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH[ARG1+184 + 0];
    SCE->REG_100H = S_FLASH[ARG1+184 + 1];
    SCE->REG_100H = S_FLASH[ARG1+184 + 2];
    SCE->REG_100H = S_FLASH[ARG1+184 + 3];
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_func025_r1.prc
***********************************************************************************************************************/
