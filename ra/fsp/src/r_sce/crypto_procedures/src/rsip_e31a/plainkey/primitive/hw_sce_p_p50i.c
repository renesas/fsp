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
    HW_SCE_p_func_sub020(0x00000007U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000050U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p50i_func101_001[] =
    {
        0xcba56606U, 0x5d358e7bU, 0xcd4babf1U, 0x1497c982U,
    };
    HW_SCE_p_func101(Param_p50i_func101_001);
    HW_SCE_p_func441(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p50i_func100_001[] =
    {
        0x9936b2eeU, 0x0d15dcf9U, 0x7137a6fbU, 0x66714e0fU,
    };
    HW_SCE_p_func100(Param_p50i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p50i_func102_001[] =
        {
            0x1a7606e2U, 0xdfa335a9U, 0xe074fd30U, 0x6f421e44U,
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
            0x0dc9fa0fU, 0x9fbd85afU, 0x05745530U, 0x9b103bb8U,
        };
        HW_SCE_p_func100(Param_p50i_func100_002);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x0000181eU);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_p50i_func100_003[] =
        {
            0xc188fcdfU, 0x18664e46U, 0x25e5e232U, 0x769890d3U,
        };
        HW_SCE_p_func100(Param_p50i_func100_003);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);

        HW_SCE_p_func_sub006(0x3c00a880U, 0x00000002U, 0x00270000U);

        static const uint32_t Param_p50i_func100_004[] =
        {
            0xaa2f10d9U, 0x16ad6344U, 0xbbbd17d2U, 0x7938dac9U,
        };
        HW_SCE_p_func100(Param_p50i_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub011(0x000003c1U, 0x08000045U);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            static const uint32_t Param_p50i_func101_002[] =
            {
                0x2e9a0469U, 0x782ab817U, 0xe9a8385fU, 0xe6009d3dU,
            };
            HW_SCE_p_func101(Param_p50i_func101_002);
        }

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0a000100U, 0x0c003080U);
        HW_SCE_p_func_sub001(0x2000b4e0U, 0x0a000108U, 0x0c003080U, 0x2000b4e0U);
        HW_SCE_p_func_sub001(0x0e000500U, 0x0c003080U, 0x2000b4e0U, 0x09000908U);

        HW_SCE_p_func_sub001(0x0c00a880U, 0xfffffffcU, 0x2000b4e0U, 0x07000d00U);

        static const uint32_t Param_p50i_func101_003[] =
        {
            0x95b7984bU, 0xe4fe98cbU, 0x36c3c461U, 0x9cd4e8b7U,
        };
        HW_SCE_p_func101(Param_p50i_func101_003);

        return FSP_SUCCESS;
    }
}
