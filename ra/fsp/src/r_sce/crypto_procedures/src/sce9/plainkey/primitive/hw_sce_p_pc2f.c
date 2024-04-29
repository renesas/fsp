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
    HW_SCE_p_func100(0xfae4674dU, 0xd71a8d44U, 0xfda7fc43U, 0xe2f0a49bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xadffe2f2U, 0x15ef16c2U, 0x7cccbab5U, 0x4476dc7cU);
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
        HW_SCE_p_func100(0x18ed9061U, 0x9f68c4f2U, 0x0ca876ceU, 0xbab18046U);
        SCE->REG_E0H = 0x810103c0U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_p_func100(0x15720916U, 0x4928aec9U, 0x9aec1c5cU, 0x2a99bea9U);
        SCE->REG_104H = 0x000000b1U;
        SCE->REG_B0H = 0x40000020U;
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
        HW_SCE_p_func100(0xdfe9ad83U, 0x17fc5993U, 0x5e9d63e7U, 0x6c1c43fbU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x7c1fd1a2U, 0x724ba216U, 0x1618d36cU, 0xb919c74bU);
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
            HW_SCE_p_func100(0xf699d6ecU, 0xc3789eafU, 0xc2619429U, 0x11f98a28U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func100(0x7e1f6a4cU, 0x5944e041U, 0x8718c3e6U, 0x5a5db474U);
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
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x0000cd24U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x40000020U;
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
                    HW_SCE_p_func101(0x779c56b5U, 0x4650dd64U, 0xe8ad07e3U, 0xae4a4ddcU);
                }
                HW_SCE_p_func100(0x80546670U, 0x081ae0e5U, 0x9a758775U, 0x3da1afa6U);
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
                SCE->REG_B0H = 0x40000020U;
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
                    HW_SCE_p_func101(0x29a06074U, 0xbdcbb2c4U, 0x5219eb7eU, 0x6e6e6eefU);
                }
                HW_SCE_p_func100(0x23f0dc1eU, 0x8497a1d5U, 0x8b5eaf23U, 0x8e25429eU);
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
                HW_SCE_p_func101(0xffd6f98aU, 0xeb205568U, 0xb0b90841U, 0x1a612f24U);
            }
            HW_SCE_p_func102(0xce7b9474U, 0x78b1de12U, 0xb22a31c4U, 0xc86ac379U);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pc2f.prc
***********************************************************************************************************************/
