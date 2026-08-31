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

    HW_SCE_p_func_sub001(0x3420a800U, 0x00000003U, 0x2000b400U, 0x00000002U);

    HW_SCE_p_func070(InData_DomainParam);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00002428U);

    static const uint32_t Param_pf4_func100_001[] =
    {
        0x00a752abU, 0xf0f5288fU, 0x8a3b9176U, 0x7e1e7c9dU,
    };
    HW_SCE_p_func100(Param_pf4_func100_001);
    HW_SCE_p_func103();
    static const uint32_t Param_pf4_func100_002[] =
    {
        0x9eb83c40U, 0x9d66bda4U, 0x9b949086U, 0x2978790eU,
    };
    HW_SCE_p_func100(Param_pf4_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10009U);
    HW_SCE_p_func_sub003(0x00010009U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf4_func100_003[] =
    {
        0xad3018bfU, 0x6dbb4f3bU, 0x68aff275U, 0x15764e37U,
    };
    HW_SCE_p_func100(Param_pf4_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub002(0x000f000aU, 0x00140000U, 0x0404000aU);

    WR1_PROG(REG_B0H, 0x0000143cU);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

    WR1_PROG(REG_B0H, 0x00001419U);
    HW_SCE_p_func_sub003(0x00c00021U);

    HW_SCE_p_func_sub022(0x00000821U, 0x00000863U, 0x000008a5U);

    for (iLoop = 0U; iLoop < 64U; iLoop++)
    {
        HW_SCE_p_func_sub002(0x00140027U, 0x001e0000U, 0x0404000aU);

        WR1_PROG(REG_B0H, 0x0000081aU);
        WR1_PROG(REG_9CH, 0x80020000U);
        HW_SCE_p_func_sub003(0x03430009U);

        HW_SCE_p_func_sub001(0x00000884U, 0x38000c21U, 0x2000d080U, 0x38000c63U);
        WR1_PROG(REG_94H, 0x1000d081U);

        HW_SCE_p_func_sub006(0x38008880U, 0x00000003U, 0x00270000U);

        static const uint32_t Param_pf4_func100_004[] =
        {
            0x89ef237aU, 0x10c33f7aU, 0x5c872477U, 0x6725de56U,
        };
        HW_SCE_p_func100(Param_pf4_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub002(0x0019001eU, 0x004b0000U, 0x04040009U);

            static const uint32_t Param_pf4_func101_001[] =
            {
                0x1c0bb4c2U, 0xe0c7fc45U, 0xd323440eU, 0x84a9dc8cU,
            };
            HW_SCE_p_func101(Param_pf4_func101_001);
        }
        else
        {
            HW_SCE_p_func_sub002(0x0019001eU, 0x00270000U, 0x04040009U);

            static const uint32_t Param_pf4_func101_002[] =
            {
                0x9fdb060aU, 0x04841875U, 0xc2df9691U, 0xf8a89245U,
            };
            HW_SCE_p_func101(Param_pf4_func101_002);
        }

        HW_SCE_p_func_sub002(0x003c002bU, 0x001e0000U, 0x04040007U);

        HW_SCE_p_func_sub002(0x003c0027U, 0x00230000U, 0x04040007U);

        WR1_PROG(REG_B0H, 0x0000081fU);
        WR1_PROG(REG_9CH, 0x80020040U);
        HW_SCE_p_func_sub003(0x03430009U);

        HW_SCE_p_func_sub002(0x0019001eU, 0x002b0000U, 0x04040009U);

        HW_SCE_p_func_sub002(0x001a0023U, 0x00270000U, 0x04040009U);

        WR1_PROG(REG_94H, 0x00002ca0U);

        static const uint32_t Param_pf4_func101_003[] =
        {
            0xca8ebd39U, 0xdcb2865eU, 0xfd743a3aU, 0x7262f493U,
        };
        HW_SCE_p_func101(Param_pf4_func101_003);
    }

    HW_SCE_p_func_sub006(0x380088a0U, 0x00000040U, 0x00270000U);

    WR1_PROG(REG_40H, 0x00402000U);

    HW_SCE_p_func_sub002(0x00140027U, 0x001e0000U, 0x0404000aU);

    WR1_PROG(REG_B0H, 0x0000081aU);
    WR1_PROG(REG_9CH, 0x80020000U);
    HW_SCE_p_func_sub003(0x03430009U);

    HW_SCE_p_func_sub001(0x00000884U, 0x38000c21U, 0x2000d080U, 0x38000c63U);
    WR1_PROG(REG_94H, 0x1000d081U);

    HW_SCE_p_func_sub006(0x38008880U, 0x00000003U, 0x00270000U);

    static const uint32_t Param_pf4_func100_005[] =
    {
        0x033d7fe4U, 0x3c493237U, 0x778f34efU, 0xc080364aU,
    };
    HW_SCE_p_func100(Param_pf4_func100_005);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub002(0x0019001eU, 0x004b0000U, 0x04040009U);

        static const uint32_t Param_pf4_func101_004[] =
        {
            0xd1d9541dU, 0xbf9270d6U, 0xf26ec02dU, 0xd7b8f3dfU,
        };
        HW_SCE_p_func101(Param_pf4_func101_004);
    }
    else
    {
        HW_SCE_p_func_sub002(0x0019001eU, 0x00270000U, 0x04040009U);

        static const uint32_t Param_pf4_func101_005[] =
        {
            0xcdb081f1U, 0xdf07d635U, 0x58f94c4bU, 0xd5702a39U,
        };
        HW_SCE_p_func101(Param_pf4_func101_005);
    }

    HW_SCE_p_func_sub002(0x000f0027U, 0x00320000U, 0x04040009U);

    WR1_PROG(REG_94H, 0x00003406U);

    HW_SCE_p_func071(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pf4_func101_006[] =
    {
        0x2040f769U, 0x9268a0ceU, 0x96433bd1U, 0x7e020a19U,
    };
    HW_SCE_p_func101(Param_pf4_func101_006);
    HW_SCE_p_func088();

    static const uint32_t Param_pf4_func100_006[] =
    {
        0x86aefeb8U, 0xf0fcd8e2U, 0x12019bc0U, 0x7988be5bU,
    };
    HW_SCE_p_func100(Param_pf4_func100_006);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pf4_func102_001[] =
        {
            0xf41c582eU, 0xa0c5d66dU, 0x76632eddU, 0xcc4522c3U,
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

        HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

        static const uint32_t Param_pf4_func100_007[] =
        {
            0x7dae7252U, 0x88b488cfU, 0x08ef9e18U, 0x9015fe13U,
        };
        HW_SCE_p_func100(Param_pf4_func100_007);
        WR1_PROG(REG_40H, 0x00400000U);
        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pf4_func100_008[] =
            {
                0x017d2341U, 0x9e359c95U, 0xd7aceedeU, 0x315cab35U,
            };
            HW_SCE_p_func100(Param_pf4_func100_008);
            HW_SCE_p_func103();
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

            WR1_PROG(REG_9CH, 0x80010000U);
            HW_SCE_p_func_sub003(0x03410005U);
            HW_SCE_p_func_sub003(0x0001000dU);

            WR1_PROG(REG_94H, 0x000034c0U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf4_func101_007[] =
            {
                0xfe2de9b6U, 0xe236c632U, 0xa9fdc761U, 0x90dbabb9U,
            };
            HW_SCE_p_func101(Param_pf4_func101_007);
            HW_SCE_p_func043();

            HW_SCE_p_func074();

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf4_func101_008[] =
            {
                0x3e54b992U, 0xc29e0fc1U, 0x711525c7U, 0xc5e2f3fdU,
            };
            HW_SCE_p_func101(Param_pf4_func101_008);
            HW_SCE_p_func044();

            static const uint32_t Param_pf4_func100_009[] =
            {
                0x535afdf0U, 0xc0485a79U, 0x9cca0cabU, 0x74abc3e6U,
            };
            HW_SCE_p_func100(Param_pf4_func100_009);
            WR1_PROG(REG_B0H, 0x00001832U);

            WR1_PROG(REG_D4H, 0x40000100U);
            WR1_PROG(REG_D0H, 0xe7009d07U);
            HW_SCE_p_func_sub003(0x00430021U);

            WR1_PROG(REG_08H, 0x00001022U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[5]);

            static const uint32_t Param_pf4_func100_010[] =
            {
                0xce43aa4eU, 0x0f2aad99U, 0xec2fd2b1U, 0xc385350aU,
            };
            HW_SCE_p_func100(Param_pf4_func100_010);
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x09108105U);
            HW_SCE_p_func_sub003(0x00410011U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[9]);

            static const uint32_t Param_pf4_func100_011[] =
            {
                0xeb5a3e85U, 0x644724b3U, 0x13cf19bdU, 0xb7a4f2c4U,
            };
            HW_SCE_p_func100(Param_pf4_func100_011);
            HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
            RD1_ADDR(REG_2CH, &OutData_PrivKeyIndex[0]);

            static const uint32_t Param_pf4_func101_009[] =
            {
                0x3bf27534U, 0x90a16e8bU, 0x5ba270abU, 0x20f4004cU,
            };
            HW_SCE_p_func101(Param_pf4_func101_009);
        }
        else
        {
            static const uint32_t Param_pf4_func100_012[] =
            {
                0xdd8756daU, 0x2c719920U, 0x8e1ab0e1U, 0x71ee1666U,
            };
            HW_SCE_p_func100(Param_pf4_func100_012);
            HW_SCE_p_func_sub015(0x00001832U, 0x00006022U);
            RD8_ADDR(REG_2CH, &OutData_PrivKey[0]);

            static const uint32_t Param_pf4_func101_010[] =
            {
                0xdba1bcf3U, 0x1bf0e542U, 0xec630723U, 0x3e0ad419U,
            };
            HW_SCE_p_func101(Param_pf4_func101_010);
        }

        static const uint32_t Param_pf4_func100_013[] =
        {
            0xdd64bf17U, 0x751d88adU, 0x2745e66bU, 0xbcaee752U,
        };
        HW_SCE_p_func100(Param_pf4_func100_013);
        HW_SCE_p_func_sub015(0x00001828U, 0x00006022U);
        RD8_ADDR(REG_2CH, &OutData_PubKey[0]);

        static const uint32_t Param_pf4_func100_014[] =
        {
            0x672f8ad1U, 0x3d91acaaU, 0x33a1baedU, 0x93b8aa1fU,
        };
        HW_SCE_p_func100(Param_pf4_func100_014);
        HW_SCE_p_func_sub015(0x0000182dU, 0x00006022U);
        RD8_ADDR(REG_2CH, &OutData_PubKey[8]);

        static const uint32_t Param_pf4_func102_002[] =
        {
            0x1e78fdb5U, 0xc3bb896cU, 0x2a3bbb1dU, 0x0c70ca6eU,
        };
        HW_SCE_p_func102(Param_pf4_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
