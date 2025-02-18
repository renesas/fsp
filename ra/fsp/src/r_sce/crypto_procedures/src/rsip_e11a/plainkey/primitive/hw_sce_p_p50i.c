/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00500001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010080U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x3000a880U);
    WR1_PROG(REG_94H, 0x00000004U);
    WR1_PROG(REG_94H, 0x00010020U);
    WR1_PROG(REG_94H, 0x0000b480U);
    WR1_PROG(REG_94H, 0x00000004U);
    WR1_PROG(REG_94H, 0x00000080U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0xd2fcfefaU, 0x403853eaU, 0x9b79e301U, 0x19f794acU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);
    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000050U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xf9132459U, 0x0ef7b7abU, 0x03518109U, 0x8a5c98f7U);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x00000007U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000050U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x0806dce3U, 0x9c0f4efeU, 0x3f1c04a5U, 0xd908a8efU);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000007c1U);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d07U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_B0H, 0x00001404U);
        WR1_PROG(REG_00H, 0x00c10021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[9]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        HW_SCE_p_func101(0xbcebbe64U, 0x1f8a76b0U, 0x96ee50faU, 0xbe7298c7U);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x00001404U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Key[0]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Key[4]);

        HW_SCE_p_func101(0x164479c8U, 0x27eaa4ccU, 0x3559bea4U, 0xa5ba099dU);
    }

    HW_SCE_p_func100(0x25ec5f4cU, 0x2117b1b3U, 0xf8c67c31U, 0x949a1cb2U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xbb5bd2f9U, 0x90c164efU, 0xfc703f4dU, 0x096e6efdU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x58e0046cU, 0x71d34cf6U, 0x846dd938U, 0x61c59eadU);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00001804U);
        WR1_PROG(REG_00H, 0x00430011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x3b8d46feU, 0x6fbdd644U, 0x0f66a504U, 0xdbf9b0d2U);
        WR1_PROG(REG_D0H, 0x08000095U);
        WR1_PROG(REG_00H, 0x00430011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0xb09cf081U, 0x2c51db0aU, 0x10b93c6dU, 0xe149f9e4U);
        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
        {
            HW_SCE_p_func101(0x0b47efa9U, 0x27152b5dU, 0xc876dd75U, 0x523e0d80U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
        {
            HW_SCE_p_func101(0xe62072d5U, 0x36995d48U, 0x3d74fa76U, 0xe4404164U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0x3a9f257fU, 0x5919ba60U, 0x9676b2b6U, 0xa65084a4U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0x955f3141U, 0xbad8b4f0U, 0xb0edd69cU, 0x3afd94f8U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0xec765abdU, 0xc48110e5U, 0xc7ed046aU, 0x0d3915bdU);
        }
        else
        {
        }

        return FSP_SUCCESS;
    }
}
