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
// <SC32#7 AES-128 Decryption with XTS Mode>                           //
// Procedure number: 10                                                //
// File name      : SC327_p10L.prc                                     //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Key[8]                                      //
// : InData_IV[4]                                       //
// : InData_Text[Len] (Text || 128 bit unit 0 padding)  //
// : (Len should be multiples of 4.)                    //
// : InData_Len[1]    (bit length of Text)              //
// Output Data    : OutData_Text[Len]                                  //
// : OutData_IV[4]                                      //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// (when InData_Len is 416bit)                                         //
// polling        : 1341 cycle                                         //
// polling access :   59 times                                         //
// write access   :  363 times                                         //
// read  access   :   26 times                                         //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_aes_private.h"
#include "SCE_ProcCommon.h"

/*******************************************************************************************************************//**
 * AES-128 Decryption with XTS Mode
 *
 * @param[in]  InData_Key      In data key
 * @param[in]  InData_IV       In data iv
 * @param[in]  InData_Len      In data length
 * @param[in]  InData_Text     In data text
 * @param      OutData_Text    The out data text
 * @param      OutData_IV      The out data iv
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict occurred.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal I/O buffer is not empty.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_AES_128XtsDecrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t * InData_Len,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text,
                                    uint32_t       * OutData_IV)
{
    uint32_t iLoop, jLoop;

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

    WR1_PROG(REG_84H, 0x00001001);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00130013);

    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x00008884);
    WR1_PROG(REG_E0H, 0x80040000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WAIT_STS(REG_00H, 21, 1);
    WR1_ADDR(REG_A0H, &InData_Len[0]);
    WR1_PROG(REG_00H, 0x00008113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_B0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x38008800);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00260000);

    SC327_function001(0xd33c6dad, 0xf560d2f9, 0x30fb400d, 0x720f198d);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0x7c59369f, 0x2d0f4db1, 0x7cea4aec, 0x45bc5689);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    SC327_function001(0xaaa44738, 0x7ec77b4e, 0x26707aba, 0x0e0ecd71);
    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x00008885);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_Key[4]);
    WR1_PROG(REG_B0H, 0x00000000);

    WR1_PROG(REG_A4H, 0x00090805);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x0004980d);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_IV[0]);
    WR1_PROG(REG_B0H, 0x00000000);

    SC327_function001(0xf8acfa6c, 0x75cd498b, 0x57d4860a, 0xd7ac87aa);
    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x00008885);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_Key[0]);
    WR1_PROG(REG_B0H, 0x00000000);

    WR1_PROG(REG_A4H, 0x00080805);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x00003420);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00076821);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00026c21);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC327_function001(0xecaa8964, 0x4e6ea92e, 0x8270a67d, 0xab390fa9);
    WR1_PROG(REG_E0H, 0x81010020);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    SC327_function001(0xf17c939a, 0xc4a93d4b, 0x4dd1efb4, 0x8a633308);

    // Host DMA Setting(if use DMA)
    // Transfer DATA is 128bits(4words) for each request
    // DMA request count is (Len/32-1) times
    // DMA request signal are WRRDYB_0,RDRDYB_0
    // Input,Output Register is REG_A0H

    WR1_PROG(REG_B0H, 0x300000e0);
    WR1_PROG(REG_A4H, 0x0000cdae);     // Enable request signals(WRRDYB_0,RDRDYB_0)

    // if you use DMA, you may release cpu

    // if use polling
    //= ====<polling_start>=====
    iLoop = 0;
    if (S_RAM[0] - 4 != 0)
    {
        WAIT_STS(REG_00H, 21, 1);
        WR4_ADDR(REG_A0H, &InData_Text[0]);
        for (iLoop = 4; iLoop < S_RAM[0] - 4; iLoop = iLoop + 4)
        {
            WAIT_STS(REG_00H, 21, 1);
            WR4_ADDR(REG_A0H, &InData_Text[iLoop]);
            WAIT_STS(REG_00H, 16, 1);
            RD4_ADDR(REG_A0H, &OutData_Text[iLoop - 4]);
        }

        WAIT_STS(REG_00H, 16, 1);
        RD4_ADDR(REG_A0H, &OutData_Text[iLoop - 4]);
    }

    //= ====<polling_end>=====

    WR1_PROG(REG_1CH, 0x002c0000);
    WR1_PROG(REG_1CH, 0x002d0000);
    WR1_PROG(REG_B0H, 0x00000001);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_A4H, 0x00008000);     // Disable request signal(WRRDYB_0,RDRDYB_0)

    SC327_function001(0xca2074bc, 0x6d1c0025, 0x1e4648d5, 0x415fc1e9);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1CH, 0x002d0000);

        SC327_function001(0xccf9a68b, 0xe07a3337, 0xf91ea7d2, 0x81a7c691);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_00H, 0x00000113);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            SC327_function002(0x212ec3f7, 0x94b1ffe0, 0xff8286e6, 0x0b1b2bdf);
        }
        else
        {
            SC327_function002(0x9b79244e, 0x2162decb, 0x3cc72174, 0x94d8caf7);
        }

        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0xadec9fa5, 0x8f1a0056, 0x03ee4d36, 0x702f427b);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38008c00);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x0000007f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00A60000);

        SC327_function001(0xf3f16df6, 0x9c77b04f, 0xd08a3662, 0xee56f3b0);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00050604);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_B0H, 0x00000020);
            WR1_PROG(REG_A4H, 0x0000cd2c);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_B0H, 0x10000020);
            WR1_PROG(REG_A4H, 0x0000cdad);
            WAIT_STS(REG_00H, 21, 1);
            WR4_ADDR(REG_A0H, &InData_Text[iLoop]);
            WR1_PROG(REG_B0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x000008c6);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x80840006);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00008113);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_ECH, 0x0000b4e0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000010);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_B0H, 0x10000000);
            WR1_PROG(REG_A4H, 0x00008885);
            WR1_PROG(REG_E0H, 0x80840007);
            WR1_PROG(REG_1D0H, 0x00000000);
            WAIT_STS(REG_00H, 21, 1);
            WR4_ADDR(REG_A0H, &InData_Text[iLoop + 4]);
            WR1_PROG(REG_00H, 0x00008113);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);
            WR1_PROG(REG_B0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x000034a0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x000368a5);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00008ca0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0000000c);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x000024c5);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x000024e5);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00003826);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00003847);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00003460);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00008c60);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0000001f);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x0000b480);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0xffffffff);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00004403);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00007484);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00000c24);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00001484);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00000c44);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00001041);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00003c47);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00003440);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00008c40);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0000007f);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x38008c40);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0000001f);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x1000a440);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000020);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x0000b420);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000080);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002822);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00056821);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00003461);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC327_function001(0x09ac8f59, 0xdd1c15c8, 0x945265cb, 0xb4602c15);
            WR1_PROG(REG_E0H, 0x81010020);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_04H, 0x00000607);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);

            for (jLoop = 0; jLoop < S_RAM[0]; jLoop = jLoop + 1)
            {
                WR1_PROG(REG_ECH, 0x0000a4c0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x0000a4e0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x00003846);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00003c47);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x00003020);
                WR1_PROG(REG_1D0H, 0x00000000);
                SC327_function002(0x353a20cb, 0xb9d0d7fc, 0x93438040, 0xce7d58c4);
            }

            WR1_PROG(REG_ECH, 0x38000c21);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            WR1_PROG(REG_1CH, 0x00402000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00040644);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_ECH, 0x0000b4e0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000010);
            WR1_PROG(REG_1D0H, 0x00000000);
            SC327_function001(0x0fe0aaf0, 0xcd071cee, 0x264fc655, 0x0000bf19);
            WR1_PROG(REG_B0H, 0x00000020);
            WR1_PROG(REG_A4H, 0x0000cdad);
            WR1_PROG(REG_E0H, 0x81840007);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00001813);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_Text[iLoop]);

            WR1_PROG(REG_ECH, 0x000008c6);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x000024c5);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00003826);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00000c24);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00003c26);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00000842);
            WR1_PROG(REG_1D0H, 0x00000000);

            for (jLoop = 0; jLoop < S_RAM[0]; jLoop = jLoop + 1)
            {
                WR1_PROG(REG_ECH, 0x0000a4c0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x00003c46);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x00003060);
                WR1_PROG(REG_1D0H, 0x00000000);
                SC327_function002(0x97da26a1, 0xb35c99b3, 0x02bb6112, 0x364a0471);
            }

            WR1_PROG(REG_ECH, 0x38000c63);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            WR1_PROG(REG_1CH, 0x00402000);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC327_function001(0x534d480e, 0x500500e1, 0x80bc2dbf, 0x1158349e);
            WR1_PROG(REG_ECH, 0x000008c6);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x81840006);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_A4H, 0x00000885);
            WR1_PROG(REG_00H, 0x00001813);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);
            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_Text[iLoop + 4]);

            SC327_function002(0x84df55e4, 0x1271f5ca, 0x672d6950, 0x1ac426c3);
        }
        else
        {
            SC327_function001(0x997138c8, 0xdc3e97f2, 0x43cc6d04, 0xd6b240a8);
            WR1_PROG(REG_B0H, 0x10000020);
            WR1_PROG(REG_A4H, 0x0000cdad);
            WAIT_STS(REG_00H, 21, 1);
            WR4_ADDR(REG_A0H, &InData_Text[iLoop]);
            WR1_PROG(REG_B0H, 0x00000000);

            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_Text[iLoop]);

            SC327_function002(0x649b96bb, 0x05e809ec, 0xb82212f7, 0x93b98c30);
        }

        SC327_function001(0xb032da9a, 0x6f716bc7, 0x760ab37c, 0x895418ca);
        WR1_PROG(REG_104H, 0x00000051);
        WR1_PROG(REG_A4H, 0x0000548c);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_04H, 0x00000113);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_A0H, &OutData_IV[0]);

        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0xac80e4eb, 0xc39e787c, 0x4643d2ec, 0x97b497c3);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
