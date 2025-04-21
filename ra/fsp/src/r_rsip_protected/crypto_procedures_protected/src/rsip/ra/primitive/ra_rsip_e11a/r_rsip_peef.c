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
    r_rsip_func100(bswap_32big(0xa0ad0f3aU),
                   bswap_32big(0x4fb03125U),
                   bswap_32big(0x27640e0cU),
                   bswap_32big(0x1e8ebcfbU));
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

    r_rsip_func101(bswap_32big(0xb37e0905U),
                   bswap_32big(0xe6bb51c8U),
                   bswap_32big(0x4cf85c6cU),
                   bswap_32big(0x18837230U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x010f6caaU);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000ee02U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x65b10fb3U),
                   bswap_32big(0x1f0b72b0U),
                   bswap_32big(0x82fcf3ebU),
                   bswap_32big(0x538da276U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xfb2e9defU),
                   bswap_32big(0xe16db998U),
                   bswap_32big(0x00e0d5b4U),
                   bswap_32big(0x46f3d96dU));
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

    r_rsip_func100(bswap_32big(0x31d90cd8U),
                   bswap_32big(0x361b034cU),
                   bswap_32big(0x536592cbU),
                   bswap_32big(0xbb49c143U));
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

    r_rsip_func100(bswap_32big(0x56e900edU),
                   bswap_32big(0x8e52006dU),
                   bswap_32big(0x6f9b4756U),
                   bswap_32big(0x1743b4afU));
    WR1_PROG(REG_009CH, 0x81010000U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &OutData_EncCertificateInfo[0]);

    r_rsip_func102(bswap_32big(0x83d47976U),
                   bswap_32big(0xd1f38d36U),
                   bswap_32big(0xc67716beU),
                   bswap_32big(0xfc8131e0U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
