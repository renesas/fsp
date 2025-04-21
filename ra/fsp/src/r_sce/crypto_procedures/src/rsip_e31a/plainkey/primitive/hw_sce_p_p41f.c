/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x4a000104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0xb9f5253dU, 0x044ec373U, 0x1c166a40U, 0x9c9e608cU);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x5a000104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0xdaeef5f4U, 0x10b52bf0U, 0x92e41f6cU, 0xcf311c10U);
    }

    WR1_PROG(REG_D0H, 0x0c000045U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        HW_SCE_p_func100(0xdd791e26U, 0x93c3eac4U, 0xa88feb51U, 0x0aed88daU);
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D0H, 0x0e000505U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[0]);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0x8526804fU, 0x5dca76d0U, 0x1a756727U, 0xe654482fU);
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
        WR1_PROG(REG_40H, 0x00270000U);

        WR1_PROG(REG_94H, 0x0000b460U);
        WR1_PROG(REG_94H, 0x00000080U);
        WR1_PROG(REG_94H, 0x34202862U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        HW_SCE_p_func100(0x530579a9U, 0x0f5004e7U, 0x6e5ef8ecU, 0x36aa8482U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x686b537eU, 0xdc94dd79U, 0x98487726U, 0x9f36a85dU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x0e000505U);
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

            HW_SCE_p_func100(0x8ff567a6U, 0xc3b043e0U, 0x7fc41c72U, 0x58fc265fU);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x09d95487U, 0xdb40dc79U, 0x04d9ed6fU, 0x645830cdU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                HW_SCE_p_func102(0x96d1c2b1U, 0xbe6a3934U, 0xa5836c73U, 0x3644a5afU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
