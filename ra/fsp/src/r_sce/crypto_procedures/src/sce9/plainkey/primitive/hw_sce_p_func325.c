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
            SCE->REG_ECH = 0x000000f0U;
            HW_SCE_p_func101(0x4b583ae7U, 0x56d78152U, 0xd8cd207fU, 0x9097cbb4U);
            HW_SCE_p_func318();
            HW_SCE_p_func100(0xa29f08daU, 0x8b21226dU, 0xba1aa171U, 0x8c03bd6bU);
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
            HW_SCE_p_func100(0x3e09f796U, 0x1f5513baU, 0xf2906a3aU, 0xf6a264a1U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(136);
            HW_SCE_p_func100(0x83f2f5c5U, 0xdb4b3aa1U, 0xacb5ab71U, 0xe7159fd6U);
            HW_SCE_p_func314(136+32);
            HW_SCE_p_func100(0xc6cc13adU, 0x22bf318cU, 0xd52ea535U, 0x0bfda6bcU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x4434b13aU, 0x76d201adU, 0x198d4932U, 0xd9a8e8c6U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(172);
            HW_SCE_p_func100(0x2034127aU, 0x60179772U, 0x9d4f2692U, 0xf359f550U);
            HW_SCE_p_func314(172+32);
            HW_SCE_p_func100(0x03be931eU, 0x9b569d30U, 0xf39d0140U, 0x2f929436U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xd22044a4U, 0x1911ee48U, 0x559c468eU, 0x6062e4e5U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(208);
            HW_SCE_p_func100(0xf4dc0b69U, 0xee39d2a1U, 0x3638a4f4U, 0x87ad8cf6U);
            HW_SCE_p_func314(208+32);
            HW_SCE_p_func101(0x48c6011cU, 0x2d1d0c0eU, 0x3ad508d0U, 0x1863f5c7U);
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
            SCE->REG_ECH = 0x000000f1U;
            HW_SCE_p_func101(0x55a0f782U, 0xc388d766U, 0xc11aff3bU, 0x804653c6U);
            HW_SCE_p_func318();
            HW_SCE_p_func100(0x8f95701eU, 0x150383aaU, 0x313ca36dU, 0x62f31989U);
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
            HW_SCE_p_func100(0x27b6018dU, 0xc2d58137U, 0xdaca4f73U, 0xa52f81c8U);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func319(136);
            HW_SCE_p_func100(0x7431f476U, 0x94a93defU, 0x3ba1ad1dU, 0x21d00227U);
            HW_SCE_p_func314(136+32);
            HW_SCE_p_func100(0x25a731a2U, 0x4a77f567U, 0xe605568cU, 0x0e3a4862U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x012e06e6U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x4d9ad891U, 0x883ad05fU, 0x12dd6651U, 0x691f5aafU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000023U;
            HW_SCE_p_func319(172);
            HW_SCE_p_func100(0x0e617478U, 0xaec9a0f7U, 0xab6c622bU, 0xc06428feU);
            HW_SCE_p_func314(172+32);
            HW_SCE_p_func100(0x8c9380feU, 0x7636013aU, 0x4796f2c7U, 0xb9a6e0b0U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0100abe1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xe3018af1U, 0x5ca863f5U, 0xc01f235dU, 0xd337275fU);
            SCE->REG_00H = 0x00002383U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func319(208);
            HW_SCE_p_func100(0xb42aa5c7U, 0xde19d9caU, 0x018b5d65U, 0xef529d6fU);
            HW_SCE_p_func314(208+32);
            SCE->REG_ECH = 0x0000d260U;
            HW_SCE_p_func101(0x96bd80abU, 0xe755313eU, 0x61b1ac43U, 0xfe71c8cfU);
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
    SCE->REG_ECH = 0x000000f2U;
    HW_SCE_p_func101(0xe3857bc5U, 0x0bf35aafU, 0xe3f75101U, 0x83c810b1U);
    HW_SCE_p_func318();
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func325.prc
***********************************************************************************************************************/
