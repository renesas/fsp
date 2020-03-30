/////////////////////////////////////////////////////////////////////////

// <SC32#2 RSA2048 Key Generation(hiding private key)>                 //
// Procedure number: e5                                                //
// File name      : SC32_pe5L_r2.prc                                   //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : MAX_CNT                                            //
// Output Data    : OutData_DomainParam[160]                           //
// :  (d mod (q-1)||q||d mod (p-1)||p||q^-1 mod p)      //
// : OutData_N[64]                                      //
// : OutData_KeyIndex[69]                               //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access + long polling//
// polling        : 15219.2k cycle                                     //
// polling access :   160.4k times                                     //
// write access   :   297.9k times                                     //
// read  access   :      599 times                                     //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_rsa_private.h"
#include "hw_sce_private.h"

fsp_err_t HW_SCE_HRK_RSA_2048KeyGenerate (uint32_t   num_tries,
                                          uint32_t * OutData_KeyIndex,
                                          uint32_t * OutData_N,
                                          uint32_t * OutData_DomainParam)
{
    uint32_t iLoop, jLoop, kLoop, lLoop;
    uint32_t MAX_CNT = num_tries;

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

    WR1_PROG(REG_84H, 0x0000e501);
    WR1_PROG(REG_108H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010001);

    SC32_function001(0xf1ea5a98, 0xc8e64fb1, 0xf49e177b, 0x74e5f668);

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
    SC32_function001(0x550700a1, 0x52f22059, 0x31f4d4a8, 0x0d17ee26);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x01080c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000a31);
    WR1_PROG(REG_1D0H, 0x00000000);
    for (kLoop = 0; kLoop < MAX_CNT; kLoop = kLoop + 1)
    {
        WR1_PROG(REG_28H, 0x00bf0001);
        WR1_PROG(REG_00H, 0x00003043);
        WR1_PROG(REG_2CH, 0x00000012);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_104H, 0x00002f57);
        WAIT_STS(REG_104H, 31, 1);
        WR48_PROG(REG_100H,
                  0x00030005,
                  0x0007000b,
                  0x000d0011,
                  0x00130017,
                  0x001d001f,
                  0x00250029,
                  0x002b002f,
                  0x003b003d,
                  0x00430047,
                  0x0049004f,
                  0x00530059,
                  0x00610065,
                  0x0067006b,
                  0x006d0071,
                  0x007f0083,
                  0x0089008b,
                  0x00950097,
                  0x009d00a3,
                  0x00a700ad,
                  0x00b300b5,
                  0x00bf00c1,
                  0x00c500c7,
                  0x00d300df,
                  0x00e300e5,
                  0x00e900ef,
                  0x00f100fb,
                  0x01010107,
                  0x010d010f,
                  0x01150119,
                  0x011b0125,
                  0x01330137,
                  0x0139013d,
                  0x014b0151,
                  0x015b015d,
                  0x01610167,
                  0x016f0175,
                  0x017b017f,
                  0x0185018d,
                  0x01910199,
                  0x01a301a5,
                  0x01af01b1,
                  0x01b701bb,
                  0x01c101c9,
                  0x01cd01cf,
                  0x01d301df,
                  0x01e701eb,
                  0x01f301f7,
                  0x01fd0000);

        WR1_PROG(REG_ECH, 0x000008c6);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_00H, 0x00000343);
        WR1_PROG(REG_2CH, 0x00000022);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_E0H, 0x80a00006);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008383);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_ECH, 0x0000b4c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000080);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80900006);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008343);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_28H, 0x009f0001);

        SC32_function001(0x302a873a, 0xef703387, 0x1ecfb4a9, 0x01ca6461);

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

        WR1_PROG(REG_E0H, 0x80040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_ECH, 0x0000d01f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x81040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003813);
        WR1_PROG(REG_2CH, 0x00000010);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        for (iLoop = 0; iLoop < 24; iLoop = iLoop + 4)
        {
            SC32_function001(0x2c69bcc9, 0xaa2af410, 0x6b80f018, 0x583faf59);

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

            SC32_function002(0x3231d862, 0xa07aec1e, 0x82149165, 0x684e1c2d);
        }

        SC32_function001(0x2c69bcc9, 0xaa2af410, 0x6b80f018, 0x583faf59);

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

        WR1_PROG(REG_E0H, 0x80040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00008213);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_ECH, 0x0000d060);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x81040000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003813);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_2CH, 0x00000011);
        WR1_PROG(REG_104H, 0x00001f57);
        WAIT_STS(REG_104H, 31, 1);
        WR32_PROG(REG_100H,
                  0xB51EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851EB8,
                  0x51EB851E,
                  0xB851EB85,
                  0x1EB851EB,
                  0x851EB851,
                  0xEB851B5C);

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00001591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00210000);

        SC32_function001(0x170b21f1, 0xa6018de2, 0xbf83ddfd, 0xce3849b6);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0xbc8af119, 0x37524602, 0x30d210b9, 0x41fdad6e);
            continue;
        }
        else
        {
            SC32_function002(0x4ccde15d, 0x0d60e81e, 0xcccd8794, 0x178ded43);
        }

        WR1_PROG(REG_ECH, 0x38008a20);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x193ae4c2, 0xf5dd4610, 0x551b2d2c, 0x3cff18fa);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x00001dc0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00001191);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);

            SC32_function001(0x6f2f18f1, 0xc16b9ce1, 0xb80570a5, 0xe5c09ac0);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000011c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00001d91);
                WAIT_STS(REG_24H, 21, 0);

                SC32_function002(0xb97aa2f3, 0xc658ec1d, 0x011912ee, 0x75d721e2);
            }
            else
            {
                SC32_function002(0x736b1bf8, 0x634e4341, 0x623690d1, 0xf502d2ba);
            }

            WR1_PROG(REG_2CH, 0x00000011);
            WR1_PROG(REG_104H, 0x00000357);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, 0x00000000, 0x00000000, 0x00000000, 0x10000000);
            WR1_PROG(REG_00H, 0x00003073);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x00001591);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);

            SC32_function001(0xfc29fc08, 0x3915869d, 0x5b4a9c3d, 0x5a90ac9d);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                SC32_function002(0xaa6cdcbb, 0x8266f23e, 0xed13d408, 0xb2ef518a);
                continue;
            }
            else
            {
                SC32_function002(0x97f82dda, 0x08b5fb3d, 0x78535dfb, 0xfbebca18);
            }
        }
        else
        {
            SC32_function002(0xec3843c2, 0x7194bd81, 0x25d97f49, 0xb185e465);
        }

        WR1_PROG(REG_ECH, 0x000008c6);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x0000094a);
        WR1_PROG(REG_1D0H, 0x00000000);

        for (iLoop = 0; iLoop < 96; iLoop = iLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x01003906);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002cc0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002cc0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x81010100);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_00H, 0x0000303f);
            WR1_PROG(REG_2CH, 0x00000014);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);
            WR1_PROG(REG_00H, 0x00003043);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_00H, 0x00003807);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x00004006);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000009c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000591);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_1CH, 0x00210000);
            SC32_function001(0x7d4e18c4, 0x3953c1e5, 0xf7948c97, 0x345dac58);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);
            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_ECH, 0x0000d140);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function002(0xf9dfe1a2, 0x053398cb, 0x70f46c7a, 0x8dd749e4);
                break;
            }
            else
            {
                SC32_function002(0x6b1c0638, 0xf02d67c3, 0xbd70b6d3, 0xee88a32c);
            }
        }

        WR1_PROG(REG_ECH, 0x38008940);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x4bf720a9, 0x13e5769c, 0x09996bb8, 0x2785cf7f);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0x32f1ad43, 0x6791e6b4, 0x223a3540, 0xa940fef4);
            continue;
        }

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000060c1);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_00H, 0x0000307f);
        WR1_PROG(REG_2CH, 0x00000014);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_104H, 0x00000057);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, 0x00010001);

        WR1_PROG(REG_24H, 0x00004006);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00000dc0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000080c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00210000);
        SC32_function001(0xacf286fd, 0x79a93054, 0xe6d7d1db, 0xf2387e50);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0x17fa1712, 0x0c867f17, 0xea701e88, 0xb3256a88);
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000b540);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000080);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_E0H, 0x80a0000a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00008383);
            WR1_PROG(REG_2CH, 0x00000020);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_ECH, 0x0000b560);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000004);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_B0H, 0x00000700);
            WR1_PROG(REG_A4H, 0x42e0873f);
            WR1_PROG(REG_00H, 0x00001383);
            WR1_PROG(REG_2CH, 0x00000020);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00000c84);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);

            WR1_PROG(REG_A4H, 0x400009cd);
            WR1_PROG(REG_00H, 0x00001113);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_ECH, 0x38008a20);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000000);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0x2759a159, 0xdf71c4cd, 0x1c4261d9, 0x94d25a19);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_7CH, 0x00000021);
                WR1_PROG(REG_00H, 0x00005113);
                WR1_PROG(REG_74H, 0x00000004);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC32_function002(0x0b41573d, 0xb9ebfd47, 0xdf508aec, 0xb0f64886);
            }
            else
            {
                WR1_PROG(REG_7CH, 0x00000041);
                WR1_PROG(REG_00H, 0x00005113);
                WR1_PROG(REG_74H, 0x00000004);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);

                SC32_function002(0x6380cedd, 0x0d9a0712, 0x261994fa, 0xa45675d5);
            }

            WR1_PROG(REG_24H, 0x000011c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000c0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000929);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x0000b4c0);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x000000fc);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00003906);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00008d00);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0xfffffffe);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00003d06);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00000908);
            WR1_PROG(REG_1D0H, 0x00000000);
            for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_ECH, 0x000038e6);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x0000a8c0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);
                for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
                {
                    WR1_PROG(REG_ECH, 0x38008900);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x00000000);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x11816907);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    WR1_PROG(REG_ECH, 0x38008900);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x00000000);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x10002d20);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    WR1_PROG(REG_ECH, 0x000168e7);
                    WR1_PROG(REG_1D0H, 0x00000000);
                }
            }

            WR1_PROG(REG_ECH, 0x00003549);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0000a540);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000003);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x0002694a);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function001(0x34da0025, 0x0db1fb79, 0xa07eb191, 0xa6e9758e);
            WR1_PROG(REG_E0H, 0x81010140);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_04H, 0x00000607);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);

            WR1_PROG(REG_ECH, 0x000037ea);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_24H, 0x000011c0);
            WAIT_STS(REG_24H, 21, 0);

            for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000185);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_ECH, 0x000033e0);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function002(0x5fc0dc12, 0xd89634e7, 0xd72471b4, 0x5ee005f9);
            }

            WR1_PROG(REG_ECH, 0x00007c1f);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x00026d4a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00002949);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function001(0x81aa2739, 0x5d36b54d, 0x9a18bc63, 0xc92e4a56);
            WR1_PROG(REG_E0H, 0x81010140);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_04H, 0x00000607);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);

            WR1_PROG(REG_ECH, 0x000037ea);
            WR1_PROG(REG_1D0H, 0x00000000);

            for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_34H, 0x00000000);
                WR1_PROG(REG_24H, 0x2000018d);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_ECH, 0x000033e0);
                WR1_PROG(REG_1D0H, 0x00000000);

                SC32_function002(0x6975d9c8, 0x12b618f1, 0x0d2d326c, 0x32eb8d6a);
            }

            WR1_PROG(REG_ECH, 0x00007c1f);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x0000a0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000a52);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x00006404);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00006c04);
            WAIT_STS(REG_24H, 21, 0);

            for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_2CH, 0x00000010);

                for (jLoop = 0; jLoop < 32; jLoop = jLoop + 4)
                {
                    SC32_function001(0x89e933e6, 0x2c3a5c4a, 0x2f1c928b, 0x88d159d3);

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

                    SC32_function002(0xcde0922d, 0xfcf46ea5, 0x21862b4c, 0x1b89a337);
                }

                WR1_PROG(REG_ECH, 0x0000b7e0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000100);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_E0H, 0x80a0001f);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_00H, 0x00008383);
                WR1_PROG(REG_2CH, 0x00000021);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);
                WR1_PROG(REG_24H, 0x000019c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000591);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x0000c0c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x00001028);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000011c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000019c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000581);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x0000c0c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_18H, 0x00000004);
                WR1_PROG(REG_24H, 0x00009004);
                WAIT_STS(REG_18H, 10, 0); // No.1  You may release cpu resources because of polling long time(Long Polling)
                WR1_PROG(REG_24H, 0x00004404);
                WAIT_STS(REG_18H, 10, 0); // No.2  You may release cpu resources because of polling long time(Long Polling)
                WR1_PROG(REG_18H, 0x00000000);

                WR1_PROG(REG_ECH, 0x0000b7e0);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x0000017c);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x0000b420);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000004);
                WR1_PROG(REG_1D0H, 0x00000000);

                for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
                {
                    WR1_PROG(REG_ECH, 0x0000389f);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 1)
                    {
                        WR1_PROG(REG_ECH, 0x3800d880);
                        WR1_PROG(REG_1D0H, 0x00000000);
                        WR1_PROG(REG_E0H, 0x00000080);

                        WR1_PROG(REG_ECH, 0x00016884);
                        WR1_PROG(REG_1D0H, 0x00000000);

                        WR1_PROG(REG_24H, 0x0000082c);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x100019b1);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_24H, 0x000019a1);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x400040c1);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_24H, 0x0000102c);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x100019b1);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_24H, 0x000019a1);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x000080c1);
                        WAIT_STS(REG_24H, 21, 0);
                    }

                    WR1_PROG(REG_ECH, 0x00002be1);
                    WR1_PROG(REG_1D0H, 0x00000000);
                }

                WR1_PROG(REG_24H, 0x000088d0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00001028);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x100019b1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000019a1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000080c1);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x000005c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00001191);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_1CH, 0x00210000);

                WR1_PROG(REG_24H, 0x000005c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000040c1);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x000011c0);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_24H, 0x00000991);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_1CH, 0x00210000);

                SC32_function001(0x80676aae, 0xdc69007b, 0x4fa7aee3, 0xb8a8d1a0);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 0))
                {
                    WR1_PROG(REG_ECH, 0x00002e40);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    SC32_function002(0xd650b7f6, 0xc0674a8e, 0xf05d0c76, 0xfae7d000);
                }
                else
                {
                    WR1_PROG(REG_24H, 0x000019c0);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x00000591);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x000040c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function001(0xd2e8a9d6, 0xa775f6aa, 0x89e4d594, 0xf6562fe6);
                    WR1_PROG(REG_E0H, 0x81010120);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_04H, 0x00000607);
                    WAIT_STS(REG_04H, 30, 1);
                    RD1_ADDR(REG_100H, &S_RAM[1]);
                    WR1_PROG(REG_ECH, 0x000037e9);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    for (jLoop = 0; jLoop < S_RAM[1]; jLoop = jLoop + 1)
                    {
                        WR1_PROG(REG_24H, 0x000009c0);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x00001191);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_1CH, 0x00210000);

                        WR1_PROG(REG_24H, 0x000011c0);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x00000991);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_1CH, 0x00210000);

                        SC32_function001(0x4695b667, 0x2456034d, 0xd585547c, 0x920d4f9c);
                        WR1_PROG(REG_1CH, 0x00400000);
                        WR1_PROG(REG_1D0H, 0x00000000);

                        if (CHCK_STS(REG_1CH, 22, 0))
                        {
                            WR1_PROG(REG_ECH, 0x00002e40);
                            WR1_PROG(REG_1D0H, 0x00000000);

                            SC32_function002(0x7ad80694, 0xa4ff5e5b, 0x0f95e894, 0x834d1de1);
                            break;
                        }
                        else
                        {
                            WR1_PROG(REG_24H, 0x00000c2c);
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
                            WR1_PROG(REG_24H, 0x000080c1);
                            WAIT_STS(REG_24H, 21, 0);

                            SC32_function002(0xd63687b8, 0x4b9ad2fb, 0xc84f48e2, 0x71edad7b);
                        }
                    }

                    WR1_PROG(REG_ECH, 0x38008a40);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_ECH, 0x00000000);
                    WR1_PROG(REG_1D0H, 0x00000000);
                    WR1_PROG(REG_E0H, 0x00000080);
                    WR1_PROG(REG_1CH, 0x00260000);

                    SC32_function001(0x23fa5f13, 0x0f90c13a, 0x7594dd2f, 0x835fc3e6);
                    WR1_PROG(REG_1CH, 0x00400000);
                    WR1_PROG(REG_1D0H, 0x00000000);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        SC32_function002(0x16ca6076, 0x1647944d, 0x734e943b, 0xe3cfa19d);
                        break;
                    }
                    else
                    {
                        SC32_function002(0x032327d3, 0xc990a8dc, 0xf8c5e326, 0x4d1c8975);
                    }
                }
            }

            WR1_PROG(REG_ECH, 0x38000a4b);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0x1fe98ed5, 0x78e993fa, 0x77e1d05c, 0x26618f74);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_ECH, 0x00002e20);
                WR1_PROG(REG_1D0H, 0x00000000);

                WR1_PROG(REG_ECH, 0x38008a20);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_ECH, 0x00000002);
                WR1_PROG(REG_1D0H, 0x00000000);
                WR1_PROG(REG_E0H, 0x00000080);
                WR1_PROG(REG_1CH, 0x00260000);

                SC32_function001(0xad365a80, 0x318206f9, 0x6dd85eb2, 0x6f0f0831);
                WR1_PROG(REG_1CH, 0x00400000);
                WR1_PROG(REG_1D0H, 0x00000000);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    SC32_function002(0x254abe9e, 0xa88d3a43, 0xfddb55f4, 0xdaafd0ba);
                    break;
                }
                else
                {
                    WR1_PROG(REG_24H, 0x000019c0);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_24H, 0x0000e0c1);
                    WAIT_STS(REG_24H, 21, 0);

                    SC32_function002(0xaf741bb2, 0x700c2cea, 0x4abbdcc5, 0xa5426f61);
                }
            }
            else
            {
                SC32_function002(0x812fa1c3, 0x5619ffb4, 0x5fe82990, 0xb8614ea4);
            }
        }
    }

    WR1_PROG(REG_ECH, 0x38008a20);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000002);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00A60000);

    SC32_function001(0x59702151, 0xb42e11d3, 0xa46d4d85, 0x00465819);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_1C0H, 0x00010000);

        SC32_function003(0x65e03944, 0x05c5fd92, 0x6b304662, 0x484e35e1);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_C8H, 17, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    SC32_function001(0x1eab7578, 0xee0ac264, 0x0c6203a1, 0x083834a2);

    WR1_PROG(REG_ECH, 0x0000b5c0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010001);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00bf0001);

    WR1_PROG(REG_D0H, 0x00000f00);
    WR1_PROG(REG_C4H, 0x42e087bf);
    WR1_PROG(REG_00H, 0x00012303);
    WR1_PROG(REG_2CH, 0x00000024);
    WR1_PROG(REG_04H, 0x00000203);

    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[iLoop]);
    }

    SC32_function001(0x8a985911, 0xa7016d4c, 0xac3bf4b9, 0xd5b54dbf);
    WR1_PROG(REG_104H, 0x00000052);
    WR1_PROG(REG_C4H, 0x00000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_C4H, 0x400009cd);
    WR1_PROG(REG_00H, 0x00002213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_04H, 0x00000213);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[iLoop]);

    WR1_PROG(REG_28H, 0x009f0001);

    WR1_PROG(REG_24H, 0x0000b0d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x0000c8d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e8d0);
    WAIT_STS(REG_24H, 21, 0);

    while (1)
    {
        WR1_PROG(REG_24H, 0x00008006);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000011c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_1CH, 0x00210000);

        SC32_function001(0xb5930ab9, 0x3b4cb3f7, 0xeb227098, 0xafa0d1cf);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            SC32_function002(0xceca9a07, 0xd496198e, 0x43b1e5bf, 0xf3550a75);
            break;
        }
        else
        {
            WR1_PROG(REG_24H, 0x000019c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000d0d0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);

            SC32_function002(0x5631a4a9, 0xd1717a8a, 0x3796eca8, 0x67488620);
        }
    }

    WR1_PROG(REG_24H, 0x000094d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_24H, 0x0000c002);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x0000dcd0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000000);
    WR1_PROG(REG_24H, 0x0000b80a);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00bf0001);

    WR1_PROG(REG_00H, 0x000030ff);
    WR1_PROG(REG_2CH, 0x00000014);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000057);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00010001);

    WR1_PROG(REG_2CH, 0x00000002);
    WR1_PROG(REG_34H, 0x00000000);
    WR1_PROG(REG_24H, 0x0000c002);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00870001);
    WR1_PROG(REG_E0H, 0x800100c0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x0000031f);
    WR1_PROG(REG_2CH, 0x00000024);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_00H, 0x00008307);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x00bf0001);
    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b500);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010001);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_24H, 0x000005c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    while (1)
    {
        WR1_PROG(REG_ECH, 0x0000094a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x80c0000a);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00018303);
        WR1_PROG(REG_2CH, 0x00000022);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_B0H, 0x00000f14);
        WR1_PROG(REG_A4H, 0x00008a07);
        WR1_PROG(REG_00H, 0x00011303);
        WR1_PROG(REG_2CH, 0x00000020);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_28H, 0x009f0001);
        WR1_PROG(REG_24H, 0x000019c0);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x0000a0c1);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000080d0);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_28H, 0x00870001);
        WR1_PROG(REG_00H, 0x0000301f);
        WR1_PROG(REG_2CH, 0x00000014);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_E0H, 0x810100c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003807);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_00H, 0x0000301f);
        WR1_PROG(REG_2CH, 0x00000010);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_E0H, 0x81010100);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x00003807);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_2CH, 0x00000000);
        WR1_PROG(REG_34H, 0x00000800);
        WR1_PROG(REG_24H, 0x8000c002);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_ECH, 0x00003506);
        WR1_PROG(REG_1D0H, 0x00000000);

        WR1_PROG(REG_E0H, 0x800100c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_00H, 0x0000031f);
        WR1_PROG(REG_2CH, 0x0000002c);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);
        WR1_PROG(REG_00H, 0x00008307);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800);

        WR1_PROG(REG_ECH, 0x380088c0);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_ECH, 0x00000000);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x732e288e, 0xa0e0164c, 0x7dee8189, 0xc08b74cb);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_28H, 0x00bf0001);
            WR1_PROG(REG_104H, 0x00003f61);
            WR1_PROG(REG_B0H, 0x00000f00);
            WR1_PROG(REG_A4H, 0x42f487bf);
            WR1_PROG(REG_00H, 0x00013103);
            WR1_PROG(REG_2CH, 0x00000014);

            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &S_HEAP[iLoop]);
            }

            SC32_function002(0xb52b78dc, 0xf81f90fe, 0xe2603270, 0xc9d670b9);
            break;
        }
        else
        {
            WR1_PROG(REG_28H, 0x009f0001);
            WR1_PROG(REG_24H, 0x000015c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000c0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_00H, 0x00003083);
            WR1_PROG(REG_2CH, 0x00000011);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_28H, 0x00bf0001);

            WR1_PROG(REG_34H, 0x00000000);
            WR1_PROG(REG_24H, 0x0000880e);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_D0H, 0x00000f1C);
            WR1_PROG(REG_C4H, 0x00008a83);
            WR1_PROG(REG_00H, 0x00013203);
            WR1_PROG(REG_2CH, 0x00000012);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            WR1_PROG(REG_24H, 0x000009c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00001191);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x0000094a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x81c0000a);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_00H, 0x00013803);
            WR1_PROG(REG_2CH, 0x00000010);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800);

            SC32_function002(0x5eaea3fd, 0xd27bfe50, 0x777d340a, 0x8074c61a);
        }
    }

    WR1_PROG(REG_ECH, 0x00007c06);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_1CH, 0x00602000);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_104H, 0x00000361);
    WR1_PROG(REG_A4H, 0x400007bd);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[iLoop]);

    WR1_PROG(REG_A4H, 0x00800c45);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0x009f0001);
    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004);

    WR1_PROG(REG_24H, 0x00008404);
    WAIT_STS(REG_18H, 10, 0);          // No.3  You may release cpu resources because of polling long time(Long Polling)

    WR1_PROG(REG_24H, 0x00009004);
    WAIT_STS(REG_18H, 10, 0);          // No.4  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_24H, 0x0000102c);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000908);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00008);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004);

    WR1_PROG(REG_24H, 0x00008404);
    WAIT_STS(REG_18H, 10, 0);          // No.5  You may release cpu resources because of polling long time(Long Polling)

    WR1_PROG(REG_24H, 0x00009004);
    WAIT_STS(REG_18H, 10, 0);          // No.6  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b500);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a00008);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000015c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00008907);
    WAIT_STS(REG_18H, 10, 0);          // No.7  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_24H, 0x00001dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000581);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000e0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_B0H, 0x00000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000015c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00008807);
    WAIT_STS(REG_18H, 10, 0);          // No.8  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000581);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_B0H, 0x08000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xae3a4a1c, 0xd23ecf12, 0xbd9020d3, 0xdac4d807);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000024);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[96 + lLoop]);
    }

    SC32_function001(0x1c7c8ce6, 0x0a0a8e55, 0x396f53fa, 0xbb9c075b);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000025);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[32 + lLoop]);
    }

    SC32_function001(0x24bb4d00, 0xd3725023, 0x54546ea5, 0x2670d904);
    WR1_PROG(REG_D0H, 0x0800071C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000283);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[64 + iLoop]);
    }

    SC32_function001(0xce69826e, 0xc6e0611d, 0x270bb783, 0x1383d4f4);
    WR1_PROG(REG_D0H, 0x0000071C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_04H, 0x00000283);
    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[iLoop]);
    }

    WR1_PROG(REG_B0H, 0x00000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000023);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_B0H, 0x08000714);
    WR1_PROG(REG_A4H, 0x00008a07);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b4e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a00007);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000060c1);
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

    WR1_PROG(REG_24H, 0x0000082c);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000828);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000040c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80a0001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008383);
    WR1_PROG(REG_2CH, 0x00000021);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000017c);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_ECH, 0x0000381f);
        WR1_PROG(REG_1D0H, 0x00000000);

        for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x3800d800);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);

            WR1_PROG(REG_ECH, 0x00016800);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x0000082c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x400040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x0000102c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
        }

        WR1_PROG(REG_ECH, 0x00002be1);
        WR1_PROG(REG_1D0H, 0x00000000);
    }

    WR1_PROG(REG_24H, 0x000088d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001028);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x100019b1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019a1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000080c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x000019c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000a0c1);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_34H, 0x00000000);
    WR1_PROG(REG_2CH, 0x00000002);
    WR1_PROG(REG_24H, 0x00007b0a);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_2CH, 0x00000011);
    WR1_PROG(REG_104H, 0x00000057);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x80000000);
    WR1_PROG(REG_00H, 0x0000307f);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x00000dc0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001591);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00402000);
    WR1_PROG(REG_1D0H, 0x00000000);

    SC32_function001(0x99082dfb, 0x8164f22c, 0x5c1d8c82, 0xc9b7d0e1);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000020);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_DomainParam[128 + lLoop]);
    }

    SC32_function001(0x67ec926a, 0x42241ac9, 0x42c9981d, 0x76f99606);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000023);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_N[0 + lLoop]);
    }

    SC32_function001(0x13f55b1b, 0x5782e411, 0xc18cf5c2, 0x1ae281f4);
    WR1_PROG(REG_D0H, 0x00000700);
    WR1_PROG(REG_C4H, 0x00008887);
    WR1_PROG(REG_00H, 0x00002383);
    WR1_PROG(REG_2CH, 0x00000022);

    WR1_PROG(REG_04H, 0x00000282);
    for (lLoop = 0; lLoop < 32; lLoop = lLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_C0H, &OutData_N[32 + lLoop]);
    }

    SC32_function001(0x9b4ca98e, 0xc50f8865, 0x4eb4d38d, 0x36170ef0);

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

    WR1_PROG(REG_E0H, 0x80040000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00008213);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    SC32_function001(0xfdd182f8, 0xa5a54ea4, 0xd43b3e44, 0xe8894764);
    WR1_PROG(REG_E0H, 0x81010000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_C4H, 0x00000884);
    WR1_PROG(REG_00H, 0x00002807);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_04H, 0x00000207);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_C0H, &OutData_KeyIndex[0]);
    WR1_PROG(REG_00H, 0x0000020f);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_C4H, 0x200c3b0c);
    WR1_PROG(REG_E0H, 0x81010000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00002807);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_C4H, 0x000c0b0c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x6d5eba26);

    SC32_function001(0x1ca1a626, 0xcd536958, 0xf0192e3f, 0x1fcfa0f0);
    WR1_PROG(REG_D0H, 0x00000f1C);
    WR1_PROG(REG_C4H, 0x00008a83);

    WR1_PROG(REG_B0H, 0x00000f00);
    WR1_PROG(REG_A4H, 0x02e487bf);

    WR1_PROG(REG_00H, 0x00011203);
    WR1_PROG(REG_04H, 0x00000103);
    for (iLoop = 1; iLoop < 65; iLoop = iLoop + 4)
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_A0H, &OutData_KeyIndex[iLoop]);
    }

    SC32_function001(0xc243dd99, 0xe821d8fb, 0xa25983f8, 0x7af3354f);
    WR1_PROG(REG_104H, 0x00000351);
    WR1_PROG(REG_A4H, 0x000009cd);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H, 0x00000000, 0x00000000, 0x00000000, 0x00000010);

    WR1_PROG(REG_04H, 0x00000113);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_A0H, &OutData_KeyIndex[iLoop]);

    WR1_PROG(REG_B0H, 0x00000700);
    WR1_PROG(REG_A4H, 0x43e0873f);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000025);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_A4H, 0x4106094d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_7CH, 0x00000021);
    WR1_PROG(REG_A4H, 0x01800c05);
    WR1_PROG(REG_00H, 0x00001513);
    WR1_PROG(REG_74H, 0x00000008);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_B0H, 0x00000700);
    WR1_PROG(REG_A4H, 0x43e0873f);
    WR1_PROG(REG_00H, 0x00001383);
    WR1_PROG(REG_2CH, 0x00000024);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    WR1_PROG(REG_104H, 0x00000051);
    WR1_PROG(REG_A4H, 0x01000c84);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x00000000);

    WR1_PROG(REG_A4H, 0x4106094d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_7CH, 0x00000041);
    WR1_PROG(REG_A4H, 0x01800c05);
    WR1_PROG(REG_00H, 0x00001513);
    WR1_PROG(REG_74H, 0x00000008);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_28H, 0xfcbf0001);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x0000c0c1);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000100);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80c0001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_D0H, 0x00000f1C);
    WR1_PROG(REG_C4H, 0x00008a83);
    WR1_PROG(REG_00H, 0x00018203);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_2CH, 0x00000010);
    WR1_PROG(REG_104H, 0x00003f57);
    WAIT_STS(REG_104H, 31, 1);
    WR64_PROG(REG_100H,
              0x7FFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFFF,
              0xFFFFFFAB);

    WR1_PROG(REG_ECH, 0x0000094a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x80c0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00018303);
    WR1_PROG(REG_2CH, 0x00000020);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00009004);
    WAIT_STS(REG_18H, 10, 0);          // No.9  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_24H, 0x00004404);
    WAIT_STS(REG_18H, 10, 0);          // No.10  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b7e0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x000001fc);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b420);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000004);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (iLoop = 0; iLoop < 64; iLoop = iLoop + 1)
    {
        WR1_PROG(REG_ECH, 0x0000389f);
        WR1_PROG(REG_1D0H, 0x00000000);

        for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
        {
            WR1_PROG(REG_ECH, 0x3800d880);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);

            WR1_PROG(REG_ECH, 0x00016884);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_24H, 0x0000082c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x400040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x0000102c);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
        }

        WR1_PROG(REG_ECH, 0x00002be1);
        WR1_PROG(REG_1D0H, 0x00000000);
    }

    WR1_PROG(REG_24H, 0x000088d0);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00bf0001);

    WR1_PROG(REG_24H, 0x000050d0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_18H, 0x00000004);
    WR1_PROG(REG_24H, 0x00008404);
    WAIT_STS(REG_18H, 10, 0);          // No.11  You may release cpu resources because of polling long time(Long Polling)
    WR1_PROG(REG_18H, 0x00000000);

    WR1_PROG(REG_ECH, 0x0000b400);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00010001);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00000bff);
    WR1_PROG(REG_1D0H, 0x00000000);

    for (jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        WR1_PROG(REG_ECH, 0x00002fe0);
        WR1_PROG(REG_1D0H, 0x00000000);

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

        SC32_function001(0xdbf09b75, 0xd0b7dce0, 0x81216b90, 0xb3355281);
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

            SC32_function002(0xc056b953, 0x9edb6348, 0x81c97ff6, 0x3d0248e0);
        }
        else
        {
            SC32_function002(0x15994fb9, 0xb74430fc, 0x3074cb09, 0x26fc7aac);
        }
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

    WR1_PROG(REG_28H, 0x00bf0001);

    WR1_PROG(REG_ECH, 0x0000094a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WR1_PROG(REG_2CH, 0x00000012);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_ECH, 0x0000b540);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000080);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x81a0000a);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_00H, 0x00003883);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);

    WR1_PROG(REG_24H, 0x000009c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00001191);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_24H, 0x000011c0);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000991);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_1CH, 0x00210000);

    WR1_PROG(REG_1CH, 0x00402000);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_1C0H, 0x00010000);

    SC32_function003(0xa7096e31, 0x571453a8, 0x4e050bd2, 0x204ed9ef);
    WR1_PROG(REG_1BCH, 0x00000040);
    WAIT_STS(REG_C8H, 17, 0);

    return FSP_SUCCESS;
}
