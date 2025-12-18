/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

rsip_ret_t r_rsip_p34i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00340001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000034U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x143eee35U),
                   bswap_32big(0x485cef6fU),
                   bswap_32big(0xb8cb7a43U),
                   bswap_32big(0x46efd2c9U));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x370d1553U),
                   bswap_32big(0x452bec0bU),
                   bswap_32big(0xb3934097U),
                   bswap_32big(0x6ade8a93U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x21a6b49aU), bswap_32big(0x6d28f224U), bswap_32big(0xc4fcff0eU),
                       bswap_32big(0x820a786fU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func_sub014(0x000000c7U, 0x80010080U);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub016(0x38000c84U, 0x00000080U, 0x00270000U);

        r_rsip_func100(bswap_32big(0x4d60086dU), bswap_32big(0x761da2a8U), bswap_32big(0x3db98b0fU),
                       bswap_32big(0xe36f3814U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func_sub019(0x000003c1U, 0x08000105U);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func_sub009(0x00000401U, 0x00c10009U, 0x00001800U);

            r_rsip_func_sub009(0x00000402U, 0x00c10009U, 0x00001800U);

            r_rsip_func101(bswap_32big(0xd25a343bU), bswap_32big(0x3b0319aeU), bswap_32big(0x59dac13eU),
                           bswap_32big(0xfa4b0d22U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000034U, 0x00000000U);

            r_rsip_func101(bswap_32big(0x2c1edbe8U), bswap_32big(0x4348c231U), bswap_32big(0xc34d976dU),
                           bswap_32big(0x8f1b4642U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xc2f1cec3U), bswap_32big(0x0ecd6ee0U), bswap_32big(0x8dafd6c8U),
                           bswap_32big(0xef6eced2U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x58150055U),
                               bswap_32big(0x35273468U),
                               bswap_32big(0x87442223U),
                               bswap_32big(0x904cae7fU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xc88f9d09U),
                               bswap_32big(0x750d9d7eU),
                               bswap_32big(0xdde1a68eU),
                               bswap_32big(0xb384ad09U));
            }
        }

        r_rsip_func100(bswap_32big(0x2caacc1dU), bswap_32big(0x01fcfe34U), bswap_32big(0xe2faf971U),
                       bswap_32big(0x1981b5c5U));
        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub009(0x0000181eU, 0x00430011U, 0x00001800U);

        r_rsip_func100(bswap_32big(0x66a6d7caU), bswap_32big(0xc0b7b2feU), bswap_32big(0xf8644b23U),
                       bswap_32big(0xc4a4507cU));
        r_rsip_func_sub013(0x08000095U, 0x00430011U);

        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub009(0x00000801U, 0x03430009U, 0x00001800U);

        r_rsip_func_sub009(0x00000802U, 0x03430009U, 0x00001800U);

        r_rsip_func100(bswap_32big(0x8533f16dU), bswap_32big(0xefd2149cU), bswap_32big(0x235419ccU),
                       bswap_32big(0xac05f2a0U));
        r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func_sub011(0x000000a1U, 0x40000000U, 0x0a0080a4U);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0xde1e5ac2U), bswap_32big(0xdaedc848U), bswap_32big(0x305ff0acU),
                       bswap_32big(0xff94c7cfU));

        return RSIP_RET_PASS;
    }
}
