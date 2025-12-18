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

    r_rsip_func_sub011(0x00470001U, 0x000000c7U, 0x80010080U);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000005U);

    r_rsip_func_sub002(0x800100e0U, 0x00004701U);

    r_rsip_func101(bswap_32big(0x89beb64eU),
                   bswap_32big(0x3ffeaa00U),
                   bswap_32big(0xff853c24U),
                   bswap_32big(0x36f22cf5U));
    r_rsip_func440(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x9d18ff63U),
                   bswap_32big(0x1a5a2b27U),
                   bswap_32big(0x6a3d35daU),
                   bswap_32big(0x1b27fe61U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xeeb47652U), bswap_32big(0xbb5940a2U), bswap_32big(0xf35f73e4U),
                       bswap_32big(0x4bef9c17U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub004(0x00000801U, 0x03430009U);

        r_rsip_func_sub004(0x00000802U, 0x03430009U);

        r_rsip_func_sub007(0x3c00a880U, 0x00000002U, 0x00260000U);

        r_rsip_func100(bswap_32big(0x400be8c1U), bswap_32big(0x6e618a49U), bswap_32big(0x4241298bU),
                       bswap_32big(0x9023cfbcU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x000008a5U);

            r_rsip_func_sub007(0x3c00a880U, 0x00000004U, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x56753d83U), bswap_32big(0x5240cea3U), bswap_32big(0xef200f5fU),
                           bswap_32big(0x51ac6be1U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0014H, 0x000000c7U);
                WR1_PROG(REG_009CH, 0x800100a0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_IVType[0]);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x5d9fcdf1U),
                               bswap_32big(0x9dd4726bU),
                               bswap_32big(0x233b31a6U),
                               bswap_32big(0xb0de3b90U));
            }

            WR1_PROG(REG_0094H, 0x38000ca5U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            r_rsip_func100(bswap_32big(0x1dd74c0bU), bswap_32big(0xf32a31c3U), bswap_32big(0x3a12388cU),
                           bswap_32big(0xc29890e7U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0014H, 0x000003c1U);
                WR1_PROG(REG_00D0H, 0x08000045U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_IV[0]);

                r_rsip_func101(bswap_32big(0xa81bbbfbU),
                               bswap_32big(0x03018856U),
                               bswap_32big(0xf59bf5d1U),
                               bswap_32big(0x11bc7193U));
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b4a0U);
                WR1_PROG(REG_0094H, 0x0199e556U);

                r_rsip_func_sub002(0x800100e0U, 0x00004702U);

                r_rsip_func101(bswap_32big(0xa62acae2U),
                               bswap_32big(0x974c50b8U),
                               bswap_32big(0xeb00ed12U),
                               bswap_32big(0x7d082c62U));
                r_rsip_func440(InData_IV);

                r_rsip_func100(bswap_32big(0x5893b71eU),
                               bswap_32big(0xac524a26U),
                               bswap_32big(0x740ab7ecU),
                               bswap_32big(0x719f0918U));
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0xef05461dU),
                                   bswap_32big(0xa519fee3U),
                                   bswap_32big(0x9be7e360U),
                                   bswap_32big(0x59bdbf9bU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    WR1_PROG(REG_00D0H, 0x08000045U);
                    r_rsip_func_sub004(0x00000801U, 0x00430009U);

                    r_rsip_func_sub004(0x00000802U, 0x00430009U);

                    r_rsip_func101(bswap_32big(0x86ca016eU),
                                   bswap_32big(0xe34b26a2U),
                                   bswap_32big(0x952fb08bU),
                                   bswap_32big(0x78806a9eU));
                }
            }
        }

        r_rsip_func100(bswap_32big(0x094b147eU), bswap_32big(0x71fafd08U), bswap_32big(0x9ff19d62U),
                       bswap_32big(0x1688ba74U));
        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub003(0x81840000U, 0x00490011U);

        r_rsip_func_sub016(0x0c003080U, 0x2000b4e0U, 0x0a000100U);

        r_rsip_func_sub016(0x0c003080U, 0x2000b4e0U, 0x0a000108U);

        r_rsip_func_sub016(0x0c003080U, 0x2000b4e0U, 0x0e000500U);

        r_rsip_func_sub016(0x0c003080U, 0x2000b4e0U, 0x09000908U);

        r_rsip_func_sub016(0x0c00a880U, 0xfffffffcU, 0x2000b4e0U);
        WR1_PROG(REG_0094H, 0x07000d00U);

        r_rsip_func101(bswap_32big(0x1392f00aU), bswap_32big(0xe0f57f43U), bswap_32big(0xac6a07daU),
                       bswap_32big(0x6837ad20U));

        return RSIP_RET_PASS;
    }
}
