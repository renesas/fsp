/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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

void HW_SCE_p_func325_r1(void)
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
    HW_SCE_p_func101(0x19b9f8aeU, 0x00dc1eecU, 0xf9dd9c29U, 0x487dca94U);
    HW_SCE_p_func324();
    SCE->REG_ECH = 0x00000a73U;
    SCE->REG_ECH = 0x00000a31U;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        SCE->REG_ECH = 0x00002e20U;
        SCE->REG_ECH = 0x38002673U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func100(0x5ff32453U, 0x873c3af2U, 0x1ef0a9f2U, 0xeea1abc8U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xd91c4453U, 0x71906777U, 0x65eb6ac8U, 0x68116537U);
        }
        else
        {
            HW_SCE_p_func100(0x6f5b19e9U, 0xdac83bf0U, 0x54111c06U, 0xb860b781U);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xe22eb519U, 0x6de82dcfU, 0xb8f9baceU, 0xbc0d647dU);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000012U;
            HW_SCE_p_func320(136);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x1cdea842U, 0xb564ce9eU, 0xaf62b09dU, 0xa657fcd4U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000013U;
            HW_SCE_p_func320(172);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x6ae3808fU, 0x31e8aaa5U, 0x83c15ab1U, 0x0e1e2a56U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000010U;
            HW_SCE_p_func320(208);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011af8f9U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xdbf17b2cU, 0x6294819cU, 0x1e63b419U, 0x687af4b1U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(408);
            HW_SCE_p_func100(0x6cafabccU, 0xab9a7899U, 0x3e4e3a72U, 0x7238056dU);
            HW_SCE_p_func314(408+32);
            HW_SCE_p_func100(0x2a966046U, 0xe5910a6aU, 0xb9af8bc2U, 0x93b2ee87U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0130aeffU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf0bb19d3U, 0x6d0a732fU, 0x79edce81U, 0x499d547fU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(444);
            HW_SCE_p_func100(0xb6c9eb32U, 0xad8b6a5aU, 0x5b45535dU, 0xdb899e90U);
            HW_SCE_p_func314(444+32);
            HW_SCE_p_func100(0xc8542ac7U, 0x35039915U, 0xfe02b565U, 0x41720439U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x010964eaU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x6977f72aU, 0xf0c40367U, 0x67b15bacU, 0x3c1c7ed3U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(480);
            HW_SCE_p_func100(0x043ee0feU, 0x624f430cU, 0xb8984341U, 0x2e9b0883U);
            HW_SCE_p_func314(480+32);
            HW_SCE_p_func100(0x990f8d9cU, 0xbae662edU, 0x9243df9fU, 0x70f27c08U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01574730U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x882daaf8U, 0x19e744beU, 0x796e7434U, 0x58deac8cU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(544);
            HW_SCE_p_func100(0xa65ba385U, 0xd358b3d1U, 0x514a28beU, 0xc75e4c3cU);
            HW_SCE_p_func314(544+32);
            HW_SCE_p_func100(0x8e27c19eU, 0x824b7d7eU, 0xe50f28fdU, 0x7e778871U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01f11123U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x90947f6fU, 0x28cf15d5U, 0xe7bf2d71U, 0xc95bc76cU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(580);
            HW_SCE_p_func100(0xd47910a8U, 0x77c0c723U, 0x9458a5c8U, 0xf065fe99U);
            HW_SCE_p_func314(580+32);
            HW_SCE_p_func100(0x462657d5U, 0xd8ee238bU, 0x244727e6U, 0x5fbb2ec0U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ac62c9U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x95cd2f1bU, 0xac924fb3U, 0x07bbac8eU, 0x5868deb3U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(616);
            HW_SCE_p_func100(0xb8afe95dU, 0xf0a676a8U, 0x278ca2e7U, 0xd432ab29U);
            HW_SCE_p_func314(616+32);
            SCE->REG_ECH = 0x0000b7a0U;
            SCE->REG_ECH = 0x000000f4U;
            HW_SCE_p_func101(0x9db26816U, 0x580414a7U, 0xd9ca64dfU, 0x92bde1e2U);
            HW_SCE_p_func318();
            HW_SCE_p_func100(0x44a0ca14U, 0x4d979e4fU, 0xfbee0bd6U, 0x9345c810U);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xb954f024U, 0x7851d4d1U, 0x8047587aU, 0x5d6d0f8cU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(136);
            HW_SCE_p_func100(0xb4570d2aU, 0xb4dde668U, 0x71a8e6cdU, 0xf3f1a820U);
            HW_SCE_p_func314(136+32);
            HW_SCE_p_func100(0x237eef91U, 0xda59697dU, 0xa4eb0859U, 0x1ccbde57U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xebf5c34bU, 0x4a1f0b74U, 0x087a146fU, 0xc062284bU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(172);
            HW_SCE_p_func100(0x0b29ed31U, 0x15bc55dbU, 0x05b50a90U, 0xe989c69bU);
            HW_SCE_p_func314(172+32);
            HW_SCE_p_func100(0x720a6ae8U, 0x68450d1bU, 0x0db485e6U, 0x36d04b94U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xc8b750e8U, 0x2793fffbU, 0xfe12fbdaU, 0x766955d4U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(208);
            HW_SCE_p_func100(0xe0cd750bU, 0x5a01adacU, 0x7aab12edU, 0x108d270aU);
            HW_SCE_p_func314(208+32);
            HW_SCE_p_func101(0x8320ae07U, 0x9ec01e29U, 0x20e024c6U, 0x210b2ed0U);
        }
        SCE->REG_ECH = 0x3800da9fU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func100(0x06fcfb29U, 0xb5045fefU, 0x87993562U, 0x6e1bce5dU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0xa3dd6937U, 0x1080ea7cU, 0xc0f8663bU, 0x39b34e02U);
        }
        else
        {
            HW_SCE_p_func100(0x540eaafeU, 0x60f8d266U, 0x51ba7ec8U, 0x6541c4a3U);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xd329fbd9U, 0x86370735U, 0x1cd4c4d4U, 0x1fb5eb99U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000012U;
            HW_SCE_p_func320(136);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x301cecd5U, 0x4564a991U, 0xbc369ba9U, 0x4a2cf3e1U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000013U;
            HW_SCE_p_func320(172);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf8299ab7U, 0x076dd2d1U, 0xc71f95d9U, 0x3f74c2beU);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000010U;
            HW_SCE_p_func320(208);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011af8f9U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x955095f2U, 0xd4c1cc44U, 0x0ce404d9U, 0x52d5d7b5U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(408);
            HW_SCE_p_func100(0xe316b5d0U, 0xdc820713U, 0x5f194abdU, 0xee24561dU);
            HW_SCE_p_func314(408+32);
            HW_SCE_p_func100(0x9ac19dcdU, 0x11319817U, 0x001f0298U, 0xd44474ddU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0130aeffU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf2b7c604U, 0xc4d8ae51U, 0xa1400e6dU, 0x4ac2cfe5U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(444);
            HW_SCE_p_func100(0xc8a82995U, 0x69c2c9d0U, 0xa23c78e5U, 0xa1933962U);
            HW_SCE_p_func314(444+32);
            HW_SCE_p_func100(0x3e8777a9U, 0x035aba94U, 0xf0b79fbeU, 0xe1b3f6a2U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x010964eaU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xeaa6d560U, 0xabad2c3aU, 0xdc290ad1U, 0x39475f8bU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(480);
            HW_SCE_p_func100(0x2b3c96c7U, 0xb57a384dU, 0x2a0d1079U, 0x0b244eddU);
            HW_SCE_p_func314(480+32);
            HW_SCE_p_func100(0x818d681cU, 0x3c100869U, 0xd540af50U, 0x53b53f03U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01fe1091U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x575886ccU, 0x974ffacdU, 0x38c459acU, 0xc330f9f3U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000012U;
            HW_SCE_p_func320(0);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019969f4U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xc1082ebfU, 0xb40fb8aeU, 0x79c8c97cU, 0xed24f889U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000013U;
            HW_SCE_p_func320(36);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019de420U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x9fb715ddU, 0xd24805b2U, 0xe75eea3fU, 0x21359476U);
            SCE->REG_00H = 0x00003283U;
            SCE->REG_2CH = 0x00000010U;
            HW_SCE_p_func320(72);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01574730U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x3d283b5bU, 0xc0006d6eU, 0x5de47c42U, 0x0b5c8f89U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(544);
            HW_SCE_p_func100(0x94a39151U, 0xb687a632U, 0x001e36d5U, 0xf6e53aecU);
            HW_SCE_p_func314(544+32);
            HW_SCE_p_func100(0x244d5b4dU, 0xe0528084U, 0xa5561169U, 0x921196d6U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01f11123U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x813a2c73U, 0xc5f64d97U, 0x9fd7d1dbU, 0x38014a6dU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(580);
            HW_SCE_p_func100(0xa5186967U, 0xf53547d6U, 0x1f89c868U, 0x20367485U);
            HW_SCE_p_func314(580+32);
            HW_SCE_p_func100(0x459a5ae0U, 0x3c7dce9dU, 0x7515a16eU, 0x531936b7U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ac62c9U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xf3133da1U, 0x77545f92U, 0x2c13ae9bU, 0x8ab362ebU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(616);
            HW_SCE_p_func100(0x58ee5ddbU, 0x9061965bU, 0xfdbfec79U, 0xab87a7f8U);
            HW_SCE_p_func314(616+32);
            SCE->REG_ECH = 0x0000b7a0U;
            SCE->REG_ECH = 0x000000f5U;
            HW_SCE_p_func101(0x05b6651dU, 0x48026b34U, 0x58ac622fU, 0x14f9c9f5U);
            HW_SCE_p_func318();
            HW_SCE_p_func100(0x6e700f7dU, 0x2298cb4bU, 0x32e82298U, 0x484d8424U);
            SCE->REG_28H = 0x009f0001U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01ef2f1cU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x4a3a5487U, 0xa5840bb3U, 0xc732bae8U, 0xa2ad21fcU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(136);
            HW_SCE_p_func100(0xcc9ac09dU, 0x0081ac03U, 0x4ab916edU, 0x9d913812U);
            HW_SCE_p_func314(136+32);
            HW_SCE_p_func100(0xbc6549c2U, 0xd9456641U, 0xb34e86e6U, 0xe288c583U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x16113b33U, 0x794e7aecU, 0x3cea8c45U, 0x075c5a35U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(172);
            HW_SCE_p_func100(0x2b248b83U, 0xa35118afU, 0xd2039341U, 0x88e2a7caU);
            HW_SCE_p_func314(172+32);
            HW_SCE_p_func100(0xe2d50f2eU, 0xa24a6f89U, 0x54e55185U, 0x3e958e8cU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x5a52d3d2U, 0x714fcb0eU, 0x4ebf21a2U, 0x64792c7dU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(208);
            HW_SCE_p_func100(0xb1242de9U, 0x181a13e5U, 0x5a2970e3U, 0x03564c58U);
            HW_SCE_p_func314(208+32);
            SCE->REG_ECH = 0x0000d260U;
            HW_SCE_p_func101(0x19f26e8cU, 0x8e32d1ccU, 0x201b6801U, 0x24d584e1U);
        }
        SCE->REG_ECH = 0x01816e94U;
        HW_SCE_p_func101(0xa7c7f7dfU, 0x2e444bafU, 0x34990ba4U, 0x0ce22f12U);
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000020U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    HW_SCE_p_func100(0x6deb8b57U, 0x94b7124bU, 0x66285537U, 0x5db62f05U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef2f1cU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xaf2a241bU, 0xd409fd47U, 0x4b0764afU, 0xf4628897U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func320(136);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012e06e6U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcb93e799U, 0x927f831eU, 0x87824be8U, 0xbd7dd869U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000013U;
    HW_SCE_p_func320(172);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0100abe1U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe14b8260U, 0xc2f90836U, 0xa4e4ccfeU, 0xb9181958U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(208);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc8121ceaU, 0x80714d15U, 0x8cef80eeU, 0xb7b9ecb1U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x135ecb32U, 0xf40d3d5aU, 0x5b75cd89U, 0x555e08a7U);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0xd562a946U, 0xb0463152U, 0x1be9639cU, 0xa25bfe98U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfb0b81a2U, 0x0475c67eU, 0xb2f3371fU, 0x9c99e5e5U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x247abdc4U, 0x8088223aU, 0x4c2a3bd3U, 0xf6f4099cU);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0x486c7a40U, 0x6761da7eU, 0xf076a48eU, 0x4c49b7bfU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc1ba29d8U, 0x6b9bded9U, 0xd2a90427U, 0x65629fb1U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0x22079e19U, 0x70a0624fU, 0xef51c3adU, 0xc38e93d3U);
    HW_SCE_p_func314(480+32);
    HW_SCE_p_func100(0xa9f9e0a8U, 0x6a85e3a5U, 0x0642606aU, 0xdd999e86U);
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
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb1ebc7b9U, 0x0f36ca8aU, 0x8f9b5f56U, 0x44721820U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func319(616);
    HW_SCE_p_func100(0x68433359U, 0x306beee5U, 0x552d671dU, 0x7168bbbcU);
    HW_SCE_p_func314(616+32);
    HW_SCE_p_func100(0xe33d52b8U, 0x809c11a1U, 0xf5117386U, 0xcc37fadcU);
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
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x48c37190U, 0x8bbefda8U, 0x978c9cddU, 0x53e45d9bU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(544);
    HW_SCE_p_func100(0xa3b1323fU, 0xf6874d14U, 0x8668673bU, 0x7990152fU);
    HW_SCE_p_func314(544+32);
    HW_SCE_p_func100(0x7daabbc8U, 0x38612bfeU, 0xf86a0b66U, 0x934059b4U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x47bab8c1U, 0xafc73bcfU, 0x5e08a50dU, 0x30704306U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(580);
    HW_SCE_p_func100(0x6a8a5afdU, 0x62926c28U, 0x8e1be5b5U, 0x89cbfff9U);
    HW_SCE_p_func314(580+32);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f6U;
    HW_SCE_p_func101(0xb4164b6fU, 0x32459ef0U, 0x26b1ec51U, 0x36eee209U);
    HW_SCE_p_func318();
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCEp_func325_r1.prc
***********************************************************************************************************************/
