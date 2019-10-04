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

// <SC32#2 RSA2048 Decryption CRT>                                     //
// Procedure number: 72                                                //
// File name      : SC32_p72L_r2.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Text[64] (Cipher text)                      //
// : InData_DomainParam[160]                            //
// :(d mod (q-1) || q || d mod (p-1) || p || q^-1 mod p)//
// Output Data    : OutData_Text[64] (Text)                            //
// Return Value   : Pass or Resource_Conflict                          //
// ---------------------------------------------------------------------//
// LONG_polling1  :   8.3k cycle                                       //
// LONG_polling2  :   8.3k cycle                                       //
// LONG_polling3  :   8.3k cycle                                       //
// LONG_polling4  :   8.3k cycle                                       //
// LONG_polling5  :   8.3k cycle                                       //
// LONG_polling6  :   8.3k cycle                                       //
// LONG_polling7  :   8.3k cycle                                       //
// LONG_polling8  :   8.3k cycle                                       //
// LONG_polling9  :   8.3k cycle                                       //
// LONG_polling10 :   8.3k cycle                                       //
// total cycle    : LONG_polling + polling + write access + read access//
// polling        : 1337.9k cycle                                      //
// polling access :   16840 times                                      //
// write access   :   28259 times                                      //
// read  access   :     209 times                                      //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_rsa_private.h"
#include "SCE_ProcCommon.h"

/*******************************************************************************************************************//**
 * @ingroup SCE_PROC_RSA
 * @brief Decryption using 2048-bit RSA private key (CRT format)
 *
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Decryption using 2048-bit RSA private key (CRT format)
 *
 * @param[in]  InData_Text         InData_Text pointer to 64-word buffer containing message to be encrypted
 * @param[in]  InData_DomainParam  InData_DomainParam  pointer to 160-word buffer with 2048-bit RSA key CRT parameters
 *                               (d mod (q-1) || q || d mod (p-1) || p || q^-1 mod p)
 * @param      OutData_Text       The result of private-key decryption is stored in the buffer pointed to by `OutData_Text`
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RSA_2048PrivateCrtKeyDecrypt (const uint32_t * InData_Text,
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

    WR1_PROG(REG_84H, 0x00007201);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x00000001);

    WR1_PROG(REG_28H, 0x00bf0001);
    WR1_PROG(REG_1CH, 0x00000080);
    WR1_PROG(REG_D0H, 0x00000f00);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00013203);
    WR1_PROG(REG_2CH, 0x00000010);
    for (lLoop = 0; lLoop < 64; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_Text[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_C4H, 0x00083b8c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x5dab6044);

    WR1_PROG(REG_D0H, 0x00000e00);
    WR1_PROG(REG_C4H, 0x42008e1f);
    WR1_PROG(REG_00H, 0x000023f3);
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

    WR1_PROG(REG_28H, 0x009f0001);
    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x00000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x7c9f0001);

    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_D0H, 0x00001700);
    WR1_PROG(REG_C4H, 0x00008887);

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008283);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 0]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000014);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 32]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x08000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00001283);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 64]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_D0H, 0x00000f00);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000015);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 96]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000011);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 128]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000084d0);
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

    WR1_PROG(REG_24H, 0x00007004);
    WAIT_STS(REG_18H, 10, 0);          // No.5  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00006c04);
    WAIT_STS(REG_18H, 10, 0);          // No.6  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00006c04);
    WAIT_STS(REG_18H, 10, 0);          // No.7  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_7CH, 0x00000031);
    WR1_PROG(REG_74H, 0x00000100);
    WR1_PROG(REG_00H, 0x00005343);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_A4H, 0x00040805);
    WR1_PROG(REG_00H, 0x00001313);
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
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x0000092c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x0000071C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003283);
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

    SC32_function001(0x5067f454, 0x004dc0aa, 0x80b0a43e, 0x07ceb86d);

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
    SC32_function001(0x079bcf59, 0x4d0697ff, 0x63381b39, 0x99da13d9);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01080c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x51b805b7, 0xb4d12a21, 0x8bdae5ea, 0x709248e1);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x42e087bf);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000020);
    WR1_PROG(REG_04H, 0x00000282);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[20 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0xbb4e1718, 0xadf47a5b, 0x3cf2bc46, 0xc5b3a3ae);
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
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000c2c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x0000071C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003283);
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

    SC32_function001(0x6a80ca73, 0xb363f38e, 0x9dcb8e4b, 0xb626c7fb);

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
    SC32_function001(0x3b735d3c, 0xddda2a95, 0x03a16930, 0x2e258cad);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x010c0c04);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x916bdbe7, 0xf55199f2, 0x4fb94064, 0x8d957238);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x02e087bf);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000020);
    WR1_PROG(REG_04H, 0x00000282);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x62b59ca8, 0x6d80ebcd, 0xa825a5b3, 0x55b9b8e1);
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
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x0000092c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x0000071C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003283);
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
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
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
    WR1_PROG(REG_E0H, 0x80a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000022);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_D0H, 0x0000071C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003283);
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

    WR1_PROG(REG_D0H, 0x00000714);
    WR1_PROG(REG_C4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000023);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00001f62);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x02f087bf);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000013);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
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
    WR1_PROG(REG_ECH, 0x0000007c);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b4a0);
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

    SC32_function001(0x58bbb7a2, 0xe0b5a396, 0x3723002d, 0x01408c87);

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
    SC32_function001(0xce3a8a97, 0x0e2e69ea, 0x21231d17, 0x195bd3f3);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x010c0c04);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0xf71479d5, 0x71bd7844, 0x88232db0, 0x29412ee8);
    WR1_PROG(REG_B0H, 0x0000071C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x02e087bf);
    WR1_PROG(REG_00H, 0x00002183);
    WR1_PROG(REG_04H, 0x00000282);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[56 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0xa575988d, 0x1da8aa2d, 0x845fac5b, 0x0ea682cd);
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
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_D0H, 0x00000714);
    WR1_PROG(REG_C4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00002883);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000094d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_B0H, 0x0800071C);
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

    WR1_PROG(REG_104H, 0x00001f62);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x42f087bf);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000013);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
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

    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00004404);
    WAIT_STS(REG_18H, 10, 0);          // No.9  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000017c);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b4a0);
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

    WR1_PROG(REG_B0H, 0x08000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a0001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00001883);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xd8d6f560, 0x884018b3, 0x2ee7a930, 0x27226ba9);

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

    SC32_function001(0x323ceff7, 0xca51deb5, 0x896bc6f2, 0x9afdd81f);
    WR1_PROG(REG_C4H, 0x00080885);
    WR1_PROG(REG_E0H, 0x81040080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002813);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xa7dc6999, 0x7f9fd9c1, 0xaed5fcc5, 0x5379c74d);
    WR1_PROG(REG_B0H, 0x0000071C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x42e087bf);
    WR1_PROG(REG_00H, 0x00002183);
    WR1_PROG(REG_04H, 0x00000282);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[56 + 100 + iLoop]);
    }

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    SC32_function001(0x08156e17, 0x1becb051, 0xd4e9ddc0, 0xe655e5ee);
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
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
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

    WR1_PROG(REG_7CH, 0x00000031);
    WR1_PROG(REG_74H, 0x00000200);
    WR1_PROG(REG_00H, 0x00003543);
    WR1_PROG(REG_2CH, 0x00000011);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
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

    WR1_PROG(REG_7CH, 0x00000031);
    WR1_PROG(REG_74H, 0x00000100);
    WR1_PROG(REG_00H, 0x00005343);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_A4H, 0x00040805);
    WR1_PROG(REG_00H, 0x00001313);
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

    WR1_PROG(REG_2CH, 0x00000011);
    for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x400007bc);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
    }

    WR1_PROG(REG_24H, 0x00001328);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000060c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b660);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_24H, 0x0000aa0b);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000016c0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x0000acd0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000060c2);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_D0H, 0x00000714);
    WR1_PROG(REG_C4H, 0x00008a07);
    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002883);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_24H, 0x0000aa0a);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x00bf0001);
    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000981);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x009f0001);
    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00001f62);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x02f087bf);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000013);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
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

    WR1_PROG(REG_ECH, 0x00000a73);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0x186960a8, 0xafcb560f, 0xf8d7f8ea, 0x14ea6a1a);
    WR1_PROG(REG_C4H, 0x00080885);
    WR1_PROG(REG_E0H, 0x81040080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002813);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00001f62);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x42f087bf);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000013);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
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

    WR1_PROG(REG_28H, 0x009f0001);
    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_D0H, 0x00001700);
    WR1_PROG(REG_C4H, 0x00008887);

    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 0]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x0000071C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003183);
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

    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 32]);
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

    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 64]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x0800071C);
    WR1_PROG(REG_A4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00003183);
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

    WR1_PROG(REG_D0H, 0x00000f00);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 96]);
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

    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000010);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[iLoop + 128]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_7CH, 0x00000031);
    WR1_PROG(REG_74H, 0x00000200);
    WR1_PROG(REG_00H, 0x00003543);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003113);
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
    WR1_PROG(REG_E0H, 0x81a00013);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000010);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x00bf0001);

    SC32_function001(0x16d122db, 0x196fcc74, 0x691e27e1, 0x496e4dc1);
    WR1_PROG(REG_D0H, 0x00000f00);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00012303);
    WR1_PROG(REG_2CH, 0x00000020);

    WR1_PROG(REG_04H, 0x00000202);
    for (lLoop = 0; lLoop < 64; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_Text[0 + lLoop]);
    }

    WR1_PROG(REG_1C0H, 0x00010000);

    SC32_function003(0x8e353bab, 0xc88ccab0, 0xa9f151cd, 0xc94f7445);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
