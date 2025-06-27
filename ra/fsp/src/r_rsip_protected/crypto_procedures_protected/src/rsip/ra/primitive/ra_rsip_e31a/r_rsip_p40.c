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

rsip_ret_t r_rsip_p40 (const uint32_t InData_LC[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00400001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func048(InData_LC);

    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000009U);
    WR1_PROG(REG_0094H, 0x34202801U);
    WR1_PROG(REG_0094H, 0x20003401U);

    WR1_PROG(REG_0094H, 0x00007c00U);
    WR1_PROG(REG_0040H, 0x00602000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_0040H, 0x00b00000U);

        r_rsip_func101(bswap_32big(0xbb935e20U), bswap_32big(0x6e50ce70U), bswap_32big(0xeb71e41bU),
                       bswap_32big(0xf82de90fU));
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_0040H, 0x00b10000U);

        r_rsip_func101(bswap_32big(0x3873d0d6U), bswap_32big(0x085b896cU), bswap_32big(0xc93e4029U),
                       bswap_32big(0x91205c03U));
    }
    else if (InData_LC[0] == 0x00000002U)
    {
        WR1_PROG(REG_0040H, 0x00b20000U);

        r_rsip_func101(bswap_32big(0xbc5dffdaU), bswap_32big(0x78d99371U), bswap_32big(0x1667199aU),
                       bswap_32big(0xa82d2d9aU));
    }
    else if (InData_LC[0] == 0x00000003U)
    {
        WR1_PROG(REG_0040H, 0x00b30000U);

        r_rsip_func101(bswap_32big(0x8d0740b2U), bswap_32big(0x858ef57bU), bswap_32big(0xd234878dU),
                       bswap_32big(0x4bc3f558U));
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_0040H, 0x00b40000U);

        r_rsip_func101(bswap_32big(0x2383cec4U), bswap_32big(0xc84ac230U), bswap_32big(0xf78b5fb0U),
                       bswap_32big(0x848bb4b9U));
    }
    else if (InData_LC[0] == 0x00000005U)
    {
        WR1_PROG(REG_0040H, 0x00b50000U);

        r_rsip_func101(bswap_32big(0x522fb782U), bswap_32big(0x62d73b91U), bswap_32big(0x95d8785aU),
                       bswap_32big(0x038ec5d5U));
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_0040H, 0x00b60000U);

        r_rsip_func101(bswap_32big(0x6b91ea31U), bswap_32big(0x9b60c730U), bswap_32big(0xa9b6d36cU),
                       bswap_32big(0x125b7f76U));
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_0040H, 0x00b70000U);

        r_rsip_func101(bswap_32big(0x8f307de7U), bswap_32big(0x791431c7U), bswap_32big(0x61410df8U),
                       bswap_32big(0x388f2816U));
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_0040H, 0x00b80000U);

        r_rsip_func101(bswap_32big(0xbffeeb94U), bswap_32big(0x3fb8bdfeU), bswap_32big(0x23eab46aU),
                       bswap_32big(0x894936d8U));
    }
    else
    {
        WR1_PROG(REG_0094H, 0x38000c00U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A70000U);

        r_rsip_func101(bswap_32big(0x1dc66a94U), bswap_32big(0x6957c711U), bswap_32big(0xa9f07efcU),
                       bswap_32big(0xd39e6c68U));
    }

    r_rsip_func100(bswap_32big(0xf3ed8513U),
                   bswap_32big(0x2ac1dceeU),
                   bswap_32big(0xcd8910cbU),
                   bswap_32big(0xe79ba28aU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x62bba183U), bswap_32big(0xa32d1a03U), bswap_32big(0xa71a937dU),
                       bswap_32big(0x634b23b3U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000040U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x07a6f0adU), bswap_32big(0xfcd6e6d9U), bswap_32big(0x49137872U),
                       bswap_32big(0x58751beeU));
        r_rsip_func040();

        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xf7009d05U);
        WR1_PROG(REG_00D8H, 0x20000000U);
        WR1_PROG(REG_0000H, 0x00480011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xf7008d05U);
        WR1_PROG(REG_00D8H, 0x20000010U);
        WR1_PROG(REG_0000H, 0x00480011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00A0H, 0x00010000U);

        WR1_PROG(REG_00B0H, 0x000014b8U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x000004b2U);
        WR1_PROG(REG_0000H, 0x00c00005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0000H, 0x00c90005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WR1_PROG(REG_00D8H, 0x20000020U);
        WR1_PROG(REG_0000H, 0x00480011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_00D0H, 0x8c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x380fa304U), bswap_32big(0x0b35a1d2U), bswap_32big(0x62b4b939U),
                       bswap_32big(0xd5f60a03U));
        WR1_PROG(REG_00D0H, 0x4a470044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e4704c4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x01417d25U));

        WR1_PROG(REG_00D0H, 0x4a040044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e040504U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x01ed9651U));

        WR1_PROG(REG_00B0H, 0x000004b3U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x000004b4U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0078H, 0x00000222U);

        r_rsip_func102(bswap_32big(0xee238fedU), bswap_32big(0xbe5722e3U), bswap_32big(0x2af56f54U),
                       bswap_32big(0xd5e1f3c3U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
