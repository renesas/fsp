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

rsip_ret_t r_rsip_pa4f (const uint32_t InData_Text[],
                        const uint32_t InData_TextLen[],
                        const uint32_t InData_MAC[],
                        const uint32_t InData_MACLength[],
                        uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    r_rsip_func_sub014(0x000000c7U, 0x80010060U);
    WR1_PROG(REG_002CH, InData_MACLength[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub010(0x38008860U, 0x00000000U, 0x00270000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    r_rsip_func_sub010(0x00000010U, 0x342028a3U, 0x00270000U);

    r_rsip_func100(bswap_32big(0xe5248a57U),
                   bswap_32big(0x58aaf447U),
                   bswap_32big(0x1984bcf5U),
                   bswap_32big(0xe726cd84U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe1df17a0U), bswap_32big(0xcd3d6f6fU), bswap_32big(0x6a2c7fb7U),
                       bswap_32big(0xeac1e89cU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func_sub014(0x000000c7U, 0x80010000U);
        WR1_PROG(REG_002CH, InData_TextLen[0]);
        r_rsip_func_sub018(0x00000000U, 0x00008c00U, 0x0000000fU);

        r_rsip_func_sub010(0x38008800U, 0x00000000U, 0x00A70000U);

        r_rsip_func100(bswap_32big(0x02fd3deeU), bswap_32big(0x20f36693U), bswap_32big(0x7475255eU),
                       bswap_32big(0x032064f6U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            WR1_PROG(REG_0094H, 0x00000821U);
            r_rsip_func_sub006(0x80840001U, 0x03410011U, 0x00000821U, 0x000008a5U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                r_rsip_func_sub022(0x3c0028a0U, 0x12003c25U, 0x00002ca0U);
            }

            r_rsip_func100(bswap_32big(0x2b45bc7fU), bswap_32big(0xe00dbb6aU), bswap_32big(0x4e1506dfU),
                           bswap_32big(0xd051b374U));
            WR1_PROG(REG_0094H, 0x00000821U);
            r_rsip_func_sub017(0x81840001U, 0x00005012U);
            RD1_ADDR(REG_002CH, &OutData_Text[0]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[2]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[3]);

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x0e108405U);
            r_rsip_func_sub012(0x81840001U, 0x00490011U);

            r_rsip_func101(bswap_32big(0xe7c0e8f2U), bswap_32big(0x31f1ec92U), bswap_32big(0x739b1a4aU),
                           bswap_32big(0x79736835U));
        }
        else
        {
            r_rsip_func101(bswap_32big(0xa08094c5U), bswap_32big(0xa4d1502cU), bswap_32big(0x2e3bc1d4U),
                           bswap_32big(0x18690ed4U));
        }

        r_rsip_func_sub008(0x000000a1U, 0x0c100104U, 0x00000000U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        r_rsip_func_sub013(0x07208d05U, 0x00410011U);

        WR1_PROG(REG_0094H, 0x00000821U);
        r_rsip_func_sub006(0x80840001U, 0x03410011U, 0x000008a5U, 0x00000821U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            r_rsip_func_sub022(0x3c0028a3U, 0x12003c25U, 0x00002ca0U);
        }

        r_rsip_func_sub019(0x000003c1U, 0x08000055U);
        WR4_ADDR(REG_002CH, &InData_MAC[0]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        r_rsip_func_sub007(0x00000821U, 0x81840001U, 0x00490011U);
        WR1_PROG(REG_00D0H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x258ebbc4U), bswap_32big(0x889df16dU), bswap_32big(0xf0bc9048U),
                       bswap_32big(0xbc7b49f6U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xeca35babU), bswap_32big(0x1bbc23a3U), bswap_32big(0xd857b2b6U),
                           bswap_32big(0x4d2b6be8U));

            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_AUTH_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0x58859ea5U), bswap_32big(0x5784eb8fU), bswap_32big(0x3ff627adU),
                           bswap_32big(0xc5591a8cU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
