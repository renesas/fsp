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

void HW_SCE_p_func318(void)
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
    SCE->REG_ECH = 0x00000008u;
    SCE->REG_ECH = 0x00003fbeu;
    HW_SCE_p_func100(0x8c693a67u, 0xb13f66fbu, 0xa25ea81bu, 0x560d7c20u);
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
    HW_SCE_p_func100(0x2074e03cu, 0x98ab4303u, 0xc1cce9b5u, 0xd43ba3ebu);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000015u;
    HW_SCE_p_func320(480);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf51ada8u, 0x1fc04491u, 0xc988fb18u, 0xfaa5c11du);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func320(616);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0dfaa529u, 0x282e920du, 0xf64592dfu, 0x9f7c68adu);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func320(444);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9c1a0702u, 0xedb2e972u, 0x22852fd3u, 0x1855837cu);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(580);
    HW_SCE_p_func323();
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x38d4cc3du, 0xce4e1aa8u, 0x561920b3u, 0x7adf0eb5u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x452bbfd4u, 0x121cc6aau, 0xbd3daaf0u, 0xedaf7d58u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x45fea76au, 0x2c6eb1dcu, 0xe2b278ceu, 0x6e651334u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa434e2acu, 0x846c8258u, 0x9bafbdf5u, 0xc50a1cf7u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0x451158f5u, 0x81c038e1u, 0x097a63bbu, 0xe2348aedu);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x65dae8bdu, 0x14d558ceu, 0x16b8aafcu, 0x6bd59a86u);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x00005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0u;
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
    SCE->REG_100H = change_endian_long(0x011af8f9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x050df3ffu, 0x4aecfa26u, 0x639cc9a9u, 0xc359e623u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000015u;
    HW_SCE_p_func320(408);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf1362f19u, 0x84c03fcfu, 0xb31f41a3u, 0x709874b2u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func320(544);
    HW_SCE_p_func323();
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0266126au, 0x5478a930u, 0x489ca55cu, 0x04eecab0u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xedb8ae49u, 0xbfdb28e5u, 0x05f80921u, 0xc430a4acu);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x8b69697du, 0x2c955d96u, 0x8ceae065u, 0x540a0614u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xea10d2f9u, 0xa280b4beu, 0x3834e872u, 0x0458f807u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x934fc829u, 0x8913448fu, 0x5fda9cfeu, 0x8343d6e1u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x83a90bf3u, 0xb6654be1u, 0xe1dbfccau, 0xf7375c69u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x9536bf06u, 0x9ecd622au, 0xd94cdfbcu, 0xf5391467u);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x00005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0u;
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
    SCE->REG_100H = change_endian_long(0x0130aeffu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x74787d02u, 0x0c72fbacu, 0xd30f6441u, 0x26867c12u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000015u;
    HW_SCE_p_func320(444);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc61ecfffu, 0xa9953287u, 0xb4500ebfu, 0xd34162e6u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func320(580);
    HW_SCE_p_func323();
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x51aedde7u, 0x9413ad77u, 0xec2342bbu, 0xa4a9cbecu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0xf03ed4f3u, 0x5745c781u, 0x0b42d870u, 0x0c7db3cbu);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0x5674c372u, 0x77e8dea9u, 0x5a55452au, 0xab9bb69du);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x70b5c05cu, 0x8660d602u, 0xd1c971cbu, 0x76e117c1u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2c5ddd9cu, 0x9b4b818au, 0x1977f83du, 0x1f6e88f4u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000020u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x10413e6au, 0x338ea4acu, 0x559a535au, 0x0e97cb42u);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0xc8d87a13u, 0x28ba25bdu, 0x4ece54ccu, 0x3d697361u);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x00005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x000060d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x52ffcbfbu, 0x25c68561u, 0x0eeed611u, 0x9cf5088du);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2114e727u, 0x4d307b50u, 0x94f1eb46u, 0xa38d9ce8u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0x09bae1beu, 0xd3e14145u, 0x7d2ba63fu, 0x23c194deu);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x05752256u, 0x4096e871u, 0xafb2d8f2u, 0x9810e5c7u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2ec33011u, 0xbcb2710eu, 0xc81ed862u, 0x457fdff6u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf2131abu, 0xab0a83eau, 0x7065e26cu, 0xcd6c7bcdu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x1c4648e5u, 0x3a746a56u, 0x40a6b1c3u, 0x8b198efeu);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x413a569au, 0x477e2227u, 0xcb5e412du, 0x020d1af2u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5571223au, 0xb8e696adu, 0xa27da0c5u, 0xa0de4e32u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4b3715c5u, 0x62ff3f7bu, 0xc93b1343u, 0x9e7c130au);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x21fecf08u, 0xc8e1e918u, 0x8addf0e1u, 0x930bd727u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0xae7ec822u, 0x07a1ce62u, 0x55ae5ea0u, 0x5cf840acu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xde7eba77u, 0x66ec29ebu, 0x09990687u, 0x799c56eeu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(952);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0b4fe097u, 0xc820684du, 0x02412687u, 0x6e212565u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0x395026a9u, 0x6c42a3fbu, 0x07b2fd77u, 0x2c39ed94u);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0x2cbbbb51u, 0xb5c1b6d5u, 0x83276d22u, 0x0c8a2248u);
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
    HW_SCE_p_func100(0xaaaa7ac4u, 0xfb5bed0eu, 0x8be2cb55u, 0xe7fd0473u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func320(480);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x31ff55c9u, 0x8140b0f5u, 0xceb9a311u, 0xf8a6f300u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(616);
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x000060d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_24H = 0x0000c8d0u;
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
    SCE->REG_100H = change_endian_long(0x01d3c420u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xacaeb6e8u, 0xd069eaffu, 0xfd178003u, 0xc18b9d75u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(896);
    HW_SCE_p_func100(0xbf3b464fu, 0x49a9553fu, 0xc387c770u, 0xc7f9b17du);
    HW_SCE_p_func314(896+36);
    HW_SCE_p_func100(0x1f7f68abu, 0x91a1a4efu, 0x664851deu, 0x26452beeu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x726ceea7u, 0xbde2b6e5u, 0xe19911d3u, 0xecccacfeu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa17ed11eu, 0x2ef17845u, 0x267746bfu, 0xb3fd52dfu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xfc753a2bu, 0xf34825afu, 0x03876e89u, 0x51b76719u);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0xf3047cc0u, 0x32c7c135u, 0x77bbf376u, 0xe4c5bdcau);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x61da3608u, 0x2332ad99u, 0x3f516d34u, 0xcd2305dfu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc8e8a814u, 0x05a35651u, 0xaca24a7fu, 0x0ea729fau);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x1dde4b25u, 0x530e5bb0u, 0xc5becf97u, 0x35b81685u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x27d54b6du, 0xeefed33fu, 0xc73bc03bu, 0xd427373du);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa900c2c0u, 0x602b64dcu, 0x5d44f94bu, 0x4fe44840u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xaf0d3c1cu, 0x50563233u, 0xe2b291b6u, 0xe0e17dd0u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xbea9c41cu, 0x79c109f4u, 0xc1a7ff55u, 0xcadfd250u);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x647ca49eu, 0xb06921a5u, 0xe84a252du, 0xc598c5a4u);
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
    HW_SCE_p_func100(0x91c27ea4u, 0x049f5f5au, 0xc129ce0cu, 0x64a8e27bu);
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
    SCE->REG_100H = change_endian_long(0x011af8f9u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xd55a5390u, 0x35f33131u, 0xd6a62829u, 0x7d2fa738u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func320(408);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(544);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x000060d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f0u;
    HW_SCE_p_func101(0x5b38f724u, 0xe9aa7946u, 0xa88a1bbfu, 0x4d8a1c23u);
    HW_SCE_p_func316();
    HW_SCE_p_func100(0xe81e581cu, 0x1b609ef3u, 0x346419fdu, 0x8a3fe878u);
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa1941a0eu, 0xcdcde287u, 0x1b756ae4u, 0xe9bdb894u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xea1c0bbdu, 0x9ae71488u, 0xfa0a43b3u, 0xa5729ea2u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x066e4ff9u, 0xf8dbab9fu, 0xafc2b53au, 0xf9846ca7u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x692d67d5u, 0xe8de307bu, 0xcb829d7fu, 0x92fe6f5cu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc1fc96f6u, 0x295eac95u, 0x7352e482u, 0x21ae2cb1u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(952);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1b397203u, 0xf394d796u, 0x8b40b8a1u, 0x7c0e538eu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0x0f0d9326u, 0x089c4bf1u, 0x39dc51eau, 0x3703a5acu);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0xa124c08bu, 0xc2ecaa23u, 0x531ca0f3u, 0x40c3e724u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4b859310u, 0x0b9fd51fu, 0xf76e1dc8u, 0xff37911eu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5372057au, 0xf005e4a0u, 0x4dbb9b05u, 0xa278ffb8u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x80f4b23du, 0x05c58c40u, 0x4e36b493u, 0xb12e2146u);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x69e11c7fu, 0x60427693u, 0x38ce5d4cu, 0x8be945a7u);
    SCE->REG_28H = 0x008f0001u;
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x800070d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000408u;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cu;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00u;
    SCE->REG_24H = 0x8000f4d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_24H = 0x000050d0u;
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
    SCE->REG_100H = change_endian_long(0x018e0c4cu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb76505f2u, 0xebf3eb95u, 0x4fa359a1u, 0x04a325bbu);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000003u;
    SCE->REG_24H = 0x800068d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x287e45eeu, 0xeb5626adu, 0x449bc603u, 0xf05aa3fau);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(896);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01d3c420u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xeb481312u, 0x27c8327du, 0x7f4519acu, 0xde7645abu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(896);
    HW_SCE_p_func100(0x7feadcc7u, 0x4d7648c9u, 0xa9f88d13u, 0xbb0d7a6fu);
    HW_SCE_p_func314(896+36);
    HW_SCE_p_func100(0xc2684d93u, 0x6d5d6e62u, 0x909d3383u, 0x31c612e1u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe5b4cae5u, 0xbcfc9e35u, 0x66ccaeedu, 0x09b575afu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe7e196efu, 0x8bda93e4u, 0x06cfe5f7u, 0x42a9bdfeu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xb8a0f1b1u, 0x10d2babbu, 0xe39d0053u, 0xca6a2be4u);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0xc8bff03bu, 0x822949adu, 0x1d0275c3u, 0x66aa2304u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xd088dc87u, 0x1e079d65u, 0x58f71342u, 0xfe73372eu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6a449ba3u, 0x644592a8u, 0xe4c0d031u, 0x0111d512u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x136d4dceu, 0x8829fe81u, 0xe1fdab6cu, 0x90d661c3u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0xdd6d1badu, 0x3f4fd94fu, 0x17bb48e3u, 0x7955ea13u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x47c671eeu, 0xac239171u, 0x21208ac1u, 0x6f45b650u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x89c44f64u, 0xcbc5e25au, 0x5f99f504u, 0x071f488eu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x79a12141u, 0x224ee8dcu, 0x5ab33560u, 0xc20b192au);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x81c4a87bu, 0xe2676d1du, 0xbac0211au, 0x5ff29039u);
    SCE->REG_28H = 0x008f0001u;
    SCE->REG_34H = 0x00000002u;
    SCE->REG_24H = 0x80004cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000810u;
    SCE->REG_24H = 0x80005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20u;
    SCE->REG_24H = 0x80005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030u;
    SCE->REG_24H = 0x80007cd0u;
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
    SCE->REG_100H = change_endian_long(0x010273a4u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe1c00d44u, 0xa3b1d245u, 0x3379eef5u, 0xa7a32ecdu);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000003u;
    SCE->REG_24H = 0x800068d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x7e4caf6cu, 0xd26d5b9cu, 0x2009e623u, 0xd5135784u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcec6776eu, 0x068afdfbu, 0x5b95a84bu, 0x37dea6cdu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0x5bb04bc7u, 0x40307f33u, 0x4438611cu, 0xce77ef4cu);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0xc23e5bffu, 0x3ff2f682u, 0x86ffb501u, 0x4b33968bu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe6aa096du, 0xd2c44e40u, 0x4bd7380eu, 0x1ee64b02u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x66651932u, 0xdd1276c0u, 0xcb505742u, 0xa96b774au);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0xc92bb4b8u, 0x3ec1b9beu, 0x6e7c1b1fu, 0x55983590u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x96245bd7u, 0x56105797u, 0x13f7872cu, 0xe823d68du);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf5e906f9u, 0x44bb39adu, 0xd0519e29u, 0x7475f442u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(952);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x06aff7d1u, 0x18aea6c8u, 0x86f229c2u, 0xf0e58cddu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0x68d7ffdbu, 0x48eebde8u, 0x65c5ae8bu, 0xfcd43c74u);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0x58880bd1u, 0xa03cce13u, 0x5cb152e7u, 0x54ed01dbu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbeb6df12u, 0xb51f6599u, 0x04dd5c6du, 0xf91a1791u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x25cafafeu, 0x8c3c0489u, 0x66ca83ffu, 0xd6d66e08u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x1f46ab53u, 0x124cc60cu, 0x8ad45ce5u, 0x7fb59dd1u);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x9b79a0f6u, 0xcb67c0b6u, 0xa3a3e1b3u, 0xd73496bbu);
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
    HW_SCE_p_func100(0x6e0e8a8au, 0x6b6b1bf9u, 0xb4b8663bu, 0x628bad41u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func320(680);
    SCE->REG_24H = 0x000084d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func322(952);
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f1u;
    HW_SCE_p_func101(0x95bda937u, 0x8aa1ebf4u, 0x011ebbfbu, 0xc72e05a2u);
    HW_SCE_p_func316();
    HW_SCE_p_func100(0xd5706a1cu, 0x9efead44u, 0x8624f1b4u, 0xe4ed91eeu);
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf27d42d7u, 0x9aebe897u, 0xa4bf4ed6u, 0xea904263u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x7b35e1c2u, 0x376987cdu, 0xffea7a71u, 0xfa1ff3f6u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xcc82736au, 0x582bd5fau, 0x3a5ab3c7u, 0x73c1f935u);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0xc3892749u, 0x72d1a0c4u, 0x4bbe56d8u, 0x16968510u);
    SCE->REG_28H = 0x008f0001u;
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x800070d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000408u;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cu;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00u;
    SCE->REG_24H = 0x8000f4d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_24H = 0x000050d0u;
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
    SCE->REG_100H = change_endian_long(0x018e0c4cu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1e9fc4b4u, 0xa5142e28u, 0x2f8d26a5u, 0xf5e585f3u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000003u;
    SCE->REG_24H = 0x800068d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x48326af2u, 0x44f85d94u, 0x71fcc7abu, 0xb1d54290u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1c1d2aacu, 0xee5bfa48u, 0x15543797u, 0xd62be25cu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xbff66f32u, 0xdeaa2ffau, 0xaeea0bf2u, 0x57221606u);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x3f4de62au, 0xd4a7763cu, 0x72a2c25du, 0xfee76446u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x408a6332u, 0x70c85823u, 0xba550647u, 0x6c7a0118u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xce068befu, 0x594ede3cu, 0xdd21f885u, 0x161bb234u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x06577a13u, 0x046c382au, 0x87202106u, 0x4aadd486u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x693044b9u, 0xf444e09du, 0x9cd38744u, 0xe79400dfu);
    SCE->REG_28H = 0x008f0001u;
    SCE->REG_34H = 0x00000002u;
    SCE->REG_24H = 0x80004cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000810u;
    SCE->REG_24H = 0x80005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20u;
    SCE->REG_24H = 0x80005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030u;
    SCE->REG_24H = 0x80007cd0u;
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
    SCE->REG_100H = change_endian_long(0x010273a4u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x02c0a883u, 0x19bc9bf8u, 0x8a4d98f1u, 0xe96ed903u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000003u;
    SCE->REG_24H = 0x800068d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfa3c622cu, 0xbe404837u, 0xeaf69b97u, 0x06fe547bu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x302b59aau, 0x3c798675u, 0xb2620a09u, 0xabfc9999u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x2caa1a54u, 0x74f01619u, 0x52968b85u, 0xde32ac27u);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0xaf3e4354u, 0xc389c01cu, 0x8632c676u, 0x37f71c4fu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfa47bbbcu, 0x2186ab9bu, 0x6cbb06aeu, 0x24eec58du);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbba4691bu, 0xe809e7ecu, 0x87cc4caeu, 0x36e4d9ceu);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xc300af1du, 0x00630fe3u, 0x587a44c0u, 0x979fcffdu);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x1add51aau, 0xd1792bb8u, 0x5da32e2du, 0xd9009259u);
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
    HW_SCE_p_func100(0x6533e676u, 0x00320303u, 0x5c57fa97u, 0xcd8f78d4u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func320(680);
    SCE->REG_24H = 0x000084d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func322(992);
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x000000f2u;
    HW_SCE_p_func101(0x20156d0du, 0x4a6debf6u, 0xcd98c326u, 0xc2592cf4u);
    HW_SCE_p_func316();
    HW_SCE_p_func100(0xb2a69fbdu, 0xd54a0102u, 0xa4ae8bc1u, 0xb09ac9cbu);
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x21279ea7u, 0x8885e559u, 0xfee5f26fu, 0xb8e8810eu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc61bc8d8u, 0xa17db7e5u, 0x4cf9ace0u, 0x8f4f62c0u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x3511825fu, 0xa1ad11c6u, 0x31304478u, 0x31441f8au);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x7afc6944u, 0x3665a4b9u, 0xe89d431eu, 0x812626ecu);
    SCE->REG_28H = 0x008f0001u;
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x800070d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000408u;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cu;
    SCE->REG_24H = 0x8000f0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00u;
    SCE->REG_24H = 0x8000f4d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_24H = 0x000050d0u;
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
    SCE->REG_100H = change_endian_long(0x018e0c4cu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9370c3b9u, 0x1148f325u, 0xe6e883c1u, 0x1554a40eu);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000003u;
    SCE->REG_24H = 0x800068d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5de51f5au, 0xd2ab8b57u, 0x5b4abc0au, 0xb66fa0ecu);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(896);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01d3c420u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x73ba7d8eu, 0x3ec086e9u, 0xb7f46379u, 0x9bfbb9e7u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(896);
    HW_SCE_p_func100(0x98fcf7c7u, 0xdb8e3b77u, 0x6d7956d9u, 0x27e79ea2u);
    HW_SCE_p_func314(896+36);
    HW_SCE_p_func100(0xf4cbee06u, 0x7c2204a2u, 0x9d9edc3fu, 0xf500a0deu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4327aa73u, 0xc6d287bbu, 0x43f83e20u, 0x2d47933du);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x898cf445u, 0xcd6ecfe9u, 0xb1e7dd5du, 0x3e376e78u);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xe04ac6d1u, 0xbbd060d9u, 0x5333fbedu, 0xb1c7a350u);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x78baf84bu, 0xd1b8ce55u, 0x026ec1a4u, 0x85342454u);
    SCE->REG_28H = 0x008f0001u;
    SCE->REG_34H = 0x00000002u;
    SCE->REG_24H = 0x80004cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000810u;
    SCE->REG_24H = 0x80005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20u;
    SCE->REG_24H = 0x80005cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030u;
    SCE->REG_24H = 0x80007cd0u;
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
    SCE->REG_100H = change_endian_long(0x010273a4u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8da0cac8u, 0x7f4719efu, 0xdd188136u, 0xc4b4b9c7u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000480au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000003u;
    SCE->REG_24H = 0x800068d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800048d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf53761fu, 0x094a3437u, 0xe9a062d0u, 0xd6a2d246u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcc697f8bu, 0x92ad849au, 0xa4431439u, 0x9d2a656du);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1u;
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
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x55bcde64u, 0x94f0b7ceu, 0xc4beae7eu, 0x801ee81du);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x20b7209eu, 0x64136fe8u, 0x7c127365u, 0xde84756bu);
    HW_SCE_p_func314(816+36);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_24H = 0x00009cd0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103e0u;
    SCE->REG_00H = 0x0000031fu;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x00008307u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_E0H = 0x800103c0u;
    SCE->REG_00H = 0x0000031fu;
    SCE->REG_2CH = 0x00000023u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x00008307u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00870001u;
    SCE->REG_ECH = 0x3800dbffu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x0e0631dfu, 0xffba1140u, 0xdb43c976u, 0xa4eb562cu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0xffffffffu;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x800080d0u;
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
        SCE->REG_34H = 0x00000008u;
        SCE->REG_24H = 0x82001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x1d28f437u, 0x93b026e2u, 0xf16d82e8u, 0x9f89524au);
    }
    else
    {
        SCE->REG_ECH = 0x00000800u;
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0xf946db7du, 0x8ce722a7u, 0xd1bf9f9fu, 0x652119e5u);
    }
    HW_SCE_p_func100(0xf758d158u, 0x1da3af1cu, 0x8442f130u, 0x481aeb30u);
    SCE->REG_ECH = 0x000034ffu;
    SCE->REG_ECH = 0x00003420u;
    SCE->REG_ECH = 0x00003440u;
    SCE->REG_ECH = 0x00003460u;
    SCE->REG_ECH = 0x00003480u;
    SCE->REG_ECH = 0x000034a0u;
    SCE->REG_ECH = 0x000034c0u;
    SCE->REG_E0H = 0x81080000u;
    SCE->REG_00H = 0x00003823u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_34H = 0x00000804u;
    SCE->REG_24H = 0x800090d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c04u;
    SCE->REG_24H = 0x800090d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x8000b0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001181u;
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
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8ce9f145u, 0x0583725du, 0x018addc6u, 0x34a422fau);
    SCE->REG_00H = 0x00002393u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xc6b3739cu, 0xd28a9d79u, 0x1a35fa37u, 0xa6242a49u);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x55afc622u, 0xa9d4b88eu, 0x14cfedb9u, 0x2b7144c8u);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x800090d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func322(896);
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_24H = 0x000009c0u;
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
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_ECH = 0x3800dbdfu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x1c438645u, 0x94e7987fu, 0xd13e1a83u, 0xe5515679u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b400u;
        SCE->REG_ECH = 0xffffffffu;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000591u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800u;
        SCE->REG_24H = 0x800080d0u;
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
        SCE->REG_34H = 0x00000008u;
        SCE->REG_24H = 0x82001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x94647d15u, 0xf787c49eu, 0xef925afeu, 0x6482c67eu);
    }
    else
    {
        SCE->REG_ECH = 0x00000800u;
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x2a5c9e0bu, 0x8043cdf5u, 0x8b7f2110u, 0x0d8657c3u);
    }
    SCE->REG_ECH = 0x000034feu;
    SCE->REG_ECH = 0x00003420u;
    SCE->REG_ECH = 0x00003440u;
    SCE->REG_ECH = 0x00003460u;
    SCE->REG_ECH = 0x00003480u;
    SCE->REG_ECH = 0x000034a0u;
    SCE->REG_ECH = 0x000034c0u;
    SCE->REG_E0H = 0x81080000u;
    SCE->REG_00H = 0x00003823u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_34H = 0x00000804u;
    SCE->REG_24H = 0x800090d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c04u;
    SCE->REG_24H = 0x800090d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x8000b0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181u;
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
    HW_SCE_p_func100(0x9a8f5bd4u, 0x7c50c72bu, 0x2584aed1u, 0xbffc5331u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf8a9bcacu, 0xaa6f357fu, 0x644801e7u, 0x96ba6801u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000011c0u;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbb149186u, 0x526dc394u, 0xedf700e9u, 0x16c04c42u);
    SCE->REG_00H = 0x00003293u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func322(856);
    SCE->REG_28H = 0x009f0001u;
    SCE->REG_24H = 0x000012c0u;
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
    HW_SCE_p_func100(0x1a9e726bu, 0xffb2129bu, 0x15e2b7fbu, 0x10575273u);
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
    HW_SCE_p_func100(0x4f21d1bcu, 0xb4adf116u, 0xa072f0c8u, 0x5bc08591u);
    SCE->REG_00H = 0x00003283u;
    SCE->REG_2CH = 0x00000015u;
    HW_SCE_p_func320(716);
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
    SCE->REG_24H = 0x0000a0d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001u;
    SCE->REG_34H = 0x00000400u;
    SCE->REG_24H = 0x800060d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800u;
    SCE->REG_24H = 0x800060d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00u;
    SCE->REG_24H = 0x800060d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103e0u;
    SCE->REG_00H = 0x0000031fu;
    SCE->REG_2CH = 0x00000023u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x00008307u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x3800dbffu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xbf8f24dcu, 0xa8611807u, 0xd3d73e92u, 0x917d5611u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_24H = 0x04001981u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1u;
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
            SCE->REG_24H = 0x000049c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001u;
            SCE->REG_E0H = 0x800103e0u;
            SCE->REG_00H = 0x0000031fu;
            SCE->REG_2CH = 0x00000023u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x00008307u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x3800dbffu;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00260000u;
            HW_SCE_p_func100(0x16bbe080u, 0x3a58b36du, 0x9c3bd981u, 0x89c7e361u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0x74ef9fabu, 0x4f103f45u, 0x28e539d5u, 0x8781be87u);
                oLoop1 = 0;
            }
            else
            {
                HW_SCE_p_func101(0xa8588d4eu, 0xd6390acau, 0x96539494u, 0x6e8e682fu);
            }
        }
    }
    else
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_24H = 0x04001991u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1u;
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
            SCE->REG_24H = 0x000049c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001u;
            SCE->REG_E0H = 0x800103e0u;
            SCE->REG_00H = 0x0000031fu;
            SCE->REG_2CH = 0x00000023u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_00H = 0x00008307u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800u;
            SCE->REG_ECH = 0x3800dbffu;
            SCE->REG_E0H = 0x00000080u;
            SCE->REG_1CH = 0x00A60000u;
            HW_SCE_p_func100(0x362dfab8u, 0x92e5f78au, 0x438ce431u, 0xf280d849u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_24H = 0x04001981u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1u;
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
                SCE->REG_24H = 0x000049c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                HW_SCE_p_func101(0x08586c47u, 0x91f65898u, 0xd0f33d44u, 0x5c1d4285u);
                oLoop1 = 0;
            }
            else
            {
                HW_SCE_p_func101(0x09a1a341u, 0x90a8d52au, 0x83a061f8u, 0x02856805u);
            }
        }
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000088d0u;
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000008u;
    SCE->REG_ECH = 0x00003bbeu;
    SCE->REG_ECH = 0x00007c1du;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func318.prc
***********************************************************************************************************************/
