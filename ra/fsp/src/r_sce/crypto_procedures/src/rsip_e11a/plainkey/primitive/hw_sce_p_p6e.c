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
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0x82d3e31bU, 0xb0db125dU, 0x5c939002U, 0xdafa96d1U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func049(InData_Cmd);

        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010020U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(InData_SharedKeyIndex[0]));
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x0000b440U);
        WR1_PROG(REG_94H, 0x2C8003A0U);

        WR1_PROG(REG_94H, 0x000034a4U);

        WR1_PROG(REG_94H, 0x38008880U);
        WR1_PROG(REG_94H, 0x00000023U);
        WR1_PROG(REG_94H, 0x1000b480U);
        WR1_PROG(REG_94H, 0x00000005U);

        HW_SCE_p_func056();

        WR1_PROG(REG_94H, 0x3420a820U);
        WR1_PROG(REG_94H, 0x00000010U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A60000U);

        HW_SCE_p_func100(0xdbbcc96cU, 0xccc799e7U, 0xb4b56b77U, 0x9262c90bU);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x80fe7b21U, 0x2bee9cebU, 0xace9157dU, 0x68513f9cU);
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

            HW_SCE_p_func101(0xa21db742U, 0x5875ae65U, 0x0ae7dfa3U, 0xcf7cf4b8U);
            HW_SCE_p_func058(InData_SessionKey, OFS_ADR);

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x0000006eU));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0xd9282a6eU, 0x9aacc76eU, 0x79afa223U, 0xa556a55eU);
            HW_SCE_p_func057(InData_IV, InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0xf4246079U, 0xb6319a3aU, 0x510a498dU, 0x93f08a44U);
            WR1_PROG(REG_B0H, 0x00001804U);

            WR1_PROG(REG_D0H, 0x080000b5U);
            WR1_PROG(REG_00H, 0x00430011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_D0H, 0x08000075U);
            WR1_PROG(REG_00H, 0x00430011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            HW_SCE_p_func100(0x920d6209U, 0x6e79e57bU, 0xf703150cU, 0xa172f769U);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x9775d67fU, 0x396d0f81U, 0x7ecbfb5fU, 0xf1fa5ac9U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xcf11713cU, 0xcbb3e7c3U, 0xcb64262eU, 0x9d3106c1U);
                WR1_PROG(REG_9CH, 0x81010000U);
                WR1_PROG(REG_08H, 0x00005006U);
                WAIT_STS(REG_08H, 30, 1);
                RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

                HW_SCE_p_func102(0x465ecbceU, 0x7403c973U, 0x8187197aU, 0x05bcbc44U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
    else
    {
        HW_SCE_p_func049(InData_Cmd);

        WR1_PROG(REG_94H, 0x0000b440U);
        WR1_PROG(REG_94H, 0x2C8003A0U);

        WR1_PROG(REG_94H, 0x000034a4U);

        WR1_PROG(REG_94H, 0x38008880U);
        WR1_PROG(REG_94H, 0x00000023U);
        WR1_PROG(REG_94H, 0x1000b480U);
        WR1_PROG(REG_94H, 0x00000005U);

        HW_SCE_p_func056();

        HW_SCE_p_func100(0xa024ddb8U, 0x88d8cbeeU, 0x36743452U, 0xca97514fU);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0xaa1baea0U, 0xf8bb4916U, 0x8852d953U, 0xc6263102U);
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

            HW_SCE_p_func101(0x50a1d64dU, 0x2196fc79U, 0x8e8c96d3U, 0xfb016606U);
            HW_SCE_p_func093(InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0x9f5926edU, 0xe3766cd5U, 0xbbaca6dfU, 0x0bc5888aU);
            WR1_PROG(REG_9CH, 0x81010000U);
            WR1_PROG(REG_08H, 0x00005006U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

            HW_SCE_p_func102(0x32fb2a21U, 0x5302162eU, 0xffe2a878U, 0xeb5cc9feU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
