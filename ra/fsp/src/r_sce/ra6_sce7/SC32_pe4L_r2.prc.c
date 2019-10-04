/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////

// <SC32#2 RSA1024 Key Generation>                                     //
// Procedure number: e4                                                //
// File name      : SC32_pe4L_r2.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : MAX_CNT                                            //
// Output Data    : OutData_DomainParam[80]                            //
// :  (d mod (q-1)||q||d mod (p-1)||p||q^-1 mod p)      //
// : OutData_N[32]                                      //
// : OutData_PrivateKey[32]                             //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access + long polling//
// polling        :  2756.7k cycle                                     //
// polling access :    81.2k times                                     //
// write access   :   167.1k times                                     //
// read  access   :      425 times                                     //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_rsa_private.h"
#include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * RSA1024 Key Generation
 *
 * @param[in]  num_words            The number words
 * @param      OutData_PrivateKey   The out data private key
 * @param      OutData_N            The out data n
 * @param      OutData_DomainParam  The out data domain parameter
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal I/O buffer is not empty.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RSA_1024KeyGenerate (uint32_t   num_words,
                                      uint32_t * OutData_PrivateKey,
                                      uint32_t * OutData_N,
                                      uint32_t * OutData_DomainParam)
{
    uint32_t iLoop, jLoop, kLoop, lLoop;
    uint32_t MAX_CNT = num_words;

    if (RD1_MASK(REG_1BCH, 0x0000001f) != 0x0000000)
    {
        // Busy now then retry later;
        // Because  1_xxxx other processing box is in duty.
        // x_1xxx resource D is in duty,then retry after you released D.
        // x_x1xx resource C is in duty,then retry after you released C.
        // x_xx1x resource B is in duty,then retry after you released B.
        // x_xxx1 resource A is in duty,then retry after you released A.

        // A,B,C,D: see Primitive Level Procedures datasheet
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000e401);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    SC32_function001(0x6615e3b6, 0x6e7c8aa6, 0xaa9267d4, 0xd9ebb630);

    WR1_PROG(REG_104H, 0x00000252);
    WR1_PROG(REG_C4H, 0x01003774);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_C4H, 0x010037f4);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_C4H, 0x010037f4);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_C4H, 0x00060805);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01073644);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_C4H, 0x000b0805);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    SC32_function001(0x4c786603, 0xa36432fd, 0x45214b38, 0x9a8f8ba4);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01080c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000a31);
    WR1_PROG(REG_1D0H, 0x00000000);
    for (kLoop = 0; kLoop < MAX_CNT; kLoop = kLoop + 1)
    {
        WR1_PROG(REG_28H, 0x00bf0001);
        WR1_PROG(REG_00H, 0x00003043);
        WR1_PROG(REG_2CH, 0x00000012);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_104H, 0x00002f57);
        WAIT_STS(REG_104H, 31, 1);
        WR48_PROG(REG_100H,
                  0x00030005,
                  0x0007000b,
                  0x000d0011,
                  0x00130017,
                  0x001d001f,
                  0x00250029,
                  0x002b002f,
                  0x003b003d,
                  0x00430047,
                  0x0049004f,
                  0x00530059,
                  0x00610065,
                  0x0067006b,
                  0x006d0071,
                  0x007f0083,
                  0x0089008b,
                  0x00950097,
                  0x009d00a3,
                  0x00a700ad,
                  0x00b300b5,
                  0x00bf00c1,
                  0x00c500c7,
                  0x00d300df,
                  0x00e300e5,
                  0x00e900ef,
                  0x00f100fb,
                  0x01010107,
                  0x010d010f,
                  0x01150119,
                  0x011b0125,
                  0x01330137,
                  0x0139013d,
                  0x014b0151,
                  0x015b015d,
                  0x01610167,
                  0x016f0175,
                  0x017b017f,
                  0x0185018d,
                  0x01910199,
                  0x01a301a5,
                  0x01af01b1,
                  0x01b701bb,
                  0x01c101c9,
                  0x01cd01cf,
                  0x01d301df,
                  0x01e701eb,
                  0x01f301f7,
                  0x01fd0000);

        WR1_PROG(REG_ECH, 0x000008c6);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_00H, 0x00000343);
        WR1_PROG(REG_2CH, 0x00000022);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_E0H, 0x80a00006);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008383);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_ECH, 0x0000b4c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000080);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80900006);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008343);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_28H, 0x008f0001);

        SC32_function001(0x2d9d0348, 0x3cb3bbd4, 0xbc07e1a8, 0xb686bfab);

        WR1_PROG(REG_104H, 0x00000252);
        WR1_PROG(REG_C4H, 0x01003774);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x010037f4);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x010037f4);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x00060805);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x01073644);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x000b0805);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x01000c84);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_E0H, 0x80040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_ECH, 0x0000d01f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x81040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003813);
        WR1_PROG(REG_2CH, 0x00000010);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        for (iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
        {
            SC32_function001(0xc4659eff, 0x2714d129, 0x0fd4b81c, 0x517c0a38);

            WR1_PROG(REG_104H, 0x00000252);
            WR1_PROG(REG_C4H, 0x01003774);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_C4H, 0x010037f4);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_C4H, 0x010037f4);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_C4H, 0x00060805);
            WR1_PROG(REG_00H, 0x00002213);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_104H, 0x00000052);
            WR1_PROG(REG_C4H, 0x01073644);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_C4H, 0x000b0805);
            WR1_PROG(REG_00H, 0x00002213);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);
            WR1_PROG(REG_104H, 0x00000052);
            WR1_PROG(REG_C4H, 0x01000c84);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_00H, 0x00003213);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            SC32_function002(0x9e19e79a, 0x3edc4161, 0xe3b10810, 0x78712422);
        }

        SC32_function001(0xc4659eff, 0x2714d129, 0x0fd4b81c, 0x517c0a38);

        WR1_PROG(REG_104H, 0x00000252);
        WR1_PROG(REG_C4H, 0x01003774);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x010037f4);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x010037f4);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x00060805);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x01073644);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_C4H, 0x000b0805);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x01000c84);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_E0H, 0x80040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_ECH, 0x0000d060);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x81040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003813);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_2CH, 0x00000011);
        WR1_PROG(REG_104H, 0x00000f57);
        WAIT_STS(REG_104H, 31, 1);
        WR16_PROG(REG_100H,
                  0xB51EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB80E);

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00001591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00210000);

        SC32_function001(0x82642442, 0x54ef02c4, 0x0125a1d4, 0x79287071);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0x8f2a3ebe, 0x1d4c1c2f, 0x2ab6fac9, 0x73288cf7);
            continue;
        }
        else
        {
            SC32_function002(0x6bd23faf, 0x50a20d27, 0x203ab949, 0xf306bf65);
        }

        WR1_PROG(REG_ECH, 0x38008a20);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x14c461e1, 0x59d48f5c, 0xe8f7f374, 0xa58ae6c0);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x00001dc0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00001191);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);

            SC32_function001(0x320637df, 0xdb011ce0, 0xbf766199, 0x20f042ed);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000011c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00001d91);
                WAIT_STS(REG_24H, 21, 0);

                SC32_function002(0xc46e0ab9, 0x84697397, 0xce20c45f, 0x70888e33);
            }
            else
            {
                SC32_function002(0x6a29a1ee, 0xbdb068ff, 0x29230787, 0xc70fabc7);
            }

            WR1_PROG(REG_2CH, 0x00000011);
            WR1_PROG(REG_104H, 0x00000357);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, 0x00000000, 0x00000000, 0x00000000, 0x10000000);
            WR1_PROG(REG_00H, 0x00003033);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x00001591);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);

            SC32_function001(0x5f092e25, 0x3750bcb9, 0x7a3d1622, 0xb81034f1);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                SC32_function002(0xe0ac04bf, 0x702e4efd, 0x85e1c9be, 0xeebddfcd);
                continue;
            }
            else
            {
                SC32_function002(0x594eb2e2, 0xe2e607e2, 0x151f3f0c, 0x38de4df3);
            }
        }
        else
        {
            SC32_function002(0x9606f70b, 0x7de08ca5, 0xb4bfbe48, 0xa8f2bde4);
        }

        WR1_PROG(REG_ECH, 0x000008c6);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x0000094a);
        WR1_PROG(REG_1D0H, 0x00000000);

        for (iLoop = 0; iLoop < 96; iLoop = iLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x01003906);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002cc0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002cc0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x81010100);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_00H, 0x0000303f);
            WR1_PROG(REG_2CH, 0x00000014);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_00H, 0x00003807);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x00004006);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000009c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000591);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);
            SC32_function001(0xb2e4da03, 0x3e8824e1, 0xf07f46c2, 0x69d9f831);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);
            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_ECH, 0x0000d140);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function002(0x379daf8a, 0x4655614a, 0xf49490b0, 0x96d7595c);
                break;
            }
            else
            {
                SC32_function002(0xee8c2db9, 0x0d3eb473, 0x1edd09a5, 0xba16e921);
            }
        }

        WR1_PROG(REG_ECH, 0x38008940);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x5c529787, 0x5d2ed082, 0xf4fa5a90, 0xd09b8ce5);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0x8923ef15, 0x37f65b2b, 0x5520af18, 0x1d96616b);
            continue;
        }

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_00H, 0x0000303f);
        WR1_PROG(REG_2CH, 0x00000014);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_104H, 0x00000057);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00010001);

        WR1_PROG(REG_24H, 0x00004006);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00210000);
        SC32_function001(0xd909ac51, 0x07a11d6d, 0x84cb742f, 0x803d0805);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0xfd6368ce, 0xd98379c3, 0xb79b7c22, 0x602606ae);
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000b540);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x000000c0);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_E0H, 0x8090000a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00008343);
            WR1_PROG(REG_2CH, 0x00000020);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_ECH, 0x0000b560);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000008);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_B0H, 0x00000300);
            WR1_PROG(REG_A4H, 0x42e0873f);
            WR1_PROG(REG_00H, 0x00001343);
            WR1_PROG(REG_2CH, 0x00000020);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00000c84);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_A4H, 0x400009cd);
            WR1_PROG(REG_00H, 0x00001113);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_ECH, 0x38008a20);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000000);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0x31e3efbd, 0xf537a433, 0xce1063ed, 0xdf34ca71);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_7CH, 0x00000021);
                WR1_PROG(REG_00H, 0x00005113);
                WR1_PROG(REG_74H, 0x00000004);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC32_function002(0xa985f261, 0xaf23035b, 0xcc3ebc07, 0x5826e380);
            }
            else
            {
                WR1_PROG(REG_7CH, 0x00000041);
                WR1_PROG(REG_00H, 0x00005113);
                WR1_PROG(REG_74H, 0x00000004);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC32_function002(0xf7591179, 0xf7becc8c, 0xd6c3d0a0, 0xcfbc9b22);
            }

            WR1_PROG(REG_24H, 0x000011c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000c0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000929);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x0000b4c0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x000000fc);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00003906);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00008d00);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0xfffffffe);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00003d06);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00000908);
            WR1_PROG(REG_1D0H, 0x00000000);
            for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_ECH, 0x000038e6);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x0000a8c0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);
                for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
                {
                    WR1_PROG(REG_ECH, 0x38008900);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x00000000);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x11816907);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    WR1_PROG(REG_ECH, 0x38008900);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x00000000);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x10002d20);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    WR1_PROG(REG_ECH, 0x000168e7);
                    WR1_PROG(REG_1D0H, 0x00000000);
                }
            }

            WR1_PROG(REG_ECH, 0x00003549);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0000a540);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000003);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0002694a);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function001(0x22886e37, 0xd779323d, 0x22558662, 0x24cd6bfc);
            WR1_PROG(REG_E0H, 0x81010140);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_04H, 0x00000607);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);

            WR1_PROG(REG_ECH, 0x000037ea);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_24H, 0x000011c0);
            WAIT_STS(REG_24H, 21, 0);

            for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_ECH, 0x000033e0);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function002(0x3cb2540d, 0x48859443, 0x04638981, 0xe6c2af48);
            }

            WR1_PROG(REG_ECH, 0x00007c1f);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00026d4a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002949);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function001(0x1953d4ed, 0xbf2f9a53, 0x726ecef6, 0x807706fa);
            WR1_PROG(REG_E0H, 0x81010140);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_04H, 0x00000607);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);

            WR1_PROG(REG_ECH, 0x000037ea);
            WR1_PROG(REG_1D0H, 0x00000000);

            for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_34H, 0x00000000);
                WR1_PROG(REG_24H, 0x2000018d);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_ECH, 0x000033e0);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function002(0x287f5cbe, 0xc341eaef, 0xc269db9e, 0x47bcfd10);
            }

            WR1_PROG(REG_ECH, 0x00007c1f);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x0000a0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000a52);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x000084d0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00021028);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000800);
            WR1_PROG(REG_24H, 0x8000c0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00006404);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00006c04);
            WAIT_STS(REG_24H, 21, 0);

            for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_2CH, 0x00000010);

                for (jLoop = 0; jLoop < 16; jLoop = jLoop + 4)
                {
                    SC32_function001(0xbbc77e71, 0x81933a55, 0xba7b3567, 0x5f73ce60);

                    WR1_PROG(REG_104H, 0x00000252);
                    WR1_PROG(REG_C4H, 0x01003774);
                    WAIT_STS(REG_104H, 31, 1);
                    WR1_PROG(REG_100H, 0x00000000);

                    WR1_PROG(REG_C4H, 0x010037f4);
                    WAIT_STS(REG_104H, 31, 1);
                    WR1_PROG(REG_100H, 0x00000000);

                    WR1_PROG(REG_C4H, 0x010037f4);
                    WAIT_STS(REG_104H, 31, 1);
                    WR1_PROG(REG_100H, 0x00000000);

                    WR1_PROG(REG_C4H, 0x00060805);
                    WR1_PROG(REG_00H, 0x00002213);
                    WAIT_STS(REG_00H, 25, 0);
                    WR1_PROG(REG_1CH, 0x00001800);

                    WR1_PROG(REG_104H, 0x00000052);
                    WR1_PROG(REG_C4H, 0x01073644);
                    WAIT_STS(REG_104H, 31, 1);
                    WR1_PROG(REG_100H, 0x00000000);

                    WR1_PROG(REG_C4H, 0x000b0805);
                    WR1_PROG(REG_00H, 0x00002213);
                    WAIT_STS(REG_00H, 25, 0);
                    WR1_PROG(REG_1CH, 0x00001800);
                    WR1_PROG(REG_104H, 0x00000052);
                    WR1_PROG(REG_C4H, 0x01000c84);
                    WAIT_STS(REG_104H, 31, 1);
                    WR1_PROG(REG_100H, 0x00000000);

                    WR1_PROG(REG_00H, 0x00003213);
                    WAIT_STS(REG_00H, 25, 0);
                    WR1_PROG(REG_1CH, 0x00001800);

                    SC32_function002(0xb8959e6a, 0xc3d5a09f, 0xd45a4d1b, 0xa6e82e52);
                }

                WR1_PROG(REG_ECH, 0x0000b7e0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000100);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_E0H, 0x8090001f);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_00H, 0x00008343);
                WR1_PROG(REG_2CH, 0x00000021);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                WR1_PROG(REG_24H, 0x000019c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x0000c0c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000050d0);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000084d0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00021028);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_34H, 0x00000800);
                WR1_PROG(REG_24H, 0x8000c0c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000088d0);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x00001028);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000011c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000019c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x0000c0c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000050d0);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000084d0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00021028);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_34H, 0x00000800);
                WR1_PROG(REG_24H, 0x8000c0c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000088d0);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_18H, 0x00000004);
                WR1_PROG(REG_24H, 0x00009004);
                WAIT_STS(REG_18H, 10, 0); // No.1  You may release cpu resources because of polling long time(Long Polling)
                WR1_PROG(REG_24H, 0x00004404);
                WAIT_STS(REG_18H, 10, 0); // No.2  You may release cpu resources because of polling long time(Long Polling)
                WR1_PROG(REG_18H, 0x00000000);

                WR1_PROG(REG_ECH, 0x0000b7e0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x0000013c);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x0000b420);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);

                for (jLoop = 0; jLoop < 16; jLoop = jLoop + 1)
                {
                    WR1_PROG(REG_ECH, 0x0000389f);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 1)
                    {
                        WR1_PROG(REG_ECH, 0x3800d880);
                        WR1_PROG(REG_1D0H, 0x00000000);
                        WR1_PROG(REG_E0H, 0x00000080);

                        WR1_PROG(REG_ECH, 0x00016884);
                        WR1_PROG(REG_1D0H, 0x00000000);

                        WR1_PROG(REG_24H, 0x0000082c);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x100019b1);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_24H, 0x000019a1);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x400040c1);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_24H, 0x0000102c);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x100019b1);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_24H, 0x000019a1);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x000080c1);
                        WAIT_STS(REG_24H, 21, 0);
                    }

                    WR1_PROG(REG_ECH, 0x00002be1);
                    WR1_PROG(REG_1D0H, 0x00000000);
                }

                WR1_PROG(REG_24H, 0x000088d0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00001028);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000005c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00001191);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_1CH, 0x00210000);

                WR1_PROG(REG_24H, 0x000005c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000040c1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000011c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000991);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_1CH, 0x00210000);

                SC32_function001(0x10377630, 0x1787a5bf, 0x4ab74f65, 0x48bf61d5);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 0))
                {
                    WR1_PROG(REG_ECH, 0x00002e40);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    SC32_function002(0x311db0d0, 0x3c366253, 0x14245800, 0x2de71be7);
                }
                else
                {
                    WR1_PROG(REG_24H, 0x000019c0);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x00000591);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x000040c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function001(0xf79ecdcf, 0x556fa1e8, 0xdda0c51b, 0xc95ebfb6);
                    WR1_PROG(REG_E0H, 0x81010120);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_04H, 0x00000607);
                    WAIT_STS(REG_04H, 30, 1);
                    RD1_ADDR(REG_100H, &S_RAM[1]);
                    WR1_PROG(REG_ECH, 0x000037e9);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    for (jLoop = 0; jLoop < S_RAM[1]; jLoop = jLoop + 1)
                    {
                        WR1_PROG(REG_24H, 0x000009c0);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x00001191);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_1CH, 0x00210000);

                        WR1_PROG(REG_24H, 0x000011c0);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x00000991);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_1CH, 0x00210000);

                        SC32_function001(0xa6fe1c88, 0xfe525ec4, 0x0a5b46bd, 0xabe4e1ae);
                        WR1_PROG(REG_1CH, 0x00400000);
                        WR1_PROG(REG_1D0H, 0x00000000);

                        if (CHCK_STS(REG_1CH, 22, 0))
                        {
                            WR1_PROG(REG_ECH, 0x00002e40);
                            WR1_PROG(REG_1D0H, 0x00000000);

                            SC32_function002(0xc72fdd53, 0xb44e169e, 0x185e5f1c, 0xfc4e1da5);
                            break;
                        }
                        else
                        {
                            WR1_PROG(REG_24H, 0x00000c2c);
                            WAIT_STS(REG_24H, 21, 0);
                            WR1_PROG(REG_24H, 0x100019b1);
                            WAIT_STS(REG_24H, 21, 0);
                            WR1_PROG(REG_24H, 0x000019a1);
                            WAIT_STS(REG_24H, 21, 0);
                            WR1_PROG(REG_24H, 0x000040c1);
                            WAIT_STS(REG_24H, 21, 0);

                            WR1_PROG(REG_24H, 0x0000082c);
                            WAIT_STS(REG_24H, 21, 0);
                            WR1_PROG(REG_24H, 0x100019b1);
                            WAIT_STS(REG_24H, 21, 0);
                            WR1_PROG(REG_24H, 0x000019a1);
                            WAIT_STS(REG_24H, 21, 0);
                            WR1_PROG(REG_24H, 0x000080c1);
                            WAIT_STS(REG_24H, 21, 0);

                            SC32_function002(0x343d6c7d, 0xb3b26807, 0x03c4faa3, 0x17f1adac);
                        }
                    }

                    WR1_PROG(REG_ECH, 0x38008a40);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x00000000);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_E0H, 0x00000080);
                    WR1_PROG(REG_1CH, 0x00260000);

                    SC32_function001(0x77ca0c30, 0xee6d52f7, 0xd27db461, 0x8fc6d79c);
                    WR1_PROG(REG_1CH, 0x00400000);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        SC32_function002(0x93e8c2b4, 0xd0e14976, 0xf705886d, 0x34db9d15);
                        break;
                    }
                    else
                    {
                        SC32_function002(0x26d39ccb, 0x40793ae4, 0x8f2473fd, 0x390344ce);
                    }
                }
            }

            WR1_PROG(REG_ECH, 0x38000a4b);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0x762e4615, 0xf1bf3699, 0xfecc402a, 0x650d7cf8);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_ECH, 0x00002e20);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x38008a20);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000002);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_E0H, 0x00000080);
                WR1_PROG(REG_1CH, 0x00260000);

                SC32_function001(0x1654d0f8, 0xfd2ed4f9, 0x6921639f, 0x3d787301);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    SC32_function002(0x0d9cc69c, 0x5be4c5fd, 0xf4efc5e6, 0xcdb0a236);
                    break;
                }
                else
                {
                    WR1_PROG(REG_24H, 0x000019c0);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x0000e0c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function002(0x409bdf80, 0x0857da69, 0x2c027d46, 0x553101fb);
                }
            }
            else
            {
                SC32_function002(0xe5d3b977, 0xa47564ea, 0x731c643c, 0x4c1a5d79);
            }
        }
    }

    WR1_PROG(REG_ECH, 0x38008a20);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000002);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00A60000);

    SC32_function001(0x45c98b2b, 0x8ff7aca9, 0x402d6819, 0x9156c76a);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x0e968457, 0x02675d07, 0x15ac6ef1, 0xecaa7868);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_C8H, 17, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_ECH, 0x0000b5c0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010001);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000020);
    WR1_PROG(REG_24H, 0x800019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001);

    SC32_function001(0xd30dcef4, 0x12ad0eb2, 0x62ba5c04, 0x26ddf55f);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x42e087bf);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000024);
    WR1_PROG(REG_04H, 0x00000283);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
    }

    SC32_function001(0x6132b4c1, 0xca6b1e21, 0xa2143216, 0xa1ae040f);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_C4H, 0x400009cd);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_04H, 0x00000213);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[iLoop]);

    WR1_PROG(REG_28H, 0x008f0001);
    WR1_PROG(REG_24H, 0x0000b0d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x0000c8d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e8d0);
    WAIT_STS(REG_24H, 21, 0);

    while (1)
    {
        WR1_PROG(REG_24H, 0x00008006);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00210000);

        SC32_function001(0xa9abea2b, 0xa4cbe41f, 0x6dbd4b71, 0x627c1e59);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0x58c20a6c, 0xc9377131, 0x8569f16b, 0x2a2e6cf7);
            break;
        }
        else
        {
            WR1_PROG(REG_24H, 0x000019c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000d0d0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);

            SC32_function002(0x7757f638, 0x0b304cad, 0x6712141f, 0x6b7ffa05);
        }
    }

    WR1_PROG(REG_24H, 0x000094d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_24H, 0x0000c002);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x0000dcd0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000980a);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001);

    WR1_PROG(REG_00H, 0x0000307f);
    WR1_PROG(REG_2CH, 0x00000014);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000057);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00010001);

    WR1_PROG(REG_2CH, 0x00000002);
    WR1_PROG(REG_34H, 0x00000000);
    WR1_PROG(REG_24H, 0x0000c002);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00870001);
    WR1_PROG(REG_E0H, 0x800100c0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x0000031f);
    WR1_PROG(REG_2CH, 0x00000024);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_00H, 0x00008307);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x009f0001);
    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b500);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010001);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_24H, 0x000005c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    while (1)
    {
        WR1_PROG(REG_ECH, 0x0000094a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80a0000a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008383);
        WR1_PROG(REG_2CH, 0x00000022);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_B0H, 0x00000714);
        WR1_PROG(REG_A4H, 0x00008a07);
        WR1_PROG(REG_00H, 0x00001383);
        WR1_PROG(REG_2CH, 0x00000020);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_28H, 0x008f0001);
        WR1_PROG(REG_24H, 0x00001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000080d0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_28H, 0x00870001);
        WR1_PROG(REG_00H, 0x0000301f);
        WR1_PROG(REG_2CH, 0x00000014);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_E0H, 0x810100c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003807);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_00H, 0x0000301f);
        WR1_PROG(REG_2CH, 0x00000010);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_E0H, 0x81010100);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003807);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_2CH, 0x00000000);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x8000c002);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x00003506);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_E0H, 0x800100c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x0000031f);
        WR1_PROG(REG_2CH, 0x0000002c);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_00H, 0x00008307);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_ECH, 0x380088c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x21b36337, 0x3ec68e48, 0xf69f8456, 0x2563d5a4);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_28H, 0x008f0001);

            WR1_PROG(REG_104H, 0x00001f61);
            WR1_PROG(REG_B0H, 0x00000700);
            WR1_PROG(REG_A4H, 0x42f487bf);
            WR1_PROG(REG_00H, 0x00003143);
            WR1_PROG(REG_2CH, 0x00000015);
            for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
            }

            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_00H, 0x00003143);
            WR1_PROG(REG_2CH, 0x00000014);
            for (iLoop = 16; iLoop < 32; iLoop = iLoop + 4)
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
            }

            SC32_function002(0xea31f83e, 0x836c27aa, 0x0ab0d5d3, 0x86996c96);
            break;
        }
        else
        {
            WR1_PROG(REG_28H, 0x008f0001);
            WR1_PROG(REG_34H, 0x00000008);
            WR1_PROG(REG_24H, 0x800011c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000e0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_00H, 0x00003043);
            WR1_PROG(REG_2CH, 0x00000018);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_28H, 0x009f0001);

            WR1_PROG(REG_34H, 0x00000000);
            WR1_PROG(REG_24H, 0x8000890e);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_D0H, 0x0000071C);
            WR1_PROG(REG_C4H, 0x00008a83);
            WR1_PROG(REG_00H, 0x00003283);
            WR1_PROG(REG_2CH, 0x00000012);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x000009c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00001191);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00001de1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x0000094a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x81a0000a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00003883);
            WR1_PROG(REG_2CH, 0x00000010);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            SC32_function002(0xdfd04102, 0x82acfabf, 0x834c9c35, 0x201e4604);
        }
    }

    WR1_PROG(REG_ECH, 0x00007c06);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00602000);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_104H, 0x00000361);
    WR1_PROG(REG_A4H, 0x400007bd);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[iLoop]);

    WR1_PROG(REG_A4H, 0x00800c45);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x008f0001);
    WR1_PROG(REG_34H, 0x00000002);
    WR1_PROG(REG_24H, 0x800009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000060c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00021028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004);

    WR1_PROG(REG_24H, 0x00008404);
    WAIT_STS(REG_18H, 10, 0);          // No.3  You may release cpu resources because of polling long time(Long Polling)

    WR1_PROG(REG_24H, 0x00009004);
    WAIT_STS(REG_18H, 10, 0);          // No.4  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_24H, 0x0000102c);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000908);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900008);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00021028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004);

    WR1_PROG(REG_24H, 0x00008404);
    WAIT_STS(REG_18H, 10, 0);          // No.5  You may release cpu resources because of polling long time(Long Polling)

    WR1_PROG(REG_24H, 0x00009004);
    WAIT_STS(REG_18H, 10, 0);          // No.6  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b500);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000040);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900008);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000015c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00008907);
    WAIT_STS(REG_18H, 10, 0);          // No.7  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000581);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_B0H, 0x00000314);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000015c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00008807);
    WAIT_STS(REG_18H, 10, 0);          // No.8  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000581);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_B0H, 0x04000314);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0x529d318a, 0x4012c512, 0xeab73f7b, 0x9b6985c3);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000024);

    WR1_PROG(REG_04H, 0x00000242);
    for (lLoop = 0; lLoop < 16; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[48 + lLoop]);
    }

    SC32_function001(0x040c9d01, 0xacfc3037, 0x8b75f1ee, 0x515810de);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000025);

    WR1_PROG(REG_04H, 0x00000242);
    for (lLoop = 0; lLoop < 16; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[16 + lLoop]);
    }

    SC32_function001(0xd4e9ef10, 0x4d8c1a04, 0x645d528a, 0x76b65958);
    WR1_PROG(REG_D0H, 0x0400031C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000243);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[32 + iLoop]);
    }

    SC32_function001(0xd84693d5, 0x5e3bb725, 0x4cb2e3b9, 0x74deb030);
    WR1_PROG(REG_D0H, 0x0000031C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000243);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[iLoop]);
    }

    WR1_PROG(REG_B0H, 0x00000314);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001343);
    WR1_PROG(REG_2CH, 0x00000023);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_B0H, 0x04000314);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001343);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00021028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b4e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000040);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900007);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000060c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x0000082c);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000828);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x8090001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000013c);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_ECH, 0x0000381f);
        WR1_PROG(REG_1D0H, 0x00000000);

        for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x3800d800);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);

            WR1_PROG(REG_ECH, 0x00016800);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x0000082c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x400040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x0000102c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
        }

        WR1_PROG(REG_ECH, 0x00002be1);
        WR1_PROG(REG_1D0H, 0x00000000);
    }

    WR1_PROG(REG_24H, 0x000088d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000000);
    WR1_PROG(REG_2CH, 0x00000002);
    WR1_PROG(REG_24H, 0x00007b0a);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000011);
    WR1_PROG(REG_104H, 0x00000057);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x80000000);
    WR1_PROG(REG_00H, 0x0000303f);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00402000);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x3d368a0c, 0x951b0572, 0x969c02ce, 0xc1ff1748);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000020);

    WR1_PROG(REG_04H, 0x00000242);
    for (lLoop = 0; lLoop < 16; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[64 + lLoop]);
    }

    SC32_function001(0x464108cb, 0x0cd0922b, 0xebfdeb39, 0x5db15319);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000023);

    WR1_PROG(REG_04H, 0x00000242);
    for (lLoop = 0; lLoop < 16; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_N[0 + lLoop]);
    }

    SC32_function001(0x4cfccb2c, 0xa6472721, 0x02aebb89, 0xc5c60a46);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000022);

    WR1_PROG(REG_04H, 0x00000242);
    for (lLoop = 0; lLoop < 16; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_N[16 + lLoop]);
    }

    SC32_function001(0xab7a5322, 0xd6a29b17, 0x22b2213c, 0x7bf3a2c6);
    WR1_PROG(REG_D0H, 0x0000071C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000283);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_PrivateKey[iLoop]);
    }

    WR1_PROG(REG_B0H, 0x00000300);
    WR1_PROG(REG_A4H, 0x43e0873f);
    WR1_PROG(REG_00H, 0x00001343);
    WR1_PROG(REG_2CH, 0x00000025);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_A4H, 0x4106094d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_7CH, 0x00000021);
    WR1_PROG(REG_A4H, 0x01800c05);
    WR1_PROG(REG_00H, 0x00001513);
    WR1_PROG(REG_74H, 0x00000008);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x00000300);
    WR1_PROG(REG_A4H, 0x43e0873f);
    WR1_PROG(REG_00H, 0x00001343);
    WR1_PROG(REG_2CH, 0x00000024);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_A4H, 0x4106094d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_7CH, 0x00000041);
    WR1_PROG(REG_A4H, 0x01800c05);
    WR1_PROG(REG_00H, 0x00001513);
    WR1_PROG(REG_74H, 0x00000008);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x008f0001);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001);

    WR1_PROG(REG_B0H, 0x0000071C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a0001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008183);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_2CH, 0x00000010);
    WR1_PROG(REG_104H, 0x00001f57);
    WAIT_STS(REG_104H, 31, 1);
    WR32_PROG(REG_100H,
              0x7FFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFE97);

    WR1_PROG(REG_ECH, 0x0000094a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00009004);
    WAIT_STS(REG_18H, 10, 0);          // No.9  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00004404);
    WAIT_STS(REG_18H, 10, 0);          // No.10  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000017c);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b420);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000004);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_ECH, 0x0000389f);
        WR1_PROG(REG_1D0H, 0x00000000);

        for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x3800d880);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);

            WR1_PROG(REG_ECH, 0x00016884);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x0000082c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x400040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x0000102c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
        }

        WR1_PROG(REG_ECH, 0x00002be1);
        WR1_PROG(REG_1D0H, 0x00000000);
    }

    WR1_PROG(REG_24H, 0x000088d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001);

    WR1_PROG(REG_24H, 0x000050d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00008404);
    WAIT_STS(REG_18H, 10, 0);          // No.11  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b400);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010001);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000bff);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        WR1_PROG(REG_ECH, 0x00002fe0);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_24H, 0x0000102c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x3800d81f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00A60000);

        WR1_PROG(REG_ECH, 0x00016c00);
        WR1_PROG(REG_1D0H, 0x00000000);

        SC32_function001(0xb2ab67ba, 0x3e80416f, 0xf22e56f6, 0xe6288477);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x0000082c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);

            SC32_function002(0xbf3884d2, 0x0f6d66f1, 0x68e40d69, 0xa9d8da62);
        }
        else
        {
            SC32_function002(0xb566b741, 0xc9bd0eec, 0xc67f9a53, 0x875a1b85);
        }
    }

    WR1_PROG(REG_ECH, 0x00008be0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000020);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00007c1f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00602000);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_24H, 0x00001028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001);

    WR1_PROG(REG_ECH, 0x0000094a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00402000);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010000);

    SC32_function003(0x462185e5, 0xcfdecd0c, 0xb1864999, 0x387f6dd2);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_C8H, 17, 0);

    return FSP_SUCCESS;
}
