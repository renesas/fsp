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

rsip_ret_t r_rsip_p41f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Text[],
                        const uint32_t InData_DataT[],
                        const uint32_t InData_DataTLen[],
                        uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        r_rsip_func_sub008(0x000000a1U, 0x4a000104U, 0x00000000U);

        r_rsip_func101(bswap_32big(0x46540841U), bswap_32big(0xa52a710fU), bswap_32big(0x0f082649U),
                       bswap_32big(0xb82b1349U));
    }
    else
    {
        r_rsip_func_sub008(0x000000a1U, 0x5a000104U, 0x00000000U);

        r_rsip_func101(bswap_32big(0x84759fe7U), bswap_32big(0x82c89bb5U), bswap_32big(0x62b66ca0U),
                       bswap_32big(0x17a9aeefU));
    }

    r_rsip_func_sub013(0x0c000045U, 0x00410011U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        r_rsip_func100(bswap_32big(0xe4eb9035U), bswap_32big(0x3aeebca6U), bswap_32big(0x760ec9bbU),
                       bswap_32big(0xb4d7e7dcU));
        r_rsip_func_sub019(0x000003c1U, 0x0e000505U);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        r_rsip_func102(bswap_32big(0x46a1209aU), bswap_32big(0xd3828dfdU), bswap_32big(0x0730f104U),
                       bswap_32big(0x8b77c1f6U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
    else
    {
        r_rsip_func_sub014(0x000000c7U, 0x80010040U);
        WR1_PROG(REG_002CH, InData_DataTLen[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub010(0x3420a840U, 0x00000010U, 0x00270000U);

        WR1_PROG(REG_0094H, 0x0000b460U);
        r_rsip_func_sub010(0x00000080U, 0x34202862U, 0x00270000U);

        r_rsip_func100(bswap_32big(0x1c380ef7U), bswap_32big(0xb2571022U), bswap_32big(0xc6eab227U),
                       bswap_32big(0x88e8b9beU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xbf871c00U), bswap_32big(0xb387e8ceU), bswap_32big(0x378534a4U),
                           bswap_32big(0x346f734cU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func_sub019(0x000003c1U, 0x0e000505U);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            WR1_PROG(REG_0094H, 0x00000821U);
            r_rsip_func_sub006(0x80840001U, 0x03410011U, 0x000034e2U, 0x000568e7U);
            r_rsip_func_sub022(0x00026ce7U, 0x00003827U, 0x0000b4c0U);
            r_rsip_func_sub022(0x00000020U, 0x00003402U, 0x00008c00U);
            r_rsip_func_sub022(0x0000001fU, 0x000028c0U, 0x00008cc0U);
            r_rsip_func_sub022(0x0000001fU, 0x00004406U, 0x00007421U);
            r_rsip_func_sub022(0x00007821U, 0x00003c27U, 0x000034c2U);
            r_rsip_func_sub022(0x0000a4c0U, 0x0000001fU, 0x000568c6U);

            r_rsip_func_sub022(0x000034e6U, 0x00026ce7U, 0x00000821U);

            for (iLoop = 0U; iLoop < 4; iLoop++)
            {
                r_rsip_func_sub022(0x3420a8e0U, 0x0000000dU, 0x10003c27U);

                WR1_PROG(REG_0094H, 0x1000a4e0U);
                WR1_PROG(REG_0094H, 0x00000004U);
            }

            WR1_PROG(REG_00D0H, 0x08000045U);
            r_rsip_func_sub012(0x81840001U, 0x00490011U);

            r_rsip_func_sub019(0x000003c1U, 0x9c000005U);
            WR4_ADDR(REG_002CH, &InData_DataT[0]);

            r_rsip_func100(bswap_32big(0xe7c4ab93U), bswap_32big(0xc3e961e0U), bswap_32big(0x7cb788f5U),
                           bswap_32big(0x1d0bd732U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x95d9ae3dU),
                               bswap_32big(0x6f242a3cU),
                               bswap_32big(0xbbf77218U),
                               bswap_32big(0x86f0667bU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_AUTH_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0xe26be36fU),
                               bswap_32big(0x29b5eb50U),
                               bswap_32big(0x81dfe866U),
                               bswap_32big(0x77c44a94U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
