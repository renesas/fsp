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

rsip_ret_t r_rsip_p82 (void)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00820001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func_sub008(0x000000a1U, 0x0b0700c4U, 0x01a0d7adU);

    r_rsip_func_sub008(0x000000a1U, 0x08000074U, 0x00000000U);

    r_rsip_func_sub022(0x3000a820U, 0x00000003U, 0x00010020U);
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WAIT_STS(REG_00E8H, 0, 0);

    r_rsip_func100(bswap_32big(0xdb3f7c3fU),
                   bswap_32big(0x06fe7b27U),
                   bswap_32big(0x2a22f192U),
                   bswap_32big(0xba1a7776U));
    WR1_PROG(REG_0094H, 0x00007c01U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0x0000ffffU) == 0x00000000U)
    {
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200003U);

        r_rsip_func101(bswap_32big(0x3e4a56c4U), bswap_32big(0xee2bb50dU), bswap_32big(0x9f3c4c04U),
                       bswap_32big(0x148e46ebU));
    }
    else if (RD1_MASK(REG_0044H, 0x0000ffffU) == 0x00000001U)
    {
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200001U);

        r_rsip_func101(bswap_32big(0x0fa80c90U), bswap_32big(0xe19f96d8U), bswap_32big(0xd1ef2fa1U),
                       bswap_32big(0x463961dbU));
    }
    else if (RD1_MASK(REG_0044H, 0x0000ffffU) == 0x00000002U)
    {
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200002U);

        r_rsip_func101(bswap_32big(0xe59a4de7U), bswap_32big(0x180b625cU), bswap_32big(0xf0fa6d84U),
                       bswap_32big(0xef51ff10U));
    }

    WR1_PROG(REG_00D0H, 0x08000044U);
    r_rsip_func_sub012(0x81010020U, 0x00490005U);

    WR1_PROG(REG_0094H, 0x00000800U);
    r_rsip_func_sub006(0x80880000U, 0x03400021U, 0x000008e7U, 0x0000b480U);
    r_rsip_func_sub022(0xffffffffU, 0x0000b4c0U, 0x00000001U);

    WR1_PROG(REG_00D0H, 0x0e340406U);

    for (iLoop = 0U; iLoop < 32U; iLoop++)
    {
        r_rsip_func_sub012(0x80010000U, 0x03440005U);

        r_rsip_func_sub012(0x81010000U, 0x00490005U);

        WR1_PROG(REG_0094H, 0x00003420U);

        for (jLoop = 0U; jLoop < 8U; jLoop++)
        {
            r_rsip_func_sub022(0x00003441U, 0x00008c40U, 0x0000000fU);

            r_rsip_func_sub022(0x00016c42U, 0x01003862U, 0x00002c60U);

            WR1_PROG(REG_0094H, 0x01003c62U);

            WR1_PROG(REG_0094H, 0x00046821U);
        }

        r_rsip_func_sub022(0x00003420U, 0x00003441U, 0x00008c40U);
        r_rsip_func_sub022(0x80000000U, 0x38000882U, 0x00030020U);

        r_rsip_func_sub022(0x00002ca0U, 0x342028c5U, 0x100034c5U);

        r_rsip_func_sub022(0x00000060U, 0x0000b4a0U, 0x00000001U);

        WR1_PROG(REG_0094H, 0x00000080U);

        for (jLoop = 0U; jLoop < 31; jLoop++)
        {
            r_rsip_func_sub022(0x00016c21U, 0x00003481U, 0x00008c80U);
            r_rsip_func_sub022(0x80000000U, 0x38000882U, 0x00030020U);

            r_rsip_func_sub022(0x00002ca0U, 0x342028c5U, 0x100034c5U);

            r_rsip_func_sub022(0x00000060U, 0x00003444U, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000001U);

            WR1_PROG(REG_0094H, 0x00000080U);
        }

        WR1_PROG(REG_0094H, 0x00003420U);

        for (jLoop = 0U; jLoop < 32U; jLoop++)
        {
            r_rsip_func_sub022(0x38008c20U, 0x00000001U, 0x00020020U);

            r_rsip_func_sub022(0x00002ce0U, 0x00000060U, 0x0000a4e0U);
            r_rsip_func_sub022(0x00010000U, 0x00000080U, 0x00016821U);
        }
    }

    WR1_PROG(REG_0040H, 0x00001200U);
    WAIT_STS(REG_00C8H, 6, 0);
    WR1_PROG(REG_00D0H, 0x00000000U);
    WR1_PROG(REG_0040H, 0x00000400U);

    r_rsip_func_sub022(0x00000800U, 0x0000b420U, 0x00000033U);

    r_rsip_func_sub022(0x342028c1U, 0x2000d011U, 0x0000b4a0U);
    r_rsip_func_sub022(0x00000348U, 0x0000b4c0U, 0x000000b7U);

    r_rsip_func_sub022(0x00003467U, 0x00008c60U, 0x0000ffffU);

    r_rsip_func_sub022(0x34202865U, 0x2000d012U, 0x342028c3U);
    r_rsip_func_sub022(0x2000d012U, 0x001068e7U, 0x342028e5U);
    r_rsip_func_sub022(0x2000d013U, 0x342028c7U, 0x2000d013U);

    WR1_PROG(REG_0094H, 0x00002467U);

    r_rsip_func100(bswap_32big(0x19ef84d0U),
                   bswap_32big(0x11a71a71U),
                   bswap_32big(0x2101aad4U),
                   bswap_32big(0xd4ba091fU));
    r_rsip_func_sub010(0x38008860U, 0x00000400U, 0x00270000U);

    WR1_PROG(REG_0040H, 0x00402000U);

    WR1_PROG(REG_0008H, 0x00020000U);

    r_rsip_func_sub022(0x0000b420U, 0x0000005AU, 0x00000842U);

    r_rsip_func_sub022(0x00000863U, 0x00000884U, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000002U);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        r_rsip_func_sub022(0x010038c4U, 0x34202826U, 0x10005002U);

        r_rsip_func_sub022(0x00002466U, 0x00002c40U, 0x00002485U);
    }

    r_rsip_func100(bswap_32big(0x662f58bcU),
                   bswap_32big(0x9aae02a7U),
                   bswap_32big(0x70727172U),
                   bswap_32big(0x4fb03162U));
    r_rsip_func_sub010(0x38008860U, 0x00000100U, 0x00270000U);

    WR1_PROG(REG_0040H, 0x00402000U);

    WR1_PROG(REG_0008H, 0x00020000U);

    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);
    r_rsip_func_sub005(0x80010020U, 0x03410005U, 0x0001000dU);

    r_rsip_func_sub010(0x00002c20U, 0x38000c00U, 0x00A70000U);

    r_rsip_func100(bswap_32big(0x688c9855U),
                   bswap_32big(0x26fc508aU),
                   bswap_32big(0x7d1719d4U),
                   bswap_32big(0xb16f81d2U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xcc90679dU), bswap_32big(0x03ead581U), bswap_32big(0xebda5126U),
                       bswap_32big(0x680afa5eU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_RETRY;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x45c66b89U), bswap_32big(0x38dc1302U), bswap_32big(0xe7f1accbU),
                       bswap_32big(0x6711a61eU));

        r_rsip_func_sub008(0x000000a1U, 0x0c300104U, 0x00000000U);
        r_rsip_func_sub012(0x80040000U, 0x03410011U);

        WR1_PROG(REG_00D4H, 0x00000600U);
        WR1_PROG(REG_00D0H, 0x0e349407U);
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200003U);
        r_rsip_func_sub015(0x00440071U, 0x00001800U);
        r_rsip_func_sub013(0x0e340505U, 0x00440011U);

        WAIT_STS(REG_00E8H, 3, 0);
        WR1_PROG(REG_00E0H, 0x00000000U);
        r_rsip_func_sub012(0x80040080U, 0x03410011U);

        r_rsip_func_sub008(0x000000a1U, 0x080000b4U, 0x00000000U);

        r_rsip_func100(bswap_32big(0x906f3ee3U), bswap_32big(0xe926df4aU), bswap_32big(0x45ff6c11U),
                       bswap_32big(0xb5e0b885U));
        r_rsip_func_sub019(0x000003a1U, 0x08000075U);
        WR4_PROG(REG_002CH, bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000000U),
                 bswap_32big(0x00000001U));

        WR1_PROG(REG_00D4H, 0x00000100U);
        WR1_PROG(REG_00D0H, 0x07338d07U);
        r_rsip_func_sub012(0x81080000U, 0x00490021U);

        r_rsip_func_sub013(0x080000b5U, 0x00410011U);

        r_rsip_func100(bswap_32big(0x5474e439U), bswap_32big(0xfef6e25cU), bswap_32big(0x22f17b93U),
                       bswap_32big(0x907f221fU));
        r_rsip_func_sub013(0x08000075U, 0x00410011U);

        r_rsip_func103();
        r_rsip_func100(bswap_32big(0x8a213d55U), bswap_32big(0x7e9356efU), bswap_32big(0xc6cbedc0U),
                       bswap_32big(0xdecfebd3U));
        r_rsip_func_sub008(0x000000a1U, 0x0c2000d4U, 0x00000000U);

        r_rsip_func100(bswap_32big(0x60fa9fbaU), bswap_32big(0x000e3d5aU), bswap_32big(0xf7b9f45bU),
                       bswap_32big(0x5cd186caU));
        r_rsip_func103();
        r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

        WR1_PROG(REG_00A0H, 0x00030000U);
        WR1_PROG(REG_0004H, 0x20000000U);
        r_rsip_func_sub009(0x00000401U, 0x00c10009U, 0x00001800U);
        r_rsip_func_sub015(0x00010009U, 0x00001800U);

        WR1_PROG(REG_0004H, 0x00000000U);
        WR1_PROG(REG_00A0H, 0x00030000U);
        r_rsip_func_sub009(0x0000f400U, 0x00c00801U, 0x00001800U);

        WR1_PROG(REG_0070H, 0x00008002U);
        WR1_PROG(REG_0078H, 0x00000d01U);

        WR1_PROG(REG_0070H, 0x00008001U);

        WR1_PROG(REG_0078H, 0x00000221U);

        r_rsip_func102(bswap_32big(0xa900da65U), bswap_32big(0xc5a42a76U), bswap_32big(0x96e1637eU),
                       bswap_32big(0xbbee10f6U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
