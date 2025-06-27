/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EcdsaP512SignatureVerificationSub (const uint32_t InData_Key[],
                                                    const uint32_t InData_MsgDgst[],
                                                    const uint32_t InData_Signature[],
                                                    const uint32_t InData_DomainParam[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x007e0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    WR1_PROG(REG_1444H, 0x00001fc2U);
    WR1_PROG(REG_1A2CH, 0x00000700U);
    WR1_PROG(REG_1A24H, 0x08008107U);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1608H, 0x80a00001U);
    for (iLoop = 0U; iLoop < 16U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Key[iLoop]);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 16U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Key[iLoop + 16]);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000fc7U);
    WR1_PROG(REG_1600H, 0x00000bffU);
    WR1_PROG(REG_1608H, 0x8090001fU);
    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_MsgDgst[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x80010360U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000007eU));
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    HW_SCE_p_func100(0x79720debU, 0x3ed6d9eeU, 0x0ac9e351U, 0x8468d1ecU);
    HW_SCE_p_func078_r2(InData_DomainParam);

    WR1_PROG(REG_1010H, 0x00000020U);
    WR1_PROG(REG_101CH, 0x000000c0U);

    WR1_PROG(REG_1004H, 0x08080010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000070U);

    WR1_PROG(REG_1004H, 0x08080010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1404H, 0x18f00000U);
    WR1_PROG(REG_1444H, 0x00001fc2U);
    WR1_PROG(REG_1A2CH, 0x00000700U);
    WR1_PROG(REG_1A24H, 0x08008107U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[4]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[8]);
    WR1_PROG(REG_1400H, 0x00c20031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[12]);
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x19400000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[16]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[20]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[24]);
    WR1_PROG(REG_1400H, 0x00c20031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Signature[28]);
    WR1_PROG(REG_1400H, 0x00c20011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1404H, 0x11c00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
    WR1_PROG(REG_1400H, 0x00c0003dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c20005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x000000c0U);
    WR1_PROG(REG_1018H, 0x00000200U);
    WR1_PROG(REG_101CH, 0x000000c0U);
    WR1_PROG(REG_1020H, 0x00000160U);

    WR1_PROG(REG_1004H, 0x0808000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000160U);
    WR1_PROG(REG_1018H, 0x00000930U);
    WR1_PROG(REG_1020H, 0x000001b0U);

    WR1_PROG(REG_1004H, 0x0808000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000930U);
    WR1_PROG(REG_1018H, 0x00000200U);
    WR1_PROG(REG_1020H, 0x000001b0U);

    WR1_PROG(REG_1004H, 0x0808000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000160U);
    WR1_PROG(REG_1018H, 0x00000980U);
    WR1_PROG(REG_1020H, 0x000001b0U);

    WR1_PROG(REG_1004H, 0x0808000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    WR1_PROG(REG_1014H, 0x00000980U);
    WR1_PROG(REG_1018H, 0x00000200U);
    WR1_PROG(REG_1020H, 0x000001b0U);

    WR1_PROG(REG_1004H, 0x0808000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_143CH, 0x00210000U);

    HW_SCE_p_func100(0x3132acfeU, 0xe2ed7ba2U, 0x840215baU, 0xb8283c3fU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1600H, 0x00000800U);

        HW_SCE_p_func101(0x962e77c1U, 0xf3234a4dU, 0x62e71fc1U, 0xb6d2a5bdU);
    }
    else
    {
        HW_SCE_p_func100(0x2fb26214U, 0x3f681f51U, 0xb112e643U, 0x330af75aU);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_1018H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000110U);
        WR1_PROG(REG_1010H, 0x00000020U);

        WR1_PROG(REG_1004H, 0x0808000fU);
        WR1_PROG(REG_1408H, 0x00020000U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);
        WR1_PROG(REG_143CH, 0x00000d00U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000840U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000160U);

        WR1_PROG(REG_1004H, 0x08080002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x10d00000U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1608H, 0x8190001fU);
        WR1_PROG(REG_1400H, 0x00c90041U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000340U);

        WR1_PROG(REG_1004H, 0x08080002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000110U);

        WR1_PROG(REG_1004H, 0x08080002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        HW_SCE_p_func100(0xbf2440e8U, 0xd8a1b53aU, 0x23f4777dU, 0x905f2768U);
        WR1_PROG(REG_1010H, 0x00000018U);

        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x00c000f1U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func079_r2(InData_DomainParam);

        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000250U);

        WR1_PROG(REG_1004H, 0x08080004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x11200000U);
        WR1_PROG(REG_1400H, 0x00c00041U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000890U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x000002a8U);

        WR1_PROG(REG_1004H, 0x08080009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000070U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x000002f0U);

        WR1_PROG(REG_1004H, 0x08080009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x13b00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0003dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000340U);
        WR1_PROG(REG_1018H, 0x000003f0U);
        WR1_PROG(REG_1020H, 0x000004e0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00a10000U);

        HW_SCE_p_func100(0xe314eb3dU, 0xbc3245c7U, 0x8a2d3144U, 0xaeab361aU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func100(0x0efa59e6U, 0x523b26c2U, 0xa36b72e1U, 0x37164e4aU);
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000480U);

            WR1_PROG(REG_1004H, 0x08080015U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1404H, 0x11c00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0003dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000480U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1600H, 0x0000b720U);
            WR1_PROG(REG_1600H, 0x180f25a9U);

            HW_SCE_p_func101(0x746ace0fU, 0x72a69af6U, 0x9fa4ed03U, 0x1e7dc474U);
        }
        else
        {
            WR1_PROG(REG_1404H, 0x13b00000U);
            WR1_PROG(REG_1400H, 0x00c00041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1404H, 0x13f80000U);
            WR1_PROG(REG_1400H, 0x00c00041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1404H, 0x14400000U);
            WR1_PROG(REG_1400H, 0x00c00041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000b39U);

            HW_SCE_p_func101(0xc439fd9fU, 0xeb2a1458U, 0x80f582a5U, 0xbf5543fbU);
        }

        HW_SCE_p_func100(0x12b85e69U, 0xc04bae5dU, 0xf4785e90U, 0x78ec8edfU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);

            HW_SCE_p_func101(0xf2e36b3cU, 0xebbf3e21U, 0x48da5e8eU, 0x8cc04b31U);
        }
        else
        {
            HW_SCE_p_func100(0x0302b6d9U, 0x61ee5517U, 0x58df0f03U, 0x105c2b8aU);
            WR1_PROG(REG_1404H, 0x11800000U);
            WR1_PROG(REG_1400H, 0x00c00041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x000001c0U);
            WR1_PROG(REG_1020H, 0x00000340U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1608H, 0x81900001U);
            WR1_PROG(REG_1400H, 0x00c90041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000001c0U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1600H, 0x00000040U);
            WR1_PROG(REG_1608H, 0x8190001fU);
            WR1_PROG(REG_1400H, 0x00c90041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000208U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000570U);

            WR1_PROG(REG_1004H, 0x08080015U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1404H, 0x11c00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0003dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000570U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x0b09d274U, 0x88c2df32U, 0x2ef37628U, 0xc35fe483U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);

                HW_SCE_p_func101(0xaded18d0U, 0x4f40d669U, 0xb9ececeaU, 0xa9dee670U);
            }
            else
            {
                WR1_PROG(REG_1600H, 0x38008b20U);
                WR1_PROG(REG_1600H, 0x180f25a9U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                HW_SCE_p_func100(0xa46585b9U, 0x36cf0a21U, 0xfc332a82U, 0x1351a0b0U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1014H, 0x00000480U);
                    WR1_PROG(REG_1018H, 0x00000570U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000250U);

                    WR1_PROG(REG_1004H, 0x08080013U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);
                    WR1_PROG(REG_143CH, 0x00000d00U);

                    WR1_PROG(REG_1404H, 0x12600000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                    WR1_PROG(REG_1400H, 0x00c0003dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_1020H, 0x000002f0U);

                    WR1_PROG(REG_1004H, 0x0808000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    HW_SCE_p_func101(0x039ae39fU, 0x4487af64U, 0x540a4b6cU, 0x6fc62708U);
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x000004e0U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x000001c0U);

                    WR1_PROG(REG_1004H, 0x08080009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);
                    WR1_PROG(REG_1014H, 0x00000528U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000208U);

                    WR1_PROG(REG_1004H, 0x08080009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x00000570U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000250U);

                    WR1_PROG(REG_1004H, 0x08080009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    HW_SCE_p_func101(0xb4e671bcU, 0x278d0699U, 0x121102dfU, 0x4ee0492bU);
                }

                HW_SCE_p_func100(0xb35aeb3eU, 0xa6e9057aU, 0xfa19f29cU, 0x45d3ae0dU);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);

                    HW_SCE_p_func101(0x54ebdcc4U, 0x9e8fe25bU, 0x4672508eU, 0x80631525U);
                }
                else
                {
                    HW_SCE_p_func100(0x88cb5f8bU, 0x375ae194U, 0xc622d07fU, 0x795ba842U);

                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);

                    WR1_PROG(REG_1004H, 0x08080004U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1404H, 0x11200000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                    WR1_PROG(REG_1400H, 0x00c0003dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000070U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000110U);

                    WR1_PROG(REG_1004H, 0x0808000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x000002a0U);
                    WR1_PROG(REG_1018H, 0x00000110U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000160U);

                    WR1_PROG(REG_1004H, 0x0808000fU);
                    WR1_PROG(REG_1408H, 0x00020000U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);
                    WR1_PROG(REG_143CH, 0x00000d00U);

                    WR1_PROG(REG_1014H, 0x000001c0U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);

                    WR1_PROG(REG_1004H, 0x08080002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x000002a0U);
                    WR1_PROG(REG_1018H, 0x00000930U);
                    WR1_PROG(REG_1020H, 0x000001b0U);

                    WR1_PROG(REG_1004H, 0x0808000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    WR1_PROG(REG_1014H, 0x00000930U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_1020H, 0x000001b0U);

                    WR1_PROG(REG_1004H, 0x0808000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    HW_SCE_p_func100(0xf224b527U, 0x279b15f7U, 0xf4f54512U, 0xa8d31a99U);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);

                        HW_SCE_p_func101(0x7b1e7f02U, 0x25d584e5U, 0xbdd3de50U, 0x4756583dU);
                    }
                    else
                    {
                        WR1_PROG(REG_1600H, 0x0000b400U);
                        WR1_PROG(REG_1600H, 0x797935bbU);

                        HW_SCE_p_func101(0x85943f8eU, 0x6e91092cU, 0x71720787U, 0xb3e7e36bU);
                    }
                }
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x797935bbU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    WR1_PROG(REG_1600H, 0x00007c1bU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func100(0xfb795218U, 0x81152a78U, 0x54cdacc0U, 0x6715d108U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xee6a4ca7U, 0x5e354fe3U, 0x477f2504U, 0x71c39cffU);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func102(0xf8007f76U, 0xdce4555dU, 0x87229698U, 0x7f2632adU);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
}
