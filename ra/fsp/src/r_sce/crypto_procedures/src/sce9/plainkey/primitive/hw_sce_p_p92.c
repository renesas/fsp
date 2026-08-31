/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_SelfCheck3Sub (void)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00009203U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x000001f0U);

    HW_SCE_p_func_sub007(0x00003bfeU, 0x38008be0U, 0x2e24c972U, 0x00A60000U);

    static const uint32_t Param_p92_func100_001[] =
    {
        0x7252ffb3U, 0xa4f2970fU, 0xccf82b60U, 0xfaf63abcU,
    };
    HW_SCE_p_func100(Param_p92_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        HW_SCE_p_func_sub012(0x00000052U, 0x00093b8cU, 0x01c7ba56U);

        HW_SCE_p_func_sub012(0x00000052U, 0x00070804U, 0x00000000U);

        HW_SCE_p_func_sub022(0x3000a820U, 0x00000003U, 0x00010020U, 0x00000821U);
        WR1_PROG(REG_ECH, 0x00000080U);

        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00000008U);
        WAIT_STS(REG_64H, 11, 0);
        WR1_PROG(REG_64H, 0x00002008U);

        HW_SCE_p_func_sub022(0x00000863U, 0x00000884U, 0x000008a5U, 0x0000b4c0U);
        HW_SCE_p_func_sub022(0x00000013U, 0x0000b4e0U, 0x00000348U, 0x0000b500U);
        WR1_PROG(REG_ECH, 0x000000b7U);

        for (jLoop = 0U; jLoop < 1U; jLoop++)
        {
            static const uint32_t Param_p92_func100_002[] =
            {
                0x79c46a3cU, 0x0ae625b1U, 0x2ec940fdU, 0xfd6753fbU,
            };
            HW_SCE_p_func100(Param_p92_func100_002);
            WR1_PROG(REG_ECH, 0x00007c01U);
            WR1_PROG(REG_1CH, 0x00600000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
            {
                WAIT_STS(REG_64H, 11, 0);
                WR1_PROG(REG_64H, 0x0020901cU);

                static const uint32_t Param_p92_func101_001[] =
                {
                    0x584ce62cU, 0x7c8ea760U, 0x07dd1294U, 0x228e5267U,
                };
                HW_SCE_p_func101(Param_p92_func101_001);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
            {
                WAIT_STS(REG_64H, 11, 0);
                WR1_PROG(REG_64H, 0x0020901eU);

                static const uint32_t Param_p92_func101_002[] =
                {
                    0x7c885349U, 0x7333bee5U, 0x63655723U, 0x31e16865U,
                };
                HW_SCE_p_func101(Param_p92_func101_002);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
            {
                WAIT_STS(REG_64H, 11, 0);
                WR1_PROG(REG_64H, 0x0020901dU);

                static const uint32_t Param_p92_func101_003[] =
                {
                    0x796ca859U, 0x963097eaU, 0x416c1f4dU, 0x6acf9612U,
                };
                HW_SCE_p_func101(Param_p92_func101_003);
            }

            WR1_PROG(REG_C4H, 0x41001e5eU);
            WR1_PROG(REG_00H, 0x80002401U);
            WAIT_STS(REG_64H, 11, 0);
            WR1_PROG(REG_1CH, 0x00001200U);
            WAIT_STS(REG_00H, 30, 0);
            WR1_PROG(REG_00H, 0x00000001U);
            WR1_PROG(REG_C4H, 0x00000000U);

            WAIT_STS(REG_64H, 11, 0);
            WR1_PROG(REG_64H, 0x0010B008U);

            WR1_PROG(REG_ECH, 0x00000800U);
            HW_SCE_p_func_sub010(0x80900000U, 0x00008443U);

            HW_SCE_p_func_sub022(0x000038a0U, 0x00003405U, 0x00002804U, 0x342028e0U);
            HW_SCE_p_func_sub022(0x10005066U, 0x34202808U, 0x10005066U, 0x00003485U);

            static const uint32_t Param_p92_func101_004[] =
            {
                0xa8ec0974U, 0x20eb43a5U, 0x794d25d7U, 0x4bdd0550U,
            };
            HW_SCE_p_func101(Param_p92_func101_004);
        }

        HW_SCE_p_func_sub022(0x0000b4e0U, 0x0000005AU, 0x00000842U, 0x000008c6U);

        HW_SCE_p_func_sub022(0x0000b480U, 0x00000004U, 0x0000b4a0U, 0x00000002U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            HW_SCE_p_func_sub022(0x01003804U, 0x342028e0U, 0x10005066U, 0x00002440U);

            WR1_PROG(REG_ECH, 0x00002cc0U);

            WR1_PROG(REG_ECH, 0x00002485U);
        }

        HW_SCE_p_func_sub007(0x00002c20U, 0x38008840U, 0x00000100U, 0x00260000U);

        WR1_PROG(REG_1CH, 0x00402000U);

        HW_SCE_p_func_sub022(0x0000b4e0U, 0x00000033U, 0x0000b480U, 0x0000003cU);

        HW_SCE_p_func_sub022(0x01003804U, 0x342028e0U, 0x10005066U, 0x00002cc0U);

        HW_SCE_p_func_sub022(0x0000b480U, 0x0000003eU, 0x01003804U, 0x342028e0U);
        HW_SCE_p_func_sub007(0x10005066U, 0x38008860U, 0x00000000U, 0x00A60000U);

        static const uint32_t Param_p92_func100_003[] =
        {
            0x61e61c3dU, 0x30283a89U, 0x5909828eU, 0xa7699c6eU,
        };
        HW_SCE_p_func100(Param_p92_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p92_func102_001[] =
            {
                0x4e350eeeU, 0xd9878500U, 0xcc805ef3U, 0x77d220feU,
            };
            HW_SCE_p_func102(Param_p92_func102_001);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_RETRY;
        }
        else
        {
            WAIT_STS(REG_64H, 11, 0);
            WR1_PROG(REG_64H, 0x0000001cU);

            HW_SCE_p_func_sub012(0x00000052U, 0x01000cc4U, 0x00000000U);
            HW_SCE_p_func_sub010(0x80040000U, 0x00008213U);

            HW_SCE_p_func_sub013(0x41001eddU, 0x00002413U);

            WAIT_STS(REG_64H, 11, 0);
            WR1_PROG(REG_64H, 0x00000000U);
            HW_SCE_p_func_sub010(0x80040080U, 0x00008213U);

            static const uint32_t Param_p92_func100_004[] =
            {
                0x99af7425U, 0x2113d46aU, 0xff58fb18U, 0x24edfe4bU,
            };
            HW_SCE_p_func100(Param_p92_func100_004);
            HW_SCE_p_func_sub012(0x00000052U, 0x000b0804U, 0x00000000U);

            WR1_PROG(REG_104H, 0x00000352U);
            WR1_PROG(REG_C4H, 0x00070805U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                     change_endian_long(0x00000000U), change_endian_long(0x00000001U));

            static const uint32_t Param_p92_func100_005[] =
            {
                0x094f8766U, 0x911c9512U, 0xfb3f4bbdU, 0x460e53e2U,
            };
            HW_SCE_p_func100(Param_p92_func100_005);
            WR1_PROG(REG_D0H, 0x00000100U);
            WR1_PROG(REG_C4H, 0x0100b7f7U);
            HW_SCE_p_func_sub010(0x81080000U, 0x00002823U);

            HW_SCE_p_func_sub013(0x000b0805U, 0x00002213U);

            HW_SCE_p_func_sub013(0x00070805U, 0x00002213U);

            static const uint32_t Param_p92_func100_006[] =
            {
                0x0b1343bfU, 0xfa20139bU, 0xb28498c2U, 0x9a061f91U,
            };
            HW_SCE_p_func100(Param_p92_func100_006);
            HW_SCE_p_func103();
            static const uint32_t Param_p92_func100_007[] =
            {
                0x27268344U, 0xed4d73cbU, 0x2e42dad1U, 0x2e6e640bU,
            };
            HW_SCE_p_func100(Param_p92_func100_007);
            HW_SCE_p_func_sub012(0x00000052U, 0x010d0c04U, 0x00000000U);

            static const uint32_t Param_p92_func100_008[] =
            {
                0xb3878676U, 0x7e57894eU, 0xd6748786U, 0x77254975U,
            };
            HW_SCE_p_func100(Param_p92_func100_008);
            HW_SCE_p_func103();
            static const uint32_t Param_p92_func100_009[] =
            {
                0xa50fc7c5U, 0x110c56e9U, 0xad65e984U, 0x00e91a6cU,
            };
            HW_SCE_p_func100(Param_p92_func100_009);
            HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

            WR1_PROG(REG_04H, 0x00000212U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &S_RAM[24]);
            S_RAM[24] = change_endian_long(S_RAM[24]);
            S_RAM[25] = change_endian_long(S_RAM[25]);
            S_RAM[26] = change_endian_long(S_RAM[26]);
            S_RAM[27] = change_endian_long(S_RAM[27]);

            WR1_PROG(REG_13CH, 0x00000202U);

            static const uint32_t Param_p92_func102_002[] =
            {
                0x079c4c8cU, 0x962acb2eU, 0x9a5c0aebU, 0x6ec75008U,
            };
            HW_SCE_p_func102(Param_p92_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
    else
    {
        static const uint32_t Param_p92_func100_010[] =
        {
            0x6b276b23U, 0x11089165U, 0x87325daaU, 0x63f67f53U,
        };
        HW_SCE_p_func100(Param_p92_func100_010);
        HW_SCE_p_func103();
        static const uint32_t Param_p92_func100_011[] =
        {
            0x9eb0ec5fU, 0xd6b216c4U, 0xe5b5cb54U, 0x17139ef3U,
        };
        HW_SCE_p_func100(Param_p92_func100_011);
        HW_SCE_p_func_sub012(0x00000052U, 0x010d0c04U, 0x00000000U);

        static const uint32_t Param_p92_func100_012[] =
        {
            0x19d71d04U, 0xf4910acdU, 0x09b90550U, 0x57b49033U,
        };
        HW_SCE_p_func100(Param_p92_func100_012);
        HW_SCE_p_func103();
        static const uint32_t Param_p92_func100_013[] =
        {
            0x0f03b51cU, 0x5b024757U, 0x31ea3b4dU, 0xf4eb1056U,
        };
        HW_SCE_p_func100(Param_p92_func100_013);
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        WR1_PROG(REG_04H, 0x00000212U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_RAM[24]);
        S_RAM[24] = change_endian_long(S_RAM[24]);
        S_RAM[25] = change_endian_long(S_RAM[25]);
        S_RAM[26] = change_endian_long(S_RAM[26]);
        S_RAM[27] = change_endian_long(S_RAM[27]);

        WR1_PROG(REG_13CH, 0x00000202U);

        static const uint32_t Param_p92_func102_003[] =
        {
            0x974ace4aU, 0xbf7d7d22U, 0xfbcbcfc6U, 0xdd8d0fe8U,
        };
        HW_SCE_p_func102(Param_p92_func102_003);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
