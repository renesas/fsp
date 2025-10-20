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

rsip_ret_t r_rsip_pa1i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[],
                        const uint32_t InData_Header[],
                        uint32_t       Header_Len)
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00a10001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, 0x00000007U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000a1U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x22302275U),
                   bswap_32big(0x49226d9fU),
                   bswap_32big(0xce987bd4U),
                   bswap_32big(0x399cc35fU));
    r_rsip_func441(InData_KeyIndex);

    r_rsip_func100(bswap_32big(0x2f50e473U),
                   bswap_32big(0xa4c566cdU),
                   bswap_32big(0x293a0c6eU),
                   bswap_32big(0x5ace7e66U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x9735d668U), bswap_32big(0x38a63afbU), bswap_32big(0x22646ffaU),
                       bswap_32big(0xf522f862U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010080U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IVType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0x3bd23a55U), bswap_32big(0x3ca67f54U), bswap_32big(0x9bc4fb87U),
                       bswap_32big(0x7d538c13U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            r_rsip_func101(bswap_32big(0xac92b4e3U), bswap_32big(0x78aa40b9U), bswap_32big(0xda8e6feaU),
                           bswap_32big(0xb8e3dec7U));
        }
        else
        {
            WR1_PROG(REG_0094H, 0x0000b4a0U);
            WR1_PROG(REG_0094H, 0x0199e556U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000a1U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xca247e08U), bswap_32big(0x75b11917U), bswap_32big(0xda00d62cU),
                           bswap_32big(0xbd2dfdacU));
            r_rsip_func440(InData_IV);

            r_rsip_func100(bswap_32big(0x864fb30aU), bswap_32big(0x5c0ed444U), bswap_32big(0x097f03d7U),
                           bswap_32big(0x5524d05fU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xa8de2ebdU),
                               bswap_32big(0x3b17eb4eU),
                               bswap_32big(0x9b63a096U),
                               bswap_32big(0xa7885e70U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00D0H, 0x08000045U);
                WR1_PROG(REG_00B0H, 0x00000801U);
                WR1_PROG(REG_0000H, 0x00430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00000802U);
                WR1_PROG(REG_0000H, 0x00430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0x35ea48ddU),
                               bswap_32big(0x101f9735U),
                               bswap_32big(0x5da2c3f1U),
                               bswap_32big(0xe8fc5ce9U));
            }
        }

        r_rsip_func100(bswap_32big(0xc9499d65U), bswap_32big(0xba80ee68U), bswap_32big(0x10454215U),
                       bswap_32big(0xcb218c48U));
        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_00B0H, 0x0000181eU);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0xfcb7219cU), bswap_32big(0x3cda4615U), bswap_32big(0x672505f6U),
                       bswap_32big(0x1f198156U));
        WR1_PROG(REG_00D0H, 0x08000095U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        r_rsip_func501(InData_Header, Header_Len);

        r_rsip_func101(bswap_32big(0xa0999066U), bswap_32big(0x4c0ad98aU), bswap_32big(0x92e42675U),
                       bswap_32big(0x715cfb95U));

        return RSIP_RET_PASS;
    }
}
