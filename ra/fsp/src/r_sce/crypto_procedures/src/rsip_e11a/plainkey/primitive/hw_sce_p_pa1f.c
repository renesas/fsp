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
    WR1_PROG(REG_40H, 0x00A60000U);

    HW_SCE_p_func100(0x7c62215eU, 0xf351b6c4U, 0x3e61ca8cU, 0x9d55de24U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

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

        HW_SCE_p_func100(0xec2935e9U, 0xe5a3fc2aU, 0x701e1a92U, 0x3740ef95U);
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

        HW_SCE_p_func101(0x37a950b0U, 0x07e83e24U, 0x9c9cf2ffU, 0xf2200c79U);
    }
    else
    {
        HW_SCE_p_func101(0x96070e01U, 0x44a3f45cU, 0x6f109413U, 0xf7cb3a56U);
    }

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    HW_SCE_p_func100(0xbada4c33U, 0x75c13c57U, 0x0db53ad4U, 0x718dcfe3U);
    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_MAC[0]);

    HW_SCE_p_func102(0xef7493ceU, 0x96643e45U, 0x530957f5U, 0xf6566567U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
