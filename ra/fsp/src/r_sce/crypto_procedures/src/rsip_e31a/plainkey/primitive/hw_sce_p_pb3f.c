/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128XtsEncryptFinalSub (const uint32_t InData_TextBitLen[],
                                           const uint32_t InData_Text[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_TextBitLen[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x00003440U, 0x00076842U, 0x00026c42U, 0x00000821U);

    HW_SCE_p_func_sub001(0x38008c00U, 0x0000007fU, 0x00020020U, 0x3420a800U);
    HW_SCE_p_func_sub001(0x00000080U, 0x1000d020U, 0x2000a840U, 0x00000004U);
    HW_SCE_p_func_sub006(0x00000080U, 0x38000c21U, 0x00A70000U);

    static const uint32_t Param_pb3f_func100_001[] =
    {
        0x854c34b8U, 0x282087faU, 0x5a8d99f6U, 0xad22cf30U,
    };
    HW_SCE_p_func100(Param_pb3f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pb3f_func102_001[] =
        {
            0x01d9a98cU, 0x1f8f44b8U, 0x01dac1ceU, 0xfb91de3cU,
        };
        HW_SCE_p_func102(Param_pb3f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_pb3f_func100_002[] =
        {
            0x994c4676U, 0x0210dfceU, 0x9dcc7aa3U, 0xbef5ba20U,
        };
        HW_SCE_p_func100(Param_pb3f_func100_002);
        HW_SCE_p_func_sub009(0x81010040U, 0x00005006U);
        RD1_ADDR(REG_2CH, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        static const uint32_t Param_pb3f_func100_003[] =
        {
            0x4f8047ccU, 0xb8357a03U, 0x6490520dU, 0x1c3a7f3eU,
        };
        HW_SCE_p_func100(Param_pb3f_func100_003);

        HW_SCE_p_func_sub016(0x00020061U, 0x00000020U, 0x0d008906U);
        WR1_PROG(REG_08H, 0x000c1000U);

        iLoop = 0U;
        if (S_RAM[0] >= 4)
        {
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_Text[0]);
            for (iLoop = 4; iLoop < S_RAM[0]; )
            {
                WAIT_STS(REG_14H, 31, 1);
                WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
                WAIT_STS(REG_08H, 30, 1);
                RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);
                iLoop = iLoop + 4U;
            }

            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);
        }

        HW_SCE_p_func206();

        HW_SCE_p_func_sub006(0x38008c00U, 0x0000007fU, 0x00A70000U);

        static const uint32_t Param_pb3f_func100_004[] =
        {
            0x5d35e8bfU, 0xb2db4873U, 0x8ac704e4U, 0x9e4b9dacU,
        };
        HW_SCE_p_func100(Param_pb3f_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub007(0x000003c1U, 0x00000020U, 0x0d008905U);
            WR4_ADDR(REG_2CH, &InData_Text[iLoop]);

            WR1_PROG(REG_94H, 0x000008c6U);
            WR1_PROG(REG_9CH, 0x80840006U);
            HW_SCE_p_func_sub003(0x03410011U);

            WR1_PROG(REG_94H, 0x0000b4e0U);
            WR1_PROG(REG_94H, 0x00000010U);
            HW_SCE_p_func_sub005(0x000003c7U, 0x80840007U);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 4]);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 5]);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 6]);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_Text[iLoop + 7]);
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func_sub001(0x000034a0U, 0x000368a5U, 0x00008ca0U, 0x0000000cU);

            HW_SCE_p_func_sub001(0x000024c5U, 0x000024e5U, 0x00003826U, 0x00003847U);

            HW_SCE_p_func_sub001(0x00003460U, 0x00008c60U, 0x0000001fU, 0x0000b480U);
            HW_SCE_p_func_sub001(0xffffffffU, 0x00004403U, 0x00007484U, 0x00000c24U);

            HW_SCE_p_func_sub001(0x00001484U, 0x00000c44U, 0x00001041U, 0x00003c47U);

            HW_SCE_p_func_sub001(0x00003420U, 0x00008c20U, 0x0000007fU, 0x38008c20U);
            HW_SCE_p_func_sub001(0x0000001fU, 0x1000a420U, 0x00000020U, 0x0000b440U);
            HW_SCE_p_func_sub001(0x00000080U, 0x00002841U, 0x00056842U, 0x00003402U);

            static const uint32_t Param_pb3f_func100_005[] =
            {
                0xfded8852U, 0xf375b584U, 0xde1274f2U, 0xcd505d8aU,
            };
            HW_SCE_p_func100(Param_pb3f_func100_005);
            HW_SCE_p_func_sub009(0x81010040U, 0x00005006U);
            RD1_ADDR(REG_2CH, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            WR1_PROG(REG_94H, 0x0000b460U);
            WR1_PROG(REG_94H, 0x00000004U);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                HW_SCE_p_func_sub001(0x000024c3U, 0x000024e3U, 0x00003826U, 0x00003c27U);

                WR1_PROG(REG_94H, 0x00003040U);
                static const uint32_t Param_pb3f_func101_001[] =
                {
                    0x5738cd88U, 0x775b76fcU, 0x403e188fU, 0x7b341a6dU,
                };
                HW_SCE_p_func101(Param_pb3f_func101_001);
            }

            HW_SCE_p_func_sub010(0x38000c42U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            static const uint32_t Param_pb3f_func100_006[] =
            {
                0x66854b7aU, 0x3c6c055fU, 0x17f6e309U, 0x6f697920U,
            };
            HW_SCE_p_func100(Param_pb3f_func100_006);
            WR1_PROG(REG_94H, 0x0000b4e0U);
            WR1_PROG(REG_94H, 0x00000010U);
            HW_SCE_p_func_sub021(0x00000020U, 0x0d008905U, 0x81840007U);
            HW_SCE_p_func_sub003(0x00490011U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_Text[iLoop]);

            HW_SCE_p_func_sub001(0x000008c6U, 0x000024c5U, 0x00003826U, 0x00000c24U);

            WR1_PROG(REG_94H, 0x00003c26U);

            WR1_PROG(REG_94H, 0x00000821U);

            for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
            {
                HW_SCE_p_func_sub022(0x000024c3U, 0x00003c26U, 0x00003000U);
                static const uint32_t Param_pb3f_func101_002[] =
                {
                    0x03914e5bU, 0xf9e21e94U, 0xed70f398U, 0x47b636b6U,
                };
                HW_SCE_p_func101(Param_pb3f_func101_002);
            }

            static const uint32_t Param_pb3f_func100_007[] =
            {
                0x71ed0242U, 0x8f086facU, 0x78236840U, 0xdea5d8e0U,
            };
            HW_SCE_p_func100(Param_pb3f_func100_007);
            HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_94H, 0x000008c6U);
            HW_SCE_p_func_sub009(0x81840006U, 0x00005012U);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 4]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 5]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 6]);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_Text[iLoop + 7]);

            static const uint32_t Param_pb3f_func101_003[] =
            {
                0x976bf953U, 0x528190d6U, 0x6223f388U, 0x0f5af31bU,
            };
            HW_SCE_p_func101(Param_pb3f_func101_003);
        }

        static const uint32_t Param_pb3f_func102_002[] =
        {
            0xffa7d819U, 0xa39ea27dU, 0x2fe036a1U, 0xceef3d2eU,
        };
        HW_SCE_p_func102(Param_pb3f_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
