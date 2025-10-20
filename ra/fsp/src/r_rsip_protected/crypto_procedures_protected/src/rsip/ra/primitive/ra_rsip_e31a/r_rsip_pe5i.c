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

rsip_ret_t r_rsip_pe5i (const uint32_t InData_KeyType[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_MsgLen[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00e50001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000001c7U);
    WR1_PROG(REG_009CH, 0x80010020U);
    WAIT_STS(REG_0014H, 31, 1);
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
    WR1_PROG(REG_0094H, 0x3420a880U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x2000b480U);
    WR1_PROG(REG_0094H, 0x00000001U);

    WR1_PROG(REG_0094H, 0x00007c04U);
    WR1_PROG(REG_0040H, 0x00600000U);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_00F4H, 0x00000050U);

        r_rsip_func101(bswap_32big(0xf5501d62U), bswap_32big(0x482fdfeaU), bswap_32big(0x253adad7U),
                       bswap_32big(0x5a97f568U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_00F4H, 0x000000a0U);

        r_rsip_func101(bswap_32big(0x3f4970c6U), bswap_32big(0xdf9d5e9eU), bswap_32big(0xea6528ecU),
                       bswap_32big(0xa72e1b45U));
    }

    WR1_PROG(REG_00F8H, 0x00000003U);

    WR1_PROG(REG_0094H, 0x38000c21U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xaa99615fU),
                   bswap_32big(0xc448ff0dU),
                   bswap_32big(0x1734e0ceU),
                   bswap_32big(0xdf9f7ffeU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x30003080U);
        WR1_PROG(REG_0094H, 0x00070020U);

        WR1_PROG(REG_0094H, 0x0000b4a0U);
        WR1_PROG(REG_0094H, 0x0000001bU);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000008U);

        WR1_PROG(REG_0094H, 0x00030040U);

        WR1_PROG(REG_0094H, 0x0000b4a0U);
        WR1_PROG(REG_0094H, 0x00000028U);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x0000000cU);

        WR1_PROG(REG_0094H, 0x00000080U);
        r_rsip_func101(bswap_32big(0x5176d14dU), bswap_32big(0x2df6c7e9U), bswap_32big(0x2ccdf0a8U),
                       bswap_32big(0x44cf8bfdU));
    }
    else
    {
        WR1_PROG(REG_0094H, 0x30003080U);
        WR1_PROG(REG_0094H, 0x00070020U);

        WR1_PROG(REG_0094H, 0x0000b4a0U);
        WR1_PROG(REG_0094H, 0x01b41ce9U);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_0094H, 0x00030040U);

        WR1_PROG(REG_0094H, 0x0000b4a0U);
        WR1_PROG(REG_0094H, 0x0199f119U);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);

        WR1_PROG(REG_0094H, 0x00000080U);
        r_rsip_func101(bswap_32big(0x9b87e1eaU), bswap_32big(0xca0b3f0eU), bswap_32big(0x52f71078U),
                       bswap_32big(0x9302377dU));
    }

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000e501U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xee48d1b3U),
                   bswap_32big(0x2c825c02U),
                   bswap_32big(0x19f46de3U),
                   bswap_32big(0xbc7b0d5fU));
    r_rsip_func143();

    WR1_PROG(REG_0094H, 0x000034c5U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000e501U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc89d9494U),
                   bswap_32big(0xc9d9bd19U),
                   bswap_32big(0xfbe84003U),
                   bswap_32big(0xd38dc5acU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xc97ec6afU),
                   bswap_32big(0x35d6fb6eU),
                   bswap_32big(0xc9031329U),
                   bswap_32big(0xe01158e3U));
    WR1_PROG(REG_009CH, 0x81010060U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_0094H, 0x000008e7U);
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000044U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000054U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    for (iLoop = 0U; iLoop < S_RAM[0]; )
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

        r_rsip_func101(bswap_32big(0xf2ea9863U), bswap_32big(0x7e6ca7eeU), bswap_32big(0x1129ef93U),
                       bswap_32big(0x09af1d95U));
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

    r_rsip_func100(bswap_32big(0x550d97c7U),
                   bswap_32big(0xaf79750bU),
                   bswap_32big(0x96508788U),
                   bswap_32big(0xc7fe7542U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x6d220011U), bswap_32big(0x7b64b947U), bswap_32big(0xf90c9a5aU),
                       bswap_32big(0xd81491edU));
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

            r_rsip_func101(bswap_32big(0x116c7367U), bswap_32big(0x0e9747a7U), bswap_32big(0x1b721addU),
                           bswap_32big(0xde8599daU));
        }
        else
        {
            WR1_PROG(REG_0014H, 0x00000040U);
            WR1_PROG(REG_0104H, InData_MsgLen[0]);
            WR1_PROG(REG_0014H, 0x00000040U);
            WR1_PROG(REG_0100H, InData_MsgLen[1]);

            WR1_PROG(REG_00FCH, 0x00000001U);

            r_rsip_func101(bswap_32big(0x285e6963U), bswap_32big(0x506c24e5U), bswap_32big(0x3565c57dU),
                           bswap_32big(0x0296bb93U));
        }

        return RSIP_RET_PASS;
    }
}
