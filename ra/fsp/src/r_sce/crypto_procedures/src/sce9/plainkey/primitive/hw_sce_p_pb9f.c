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
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextBitLen[0];
    SCE->REG_ECH = 0x000037c0U;
    SCE->REG_ECH = 0x00076bdeU;
    SCE->REG_ECH = 0x00026fdeU;
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_ECH = 0x38008c00U;
    SCE->REG_ECH = 0x0000007fU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x1000d3e0U;
    SCE->REG_ECH = 0x2000abc0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38000fffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0xe915e6d7U, 0x1d65d1c4U, 0x8ff5b85bU, 0xa4526103U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xe3234672U, 0x27bcdd00U, 0xcdf184b4U, 0xc0195e81U);
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
        HW_SCE_p_func100(0xd572f89fU, 0x8c16b8adU, 0xc63fc14eU, 0x5b2dafdcU);
        SCE->REG_E0H = 0x810103c0U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_p_func100(0xe22fe9a3U, 0x19b8ff1dU, 0x41e0e0ccU, 0x7f45f38aU);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000020U;
        SCE->REG_A4H = 0x00008da6U;
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
        HW_SCE_p_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func100(0xbb591048U, 0x64c28870U, 0x5398d50dU, 0x5e3ab165U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x3f5592d3U, 0x4bcce341U, 0x90e9f640U, 0x3be1cb9aU);
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
            SCE->REG_ECH = 0x0000007fU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            HW_SCE_p_func100(0x1eec6f52U, 0x5e74c52aU, 0x1b2d8528U, 0x000c9a2dU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x00008da5U;
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
                SCE->REG_E0H = 0x80840006U;
                SCE->REG_00H = 0x00008113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_104H = 0x00000368U;
                SCE->REG_E0H = 0x80840007U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+4 + 0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+5 + 0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+6 + 0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_Text[iLoop+7 + 0];
                SCE->REG_ECH = 0x0000b4a0U;
                SCE->REG_ECH = 0x00000004U;
                SCE->REG_ECH = 0x00003500U;
                SCE->REG_ECH = 0x00036908U;
                SCE->REG_ECH = 0x00008d00U;
                SCE->REG_ECH = 0x0000000cU;
                SCE->REG_ECH = 0x000024c8U;
                SCE->REG_ECH = 0x000024e8U;
                SCE->REG_ECH = 0x00003826U;
                SCE->REG_ECH = 0x00003847U;
                SCE->REG_ECH = 0x00003460U;
                SCE->REG_ECH = 0x00008c60U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x0000b480U;
                SCE->REG_ECH = 0xffffffffU;
                SCE->REG_ECH = 0x00004403U;
                SCE->REG_ECH = 0x00007484U;
                SCE->REG_ECH = 0x00000c24U;
                SCE->REG_ECH = 0x00001484U;
                SCE->REG_ECH = 0x00000c44U;
                SCE->REG_ECH = 0x00001041U;
                SCE->REG_ECH = 0x00003c47U;
                SCE->REG_ECH = 0x000037e0U;
                SCE->REG_ECH = 0x00008fe0U;
                SCE->REG_ECH = 0x0000007fU;
                SCE->REG_ECH = 0x38008fe0U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x1000a7e0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000080U;
                SCE->REG_ECH = 0x00002bdfU;
                SCE->REG_ECH = 0x00056bdeU;
                SCE->REG_ECH = 0x0000353eU;
                HW_SCE_p_func100(0x4c3b7f8eU, 0x431841b4U, 0xcf3c2a19U, 0x475aee98U);
                SCE->REG_E0H = 0x810103c0U;
                SCE->REG_04H = 0x00000607U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = change_endian_long(SCE->REG_100H);
                for (jLoop = 0; jLoop < (int32_t)S_RAM[0]; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x000024c5U;
                    SCE->REG_ECH = 0x000024e5U;
                    SCE->REG_ECH = 0x00003ba6U;
                    SCE->REG_ECH = 0x00003fa7U;
                    SCE->REG_ECH = 0x000033c0U;
                    HW_SCE_p_func101(0x951a9435U, 0xe4953a42U, 0x053c0042U, 0x3e4cfe4aU);
                }
                SCE->REG_ECH = 0x38000fdeU;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000010U;
                HW_SCE_p_func100(0xc7c98e4dU, 0x464f55caU, 0x7a20898fU, 0xe1485eb3U);
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x00008da5U;
                SCE->REG_E0H = 0x81840007U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000113U;
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
                SCE->REG_ECH = 0x000024c8U;
                SCE->REG_ECH = 0x00003826U;
                SCE->REG_ECH = 0x00000c24U;
                SCE->REG_ECH = 0x00003c26U;
                SCE->REG_ECH = 0x00000bffU;
                for (jLoop = 0; jLoop < (int32_t)S_RAM[0]; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x000024c5U;
                    SCE->REG_ECH = 0x00003fe6U;
                    SCE->REG_ECH = 0x00003120U;
                    HW_SCE_p_func101(0x88630b84U, 0x09e52004U, 0xa0f8a19fU, 0x3e97a8a7U);
                }
                SCE->REG_ECH = 0x38000d29U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                HW_SCE_p_func100(0xb7ce9444U, 0x95bb5d55U, 0xa6254961U, 0x786d3859U);
                SCE->REG_ECH = 0x000008c6U;
                SCE->REG_E0H = 0x81840006U;
                SCE->REG_04H = 0x00000613U;
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
                HW_SCE_p_func101(0x31dbc936U, 0xd6f4103cU, 0xb55ba7e0U, 0x9f882e30U);
            }
            HW_SCE_p_func102(0x1af1cb45U, 0xcbab59ffU, 0x4010b50eU, 0x0ad6f321U);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pb9f.prc
***********************************************************************************************************************/
