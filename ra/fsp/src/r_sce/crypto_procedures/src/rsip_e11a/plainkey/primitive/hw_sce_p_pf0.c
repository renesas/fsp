/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EcdsaSignatureGenerateSub (const uint32_t InData_CurveType[],
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

    WR1_PROG(REG_70H, 0x00f00001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x3420a800U, 0x00000003U, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    HW_SCE_p_func070_r1(InData_DomainParam);

    static const uint32_t Param_pf0_func100_001[] =
    {
        0x8f60d052U, 0xeadcdd69U, 0x08d746bcU, 0xf3fa82f9U,
    };
    HW_SCE_p_func100(Param_pf0_func100_001);

    WR1_PROG(REG_B0H, 0x0000140fU);
    HW_SCE_p_func103();
    static const uint32_t Param_pf0_func100_002[] =
    {
        0x5eef15a3U, 0xefca12ddU, 0xc58aa9efU, 0xfccab30cU,
    };
    HW_SCE_p_func100(Param_pf0_func100_002);
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub002(0x00c10011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);
    HW_SCE_p_func_sub002(0x00c10011U);

    WR1_PROG(REG_B0H, 0x00001428U);
    HW_SCE_p_func_sub002(0x00c0001dU);
    HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

    WR1_PROG(REG_B0H, 0x00001419U);
    HW_SCE_p_func_sub002(0x00c0001dU);
    HW_SCE_p_func_sub011(0x000000a5U, 0x00000002U);

    HW_SCE_p_func_sub003(0x0019000aU, 0x00140000U, 0x0404000aU);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B8H, 0x00000014U);

    WR1_PROG(REG_A4H, 0x04040010U);

    HW_SCE_p_func_sub017();

    HW_SCE_p_func_sub003(0x0028000fU, 0x002d0014U, 0x04040002U);

    HW_SCE_p_func_sub003(0x0028002dU, 0x00320000U, 0x04040009U);

    HW_SCE_p_func071_r1(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_pf0_func101_001[] =
    {
        0xf9e35f7dU, 0x7538ea3bU, 0x5fab3e1fU, 0x06db957aU,
    };
    HW_SCE_p_func101(Param_pf0_func101_001);
    HW_SCE_p_func088();

    static const uint32_t Param_pf0_func100_003[] =
    {
        0xaaf87e98U, 0xe8e3ec7eU, 0xce77ae89U, 0x9572cbaeU,
    };
    HW_SCE_p_func100(Param_pf0_func100_003);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pf0_func102_001[] =
        {
            0xc815d4cfU, 0xf1790d98U, 0xa66a0668U, 0x3b5401e7U,
        };
        HW_SCE_p_func102(Param_pf0_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_B8H, 0x0000000aU);

        WR1_PROG(REG_A4H, 0x04040010U);

        HW_SCE_p_func_sub017();

        HW_SCE_p_func_sub003(0x005a0028U, 0x002d000aU, 0x04040002U);

        WR1_PROG(REG_14H, 0x000000a5U);
        WR1_PROG(REG_B0H, 0x0000140fU);
        HW_SCE_p_func_sub002(0x00c0001dU);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

        HW_SCE_p_func_sub003(0x000f002dU, 0x0028000aU, 0x04040002U);

        HW_SCE_p_func_sub003(0x000f0028U, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_pf0_func100_004[] =
        {
            0xfdbaed1cU, 0xd56ce5beU, 0x639635d2U, 0xcacc94b9U,
        };
        HW_SCE_p_func100(Param_pf0_func100_004);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_pf0_func102_002[] =
            {
                0xd2c4ec5dU, 0x25fc2807U, 0xc3e3dac8U, 0xb2c34828U,
            };
            HW_SCE_p_func102(Param_pf0_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            static const uint32_t Param_pf0_func100_005[] =
            {
                0xaf54dd06U, 0x6f470315U, 0x0e2b326dU, 0xa4ee0942U,
            };
            HW_SCE_p_func100(Param_pf0_func100_005);
            WR1_PROG(REG_B0H, 0x00001414U);
            HW_SCE_p_func_sub002(0x00c0001dU);
            HW_SCE_p_func_sub011(0x000000a5U, 0x00000002U);

            HW_SCE_p_func_sub003(0x0014000aU, 0x000f0000U, 0x0404000aU);

            WR1_PROG(REG_B4H, 0x000f0032U);
            WR1_PROG(REG_B8H, 0x0014000aU);

            WR1_PROG(REG_A4H, 0x04040000U);
            WR1_PROG(REG_08H, 0x00020000U);
            HW_SCE_p_func_sub017();
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func_sub003(0x005a0014U, 0x000f000aU, 0x04040002U);

            WR1_PROG(REG_14H, 0x000007c5U);
            WR1_PROG(REG_B0H, 0x00001414U);
            WAIT_STS(REG_14H, 31, 1);
            WR8_ADDR(REG_2CH, &InData_MsgDgst[0]);

            HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
            WR1_PROG(REG_2CH, InData_KeyMode[0]);
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func074();

            WR1_PROG(REG_94H, 0x000034a6U);

            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f0U));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_pf0_func101_002[] =
            {
                0xe9688cf8U, 0x0684aeddU, 0x9b01425bU, 0x309ba160U,
            };
            HW_SCE_p_func101(Param_pf0_func101_002);
            HW_SCE_p_func441(InData_KeyIndex, InData_Key);

            static const uint32_t Param_pf0_func100_006[] =
            {
                0x25e17c4eU, 0x6ed1498eU, 0xc45ca961U, 0x41c70219U,
            };
            HW_SCE_p_func100(Param_pf0_func100_006);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_pf0_func102_003[] =
                {
                    0x47d80defU, 0x2b6d3d87U, 0x53234de4U, 0x059690c4U,
                };
                HW_SCE_p_func102(Param_pf0_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                HW_SCE_p_func_sub003(0x005a001eU, 0x0019000aU, 0x04040002U);

                HW_SCE_p_func_sub003(0x00280019U, 0x001e000aU, 0x04040002U);

                HW_SCE_p_func_sub003(0x001e0014U, 0x0019000aU, 0x04040005U);

                HW_SCE_p_func_sub003(0x0019000fU, 0x001e000aU, 0x04040002U);

                WR1_PROG(REG_B0H, 0x0000140fU);
                HW_SCE_p_func_sub002(0x00c0001dU);
                HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

                HW_SCE_p_func_sub003(0x000f001eU, 0x00140000U, 0x0404000aU);

                WR1_PROG(REG_40H, 0x00210000U);

                static const uint32_t Param_pf0_func100_007[] =
                {
                    0xedde16e8U, 0xbe10469dU, 0xc73514eeU, 0xa47c9984U,
                };
                HW_SCE_p_func100(Param_pf0_func100_007);
                WR1_PROG(REG_40H, 0x00400000U);
                WR1_PROG(REG_24H, 0x00000000U);

                if (CHCK_STS(REG_40H, 22, 1))
                {
                    static const uint32_t Param_pf0_func102_004[] =
                    {
                        0x7817805dU, 0x730368a4U, 0x845fb78cU, 0x1640c819U,
                    };
                    HW_SCE_p_func102(Param_pf0_func102_004);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    static const uint32_t Param_pf0_func100_008[] =
                    {
                        0xbf6257d8U, 0xb25ef455U, 0x947923ceU, 0xf801f46aU,
                    };
                    HW_SCE_p_func100(Param_pf0_func100_008);
                    WR1_PROG(REG_B0H, 0x00001828U);
                    WR1_PROG(REG_08H, 0x00006022U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD8_ADDR(REG_2CH, &OutData_Signature[0]);

                    static const uint32_t Param_pf0_func100_009[] =
                    {
                        0x18c1b438U, 0x4ea35b53U, 0xeaca3ffcU, 0xb823f43cU,
                    };
                    HW_SCE_p_func100(Param_pf0_func100_009);
                    WR1_PROG(REG_B0H, 0x0000181eU);
                    WR1_PROG(REG_08H, 0x00006022U);
                    WAIT_STS(REG_08H, 30, 1);
                    RD8_ADDR(REG_2CH, &OutData_Signature[8]);

                    static const uint32_t Param_pf0_func102_005[] =
                    {
                        0xc5f3de79U, 0xe3a399f8U, 0x7e14aa06U, 0xf241b6ffU,
                    };
                    HW_SCE_p_func102(Param_pf0_func102_005);
                    WR1_PROG(REG_6CH, 0x00000040U);
                    WAIT_STS(REG_20H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
