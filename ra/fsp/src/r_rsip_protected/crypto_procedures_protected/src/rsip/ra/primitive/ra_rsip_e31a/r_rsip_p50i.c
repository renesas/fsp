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

rsip_ret_t r_rsip_p50i (const uint32_t InData_Cmd[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00500001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3000a880U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b480U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000050U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x0f6b6e84U),
                   bswap_32big(0x7cdb5aeeU),
                   bswap_32big(0x9170ec0fU),
                   bswap_32big(0x1862828bU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000050U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x13828a14U),
                   bswap_32big(0xa22b5b13U),
                   bswap_32big(0x54f31e56U),
                   bswap_32big(0x76fa5eb0U));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x000007c1U);
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xf7009d07U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    WR1_PROG(REG_00B0H, 0x00001404U);
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

    r_rsip_func100(bswap_32big(0xd69d80ecU),
                   bswap_32big(0x18ec69a6U),
                   bswap_32big(0x31dd90e2U),
                   bswap_32big(0x1e800d8aU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd8f65b46U), bswap_32big(0x62f4fe49U), bswap_32big(0x90328ef1U),
                       bswap_32big(0xaf966af5U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xe80f781fU), bswap_32big(0x36518168U), bswap_32big(0x4c59466cU),
                       bswap_32big(0x317cc5bfU));
        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            r_rsip_func100(bswap_32big(0xf93d9adfU), bswap_32big(0xf23c2999U), bswap_32big(0x59bd420aU),
                           bswap_32big(0xfac4d203U));

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x7f3564c3U), bswap_32big(0xdf528f0aU), bswap_32big(0xf864d0dcU),
                           bswap_32big(0x1b9e0086U));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x128dca04U), bswap_32big(0xb2db1ca8U), bswap_32big(0x4eeac610U),
                           bswap_32big(0x14928e52U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func100(bswap_32big(0xbc7b2315U), bswap_32big(0xa3ecf2f6U), bswap_32big(0x2b0c261aU),
                           bswap_32big(0xf692bfebU));

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x4cfbda26U), bswap_32big(0x332087d5U), bswap_32big(0x3c4910d0U),
                           bswap_32big(0xe48870dbU));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x5065772dU), bswap_32big(0x9bec8230U), bswap_32big(0xd608bb58U),
                           bswap_32big(0x39ec29b4U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00005001U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x6eafdb3bU), bswap_32big(0x16bbe6afU), bswap_32big(0xe15a4650U),
                           bswap_32big(0xcc14a8adU));
            r_rsip_func510(InData_IVType, InData_IV);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0x50e60d28U), bswap_32big(0xdf26cc40U), bswap_32big(0x633e7881U),
                           bswap_32big(0xf0c4b25dU));
            WR1_PROG(REG_0040H, 0x00400000U);
            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x4006c561U),
                               bswap_32big(0xbeab3db8U),
                               bswap_32big(0x9be9ff1eU),
                               bswap_32big(0x89717556U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_009CH, 0x81840001U);
                WR1_PROG(REG_0000H, 0x00490011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0xfad50d98U),
                               bswap_32big(0x0a4d8ae0U),
                               bswap_32big(0x29be0126U),
                               bswap_32big(0x81eceb46U));
                WR1_PROG(REG_00D0H, 0x08000085U);
                WR1_PROG(REG_00B0H, 0x00001804U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0x4e6d1137U),
                               bswap_32big(0x0b8f4155U),
                               bswap_32big(0x3a4959faU),
                               bswap_32big(0x55e2d44bU));
                WR1_PROG(REG_00D0H, 0x08000095U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0x6b8636ebU),
                               bswap_32big(0x18f88020U),
                               bswap_32big(0x5985b544U),
                               bswap_32big(0xf4145e8fU));
            }
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00005002U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa7d9f4f2U), bswap_32big(0x69ffe0bfU), bswap_32big(0x7bf8078dU),
                           bswap_32big(0x47667bdcU));
            r_rsip_func510(InData_IVType, InData_IV);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A70000U);

            r_rsip_func100(bswap_32big(0xe93ff004U), bswap_32big(0xf2355d57U), bswap_32big(0x0fcf85baU),
                           bswap_32big(0x26a67a46U));
            WR1_PROG(REG_0040H, 0x00400000U);
            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x58b0b328U),
                               bswap_32big(0x60828308U),
                               bswap_32big(0xfde95b2eU),
                               bswap_32big(0xb5a9fb9aU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x00000010U);
                WR1_PROG(REG_009CH, 0x81840001U);
                WR1_PROG(REG_0000H, 0x00490011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0x0b1b44adU),
                               bswap_32big(0xbbb2646dU),
                               bswap_32big(0x2a815396U),
                               bswap_32big(0x80f2bf99U));
                WR1_PROG(REG_00D0H, 0x08000085U);
                WR1_PROG(REG_00B0H, 0x00001804U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func100(bswap_32big(0x001f98ceU),
                               bswap_32big(0x4af92fd3U),
                               bswap_32big(0xcc878fe6U),
                               bswap_32big(0x99eb84c1U));
                WR1_PROG(REG_00D0H, 0x08000095U);
                WR1_PROG(REG_0000H, 0x00430011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0x80721240U),
                               bswap_32big(0x3c2c59b1U),
                               bswap_32big(0x4cadc40aU),
                               bswap_32big(0x6e5254aaU));
            }
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            r_rsip_func100(bswap_32big(0x265bee74U), bswap_32big(0xe025077cU), bswap_32big(0x473c9fd5U),
                           bswap_32big(0x34594b33U));
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x40e3ea4bU), bswap_32big(0xd71a95b7U), bswap_32big(0x792d40feU),
                           bswap_32big(0xdb3dc480U));
            WR1_PROG(REG_00D0H, 0x08000095U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x22a1e5e3U), bswap_32big(0xed8547c3U), bswap_32big(0x431fba48U),
                           bswap_32big(0xa8d7f4c4U));
        }
        else
        {
        }

        return RSIP_RET_PASS;
    }
}
