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

void HW_SCE_p_func311(void)
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
    HW_SCE_p_func100(0xfd4b176bu, 0xd5a81478u, 0x6420f33du, 0xf5728f32u);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000002cu;
    SCE->REG_ECH = 0x00003c1eu;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x800080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x04000591u;
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
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000008u;
    SCE->REG_24H = 0x800011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000008u;
    SCE->REG_24H = 0x82001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa9ea96d7u, 0x43b13488u, 0x024e5431u, 0x4c64617bu);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(680);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(748);
    SCE->REG_24H = 0x000001c0u;
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
    SCE->REG_24H = 0x00000581u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00210000u;
    oLoop1 = 1;
    while(oLoop1 == 1)
    {
        HW_SCE_p_func100(0xd6e08aa7u, 0xec23e33du, 0x69c55027u, 0xb230fa25u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x6a97a04bu, 0x686aafbau, 0x37cc5886u, 0xf353c266u);
            oLoop1 = 0;
        }
        else
        {
            SCE->REG_24H = 0x000049c1u;
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
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func101(0x7f0eb3ebu, 0x8636ae7eu, 0xa78fc1fau, 0x8247ea08u);
        }
    }
    HW_SCE_p_func100(0xb4873111u, 0xecb38ea8u, 0x15a4ff05u, 0x06e2ba67u);
    SCE->REG_24H = 0x000049c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
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
    SCE->REG_24H = 0x02001181u;
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
    SCE->REG_100H = change_endian_long(0x016bcaa1u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x089ef4feu, 0x15bbe85fu, 0x80a2f025u, 0x29ff60e2u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(136);
    HW_SCE_p_func100(0x99313b51u, 0x88d8f2e1u, 0xdb56f33bu, 0xb6d38a7fu);
    HW_SCE_p_func314(136+64);
    SCE->REG_24H = 0x000049c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func100(0xcfda5444u, 0x2be84e0fu, 0xe0e2bd7bu, 0xa7c355d9u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c85beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa765abb1u, 0x26cce39du, 0x4b9fdea1u, 0xf6435bdbu);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(204);
    HW_SCE_p_func100(0x8d279c22u, 0xfc68a162u, 0x2fbd3f61u, 0x61c9e67fu);
    HW_SCE_p_func314(204+64);
    SCE->REG_24H = 0x000049c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000a52u;
    for (iLoop = 0; iLoop < 256; iLoop = iLoop + 1)
    {
        HW_SCE_p_func100(0x9bdc8e76u, 0xa1c2a576u, 0xf7908ae4u, 0xa3ee9d7fu);
        SCE->REG_24H = 0x040049c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000149u;
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
        SCE->REG_24H = 0x0400d0d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02000149u;
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
        SCE->REG_00H = 0x00013203u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func312(680);
        SCE->REG_ECH = 0x00002e40u;
        HW_SCE_p_func101(0x7d34eb40u, 0x5747f818u, 0x1be65614u, 0xd6ed34b3u);
    }
    HW_SCE_p_func100(0x142ecffcu, 0x326510a6u, 0x8cbe023bu, 0x026a5df9u);
    SCE->REG_ECH = 0x38008a40u;
    SCE->REG_ECH = 0x00000100u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    SCE->REG_24H = 0x040049c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x040019a1u;
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
    SCE->REG_24H = 0x0400d0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x020019a1u;
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
    HW_SCE_p_func100(0xb896da45u, 0x16e2080fu, 0x293b4f68u, 0x9dc078e9u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(680);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x718e4ecbu, 0x6d103300u, 0xcb1eb1bbu, 0x52ffc030u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(408);
    HW_SCE_p_func100(0xf0047e74u, 0xc38cc552u, 0x8a3454a0u, 0x0dc9fc09u);
    HW_SCE_p_func314(408+64);
    HW_SCE_p_func100(0xb89c82d1u, 0xca37b6d4u, 0xfebe0198u, 0x2992116au);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3du);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8c0b1577u, 0xd80af8b9u, 0x8a28fa6au, 0xb8691f5au);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(544);
    HW_SCE_p_func100(0x6a8f8a7bu, 0xea162157u, 0xf8e0b9d6u, 0xb3d9155bu);
    HW_SCE_p_func314(544+64);
    SCE->REG_24H = 0x000049c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func100(0x0cd9debeu, 0x90441b42u, 0x6c48e06du, 0xd5ce096eu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x95056b4fu, 0xa2022506u, 0xd5895c90u, 0xc9016455u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(476);
    HW_SCE_p_func100(0x8de7ac54u, 0x2086ac6eu, 0xda5ccc3du, 0x720b13b1u);
    HW_SCE_p_func314(476+64);
    HW_SCE_p_func100(0xd9c89923u, 0xda6185eeu, 0x520354eau, 0x62d3ec2bu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8c5f3115u, 0x6e3076f9u, 0xc072f381u, 0x3dceb2c9u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(612);
    HW_SCE_p_func100(0x0221233fu, 0x3eb2c7f3u, 0x2f53721bu, 0x87b0f538u);
    HW_SCE_p_func314(612+64);
    SCE->REG_ECH = 0x00000a52u;
    for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0x00000085u;
        HW_SCE_p_func101(0x6d1dde65u, 0x27e804aau, 0x0353a48au, 0xc63e1af4u);
        HW_SCE_p_func309();
        HW_SCE_p_func100(0x52609d4fu, 0x2847540du, 0xe7fd5f89u, 0xf730b53du);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01a67f45u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xe6b75748u, 0xf45d1592u, 0xee7bfe91u, 0x326aca9du);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func313(476);
        HW_SCE_p_func100(0xe9fe5121u, 0xce726d25u, 0xa83a96a3u, 0xb8b584aau);
        HW_SCE_p_func314(476+64);
        HW_SCE_p_func100(0xb3bc9911u, 0xf6c18db0u, 0xfc732293u, 0x3cd6f686u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019fce91u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x6dd6c2adu, 0x7c99c2a6u, 0x3a7d202du, 0x33864215u);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func313(612);
        HW_SCE_p_func100(0x00e68939u, 0x22376fe5u, 0x1dc88c20u, 0x4f16dbfeu);
        HW_SCE_p_func314(612+64);
        HW_SCE_p_func100(0x225f07a7u, 0xe5c06b6bu, 0xd5ad4e40u, 0x77a94de9u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x011f5dcdu);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x161d0285u, 0x582fea60u, 0x8ddb0abfu, 0xf3e3813fu);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func313(408);
        HW_SCE_p_func100(0xba986d4au, 0x8c0c05c3u, 0x9106460cu, 0x4fcb22b1u);
        HW_SCE_p_func314(408+64);
        HW_SCE_p_func100(0xba3a26c5u, 0xab973a6du, 0x113d70d0u, 0x17ceceabu);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01e59c3du);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xed966499u, 0xffbb31adu, 0x0babdc9eu, 0x028e43eau);
        SCE->REG_00H = 0x00012303u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func313(544);
        HW_SCE_p_func100(0x70e80bbeu, 0x80e52ebcu, 0xc889fbaeu, 0x908cde5du);
        HW_SCE_p_func314(544+64);
        SCE->REG_ECH = 0x00002e40u;
        HW_SCE_p_func101(0xe79021aau, 0x8e1a3178u, 0x17485e2au, 0x7739cc4au);
    }
    SCE->REG_ECH = 0x38008a40u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    HW_SCE_p_func100(0xa7713f01u, 0xff3d0159u, 0x902c8403u, 0xa6e08877u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xd79142abu, 0xdda79cd3u, 0xa39e379bu, 0x30387819u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func313(476);
    HW_SCE_p_func100(0x840d4a08u, 0x2d844345u, 0xcafbbf9fu, 0x5f275859u);
    HW_SCE_p_func314(476+64);
    HW_SCE_p_func100(0xebcced92u, 0x52a220a6u, 0x4b7a4cfbu, 0xe36bc013u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf2e9a370u, 0x660aefceu, 0x405fff51u, 0xb7af9bb1u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(408);
    HW_SCE_p_func100(0x17c8247cu, 0xa0ddb080u, 0x9e68312cu, 0xef695d8eu);
    HW_SCE_p_func314(408+64);
    HW_SCE_p_func100(0x8de20e43u, 0x8198b797u, 0x50909c69u, 0xe206fb6eu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0132d44bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8bd2bbe9u, 0x0be9aca0u, 0x6bf6b397u, 0x2b511dbfu);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(68);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01432c7au);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8921c32eu, 0x0b09dafau, 0x0a0bda14u, 0x9944d54cu);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(0);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2541ef28u, 0x061e859cu, 0xe88ecdd7u, 0x0f6035d5u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func313(612);
    HW_SCE_p_func100(0x4d51142bu, 0x42fff715u, 0x472627e9u, 0x603bdc70u);
    HW_SCE_p_func314(612+64);
    HW_SCE_p_func100(0x0efd708cu, 0xcc94585bu, 0xc223494au, 0xc6eb2968u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3du);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa3fc9c35u, 0x200d7e68u, 0x469464dau, 0x5b9149ecu);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(544);
    HW_SCE_p_func100(0xcbb87f2cu, 0xcdf462d9u, 0x6ff399b9u, 0x9b315f2du);
    HW_SCE_p_func314(544+64);
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000086u;
    HW_SCE_p_func101(0x3cbf7cedu, 0x9f0ca8c1u, 0x9fc1b0a7u, 0x1fb8e5cbu);
    HW_SCE_p_func309();
    HW_SCE_p_func100(0xd887c518u, 0x5a403aa4u, 0xc6176be4u, 0x5ce2816eu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0132d44bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x33ef899cu, 0x80ff43e7u, 0x24d6eaa4u, 0x1fcd4bb9u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func313(68);
    HW_SCE_p_func100(0x4eb32dd0u, 0x894b3a68u, 0x790aeb44u, 0x83d869b6u);
    HW_SCE_p_func314(68+64);
    HW_SCE_p_func100(0x6441f351u, 0x8a23ac4eu, 0xaf9adeadu, 0xeae53c32u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01432c7au);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbdf03440u, 0x37792dbcu, 0x58df6b26u, 0x61fffe27u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(0);
    HW_SCE_p_func100(0x10098830u, 0x68ef79e5u, 0x8d4399a9u, 0x320f688fu);
    HW_SCE_p_func314(0+64);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000002cu;
    SCE->REG_ECH = 0x0000381eu;
    SCE->REG_ECH = 0x00007c00u;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func311.prc
***********************************************************************************************************************/
