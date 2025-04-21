/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_TextLen[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x00008c00U);
    WR1_PROG(REG_94H, 0x0000000fU);

    WR1_PROG(REG_94H, 0x38008800U);
    WR1_PROG(REG_94H, 0x00000000U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A70000U);

    HW_SCE_p_func100(0x1ebfd025U, 0xb5c2e63fU, 0x66d8ba70U, 0x7f03bab4U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xe7008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[0]);

        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80840001U);
        WR1_PROG(REG_00H, 0x03410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_94H, 0x00000821U);

        WR1_PROG(REG_94H, 0x000008a5U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_94H, 0x3c0028a0U);
            WR1_PROG(REG_94H, 0x12003c25U);
            WR1_PROG(REG_94H, 0x00002ca0U);
        }

        HW_SCE_p_func100(0x766d25caU, 0x57a1ec11U, 0x70e0c633U, 0xd2aa600eU);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x81840001U);
        WR1_PROG(REG_08H, 0x00005012U);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[0]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[1]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[2]);
        WAIT_STS(REG_08H, 30, 1);
        RD1_ADDR(REG_2CH, &OutData_Text[3]);

        HW_SCE_p_func101(0xb86e28d8U, 0x54c4f7d3U, 0xd9084a3fU, 0xe71e863dU);
    }
    else
    {
        HW_SCE_p_func101(0x9c5b8fccU, 0xda5d0be0U, 0x07e2b337U, 0x1d878b19U);
    }

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    HW_SCE_p_func100(0x8a24861bU, 0x8e8a8271U, 0x51b5030eU, 0xf803a1e6U);
    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_MAC[0]);

    HW_SCE_p_func102(0x81c2e166U, 0xa7e191d1U, 0xbce9e628U, 0x72e57675U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
