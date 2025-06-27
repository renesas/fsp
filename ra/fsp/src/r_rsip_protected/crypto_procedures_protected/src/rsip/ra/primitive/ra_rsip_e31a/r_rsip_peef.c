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

rsip_ret_t r_rsip_peef (uint32_t OutData_EncCertificateInfo[])
{
    r_rsip_func100(bswap_32big(0xec4bb937U),
                   bswap_32big(0xe8062b64U),
                   bswap_32big(0xeb4b98a8U),
                   bswap_32big(0x6dd96185U));
    r_rsip_func103();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_009CH, 0x80010000U);
    WR1_PROG(REG_0000H, 0x03410005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0000H, 0x0001000dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x000034c0U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000ee02U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xe8bec482U),
                   bswap_32big(0x81f81af2U),
                   bswap_32big(0x6912d4c2U),
                   bswap_32big(0xcb51f10bU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x010f6caaU);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000ee02U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd534c3e8U),
                   bswap_32big(0x7b324fd2U),
                   bswap_32big(0x76282dcbU),
                   bswap_32big(0x96a72442U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x85af574cU),
                   bswap_32big(0x0414bc7eU),
                   bswap_32big(0xf8913c32U),
                   bswap_32big(0x56c08b48U));
    WR1_PROG(REG_00B0H, 0x0000187eU);

    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    WR1_PROG(REG_0000H, 0x00430021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[5]);

    r_rsip_func100(bswap_32big(0x41a862a8U),
                   bswap_32big(0xf2aa4d10U),
                   bswap_32big(0xa852b29bU),
                   bswap_32big(0x6a79304cU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c000104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x09108105U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[9]);

    r_rsip_func100(bswap_32big(0x2ff7d652U),
                   bswap_32big(0xe62ae6c2U),
                   bswap_32big(0xa61a75b3U),
                   bswap_32big(0xb1863f3eU));
    WR1_PROG(REG_009CH, 0x81010000U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &OutData_EncCertificateInfo[0]);

    r_rsip_func102(bswap_32big(0x62e501aeU),
                   bswap_32big(0xa1f30a66U),
                   bswap_32big(0xacd55e6dU),
                   bswap_32big(0x6f022925U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
