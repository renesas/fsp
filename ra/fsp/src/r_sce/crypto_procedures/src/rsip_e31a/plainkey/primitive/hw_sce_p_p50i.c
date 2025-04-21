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

    WR1_PROG(REG_94H, 0x0000b4a0U);
    WR1_PROG(REG_94H, 0x00000007U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000050U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x3ba2ff21U, 0x54397079U, 0x96350c9dU, 0x90dfda9eU);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    HW_SCE_p_func100(0x9936b2eeU, 0x0d15dcf9U, 0x7137a6fbU, 0x66714e0fU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x1a7606e2U, 0xdfa335a9U, 0xe074fd30U, 0x6f421e44U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x0dc9fa0fU, 0x9fbd85afU, 0x05745530U, 0x9b103bb8U);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        WR1_PROG(REG_00H, 0x00430011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0xc188fcdfU, 0x18664e46U, 0x25e5e232U, 0x769890d3U);
        WR1_PROG(REG_D0H, 0x08000095U);
        WR1_PROG(REG_00H, 0x00430011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0xd7ce5e52U, 0x331a64a3U, 0x459bc0c0U, 0x3a01724cU);
        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
        {
            HW_SCE_p_func101(0x4df563c7U, 0x1ee05fd9U, 0xb63d0835U, 0xa0c0fed8U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
        {
            HW_SCE_p_func101(0x655331ecU, 0xfa159498U, 0x2a55d5afU, 0x6c153038U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0xe975b0a3U, 0x4d436519U, 0x1ac3863aU, 0x90e9326dU);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0xd6b4bd62U, 0x754db3afU, 0x7c033546U, 0x29217d9dU);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0x2d6e184bU, 0x837d88a0U, 0xa60ae24cU, 0x5186b3e6U);
        }
        else
        {
        }

        return FSP_SUCCESS;
    }
}
