/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub (const uint32_t InData_Text[],
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

    static const uint32_t Param_pa4f_func100_001[] =
    {
        0xcd3cc801U, 0x256f2dcdU, 0xece27a95U, 0x5c50fdeeU,
    };
    HW_SCE_p_func100(Param_pa4f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pa4f_func102_001[] =
        {
            0x44e4ae9aU, 0x1de613ebU, 0x58d1dfc2U, 0x594800d9U,
        };
        HW_SCE_p_func102(Param_pa4f_func102_001);
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

        static const uint32_t Param_pa4f_func100_002[] =
        {
            0x87db616bU, 0x0fee6673U, 0x090b899aU, 0xb2291b7dU,
        };
        HW_SCE_p_func100(Param_pa4f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
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

            static const uint32_t Param_pa4f_func100_003[] =
            {
                0x991fe4bdU, 0xb41d3f23U, 0x00c44bb2U, 0x90e3c9b8U,
            };
            HW_SCE_p_func100(Param_pa4f_func100_003);
            WR1_PROG(REG_94H, 0x00000821U);
            HW_SCE_p_func_sub009(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            HW_SCE_p_func_sub021(0x40000000U, 0x0e108405U, 0x81840001U);
            HW_SCE_p_func_sub003(0x00490011U);

            static const uint32_t Param_pa4f_func101_001[] =
            {
                0xbd2bd911U, 0x2ddf22e3U, 0xe50d7dd4U, 0xdb0c6f4dU,
            };
            HW_SCE_p_func101(Param_pa4f_func101_001);
        }
        else
        {
            static const uint32_t Param_pa4f_func101_002[] =
            {
                0x72af2ee9U, 0xd8141849U, 0x5144e6b0U, 0x53bbeb29U,
            };
            HW_SCE_p_func101(Param_pa4f_func101_002);
        }

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07208d05U);
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

        static const uint32_t Param_pa4f_func100_004[] =
        {
            0x505fd58dU, 0x37a55cdaU, 0xeb82dc33U, 0xbc14d2d9U,
        };
        HW_SCE_p_func100(Param_pa4f_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pa4f_func102_002[] =
            {
                0xaeec86e6U, 0x35735202U, 0xd150bf96U, 0x3a07ce1cU,
            };
            HW_SCE_p_func102(Param_pa4f_func102_002);

            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            static const uint32_t Param_pa4f_func102_003[] =
            {
                0x5ab00f1eU, 0x83ffd697U, 0xcde8f013U, 0x05354104U,
            };
            HW_SCE_p_func102(Param_pa4f_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
