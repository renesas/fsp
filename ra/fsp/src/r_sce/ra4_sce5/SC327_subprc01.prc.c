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
// <SC32#7 selftest subprocedure 01>                                   //
// File name     : SC327_subprc01.prc                                  //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_private.h"

void HW_SCE_Initialization1_Subproc1 () {
    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_A4H, 0x00000008);
    WR1_PROG(REG_8CH, 0x00000100);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_7CH, 0x00000001);
    WR1_PROG(REG_14H, 0x10103005);
    WR1_PROG(REG_10H, 0x01234567);
    WR1_PROG(REG_14H, 0x10103015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);

    // 4096 cycle
    WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_A4H, 0x00000008);
    WR1_PROG(REG_8CH, 0x00000102);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_7CH, 0x00000001);
    WR1_PROG(REG_14H, 0x10303005);
    WR1_PROG(REG_10H, 0xefa59826);
    WR1_PROG(REG_14H, 0x10303015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);

    // 4096 cycle
    WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_A4H, 0x00000008);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_8CH, 0x00000100);
    WR1_PROG(REG_7CH, 0x00000001);
    WR1_PROG(REG_78H, 0x00000001);
    WR1_PROG(REG_14H, 0x10303005);
    WR1_PROG(REG_10H, 0x6159465e);
    WR1_PROG(REG_14H, 0x10303015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);

    // 4096 cycle
    WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);
    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_A4H, 0x00000008);
    WR1_PROG(REG_8CH, 0x00000103);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_68H, 0x00000005);
    WR1_PROG(REG_7CH, 0x00000001);
    WR1_PROG(REG_78H, 0x00000005);
    WR1_PROG(REG_14H, 0x70303005);
    WR1_PROG(REG_10H, 0xb785467c);
    WR1_PROG(REG_14H, 0x70303015);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);

    // 4096 cycle
    WAIT_STS(REG_00H, 31, 0);

    WR1_PROG(REG_138H, 0xf597806A);
    WR1_PROG(REG_F0H, 0x00000000);
    WR1_PROG(REG_10CH, 0x00010001);

    WR1_PROG(REG_ECH, 0x00000c00);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x08008802);

    WR1_PROG(REG_80H, 0x00000001);
    WR1_PROG(REG_A4H, 0x00000008);
    WR1_PROG(REG_8CH, 0xfffff1df);
    WR1_PROG(REG_64H, 0x00000008);
    WR1_PROG(REG_68H, 0x00000005);
    WR1_PROG(REG_7CH, 0x00000001);
    WR1_PROG(REG_78H, 0x00000005);
    WR1_PROG(REG_14H, 0x10300007);
    WR1_PROG(REG_10H, 0x9a59a424);
    WR1_PROG(REG_14H, 0x10300017);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);

    // 4096 cycle
    WAIT_STS(REG_00H, 31, 0);
}
