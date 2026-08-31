/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_LoadHukSub (uint32_t InData_LC[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00004001U);
    WR1_PROG(REG_108H, 0x00000000U);

    HW_SCE_p_func048(InData_LC);

    HW_SCE_p_func_sub022(0x0000b420U, 0x00000009U, 0x34202801U, 0x20003401U);

    WR1_PROG(REG_ECH, 0x00007c00U);
    WR1_PROG(REG_1CH, 0x00602000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_1CH, 0x00b80000U);

        static const uint32_t Param_p40_func101_001[] =
        {
            0x8df65220U, 0x66b86af0U, 0x024552f0U, 0x698bb6acU,
        };
        HW_SCE_p_func101(Param_p40_func101_001);
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_1CH, 0x00b00000U);

        static const uint32_t Param_p40_func101_002[] =
        {
            0x75474f29U, 0xcf9f73aaU, 0xa8987b45U, 0x01019f0cU,
        };
        HW_SCE_p_func101(Param_p40_func101_002);
    }
    else if (InData_LC[0] == 0x00000002U)
    {
        WR1_PROG(REG_1CH, 0x00b10000U);

        static const uint32_t Param_p40_func101_003[] =
        {
            0x37fe7e13U, 0xdba1bf8dU, 0xad1e7c16U, 0xf4949bbaU,
        };
        HW_SCE_p_func101(Param_p40_func101_003);
    }
    else if (InData_LC[0] == 0x00000003U)
    {
        WR1_PROG(REG_1CH, 0x00b20000U);

        static const uint32_t Param_p40_func101_004[] =
        {
            0xcaf7e415U, 0x4128fb42U, 0xdb48afe2U, 0x99074a75U,
        };
        HW_SCE_p_func101(Param_p40_func101_004);
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_1CH, 0x00b30000U);

        static const uint32_t Param_p40_func101_005[] =
        {
            0x57f8f4a6U, 0x94787521U, 0x31fcee4fU, 0x864d46bdU,
        };
        HW_SCE_p_func101(Param_p40_func101_005);
    }
    else if (InData_LC[0] == 0x00000005U)
    {
        WR1_PROG(REG_1CH, 0x00b40000U);

        static const uint32_t Param_p40_func101_006[] =
        {
            0xb16bd6fdU, 0xc927d654U, 0xfc8bef50U, 0x3d3513a4U,
        };
        HW_SCE_p_func101(Param_p40_func101_006);
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_1CH, 0x00b50000U);

        static const uint32_t Param_p40_func101_007[] =
        {
            0x086e5c12U, 0x2708cae7U, 0x24c60329U, 0xd6a1f0ceU,
        };
        HW_SCE_p_func101(Param_p40_func101_007);
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_1CH, 0x00b60000U);

        static const uint32_t Param_p40_func101_008[] =
        {
            0x64586489U, 0xe5ec3887U, 0xaf796043U, 0xf870aad7U,
        };
        HW_SCE_p_func101(Param_p40_func101_008);
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_1CH, 0x00b70000U);

        static const uint32_t Param_p40_func101_009[] =
        {
            0xdd18b7c6U, 0x61da8f10U, 0x2dddd787U, 0x0986d7deU,
        };
        HW_SCE_p_func101(Param_p40_func101_009);
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00A60000U);

        static const uint32_t Param_p40_func101_010[] =
        {
            0x855d7c4aU, 0x63f263faU, 0x172ed129U, 0x7c8fa20fU,
        };
        HW_SCE_p_func101(Param_p40_func101_010);
    }

    static const uint32_t Param_p40_func100_001[] =
    {
        0xc49e2b89U, 0x3ccaecb7U, 0xa622a807U, 0x78f51bbeU,
    };
    HW_SCE_p_func100(Param_p40_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p40_func102_001[] =
        {
            0x0c3811c9U, 0xb8dedefdU, 0xeb431a83U, 0xd5122286U,
        };
        HW_SCE_p_func102(Param_p40_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_104H, 0x00000352U);
        WR1_PROG(REG_C4H, 0x000f3a0dU);
        WAIT_STS(REG_104H, 31, 1);
        WR4_PROG(REG_100H, change_endian_long(0x7e2fdbffU), change_endian_long(0xd4e34e49U),
                 change_endian_long(0x86044a47U), change_endian_long(0x78ea77fbU));

        static const uint32_t Param_p40_func100_002[] =
        {
            0x5a22ea97U, 0xb775468eU, 0xc77479b3U, 0xa7c5d2eaU,
        };
        HW_SCE_p_func100(Param_p40_func100_002);
        WR1_PROG(REG_C4H, 0x20443a0cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_C4H, 0x20083e1cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x01ea725dU));

        static const uint32_t Param_p40_func100_003[] =
        {
            0xfbcffc6bU, 0xce9dd311U, 0x605e19c8U, 0xfe10bb07U,
        };
        HW_SCE_p_func100(Param_p40_func100_003);
        WR1_PROG(REG_C4H, 0x20443a0cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_C4H, 0x20093e1cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x02ea725dU));

        WR1_PROG(REG_104H, 0x00000352U);
        WR1_PROG(REG_C4H, 0x000f3a0dU);
        WAIT_STS(REG_104H, 31, 1);
        WR4_PROG(REG_100H, change_endian_long(0x1201f0d2U), change_endian_long(0x9fc1d562U),
                 change_endian_long(0x4f02fc25U), change_endian_long(0x6b60ff19U));

        static const uint32_t Param_p40_func100_004[] =
        {
            0xba5d965cU, 0x54ecb6f4U, 0xf3e2d5bfU, 0xcf8889bcU,
        };
        HW_SCE_p_func100(Param_p40_func100_004);
        WR1_PROG(REG_D0H, 0x40000100U);
        WR1_PROG(REG_C4H, 0x02f087b5U);
        WR1_PROG(REG_E8H, 0x80000000U);
        WR1_PROG(REG_00H, 0x00002613U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x00f087b5U);
        WR1_PROG(REG_E8H, 0x80000004U);
        WR1_PROG(REG_00H, 0x00002613U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

        static const uint32_t Param_p40_func100_005[] =
        {
            0xae1e176eU, 0x880b1b75U, 0x6486a9a3U, 0x9cf0492aU,
        };
        HW_SCE_p_func100(Param_p40_func100_005);
        HW_SCE_p_func_sub019(0x00090805U, 0x00001213U);

        WR1_PROG(REG_ECH, 0x0000b420U);
        WR1_PROG(REG_ECH, 0x000001b0U);
        WR1_PROG(REG_ECH, 0x00003c01U);

        WR1_PROG(REG_D0H, 0x40000000U);
        WR1_PROG(REG_C4H, 0x000087b5U);
        WR1_PROG(REG_E8H, 0x80000008U);
        WR1_PROG(REG_00H, 0x00002613U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);
        HW_SCE_p_func_sub013(0x00800c45U, 0x00002213U);

        WR1_PROG(REG_104H, 0x00000251U);
        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x00448a04U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x00008e84U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x019ee295U));

        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x00008e84U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x029ee295U));

        WR1_PROG(REG_ECH, 0x0000b420U);
        WR1_PROG(REG_ECH, 0x000001d0U);
        HW_SCE_p_func_sub010(0x80880001U, 0x00008123U);

        static const uint32_t Param_p40_func100_006[] =
        {
            0xf779cdc0U, 0x8979d743U, 0x8cdcd58bU, 0xabca3852U,
        };
        HW_SCE_p_func100(Param_p40_func100_006);
        WR1_PROG(REG_C4H, 0x20443a0cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_C4H, 0x200c3e1cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x0152db38U));

        WR1_PROG(REG_C4H, 0x00440a0cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x00000000U));

        WR1_PROG(REG_C4H, 0x00000e9cU);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, change_endian_long(0x01f7370eU));

        WR1_PROG(REG_ECH, 0x0000b420U);
        WR1_PROG(REG_ECH, 0x000001c0U);
        HW_SCE_p_func_sub010(0x80840001U, 0x00008213U);

        WR1_PROG(REG_13CH, 0x00000211U);

        static const uint32_t Param_p40_func102_002[] =
        {
            0xff71be6bU, 0xdfbc00b3U, 0xa5a52bdaU, 0x8b9ab0edU,
        };
        HW_SCE_p_func102(Param_p40_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
