/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyMode[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       OutData_Signature[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f50001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func027(InData_DomainParam);

    static const uint32_t Param_pf5_func100_001[] =
    {
        0x1a6a3e70U, 0x08504b05U, 0x5fe1583eU, 0x18b37cb1U,
    };
    HW_SCE_p_func100(Param_pf5_func100_001);

    WR1_PROG(REG_B0H, 0x00009415U);
    HW_SCE_p_func103();
    static const uint32_t Param_pf5_func100_002[] =
    {
        0xf72b763aU, 0x3ad433cdU, 0x2f01b426U, 0x3a23020bU,
    };
    HW_SCE_p_func100(Param_pf5_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf5_func100_003[] =
    {
        0xbb243e4bU, 0xe651aca6U, 0x4423fcb8U, 0x3fac74ceU,
    };
    HW_SCE_p_func100(Param_pf5_func100_003);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub003(0x00c10011U);

    WR1_PROG(REG_B0H, 0x00009438U);
    HW_SCE_p_func_sub003(0x00c0002dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    WR1_PROG(REG_B0H, 0x00009423U);
    HW_SCE_p_func_sub003(0x00c0002dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

    HW_SCE_p_func_sub002(0x0023000eU, 0x001c0000U, 0x0606000aU);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B8H, 0x0000001cU);

    WR1_PROG(REG_A4H, 0x06060010U);

    HW_SCE_p_func_sub012();

    HW_SCE_p_func_sub002(0x00380015U, 0x003f001cU, 0x06060002U);

    HW_SCE_p_func_sub002(0x0038003fU, 0x00460000U, 0x06060009U);

    HW_SCE_p_func028(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f5U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pf5_func101_001[] =
    {
        0xc5c1196dU, 0xab703962U, 0xf2ea11bfU, 0x64058279U,
    };
    HW_SCE_p_func101(Param_pf5_func101_001);
    HW_SCE_p_func089();

    static const uint32_t Param_pf5_func100_004[] =
    {
        0x7f01fb8fU, 0x8f340dd5U, 0x708fea86U, 0x55b558abU,
    };
    HW_SCE_p_func100(Param_pf5_func100_004);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pf5_func102_001[] =
        {
            0x55108f67U, 0xa4a3e373U, 0x65be77fcU, 0x648affc2U,
        };
        HW_SCE_p_func102(Param_pf5_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_B8H, 0x0000000eU);

        WR1_PROG(REG_A4H, 0x06060010U);

        HW_SCE_p_func_sub012();

        HW_SCE_p_func_sub002(0x007e0038U, 0x003f000eU, 0x06060002U);

        WR1_PROG(REG_14H, 0x000000a5U);
        WR1_PROG(REG_B0H, 0x00009415U);
        HW_SCE_p_func_sub003(0x00c0002dU);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        HW_SCE_p_func_sub002(0x0015003fU, 0x0038000eU, 0x06060002U);

        HW_SCE_p_func_sub002(0x00150038U, 0x001c0000U, 0x0606000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_pf5_func100_005[] =
        {
            0x7464657fU, 0x815bf615U, 0x07c2614cU, 0x127620f2U,
        };
        HW_SCE_p_func100(Param_pf5_func100_005);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pf5_func102_002[] =
            {
                0x5a97975dU, 0xa33e3d04U, 0x13e09bc9U, 0x2d6da0f7U,
            };
            HW_SCE_p_func102(Param_pf5_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            static const uint32_t Param_pf5_func100_006[] =
            {
                0x728d9478U, 0xc3d9aabcU, 0xdcd6c03eU, 0x05601553U,
            };
            HW_SCE_p_func100(Param_pf5_func100_006);
            WR1_PROG(REG_B0H, 0x0000941cU);
            HW_SCE_p_func_sub003(0x00c0002dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

            HW_SCE_p_func_sub002(0x001c000eU, 0x00150000U, 0x0606000aU);

            HW_SCE_p_func_sub019(0x00150046U, 0x001c000eU, 0x06060000U);
            HW_SCE_p_func_sub012();
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func_sub002(0x007e001cU, 0x0015000eU, 0x06060002U);

            HW_SCE_p_func_sub017(0x00000bc5U, 0x0000941cU);
            WR4_ADDR(REG_2CH, &InData_MsgDgst[0]);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MsgDgst[4]);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MsgDgst[8]);

            HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
            WR1_PROG(REG_2CH, InData_KeyMode[0]);
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func076();

            WR1_PROG(REG_94H, 0x000034a6U);

            static const uint32_t Param_pf5_sub100_001[] =
            {
                0x00e95e43U, 0x78b2cfc0U, 0x9ee5e83aU, 0xf97787bfU, 0x000000f5U, 0xad719524U, 0xc5187c37U, 0x01f15299U,
                0xec9bda24U, 0x000000f5U, 0x830f8cd3U, 0xcbb57783U, 0xa3fcdb99U, 0xed7fcc73U, 0x0000942aU, 0xdd2e7dfcU,
                0x60b9a092U, 0x652a8946U, 0x8e5c1313U, 0x0000942aU, 0xd34462e3U, 0xf2f4918cU, 0xae365994U, 0xbbf2b14eU,
            };
            HW_SCE_p_func_sub100(InData_KeyIndex, InData_Key, Param_pf5_sub100_001, RSIP_SEL_BIT_LENGTH_384);

            static const uint32_t Param_pf5_func100_007[] =
            {
                0xc751991eU, 0xbe4f40caU, 0xb4af7142U, 0x189d799cU,
            };
            HW_SCE_p_func100(Param_pf5_func100_007);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_pf5_func102_003[] =
                {
                    0x9d9bddd8U, 0xed4ec227U, 0x2b4633d2U, 0x67f80372U,
                };
                HW_SCE_p_func102(Param_pf5_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                HW_SCE_p_func_sub002(0x007e002aU, 0x0023000eU, 0x06060002U);

                HW_SCE_p_func_sub002(0x00380023U, 0x002a000eU, 0x06060002U);

                HW_SCE_p_func_sub002(0x002a001cU, 0x0023000eU, 0x06060005U);

                HW_SCE_p_func_sub002(0x00230015U, 0x002a000eU, 0x06060002U);

                WR1_PROG(REG_B0H, 0x00009415U);
                HW_SCE_p_func_sub003(0x00c0002dU);
                HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

                HW_SCE_p_func_sub002(0x0015002aU, 0x001c0000U, 0x0606000aU);

                WR1_PROG(REG_40H, 0x00210000U);

                static const uint32_t Param_pf5_func100_008[] =
                {
                    0x6b82f46eU, 0xd0778a7eU, 0x38b85951U, 0x3028bdfdU,
                };
                HW_SCE_p_func100(Param_pf5_func100_008);
                WR1_PROG(REG_40H, 0x00400000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    static const uint32_t Param_pf5_func102_004[] =
                    {
                        0x058c74e7U, 0x067ef944U, 0x53deae0dU, 0xfa63f738U,
                    };
                    HW_SCE_p_func102(Param_pf5_func102_004);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    static const uint32_t Param_pf5_func100_009[] =
                    {
                        0x82502182U, 0x22ff4b8cU, 0xe9d0dbe5U, 0x54f5f03fU,
                    };
                    HW_SCE_p_func100(Param_pf5_func100_009);
                    HW_SCE_p_func_sub015(0x00009838U, 0x00006032U);
                    RD4_ADDR(REG_2CH, &OutData_Signature[0]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[4]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[8]);

                    static const uint32_t Param_pf5_func100_010[] =
                    {
                        0xfdb80745U, 0x6279cbe8U, 0xd95ccf7eU, 0xa161e06eU,
                    };
                    HW_SCE_p_func100(Param_pf5_func100_010);
                    HW_SCE_p_func_sub015(0x0000982aU, 0x00006032U);
                    RD4_ADDR(REG_2CH, &OutData_Signature[12]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[16]);
                    WAIT_STS(REG_08H, 30, 1);
                    RD4_ADDR(REG_2CH, &OutData_Signature[20]);

                    static const uint32_t Param_pf5_func102_005[] =
                    {
                        0x1ff3be0eU, 0x83392ebbU, 0x45c069f6U, 0x98b61880U,
                    };
                    HW_SCE_p_func102(Param_pf5_func102_005);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
