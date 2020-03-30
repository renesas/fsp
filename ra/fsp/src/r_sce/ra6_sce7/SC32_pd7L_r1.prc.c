///////////////////////////////////////////////////////////////////////////

// <SC32#2 P-256 ECDSA Signature Generation(hidden key)>                 //
// Procedure number: d7                                                  //
// File_Name      : SC32_pd7L_r1.prc                                     //
// State Diagram  : main(FSM1)                                           //
// Start State    : main03                                               //
// End State      : main03                                               //
// Input Data     : InData_DomainParam[32] (a||b||p||n)                  //
// : InData_G[16] (Gx||Gy)                                //
// : InData_KeyIndex[13]                                  //
// : InData_MsgDgst[8]                                    //
// Output Data    : OutData_R[8] (Signature r)                           //
// : OutData_S[8] (Signature s)                           //
// Return value   : Pass or Fail or HRK_Invalid_Index                    //
// : or Resource_Conflict                                 //
// -----------------------------------------------------------------------//
// total cycle    : polling + write access + read access + long polling  //
// polling        : 438.4k cycle                                         //
// polling access :  50.9k times                                         //
// write access   : 103.5k times                                         //
// read  access   :   2373 times                                         //
///////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_ecc_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_ECC_256HrkGenerateSign (const uint32_t * InData_DomainParam,
                                         const uint32_t * InData_G,
                                         const uint32_t * InData_KeyIndex,
                                         const uint32_t * InData_MsgDgst,
                                         uint32_t       * OutData_R,
                                         uint32_t       * OutData_S) {
    uint32_t lLoop;
    uint32_t iLoop;
    uint32_t jLoop;

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

    WR1_PROG(REG_84H, 0x0000d701);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x00870001);

    WR1_PROG(REG_1CH, 0x00000088);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003223);
    WR1_PROG(REG_2CH, 0x0000001d);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x00000088);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003223);
    WR1_PROG(REG_2CH, 0x00000015);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[(16) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x00000088);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003223);
    WR1_PROG(REG_2CH, 0x00000014);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[(24) + lLoop]);
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

    SC32_function001(0x0dff84da, 0xa9915226, 0x480177ad, 0x260946c2);

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

    SC32_function001(0xee4b2125, 0x81801984, 0x5c3638fd, 0x42ef62b7);

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

    WR1_PROG(REG_1CH, 0x00000088);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003223);
    WR1_PROG(REG_2CH, 0x0000001a);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_G[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x00000088);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003223);
    WR1_PROG(REG_2CH, 0x0000001b);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_G[(8) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000020);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x8088001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008323);
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
    WR1_PROG(REG_ECH, 0x00000040);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x8088001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008323);
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
    WR1_PROG(REG_E0H, 0x8088001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008323);
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
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b7a0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x000000d7);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000b9c);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x5b1316e8, 0x96821ad0, 0x0b4ebf94, 0x32ba0e82);
    WR1_PROG(REG_E0H, 0x81010380);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    for (iLoop = 0; iLoop < 256; iLoop = iLoop + 1)
    {
        SC32_function002(0xb2a85c9a, 0x48699fc0, 0xbd10f82f, 0xffefd686);

        SC32_Subprc03();

        if (S_RAM[0] == 0x00000001)
        {
            break;
        }

        SC32_function002(0xfb3ab97b, 0x59394c04, 0xf8d9548d, 0xba9a61ce);
    }

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0xa4284e36, 0x9edddf6c, 0x4cc79743, 0x515afb08);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x39e08efa, 0xa650daa1, 0x98dc4ba0, 0xea600225);
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
        WR1_PROG(REG_E0H, 0x8088001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008323);
        WR1_PROG(REG_2CH, 0x00000021);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
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

                SC32_function001(0x096f8b1d, 0x7ca1b254, 0x3bf0a561, 0xf1bb33a0);
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

                    SC32_function002(0xa1b7f21f, 0xaa13bf02, 0xf57f2d47, 0x77c28f8d);
                }
                else
                {
                    SC32_function002(0xd81a508f, 0x56a11686, 0xeff3ebf4, 0x852c17b4);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x55c25585, 0xd8af8387, 0x6279a27e, 0xe7dc3acb);
        }

        WR1_PROG(REG_ECH, 0x00008be0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000020);
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
        WR1_PROG(REG_ECH, 0x00000040);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x8188001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003823);
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
        WR1_PROG(REG_ECH, 0x00000020);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x8188001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003823);
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
        WR1_PROG(REG_E0H, 0x8088001f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008323);
        WR1_PROG(REG_2CH, 0x00000021);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
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

                SC32_function001(0x7f599b3d, 0x1368df6e, 0x1b3e8cd0, 0x50fe35bf);
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

                    SC32_function002(0x24f6cd91, 0xda532a4b, 0x0cb8da5f, 0xaf4e5003);
                }
                else
                {
                    SC32_function002(0xe11ced5c, 0x4065e4f9, 0xc761fd7f, 0x37915f43);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x9b956e7d, 0x599b8b5d, 0x36c880c8, 0x8c92156b);
        }

        WR1_PROG(REG_ECH, 0x00008be0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000020);
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

        WR1_PROG(REG_1CH, 0x00000088);
        WR1_PROG(REG_D0H, 0x00000100);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003223);
        WR1_PROG(REG_2CH, 0x00000011);
        for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
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
        WR1_PROG(REG_100H, 0xa4cf6fd0);

        WR1_PROG(REG_1CH, 0x00000088);
        WR1_PROG(REG_D0H, 0x00000100);
        WR1_PROG(REG_C4H, 0x02f087bf);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[1]);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[5]);
        WR1_PROG(REG_00H, 0x00003223);
        WR1_PROG(REG_2CH, 0x00000018);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_1CH, 0x00000084);
        WR1_PROG(REG_C4H, 0x000007bd);
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_KeyIndex[9]);

        WR1_PROG(REG_C4H, 0x00900c45);
        WR1_PROG(REG_00H, 0x00002213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        SC32_function001(0xf70bb870, 0x80660f32, 0x70a3b23b, 0x787bee8f);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0xfe23b5d7, 0xb1d5aca7, 0x94815290, 0x7c369cdf);
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

        SC32_function001(0x1a178f4e, 0x8cccf3a0, 0x6ab97aaa, 0x72e25008);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0x90ba858b, 0xa65d344a, 0x0e234697, 0x4cbb34fc);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SC32_function001(0xda75b26e, 0xc0c3963c, 0x673ae2ef, 0x0b54f34c);
            WR1_PROG(REG_D0H, 0x00000100);
            WR1_PROG(REG_C4H, 0x00008887);
            WR1_PROG(REG_00H, 0x00002323);
            WR1_PROG(REG_2CH, 0x0000002b);
            WR1_PROG(REG_04H, 0x00000222);
            for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
            {
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_C0H, &OutData_R[(0) + lLoop]);
            }

            SC32_function001(0xe628dbc6, 0x6cb73660, 0xc6f2d954, 0xf129b8f0);
            WR1_PROG(REG_D0H, 0x00000100);
            WR1_PROG(REG_C4H, 0x00008887);
            WR1_PROG(REG_00H, 0x00002323);
            WR1_PROG(REG_2CH, 0x0000002a);
            WR1_PROG(REG_04H, 0x00000222);
            for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
            {
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_C0H, &OutData_S[(0) + lLoop]);
            }

            WR1_PROG(REG_1C0H, 0x00010000);

            SC32_function003(0xe9ba4375, 0x15ea90a0, 0x203d31aa, 0xd72e8e0b);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
