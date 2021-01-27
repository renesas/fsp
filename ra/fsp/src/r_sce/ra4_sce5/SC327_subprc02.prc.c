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

//////////////////////////////////////////////////////////////////////////
// <SC32#7 randum number inspection subprocedure 02>                    //
// File name            : SC327_subprc02.prc                            //
//////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_private.h"

void HW_SCE_Initialization2_Subproc2 (void) {
    uint32_t iLoop, jLoop, kLoop;

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x40083a8c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x4a2d0cef);

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x00010804);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000800);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80880000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008023);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b460);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000002);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b4e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00400003);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_A4H, 0xc0200c1e);

    for (iLoop = 0; iLoop < 1024; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_E0H, 0x80010020);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008407);
        WAIT_STS(REG_00H, 25, 0);      // 0.33ms
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_ECH, 0x000034c1);
        WR1_PROG(REG_1D0H, 0x00000000);
        for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x0c016cc6);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x100008c7);
            WR1_PROG(REG_1D0H, 0x00000000);
        }

        WR1_PROG(REG_E0H, 0x810100c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00001807);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        for (jLoop = 0; jLoop < 8; jLoop = jLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x00003441);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00008c40);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0000000f);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00000800);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000884);
            WR1_PROG(REG_1D0H, 0x00000000);
            for (kLoop = 0; kLoop < 16; kLoop = kLoop + 1)
            {
                WR1_PROG(REG_ECH, 0x010038a0);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x38000844);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x10002ca0);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x01003ca0);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x00002403);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00002c80);
                WR1_PROG(REG_1D0H, 0x00000000);
            }

            WR1_PROG(REG_ECH, 0x00046821);
            WR1_PROG(REG_1D0H, 0x00000000);
        }
    }

    WAIT_STS(REG_A8H, 6, 0);
    WR1_PROG(REG_A4H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00000400);

    WR1_PROG(REG_ECH, 0x00000821);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b480);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000B50);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000800);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000863);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x000008c6);
    WR1_PROG(REG_1D0H, 0x00000000);
    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_ECH, 0x010038a0);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x30002885);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00070020);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00005023);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000080);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x000024c5);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x0000a400);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000002);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00002c60);
        WR1_PROG(REG_1D0H, 0x00000000);
    }

    WR1_PROG(REG_ECH, 0x380088c0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00002000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00260000);

    WR1_PROG(REG_1CH, 0x00402000);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x38008820);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00A60000);
}
