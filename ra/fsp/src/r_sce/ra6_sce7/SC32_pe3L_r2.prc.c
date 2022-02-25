/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////

// <SC32#2 RSA2048 Key Generation>                                     //
// Procedure number: e3                                                //
// File name      : SC32_pe3L_r2.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : MAX_CNT                                            //
// Output Data    : OutData_DomainParam[160]                           //
// :  (d mod (q-1)||q||d mod (p-1)||p||q^-1 mod p)      //
// : OutData_N[64]                                      //
// : OutData_PrivateKey[64]                             //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access + long polling//
// polling        : 15218.8k cycle                                     //
// polling access :   160.4k times                                     //
// write access   :   297.9k times                                     //
// read  access   :      594 times                                     //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_rsa_private.h"
#include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * RSA2048 Key Generation
 *
 * @param[in]  num_tries            The number tries
 * @param      OutData_PrivateKey   The out data private key
 * @param      OutData_N            The out data n
 * @param      OutData_DomainParam  The out data domain parameter
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal I/O buffer is not empty.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RSA_2048KeyGenerate (uint32_t   num_tries,
                                      uint32_t * OutData_PrivateKey,
                                      uint32_t * OutData_N,
                                      uint32_t * OutData_DomainParam)
{
    uint32_t iLoop, jLoop, kLoop, lLoop;
    uint32_t MAX_CNT = num_tries;

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

    WR1_PROG(REG_84H, 0x0000e301);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    SC32_function001(0x521ab6f5, 0xfc4c0e57, 0xac4889ea, 0xb2992f35);

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
    SC32_function001(0xb9dfacf0, 0xfa1a48e6, 0x5e937a0c, 0x1cde32e6);
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

        WR1_PROG(REG_28H, 0x009f0001);

        SC32_function001(0x9f294202, 0x9e2906f8, 0x2dedb636, 0x538de2f5);

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

        for (iLoop = 0; iLoop < 24; iLoop = iLoop + 4)
        {
            SC32_function001(0x12afab67, 0xb2d780ee, 0x9d1dac62, 0xdaf2c968);

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

            SC32_function002(0xde09975e, 0xbaf78d76, 0x08d462dd, 0xce64ee03);
        }

        SC32_function001(0x12afab67, 0xb2d780ee, 0x9d1dac62, 0xdaf2c968);

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
        WR1_PROG(REG_104H, 0x00001f57);
        WAIT_STS(REG_104H, 31, 1);
        WR32_PROG(REG_100H,
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
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851B5C);

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00001591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00210000);

        SC32_function001(0x17f5e7ed, 0xb6ab055c, 0x0188f204, 0x11f9f1d1);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0xd3a587eb, 0xff0ed64f, 0x6b2df46f, 0x5b807bdf);
            continue;
        }
        else
        {
            SC32_function002(0xb2c0d9d2, 0xba5bf12e, 0x8d400b3e, 0x9881c073);
        }

        WR1_PROG(REG_ECH, 0x38008a20);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x75a4e19e, 0x708ccaae, 0x28ef7084, 0x727461a6);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x00001dc0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00001191);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);

            SC32_function001(0x0b47d20f, 0x7590c382, 0xa0c6a785, 0xc02561dd);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000011c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00001d91);
                WAIT_STS(REG_24H, 21, 0);

                SC32_function002(0x65bfad5e, 0x406e8d0d, 0xb2b03ac7, 0x9396ea2d);
            }
            else
            {
                SC32_function002(0x066dede5, 0x998a3851, 0x7ba9ff3d, 0x3932e77e);
            }

            WR1_PROG(REG_2CH, 0x00000011);
            WR1_PROG(REG_104H, 0x00000357);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, 0x00000000, 0x00000000, 0x00000000, 0x10000000);
            WR1_PROG(REG_00H, 0x00003073);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x00001591);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);

            SC32_function001(0xdcc5f5f8, 0x4cf02b63, 0x32440c75, 0x4b8f0dae);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                SC32_function002(0xc50644fe, 0x10f74a7b, 0xafb0aa8d, 0xda39ea87);
                continue;
            }
            else
            {
                SC32_function002(0x8d332ae7, 0x23ce32d0, 0x5e1b7e7f, 0x596d4aee);
            }
        }
        else
        {
            SC32_function002(0x6634aaea, 0x874a2ed3, 0x2d6ffc56, 0xdba7d516);
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
            WR1_PROG(REG_00H, 0x00003043);
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
            SC32_function001(0xdc030f40, 0x8f5302a1, 0x3fa33cee, 0x7de967d8);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);
            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_ECH, 0x0000d140);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function002(0x35c2527a, 0xad3ea69e, 0xe42ef414, 0xe17d510a);
                break;
            }
            else
            {
                SC32_function002(0x8797fcd3, 0x10c69d05, 0x34fbfbad, 0x46e7bf86);
            }
        }

        WR1_PROG(REG_ECH, 0x38008940);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x5bf62f68, 0xa3840f9c, 0xf2531e94, 0x412243fc);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0x1c4c498f, 0xa9cd0c1f, 0xc1c622b6, 0xbd639ef1);
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

        WR1_PROG(REG_00H, 0x0000307f);
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
        SC32_function001(0x1142e446, 0x6949ef7e, 0xbceb7b32, 0xae17581a);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0xb25f7b9e, 0x88c14e63, 0xfe9108d9, 0x1f1a6abb);
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000b540);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000080);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_E0H, 0x80a0000a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00008383);
            WR1_PROG(REG_2CH, 0x00000020);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_ECH, 0x0000b560);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000004);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_B0H, 0x00000700);
            WR1_PROG(REG_A4H, 0x42e0873f);
            WR1_PROG(REG_00H, 0x00001383);
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

            SC32_function001(0xb48ea1ce, 0x817170b3, 0xab4af7a4, 0x0b008442);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_7CH, 0x00000021);
                WR1_PROG(REG_00H, 0x00005113);
                WR1_PROG(REG_74H, 0x00000004);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC32_function002(0xdad16018, 0x570b578d, 0xa188c710, 0x37263a1a);
            }
            else
            {
                WR1_PROG(REG_7CH, 0x00000041);
                WR1_PROG(REG_00H, 0x00005113);
                WR1_PROG(REG_74H, 0x00000004);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC32_function002(0x430f5cf7, 0x8c6bfed3, 0x86d1131d, 0x1ecbf5b8);
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

            SC32_function001(0x344be7ee, 0x6a20bc26, 0x920bf1ca, 0x73754b8a);
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

                SC32_function002(0x9c661789, 0x07df7b12, 0xf876d29e, 0x4939f5f4);
            }

            WR1_PROG(REG_ECH, 0x00007c1f);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00026d4a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002949);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function001(0xd39fc608, 0x046b3041, 0x8717f211, 0x7ba4dff2);
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

                SC32_function002(0x109312a4, 0xdebe8f3f, 0xd5777fe1, 0x9d2f29b5);
            }

            WR1_PROG(REG_ECH, 0x00007c1f);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x0000a0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000a52);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x00006404);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00006c04);
            WAIT_STS(REG_24H, 21, 0);

            for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_2CH, 0x00000010);

                for (jLoop = 0; jLoop < 32; jLoop = jLoop + 4)
                {
                    SC32_function001(0x1dbcc04a, 0x6e5a9fe3, 0xb32ca76f, 0x34172ab4);

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

                    SC32_function002(0xcf6042c0, 0x2a1e1c57, 0x380ac473, 0x26e4a3b3);
                }

                WR1_PROG(REG_ECH, 0x0000b7e0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000100);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_E0H, 0x80a0001f);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_00H, 0x00008383);
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

                WR1_PROG(REG_18H, 0x00000004);
                WR1_PROG(REG_24H, 0x00009004);
                WAIT_STS(REG_18H, 10, 0); // No.1  You may release cpu resources because of polling long time(Long Polling)
                WR1_PROG(REG_24H, 0x00004404);
                WAIT_STS(REG_18H, 10, 0); // No.2  You may release cpu resources because of polling long time(Long Polling)
                WR1_PROG(REG_18H, 0x00000000);

                WR1_PROG(REG_ECH, 0x0000b7e0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x0000017c);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x0000b420);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);

                for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
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

                SC32_function001(0x77db023f, 0x570e4daf, 0xd065400c, 0x24f9b8e2);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 0))
                {
                    WR1_PROG(REG_ECH, 0x00002e40);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    SC32_function002(0xcaf6dfe6, 0xe87423da, 0x6f87dcb0, 0xd019ac4f);
                }
                else
                {
                    WR1_PROG(REG_24H, 0x000019c0);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x00000591);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x000040c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function001(0xa80f72a5, 0x977174e4, 0x4a1eb29d, 0x2c6246cd);
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

                        SC32_function001(0x6656eae4, 0xcf7ce16b, 0xc6ece5fe, 0xdd29d29e);
                        WR1_PROG(REG_1CH, 0x00400000);
                        WR1_PROG(REG_1D0H, 0x00000000);

                        if (CHCK_STS(REG_1CH, 22, 0))
                        {
                            WR1_PROG(REG_ECH, 0x00002e40);
                            WR1_PROG(REG_1D0H, 0x00000000);

                            SC32_function002(0xd8192439, 0x27fead75, 0x120a175c, 0x95afb180);
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

                            SC32_function002(0x3392f632, 0xa8e6e0e0, 0x581a8df9, 0xa7cf73a4);
                        }
                    }

                    WR1_PROG(REG_ECH, 0x38008a40);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x00000000);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_E0H, 0x00000080);
                    WR1_PROG(REG_1CH, 0x00260000);

                    SC32_function001(0xf3ee46b8, 0x072b344e, 0xfd727e93, 0x8a8b7dc2);
                    WR1_PROG(REG_1CH, 0x00400000);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        SC32_function002(0x58233b99, 0xce196e8d, 0x9a815f37, 0x02eaca69);
                        break;
                    }
                    else
                    {
                        SC32_function002(0x74deaf6e, 0xfaa04eb9, 0xe4d120ab, 0x20a7f97d);
                    }
                }
            }

            WR1_PROG(REG_ECH, 0x38000a4b);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0xcb67bfff, 0x663ac395, 0xc773a804, 0x5b0b0fbf);
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

                SC32_function001(0x1896b5d7, 0x06c5e5e8, 0xc40aa4f1, 0x697a1231);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    SC32_function002(0xfdd9b65e, 0x4ca28070, 0x2699cc6a, 0xba73025c);
                    break;
                }
                else
                {
                    WR1_PROG(REG_24H, 0x000019c0);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x0000e0c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function002(0xbe2cdc66, 0x602410f0, 0x33f179d9, 0xc2c866dd);
                }
            }
            else
            {
                SC32_function002(0x03464429, 0x7635205a, 0x79d2fd5f, 0x8ee873b2);
            }
        }
    }

    WR1_PROG(REG_ECH, 0x38008a20);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000002);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00A60000);

    SC32_function001(0x2edfd131, 0x51db7cc9, 0xdae95417, 0x005e899f);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x5f874045, 0x650c7ba7, 0x3ab0e687, 0x12afbec0);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_C8H, 17, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    SC32_function001(0x9543e55f, 0xd2792283, 0xf7c8e2bc, 0x57917643);

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
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00bf0001);

    WR1_PROG(REG_D0H, 0x00000f00);
    WR1_PROG(REG_C4H, 0x42e087bf);
    WR1_PROG(REG_00H, 0x00012303);
    WR1_PROG(REG_2CH, 0x00000024);
    WR1_PROG(REG_04H, 0x00000203);

    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
    }

    SC32_function001(0xff871dce, 0x6bdc40e9, 0x0e971be0, 0x55e6b301);
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

    WR1_PROG(REG_28H, 0x009f0001);

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

        SC32_function001(0xafdde79a, 0x2116add9, 0x22f01c51, 0x6007da3d);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0x8603d3b3, 0x32dafa50, 0x72081dbb, 0xa0260715);
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

            SC32_function002(0x0313b54c, 0xd4a89fd6, 0x8b225476, 0xe6639f7e);
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
    WR1_PROG(REG_24H, 0x0000b80a);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00bf0001);

    WR1_PROG(REG_00H, 0x000030ff);
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

    WR1_PROG(REG_28H, 0x00bf0001);
    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
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
        WR1_PROG(REG_E0H, 0x80c0000a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00018303);
        WR1_PROG(REG_2CH, 0x00000022);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_B0H, 0x00000f14);
        WR1_PROG(REG_A4H, 0x00008a07);
        WR1_PROG(REG_00H, 0x00011303);
        WR1_PROG(REG_2CH, 0x00000020);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_28H, 0x009f0001);
        WR1_PROG(REG_24H, 0x000019c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
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

        SC32_function001(0xe3a94c2d, 0x7a3fc875, 0x6676a862, 0x95427828);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_28H, 0x00bf0001);
            WR1_PROG(REG_104H, 0x00003f61);
            WR1_PROG(REG_B0H, 0x00000f00);
            WR1_PROG(REG_A4H, 0x42f487bf);
            WR1_PROG(REG_00H, 0x00013103);
            WR1_PROG(REG_2CH, 0x00000014);

            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
            }

            SC32_function002(0xc9c3925a, 0x2e99c53b, 0xea836851, 0xba681974);
            break;
        }
        else
        {
            WR1_PROG(REG_28H, 0x009f0001);
            WR1_PROG(REG_24H, 0x000015c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000c0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_00H, 0x00003083);
            WR1_PROG(REG_2CH, 0x00000011);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_28H, 0x00bf0001);

            WR1_PROG(REG_34H, 0x00000000);
            WR1_PROG(REG_24H, 0x0000880e);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_D0H, 0x00000f1C);
            WR1_PROG(REG_C4H, 0x00008a83);
            WR1_PROG(REG_00H, 0x00013203);
            WR1_PROG(REG_2CH, 0x00000012);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x000009c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00001191);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x0000094a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x81c0000a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00013803);
            WR1_PROG(REG_2CH, 0x00000010);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            SC32_function002(0xb8c550be, 0x2e0dcbbf, 0x1de5ce8c, 0x84946896);
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

    WR1_PROG(REG_28H, 0x009f0001);
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
    WR1_PROG(REG_E0H, 0x80a00008);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004);

    WR1_PROG(REG_24H, 0x00008404);
    WAIT_STS(REG_18H, 10, 0);          // No.5  You may release cpu resources because of polling long time(Long Polling)

    WR1_PROG(REG_24H, 0x00009004);
    WAIT_STS(REG_18H, 10, 0);          // No.6  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b500);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00008);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
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
    WR1_PROG(REG_B0H, 0x00000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
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
    WR1_PROG(REG_B0H, 0x08000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xb3060d02, 0xb5a8e69b, 0xd72dcdcb, 0x324a856c);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000024);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[96 + lLoop]);
    }

    SC32_function001(0x59698897, 0x24212cec, 0x72b89412, 0xd93b25d8);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000025);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[32 + lLoop]);
    }

    SC32_function001(0x9e45bc44, 0x83f26aed, 0x7cb8ba27, 0x47846544);
    WR1_PROG(REG_D0H, 0x0800071C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000283);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[64 + iLoop]);
    }

    SC32_function001(0xd39b6ea2, 0x1eca86be, 0xb80b4d9a, 0x7333349e);
    WR1_PROG(REG_D0H, 0x0000071C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000283);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[iLoop]);
    }

    WR1_PROG(REG_B0H, 0x00000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000023);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_B0H, 0x08000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b4e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a00007);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
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
    WR1_PROG(REG_E0H, 0x80a0001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000017c);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
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
    WR1_PROG(REG_00H, 0x0000307f);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00402000);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x14e825a6, 0xd9566478, 0x501cc875, 0x661dce7b);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000020);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[128 + lLoop]);
    }

    SC32_function001(0x49af1da1, 0x8cbe6635, 0x91952317, 0xf52b9dfc);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000023);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_N[0 + lLoop]);
    }

    SC32_function001(0x36a967ea, 0xfda63d0d, 0x2e7c220a, 0xc2cbb8b0);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000022);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_N[32 + lLoop]);
    }

    SC32_function001(0xaed34cea, 0xe5f99c7f, 0x1a17aa89, 0x77c79f42);
    WR1_PROG(REG_D0H, 0x00000f1C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000203);
    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_PrivateKey[iLoop]);
    }

    WR1_PROG(REG_B0H, 0x00000700);
    WR1_PROG(REG_A4H, 0x43e0873f);
    WR1_PROG(REG_00H, 0x00001383);
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

    WR1_PROG(REG_B0H, 0x00000700);
    WR1_PROG(REG_A4H, 0x43e0873f);
    WR1_PROG(REG_00H, 0x00001383);
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

    WR1_PROG(REG_28H, 0xfcbf0001);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80c0001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_D0H, 0x00000f1C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00018203);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_2CH, 0x00000010);
    WR1_PROG(REG_104H, 0x00003f57);
    WAIT_STS(REG_104H, 31, 1);
    WR64_PROG(REG_100H,
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
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFAB);

    WR1_PROG(REG_ECH, 0x0000094a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80c0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00018303);
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
    WR1_PROG(REG_ECH, 0x000001fc);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b420);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000004);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 1)
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

    WR1_PROG(REG_28H, 0x00bf0001);

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

        SC32_function001(0xebbf33dd, 0x41212836, 0xab9b79c1, 0x5f2f90cf);
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

            SC32_function002(0x6d14cd7c, 0xf999416f, 0x72015075, 0x879a8016);
        }
        else
        {
            SC32_function002(0xf45dce4c, 0x17a6a730, 0x91bf150c, 0x9debeb62);
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

    WR1_PROG(REG_28H, 0x00bf0001);

    WR1_PROG(REG_ECH, 0x0000094a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b540);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
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

    SC32_function003(0xcfad6b78, 0xf6ef4ebb, 0x48a1f91e, 0x242ee559);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_C8H, 17, 0);

    return FSP_SUCCESS;
}
