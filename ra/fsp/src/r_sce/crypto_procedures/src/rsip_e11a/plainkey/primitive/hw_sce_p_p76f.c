/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha256HmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_MAC[],
                                     const uint32_t InData_length[],
                                     uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_F4H, 0x00000100U);

    WR1_PROG(REG_F4H, 0x00000020U);

    WR1_PROG(REG_B0H, 0x00001404U);
    WR1_PROG(REG_00H, 0x00c50021U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_F4H, 0x00000010U);

    WR1_PROG(REG_14H, 0x000007a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_PROG(REG_2CH,
             change_endian_long(0x6a09e667U),
             change_endian_long(0xbb67ae85U),
             change_endian_long(0x3c6ef372U),
             change_endian_long(0xa54ff53aU),
             change_endian_long(0x510e527fU),
             change_endian_long(0x9b05688cU),
             change_endian_long(0x1f83d9abU),
             change_endian_long(0x5be0cd19U));

    WR1_PROG(REG_F4H, 0x00000011U);

    HW_SCE_p_func002();

    WR1_PROG(REG_B0H, 0x00001804U);
    WR1_PROG(REG_00H, 0x01430021U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_14H, 0x000000a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x80000000U));

    WR1_PROG(REG_00H, 0x01400015U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_14H, 0x000001a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR2_PROG(REG_2CH,
             change_endian_long(0x00000000U),
             change_endian_long(0x00000300U));

    WAIT_STS(REG_F8H, 2, 0);

    WR1_PROG(REG_F4H, 0x00000100U);

    WR1_PROG(REG_40H, 0x00001600U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x38000c00U);
    WR1_PROG(REG_9CH, 0x00000080U);
    WR1_PROG(REG_40H, 0x00260000U);

    HW_SCE_p_func100(0x84d2ee82U, 0xbff3788bU, 0xe913c8e5U, 0x0239275cU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func100(0x74463ec7U, 0xb9516badU, 0x3437cd7eU, 0x9f68ac06U);
        WR1_PROG(REG_F4H, 0x00000020U);

        WR1_PROG(REG_08H, 0x00004022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_MAC[0]);

        HW_SCE_p_func102(0x84aa1bedU, 0x1ce431e1U, 0x4122226aU, 0x5ff26446U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x80010020U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_length[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_94H, 0x3420a820U);
        WR1_PROG(REG_94H, 0x00000004U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00260000U);

        WR1_PROG(REG_94H, 0x3420a820U);
        WR1_PROG(REG_94H, 0x00000021U);
        WR1_PROG(REG_9CH, 0x00000080U);
        WR1_PROG(REG_40H, 0x00A60000U);

        HW_SCE_p_func100(0x7440e570U, 0x7f9fd767U, 0x3ad6d216U, 0x2e03bd69U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0x128ed33fU, 0xde52a1feU, 0x9d900324U, 0x6d549109U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80880002U);

            WR1_PROG(REG_F4H, 0x00000020U);

            WR1_PROG(REG_00H, 0x03450021U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_94H, 0x00000800U);
            for (iLoop = 0U; iLoop < 32U; iLoop++)
            {
                WR1_PROG(REG_94H, 0x3c002841U);
                WR1_PROG(REG_94H, 0x12003c02U);
                WR1_PROG(REG_94H, 0x00002c40U);
            }

            WR1_PROG(REG_D0H, 0x08000045U);
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x81880002U);
            WR1_PROG(REG_00H, 0x00490011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_D0H, 0x08000055U);
            WR1_PROG(REG_00H, 0x00490011U);
            WAIT_STS(REG_04H, 30, 0);
            WR1_PROG(REG_40H, 0x00001800U);

            WR1_PROG(REG_14H, 0x000007c1U);
            WR1_PROG(REG_D0H, 0x9c000005U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MAC[0]);

            WR1_PROG(REG_D0H, 0x9c100005U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MAC[4]);

            HW_SCE_p_func100(0x846fbd7aU, 0xbae7e5f3U, 0x5f9294bdU, 0xe1cfd17dU);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                HW_SCE_p_func102(0x011b8f65U, 0x5d392ae1U, 0x06cd3bfdU, 0xdb83903fU);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func102(0xa6913bdbU, 0xdad926e0U, 0x14ef6701U, 0xf9ed3a66U);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
