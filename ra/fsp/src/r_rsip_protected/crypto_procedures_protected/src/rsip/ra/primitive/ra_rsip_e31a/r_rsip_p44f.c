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

rsip_ret_t r_rsip_p44f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Text[],
                        const uint32_t InData_DataT[],
                        const uint32_t InData_DataTLen[],
                        uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x4a008104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0x276a10c9U), bswap_32big(0xe0f33c61U), bswap_32big(0x37944f61U),
                       bswap_32big(0x2de566d9U));
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x5a008104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0x8e62deadU), bswap_32big(0xe6915aeeU), bswap_32big(0x2eb4110eU),
                       bswap_32big(0xacecc8c2U));
    }

    WR1_PROG(REG_00D0H, 0x0c000045U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        r_rsip_func100(bswap_32big(0xeab9cd2aU), bswap_32big(0x54cf93d9U), bswap_32big(0x5dec354bU),
                       bswap_32big(0x9f4c86e3U));
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0e008505U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        r_rsip_func102(bswap_32big(0xc17d54b1U), bswap_32big(0xcc1de4f0U), bswap_32big(0xbf2535ddU),
                       bswap_32big(0x452f043fU));
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
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000080U);
        WR1_PROG(REG_0094H, 0x34202862U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0xfe82f015U), bswap_32big(0x0645d3ecU), bswap_32big(0xe7898414U),
                       bswap_32big(0xe6bcc45eU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x8612252fU), bswap_32big(0x62b84b31U), bswap_32big(0xb14ed490U),
                           bswap_32big(0xe10ad400U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x0e008505U);
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

            r_rsip_func100(bswap_32big(0x1b74208eU), bswap_32big(0x005c7bb7U), bswap_32big(0xdf9466d8U),
                           bswap_32big(0xf1e6a51aU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x0132a139U),
                               bswap_32big(0x9dd37622U),
                               bswap_32big(0x3e28a8efU),
                               bswap_32big(0x0baf6c1eU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_AUTH_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x0db3a55bU),
                               bswap_32big(0xa0a2383aU),
                               bswap_32big(0x321bc0dcU),
                               bswap_32big(0xf8a968b7U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
