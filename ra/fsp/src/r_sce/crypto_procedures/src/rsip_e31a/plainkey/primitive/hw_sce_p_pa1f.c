/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub (const uint32_t InData_Text[],
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

    static const uint32_t Param_pa1f_func100_001[] =
    {
        0x1ebfd025U, 0xb5c2e63fU, 0x66d8ba70U, 0x7f03bab4U,
    };
    HW_SCE_p_func100(Param_pa1f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0xe7008d05U);
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

        static const uint32_t Param_pa1f_func100_002[] =
        {
            0x766d25caU, 0x57a1ec11U, 0x70e0c633U, 0xd2aa600eU,
        };
        HW_SCE_p_func100(Param_pa1f_func100_002);
        WR1_PROG(REG_94H, 0x00000821U);
        HW_SCE_p_func_sub009(0x81840001U, 0x00005012U);
        RD1_ADDR(REG_2CH, &OutData_Text[0]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[1]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[2]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[3]);

        static const uint32_t Param_pa1f_func101_001[] =
        {
            0xb86e28d8U, 0x54c4f7d3U, 0xd9084a3fU, 0xe71e863dU,
        };
        HW_SCE_p_func101(Param_pa1f_func101_001);
    }
    else
    {
        static const uint32_t Param_pa1f_func101_002[] =
        {
            0x9c5b8fccU, 0xda5d0be0U, 0x07e2b337U, 0x1d878b19U,
        };
        HW_SCE_p_func101(Param_pa1f_func101_002);
    }

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

    static const uint32_t Param_pa1f_func100_003[] =
    {
        0x8a24861bU, 0x8e8a8271U, 0x51b5030eU, 0xf803a1e6U,
    };
    HW_SCE_p_func100(Param_pa1f_func100_003);
    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    HW_SCE_p_func_sub003(0x00410011U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_MAC[0]);

    static const uint32_t Param_pa1f_func102_001[] =
    {
        0x81c2e166U, 0xa7e191d1U, 0xbce9e628U, 0x72e57675U,
    };
    HW_SCE_p_func102(Param_pa1f_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
