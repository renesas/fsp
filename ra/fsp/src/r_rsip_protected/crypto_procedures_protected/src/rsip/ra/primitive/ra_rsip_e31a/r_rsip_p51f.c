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

rsip_ret_t r_rsip_p51f (uint32_t OutData_EncCertificateInfo[])
{
    WR1_PROG(REG_0014H, 0x00000bc1U);
    WR1_PROG(REG_00D4H, 0x00000200U);
    WR1_PROG(REG_00D0H, 0xf7029d07U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &S_HEAP[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &S_HEAP[4]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &S_HEAP[8]);

    WR1_PROG(REG_00B0H, 0x000094a1U);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x07020d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &S_HEAP[12]);

    WR1_PROG(REG_00D0H, 0x8c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0xfd82d4f5U),
                   bswap_32big(0xf5b66892U),
                   bswap_32big(0x9f4ec2edU),
                   bswap_32big(0x83637324U));
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
    WR1_PROG(REG_002CH, bswap_32big(0x00005102U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x4fae6a23U),
                   bswap_32big(0x641cc3b1U),
                   bswap_32big(0x91ca7a39U),
                   bswap_32big(0x34f5f8eaU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x01f6c222U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00005102U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd4e127a4U),
                   bswap_32big(0x78812f8cU),
                   bswap_32big(0x2d679f50U),
                   bswap_32big(0x2df80b58U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xfe039474U),
                   bswap_32big(0x7d24ebc6U),
                   bswap_32big(0xf2d4e012U),
                   bswap_32big(0xa2302adeU));
    WR1_PROG(REG_00B0H, 0x000098a1U);

    WR1_PROG(REG_00D4H, 0x40000200U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    WR1_PROG(REG_0000H, 0x00430031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001032U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[5]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[9]);

    r_rsip_func100(bswap_32big(0x2710a628U),
                   bswap_32big(0xe37d29dcU),
                   bswap_32big(0x866b8e97U),
                   bswap_32big(0x778547e1U));
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
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[13]);

    r_rsip_func100(bswap_32big(0x592dbdc3U),
                   bswap_32big(0xb5c8e716U),
                   bswap_32big(0x1d877095U),
                   bswap_32big(0x2487c2f5U));
    WR1_PROG(REG_009CH, 0x81010000U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &OutData_EncCertificateInfo[0]);

    r_rsip_func102(bswap_32big(0x9590be2bU),
                   bswap_32big(0x224b8e63U),
                   bswap_32big(0xdf524aadU),
                   bswap_32big(0x25d41f3dU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
