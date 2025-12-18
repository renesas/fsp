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

    r_rsip_func_sub014(0x000000c7U, 0x800100a0U);
    WR1_PROG(REG_002CH, InData_EncMsgLength[0]);
    r_rsip_func_sub018(0x00000000U, 0x000008e7U, 0x300088a0U);
    r_rsip_func_sub022(0x00000000U, 0x00030020U, 0x00002ce0U);

    r_rsip_func_sub022(0x00000080U, 0x300088a0U, 0x0000000dU);
    r_rsip_func_sub022(0x00030020U, 0x00002ce0U, 0x00000080U);

    r_rsip_func_sub022(0x300088a0U, 0x00000011U, 0x00030020U);

    WR1_PROG(REG_0094H, 0x00002ce0U);

    r_rsip_func_sub010(0x00000080U, 0x38000ce7U, 0x00270000U);

    r_rsip_func100(bswap_32big(0xbb586cafU),
                   bswap_32big(0xedfb77e0U),
                   bswap_32big(0x04de4fdaU),
                   bswap_32big(0x6a15df92U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x12ba7348U), bswap_32big(0x1ca4682fU), bswap_32big(0x1a9b773eU),
                       bswap_32big(0xe5fd36fdU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func_sub016(0x38000ca5U, 0x00000080U, 0x00A70000U);

        r_rsip_func100(bswap_32big(0xc032819bU), bswap_32big(0x5f824611U), bswap_32big(0x3f66c088U),
                       bswap_32big(0xaacd8effU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
            WR1_PROG(REG_002CH, InData_EncMsg[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e503U, 0x00000000U);

            r_rsip_func101(bswap_32big(0xcd1e2290U), bswap_32big(0xaf7cfe9fU), bswap_32big(0x877f7f1bU),
                           bswap_32big(0x89e29d1fU));
            r_rsip_func143();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e503U, 0x00000000U);

            r_rsip_func101(bswap_32big(0x3f2d253cU), bswap_32big(0x49228e4bU), bswap_32big(0xcd505acaU),
                           bswap_32big(0xca7a1e60U));
            r_rsip_func044();

            WAIT_STS(REG_0118H, 0, 1);

            r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

            r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

            r_rsip_func100(bswap_32big(0x9ac1fca9U), bswap_32big(0xc9504199U), bswap_32big(0x80f5e047U),
                           bswap_32big(0xa2ecf57dU));
            r_rsip_func_sub017(0x810100a0U, 0x00005006U);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            r_rsip_func_sub022(0x0000a8a0U, 0x00000002U, 0x000268a5U);

            WR1_PROG(REG_0094H, 0x00000821U);

            for (iLoop = 0U; iLoop < S_RAM[0] - 5; )
            {
                r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0xf7008d05U);
                WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

                r_rsip_func_sub015(0x01410011U, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0x425d1c9aU),
                               bswap_32big(0x0c4747edU),
                               bswap_32big(0x6eaeda7dU),
                               bswap_32big(0xdca5d420U));
                iLoop = iLoop + 4U;
            }

            r_rsip_func_sub016(0x38000825U, 0x00000080U, 0x00270000U);
            WR1_PROG(REG_0040H, 0x00402000U);

            r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_EncMsg[1 + iLoop]);

            r_rsip_func_sub013(0x9c100005U, 0x00410011U);

            r_rsip_func100(bswap_32big(0x85da840fU), bswap_32big(0x218f78bfU), bswap_32big(0xeccf0ed1U),
                           bswap_32big(0xd2ee313aU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func101(bswap_32big(0x24f3b5fcU),
                               bswap_32big(0xbda9a57bU),
                               bswap_32big(0x10c7a068U),
                               bswap_32big(0x83a39d14U));

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0x6b3112a0U),
                               bswap_32big(0x770983f0U),
                               bswap_32big(0xfe58faaeU),
                               bswap_32big(0x3e38a962U));

                return RSIP_RET_PASS;
            }
        }
        else
        {
            r_rsip_func101(bswap_32big(0x86106522U), bswap_32big(0x1926328fU), bswap_32big(0x2dde8f5cU),
                           bswap_32big(0xec6670fbU));

            return RSIP_RET_PASS;
        }
    }
}
