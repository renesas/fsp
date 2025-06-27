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

rsip_ret_t r_rsip_p3b (const uint32_t MAX_CNT, uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;
    uint32_t kLoop   = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x003b0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x00000e50U);

    WR1_PROG(REG_1600H, 0x00000a31U);
    for (kLoop = 0U; kLoop < MAX_CNT; kLoop++)
    {
        WR1_PROG(REG_1444H, 0x00002fb0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_0160H, bswap_32big(0x00030005U));
        WR1_PROG(REG_0164H, bswap_32big(0x0007000bU));
        WR1_PROG(REG_0168H, bswap_32big(0x000d0011U));
        WR1_PROG(REG_016CH, bswap_32big(0x00130017U));
        WR1_PROG(REG_0170H, bswap_32big(0x001d001fU));
        WR1_PROG(REG_0174H, bswap_32big(0x00250029U));
        WR1_PROG(REG_0178H, bswap_32big(0x002b002fU));
        WR1_PROG(REG_017CH, bswap_32big(0x003b003dU));
        WR1_PROG(REG_0180H, bswap_32big(0x00430047U));
        WR1_PROG(REG_0184H, bswap_32big(0x0049004fU));
        WR1_PROG(REG_0188H, bswap_32big(0x00530059U));
        WR1_PROG(REG_018CH, bswap_32big(0x00610065U));
        WR1_PROG(REG_0190H, bswap_32big(0x0067006bU));
        WR1_PROG(REG_0194H, bswap_32big(0x006d0071U));
        WR1_PROG(REG_0198H, bswap_32big(0x007f0083U));
        WR1_PROG(REG_019CH, bswap_32big(0x0089008bU));
        WR1_PROG(REG_01A0H, bswap_32big(0x00950097U));
        WR1_PROG(REG_01A4H, bswap_32big(0x009d00a3U));
        WR1_PROG(REG_01A8H, bswap_32big(0x00a700adU));
        WR1_PROG(REG_01ACH, bswap_32big(0x00b300b5U));
        WR1_PROG(REG_01B0H, bswap_32big(0x00bf00c1U));
        WR1_PROG(REG_01B4H, bswap_32big(0x00c500c7U));
        WR1_PROG(REG_01B8H, bswap_32big(0x00d300dfU));
        WR1_PROG(REG_01BCH, bswap_32big(0x00e300e5U));
        WR1_PROG(REG_01C0H, bswap_32big(0x00e900efU));
        WR1_PROG(REG_01C4H, bswap_32big(0x00f100fbU));
        WR1_PROG(REG_01C8H, bswap_32big(0x01010107U));
        WR1_PROG(REG_01CCH, bswap_32big(0x010d010fU));
        WR1_PROG(REG_01D0H, bswap_32big(0x01150119U));
        WR1_PROG(REG_01D4H, bswap_32big(0x011b0125U));
        WR1_PROG(REG_01D8H, bswap_32big(0x01330137U));
        WR1_PROG(REG_01DCH, bswap_32big(0x0139013dU));
        WR1_PROG(REG_01E0H, bswap_32big(0x014b0151U));
        WR1_PROG(REG_01E4H, bswap_32big(0x015b015dU));
        WR1_PROG(REG_01E8H, bswap_32big(0x01610167U));
        WR1_PROG(REG_01ECH, bswap_32big(0x016f0175U));
        WR1_PROG(REG_01F0H, bswap_32big(0x017b017fU));
        WR1_PROG(REG_01F4H, bswap_32big(0x0185018dU));
        WR1_PROG(REG_01F8H, bswap_32big(0x01910199U));
        WR1_PROG(REG_01FCH, bswap_32big(0x01a301a5U));
        WR1_PROG(REG_0200H, bswap_32big(0x01af01b1U));
        WR1_PROG(REG_0204H, bswap_32big(0x01b701bbU));
        WR1_PROG(REG_0208H, bswap_32big(0x01c101c9U));
        WR1_PROG(REG_020CH, bswap_32big(0x01cd01cfU));
        WR1_PROG(REG_0210H, bswap_32big(0x01d301dfU));
        WR1_PROG(REG_0214H, bswap_32big(0x01e701ebU));
        WR1_PROG(REG_0218H, bswap_32big(0x01f301f7U));
        WR1_PROG(REG_021CH, bswap_32big(0x01fd0000U));

        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x000000c0U);
        WR1_PROG(REG_1608H, 0x80b00006U);
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x034300c1U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00003b01U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x2fc1e1cfU), bswap_32big(0x23797578U), bswap_32big(0x8e47bcedU),
                       bswap_32big(0x846b3dbaU));
        r_rsip_func113();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000d01fU);
        WR1_PROG(REG_1608H, 0x81040000U);
        WR1_PROG(REG_1404H, 0x11200000U);
        WR1_PROG(REG_1400H, 0x00c90011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00000884U);
        WR1_PROG(REG_1600H, 0x0000b4a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x00000038U);
        WR1_PROG(REG_1600H, 0x000008e7U);

        for (iLoop = 0U; iLoop < 56U; )
        {
            WR1_PROG(REG_1600H, 0x34202886U);
            WR1_PROG(REG_1600H, 0x2000d0e0U);
            WR1_PROG(REG_1600H, 0x00007c07U);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00003b02U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x60b27d92U), bswap_32big(0xbe9d23abU), bswap_32big(0x897293e6U),
                           bswap_32big(0xa7b4b582U));
            r_rsip_func113();

            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00002485U);

            r_rsip_func101(bswap_32big(0x05101202U), bswap_32big(0x27fe0d14U), bswap_32big(0x7f440cbcU),
                           bswap_32big(0xaf4c7cc2U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000886U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00003b03U));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x74df1227U), bswap_32big(0x5d58d46fU), bswap_32big(0xdfdfeedfU),
                       bswap_32big(0x24a350adU));
        r_rsip_func113();

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1600H, 0x0000d060U);
        WR1_PROG(REG_1608H, 0x81040000U);
        WR1_PROG(REG_1400H, 0x00c90011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x00003fb0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_0940H, bswap_32big(0xB51EB851U));
        WR1_PROG(REG_0944H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_0948H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_094CH, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_0950H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_0954H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_0958H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_095CH, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_0960H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_0964H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_0968H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_096CH, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_0970H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_0974H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_0978H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_097CH, bswap_32big(0x851EB851U));
        WR1_PROG(REG_0980H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_0984H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_0988H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_098CH, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_0990H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_0994H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_0998H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_099CH, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_09A0H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_09A4H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_09A8H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_09ACH, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_09B0H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_09B4H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_09B8H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_09BCH, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_09C0H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_09C4H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_09C8H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_09CCH, bswap_32big(0x851EB851U));
        WR1_PROG(REG_09D0H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_09D4H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_09D8H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_09DCH, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_09E0H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_09E4H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_09E8H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_09ECH, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_09F0H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_09F4H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_09F8H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_09FCH, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_0A00H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_0A04H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_0A08H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_0A0CH, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_0A10H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_0A14H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_0A18H, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_0A1CH, bswap_32big(0x851EB851U));
        WR1_PROG(REG_0A20H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_0A24H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_0A28H, bswap_32big(0xB851EB85U));
        WR1_PROG(REG_0A2CH, bswap_32big(0x1EB851EBU));
        WR1_PROG(REG_0A30H, bswap_32big(0x851EB851U));
        WR1_PROG(REG_0A34H, bswap_32big(0xEB851EB8U));
        WR1_PROG(REG_0A38H, bswap_32big(0x51EB851EU));
        WR1_PROG(REG_0A3CH, bswap_32big(0xB851EB85U));

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x2020000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0xc97748faU), bswap_32big(0xab884819U), bswap_32big(0x9b85f9acU),
                       bswap_32big(0x38955739U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func101(bswap_32big(0xdf9a48a5U), bswap_32big(0xe6e71d7bU), bswap_32big(0x3505f1e3U),
                           bswap_32big(0x5c861a45U));
            continue;
        }
        else
        {
            r_rsip_func101(bswap_32big(0x0813b602U), bswap_32big(0xc87e6c80U), bswap_32big(0xe094433bU),
                           bswap_32big(0x9cf2adffU));
        }

        WR1_PROG(REG_1600H, 0x38008a20U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x3ba6e686U), bswap_32big(0x626c44f4U), bswap_32big(0x9bf1beecU),
                       bswap_32big(0x77a633c8U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000320U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x74f3a65dU), bswap_32big(0x1848676eU), bswap_32big(0x8a28c37aU),
                           bswap_32big(0x9a274586U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000320U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                r_rsip_func101(bswap_32big(0xbbb1a687U),
                               bswap_32big(0x82e66be3U),
                               bswap_32big(0x7d8b5f5cU),
                               bswap_32big(0x457c201eU));
            }
            else
            {
                r_rsip_func101(bswap_32big(0x732839fdU),
                               bswap_32big(0xe4c1b727U),
                               bswap_32big(0xaa9b81e6U),
                               bswap_32big(0x4de5d5b9U));
            }

            WR1_PROG(REG_1404H, 0x19400000U);
            WR1_PROG(REG_1444H, 0x000003a2U);
            WR1_PROG(REG_1A24H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_PROG(REG_1420H,
                     bswap_32big(0x00000000U),
                     bswap_32big(0x00000000U),
                     bswap_32big(0x00000000U),
                     bswap_32big(0x10000000U));
            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x79334c80U), bswap_32big(0x0b4dee97U), bswap_32big(0x8129b330U),
                           bswap_32big(0x04176892U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func101(bswap_32big(0x9b4cb7fcU),
                               bswap_32big(0x384a7416U),
                               bswap_32big(0x221b74fcU),
                               bswap_32big(0x16621e18U));
                continue;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xbb9be7b4U),
                               bswap_32big(0xbe40177dU),
                               bswap_32big(0x6e845b37U),
                               bswap_32big(0x1fc001baU));
            }
        }
        else
        {
            r_rsip_func101(bswap_32big(0xe1c7b987U), bswap_32big(0x5d733990U), bswap_32big(0x6b3226b0U),
                           bswap_32big(0xe6645d86U));
        }

        WR1_PROG(REG_1600H, 0x0000b4c0U);
        WR1_PROG(REG_1600H, 0x000000c0U);
        WR1_PROG(REG_1600H, 0x0000094aU);

        for (iLoop = 0U; iLoop < 95U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x01003906U);
            WR1_PROG(REG_1600H, 0x00002cc0U);
            WR1_PROG(REG_1600H, 0x00002cc0U);
            WR1_PROG(REG_1608H, 0x81010100U);

            WR1_PROG(REG_1404H, 0x15300000U);
            WR1_PROG(REG_1400H, 0x00c000fdU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c90005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000630U);

            WR1_PROG(REG_1004H, 0x20200010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_1014H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x20200004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x19400000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c000fdU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0x0f6a6285U), bswap_32big(0x0ab5fc1bU), bswap_32big(0x5ccbaf23U),
                           bswap_32big(0xa9d5db6eU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x0000d140U);

                r_rsip_func101(bswap_32big(0xb8394cf3U),
                               bswap_32big(0x7d8048d4U),
                               bswap_32big(0x7781eb32U),
                               bswap_32big(0x719c9025U));
                break;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xcfb15a84U),
                               bswap_32big(0x8f5b0ef6U),
                               bswap_32big(0x0a648675U),
                               bswap_32big(0x018207ebU));
            }

            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1600H, 0x38008940U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x339aee89U), bswap_32big(0x8f9281f7U), bswap_32big(0xc1ae3ffaU),
                       bswap_32big(0x8a2a8345U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func101(bswap_32big(0xad24540eU), bswap_32big(0x34c5cc9bU), bswap_32big(0x312d5413U),
                           bswap_32big(0x1a09a2bcU));
            continue;
        }

        WR1_PROG(REG_1404H, 0x18380000U);
        WR1_PROG(REG_1400H, 0x00c00101U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_1018H, 0x00000938U);
        WR1_PROG(REG_1020H, 0x00000428U);

        WR1_PROG(REG_1004H, 0x20200009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000428U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000220U);

        WR1_PROG(REG_1004H, 0x2020000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x15300000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00010001U));
        WR1_PROG(REG_1400H, 0x00c000fdU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000630U);

        WR1_PROG(REG_1004H, 0x20200010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_1014H, 0x00000220U);
        WR1_PROG(REG_101CH, 0x00000630U);
        WR1_PROG(REG_1020H, 0x00000838U);

        WR1_PROG(REG_1004H, 0x20200004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x19400000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c000fdU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000838U);
        WR1_PROG(REG_1018H, 0x00000a40U);
        WR1_PROG(REG_1020H, 0x00000630U);

        WR1_PROG(REG_1004H, 0x2020000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        r_rsip_func100(bswap_32big(0xcbe3691cU), bswap_32big(0x3d37eecdU), bswap_32big(0x2cbf8f32U),
                       bswap_32big(0xb6558f40U));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func101(bswap_32big(0x7c285b39U), bswap_32big(0xd94fe5fcU), bswap_32big(0x2ced59f3U),
                           bswap_32big(0x9d597440U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0xddacf41fU), bswap_32big(0x8dd867daU), bswap_32big(0xa5bcb447U),
                           bswap_32big(0xa1a3368cU));
            WR1_PROG(REG_1404H, 0x17380000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
            WR1_PROG(REG_1400H, 0x00c000fdU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000428U);

            WR1_PROG(REG_1004H, 0x20200010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000220U);
            WR1_PROG(REG_101CH, 0x00000428U);
            WR1_PROG(REG_1020H, 0x00000630U);

            WR1_PROG(REG_1004H, 0x20200000U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000630U);
            WR1_PROG(REG_1018H, 0x00000a40U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000a40U);
            WR1_PROG(REG_1018H, 0x00000630U);
            WR1_PROG(REG_1020H, 0x00000838U);

            WR1_PROG(REG_1004H, 0x2020000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            r_rsip_func100(bswap_32big(0xbefabb5cU), bswap_32big(0x56de6de1U), bswap_32big(0x3172e3c0U),
                           bswap_32big(0x7ba2c65cU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func101(bswap_32big(0xa24b7be6U),
                               bswap_32big(0x7339b2c7U),
                               bswap_32big(0x5b215e79U),
                               bswap_32big(0x54ebc466U));
                continue;
            }

            r_rsip_func100(bswap_32big(0x440ad503U), bswap_32big(0xb865ceafU), bswap_32big(0x9cf41037U),
                           bswap_32big(0x7dfedf87U));

            WR1_PROG(REG_1600H, 0x0000b560U);
            WR1_PROG(REG_1600H, 0x00000001U);

            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x80c0000aU);
            WR1_PROG(REG_1404H, 0x11200000U);
            WR1_PROG(REG_1400H, 0x03430101U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000929U);
            WR1_PROG(REG_1600H, 0x00000908U);
            WR1_PROG(REG_1600H, 0x0000b4c0U);
            WR1_PROG(REG_1600H, 0x000000fcU);

            for (iLoop = 0U; iLoop < 64U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x000038e6U);
                WR1_PROG(REG_1600H, 0x0000a8c0U);
                WR1_PROG(REG_1600H, 0x00000004U);
                for (jLoop = 0U; jLoop < 32U; jLoop++)
                {
                    WR1_PROG(REG_1600H, 0x38008900U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x11816907U);

                    WR1_PROG(REG_1600H, 0x38008900U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x10002d20U);

                    WR1_PROG(REG_1600H, 0x000168e7U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1608H, 0x81010120U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);
            WR1_PROG(REG_1600H, 0x000037e9U);

            WR1_PROG(REG_1404H, 0x15300000U);
            WR1_PROG(REG_1600H, 0x0000094aU);
            WR1_PROG(REG_1608H, 0x81c0000aU);
            WR1_PROG(REG_1400H, 0x00c90101U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1014H, 0x00000630U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x2020000cU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1018H, 0x00000938U);
                WR1_PROG(REG_1020H, 0x00000630U);

                WR1_PROG(REG_1004H, 0x20200009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1600H, 0x000033e0U);

                r_rsip_func101(bswap_32big(0xf4c051cdU),
                               bswap_32big(0x85faeffdU),
                               bswap_32big(0x11f39e9cU),
                               bswap_32big(0x68ca93caU));
            }

            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00007c1fU);
            WR1_PROG(REG_143CH, 0x00602000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func100(bswap_32big(0xaa2f3502U), bswap_32big(0x2e7d6e14U), bswap_32big(0xf5d25804U),
                           bswap_32big(0x637fb462U));
            WR1_PROG(REG_1600H, 0x00000a52U);

            WR1_PROG(REG_1608H, 0x81010160U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x00000884U);
                WR1_PROG(REG_1600H, 0x0000b4a0U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1600H, 0x0000b4c0U);
                WR1_PROG(REG_1600H, 0x00000040U);
                WR1_PROG(REG_1600H, 0x000008e7U);

                WR1_PROG(REG_1404H, 0x11200000U);
                for (jLoop = 0U; jLoop < 64U; )
                {
                    WR1_PROG(REG_1600H, 0x34202886U);
                    WR1_PROG(REG_1600H, 0x2000d0e0U);
                    WR1_PROG(REG_1600H, 0x00007c07U);
                    WR1_PROG(REG_143CH, 0x00602000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00003b04U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x8974bbd1U),
                                   bswap_32big(0x456aeee3U),
                                   bswap_32big(0xfefddb03U),
                                   bswap_32big(0xf7ee3065U));
                    r_rsip_func113();

                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x0c200104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                    WR1_PROG(REG_1400H, 0x00c20011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002485U);

                    r_rsip_func101(bswap_32big(0xd23841ccU),
                                   bswap_32big(0x0b85fcb8U),
                                   bswap_32big(0x5900c61cU),
                                   bswap_32big(0x2013006eU));
                    jLoop = jLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000886U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func100(bswap_32big(0xc7fd0ed7U),
                               bswap_32big(0xccd04254U),
                               bswap_32big(0x5caa8a30U),
                               bswap_32big(0xc87ab93fU));
                WR1_PROG(REG_1404H, 0x19400000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000004U));
                WR1_PROG(REG_1400H, 0x00c000fdU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000428U);
                WR1_PROG(REG_1018H, 0x00000a40U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000838U);

                WR1_PROG(REG_1004H, 0x20200010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_101CH, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000a40U);

                WR1_PROG(REG_1004H, 0x20200004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x17380000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c000fdU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x20200009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1010H, 0x00000018U);
                WR1_PROG(REG_101CH, 0x00000428U);

                WR1_PROG(REG_1004H, 0x20200010U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_1018H, 0x00000630U);
                WR1_PROG(REG_101CH, 0x00000428U);
                WR1_PROG(REG_1020H, 0x00000838U);

                WR1_PROG(REG_1004H, 0x20200000U);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1404H, 0x19400000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c000fdU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000838U);
                WR1_PROG(REG_1018H, 0x00000a40U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                WR1_PROG(REG_1014H, 0x00000a40U);
                WR1_PROG(REG_1018H, 0x00000838U);
                WR1_PROG(REG_1020H, 0x00000220U);

                WR1_PROG(REG_1004H, 0x2020000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                r_rsip_func100(bswap_32big(0x7af3ef3dU),
                               bswap_32big(0x501e059eU),
                               bswap_32big(0xbd913ac0U),
                               bswap_32big(0xf6206e97U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 0))
                {
                    WR1_PROG(REG_1600H, 0x00002e40U);

                    r_rsip_func101(bswap_32big(0xb81f3c12U),
                                   bswap_32big(0xfabc508fU),
                                   bswap_32big(0x2ebd007eU),
                                   bswap_32big(0xe9279829U));
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x0000094aU);

                    r_rsip_func100(bswap_32big(0xda07bc27U),
                                   bswap_32big(0xaa7b7215U),
                                   bswap_32big(0x5a56c5cbU),
                                   bswap_32big(0x39a236cdU));
                    WR1_PROG(REG_1608H, 0x81010120U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                    S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);
                    WR1_PROG(REG_1600H, 0x000037e9U);

                    for (jLoop = 0U; jLoop < S_RAM[0 + 1]; jLoop++)
                    {
                        WR1_PROG(REG_1404H, 0x19400000U);
                        WR1_PROG(REG_1608H, 0x81c0000aU);
                        WR1_PROG(REG_1400H, 0x00c90101U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1014H, 0x00000838U);
                        WR1_PROG(REG_1018H, 0x00000a40U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x2020000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        WR1_PROG(REG_1014H, 0x00000a40U);
                        WR1_PROG(REG_1018H, 0x00000838U);
                        WR1_PROG(REG_1020H, 0x00000220U);

                        WR1_PROG(REG_1004H, 0x2020000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        r_rsip_func100(bswap_32big(0x4a92d88fU),
                                       bswap_32big(0x71beda31U),
                                       bswap_32big(0x675a2e4dU),
                                       bswap_32big(0x2cbb75d8U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 0))
                        {
                            WR1_PROG(REG_1600H, 0x00002e40U);

                            r_rsip_func101(bswap_32big(0xf05b995fU),
                                           bswap_32big(0xef88e2d4U),
                                           bswap_32big(0x7eb27f3aU),
                                           bswap_32big(0xaa63d751U));
                            break;
                        }
                        else
                        {
                            r_rsip_func100(bswap_32big(0xe8e2cf85U),
                                           bswap_32big(0x528ef2f8U),
                                           bswap_32big(0x1761cd5cU),
                                           bswap_32big(0x3c4bd2e8U));
                            WR1_PROG(REG_1404H, 0x19400000U);
                            WR1_PROG(REG_1444H, 0x000000a2U);
                            WR1_PROG(REG_1A24H, 0x08000104U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                            WR1_PROG(REG_1400H, 0x00c000fdU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x00c20005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x0002000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1014H, 0x00000838U);
                            WR1_PROG(REG_1018H, 0x00000a40U);
                            WR1_PROG(REG_101CH, 0x00000428U);
                            WR1_PROG(REG_1020H, 0x00000220U);

                            WR1_PROG(REG_1004H, 0x20200000U);
                            WR1_PROG(REG_1408H, 0x00020000U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);
                            WR1_PROG(REG_143CH, 0x00000d00U);

                            WR1_PROG(REG_1014H, 0x00000220U);
                            WR1_PROG(REG_1018H, 0x00000938U);
                            WR1_PROG(REG_1020H, 0x00000838U);

                            WR1_PROG(REG_1004H, 0x20200009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            r_rsip_func101(bswap_32big(0xdecb8abeU),
                                           bswap_32big(0x1cb92eabU),
                                           bswap_32big(0x79853ce1U),
                                           bswap_32big(0xbc388166U));
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x38008a40U);
                    WR1_PROG(REG_1600H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    r_rsip_func100(bswap_32big(0xd9ecd517U),
                                   bswap_32big(0xf99dbecbU),
                                   bswap_32big(0xc2dbd955U),
                                   bswap_32big(0x9ccc3bceU));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func101(bswap_32big(0xdf36d6a6U),
                                       bswap_32big(0x880a7c8eU),
                                       bswap_32big(0xc6657bdeU),
                                       bswap_32big(0xf65aee7cU));
                        break;
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x7acff248U),
                                       bswap_32big(0x8366309bU),
                                       bswap_32big(0x0c1b9eb5U),
                                       bswap_32big(0x8dd52387U));
                    }
                }
            }

            WR1_PROG(REG_1600H, 0x38000a4bU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            r_rsip_func100(bswap_32big(0x765635b4U), bswap_32big(0xd2820434U), bswap_32big(0x7fc0b664U),
                           bswap_32big(0x90cf302eU));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00002e20U);

                WR1_PROG(REG_1600H, 0x38008a20U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0xd5601d34U),
                               bswap_32big(0xe1de9099U),
                               bswap_32big(0x04392bb1U),
                               bswap_32big(0xdaa4151bU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func101(bswap_32big(0x069e5338U),
                                   bswap_32big(0x02450d07U),
                                   bswap_32big(0x7d3f34a8U),
                                   bswap_32big(0x32d9fd1fU));
                    break;
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000428U);
                    WR1_PROG(REG_1018H, 0x00000938U);
                    WR1_PROG(REG_1020H, 0x00000320U);

                    WR1_PROG(REG_1004H, 0x20200009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    r_rsip_func101(bswap_32big(0xab33dde8U),
                                   bswap_32big(0x9e2bf4f3U),
                                   bswap_32big(0x7784a8ffU),
                                   bswap_32big(0x88a39058U));
                }
            }
            else
            {
                r_rsip_func101(bswap_32big(0xaf8b4143U),
                               bswap_32big(0xc2a4d2faU),
                               bswap_32big(0x47126475U),
                               bswap_32big(0x3ce7f66bU));
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008a20U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xaf77d897U),
                   bswap_32big(0x35892c72U),
                   bswap_32big(0x426f53abU),
                   bswap_32big(0xac579fd0U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd043e820U), bswap_32big(0x89c7fb14U), bswap_32big(0xe944a3b5U),
                       bswap_32big(0xa7a4b951U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }

    WR1_PROG(REG_1404H, 0x19400000U);
    WR1_PROG(REG_1400H, 0x00c00101U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000838U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000320U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000738U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b05U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xfe9e64e4U),
                   bswap_32big(0x722b100dU),
                   bswap_32big(0x6e831b5cU),
                   bswap_32big(0xab76c28dU));
    r_rsip_func113();

    r_rsip_func100(bswap_32big(0xfac3916eU),
                   bswap_32big(0x007aeb65U),
                   bswap_32big(0x2d3a8d6eU),
                   bswap_32big(0xe04a7c35U));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c2000c4U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x16380000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x6c59c3e9U),
                   bswap_32big(0xff39b0a1U),
                   bswap_32big(0x80ce95aaU),
                   bswap_32big(0xbb628179U));
    r_rsip_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x19400000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c000fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000320U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000220U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000428U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000630U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x0000003bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x4cb5bf94U),
                   bswap_32big(0xc862ac8aU),
                   bswap_32big(0x688ce218U),
                   bswap_32big(0xa438740dU));
    r_rsip_func054();

    WR1_PROG(REG_1404H, 0x19400000U);
    WR1_PROG(REG_1400H, 0x00c00101U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000a40U);
    WR1_PROG(REG_1020H, 0x00000660U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x00000dc0U);

    WR1_PROG(REG_1404H, 0x14500000U);
    WR1_PROG(REG_1400H, 0x00c00111U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x16780000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xba7ce631U),
                   bswap_32big(0x2f615e20U),
                   bswap_32big(0x0c448cb2U),
                   bswap_32big(0x57c85c63U));
    r_rsip_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x00000778U);
    WR1_PROG(REG_1018H, 0x00000878U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x20200007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xede19902U),
                   bswap_32big(0x622636f0U),
                   bswap_32big(0x12ae68b1U),
                   bswap_32big(0x6a701ecaU));
    r_rsip_func321();

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000660U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a90U);
    WR1_PROG(REG_1018H, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    r_rsip_func100(bswap_32big(0x92dcf757U),
                   bswap_32big(0xf576443fU),
                   bswap_32big(0xb35cef75U),
                   bswap_32big(0xdec1ecaaU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x57fca3a9U), bswap_32big(0x6469b8afU), bswap_32big(0x1c921ed4U),
                       bswap_32big(0xd58983ceU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x12480000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x0ba82be5U),
                   bswap_32big(0x4c795556U),
                   bswap_32big(0x51bc5ebfU),
                   bswap_32big(0xc947aa3dU));
    r_rsip_func017(OFS_ADR);

    WR1_PROG(REG_1014H, 0x00000348U);
    WR1_PROG(REG_1018H, 0x00000448U);
    WR1_PROG(REG_1020H, 0x00000660U);

    WR1_PROG(REG_1004H, 0x20200007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x14600000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xa15ef1f3U),
                   bswap_32big(0xce8ed8ceU),
                   bswap_32big(0x4f4c7bd0U),
                   bswap_32big(0xa0a1cd2eU));
    r_rsip_func016(OFS_ADR);

    WR1_PROG(REG_1404H, 0x19900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c000fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000448U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000348U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000130U);

    WR1_PROG(REG_1004H, 0x2020000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000130U);
    WR1_PROG(REG_1018H, 0x00000230U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x20200007U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000660U);

    WR1_PROG(REG_1004H, 0x40400010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000448U);
    WR1_PROG(REG_1018H, 0x00000878U);
    WR1_PROG(REG_101CH, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x40400002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_101CH, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x40400003U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000448U);
    WR1_PROG(REG_1018H, 0x00000230U);
    WR1_PROG(REG_101CH, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000230U);

    WR1_PROG(REG_1004H, 0x40400002U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x14600000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00010001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x75f6ae8aU),
                   bswap_32big(0x62d61efdU),
                   bswap_32big(0x6002bbccU),
                   bswap_32big(0x0fd08483U));
    r_rsip_func321();

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c001fdU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000660U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000a90U);
    WR1_PROG(REG_1018H, 0x00000660U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x4040000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    r_rsip_func100(bswap_32big(0x509f3ab6U),
                   bswap_32big(0x67fdc39eU),
                   bswap_32big(0xa206f2ccU),
                   bswap_32big(0x9537d209U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xd78663c1U), bswap_32big(0x8dec69ffU), bswap_32big(0xbb663cb7U),
                       bswap_32big(0xf6ce8835U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }

    WR1_PROG(REG_1404H, 0x18900000U);
    WR1_PROG(REG_1400H, 0x00c00201U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000878U);
    WR1_PROG(REG_1018H, 0x00000a90U);
    WR1_PROG(REG_1020H, 0x00000448U);

    WR1_PROG(REG_1004H, 0x40400009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b040184U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x360905f3U));

    OFS_ADR = 808;

    WR1_PROG(REG_1404H, 0x14600000U);

    WR1_PROG(REG_1600H, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b03U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x460b701bU),
                   bswap_32big(0xf27a8b01U),
                   bswap_32big(0x86637c6eU),
                   bswap_32big(0x15a10f2fU));
    r_rsip_func017(OFS_ADR);

    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x00010001U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b06U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x8bb0aa17U),
                   bswap_32big(0xc52cf8a7U),
                   bswap_32big(0x236250abU),
                   bswap_32big(0x3ab6186bU));
    r_rsip_func113();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x32ed4c3fU),
                   bswap_32big(0xfc9853daU),
                   bswap_32big(0x69a8e333U),
                   bswap_32big(0x8f2c6ae9U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000011U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b01U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xbab165dfU),
                   bswap_32big(0xea5f053fU),
                   bswap_32big(0x9cc97e5fU),
                   bswap_32big(0xa3ab25eeU));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00000884U);
    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x14600000U);
    for (iLoop = 0U; iLoop < 128U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x417b502eU), bswap_32big(0xabbdaf08U), bswap_32big(0xab0e9843U),
                       bswap_32big(0x4489b2b7U));
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe7008d05U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[1 + iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        r_rsip_func101(bswap_32big(0x476fdeb3U), bswap_32big(0xc68ebad2U), bswap_32big(0x30fd0d92U),
                       bswap_32big(0xa00cd93eU));
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000886U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00000884U);
    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x12480000U);
    for (iLoop = 0U; iLoop < 128U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x763f5e48U), bswap_32big(0x72927fdaU), bswap_32big(0x820bdc09U),
                       bswap_32big(0xc44ae84fU));
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe7008d05U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[129 + iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        r_rsip_func101(bswap_32big(0x459ba85bU), bswap_32big(0x899a5235U), bswap_32big(0x20383419U),
                       bswap_32big(0x29a83e03U));
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000886U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func100(bswap_32big(0x1e2a72bdU),
                   bswap_32big(0x5db0e968U),
                   bswap_32big(0xc34f2212U),
                   bswap_32big(0x022b33cdU));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PrivKeyIndex[257]);

    r_rsip_func100(bswap_32big(0x1676c8baU),
                   bswap_32big(0x97e09d5dU),
                   bswap_32big(0x1212dd81U),
                   bswap_32big(0x9fe7c745U));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_PrivKeyIndex[0]);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b07U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xbc6b2673U),
                   bswap_32big(0x04551e73U),
                   bswap_32big(0xf0cef891U),
                   bswap_32big(0x6677ccfdU));
    r_rsip_func113();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x19538ee2U),
                   bswap_32big(0x8bd76535U),
                   bswap_32big(0x8b3362a6U),
                   bswap_32big(0x0698f638U));
    r_rsip_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000010U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00003b02U));
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xdfe0280dU),
                   bswap_32big(0xa02a7c45U),
                   bswap_32big(0x115f778dU),
                   bswap_32big(0xdcd304fdU));
    r_rsip_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x00000884U);
    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x000008e7U);

    WR1_PROG(REG_1404H, 0x14600000U);
    for (iLoop = 0U; iLoop < 128U; )
    {
        WR1_PROG(REG_1600H, 0x34202886U);
        WR1_PROG(REG_1600H, 0x2000d0e0U);
        WR1_PROG(REG_1600H, 0x00007c07U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x51749134U), bswap_32big(0xee71497eU), bswap_32big(0x9d76c078U),
                       bswap_32big(0xa8af4895U));
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[1 + iLoop]);

        WR1_PROG(REG_1600H, 0x00002485U);

        r_rsip_func101(bswap_32big(0xf5cc0599U), bswap_32big(0x207d18a2U), bswap_32big(0xdaf0184bU),
                       bswap_32big(0x32b8b67dU));
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000886U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func100(bswap_32big(0xea7c6de5U),
                   bswap_32big(0x52aac35eU),
                   bswap_32big(0xeada5e0dU),
                   bswap_32big(0x3bb4b6d5U));
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xe8008104U);
    WR1_PROG(REG_1608H, 0x81010280U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[129]);

    r_rsip_func100(bswap_32big(0x86877c2bU),
                   bswap_32big(0xc8186f67U),
                   bswap_32big(0xf68c387aU),
                   bswap_32big(0x75a031d5U));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_PubKeyIndex[133]);

    r_rsip_func100(bswap_32big(0xd2936377U),
                   bswap_32big(0x5a5d7e76U),
                   bswap_32big(0xc7a4e8eaU),
                   bswap_32big(0xc56946d9U));
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &OutData_PubKeyIndex[0]);

    r_rsip_func102(bswap_32big(0x4c252cefU),
                   bswap_32big(0x7702e86bU),
                   bswap_32big(0x01808324U),
                   bswap_32big(0x5967d15fU));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
