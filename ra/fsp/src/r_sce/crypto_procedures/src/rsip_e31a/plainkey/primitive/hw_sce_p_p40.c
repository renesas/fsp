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

    HW_SCE_p_func_sub001(0x0000b420U, 0x00000009U, 0x34202801U, 0x20003401U);

    WR1_PROG(REG_94H, 0x00007c00U);
    WR1_PROG(REG_40H, 0x00602000U);

    if (InData_LC[0] == 0x00000000U)
    {
        WR1_PROG(REG_40H, 0x00b00000U);

        static const uint32_t Param_p40_func101_001[] =
        {
            0x4d5e1f56U, 0xe29a4c84U, 0xd387cb2fU, 0x13cabb5cU,
        };
        HW_SCE_p_func101(Param_p40_func101_001);
    }
    else if (InData_LC[0] == 0x00000001U)
    {
        WR1_PROG(REG_40H, 0x00b10000U);

        static const uint32_t Param_p40_func101_002[] =
        {
            0x4ce5061bU, 0xc4e7ab14U, 0x26d622e2U, 0xa87aea6cU,
        };
        HW_SCE_p_func101(Param_p40_func101_002);
    }
    else if (InData_LC[0] == 0x00000002U)
    {
        WR1_PROG(REG_40H, 0x00b20000U);

        static const uint32_t Param_p40_func101_003[] =
        {
            0x30cc4872U, 0x063082b5U, 0x50092503U, 0x4ff61566U,
        };
        HW_SCE_p_func101(Param_p40_func101_003);
    }
    else if (InData_LC[0] == 0x00000003U)
    {
        WR1_PROG(REG_40H, 0x00b30000U);

        static const uint32_t Param_p40_func101_004[] =
        {
            0x889e14dbU, 0x839ef160U, 0x17326147U, 0x46155b41U,
        };
        HW_SCE_p_func101(Param_p40_func101_004);
    }
    else if (InData_LC[0] == 0x00000004U)
    {
        WR1_PROG(REG_40H, 0x00b40000U);

        static const uint32_t Param_p40_func101_005[] =
        {
            0x7be61f78U, 0xc743ba61U, 0xf56e6bfcU, 0x85d1669bU,
        };
        HW_SCE_p_func101(Param_p40_func101_005);
    }
    else if (InData_LC[0] == 0x00000005U)
    {
        WR1_PROG(REG_40H, 0x00b50000U);

        static const uint32_t Param_p40_func101_006[] =
        {
            0x22918d83U, 0xee30ab23U, 0xc4996919U, 0x4121fd6cU,
        };
        HW_SCE_p_func101(Param_p40_func101_006);
    }
    else if (InData_LC[0] == 0x00000006U)
    {
        WR1_PROG(REG_40H, 0x00b60000U);

        static const uint32_t Param_p40_func101_007[] =
        {
            0x0b622040U, 0xbcd7eee6U, 0x07734b94U, 0xd70c1fbcU,
        };
        HW_SCE_p_func101(Param_p40_func101_007);
    }
    else if (InData_LC[0] == 0x00000007U)
    {
        WR1_PROG(REG_40H, 0x00b70000U);

        static const uint32_t Param_p40_func101_008[] =
        {
            0xa220a7d0U, 0x720aa4afU, 0xbd94e49dU, 0xf93c6fd6U,
        };
        HW_SCE_p_func101(Param_p40_func101_008);
    }
    else if (InData_LC[0] == 0x00000008U)
    {
        WR1_PROG(REG_40H, 0x00b80000U);

        static const uint32_t Param_p40_func101_009[] =
        {
            0x58eea1fbU, 0x15929c43U, 0xf9527817U, 0xd55719b6U,
        };
        HW_SCE_p_func101(Param_p40_func101_009);
    }
    else
    {
        HW_SCE_p_func_sub010(0x38000c00U, 0x00A70000U);

        static const uint32_t Param_p40_func101_010[] =
        {
            0x9e3aaf09U, 0xb9210d60U, 0x6179cbd7U, 0x298b38bcU,
        };
        HW_SCE_p_func101(Param_p40_func101_010);
    }

    static const uint32_t Param_p40_func100_001[] =
    {
        0xe8dfa0deU, 0x180f8d04U, 0xcbf6d41aU, 0x4286324fU,
    };
    HW_SCE_p_func100(Param_p40_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p40_func102_001[] =
        {
            0x373028f4U, 0xd9d5db24U, 0x0f492464U, 0x77aaee3eU,
        };
        HW_SCE_p_func102(Param_p40_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub011(0x000003a1U, 0x0a0700f5U);
        WR4_PROG(REG_2CH, change_endian_long(0x4a6dc144U), change_endian_long(0x4531957bU),
                 change_endian_long(0x817db8c2U), change_endian_long(0xbdded65eU));

        static const uint32_t Param_p40_func100_002[] =
        {
            0x33cddaeeU, 0xe316a858U, 0xfc15c88dU, 0xbdda5605U,
        };
        HW_SCE_p_func100(Param_p40_func100_002);
        HW_SCE_p_func_sub018(0x4a470044U, 0x00000000U);

        HW_SCE_p_func_sub018(0x0e470484U, 0x01a5da45U);

        static const uint32_t Param_p40_func100_003[] =
        {
            0x37796818U, 0xdfd7426cU, 0x10b16059U, 0x1acf1a4bU,
        };
        HW_SCE_p_func100(Param_p40_func100_003);
        HW_SCE_p_func_sub018(0x4a470044U, 0x00000000U);

        HW_SCE_p_func_sub018(0x0e470494U, 0x02a5da45U);

        HW_SCE_p_func_sub011(0x000003a1U, 0x0a0700f5U);
        WR4_PROG(REG_2CH, change_endian_long(0xf253e7c3U), change_endian_long(0xbe30cfc0U),
                 change_endian_long(0xe01c4581U), change_endian_long(0x5cb708d6U));

        static const uint32_t Param_p40_func100_004[] =
        {
            0x79ea15b4U, 0x47217101U, 0x8cc5f52fU, 0x8cb6ef43U,
        };
        HW_SCE_p_func100(Param_p40_func100_004);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d05U);
        WR1_PROG(REG_D8H, 0x20000000U);
        HW_SCE_p_func_sub003(0x00480011U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xf7008d05U);
        WR1_PROG(REG_D8H, 0x20000010U);
        HW_SCE_p_func_sub003(0x00480011U);
        WR1_PROG(REG_94H, 0x00000821U);
        WR1_PROG(REG_9CH, 0x80880001U);
        HW_SCE_p_func_sub003(0x03410021U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WR1_PROG(REG_D8H, 0x20000020U);
        HW_SCE_p_func_sub003(0x00480011U);
        WR1_PROG(REG_D0H, 0x8c100005U);
        HW_SCE_p_func_sub003(0x00410011U);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_9CH, 0x81880001U);
        HW_SCE_p_func_sub003(0x00490011U);

        static const uint32_t Param_p40_func100_005[] =
        {
            0xd977babeU, 0x77019f0cU, 0x224d74e8U, 0xafdff1c3U,
        };
        HW_SCE_p_func100(Param_p40_func100_005);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00490011U);

        WR1_PROG(REG_A0H, 0x00010000U);

        WR1_PROG(REG_B0H, 0x000004b2U);
        HW_SCE_p_func_sub003(0x00c00005U);
        WR1_PROG(REG_9CH, 0x81010000U);
        HW_SCE_p_func_sub003(0x00c90005U);

        HW_SCE_p_func_sub007(0x000002a1U, 0x40000000U, 0x4a008044U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_D4H, 0x40000000U);
        HW_SCE_p_func_sub018(0x0e008104U, 0x01603623U);

        WR1_PROG(REG_D4H, 0x40000000U);
        HW_SCE_p_func_sub018(0x0e008104U, 0x02603623U);

        WR1_PROG(REG_B0H, 0x000014b8U);
        HW_SCE_p_func_sub003(0x00c10021U);

        static const uint32_t Param_p40_func100_006[] =
        {
            0x8a8fdb73U, 0xd90c3887U, 0x587948e7U, 0xeb9af0b1U,
        };
        HW_SCE_p_func100(Param_p40_func100_006);
        HW_SCE_p_func_sub018(0x4a470044U, 0x00000000U);

        HW_SCE_p_func_sub018(0x0e4704c4U, 0x01417d25U);

        HW_SCE_p_func_sub018(0x4a040044U, 0x00000000U);

        HW_SCE_p_func_sub018(0x0e040504U, 0x01917ba8U);

        WR1_PROG(REG_B0H, 0x000004b3U);
        HW_SCE_p_func_sub003(0x00c10009U);

        WR1_PROG(REG_B0H, 0x000004b4U);
        HW_SCE_p_func_sub003(0x00c10009U);

        WR1_PROG(REG_78H, 0x00000222U);

        static const uint32_t Param_p40_func102_002[] =
        {
            0x96a99333U, 0xdaa21363U, 0xdfb60698U, 0xc022754aU,
        };
        HW_SCE_p_func102(Param_p40_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
