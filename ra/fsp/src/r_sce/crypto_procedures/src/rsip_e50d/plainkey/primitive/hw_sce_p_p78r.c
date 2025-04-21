/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha3GenerateMessageDigestResumeSub (const uint32_t InData_HashType[], const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00780001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func100(0x7c625bb6U, 0xb7ffb0daU, 0x058ec7b7U, 0x47a6433bU);
    WR1_PROG(REG_2400H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2404H, 0x00001000U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000024U);

        HW_SCE_p_func101(0x938da92eU, 0x7085fd70U, 0x4535a46eU, 0x0801848aU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2404H, 0x00001010U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000022U);

        HW_SCE_p_func101(0xb2147191U, 0xf69ff033U, 0xc9abd3ddU, 0xc6de4955U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2404H, 0x00001020U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x0000001aU);

        HW_SCE_p_func101(0xa32695ccU, 0x75b3bcc6U, 0x244555c2U, 0x308acc5fU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2404H, 0x00001030U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000012U);

        HW_SCE_p_func101(0x3c40ec80U, 0xf2771473U, 0x99512ed8U, 0xfafe8d05U);
    }

    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_PROG(REG_2414H, InData_State[50]);
    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_PROG(REG_2410H, InData_State[51]);

    for (iLoop = 0U; iLoop < 50; iLoop++)
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2438H, InData_State[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func100(0x73948803U, 0x539a1754U, 0x88a50798U, 0xfa4e3a28U);
    WR1_PROG(REG_1608H, 0x81010020U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = change_endian_long(S_RAM[0]);

    HW_SCE_p_func101(0x5f40cebaU, 0x046ad471U, 0x2b4b43b3U, 0x0004e04aU);

    return FSP_SUCCESS;
}
