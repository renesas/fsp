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

rsip_ret_t r_rsip_p51i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[],
                        const uint32_t InData_Signature[],
                        const uint32_t InData_DomainParam[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00510001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x00000800U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_0014H, 0x000017c5U);
    WR1_PROG(REG_00B0H, 0x00009493U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[4]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[8]);

    WR1_PROG(REG_00B0H, 0x0000949aU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[12]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[16]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[20]);

    WR1_PROG(REG_0014H, 0x00000bc5U);
    WR1_PROG(REG_00B0H, 0x000094a1U);
    WAIT_STS(REG_0014H, 31, 1);
    WR12_ADDR(REG_002CH, &InData_MsgDgst[0]);

    r_rsip_func100(bswap_32big(0x4f58b2ffU),
                   bswap_32big(0xc4517874U),
                   bswap_32big(0xd3f11b18U),
                   bswap_32big(0xdb542c2dU));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x1130dc7aU),
                   bswap_32big(0x8c580281U),
                   bswap_32big(0x94db95ddU),
                   bswap_32big(0x4d2e899aU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c2000a4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    r_rsip_func100(bswap_32big(0x1b92cad8U),
                   bswap_32big(0x177f938dU),
                   bswap_32big(0x678a75cdU),
                   bswap_32big(0x13bb23e2U));
    WR1_PROG(REG_00B0H, 0x000098a1U);

    WR1_PROG(REG_00D4H, 0x00000200U);
    WR1_PROG(REG_00D0H, 0xe7029d07U);
    WR1_PROG(REG_0000H, 0x00430031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001032U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &S_HEAP[0]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &S_HEAP[4]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &S_HEAP[8]);

    r_rsip_func100(bswap_32big(0x2cdac17bU),
                   bswap_32big(0xea4e073fU),
                   bswap_32big(0x7c2e0401U),
                   bswap_32big(0x6c43dd38U));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c000104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_00D0H, 0x09120105U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &S_HEAP[12]);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00005101U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd05c5bf8U),
                   bswap_32big(0xfe3bda79U),
                   bswap_32big(0xf6c6d070U),
                   bswap_32big(0x7a922aefU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000018U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00005101U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x6a525413U),
                   bswap_32big(0xab7e2024U),
                   bswap_32big(0x5956883dU),
                   bswap_32big(0xbcfbde39U));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000044U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000054U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x000017c1U);
    WR1_PROG(REG_00D4H, 0x40000500U);
    WR1_PROG(REG_00D0H, 0xe8008107U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    WR1_PROG(REG_00B0H, 0x0000b4adU);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[13]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[17]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[21]);

    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x07008d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[25]);

    WR1_PROG(REG_00D0H, 0x9c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0xde3e4fe7U),
                   bswap_32big(0x503ee36dU),
                   bswap_32big(0xf3333fa3U),
                   bswap_32big(0x697d670aU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xaeb73c42U), bswap_32big(0x99557010U), bswap_32big(0x59f57164U),
                       bswap_32big(0xe8246615U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000051U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xa209d48fU), bswap_32big(0x03dcb2e8U), bswap_32big(0x3bd9cfdeU),
                       bswap_32big(0x64e0c79fU));
        r_rsip_func029(InData_DomainParam);

        r_rsip_func100(bswap_32big(0x730109adU), bswap_32big(0x2fbff422U), bswap_32big(0x40d22deaU),
                       bswap_32big(0xa8ea354aU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xfeffc477U), bswap_32big(0x51b0f4f9U), bswap_32big(0xb60f7959U),
                           bswap_32big(0xe6e5e27cU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func101(bswap_32big(0xbb74f6a6U), bswap_32big(0x4eb6cbd8U), bswap_32big(0x7cc8cd52U),
                           bswap_32big(0x859721d4U));

            return RSIP_RET_PASS;
        }
    }
}
