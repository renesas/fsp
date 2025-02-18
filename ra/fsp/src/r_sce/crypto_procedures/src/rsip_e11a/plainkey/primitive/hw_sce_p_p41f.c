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

        HW_SCE_p_func101(0xcec6f407U, 0x6406d6afU, 0x0c46fdfeU, 0x0a4d5e7bU);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x5a000104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x9f5bf136U, 0x0c9795c2U, 0xae6d07c1U, 0x301accd7U);
    }

    WR1_PROG(REG_D0H, 0x0c000045U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        HW_SCE_p_func100(0x42255d08U, 0x2f11d49cU, 0xdb6e0971U, 0x543a2125U);
        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D0H, 0x0e000505U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[0]);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0x26d8d3a1U, 0x67e65b35U, 0x33788fbaU, 0x6a0f87ecU);
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

        HW_SCE_p_func100(0x4a3ce344U, 0x1a6adf4aU, 0xd275e56fU, 0xd4954365U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x11dd52c3U, 0x27475673U, 0x2cd5a7bbU, 0x61a3c5b6U);
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

            HW_SCE_p_func100(0x8eec0eb1U, 0x98882d64U, 0xcc918c5bU, 0xae6a48d8U);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0xbfbe79dcU, 0xa5d3fd66U, 0xd0d22fbcU, 0xc3e8352eU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                HW_SCE_p_func102(0x17373c74U, 0xe06073f8U, 0xe2ebd3a3U, 0xc783b44bU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
