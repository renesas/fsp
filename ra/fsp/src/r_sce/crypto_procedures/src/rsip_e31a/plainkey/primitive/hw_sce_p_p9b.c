/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyMode[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_PubKey[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       OutData_R[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x009b0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x00003420U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0xa90c9b82U, 0xd19bbfffU, 0xe8fd3aa2U, 0xe32131d7U);
    WR1_PROG(REG_40H, 0x00400000U);
    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x0000009bU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xda5ba085U, 0xdd39db78U, 0xbc84fb81U, 0xfab94436U);
        HW_SCE_p_func043();

        HW_SCE_p_func076();

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x0000009bU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x3382b087U, 0xa85f4958U, 0xffe47320U, 0x89f68a0bU);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x00000bc1U);
        WR1_PROG(REG_D4H, 0x40000200U);
        WR1_PROG(REG_D0H, 0xf7009d07U);

        for (iLoop = 0U; iLoop < 12U; )
        {
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_B0H, 0x00009446U);
        WR1_PROG(REG_00H, 0x00c10031U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(0x16fa4821U, 0xcdb2711cU, 0x1b749ea9U, 0xc8a1b8e0U);
    }
    else
    {
        WR1_PROG(REG_14H, 0x00000bc5U);
        WR1_PROG(REG_B0H, 0x00009446U);
        WAIT_STS(REG_14H, 31, 1);
        WR12_ADDR(REG_2CH, &InData_Key[0]);

        HW_SCE_p_func101(0xacb821f5U, 0xa1d7f87bU, 0x8d2bfb00U, 0x52f2c44bU);
    }

    HW_SCE_p_func100(0x4a54873eU, 0xa2325f9bU, 0xa1e1f0aaU, 0x99670d02U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xa6b363deU, 0x2e9e7c58U, 0x03d1da78U, 0xdb6b1893U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_B0H, 0x00009415U);
        WR1_PROG(REG_00H, 0x00c0002dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WR1_PROG(REG_14H, 0x000000a5U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_B4H, 0x00150046U);
        WR1_PROG(REG_B8H, 0x00230000U);

        WR1_PROG(REG_A4H, 0x0606000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func100(0xf17a734aU, 0xa95e3f42U, 0xb7e0bd92U, 0xb5eee162U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0xa3b7a722U, 0x203f1361U, 0x838d8e47U, 0xcf93c85eU);
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

            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_14H, 0x000017c5U);
            WR1_PROG(REG_B0H, 0x00009415U);
            WAIT_STS(REG_14H, 31, 1);
            WR12_ADDR(REG_2CH, &InData_PubKey[0]);

            WR1_PROG(REG_B0H, 0x0000941cU);
            WAIT_STS(REG_14H, 31, 1);
            WR12_ADDR(REG_2CH, &InData_PubKey[12]);

            WR1_PROG(REG_B4H, 0x004d0015U);
            WR1_PROG(REG_B8H, 0x00230007U);

            WR1_PROG(REG_A4H, 0x06060002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x004d001cU);
            WR1_PROG(REG_B8H, 0x002a0007U);

            WR1_PROG(REG_A4H, 0x06060002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00230023U);
            WR1_PROG(REG_B8H, 0x00150007U);

            WR1_PROG(REG_A4H, 0x06060002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00850015U);
            WR1_PROG(REG_B8H, 0x001c0007U);

            WR1_PROG(REG_A4H, 0x06060005U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x0023001cU);
            WR1_PROG(REG_B8H, 0x00150007U);

            WR1_PROG(REG_A4H, 0x06060002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x008c0015U);
            WR1_PROG(REG_B8H, 0x001c0007U);

            WR1_PROG(REG_A4H, 0x06060005U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x002a002aU);
            WR1_PROG(REG_B8H, 0x00150007U);

            WR1_PROG(REG_A4H, 0x06060002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x001c0015U);
            WR1_PROG(REG_B8H, 0x00310000U);

            WR1_PROG(REG_A4H, 0x0606000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            WR1_PROG(REG_B4H, 0x0015001cU);
            WR1_PROG(REG_B8H, 0x00310000U);

            WR1_PROG(REG_A4H, 0x0606000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func100(0x6f81c212U, 0x9735eca3U, 0x5645ff93U, 0x506c8ec3U);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x0dbfb830U, 0x5af445d2U, 0xda7a8487U, 0x3f9fa854U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_14H, 0x000000a7U);
                WR1_PROG(REG_9CH, 0x800100e0U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x0000009bU));
                WR1_PROG(REG_24H, 0x00000000U);

                HW_SCE_p_func101(0x978846faU, 0x7615f475U, 0x28cf0dc3U, 0x8d71bcb2U);
                HW_SCE_p_func089();

                HW_SCE_p_func100(0x6fbb2885U, 0xb67e62b2U, 0xd2212e30U, 0xf6e6260dU);
                WR1_PROG(REG_40H, 0x00400000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    HW_SCE_p_func102(0x7e2a14a3U, 0x95b9304dU, 0x5ba3dfeeU, 0x27ab2517U);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func100(0xb04282a8U, 0x7bb4f05bU, 0xa4c31dceU, 0x1081e83cU);
                    WR1_PROG(REG_B0H, 0x00009838U);
                    WR1_PROG(REG_08H, 0x00006032U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD12_ADDR(REG_2CH, &OutData_R[0]);

                    HW_SCE_p_func100(0x9b02bf09U, 0xd1a4ed75U, 0xaa345be2U, 0x7c116d72U);
                    WR1_PROG(REG_B0H, 0x0000983fU);
                    WR1_PROG(REG_08H, 0x00006032U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD12_ADDR(REG_2CH, &OutData_R[12]);

                    HW_SCE_p_func102(0x9405f510U, 0x970bb01eU, 0x40d8a9fdU, 0x9299d3ebU);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
