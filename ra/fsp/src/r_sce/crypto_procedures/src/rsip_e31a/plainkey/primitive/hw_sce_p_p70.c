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

    HW_SCE_p_func_sub001(0x00000842U, 0x3020a880U, 0x00000020U, 0x00070020U);
    HW_SCE_p_func_sub001(0x0000b440U, 0xAA8003A0U, 0x00000080U, 0x3020a880U);
    HW_SCE_p_func_sub001(0x00000040U, 0x00070020U, 0x3020a880U, 0x00000020U);
    HW_SCE_p_func_sub001(0x00060020U, 0x0000b440U, 0x00000F88U, 0x00000080U);
    HW_SCE_p_func_sub001(0x00000080U, 0x000034a4U, 0x00008c80U, 0x0000001fU);

    HW_SCE_p_func056();

    static const uint32_t Param_p70_func100_001[] =
    {
        0x224430d1U, 0xdb4ab814U, 0xbed9aeaaU, 0x256732c8U,
    };
    HW_SCE_p_func100(Param_p70_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p70_func102_001[] =
        {
            0x11114fc3U, 0x7427d67fU, 0x11e98348U, 0xd2460cb2U,
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
            0x0b6d911fU, 0xbe1361a1U, 0xf6c31793U, 0x27ada00aU,
        };
        HW_SCE_p_func101(Param_p70_func101_001);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x000034c4U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p70_func101_002[] =
        {
            0x4fcfbc17U, 0x37642177U, 0x3fe2d49fU, 0xafb04421U,
        };
        HW_SCE_p_func101(Param_p70_func101_002);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub004(0x000000a1U, 0x08000044U, 0x00000000U);

        HW_SCE_p_func_sub016(0x00020061U, 0x40000000U, 0xf7009c06U);

        for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
        {
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func205();

        HW_SCE_p_func_sub007(0x000003c1U, 0x40000000U, 0x07008d05U);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        HW_SCE_p_func_sub003(0x00410011U);

        static const uint32_t Param_p70_func100_002[] =
        {
            0x2e7c08b2U, 0x4cd17121U, 0xcc5ef63cU, 0xcc7767dfU,
        };
        HW_SCE_p_func100(Param_p70_func100_002);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p70_func102_002[] =
            {
                0x50e274a7U, 0x90fa0c1aU, 0x6bea3174U, 0x58676e3aU,
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
                0x751b674dU, 0x515193feU, 0x25e50687U, 0x06556c66U,
            };
            HW_SCE_p_func102(Param_p70_func102_003);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
