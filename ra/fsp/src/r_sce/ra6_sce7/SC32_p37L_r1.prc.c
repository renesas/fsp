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

// <SC32#2 RSA2048 Encryption with Public Key>                         //
// Procedure number: 37                                                //
// File name      : SC32_p37L_r1.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Text[64] (text)                             //
// : InData_PublicKey[1] (public exponent)              //
// : InData_N[64] (public modulus)                      //
// Output Data    : OutData_Text[64] (Cipher Text)                     //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// LONG_polling1  : 32.9k cycle                                        //
// LONG_polling2  : 32.9k cycle                                        //
// total cycle    : LONG_polling + polling + write access + read access//
// polling        : 114.2k cycle                                       //
// polling access :    329 times                                       //
// write access   :    989 times                                       //
// read  access   :     98 times                                       //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_rsa_private.h"
#include  "SCE_ProcCommon.h"

// 2048-bit RSA

/*******************************************************************************************************************//**
 *  Encryption using 2048-bit RSA public key
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * RSA2048 Encryption with Public Key
 *
 * @param[in]  InData_Text       InData_Text pointer to 64-word buffer containing message to be encrypted
 * @param[in]  InData_PublicKey  InData_PublicKey pointer to 1-word buffer 2048-bit RSA public exponent (`e`)
 * @param[in]  InData_N          InData_N pointer to 64-word buffer containing 2048-bit RSA public modulus (`N`)
 * @param      OutData_Text      TOutData_Text result of public-key encryption is stored in the buffer pointed to by `OutData_R`
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal I/O buffer is not empty.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RSA_2048PublicKeyEncrypt (const uint32_t * InData_Text,
                                           const uint32_t * InData_PublicKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text)
{
    uint32_t jLoop, lLoop;

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

    WR1_PROG(REG_84H, 0x00003701);
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

    SC32_function001(0xcf4d109d, 0x0ec560b9, 0x5ef2d673, 0xa87d2c20);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x04066a95, 0x571ef180, 0x31d08ff9, 0x9b88db8b);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_18H, 0x00000004);
        WR1_PROG(REG_24H, 0x00005004);
        WAIT_STS(REG_18H, 10, 0);      // No.1  You may release cpu resources because of polling long time(Long Polling)
        WR1_PROG(REG_24H, 0x00008404);
        WAIT_STS(REG_18H, 10, 0);      // No.2  You may release cpu resources because of polling long time(Long Polling)
        WR1_PROG(REG_18H, 0x00000000);

        WR1_PROG(REG_1CH, 0x00000081);
        WR1_PROG(REG_C4H, 0x00000884);
        WAIT_STS(REG_00H, 22, 1);
        WR1_ADDR(REG_C0H, &InData_PublicKey[0]);
        WR1_PROG(REG_E0H, 0x80010000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008207);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_00H, 0x0000020f);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000020);
        WR1_PROG(REG_1D0H, 0x00000000);
        for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x000033e0);
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

            SC32_function001(0x2d429169, 0x094b29b0, 0x0a3efadb, 0xd384f669);
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

                SC32_function002(0x6d3cc486, 0xb86514bb, 0x02436901, 0x09a26999);
            }
            else
            {
                SC32_function002(0xecdcd2f3, 0xc2808ff0, 0x3da82de9, 0x4b84cc5e);
            }
        }

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

        SC32_function001(0x32750fa3, 0x06fd5e73, 0x68143c68, 0xc695071a);
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

        SC32_function003(0x080e6830, 0x5f45578b, 0x9f39eb30, 0xafe3ab49);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
