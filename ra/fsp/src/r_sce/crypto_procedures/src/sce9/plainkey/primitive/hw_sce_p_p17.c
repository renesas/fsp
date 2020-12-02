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

fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub(uint32_t *OutData_KeyIndex)
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
    if (0x0u != (SCE->REG_1BCH & 0x1fu))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00001702u;
    SCE->REG_108H = 0x00000000u;
    HW_SCE_p_func100(0x737bb4a5u, 0xbff6a348u, 0xaeb16686u, 0xe2d29c1au);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_E0H = 0x80010000u;
    SCE->REG_00H = 0x00008207u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000020fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x000034e0u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000017u);
    HW_SCE_p_func101(0x4815a41cu, 0x00916820u, 0xbe01c103u, 0x1dec006au);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x00000009u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000017u);
    HW_SCE_p_func101(0xd842bfd1u, 0xd2970d65u, 0xbc2702f7u, 0x02db49feu);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0xf7d92364u, 0x5552bf8au, 0x97e251cdu, 0xecbc6a8cu);
    SCE->REG_E0H = 0x81010000u;
    SCE->REG_04H = 0x00000606u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[0] = SCE->REG_100H;
    HW_SCE_p_func100(0x9393aedfu, 0x0a40b1f7u, 0x05756c3au, 0x1b56ba0cu);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_E0H = 0x80100000u;
    SCE->REG_00H = 0x00008213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0xac85b8abu, 0xee4cd758u, 0xa30bc79du, 0x400754d0u);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x00008213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x72864ca0u, 0xa02a9463u, 0x51458194u, 0x25480ca7u);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x00008213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0xca854ddfu, 0x013d0d2bu, 0xbae6953fu, 0x203b2168u);
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x00008213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x98a0b10bu, 0xbc9e675fu, 0xc7c22bccu, 0xc608476eu);
    SCE->REG_D0H = 0x40000300u;
    SCE->REG_C4H = 0x02e487b7u;
    SCE->REG_E0H = 0x81100000u;
    SCE->REG_00H = 0x00002843u;
    SCE->REG_04H = 0x00000242u;
    for(iLoop=1; iLoop<17; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
        OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
    }
    HW_SCE_p_func100(0x6d2f16f6u, 0xa21672b3u, 0x54a9986cu, 0xb2894ec7u);
    SCE->REG_104H = 0x00000352u;
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x000089c5u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000004u);
    SCE->REG_04H = 0x00000212u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[iLoop + 0] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 1] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 2] = SCE->REG_100H;
    OutData_KeyIndex[iLoop + 3] = SCE->REG_100H;
    HW_SCE_p_func102(0xe907d5eeu, 0x06fc1a87u, 0x4695e21du, 0x9b334c1du);
    SCE->REG_1BCH = 0x00000040u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p17_r1.prc
***********************************************************************************************************************/
