/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateRandomKeyIndexSub (const uint32_t InData_Cmd[], uint32_t OutData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00550001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func049(InData_Cmd);

    WR1_PROG(REG_94H, 0x00003464U);

    HW_SCE_p_func_sub006(0x3420a880U, 0x00000040U, 0x00A70000U);

    HW_SCE_p_func_sub001(0x00000842U, 0x3020a880U, 0x00000020U, 0x00070020U);
    HW_SCE_p_func_sub001(0x0000b440U, 0x080000A0U, 0x00000080U, 0x3020a880U);
    HW_SCE_p_func_sub001(0x00000040U, 0x00070020U, 0x3020a880U, 0x00000020U);
    HW_SCE_p_func_sub001(0x00060020U, 0x0000b440U, 0x00000F00U, 0x00000080U);
    HW_SCE_p_func_sub001(0x00000080U, 0x00008c80U, 0x0000001fU, 0x38005844U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00270000U);

    static const uint32_t Param_p55_func100_001[] =
    {
        0x021dac6fU, 0x36fd6f2eU, 0x4b05252bU, 0x57684e56U,
    };
    HW_SCE_p_func100(Param_p55_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p55_func102_001[] =
        {
            0x84b553caU, 0x52e87d6dU, 0xd195afb2U, 0x52822732U,
        };
        HW_SCE_p_func102(Param_p55_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_p55_func100_002[] =
        {
            0x6331a09bU, 0x185b1b31U, 0x1ab6b2f1U, 0x7826b91cU,
        };
        HW_SCE_p_func100(Param_p55_func100_002);

        HW_SCE_p_func_sub001(0x38008860U, 0x00000005U, 0x1000b420U, 0x00000004U);

        HW_SCE_p_func_sub001(0x38008860U, 0x00000007U, 0x1000b420U, 0x00000008U);

        HW_SCE_p_func_sub001(0x38008860U, 0x0000001bU, 0x1000b420U, 0x00000008U);

        HW_SCE_p_func_sub001(0x38008860U, 0x00000028U, 0x1000b420U, 0x0000000cU);

        HW_SCE_p_func_sub001(0x38008860U, 0x00000029U, 0x1000b420U, 0x00000010U);

        HW_SCE_p_func_sub001(0x38008860U, 0x0000002aU, 0x1000b420U, 0x00000010U);

        HW_SCE_p_func_sub001(0x38008860U, 0x0000002bU, 0x1000b420U, 0x00000010U);

        HW_SCE_p_func103();
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

        WR1_PROG(REG_9CH, 0x80010000U);
        HW_SCE_p_func_sub003(0x03410005U);
        HW_SCE_p_func_sub003(0x0001000dU);

        WR1_PROG(REG_94H, 0x000034c0U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000055U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p55_func101_001[] =
        {
            0x351cce4cU, 0xa3cbc11bU, 0x0c68392fU, 0x76fd7706U,
        };
        HW_SCE_p_func101(Param_p55_func101_001);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x000034c3U);

        HW_SCE_p_func_sub005(0x000000a7U, 0x800100e0U);
        WR1_PROG(REG_2CH, change_endian_long(0x00000055U));
        WR1_PROG(REG_24H, 0x00000000U);

        static const uint32_t Param_p55_func101_002[] =
        {
            0xcb458ec9U, 0xc6b174a2U, 0x7131f0b0U, 0x199186eaU,
        };
        HW_SCE_p_func101(Param_p55_func101_002);
        HW_SCE_p_func044();

        static const uint32_t Param_p55_func100_003[] =
        {
            0x6c3471d5U, 0x8557eff7U, 0xb405d083U, 0x519e2cedU,
        };
        HW_SCE_p_func100(Param_p55_func100_003);
        HW_SCE_p_func_sub004(0x000001a1U, 0x08000044U, 0x00000000U);

        HW_SCE_p_func_sub018(0x08000054U, 0x00000000U);

        HW_SCE_p_func_sub009(0x81010020U, 0x00005006U);
        RD1_ADDR(REG_2CH, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            static const uint32_t Param_p55_func100_004[] =
            {
                0xc803eb65U, 0xb6293458U, 0xbeecdea8U, 0x132ba637U,
            };
            HW_SCE_p_func100(Param_p55_func100_004);
            HW_SCE_p_func103();
            static const uint32_t Param_p55_func100_005[] =
            {
                0x59669847U, 0x38766b0fU, 0x8c3e676fU, 0xc3263707U,
            };
            HW_SCE_p_func100(Param_p55_func100_005);
            HW_SCE_p_func_sub004(0x000000a1U, 0x0c200104U, 0x00000000U);

            WR1_PROG(REG_D4H, 0x40000000U);
            WR1_PROG(REG_D0H, 0xe7008d45U);
            HW_SCE_p_func_sub003(0x00410011U);

            WR1_PROG(REG_08H, 0x00001012U);
            WAIT_STS(REG_08H, 30, 1);
            RD4_ADDR(REG_2CH, &OutData_KeyIndex[1 + iLoop]);

            WR1_PROG(REG_94H, 0x0000a820U);
            WR1_PROG(REG_94H, 0x00000004U);

            static const uint32_t Param_p55_func101_003[] =
            {
                0x61df87bcU, 0x20567248U, 0xa8bbf2bfU, 0xf4211f3eU,
            };
            HW_SCE_p_func101(Param_p55_func101_003);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_94H, 0x00007c01U);
        WR1_PROG(REG_40H, 0x00602000U);

        static const uint32_t Param_p55_func100_006[] =
        {
            0x725008a4U, 0x5b930287U, 0xc864ae75U, 0x2afc703bU,
        };
        HW_SCE_p_func100(Param_p55_func100_006);
        HW_SCE_p_func_sub004(0x000000a1U, 0x0c000104U, 0x00000000U);

        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x09108105U);
        HW_SCE_p_func_sub003(0x00410011U);

        WR1_PROG(REG_08H, 0x00001012U);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_KeyIndex[1 + iLoop]);

        static const uint32_t Param_p55_func100_007[] =
        {
            0x654c2f2bU, 0x428959beU, 0x802a0064U, 0xec06fec7U,
        };
        HW_SCE_p_func100(Param_p55_func100_007);
        HW_SCE_p_func_sub009(0x81010000U, 0x00005006U);
        RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

        static const uint32_t Param_p55_func102_002[] =
        {
            0x369c7e6fU, 0x815b1a25U, 0x50148b87U, 0x8d7fd9e4U,
        };
        HW_SCE_p_func102(Param_p55_func102_002);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
