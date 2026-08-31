/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateEccEd25519RandomKeyIndexSub (const uint32_t InData_KeyMode[],
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

    WR1_PROG(REG_70H, 0x0001a001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x000014a0U);

    static const uint32_t Param_p1a_func100_001[] =
    {
        0x1b812f48U, 0x5003d636U, 0x9dfa3301U, 0xdf3333c8U,
    };
    HW_SCE_p_func100(Param_p1a_func100_001);
    HW_SCE_p_func103();
    static const uint32_t Param_p1a_func100_002[] =
    {
        0xe13ede4eU, 0xfc5ffb4dU, 0x31568f9eU, 0xcc063445U,
    };
    HW_SCE_p_func100(Param_p1a_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    WR1_PROG(REG_F0H, 0x00000001U);
    WR1_PROG(REG_F4H, 0x000000b0U);

    WR1_PROG(REG_14H, 0x00000020U);
    WR1_PROG(REG_104H, 0x00000000U);
    WR1_PROG(REG_14H, 0x00000020U);
    WR1_PROG(REG_100H, 0x00000100U);

    WR1_PROG(REG_B0H, 0x000018a0U);
    HW_SCE_p_func_sub003(0x01430021U);

    WAIT_STS(REG_118H, 4, 1);

    WR1_PROG(REG_94H, 0x00000800U);
    WR1_PROG(REG_9CH, 0x80880000U);
    HW_SCE_p_func_sub003(0x03450021U);
    HW_SCE_p_func_sub003(0x00050021U);

    HW_SCE_p_func_sub001(0x00003820U, 0x00008c20U, 0xf8ffffffU, 0x00003c20U);

    HW_SCE_p_func_sub001(0x0000b400U, 0x0000001cU, 0x00003820U, 0x00008c20U);
    HW_SCE_p_func_sub001(0xffffff3fU, 0x00009020U, 0x00000040U, 0x00003c20U);

    HW_SCE_p_func_sub001(0x00000800U, 0x00000821U, 0x00000842U, 0x0000b460U);
    WR1_PROG(REG_94H, 0x0000001fU);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        HW_SCE_p_func_sub001(0x02003801U, 0x02003843U, 0x02003c41U, 0x02003c03U);

        WR1_PROG(REG_94H, 0x00002c20U);
        WR1_PROG(REG_94H, 0x00003060U);
    }

    HW_SCE_p_func401(InData_DomainParam);

    HW_SCE_p_func406(InData_DomainParam);

    WR1_PROG(REG_B0H, 0x00001487U);
    HW_SCE_p_func_sub003(0x00c00021U);

    WR1_PROG(REG_B0H, 0x00000840U);
    WR1_PROG(REG_9CH, 0x80020000U);
    HW_SCE_p_func_sub003(0x03430009U);
    WR1_PROG(REG_B0H, 0x000004b1U);
    WR1_PROG(REG_9CH, 0x81020000U);
    HW_SCE_p_func_sub003(0x00c90009U);

    WR1_PROG(REG_B0H, 0x00001450U);
    HW_SCE_p_func_sub003(0x00c00015U);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
    HW_SCE_p_func_sub003(0x00c00009U);

    WR1_PROG(REG_B0H, 0x00001464U);
    HW_SCE_p_func_sub003(0x00c00021U);

    WR1_PROG(REG_B0H, 0x00001469U);
    HW_SCE_p_func_sub003(0x00c00015U);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
    HW_SCE_p_func_sub003(0x00c00009U);

    WR1_PROG(REG_B0H, 0x0000146eU);
    HW_SCE_p_func_sub003(0x00c00015U);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
    HW_SCE_p_func_sub003(0x00c00009U);

    WR1_PROG(REG_B0H, 0x0000148cU);
    HW_SCE_p_func_sub003(0x00c00021U);

    WR1_PROG(REG_B0H, 0x00001491U);
    HW_SCE_p_func_sub003(0x00c00015U);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
    HW_SCE_p_func_sub003(0x00c00009U);

    WR1_PROG(REG_B0H, 0x00001496U);
    HW_SCE_p_func_sub003(0x00c00015U);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000026U);
    HW_SCE_p_func_sub003(0x00c00009U);

    HW_SCE_p_func_sub001(0x000008c6U, 0x00000800U, 0x0000b420U, 0x0000001fU);

    WR1_PROG(REG_94H, 0x0000b440U);
    WR1_PROG(REG_94H, 0x00000001U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x0000001aU));
    WR1_PROG(REG_24H, 0x00000000U);

    for (iLoop = 0U; iLoop < 256U; iLoop++)
    {
        HW_SCE_p_func405();

        HW_SCE_p_func403();

        static const uint32_t Param_p1a_func101_001[] =
        {
            0x76553d38U, 0xad268303U, 0x0b5e74c9U, 0xcb0e9a3fU,
        };
        HW_SCE_p_func101(Param_p1a_func101_001);
        HW_SCE_p_func402();

        HW_SCE_p_func404();

        WR1_PROG(REG_94H, 0x00002cc0U);

        static const uint32_t Param_p1a_func101_002[] =
        {
            0xc699e0b6U, 0x3a50b2b5U, 0xf4915a2fU, 0x509c42fdU,
        };
        HW_SCE_p_func101(Param_p1a_func101_002);
    }

    HW_SCE_p_func_sub006(0x380088c0U, 0x00000100U, 0x00270000U);

    WR1_PROG(REG_40H, 0x00402000U);

    static const uint32_t Param_p1a_func100_003[] =
    {
        0x6f824ab9U, 0x5fb81fdaU, 0xef2371f1U, 0xfb1eac74U,
    };
    HW_SCE_p_func100(Param_p1a_func100_003);

    HW_SCE_p_func_sub002(0x00870064U, 0x00550000U, 0x0404000aU);

    HW_SCE_p_func_sub002(0x00870069U, 0x005a0000U, 0x0404000aU);

    HW_SCE_p_func_sub002(0x0087006eU, 0x005f0000U, 0x0404000aU);

    WR1_PROG(REG_B0H, 0x00001482U);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub002(0x0082005fU, 0x00230005U, 0x04040002U);

    WR1_PROG(REG_B0H, 0x0000142dU);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

    HW_SCE_p_func_sub002(0x002d0005U, 0x00280000U, 0x0404000aU);

    HW_SCE_p_func_sub019(0x00280023U, 0x002d0005U, 0x04040000U);
    HW_SCE_p_func_sub012();
    WR1_PROG(REG_40H, 0x00000d00U);

    HW_SCE_p_func_sub002(0x002d0055U, 0x00230005U, 0x04040002U);

    HW_SCE_p_func_sub002(0x002d005aU, 0x00280005U, 0x04040002U);

    WR1_PROG(REG_B0H, 0x00001823U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80880001U);
    HW_SCE_p_func_sub003(0x03430021U);

    HW_SCE_p_func_sub001(0x0000b420U, 0x0000001cU, 0x00003841U, 0x001f6c42U);

    WR1_PROG(REG_B0H, 0x00001828U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80880001U);
    HW_SCE_p_func_sub003(0x03430021U);

    HW_SCE_p_func_sub001(0x00003801U, 0x00008c00U, 0x7fffffffU, 0x00001002U);

    HW_SCE_p_func_sub001(0x00003c01U, 0x00000800U, 0x00000821U, 0x00000842U);
    WR1_PROG(REG_94H, 0x0000b460U);
    WR1_PROG(REG_94H, 0x0000001fU);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        HW_SCE_p_func_sub001(0x02003801U, 0x02003843U, 0x02003c41U, 0x02003c03U);

        WR1_PROG(REG_94H, 0x00002c20U);
        WR1_PROG(REG_94H, 0x00003060U);
    }

    WR1_PROG(REG_94H, 0x00000800U);

    WR1_PROG(REG_B0H, 0x000014a5U);
    WR1_PROG(REG_9CH, 0x81880000U);
    HW_SCE_p_func_sub003(0x00c90021U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

    static const uint32_t Param_p1a_func100_004[] =
    {
        0x8781daffU, 0x081450cfU, 0xc55d07f9U, 0x69ef749fU,
    };
    HW_SCE_p_func100(Param_p1a_func100_004);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p1a_func100_005[] =
        {
            0x032620a0U, 0x62cf32b8U, 0x0642e9d0U, 0x4b186fa8U,
        };
        HW_SCE_p_func100(Param_p1a_func100_005);
        HW_SCE_p_func103();

        HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

        WR1_PROG(REG_9CH, 0x80010000U);
        HW_SCE_p_func_sub003(0x03410005U);
        HW_SCE_p_func_sub003(0x0001000dU);

        WR1_PROG(REG_94H, 0x000034c0U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x0000001aU));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p1a_func101_003[] =
        {
            0x786df190U, 0x27107fbcU, 0xfeacf57bU, 0x1c64e4baU,
        };
        HW_SCE_p_func101(Param_p1a_func101_003);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x00000027U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x0000001aU));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p1a_func101_004[] =
        {
            0xa5d2160eU, 0xd020aa4aU, 0xa3945071U, 0x76a51eb6U,
        };
        HW_SCE_p_func101(Param_p1a_func101_004);
        HW_SCE_p_func044();

        static const uint32_t Param_p1a_func100_006[] =
        {
            0xc67b6c76U, 0xdc6e9c3bU, 0x5a560668U, 0x6b62cb9eU,
        };
        HW_SCE_p_func100(Param_p1a_func100_006);
        WR1_PROG(REG_B0H, 0x000018a0U);

        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xe7009d07U);
        HW_SCE_p_func_sub003(0x00430021U);

        WR1_PROG(REG_08H, 0x00001022U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[1]);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[5]);

        static const uint32_t Param_p1a_func100_007[] =
        {
            0x06973d85U, 0x23f26fdaU, 0x35703a56U, 0xf936156aU,
        };
        HW_SCE_p_func100(Param_p1a_func100_007);
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x09108105U);
        HW_SCE_p_func_sub003(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[9]);

        static const uint32_t Param_p1a_func100_008[] =
        {
            0xe0bef1ebU, 0xf50de238U, 0xbd03772dU, 0x2ceb2b96U,
        };
        HW_SCE_p_func100(Param_p1a_func100_008);
        HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
        RD1_ADDR(REG_2CH, &OutData_PrivKeyIndex[0]);

        static const uint32_t Param_p1a_func101_005[] =
        {
            0x44940cf2U, 0x5fc93b7fU, 0x1d2e0f15U, 0xb565f036U,
        };
        HW_SCE_p_func101(Param_p1a_func101_005);
    }
    else
    {
        static const uint32_t Param_p1a_func100_009[] =
        {
            0x31876621U, 0x9488be39U, 0xea65c665U, 0x466060f8U,
        };
        HW_SCE_p_func100(Param_p1a_func100_009);
        HW_SCE_p_func_sub015(0x000018a0U, 0x00006022U);
        RD8_ADDR(REG_2CH, &OutData_PrivKey[0]);

        static const uint32_t Param_p1a_func101_006[] =
        {
            0x5786ed25U, 0x555bfd14U, 0x89f2d7d1U, 0x01978fe3U,
        };
        HW_SCE_p_func101(Param_p1a_func101_006);
    }

    static const uint32_t Param_p1a_func100_010[] =
    {
        0xcf5f0a1eU, 0x3f97c086U, 0x7e8d3aceU, 0xfb03be3dU,
    };
    HW_SCE_p_func100(Param_p1a_func100_010);
    HW_SCE_p_func_sub015(0x000018a5U, 0x00006022U);
    RD8_ADDR(REG_2CH, &OutData_PubKey[0]);

    static const uint32_t Param_p1a_func102_001[] =
    {
        0x5e4345eaU, 0x81fb7650U, 0x08c6d519U, 0xca0970e0U,
    };
    HW_SCE_p_func102(Param_p1a_func102_001);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
