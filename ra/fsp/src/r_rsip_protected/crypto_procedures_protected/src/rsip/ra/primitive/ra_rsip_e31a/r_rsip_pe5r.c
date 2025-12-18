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

rsip_ret_t r_rsip_pe5r (const uint32_t InData_KeyType[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e50001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func_sub014(0x000001c7U, 0x80010020U);
    WR1_PROG(REG_002CH, InData_KeyType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);

    WR1_PROG(REG_00F0H, 0x00000001U);

    r_rsip_func100(bswap_32big(0xb8f450beU),
                   bswap_32big(0xc16aa67aU),
                   bswap_32big(0x12ac29b5U),
                   bswap_32big(0x3908380bU));
    r_rsip_func_sub022(0x3420a880U, 0x00000002U, 0x2000b480U);
    WR1_PROG(REG_0094H, 0x00000001U);

    WR1_PROG(REG_0094H, 0x00007c04U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_00F4H, 0x00001050U);

        r_rsip_func101(bswap_32big(0xca4c1d5bU), bswap_32big(0x923c10a7U), bswap_32big(0x64c6d2e1U),
                       bswap_32big(0x87ecec95U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_00F4H, 0x000010a0U);

        r_rsip_func101(bswap_32big(0xdd8bd317U), bswap_32big(0x0cd1fb7fU), bswap_32big(0x6c80e87cU),
                       bswap_32big(0x2d720456U));
    }

    WR1_PROG(REG_00F8H, 0x00000003U);

    r_rsip_func_sub016(0x38000c21U, 0x00000080U, 0x00270000U);

    r_rsip_func100(bswap_32big(0x61749c53U),
                   bswap_32big(0xce0f44f0U),
                   bswap_32big(0xd685fa7eU),
                   bswap_32big(0xb2ccbab7U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func_sub022(0x30003080U, 0x00070020U, 0x0000b4a0U);
        r_rsip_func_sub022(0x0000001bU, 0x0000b460U, 0x00000008U);

        r_rsip_func_sub022(0x00030040U, 0x0000b4a0U, 0x00000028U);

        r_rsip_func_sub022(0x0000b460U, 0x0000000cU, 0x00000080U);
        r_rsip_func101(bswap_32big(0xda41a285U), bswap_32big(0x7463d39aU), bswap_32big(0xc4a415e6U),
                       bswap_32big(0x0b6fe281U));
    }
    else
    {
        r_rsip_func_sub022(0x30003080U, 0x00070020U, 0x0000b4a0U);
        r_rsip_func_sub022(0x01b41ce9U, 0x0000b460U, 0x00000010U);

        r_rsip_func_sub022(0x00030040U, 0x0000b4a0U, 0x0199f119U);

        r_rsip_func_sub022(0x0000b460U, 0x00000010U, 0x00000080U);
        r_rsip_func101(bswap_32big(0xf28b702cU), bswap_32big(0xba0877e3U), bswap_32big(0xf7f64d0eU),
                       bswap_32big(0x42a81579U));
    }

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e502U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xfec019d1U),
                   bswap_32big(0x4b6a4fd9U),
                   bswap_32big(0x19d1fa38U),
                   bswap_32big(0xf45fed78U));
    r_rsip_func143();

    WR1_PROG(REG_0094H, 0x000034c5U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000e502U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x98ae13c9U),
                   bswap_32big(0xf9f5030fU),
                   bswap_32big(0x25eac4aeU),
                   bswap_32big(0x677f07c3U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xd2d7435aU),
                   bswap_32big(0xa934fb56U),
                   bswap_32big(0xa407bbcbU),
                   bswap_32big(0xccbc6fbdU));
    r_rsip_func_sub017(0x81010060U, 0x00005006U);
    RD1_ADDR(REG_002CH, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_0094H, 0x000008e7U);
    r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

    r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

    for (iLoop = 0U; iLoop < S_RAM[0]; )
    {
        r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0xf7008d05U);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

        r_rsip_func_sub015(0x01410011U, 0x00001800U);

        WR1_PROG(REG_0094H, 0x0000a4e0U);
        WR1_PROG(REG_0094H, 0x00000004U);

        r_rsip_func101(bswap_32big(0x1872c64bU), bswap_32big(0xff41ca58U), bswap_32big(0x5f4d081bU),
                       bswap_32big(0x6eeeabf7U));
        iLoop = iLoop + 4U;
    }

    r_rsip_func_sub016(0x380008e3U, 0x00000080U, 0x00270000U);
    WR1_PROG(REG_0040H, 0x00402000U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0x5cf1bb7dU),
                   bswap_32big(0x107bcb74U),
                   bswap_32big(0x70b84c97U),
                   bswap_32big(0xa8a75f1fU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xbf07d12eU), bswap_32big(0xa977d358U), bswap_32big(0x384e5b20U),
                       bswap_32big(0xabc67136U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x00000040U);
        WR1_PROG(REG_0104H, InData_State[18]);
        WR1_PROG(REG_0014H, 0x00000040U);
        WR1_PROG(REG_0100H, InData_State[19]);

        for (iLoop = 0U; iLoop < 18U; iLoop++)
        {
            WR1_PROG(REG_0014H, 0x00000040U);
            WR1_PROG(REG_0110H, InData_State[iLoop]);
        }

        r_rsip_func101(bswap_32big(0x60c93849U), bswap_32big(0x882a816dU), bswap_32big(0xd523a23aU),
                       bswap_32big(0x73e2c8a8U));

        return RSIP_RET_PASS;
    }
}
