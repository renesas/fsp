/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub (const uint32_t InData_KeyMode[],
                                               const uint32_t InData_CurveType[],
                                               const uint32_t InData_DomainParam[],
                                               uint32_t       OutData_PubKey[],
                                               uint32_t       OutData_PrivKeyIndex[],
                                               uint32_t       OutData_PrivKey[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f40001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x3420a800U, 0x00000003U, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    HW_SCE_p_func070_r1(InData_DomainParam);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00002428U);

    static const uint32_t Param_pf4_func100_001[] =
    {
        0x095b5341U, 0x00d38bdfU, 0x159a754fU, 0xf75398c2U,
    };
    HW_SCE_p_func100(Param_pf4_func100_001);
    HW_SCE_p_func103();
    static const uint32_t Param_pf4_func100_002[] =
    {
        0x1aca66c0U, 0x6e7e5f9cU, 0x89697765U, 0x047eb159U,
    };
    HW_SCE_p_func100(Param_pf4_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub002(0x00c10009U);
    HW_SCE_p_func_sub002(0x00010009U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf4_func100_003[] =
    {
        0xeb3e3707U, 0x9acec535U, 0x434bd9edU, 0x3a9b8d91U,
    };
    HW_SCE_p_func100(Param_pf4_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub002(0x00c10011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub002(0x00c10011U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    HW_SCE_p_func_sub002(0x00c0001dU);
    HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub003(0x000f000aU, 0x00140000U, 0x0404000aU);

    WR1_PROG(REG_B0H, 0x0000143cU);
    HW_SCE_p_func_sub002(0x00c0001dU);
    HW_SCE_p_func_sub011(0x000000a5U, 0x00000002U);

    WR1_PROG(REG_B0H, 0x00001419U);
    HW_SCE_p_func_sub002(0x00c00021U);

    HW_SCE_p_func_sub001(0x00000821U, 0x00000863U, 0x000008a5U);

    for (iLoop = 0U; iLoop < 64U; iLoop++)
    {
        HW_SCE_p_func_sub003(0x00140027U, 0x001e0000U, 0x0404000aU);

        WR1_PROG(REG_B0H, 0x0000081aU);
        WR1_PROG(REG_9CH, 0x80020000U);
        HW_SCE_p_func_sub002(0x03430009U);

        HW_SCE_p_func_sub001(0x00000884U, 0x38000c21U, 0x2000d080U);

        HW_SCE_p_func_sub001(0x38000c63U, 0x1000d081U, 0x38008880U);
        HW_SCE_p_func_sub009(0x00000003U, 0x00260000U);

        static const uint32_t Param_pf4_func100_004[] =
        {
            0xf162ada1U, 0x32395b22U, 0x6b24049bU, 0x566dd424U,
        };
        HW_SCE_p_func100(Param_pf4_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub003(0x0019001eU, 0x004b0000U, 0x04040009U);

            static const uint32_t Param_pf4_func101_001[] =
            {
                0xf6795a8cU, 0x06bb4188U, 0x987ee520U, 0x94d06473U,
            };
            HW_SCE_p_func101(Param_pf4_func101_001);
        }
        else
        {
            HW_SCE_p_func_sub003(0x0019001eU, 0x00270000U, 0x04040009U);

            static const uint32_t Param_pf4_func101_002[] =
            {
                0xea5dcde1U, 0x67607120U, 0xe0686590U, 0x6f5bb77fU,
            };
            HW_SCE_p_func101(Param_pf4_func101_002);
        }

        HW_SCE_p_func_sub003(0x003c002bU, 0x001e0000U, 0x04040007U);

        HW_SCE_p_func_sub003(0x003c0027U, 0x00230000U, 0x04040007U);

        WR1_PROG(REG_B0H, 0x0000081fU);
        WR1_PROG(REG_9CH, 0x80020040U);
        HW_SCE_p_func_sub002(0x03430009U);

        HW_SCE_p_func_sub003(0x0019001eU, 0x002b0000U, 0x04040009U);

        HW_SCE_p_func_sub003(0x001a0023U, 0x00270000U, 0x04040009U);

        WR1_PROG(REG_94H, 0x00002ca0U);

        static const uint32_t Param_pf4_func101_003[] =
        {
            0x8f1f10a1U, 0x08e13779U, 0x2a52e3cdU, 0x6497f3f1U,
        };
        HW_SCE_p_func101(Param_pf4_func101_003);
    }

    HW_SCE_p_func_sub006(0x380088a0U, 0x00000040U, 0x00260000U);

    WR1_PROG(REG_40H, 0x00402000U);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub003(0x00140027U, 0x001e0000U, 0x0404000aU);

    WR1_PROG(REG_B0H, 0x0000081aU);
    WR1_PROG(REG_9CH, 0x80020000U);
    HW_SCE_p_func_sub002(0x03430009U);

    HW_SCE_p_func_sub001(0x00000884U, 0x38000c21U, 0x2000d080U);

    HW_SCE_p_func_sub001(0x38000c63U, 0x1000d081U, 0x38008880U);
    HW_SCE_p_func_sub009(0x00000003U, 0x00260000U);

    static const uint32_t Param_pf4_func100_005[] =
    {
        0x54f77d72U, 0x03baed44U, 0x7c8a967fU, 0x94e59fddU,
    };
    HW_SCE_p_func100(Param_pf4_func100_005);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub003(0x0019001eU, 0x004b0000U, 0x04040009U);

        static const uint32_t Param_pf4_func101_004[] =
        {
            0x74e79011U, 0x5845bf78U, 0x6ef80091U, 0x2d4db133U,
        };
        HW_SCE_p_func101(Param_pf4_func101_004);
    }
    else
    {
        HW_SCE_p_func_sub003(0x0019001eU, 0x00270000U, 0x04040009U);

        static const uint32_t Param_pf4_func101_005[] =
        {
            0xf159175dU, 0xab9a327cU, 0x8c3b1f34U, 0xbb476ff8U,
        };
        HW_SCE_p_func101(Param_pf4_func101_005);
    }

    HW_SCE_p_func_sub003(0x000f0027U, 0x00320000U, 0x04040009U);

    WR1_PROG(REG_94H, 0x00003406U);

    HW_SCE_p_func071_r1(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pf4_func101_006[] =
    {
        0xaee7665dU, 0xdaf92cd8U, 0xb36f75ebU, 0xa7b10b10U,
    };
    HW_SCE_p_func101(Param_pf4_func101_006);
    HW_SCE_p_func088();

    static const uint32_t Param_pf4_func100_006[] =
    {
        0xcb83c991U, 0xd0e8b383U, 0xa9aa384cU, 0xfce6e1a7U,
    };
    HW_SCE_p_func100(Param_pf4_func100_006);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pf4_func102_001[] =
        {
            0xf8b93f4bU, 0xf90039dcU, 0x82807fd8U, 0xae8f365cU,
        };
        HW_SCE_p_func102(Param_pf4_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
        WR1_PROG(REG_2CH, InData_KeyMode[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub009(0x38000c00U, 0x00260000U);

        static const uint32_t Param_pf4_func100_007[] =
        {
            0x17e3b02bU, 0xc25d4013U, 0x2b23b657U, 0x1f764db1U,
        };
        HW_SCE_p_func100(Param_pf4_func100_007);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);
        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pf4_func100_008[] =
            {
                0xc3e968a1U, 0xa0e12941U, 0x30a4b25eU, 0x674fcc09U,
            };
            HW_SCE_p_func100(Param_pf4_func100_008);
            HW_SCE_p_func103();
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

            WR1_PROG(REG_9CH, 0x80010000U);
            HW_SCE_p_func_sub002(0x03410005U);
            HW_SCE_p_func_sub002(0x0001000dU);

            WR1_PROG(REG_94H, 0x000034c0U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf4_func101_007[] =
            {
                0x291a0ca3U, 0x28a82454U, 0x476b77b1U, 0xf6c53132U,
            };
            HW_SCE_p_func101(Param_pf4_func101_007);
            HW_SCE_p_func043_r1();

            HW_SCE_p_func074();

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf4_func101_008[] =
            {
                0xfb965186U, 0xfb4ae889U, 0x7a222689U, 0xd1346d90U,
            };
            HW_SCE_p_func101(Param_pf4_func101_008);
            HW_SCE_p_func044();

            static const uint32_t Param_pf4_func100_009[] =
            {
                0x2b316d31U, 0xd922edaaU, 0x79ce9339U, 0x46be6298U,
            };
            HW_SCE_p_func100(Param_pf4_func100_009);
            WR1_PROG(REG_B0H, 0x00001832U);

            WR1_PROG(REG_D4H, 0x40000100U);
            WR1_PROG(REG_D0H, 0xe7009d07U);
            HW_SCE_p_func_sub002(0x00430021U);

            WR1_PROG(REG_08H, 0x00001022U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[5]);

            static const uint32_t Param_pf4_func100_010[] =
            {
                0xce5dbb96U, 0xae78b31cU, 0x1cf6e125U, 0x835302f5U,
            };
            HW_SCE_p_func100(Param_pf4_func100_010);
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x09108105U);
            HW_SCE_p_func_sub002(0x00410011U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[9]);

            static const uint32_t Param_pf4_func100_011[] =
            {
                0x4b4722e5U, 0x76edacf2U, 0xbba4e3d1U, 0xa5d9f0c8U,
            };
            HW_SCE_p_func100(Param_pf4_func100_011);
            HW_SCE_p_func_sub012(0x81010000U, 0x00005006U);
            RD1_ADDR(REG_2CH, &OutData_PrivKeyIndex[0]);

            static const uint32_t Param_pf4_func101_009[] =
            {
                0x77ad81deU, 0x3c1b16b5U, 0xe263e21fU, 0x4ba1346fU,
            };
            HW_SCE_p_func101(Param_pf4_func101_009);
        }
        else
        {
            static const uint32_t Param_pf4_func100_012[] =
            {
                0x2c009193U, 0x29108391U, 0x139489cdU, 0x1e5f9a02U,
            };
            HW_SCE_p_func100(Param_pf4_func100_012);
            WR1_PROG(REG_B0H, 0x00001832U);
            WR1_PROG(REG_08H, 0x00006022U);
            WAIT_STS(REG_08H, 30, 1);
            RD8_ADDR(REG_2CH, &OutData_PrivKey[0]);

            static const uint32_t Param_pf4_func101_010[] =
            {
                0xf81dc7f5U, 0x50629fbfU, 0xbcab0ea1U, 0x01fe5642U,
            };
            HW_SCE_p_func101(Param_pf4_func101_010);
        }

        static const uint32_t Param_pf4_func100_013[] =
        {
            0xc7644ce3U, 0x97c3c8cbU, 0x587698bbU, 0xe12f901dU,
        };
        HW_SCE_p_func100(Param_pf4_func100_013);
        WR1_PROG(REG_B0H, 0x00001828U);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_PubKey[0]);

        static const uint32_t Param_pf4_func100_014[] =
        {
            0xcfb6d08aU, 0xd71b381eU, 0x2a5ccc11U, 0x0575dc32U,
        };
        HW_SCE_p_func100(Param_pf4_func100_014);
        WR1_PROG(REG_B0H, 0x0000182dU);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_PubKey[8]);

        static const uint32_t Param_pf4_func102_002[] =
        {
            0x12ecc7b7U, 0xf2a39a12U, 0xfb4787c5U, 0x096427afU,
        };
        HW_SCE_p_func102(Param_pf4_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
