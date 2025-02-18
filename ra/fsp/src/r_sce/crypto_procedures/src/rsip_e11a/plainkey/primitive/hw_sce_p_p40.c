/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_LoadHukSub (const uint32_t InData_LC[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00400001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func048(InData_LC);

    WR1_PROG(REG_94H, 0x0000b420U);
    WR1_PROG(REG_94H, 0x00000009U);
    WR1_PROG(REG_94H, 0x34202801U);
    WR1_PROG(REG_94H, 0x20003401U);

    WR1_PROG(REG_94H, 0x00007c00U);
    WR1_PROG(REG_40H, 0x00602000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_40H, 0x00b00000U);

        HW_SCE_p_func101(0x399b3355U, 0x69a5994eU, 0x6f4f82beU, 0x7cdb80bbU);
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_40H, 0x00b10000U);

        HW_SCE_p_func101(0x06014c3aU, 0x828be8fbU, 0xf23cea72U, 0xdca0f318U);
    }
    else if (InData_LC[0] == 0x00000002U)
    {
        WR1_PROG(REG_40H, 0x00b20000U);

        HW_SCE_p_func101(0x4a0b603eU, 0x2caa0248U, 0x84f54389U, 0xfb2d9d8bU);
    }
    else if (InData_LC[0] == 0x00000003U)
    {
        WR1_PROG(REG_40H, 0x00b30000U);

        HW_SCE_p_func101(0xf65e1250U, 0x698a4573U, 0x4d70cd6dU, 0xf1df75c0U);
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_40H, 0x00b40000U);

        HW_SCE_p_func101(0x73b39312U, 0x9a94d935U, 0x61c3ec9cU, 0x25bbbeb0U);
    }
    else if (InData_LC[0] == 0x00000005U)
    {
        WR1_PROG(REG_40H, 0x00b50000U);

        HW_SCE_p_func101(0x26f0499bU, 0x20fd5bdcU, 0x4f9bb5b6U, 0xfbffeb9bU);
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_40H, 0x00b60000U);

        HW_SCE_p_func101(0x155ad156U, 0xb6ce6493U, 0x20cd7b9fU, 0xeba67dacU);
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_40H, 0x00b70000U);

        HW_SCE_p_func101(0xc35ac31dU, 0x5d0eddebU, 0x4ea7686eU, 0xac86af8dU);
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_40H, 0x00b80000U);

        HW_SCE_p_func101(0x859a7728U, 0x4c61f1e8U, 0xa9692a5aU, 0x97a77a14U);
    }
    else
    {
        WR1_PROG(REG_94H, 0x38000c00U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A60000U);

        HW_SCE_p_func101(0x8f4361a7U, 0x4f55fa93U, 0x6c256098U, 0x91f05044U);
    }

    HW_SCE_p_func100(0x2a3cbb58U, 0x75f9c1abU, 0x7d6552eaU, 0xd9a42065U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x2be01237U, 0x26d430f9U, 0x5e052767U, 0x461d8d2cU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000003a1U);
        WR1_PROG(REG_D0H, 0x0a0700f5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0xfd32ed95U), change_endian_long(0xc0adaf20U),
                 change_endian_long(0x61f7d366U), change_endian_long(0x1a13aa80U));

        HW_SCE_p_func100(0x75d292f4U, 0x33520d7cU, 0xa3e35cf1U, 0xd501a8c9U);
        WR1_PROG(REG_D0H, 0x4a470044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e470484U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x015cfefdU));

        HW_SCE_p_func100(0xf801104cU, 0x3066ec10U, 0x133ee623U, 0xd724d94cU);
        WR1_PROG(REG_D0H, 0x4a470044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e470494U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x025cfefdU));

        WR1_PROG(REG_14H, 0x000003a1U);
        WR1_PROG(REG_D0H, 0x0a0700f5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0xb6803eb9U), change_endian_long(0x31b4dd4aU),
                 change_endian_long(0xfc5cdeaeU), change_endian_long(0xdb3d1dfdU));

        HW_SCE_p_func100(0x7947ad55U, 0x9c701c5fU, 0x4341e36cU, 0x99b8d05dU);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d05U);
        WR1_PROG(REG_D8H, 0x20000000U);
        WR1_PROG(REG_00H, 0x00480011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xf7008d05U);
        WR1_PROG(REG_D8H, 0x20000010U);
        WR1_PROG(REG_00H, 0x00480011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80880001U);
        WR1_PROG(REG_00H, 0x03410021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WR1_PROG(REG_D8H, 0x20000020U);
        WR1_PROG(REG_00H, 0x00480011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_D0H, 0x8c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_9CH, 0x81880001U);
        WR1_PROG(REG_00H, 0x00490011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x1a4a6a5dU, 0x9f3c2a50U, 0xa5e46326U, 0x5bebb764U);
        WR1_PROG(REG_D0H, 0x08000095U);
        WR1_PROG(REG_00H, 0x00490011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_A0H, 0x00010000U);

        WR1_PROG(REG_B0H, 0x00000492U);
        WR1_PROG(REG_00H, 0x00c00005U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_9CH, 0x81010000U);
        WR1_PROG(REG_00H, 0x00c90005U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000002a1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x4a008044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0e008104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x01d65991U));

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0e008104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x02d65991U));

        WR1_PROG(REG_B0H, 0x00001498U);
        WR1_PROG(REG_00H, 0x00c10021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x215a41c2U, 0xd0d54e4bU, 0x73da3375U, 0x7c1ce3efU);
        WR1_PROG(REG_D0H, 0x4a470044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e4704c4U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x0152db38U));

        WR1_PROG(REG_D0H, 0x4a040044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e040504U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x010daaebU));

        WR1_PROG(REG_B0H, 0x00000493U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x00000494U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_78H, 0x00000202U);

        HW_SCE_p_func102(0xb5de2ba1U, 0x85465aa0U, 0x30d01d96U, 0xd9d05b11U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
