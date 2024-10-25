/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha224HmacMessageDigest (const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_Msg[],
                                          const uint32_t InData_MsgLen[],
                                          const uint32_t InData_MAC[],
                                          const uint32_t InData_length[],
                                          uint32_t       InData_State[],
                                          uint32_t       OutData_MAC[],
                                          uint32_t       OutData_State[],
                                          const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00740001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000074U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x01d87635U, 0xbd9a63dcU, 0xe0723726U, 0x43d85ae9U);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0000001aU);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000074U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x433cb9b3U, 0x3d1463a0U, 0xc7092b6aU, 0x9a451fe6U);
    HW_SCE_p_func044_r1();

    WR1_PROG(REG_1444H, 0x000007c2U);
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xf7009d07U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1608H, 0x80880000U);
    WR1_PROG(REG_1400H, 0x03420021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func100(0x05cf8becU, 0x0446dc34U, 0x092677b1U, 0x260de539U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x28fc6469U, 0x4b5fd918U, 0x6aca677aU, 0xc801f0caU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_2000H, 0x00000001U);

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010020U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Cmd[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x3420a820U);
        WR1_PROG(REG_1600H, 0x00000006U);
        WR1_PROG(REG_1600H, 0x2000b420U);
        WR1_PROG(REG_1600H, 0x00000005U);

        WR1_PROG(REG_1600H, 0x38000c21U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xbd35bc9eU, 0xd1dabd11U, 0x8276cd40U, 0x47df3facU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_2004H, 0x00000040U);

            WR1_PROG(REG_2008H, 0x00000013U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1608H, 0x81880000U);
            WR1_PROG(REG_1400H, 0x01490021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
            {
                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2014H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2010H, 0x00000080U);

                WR1_PROG(REG_200CH, 0x00000001U);

                WAIT_STS(REG_2030H, 8, 0);

                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2014H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2010H, 0x00000000U);

                WR1_PROG(REG_200CH, 0x00000100U);

                HW_SCE_p_func101(0xec0cc1f2U, 0xf3b29868U, 0x47e36370U, 0xd2188b8aU);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, InData_MsgLen[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, InData_MsgLen[1]);

                WR1_PROG(REG_200CH, 0x00000001U);

                HW_SCE_p_func101(0x93045ba8U, 0x3b8061d8U, 0xeb6138b5U, 0xa4191ec9U);
            }

            HW_SCE_p_func101(0x9bb56bf8U, 0x0bc461cbU, 0xe7a68329U, 0x761f5953U);
        }
        else
        {
            WR1_PROG(REG_2004H, 0x00001040U);

            WR1_PROG(REG_2008H, 0x00000013U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1608H, 0x81880000U);
            WR1_PROG(REG_1400H, 0x01490021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, InData_State[18]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, InData_State[19]);

            for (iLoop = 0U; iLoop < 18U; iLoop++)
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2028H, InData_State[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xd3a85e7bU, 0xd394b3c9U, 0x6cdb9616U, 0x8a229da3U);
        }

        WAIT_STS(REG_2030H, 0, 1);

        WR1_PROG(REG_1444H, 0x00020064U);

        for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);
            iLoop = iLoop + 16U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Msg[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x00000000U);
        WAIT_STS(REG_2030H, 8, 0);
        WR1_PROG(REG_143CH, 0x00001600U);

        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x629dc60fU, 0x9cd110e0U, 0x4b9592a9U, 0x70f0cd47U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            for (iLoop = 0U; iLoop < 18U; iLoop++)
            {
                RD1_ADDR(REG_202CH, &OutData_State[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            RD1_ADDR(REG_2014H, &OutData_State[18]);
            RD1_ADDR(REG_2010H, &OutData_State[19]);

            HW_SCE_p_func102(0x23e6c77cU, 0xcecf665aU, 0x5f848e07U, 0xd218e0aeU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x38000c21U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_1600H, 0x38008820U);
            WR1_PROG(REG_1600H, 0x00000003U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x5093a0d8U, 0xb0af94eaU, 0x6dc5c630U, 0x696d431eU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func100(0xe2c5a0d2U, 0xfd143905U, 0xb54a2a0aU, 0xb1249f75U);
                WR1_PROG(REG_1408H, 0x0000401eU);
                WAIT_STS(REG_1408H, 30, 1);
                RD7_ADDR(REG_1420H, &OutData_MAC[0]);

                HW_SCE_p_func102(0x0fa62559U, 0x584514fdU, 0x5f984732U, 0xf11290a2U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010020U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_length[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x3420a820U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_1600H, 0x3420a820U);
                WR1_PROG(REG_1600H, 0x0000001dU);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                HW_SCE_p_func100(0x69e40889U, 0x8c326aa2U, 0x9f804224U, 0xf23a5e02U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0xc986f172U, 0xc6f599ffU, 0xc42122f9U, 0x6f641f75U);
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x00000bffU);
                    WR1_PROG(REG_1608H, 0x8087001fU);
                    WR1_PROG(REG_1400H, 0x0345001dU);

                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00000800U);
                    for (iLoop = 0U; iLoop < 32U; iLoop++)
                    {
                        WR1_PROG(REG_1600H, 0x3c002be1U);
                        WR1_PROG(REG_1600H, 0x12003c1fU);
                        WR1_PROG(REG_1600H, 0x00002fe0U);
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1824H, 0x08000045U);
                    WR1_PROG(REG_1600H, 0x00000bffU);
                    WR1_PROG(REG_1608H, 0x8188001fU);
                    WR1_PROG(REG_1400H, 0x00490011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1824H, 0x08000055U);
                    WR1_PROG(REG_1400H, 0x00490011U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1444H, 0x000006c1U);
                    WR1_PROG(REG_1824H, 0x9c000005U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_MAC[0]);

                    WR1_PROG(REG_1824H, 0x9c100005U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR3_ADDR(REG_1420H, &InData_MAC[4]);
                    WR1_PROG(REG_1444H, 0x000000a1U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

                    HW_SCE_p_func100(0xbba991c0U, 0x96a30510U, 0x67733e98U, 0xf75774bdU);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        HW_SCE_p_func102(0xa3392f46U, 0x554bac1cU, 0x61b1fd28U, 0x03bb384cU);
                        WR1_PROG(REG_14BCH, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        HW_SCE_p_func102(0xb38ad2c6U, 0x620bdb3bU, 0xa7c5e209U, 0x94ad26d0U);
                        WR1_PROG(REG_14BCH, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return FSP_SUCCESS;
                    }
                }
            }
        }
    }
}
