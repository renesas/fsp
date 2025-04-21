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

rsip_ret_t r_rsip_p76f (const uint32_t InData_Cmd[],
                        const uint32_t InData_MAC[],
                        const uint32_t InData_length[],
                        uint32_t       OutData_MAC[])
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
    WR8_PROG(REG_002CH, bswap_32big(0x6a09e667U),
                        bswap_32big(0xbb67ae85U),
                        bswap_32big(0x3c6ef372U),
                        bswap_32big(0xa54ff53aU),
                        bswap_32big(0x510e527fU),
                        bswap_32big(0x9b05688cU),
                        bswap_32big(0x1f83d9abU),
                        bswap_32big(0x5be0cd19U));

    WR1_PROG(REG_00F4H, 0x00000011U);

    r_rsip_func002();

    WR1_PROG(REG_00B0H, 0x00001804U);
    WR1_PROG(REG_0000H, 0x01430021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000000a4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x80000000U));

    WR1_PROG(REG_0000H, 0x01400015U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000001a4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR2_PROG(REG_002CH, bswap_32big(0x00000000U), bswap_32big(0x00000300U));

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

    r_rsip_func100(bswap_32big(0x5ff0f3cbU), bswap_32big(0x27d769edU), bswap_32big(0x18253243U), bswap_32big(0xdb3b807cU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func100(bswap_32big(0x2e009a66U), bswap_32big(0xcb2eece3U), bswap_32big(0x9581a4f6U), bswap_32big(0xe5517513U));
        WR1_PROG(REG_00F4H, 0x00000020U);

        WR1_PROG(REG_0008H, 0x00004022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD8_ADDR(REG_002CH, &OutData_MAC[0]);

        r_rsip_func102(bswap_32big(0x17bf677aU), bswap_32big(0x4143d1f5U), bswap_32big(0x57a194d2U), bswap_32big(0x327e1535U));
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
        WR1_PROG(REG_0094H, 0x00000021U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x47771130U), bswap_32big(0xc4190b65U), bswap_32big(0xb08332d3U), bswap_32big(0xe7e805c8U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xa5f4848eU), bswap_32big(0x21eaf485U), bswap_32big(0xbd3e3b66U), bswap_32big(0x104a9721U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0094H, 0x00000842U);
            WR1_PROG(REG_009CH, 0x80880002U);

            WR1_PROG(REG_00F4H, 0x00000020U);

            WR1_PROG(REG_0000H, 0x03450021U);
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

            WR1_PROG(REG_0014H, 0x000007c1U);
            WR1_PROG(REG_00D0H, 0x9c000005U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_MAC[0]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_MAC[4]);

            r_rsip_func100(bswap_32big(0xc61146ceU), bswap_32big(0xbf1317fdU), bswap_32big(0x0c533296U), bswap_32big(0x1209404aU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xd8920dd9U), bswap_32big(0x2075257dU), bswap_32big(0x7c4e5ff7U), bswap_32big(0x826913f0U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x4aa2bb91U), bswap_32big(0x170a54a3U), bswap_32big(0x5a45fdf1U), bswap_32big(0xf530f647U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
