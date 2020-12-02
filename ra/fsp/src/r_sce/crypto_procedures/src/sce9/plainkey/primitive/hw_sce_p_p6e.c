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

fsp_err_t HW_SCE_GenerateOemKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_Cmd, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00006e02u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x800103e0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38000fffu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0x65d6015fu, 0xcef163cdu, 0xd36f3dbau, 0x9ff542e9u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func049(InData_Cmd);
        SCE->REG_104H = 0x00000068u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(InData_SharedKeyIndex[0]);
        SCE->REG_ECH = 0x000037e4u;
        SCE->REG_ECH = 0x3420a880u;
        SCE->REG_ECH = 0x00000005u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        SCE->REG_ECH = 0x3420a880u;
        SCE->REG_ECH = 0x00000024u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        SCE->REG_ECH = 0x3420a820u;
        SCE->REG_ECH = 0x00000010u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func100(0x98244c8cu, 0x79b8693eu, 0x27d09331u, 0x54bd7297u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x619b2415u, 0x1a64fb8fu, 0x72abf3c5u, 0xb1a9f8d3u);
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
            SCE->REG_ECH = 0x0000349fu;
            OFS_ADR = InData_SharedKeyIndex[0] << 3;
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000006eu);
            HW_SCE_p_func101(0xa7637c51u, 0x0fdd3f7fu, 0x3ef7d917u, 0x86dcab7au);
            HW_SCE_p_func058(InData_SessionKey,OFS_ADR);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010380u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000006eu);
            HW_SCE_p_func101(0xe5d19a97u, 0xbbcdd6dau, 0x4233f284u, 0x7d0593bau);
            HW_SCE_p_func057_r1(InData_IV,InData_InstData,OutData_KeyIndex);
            HW_SCE_p_func100(0x0ab4814bu, 0xb8367889u, 0x271bcf2fu, 0x4feba308u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x9e5039cbu, 0xd69d6c2au, 0xa37c0068u, 0x3994c7b9u);
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
                HW_SCE_p_func100(0x8daed06bu, 0x2a351c5cu, 0x97281b51u, 0x096a7d03u);
                SCE->REG_E0H = 0x81010000u;
                SCE->REG_04H = 0x00000606u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[0] = SCE->REG_100H;
                HW_SCE_p_func102(0x5d24c640u, 0x65732df6u, 0x707f16f3u, 0x63de5db7u);
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
    else
    {
        HW_SCE_p_func049(InData_Cmd);
        SCE->REG_ECH = 0x000037e4u;
        SCE->REG_ECH = 0x3420a880u;
        SCE->REG_ECH = 0x00000005u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        SCE->REG_ECH = 0x3420a880u;
        SCE->REG_ECH = 0x00000024u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func100(0x7aef0fcbu, 0x9258934au, 0x8b4dbf1fu, 0xf15611dcu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x638045bau, 0xdc6175a9u, 0x99105401u, 0x7086cb16u);
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
            SCE->REG_ECH = 0x0000349fu;
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010380u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000006eu);
            HW_SCE_p_func101(0x083ef1a1u, 0x630e194cu, 0x4b5f490eu, 0x96a54f99u);
            HW_SCE_p_func065_r1(InData_InstData,OutData_KeyIndex);
            HW_SCE_p_func100(0x1cf9ac81u, 0x590924eau, 0xd4425eb1u, 0xd5db5292u);
            SCE->REG_E0H = 0x81010000u;
            SCE->REG_04H = 0x00000606u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[0] = SCE->REG_100H;
            HW_SCE_p_func102(0x61423c7fu, 0xf3f4807eu, 0x10a36a81u, 0x6c3dbeadu);
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

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p6e_r2.prc
***********************************************************************************************************************/
