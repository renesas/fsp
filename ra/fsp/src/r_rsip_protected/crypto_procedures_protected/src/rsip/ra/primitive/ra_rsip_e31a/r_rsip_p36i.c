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

rsip_ret_t r_rsip_p36i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00360001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000036U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xb7b71427U),
                   bswap_32big(0xa2cf9c70U),
                   bswap_32big(0x8f087e9dU),
                   bswap_32big(0x8f09c320U));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x7f529053U),
                   bswap_32big(0x25e4bb5eU),
                   bswap_32big(0x418cd06cU),
                   bswap_32big(0x32ba2b80U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x57724a11U), bswap_32big(0xfbf7caf7U), bswap_32big(0xec002050U),
                       bswap_32big(0x27eb5b2eU));
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

        r_rsip_func100(bswap_32big(0x3a39e70cU), bswap_32big(0x0d535567U), bswap_32big(0x44657cd6U),
                       bswap_32big(0x31870adbU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func_sub019(0x000003c1U, 0x08000105U);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func_sub009(0x00000401U, 0x00c10009U, 0x00001800U);

            r_rsip_func_sub009(0x00000402U, 0x00c10009U, 0x00001800U);

            r_rsip_func101(bswap_32big(0x14443888U), bswap_32big(0xf1acef5dU), bswap_32big(0xa78ddf29U),
                           bswap_32big(0xa9ac2093U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000036U, 0x00000000U);

            r_rsip_func101(bswap_32big(0x8f2dd865U), bswap_32big(0x32a832abU), bswap_32big(0x2f67a368U),
                           bswap_32big(0xa2ee7a07U));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0xdec43c01U), bswap_32big(0xa0414286U), bswap_32big(0x6b91767aU),
                           bswap_32big(0x7e9dbaa2U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x960e50e5U),
                               bswap_32big(0x6822a99eU),
                               bswap_32big(0x027ff071U),
                               bswap_32big(0x8c81d42eU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xc8eb1b49U),
                               bswap_32big(0x60996205U),
                               bswap_32big(0x8f82cb22U),
                               bswap_32big(0x56f3df11U));
            }
        }

        r_rsip_func100(bswap_32big(0x693c3db2U), bswap_32big(0x65e164a3U), bswap_32big(0xf5edfdccU),
                       bswap_32big(0x20863ef3U));
        WR1_PROG(REG_00D0H, 0x08000085U);
        r_rsip_func_sub009(0x0000181eU, 0x00430011U, 0x00001800U);

        r_rsip_func100(bswap_32big(0xb9c383edU), bswap_32big(0x53b726a8U), bswap_32big(0xf0869f7fU),
                       bswap_32big(0xb859ffa5U));
        r_rsip_func_sub013(0x08000095U, 0x00430011U);

        WR1_PROG(REG_0094H, 0x0000b400U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_009CH, 0x80840000U);
        r_rsip_func_sub009(0x00000801U, 0x03430009U, 0x00001800U);

        r_rsip_func_sub009(0x00000802U, 0x03430009U, 0x00001800U);

        r_rsip_func100(bswap_32big(0x0834eb01U), bswap_32big(0x69b92ee9U), bswap_32big(0x527f27d9U),
                       bswap_32big(0x7b0aad13U));
        r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func_sub011(0x000000a1U, 0x40000000U, 0x0a0080a4U);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func101(bswap_32big(0x9797d0aeU), bswap_32big(0x848281a1U), bswap_32big(0xadacbc43U),
                       bswap_32big(0x756dbbc8U));

        return RSIP_RET_PASS;
    }
}
