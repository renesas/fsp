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

rsip_ret_t r_rsip_pe3 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[])
{
    uint32_t iLoop = 0U;

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

    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x00000080U);

    r_rsip_func100(bswap_32big(0x65274120U),
                   bswap_32big(0x658d6182U),
                   bswap_32big(0xeb90ca22U),
                   bswap_32big(0x2a898c6eU));
    WR1_PROG(REG_1600H, 0x00007c04U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x015c5d71U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000008U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xea78200aU), bswap_32big(0xc6cfce83U), bswap_32big(0x28164f43U),
                       bswap_32big(0xe34ce455U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x0165e3d8U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000000cU));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x18a7d474U), bswap_32big(0xc3e733b8U), bswap_32big(0xb9353527U),
                       bswap_32big(0x6743e1bdU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x01ea2366U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000014U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x57ed0880U), bswap_32big(0xf162c12dU), bswap_32big(0x7ae6233cU),
                       bswap_32big(0x0c695f5aU));
    }

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x000000e3U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x0550f34eU),
                   bswap_32big(0xde7e5fbeU),
                   bswap_32big(0x01c1ea86U),
                   bswap_32big(0x7a2df0f5U));
    r_rsip_func407(InData_EncSecret);

    r_rsip_func100(bswap_32big(0xfb0c75c1U),
                   bswap_32big(0xdae08bd5U),
                   bswap_32big(0xc48096e1U),
                   bswap_32big(0x2c7c7242U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd17ba5a2U), bswap_32big(0xa727a069U), bswap_32big(0xf0bc4b3aU),
                       bswap_32big(0xc7eeb797U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38008880U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0xf2968371U), bswap_32big(0x68420f8bU), bswap_32big(0x252642f3U),
                       bswap_32big(0x96280760U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func408();

            r_rsip_func101(bswap_32big(0x4420f101U), bswap_32big(0x19390d23U), bswap_32big(0x0aecbc76U),
                           bswap_32big(0xebc57852U));
        }

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x000000e3U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe5becfc7U), bswap_32big(0x6be4a5b9U), bswap_32big(0x75a98eeaU),
                       bswap_32big(0xd8c779c2U));
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
        WR1_PROG(REG_1420H, bswap_32big(0x000000e3U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x4cf2df9bU), bswap_32big(0x940f65b0U), bswap_32big(0xd0e669faU),
                       bswap_32big(0x5852a67bU));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x01799093U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x000000e3U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x326fc89eU), bswap_32big(0xe057a14eU), bswap_32big(0x06940d24U),
                       bswap_32big(0x9b9c4bfcU));
        r_rsip_func044();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1600H, 0x000008e7U);

        WR1_PROG(REG_1600H, 0x000008a5U);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            r_rsip_func100(bswap_32big(0x6393feb6U), bswap_32big(0xc2f2d86dU), bswap_32big(0xfac11f66U),
                           bswap_32big(0x173607f8U));
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1608H, 0x81840005U);
            WR1_PROG(REG_1400H, 0x00890011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_EncMsg[iLoop + 1]);

            WR1_PROG(REG_1600H, 0x0000a4a0U);
            WR1_PROG(REG_1600H, 0x00000010U);

            WR1_PROG(REG_1600H, 0x0000a4e0U);
            WR1_PROG(REG_1600H, 0x00000004U);

            r_rsip_func101(bswap_32big(0x7c97ad8fU), bswap_32big(0x35987e49U), bswap_32big(0x2e3707edU),
                           bswap_32big(0x34872db6U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x380008c7U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0xb060c049U), bswap_32big(0xa32490c7U), bswap_32big(0x565f4714U),
                       bswap_32big(0xb9637c90U));
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
        RD4_ADDR(REG_1420H, &OutData_EncMsg[iLoop + 1]);

        r_rsip_func100(bswap_32big(0x9f1e770bU), bswap_32big(0x09bde06fU), bswap_32big(0x27db0297U),
                       bswap_32big(0xdff480acU));
        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_EncMsg[0]);

        r_rsip_func102(bswap_32big(0xaa28efb0U), bswap_32big(0x392d3709U), bswap_32big(0xde45a6d2U),
                       bswap_32big(0xa37cf0e3U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
}
