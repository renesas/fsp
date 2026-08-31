/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub (uint32_t InData_KeyType[],
                                          uint32_t InData_DataType[],
                                          uint32_t InData_Cmd[],
                                          uint32_t InData_TextLen[],
                                          uint32_t InData_MACLength[],
                                          uint32_t InData_KeyIndex[],
                                          uint32_t InData_IV[],
                                          uint32_t InData_Header[],
                                          uint32_t Header_Len,
                                          uint32_t InData_SeqNum[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00009802U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    WR1_PROG(REG_ECH, 0x00003640U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010120U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[0]);

    HW_SCE_p_func_sub007(0x00003689U, 0x3420a800U, 0x00000004U, 0x00260000U);

    static const uint32_t Param_p98i_func100_001[] =
    {
        0xfe107021U, 0x2c0bf976U, 0x0a0ae754U, 0x1e187b81U,
    };
    HW_SCE_p_func100(Param_p98i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_104H, 0x00000068U);
        WR1_PROG(REG_E0H, 0x80010140U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_MACLength[0]);

        static const uint32_t Param_p98i_func101_001[] =
        {
            0x3c23d9a5U, 0x7bbd6cf0U, 0x954672a7U, 0xff301ed1U,
        };
        HW_SCE_p_func101(Param_p98i_func101_001);
    }
    else
    {
        WR1_PROG(REG_ECH, 0x0000b540U);
        HW_SCE_p_func_sub007(0x00000010U, 0x3420a920U, 0x00004101U, 0x00A60000U);

        static const uint32_t Param_p98i_func101_002[] =
        {
            0xf28b6b15U, 0x24b88936U, 0x4951718eU, 0x8e28568eU,
        };
        HW_SCE_p_func101(Param_p98i_func101_002);
    }

    HW_SCE_p_func_sub007(0x0000366aU, 0x38008800U, 0x00000001U, 0x00260000U);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000003U, 0x00260000U);

    static const uint32_t Param_p98i_func100_002[] =
    {
        0xbd03be63U, 0x5acfa017U, 0x59c64d67U, 0xbe89ce07U,
    };
    HW_SCE_p_func100(Param_p98i_func100_002);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p98i_func102_001[] =
        {
            0xae46d292U, 0x9874cb67U, 0x2f89dc77U, 0xeff862dcU,
        };
        HW_SCE_p_func102(Param_p98i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub014(0x3420a800U, 0x00000004U, 0x00260000U);

        static const uint32_t Param_p98i_func100_003[] =
        {
            0x09231be9U, 0x79a7045fU, 0x8615bd3cU, 0x92350c8fU,
        };
        HW_SCE_p_func100(Param_p98i_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x38000c00U);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p98i_func100_004[] =
            {
                0x7e64c5d2U, 0xe0328a9cU, 0xdc55cc93U, 0xdc40b046U,
            };
            HW_SCE_p_func100(Param_p98i_func100_004);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x800100e0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000098U);

                static const uint32_t Param_p98i_func101_003[] =
                {
                    0xbe95e98fU, 0x7b14d868U, 0x22a9108bU, 0x3bdfa7caU,
                };
                HW_SCE_p_func101(Param_p98i_func101_003);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000005U);

                static const uint32_t Param_p98i_func101_004[] =
                {
                    0xe1c588a8U, 0xa185ea37U, 0x92a8ebc2U, 0xc6ba3e53U,
                };
                HW_SCE_p_func101(Param_p98i_func101_004);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010140U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000098U);

                static const uint32_t Param_p98i_func101_005[] =
                {
                    0xeb42863fU, 0x3cb151c3U, 0x49401fc4U, 0x89c0987dU,
                };
                HW_SCE_p_func101(Param_p98i_func101_005);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x0146c04bU);

                static const uint32_t Param_p98i_func101_006[] =
                {
                    0xa49f0b45U, 0xd0e46b3fU, 0x49506eb0U, 0xd0040c29U,
                };
                HW_SCE_p_func101(Param_p98i_func101_006);
            }

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000098U);

            static const uint32_t Param_p98i_func101_007[] =
            {
                0xbc08b804U, 0x074e9f88U, 0xdf36e17aU, 0x02c44201U,
            };
            HW_SCE_p_func101(Param_p98i_func101_007);
            HW_SCE_p_func044();

            static const uint32_t Param_p98i_func100_005[] =
            {
                0x5ee543bbU, 0xbe019c49U, 0x44a68e5fU, 0xf3593618U,
            };
            HW_SCE_p_func100(Param_p98i_func100_005);
            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

            WR1_PROG(REG_A4H, 0x00080805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p98i_func101_008[] =
            {
                0x5b0413a5U, 0xa11b707fU, 0xedf9c29dU, 0xda19fd49U,
            };
            HW_SCE_p_func101(Param_p98i_func101_008);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010020U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_DataType[0]);

            WR1_PROG(REG_ECH, 0x38000c21U);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p98i_func100_006[] =
            {
                0xe3098454U, 0xc5646dafU, 0x43b2527cU, 0x7b5261bbU,
            };
            HW_SCE_p_func100(Param_p98i_func100_006);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010000U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_Cmd[0]);

                WR1_PROG(REG_ECH, 0x000036a0U);

                WR1_PROG(REG_ECH, 0x0000b6c0U);
                HW_SCE_p_func_sub005(0x0126ee7fU, 0x00000058U, 0x800103a0U, 0x00000098U);

                static const uint32_t Param_p98i_func101_009[] =
                {
                    0x4e489fcfU, 0x7cfb3977U, 0xa5adde78U, 0x250da5b6U,
                };
                HW_SCE_p_func101(Param_p98i_func101_009);
                HW_SCE_p_func082();

                static const uint32_t Param_p98i_func101_010[] =
                {
                    0x59da29ceU, 0x415bccc5U, 0xe8dfcb7cU, 0xb3723783U,
                };
                HW_SCE_p_func101(Param_p98i_func101_010);
            }
            else
            {
                HW_SCE_p_func_sub009(0x800103a0U, 0x00000003U);

                static const uint32_t Param_p98i_func101_011[] =
                {
                    0x7ea7e6a2U, 0xc14df11eU, 0xd569df01U, 0x574f3714U,
                };
                HW_SCE_p_func101(Param_p98i_func101_011);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                HW_SCE_p_func_sub005(0x01bae316U, 0x00000058U, 0x800103a0U, 0x000000ccU);

                static const uint32_t Param_p98i_func101_012[] =
                {
                    0x4fd122aeU, 0x6ada8620U, 0xc9d4c5d4U, 0xf5c020a0U,
                };
                HW_SCE_p_func101(Param_p98i_func101_012);
                HW_SCE_p_func044();

                static const uint32_t Param_p98i_func101_013[] =
                {
                    0xf8e909e8U, 0x331dcfacU, 0xa20d2e22U, 0xc7fc901bU,
                };
                HW_SCE_p_func101(Param_p98i_func101_013);
            }

            static const uint32_t Param_p98i_func100_007[] =
            {
                0x11a07849U, 0x2d785852U, 0x5c07f7f2U, 0xdbf9049aU,
            };
            HW_SCE_p_func100(Param_p98i_func100_007);
            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

            WR1_PROG(REG_A4H, 0x00080805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x00f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

            WR1_PROG(REG_E0H, 0x80040080U);
            WR1_PROG(REG_00H, 0x00008213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p98i_func101_014[] =
            {
                0x4848b446U, 0x27c3f86dU, 0xebb9a2edU, 0x8234670cU,
            };
            HW_SCE_p_func101(Param_p98i_func101_014);
        }

        static const uint32_t Param_p98i_func100_008[] =
        {
            0xf37c41eaU, 0x7aab28dfU, 0x4f0813bbU, 0x6fb28ef5U,
        };
        HW_SCE_p_func100(Param_p98i_func100_008);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p98i_func102_002[] =
            {
                0x9d0c2ad1U, 0x2653702aU, 0xc270905cU, 0xbdfc186cU,
            };
            HW_SCE_p_func102(Param_p98i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_ECH, 0x00003534U);

            WR1_PROG(REG_ECH, 0x00003553U);

            HW_SCE_p_func_sub007(0x00003412U, 0x3420a800U, 0x00000004U, 0x00260000U);

            static const uint32_t Param_p98i_func100_009[] =
            {
                0xc912f1edU, 0x89adc8ebU, 0xebc24832U, 0x23f70182U,
            };
            HW_SCE_p_func100(Param_p98i_func100_009);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040885U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                HW_SCE_p_func_sub019(0x00060805U, 0x00001113U);

                HW_SCE_p_func_sub021(0x00000734U);

                HW_SCE_p_func_sub021(0x00050804U);

                WR1_PROG(REG_104H, 0x000000b1U);
                WR1_PROG(REG_A4H, 0x00f00806U);

                for (iLoop = 0U; iLoop < Header_Len; )
                {
                    WAIT_STS(REG_104H, 31, 1);
                    WR4_ADDR(REG_100H, &InData_Header[iLoop]);
                    iLoop = iLoop + 4U;
                }

                HW_SCE_p_func205();

                static const uint32_t Param_p98i_func101_015[] =
                {
                    0x682f0742U, 0x7794d1a8U, 0x2c15c7acU, 0x13c0d6c9U,
                };
                HW_SCE_p_func101(Param_p98i_func101_015);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000168U);
                WR1_PROG(REG_E0H, 0x800201c0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[0]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[1]);

                HW_SCE_p_func_sub022(0x000008aeU, 0x000008cfU, 0x0000b460U, 0x00000002U);

                HW_SCE_p_func_sub022(0x01986c64U, 0x01986c85U, 0x01986ca6U, 0x00186cc6U);

                WR1_PROG(REG_A4H, 0x00040885U);
                HW_SCE_p_func_sub010(0x81040060U, 0x00001813U);

                HW_SCE_p_func_sub019(0x00060805U, 0x00001113U);

                HW_SCE_p_func_sub021(0x00000734U);

                HW_SCE_p_func_sub021(0x00050804U);

                HW_SCE_p_func031(InData_Header);

                static const uint32_t Param_p98i_func101_016[] =
                {
                    0x70b3f957U, 0x0e7e6b9cU, 0xa46cfd01U, 0xce71fd1bU,
                };
                HW_SCE_p_func101(Param_p98i_func101_016);
            }

            static const uint32_t Param_p98i_func100_010[] =
            {
                0xb06f69d5U, 0xdac52fbaU, 0xdaf8b050U, 0x579e944cU,
            };
            HW_SCE_p_func100(Param_p98i_func100_010);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p98i_func102_003[] =
                {
                    0xba154afaU, 0x74164f03U, 0x73419898U, 0x92ca8b80U,
                };
                HW_SCE_p_func102(Param_p98i_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p98i_func101_017[] =
                {
                    0xdfba0f27U, 0x0eb92c21U, 0xf0a41467U, 0xe83e652fU,
                };
                HW_SCE_p_func101(Param_p98i_func101_017);

                return FSP_SUCCESS;
            }
        }
    }
}
