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
// <SC32#9 selftest subprocedure 01>                                   //
// File name     : SC329_subprc01.prc                                  //
/////////////////////////////////////////////////////////////////////////

#include  "SCE_ProcCommon.h"
#include "hw_sce_private.h"

void HW_SCE_Initialization1_Subproc1 () {
    uint32_t iLoop;

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_64H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_14H, 0x10300007);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_6CH, 0x64564f2d);
    WR1_PROG(REG_64H, 0x0000007B);
    WR1_PROG(REG_68H, 0x00000007);
    WR1_PROG(REG_10H, 0x3e5c6a49);
    WR1_PROG(REG_14H, 0x10300017);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(1024);                   // TEST_BUSY WAIT 0 //1024 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_14H, 0x10300007);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_6CH, 0x64564f2d);
    WR1_PROG(REG_64H, 0x0000007B);
    WR1_PROG(REG_68H, 0x00003807);
    WR1_PROG(REG_14H, 0x10303017);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(4096);                   // TEST_BUSY WAIT 0 //4096 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_7CH, 0x00000001);
    WR1_PROG(REG_74H, 0x00000008);
    WR1_PROG(REG_134H, 0x91dfe669);
    WR1_PROG(REG_78H, 0x00000106);
    WR1_PROG(REG_14H, 0x00100005);
    WR1_PROG(REG_14H, 0x00100015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(1024);                   // TEST_BUSY WAIT 0 //1024 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_80H, 0x00000000);
    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_94H, 0xc2282709);
    WR1_PROG(REG_8CH, 0x0000818B);
    WR1_PROG(REG_14H, 0x00001005);
    WR1_PROG(REG_14H, 0x00001015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(64);                     // TEST_BUSY WAIT 0 //64 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_28H, 0x00000001);
    WR1_PROG(REG_28H, 0x00Bf0001);
    WR1_PROG(REG_4CH, 0xcb749264);

    WR1_PROG(REG_24H, 0x00008080);
    WAIT_STS(REG_24H, 20, 0);
    WR1_PROG(REG_24H, 0x00004080);
    WAIT_STS(REG_24H, 20, 0);
    WR1_PROG(REG_24H, 0x0000C080);
    WAIT_STS(REG_24H, 20, 0);
    WR1_PROG(REG_2CH, 0x00000050);
    WAIT_STS(REG_00H, 23, 1);
    WR1_PROG(REG_20H, 0xFFFFFFFF);

    WR1_PROG(REG_3CH, 0x00210343);
    WR1_PROG(REG_14H, 0x00001005);
    WR1_PROG(REG_14H, 0x00001015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(64);                     // TEST_BUSY WAIT 0 //64 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_28H, 0x00000001);
    WR1_PROG(REG_28H, 0xfdBf0001);
    WR1_PROG(REG_3CH, 0x00211B4B);
    WR1_PROG(REG_14H, 0x00301005);
    WR1_PROG(REG_14H, 0x00301015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(64);                     // TEST_BUSY WAIT 0 //64 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_28H, 0x00000001);
    WR1_PROG(REG_28H, 0xfeBf0001);
    WR1_PROG(REG_3CH, 0x0021134B);
    WR1_PROG(REG_14H, 0x00101005);
    WR1_PROG(REG_14H, 0x00101015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(64);                     // TEST_BUSY WAIT 0 //64 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_00H, 0x0000E14D);
    WR1_PROG(REG_04H, 0x00400E40);
    WR1_PROG(REG_14H, 0xa1f03007);
    WR1_PROG(REG_14H, 0xa1f03017);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    SCE_DELAY(4096);                   // TEST_BUSY WAIT 0 //4096 cycle
    // WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_64H, 0x00000000);

    for (iLoop = 0; iLoop < 15; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_138H, 0xf597806A);
        WR1_PROG(REG_F0H, 0x00000000);
        WR1_PROG(REG_10CH, 0x00010001);
        WR1_PROG(REG_80H, 0x00000001);
        WR1_PROG(REG_8CH, 0x0000800f);
        WR1_PROG(REG_14H, 0x00003007);
        WR1_PROG(REG_14H, 0x00003017);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        SCE_DELAY(4096);               // TEST_BUSY WAIT 0 //4096 cycle
        // WAIT_STS(REG_00H, 31, 0);
    }

    for (iLoop = 0; iLoop < 15; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_138H, 0xf597806A);
        WR1_PROG(REG_F0H, 0x00000000);
        WR1_PROG(REG_10CH, 0x00010001);
        WR1_PROG(REG_80H, 0x00000001);
        WR1_PROG(REG_8CH, 0x0000870f);
        WR1_PROG(REG_14H, 0xc0703007);
        WR1_PROG(REG_14H, 0xc0703017);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        SCE_DELAY(4096);               // TEST_BUSY WAIT 0 //4096 cycle
        // WAIT_STS(REG_00H, 31, 0);
    }

    for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_138H, 0xf597806A);
        WR1_PROG(REG_F0H, 0x00000000);
        WR1_PROG(REG_10CH, 0x00010001);
        WR1_PROG(REG_28H, 0x00000001);
        WR1_PROG(REG_28H, 0x00Bf0001);
        WR1_PROG(REG_3CH, 0x000c24bf);
        WR1_PROG(REG_14H, 0xe6f03007);
        WR1_PROG(REG_14H, 0xe6f03017);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        SCE_DELAY(4096);               // TEST_BUSY WAIT 0 //4096 cycle
        // WAIT_STS(REG_00H, 31, 0);
    }

    for (iLoop = 0; iLoop < 15; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_138H, 0xf597806A);
        WR1_PROG(REG_F0H, 0x00000000);
        WR1_PROG(REG_10CH, 0x00010001);
        WR1_PROG(REG_28H, 0x00000001);
        WR1_PROG(REG_28H, 0xfdBf0001);
        WR1_PROG(REG_3CH, 0x00211B4B);
        WR1_PROG(REG_14H, 0x00303007);
        WR1_PROG(REG_14H, 0x00303017);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        SCE_DELAY(4096);               // TEST_BUSY WAIT 0 //4096 cycle
        // WAIT_STS(REG_00H, 31, 0);
    }

    for (iLoop = 0; iLoop < 15; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_138H, 0xf597806A);
        WR1_PROG(REG_F0H, 0x00000000);
        WR1_PROG(REG_10CH, 0x00010001);
        WR1_PROG(REG_28H, 0x00000001);
        WR1_PROG(REG_28H, 0xfeBf0001);
        WR1_PROG(REG_3CH, 0x00211B4B);
        WR1_PROG(REG_14H, 0x00303007);
        WR1_PROG(REG_14H, 0x00303017);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        SCE_DELAY(4096);               // TEST_BUSY WAIT 0 //4096 cycle
        // WAIT_STS(REG_00H, 31, 0);
    }

    for (iLoop = 0; iLoop < 15; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_138H, 0xf597806A);
        WR1_PROG(REG_F0H, 0x00000000);
        WR1_PROG(REG_10CH, 0x00010001);
        WR1_PROG(REG_7CH, 0x00000001);
        WR1_PROG(REG_7CH, 0x00000011);
        WR1_PROG(REG_78H, 0x0000001f);
        WR1_PROG(REG_14H, 0x00303007);
        WR1_PROG(REG_14H, 0x00303017);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        SCE_DELAY(4096);               // TEST_BUSY WAIT 0 //4096 cycle
        // WAIT_STS(REG_00H, 31, 0);
    }
}
