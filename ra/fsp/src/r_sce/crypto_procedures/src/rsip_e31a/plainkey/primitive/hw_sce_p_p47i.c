/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

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

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010080U);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000047U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p47i_func101_001[] =
    {
        0x24d00915U, 0x0eea6928U, 0x8fa38fa9U, 0x532ac595U,
    };
    HW_SCE_p_func101(Param_p47i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p47i_func100_001[] =
    {
        0xea79eed9U, 0x4796422eU, 0x9fd14819U, 0xd791129cU,
    };
    HW_SCE_p_func100(Param_p47i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p47i_func102_001[] =
        {
            0x01a5e6fdU, 0x71e62933U, 0x28dcc7c8U, 0x0c2fac30U,
        };
        HW_SCE_p_func102(Param_p47i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p47i_func100_002[] =
        {
            0x96ad1b21U, 0xc74344cdU, 0x31569060U, 0x4a37cc8fU,
        };
        HW_SCE_p_func100(Param_p47i_func100_002);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub003(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub003(0x00430009U);

        HW_SCE_p_func_sub006(0x3c00a880U, 0x00000002U, 0x00270000U);

        static const uint32_t Param_p47i_func100_003[] =
        {
            0xe8f58d35U, 0xbb179feaU, 0x241739deU, 0xa1623165U,
        };
        HW_SCE_p_func100(Param_p47i_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub011(0x000003c1U, 0x08000045U);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            static const uint32_t Param_p47i_func101_002[] =
            {
                0x958b91dfU, 0x82499d55U, 0x21768837U, 0x5d3570a5U,
            };
            HW_SCE_p_func101(Param_p47i_func101_002);
        }

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0a000100U, 0x0c003080U);
        HW_SCE_p_func_sub001(0x2000b4e0U, 0x0a000108U, 0x0c003080U, 0x2000b4e0U);
        HW_SCE_p_func_sub001(0x0e000500U, 0x0c003080U, 0x2000b4e0U, 0x09000908U);

        HW_SCE_p_func_sub001(0x0c00a880U, 0xfffffffcU, 0x2000b4e0U, 0x07000d00U);

        static const uint32_t Param_p47i_func101_003[] =
        {
            0x8be6e656U, 0x0a253748U, 0x39055a41U, 0x086f5a05U,
        };
        HW_SCE_p_func101(Param_p47i_func101_003);

        return FSP_SUCCESS;
    }
}
