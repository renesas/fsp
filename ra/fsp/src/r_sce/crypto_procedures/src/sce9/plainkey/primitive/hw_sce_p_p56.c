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

fsp_err_t HW_SCE_Rsa2048ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text, uint32_t *OutData_Text)
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
    if (0x0u != (SCE->REG_1BCH & 0x1fu))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00005601u;
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
    SCE->REG_100H = change_endian_long(0x00000056u);
    HW_SCE_p_func101(0xdc0a590bu, 0x6e3392ffu, 0x97adc5b9u, 0x633171bbu);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x0000b4e0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000056u);
    HW_SCE_p_func101(0xfc2447fau, 0x9cf0143bu, 0x85110c57u, 0x2b7cbdcfu);
    HW_SCE_p_func044();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00040804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_28H = 0x00000001u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    SCE->REG_104H = 0x00008362u;
    SCE->REG_D0H = 0x40000f00u;
    SCE->REG_C4H = 0x02e08887u;
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
    SCE->REG_D0H = 0x40000000u;
    SCE->REG_C4H = 0x00e08885u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[65];
    SCE->REG_100H = InData_KeyIndex[66];
    SCE->REG_100H = InData_KeyIndex[67];
    SCE->REG_100H = InData_KeyIndex[68];
    SCE->REG_E0H = 0x80010000u;
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
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    SCE->REG_D0H = 0x40000f00u;
    SCE->REG_C4H = 0x00f087b7u;
    for(iLoop=68; iLoop<132; iLoop=iLoop+4)
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
    SCE->REG_C4H = 0x000087b5u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyIndex[133];
    SCE->REG_100H = InData_KeyIndex[134];
    SCE->REG_100H = InData_KeyIndex[135];
    SCE->REG_100H = InData_KeyIndex[136];
    SCE->REG_C4H = 0x00900c45u;
    SCE->REG_00H = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func100(0x0493bf32u, 0x4fd6ac99u, 0x18fd6dbdu, 0x235e32ddu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xe07e4daau, 0x5778972bu, 0xd2cb35fdu, 0x1c09d955u);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x30b546ddu, 0x1c282749u, 0xd166b5dfu, 0x5f659d4bu);
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
        SCE->REG_18H = 0x00000004u;
        SCE->REG_38H = 0x00000338u;
        SCE->REG_E0H = 0x81010000u;
        SCE->REG_00H = 0x00003807u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B10)
        {
            /* waiting */
        }
        SCE->REG_18H = 0x00000000u;
        HW_SCE_p_func100(0x305b97ceu, 0x263481e9u, 0x9ae65b13u, 0xb79bccfeu);
        SCE->REG_2CH = 0x00000020u;
        SCE->REG_04H = 0x00000303u;
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
        HW_SCE_p_func102(0xa498754bu, 0x729577e0u, 0x423a9c49u, 0xbf249dabu);
        SCE->REG_1BCH = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p56.prc
***********************************************************************************************************************/
