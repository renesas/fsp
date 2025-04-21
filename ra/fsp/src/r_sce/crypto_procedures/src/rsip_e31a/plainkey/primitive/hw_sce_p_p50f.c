/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0x299cf4a9U, 0x1ad9b8eeU, 0x54c76cd4U, 0x68129500U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0xadf89849U, 0x229cd6dbU, 0x50b47babU, 0x1599f647U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0x96e38fd7U, 0x6727350fU, 0xc4ecf4f7U, 0x6ef630e3U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0x47b480aaU, 0xc4a1d156U, 0x54cb0fc3U, 0x115b54adU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0xc9f61e07U, 0xd969c3faU, 0xa8c735bdU, 0xfe52afc4U);
    }

    HW_SCE_p_func102(0x55dec32eU, 0x11bbed03U, 0xc5af0be4U, 0x256d708fU);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
