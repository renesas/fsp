/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha256HmacFinalSub (uint32_t InData_Cmd[],
                                     uint32_t InData_MAC[],
                                     uint32_t InData_length[],
                                     uint32_t OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_74H, 0x00000000U);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_00H, 0x00003523U);
    WR1_PROG(REG_74H, 0x00000008U);
    WR1_PROG(REG_2CH, 0x00000010U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

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

    HW_SCE_p_func002();

    HW_SCE_p_func_sub011(0x00005323U, 0x00000020U);

    WR1_PROG(REG_104H, 0x00000054U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x80000000U));

    WR1_PROG(REG_F8H, 0x00000040U);

    WR1_PROG(REG_104H, 0x00000154U);
    WAIT_STS(REG_104H, 31, 1);
    WR2_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000300U));

    WAIT_STS(REG_74H, 18, 0);
    WR1_PROG(REG_74H, 0x00000000U);
    WR1_PROG(REG_1CH, 0x00001600U);

    WR1_PROG(REG_E0H, 0x80010000U);
    WR1_PROG(REG_104H, 0x00000068U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_Cmd[0]);

    WR1_PROG(REG_ECH, 0x38000c00U);
    WR1_PROG(REG_ECH, 0x1000b780U);
    WR1_PROG(REG_ECH, 0x00002000U);
    HW_SCE_p_func_sub007(0x2000b780U, 0x00001000U, 0x38000f9bU, 0x00260000U);

    static const uint32_t Param_p76f_func100_001[] =
    {
        0x5645d712U, 0xf440c1a2U, 0x355c8516U, 0x48ad4f74U,
    };
    HW_SCE_p_func100(Param_p76f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p76f_func102_001[] =
        {
            0x9f0753abU, 0x672d8e04U, 0x33faac82U, 0xa4233a9eU,
        };
        HW_SCE_p_func102(Param_p76f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_p76f_func100_002[] =
        {
            0x63745b29U, 0xaebe8cc7U, 0x7085ee73U, 0x8e5d85a1U,
        };
        HW_SCE_p_func100(Param_p76f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p76f_func100_003[] =
            {
                0x5b5be3a7U, 0x336987a4U, 0x9aa80c8cU, 0x48f5e12aU,
            };
            HW_SCE_p_func100(Param_p76f_func100_003);
            WR1_PROG(REG_74H, 0x00000008U);
            WR1_PROG(REG_04H, 0x00000523U);
            WAIT_STS(REG_04H, 30, 1);
            RD8_ADDR(REG_100H, &OutData_MAC[0]);

            static const uint32_t Param_p76f_func102_002[] =
            {
                0xf3b0da21U, 0xaa2c1883U, 0x81dcbe92U, 0x1211e78fU,
            };
            HW_SCE_p_func102(Param_p76f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010020U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_length[0]);

            HW_SCE_p_func_sub014(0x3420a820U, 0x00000004U, 0x00260000U);

            HW_SCE_p_func_sub014(0x3420a820U, 0x00000021U, 0x00A60000U);

            static const uint32_t Param_p76f_func100_004[] =
            {
                0x787f2c3cU, 0x51494157U, 0x8d21dbdaU, 0xae4b1106U,
            };
            HW_SCE_p_func100(Param_p76f_func100_004);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p76f_func102_003[] =
                {
                    0x48ebd1e7U, 0x8950bad9U, 0xacd6fb88U, 0x66f4b1edU,
                };
                HW_SCE_p_func102(Param_p76f_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_ECH, 0x00000bffU);
                WR1_PROG(REG_E0H, 0x8088001fU);
                WR1_PROG(REG_00H, 0x00008523U);
                WR1_PROG(REG_74H, 0x00000008U);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800U);

                WR1_PROG(REG_ECH, 0x00000800U);
                for (iLoop = 0U; iLoop < 32U; iLoop++)
                {
                    WR1_PROG(REG_ECH, 0x3c002be1U);
                    WR1_PROG(REG_ECH, 0x12003c1fU);
                    WR1_PROG(REG_ECH, 0x00002fe0U);
                }

                WR1_PROG(REG_A4H, 0x00040805U);
                WR1_PROG(REG_ECH, 0x00000bffU);
                HW_SCE_p_func_sub010(0x8188001fU, 0x00001813U);

                HW_SCE_p_func_sub019(0x00050805U, 0x00001813U);

                WR1_PROG(REG_104H, 0x00000761U);
                WR1_PROG(REG_A4H, 0x00900c05U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_MAC[0]);

                WR1_PROG(REG_A4H, 0x00900c45U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_MAC[4]);

                static const uint32_t Param_p76f_func100_005[] =
                {
                    0xfcc31f34U, 0x1b5c3390U, 0x9e47672dU, 0x93c96d76U,
                };
                HW_SCE_p_func100(Param_p76f_func100_005);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_p76f_func102_004[] =
                    {
                        0x7db6d140U, 0xac1e40a8U, 0x55d31ba6U, 0xdf750b0bU,
                    };
                    HW_SCE_p_func102(Param_p76f_func102_004);
                    WR1_PROG(REG_1BCH, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    static const uint32_t Param_p76f_func102_005[] =
                    {
                        0x8e622b72U, 0x844d725fU, 0xd2e4a8e7U, 0x6bff87e6U,
                    };
                    HW_SCE_p_func102(Param_p76f_func102_005);
                    WR1_PROG(REG_1BCH, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
