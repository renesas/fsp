/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

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

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x3420a800U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_94H, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    WR1_PROG(REG_94H, 0x00003420U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0x40e3ed33U, 0x97540bf1U, 0x1ba66973U, 0xe0262f8aU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);
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
        WR1_PROG(REG_2CH, change_endian_long(0x0000009aU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x6a7ed1c3U, 0xfea2fa3fU, 0x357f4e5bU, 0xdc0bea3dU);
        HW_SCE_p_func043();

        HW_SCE_p_func074();

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x0000009aU));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x971df8dcU, 0x3e4c018eU, 0x533e3d57U, 0x0a777968U);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000007c1U);
        WR1_PROG(REG_D4H, 0x40000100U);
        WR1_PROG(REG_D0H, 0xf7009d07U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_B0H, 0x00001432U);
        WR1_PROG(REG_00H, 0x00c10021U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[9]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func101(0xb93bb137U, 0x93dcee7eU, 0x545a76f0U, 0x49638153U);
    }
    else
    {
        WR1_PROG(REG_14H, 0x000007c5U);
        WR1_PROG(REG_B0H, 0x00001432U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_Key[0]);

        HW_SCE_p_func101(0xaa9429c0U, 0x259d1369U, 0xbb725b66U, 0xbfb85f8dU);
    }

    HW_SCE_p_func100(0xedc1957aU, 0xa790b1ffU, 0x9196da75U, 0x6b36a4eeU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x50ccc8dcU, 0x6cf7177fU, 0xb36f3fe0U, 0x1fc6940bU);
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

        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_14H, 0x00000fc5U);
        WR1_PROG(REG_B0H, 0x0000140fU);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_PubKey[0]);

        WR1_PROG(REG_B0H, 0x00001414U);
        WAIT_STS(REG_14H, 31, 1);
        WR8_ADDR(REG_2CH, &InData_PubKey[8]);

        HW_SCE_p_func008();

        HW_SCE_p_func100(0x16ea2cb6U, 0x4ea5c4d8U, 0x457b8770U, 0x167cfc85U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x00fd0c66U, 0x8bc71819U, 0xbb08936eU, 0x1b3acd5fU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x0000009aU));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x4c731c18U, 0x8394bf79U, 0x999f3da9U, 0x011a7610U);
            HW_SCE_p_func088();

            HW_SCE_p_func100(0x9aa56be7U, 0xec4a4a90U, 0x931c1ecbU, 0x9fb2602fU);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0xbada36b6U, 0xb1a266faU, 0x803c7b19U, 0x766f38c2U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xe8cc660aU, 0xd5b85404U, 0x088acd67U, 0x2159f401U);
                WR1_PROG(REG_B0H, 0x00001828U);
                WR1_PROG(REG_08H, 0x00006022U);
                WAIT_STS(REG_08H, 30, 1);
                RD8_ADDR(REG_2CH, &OutData_R[0]);

                HW_SCE_p_func100(0xdcc2a953U, 0x8e3ff986U, 0xa917da34U, 0xec3ce9e1U);
                WR1_PROG(REG_B0H, 0x0000182dU);
                WR1_PROG(REG_08H, 0x00006022U);
                WAIT_STS(REG_08H, 30, 1);
                RD8_ADDR(REG_2CH, &OutData_R[8]);

                HW_SCE_p_func102(0x9707deccU, 0x41dffacfU, 0xde1c9557U, 0xf7e46917U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
