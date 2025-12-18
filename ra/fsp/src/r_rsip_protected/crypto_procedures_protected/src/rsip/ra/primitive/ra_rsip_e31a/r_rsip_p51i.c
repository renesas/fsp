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

rsip_ret_t r_rsip_p51i (const uint32_t InData_CurveType[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[],
                        const uint32_t InData_Signature[],
                        const uint32_t InData_DomainParam[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00510001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func_sub014(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    r_rsip_func_sub018(0x00000000U, 0x3420a800U, 0x00000002U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000001U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_0014H, 0x000017c5U);
    WR1_PROG(REG_00B0H, 0x00009493U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[4]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[8]);

    WR1_PROG(REG_00B0H, 0x0000949aU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[12]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[16]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Signature[20]);

    WR1_PROG(REG_0014H, 0x00000bc5U);
    WR1_PROG(REG_00B0H, 0x000094a1U);
    WAIT_STS(REG_0014H, 31, 1);
    WR12_ADDR(REG_002CH, &InData_MsgDgst[0]);

    WR1_PROG(REG_0094H, 0x00003420U);

    r_rsip_func100(bswap_32big(0x09e47bd0U),
                   bswap_32big(0x27f8d77dU),
                   bswap_32big(0x44dacdf2U),
                   bswap_32big(0x3f1379d2U));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x5d9c324eU),
                   bswap_32big(0x164f1990U),
                   bswap_32big(0xab7631faU),
                   bswap_32big(0x1ba84c66U));
    r_rsip_func_sub008(0x000000a1U, 0x0c2000a4U, 0x00000000U);
    r_rsip_func100(bswap_32big(0x0687d526U),
                   bswap_32big(0x4d859fe6U),
                   bswap_32big(0x63aedf52U),
                   bswap_32big(0xe9576716U));
    WR1_PROG(REG_00B0H, 0x000098a1U);

    r_rsip_func_sub004(0x00000200U, 0xe7029d07U, 0x00430031U, 0x00001032U);
    RD4_ADDR(REG_002CH, &S_HEAP[0]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &S_HEAP[4]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &S_HEAP[8]);

    r_rsip_func100(bswap_32big(0xb6357519U),
                   bswap_32big(0x8735757fU),
                   bswap_32big(0xa1388988U),
                   bswap_32big(0x0bef323fU));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub013(0x09120105U, 0x00410011U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &S_HEAP[12]);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00005101U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xb65cd4deU),
                   bswap_32big(0x96a815bbU),
                   bswap_32big(0x805b5ba4U),
                   bswap_32big(0x3019482dU));
    r_rsip_func043();

    r_rsip_func077();

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00005101U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xf13260a9U),
                   bswap_32big(0xd098d125U),
                   bswap_32big(0xe5f4d3b4U),
                   bswap_32big(0x0e7c50e4U));
    r_rsip_func044();

    r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

    r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

    r_rsip_func_sub011(0x000017c1U, 0x40000500U, 0xe8008107U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    r_rsip_func_sub009(0x0000b4adU, 0x00c10031U, 0x00001800U);

    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[13]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[17]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[21]);

    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[25]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0xde3e4fe7U),
                   bswap_32big(0x503ee36dU),
                   bswap_32big(0xf3333fa3U),
                   bswap_32big(0x697d670aU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xaeb73c42U), bswap_32big(0x99557010U), bswap_32big(0x59f57164U),
                       bswap_32big(0xe8246615U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000051U, 0x00000000U);

        r_rsip_func101(bswap_32big(0xa209d48fU), bswap_32big(0x03dcb2e8U), bswap_32big(0x3bd9cfdeU),
                       bswap_32big(0x64e0c79fU));
        r_rsip_func029(InData_DomainParam);

        r_rsip_func100(bswap_32big(0x730109adU), bswap_32big(0x2fbff422U), bswap_32big(0x40d22deaU),
                       bswap_32big(0xa8ea354aU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xfeffc477U), bswap_32big(0x51b0f4f9U), bswap_32big(0xb60f7959U),
                           bswap_32big(0xe6e5e27cU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func101(bswap_32big(0xbb74f6a6U), bswap_32big(0x4eb6cbd8U), bswap_32big(0x7cc8cd52U),
                           bswap_32big(0x859721d4U));

            return RSIP_RET_PASS;
        }
    }
}
