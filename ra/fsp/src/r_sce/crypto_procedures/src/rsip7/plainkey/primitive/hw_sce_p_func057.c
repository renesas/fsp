/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func057 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    HW_SCE_p_func100(0x014fc442U, 0x7fb45e76U, 0x2e7fbef3U, 0x70d8c890U);
    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_1824H, 0x08000045U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &ARG1[0]);

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    HW_SCE_p_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x000000ffU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x97c16b1aU, 0xcab4e1e0U, 0xe83dc919U, 0x63d1c089U);
    HW_SCE_p_func043();

    WR1_PROG(REG_1600H, 0x000034e4U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x000000feU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x81188bcdU, 0xd465cb3aU, 0x5460ee88U, 0xfa6e9d6dU);
    HW_SCE_p_func044();

    HW_SCE_p_func100(0xea88f7e8U, 0x8c73c3daU, 0xada49d15U, 0xe6e78f26U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1000H, 0x00010000U);

    HW_SCE_p_func081();

    WR1_PROG(REG_1600H, 0x00007c01U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    oLoop = 0x00000000U;
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4U); )
        {
            HW_SCE_p_func100(0xabaeb1d2U, 0xdbce3d0aU, 0x2b27fdf2U, 0x45abd5cbU);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0xd900090dU);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG2[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG3[1 + iLoop]);

            HW_SCE_p_func101(0x0c156d4aU, 0x4726e434U, 0xc9151a06U, 0x39ab66f1U);
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        HW_SCE_p_func101(0x55094f4dU, 0x5dc73591U, 0xa8ee2f55U, 0xade97968U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
    {
        HW_SCE_p_func100(0x0a501155U, 0x1a1f7ec3U, 0x26602d39U, 0x83084874U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func061(0U, ARG2);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG3);
        HW_SCE_p_func100(0x150c4f50U, 0x44b7a9a3U, 0x78e48b23U, 0x9c62b9e7U);
        HW_SCE_p_func065(8U, ARG3);
        HW_SCE_p_func100(0x05e508ceU, 0x3c07de0aU, 0x7c89e370U, 0xb9503bedU);
        HW_SCE_p_func065(16U, ARG3);
        HW_SCE_p_func100(0x2e100529U, 0x3308d50fU, 0xd9c51be6U, 0x659036b2U);
        HW_SCE_p_func065(24U, ARG3);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0xc502c2c0U, 0x70f468d9U, 0x7a0d28efU, 0x0b986501U);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xd900090dU);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func100(0x7caf20d1U, 0xe59a5be5U, 0xf70e3425U, 0x2162d703U);
        HW_SCE_p_func060();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(36U, ARG3);
        HW_SCE_p_func100(0x8e65434eU, 0xf9ee6df3U, 0x05296722U, 0x60353489U);
        HW_SCE_p_func062(44U, ARG3);
        HW_SCE_p_func100(0x0253ea51U, 0x38f6d4b6U, 0x637263ecU, 0xcf8f3ed0U);
        HW_SCE_p_func062(52U, ARG3);
        HW_SCE_p_func100(0x9290b786U, 0xc813031aU, 0xb1cbb901U, 0xa6f4b465U);
        HW_SCE_p_func062(60U, ARG3);
        oLoop = 36U + 32U;

        HW_SCE_p_func101(0x505df6faU, 0xb9fa0edbU, 0x3c31bfd4U, 0x042e7292U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
    {
        HW_SCE_p_func100(0x69ed3d1aU, 0x35bb8c57U, 0x079e21f7U, 0xac20d974U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func061(0U, ARG2);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG3);
        HW_SCE_p_func100(0x34543cc0U, 0x37999e77U, 0x0508ded5U, 0xb1b65e73U);
        HW_SCE_p_func062(8U, ARG3);
        HW_SCE_p_func100(0x937c954eU, 0x7a67ef9dU, 0x371ad5a4U, 0x3bbab049U);
        HW_SCE_p_func062(16U, ARG3);
        HW_SCE_p_func100(0xa58bd013U, 0x0efa64a6U, 0x2d5bd251U, 0xa7b7908aU);
        HW_SCE_p_func062(24U, ARG3);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0xd42979e7U, 0xc4b53fa8U, 0x3dcc256eU, 0xe76e10cbU);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func061(32U, ARG2);
        iLoop = 32U + 32U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(32U, ARG3);
        HW_SCE_p_func100(0xd06106c1U, 0x19b7bb2aU, 0x65b22396U, 0x9fa6494fU);
        HW_SCE_p_func062(40U, ARG3);
        HW_SCE_p_func100(0xd0851840U, 0x4b4c5260U, 0x13248d04U, 0xd1912639U);
        HW_SCE_p_func062(48U, ARG3);
        HW_SCE_p_func100(0x6ec3050aU, 0x3ae09ab9U, 0xeabb2db6U, 0xfbf3de81U);
        HW_SCE_p_func062(56U, ARG3);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0xacf194b9U, 0x84383146U, 0xec2d6c29U, 0x88026692U);
        HW_SCE_p_func060();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(64U, ARG3);
        HW_SCE_p_func100(0x25b1416eU, 0xdff23336U, 0xfdeaa105U, 0x9efde552U);
        HW_SCE_p_func062(72U, ARG3);
        HW_SCE_p_func100(0x0311d7daU, 0xb5663fbaU, 0xbaaddda8U, 0x13c8f516U);
        HW_SCE_p_func062(80U, ARG3);
        HW_SCE_p_func100(0x4a84a314U, 0x900dd898U, 0x034b241bU, 0xc3225d84U);
        HW_SCE_p_func062(88U, ARG3);
        oLoop = 64U + 32U;

        HW_SCE_p_func101(0x103683c8U, 0x497bf486U, 0xe02b6b4aU, 0xe4323d0aU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
    {
        HW_SCE_p_func100(0xc408c4beU, 0x50c4375bU, 0xdaacc884U, 0xda0c28c2U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func063(0U, ARG2);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG3);
        HW_SCE_p_func100(0xba8c7f77U, 0x06385d3eU, 0x6abfcee5U, 0xfb7ee248U);
        HW_SCE_p_func065(8U, ARG3);
        HW_SCE_p_func100(0x7475812aU, 0xe09edbb1U, 0x10fbf3b6U, 0xa1c9018eU);
        HW_SCE_p_func065(16U, ARG3);
        HW_SCE_p_func100(0x839ddf35U, 0x5cefd93dU, 0x76abad37U, 0x4f1607ffU);
        HW_SCE_p_func065(24U, ARG3);
        HW_SCE_p_func100(0x9cc4f463U, 0x42cd7f68U, 0xb8b4c48cU, 0x11f223beU);
        HW_SCE_p_func065(32U, ARG3);
        HW_SCE_p_func100(0x042ed769U, 0xcfd046dbU, 0x69edcc25U, 0x27361e6aU);
        HW_SCE_p_func065(40U, ARG3);
        HW_SCE_p_func100(0xa55d021dU, 0xc4f07f79U, 0x3ef983b8U, 0x8cd5a80bU);
        HW_SCE_p_func065(48U, ARG3);
        HW_SCE_p_func100(0x82d51100U, 0xd69b1239U, 0x268dcc2aU, 0xd8fab087U);
        HW_SCE_p_func065(56U, ARG3);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0x6110b2b8U, 0xcfa5c11eU, 0x2f430ac2U, 0x77386c4aU);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xd900090dU);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func100(0x451c42b3U, 0x0706c49bU, 0x8747d30cU, 0x852579a5U);
        HW_SCE_p_func066();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(68U, ARG3);
        HW_SCE_p_func100(0x9553b5f1U, 0xac77ca51U, 0x848543d0U, 0xe55d60eaU);
        HW_SCE_p_func062(76U, ARG3);
        HW_SCE_p_func100(0x88501696U, 0x567cf779U, 0xc1d8cd77U, 0x728e8bb9U);
        HW_SCE_p_func062(84U, ARG3);
        HW_SCE_p_func100(0x092082f7U, 0x6155d1a3U, 0xc73057d8U, 0x0b0bdb12U);
        HW_SCE_p_func062(92U, ARG3);
        HW_SCE_p_func100(0xf1fbc9e4U, 0x230d7cdaU, 0xcefb4b87U, 0x6a8c2a0eU);
        HW_SCE_p_func062(100U, ARG3);
        HW_SCE_p_func100(0x837eb59cU, 0x4c9d208aU, 0x168303daU, 0xdabcb6cbU);
        HW_SCE_p_func062(108U, ARG3);
        HW_SCE_p_func100(0x2e4d7684U, 0xbf9edc91U, 0x0c555029U, 0xb34d1d45U);
        HW_SCE_p_func062(116U, ARG3);
        HW_SCE_p_func100(0xc5fda8f6U, 0x5cfbd5a3U, 0xb4ceaafdU, 0x0582633cU);
        HW_SCE_p_func062(124U, ARG3);
        oLoop = 68U + 64U;

        HW_SCE_p_func101(0x5569a977U, 0xc21a575aU, 0xe8630117U, 0x7e7da593U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
    {
        HW_SCE_p_func100(0x1107c72cU, 0x29affbb5U, 0x90f19911U, 0x1fb07f92U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func063(0U, ARG2);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG3);
        HW_SCE_p_func100(0x30c29bdfU, 0x4f879100U, 0x6b612180U, 0xe4f537daU);
        HW_SCE_p_func062(8U, ARG3);
        HW_SCE_p_func100(0x5c3a3e31U, 0x86b9e9c7U, 0xac219169U, 0x98806278U);
        HW_SCE_p_func062(16U, ARG3);
        HW_SCE_p_func100(0x453f9a6fU, 0xc6f5ad0bU, 0x37993f8eU, 0xe3aee985U);
        HW_SCE_p_func062(24U, ARG3);
        HW_SCE_p_func100(0xfe27efbcU, 0x58063c69U, 0x738af859U, 0x2692b69cU);
        HW_SCE_p_func062(32U, ARG3);
        HW_SCE_p_func100(0x8362c470U, 0x3fdb04d5U, 0x1df6b336U, 0xb77f3d0aU);
        HW_SCE_p_func062(40U, ARG3);
        HW_SCE_p_func100(0xacfe300cU, 0xf031c137U, 0x08123200U, 0xb9e65507U);
        HW_SCE_p_func062(48U, ARG3);
        HW_SCE_p_func100(0x593ef93bU, 0xc0f95a4fU, 0x78112f36U, 0x4d694a95U);
        HW_SCE_p_func062(56U, ARG3);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0x8df7f9f4U, 0xb5dd3cdbU, 0x9ca3751cU, 0x293567b0U);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func063(64U, ARG2);
        iLoop = 64U + 64U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(64U, ARG3);
        HW_SCE_p_func100(0xd7ce96f9U, 0x19570512U, 0xcb401159U, 0x830e068eU);
        HW_SCE_p_func062(72U, ARG3);
        HW_SCE_p_func100(0x4964b85dU, 0x1d0d6c23U, 0x4dee545dU, 0x94d7b6b7U);
        HW_SCE_p_func062(80U, ARG3);
        HW_SCE_p_func100(0x4f0af471U, 0x6f5faa44U, 0xdaea5248U, 0x3788c037U);
        HW_SCE_p_func062(88U, ARG3);
        HW_SCE_p_func100(0xea18875aU, 0xe99995b8U, 0x13e976b3U, 0x8c909715U);
        HW_SCE_p_func062(96U, ARG3);
        HW_SCE_p_func100(0xb8ce7a2cU, 0x06255c78U, 0x13832e71U, 0xf9f467b3U);
        HW_SCE_p_func062(104U, ARG3);
        HW_SCE_p_func100(0x8b9693d8U, 0xfd19485dU, 0x5a8d43e3U, 0x2d8ba186U);
        HW_SCE_p_func062(112U, ARG3);
        HW_SCE_p_func100(0x4e68bef9U, 0x8023a9c8U, 0x081034a4U, 0x7ce84db2U);
        HW_SCE_p_func062(120U, ARG3);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0xa5a0bc56U, 0x9d0ebe56U, 0x5f3936f3U, 0xa177265bU);
        HW_SCE_p_func066();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(128U, ARG3);
        HW_SCE_p_func100(0xa32e41b5U, 0xc68c0895U, 0x8070876eU, 0xb20e473dU);
        HW_SCE_p_func062(136U, ARG3);
        HW_SCE_p_func100(0x908f9fa9U, 0x3300540aU, 0x0aae4c8dU, 0x8f88ec0bU);
        HW_SCE_p_func062(144U, ARG3);
        HW_SCE_p_func100(0xc84a5121U, 0x1c99a6b5U, 0x8af88d7dU, 0xa19bf292U);
        HW_SCE_p_func062(152U, ARG3);
        HW_SCE_p_func100(0x7cbfc8b8U, 0x7330e2ceU, 0x229bcf44U, 0x4c1a68b8U);
        HW_SCE_p_func062(160U, ARG3);
        HW_SCE_p_func100(0x82417d19U, 0xd15cad02U, 0xb1766c82U, 0x3d940834U);
        HW_SCE_p_func062(168U, ARG3);
        HW_SCE_p_func100(0xece00fa4U, 0x96d62db7U, 0x77c6dbdaU, 0x9f2f6164U);
        HW_SCE_p_func062(176U, ARG3);
        HW_SCE_p_func100(0x23d59a6aU, 0x35ae4a7aU, 0x75b21fecU, 0x64512fc4U);
        HW_SCE_p_func062(184U, ARG3);
        oLoop = 128U + 64U;

        HW_SCE_p_func101(0xe8f064f9U, 0xcabf1265U, 0x5e619833U, 0x0a27de1aU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4U); )
        {
            HW_SCE_p_func100(0x5935f015U, 0xa7faa697U, 0x6daffbd8U, 0x7553f5d3U);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0xd900090dU);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG2[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe8008105U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG3[1 + iLoop]);

            HW_SCE_p_func101(0xdfabf01bU, 0x30fc4e73U, 0xe6281d2cU, 0xa33fadfdU);
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        HW_SCE_p_func101(0x7f3a87bfU, 0x4e796887U, 0x2b420216U, 0xe3d834a7U);
    }

    HW_SCE_p_func100(0xb9028d29U, 0x37d0a3b6U, 0x99afb95bU, 0x5e729e90U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &ARG3[1 + oLoop]);

    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_1824H, 0x0900090dU);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &ARG2[iLoop]);

    WR1_PROG(REG_1824H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00007c1cU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}

