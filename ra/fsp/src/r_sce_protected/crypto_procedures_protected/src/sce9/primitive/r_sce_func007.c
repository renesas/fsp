/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED  AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 05.10.2020 1.00        First Release.
 *         : 02.12.2020 1.01        Added new functions such as the Brainpool curve.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_sce.h"
#include "r_sce_private.h"

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

void R_SCE_func007(void)
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
    SCE->REG_100H = S_HEAP[0];
    SCE->REG_100H = S_HEAP[1];
    SCE->REG_100H = S_HEAP[2];
    SCE->REG_100H = S_HEAP[3];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[4];
    SCE->REG_100H = S_HEAP[5];
    SCE->REG_100H = S_HEAP[6];
    SCE->REG_100H = S_HEAP[7];
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
    SCE->REG_100H = S_HEAP[8];
    SCE->REG_100H = S_HEAP[9];
    SCE->REG_100H = S_HEAP[10];
    SCE->REG_100H = S_HEAP[11];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[12];
    SCE->REG_100H = S_HEAP[13];
    SCE->REG_100H = S_HEAP[14];
    SCE->REG_100H = S_HEAP[15];
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
    SCE->REG_100H = S_HEAP[16];
    SCE->REG_100H = S_HEAP[17];
    SCE->REG_100H = S_HEAP[18];
    SCE->REG_100H = S_HEAP[19];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[20];
    SCE->REG_100H = S_HEAP[21];
    SCE->REG_100H = S_HEAP[22];
    SCE->REG_100H = S_HEAP[23];
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
    SCE->REG_100H = S_HEAP[24];
    SCE->REG_100H = S_HEAP[25];
    SCE->REG_100H = S_HEAP[26];
    SCE->REG_100H = S_HEAP[27];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[28];
    SCE->REG_100H = S_HEAP[29];
    SCE->REG_100H = S_HEAP[30];
    SCE->REG_100H = S_HEAP[31];
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
    SCE->REG_100H = S_HEAP[32];
    SCE->REG_100H = S_HEAP[33];
    SCE->REG_100H = S_HEAP[34];
    SCE->REG_100H = S_HEAP[35];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[36];
    SCE->REG_100H = S_HEAP[37];
    SCE->REG_100H = S_HEAP[38];
    SCE->REG_100H = S_HEAP[39];
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
    SCE->REG_100H = S_HEAP[40];
    SCE->REG_100H = S_HEAP[41];
    SCE->REG_100H = S_HEAP[42];
    SCE->REG_100H = S_HEAP[43];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[44];
    SCE->REG_100H = S_HEAP[45];
    SCE->REG_100H = S_HEAP[46];
    SCE->REG_100H = S_HEAP[47];
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
    SCE->REG_100H = S_HEAP[48];
    SCE->REG_100H = S_HEAP[49];
    SCE->REG_100H = S_HEAP[50];
    SCE->REG_100H = S_HEAP[51];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[52];
    SCE->REG_100H = S_HEAP[53];
    SCE->REG_100H = S_HEAP[54];
    SCE->REG_100H = S_HEAP[55];
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
    SCE->REG_100H = S_HEAP[56];
    SCE->REG_100H = S_HEAP[57];
    SCE->REG_100H = S_HEAP[58];
    SCE->REG_100H = S_HEAP[59];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[60];
    SCE->REG_100H = S_HEAP[61];
    SCE->REG_100H = S_HEAP[62];
    SCE->REG_100H = S_HEAP[63];
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
    SCE->REG_100H = S_HEAP[64];
    SCE->REG_100H = S_HEAP[65];
    SCE->REG_100H = S_HEAP[66];
    SCE->REG_100H = S_HEAP[67];
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func007.prc
***********************************************************************************************************************/
