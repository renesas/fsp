/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha256HmacInitSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00760001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x0000001bU);

    static const uint32_t Param_p76i_sub100_001[] =
    {
        0x099dca25U, 0xe140d44eU, 0x3ed2ff36U, 0xd848fee2U, 0x00000076U, 0x0a7a4563U, 0x384da644U, 0xcd1aa0bcU,
        0x55253bc7U, 0x00000076U, 0xb8bbad3cU, 0x143b1420U, 0x87a22148U, 0x9c02e8c6U, 0x00001404U, 0xb1ea2662U,
        0xc37b3e82U, 0x155afd52U, 0xfebcc14dU, 0x00001404U, 0x347c3814U, 0x10af3636U, 0xeb32c943U, 0xcb289377U,
    };
    HW_SCE_p_func_sub100(InData_KeyIndex, InData_Key, Param_p76i_sub100_001);

    static const uint32_t Param_p76i_func100_001[] =
    {
        0x77abb227U, 0xf53dbb40U, 0x580188aaU, 0x83dfc175U,
    };
    HW_SCE_p_func100(Param_p76i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p76i_func102_001[] =
        {
            0x3a638235U, 0x588a0d27U, 0xaffa9656U, 0x7b8e270eU,
        };
        HW_SCE_p_func102(Param_p76i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func004();

        WR1_PROG(REG_F4H, 0x00000011U);

        HW_SCE_p_func001();

        static const uint32_t Param_p76i_func101_001[] =
        {
            0xb0fecd2aU, 0x4cf10ef9U, 0x28bc0eb9U, 0x35ac5307U,
        };
        HW_SCE_p_func101(Param_p76i_func101_001);

        return FSP_SUCCESS;
    }
}
