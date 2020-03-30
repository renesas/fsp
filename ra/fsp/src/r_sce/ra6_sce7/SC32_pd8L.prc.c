/////////////////////////////////////////////////////////////////////////

// <SC32 P-256 ECC Scalar Multiplication(hidden key)>                  //
// Procedure number: d8                                                //
// File name      : SC32_pd8L.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_DomainParam[24] (a || b || p)               //
// : InData_KeyIndex[13]                                //
// : InData_P[16] (Px || Py)                            //
// Output Data    : OutData_R[16](Rx || Ry)                            //
// Return Value   : Pass or Fail or HRK_Invalid_Index                  //
// : or Resource_Conflict                               //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 410.0k cycle                                       //
// polling access :  47913 times                                       //
// write access   :  96731 times                                       //
// read  access   :   2068 times                                       //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_ecc_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_ECC_256HrkScalarMultiplication (const uint32_t * InData_DomainParam,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_P,
                                                 uint32_t       * OutData_R) {
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

    WR1_PROG(REG_84H, 0x0000d801);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x00000001);

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
    WR1_PROG(REG_2CH, 0x00000014);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_DomainParam[(16) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

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
    WR1_PROG(REG_2CH, 0x00000011);
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

    SC32_function001(0x48d94d68, 0x5d5555e2, 0x190a338e, 0xed34abbb);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x8c0a0a02, 0x4d37fe37, 0xc2cbfff9, 0x63a94906);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }

    WR1_PROG(REG_1CH, 0x00000088);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003223);
    WR1_PROG(REG_2CH, 0x0000001a);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_P[(0) + lLoop]);
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
        WR4_ADDR(REG_C0H, &InData_P[(8) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8002d028);
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
    WR1_PROG(REG_24H, 0x0000e8d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000020);
    WR1_PROG(REG_24H, 0x80009cd0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000f004);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000002);
    WR1_PROG(REG_24H, 0x800088d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x80005004);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000802);
    WR1_PROG(REG_24H, 0x800088d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000002);
    WR1_PROG(REG_24H, 0x80008cd0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x80007004);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000802);
    WR1_PROG(REG_24H, 0x8000acd0);
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
    WR1_PROG(REG_ECH, 0x000000d8);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000b9c);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x6c3687e4, 0x668ee67f, 0x39b20280, 0xb929b57c);
    WR1_PROG(REG_E0H, 0x81010380);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    for (iLoop = 0; iLoop < 256; iLoop = iLoop + 1)
    {
        SC32_function002(0x4ed197c5, 0xe3f1ba6b, 0x5b8c13a2, 0x8e76be5b);

        SC32_Subprc03();

        if (S_RAM[0] == 0x00000001)
        {
            break;
        }

        SC32_function002(0x6a05f6d7, 0x7767b2f4, 0x00452a2a, 0x80c39db4);
    }

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0x56a94090, 0x7c953933, 0xf1db80b4, 0xde7f2782);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x6d64ca04, 0x2cc91ca9, 0xb11ead78, 0xff59194e);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_24H, 0x00001dc0);
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

            SC32_function001(0x1fe64301, 0x39d182a8, 0x6ff9760b, 0x0689520c);
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

                SC32_function002(0x92407913, 0x480e86ab, 0xd0b6bdb5, 0x8832419c);
            }
            else
            {
                SC32_function002(0x6cae7f6a, 0x29f5da05, 0x941d8786, 0x5941adb7);
            }
        }

        WR1_PROG(REG_ECH, 0x000027e1);
        WR1_PROG(REG_1D0H, 0x00000000);

        SC32_function002(0x4b348d99, 0xf6fffcfc, 0x17708b23, 0x2a496ce6);
    }

    WR1_PROG(REG_ECH, 0x00008be0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000020);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00007c1f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00602000);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_Subprc04();

    SC32_function001(0xbaf99ff9, 0x180a1500, 0x72da544d, 0xf467cc45);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002323);
    WR1_PROG(REG_2CH, 0x00000022);
    WR1_PROG(REG_04H, 0x00000222);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_R[(0) + lLoop]);
    }

    SC32_function001(0x4e68f5b8, 0xde4df07b, 0xd62f80d2, 0xc800a3ea);
    WR1_PROG(REG_D0H, 0x00000100);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002323);
    WR1_PROG(REG_2CH, 0x00000023);
    WR1_PROG(REG_04H, 0x00000222);
    for (lLoop = 0; lLoop < 8; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_R[(8) + lLoop]);
    }

    WR1_PROG(REG_1C0H, 0x00010000);

    SC32_function003(0x7cb0e010, 0xbefe6160, 0xd122dc68, 0x62540f92);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
