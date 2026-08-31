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
            0xb9f5253dU, 0x044ec373U, 0x1c166a40U, 0x9c9e608cU,
        };
        HW_SCE_p_func101(Param_p41f_func101_001);
    }
    else
    {
        HW_SCE_p_func_sub004(0x000000a1U, 0x5a000104U, 0x00000000U);

        static const uint32_t Param_p41f_func101_002[] =
        {
            0xdaeef5f4U, 0x10b52bf0U, 0x92e41f6cU, 0xcf311c10U,
        };
        HW_SCE_p_func101(Param_p41f_func101_002);
    }

    WR1_PROG(REG_D0H, 0x0c000045U);
    HW_SCE_p_func_sub003(0x00410011U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        static const uint32_t Param_p41f_func100_001[] =
        {
            0xdd791e26U, 0x93c3eac4U, 0xa88feb51U, 0x0aed88daU,
        };
        HW_SCE_p_func100(Param_p41f_func100_001);
        HW_SCE_p_func_sub011(0x000003c1U, 0x0e000505U);
        WR4_ADDR(REG_2CH, &InData_Text[0]);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_DataT[0]);

        static const uint32_t Param_p41f_func102_001[] =
        {
            0x8526804fU, 0x5dca76d0U, 0x1a756727U, 0xe654482fU,
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

        HW_SCE_p_func_sub006(0x3420a840U, 0x00000010U, 0x00270000U);

        WR1_PROG(REG_94H, 0x0000b460U);
        HW_SCE_p_func_sub006(0x00000080U, 0x34202862U, 0x00270000U);

        static const uint32_t Param_p41f_func100_002[] =
        {
            0x530579a9U, 0x0f5004e7U, 0x6e5ef8ecU, 0x36aa8482U,
        };
        HW_SCE_p_func100(Param_p41f_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p41f_func102_002[] =
            {
                0x686b537eU, 0xdc94dd79U, 0x98487726U, 0x9f36a85dU,
            };
            HW_SCE_p_func102(Param_p41f_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub011(0x000003c1U, 0x0e000505U);
            WR4_ADDR(REG_2CH, &InData_Text[0]);

            WR1_PROG(REG_94H, 0x00000821U);
            WR1_PROG(REG_9CH, 0x80840001U);
            HW_SCE_p_func_sub003(0x03410011U);

            HW_SCE_p_func_sub001(0x000034e2U, 0x000568e7U, 0x00026ce7U, 0x00003827U);

            HW_SCE_p_func_sub001(0x0000b4c0U, 0x00000020U, 0x00003402U, 0x00008c00U);
            HW_SCE_p_func_sub001(0x0000001fU, 0x000028c0U, 0x00008cc0U, 0x0000001fU);

            HW_SCE_p_func_sub001(0x00004406U, 0x00007421U, 0x00007821U, 0x00003c27U);

            HW_SCE_p_func_sub001(0x000034c2U, 0x0000a4c0U, 0x0000001fU, 0x000568c6U);

            HW_SCE_p_func_sub022(0x000034e6U, 0x00026ce7U, 0x00000821U);

            for (iLoop = 0U; iLoop < 4; iLoop++)
            {
                HW_SCE_p_func_sub001(0x3420a8e0U, 0x0000000dU, 0x10003c27U, 0x1000a4e0U);
                WR1_PROG(REG_94H, 0x00000004U);
            }

            WR1_PROG(REG_D0H, 0x08000045U);
            WR1_PROG(REG_9CH, 0x81840001U);
            HW_SCE_p_func_sub003(0x00490011U);

            HW_SCE_p_func_sub011(0x000003c1U, 0x9c000005U);
            WR4_ADDR(REG_2CH, &InData_DataT[0]);

            static const uint32_t Param_p41f_func100_003[] =
            {
                0x8ff567a6U, 0xc3b043e0U, 0x7fc41c72U, 0x58fc265fU,
            };
            HW_SCE_p_func100(Param_p41f_func100_003);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p41f_func102_003[] =
                {
                    0x09d95487U, 0xdb40dc79U, 0x04d9ed6fU, 0x645830cdU,
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
                    0x96d1c2b1U, 0xbe6a3934U, 0xa5836c73U, 0x3644a5afU,
                };
                HW_SCE_p_func102(Param_p41f_func102_004);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
