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

rsip_ret_t r_rsip_p4e (const uint32_t InData_PubKeyType[],
                       const uint32_t InData_PubKey[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_EncSecret[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x004e0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x00010000U);

    WR1_PROG(REG_0094H, 0x00000800U);

    r_rsip_func027(InData_DomainParam);

    WR1_PROG(REG_00B8H, 0x00000007U);

    WR1_PROG(REG_00A4H, 0x06060010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00004e01U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x44d72765U),
                   bswap_32big(0x4d85caccU),
                   bswap_32big(0xe351dfa8U),
                   bswap_32big(0x5642464bU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000019U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00004e01U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xde48a66eU),
                   bswap_32big(0x20cd7f03U),
                   bswap_32big(0xed103cbeU),
                   bswap_32big(0x0ae14dd3U));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x00000bc1U);
    WR1_PROG(REG_00D4H, 0x40000200U);
    WR1_PROG(REG_00D0H, 0xf7009d07U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    WR1_PROG(REG_00B0H, 0x00009446U);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x07008d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[13]);

    WR1_PROG(REG_00D0H, 0x9c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0xe7dc83e7U),
                   bswap_32big(0xba25cb52U),
                   bswap_32big(0xd5c4e858U),
                   bswap_32big(0x9decf68cU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x1f3f595dU), bswap_32big(0xb39a9ca5U), bswap_32big(0x00ba165eU),
                       bswap_32big(0xb1d415f4U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010060U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_PubKeyType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x38000c63U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0xc12e89e6U), bswap_32big(0x7c5ed210U), bswap_32big(0x16df0fe9U),
                       bswap_32big(0xd98f00acU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000017c5U);
            WR1_PROG(REG_00B0H, 0x00009415U);
            WAIT_STS(REG_0014H, 31, 1);
            WR12_ADDR(REG_002CH, &InData_PubKey[0]);

            WR1_PROG(REG_00B0H, 0x0000941cU);
            WAIT_STS(REG_0014H, 31, 1);
            WR12_ADDR(REG_002CH, &InData_PubKey[12]);

            r_rsip_func101(bswap_32big(0x56205f3fU), bswap_32big(0x01948b7bU), bswap_32big(0x7d016639U),
                           bswap_32big(0xd4112d67U));
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_PubKey[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00004e02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xc9095cf6U), bswap_32big(0x81998052U), bswap_32big(0x561c18b1U),
                           bswap_32big(0x74a3107eU));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x00000018U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00004e02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xbb951bffU), bswap_32big(0xf76acf26U), bswap_32big(0x489f6f5bU),
                           bswap_32big(0xae68b1e2U));
            r_rsip_func044();

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000044U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x000017c1U);
            WR1_PROG(REG_00D4H, 0x40000500U);
            WR1_PROG(REG_00D0H, 0xe8009107U);

            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[5]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[9]);

            WR1_PROG(REG_00B0H, 0x00009415U);
            WR1_PROG(REG_0000H, 0x00c10031U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[13]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[17]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[21]);

            WR1_PROG(REG_00B0H, 0x0000941cU);
            WR1_PROG(REG_0000H, 0x00c10031U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[25]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x27ccc9d9U), bswap_32big(0x1abb3c76U), bswap_32big(0xfd2ce282U),
                           bswap_32big(0xe61d2177U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x0adbeb65U),
                               bswap_32big(0x1e2b70a2U),
                               bswap_32big(0xecd237ddU),
                               bswap_32big(0xfc32159bU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xa75442b5U),
                               bswap_32big(0x571c1a7bU),
                               bswap_32big(0xcb241593U),
                               bswap_32big(0x9e7d4c63U));
            }
        }

        WR1_PROG(REG_00B4H, 0x004d0015U);
        WR1_PROG(REG_00B8H, 0x00230007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x004d001cU);
        WR1_PROG(REG_00B8H, 0x002a0007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00230023U);
        WR1_PROG(REG_00B8H, 0x00150007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00850015U);
        WR1_PROG(REG_00B8H, 0x001c0007U);

        WR1_PROG(REG_00A4H, 0x06060005U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x0023001cU);
        WR1_PROG(REG_00B8H, 0x00150007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x008c0015U);
        WR1_PROG(REG_00B8H, 0x001c0007U);

        WR1_PROG(REG_00A4H, 0x06060005U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x002a002aU);
        WR1_PROG(REG_00B8H, 0x00150007U);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x001c0015U);
        WR1_PROG(REG_00B8H, 0x00310000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        WR1_PROG(REG_00B4H, 0x0015001cU);
        WR1_PROG(REG_00B8H, 0x00310000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x06a7db75U), bswap_32big(0x7abd15c6U), bswap_32big(0xe87c164aU),
                       bswap_32big(0x7b4138d7U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x396972fcU), bswap_32big(0xaa342138U), bswap_32big(0xaa9b724dU),
                           bswap_32big(0xc001ffdfU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000004eU));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x4f92ea70U), bswap_32big(0xfc56d0ccU), bswap_32big(0x3a67a75eU),
                           bswap_32big(0x4e5ba7a2U));
            r_rsip_func089();

            r_rsip_func100(bswap_32big(0xad2cb81cU), bswap_32big(0x67c7b1d6U), bswap_32big(0x41cf3d39U),
                           bswap_32big(0xd20b045eU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xa4531e35U),
                               bswap_32big(0xcc3855b1U),
                               bswap_32big(0xc2c81c61U),
                               bswap_32big(0x7bf2d44eU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xe0d3120aU),
                               bswap_32big(0xf9bf0e64U),
                               bswap_32big(0x1015145cU),
                               bswap_32big(0x69b1c7edU));
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
                WR1_PROG(REG_002CH, bswap_32big(0x00004e03U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x6d9c3c71U),
                               bswap_32big(0x919381c7U),
                               bswap_32big(0x0f46ea3bU),
                               bswap_32big(0x1a73dd00U));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x0000b4c0U);
                WR1_PROG(REG_0094H, 0x0165e3d8U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00004e03U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x073a1a0aU),
                               bswap_32big(0x1fa0acf7U),
                               bswap_32big(0x01fa3145U),
                               bswap_32big(0x75a2d08cU));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0x04cac0e6U),
                               bswap_32big(0x08d035f7U),
                               bswap_32big(0xd5b4c498U),
                               bswap_32big(0x0e8fa1beU));
                WR1_PROG(REG_00B0H, 0x00009838U);

                WR1_PROG(REG_00D4H, 0x40000200U);
                WR1_PROG(REG_00D0H, 0xe7009d07U);
                WR1_PROG(REG_0000H, 0x00430031U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0008H, 0x00001032U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[5]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[9]);

                r_rsip_func100(bswap_32big(0x152ec865U),
                               bswap_32big(0x56a56499U),
                               bswap_32big(0x4092aeffU),
                               bswap_32big(0xfbca4362U));
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
                RD4_ADDR(REG_002CH, &OutData_EncSecret[13]);

                r_rsip_func100(bswap_32big(0xce730911U),
                               bswap_32big(0xd387c461U),
                               bswap_32big(0x7d5eb719U),
                               bswap_32big(0xded8e8c4U));
                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_EncSecret[0]);

                r_rsip_func102(bswap_32big(0xb0cad132U),
                               bswap_32big(0xef580084U),
                               bswap_32big(0xdfb1542bU),
                               bswap_32big(0x66298457U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
