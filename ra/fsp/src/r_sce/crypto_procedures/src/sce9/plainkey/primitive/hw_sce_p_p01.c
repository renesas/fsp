/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_SelfCheck1Sub (void)
{
    HW_SCE_SelfCheck1SubSub();

    WR1_PROG(REG_138H, 0xf597806AU);
    WR1_PROG(REG_F0H, 0x00000000U);

    WR1_PROG(REG_04H, 0x00000001U);
    WR1_PROG(REG_10CH, 0x00000701U);

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_80H, 0x00000001U);
    WR1_PROG(REG_28H, 0x00000001U);
    WR1_PROG(REG_7CH, 0x00000001U);
    WAIT_STS(REG_64H, 11, 0);
    WR1_PROG(REG_64H, 0x00000008U);

    WR1_PROG(REG_84H, 0x00010101U);
    WR1_PROG(REG_13CH, 0x00000F00U);

    WR1_PROG(REG_88H, 0x00008002U);

    WR1_PROG(REG_104H, 0x00000352U);
    static const uint32_t Param_p01_func101_001[] =
    {
        RSIP_PRV_BSWAP_32_C(0xe1a2a5d8U), RSIP_PRV_BSWAP_32_C(0x821a5428U), RSIP_PRV_BSWAP_32_C(0x7c777ac3U),
        RSIP_PRV_BSWAP_32_C(0xfd151290U),
    };
    HW_SCE_p_func101(Param_p01_func101_001);
    WR1_PROG(REG_88H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000352U);
    WR1_PROG(REG_C4H, 0x000f3a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H, 0x9ed66559U, 0x8e5bcbb9U, 0xd2f5d1d3U, 0xae209b90U);

    static const uint32_t Param_p01_func101_002[] =
    {
        RSIP_PRV_BSWAP_32_C(0xf4e6ce80U), RSIP_PRV_BSWAP_32_C(0x39773b0fU), RSIP_PRV_BSWAP_32_C(0x86227f8fU),
        RSIP_PRV_BSWAP_32_C(0x2b810040U),
    };
    HW_SCE_p_func101(Param_p01_func101_002);

    static const uint32_t Param_p01_func100_001[] =
    {
        RSIP_PRV_BSWAP_32_C(0x3e5590a5U), RSIP_PRV_BSWAP_32_C(0x96fa7453U), RSIP_PRV_BSWAP_32_C(0x0e213a19U),
        RSIP_PRV_BSWAP_32_C(0x12498aecU),
    };
    HW_SCE_p_func100(Param_p01_func100_001);

    WR1_PROG(REG_04H, 0x00001001U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_18H, 13, 0))
    {
        WR1_PROG(REG_1BCH, 0x00000020U);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_08H, 0x0000FFFFU);

        WR1_PROG(REG_13CH, 0x00000220U);

        static const uint32_t Param_p01_func102_001[] =
        {
            RSIP_PRV_BSWAP_32_C(0x62cb9591U), RSIP_PRV_BSWAP_32_C(0x72556c92U), RSIP_PRV_BSWAP_32_C(0x45cac937U),
            RSIP_PRV_BSWAP_32_C(0x8431be8fU),
        };
        HW_SCE_p_func102(Param_p01_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
