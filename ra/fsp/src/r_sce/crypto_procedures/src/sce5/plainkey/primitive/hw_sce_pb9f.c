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

fsp_err_t HW_SCE_Aes256XtsEncryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    HW_SCE_func001(0xe3d7cd5fU, 0xfe4d305bU, 0x10ca5e65U, 0xf453caccU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0x99091361U, 0x1488f34aU, 0x30a16f63U, 0xcec8b940U);
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
            HW_SCE_func002(0x3566a77fU, 0x3f7e8a14U, 0x94e39633U, 0x192b2e5dU);
        }
        else
        {
            HW_SCE_func002(0x531b7461U, 0xdac9105fU, 0x50a1d923U, 0xb0c66d32U);
        }
        HW_SCE_func001(0x20f0967fU, 0x5bccc8dbU, 0x9828ed15U, 0x5260c813U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x010b0644U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_func003(0x825432f1U, 0x95184069U, 0x2388bdf5U, 0xd5ed4928U);
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
        HW_SCE_func001(0x79902488U, 0x90ac2eafU, 0x55780219U, 0x37904342U);
        SCE->REG_E0H = 0x81010020U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_func001(0x4975b4acU, 0x8226d9ddU, 0x491df082U, 0x853efa8bU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000020U;
        SCE->REG_A4H = 0x00008daeU;
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
        HW_SCE_func001(0x26d5c2bcU, 0xffda44beU, 0x1ca188bcU, 0xd045c96fU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_1CH = 0x002d0000U;
            HW_SCE_func001(0x573c4303U, 0x29ee731eU, 0xfa9f417dU, 0xeec5611aU);
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
                HW_SCE_func002(0x5c93420eU, 0x625fa6d5U, 0xd92b5d00U, 0x5488c446U);
            }
            else
            {
                HW_SCE_func002(0x7f90ca60U, 0x4da9a2ebU, 0x9d1f39bbU, 0x95cdb4b2U);
            }
            HW_SCE_func001(0xe59e2853U, 0x9d9e56f0U, 0xfbafdeeaU, 0x35934401U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x010b0644U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_func003(0xbe820c8fU, 0x2c8b1dc6U, 0xec1af11dU, 0xda87d583U);
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
            HW_SCE_func001(0x7915accdU, 0x7ab62473U, 0x775f9db6U, 0x45dc8e36U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func001(0x4de076b9U, 0xb10ac7b9U, 0x4e697c78U, 0x4a57cbe5U);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x00008dadU;
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
                    HW_SCE_func002(0xa62c1099U, 0x3d72cd2bU, 0xc31de1feU, 0x4bee9f13U);
                }
                HW_SCE_func001(0xb02d577bU, 0x9fd9e562U, 0xb281ff0cU, 0x997d8400U);
                SCE->REG_ECH = 0x38000c21U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x0000b460U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x00008dadU;
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
                    HW_SCE_func002(0xac8ef2b1U, 0xc2fe571cU, 0x1a5adf4eU, 0xf27a67b2U);
                }
                HW_SCE_func001(0xe8576321U, 0x972e49f3U, 0x05af01efU, 0x19f4699bU);
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
                HW_SCE_func002(0x8a7b089fU, 0xd21e6af5U, 0x28dce7b2U, 0xb264a678U);
            }
            HW_SCE_func001(0xfb595513U, 0x993b1bfbU, 0xb229e17fU, 0x7f506d0bU);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x010b0644U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_func003(0xdea4c319U, 0x1870122dU, 0x567cba9dU, 0x24e3e4d0U);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_pb9f.prc
***********************************************************************************************************************/
