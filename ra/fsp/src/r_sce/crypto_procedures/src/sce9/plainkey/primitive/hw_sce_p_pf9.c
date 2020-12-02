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

fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSub(const uint32_t *InData_CurveType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PrivKeyIndex)
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
    SCE->REG_84H = 0x0000f902u;
    SCE->REG_108H = 0x00000000u;
    HW_SCE_p_func100(0xba8ae618u, 0x5d822127u, 0xa6afe272u, 0x6caf7220u);
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
    HW_SCE_p_func100(0x0b6231a1u, 0x4082f030u, 0x48c52f06u, 0x5326581du);
    HW_SCE_p_func027_r2(OFS_ADR);
    HW_SCE_p_func100(0x0b7f37d0u, 0xd0a2a81eu, 0x474b3adfu, 0x9178501bu);
    SCE->REG_28H = 0x008d0001u;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x41340726u, 0x77095143u, 0x72576630u, 0x93c93c46u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x00003213u;
    SCE->REG_2CH = 0x00000011u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xe7d4d41fu, 0x6983ba59u, 0x15f1cca4u, 0xf5ee9a3eu);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x00003213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xb89c36f1u, 0xebc180b7u, 0xd992e7d8u, 0x4a0de3e7u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x00003213u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    HW_SCE_p_func103();
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_00H = 0x0000320bu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000020bu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
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
    SCE->REG_24H = 0x0000c0c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000004u;
    SCE->REG_24H = 0x0000a206u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000000u;
    SCE->REG_24H = 0x000016c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000682u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c2u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x008b0001u;
    SCE->REG_24H = 0x0000dcd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000820u;
    SCE->REG_24H = 0x80009cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func100(0x3d1a8336u, 0x622e0f62u, 0xb1697e91u, 0xa005292fu);
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
    SCE->REG_24H = 0x00004404u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e8d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000808u;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func028_r2(OFS_ADR);
    HW_SCE_p_func100(0x64d66971u, 0x64ca9b9eu, 0x5940c872u, 0x204325b7u);
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
    SCE->REG_ECH = 0x00000bffu;
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
    SCE->REG_ECH = 0x000000f9u;
    SCE->REG_ECH = 0x00000b9cu;
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
        HW_SCE_p_func101(0xdbe796a4u, 0x6b1d9355u, 0xf4fd2662u, 0xd98cb7d6u);
        HW_SCE_p_func300();
        if (S_RAM[0] == 0x00000001)
        {
            break;
        }
        HW_SCE_p_func101(0xc0de3a65u, 0xfe27f27fu, 0x4d239102u, 0xb50f0d0au);
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
    HW_SCE_p_func100(0x1daa4a2du, 0x7ce5aa27u, 0xa5415a80u, 0x914b2f17u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x162e3ccbu, 0x2f9a1e6fu, 0x693474d6u, 0x94d238e3u);
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
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x8000f4d0u;
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
        SCE->REG_ECH = 0x00000bffu;
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
                HW_SCE_p_func100(0x8f9c2a77u, 0xf33844d5u, 0x8455d6fdu, 0x13143ad2u);
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
                    HW_SCE_p_func101(0x86ef67c2u, 0xe8cf24d0u, 0x37804e2au, 0xf098530du);
                }
                else
                {
                    HW_SCE_p_func101(0xf2132842u, 0x74acefcdu, 0x0c004a87u, 0x08b9d513u);
                }
            }
            SCE->REG_ECH = 0x000027e1u;
            HW_SCE_p_func101(0x01c83fafu, 0xef7c4381u, 0x10d53a54u, 0x051e247eu);
        }
        SCE->REG_ECH = 0x00008be0u;
        SCE->REG_ECH = 0x00000030u;
        SCE->REG_ECH = 0x00007c1fu;
        SCE->REG_1CH = 0x00602000u;
        HW_SCE_p_func301();
        HW_SCE_p_func100(0x88354d96u, 0xf9abfe45u, 0xcf2ad333u, 0x5c4b54aau);
        HW_SCE_p_func103();
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
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
        SCE->REG_ECH = 0x000034e0u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000f9u);
        HW_SCE_p_func101(0xd43c4306u, 0xb91b575bu, 0xded4cef2u, 0x3eedd0dfu);
        HW_SCE_p_func043();
        HW_SCE_p_func076();
        SCE->REG_ECH = 0x000034feu;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x000000f9u);
        HW_SCE_p_func101(0xa5113cbeu, 0x6d527565u, 0x8445bbf4u, 0xa1034407u);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0x6762285cu, 0x0d4cf93du, 0xa3506f40u, 0x1ceecb69u);
        SCE->REG_D0H = 0x40000200u;
        SCE->REG_C4H = 0x02e087b7u;
        SCE->REG_00H = 0x00002333u;
        SCE->REG_2CH = 0x0000002du;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_04H = 0x00000232u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[1] = SCE->REG_100H;
        OutData_PrivKeyIndex[2] = SCE->REG_100H;
        OutData_PrivKeyIndex[3] = SCE->REG_100H;
        OutData_PrivKeyIndex[4] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[5] = SCE->REG_100H;
        OutData_PrivKeyIndex[6] = SCE->REG_100H;
        OutData_PrivKeyIndex[7] = SCE->REG_100H;
        OutData_PrivKeyIndex[8] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[9] = SCE->REG_100H;
        OutData_PrivKeyIndex[10] = SCE->REG_100H;
        OutData_PrivKeyIndex[11] = SCE->REG_100H;
        OutData_PrivKeyIndex[12] = SCE->REG_100H;
        HW_SCE_p_func100(0xe81c9889u, 0x67692950u, 0xbe826a22u, 0x2e8a4dbeu);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x00000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x000089c5u;
        SCE->REG_00H = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_04H = 0x00000212u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[13] = SCE->REG_100H;
        OutData_PrivKeyIndex[14] = SCE->REG_100H;
        OutData_PrivKeyIndex[15] = SCE->REG_100H;
        OutData_PrivKeyIndex[16] = SCE->REG_100H;
        HW_SCE_p_func100(0x13b2eeb6u, 0xc897657du, 0x440a39ffu, 0xa369cdd9u);
        SCE->REG_E0H = 0x81010000u;
        SCE->REG_04H = 0x00000606u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PrivKeyIndex[0] = SCE->REG_100H;
        HW_SCE_p_func100(0x5582f747u, 0x39e01cb7u, 0x3691c4c7u, 0xe0da29edu);
        HW_SCE_p_func103();
        SCE->REG_104H = 0x00000052u;
        SCE->REG_C4H = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
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
        SCE->REG_ECH = 0x000034e0u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x800103a0u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000027u);
        HW_SCE_p_func101(0x70f41c99u, 0xba1e2bc7u, 0xa7b2ae76u, 0xe6f2e9fcu);
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
        SCE->REG_100H = change_endian_long(0x00000028u);
        HW_SCE_p_func101(0x2cabf676u, 0x643a1a6bu, 0xb94816b0u, 0xd195fadau);
        HW_SCE_p_func044();
        HW_SCE_p_func100(0x3901d920u, 0x63dad967u, 0x365fd72cu, 0x2905477du);
        SCE->REG_D0H = 0x40000200u;
        SCE->REG_C4H = 0x02e08887u;
        SCE->REG_00H = 0x00002333u;
        SCE->REG_2CH = 0x00000022u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_04H = 0x00000232u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[1] = SCE->REG_100H;
        OutData_PubKeyIndex[2] = SCE->REG_100H;
        OutData_PubKeyIndex[3] = SCE->REG_100H;
        OutData_PubKeyIndex[4] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[5] = SCE->REG_100H;
        OutData_PubKeyIndex[6] = SCE->REG_100H;
        OutData_PubKeyIndex[7] = SCE->REG_100H;
        OutData_PubKeyIndex[8] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[9] = SCE->REG_100H;
        OutData_PubKeyIndex[10] = SCE->REG_100H;
        OutData_PubKeyIndex[11] = SCE->REG_100H;
        OutData_PubKeyIndex[12] = SCE->REG_100H;
        HW_SCE_p_func100(0xdc1ff7abu, 0x50b66339u, 0x2bc1b6f1u, 0x0303639fu);
        SCE->REG_D0H = 0x40000200u;
        SCE->REG_C4H = 0x00e08887u;
        SCE->REG_00H = 0x00002333u;
        SCE->REG_2CH = 0x00000023u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_04H = 0x00000232u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[13] = SCE->REG_100H;
        OutData_PubKeyIndex[14] = SCE->REG_100H;
        OutData_PubKeyIndex[15] = SCE->REG_100H;
        OutData_PubKeyIndex[16] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[17] = SCE->REG_100H;
        OutData_PubKeyIndex[18] = SCE->REG_100H;
        OutData_PubKeyIndex[19] = SCE->REG_100H;
        OutData_PubKeyIndex[20] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[21] = SCE->REG_100H;
        OutData_PubKeyIndex[22] = SCE->REG_100H;
        OutData_PubKeyIndex[23] = SCE->REG_100H;
        OutData_PubKeyIndex[24] = SCE->REG_100H;
        HW_SCE_p_func100(0x7d1ad014u, 0xbcf9baa2u, 0x3a53ca7cu, 0x64a40b32u);
        SCE->REG_104H = 0x00000052u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x000089c4u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_04H = 0x00000212u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[25] = SCE->REG_100H;
        OutData_PubKeyIndex[26] = SCE->REG_100H;
        OutData_PubKeyIndex[27] = SCE->REG_100H;
        OutData_PubKeyIndex[28] = SCE->REG_100H;
        HW_SCE_p_func100(0x5e7bb2b6u, 0xa502456fu, 0xbca534c6u, 0x74f8870fu);
        SCE->REG_E0H = 0x81010000u;
        SCE->REG_04H = 0x00000606u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_PubKeyIndex[0] = SCE->REG_100H;
        HW_SCE_p_func102(0xad16c748u, 0x1d60a10du, 0xfbdbbe7au, 0xd146affau);
        SCE->REG_1B8H = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_pf9_r4.prc
***********************************************************************************************************************/
