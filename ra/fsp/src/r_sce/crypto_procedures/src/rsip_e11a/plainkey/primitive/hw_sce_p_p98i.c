/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t Header_Len)
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00990001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000099U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p98i_func101_001[] =
    {
        0x5a5ef540U, 0x8e4adc7cU, 0x78bc5cc0U, 0x78eeae5dU,
    };
    HW_SCE_p_func101(Param_p98i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p98i_func100_001[] =
    {
        0x08faebf7U, 0x67e72dfcU, 0xba9c3e21U, 0xeeb0cbddU,
    };
    HW_SCE_p_func100(Param_p98i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p98i_func102_001[] =
        {
            0xabab3fb5U, 0x9d3327c4U, 0x928621fcU, 0x7db15abeU,
        };
        HW_SCE_p_func102(Param_p98i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p98i_func100_002[] =
        {
            0x0aedda8bU, 0x681782b6U, 0xd9f5dff0U, 0x48662401U,
        };
        HW_SCE_p_func100(Param_p98i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub002(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub002(0x00430009U);

        WR1_PROG(REG_D4H, 0x00000000U);
        HW_SCE_p_func501(InData_IV, InData_Header, Header_Len);

        static const uint32_t Param_p98i_func101_002[] =
        {
            0x51755072U, 0xd505155eU, 0xa521d7d5U, 0x63f508edU,
        };
        HW_SCE_p_func101(Param_p98i_func101_002);

        return FSP_SUCCESS;
    }
}
