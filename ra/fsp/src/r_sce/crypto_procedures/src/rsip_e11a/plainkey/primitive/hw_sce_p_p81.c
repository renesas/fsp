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

    if (RD1_MASK(REG_90H, 0xFFFFFFFFU) != 0x00047C00U)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_0CH, 0x38c60eedU);
        WR1_PROG(REG_24H, 0x00000000U);
        WR1_PROG(REG_24H, 0x00000000U);
        WR1_PROG(REG_48H, 0x00000000U);

        WR1_PROG(REG_08H, 0x00000001U);
        WR1_PROG(REG_10H, 0x00001601U);
        WR1_PROG(REG_24H, 0x00000000U);
        WR1_PROG(REG_24H, 0x00000000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
        {
            return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
        }

        WR1_PROG(REG_C0H, 0x00000001U);
        WR1_PROG(REG_E0H, 0x00000001U);
        WR1_PROG(REG_F0H, 0x00000001U);

        WR1_PROG(REG_70H, 0x00818001U);
        WR1_PROG(REG_78H, 0x00000d00U);

        WR1_PROG(REG_C4H, 0x00008003U);

        WR1_PROG(REG_14H, 0x000003a1U);
        static const uint32_t Param_p81_func101_001[] =
        {
            RSIP_PRV_BSWAP_32_C(0xf0ff457fU), RSIP_PRV_BSWAP_32_C(0x2fe0cbe8U), RSIP_PRV_BSWAP_32_C(0x190e0f4aU),
            RSIP_PRV_BSWAP_32_C(0xb0f9c579U),
        };
        HW_SCE_p_func101(Param_p81_func101_001);
        WR1_PROG(REG_C4H, 0x00000000U);

        HW_SCE_p_func_sub008(0x000003a1U, 0x0a0700f5U);
        WR4_PROG(REG_2CH, 0x1863d378U, 0xf60d1643U, 0xfc1f44bdU, 0x46335a7cU);

        static const uint32_t Param_p81_func101_002[] =
        {
            RSIP_PRV_BSWAP_32_C(0x7b2dcda0U), RSIP_PRV_BSWAP_32_C(0x8e1de57bU), RSIP_PRV_BSWAP_32_C(0xfe9947d0U),
            RSIP_PRV_BSWAP_32_C(0x9c241705U),
        };
        HW_SCE_p_func101(Param_p81_func101_002);

        static const uint32_t Param_p81_func100_001[] =
        {
            RSIP_PRV_BSWAP_32_C(0x17f7cbc4U), RSIP_PRV_BSWAP_32_C(0xf4585f39U), RSIP_PRV_BSWAP_32_C(0xe0f297abU),
            RSIP_PRV_BSWAP_32_C(0xf225d9daU),
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
                RSIP_PRV_BSWAP_32_C(0xc8930ce0U), RSIP_PRV_BSWAP_32_C(0x63e5b4ecU), RSIP_PRV_BSWAP_32_C(0x5fb76a71U),
                RSIP_PRV_BSWAP_32_C(0xe7971d26U),
            };
            HW_SCE_p_func102(Param_p81_func102_001);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
