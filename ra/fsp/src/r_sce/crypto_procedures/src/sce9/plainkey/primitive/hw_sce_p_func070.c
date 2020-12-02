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

void HW_SCE_p_func070_r2(uint32_t ARG1)
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
    SCE->REG_ECH = 0x30003340u;
    SCE->REG_ECH = 0x00050020u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0131ec45u;
    SCE->REG_ECH = 0x00030040u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x014bb610u;
    SCE->REG_ECH = 0x00070040u;
    SCE->REG_ECH = 0x30003380u;
    SCE->REG_ECH = 0x00070020u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x01542614u;
    SCE->REG_ECH = 0x00030040u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x01ba24feu;
    SCE->REG_ECH = 0x00050040u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x01bb59d6u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_28H = 0x00870001u;
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
    SCE->REG_104H = 0x00002f62u;
    SCE->REG_D0H = 0x00000b00u;
    SCE->REG_C4H = 0x02f087bfu;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+68 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+68 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+68 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+68 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+72 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+72 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+72 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+72 + 3];
    SCE->REG_00H = 0x00003223u;
    SCE->REG_2CH = 0x00000015u;
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
    SCE->REG_100H = S_FLASH2[ARG1+76 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+76 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+76 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+76 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+80 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+80 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+80 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+80 + 3];
    SCE->REG_00H = 0x00003223u;
    SCE->REG_2CH = 0x0000009au;
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
    SCE->REG_100H = S_FLASH2[ARG1+84 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+84 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+84 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+84 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+88 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+88 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+88 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+88 + 3];
    SCE->REG_00H = 0x00003223u;
    SCE->REG_2CH = 0x0000001du;
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
    SCE->REG_100H = S_FLASH2[ARG1+92 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+92 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+92 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+92 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+96 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+96 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+96 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+96 + 3];
    SCE->REG_00H = 0x00003223u;
    SCE->REG_2CH = 0x0000009du;
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
    SCE->REG_100H = S_FLASH2[ARG1+100 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+100 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+100 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+100 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+104 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+104 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+104 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+104 + 3];
    SCE->REG_00H = 0x00003223u;
    SCE->REG_2CH = 0x00000014u;
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
    SCE->REG_100H = S_FLASH2[ARG1+108 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+108 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+108 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+108 + 3];
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_FLASH2[ARG1+112 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+112 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+112 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+112 + 3];
    SCE->REG_00H = 0x00003223u;
    SCE->REG_2CH = 0x0000001au;
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
    SCE->REG_100H = S_FLASH2[ARG1+116 + 0];
    SCE->REG_100H = S_FLASH2[ARG1+116 + 1];
    SCE->REG_100H = S_FLASH2[ARG1+116 + 2];
    SCE->REG_100H = S_FLASH2[ARG1+116 + 3];
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func070_r2.prc
***********************************************************************************************************************/
