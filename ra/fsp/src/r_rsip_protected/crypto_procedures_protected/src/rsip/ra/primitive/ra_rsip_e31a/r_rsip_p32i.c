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

rsip_ret_t r_rsip_p32i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00320001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000005U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00003201U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc7ad2f27U),
                   bswap_32big(0xfe5c54dfU),
                   bswap_32big(0xfb5e319dU),
                   bswap_32big(0x0d12b1d6U));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x93981702U),
                   bswap_32big(0x85f92f58U),
                   bswap_32big(0xab0daf5aU),
                   bswap_32big(0x9f7084e8U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x5234c713U), bswap_32big(0x2c31ea1dU), bswap_32big(0x3f09dbcdU),
                       bswap_32big(0xf79802fcU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100a0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x38000ca5U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0x90b7b3e3U), bswap_32big(0x5a2100dcU), bswap_32big(0x26de91fbU),
                       bswap_32big(0x03d90f52U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000105U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            WR1_PROG(REG_00B0H, 0x00000401U);
            WR1_PROG(REG_0000H, 0x00c10009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000402U);
            WR1_PROG(REG_0000H, 0x00c10009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x3aa9c96aU), bswap_32big(0x224e8e61U), bswap_32big(0x57cfa3f1U),
                           bswap_32big(0xc2900aa4U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00003202U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x58898b6bU), bswap_32big(0x9ccc22c0U), bswap_32big(0xea493085U),
                           bswap_32big(0x4e8da3b4U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0x244484cdU), bswap_32big(0x751fee21U), bswap_32big(0xa830fdd1U),
                           bswap_32big(0x775a4afeU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x2a2fd1eeU),
                               bswap_32big(0xe65c4409U),
                               bswap_32big(0xbbec79cfU),
                               bswap_32big(0x2c47e6faU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xbff9dc43U),
                               bswap_32big(0x8d9af953U),
                               bswap_32big(0xf318c4b2U),
                               bswap_32big(0xdb281470U));
            }
        }

        r_rsip_func100(bswap_32big(0x5fbd6eb8U), bswap_32big(0x27d6b267U), bswap_32big(0x958624c5U),
                       bswap_32big(0x6bb3d724U));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_009CH, 0x81840000U);
        WR1_PROG(REG_0000H, 0x00490011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_009CH, 0x80840000U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x03430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x87258746U), bswap_32big(0xc4783506U), bswap_32big(0x70bbf430U),
                       bswap_32big(0xc431529aU));
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0a0000a4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0x4db459ffU), bswap_32big(0xf7968416U), bswap_32big(0xc83354acU),
                       bswap_32big(0x3720cdf6U));

        return RSIP_RET_PASS;
    }
}
