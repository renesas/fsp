/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha3GenerateMessageDigestInitSub (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
{
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
        WR1_PROG(REG_2404H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000024U);

        HW_SCE_p_func101(0x324e9754U, 0x7d14beadU, 0x6b5a6786U, 0x4c71b5c2U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2404H, 0x00000010U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000022U);

        HW_SCE_p_func101(0xd70b3732U, 0xf9f65611U, 0x3a3ddc3fU, 0x42269b61U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2404H, 0x00000020U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x0000001aU);

        HW_SCE_p_func101(0x2703bdf5U, 0xd55e97f4U, 0x0a604eedU, 0x8fba773bU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2404H, 0x00000030U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000012U);

        HW_SCE_p_func101(0x51793d0fU, 0x5dbf7ac9U, 0xe468cd8dU, 0x47800d85U);
    }

    HW_SCE_p_func100(0xe86c8321U, 0x7b8a512dU, 0xab74ead3U, 0xfc453cb1U);
    WR1_PROG(REG_1608H, 0x81010020U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = change_endian_long(S_RAM[0]);

    if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
    {
        WR1_PROG(REG_240CH, 0x00000100U);

        HW_SCE_p_func101(0xf19879e3U, 0xb2b75bbaU, 0xfcc90cc5U, 0xc0c1d72dU);
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2414H, InData_MsgLen[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2410H, InData_MsgLen[1]);

        HW_SCE_p_func101(0x9c19ee65U, 0x09f4bfefU, 0xbad5ba83U, 0x4101b476U);
    }

    return FSP_SUCCESS;
}
