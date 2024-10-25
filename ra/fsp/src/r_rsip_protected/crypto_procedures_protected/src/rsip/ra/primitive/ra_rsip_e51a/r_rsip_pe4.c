/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_pe4 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e40001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x6bf5f407U), bswap_32big(0xb57b3b67U), bswap_32big(0xeda1a478U), bswap_32big(0x554b4a62U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x861075e7U), bswap_32big(0x8229ff95U), bswap_32big(0x886c60cfU), bswap_32big(0xd123212cU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_EncSecret[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e401U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x9fa6647cU), bswap_32big(0x63e4aa8fU), bswap_32big(0x432f2600U), bswap_32big(0x64930009U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x015c5d71U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e401U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x4e7199cfU), bswap_32big(0x3c6c3c8fU), bswap_32big(0xa43bdef7U), bswap_32big(0x1518d54fU));
        r_rsip_func044();

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);

        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncSecret[1]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncSecret[5]);

        WR1_PROG(REG_1600H, 0x000008a5U);
        WR1_PROG(REG_1608H, 0x80880005U);
        WR1_PROG(REG_1400H, 0x03420021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncSecret[9]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0xacfe7a4aU), bswap_32big(0xc13c7889U), bswap_32big(0x93597d89U), bswap_32big(0x31d034e8U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x5bdd4513U), bswap_32big(0x33b9e4e8U), bswap_32big(0x9f24542fU), bswap_32big(0xe2462159U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x46b7b068U), bswap_32big(0xea6a1f8dU), bswap_32big(0x55cadce6U), bswap_32big(0xc11a7903U));
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
            WR1_PROG(REG_1420H, bswap_32big(0x0000e402U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x0fb85a35U), bswap_32big(0xf70c169fU), bswap_32big(0x06899cbdU), bswap_32big(0x91e75d18U));
            r_rsip_func043();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x01b41ce9U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000e402U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa5cee12bU), bswap_32big(0xa7d7ef58U), bswap_32big(0xff8402f5U), bswap_32big(0x56ca293eU));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0x5dbe422bU), bswap_32big(0x84e55c0fU), bswap_32big(0x3934304dU), bswap_32big(0x325f12d0U));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7009d07U);
            WR1_PROG(REG_1608H, 0x81880005U);
            WR1_PROG(REG_1400H, 0x00890021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

            r_rsip_func100(bswap_32big(0x45c6cd04U), bswap_32big(0x1625adc5U), bswap_32big(0xc88f573aU), bswap_32big(0xce867483U));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7008d07U);
            WR1_PROG(REG_1400H, 0x00800021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_KeyIndex[9]);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_KeyIndex[13]);

            r_rsip_func100(bswap_32big(0x27aa6855U), bswap_32big(0x12a07ad3U), bswap_32big(0x19d6eaf3U), bswap_32big(0xf7bcc270U));
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
            RD4_ADDR(REG_1420H, &OutData_KeyIndex[17]);

            r_rsip_func100(bswap_32big(0x3a49d3d0U), bswap_32big(0xaf470d93U), bswap_32big(0x591ec768U), bswap_32big(0x5b5dbe84U));
            WR1_PROG(REG_1608H, 0x81010000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

            r_rsip_func102(bswap_32big(0x0b5743c3U), bswap_32big(0x989ed8b3U), bswap_32big(0xbc687707U), bswap_32big(0x994a88c0U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
