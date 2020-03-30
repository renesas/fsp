/////////////////////////////////////////////////////////////////////////

// <SC32#7 AES-128 Decryption with ECB Mode(hidden key)>               //
// Procedure number: 43                                                //
// File name      : SC327_p43L.prc                                     //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_KeyIndex[9]                                 //
// : InData_Text[MAX_CNT]                               //
// Output Data    : OutData_Text[MAX_CNT]                              //
// : (MAX_CNT is Multiples of four.)                    //
// Return Value   : Pass, Fail, HRK_Invalid_Index or Resource_Conflict //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 588 + (MAX_CNT/4-1)*44 cycle                       //
// polling access :  20 + (MAX_CNT/4-1)*2  times                       //
// write access   :  74 + (MAX_CNT-4) times                            //
// read  access   :   7 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_aes_private.h"
#include "SCE_ProcCommon.h"

fsp_err_t HW_SCE_AES_128EcbDecryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     uint32_t         num_words,
                                                     const uint32_t * InData_Text,
                                                     uint32_t       * OutData_Text)
{
    uint32_t iLoop, MAX_CNT = num_words;

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

    WR1_PROG(REG_84H, 0x00004301);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00130013);

    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x00008884);
    WAIT_STS(REG_00H, 21, 1);
    WR1_ADDR(REG_A0H, &InData_KeyIndex[0]);
    WR1_PROG(REG_B0H, 0x00000000);

    WR1_PROG(REG_A4H, 0x600c3a0d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_A4H, 0x400c0a0c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x4e2279db);

    SC327_function001(0x2ecf2819, 0xd2728eec, 0x82d716c3, 0xb7a2cbf4);
    WR1_PROG(REG_B0H, 0x10000100);
    WR1_PROG(REG_A4H, 0x00008887);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[1]);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[5]);
    WR1_PROG(REG_B0H, 0x00000000);

    WR1_PROG(REG_A4H, 0x42f8063d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_A4H, 0x400086bd);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_A4H, 0x00900c45);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC327_function001(0x93c7a38a, 0xa2486ad3, 0x8d49920b, 0xfa8190d6);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0xc0bd8f8c, 0x4cdc8050, 0xa9aa262c, 0x5066819a);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }
    else
    {
        SC327_function001(0xbfdbc84a, 0x1d187e35, 0x27b362ac, 0xf45ff2a1);

        // Host DMA Setting(if use DMA)
        // Transfer DATA is 128bits(4words) for each request
        // DMA request count is (MAX_CNT/4) times
        // DMA request signal are WRRDYB_0,RDRDYB_0
        // Input,Output Register is REG_A0H

        WR1_PROG(REG_B0H, 0x300000C0);
        WR1_PROG(REG_A4H, 0x0000c88e); // Enable request signals(WRRDYB_0,RDRDYB_0)

        // if you use DMA, you may release cpu

        // if use polling
        //= ====<polling_start>=====
        WAIT_STS(REG_00H, 21, 1);
        WR4_ADDR(REG_A0H, &InData_Text[0]);
        for (iLoop = 4; iLoop < MAX_CNT; iLoop = iLoop + 4)
        {
            WAIT_STS(REG_00H, 21, 1);
            WR4_ADDR(REG_A0H, &InData_Text[iLoop]);
            WAIT_STS(REG_00H, 16, 1);
            RD4_ADDR(REG_A0H, &OutData_Text[iLoop - 4]);
        }

        WAIT_STS(REG_00H, 16, 1);
        RD4_ADDR(REG_A0H, &OutData_Text[MAX_CNT - 4]);

        //= ====<polling_end>=====

        WR1_PROG(REG_1CH, 0x002c0000);
        WR1_PROG(REG_1CH, 0x002d0000);
        WR1_PROG(REG_B0H, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_A4H, 0x00008000); // Disable request signal(WRRDYB_0,RDRDYB_0)

        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function001(0x7828be39, 0xba079f71, 0x179ee711, 0x39b3c10e);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1CH, 0x002d0000);

            SC327_function001(0x45e0cf2f, 0xf5d0fec1, 0x39abad15, 0x2a94a2b7);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_00H, 0x00000113);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC327_function002(0x29be68ab, 0xb36eb1bc, 0xe019a681, 0x634fb951);
            }
            else
            {
                SC327_function002(0x228ec9cc, 0x17c70328, 0xb6e3131e, 0x6c2a45d1);
            }

            SC327_function003(0xbc599192, 0x7b8946c3, 0x2425e6a1, 0xf8bf466f);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SC327_function003(0x3cce9ef7, 0xc2d20f6f, 0x31c0cc7f, 0xedfaa4a1);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
