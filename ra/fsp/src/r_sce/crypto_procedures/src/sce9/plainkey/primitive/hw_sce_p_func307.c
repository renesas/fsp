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

void HW_SCE_p_func307(void)
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
    SCE->REG_ECH = 0x00000090u;
    SCE->REG_ECH = 0x00003c1eu;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000080u;
    HW_SCE_p_func101(0x46765f77u, 0x5749f546u, 0xffae0ff7u, 0x8b2d018eu);
    HW_SCE_p_func311();
    SCE->REG_ECH = 0x00000a73u;
    SCE->REG_ECH = 0x00000a31u;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        SCE->REG_ECH = 0x00002e20u;
        SCE->REG_ECH = 0x38002673u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func100(0x0efed670u, 0x4c5eb194u, 0xde5be454u, 0x29041d0fu);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x733f12abu, 0xecc5543eu, 0xc537a171u, 0x48357424u);
        }
        else
        {
            HW_SCE_p_func100(0x2d664c4du, 0xd9d9fd9du, 0xe34eae6au, 0x62d43b41u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xe804d856u, 0xe4909999u, 0xa52e04fdu, 0xfe75ac58u);
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000010u;
            HW_SCE_p_func312(204);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x517c7161u, 0x77c03114u, 0x61d87db2u, 0x4f1c9985u);
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000012u;
            HW_SCE_p_func312(136);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01a67f45u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x989e30fdu, 0xfb087ef5u, 0xec2e871bu, 0x64eb0658u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func313(476);
            HW_SCE_p_func100(0xbf56fa09u, 0x821175ccu, 0x1891f091u, 0x8f3b024au);
            HW_SCE_p_func314(476+64);
            HW_SCE_p_func100(0xd2825fcdu, 0xc659f6e8u, 0x10029c48u, 0x47827fb5u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019fce91u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xa3c241c7u, 0x45c0ad6bu, 0xe6a7bb38u, 0x84b04d8bu);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func313(612);
            HW_SCE_p_func100(0x3f406e95u, 0x13025ff8u, 0xf8b51b24u, 0x4c05351cu);
            HW_SCE_p_func314(612+64);
            HW_SCE_p_func100(0x0830ae7au, 0x6d43b3e9u, 0xd4ccc5eau, 0xe6dcdce5u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011f5dcdu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x40901979u, 0xc4600862u, 0x60d83598u, 0xf0d8941fu);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func313(408);
            HW_SCE_p_func100(0x2c04ab0bu, 0x0e747ad8u, 0x7eb80229u, 0xf876f457u);
            HW_SCE_p_func314(408+64);
            HW_SCE_p_func100(0xa016bd2cu, 0x3aa9aa45u, 0x7542dc38u, 0xdcc879c6u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01e59c3du);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x20c49ee6u, 0x329d4116u, 0xa1fa89feu, 0x0340299cu);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func313(544);
            HW_SCE_p_func100(0x6e9c8d98u, 0x6120d3adu, 0x665f0919u, 0x27efb3bau);
            HW_SCE_p_func314(544+64);
            SCE->REG_ECH = 0x0000b400u;
            SCE->REG_ECH = 0x00000081u;
            HW_SCE_p_func101(0xca53192fu, 0x211abfddu, 0xa870386fu, 0xb8e79d3eu);
            HW_SCE_p_func309();
            HW_SCE_p_func100(0xcd35d372u, 0x54dbdbceu, 0xb0afbbdbu, 0xf796fc29u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xaee9f5b2u, 0x522163adu, 0x95ef5614u, 0x66787e86u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func313(204);
            HW_SCE_p_func100(0x2e1850f0u, 0x07ff76f0u, 0xce36e13cu, 0x6eea89e8u);
            HW_SCE_p_func314(204+64);
            HW_SCE_p_func100(0x05d76537u, 0xa64e6099u, 0x19533700u, 0x491094b8u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xe6475365u, 0x1fae56fbu, 0x565db664u, 0xa6771660u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func313(136);
            HW_SCE_p_func100(0xfe310ec6u, 0xff3bb340u, 0x3af230a3u, 0xbcedede9u);
            HW_SCE_p_func314(136+64);
            HW_SCE_p_func101(0x9fa02c96u, 0xfaf805deu, 0x6623feddu, 0xbc1389aeu);
        }
        SCE->REG_ECH = 0x3800da9fu;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func100(0x3d92f89au, 0xa4b197f4u, 0x583087f9u, 0x353f282du);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x60afc885u, 0xc0ff181bu, 0x12ea81aeu, 0x2804d93eu);
        }
        else
        {
            HW_SCE_p_func100(0xb9b491e0u, 0x1463bd81u, 0x8cdca180u, 0x461e2b79u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x909714ffu, 0xd0219bf6u, 0x9f8fbbbdu, 0xd4083fd2u);
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000010u;
            HW_SCE_p_func312(204);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1u);
            HW_SCE_p_func080();
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000012u;
            HW_SCE_p_func312(136);
            HW_SCE_p_func100(0x5592c700u, 0x5a6eaa8au, 0xd9bf08bdu, 0x69ab981du);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01a67f45u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x5925d68du, 0x7a61ecf6u, 0x5bae60ccu, 0x83f7e3a4u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func313(476);
            HW_SCE_p_func100(0xa3ca016bu, 0x8aaf93d3u, 0xbdc90e30u, 0x56d8ac7du);
            HW_SCE_p_func314(476+64);
            HW_SCE_p_func100(0xb313c752u, 0x5c602865u, 0xec2fe69cu, 0x7be094a4u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011f5dcdu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xa821b521u, 0x461c4e09u, 0x65b8de9cu, 0x3ce623a5u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func313(408);
            HW_SCE_p_func100(0x1360b584u, 0xf686799du, 0xab5b69bfu, 0x19469924u);
            HW_SCE_p_func314(408+64);
            HW_SCE_p_func100(0x7af0c270u, 0x7ed6ff84u, 0x92765f4fu, 0xc608e17fu);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0132d44bu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x6964e4b4u, 0xe864d305u, 0xc84d8bb4u, 0x07ec5ec8u);
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
            SCE->REG_00H = 0x00013203u;
            SCE->REG_2CH = 0x00000012u;
            HW_SCE_p_func312(0);
            HW_SCE_p_func100(0xd7e164c0u, 0x1ecc338bu, 0x510e64e7u, 0x6a2613a5u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019fce91u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x4e82d9a2u, 0x40be6e96u, 0x0fe40003u, 0x6ff6e827u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func313(612);
            HW_SCE_p_func100(0xa348c089u, 0x43d0ff84u, 0x778ff6b8u, 0x67521438u);
            HW_SCE_p_func314(612+64);
            HW_SCE_p_func100(0xdc825e03u, 0x32ed1ec4u, 0x42c88adfu, 0x371b0bc8u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01e59c3du);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x0e29cd80u, 0x38300037u, 0x45986240u, 0x957d7b77u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func313(544);
            HW_SCE_p_func100(0x4e55f63au, 0x2241701bu, 0x4a60cce7u, 0x29c0bbd9u);
            HW_SCE_p_func314(544+64);
            SCE->REG_ECH = 0x0000b400u;
            SCE->REG_ECH = 0x00000082u;
            HW_SCE_p_func101(0x8389d01fu, 0xe6c6ffddu, 0x142d5ccfu, 0x7a0e9c6du);
            HW_SCE_p_func309();
            HW_SCE_p_func100(0xdee3518fu, 0xb273ad82u, 0x9fe71ee7u, 0x2edf8f2cu);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xb9c1509fu, 0xbf54f012u, 0x98c8652au, 0x203d25fcu);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func313(204);
            HW_SCE_p_func100(0x8eea8326u, 0x2d4020ceu, 0x4d41424cu, 0xe4982805u);
            HW_SCE_p_func314(204+64);
            HW_SCE_p_func100(0xbf7df5f8u, 0x324650cau, 0x225fdd08u, 0x90466761u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x45705ce6u, 0xd8eacde4u, 0x3a795df3u, 0xbe5b4797u);
            SCE->REG_00H = 0x00012303u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func313(136);
            HW_SCE_p_func100(0x1fe6691eu, 0xe9108d9au, 0x57f0bf4cu, 0x6708d01cu);
            HW_SCE_p_func314(136+64);
            SCE->REG_ECH = 0x0000d260u;
            HW_SCE_p_func101(0x6358b604u, 0x6dc2d12bu, 0x6cbb7715u, 0x3eb0ec45u);
        }
        SCE->REG_ECH = 0x01816e94u;
        HW_SCE_p_func101(0xf737726cu, 0x7dc9f6f9u, 0xe1731169u, 0x6df578f1u);
    }
    SCE->REG_ECH = 0x38008a20u;
    SCE->REG_ECH = 0x00000020u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    HW_SCE_p_func100(0x07ff897au, 0x247d24c7u, 0xfbf81f2cu, 0x1baceb97u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c85beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5035ba16u, 0xf255a3adu, 0x1ed0bc13u, 0x92e894d5u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(204);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016bcaa1u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4a5f6826u, 0xfa67b379u, 0x995c12b3u, 0x2c6cab19u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(136);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9f2effcau, 0xfa8f0918u, 0x75ac2514u, 0xf921ad9fu);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func313(476);
    HW_SCE_p_func100(0x932f0373u, 0x17ca4781u, 0x75f63f1du, 0x12347107u);
    HW_SCE_p_func314(476+64);
    HW_SCE_p_func100(0x5e19c95eu, 0x1bf7f515u, 0xa49b9e82u, 0xdebab01eu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc5a99131u, 0x9797c7d3u, 0xea9c1037u, 0xb9f0451du);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(408);
    HW_SCE_p_func100(0x95a8001eu, 0x9fb1b0ecu, 0xf62ab0a9u, 0x2b362008u);
    HW_SCE_p_func314(408+64);
    HW_SCE_p_func100(0x4bcfab8fu, 0x3ffb18cfu, 0x786aa6c9u, 0x3bab7324u);
    SCE->REG_24H = 0x000001c0u;
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
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4078b7d0u, 0x46f98634u, 0x880c48a1u, 0x7cf1df0du);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func313(612);
    HW_SCE_p_func100(0x68145b96u, 0x8dfc7766u, 0xc0a86193u, 0x9d16ea7au);
    HW_SCE_p_func314(612+64);
    HW_SCE_p_func100(0xb2940826u, 0xa63e577fu, 0x926b6b1eu, 0x16a88b70u);
    SCE->REG_24H = 0x00000581u;
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
    SCE->REG_100H = change_endian_long(0x01e59c3du);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x17c2749cu, 0x8d75c162u, 0xfd7d6916u, 0x945b30a9u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(544);
    HW_SCE_p_func100(0x5cdf4f3du, 0xc1445dfau, 0x7c2cd0aau, 0x42ffc8a0u);
    HW_SCE_p_func314(544+64);
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000083u;
    HW_SCE_p_func101(0x24e91976u, 0x418be7b2u, 0x2aeeec01u, 0x65afa0b3u);
    HW_SCE_p_func309();
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000090u;
    SCE->REG_ECH = 0x0000381eu;
    SCE->REG_ECH = 0x00007c00u;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func307.prc
***********************************************************************************************************************/
