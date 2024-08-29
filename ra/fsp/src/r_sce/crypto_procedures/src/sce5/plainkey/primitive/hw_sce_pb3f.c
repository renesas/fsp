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

fsp_err_t HW_SCE_Aes128XtsEncryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    HW_SCE_func001(0xada7a2a7U, 0x3c06c766U, 0xcee96d8cU, 0xbb06f9afU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0x20c968f6U, 0x7ca4814cU, 0x7273f13aU, 0x569a4247U);
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
            HW_SCE_func002(0xef49cf67U, 0x79b08e3fU, 0x0f25d451U, 0x920ba087U);
        }
        else
        {
            HW_SCE_func002(0x16103be5U, 0x18f5fa4cU, 0xd1e03853U, 0xaea3c1f5U);
        }
        HW_SCE_func003(0x4ddf8916U, 0x048eb860U, 0xc424455bU, 0xaabb9316U);
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
        HW_SCE_func001(0x79fc81b5U, 0x059e6c78U, 0xf0460d58U, 0x5a190490U);
        SCE->REG_E0H = 0x81010020U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_func001(0xc195e91dU, 0x6f1bf5e5U, 0x09713592U, 0xce791577U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x00000020U;
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
        HW_SCE_func001(0x6ccff8f0U, 0x6a9b3933U, 0x4a1440c8U, 0x4c71a2e3U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_1CH = 0x002d0000U;
            HW_SCE_func001(0xd0bae410U, 0x4d1061c6U, 0xf751cda8U, 0x94c38a99U);
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
                HW_SCE_func002(0xa4668cddU, 0xe7c37c21U, 0x705c7557U, 0xa8f88eb4U);
            }
            else
            {
                HW_SCE_func002(0x4f1c669eU, 0x21ea31d5U, 0x1e96f4c1U, 0x3ab4e6b8U);
            }
            HW_SCE_func003(0x38f4dbbaU, 0x93ad1091U, 0x47cf57e0U, 0x7f78ca80U);
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
            HW_SCE_func001(0x211f4540U, 0xf8091d27U, 0xc3bb854cU, 0x0b847558U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func001(0xd9e0ddd6U, 0x4e7f16a9U, 0xa5de5dacU, 0xc5d2ef87U);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x00000020U;
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
                    HW_SCE_func002(0x3dee1511U, 0xde3b88feU, 0x2e4c5e9aU, 0x2105aeb3U);
                }
                HW_SCE_func001(0x16223a72U, 0x70c9e73eU, 0x621cf19dU, 0xe6a1dabfU);
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
                SCE->REG_B0H = 0x00000020U;
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
                    HW_SCE_func002(0x5fd415a4U, 0x053385b5U, 0x1d6211daU, 0xb850974aU);
                }
                HW_SCE_func001(0x309fc174U, 0x83ac880bU, 0xf4b95fc3U, 0x5bb8b140U);
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
                HW_SCE_func002(0x35e1960dU, 0xd45960b2U, 0xe6dadf8cU, 0x914fbfa7U);
            }
            HW_SCE_func003(0xc5d51ffbU, 0xa4de3279U, 0x9411dddbU, 0xf093895eU);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_pb3f.prc
***********************************************************************************************************************/
