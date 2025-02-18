/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00470001U);
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

    HW_SCE_p_func100(0x5bb01efeU, 0xff57d48eU, 0x92ae6b88U, 0x4feeb7efU);
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
        WR1_PROG(REG_2CH, change_endian_long(0x00000047U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xf8a8800fU, 0xf20c41c6U, 0xc3dbd55eU, 0x3bf67e8eU);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x00000005U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000047U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x906b9351U, 0x95a3f705U, 0xf7893af5U, 0x35fb3834U);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xf7009d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);

        WR1_PROG(REG_B0H, 0x00000401U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_B0H, 0x00000402U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(0x262e52a0U, 0x08c7e57eU, 0xf5739e53U, 0x0b4b14f6U);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000003c5U);
        WR1_PROG(REG_B0H, 0x00000401U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &InData_Key[0]);
        WR1_PROG(REG_B0H, 0x00000402U);
        WAIT_STS(REG_14H, 31, 1);
        WR2_ADDR(REG_2CH, &InData_Key[2]);

        HW_SCE_p_func101(0x5e977c8eU, 0x225836d1U, 0x3259e6fdU, 0x2ba5b5e9U);
    }

    HW_SCE_p_func100(0x323153b0U, 0x5a8ea4bfU, 0x6efe2f15U, 0x7e221345U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x409f4db3U, 0xa52e87a4U, 0xa1b9d6b0U, 0xe00307ecU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x70346a8bU, 0xe4db9705U, 0x4ac62cc0U, 0x4799913fU);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00000802U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0xd844b852U, 0x1228b1b3U, 0x6c245004U, 0x02a8f215U);
        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
        {
            HW_SCE_p_func101(0x3be31c9aU, 0x8724f055U, 0xf502c3a0U, 0xad4927e8U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
        {
            HW_SCE_p_func101(0xea99bfdcU, 0x1834c4baU, 0x7b25585aU, 0x6dfeebb1U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0x5ad8e600U, 0xd66c96deU, 0x1da80fc7U, 0x1392f195U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0xb7ee85c3U, 0xea6b9239U, 0x7835bac5U, 0x6d438e59U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0xe1d5735dU, 0xfa86aa73U, 0xe9e7bf31U, 0x92537a04U);
        }
        else
        {
        }

        return FSP_SUCCESS;
    }
}
