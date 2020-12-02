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

void HW_SCE_p_func325(void)
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
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00003fbeu;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f0u;
    HW_SCE_p_func101(0x19b9f8aeu, 0x00dc1eecu, 0xf9dd9c29u, 0x487dca94u);
    HW_SCE_p_func324();
    SCE->REG_ECH = 0x00000a73u;
    SCE->REG_ECH = 0x00000a31u;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        SCE->REG_ECH = 0x00002e20u;
        SCE->REG_ECH = 0x38002673u;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func100(0x5ff32453u, 0x873c3af2u, 0x1ef0a9f2u, 0xeea1abc8u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xd91c4453u, 0x71906777u, 0x65eb6ac8u, 0x68116537u);
        }
        else
        {
            HW_SCE_p_func100(0x6f5b19e9u, 0xdac83bf0u, 0x54111c06u, 0xb860b781u);
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
            HW_SCE_p_func100(0xe22eb519u, 0x6de82dcfu, 0xb8f9baceu, 0xbc0d647du);
            SCE->REG_00H = 0x00003283u;
            SCE->REG_2CH = 0x00000012u;
            HW_SCE_p_func320(136);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x1cdea842u, 0xb564ce9eu, 0xaf62b09du, 0xa657fcd4u);
            SCE->REG_00H = 0x00003283u;
            SCE->REG_2CH = 0x00000013u;
            HW_SCE_p_func320(172);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x6ae3808fu, 0x31e8aaa5u, 0x83c15ab1u, 0x0e1e2a56u);
            SCE->REG_00H = 0x00003283u;
            SCE->REG_2CH = 0x00000010u;
            HW_SCE_p_func320(208);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011af8f9u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xdbf17b2cu, 0x6294819cu, 0x1e63b419u, 0x687af4b1u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func319(408);
            HW_SCE_p_func100(0x6cafabccu, 0xab9a7899u, 0x3e4e3a72u, 0x7238056du);
            HW_SCE_p_func314(408+32);
            HW_SCE_p_func100(0x2a966046u, 0xe5910a6au, 0xb9af8bc2u, 0x93b2ee87u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0130aeffu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf0bb19d3u, 0x6d0a732fu, 0x79edce81u, 0x499d547fu);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000023u;
            HW_SCE_p_func319(444);
            HW_SCE_p_func100(0xb6c9eb32u, 0xad8b6a5au, 0x5b45535du, 0xdb899e90u);
            HW_SCE_p_func314(444+32);
            HW_SCE_p_func100(0xc8542ac7u, 0x35039915u, 0xfe02b565u, 0x41720439u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x010964eau);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x6977f72au, 0xf0c40367u, 0x67b15bacu, 0x3c1c7ed3u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func319(480);
            HW_SCE_p_func100(0x043ee0feu, 0x624f430cu, 0xb8984341u, 0x2e9b0883u);
            HW_SCE_p_func314(480+32);
            HW_SCE_p_func100(0x990f8d9cu, 0xbae662edu, 0x9243df9fu, 0x70f27c08u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01574730u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x882daaf8u, 0x19e744beu, 0x796e7434u, 0x58deac8cu);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func319(544);
            HW_SCE_p_func100(0xa65ba385u, 0xd358b3d1u, 0x514a28beu, 0xc75e4c3cu);
            HW_SCE_p_func314(544+32);
            HW_SCE_p_func100(0x8e27c19eu, 0x824b7d7eu, 0xe50f28fdu, 0x7e778871u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01f11123u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x90947f6fu, 0x28cf15d5u, 0xe7bf2d71u, 0xc95bc76cu);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000023u;
            HW_SCE_p_func319(580);
            HW_SCE_p_func100(0xd47910a8u, 0x77c0c723u, 0x9458a5c8u, 0xf065fe99u);
            HW_SCE_p_func314(580+32);
            HW_SCE_p_func100(0x462657d5u, 0xd8ee238bu, 0x244727e6u, 0x5fbb2ec0u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ac62c9u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x95cd2f1bu, 0xac924fb3u, 0x07bbac8eu, 0x5868deb3u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func319(616);
            HW_SCE_p_func100(0xb8afe95du, 0xf0a676a8u, 0x278ca2e7u, 0xd432ab29u);
            HW_SCE_p_func314(616+32);
            SCE->REG_ECH = 0x0000b7a0u;
            SCE->REG_ECH = 0x000000f0u;
            HW_SCE_p_func101(0x4b583ae7u, 0x56d78152u, 0xd8cd207fu, 0x9097cbb4u);
            HW_SCE_p_func318();
            HW_SCE_p_func100(0xa29f08dau, 0x8b21226du, 0xba1aa171u, 0x8c03bd6bu);
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
            HW_SCE_p_func100(0x3e09f796u, 0x1f5513bau, 0xf2906a3au, 0xf6a264a1u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func319(136);
            HW_SCE_p_func100(0x83f2f5c5u, 0xdb4b3aa1u, 0xacb5ab71u, 0xe7159fd6u);
            HW_SCE_p_func314(136+32);
            HW_SCE_p_func100(0xc6cc13adu, 0x22bf318cu, 0xd52ea535u, 0x0bfda6bcu);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x4434b13au, 0x76d201adu, 0x198d4932u, 0xd9a8e8c6u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000023u;
            HW_SCE_p_func319(172);
            HW_SCE_p_func100(0x2034127au, 0x60179772u, 0x9d4f2692u, 0xf359f550u);
            HW_SCE_p_func314(172+32);
            HW_SCE_p_func100(0x03be931eu, 0x9b569d30u, 0xf39d0140u, 0x2f929436u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xd22044a4u, 0x1911ee48u, 0x559c468eu, 0x6062e4e5u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func319(208);
            HW_SCE_p_func100(0xf4dc0b69u, 0xee39d2a1u, 0x3638a4f4u, 0x87ad8cf6u);
            HW_SCE_p_func314(208+32);
            HW_SCE_p_func101(0x48c6011cu, 0x2d1d0c0eu, 0x3ad508d0u, 0x1863f5c7u);
        }
        SCE->REG_ECH = 0x3800da9fu;
        SCE->REG_E0H = 0x00000080u;
        SCE->REG_1CH = 0x00A60000u;
        HW_SCE_p_func100(0x06fcfb29u, 0xb5045fefu, 0x87993562u, 0x6e1bce5du);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (0u == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xa3dd6937u, 0x1080ea7cu, 0xc0f8663bu, 0x39b34e02u);
        }
        else
        {
            HW_SCE_p_func100(0x540eaafeu, 0x60f8d266u, 0x51ba7ec8u, 0x6541c4a3u);
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
            HW_SCE_p_func100(0xd329fbd9u, 0x86370735u, 0x1cd4c4d4u, 0x1fb5eb99u);
            SCE->REG_00H = 0x00003283u;
            SCE->REG_2CH = 0x00000012u;
            HW_SCE_p_func320(136);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x301cecd5u, 0x4564a991u, 0xbc369ba9u, 0x4a2cf3e1u);
            SCE->REG_00H = 0x00003283u;
            SCE->REG_2CH = 0x00000013u;
            HW_SCE_p_func320(172);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf8299ab7u, 0x076dd2d1u, 0xc71f95d9u, 0x3f74c2beu);
            SCE->REG_00H = 0x00003283u;
            SCE->REG_2CH = 0x00000010u;
            HW_SCE_p_func320(208);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011af8f9u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x955095f2u, 0xd4c1cc44u, 0x0ce404d9u, 0x52d5d7b5u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func319(408);
            HW_SCE_p_func100(0xe316b5d0u, 0xdc820713u, 0x5f194abdu, 0xee24561du);
            HW_SCE_p_func314(408+32);
            HW_SCE_p_func100(0x9ac19dcdu, 0x11319817u, 0x001f0298u, 0xd44474ddu);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0130aeffu);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf2b7c604u, 0xc4d8ae51u, 0xa1400e6du, 0x4ac2cfe5u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000023u;
            HW_SCE_p_func319(444);
            HW_SCE_p_func100(0xc8a82995u, 0x69c2c9d0u, 0xa23c78e5u, 0xa1933962u);
            HW_SCE_p_func314(444+32);
            HW_SCE_p_func100(0x3e8777a9u, 0x035aba94u, 0xf0b79fbeu, 0xe1b3f6a2u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x010964eau);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xeaa6d560u, 0xabad2c3au, 0xdc290ad1u, 0x39475f8bu);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func319(480);
            HW_SCE_p_func100(0x2b3c96c7u, 0xb57a384du, 0x2a0d1079u, 0x0b244eddu);
            HW_SCE_p_func314(480+32);
            HW_SCE_p_func100(0x818d681cu, 0x3c100869u, 0xd540af50u, 0x53b53f03u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01fe1091u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x575886ccu, 0x974ffacdu, 0x38c459acu, 0xc330f9f3u);
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
            HW_SCE_p_func100(0xc1082ebfu, 0xb40fb8aeu, 0x79c8c97cu, 0xed24f889u);
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
            HW_SCE_p_func100(0x9fb715ddu, 0xd24805b2u, 0xe75eea3fu, 0x21359476u);
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
            HW_SCE_p_func100(0x3d283b5bu, 0xc0006d6eu, 0x5de47c42u, 0x0b5c8f89u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func319(544);
            HW_SCE_p_func100(0x94a39151u, 0xb687a632u, 0x001e36d5u, 0xf6e53aecu);
            HW_SCE_p_func314(544+32);
            HW_SCE_p_func100(0x244d5b4du, 0xe0528084u, 0xa5561169u, 0x921196d6u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01f11123u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x813a2c73u, 0xc5f64d97u, 0x9fd7d1dbu, 0x38014a6du);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000023u;
            HW_SCE_p_func319(580);
            HW_SCE_p_func100(0xa5186967u, 0xf53547d6u, 0x1f89c868u, 0x20367485u);
            HW_SCE_p_func314(580+32);
            HW_SCE_p_func100(0x459a5ae0u, 0x3c7dce9du, 0x7515a16eu, 0x531936b7u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ac62c9u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf3133da1u, 0x77545f92u, 0x2c13ae9bu, 0x8ab362ebu);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func319(616);
            HW_SCE_p_func100(0x58ee5ddbu, 0x9061965bu, 0xfdbfec79u, 0xab87a7f8u);
            HW_SCE_p_func314(616+32);
            SCE->REG_ECH = 0x0000b7a0u;
            SCE->REG_ECH = 0x000000f1u;
            HW_SCE_p_func101(0x55a0f782u, 0xc388d766u, 0xc11aff3bu, 0x804653c6u);
            HW_SCE_p_func318();
            HW_SCE_p_func100(0x8f95701eu, 0x150383aau, 0x313ca36du, 0x62f31989u);
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
            HW_SCE_p_func100(0x27b6018du, 0xc2d58137u, 0xdaca4f73u, 0xa52f81c8u);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000022u;
            HW_SCE_p_func319(136);
            HW_SCE_p_func100(0x7431f476u, 0x94a93defu, 0x3ba1ad1du, 0x21d00227u);
            HW_SCE_p_func314(136+32);
            HW_SCE_p_func100(0x25a731a2u, 0x4a77f567u, 0xe605568cu, 0x0e3a4862u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x4d9ad891u, 0x883ad05fu, 0x12dd6651u, 0x691f5aafu);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000023u;
            HW_SCE_p_func319(172);
            HW_SCE_p_func100(0x0e617478u, 0xaec9a0f7u, 0xab6c622bu, 0xc06428feu);
            HW_SCE_p_func314(172+32);
            HW_SCE_p_func100(0x8c9380feu, 0x7636013au, 0x4796f2c7u, 0xb9a6e0b0u);
            SCE->REG_104H = 0x00000058u;
            SCE->REG_E0H = 0x80010020u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1u);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xe3018af1u, 0x5ca863f5u, 0xc01f235du, 0xd337275fu);
            SCE->REG_00H = 0x00002383u;
            SCE->REG_2CH = 0x00000020u;
            HW_SCE_p_func319(208);
            HW_SCE_p_func100(0xb42aa5c7u, 0xde19d9cau, 0x018b5d65u, 0xef529d6fu);
            HW_SCE_p_func314(208+32);
            SCE->REG_ECH = 0x0000d260u;
            HW_SCE_p_func101(0x96bd80abu, 0xe755313eu, 0x61b1ac43u, 0xfe71c8cfu);
        }
        SCE->REG_ECH = 0x01816e94u;
        HW_SCE_p_func101(0xa7c7f7dfu, 0x2e444bafu, 0x34990ba4u, 0x0ce22f12u);
    }
    SCE->REG_ECH = 0x38008a20u;
    SCE->REG_ECH = 0x00000020u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    HW_SCE_p_func100(0x6deb8b57u, 0x94b7124bu, 0x66285537u, 0x5db62f05u);
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
    HW_SCE_p_func100(0xaf2a241bu, 0xd409fd47u, 0x4b0764afu, 0xf4628897u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func320(136);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012e06e6u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcb93e799u, 0x927f831eu, 0x87824be8u, 0xbd7dd869u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000013u;
    HW_SCE_p_func320(172);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0100abe1u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe14b8260u, 0xc2f90836u, 0xa4e4ccfeu, 0xb9181958u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(208);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc8121ceau, 0x80714d15u, 0x8cef80eeu, 0xb7b9ecb1u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x135ecb32u, 0xf40d3d5au, 0x5b75cd89u, 0x555e08a7u);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0xd562a946u, 0xb0463152u, 0x1be9639cu, 0xa25bfe98u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfb0b81a2u, 0x0475c67eu, 0xb2f3371fu, 0x9c99e5e5u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x247abdc4u, 0x8088223au, 0x4c2a3bd3u, 0xf6f4099cu);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0x486c7a40u, 0x6761da7eu, 0xf076a48eu, 0x4c49b7bfu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eau);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc1ba29d8u, 0x6b9bded9u, 0xd2a90427u, 0x65629fb1u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0x22079e19u, 0x70a0624fu, 0xef51c3adu, 0xc38e93d3u);
    HW_SCE_p_func314(480+32);
    HW_SCE_p_func100(0xa9f9e0a8u, 0x6a85e3a5u, 0x0642606au, 0xdd999e86u);
    SCE->REG_28H = 0x00bf0001u;
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
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb1ebc7b9u, 0x0f36ca8au, 0x8f9b5f56u, 0x44721820u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func319(616);
    HW_SCE_p_func100(0x68433359u, 0x306beee5u, 0x552d671du, 0x7168bbbcu);
    HW_SCE_p_func314(616+32);
    HW_SCE_p_func100(0xe33d52b8u, 0x809c11a1u, 0xf5117386u, 0xcc37fadcu);
    SCE->REG_28H = 0x00bf0001u;
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
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x48c37190u, 0x8bbefda8u, 0x978c9cddu, 0x53e45d9bu);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func319(544);
    HW_SCE_p_func100(0xa3b1323fu, 0xf6874d14u, 0x8668673bu, 0x7990152fu);
    HW_SCE_p_func314(544+32);
    HW_SCE_p_func100(0x7daabbc8u, 0x38612bfeu, 0xf86a0b66u, 0x934059b4u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x47bab8c1u, 0xafc73bcfu, 0x5e08a50du, 0x30704306u);
    SCE->REG_00H = 0x00002383u;
    SCE->REG_2CH = 0x00000023u;
    HW_SCE_p_func319(580);
    HW_SCE_p_func100(0x6a8a5afdu, 0x62926c28u, 0x8e1be5b5u, 0x89cbfff9u);
    HW_SCE_p_func314(580+32);
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f2u;
    HW_SCE_p_func101(0xe3857bc5u, 0x0bf35aafu, 0xe3f75101u, 0x83c810b1u);
    HW_SCE_p_func318();
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00003bbeu;
    SCE->REG_ECH = 0x00007c1du;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func325.prc
***********************************************************************************************************************/
