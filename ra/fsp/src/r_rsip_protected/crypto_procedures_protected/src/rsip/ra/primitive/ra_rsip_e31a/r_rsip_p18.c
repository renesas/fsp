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

rsip_ret_t r_rsip_p18 (const uint32_t InData_PrivKeyIndex[],
                       const uint32_t InData_PubKeyIndex[],
                       const uint32_t InData_Msg[],
                       const uint32_t InData_MsgLen[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_Signature[],
                       uint64_t       MAX_CNT)
{
    uint64_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00180001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x20010000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100c0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_PubKeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00001801U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x6f021312U),
                   bswap_32big(0x86883269U),
                   bswap_32big(0x18b6a5e4U),
                   bswap_32big(0xe1b2a5e0U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000026U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00001801U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x5490d49fU),
                   bswap_32big(0xddee4883U),
                   bswap_32big(0x964b6dc0U),
                   bswap_32big(0xfb37dfacU));
    r_rsip_func044();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000044U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000054U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x000007c1U);
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe8008107U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_PubKeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_PubKeyIndex[5]);

    WR1_PROG(REG_00B0H, 0x000014a5U);
    WR1_PROG(REG_0000H, 0x00c10021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x07008d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_PubKeyIndex[9]);

    WR1_PROG(REG_00D0H, 0x9c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0xf49f818dU),
                   bswap_32big(0xb92dbd2eU),
                   bswap_32big(0x0365d99aU),
                   bswap_32big(0x8d60c130U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x3bb8a93bU), bswap_32big(0x72fe8840U), bswap_32big(0xf6c1373dU),
                       bswap_32big(0xe04e24f5U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_PrivKeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00001802U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe56a3f54U), bswap_32big(0x11745775U), bswap_32big(0x27bbc5acU),
                       bswap_32big(0xd5d2f287U));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x00000027U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00001802U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x018b48cdU), bswap_32big(0x905a5d72U), bswap_32big(0x13b3b892U),
                       bswap_32big(0xc3f5de86U));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000007c1U);
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xf7009d07U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_PrivKeyIndex[1]);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_PrivKeyIndex[5]);

        WR1_PROG(REG_0094H, 0x00000800U);
        WR1_PROG(REG_009CH, 0x80880000U);
        WR1_PROG(REG_0000H, 0x03410021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_PrivKeyIndex[9]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0xd7bdc2e9U), bswap_32big(0x1e33c8e5U), bswap_32big(0x6e1f626aU),
                       bswap_32big(0xe3460794U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x3a1831cdU), bswap_32big(0x65af2631U), bswap_32big(0xbecf846cU),
                           bswap_32big(0xb2b931bdU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_KEY_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000001c7U);
            WR1_PROG(REG_009CH, 0x80020000U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_MsgLen[0]);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_MsgLen[1]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x00000842U);

            WR1_PROG(REG_0094H, 0x30008800U);
            WR1_PROG(REG_0094H, 0xffffffffU);
            WR1_PROG(REG_0094H, 0x00030020U);
            WR1_PROG(REG_0094H, 0x3000a820U);
            WR1_PROG(REG_0094H, 0xfffffdffU);
            WR1_PROG(REG_0094H, 0x00050020U);
            WR1_PROG(REG_0094H, 0x1000d040U);
            WR1_PROG(REG_0094H, 0x00000080U);
            WR1_PROG(REG_0094H, 0x00000080U);
            WR1_PROG(REG_0094H, 0x38008840U);
            WR1_PROG(REG_0094H, 0x00000001U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00270000U);

            r_rsip_func100(bswap_32big(0x1d217123U), bswap_32big(0x10949d4eU), bswap_32big(0xcc114ec5U),
                           bswap_32big(0xed5aa885U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x0659f1d8U),
                               bswap_32big(0x153c7117U),
                               bswap_32big(0xae4092b5U),
                               bswap_32big(0x51547165U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x8a66d628U),
                               bswap_32big(0xd651532bU),
                               bswap_32big(0x43fb1081U),
                               bswap_32big(0xbb3a3abfU));
                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_0094H, 0x0c00a420U);
                WR1_PROG(REG_0094H, 0x00000100U);
                WR1_PROG(REG_0094H, 0x00802402U);

                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0008H, 0x0000500aU);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0 + 1]);
                S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

                r_rsip_func100(bswap_32big(0xd63daaf2U),
                               bswap_32big(0x776020bdU),
                               bswap_32big(0xb7d80c65U),
                               bswap_32big(0xe90ec63aU));
                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_0094H, 0x0c00a420U);
                WR1_PROG(REG_0094H, 0x00000100U);
                WR1_PROG(REG_0094H, 0x00802402U);

                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0008H, 0x0000500aU);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0 + 2]);
                S_RAM[0 + 2] = bswap_32big(S_RAM[0 + 2]);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0 + 3]);
                S_RAM[0 + 3] = bswap_32big(S_RAM[0 + 3]);

                WR1_PROG(REG_00F0H, 0x00000001U);

                WR1_PROG(REG_00F4H, 0x000000b0U);

                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0104H, 0x00000000U);
                WR1_PROG(REG_0014H, 0x00000020U);
                WR1_PROG(REG_0100H, 0x00000100U);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x01490021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WAIT_STS(REG_0118H, 4, 1);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03450021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00003841U);
                WR1_PROG(REG_0094H, 0x00008c40U);
                WR1_PROG(REG_0094H, 0xf8ffffffU);
                WR1_PROG(REG_0094H, 0x00003c41U);

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x0000001cU);
                WR1_PROG(REG_0094H, 0x00003841U);

                WR1_PROG(REG_0094H, 0x00008c40U);
                WR1_PROG(REG_0094H, 0xffffff3fU);

                WR1_PROG(REG_0094H, 0x00009040U);
                WR1_PROG(REG_0094H, 0x00000040U);
                WR1_PROG(REG_0094H, 0x00003c41U);

                WR1_PROG(REG_00B0H, 0x0000149bU);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03450021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00F0H, 0x00000001U);

                WR1_PROG(REG_00F4H, 0x000000b0U);

                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0104H, S_RAM[0]);
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0100H, S_RAM[0 + 1]);

                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x01490021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x00020064U);

                for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffffffffffff0U); )
                {
                    WAIT_STS(REG_0014H, 31, 1);
                    WR8_ADDR(REG_002CH, &InData_Msg[iLoop]);
                    iLoop = iLoop + 8U;
                }

                WAIT_STS(REG_0014H, 31, 1);
                for (iLoop = (MAX_CNT & 0xfffffffffffffff0U); iLoop < MAX_CNT; iLoop++)
                {
                    WR1_PROG(REG_002CH, InData_Msg[iLoop]);
                }

                WR1_PROG(REG_0014H, 0x00000000U);

                WAIT_STS(REG_0118H, 4, 1);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03450021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func409();

                WR1_PROG(REG_00B0H, 0x00001437U);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03450021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func409();

                WR1_PROG(REG_00B0H, 0x00001432U);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func401(InData_DomainParam);

                r_rsip_func406(InData_DomainParam);

                WR1_PROG(REG_00B0H, 0x00001487U);
                WR1_PROG(REG_0000H, 0x00c00021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00000841U);
                WR1_PROG(REG_009CH, 0x80020000U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_00B0H, 0x000004b1U);
                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0000H, 0x00c90009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00001423U);
                WR1_PROG(REG_0014H, 0x000007a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_PROG(REG_002CH,
                         bswap_32big(0x0EEC73D2U),
                         bswap_32big(0x17F5BE65U),
                         bswap_32big(0xCB5C63AAU),
                         bswap_32big(0x97A331B5U));
                WAIT_STS(REG_0014H, 31, 1);
                WR4_PROG(REG_002CH,
                         bswap_32big(0x0665E1DBU),
                         bswap_32big(0x6EABA043U),
                         bswap_32big(0xF98B4BAAU),
                         bswap_32big(0x9C78F954U));

                WR1_PROG(REG_00B4H, 0x00320023U);
                WR1_PROG(REG_00B8H, 0x002d000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x001e0037U);
                WR1_PROG(REG_00B8H, 0x0028000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00001482U);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x00820028U);
                WR1_PROG(REG_00B8H, 0x0023000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x002d0023U);
                WR1_PROG(REG_00B8H, 0x00a0000aU);

                WR1_PROG(REG_00A4H, 0x04040005U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00000840U);
                WR1_PROG(REG_009CH, 0x80020000U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_00B0H, 0x000004b1U);
                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0000H, 0x00c90009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00001450U);
                WR1_PROG(REG_0000H, 0x00c00015U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000026U));
                WR1_PROG(REG_0000H, 0x00c00009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00001464U);
                WR1_PROG(REG_0000H, 0x00c00021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00001469U);
                WR1_PROG(REG_0000H, 0x00c00015U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000026U));
                WR1_PROG(REG_0000H, 0x00c00009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x0000146eU);
                WR1_PROG(REG_0000H, 0x00c00015U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000026U));
                WR1_PROG(REG_0000H, 0x00c00009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x0000148cU);
                WR1_PROG(REG_0000H, 0x00c00021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00001491U);
                WR1_PROG(REG_0000H, 0x00c00015U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000026U));
                WR1_PROG(REG_0000H, 0x00c00009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00001496U);
                WR1_PROG(REG_0000H, 0x00c00015U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000026U));
                WR1_PROG(REG_0000H, 0x00c00009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x000018a0U);
                WR1_PROG(REG_0094H, 0x00000800U);
                WR1_PROG(REG_009CH, 0x80880000U);
                WR1_PROG(REG_0000H, 0x03430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x000008c6U);
                WR1_PROG(REG_0094H, 0x00000800U);

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x0000001fU);

                WR1_PROG(REG_0094H, 0x0000b440U);
                WR1_PROG(REG_0094H, 0x00000001U);

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000018U));
                WR1_PROG(REG_0024H, 0x00000000U);

                for (iLoop = 0U; iLoop < 256U; iLoop++)
                {
                    r_rsip_func405();

                    r_rsip_func403();

                    r_rsip_func101(bswap_32big(0x7c3a6064U),
                                   bswap_32big(0x49a7eea1U),
                                   bswap_32big(0x2dd026a8U),
                                   bswap_32big(0x00a9ea0aU));
                    r_rsip_func402();

                    r_rsip_func404();

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0xf0b804caU),
                                   bswap_32big(0x6b27dd31U),
                                   bswap_32big(0x4bbb1e4dU),
                                   bswap_32big(0x90d83f02U));
                }

                WR1_PROG(REG_0094H, 0x380088c0U);
                WR1_PROG(REG_0094H, 0x00000100U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00270000U);

                WR1_PROG(REG_0040H, 0x00402000U);

                r_rsip_func100(bswap_32big(0xb026e883U),
                               bswap_32big(0x4ef6d657U),
                               bswap_32big(0x9d0ab8d8U),
                               bswap_32big(0x5565721aU));

                WR1_PROG(REG_00B4H, 0x00870064U);
                WR1_PROG(REG_00B8H, 0x00550000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00870069U);
                WR1_PROG(REG_00B8H, 0x005a0000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x0087006eU);
                WR1_PROG(REG_00B8H, 0x005f0000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00001482U);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x0082005fU);
                WR1_PROG(REG_00B8H, 0x00230005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000142dU);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

                WR1_PROG(REG_00B4H, 0x002d0005U);
                WR1_PROG(REG_00B8H, 0x00280000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00280023U);
                WR1_PROG(REG_00B8H, 0x002d0005U);

                WR1_PROG(REG_00A4H, 0x04040000U);
                WR1_PROG(REG_0008H, 0x00020000U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);
                WR1_PROG(REG_0040H, 0x00000d00U);

                WR1_PROG(REG_00B4H, 0x002d0055U);
                WR1_PROG(REG_00B8H, 0x00230005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x002d005aU);
                WR1_PROG(REG_00B8H, 0x00280005U);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00001823U);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000b420U);
                WR1_PROG(REG_0094H, 0x0000001cU);
                WR1_PROG(REG_0094H, 0x00003841U);

                WR1_PROG(REG_0094H, 0x001f6c42U);

                WR1_PROG(REG_00B0H, 0x00001828U);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00003801U);

                WR1_PROG(REG_0094H, 0x00008c00U);
                WR1_PROG(REG_0094H, 0x7fffffffU);

                WR1_PROG(REG_0094H, 0x00001002U);

                WR1_PROG(REG_0094H, 0x00003c01U);

                r_rsip_func409();

                WR1_PROG(REG_0094H, 0x00000821U);

                WR1_PROG(REG_00B0H, 0x0000142dU);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00F0H, 0x00000001U);

                WR1_PROG(REG_00F4H, 0x000000b0U);

                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0104H, S_RAM[0 + 2]);
                WR1_PROG(REG_0014H, 0x00000040U);
                WR1_PROG(REG_0100H, S_RAM[0 + 3]);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x01490021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x000018a5U);
                WR1_PROG(REG_0000H, 0x01430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0014H, 0x00020064U);

                for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffffffffffff0U); )
                {
                    WAIT_STS(REG_0014H, 31, 1);
                    WR16_ADDR(REG_002CH, &InData_Msg[iLoop]);
                    iLoop = iLoop + 16U;
                }

                WAIT_STS(REG_0014H, 31, 1);
                for (iLoop = (MAX_CNT & 0xfffffffffffffff0U); iLoop < MAX_CNT; iLoop++)
                {
                    WR1_PROG(REG_002CH, InData_Msg[iLoop]);
                }

                WR1_PROG(REG_0014H, 0x00000000U);

                WAIT_STS(REG_0118H, 4, 1);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03450021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func409();

                WR1_PROG(REG_00B0H, 0x000014afU);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_0094H, 0x00000842U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03450021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func409();

                WR1_PROG(REG_00B0H, 0x000014aaU);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x0000189bU);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func409();

                WR1_PROG(REG_00B0H, 0x0000149bU);
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0000H, 0x00c90021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00000841U);
                WR1_PROG(REG_009CH, 0x80020000U);
                WR1_PROG(REG_0000H, 0x03430009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_00B0H, 0x000004b1U);
                WR1_PROG(REG_009CH, 0x81020000U);
                WR1_PROG(REG_0000H, 0x00c90009U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_00B0H, 0x00001423U);
                WR1_PROG(REG_0014H, 0x000007a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_PROG(REG_002CH,
                         bswap_32big(0x0EEC73D2U),
                         bswap_32big(0x17F5BE65U),
                         bswap_32big(0xCB5C63AAU),
                         bswap_32big(0x97A331B5U));
                WAIT_STS(REG_0014H, 31, 1);
                WR4_PROG(REG_002CH,
                         bswap_32big(0x0665E1DBU),
                         bswap_32big(0x6EABA043U),
                         bswap_32big(0xF98B4BAAU),
                         bswap_32big(0x9C78F954U));

                WR1_PROG(REG_00B4H, 0x00aa0023U);
                WR1_PROG(REG_00B8H, 0x0028000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x001e00afU);
                WR1_PROG(REG_00B8H, 0x0023000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x00001482U);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                WR1_PROG(REG_00B4H, 0x00820023U);
                WR1_PROG(REG_00B8H, 0x003c000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x0028003cU);
                WR1_PROG(REG_00B8H, 0x0032000aU);

                WR1_PROG(REG_00A4H, 0x04040005U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x0032001eU);
                WR1_PROG(REG_00B8H, 0x0037000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x009b0037U);
                WR1_PROG(REG_00B8H, 0x003c000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x003c00a0U);
                WR1_PROG(REG_00B8H, 0x0028000aU);

                WR1_PROG(REG_00A4H, 0x04040005U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0094H, 0x00000821U);

                WR1_PROG(REG_00B0H, 0x00001828U);
                WR1_PROG(REG_009CH, 0x80880001U);
                WR1_PROG(REG_0000H, 0x03430021U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func409();

                r_rsip_func100(bswap_32big(0x0122bd04U),
                               bswap_32big(0x730e8bf3U),
                               bswap_32big(0xe573b554U),
                               bswap_32big(0xb5d65c75U));
                WR1_PROG(REG_00B0H, 0x0000182dU);
                WR1_PROG(REG_0008H, 0x00006022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD8_ADDR(REG_002CH, &OutData_Signature[0]);

                r_rsip_func100(bswap_32big(0xc2728a8dU),
                               bswap_32big(0x640fbc79U),
                               bswap_32big(0xe2738eb0U),
                               bswap_32big(0xa8a8d86eU));
                WR1_PROG(REG_0094H, 0x00000821U);
                WR1_PROG(REG_009CH, 0x81880001U);
                WR1_PROG(REG_0008H, 0x00005022U);
                for (iLoop = 8; iLoop < 16U; iLoop++)
                {
                    WAIT_STS(REG_0008H, 30, 1);
                    RD1_ADDR(REG_002CH, &OutData_Signature[iLoop]);
                }

                r_rsip_func102(bswap_32big(0x37f21ee1U),
                               bswap_32big(0x2219b561U),
                               bswap_32big(0xfbc29560U),
                               bswap_32big(0xd96f14d2U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
