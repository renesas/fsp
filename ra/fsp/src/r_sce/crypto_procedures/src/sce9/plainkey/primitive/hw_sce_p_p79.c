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

fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text, uint32_t *OutData_Text)
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
    SCE->REG_84H = 0x00007903u;
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
    SCE->REG_100H = change_endian_long(0x00000079u);
    HW_SCE_p_func101(0x9930b009u, 0x81e95a8cu, 0xe8edfc49u, 0xa9c2f412u);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x0000000eu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000079u);
    HW_SCE_p_func101(0x6b0497cfu, 0x2c4fe92bu, 0x51befe47u, 0xb7bd24b5u);
    HW_SCE_p_func044();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00040804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00006362u;
    SCE->REG_D0H = 0x40001800u;
    SCE->REG_C4H = 0x02e08887u;
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    for(iLoop=0; iLoop<32; iLoop=iLoop+4)
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
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000012u;
    for(iLoop=32; iLoop<64; iLoop=iLoop+4)
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
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    for(iLoop=64; iLoop<96; iLoop=iLoop+4)
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
    HW_SCE_p_func100(0x7ee8691bu, 0x37b5f60au, 0x87859dc1u, 0x394206a8u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x1e94bb70u, 0xd0807b52u, 0xb19b60a0u, 0x875879ffu);
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
        HW_SCE_p_func100(0x115bdcb3u, 0x073a2576u, 0xa28bdb20u, 0x2f2d587au);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xa970f4fau, 0xb28af495u, 0x5d28b925u, 0x2ec6dfa3u);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x010c0c04u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        HW_SCE_p_func100(0x4350ff0fu, 0x54672d5au, 0x3e9ea952u, 0xed9785dau);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x018e0c4cu);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x830263b0u, 0x987f3967u, 0xdd7089eau, 0xfb6164b3u);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func319(752);
        HW_SCE_p_func100(0x7d8ff34eu, 0x39614ffau, 0x02d73beeu, 0x32051da9u);
        HW_SCE_p_func314(752+32);
        HW_SCE_p_func100(0x336798e0u, 0x6d49a1fbu, 0x49bd8f75u, 0x8a0e9fa7u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010273a4u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xa0287871u, 0x20908695u, 0x4fda4e72u, 0x8d0d67a8u);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func319(716);
        HW_SCE_p_func100(0xe3e3d8acu, 0xa1e30561u, 0x83e21b2eu, 0x7d239563u);
        HW_SCE_p_func314(716+32);
        HW_SCE_p_func100(0xfa3af305u, 0xdb097dcfu, 0xf809dec6u, 0xfd840cdeu);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019410dfu);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x9fd08737u, 0x4f2d0f36u, 0x1b1a4873u, 0xf3b346f4u);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000024u;
        HW_SCE_p_func319(680);
        HW_SCE_p_func100(0xe3cbffc7u, 0xa0ff85e1u, 0x18893f9fu, 0xae2c8b0eu);
        HW_SCE_p_func314(680+32);
        SCE->REG_00H = 0x0000037fu;
        SCE->REG_2CH = 0x00000024u;
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
        SCE->REG_2CH = 0x00000010u;
        SCE->REG_104H = 0x00001f67u;
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
        SCE->REG_24H = 0x0000a0d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_2CH = 0x00000014u;
        SCE->REG_104H = 0x00003f67u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
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
        SCE->REG_28H = 0x009f0001u;
        HW_SCE_p_func100(0x3b932c9du, 0xe60b45f9u, 0x4c68dc70u, 0xbab75753u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019de420u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xf14dc81du, 0x08c983d3u, 0x2ab61a1eu, 0x451526acu);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func319(72);
        HW_SCE_p_func100(0x2038a22au, 0xb18b5053u, 0xaeaa8fb6u, 0x146a776cu);
        HW_SCE_p_func314(72+32);
        HW_SCE_p_func100(0x98d4795du, 0xc5730533u, 0x8758a926u, 0x59185715u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019969f4u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x219de09du, 0x3123024fu, 0x16875a12u, 0x75a53b8eu);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000025u;
        HW_SCE_p_func319(36);
        HW_SCE_p_func100(0x95492014u, 0xb970b606u, 0x4ce340ceu, 0x17ca043au);
        HW_SCE_p_func314(36+32);
        HW_SCE_p_func100(0x815aba79u, 0x0c7e88ddu, 0xaa881027u, 0x49e7c658u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01fe1091u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x50c99eb5u, 0xb362b304u, 0xa260fd0cu, 0xd13b0444u);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000024u;
        HW_SCE_p_func319(0);
        HW_SCE_p_func100(0x99efb969u, 0xc88fe10cu, 0x3a83bfc6u, 0xd056ba30u);
        HW_SCE_p_func314(0+32);
        HW_SCE_p_func100(0x037788a3u, 0x79be5549u, 0xe46f539eu, 0x5aab9302u);
        SCE->REG_28H = 0x00bf0001u;
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
        SCE->REG_24H = 0x000049c1u;
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
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019410dfu);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x526c5725u, 0x2b7bafbcu, 0x6f8db96cu, 0xeb735ef5u);
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000010u;
        HW_SCE_p_func320(680);
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
        SCE->REG_100H = change_endian_long(0x010273a4u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x0865271cu, 0x120ff1a1u, 0x71f5a98au, 0xfccde033u);
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000011u;
        HW_SCE_p_func320(716);
        SCE->REG_24H = 0x000016c0u;
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
        SCE->REG_100H = change_endian_long(0x018e0c4cu);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xaf4abd00u, 0x732a43fdu, 0xf1b0a12cu, 0x8b129d76u);
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000012u;
        HW_SCE_p_func320(752);
        SCE->REG_24H = 0x000060d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
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
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01fe1091u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x31290a2bu, 0xbf7356c4u, 0x4d0cccfau, 0x22e1373fu);
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func320(0);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019969f4u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x8c99cd47u, 0x2868da89u, 0x91452e8eu, 0x7963c836u);
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000015u;
        HW_SCE_p_func320(36);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019de420u);
        HW_SCE_p_func080();
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000010u;
        HW_SCE_p_func320(72);
        SCE->REG_24H = 0x0000a0d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
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
        HW_SCE_p_func100(0x3578337cu, 0xf2829ff4u, 0xcfc2f8a8u, 0xf4ebc9bau);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xa3c643d5u, 0xbeb0bc69u, 0xc8cb1884u, 0x31c8ab72u);
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
            SCE->REG_ECH = 0x0000b7a0u;
            SCE->REG_ECH = 0x00000079u;
            HW_SCE_p_func101(0xee77e57cu, 0x9533b284u, 0x8d1c3bc5u, 0x7dafdaabu);
            HW_SCE_p_func325();
            SCE->REG_28H = 0x009f0001u;
            HW_SCE_p_func100(0x89f73d3fu, 0x7ca8dee1u, 0x9173e011u, 0x633d40e3u);
            SCE->REG_2CH = 0x00000020u;
            SCE->REG_04H = 0x00000382u;
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
            SCE->REG_28H = 0x00bf0001u;
            HW_SCE_p_func100(0xa42466f5u, 0x57bd3bb3u, 0xb6f415b2u, 0xe32c0359u);
            SCE->REG_2CH = 0x00000022u;
            SCE->REG_04H = 0x00000302u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
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
            HW_SCE_p_func102(0xfeb44e6eu, 0x7548637du, 0x57cf5ec8u, 0xef21b7b0u);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p79_r2.prc
***********************************************************************************************************************/
