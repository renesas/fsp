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

rsip_ret_t r_rsip_p47i (const uint32_t InData_Cmd[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00470001U);
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
    WR1_PROG(REG_002CH, bswap_32big(0x00000047U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x350eb036U),
                   bswap_32big(0x82ea0e3aU),
                   bswap_32big(0x94ee55a9U),
                   bswap_32big(0x7e8eb9c6U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000005U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000047U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x576fa2efU),
                   bswap_32big(0x8b548ebbU),
                   bswap_32big(0x4e309dc4U),
                   bswap_32big(0xeefa7565U));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0xf7009d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);

    WR1_PROG(REG_00B0H, 0x00000401U);
    WR1_PROG(REG_0000H, 0x00c10009U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_00B0H, 0x00000402U);
    WR1_PROG(REG_0000H, 0x00c10009U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x07008d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

    WR1_PROG(REG_00D0H, 0x9c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x4e629e67U),
                   bswap_32big(0x2018830dU),
                   bswap_32big(0x95197cf7U),
                   bswap_32big(0x24992562U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe37ba155U), bswap_32big(0x8ade7c9bU), bswap_32big(0xa86f6b62U),
                       bswap_32big(0xa59f8ba5U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x713f2fddU), bswap_32big(0x0df49ca1U), bswap_32big(0x2419c1d0U),
                       bswap_32big(0x5b64d8e3U));
        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            r_rsip_func100(bswap_32big(0x3e5802f7U), bswap_32big(0x7634eed2U), bswap_32big(0x027011a7U),
                           bswap_32big(0x303892a9U));

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00000801U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000802U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x30b7e661U), bswap_32big(0xce60137dU), bswap_32big(0xe1467aa6U),
                           bswap_32big(0xd89f8b34U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func100(bswap_32big(0xff6c365eU), bswap_32big(0x8b31d7cdU), bswap_32big(0x26330f45U),
                           bswap_32big(0x823d2930U));

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00000801U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000802U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x58bf1dcfU), bswap_32big(0x13de17a7U), bswap_32big(0xb6f99bd8U),
                           bswap_32big(0x48e74862U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00004701U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xbcc4375aU), bswap_32big(0x0c764644U), bswap_32big(0x5c30d434U),
                           bswap_32big(0xf44dff3eU));
            r_rsip_func510(InData_IVType, InData_IV);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x262c1920U), bswap_32big(0xd962c02cU), bswap_32big(0x6d221b39U),
                           bswap_32big(0xae927439U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);
            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xf2ac1f1bU),
                               bswap_32big(0xaa137f36U),
                               bswap_32big(0x7b774634U),
                               bswap_32big(0x49c337c5U));
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

                r_rsip_func100(bswap_32big(0x7859ad37U),
                               bswap_32big(0x51e4fceaU),
                               bswap_32big(0x2187829eU),
                               bswap_32big(0x3daa36dbU));
                WR1_PROG(REG_00D0H, 0x08000085U);
                WR1_PROG(REG_00B0H, 0x00000801U);
                WR1_PROG(REG_0000H, 0x00430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00000802U);
                WR1_PROG(REG_0000H, 0x00430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0xf6d50b74U),
                               bswap_32big(0xdf6c89fbU),
                               bswap_32big(0xdac35f49U),
                               bswap_32big(0x7d5ad896U));
            }
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00004702U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x92d529a2U), bswap_32big(0xbb9d3138U), bswap_32big(0xae2f1ebaU),
                           bswap_32big(0x7e297c2bU));
            r_rsip_func510(InData_IVType, InData_IV);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0xa306aad9U), bswap_32big(0xb46837edU), bswap_32big(0xc34f05b1U),
                           bswap_32big(0xf60ea4f0U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);
            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x65cf9004U),
                               bswap_32big(0x1d672c5aU),
                               bswap_32big(0x6a5b967fU),
                               bswap_32big(0xf12bf64eU));
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

                r_rsip_func100(bswap_32big(0xece51200U),
                               bswap_32big(0xc0d1d56eU),
                               bswap_32big(0x2879a47eU),
                               bswap_32big(0x42d1f9edU));
                WR1_PROG(REG_00D0H, 0x08000085U);
                WR1_PROG(REG_00B0H, 0x00000801U);
                WR1_PROG(REG_0000H, 0x00430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00000802U);
                WR1_PROG(REG_0000H, 0x00430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0x9ce42461U),
                               bswap_32big(0xc0dee97fU),
                               bswap_32big(0xb0095eadU),
                               bswap_32big(0x8a21c6edU));
            }
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            r_rsip_func100(bswap_32big(0xf36745e1U), bswap_32big(0xe8001660U), bswap_32big(0x998349e8U),
                           bswap_32big(0x7f3188f0U));
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            WR1_PROG(REG_00D0H, 0x08000085U);
            WR1_PROG(REG_00B0H, 0x00000801U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00B0H, 0x00000802U);
            WR1_PROG(REG_0000H, 0x00430009U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func101(bswap_32big(0x5476ef27U), bswap_32big(0xae373dabU), bswap_32big(0x8d384f0dU),
                           bswap_32big(0x4553e3e9U));
        }
        else
        {
        }

        return RSIP_RET_PASS;
    }
}
