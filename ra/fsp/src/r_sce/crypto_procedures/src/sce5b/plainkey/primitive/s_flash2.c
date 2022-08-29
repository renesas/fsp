/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : s_flash2.c
 * Version      : 1.01
 * Description  : Key information file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 05.10.2020 1.00        First Release.
 *         : 02.12.2020 1.01        Added new functions such as the Brainpool curve.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_sce_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
uint32_t const S_FLASH2[] =
{
#ifndef __ARMEB__   /* Little endian */
    0xbfacfc87, 0x381b73d8, 0x1d5c3edc, 0xafaa0b7c,
    0x73785296, 0x6b7061d9, 0x136b6548, 0x61e757e4,
    0x63c486fc, 0x32f57607, 0x27f815d5, 0x820d899e,
    0x6d9da017, 0x44f759d2, 0xfd6b9863, 0xe50651ac,
    0xacf6ff72, 0xa0074850, 0xb9e60823, 0x25253121,
    0xe3b724ac, 0xefe089f1, 0x54b3882f, 0x55d75f9b,
    0x62a7d166, 0xdd6359e0, 0x25d8bfab, 0x337ee97e,
    0x3175b086, 0xd571f022, 0xd6c29749, 0x720cfcf7,
    0x21bb119e, 0x86387eae, 0x202bf380, 0x23c21e0c,
    0x5082b073, 0x01ed07d0, 0xd1ad281c, 0x08f76b26,
    0x3576f994, 0x5c2b1c92, 0x1dc3f997, 0xb24a5104,
    0x13884b3c, 0x7f0f63f9, 0x39e2f270, 0x8b121e18,
    0x757644f0, 0x4b24902c, 0xbc234f09, 0x3142d12a,
    0x3e344ae8, 0x61099aa4, 0xee568c51, 0x6ccfe03a,
    0x458ce878, 0x001f51f6, 0xd0ba3b34, 0x2105340b,
    0x242575cd, 0xe9a6191b, 0x4b8db240, 0x51ffaacf,
    0xec2641e2, 0x32f7b858, 0xbfac9c98, 0xecedf604,
    0xbd08a48a, 0x85118400, 0xdc9950e2, 0x149b4ab0,
    0xfdf7a843, 0xd3d68566, 0xfe6bce60, 0x163361da,
    0x45cf2cc5, 0x8bd50a8a, 0x415ca509, 0xf43d0aab,
    0xa5d84d38, 0x9187225f, 0x6ff551a7, 0x82c45745,
    0x7f14f76c, 0xb22e72ab, 0xf3d0fd01, 0x9b1782ff,
    0x08582ccc, 0xdc77d9be, 0xe8efc110, 0x034dfa37,
    0xdf1c7d61, 0xbf717709, 0x84bcc6de, 0xcaad5976,
    0x1c9980fc, 0x8e7260c6, 0xf8a509d4, 0x7a974bae,
    0x1cc4a8c4, 0xb6f43424, 0x37092384, 0x7054ea4d,
    0x3985c76a, 0x80a83eb4, 0xb48b7024, 0xe75d88a0,
    0xcc6910ee, 0x3574940b, 0x5df8964a, 0x7c775e19,
    0x365fa5bb, 0xf5e88350, 0x9889f781, 0xd20acf20,
    0x68a81d9d, 0xb7049d78, 0x2b0a25ee, 0xb4299ed6,
    0x4a714da1, 0xe34f755f, 0x1762e2bb, 0x74a12e41,
    0x3c810507, 0x3d53169e, 0xfdda9e53, 0xecbffe79,
#else     /* Big endian */
    0x87fcacbf, 0xd8731b38, 0xdc3e5c1d, 0x7c0baaaf,
    0x96527873, 0xd961706b, 0x48656b13, 0xe457e761,
    0xfc86c463, 0x0776f532, 0xd515f827, 0x9e890d82,
    0x17a09d6d, 0xd259f744, 0x63986bfd, 0xac5106e5,
    0x72fff6ac, 0x504807a0, 0x2308e6b9, 0x21312525,
    0xac24b7e3, 0xf189e0ef, 0x2f88b354, 0x9b5fd755,
    0x66d1a762, 0xe05963dd, 0xabbfd825, 0x7ee97e33,
    0x86b07531, 0x22f071d5, 0x4997c2d6, 0xf7fc0c72,
    0x9e11bb21, 0xae7e3886, 0x80f32b20, 0x0c1ec223,
    0x73b08250, 0xd007ed01, 0x1c28add1, 0x266bf708,
    0x94f97635, 0x921c2b5c, 0x97f9c31d, 0x04514ab2,
    0x3c4b8813, 0xf9630f7f, 0x70f2e239, 0x181e128b,
    0xf0447675, 0x2c90244b, 0x094f23bc, 0x2ad14231,
    0xe84a343e, 0xa49a0961, 0x518c56ee, 0x3ae0cf6c,
    0x78e88c45, 0xf6511f00, 0x343bbad0, 0x0b340521,
    0xcd752524, 0x1b19a6e9, 0x40b28d4b, 0xcfaaff51,
    0xe24126ec, 0x58b8f732, 0x989cacbf, 0x04f6edec,
    0x8aa408bd, 0x00841185, 0xe25099dc, 0xb04a9b14,
    0x43a8f7fd, 0x6685d6d3, 0x60ce6bfe, 0xda613316,
    0xc52ccf45, 0x8a0ad58b, 0x09a55c41, 0xab0a3df4,
    0x384dd8a5, 0x5f228791, 0xa751f56f, 0x4557c482,
    0x6cf7147f, 0xab722eb2, 0x01fdd0f3, 0xff82179b,
    0xcc2c5808, 0xbed977dc, 0x10c1efe8, 0x37fa4d03,
    0x617d1cdf, 0x097771bf, 0xdec6bc84, 0x7659adca,
    0xfc80991c, 0xc660728e, 0xd409a5f8, 0xae4b977a,
    0xc4a8c41c, 0x2434f4b6, 0x84230937, 0x4dea5470,
    0x6ac78539, 0xb43ea880, 0x24708bb4, 0xa0885de7,
    0xee1069cc, 0x0b947435, 0x4a96f85d, 0x195e777c,
    0xbba55f36, 0x5083e8f5, 0x81f78998, 0x20cf0ad2,
    0x9d1da868, 0x789d04b7, 0xee250a2b, 0xd69e29b4,
    0xa14d714a, 0x5f754fe3, 0xbbe26217, 0x412ea174,
    0x0705813c, 0x9e16533d, 0x539edafd, 0x79febfec,
#endif  /* defined __ARMEB__ */
};

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

