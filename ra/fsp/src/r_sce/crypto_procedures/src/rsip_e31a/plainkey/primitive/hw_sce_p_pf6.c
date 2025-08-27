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

    WR1_PROG(REG_70H, 0x00f60001U);
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
    WR1_PROG(REG_2CH, change_endian_long(0x000000f6U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x25896fd6U, 0x1016384bU, 0x1dda205fU, 0x3b148a41U);
    HW_SCE_p_func029(InData_DomainParam);

    HW_SCE_p_func100(0x38efb84dU, 0x328a7c8cU, 0xb7f3786bU, 0x7a580874U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x79c0155eU, 0xd73ce60cU, 0x2cc30001U, 0x0693c979U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func102(0xfd999542U, 0x18108e0eU, 0x80eb010eU, 0xc84c8c62U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
