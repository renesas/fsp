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
#include "r_sce.h"
#include "r_sce_private.h"

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

void R_SCE_func325(void)
{
    uint32_t iLoop    = 0U;
    uint32_t iLoop1   = 0U;
    uint32_t iLoop2   = 0U;
    int32_t  jLoop    = 0U;
    uint32_t kLoop    = 0U;
    uint32_t oLoop    = 0U;
    uint32_t oLoop1   = 0U;
    uint32_t oLoop2   = 0U;
    uint32_t dummy    = 0U;
    uint32_t KEY_ADR  = 0U;
    uint32_t OFS_ADR  = 0U;
    uint32_t MAX_CNT2 = 0U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003fbeU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f0U;
    R_SCE_func101(0x01df4410U, 0x25186facU, 0xc0075b91U, 0x7743fcadU);
    R_SCE_func324();
    SCE->REG_ECH = 0x00000a73U;
    SCE->REG_ECH = 0x00000a31U;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        SCE->REG_ECH = 0x00002e20U;
        SCE->REG_ECH = 0x38002673U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func100(0x908f652fU, 0x12371bfeU, 0x96ad2afeU, 0x6d9d50f3U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x11e5f4f1U, 0x6d84a57aU, 0xc809f751U, 0x99636076U);
        }
        else
        {
            R_SCE_func100(0xfa2e0ea1U, 0xea818c35U, 0x206dd7d8U, 0xa982af56U);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            R_SCE_func080();
            R_SCE_func100(0x601d254bU, 0xc6c8196aU, 0x822d4883U, 0x9884b420U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000012U;
            R_SCE_func320(136);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            R_SCE_func080();
            R_SCE_func100(0x7db7dc7bU, 0xc4a198eeU, 0x9110a238U, 0x0e1526e3U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000013U;
            R_SCE_func320(172);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            R_SCE_func080();
            R_SCE_func100(0x1f97b750U, 0xabf9cf2dU, 0x02f06b86U, 0x607cf951U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000010U;
            R_SCE_func320(208);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011af8f9U);
            R_SCE_func080();
            R_SCE_func100(0x775c82b8U, 0xbffd76d9U, 0xf0b31502U, 0x55643534U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func319(408);
            R_SCE_func100(0xb39891fbU, 0x61bdd3d2U, 0x9cdcf4a3U, 0x9547c3d6U);
            R_SCE_func314(408+32);
            R_SCE_func100(0x2d57513fU, 0xcdc90ceaU, 0x422ca489U, 0xf15cd933U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0130aeffU);
            R_SCE_func080();
            R_SCE_func100(0x446d6820U, 0x9a780882U, 0xa6e287a6U, 0x0e609579U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            R_SCE_func319(444);
            R_SCE_func100(0xe0c086e1U, 0xd25b71bbU, 0xf516549aU, 0x86a946efU);
            R_SCE_func314(444+32);
            R_SCE_func100(0xe56eed48U, 0x85b8e7b6U, 0x1acaef41U, 0xd213ea22U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x010964eaU);
            R_SCE_func080();
            R_SCE_func100(0xb91c5c86U, 0x79eafe0aU, 0xaea965e8U, 0xd122ee72U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func319(480);
            R_SCE_func100(0x587c5d00U, 0x624336d5U, 0x253445a1U, 0xbdacb006U);
            R_SCE_func314(480+32);
            R_SCE_func100(0x9cd90b3eU, 0x5eb55e97U, 0x87cfa963U, 0x77434f39U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01574730U);
            R_SCE_func080();
            R_SCE_func100(0xc17847b2U, 0x8830192fU, 0x546a11d8U, 0x99341ce0U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func319(544);
            R_SCE_func100(0x210ad79dU, 0x19a3f01dU, 0x5892e46dU, 0x50c7d007U);
            R_SCE_func314(544+32);
            R_SCE_func100(0x1007e210U, 0x980e5ae9U, 0xfbbd5ad2U, 0x5a9d8c47U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01f11123U);
            R_SCE_func080();
            R_SCE_func100(0xbc75c1adU, 0x16be37efU, 0x073750ffU, 0x0194fc3cU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            R_SCE_func319(580);
            R_SCE_func100(0x342e81f6U, 0x80bcaddaU, 0x643a5cb6U, 0xfb297621U);
            R_SCE_func314(580+32);
            R_SCE_func100(0xc4f9eb6dU, 0x84423fb8U, 0x9ef8a114U, 0x0e872738U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ac62c9U);
            R_SCE_func080();
            R_SCE_func100(0x27437ef9U, 0x737420f5U, 0xf2152a8cU, 0x8f3366fbU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func319(616);
            R_SCE_func100(0x5e070d2bU, 0x2861ec9cU, 0xddebfea5U, 0x5e6be40aU);
            R_SCE_func314(616+32);
            SCE->REG_ECH = 0x0000b7a0U;
            SCE->REG_ECH = 0x000000f0U;
            R_SCE_func101(0x8504baf0U, 0x98c213a7U, 0x7ba693a6U, 0xbe05b697U);
            R_SCE_func318();
            R_SCE_func100(0xc97a2978U, 0x949d76fcU, 0x49120e25U, 0xfb5ec39aU);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            R_SCE_func080();
            R_SCE_func100(0xc9848707U, 0x732fe66bU, 0xa4c3e64aU, 0x0ab5e387U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func319(136);
            R_SCE_func100(0x7a59ac3cU, 0xab0ae38aU, 0xd0306db7U, 0x8c5feb38U);
            R_SCE_func314(136+32);
            R_SCE_func100(0xf3a0d3c7U, 0x0dec92b0U, 0xd17099d7U, 0x06a2d285U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            R_SCE_func080();
            R_SCE_func100(0x0cef17afU, 0x00de804eU, 0xd14e112aU, 0x797d9bdeU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            R_SCE_func319(172);
            R_SCE_func100(0x9ca71154U, 0x37bd596bU, 0x21278a1eU, 0x551d02f1U);
            R_SCE_func314(172+32);
            R_SCE_func100(0xea715054U, 0x50f39232U, 0x606179a9U, 0xaa3c0311U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            R_SCE_func080();
            R_SCE_func100(0xa687f8dbU, 0x5cb7e174U, 0x0e863223U, 0x911f200bU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func319(208);
            R_SCE_func100(0x909ebb52U, 0x60af5848U, 0x6997f317U, 0xf434ba3fU);
            R_SCE_func314(208+32);
            R_SCE_func101(0x45c1f242U, 0x313d5619U, 0x3572a9ecU, 0xf5a37769U);
        }
        SCE->REG_ECH = 0x3800da9fU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func100(0xa9d5449cU, 0xe39f423dU, 0x8ff10b63U, 0x073b3b82U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0xefb7b8baU, 0x7e980dcbU, 0x1ee49179U, 0x3586b701U);
        }
        else
        {
            R_SCE_func100(0x6236b7f6U, 0x7ca8b230U, 0x2beb8a3eU, 0xe9c3edf7U);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            R_SCE_func080();
            R_SCE_func100(0x2495874bU, 0xf92c43dbU, 0xabc3130dU, 0xffbeee97U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000012U;
            R_SCE_func320(136);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            R_SCE_func080();
            R_SCE_func100(0xed242108U, 0xbcaca17bU, 0xec49b686U, 0x9e592caeU);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000013U;
            R_SCE_func320(172);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            R_SCE_func080();
            R_SCE_func100(0x0bcb5242U, 0x104610faU, 0xda01cde6U, 0xcf0537efU);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000010U;
            R_SCE_func320(208);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011af8f9U);
            R_SCE_func080();
            R_SCE_func100(0x43c6fc85U, 0x9f089d2dU, 0xd7a50b8aU, 0x291459afU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func319(408);
            R_SCE_func100(0xaeced1cbU, 0x972bea38U, 0x2e208deaU, 0xa9378501U);
            R_SCE_func314(408+32);
            R_SCE_func100(0x5a418b38U, 0xa59b548bU, 0xc3aa4612U, 0x0a4269f2U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0130aeffU);
            R_SCE_func080();
            R_SCE_func100(0x4d05f620U, 0xcb0fa529U, 0x1cdd6d5bU, 0x0cc0daf0U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            R_SCE_func319(444);
            R_SCE_func100(0xc2a94833U, 0x617cecb0U, 0xb0855d1fU, 0xd5fa993eU);
            R_SCE_func314(444+32);
            R_SCE_func100(0x090a524dU, 0x2727222eU, 0xa181dc2fU, 0x2bcd369eU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x010964eaU);
            R_SCE_func080();
            R_SCE_func100(0x426074f3U, 0x912a899eU, 0x0778666eU, 0xf074b79cU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func319(480);
            R_SCE_func100(0xbb422d79U, 0xa1a4a813U, 0x89b0018bU, 0xb0190a52U);
            R_SCE_func314(480+32);
            R_SCE_func100(0xd1416e14U, 0x81b8018eU, 0x2aa99d77U, 0x5da75233U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01fe1091U);
            R_SCE_func080();
            R_SCE_func100(0x5ecf3095U, 0x7125a761U, 0xaff4ef2cU, 0xc491d26bU);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000012U;
            R_SCE_func320(0);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019969f4U);
            R_SCE_func080();
            R_SCE_func100(0x2195c9cdU, 0x9edd401fU, 0x095ffd48U, 0x957e05c1U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000013U;
            R_SCE_func320(36);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019de420U);
            R_SCE_func080();
            R_SCE_func100(0x5e05c154U, 0x9dc5de79U, 0x5b9d8e95U, 0xc72b0350U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000010U;
            R_SCE_func320(72);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01574730U);
            R_SCE_func080();
            R_SCE_func100(0x73475eaeU, 0xc4f26631U, 0xbcfb74dbU, 0x8b0350ceU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func319(544);
            R_SCE_func100(0x2e04d1b2U, 0xabefad23U, 0xf52411ecU, 0x5e724018U);
            R_SCE_func314(544+32);
            R_SCE_func100(0x3cbc8a76U, 0x2fded6c9U, 0x2cf5498bU, 0x275e02e1U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01f11123U);
            R_SCE_func080();
            R_SCE_func100(0xaf402062U, 0xad155a0eU, 0xa5900c85U, 0xdb1608d0U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            R_SCE_func319(580);
            R_SCE_func100(0x9dce9b00U, 0x123ca2e7U, 0x01139d9fU, 0x738d77acU);
            R_SCE_func314(580+32);
            R_SCE_func100(0xa3448e88U, 0x03d0664bU, 0xb55fac14U, 0xdea30f7bU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ac62c9U);
            R_SCE_func080();
            R_SCE_func100(0x5aa8caecU, 0xf96ce569U, 0xb803673bU, 0x365dacafU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func319(616);
            R_SCE_func100(0x0b5d830eU, 0x25e4e603U, 0xddf8cacdU, 0x8cc7eea0U);
            R_SCE_func314(616+32);
            SCE->REG_ECH = 0x0000b7a0U;
            SCE->REG_ECH = 0x000000f1U;
            R_SCE_func101(0x9e2fe872U, 0xe3fe8487U, 0xe8e3d1c3U, 0x3600421cU);
            R_SCE_func318();
            R_SCE_func100(0x9993f00bU, 0xd43b20d5U, 0x8ccd0186U, 0x169b9b48U);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            R_SCE_func080();
            R_SCE_func100(0xa0044513U, 0x02c142f2U, 0xb083d6b6U, 0xf436a715U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func319(136);
            R_SCE_func100(0xdd3473c5U, 0x5c56b339U, 0x44be53d2U, 0xdec4eae4U);
            R_SCE_func314(136+32);
            R_SCE_func100(0xe3c006cdU, 0x4a3d24b9U, 0x35583656U, 0x7e1c7f89U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            R_SCE_func080();
            R_SCE_func100(0xf05de98dU, 0x1a5391c5U, 0x250f290cU, 0x9b2cc401U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            R_SCE_func319(172);
            R_SCE_func100(0x83c9a339U, 0xc45bf34eU, 0x3fe26839U, 0x15bad4b9U);
            R_SCE_func314(172+32);
            R_SCE_func100(0x51dc2d74U, 0xb77c6ffbU, 0x4c087d2cU, 0x3451a641U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            R_SCE_func080();
            R_SCE_func100(0x1a63ef1aU, 0x5c00b85eU, 0xf01ab08aU, 0xc5d4d7a5U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func319(208);
            R_SCE_func100(0x3c2dd259U, 0x4ac8966aU, 0x27321effU, 0x915b8750U);
            R_SCE_func314(208+32);
            SCE->REG_ECH = 0x0000d260U;
            R_SCE_func101(0x406287bdU, 0x8532f418U, 0xd7387695U, 0x41798135U);
        }
        SCE->REG_ECH = 0x01816e94U;
        R_SCE_func101(0x359452aaU, 0x98453f58U, 0x1fd0e35dU, 0x137f3a69U);
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000020U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    R_SCE_func100(0x8101ab22U, 0xcd7e8c3aU, 0x769521d6U, 0xfe12b1f9U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef2f1cU);
    R_SCE_func080();
    R_SCE_func100(0x1184d29aU, 0xee27bc01U, 0x767b805fU, 0x243fa62aU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func320(136);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012e06e6U);
    R_SCE_func080();
    R_SCE_func100(0xd5e8c1beU, 0x2acf111aU, 0x502f6a82U, 0x92bd2dcfU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000013U;
    R_SCE_func320(172);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0100abe1U);
    R_SCE_func080();
    R_SCE_func100(0x21739cdcU, 0x951190acU, 0x45685982U, 0xe86e44c2U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(208);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    R_SCE_func080();
    R_SCE_func100(0xa0dfa6bbU, 0xc3707f6cU, 0x1d070527U, 0xa7a76986U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(408);
    R_SCE_func100(0xe15f6095U, 0x5e7571fbU, 0xc056da74U, 0x4ce96450U);
    R_SCE_func314(408+32);
    R_SCE_func100(0xf8bed511U, 0x1fd12dacU, 0x049f4f8cU, 0xfaac7c32U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    R_SCE_func080();
    R_SCE_func100(0x2613c29fU, 0x2f7124f8U, 0x58c80261U, 0x9e8fad30U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(444);
    R_SCE_func100(0xe377d1adU, 0xf2cc2950U, 0x3e3f9828U, 0x8c99bba0U);
    R_SCE_func314(444+32);
    R_SCE_func100(0xcff395d4U, 0x3a143213U, 0x86331293U, 0xd9b29133U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    R_SCE_func080();
    R_SCE_func100(0x2b9a1733U, 0xabd070c3U, 0x02d6bdfdU, 0xfce33528U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func319(480);
    R_SCE_func100(0x24e5bf06U, 0xba03c1efU, 0x92b67d68U, 0x5ddd0b41U);
    R_SCE_func314(480+32);
    R_SCE_func100(0xacf41896U, 0x49c475acU, 0xe8c0c3caU, 0x87c58bbaU);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    R_SCE_func080();
    R_SCE_func100(0xdd218c06U, 0xfc98d24eU, 0xb309d670U, 0xa81a4505U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func319(616);
    R_SCE_func100(0x99cb872bU, 0x1976524cU, 0x5a0fe391U, 0x647562c5U);
    R_SCE_func314(616+32);
    R_SCE_func100(0xb44723a9U, 0xaf5d6bf9U, 0xe5892cb2U, 0xfaee8697U);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x00000581U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    R_SCE_func080();
    R_SCE_func100(0xe67063b6U, 0xa02bc232U, 0xe36a9c0dU, 0x7c54ca07U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(544);
    R_SCE_func100(0x07975b62U, 0xd726d261U, 0xdb1e7d62U, 0x5c2f39d8U);
    R_SCE_func314(544+32);
    R_SCE_func100(0x99557507U, 0x377308f8U, 0x3bef2dd5U, 0xebd6a27eU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    R_SCE_func080();
    R_SCE_func100(0x490d95cdU, 0xac3d9a2fU, 0x67d4e72fU, 0x5aac6e67U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(580);
    R_SCE_func100(0x88f4a784U, 0x630c5a7aU, 0x26cbe993U, 0xf47e6630U);
    R_SCE_func314(580+32);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f2U;
    R_SCE_func101(0x655c5497U, 0xae524564U, 0x2b01826cU, 0x6a8cb6a5U);
    R_SCE_func318();
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func325.prc
***********************************************************************************************************************/
