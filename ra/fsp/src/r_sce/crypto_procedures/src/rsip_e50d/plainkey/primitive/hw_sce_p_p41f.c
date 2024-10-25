/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes128CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x4a000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x7ac2c440U, 0xd5d8e6d5U, 0x0685a602U, 0xd6ba5accU);
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x5a000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x467ae937U, 0xd38e73f9U, 0xfa7acb0dU, 0xa3f58b44U);
    }

    WR1_PROG(REG_1824H, 0x0c000045U);
    WR1_PROG(REG_1400H, 0x00410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        HW_SCE_p_func100(0x8245ae0dU, 0x815caaebU, 0x019eea8aU, 0x526a9f8eU);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x0e000505U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[0]);

        WR1_PROG(REG_1408H, 0x00001012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_DataT[0]);

        HW_SCE_p_func102(0x8951549aU, 0xce520176U, 0x1cf60ba6U, 0x1453367cU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010040U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_DataTLen[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x3420a840U);
        WR1_PROG(REG_1600H, 0x00000010U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x0000b460U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x34202862U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xcce2937cU, 0x3b04fc4dU, 0x0cbf409bU, 0xaa7bbd9bU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x8b1e1ec6U, 0x9117aaf9U, 0x0c0a673dU, 0x03ecd8ffU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x0e000505U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[0]);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x80840001U);
            WR1_PROG(REG_1400H, 0x03410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x000034e2U);
            WR1_PROG(REG_1600H, 0x000568e7U);
            WR1_PROG(REG_1600H, 0x00026ce7U);

            WR1_PROG(REG_1600H, 0x00003827U);

            WR1_PROG(REG_1600H, 0x0000b4c0U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1600H, 0x00003402U);
            WR1_PROG(REG_1600H, 0x00008c00U);
            WR1_PROG(REG_1600H, 0x0000001fU);
            WR1_PROG(REG_1600H, 0x000028c0U);
            WR1_PROG(REG_1600H, 0x00008cc0U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1600H, 0x00004406U);

            WR1_PROG(REG_1600H, 0x00007421U);
            WR1_PROG(REG_1600H, 0x00007821U);

            WR1_PROG(REG_1600H, 0x00003c27U);

            WR1_PROG(REG_1600H, 0x000034c2U);
            WR1_PROG(REG_1600H, 0x0000a4c0U);
            WR1_PROG(REG_1600H, 0x0000001fU);
            WR1_PROG(REG_1600H, 0x000568c6U);

            WR1_PROG(REG_1600H, 0x000034e6U);
            WR1_PROG(REG_1600H, 0x00026ce7U);

            WR1_PROG(REG_1600H, 0x00000821U);

            for (iLoop = 0U; iLoop < 4U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x3420a8e0U);
                WR1_PROG(REG_1600H, 0x0000000dU);
                WR1_PROG(REG_1600H, 0x10003c27U);

                WR1_PROG(REG_1600H, 0x1000a4e0U);
                WR1_PROG(REG_1600H, 0x00000004U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1824H, 0x08000045U);
            WR1_PROG(REG_1608H, 0x81840001U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x9c000005U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_DataT[0]);

            HW_SCE_p_func100(0xc3220594U, 0x34d5ae98U, 0x3c9400fcU, 0x1e6088d5U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x7758be04U, 0x8391d62cU, 0x06885f73U, 0xd1f36b60U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                HW_SCE_p_func102(0xd3341aa1U, 0xd4fd8a50U, 0xa3136383U, 0xae07a322U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
