/////////////////////////////////////////////////////////////////////////

// <SC32#2 P-384 ECDSA Signature Verification>                         //
// Procedure number: c6                                                //
// File name      : SC32_pc6L_r1.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_DomainParam[48] (a||b||p||n)                //
// : InData_G[24] (Gx||Gy)                              //
// : InData_PubKey[24]                                  //
// : InData_MsgDgst[12]                                 //
// : InData_R[12]                                       //
// : InData_S[12]                                       //
// Output Data    : void                                               //
// Return Value   : Pass, Fail, Verification_Fail or Resource_Conflict //
// ---------------------------------------------------------------------//
// total cycle    : LONG_polling + polling + write access + read access//
// polling        : 1749.6k cycle                                      //
// polling access :  116.8k times                                      //
// write access   :  223.5k times                                      //
// read  access   :    5458 times                                      //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_ecc_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_ECC_384VerifySign (const uint32_t * InData_DomainParam,
                                    const uint32_t * InData_G,
                                    const uint32_t * InData_PubKey,
                                    const uint32_t * InData_MsgDgst,
                                    const uint32_t * InData_R,
                                    const uint32_t * InData_S) {
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

    WR1_PROG(REG_84H, 0x0000c601);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    WR1_PROG(REG_28H, 0x008b0001);

    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WR1_PROG(REG_2CH, 0x00000015);
    for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_R[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_1CH, 0x0000008c);
    WR1_PROG(REG_D0H, 0x00000200);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00003233);
    WR1_PROG(REG_2CH, 0x00000010);
    for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_00H, 22, 1);
        WR4_ADDR(REG_C0H, &InData_S[(0) + lLoop]);
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x008b0001);

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

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000130);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x808c001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008333);
    WR1_PROG(REG_2CH, 0x00000024);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000070d0);
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

    WR1_PROG(REG_24H, 0x00008cd0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000060c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000d91);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00001f00);
    WR1_PROG(REG_1CH, 0x00210000);

    SC32_function001(0xe5957caa, 0x3e2c4d76, 0x7c5c8a46, 0x04a80c2b);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        SC32_function003(0xa343bd4c, 0x184f0483, 0xd5479d2e, 0xa3e57347);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
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

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000100);
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

                SC32_function001(0x308bc476, 0x7a7e32b3, 0x96dfe1e6, 0x944191c3);
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

                    SC32_function002(0x18032e50, 0x231fb981, 0xc6ff8efd, 0x11883c91);
                }
                else
                {
                    SC32_function002(0x26ec3c3e, 0x3b7c81a3, 0xf65db283, 0x46986193);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0xb031f45e, 0x1425d0cc, 0x7b761ba6, 0x591e31c8);
        }

        WR1_PROG(REG_ECH, 0x00008be0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000130);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00007c1f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1CH, 0x00602000);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_24H, 0x00001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000094a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x808c000a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008333);
        WR1_PROG(REG_2CH, 0x00000023);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000010);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_MsgDgst[(0) + lLoop]);
        }

        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000e0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000014);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
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

        WR1_PROG(REG_24H, 0x00004404);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00004804);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000010);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_G[(0) + lLoop]);
        }

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

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000010);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_G[(12) + lLoop]);
        }

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

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x8000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000b540);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000040);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x808c000a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008333);
        WR1_PROG(REG_2CH, 0x00000025);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x000009c0);
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

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000100);
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
        WR1_PROG(REG_ECH, 0x000000c6);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00000b9c);
        WR1_PROG(REG_1D0H, 0x00000000);

        SC32_function001(0x7d987f24, 0xfe509936, 0x77a9d43d, 0xef460a97);
        WR1_PROG(REG_E0H, 0x81010380);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_04H, 0x00000607);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);

        for (iLoop = 0; iLoop < 384; iLoop = iLoop + 1)
        {
            SC32_function002(0xea687f92, 0x7702a37a, 0xfaee0d32, 0x901e9dc6);

            SC32_Subprc05();

            if (S_RAM[0] == 0x00000001)
            {
                break;
            }

            SC32_function002(0x42751767, 0x093a6146, 0xd03640a2, 0xf4810f17);
        }

        WR1_PROG(REG_ECH, 0x00000a73);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x0000b660);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000040);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x818c0013);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003833);
        WR1_PROG(REG_2CH, 0x0000001a);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x00001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00001f00);
        WR1_PROG(REG_1CH, 0x00210000);

        WR1_PROG(REG_24H, 0x00004404);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00004804);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800068d0);
        WAIT_STS(REG_24H, 21, 0);

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

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000100);
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

                SC32_function001(0x048c511e, 0xbd393100, 0xa7d05c22, 0x1123f870);
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

                    SC32_function002(0x92cb1ee4, 0x13b4e04d, 0x9905f41d, 0xfe87e8cf);
                }
                else
                {
                    SC32_function002(0x29a8ab91, 0x64dee96f, 0xf19f6009, 0x440a1d89);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x40021df8, 0x88e335ec, 0x846d3ea9, 0x8a407157);
        }

        WR1_PROG(REG_ECH, 0x00008be0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000130);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00007c1f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1CH, 0x00602000);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x80000dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800011c0);
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

        WR1_PROG(REG_24H, 0x00000a2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800015c0);
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

        WR1_PROG(REG_24H, 0x00000e2c);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000015c0);
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

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x800009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800080c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000010);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_PubKey[(0) + lLoop]);
        }

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

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_1CH, 0x0000008c);
        WR1_PROG(REG_D0H, 0x00000200);
        WR1_PROG(REG_C4H, 0x00008887);
        WR1_PROG(REG_00H, 0x00003233);
        WR1_PROG(REG_2CH, 0x00000010);
        for (lLoop = 0; lLoop < 12; lLoop = lLoop + 4)
        {
            WAIT_STS(REG_00H, 22, 1);
            WR4_ADDR(REG_C0H, &InData_PubKey[(12) + lLoop]);
        }

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

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x800009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x80000dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x8000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000b540);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000080);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x808c000a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008333);
        WR1_PROG(REG_2CH, 0x00000022);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_ECH, 0x0000b540);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x000000C0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x808c000a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008333);
        WR1_PROG(REG_2CH, 0x00000023);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000100);
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
        WR1_PROG(REG_ECH, 0x000000cd);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00000b9c);
        WR1_PROG(REG_1D0H, 0x00000000);

        SC32_function001(0xfc0d8ea8, 0x7fa8b36d, 0x4b59b16b, 0x7e4d9246);
        WR1_PROG(REG_E0H, 0x81010380);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_04H, 0x00000607);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);

        for (iLoop = 0; iLoop < 384; iLoop = iLoop + 1)
        {
            SC32_function002(0xe36dd76a, 0xc3b47c81, 0x71019cf7, 0x70ac9961);

            SC32_Subprc05();

            if (S_RAM[0] == 0x00000001)
            {
                break;
            }

            SC32_function002(0xf9a07550, 0xfdd9a138, 0x259e2397, 0x19b57c11);
        }

        WR1_PROG(REG_24H, 0x00001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00001f00);
        WR1_PROG(REG_1CH, 0x00210000);

        WR1_PROG(REG_ECH, 0x0000b660);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000080);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x818c0013);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003833);
        WR1_PROG(REG_2CH, 0x0000001a);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_ECH, 0x0000b660);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x000000C0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x818c0013);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003833);
        WR1_PROG(REG_2CH, 0x0000001b);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x00009cd0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000102c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000070d0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x800048d0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000082c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800011c0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000200);
        WR1_PROG(REG_24H, 0x80000a41);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800011c0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000200);
        WR1_PROG(REG_24H, 0x80000951);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x80004cd0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000082c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000280);
        WR1_PROG(REG_24H, 0x800019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000080);
        WR1_PROG(REG_24H, 0x800080c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000e0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x0000102c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000200);
        WR1_PROG(REG_24H, 0x900019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000280);
        WR1_PROG(REG_24H, 0x800019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800015c0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000941);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800015c0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000951);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000080);
        WR1_PROG(REG_24H, 0x800040c2);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000200);
        WR1_PROG(REG_24H, 0x800012c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00008cd0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000082c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00008cd0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000102c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000951);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000149);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000d51);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000082c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000080);
        WR1_PROG(REG_24H, 0x800080c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000080);
        WR1_PROG(REG_24H, 0x800060c2);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000c2c);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000d51);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000145);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x8000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00001dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00001f00);
        WR1_PROG(REG_1CH, 0x00210000);

        WR1_PROG(REG_24H, 0x00004404);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00004804);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x800068d0);
        WAIT_STS(REG_24H, 21, 0);

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

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000100);
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

                SC32_function001(0x8971ad57, 0x467ad4b9, 0xd4905b12, 0xcc0d9bfb);
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

                    SC32_function002(0x0e8bee7f, 0x79714533, 0x64c1cd32, 0x451e310a);
                }
                else
                {
                    SC32_function002(0x5f80a40d, 0x32fa8734, 0x4c65839f, 0xd7637705);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x8c2b6408, 0x08050287, 0x996ec72f, 0xfac2aa5f);
        }

        WR1_PROG(REG_ECH, 0x00008be0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000130);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_ECH, 0x00007c1f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1CH, 0x00602000);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_34H, 0x00000002);
        WR1_PROG(REG_24H, 0x80000dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_34H, 0x00000008);
        WR1_PROG(REG_24H, 0x800011c0);
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

        WR1_PROG(REG_ECH, 0x0000b7e0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000130);
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

        WR1_PROG(REG_24H, 0x000088d0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00009004);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00001028);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x100019b1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000019a1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x0000b660);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x818c0013);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003833);
        WR1_PROG(REG_2CH, 0x00000014);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00001991);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00001f00);
        WR1_PROG(REG_1CH, 0x00210000);

        WR1_PROG(REG_24H, 0x000019c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000991);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00001f00);
        WR1_PROG(REG_1CH, 0x00210000);

        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function001(0xc01945dd, 0x70cda2cf, 0x55d6135e, 0x63c5ee20);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function003(0x8c16d030, 0x48fe2775, 0x42dcfcd5, 0x5278a741);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_VERIFY_FAIL;
        }
        else
        {
            SC32_function003(0xafe11816, 0xd4fba5e8, 0xe5ee99c7, 0xe0659cd8);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
