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

rsip_ret_t r_rsip_p76f (const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_length[], uint32_t OutData_MAC[])
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

    r_rsip_func100(bswap_32big(0xf2497a01U), bswap_32big(0xe4ab3da0U), bswap_32big(0x0b3bcbe1U), bswap_32big(0x387fffd9U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func100(bswap_32big(0xa89c1bb0U), bswap_32big(0x8f8ab11eU), bswap_32big(0x953619abU), bswap_32big(0x5d34d155U));
        WR1_PROG(REG_00F4H, 0x00000020U);

        WR1_PROG(REG_0008H, 0x00004022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD8_ADDR(REG_002CH, &OutData_MAC[0]);

        r_rsip_func102(bswap_32big(0xbc47f4edU), bswap_32big(0xfcc13ee9U), bswap_32big(0x9cf8de38U), bswap_32big(0x84b1c0c6U));
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

        r_rsip_func100(bswap_32big(0x94596fb3U), bswap_32big(0xf21a2861U), bswap_32big(0x4cbe1c65U), bswap_32big(0xa4b39f2cU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x66f9eb13U), bswap_32big(0x6cd36b74U), bswap_32big(0x650a15c8U), bswap_32big(0x03579a13U));
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

            r_rsip_func100(bswap_32big(0x79f47222U), bswap_32big(0xb9054e70U), bswap_32big(0x970ee086U), bswap_32big(0x3a0bad38U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x39e01276U), bswap_32big(0xd5a9553bU), bswap_32big(0x6df548f2U), bswap_32big(0x3e6d3324U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x830f1f19U), bswap_32big(0xb5909270U), bswap_32big(0xcc95702fU), bswap_32big(0xdcd8670bU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
