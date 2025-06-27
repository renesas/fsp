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

rsip_ret_t r_rsip_pe2 (const uint32_t InData_PubKeyType[],
                       const uint32_t InData_PubKey[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_EncSecret[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e20001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x00010000U);

    WR1_PROG(REG_0094H, 0x00000800U);

    r_rsip_func070(InData_DomainParam);

    WR1_PROG(REG_00B8H, 0x00000005U);

    WR1_PROG(REG_00A4H, 0x04040010U);

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
    WR1_PROG(REG_002CH, bswap_32big(0x0000e201U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc2e810eeU),
                   bswap_32big(0xeb9ff9a4U),
                   bswap_32big(0x50a58b3eU),
                   bswap_32big(0xeaa36588U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000017U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000e201U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc46b040fU),
                   bswap_32big(0x7e457c65U),
                   bswap_32big(0x521982eeU),
                   bswap_32big(0x8d153622U));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x000007c1U);
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xf7009d07U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    WR1_PROG(REG_00B0H, 0x00001432U);
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

    r_rsip_func100(bswap_32big(0x9e5c7cbdU),
                   bswap_32big(0xf53fae8fU),
                   bswap_32big(0x3396ff5eU),
                   bswap_32big(0xfebf5a76U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x2fd04f93U), bswap_32big(0x583ac9caU), bswap_32big(0xfd47875dU),
                       bswap_32big(0x13d67dcdU));
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

        r_rsip_func100(bswap_32big(0xc8424aceU), bswap_32big(0x269a5d9bU), bswap_32big(0x7a885cb3U),
                       bswap_32big(0x36a3817bU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x00000fc5U);
            WR1_PROG(REG_00B0H, 0x0000140fU);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_ADDR(REG_002CH, &InData_PubKey[0]);

            WR1_PROG(REG_00B0H, 0x00001414U);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_ADDR(REG_002CH, &InData_PubKey[8]);

            r_rsip_func101(bswap_32big(0xcc08d624U), bswap_32big(0x31128036U), bswap_32big(0xc4e34e38U),
                           bswap_32big(0x8a8899deU));
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
            WR1_PROG(REG_002CH, bswap_32big(0x0000e202U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xe6002feeU), bswap_32big(0xc674acbdU), bswap_32big(0x48d61b82U),
                           bswap_32big(0x41f0d4a2U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x00000016U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000e202U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xbd3fee6bU), bswap_32big(0xc9c956fbU), bswap_32big(0x9c764b54U),
                           bswap_32big(0x0273596eU));
            r_rsip_func044();

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000044U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x00000fc1U);
            WR1_PROG(REG_00D4H, 0x40000300U);
            WR1_PROG(REG_00D0H, 0xe8009107U);

            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[5]);

            WR1_PROG(REG_00B0H, 0x0000140fU);
            WR1_PROG(REG_0000H, 0x00c10021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[9]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[13]);

            WR1_PROG(REG_00B0H, 0x00001414U);
            WR1_PROG(REG_0000H, 0x00c10021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[17]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0xe5a01ae5U), bswap_32big(0x5c89bb66U), bswap_32big(0x06bdc215U),
                           bswap_32big(0x995cda27U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xd5a16328U),
                               bswap_32big(0x2f158a32U),
                               bswap_32big(0xe251cb13U),
                               bswap_32big(0x85037851U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xafacb07dU),
                               bswap_32big(0x344c0bcaU),
                               bswap_32big(0x6b6519b6U),
                               bswap_32big(0x6f87b244U));
            }
        }

        r_rsip_func008();

        r_rsip_func100(bswap_32big(0x6ec836aaU), bswap_32big(0xd58d5512U), bswap_32big(0xb5521282U),
                       bswap_32big(0x2bb4cb60U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x86cef836U), bswap_32big(0x15251739U), bswap_32big(0x351090bdU),
                           bswap_32big(0xfdf0996cU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000e2U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x55a7ffdbU), bswap_32big(0x50bda35cU), bswap_32big(0xd5d65cadU),
                           bswap_32big(0xff3bc6c8U));
            r_rsip_func088();

            r_rsip_func100(bswap_32big(0x422686d9U), bswap_32big(0xae95433bU), bswap_32big(0x8b726562U),
                           bswap_32big(0xbf4401f6U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xe9624b2eU),
                               bswap_32big(0xe24cbd49U),
                               bswap_32big(0x606b3a3eU),
                               bswap_32big(0xa0cc72f3U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xbb869832U),
                               bswap_32big(0xaa061383U),
                               bswap_32big(0xddecf058U),
                               bswap_32big(0xfcf7bbd3U));
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
                WR1_PROG(REG_002CH, bswap_32big(0x0000e203U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x01d59e09U),
                               bswap_32big(0x02068c1eU),
                               bswap_32big(0x9ff26827U),
                               bswap_32big(0x9a690832U));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x0000b4c0U);
                WR1_PROG(REG_0094H, 0x015c5d71U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x0000e203U));
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xa6be231dU),
                               bswap_32big(0x4dbe63a1U),
                               bswap_32big(0x6cef52d4U),
                               bswap_32big(0x30f0e674U));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0x08969528U),
                               bswap_32big(0x5be7c99fU),
                               bswap_32big(0x3b22ae41U),
                               bswap_32big(0xb1933a99U));
                WR1_PROG(REG_00B0H, 0x00001828U);

                WR1_PROG(REG_00D4H, 0x40000100U);
                WR1_PROG(REG_00D0H, 0xe7009d07U);
                WR1_PROG(REG_0000H, 0x00430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0008H, 0x00001022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[5]);

                r_rsip_func100(bswap_32big(0x7993c8b0U),
                               bswap_32big(0x1b8d45d2U),
                               bswap_32big(0x703280abU),
                               bswap_32big(0xead63f15U));
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
                RD4_ADDR(REG_002CH, &OutData_EncSecret[9]);

                r_rsip_func100(bswap_32big(0x3c66653fU),
                               bswap_32big(0x6d4de3ccU),
                               bswap_32big(0xfb79a827U),
                               bswap_32big(0x6d17f45eU));
                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_EncSecret[0]);

                r_rsip_func102(bswap_32big(0xba5794a1U),
                               bswap_32big(0xe9b47f1aU),
                               bswap_32big(0x79090a19U),
                               bswap_32big(0xc2a51b35U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
