/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CmacInitSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00410001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000041U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p41i_func101_001[] =
    {
        0x344beb67U, 0x5be79698U, 0x5344c62aU, 0xa104e25dU,
    };
    HW_SCE_p_func101(Param_p41i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p41i_func100_001[] =
    {
        0xa9349c49U, 0xbb988755U, 0x9a5816c2U, 0xd88e0e6dU,
    };
    HW_SCE_p_func100(Param_p41i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p41i_func102_001[] =
        {
            0x23d0ec5dU, 0x30feb695U, 0xe08c39d7U, 0xb25ec315U,
        };
        HW_SCE_p_func102(Param_p41i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p41i_func100_002[] =
        {
            0x98fe55e9U, 0x69bbefe2U, 0xd9c81cc9U, 0xa9dc656fU,
        };
        HW_SCE_p_func100(Param_p41i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub002(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub002(0x00430009U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x08000044U, 0x00000000U);

        static const uint32_t Param_p41i_func101_002[] =
        {
            0xc1e21e4eU, 0x65e1a5b8U, 0xe01037b8U, 0x356dd872U,
        };
        HW_SCE_p_func101(Param_p41i_func101_002);

        return FSP_SUCCESS;
    }
}
