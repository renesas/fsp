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

// <SC32#2 RSA1024 Decryption CRT>                                     //
// Procedure number: 73                                                //
// File name      : SC32_p73L_r2.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Text[32] (Cipher text)                      //
// : InData_DomainParam[80]                             //
// :(d mod (q-1) || q || d mod (p-1) || p || q^-1 mod p)//
// Output Data    : OutData_Text[32] (Text)                            //
// Return Value   : Pass or Resource_Conflict                          //
// ---------------------------------------------------------------------//
// LONG_polling1  :  2.1k cycle                                        //
// LONG_polling2  :  2.1k cycle                                        //
// LONG_polling3  :  2.1k cycle                                        //
// LONG_polling4  :  2.1k cycle                                        //
// LONG_polling5  :  2.1k cycle                                        //
// LONG_polling6  :  2.1k cycle                                        //
// LONG_polling7  :  2.1k cycle                                        //
// LONG_polling8  :  2.1k cycle                                        //
// LONG_polling9  :  2.1k cycle                                        //
// LONG_polling10 :  2.1k cycle                                        //
// total cycle    : LONG_polling + polling + write access + read access//
// polling        :  223k cycle                                        //
// polling access :  8563 times                                        //
// write access   : 14543 times                                        //
// read  access   :   113 times                                        //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_rsa_private.h"
#include "SCE_ProcCommon.h"

/*******************************************************************************************************************//**
 * @ingroup SCE_PROC_RSA
 * @brief Decryption using 1024-bit RSA private key (CRT format)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * { function_description }
 *
 * @param[in]  InData_Text         Pointer to 32-word buffer containing message to be encrypted
 * @param[in]  InData_DomainParam  Pointer to 80-word buffer with 1024-bit RSA key CRT parameters
 *                               (d mod (q-1) || q || d mod (p-1) || p || q^-1 mod p)
 * @param      OutData_Text       Result of private-key decryption is stored in the buffer pointed to by `OutData_Text`
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RSA_1024PrivateCrtKeyDecrypt (const uint32_t * InData_Text,
                                               const uint32_t * InData_DomainParam,
                                               uint32_t       * OutData_Text)
{
    uint32_t iLoop, jLoop, lLoop;

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

    WR1_PROG(REG_84H, 0x00007301);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x00000001);

    WR1_PROG(REG_28H, 0x009f0001);
    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000010);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_Text[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_C4H, 0x00083b8c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x5dab6044);

    WR1_PROG(REG_D0H, 0x00000600);
    WR1_PROG(REG_C4H, 0x42008e1f);
    WR1_PROG(REG_00H, 0x00002373);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_C4H, 0x40000e9d);
    WR1_PROG(REG_00H, 0x00002313);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_E0H, 0x80040000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x008f0001);
    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x00000314);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001343);
    WR1_PROG(REG_2CH, 0x00000028);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x3c8f0001);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_D0H, 0x00001300);
    WR1_PROG(REG_C4H, 0x00008887);

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008243);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 0]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000014);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 16]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x08000314);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00001243);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 32]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000015);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 48]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000011);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 64]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00021128);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000e0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x0000b304);
    WAIT_STS(REG_18H, 10, 0);          // No.1  You may release cpu resources because of polling long time(Long Polling)

    WR1_PROG(REG_24H, 0x00005104);
    WAIT_STS(REG_18H, 10, 0);          // No.2  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00004904);
    WAIT_STS(REG_18H, 10, 0);          // No.3  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00004904);
    WAIT_STS(REG_18H, 10, 0);          // No.4  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

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
    WR1_PROG(REG_24H, 0x00007004);
    WAIT_STS(REG_18H, 10, 0);          // No.5  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00006c04);
    WAIT_STS(REG_18H, 10, 0);          // No.6  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00006c04);
    WAIT_STS(REG_18H, 10, 0);          // No.7  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_A4H, 0x00040805);
    WR1_PROG(REG_00H, 0x00001313);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_A4H, 0x00050805);
    WR1_PROG(REG_00H, 0x00001313);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_A4H, 0x00060805);
    WR1_PROG(REG_00H, 0x00001313);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_A4H, 0x00070805);
    WR1_PROG(REG_00H, 0x00001313);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x0000092c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x0000031C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x0000092d);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    SC32_function001(0xdcd7d819, 0x714af28e, 0x613d0099, 0xe2a83464);

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
    SC32_function001(0x76a9c85f, 0xd42e7bff, 0xf727a34e, 0x5d2b6c2b);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01080c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0xd2e60455, 0x055a0901, 0x0aca885f, 0x470be9bb);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x42e087bf);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000020);
    WR1_PROG(REG_04H, 0x00000242);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[20 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0xb09f32b5, 0x24e8492d, 0x95880b29, 0x26852264);
    WR1_PROG(REG_C4H, 0x400009cd);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_04H, 0x00000212);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[20 + iLoop]);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000c2c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x0000031C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000c2d);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    SC32_function001(0xa96da9f6, 0x93694766, 0xad4feec6, 0x726f51f3);

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
    SC32_function001(0xf84d532d, 0x4031d77e, 0x023154b9, 0xf55b3eb4);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x010c0c04);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x9c23727b, 0x93a068f1, 0x24355764, 0x7657bff0);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x02e087bf);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000020);
    WR1_PROG(REG_04H, 0x00000242);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x5ae8df7c, 0x8e0b41f5, 0x4f4ce5e1, 0xa0326357);
    WR1_PROG(REG_C4H, 0x000009cd);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_04H, 0x00000212);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x0000092c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x0000031C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x0000092d);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000c2c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000022);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_D0H, 0x0000031C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000c2d);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x00000314);
    WR1_PROG(REG_C4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00002343);
    WR1_PROG(REG_2CH, 0x00000023);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000f62);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x02f087bf);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000013);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000362);
    WR1_PROG(REG_C4H, 0x000007bd);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);

    WR1_PROG(REG_C4H, 0x00800c45);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00004404);
    WAIT_STS(REG_18H, 10, 0);          // No.8  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000003c);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b4a0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000004);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
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

        WR1_PROG(REG_ECH, 0x00002be5);
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

    WR1_PROG(REG_24H, 0x00004cd0);
    WAIT_STS(REG_24H, 21, 0);

    SC32_function001(0xa8e66dea, 0xfc1e5097, 0x8f9bdcf9, 0x2fe08e4b);

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
    SC32_function001(0x55be73bb, 0x5c293d5b, 0x4433672e, 0xc788e91e);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x010c0c04);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x542e04d4, 0xd016a86b, 0xc84830bc, 0x1ab0669c);
    WR1_PROG(REG_B0H, 0x0000031C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x02e087bf);
    WR1_PROG(REG_00H, 0x00002143);
    WR1_PROG(REG_04H, 0x00000242);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x67b70e1e, 0x4c7be7b5, 0x3f7b4911, 0xebfb398b);
    WR1_PROG(REG_C4H, 0x000009cd);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_04H, 0x00000212);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_D0H, 0x00000314);
    WR1_PROG(REG_C4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00002843);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000094d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_B0H, 0x0800031C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x8090001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008143);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000f62);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x42f087bf);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000013);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[20 + iLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000362);
    WR1_PROG(REG_C4H, 0x400007bd);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[20 + iLoop]);

    WR1_PROG(REG_C4H, 0x00800c45);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00004cd0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000f8d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000020);
    WR1_PROG(REG_24H, 0x800019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000820);
    WR1_PROG(REG_24H, 0x8000dcd0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000e0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00004404);
    WAIT_STS(REG_18H, 10, 0);          // No.9  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000013c);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b4a0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000004);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
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

        WR1_PROG(REG_ECH, 0x00002be5);
        WR1_PROG(REG_1D0H, 0x00000000);
    }

    WR1_PROG(REG_24H, 0x0000a8d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001228);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_B0H, 0x08000314);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x8190001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00001843);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0x9d10c564, 0x45fe3493, 0x24fe3722, 0xdf4e3647);

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

    WR1_PROG(REG_E0H, 0x80040080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xdfd91cfc, 0x265842d2, 0xd80c7d19, 0x9ceeccd1);
    WR1_PROG(REG_C4H, 0x00080885);
    WR1_PROG(REG_E0H, 0x81040080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002813);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xe431a157, 0x31b62ea3, 0xe97ee419, 0xae836407);
    WR1_PROG(REG_B0H, 0x0000031C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x42e087bf);
    WR1_PROG(REG_00H, 0x00002143);
    WR1_PROG(REG_04H, 0x00000242);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[56 + 100 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x4c9f3f27, 0x6c93cef3, 0xac2831ec, 0xd4a77dbb);
    WR1_PROG(REG_C4H, 0x400009cd);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_04H, 0x00000212);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[56 + 100 + iLoop]);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00004404);
    WAIT_STS(REG_18H, 10, 0);          // No.10  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);
    WR1_PROG(REG_24H, 0x0000082c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000015c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WR1_PROG(REG_2CH, 0x00000011);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00000cc4);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000cc4);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000a2c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_A4H, 0x00040805);
    WR1_PROG(REG_00H, 0x00001313);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_A4H, 0x00050805);
    WR1_PROG(REG_00H, 0x00001313);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_A4H, 0x00060805);
    WR1_PROG(REG_00H, 0x00001313);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_A4H, 0x00070805);
    WR1_PROG(REG_00H, 0x00001313);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000050d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_C4H, 0x00083b8c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x5dab6044);

    WR1_PROG(REG_C4H, 0x00040805);
    WR1_PROG(REG_E0H, 0x81040000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002813);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_2CH, 0x00000018);
    for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x400007bc);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
    }

    WR1_PROG(REG_34H, 0x00000008);
    WR1_PROG(REG_24H, 0x80001128);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x800080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000008);
    WR1_PROG(REG_24H, 0x80001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000060c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_34H, 0x00000808);
    WR1_PROG(REG_24H, 0x8000880b);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000208);
    WR1_PROG(REG_24H, 0x800011c0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x80008cd0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000880);
    WR1_PROG(REG_24H, 0x800040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x00000314);
    WR1_PROG(REG_C4H, 0x00008a07);
    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002843);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_34H, 0x00000808);
    WR1_PROG(REG_24H, 0x8000880a);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x009f0001);
    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000981);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x008f0001);
    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000f62);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x02f087bf);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000013);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000362);
    WR1_PROG(REG_C4H, 0x000007bd);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);

    WR1_PROG(REG_C4H, 0x00800c45);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0x8e33c60a, 0x098e32f9, 0xfc7361f6, 0x6867eb33);
    WR1_PROG(REG_C4H, 0x00080885);
    WR1_PROG(REG_E0H, 0x81040080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002813);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000f62);
    WR1_PROG(REG_D0H, 0x00000300);
    WR1_PROG(REG_C4H, 0x42f087bf);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000013);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[56 + 100 + iLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000362);
    WR1_PROG(REG_C4H, 0x400007bd);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[56 + 100 + iLoop]);

    WR1_PROG(REG_C4H, 0x00800c45);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x008f0001);
    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_D0H, 0x00001300);
    WR1_PROG(REG_C4H, 0x00008887);

    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 0]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x0000031C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003143);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 16]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001d91);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 32]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x0800031C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003143);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 48]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00000090);
    WR1_PROG(REG_00H, 0x00003243);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 64]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00000cc4);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000cc4);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000828);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00402000);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81900013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003843);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x009f0001);

    SC32_function001(0x45b9bd8a, 0xb6e77c52, 0xb9a04a3d, 0x44491768);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000020);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_Text[0 + lLoop]);
    }

    WR1_PROG(REG_1C0H, 0x00010000);

    SC32_function003(0xc22ebd5d, 0xf9b0d121, 0x00da652d, 0x192b0739);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
