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
// <SC32#9 initialization1>                                            //
// Procedure number: 01                                                //
// File name      : SC329_p01.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main00                                             //
// End State      : Pass :main01, Fail :stop                           //
// Input Data     : void                                               //
// Output Data    : void                                               //
// Return value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 385k cycle                                         //
// polling access :  111 times                                         //
// write access   : 1005 times                                         //
// read  access   :    0 times                                         //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include  "SCE_ProcCommon.h"

/*******************************************************************************************************************//**
 * SCE Initialization1
 * @retval FSP_SUCCESS          The operation completed successfully.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_Initialization1 () {
    HW_SCE_Initialization1_Subproc1(); // `include "SC329_subprc01.prc"

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);

    WR1_PROG(REG_04H, 0x00000001);
    WR1_PROG(REG_10CH, 0x0000057b);

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

    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_28H, 0x00000001);
    WR1_PROG(REG_7CH, 0x00000001);
    WR1_PROG(REG_64H, 0x00000008);

    WR1_PROG(REG_84H, 0x00010101);
    WR1_PROG(REG_13CH, 0x00000F00);

    WR1_PROG(REG_88H, 0x00008001);

    WR1_PROG(REG_104H, 0x00000352);
    SC32_function002(0x4aa8c12e, 0xe1a0b187, 0x9b270bde, 0x056b5745);
    WR1_PROG(REG_88H, 0x00000000);

    WR1_PROG(REG_104H, 0x00000352);
    WR1_PROG(REG_C4H, 0x000f3a0d);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H, 0x951d9549, 0xc82e9087, 0x2f77a727, 0xc9d1da1a);

    SC32_function002(0xfa6216c2, 0x67538f9b, 0xc37c7123, 0xcf5def2b);

    SC32_function001(0x0aa411ce, 0x8a35340d, 0x8b5a17f7, 0xc49ac19b);

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

        SC32_function003(0x511ebe4c, 0x7d8d5307, 0x34ec725e, 0x82936a4d);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
