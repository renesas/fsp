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

rsip_ret_t r_rsip_pe4 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e40001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3000a880U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b480U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_0094H, 0x00000080U);

    r_rsip_func100(bswap_32big(0xfe162781U),
                   bswap_32big(0x738fb169U),
                   bswap_32big(0xe2f053bdU),
                   bswap_32big(0x7169b5feU));
    WR1_PROG(REG_0094H, 0x00007c04U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e4U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x41e5ce18U), bswap_32big(0xa70e3026U), bswap_32big(0x01733264U),
                       bswap_32big(0x5fbb93efU));
        r_rsip_func407(InData_EncSecret);

        r_rsip_func101(bswap_32big(0x0532841eU), bswap_32big(0x1ff8f191U), bswap_32big(0xee62a836U),
                       bswap_32big(0x1f0bee28U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e4U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x69169879U), bswap_32big(0x863d67caU), bswap_32big(0x4b5a5802U),
                       bswap_32big(0xdef29282U));
        r_rsip_func410(InData_EncSecret);

        r_rsip_func101(bswap_32big(0x434b6f66U), bswap_32big(0x9a185dfeU), bswap_32big(0xb602e35cU),
                       bswap_32big(0xe2034d83U));
    }

    r_rsip_func100(bswap_32big(0x73dcbc25U),
                   bswap_32big(0x56913bddU),
                   bswap_32big(0xdd5b61bfU),
                   bswap_32big(0x7595fcf9U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xc99a51c9U), bswap_32big(0xa4ab7c6bU), bswap_32big(0x34333d68U),
                       bswap_32big(0x22c6f110U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x48a0648dU), bswap_32big(0x28550348U), bswap_32big(0x965f5232U),
                       bswap_32big(0xc0376d2cU));
        r_rsip_func103();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c200104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_009CH, 0x80010000U);
        WR1_PROG(REG_0000H, 0x03410005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0000H, 0x0001000dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x000034c0U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e4U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xf0a01da5U), bswap_32big(0xa11df14eU), bswap_32big(0xa6ec8354U),
                       bswap_32big(0x44ec8499U));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x30003080U);
        WR1_PROG(REG_0094H, 0x00070020U);
        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x01b41ce9U);
        WR1_PROG(REG_0094H, 0x00000060U);
        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x0199f119U);
        WR1_PROG(REG_0094H, 0x00000080U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e4U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x2b3945acU), bswap_32big(0x1e20d2e0U), bswap_32big(0xd624eeb9U),
                       bswap_32big(0x1ad142e1U));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0x82ae1a4aU), bswap_32big(0xb8ee1e65U), bswap_32big(0x8e7454e1U),
                       bswap_32big(0xadbe040dU));
        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            r_rsip_func100(bswap_32big(0x10f1844cU), bswap_32big(0xdb5de387U), bswap_32big(0x5d2151b9U),
                           bswap_32big(0xa79a314aU));

            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xe7009d07U);
            WR1_PROG(REG_0000H, 0x00430021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

            r_rsip_func100(bswap_32big(0xdd9fb145U), bswap_32big(0x0513e5f9U), bswap_32big(0xa840a2a2U),
                           bswap_32big(0x497cb99bU));
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xe7008d07U);
            WR1_PROG(REG_0000H, 0x00400021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

            r_rsip_func100(bswap_32big(0xbf082c0fU), bswap_32big(0xa88b6b8aU), bswap_32big(0xb7910cc5U),
                           bswap_32big(0xfcc052cdU));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x0c000104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x09108105U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[17]);

            r_rsip_func101(bswap_32big(0xfb37f0f2U), bswap_32big(0x9feadcafU), bswap_32big(0x057e694fU),
                           bswap_32big(0x1b24d719U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func100(bswap_32big(0x9ee2f6b5U), bswap_32big(0x10097112U), bswap_32big(0x393153e3U),
                           bswap_32big(0xf9dd4c79U));

            WR1_PROG(REG_00B0H, 0x00009806U);
            WR1_PROG(REG_00D4H, 0x40000200U);
            WR1_PROG(REG_00D0H, 0xe7009d07U);
            WR1_PROG(REG_0000H, 0x00430031U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001032U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);

            r_rsip_func100(bswap_32big(0xb5108a78U), bswap_32big(0x717cf5fcU), bswap_32big(0xe5b20fedU),
                           bswap_32big(0x600915d5U));
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xe7008d07U);
            WR1_PROG(REG_0000H, 0x00400011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

            r_rsip_func100(bswap_32big(0x1597ede5U), bswap_32big(0xda02dc00U), bswap_32big(0x1c3db898U),
                           bswap_32big(0xb6c12c57U));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x0c000104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x09108105U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KeyIndex[17]);

            r_rsip_func101(bswap_32big(0xa0a7ff8bU), bswap_32big(0x5ffeddddU), bswap_32big(0x2a7a73c4U),
                           bswap_32big(0x9cf2262fU));
        }

        r_rsip_func100(bswap_32big(0x953632e2U), bswap_32big(0x55c40fabU), bswap_32big(0x39b232ccU),
                       bswap_32big(0xc2e9ec23U));
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

        r_rsip_func102(bswap_32big(0x3c81548dU), bswap_32big(0x748f2872U), bswap_32big(0xa07a77bbU),
                       bswap_32big(0xe0b908d6U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
