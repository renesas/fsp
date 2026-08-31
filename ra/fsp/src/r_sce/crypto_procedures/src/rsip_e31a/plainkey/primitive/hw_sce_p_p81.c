/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_SelfCheck1Sub (void)
{
    WR1_PROG(REG_8CH, 0x00000001U);

    WAIT_STS(REG_8CH, 1, 0);

    if (RD1_MASK(REG_90H, 0xFFFFFFFFU) != 0x000D8087U)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_0CH, 0x38c60eedU);
        WR1_PROG(REG_48H, 0x00000000U);

        WR1_PROG(REG_08H, 0x00000001U);
        WR1_PROG(REG_10H, 0x00001601U);

        if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
        {
            return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
        }

        WR1_PROG(REG_C0H, 0x00000001U);
        WR1_PROG(REG_E0H, 0x00000001U);

        WR1_PROG(REG_70H, 0x00818001U);
        WR1_PROG(REG_78H, 0x00000d00U);

        WR1_PROG(REG_C4H, 0x00008004U);

        WR1_PROG(REG_14H, 0x000003a1U);
        static const uint32_t Param_p81_func101_001[] =
        {
            RSIP_PRV_BSWAP_32_C(0xfa0903b2U), RSIP_PRV_BSWAP_32_C(0x13f8a51bU), RSIP_PRV_BSWAP_32_C(0x7857b30eU),
            RSIP_PRV_BSWAP_32_C(0x146acec5U),
        };
        HW_SCE_p_func101(Param_p81_func101_001);
        WR1_PROG(REG_C4H, 0x00000000U);

        HW_SCE_p_func_sub011(0x000003a1U, 0x0a0700f5U);
        WR4_PROG(REG_2CH, 0xec969662U, 0xfcfc0cb9U, 0x7d09e6c4U, 0xe0ae59bfU);

        static const uint32_t Param_p81_func101_002[] =
        {
            RSIP_PRV_BSWAP_32_C(0x9b550eceU), RSIP_PRV_BSWAP_32_C(0x990e35fcU), RSIP_PRV_BSWAP_32_C(0xec4b9d1bU),
            RSIP_PRV_BSWAP_32_C(0x6eff2683U),
        };
        HW_SCE_p_func101(Param_p81_func101_002);

        static const uint32_t Param_p81_func100_001[] =
        {
            RSIP_PRV_BSWAP_32_C(0x1a7ca069U), RSIP_PRV_BSWAP_32_C(0x94dc91e3U), RSIP_PRV_BSWAP_32_C(0x0648b0a3U),
            RSIP_PRV_BSWAP_32_C(0x123df0e8U),
        };
        HW_SCE_p_func100(Param_p81_func100_001);

        WR1_PROG(REG_08H, 0x00020000U);

        if (CHCK_STS(REG_20H, 13, 0))
        {
            WR1_PROG(REG_6CH, 0x00000020U);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_38H, 0x000000F1U);

            WR1_PROG(REG_78H, 0x00000220U);

            static const uint32_t Param_p81_func102_001[] =
            {
                RSIP_PRV_BSWAP_32_C(0x702a3445U), RSIP_PRV_BSWAP_32_C(0x7bb18f33U), RSIP_PRV_BSWAP_32_C(0x6fe3f500U),
                RSIP_PRV_BSWAP_32_C(0xffa23a05U),
            };
            HW_SCE_p_func102(Param_p81_func102_001);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
