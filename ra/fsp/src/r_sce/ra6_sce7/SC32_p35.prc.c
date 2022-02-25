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

// <SC32#2 SHA-256 Message Digest Generation>                          //
// Procedure number: 35                                                //
// File name      : SC32_p35L.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_SHA256InitVal[8]                            //
// : (First:initial hash value of SHA-256.                             //
// :  Second to last: previous Message Digest)                         //
// : InData_PaddedMsg[MAX_CNT]                                         //
// : (MAX_CNT is Multiples of sixteen.)                                //
// : (total InData_PaddedMsg =                                         //
// :    Message||stop bit||0padding||Message length)                   //
// Output Data    : OutData_MsgDigest[8]                               //
// Return Value   : Pass or Resource_Conflict                          //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// (when Padded Message is 8KByte)                                     //
// polling        : 6722 cycle                                         //
// polling access :  137 cycle                                         //
// write access   : 2084 times                                         //
// read  access   :    8 times                                         //
/////////////////////////////////////////////////////////////////////////

#include  "SCE_ProcCommon.h"
#include "hw_sce_hash_private.h"
#include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * SHA-256 Message Digest Generation
 *
 * @param[in]  p_source        The source
 * @param[in]  num_words       The number words
 * @param      p_digest        The digest
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_SHA256_UpdateHash (const uint32_t * p_source, const uint32_t num_words, uint32_t * p_digest)
{
    uint32_t         iLoop, MAX_CNT = num_words;
    uint32_t       * InData_SHA256InitVal = p_digest;
    const uint32_t * InData_PaddedMsg     = p_source;
    uint32_t       * OutData_MsgDigest    = p_digest;
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

    WR1_PROG(REG_84H, 0x00003501);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00090009);

    WR1_PROG(REG_7CH, 0x00000011);

    WR1_PROG(REG_1CH, 0x00000088);
    WR1_PROG(REG_74H, 0x00000004);
    WAIT_STS(REG_00H, 24, 1);
    WR8_ADDR(REG_70H, &InData_SHA256InitVal[0]);

    // Host DMA Setting(if use DMA)
    // Transfer DATA is 512bits(16words) for each time(Depend on DMA controller)
    // DMA request count is (MAX_CNT/16) times
    // DMA request signal is WRRDYB_4
    // In/Out Register is REG_70H

    WR1_PROG(REG_74H, 0x08000012);     // Enable request signals(WRRDYB_4)

    // if use DMA you may release cpu until Transfer finished
    // if use polling
    //= ====<polling_start>=====
    for (iLoop = 0; iLoop < MAX_CNT; iLoop = iLoop + 16)
    {
        WAIT_STS(REG_00H, 24, 1);
        WR16_ADDR(REG_70H, &InData_PaddedMsg[0 + iLoop]);
    }

    //= ====<polling_end>=====
    WR1_PROG(REG_74H, 0x00000080);     // Disable request signals(WRRDYB_4)
    WAIT_STS(REG_74H, 18, 0);
    WR1_PROG(REG_74H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00001600);

    SC32_function001(0xb8c1f847, 0xecfd21f6, 0x5ee28e30, 0x8e86b979);
    WR1_PROG(REG_74H, 0x00000008);
    WR1_PROG(REG_04H, 0x00000523);
    WAIT_STS(REG_04H, 30, 1);
    RD8_ADDR(REG_70H, &OutData_MsgDigest[0]);

    WR1_PROG(REG_1C0H, 0x00090000);

    SC32_function003(0xab5185b6, 0xe50df1bf, 0x283574d1, 0x83114556);

    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
