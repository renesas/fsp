/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_OemKeyIndexValidationSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00700001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func049(InData_Cmd);

    HW_SCE_p_func_sub001(0x0000b440U, 0x2C8003A0U, 0x000034a4U);

    HW_SCE_p_func_sub001(0x38008880U, 0x00000023U, 0x1000b480U);
    WR1_PROG(REG_94H, 0x00000005U);

    HW_SCE_p_func056();

    static const uint32_t Param_p70_func100_001[] =
    {
        0x5d7279a3U, 0x1330fbb0U, 0xa50ab7daU, 0x66da9720U,
    };
    HW_SCE_p_func100(Param_p70_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p70_func102_001[] =
        {
            0xe972e450U, 0x0e395792U, 0x21afb1b4U, 0xd50886dfU,
        };
        HW_SCE_p_func102(Param_p70_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_94H, 0x00003485U);

        HW_SCE_p_func_sub005(0x000000c7U, 0x800100c0U);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p70_func101_001[] =
        {
            0xb6d78302U, 0x3da6bdc1U, 0x5f13936dU, 0x4b6222d7U,
        };
        HW_SCE_p_func101(Param_p70_func101_001);
        HW_SCE_p_func043_r1();

        WR1_PROG(REG_94H, 0x000034c4U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p70_func101_002[] =
        {
            0xc3074b27U, 0x6c985a0eU, 0xc068e8ccU, 0x266808d1U,
        };
        HW_SCE_p_func101(Param_p70_func101_002);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub004(0x000000a1U, 0x08000044U, 0x00000000U);

        HW_SCE_p_func_sub018(0x40000000U, 0xf7009c06U);

        for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
        {
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func205_r1();

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        HW_SCE_p_func_sub002(0x00410011U);

        static const uint32_t Param_p70_func100_002[] =
        {
            0x44514f8dU, 0x3e29cbabU, 0xd634c0e3U, 0x402c3a89U,
        };
        HW_SCE_p_func100(Param_p70_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p70_func102_002[] =
            {
                0xf521f8d8U, 0x762fd3a9U, 0x21105bd1U, 0xfb66ead9U,
            };
            HW_SCE_p_func102(Param_p70_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            static const uint32_t Param_p70_func102_003[] =
            {
                0xabdb91cdU, 0xd5d27b10U, 0xe306bc34U, 0xfd5edb91U,
            };
            HW_SCE_p_func102(Param_p70_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
