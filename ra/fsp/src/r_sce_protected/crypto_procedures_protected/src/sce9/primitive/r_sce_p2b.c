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

fsp_err_t R_SCE_GenerateRsa2048RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PrivKeyIndex)
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
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00002b02U;
    SCE->REG_108H = 0x00000000U;
    R_SCE_func100(0xa5b6dcb3U, 0xed6ad1f7U, 0x249f777dU, 0x4201651aU);
    R_SCE_func103();
    R_SCE_func100(0x8db9affaU, 0x8d66f896U, 0x969ffd93U, 0x10a2bdedU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01080c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_ECH = 0x00000a31U;
    for(kLoop = 0; kLoop < MAX_CNT; kLoop = kLoop + 1)
    {
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_00H = 0x00003043U;
        SCE->REG_2CH = 0x00000012U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00002f57U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00030005U);
        SCE->REG_100H = change_endian_long(0x0007000bU);
        SCE->REG_100H = change_endian_long(0x000d0011U);
        SCE->REG_100H = change_endian_long(0x00130017U);
        SCE->REG_100H = change_endian_long(0x001d001fU);
        SCE->REG_100H = change_endian_long(0x00250029U);
        SCE->REG_100H = change_endian_long(0x002b002fU);
        SCE->REG_100H = change_endian_long(0x003b003dU);
        SCE->REG_100H = change_endian_long(0x00430047U);
        SCE->REG_100H = change_endian_long(0x0049004fU);
        SCE->REG_100H = change_endian_long(0x00530059U);
        SCE->REG_100H = change_endian_long(0x00610065U);
        SCE->REG_100H = change_endian_long(0x0067006bU);
        SCE->REG_100H = change_endian_long(0x006d0071U);
        SCE->REG_100H = change_endian_long(0x007f0083U);
        SCE->REG_100H = change_endian_long(0x0089008bU);
        SCE->REG_100H = change_endian_long(0x00950097U);
        SCE->REG_100H = change_endian_long(0x009d00a3U);
        SCE->REG_100H = change_endian_long(0x00a700adU);
        SCE->REG_100H = change_endian_long(0x00b300b5U);
        SCE->REG_100H = change_endian_long(0x00bf00c1U);
        SCE->REG_100H = change_endian_long(0x00c500c7U);
        SCE->REG_100H = change_endian_long(0x00d300dfU);
        SCE->REG_100H = change_endian_long(0x00e300e5U);
        SCE->REG_100H = change_endian_long(0x00e900efU);
        SCE->REG_100H = change_endian_long(0x00f100fbU);
        SCE->REG_100H = change_endian_long(0x01010107U);
        SCE->REG_100H = change_endian_long(0x010d010fU);
        SCE->REG_100H = change_endian_long(0x01150119U);
        SCE->REG_100H = change_endian_long(0x011b0125U);
        SCE->REG_100H = change_endian_long(0x01330137U);
        SCE->REG_100H = change_endian_long(0x0139013dU);
        SCE->REG_100H = change_endian_long(0x014b0151U);
        SCE->REG_100H = change_endian_long(0x015b015dU);
        SCE->REG_100H = change_endian_long(0x01610167U);
        SCE->REG_100H = change_endian_long(0x016f0175U);
        SCE->REG_100H = change_endian_long(0x017b017fU);
        SCE->REG_100H = change_endian_long(0x0185018dU);
        SCE->REG_100H = change_endian_long(0x01910199U);
        SCE->REG_100H = change_endian_long(0x01a301a5U);
        SCE->REG_100H = change_endian_long(0x01af01b1U);
        SCE->REG_100H = change_endian_long(0x01b701bbU);
        SCE->REG_100H = change_endian_long(0x01c101c9U);
        SCE->REG_100H = change_endian_long(0x01cd01cfU);
        SCE->REG_100H = change_endian_long(0x01d301dfU);
        SCE->REG_100H = change_endian_long(0x01e701ebU);
        SCE->REG_100H = change_endian_long(0x01f301f7U);
        SCE->REG_100H = change_endian_long(0x01fd0000U);
        SCE->REG_ECH = 0x000008c6U;
        SCE->REG_00H = 0x00000343U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x80b00006U;
        SCE->REG_00H = 0x000083c3U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x009f0001U;
        R_SCE_func100(0x92442479U, 0xb6bbc6ecU, 0xb64748ceU, 0x8d1bfc0aU);
        R_SCE_func103();
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x80040000U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000d01fU;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_00H = 0x00003813U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        for(iLoop = 0; iLoop < 24; iLoop = iLoop + 4)
        {
            R_SCE_func100(0xdc0d5af6U, 0xbd12c604U, 0xc6a01bddU, 0xe46a6d37U);
            R_SCE_func103();
            SCE->REG_104H = 0x00000052U;
            SCE->REG_C4H = 0x01000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_00H = 0x00003213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func101(0x1c3ebb0aU, 0xb9a23b76U, 0x0270bcd9U, 0x1de14b5eU);
        }
        R_SCE_func100(0xdc0d5af6U, 0xbd12c604U, 0xc6a01bddU, 0xe46a6d37U);
        R_SCE_func103();
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_E0H = 0x80040000U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000d060U;
        SCE->REG_E0H = 0x81040000U;
        SCE->REG_00H = 0x00003813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_2CH = 0x00000011U;
        SCE->REG_104H = 0x00001f57U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xB51EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851EB8U);
        SCE->REG_100H = change_endian_long(0x51EB851EU);
        SCE->REG_100H = change_endian_long(0xB851EB85U);
        SCE->REG_100H = change_endian_long(0x1EB851EBU);
        SCE->REG_100H = change_endian_long(0x851EB851U);
        SCE->REG_100H = change_endian_long(0xEB851B5CU);
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0x5ad8cda7U, 0x62048bc4U, 0x86a5759eU, 0xaea4ff60U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x6676f283U, 0x9ba9080aU, 0xbdd78178U, 0xe0903ba9U);
            continue;
        }
        else
        {
            R_SCE_func101(0x65317c53U, 0xbc70d6c2U, 0x5441d8e3U, 0xb945c2d3U);
        }
        SCE->REG_ECH = 0x38008a20U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0x84630910U, 0x62797a2fU, 0x8e56b500U, 0x1eda6d62U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_24H = 0x00001dc0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0x44e7eb40U, 0x6768a961U, 0xd7144ab5U, 0x170f220eU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001d91U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                R_SCE_func101(0x10156e72U, 0x8cc9c88cU, 0xd9d7e887U, 0xe5e7d5f9U);
            }
            else
            {
                R_SCE_func101(0x303fb30aU, 0x6cfba06dU, 0x6620c812U, 0x59960c0fU);
            }
            SCE->REG_2CH = 0x00000011U;
            SCE->REG_104H = 0x00000357U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x10000000U);
            SCE->REG_00H = 0x00003073U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x00001591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0xa1104f56U, 0x294ae338U, 0xcebacfc2U, 0x3ab40673U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func101(0x177827aeU, 0x8619839cU, 0x6b9fe109U, 0xdf2abd62U);
                continue;
            }
            else
            {
                R_SCE_func101(0xd659d2f2U, 0x055f7d3eU, 0xc9e402c3U, 0xa1899eaaU);
            }
        }
        else
        {
            R_SCE_func101(0x7d644ce1U, 0xef19c703U, 0xab47e11fU, 0x0acd12c5U);
        }
        SCE->REG_ECH = 0x000008c6U;
        SCE->REG_ECH = 0x0000094aU;
        for(iLoop = 0; iLoop < 96; iLoop = iLoop + 1)
        {
            SCE->REG_ECH = 0x01003906U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_ECH = 0x00002cc0U;
            SCE->REG_E0H = 0x81010100U;
            SCE->REG_00H = 0x0000307fU;
            SCE->REG_2CH = 0x00000014U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00003807U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x00004006U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000009c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0xe710891fU, 0xc42b9f48U, 0xb7d9dc7bU, 0x5f101fbbU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x0000d140U;
                R_SCE_func101(0x2af0a95dU, 0x4988a3b9U, 0x167570e5U, 0x8445c739U);
                break;
            }
            else
            {
                R_SCE_func101(0x695f9debU, 0x1226bf6eU, 0xec5af709U, 0x95c8c661U);
            }
        }
        SCE->REG_ECH = 0x38008940U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0xb4500ab0U, 0x5d9e286cU, 0x13f71830U, 0xf4dd053eU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x0f9d849dU, 0x12ff3971U, 0x8638b124U, 0xf25f9d13U);
            continue;
        }
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000060c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_00H = 0x0000307fU;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_104H = 0x00000057U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00010001U);
        SCE->REG_24H = 0x00004006U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000dc0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000009c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0xce8db60cU, 0x150bed3dU, 0x443a1514U, 0x136faa52U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x8f77518eU, 0xc53878f6U, 0x02979a45U, 0x1f480ae0U);
        }
        else
        {
            SCE->REG_24H = 0x0000d0d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000a0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000005c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000189U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            R_SCE_func100(0xa6d36ce0U, 0x0ccf1c75U, 0x9d058d00U, 0xa0dc7698U);
            SCE->REG_18H = 0x00000004U;
            SCE->REG_38H = 0x00004080U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B10)
            {
                /* waiting */
            }
            SCE->REG_18H = 0x00000000U;
            SCE->REG_24H = 0x000005c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            SCE->REG_24H = 0x000044d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000991U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0x42765fc8U, 0xf8956ad1U, 0xb31a8bb0U, 0x4e7a849cU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func101(0xaa5a6a8bU, 0x8b5adf21U, 0x0dd909bbU, 0x80450c86U);
                continue;
            }
            SCE->REG_24H = 0x000098d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b540U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_E0H = 0x80a0000aU;
            SCE->REG_00H = 0x00008383U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b560U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_B0H = 0x00000700U;
            SCE->REG_A4H = 0x42e0873fU;
            SCE->REG_00H = 0x00001383U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00000c84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x400009cdU;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x38008a20U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0xd074aa3aU, 0x87e6862cU, 0x282a6f5eU, 0xf151c1dfU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_7CH = 0x00000021U;
                SCE->REG_00H = 0x00005113U;
                SCE->REG_74H = 0x00000004U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                R_SCE_func101(0x1eff8031U, 0x640f93a1U, 0xd6ec3790U, 0x30429447U);
            }
            else
            {
                SCE->REG_7CH = 0x00000041U;
                SCE->REG_00H = 0x00005113U;
                SCE->REG_74H = 0x00000004U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                R_SCE_func101(0xad46038bU, 0x03072792U, 0x9fdb5c00U, 0x4016ab53U);
            }
            R_SCE_func100(0x779dcabcU, 0x62898055U, 0x314a9e98U, 0xe914e2b1U);
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000c0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00000929U;
            SCE->REG_ECH = 0x0000b4c0U;
            SCE->REG_ECH = 0x000000fcU;
            SCE->REG_ECH = 0x00003906U;
            SCE->REG_ECH = 0x00008d00U;
            SCE->REG_ECH = 0xfffffffeU;
            SCE->REG_ECH = 0x00003d06U;
            SCE->REG_ECH = 0x00000908U;
            for(iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
            {
                SCE->REG_ECH = 0x000038e6U;
                SCE->REG_ECH = 0x0000a8c0U;
                SCE->REG_ECH = 0x00000004U;
                for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x38008900U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_ECH = 0x11816907U;
                    SCE->REG_ECH = 0x38008900U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_ECH = 0x10002d20U;
                    SCE->REG_ECH = 0x000168e7U;
                }
            }
            SCE->REG_ECH = 0x00003549U;
            SCE->REG_ECH = 0x0000a540U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_ECH = 0x0002694aU;
            SCE->REG_E0H = 0x81010140U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            SCE->REG_ECH = 0x000037eaU;
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000185U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x000033e0U;
                R_SCE_func101(0x49280d66U, 0x305c394cU, 0x1b479599U, 0xc67af230U);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            R_SCE_func100(0x37bbd1cbU, 0xf9ea6a6cU, 0x0bfe71b0U, 0x2d18f113U);
            SCE->REG_ECH = 0x00026d4aU;
            SCE->REG_ECH = 0x00002949U;
            SCE->REG_E0H = 0x81010140U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            SCE->REG_ECH = 0x000037eaU;
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_24H = 0x2000018dU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x000033e0U;
                R_SCE_func101(0xa5eef22dU, 0xd8b34e6fU, 0xf293ed5dU, 0x27367962U);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            R_SCE_func100(0x71eef8b7U, 0x013dee0aU, 0x8aa23bfeU, 0xb7f89b02U);
            SCE->REG_24H = 0x0000a0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00000a52U;
            SCE->REG_24H = 0x00006404U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00006c04U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_E0H = 0x81010160U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            for(iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                SCE->REG_2CH = 0x00000010U;
                for(jLoop = 0; jLoop < 32; jLoop = jLoop + 4)
                {
                    R_SCE_func100(0x45703240U, 0x6434c517U, 0xd9732713U, 0x5c487d86U);
                    R_SCE_func103();
                    SCE->REG_104H = 0x00000052U;
                    SCE->REG_C4H = 0x01000c84U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000000U);
                    SCE->REG_00H = 0x00003213U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    R_SCE_func101(0xb4095821U, 0xc571b2dcU, 0x82013581U, 0x98b2ee91U);
                }
                R_SCE_func100(0x8721c59aU, 0x1fba425dU, 0xcd6812f6U, 0x4a92f6f7U);
                SCE->REG_24H = 0x000019c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000c0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00009008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000019c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000581U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000c0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000dc0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_18H = 0x00000004U;
                SCE->REG_38H = 0x00000c40U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B10)
                {
                    /* waiting */
                }
                SCE->REG_18H = 0x00000000U;
                SCE->REG_24H = 0x000005c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00001191U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00210000U;
                SCE->REG_24H = 0x000005c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000991U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00210000U;
                R_SCE_func100(0x50b07a2dU, 0xa919932dU, 0x8d61da2aU, 0x2527551cU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (0U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_ECH = 0x00002e40U;
                    R_SCE_func101(0xd2aa5059U, 0x69986543U, 0xe9521bcbU, 0xf36550d9U);
                }
                else
                {
                    R_SCE_func100(0x7dab1164U, 0x0d1f6b6eU, 0x555bfb9aU, 0xfc3a2a6bU);
                    SCE->REG_24H = 0x000019c0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000591U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00006404U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00006c04U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_E0H = 0x81010120U;
                    SCE->REG_04H = 0x00000606U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    S_RAM[0+1 + 0] = change_endian_long(SCE->REG_100H);
                    SCE->REG_ECH = 0x000037e9U;
                    for(jLoop = 0; jLoop < (int32_t)S_RAM[0+1]; jLoop = jLoop + 1)
                    {
                        SCE->REG_24H = 0x000009c0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00001191U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000U;
                        SCE->REG_24H = 0x000011c0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000991U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00210000U;
                        R_SCE_func100(0x8f2574f0U, 0x6a6aec33U, 0xd1a35a1fU, 0x0bde026eU);
                        SCE->REG_1CH = 0x00400000U;
                        SCE->REG_1D0H = 0x00000000U;
                        if (0U == (SCE->REG_1CH_b.B22))
                        {
                            SCE->REG_ECH = 0x00002e40U;
                            R_SCE_func101(0xcb24a47dU, 0x5b98e3f7U, 0xfc0bfcb3U, 0x8c5c1dcdU);
                            break;
                        }
                        else
                        {
                            SCE->REG_24H = 0x00004c0cU;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x0000880cU;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x000019c0U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x00000591U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_24H = 0x000040c1U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            R_SCE_func101(0xa61e2c9aU, 0x4b749da4U, 0x27d4f0f7U, 0x5cf35267U);
                        }
                    }
                    SCE->REG_ECH = 0x38008a40U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    R_SCE_func100(0x1637e74aU, 0x922ba8a8U, 0x6be1187eU, 0x1dc2f8edU);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        R_SCE_func101(0x1b879c9dU, 0x6c0782e5U, 0xde66656dU, 0x702c359aU);
                        break;
                    }
                    else
                    {
                        R_SCE_func101(0xe75699d4U, 0x4082d188U, 0xfcc85dccU, 0x6eaf82b5U);
                    }
                }
            }
            SCE->REG_ECH = 0x38000a4bU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0x52109273U, 0x7569c715U, 0x565a942eU, 0xc0242ca8U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x00002e20U;
                SCE->REG_ECH = 0x38008a20U;
                SCE->REG_ECH = 0x00000002U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                R_SCE_func100(0x72f62bb0U, 0xca307657U, 0xe2890891U, 0x2fe84ce6U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    R_SCE_func101(0x83ecc02fU, 0x1e7c7752U, 0x685d01d0U, 0x90cc3456U);
                    break;
                }
                else
                {
                    SCE->REG_24H = 0x000019c0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000e0c1U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    R_SCE_func101(0x545eb67bU, 0x0d2cc963U, 0xea3a2fdbU, 0x80b913c5U);
                }
            }
            else
            {
                R_SCE_func101(0xe073e65cU, 0xc9ee69a6U, 0x8947c379U, 0xbafefb7eU);
            }
        }
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x18e47f34U, 0x1884fb0aU, 0xa4ca32efU, 0xf9d0ab66U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x51de014dU, 0x33e1ad9aU, 0xffec29ffU, 0x95776928U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    R_SCE_func100(0xd9e2b8e7U, 0xe950901cU, 0xe0486221U, 0xbc3e860fU);
    SCE->REG_ECH = 0x0000b5c0U;
    SCE->REG_ECH = 0x00010001U;
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001dc0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_D0H = 0x00000f00U;
    SCE->REG_C4H = 0x42e087bfU;
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    SCE->REG_04H = 0x00000202U;
    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[iLoop + 0] = SCE->REG_100H;
        S_HEAP[iLoop + 1] = SCE->REG_100H;
        S_HEAP[iLoop + 2] = SCE->REG_100H;
        S_HEAP[iLoop + 3] = SCE->REG_100H;
    }
    R_SCE_func100(0x1516b75eU, 0x0e239e32U, 0x6a166d1bU, 0xa6c89764U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_C4H = 0x400009cdU;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_HEAP[iLoop + 0] = SCE->REG_100H;
    S_HEAP[iLoop + 1] = SCE->REG_100H;
    S_HEAP[iLoop + 2] = SCE->REG_100H;
    S_HEAP[iLoop + 3] = SCE->REG_100H;
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    while(1)
    {
        SCE->REG_24H = 0x00008006U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0xc649a206U, 0xa18db666U, 0xaa98a57fU, 0xc2111e03U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x6029ecd9U, 0x9a4a1d8fU, 0x4c38f31fU, 0x7101fbc3U);
            break;
        }
        else
        {
            SCE->REG_24H = 0x000019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000d0d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            R_SCE_func101(0x616d9225U, 0x75bbe7f3U, 0x135c9e2aU, 0x5b8ef0d6U);
        }
    }
    SCE->REG_24H = 0x000094d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000c002U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000dcd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000b80aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_00H = 0x000030ffU;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000057U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00010001U);
    SCE->REG_2CH = 0x00000002U;
    SCE->REG_24H = 0x0000c002U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_E0H = 0x800100c0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000024U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b500U;
    SCE->REG_ECH = 0x00010001U;
    SCE->REG_24H = 0x000005c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    while(1)
    {
        R_SCE_func100(0x31a8a36fU, 0xb31b2ee3U, 0xbcf5a0d7U, 0x14fbe491U);
        R_SCE_func103();
        R_SCE_func100(0xca8db3d0U, 0xa00b6625U, 0xa2c83245U, 0x4f4f4c5cU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01090c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_ECH = 0x0000094aU;
        SCE->REG_E0H = 0x80c0000aU;
        SCE->REG_00H = 0x00018303U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0x3746a344U, 0x9f44ba6cU, 0x35bb51f4U, 0x4c0d1991U);
        SCE->REG_D0H = 0x00000f00U;
        SCE->REG_C4H = 0x42e097bfU;
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_04H = 0x00000202U;
        for (iLoop=68; iLoop<132; iLoop=iLoop+4)
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_HEAP[iLoop + 0] = SCE->REG_100H;
            S_HEAP[iLoop + 1] = SCE->REG_100H;
            S_HEAP[iLoop + 2] = SCE->REG_100H;
            S_HEAP[iLoop + 3] = SCE->REG_100H;
        }
        R_SCE_func100(0x27be7167U, 0x17c8cdfdU, 0xf01afed2U, 0x3301a3d5U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x400019cdU;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000212U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[iLoop + 0] = SCE->REG_100H;
        S_HEAP[iLoop + 1] = SCE->REG_100H;
        S_HEAP[iLoop + 2] = SCE->REG_100H;
        S_HEAP[iLoop + 3] = SCE->REG_100H;
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_24H = 0x000019c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001U;
        SCE->REG_00H = 0x0000301fU;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x810100c0U;
        SCE->REG_00H = 0x00003807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x0000301fU;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x81010100U;
        SCE->REG_00H = 0x00003807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_2CH = 0x00000000U;
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x8000c002U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x00003506U;
        SCE->REG_E0H = 0x800100c0U;
        SCE->REG_00H = 0x0000031fU;
        SCE->REG_2CH = 0x0000002cU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_00H = 0x00008307U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x380088c0U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0x3654ea74U, 0x1fd1cc3fU, 0xfc04a87dU, 0xcc28b43aU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_104H = 0x00003f61U;
            SCE->REG_B0H = 0x00000f00U;
            SCE->REG_A4H = 0x42f087bfU;
            SCE->REG_00H = 0x00013103U;
            SCE->REG_2CH = 0x00000014U;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = S_HEAP[iLoop + 0];
                SCE->REG_100H = S_HEAP[iLoop + 1];
                SCE->REG_100H = S_HEAP[iLoop + 2];
                SCE->REG_100H = S_HEAP[iLoop + 3];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func101(0xa8e7d727U, 0xfdc6a8daU, 0x844ee6f2U, 0x00b0b96cU);
            break;
        }
        else
        {
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_24H = 0x000015c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000c0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_00H = 0x00003083U;
            SCE->REG_2CH = 0x00000011U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x0000880eU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_104H = 0x00003f62U;
            SCE->REG_D0H = 0x00000f00U;
            SCE->REG_C4H = 0x42f097bfU;
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            for (iLoop=68; iLoop<132; iLoop=iLoop+4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = S_HEAP[iLoop + 0];
                SCE->REG_100H = S_HEAP[iLoop + 1];
                SCE->REG_100H = S_HEAP[iLoop + 2];
                SCE->REG_100H = S_HEAP[iLoop + 3];
            }
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_C4H = 0x400017bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = S_HEAP[iLoop + 0];
            SCE->REG_100H = S_HEAP[iLoop + 1];
            SCE->REG_100H = S_HEAP[iLoop + 2];
            SCE->REG_100H = S_HEAP[iLoop + 3];
            SCE->REG_C4H = 0x00800c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000009c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000094aU;
            SCE->REG_E0H = 0x81c0000aU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func101(0xaa5e6f19U, 0x8e2e22e4U, 0x947483bdU, 0x8ad8139bU);
        }
    }
    SCE->REG_ECH = 0x00007c06U;
    SCE->REG_1CH = 0x00602000U;
    SCE->REG_A4H = 0x400007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[iLoop + 0];
    SCE->REG_100H = S_HEAP[iLoop + 1];
    SCE->REG_100H = S_HEAP[iLoop + 2];
    SCE->REG_100H = S_HEAP[iLoop + 3];
    SCE->REG_A4H = 0x00800c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0xb833bda0U, 0x5c4c9605U, 0x3c9248f5U, 0xfa28bae6U);
    SCE->REG_28H = 0x00bf0001U;
    R_SCE_func103();
    R_SCE_func100(0xe6d75747U, 0x7ad48da5U, 0xca36e100U, 0x0818a927U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01090c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    R_SCE_func100(0x497f8681U, 0x673c28fcU, 0x1a470b9eU, 0xd5549ffbU);
    SCE->REG_D0H = 0x00000f00U;
    SCE->REG_C4H = 0x42e097bfU;
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    SCE->REG_04H = 0x00000202U;
    for (iLoop=68; iLoop<132; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[iLoop + 0] = SCE->REG_100H;
        S_HEAP[iLoop + 1] = SCE->REG_100H;
        S_HEAP[iLoop + 2] = SCE->REG_100H;
        S_HEAP[iLoop + 3] = SCE->REG_100H;
    }
    R_SCE_func100(0x8846e6ffU, 0x3a8401bfU, 0x6e286aa1U, 0x079872f4U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_C4H = 0x400019cdU;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_HEAP[iLoop + 0] = SCE->REG_100H;
    S_HEAP[iLoop + 1] = SCE->REG_100H;
    S_HEAP[iLoop + 2] = SCE->REG_100H;
    S_HEAP[iLoop + 3] = SCE->REG_100H;
    R_SCE_func100(0xf4c59366U, 0xd36da880U, 0xbc610906U, 0xc4ee03deU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x0000b8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000002U;
    SCE->REG_24H = 0x00007b0aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0xfcbf0001U;
    SCE->REG_24H = 0x0000c8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_00H = 0x00008207U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000020fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x000034e0U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000002bU);
    R_SCE_func101(0x6ab98776U, 0x58e8a14bU, 0x78865269U, 0xc34ab9f1U);
    R_SCE_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000002bU);
    R_SCE_func101(0xf201f748U, 0x5c87c622U, 0xc5c0deb4U, 0x7e69236cU);
    R_SCE_func044();
    R_SCE_func100(0xa8c17ffbU, 0x12ae4b7cU, 0x6f3471c5U, 0x0d2adfa0U);
    SCE->REG_E0H = 0x81010000U;
    SCE->REG_04H = 0x00000606U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PubKeyIndex[0] = SCE->REG_100H;
    R_SCE_func100(0x54202126U, 0x61df8c16U, 0xf766cceeU, 0xda3f5c49U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00040804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    SCE->REG_D0H = 0x40000f00U;
    SCE->REG_C4H = 0x02e08887U;
    SCE->REG_04H = 0x00000202U;
    for(iLoop=0; iLoop<64; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0x1bfce66dU, 0x873a200eU, 0x0ba3530fU, 0xbbf531acU);
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x00e08884U;
    SCE->REG_E0H = 0x810101c0U;
    SCE->REG_00H = 0x00002807U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PubKeyIndex[65] = SCE->REG_100H;
    OutData_PubKeyIndex[66] = SCE->REG_100H;
    OutData_PubKeyIndex[67] = SCE->REG_100H;
    OutData_PubKeyIndex[68] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (0U != SCE->REG_C8H_b.B6)
    {
        /* waiting */
    }
    R_SCE_func100(0x62caf56aU, 0xaea4a5c2U, 0xbffb0b7fU, 0xaea7002dU);
    SCE->REG_18H = 0x00000004U;
    SCE->REG_24H = 0x00004404U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00004804U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000000U;
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    SCE->REG_D0H = 0x40000f00U;
    SCE->REG_C4H = 0x00e087b7U;
    SCE->REG_04H = 0x00000202U;
    for(iLoop=68; iLoop<132; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PubKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0x3131149aU, 0x11bf462fU, 0x71b885dcU, 0x6a0fdd2eU);
    SCE->REG_104H = 0x00000352U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000089c5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000010U);
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PubKeyIndex[133] = SCE->REG_100H;
    OutData_PubKeyIndex[134] = SCE->REG_100H;
    OutData_PubKeyIndex[135] = SCE->REG_100H;
    OutData_PubKeyIndex[136] = SCE->REG_100H;
    R_SCE_func100(0xff3c2dbeU, 0x060f91ecU, 0xcc73f6daU, 0xb7be39d1U);
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_00H = 0x00008207U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000020fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x000034e0U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000fdU);
    R_SCE_func101(0xbb004206U, 0x83367280U, 0xcf594deaU, 0xf68a314eU);
    R_SCE_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x0000000dU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000fdU);
    R_SCE_func101(0x990e90aeU, 0xc3053983U, 0x557ddf50U, 0x8973f306U);
    R_SCE_func044();
    R_SCE_func100(0x722ff02bU, 0xf75d5865U, 0xfc29d717U, 0xea177bf8U);
    SCE->REG_E0H = 0x81010000U;
    SCE->REG_04H = 0x00000606U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PrivKeyIndex[0] = SCE->REG_100H;
    R_SCE_func100(0xb0850381U, 0xc4dd3713U, 0x38ad8efaU, 0x1a75c26dU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    SCE->REG_D0H = 0x40000f00U;
    SCE->REG_C4H = 0x02e087b7U;
    SCE->REG_04H = 0x00000202U;
    for(iLoop=0; iLoop<64; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0xcdb6eacfU, 0x47e24249U, 0x3cfaa2a2U, 0xcc672c7eU);
    SCE->REG_00H = 0x00012103U;
    SCE->REG_104H = 0x00000031U;
    SCE->REG_B0H = 0x00000f00U;
    SCE->REG_A4H = 0x42f097bfU;
    SCE->REG_D0H = 0x40000f00U;
    SCE->REG_C4H = 0x00e087b7U;
    SCE->REG_04H = 0x00000202U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[68];
    SCE->REG_100H = S_HEAP[69];
    SCE->REG_100H = S_HEAP[70];
    SCE->REG_100H = S_HEAP[71];
    for (iLoop = 64; iLoop < 124 ; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = S_HEAP[iLoop+8 + 0];
        SCE->REG_100H = S_HEAP[iLoop+8 + 1];
        SCE->REG_100H = S_HEAP[iLoop+8 + 2];
        SCE->REG_100H = S_HEAP[iLoop+8 + 3];
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
    OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
    OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
    OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    SCE->REG_104H = 0x00000000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_C8H_b.B6)
    {
        /* waiting */
    }
    SCE->REG_A4H = 0x400017bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_HEAP[132];
    SCE->REG_100H = S_HEAP[133];
    SCE->REG_100H = S_HEAP[134];
    SCE->REG_100H = S_HEAP[135];
    SCE->REG_A4H = 0x00800c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0x23908e74U, 0x00fdbcecU, 0xf291c22eU, 0x4c0cc4fdU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    SCE->REG_D0H = 0x40000f00U;
    SCE->REG_C4H = 0x00e087b7U;
    SCE->REG_04H = 0x00000202U;
    for(iLoop=128; iLoop<192; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[iLoop+1 + 0] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 1] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 2] = SCE->REG_100H;
        OutData_PrivKeyIndex[iLoop+1 + 3] = SCE->REG_100H;
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0xd96db8efU, 0x196981a3U, 0xe8c6e4a5U, 0xa21b6ba1U);
    SCE->REG_104H = 0x00000352U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000089c5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000030U);
    SCE->REG_04H = 0x00000212U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PrivKeyIndex[193] = SCE->REG_100H;
    OutData_PrivKeyIndex[194] = SCE->REG_100H;
    OutData_PrivKeyIndex[195] = SCE->REG_100H;
    OutData_PrivKeyIndex[196] = SCE->REG_100H;
    R_SCE_func102(0xf7c434feU, 0xc787e528U, 0xb90a4a06U, 0xd4ff2cd5U);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p2b_r2.prc
***********************************************************************************************************************/
