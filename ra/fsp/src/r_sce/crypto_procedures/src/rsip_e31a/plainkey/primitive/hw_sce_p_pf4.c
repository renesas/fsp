/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub (const uint32_t InData_KeyMode[],
                                               const uint32_t InData_CurveType[],
                                               const uint32_t InData_DomainParam[],
                                               uint32_t       OutData_PubKey[],
                                               uint32_t       OutData_PrivKeyIndex[],
                                               uint32_t       OutData_PrivKey[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f40001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x3420a800U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_94H, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    HW_SCE_p_func070(InData_DomainParam);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00002428U);

    HW_SCE_p_func100(0x00a752abU, 0xf0f5288fU, 0x8a3b9176U, 0x7e1e7c9dU);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x9eb83c40U, 0x9d66bda4U, 0x9b949086U, 0x2978790eU);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10009U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_00H, 0x00010009U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func103();
    HW_SCE_p_func100(0xad3018bfU, 0x6dbb4f3bU, 0x68aff275U, 0x15764e37U);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func103();
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_00H, 0x00c10011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    WR1_PROG(REG_00H, 0x00c0001dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_14H, 0x000000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000001U));

    WR1_PROG(REG_B4H, 0x000f000aU);
    WR1_PROG(REG_B8H, 0x00140000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B0H, 0x0000143cU);
    WR1_PROG(REG_00H, 0x00c0001dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_14H, 0x000000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000002U));

    WR1_PROG(REG_B0H, 0x00001419U);
    WR1_PROG(REG_00H, 0x00c00021U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_94H, 0x00000863U);
    WR1_PROG(REG_94H, 0x000008a5U);

    for (iLoop = 0U; iLoop < 64U; iLoop++)
    {
        WR1_PROG(REG_B4H, 0x00140027U);
        WR1_PROG(REG_B8H, 0x001e0000U);

        WR1_PROG(REG_A4H, 0x0404000aU);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x0000081aU);
        WR1_PROG(REG_9CH, 0x80020000U);
        WR1_PROG(REG_00H, 0x03430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_94H, 0x00000884U);

        WR1_PROG(REG_94H, 0x38000c21U);
        WR1_PROG(REG_94H, 0x2000d080U);

        WR1_PROG(REG_94H, 0x38000c63U);
        WR1_PROG(REG_94H, 0x1000d081U);

        WR1_PROG(REG_94H, 0x38008880U);
        WR1_PROG(REG_94H, 0x00000003U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        HW_SCE_p_func100(0x89ef237aU, 0x10c33f7aU, 0x5c872477U, 0x6725de56U);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_B4H, 0x0019001eU);
            WR1_PROG(REG_B8H, 0x004b0000U);

            WR1_PROG(REG_A4H, 0x04040009U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func101(0x1c0bb4c2U, 0xe0c7fc45U, 0xd323440eU, 0x84a9dc8cU);
        }
        else
        {
            WR1_PROG(REG_B4H, 0x0019001eU);
            WR1_PROG(REG_B8H, 0x00270000U);

            WR1_PROG(REG_A4H, 0x04040009U);
            WR1_PROG(REG_A0H, 0x20010001U);
            WAIT_STS(REG_A8H, 0, 1);
            WR1_PROG(REG_ACH, 0x00000001U);

            HW_SCE_p_func101(0x9fdb060aU, 0x04841875U, 0xc2df9691U, 0xf8a89245U);
        }

        WR1_PROG(REG_B4H, 0x003c002bU);
        WR1_PROG(REG_B8H, 0x001e0000U);

        WR1_PROG(REG_A4H, 0x04040007U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x003c0027U);
        WR1_PROG(REG_B8H, 0x00230000U);

        WR1_PROG(REG_A4H, 0x04040007U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B0H, 0x0000081fU);
        WR1_PROG(REG_9CH, 0x80020040U);
        WR1_PROG(REG_00H, 0x03430009U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        WR1_PROG(REG_B4H, 0x0019001eU);
        WR1_PROG(REG_B8H, 0x002b0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_B4H, 0x001a0023U);
        WR1_PROG(REG_B8H, 0x00270000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        WR1_PROG(REG_94H, 0x00002ca0U);

        HW_SCE_p_func101(0xca8ebd39U, 0xdcb2865eU, 0xfd743a3aU, 0x7262f493U);
    }

    WR1_PROG(REG_94H, 0x380088a0U);
    WR1_PROG(REG_94H, 0x00000040U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    WR1_PROG(REG_40H, 0x00402000U);

    WR1_PROG(REG_B4H, 0x00140027U);
    WR1_PROG(REG_B8H, 0x001e0000U);

    WR1_PROG(REG_A4H, 0x0404000aU);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_B0H, 0x0000081aU);
    WR1_PROG(REG_9CH, 0x80020000U);
    WR1_PROG(REG_00H, 0x03430009U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x00000884U);

    WR1_PROG(REG_94H, 0x38000c21U);
    WR1_PROG(REG_94H, 0x2000d080U);

    WR1_PROG(REG_94H, 0x38000c63U);
    WR1_PROG(REG_94H, 0x1000d081U);

    WR1_PROG(REG_94H, 0x38008880U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    HW_SCE_p_func100(0x033d7fe4U, 0x3c493237U, 0x778f34efU, 0xc080364aU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_B4H, 0x0019001eU);
        WR1_PROG(REG_B8H, 0x004b0000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        HW_SCE_p_func101(0xd1d9541dU, 0xbf9270d6U, 0xf26ec02dU, 0xd7b8f3dfU);
    }
    else
    {
        WR1_PROG(REG_B4H, 0x0019001eU);
        WR1_PROG(REG_B8H, 0x00270000U);

        WR1_PROG(REG_A4H, 0x04040009U);
        WR1_PROG(REG_A0H, 0x20010001U);
        WAIT_STS(REG_A8H, 0, 1);
        WR1_PROG(REG_ACH, 0x00000001U);

        HW_SCE_p_func101(0xcdb081f1U, 0xdf07d635U, 0x58f94c4bU, 0xd5702a39U);
    }

    WR1_PROG(REG_B4H, 0x000f0027U);
    WR1_PROG(REG_B8H, 0x00320000U);

    WR1_PROG(REG_A4H, 0x04040009U);
    WR1_PROG(REG_A0H, 0x20010001U);
    WAIT_STS(REG_A8H, 0, 1);
    WR1_PROG(REG_ACH, 0x00000001U);

    WR1_PROG(REG_94H, 0x00003406U);

    HW_SCE_p_func071(InData_DomainParam);

    WR1_PROG(REG_94H, 0x00003420U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x2040f769U, 0x9268a0ceU, 0x96433bd1U, 0x7e020a19U);
    HW_SCE_p_func088();

    HW_SCE_p_func100(0x86aefeb8U, 0xf0fcd8e2U, 0x12019bc0U, 0x7988be5bU);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0xf41c582eU, 0xa0c5d66dU, 0x76632eddU, 0xcc4522c3U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010000U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyMode[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x38000c00U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00270000U);

        HW_SCE_p_func100(0x7dae7252U, 0x88b488cfU, 0x08ef9e18U, 0x9015fe13U);
        WR1_PROG(REG_40H, 0x00400000U);
        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func100(0x017d2341U, 0x9e359c95U, 0xd7aceedeU, 0x315cab35U);
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
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0xfe2de9b6U, 0xe236c632U, 0xa9fdc761U, 0x90dbabb9U);
            HW_SCE_p_func043();

            HW_SCE_p_func074();

            WR1_PROG(REG_14H, 0x000000a7U);
            WR1_PROG(REG_9CH, 0x800100e0U);
            WAIT_STS(REG_14H, 31, 1);
            WR1_PROG(REG_2CH, change_endian_long(0x000000f4U));
            WR1_PROG(REG_24H, 0x00000000U);

            HW_SCE_p_func101(0x3e54b992U, 0xc29e0fc1U, 0x711525c7U, 0xc5e2f3fdU);
            HW_SCE_p_func044();

            HW_SCE_p_func100(0x535afdf0U, 0xc0485a79U, 0x9cca0cabU, 0x74abc3e6U);
            WR1_PROG(REG_B0H, 0x00001832U);

            WR1_PROG(REG_D4H, 0x40000100U);
            WR1_PROG(REG_D0H, 0xe7009d07U);
            WR1_PROG(REG_00H, 0x00430021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_08H, 0x00001022U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[1]);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[5]);

            HW_SCE_p_func100(0xce43aa4eU, 0x0f2aad99U, 0xec2fd2b1U, 0xc385350aU);
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
            RD4_ADDR(REG_2CH, &OutData_PrivKeyIndex[9]);

            HW_SCE_p_func100(0xeb5a3e85U, 0x644724b3U, 0x13cf19bdU, 0xb7a4f2c4U);
            WR1_PROG(REG_9CH, 0x81010000U);
            WR1_PROG(REG_08H, 0x00005006U);
            WAIT_STS(REG_08H, 30, 1);
            RD1_ADDR(REG_2CH, &OutData_PrivKeyIndex[0]);

            HW_SCE_p_func101(0x3bf27534U, 0x90a16e8bU, 0x5ba270abU, 0x20f4004cU);
        }
        else
        {
            HW_SCE_p_func100(0xdd8756daU, 0x2c719920U, 0x8e1ab0e1U, 0x71ee1666U);
            WR1_PROG(REG_B0H, 0x00001832U);
            WR1_PROG(REG_08H, 0x00006022U);
            WAIT_STS(REG_08H, 30, 1);
            RD8_ADDR(REG_2CH, &OutData_PrivKey[0]);

            HW_SCE_p_func101(0xdba1bcf3U, 0x1bf0e542U, 0xec630723U, 0x3e0ad419U);
        }

        HW_SCE_p_func100(0xdd64bf17U, 0x751d88adU, 0x2745e66bU, 0xbcaee752U);
        WR1_PROG(REG_B0H, 0x00001828U);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_PubKey[0]);

        HW_SCE_p_func100(0x672f8ad1U, 0x3d91acaaU, 0x33a1baedU, 0x93b8aa1fU);
        WR1_PROG(REG_B0H, 0x0000182dU);
        WR1_PROG(REG_08H, 0x00006022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_PubKey[8]);

        HW_SCE_p_func102(0x1e78fdb5U, 0xc3bb896cU, 0x2a3bbb1dU, 0x0c70ca6eU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
