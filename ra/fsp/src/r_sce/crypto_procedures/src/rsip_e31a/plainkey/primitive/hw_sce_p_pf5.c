/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyMode[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       OutData_Signature[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f50001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func027(InData_DomainParam);

    HW_SCE_p_func100(0x1a6a3e70U, 0x08504b05U, 0x5fe1583eU, 0x18b37cb1U);

    WR1_PROG(REG_B0H, 0x00009415U);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xf72b763aU, 0x3ad433cdU, 0x2f01b426U, 0x3a23020bU);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func103();
    HW_SCE_p_func100(0xbb243e4bU, 0xe651aca6U, 0x4423fcb8U, 0x3fac74ceU);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func103();
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_B0H, 0x00009438U);
    WR1_PROG(REG_00H, 0x00c0002dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_14H, 0x000000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

    WR1_PROG(REG_B0H, 0x00009423U);
    WR1_PROG(REG_00H, 0x00c0002dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_14H, 0x000000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

    WR1_PROG(REG_B4H, 0x0023000eU);
    WR1_PROG(REG_B8H, 0x001c0000U);

    WR1_PROG(REG_A4H, 0x0606000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B8H, 0x0000001cU);

    WR1_PROG(REG_A4H, 0x06060010U);

    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B4H, 0x00380015U);
    WR1_PROG(REG_B8H, 0x003f001cU);

    WR1_PROG(REG_A4H, 0x06060002U);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B4H, 0x0038003fU);
    WR1_PROG(REG_B8H, 0x00460000U);

    WR1_PROG(REG_A4H, 0x06060009U);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    HW_SCE_p_func028(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f5U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0xc5c1196dU, 0xab703962U, 0xf2ea11bfU, 0x64058279U);
    HW_SCE_p_func089();

    HW_SCE_p_func100(0x7f01fb8fU, 0x8f340dd5U, 0x708fea86U, 0x55b558abU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x55108f67U, 0xa4a3e373U, 0x65be77fcU, 0x648affc2U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_B8H, 0x0000000eU);

        WR1_PROG(REG_A4H, 0x06060010U);

        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x007e0038U);
        WR1_PROG(REG_B8H, 0x003f000eU);

        WR1_PROG(REG_A4H, 0x06060002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_14H, 0x000000a5U);
        WR1_PROG(REG_B0H, 0x00009415U);
        WR1_PROG(REG_00H, 0x00c0002dU);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_B4H, 0x0015003fU);
        WR1_PROG(REG_B8H, 0x0038000eU);

        WR1_PROG(REG_A4H, 0x06060002U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x00150038U);
        WR1_PROG(REG_B8H, 0x001c0000U);

        WR1_PROG(REG_A4H, 0x0606000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func100(0x7464657fU, 0x815bf615U, 0x07c2614cU, 0x127620f2U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x5a97975dU, 0xa33e3d04U, 0x13e09bc9U, 0x2d6da0f7U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x728d9478U, 0xc3d9aabcU, 0xdcd6c03eU, 0x05601553U);
            WR1_PROG(REG_B0H, 0x0000941cU);
            WR1_PROG(REG_00H, 0x00c0002dU);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);
            WR1_PROG(REG_14H, 0x000000a5U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

            WR1_PROG(REG_B4H, 0x001c000eU);
            WR1_PROG(REG_B8H, 0x00150000U);

            WR1_PROG(REG_A4H, 0x0606000aU);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_B4H, 0x00150046U);
            WR1_PROG(REG_B8H, 0x001c000eU);

            WR1_PROG(REG_A4H, 0x06060000U);
            WR1_PROG(REG_08H, 0x00020000U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);
            WR1_PROG(REG_40H, 0x00000d00U);

            WR1_PROG(REG_B4H, 0x007e001cU);
            WR1_PROG(REG_B8H, 0x0015000eU);

            WR1_PROG(REG_A4H, 0x06060002U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            WR1_PROG(REG_14H, 0x00000bc5U);
            WR1_PROG(REG_B0H, 0x0000941cU);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MsgDgst[0]);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MsgDgst[4]);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MsgDgst[8]);

            WR1_PROG(REG_14H, 0x000000c7U);
            WR1_PROG(REG_9CH, 0x80010000U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, InData_KeyMode[0]);
            WR1_PROG(REG_24H, 0x00000000U);

            WR1_PROG(REG_94H, 0x38000c00U);
            WR1_PROG(REG_9CH, 0x00000080U);
            WR1_PROG(REG_40H, 0x00270000U);

            HW_SCE_p_func100(0x2302add4U, 0x2d41b92cU, 0xa3bd3957U, 0x542af3b4U);
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
                WR1_PROG(REG_2CH, change_endian_long(0x000000f5U));
                WR1_PROG(REG_24H, 0x00000000U);

                HW_SCE_p_func101(0x7c0d40fbU, 0x895bc819U, 0x6c79199dU, 0x3e2a5e82U);
                HW_SCE_p_func043();

                HW_SCE_p_func076();

                WR1_PROG(REG_14H, 0x000000a7U);
                WR1_PROG(REG_9CH, 0x800100e0U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x000000f5U));
                WR1_PROG(REG_24H, 0x00000000U);

                HW_SCE_p_func101(0x01587e4aU, 0x405fc8a4U, 0x5f486015U, 0xc82cb431U);
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

                WR1_PROG(REG_B0H, 0x0000942aU);
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

                HW_SCE_p_func101(0xdd2e7dfcU, 0x60b9a092U, 0x652a8946U, 0x8e5c1313U);
            }
            else
            {
                WR1_PROG(REG_14H, 0x00000bc5U);
                WR1_PROG(REG_B0H, 0x0000942aU);
                WAIT_STS(REG_14H, 31, 1);
                WR12_ADDR(REG_2CH, &InData_Key[0]);

                HW_SCE_p_func101(0xe2439470U, 0xd546fdbfU, 0x0973194eU, 0x161d278dU);
            }

            HW_SCE_p_func100(0xc751991eU, 0xbe4f40caU, 0xb4af7142U, 0x189d799cU);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x9d9bddd8U, 0xed4ec227U, 0x2b4633d2U, 0x67f80372U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                WR1_PROG(REG_B4H, 0x007e002aU);
                WR1_PROG(REG_B8H, 0x0023000eU);

                WR1_PROG(REG_A4H, 0x06060002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x00380023U);
                WR1_PROG(REG_B8H, 0x002a000eU);

                WR1_PROG(REG_A4H, 0x06060002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x002a001cU);
                WR1_PROG(REG_B8H, 0x0023000eU);

                WR1_PROG(REG_A4H, 0x06060005U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B4H, 0x00230015U);
                WR1_PROG(REG_B8H, 0x002a000eU);

                WR1_PROG(REG_A4H, 0x06060002U);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_B0H, 0x00009415U);
                WR1_PROG(REG_00H, 0x00c0002dU);
                WAIT_STS(REG_04H, 30, 0);
                WR1_PROG(REG_40H, 0x00001800U);
                WR1_PROG(REG_14H, 0x000000a5U);
                WAIT_STS(REG_14H, 31, 1);
                WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

                WR1_PROG(REG_B4H, 0x0015002aU);
                WR1_PROG(REG_B8H, 0x001c0000U);

                WR1_PROG(REG_A4H, 0x0606000aU);
                WR1_PROG(REG_A0H, 0x20010001U);
                WAIT_STS(REG_A8H, 0, 1);
                WR1_PROG(REG_ACH, 0x00000001U);

                WR1_PROG(REG_40H, 0x00210000U);

                HW_SCE_p_func100(0x6b82f46eU, 0xd0778a7eU, 0x38b85951U, 0x3028bdfdU);
                WR1_PROG(REG_40H, 0x00400000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    HW_SCE_p_func102(0x058c74e7U, 0x067ef944U, 0x53deae0dU, 0xfa63f738U);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func100(0x82502182U, 0x22ff4b8cU, 0xe9d0dbe5U, 0x54f5f03fU);
                    WR1_PROG(REG_B0H, 0x00009838U);
                    WR1_PROG(REG_08H, 0x00006032U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[0]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[4]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[8]);

                    HW_SCE_p_func100(0xfdb80745U, 0x6279cbe8U, 0xd95ccf7eU, 0xa161e06eU);
                    WR1_PROG(REG_B0H, 0x0000982aU);
                    WR1_PROG(REG_08H, 0x00006032U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[12]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[16]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[20]);

                    HW_SCE_p_func102(0x1ff3be0eU, 0x83392ebbU, 0x45c069f6U, 0x98b61880U);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
