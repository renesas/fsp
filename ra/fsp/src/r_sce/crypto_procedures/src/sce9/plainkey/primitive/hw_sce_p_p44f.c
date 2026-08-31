/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CmacFinalSub (uint32_t InData_Cmd[],
                                     uint32_t InData_Text[],
                                     uint32_t InData_DataT[],
                                     uint32_t InData_DataTLen[],
                                     uint32_t OutData_DataT[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p44f_func100_001[] =
    {
        0xf12ceb80U, 0xd9c1ad15U, 0xf0601e59U, 0xebbb0fa5U,
    };
    HW_SCE_p_func100(Param_p44f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p44f_func102_001[] =
        {
            0xda00fcb8U, 0xa57aaf1bU, 0x95160be9U, 0x895676beU,
        };
        HW_SCE_p_func102(Param_p44f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            WR1_PROG(REG_104H, 0x00000051U);
            WR1_PROG(REG_B0H, 0x40000000U);
            WR1_PROG(REG_A4H, 0x00408a84U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));

            static const uint32_t Param_p44f_func101_001[] =
            {
                0x0cd04e7dU, 0x9fd5dc73U, 0x9a3cbb47U, 0x724115f4U,
            };
            HW_SCE_p_func101(Param_p44f_func101_001);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000051U);
            WR1_PROG(REG_B0H, 0x40000000U);
            WR1_PROG(REG_A4H, 0x00508a84U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));

            static const uint32_t Param_p44f_func101_002[] =
            {
                0x96ed81b8U, 0xe4f38e9bU, 0x57ba7900U, 0xd6d5d4f7U,
            };
            HW_SCE_p_func101(Param_p44f_func101_002);
        }

        HW_SCE_p_func_sub019(0x00040c05U, 0x00001113U);

        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
        {
            static const uint32_t Param_p44f_func100_002[] =
            {
                0x4d56af1dU, 0x2e043c8cU, 0x6111e33dU, 0x5219a7baU,
            };
            HW_SCE_p_func100(Param_p44f_func100_002);
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_B0H, 0x40000000U);
            WR1_PROG(REG_A4H, 0x00008e95U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Text[0]);

            WR1_PROG(REG_04H, 0x00000113U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_DataT[0]);

            static const uint32_t Param_p44f_func102_002[] =
            {
                0x0166df65U, 0xb722f713U, 0x23f23e9dU, 0x35adb4daU,
            };
            HW_SCE_p_func102(Param_p44f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010040U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_DataTLen[0]);

            HW_SCE_p_func_sub014(0x3420a840U, 0x00000010U, 0x00260000U);

            HW_SCE_p_func_sub007(0x0000b460U, 0x00000080U, 0x34202862U, 0x00260000U);

            static const uint32_t Param_p44f_func100_003[] =
            {
                0xe1b828acU, 0xeec7109fU, 0xaaa40e84U, 0x7a5fa67aU,
            };
            HW_SCE_p_func100(Param_p44f_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p44f_func102_003[] =
                {
                    0x5aa774dcU, 0xac0f2b93U, 0xb9a1ecdfU, 0xeb96fc9bU,
                };
                HW_SCE_p_func102(Param_p44f_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_B0H, 0x40000000U);
                WR1_PROG(REG_A4H, 0x00008e95U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_Text[0]);

                WR1_PROG(REG_ECH, 0x00000821U);
                HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

                HW_SCE_p_func_sub022(0x000034e2U, 0x000568e7U, 0x00026ce7U, 0x00003827U);

                HW_SCE_p_func_sub022(0x0000b4c0U, 0x00000020U, 0x00003402U, 0x00008c00U);
                HW_SCE_p_func_sub022(0x0000001fU, 0x000028c0U, 0x00008cc0U, 0x0000001fU);

                HW_SCE_p_func_sub022(0x00004406U, 0x00007421U, 0x00007821U, 0x00003c27U);

                HW_SCE_p_func_sub022(0x000034c2U, 0x0000a4c0U, 0x0000001fU, 0x000568c6U);

                WR1_PROG(REG_ECH, 0x000034e6U);
                WR1_PROG(REG_ECH, 0x00026ce7U);

                WR1_PROG(REG_ECH, 0x00000821U);

                for (iLoop = 0U; iLoop < 4; iLoop++)
                {
                    HW_SCE_p_func_sub022(0x3420a8e0U, 0x0000000dU, 0x10003c27U, 0x1000a4e0U);
                    WR1_PROG(REG_ECH, 0x00000004U);
                }

                WR1_PROG(REG_A4H, 0x00040805U);
                HW_SCE_p_func_sub010(0x81840001U, 0x00001813U);

                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00900c05U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_DataT[0]);

                static const uint32_t Param_p44f_func100_004[] =
                {
                    0x50998f29U, 0x33e8aa7dU, 0x6ddef9aeU, 0x50022b35U,
                };
                HW_SCE_p_func100(Param_p44f_func100_004);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_p44f_func102_004[] =
                    {
                        0xf9748aefU, 0x98e726d3U, 0x3ea79cd2U, 0xd61b8294U,
                    };
                    HW_SCE_p_func102(Param_p44f_func102_004);
                    WR1_PROG(REG_1BCH, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
                }
                else
                {
                    static const uint32_t Param_p44f_func102_005[] =
                    {
                        0xa742a0f5U, 0xeb4e1673U, 0xd9493fc0U, 0x626c6415U,
                    };
                    HW_SCE_p_func102(Param_p44f_func102_005);
                    WR1_PROG(REG_1BCH, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
