/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00070001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func100(0xa126d95eU, 0x7c9b58c2U, 0xa08a31b9U, 0x776770c8U);
    HW_SCE_p_func103();
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_9CH, 0x80010000U);
    WR1_PROG(REG_00H, 0x03410005U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_00H, 0x0001000dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000007U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x26c31b4bU, 0x74230415U, 0x4b5fbd5cU, 0xb822f63fU);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x00000005U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000007U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x6872c9c2U, 0xae0ba78dU, 0x22315bbeU, 0x8a9aabbcU);
    HW_SCE_p_func044();

    HW_SCE_p_func100(0xdb310a39U, 0x303ac451U, 0x485052c9U, 0x228508faU);
    HW_SCE_p_func103();

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    WR1_PROG(REG_00H, 0x03410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func100(0xcec3a6afU, 0x2dd7d901U, 0x456fd12bU, 0x510f32fcU);
    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0xe7009d05U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x81840001U);
    WR1_PROG(REG_00H, 0x00490011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);

    HW_SCE_p_func100(0x2e95ffa8U, 0x6600abafU, 0xe836fcabU, 0xb6a5e1f3U);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c000104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    HW_SCE_p_func100(0x1345978aU, 0x84f650e5U, 0xdbcbe8a5U, 0x9ba76eb2U);
    WR1_PROG(REG_9CH, 0x81010000U);
    WR1_PROG(REG_08H, 0x00005006U);
    WAIT_STS(REG_08H, 30, 1);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    HW_SCE_p_func102(0xe61be1ddU, 0x5cf527e7U, 0x1980189cU, 0xb587fe80U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
