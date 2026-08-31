/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_SelfCheck2Sub (void)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00820001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x0b0700c4U, 0x01a0d7adU);

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000074U, 0x00000000U);

    HW_SCE_p_func_sub001(0x3000a820U, 0x00000003U, 0x00010020U, 0x00000821U);
    WR1_PROG(REG_94H, 0x00000080U);

    WAIT_STS(REG_E8H, 0, 0);

    static const uint32_t Param_p82_func100_001[] =
    {
        0x1886c19bU, 0x53f2e8d1U, 0x3208b1f1U, 0x62ab78f3U,
    };
    HW_SCE_p_func100(Param_p82_func100_001);
    WR1_PROG(REG_94H, 0x00007c01U);
    WR1_PROG(REG_40H, 0x00600000U);

    if (RD1_MASK(REG_44H, 0x0000ffffU) == 0x00000000U)
    {
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200003U);

        static const uint32_t Param_p82_func101_001[] =
        {
            0x4c58f7d8U, 0x35804f26U, 0x1aabfaf3U, 0x4253b968U,
        };
        HW_SCE_p_func101(Param_p82_func101_001);
    }
    else if (RD1_MASK(REG_44H, 0x0000ffffU) == 0x00000001U)
    {
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200001U);

        static const uint32_t Param_p82_func101_002[] =
        {
            0xae0467e7U, 0x13b724ecU, 0x72f8f961U, 0x94ee4661U,
        };
        HW_SCE_p_func101(Param_p82_func101_002);
    }
    else if (RD1_MASK(REG_44H, 0x0000ffffU) == 0x00000002U)
    {
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200002U);

        static const uint32_t Param_p82_func101_003[] =
        {
            0x8e4948a0U, 0x99c62c39U, 0x165e8e82U, 0x0b6b7418U,
        };
        HW_SCE_p_func101(Param_p82_func101_003);
    }

    WR1_PROG(REG_D0H, 0x08000044U);
    WR1_PROG(REG_9CH, 0x81010020U);
    HW_SCE_p_func_sub003(0x00490005U);

    WR1_PROG(REG_94H, 0x00000800U);
    WR1_PROG(REG_9CH, 0x80880000U);
    HW_SCE_p_func_sub003(0x03400021U);

    HW_SCE_p_func_sub001(0x000008e7U, 0x0000b480U, 0xffffffffU, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000001U);

    WR1_PROG(REG_D0H, 0x0e340406U);

    for (iLoop = 0U; iLoop < 32U; iLoop++)
    {
        WR1_PROG(REG_9CH, 0x80010000U);
        HW_SCE_p_func_sub003(0x03440005U);

        WR1_PROG(REG_9CH, 0x81010000U);
        HW_SCE_p_func_sub003(0x00490005U);

        WR1_PROG(REG_94H, 0x00003420U);

        for (jLoop = 0U; jLoop < 8U; jLoop++)
        {
            HW_SCE_p_func_sub001(0x00003441U, 0x00008c40U, 0x0000000fU, 0x00016c42U);

            HW_SCE_p_func_sub001(0x01003862U, 0x00002c60U, 0x01003c62U, 0x00046821U);
        }

        HW_SCE_p_func_sub001(0x00003420U, 0x00003441U, 0x00008c40U, 0x80000000U);

        HW_SCE_p_func_sub001(0x38000882U, 0x00030020U, 0x00002ca0U, 0x342028c5U);
        HW_SCE_p_func_sub001(0x100034c5U, 0x00000060U, 0x0000b4a0U, 0x00000001U);

        WR1_PROG(REG_94H, 0x00000080U);

        for (jLoop = 0U; jLoop < 31; jLoop++)
        {
            HW_SCE_p_func_sub001(0x00016c21U, 0x00003481U, 0x00008c80U, 0x80000000U);

            HW_SCE_p_func_sub001(0x38000882U, 0x00030020U, 0x00002ca0U, 0x342028c5U);
            HW_SCE_p_func_sub001(0x100034c5U, 0x00000060U, 0x00003444U, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000001U);

            WR1_PROG(REG_94H, 0x00000080U);
        }

        WR1_PROG(REG_94H, 0x00003420U);

        for (jLoop = 0U; jLoop < 32U; jLoop++)
        {
            HW_SCE_p_func_sub001(0x38008c20U, 0x00000001U, 0x00020020U, 0x00002ce0U);

            HW_SCE_p_func_sub001(0x00000060U, 0x0000a4e0U, 0x00010000U, 0x00000080U);

            WR1_PROG(REG_94H, 0x00016821U);
        }
    }

    WR1_PROG(REG_40H, 0x00001200U);
    WAIT_STS(REG_C8H, 6, 0);
    WR1_PROG(REG_D0H, 0x00000000U);
    WR1_PROG(REG_40H, 0x00000400U);

    HW_SCE_p_func_sub001(0x00000800U, 0x0000b420U, 0x00000033U, 0x342028c1U);
    HW_SCE_p_func_sub001(0x2000d011U, 0x0000b4a0U, 0x00000348U, 0x0000b4c0U);
    HW_SCE_p_func_sub001(0x000000b7U, 0x00003467U, 0x00008c60U, 0x0000ffffU);

    HW_SCE_p_func_sub001(0x34202865U, 0x2000d012U, 0x342028c3U, 0x2000d012U);

    HW_SCE_p_func_sub001(0x001068e7U, 0x342028e5U, 0x2000d013U, 0x342028c7U);
    WR1_PROG(REG_94H, 0x2000d013U);

    WR1_PROG(REG_94H, 0x00002467U);

    static const uint32_t Param_p82_func100_002[] =
    {
        0xbdf71146U, 0xe353230bU, 0xc1e8e5b9U, 0x661592d7U,
    };
    HW_SCE_p_func100(Param_p82_func100_002);
    HW_SCE_p_func_sub006(0x38008860U, 0x00000400U, 0x00270000U);

    WR1_PROG(REG_40H, 0x00402000U);

    WR1_PROG(REG_08H, 0x00020000U);

    HW_SCE_p_func_sub001(0x0000b420U, 0x0000005AU, 0x00000842U, 0x00000863U);

    HW_SCE_p_func_sub022(0x00000884U, 0x0000b4a0U, 0x00000002U);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        HW_SCE_p_func_sub001(0x010038c4U, 0x34202826U, 0x10005002U, 0x00002466U);

        WR1_PROG(REG_94H, 0x00002c40U);

        WR1_PROG(REG_94H, 0x00002485U);
    }

    static const uint32_t Param_p82_func100_003[] =
    {
        0x0baf2112U, 0xbda73caaU, 0x874196f6U, 0x1034f852U,
    };
    HW_SCE_p_func100(Param_p82_func100_003);
    HW_SCE_p_func_sub006(0x38008860U, 0x00000100U, 0x00270000U);

    WR1_PROG(REG_40H, 0x00402000U);

    WR1_PROG(REG_08H, 0x00020000U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);
    WR1_PROG(REG_9CH, 0x80010020U);
    HW_SCE_p_func_sub003(0x03410005U);
    HW_SCE_p_func_sub003(0x0001000dU);

    HW_SCE_p_func_sub006(0x00002c20U, 0x38000c00U, 0x00A70000U);

    static const uint32_t Param_p82_func100_004[] =
    {
        0x09e6c50dU, 0xa1055fc5U, 0xfd0d26b7U, 0xa0cde887U,
    };
    HW_SCE_p_func100(Param_p82_func100_004);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p82_func102_001[] =
        {
            0x0a9355a5U, 0x451c4845U, 0x89a197b3U, 0x743603e3U,
        };
        HW_SCE_p_func102(Param_p82_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_RETRY;
    }
    else
    {
        static const uint32_t Param_p82_func100_005[] =
        {
            0x08bf3fe5U, 0xe0dffa77U, 0x758dd3d3U, 0x12c65024U,
        };
        HW_SCE_p_func100(Param_p82_func100_005);

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c300104U, 0x00000000U);
        WR1_PROG(REG_9CH, 0x80040000U);
        HW_SCE_p_func_sub003(0x03410011U);

        WR1_PROG(REG_D4H, 0x00000600U);
        WR1_PROG(REG_D0H, 0x0e349407U);
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200003U);
        HW_SCE_p_func_sub003(0x00440071U);
        WR1_PROG(REG_D0H, 0x0e340505U);
        HW_SCE_p_func_sub003(0x00440011U);

        WAIT_STS(REG_E8H, 3, 0);
        WR1_PROG(REG_E0H, 0x00000000U);
        WR1_PROG(REG_9CH, 0x80040080U);
        HW_SCE_p_func_sub003(0x03410011U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x080000b4U, 0x00000000U);

        static const uint32_t Param_p82_func100_006[] =
        {
            0x03149dafU, 0x850ff3b5U, 0x04a466b7U, 0x02a4c914U,
        };
        HW_SCE_p_func100(Param_p82_func100_006);
        HW_SCE_p_func_sub011(0x000003a1U, 0x08000075U);
        WR4_PROG(REG_2CH, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000001U));

        HW_SCE_p_func_sub021(0x00000100U, 0x07338d07U, 0x81080000U);
        HW_SCE_p_func_sub003(0x00490021U);

        WR1_PROG(REG_D0H, 0x080000b5U);
        HW_SCE_p_func_sub003(0x00410011U);

        static const uint32_t Param_p82_func100_007[] =
        {
            0x85736a47U, 0x92660c55U, 0x9e0b38bbU, 0x03650b99U,
        };
        HW_SCE_p_func100(Param_p82_func100_007);
        WR1_PROG(REG_D0H, 0x08000075U);
        HW_SCE_p_func_sub003(0x00410011U);

        HW_SCE_p_func103();
        static const uint32_t Param_p82_func100_008[] =
        {
            0xebecbf36U, 0x9084d5d3U, 0x427cb8c8U, 0x82c1d1a0U,
        };
        HW_SCE_p_func100(Param_p82_func100_008);
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c2000d4U, 0x00000000U);

        static const uint32_t Param_p82_func100_009[] =
        {
            0xd005eb06U, 0x7567b334U, 0xd9cbefc1U, 0xa1de75ddU,
        };
        HW_SCE_p_func100(Param_p82_func100_009);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

        WR1_PROG(REG_A0H, 0x00030000U);
        WR1_PROG(REG_04H, 0x20000000U);
        WR1_PROG(REG_B0H, 0x00000401U);

        HW_SCE_p_func_sub003(0x00c10009U);
        HW_SCE_p_func_sub003(0x00010009U);

        WR1_PROG(REG_04H, 0x00000000U);
        WR1_PROG(REG_A0H, 0x00030000U);
        WR1_PROG(REG_B0H, 0x0000f400U);
        HW_SCE_p_func_sub003(0x00c00801U);

        WR1_PROG(REG_70H, 0x00008002U);
        WR1_PROG(REG_78H, 0x00000d01U);

        WR1_PROG(REG_70H, 0x00008001U);

        WR1_PROG(REG_78H, 0x00000221U);

        static const uint32_t Param_p82_func102_002[] =
        {
            0x19229394U, 0x9c4ca626U, 0xea3b7f44U, 0x695a35e6U,
        };
        HW_SCE_p_func102(Param_p82_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
