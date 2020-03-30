/////////////////////////////////////////////////////////////////////////

// <SC32 P-384 key generation>                                         //
// Procedure number: a7                                                //
// File name      : SC32_pa7L_r1.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_DomainParam[48] (a || b || p || n)          //
// : InData_G[24] (Gx || Gy)                            //
// Output Data    : OutData_PrivKey[12]                                //
// : OutData_PubKey[24](Px || Py)                       //
// Return Value   : Pass or Fail or Resource_Conflict                  //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 1228.8k cycle                                      //
// polling access :   72430 times                                      //
// write access   :  145692 times                                      //
// read  access   :    3127 times                                      //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_ecc_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_ECC_384GenerateKey (const uint32_t * InData_DomainParam,
                                     const uint32_t * InData_G,
                                     uint32_t       * OutData_PrivKey,
                                     uint32_t       * OutData_PubKey) {
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

    WR1_PROG(REG_84H, 0x0000a701);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x00000001);

    WR1_PROG(REG_28H, 0x008f0001);

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x00000018);
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

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x00000015);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[36]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[40]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_DomainParam[44]);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x0000001a);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_G[0]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_G[4]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_G[8]);
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
    WR4_ADDR(REG_C0H, &InData_G[12]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_G[16]);
    WAIT_STS(REG_00H, 22, 1);
    WR4_ADDR(REG_C0H, &InData_G[20]);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000084d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00021128);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000e0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_00H, 0x00003013);
    WR1_PROG(REG_2CH, 0x00000011);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xc1b195e9, 0x1a4ef749, 0x0d8f64e0, 0x0791f3e3);

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

    SC32_function001(0xd7f66366, 0x6d5bee62, 0x17cbd238, 0xf72ea11a);

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

    SC32_function001(0xdc2d47b0, 0xb3f2f6b2, 0xb6aa0dd3, 0x73940157);

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

    WR1_PROG(REG_24H, 0x000005c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000b0c);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x10001df1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001de1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
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
    WR1_PROG(REG_24H, 0x0000e8d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000808);
    WR1_PROG(REG_24H, 0x8000f0d0);
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
    WR1_PROG(REG_ECH, 0x000000a7);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000b9c);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x94bd7f4a, 0xd11e4a1b, 0xe674cde6, 0x0896b5bd);
    WR1_PROG(REG_E0H, 0x81010380);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_04H, 0x00000607);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);

    for (iLoop = 0; iLoop < 384; iLoop = iLoop + 1)
    {
        SC32_function002(0x930a69dc, 0x5a441516, 0xd99b814c, 0x778f88de);

        SC32_Subprc03();

        if (S_RAM[0] == 0x00000001)
        {
            break;
        }

        SC32_function002(0x5558ca61, 0x0f41ce70, 0x59f55050, 0x07284760);
    }

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0x5d62abac, 0x38451ddf, 0x1ec906e2, 0xd906405c);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x2648ff1c, 0x10b8b0e6, 0x6bbdd119, 0xb0d5361b);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_34H, 0x00000800);
    WR1_PROG(REG_24H, 0x8000f4d0);
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

            SC32_function001(0xb5f64523, 0x92eaae2f, 0xbfb64e98, 0x150505fa);
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

                SC32_function002(0xe86e3d03, 0x79c09da8, 0x6c6bd527, 0xcb71b3b6);
            }
            else
            {
                SC32_function002(0x72cc79ca, 0x98b4886e, 0x563ecbb7, 0x5b110541);
            }
        }

        WR1_PROG(REG_ECH, 0x000027e1);
        WR1_PROG(REG_1D0H, 0x00000000);

        SC32_function002(0xda947e15, 0x1ab8b93d, 0x61402145, 0xaca9390a);
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

    SC32_function001(0x7c92006f, 0x5912474a, 0xfdbd1731, 0x51733eaf);
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
    RD4_ADDR(REG_C0H, &OutData_PubKey[0]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_PubKey[4]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_PubKey[8]);

    SC32_function001(0xdad53e19, 0x3f591467, 0x9031c419, 0xb36dbae8);
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
    RD4_ADDR(REG_C0H, &OutData_PubKey[12]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_PubKey[16]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_PubKey[20]);

    SC32_function001(0x7c25b423, 0xa1c7837f, 0x67fbb122, 0x40679f7d);
    WR1_PROG(REG_00H, 0x00000313);
    WR1_PROG(REG_2CH, 0x0000002d);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002333);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_04H, 0x00000232);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_PrivKey[0]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_PrivKey[4]);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_C0H, &OutData_PrivKey[8]);

    WR1_PROG(REG_1C0H, 0x00010000);

    SC32_function003(0xc531f2e5, 0xcdf7a96f, 0xb2daa189, 0xf7c52bbd);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
