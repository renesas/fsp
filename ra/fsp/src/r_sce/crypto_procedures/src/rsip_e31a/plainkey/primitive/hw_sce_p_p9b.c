/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyMode[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_PubKey[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       OutData_R[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x009b0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func076();

    WR1_PROG(REG_94H, 0x000034a6U);

    static const uint32_t Param_p9b_sub100_001[] =
    {
        0x9265cc8bU, 0x13fc4fe0U, 0xcc54b916U, 0xf9ef49dbU, 0x0000009bU, 0x9d6cfda4U, 0xc31e99d9U, 0xa3c6bea5U,
        0x06fc4d8dU, 0x0000009bU, 0x6f4d67beU, 0x26c24669U, 0xb8b0fd2fU, 0x751f0d13U, 0x00009446U, 0x16fa4821U,
        0xcdb2711cU, 0x1b749ea9U, 0xc8a1b8e0U, 0x00009446U, 0x79d0e062U, 0x91f60286U, 0xf27c3718U, 0xc1bbce2bU,
    };
    HW_SCE_p_func_sub100(InData_KeyIndex, InData_Key, Param_p9b_sub100_001, RSIP_SEL_BIT_LENGTH_384);

    static const uint32_t Param_p9b_func100_001[] =
    {
        0x4a54873eU, 0xa2325f9bU, 0xa1e1f0aaU, 0x99670d02U,
    };
    HW_SCE_p_func100(Param_p9b_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p9b_func102_001[] =
        {
            0xa6b363deU, 0x2e9e7c58U, 0x03d1da78U, 0xdb6b1893U,
        };
        HW_SCE_p_func102(Param_p9b_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_B0H, 0x00009415U);
        HW_SCE_p_func_sub003(0x00c0002dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub002(0x00150046U, 0x00230000U, 0x0606000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_p9b_func100_002[] =
        {
            0xf17a734aU, 0xa95e3f42U, 0xb7e0bd92U, 0xb5eee162U,
        };
        HW_SCE_p_func100(Param_p9b_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p9b_func102_002[] =
            {
                0xa3b7a722U, 0x203f1361U, 0x838d8e47U, 0xcf93c85eU,
            };
            HW_SCE_p_func102(Param_p9b_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_94H, 0x00003401U);

            HW_SCE_p_func027(InData_DomainParam);

            WR1_PROG(REG_B8H, 0x00000007U);

            WR1_PROG(REG_A4H, 0x06060010U);

            HW_SCE_p_func_sub012();

            HW_SCE_p_func_sub017(0x000017c5U, 0x00009415U);
            WR12_ADDR(REG_2CH, &InData_PubKey[0]);

            WR1_PROG(REG_B0H, 0x0000941cU);
            WAIT_STS(REG_14H, 31, 1);
            WR12_ADDR(REG_2CH, &InData_PubKey[12]);

            HW_SCE_p_func_sub002(0x004d0015U, 0x00230007U, 0x06060002U);

            HW_SCE_p_func_sub002(0x004d001cU, 0x002a0007U, 0x06060002U);

            HW_SCE_p_func_sub002(0x00230023U, 0x00150007U, 0x06060002U);

            HW_SCE_p_func_sub002(0x00850015U, 0x001c0007U, 0x06060005U);

            HW_SCE_p_func_sub002(0x0023001cU, 0x00150007U, 0x06060002U);

            HW_SCE_p_func_sub002(0x008c0015U, 0x001c0007U, 0x06060005U);

            HW_SCE_p_func_sub002(0x002a002aU, 0x00150007U, 0x06060002U);

            HW_SCE_p_func_sub002(0x001c0015U, 0x00310000U, 0x0606000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func_sub002(0x0015001cU, 0x00310000U, 0x0606000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            static const uint32_t Param_p9b_func100_003[] =
            {
                0x6f81c212U, 0x9735eca3U, 0x5645ff93U, 0x506c8ec3U,
            };
            HW_SCE_p_func100(Param_p9b_func100_003);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p9b_func102_003[] =
                {
                    0x0dbfb830U, 0x5af445d2U, 0xda7a8487U, 0x3f9fa854U,
                };
                HW_SCE_p_func102(Param_p9b_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
                WR1_PROG(REG_2CH, change_endian_long(0x0000009bU));
                WR1_PROG(REG_24H, 0x00000000U);

                static const uint32_t Param_p9b_func101_001[] =
                {
                    0x978846faU, 0x7615f475U, 0x28cf0dc3U, 0x8d71bcb2U,
                };
                HW_SCE_p_func101(Param_p9b_func101_001);
                HW_SCE_p_func089();

                static const uint32_t Param_p9b_func100_004[] =
                {
                    0x6fbb2885U, 0xb67e62b2U, 0xd2212e30U, 0xf6e6260dU,
                };
                HW_SCE_p_func100(Param_p9b_func100_004);
                WR1_PROG(REG_40H, 0x00400000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    static const uint32_t Param_p9b_func102_004[] =
                    {
                        0x7e2a14a3U, 0x95b9304dU, 0x5ba3dfeeU, 0x27ab2517U,
                    };
                    HW_SCE_p_func102(Param_p9b_func102_004);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    static const uint32_t Param_p9b_func100_005[] =
                    {
                        0xb04282a8U, 0x7bb4f05bU, 0xa4c31dceU, 0x1081e83cU,
                    };
                    HW_SCE_p_func100(Param_p9b_func100_005);
                    HW_SCE_p_func_sub015(0x00009838U, 0x00006032U);
                    RD12_ADDR(REG_2CH, &OutData_R[0]);

                    static const uint32_t Param_p9b_func100_006[] =
                    {
                        0x9b02bf09U, 0xd1a4ed75U, 0xaa345be2U, 0x7c116d72U,
                    };
                    HW_SCE_p_func100(Param_p9b_func100_006);
                    HW_SCE_p_func_sub015(0x0000983fU, 0x00006032U);
                    RD12_ADDR(REG_2CH, &OutData_R[12]);

                    static const uint32_t Param_p9b_func102_005[] =
                    {
                        0x9405f510U, 0x970bb01eU, 0x40d8a9fdU, 0x9299d3ebU,
                    };
                    HW_SCE_p_func102(Param_p9b_func102_005);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
