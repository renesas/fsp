/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256GcmEncryptInitSub (uint32_t InData_KeyType[], uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00003402U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

    static const uint32_t Param_p34i_func100_001[] =
    {
        0x5c83d115U, 0x47bbe101U, 0x3b128e6aU, 0xe186e4bfU,
    };
    HW_SCE_p_func100(Param_p34i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p34i_func102_001[] =
        {
            0x589de215U, 0x8e3adb05U, 0x80b871ceU, 0x912112a5U,
        };
        HW_SCE_p_func102(Param_p34i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_p34i_func100_002[] =
        {
            0xd22a2787U, 0xe99d6310U, 0x6060c535U, 0xf1e26dfbU,
        };
        HW_SCE_p_func100(Param_p34i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000034U);

            static const uint32_t Param_p34i_func101_001[] =
            {
                0x1d7b989eU, 0x455cf0a7U, 0x0a860ad4U, 0xe6e206a3U,
            };
            HW_SCE_p_func101(Param_p34i_func101_001);
            HW_SCE_p_func043();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x00000007U);

            static const uint32_t Param_p34i_func101_002[] =
            {
                0xb4c60a90U, 0x3c4c5d47U, 0x6285b2daU, 0xa028a374U,
            };
            HW_SCE_p_func101(Param_p34i_func101_002);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000034U);

            static const uint32_t Param_p34i_func101_003[] =
            {
                0x0093caf3U, 0x45983c1dU, 0xad22ee8bU, 0x7829bbe8U,
            };
            HW_SCE_p_func101(Param_p34i_func101_003);
            HW_SCE_p_func068();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x01d04999U);

            static const uint32_t Param_p34i_func101_004[] =
            {
                0xf44f02e2U, 0xd018d03bU, 0x4a557e28U, 0x5ce872c9U,
            };
            HW_SCE_p_func101(Param_p34i_func101_004);
        }

        HW_SCE_p_func_sub009(0x800103a0U, 0x00000034U);

        static const uint32_t Param_p34i_func101_005[] =
        {
            0x40128d5eU, 0xc2dc411cU, 0x6b69cf4bU, 0xb8605269U,
        };
        HW_SCE_p_func101(Param_p34i_func101_005);
        HW_SCE_p_func044();

        static const uint32_t Param_p34i_func100_003[] =
        {
            0x3dadf477U, 0xaa79b613U, 0xe024c3e0U, 0x6739d560U,
        };
        HW_SCE_p_func100(Param_p34i_func100_003);
        HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

        HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

        static const uint32_t Param_p34i_func100_004[] =
        {
            0x0dc0d94dU, 0x916dcb2aU, 0x0abb86a0U, 0x6c1b2403U,
        };
        HW_SCE_p_func100(Param_p34i_func100_004);
        WR1_PROG(REG_A4H, 0x00090805U);
        WR1_PROG(REG_00H, 0x00001213U);
        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        static const uint32_t Param_p34i_func100_005[] =
        {
            0x653cab86U, 0x62f0afbeU, 0x0e891ff6U, 0x6f16d588U,
        };
        HW_SCE_p_func100(Param_p34i_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p34i_func102_002[] =
            {
                0x8bbd7bcbU, 0xb89b00efU, 0xa480cd72U, 0xbc8671cfU,
            };
            HW_SCE_p_func102(Param_p34i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000368U);
            WR1_PROG(REG_E0H, 0x80040080U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_IV[0]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_IV[1]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_IV[2]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_IV[3]);

            WR1_PROG(REG_7CH, 0x00000001U);
            WR1_PROG(REG_7CH, 0x00000041U);

            WR1_PROG(REG_104H, 0x00000051U);
            WR1_PROG(REG_B0H, 0x40000000U);
            WR1_PROG(REG_A4H, 0x00008a84U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));

            WR1_PROG(REG_00H, 0x00005113U);
            WR1_PROG(REG_74H, 0x00001000U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_74H, 0x00000004U);
            WR1_PROG(REG_104H, 0x00000354U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                     change_endian_long(0x00000000U), change_endian_long(0x00000000U));

            WR1_PROG(REG_74H, 0x00000002U);

            return FSP_SUCCESS;
        }
    }
}
