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

rsip_ret_t r_rsip_pe5e (const uint32_t InData_EncMsg[], const uint32_t InData_EncMsgLength[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100a0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_EncMsgLength[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub016(0x000008e7U, 0x300088a0U, 0x00000000U);
    r_rsip_func_sub016(0x00030020U, 0x00002ce0U, 0x00000080U);

    r_rsip_func_sub016(0x300088a0U, 0x0000000dU, 0x00030020U);

    WR1_PROG(REG_0094H, 0x00002ce0U);

    r_rsip_func_sub007(0x00000080U, 0x38000ce7U, 0x00260000U);

    r_rsip_func100(bswap_32big(0x44f4025eU),
                   bswap_32big(0x9b213911U),
                   bswap_32big(0x9da2ee54U),
                   bswap_32big(0xf1841a6cU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe2090228U), bswap_32big(0x202d8015U), bswap_32big(0x62bc6475U),
                       bswap_32big(0x1e84a15aU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x38000ca5U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0xc99f732cU), bswap_32big(0xe455318bU), bswap_32big(0xb3942fa6U),
                       bswap_32big(0xefbcf5c9U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_EncMsg[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func_sub002(0x800100e0U, 0x0000e503U);

            r_rsip_func101(bswap_32big(0x9a0dc906U), bswap_32big(0xf1707ebbU), bswap_32big(0xc84c3f64U),
                           bswap_32big(0xca91d374U));
            r_rsip_func143();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            r_rsip_func_sub002(0x800100e0U, 0x0000e503U);

            r_rsip_func101(bswap_32big(0x1618b0d5U), bswap_32big(0xa852907cU), bswap_32big(0xb17fc45dU),
                           bswap_32big(0x039e6b80U));
            r_rsip_func044();

            WAIT_STS(REG_00F8H, 0, 1);

            r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

            r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

            r_rsip_func100(bswap_32big(0xbd2b2fb0U), bswap_32big(0x8ae84c1dU), bswap_32big(0x0371bf94U),
                           bswap_32big(0x92db4e88U));
            WR1_PROG(REG_009CH, 0x810100a0U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            r_rsip_func_sub016(0x0000a8a0U, 0x00000002U, 0x000268a5U);

            WR1_PROG(REG_0094H, 0x00000884U);

            for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
            {
                r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0xf7008d05U);
                WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

                r_rsip_func_sub009(0x01410011U, 0x00002c80U);

                r_rsip_func101(bswap_32big(0xe25df6e0U),
                               bswap_32big(0x9ccce299U),
                               bswap_32big(0x930c6830U),
                               bswap_32big(0x49b8594eU));
                iLoop = iLoop + 4U;
            }

            r_rsip_func_sub010(0x38000885U);

            r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

            r_rsip_func_sub006(0x9c100005U, 0x00410011U);

            r_rsip_func100(bswap_32big(0x6a2fd603U), bswap_32big(0x5a339d7dU), bswap_32big(0x6092bf17U),
                           bswap_32big(0xd0c74361U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func101(bswap_32big(0x118b9391U),
                               bswap_32big(0x36a46826U),
                               bswap_32big(0x14286a92U),
                               bswap_32big(0x0f35064aU));

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x1903d8a2U),
                               bswap_32big(0x40239b76U),
                               bswap_32big(0x2075ee06U),
                               bswap_32big(0xaeb764adU));

                return RSIP_RET_PASS;
            }
        }
        else
        {
            r_rsip_func101(bswap_32big(0x0732e560U), bswap_32big(0xb53c2b66U), bswap_32big(0x55e071edU),
                           bswap_32big(0x9e7cd9e4U));

            return RSIP_RET_PASS;
        }
    }
}
