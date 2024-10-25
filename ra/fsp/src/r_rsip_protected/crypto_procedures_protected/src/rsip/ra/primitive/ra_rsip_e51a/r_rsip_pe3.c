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

rsip_ret_t r_rsip_pe3 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[])
{
    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e30001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x620e8062U), bswap_32big(0x5d616facU), bswap_32big(0x7a62781cU), bswap_32big(0x95cbc949U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x66e74fedU), bswap_32big(0x487dc59bU), bswap_32big(0x88b7a33dU), bswap_32big(0x3080a1aaU));
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
        WR1_PROG(REG_1420H, bswap_32big(0x0000e301U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x0f036b17U), bswap_32big(0x8c82e0fcU), bswap_32big(0x3f646db9U), bswap_32big(0xb05271e1U));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x015c5d71U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e301U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x1d066cb5U), bswap_32big(0xc9fcb0d1U), bswap_32big(0xf5d0bbc7U), bswap_32big(0x9d9d3bbdU));
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

        r_rsip_func100(bswap_32big(0xd3c7526bU), bswap_32big(0x378681a0U), bswap_32big(0xd83b574cU), bswap_32big(0x0c35b436U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x615e16c0U), bswap_32big(0x804140f5U), bswap_32big(0x44696820U), bswap_32big(0x8d90854cU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x30a9f548U), bswap_32big(0x714b3ee9U), bswap_32big(0x09bc67bbU), bswap_32big(0x148bad08U));
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
            WR1_PROG(REG_1420H, bswap_32big(0x0000e302U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x1a8f606bU), bswap_32big(0x3afac85aU), bswap_32big(0xee2f9234U), bswap_32big(0xfc83a67dU));
            r_rsip_func043();

            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1600H, 0x01799093U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000e302U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x721b6d21U), bswap_32big(0x86c5e511U), bswap_32big(0x7fcd996aU), bswap_32big(0x4c1abbb6U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0x7b0f426eU), bswap_32big(0xf7f8c578U), bswap_32big(0xb3137588U), bswap_32big(0xc43c9363U));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7009d07U);
            WR1_PROG(REG_1608H, 0x81880005U);
            WR1_PROG(REG_1400H, 0x00890021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_EncMsg[1]);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_EncMsg[5]);

            r_rsip_func100(bswap_32big(0x5ac47c94U), bswap_32big(0xbb930acfU), bswap_32big(0x1facfb02U), bswap_32big(0x5ab38679U));
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
            RD4_ADDR(REG_1420H, &OutData_EncMsg[9]);

            r_rsip_func100(bswap_32big(0x8b4eec05U), bswap_32big(0x750fc80aU), bswap_32big(0x56a027b7U), bswap_32big(0x66303af2U));
            WR1_PROG(REG_1608H, 0x81010000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[0]);

            r_rsip_func102(bswap_32big(0xb8a0f61aU), bswap_32big(0x296a1ef7U), bswap_32big(0x737b09d1U), bswap_32big(0x722792e5U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
