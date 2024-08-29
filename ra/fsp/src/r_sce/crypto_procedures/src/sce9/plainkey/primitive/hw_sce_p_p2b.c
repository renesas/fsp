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

fsp_err_t HW_SCE_GenerateRsa2048RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey)
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
    (void)InData_KeyType;
    (void)OutData_PrivKey;
    (void)OutData_PubKey;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00002b02U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_p_func100(0x29802336U, 0xd159a0b7U, 0xe311d54cU, 0x36dce5c5U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xb8dc77d4U, 0x3247864dU, 0xc9a3aaf3U, 0x419c0ae7U);
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
        HW_SCE_p_func100(0x7c3be8a4U, 0x10077703U, 0x98320738U, 0x5903bfb6U);
        HW_SCE_p_func103();
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
            HW_SCE_p_func100(0x10e16e07U, 0x8fb49ab6U, 0xf23e1fdfU, 0x970de29aU);
            HW_SCE_p_func103();
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
            HW_SCE_p_func101(0xfc43caa7U, 0xb55af2a9U, 0x6c16fba1U, 0x313b167cU);
        }
        HW_SCE_p_func100(0x10e16e07U, 0x8fb49ab6U, 0xf23e1fdfU, 0x970de29aU);
        HW_SCE_p_func103();
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
        HW_SCE_p_func100(0x90ae1e92U, 0x8bca1ce6U, 0x377f1b58U, 0x7427eca8U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x5cba8941U, 0x18800bcfU, 0x699933a2U, 0xc0a9c83dU);
            continue;
        }
        else
        {
            HW_SCE_p_func101(0x755f15bcU, 0xfaa7c752U, 0x8cdee2ccU, 0x7c5d5e22U);
        }
        SCE->REG_ECH = 0x38008a20U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x1ff30c58U, 0x2c43ede7U, 0x51891153U, 0xc6f0919aU);
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
            HW_SCE_p_func100(0x491d7813U, 0x9669f2a6U, 0x8ab8a647U, 0xebc5b55fU);
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
                HW_SCE_p_func101(0x512c888cU, 0xac3c9b30U, 0x350fde63U, 0xaae062a7U);
            }
            else
            {
                HW_SCE_p_func101(0xc1f2ef4fU, 0x557853acU, 0x59b8831bU, 0x4b149043U);
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
            HW_SCE_p_func100(0x87807a30U, 0x9f5ca829U, 0xe1175f96U, 0x1a9e6e75U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0xe281d2f1U, 0x0c9fbf53U, 0xf7faeb43U, 0xc9102828U);
                continue;
            }
            else
            {
                HW_SCE_p_func101(0xc6d10669U, 0x9f4ff89dU, 0x8038e04aU, 0x9a3e17b0U);
            }
        }
        else
        {
            HW_SCE_p_func101(0x07901e4cU, 0x0cebe917U, 0x0f834a0eU, 0x9f2d080eU);
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
            HW_SCE_p_func100(0x85dde662U, 0xd8fc3123U, 0x89de60c8U, 0x07d5ef2eU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x0000d140U;
                HW_SCE_p_func101(0x28a65192U, 0xe2a959dbU, 0xd43404eaU, 0x7339fd84U);
                break;
            }
            else
            {
                HW_SCE_p_func101(0x11a06545U, 0x32ad1e6fU, 0xdeb595cdU, 0xe97bc932U);
            }
        }
        SCE->REG_ECH = 0x38008940U;
        SCE->REG_ECH = 0x00000001U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x11867603U, 0x6f83bc5aU, 0xaa875c8dU, 0x12f9e1ecU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xebf0bae4U, 0x21cca239U, 0xd872659aU, 0xfcdcf0fcU);
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
        HW_SCE_p_func100(0x7c533ae2U, 0x000734a8U, 0x356810baU, 0x487c1ecfU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x5436329aU, 0x9632d27fU, 0x10281c9eU, 0xc0df0d5fU);
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
            HW_SCE_p_func100(0x79f5b90aU, 0xd7922a5aU, 0xac0169c2U, 0x03577a52U);
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
            HW_SCE_p_func100(0x8a4e89beU, 0xad785403U, 0x03489702U, 0x2497f830U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0xbe8e9962U, 0x0bda5eb5U, 0x5c30c9c9U, 0x33a96ae3U);
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
            HW_SCE_p_func100(0xf96cb05eU, 0x7a810f51U, 0x46e8fa5eU, 0x812236d7U);
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
                HW_SCE_p_func101(0x87016245U, 0x5e83f673U, 0x602e7aebU, 0xeb5683b0U);
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
                HW_SCE_p_func101(0x239b33b8U, 0xd6eb409fU, 0x93df7b47U, 0xb35986dcU);
            }
            HW_SCE_p_func100(0xeaa4de27U, 0x5c6570b3U, 0x23239a44U, 0xb259bd4dU);
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
                HW_SCE_p_func101(0x25f7c21cU, 0xa58e2d37U, 0xc7d2c302U, 0x94a4950cU);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func100(0x3ffbde47U, 0xdf842701U, 0x3ed2ea1fU, 0x92f4b6cdU);
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
                HW_SCE_p_func101(0xf2494d23U, 0x208dc9cfU, 0x9eaacfe5U, 0xe3122179U);
            }
            SCE->REG_ECH = 0x00007c1fU;
            SCE->REG_1CH = 0x00602000U;
            HW_SCE_p_func100(0xb09a35c9U, 0x5d8bb3e6U, 0xfc920928U, 0x6f246efaU);
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
                    HW_SCE_p_func100(0x80f0c0afU, 0xb016844bU, 0xab5eb905U, 0x9689d197U);
                    HW_SCE_p_func103();
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
                    HW_SCE_p_func101(0x615822e9U, 0xfce99d10U, 0xc52ef231U, 0xd71f309aU);
                }
                HW_SCE_p_func100(0xad8720efU, 0x8c70ba5eU, 0xc306a7e5U, 0x8d3defeeU);
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
                HW_SCE_p_func100(0x5025e1b2U, 0xe9c90814U, 0x20f9ebb3U, 0x8d9af69eU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (0U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_ECH = 0x00002e40U;
                    HW_SCE_p_func101(0x400c3652U, 0x19b00af6U, 0x415d810dU, 0x6580bbf1U);
                }
                else
                {
                    HW_SCE_p_func100(0x87f0e1cbU, 0x06afd9adU, 0xc94c17ecU, 0xc9d9cfc0U);
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
                        HW_SCE_p_func100(0x8ec7a622U, 0xc2ecfd33U, 0x4596d1b1U, 0xdd384955U);
                        SCE->REG_1CH = 0x00400000U;
                        SCE->REG_1D0H = 0x00000000U;
                        if (0U == (SCE->REG_1CH_b.B22))
                        {
                            SCE->REG_ECH = 0x00002e40U;
                            HW_SCE_p_func101(0xd4b47306U, 0x947e48e2U, 0xe08a050cU, 0x6baf7466U);
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
                            HW_SCE_p_func101(0xe518ad9dU, 0x5640af24U, 0x34eac94eU, 0x014d63edU);
                        }
                    }
                    SCE->REG_ECH = 0x38008a40U;
                    SCE->REG_ECH = 0x00000000U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    HW_SCE_p_func100(0x98765488U, 0x67b2035eU, 0x3880187bU, 0x02273ca1U);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        HW_SCE_p_func101(0xdbe391c8U, 0xe36886d3U, 0x44ecc41bU, 0x542e2e2dU);
                        break;
                    }
                    else
                    {
                        HW_SCE_p_func101(0x624f8893U, 0xe40b8b49U, 0x8082da1aU, 0xc20670a6U);
                    }
                }
            }
            SCE->REG_ECH = 0x38000a4bU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xd67e7880U, 0xe9c8649eU, 0x28a2b1caU, 0xa1387d95U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_ECH = 0x00002e20U;
                SCE->REG_ECH = 0x38008a20U;
                SCE->REG_ECH = 0x00000002U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                HW_SCE_p_func100(0xc0f8142aU, 0x43ece9e1U, 0xe5a42c4cU, 0x95e232e0U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func101(0x72ead49bU, 0x3189737dU, 0x9848fc7dU, 0x2304bad9U);
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
                    HW_SCE_p_func101(0x4165eaaaU, 0xde546422U, 0x77a875aaU, 0x47feb412U);
                }
            }
            else
            {
                HW_SCE_p_func101(0x424beb5fU, 0x7e7bd614U, 0xc3225a20U, 0xaa7eb3c8U);
            }
        }
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x797c9f8cU, 0xf9c42989U, 0xc34235dcU, 0xabd7d990U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x9557ba67U, 0x07316373U, 0x90ae53f1U, 0x62dc9458U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    HW_SCE_p_func100(0xac0314bdU, 0x515c4e7eU, 0xb9f37c2bU, 0xa620448dU);
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
    HW_SCE_p_func100(0xd43ec52dU, 0x5fb382ecU, 0xa9cc436cU, 0x4d6b8853U);
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
        HW_SCE_p_func100(0xa7c960d8U, 0xb1109e97U, 0x6b23ed89U, 0x19ad0c6dU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x1f9661cdU, 0x28746ae5U, 0x8cd2741dU, 0x6ddec20bU);
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
            HW_SCE_p_func101(0x3f844510U, 0xe045fee9U, 0x9ccc4a88U, 0x014d4648U);
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
        HW_SCE_p_func100(0x2601c365U, 0x86269c2cU, 0x8bd2d673U, 0x7fd6e24eU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0x628d9e05U, 0xdbb7daa3U, 0xa04bf479U, 0x0ed0c908U);
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
        HW_SCE_p_func100(0x91cef570U, 0x5ddcb017U, 0x1a28922fU, 0xde55c6f6U);
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
        HW_SCE_p_func100(0x85c5fb6eU, 0xd3462e3cU, 0xefde4039U, 0x337f35b6U);
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
        HW_SCE_p_func100(0x84072e81U, 0xb4707fe1U, 0x210e80f2U, 0x478f4a77U);
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
            HW_SCE_p_func101(0x4d7de79eU, 0x7aee29b9U, 0xfdb1ad36U, 0xe56bb109U);
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
            HW_SCE_p_func101(0xd78e57d3U, 0x88d3ecf5U, 0x786fbc37U, 0x62fe7edfU);
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
    HW_SCE_p_func100(0xe8af30a3U, 0x68c2064eU, 0x712f8903U, 0xf66d4c14U);
    SCE->REG_28H = 0x00bf0001U;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xd6fee8b4U, 0xfeb8e1cfU, 0xec897771U, 0x8805760eU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01090c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    HW_SCE_p_func100(0x7a264cd4U, 0x63f846bdU, 0x4e808fcaU, 0xacfd971fU);
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
    HW_SCE_p_func100(0x771da7e3U, 0x9729dd62U, 0xae475f17U, 0x8047367cU);
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
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800103e0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38000fffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xf87eee7cU, 0x9e5e9ba6U, 0xd674c5d9U, 0xb96e11d5U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func100(0xd6c84d13U, 0xcdd54a0aU, 0xf1a3df40U, 0x96ab1f3eU);
        HW_SCE_p_func103();
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
        HW_SCE_p_func101(0x18f639afU, 0x6e25c8b7U, 0x6bd5d373U, 0x20c980dfU);
        HW_SCE_p_func043();
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
        HW_SCE_p_func101(0xea8d2962U, 0x23b0c731U, 0x02063f7bU, 0x360e6545U);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0xfb3eaadcU, 0x1b4c926bU, 0x41d898b5U, 0x5d237607U);
        SCE->REG_E0H = 0x81010000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[0] = SCE->REG_100H;
        HW_SCE_p_func100(0x15b39e7dU, 0xbc172d9fU, 0x0dbd45d3U, 0x9d30cd21U);
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
        HW_SCE_p_func100(0xea7a2df8U, 0x6d487225U, 0x96637959U, 0xd7948d95U);
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
        HW_SCE_p_func100(0xf17df3bdU, 0xa237d4c4U, 0x31891948U, 0x398bde44U);
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
        HW_SCE_p_func100(0x77aecc1aU, 0xc4e61c3cU, 0x32de60c5U, 0xc40e7285U);
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
        HW_SCE_p_func100(0xb77e9d11U, 0x739cdbb4U, 0xb03798c4U, 0x99c1079bU);
        HW_SCE_p_func103();
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
        HW_SCE_p_func101(0x394f8441U, 0xfba13dc3U, 0x22815382U, 0xff49cec6U);
        HW_SCE_p_func043();
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
        HW_SCE_p_func101(0x66692d56U, 0x5e6c77caU, 0xed7b634fU, 0x905615c9U);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0x35fa4854U, 0xcef1ec09U, 0xab49a001U, 0x599a6c24U);
        SCE->REG_E0H = 0x81010000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[0] = SCE->REG_100H;
        HW_SCE_p_func100(0x06f73d5fU, 0x532f17d5U, 0x54dc5af0U, 0x6eee362dU);
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
        HW_SCE_p_func100(0xbecdb75cU, 0xbca8b94eU, 0x0b91504cU, 0xc1f7fc25U);
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
        HW_SCE_p_func100(0x9ac4e83aU, 0xf48e1713U, 0xe59c8f74U, 0xb22f3529U);
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
        HW_SCE_p_func100(0x36d14ec8U, 0xb8c807a7U, 0x74d82cfdU, 0x7a62a60bU);
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
        HW_SCE_p_func101(0x5e0bdd5bU, 0x98aa40d7U, 0x7420083fU, 0x1fbf92daU);
    }
    else
    {
        HW_SCE_p_func100(0x44a10193U, 0x9b7f8205U, 0x4ed43b28U, 0xde684559U);
        SCE->REG_2CH = 0x00000024U;
        SCE->REG_04H = 0x00000302U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKey[0] = SCE->REG_100H;
        OutData_PubKey[1] = SCE->REG_100H;
        OutData_PubKey[2] = SCE->REG_100H;
        OutData_PubKey[3] = SCE->REG_100H;
        OutData_PubKey[4] = SCE->REG_100H;
        OutData_PubKey[5] = SCE->REG_100H;
        OutData_PubKey[6] = SCE->REG_100H;
        OutData_PubKey[7] = SCE->REG_100H;
        OutData_PubKey[8] = SCE->REG_100H;
        OutData_PubKey[9] = SCE->REG_100H;
        OutData_PubKey[10] = SCE->REG_100H;
        OutData_PubKey[11] = SCE->REG_100H;
        OutData_PubKey[12] = SCE->REG_100H;
        OutData_PubKey[13] = SCE->REG_100H;
        OutData_PubKey[14] = SCE->REG_100H;
        OutData_PubKey[15] = SCE->REG_100H;
        OutData_PubKey[16] = SCE->REG_100H;
        OutData_PubKey[17] = SCE->REG_100H;
        OutData_PubKey[18] = SCE->REG_100H;
        OutData_PubKey[19] = SCE->REG_100H;
        OutData_PubKey[20] = SCE->REG_100H;
        OutData_PubKey[21] = SCE->REG_100H;
        OutData_PubKey[22] = SCE->REG_100H;
        OutData_PubKey[23] = SCE->REG_100H;
        OutData_PubKey[24] = SCE->REG_100H;
        OutData_PubKey[25] = SCE->REG_100H;
        OutData_PubKey[26] = SCE->REG_100H;
        OutData_PubKey[27] = SCE->REG_100H;
        OutData_PubKey[28] = SCE->REG_100H;
        OutData_PubKey[29] = SCE->REG_100H;
        OutData_PubKey[30] = SCE->REG_100H;
        OutData_PubKey[31] = SCE->REG_100H;
        OutData_PubKey[32] = SCE->REG_100H;
        OutData_PubKey[33] = SCE->REG_100H;
        OutData_PubKey[34] = SCE->REG_100H;
        OutData_PubKey[35] = SCE->REG_100H;
        OutData_PubKey[36] = SCE->REG_100H;
        OutData_PubKey[37] = SCE->REG_100H;
        OutData_PubKey[38] = SCE->REG_100H;
        OutData_PubKey[39] = SCE->REG_100H;
        OutData_PubKey[40] = SCE->REG_100H;
        OutData_PubKey[41] = SCE->REG_100H;
        OutData_PubKey[42] = SCE->REG_100H;
        OutData_PubKey[43] = SCE->REG_100H;
        OutData_PubKey[44] = SCE->REG_100H;
        OutData_PubKey[45] = SCE->REG_100H;
        OutData_PubKey[46] = SCE->REG_100H;
        OutData_PubKey[47] = SCE->REG_100H;
        OutData_PubKey[48] = SCE->REG_100H;
        OutData_PubKey[49] = SCE->REG_100H;
        OutData_PubKey[50] = SCE->REG_100H;
        OutData_PubKey[51] = SCE->REG_100H;
        OutData_PubKey[52] = SCE->REG_100H;
        OutData_PubKey[53] = SCE->REG_100H;
        OutData_PubKey[54] = SCE->REG_100H;
        OutData_PubKey[55] = SCE->REG_100H;
        OutData_PubKey[56] = SCE->REG_100H;
        OutData_PubKey[57] = SCE->REG_100H;
        OutData_PubKey[58] = SCE->REG_100H;
        OutData_PubKey[59] = SCE->REG_100H;
        OutData_PubKey[60] = SCE->REG_100H;
        OutData_PubKey[61] = SCE->REG_100H;
        OutData_PubKey[62] = SCE->REG_100H;
        OutData_PubKey[63] = SCE->REG_100H;
        HW_SCE_p_func100(0xbfc6d200U, 0x18e2c977U, 0xd859db6cU, 0x5abd8659U);
        SCE->REG_E0H = 0x810101c0U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKey[64] = SCE->REG_100H;
        HW_SCE_p_func100(0xea5f5baaU, 0xfd08e672U, 0xe7b9ba08U, 0x2d526356U);
        SCE->REG_104H = 0x00003f61U;
        SCE->REG_B0H = 0x00000f00U;
        SCE->REG_A4H = 0x42f097bfU;
        SCE->REG_00H = 0x00013103U;
        SCE->REG_2CH = 0x00000010U;
        for (iLoop = 68; iLoop < 132 ; iLoop=iLoop+4)
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
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_04H = 0x00000302U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKey[0] = SCE->REG_100H;
        OutData_PrivKey[1] = SCE->REG_100H;
        OutData_PrivKey[2] = SCE->REG_100H;
        OutData_PrivKey[3] = SCE->REG_100H;
        OutData_PrivKey[4] = SCE->REG_100H;
        OutData_PrivKey[5] = SCE->REG_100H;
        OutData_PrivKey[6] = SCE->REG_100H;
        OutData_PrivKey[7] = SCE->REG_100H;
        OutData_PrivKey[8] = SCE->REG_100H;
        OutData_PrivKey[9] = SCE->REG_100H;
        OutData_PrivKey[10] = SCE->REG_100H;
        OutData_PrivKey[11] = SCE->REG_100H;
        OutData_PrivKey[12] = SCE->REG_100H;
        OutData_PrivKey[13] = SCE->REG_100H;
        OutData_PrivKey[14] = SCE->REG_100H;
        OutData_PrivKey[15] = SCE->REG_100H;
        OutData_PrivKey[16] = SCE->REG_100H;
        OutData_PrivKey[17] = SCE->REG_100H;
        OutData_PrivKey[18] = SCE->REG_100H;
        OutData_PrivKey[19] = SCE->REG_100H;
        OutData_PrivKey[20] = SCE->REG_100H;
        OutData_PrivKey[21] = SCE->REG_100H;
        OutData_PrivKey[22] = SCE->REG_100H;
        OutData_PrivKey[23] = SCE->REG_100H;
        OutData_PrivKey[24] = SCE->REG_100H;
        OutData_PrivKey[25] = SCE->REG_100H;
        OutData_PrivKey[26] = SCE->REG_100H;
        OutData_PrivKey[27] = SCE->REG_100H;
        OutData_PrivKey[28] = SCE->REG_100H;
        OutData_PrivKey[29] = SCE->REG_100H;
        OutData_PrivKey[30] = SCE->REG_100H;
        OutData_PrivKey[31] = SCE->REG_100H;
        OutData_PrivKey[32] = SCE->REG_100H;
        OutData_PrivKey[33] = SCE->REG_100H;
        OutData_PrivKey[34] = SCE->REG_100H;
        OutData_PrivKey[35] = SCE->REG_100H;
        OutData_PrivKey[36] = SCE->REG_100H;
        OutData_PrivKey[37] = SCE->REG_100H;
        OutData_PrivKey[38] = SCE->REG_100H;
        OutData_PrivKey[39] = SCE->REG_100H;
        OutData_PrivKey[40] = SCE->REG_100H;
        OutData_PrivKey[41] = SCE->REG_100H;
        OutData_PrivKey[42] = SCE->REG_100H;
        OutData_PrivKey[43] = SCE->REG_100H;
        OutData_PrivKey[44] = SCE->REG_100H;
        OutData_PrivKey[45] = SCE->REG_100H;
        OutData_PrivKey[46] = SCE->REG_100H;
        OutData_PrivKey[47] = SCE->REG_100H;
        OutData_PrivKey[48] = SCE->REG_100H;
        OutData_PrivKey[49] = SCE->REG_100H;
        OutData_PrivKey[50] = SCE->REG_100H;
        OutData_PrivKey[51] = SCE->REG_100H;
        OutData_PrivKey[52] = SCE->REG_100H;
        OutData_PrivKey[53] = SCE->REG_100H;
        OutData_PrivKey[54] = SCE->REG_100H;
        OutData_PrivKey[55] = SCE->REG_100H;
        OutData_PrivKey[56] = SCE->REG_100H;
        OutData_PrivKey[57] = SCE->REG_100H;
        OutData_PrivKey[58] = SCE->REG_100H;
        OutData_PrivKey[59] = SCE->REG_100H;
        OutData_PrivKey[60] = SCE->REG_100H;
        OutData_PrivKey[61] = SCE->REG_100H;
        OutData_PrivKey[62] = SCE->REG_100H;
        OutData_PrivKey[63] = SCE->REG_100H;
        HW_SCE_p_func101(0xd097e80dU, 0x8c2ccf6eU, 0x232872d5U, 0xe1cd1cb8U);
    }
    HW_SCE_p_func102(0x38178303U, 0x237b9524U, 0xe9505df9U, 0x646a3b4aU);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p2b_r3.prc
***********************************************************************************************************************/
