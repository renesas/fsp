/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

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

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_HashType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

    static const uint32_t Param_p73r_func100_001[] =
    {
        0xe133b056U, 0x6335d392U, 0x4363bd93U, 0x4c485ca1U,
    };
    HW_SCE_p_func100(Param_p73r_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p73r_func102_001[] =
        {
            0x7ac04887U, 0xf19e7e3eU, 0x140523b2U, 0xe9f6ecf0U,
        };
        HW_SCE_p_func102(Param_p73r_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p73r_func100_002[] =
        {
            0xf4f88269U, 0xb6c389c9U, 0xc62e5d0fU, 0x6f153fc9U,
        };
        HW_SCE_p_func100(Param_p73r_func100_002);
        HW_SCE_p_func_sub001(0x3420a800U, 0x00000007U, 0x2000b400U, 0x00000006U);

        WR1_PROG(REG_94H, 0x00007c00U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
        {
            WR1_PROG(REG_F4H, 0x00001040U);

            static const uint32_t Param_p73r_func101_001[] =
            {
                0xc8d62d85U, 0xc5bc79f6U, 0x1a00c7b0U, 0x4e57e282U,
            };
            HW_SCE_p_func101(Param_p73r_func101_001);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_F4H, 0x00001050U);

            static const uint32_t Param_p73r_func101_002[] =
            {
                0x9cb6326bU, 0xe553a8fcU, 0xd76598f0U, 0xdd936f65U,
            };
            HW_SCE_p_func101(Param_p73r_func101_002);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_F4H, 0x00001080U);

            static const uint32_t Param_p73r_func101_003[] =
            {
                0xda38eb7dU, 0x9c6112abU, 0x634d14f3U, 0xc8e78e94U,
            };
            HW_SCE_p_func101(Param_p73r_func101_003);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_F4H, 0x00001090U);

            static const uint32_t Param_p73r_func101_004[] =
            {
                0xb3c73a6bU, 0x32f73f8bU, 0x288f9758U, 0xa8099318U,
            };
            HW_SCE_p_func101(Param_p73r_func101_004);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_F4H, 0x000010a0U);

            static const uint32_t Param_p73r_func101_005[] =
            {
                0x44bb3f73U, 0x8f282ec2U, 0x5f42b74aU, 0xa0572f05U,
            };
            HW_SCE_p_func101(Param_p73r_func101_005);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_F4H, 0x000010b0U);

            static const uint32_t Param_p73r_func101_006[] =
            {
                0x8dceb0a3U, 0x9d407adeU, 0x044295e0U, 0xe559da3cU,
            };
            HW_SCE_p_func101(Param_p73r_func101_006);
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

        static const uint32_t Param_p73r_func101_007[] =
        {
            0x3344ac12U, 0xe5b5b6a8U, 0x4a359a8eU, 0x90894ba4U,
        };
        HW_SCE_p_func101(Param_p73r_func101_007);

        return FSP_SUCCESS;
    }
}
