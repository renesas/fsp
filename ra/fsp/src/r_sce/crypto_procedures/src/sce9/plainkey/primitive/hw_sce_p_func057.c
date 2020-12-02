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

void HW_SCE_p_func057_r1(uint32_t* ARG1, uint32_t* ARG2, uint32_t* ARG3)
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
    HW_SCE_p_func100(0xf31fc280u, 0xb1f04b9eu, 0x9454ff9bu, 0x9c90f37eu);
    SCE->REG_104H = 0x00000361u;
    SCE->REG_A4H = 0x00040805u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG1[0];
    SCE->REG_100H = ARG1[1];
    SCE->REG_100H = ARG1[2];
    SCE->REG_100H = ARG1[3];
    SCE->REG_104H = 0x00000051u;
    SCE->REG_A4H = 0x00050804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
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
    SCE->REG_100H = change_endian_long(0x000000ffu);
    HW_SCE_p_func101(0xab47b184u, 0xfa6aa1bfu, 0x2f5a393fu, 0x383be959u);
    HW_SCE_p_func043();
    SCE->REG_ECH = 0x000034e4u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x800103a0u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000feu);
    HW_SCE_p_func101(0x8579d3eau, 0x0270bbfcu, 0x83222df1u, 0x72d3673du);
    HW_SCE_p_func044();
    HW_SCE_p_func100(0x09b4fe19u, 0xcd9e71fau, 0x41f1394cu, 0xd138ac96u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00040804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_104H = 0x00000052u;
    SCE->REG_C4H = 0x00050804u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000u);
    HW_SCE_p_func081();
    SCE->REG_ECH = 0x00007c01u;
    SCE->REG_1CH = 0x00600000u;
    SCE->REG_1D0H = 0x00000000u;
    if (0x00000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0xd863f335u, 0x104e1c40u, 0x70842eb1u, 0xa48e0ba2u);
        SCE->REG_00H = 0x80002100u;
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x00d049a6u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x02e087b6u;
        SCE->REG_04H = 0x0000c200u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[0];
        SCE->REG_100H = ARG2[1];
        SCE->REG_100H = ARG2[2];
        SCE->REG_100H = ARG2[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-8) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG2[4+iLoop + 0];
            SCE->REG_100H = ARG2[4+iLoop + 1];
            SCE->REG_100H = ARG2[4+iLoop + 2];
            SCE->REG_100H = ARG2[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+iLoop + 0] = SCE->REG_100H;
            ARG3[1+iLoop + 1] = SCE->REG_100H;
            ARG3[1+iLoop + 2] = SCE->REG_100H;
            ARG3[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG3[1+iLoop + 0] = SCE->REG_100H;
        ARG3[1+iLoop + 1] = SCE->REG_100H;
        ARG3[1+iLoop + 2] = SCE->REG_100H;
        ARG3[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x4ca67631u, 0xbfe8efa6u, 0x42650b01u, 0x9a59c797u);
    }
    else if (0x0a000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0xc39300fcu, 0x932823bau, 0xdc7a21f7u, 0x41e8b020u);
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_00H = 0x00003183u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func061(0,ARG2);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000024u;
        SCE->REG_D0H = 0x40000700u;
        SCE->REG_C4H = 0x02e08887u;
        SCE->REG_04H = 0x00000282u;
        for(oLoop=0; oLoop<32; oLoop=oLoop+4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+oLoop + 0] = SCE->REG_100H;
            ARG3[1+oLoop + 1] = SCE->REG_100H;
            ARG3[1+oLoop + 2] = SCE->REG_100H;
            ARG3[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0x4efe8e8au, 0xfeed2dfcu, 0xdadb5c4au, 0x65e1b33du);
        SCE->REG_104H = 0x00000361u;
        SCE->REG_A4H = 0x00d049a5u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[iLoop + 0];
        SCE->REG_100H = ARG2[iLoop + 1];
        SCE->REG_100H = ARG2[iLoop + 2];
        SCE->REG_100H = ARG2[iLoop + 3];
        iLoop = iLoop + 4;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x00e08885u;
        SCE->REG_00H = 0x00002113u;
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
        ARG3[1+oLoop + 0] = SCE->REG_100H;
        ARG3[1+oLoop + 1] = SCE->REG_100H;
        ARG3[1+oLoop + 2] = SCE->REG_100H;
        ARG3[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0u != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xa393ce95u, 0x386cc78fu, 0x4a0dde05u, 0x23b90198u);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func062(36,ARG3);
        oLoop = 36 + 32;
        HW_SCE_p_func101(0xb78e40beu, 0x9a507c58u, 0xa058119cu, 0x4604a55au);
    }
    else if (0x0b000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0x0ec0ae03u, 0xbdb21de0u, 0x33e56e86u, 0x9376b996u);
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_00H = 0x00003183u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func061(0,ARG2);
        iLoop = 0 + 32;
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000024u;
        HW_SCE_p_func062(0,ARG3);
        oLoop = 0 + 32;
        HW_SCE_p_func100(0x04750e53u, 0x7952bb79u, 0xc5800b7eu, 0x403b9779u);
        SCE->REG_00H = 0x00003183u;
        SCE->REG_2CH = 0x00000011u;
        HW_SCE_p_func061(32,ARG2);
        iLoop = 32 + 32;
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000021u;
        HW_SCE_p_func062(32,ARG3);
        oLoop = 32 + 32;
        HW_SCE_p_func100(0xf1f9707fu, 0x25d81b4fu, 0x22350d39u, 0x14f1ca2au);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func062(64,ARG3);
        oLoop = 64 + 32;
        HW_SCE_p_func101(0x03dad023u, 0xcec3eca2u, 0xaa31e30fu, 0x45a27577u);
    }
    else if (0x0c000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0x40b8f383u, 0xcc74ecfdu, 0xa253bdf2u, 0x5d08ae64u);
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_00H = 0x00013103u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func063(0,ARG2);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000024u;
        SCE->REG_D0H = 0x40000f00u;
        SCE->REG_C4H = 0x02e08887u;
        SCE->REG_04H = 0x00000202u;
        for(oLoop=0; oLoop<64; oLoop=oLoop+4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+oLoop + 0] = SCE->REG_100H;
            ARG3[1+oLoop + 1] = SCE->REG_100H;
            ARG3[1+oLoop + 2] = SCE->REG_100H;
            ARG3[1+oLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        HW_SCE_p_func100(0xd5560200u, 0x28a09e8eu, 0xdf18a10au, 0xa09ce3bdu);
        SCE->REG_104H = 0x00000361u;
        SCE->REG_A4H = 0x00d049a5u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[iLoop + 0];
        SCE->REG_100H = ARG2[iLoop + 1];
        SCE->REG_100H = ARG2[iLoop + 2];
        SCE->REG_100H = ARG2[iLoop + 3];
        iLoop = iLoop + 4;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x00e08885u;
        SCE->REG_00H = 0x00002113u;
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
        ARG3[1+oLoop + 0] = SCE->REG_100H;
        ARG3[1+oLoop + 1] = SCE->REG_100H;
        ARG3[1+oLoop + 2] = SCE->REG_100H;
        ARG3[1+oLoop + 3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (0u != SCE->REG_C8H_b.B6)
        {
            /* waiting */
        }
        HW_SCE_p_func100(0xb55664d8u, 0xdda299b2u, 0xa618943du, 0x763fa4a4u);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func064(68,ARG3);
        oLoop = 68 + 64;
        HW_SCE_p_func101(0x197c0cd4u, 0x2641e686u, 0xca561b5au, 0x3a15237au);
    }
    else if (0x0d000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0xbe980790u, 0x643b9dc7u, 0x163962b6u, 0xc3cc6613u);
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_00H = 0x00013103u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func063(0,ARG2);
        iLoop = 0 + 64;
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000024u;
        HW_SCE_p_func064(0,ARG3);
        oLoop = 0 + 64;
        HW_SCE_p_func100(0x7e2b313au, 0xa6926a4du, 0x837b0236u, 0xe47c35d1u);
        SCE->REG_00H = 0x00013103u;
        SCE->REG_2CH = 0x00000010u;
        HW_SCE_p_func063(64,ARG2);
        iLoop = 64 + 64;
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func064(64,ARG3);
        oLoop = 64 + 64;
        HW_SCE_p_func100(0xee7b76e5u, 0xc6116ce8u, 0x9952521eu, 0xf6ef1e2fu);
        HW_SCE_p_func060();
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func064(128,ARG3);
        oLoop = 128 + 64;
        HW_SCE_p_func101(0x0bbc011eu, 0x8bf07c60u, 0x4ce1e9aau, 0x24601a0cu);
    }
    else if (0x12000000u == (SCE->REG_1CH & 0xff000000u))
    {
        HW_SCE_p_func100(0xdb02e3c5u, 0x8f35d0d4u, 0xb1fca80fu, 0xd78d93b5u);
        SCE->REG_00H = 0x80002100u;
        SCE->REG_104H = 0x000000b1u;
        SCE->REG_A4H = 0x00d049a6u;
        SCE->REG_D0H = 0x40000000u;
        SCE->REG_C4H = 0x02e08886u;
        SCE->REG_04H = 0x0000c200u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = ARG2[0];
        SCE->REG_100H = ARG2[1];
        SCE->REG_100H = ARG2[2];
        SCE->REG_100H = ARG2[3];
        for (iLoop = 0; iLoop < (INST_DATA_SIZE-8) ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = ARG2[4+iLoop + 0];
            SCE->REG_100H = ARG2[4+iLoop + 1];
            SCE->REG_100H = ARG2[4+iLoop + 2];
            SCE->REG_100H = ARG2[4+iLoop + 3];
            /* WAIT_LOOP */
            while (1u != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            ARG3[1+iLoop + 0] = SCE->REG_100H;
            ARG3[1+iLoop + 1] = SCE->REG_100H;
            ARG3[1+iLoop + 2] = SCE->REG_100H;
            ARG3[1+iLoop + 3] = SCE->REG_100H;
        }
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        ARG3[1+iLoop + 0] = SCE->REG_100H;
        ARG3[1+iLoop + 1] = SCE->REG_100H;
        ARG3[1+iLoop + 2] = SCE->REG_100H;
        ARG3[1+iLoop + 3] = SCE->REG_100H;
        iLoop = iLoop + 4;
        oLoop = iLoop;
        HW_SCE_p_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        HW_SCE_p_func101(0x0052d385u, 0xd76d9a95u, 0x7739e2c2u, 0x966b5ef3u);
    }
    HW_SCE_p_func100(0xd3371c6du, 0xd24af252u, 0x239fe0dcu, 0x815b0e6cu);
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
    ARG3[1+oLoop + 0] = SCE->REG_100H;
    ARG3[1+oLoop + 1] = SCE->REG_100H;
    ARG3[1+oLoop + 2] = SCE->REG_100H;
    ARG3[1+oLoop + 3] = SCE->REG_100H;
    SCE->REG_104H = 0x00000361u;
    SCE->REG_A4H = 0x000049a5u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = ARG2[iLoop + 0];
    SCE->REG_100H = ARG2[iLoop + 1];
    SCE->REG_100H = ARG2[iLoop + 2];
    SCE->REG_100H = ARG2[iLoop + 3];
    SCE->REG_A4H = 0x00900c45u;
    SCE->REG_00H = 0x00001113u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x00007c1cu;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func057_r1.prc
***********************************************************************************************************************/
