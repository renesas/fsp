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

    HW_SCE_p_func_sub001(0x3420a800U, 0x00000003U, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    WR1_PROG(REG_94H, 0x00003420U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func074();

    WR1_PROG(REG_94H, 0x000034a6U);

    static const uint32_t Param_p9a_sub100_001[] =
    {
        0x70bbfc00U, 0xa5677229U, 0xb3df7c5eU, 0x727a6f2cU, 0x0000009aU, 0x2032bc99U, 0xf1d2c2deU, 0x32a44c8eU,
        0xd07ed4b5U, 0x0000009aU, 0x1d4277a1U, 0xa3862c37U, 0x6a28461dU, 0x1b8e3a1aU, 0x00001432U, 0xb93bb137U,
        0x93dcee7eU, 0x545a76f0U, 0x49638153U, 0x00001432U, 0x73afa374U, 0x69a4f094U, 0xfef588dfU, 0x62031a27U,
    };
    HW_SCE_p_func_sub100(InData_KeyIndex, InData_Key, Param_p9a_sub100_001);

    static const uint32_t Param_p9a_func100_001[] =
    {
        0xedc1957aU, 0xa790b1ffU, 0x9196da75U, 0x6b36a4eeU,
    };
    HW_SCE_p_func100(Param_p9a_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p9a_func102_001[] =
        {
            0x50ccc8dcU, 0x6cf7177fU, 0xb36f3fe0U, 0x1fc6940bU,
        };
        HW_SCE_p_func102(Param_p9a_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_94H, 0x00003401U);

        HW_SCE_p_func070_r1(InData_DomainParam);

        WR1_PROG(REG_B8H, 0x00000005U);

        WR1_PROG(REG_A4H, 0x04040010U);

        HW_SCE_p_func_sub017();

        WR1_PROG(REG_14H, 0x00000fc5U);
        WR1_PROG(REG_B0H, 0x0000140fU);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_PubKey[0]);

        WR1_PROG(REG_B0H, 0x00001414U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_PubKey[8]);

        HW_SCE_p_func008();

        static const uint32_t Param_p9a_func100_002[] =
        {
            0x16ea2cb6U, 0x4ea5c4d8U, 0x457b8770U, 0x167cfc85U,
        };
        HW_SCE_p_func100(Param_p9a_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p9a_func102_002[] =
            {
                0x00fd0c66U, 0x8bc71819U, 0xbb08936eU, 0x1b3acd5fU,
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
                0x4c731c18U, 0x8394bf79U, 0x999f3da9U, 0x011a7610U,
            };
            HW_SCE_p_func101(Param_p9a_func101_001);
            HW_SCE_p_func088();

            static const uint32_t Param_p9a_func100_003[] =
            {
                0x9aa56be7U, 0xec4a4a90U, 0x931c1ecbU, 0x9fb2602fU,
            };
            HW_SCE_p_func100(Param_p9a_func100_003);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p9a_func102_003[] =
                {
                    0xbada36b6U, 0xb1a266faU, 0x803c7b19U, 0x766f38c2U,
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
                    0xe8cc660aU, 0xd5b85404U, 0x088acd67U, 0x2159f401U,
                };
                HW_SCE_p_func100(Param_p9a_func100_004);
                WR1_PROG(REG_B0H, 0x00001828U);
                WR1_PROG(REG_08H, 0x00006022U);
                WAIT_STS(REG_08H, 30, 1);
                RD8_ADDR(REG_2CH, &OutData_R[0]);

                static const uint32_t Param_p9a_func100_005[] =
                {
                    0xdcc2a953U, 0x8e3ff986U, 0xa917da34U, 0xec3ce9e1U,
                };
                HW_SCE_p_func100(Param_p9a_func100_005);
                WR1_PROG(REG_B0H, 0x0000182dU);
                WR1_PROG(REG_08H, 0x00006022U);
                WAIT_STS(REG_08H, 30, 1);
                RD8_ADDR(REG_2CH, &OutData_R[8]);

                static const uint32_t Param_p9a_func102_004[] =
                {
                    0x9707deccU, 0x41dffacfU, 0xde1c9557U, 0xf7e46917U,
                };
                HW_SCE_p_func102(Param_p9a_func102_004);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
