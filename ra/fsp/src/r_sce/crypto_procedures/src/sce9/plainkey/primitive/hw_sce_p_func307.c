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

void HW_SCE_p_func307_r1(void)
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
    SCE->REG_ECH = 0x00000090U;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000080U;
    HW_SCE_p_func101(0x46765f77U, 0x5749f546U, 0xffae0ff7U, 0x8b2d018eU);
    HW_SCE_p_func311_r1();
    SCE->REG_ECH = 0x00000a73U;
    SCE->REG_ECH = 0x00000a31U;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        SCE->REG_ECH = 0x00002e20U;
        SCE->REG_ECH = 0x38002673U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func100(0x0efed670U, 0x4c5eb194U, 0xde5be454U, 0x29041d0fU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x733f12abU, 0xecc5543eU, 0xc537a171U, 0x48357424U);
        }
        else
        {
            HW_SCE_p_func100(0x2d664c4dU, 0xd9d9fd9dU, 0xe34eae6aU, 0x62d43b41U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xe804d856U, 0xe4909999U, 0xa52e04fdU, 0xfe75ac58U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000010U;
            HW_SCE_p_func312(204);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x517c7161U, 0x77c03114U, 0x61d87db2U, 0x4f1c9985U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            HW_SCE_p_func312(136);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01a67f45U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x989e30fdU, 0xfb087ef5U, 0xec2e871bU, 0x64eb0658U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func313(476);
            HW_SCE_p_func100(0xbf56fa09U, 0x821175ccU, 0x1891f091U, 0x8f3b024aU);
            HW_SCE_p_func314(476+64);
            HW_SCE_p_func100(0xd2825fcdU, 0xc659f6e8U, 0x10029c48U, 0x47827fb5U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019fce91U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xa3c241c7U, 0x45c0ad6bU, 0xe6a7bb38U, 0x84b04d8bU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func313(612);
            HW_SCE_p_func100(0x3f406e95U, 0x13025ff8U, 0xf8b51b24U, 0x4c05351cU);
            HW_SCE_p_func314(612+64);
            HW_SCE_p_func100(0x0830ae7aU, 0x6d43b3e9U, 0xd4ccc5eaU, 0xe6dcdce5U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011f5dcdU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x40901979U, 0xc4600862U, 0x60d83598U, 0xf0d8941fU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func313(408);
            HW_SCE_p_func100(0x2c04ab0bU, 0x0e747ad8U, 0x7eb80229U, 0xf876f457U);
            HW_SCE_p_func314(408+64);
            HW_SCE_p_func100(0xa016bd2cU, 0x3aa9aa45U, 0x7542dc38U, 0xdcc879c6U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01e59c3dU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x20c49ee6U, 0x329d4116U, 0xa1fa89feU, 0x0340299cU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func313(544);
            HW_SCE_p_func100(0x6e9c8d98U, 0x6120d3adU, 0x665f0919U, 0x27efb3baU);
            HW_SCE_p_func314(544+64);
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x00000081U;
            HW_SCE_p_func101(0xca53192fU, 0x211abfddU, 0xa870386fU, 0xb8e79d3eU);
            HW_SCE_p_func309_r1();
            HW_SCE_p_func100(0xcd35d372U, 0x54dbdbceU, 0xb0afbbdbU, 0xf796fc29U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xaee9f5b2U, 0x522163adU, 0x95ef5614U, 0x66787e86U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func313(204);
            HW_SCE_p_func100(0x2e1850f0U, 0x07ff76f0U, 0xce36e13cU, 0x6eea89e8U);
            HW_SCE_p_func314(204+64);
            HW_SCE_p_func100(0x05d76537U, 0xa64e6099U, 0x19533700U, 0x491094b8U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xe6475365U, 0x1fae56fbU, 0x565db664U, 0xa6771660U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func313(136);
            HW_SCE_p_func100(0xfe310ec6U, 0xff3bb340U, 0x3af230a3U, 0xbcedede9U);
            HW_SCE_p_func314(136+64);
            HW_SCE_p_func101(0x9fa02c96U, 0xfaf805deU, 0x6623feddU, 0xbc1389aeU);
        }
        SCE->REG_ECH = 0x3800da9fU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func100(0x3d92f89aU, 0xa4b197f4U, 0x583087f9U, 0x353f282dU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x60afc885U, 0xc0ff181bU, 0x12ea81aeU, 0x2804d93eU);
        }
        else
        {
            HW_SCE_p_func100(0xb9b491e0U, 0x1463bd81U, 0x8cdca180U, 0x461e2b79U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x909714ffU, 0xd0219bf6U, 0x9f8fbbbdU, 0xd4083fd2U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000010U;
            HW_SCE_p_func312(204);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            HW_SCE_p_func080();
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            HW_SCE_p_func312(136);
            HW_SCE_p_func100(0x5592c700U, 0x5a6eaa8aU, 0xd9bf08bdU, 0x69ab981dU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01a67f45U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x5925d68dU, 0x7a61ecf6U, 0x5bae60ccU, 0x83f7e3a4U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func313(476);
            HW_SCE_p_func100(0xa3ca016bU, 0x8aaf93d3U, 0xbdc90e30U, 0x56d8ac7dU);
            HW_SCE_p_func314(476+64);
            HW_SCE_p_func100(0xb313c752U, 0x5c602865U, 0xec2fe69cU, 0x7be094a4U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011f5dcdU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xa821b521U, 0x461c4e09U, 0x65b8de9cU, 0x3ce623a5U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func313(408);
            HW_SCE_p_func100(0x1360b584U, 0xf686799dU, 0xab5b69bfU, 0x19469924U);
            HW_SCE_p_func314(408+64);
            HW_SCE_p_func100(0x7af0c270U, 0x7ed6ff84U, 0x92765f4fU, 0xc608e17fU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0132d44bU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x6964e4b4U, 0xe864d305U, 0xc84d8bb4U, 0x07ec5ec8U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000010U;
            HW_SCE_p_func312(68);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01432c7aU);
            HW_SCE_p_func080();
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            HW_SCE_p_func312(0);
            HW_SCE_p_func100(0xd7e164c0U, 0x1ecc338bU, 0x510e64e7U, 0x6a2613a5U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019fce91U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x4e82d9a2U, 0x40be6e96U, 0x0fe40003U, 0x6ff6e827U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func313(612);
            HW_SCE_p_func100(0xa348c089U, 0x43d0ff84U, 0x778ff6b8U, 0x67521438U);
            HW_SCE_p_func314(612+64);
            HW_SCE_p_func100(0xdc825e03U, 0x32ed1ec4U, 0x42c88adfU, 0x371b0bc8U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01e59c3dU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x0e29cd80U, 0x38300037U, 0x45986240U, 0x957d7b77U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func313(544);
            HW_SCE_p_func100(0x4e55f63aU, 0x2241701bU, 0x4a60cce7U, 0x29c0bbd9U);
            HW_SCE_p_func314(544+64);
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x00000082U;
            HW_SCE_p_func101(0x8389d01fU, 0xe6c6ffddU, 0x142d5ccfU, 0x7a0e9c6dU);
            HW_SCE_p_func309_r1();
            HW_SCE_p_func100(0xdee3518fU, 0xb273ad82U, 0x9fe71ee7U, 0x2edf8f2cU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0xb9c1509fU, 0xbf54f012U, 0x98c8652aU, 0x203d25fcU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            HW_SCE_p_func313(204);
            HW_SCE_p_func100(0x8eea8326U, 0x2d4020ceU, 0x4d41424cU, 0xe4982805U);
            HW_SCE_p_func314(204+64);
            HW_SCE_p_func100(0xbf7df5f8U, 0x324650caU, 0x225fdd08U, 0x90466761U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            HW_SCE_p_func080();
            HW_SCE_p_func100(0x45705ce6U, 0xd8eacde4U, 0x3a795df3U, 0xbe5b4797U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            HW_SCE_p_func313(136);
            HW_SCE_p_func100(0x1fe6691eU, 0xe9108d9aU, 0x57f0bf4cU, 0x6708d01cU);
            HW_SCE_p_func314(136+64);
            SCE->REG_ECH = 0x0000d260U;
            HW_SCE_p_func101(0x6358b604U, 0x6dc2d12bU, 0x6cbb7715U, 0x3eb0ec45U);
        }
        SCE->REG_ECH = 0x01816e94U;
        HW_SCE_p_func101(0xf737726cU, 0x7dc9f6f9U, 0xe1731169U, 0x6df578f1U);
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000020U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    HW_SCE_p_func100(0x07ff897aU, 0x247d24c7U, 0xfbf81f2cU, 0x1baceb97U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c85beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5035ba16U, 0xf255a3adU, 0x1ed0bc13U, 0x92e894d5U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func312(204);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016bcaa1U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4a5f6826U, 0xfa67b379U, 0x995c12b3U, 0x2c6cab19U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(136);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9f2effcaU, 0xfa8f0918U, 0x75ac2514U, 0xf921ad9fU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func313(476);
    HW_SCE_p_func100(0x932f0373U, 0x17ca4781U, 0x75f63f1dU, 0x12347107U);
    HW_SCE_p_func314(476+64);
    HW_SCE_p_func100(0x5e19c95eU, 0x1bf7f515U, 0xa49b9e82U, 0xdebab01eU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc5a99131U, 0x9797c7d3U, 0xea9c1037U, 0xb9f0451dU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(408);
    HW_SCE_p_func100(0x95a8001eU, 0x9fb1b0ecU, 0xf62ab0a9U, 0x2b362008U);
    HW_SCE_p_func314(408+64);
    HW_SCE_p_func100(0x4bcfab8fU, 0x3ffb18cfU, 0x786aa6c9U, 0x3bab7324U);
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4078b7d0U, 0x46f98634U, 0x880c48a1U, 0x7cf1df0dU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func313(612);
    HW_SCE_p_func100(0x68145b96U, 0x8dfc7766U, 0xc0a86193U, 0x9d16ea7aU);
    HW_SCE_p_func314(612+64);
    HW_SCE_p_func100(0xb2940826U, 0xa63e577fU, 0x926b6b1eU, 0x16a88b70U);
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x17c2749cU, 0x8d75c162U, 0xfd7d6916U, 0x945b30a9U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(544);
    HW_SCE_p_func100(0x5cdf4f3dU, 0xc1445dfaU, 0x7c2cd0aaU, 0x42ffc8a0U);
    HW_SCE_p_func314(544+64);
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000083U;
    HW_SCE_p_func101(0x24e91976U, 0x418be7b2U, 0x2aeeec01U, 0x65afa0b3U);
    HW_SCE_p_func309_r1();
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000090U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCEp_func307_r1.prc
***********************************************************************************************************************/
