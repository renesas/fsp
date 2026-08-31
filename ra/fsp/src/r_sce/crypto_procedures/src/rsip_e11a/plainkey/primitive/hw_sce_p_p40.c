/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_LoadHukSub (const uint32_t InData_LC[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00400001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func048(InData_LC);

    HW_SCE_p_func_sub001(0x0000b420U, 0x00000009U, 0x34202801U);
    WR1_PROG(REG_94H, 0x20003401U);

    HW_SCE_p_func_sub015(0x00007c00U, 0x00602000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_40H, 0x00b00000U);

        static const uint32_t Param_p40_func101_001[] =
        {
            0x399b3355U, 0x69a5994eU, 0x6f4f82beU, 0x7cdb80bbU,
        };
        HW_SCE_p_func101(Param_p40_func101_001);
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_40H, 0x00b10000U);

        static const uint32_t Param_p40_func101_002[] =
        {
            0x06014c3aU, 0x828be8fbU, 0xf23cea72U, 0xdca0f318U,
        };
        HW_SCE_p_func101(Param_p40_func101_002);
    }
    else if (InData_LC[0] == 0x00000002U)
    {
        WR1_PROG(REG_40H, 0x00b20000U);

        static const uint32_t Param_p40_func101_003[] =
        {
            0x4a0b603eU, 0x2caa0248U, 0x84f54389U, 0xfb2d9d8bU,
        };
        HW_SCE_p_func101(Param_p40_func101_003);
    }
    else if (InData_LC[0] == 0x00000003U)
    {
        WR1_PROG(REG_40H, 0x00b30000U);

        static const uint32_t Param_p40_func101_004[] =
        {
            0xf65e1250U, 0x698a4573U, 0x4d70cd6dU, 0xf1df75c0U,
        };
        HW_SCE_p_func101(Param_p40_func101_004);
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_40H, 0x00b40000U);

        static const uint32_t Param_p40_func101_005[] =
        {
            0x73b39312U, 0x9a94d935U, 0x61c3ec9cU, 0x25bbbeb0U,
        };
        HW_SCE_p_func101(Param_p40_func101_005);
    }
    else if (InData_LC[0] == 0x00000005U)
    {
        WR1_PROG(REG_40H, 0x00b50000U);

        static const uint32_t Param_p40_func101_006[] =
        {
            0x26f0499bU, 0x20fd5bdcU, 0x4f9bb5b6U, 0xfbffeb9bU,
        };
        HW_SCE_p_func101(Param_p40_func101_006);
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_40H, 0x00b60000U);

        static const uint32_t Param_p40_func101_007[] =
        {
            0x155ad156U, 0xb6ce6493U, 0x20cd7b9fU, 0xeba67dacU,
        };
        HW_SCE_p_func101(Param_p40_func101_007);
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_40H, 0x00b70000U);

        static const uint32_t Param_p40_func101_008[] =
        {
            0xc35ac31dU, 0x5d0eddebU, 0x4ea7686eU, 0xac86af8dU,
        };
        HW_SCE_p_func101(Param_p40_func101_008);
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_40H, 0x00b80000U);

        static const uint32_t Param_p40_func101_009[] =
        {
            0x859a7728U, 0x4c61f1e8U, 0xa9692a5aU, 0x97a77a14U,
        };
        HW_SCE_p_func101(Param_p40_func101_009);
    }
    else
    {
        HW_SCE_p_func_sub009(0x38000c00U, 0x00A60000U);

        static const uint32_t Param_p40_func101_010[] =
        {
            0x8f4361a7U, 0x4f55fa93U, 0x6c256098U, 0x91f05044U,
        };
        HW_SCE_p_func101(Param_p40_func101_010);
    }

    static const uint32_t Param_p40_func100_001[] =
    {
        0x2a3cbb58U, 0x75f9c1abU, 0x7d6552eaU, 0xd9a42065U,
    };
    HW_SCE_p_func100(Param_p40_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p40_func102_001[] =
        {
            0x2be01237U, 0x26d430f9U, 0x5e052767U, 0x461d8d2cU,
        };
        HW_SCE_p_func102(Param_p40_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub008(0x000003a1U, 0x0a0700f5U);
        WR4_PROG(REG_2CH, change_endian_long(0xfd32ed95U), change_endian_long(0xc0adaf20U),
                 change_endian_long(0x61f7d366U), change_endian_long(0x1a13aa80U));

        static const uint32_t Param_p40_func100_002[] =
        {
            0x75d292f4U, 0x33520d7cU, 0xa3e35cf1U, 0xd501a8c9U,
        };
        HW_SCE_p_func100(Param_p40_func100_002);
        HW_SCE_p_func_sub010(0x4a470044U, 0x00000000U);

        HW_SCE_p_func_sub010(0x0e470484U, 0x015cfefdU);

        static const uint32_t Param_p40_func100_003[] =
        {
            0xf801104cU, 0x3066ec10U, 0x133ee623U, 0xd724d94cU,
        };
        HW_SCE_p_func100(Param_p40_func100_003);
        HW_SCE_p_func_sub010(0x4a470044U, 0x00000000U);

        HW_SCE_p_func_sub010(0x0e470494U, 0x025cfefdU);

        HW_SCE_p_func_sub008(0x000003a1U, 0x0a0700f5U);
        WR4_PROG(REG_2CH, change_endian_long(0xb6803eb9U), change_endian_long(0x31b4dd4aU),
                 change_endian_long(0xfc5cdeaeU), change_endian_long(0xdb3d1dfdU));

        static const uint32_t Param_p40_func100_004[] =
        {
            0x7947ad55U, 0x9c701c5fU, 0x4341e36cU, 0x99b8d05dU,
        };
        HW_SCE_p_func100(Param_p40_func100_004);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d05U);
        WR1_PROG(REG_D8H, 0x20000000U);
        HW_SCE_p_func_sub002(0x00480011U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xf7008d05U);
        WR1_PROG(REG_D8H, 0x20000010U);
        HW_SCE_p_func_sub002(0x00480011U);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80880001U);
        HW_SCE_p_func_sub002(0x03410021U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WR1_PROG(REG_D8H, 0x20000020U);
        HW_SCE_p_func_sub002(0x00480011U);
        WR1_PROG(REG_D0H, 0x8c100005U);
        HW_SCE_p_func_sub002(0x00410011U);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_9CH, 0x81880001U);
        HW_SCE_p_func_sub002(0x00490011U);

        static const uint32_t Param_p40_func100_005[] =
        {
            0x1a4a6a5dU, 0x9f3c2a50U, 0xa5e46326U, 0x5bebb764U,
        };
        HW_SCE_p_func100(Param_p40_func100_005);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub002(0x00490011U);

        WR1_PROG(REG_A0H, 0x00010000U);

        WR1_PROG(REG_B0H, 0x00000492U);
        HW_SCE_p_func_sub002(0x00c00005U);
        WR1_PROG(REG_9CH, 0x81010000U);
        HW_SCE_p_func_sub002(0x00c90005U);

        HW_SCE_p_func_sub007(0x000002a1U, 0x40000000U, 0x4a008044U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D4H, 0x40000000U);
        HW_SCE_p_func_sub010(0x0e008104U, 0x01d65991U);

        WR1_PROG(REG_D4H, 0x40000000U);
        HW_SCE_p_func_sub010(0x0e008104U, 0x02d65991U);

        WR1_PROG(REG_B0H, 0x00001498U);
        HW_SCE_p_func_sub002(0x00c10021U);

        static const uint32_t Param_p40_func100_006[] =
        {
            0x215a41c2U, 0xd0d54e4bU, 0x73da3375U, 0x7c1ce3efU,
        };
        HW_SCE_p_func100(Param_p40_func100_006);
        HW_SCE_p_func_sub010(0x4a470044U, 0x00000000U);

        HW_SCE_p_func_sub010(0x0e4704c4U, 0x0152db38U);

        HW_SCE_p_func_sub010(0x4a040044U, 0x00000000U);

        HW_SCE_p_func_sub010(0x0e040504U, 0x010daaebU);

        WR1_PROG(REG_B0H, 0x00000493U);
        HW_SCE_p_func_sub002(0x00c10009U);

        WR1_PROG(REG_B0H, 0x00000494U);
        HW_SCE_p_func_sub002(0x00c10009U);

        WR1_PROG(REG_78H, 0x00000202U);

        static const uint32_t Param_p40_func102_002[] =
        {
            0xb5de2ba1U, 0x85465aa0U, 0x30d01d96U, 0xd9d05b11U,
        };
        HW_SCE_p_func102(Param_p40_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
