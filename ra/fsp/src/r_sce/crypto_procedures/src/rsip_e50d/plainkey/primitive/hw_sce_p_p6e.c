/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_GenerateOemKeyIndexSub (const uint32_t InData_KeyType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_SharedKeyIndex[],
                                         const uint32_t InData_SessionKey[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[])
{
    uint32_t OFS_ADR = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x006e0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800103e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x27a1a378U, 0xb1e702c6U, 0xc089e2ccU, 0x03beb809U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func049_r1(InData_Cmd);

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010020U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(InData_SharedKeyIndex[0]));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x0000094aU);

        WR1_PROG(REG_1600H, 0x000037e4U);

        WR1_PROG(REG_1600H, 0x3000a880U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1600H, 0x3000a880U);
        WR1_PROG(REG_1600H, 0x00000030U);
        WR1_PROG(REG_1600H, 0x00040020U);
        WR1_PROG(REG_1600H, 0x0000b480U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x38008880U);
        WR1_PROG(REG_1600H, 0x000000ffU);
        WR1_PROG(REG_1600H, 0x1000b480U);
        WR1_PROG(REG_1600H, 0x00000005U);

        WR1_PROG(REG_1600H, 0x38008880U);
        WR1_PROG(REG_1600H, 0x000000feU);
        WR1_PROG(REG_1600H, 0x1000b480U);
        WR1_PROG(REG_1600H, 0x00000005U);

        WR1_PROG(REG_1600H, 0x3420a820U);
        WR1_PROG(REG_1600H, 0x00000010U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        HW_SCE_p_func100(0x12375f1eU, 0xd716167dU, 0x4b8af10aU, 0x8254ab2fU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x0e4da44aU, 0xec11e3b0U, 0xaebb255eU, 0x30092d00U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x0000349fU);

            OFS_ADR = InData_SharedKeyIndex[0] << 3;

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0000006eU));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xffcd1155U, 0x23d7aeb1U, 0xfba71f19U, 0x374713deU);
            HW_SCE_p_func058_r1(InData_SessionKey, OFS_ADR);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x80010380U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0000006eU));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xfbeae9b9U, 0xb3dd9b58U, 0xf3a3d73fU, 0x2d5e323dU);
            HW_SCE_p_func057_r1(InData_IV, InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0xfbc657a3U, 0xcb4f283fU, 0x447eb3e5U, 0x43e8473dU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x3dc32268U, 0xea40c066U, 0x38de8720U, 0xc6bf2474U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0x117b1137U, 0xf873bbffU, 0x5bac2524U, 0x7588c157U);
                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

                HW_SCE_p_func102(0x8ec70a83U, 0x18f8da3cU, 0x16aa90aeU, 0x99f49cddU);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
    else
    {
        HW_SCE_p_func049_r1(InData_Cmd);

        WR1_PROG(REG_1600H, 0x000037e4U);

        WR1_PROG(REG_1600H, 0x3000a880U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1600H, 0x3000a880U);
        WR1_PROG(REG_1600H, 0x00000030U);
        WR1_PROG(REG_1600H, 0x00040020U);
        WR1_PROG(REG_1600H, 0x0000b480U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x38008880U);
        WR1_PROG(REG_1600H, 0x000000feU);
        WR1_PROG(REG_1600H, 0x1000b480U);
        WR1_PROG(REG_1600H, 0x00000005U);

        WR1_PROG(REG_1600H, 0x3420a880U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xf3990c67U, 0x73c0ea10U, 0xaf69dd7cU, 0xffbecf29U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x596a5850U, 0x1ce9f500U, 0x3ff61d2aU, 0x0950a09dU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x0000349fU);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x80010380U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0000006eU));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xb788fda1U, 0xa949ed0dU, 0x38e8d1fdU, 0x60b6175bU);
            HW_SCE_p_func093_r1(InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0x0d2f063dU, 0x46218b25U, 0x5d0a343dU, 0xb387cb82U);
            WR1_PROG(REG_1608H, 0x81010000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);

            HW_SCE_p_func102(0x81a1e749U, 0x1f4f87e5U, 0x33f337a0U, 0x7fd9a798U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
