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

rsip_ret_t r_rsip_p41f (const uint32_t InData_Cmd[], const uint32_t InData_Text[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x4a000104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0xec692b6cU), bswap_32big(0xd761f7bbU), bswap_32big(0x1377e039U), bswap_32big(0xf5bb2c46U));
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x5a000104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0x87232a09U), bswap_32big(0x05dbf5b0U), bswap_32big(0x69644b78U), bswap_32big(0xcf71fe06U));
    }

    WR1_PROG(REG_00D0H, 0x0c000045U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        r_rsip_func100(bswap_32big(0xe30c2a4dU), bswap_32big(0x29f2e049U), bswap_32big(0x52f6fdadU), bswap_32big(0x29cd2d55U));
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0x0e000505U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        r_rsip_func102(bswap_32big(0xa6ee047bU), bswap_32big(0x83099de9U), bswap_32big(0x847be09dU), bswap_32big(0x148033a3U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010040U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_DataTLen[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x3420a840U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000080U);
        WR1_PROG(REG_0094H, 0x34202862U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        r_rsip_func100(bswap_32big(0xb76c3236U), bswap_32big(0xa70185edU), bswap_32big(0x2cd4cfbdU), bswap_32big(0x5f16d5e7U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xed7cd241U), bswap_32big(0xaf8ea654U), bswap_32big(0x72be56ecU), bswap_32big(0xf9012341U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x0e000505U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_009CH, 0x80840001U);
            WR1_PROG(REG_0000H, 0x03410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x000034e2U);
            WR1_PROG(REG_0094H, 0x000568e7U);
            WR1_PROG(REG_0094H, 0x00026ce7U);

            WR1_PROG(REG_0094H, 0x00003827U);

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x00000020U);
            WR1_PROG(REG_0094H, 0x00003402U);
            WR1_PROG(REG_0094H, 0x00008c00U);
            WR1_PROG(REG_0094H, 0x0000001fU);
            WR1_PROG(REG_0094H, 0x000028c0U);
            WR1_PROG(REG_0094H, 0x00008cc0U);
            WR1_PROG(REG_0094H, 0x0000001fU);

            WR1_PROG(REG_0094H, 0x00004406U);

            WR1_PROG(REG_0094H, 0x00007421U);
            WR1_PROG(REG_0094H, 0x00007821U);

            WR1_PROG(REG_0094H, 0x00003c27U);

            WR1_PROG(REG_0094H, 0x000034c2U);
            WR1_PROG(REG_0094H, 0x0000a4c0U);
            WR1_PROG(REG_0094H, 0x0000001fU);
            WR1_PROG(REG_0094H, 0x000568c6U);

            WR1_PROG(REG_0094H, 0x000034e6U);
            WR1_PROG(REG_0094H, 0x00026ce7U);

            WR1_PROG(REG_0094H, 0x00000821U);

            for (iLoop = 0U; iLoop < 4; iLoop++)
            {
                WR1_PROG(REG_0094H, 0x3420a8e0U);
                WR1_PROG(REG_0094H, 0x0000000dU);
                WR1_PROG(REG_0094H, 0x10003c27U);

                WR1_PROG(REG_0094H, 0x1000a4e0U);
                WR1_PROG(REG_0094H, 0x00000004U);
            }

            WR1_PROG(REG_00D0H, 0x08000045U);
            WR1_PROG(REG_009CH, 0x81840001U);
            WR1_PROG(REG_0000H, 0x00490011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x9c000005U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_DataT[0]);

            r_rsip_func100(bswap_32big(0xc0eb5ffcU), bswap_32big(0x2d1d20f5U), bswap_32big(0xafd9c26eU), bswap_32big(0xf6a168feU));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x5abb2de7U), bswap_32big(0xe082f4d5U), bswap_32big(0x9fffed78U), bswap_32big(0x0f4e30c2U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_AUTH_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x7d6de6fdU), bswap_32big(0x9009f2ecU), bswap_32big(0xec852aa6U), bswap_32big(0xa579b668U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
