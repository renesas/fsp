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

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t * InData_Cmd,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_IV)
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
    SCE->REG_84H = 0x00005002u;
    SCE->REG_108H = 0x00000000u;
    SCE->REG_C4H = 0x200e1a0du;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[20+0 + 0];
    SCE->REG_100H = S_RAM[20+0 + 1];
    SCE->REG_100H = S_RAM[20+0 + 2];
    SCE->REG_100H = S_RAM[20+0 + 3];
    SCE->REG_E0H = 0x80010000u;
    SCE->REG_104H = 0x00000068u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x3000a800u;
    SCE->REG_ECH = 0x00000006u;
    SCE->REG_ECH = 0x00010020u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000006u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x3420a800u;
    SCE->REG_ECH = 0x00000005u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0xa75beb2du, 0x0b0dc6e8u, 0x742eeb18u, 0xde0c5645u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
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
        SCE->REG_100H = change_endian_long(0x00000050u);
        HW_SCE_p_func101(0xf2c83e65u, 0x7f80c6a7u, 0xaea2052au, 0x050e7614u);
        HW_SCE_p_func043();
        SCE->REG_ECH = 0x0000b4e0u;
        SCE->REG_ECH = 0x00000007u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000050u);
        HW_SCE_p_func101(0xf21f08acu, 0xafe1d606u, 0x64a4b8e0u, 0x872de97bu);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0x66dc5d68u, 0x94d4454cu, 0x572c97f9u, 0xb1ae352du);
        SCE->REG_104H = 0x00000762u;
        SCE->REG_D0H = 0x40000100u;
        SCE->REG_C4H = 0x02f087b7u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[1];
        SCE->REG_100H = InData_KeyIndex[2];
        SCE->REG_100H = InData_KeyIndex[3];
        SCE->REG_100H = InData_KeyIndex[4];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_A4H = 0x00080805u;
        SCE->REG_00H = 0x00001213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0xa3d98bd6u, 0xde409614u, 0x4865160bu, 0xe2778f91u);
        SCE->REG_A4H = 0x00090805u;
        SCE->REG_00H = 0x00001213u;
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
        SCE->REG_100H = InData_KeyIndex[9];
        SCE->REG_100H = InData_KeyIndex[10];
        SCE->REG_100H = InData_KeyIndex[11];
        SCE->REG_100H = InData_KeyIndex[12];
        SCE->REG_C4H = 0x00900c45u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func101(0x1c335020u, 0x9f787ee6u, 0x3c9df4ebu, 0xfc302bdbu);
    }
    else
    {
        SCE->REG_104H = 0x00000368u;
        SCE->REG_E0H = 0x80040040u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[0];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[1];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[2];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[3];
        SCE->REG_ECH = 0x00000bdeu;
        SCE->REG_ECH = 0x000037e2u;
        SCE->REG_ECH = 0x00008fe0u;
        SCE->REG_ECH = 0x00ff0000u;
        SCE->REG_ECH = 0x38008be0u;
        SCE->REG_ECH = 0x00010000u;
        SCE->REG_ECH = 0x1000d3c0u;
        SCE->REG_ECH = 0x38008800u;
        SCE->REG_ECH = 0x00000005u;
        SCE->REG_ECH = 0x1000b540u;
        SCE->REG_ECH = 0x0000000fu;
        SCE->REG_ECH = 0x2000b540u;
        SCE->REG_ECH = 0x0000000eu;
        SCE->REG_ECH = 0x3800584au;
        SCE->REG_ECH = 0x2000d3c1u;
        SCE->REG_ECH = 0x000037e2u;
        SCE->REG_ECH = 0x00008fe0u;
        SCE->REG_ECH = 0x000000feu;
        SCE->REG_ECH = 0x38008be0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_ECH = 0x1000d3c2u;
        SCE->REG_ECH = 0x38008bc0u;
        SCE->REG_ECH = 0x00000007u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        SCE->REG_ECH = 0x0000a800u;
        SCE->REG_ECH = 0x00000003u;
        SCE->REG_ECH = 0x00003542u;
        SCE->REG_ECH = 0x00003563u;
        SCE->REG_ECH = 0x00003584u;
        SCE->REG_ECH = 0x000035a5u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000050u);
        HW_SCE_p_func101(0xbe7770c1u, 0x76a8f8b8u, 0x83aabf34u, 0x8aaf31f8u);
        HW_SCE_p_func059();
        HW_SCE_p_func100(0xfc41514eu, 0x17da911bu, 0xd1be8b6au, 0xb76ef6c2u);
        SCE->REG_104H = 0x00000762u;
        SCE->REG_D0H = 0x40000100u;
        SCE->REG_C4H = 0x02f087b7u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[4];
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[8];
        SCE->REG_100H = InData_KeyIndex[9];
        SCE->REG_100H = InData_KeyIndex[10];
        SCE->REG_100H = InData_KeyIndex[11];
        SCE->REG_A4H = 0x00080805u;
        SCE->REG_00H = 0x00001213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0x0d06633fu, 0x33b5eaf5u, 0xe669c903u, 0xe82117f6u);
        SCE->REG_A4H = 0x00090805u;
        SCE->REG_00H = 0x00001213u;
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
        SCE->REG_100H = InData_KeyIndex[12];
        SCE->REG_100H = InData_KeyIndex[13];
        SCE->REG_100H = InData_KeyIndex[14];
        SCE->REG_100H = InData_KeyIndex[15];
        SCE->REG_C4H = 0x00900c45u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func101(0x6477171au, 0x6c3a64ebu, 0x25a1b356u, 0xca8dc5d9u);
    }
    HW_SCE_p_func100(0x870632e2u, 0xcc4d5f31u, 0xd07aaac5u, 0x05592fc6u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xa0f62086u, 0xb4d95257u, 0x4a8a8cb7u, 0xb3231c7fu);
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
        HW_SCE_p_func100(0x535d3514u, 0xdabd83b5u, 0x3c1e4e54u, 0xf7550eb2u);
        SCE->REG_ECH = 0x00007c00u;
        SCE->REG_1CH = 0x00600000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
        {
            HW_SCE_p_func101(0x5910877eu, 0x9a9688e0u, 0xd01879feu, 0xac44966au);
        }
        else if (0x01000000u == (SCE->REG_1CH & 0xff000000u))
        {
            HW_SCE_p_func101(0xc15c53ebu, 0x5467c50fu, 0x454ecc55u, 0xef61db5eu);
        }
        else if (0x02000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00040805u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            HW_SCE_p_func101(0x2a869265u, 0xd7aa0acdu, 0xe047eb03u, 0xa0403e78u);
        }
        else if (0x03000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00040805u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            HW_SCE_p_func101(0x612ecac0u, 0x2675bbd3u, 0x23f488dcu, 0x2b4c76a5u);
        }
        else if (0x04000000u == (SCE->REG_1CH & 0xff000000u))
        {
            SCE->REG_104H = 0x00000361u;
            SCE->REG_A4H = 0x00040805u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            SCE->REG_100H = InData_IV[1];
            SCE->REG_100H = InData_IV[2];
            SCE->REG_100H = InData_IV[3];
            HW_SCE_p_func101(0x6882b60du, 0xc5fccc00u, 0x0f996f3eu, 0xf655eecfu);
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p50i_r1.prc
***********************************************************************************************************************/
