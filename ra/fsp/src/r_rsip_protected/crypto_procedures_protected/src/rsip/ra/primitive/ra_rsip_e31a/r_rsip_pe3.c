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

rsip_ret_t r_rsip_pe3 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e30001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_HashType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3000a880U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b480U);
    WR1_PROG(REG_0094H, 0x00000001U);
    WR1_PROG(REG_0094H, 0x00000080U);

    r_rsip_func100(bswap_32big(0xe1a40fd5U),
                   bswap_32big(0x7427c89eU),
                   bswap_32big(0x9d0130cfU),
                   bswap_32big(0x60f16e3dU));
    WR1_PROG(REG_0094H, 0x00007c04U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e3U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xa7fb953eU), bswap_32big(0x44bc0be1U), bswap_32big(0x605c754aU),
                       bswap_32big(0x67bd1b55U));
        r_rsip_func407(InData_EncSecret);

        r_rsip_func101(bswap_32big(0x65b7dbb4U), bswap_32big(0x277ab49aU), bswap_32big(0x7763f886U),
                       bswap_32big(0x904505b8U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e3U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe81a78f4U), bswap_32big(0xa7d594d8U), bswap_32big(0x688a60fcU),
                       bswap_32big(0xbcf62444U));
        r_rsip_func410(InData_EncSecret);

        r_rsip_func101(bswap_32big(0x32e05708U), bswap_32big(0xea161a31U), bswap_32big(0xfc9cc7b4U),
                       bswap_32big(0xb0575584U));
    }

    r_rsip_func100(bswap_32big(0xb7dfa5c4U),
                   bswap_32big(0xe5cd1f82U),
                   bswap_32big(0x8ed38a2eU),
                   bswap_32big(0x30814f6eU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x10f86227U), bswap_32big(0xa4faabcfU), bswap_32big(0xb561e8e8U),
                       bswap_32big(0xd62753d9U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x6f50672cU), bswap_32big(0x130de3ceU), bswap_32big(0xa44634b1U),
                       bswap_32big(0x007243e7U));
        r_rsip_func103();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c200104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_009CH, 0x80010000U);
        WR1_PROG(REG_0000H, 0x03410005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0000H, 0x0001000dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x000034c0U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e3U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x6c7e7f41U), bswap_32big(0x5f38cdfbU), bswap_32big(0x216df227U),
                       bswap_32big(0x2a60fdd6U));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x01799093U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x000000e3U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x91e03df8U), bswap_32big(0x0f32e129U), bswap_32big(0xc1a4427bU),
                       bswap_32big(0x9e07ad6eU));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        r_rsip_func100(bswap_32big(0xdfead7b7U), bswap_32big(0xed8b1270U), bswap_32big(0x296d303eU),
                       bswap_32big(0x9e51777eU));
        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            r_rsip_func100(bswap_32big(0xc30c8b1dU), bswap_32big(0x31af5ac5U), bswap_32big(0xec9c41dbU),
                           bswap_32big(0x433a8f85U));

            WR1_PROG(REG_00B0H, 0x00001804U);
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xe7008d07U);
            WR1_PROG(REG_0000H, 0x00430021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_EncMsg[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_EncMsg[5]);

            r_rsip_func100(bswap_32big(0x28229124U), bswap_32big(0xbf44c2e5U), bswap_32big(0x5044d28aU),
                           bswap_32big(0x0344f9a9U));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x0c000104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x09108105U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_EncMsg[9]);

            r_rsip_func101(bswap_32big(0x94f9cc2fU), bswap_32big(0x4de088f6U), bswap_32big(0x1e15bd00U),
                           bswap_32big(0x600d8948U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func100(bswap_32big(0xa1bf7cdbU), bswap_32big(0x92f45965U), bswap_32big(0x1eb56e3bU),
                           bswap_32big(0xed421cabU));

            WR1_PROG(REG_00B0H, 0x00009806U);
            WR1_PROG(REG_00D4H, 0x40000200U);
            WR1_PROG(REG_00D0H, 0xe7008d07U);
            WR1_PROG(REG_0000H, 0x00430031U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001032U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_EncMsg[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_EncMsg[5]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_EncMsg[9]);

            r_rsip_func100(bswap_32big(0x47602c7aU), bswap_32big(0x0c69727eU), bswap_32big(0xdfb4cd70U),
                           bswap_32big(0xab4f15b9U));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x0c000104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x09108105U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_EncMsg[13]);

            r_rsip_func101(bswap_32big(0x3dae5ba0U), bswap_32big(0x69464d9bU), bswap_32big(0x0113163eU),
                           bswap_32big(0x791c28eaU));
        }

        r_rsip_func100(bswap_32big(0xa2e76b47U), bswap_32big(0xbd324860U), bswap_32big(0x2242186dU),
                       bswap_32big(0x03faff1cU));
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0008H, 0x00005006U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_EncMsg[0]);

        r_rsip_func102(bswap_32big(0x044561a1U), bswap_32big(0x1c46112bU), bswap_32big(0x14381cadU),
                       bswap_32big(0xb7a493a8U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
