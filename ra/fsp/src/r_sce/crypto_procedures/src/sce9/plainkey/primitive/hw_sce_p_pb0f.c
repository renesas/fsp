/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes192CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_pb0f_func100_001[] =
    {
        0x26af63b6U, 0x2380b8a2U, 0x3ffdd73aU, 0xaf08b6b2U,
    };
    HW_SCE_p_func100(Param_pb0f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb0f_func102_001[] =
        {
            0xad4a5577U, 0x08513a85U, 0x388e49aaU, 0xfb01c2bcU,
        };
        HW_SCE_p_func102(Param_pb0f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_104H, 0x00000068U);
        WR1_PROG(REG_E0H, 0x80010140U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_MACLength[0]);

        HW_SCE_p_func_sub014(0x38008940U, 0x00000000U, 0x00260000U);

        HW_SCE_p_func_sub007(0x0000b7e0U, 0x00000010U, 0x34202beaU, 0x00260000U);

        static const uint32_t Param_pb0f_func100_002[] =
        {
            0xd349ede2U, 0x7d4e9a7dU, 0x50e8a223U, 0xd5a45cc8U,
        };
        HW_SCE_p_func100(Param_pb0f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pb0f_func102_002[] =
            {
                0x87a74f51U, 0x93aa34a0U, 0xf2c0e489U, 0xa4242a17U,
            };
            HW_SCE_p_func102(Param_pb0f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010000U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_TextLen[0]);

            WR1_PROG(REG_ECH, 0x00008c00U);
            HW_SCE_p_func_sub007(0x0000000fU, 0x38008800U, 0x00000000U, 0x00A60000U);

            static const uint32_t Param_pb0f_func100_003[] =
            {
                0x908dafbcU, 0x7a190575U, 0x2722df91U, 0x458e37a2U,
            };
            HW_SCE_p_func100(Param_pb0f_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_B0H, 0x40000010U);
                WR1_PROG(REG_A4H, 0x000087b5U);
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

                static const uint32_t Param_pb0f_func100_004[] =
                {
                    0x0e939bd4U, 0x998bc030U, 0x6fa068efU, 0x9c49870eU,
                };
                HW_SCE_p_func100(Param_pb0f_func100_004);
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

                WR1_PROG(REG_B0H, 0x40000010U);
                WR1_PROG(REG_A4H, 0x00008e55U);
                HW_SCE_p_func_sub010(0x81840001U, 0x00001813U);

                static const uint32_t Param_pb0f_func101_001[] =
                {
                    0x534d33e4U, 0xd1bebc7dU, 0xc0d24399U, 0x4fa6ba70U,
                };
                HW_SCE_p_func101(Param_pb0f_func101_001);
            }
            else
            {
                static const uint32_t Param_pb0f_func101_002[] =
                {
                    0x60cb1579U, 0xdfb576c0U, 0xbf5276b8U, 0xcfeb2d6eU,
                };
                HW_SCE_p_func101(Param_pb0f_func101_002);
            }

            HW_SCE_p_func_sub021(0x00000cc4U);

            WR1_PROG(REG_B0H, 0x40000010U);
            HW_SCE_p_func_sub019(0x010087b5U, 0x00001113U);

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

            static const uint32_t Param_pb0f_func100_005[] =
            {
                0x6c425cecU, 0x192adbe0U, 0xc5a9f23fU, 0x9ca8d5bfU,
            };
            HW_SCE_p_func100(Param_pb0f_func100_005);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pb0f_func102_003[] =
                {
                    0x5cd83331U, 0xf341d027U, 0xa9a7f36dU, 0x80224432U,
                };
                HW_SCE_p_func102(Param_pb0f_func102_003);

                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_pb0f_func102_004[] =
                {
                    0x2147e2dbU, 0xd5bad0c8U, 0xc4e93291U, 0x1ce9be56U,
                };
                HW_SCE_p_func102(Param_pb0f_func102_004);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
