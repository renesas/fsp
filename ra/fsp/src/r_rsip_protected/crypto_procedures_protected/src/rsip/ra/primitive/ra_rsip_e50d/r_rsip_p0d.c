/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_p0d (const uint32_t InData_KeyCertificate[],
                       const uint32_t InData_KeyCertificateLength[],
                       const uint32_t InData_KeyCertificateSignature[],
                       const uint32_t InData_KeyCertificatePubKey[],
                       const uint32_t InData_ImgPkHash[],
                       const uint32_t InData_OemRootPkHashIndex[],
                       const uint32_t InData_CodeCertificate[],
                       const uint32_t InData_CodeCertificateLength[],
                       const uint32_t InData_CodeCertificateSignature[],
                       const uint32_t InData_CodeCertificatePubKey[],
                       const uint32_t InData_Image[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       MAX_CNT,
                       uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t iTemp = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x000d0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000004c7U);
    WR1_PROG(REG_1608H, 0x800501e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_CodeCertificateLength[0]);
    for (iLoop = 0U; iLoop < 4; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_CodeCertificatePubKey[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000006c7U);
    WR1_PROG(REG_1608H, 0x800702c0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyCertificateLength[0]);
    for (iLoop = 0U; iLoop < 4; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyCertificatePubKey[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = 0U; iLoop < 2U; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_ImgPkHash[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00000bffU);

    WR1_PROG(REG_1600H, 0x34202af8U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202b19U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202b3aU);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202b5bU);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202b7cU);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202b96U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x00003417U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x08000818U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x00003419U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x0800081aU);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x0000341bU);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x0800081cU);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x34202bd0U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202a11U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202a32U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202a53U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x34202a6fU);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x00003410U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x08000811U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x00003412U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x08000813U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);

    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x5a19a28aU),
                   bswap_32big(0xc3fce2b4U),
                   bswap_32big(0x0a45ed75U),
                   bswap_32big(0xbf0e93e6U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_14BCH, 0x00000020U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PARAM_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x3d321d68U), bswap_32big(0x7b98f83cU), bswap_32big(0xe3d49b91U),
                       bswap_32big(0x3c8ef22dU));

        WR1_PROG(REG_2000H, 0x00000001U);

        WR1_PROG(REG_2004H, 0x00000050U);

        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1600H, 0x00003436U);

        WR1_PROG(REG_1600H, 0x01836c01U);
        WR1_PROG(REG_1600H, 0x00036c21U);

        WR1_PROG(REG_1608H, 0x81020000U);
        WR1_PROG(REG_1408H, 0x0000500aU);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
        S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

        r_rsip_func100(bswap_32big(0xcf472b35U), bswap_32big(0x51d463b2U), bswap_32big(0x683122a4U),
                       bswap_32big(0xef03e8e6U));
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, S_RAM[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, S_RAM[0 + 1]);

        WR1_PROG(REG_1600H, 0x00003417U);
        WR1_PROG(REG_1600H, 0x00046800U);
        WR1_PROG(REG_1600H, 0x00026c00U);

        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        WR1_PROG(REG_1600H, 0x000008a5U);

        for (iLoop = 0U; iLoop < S_RAM[0]; )
        {
            WR1_PROG(REG_1444H, 0x000003c4U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyCertificate[iLoop]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000a4a0U);
            WR1_PROG(REG_1600H, 0x00000004U);

            r_rsip_func101(bswap_32big(0x5081cf2aU), bswap_32big(0xb75c1a81U), bswap_32big(0xdfd26d14U),
                           bswap_32big(0x22a59465U));
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0xf7f01f28U), bswap_32big(0x22a79eddU), bswap_32big(0xbd0db958U),
                       bswap_32big(0x62431676U));

        WR1_PROG(REG_1600H, 0x38000805U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1404H, 0x10000000U);

        WR1_PROG(REG_1600H, 0x00003416U);
        WR1_PROG(REG_1600H, 0x00026800U);
        WR1_PROG(REG_1600H, 0x38008ec0U);
        WR1_PROG(REG_1600H, 0x00000003U);
        WR1_PROG(REG_1600H, 0x20002c00U);

        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        WR1_PROG(REG_1600H, 0x00003445U);
        WR1_PROG(REG_1600H, 0x00026c42U);

        WR1_PROG(REG_1600H, 0x000034d6U);
        WR1_PROG(REG_1600H, 0x000030c0U);

        WR1_PROG(REG_1600H, 0x0000b520U);
        WR1_PROG(REG_1600H, 0x00000180U);

        iTemp = iLoop;
        for (iLoop = iTemp; iLoop < S_RAM[0]; iLoop++)
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010100U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_KeyCertificate[iLoop]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x00000004U);

            for (jLoop = 0U; jLoop < 4; jLoop++)
            {
                WR1_PROG(REG_1600H, 0x00003020U);

                WR1_PROG(REG_1600H, 0x01886ce8U);
                WR1_PROG(REG_1600H, 0x00086d08U);

                WR1_PROG(REG_1600H, 0x00000863U);
                WR1_PROG(REG_1600H, 0x3c002859U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1600H, 0x3c002b42U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1600H, 0x38000c63U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0xebe2ac0eU),
                               bswap_32big(0x78ec0a6cU),
                               bswap_32big(0x70feb889U),
                               bswap_32big(0x78e0d136U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1608H, 0x810100e0U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x10c90005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    r_rsip_func101(bswap_32big(0x89721c48U),
                                   bswap_32big(0x99e823a3U),
                                   bswap_32big(0xd38c74f1U),
                                   bswap_32big(0xe470a45dU));
                }

                WR1_PROG(REG_1600H, 0x00000863U);
                WR1_PROG(REG_1600H, 0x3c002857U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1600H, 0x3c002b02U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1600H, 0x38000c63U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0xc43af23bU),
                               bswap_32big(0xe09d4306U),
                               bswap_32big(0xb6ffe941U),
                               bswap_32big(0x84ff5436U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1608H, 0x810100e0U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x10c90005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    r_rsip_func101(bswap_32big(0xe9471574U),
                                   bswap_32big(0x4340cc57U),
                                   bswap_32big(0xcdb1caa3U),
                                   bswap_32big(0x37a86996U));
                }

                WR1_PROG(REG_1600H, 0x00000863U);
                WR1_PROG(REG_1600H, 0x3c00285bU);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1600H, 0x3c002b82U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1600H, 0x38000c63U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0xa9784474U),
                               bswap_32big(0x615bc6edU),
                               bswap_32big(0xd250cc05U),
                               bswap_32big(0xe48f0defU));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x02003ce9U);
                    WR1_PROG(REG_1600H, 0x00002d20U);
                    r_rsip_func101(bswap_32big(0xe2108c5cU),
                                   bswap_32big(0x69bf3cd0U),
                                   bswap_32big(0x69f2cd61U),
                                   bswap_32big(0xcd0cb441U));
                }

                WR1_PROG(REG_1600H, 0x00000863U);
                WR1_PROG(REG_1600H, 0x3c0028c2U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1600H, 0x38000c63U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                r_rsip_func100(bswap_32big(0x0fcb4f5aU),
                               bswap_32big(0x3fb69779U),
                               bswap_32big(0xc8405c5dU),
                               bswap_32big(0x2c245611U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1608H, 0x810100e0U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x11490005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    r_rsip_func101(bswap_32big(0xa17f657bU),
                                   bswap_32big(0xa2c98cdfU),
                                   bswap_32big(0xfa206f23U),
                                   bswap_32big(0x6b449d7fU));
                }

                WR1_PROG(REG_1600H, 0x00002c40U);

                r_rsip_func101(bswap_32big(0x0f39f874U),
                               bswap_32big(0x115e6b00U),
                               bswap_32big(0x7e87ceebU),
                               bswap_32big(0x0187cd32U));
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x08000c21U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x00002ca0U);

            r_rsip_func101(bswap_32big(0x5f998a3bU), bswap_32big(0x45335dd5U), bswap_32big(0x8922604aU),
                           bswap_32big(0xc8e4775fU));
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000805U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x0d2466fbU), bswap_32big(0xde474549U), bswap_32big(0xb5a9eca5U),
                       bswap_32big(0x3095153fU));
        WR1_PROG(REG_1600H, 0x00003416U);
        WR1_PROG(REG_1600H, 0x00008c00U);
        WR1_PROG(REG_1600H, 0x00000003U);

        WR1_PROG(REG_1600H, 0x0000b440U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x00002840U);

        WR1_PROG(REG_1600H, 0x00008c40U);
        WR1_PROG(REG_1600H, 0x00000003U);

        WR1_PROG(REG_1608H, 0x81010040U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = bswap_32big(S_RAM[0]);

        WR1_PROG(REG_1600H, 0x000008a5U);

        WR1_PROG(REG_1600H, 0x0000b460U);
        WR1_PROG(REG_1600H, 0x00000000U);

        for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
        {
            WR1_PROG(REG_1608H, 0x81010060U);
            WR1_PROG(REG_1400H, 0x11490005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x1009000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00086c63U);

            WR1_PROG(REG_1600H, 0x00002ca0U);

            r_rsip_func101(bswap_32big(0xd2e2a759U), bswap_32big(0xfff888c7U), bswap_32big(0x29f1d2d0U),
                           bswap_32big(0xc0c1e4ebU));
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x38000845U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WAIT_STS(REG_2030H, 4, 1);

        WR1_PROG(REG_1600H, 0x00000929U);
        WR1_PROG(REG_1608H, 0x80880009U);
        WR1_PROG(REG_1400H, 0x03450021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_2000H, 0x00000001U);

        WR1_PROG(REG_2004H, 0x00000050U);

        WR1_PROG(REG_2014H, 0x00000000U);
        WR1_PROG(REG_2010H, 0x00000200U);

        WR1_PROG(REG_1404H, 0x10000000U);
        WR1_PROG(REG_1400H, 0x01430041U);

        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WAIT_STS(REG_2030H, 4, 1);

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1600H, 0x000000fdU);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x0000000dU));
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xdb3052a8U), bswap_32big(0xb7f1af97U), bswap_32big(0xdf35612aU),
                       bswap_32big(0xc22fb133U));
        r_rsip_func043();

        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x08000045U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, bswap_32big(0x37b96c17U), bswap_32big(0xf6bb586aU), bswap_32big(0x4c781037U),
                 bswap_32big(0x17ba4317U));

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0x0900890fU);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_OemRootPkHashIndex[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_OemRootPkHashIndex[4]);

        WR1_PROG(REG_1A24H, 0x08000055U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00850011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A24H, 0x08000055U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00850011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0xf18ea06fU), bswap_32big(0x273dad0dU), bswap_32big(0x3dde803eU),
                       bswap_32big(0xa801896eU));
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_14BCH, 0x00000020U);
            WAIT_STS(REG_142CH, 12, 0);

            return RSIP_RET_VERIFICATION_FAIL;
        }
        else
        {
            WR1_PROG(REG_1404H, 0x10000000U);
            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1600H, 0x00000060U);
            WR1_PROG(REG_1608H, 0x80900001U);
            WR1_PROG(REG_1400H, 0x03430041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x19100000U);
            WR1_PROG(REG_1444H, 0x00000fc1U);
            WR1_PROG(REG_182CH, 0x00000300U);
            WR1_PROG(REG_1824H, 0x08008107U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyCertificateSignature[0]);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyCertificateSignature[4]);
            WR1_PROG(REG_1400H, 0x00c10021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x19600000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyCertificateSignature[8]);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyCertificateSignature[12]);
            WR1_PROG(REG_1400H, 0x00c10021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x00000b5aU);
            WR1_PROG(REG_1600H, 0x00000b9cU);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, bswap_32big(0x00000d01U));
            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x1cbf9403U), bswap_32big(0xff5237f6U), bswap_32big(0x1aea544cU),
                           bswap_32big(0xdb30e1bdU));
            r_rsip_func073(InData_DomainParam);

            r_rsip_func100(bswap_32big(0xda978056U), bswap_32big(0x812e105dU), bswap_32big(0x3d36d693U),
                           bswap_32big(0xe9f42218U));
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_14BCH, 0x00000020U);
                WAIT_STS(REG_142CH, 12, 0);

                return RSIP_RET_VERIFICATION_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x4506db4aU),
                               bswap_32big(0x401df0a0U),
                               bswap_32big(0xf695b240U),
                               bswap_32big(0x20b6de78U));

                WR1_PROG(REG_1600H, 0x000036cfU);
                WR1_PROG(REG_1600H, 0x000036f0U);
                WR1_PROG(REG_1600H, 0x00003711U);
                WR1_PROG(REG_1600H, 0x00003732U);
                WR1_PROG(REG_1600H, 0x00003753U);

                WR1_PROG(REG_2000H, 0x00000001U);

                WR1_PROG(REG_2004H, 0x00000050U);

                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010160U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, MAX_CNT);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1600H, 0x0000342bU);

                WR1_PROG(REG_1600H, 0x01826c01U);
                WR1_PROG(REG_1600H, 0x00026c21U);

                WR1_PROG(REG_1600H, 0x000008c6U);
                WR1_PROG(REG_1600H, 0x0c002436U);
                WR1_PROG(REG_1600H, 0x00802406U);

                WR1_PROG(REG_1600H, 0x01836c01U);
                WR1_PROG(REG_1600H, 0x00036c21U);

                WR1_PROG(REG_1608H, 0x81020000U);
                WR1_PROG(REG_1408H, 0x0000500aU);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

                r_rsip_func100(bswap_32big(0x4fe5e312U),
                               bswap_32big(0xb57c2757U),
                               bswap_32big(0xb4663336U),
                               bswap_32big(0x744515d8U));
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, S_RAM[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, S_RAM[0 + 1]);

                WR1_PROG(REG_1600H, 0x00003417U);
                WR1_PROG(REG_1600H, 0x00046800U);
                WR1_PROG(REG_1600H, 0x00026c00U);

                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x0000000dU));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x501f45b0U),
                               bswap_32big(0xcf4c42d9U),
                               bswap_32big(0xf3329b50U),
                               bswap_32big(0xc52a8eebU));
                r_rsip_func103();

                r_rsip_func100(bswap_32big(0x0601662cU),
                               bswap_32big(0x07d78a49U),
                               bswap_32big(0xd0710447U),
                               bswap_32big(0x796ca9e2U));
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x0c200184U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

                WR1_PROG(REG_1444H, 0x000003a1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_PROG(REG_1420H,
                         bswap_32big(0x8ab22685U),
                         bswap_32big(0xbfab115bU),
                         bswap_32big(0x841c0f17U),
                         bswap_32big(0xa1af8aa1U));

                WR1_PROG(REG_1824H, 0x0e0c0446U);

                WR1_PROG(REG_1600H, 0x0000b7e0U);
                WR1_PROG(REG_1600H, 0x00000090U);

                WR1_PROG(REG_1444H, 0x000007c7U);
                WR1_PROG(REG_1608H, 0x8088001fU);
                for (iLoop = 0U; iLoop < 8U; iLoop++)
                {
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, InData_CodeCertificate[iLoop]);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1608H, 0x8188001fU);
                WR1_PROG(REG_1400H, 0x02490021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000b4a0U);
                WR1_PROG(REG_1600H, 0x00000008U);

                for (iLoop = 8; iLoop < S_RAM[0]; )
                {
                    WR1_PROG(REG_1444H, 0x000003caU);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_CodeCertificate[iLoop]);

                    WR1_PROG(REG_1600H, 0x0000a4a0U);
                    WR1_PROG(REG_1600H, 0x00000004U);

                    r_rsip_func101(bswap_32big(0x505bd04aU),
                                   bswap_32big(0x6f02fbc4U),
                                   bswap_32big(0xa1cf524aU),
                                   bswap_32big(0xe64025b6U));
                    iLoop = iLoop + 4U;
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func100(bswap_32big(0x83bff524U),
                               bswap_32big(0xed503092U),
                               bswap_32big(0x9ffd14dfU),
                               bswap_32big(0x9d981f0eU));

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1404H, 0x10000000U);

                WR1_PROG(REG_1600H, 0x00003416U);
                WR1_PROG(REG_1600H, 0x00026800U);
                WR1_PROG(REG_1600H, 0x38008ec0U);
                WR1_PROG(REG_1600H, 0x00000003U);
                WR1_PROG(REG_1600H, 0x20002c00U);

                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_1600H, 0x00003445U);
                WR1_PROG(REG_1600H, 0x00026c42U);

                WR1_PROG(REG_1600H, 0x000034d6U);
                WR1_PROG(REG_1600H, 0x000030c0U);

                iTemp = iLoop;
                for (iLoop = iTemp; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x80010100U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, InData_CodeCertificate[iLoop]);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x0000b420U);
                    WR1_PROG(REG_1600H, 0x00000004U);

                    for (jLoop = 0U; jLoop < 4; jLoop++)
                    {
                        WR1_PROG(REG_1600H, 0x00003020U);

                        WR1_PROG(REG_1600H, 0x01886ce8U);
                        WR1_PROG(REG_1600H, 0x00086d08U);

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c002859U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x3c002b42U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x8c164b95U),
                                       bswap_32big(0x3c32fd0fU),
                                       bswap_32big(0x0a516bb1U),
                                       bswap_32big(0xddf95c50U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1608H, 0x810100e0U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x10c90005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0xec0fc5c8U),
                                           bswap_32big(0x6144c68aU),
                                           bswap_32big(0xb7e7bcbeU),
                                           bswap_32big(0xb7ede7f5U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c002857U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x3c002b02U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x0af6d1f2U),
                                       bswap_32big(0x8665d3c5U),
                                       bswap_32big(0x50d1dd0eU),
                                       bswap_32big(0x3ef364c4U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1608H, 0x810100e0U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x10c90005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0xb1432e78U),
                                           bswap_32big(0x0995a7b7U),
                                           bswap_32big(0x66d6bf47U),
                                           bswap_32big(0xd08fde38U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1600H, 0x3c0028c2U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x65ccdc79U),
                                       bswap_32big(0xaf4bfebfU),
                                       bswap_32big(0x673edc84U),
                                       bswap_32big(0x009b678cU));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1608H, 0x810100e0U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x12490005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func101(bswap_32big(0x5ad8157eU),
                                           bswap_32big(0x08efb79bU),
                                           bswap_32big(0x8435a772U),
                                           bswap_32big(0x9a2b12d9U));
                        }

                        WR1_PROG(REG_1600H, 0x00002c40U);

                        r_rsip_func101(bswap_32big(0xd3d39bcaU),
                                       bswap_32big(0x465e7014U),
                                       bswap_32big(0x83a9b1c2U),
                                       bswap_32big(0x44ddb393U));
                    }

                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x08000c21U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    WR1_PROG(REG_1600H, 0x00002ca0U);

                    r_rsip_func101(bswap_32big(0xace4cca9U),
                                   bswap_32big(0xb4da0198U),
                                   bswap_32big(0x44496754U),
                                   bswap_32big(0x94724b21U));
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x0000b7c0U);
                WR1_PROG(REG_1600H, 0x00000030U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, bswap_32big(0x00000d01U));
                WR1_PROG(REG_1458H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x7dda89d5U),
                               bswap_32big(0x7fe11744U),
                               bswap_32big(0x2b9e0094U),
                               bswap_32big(0xc98f0645U));
                r_rsip_func083(InData_Image);

                WR1_PROG(REG_1600H, 0x00000929U);
                WR1_PROG(REG_1608H, 0x80880009U);
                WR1_PROG(REG_1400H, 0x03450021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_2000H, 0x00000001U);

                WR1_PROG(REG_2004H, 0x00000050U);

                WR1_PROG(REG_2014H, 0x00000000U);
                WR1_PROG(REG_2010H, 0x00000200U);

                WR1_PROG(REG_1404H, 0x10000000U);
                WR1_PROG(REG_1400H, 0x01430041U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WAIT_STS(REG_2030H, 4, 1);

                WR1_PROG(REG_1600H, 0x0000b520U);
                WR1_PROG(REG_1600H, 0x00000180U);
                WR1_PROG(REG_1A24H, 0x08000045U);
                WR1_PROG(REG_1608H, 0x81840009U);
                WR1_PROG(REG_1400H, 0x00890011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1A24H, 0x9c000005U);
                WR1_PROG(REG_1400H, 0x00850011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x0000a520U);
                WR1_PROG(REG_1600H, 0x00000010U);
                WR1_PROG(REG_1A24H, 0x08000045U);
                WR1_PROG(REG_1608H, 0x81840009U);
                WR1_PROG(REG_1400H, 0x00890011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1A24H, 0x9c000005U);
                WR1_PROG(REG_1400H, 0x00850011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                r_rsip_func100(bswap_32big(0x7e6c155eU),
                               bswap_32big(0xe34ab487U),
                               bswap_32big(0xdb30c0afU),
                               bswap_32big(0x42fa0182U));
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_14BCH, 0x00000020U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return RSIP_RET_VERIFICATION_FAIL;
                }
                else
                {
                    WR1_PROG(REG_1404H, 0x10000000U);
                    WR1_PROG(REG_1600H, 0x0000b420U);
                    WR1_PROG(REG_1600H, 0x00000060U);
                    WR1_PROG(REG_1608H, 0x80900001U);
                    WR1_PROG(REG_1400H, 0x03430041U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1404H, 0x19100000U);
                    WR1_PROG(REG_1444H, 0x00000fc1U);
                    WR1_PROG(REG_182CH, 0x00000300U);
                    WR1_PROG(REG_1824H, 0x08008107U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_CodeCertificateSignature[0]);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_CodeCertificateSignature[4]);
                    WR1_PROG(REG_1400H, 0x00c10021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1404H, 0x19600000U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_CodeCertificateSignature[8]);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR4_ADDR(REG_1420H, &InData_CodeCertificateSignature[12]);
                    WR1_PROG(REG_1400H, 0x00c10021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00000b5aU);
                    WR1_PROG(REG_1600H, 0x00000b9cU);

                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000d02U));
                    WR1_PROG(REG_1458H, 0x00000000U);

                    r_rsip_func101(bswap_32big(0x032af6f9U),
                                   bswap_32big(0x1566cf9aU),
                                   bswap_32big(0x17afdde4U),
                                   bswap_32big(0xa92c3c12U));
                    r_rsip_func073(InData_DomainParam);

                    r_rsip_func100(bswap_32big(0x1f6c4198U),
                                   bswap_32big(0x9c46fd47U),
                                   bswap_32big(0xa53c2456U),
                                   bswap_32big(0x3c2e5212U));
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_14BCH, 0x00000020U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return RSIP_RET_VERIFICATION_FAIL;
                    }
                    else
                    {
                        WR1_PROG(REG_2000H, 0x00000001U);

                        WR1_PROG(REG_2004H, 0x00000050U);

                        WR1_PROG(REG_2008H, 0x00000013U);

                        WR1_PROG(REG_1600H, 0x000037ebU);

                        WR1_PROG(REG_1600H, 0x0000b4e0U);
                        WR1_PROG(REG_1600H, 0x01522594U);

                        WR1_PROG(REG_1444H, 0x000000a7U);
                        WR1_PROG(REG_1608H, 0x800103a0U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, bswap_32big(0x0000000dU));
                        WR1_PROG(REG_1458H, 0x00000000U);

                        r_rsip_func101(bswap_32big(0x810d03cbU),
                                       bswap_32big(0x3b5ba7afU),
                                       bswap_32big(0xfceb03bbU),
                                       bswap_32big(0x128b21b9U));
                        r_rsip_func082();

                        WR1_PROG(REG_1600H, 0x0000357fU);

                        WR1_PROG(REG_1600H, 0x00000800U);
                        WR1_PROG(REG_1600H, 0x00003436U);
                        WR1_PROG(REG_1600H, 0x01836c01U);
                        WR1_PROG(REG_1600H, 0x00036c21U);

                        WR1_PROG(REG_1600H, 0x00000842U);
                        WR1_PROG(REG_1600H, 0x0000346bU);
                        WR1_PROG(REG_1600H, 0x01856c43U);
                        WR1_PROG(REG_1600H, 0x00056c63U);

                        WR1_PROG(REG_1600H, 0x0c002423U);
                        WR1_PROG(REG_1600H, 0x00802402U);

                        WR1_PROG(REG_1600H, 0x00000842U);
                        WR1_PROG(REG_1600H, 0x0c00a420U);
                        WR1_PROG(REG_1600H, 0x00000200U);
                        WR1_PROG(REG_1600H, 0x00802402U);

                        WR1_PROG(REG_1600H, 0x38001001U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        r_rsip_func100(bswap_32big(0x28a09012U),
                                       bswap_32big(0x32c1bbe5U),
                                       bswap_32big(0x75350176U),
                                       bswap_32big(0x07ea20f0U));
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1444H, 0x00000020U);
                            WR1_PROG(REG_2014H, 0x00000000U);
                            WR1_PROG(REG_1444H, 0x00000020U);
                            WR1_PROG(REG_2010H, 0x00000080U);

                            WR1_PROG(REG_200CH, 0x00000001U);

                            WAIT_STS(REG_2030H, 8, 0);

                            WR1_PROG(REG_1444H, 0x00000020U);
                            WR1_PROG(REG_2014H, 0x00000000U);
                            WR1_PROG(REG_1444H, 0x00000020U);
                            WR1_PROG(REG_2010H, 0x00000000U);

                            WR1_PROG(REG_200CH, 0x00000100U);

                            WAIT_STS(REG_2030H, 4, 1);

                            r_rsip_func100(bswap_32big(0x3470fe60U),
                                           bswap_32big(0x6038d875U),
                                           bswap_32big(0x5c49920cU),
                                           bswap_32big(0x1466ad29U));
                            WR1_PROG(REG_1408H, 0x00004022U);
                            for (iLoop = 0U; iLoop < 8U; iLoop++)
                            {
                                WAIT_STS(REG_1408H, 30, 1);
                                RD1_ADDR(REG_1420H, &OutData_MAC[iLoop]);
                            }

                            WR1_PROG(REG_1458H, 0x00000000U);

                            WR1_PROG(REG_1B08H, 0x00000216U);

                            r_rsip_func102(bswap_32big(0x23089c47U),
                                           bswap_32big(0xbacad5d2U),
                                           bswap_32big(0x1aaf3f13U),
                                           bswap_32big(0xd09fa1e1U));
                            WR1_PROG(REG_149CH, 0x00000040U);
                            WAIT_STS(REG_142CH, 12, 0);

                            return RSIP_RET_PASS;
                        }
                        else
                        {
                            r_rsip_func100(bswap_32big(0xd4c123c7U),
                                           bswap_32big(0x1a9ed1c9U),
                                           bswap_32big(0x8e8a5ab1U),
                                           bswap_32big(0xf78792fdU));
                            WR1_PROG(REG_1608H, 0x81020000U);
                            WR1_PROG(REG_1408H, 0x0000500aU);
                            WAIT_STS(REG_1408H, 30, 1);
                            RD1_ADDR(REG_1420H, &S_RAM[0]);
                            S_RAM[0] = bswap_32big(S_RAM[0]);
                            WAIT_STS(REG_1408H, 30, 1);
                            RD1_ADDR(REG_1420H, &S_RAM[0 + 1]);
                            S_RAM[0 + 1] = bswap_32big(S_RAM[0 + 1]);

                            WR1_PROG(REG_1444H, 0x00000040U);
                            WR1_PROG(REG_2014H, S_RAM[0]);
                            WR1_PROG(REG_1444H, 0x00000040U);
                            WR1_PROG(REG_2010H, S_RAM[0 + 1]);

                            WR1_PROG(REG_200CH, 0x00000001U);

                            r_rsip_func100(bswap_32big(0x1a9d11bfU),
                                           bswap_32big(0x62cf9404U),
                                           bswap_32big(0x6962b083U),
                                           bswap_32big(0xf19a64d2U));
                            WR1_PROG(REG_1444H, 0x000003a1U);
                            WR1_PROG(REG_1824H, 0x08000045U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR4_PROG(REG_1420H, bswap_32big(0x8ab22685U), bswap_32big(0xbfab115bU),
                                     bswap_32big(0x841c0f17U), bswap_32big(0xa1af8aa1U));

                            WR1_PROG(REG_1600H, 0x00003416U);
                            WR1_PROG(REG_1600H, 0x00026800U);
                            WR1_PROG(REG_1600H, 0x00008c00U);
                            WR1_PROG(REG_1600H, 0xfffffffcU);

                            WR1_PROG(REG_1608H, 0x81010000U);
                            WR1_PROG(REG_1408H, 0x00005006U);
                            WAIT_STS(REG_1408H, 30, 1);
                            RD1_ADDR(REG_1420H, &S_RAM[0]);
                            S_RAM[0] = bswap_32big(S_RAM[0]);

                            WR1_PROG(REG_1600H, 0x000008a5U);

                            WR1_PROG(REG_1824H, 0x0e0c0446U);

                            for (iLoop = 0U; iLoop < S_RAM[0]; )
                            {
                                WR1_PROG(REG_1444H, 0x000003caU);
                                WAIT_STS(REG_1444H, 31, 1);
                                WR4_ADDR(REG_1420H, &InData_CodeCertificate[iLoop]);

                                WR1_PROG(REG_1600H, 0x0000a4a0U);
                                WR1_PROG(REG_1600H, 0x00000004U);

                                r_rsip_func101(bswap_32big(0x5c292978U), bswap_32big(0x60c7bff0U),
                                               bswap_32big(0x3ef9b0a2U), bswap_32big(0x96ff5accU));
                                iLoop = iLoop + 4U;
                            }

                            WR1_PROG(REG_1458H, 0x00000000U);
                            r_rsip_func100(bswap_32big(0x807d1fd1U),
                                           bswap_32big(0xafdd4ee9U),
                                           bswap_32big(0x6121e6b6U),
                                           bswap_32big(0x4fc0714bU));

                            WR1_PROG(REG_1600H, 0x38000805U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);

                            WR1_PROG(REG_143CH, 0x00402000U);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            WR1_PROG(REG_1600H, 0x00003416U);
                            WR1_PROG(REG_1600H, 0x0000a400U);
                            WR1_PROG(REG_1600H, 0x00000003U);

                            WR1_PROG(REG_1600H, 0x00026800U);

                            WR1_PROG(REG_1608H, 0x81010000U);
                            WR1_PROG(REG_1408H, 0x00005006U);
                            WAIT_STS(REG_1408H, 30, 1);
                            RD1_ADDR(REG_1420H, &S_RAM[0]);
                            S_RAM[0] = bswap_32big(S_RAM[0]);

                            WR1_PROG(REG_1600H, 0x00003445U);
                            WR1_PROG(REG_1600H, 0x00026c42U);

                            WR1_PROG(REG_1600H, 0x000034d6U);
                            WR1_PROG(REG_1600H, 0x000030c0U);

                            iTemp = iLoop;
                            for (iLoop = iTemp; iLoop < S_RAM[0]; iLoop++)
                            {
                                WR1_PROG(REG_1444H, 0x000000c7U);
                                WR1_PROG(REG_1608H, 0x80010100U);
                                WAIT_STS(REG_1444H, 31, 1);
                                WR1_PROG(REG_1420H, InData_CodeCertificate[iLoop]);
                                WR1_PROG(REG_1458H, 0x00000000U);

                                WR1_PROG(REG_1600H, 0x0000b420U);
                                WR1_PROG(REG_1600H, 0x00000004U);

                                for (jLoop = 0U; jLoop < 4; jLoop++)
                                {
                                    WR1_PROG(REG_1600H, 0x00003020U);

                                    WR1_PROG(REG_1600H, 0x01886ce8U);
                                    WR1_PROG(REG_1600H, 0x00086d08U);

                                    WR1_PROG(REG_1600H, 0x00000863U);
                                    WR1_PROG(REG_1600H, 0x3c0028c2U);
                                    WR1_PROG(REG_1600H, 0x20002c60U);
                                    WR1_PROG(REG_1600H, 0x38000c63U);
                                    WR1_PROG(REG_1608H, 0x00000080U);
                                    WR1_PROG(REG_143CH, 0x00260000U);

                                    r_rsip_func100(bswap_32big(0x94552a48U), bswap_32big(0xe58be834U),
                                                   bswap_32big(0x9ff2f743U), bswap_32big(0xb0673975U));
                                    WR1_PROG(REG_143CH, 0x00400000U);

                                    if (CHCK_STS(REG_143CH, 22, 1))
                                    {
                                        WR1_PROG(REG_1608H, 0x810100e0U);
                                        WR1_PROG(REG_1400H, 0x1009000dU);
                                        WAIT_STS(REG_1404H, 30, 0);
                                        WR1_PROG(REG_143CH, 0x00001800U);
                                        WR1_PROG(REG_1400H, 0x12490005U);
                                        WAIT_STS(REG_1404H, 30, 0);
                                        WR1_PROG(REG_143CH, 0x00001800U);

                                        r_rsip_func101(bswap_32big(0x81c74b5cU), bswap_32big(0x4453b1cdU),
                                                       bswap_32big(0x3ce7e6f4U), bswap_32big(0xcdd3e4a0U));
                                    }

                                    WR1_PROG(REG_1600H, 0x00002c40U);

                                    r_rsip_func101(bswap_32big(0x3260293cU), bswap_32big(0xcff54e13U),
                                                   bswap_32big(0x2b81adb4U), bswap_32big(0xcac1a2daU));
                                }

                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x08000c21U);
                                WR1_PROG(REG_1608H, 0x00000080U);
                                WR1_PROG(REG_143CH, 0x00260000U);
                                WR1_PROG(REG_143CH, 0x00402000U);
                                WR1_PROG(REG_1458H, 0x00000000U);

                                WR1_PROG(REG_1600H, 0x00002ca0U);

                                r_rsip_func101(bswap_32big(0x4af10ec7U), bswap_32big(0x81f4dd98U),
                                               bswap_32big(0x067aea8cU), bswap_32big(0xd733d0a5U));
                            }

                            WR1_PROG(REG_1458H, 0x00000000U);

                            WR1_PROG(REG_1600H, 0x38000805U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);
                            WR1_PROG(REG_143CH, 0x00402000U);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            WR1_PROG(REG_1404H, 0x19100000U);
                            WR1_PROG(REG_1400H, 0x11430081U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1404H, 0x19600000U);
                            WR1_PROG(REG_1400H, 0x11430081U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1600H, 0x0000b7c0U);
                            WR1_PROG(REG_1600H, 0x00000080U);

                            WR1_PROG(REG_1444H, 0x000000a7U);
                            WR1_PROG(REG_1608H, 0x800103a0U);
                            WAIT_STS(REG_1444H, 31, 1);
                            WR1_PROG(REG_1420H, bswap_32big(0x00000d02U));
                            WR1_PROG(REG_1458H, 0x00000000U);

                            r_rsip_func101(bswap_32big(0x0ea2b246U),
                                           bswap_32big(0x20949da3U),
                                           bswap_32big(0xb7b4fd6fU),
                                           bswap_32big(0x1f73d099U));
                            r_rsip_func083(InData_Image);

                            WR1_PROG(REG_1824H, 0x9c000005U);
                            WR1_PROG(REG_1600H, 0x0000b7e0U);
                            WR1_PROG(REG_1600H, 0x00000030U);
                            WR1_PROG(REG_1608H, 0x8184001fU);
                            WR1_PROG(REG_1400H, 0x00490011U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            r_rsip_func100(bswap_32big(0x34d0cf7cU),
                                           bswap_32big(0xa8cff4e4U),
                                           bswap_32big(0x82ae773bU),
                                           bswap_32big(0x3893daa4U));
                            WR1_PROG(REG_143CH, 0x00400000U);

                            if (CHCK_STS(REG_143CH, 22, 1))
                            {
                                r_rsip_func102(bswap_32big(0x651d6ce0U), bswap_32big(0xeb3ef632U),
                                               bswap_32big(0x6ff722e0U), bswap_32big(0xfb5aa02bU));
                                WR1_PROG(REG_14BCH, 0x00000020U);
                                WAIT_STS(REG_142CH, 12, 0);

                                return RSIP_RET_FAIL;
                            }
                            else
                            {
                                r_rsip_func100(bswap_32big(0xdb69aebfU), bswap_32big(0x07da4621U),
                                               bswap_32big(0x6540a723U), bswap_32big(0xe2d99dddU));

                                WR1_PROG(REG_1408H, 0x00004022U);
                                for (iLoop = 0U; iLoop < 8U; iLoop++)
                                {
                                    WAIT_STS(REG_1408H, 30, 1);
                                    RD1_ADDR(REG_1420H, &OutData_MAC[iLoop]);
                                }

                                WR1_PROG(REG_1458H, 0x00000000U);

                                WR1_PROG(REG_1B08H, 0x00000216U);

                                r_rsip_func102(bswap_32big(0x0a5197c9U), bswap_32big(0xa558050dU),
                                               bswap_32big(0x79626149U), bswap_32big(0x69be5213U));
                                WR1_PROG(REG_149CH, 0x00000040U);
                                WAIT_STS(REG_142CH, 12, 0);

                                return RSIP_RET_PASS;
                            }
                        }
                    }
                }
            }
        }
    }
}
