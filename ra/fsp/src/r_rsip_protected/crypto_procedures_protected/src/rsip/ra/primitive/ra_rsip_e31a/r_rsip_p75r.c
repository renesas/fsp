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

rsip_ret_t r_rsip_p75r (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_State[],
                        uint32_t       KEY_INDEX_SIZE)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00750001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00F0H, 0x00000001U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c84U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xae3bd963U),
                   bswap_32big(0xc869c403U),
                   bswap_32big(0xcf65a101U),
                   bswap_32big(0x1f1d6f52U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x53fd1f1bU), bswap_32big(0x13766c3cU), bswap_32big(0xc218a604U),
                       bswap_32big(0xa85d6961U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x9238ce2eU), bswap_32big(0x2429959bU), bswap_32big(0x91b7ec51U),
                       bswap_32big(0x19e3bc75U));
        WR1_PROG(REG_0094H, 0x3420a880U);
        WR1_PROG(REG_0094H, 0x00000007U);
        WR1_PROG(REG_0094H, 0x2000b480U);
        WR1_PROG(REG_0094H, 0x00000006U);

        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0000001bU);

            WR1_PROG(REG_00F4H, 0x00001050U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000008U);

            r_rsip_func101(bswap_32big(0x068ac4abU), bswap_32big(0xf04f8124U), bswap_32big(0x5aee3aebU),
                           bswap_32big(0x22a1823fU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0000002aU);

            WR1_PROG(REG_00F4H, 0x00001080U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            r_rsip_func101(bswap_32big(0x13f00984U), bswap_32big(0xb528baafU), bswap_32big(0x6c80d8b5U),
                           bswap_32big(0x0cfac5d6U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0000002bU);

            WR1_PROG(REG_00F4H, 0x00001090U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            r_rsip_func101(bswap_32big(0x7aaf6a21U), bswap_32big(0x872b6262U), bswap_32big(0xdb62f002U),
                           bswap_32big(0x96710dbaU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000028U);

            WR1_PROG(REG_00F4H, 0x000010a0U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x0000000cU);

            r_rsip_func101(bswap_32big(0x20facd08U), bswap_32big(0x776721a3U), bswap_32big(0x4f1af50eU),
                           bswap_32big(0x41a1c91dU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000029U);

            WR1_PROG(REG_00F4H, 0x000010b0U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            r_rsip_func101(bswap_32big(0xd411f561U), bswap_32big(0xd16b9fe4U), bswap_32big(0x2a3cd832U),
                           bswap_32big(0xcff03f26U));
        }

        WR1_PROG(REG_00F8H, 0x00000003U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_KeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00007502U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x74ccdb99U), bswap_32big(0x05bfde35U), bswap_32big(0x8a8e594eU),
                       bswap_32big(0x2fb037a4U));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x000034c5U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00007502U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x513a8451U), bswap_32big(0x04789632U), bswap_32big(0x6e70b29fU),
                       bswap_32big(0xea9577f0U));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0094H, 0x000008e7U);

        for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xf7008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

            WR1_PROG(REG_0000H, 0x01410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x0000a4e0U);
            WR1_PROG(REG_0094H, 0x00000004U);

            r_rsip_func101(bswap_32big(0xff7d31acU), bswap_32big(0xe42f3c48U), bswap_32big(0xe283cd98U),
                           bswap_32big(0x9ba9a892U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_0094H, 0x380008e3U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0040H, 0x00402000U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x28a4fc56U), bswap_32big(0x4a87ab13U), bswap_32big(0x346ce4d2U),
                       bswap_32big(0xb3b9cb3eU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xe4253cddU), bswap_32big(0x1f47ebc9U), bswap_32big(0x111897ecU),
                           bswap_32big(0x99583903U));
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

            r_rsip_func101(bswap_32big(0x3ae6a95eU), bswap_32big(0xd5daec92U), bswap_32big(0x5c2c54c8U),
                           bswap_32big(0x834efad2U));

            return RSIP_RET_PASS;
        }
    }
}
