/////////////////////////////////////////////////////////////////////////

// <SC32#2 AES-256 Encryption with ECB Mode(hidden key)>               //
// Procedure number: 52                                                //
// File name      : SC32_p52L.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_KeyIndex[13]                                //
// : InData_Text[MAX_CNT]                               //
// Output Data    : OutData_Text[MAX_CNT]                              //
// : (MAX_CNT is Multiples of four.)                    //
// Return Value   : Pass, Fail, HRK_Invalid_Index or Resource_Conflict //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 205 + (MAX_CNT/4-1)*11 cycle                       //
// polling access :  20 + (MAX_CNT/4-1)*2  times                       //
// write access   :  76 + (MAX_CNT-4) times                            //
// read  access   :   4 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_aes_private.h"

fsp_err_t HW_SCE_AES_256EcbEncryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t   num_words,
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

        // A,B,C,D: see Primitive Level Procedures datasheet
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00005201);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00130013);

    WR1_PROG(REG_1CH, 0x00000081);
    WR1_PROG(REG_A4H, 0x200c3b0c);
    WAIT_STS(REG_00H, 21, 1);
    WR1_ADDR(REG_A0H, &InData_KeyIndex[0]);

    WR1_PROG(REG_A4H, 0x000c0b0c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x615e8e97);

    SC32_function001(0x9e98680c, 0x281d09ea, 0xfd53669f, 0x3e063dfe);
    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x02f8073d);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[1]);

    SC32_function001(0xbf59dbec, 0xdcaa2d7b, 0xab985d75, 0xd1faa5fc);
    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x00f9073d);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[5]);

    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x000007bd);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[9]);

    WR1_PROG(REG_A4H, 0x00900c45);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0x30e5da99, 0x6531fcd0, 0x053979e2, 0xcd2a7324);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00130000);

        SC32_function003(0x5376d8c2, 0x20a3e5c9, 0x7e75d29c, 0x91d3d8fb);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }
    else
    {
        SC32_function001(0xf6fdb447, 0x705fd5df, 0x8a3bfe8d, 0x4b3f7ec2);

        // Host DMA Setting(if use DMA)
        // Transfer DATA is 128bits(4words) for each request
        // DMA request count is (MAX_CNT/4) times
        // DMA request signal are WRRDYB_0,RDRDYB_0
        // Input,Output Register is REG_A0H

        WR1_PROG(REG_B0H, 0x700000C0);
        WR1_PROG(REG_A4H, 0x00008a86); // Enable request signals(WRRDYB_0,RDRDYB_0)

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

        SC32_function001(0xedf4a213, 0x3f01ea91, 0xcf8d6fbf, 0x904b52f9);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function003(0xc5715492, 0xe3f53d8e, 0xab42df19, 0xea2fbf70);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SC32_function003(0x6e676e47, 0xea33949e, 0x5123f9e7, 0x3bdd0e12);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
