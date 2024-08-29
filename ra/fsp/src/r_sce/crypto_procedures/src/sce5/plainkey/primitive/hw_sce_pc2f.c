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

fsp_err_t HW_SCE_Aes256XtsDecryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextBitLen[0];
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00003420U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00076821U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00026c21U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x000008c6U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x38008c00U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000007fU;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x1000d0c0U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x2000a820U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x38000cc6U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_func001(0xce9accb2U, 0xcdcc26e2U, 0xd91fa9edU, 0xab15a636U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0x22df0fb7U, 0xc2a78deaU, 0xc78df098U, 0x2fd15e14U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_00H = 0x00000113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0x1fd615f9U, 0xf33df947U, 0xb9b40855U, 0x36adf76fU);
        }
        else
        {
            HW_SCE_func002(0x4dccb1e1U, 0xbd1f45faU, 0xc5c33d20U, 0x400b0df4U);
        }
        HW_SCE_func001(0xec71656cU, 0xa352f213U, 0xd2c9122aU, 0x46093feaU);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x010b0644U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_func003(0xaaf565b6U, 0xa14023eeU, 0x0a9561e1U, 0x10c72774U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_func001(0x5ae5c7a0U, 0xd1c87403U, 0xf1bb78f0U, 0x4ae3820fU);
        SCE->REG_E0H = 0x81010020U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_func001(0xa6de294cU, 0x6e2d19e0U, 0xf8f5bd40U, 0x1918fceeU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000020U;
        SCE->REG_A4H = 0x0000cdaeU;
        SCE->REG_04H = 0x0000c100U;
        iLoop = 0;
            if(S_RAM[0] >= 4) 
        {
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            for (iLoop = 4; iLoop < S_RAM[0]; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop + 0];
                SCE->REG_100H = InData_Text[iLoop + 1];
                SCE->REG_100H = InData_Text[iLoop + 2];
                SCE->REG_100H = InData_Text[iLoop + 3];
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop-4 + 0] = SCE->REG_100H;
                OutData_Text[iLoop-4 + 1] = SCE->REG_100H;
                OutData_Text[iLoop-4 + 2] = SCE->REG_100H;
                OutData_Text[iLoop-4 + 3] = SCE->REG_100H;
            }
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[iLoop-4 + 0] = SCE->REG_100H;
            OutData_Text[iLoop-4 + 1] = SCE->REG_100H;
            OutData_Text[iLoop-4 + 2] = SCE->REG_100H;
            OutData_Text[iLoop-4 + 3] = SCE->REG_100H;
        }
        HW_SCE_func206();
        HW_SCE_func001(0x59ac3e9fU, 0x34ae6ff2U, 0x5ce7e8cdU, 0xb3cd0f1dU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_1CH = 0x002d0000U;
            HW_SCE_func001(0x95e388c1U, 0x8c85dcebU, 0xe27a815dU, 0x5a60e683U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_00H = 0x00000113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_func002(0xf277f06dU, 0x03318561U, 0x1900dfeeU, 0xf2f91da3U);
            }
            else
            {
                HW_SCE_func002(0x3e25783cU, 0x8d1906f6U, 0xae010de0U, 0xde84e80dU);
            }
            HW_SCE_func001(0x2c7d9a60U, 0x1f750dd1U, 0xd01a6b39U, 0x26c7bceaU);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x010b0644U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_func003(0x5007b925U, 0xb5010564U, 0x130075acU, 0x5dd666ffU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_ECH = 0x38008c00U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x0000007fU;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            HW_SCE_func001(0x3a5ffb0eU, 0x7107479aU, 0x75504e7cU, 0x351e41bbU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func001(0xb7b3056eU, 0xe3c02d5bU, 0x7d96a9ecU, 0xe1f61ea8U);
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00050604U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000051U;
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x0000cd2cU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x0000cdadU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop + 0];
                SCE->REG_100H = InData_Text[iLoop + 1];
                SCE->REG_100H = InData_Text[iLoop + 2];
                SCE->REG_100H = InData_Text[iLoop + 3];
                SCE->REG_ECH = 0x000008c6U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_E0H = 0x80840006U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_00H = 0x00008113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b460U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_104H = 0x00000368U;
                SCE->REG_E0H = 0x80840003U;
                SCE->REG_1D0H = 0x00000000U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+4 + 0];
                SCE->REG_1D0H = 0x00000000U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+5 + 0];
                SCE->REG_1D0H = 0x00000000U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+6 + 0];
                SCE->REG_1D0H = 0x00000000U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+7 + 0];
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003440U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00008c40U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000b480U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0xffffffffU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00004402U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00007484U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000034a0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000368a5U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00008ca0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000000cU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000024c5U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00002465U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003826U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003843U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000c24U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00001484U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000c44U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00001041U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003c43U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003440U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00008c40U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000007fU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x38008c40U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x1000a440U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000b420U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000080U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00002822U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00056821U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003401U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_E0H = 0x81010020U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_04H = 0x00000606U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = change_endian_long(SCE->REG_100H);
                for (jLoop = 0; jLoop < (int32_t)S_RAM[0]; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x0000a4c0U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x0000a460U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00003846U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00003c43U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00003020U;
                    SCE->REG_1D0H = 0x00000000U;
                    HW_SCE_func002(0xcb48c703U, 0xee2dc584U, 0xe2638516U, 0xb9d2ef96U);
                }
                HW_SCE_func001(0x721b4e10U, 0xf5d4dc8eU, 0x2083fee8U, 0xc4f55818U);
                SCE->REG_ECH = 0x38000c21U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00040644U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_ECH = 0x0000b460U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x0000cdadU;
                SCE->REG_E0H = 0x81840003U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000112U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop + 0] = SCE->REG_100H;
                OutData_Text[iLoop + 1] = SCE->REG_100H;
                OutData_Text[iLoop + 2] = SCE->REG_100H;
                OutData_Text[iLoop + 3] = SCE->REG_100H;
                SCE->REG_ECH = 0x000008c6U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000024c5U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003826U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000c24U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00003c26U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000842U;
                SCE->REG_1D0H = 0x00000000U;
                for (jLoop = 0; jLoop < (int32_t)S_RAM[0]; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x0000a4c0U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00003c46U;
                    SCE->REG_1D0H = 0x00000000U;
                    SCE->REG_ECH = 0x00003000U;
                    SCE->REG_1D0H = 0x00000000U;
                    HW_SCE_func002(0x470dbb5eU, 0x77fcf121U, 0x82a42003U, 0xf494beccU);
                }
                HW_SCE_func001(0x0b847bfdU, 0xc4c48c6eU, 0xad20a312U, 0x6e3e81c5U);
                SCE->REG_ECH = 0x38000c00U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x000008c6U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_E0H = 0x81840006U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_04H = 0x00000612U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+4 + 0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+5 + 0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+6 + 0] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_Text[iLoop+7 + 0] = SCE->REG_100H;
                HW_SCE_func002(0x8da3c818U, 0x56364771U, 0xee0081e9U, 0x3815eb4cU);
            }
            HW_SCE_func001(0x40750ce0U, 0x171fd58bU, 0x60aac93eU, 0xdabce961U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x010b0644U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_func003(0x98cfbfeeU, 0x4c6ffa00U, 0x97f1a35fU, 0x24761a97U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_pc2f.prc
***********************************************************************************************************************/
