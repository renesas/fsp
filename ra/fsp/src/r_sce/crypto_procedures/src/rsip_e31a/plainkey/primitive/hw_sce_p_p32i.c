/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128GcmDecryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00320001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub020(0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000032U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p32i_func101_001[] =
    {
        0x43e6815cU, 0xbfcdf9feU, 0x2c989bfdU, 0xea3c63daU,
    };
    HW_SCE_p_func101(Param_p32i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p32i_func100_001[] =
    {
        0x93db6b21U, 0xeb7ed869U, 0xca90ca6cU, 0x452f9a4fU,
    };
    HW_SCE_p_func100(Param_p32i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p32i_func102_001[] =
        {
            0x418a3054U, 0x008da933U, 0xf53f942cU, 0x2d937cbeU,
        };
        HW_SCE_p_func102(Param_p32i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p32i_func100_002[] =
        {
            0x8859164fU, 0x32e5c1beU, 0x22e6f7bdU, 0xfaf9a148U,
        };
        HW_SCE_p_func100(Param_p32i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub003(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub003(0x00430009U);

        static const uint32_t Param_p32i_func100_003[] =
        {
            0x3e140dd4U, 0x0df65b7dU, 0x1c15dfa0U, 0xf2a07ca1U,
        };
        HW_SCE_p_func100(Param_p32i_func100_003);
        WR1_PROG(REG_14H, 0x000003c7U);
        WR1_PROG(REG_94H, 0x0000b420U);
        WR1_PROG(REG_94H, 0x00000010U);
        WR1_PROG(REG_9CH, 0x80840001U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[0]);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[2]);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_IV[3]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x08000054U, 0x00000000U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x0a0000a4U, 0x00000000U);

        static const uint32_t Param_p32i_func101_002[] =
        {
            0x4aa45debU, 0xd9fc207cU, 0x3854ae51U, 0x777f8e93U,
        };
        HW_SCE_p_func101(Param_p32i_func101_002);

        return FSP_SUCCESS;
    }
}
