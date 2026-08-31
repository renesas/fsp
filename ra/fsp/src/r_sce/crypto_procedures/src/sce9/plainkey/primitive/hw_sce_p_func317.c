/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func317 (void)
{
    uint32_t oLoop1 = 0U;

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x00000010U);
    WR1_PROG(REG_ECH, 0x00003fbeU);

    WR1_PROG(REG_28H, 0x00a30001U);
    WR1_PROG(REG_ECH, 0x00000b39U);
    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_E0H, 0x800103c0U);
    HW_SCE_p_func_sub011(0x0000031fU, 0x00000023U);
    WR1_PROG(REG_00H, 0x00008307U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_ECH, 0x3800dbdfU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00A60000U);

    static const uint32_t Param_func317_func100_001[] =
    {
        0x54c736d5U, 0x1687cea2U, 0xb9a27aefU, 0x0efb8de2U,
    };
    HW_SCE_p_func100(Param_func317_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_28H, 0x00a30001U);
        WR1_PROG(REG_24H, 0x000009c0U);
        WAIT_STS(REG_24H, 21, 0);

        oLoop1 = 1;
        while (oLoop1 == 1)
        {
            WR1_PROG(REG_28H, 0x00870001U);
            WR1_PROG(REG_E0H, 0x800103c0U);
            HW_SCE_p_func_sub011(0x0000031fU, 0x00000023U);
            WR1_PROG(REG_00H, 0x00008307U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);
            WR1_PROG(REG_28H, 0x00a30001U);

            WR1_PROG(REG_ECH, 0x3800dbdfU);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00A60000U);

            static const uint32_t Param_func317_func100_002[] =
            {
                0xb050152eU, 0x4b531e69U, 0x106eb6e5U, 0xa55c8f7fU,
            };
            HW_SCE_p_func100(Param_func317_func100_002);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x00001981U);
                HW_SCE_p_func_sub016(0x000040c1U, 0x00002f20U);

                static const uint32_t Param_func317_func101_001[] =
                {
                    0x53c53629U, 0xc624f94dU, 0xcc1a9552U, 0x5b2c6d97U,
                };
                HW_SCE_p_func101(Param_func317_func101_001);
            }
            else
            {
                static const uint32_t Param_func317_func101_002[] =
                {
                    0x1279d640U, 0x26ecf237U, 0x637e567bU, 0xdf3efeccU,
                };
                HW_SCE_p_func101(Param_func317_func101_002);
                oLoop1 = 0;
            }
        }

        WR1_PROG(REG_ECH, 0x0000537fU);

        static const uint32_t Param_func317_func101_003[] =
        {
            0x7cb89078U, 0x36f852b6U, 0xb36ce496U, 0xdd7983beU,
        };
        HW_SCE_p_func101(Param_func317_func101_003);
    }
    else
    {
        HW_SCE_p_func_sub020(0x00a30001U, 0x000009c0U, 0x00001991U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x000040c1U);
        WAIT_STS(REG_24H, 21, 0);

        oLoop1 = 1;
        while (oLoop1 == 1)
        {
            WR1_PROG(REG_28H, 0x00870001U);
            WR1_PROG(REG_E0H, 0x800103c0U);
            HW_SCE_p_func_sub011(0x0000031fU, 0x00000023U);
            WR1_PROG(REG_00H, 0x00008307U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);
            WR1_PROG(REG_28H, 0x00a30001U);

            WR1_PROG(REG_ECH, 0x3800dbdfU);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00A60000U);

            static const uint32_t Param_func317_func100_003[] =
            {
                0x3b020f6eU, 0xeb260ad7U, 0xa93e0aa8U, 0x95ef9e82U,
            };
            HW_SCE_p_func100(Param_func317_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_24H, 0x00001981U);
                WAIT_STS(REG_24H, 21, 0);

                static const uint32_t Param_func317_func101_004[] =
                {
                    0x8624917eU, 0x91b076eeU, 0x5dbd5e14U, 0x70155193U,
                };
                HW_SCE_p_func101(Param_func317_func101_004);
                oLoop1 = 0;
            }
            else
            {
                WR1_PROG(REG_24H, 0x00001991U);
                HW_SCE_p_func_sub016(0x000040c1U, 0x00002f20U);

                static const uint32_t Param_func317_func101_005[] =
                {
                    0x09722fbaU, 0xa95ea208U, 0x4ad6f5a0U, 0xeaae6343U,
                };
                HW_SCE_p_func101(Param_func317_func101_005);
            }
        }

        WR1_PROG(REG_ECH, 0x0000577fU);

        static const uint32_t Param_func317_func101_006[] =
        {
            0x654a6dd5U, 0x21175d16U, 0x4cab116eU, 0xbfd1f105U,
        };
        HW_SCE_p_func101(Param_func317_func101_006);
    }

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x00000010U, 0x00003bbeU, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
