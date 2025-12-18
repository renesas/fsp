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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

rsip_ret_t r_rsip_p51f (uint32_t OutData_EncCertificateInfo[])
{
    r_rsip_func_sub011(0x00000bc1U, 0x00000200U, 0xf7029d07U);
    WR4_ADDR(REG_002CH, &S_HEAP[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &S_HEAP[4]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &S_HEAP[8]);

    r_rsip_func_sub009(0x000094a1U, 0x00c10031U, 0x00001800U);

    r_rsip_func_sub019(0x000003c1U, 0x07020d05U);
    WR4_ADDR(REG_002CH, &S_HEAP[12]);

    r_rsip_func_sub013(0x8c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0xfd82d4f5U),
                   bswap_32big(0xf5b66892U),
                   bswap_32big(0x9f4ec2edU),
                   bswap_32big(0x83637324U));
    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00005102U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x4fae6a23U),
                   bswap_32big(0x641cc3b1U),
                   bswap_32big(0x91ca7a39U),
                   bswap_32big(0x34f5f8eaU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x01f6c222U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00005102U, 0x00000000U);

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

    r_rsip_func_sub004(0x40000200U, 0xe7009d07U, 0x00430031U, 0x00001032U);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[5]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[9]);

    r_rsip_func100(bswap_32big(0x2710a628U),
                   bswap_32big(0xe37d29dcU),
                   bswap_32big(0x866b8e97U),
                   bswap_32big(0x778547e1U));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_EncCertificateInfo[13]);

    r_rsip_func100(bswap_32big(0x592dbdc3U),
                   bswap_32big(0xb5c8e716U),
                   bswap_32big(0x1d877095U),
                   bswap_32big(0x2487c2f5U));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_EncCertificateInfo[0]);

    r_rsip_func102(bswap_32big(0x9590be2bU),
                   bswap_32big(0x224b8e63U),
                   bswap_32big(0xdf524aadU),
                   bswap_32big(0x25d41f3dU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
