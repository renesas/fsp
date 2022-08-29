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

fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub(uint32_t *InData_Text, uint32_t *InData_DataALen, uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_DataT)
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
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_E0H = 0x80820001U;
    SCE->REG_104H = 0x00000168U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[0];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[1];
    SCE->REG_ECH = 0x0000b440U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x00003822U;
    SCE->REG_ECH = 0x0000a440U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003802U;
    SCE->REG_ECH = 0x0000b440U;
    SCE->REG_ECH = 0x0000007FU;
    SCE->REG_ECH = 0x0000b460U;
    SCE->REG_ECH = 0xFFFFFF00U;
    SCE->REG_ECH = 0x0c002860U;
    SCE->REG_ECH = 0x04a02841U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_func100(0x37380fafU, 0x6a1923dfU, 0x5dbe5005U, 0xcf530ca8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b4c0U;
        SCE->REG_ECH = 0x00000018U;
        SCE->REG_ECH = 0x000038e6U;
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
        HW_SCE_func102(0x6bc70a28U, 0xf377996eU, 0x85a71619U, 0x8c6da9fcU);
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
        SCE->REG_ECH = 0x00036800U;
        SCE->REG_ECH = 0x08008c00U;
        SCE->REG_ECH = 0x0000000fU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func100(0x0633f8ecU, 0xf54e0ca9U, 0x2e8fa986U, 0x6d476adfU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func100(0x283d9633U, 0xed08fafeU, 0x76748c0dU, 0xb4ff6c84U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_B0H = 0x40000020U;
            SCE->REG_A4H = 0x000086bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_E0H = 0x80840001U;
            SCE->REG_00H = 0x00008113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00000863U;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
            {
                SCE->REG_ECH = 0x3c002860U;
                SCE->REG_ECH = 0x12003c23U;
                SCE->REG_ECH = 0x00002c60U;
            }
            SCE->REG_A4H = 0x00000885U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_E0H = 0x81840001U;
            SCE->REG_00H = 0x00004813U;
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
            OutData_Text[0] = SCE->REG_100H;
            OutData_Text[1] = SCE->REG_100H;
            OutData_Text[2] = SCE->REG_100H;
            OutData_Text[3] = SCE->REG_100H;
            HW_SCE_func101(0xcfec7804U, 0x9caa2c9aU, 0x82659f98U, 0x29c67ecdU);
        }
        HW_SCE_func100(0x88089f6aU, 0xd164529aU, 0xb47dc1ddU, 0xd3b59ccaU);
        SCE->REG_104H = 0x00000164U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_DataALen[0];
        SCE->REG_100H = InData_DataALen[1];
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_E0H = 0x81820001U;
        SCE->REG_00H = 0x0000580bU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_74H_b.B18)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001600U;
        SCE->REG_74H = 0x00000000U;
        SCE->REG_A4H = 0x00040805U;
        SCE->REG_E0H = 0x81040080U;
        SCE->REG_00H = 0x00001813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_B0H = 0x40000020U;
        SCE->REG_A4H = 0x000086bdU;
        SCE->REG_00H = 0x00001513U;
        SCE->REG_74H = 0x00000008U;
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
        OutData_DataT[0] = SCE->REG_100H;
        OutData_DataT[1] = SCE->REG_100H;
        OutData_DataT[2] = SCE->REG_100H;
        OutData_DataT[3] = SCE->REG_100H;
        SCE->REG_ECH = 0x0000b4c0U;
        SCE->REG_ECH = 0x00000018U;
        SCE->REG_ECH = 0x000038e6U;
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
        HW_SCE_func102(0x1d6e9f09U, 0x3319427aU, 0xadeae2b3U, 0x65c8dcedU);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_p34f.prc
***********************************************************************************************************************/
