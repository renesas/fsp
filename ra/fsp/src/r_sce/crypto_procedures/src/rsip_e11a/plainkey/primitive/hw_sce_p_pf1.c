/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EcdsaSignatureVerificationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_Signature[],
                                                const uint32_t InData_DomainParam[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f10001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x3420a800U, 0x00000003U, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_14H, 0x00000fc5U);
    WR1_PROG(REG_B0H, 0x00001469U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_Signature[0]);

    WR1_PROG(REG_B0H, 0x0000146eU);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_Signature[8]);

    WR1_PROG(REG_14H, 0x000007c5U);
    WR1_PROG(REG_B0H, 0x00001472U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_MsgDgst[0]);

    WR1_PROG(REG_14H, 0x00000fc5U);
    WR1_PROG(REG_B0H, 0x0000347aU);
    WAIT_STS(REG_14H, 31, 1);
    WR16_ADDR(REG_2CH, &InData_Key[0]);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f1U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pf1_func101_001[] =
    {
        0x469f1975U, 0x2f2c9075U, 0x02f4c461U, 0x88338e77U,
    };
    HW_SCE_p_func101(Param_pf1_func101_001);
    HW_SCE_p_func073_r2(InData_DomainParam);

    static const uint32_t Param_pf1_func100_001[] =
    {
        0x798eae77U, 0x01c0213aU, 0x684cddfeU, 0x94e137a7U,
    };
    HW_SCE_p_func100(Param_pf1_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pf1_func102_001[] =
        {
            0xb9f72f43U, 0x7d4ba27dU, 0x546844c9U, 0x4e0c5679U,
        };
        HW_SCE_p_func102(Param_pf1_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_pf1_func102_002[] =
        {
            0xbaff028bU, 0xd49c0273U, 0x3aa94094U, 0xe091e383U,
        };
        HW_SCE_p_func102(Param_pf1_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
