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

void R_SCE_func311(void)
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
    R_SCE_func100(0x73528994U, 0x73843df3U, 0x788210e1U, 0xf7479a52U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000002cU;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
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
    SCE->REG_24H = 0x000040c1U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    R_SCE_func080();
    R_SCE_func100(0xda994b8aU, 0xd2235665U, 0x9b2cea4aU, 0xee2a57d1U);
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
    SCE->REG_24H = 0x00000581U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00210000U;
    oLoop1 = 1;
    while(oLoop1 == 1)
    {
        R_SCE_func100(0x6fdf6c08U, 0xa2722980U, 0x48fcacb7U, 0xad2aa6b2U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x534e0a0dU, 0x2a6da938U, 0xe0f8ce9dU, 0xfc414a50U);
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
            R_SCE_func101(0x32d40389U, 0xc8fe545bU, 0x7940e3a4U, 0x95763cb4U);
        }
    }
    R_SCE_func100(0x93fe9a76U, 0x91cfe05bU, 0x9527b0f2U, 0xa1687aeaU);
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016bcaa1U);
    R_SCE_func080();
    R_SCE_func100(0x99858efaU, 0x1f95d811U, 0x2a0efd63U, 0x0a7155a0U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(136);
    R_SCE_func100(0x40722065U, 0xdc14ea5cU, 0x56b8396bU, 0x701248dcU);
    R_SCE_func314(136+64);
    SCE->REG_24H = 0x000049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    R_SCE_func100(0xce0c5cabU, 0x08fc0f2dU, 0x7ab5caf9U, 0x7099eb64U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c85beU);
    R_SCE_func080();
    R_SCE_func100(0xc75c36c6U, 0x08bf7526U, 0xa0805931U, 0xf35c625fU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(204);
    R_SCE_func100(0x9b330478U, 0xbbe194d3U, 0x67fd1f35U, 0x6650c462U);
    R_SCE_func314(204+64);
    SCE->REG_24H = 0x000049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000a52U;
    for (iLoop = 0; iLoop < 256; iLoop = iLoop + 1)
    {
        R_SCE_func100(0xe1f04f65U, 0x8a0278bbU, 0xafa9eaceU, 0x0a473291U);
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
        SCE->REG_ECH = 0x00002e40U;
        R_SCE_func101(0x4eca043bU, 0x7bf6a009U, 0xff72fe5aU, 0x6c33e6a9U);
    }
    R_SCE_func100(0x9c0c4a3bU, 0x0b81844aU, 0xcc522fe2U, 0x40b55a7eU);
    SCE->REG_ECH = 0x38008a40U;
    SCE->REG_ECH = 0x00000100U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    R_SCE_func080();
    R_SCE_func100(0xc8fa73dcU, 0x13a1c885U, 0x3665eef1U, 0x757770acU);
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
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    R_SCE_func080();
    R_SCE_func100(0x0b7254e4U, 0xf5746033U, 0xeedc483cU, 0xefc2e8e6U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(408);
    R_SCE_func100(0x1a10c0a9U, 0x791abd27U, 0xa886a58fU, 0x45e8296bU);
    R_SCE_func314(408+64);
    R_SCE_func100(0xea326835U, 0x66be423cU, 0x53c01fefU, 0x1d06c555U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    R_SCE_func080();
    R_SCE_func100(0xb4422e59U, 0xe0ca3e46U, 0xbd31e2c1U, 0xb725d8aaU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(544);
    R_SCE_func100(0x656e0585U, 0x0558d20bU, 0x10a6cd2cU, 0xf7d20198U);
    R_SCE_func314(544+64);
    SCE->REG_24H = 0x000049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    R_SCE_func100(0x90252b1fU, 0x57108521U, 0xbf1c6553U, 0x6921810bU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    R_SCE_func080();
    R_SCE_func100(0x68e52833U, 0x99d2e2c2U, 0xd30409ddU, 0x48ea4ffcU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(476);
    R_SCE_func100(0x999f97cfU, 0xdcc7d5d8U, 0x74b11220U, 0x89c15bd6U);
    R_SCE_func314(476+64);
    R_SCE_func100(0x1ea20d50U, 0x0baeaea8U, 0x1ffc161aU, 0x60906c7eU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    R_SCE_func080();
    R_SCE_func100(0x5a3541d0U, 0xe4c243d7U, 0x72fa1d1dU, 0x8a8193b1U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(612);
    R_SCE_func100(0x4493349bU, 0xdffc6cefU, 0x5531c167U, 0xe783fc74U);
    R_SCE_func314(612+64);
    SCE->REG_ECH = 0x00000a52U;
    for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x00000085U;
        R_SCE_func101(0xd2fab61cU, 0x19e55020U, 0xbfd2c9cfU, 0xa138f98aU);
        R_SCE_func309();
        R_SCE_func100(0xfe6cc685U, 0xf2374263U, 0x7d4e35eaU, 0x54b68c15U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01a67f45U);
        R_SCE_func080();
        R_SCE_func100(0x861265b4U, 0x796577c1U, 0x0d8bfd62U, 0x8e34e848U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func313(476);
        R_SCE_func100(0x3e0a0580U, 0x5e233edaU, 0xc28a5e6aU, 0x47e8ac83U);
        R_SCE_func314(476+64);
        R_SCE_func100(0x3bd8e4c2U, 0x71b182fdU, 0x61503290U, 0x8a694105U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x019fce91U);
        R_SCE_func080();
        R_SCE_func100(0x11295d01U, 0xacd34627U, 0x6dfbfc6cU, 0x7b0910b6U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000020U;
        R_SCE_func313(612);
        R_SCE_func100(0xf536312eU, 0xef63f865U, 0xa6f9e409U, 0x125db8e1U);
        R_SCE_func314(612+64);
        R_SCE_func100(0xdadaf6e7U, 0x4cd299f0U, 0xf0bd3e4fU, 0xd47134b3U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x011f5dcdU);
        R_SCE_func080();
        R_SCE_func100(0xd1d2fc3bU, 0x821e77f4U, 0x1223e73bU, 0x9a3e45d7U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func313(408);
        R_SCE_func100(0xbbffc3baU, 0x4fcd1362U, 0xcb888c5cU, 0x64df995bU);
        R_SCE_func314(408+64);
        R_SCE_func100(0xdefbf735U, 0x0c1ef570U, 0x9c62c5a5U, 0x0ee26750U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01e59c3dU);
        R_SCE_func080();
        R_SCE_func100(0x39012b26U, 0xc601dd1fU, 0x959065f3U, 0x63387816U);
        SCE->REG_00H = 0x00012303U;
        SCE->REG_2CH = 0x00000022U;
        R_SCE_func313(544);
        R_SCE_func100(0xabcebe49U, 0x179c5fafU, 0xe662a18eU, 0xed98e35dU);
        R_SCE_func314(544+64);
        SCE->REG_ECH = 0x00002e40U;
        R_SCE_func101(0x0c93bb26U, 0xbf5f443dU, 0xbe68a205U, 0x75195beaU);
    }
    SCE->REG_ECH = 0x38008a40U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    R_SCE_func100(0x0d28278aU, 0x6a7e5e5cU, 0x72ed7be3U, 0x679800c1U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    R_SCE_func080();
    R_SCE_func100(0x5732c361U, 0xc468617aU, 0xa21f5955U, 0xf91d83beU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func313(476);
    R_SCE_func100(0x75f12e8bU, 0x5d7db927U, 0x622d4a34U, 0x455cf1b1U);
    R_SCE_func314(476+64);
    R_SCE_func100(0xa7b733b2U, 0x289d6efdU, 0x55acdc7aU, 0xad72dedaU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    R_SCE_func080();
    R_SCE_func100(0xc0606955U, 0x53025a57U, 0x2ba842ebU, 0xe1c79ca7U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(408);
    R_SCE_func100(0x3be2a735U, 0xcbd16da2U, 0x0938b594U, 0xdae27863U);
    R_SCE_func314(408+64);
    R_SCE_func100(0x908c1057U, 0x585ed4e4U, 0xc38508a7U, 0x46f60643U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0132d44bU);
    R_SCE_func080();
    R_SCE_func100(0x57131858U, 0x2ce8a582U, 0x296d4c16U, 0x39d08c82U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(68);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01432c7aU);
    R_SCE_func080();
    R_SCE_func100(0x84c0cd15U, 0x2b620dd4U, 0xf287e327U, 0x01072788U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(0);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    R_SCE_func080();
    R_SCE_func100(0x2d3fc6a3U, 0xc945cfa8U, 0xf1bdfd78U, 0x7d834f68U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func313(612);
    R_SCE_func100(0x00abad6bU, 0xe8eace98U, 0x9bbc0fa6U, 0x15bdea7dU);
    R_SCE_func314(612+64);
    R_SCE_func100(0x401f4023U, 0x1c42be4bU, 0x7205844fU, 0xccd09e1cU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    R_SCE_func080();
    R_SCE_func100(0xc3bc9b24U, 0x68c0800eU, 0xbb607b1eU, 0x3de7f2a1U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(544);
    R_SCE_func100(0x438adbc6U, 0x26cb7a4fU, 0xbbe48db0U, 0x8dcc8ce7U);
    R_SCE_func314(544+64);
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000086U;
    R_SCE_func101(0xc2bab545U, 0x4b633385U, 0x800a7901U, 0xfe430d39U);
    R_SCE_func309();
    R_SCE_func100(0x7569cd34U, 0x193e9b08U, 0x5bfba64aU, 0xb7275878U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0132d44bU);
    R_SCE_func080();
    R_SCE_func100(0xb93ceb35U, 0xab0f1a81U, 0x1afd42daU, 0x8f11e61aU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func313(68);
    R_SCE_func100(0x785ffadbU, 0x376e09bfU, 0xa3893c05U, 0x0bf8b1d1U);
    R_SCE_func314(68+64);
    R_SCE_func100(0x7f7c47b6U, 0x96812191U, 0xa6cbb794U, 0x7d92aa44U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01432c7aU);
    R_SCE_func080();
    R_SCE_func100(0xe3bf1a4eU, 0xea987511U, 0x61b1a8d9U, 0x8f86988bU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(0);
    R_SCE_func100(0x2fb432eaU, 0x28b2a2eeU, 0x25691e4aU, 0x2940a60cU);
    R_SCE_func314(0+64);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000002cU;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func311.prc
***********************************************************************************************************************/
