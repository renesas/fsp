/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

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

    WR1_PROG(REG_94H, 0x00000842U);

    WR1_PROG(REG_94H, 0x3020a880U);
    WR1_PROG(REG_94H, 0x00000020U);
    WR1_PROG(REG_94H, 0x00070020U);
    WR1_PROG(REG_94H, 0x0000b440U);
    WR1_PROG(REG_94H, 0xAA8003A0U);
    WR1_PROG(REG_94H, 0x00000080U);
    WR1_PROG(REG_94H, 0x3020a880U);
    WR1_PROG(REG_94H, 0x00000040U);
    WR1_PROG(REG_94H, 0x00070020U);
    WR1_PROG(REG_94H, 0x3020a880U);
    WR1_PROG(REG_94H, 0x00000020U);
    WR1_PROG(REG_94H, 0x00060020U);
    WR1_PROG(REG_94H, 0x0000b440U);
    WR1_PROG(REG_94H, 0x00000F88U);
    WR1_PROG(REG_94H, 0x00000080U);
    WR1_PROG(REG_94H, 0x00000080U);

    WR1_PROG(REG_94H, 0x000034a4U);

    WR1_PROG(REG_94H, 0x00008c80U);
    WR1_PROG(REG_94H, 0x0000001fU);

    HW_SCE_p_func056();

    HW_SCE_p_func100(0x224430d1U, 0xdb4ab814U, 0xbed9aeaaU, 0x256732c8U);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x11114fc3U, 0x7427d67fU, 0x11e98348U, 0xd2460cb2U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_94H, 0x00003485U);

        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x0b6d911fU, 0xbe1361a1U, 0xf6c31793U, 0x27ada00aU);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x000034c4U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x4fcfbc17U, 0x37642177U, 0x3fe2d49fU, 0xafb04421U);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x08000044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xf7009c06U);

        for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
        {
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func205();

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x2e7c08b2U, 0x4cd17121U, 0xcc5ef63cU, 0xcc7767dfU);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x50e274a7U, 0x90fa0c1aU, 0x6bea3174U, 0x58676e3aU);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0x751b674dU, 0x515193feU, 0x25e50687U, 0x06556c66U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
