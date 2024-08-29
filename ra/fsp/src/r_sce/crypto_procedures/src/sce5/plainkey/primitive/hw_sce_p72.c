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

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub(const uint32_t *InData_TextLen, const uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t *OutData_MAC)
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
    HW_SCE_func001(0xbfedbb70U, 0x35182d4bU, 0xb2629fb6U, 0x94cab2abU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0xd82804c6U, 0x8706f8e8U, 0xab5f2a5cU, 0xdb64b1c5U);
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
            HW_SCE_func002(0xc0be7778U, 0x6c18ba79U, 0x1566ea97U, 0x478a36c6U);
        }
        else
        {
            HW_SCE_func002(0xd36e91d0U, 0xa5f26c5aU, 0x7417b4b8U, 0x65d0d7d7U);
        }
        HW_SCE_func003(0xd2dc8619U, 0x9ec5a34bU, 0x8e45c32cU, 0x9adc9855U);
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
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_1D0H = 0x00000000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_TextLen[0];
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00008c00U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000000fU;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x38008800U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func001(0x8f0494d6U, 0x8334273dU, 0x81a350a5U, 0x902b59baU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func001(0x7d96daf0U, 0xf6ca0690U, 0xf491df6eU, 0xfe413cc6U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00e006bdU;
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
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x81840001U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_04H = 0x00000612U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[0] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[1] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[2] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[3] = SCE->REG_100H;
            HW_SCE_func002(0x252f8db7U, 0x72b6eb6cU, 0xaa304b08U, 0x67357b0cU);
        }
        else
        {
            HW_SCE_func002(0x90e12ea7U, 0x5ec40150U, 0x9adb4738U, 0x6cc52e90U);
        }
        HW_SCE_func001(0x3efa62bfU, 0x3895f0daU, 0xf1ec52c8U, 0x5898ef8fU);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000e84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_A4H = 0x000009cdU;
        SCE->REG_00H = 0x00001113U;
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
        OutData_MAC[0] = SCE->REG_100H;
        OutData_MAC[1] = SCE->REG_100H;
        OutData_MAC[2] = SCE->REG_100H;
        OutData_MAC[3] = SCE->REG_100H;
        HW_SCE_func003(0x6d40063eU, 0x1d491143U, 0x1d451713U, 0x1355d1a3U);
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
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p72.prc
***********************************************************************************************************************/
