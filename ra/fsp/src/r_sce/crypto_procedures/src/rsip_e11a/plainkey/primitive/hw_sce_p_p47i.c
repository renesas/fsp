/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00470001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010080U);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_KeyMode[0]);
    HW_SCE_p_func_sub014(0x0000b4a0U, 0x00000005U);

    HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
    WR1_PROG(REG_2CH, change_endian_long(0x00000047U));
    WR1_PROG(REG_24H, 0x00000000U);

    static const uint32_t Param_p47i_func101_001[] =
    {
        0x20291e65U, 0x2dfbcc7eU, 0x884a6e36U, 0x4e1bec51U,
    };
    HW_SCE_p_func101(Param_p47i_func101_001);
    HW_SCE_p_func440(InData_KeyIndex, InData_Key);

    static const uint32_t Param_p47i_func100_001[] =
    {
        0x031dd750U, 0x433c5f77U, 0x577cd371U, 0x850d1815U,
    };
    HW_SCE_p_func100(Param_p47i_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p47i_func102_001[] =
        {
            0xe3c216aeU, 0xbe856dc0U, 0x94e38cb8U, 0xc367c8e9U,
        };
        HW_SCE_p_func102(Param_p47i_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p47i_func100_002[] =
        {
            0x728dd117U, 0x938f997bU, 0x89e55c34U, 0x894857b1U,
        };
        HW_SCE_p_func100(Param_p47i_func100_002);

        WR1_PROG(REG_D0H, 0x08000085U);
        WR1_PROG(REG_B0H, 0x00000801U);
        HW_SCE_p_func_sub002(0x00430009U);

        WR1_PROG(REG_B0H, 0x00000802U);
        HW_SCE_p_func_sub002(0x00430009U);

        HW_SCE_p_func_sub006(0x3c00a880U, 0x00000002U, 0x00260000U);

        static const uint32_t Param_p47i_func100_003[] =
        {
            0xff5a1848U, 0x53565619U, 0x345eeca3U, 0x365cce6eU,
        };
        HW_SCE_p_func100(Param_p47i_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub008(0x000003c1U, 0x08000045U);
            WR4_ADDR(REG_2CH, &InData_IV[0]);

            static const uint32_t Param_p47i_func101_002[] =
            {
                0xb1226603U, 0x74540361U, 0xf866d09fU, 0x375dca12U,
            };
            HW_SCE_p_func101(Param_p47i_func101_002);
        }

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0a000100U);

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0a000108U);

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x0e000500U);

        HW_SCE_p_func_sub001(0x0c003080U, 0x2000b4e0U, 0x09000908U);

        HW_SCE_p_func_sub001(0x0c00a880U, 0xfffffffcU, 0x2000b4e0U);
        WR1_PROG(REG_94H, 0x07000d00U);

        static const uint32_t Param_p47i_func101_003[] =
        {
            0xc304ade4U, 0x3ba11c29U, 0x94ea020fU, 0x09a863d7U,
        };
        HW_SCE_p_func101(Param_p47i_func101_003);

        return FSP_SUCCESS;
    }
}
