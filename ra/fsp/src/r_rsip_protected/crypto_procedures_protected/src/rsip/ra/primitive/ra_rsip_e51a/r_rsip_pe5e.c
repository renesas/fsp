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

rsip_ret_t r_rsip_pe5e (const uint32_t InData_EncMsg[], uint32_t MAX_CNT2)
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010100U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(MAX_CNT2));
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000d08U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xb1896bd9U), bswap_32big(0xa91c0f26U), bswap_32big(0xaeb0a8bfU), bswap_32big(0x94a1395aU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_EncMsg[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e503U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xc12bffadU), bswap_32big(0xefa1a2b5U), bswap_32big(0x993f55fcU), bswap_32big(0x4613e8deU));
        r_rsip_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x01799093U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e503U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xfbda1c8aU), bswap_32big(0x5b3a2b82U), bswap_32big(0x0231fbb2U), bswap_32big(0x1df93cb9U));
        r_rsip_func044();

        WAIT_STS(REG_2030H, 0, 1);

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000054U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0x86fa8a6bU), bswap_32big(0x3f399855U), bswap_32big(0x6ba5a018U), bswap_32big(0xe0211bd1U));
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0x65d4110cU), bswap_32big(0xd0235ae7U), bswap_32big(0xd74529f7U), bswap_32big(0x2a182de1U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c2000c4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0x8f1a5d77U), bswap_32big(0xa4c4774aU), bswap_32big(0xdca65a6bU), bswap_32big(0x8037d15eU));
        WR1_PROG(REG_1608H, 0x81010100U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);
        OFS_ADR  = S_RAM[0];

        WR1_PROG(REG_1600H, 0x0000a900U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1600H, 0x00026908U);

        WR1_PROG(REG_1600H, 0x00000929U);

        for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
        {
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_EncMsg[1 + iLoop]);

            r_rsip_func100(bswap_32big(0x23598f58U), bswap_32big(0x359440bcU), bswap_32big(0x1150dc1fU), bswap_32big(0x25764abaU));
            WR1_PROG(REG_1824H, 0xe7040d05U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1408H, 0x00001012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &S_HEAP[iLoop]);

            WR1_PROG(REG_1600H, 0x00002d20U);

            r_rsip_func101(bswap_32big(0xc7deced5U), bswap_32big(0x5f985946U), bswap_32big(0x9c3113e7U), bswap_32big(0x3887b2ccU));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000909U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0xf3b37adfU), bswap_32big(0xe0e93e14U), bswap_32big(0xb35f44d4U), bswap_32big(0x7eff7a21U));
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x0c000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1824H, 0x09140105U);
        WR1_PROG(REG_1400H, 0x00410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00001012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &S_HEAP[iLoop]);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_EncMsg[OFS_ADR - 4]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x814ce8abU), bswap_32big(0xacdbef80U), bswap_32big(0xd36894f2U), bswap_32big(0xd48aec53U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func101(bswap_32big(0xba48ca99U), bswap_32big(0x072c98ddU), bswap_32big(0x42007c38U), bswap_32big(0xbd29da3aU));

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000044U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000054U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1600H, 0x00000929U);

            for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0xf7040d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &S_HEAP[iLoop]);
                WR1_PROG(REG_1400H, 0x01410011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00002d20U);

                r_rsip_func101(bswap_32big(0xc07ea5d0U), bswap_32big(0x7e6f6afbU), bswap_32big(0xaae49b0dU), bswap_32big(0xdc200a2eU));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000909U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x07040d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &S_HEAP[iLoop]);

            WR1_PROG(REG_1824H, 0x8c100005U);
            WR1_PROG(REG_1400H, 0x00410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            r_rsip_func100(bswap_32big(0x14cb3e1fU), bswap_32big(0x98f0c2edU), bswap_32big(0x05bc1c60U), bswap_32big(0x519614d8U));

            WR1_PROG(REG_1408H, 0x00020000U);

            r_rsip_func101(bswap_32big(0x3e62a59fU), bswap_32big(0xadb3ccd7U), bswap_32big(0xdff6c8faU), bswap_32big(0x1f955a02U));

            return RSIP_RET_PASS;
        }
    }
    else
    {
        r_rsip_func101(bswap_32big(0x7be6d59aU), bswap_32big(0x660960d3U), bswap_32big(0x1385e7fdU), bswap_32big(0x1f28b2a5U));

        return RSIP_RET_PASS;
    }
}
