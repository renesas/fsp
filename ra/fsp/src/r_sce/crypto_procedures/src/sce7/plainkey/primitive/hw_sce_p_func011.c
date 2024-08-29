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

void HW_SCE_p_func011(uint32_t* ARG1)
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
    SCE->REG_104H = 0x00003f62U;
    SCE->REG_D0H = 0x00000f00U;
    SCE->REG_C4H = 0x42f087bfU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[0];
    SCE->REG_100H = ARG1[1];
    SCE->REG_100H = ARG1[2];
    SCE->REG_100H = ARG1[3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[4];
    SCE->REG_100H = ARG1[5];
    SCE->REG_100H = ARG1[6];
    SCE->REG_100H = ARG1[7];
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
    SCE->REG_100H = ARG1[8];
    SCE->REG_100H = ARG1[9];
    SCE->REG_100H = ARG1[10];
    SCE->REG_100H = ARG1[11];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[12];
    SCE->REG_100H = ARG1[13];
    SCE->REG_100H = ARG1[14];
    SCE->REG_100H = ARG1[15];
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
    SCE->REG_100H = ARG1[16];
    SCE->REG_100H = ARG1[17];
    SCE->REG_100H = ARG1[18];
    SCE->REG_100H = ARG1[19];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[20];
    SCE->REG_100H = ARG1[21];
    SCE->REG_100H = ARG1[22];
    SCE->REG_100H = ARG1[23];
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
    SCE->REG_100H = ARG1[24];
    SCE->REG_100H = ARG1[25];
    SCE->REG_100H = ARG1[26];
    SCE->REG_100H = ARG1[27];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[28];
    SCE->REG_100H = ARG1[29];
    SCE->REG_100H = ARG1[30];
    SCE->REG_100H = ARG1[31];
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
    SCE->REG_100H = ARG1[32];
    SCE->REG_100H = ARG1[33];
    SCE->REG_100H = ARG1[34];
    SCE->REG_100H = ARG1[35];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[36];
    SCE->REG_100H = ARG1[37];
    SCE->REG_100H = ARG1[38];
    SCE->REG_100H = ARG1[39];
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
    SCE->REG_100H = ARG1[40];
    SCE->REG_100H = ARG1[41];
    SCE->REG_100H = ARG1[42];
    SCE->REG_100H = ARG1[43];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[44];
    SCE->REG_100H = ARG1[45];
    SCE->REG_100H = ARG1[46];
    SCE->REG_100H = ARG1[47];
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
    SCE->REG_100H = ARG1[48];
    SCE->REG_100H = ARG1[49];
    SCE->REG_100H = ARG1[50];
    SCE->REG_100H = ARG1[51];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[52];
    SCE->REG_100H = ARG1[53];
    SCE->REG_100H = ARG1[54];
    SCE->REG_100H = ARG1[55];
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
    SCE->REG_100H = ARG1[56];
    SCE->REG_100H = ARG1[57];
    SCE->REG_100H = ARG1[58];
    SCE->REG_100H = ARG1[59];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[60];
    SCE->REG_100H = ARG1[61];
    SCE->REG_100H = ARG1[62];
    SCE->REG_100H = ARG1[63];
    SCE->REG_00H = 0x00003223U;
    SCE->REG_2CH = 0x0000009bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_C4H = 0x400007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[64];
    SCE->REG_100H = ARG1[65];
    SCE->REG_100H = ARG1[66];
    SCE->REG_100H = ARG1[67];
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_func011.prc
***********************************************************************************************************************/
