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

fsp_err_t HW_SCE_Rsa2048ModularExponentDecryptSub(uint32_t *InData_KeyIndex, const uint32_t *InData_Text, uint32_t *OutData_Text)
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
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00005701U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_A4H = 0x200c3b0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_100H = InData_KeyIndex[1];
    SCE->REG_100H = InData_KeyIndex[2];
    SCE->REG_100H = InData_KeyIndex[3];
    SCE->REG_A4H = 0x000c0b0cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x3770f901U);
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x00040804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_28H = 0x00000001U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_00H = 0x00013103U;
    SCE->REG_2CH = 0x00000014U;
    SCE->REG_104H = 0x0000bf61U;
    SCE->REG_B0H = 0x00000f00U;
    SCE->REG_A4H = 0x02f0888fU;
    for(iLoop=4; iLoop<68; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop + 3];
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_E0H = 0x80c00001U;
    SCE->REG_B0H = 0x00000f00U;
    SCE->REG_A4H = 0x00f087bfU;
    SCE->REG_00H = 0x00018103U;
    for(iLoop=68; iLoop<132; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop + 3];
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00013103U;
    SCE->REG_2CH = 0x00000012U;
    SCE->REG_B0H = 0x00000f00U;
    SCE->REG_A4H = 0x00f087bfU;
    for(iLoop=132; iLoop<196; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop + 3];
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000361U;
    SCE->REG_A4H = 0x000007bdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[196];
    SCE->REG_100H = InData_KeyIndex[197];
    SCE->REG_100H = InData_KeyIndex[198];
    SCE->REG_100H = InData_KeyIndex[199];
    SCE->REG_A4H = 0x00900c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x131938b9U, 0x074a9721U, 0xac58b9d9U, 0x6a432bf8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xf2188facU, 0x2b1c10e8U, 0x7f2eae66U, 0xc600299bU);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x437ca108U, 0x97b61504U, 0x4b65f209U, 0x085b5da4U);
        SCE->REG_2CH = 0x00000010U;
        SCE->REG_104H = 0x00003f67U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_Text[0];
        SCE->REG_100H = InData_Text[1];
        SCE->REG_100H = InData_Text[2];
        SCE->REG_100H = InData_Text[3];
        SCE->REG_100H = InData_Text[4];
        SCE->REG_100H = InData_Text[5];
        SCE->REG_100H = InData_Text[6];
        SCE->REG_100H = InData_Text[7];
        SCE->REG_100H = InData_Text[8];
        SCE->REG_100H = InData_Text[9];
        SCE->REG_100H = InData_Text[10];
        SCE->REG_100H = InData_Text[11];
        SCE->REG_100H = InData_Text[12];
        SCE->REG_100H = InData_Text[13];
        SCE->REG_100H = InData_Text[14];
        SCE->REG_100H = InData_Text[15];
        SCE->REG_100H = InData_Text[16];
        SCE->REG_100H = InData_Text[17];
        SCE->REG_100H = InData_Text[18];
        SCE->REG_100H = InData_Text[19];
        SCE->REG_100H = InData_Text[20];
        SCE->REG_100H = InData_Text[21];
        SCE->REG_100H = InData_Text[22];
        SCE->REG_100H = InData_Text[23];
        SCE->REG_100H = InData_Text[24];
        SCE->REG_100H = InData_Text[25];
        SCE->REG_100H = InData_Text[26];
        SCE->REG_100H = InData_Text[27];
        SCE->REG_100H = InData_Text[28];
        SCE->REG_100H = InData_Text[29];
        SCE->REG_100H = InData_Text[30];
        SCE->REG_100H = InData_Text[31];
        SCE->REG_100H = InData_Text[32];
        SCE->REG_100H = InData_Text[33];
        SCE->REG_100H = InData_Text[34];
        SCE->REG_100H = InData_Text[35];
        SCE->REG_100H = InData_Text[36];
        SCE->REG_100H = InData_Text[37];
        SCE->REG_100H = InData_Text[38];
        SCE->REG_100H = InData_Text[39];
        SCE->REG_100H = InData_Text[40];
        SCE->REG_100H = InData_Text[41];
        SCE->REG_100H = InData_Text[42];
        SCE->REG_100H = InData_Text[43];
        SCE->REG_100H = InData_Text[44];
        SCE->REG_100H = InData_Text[45];
        SCE->REG_100H = InData_Text[46];
        SCE->REG_100H = InData_Text[47];
        SCE->REG_100H = InData_Text[48];
        SCE->REG_100H = InData_Text[49];
        SCE->REG_100H = InData_Text[50];
        SCE->REG_100H = InData_Text[51];
        SCE->REG_100H = InData_Text[52];
        SCE->REG_100H = InData_Text[53];
        SCE->REG_100H = InData_Text[54];
        SCE->REG_100H = InData_Text[55];
        SCE->REG_100H = InData_Text[56];
        SCE->REG_100H = InData_Text[57];
        SCE->REG_100H = InData_Text[58];
        SCE->REG_100H = InData_Text[59];
        SCE->REG_100H = InData_Text[60];
        SCE->REG_100H = InData_Text[61];
        SCE->REG_100H = InData_Text[62];
        SCE->REG_100H = InData_Text[63];
        SCE->REG_E0H = 0x00000100U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x000000fcU;
        SCE->REG_18H = 0x00000004U;
        SCE->REG_38H = 0x00000248U;
        SCE->REG_E0H = 0x81c0001fU;
        SCE->REG_00H = 0x00013803U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        SCE->REG_E0H = 0x00000000U;
        HW_SCE_p_func100(0x6ab04ea5U, 0x6745fe00U, 0xd8088d2dU, 0xab4f5601U);
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_04H = 0x00000302U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_Text[0] = SCE->REG_100H;
        OutData_Text[1] = SCE->REG_100H;
        OutData_Text[2] = SCE->REG_100H;
        OutData_Text[3] = SCE->REG_100H;
        OutData_Text[4] = SCE->REG_100H;
        OutData_Text[5] = SCE->REG_100H;
        OutData_Text[6] = SCE->REG_100H;
        OutData_Text[7] = SCE->REG_100H;
        OutData_Text[8] = SCE->REG_100H;
        OutData_Text[9] = SCE->REG_100H;
        OutData_Text[10] = SCE->REG_100H;
        OutData_Text[11] = SCE->REG_100H;
        OutData_Text[12] = SCE->REG_100H;
        OutData_Text[13] = SCE->REG_100H;
        OutData_Text[14] = SCE->REG_100H;
        OutData_Text[15] = SCE->REG_100H;
        OutData_Text[16] = SCE->REG_100H;
        OutData_Text[17] = SCE->REG_100H;
        OutData_Text[18] = SCE->REG_100H;
        OutData_Text[19] = SCE->REG_100H;
        OutData_Text[20] = SCE->REG_100H;
        OutData_Text[21] = SCE->REG_100H;
        OutData_Text[22] = SCE->REG_100H;
        OutData_Text[23] = SCE->REG_100H;
        OutData_Text[24] = SCE->REG_100H;
        OutData_Text[25] = SCE->REG_100H;
        OutData_Text[26] = SCE->REG_100H;
        OutData_Text[27] = SCE->REG_100H;
        OutData_Text[28] = SCE->REG_100H;
        OutData_Text[29] = SCE->REG_100H;
        OutData_Text[30] = SCE->REG_100H;
        OutData_Text[31] = SCE->REG_100H;
        OutData_Text[32] = SCE->REG_100H;
        OutData_Text[33] = SCE->REG_100H;
        OutData_Text[34] = SCE->REG_100H;
        OutData_Text[35] = SCE->REG_100H;
        OutData_Text[36] = SCE->REG_100H;
        OutData_Text[37] = SCE->REG_100H;
        OutData_Text[38] = SCE->REG_100H;
        OutData_Text[39] = SCE->REG_100H;
        OutData_Text[40] = SCE->REG_100H;
        OutData_Text[41] = SCE->REG_100H;
        OutData_Text[42] = SCE->REG_100H;
        OutData_Text[43] = SCE->REG_100H;
        OutData_Text[44] = SCE->REG_100H;
        OutData_Text[45] = SCE->REG_100H;
        OutData_Text[46] = SCE->REG_100H;
        OutData_Text[47] = SCE->REG_100H;
        OutData_Text[48] = SCE->REG_100H;
        OutData_Text[49] = SCE->REG_100H;
        OutData_Text[50] = SCE->REG_100H;
        OutData_Text[51] = SCE->REG_100H;
        OutData_Text[52] = SCE->REG_100H;
        OutData_Text[53] = SCE->REG_100H;
        OutData_Text[54] = SCE->REG_100H;
        OutData_Text[55] = SCE->REG_100H;
        OutData_Text[56] = SCE->REG_100H;
        OutData_Text[57] = SCE->REG_100H;
        OutData_Text[58] = SCE->REG_100H;
        OutData_Text[59] = SCE->REG_100H;
        OutData_Text[60] = SCE->REG_100H;
        OutData_Text[61] = SCE->REG_100H;
        OutData_Text[62] = SCE->REG_100H;
        OutData_Text[63] = SCE->REG_100H;
        HW_SCE_p_func102(0x0e1f70ddU, 0xc4f5101eU, 0xa4b28d26U, 0xdf4d7264U);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p57.prc
***********************************************************************************************************************/
