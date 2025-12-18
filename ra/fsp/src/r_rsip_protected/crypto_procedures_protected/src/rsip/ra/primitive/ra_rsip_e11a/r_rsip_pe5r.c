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

rsip_ret_t r_rsip_pe5r (const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[],
                        const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    r_rsip_func_sub011(0x00e50001U, 0x000000c7U, 0x80010020U);
    WR1_PROG(REG_002CH, InData_KeyType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x800100e0U, 0x0000e502U);

    r_rsip_func101(bswap_32big(0x29b0dde8U),
                   bswap_32big(0x36aba09aU),
                   bswap_32big(0xdeeebb2aU),
                   bswap_32big(0x451a71afU));
    r_rsip_func143();

    WR1_PROG(REG_0094H, 0x38000c21U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0xb5417e80U),
                   bswap_32big(0xc7419993U),
                   bswap_32big(0xe082b0dbU),
                   bswap_32big(0xa6b6ecb4U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func_sub016(0x0000b4c0U, 0x0000001bU, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000008U);

        WR1_PROG(REG_00B0H, 0x00001404U);

        r_rsip_func101(bswap_32big(0x082fe892U), bswap_32big(0x1916fb38U), bswap_32big(0xd138abc0U),
                       bswap_32big(0x8dca90daU));
    }
    else
    {
        r_rsip_func_sub016(0x0000b4c0U, 0x01b41ce9U, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_00B0H, 0x00003408U);

        r_rsip_func101(bswap_32big(0x24378872U), bswap_32big(0x8e92c9fcU), bswap_32big(0x8ae99778U),
                       bswap_32big(0xbc1cea56U));
    }

    r_rsip_func_sub002(0x800100e0U, 0x0000e502U);

    r_rsip_func101(bswap_32big(0xd9242a23U),
                   bswap_32big(0x35d25495U),
                   bswap_32big(0x04ac0285U),
                   bswap_32big(0x59970663U));
    r_rsip_func044();

    r_rsip_func_sub005(0x000000a1U, 0x08000044U, 0x00000000U);

    r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

    r_rsip_func100(bswap_32big(0x4aa291ebU),
                   bswap_32big(0x4b419fd1U),
                   bswap_32big(0x26cd32c0U),
                   bswap_32big(0xec35ab95U));
    WR1_PROG(REG_009CH, 0x81010060U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_0094H, 0x000008e7U);

    for (iLoop = 0U; iLoop < S_RAM[0]; )
    {
        r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0xf7008d05U);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

        r_rsip_func_sub009(0x00c10011U, 0x0000a4e0U);
        WR1_PROG(REG_0094H, 0x00000004U);

        r_rsip_func101(bswap_32big(0x992c72a3U), bswap_32big(0xf1d54263U), bswap_32big(0x5d1ad92cU),
                       bswap_32big(0xe7e2eb2bU));
        iLoop = iLoop + 4U;
    }

    r_rsip_func_sub010(0x380008e3U);

    r_rsip_func_sub008(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

    r_rsip_func_sub006(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0x551e2d33U),
                   bswap_32big(0x92b83dbeU),
                   bswap_32big(0xf5ab92e5U),
                   bswap_32big(0xf49c7cb1U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd403d491U), bswap_32big(0xd8220d13U), bswap_32big(0x0afafc30U),
                       bswap_32big(0x299048feU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_00F4H, 0x00000010U);

        WR1_PROG(REG_0014H, 0x000007c4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_ADDR(REG_002CH, &InData_State[0]);

        WR1_PROG(REG_00F4H, 0x00000011U);

        r_rsip_func101(bswap_32big(0x30abffcfU), bswap_32big(0x67ee3758U), bswap_32big(0xf30a99f2U),
                       bswap_32big(0xe1f34f9fU));

        return RSIP_RET_PASS;
    }
}
