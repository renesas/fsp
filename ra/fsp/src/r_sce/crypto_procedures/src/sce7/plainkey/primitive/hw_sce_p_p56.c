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

fsp_err_t HW_SCE_Rsa2048ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text, uint32_t *OutData_Text)
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
    SCE->REG_84H = 0x00005601U;
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
    SCE->REG_100H = change_endian_long(0x671c43cbU);
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
    SCE->REG_104H = 0x00008361U;
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
    SCE->REG_A4H = 0x00f0088dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[68];
    SCE->REG_100H = InData_KeyIndex[69];
    SCE->REG_100H = InData_KeyIndex[70];
    SCE->REG_100H = InData_KeyIndex[71];
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_00H = 0x00008107U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000010fU;
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
    for(iLoop=72; iLoop<136; iLoop=iLoop+4)
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
    SCE->REG_100H = InData_KeyIndex[136];
    SCE->REG_100H = InData_KeyIndex[137];
    SCE->REG_100H = InData_KeyIndex[138];
    SCE->REG_100H = InData_KeyIndex[139];
    SCE->REG_A4H = 0x00900c45U;
    SCE->REG_00H = 0x00001113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0xf4da777fU, 0xcc4004b5U, 0xebebf0c5U, 0x0bb69a6bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x8882e286U, 0x531b34f1U, 0x384d6386U, 0xc543a862U);
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
        HW_SCE_p_func100(0xd48f78e9U, 0x9ea8d968U, 0xf035a43fU, 0x583b8f42U);
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
        SCE->REG_18H = 0x00000004U;
        SCE->REG_38H = 0x00000338U;
        SCE->REG_E0H = 0x81010000U;
        SCE->REG_00H = 0x00003807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000U;
        HW_SCE_p_func100(0xae116e33U, 0x28342520U, 0xc80e3456U, 0xf3c36687U);
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
        HW_SCE_p_func102(0x92b5aa27U, 0x489b281bU, 0xbdc4d35fU, 0xa4b213adU);
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
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p56.prc
***********************************************************************************************************************/
