/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010060U);
    WR1_PROG(REG_2CH, InData_MACLength[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub006(0x38008860U, 0x00000000U, 0x00270000U);

    WR1_PROG(REG_94H, 0x0000b4a0U);
    HW_SCE_p_func_sub006(0x00000010U, 0x342028a3U, 0x00270000U);

    static const uint32_t Param_p99f_func100_001[] =
    {
        0x8d16e576U, 0x31b3716eU, 0xf2146aafU, 0x1132934eU,
    };
    HW_SCE_p_func100(Param_p99f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p99f_func102_001[] =
        {
            0xaea4a8e6U, 0x4337572aU, 0x42b411c2U, 0x80d9af4aU,
        };
        HW_SCE_p_func102(Param_p99f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
        WR1_PROG(REG_2CH, InData_TextLen[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub001(0x00008c00U, 0x0000000fU, 0x38008800U, 0x00000000U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A70000U);

        static const uint32_t Param_p99f_func100_002[] =
        {
            0x1c32cf46U, 0x140d6e1cU, 0x0beae4ccU, 0x4b403d1dU,
        };
        HW_SCE_p_func100(Param_p99f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub011(0x000003c1U, 0x07000d05U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub003(0x03410011U);

            WR1_PROG(REG_94H, 0x00000821U);

            WR1_PROG(REG_94H, 0x000008a5U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                HW_SCE_p_func_sub022(0x3c0028a0U, 0x12003c25U, 0x00002ca0U);
            }

            static const uint32_t Param_p99f_func100_003[] =
            {
                0x1958dfb4U, 0x336b34a8U, 0x5b5491f6U, 0x5790611bU,
            };
            HW_SCE_p_func100(Param_p99f_func100_003);
            WR1_PROG(REG_94H, 0x00000821U);
            HW_SCE_p_func_sub009(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            WR1_PROG(REG_D0H, 0x0e100405U);
            WR1_PROG(REG_9CH, 0x81840001U);
            HW_SCE_p_func_sub003(0x00490011U);

            static const uint32_t Param_p99f_func101_001[] =
            {
                0x9f291820U, 0x23ab5157U, 0x69f71f72U, 0x8990ca88U,
            };
            HW_SCE_p_func101(Param_p99f_func101_001);
        }
        else
        {
            static const uint32_t Param_p99f_func101_002[] =
            {
                0x14f0d090U, 0x36929c6bU, 0x4ea95522U, 0x8199ac05U,
            };
            HW_SCE_p_func101(Param_p99f_func101_002);
        }

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_D0H, 0x07200d05U);
        HW_SCE_p_func_sub003(0x00410011U);

        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80840001U);
        HW_SCE_p_func_sub003(0x03410011U);

        WR1_PROG(REG_94H, 0x000008a5U);

        WR1_PROG(REG_94H, 0x00000821U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            HW_SCE_p_func_sub022(0x3c0028a3U, 0x12003c25U, 0x00002ca0U);
        }

        HW_SCE_p_func_sub011(0x000003c1U, 0x08000055U);
        WR4_ADDR(REG_2CH, &InData_MAC[0]);

        HW_SCE_p_func_sub013(0x9c100005U, 0x00000821U, 0x81840001U);
        HW_SCE_p_func_sub003(0x00490011U);
        WR1_PROG(REG_D0H, 0x00000000U);

        static const uint32_t Param_p99f_func100_004[] =
        {
            0x402d2f3dU, 0xa8bd060fU, 0xe7d5408eU, 0xc9ec5261U,
        };
        HW_SCE_p_func100(Param_p99f_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p99f_func102_002[] =
            {
                0x77b16d76U, 0x39d73e8dU, 0x8125cdd4U, 0x5133db3dU,
            };
            HW_SCE_p_func102(Param_p99f_func102_002);

            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            static const uint32_t Param_p99f_func102_003[] =
            {
                0x63b4d94eU, 0x0552cfddU, 0xce47153eU, 0xc0e1d62fU,
            };
            HW_SCE_p_func102(Param_p99f_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
