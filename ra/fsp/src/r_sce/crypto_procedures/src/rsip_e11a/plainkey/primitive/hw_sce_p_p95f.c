/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_TextLen[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x00008c00U, 0x0000000fU, 0x38008800U);
    HW_SCE_p_func_sub009(0x00000000U, 0x00A60000U);

    static const uint32_t Param_p95f_func100_001[] =
    {
        0xc8180b61U, 0xc5543425U, 0x3d29f672U, 0x1f47509dU,
    };
    HW_SCE_p_func100(Param_p95f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub008(0x000003c1U, 0xe7000d05U);
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

        static const uint32_t Param_p95f_func100_002[] =
        {
            0x379f6099U, 0x8fe0aef6U, 0xf6e482f2U, 0x8bfc260eU,
        };
        HW_SCE_p_func100(Param_p95f_func100_002);
        WR1_PROG(REG_94H, 0x00000821U);
        HW_SCE_p_func_sub012(0x81840001U, 0x00005012U);
        RD1_ADDR(REG_2CH, &OutData_Text[0]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[1]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[2]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[3]);

        static const uint32_t Param_p95f_func101_001[] =
        {
            0x56b2247aU, 0x6c4a97d4U, 0xb06986b8U, 0xfd08b80aU,
        };
        HW_SCE_p_func101(Param_p95f_func101_001);
    }
    else
    {
        static const uint32_t Param_p95f_func101_002[] =
        {
            0xf334f31dU, 0x7fd9a4a2U, 0xb6bad84bU, 0x01e636bcU,
        };
        HW_SCE_p_func101(Param_p95f_func101_002);
    }

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    static const uint32_t Param_p95f_func100_003[] =
    {
        0x2cb4ad8dU, 0x2809071bU, 0xd5180aecU, 0xd3a4e3b0U,
    };
    HW_SCE_p_func100(Param_p95f_func100_003);
    WR1_PROG(REG_D0H, 0x09100105U);
    HW_SCE_p_func_sub002(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_MAC[0]);

    static const uint32_t Param_p95f_func102_001[] =
    {
        0x091e9f00U, 0x4e7e97ccU, 0x8424276bU, 0xa154d7a2U,
    };
    HW_SCE_p_func102(Param_p95f_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
