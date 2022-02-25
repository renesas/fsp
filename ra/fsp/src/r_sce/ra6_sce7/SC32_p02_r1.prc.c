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

/////////////////////////////////////////////////////////////////////////////////////////
// <SC32#2 initialization2>                                                            //
// Procedure number: 02                                                                //
// File name       : SC32_p02_r1.prc                                                   //
// State Diagram   : main(FSM1)                                                        //
// Start State     : main01                                                            //
// End State       : Pass :main02, Retry :main01                                       //
// Input Data      : void                                                              //
// Output Data     : void                                                              //
// Return value    : Pass, Retry, Resource_Conflict                                    //
// -------------------------------------------------------------------------------------//
// total cycle     : polling + write access + read access + Long_Polling               //
// polling         : 1953 cycle + 67ms(MAX)                                            //
// polling access  :   58 times                                                        //
// write access    :  428 times                                                        //
// read  access    :    9 times                                                        //
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

        // A,B,C,D: see Primitive Level Procedures datasheet
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00000201);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00093b8c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x26c7ba56);

    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00070804);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_ECH, 0x3000a9a0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000003);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010020);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x000009ad);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x5f451da4, 0x654b8648, 0x9dd07486, 0x6d2906a2);
    WR1_PROG(REG_ECH, 0x00007c0d);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00600000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (RD1_MASK(REG_1CH, 0xff000000) == 0x00000000)
    {
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000008);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00002008);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x0000901C);

        SC32_function002(0xf57ff76b, 0x35e4f7f4, 0x7e162812, 0x6f0cae24);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000) == 0x01000000)
    {
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000008);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00002008);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x0000901e);

        SC32_function002(0x6dc035f3, 0x38930354, 0x1e03c336, 0x266623eb);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000) == 0x02000000)
    {
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000008);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00002008);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x0000901d);

        SC32_function002(0xac37def2, 0x4aa042cd, 0x44cc106f, 0x6b06baba);
    }

    HW_SCE_Initialization2_Subproc2(); // `include "SC32_subprc02.prc"

    SC32_function001(0xc79e71bd, 0x953c5007, 0x4d7a3d00, 0xc2989b7b);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        SC32_function003(0x52601504, 0x62179af5, 0x755240e7, 0x04665a9a);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_RETRY;
    }
    else
    {
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x0000001c);

        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x01000cc4);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_C4H, 0x41001edd);
        WR1_PROG(REG_00H, 0x00002413);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80040080);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        SC32_function001(0x974fa4a7, 0xf541d0a2, 0xa9176623, 0xa6940bca);
        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x000b0804);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_104H, 0x00000352);
        WR1_PROG(REG_C4H, 0x00070805);
        WAIT_STS(REG_104H, 31, 1);
        WR4_PROG(REG_100H, 0x00000000, 0x00000000, 0x00000000, 0x00000001);

        SC32_function001(0x31360bf9, 0x360457f3, 0xc37f318a, 0x9d1e2ddd);
        WR1_PROG(REG_D0H, 0x00000100);
        WR1_PROG(REG_C4H, 0x0100b7f7);
        WR1_PROG(REG_E0H, 0x81080000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00002823);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_C4H, 0x000b0805);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_C4H, 0x00070805);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        SC32_function001(0x658e5d91, 0xae9595e6, 0xb9dfcd67, 0x0d42d6b5);

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
        SC32_function001(0x92df822b, 0xafec3b77, 0x7429cc5f, 0x5dbd459d);
        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x010d0c04);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        SC32_function001(0x9016b0ff, 0x1f6c08e5, 0x90e03bc7, 0xae893bd7);

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
        SC32_function001(0xc5a139af, 0x5003239f, 0x60f7a180, 0xd9869b33);
        WR1_PROG(REG_104H, 0x00000052);
        WR1_PROG(REG_C4H, 0x01000c84);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_04H, 0x00000213);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_RAM[16 + 0]);

        WR1_PROG(REG_13CH, 0x00000202);

        SC32_function003(0xc92906e6, 0xc1e11c29, 0x359ab41f, 0x38c44c39);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
