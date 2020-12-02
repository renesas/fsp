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

void HW_SCE_p_func316(void)
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_ECH = 0x00003fbeu;
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_ECH = 0x0000d779u;
    SCE->REG_28H = 0x00870001u;
    SCE->REG_E0H = 0x80010300u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x000000acu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000031fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x0000e0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_ECH = 0x3800db1fu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    HW_SCE_p_func100(0x8dd5b077u, 0xd50c776fu, 0x9d162b11u, 0xab952327u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00a70001u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_24H = 0x00000682u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00a70001u;
        SCE->REG_24H = 0x00001991u;
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
        SCE->REG_ECH = 0x0000d379u;
        HW_SCE_p_func101(0x1eb5c006u, 0x14f8b611u, 0x3c79c58bu, 0x2b91f0c0u);
    }
    SCE->REG_ECH = 0x0000b7e0u;
    SCE->REG_ECH = 0x0000001cu;
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f0u;
    HW_SCE_p_func101(0x2d145c92u, 0x70901d38u, 0x611110efu, 0x988983bfu);
    HW_SCE_p_func317();
    SCE->REG_ECH = 0x00003759u;
    SCE->REG_24H = 0x000050d0u;
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
    SCE->REG_ECH = 0x0000b7e0u;
    SCE->REG_ECH = 0x0000001du;
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f1u;
    HW_SCE_p_func101(0x82531a33u, 0xa8d87c8fu, 0x6ac862c0u, 0x734e49c8u);
    HW_SCE_p_func317();
    SCE->REG_24H = 0x000050d0u;
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
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x0000b0d0u;
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
    SCE->REG_24H = 0x000060c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000c00u;
    SCE->REG_24H = 0x8000ecd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00007cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000bcd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e4d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a00001u;
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
    SCE->REG_28H = 0x00a70001u;
    for(oLoop2 = 0; oLoop2 < 32; oLoop2 = oLoop2 + 1)
    {
        SCE->REG_24H = 0x00000189u;
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
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000030u;
    SCE->REG_24H = 0x80007cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000002c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x00000dc0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a00001u;
    SCE->REG_24H = 0x00001151u;
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
    SCE->REG_24H = 0x00001991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00210000u;
    HW_SCE_p_func100(0x511e8e8eu, 0xd9e12ddbu, 0xf22bed32u, 0x73de2ff2u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x00001981u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x1e68f2e3u, 0xb5e7bbfcu, 0x18236343u, 0xecce8c56u);
    }
    else
    {
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_24H = 0x000006c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00a00001u;
        SCE->REG_24H = 0x040091c1u;
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
        HW_SCE_p_func101(0x91b9177bu, 0xc40e686du, 0xce3d3442u, 0x8db507f8u);
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x000006c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a00001u;
    SCE->REG_24H = 0x00001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00210000u;
    HW_SCE_p_func100(0xffb51ee1u, 0x2551d008u, 0x419923a9u, 0xa6a91ad0u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x00001981u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x8bafbae7u, 0xcc319b8eu, 0x09db8e30u, 0x6719a39au);
    }
    else
    {
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_24H = 0x000006c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00a00001u;
        SCE->REG_24H = 0x040091c1u;
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
        HW_SCE_p_func101(0x4ee65c47u, 0x1e802413u, 0xe499d1a8u, 0xdb8fab6au);
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x3800db20u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x1d570422u, 0xba2e8875u, 0x4417d7b7u, 0x75e2ba4au);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x000009c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_24H = 0x000002c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00a00001u;
        SCE->REG_24H = 0x00001181u;
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
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_24H = 0x000015c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_24H = 0x000002c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000020u;
        SCE->REG_24H = 0x80001dc0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00a00001u;
        SCE->REG_24H = 0x00001981u;
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
        HW_SCE_p_func101(0x5930a123u, 0xe735b3d5u, 0xc4d172b9u, 0x05e9d5b3u);
    }
    else
    {
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_24H = 0x0000d4d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001u;
        SCE->REG_34H = 0x00000020u;
        SCE->REG_24H = 0x8000dcd0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000e0d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0xaa453373u, 0xe70c1f7bu, 0x2794ae86u, 0x1e04ffb8u);
    }
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x00004cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x000060d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a00001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000bffu;
    HW_SCE_p_func100(0x1424e022u, 0x37343771u, 0xa0416005u, 0x010b4e36u);
    SCE->REG_E0H = 0x81010340u;
    SCE->REG_04H = 0x00000607u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    SCE->REG_ECH = 0x3800db7cu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xd4918aa4u, 0x20669ad3u, 0x6d1f6b3fu, 0x6459ad47u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            SCE->REG_24H = 0x00001991u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00002fe0u;
            HW_SCE_p_func101(0xb7698563u, 0x1d329d6bu, 0x968a2dceu, 0xd32a5eadu);
        }
        HW_SCE_p_func101(0x8cfc7f48u, 0x1596a76du, 0xe304f64au, 0xe359ab67u);
    }
    else
    {
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            SCE->REG_24H = 0x00001981u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00002fe0u;
            HW_SCE_p_func101(0x4e152c24u, 0xe90797beu, 0x172490f0u, 0x260bc8bcu);
        }
        HW_SCE_p_func101(0xb6fea3f5u, 0x85e41681u, 0xb3f14e96u, 0x5022aeefu);
    }
    SCE->REG_ECH = 0x38000b5fu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x3800db79u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x40f924e5u, 0xc4f5438du, 0xb74cc091u, 0xf662ab19u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x000001c0u;
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
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00a00001u;
        SCE->REG_24H = 0x000009c0u;
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
        SCE->REG_24H = 0x000040c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x0270d572u, 0x600e206bu, 0x72b67275u, 0xfd7bff07u);
    }
    else
    {
        HW_SCE_p_func101(0x145e3f7du, 0x4bd25dc4u, 0x94ed56edu, 0x32ddd531u);
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x0000000cu;
    SCE->REG_ECH = 0x00003bbeu;
    SCE->REG_ECH = 0x00007c1du;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func316.prc
***********************************************************************************************************************/
