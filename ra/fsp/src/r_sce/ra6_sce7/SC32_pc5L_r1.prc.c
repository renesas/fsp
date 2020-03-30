///////////////////////////////////////////////////////////////////////////

// <SC32#2 P-384 ECDSA Signature Generation>                             //
// Procedure number: c5                                                  //
// File_Name      : SC32_pc5L_r1.prc                                     //
// State Diagram  : main(FSM1)                                           //
// Start State    : main03                                               //
// End State      : main03                                               //
// Input Data     : InData_DomainParam[48] (a||b||p||n)                  //
// : InData_G[24] (Gx||Gy)                                //
// : InData_PrivKey[12]                                   //
// : InData_MsgDgst[12]                                   //
// Output Data    : OutData_R[12] (Signature r)                          //
// : OutData_S[12] (Signature s)                          //
// Return value   : Pass or Fail or Resource_Conflict                    //
// -----------------------------------------------------------------------//
// total cycle    : polling + write access + read access + long polling  //
// polling        : 1156.4k cycle                                        //
// polling access :   76.8k times                                        //
// write access   :  155.6k times                                        //
// read  access   :    3556 times                                        //
///////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_ecc_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_ECC_384GenerateSign (const uint32_t * InData_DomainParam,
                                      const uint32_t * InData_G,
                                      const uint32_t * InData_PrivKey,
                                      const uint32_t * InData_MsgDgst,
                                      uint32_t       * OutData_R,
                                      uint32_t       * OutData_S) {
    uint32_t iLoop;
    uint32_t jLoop;
    uint32_t lLoop;

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

    WR1_PROG(REG_84H, 0x0000c501);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x008b0001);

    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WR1_PROG(REG_2CH, 0x0000001d);
    for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WR1_PROG(REG_2CH, 0x00000015);
    for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[(24) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WR1_PROG(REG_2CH, 0x00000014);
    for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[(36) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00021028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    SC32_function001(0x7da6f72e, 0x6a136357, 0x72ba1c99, 0x68666f85);

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
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_00H, 0x00003213);
    WR1_PROG(REG_2CH, 0x00000011);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xd0b9951e, 0x7e56b5d5, 0xe723c2e0, 0x4e7de0ef);

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
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_00H, 0x00003213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0x21af3ee0, 0xf6e36a35, 0xa8020321, 0x038c1764);

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
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_00H, 0x00003213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00001228);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WR1_PROG(REG_2CH, 0x0000001a);
    for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_G[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WR1_PROG(REG_2CH, 0x0000001b);
    for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_G[(12) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000030);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x808c001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008333);
    WR1_PROG(REG_2CH, 0x00000024);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00021028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00004404);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00004804);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x800088d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000020);
    WR1_PROG(REG_24H, 0x80009cd0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000082c);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000e0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000008);
    WR1_PROG(REG_24H, 0x800011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000008);
    WR1_PROG(REG_24H, 0x800011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000060);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x808c001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008333);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_34H, 0x00000802);
    WR1_PROG(REG_24H, 0x800088d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000008);
    WR1_PROG(REG_24H, 0x8000082c);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x800080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x800040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000802);
    WR1_PROG(REG_24H, 0x8000acd0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000008);
    WR1_PROG(REG_24H, 0x80000a2c);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000a0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x800060c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00005cd0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000bff);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x808c001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008333);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x00000bde);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000842);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b420);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000004);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b480);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000180);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b7a0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x000000c5);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000b9c);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0xc995bd51, 0x24bc2647, 0x5081d894, 0x6a7ee9a5);
    WR1_PROG(REG_E0H, 0x81010380);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    for (iLoop = 0; iLoop < 384; iLoop = iLoop + 1)
    {
        SC32_function002(0xed884f9d, 0xbe532baf, 0x8d4e9feb, 0x7dc93696);

        SC32_Subprc03();

        if (S_RAM[0] == 0x00000001)
        {
            break;
        }

        SC32_function002(0xc34be585, 0xa0392b63, 0x5236a875, 0x15df2ec2);
    }

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0xe16dd994, 0xfffc91b4, 0x04f5119a, 0x87e80883);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0xa406c807, 0x95307aff, 0x6ec4ccb8, 0x54542ee1);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_24H, 0x00001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000015c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00005004);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00008404);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000b420);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000004);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00000bff);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x808c001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008333);
        WR1_PROG(REG_2CH, 0x00000021);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        for (iLoop = 0; iLoop < 12; iLoop = iLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x0000381f);
            WR1_PROG(REG_1D0H, 0x00000000);

            for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
            {
                WR1_PROG(REG_24H, 0x0000102c);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_ECH, 0x3800d81f);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_E0H, 0x00000080);
                WR1_PROG(REG_1CH, 0x00A60000);

                WR1_PROG(REG_ECH, 0x00016c00);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function001(0xa06cdbe0, 0xfff51dfb, 0x1748220e, 0xb011c2b3);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    WR1_PROG(REG_24H, 0x0000082c);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x100019b1);
                    WAIT_STS(REG_24H, 21, 0);

                    WR1_PROG(REG_24H, 0x000019a1);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x000080c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function002(0xe0bcb58d, 0xa60de211, 0xd9ea71d8, 0xcf32a305);
                }
                else
                {
                    SC32_function002(0x75d1fdb8, 0xb8ec3ebf, 0x01ff3870, 0xcd823c35);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x1ae5f365, 0xbc3642ef, 0xe8ed9678, 0xe8149feb);
        }

        WR1_PROG(REG_ECH, 0x00008be0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000030);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00007c1f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1CH, 0x00602000);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_24H, 0x00001028);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000060);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x818c001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003833);
        WR1_PROG(REG_2CH, 0x00000012);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x0000082c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800012c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c2);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000a2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000082c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000082c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800016c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c2);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000e2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000e2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000030);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x818c001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003833);
        WR1_PROG(REG_2CH, 0x00000014);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x000084d0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00021028);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x8000c0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00006404);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00006c04);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x8000ecd0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000a8d0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000020);
        WR1_PROG(REG_24H, 0x80001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000a2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000828);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00001f00);
        WR1_PROG(REG_1CH, 0x00210000);

        WR1_PROG(REG_24H, 0x00000ac0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800060c2);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x800009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00005004);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00008404);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000b420);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000004);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00000bff);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x808c001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008333);
        WR1_PROG(REG_2CH, 0x00000021);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        for (iLoop = 0; iLoop < 12; iLoop = iLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x0000381f);
            WR1_PROG(REG_1D0H, 0x00000000);

            for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
            {
                WR1_PROG(REG_24H, 0x0000102c);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_ECH, 0x3800d81f);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_E0H, 0x00000080);
                WR1_PROG(REG_1CH, 0x00A60000);

                WR1_PROG(REG_ECH, 0x00016c00);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function001(0x2ea3aaa0, 0xe3f970e6, 0xfa36eb5d, 0x33cfd8c2);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    WR1_PROG(REG_24H, 0x0000082c);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x100019b1);
                    WAIT_STS(REG_24H, 21, 0);

                    WR1_PROG(REG_24H, 0x000019a1);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x000080c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function002(0x5016c372, 0xf9b62959, 0x7475b6c1, 0x8c72944a);
                }
                else
                {
                    SC32_function002(0x8dbf18a3, 0xe8b65f3d, 0x3f2edbd1, 0x315ced9b);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x34c71841, 0xd2ca7ac7, 0xae37ea42, 0xc1f6f33b);
        }

        WR1_PROG(REG_ECH, 0x00008be0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000030);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00007c1f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1CH, 0x00602000);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_24H, 0x00001028);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000011);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_MsgDgst[(0) + lLoop]);
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_34H, 0x00000020);
        WR1_PROG(REG_24H, 0x80001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x80000a2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x800009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000020);
        WR1_PROG(REG_24H, 0x80001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000018);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_PrivKey[(0) + lLoop]);
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x000015c0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x80000c2d);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x8000082c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x800009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00001f00);
        WR1_PROG(REG_1CH, 0x00210000);

        SC32_function001(0xae47c689, 0xdd0ad1fc, 0x4e69decf, 0xd1dd47cf);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0xb94ee888, 0x5d3c0b45, 0x4fab6a43, 0x2e0eb4c4);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SC32_function001(0xa6eb09d5, 0x8a169ec8, 0x28bf1a6e, 0xe1393716);
            WR1_PROG(REG_D0H, 0x00000200);
            WR1_PROG(REG_C4H, 0x00008887);
            WR1_PROG(REG_00H, 0x00002333);
            WR1_PROG(REG_2CH, 0x0000002b);
            WR1_PROG(REG_04H, 0x00000232);
            for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
            {
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_C0H, &OutData_R[(0) + lLoop]);
            }

            SC32_function001(0xeea5bee9, 0xe1a3d933, 0x66b1469c, 0x5af9e73a);
            WR1_PROG(REG_D0H, 0x00000200);
            WR1_PROG(REG_C4H, 0x00008887);
            WR1_PROG(REG_00H, 0x00002333);
            WR1_PROG(REG_2CH, 0x0000002a);
            WR1_PROG(REG_04H, 0x00000232);
            for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
            {
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_C0H, &OutData_S[(0) + lLoop]);
            }

            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0xf8c65e17, 0x51bba0be, 0x795261a5, 0x7af3ade6);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
