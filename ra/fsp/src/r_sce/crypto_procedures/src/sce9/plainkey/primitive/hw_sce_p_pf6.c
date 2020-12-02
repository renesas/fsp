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

fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSub(const uint32_t *InData_CurveType, const uint32_t *InData_KeyIndex, const uint32_t *InData_MsgDgst, const uint32_t *InData_Signature)
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
    SCE->REG_84H = 0x0000f601u;
    SCE->REG_108H = 0x00000000u;
    HW_SCE_p_func100(0xde86a436u, 0x5028d235u, 0xd797fae2u, 0xe51894ddu);
    SCE->REG_28H = 0x008b0001u;
    SCE->REG_104H = 0x00000068u;
    SCE->REG_E0H = 0x80010340u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_ECH = 0x38000f5au;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x000002B4u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x000003D8u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_E0H = 0x81010000u;
    SCE->REG_04H = 0x00000606u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    OFS_ADR = S_RAM[0];
    HW_SCE_p_func100(0x50f75db7u, 0x80f401ceu, 0x2b894e39u, 0xb0cb9752u);
    HW_SCE_p_func027_r2(OFS_ADR);
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x80006cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x8000bcd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000015u;
    SCE->REG_104H = 0x00000b67u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Signature[0];
    SCE->REG_100H = InData_Signature[1];
    SCE->REG_100H = InData_Signature[2];
    SCE->REG_100H = InData_Signature[3];
    SCE->REG_100H = InData_Signature[4];
    SCE->REG_100H = InData_Signature[5];
    SCE->REG_100H = InData_Signature[6];
    SCE->REG_100H = InData_Signature[7];
    SCE->REG_100H = InData_Signature[8];
    SCE->REG_100H = InData_Signature[9];
    SCE->REG_100H = InData_Signature[10];
    SCE->REG_100H = InData_Signature[11];
    SCE->REG_2CH = 0x00000010u;
    SCE->REG_104H = 0x00000b67u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Signature[12];
    SCE->REG_100H = InData_Signature[13];
    SCE->REG_100H = InData_Signature[14];
    SCE->REG_100H = InData_Signature[15];
    SCE->REG_100H = InData_Signature[16];
    SCE->REG_100H = InData_Signature[17];
    SCE->REG_100H = InData_Signature[18];
    SCE->REG_100H = InData_Signature[19];
    SCE->REG_100H = InData_Signature[20];
    SCE->REG_100H = InData_Signature[21];
    SCE->REG_100H = InData_Signature[22];
    SCE->REG_100H = InData_Signature[23];
    SCE->REG_ECH = 0x0000b7e0u;
    SCE->REG_ECH = 0x00000140u;
    SCE->REG_E0H = 0x808c001fu;
    SCE->REG_00H = 0x00008333u;
    SCE->REG_2CH = 0x00000024u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x000070d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000084d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00021028u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x100019b1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x8000c0c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00008cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001dc0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000060c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000d91u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001f00u;
    SCE->REG_1CH = 0x00210000u;
    SCE->REG_24H = 0x00000dc0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001f00u;
    SCE->REG_1CH = 0x00210000u;
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001f00u;
    SCE->REG_1CH = 0x00210000u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001f00u;
    SCE->REG_1CH = 0x00210000u;
    HW_SCE_p_func100(0x48dc9437u, 0x7d99e59au, 0x359b6d56u, 0x26bc5175u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xb0a214e8u, 0x3ea6e6fdu, 0x18a83f65u, 0x349085f8u);
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
        SCE->REG_24H = 0x000019c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00005004u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00008404u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b420u;
        SCE->REG_ECH = 0x00000004u;
        SCE->REG_ECH = 0x0000b7e0u;
        SCE->REG_ECH = 0x00000100u;
        SCE->REG_E0H = 0x808c001fu;
        SCE->REG_00H = 0x00008333u;
        SCE->REG_2CH = 0x00000021u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        for(iLoop=0; iLoop<12; iLoop=iLoop+1)
        {
            SCE->REG_ECH = 0x0000381fu;
            for(jLoop=0; jLoop<32; jLoop=jLoop+1)
            {
                SCE->REG_24H = 0x0000102cu;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x100019b1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000019a1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x3800d81fu;
                SCE->REG_E0H = 0x00000080u;
                SCE->REG_1CH = 0x00A60000u;
                SCE->REG_ECH = 0x00016c00u;
                HW_SCE_p_func100(0x4f50ce7au, 0x5b245d5du, 0x09650643u, 0x292d4bbfu);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (1u == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_24H = 0x0000082cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    HW_SCE_p_func101(0xbfbe8c9cu, 0x3d95ed3cu, 0x3cf22247u, 0xa53ed86cu);
                }
                else
                {
                    HW_SCE_p_func101(0xc389e42cu, 0x971fe1eau, 0xd116d4fcu, 0x87c07bd4u);
                }
            }
            SCE->REG_ECH = 0x000027e1u;
            HW_SCE_p_func101(0x89976506u, 0x0f51be2du, 0x4581d2b3u, 0x31ad08acu);
        }
        SCE->REG_ECH = 0x00008be0u;
        SCE->REG_ECH = 0x00000130u;
        SCE->REG_ECH = 0x00007c1fu;
        SCE->REG_1CH = 0x00602000u;
        HW_SCE_p_func100(0x6e827556u, 0x95f748d3u, 0x599c27e2u, 0x22b78e38u);
        SCE->REG_24H = 0x00001dc0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000060c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_2CH = 0x00000011u;
        SCE->REG_104H = 0x00000b67u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MsgDgst[0];
        SCE->REG_100H = InData_MsgDgst[1];
        SCE->REG_100H = InData_MsgDgst[2];
        SCE->REG_100H = InData_MsgDgst[3];
        SCE->REG_100H = InData_MsgDgst[4];
        SCE->REG_100H = InData_MsgDgst[5];
        SCE->REG_100H = InData_MsgDgst[6];
        SCE->REG_100H = InData_MsgDgst[7];
        SCE->REG_100H = InData_MsgDgst[8];
        SCE->REG_100H = InData_MsgDgst[9];
        SCE->REG_100H = InData_MsgDgst[10];
        SCE->REG_100H = InData_MsgDgst[11];
        SCE->REG_ECH = 0x0000094au;
        SCE->REG_E0H = 0x808c000au;
        SCE->REG_00H = 0x00008333u;
        SCE->REG_2CH = 0x00000023u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x00000c2cu;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000019a1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000060c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000094d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000c2cu;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000019a1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000a0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000009c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000e0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008u;
        SCE->REG_24H = 0x8000d4d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000084d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00021028u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000019a1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x8000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000002u;
        SCE->REG_24H = 0x80004cd0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func028_r2(OFS_ADR);
        SCE->REG_34H = 0x00000802u;
        SCE->REG_24H = 0x800088d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000802u;
        SCE->REG_24H = 0x8000acd0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b540u;
        SCE->REG_ECH = 0x00000040u;
        SCE->REG_E0H = 0x808c000au;
        SCE->REG_00H = 0x00008333u;
        SCE->REG_2CH = 0x00000025u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x000009c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001028u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000019a1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000e0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b7e0u;
        SCE->REG_ECH = 0x00000100u;
        SCE->REG_E0H = 0x808c001fu;
        SCE->REG_00H = 0x00008333u;
        SCE->REG_2CH = 0x00000021u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_ECH = 0x00000bdeu;
        SCE->REG_ECH = 0x00000842u;
        SCE->REG_ECH = 0x0000b420u;
        SCE->REG_ECH = 0x00000004u;
        SCE->REG_ECH = 0x0000b480u;
        SCE->REG_ECH = 0x00000180u;
        SCE->REG_ECH = 0x0000b7a0u;
        SCE->REG_ECH = 0x000000f6u;
        SCE->REG_ECH = 0x00000b9cu;
        HW_SCE_p_func100(0x207fcddau, 0x5d1f4932u, 0x025fe82bu, 0x311610c3u);
        SCE->REG_E0H = 0x81010380u;
        SCE->REG_04H = 0x00000607u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for(iLoop=0;iLoop<384;iLoop=iLoop+1)
        {
            HW_SCE_p_func101(0x343faaa0u, 0xc8a220e1u, 0x9e286aadu, 0x12ebe9cfu);
            HW_SCE_p_func302();
            if (S_RAM[0] == 0x00000001)
            {
                break;
            }
            HW_SCE_p_func101(0xfe611096u, 0xf63529f2u, 0x1bc80c49u, 0xb74546a0u);
        }
        SCE->REG_ECH = 0x0000b660u;
        SCE->REG_ECH = 0x00000040u;
        SCE->REG_E0H = 0x818c0013u;
        SCE->REG_00H = 0x00003833u;
        SCE->REG_2CH = 0x0000001au;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x00001dc0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00u;
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0x77781b31u, 0x7ee34842u, 0x3e67a132u, 0x866f6dffu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x0d2df2eau, 0xcafdcc6du, 0x4b14a008u, 0xeecb2b39u);
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
            SCE->REG_24H = 0x00004404u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00004804u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000040u;
            SCE->REG_E0H = 0x808c001fu;
            SCE->REG_00H = 0x00008333u;
            SCE->REG_2CH = 0x00000022u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_34H = 0x00000800u;
            SCE->REG_24H = 0x800068d0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001dc0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000a0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00005004u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00008404u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b420u;
            SCE->REG_ECH = 0x00000004u;
            SCE->REG_ECH = 0x0000b7e0u;
            SCE->REG_ECH = 0x00000100u;
            SCE->REG_E0H = 0x808c001fu;
            SCE->REG_00H = 0x00008333u;
            SCE->REG_2CH = 0x00000021u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            for(iLoop=0; iLoop<12; iLoop=iLoop+1)
            {
                SCE->REG_ECH = 0x0000381fu;
                for(jLoop=0; jLoop<32; jLoop=jLoop+1)
                {
                    SCE->REG_24H = 0x0000102cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_ECH = 0x3800d81fu;
                    SCE->REG_E0H = 0x00000080u;
                    SCE->REG_1CH = 0x00A60000u;
                    SCE->REG_ECH = 0x00016c00u;
                    HW_SCE_p_func100(0x1f9de355u, 0x2cf5dd10u, 0xafc11e8cu, 0x2e0989d4u);
                    SCE->REG_1CH = 0x00400000u;
                    SCE->REG_1D0H = 0x00000000u;
                    if (1u == (SCE->REG_1CH_b.B22))
                    {
                        SCE->REG_24H = 0x0000082cu;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000080c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        HW_SCE_p_func101(0x63ed1c79u, 0x60fce20bu, 0xfd1676abu, 0x4b71e169u);
                    }
                    else
                    {
                        HW_SCE_p_func101(0xf236aa04u, 0xdba8fd83u, 0xf47ee85eu, 0x10f90084u);
                    }
                }
                SCE->REG_ECH = 0x000027e1u;
                HW_SCE_p_func101(0x09d2c05eu, 0xfc984d92u, 0xe5594ea9u, 0x41078609u);
            }
            SCE->REG_ECH = 0x00008be0u;
            SCE->REG_ECH = 0x00000130u;
            SCE->REG_ECH = 0x00007c1fu;
            SCE->REG_1CH = 0x00602000u;
            SCE->REG_34H = 0x00000002u;
            SCE->REG_24H = 0x80000dc0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000009c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000a0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000008u;
            SCE->REG_24H = 0x800011c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000a2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000082cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000082cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000a2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000008u;
            SCE->REG_24H = 0x800015c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000e2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000c2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000c2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000c2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000e2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000e2cu;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000060c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000015c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00001028u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000e0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000002u;
            SCE->REG_24H = 0x800009c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000a0c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000009c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800u;
            SCE->REG_24H = 0x800080c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000011c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
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
            SCE->REG_100H = change_endian_long(0x000000f6u);
            HW_SCE_p_func101(0xabde0957u, 0x0fbfdc07u, 0x816885b7u, 0x6864b23eu);
            HW_SCE_p_func043();
            HW_SCE_p_func077();
            SCE->REG_ECH = 0x000034feu;
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000f6u);
            HW_SCE_p_func101(0x11952f36u, 0x92fa06b0u, 0xbec6cccfu, 0xdd60618cu);
            HW_SCE_p_func044();
            SCE->REG_104H = 0x00000052u;
            SCE->REG_C4H = 0x00040804u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_104H = 0x00001762u;
            SCE->REG_D0H = 0x40000500u;
            SCE->REG_C4H = 0x02e08887u;
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
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[9];
            SCE->REG_100H = InData_KeyIndex[10];
            SCE->REG_100H = InData_KeyIndex[11];
            SCE->REG_100H = InData_KeyIndex[12];
            SCE->REG_00H = 0x00003233u;
            SCE->REG_2CH = 0x00000010u;
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
            SCE->REG_100H = InData_KeyIndex[13];
            SCE->REG_100H = InData_KeyIndex[14];
            SCE->REG_100H = InData_KeyIndex[15];
            SCE->REG_100H = InData_KeyIndex[16];
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[17];
            SCE->REG_100H = InData_KeyIndex[18];
            SCE->REG_100H = InData_KeyIndex[19];
            SCE->REG_100H = InData_KeyIndex[20];
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[21];
            SCE->REG_100H = InData_KeyIndex[22];
            SCE->REG_100H = InData_KeyIndex[23];
            SCE->REG_100H = InData_KeyIndex[24];
            SCE->REG_00H = 0x00003233u;
            SCE->REG_2CH = 0x0000001bu;
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
            SCE->REG_100H = InData_KeyIndex[25];
            SCE->REG_100H = InData_KeyIndex[26];
            SCE->REG_100H = InData_KeyIndex[27];
            SCE->REG_100H = InData_KeyIndex[28];
            SCE->REG_C4H = 0x00900c45u;
            SCE->REG_00H = 0x00002213u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            HW_SCE_p_func100(0xf18601a4u, 0x70bb1760u, 0x318349cbu, 0xff5d1355u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x559c24e4u, 0xf2aa0acdu, 0x8b9b73a1u, 0x3b80136fu);
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
                SCE->REG_24H = 0x0000082cu;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x100019b1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000019a1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000002u;
                SCE->REG_24H = 0x80008cd0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000082cu;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x100019b1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000019a1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800060c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000008u;
                SCE->REG_24H = 0x800011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000002u;
                SCE->REG_24H = 0x800009c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x800080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000002u;
                SCE->REG_24H = 0x80000dc0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000800u;
                SCE->REG_24H = 0x8000a0c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b540u;
                SCE->REG_ECH = 0x00000080u;
                SCE->REG_E0H = 0x808c000au;
                SCE->REG_00H = 0x00008333u;
                SCE->REG_2CH = 0x00000022u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b540u;
                SCE->REG_ECH = 0x000000C0u;
                SCE->REG_E0H = 0x808c000au;
                SCE->REG_00H = 0x00008333u;
                SCE->REG_2CH = 0x00000023u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x0000b7e0u;
                SCE->REG_ECH = 0x00000100u;
                SCE->REG_E0H = 0x808c001fu;
                SCE->REG_00H = 0x00008333u;
                SCE->REG_2CH = 0x00000021u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800u;
                SCE->REG_ECH = 0x00000bdeu;
                SCE->REG_ECH = 0x00000842u;
                SCE->REG_ECH = 0x0000b420u;
                SCE->REG_ECH = 0x00000004u;
                SCE->REG_ECH = 0x0000b480u;
                SCE->REG_ECH = 0x00000180u;
                SCE->REG_ECH = 0x0000b7a0u;
                SCE->REG_ECH = 0x00000002u;
                SCE->REG_ECH = 0x00000b9cu;
                HW_SCE_p_func100(0xf316d8d2u, 0x79929798u, 0x751a3d39u, 0xe14b89b8u);
                SCE->REG_E0H = 0x81010380u;
                SCE->REG_04H = 0x00000607u;
                /* WAIT_LOOP */
                while (1u != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = change_endian_long(SCE->REG_100H);
                for(iLoop=0;iLoop<384;iLoop=iLoop+1)
                {
                    HW_SCE_p_func101(0x67d6accfu, 0x410dac54u, 0xd335e1bfu, 0x3a9b29d0u);
                    HW_SCE_p_func302();
                    if (S_RAM[0] == 0x00000001)
                    {
                        break;
                    }
                    HW_SCE_p_func101(0x8dc9b62au, 0xea2a3202u, 0x330c3721u, 0xed7351f2u);
                }
                SCE->REG_24H = 0x00001dc0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001f00u;
                SCE->REG_1CH = 0x00210000u;
                HW_SCE_p_func100(0x53ca79ecu, 0x8c5fbfbeu, 0x789481f8u, 0x2f64684cu);
                SCE->REG_1CH = 0x00400000u;
                SCE->REG_1D0H = 0x00000000u;
                if (1u == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x17c9dd80u, 0x82da83bfu, 0x0d790543u, 0x50485666u);
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
                    SCE->REG_ECH = 0x0000b660u;
                    SCE->REG_ECH = 0x00000080u;
                    SCE->REG_E0H = 0x818c0013u;
                    SCE->REG_00H = 0x00003833u;
                    SCE->REG_2CH = 0x0000001au;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800u;
                    SCE->REG_ECH = 0x0000b660u;
                    SCE->REG_ECH = 0x000000C0u;
                    SCE->REG_E0H = 0x818c0013u;
                    SCE->REG_00H = 0x00003833u;
                    SCE->REG_2CH = 0x0000001bu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800u;
                    SCE->REG_24H = 0x00009cd0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000102cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000070d0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000002u;
                    SCE->REG_24H = 0x800048d0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000082cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000c2cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000008u;
                    SCE->REG_24H = 0x800011c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000200u;
                    SCE->REG_24H = 0x80000a41u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000008u;
                    SCE->REG_24H = 0x800011c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000200u;
                    SCE->REG_24H = 0x80000951u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000002u;
                    SCE->REG_24H = 0x80004cd0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000082cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000280u;
                    SCE->REG_24H = 0x800019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000080u;
                    SCE->REG_24H = 0x800080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000c2cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000e0c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000102cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000060c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000c2cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000200u;
                    SCE->REG_24H = 0x900019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000280u;
                    SCE->REG_24H = 0x800019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000008u;
                    SCE->REG_24H = 0x800015c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000941u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000008u;
                    SCE->REG_24H = 0x800015c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000951u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000080u;
                    SCE->REG_24H = 0x800040c2u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000200u;
                    SCE->REG_24H = 0x800012c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00008cd0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000060c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000082cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00008cd0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000102cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000951u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000800u;
                    SCE->REG_24H = 0x800080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000149u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000060c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000009c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000d51u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x0000082cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000080u;
                    SCE->REG_24H = 0x800080c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000080u;
                    SCE->REG_24H = 0x800060c2u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000c2cu;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x100019b1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000060c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000009c0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000d51u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000019a1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000145u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000800u;
                    SCE->REG_24H = 0x8000a0c1u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00001dc0u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000591u;
                    /* WAIT_LOOP */
                    while (0u != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001f00u;
                    SCE->REG_1CH = 0x00210000u;
                    HW_SCE_p_func100(0x5a83c212u, 0x26eaa86eu, 0x1abecd3au, 0xf8dd0538u);
                    SCE->REG_1CH = 0x00400000u;
                    SCE->REG_1D0H = 0x00000000u;
                    if (1u == (SCE->REG_1CH_b.B22))
                    {
                        HW_SCE_p_func102(0x69e5c4abu, 0xbc0d5482u, 0xc110625bu, 0x71573c04u);
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
                        SCE->REG_ECH = 0x0000b7e0u;
                        SCE->REG_ECH = 0x00000040u;
                        SCE->REG_E0H = 0x818c001fu;
                        SCE->REG_00H = 0x00003833u;
                        SCE->REG_2CH = 0x00000012u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800u;
                        SCE->REG_34H = 0x00000800u;
                        SCE->REG_24H = 0x800068d0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00001dc0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000080c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000019c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000591u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000591u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x0000a0c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00005004u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00008404u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_ECH = 0x0000b420u;
                        SCE->REG_ECH = 0x00000004u;
                        SCE->REG_ECH = 0x0000b7e0u;
                        SCE->REG_ECH = 0x00000100u;
                        SCE->REG_E0H = 0x808c001fu;
                        SCE->REG_00H = 0x00008333u;
                        SCE->REG_2CH = 0x00000021u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800u;
                        for(iLoop=0; iLoop<12; iLoop=iLoop+1)
                        {
                            SCE->REG_ECH = 0x0000381fu;
                            for(jLoop=0; jLoop<32; jLoop=jLoop+1)
                            {
                                SCE->REG_24H = 0x0000102cu;
                                /* WAIT_LOOP */
                                while (0u != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_24H = 0x100019b1u;
                                /* WAIT_LOOP */
                                while (0u != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_24H = 0x000019a1u;
                                /* WAIT_LOOP */
                                while (0u != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_24H = 0x000080c1u;
                                /* WAIT_LOOP */
                                while (0u != SCE->REG_24H_b.B21)
                                {
                                    /* waiting */
                                }
                                SCE->REG_ECH = 0x3800d81fu;
                                SCE->REG_E0H = 0x00000080u;
                                SCE->REG_1CH = 0x00A60000u;
                                SCE->REG_ECH = 0x00016c00u;
                                HW_SCE_p_func100(0x1fca6902u, 0xdb92fa7cu, 0x246ef741u, 0x05211b66u);
                                SCE->REG_1CH = 0x00400000u;
                                SCE->REG_1D0H = 0x00000000u;
                                if (1u == (SCE->REG_1CH_b.B22))
                                {
                                    SCE->REG_24H = 0x0000082cu;
                                    /* WAIT_LOOP */
                                    while (0u != SCE->REG_24H_b.B21)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_24H = 0x100019b1u;
                                    /* WAIT_LOOP */
                                    while (0u != SCE->REG_24H_b.B21)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_24H = 0x000019a1u;
                                    /* WAIT_LOOP */
                                    while (0u != SCE->REG_24H_b.B21)
                                    {
                                        /* waiting */
                                    }
                                    SCE->REG_24H = 0x000080c1u;
                                    /* WAIT_LOOP */
                                    while (0u != SCE->REG_24H_b.B21)
                                    {
                                        /* waiting */
                                    }
                                    HW_SCE_p_func101(0x26c9111fu, 0x476535c1u, 0x13d0b543u, 0xe890e9f3u);
                                }
                                else
                                {
                                    HW_SCE_p_func101(0x03806e32u, 0xa9ed89feu, 0x00e95f20u, 0x5db753ccu);
                                }
                            }
                            SCE->REG_ECH = 0x000027e1u;
                            HW_SCE_p_func101(0xd048889eu, 0x80940a86u, 0x6baaaf20u, 0x544eb0bfu);
                        }
                        SCE->REG_ECH = 0x00008be0u;
                        SCE->REG_ECH = 0x00000130u;
                        SCE->REG_ECH = 0x00007c1fu;
                        SCE->REG_1CH = 0x00602000u;
                        SCE->REG_34H = 0x00000002u;
                        SCE->REG_24H = 0x80000dc0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000040c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000009c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x0000a0c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000008u;
                        SCE->REG_24H = 0x800011c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000040c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000a2cu;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000040c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x0000082cu;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000040c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x0000082cu;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000040c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_ECH = 0x0000b7e0u;
                        SCE->REG_ECH = 0x00000140u;
                        SCE->REG_E0H = 0x818c001fu;
                        SCE->REG_00H = 0x00003833u;
                        SCE->REG_2CH = 0x00000014u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800u;
                        SCE->REG_24H = 0x000084d0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00021028u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000800u;
                        SCE->REG_24H = 0x8000c0c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000088d0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00009004u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00001028u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x100019b1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000019a1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x000040c1u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_ECH = 0x0000b660u;
                        SCE->REG_ECH = 0x00000000u;
                        SCE->REG_E0H = 0x818c0013u;
                        SCE->REG_00H = 0x00003833u;
                        SCE->REG_2CH = 0x00000014u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800u;
                        SCE->REG_24H = 0x000009c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00001991u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001f00u;
                        SCE->REG_1CH = 0x00210000u;
                        SCE->REG_24H = 0x000019c0u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_24H = 0x00000991u;
                        /* WAIT_LOOP */
                        while (0u != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001f00u;
                        SCE->REG_1CH = 0x00210000u;
                        HW_SCE_p_func100(0x5c2d0ec5u, 0xc2315674u, 0xdcad06ccu, 0x6322755fu);
                        SCE->REG_1CH = 0x00400000u;
                        SCE->REG_1D0H = 0x00000000u;
                        if (1u == (SCE->REG_1CH_b.B22))
                        {
                            HW_SCE_p_func102(0xdb95f1aau, 0xbf1fe75bu, 0xa804bf04u, 0x7c374249u);
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
                            HW_SCE_p_func102(0x914a2eb8u, 0x0568a5aeu, 0x5d214490u, 0xb78ae4f6u);
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
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pf6_r3.prc
***********************************************************************************************************************/
