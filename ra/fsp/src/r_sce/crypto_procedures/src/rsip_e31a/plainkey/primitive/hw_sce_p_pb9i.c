/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256XtsEncryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00b90001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub010(0x38000c00U, 0x00270000U);

    static const uint32_t Param_pb9i_func100_001[] =
    {
        0xbc58ffa4U, 0x66e86658U, 0xae21fb9eU, 0xa2d2ed97U,
    };
    HW_SCE_p_func100(Param_pb9i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x800100c0U);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x000000b9U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_pb9i_func101_001[] =
        {
            0x3b772c0bU, 0xdc5a8034U, 0x477ae103U, 0x14709ad7U,
        };
        HW_SCE_p_func101(Param_pb9i_func101_001);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x0000b4c0U);
        WR1_PROG(REG_94H, 0x00000009U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x000000b9U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_pb9i_func101_002[] =
        {
            0x082b134fU, 0x1b701b8cU, 0x5224b998U, 0xca447d3eU,
        };
        HW_SCE_p_func101(Param_pb9i_func101_002);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub007(0x000007c1U, 0x40000100U, 0xf7009d07U);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_B0H, 0x00001404U);
        HW_SCE_p_func_sub003(0x00c10021U);

        HW_SCE_p_func_sub007(0x000007c1U, 0x40000100U, 0xf7008d07U);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[9]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[13]);

        WR1_PROG(REG_B0H, 0x00001408U);
        HW_SCE_p_func_sub003(0x00c10021U);

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[17]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        HW_SCE_p_func_sub003(0x00410011U);

        static const uint32_t Param_pb9i_func101_003[] =
        {
            0xa1c68f2eU, 0x4372453dU, 0xf828428dU, 0x5d98b071U,
        };
        HW_SCE_p_func101(Param_pb9i_func101_003);
    }
    else
    {
        HW_SCE_p_func_sub017(0x00000fc5U, 0x00003408U);
        WR4_ADDR(REG_2CH, &InData_Key[0]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Key[4]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Key[8]);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Key[12]);

        static const uint32_t Param_pb9i_func101_004[] =
        {
            0xc4a635f5U, 0xaaa0502dU, 0xdf906d63U, 0xa0498c31U,
        };
        HW_SCE_p_func101(Param_pb9i_func101_004);
    }

    static const uint32_t Param_pb9i_func100_002[] =
    {
        0xa8b924e4U, 0x616999ceU, 0xdbf42139U, 0x086aff61U,
    };
    HW_SCE_p_func100(Param_pb9i_func100_002);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_pb9i_func102_001[] =
        {
            0x483e0c5bU, 0x2e98aa5eU, 0x27f839e4U, 0xa33d7696U,
        };
        HW_SCE_p_func102(Param_pb9i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_pb9i_func100_003[] =
        {
            0xae0072beU, 0xc18d7f81U, 0xcf1a8718U, 0xc17a25dcU,
        };
        HW_SCE_p_func100(Param_pb9i_func100_003);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00001808U);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_pb9i_func100_004[] =
        {
            0xbfc28499U, 0x74748b78U, 0x6cc30f16U, 0x742dfa14U,
        };
        HW_SCE_p_func100(Param_pb9i_func100_004);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);
        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x0a008045U);
        WR4_ADDR(REG_2CH, &InData_IV[0]);

        static const uint32_t Param_pb9i_func100_005[] =
        {
            0x21da2602U, 0xfb9b9304U, 0x27d17cd0U, 0x2c7a136fU,
        };
        HW_SCE_p_func100(Param_pb9i_func100_005);
        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00001804U);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_pb9i_func100_006[] =
        {
            0x94595a17U, 0x8052d174U, 0x975c8f7bU, 0x2787dfffU,
        };
        HW_SCE_p_func100(Param_pb9i_func100_006);
        WR1_PROG(REG_D0H, 0x08000095U);
        HW_SCE_p_func_sub003(0x00430011U);

        static const uint32_t Param_pb9i_func101_005[] =
        {
            0x3f014623U, 0xc6f70cebU, 0x1833df55U, 0x9766e73eU,
        };
        HW_SCE_p_func101(Param_pb9i_func101_005);

        return FSP_SUCCESS;
    }
}
