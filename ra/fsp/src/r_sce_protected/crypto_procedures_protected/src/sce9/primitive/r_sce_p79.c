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
#include "r_sce.h"
#include "r_sce_private.h"

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

fsp_err_t R_SCE_Rsa3072ModularExponentEncryptSub(uint32_t *InData_KeyIndex, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    if (0x0U != (SCE->REG_1B8H & 0x1eU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00007903U;
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
    SCE->REG_100H = change_endian_long(0x00000079U);
    R_SCE_func101(0x0094c566U, 0x10986435U, 0x9f31addfU, 0xc8301f32U);
    R_SCE_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x0000000eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000079U);
    R_SCE_func101(0xf5d62600U, 0xb1abe549U, 0x6a33cbc3U, 0xd04a30cbU);
    R_SCE_func044();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00040804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00006362U;
    SCE->REG_D0H = 0x40001800U;
    SCE->REG_C4H = 0x02e08887U;
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    for(iLoop=0; iLoop<32; iLoop=iLoop+4)
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
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    for(iLoop=32; iLoop<64; iLoop=iLoop+4)
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
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    for(iLoop=64; iLoop<96; iLoop=iLoop+4)
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
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    SCE->REG_E0H = 0x80010280U;
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
    SCE->REG_104H = 0x00000362U;
    SCE->REG_D0H = 0x40000000U;
    SCE->REG_C4H = 0x000087b5U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 0];
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 1];
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 2];
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 3];
    SCE->REG_C4H = 0x00900c45U;
    SCE->REG_00H = 0x00002213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0x2bd4de17U, 0x936d99ffU, 0x2fa1d6b0U, 0x6693146dU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x2691e276U, 0x93a1552aU, 0xf28c0224U, 0xd2253a99U);
        SCE->REG_1B8H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        R_SCE_func100(0xcae1ea65U, 0xf76049bfU, 0xbb4332b1U, 0x971fd234U);
        R_SCE_func103();
        R_SCE_func100(0x90487217U, 0xc7b0affcU, 0x026e5761U, 0xb1a55416U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010c0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        R_SCE_func100(0x8608f20bU, 0xb5bdb91dU, 0xb8c153d9U, 0x05083d7aU);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x018e0c4cU);
        R_SCE_func080();
        R_SCE_func100(0xd925b2baU, 0x5f87235fU, 0x4cb02c53U, 0xc5a41b88U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func319(752);
        R_SCE_func100(0xba8fe304U, 0x822c1026U, 0x1577ad01U, 0xd78a2a1cU);
        R_SCE_func314(752+32);
        R_SCE_func100(0x57e81972U, 0xcfec4cb2U, 0x412b52a2U, 0x785da8f7U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010273a4U);
        R_SCE_func080();
        R_SCE_func100(0xa58363ffU, 0xa1ab3397U, 0x83965bcbU, 0x6830d52fU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func319(716);
        R_SCE_func100(0x2c41d291U, 0x8e8520a0U, 0x25501a9fU, 0xd841477eU);
        R_SCE_func314(716+32);
        R_SCE_func100(0x018c1b2bU, 0xed8b7d12U, 0x4a5be87eU, 0xfe509361U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019410dfU);
        R_SCE_func080();
        R_SCE_func100(0x968273c9U, 0x99dbcfc1U, 0xab022f11U, 0x6c2b9e0dU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        R_SCE_func319(680);
        R_SCE_func100(0xe14b6150U, 0xb6403443U, 0x22f77d54U, 0x9c08de82U);
        R_SCE_func314(680+32);
        SCE->REG_00H = 0x0000037fU;
        SCE->REG_2CH = 0x00000024U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_E0H = 0x800103e0U;
        SCE->REG_00H = 0x00008307U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x3800dbe0U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_2CH = 0x00000010U;
        SCE->REG_104H = 0x00001f67U;
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
        SCE->REG_24H = 0x0000a0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_2CH = 0x00000014U;
        SCE->REG_104H = 0x00003f67U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
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
        SCE->REG_100H = InData_Text[64];
        SCE->REG_100H = InData_Text[65];
        SCE->REG_100H = InData_Text[66];
        SCE->REG_100H = InData_Text[67];
        SCE->REG_100H = InData_Text[68];
        SCE->REG_100H = InData_Text[69];
        SCE->REG_100H = InData_Text[70];
        SCE->REG_100H = InData_Text[71];
        SCE->REG_100H = InData_Text[72];
        SCE->REG_100H = InData_Text[73];
        SCE->REG_100H = InData_Text[74];
        SCE->REG_100H = InData_Text[75];
        SCE->REG_100H = InData_Text[76];
        SCE->REG_100H = InData_Text[77];
        SCE->REG_100H = InData_Text[78];
        SCE->REG_100H = InData_Text[79];
        SCE->REG_100H = InData_Text[80];
        SCE->REG_100H = InData_Text[81];
        SCE->REG_100H = InData_Text[82];
        SCE->REG_100H = InData_Text[83];
        SCE->REG_100H = InData_Text[84];
        SCE->REG_100H = InData_Text[85];
        SCE->REG_100H = InData_Text[86];
        SCE->REG_100H = InData_Text[87];
        SCE->REG_100H = InData_Text[88];
        SCE->REG_100H = InData_Text[89];
        SCE->REG_100H = InData_Text[90];
        SCE->REG_100H = InData_Text[91];
        SCE->REG_100H = InData_Text[92];
        SCE->REG_100H = InData_Text[93];
        SCE->REG_100H = InData_Text[94];
        SCE->REG_100H = InData_Text[95];
        SCE->REG_28H = 0x009f0001U;
        R_SCE_func100(0x334d09ccU, 0x2524049aU, 0xa6f0a0ecU, 0x7a2115e4U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019de420U);
        R_SCE_func080();
        R_SCE_func100(0x86fb7a96U, 0xbe6bdc21U, 0xf5ecf8dbU, 0xc0c6b984U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func319(72);
        R_SCE_func100(0x840fdf71U, 0x1f169255U, 0xa1b1efb1U, 0x555756faU);
        R_SCE_func314(72+32);
        R_SCE_func100(0xe836c33eU, 0x66ba0d4cU, 0xd379eb0fU, 0x1232fef2U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019969f4U);
        R_SCE_func080();
        R_SCE_func100(0x920ec563U, 0x76061a03U, 0x67937367U, 0x8eef3d82U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000025U;
        R_SCE_func319(36);
        R_SCE_func100(0x9389e6faU, 0x789df45aU, 0xa3481096U, 0xe82b4249U);
        R_SCE_func314(36+32);
        R_SCE_func100(0xfdf89268U, 0x4102be99U, 0x640574b3U, 0xf35decb6U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01fe1091U);
        R_SCE_func080();
        R_SCE_func100(0x0a829422U, 0x66823532U, 0x273db663U, 0x40cf4369U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        R_SCE_func319(0);
        R_SCE_func100(0x22e4d97eU, 0xa11d4053U, 0xef031ce3U, 0xc4fc54c9U);
        R_SCE_func314(0+32);
        R_SCE_func100(0x2bbb753cU, 0xfecdf56fU, 0x57596fa1U, 0x66aaa8a7U);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x000040d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000005c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00a10000U;
        SCE->REG_24H = 0x000005c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000581U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019410dfU);
        R_SCE_func080();
        R_SCE_func100(0x7a022d1dU, 0xccdb45d5U, 0x0fcb103eU, 0x6ff16ea3U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000010U;
        R_SCE_func320(680);
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010273a4U);
        R_SCE_func080();
        R_SCE_func100(0x14a62edbU, 0x079a9d1eU, 0x2d13b4c4U, 0x20b1211cU);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000011U;
        R_SCE_func320(716);
        SCE->REG_24H = 0x000016c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x018e0c4cU);
        R_SCE_func080();
        R_SCE_func100(0xe69ca1b6U, 0xfbe4980aU, 0xeb9f822aU, 0x4342a555U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000012U;
        R_SCE_func320(752);
        SCE->REG_24H = 0x000060d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x000080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x060049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01fe1091U);
        R_SCE_func080();
        R_SCE_func100(0x779f0ef9U, 0xe57d33bcU, 0x1da42781U, 0xf33ec00aU);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func320(0);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019969f4U);
        R_SCE_func080();
        R_SCE_func100(0x8b2c605eU, 0x0044090bU, 0x5b2c5203U, 0x95272c73U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000015U;
        R_SCE_func320(36);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019de420U);
        R_SCE_func080();
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000010U;
        R_SCE_func320(72);
        SCE->REG_24H = 0x0000a0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x04001991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x060049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0xd32f396bU, 0xe0e4b72eU, 0x9066e0a4U, 0xaeabb5efU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x94bcd5e6U, 0xaee6e985U, 0xf19fcc91U, 0x71b9e9e6U);
            SCE->REG_1B8H = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_ECH = 0x0000b7a0U;
            SCE->REG_ECH = 0x00000079U;
            R_SCE_func101(0xf53c859fU, 0x88e5bcc8U, 0x4a2d21a2U, 0xb21edb0aU);
            R_SCE_func325();
            SCE->REG_28H = 0x009f0001U;
            R_SCE_func100(0xbb65f7f3U, 0xd08c83a1U, 0x3a33f9eaU, 0x28c13174U);
            SCE->REG_2CH = 0x00000020U;
            SCE->REG_04H = 0x00000382U;
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
            SCE->REG_28H = 0x00bf0001U;
            R_SCE_func100(0x3832473fU, 0x9f8a2731U, 0x2b7f0621U, 0x044e8a0dU);
            SCE->REG_2CH = 0x00000022U;
            SCE->REG_04H = 0x00000302U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
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
            OutData_Text[64] = SCE->REG_100H;
            OutData_Text[65] = SCE->REG_100H;
            OutData_Text[66] = SCE->REG_100H;
            OutData_Text[67] = SCE->REG_100H;
            OutData_Text[68] = SCE->REG_100H;
            OutData_Text[69] = SCE->REG_100H;
            OutData_Text[70] = SCE->REG_100H;
            OutData_Text[71] = SCE->REG_100H;
            OutData_Text[72] = SCE->REG_100H;
            OutData_Text[73] = SCE->REG_100H;
            OutData_Text[74] = SCE->REG_100H;
            OutData_Text[75] = SCE->REG_100H;
            OutData_Text[76] = SCE->REG_100H;
            OutData_Text[77] = SCE->REG_100H;
            OutData_Text[78] = SCE->REG_100H;
            OutData_Text[79] = SCE->REG_100H;
            OutData_Text[80] = SCE->REG_100H;
            OutData_Text[81] = SCE->REG_100H;
            OutData_Text[82] = SCE->REG_100H;
            OutData_Text[83] = SCE->REG_100H;
            OutData_Text[84] = SCE->REG_100H;
            OutData_Text[85] = SCE->REG_100H;
            OutData_Text[86] = SCE->REG_100H;
            OutData_Text[87] = SCE->REG_100H;
            OutData_Text[88] = SCE->REG_100H;
            OutData_Text[89] = SCE->REG_100H;
            OutData_Text[90] = SCE->REG_100H;
            OutData_Text[91] = SCE->REG_100H;
            OutData_Text[92] = SCE->REG_100H;
            OutData_Text[93] = SCE->REG_100H;
            OutData_Text[94] = SCE->REG_100H;
            OutData_Text[95] = SCE->REG_100H;
            R_SCE_func102(0x150da20dU, 0xa1749a49U, 0x21ab47b6U, 0x7af769c3U);
            SCE->REG_1B8H = 0x00000040U;
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p79_r2.prc
***********************************************************************************************************************/
