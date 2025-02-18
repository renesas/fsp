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

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

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

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0b0700c4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x013e68caU));

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000074U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0094H, 0x3000a820U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WAIT_STS(REG_00E8H, 0, 0);

    r_rsip_func100(bswap_32big(0x869b3c42U), bswap_32big(0x51263821U), bswap_32big(0x821ebba4U), bswap_32big(0xed64efedU));
    WR1_PROG(REG_0094H, 0x00007c01U);
    WR1_PROG(REG_0040H, 0x00600000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (RD1_MASK(REG_0044H, 0x0000ffffU) == 0x00000000U)
    {
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200003U);

        r_rsip_func101(bswap_32big(0x02ba031eU), bswap_32big(0x37813b54U), bswap_32big(0xc118d76bU), bswap_32big(0xfe686544U));
    }
    else if (RD1_MASK(REG_0044H, 0x0000ffffU) == 0x00000001U)
    {
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200001U);

        r_rsip_func101(bswap_32big(0x9a273f1dU), bswap_32big(0xf5123ebdU), bswap_32big(0xc736eccdU), bswap_32big(0x018c4880U));
    }
    else if (RD1_MASK(REG_0044H, 0x0000ffffU) == 0x00000002U)
    {
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200002U);

        r_rsip_func101(bswap_32big(0x17dd015cU), bswap_32big(0xee695ed1U), bswap_32big(0x483e796fU), bswap_32big(0xa36cf3a5U));
    }

    WR1_PROG(REG_00D0H, 0x08000044U);
    WR1_PROG(REG_009CH, 0x81010020U);
    WR1_PROG(REG_0000H, 0x00490005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00000800U);
    WR1_PROG(REG_009CH, 0x80880000U);
    WR1_PROG(REG_0000H, 0x03400021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x000008e7U);

    WR1_PROG(REG_0094H, 0x0000b480U);
    WR1_PROG(REG_0094H, 0xffffffffU);

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000001U);

    WR1_PROG(REG_00D0H, 0x0e340406U);

    for (iLoop = 0U; iLoop < 32U; iLoop++)
    {
        WR1_PROG(REG_009CH, 0x80010000U);
        WR1_PROG(REG_0000H, 0x03440005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0000H, 0x00490005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x00003420U);

        for (jLoop = 0U; jLoop < 8U; jLoop++)
        {
            WR1_PROG(REG_0094H, 0x00003441U);

            WR1_PROG(REG_0094H, 0x00008c40U);
            WR1_PROG(REG_0094H, 0x0000000fU);

            WR1_PROG(REG_0094H, 0x00016c42U);

            WR1_PROG(REG_0094H, 0x01003862U);

            WR1_PROG(REG_0094H, 0x00002c60U);

            WR1_PROG(REG_0094H, 0x01003c62U);

            WR1_PROG(REG_0094H, 0x00046821U);
        }

        WR1_PROG(REG_0094H, 0x00003420U);

        WR1_PROG(REG_0094H, 0x00003441U);

        WR1_PROG(REG_0094H, 0x00008c40U);
        WR1_PROG(REG_0094H, 0x80000000U);

        WR1_PROG(REG_0094H, 0x38000882U);
        WR1_PROG(REG_0094H, 0x00030020U);

        WR1_PROG(REG_0094H, 0x00002ca0U);

        WR1_PROG(REG_0094H, 0x342028c5U);
        WR1_PROG(REG_0094H, 0x100034c5U);

        WR1_PROG(REG_0094H, 0x00000060U);

        WR1_PROG(REG_0094H, 0x0000b4a0U);
        WR1_PROG(REG_0094H, 0x00000001U);

        WR1_PROG(REG_0094H, 0x00000080U);

        for (jLoop = 0U; jLoop < 31; jLoop++)
        {
            WR1_PROG(REG_0094H, 0x00016c21U);

            WR1_PROG(REG_0094H, 0x00003481U);

            WR1_PROG(REG_0094H, 0x00008c80U);
            WR1_PROG(REG_0094H, 0x80000000U);

            WR1_PROG(REG_0094H, 0x38000882U);
            WR1_PROG(REG_0094H, 0x00030020U);

            WR1_PROG(REG_0094H, 0x00002ca0U);

            WR1_PROG(REG_0094H, 0x342028c5U);
            WR1_PROG(REG_0094H, 0x100034c5U);

            WR1_PROG(REG_0094H, 0x00000060U);

            WR1_PROG(REG_0094H, 0x00003444U);

            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000001U);

            WR1_PROG(REG_0094H, 0x00000080U);
        }

        WR1_PROG(REG_0094H, 0x00003420U);

        for (jLoop = 0U; jLoop < 32U; jLoop++)
        {
            WR1_PROG(REG_0094H, 0x38008c20U);
            WR1_PROG(REG_0094H, 0x00000001U);
            WR1_PROG(REG_0094H, 0x00020020U);

            WR1_PROG(REG_0094H, 0x00002ce0U);

            WR1_PROG(REG_0094H, 0x00000060U);

            WR1_PROG(REG_0094H, 0x0000a4e0U);
            WR1_PROG(REG_0094H, 0x00010000U);

            WR1_PROG(REG_0094H, 0x00000080U);

            WR1_PROG(REG_0094H, 0x00016821U);
        }
    }

    WR1_PROG(REG_0040H, 0x00001200U);
    WAIT_STS(REG_00C8H, 6, 0);
    WR1_PROG(REG_00D0H, 0x00000000U);
    WR1_PROG(REG_0040H, 0x00000400U);

    WR1_PROG(REG_0094H, 0x00000800U);

    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000033U);

    WR1_PROG(REG_0094H, 0x342028c1U);
    WR1_PROG(REG_0094H, 0x2000d011U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000348U);

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x000000b7U);

    WR1_PROG(REG_0094H, 0x00003467U);
    WR1_PROG(REG_0094H, 0x00008c60U);
    WR1_PROG(REG_0094H, 0x0000ffffU);

    WR1_PROG(REG_0094H, 0x34202865U);
    WR1_PROG(REG_0094H, 0x2000d012U);

    WR1_PROG(REG_0094H, 0x342028c3U);
    WR1_PROG(REG_0094H, 0x2000d012U);

    WR1_PROG(REG_0094H, 0x001068e7U);

    WR1_PROG(REG_0094H, 0x342028e5U);
    WR1_PROG(REG_0094H, 0x2000d013U);

    WR1_PROG(REG_0094H, 0x342028c7U);
    WR1_PROG(REG_0094H, 0x2000d013U);

    WR1_PROG(REG_0094H, 0x00002467U);

    r_rsip_func100(bswap_32big(0xe51d9bd1U), bswap_32big(0x08064450U), bswap_32big(0x3c90aa9cU), bswap_32big(0x56592491U));
    WR1_PROG(REG_0094H, 0x38008860U);
    WR1_PROG(REG_0094H, 0x00000400U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0040H, 0x00402000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0008H, 0x00020000U);

    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x0000005AU);

    WR1_PROG(REG_0094H, 0x00000842U);

    WR1_PROG(REG_0094H, 0x00000863U);

    WR1_PROG(REG_0094H, 0x00000884U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000002U);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WR1_PROG(REG_0094H, 0x010038c4U);

        WR1_PROG(REG_0094H, 0x34202826U);
        WR1_PROG(REG_0094H, 0x10005002U);

        WR1_PROG(REG_0094H, 0x00002466U);

        WR1_PROG(REG_0094H, 0x00002c40U);

        WR1_PROG(REG_0094H, 0x00002485U);
    }

    r_rsip_func100(bswap_32big(0x8493fd57U), bswap_32big(0x807be07eU), bswap_32big(0x9693dc53U), bswap_32big(0xf141011eU));
    WR1_PROG(REG_0094H, 0x38008860U);
    WR1_PROG(REG_0094H, 0x00000100U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0040H, 0x00402000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0008H, 0x00020000U);

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c000104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_009CH, 0x80010020U);
    WR1_PROG(REG_0000H, 0x03410005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0000H, 0x0001000dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00002c20U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x3d511ae0U), bswap_32big(0x00f2c4b5U), bswap_32big(0x0d73b1d9U), bswap_32big(0x71ad1793U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x422babd7U), bswap_32big(0xc3833acfU), bswap_32big(0x0e409217U), bswap_32big(0xfbb526d2U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_RETRY;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x91b39c03U), bswap_32big(0x1a733febU), bswap_32big(0x96bf867bU), bswap_32big(0x6e999f41U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c300104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
        WR1_PROG(REG_009CH, 0x80040000U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D4H, 0x00000600U);
        WR1_PROG(REG_00D0H, 0x0e349407U);
        WAIT_STS(REG_00E8H, 0, 0);
        WR1_PROG(REG_00E4H, 0x00200003U);
        WR1_PROG(REG_0000H, 0x00440071U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_00D0H, 0x0e340505U);
        WR1_PROG(REG_0000H, 0x00440011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WAIT_STS(REG_00E8H, 3, 0);
        WR1_PROG(REG_00E0H, 0x00000000U);
        WR1_PROG(REG_009CH, 0x80040080U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x080000b4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0x115bccc8U), bswap_32big(0x8dc77d91U), bswap_32big(0x1ea9bdffU), bswap_32big(0x4d64f882U));
        WR1_PROG(REG_0014H, 0x000003a1U);
        WR1_PROG(REG_00D0H, 0x08000075U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_PROG(REG_002CH, bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000001U));

        WR1_PROG(REG_00D4H, 0x00000100U);
        WR1_PROG(REG_00D0H, 0x07338d07U);
        WR1_PROG(REG_009CH, 0x81080000U);
        WR1_PROG(REG_0000H, 0x00490021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D0H, 0x080000b5U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x1b4918e3U), bswap_32big(0xd02a381bU), bswap_32big(0xbdbda91bU), bswap_32big(0xe029dcadU));
        WR1_PROG(REG_00D0H, 0x08000075U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func103();
        r_rsip_func100(bswap_32big(0x17b89998U), bswap_32big(0x555ab9c3U), bswap_32big(0x7dd3d4fcU), bswap_32big(0xbd10c10bU));
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c2000d4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0x8cc5e8a1U), bswap_32big(0xf5a4c4b6U), bswap_32big(0x09b81925U), bswap_32big(0x98e790edU));
        r_rsip_func103();
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c200104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00A0H, 0x00030000U);
        WR1_PROG(REG_0004H, 0x20000000U);
        WR1_PROG(REG_00B0H, 0x00000401U);

        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0000H, 0x00010009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0004H, 0x00000000U);
        WR1_PROG(REG_00A0H, 0x00030000U);
        WR1_PROG(REG_00B0H, 0x000074c0U);
        WR1_PROG(REG_0000H, 0x00c00601U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0070H, 0x00008002U);
        WR1_PROG(REG_0078H, 0x00000d01U);

        WR1_PROG(REG_0070H, 0x00008001U);

        WR1_PROG(REG_0078H, 0x00000214U);

        r_rsip_func102(bswap_32big(0x84053bdbU), bswap_32big(0xbbe3627dU), bswap_32big(0xa7926190U), bswap_32big(0x8fbd6cbdU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
