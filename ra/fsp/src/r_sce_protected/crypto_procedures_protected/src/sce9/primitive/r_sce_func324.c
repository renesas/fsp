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

void R_SCE_func324(void)
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
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003fbeU;
    R_SCE_func100(0x429de192U, 0xa16d9682U, 0x418795f3U, 0xe9239d90U);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000005c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000060c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_100H = change_endian_long(0x019410dfU);
    R_SCE_func080();
    R_SCE_func100(0x00512c7dU, 0xb2e066fbU, 0x2da6f8f2U, 0x29977d57U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    R_SCE_func080();
    R_SCE_func100(0x222fc4deU, 0x0bd3a9cdU, 0xa8b95887U, 0x285e7485U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    R_SCE_func320(716);
    SCE->REG_24H = 0x0000a0c1U;
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
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    R_SCE_func080();
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(752);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x060049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00210000U;
    oLoop1 = 1;
    while(oLoop1 == 1)
    {
        R_SCE_func100(0xafcf0809U, 0xe2265259U, 0x7768feafU, 0x320f0fcbU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x40a54325U, 0xaeef9d77U, 0x30adfefeU, 0xd0040ad2U);
            oLoop1 = 0;
        }
        else
        {
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x04001991U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x060049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x02001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func101(0x2295cc6cU, 0xf9e30bb5U, 0xe57ac962U, 0xd1b2dda3U);
        }
    }
    R_SCE_func100(0x68757846U, 0xd8685994U, 0x65ee0365U, 0xf90a0df9U);
    SCE->REG_24H = 0x000049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x060049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02001181U;
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
    SCE->REG_100H = change_endian_long(0x01ef2f1cU);
    R_SCE_func080();
    R_SCE_func100(0x3461e611U, 0xf04c888dU, 0x42b43f82U, 0x14db3542U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(136);
    R_SCE_func100(0x5c08a548U, 0x9b5d3c83U, 0x19770369U, 0x641e4213U);
    R_SCE_func314(136+32);
    R_SCE_func100(0x97562bf0U, 0x4e966879U, 0x73bb6401U, 0xc8ea7174U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012e06e6U);
    R_SCE_func080();
    R_SCE_func100(0x2fa6101aU, 0x3eef4bb6U, 0x3ec58dfbU, 0x52d243b0U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(172);
    R_SCE_func100(0x80554a29U, 0xbac83d5eU, 0xa3e18209U, 0x51346e43U);
    R_SCE_func314(172+32);
    R_SCE_func100(0xc3424aa9U, 0x650486ebU, 0x85b67ffeU, 0x2c144f41U);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000049c1U;
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
    SCE->REG_100H = change_endian_long(0x0100abe1U);
    R_SCE_func080();
    R_SCE_func100(0x555c07d3U, 0x5622185aU, 0x6242cca1U, 0xce1345feU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(208);
    R_SCE_func100(0xd7ad59a8U, 0xbfc6dcafU, 0x90f394ebU, 0x637e4e40U);
    R_SCE_func314(208+32);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000a52U;
    for (iLoop = 0; iLoop < 128; iLoop = iLoop + 1)
    {
        R_SCE_func100(0x6ec8063dU, 0x22eb9ea5U, 0x9f6d07aeU, 0x8fab2affU);
        SCE->REG_24H = 0x040049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000149U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x060049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0400d0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02000149U;
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
        SCE->REG_100H = change_endian_long(0x019410dfU);
        R_SCE_func080();
        R_SCE_func100(0x8afbdd55U, 0x8b82f03cU, 0x1fa8fab3U, 0xe293d320U);
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func320(680);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010273a4U);
        R_SCE_func080();
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000015U;
        R_SCE_func320(716);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_ECH = 0x00002e40U;
        R_SCE_func101(0x318d1c4aU, 0x2eb21cf3U, 0xbc389f93U, 0x8dee3437U);
    }
    SCE->REG_ECH = 0x38008a40U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    R_SCE_func100(0x1776415eU, 0xa47b9dc0U, 0xe55c378dU, 0x8f9360e1U);
    SCE->REG_24H = 0x040049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x040019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x060049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0400d0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x020019a1U;
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
    SCE->REG_100H = change_endian_long(0x019410dfU);
    R_SCE_func080();
    R_SCE_func100(0x59d90514U, 0x07ceab5fU, 0x25b7f032U, 0xb6fe2a07U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    R_SCE_func080();
    R_SCE_func100(0x10b25a83U, 0xba221802U, 0x00f94ba4U, 0x5b582f2eU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    R_SCE_func320(716);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    R_SCE_func080();
    R_SCE_func100(0x1c7af639U, 0xb715e1e8U, 0x04cba709U, 0x44648b64U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(408);
    R_SCE_func100(0x388a7f76U, 0x1907bb17U, 0xe9688385U, 0x0e33ee71U);
    R_SCE_func314(408+32);
    R_SCE_func100(0x2f3e6a11U, 0x92b21123U, 0x9890bcabU, 0x22efd7dcU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    R_SCE_func080();
    R_SCE_func100(0xd5439bcaU, 0x1dfcdff3U, 0xf8a3c6e2U, 0x4b08c893U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(444);
    R_SCE_func100(0x639f523cU, 0x7f22c2aeU, 0x35b2dfdcU, 0xb7629597U);
    R_SCE_func314(444+32);
    R_SCE_func100(0x183f24f4U, 0x51672d5dU, 0xbe1aa4f9U, 0x5c631c4eU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    R_SCE_func080();
    R_SCE_func100(0x4c452484U, 0xd7cfec48U, 0xfc4979f4U, 0x5749b02cU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(544);
    R_SCE_func100(0x8d9fea97U, 0x8c7429feU, 0xb110c9ebU, 0x3a4bd5a5U);
    R_SCE_func314(544+32);
    R_SCE_func100(0xd02f485eU, 0xff4c069cU, 0xe2b919d1U, 0x7f54f343U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    R_SCE_func080();
    R_SCE_func100(0x0bfcc270U, 0x8a9ea7c0U, 0x67d45212U, 0x8bf4084cU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(580);
    R_SCE_func100(0x819d87b5U, 0xc2a94a8aU, 0x262f0072U, 0x28afab02U);
    R_SCE_func314(580+32);
    R_SCE_func100(0x28714cdeU, 0xee98a453U, 0xb4127422U, 0xe3c5faabU);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000049c1U;
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
    SCE->REG_100H = change_endian_long(0x010964eaU);
    R_SCE_func080();
    R_SCE_func100(0x0be5ab75U, 0x876af442U, 0x8cab5b07U, 0xd97c16d2U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(480);
    R_SCE_func100(0x9955ffc5U, 0x788a5c58U, 0x2dc38677U, 0x918d0bc3U);
    R_SCE_func314(480+32);
    R_SCE_func100(0x44caa811U, 0x693f746eU, 0xf086598eU, 0xddcc39f7U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    R_SCE_func080();
    R_SCE_func100(0x4b253f69U, 0x2e6d8306U, 0x980ff2faU, 0x32b41e2bU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(616);
    R_SCE_func100(0x41af8c4dU, 0x3d54687cU, 0x017cfc3eU, 0xe342e1ecU);
    R_SCE_func314(616+32);
    SCE->REG_ECH = 0x00000a52U;
    for (iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x0000b7a0U;
        SCE->REG_ECH = 0x000000f0U;
        R_SCE_func101(0x9b1ff368U, 0x4d24aca2U, 0x8a2921baU, 0x6e85a843U);
        R_SCE_func318();
        R_SCE_func100(0x81d9aff3U, 0x7367f41bU, 0x9984bacfU, 0xc03b1097U);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x011af8f9U);
        R_SCE_func080();
        R_SCE_func100(0x45c55453U, 0x937fcc24U, 0xf9641819U, 0x08a66517U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func319(408);
        R_SCE_func100(0xfdbce1dfU, 0x51695a47U, 0x716e460bU, 0xf5051005U);
        R_SCE_func314(408+32);
        R_SCE_func100(0xc5071c70U, 0x70927937U, 0x796a3d8bU, 0x96a6b537U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0130aeffU);
        R_SCE_func080();
        R_SCE_func100(0x835d0de8U, 0xec0c509bU, 0xa22176c7U, 0xd1a34c28U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000023U;
        R_SCE_func319(444);
        R_SCE_func100(0x890ec5c3U, 0x1d13c4a4U, 0xd1062b82U, 0x70ae5b5eU);
        R_SCE_func314(444+32);
        R_SCE_func100(0xb86747fdU, 0x6ef17382U, 0xd9bbb572U, 0xc4451452U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010964eaU);
        R_SCE_func080();
        R_SCE_func100(0x5b0cef20U, 0x5049f5cfU, 0x8ef92436U, 0x4a039351U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func319(480);
        R_SCE_func100(0x87d35587U, 0xc1846f2dU, 0xd29efed1U, 0xa1f22ea7U);
        R_SCE_func314(480+32);
        R_SCE_func100(0x3b9f198aU, 0xc82cedb5U, 0xbdff48e6U, 0x3b28799fU);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01574730U);
        R_SCE_func080();
        R_SCE_func100(0x0ac8ef5aU, 0x4dcb4f13U, 0xb920af68U, 0x892e4d61U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func319(544);
        R_SCE_func100(0xc44766f1U, 0xd92045ccU, 0xc72b724bU, 0xdc75527bU);
        R_SCE_func314(544+32);
        R_SCE_func100(0x47a32024U, 0x5e5c6264U, 0xabad0bf0U, 0x8bef0a8dU);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01f11123U);
        R_SCE_func080();
        R_SCE_func100(0xadaf2346U, 0x8b8cd487U, 0xef661c72U, 0xfba75a20U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000023U;
        R_SCE_func319(580);
        R_SCE_func100(0xbe3dd14fU, 0xe26b0965U, 0xd6023466U, 0x9d9bedd3U);
        R_SCE_func314(580+32);
        R_SCE_func100(0x59bccd45U, 0x61c1e417U, 0xe8015039U, 0xc3ef0fdeU);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01ac62c9U);
        R_SCE_func080();
        R_SCE_func100(0x9203fb89U, 0x4e066d76U, 0x1c201e78U, 0x2bedb566U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func319(616);
        R_SCE_func100(0xb6cf0cfdU, 0x1cbc0e56U, 0xb971023fU, 0xe7b05c43U);
        R_SCE_func314(616+32);
        SCE->REG_ECH = 0x00002e40U;
        R_SCE_func101(0x5560f6eeU, 0x27632186U, 0x0ef19804U, 0xb4018f81U);
    }
    SCE->REG_ECH = 0x38008a40U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f1U;
    R_SCE_func101(0xe5ce2b69U, 0x42ca9a52U, 0x4168e50eU, 0xf53e4bc9U);
    R_SCE_func318();
    R_SCE_func100(0x31338abbU, 0x54b02d89U, 0x60484eedU, 0x81edd3fdU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    R_SCE_func080();
    R_SCE_func100(0x3f87dcaeU, 0x4d0d13c8U, 0xce04b35aU, 0x1d18dfe0U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(408);
    R_SCE_func100(0xcb0c6b2dU, 0xa0238485U, 0x52437900U, 0x84f3223fU);
    R_SCE_func314(408+32);
    R_SCE_func100(0xb30570f7U, 0x550e5073U, 0x833895feU, 0x1f096b6aU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    R_SCE_func080();
    R_SCE_func100(0xec38ef60U, 0x905fbef5U, 0xfa4f292fU, 0xb4770a02U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(444);
    R_SCE_func100(0x6d7e5f89U, 0xe754abecU, 0xeb71227dU, 0x51a744dcU);
    R_SCE_func314(444+32);
    R_SCE_func100(0x38caef72U, 0x59315978U, 0x9c2df5b1U, 0x5d8c5881U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    R_SCE_func080();
    R_SCE_func100(0xd1b3702dU, 0x223bb42dU, 0xc707ca74U, 0xccd4be7bU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func319(480);
    R_SCE_func100(0x2b002e59U, 0x6564762eU, 0xa88743baU, 0x4d76e65eU);
    R_SCE_func314(480+32);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f2U;
    R_SCE_func101(0xab310cadU, 0x1a6dca44U, 0x97176702U, 0xfa7c0ff0U);
    R_SCE_func318();
    R_SCE_func100(0x7bb51f88U, 0x40a88938U, 0x74900bcaU, 0xc3e6d98dU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d34587U);
    R_SCE_func080();
    R_SCE_func100(0x46f636eaU, 0xae5727e9U, 0x17ad1439U, 0x7c106643U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(272);
    R_SCE_func100(0x244cf7a6U, 0x2f8e4941U, 0x84d900eeU, 0x835417eeU);
    R_SCE_func314(272+32);
    R_SCE_func100(0xabb3f445U, 0x029cfcbaU, 0x58ece236U, 0xc2b8ce24U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01315552U);
    R_SCE_func080();
    R_SCE_func100(0x2a3a3da1U, 0x35c62dadU, 0xb1091148U, 0xbf194399U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(308);
    R_SCE_func100(0x733b65c9U, 0xd4df45e5U, 0xa1f7a313U, 0xe2d839b7U);
    R_SCE_func314(308+32);
    R_SCE_func100(0x34569306U, 0x2c1f5275U, 0x1041511aU, 0x376aac73U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011a27dfU);
    R_SCE_func080();
    R_SCE_func100(0x2b2f00d7U, 0x4afe6c1bU, 0x50446006U, 0xfca93898U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func319(344);
    R_SCE_func100(0x3e2eb434U, 0xa39ea329U, 0x159ff237U, 0xb88019efU);
    R_SCE_func314(344+32);
    R_SCE_func100(0x3ac7452dU, 0x7a09e2aaU, 0x8db465ffU, 0x363be7e5U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    R_SCE_func080();
    R_SCE_func100(0x94fa60e7U, 0x9d459e0dU, 0x530f958bU, 0x5be9a16cU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(408);
    R_SCE_func100(0x11c507deU, 0xb21f112eU, 0xa8d75ec7U, 0x6c1073c7U);
    R_SCE_func314(408+32);
    R_SCE_func100(0x9899dcaeU, 0x20b54bb0U, 0xb3bcd7a3U, 0x1c6120e0U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    R_SCE_func080();
    R_SCE_func100(0x60e30c92U, 0x0c85d6d0U, 0xf2e9becdU, 0x2a727b4bU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(444);
    R_SCE_func100(0x93f0cef1U, 0xcd9397b5U, 0x859a25f2U, 0xdd0814d8U);
    R_SCE_func314(444+32);
    R_SCE_func100(0xbc9ff10cU, 0xbc2cf830U, 0xf76d73f9U, 0x1d7c91f4U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    R_SCE_func080();
    R_SCE_func100(0x2ed705bbU, 0xaba0d099U, 0x0e58d5bfU, 0x00b631daU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func319(480);
    R_SCE_func100(0xa54075aeU, 0xb4f2bb0eU, 0xb727972aU, 0x62d373e6U);
    R_SCE_func314(480+32);
    R_SCE_func100(0x525ca907U, 0x4dea3d68U, 0xca687068U, 0xfff525c5U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01fe1091U);
    R_SCE_func080();
    R_SCE_func100(0xb2b2a788U, 0xd5162840U, 0xe98d6baeU, 0x3d8887f4U);
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
    R_SCE_func100(0x47e414afU, 0xa3d215d7U, 0x5fd450f5U, 0xdaa9831aU);
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
    R_SCE_func100(0x5c073441U, 0xb1b7d0a4U, 0x54afdfe9U, 0x428aab6aU);
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
    R_SCE_func100(0x06fada7fU, 0x91d16c9dU, 0xc69c303aU, 0xf29e27c9U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(544);
    R_SCE_func100(0xf12eea57U, 0x9c7a9746U, 0x94ba172bU, 0x8a98a7f3U);
    R_SCE_func314(544+32);
    R_SCE_func100(0xcfb9e44eU, 0x67a00eccU, 0x9f4ab7daU, 0xb8155a69U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    R_SCE_func080();
    R_SCE_func100(0xf4ac2160U, 0xcce69e5cU, 0x4bf3f1f6U, 0x6874de45U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(580);
    R_SCE_func100(0x80cfd405U, 0x0d90d9b3U, 0x6f5bbb8cU, 0xc5208b78U);
    R_SCE_func314(580+32);
    R_SCE_func100(0x87a70014U, 0x2f1596f6U, 0xe10448d9U, 0xf177200fU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    R_SCE_func080();
    R_SCE_func100(0xf480cf8eU, 0x9865a7adU, 0x1cb9a0ccU, 0xb511e0acU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func319(616);
    R_SCE_func100(0x63ad7fd6U, 0x135155a2U, 0x5157be4dU, 0xd7467a88U);
    R_SCE_func314(616+32);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f3U;
    R_SCE_func101(0xef91da34U, 0x491d24c5U, 0xe1cb37c9U, 0x7822bc7fU);
    R_SCE_func318();
    R_SCE_func100(0x61374fa5U, 0xfba64b54U, 0x17a2bb60U, 0x64e10b2bU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01fe1091U);
    R_SCE_func080();
    R_SCE_func100(0xd36c8788U, 0x33f7fcefU, 0x4b3678e6U, 0x6d7ca149U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func319(0);
    R_SCE_func100(0x8f8db157U, 0x66a51e0fU, 0xf4ba03ebU, 0x3bc031e8U);
    R_SCE_func314(0+32);
    R_SCE_func100(0xbe1491d9U, 0x689fa1faU, 0x03c77f53U, 0x95f9dcbcU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019969f4U);
    R_SCE_func080();
    R_SCE_func100(0x2d7492eaU, 0x4b601209U, 0xbec2c501U, 0xdd80624cU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    R_SCE_func319(36);
    R_SCE_func100(0x8c75f085U, 0xdc06e331U, 0x7bb203adU, 0x2b28ab69U);
    R_SCE_func314(36+32);
    R_SCE_func100(0xf6ddd89eU, 0xa015673eU, 0x5c73b7caU, 0xa48d5a8eU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019de420U);
    R_SCE_func080();
    R_SCE_func100(0x0eb0c917U, 0xe78a5902U, 0x1988afe2U, 0x366b221dU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func319(72);
    R_SCE_func100(0x8ea1777aU, 0x5a8c56c5U, 0xa93e7fa8U, 0x4fc44a55U);
    R_SCE_func314(72+32);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func324.prc
***********************************************************************************************************************/
