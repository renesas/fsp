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

    HW_SCE_p_func_sub006(0x38008860U, 0x00000000U, 0x00260000U);

    HW_SCE_p_func_sub001(0x0000b4a0U, 0x00000010U, 0x342028a3U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    static const uint32_t Param_p98f_func100_001[] =
    {
        0x0fe71966U, 0xbaaf71aeU, 0x60d866d7U, 0x0d3ac19fU,
    };
    HW_SCE_p_func100(Param_p98f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p98f_func102_001[] =
        {
            0x6e67ea31U, 0xcdfff92cU, 0xe695cec1U, 0x0f74a663U,
        };
        HW_SCE_p_func102(Param_p98f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
        WR1_PROG(REG_2CH, InData_TextLen[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub001(0x00008c00U, 0x0000000fU, 0x38008800U);
        HW_SCE_p_func_sub009(0x00000000U, 0x00A60000U);

        static const uint32_t Param_p98f_func100_002[] =
        {
            0xc42aaee1U, 0xe3400395U, 0x43aee20dU, 0xa76c033aU,
        };
        HW_SCE_p_func100(Param_p98f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub008(0x000003c1U, 0x07000d05U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub002(0x03410011U);

            WR1_PROG(REG_94H, 0x00000821U);

            WR1_PROG(REG_94H, 0x000008a5U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                HW_SCE_p_func_sub001(0x3c0028a0U, 0x12003c25U, 0x00002ca0U);
            }

            static const uint32_t Param_p98f_func100_003[] =
            {
                0x398acac6U, 0xa68de941U, 0xe0e94c78U, 0x26cd197dU,
            };
            HW_SCE_p_func100(Param_p98f_func100_003);
            WR1_PROG(REG_94H, 0x00000821U);
            HW_SCE_p_func_sub012(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[0]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[2]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[3]);

            WR1_PROG(REG_D0H, 0x0e100405U);
            WR1_PROG(REG_9CH, 0x81840001U);
            HW_SCE_p_func_sub002(0x00490011U);

            static const uint32_t Param_p98f_func101_001[] =
            {
                0x0c4a1ec0U, 0xa3730b30U, 0xd0c96bccU, 0xa1019d0aU,
            };
            HW_SCE_p_func101(Param_p98f_func101_001);
        }
        else
        {
            static const uint32_t Param_p98f_func101_002[] =
            {
                0x8f224d1eU, 0xc6a15a9dU, 0x20a77796U, 0xd16932a9U,
            };
            HW_SCE_p_func101(Param_p98f_func101_002);
        }

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_D0H, 0x07200d05U);
        HW_SCE_p_func_sub002(0x00410011U);

        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80840001U);
        HW_SCE_p_func_sub002(0x03410011U);

        WR1_PROG(REG_94H, 0x000008a5U);

        WR1_PROG(REG_94H, 0x00000821U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            HW_SCE_p_func_sub001(0x3c0028a3U, 0x12003c25U, 0x00002ca0U);
        }

        HW_SCE_p_func_sub008(0x000003c1U, 0x08000055U);
        WR4_ADDR(REG_2CH, &InData_MAC[0]);

        HW_SCE_p_func_sub016(0x9c100005U, 0x00000821U, 0x81840001U);
        HW_SCE_p_func_sub002(0x00490011U);
        WR1_PROG(REG_D0H, 0x00000000U);

        static const uint32_t Param_p98f_func100_004[] =
        {
            0xc690565dU, 0x1f3991ddU, 0xeb9e51a1U, 0x3495e6a0U,
        };
        HW_SCE_p_func100(Param_p98f_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p98f_func102_002[] =
            {
                0x27e9707fU, 0x4fbea5b6U, 0xb6dd3648U, 0x6bbec710U,
            };
            HW_SCE_p_func102(Param_p98f_func102_002);

            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            static const uint32_t Param_p98f_func102_003[] =
            {
                0xfeffdd51U, 0x8ccb2e0aU, 0xeda1a01cU, 0x4f83af8fU,
            };
            HW_SCE_p_func102(Param_p98f_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
