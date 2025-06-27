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

rsip_ret_t r_rsip_p52f (uint32_t OutData_EncCertificateInfo[])
{
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000052U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x7837c402U),
                   bswap_32big(0x7f93686aU),
                   bswap_32big(0x1794922aU),
                   bswap_32big(0x646f50fdU));
    r_rsip_func103();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00005202U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x4d06f5eaU),
                   bswap_32big(0xb0564afdU),
                   bswap_32big(0xb6e2f911U),
                   bswap_32big(0x69d8d027U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x013a8e02U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00005202U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x556c74cdU),
                   bswap_32big(0x8f7abcefU),
                   bswap_32big(0x27a3d91aU),
                   bswap_32big(0xe12e0bc5U));
    r_rsip_func044();

    WR1_PROG(REG_1600H, 0x00000884U);

    r_rsip_func100(bswap_32big(0xbef22b11U),
                   bswap_32big(0xbecfa02cU),
                   bswap_32big(0x030631f7U),
                   bswap_32big(0x83206983U));
    WR1_PROG(REG_1A2CH, 0x40000200U);
    WR1_PROG(REG_1A24H, 0xe7009d07U);

    WR1_PROG(REG_1608H, 0x81900004U);
    WR1_PROG(REG_1400H, 0x00890031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002032U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_EncCertificateInfo[1]);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_EncCertificateInfo[5]);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_EncCertificateInfo[9]);

    r_rsip_func100(bswap_32big(0xe81f6f37U),
                   bswap_32big(0xc62167beU),
                   bswap_32big(0xe9f99abaU),
                   bswap_32big(0x03f64998U));
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xe7008d05U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_EncCertificateInfo[13]);

    r_rsip_func100(bswap_32big(0x7902fa73U),
                   bswap_32big(0x4b70644dU),
                   bswap_32big(0xa5d8617bU),
                   bswap_32big(0x9faa2747U));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_EncCertificateInfo[17]);

    r_rsip_func100(bswap_32big(0x544f39f7U),
                   bswap_32big(0x9d970e29U),
                   bswap_32big(0xbe204d09U),
                   bswap_32big(0x563157b0U));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_EncCertificateInfo[0]);

    r_rsip_func102(bswap_32big(0x94263f9aU),
                   bswap_32big(0x6d606824U),
                   bswap_32big(0x4d748050U),
                   bswap_32big(0x37f46c6cU));
    WR1_PROG(REG_14B8H, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
