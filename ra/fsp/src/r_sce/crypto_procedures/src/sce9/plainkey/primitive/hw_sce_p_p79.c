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

fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text, uint32_t *OutData_Text)
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
    HW_SCE_p_func101(0x9930b009U, 0x81e95a8cU, 0xe8edfc49U, 0xa9c2f412U);
    HW_SCE_p_func043();
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
    HW_SCE_p_func101(0x6b0497cfU, 0x2c4fe92bU, 0x51befe47U, 0xb7bd24b5U);
    HW_SCE_p_func044();
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
    HW_SCE_p_func100(0x7ee8691bU, 0x37b5f60aU, 0x87859dc1U, 0x394206a8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x1e94bb70U, 0xd0807b52U, 0xb19b60a0U, 0x875879ffU);
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
        HW_SCE_p_func100(0x115bdcb3U, 0x073a2576U, 0xa28bdb20U, 0x2f2d587aU);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xa970f4faU, 0xb28af495U, 0x5d28b925U, 0x2ec6dfa3U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x010c0c04U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        HW_SCE_p_func100(0x4350ff0fU, 0x54672d5aU, 0x3e9ea952U, 0xed9785daU);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x018e0c4cU);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x830263b0U, 0x987f3967U, 0xdd7089eaU, 0xfb6164b3U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        HW_SCE_p_func319(752);
        HW_SCE_p_func100(0x7d8ff34eU, 0x39614ffaU, 0x02d73beeU, 0x32051da9U);
        HW_SCE_p_func314(752+32);
        HW_SCE_p_func100(0x336798e0U, 0x6d49a1fbU, 0x49bd8f75U, 0x8a0e9fa7U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010273a4U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xa0287871U, 0x20908695U, 0x4fda4e72U, 0x8d0d67a8U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func319(716);
        HW_SCE_p_func100(0xe3e3d8acU, 0xa1e30561U, 0x83e21b2eU, 0x7d239563U);
        HW_SCE_p_func314(716+32);
        HW_SCE_p_func100(0xfa3af305U, 0xdb097dcfU, 0xf809dec6U, 0xfd840cdeU);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019410dfU);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x9fd08737U, 0x4f2d0f36U, 0x1b1a4873U, 0xf3b346f4U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        HW_SCE_p_func319(680);
        HW_SCE_p_func100(0xe3cbffc7U, 0xa0ff85e1U, 0x18893f9fU, 0xae2c8b0eU);
        HW_SCE_p_func314(680+32);
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
        HW_SCE_p_func100(0x3b932c9dU, 0xe60b45f9U, 0x4c68dc70U, 0xbab75753U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019de420U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xf14dc81dU, 0x08c983d3U, 0x2ab61a1eU, 0x451526acU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        HW_SCE_p_func319(72);
        HW_SCE_p_func100(0x2038a22aU, 0xb18b5053U, 0xaeaa8fb6U, 0x146a776cU);
        HW_SCE_p_func314(72+32);
        HW_SCE_p_func100(0x98d4795dU, 0xc5730533U, 0x8758a926U, 0x59185715U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019969f4U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x219de09dU, 0x3123024fU, 0x16875a12U, 0x75a53b8eU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000025U;
        HW_SCE_p_func319(36);
        HW_SCE_p_func100(0x95492014U, 0xb970b606U, 0x4ce340ceU, 0x17ca043aU);
        HW_SCE_p_func314(36+32);
        HW_SCE_p_func100(0x815aba79U, 0x0c7e88ddU, 0xaa881027U, 0x49e7c658U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01fe1091U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x50c99eb5U, 0xb362b304U, 0xa260fd0cU, 0xd13b0444U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000024U;
        HW_SCE_p_func319(0);
        HW_SCE_p_func100(0x99efb969U, 0xc88fe10cU, 0x3a83bfc6U, 0xd056ba30U);
        HW_SCE_p_func314(0+32);
        HW_SCE_p_func100(0x037788a3U, 0x79be5549U, 0xe46f539eU, 0x5aab9302U);
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
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x526c5725U, 0x2b7bafbcU, 0x6f8db96cU, 0xeb735ef5U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000010U;
        HW_SCE_p_func320(680);
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
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x0865271cU, 0x120ff1a1U, 0x71f5a98aU, 0xfccde033U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000011U;
        HW_SCE_p_func320(716);
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
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xaf4abd00U, 0x732a43fdU, 0xf1b0a12cU, 0x8b129d76U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000012U;
        HW_SCE_p_func320(752);
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
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x31290a2bU, 0xbf7356c4U, 0x4d0cccfaU, 0x22e1373fU);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000014U;
        HW_SCE_p_func320(0);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019969f4U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x8c99cd47U, 0x2868da89U, 0x91452e8eU, 0x7963c836U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000015U;
        HW_SCE_p_func320(36);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019de420U);
        HW_SCE_p_func080();
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000010U;
        HW_SCE_p_func320(72);
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
        HW_SCE_p_func100(0x3578337cU, 0xf2829ff4U, 0xcfc2f8a8U, 0xf4ebc9baU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xa3c643d5U, 0xbeb0bc69U, 0xc8cb1884U, 0x31c8ab72U);
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
            HW_SCE_p_func101(0xee77e57cU, 0x9533b284U, 0x8d1c3bc5U, 0x7dafdaabU);
            HW_SCE_p_func325_r1();
            SCE->REG_28H = 0x009f0001U;
            HW_SCE_p_func100(0xad4e3029U, 0x051ef4dfU, 0xf5ba502aU, 0x0f985354U);
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
            HW_SCE_p_func100(0x1ecc620bU, 0x57edb624U, 0x96cb0511U, 0x89d05b36U);
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
            HW_SCE_p_func102(0x0bd7bf02U, 0xee336e55U, 0xbb83a9edU, 0x0c98b241U);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCEp_p79_r3.prc
***********************************************************************************************************************/
