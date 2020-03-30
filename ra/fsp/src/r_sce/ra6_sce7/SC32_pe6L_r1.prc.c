/////////////////////////////////////////////////////////////////////////

// <SC32#2 RSA2048 Decryption with Private Key(hidden key)>            //
// Procedure number: e6                                                //
// File name      : SC32_pe6L_r1.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Text[64] (Cipher text)                      //
// : InData_KeyIndex[69]                                //
// : InData_N[64] (public modulus)                      //
// Output Data    : OutData_Text[64] (Text)                            //
// Return Value   : Pass, Fail, HRK_Invalid_Index or Resource_Conflict //
// ---------------------------------------------------------------------//
// LONG_polling1  :  32.9k cycle                                       //
// LONG_polling2  :  32.9k cycle                                       //
// total cycle    : LONG_polling + polling + write access + read access//
// polling        : 13176.4k cycle                                     //
// polling access :    16478 times                                     //
// write access   :    27234 times                                     //
// read  access   :       65 times                                     //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_rsa_private.h"

// <TODO> rewrite this function name.
fsp_err_t HW_SCE_HRK_RSA_2048PrivateKeyDecrypt (const uint32_t * InData_Text,
                                                const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_N,
                                                uint32_t       * OutData_Text)
{
    // <TODO> declare variables if need. exp: iLoop, KEY_ADR ...
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

    WR1_PROG(REG_84H, 0x0000e601);
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
    WR1_PROG(REG_1CH, 0x00000080);
    WR1_PROG(REG_D0H, 0x00000f00);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00013203);
    WR1_PROG(REG_2CH, 0x00000014);
    for (lLoop = 0; lLoop < 64; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_N[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_00H, 0x000003ff);
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

    SC32_function001(0xf5900c26, 0x36430214, 0x6509fb67, 0x48903ccd);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x1c784b88, 0xe863bfb4, 0x1a4701dc, 0x22f81e7e);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1CH, 0x00000081);
        WR1_PROG(REG_C4H, 0x200c3b0c);
        WAIT_STS(REG_00H, 22, 1);
        WR1_ADDR(REG_C0H, &InData_KeyIndex[0]);

        WR1_PROG(REG_C4H, 0x000c0b0c);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x6d5eba26);

        WR1_PROG(REG_1CH, 0x00000080);
        WR1_PROG(REG_D0H, 0x00000f00);
        WR1_PROG(REG_C4H, 0x02f087bf);
        WR1_PROG(REG_ECH, 0x00000bff);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80c0001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00018203);
        for (iLoop = 1; iLoop < 65; iLoop = iLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_KeyIndex[iLoop]);
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_1CH, 0x00000084);
        WR1_PROG(REG_C4H, 0x000007bd);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[iLoop]);

        WR1_PROG(REG_C4H, 0x00900c45);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        SC32_function001(0x84c67a45, 0xf40061e2, 0x03cff9c6, 0xbdc85411);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0x050c7c3c, 0x7f6212d5, 0xe2cfde1d, 0xc42e6b72);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
        }

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
        WR1_PROG(REG_ECH, 0x000000fc);
        WR1_PROG(REG_1D0H, 0x00000000);

        for (iLoop = 0; iLoop < 64; iLoop = iLoop + 1)
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

        SC32_function001(0x116325d6, 0x2e3bb3e5, 0x3684116f, 0x6bc4cb1c);
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

        SC32_function003(0x80ab7d5a, 0x2e3683db, 0xa827e08e, 0x1aede93d);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
