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

/////////////////////////////////////////////////////////////////////////////////////////
// <SC32#7 initialization2>                                                            //
// Procedure number: 02                                                                //
// File name       : SC327_p02.prc                                                     //
// State Diagram   : main(FSM1)                                                        //
// Start State     : main01                                                            //
// End State       : Pass :main03, Retry :main01                                       //
// Input Data      : void                                                              //
// Output Data     : void                                                              //
// Return value    : Pass, Retry, Resource_Conflict                                    //
// -------------------------------------------------------------------------------------//
// total cycle     : polling + write access + read access                              //
// polling         :  8784 cycle                                                       //
// polling access  :    20 times                                                       //
// write access    : 1813k times                                                       //
// read  access    :     4 times                                                       //
/////////////////////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "SCE_ProcCommon.h"
uint32_t S_RAM[80];
uint32_t S_HEAP[256];

/*******************************************************************************************************************//**
 * SCE  Initialization2
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal I/O buffer is not empty.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_Initialization2 () {
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

    WR1_PROG(REG_84H, 0x00000201);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_ECH, 0x3000a800);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000003);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010020);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000800);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC327_function001(0x254c7522, 0xe9100820, 0x4339961a, 0x97861969);
    WR1_PROG(REG_ECH, 0x00007c00);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00600000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (RD1_MASK(REG_1CH, 0xff000000) == 0x00000000)
    {
        WR1_PROG(REG_64H, 0x00000008);
        WR1_PROG(REG_64H, 0x0000005C);

        SC327_function002(0xf5e7d55f, 0x39408b60, 0x10dddf1f, 0x9468dc6d);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000) == 0x01000000)
    {
        WR1_PROG(REG_64H, 0x00000008);
        WR1_PROG(REG_64H, 0x0000005e);

        SC327_function002(0x1ddfaf0e, 0xb435d3e8, 0xdeb69041, 0x3ced149d);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000) == 0x02000000)
    {
        WR1_PROG(REG_64H, 0x00000008);
        WR1_PROG(REG_64H, 0x0000005d);

        SC327_function002(0xaa830ffa, 0x171839e7, 0x025e316b, 0xefce669c);
    }

    WR1_PROG(REG_A4H, 0x00040804);
    WR1_PROG(REG_E0H, 0x81010000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00001807);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    HW_SCE_Initialization2_Subproc2(); // `include "SC327_subprc02.prc"
    WAIT_STS(REG_64H, 11, 0);

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00000684);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80010000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008107);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_00H, 0x0000010f);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x00002c00);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC327_function001(0xd400c3d0, 0x05773ea8, 0xe54882f7, 0xf3d87bfb);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        SC327_function003(0xb8a5aa0f, 0xaa93bf73, 0xf37d9ef6, 0x20563ee1);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_RETRY;
    }
    else
    {
        WR1_PROG(REG_64H, 0x00000000);

        SC327_function001(0x48db42b0, 0x9773ccd6, 0xab653f7c, 0xf5f31db2);
        WR1_PROG(REG_104H, 0x00000051);
        WR1_PROG(REG_A4H, 0x00280e84);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_A4H, 0x40013a0c);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0xbeecb97b);

        SC327_function001(0xd0f460ee, 0xd623fa03, 0x5f9f6842, 0xe6b07784);
        WR1_PROG(REG_A4H, 0xc02d063c);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        SC327_function001(0xc04bccac, 0x728a1558, 0x4eb57983, 0xa86214c0);
        WR1_PROG(REG_A4H, 0xc02006bc);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_A4H, 0x00050885);
        WR1_PROG(REG_00H, 0x00001113);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_04H, 0x00000113);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_RAM[4 + 0]);

        WR1_PROG(REG_13CH, 0x00000203);

        SC327_function003(0x5a17a7a3, 0x2560f9b6, 0x00e9922c, 0x8acba7a8);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
