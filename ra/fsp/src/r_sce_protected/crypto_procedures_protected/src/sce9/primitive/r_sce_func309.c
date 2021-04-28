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

void R_SCE_func309(void)
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
    R_SCE_func100(0xc9497620U, 0x866c5700U, 0xfeb665d0U, 0x22c9a6bbU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000028U;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000b7bU;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    R_SCE_func080();
    R_SCE_func100(0x056065a2U, 0x12ea8a76U, 0x1368ce4aU, 0x2a3de50eU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(476);
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(612);
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000090U;
    R_SCE_func101(0x4ac0cb7eU, 0x5aaad032U, 0x5bd81569U, 0xa9240905U);
    R_SCE_func308();
    R_SCE_func100(0x65a81509U, 0x2f80ad84U, 0xa9ce0862U, 0xa8b16e2cU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x00003fbeU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    R_SCE_func080();
    R_SCE_func100(0xc3978dfaU, 0xd86edae6U, 0x7801300eU, 0x85190f12U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func313(884);
    R_SCE_func100(0xeb9204ccU, 0xe1ff0601U, 0x8d356106U, 0x2ddac834U);
    R_SCE_func314(884+64);
    R_SCE_func100(0x90ae1312U, 0xd76c960aU, 0x66422980U, 0x25eb51fcU);
    SCE->REG_ECH = 0x3000db72U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d770U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_24H = 0x0000d0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    R_SCE_func100(0x8998d772U, 0xeeba55e7U, 0xf1b97798U, 0xf3db04d2U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func313(816);
    R_SCE_func100(0xe03a23fbU, 0x0502d76fU, 0xa5e303abU, 0x8ab8c5eaU);
    R_SCE_func314(816+64);
    R_SCE_func100(0xa1171a4fU, 0x6503528fU, 0x1bec2a37U, 0xf3188f78U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x000000a0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04000991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    R_SCE_func080();
    R_SCE_func100(0x312d693eU, 0x885b4cbdU, 0xdf5f1540U, 0xf3862899U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(952);
    R_SCE_func100(0x653e2156U, 0xa4a401d3U, 0x25fce12cU, 0xeb50b072U);
    R_SCE_func314(952+64);
    R_SCE_func100(0xc4f3d006U, 0x40d182c0U, 0x006bd509U, 0xa755cb36U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    R_SCE_func080();
    R_SCE_func100(0x15efd281U, 0xfb20a67fU, 0x0f5b7093U, 0x61aa8c45U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(544);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    R_SCE_func080();
    R_SCE_func100(0x3e72a381U, 0x9588b4feU, 0x9e492c5fU, 0xa38f8108U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(612);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    R_SCE_func080();
    R_SCE_func100(0x8d2e52e0U, 0x1300f0a1U, 0xda2e4d6eU, 0x0d1b5c12U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(408);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(476);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_34H = 0x00000008U;
    SCE->REG_24H = 0x800011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000000cU;
    SCE->REG_24H = 0x82001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000028U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000091U;
    R_SCE_func101(0x9772fa14U, 0xe01b0b89U, 0x94b1a65dU, 0x7d0de12aU);
    R_SCE_func308();
    R_SCE_func100(0x2ba1c177U, 0xbbd9c4f5U, 0x8e516c93U, 0x06216eccU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x56980b36U, 0x6aec4eb5U, 0x721341eaU, 0xf44ae362U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0x846ef339U, 0x3d5ab58bU, 0xdd143b7aU, 0x534890b9U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x17b1fe6dU, 0xef4daec6U, 0xca3f81caU, 0x14101586U);
    }
    R_SCE_func100(0x917cfba7U, 0xe14936dfU, 0x9a334628U, 0x450a93b7U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    R_SCE_func100(0xee68ca77U, 0xdd0fc4f1U, 0xb512c047U, 0x7da75dfeU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(816);
    R_SCE_func100(0x2c598c56U, 0x22b2e36cU, 0x153ed168U, 0x7bae1f6dU);
    R_SCE_func314(816+64);
    R_SCE_func100(0xeb0c65d8U, 0xee968b4cU, 0xf4864fcaU, 0x227e7684U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(952);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x3800db71U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xbbefa963U, 0x4616e5dcU, 0x6f84cd1eU, 0x9c882529U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0xafcac712U, 0x13cf3623U, 0x7f68142aU, 0x782923cfU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x08d18960U, 0xe3f8f928U, 0xecf93710U, 0x3f8a09eeU);
    }
    R_SCE_func100(0xbf6e7fa5U, 0xa933fa11U, 0x76309954U, 0xa1a7b56eU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    R_SCE_func080();
    R_SCE_func100(0xd34d10fdU, 0xf14c7ec4U, 0x2878fd42U, 0x3d896fe4U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(952);
    R_SCE_func100(0xb4d3a326U, 0x84c7f992U, 0x2ab3997dU, 0x1a345d87U);
    R_SCE_func314(952+64);
    R_SCE_func100(0x6990032dU, 0x2c1bef62U, 0x1d9cf13eU, 0x245b1835U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    R_SCE_func080();
    R_SCE_func100(0xa80ff0adU, 0x2417fcd2U, 0x2bd6d6adU, 0xa670e68aU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(408);
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    R_SCE_func080();
    R_SCE_func100(0x60e11786U, 0xaa724960U, 0x9491d91fU, 0xb1985116U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(544);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(680);
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000092U;
    R_SCE_func101(0x6b69288eU, 0xd1ecfcbaU, 0x82e19566U, 0x6b62af3aU);
    R_SCE_func304();
    R_SCE_func100(0x368d2f14U, 0x93f1d277U, 0x8ccd8026U, 0x3381bbe1U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xdaff94beU, 0x192a36deU, 0x8d68cf48U, 0x67aa70e2U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000190U);
        R_SCE_func101(0x0848476eU, 0xc735ae41U, 0x0f65a3a1U, 0x18236a1dU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x129e0c32U, 0x33d5181bU, 0xbd152f92U, 0x83634ab8U);
    }
    R_SCE_func100(0xaf945a08U, 0x76e6d0a6U, 0x0b951159U, 0xf4386352U);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    R_SCE_func100(0xba2ae63aU, 0xa6539f83U, 0xd13eeb08U, 0x3e02c748U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(816);
    R_SCE_func100(0x05c8ab2cU, 0xcfbfe041U, 0x93ef8646U, 0x773d783eU);
    R_SCE_func314(816+64);
    R_SCE_func100(0xb223ce42U, 0xcff4a48fU, 0xeb4798baU, 0x805894ceU);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(952);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x3800db71U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x723e4f09U, 0x6fe3bf6bU, 0xbbd40e45U, 0xd08992d8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0xc7c45474U, 0x19983a69U, 0xbc067586U, 0x5305214fU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x324eb05dU, 0x917ab405U, 0xa787dd7dU, 0x49538a46U);
    }
    R_SCE_func100(0xd98570c9U, 0xa8db5ad0U, 0xd5bd3aa6U, 0x732a9600U);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    R_SCE_func080();
    R_SCE_func100(0xf4f0c4e2U, 0x43c34df9U, 0x28054165U, 0x0c25de26U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(952);
    R_SCE_func100(0xc7ba66bcU, 0x97b26d5cU, 0x2d755917U, 0xf73639ecU);
    R_SCE_func314(952+64);
    R_SCE_func100(0x85d722b0U, 0xa94023feU, 0x3b8520b9U, 0xdeac91eeU);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_ECH = 0x00003b9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x3000db68U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37aU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(748);
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000093U;
    R_SCE_func101(0x93c64f76U, 0xe68789b5U, 0xab51aa7aU, 0xb21bbb14U);
    R_SCE_func308();
    R_SCE_func100(0x57bd6f00U, 0x0c886102U, 0xdfefc085U, 0xa5ca49a2U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(884);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x9305ae89U, 0xe37db1d8U, 0x251ed0dfU, 0x77ff28d7U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000190U);
        R_SCE_func101(0xa20706e1U, 0xfa887457U, 0x77852390U, 0xa67a3c3eU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0xc786ca2fU, 0xaa1706d3U, 0x27f0b69bU, 0x96b1c95cU);
    }
    R_SCE_func100(0x4595af69U, 0x8e586200U, 0xf24564d6U, 0x4f1039f1U);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d370U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d770U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    R_SCE_func080();
    R_SCE_func100(0xfd730458U, 0xc8fe8c44U, 0x844467b4U, 0x150b4fceU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(884);
    R_SCE_func100(0xe0255f01U, 0xf11d3b68U, 0x50a7fef5U, 0xbc4c6830U);
    R_SCE_func314(884+64);
    R_SCE_func100(0x1120981aU, 0x498f9ad7U, 0x4f5df720U, 0x9ef9c90cU);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xaf1b3f51U, 0xc407883fU, 0x5d58d23fU, 0x2530c593U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0xb428bd01U, 0x64d98544U, 0x6a7f0124U, 0x2859e5c4U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0xc1e2626bU, 0xb973e6f7U, 0xd82fe9b1U, 0xd14b7268U);
    }
    R_SCE_func100(0xee4fa77fU, 0xbb5880cfU, 0x40c5cc5aU, 0x908892d7U);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    R_SCE_func100(0x5cd4ea6aU, 0x3176e314U, 0x859d405fU, 0x2d0a1068U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(816);
    R_SCE_func100(0x99468bc5U, 0x961dccd5U, 0xa6dd6826U, 0xcbeae596U);
    R_SCE_func314(816+64);
    R_SCE_func100(0xe76d23deU, 0x7934ce14U, 0x247368e4U, 0x0a0045efU);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(952);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x3800db71U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x944114f4U, 0xda6fcbc3U, 0xc5e68002U, 0xe3dbdef8U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0x04b0a7b2U, 0xd52949b2U, 0x247774efU, 0x5cd2539aU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0xb042a7b6U, 0xa96d1895U, 0xd18dd35fU, 0xbf086bffU);
    }
    R_SCE_func100(0x755e79feU, 0x7cfa4788U, 0xa1fb3f6aU, 0xe4ee11b9U);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x00003b9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_ECH = 0x3000db71U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37aU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000581U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(680);
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000094U;
    R_SCE_func101(0x76e2fda6U, 0x0de14033U, 0xe3bbccb0U, 0x6cdee050U);
    R_SCE_func304();
    R_SCE_func100(0xe49c519cU, 0x97153a06U, 0xcb96ad65U, 0x2fd3f2a8U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x9849bd95U, 0x48605585U, 0xc68e82e2U, 0x330655fdU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0x2489efffU, 0x1b079a46U, 0xe92655c0U, 0xf593ef9fU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0xa1bf1379U, 0xeb0a8be9U, 0x21f7462dU, 0x374525bcU);
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x7dffb181U, 0x763fc10eU, 0xe633a50aU, 0x95617badU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000190U);
        R_SCE_func101(0xb58dc8f7U, 0x9bc95df4U, 0xf02bf893U, 0xd97d9ff9U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x827589d1U, 0x85dbfdfdU, 0x3a05e242U, 0xa86ae06dU);
    }
    R_SCE_func100(0x6a56d422U, 0xe3225b60U, 0x5ea7e3f1U, 0x36f4ee8bU);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    R_SCE_func100(0x57395970U, 0xc884887fU, 0xa3fda2e3U, 0x5e5404e3U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(816);
    R_SCE_func100(0x20b18da3U, 0xec8ce86eU, 0xee70ef5bU, 0x349f8bcdU);
    R_SCE_func314(816+64);
    R_SCE_func100(0xb4a186f3U, 0x41ec7aa9U, 0xee9975b9U, 0xc3a09f57U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_ECH = 0x00003b9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x3000db68U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37aU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(748);
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000095U;
    R_SCE_func101(0x18dc12dcU, 0xfedf4fadU, 0x38eaa911U, 0xbd76a830U);
    R_SCE_func308();
    R_SCE_func100(0x35a1d788U, 0xb3dae31bU, 0x5b837588U, 0x3b6109deU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000c8d0U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xa952f5b3U, 0x10a39d4fU, 0x44932a05U, 0xc6b012b5U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0xb329a1d4U, 0xcae5801dU, 0x5a9b2cf9U, 0x775981dcU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x19c1eae7U, 0xf124c7dfU, 0x21674703U, 0xb2fcdc21U);
    }
    R_SCE_func100(0x68dd0067U, 0x1397966aU, 0x18ccd0b1U, 0x9d2988dbU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(884);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x3800db70U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xa6a51a04U, 0xabed4cb9U, 0xe6280cc9U, 0xf61c86ebU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000110U);
        R_SCE_func101(0x58ccd2fcU, 0xe601b4d5U, 0x8ecb4b3cU, 0x63947123U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x3bdfd0abU, 0x993a3658U, 0x19fd9437U, 0xdaecb896U);
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xf8718155U, 0x69adcb54U, 0x390bb37bU, 0x1088effdU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000190U);
        R_SCE_func101(0xe5bb3db2U, 0x3d85e004U, 0x02cebd78U, 0x132d6343U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0xd1c12944U, 0x4004e6e0U, 0x307b0af9U, 0xa7b4d853U);
    }
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xb2e76836U, 0xda1ba345U, 0x556ef2c8U, 0x5f571763U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001U;
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x04000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001U;
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x00000030U;
        SCE->REG_E0H = 0x8088001eU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000024U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x0000000cU;
        SCE->REG_ECH = 0x00003b9eU;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x0000004cU;
        SCE->REG_ECH = 0x00003f9eU;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x00000030U;
        SCE->REG_E0H = 0x8188001eU;
        SCE->REG_00H = 0x00003823U;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_28H = 0x00800001U;
        SCE->REG_104H = 0x00000257U;
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001U);
        SCE->REG_2CH = 0x00000190U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xFFFFFFFFU);
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x2f82caadU, 0x7a1f23b5U, 0x6bda5545U, 0xaa3483e9U);
    }
    else
    {
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x121eb339U, 0x6a675b8dU, 0x0377749aU, 0x98d7ab8aU);
    }
    R_SCE_func100(0x7bc076d8U, 0x3190ba23U, 0x0ea9c00dU, 0x04a12dd9U);
    SCE->REG_24H = 0x000009c0U;
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
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d37eU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000020U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x000011c0U;
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
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    R_SCE_func080();
    R_SCE_func100(0xfd22029aU, 0x9186349aU, 0x1dc3a93aU, 0x13fe01baU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(748);
    SCE->REG_ECH = 0x3800db7eU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x14897332U, 0xefb8f2bdU, 0xde971716U, 0x795bdc4eU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000000a0U;
        SCE->REG_E0H = 0x80c0001eU;
        SCE->REG_00H = 0x00018303U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000049c1U;
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
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        SCE->REG_24H = 0x000049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000000a0U;
        SCE->REG_E0H = 0x81c0001eU;
        SCE->REG_00H = 0x00013803U;
        SCE->REG_2CH = 0x00000012U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            R_SCE_func100(0x9e0141c8U, 0xa5964252U, 0xd5fc56cdU, 0x45a5bc93U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x04001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x06001181U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x80c0001eU;
                SCE->REG_00H = 0x00018303U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x000000a0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_28H = 0x00800001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_104H = 0x00000157U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000001U);
                SCE->REG_E0H = 0x8181001eU;
                SCE->REG_00H = 0x00003807U;
                SCE->REG_2CH = 0x00000110U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_24H = 0x000001c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000400U;
                SCE->REG_24H = 0x800080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001181U;
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
                SCE->REG_E0H = 0x8081001eU;
                SCE->REG_00H = 0x00008307U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_1CH = 0x00210000U;
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000090U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x81c0001eU;
                SCE->REG_00H = 0x00013803U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                R_SCE_func101(0xee699b8aU, 0x2584d6b5U, 0x82dad7a8U, 0x1b259d57U);
            }
            else
            {
                R_SCE_func101(0x2e3dfe53U, 0x1edd9cecU, 0x16936127U, 0xf9439d41U);
                oLoop1 = 0;
            }
        }
        R_SCE_func101(0x1932fa92U, 0xd379a7d0U, 0xb4088718U, 0x8edb462aU);
    }
    else
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x80c0001eU;
            SCE->REG_00H = 0x00018303U;
            SCE->REG_2CH = 0x00000022U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x81c0001eU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000012U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x80c0001eU;
            SCE->REG_00H = 0x00018303U;
            SCE->REG_2CH = 0x00000022U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x06001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x81c0001eU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000012U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x80c0001eU;
            SCE->REG_00H = 0x00018303U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000050U;
            SCE->REG_E0H = 0x8088001eU;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000070U;
            SCE->REG_E0H = 0x8088001eU;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x000000a0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_28H = 0x00800001U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_E0H = 0x8181001eU;
            SCE->REG_00H = 0x00003807U;
            SCE->REG_2CH = 0x00000090U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
            SCE->REG_34H = 0x00000004U;
            SCE->REG_24H = 0x800011c0U;
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
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_1CH = 0x00210000U;
            SCE->REG_28H = 0x00870001U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000050U;
            SCE->REG_E0H = 0x8188001eU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000070U;
            SCE->REG_E0H = 0x8188001eU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000090U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x81c0001eU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0xd334a49cU, 0x58a841f6U, 0xc819bbfeU, 0x6bd1b9f7U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func101(0x43b973a6U, 0x021cb33aU, 0x041fe7baU, 0x7a896230U);
                oLoop1 = 0;
            }
            else
            {
                SCE->REG_24H = 0x04001991U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x06001191U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x80c0001eU;
                SCE->REG_00H = 0x00018303U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x000000a0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_28H = 0x00800001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_104H = 0x00000157U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000001U);
                SCE->REG_E0H = 0x8181001eU;
                SCE->REG_00H = 0x00003807U;
                SCE->REG_2CH = 0x00000110U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_24H = 0x000001c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000400U;
                SCE->REG_24H = 0x800080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001191U;
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
                SCE->REG_E0H = 0x8081001eU;
                SCE->REG_00H = 0x00008307U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000090U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x81c0001eU;
                SCE->REG_00H = 0x00013803U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                R_SCE_func101(0x403817d6U, 0x80059b03U, 0xbed534dcU, 0x1b72170aU);
            }
        }
        R_SCE_func101(0xb9cdfcb5U, 0x50c5e00cU, 0xe277d5e3U, 0x6ccef386U);
    }
    SCE->REG_24H = 0x000088d0U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000028U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func309.prc
***********************************************************************************************************************/
