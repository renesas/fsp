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

rsip_ret_t r_rsip_p95f (const uint32_t InData_Text[],
                        const uint32_t InData_TextLen[],
                        uint32_t       OutData_Text[],
                        uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    r_rsip_func_sub014(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_002CH, InData_TextLen[0]);
    r_rsip_func_sub018(0x00000000U, 0x00008c00U, 0x0000000fU);

    r_rsip_func_sub010(0x38008800U, 0x00000000U, 0x00A70000U);

    r_rsip_func100(bswap_32big(0xdb82c82cU),
                   bswap_32big(0x298989faU),
                   bswap_32big(0xf13a26edU),
                   bswap_32big(0x1b7e4decU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func_sub019(0x000003c1U, 0xe7000d05U);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0094H, 0x00000821U);
        r_rsip_func_sub006(0x80840001U, 0x03410011U, 0x00000821U, 0x000008a5U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            r_rsip_func_sub022(0x3c0028a0U, 0x12003c25U, 0x00002ca0U);
        }

        r_rsip_func100(bswap_32big(0x70159a0fU), bswap_32big(0x5731a444U), bswap_32big(0x90ab8be4U),
                       bswap_32big(0xb62124b1U));
        WR1_PROG(REG_0094H, 0x00000821U);
        r_rsip_func_sub017(0x81840001U, 0x00005012U);
        RD1_ADDR(REG_002CH, &OutData_Text[0]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[2]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[3]);

        r_rsip_func101(bswap_32big(0x4f4cf7a5U), bswap_32big(0x8bac289eU), bswap_32big(0x23ad6375U),
                       bswap_32big(0x63d48dabU));
    }
    else
    {
        r_rsip_func101(bswap_32big(0xda4f8150U), bswap_32big(0x290d058cU), bswap_32big(0xbefa41fbU),
                       bswap_32big(0x95583d4aU));
    }

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func100(bswap_32big(0x00d76d03U),
                   bswap_32big(0xb1872fe8U),
                   bswap_32big(0x6ab0c05dU),
                   bswap_32big(0xed2b60d3U));
    r_rsip_func_sub013(0x09100105U, 0x00410011U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_MAC[0]);

    r_rsip_func102(bswap_32big(0x1d7ab3ddU),
                   bswap_32big(0x331bd333U),
                   bswap_32big(0x81240068U),
                   bswap_32big(0xcdad1785U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
