/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x4a008104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x9adc4ee1U, 0xd34285c4U, 0x5c36c779U, 0x816cde3dU);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x5a008104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x040f40ecU, 0x1d1edee8U, 0xdfad218fU, 0xaf9adfd3U);
    }

    WR1_PROG(REG_D0H, 0x0c000045U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        HW_SCE_p_func100(0x4a9e4cd3U, 0x69a97668U, 0x02d2f379U, 0xed75d9fbU);
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0e008505U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[0]);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0xe3cb80a7U, 0xd90244b7U, 0x3838a5caU, 0xb621d409U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010040U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_DataTLen[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x3420a840U);
        WR1_PROG(REG_94H, 0x00000010U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00260000U);

        WR1_PROG(REG_94H, 0x0000b460U);
        WR1_PROG(REG_94H, 0x00000080U);
        WR1_PROG(REG_94H, 0x34202862U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00260000U);

        HW_SCE_p_func100(0x5d8ddad8U, 0xfeac97e2U, 0x5c5106c5U, 0x6e8a115aU);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x45d89000U, 0xf237aca2U, 0xea6dcc5aU, 0x8d49b799U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x0e008505U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            WR1_PROG(REG_00H, 0x03410011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x000034e2U);
            WR1_PROG(REG_94H, 0x000568e7U);
            WR1_PROG(REG_94H, 0x00026ce7U);

            WR1_PROG(REG_94H, 0x00003827U);

            WR1_PROG(REG_94H, 0x0000b4c0U);
            WR1_PROG(REG_94H, 0x00000020U);
            WR1_PROG(REG_94H, 0x00003402U);
            WR1_PROG(REG_94H, 0x00008c00U);
            WR1_PROG(REG_94H, 0x0000001fU);
            WR1_PROG(REG_94H, 0x000028c0U);
            WR1_PROG(REG_94H, 0x00008cc0U);
            WR1_PROG(REG_94H, 0x0000001fU);

            WR1_PROG(REG_94H, 0x00004406U);

            WR1_PROG(REG_94H, 0x00007421U);
            WR1_PROG(REG_94H, 0x00007821U);

            WR1_PROG(REG_94H, 0x00003c27U);

            WR1_PROG(REG_94H, 0x000034c2U);
            WR1_PROG(REG_94H, 0x0000a4c0U);
            WR1_PROG(REG_94H, 0x0000001fU);
            WR1_PROG(REG_94H, 0x000568c6U);

            WR1_PROG(REG_94H, 0x000034e6U);
            WR1_PROG(REG_94H, 0x00026ce7U);

            WR1_PROG(REG_94H, 0x00000821U);

            for (iLoop = 0U; iLoop < 4; iLoop++)
            {
                WR1_PROG(REG_94H, 0x3420a8e0U);
                WR1_PROG(REG_94H, 0x0000000dU);
                WR1_PROG(REG_94H, 0x10003c27U);

                WR1_PROG(REG_94H, 0x1000a4e0U);
                WR1_PROG(REG_94H, 0x00000004U);
            }

            WR1_PROG(REG_D0H, 0x08000045U);
            WR1_PROG(REG_9CH, 0x81840001U);
            WR1_PROG(REG_00H, 0x00490011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x9c000005U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_DataT[0]);

            HW_SCE_p_func100(0x6f44e894U, 0xb8203890U, 0xdb2a0872U, 0x2559144bU);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0xa7213795U, 0xda3cd31dU, 0x7b33e749U, 0xf0a7c1d4U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                HW_SCE_p_func102(0x25e9015fU, 0x7503bc1fU, 0x0127f36eU, 0xc864e16eU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
