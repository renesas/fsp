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

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x006e0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func048(InData_KeyType);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0x521cbe1eU, 0x4b51b0bfU, 0x1b225562U, 0x1e1cd854U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func049(InData_Cmd);

        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010020U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(InData_SharedKeyIndex[0]));
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x00000842U);

        WR1_PROG(REG_94H, 0x3020a880U);
        WR1_PROG(REG_94H, 0x00000020U);
        WR1_PROG(REG_94H, 0x00070020U);
        WR1_PROG(REG_94H, 0x0000b440U);
        WR1_PROG(REG_94H, 0xAA8003A0U);
        WR1_PROG(REG_94H, 0x00000080U);
        WR1_PROG(REG_94H, 0x3020a880U);
        WR1_PROG(REG_94H, 0x00000040U);
        WR1_PROG(REG_94H, 0x00070020U);
        WR1_PROG(REG_94H, 0x3020a880U);
        WR1_PROG(REG_94H, 0x00000020U);
        WR1_PROG(REG_94H, 0x00060020U);
        WR1_PROG(REG_94H, 0x0000b440U);
        WR1_PROG(REG_94H, 0x00000F88U);
        WR1_PROG(REG_94H, 0x00000080U);
        WR1_PROG(REG_94H, 0x00000080U);

        WR1_PROG(REG_94H, 0x000034a4U);

        WR1_PROG(REG_94H, 0x00008c80U);
        WR1_PROG(REG_94H, 0x0000001fU);

        HW_SCE_p_func056();

        WR1_PROG(REG_94H, 0x3420a820U);
        WR1_PROG(REG_94H, 0x00000010U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A70000U);

        HW_SCE_p_func100(0xa35eb2a9U, 0x3034a84cU, 0xc75ace06U, 0x2fa4ea32U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0xaee89dc4U, 0x9d278b8eU, 0xf1b852edU, 0x042323f3U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_94H, 0x00003485U);

            WR1_PROG(REG_14H, 0x000001a1U);
            WR1_PROG(REG_D0H, 0x07330c04U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_D0H, 0x07330d04U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_9CH, 0x80010000U);
            WR1_PROG(REG_00H, 0x03410005U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_00H, 0x0001000dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_14H, 0x000001a1U);
            WR1_PROG(REG_D0H, 0x07330d04U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_D0H, 0x06330104U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_B0H, 0x00001404U);
            WR1_PROG(REG_00H, 0x00c10021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            OFS_ADR = InData_SharedKeyIndex[0] << 3;

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x0000006eU));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x85c88c03U, 0x08478fbdU, 0xbad9f453U, 0x0dd56ca4U);
            HW_SCE_p_func058(InData_SessionKey, OFS_ADR);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x0000006eU));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x005a7415U, 0x693b6206U, 0xe7ada7bdU, 0x8a53b325U);
            HW_SCE_p_func057(InData_IV, InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0x9a143894U, 0x60151963U, 0xc67600a2U, 0x8dfb2ea5U);
            WR1_PROG(REG_B0H, 0x00001804U);

            WR1_PROG(REG_D0H, 0x080000b5U);
            WR1_PROG(REG_00H, 0x00430011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_D0H, 0x08000075U);
            WR1_PROG(REG_00H, 0x00430011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            HW_SCE_p_func100(0x60f57f73U, 0xe4c4d05fU, 0x7c853177U, 0x4f60d1a7U);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x3e0635ffU, 0xe12e67a4U, 0x6d87290cU, 0xca7def55U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0x7a4a8799U, 0x4667aa10U, 0x440e7b0cU, 0x4c64dcf9U);
                WR1_PROG(REG_9CH, 0x81010000U);
                WR1_PROG(REG_08H, 0x00005006U);
                WAIT_STS(REG_08H, 30, 1);
                RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

                HW_SCE_p_func102(0x09c7e53aU, 0x93925457U, 0xe8361c39U, 0xf9c56138U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
    else
    {
        HW_SCE_p_func049(InData_Cmd);

        WR1_PROG(REG_94H, 0x00000842U);

        WR1_PROG(REG_94H, 0x3020a880U);
        WR1_PROG(REG_94H, 0x00000020U);
        WR1_PROG(REG_94H, 0x00070020U);
        WR1_PROG(REG_94H, 0x0000b440U);
        WR1_PROG(REG_94H, 0xAA8003A0U);
        WR1_PROG(REG_94H, 0x00000080U);
        WR1_PROG(REG_94H, 0x3020a880U);
        WR1_PROG(REG_94H, 0x00000040U);
        WR1_PROG(REG_94H, 0x00070020U);
        WR1_PROG(REG_94H, 0x3020a880U);
        WR1_PROG(REG_94H, 0x00000020U);
        WR1_PROG(REG_94H, 0x00060020U);
        WR1_PROG(REG_94H, 0x0000b440U);
        WR1_PROG(REG_94H, 0x00000F88U);
        WR1_PROG(REG_94H, 0x00000080U);
        WR1_PROG(REG_94H, 0x00000080U);

        WR1_PROG(REG_94H, 0x000034a4U);

        WR1_PROG(REG_94H, 0x00008c80U);
        WR1_PROG(REG_94H, 0x0000001fU);

        HW_SCE_p_func056();

        HW_SCE_p_func100(0x27fb9c44U, 0xdcfa7a0bU, 0x08e18aedU, 0x990b92c4U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0xbb29be65U, 0x8c3513f9U, 0xc06b58f0U, 0x9fce056bU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_94H, 0x00003485U);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x0000006eU));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0xc7bcb6daU, 0x09fea00eU, 0x45250f82U, 0x25e95514U);
            HW_SCE_p_func093(InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0xef970e1aU, 0x37ca3491U, 0x45df93c0U, 0x24b4d44eU);
            WR1_PROG(REG_9CH, 0x81010000U);
            WR1_PROG(REG_08H, 0x00005006U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

            HW_SCE_p_func102(0x9735052cU, 0xd4093a17U, 0xbfeb3e8dU, 0xd7ad95b1U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
