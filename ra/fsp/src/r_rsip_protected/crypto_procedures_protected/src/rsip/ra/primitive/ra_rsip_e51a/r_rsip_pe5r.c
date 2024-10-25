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

rsip_ret_t r_rsip_pe5r (const uint32_t InData_KeyType[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e50001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000001c7U);
    WR1_PROG(REG_1608H, 0x800200a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000cc6U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x301c3dd8U), bswap_32big(0x7fd60052U), bswap_32big(0xb48dbf76U), bswap_32big(0x0f5d63aeU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd60edbeeU), bswap_32big(0x7706f80eU), bswap_32big(0xbe5395f3U), bswap_32big(0xc98b4387U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_2000H, 0x00000001U);

        WR1_PROG(REG_2004H, 0x00001050U);

        WR1_PROG(REG_2008H, 0x00000003U);

        WR1_PROG(REG_1600H, 0x38000ca5U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0xd1f2f893U), bswap_32big(0x6e32e546U), bswap_32big(0xe477e54cU), bswap_32big(0xeae2ddc2U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x0000b4a0U);
            WR1_PROG(REG_1600H, 0x0000001bU);

            WR1_PROG(REG_1600H, 0x0000b500U);
            WR1_PROG(REG_1600H, 0x00000008U);

            r_rsip_func101(bswap_32big(0x4e77a4cdU), bswap_32big(0xb14febe3U), bswap_32big(0xb443a13fU), bswap_32big(0xa62f1641U));
        }
        else
        {
            WR1_PROG(REG_1600H, 0x0000b4a0U);
            WR1_PROG(REG_1600H, 0x01b41ce9U);

            WR1_PROG(REG_1600H, 0x0000b500U);
            WR1_PROG(REG_1600H, 0x00000010U);

            r_rsip_func101(bswap_32big(0x8126856cU), bswap_32big(0x95a2022aU), bswap_32big(0x6ab79dafU), bswap_32big(0xd7390c0dU));
        }

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e502U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xcec7b850U), bswap_32big(0x709c9182U), bswap_32big(0x21f1a1a8U), bswap_32big(0x20838db3U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x000034e5U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e502U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x4389585eU), bswap_32big(0xbd0f1b8cU), bswap_32big(0x97d773c4U), bswap_32big(0x42246fbcU));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0xa39fd439U), bswap_32big(0x68871382U), bswap_32big(0xca8af331U), bswap_32big(0x5d89f6b0U));
        WR1_PROG(REG_1608H, 0x81010100U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        WR1_PROG(REG_1600H, 0x00000929U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
            WR1_PROG(REG_1400H, 0x01420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000a520U);
            WR1_PROG(REG_1600H, 0x00000004U);
            r_rsip_func101(bswap_32big(0x2f58d9b8U), bswap_32big(0xc77bcc0eU), bswap_32big(0xcea1b11bU), bswap_32big(0x3125e5cbU));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000909U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x84887498U), bswap_32big(0x81cde991U), bswap_32big(0xf9e94a91U), bswap_32big(0x565e3767U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x98af6c21U), bswap_32big(0xeef21691U), bswap_32big(0x5aba8ebfU), bswap_32big(0x4e04cd03U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, InData_State[18]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, InData_State[19]);

            for (iLoop = 0U; iLoop < 18U; iLoop++)
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2028H, InData_State[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x7b647f3dU), bswap_32big(0xb5488a44U), bswap_32big(0x808092f0U), bswap_32big(0x81a2ae84U));

            return RSIP_RET_PASS;
        }
    }
}
