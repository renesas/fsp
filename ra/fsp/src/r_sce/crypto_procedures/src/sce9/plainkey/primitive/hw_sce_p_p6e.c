/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateOemKeyIndexSub (uint32_t InData_KeyType[],
                                         uint32_t InData_Cmd[],
                                         uint32_t InData_SharedKeyIndex[],
                                         uint32_t InData_SessionKey[],
                                         uint32_t InData_IV[],
                                         uint32_t InData_InstData[],
                                         uint32_t OutData_KeyIndex[])
{
    uint32_t OFS_ADR = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00006e02U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800103e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    WR1_PROG(REG_ECH, 0x38000fffU);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);

    static const uint32_t Param_p6e_func100_001[] =
    {
        0x65d6015fU, 0xcef163cdU, 0xd36f3dbaU, 0x9ff542e9U,
    };
    HW_SCE_p_func100(Param_p6e_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        HW_SCE_p_func049(InData_Cmd);

        WR1_PROG(REG_104H, 0x00000068U);
        WR1_PROG(REG_E0H, 0x80010020U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(InData_SharedKeyIndex[0]));

        HW_SCE_p_func_sub007(0x000037e4U, 0x3420a880U, 0x00000005U, 0x00260000U);

        HW_SCE_p_func_sub014(0x3420a880U, 0x00000024U, 0x00A60000U);

        HW_SCE_p_func_sub014(0x3420a820U, 0x00000010U, 0x00A60000U);

        static const uint32_t Param_p6e_func100_002[] =
        {
            0x98244c8cU, 0x79b8693eU, 0x27d09331U, 0x54bd7297U,
        };
        HW_SCE_p_func100(Param_p6e_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p6e_func102_001[] =
            {
                0x619b2415U, 0x1a64fb8fU, 0x72abf3c5U, 0xb1a9f8d3U,
            };
            HW_SCE_p_func102(Param_p6e_func102_001);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000349fU);

            OFS_ADR = InData_SharedKeyIndex[0] << 3;

            HW_SCE_p_func_sub009(0x800103a0U, 0x0000006eU);

            static const uint32_t Param_p6e_func101_001[] =
            {
                0xa7637c51U, 0x0fdd3f7fU, 0x3ef7d917U, 0x86dcab7aU,
            };
            HW_SCE_p_func101(Param_p6e_func101_001);
            HW_SCE_p_func058(InData_SessionKey, OFS_ADR);

            HW_SCE_p_func_sub009(0x80010380U, 0x0000006eU);

            static const uint32_t Param_p6e_func101_002[] =
            {
                0xe5d19a97U, 0xbbcdd6daU, 0x4233f284U, 0x7d0593baU,
            };
            HW_SCE_p_func101(Param_p6e_func101_002);
            HW_SCE_p_func057_r1(InData_IV, InData_InstData, OutData_KeyIndex);

            static const uint32_t Param_p6e_func100_003[] =
            {
                0x0ab4814bU, 0xb8367889U, 0x271bcf2fU, 0x4feba308U,
            };
            HW_SCE_p_func100(Param_p6e_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p6e_func102_002[] =
                {
                    0x9e5039cbU, 0xd69d6c2aU, 0xa37c0068U, 0x3994c7b9U,
                };
                HW_SCE_p_func102(Param_p6e_func102_002);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p6e_func100_004[] =
                {
                    0x8daed06bU, 0x2a351c5cU, 0x97281b51U, 0x096a7d03U,
                };
                HW_SCE_p_func100(Param_p6e_func100_004);
                WR1_PROG(REG_E0H, 0x81010000U);
                WR1_PROG(REG_04H, 0x00000606U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_KeyIndex[0]);

                static const uint32_t Param_p6e_func102_003[] =
                {
                    0x5d24c640U, 0x65732df6U, 0x707f16f3U, 0x63de5db7U,
                };
                HW_SCE_p_func102(Param_p6e_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
    else
    {
        HW_SCE_p_func049(InData_Cmd);

        HW_SCE_p_func_sub007(0x000037e4U, 0x3420a880U, 0x00000005U, 0x00260000U);

        HW_SCE_p_func_sub014(0x3420a880U, 0x00000024U, 0x00A60000U);

        static const uint32_t Param_p6e_func100_005[] =
        {
            0x7aef0fcbU, 0x9258934aU, 0x8b4dbf1fU, 0xf15611dcU,
        };
        HW_SCE_p_func100(Param_p6e_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p6e_func102_004[] =
            {
                0x638045baU, 0xdc6175a9U, 0x99105401U, 0x7086cb16U,
            };
            HW_SCE_p_func102(Param_p6e_func102_004);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub005(0x0000349fU, 0x00000058U, 0x80010380U, 0x0000006eU);

            static const uint32_t Param_p6e_func101_003[] =
            {
                0x083ef1a1U, 0x630e194cU, 0x4b5f490eU, 0x96a54f99U,
            };
            HW_SCE_p_func101(Param_p6e_func101_003);
            HW_SCE_p_func065_r1(InData_InstData, OutData_KeyIndex);

            static const uint32_t Param_p6e_func100_006[] =
            {
                0x1cf9ac81U, 0x590924eaU, 0xd4425eb1U, 0xd5db5292U,
            };
            HW_SCE_p_func100(Param_p6e_func100_006);
            WR1_PROG(REG_E0H, 0x81010000U);
            WR1_PROG(REG_04H, 0x00000606U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &OutData_KeyIndex[0]);

            static const uint32_t Param_p6e_func102_005[] =
            {
                0x61423c7fU, 0xf3f4807eU, 0x10a36a81U, 0x6c3dbeadU,
            };
            HW_SCE_p_func102(Param_p6e_func102_005);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
