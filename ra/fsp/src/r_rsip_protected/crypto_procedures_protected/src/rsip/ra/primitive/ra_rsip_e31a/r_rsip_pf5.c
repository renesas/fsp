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

rsip_ret_t r_rsip_pf5 (const uint32_t InData_CurveType[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_Signature[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f50001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func027(InData_DomainParam);

    r_rsip_func100(bswap_32big(0xb115ceb5U),
                   bswap_32big(0x8c87476bU),
                   bswap_32big(0x1f0e9b19U),
                   bswap_32big(0xc6f5e166U));

    WR1_PROG(REG_00B0H, 0x00009415U);
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x8de8c312U),
                   bswap_32big(0xfbb6fe82U),
                   bswap_32big(0xabaa8e2bU),
                   bswap_32big(0xbd973d0dU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xbbe97b0eU),
                   bswap_32big(0x307b19acU),
                   bswap_32big(0xdf32f693U),
                   bswap_32big(0xd28f4a14U));
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

    WR1_PROG(REG_00B0H, 0x00009438U);
    WR1_PROG(REG_0000H, 0x00c0002dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    WR1_PROG(REG_00B0H, 0x00009423U);
    WR1_PROG(REG_0000H, 0x00c0002dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

    WR1_PROG(REG_00B4H, 0x0023000eU);
    WR1_PROG(REG_00B8H, 0x001c0000U);

    WR1_PROG(REG_00A4H, 0x0606000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B8H, 0x0000001cU);

    WR1_PROG(REG_00A4H, 0x06060010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x00380015U);
    WR1_PROG(REG_00B8H, 0x003f001cU);

    WR1_PROG(REG_00A4H, 0x06060002U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0038003fU);
    WR1_PROG(REG_00B8H, 0x00460000U);

    WR1_PROG(REG_00A4H, 0x06060009U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    r_rsip_func028(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000f5U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x79a8737eU),
                   bswap_32big(0x86fd90f7U),
                   bswap_32big(0xdb7b4eddU),
                   bswap_32big(0xb6110de8U));
    r_rsip_func089();

    r_rsip_func100(bswap_32big(0x022b0067U),
                   bswap_32big(0xb48a833cU),
                   bswap_32big(0x2461b931U),
                   bswap_32big(0xcc167a69U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x5df28191U), bswap_32big(0x067185b6U), bswap_32big(0x10059891U),
                       bswap_32big(0xf5b6a1dbU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_00B8H, 0x0000000eU);

        WR1_PROG(REG_00A4H, 0x06060010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x007e0038U);
        WR1_PROG(REG_00B8H, 0x003f000eU);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0014H, 0x000000a5U);
        WR1_PROG(REG_00B0H, 0x00009415U);
        WR1_PROG(REG_0000H, 0x00c0002dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        WR1_PROG(REG_00B4H, 0x0015003fU);
        WR1_PROG(REG_00B8H, 0x0038000eU);

        WR1_PROG(REG_00A4H, 0x06060002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x00150038U);
        WR1_PROG(REG_00B8H, 0x001c0000U);

        WR1_PROG(REG_00A4H, 0x0606000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x9befea36U), bswap_32big(0x75988304U), bswap_32big(0x3a5795d8U),
                       bswap_32big(0x79f1e06bU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xb31cda1dU), bswap_32big(0xff486971U), bswap_32big(0x457ca05fU),
                           bswap_32big(0x5a303a3aU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xa9c8370cU), bswap_32big(0x7c04069eU), bswap_32big(0xc413c550U),
                           bswap_32big(0xbf5ad3dbU));
            WR1_PROG(REG_00B0H, 0x0000941cU);
            WR1_PROG(REG_0000H, 0x00c0002dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

            WR1_PROG(REG_00B4H, 0x001c000eU);
            WR1_PROG(REG_00B8H, 0x00150000U);

            WR1_PROG(REG_00A4H, 0x0606000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B4H, 0x00150046U);
            WR1_PROG(REG_00B8H, 0x001c000eU);

            WR1_PROG(REG_00A4H, 0x06060000U);
            WR1_PROG(REG_0008H, 0x00020000U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            WR1_PROG(REG_00B4H, 0x007e001cU);
            WR1_PROG(REG_00B8H, 0x0015000eU);

            WR1_PROG(REG_00A4H, 0x06060002U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0014H, 0x00000bc5U);
            WR1_PROG(REG_00B0H, 0x0000941cU);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_MsgDgst[0]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_MsgDgst[4]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_MsgDgst[8]);

            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_KeyIndex[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000f5U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x4ae51dabU), bswap_32big(0xc80e437aU), bswap_32big(0x9d02046fU),
                           bswap_32big(0x86196168U));
            r_rsip_func043();

            r_rsip_func076();

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x000000f5U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x4e6636d0U), bswap_32big(0x42dd826cU), bswap_32big(0x4440cec1U),
                           bswap_32big(0xacd3e692U));
            r_rsip_func044();

            WR1_PROG(REG_0014H, 0x00000bc1U);
            WR1_PROG(REG_00D4H, 0x40000200U);
            WR1_PROG(REG_00D0H, 0xf7009d07U);

            for (iLoop = 0U; iLoop < 12U; )
            {
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_00B0H, 0x0000942aU);
            WR1_PROG(REG_0000H, 0x00c10031U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[1 + iLoop]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x2c474d3dU), bswap_32big(0x9bda990fU), bswap_32big(0xf7967fb9U),
                           bswap_32big(0x3f00e90dU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x4db8f271U),
                               bswap_32big(0x39b281b0U),
                               bswap_32big(0x782e0921U),
                               bswap_32big(0x1a235e53U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                WR1_PROG(REG_00B4H, 0x007e002aU);
                WR1_PROG(REG_00B8H, 0x0023000eU);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00380023U);
                WR1_PROG(REG_00B8H, 0x002a000eU);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x002a001cU);
                WR1_PROG(REG_00B8H, 0x0023000eU);

                WR1_PROG(REG_00A4H, 0x06060005U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00230015U);
                WR1_PROG(REG_00B8H, 0x002a000eU);

                WR1_PROG(REG_00A4H, 0x06060002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00009415U);
                WR1_PROG(REG_0000H, 0x00c0002dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x0015002aU);
                WR1_PROG(REG_00B8H, 0x001c0000U);

                WR1_PROG(REG_00A4H, 0x0606000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                r_rsip_func100(bswap_32big(0xaffe395eU),
                               bswap_32big(0xd517c071U),
                               bswap_32big(0x6e990641U),
                               bswap_32big(0x090c9765U));
                WR1_PROG(REG_0040H, 0x00400000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    r_rsip_func102(bswap_32big(0x744a0831U),
                                   bswap_32big(0x203e67abU),
                                   bswap_32big(0xf28f8ee1U),
                                   bswap_32big(0x7a0e4df0U));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xb95f1927U),
                                   bswap_32big(0x25b0bcb4U),
                                   bswap_32big(0xed0ae2dfU),
                                   bswap_32big(0xaa1519c4U));
                    WR1_PROG(REG_00B0H, 0x00009838U);
                    WR1_PROG(REG_0008H, 0x00006032U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_Signature[0]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_Signature[4]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_Signature[8]);

                    r_rsip_func100(bswap_32big(0x8c2521aaU),
                                   bswap_32big(0x134e1f4bU),
                                   bswap_32big(0x8049b2ecU),
                                   bswap_32big(0xd71d88d1U));
                    WR1_PROG(REG_00B0H, 0x0000982aU);
                    WR1_PROG(REG_0008H, 0x00006032U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_Signature[12]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_Signature[16]);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD4_ADDR(REG_002CH, &OutData_Signature[20]);

                    r_rsip_func102(bswap_32big(0x8d4ac452U),
                                   bswap_32big(0xc0e5e098U),
                                   bswap_32big(0xc9dfadd4U),
                                   bswap_32big(0x4d6c935fU));
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
