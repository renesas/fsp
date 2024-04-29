/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_SelfCheck1Sub (void)
{
    WR1_PROG(REG_1D04H, 0x000dec05U);
    WR1_PROG(REG_1D08H, 0x000f3c90U);

    WR1_PROG(REG_1D00H, 0x00000001U);

    WAIT_STS(REG_1D00H, 1, 0);

    if (RD1_MASK(REG_1D00H, 0x00030000U) != 0x00000000U)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_140CH, 0x38c60eedU);
        WR1_PROG(REG_1448H, 0x00000000U);

        WR1_PROG(REG_1408H, 0x00000001U);
        WR1_PROG(REG_1414H, 0x00001601U);

        if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
        {
            return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
        }
        else
        {
            ;
        }

        WR1_PROG(REG_1800H, 0x00000001U);
        WR1_PROG(REG_1700H, 0x00000001U);

        WR1_PROG(REG_1B00H, 0x00818001U);
        WR1_PROG(REG_1B08H, 0x00000d00U);

        WR1_PROG(REG_1804H, 0x00008002U);

        WR1_PROG(REG_1444H, 0x000003a2U);
        HW_SCE_p_func101(change_endian_long(0x761c3212U), change_endian_long(0x5929b561U), change_endian_long(0x41d63d71U), change_endian_long(0xc203e20eU));
        WR1_PROG(REG_1804H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x0a0700f5U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, 0xfa628a35U, 0x28f9dcb2U, 0x6bf927b0U, 0x111b9709U);

        HW_SCE_p_func101(change_endian_long(0x4462fc48U), change_endian_long(0x45c20005U), change_endian_long(0x382dac30U), change_endian_long(0x820498b6U));

        HW_SCE_p_func100(change_endian_long(0x0c85360bU), change_endian_long(0x8794147aU), change_endian_long(0x9fe177e4U), change_endian_long(0x38d62ae4U));

        WR1_PROG(REG_1408H, 0x00020000U);

        if (CHCK_STS(REG_142CH, 13, 0))
        {
            WR1_PROG(REG_14BCH, 0x00000020U);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1430H, 0x0000FFFFU);

            WR1_PROG(REG_1B08H, 0x00000220U);

            HW_SCE_p_func102(change_endian_long(0x3ef67e43U), change_endian_long(0xbf82d536U), change_endian_long(0x648d23c9U), change_endian_long(0xabad7ea7U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
