/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestResumeSub (const uint32_t InData_HashType[], const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

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
            WR1_PROG(REG_F4H, 0x00001040U);

            HW_SCE_p_func101(0xc8d62d85U, 0xc5bc79f6U, 0x1a00c7b0U, 0x4e57e282U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_F4H, 0x00001050U);

            HW_SCE_p_func101(0x9cb6326bU, 0xe553a8fcU, 0xd76598f0U, 0xdd936f65U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_F4H, 0x00001080U);

            HW_SCE_p_func101(0xda38eb7dU, 0x9c6112abU, 0x634d14f3U, 0xc8e78e94U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_F4H, 0x00001090U);

            HW_SCE_p_func101(0xb3c73a6bU, 0x32f73f8bU, 0x288f9758U, 0xa8099318U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_F4H, 0x000010a0U);

            HW_SCE_p_func101(0x44bb3f73U, 0x8f282ec2U, 0x5f42b74aU, 0xa0572f05U);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_F4H, 0x000010b0U);

            HW_SCE_p_func101(0x8dceb0a3U, 0x9d407adeU, 0x044295e0U, 0xe559da3cU);
        }

        WR1_PROG(REG_14H, 0x00000040U);
        WR1_PROG(REG_104H, InData_State[18]);
        WR1_PROG(REG_14H, 0x00000040U);
        WR1_PROG(REG_100H, InData_State[19]);

        for (iLoop = 0U; iLoop < 18U; iLoop++)
        {
            WR1_PROG(REG_14H, 0x00000040U);
            WR1_PROG(REG_110H, InData_State[iLoop]);
        }

        HW_SCE_p_func101(0x3344ac12U, 0xe5b5b6a8U, 0x4a359a8eU, 0x90894ba4U);

        return FSP_SUCCESS;
    }
}
