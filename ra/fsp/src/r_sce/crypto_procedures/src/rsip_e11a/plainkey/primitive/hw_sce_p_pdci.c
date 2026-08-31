/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha224HmacInitSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00dc0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x0000001aU);

    static const uint32_t Param_pdci_sub100_001[] =
    {
        0xa1480ce9U, 0x29d77c3dU, 0xb0ab3089U, 0x6f791640U, 0x000000dcU, 0x1b9f6e2aU, 0xf365c822U, 0xcd298e66U,
        0x98b77f8bU, 0x000000dcU, 0xb2e6738cU, 0x96cf9863U, 0xb880e9baU, 0x04ed5dc6U, 0x00001404U, 0xd665616aU,
        0xa60210a1U, 0xa862c24dU, 0x29df8d0cU, 0x00001404U, 0x289f0b5cU, 0xfe60b7deU, 0x5e154c77U, 0xf35e6ddaU,
    };
    HW_SCE_p_func_sub100(InData_KeyIndex, InData_Key, Param_pdci_sub100_001);

    static const uint32_t Param_pdci_func100_001[] =
    {
        0x5fddb2a3U, 0x73ad4219U, 0x656befb9U, 0x0bfd6fedU,
    };
    HW_SCE_p_func100(Param_pdci_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pdci_func102_001[] =
        {
            0xa2ad601fU, 0xdb8ef99aU, 0x25cb3060U, 0x585ce026U,
        };
        HW_SCE_p_func102(Param_pdci_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func003();

        WR1_PROG(REG_F4H, 0x00000011U);

        HW_SCE_p_func001();

        static const uint32_t Param_pdci_func101_001[] =
        {
            0x53fa0b86U, 0x8f688219U, 0x7b76f7a2U, 0x09e60a83U,
        };
        HW_SCE_p_func101(Param_pdci_func101_001);

        return FSP_SUCCESS;
    }
}
