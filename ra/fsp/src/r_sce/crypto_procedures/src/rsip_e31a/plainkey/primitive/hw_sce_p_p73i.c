/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestInitSub (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00730001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_F0H, 0x00000001U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_HashType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0xe133b056U, 0x6335d392U, 0x4363bd93U, 0x4c485ca1U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x7ac04887U, 0xf19e7e3eU, 0x140523b2U, 0xe9f6ecf0U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0xf4f88269U, 0xb6c389c9U, 0xc62e5d0fU, 0x6f153fc9U);
        WR1_PROG(REG_94H, 0x3420a800U);
        WR1_PROG(REG_94H, 0x00000007U);
        WR1_PROG(REG_94H, 0x2000b400U);
        WR1_PROG(REG_94H, 0x00000006U);

        WR1_PROG(REG_94H, 0x00007c00U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_F4H, 0x00000040U);

            HW_SCE_p_func101(0x15bc12eeU, 0x44a46d57U, 0xde831d31U, 0x3e373109U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_F4H, 0x00000050U);

            HW_SCE_p_func101(0x57c1abd5U, 0xea82a126U, 0x5328616bU, 0x31956f63U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_F4H, 0x00000080U);

            HW_SCE_p_func101(0x589f94e6U, 0x13fe88d6U, 0x4ffa87faU, 0x5615384fU);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_F4H, 0x00000090U);

            HW_SCE_p_func101(0x7ae33a78U, 0x5d4757b7U, 0x2dbea097U, 0x5ca33d82U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_F4H, 0x000000a0U);

            HW_SCE_p_func101(0x08ab9ebfU, 0xfe66f025U, 0x3185a796U, 0xb9468b30U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_F4H, 0x000000b0U);

            HW_SCE_p_func101(0xf670f6daU, 0xc6cc4465U, 0x66bf7f32U, 0x9b0888d1U);
        }

        if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
        {
            WR1_PROG(REG_FCH, 0x00000100U);

            HW_SCE_p_func101(0xd02e8106U, 0x2d29efffU, 0xe7d83645U, 0xabd7d94aU);
        }
        else
        {
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_104H, InData_MsgLen[0]);
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_100H, InData_MsgLen[1]);

            HW_SCE_p_func101(0x4f23cd4bU, 0xf4422740U, 0x4497bfc5U, 0x91eefb70U);
        }

        return FSP_SUCCESS;
    }
}
