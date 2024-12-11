/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_pf1 (const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f10001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xacc6c487U), bswap_32big(0xfc7898feU), bswap_32big(0x420db758U), bswap_32big(0x15fc4139U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x89967c69U), bswap_32big(0x2a0ba988U), bswap_32big(0x82cc737dU), bswap_32big(0xfcf9dca9U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x3420a800U);
        WR1_PROG(REG_0094H, 0x00000003U);
        WR1_PROG(REG_0094H, 0x2000b400U);
        WR1_PROG(REG_0094H, 0x00000002U);

        WR1_PROG(REG_00A0H, 0x20010000U);
        WR1_PROG(REG_0014H, 0x00000fc5U);
        WR1_PROG(REG_00B0H, 0x00001469U);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_ADDR(REG_002CH, &InData_Signature[0]);

        WR1_PROG(REG_00B0H, 0x0000146eU);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_ADDR(REG_002CH, &InData_Signature[8]);

        WR1_PROG(REG_0014H, 0x000007c5U);
        WR1_PROG(REG_00B0H, 0x00001472U);
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
        WR1_PROG(REG_002CH, bswap_32big(0x000000f1U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x3b259bccU), bswap_32big(0x3c278f61U), bswap_32big(0x86ae98f0U), bswap_32big(0x9dbe8797U));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x00003420U);

        r_rsip_func075();

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000f1U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x554bb8c2U), bswap_32big(0xd7fdb934U), bswap_32big(0x0fd20ad8U), bswap_32big(0xb987abe4U));
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

        r_rsip_func100(bswap_32big(0x06705d4bU), bswap_32big(0x2febcb7bU), bswap_32big(0xb6966c38U), bswap_32big(0x18b81d18U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x3179c095U), bswap_32big(0xc1a7a8ffU), bswap_32big(0xd6fb1ec3U), bswap_32big(0xccf52c3cU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000f1U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x099d6605U), bswap_32big(0x20658a1bU), bswap_32big(0x6a7cec78U), bswap_32big(0x67fc2fadU));
            r_rsip_func073(InData_DomainParam);

            r_rsip_func100(bswap_32big(0xce5616d2U), bswap_32big(0x50744a4bU), bswap_32big(0x2df1a1ceU), bswap_32big(0xb3f425f8U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x11df3615U), bswap_32big(0xedf4ccb3U), bswap_32big(0x69107022U), bswap_32big(0x61587b54U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0xf23c9e8cU), bswap_32big(0xbea15303U), bswap_32big(0xcbbe3e0cU), bswap_32big(0x2d57d208U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
