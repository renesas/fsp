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

rsip_ret_t r_rsip_pe7 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataType[],
                       const uint32_t InData_OutDataLocation[],
                       const uint32_t InData_SeqNum[],
                       uint32_t       OutData_HMACKeyIndex[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       OutData_EncIV[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e70001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000002c7U);
    WR1_PROG(REG_1608H, 0x80030080U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KDFInfo_Count[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_OutDataType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x30003080U);
    WR1_PROG(REG_1600H, 0x00070020U);
    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x08000000U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x05555555U);
    WR1_PROG(REG_1600H, 0x00050040U);
    WR1_PROG(REG_1600H, 0x0000b680U);
    WR1_PROG(REG_1600H, 0x04000000U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x3000a8c0U);
    WR1_PROG(REG_1600H, 0x00000009U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000008U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x38000ca5U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x34202a85U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x380088c0U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0x66e78dc6U),
                   bswap_32big(0x82f80f9cU),
                   bswap_32big(0xea743073U),
                   bswap_32big(0x06cba152U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x2f151912U), bswap_32big(0x65d514e8U), bswap_32big(0x8617efe7U),
                       bswap_32big(0xb7f69aa0U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xbbc82708U), bswap_32big(0xd2269029U), bswap_32big(0xc7c7e100U),
                       bswap_32big(0xe7b8f696U));
        WR1_PROG(REG_1600H, 0x00007c06U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x00000005U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xf2f5a516U), bswap_32big(0x06a3b8f1U), bswap_32big(0xcb1dfdb6U),
                           bswap_32big(0x6c39b842U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x00000007U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x12bd3407U), bswap_32big(0x3cfdda92U), bswap_32big(0x568480cbU),
                           bswap_32big(0x41c5a77eU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0199e556U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xc8e83836U), bswap_32big(0x5eae7d6aU), bswap_32big(0x523963bdU),
                           bswap_32big(0x8b39b682U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0199e556U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000003U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xe4cf8d06U), bswap_32big(0xb76e6bcdU), bswap_32big(0x0f93404fU),
                           bswap_32big(0xe5bd611dU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0199e556U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000bU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xec3e3599U), bswap_32big(0x7b92e833U), bswap_32big(0xf039b581U),
                           bswap_32big(0x8e41bc87U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x0000001bU);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x9f21502aU), bswap_32big(0x5940cf6cU), bswap_32big(0x317a571aU),
                           bswap_32big(0xfbde2f68U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000007U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x00000028U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000002fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x8f124057U), bswap_32big(0xcc7e625dU), bswap_32big(0x5f49a9c8U),
                           bswap_32big(0x9f11f08fU));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000008U)
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1600H, 0x00000029U);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x0000003fU));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xb3fa54f9U), bswap_32big(0x128fcf24U), bswap_32big(0xa9193973U),
                           bswap_32big(0xeac5840eU));
        }

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010100U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_OutDataLocation[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x30003080U);
        WR1_PROG(REG_1600H, 0x00070020U);

        WR1_PROG(REG_1600H, 0x0000b600U);
        WR1_PROG(REG_1600H, 0x0000001fU);

        WR1_PROG(REG_1600H, 0x0000b460U);
        WR1_PROG(REG_1600H, 0x0000000dU);

        WR1_PROG(REG_1600H, 0x00003685U);
        WR1_PROG(REG_1600H, 0x00056e94U);
        WR1_PROG(REG_1600H, 0x00003280U);

        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x30003080U);
        WR1_PROG(REG_1600H, 0x00030020U);

        WR1_PROG(REG_1600H, 0x0000b600U);
        WR1_PROG(REG_1600H, 0x0000002fU);

        WR1_PROG(REG_1600H, 0x0000b460U);
        WR1_PROG(REG_1600H, 0x00000011U);

        WR1_PROG(REG_1600H, 0x00003685U);
        WR1_PROG(REG_1600H, 0x00046e94U);
        WR1_PROG(REG_1600H, 0x000036a5U);
        WR1_PROG(REG_1600H, 0x00056eb4U);
        WR1_PROG(REG_1600H, 0x00002695U);
        WR1_PROG(REG_1600H, 0x00003280U);

        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x30003080U);
        WR1_PROG(REG_1600H, 0x00050020U);

        WR1_PROG(REG_1600H, 0x0000b600U);
        WR1_PROG(REG_1600H, 0x0000003fU);

        WR1_PROG(REG_1600H, 0x0000b460U);
        WR1_PROG(REG_1600H, 0x00000015U);

        WR1_PROG(REG_1600H, 0x00003685U);
        WR1_PROG(REG_1600H, 0x00066e94U);
        WR1_PROG(REG_1600H, 0x00003280U);

        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x00003628U);
        WR1_PROG(REG_1600H, 0x0000262eU);

        WR1_PROG(REG_1600H, 0x34202a91U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x34202911U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x17ecf5d1U), bswap_32big(0x81f878a2U), bswap_32big(0x038d4301U),
                       bswap_32big(0x8f2051eaU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x6233df11U), bswap_32big(0x4c81567cU), bswap_32big(0x4700e274U),
                           bswap_32big(0x4b64a2b9U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x50061ef5U), bswap_32big(0x743fb9ebU), bswap_32big(0x1e955c91U),
                           bswap_32big(0xfff04a32U));

            WR1_PROG(REG_1600H, 0x00000a73U);

            WR1_PROG(REG_1600H, 0x00000ab5U);

            WR1_PROG(REG_1600H, 0x000009efU);

            WR1_PROG(REG_1600H, 0x00000a94U);

            WR1_PROG(REG_1600H, 0x00000ad6U);

            WR1_PROG(REG_1600H, 0x00000af7U);

            WR1_PROG(REG_1608H, 0x81010060U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);
            OFS_ADR  = S_RAM[0];

            r_rsip_func100(bswap_32big(0x693e116bU), bswap_32big(0x67b68b94U), bswap_32big(0xf6860e15U),
                           bswap_32big(0x3d09544eU));
            WR1_PROG(REG_1608H, 0x810100a0U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x34202a65U);
                WR1_PROG(REG_1600H, 0x2000d2c0U);
                WR1_PROG(REG_1600H, 0x00007c16U);
                WR1_PROG(REG_143CH, 0x00602000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x34202a35U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_1600H, 0x000026b0U);

                WR1_PROG(REG_1600H, 0x34202aa8U);
                WR1_PROG(REG_1600H, 0x100026f0U);
                WR1_PROG(REG_1600H, 0x10002ee0U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0xcc04d82fU),
                               bswap_32big(0xfca1088dU),
                               bswap_32big(0x19b61a23U),
                               bswap_32big(0xcd72ff27U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    r_rsip_func101(bswap_32big(0xace5090fU),
                                   bswap_32big(0xd63de514U),
                                   bswap_32big(0xd79a14aaU),
                                   bswap_32big(0x3a35994bU));
                }
                else
                {
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x800100e0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, InData_KDFInfo[iLoop * OFS_ADR]);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e701U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x0992a21fU),
                                   bswap_32big(0x06e5a9a3U),
                                   bswap_32big(0xef1cec55U),
                                   bswap_32big(0x142cecb4U));
                    r_rsip_func043();

                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1600H, 0x01799093U);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e701U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x9c61fffbU),
                                   bswap_32big(0x09e3315bU),
                                   bswap_32big(0xcfd3ddfdU),
                                   bswap_32big(0x24fcc7abU));
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

                        WR1_PROG(REG_1608H, 0x8084000fU);
                        WR1_PROG(REG_1400H, 0x03420011U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1600H, 0x0000a5e0U);
                        WR1_PROG(REG_1600H, 0x00000010U);

                        WR1_PROG(REG_1600H, 0x0000a440U);
                        WR1_PROG(REG_1600H, 0x00000004U);

                        r_rsip_func101(bswap_32big(0xa571703aU),
                                       bswap_32big(0x25c45bd7U),
                                       bswap_32big(0x7bed084bU),
                                       bswap_32big(0xaa19d7ddU));
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

                    r_rsip_func100(bswap_32big(0x6cc70a6cU),
                                   bswap_32big(0xf6257653U),
                                   bswap_32big(0x5f254811U),
                                   bswap_32big(0x51683710U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x0000d280U);
                        r_rsip_func101(bswap_32big(0x351a8e36U),
                                       bswap_32big(0x7ae7c091U),
                                       bswap_32big(0x8d865b3bU),
                                       bswap_32big(0xc77621ecU));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x05209ca6U),
                                       bswap_32big(0x1e31a528U),
                                       bswap_32big(0x509d513bU),
                                       bswap_32big(0x21856440U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);
                }

                WR1_PROG(REG_1600H, 0x00002ea0U);

                WR1_PROG(REG_1600H, 0x00002e60U);

                r_rsip_func101(bswap_32big(0x0f72f0e1U),
                               bswap_32big(0xdf4699edU),
                               bswap_32big(0x39f23856U),
                               bswap_32big(0x5e7b7138U));
            }

            WR1_PROG(REG_1600H, 0x38000a65U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x38000e94U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);
            r_rsip_func100(bswap_32big(0xda13e26eU), bswap_32big(0xe133728eU), bswap_32big(0xaf77d4a4U),
                           bswap_32big(0x4db6ce65U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xd78e043cU),
                               bswap_32big(0x3dc1bafcU),
                               bswap_32big(0x8e723d8bU),
                               bswap_32big(0x63220465U));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x000000e7U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0xdc3b6733U),
                               bswap_32big(0x382f721dU),
                               bswap_32big(0xc9407de3U),
                               bswap_32big(0x5f0b3e87U));
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
                WR1_PROG(REG_1420H, bswap_32big(0x0000e702U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x2e0b0276U),
                               bswap_32big(0xad5fab07U),
                               bswap_32big(0xf3d5e64fU),
                               bswap_32big(0x93b1ee25U));
                r_rsip_func043();

                WR1_PROG(REG_1600H, 0x000034e9U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e702U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x2135551dU),
                               bswap_32big(0x1ea02da0U),
                               bswap_32big(0xd7ef2847U),
                               bswap_32big(0x5394ae29U));
                r_rsip_func044();

                WR1_PROG(REG_1600H, 0x00002917U);

                WR1_PROG(REG_1600H, 0x0000b5e0U);
                WR1_PROG(REG_1600H, 0x00000080U);

                WR1_PROG(REG_1600H, 0x3420a8c0U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0xcdadaf95U),
                               bswap_32big(0xd3a0e66aU),
                               bswap_32big(0x7b13edaaU),
                               bswap_32big(0xf2ca94f7U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    for (iLoop = 0U; iLoop < 32U; iLoop++)
                    {
                        WR1_PROG(REG_1600H, 0x00000ab5U);

                        WR1_PROG(REG_1600H, 0x02003aa8U);
                        WR1_PROG(REG_1600H, 0x02003eafU);

                        WR1_PROG(REG_1600H, 0x00002d00U);
                        WR1_PROG(REG_1600H, 0x00002de0U);
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x0000b5e0U);
                    WR1_PROG(REG_1600H, 0x00000080U);

                    WR1_PROG(REG_1600H, 0x38000cc6U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    r_rsip_func100(bswap_32big(0x7fa36711U),
                                   bswap_32big(0x6a700b27U),
                                   bswap_32big(0xea1b607cU),
                                   bswap_32big(0x7ddb8d2dU));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0x44053fd0U),
                                       bswap_32big(0x1a0e3326U),
                                       bswap_32big(0xe2ed1fd7U),
                                       bswap_32big(0xabd3cbfbU));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe7009d05U);

                        WR1_PROG(REG_1608H, 0x8184000fU);
                        WR1_PROG(REG_1400H, 0x00890011U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);

                        r_rsip_func100(bswap_32big(0xcdcc2e2eU),
                                       bswap_32big(0x6a772b76U),
                                       bswap_32big(0x44bdff0eU),
                                       bswap_32big(0x76dff7feU));
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
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

                        r_rsip_func101(bswap_32big(0x1bc30a38U),
                                       bswap_32big(0x93df629bU),
                                       bswap_32big(0x557aa8cdU),
                                       bswap_32big(0xbb007b11U));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x864f4d31U),
                                       bswap_32big(0xc126923bU),
                                       bswap_32big(0xb1917342U),
                                       bswap_32big(0xb6a08bb0U));
                        WR1_PROG(REG_1A2CH, 0x40000100U);
                        WR1_PROG(REG_1A24H, 0xe7009d07U);

                        WR1_PROG(REG_1608H, 0x8188000fU);
                        WR1_PROG(REG_1400H, 0x00890021U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[1]);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[5]);

                        r_rsip_func100(bswap_32big(0x42246865U),
                                       bswap_32big(0x2b683870U),
                                       bswap_32big(0x9e1aff84U),
                                       bswap_32big(0x52fc3ab5U));
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
                        RD4_ADDR(REG_1420H, &OutData_KeyIndex[9]);

                        r_rsip_func101(bswap_32big(0xa03af004U),
                                       bswap_32big(0xe69b5053U),
                                       bswap_32big(0x7a3c7f56U),
                                       bswap_32big(0x13733d7cU));
                    }

                    r_rsip_func100(bswap_32big(0xbfac564aU),
                                   bswap_32big(0x479f3edaU),
                                   bswap_32big(0xf4bf26c8U),
                                   bswap_32big(0xbf659d4fU));
                    WR1_PROG(REG_1608H, 0x81010000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                    r_rsip_func102(bswap_32big(0x104da134U),
                                   bswap_32big(0x22eaaa9fU),
                                   bswap_32big(0x7e331779U),
                                   bswap_32big(0xd6b28d59U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_PASS;
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x3420a8c0U);
                    WR1_PROG(REG_1600H, 0x00000005U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0xccfd197aU),
                                   bswap_32big(0x5f232ab6U),
                                   bswap_32big(0xfe915969U),
                                   bswap_32big(0xa69328d8U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        for (iLoop = 0U; iLoop < 64U; iLoop++)
                        {
                            WR1_PROG(REG_1600H, 0x00000ab5U);

                            WR1_PROG(REG_1600H, 0x02003aa8U);
                            WR1_PROG(REG_1600H, 0x02003eafU);

                            WR1_PROG(REG_1600H, 0x00002d00U);
                            WR1_PROG(REG_1600H, 0x00002de0U);
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);

                        WR1_PROG(REG_1600H, 0x0000b5e0U);
                        WR1_PROG(REG_1600H, 0x00000080U);

                        WR1_PROG(REG_1600H, 0x000008e7U);

                        r_rsip_func100(bswap_32big(0x79ae61a0U),
                                       bswap_32big(0x1608da44U),
                                       bswap_32big(0x0549ac71U),
                                       bswap_32big(0xf737a3c3U));
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000044U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000054U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                        WR1_PROG(REG_1600H, 0x00002dc0U);
                        WR1_PROG(REG_1600H, 0x000269ceU);

                        WR1_PROG(REG_1608H, 0x810101c0U);
                        WR1_PROG(REG_1408H, 0x00005006U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD1_ADDR(REG_1420H, &S_RAM[0]);
                        S_RAM[0] = bswap_32big(S_RAM[0]);

                        for (iLoop = 0U; iLoop < S_RAM[0]; )
                        {
                            r_rsip_func100(bswap_32big(0xb95fec6bU),
                                           bswap_32big(0xcd02edb3U),
                                           bswap_32big(0x08a72052U),
                                           bswap_32big(0xead94f63U));
                            WR1_PROG(REG_1A2CH, 0x40000000U);
                            WR1_PROG(REG_1A24H, 0xe7008d05U);
                            WR1_PROG(REG_1608H, 0x8184000fU);
                            WR1_PROG(REG_1400H, 0x00890011U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1408H, 0x00002012U);
                            WAIT_STS(REG_1408H, 30, 1);
                            RD4_ADDR(REG_1420H, &OutData_HMACKeyIndex[iLoop + 1]);

                            WR1_PROG(REG_1600H, 0x0000a5e0U);
                            WR1_PROG(REG_1600H, 0x00000010U);

                            WR1_PROG(REG_1600H, 0x0000a4e0U);
                            WR1_PROG(REG_1600H, 0x00000004U);

                            r_rsip_func101(bswap_32big(0x584cbaa9U),
                                           bswap_32big(0x4100b76fU),
                                           bswap_32big(0x25422872U),
                                           bswap_32big(0x8fdedb23U));
                            iLoop = iLoop + 4U;
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);

                        WR1_PROG(REG_1600H, 0x380009c7U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        WR1_PROG(REG_143CH, 0x00402000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        r_rsip_func100(bswap_32big(0xc1f4458dU),
                                       bswap_32big(0xc6ed5e97U),
                                       bswap_32big(0x99814f08U),
                                       bswap_32big(0xd2bbb6acU));
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
                        RD4_ADDR(REG_1420H, &OutData_HMACKeyIndex[iLoop + 1]);

                        r_rsip_func100(bswap_32big(0xe2576ba7U),
                                       bswap_32big(0x024d360fU),
                                       bswap_32big(0x1de5cf02U),
                                       bswap_32big(0xbe08c4d2U));
                        WR1_PROG(REG_1608H, 0x81010000U);
                        WR1_PROG(REG_1408H, 0x00005006U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[0]);

                        r_rsip_func102(bswap_32big(0x5e1bac4aU),
                                       bswap_32big(0x09f27b17U),
                                       bswap_32big(0xc35619beU),
                                       bswap_32big(0x1f53ac69U));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return RSIP_RET_PASS;
                    }
                    else
                    {
                        for (iLoop = 0U; iLoop < 16U; iLoop++)
                        {
                            WR1_PROG(REG_1600H, 0x00000ab5U);

                            WR1_PROG(REG_1600H, 0x02003aa8U);
                            WR1_PROG(REG_1600H, 0x02003eafU);

                            WR1_PROG(REG_1600H, 0x00002d00U);
                            WR1_PROG(REG_1600H, 0x00002de0U);
                        }

                        WR1_PROG(REG_1458H, 0x00000000U);

                        WR1_PROG(REG_1600H, 0x0000b5e0U);
                        WR1_PROG(REG_1600H, 0x00000080U);

                        WR1_PROG(REG_1600H, 0x380088c0U);
                        WR1_PROG(REG_1600H, 0x00000002U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0xc6903c6bU),
                                       bswap_32big(0x21f6649bU),
                                       bswap_32big(0x6ff1fb50U),
                                       bswap_32big(0x935ca698U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1A24H, 0x08000105U);
                            WR1_PROG(REG_1608H, 0x8184000fU);
                            WR1_PROG(REG_1400H, 0x00890011U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1608H, 0x80040140U);
                            WR1_PROG(REG_1400H, 0x03420011U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0x07d58005U),
                                           bswap_32big(0xa6d5047dU),
                                           bswap_32big(0xa47b7ac7U),
                                           bswap_32big(0xfc6f30b8U));
                        }
                        else
                        {
                            WR1_PROG(REG_1444H, 0x000001c7U);
                            WR1_PROG(REG_1608H, 0x80020080U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, InData_SeqNum[0]);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, InData_SeqNum[1]);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            WR1_PROG(REG_1600H, 0x380088c0U);
                            WR1_PROG(REG_1600H, 0x00000003U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);

                            r_rsip_func100(bswap_32big(0x8d6174c4U),
                                           bswap_32big(0x662a3f1eU),
                                           bswap_32big(0xe8a69f4cU),
                                           bswap_32big(0x0f408ceeU));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                WR1_PROG(REG_1600H, 0x0000394fU);

                                WR1_PROG(REG_1600H, 0x00003564U);
                                WR1_PROG(REG_1600H, 0x00003585U);

                                WR1_PROG(REG_1600H, 0x0000b5a0U);
                                WR1_PROG(REG_1600H, 0x00000001U);

                                r_rsip_func101(bswap_32big(0xf2d48b40U), bswap_32big(0x28b9ddbcU),
                                               bswap_32big(0xdca6df5eU), bswap_32big(0xfe98daeeU));
                            }
                            else
                            {
                                WR1_PROG(REG_1A24H, 0x08000105U);
                                WR1_PROG(REG_1608H, 0x8183000fU);
                                WR1_PROG(REG_1400H, 0x0089000dU);
                                WAIT_STS(REG_1404H, 30, 0);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1400H, 0x00800005U);
                                WAIT_STS(REG_1404H, 30, 0);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1608H, 0x80040140U);
                                WR1_PROG(REG_1400H, 0x03420011U);
                                WAIT_STS(REG_1404H, 30, 0);
                                WR1_PROG(REG_143CH, 0x00001800U);

                                WR1_PROG(REG_1600H, 0x00000964U);
                                WR1_PROG(REG_1600H, 0x00000985U);

                                WR1_PROG(REG_1600H, 0x0000b5a0U);
                                WR1_PROG(REG_1600H, 0x00000001U);

                                r_rsip_func101(bswap_32big(0x67366776U), bswap_32big(0xfc5de326U),
                                               bswap_32big(0x93ceaed1U), bswap_32big(0xa99d8678U));
                            }
                        }

                        r_rsip_func100(bswap_32big(0x2fe01943U),
                                       bswap_32big(0x678b398fU),
                                       bswap_32big(0x55180509U),
                                       bswap_32big(0xb177a085U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe7009d05U);

                        WR1_PROG(REG_1608H, 0x81040140U);
                        WR1_PROG(REG_1400H, 0x00890011U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_EncIV[1]);

                        r_rsip_func100(bswap_32big(0x515aac5fU),
                                       bswap_32big(0x5176d607U),
                                       bswap_32big(0xd5aee535U),
                                       bswap_32big(0x97d45531U));
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
                        RD4_ADDR(REG_1420H, &OutData_EncIV[5]);

                        r_rsip_func100(bswap_32big(0x541431d4U),
                                       bswap_32big(0xf3518144U),
                                       bswap_32big(0x15642c73U),
                                       bswap_32big(0xf072531dU));
                        WR1_PROG(REG_1608H, 0x81010000U);
                        WR1_PROG(REG_1408H, 0x00005006U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[0]);

                        r_rsip_func102(bswap_32big(0xdc55094cU),
                                       bswap_32big(0x1ea32b4eU),
                                       bswap_32big(0x2e3c8351U),
                                       bswap_32big(0x9ce89533U));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return RSIP_RET_PASS;
                    }
                }
            }
        }
    }
}
