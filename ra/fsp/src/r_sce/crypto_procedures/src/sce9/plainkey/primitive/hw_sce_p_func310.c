/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func310 (void)
{
    uint32_t oLoop2 = 0U;

    HW_SCE_p_func_sub014(0x00000bffU, 0x3800db6bU, 0x00A60000U);
    static const uint32_t Param_func310_func100_001[] =
    {
        0x37586798U, 0xceb0a5e6U, 0xd919e7e3U, 0xc7566c27U,
    };
    HW_SCE_p_func100(Param_func310_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_func310_func100_002[] =
        {
            0xba3e67acU, 0x77923dc6U, 0xf20f94eeU, 0x8caa5b29U,
        };
        HW_SCE_p_func100(Param_func310_func100_002);
        WR1_PROG(REG_E0H, 0x810103c0U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            WR1_PROG(REG_24H, 0x000009c0U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x04001991U);
            HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
            HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001191U, 0x000080c1U);
            WR1_PROG(REG_28H, 0x00bf0001U);

            WR1_PROG(REG_ECH, 0x00002fe0U);

            static const uint32_t Param_func310_func101_001[] =
            {
                0xa399fe47U, 0x7f8396a0U, 0xa5800b1bU, 0xa90e187aU,
            };
            HW_SCE_p_func101(Param_func310_func101_001);
        }

        static const uint32_t Param_func310_func101_002[] =
        {
            0xfd179c04U, 0x17853e37U, 0xb53c5511U, 0xfa864017U,
        };
        HW_SCE_p_func101(Param_func310_func101_002);
    }
    else
    {
        static const uint32_t Param_func310_func100_003[] =
        {
            0x249f2fc5U, 0x3cc969d5U, 0x8b2fc801U, 0x391bc107U,
        };
        HW_SCE_p_func100(Param_func310_func100_003);
        WR1_PROG(REG_E0H, 0x810103c0U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            WR1_PROG(REG_24H, 0x000009c0U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_24H, 0x04001981U);
            HW_SCE_p_func_sub015(0x000040c1U, 0x00800001U);
            HW_SCE_p_func_sub001(0x000011c0U, 0x00000004U, 0x82001181U, 0x000080c1U);
            WR1_PROG(REG_28H, 0x00bf0001U);

            WR1_PROG(REG_ECH, 0x00002fe0U);

            static const uint32_t Param_func310_func101_003[] =
            {
                0xf1d57656U, 0xc866fae8U, 0x1d69570cU, 0xc958fbf8U,
            };
            HW_SCE_p_func101(Param_func310_func101_003);
        }

        static const uint32_t Param_func310_func101_004[] =
        {
            0xb4b60db5U, 0x46826080U, 0xe4c9f49dU, 0x86683fceU,
        };
        HW_SCE_p_func101(Param_func310_func101_004);
    }

    WR1_PROG(REG_ECH, 0x38000bdfU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    WR1_PROG(REG_ECH, 0x00007c00U);
    WR1_PROG(REG_1CH, 0x00602000U);
}
