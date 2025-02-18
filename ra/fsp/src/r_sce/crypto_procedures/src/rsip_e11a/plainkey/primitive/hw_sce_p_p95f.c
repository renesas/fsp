/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_94H, 0x00003404U);

    WR1_PROG(REG_94H, 0x00008c00U);
    WR1_PROG(REG_94H, 0x0000000fU);

    WR1_PROG(REG_94H, 0x38008800U);
    WR1_PROG(REG_94H, 0x00000000U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A60000U);

    HW_SCE_p_func100(0xd4c822efU, 0x1347e539U, 0x0f841bb9U, 0xc821d816U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D0H, 0xe7000d05U);
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

        HW_SCE_p_func100(0xa09072c2U, 0x8554a08fU, 0x5dd0e166U, 0xb7349dc4U);
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

        HW_SCE_p_func101(0x7e1e1bc0U, 0x5904e1aaU, 0xf17173d8U, 0x9b16a352U);
    }
    else
    {
        HW_SCE_p_func101(0x45e9db84U, 0x37eee82fU, 0xe3ca087aU, 0xe658659bU);
    }

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    HW_SCE_p_func100(0xce06867cU, 0xf867ecd1U, 0xfb5b50a1U, 0xe56f2e6dU);
    WR1_PROG(REG_D0H, 0x09100105U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_MAC[0]);

    HW_SCE_p_func102(0xd0367f8cU, 0x09eccc5fU, 0x6d60092eU, 0xf5a1eb9cU);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
