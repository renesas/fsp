/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           uint32_t OutData_MAC[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p95f_func100_001[] =
    {
        0xea930652U, 0xe5416dadU, 0xa11f4404U, 0xb9a96648U,
    };
    HW_SCE_p_func100(Param_p95f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p95f_func102_001[] =
        {
            0x9ae58a76U, 0x65cd4da8U, 0xacf9799aU, 0xb7b42675U,
        };
        HW_SCE_p_func102(Param_p95f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00003409U);

        WR1_PROG(REG_ECH, 0x00008c00U);
        HW_SCE_p_func_sub007(0x0000000fU, 0x38008800U, 0x00000000U, 0x00A60000U);

        static const uint32_t Param_p95f_func100_002[] =
        {
            0xd6649063U, 0x5beb8766U, 0x0c44eb72U, 0x12ef34f7U,
        };
        HW_SCE_p_func100(Param_p95f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00e007b5U);
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

            static const uint32_t Param_p95f_func100_003[] =
            {
                0x9733ab36U, 0x7db43a40U, 0x519e1501U, 0xaddd2904U,
            };
            HW_SCE_p_func100(Param_p95f_func100_003);
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

            static const uint32_t Param_p95f_func101_001[] =
            {
                0x4054feeeU, 0x08703900U, 0x1eb616e8U, 0x46fa2c42U,
            };
            HW_SCE_p_func101(Param_p95f_func101_001);
        }
        else
        {
            static const uint32_t Param_p95f_func101_002[] =
            {
                0xa82e1ac7U, 0x166feccaU, 0xf7999152U, 0xf360fb8eU,
            };
            HW_SCE_p_func101(Param_p95f_func101_002);
        }

        HW_SCE_p_func_sub021(0x01000c84U);

        static const uint32_t Param_p95f_func100_004[] =
        {
            0x5b999e00U, 0x4650e61cU, 0xfe35bad5U, 0xc8441257U,
        };
        HW_SCE_p_func100(Param_p95f_func100_004);
        HW_SCE_p_func_sub019(0x000009c5U, 0x00001113U);

        WR1_PROG(REG_04H, 0x00000113U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_MAC[0]);

        static const uint32_t Param_p95f_func102_002[] =
        {
            0xb8cd90ffU, 0xfcd5b6bbU, 0x7ab586e5U, 0xb84ac295U,
        };
        HW_SCE_p_func102(Param_p95f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
