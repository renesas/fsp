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

rsip_ret_t r_rsip_pf0 (const uint32_t InData_CurveType[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_Signature[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f00001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);

    r_rsip_func070(InData_DomainParam);

    r_rsip_func100(bswap_32big(0x34c3e345U),
                   bswap_32big(0xd4967a3eU),
                   bswap_32big(0x9640d322U),
                   bswap_32big(0x03bb67adU));

    WR1_PROG(REG_00B0H, 0x0000140fU);
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x9c3e1fbdU),
                   bswap_32big(0xed3fc243U),
                   bswap_32big(0x30aa6952U),
                   bswap_32big(0x89d69956U));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00001428U);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B0H, 0x00001419U);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

    WR1_PROG(REG_00B4H, 0x0019000aU);
    WR1_PROG(REG_00B8H, 0x00140000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B8H, 0x00000014U);

    WR1_PROG(REG_00A4H, 0x04040010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028000fU);
    WR1_PROG(REG_00B8H, 0x002d0014U);

    WR1_PROG(REG_00A4H, 0x04040002U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028002dU);
    WR1_PROG(REG_00B8H, 0x00320000U);

    WR1_PROG(REG_00A4H, 0x04040009U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    r_rsip_func071(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000f0U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x258f6197U),
                   bswap_32big(0xfd1ab13bU),
                   bswap_32big(0x45e121b7U),
                   bswap_32big(0x1da6fa29U));
    r_rsip_func088();

    r_rsip_func100(bswap_32big(0xc5c60ce9U),
                   bswap_32big(0x7369d5d6U),
                   bswap_32big(0x3bd7a56eU),
                   bswap_32big(0x11781508U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x12087763U), bswap_32big(0xd9aa88b7U), bswap_32big(0xfe29156bU),
                       bswap_32big(0xc687bf72U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_00B8H, 0x0000000aU);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x005a0028U);
        WR1_PROG(REG_00B8H, 0x002d000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0014H, 0x000000a5U);
        WR1_PROG(REG_00B0H, 0x0000140fU);
        WR1_PROG(REG_0000H, 0x00c0001dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x000f002dU);
        WR1_PROG(REG_00B8H, 0x0028000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x000f0028U);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x96939109U), bswap_32big(0xb9ec7100U), bswap_32big(0x1a257696U),
                       bswap_32big(0x1d6d486dU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x52bc1482U), bswap_32big(0x00d6d89bU), bswap_32big(0xe8cbc722U),
                           bswap_32big(0x573432d9U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xecbf2ea1U), bswap_32big(0x7447c70bU), bswap_32big(0x583093a0U),
                           bswap_32big(0x7325cb8dU));
            WR1_PROG(REG_00B0H, 0x00001414U);
            WR1_PROG(REG_0000H, 0x00c0001dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

            WR1_PROG(REG_00B4H, 0x0014000aU);
            WR1_PROG(REG_00B8H, 0x000f0000U);

            WR1_PROG(REG_00A4H, 0x0404000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B4H, 0x000f0032U);
            WR1_PROG(REG_00B8H, 0x0014000aU);

            WR1_PROG(REG_00A4H, 0x04040000U);
            WR1_PROG(REG_0008H, 0x00020000U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            WR1_PROG(REG_00B4H, 0x005a0014U);
            WR1_PROG(REG_00B8H, 0x000f000aU);

            WR1_PROG(REG_00A4H, 0x04040002U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0014H, 0x000007c5U);
            WR1_PROG(REG_00B0H, 0x00001414U);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_ADDR(REG_002CH, &InData_MsgDgst[0]);

            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_KeyIndex[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000f0U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x97383a03U), bswap_32big(0xbfecb2faU), bswap_32big(0x8231f083U),
                           bswap_32big(0xc52808d3U));
            r_rsip_func043();

            r_rsip_func074();

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000f0U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xcd3942a2U), bswap_32big(0x69bd4023U), bswap_32big(0x2376489dU),
                           bswap_32big(0xa9846cebU));
            r_rsip_func044();

            WR1_PROG(REG_0014H, 0x000007c1U);
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xf7009d07U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

            WR1_PROG(REG_00B0H, 0x0000141eU);
            WR1_PROG(REG_0000H, 0x00c10021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x13b462c9U), bswap_32big(0xc9725d6eU), bswap_32big(0xf8bb234cU),
                           bswap_32big(0xc81c11deU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xee29133aU),
                               bswap_32big(0x24cf281cU),
                               bswap_32big(0xf2d51026U),
                               bswap_32big(0xd3483087U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                WR1_PROG(REG_00B4H, 0x005a001eU);
                WR1_PROG(REG_00B8H, 0x0019000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00280019U);
                WR1_PROG(REG_00B8H, 0x001e000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x001e0014U);
                WR1_PROG(REG_00B8H, 0x0019000aU);

                WR1_PROG(REG_00A4H, 0x04040005U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x0019000fU);
                WR1_PROG(REG_00B8H, 0x001e000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000140fU);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x000f001eU);
                WR1_PROG(REG_00B8H, 0x00140000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0x340d96f6U),
                               bswap_32big(0xbe3b9dafU),
                               bswap_32big(0x3abea947U),
                               bswap_32big(0xf9087800U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x372fe566U),
                                   bswap_32big(0xe13b9215U),
                                   bswap_32big(0x3409330eU),
                                   bswap_32big(0x990c6f1aU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x9485d266U),
                                   bswap_32big(0xf506fdc9U),
                                   bswap_32big(0x89c977baU),
                                   bswap_32big(0x58fe06e4U));
                    WR1_PROG(REG_00B0H, 0x00001828U);
                    WR1_PROG(REG_0008H, 0x00006022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD8_ADDR(REG_002CH, &OutData_Signature[0]);

                    r_rsip_func100(bswap_32big(0x45db71acU),
                                   bswap_32big(0x7728e45aU),
                                   bswap_32big(0x8c1a8d64U),
                                   bswap_32big(0xcf08a2e5U));
                    WR1_PROG(REG_00B0H, 0x0000181eU);
                    WR1_PROG(REG_0008H, 0x00006022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD8_ADDR(REG_002CH, &OutData_Signature[8]);

                    r_rsip_func102(bswap_32big(0xb080ee35U),
                                   bswap_32big(0xae552045U),
                                   bswap_32big(0xa8205695U),
                                   bswap_32big(0xadbdbe3fU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
