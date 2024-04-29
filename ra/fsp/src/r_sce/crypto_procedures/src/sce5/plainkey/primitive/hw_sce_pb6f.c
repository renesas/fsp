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

fsp_err_t HW_SCE_Aes128XtsDecryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    HW_SCE_func001(0x04a1a3adU, 0xb7ae1bb2U, 0x96919b7aU, 0xae7bca18U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0xd8e7b9ceU, 0x8e48f4d4U, 0x0cf65781U, 0xcbc06fdfU);
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
            HW_SCE_func002(0x494c4865U, 0x975f1863U, 0x1dee465bU, 0x2fe166ecU);
        }
        else
        {
            HW_SCE_func002(0xd2c2702fU, 0xa95166c0U, 0xb41110eeU, 0x06c2a737U);
        }
        HW_SCE_func003(0x64e39d0eU, 0xbaaacb50U, 0x5002b105U, 0x99165728U);
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
        HW_SCE_func001(0x78f0a60aU, 0x5719b14bU, 0xa4385167U, 0x9195283fU);
        SCE->REG_E0H = 0x81010020U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_func001(0x621d84bbU, 0xe8c8553fU, 0x8ec52b15U, 0xa850847eU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x00000020U;
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
        HW_SCE_func001(0x6af85827U, 0x986f2951U, 0xcd494103U, 0x4f332451U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_1CH = 0x002d0000U;
            HW_SCE_func001(0x1a02ab9eU, 0xa489ea6dU, 0x2e2cd1d5U, 0xbcb840cdU);
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
                HW_SCE_func002(0x1abad95eU, 0x2a5721e1U, 0x209eafb9U, 0x182c4fa7U);
            }
            else
            {
                HW_SCE_func002(0x7dc66de0U, 0x53ae55dbU, 0x2160bba0U, 0x7d5c0f1eU);
            }
            HW_SCE_func003(0x9a611b88U, 0x9eb9266eU, 0xbadf9271U, 0x5c17d597U);
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
            HW_SCE_func001(0x1369afc1U, 0xe520ca03U, 0x9c86ba8aU, 0x58d9062bU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func001(0x56512253U, 0x591af8aaU, 0x317d00e3U, 0x9b083202U);
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00050604U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000051U;
                SCE->REG_B0H = 0x00000020U;
                SCE->REG_A4H = 0x0000cd2cU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x00000020U;
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
                    HW_SCE_func002(0xd677f598U, 0xd2e09b40U, 0x039486f9U, 0xb04463deU);
                }
                HW_SCE_func001(0xea307e71U, 0x053d7261U, 0x15a2c000U, 0xd5f6b634U);
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
                SCE->REG_B0H = 0x00000020U;
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
                    HW_SCE_func002(0x790cf255U, 0xd2a06165U, 0xc0da2c52U, 0x9db4aba4U);
                }
                HW_SCE_func001(0xdcf8b5a3U, 0xc198b5caU, 0x4bc15577U, 0xb0cd47f1U);
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
                HW_SCE_func002(0xf55d04efU, 0x65c1ba06U, 0x46edae79U, 0x5919b454U);
            }
            HW_SCE_func003(0x28a11de3U, 0x4dc4fddaU, 0xfdada47dU, 0x3f895a0eU);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_pb6f.prc
***********************************************************************************************************************/
