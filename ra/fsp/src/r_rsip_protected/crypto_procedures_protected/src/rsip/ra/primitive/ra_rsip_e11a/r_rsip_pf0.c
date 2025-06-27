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

rsip_ret_t r_rsip_pf0 (const uint32_t InData_CurveType[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_Signature[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f00001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);

    r_rsip_func070(InData_DomainParam);

    r_rsip_func100(bswap_32big(0x686deac7U),
                   bswap_32big(0x709b2a28U),
                   bswap_32big(0xbcc50a35U),
                   bswap_32big(0xdd4c2688U));

    WR1_PROG(REG_00B0H, 0x0000140fU);
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x2867ed39U),
                   bswap_32big(0x3356f188U),
                   bswap_32big(0x8e378447U),
                   bswap_32big(0x9aaf3b9eU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00001428U);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B0H, 0x00001419U);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

    WR1_PROG(REG_00B4H, 0x0019000aU);
    WR1_PROG(REG_00B8H, 0x00140000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B8H, 0x00000014U);

    WR1_PROG(REG_00A4H, 0x04040010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028000fU);
    WR1_PROG(REG_00B8H, 0x002d0014U);

    WR1_PROG(REG_00A4H, 0x04040002U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028002dU);
    WR1_PROG(REG_00B8H, 0x00320000U);

    WR1_PROG(REG_00A4H, 0x04040009U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    r_rsip_func071(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000f0U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xbba9725fU),
                   bswap_32big(0x37f58e4fU),
                   bswap_32big(0x806ac6acU),
                   bswap_32big(0x3bcfd5faU));
    r_rsip_func088();

    r_rsip_func100(bswap_32big(0x428c2e0dU),
                   bswap_32big(0x5da1d275U),
                   bswap_32big(0x1f07e4f7U),
                   bswap_32big(0x5ce8df37U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xc3fd2c34U), bswap_32big(0xd266d3fbU), bswap_32big(0xd69f85eaU),
                       bswap_32big(0x412328d3U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_00B8H, 0x0000000aU);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x005a0028U);
        WR1_PROG(REG_00B8H, 0x002d000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0014H, 0x000000a5U);
        WR1_PROG(REG_00B0H, 0x0000140fU);
        WR1_PROG(REG_0000H, 0x00c0001dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x000f002dU);
        WR1_PROG(REG_00B8H, 0x0028000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x000f0028U);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x0d166d6cU), bswap_32big(0xab40d024U), bswap_32big(0x621f1f6dU),
                       bswap_32big(0x7babc156U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xc525800fU), bswap_32big(0x06fe9510U), bswap_32big(0x67968cd5U),
                           bswap_32big(0x025a0febU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xe88d6cd4U), bswap_32big(0xa60c2b1cU), bswap_32big(0x9ba0284cU),
                           bswap_32big(0x88d159c4U));
            WR1_PROG(REG_00B0H, 0x00001414U);
            WR1_PROG(REG_0000H, 0x00c0001dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

            WR1_PROG(REG_00B4H, 0x0014000aU);
            WR1_PROG(REG_00B8H, 0x000f0000U);

            WR1_PROG(REG_00A4H, 0x0404000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B4H, 0x000f0032U);
            WR1_PROG(REG_00B8H, 0x0014000aU);

            WR1_PROG(REG_00A4H, 0x04040000U);
            WR1_PROG(REG_0008H, 0x00020000U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            WR1_PROG(REG_00B4H, 0x005a0014U);
            WR1_PROG(REG_00B8H, 0x000f000aU);

            WR1_PROG(REG_00A4H, 0x04040002U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0014H, 0x000007c5U);
            WR1_PROG(REG_00B0H, 0x00001414U);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_ADDR(REG_002CH, &InData_MsgDgst[0]);

            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_KeyIndex[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000f0U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa3f108cbU), bswap_32big(0xf3d7f527U), bswap_32big(0x70d272a4U),
                           bswap_32big(0x43ac7d78U));
            r_rsip_func043();

            r_rsip_func074();

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000f0U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa4fc1da1U), bswap_32big(0x6159c4f3U), bswap_32big(0xa87b36b4U),
                           bswap_32big(0x6fa51cccU));
            r_rsip_func044();

            WR1_PROG(REG_0014H, 0x000007c1U);
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xf7009d07U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

            WR1_PROG(REG_00B0H, 0x0000141eU);
            WR1_PROG(REG_0000H, 0x00c10021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x1ce19926U), bswap_32big(0x58facef9U), bswap_32big(0x4104ecd6U),
                           bswap_32big(0x2d0afc06U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x727867c3U),
                               bswap_32big(0x7628bc59U),
                               bswap_32big(0x7be7d455U),
                               bswap_32big(0x66fd49d7U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                WR1_PROG(REG_00B4H, 0x005a001eU);
                WR1_PROG(REG_00B8H, 0x0019000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00280019U);
                WR1_PROG(REG_00B8H, 0x001e000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x001e0014U);
                WR1_PROG(REG_00B8H, 0x0019000aU);

                WR1_PROG(REG_00A4H, 0x04040005U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x0019000fU);
                WR1_PROG(REG_00B8H, 0x001e000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000140fU);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x000f001eU);
                WR1_PROG(REG_00B8H, 0x00140000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0x2d150997U),
                               bswap_32big(0x0c0a966cU),
                               bswap_32big(0x5d51785aU),
                               bswap_32big(0x2eda3398U));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0xaa471888U),
                                   bswap_32big(0x23d64989U),
                                   bswap_32big(0x17f48780U),
                                   bswap_32big(0x48100d87U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x1d4ff26dU),
                                   bswap_32big(0x0bb2356dU),
                                   bswap_32big(0x32fc7f83U),
                                   bswap_32big(0x39acd271U));
                    WR1_PROG(REG_00B0H, 0x00001828U);
                    WR1_PROG(REG_0008H, 0x00006022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD8_ADDR(REG_002CH, &OutData_Signature[0]);

                    r_rsip_func100(bswap_32big(0x00402c1cU),
                                   bswap_32big(0x4f01dbe0U),
                                   bswap_32big(0x4e8843cdU),
                                   bswap_32big(0xf9e6dbb3U));
                    WR1_PROG(REG_00B0H, 0x0000181eU);
                    WR1_PROG(REG_0008H, 0x00006022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD8_ADDR(REG_002CH, &OutData_Signature[8]);

                    r_rsip_func102(bswap_32big(0x11f25041U),
                                   bswap_32big(0x3a3f0ac7U),
                                   bswap_32big(0x198686c3U),
                                   bswap_32big(0x99ef44ccU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
