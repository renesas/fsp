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
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000056U);
    HW_SCE_p_func101(0xdc0a590bU, 0x6e3392ffU, 0x97adc5b9U, 0x633171bbU);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000056U);
    HW_SCE_p_func101(0xfc2447faU, 0x9cf0143bU, 0x85110c57U, 0x2b7cbdcfU);
    HW_SCE_p_func044();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00040804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_28H = 0x00000001U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    SCE->REG_104H = 0x00008362U;
    SCE->REG_D0H = 0x40000f00U;
    SCE->REG_C4H = 0x02e08887U;
    for(iLoop=0; iLoop<64; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x00e08885U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[65];
    SCE->REG_100H = InData_KeyIndex[66];
    SCE->REG_100H = InData_KeyIndex[67];
    SCE->REG_100H = InData_KeyIndex[68];
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_00H = 0x00008207U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000020fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    SCE->REG_D0H = 0x40000f00U;
    SCE->REG_C4H = 0x00f087b7U;
    for(iLoop=68; iLoop<132; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000362U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000087b5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[133];
    SCE->REG_100H = InData_KeyIndex[134];
    SCE->REG_100H = InData_KeyIndex[135];
    SCE->REG_100H = InData_KeyIndex[136];
    SCE->REG_C4H = 0x00900c45U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_p_func100(0x0493bf32U, 0x4fd6ac99U, 0x18fd6dbdU, 0x235e32ddU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xe07e4daaU, 0x5778972bU, 0xd2cb35fdU, 0x1c09d955U);
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
        HW_SCE_p_func100(0x30b546ddU, 0x1c282749U, 0xd166b5dfU, 0x5f659d4bU);
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
        HW_SCE_p_func100(0x305b97ceU, 0x263481e9U, 0x9ae65b13U, 0xb79bccfeU);
        SCE->REG_2CH = 0x00000020U;
        SCE->REG_04H = 0x00000303U;
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
        HW_SCE_p_func102(0xa498754bU, 0x729577e0U, 0x423a9c49U, 0xbf249dabU);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p56.prc
***********************************************************************************************************************/
