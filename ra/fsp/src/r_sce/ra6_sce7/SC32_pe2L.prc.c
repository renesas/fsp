/////////////////////////////////////////////////////////////////////////

// <SC32 P-384 ECC Scalar Multiplication(hidden key)>                  //
// Procedure number: e2                                                //
// File name      : SC32_pe2L.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_DomainParam[36] (a || b || p)               //
// : InData_KeyIndex[17]                                //
// : InData_P[24] (Px || Py)                            //
// Output Data    : OutData_R[24](Rx || Ry)                            //
// Return Value   : Pass or Fail or HRK_Invalid_Index                  //
// : or Resource_Conflict                               //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 1228.2k cycle                                      //
// polling access :   72375 times                                      //
// write access   :  145569 times                                      //
// read  access   :    3100 times                                      //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_ecc_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_ECC_384HrkScalarMultiplication (const uint32_t * InData_DomainParam,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_P,
                                                 uint32_t       * OutData_R) {
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

    WR1_PROG(REG_84H, 0x0000e201);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x00000001);

    WR1_PROG(REG_28H, 0x008f0001);

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x0000001d);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[0]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[4]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[8]);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x00000014);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[24]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[28]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[32]);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

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
    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x00000011);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_00H, 0x00003233);
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

    SC32_function001(0xa98221ba, 0x1d06d2b1, 0xba0d7137, 0xd330e90f);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0xfc1ee279, 0xed44fdff, 0x1cbd9114, 0x2b7bd1d1);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x0000001a);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_P[0]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_P[4]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_P[8]);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x0000001b);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_P[12]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_P[16]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_P[20]);
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
    WR1_PROG(REG_E0H, 0x8090001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000010);
    WR1_PROG(REG_1D0H, 0x00000000);

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
    WR1_PROG(REG_ECH, 0x000000e2);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000b9c);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x3474f858, 0xa68f9efd, 0x48e29bd7, 0x3dfeb02b);
    WR1_PROG(REG_E0H, 0x81010380);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    for (iLoop = 0; iLoop < 384; iLoop = iLoop + 1)
    {
        SC32_function002(0x1e014770, 0xe633c2b6, 0xdb7495b7, 0x7a2064fd);

        SC32_Subprc03();

        if (S_RAM[0] == 0x00000001)
        {
            break;
        }

        SC32_function002(0x6d3a02bc, 0x14895105, 0xb29aea5c, 0xebfa84bd);
    }

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0xe3ee5fb2, 0x42b41537, 0x3d1b66ae, 0x83ff4454);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x23a3f0f1, 0x3bafc236, 0x289237cd, 0x78f5ca1c);
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
    WR1_PROG(REG_E0H, 0x8090001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008343);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000010);
    WR1_PROG(REG_1D0H, 0x00000000);

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

            SC32_function001(0xcb2f5270, 0xda58ce10, 0xad6f1bb8, 0x1a64daa9);
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

                SC32_function002(0x1c281b7f, 0x2153a4fc, 0x848039b7, 0xf60f484f);
            }
            else
            {
                SC32_function002(0x11e54c31, 0x1449b588, 0x5692e620, 0xf6a479bb);
            }
        }

        WR1_PROG(REG_ECH, 0x000027e1);
        WR1_PROG(REG_1D0H, 0x00000000);

        SC32_function002(0x476b33f0, 0x35d54312, 0xb086bfcf, 0xc73a9b22);
    }

    WR1_PROG(REG_ECH, 0x00008be0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000040);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00007c1f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00602000);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_Subprc04();

    SC32_function001(0xa8a08409, 0x61e4da58, 0x106d24d4, 0x3274f7f6);
    WR1_PROG(REG_00H, 0x00000313);
    WR1_PROG(REG_2CH, 0x00000022);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002333);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_04H, 0x00000232);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_R[0]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_R[4]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_R[8]);

    SC32_function001(0xd7e396a5, 0x40a77963, 0x2d7dfe1e, 0x548a6426);
    WR1_PROG(REG_00H, 0x00000313);
    WR1_PROG(REG_2CH, 0x00000023);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002333);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_04H, 0x00000232);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_R[12]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_R[16]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_R[20]);

    WR1_PROG(REG_1C0H, 0x00010000);

    SC32_function003(0x309e60db, 0x97354bbe, 0x42b404a8, 0xafc9fc78);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
