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

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_40H, 0x00b00000U);

        HW_SCE_p_func101(0x4d5e1f56U, 0xe29a4c84U, 0xd387cb2fU, 0x13cabb5cU);
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_40H, 0x00b10000U);

        HW_SCE_p_func101(0x4ce5061bU, 0xc4e7ab14U, 0x26d622e2U, 0xa87aea6cU);
    }
    else if (InData_LC[0] == 0x00000002U)
    {
        WR1_PROG(REG_40H, 0x00b20000U);

        HW_SCE_p_func101(0x30cc4872U, 0x063082b5U, 0x50092503U, 0x4ff61566U);
    }
    else if (InData_LC[0] == 0x00000003U)
    {
        WR1_PROG(REG_40H, 0x00b30000U);

        HW_SCE_p_func101(0x889e14dbU, 0x839ef160U, 0x17326147U, 0x46155b41U);
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_40H, 0x00b40000U);

        HW_SCE_p_func101(0x7be61f78U, 0xc743ba61U, 0xf56e6bfcU, 0x85d1669bU);
    }
    else if (InData_LC[0] == 0x00000005U)
    {
        WR1_PROG(REG_40H, 0x00b50000U);

        HW_SCE_p_func101(0x22918d83U, 0xee30ab23U, 0xc4996919U, 0x4121fd6cU);
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_40H, 0x00b60000U);

        HW_SCE_p_func101(0x0b622040U, 0xbcd7eee6U, 0x07734b94U, 0xd70c1fbcU);
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_40H, 0x00b70000U);

        HW_SCE_p_func101(0xa220a7d0U, 0x720aa4afU, 0xbd94e49dU, 0xf93c6fd6U);
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_40H, 0x00b80000U);

        HW_SCE_p_func101(0x58eea1fbU, 0x15929c43U, 0xf9527817U, 0xd55719b6U);
    }
    else
    {
        WR1_PROG(REG_94H, 0x38000c00U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A70000U);

        HW_SCE_p_func101(0x9e3aaf09U, 0xb9210d60U, 0x6179cbd7U, 0x298b38bcU);
    }

    HW_SCE_p_func100(0xe8dfa0deU, 0x180f8d04U, 0xcbf6d41aU, 0x4286324fU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x373028f4U, 0xd9d5db24U, 0x0f492464U, 0x77aaee3eU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000003a1U);
        WR1_PROG(REG_D0H, 0x0a0700f5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0x4a6dc144U), change_endian_long(0x4531957bU),
                 change_endian_long(0x817db8c2U), change_endian_long(0xbdded65eU));

        HW_SCE_p_func100(0x33cddaeeU, 0xe316a858U, 0xfc15c88dU, 0xbdda5605U);
        WR1_PROG(REG_D0H, 0x4a470044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e470484U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x01a5da45U));

        HW_SCE_p_func100(0x37796818U, 0xdfd7426cU, 0x10b16059U, 0x1acf1a4bU);
        WR1_PROG(REG_D0H, 0x4a470044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e470494U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x02a5da45U));

        WR1_PROG(REG_14H, 0x000003a1U);
        WR1_PROG(REG_D0H, 0x0a0700f5U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_PROG(REG_2CH, change_endian_long(0xf253e7c3U), change_endian_long(0xbe30cfc0U),
                 change_endian_long(0xe01c4581U), change_endian_long(0x5cb708d6U));

        HW_SCE_p_func100(0x79ea15b4U, 0x47217101U, 0x8cc5f52fU, 0x8cb6ef43U);
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

        HW_SCE_p_func100(0xd977babeU, 0x77019f0cU, 0x224d74e8U, 0xafdff1c3U);
        WR1_PROG(REG_D0H, 0x08000095U);
        WR1_PROG(REG_00H, 0x00490011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_A0H, 0x00010000U);

        WR1_PROG(REG_B0H, 0x000004b2U);
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
        WR1_PROG(REG_2CH, change_endian_long(0x01603623U));

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0e008104U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x02603623U));

        WR1_PROG(REG_B0H, 0x000014b8U);
        WR1_PROG(REG_00H, 0x00c10021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x8a8fdb73U, 0xd90c3887U, 0x587948e7U, 0xeb9af0b1U);
        WR1_PROG(REG_D0H, 0x4a470044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e4704c4U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x01417d25U));

        WR1_PROG(REG_D0H, 0x4a040044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D0H, 0x0e040504U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x01917ba8U));

        WR1_PROG(REG_B0H, 0x000004b3U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B0H, 0x000004b4U);
        WR1_PROG(REG_00H, 0x00c10009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_78H, 0x00000222U);

        HW_SCE_p_func102(0x96a99333U, 0xdaa21363U, 0xdfb60698U, 0xc022754aU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
