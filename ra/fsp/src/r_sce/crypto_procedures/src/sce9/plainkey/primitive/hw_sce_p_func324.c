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

void HW_SCE_p_func324(void)
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
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00003fbeu;
    HW_SCE_p_func100(0xba800165u, 0x9d0773f6u, 0xc404520bu, 0x64890201u);
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x000005c0u;
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
    SCE->REG_24H = 0x000001c0u;
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
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xd5fc2c48u, 0x3ee36e03u, 0x5d0a4911u, 0x3a0bf64du);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func320(680);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8b104378u, 0x5c4821e6u, 0xd5ad0910u, 0x350a2659u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000015u;
    HW_SCE_p_func320(716);
    SCE->REG_24H = 0x0000a0c1u;
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
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00bf0001u;
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
    SCE->REG_1CH = 0x00210000u;
    oLoop1 = 1;
    while(oLoop1 == 1)
    {
        HW_SCE_p_func100(0xf53e35c6u, 0xd82158c6u, 0xb88968fcu, 0xc7b36f20u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x905bfec7u, 0x34f45708u, 0x8a2c63ffu, 0x0f52cc31u);
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
            HW_SCE_p_func101(0x6fd622f4u, 0xc5c30bdbu, 0x97754975u, 0xabab04e2u);
        }
    }
    HW_SCE_p_func100(0x21bbb393u, 0xcd9f14a3u, 0x26a0865fu, 0x7ab63a5fu);
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
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef2f1cu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfc6ff514u, 0xa79a0df4u, 0x7e3fac51u, 0x4283d461u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(136);
    HW_SCE_p_func100(0x94f25a99u, 0xdcf9f94bu, 0xcc235501u, 0x569b42ddu);
    HW_SCE_p_func314(136+32);
    HW_SCE_p_func100(0xc3c50340u, 0x1fed1a99u, 0xc269950cu, 0xe7766b8eu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012e06e6u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8cebb57cu, 0x04b0382fu, 0x60452136u, 0xde3445a7u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(172);
    HW_SCE_p_func100(0xf53e25d8u, 0x61d4a5ceu, 0xd3c4952au, 0x9acca047u);
    HW_SCE_p_func314(172+32);
    HW_SCE_p_func100(0xb8a00ca9u, 0x28cfa0d8u, 0x81dd7ba0u, 0xa28e4d9fu);
    SCE->REG_28H = 0x00bf0001u;
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
    SCE->REG_100H = change_endian_long(0x0100abe1u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6f9aab8fu, 0xabe2fdc1u, 0xd809f527u, 0x5f0cfc44u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(208);
    HW_SCE_p_func100(0x85986bc9u, 0xdfec6f9fu, 0xd0187c6du, 0x35b96576u);
    HW_SCE_p_func314(208+32);
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000049c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000a52u;
    for (iLoop = 0; iLoop < 128; iLoop = iLoop + 1)
    {
        HW_SCE_p_func100(0x676328e0u, 0x613dcc15u, 0xb5174525u, 0x35e75a6fu);
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
        HW_SCE_p_func100(0x23195e77u, 0x97f9f9e3u, 0x3a294c80u, 0x21a31b5fu);
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func320(680);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010273a4u);
        HW_SCE_p_func080();
        SCE->REG_00H = 0x00003283u;
        SCE->REG_2CH = 0x00000015u;
        HW_SCE_p_func320(716);
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_ECH = 0x00002e40u;
        HW_SCE_p_func101(0xe6f2fb13u, 0x44ac6782u, 0xacacfa2cu, 0xc6ce06bau);
    }
    SCE->REG_ECH = 0x38008a40u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    HW_SCE_p_func100(0xdff19989u, 0xed86b6e4u, 0x810692d1u, 0x4054ba1fu);
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
    HW_SCE_p_func100(0xb252e8f6u, 0xa305ef14u, 0xae64b69au, 0x585821f5u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func320(680);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe3ac09b8u, 0xed2ade8eu, 0x09e0d6a0u, 0x53c92617u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000015u;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4a733c3du, 0x2b978923u, 0xc70ac96au, 0xf892a403u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x6a895ce5u, 0x6c42347fu, 0x214cfe83u, 0x59e7049eu);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0xdea06f25u, 0x53d8df33u, 0x9c88cf0eu, 0x67a0090au);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf3bc416u, 0x136f6b3eu, 0xacf5f90fu, 0x3425f707u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x1c85df96u, 0x3d70a07du, 0x430218bcu, 0xb738452du);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0x4894e0eau, 0x1ed6fd66u, 0x44c98fa9u, 0x93476849u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x27653520u, 0xaf747027u, 0xdc554257u, 0xf7ab9d4bu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(544);
    HW_SCE_p_func100(0x799b94d4u, 0xc20a7cd7u, 0x9cca7baau, 0x7cb589a4u);
    HW_SCE_p_func314(544+32);
    HW_SCE_p_func100(0x88fb9181u, 0xb55c73deu, 0x7d7588f0u, 0xf5f0778cu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf3a6d287u, 0xc0bae19au, 0x4a678488u, 0x782770a3u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(580);
    HW_SCE_p_func100(0x713444a7u, 0xc18c9532u, 0x50c8e298u, 0x48490351u);
    HW_SCE_p_func314(580+32);
    HW_SCE_p_func100(0xc516255bu, 0xc4f1442cu, 0xe9885d55u, 0xb986eeb2u);
    SCE->REG_28H = 0x00bf0001u;
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
    SCE->REG_100H = change_endian_long(0x010964eau);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x54c6a527u, 0x13c8e927u, 0xb44ce6aau, 0xeb9e9d3fu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0x265120a7u, 0x73fc5c2eu, 0xef24e3f8u, 0x4fbcfaadu);
    HW_SCE_p_func314(480+32);
    HW_SCE_p_func100(0x61f0fe5eu, 0x0f4cbddfu, 0x1ad3a9e8u, 0x1a0d7668u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x7be00fceu, 0x9aeb3edeu, 0x25026ce9u, 0xc2d0db59u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(616);
    HW_SCE_p_func100(0x73a48fa9u, 0x38d334c0u, 0xadf63b4du, 0xf330a5ccu);
    HW_SCE_p_func314(616+32);
    SCE->REG_ECH = 0x00000a52u;
    for (iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x0000b7a0u;
        SCE->REG_ECH = 0x000000f0u;
        HW_SCE_p_func101(0x20fa9c73u, 0xbbf1986du, 0x9bfb0b9du, 0x272b4a9eu);
        HW_SCE_p_func318();
        HW_SCE_p_func100(0x91e54cabu, 0xdaa2840bu, 0xe523dc34u, 0x667f6b46u);
        SCE->REG_28H = 0x009f0001u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x011af8f9u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xb669ddffu, 0xc3ef8260u, 0x5350ad91u, 0x9fa7b544u);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func319(408);
        HW_SCE_p_func100(0x147c2639u, 0x9cc02970u, 0x583dd0dbu, 0x528abff7u);
        HW_SCE_p_func314(408+32);
        HW_SCE_p_func100(0x1714ce33u, 0x4aad3236u, 0x7b544d55u, 0xd9609333u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0130aeffu);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x1cd470e5u, 0x633c9ff4u, 0x1cdcb115u, 0x26eda65cu);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000023u;
        HW_SCE_p_func319(444);
        HW_SCE_p_func100(0xb9364cc7u, 0xbefc7673u, 0x0e7a2b28u, 0x2ad0bb86u);
        HW_SCE_p_func314(444+32);
        HW_SCE_p_func100(0x51f70bf0u, 0x01fd1d85u, 0x88cd7d7au, 0xc11c13c1u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010964eau);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x859aa5c9u, 0x89c173aeu, 0x7aab7a3eu, 0x4bd05495u);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func319(480);
        HW_SCE_p_func100(0xa64744e4u, 0xa6a5a5c4u, 0x6f2d5dc6u, 0x2fe1048eu);
        HW_SCE_p_func314(480+32);
        HW_SCE_p_func100(0xfa4d90b8u, 0x0d966024u, 0x19970766u, 0x2c40f92eu);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01574730u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x7f6a3d31u, 0x15656e45u, 0x8350c92bu, 0xa29a076du);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000022u;
        HW_SCE_p_func319(544);
        HW_SCE_p_func100(0xe8a70fe7u, 0x4d8a9e70u, 0x3f48c23au, 0x89eeb55eu);
        HW_SCE_p_func314(544+32);
        HW_SCE_p_func100(0x5c04f776u, 0x21f0f81fu, 0x4e3a8a5bu, 0x76098a00u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01f11123u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x472aaf2au, 0xf9d8f81cu, 0x07508940u, 0xd7a49d5au);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000023u;
        HW_SCE_p_func319(580);
        HW_SCE_p_func100(0x05d64b3fu, 0x793b0085u, 0xa705f245u, 0xe95259deu);
        HW_SCE_p_func314(580+32);
        HW_SCE_p_func100(0xfa3b4138u, 0xbe30de6cu, 0xfc3bd1eau, 0x2e93d150u);
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01ac62c9u);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xa6ec6b8cu, 0xaa9fd90bu, 0x46b98ebeu, 0xfbe37dfcu);
        SCE->REG_00H = 0x00002383u;
        SCE->REG_2CH = 0x00000020u;
        HW_SCE_p_func319(616);
        HW_SCE_p_func100(0x0f67fcf6u, 0xd661c9b8u, 0x78b71659u, 0xdc1671e7u);
        HW_SCE_p_func314(616+32);
        SCE->REG_ECH = 0x00002e40u;
        HW_SCE_p_func101(0x61371d76u, 0x8955c0e3u, 0xf57d2ea6u, 0x6b052d94u);
    }
    SCE->REG_ECH = 0x38008a40u;
    SCE->REG_ECH = 0x00000003u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f1u;
    HW_SCE_p_func101(0x8bba8cdbu, 0xa7e18e91u, 0xf71d87c8u, 0x797aa69cu);
    HW_SCE_p_func318();
    HW_SCE_p_func100(0x322547acu, 0x9b5539eeu, 0x631909e9u, 0xa317cbbbu);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1759ee18u, 0x3b01deecu, 0x6a8590f4u, 0xf6c5f969u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x96c47023u, 0x7df6d2ccu, 0xf3632006u, 0x6fe7f4f8u);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0x91a24210u, 0xcbb101b4u, 0xb5ba4705u, 0xfbf14b32u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2c310da3u, 0x5ea30255u, 0xa29d782eu, 0x0bc1f93eu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x8b87eef7u, 0x213e09a1u, 0xa69cfedbu, 0xfb9276f3u);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0xd41003bau, 0x105fbe5au, 0x561c8390u, 0x4b945c86u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eau);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x48db3531u, 0x94b996bdu, 0x060dbf20u, 0x9520a664u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0xb51fc317u, 0xc794cd92u, 0xb477efbcu, 0x81dce284u);
    HW_SCE_p_func314(480+32);
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f2u;
    HW_SCE_p_func101(0xbf232622u, 0x10d13a51u, 0x848c8464u, 0x5f80635du);
    HW_SCE_p_func318();
    HW_SCE_p_func100(0x30a00026u, 0x69802337u, 0x7cd74e4fu, 0x52041efcu);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d34587u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x553d552eu, 0xb04761ecu, 0x3077aef8u, 0x831743f4u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(272);
    HW_SCE_p_func100(0x7432c608u, 0xc9fed9c7u, 0xec726f19u, 0x8d5f8875u);
    HW_SCE_p_func314(272+32);
    HW_SCE_p_func100(0xaace0e99u, 0x42f2e878u, 0xdd957896u, 0xcd0de241u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01315552u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5c31900bu, 0x2680183du, 0xe043b5a4u, 0x8db6cf2du);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(308);
    HW_SCE_p_func100(0xcdd8331eu, 0xa782fd53u, 0xc031e37eu, 0xf9541b33u);
    HW_SCE_p_func314(308+32);
    HW_SCE_p_func100(0x36ab5860u, 0x7d1990c3u, 0xd106d439u, 0xd15c9b71u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011a27dfu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6fc441bdu, 0x7bce0d3bu, 0xe350cbc9u, 0x0d856aceu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func319(344);
    HW_SCE_p_func100(0xe4f910e8u, 0x57082666u, 0x3975f343u, 0xeb5a48a4u);
    HW_SCE_p_func314(344+32);
    HW_SCE_p_func100(0x8de19a0bu, 0x8f9aed6fu, 0x47fdf7ecu, 0x62fb4c80u);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x26831bc6u, 0xcde42f4fu, 0x8b4d5307u, 0xca3cecfeu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x68d5d8f0u, 0x2d218dd1u, 0xd6eea468u, 0xb35336b8u);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0x021c7250u, 0x492cdf1fu, 0x3a45037fu, 0xefeca1b5u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0cb3fc26u, 0xcb04bc14u, 0xb6de0377u, 0x53ba5f3fu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x2e642543u, 0x4902544au, 0x51f5ebe8u, 0x72794910u);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0x8f9d782eu, 0x81c16d66u, 0x5e85807eu, 0x6ef1b6d8u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eau);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc718fd71u, 0x78b1a7f1u, 0x20b0a1fcu, 0x08efeaa0u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0x1703905fu, 0x2588568cu, 0x62ecbe40u, 0x232f9133u);
    HW_SCE_p_func314(480+32);
    HW_SCE_p_func100(0x3a1733d4u, 0x86275a46u, 0x6eccc0a1u, 0x33a7dc95u);
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
    HW_SCE_p_func100(0x8e52d68bu, 0x1f5c3894u, 0x691f3877u, 0x2243d7a3u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000012u;
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
    HW_SCE_p_func100(0x29bf281fu, 0x90730ae8u, 0x5c16ffe4u, 0x9746b752u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000013u;
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
    HW_SCE_p_func100(0xc6d651f1u, 0xea4e04fbu, 0x1e97b80eu, 0x728f545cu);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(72);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4f8d632au, 0xfd956a83u, 0x8a13de73u, 0x6dd74cadu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(544);
    HW_SCE_p_func100(0xc1fe21f7u, 0x1494de69u, 0xb4a7584bu, 0x901cd492u);
    HW_SCE_p_func314(544+32);
    HW_SCE_p_func100(0x0e1dc5d7u, 0x2032e656u, 0x84c0fcffu, 0x1b85a4d7u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x085429ddu, 0x35c43703u, 0x5059446fu, 0x997691b1u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(580);
    HW_SCE_p_func100(0x6d916213u, 0xb2da4cceu, 0x367fbab5u, 0x2acea943u);
    HW_SCE_p_func314(580+32);
    HW_SCE_p_func100(0x18057ff5u, 0x754a8c51u, 0x086a4be3u, 0x90067525u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x325a9a89u, 0x535dc5d9u, 0x1f05a791u, 0xcd2f9884u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func319(616);
    HW_SCE_p_func100(0xc75b4b8fu, 0x620e68b0u, 0xbbebe121u, 0xe12fba81u);
    HW_SCE_p_func314(616+32);
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f3u;
    HW_SCE_p_func101(0x06aa632cu, 0x2c294586u, 0x524b9262u, 0x937064feu);
    HW_SCE_p_func318();
    HW_SCE_p_func100(0x7ea795a3u, 0x8915f2cbu, 0xa7c41020u, 0x0f89207eu);
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
    HW_SCE_p_func100(0x9a6b4727u, 0x19829e58u, 0xb07a6fc7u, 0x1ec71baeu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(0);
    HW_SCE_p_func100(0xb85e4c02u, 0x1065c4d4u, 0x565140bcu, 0x9e233683u);
    HW_SCE_p_func314(0+32);
    HW_SCE_p_func100(0x0f6b1778u, 0xbd59c987u, 0x90211bb5u, 0x109bfbf8u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019969f4u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb356879fu, 0xa9e41716u, 0x28645099u, 0x0bf86938u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(36);
    HW_SCE_p_func100(0xb6a059a7u, 0xb27e1a91u, 0xe6575256u, 0x7d8b8dbcu);
    HW_SCE_p_func314(36+32);
    HW_SCE_p_func100(0xe0209cc9u, 0xc3e5b064u, 0xe233e02bu, 0xb82949e6u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019de420u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcf7deda8u, 0xb4cb207eu, 0x706bb36cu, 0xd048408eu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func319(72);
    HW_SCE_p_func100(0x39eb6316u, 0x27f38705u, 0x8667e6f3u, 0xf04bff62u);
    HW_SCE_p_func314(72+32);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x00003bbeu;
    SCE->REG_ECH = 0x00007c1du;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func324.prc
***********************************************************************************************************************/
