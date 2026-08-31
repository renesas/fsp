/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestInitSub (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00730001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_F0H, 0x00000001U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_HashType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

    static const uint32_t Param_p73i_func100_001[] =
    {
        0xe133b056U, 0x6335d392U, 0x4363bd93U, 0x4c485ca1U,
    };
    HW_SCE_p_func100(Param_p73i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p73i_func102_001[] =
        {
            0x7ac04887U, 0xf19e7e3eU, 0x140523b2U, 0xe9f6ecf0U,
        };
        HW_SCE_p_func102(Param_p73i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p73i_func100_002[] =
        {
            0xf4f88269U, 0xb6c389c9U, 0xc62e5d0fU, 0x6f153fc9U,
        };
        HW_SCE_p_func100(Param_p73i_func100_002);
        HW_SCE_p_func_sub001(0x3420a800U, 0x00000007U, 0x2000b400U, 0x00000006U);

        WR1_PROG(REG_94H, 0x00007c00U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_F4H, 0x00000040U);

            static const uint32_t Param_p73i_func101_001[] =
            {
                0x15bc12eeU, 0x44a46d57U, 0xde831d31U, 0x3e373109U,
            };
            HW_SCE_p_func101(Param_p73i_func101_001);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_F4H, 0x00000050U);

            static const uint32_t Param_p73i_func101_002[] =
            {
                0x57c1abd5U, 0xea82a126U, 0x5328616bU, 0x31956f63U,
            };
            HW_SCE_p_func101(Param_p73i_func101_002);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_F4H, 0x00000080U);

            static const uint32_t Param_p73i_func101_003[] =
            {
                0x589f94e6U, 0x13fe88d6U, 0x4ffa87faU, 0x5615384fU,
            };
            HW_SCE_p_func101(Param_p73i_func101_003);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_F4H, 0x00000090U);

            static const uint32_t Param_p73i_func101_004[] =
            {
                0x7ae33a78U, 0x5d4757b7U, 0x2dbea097U, 0x5ca33d82U,
            };
            HW_SCE_p_func101(Param_p73i_func101_004);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_F4H, 0x000000a0U);

            static const uint32_t Param_p73i_func101_005[] =
            {
                0x08ab9ebfU, 0xfe66f025U, 0x3185a796U, 0xb9468b30U,
            };
            HW_SCE_p_func101(Param_p73i_func101_005);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_F4H, 0x000000b0U);

            static const uint32_t Param_p73i_func101_006[] =
            {
                0xf670f6daU, 0xc6cc4465U, 0x66bf7f32U, 0x9b0888d1U,
            };
            HW_SCE_p_func101(Param_p73i_func101_006);
        }

        if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
        {
            WR1_PROG(REG_FCH, 0x00000100U);

            static const uint32_t Param_p73i_func101_007[] =
            {
                0xd02e8106U, 0x2d29efffU, 0xe7d83645U, 0xabd7d94aU,
            };
            HW_SCE_p_func101(Param_p73i_func101_007);
        }
        else
        {
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_104H, InData_MsgLen[0]);
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_100H, InData_MsgLen[1]);

            static const uint32_t Param_p73i_func101_008[] =
            {
                0x4f23cd4bU, 0xf4422740U, 0x4497bfc5U, 0x91eefb70U,
            };
            HW_SCE_p_func101(Param_p73i_func101_008);
        }

        return FSP_SUCCESS;
    }
}
