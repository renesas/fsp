/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSub (const uint32_t InData_KeyMode[],
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

    WR1_PROG(REG_70H, 0x00f90001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func027(InData_DomainParam);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x0000a438U);

    static const uint32_t Param_pf9_func100_001[] =
    {
        0x3ab21592U, 0x89ea5a8aU, 0x04c9811cU, 0x6fd8fd7fU,
    };
    HW_SCE_p_func100(Param_pf9_func100_001);
    HW_SCE_p_func103();
    static const uint32_t Param_pf9_func100_002[] =
    {
        0xdec4fd01U, 0x387c123cU, 0xdc7a45cfU, 0x79fe172eU,
    };
    HW_SCE_p_func100(Param_pf9_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10009U);
    HW_SCE_p_func_sub003(0x00010009U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf9_func100_003[] =
    {
        0x0b687d14U, 0x9ba5feb6U, 0x5eb9244bU, 0xa52d6f94U,
    };
    HW_SCE_p_func100(Param_pf9_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf9_func100_004[] =
    {
        0xdcfc1f38U, 0xc8ea72eeU, 0x8a3e28b1U, 0xefcc3c5eU,
    };
    HW_SCE_p_func100(Param_pf9_func100_004);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    WR1_PROG(REG_B0H, 0x00009415U);
    HW_SCE_p_func_sub003(0x00c0002dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub002(0x0015000eU, 0x001c0000U, 0x0606000aU);

    WR1_PROG(REG_B0H, 0x00009454U);
    HW_SCE_p_func_sub003(0x00c0002dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

    WR1_PROG(REG_B0H, 0x00009423U);
    HW_SCE_p_func_sub003(0x00c00031U);

    HW_SCE_p_func_sub022(0x00000821U, 0x00000863U, 0x000008a5U);

    for (iLoop = 0U; iLoop < 64U; iLoop++)
    {
        HW_SCE_p_func_sub002(0x001c0037U, 0x002a0000U, 0x0606000aU);

        WR1_PROG(REG_B0H, 0x00000824U);
        WR1_PROG(REG_9CH, 0x80020000U);
        HW_SCE_p_func_sub003(0x03430009U);

        HW_SCE_p_func_sub001(0x00000884U, 0x38000c21U, 0x2000d080U, 0x38000c63U);
        WR1_PROG(REG_94H, 0x1000d081U);

        HW_SCE_p_func_sub006(0x38008880U, 0x00000003U, 0x00270000U);

        static const uint32_t Param_pf9_func100_005[] =
        {
            0x95e381c4U, 0xc3ab3ae9U, 0x3751bfe6U, 0x938ca07cU,
        };
        HW_SCE_p_func100(Param_pf9_func100_005);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub002(0x0023002aU, 0x00690000U, 0x06060009U);

            static const uint32_t Param_pf9_func101_001[] =
            {
                0xe8a90266U, 0x15e364d3U, 0xc707d2c5U, 0xa802d4feU,
            };
            HW_SCE_p_func101(Param_pf9_func101_001);
        }
        else
        {
            HW_SCE_p_func_sub002(0x0023002aU, 0x00370000U, 0x06060009U);

            static const uint32_t Param_pf9_func101_002[] =
            {
                0xa229f442U, 0x5e237467U, 0xb1cd0cf1U, 0xd9f71c5cU,
            };
            HW_SCE_p_func101(Param_pf9_func101_002);
        }

        HW_SCE_p_func_sub002(0x0054003dU, 0x002a0000U, 0x06060007U);

        HW_SCE_p_func_sub002(0x00540037U, 0x00310000U, 0x06060007U);

        WR1_PROG(REG_B0H, 0x0000082bU);
        WR1_PROG(REG_9CH, 0x80020040U);
        HW_SCE_p_func_sub003(0x03430009U);

        HW_SCE_p_func_sub002(0x0023002aU, 0x003d0000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x00240031U, 0x00370000U, 0x06060009U);

        WR1_PROG(REG_94H, 0x00002ca0U);

        static const uint32_t Param_pf9_func101_003[] =
        {
            0xfd59e198U, 0x117fc47fU, 0x873127efU, 0x0790bce3U,
        };
        HW_SCE_p_func101(Param_pf9_func101_003);
    }

    HW_SCE_p_func_sub006(0x380088a0U, 0x00000040U, 0x00270000U);

    WR1_PROG(REG_40H, 0x00402000U);

    HW_SCE_p_func_sub002(0x001c0037U, 0x002a0000U, 0x0606000aU);

    WR1_PROG(REG_B0H, 0x00000824U);
    WR1_PROG(REG_9CH, 0x80020000U);
    HW_SCE_p_func_sub003(0x03430009U);

    HW_SCE_p_func_sub001(0x00000884U, 0x38000c21U, 0x2000d080U, 0x38000c63U);
    WR1_PROG(REG_94H, 0x1000d081U);

    HW_SCE_p_func_sub006(0x38008880U, 0x00000003U, 0x00270000U);

    static const uint32_t Param_pf9_func100_006[] =
    {
        0x1301f3c1U, 0x34685f9fU, 0x38a2fd9eU, 0xa772a846U,
    };
    HW_SCE_p_func100(Param_pf9_func100_006);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub002(0x0023002aU, 0x00690000U, 0x06060009U);

        static const uint32_t Param_pf9_func101_004[] =
        {
            0xd9111ba3U, 0xe2035d9cU, 0xa1dd0010U, 0x1cec9362U,
        };
        HW_SCE_p_func101(Param_pf9_func101_004);
    }
    else
    {
        HW_SCE_p_func_sub002(0x0023002aU, 0x00370000U, 0x06060009U);

        static const uint32_t Param_pf9_func101_005[] =
        {
            0xc6c29451U, 0xbd9209eaU, 0x8f9334a4U, 0xe1f066a5U,
        };
        HW_SCE_p_func101(Param_pf9_func101_005);
    }

    HW_SCE_p_func_sub002(0x00150037U, 0x00460000U, 0x06060009U);

    WR1_PROG(REG_94H, 0x00003406U);

    HW_SCE_p_func028(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f9U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pf9_func101_006[] =
    {
        0xd01e49d4U, 0xb8c007ebU, 0x2a5a0cfeU, 0xe187e3f4U,
    };
    HW_SCE_p_func101(Param_pf9_func101_006);
    HW_SCE_p_func089();

    static const uint32_t Param_pf9_func100_007[] =
    {
        0xb9b8b634U, 0x024ff6aaU, 0xdcb4c523U, 0xef9b2d0fU,
    };
    HW_SCE_p_func100(Param_pf9_func100_007);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pf9_func102_001[] =
        {
            0xebb41341U, 0x61d381b4U, 0x85e33593U, 0xfb11ebb8U,
        };
        HW_SCE_p_func102(Param_pf9_func102_001);
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

        static const uint32_t Param_pf9_func100_008[] =
        {
            0xb4057983U, 0x4cad7131U, 0xf16ca119U, 0x02c5f836U,
        };
        HW_SCE_p_func100(Param_pf9_func100_008);
        WR1_PROG(REG_40H, 0x00400000U);
        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pf9_func100_009[] =
            {
                0x86f32ddeU, 0x957a1851U, 0x988e9459U, 0x501bd1c9U,
            };
            HW_SCE_p_func100(Param_pf9_func100_009);
            HW_SCE_p_func103();
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

            WR1_PROG(REG_9CH, 0x80010000U);
            HW_SCE_p_func_sub003(0x03410005U);
            HW_SCE_p_func_sub003(0x0001000dU);

            WR1_PROG(REG_94H, 0x000034c0U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f9U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf9_func101_007[] =
            {
                0x7ae9f47eU, 0xdf27d25cU, 0x4172abc2U, 0x90bcea7bU,
            };
            HW_SCE_p_func101(Param_pf9_func101_007);
            HW_SCE_p_func043();

            HW_SCE_p_func076();

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f9U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf9_func101_008[] =
            {
                0x8c22f426U, 0x527cb8edU, 0xd824498bU, 0xaaed2734U,
            };
            HW_SCE_p_func101(Param_pf9_func101_008);
            HW_SCE_p_func044();

            static const uint32_t Param_pf9_func100_010[] =
            {
                0x990ef770U, 0xc05c30a9U, 0xe03d5477U, 0x8e973865U,
            };
            HW_SCE_p_func100(Param_pf9_func100_010);
            WR1_PROG(REG_B0H, 0x00009846U);

            WR1_PROG(REG_D4H, 0x40000200U);
            WR1_PROG(REG_D0H, 0xe7009d07U);
            HW_SCE_p_func_sub003(0x00430031U);

            WR1_PROG(REG_08H, 0x00001032U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[5]);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[9]);

            static const uint32_t Param_pf9_func100_011[] =
            {
                0x45bad9deU, 0x1308b911U, 0xdab5a86fU, 0xece350ccU,
            };
            HW_SCE_p_func100(Param_pf9_func100_011);
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0x09108105U);
            HW_SCE_p_func_sub003(0x00410011U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[13]);

            static const uint32_t Param_pf9_func100_012[] =
            {
                0x0ec30707U, 0xc78d8848U, 0xb688aa0eU, 0x44d6819eU,
            };
            HW_SCE_p_func100(Param_pf9_func100_012);
            HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
            RD1_ADDR(REG_2CH, &OutData_PrivKeyIndex[0]);

            static const uint32_t Param_pf9_func101_009[] =
            {
                0x42ab77c7U, 0x86f5c2b6U, 0x3b3039e2U, 0xe923f21eU,
            };
            HW_SCE_p_func101(Param_pf9_func101_009);
        }
        else
        {
            static const uint32_t Param_pf9_func100_013[] =
            {
                0x938bee36U, 0x8dd427b3U, 0x077a78ccU, 0xe2e0cf7cU,
            };
            HW_SCE_p_func100(Param_pf9_func100_013);
            HW_SCE_p_func_sub015(0x00009846U, 0x00006032U);
            RD12_ADDR(REG_2CH, &OutData_PrivKey[0]);

            static const uint32_t Param_pf9_func101_010[] =
            {
                0x586b842aU, 0xc00f385bU, 0xc28898e9U, 0xaf2cad9aU,
            };
            HW_SCE_p_func101(Param_pf9_func101_010);
        }

        static const uint32_t Param_pf9_func100_014[] =
        {
            0xb3089243U, 0xc1ad8fa1U, 0xc49b8510U, 0x70df0678U,
        };
        HW_SCE_p_func100(Param_pf9_func100_014);
        HW_SCE_p_func_sub015(0x00009838U, 0x00006032U);
        RD12_ADDR(REG_2CH, &OutData_PubKey[0]);

        static const uint32_t Param_pf9_func100_015[] =
        {
            0x51b7116eU, 0x42967733U, 0x5280f9bdU, 0x50936f9cU,
        };
        HW_SCE_p_func100(Param_pf9_func100_015);
        HW_SCE_p_func_sub015(0x0000983fU, 0x00006032U);
        RD12_ADDR(REG_2CH, &OutData_PubKey[12]);

        static const uint32_t Param_pf9_func102_002[] =
        {
            0x2d58b4d7U, 0xe583c6a4U, 0x8f643a7fU, 0x8343c42aU,
        };
        HW_SCE_p_func102(Param_pf9_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
