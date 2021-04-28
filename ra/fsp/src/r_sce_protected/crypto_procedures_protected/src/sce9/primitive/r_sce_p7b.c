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

fsp_err_t R_SCE_Rsa4096ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, uint32_t *InData_Text, uint32_t *OutData_Text)
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
    SCE->REG_84H = 0x00007b03U;
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
    SCE->REG_100H = change_endian_long(0x0000007bU);
    R_SCE_func101(0x7ad72a9bU, 0xc0d644cbU, 0xfaca9314U, 0x11bbba6bU);
    R_SCE_func043();
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0000007bU);
    R_SCE_func101(0x205a7830U, 0x6c4a6d70U, 0xc9421de4U, 0xbf1d257eU);
    R_SCE_func044();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x00040804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00007f62U;
    SCE->REG_D0H = 0x40001f00U;
    SCE->REG_C4H = 0x02e08887U;
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
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
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    for(iLoop=64; iLoop<128; iLoop=iLoop+4)
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
    SCE->REG_C4H = 0x00e08885U;
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
    R_SCE_func100(0xb7f64b98U, 0xce8be4f2U, 0xdaecb29fU, 0xba4bee57U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x38f2ba28U, 0x7b5fd1f3U, 0x2cf26fd2U, 0xc1024f2fU);
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
        R_SCE_func100(0x5dcd5dc9U, 0x76547c90U, 0x8501b35bU, 0x48978d2eU);
        R_SCE_func103();
        R_SCE_func100(0x8e5ab704U, 0xd3215d65U, 0xf6885c91U, 0xf9dc448eU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010c0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        R_SCE_func100(0x022fb9d2U, 0x81775805U, 0xda776150U, 0x273acd23U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x012dc3c7U);
        R_SCE_func080();
        R_SCE_func100(0xb68fe435U, 0x408234a3U, 0x7502469dU, 0x151fa101U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func313(748);
        R_SCE_func100(0xf7b240d4U, 0x5d10b4a0U, 0xe463f3acU, 0xffa56053U);
        R_SCE_func314(748+64);
        R_SCE_func100(0x2295a160U, 0xab9ce977U, 0x5025c0c8U, 0x36815466U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01b9d3a9U);
        R_SCE_func080();
        R_SCE_func100(0x795c26baU, 0xf985e8b5U, 0x4f24dd66U, 0xc556109bU);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func313(680);
        R_SCE_func100(0x8344f51cU, 0x970d22abU, 0x026ab0a7U, 0xbdf9063bU);
        R_SCE_func314(680+64);
        SCE->REG_00H = 0x000003ffU;
        SCE->REG_2CH = 0x00000022U;
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
        R_SCE_func100(0xd2a1b049U, 0x70be50b2U, 0x7fa58ad6U, 0xfe642e4cU);
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
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0132d44bU);
        R_SCE_func080();
        R_SCE_func100(0xd4b4e6e1U, 0xa785f78bU, 0x6c79a84dU, 0x7d23f718U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func313(68);
        R_SCE_func100(0xffa9408cU, 0x5afbfcf1U, 0xccb0ac56U, 0xb77df063U);
        R_SCE_func314(68+64);
        R_SCE_func100(0x25d15aabU, 0x77aa55a3U, 0x099062d6U, 0x88f4f775U);
        SCE->REG_2CH = 0x00000014U;
        SCE->REG_104H = 0x00003f67U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
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
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01432c7aU);
        R_SCE_func080();
        R_SCE_func100(0x38359f99U, 0x72026843U, 0x34de71ddU, 0xeb37ea65U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000024U;
        R_SCE_func313(0);
        R_SCE_func100(0x5207d298U, 0x39dcd15dU, 0x680983ceU, 0xb6628fd8U);
        R_SCE_func314(0+64);
        R_SCE_func100(0x4dd8e7c0U, 0x0c001f8fU, 0x9cc0ac77U, 0xc283a6d8U);
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
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01b9d3a9U);
        R_SCE_func080();
        R_SCE_func100(0xd40fcc2eU, 0x9ade18b0U, 0x8545ef60U, 0xe90f552aU);
        SCE->REG_00H = 0x00013203U;
        SCE->REG_2CH = 0x00000010U;
        R_SCE_func312(680);
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
        SCE->REG_100H = change_endian_long(0x012dc3c7U);
        R_SCE_func080();
        R_SCE_func100(0x0cf3ad46U, 0xd701fb04U, 0xbdac7452U, 0x6eb22107U);
        SCE->REG_00H = 0x00013203U;
        SCE->REG_2CH = 0x00000012U;
        R_SCE_func312(748);
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
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01432c7aU);
        R_SCE_func080();
        R_SCE_func100(0x527b0f66U, 0x887690e8U, 0x7aa948f6U, 0xa84eb5e8U);
        SCE->REG_00H = 0x00013203U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func312(0);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0132d44bU);
        R_SCE_func080();
        SCE->REG_00H = 0x00013203U;
        SCE->REG_2CH = 0x00000010U;
        R_SCE_func312(68);
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
        R_SCE_func100(0x8616b1c2U, 0xf15b1d65U, 0x0b519337U, 0x546a6a9bU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x306d1ceaU, 0x8538343eU, 0x71f1a4c7U, 0x29c40b79U);
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
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x0000007bU;
            R_SCE_func101(0x6d2f8001U, 0x84e44900U, 0xefad9bb2U, 0x7eae5acdU);
            R_SCE_func307();
            R_SCE_func100(0xc9dbdeffU, 0x9dc1302aU, 0x9293827eU, 0xa2d5d039U);
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
            R_SCE_func100(0xf1ec3171U, 0x776ebc7aU, 0xefbfa3baU, 0x9ea08d5eU);
            SCE->REG_2CH = 0x00000022U;
            SCE->REG_04H = 0x00000302U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
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
            R_SCE_func102(0xcea23837U, 0x87b642a5U, 0x5c40ed39U, 0xd3083ffeU);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p7b_r2.prc
***********************************************************************************************************************/
