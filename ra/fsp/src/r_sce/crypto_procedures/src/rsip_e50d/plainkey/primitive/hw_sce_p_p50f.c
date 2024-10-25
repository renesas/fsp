/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0xe4ec614aU, 0xaac97f18U, 0x2ac4c921U, 0xb5b87360U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0x9c0e15eeU, 0x891035a1U, 0xd6d1ed99U, 0x3602acc9U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0x66392e50U, 0x3c40fec7U, 0x2f314b29U, 0x4c59ac7eU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0xa91c3852U, 0x89b8df26U, 0x322b45eaU, 0xeaa6514dU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0xfb4050a0U, 0xa2bd35ceU, 0x1090dc04U, 0x6d100b16U);
    }
    else
    {
        ;
    }

    HW_SCE_p_func102(0x2689350fU, 0x6eafcef9U, 0x7c4ebbd6U, 0xe6183d3aU);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}

