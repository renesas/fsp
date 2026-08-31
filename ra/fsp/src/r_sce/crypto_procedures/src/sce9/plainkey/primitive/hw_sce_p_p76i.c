/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha256HmacInitSub (uint32_t InData_KeyType[], uint32_t InData_KeyIndex[], uint32_t LEN)
{
    uint32_t InData_Cmd[1] = {0};
    (void) LEN;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00007602U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_7CH, 0x00000011U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000003U, 0x00260000U);

    static const uint32_t Param_p76i_func100_001[] =
    {
        0x42507e18U, 0xb60252ceU, 0x59a423edU, 0x32e93062U,
    };
    HW_SCE_p_func100(Param_p76i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p76i_func102_001[] =
        {
            0xc37eabffU, 0x387e2530U, 0xdddaf1e4U, 0xc598a37bU,
        };
        HW_SCE_p_func102(Param_p76i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        HW_SCE_p_func_sub014(0x38008800U, 0x00000002U, 0x00260000U);

        static const uint32_t Param_p76i_func100_002[] =
        {
            0x7b47afd6U, 0x7d3fd654U, 0xd668f641U, 0x86ef5ef4U,
        };
        HW_SCE_p_func100(Param_p76i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x38000c00U);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p76i_func100_003[] =
            {
                0x21e049acU, 0xee0fef1cU, 0xa39aed15U, 0x10a4a162U,
            };
            HW_SCE_p_func100(Param_p76i_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x800100e0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000076U);

                static const uint32_t Param_p76i_func101_001[] =
                {
                    0x367adaa1U, 0x7284198dU, 0xbf2df312U, 0xe8ccb82dU,
                };
                HW_SCE_p_func101(Param_p76i_func101_001);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x0000001bU);

                static const uint32_t Param_p76i_func101_002[] =
                {
                    0x16a9bc34U, 0xb50d353fU, 0x339765ffU, 0xf23ade49U,
                };
                HW_SCE_p_func101(Param_p76i_func101_002);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010140U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000076U);

                static const uint32_t Param_p76i_func101_003[] =
                {
                    0x6428f417U, 0xce057e0dU, 0x9eb8d8caU, 0x8ecbc8e2U,
                };
                HW_SCE_p_func101(Param_p76i_func101_003);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x01e3697fU);

                static const uint32_t Param_p76i_func101_004[] =
                {
                    0xb0d1cfbaU, 0x1be9ec0fU, 0xfbe95721U, 0x3ff33801U,
                };
                HW_SCE_p_func101(Param_p76i_func101_004);
            }

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000076U);

            static const uint32_t Param_p76i_func101_005[] =
            {
                0x85c3ea34U, 0x0e0d6a2aU, 0x535039d6U, 0x637735f0U,
            };
            HW_SCE_p_func101(Param_p76i_func101_005);
            HW_SCE_p_func044();

            HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

            WR1_PROG(REG_E0H, 0x80080000U);
            WR1_PROG(REG_00H, 0x00008223U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            WR1_PROG(REG_ECH, 0x0000b760U);
            WR1_PROG(REG_ECH, 0x00003000U);

            static const uint32_t Param_p76i_func101_006[] =
            {
                0x2deea867U, 0xb7d5bae0U, 0x3157a392U, 0x9b767470U,
            };
            HW_SCE_p_func101(Param_p76i_func101_006);
        }
        else
        {
            HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

            static const uint32_t Param_p76i_func100_004[] =
            {
                0xf9416e2fU, 0x86f70075U, 0x5e5d5510U, 0x5f6eddcfU,
            };
            HW_SCE_p_func100(Param_p76i_func100_004);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000368U);
                WR1_PROG(REG_E0H, 0x80040000U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[1]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[2]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[3]);

                HW_SCE_p_func_sub022(0x00000bdeU, 0x000037e0U, 0x00008fe0U, 0x00ff0000U);
                HW_SCE_p_func_sub022(0x38008be0U, 0x00020000U, 0x1000d3c0U, 0x000037e0U);

                HW_SCE_p_func_sub022(0x38008fe0U, 0x00003000U, 0x2000d3c1U, 0x00003760U);
                HW_SCE_p_func_sub022(0x00008f60U, 0x00003000U, 0x000037e0U, 0x00008fe0U);
                WR1_PROG(REG_ECH, 0x000000feU);

                WR1_PROG(REG_ECH, 0x38008be0U);
                WR1_PROG(REG_ECH, 0x00000000U);
                HW_SCE_p_func_sub007(0x1000d3c2U, 0x38008bc0U, 0x00000007U, 0x00A60000U);

                WR1_PROG(REG_ECH, 0x00003540U);
                WR1_PROG(REG_ECH, 0x00003561U);
                WR1_PROG(REG_ECH, 0x00003582U);
                HW_SCE_p_func_sub005(0x000035a3U, 0x00000058U, 0x800103a0U, 0x00000076U);

                static const uint32_t Param_p76i_func101_007[] =
                {
                    0xa21aea54U, 0x1230205eU, 0x72365073U, 0xe9fd7131U,
                };
                HW_SCE_p_func101(Param_p76i_func101_007);
                HW_SCE_p_func059();

                HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[4]);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_KeyIndex[8]);

                WR1_PROG(REG_E0H, 0x80080000U);
                WR1_PROG(REG_00H, 0x00008223U);
                HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[12]);

                HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

                static const uint32_t Param_p76i_func101_008[] =
                {
                    0x0f08784aU, 0x6264fe2eU, 0x436ab374U, 0xbbca3172U,
                };
                HW_SCE_p_func101(Param_p76i_func101_008);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010000U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_Cmd[0]);

                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010280U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                WR1_PROG(REG_ECH, 0x00003554U);

                WR1_PROG(REG_ECH, 0x000036a0U);

                WR1_PROG(REG_ECH, 0x0000b6c0U);
                HW_SCE_p_func_sub005(0x01249674U, 0x00000058U, 0x800103a0U, 0x00000076U);

                static const uint32_t Param_p76i_func101_009[] =
                {
                    0x87ab1ca1U, 0xbcd597d8U, 0x2111f755U, 0x6521a6caU,
                };
                HW_SCE_p_func101(Param_p76i_func101_009);
                HW_SCE_p_func082();

                WR1_PROG(REG_ECH, 0x0000b760U);
                WR1_PROG(REG_ECH, 0x00003000U);

                HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

                WR1_PROG(REG_E0H, 0x80080000U);
                WR1_PROG(REG_00H, 0x00008223U);
                HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

                HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

                static const uint32_t Param_p76i_func101_010[] =
                {
                    0xe19400bcU, 0x1a449204U, 0xded3fd25U, 0x97e68e25U,
                };
                HW_SCE_p_func101(Param_p76i_func101_010);
            }

            static const uint32_t Param_p76i_func101_011[] =
            {
                0x1173e310U, 0xd26794b2U, 0x3a238f9bU, 0x670a16daU,
            };
            HW_SCE_p_func101(Param_p76i_func101_011);
        }

        static const uint32_t Param_p76i_func100_005[] =
        {
            0x063a8108U, 0x8c07b7a6U, 0x7e2e826fU, 0xe2a527e9U,
        };
        HW_SCE_p_func100(Param_p76i_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p76i_func102_002[] =
            {
                0x618eda6cU, 0xd48d8015U, 0xaa3ad2fbU, 0xb0d44b36U,
            };
            HW_SCE_p_func102(Param_p76i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_7CH, 0x00000011U);
            WR1_PROG(REG_104H, 0x00000754U);
            WR1_PROG(REG_74H, 0x00000004U);
            WAIT_STS(REG_104H, 31, 1);
            WR8_PROG(REG_100H,
                     change_endian_long(0x6a09e667U),
                     change_endian_long(0xbb67ae85U),
                     change_endian_long(0x3c6ef372U),
                     change_endian_long(0xa54ff53aU),
                     change_endian_long(0x510e527fU),
                     change_endian_long(0x9b05688cU),
                     change_endian_long(0x1f83d9abU),
                     change_endian_long(0x5be0cd19U));

            WR1_PROG(REG_74H, 0x00000002U);

            HW_SCE_p_func001();

            return FSP_SUCCESS;
        }
    }
}
