/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CmacFinalSub (uint32_t InData_Cmd[],
                                     uint32_t InData_Text[],
                                     uint32_t InData_DataT[],
                                     uint32_t InData_DataTLen[],
                                     uint32_t OutData_DataT[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p41f_func100_001[] =
    {
        0x4a99ebceU, 0x994c779bU, 0xf070c5f0U, 0xd8443037U,
    };
    HW_SCE_p_func100(Param_p41f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p41f_func102_001[] =
        {
            0x17eb14a1U, 0xb77756aeU, 0xa6e65c9fU, 0xfba60a99U,
        };
        HW_SCE_p_func102(Param_p41f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            HW_SCE_p_func_sub021(0x00400a84U);

            static const uint32_t Param_p41f_func101_001[] =
            {
                0xcc1c0947U, 0x99cbbd69U, 0xcbae7594U, 0x176a22c1U,
            };
            HW_SCE_p_func101(Param_p41f_func101_001);
        }
        else
        {
            HW_SCE_p_func_sub021(0x00500a84U);

            static const uint32_t Param_p41f_func101_002[] =
            {
                0xfd8f573dU, 0x0b0980a6U, 0x7cbf9d4dU, 0x60bc39c5U,
            };
            HW_SCE_p_func101(Param_p41f_func101_002);
        }

        HW_SCE_p_func_sub019(0x00040c05U, 0x00001113U);

        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
        {
            static const uint32_t Param_p41f_func100_002[] =
            {
                0xaecaecc1U, 0x365ceb89U, 0x853113fbU, 0xe4a9d73eU,
            };
            HW_SCE_p_func100(Param_p41f_func100_002);
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00000e95U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Text[0]);

            WR1_PROG(REG_04H, 0x00000113U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_DataT[0]);

            static const uint32_t Param_p41f_func102_002[] =
            {
                0x46910254U, 0xfe754650U, 0x87941303U, 0xbbb02417U,
            };
            HW_SCE_p_func102(Param_p41f_func102_002);
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

            static const uint32_t Param_p41f_func100_003[] =
            {
                0x868c3fa6U, 0xcbebe6a2U, 0xa5e8d99fU, 0x4e7f2acbU,
            };
            HW_SCE_p_func100(Param_p41f_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p41f_func102_003[] =
                {
                    0xc84095e3U, 0xfe73f3faU, 0x5d208506U, 0x4f06dd4dU,
                };
                HW_SCE_p_func102(Param_p41f_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00000e95U);
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

                static const uint32_t Param_p41f_func100_004[] =
                {
                    0x209fb07dU, 0x45c52359U, 0x8bd1ffb8U, 0x63570637U,
                };
                HW_SCE_p_func100(Param_p41f_func100_004);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_p41f_func102_004[] =
                    {
                        0xc546b264U, 0xb50aa63aU, 0x59d29b24U, 0x618a6db3U,
                    };
                    HW_SCE_p_func102(Param_p41f_func102_004);
                    WR1_PROG(REG_1BCH, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
                }
                else
                {
                    static const uint32_t Param_p41f_func102_005[] =
                    {
                        0x927f099dU, 0xa622d40dU, 0x3fd396adU, 0x3552f048U,
                    };
                    HW_SCE_p_func102(Param_p41f_func102_005);
                    WR1_PROG(REG_1BCH, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
