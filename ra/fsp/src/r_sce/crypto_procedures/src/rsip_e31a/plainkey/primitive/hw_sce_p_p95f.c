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

    HW_SCE_p_func_sub001(0x00008c00U, 0x0000000fU, 0x38008800U, 0x00000000U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A70000U);

    static const uint32_t Param_p95f_func100_001[] =
    {
        0x9f9d0877U, 0x8471635dU, 0x9ff7209fU, 0x110bf32aU,
    };
    HW_SCE_p_func100(Param_p95f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub011(0x000003c1U, 0xe7000d05U);
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

        static const uint32_t Param_p95f_func100_002[] =
        {
            0xe9241471U, 0x89865570U, 0xfda37e73U, 0x9bf637b1U,
        };
        HW_SCE_p_func100(Param_p95f_func100_002);
        WR1_PROG(REG_94H, 0x00000821U);
        HW_SCE_p_func_sub009(0x81840001U, 0x00005012U);
        RD1_ADDR(REG_2CH, &OutData_Text[0]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[1]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[2]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[3]);

        static const uint32_t Param_p95f_func101_001[] =
        {
            0x5dc78578U, 0x6606f6a2U, 0x033e533fU, 0xfc95f7b7U,
        };
        HW_SCE_p_func101(Param_p95f_func101_001);
    }
    else
    {
        static const uint32_t Param_p95f_func101_002[] =
        {
            0xd8e4d07dU, 0xc30c20aeU, 0x2de3d5e1U, 0xaf09dd0bU,
        };
        HW_SCE_p_func101(Param_p95f_func101_002);
    }

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    static const uint32_t Param_p95f_func100_003[] =
    {
        0x9c293948U, 0x7298bcf7U, 0x9d711568U, 0xbf5593ceU,
    };
    HW_SCE_p_func100(Param_p95f_func100_003);
    WR1_PROG(REG_D0H, 0x09100105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_MAC[0]);

    static const uint32_t Param_p95f_func102_001[] =
    {
        0x1d3cea70U, 0x79e4420dU, 0x16b5c1d4U, 0x434e4931U,
    };
    HW_SCE_p_func102(Param_p95f_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
