/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256GcmDecryptInitSub (uint32_t InData_KeyType[], uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00003602U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

    static const uint32_t Param_p36i_func100_001[] =
    {
        0xc5da3597U, 0x37bf9b10U, 0x008368c1U, 0xfdf8df45U,
    };
    HW_SCE_p_func100(Param_p36i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p36i_func102_001[] =
        {
            0xb8b16d09U, 0x0643ae78U, 0x57c11036U, 0xc4405e37U,
        };
        HW_SCE_p_func102(Param_p36i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_p36i_func100_002[] =
        {
            0x626ec7dcU, 0x709c9515U, 0x20150b19U, 0x178820bfU,
        };
        HW_SCE_p_func100(Param_p36i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000036U);

            static const uint32_t Param_p36i_func101_001[] =
            {
                0x8260f9e5U, 0x616709ecU, 0x02ba382fU, 0x60d2afd9U,
            };
            HW_SCE_p_func101(Param_p36i_func101_001);
            HW_SCE_p_func043();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x00000007U);

            static const uint32_t Param_p36i_func101_002[] =
            {
                0x80a68b65U, 0xc994bf2dU, 0x7381ef5eU, 0x7b7e6c45U,
            };
            HW_SCE_p_func101(Param_p36i_func101_002);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000036U);

            static const uint32_t Param_p36i_func101_003[] =
            {
                0x31aee683U, 0x3f10f504U, 0xfce9b013U, 0x788f231bU,
            };
            HW_SCE_p_func101(Param_p36i_func101_003);
            HW_SCE_p_func068();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x01d04999U);

            static const uint32_t Param_p36i_func101_004[] =
            {
                0xf6edbc33U, 0x5a7d5709U, 0x20602a3fU, 0xb1116a90U,
            };
            HW_SCE_p_func101(Param_p36i_func101_004);
        }

        HW_SCE_p_func_sub009(0x800103a0U, 0x00000036U);

        static const uint32_t Param_p36i_func101_005[] =
        {
            0x9de30cd0U, 0x0a74e31bU, 0xcddf65daU, 0x662e9af5U,
        };
        HW_SCE_p_func101(Param_p36i_func101_005);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

        WR1_PROG(REG_E0H, 0x80080000U);
        WR1_PROG(REG_00H, 0x00008223U);
        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        static const uint32_t Param_p36i_func100_003[] =
        {
            0x8e70b58cU, 0xd001ee91U, 0x5ae7a0b3U, 0xf136c4d9U,
        };
        HW_SCE_p_func100(Param_p36i_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p36i_func102_002[] =
            {
                0xa9e6f3aeU, 0xacd0bfaaU, 0xe005a0fdU, 0xae5b258aU,
            };
            HW_SCE_p_func102(Param_p36i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            static const uint32_t Param_p36i_func100_004[] =
            {
                0xb06163bdU, 0x5e4525d5U, 0x8415ba90U, 0x28857abbU,
            };
            HW_SCE_p_func100(Param_p36i_func100_004);
            WR1_PROG(REG_E0H, 0x81080000U);
            HW_SCE_p_func_sub013(0x00080805U, 0x00002813U);

            static const uint32_t Param_p36i_func100_005[] =
            {
                0x2ed25b81U, 0x0831d289U, 0xc21be4dfU, 0xbe708663U,
            };
            HW_SCE_p_func100(Param_p36i_func100_005);
            HW_SCE_p_func_sub013(0x00090805U, 0x00002813U);

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

            HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x00008a84U);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));

            WR1_PROG(REG_00H, 0x00005213U);
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
