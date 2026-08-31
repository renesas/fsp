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

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00000202U);
    WR1_PROG(REG_108H, 0x00000000U);

    HW_SCE_p_func_sub012(0x00000052U, 0x00093b8cU, 0x01c7ba56U);

    HW_SCE_p_func_sub012(0x00000052U, 0x00070804U, 0x00000000U);

    HW_SCE_p_func_sub022(0x3000a820U, 0x00000003U, 0x00010020U, 0x00000821U);
    WR1_PROG(REG_ECH, 0x00000080U);

    WAIT_STS(REG_64H, 11, 0);
    WR1_PROG(REG_64H, 0x00000008U);
    WAIT_STS(REG_64H, 11, 0);
    WR1_PROG(REG_64H, 0x00002008U);

    HW_SCE_p_func_sub022(0x00000863U, 0x00000884U, 0x000008a5U, 0x0000b4c0U);
    HW_SCE_p_func_sub022(0x00000013U, 0x0000b4e0U, 0x00000348U, 0x0000b500U);
    WR1_PROG(REG_ECH, 0x000000b7U);

    for (jLoop = 0U; jLoop < 32U; jLoop++)
    {
        static const uint32_t Param_p02_func100_001[] =
        {
            0x6c71e264U, 0x905d3c7cU, 0x2a4c435eU, 0xbdb4777bU,
        };
        HW_SCE_p_func100(Param_p02_func100_001);
        WR1_PROG(REG_ECH, 0x00007c01U);
        WR1_PROG(REG_1CH, 0x00600000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
        {
            WAIT_STS(REG_64H, 11, 0);
            WR1_PROG(REG_64H, 0x0020901cU);

            static const uint32_t Param_p02_func101_001[] =
            {
                0x4ed68504U, 0x34692cfcU, 0xa224db89U, 0x08268dfbU,
            };
            HW_SCE_p_func101(Param_p02_func101_001);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
        {
            WAIT_STS(REG_64H, 11, 0);
            WR1_PROG(REG_64H, 0x0020901eU);

            static const uint32_t Param_p02_func101_002[] =
            {
                0x7de6d907U, 0x8a506eeaU, 0x951e9155U, 0x15bb7447U,
            };
            HW_SCE_p_func101(Param_p02_func101_002);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
        {
            WAIT_STS(REG_64H, 11, 0);
            WR1_PROG(REG_64H, 0x0020901dU);

            static const uint32_t Param_p02_func101_003[] =
            {
                0x6f12da0dU, 0xb83a404aU, 0x1332d5efU, 0x94827cceU,
            };
            HW_SCE_p_func101(Param_p02_func101_003);
        }

        WR1_PROG(REG_C4H, 0x41001e5eU);
        WR1_PROG(REG_00H, 0x80002401U);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_1CH, 0x00001200U);
        WAIT_STS(REG_00H, 30, 0);
        WR1_PROG(REG_00H, 0x00000001U);
        WR1_PROG(REG_C4H, 0x00000000U);

        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x0010B008U);

        WR1_PROG(REG_ECH, 0x00000800U);
        HW_SCE_p_func_sub010(0x80900000U, 0x00008443U);

        HW_SCE_p_func_sub022(0x000038a0U, 0x00003405U, 0x00002804U, 0x342028e0U);
        HW_SCE_p_func_sub022(0x10005066U, 0x34202808U, 0x10005066U, 0x00003485U);

        static const uint32_t Param_p02_func101_004[] =
        {
            0xca3b3ea4U, 0x71236437U, 0x3e0d1f89U, 0x58d2df4bU,
        };
        HW_SCE_p_func101(Param_p02_func101_004);
    }

    HW_SCE_p_func_sub022(0x0000b4e0U, 0x00000B50U, 0x00000842U, 0x000008c6U);

    HW_SCE_p_func_sub022(0x0000b480U, 0x00000004U, 0x0000b4a0U, 0x00000002U);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        HW_SCE_p_func_sub022(0x01003804U, 0x342028e0U, 0x10005066U, 0x00002440U);

        WR1_PROG(REG_ECH, 0x00002cc0U);

        WR1_PROG(REG_ECH, 0x00002485U);
    }

    HW_SCE_p_func_sub007(0x00002c20U, 0x38008840U, 0x00002000U, 0x00260000U);

    WR1_PROG(REG_1CH, 0x00402000U);

    HW_SCE_p_func_sub022(0x0000b4e0U, 0x00000033U, 0x0000b480U, 0x0000003cU);

    HW_SCE_p_func_sub022(0x01003804U, 0x342028e0U, 0x10005066U, 0x00002cc0U);

    HW_SCE_p_func_sub022(0x0000b480U, 0x0000003eU, 0x01003804U, 0x342028e0U);
    HW_SCE_p_func_sub007(0x10005066U, 0x38008860U, 0x00000000U, 0x00A60000U);

    static const uint32_t Param_p02_func100_002[] =
    {
        0x25d4d69bU, 0x231245f9U, 0x52a77bdaU, 0xba7e5bc8U,
    };
    HW_SCE_p_func100(Param_p02_func100_002);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p02_func102_001[] =
        {
            0x7d948770U, 0x3e084379U, 0xc51558caU, 0x81647cd1U,
        };
        HW_SCE_p_func102(Param_p02_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_RETRY;
    }
    else
    {
        HW_SCE_p_func_sub022(0x0000b7c0U, 0x000001f0U, 0x0000b7e0U, 0x2e24c972U);

        WR1_PROG(REG_ECH, 0x00003ffeU);

        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x0000001cU);

        HW_SCE_p_func_sub012(0x00000052U, 0x01000cc4U, 0x00000000U);
        HW_SCE_p_func_sub010(0x80040000U, 0x00008213U);

        HW_SCE_p_func_sub013(0x41001eddU, 0x00002413U);

        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000000U);
        HW_SCE_p_func_sub010(0x80040080U, 0x00008213U);

        static const uint32_t Param_p02_func100_003[] =
        {
            0x8d0bfb78U, 0xe6d5ba61U, 0xf547a492U, 0x401bf606U,
        };
        HW_SCE_p_func100(Param_p02_func100_003);
        HW_SCE_p_func_sub012(0x00000052U, 0x000b0804U, 0x00000000U);

        WR1_PROG(REG_104H, 0x00000352U);
        WR1_PROG(REG_C4H, 0x00070805U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000001U));

        static const uint32_t Param_p02_func100_004[] =
        {
            0xbffc56f3U, 0x242ee8afU, 0xd6f5a7f5U, 0xdc95f65eU,
        };
        HW_SCE_p_func100(Param_p02_func100_004);
        WR1_PROG(REG_D0H, 0x00000100U);
        WR1_PROG(REG_C4H, 0x0100b7f7U);
        HW_SCE_p_func_sub010(0x81080000U, 0x00002823U);

        HW_SCE_p_func_sub013(0x000b0805U, 0x00002213U);

        HW_SCE_p_func_sub013(0x00070805U, 0x00002213U);

        static const uint32_t Param_p02_func100_005[] =
        {
            0x48de5befU, 0x8b1403c2U, 0x1e08e8feU, 0xa1a7a87cU,
        };
        HW_SCE_p_func100(Param_p02_func100_005);
        HW_SCE_p_func103();
        static const uint32_t Param_p02_func100_006[] =
        {
            0x3cb5779eU, 0xbab174adU, 0xf71b0f88U, 0xbe7d89cdU,
        };
        HW_SCE_p_func100(Param_p02_func100_006);
        HW_SCE_p_func_sub012(0x00000052U, 0x010d0c04U, 0x00000000U);

        static const uint32_t Param_p02_func100_007[] =
        {
            0x95ad7aabU, 0x2279e4ddU, 0x55fb6a92U, 0x431d725eU,
        };
        HW_SCE_p_func100(Param_p02_func100_007);
        HW_SCE_p_func103();
        static const uint32_t Param_p02_func100_008[] =
        {
            0x70782e85U, 0x7706b601U, 0x736af867U, 0x38a12bdfU,
        };
        HW_SCE_p_func100(Param_p02_func100_008);
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_RAM[20]);

        WR1_PROG(REG_13CH, 0x00000202U);

        static const uint32_t Param_p02_func102_002[] =
        {
            0x75fe6fe1U, 0x9ab95ef0U, 0xec59c801U, 0x84cb693aU,
        };
        HW_SCE_p_func102(Param_p02_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
