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
 * File Name    : s_flash.c
 * Version      : 1.09
 * Description  : Key information file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 31.03.2020 1.09     First Release
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
uint32_t const S_FLASH[] =
{
#ifndef __ARMEB__   /* Little endian */
    0x1f139b11, 0x36f1a8ff, 0xfbb51d1f, 0x39c11444, 
    0xbd0159ef, 0x95220e61, 0x332d2f12, 0xdeb00ba0, 
    0xbfdb72e5, 0xab79e7e3, 0x0f54848b, 0xdf66b71b, 
    0xa744cfd8, 0x6bce32d3, 0xe1a02e9c, 0x6c437ff5, 
    0xb6cc7fb4, 0xb0a479fb, 0x55cc77d0, 0x8a0bd853, 
    0xb53344a2, 0x9f0fcd84, 0x9f4ee8c1, 0x306cc3f3, 
    0xa9190024, 0x81c16117, 0xa18ca15c, 0x13d8f8c5, 
    0xa4fb5f21, 0xff9cc9b5, 0x1d9597d7, 0xc479be7d, 
    0x5a1571a5, 0x806f16a6, 0x4adf4e41, 0xc4027bc2, 
    0xbd60c1d7, 0x8d7361de, 0xff1cc445, 0xc3f0e15e, 
    0xbccbac1a, 0xcd35fc18, 0xe170e2d9, 0x1520ae6b, 
    0x3ea2ca89, 0x14b612a8, 0x43c2e688, 0xd0f7d645, 
    0xe42890cc, 0x54837d00, 0x8b1ff9bd, 0xd029b7ca, 
    0xbd6ec31e, 0x11fed66b, 0x2b1f0efa, 0xdf697736, 
    0xe40d9717, 0x91100d59, 0xb1a901e7, 0xe9d8ee46, 
    0x0bef8388, 0x403b5fca, 0xba0274ec, 0xc52088cc, 
    0x13c4e697, 0x43ef750e, 0x6e6545c6, 0xf2a5d180, 
    0x14122acb, 0x6908dabe, 0x843177de, 0x7097cc80, 
    0x69e41816, 0x02808419, 0x639baaab, 0xfe011eb1, 
    0xde29fd5f, 0x97cd6c1e, 0xb6c346e0, 0xd8b94c10, 
    0x3b2c74cb, 0x5c5aa1cc, 0x70694a1a, 0x42cb781c, 
    0x65610c9a, 0xaa7a087c, 0x530ef768, 0x2a02283f, 
    0x9a18a849, 0xa20a3514, 0x842e319d, 0x420ddf7c, 
    0x39e7e858, 0xbc2bea47, 0xbc6905f7, 0x72e83583, 
    0x3d09c27f, 0x88ac6a9e, 0x03781e76, 0xb67503c0, 
    0xa64ed20c, 0x63f083dc, 0x91f40140, 0x64248a9b, 
    0x61e5734b, 0x18f17613, 0x2ccc4f31, 0x8c83d7d8, 
    0x52bc354c, 0xd8715be6, 0x292ac64e, 0xd1c90f1a, 
    0xedfedaeb, 0x491045a5, 0x13769dc6, 0x17b38fb7, 
    0x70b4212a, 0xdc225cef, 0x41e19ec7, 0xd30ad44a, 
    0x0b525acb, 0x9102297a, 0x098620e0, 0xd8dac35c, 
    0x38ffc99e, 0xd7787d38, 0x059b1611, 0x820543f3, 
#else               /* Big endian */
    0x119b131f, 0xffa8f136, 0x1f1db5fb, 0x4414c139, 
    0xef5901bd, 0x610e2295, 0x122f2d33, 0xa00bb0de, 
    0xe572dbbf, 0xe3e779ab, 0x8b84540f, 0x1bb766df, 
    0xd8cf44a7, 0xd332ce6b, 0x9c2ea0e1, 0xf57f436c, 
    0xb47fccb6, 0xfb79a4b0, 0xd077cc55, 0x53d80b8a, 
    0xa24433b5, 0x84cd0f9f, 0xc1e84e9f, 0xf3c36c30, 
    0x240019a9, 0x1761c181, 0x5ca18ca1, 0xc5f8d813, 
    0x215ffba4, 0xb5c99cff, 0xd797951d, 0x7dbe79c4, 
    0xa571155a, 0xa6166f80, 0x414edf4a, 0xc27b02c4, 
    0xd7c160bd, 0xde61738d, 0x45c41cff, 0x5ee1f0c3, 
    0x1aaccbbc, 0x18fc35cd, 0xd9e270e1, 0x6bae2015, 
    0x89caa23e, 0xa812b614, 0x88e6c243, 0x45d6f7d0, 
    0xcc9028e4, 0x007d8354, 0xbdf91f8b, 0xcab729d0, 
    0x1ec36ebd, 0x6bd6fe11, 0xfa0e1f2b, 0x367769df, 
    0x17970de4, 0x590d1091, 0xe701a9b1, 0x46eed8e9, 
    0x8883ef0b, 0xca5f3b40, 0xec7402ba, 0xcc8820c5, 
    0x97e6c413, 0x0e75ef43, 0xc645656e, 0x80d1a5f2, 
    0xcb2a1214, 0xbeda0869, 0xde773184, 0x80cc9770, 
    0x1618e469, 0x19848002, 0xabaa9b63, 0xb11e01fe, 
    0x5ffd29de, 0x1e6ccd97, 0xe046c3b6, 0x104cb9d8, 
    0xcb742c3b, 0xcca15a5c, 0x1a4a6970, 0x1c78cb42, 
    0x9a0c6165, 0x7c087aaa, 0x68f70e53, 0x3f28022a, 
    0x49a8189a, 0x14350aa2, 0x9d312e84, 0x7cdf0d42, 
    0x58e8e739, 0x47ea2bbc, 0xf70569bc, 0x8335e872, 
    0x7fc2093d, 0x9e6aac88, 0x761e7803, 0xc00375b6, 
    0x0cd24ea6, 0xdc83f063, 0x4001f491, 0x9b8a2464, 
    0x4b73e561, 0x1376f118, 0x314fcc2c, 0xd8d7838c, 
    0x4c35bc52, 0xe65b71d8, 0x4ec62a29, 0x1a0fc9d1, 
    0xebdafeed, 0xa5451049, 0xc69d7613, 0xb78fb317, 
    0x2a21b470, 0xef5c22dc, 0xc79ee141, 0x4ad40ad3, 
    0xcb5a520b, 0x7a290291, 0xe0208609, 0x5cc3dad8, 
    0x9ec9ff38, 0x387d78d7, 0x11169b05, 0xf3430582, 
#endif  /* defined __ARMEB__ */
};

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

