/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

//////////////////////////////////////////////////////////////////////
// <SC32#7 AES-256 Encryption with CBC Mode>                        //
// Procedure number: 22                                             //
// File name      : SC327_p22L.prc                                  //
// State Diagram  : main(FSM1)                                      //
// Start State    : main03                                          //
// End State      : main03                                          //
// Input Data     : InData_Key[8]                                   //
// : InData_IV[4]                                                   //
// : InData_Text[MAX_CNT]                                           //
// Output Data    : OutData_Text[MAX_CNT]                           //
// : (MAX_CNT is Multiples of four.)                                //
// OutData_IV[4]                                                    //
// Return Value   : Pass, Fail or Resource_Conflict                 //
// ------------------------------------------------------------------//
// total cycle    : polling + write access + read access            //
// polling        : 404 + (MAX_CNT/4-1)*61 cycle                    //
// polling access :  21 + (MAX_CNT/4-1)*2  times                    //
// write access   :  75 + (MAX_CNT-4) times                         //
// read  access   :  10 + (MAX_CNT-4) times                         //
//////////////////////////////////////////////////////////////////////

#include "hw_sce_aes_private.h"
#include "SCE_ProcCommon.h"

/*******************************************************************************************************************//**
 * AES-256 Encryption with CBC Mode
 *
 * @param[in]  InData_Key      In data key
 * @param[in]  InData_IV       In data iv
 * @param[in]  num_words       The number words
 * @param[in]  InData_Text     In data text
 * @param      OutData_Text    The out data text
 * @param      OutData_IV      The out data iv
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal I/O buffer is not empty.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_AES_256CbcEncrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text,
                                    uint32_t       * OutData_IV)
{
    uint32_t iLoop, MAX_CNT = num_words;

    if (RD1_MASK(REG_1BCH, 0x0000001f) != 0x0000000)
    {
        // Busy now then retry later;
        // Because  1_xxxx other processing box is in duty.
        // x_1xxx resource D is in duty,then retry after you released D.
        // x_x1xx resource C is in duty,then retry after you released C.
        // x_xx1x resource B is in duty,then retry after you released B.
        // x_xxx1 resource A is in duty,then retry after you released A.

        // A,B,C,D: see TrustedSystem datasheet
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00002201);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00130013);

    SC327_function001(0x811f3ef9, 0x4d269387, 0xf9b24c89, 0x41524830);
    WR1_PROG(REG_B0H, 0x10000100);
    WR1_PROG(REG_A4H, 0x00008887);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_Key[0]);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_Key[4]);
    WR1_PROG(REG_B0H, 0x00000000);

    WR1_PROG(REG_A4H, 0x00080805);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC327_function001(0x7cdb31c5, 0x839901fe, 0x8c0b85ad, 0xfe9c22c9);
    WR1_PROG(REG_A4H, 0x00090805);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x00048805);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_IV[0]);
    WR1_PROG(REG_B0H, 0x00000000);

    SC327_function001(0xd0c8a772, 0x1a3b659e, 0x87b5e25e, 0x3ba77f72);

    // Host DMA Setting(if use DMA)
    // Transfer DATA is 128bits(4words) for each request
    // DMA request count is (MAX_CNT/4) times
    // DMA request signal are WRRDYB_0,RDRDYB_0
    // Input,Output Register is REG_A0H

    WR1_PROG(REG_B0H, 0x700000c0);
    WR1_PROG(REG_A4H, 0x00008c9e);     // Enable request signals(WRRDYB_0,RDRDYB_0)

    // if you use DMA, you may release cpu

    // if use polling
    //= ====<polling_start>=====
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_00H, 21, 1);
        WR4_ADDR(REG_A0H, &InData_Text[iLoop]);
        WAIT_STS(REG_00H, 16, 1);
        RD4_ADDR(REG_A0H, &OutData_Text[iLoop - 4]);
    }

    WAIT_STS(REG_00H, 16, 1);
    RD4_ADDR(REG_A0H, &OutData_Text[MAX_CNT - 4]);

    //= ====<polling_end>=====

    WR1_PROG(REG_1CH, 0x002c0000);
    WR1_PROG(REG_1CH, 0x002d0000);
    WR1_PROG(REG_B0H, 0x00000001);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_A4H, 0x00008000);     // Disable request signal(WRRDYB_0,RDRDYB_0)

    SC327_function001(0x5648b1f3, 0xfa3c3115, 0x3b0def02, 0xb13517f1);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1CH, 0x002d0000);

        SC327_function001(0xac360247, 0x7da92ae6, 0x94e21c9a, 0x3b2df0ac);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_00H, 0x00000113);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            SC327_function002(0xf4c7e1a1, 0xc2bf9ffc, 0x84e5c6f1, 0xd9fec101);
        }
        else
        {
            SC327_function002(0x375f840c, 0xb651c4a5, 0x138ecba2, 0x3efef8b1);
        }

        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0x338fa757, 0x02f6b583, 0x60217985, 0xb996a83e);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SC327_function001(0x21123ece, 0xe60f62b7, 0x843a0bc1, 0x4ed8a881);

        WR1_PROG(REG_104H, 0x00000051);
        WR1_PROG(REG_A4H, 0x00000684);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_04H, 0x00000113);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_A0H, &OutData_IV[0]);

        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0xca5e03f8, 0x0921a8ab, 0xe0b1a650, 0xe1c30d67);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
