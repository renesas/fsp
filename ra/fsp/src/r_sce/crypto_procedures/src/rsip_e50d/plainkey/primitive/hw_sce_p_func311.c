/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func311 (void)
{
    WR1_PROG(REG_1404H, 0x1b680000U);
    WR1_PROG(REG_1400H, 0x00c00331U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1014H, 0x00000530U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000d88U);

    WR1_PROG(REG_1004H, 0x10100009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000630U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000e98U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    while (1)
    {
        WR1_PROG(REG_1404H, 0x1ae00000U);
        WR1_PROG(REG_1608H, 0x80010080U);
        WR1_PROG(REG_1400H, 0x03430005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00030005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x38000c84U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        HW_SCE_p_func100(0xe45d5563U, 0x4c082d54U, 0x0afac442U, 0xd489c53eU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1014H, 0x00000b68U);
            WR1_PROG(REG_1018H, 0x00000d88U);
            WR1_PROG(REG_1020H, 0x00000b68U);

            WR1_PROG(REG_1004H, 0x11110009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000948U);
            WR1_PROG(REG_1018H, 0x00000e98U);
            WR1_PROG(REG_1020H, 0x00000948U);

            WR1_PROG(REG_1004H, 0x21210009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func101(0x4c8110c0U, 0x3c272b26U, 0x88150c05U, 0xc95ef49fU);
        }
        else
        {
            WR1_PROG(REG_1014H, 0x00000b68U);
            WR1_PROG(REG_1018H, 0x00000d88U);
            WR1_PROG(REG_1020H, 0x00000a58U);

            WR1_PROG(REG_1004H, 0x1111000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x19d00000U);
            WR1_PROG(REG_1608H, 0x800100a0U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000d88U);
            WR1_PROG(REG_1018H, 0x00000b68U);
            WR1_PROG(REG_1020H, 0x00000a58U);

            WR1_PROG(REG_1004H, 0x1111000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x19d00000U);
            WR1_PROG(REG_1608H, 0x800100c0U);
            WR1_PROG(REG_1400H, 0x03430005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00030005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x38000cc6U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x3e577b9eU, 0x3e991902U, 0x2f3f4537U, 0xc65ac32eU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1404H, 0x18400000U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WR1_PROG(REG_1400H, 0x03430005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00030005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x38000ce7U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                HW_SCE_p_func100(0x395862d7U, 0xae65ede2U, 0x3f8968f0U, 0x63031466U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1014H, 0x00000c78U);
                    WR1_PROG(REG_1018H, 0x00000948U);
                    WR1_PROG(REG_1020H, 0x00000a58U);

                    WR1_PROG(REG_1004H, 0x2121000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1404H, 0x19500000U);
                    WR1_PROG(REG_1608H, 0x80010100U);
                    WR1_PROG(REG_1400H, 0x00030005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x03430005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1600H, 0x00002d00U);

                    WR1_PROG(REG_1404H, 0x19d00000U);
                    WR1_PROG(REG_1608H, 0x81010100U);
                    WR1_PROG(REG_1400H, 0x00c00085U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c90005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000b68U);
                    WR1_PROG(REG_1018H, 0x00000a58U);
                    WR1_PROG(REG_1020H, 0x00000b68U);

                    WR1_PROG(REG_1004H, 0x1111000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1404H, 0x19500000U);
                    WR1_PROG(REG_1608H, 0x81010100U);
                    WR1_PROG(REG_1400H, 0x00c00005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c90005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c00101U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000948U);
                    WR1_PROG(REG_1018H, 0x00000a58U);
                    WR1_PROG(REG_1020H, 0x00000948U);

                    WR1_PROG(REG_1004H, 0x21210009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    HW_SCE_p_func101(0x0d516bf6U, 0x832ae795U, 0x7f2583f0U, 0x655a2731U);
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x38000ca5U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);

                    HW_SCE_p_func100(0xeae539d9U, 0x354e00f6U, 0xd2d99db2U, 0x14f54fb1U);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1014H, 0x00000948U);
                        WR1_PROG(REG_1018H, 0x00000e98U);
                        WR1_PROG(REG_1020H, 0x00000a58U);

                        WR1_PROG(REG_1004H, 0x2121000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_1404H, 0x19500000U);
                        WR1_PROG(REG_1608H, 0x80010100U);
                        WR1_PROG(REG_1400H, 0x03430005U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x00030005U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1600H, 0x38000d08U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00A60000U);

                        HW_SCE_p_func100(0x9ba996f0U, 0x81f5fcebU, 0xcdac4e70U, 0x7be4e64bU);
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            HW_SCE_p_func101(0x8e0d5e8cU, 0x4f0d5a7aU, 0x187dd700U, 0x10ea3972U);

                            break;
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x18400000U);
                            WR1_PROG(REG_1400H, 0x00c00109U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1014H, 0x00000b68U);
                            WR1_PROG(REG_1018H, 0x00000d88U);
                            WR1_PROG(REG_1020H, 0x00000b68U);

                            WR1_PROG(REG_1004H, 0x1111000aU);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            WR1_PROG(REG_1014H, 0x00000a58U);
                            WR1_PROG(REG_1018H, 0x00000948U);
                            WR1_PROG(REG_1020H, 0x00000948U);

                            WR1_PROG(REG_1004H, 0x21210009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            HW_SCE_p_func101(0x402267b5U, 0xdb2d43bfU, 0x9e2bc874U, 0xedb11de1U);
                        }
                    }
                    else
                    {
                        WR1_PROG(REG_1404H, 0x18400000U);
                        WR1_PROG(REG_1608H, 0x80010120U);
                        WR1_PROG(REG_1400H, 0x00030005U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x03430005U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1600H, 0x38000d29U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);

                        HW_SCE_p_func100(0xd61d9b05U, 0xe1a3bc4aU, 0xcf36fd92U, 0xe8bb066eU);
                        WR1_PROG(REG_143CH, 0x00400000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            HW_SCE_p_func101(0xea761542U, 0x6abb438bU, 0x93a6c886U, 0xb9196220U);

                            break;
                        }
                        else
                        {
                            WR1_PROG(REG_1404H, 0x18400000U);
                            WR1_PROG(REG_1400H, 0x00c00009U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1404H, 0x19d00000U);
                            WR1_PROG(REG_1608H, 0x81010120U);
                            WR1_PROG(REG_1400H, 0x00c00085U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x00c90005U);
                            WAIT_STS(REG_1404H, 30, 0);
                            WR1_PROG(REG_143CH, 0x00001800U);

                            WR1_PROG(REG_1014H, 0x00000b68U);
                            WR1_PROG(REG_1018H, 0x00000a58U);
                            WR1_PROG(REG_1020H, 0x00000b68U);

                            WR1_PROG(REG_1004H, 0x21210009U);
                            WR1_PROG(REG_1000H, 0x00010001U);
                            WAIT_STS(REG_1000H, 0, 0);

                            HW_SCE_p_func101(0xdaa756deU, 0xf04bb26dU, 0x1f2163bcU, 0xbe104359U);
                        }
                    }
                }
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000b68U);
                WR1_PROG(REG_1018H, 0x00000d88U);
                WR1_PROG(REG_1020H, 0x00000b68U);

                WR1_PROG(REG_1004H, 0x1111000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000948U);
                WR1_PROG(REG_1018H, 0x00000e98U);
                WR1_PROG(REG_1020H, 0x00000948U);

                WR1_PROG(REG_1004H, 0x2121000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                HW_SCE_p_func101(0xa809ff8dU, 0x07cfc0f5U, 0x72ec2711U, 0x0930801fU);
            }
        }
    }

    WR1_PROG(REG_1014H, 0x00000948U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000838U);

    WR1_PROG(REG_1004H, 0x20200009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1014H, 0x00000b68U);
    WR1_PROG(REG_1018H, 0x00000c78U);
    WR1_PROG(REG_1020H, 0x00000738U);

    WR1_PROG(REG_1004H, 0x10100009U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
