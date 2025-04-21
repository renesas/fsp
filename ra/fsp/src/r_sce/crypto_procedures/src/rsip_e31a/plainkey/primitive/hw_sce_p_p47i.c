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

    WR1_PROG(REG_94H, 0x0000b4a0U);
    WR1_PROG(REG_94H, 0x00000005U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000047U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x4b313b0dU, 0x159b55b8U, 0x01e0bf66U, 0x394eef7dU);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    HW_SCE_p_func100(0xea79eed9U, 0x4796422eU, 0x9fd14819U, 0xd791129cU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x01a5e6fdU, 0x71e62933U, 0x28dcc7c8U, 0x0c2fac30U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x96ad1b21U, 0xc74344cdU, 0x31569060U, 0x4a37cc8fU);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00000802U);
        WR1_PROG(REG_00H, 0x00430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x5381c985U, 0xb2dd3c6bU, 0xf7bdd50dU, 0xabdaadb9U);
        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
        {
            HW_SCE_p_func101(0x018e958eU, 0xacbbf3d7U, 0x65621a5aU, 0x0aaa204bU);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
        {
            HW_SCE_p_func101(0xe0fc78afU, 0x36804f25U, 0xb3d9d228U, 0xd09072cdU);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0x3fe24e01U, 0x5e856f91U, 0x5348a61dU, 0xada05436U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0x97af414cU, 0x28e1a6dcU, 0xa499b866U, 0xc832a833U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_14H, 0x000003c1U);
            WR1_PROG(REG_D0H, 0x08000045U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            HW_SCE_p_func101(0xa33074dcU, 0x85031e04U, 0x8bbd1abdU, 0x93c7539bU);
        }
        else
        {
        }

        return FSP_SUCCESS;
    }
}
