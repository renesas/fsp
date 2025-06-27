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

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_p6f (const uint32_t InData_LC[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_InstData[],
                       uint32_t       OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x006f0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func048(InData_LC);

    WR1_PROG(REG_00A0H, 0x00010000U);

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000001cU);

    WR1_PROG(REG_00B0H, 0x00000892U);
    WR1_PROG(REG_009CH, 0x80810006U);
    WR1_PROG(REG_0000H, 0x00030005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0000H, 0x03430005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func049(InData_Cmd);

    WR1_PROG(REG_0094H, 0x00000842U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000009U);
    WR1_PROG(REG_0094H, 0x1000b440U);
    WR1_PROG(REG_0094H, 0x3CC003A0U);

    WR1_PROG(REG_0094H, 0x000034a4U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000023U);
    WR1_PROG(REG_0094H, 0x1000b480U);
    WR1_PROG(REG_0094H, 0x00000005U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000022U);
    WR1_PROG(REG_0094H, 0x1000b480U);
    WR1_PROG(REG_0094H, 0x00000005U);

    r_rsip_func056();

    r_rsip_func100(bswap_32big(0x22cbd607U),
                   bswap_32big(0xe3efefb1U),
                   bswap_32big(0x1eb4c4ccU),
                   bswap_32big(0xa378629eU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x0253d334U), bswap_32big(0xd7186086U), bswap_32big(0x589548bfU),
                       bswap_32big(0xd4c0f040U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003485U);

        WR1_PROG(REG_0014H, 0x000001a1U);
        WR1_PROG(REG_00D0H, 0x07330c04U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x07330d04U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_009CH, 0x80010000U);
        WR1_PROG(REG_0000H, 0x03410005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0000H, 0x0001000dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000001a1U);
        WR1_PROG(REG_00D0H, 0x07330d04U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x06330104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00B0H, 0x00001404U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, S_INST2[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000006fU));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x8723d0efU), bswap_32big(0xddc7be4cU), bswap_32big(0xe54ff9eeU),
                       bswap_32big(0x59281880U));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x000000ffU);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000006fU));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x9a6619b9U), bswap_32big(0xac02b550U), bswap_32big(0xde28ce32U),
                       bswap_32big(0x540817c1U));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0xb67ae076U), bswap_32big(0xa2302888U), bswap_32big(0xc2132e3fU),
                       bswap_32big(0xa88beb00U));
        WR1_PROG(REG_0014H, 0x000007c1U);
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xf7009d07U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &S_INST2[0 + 1]);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &S_INST2[0 + 5]);

        WR1_PROG(REG_00D0H, 0x080000a5U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x820c73e1U), bswap_32big(0x42ab1dcfU), bswap_32big(0xb53d6407U),
                       bswap_32big(0xaad627d1U));
        WR1_PROG(REG_00D0H, 0x080000b5U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &S_INST2[0 + 9]);

        WR1_PROG(REG_00D0H, 0x8c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000006fU));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x332001c2U), bswap_32big(0x82dbf299U), bswap_32big(0xe89d6799U),
                       bswap_32big(0x943c64e0U));
        r_rsip_func057(InData_IV, InData_InstData, OutData_KeyIndex);

        r_rsip_func100(bswap_32big(0xdca87a2dU), bswap_32big(0xb22b908bU), bswap_32big(0xc793f014U),
                       bswap_32big(0x06d24e3bU));
        WR1_PROG(REG_00B0H, 0x00001804U);

        WR1_PROG(REG_00D0H, 0x080000b5U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D0H, 0x08000075U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x44871b27U), bswap_32big(0xb7e2c72eU), bswap_32big(0xa9eff8dfU),
                       bswap_32big(0x386c6797U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x6eb1c767U), bswap_32big(0xfa909053U), bswap_32big(0xa95e487fU),
                           bswap_32big(0xec14938eU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xa73cfa0bU), bswap_32big(0xd353256aU), bswap_32big(0x2c0398d6U),
                           bswap_32big(0x51b43811U));
            WR1_PROG(REG_009CH, 0x81010000U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

            r_rsip_func102(bswap_32big(0x68bcb25eU), bswap_32big(0x64dcf4ddU), bswap_32big(0x3e4fac0eU),
                           bswap_32big(0x9a8368d0U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
