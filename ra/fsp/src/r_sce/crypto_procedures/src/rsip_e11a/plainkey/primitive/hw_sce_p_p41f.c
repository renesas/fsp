/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        HW_SCE_p_func_sub004(0x000000a1U, 0x4a000104U, 0x00000000U);

        static const uint32_t Param_p41f_func101_001[] =
        {
            0xcec6f407U, 0x6406d6afU, 0x0c46fdfeU, 0x0a4d5e7bU,
        };
        HW_SCE_p_func101(Param_p41f_func101_001);
    }
    else
    {
        HW_SCE_p_func_sub004(0x000000a1U, 0x5a000104U, 0x00000000U);

        static const uint32_t Param_p41f_func101_002[] =
        {
            0x9f5bf136U, 0x0c9795c2U, 0xae6d07c1U, 0x301accd7U,
        };
        HW_SCE_p_func101(Param_p41f_func101_002);
    }

    WR1_PROG(REG_D0H, 0x0c000045U);
    HW_SCE_p_func_sub002(0x00410011U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        static const uint32_t Param_p41f_func100_001[] =
        {
            0x42255d08U, 0x2f11d49cU, 0xdb6e0971U, 0x543a2125U,
        };
        HW_SCE_p_func100(Param_p41f_func100_001);
        HW_SCE_p_func_sub008(0x000003c1U, 0x0e000505U);
        WR4_ADDR(REG_2CH, &InData_Text[0]);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        static const uint32_t Param_p41f_func102_001[] =
        {
            0x26d8d3a1U, 0x67e65b35U, 0x33788fbaU, 0x6a0f87ecU,
        };
        HW_SCE_p_func102(Param_p41f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x80010040U);
        WR1_PROG(REG_2CH, InData_DataTLen[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub006(0x3420a840U, 0x00000010U, 0x00260000U);

        HW_SCE_p_func_sub001(0x0000b460U, 0x00000080U, 0x34202862U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00260000U);

        static const uint32_t Param_p41f_func100_002[] =
        {
            0x4a3ce344U, 0x1a6adf4aU, 0xd275e56fU, 0xd4954365U,
        };
        HW_SCE_p_func100(Param_p41f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p41f_func102_002[] =
            {
                0x11dd52c3U, 0x27475673U, 0x2cd5a7bbU, 0x61a3c5b6U,
            };
            HW_SCE_p_func102(Param_p41f_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub008(0x000003c1U, 0x0e000505U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub002(0x03410011U);

            HW_SCE_p_func_sub001(0x000034e2U, 0x000568e7U, 0x00026ce7U);

            HW_SCE_p_func_sub001(0x00003827U, 0x0000b4c0U, 0x00000020U);
            HW_SCE_p_func_sub001(0x00003402U, 0x00008c00U, 0x0000001fU);
            HW_SCE_p_func_sub001(0x000028c0U, 0x00008cc0U, 0x0000001fU);

            HW_SCE_p_func_sub001(0x00004406U, 0x00007421U, 0x00007821U);

            HW_SCE_p_func_sub001(0x00003c27U, 0x000034c2U, 0x0000a4c0U);
            HW_SCE_p_func_sub001(0x0000001fU, 0x000568c6U, 0x000034e6U);
            WR1_PROG(REG_94H, 0x00026ce7U);

            WR1_PROG(REG_94H, 0x00000821U);

            for (iLoop = 0U; iLoop < 4; iLoop++)
            {
                HW_SCE_p_func_sub001(0x3420a8e0U, 0x0000000dU, 0x10003c27U);

                WR1_PROG(REG_94H, 0x1000a4e0U);
                WR1_PROG(REG_94H, 0x00000004U);
            }

            WR1_PROG(REG_D0H, 0x08000045U);
            WR1_PROG(REG_9CH, 0x81840001U);
            HW_SCE_p_func_sub002(0x00490011U);

            HW_SCE_p_func_sub008(0x000003c1U, 0x9c000005U);
            WR4_ADDR(REG_2CH, &InData_DataT[0]);

            static const uint32_t Param_p41f_func100_003[] =
            {
                0x8eec0eb1U, 0x98882d64U, 0xcc918c5bU, 0xae6a48d8U,
            };
            HW_SCE_p_func100(Param_p41f_func100_003);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p41f_func102_003[] =
                {
                    0xbfbe79dcU, 0xa5d3fd66U, 0xd0d22fbcU, 0xc3e8352eU,
                };
                HW_SCE_p_func102(Param_p41f_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                static const uint32_t Param_p41f_func102_004[] =
                {
                    0x17373c74U, 0xe06073f8U, 0xe2ebd3a3U, 0xc783b44bU,
                };
                HW_SCE_p_func102(Param_p41f_func102_004);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
