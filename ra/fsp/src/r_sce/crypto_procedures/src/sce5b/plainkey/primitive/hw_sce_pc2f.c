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
    SCE->REG_ECH = 0x00003420U;
    SCE->REG_ECH = 0x00076821U;
    SCE->REG_ECH = 0x00026c21U;
    SCE->REG_ECH = 0x000008c6U;
    SCE->REG_ECH = 0x38008c00U;
    SCE->REG_ECH = 0x0000007fU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x1000d0c0U;
    SCE->REG_ECH = 0x2000a820U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38000cc6U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_func100(0x9f1ad3c7U, 0xa3fa4a6aU, 0x3396b804U, 0xa60bac7cU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func100(0x2c5cb97cU, 0x52b86309U, 0xa3772fd0U, 0x9fa59d56U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x010b0644U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_func102(0x999953abU, 0x3d46bd2cU, 0xc31bc82aU, 0x351b3e6bU);
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
        HW_SCE_func100(0x13b7fe30U, 0x99470ecbU, 0x73fb0091U, 0xcc1422dcU);
        SCE->REG_E0H = 0x81010020U;
        SCE->REG_04H = 0x00000606U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        HW_SCE_func100(0x0c139818U, 0xb1c60822U, 0xd9896ec5U, 0x584bc4adU);
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
        HW_SCE_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_func100(0x119c2ec4U, 0x628ea9ceU, 0xe50ebefcU, 0x40952bd4U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func100(0x752f6284U, 0x2165f522U, 0x05dbf687U, 0xbc616416U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x010b0644U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_func102(0x930c35a5U, 0x851d1f53U, 0x2669c14dU, 0xd087b9c6U);
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
            HW_SCE_func100(0x64ca3a97U, 0x78133f41U, 0x06f8a6f2U, 0x1f2ceea0U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func100(0xbc213d26U, 0xea83d482U, 0x605fceb4U, 0xe586e915U);
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
                SCE->REG_E0H = 0x80840006U;
                SCE->REG_00H = 0x00008113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b460U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_104H = 0x00000368U;
                SCE->REG_E0H = 0x80840003U;
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
                SCE->REG_ECH = 0x00003440U;
                SCE->REG_ECH = 0x00008c40U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x0000b480U;
                SCE->REG_ECH = 0xffffffffU;
                SCE->REG_ECH = 0x00004402U;
                SCE->REG_ECH = 0x00007484U;
                SCE->REG_ECH = 0x000034a0U;
                SCE->REG_ECH = 0x000368a5U;
                SCE->REG_ECH = 0x00008ca0U;
                SCE->REG_ECH = 0x0000000cU;
                SCE->REG_ECH = 0x000024c5U;
                SCE->REG_ECH = 0x00002465U;
                SCE->REG_ECH = 0x00003826U;
                SCE->REG_ECH = 0x00003843U;
                SCE->REG_ECH = 0x00000c24U;
                SCE->REG_ECH = 0x00001484U;
                SCE->REG_ECH = 0x00000c44U;
                SCE->REG_ECH = 0x00001041U;
                SCE->REG_ECH = 0x00003c43U;
                SCE->REG_ECH = 0x00003440U;
                SCE->REG_ECH = 0x00008c40U;
                SCE->REG_ECH = 0x0000007fU;
                SCE->REG_ECH = 0x38008c40U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x1000a440U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_ECH = 0x0000b420U;
                SCE->REG_ECH = 0x00000080U;
                SCE->REG_ECH = 0x00002822U;
                SCE->REG_ECH = 0x00056821U;
                SCE->REG_ECH = 0x00003401U;
                SCE->REG_E0H = 0x81010020U;
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
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_ECH = 0x0000a460U;
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_ECH = 0x00003846U;
                    SCE->REG_ECH = 0x00003c43U;
                    SCE->REG_ECH = 0x00003020U;
                    HW_SCE_func101(0xfbedd59eU, 0xa57d25f5U, 0x85c40796U, 0x9ef260d9U);
                }
                HW_SCE_func100(0x58650db8U, 0x80ad8165U, 0x57e76724U, 0x05e2c34fU);
                SCE->REG_ECH = 0x38000c21U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00040644U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_ECH = 0x0000b460U;
                SCE->REG_ECH = 0x00000010U;
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_A4H = 0x0000cdadU;
                SCE->REG_E0H = 0x81840003U;
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
                SCE->REG_ECH = 0x000024c5U;
                SCE->REG_ECH = 0x00003826U;
                SCE->REG_ECH = 0x00000c24U;
                SCE->REG_ECH = 0x00003c26U;
                SCE->REG_ECH = 0x00000842U;
                for (jLoop = 0; jLoop < (int32_t)S_RAM[0]; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x0000a4c0U;
                    SCE->REG_ECH = 0x00000004U;
                    SCE->REG_ECH = 0x00003c46U;
                    SCE->REG_ECH = 0x00003000U;
                    HW_SCE_func101(0x39a7b534U, 0x872e0cd2U, 0x9512ea80U, 0xd7d75551U);
                }
                HW_SCE_func100(0xf1ed533dU, 0xeaafc24aU, 0x9eb39fbfU, 0xf32ecf93U);
                SCE->REG_ECH = 0x38000c00U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_ECH = 0x000008c6U;
                SCE->REG_E0H = 0x81840006U;
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
                HW_SCE_func101(0x1ad30d99U, 0xb444de05U, 0xc1906ac8U, 0x8bb61113U);
            }
            HW_SCE_func100(0x041d0122U, 0xd678cd0dU, 0xaa89c2beU, 0x6629aa7cU);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x010b0644U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x01000684U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_ECH = 0x0000b4c0U;
            SCE->REG_ECH = 0x00000010U;
            SCE->REG_E0H = 0x80840006U;
            SCE->REG_00H = 0x00008113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func102(0x710fa672U, 0x02c006c9U, 0x23245875U, 0xcd131682U);
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
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_pc2f.prc
***********************************************************************************************************************/
