/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Sha256HmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_MAC[],
                                     const uint32_t InData_length[],
                                     uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_F4H, 0x00000100U);

    WR1_PROG(REG_F4H, 0x00000020U);

    WR1_PROG(REG_B0H, 0x00001404U);
    HW_SCE_p_func_sub002(0x00c50021U);

    HW_SCE_p_func004();

    WR1_PROG(REG_F4H, 0x00000011U);

    HW_SCE_p_func002();

    WR1_PROG(REG_B0H, 0x00001804U);
    HW_SCE_p_func_sub002(0x01430021U);

    HW_SCE_p_func_sub011(0x000000a4U, 0x80000000U);

    HW_SCE_p_func_sub002(0x01400015U);

    WR1_PROG(REG_14H, 0x000001a4U);
    WAIT_STS(REG_14H, 31, 1);
    WR2_PROG(REG_2CH, change_endian_long(0x00000000U), change_endian_long(0x00000300U));

    WAIT_STS(REG_F8H, 2, 0);

    WR1_PROG(REG_F4H, 0x00000100U);

    WR1_PROG(REG_40H, 0x00001600U);

    HW_SCE_p_func_sub005(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_2CH, InData_Cmd[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func_sub009(0x38000c00U, 0x00260000U);

    static const uint32_t Param_p76f_func100_001[] =
    {
        0x84d2ee82U, 0xbff3788bU, 0xe913c8e5U, 0x0239275cU,
    };
    HW_SCE_p_func100(Param_p76f_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        static const uint32_t Param_p76f_func100_002[] =
        {
            0x74463ec7U, 0xb9516badU, 0x3437cd7eU, 0x9f68ac06U,
        };
        HW_SCE_p_func100(Param_p76f_func100_002);
        WR1_PROG(REG_F4H, 0x00000020U);

        WR1_PROG(REG_08H, 0x00004022U);
        WAIT_STS(REG_08H, 30, 1);
        RD8_ADDR(REG_2CH, &OutData_MAC[0]);

        static const uint32_t Param_p76f_func102_001[] =
        {
            0x84aa1bedU, 0x1ce431e1U, 0x4122226aU, 0x5ff26446U,
        };
        HW_SCE_p_func102(Param_p76f_func102_001);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        HW_SCE_p_func_sub005(0x000000c7U, 0x80010020U);
        WR1_PROG(REG_2CH, InData_length[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func_sub006(0x3420a820U, 0x00000004U, 0x00260000U);

        HW_SCE_p_func_sub006(0x3420a820U, 0x00000021U, 0x00A60000U);

        static const uint32_t Param_p76f_func100_003[] =
        {
            0x7440e570U, 0x7f9fd767U, 0x3ad6d216U, 0x2e03bd69U,
        };
        HW_SCE_p_func100(Param_p76f_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            static const uint32_t Param_p76f_func102_002[] =
            {
                0x128ed33fU, 0xde52a1feU, 0x9d900324U, 0x6d549109U,
            };
            HW_SCE_p_func102(Param_p76f_func102_002);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_94H, 0x00000842U);
            WR1_PROG(REG_9CH, 0x80880002U);

            WR1_PROG(REG_F4H, 0x00000020U);

            HW_SCE_p_func_sub002(0x03450021U);

            WR1_PROG(REG_94H, 0x00000800U);
            for (iLoop = 0U; iLoop < 32U; iLoop++)
            {
                HW_SCE_p_func_sub001(0x3c002841U, 0x12003c02U, 0x00002c40U);
            }

            HW_SCE_p_func_sub016(0x08000045U, 0x00000842U, 0x81880002U);
            HW_SCE_p_func_sub002(0x00490011U);

            WR1_PROG(REG_D0H, 0x08000055U);
            HW_SCE_p_func_sub002(0x00490011U);

            HW_SCE_p_func_sub008(0x000007c1U, 0x9c000005U);
            WR4_ADDR(REG_2CH, &InData_MAC[0]);

            WR1_PROG(REG_D0H, 0x9c100005U);
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_MAC[4]);

            static const uint32_t Param_p76f_func100_004[] =
            {
                0x846fbd7aU, 0xbae7e5f3U, 0x5f9294bdU, 0xe1cfd17dU,
            };
            HW_SCE_p_func100(Param_p76f_func100_004);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                static const uint32_t Param_p76f_func102_003[] =
                {
                    0x011b8f65U, 0x5d392ae1U, 0x06cd3bfdU, 0xdb83903fU,
                };
                HW_SCE_p_func102(Param_p76f_func102_003);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p76f_func102_004[] =
                {
                    0xa6913bdbU, 0xdad926e0U, 0x14ef6701U, 0xf9ed3a66U,
                };
                HW_SCE_p_func102(Param_p76f_func102_004);
                WR1_PROG(REG_6CH, 0x00000040U);
                WAIT_STS(REG_20H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
