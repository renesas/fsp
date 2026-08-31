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

    HW_SCE_p_func_sub004(0x000000a1U, 0x0b0700c4U, 0x013e68caU);

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000074U, 0x00000000U);

    HW_SCE_p_func_sub001(0x3000a820U, 0x00000003U, 0x00010020U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_94H, 0x00000080U);

    WAIT_STS(REG_E8H, 0, 0);

    static const uint32_t Param_p82_func100_001[] =
    {
        0x55d73436U, 0x03cb094dU, 0x01316a96U, 0x9e88f677U,
    };
    HW_SCE_p_func100(Param_p82_func100_001);
    HW_SCE_p_func_sub015(0x00007c01U, 0x00600000U);

    if (RD1_MASK(REG_44H, 0x0000ffffU) == 0x00000000U)
    {
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200003U);

        static const uint32_t Param_p82_func101_001[] =
        {
            0xf9fb1361U, 0x8c6fe7ffU, 0x567aafc3U, 0xa8b0b397U,
        };
        HW_SCE_p_func101(Param_p82_func101_001);
    }
    else if (RD1_MASK(REG_44H, 0x0000ffffU) == 0x00000001U)
    {
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200001U);

        static const uint32_t Param_p82_func101_002[] =
        {
            0x44a06a62U, 0x96362a25U, 0x8e01b304U, 0x1c5a5978U,
        };
        HW_SCE_p_func101(Param_p82_func101_002);
    }
    else if (RD1_MASK(REG_44H, 0x0000ffffU) == 0x00000002U)
    {
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200002U);

        static const uint32_t Param_p82_func101_003[] =
        {
            0x884c99e4U, 0x9a8e7fa1U, 0x92819604U, 0xb2025e49U,
        };
        HW_SCE_p_func101(Param_p82_func101_003);
    }

    WR1_PROG(REG_D0H, 0x08000044U);
    WR1_PROG(REG_9CH, 0x81010020U);
    HW_SCE_p_func_sub002(0x00490005U);

    WR1_PROG(REG_94H, 0x00000800U);
    WR1_PROG(REG_9CH, 0x80880000U);
    HW_SCE_p_func_sub002(0x03400021U);

    HW_SCE_p_func_sub001(0x000008e7U, 0x0000b480U, 0xffffffffU);

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000001U);

    WR1_PROG(REG_D0H, 0x0e340406U);

    for (iLoop = 0U; iLoop < 32U; iLoop++)
    {
        WR1_PROG(REG_9CH, 0x80010000U);
        HW_SCE_p_func_sub002(0x03440005U);

        WR1_PROG(REG_9CH, 0x81010000U);
        HW_SCE_p_func_sub002(0x00490005U);

        WR1_PROG(REG_94H, 0x00003420U);

        for (jLoop = 0U; jLoop < 8U; jLoop++)
        {
            HW_SCE_p_func_sub001(0x00003441U, 0x00008c40U, 0x0000000fU);

            HW_SCE_p_func_sub001(0x00016c42U, 0x01003862U, 0x00002c60U);

            WR1_PROG(REG_94H, 0x01003c62U);

            WR1_PROG(REG_94H, 0x00046821U);
        }

        HW_SCE_p_func_sub001(0x00003420U, 0x00003441U, 0x00008c40U);
        HW_SCE_p_func_sub001(0x80000000U, 0x38000882U, 0x00030020U);

        HW_SCE_p_func_sub001(0x00002ca0U, 0x342028c5U, 0x100034c5U);

        HW_SCE_p_func_sub001(0x00000060U, 0x0000b4a0U, 0x00000001U);

        WR1_PROG(REG_94H, 0x00000080U);

        for (jLoop = 0U; jLoop < 31; jLoop++)
        {
            HW_SCE_p_func_sub001(0x00016c21U, 0x00003481U, 0x00008c80U);
            HW_SCE_p_func_sub001(0x80000000U, 0x38000882U, 0x00030020U);

            HW_SCE_p_func_sub001(0x00002ca0U, 0x342028c5U, 0x100034c5U);

            HW_SCE_p_func_sub001(0x00000060U, 0x00003444U, 0x0000b4a0U);
            WR1_PROG(REG_94H, 0x00000001U);

            WR1_PROG(REG_94H, 0x00000080U);
        }

        WR1_PROG(REG_94H, 0x00003420U);

        for (jLoop = 0U; jLoop < 32U; jLoop++)
        {
            HW_SCE_p_func_sub001(0x38008c20U, 0x00000001U, 0x00020020U);

            HW_SCE_p_func_sub001(0x00002ce0U, 0x00000060U, 0x0000a4e0U);
            HW_SCE_p_func_sub001(0x00010000U, 0x00000080U, 0x00016821U);
        }
    }

    WR1_PROG(REG_40H, 0x00001200U);
    WAIT_STS(REG_C8H, 6, 0);
    WR1_PROG(REG_D0H, 0x00000000U);
    WR1_PROG(REG_40H, 0x00000400U);

    HW_SCE_p_func_sub001(0x00000800U, 0x0000b420U, 0x00000033U);

    HW_SCE_p_func_sub001(0x342028c1U, 0x2000d011U, 0x0000b4a0U);
    HW_SCE_p_func_sub001(0x00000348U, 0x0000b4c0U, 0x000000b7U);

    HW_SCE_p_func_sub001(0x00003467U, 0x00008c60U, 0x0000ffffU);

    HW_SCE_p_func_sub001(0x34202865U, 0x2000d012U, 0x342028c3U);
    HW_SCE_p_func_sub001(0x2000d012U, 0x001068e7U, 0x342028e5U);
    HW_SCE_p_func_sub001(0x2000d013U, 0x342028c7U, 0x2000d013U);

    WR1_PROG(REG_94H, 0x00002467U);

    static const uint32_t Param_p82_func100_002[] =
    {
        0xb0c2b455U, 0x67a42c02U, 0xb91fb3cbU, 0x117e44d0U,
    };
    HW_SCE_p_func100(Param_p82_func100_002);
    HW_SCE_p_func_sub006(0x38008860U, 0x00000400U, 0x00260000U);

    WR1_PROG(REG_40H, 0x00402000U);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_08H, 0x00020000U);

    HW_SCE_p_func_sub001(0x0000b420U, 0x0000005AU, 0x00000842U);

    HW_SCE_p_func_sub001(0x00000863U, 0x00000884U, 0x0000b4a0U);
    WR1_PROG(REG_94H, 0x00000002U);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        HW_SCE_p_func_sub001(0x010038c4U, 0x34202826U, 0x10005002U);

        HW_SCE_p_func_sub001(0x00002466U, 0x00002c40U, 0x00002485U);
    }

    static const uint32_t Param_p82_func100_003[] =
    {
        0xbef2e50aU, 0x69999e1dU, 0x290ca8c4U, 0xad8c7d17U,
    };
    HW_SCE_p_func100(Param_p82_func100_003);
    HW_SCE_p_func_sub006(0x38008860U, 0x00000100U, 0x00260000U);

    WR1_PROG(REG_40H, 0x00402000U);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_08H, 0x00020000U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);
    WR1_PROG(REG_9CH, 0x80010020U);
    HW_SCE_p_func_sub002(0x03410005U);
    HW_SCE_p_func_sub002(0x0001000dU);

    HW_SCE_p_func_sub006(0x00002c20U, 0x38000c00U, 0x00A60000U);

    static const uint32_t Param_p82_func100_004[] =
    {
        0x3e5c36f5U, 0x7e22cb6eU, 0x625146beU, 0xa98518dbU,
    };
    HW_SCE_p_func100(Param_p82_func100_004);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p82_func102_001[] =
        {
            0xbe37cd78U, 0xf2ebfe39U, 0xb6417257U, 0x614e402cU,
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
            0x9d47a042U, 0xe7c53d1dU, 0xb8d416d4U, 0x2511452cU,
        };
        HW_SCE_p_func100(Param_p82_func100_005);

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c300104U, 0x00000000U);
        WR1_PROG(REG_9CH, 0x80040000U);
        HW_SCE_p_func_sub002(0x03410011U);

        WR1_PROG(REG_D4H, 0x00000600U);
        WR1_PROG(REG_D0H, 0x0e349407U);
        WAIT_STS(REG_E8H, 0, 0);
        WR1_PROG(REG_E4H, 0x00200003U);
        HW_SCE_p_func_sub002(0x00440071U);
        WR1_PROG(REG_D0H, 0x0e340505U);
        HW_SCE_p_func_sub002(0x00440011U);

        WAIT_STS(REG_E8H, 3, 0);
        WR1_PROG(REG_E0H, 0x00000000U);
        WR1_PROG(REG_9CH, 0x80040080U);
        HW_SCE_p_func_sub002(0x03410011U);

        HW_SCE_p_func_sub004(0x000000a1U, 0x080000b4U, 0x00000000U);

        static const uint32_t Param_p82_func100_006[] =
        {
            0x0380c24dU, 0x8960d168U, 0xa4457366U, 0x24fcd105U,
        };
        HW_SCE_p_func100(Param_p82_func100_006);
        HW_SCE_p_func_sub008(0x000003a1U, 0x08000075U);
        WR4_PROG(REG_2CH, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000001U));

        WR1_PROG(REG_D4H, 0x00000100U);
        WR1_PROG(REG_D0H, 0x07338d07U);
        WR1_PROG(REG_9CH, 0x81080000U);
        HW_SCE_p_func_sub002(0x00490021U);

        WR1_PROG(REG_D0H, 0x080000b5U);
        HW_SCE_p_func_sub002(0x00410011U);

        static const uint32_t Param_p82_func100_007[] =
        {
            0x6c62d004U, 0xa627ba76U, 0x44932a89U, 0x7fadbba0U,
        };
        HW_SCE_p_func100(Param_p82_func100_007);
        WR1_PROG(REG_D0H, 0x08000075U);
        HW_SCE_p_func_sub002(0x00410011U);

        HW_SCE_p_func103();
        static const uint32_t Param_p82_func100_008[] =
        {
            0xa48af824U, 0x0bd286a5U, 0xc8fa2f14U, 0x95f3f5b6U,
        };
        HW_SCE_p_func100(Param_p82_func100_008);
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c2000d4U, 0x00000000U);

        static const uint32_t Param_p82_func100_009[] =
        {
            0x85a3279fU, 0x254914e6U, 0x9cf14f75U, 0xaccd6503U,
        };
        HW_SCE_p_func100(Param_p82_func100_009);
        HW_SCE_p_func103();
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

        WR1_PROG(REG_A0H, 0x00030000U);
        WR1_PROG(REG_04H, 0x20000000U);
        WR1_PROG(REG_B0H, 0x00000401U);

        HW_SCE_p_func_sub002(0x00c10009U);
        HW_SCE_p_func_sub002(0x00010009U);

        WR1_PROG(REG_04H, 0x00000000U);
        WR1_PROG(REG_A0H, 0x00030000U);
        WR1_PROG(REG_B0H, 0x000074c0U);
        HW_SCE_p_func_sub002(0x00c00601U);

        WR1_PROG(REG_70H, 0x00008002U);
        WR1_PROG(REG_78H, 0x00000d01U);

        WR1_PROG(REG_70H, 0x00008001U);

        WR1_PROG(REG_78H, 0x00000214U);

        static const uint32_t Param_p82_func102_002[] =
        {
            0x8b8e2f4cU, 0x973198f0U, 0x23fcc132U, 0xa090def0U,
        };
        HW_SCE_p_func102(Param_p82_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
