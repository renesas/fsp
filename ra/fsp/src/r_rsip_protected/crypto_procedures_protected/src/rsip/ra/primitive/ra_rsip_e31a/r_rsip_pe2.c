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

rsip_ret_t r_rsip_pe2 (const uint32_t InData_CurveType[],
                       const uint32_t InData_PubKeyType[],
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

    r_rsip_func_sub014(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    r_rsip_func_sub018(0x00000000U, 0x3420a800U, 0x00000002U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000001U);

    r_rsip_func070(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_00B8H, 0x00000005U);

    WR1_PROG(REG_00A4H, 0x04040010U);

    r_rsip_func_sub020(0x20010001U, 0x00000001U);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e201U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x61cd8e17U),
                   bswap_32big(0xcb0760f8U),
                   bswap_32big(0x4f1c6621U),
                   bswap_32big(0x70b1b4bdU));
    r_rsip_func043();

    r_rsip_func074();

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e201U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xec6caadeU),
                   bswap_32big(0xa6b73e6aU),
                   bswap_32big(0xf15c6319U),
                   bswap_32big(0x54879325U));
    r_rsip_func044();

    r_rsip_func_sub011(0x000007c1U, 0x40000100U, 0xf7009d07U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    r_rsip_func_sub009(0x00001432U, 0x00c10021U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

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
        r_rsip_func_sub014(0x000000c7U, 0x80010060U);
        WR1_PROG(REG_002CH, InData_PubKeyType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub016(0x38000c63U, 0x00000080U, 0x00270000U);

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

            r_rsip_func101(bswap_32big(0x5c5f5981U), bswap_32big(0x4a142153U), bswap_32big(0x4decd683U),
                           bswap_32big(0x9f37e783U));
        }
        else
        {
            r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
            WR1_PROG(REG_002CH, InData_PubKey[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e202U, 0x00000000U);

            r_rsip_func101(bswap_32big(0xe6002feeU), bswap_32big(0xc674acbdU), bswap_32big(0x48d61b82U),
                           bswap_32big(0x41f0d4a2U));
            r_rsip_func043();

            r_rsip_func075();

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e202U, 0x00000000U);

            r_rsip_func101(bswap_32big(0x546b7bcbU), bswap_32big(0x373e5395U), bswap_32big(0xe1bc1a33U),
                           bswap_32big(0xee8a2c79U));
            r_rsip_func044();

            r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

            r_rsip_func_sub011(0x00000fc1U, 0x40000300U, 0xe8009107U);
            WR4_ADDR(REG_002CH, &InData_PubKey[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[5]);

            r_rsip_func_sub009(0x0000140fU, 0x00c10021U, 0x00001800U);

            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[9]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[13]);

            r_rsip_func_sub009(0x00001414U, 0x00c10021U, 0x00001800U);

            r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_PubKey[17]);

            r_rsip_func_sub013(0x9c100005U, 0x00410011U);

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
                r_rsip_func101(bswap_32big(0xfb82ec0cU),
                               bswap_32big(0x423e0a16U),
                               bswap_32big(0x82504df7U),
                               bswap_32big(0xa9e9922cU));
            }
        }

        r_rsip_func008();

        r_rsip_func100(bswap_32big(0x908df434U), bswap_32big(0xd0d7d6a2U), bswap_32big(0x5d12500eU),
                       bswap_32big(0xbd08c02aU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x5925df6eU), bswap_32big(0x097d7b89U), bswap_32big(0xf566e677U),
                           bswap_32big(0xaf90188bU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x000000e2U, 0x00000000U);

            r_rsip_func101(bswap_32big(0x4e5b8995U), bswap_32big(0x9125f7b2U), bswap_32big(0x492ff671U),
                           bswap_32big(0x3dacb2d2U));
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

                r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

                r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

                WR1_PROG(REG_0094H, 0x000034c0U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e203U, 0x00000000U);

                r_rsip_func101(bswap_32big(0x01d59e09U),
                               bswap_32big(0x02068c1eU),
                               bswap_32big(0x9ff26827U),
                               bswap_32big(0x9a690832U));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x0000b4c0U);
                WR1_PROG(REG_0094H, 0x015c5d71U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e203U, 0x00000000U);

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

                r_rsip_func_sub004(0x40000100U, 0xe7009d07U, 0x00430021U, 0x00001022U);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[5]);

                r_rsip_func100(bswap_32big(0x7993c8b0U),
                               bswap_32big(0x1b8d45d2U),
                               bswap_32big(0x703280abU),
                               bswap_32big(0xead63f15U));
                r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

                r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[9]);

                r_rsip_func100(bswap_32big(0x3c66653fU),
                               bswap_32big(0x6d4de3ccU),
                               bswap_32big(0xfb79a827U),
                               bswap_32big(0x6d17f45eU));
                r_rsip_func_sub017(0x81010000U, 0x00005006U);
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
