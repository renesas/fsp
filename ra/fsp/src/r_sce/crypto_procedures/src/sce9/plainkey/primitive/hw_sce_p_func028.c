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

void HW_SCE_p_func028_r2(uint32_t ARG1)
{
    uint32_t iLoop = 0u, iLoop1 = 0u, iLoop2 = 0u, jLoop = 0u, kLoop = 0u, oLoop = 0u, oLoop1 = 0u, oLoop2 = 0u, KEY_ADR = 0u, OFS_ADR = 0u, MAX_CNT2 = 0u;
    uint32_t dummy = 0u;
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
    SCE->REG_ECH = 0x38000f5au;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x01166403u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x013659ffu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_C4H = 0x00443a0cu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_C4H = 0x000c3e1cu;
    SCE->REG_E0H = 0x810103c0u;
    SCE->REG_00H = 0x00002807u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00001762u;
    SCE->REG_D0H = 0x00000500u;
    SCE->REG_C4H = 0x02f087bfu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+0 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+0 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+0 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+0 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+4 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+4 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+4 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+4 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+8 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+8 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+8 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+8 + 3];
    SCE->REG_00H = 0x00003233u;
    SCE->REG_2CH = 0x0000001au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+12 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+12 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+12 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+12 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+16 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+16 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+16 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+16 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+20 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+20 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+20 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+20 + 3];
    SCE->REG_00H = 0x00003233u;
    SCE->REG_2CH = 0x0000001bu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_C4H = 0x000007bdu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+24 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+24 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+24 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+24 + 3];
    SCE->REG_C4H = 0x00800c45u;
    SCE->REG_00H = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func028_r2.prc
***********************************************************************************************************************/
