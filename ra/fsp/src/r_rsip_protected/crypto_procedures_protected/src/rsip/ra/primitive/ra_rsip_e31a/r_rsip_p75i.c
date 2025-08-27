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

rsip_ret_t r_rsip_p75i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_MsgLen[],
                        uint32_t       KEY_INDEX_SIZE)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00750001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00F0H, 0x00000001U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c84U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0x8987a1ddU),
                   bswap_32big(0x2c646244U),
                   bswap_32big(0x370882f9U),
                   bswap_32big(0xb97b7af3U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x313567b4U), bswap_32big(0x9aac8f6bU), bswap_32big(0xb53e48ddU),
                       bswap_32big(0x7c1e6c6fU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x1424b01dU), bswap_32big(0x8dceca5aU), bswap_32big(0xaf03518bU),
                       bswap_32big(0x8ea28928U));
        WR1_PROG(REG_0094H, 0x3420a880U);
        WR1_PROG(REG_0094H, 0x00000007U);
        WR1_PROG(REG_0094H, 0x2000b480U);
        WR1_PROG(REG_0094H, 0x00000006U);

        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0000001bU);

            WR1_PROG(REG_00F4H, 0x00000050U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000008U);

            r_rsip_func101(bswap_32big(0x55790f00U), bswap_32big(0x7bc730e9U), bswap_32big(0x3be72c8fU),
                           bswap_32big(0xe6ceceafU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000028U);

            WR1_PROG(REG_00F4H, 0x000000a0U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x0000000cU);

            r_rsip_func101(bswap_32big(0x378643adU), bswap_32big(0xdc6f3fdfU), bswap_32big(0x869c25a9U),
                           bswap_32big(0xeb22d1b9U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000029U);

            WR1_PROG(REG_00F4H, 0x000000b0U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            r_rsip_func101(bswap_32big(0xe929d022U), bswap_32big(0x53e2a224U), bswap_32big(0x89767c00U),
                           bswap_32big(0x3ffec740U));
        }

        WR1_PROG(REG_00F8H, 0x00000003U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_KeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00007501U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xacf022a5U), bswap_32big(0x07c42451U), bswap_32big(0x9f816f4bU),
                       bswap_32big(0x11386d85U));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x000034c5U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00007501U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x60c789abU), bswap_32big(0x8e2031a2U), bswap_32big(0x98ca8558U),
                       bswap_32big(0xc355cdb2U));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0094H, 0x000008e7U);

        for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xf7008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

            WR1_PROG(REG_0000H, 0x01410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x0000a4e0U);
            WR1_PROG(REG_0094H, 0x00000004U);

            r_rsip_func101(bswap_32big(0x9da72476U), bswap_32big(0xff56a61fU), bswap_32big(0xdff477c7U),
                           bswap_32big(0x843912f8U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_0094H, 0x380008e3U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0040H, 0x00402000U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x0be32cddU), bswap_32big(0x341b860dU), bswap_32big(0xd4971ee4U),
                       bswap_32big(0xbe51fb72U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x7c5c0744U), bswap_32big(0x77438172U), bswap_32big(0xc1a0ca04U),
                           bswap_32big(0x6ab6edf0U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
            {
                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0104H, 0x00000000U);
                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0100H, 0x00000080U);

                WR1_PROG(REG_00FCH, 0x00000001U);

                WAIT_STS(REG_0118H, 8, 0);

                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0104H, 0x00000000U);
                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0100H, 0x00000000U);

                WR1_PROG(REG_00FCH, 0x00000100U);

                r_rsip_func101(bswap_32big(0x6e5c33e1U),
                               bswap_32big(0xe49c58f8U),
                               bswap_32big(0x31bf34a5U),
                               bswap_32big(0xc5765540U));
            }
            else
            {
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0104H, InData_MsgLen[0]);
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0100H, InData_MsgLen[1]);

                WR1_PROG(REG_00FCH, 0x00000001U);

                r_rsip_func101(bswap_32big(0x5beb7ff6U),
                               bswap_32big(0xb414cb51U),
                               bswap_32big(0x782e3f68U),
                               bswap_32big(0xcecbdf49U));
            }

            return RSIP_RET_PASS;
        }
    }
}
