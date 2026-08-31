/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub (const uint32_t InData_CurveType[],
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

    WR1_PROG(REG_70H, 0x009a0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_A0H, 0x20010000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub001(0x3420a800U, 0x00000003U, 0x2000b400U, 0x00000002U);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func074();

    WR1_PROG(REG_94H, 0x000034a6U);

    static const uint32_t Param_p9a_sub100_001[] =
    {
        0xa820e618U, 0xdab6761dU, 0xd63418faU, 0xd703ebfeU, 0x0000009aU, 0xd3098547U, 0xcc26bcb1U, 0x9fc8d691U,
        0x7635d3aeU, 0x0000009aU, 0x88343d90U, 0x2b58ed2fU, 0x17b810a2U, 0xc9b59e17U, 0x00001432U, 0x3a287061U,
        0x2a230bb7U, 0x0c356758U, 0xfb61093aU, 0x00001432U, 0xfcacad1aU, 0x4b3d5de0U, 0x61db2c1eU, 0xdb30c9efU,
    };
    HW_SCE_p_func_sub100(InData_KeyIndex, InData_Key, Param_p9a_sub100_001, RSIP_SEL_BIT_LENGTH_256);

    static const uint32_t Param_p9a_func100_001[] =
    {
        0xd1e511b6U, 0x864427d8U, 0xaac39985U, 0xc5c264afU,
    };
    HW_SCE_p_func100(Param_p9a_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p9a_func102_001[] =
        {
            0xf8b3a65eU, 0x0feead67U, 0x3f0cecadU, 0xe971497cU,
        };
        HW_SCE_p_func102(Param_p9a_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_94H, 0x00003401U);

        HW_SCE_p_func070(InData_DomainParam);

        WR1_PROG(REG_B8H, 0x00000005U);

        WR1_PROG(REG_A4H, 0x04040010U);

        HW_SCE_p_func_sub012();

        HW_SCE_p_func_sub017(0x00000fc5U, 0x0000140fU);
        WR8_ADDR(REG_2CH, &InData_PubKey[0]);

        WR1_PROG(REG_B0H, 0x00001414U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_PubKey[8]);

        HW_SCE_p_func008();

        static const uint32_t Param_p9a_func100_002[] =
        {
            0x46d2046dU, 0x749ecfacU, 0x7666dff8U, 0x4d6fff2bU,
        };
        HW_SCE_p_func100(Param_p9a_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p9a_func102_002[] =
            {
                0x89f5874cU, 0xe86afc4aU, 0x05ebe120U, 0x3085b0afU,
            };
            HW_SCE_p_func102(Param_p9a_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
            WR1_PROG(REG_2CH, change_endian_long(0x0000009aU));
            WR1_PROG(REG_24H, 0x00000000U);

            static const uint32_t Param_p9a_func101_001[] =
            {
                0xf860a957U, 0x7b127890U, 0x36b15afcU, 0xd294428bU,
            };
            HW_SCE_p_func101(Param_p9a_func101_001);
            HW_SCE_p_func088();

            static const uint32_t Param_p9a_func100_003[] =
            {
                0x6ed553f7U, 0x197e36f2U, 0x9084d0f2U, 0x144b9ab5U,
            };
            HW_SCE_p_func100(Param_p9a_func100_003);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p9a_func102_003[] =
                {
                    0x395234eeU, 0x7f3e77f3U, 0x0eff5cccU, 0xf8eb73bcU,
                };
                HW_SCE_p_func102(Param_p9a_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p9a_func100_004[] =
                {
                    0xb11338c2U, 0x208c6a40U, 0xb321da10U, 0x58e89618U,
                };
                HW_SCE_p_func100(Param_p9a_func100_004);
                HW_SCE_p_func_sub015(0x00001828U, 0x00006022U);
                RD8_ADDR(REG_2CH, &OutData_R[0]);

                static const uint32_t Param_p9a_func100_005[] =
                {
                    0x0c80998fU, 0xb96d0eb3U, 0xd930ad6fU, 0xed342749U,
                };
                HW_SCE_p_func100(Param_p9a_func100_005);
                HW_SCE_p_func_sub015(0x0000182dU, 0x00006022U);
                RD8_ADDR(REG_2CH, &OutData_R[8]);

                static const uint32_t Param_p9a_func102_004[] =
                {
                    0x9ea457f8U, 0x7041c0b8U, 0x3f5ce921U, 0x563fd987U,
                };
                HW_SCE_p_func102(Param_p9a_func102_004);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
