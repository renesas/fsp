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

// <SC32#2 RSA1024 Decryption with Private Key>                        //
// Procedure number: 40                                                //
// File name      : SC32_p40L_r1.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Text[32] (Cipher text)                      //
// : InData_PrivateKey[32] (private exponent)                          //
// : InData_N[32] (public modulus)                                     //
// Output Data    : OutData_Text[32] (Text)                            //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// LONG_polling1  :   8.3k cycle                                       //
// LONG_polling2  :   8.3k cycle                                       //
// total cycle    : LONG_polling + polling + write access + read access//
// polling        :  664.2k cycle                                      //
// polling access :  8244 times                                        //
// write access   : 13622 times                                        //
// read  access   :    34 times                                        //
/////////////////////////////////////////////////////////////////////////

#include  "SCE_ProcCommon.h"
#include "hw_sce_rsa_private.h"

/*******************************************************************************************************************//**
 * RSA1024 Decryption with Private Key
 *
 * @param[in]  InData_Text        InData_Text pointer to 32-word buffer containing message to be encrypted
 * @param[in]  InData_PrivateKey  InData_PrivateKey pointer to 32-word buffer 2048-bit RSA private exponent (`d`)
 * @param[in]  InData_N           InData_N pointer to 32-word buffer containing 2048-bit RSA public modulus (`N`)
 * @param      OutData_Text       OutData_Text result of private-key decryption is stored in the buffer pointed to by `OutData_Text`
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal I/O buffer is not empty.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RSA_1024PrivateKeyDecrypt (const uint32_t * InData_Text,
                                            const uint32_t * InData_PrivateKey,
                                            const uint32_t * InData_N,
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

    WR1_PROG(REG_84H, 0x00004001);
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
    WR1_PROG(REG_1CH, 0x000000a0);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003283);
    WR1_PROG(REG_2CH, 0x00000014);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_N[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_00H, 0x0000037f);
    WR1_PROG(REG_2CH, 0x00000024);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_E0H, 0x800103e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008307);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x3800dbe0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00260000);

    WR1_PROG(REG_24H, 0x000005c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00a10000);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0xd818e4c9, 0xef382136, 0x02f8e983, 0x3704a41c);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0xf7e3157a, 0xbcbb95de, 0xc10cd42c, 0xcdf3d858);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1CH, 0x000000a0);
        WR1_PROG(REG_D0H, 0x00000700);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_ECH, 0x00000bff);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80a0001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008283);
        for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_PrivateKey[iLoop]);
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_18H, 0x00000004);
        WR1_PROG(REG_24H, 0x00009004);
        WAIT_STS(REG_18H, 10, 0);      // No.1  You may release cpu resources because of polling long time(Long Polling)
        WR1_PROG(REG_24H, 0x00004404);
        WAIT_STS(REG_18H, 10, 0);      // No.2  You may release cpu resources because of polling long time(Long Polling)
        WR1_PROG(REG_18H, 0x00000000);

        WR1_PROG(REG_ECH, 0x0000b420);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000004);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x0000007c);
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

        SC32_function001(0x55c48200, 0xf2acb7bf, 0x982d5440, 0x6927d3fe);
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

        SC32_function003(0xb82e9c3e, 0xbe01a1a8, 0xe4a09197, 0xfe1cf1fc);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
