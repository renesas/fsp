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

fsp_err_t HW_SCE_Aes256CmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_Text, uint32_t *InData_DataT, uint32_t *InData_DataTLen, uint32_t *OutData_DataT)
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
    HW_SCE_p_func100(0xf12ceb80u, 0xd9c1ad15u, 0xf0601e59u, 0xebbb0fa5u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xda00fcb8u, 0xa57aaf1bu, 0x95160be9u, 0x895676beu);
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
        if ((InData_Cmd[0] == 0x00000000) || (InData_Cmd[0] == 0x00000002))
        {
            SCE->REG_104H = 0x00000051u;
            SCE->REG_B0H = 0x40000000u;
            SCE->REG_A4H = 0x00408a84u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            HW_SCE_p_func101(0x12a5767bu, 0x9b238f34u, 0x03fc5a80u, 0xe1114431u);
        }
        else
        {
            SCE->REG_104H = 0x00000051u;
            SCE->REG_B0H = 0x40000000u;
            SCE->REG_A4H = 0x00508a84u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            HW_SCE_p_func101(0x105cc13cu, 0xe11d8e1eu, 0x624ffeabu, 0xb00e22f8u);
        }
        SCE->REG_A4H = 0x00040c05u;
        SCE->REG_00H = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        if ((InData_Cmd[0] == 0x00000000) || (InData_Cmd[0] == 0x00000001))
        {
            HW_SCE_p_func100(0xab3f8b13u, 0x24985a75u, 0x9d898c5eu, 0x5378c4b9u);
            SCE->REG_104H = 0x00000361u;
            SCE->REG_B0H = 0x40000000u;
            SCE->REG_A4H = 0x00008e95u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_04H = 0x00000113u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_DataT[0] = SCE->REG_100H;
            OutData_DataT[1] = SCE->REG_100H;
            OutData_DataT[2] = SCE->REG_100H;
            OutData_DataT[3] = SCE->REG_100H;
            HW_SCE_p_func102(0xd572dcd4u, 0xdc606567u, 0x854156cau, 0x4c0d8e84u);
            SCE->REG_1BCH = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
        else
        {
            SCE->REG_104H = 0x00000068u;
            SCE->REG_E0H = 0x80010040u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_DataTLen[0];
            SCE->REG_ECH = 0x3420a840u;
            SCE->REG_ECH = 0x00000010u;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00260000u;
            SCE->REG_ECH = 0x0000b460u;
            SCE->REG_ECH = 0x00000080u;
            SCE->REG_ECH = 0x34202862u;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00260000u;
            HW_SCE_p_func100(0x2d0117a5u, 0x824ffaadu, 0xdc4caf16u, 0x2cc10babu);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xd84af4b1u, 0x556cb646u, 0xbc9c491bu, 0x55808f8du);
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
                SCE->REG_104H = 0x00000361u;
                SCE->REG_B0H = 0x40000000u;
                SCE->REG_A4H = 0x00008e95u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[0];
                SCE->REG_100H = InData_Text[1];
                SCE->REG_100H = InData_Text[2];
                SCE->REG_100H = InData_Text[3];
                SCE->REG_ECH = 0x00000821u;
                SCE->REG_E0H = 0x80840001u;
                SCE->REG_00H = 0x00008113u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x000034e2u;
                SCE->REG_ECH = 0x000568e7u;
                SCE->REG_ECH = 0x00026ce7u;
                SCE->REG_ECH = 0x00003827u;
                SCE->REG_ECH = 0x0000b4c0u;
                SCE->REG_ECH = 0x00000020u;
                SCE->REG_ECH = 0x00003402u;
                SCE->REG_ECH = 0x00008c00u;
                SCE->REG_ECH = 0x0000001fu;
                SCE->REG_ECH = 0x000028c0u;
                SCE->REG_ECH = 0x00008cc0u;
                SCE->REG_ECH = 0x0000001fu;
                SCE->REG_ECH = 0x00004406u;
                SCE->REG_ECH = 0x00007421u;
                SCE->REG_ECH = 0x00007821u;
                SCE->REG_ECH = 0x00003c27u;
                SCE->REG_ECH = 0x000034c2u;
                SCE->REG_ECH = 0x0000a4c0u;
                SCE->REG_ECH = 0x0000001fu;
                SCE->REG_ECH = 0x000568c6u;
                SCE->REG_ECH = 0x000034e6u;
                SCE->REG_ECH = 0x00026ce7u;
                SCE->REG_ECH = 0x00000821u;
                for (iLoop = 0; iLoop < 4; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3420a8e0u;
                    SCE->REG_ECH = 0x0000000du;
                    SCE->REG_ECH = 0x10003c27u;
                    SCE->REG_ECH = 0x1000a4e0u;
                    SCE->REG_ECH = 0x00000004u;
                }
                SCE->REG_A4H = 0x00040805u;
                SCE->REG_E0H = 0x81840001u;
                SCE->REG_00H = 0x00001813u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_104H = 0x00000361u;
                SCE->REG_A4H = 0x00900c05u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_DataT[0];
                SCE->REG_100H = InData_DataT[1];
                SCE->REG_100H = InData_DataT[2];
                SCE->REG_100H = InData_DataT[3];
                HW_SCE_p_func100(0x5213259fu, 0xa67e25cdu, 0x3200d319u, 0x0cf582a1u);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (1u == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x3e4ea75bu, 0x922e715bu, 0x60bb4b70u, 0x7cddda01u);
                    SCE->REG_1BCH = 0x00000040u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_18H_b.B12)
                    {
                        /* waiting */
                    }
                    return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
                }
                else
                {
                    HW_SCE_p_func102(0xa03574e2u, 0xb7c3a1c9u, 0x6c50faf9u, 0x2a69090cu);
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
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p44f.prc
***********************************************************************************************************************/
