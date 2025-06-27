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

rsip_ret_t r_rsip_peei (const uint32_t InData_CurveType[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[],
                        const uint32_t InData_Signature[],
                        const uint32_t InData_DomainParam[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00ee0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x00010000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000001U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_0014H, 0x00000fc5U);
    WR1_PROG(REG_00B0H, 0x00001469U);
    WAIT_STS(REG_0014H, 31, 1);
    WR8_ADDR(REG_002CH, &InData_Signature[0]);

    WR1_PROG(REG_00B0H, 0x0000146eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR8_ADDR(REG_002CH, &InData_Signature[8]);

    WR1_PROG(REG_0014H, 0x000007c5U);
    WR1_PROG(REG_00B0H, 0x0000147eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR8_ADDR(REG_002CH, &InData_MsgDgst[0]);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000ee01U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x5bd46a3bU),
                   bswap_32big(0xed6180ccU),
                   bswap_32big(0x57ab2472U),
                   bswap_32big(0x431a940bU));
    r_rsip_func043();

    r_rsip_func075();

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000ee01U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd4b2745cU),
                   bswap_32big(0x5b577134U),
                   bswap_32big(0x69c0b01dU),
                   bswap_32big(0x441df5beU));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000044U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000054U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x00000fc1U);
    WR1_PROG(REG_00D4H, 0x40000300U);
    WR1_PROG(REG_00D0H, 0xe8008107U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    WR1_PROG(REG_00B0H, 0x0000347aU);
    WR1_PROG(REG_0000H, 0x00c10021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[13]);

    WR1_PROG(REG_0000H, 0x00c10021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x07008d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[17]);

    WR1_PROG(REG_00D0H, 0x9c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x06558c39U),
                   bswap_32big(0x900b8f8dU),
                   bswap_32big(0xa6b9d550U),
                   bswap_32big(0xb9a1e785U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x24b7fa68U), bswap_32big(0x899c7b2eU), bswap_32big(0x4e098fd7U),
                       bswap_32big(0x1d1f2267U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000eeU));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x5ac955dfU), bswap_32big(0xd1d57112U), bswap_32big(0x054eb1f2U),
                       bswap_32big(0xb3bbfc44U));
        r_rsip_func073(InData_DomainParam);

        r_rsip_func100(bswap_32big(0x28a93dfaU), bswap_32big(0xff30788eU), bswap_32big(0xa817871dU),
                       bswap_32big(0x28b8c94dU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x32e54adeU), bswap_32big(0x9ee32067U), bswap_32big(0x2f03a32aU),
                           bswap_32big(0x4127fd7dU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func101(bswap_32big(0xa44a86a3U), bswap_32big(0x37b7ed4cU), bswap_32big(0x67e1d061U),
                           bswap_32big(0x3e87b994U));

            return RSIP_RET_PASS;
        }
    }
}
