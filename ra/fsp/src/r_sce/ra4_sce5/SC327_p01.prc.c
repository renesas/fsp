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

/////////////////////////////////////////////////////////////////////////
// <SC32#7 SCE Selftest Function1>                                    //
// Procedure number: 01                                                //
// File name      : SC327_p01.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main00                                             //
// End State      : Pass :main01, Fail :stop                           //
// Input Data     : void                                               //
// Output Data    : void                                               //
// Return value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        :  18k cycle                                         //
// polling access :   14 times                                         //
// write access   :  118 times                                         //
// read  access   :    0 times                                         //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "SCE_ProcCommon.h"

/*******************************************************************************************************************//**
 * SCE Selftest Function1
 * @retval FSP_SUCCESS          The operation completed successfully.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_Initialization1 () {
    WR1_PROG(REG_1D0H, 0x00000000);

    HW_SCE_Initialization1_Subproc1(); // `include "SC327_subprc01.prc"

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);

    WR1_PROG(REG_04H, 0x00000001);

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

    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_64H, 0x00000008);

    WR1_PROG(REG_84H, 0x00010101);
    WR1_PROG(REG_13CH, 0x00000F00);

    WR1_PROG(REG_88H, 0x00008001);

    WR1_PROG(REG_104H, 0x00000351);
    SC327_function002(0x0498679a, 0x3ed6ffe9, 0x6b5bb8c8, 0x5c644848);
    WR1_PROG(REG_88H, 0x00000000);

    WR1_PROG(REG_104H, 0x00000351);
    WR1_PROG(REG_A4H, 0x400f380d);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H, 0x7a282626, 0xcf2e49b9, 0x9eabf6cf, 0x0c07203c);

    SC327_function002(0x4fada8e5, 0xf504eed8, 0xff623d27, 0x538c46f5);

    SC327_function001(0x70ee7ad1, 0x40d958ac, 0x7930599c, 0xa6fafb00);

    WR1_PROG(REG_04H, 0x00001001);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_18H, 13, 0))
    {
        WR1_PROG(REG_1BCH, 0x00000020);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_13CH, 0x00000201);

        SC327_function003(0x9df67bfd, 0x4999f372, 0xdb8f0211, 0xa507b601);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
