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

rsip_ret_t r_rsip_pa4i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[],
                        const uint32_t InData_Header[],
                        uint32_t       Header_Len)
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00a40001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x000000a4U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xf689dc77U),
                   bswap_32big(0x9bd4496aU),
                   bswap_32big(0x255e49b9U),
                   bswap_32big(0x11e8ee2cU));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0xe33f4d70U),
                   bswap_32big(0xf4cdcd36U),
                   bswap_32big(0x2ab280faU),
                   bswap_32big(0x3be45fdbU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x7f177045U), bswap_32big(0xa76c5b9cU), bswap_32big(0x5c2630cbU),
                       bswap_32big(0xfe6d441cU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func_sub014(0x000000c7U, 0x80010080U);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub016(0x38000c84U, 0x00000080U, 0x00270000U);

        r_rsip_func100(bswap_32big(0xbf34319dU), bswap_32big(0x4cc95aa6U), bswap_32big(0x3531da6cU),
                       bswap_32big(0xf0484378U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func_sub019(0x000003c1U, 0x08000045U);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0xc82f4253U), bswap_32big(0x95d3cd4eU), bswap_32big(0x2dc33eebU),
                           bswap_32big(0x44bb3900U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x000000a4U, 0x00000000U);

            r_rsip_func101(bswap_32big(0x22ffc139U), bswap_32big(0xec4ad117U), bswap_32big(0xa09ba276U),
                           bswap_32big(0x307b4fecU));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xb795a95fU), bswap_32big(0xf46857c0U), bswap_32big(0xf1ff80f3U),
                           bswap_32big(0x5189afc3U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x27332e7dU),
                               bswap_32big(0x15b908a6U),
                               bswap_32big(0x8f351135U),
                               bswap_32big(0xca61f428U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                r_rsip_func_sub009(0x00000801U, 0x00430009U, 0x00001800U);

                r_rsip_func_sub009(0x00000802U, 0x00430009U, 0x00001800U);

                r_rsip_func101(bswap_32big(0x1d607feeU),
                               bswap_32big(0xf95e0d6bU),
                               bswap_32big(0x75e3260fU),
                               bswap_32big(0x21afb4f1U));
            }
        }

        r_rsip_func100(bswap_32big(0x358c6d16U), bswap_32big(0x08893465U), bswap_32big(0x9061c122U),
                       bswap_32big(0x3b91cb3eU));
        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub009(0x0000181eU, 0x00430011U, 0x00001800U);

        r_rsip_func100(bswap_32big(0xdd7387cbU), bswap_32big(0x83ec9314U), bswap_32big(0x0eafe9bbU),
                       bswap_32big(0x4c4f9ea6U));
        r_rsip_func_sub013(0x08000095U, 0x00430011U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        r_rsip_func501(InData_Header, Header_Len);

        r_rsip_func101(bswap_32big(0x3754bbb3U), bswap_32big(0xc4ba2214U), bswap_32big(0xae0e67edU),
                       bswap_32big(0x7762bd8eU));

        return RSIP_RET_PASS;
    }
}
