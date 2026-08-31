/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha2HmacFinalSub (const uint32_t InData_Cmd[],
                                   const uint32_t InData_Msg[],
                                   const uint32_t InData_MAC[],
                                   const uint32_t InData_length[],
                                   uint32_t       OutData_MAC[],
                                   const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_118H, 0, 1);

    WR1_PROG(REG_14H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR16_ADDR(REG_2CH, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_14H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_2CH, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_14H, 0x00000000U);
    WAIT_STS(REG_118H, 8, 0);
    WR1_PROG(REG_40H, 0x00001600U);

    WAIT_STS(REG_118H, 4, 1);

    HW_SCE_p_func_sub001(0x38008880U, 0x00000004U, 0x1000b480U, 0x00000002U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

    static const uint32_t Param_p75f_func100_001[] =
    {
        0x5382830aU, 0xe4ab43fbU, 0x6a49be64U, 0x0aee1fbcU,
    };
    HW_SCE_p_func100(Param_p75f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p75f_func100_002[] =
        {
            0x0e35de2cU, 0xd6460dd1U, 0x6d1ee190U, 0x2f65a622U,
        };
        HW_SCE_p_func100(Param_p75f_func100_002);

        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            static const uint32_t Param_p75f_func100_003[] =
            {
                0x65e21a66U, 0x58ca34fbU, 0xa17ede80U, 0xe1ce5b88U,
            };
            HW_SCE_p_func100(Param_p75f_func100_003);
            WR1_PROG(REG_08H, 0x00004022U);
            WAIT_STS(REG_08H, 30, 1);
            RD8_ADDR(REG_2CH, &OutData_MAC[0]);

            static const uint32_t Param_p75f_func102_001[] =
            {
                0xc7ff4808U, 0x781fe13dU, 0xb9c35cc9U, 0x8ccfc6d4U,
            };
            HW_SCE_p_func102(Param_p75f_func102_001);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            static const uint32_t Param_p75f_func100_004[] =
            {
                0x0096102cU, 0x661d0192U, 0xa29633eeU, 0x08da6d64U,
            };
            HW_SCE_p_func100(Param_p75f_func100_004);
            WR1_PROG(REG_08H, 0x0000401eU);
            WAIT_STS(REG_08H, 30, 1);
            RD7_ADDR(REG_2CH, &OutData_MAC[0]);

            static const uint32_t Param_p75f_func102_002[] =
            {
                0xb3a6451fU, 0x2771471aU, 0x949318e5U, 0xd30a44f8U,
            };
            HW_SCE_p_func102(Param_p75f_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            static const uint32_t Param_p75f_func100_005[] =
            {
                0xecb7c34fU, 0x42e5b11cU, 0x46f4c985U, 0xaa2c51adU,
            };
            HW_SCE_p_func100(Param_p75f_func100_005);
            WR1_PROG(REG_08H, 0x00004032U);
            WAIT_STS(REG_08H, 30, 1);
            RD12_ADDR(REG_2CH, &OutData_MAC[0]);

            static const uint32_t Param_p75f_func102_003[] =
            {
                0x7c70493cU, 0x2f1af63eU, 0x26623d95U, 0x53fdef9eU,
            };
            HW_SCE_p_func102(Param_p75f_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            static const uint32_t Param_p75f_func100_006[] =
            {
                0x4397e8d0U, 0x0ebba477U, 0x37b3df6eU, 0x700a9483U,
            };
            HW_SCE_p_func100(Param_p75f_func100_006);
            WR1_PROG(REG_08H, 0x00004042U);
            WAIT_STS(REG_08H, 30, 1);
            RD16_ADDR(REG_2CH, &OutData_MAC[0]);

            static const uint32_t Param_p75f_func102_004[] =
            {
                0xa9aa9e45U, 0xbf306866U, 0x0fa2abf2U, 0x041f54f3U,
            };
            HW_SCE_p_func102(Param_p75f_func102_004);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);
        }

        return FSP_SUCCESS;
    }
    else
    {
        static const uint32_t Param_p75f_func100_007[] =
        {
            0xb56b3538U, 0xa709b7aaU, 0x95aa85bbU, 0x2911551cU,
        };
        HW_SCE_p_func100(Param_p75f_func100_007);

        HW_SCE_p_func_sub005(0x000000c7U, 0x80010020U);
        WR1_PROG(REG_2CH, InData_length[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x00007c04U);
        WR1_PROG(REG_40H, 0x00600000U);

        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000020U);

            static const uint32_t Param_p75f_func101_001[] =
            {
                0x10826a1aU, 0x30295e1aU, 0x2219eae9U, 0xc5f8b6f7U,
            };
            HW_SCE_p_func101(Param_p75f_func101_001);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x0000001cU);

            static const uint32_t Param_p75f_func101_002[] =
            {
                0x4ec166e8U, 0x602e07a9U, 0xcabb5810U, 0xd5f44116U,
            };
            HW_SCE_p_func101(Param_p75f_func101_002);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000030U);

            static const uint32_t Param_p75f_func101_003[] =
            {
                0xfa058e9cU, 0xe0af0db1U, 0x78d78a03U, 0x0ea0d198U,
            };
            HW_SCE_p_func101(Param_p75f_func101_003);
        }
        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_94H, 0x0000b440U);
            WR1_PROG(REG_94H, 0x00000040U);

            static const uint32_t Param_p75f_func101_004[] =
            {
                0xfa35cf96U, 0xf889f32dU, 0x97e59d0aU, 0x8564a044U,
            };
            HW_SCE_p_func101(Param_p75f_func101_004);
        }

        HW_SCE_p_func_sub006(0x3420a820U, 0x00000004U, 0x00270000U);

        HW_SCE_p_func_sub010(0x34202841U, 0x00270000U);

        static const uint32_t Param_p75f_func100_008[] =
        {
            0x00471861U, 0x787b159aU, 0x215321f8U, 0x4e30a891U,
        };
        HW_SCE_p_func100(Param_p75f_func100_008);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p75f_func102_005[] =
            {
                0x35c6ba41U, 0xf290472eU, 0x8335f4c3U, 0x24a970b5U,
            };
            HW_SCE_p_func102(Param_p75f_func102_005);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            static const uint32_t Param_p75f_func100_009[] =
            {
                0x951f62faU, 0xc1b3a8fbU, 0x02484e6dU, 0x98b1913eU,
            };
            HW_SCE_p_func100(Param_p75f_func100_009);

            HW_SCE_p_func_sub001(0x000008c6U, 0x000008a5U, 0x0000a440U, 0x0000000fU);
            WR1_PROG(REG_94H, 0x00046842U);
            WR1_PROG(REG_94H, 0x00026c42U);

            HW_SCE_p_func_sub009(0x81010040U, 0x00005006U);
            RD1_ADDR(REG_2CH, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; )
            {
                static const uint32_t Param_p75f_func100_010[] =
                {
                    0xc9ac73c8U, 0x6e2fbb30U, 0x298cf0eeU, 0x13322411U,
                };
                HW_SCE_p_func100(Param_p75f_func100_010);

                HW_SCE_p_func_sub001(0x000008e7U, 0x00000863U, 0x380088c0U, 0x00000004U);
                HW_SCE_p_func_sub001(0x2000d060U, 0x38008880U, 0x00000003U, 0x2000d060U);

                WR1_PROG(REG_94H, 0x00007c03U);
                WR1_PROG(REG_40H, 0x00600000U);

                if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_9CH, 0x80830007U);
                    HW_SCE_p_func_sub003(0x0345000dU);

                    HW_SCE_p_func_sub011(0x000002c1U, 0x08000045U);
                    WR3_ADDR(REG_2CH, &InData_MAC[iLoop]);
                    HW_SCE_p_func_sub008(0x000000a1U, 0x00000000U);

                    static const uint32_t Param_p75f_func101_005[] =
                    {
                        0x3ee0be4aU, 0xa3251c69U, 0x5c386e28U, 0x39dfe4edU,
                    };
                    HW_SCE_p_func101(Param_p75f_func101_005);
                }
                else
                {
                    WR1_PROG(REG_9CH, 0x80840007U);
                    HW_SCE_p_func_sub003(0x03450011U);

                    HW_SCE_p_func_sub011(0x000003c1U, 0x08000045U);
                    WR4_ADDR(REG_2CH, &InData_MAC[iLoop]);

                    static const uint32_t Param_p75f_func101_006[] =
                    {
                        0x5837832aU, 0xeeb0583aU, 0x5861adc6U, 0xd9022a26U,
                    };
                    HW_SCE_p_func101(Param_p75f_func101_006);
                }

                WR1_PROG(REG_94H, 0x00000800U);
                for (jLoop = 0U; jLoop < 16U; jLoop++)
                {
                    HW_SCE_p_func_sub001(0x3c0028a1U, 0x12003c07U, 0x00002ce0U, 0x00002ca0U);
                }

                HW_SCE_p_func_sub013(0x9c000005U, 0x000008e7U, 0x81840007U);
                HW_SCE_p_func_sub003(0x00490011U);

                WR1_PROG(REG_94H, 0x0000a4c0U);
                WR1_PROG(REG_94H, 0x00000004U);

                static const uint32_t Param_p75f_func101_007[] =
                {
                    0x455cf341U, 0xe7e69b18U, 0xf641fe3aU, 0x81e1939dU,
                };
                HW_SCE_p_func101(Param_p75f_func101_007);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_94H, 0x000008c2U);

            WR1_PROG(REG_94H, 0x00007c06U);
            WR1_PROG(REG_40H, 0x00602000U);

            static const uint32_t Param_p75f_func100_011[] =
            {
                0xd0553e43U, 0xb2ed5cd7U, 0x982d9893U, 0xd0782e1aU,
            };
            HW_SCE_p_func100(Param_p75f_func100_011);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p75f_func102_006[] =
                {
                    0x26a4b405U, 0x01e7feecU, 0xa810a779U, 0x71247336U,
                };
                HW_SCE_p_func102(Param_p75f_func102_006);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p75f_func102_007[] =
                {
                    0x0c785bc2U, 0xe27eb583U, 0x3178e5c2U, 0x00aa7661U,
                };
                HW_SCE_p_func102(Param_p75f_func102_007);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
