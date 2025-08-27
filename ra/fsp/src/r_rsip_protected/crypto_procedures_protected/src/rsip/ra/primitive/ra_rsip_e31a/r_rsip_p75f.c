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

rsip_ret_t r_rsip_p75f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Msg[],
                        const uint32_t InData_MAC[],
                        const uint32_t InData_length[],
                        uint32_t       MAX_CNT,
                        uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_0118H, 0, 1);

    WR1_PROG(REG_0014H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR16_ADDR(REG_002CH, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_0014H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_002CH, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_0014H, 0x00000000U);
    WAIT_STS(REG_0118H, 8, 0);
    WR1_PROG(REG_0040H, 0x00001600U);

    WAIT_STS(REG_0118H, 4, 1);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xa3342510U),
                   bswap_32big(0xc5c8c3ecU),
                   bswap_32big(0x14b262b9U),
                   bswap_32big(0x337e0661U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func100(bswap_32big(0xede8b578U), bswap_32big(0xe3eff517U), bswap_32big(0x48b48104U),
                       bswap_32big(0x214e9725U));

        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            r_rsip_func100(bswap_32big(0xddbeb41fU), bswap_32big(0x9b8e55d4U), bswap_32big(0x4566fb82U),
                           bswap_32big(0x9418e1f1U));
            WR1_PROG(REG_0008H, 0x00004022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD8_ADDR(REG_002CH, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0xf565b7ffU), bswap_32big(0xccf5cd82U), bswap_32big(0x32330596U),
                           bswap_32big(0x70f5de23U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            r_rsip_func100(bswap_32big(0xe7e6c579U), bswap_32big(0x9ffa46ecU), bswap_32big(0x9ccd5118U),
                           bswap_32big(0x0e450f3bU));
            WR1_PROG(REG_0008H, 0x00004032U);
            WAIT_STS(REG_0008H, 30, 1);
            RD12_ADDR(REG_002CH, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0x7a1c5907U), bswap_32big(0x854fa39eU), bswap_32big(0xcb566e54U),
                           bswap_32big(0xe598ff1dU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            r_rsip_func100(bswap_32big(0x0e21ac3aU), bswap_32big(0x2505a928U), bswap_32big(0x9432fc1eU),
                           bswap_32big(0xa6107f91U));
            WR1_PROG(REG_0008H, 0x00004042U);
            WAIT_STS(REG_0008H, 30, 1);
            RD16_ADDR(REG_002CH, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0x14472988U), bswap_32big(0x8e7d3cc8U), bswap_32big(0x9f36875bU),
                           bswap_32big(0x54fba7a0U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);
        }

        return RSIP_RET_PASS;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xed23643cU), bswap_32big(0xceb4027cU), bswap_32big(0xb186ce37U),
                       bswap_32big(0x5e337808U));

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010020U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_length[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0094H, 0x0000b440U);
            WR1_PROG(REG_0094H, 0x00000020U);

            r_rsip_func101(bswap_32big(0x6bdebfc9U), bswap_32big(0xeb98df51U), bswap_32big(0x57bed4e8U),
                           bswap_32big(0x2e25140fU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_0094H, 0x0000b440U);
            WR1_PROG(REG_0094H, 0x00000030U);

            r_rsip_func101(bswap_32big(0x78527030U), bswap_32big(0x0a460a97U), bswap_32big(0x4b62c77bU),
                           bswap_32big(0x10c262d2U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_0094H, 0x0000b440U);
            WR1_PROG(REG_0094H, 0x00000040U);

            r_rsip_func101(bswap_32big(0xcad5824dU), bswap_32big(0x35e2c9c7U), bswap_32big(0x8e51936eU),
                           bswap_32big(0x944bc2cbU));
        }

        WR1_PROG(REG_0094H, 0x3420a820U);
        WR1_PROG(REG_0094H, 0x00000004U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0094H, 0x34202841U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0x4e3bf61eU), bswap_32big(0xdb075a96U), bswap_32big(0x244900a3U),
                       bswap_32big(0x2e615c48U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x6ffd75f0U), bswap_32big(0xaed03082U), bswap_32big(0x83d71c37U),
                           bswap_32big(0xaaa9fd7dU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x1d653cb1U), bswap_32big(0x6c0d359aU), bswap_32big(0x7d3ea1d1U),
                           bswap_32big(0x8f7993c6U));

            WR1_PROG(REG_0094H, 0x000008c6U);

            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x00026842U);

            WR1_PROG(REG_009CH, 0x81010040U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; )
            {
                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_009CH, 0x80840007U);
                WR1_PROG(REG_0000H, 0x03450011U);

                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D0H, 0x08000045U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_MAC[iLoop]);

                WR1_PROG(REG_0094H, 0x00000800U);
                for (jLoop = 0U; jLoop < 16U; jLoop++)
                {
                    WR1_PROG(REG_0094H, 0x3c0028a1U);
                    WR1_PROG(REG_0094H, 0x12003c07U);
                    WR1_PROG(REG_0094H, 0x00002ce0U);
                    WR1_PROG(REG_0094H, 0x00002ca0U);
                }

                WR1_PROG(REG_00D0H, 0x9c000005U);
                WR1_PROG(REG_0094H, 0x000008e7U);
                WR1_PROG(REG_009CH, 0x81840007U);
                WR1_PROG(REG_0000H, 0x00490011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000a4c0U);
                WR1_PROG(REG_0094H, 0x00000004U);

                r_rsip_func101(bswap_32big(0x0a62d5f4U),
                               bswap_32big(0x207064adU),
                               bswap_32big(0x73267434U),
                               bswap_32big(0x5efdfe79U));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_0094H, 0x000008c2U);

            WR1_PROG(REG_0094H, 0x00007c06U);
            WR1_PROG(REG_0040H, 0x00602000U);

            r_rsip_func100(bswap_32big(0xe7cd31f6U), bswap_32big(0x09f2544dU), bswap_32big(0x414fdcf2U),
                           bswap_32big(0x3cc25be2U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x735c917eU),
                               bswap_32big(0xa99e7a7bU),
                               bswap_32big(0x3f3f2bddU),
                               bswap_32big(0xe2f8f9e9U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x85aef91eU),
                               bswap_32big(0x4dd91aabU),
                               bswap_32big(0xf75087bbU),
                               bswap_32big(0xc307e3a7U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
