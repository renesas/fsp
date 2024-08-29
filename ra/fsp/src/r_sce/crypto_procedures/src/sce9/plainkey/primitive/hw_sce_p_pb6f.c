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
    HW_SCE_p_func100(0xca624a8dU, 0xdadff4e7U, 0x2a86a494U, 0xbafc5094U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xd37a0b7cU, 0xc42aa712U, 0x183f3f79U, 0x3b712616U);
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
        HW_SCE_p_func100(0x1565838dU, 0xc2d03568U, 0x6ad73cfbU, 0x860aef7fU);
        SCE->REG_E0H = 0x810103c0U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_p_func100(0xf539e42bU, 0x46f05f8dU, 0xfaaa2b74U, 0xf2bd30b3U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x00000020U;
        SCE->REG_A4H = 0x0000cda6U;
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
        HW_SCE_p_func100(0xbbc12c23U, 0x0cfb3332U, 0x1ac38658U, 0x5528d3dcU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xb0f2e41aU, 0x8539baf3U, 0x13fe00e9U, 0x40a8cdbeU);
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
            HW_SCE_p_func100(0x8b26e6abU, 0x4d0c31c0U, 0xf8a616f6U, 0x2c8001f6U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func100(0x6b7ed0d5U, 0xf35452ddU, 0xa81e9a1aU, 0xd5e7e882U);
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80040140U;
                SCE->REG_00H = 0x00008113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000051U;
                SCE->REG_B0H = 0x00000020U;
                SCE->REG_A4H = 0x0000cd24U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x00000020U;
                SCE->REG_A4H = 0x0000cda5U;
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
                    HW_SCE_p_func101(0xcddc449bU, 0x4e86b813U, 0x9f7d8b1fU, 0xa333ba6fU);
                }
                HW_SCE_p_func100(0x630cb437U, 0xe87d589dU, 0x42e79c01U, 0xc3d8d05eU);
                SCE->REG_ECH = 0x38000fdeU;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_A4H = 0x00040805U;
                SCE->REG_E0H = 0x81040140U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_B0H = 0x00000020U;
                SCE->REG_A4H = 0x0000cda5U;
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
                    HW_SCE_p_func101(0x3ffc373fU, 0x6967e754U, 0xec3ec0dbU, 0x2f0c1b7eU);
                }
                HW_SCE_p_func100(0x9f55dc28U, 0xe577c2f2U, 0x87e6055aU, 0xa66aecd0U);
                SCE->REG_ECH = 0x38000d29U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
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
                HW_SCE_p_func101(0x5c4e6f65U, 0x36ef7d88U, 0x846364a9U, 0xfe581a43U);
            }
            HW_SCE_p_func102(0x642757a2U, 0x712ec770U, 0x3bde479bU, 0x19e636faU);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pb6f.prc
***********************************************************************************************************************/
