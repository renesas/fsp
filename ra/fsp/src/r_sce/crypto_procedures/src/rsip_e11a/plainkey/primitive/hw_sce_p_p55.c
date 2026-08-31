/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateRandomKeyIndexSub (const uint32_t InData_Cmd[], uint32_t OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00550001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func049(InData_Cmd);

    HW_SCE_p_func_sub001(0x00003464U, 0x3420a880U, 0x00000020U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00A60000U);

    HW_SCE_p_func_sub001(0x00000842U, 0x0000b440U, 0x0C0000A0U);

    HW_SCE_p_func_sub009(0x38005844U, 0x00260000U);

    static const uint32_t Param_p55_func100_001[] =
    {
        0xc808143dU, 0x7dd0b80cU, 0x31fe2088U, 0xb4d499d9U,
    };
    HW_SCE_p_func100(Param_p55_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p55_func102_001[] =
        {
            0x3c911898U, 0x7877f647U, 0x25a226e3U, 0x24d257a1U,
        };
        HW_SCE_p_func102(Param_p55_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p55_func100_002[] =
        {
            0xc21bdda0U, 0xba9632b2U, 0x5765ac7aU, 0xfa975376U,
        };
        HW_SCE_p_func100(Param_p55_func100_002);

        HW_SCE_p_func_sub001(0x000008a5U, 0x38008860U, 0x00000005U);
        HW_SCE_p_func_sub001(0x1000b420U, 0x00000004U, 0x38008860U);
        HW_SCE_p_func_sub001(0x00000007U, 0x1000b420U, 0x00000008U);

        HW_SCE_p_func_sub001(0x38008860U, 0x0000001aU, 0x1000b420U);
        HW_SCE_p_func_sub001(0x00000004U, 0x1000d0a0U, 0x38008860U);
        HW_SCE_p_func_sub001(0x0000001bU, 0x1000b420U, 0x00000008U);

        HW_SCE_p_func103();
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

        WR1_PROG(REG_9CH, 0x80010000U);
        HW_SCE_p_func_sub002(0x03410005U);
        HW_SCE_p_func_sub002(0x0001000dU);

        WR1_PROG(REG_94H, 0x000034c0U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000055U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p55_func101_001[] =
        {
            0x80baf62fU, 0x6c7fa1d9U, 0xdacecbcfU, 0x37e41488U,
        };
        HW_SCE_p_func101(Param_p55_func101_001);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_94H, 0x000034c3U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000055U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p55_func101_002[] =
        {
            0x889b0072U, 0x37d9b222U, 0xe735756aU, 0xb4c0ab62U,
        };
        HW_SCE_p_func101(Param_p55_func101_002);
        HW_SCE_p_func044();

        static const uint32_t Param_p55_func100_003[] =
        {
            0x36558bb9U, 0x3454815fU, 0xc3c00992U, 0x2bfe3c9dU,
        };
        HW_SCE_p_func100(Param_p55_func100_003);
        HW_SCE_p_func_sub004(0x000001a1U, 0x08000044U, 0x00000000U);

        HW_SCE_p_func_sub010(0x08000054U, 0x00000000U);

        HW_SCE_p_func_sub012(0x81010020U, 0x00005006U);
        RD1_ADDR(REG_2CH, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            static const uint32_t Param_p55_func100_004[] =
            {
                0x374d2ef3U, 0x9be6d72fU, 0x179610afU, 0xbe869419U,
            };
            HW_SCE_p_func100(Param_p55_func100_004);
            HW_SCE_p_func103();
            static const uint32_t Param_p55_func100_005[] =
            {
                0xdeb94170U, 0xf938b4adU, 0xda8a3075U, 0x28587287U,
            };
            HW_SCE_p_func100(Param_p55_func100_005);
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0xe7008d45U);
            HW_SCE_p_func_sub002(0x00410011U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_KeyIndex[1 + iLoop]);

            WR1_PROG(REG_94H, 0x0000a820U);
            WR1_PROG(REG_94H, 0x00000004U);

            static const uint32_t Param_p55_func101_003[] =
            {
                0xe52a2c75U, 0x9ed90fe8U, 0x00496772U, 0x6f5f4a33U,
            };
            HW_SCE_p_func101(Param_p55_func101_003);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func_sub015(0x00007c01U, 0x00602000U);

        HW_SCE_p_func_sub006(0x380088a0U, 0x00000001U, 0x00260000U);

        static const uint32_t Param_p55_func100_006[] =
        {
            0x58795bb0U, 0xebed528cU, 0x4a7ebd4bU, 0xd2a468faU,
        };
        HW_SCE_p_func100(Param_p55_func100_006);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p55_func100_007[] =
            {
                0x568aef70U, 0x8a36ef5cU, 0xa896cdceU, 0xfd293eceU,
            };
            HW_SCE_p_func100(Param_p55_func100_007);
            HW_SCE_p_func103();
            static const uint32_t Param_p55_func100_008[] =
            {
                0xd5006185U, 0x7b91ca30U, 0xb0acd9f9U, 0xed2b6c13U,
            };
            HW_SCE_p_func100(Param_p55_func100_008);
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0xe7008d45U);
            HW_SCE_p_func_sub002(0x0041000dU);
            HW_SCE_p_func_sub002(0x00010005U);
            HW_SCE_p_func_sub002(0x00400005U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_KeyIndex[1 + iLoop]);

            iLoop = iLoop + 4;

            static const uint32_t Param_p55_func101_004[] =
            {
                0xd70704d2U, 0xa54bd5e3U, 0xb8ba3d30U, 0xdb211d69U,
            };
            HW_SCE_p_func101(Param_p55_func101_004);
        }

        static const uint32_t Param_p55_func100_009[] =
        {
            0xed25b118U, 0xc37d6747U, 0x79e58367U, 0x571f4f6eU,
        };
        HW_SCE_p_func100(Param_p55_func100_009);
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x09108105U);
        HW_SCE_p_func_sub002(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_KeyIndex[1 + iLoop]);

        static const uint32_t Param_p55_func100_010[] =
        {
            0x8def10b0U, 0xb7435d54U, 0x4f1167bfU, 0x088980e6U,
        };
        HW_SCE_p_func100(Param_p55_func100_010);
        HW_SCE_p_func_sub012(0x81010000U, 0x00005006U);
        RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

        static const uint32_t Param_p55_func102_002[] =
        {
            0x2b89a917U, 0x3924c9abU, 0x581fe1b3U, 0xcdc4bfdbU,
        };
        HW_SCE_p_func102(Param_p55_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
