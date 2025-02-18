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

rsip_ret_t r_rsip_pdcf (const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_length[], uint32_t OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_00F4H, 0x00000100U);

    WR1_PROG(REG_00F4H, 0x00000020U);

    WR1_PROG(REG_00B0H, 0x00001404U);
    WR1_PROG(REG_0000H, 0x00c50021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00F4H, 0x00000010U);

    WR1_PROG(REG_0014H, 0x000007a4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR8_PROG(REG_002CH, bswap_32big(0xc1059ed8U),
                        bswap_32big(0x367cd507U),
                        bswap_32big(0x3070dd17U),
                        bswap_32big(0xf70e5939U),
                        bswap_32big(0xffc00b31U),
                        bswap_32big(0x68581511U),
                        bswap_32big(0x64f98fa7U),
                        bswap_32big(0xbefa4fa4U));

    WR1_PROG(REG_00F4H, 0x00000011U);

    r_rsip_func002();

    WR1_PROG(REG_00B0H, 0x00001804U);
    WR1_PROG(REG_0000H, 0x0143001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0000H, 0x00030005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000000a4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x80000000U));

    WR1_PROG(REG_0000H, 0x01400019U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000001a4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR2_PROG(REG_002CH, bswap_32big(0x00000000U), bswap_32big(0x000002E0U));

    WAIT_STS(REG_00F8H, 2, 0);

    WR1_PROG(REG_00F4H, 0x00000100U);

    WR1_PROG(REG_0040H, 0x00001600U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0xdb008a80U), bswap_32big(0xf867ca4fU), bswap_32big(0x97ece341U), bswap_32big(0x1078d174U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func100(bswap_32big(0xd98670ceU), bswap_32big(0x88a94255U), bswap_32big(0x2c382732U), bswap_32big(0xd8419c9dU));
        WR1_PROG(REG_00F4H, 0x00000020U);

        WR1_PROG(REG_0008H, 0x0000401eU);
        WAIT_STS(REG_0008H, 30, 1);
        RD7_ADDR(REG_002CH, &OutData_MAC[0]);
        WR1_PROG(REG_0000H, 0x00050005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func102(bswap_32big(0xf30a43a4U), bswap_32big(0x7703dedcU), bswap_32big(0x19a6e878U), bswap_32big(0xf716950aU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010020U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_length[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x3420a820U);
        WR1_PROG(REG_0094H, 0x00000004U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        WR1_PROG(REG_0094H, 0x3420a820U);
        WR1_PROG(REG_0094H, 0x0000001dU);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x7e44a803U), bswap_32big(0x37d1bee3U), bswap_32big(0x5c4da8cbU), bswap_32big(0xaa4acaf8U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x1bf08edbU), bswap_32big(0x3c17652aU), bswap_32big(0x3ca6bb16U), bswap_32big(0x6edbea76U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0094H, 0x00000842U);
            WR1_PROG(REG_009CH, 0x80870002U);

            WR1_PROG(REG_00F4H, 0x00000020U);

            WR1_PROG(REG_0000H, 0x0345001dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0000H, 0x00050005U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x00000800U);
            for (iLoop = 0U; iLoop < 32U; iLoop++)
            {
                WR1_PROG(REG_0094H, 0x3c002841U);
                WR1_PROG(REG_0094H, 0x12003c02U);
                WR1_PROG(REG_0094H, 0x00002c40U);
            }

            WR1_PROG(REG_00D0H, 0x08000045U);
            WR1_PROG(REG_0094H, 0x00000842U);
            WR1_PROG(REG_009CH, 0x81880002U);
            WR1_PROG(REG_0000H, 0x00490011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D0H, 0x08000055U);
            WR1_PROG(REG_0000H, 0x00490011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000006c1U);
            WR1_PROG(REG_00D0H, 0x9c000005U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_MAC[0]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WAIT_STS(REG_0014H, 31, 1);
            WR3_ADDR(REG_002CH, &InData_MAC[4]);
            WR1_PROG(REG_0014H, 0x000000a1U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            r_rsip_func100(bswap_32big(0xdc599725U), bswap_32big(0x007ca6abU), bswap_32big(0x3fbd603cU), bswap_32big(0x6fccfca2U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x194b8b94U), bswap_32big(0xa683588bU), bswap_32big(0xae4a59f6U), bswap_32big(0x62407fb6U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x76a980c2U), bswap_32big(0xdc547b6dU), bswap_32big(0x54b1ec35U), bswap_32big(0x81dd1035U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
