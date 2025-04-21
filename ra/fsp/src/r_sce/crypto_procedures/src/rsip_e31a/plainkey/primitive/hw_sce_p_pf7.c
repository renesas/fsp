/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSub (const uint32_t InData_CurveType[],
                                                    const uint32_t InData_Key[],
                                                    const uint32_t InData_MsgDgst[],
                                                    const uint32_t InData_Signature[],
                                                    const uint32_t InData_DomainParam[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f70001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_14H, 0x000017c5U);
    WR1_PROG(REG_B0H, 0x00009493U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Signature[0]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Signature[4]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Signature[8]);

    WR1_PROG(REG_B0H, 0x0000949aU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Signature[12]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Signature[16]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Signature[20]);

    WR1_PROG(REG_14H, 0x00000bc5U);
    WR1_PROG(REG_B0H, 0x000094a1U);
    WAIT_STS(REG_14H, 31, 1);
    WR12_ADDR(REG_2CH, &InData_MsgDgst[0]);

    WR1_PROG(REG_14H, 0x000017c5U);
    WR1_PROG(REG_B0H, 0x0000b4adU);
    WAIT_STS(REG_14H, 31, 1);
    WR24_ADDR(REG_2CH, &InData_Key[0]);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f7U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0xc6f6eb8cU, 0x6b063eabU, 0x1d8d1b24U, 0x3ec6325aU);
    HW_SCE_p_func029(InData_DomainParam);

    HW_SCE_p_func100(0x20e91d5aU, 0x191c3af5U, 0x5352af5fU, 0xc4977339U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xa1ab56e2U, 0xcc048c6eU, 0xefd52d1bU, 0x45538b56U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func102(0x2b2deef7U, 0x67288ba1U, 0x241d2cbbU, 0x3c8a4a68U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
