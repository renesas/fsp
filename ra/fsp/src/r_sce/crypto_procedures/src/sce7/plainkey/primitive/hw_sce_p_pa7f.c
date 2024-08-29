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

fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_MAC)
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
    HW_SCE_p_func100(0x470d2cb1U, 0x16b738d9U, 0x8fddf5afU, 0x81545ec7U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xb29c5e20U, 0x805deec2U, 0xaa036e1bU, 0x222235c7U);
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
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_TextLen[0];
        SCE->REG_ECH = 0x00008c00U;
        SCE->REG_ECH = 0x0000000fU;
        SCE->REG_ECH = 0x38008800U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func100(0x29f34e19U, 0x52a2e9f9U, 0xc8e8929cU, 0xde66f217U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000361U;
            SCE->REG_B0H = 0x40000010U;
            SCE->REG_A4H = 0x00e087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_E0H = 0x80840001U;
            SCE->REG_00H = 0x00008113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_ECH = 0x0000a400U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000080U;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
            {
                SCE->REG_ECH = 0x3c002be0U;
                SCE->REG_ECH = 0x12003c3fU;
                SCE->REG_ECH = 0x00002fe0U;
            }
            HW_SCE_p_func100(0x81d76dc5U, 0x88b8965cU, 0xcedb7e8aU, 0xd95b0f41U);
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_E0H = 0x81840001U;
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
            HW_SCE_p_func101(0xb79f433bU, 0xd3fe8f2aU, 0x6a5195eeU, 0xd44ecb00U);
        }
        else
        {
            HW_SCE_p_func101(0x57d61337U, 0xbcbb1dc0U, 0xb500f5f3U, 0x3799a289U);
        }
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_p_func100(0x6b5ef7f2U, 0xc1a631acU, 0xf9820bd4U, 0xd44f8d7dU);
        SCE->REG_B0H = 0x40000010U;
        SCE->REG_A4H = 0x000089c5U;
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
        HW_SCE_p_func102(0x6a61afe6U, 0x05e3bd11U, 0x75b9b3e5U, 0x2326bcd9U);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_pa7f.prc
***********************************************************************************************************************/
