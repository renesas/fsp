/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestSub (const uint32_t InData_HashType[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_Msg[],
                                              const uint32_t InData_MsgLen[],
                                              const uint32_t InData_State[],
                                              uint32_t       OutData_MsgDigest[],
                                              uint32_t       OutData_State[],
                                              const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00720001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func100(0x5cc7a738U, 0x90dc8200U, 0x34171e23U, 0xd831d306U);
    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000001c7U);
    WR1_PROG(REG_1608H, 0x80020000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1600H, 0x3420a820U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x2000b420U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x000037e1U);
    WR1_PROG(REG_1600H, 0x00008fe0U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x00046fffU);

    WR1_PROG(REG_1600H, 0x000013e0U);

    WR1_PROG(REG_1600H, 0x00007c1fU);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00000000U);

        HW_SCE_p_func101(0x567bd220U, 0xe387700aU, 0xb93858c6U, 0xd4c52eabU);
    }

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000020U)
    {
        WR1_PROG(REG_2004H, 0x00001000U);

        HW_SCE_p_func101(0x722d1de3U, 0x779cee14U, 0xc58e7e64U, 0xeb3620ebU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x00000040U);

        HW_SCE_p_func101(0xb7b4d935U, 0x46c22addU, 0xa5558401U, 0x4607a89dU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000021U)
    {
        WR1_PROG(REG_2004H, 0x00001040U);

        HW_SCE_p_func101(0x67442591U, 0x786e30bbU, 0x93902f5cU, 0x578d3adaU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x00000050U);

        HW_SCE_p_func101(0xf518e2aeU, 0x8e1b36f8U, 0x70ecea7aU, 0xca9d23f4U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000022U)
    {
        WR1_PROG(REG_2004H, 0x00001050U);

        HW_SCE_p_func101(0xda089660U, 0x18025d26U, 0xddcd1998U, 0x896953edU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2004H, 0x00000080U);

        HW_SCE_p_func101(0x26b0b178U, 0x1d0fe47eU, 0x45e58734U, 0x6215c917U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000023U)
    {
        WR1_PROG(REG_2004H, 0x00001080U);

        HW_SCE_p_func101(0xc47858b3U, 0x4995e6faU, 0x7896f678U, 0xd71e6cdcU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_2004H, 0x00000090U);

        HW_SCE_p_func101(0x42732d61U, 0x8cecb6baU, 0x16bf231aU, 0xb034c5cbU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000024U)
    {
        WR1_PROG(REG_2004H, 0x00001090U);

        HW_SCE_p_func101(0x581caea6U, 0x596410d2U, 0x082546efU, 0x23d25de0U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        WR1_PROG(REG_2004H, 0x000000a0U);

        HW_SCE_p_func101(0xf95267a0U, 0x018e70c5U, 0x5aab4063U, 0xb34b9005U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000025U)
    {
        WR1_PROG(REG_2004H, 0x000010a0U);

        HW_SCE_p_func101(0xe43eff9dU, 0x68a1f827U, 0xeb746affU, 0xbb50f3c5U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        WR1_PROG(REG_2004H, 0x000000b0U);

        HW_SCE_p_func101(0xee47d997U, 0xb5114802U, 0xf7d566b7U, 0x57a414a3U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000026U)
    {
        WR1_PROG(REG_2004H, 0x000010b0U);

        HW_SCE_p_func101(0xe976cebfU, 0x9ee6f387U, 0x4cabc998U, 0xcca0c4e3U);
    }

    WR1_PROG(REG_1600H, 0x38008c20U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x7e733a2fU, 0x1c43d408U, 0x48cf0d5dU, 0xc2578cc4U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
        {
            WR1_PROG(REG_200CH, 0x00000100U);

            HW_SCE_p_func101(0x17b8a614U, 0xe92389f4U, 0x4f5c2c06U, 0x36fc165fU);
        }
        else
        {
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, InData_MsgLen[0]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, InData_MsgLen[1]);

            HW_SCE_p_func101(0x69c2380cU, 0xf7dddb4cU, 0x5a26f049U, 0xc9c08de7U);
        }
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, InData_State[18]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, InData_State[19]);

        for (iLoop = 0U; iLoop < 18U; iLoop++)
        {
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2028H, InData_State[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x3548bbb4U, 0x3723cbd6U, 0x5f1d925aU, 0x32561ea2U);
    }

    WR1_PROG(REG_1444H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);

        iLoop = iLoop + 16U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008820U);
    WR1_PROG(REG_1600H, 0x00000001U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x38008820U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x567e410eU, 0x371ac929U, 0xfe0d7c0aU, 0xc213adfcU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WAIT_STS(REG_2030H, 8, 0);
        for (iLoop = 0U; iLoop < 18U; iLoop++)
        {
            RD1_ADDR(REG_202CH, &OutData_State[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        RD1_ADDR(REG_2014H, &OutData_State[18]);
        RD1_ADDR(REG_2010H, &OutData_State[19]);

        HW_SCE_p_func102(0xbb9650efU, 0xc4147094U, 0xc3d6d0a4U, 0x7263ee45U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else
    {
        WAIT_STS(REG_2030H, 4, 1);

        HW_SCE_p_func100(0xb44467ddU, 0x4d8301f1U, 0xad44168aU, 0x3967754cU);
        WR1_PROG(REG_1600H, 0x38008800U);
        WR1_PROG(REG_1600H, 0x00000003U);
        WR1_PROG(REG_1600H, 0x1000b400U);
        WR1_PROG(REG_1600H, 0x00000001U);

        WR1_PROG(REG_1600H, 0x38008800U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x1000b400U);
        WR1_PROG(REG_1600H, 0x00000002U);

        WR1_PROG(REG_1600H, 0x00007c00U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            HW_SCE_p_func100(0xab266e93U, 0x312561ffU, 0xfb522dbaU, 0x43e512b4U);
            WR1_PROG(REG_1408H, 0x00004016U);
            for (iLoop = 0U; iLoop < 5U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func102(0x0038d5aeU, 0x8385b01eU, 0x036509f6U, 0x1e4afdf1U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            HW_SCE_p_func100(0xb7a47235U, 0x7be6565eU, 0xe534067fU, 0x33a2c499U);
            WR1_PROG(REG_1408H, 0x0000401eU);
            for (iLoop = 0U; iLoop < 7U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func102(0x34a7120fU, 0xaa6f4261U, 0x68591b80U, 0x8c81cdbbU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            HW_SCE_p_func100(0x2ce178f3U, 0xa1cc3febU, 0xc1949a5aU, 0x21497d09U);
            WR1_PROG(REG_1408H, 0x00004022U);
            for (iLoop = 0U; iLoop < 8U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func102(0x172c0899U, 0x95e1cb98U, 0x8dc08fa0U, 0xc8dd378eU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
        {
            HW_SCE_p_func100(0x287bea2eU, 0x1df2e96fU, 0x4dbcb393U, 0x4c9d6cccU);
            WR1_PROG(REG_1408H, 0x00004032U);
            for (iLoop = 0U; iLoop < 12U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func102(0x0e16e5aaU, 0x050a18f3U, 0x63018b80U, 0x9957231fU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
        {
            HW_SCE_p_func100(0x2fa2bc81U, 0xdfaebf75U, 0x92eafb33U, 0x9fceb828U);
            WR1_PROG(REG_1408H, 0x00004042U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func102(0xc4b453dfU, 0x18f97805U, 0x06a53817U, 0x5d2a0d9aU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
    }

    return FSP_SUCCESS;
}
