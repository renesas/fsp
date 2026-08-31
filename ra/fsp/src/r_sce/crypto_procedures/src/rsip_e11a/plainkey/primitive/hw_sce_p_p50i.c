/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00500001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010080U);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000050U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p50i_func101_001[] =
    {
        0xb0593af2U, 0xa945a5cfU, 0x49defbefU, 0x257dd09aU,
    };
    HW_SCE_p_func101(Param_p50i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p50i_func100_001[] =
    {
        0xa279d4c0U, 0xaf70e48aU, 0x5dbf9b41U, 0xc4f70320U,
    };
    HW_SCE_p_func100(Param_p50i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p50i_func102_001[] =
        {
            0x90fb00f0U, 0x620f39f0U, 0xb36d3551U, 0x2f9c4f26U,
        };
        HW_SCE_p_func102(Param_p50i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p50i_func100_002[] =
        {
            0xc6ab7c09U, 0x2a9b4262U, 0xd1ed4033U, 0xa5c9e3a3U,
        };
        HW_SCE_p_func100(Param_p50i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub002(0x00430011U);

        static const uint32_t Param_p50i_func100_003[] =
        {
            0xe673ad45U, 0xbfc8cc6bU, 0xbf4fbe49U, 0xca70de61U,
        };
        HW_SCE_p_func100(Param_p50i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub002(0x00430011U);

        HW_SCE_p_func_sub006(0x3c00a880U, 0x00000002U, 0x00260000U);

        static const uint32_t Param_p50i_func100_004[] =
        {
            0xc503f6dbU, 0xf604409aU, 0x448bca42U, 0x3489fe4eU,
        };
        HW_SCE_p_func100(Param_p50i_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub008(0x000003c1U, 0x08000045U);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            static const uint32_t Param_p50i_func101_002[] =
            {
                0x9aeab1d7U, 0x49f32be6U, 0x36dddca4U, 0xc78b3f5bU,
            };
            HW_SCE_p_func101(Param_p50i_func101_002);
        }

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0a000100U);

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0a000108U);

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0e000500U);

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x09000908U);

        HW_SCE_p_func_sub001(0x0c00a880U, 0xfffffffcU, 0x2000b4e0U);
        WR1_PROG(REG_94H, 0x07000d00U);

        static const uint32_t Param_p50i_func101_003[] =
        {
            0x6c47d9f9U, 0x4dc7409dU, 0xf449bbdcU, 0x19e56879U,
        };
        HW_SCE_p_func101(Param_p50i_func101_003);

        return FSP_SUCCESS;
    }
}
