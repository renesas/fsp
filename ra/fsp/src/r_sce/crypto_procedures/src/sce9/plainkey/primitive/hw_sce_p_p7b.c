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

fsp_err_t HW_SCE_Rsa4096ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text, uint32_t *OutData_Text)
{
    uint32_t iLoop = 0u, iLoop1 = 0u, iLoop2 = 0u, jLoop = 0u, kLoop = 0u, oLoop = 0u, oLoop1 = 0u, oLoop2 = 0u, KEY_ADR = 0u, OFS_ADR = 0u, MAX_CNT2 = 0u;
    uint32_t dummy = 0u;
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
    if (0x0u != (SCE->REG_1B8H & 0x1eu))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00007b03u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x800100e0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[0];
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000007bu);
    HW_SCE_p_func101(0xb075d3d7u, 0xf61f2d39u, 0xc46c26acu, 0x8db6a4f9u);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x00000010u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000007bu);
    HW_SCE_p_func101(0x2309da37u, 0xf0f28872u, 0x6cfd2509u, 0xa7f31384u);
    HW_SCE_p_func044();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00040804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_104H = 0x00007f62u;
    SCE->REG_D0H = 0x40001f00u;
    SCE->REG_C4H = 0x02e08887u;
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    for(iLoop=0; iLoop<64; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    }
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    for(iLoop=64; iLoop<128; iLoop=iLoop+4)
    {
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    }
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000362u;
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x00e08885u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
    SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
    SCE->REG_E0H = 0x80010280u;
    SCE->REG_00H = 0x00008207u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000020fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_104H = 0x00000362u;
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x000087b5u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 0];
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 1];
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 2];
    SCE->REG_100H = InData_KeyIndex[iLoop+5 + 3];
    SCE->REG_C4H = 0x00900c45u;
    SCE->REG_00H = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x903b968eu, 0xad9da53cu, 0xaba0cd07u, 0x97b48c76u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x54d41d5au, 0x06b3a163u, 0x53f979b9u, 0x47bf5286u);
        SCE->REG_1B8H = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x461f3249u, 0x2efadb3eu, 0xbaf07020u, 0xaeeceaecu);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xe5463b0du, 0xcd954697u, 0x740fdb08u, 0xc51bf68cu);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x010c0c04u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        HW_SCE_p_func100(0x666934e9u, 0x793e6d91u, 0x0e43c17eu, 0x0616660cu);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x012dc3c7u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xe5642d63u, 0xc3d07339u, 0xa16918beu, 0xa74ae22eu);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func313(748);
        HW_SCE_p_func100(0x3839dc3du, 0x00caee54u, 0xce7cc0a9u, 0xc779149fu);
        HW_SCE_p_func314(748+64);
        HW_SCE_p_func100(0x82eca6bdu, 0xdb97e979u, 0x36f8c5f4u, 0x8f0548a4u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01b9d3a9u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x4fa851eau, 0xfe31e49eu, 0xbf16a61au, 0x411d969cu);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func313(680);
        HW_SCE_p_func100(0x9810dd6au, 0x2c76d595u, 0xd604ae28u, 0xf8772679u);
        HW_SCE_p_func314(680+64);
        SCE->REG_00H = 0x000003ffu;
        SCE->REG_2CH = 0x00000022u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_E0H = 0x800103e0u;
        SCE->REG_00H = 0x00008307u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x3800dbe0u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00260000u;
        HW_SCE_p_func100(0x2fd0da4fu, 0xc0180b8eu, 0x9b930e08u, 0x25b04aecu);
        SCE->REG_2CH = 0x00000010u;
        SCE->REG_104H = 0x00003f67u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
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
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0132d44bu);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x3279f1d9u, 0x0f2dfdfbu, 0x0f0ffcb2u, 0x6357c36au);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func313(68);
        HW_SCE_p_func100(0xf2add757u, 0xfa02b79bu, 0x6c5ffee4u, 0x82be2125u);
        HW_SCE_p_func314(68+64);
        HW_SCE_p_func100(0x692e1d9fu, 0x0ff2e4d0u, 0x35103c8du, 0x81420ab6u);
        SCE->REG_2CH = 0x00000014u;
        SCE->REG_104H = 0x00003f67u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
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
        SCE->REG_100H = InData_Text[96];
        SCE->REG_100H = InData_Text[97];
        SCE->REG_100H = InData_Text[98];
        SCE->REG_100H = InData_Text[99];
        SCE->REG_100H = InData_Text[100];
        SCE->REG_100H = InData_Text[101];
        SCE->REG_100H = InData_Text[102];
        SCE->REG_100H = InData_Text[103];
        SCE->REG_100H = InData_Text[104];
        SCE->REG_100H = InData_Text[105];
        SCE->REG_100H = InData_Text[106];
        SCE->REG_100H = InData_Text[107];
        SCE->REG_100H = InData_Text[108];
        SCE->REG_100H = InData_Text[109];
        SCE->REG_100H = InData_Text[110];
        SCE->REG_100H = InData_Text[111];
        SCE->REG_100H = InData_Text[112];
        SCE->REG_100H = InData_Text[113];
        SCE->REG_100H = InData_Text[114];
        SCE->REG_100H = InData_Text[115];
        SCE->REG_100H = InData_Text[116];
        SCE->REG_100H = InData_Text[117];
        SCE->REG_100H = InData_Text[118];
        SCE->REG_100H = InData_Text[119];
        SCE->REG_100H = InData_Text[120];
        SCE->REG_100H = InData_Text[121];
        SCE->REG_100H = InData_Text[122];
        SCE->REG_100H = InData_Text[123];
        SCE->REG_100H = InData_Text[124];
        SCE->REG_100H = InData_Text[125];
        SCE->REG_100H = InData_Text[126];
        SCE->REG_100H = InData_Text[127];
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01432c7au);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x6856f51bu, 0x67c3861bu, 0x0f98564fu, 0x1c2173b6u);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000024u;
        HW_SCE_p_func313(0);
        HW_SCE_p_func100(0x2cc7c29fu, 0x55989bb4u, 0xe0885821u, 0x47946e2bu);
        HW_SCE_p_func314(0+64);
        HW_SCE_p_func100(0x4a70a9f1u, 0x00cbb8f2u, 0xd7e7b87cu, 0xb4b60fccu);
        SCE->REG_24H = 0x000040d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000005c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x060049c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00a10000u;
        SCE->REG_24H = 0x000005c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000581u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01b9d3a9u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x9ac95ad5u, 0x6a879f56u, 0x923eb619u, 0x26d3747bu);
        SCE->REG_00H = 0x00013203u;
        SCE->REG_2CH = 0x00000010u;
        HW_SCE_p_func312(680);
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x012dc3c7u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x4f01d2cfu, 0x0d4eb0adu, 0xcaba60efu, 0x3970713cu);
        SCE->REG_00H = 0x00013203u;
        SCE->REG_2CH = 0x00000012u;
        HW_SCE_p_func312(748);
        SCE->REG_24H = 0x000080d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x060049c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000049c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01432c7au);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xacafc88eu, 0xdbd38fc2u, 0xb6c15c6au, 0x17f023f3u);
        SCE->REG_00H = 0x00013203u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func312(0);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0132d44bu);
        HW_SCE_p_func080();
        SCE->REG_00H = 0x00013203u;
        SCE->REG_2CH = 0x00000010u;
        HW_SCE_p_func312(68);
        SCE->REG_24H = 0x04001991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x060049c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0xee4a893eu, 0x61180774u, 0x5f024dfeu, 0x354fe237u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xcbeb2459u, 0x60ad9840u, 0x6aa33f73u, 0xc3e165e4u);
            SCE->REG_1B8H = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_ECH = 0x0000b400u;
            SCE->REG_ECH = 0x0000007bu;
            HW_SCE_p_func101(0xad1ea16du, 0xf8e9b417u, 0x6e7fb16au, 0x0cb69393u);
            HW_SCE_p_func307();
            HW_SCE_p_func100(0x79311285u, 0xe19252e8u, 0x6b8254d5u, 0x5380f50eu);
            SCE->REG_2CH = 0x00000020u;
            SCE->REG_04H = 0x00000302u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
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
            HW_SCE_p_func100(0x05cf816cu, 0xaebbba33u, 0xc92ae771u, 0x1fba7f70u);
            SCE->REG_2CH = 0x00000022u;
            SCE->REG_04H = 0x00000302u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
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
            OutData_Text[96] = SCE->REG_100H;
            OutData_Text[97] = SCE->REG_100H;
            OutData_Text[98] = SCE->REG_100H;
            OutData_Text[99] = SCE->REG_100H;
            OutData_Text[100] = SCE->REG_100H;
            OutData_Text[101] = SCE->REG_100H;
            OutData_Text[102] = SCE->REG_100H;
            OutData_Text[103] = SCE->REG_100H;
            OutData_Text[104] = SCE->REG_100H;
            OutData_Text[105] = SCE->REG_100H;
            OutData_Text[106] = SCE->REG_100H;
            OutData_Text[107] = SCE->REG_100H;
            OutData_Text[108] = SCE->REG_100H;
            OutData_Text[109] = SCE->REG_100H;
            OutData_Text[110] = SCE->REG_100H;
            OutData_Text[111] = SCE->REG_100H;
            OutData_Text[112] = SCE->REG_100H;
            OutData_Text[113] = SCE->REG_100H;
            OutData_Text[114] = SCE->REG_100H;
            OutData_Text[115] = SCE->REG_100H;
            OutData_Text[116] = SCE->REG_100H;
            OutData_Text[117] = SCE->REG_100H;
            OutData_Text[118] = SCE->REG_100H;
            OutData_Text[119] = SCE->REG_100H;
            OutData_Text[120] = SCE->REG_100H;
            OutData_Text[121] = SCE->REG_100H;
            OutData_Text[122] = SCE->REG_100H;
            OutData_Text[123] = SCE->REG_100H;
            OutData_Text[124] = SCE->REG_100H;
            OutData_Text[125] = SCE->REG_100H;
            OutData_Text[126] = SCE->REG_100H;
            OutData_Text[127] = SCE->REG_100H;
            HW_SCE_p_func102(0xd5b1053bu, 0x51915abdu, 0x25d683eeu, 0x9890acd5u);
            SCE->REG_1B8H = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p7b_r2.prc
***********************************************************************************************************************/
