/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

//////////////////////////////////////////////////////////////////////////
// <SC32#2 subprocedure 05>                                             //
// File name            : SC32_subprc05.prc                             //
//////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_private.h"

void SC32_Subprc05 (void) {
    WR1_PROG(REG_ECH, 0x38008fc0);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x0000001f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x1000381f);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x100027e1);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x00002fc0);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x38008c00);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x80000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x20002c40);
    WR1_PROG(REG_1D0H, 0x00000000);

    WR1_PROG(REG_ECH, 0x38008840);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_ECH, 0x00000000);
    WR1_PROG(REG_1D0H, 0x00000000);
    WR1_PROG(REG_E0H, 0x00000080);
    WR1_PROG(REG_1CH, 0x00A60000);

    SC32_function001(0x196f6f7e, 0x891ccabb, 0xe478ae6b, 0xc8fb9e55);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_ECH, 0x3800d81f);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00A60000);

        SC32_function001(0x1148971b, 0x476d53df, 0xc78c7f4c, 0x690c174f);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_24H, 0x00009cd0);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x0000302c);
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

            WR1_PROG(REG_24H, 0x0000282c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00000863);
            WR1_PROG(REG_1D0H, 0x00000000);

            WR1_PROG(REG_ECH, 0x38008840);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000001);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0xb42a9dd6, 0xe51f912c, 0x517fbb4e, 0x72c2b5fd);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_34H, 0x00000800);
                WR1_PROG(REG_24H, 0x800088d0);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0x0463aea4, 0xc241ac12, 0xd99713b2, 0xf8f7f0e6);
            }

            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00002c2c);
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

            WR1_PROG(REG_24H, 0x0000282c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_34H, 0x00000280);
            WR1_PROG(REG_24H, 0x800019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x38008840);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000001);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0x4d445db7, 0xb167bd63, 0x2b737a50, 0xa72a1f7c);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_34H, 0x00000800);
                WR1_PROG(REG_24H, 0x8000a8d0);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0x9b09ecad, 0xbbaa4d1d, 0xcae5140e, 0x2475aa79);
            }

            WR1_PROG(REG_34H, 0x00000080);
            WR1_PROG(REG_24H, 0x800080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00002c2c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x38008840);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000001);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0xedcb018d, 0xb4efff1b, 0xf6f573e0, 0x49d6d67d);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000040c1);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0x6c502de5, 0x104091b2, 0x21b8813d, 0x2166f09a);
            }
            else
            {
                WR1_PROG(REG_24H, 0x0000e0c1);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0x5455f217, 0xde8f361e, 0xd2e9de58, 0xe4380793);
            }

            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000060c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00002c2c);
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
            WR1_PROG(REG_24H, 0x0000282c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00008cd0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00000951);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x38008840);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000001);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0x165cff9e, 0x9f9b552e, 0xc19d6519, 0x42624ede);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000060c1);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0xa6cc0f5a, 0xd0672785, 0x4b753ee3, 0xa2e2a5b3);
            }
            else
            {
                WR1_PROG(REG_34H, 0x00000800);
                WR1_PROG(REG_24H, 0x800080c1);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0x57dc6511, 0xbe0152c2, 0xbe41242f, 0x49a948cb);
            }

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
            WR1_PROG(REG_24H, 0x0000282c);
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
            WR1_PROG(REG_24H, 0x00002c2c);
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

            WR1_PROG(REG_ECH, 0x38008840);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_ECH, 0x00000001);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_E0H, 0x00000080);
            WR1_PROG(REG_1CH, 0x00260000);

            SC32_function001(0x9fa63bbb, 0x5a35ca20, 0x5796c278, 0x16ac92a9);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x000060c1);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0x9b39da4c, 0x23402783, 0x64fd243a, 0x98f031b3);
            }
            else
            {
                WR1_PROG(REG_34H, 0x00000800);
                WR1_PROG(REG_24H, 0x8000a0c1);
                WAIT_STS(REG_24H, 21, 0);
                SC32_function002(0xa4b7ed2a, 0x654952a0, 0x71189fc3, 0x9923ed93);
            }
        }
        else
        {
            SC32_function002(0xac3b607a, 0x7f28d5e1, 0xc1c864ee, 0x8edc6481);
        }

        WR1_PROG(REG_ECH, 0x38000bc4);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_E0H, 0x00000080);
        WR1_PROG(REG_1CH, 0x00260000);

        SC32_function001(0x056c28d0, 0xae4a12e6, 0x48c7d01b, 0xa5420ea6);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x00002f80);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function001(0xf53cab35, 0x08ba8507, 0x39c38289, 0x4f142beb);
            WR1_PROG(REG_E0H, 0x81010380);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_04H, 0x00000607);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);

            WR1_PROG(REG_ECH, 0x00007c1d);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);
        }
        else
        {
            WR1_PROG(REG_24H, 0x00009cd0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000020);
            WR1_PROG(REG_24H, 0x80005cd0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000070d0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000208);
            WR1_PROG(REG_24H, 0x800011c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000282c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_34H, 0x00000080);
            WR1_PROG(REG_24H, 0x800080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000149);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00001141);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000941);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000080);
            WR1_PROG(REG_24H, 0x800040c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000008);
            WR1_PROG(REG_24H, 0x800094d0);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_34H, 0x00000200);
            WR1_PROG(REG_24H, 0x800019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00002c2c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00000149);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x0000e0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000282c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_34H, 0x00000200);
            WR1_PROG(REG_24H, 0x800002d1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000009c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000149);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000149);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000149);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000080);
            WR1_PROG(REG_24H, 0x800080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000060c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000302c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00000d51);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_34H, 0x00000800);
            WR1_PROG(REG_24H, 0x800080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000060c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000009c0);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000d51);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000040c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000080);
            WR1_PROG(REG_24H, 0x8000014a);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000149);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x00000149);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000080);
            WR1_PROG(REG_24H, 0x800080c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x000060c1);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x0000282c);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x100019b1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00000d51);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x000019a1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_34H, 0x00000800);
            WR1_PROG(REG_24H, 0x8000a0c1);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x00016c00);
            WR1_PROG(REG_1D0H, 0x00000000);

            SC32_function002(0x10c3b68c, 0x6afcc9f2, 0xb092d21d, 0x16344c55);

            WR1_PROG(REG_ECH, 0x00007c1d);
            WR1_PROG(REG_1D0H, 0x00000000);
            WR1_PROG(REG_1CH, 0x00602000);
            WR1_PROG(REG_1D0H, 0x00000000);
        }
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00016c00);
        WR1_PROG(REG_1D0H, 0x00000000);

        SC32_function002(0x5c3721f7, 0x23b82b85, 0x457cf39c, 0x5705e009);

        WR1_PROG(REG_ECH, 0x00007c1d);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_1CH, 0x00602000);
        WR1_PROG(REG_1D0H, 0x00000000);
    }
}
