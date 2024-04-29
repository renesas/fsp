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

fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_DataALen, uint32_t *OutData_Text, uint32_t *OutData_DataT)
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
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x80820001U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_104H = 0x00000168U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[0];
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[1];
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000b440U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00003822U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000a440U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00003802U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000b440U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000007FU;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000b460U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0xFFFFFF00U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0c002860U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x04a02841U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_func001(0x1dd8c755U, 0xed55b6b7U, 0x900b5ee5U, 0x1001c3d4U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func003(0x875f4780U, 0x8e6d834eU, 0xa9f0c940U, 0x9381fd93U);
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
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x08008c00U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000000fU;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func001(0x68dd183cU, 0x436261a3U, 0xb957edc3U, 0x0d88b76dU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func001(0xf5f71d06U, 0x2290dc7cU, 0xda61f11bU, 0x74795eefU);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_B0H = 0x00000020U;
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
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x80840001U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00008113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00000863U;
            SCE->REG_1D0H = 0x00000000U;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
            {
                SCE->REG_ECH = 0x3c002860U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x12003c23U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00002c60U;
                SCE->REG_1D0H = 0x00000000U;
            }
            SCE->REG_A4H = 0x00000885U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x81840001U;
            SCE->REG_1D0H = 0x00000000U;
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
            HW_SCE_func002(0x4cf4f5f4U, 0x0ca3f52bU, 0x69a71dc9U, 0x3bc5d3f8U);
        }
        HW_SCE_func001(0x28215800U, 0xc743b779U, 0xdaeed44fU, 0x3f05cc51U);
        SCE->REG_104H = 0x00000164U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_DataALen[0];
        SCE->REG_100H = InData_DataALen[1];
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x81820001U;
        SCE->REG_1D0H = 0x00000000U;
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
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_00H = 0x00001813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_B0H = 0x00000020U;
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
        HW_SCE_func003(0x12eb1e99U, 0x7e8f8f75U, 0x3a56763dU, 0x77775791U);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p34.prc
***********************************************************************************************************************/
