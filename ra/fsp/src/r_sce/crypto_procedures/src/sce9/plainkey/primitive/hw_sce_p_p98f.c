/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_MAC[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p98f_func100_001[] =
    {
        0x756b282cU, 0x61eb6ac1U, 0x0547ad54U, 0x815d9795U,
    };
    HW_SCE_p_func100(Param_p98f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p98f_func102_001[] =
        {
            0x4d7e857eU, 0x5942cc85U, 0x11512bd8U, 0x9082677fU,
        };
        HW_SCE_p_func102(Param_p98f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub014(0x38008940U, 0x00000000U, 0x00260000U);

        HW_SCE_p_func_sub007(0x0000b7e0U, 0x00000010U, 0x34202beaU, 0x00260000U);

        static const uint32_t Param_p98f_func100_002[] =
        {
            0x2068ea33U, 0x35fe694fU, 0x1fffea4fU, 0xb17cb918U,
        };
        HW_SCE_p_func100(Param_p98f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p98f_func102_002[] =
            {
                0xf3e4e3d7U, 0x7db5da18U, 0xc8e7a740U, 0x69d1ed6cU,
            };
            HW_SCE_p_func102(Param_p98f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_ECH, 0x00003409U);

            WR1_PROG(REG_ECH, 0x00008c00U);
            HW_SCE_p_func_sub007(0x0000000fU, 0x38008800U, 0x00000000U, 0x00A60000U);

            static const uint32_t Param_p98f_func100_003[] =
            {
                0x73584992U, 0xc573a5d6U, 0x6ea546bbU, 0xcfe69407U,
            };
            HW_SCE_p_func100(Param_p98f_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x000007b5U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_Text[0]);

                WR1_PROG(REG_ECH, 0x0000b420U);
                WR1_PROG(REG_ECH, 0x00000080U);
                HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

                HW_SCE_p_func_sub022(0x00000821U, 0x0000a400U, 0x00000080U, 0x0000b7e0U);
                WR1_PROG(REG_ECH, 0x00000080U);

                for (iLoop = 0U; iLoop < 16U; iLoop++)
                {
                    WR1_PROG(REG_ECH, 0x3c002be0U);
                    WR1_PROG(REG_ECH, 0x12003c3fU);
                    WR1_PROG(REG_ECH, 0x00002fe0U);
                }

                static const uint32_t Param_p98f_func100_004[] =
                {
                    0xbc0c311eU, 0xea2c3892U, 0x0a8e613aU, 0x74bd2866U,
                };
                HW_SCE_p_func100(Param_p98f_func100_004);
                WR1_PROG(REG_ECH, 0x0000b420U);
                WR1_PROG(REG_ECH, 0x00000080U);
                WR1_PROG(REG_E0H, 0x81840001U);
                WR1_PROG(REG_04H, 0x00000613U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[0]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[1]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[2]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[3]);

                WR1_PROG(REG_A4H, 0x00000e55U);
                HW_SCE_p_func_sub010(0x81840001U, 0x00001813U);

                static const uint32_t Param_p98f_func101_001[] =
                {
                    0x31cd2a46U, 0x4dee405dU, 0x5cf87637U, 0x7a6f8ce2U,
                };
                HW_SCE_p_func101(Param_p98f_func101_001);
            }
            else
            {
                static const uint32_t Param_p98f_func101_002[] =
                {
                    0x22cf8d83U, 0x541651fcU, 0xac958888U, 0x82de838cU,
                };
                HW_SCE_p_func101(Param_p98f_func101_002);
            }

            HW_SCE_p_func_sub021(0x00000cc4U);

            HW_SCE_p_func_sub019(0x010007b5U, 0x00001113U);

            WR1_PROG(REG_ECH, 0x0000b420U);
            WR1_PROG(REG_ECH, 0x00000080U);
            HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

            HW_SCE_p_func_sub022(0x0000a540U, 0x00000080U, 0x0000b7e0U, 0x00000080U);

            WR1_PROG(REG_ECH, 0x00000821U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x3c002beaU);
                WR1_PROG(REG_ECH, 0x12003c3fU);
                WR1_PROG(REG_ECH, 0x00002fe0U);
            }

            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00050805U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_MAC[0]);

            WR1_PROG(REG_A4H, 0x00900c45U);
            WR1_PROG(REG_ECH, 0x0000b420U);
            WR1_PROG(REG_ECH, 0x00000080U);
            HW_SCE_p_func_sub010(0x81840001U, 0x00001813U);
            WR1_PROG(REG_A4H, 0x00000000U);

            static const uint32_t Param_p98f_func100_005[] =
            {
                0x2ea4caa9U, 0xfbd261e2U, 0xcb769774U, 0x0dc25313U,
            };
            HW_SCE_p_func100(Param_p98f_func100_005);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p98f_func102_003[] =
                {
                    0x66790dccU, 0xe55eefe5U, 0xb927a6bdU, 0xc192c729U,
                };
                HW_SCE_p_func102(Param_p98f_func102_003);

                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p98f_func102_004[] =
                {
                    0xf1b693deU, 0x4e469de9U, 0x7d25b62aU, 0xfd63f049U,
                };
                HW_SCE_p_func102(Param_p98f_func102_004);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
