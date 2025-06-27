/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestInitSub (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00730001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func100(0x7f797d3fU, 0x084303d5U, 0xd4bb5ca2U, 0x798174fdU);
    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00000000U);

        HW_SCE_p_func101(0xfdee56e9U, 0x5e83ceb4U, 0xa51d4803U, 0xa5fc0889U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x00000040U);

        HW_SCE_p_func101(0x67b8b695U, 0x01f28097U, 0xe46c5c86U, 0xd589d478U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x00000050U);

        HW_SCE_p_func101(0xd22665f4U, 0x6db51b8fU, 0x8b711d31U, 0xfdf72db6U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2004H, 0x00000080U);

        HW_SCE_p_func101(0x32e90f4aU, 0x631b1d22U, 0x544c18acU, 0x6d88f9c5U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_2004H, 0x00000090U);

        HW_SCE_p_func101(0xf7b9bb1eU, 0x683b3fdfU, 0xd4244156U, 0xb906f836U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        WR1_PROG(REG_2004H, 0x000000a0U);

        HW_SCE_p_func101(0x037fa157U, 0xa3bc855bU, 0xf471a9f0U, 0xbd285f46U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        WR1_PROG(REG_2004H, 0x000000b0U);

        HW_SCE_p_func101(0x7a76b67fU, 0xaaed03fdU, 0x5a11fd65U, 0x055e574aU);
    }

    if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
    {
        WR1_PROG(REG_200CH, 0x00000100U);

        HW_SCE_p_func101(0x2bb31e26U, 0x582a1fd1U, 0xc5917bfbU, 0xe69a4370U);
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, InData_MsgLen[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, InData_MsgLen[1]);

        HW_SCE_p_func101(0x49a02ef2U, 0xb5ce77ffU, 0xc1de041fU, 0xf11a9b4bU);
    }

    return FSP_SUCCESS;
}
