/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmDecryptInitSub (uint32_t InData_KeyIndex[],
                                          uint32_t InData_IV[],
                                          uint32_t InData_Header[],
                                          uint32_t Header_Len)
{
    uint32_t iLoop             = 0U;
    uint32_t InData_KeyType[1] = {0};

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000a402U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

    static const uint32_t Param_pa4i_func100_001[] =
    {
        0xdfa0448cU, 0x8808b5ccU, 0x04e7721aU, 0xe0a8cb37U,
    };
    HW_SCE_p_func100(Param_pa4i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pa4i_func102_001[] =
        {
            0x3accef6cU, 0xc723ec7bU, 0x5e11e265U, 0x0d206b2fU,
        };
        HW_SCE_p_func102(Param_pa4i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000c00U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_pa4i_func100_002[] =
        {
            0xf7df8c18U, 0x61308fb5U, 0x3c8f45c3U, 0xbf7ada43U,
        };
        HW_SCE_p_func100(Param_pa4i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x000000a4U);

            static const uint32_t Param_pa4i_func101_001[] =
            {
                0xbe8ca322U, 0x1aa1dac3U, 0xbc19dc95U, 0x02f96959U,
            };
            HW_SCE_p_func101(Param_pa4i_func101_001);
            HW_SCE_p_func043();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x00000007U);

            static const uint32_t Param_pa4i_func101_002[] =
            {
                0x07f505ceU, 0x13aa14f5U, 0x6f132873U, 0xca8d4bfcU,
            };
            HW_SCE_p_func101(Param_pa4i_func101_002);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x000000a4U);

            static const uint32_t Param_pa4i_func101_003[] =
            {
                0x1a2be49bU, 0x7cc3669cU, 0x012178baU, 0x053cec45U,
            };
            HW_SCE_p_func101(Param_pa4i_func101_003);
            HW_SCE_p_func068();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x01d04999U);

            static const uint32_t Param_pa4i_func101_004[] =
            {
                0xd6042fb7U, 0x0a34fe79U, 0x38adb011U, 0x3d571f5bU,
            };
            HW_SCE_p_func101(Param_pa4i_func101_004);
        }

        HW_SCE_p_func_sub009(0x800103a0U, 0x000000a4U);

        static const uint32_t Param_pa4i_func101_005[] =
        {
            0xb6d9fef4U, 0x80d9ff64U, 0xad14a781U, 0x7972149bU,
        };
        HW_SCE_p_func101(Param_pa4i_func101_005);
        HW_SCE_p_func044();

        static const uint32_t Param_pa4i_func100_003[] =
        {
            0x9bdde299U, 0xd7bb9828U, 0xd054a005U, 0x5c075b38U,
        };
        HW_SCE_p_func100(Param_pa4i_func100_003);
        HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

        HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

        static const uint32_t Param_pa4i_func100_004[] =
        {
            0x5d7fd712U, 0xc15088b0U, 0x5150fc22U, 0xb8cbcffbU,
        };
        HW_SCE_p_func100(Param_pa4i_func100_004);
        WR1_PROG(REG_A4H, 0x00090805U);
        WR1_PROG(REG_00H, 0x00001213U);
        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        static const uint32_t Param_pa4i_func100_005[] =
        {
            0x8765069fU, 0xd90a7f65U, 0x31f5aae0U, 0x31931d14U,
        };
        HW_SCE_p_func100(Param_pa4i_func100_005);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pa4i_func102_002[] =
            {
                0x21ecde34U, 0x7d279b27U, 0x6576116dU, 0x2654af5eU,
            };
            HW_SCE_p_func102(Param_pa4i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00040885U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_IV[0]);

            HW_SCE_p_func_sub019(0x00060805U, 0x00001113U);

            HW_SCE_p_func_sub021(0x00000734U);

            HW_SCE_p_func_sub021(0x00050804U);

            WR1_PROG(REG_104H, 0x000000b1U);
            WR1_PROG(REG_B0H, 0x40000000U);
            WR1_PROG(REG_A4H, 0x00008e56U);

            for (iLoop = 0U; iLoop < Header_Len; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_Header[iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func205();

            static const uint32_t Param_pa4i_func100_006[] =
            {
                0x56ff7118U, 0xaf0e4a64U, 0xcb88969fU, 0xbe33c357U,
            };
            HW_SCE_p_func100(Param_pa4i_func100_006);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pa4i_func102_003[] =
                {
                    0x78d151e3U, 0x897f0e42U, 0xf2e9a3e7U, 0x3b140c4fU,
                };
                HW_SCE_p_func102(Param_pa4i_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                return FSP_SUCCESS;
            }
        }
    }
}
