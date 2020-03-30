///////////////////////////////////////////////////////////////////////////

// <SC32#2 P-384 ECDSA Signature Generation(hidden key)>                 //
// Procedure number: e1                                                  //
// File_Name      : SC32_pe1L_r1.prc                                     //
// State Diagram  : main(FSM1)                                           //
// Start State    : main03                                               //
// End State      : main03                                               //
// Input Data     : InData_DomainParam[48] (a||b||p||n)                  //
// : InData_G[24] (Gx||Gy)                                //
// : InData_KeyIndex[17]                                  //
// : InData_MsgDgst[12]                                   //
// Output Data    : OutData_R[12] (Signature r)                          //
// : OutData_S[12] (Signature s)                          //
// Return value   : Pass or Fail or HRK_Invalid_Index                    //
// : or Resource_Conflict                                 //
// -----------------------------------------------------------------------//
// total cycle    : polling + write access + read access + long polling  //
// polling        : 1156.5k cycle                                        //
// polling access :   76.8k times                                        //
// write access   :  155.7k times                                        //
// read  access   :    3557 times                                        //
///////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_ecc_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_ECC_384HrkGenerateSign (const uint32_t * InData_DomainParam,
                                         const uint32_t * InData_G,
                                         const uint32_t * InData_KeyIndex,
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

    WR1_PROG(REG_84H, 0x0000e101);
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

    SC32_function001(0x91511883, 0xe15d21af, 0xa6d8fabc, 0xb7cc8466);

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

    SC32_function001(0x98e6d2e3, 0x4fe7eb99, 0xb46a418d, 0xa23fe178);

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

    SC32_function001(0xcebb50bc, 0x066c83cb, 0x0326793a, 0x9aafab2d);

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
    WR1_PROG(REG_ECH, 0x000000e1);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000b9c);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0xcf44122f, 0xafac0646, 0xec36c2d3, 0xfc0c86a0);
    WR1_PROG(REG_E0H, 0x81010380);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    for (iLoop = 0; iLoop < 384; iLoop = iLoop + 1)
    {
        SC32_function002(0x2b683554, 0x9702d8e5, 0xcbc6cadc, 0x35bfd1dd);

        SC32_Subprc03();

        if (S_RAM[0] == 0x00000001)
        {
            break;
        }

        SC32_function002(0xa5bf8daa, 0x4ca1ba16, 0x72b0cf8c, 0xaf762cbb);
    }

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0xce5399ad, 0xbce5d001, 0x8a8e47a6, 0x48faca19);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x70e6bc31, 0xd3b123cf, 0x3d43233e, 0xdaa643f2);
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

                SC32_function001(0xf6305780, 0xddecc568, 0xb0767bbd, 0x8d22a50a);
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

                    SC32_function002(0xbd85b513, 0xcae33ad7, 0x1e716080, 0xe1d4b3a3);
                }
                else
                {
                    SC32_function002(0x30b5f6e2, 0xac0c3bab, 0xc5ed458d, 0xbe0ec0bc);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0xe0b6d680, 0xa2232733, 0x72e0f1dc, 0x0f8d388e);
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

                SC32_function001(0xc67759cf, 0x49317930, 0x7817ff76, 0x955c8df4);
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

                    SC32_function002(0x03375408, 0xd25148d2, 0xe40ea511, 0x81134642);
                }
                else
                {
                    SC32_function002(0xba125f5e, 0x3aca571c, 0x56b28d1d, 0xa5db630c);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x98f9b06d, 0x281bb509, 0xb32a44f4, 0x9e427f82);
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

        WR1_PROG(REG_1CH, 0x00000081);
        WR1_PROG(REG_C4H, 0x200c3b0c);
        WAIT_STS(REG_00H, 22, 1);
        WR1_ADDR(REG_C0H, &InData_KeyIndex[0]);

        WR1_PROG(REG_C4H, 0x000c0b0c);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x6f16e9b9);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x02f087bf);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[1]);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[5]);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[9]);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000018);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_1CH, 0x00000084);
        WR1_PROG(REG_C4H, 0x000007bd);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[13]);

        WR1_PROG(REG_C4H, 0x00900c45);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        SC32_function001(0x8230ff10, 0x3a31f773, 0xa77c41fd, 0x4ce709d9);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0xd0b0744c, 0x8d024fad, 0x7dd5a523, 0x5a2e4e8c);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
        }

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

        SC32_function001(0x757d5ffb, 0x20acc11c, 0x07ae4155, 0x3da3999e);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0x6982373a, 0x7afa4822, 0x29f0a41e, 0xdd8d7917);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SC32_function001(0xbbf71949, 0xd592392c, 0x57b54271, 0xd8be6e6a);
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

            SC32_function001(0xc923302a, 0x49bd5add, 0x42aeeb86, 0xedcfdbe8);
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

            SC32_function003(0x6f1ac2c3, 0x635ea82d, 0x6ddc9296, 0xb7bc7897);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
