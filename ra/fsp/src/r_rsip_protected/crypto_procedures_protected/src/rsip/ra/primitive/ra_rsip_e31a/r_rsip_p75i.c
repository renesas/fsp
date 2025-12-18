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

rsip_ret_t r_rsip_p75i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_MsgLen[],
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

    r_rsip_func_sub014(0x000000c7U, 0x80010080U);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub016(0x38000c84U, 0x00000080U, 0x00270000U);

    r_rsip_func_sub010(0x38008880U, 0x00000001U, 0x00270000U);

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
        r_rsip_func_sub022(0x3420a880U, 0x00000007U, 0x2000b480U);
        WR1_PROG(REG_0094H, 0x00000006U);

        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0000001bU);

            WR1_PROG(REG_00F4H, 0x00000050U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000008U);

            r_rsip_func101(bswap_32big(0x2b723a84U), bswap_32big(0xba4128faU), bswap_32big(0xf722af91U),
                           bswap_32big(0x2ae8c4c3U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0000002aU);

            WR1_PROG(REG_00F4H, 0x00000080U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            r_rsip_func101(bswap_32big(0xb5f16690U), bswap_32big(0x50a660a0U), bswap_32big(0xdddc9164U),
                           bswap_32big(0xa8a05b9bU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0000002bU);

            WR1_PROG(REG_00F4H, 0x00000090U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            r_rsip_func101(bswap_32big(0x0aa2e0c7U), bswap_32big(0x8379a578U), bswap_32big(0xa6526e03U),
                           bswap_32big(0xfd466546U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000028U);

            WR1_PROG(REG_00F4H, 0x000000a0U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x0000000cU);

            r_rsip_func101(bswap_32big(0x831c23d6U), bswap_32big(0x2140f211U), bswap_32big(0xe0c14795U),
                           bswap_32big(0x3233aa40U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x00000029U);

            WR1_PROG(REG_00F4H, 0x000000b0U);

            WR1_PROG(REG_0094H, 0x0000b460U);
            WR1_PROG(REG_0094H, 0x00000010U);

            r_rsip_func101(bswap_32big(0xc2e7b9d1U), bswap_32big(0xbd87df08U), bswap_32big(0xe14cd45aU),
                           bswap_32big(0x211c22b9U));
        }

        WR1_PROG(REG_00F8H, 0x00000003U);

        r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
        WR1_PROG(REG_002CH, InData_KeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00007501U, 0x00000000U);

        r_rsip_func101(bswap_32big(0xacf022a5U), bswap_32big(0x07c42451U), bswap_32big(0x9f816f4bU),
                       bswap_32big(0x11386d85U));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x000034c5U);

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00007501U, 0x00000000U);

        r_rsip_func101(bswap_32big(0x60c789abU), bswap_32big(0x8e2031a2U), bswap_32big(0x98ca8558U),
                       bswap_32big(0xc355cdb2U));
        r_rsip_func044();

        r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

        r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

        WR1_PROG(REG_0094H, 0x000008e7U);

        for (iLoop = 0U; iLoop < KEY_INDEX_SIZE - 5; )
        {
            r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0xf7008d05U);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

            r_rsip_func_sub015(0x01410011U, 0x00001800U);

            WR1_PROG(REG_0094H, 0x0000a4e0U);
            WR1_PROG(REG_0094H, 0x00000004U);

            r_rsip_func101(bswap_32big(0x9da72476U), bswap_32big(0xff56a61fU), bswap_32big(0xdff477c7U),
                           bswap_32big(0x843912f8U));
            iLoop = iLoop + 4U;
        }

        r_rsip_func_sub016(0x380008e3U, 0x00000080U, 0x00270000U);

        WR1_PROG(REG_0040H, 0x00402000U);

        r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[iLoop + 1]);

        r_rsip_func_sub013(0x9c100005U, 0x00410011U);

        r_rsip_func100(bswap_32big(0x0be32cddU), bswap_32big(0x341b860dU), bswap_32big(0xd4971ee4U),
                       bswap_32big(0xbe51fb72U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x7c5c0744U), bswap_32big(0x77438172U), bswap_32big(0xc1a0ca04U),
                           bswap_32big(0x6ab6edf0U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
            {
                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0104H, 0x00000000U);
                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0100H, 0x00000080U);

                WR1_PROG(REG_00FCH, 0x00000001U);

                WAIT_STS(REG_0118H, 8, 0);

                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0104H, 0x00000000U);
                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0100H, 0x00000000U);

                WR1_PROG(REG_00FCH, 0x00000100U);

                r_rsip_func101(bswap_32big(0x6e5c33e1U),
                               bswap_32big(0xe49c58f8U),
                               bswap_32big(0x31bf34a5U),
                               bswap_32big(0xc5765540U));
            }
            else
            {
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0104H, InData_MsgLen[0]);
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0100H, InData_MsgLen[1]);

                WR1_PROG(REG_00FCH, 0x00000001U);

                r_rsip_func101(bswap_32big(0x5beb7ff6U),
                               bswap_32big(0xb414cb51U),
                               bswap_32big(0x782e3f68U),
                               bswap_32big(0xcecbdf49U));
            }

            return RSIP_RET_PASS;
        }
    }
}
