/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_FwIntegrityCheck (void)
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00002601U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_84H, 0x00010002U);
    WR1_PROG(REG_13CH, 0x00000F01U);

    WR1_PROG(REG_84H, 0x00010003U);
    WR1_PROG(REG_13CH, 0x00000F01U);

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x000001f0U, 0x0000b7e0U, 0x00000000U);

    WR1_PROG(REG_ECH, 0x00003ffeU);

    WR1_PROG(REG_84H, 0x00010001U);

    WR1_PROG(REG_13CH, 0x00000202U);

    static const uint32_t Param_p26_func102_001[] =
    {
        0x5e152cc3U, 0x70c33839U, 0x6c11afcdU, 0x3a544458U,
    };
    HW_SCE_p_func102(Param_p26_func102_001);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
