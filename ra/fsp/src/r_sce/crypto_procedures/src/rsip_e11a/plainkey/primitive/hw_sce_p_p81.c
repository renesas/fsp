/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

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
        HW_SCE_p_func101(change_endian_long(0xf0ff457fU), change_endian_long(0x2fe0cbe8U), change_endian_long(0x190e0f4aU), change_endian_long(0xb0f9c579U));
        WR1_PROG(REG_C4H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000003a1U);
        WR1_PROG(REG_D0H, 0x0a0700f5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, 0x1863d378U, 0xf60d1643U, 0xfc1f44bdU, 0x46335a7cU);

        HW_SCE_p_func101(change_endian_long(0x7b2dcda0U), change_endian_long(0x8e1de57bU), change_endian_long(0xfe9947d0U), change_endian_long(0x9c241705U));

        HW_SCE_p_func100(change_endian_long(0x17f7cbc4U), change_endian_long(0xf4585f39U), change_endian_long(0xe0f297abU), change_endian_long(0xf225d9daU));

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

            HW_SCE_p_func102(change_endian_long(0xc8930ce0U), change_endian_long(0x63e5b4ecU), change_endian_long(0x5fb76a71U), change_endian_long(0xe7971d26U));
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
