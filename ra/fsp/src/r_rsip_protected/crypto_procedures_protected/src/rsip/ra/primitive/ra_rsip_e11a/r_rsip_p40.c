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
    WR1_PROG(REG_0024H, 0x00000000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_0040H, 0x00b00000U);

        r_rsip_func101(bswap_32big(0x18a76540U), bswap_32big(0x1efe0190U), bswap_32big(0x45f830b4U), bswap_32big(0xe49d1eacU));
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_0040H, 0x00b10000U);

        r_rsip_func101(bswap_32big(0x43aff45cU), bswap_32big(0x4fbbf1c7U), bswap_32big(0xf5063a7cU), bswap_32big(0xd3de6c3fU));
    }
    else if (InData_LC[0] == 0x00000002U)
    {
        WR1_PROG(REG_0040H, 0x00b20000U);

        r_rsip_func101(bswap_32big(0xcd4465dfU), bswap_32big(0xd248e542U), bswap_32big(0x0f2b75baU), bswap_32big(0x77477e00U));
    }
    else if (InData_LC[0] == 0x00000003U)
    {
        WR1_PROG(REG_0040H, 0x00b30000U);

        r_rsip_func101(bswap_32big(0xf0335eccU), bswap_32big(0x3871b7d5U), bswap_32big(0x56fd5f61U), bswap_32big(0x02d083dfU));
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_0040H, 0x00b40000U);

        r_rsip_func101(bswap_32big(0xd4ff22e8U), bswap_32big(0x9a8992d7U), bswap_32big(0x044482b8U), bswap_32big(0x5fb3568dU));
    }
    else if (InData_LC[0] == 0x00000005U)
    {
        WR1_PROG(REG_0040H, 0x00b50000U);

        r_rsip_func101(bswap_32big(0xdc69b8e1U), bswap_32big(0xc42ca9a4U), bswap_32big(0x5ccdbe97U), bswap_32big(0x79a740d6U));
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_0040H, 0x00b60000U);

        r_rsip_func101(bswap_32big(0x84af7869U), bswap_32big(0xb7d37084U), bswap_32big(0x6e1a6e29U), bswap_32big(0x9856e438U));
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_0040H, 0x00b70000U);

        r_rsip_func101(bswap_32big(0x9d0328c4U), bswap_32big(0xfb18f859U), bswap_32big(0xb73edfbfU), bswap_32big(0xca0b6303U));
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_0040H, 0x00b80000U);

        r_rsip_func101(bswap_32big(0xc88ac57fU), bswap_32big(0x139c3084U), bswap_32big(0xbc8fd1a7U), bswap_32big(0x62760011U));
    }
    else
    {
        WR1_PROG(REG_0094H, 0x38000c00U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func101(bswap_32big(0x5bc658fdU), bswap_32big(0xc358f8a7U), bswap_32big(0xdcee7e82U), bswap_32big(0x724ff081U));
    }

    r_rsip_func100(bswap_32big(0x9cc10949U), bswap_32big(0x18f1d566U), bswap_32big(0xfea8279cU), bswap_32big(0xa6fc53adU));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x5e528cbbU), bswap_32big(0x3d49fc22U), bswap_32big(0xccd0f740U), bswap_32big(0x156b69ffU));
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

        r_rsip_func101(bswap_32big(0xa7bf41d7U), bswap_32big(0xc69fac6cU), bswap_32big(0xe65f5b28U), bswap_32big(0xfd8f6cc7U));
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

        WR1_PROG(REG_00B0H, 0x00001498U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000492U);
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

        r_rsip_func100(bswap_32big(0x21bdf056U), bswap_32big(0x9377682aU), bswap_32big(0xf879e106U), bswap_32big(0x1a792e23U));
        WR1_PROG(REG_00D0H, 0x4a470044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e4704c4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0152db38U));

        WR1_PROG(REG_00D0H, 0x4a040044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e040504U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x01f7370eU));

        WR1_PROG(REG_00B0H, 0x00000493U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000494U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0078H, 0x00000202U);

        r_rsip_func102(bswap_32big(0xb9a20652U), bswap_32big(0xdc55b7ceU), bswap_32big(0xfe4e13c7U), bswap_32big(0x645b9504U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
