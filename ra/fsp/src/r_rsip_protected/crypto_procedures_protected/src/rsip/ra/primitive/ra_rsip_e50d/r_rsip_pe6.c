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

rsip_ret_t r_rsip_pe6 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataLength[],
                       uint32_t       OutData_KeyIndex[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e60001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x30003080U);
    WR1_PROG(REG_1600H, 0x00070020U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000020U);

    WR1_PROG(REG_1600H, 0x0000b460U);
    WR1_PROG(REG_1600H, 0x0000000dU);

    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x01b41ce9U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000030U);

    WR1_PROG(REG_1600H, 0x0000b460U);
    WR1_PROG(REG_1600H, 0x00000011U);

    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x0199f119U);
    WR1_PROG(REG_1600H, 0x00050040U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000001U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000040U);

    WR1_PROG(REG_1600H, 0x0000b460U);
    WR1_PROG(REG_1600H, 0x00000015U);

    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x01b4cab0U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KDFInfo_Count[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000ca5U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x342028c5U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x86fc6261U),
                   bswap_32big(0x73413f58U),
                   bswap_32big(0x024cd898U),
                   bswap_32big(0x9da756c8U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x74346ae0U), bswap_32big(0x2823702fU), bswap_32big(0x5196d508U),
                       bswap_32big(0x6cd6abc2U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_OutDataLength[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x300030a0U);
        WR1_PROG(REG_1600H, 0x00030020U);
        WR1_PROG(REG_1600H, 0x00003547U);

        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1600H, 0x0000b540U);
        WR1_PROG(REG_1600H, 0x00000040U);

        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x342028c7U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x34202946U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        r_rsip_func100(bswap_32big(0x4be3e91fU), bswap_32big(0x3ca3b0f1U), bswap_32big(0x4ccae43cU),
                       bswap_32big(0xc7db144eU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x09b0f5b5U), bswap_32big(0x5bb2b55dU), bswap_32big(0x61eb8d8bU),
                           bswap_32big(0x902b2564U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x71ac79acU), bswap_32big(0xd98054ffU), bswap_32big(0x755acf41U),
                           bswap_32big(0x5fa060e1U));
            WR1_PROG(REG_1608H, 0x810100a0U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            r_rsip_func100(bswap_32big(0xaed15345U), bswap_32big(0xe647ff87U), bswap_32big(0xfe9d70d4U),
                           bswap_32big(0x159524a7U));
            WR1_PROG(REG_1608H, 0x81010060U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
            S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);
            OFS_ADR      = S_RAM[0 + 1];

            WR1_PROG(REG_1600H, 0x00000908U);

            WR1_PROG(REG_1600H, 0x00000929U);

            WR1_PROG(REG_1600H, 0x000009ceU);

            WR1_PROG(REG_1600H, 0x000009efU);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x34202905U);
                WR1_PROG(REG_1600H, 0x2000d1e0U);
                WR1_PROG(REG_1600H, 0x00007c0fU);
                WR1_PROG(REG_143CH, 0x00602000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KDFInfo[iLoop * OFS_ADR]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e601U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x2600618eU),
                               bswap_32big(0xfd61db2cU),
                               bswap_32big(0xf31ea1c0U),
                               bswap_32big(0x05799483U));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1600H, 0x01799093U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e601U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x5d60f3faU),
                               bswap_32big(0x2db9487aU),
                               bswap_32big(0xe10967efU),
                               bswap_32big(0xfa6b512eU));
                r_rsip_func044();

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000044U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000054U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1600H, 0x00000842U);

                for (jLoop = 0U; jLoop < OFS_ADR - 5; )
                {
                    WR1_PROG(REG_1444H, 0x000003c2U);
                    WR1_PROG(REG_1A2CH, 0x40000000U);
                    WR1_PROG(REG_1A24H, 0xf7008d05U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_KDFInfo[1 + jLoop + iLoop * OFS_ADR]);

                    WR1_PROG(REG_1608H, 0x80840009U);
                    WR1_PROG(REG_1400H, 0x03420011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x0000a520U);
                    WR1_PROG(REG_1600H, 0x00000010U);

                    WR1_PROG(REG_1600H, 0x0000a440U);
                    WR1_PROG(REG_1600H, 0x00000004U);

                    r_rsip_func101(bswap_32big(0x60b34839U),
                                   bswap_32big(0xf4f4d07cU),
                                   bswap_32big(0x5dbcf28bU),
                                   bswap_32big(0x3e5f6892U));
                    jLoop = jLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000037e3U);
                WR1_PROG(REG_1600H, 0x0000abe0U);
                WR1_PROG(REG_1600H, 0x00000005U);

                WR1_PROG(REG_1600H, 0x38000be2U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KDFInfo[1 + jLoop + iLoop * OFS_ADR]);

                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00002d00U);

                r_rsip_func100(bswap_32big(0x0afd354dU),
                               bswap_32big(0xc30bbd44U),
                               bswap_32big(0xf1ce9ac0U),
                               bswap_32big(0x1b2b7350U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x0000d1c0U);
                    r_rsip_func101(bswap_32big(0xd23de98cU),
                                   bswap_32big(0xdc9fde27U),
                                   bswap_32big(0x5561a79eU),
                                   bswap_32big(0xf911f5eeU));
                }
                else
                {
                    r_rsip_func101(bswap_32big(0xbe0b111cU),
                                   bswap_32big(0x9774077dU),
                                   bswap_32big(0xe1b9ba3fU),
                                   bswap_32big(0x2f1f9d4fU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);
            }

            WR1_PROG(REG_1600H, 0x38000905U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000dceU);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);
            r_rsip_func100(bswap_32big(0xe53c68e9U), bswap_32big(0x190addaeU), bswap_32big(0x292144a6U),
                           bswap_32big(0x5242f435U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xb8d7f1c4U),
                               bswap_32big(0x471e9524U),
                               bswap_32big(0x2e5f6656U),
                               bswap_32big(0x1066d94dU));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x745c3c70U),
                               bswap_32big(0x1988cc90U),
                               bswap_32big(0x7a9fbd1fU),
                               bswap_32big(0x6d6dec98U));
                WR1_PROG(REG_1608H, 0x810100c0U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1600H, 0x0000094aU);

                WR1_PROG(REG_1600H, 0x0000b560U);
                WR1_PROG(REG_1600H, 0x00000040U);
                WR1_PROG(REG_1600H, 0x00002966U);

                WR1_PROG(REG_1600H, 0x00000908U);
                WR1_PROG(REG_1600H, 0x00003526U);

                for (iLoop = S_RAM[0]; iLoop < 64U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x02003d49U);
                    WR1_PROG(REG_1600H, 0x00002d00U);
                    WR1_PROG(REG_1600H, 0x00002d20U);
                    r_rsip_func101(bswap_32big(0x8598ab1aU),
                                   bswap_32big(0xa1d4fab4U),
                                   bswap_32big(0x31fe2d86U),
                                   bswap_32big(0x29c272dbU));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x3800090bU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x000000e6U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xf9f9cfd4U),
                               bswap_32big(0x3681b8b3U),
                               bswap_32big(0xe81449d0U),
                               bswap_32big(0x599f8951U));
                r_rsip_func103();

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
                WR1_PROG(REG_1420H, bswap_32big(0x0000e602U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xd7a83816U),
                               bswap_32big(0xc165a7bdU),
                               bswap_32big(0x6b34c42cU),
                               bswap_32big(0x33ef8033U));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x000034f4U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e602U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x9ec70516U),
                               bswap_32big(0x279ab210U),
                               bswap_32big(0x4afd0185U),
                               bswap_32big(0x971c06bdU));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0x5b824665U),
                               bswap_32big(0x31202ed1U),
                               bswap_32big(0x929e7270U),
                               bswap_32big(0x17a91801U));
                WR1_PROG(REG_1600H, 0x00000929U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xe7009d07U);

                WR1_PROG(REG_1608H, 0x81900009U);
                WR1_PROG(REG_1400H, 0x00890021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1408H, 0x00002022U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

                r_rsip_func100(bswap_32big(0x03e2f623U),
                               bswap_32big(0x9931a480U),
                               bswap_32big(0xdd19d07aU),
                               bswap_32big(0xb96ead96U));
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xe7008d07U);
                WR1_PROG(REG_1400H, 0x00890021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1408H, 0x00002022U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KeyIndex[9]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_KeyIndex[13]);

                r_rsip_func100(bswap_32big(0x05855d7aU),
                               bswap_32big(0x59e3f930U),
                               bswap_32big(0xa1cc8cd3U),
                               bswap_32big(0xe596233bU));
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
                RD4_ADDR(REG_1420H, &OutData_KeyIndex[17]);

                r_rsip_func100(bswap_32big(0x0c3a9da3U),
                               bswap_32big(0xce12cd51U),
                               bswap_32big(0x40140142U),
                               bswap_32big(0x2d298f8eU));
                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                r_rsip_func102(bswap_32big(0x7b06b4eeU),
                               bswap_32big(0xfd66a282U),
                               bswap_32big(0xbb25d0ffU),
                               bswap_32big(0xe5dd99f1U));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
