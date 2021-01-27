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
// <SC32#7 AES-128 Encryption with XTS Mode>                           //
// Procedure number: 09                                                //
// File name      : SC327_p09L.prc                                     //
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
// polling        : 1285 cycle                                         //
// polling access :   56 times                                         //
// write access   :  353 times                                         //
// read  access   :   26 times                                         //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_aes_private.h"
#include "SCE_ProcCommon.h"

/*******************************************************************************************************************//**
 * AES-128 Encryption with XTS Mode
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
fsp_err_t HW_SCE_AES_128XtsEncrypt (const uint32_t * InData_Key,
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

    WR1_PROG(REG_84H, 0x00000901);
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

    SC327_function001(0x83b8411d, 0x9ed09fdc, 0x3efb448d, 0x2167ae75);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0xaeea7eb3, 0xb024ad16, 0xbb06974c, 0xd64df5ce);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    SC327_function001(0x7882950f, 0xb4a82370, 0x17eedb66, 0x30341e55);
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

    SC327_function001(0x1ae9fa25, 0xc76c45e8, 0x877a5587, 0x5a82e442);
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

    SC327_function001(0x038739f7, 0xc2f4de0d, 0x704e2336, 0x2445e9fe);
    WR1_PROG(REG_E0H, 0x81010020);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    SC327_function001(0xb2b8d94a, 0x906ac658, 0x2487bc1f, 0xbc7a0fe2);

    // Host DMA Setting(if use DMA)
    // Transfer DATA is 128bits(4words) for each request
    // DMA request count is (Len/32-1) times
    // DMA request signal are WRRDYB_0,RDRDYB_0
    // Input,Output Register is REG_A0H

    WR1_PROG(REG_B0H, 0x300000e0);
    WR1_PROG(REG_A4H, 0x00008dae);     // Enable request signals(WRRDYB_0,RDRDYB_0)

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

    SC327_function001(0x712cca75, 0xe4cf048e, 0x46901c5e, 0x06030fb8);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1CH, 0x002d0000);

        SC327_function001(0xdda5cd4a, 0x97ba7404, 0xfe3016be, 0x9fd0aa86);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_00H, 0x00000113);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            SC327_function002(0x3faa841a, 0xe0832d8f, 0x35062307, 0x229eb0d7);
        }
        else
        {
            SC327_function002(0xfdb45582, 0xd49007a8, 0x17f8d39f, 0xa347aefc);
        }

        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0x6a2bdc0c, 0x00f5a969, 0xe5526473, 0xb4caccb5);
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

        SC327_function001(0x7c55b6f7, 0x66275076, 0xd2aff280, 0x21182b48);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_B0H, 0x10000020);
            WR1_PROG(REG_A4H, 0x00008dad);
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

            SC327_function001(0x46b06c91, 0xbbf9650b, 0xd77ca839, 0xf236361b);
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
                SC327_function002(0x8a859e75, 0x68c1c256, 0x94a947d9, 0x2d1bc533);
            }

            WR1_PROG(REG_ECH, 0x38000c21);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            WR1_PROG(REG_1CH, 0x00402000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x0000b4e0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000010);
            WR1_PROG(REG_1D0H, 0x00000000);
            SC327_function001(0x56f5146f, 0xfc39496a, 0x163d1665, 0xb6fafcf6);
            WR1_PROG(REG_B0H, 0x00000020);
            WR1_PROG(REG_A4H, 0x00008dad);
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
                SC327_function002(0x2fcf8a86, 0x659d9db6, 0xbaed39d9, 0x4cf447a9);
            }

            WR1_PROG(REG_ECH, 0x38000c63);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            WR1_PROG(REG_1CH, 0x00402000);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC327_function001(0x4c4aeafd, 0x5f6a2968, 0x5deea3ab, 0xd5c03fd5);
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

            SC327_function002(0xde08bdb4, 0xd3aecc98, 0xa350817c, 0x18ae70a9);
        }
        else
        {
            SC327_function001(0x1a51d556, 0x4bf43541, 0xaae28b43, 0x00198a66);
            WR1_PROG(REG_B0H, 0x10000020);
            WR1_PROG(REG_A4H, 0x00008dad);
            WAIT_STS(REG_00H, 21, 1);
            WR4_ADDR(REG_A0H, &InData_Text[iLoop]);
            WR1_PROG(REG_B0H, 0x00000000);

            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_Text[iLoop]);

            SC327_function002(0xdef9d705, 0x21f4e321, 0xfda1b530, 0x24eb3039);
        }

        SC327_function001(0xfab94b60, 0x3d878052, 0x5a4138d1, 0xa401928c);
        WR1_PROG(REG_104H, 0x00000051);
        WR1_PROG(REG_A4H, 0x0000548c);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00000000);

        WR1_PROG(REG_04H, 0x00000113);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_A0H, &OutData_IV[0]);

        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0x6f878d54, 0x45b58c64, 0x1025c66a, 0x0ebcc6b7);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
