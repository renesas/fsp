/////////////////////////////////////////////////////////////////////////

// <SC32#7 AES-128 Encryption with ECB Mode(hidden key)>               //
// Procedure number: 42                                                //
// File name      : SC327_p42L.prc                                     //
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
// polling        : 544 + (MAX_CNT/4-1)*44 cycle                       //
// polling access :  20 + (MAX_CNT/4-1)*2  times                       //
// write access   :  74 + (MAX_CNT-4) times                            //
// read  access   :   7 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_aes_private.h"
#include "SCE_ProcCommon.h"

fsp_err_t HW_SCE_AES_128EcbEncryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
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

    WR1_PROG(REG_84H, 0x00004201);
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

    SC327_function001(0x2360a5fa, 0x1c92f272, 0x7419fc2f, 0xeb34bba2);
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

    SC327_function001(0x54e7e19d, 0xdf37ffcb, 0xd41c560d, 0x01dcede1);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00130000);

        SC327_function003(0x5610e6dc, 0xcb3174c2, 0xe759d2ac, 0x1ea7ef41);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }
    else
    {
        SC327_function001(0x27c5c673, 0x609911e5, 0xf826e8d4, 0x395d3ea4);

        // Host DMA Setting(if use DMA)
        // Transfer DATA is 128bits(4words) for each request
        // DMA request count is (MAX_CNT/4) times
        // DMA request signal are WRRDYB_0,RDRDYB_0
        // Input,Output Register is REG_A0H

        WR1_PROG(REG_B0H, 0x300000C0);
        WR1_PROG(REG_A4H, 0x0000888e); // Enable request signals(WRRDYB_0,RDRDYB_0)

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

        SC327_function001(0x89f3a77e, 0x59c7e964, 0x524da947, 0xe3d90410);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1CH, 0x002d0000);

            SC327_function001(0x929b5eb3, 0x72a6df41, 0xfd09bedd, 0x9e3a499a);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_00H, 0x00000113);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC327_function002(0x63bea7f3, 0xcbde19fa, 0xa34eb865, 0x6929030a);
            }
            else
            {
                SC327_function002(0x3ce30d80, 0x664f7971, 0x202a6293, 0xf6d4e8ce);
            }

            SC327_function003(0x3b80f8bb, 0xb8b2ba45, 0xd1818fcb, 0x32c34c47);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SC327_function003(0x4b820dd0, 0x94263634, 0x9323187d, 0x137d1318);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
