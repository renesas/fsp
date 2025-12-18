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

rsip_ret_t r_rsip_p47i (const uint32_t InData_Cmd[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00470001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func_sub014(0x000000c7U, 0x80010080U);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    r_rsip_func_sub018(0x00000000U, 0x0000b4a0U, 0x00000005U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004701U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x722f5066U),
                   bswap_32big(0x00843c82U),
                   bswap_32big(0x2f5d9ed1U),
                   bswap_32big(0x54ff5e39U));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0xdb8bd860U),
                   bswap_32big(0x2b613286U),
                   bswap_32big(0x3c670360U),
                   bswap_32big(0x4fc01d4dU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x2405e15eU), bswap_32big(0x2bf57863U), bswap_32big(0x73a29c16U),
                       bswap_32big(0xbbf6056eU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub009(0x00000801U, 0x03430009U, 0x00001800U);

        r_rsip_func_sub009(0x00000802U, 0x03430009U, 0x00001800U);

        r_rsip_func_sub010(0x3c00a880U, 0x00000002U, 0x00270000U);

        r_rsip_func100(bswap_32big(0x8a9cf995U), bswap_32big(0x86f42795U), bswap_32big(0x52c46571U),
                       bswap_32big(0x870687a6U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x000008a5U);

            r_rsip_func_sub010(0x3c00a880U, 0x00000004U, 0x00A70000U);

            r_rsip_func100(bswap_32big(0xde52627aU), bswap_32big(0x00f93636U), bswap_32big(0x0a56258bU),
                           bswap_32big(0xafdb528eU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func_sub014(0x000000c7U, 0x800100a0U);
                WR1_PROG(REG_002CH, InData_IVType[0]);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x93bb54d2U),
                               bswap_32big(0x3bc828a9U),
                               bswap_32big(0x751ec07fU),
                               bswap_32big(0xe6ab5965U));
            }

            r_rsip_func_sub016(0x38000ca5U, 0x00000080U, 0x00270000U);

            r_rsip_func100(bswap_32big(0x2a57ea16U), bswap_32big(0x2d53ec98U), bswap_32big(0x2525871bU),
                           bswap_32big(0x03391f45U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func_sub019(0x000003c1U, 0x08000045U);
                WR4_ADDR(REG_002CH, &InData_IV[0]);

                r_rsip_func101(bswap_32big(0xbe199501U),
                               bswap_32big(0xf08ab8f4U),
                               bswap_32big(0x02ece9caU),
                               bswap_32big(0x172e7381U));
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b4a0U);
                WR1_PROG(REG_0094H, 0x0199e556U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004702U, 0x00000000U);

                r_rsip_func101(bswap_32big(0x1669ae4eU),
                               bswap_32big(0x8f26a5a4U),
                               bswap_32big(0x4113a9e2U),
                               bswap_32big(0x0c412992U));
                r_rsip_func440(InData_IV);

                r_rsip_func100(bswap_32big(0x4f6dedf0U),
                               bswap_32big(0x4af5e622U),
                               bswap_32big(0xa3b7d412U),
                               bswap_32big(0xa0a5ffa5U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0xe058af49U),
                                   bswap_32big(0xc898725aU),
                                   bswap_32big(0x8b6e8a31U),
                                   bswap_32big(0xe5fbc204U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    WR1_PROG(REG_00D0H, 0x08000045U);
                    r_rsip_func_sub009(0x00000801U, 0x00430009U, 0x00001800U);

                    r_rsip_func_sub009(0x00000802U, 0x00430009U, 0x00001800U);

                    r_rsip_func101(bswap_32big(0xc53f9494U),
                                   bswap_32big(0x279cd20dU),
                                   bswap_32big(0x49d879deU),
                                   bswap_32big(0x1212ac44U));
                }
            }
        }

        r_rsip_func100(bswap_32big(0xa8c4c812U), bswap_32big(0xd8ca79f9U), bswap_32big(0x5d340b23U),
                       bswap_32big(0x1ac250d3U));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub006(0x81840000U, 0x00490011U, 0x0c003080U, 0x2000b4e0U);
        r_rsip_func_sub022(0x0a000100U, 0x0c003080U, 0x2000b4e0U);
        r_rsip_func_sub022(0x0a000108U, 0x0c003080U, 0x2000b4e0U);
        r_rsip_func_sub022(0x0e000500U, 0x0c003080U, 0x2000b4e0U);
        r_rsip_func_sub022(0x09000908U, 0x0c00a880U, 0xfffffffcU);
        WR1_PROG(REG_0094H, 0x2000b4e0U);
        WR1_PROG(REG_0094H, 0x07000d00U);

        r_rsip_func101(bswap_32big(0x517cf2dbU), bswap_32big(0xbd26b748U), bswap_32big(0x3172b529U),
                       bswap_32big(0x230c22b0U));

        return RSIP_RET_PASS;
    }
}
