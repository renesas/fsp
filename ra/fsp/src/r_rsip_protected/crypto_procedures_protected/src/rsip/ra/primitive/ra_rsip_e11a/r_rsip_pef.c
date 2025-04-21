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

rsip_ret_t r_rsip_pef (const uint32_t InData_Msg1[],
                       const uint32_t InData_Msg1Length[],
                       const uint32_t InData_EncMsg[],
                       const uint32_t InData_EncMsgLength[],
                       const uint32_t InData_Msg2[],
                       const uint32_t InData_Msg2Length[],
                       uint32_t       OutData_KDFInfo[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00ef0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000002c7U);
    WR1_PROG(REG_009CH, 0x80030060U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg1Length[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_EncMsgLength[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Msg2Length[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38008c80U);
    WR1_PROG(REG_0094H, 0xffffffdfU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    WR1_PROG(REG_0094H, 0x3420a8a0U);
    WR1_PROG(REG_0094H, 0x00000009U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0094H, 0x00000800U);
    WR1_PROG(REG_0094H, 0x00002403U);
    WR1_PROG(REG_0094H, 0x00002404U);
    WR1_PROG(REG_0094H, 0x00002405U);

    WR1_PROG(REG_0094H, 0x38008c00U);
    WR1_PROG(REG_0094H, 0x0000003fU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    r_rsip_func100(bswap_32big(0xa956ba27U),
                   bswap_32big(0xd3df7a09U),
                   bswap_32big(0x1ecf853fU),
                   bswap_32big(0xcba33ae5U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xe7aa7f9eU), bswap_32big(0x36296cb9U), bswap_32big(0x86d86cfcU),
                       bswap_32big(0x1203f970U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00000821U);

        WR1_PROG(REG_0094H, 0x00003405U);

        WR1_PROG(REG_0094H, 0x38000c84U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0x2a7c86b0U), bswap_32big(0xc5bf04e2U), bswap_32big(0x01f0c16bU),
                       bswap_32big(0x29ac6782U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x800100c0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_EncMsg[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef01U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0xa02954d3U), bswap_32big(0xe8e83489U), bswap_32big(0x2ca8c2c3U),
                           bswap_32big(0x19813641U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef01U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x7d0efc43U), bswap_32big(0x15efe684U), bswap_32big(0x29c3d9cbU),
                           bswap_32big(0xc31017d6U));
            r_rsip_func044();

            WR1_PROG(REG_0014H, 0x000007c1U);
            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xf7009d07U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_EncMsg[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_EncMsg[5]);

            WR1_PROG(REG_00B0H, 0x00001404U);
            WR1_PROG(REG_0000H, 0x00c10021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_EncMsg[9]);

            WR1_PROG(REG_00D0H, 0x9c100005U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            r_rsip_func100(bswap_32big(0x3e268571U), bswap_32big(0x4418e672U), bswap_32big(0x24651cdaU),
                           bswap_32big(0xc631e030U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00002c20U);
                r_rsip_func101(bswap_32big(0x53e9821eU),
                               bswap_32big(0xe29359c2U),
                               bswap_32big(0xefff844eU),
                               bswap_32big(0x3a60df2cU));
            }

            r_rsip_func101(bswap_32big(0x4f16ec55U), bswap_32big(0x2879b3ceU), bswap_32big(0x5214aa5bU),
                           bswap_32big(0x2e8f3981U));
        }

        WR1_PROG(REG_0094H, 0x38000c21U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        r_rsip_func100(bswap_32big(0xbd48f989U), bswap_32big(0x219e864cU), bswap_32big(0xefc9855cU),
                       bswap_32big(0x5c2a65d7U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);
        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xd751547aU), bswap_32big(0x57d391a5U), bswap_32big(0xe74e5fd6U),
                           bswap_32big(0x530a5906U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_00F4H, 0x00000010U);

            WR1_PROG(REG_0014H, 0x000007a4U);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_PROG(REG_002CH,
                     bswap_32big(0x6a09e667U),
                     bswap_32big(0xbb67ae85U),
                     bswap_32big(0x3c6ef372U),
                     bswap_32big(0xa54ff53aU),
                     bswap_32big(0x510e527fU),
                     bswap_32big(0x9b05688cU),
                     bswap_32big(0x1f83d9abU),
                     bswap_32big(0x5be0cd19U));

            WR1_PROG(REG_00F4H, 0x00000011U);

            WR1_PROG(REG_0094H, 0x00000821U);

            WR1_PROG(REG_0094H, 0x00003c01U);

            WR1_PROG(REG_0094H, 0x38000c63U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x4f916dedU), bswap_32big(0x02c13ef7U), bswap_32big(0xd8354c9cU),
                           bswap_32big(0x404f0090U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func100(bswap_32big(0x15198448U),
                               bswap_32big(0x82a53068U),
                               bswap_32big(0x06c2ee3bU),
                               bswap_32big(0x2ca02539U));

                WR1_PROG(REG_0094H, 0x00000800U);

                WR1_PROG(REG_0094H, 0x00003443U);
                WR1_PROG(REG_0094H, 0x0000a440U);
                WR1_PROG(REG_0094H, 0x00000003U);
                WR1_PROG(REG_0094H, 0x00026842U);

                WR1_PROG(REG_009CH, 0x81010040U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &S_RAM[0]);
                S_RAM[0] = bswap_32big(S_RAM[0]);

                WR1_PROG(REG_0094H, 0x000008a5U);

                WR1_PROG(REG_0094H, 0x000008c6U);

                for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
                {
                    WR1_PROG(REG_0014H, 0x000000c7U);
                    WR1_PROG(REG_009CH, 0x80010020U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, InData_Msg1[iLoop]);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0094H, 0x000008e7U);

                    for (jLoop = 0U; jLoop < 4; jLoop++)
                    {
                        WR1_PROG(REG_0094H, 0x01886c01U);
                        WR1_PROG(REG_0094H, 0x00086c21U);
                        WR1_PROG(REG_0094H, 0x342028a3U);
                        WR1_PROG(REG_009CH, 0x00000080U);
                        WR1_PROG(REG_0040H, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x687b081aU),
                                       bswap_32big(0xfe132f91U),
                                       bswap_32big(0xf067ee39U),
                                       bswap_32big(0x47afc98bU));
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            WR1_PROG(REG_009CH, 0x81010000U);
                            WR1_PROG(REG_0000H, 0x1009000dU);
                            WAIT_STS(REG_0004H, 30, 0);
                            WR1_PROG(REG_0040H, 0x00001800U);
                            WR1_PROG(REG_0000H, 0x11490005U);
                            WAIT_STS(REG_0004H, 30, 0);
                            WR1_PROG(REG_0040H, 0x00001800U);

                            WR1_PROG(REG_0094H, 0x00002ca0U);
                            r_rsip_func101(bswap_32big(0x8f6b5f6aU),
                                           bswap_32big(0xc9b60d78U),
                                           bswap_32big(0xff5eba82U),
                                           bswap_32big(0xa665ff82U));
                        }

                        WR1_PROG(REG_0094H, 0x00002ce0U);

                        r_rsip_func101(bswap_32big(0x8bd8129eU),
                                       bswap_32big(0x06fc7a77U),
                                       bswap_32big(0x52066d68U),
                                       bswap_32big(0xaddf6eaaU));
                    }

                    WR1_PROG(REG_0094H, 0x380088e0U);
                    WR1_PROG(REG_0094H, 0x00000004U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);
                    WR1_PROG(REG_0040H, 0x00402000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    WR1_PROG(REG_0094H, 0x00002cc0U);

                    r_rsip_func101(bswap_32big(0x442ef2efU),
                                   bswap_32big(0xb74fbc52U),
                                   bswap_32big(0x1cf84c81U),
                                   bswap_32big(0x01e67addU));
                }

                WR1_PROG(REG_0094H, 0x380008c2U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);
                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                r_rsip_func101(bswap_32big(0x9ee72464U),
                               bswap_32big(0x52e3b5beU),
                               bswap_32big(0xb8410189U),
                               bswap_32big(0x8ab883fbU));
            }

            WR1_PROG(REG_0094H, 0x38000c84U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00A60000U);

            r_rsip_func100(bswap_32big(0x8f82ea18U), bswap_32big(0x74d6f822U), bswap_32big(0x7b1d0ed8U),
                           bswap_32big(0x6bd0aa34U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_00B0H, 0x00001804U);
                WR1_PROG(REG_0000H, 0x11430081U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                r_rsip_func101(bswap_32big(0x9e99627aU),
                               bswap_32big(0x74abac6cU),
                               bswap_32big(0x5f4023c3U),
                               bswap_32big(0xa3c74cedU));
            }

            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_0094H, 0x00003861U);

            r_rsip_func100(bswap_32big(0x56f52dcbU), bswap_32big(0x43ba8a94U), bswap_32big(0xddc7b64fU),
                           bswap_32big(0x58be46aaU));

            WR1_PROG(REG_0094H, 0x00000800U);

            WR1_PROG(REG_0094H, 0x00003443U);
            WR1_PROG(REG_0094H, 0x0000a440U);
            WR1_PROG(REG_0094H, 0x00000003U);
            WR1_PROG(REG_0094H, 0x00026842U);

            WR1_PROG(REG_009CH, 0x81010040U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x000008c6U);

            for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
            {
                WR1_PROG(REG_0014H, 0x000000c7U);
                WR1_PROG(REG_009CH, 0x80010020U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, InData_Msg2[iLoop]);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x000008e7U);

                for (jLoop = 0U; jLoop < 4; jLoop++)
                {
                    WR1_PROG(REG_0094H, 0x01886c01U);
                    WR1_PROG(REG_0094H, 0x00086c21U);
                    WR1_PROG(REG_0094H, 0x342028a3U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00260000U);
                    r_rsip_func100(bswap_32big(0xfb412696U),
                                   bswap_32big(0x255df820U),
                                   bswap_32big(0x1e30963dU),
                                   bswap_32big(0x5ede9624U));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        WR1_PROG(REG_009CH, 0x81010000U);
                        WR1_PROG(REG_0000H, 0x1009000dU);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);
                        WR1_PROG(REG_0000H, 0x11490005U);
                        WAIT_STS(REG_0004H, 30, 0);
                        WR1_PROG(REG_0040H, 0x00001800U);

                        WR1_PROG(REG_0094H, 0x00002ca0U);
                        r_rsip_func101(bswap_32big(0x4cdc1d6cU),
                                       bswap_32big(0x09e0e2c6U),
                                       bswap_32big(0x5b596647U),
                                       bswap_32big(0xf43417ccU));
                    }

                    WR1_PROG(REG_0094H, 0x00002ce0U);

                    r_rsip_func101(bswap_32big(0xb7e59e7fU),
                                   bswap_32big(0x33badf95U),
                                   bswap_32big(0xf680ffacU),
                                   bswap_32big(0x81c47a9eU));
                }

                WR1_PROG(REG_0094H, 0x380088e0U);
                WR1_PROG(REG_0094H, 0x00000004U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);
                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00002cc0U);

                r_rsip_func101(bswap_32big(0xdad19425U),
                               bswap_32big(0x616ae551U),
                               bswap_32big(0x1ef03c06U),
                               bswap_32big(0xa634b6b4U));
            }

            WR1_PROG(REG_0094H, 0x380008c2U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);
            WR1_PROG(REG_0040H, 0x00402000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            WAIT_STS(REG_00F8H, 2, 0);

            WR1_PROG(REG_00F4H, 0x00000100U);

            WR1_PROG(REG_0040H, 0x00001600U);

            WR1_PROG(REG_00F4H, 0x00000020U);

            r_rsip_func100(bswap_32big(0xfce8c9d1U), bswap_32big(0x05b28f48U), bswap_32big(0x22ae00bfU),
                           bswap_32big(0xc533fbf2U));
            r_rsip_func103();

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x0c200104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_009CH, 0x80010000U);
            WR1_PROG(REG_0000H, 0x03410005U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0000H, 0x0001000dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x000034c0U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x9d08a8f8U), bswap_32big(0xeeb6e598U), bswap_32big(0x88f90ea8U),
                           bswap_32big(0x1cab19b8U));
            r_rsip_func043();

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x01799093U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x0000ef02U));
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func101(bswap_32big(0x5ed5a8e2U), bswap_32big(0x5dff1c45U), bswap_32big(0xa435e196U),
                           bswap_32big(0xd7acc765U));
            r_rsip_func044();

            r_rsip_func100(bswap_32big(0xfc3c89afU), bswap_32big(0xac7169caU), bswap_32big(0x71547106U),
                           bswap_32big(0x5f554f0fU));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000044U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x08000054U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_00D4H, 0x40000100U);
            WR1_PROG(REG_00D0H, 0xe7009d07U);
            WR1_PROG(REG_0000H, 0x00450021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KDFInfo[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KDFInfo[5]);

            r_rsip_func100(bswap_32big(0x03cb5bc7U), bswap_32big(0x4db758ebU), bswap_32big(0x204f610cU),
                           bswap_32big(0x8d6b6577U));
            WR1_PROG(REG_0014H, 0x000000a1U);
            WR1_PROG(REG_00D0H, 0x0c000104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x09108105U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &OutData_KDFInfo[9]);

            r_rsip_func100(bswap_32big(0x7a7c257fU), bswap_32big(0x7228db43U), bswap_32big(0xdbd827c7U),
                           bswap_32big(0x3316f326U));
            WR1_PROG(REG_009CH, 0x81010000U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_KDFInfo[0]);

            r_rsip_func102(bswap_32big(0xe31084a9U), bswap_32big(0xf8f3f4e3U), bswap_32big(0xcf71bfaaU),
                           bswap_32big(0x94b9f8f8U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
