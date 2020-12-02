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

fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub(uint32_t *InData_Text, uint32_t *InData_TextLen, uint32_t *InData_MAC, uint32_t *InData_MACLength, uint32_t *OutData_Text)
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
    HW_SCE_p_func100(0x1947bce2u, 0xb6dd8cefu, 0x72f49a52u, 0xaf05502eu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x7c1b7ea3u, 0xf18dfaa8u, 0xe8780c1fu, 0x9959f912u);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_104H = 0x00000068u;
        SCE->REG_E0H = 0x80010140u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MACLength[0];
        SCE->REG_ECH = 0x38008940u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        SCE->REG_ECH = 0x0000b7e0u;
        SCE->REG_ECH = 0x00000010u;
        SCE->REG_ECH = 0x34202beau;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0xb2cb41d9u, 0x8f1c5bc0u, 0x95ce1a2au, 0x5b1f71d8u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x6ea3e4f6u, 0xd9b8445fu, 0xa3c85ad4u, 0x274f912au);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_104H = 0x00000068u;
            SCE->REG_E0H = 0x80010000u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_TextLen[0];
            SCE->REG_ECH = 0x00008c00u;
            SCE->REG_ECH = 0x0000000fu;
            SCE->REG_ECH = 0x38008800u;
            SCE->REG_ECH = 0x00000000u;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00A60000u;
            HW_SCE_p_func100(0x4d69888du, 0x907ce4c9u, 0xec2167c2u, 0xb4887c76u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000361u;
                SCE->REG_B0H = 0x40000000u;
                SCE->REG_A4H = 0x000087b5u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[0];
                SCE->REG_100H = InData_Text[1];
                SCE->REG_100H = InData_Text[2];
                SCE->REG_100H = InData_Text[3];
                SCE->REG_ECH = 0x0000b420u;
                SCE->REG_ECH = 0x00000080u;
                SCE->REG_E0H = 0x80840001u;
                SCE->REG_00H = 0x00008113u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x00000821u;
                SCE->REG_ECH = 0x0000a400u;
                SCE->REG_ECH = 0x00000080u;
                SCE->REG_ECH = 0x0000b7e0u;
                SCE->REG_ECH = 0x00000080u;
                for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3c002be0u;
                    SCE->REG_ECH = 0x12003c3fu;
                    SCE->REG_ECH = 0x00002fe0u;
                }
                HW_SCE_p_func100(0xe0008a61u, 0xaf3a2505u, 0x1b72c8feu, 0x4cda0270u);
                SCE->REG_ECH = 0x0000b420u;
                SCE->REG_ECH = 0x00000080u;
                SCE->REG_E0H = 0x81840001u;
                SCE->REG_04H = 0x00000613u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[1] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[2] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[3] = SCE->REG_100H;
                SCE->REG_B0H = 0x40000000u;
                SCE->REG_A4H = 0x00008e55u;
                SCE->REG_E0H = 0x81840001u;
                SCE->REG_00H = 0x00001813u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                HW_SCE_p_func101(0xb2c1c419u, 0x2daab86du, 0xb3644f3eu, 0x7dcb2c5bu);
            }
            else
            {
                HW_SCE_p_func101(0x18194dc3u, 0x55159f50u, 0x743daa12u, 0x7361ff72u);
            }
            SCE->REG_104H = 0x00000051u;
            SCE->REG_A4H = 0x00000cc4u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_B0H = 0x40000000u;
            SCE->REG_A4H = 0x010087b5u;
            SCE->REG_00H = 0x00001113u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000b420u;
            SCE->REG_ECH = 0x00000080u;
            SCE->REG_E0H = 0x80840001u;
            SCE->REG_00H = 0x00008113u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x0000a540u;
            SCE->REG_ECH = 0x00000080u;
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000080u;
            SCE->REG_ECH = 0x00000821u;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
            {
                SCE->REG_ECH = 0x3c002beau;
                SCE->REG_ECH = 0x12003c3fu;
                SCE->REG_ECH = 0x00002fe0u;
            }
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00050805u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_MAC[0];
            SCE->REG_100H = InData_MAC[1];
            SCE->REG_100H = InData_MAC[2];
            SCE->REG_100H = InData_MAC[3];
            SCE->REG_A4H = 0x00900c45u;
            SCE->REG_ECH = 0x0000b420u;
            SCE->REG_ECH = 0x00000080u;
            SCE->REG_E0H = 0x81840001u;
            SCE->REG_00H = 0x00001813u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_A4H = 0x00000000u;
            HW_SCE_p_func100(0x26a02e05u, 0x2e0d7c97u, 0x5a42f7e8u, 0xc9307893u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x439cff70u, 0x32634fd1u, 0x3f0a3267u, 0xe61861f1u);
                SCE->REG_1BCH = 0x00000040u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func102(0xa19bacb9u, 0x31b73ae7u, 0x93a90fb2u, 0x617899fcu);
                SCE->REG_1BCH = 0x00000040u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_SUCCESS;
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pa4f.prc
***********************************************************************************************************************/
