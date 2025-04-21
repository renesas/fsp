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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func073 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

    r_rsip_func070(ARG1);

    WR1_PROG(REG_00A0H, 0x20010000U);

    WR1_PROG(REG_00B8H, 0x0000000aU);

    WR1_PROG(REG_00A4H, 0x04040010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    r_rsip_func073_sub002(0x0000141eU, 0x00c0001dU);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

    r_rsip_func073_sub001(0x001e000aU, 0x00140000U, 0x0404000aU);

    r_rsip_func073_sub001(0x00690014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func073_sub001(0x001e0069U, 0x00190000U, 0x0404000aU);
    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func073_sub001(0x006e0014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func073_sub001(0x001e006eU, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    r_rsip_func100(bswap_32big(0xe51f8c65U),
                   bswap_32big(0xafa0f132U),
                   bswap_32big(0x457067c3U),
                   bswap_32big(0x63aa4fc3U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        r_rsip_func101(bswap_32big(0x0d051ebaU), bswap_32big(0x01857d55U), bswap_32big(0x0e7c2091U),
                       bswap_32big(0x456e85efU));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x7095fd7cU), bswap_32big(0x9d8da667U), bswap_32big(0xb72431feU),
                       bswap_32big(0xa3cc89b9U));

        r_rsip_func073_sub001(0x001e0014U, 0x00190000U, 0x0404000aU);

        WR1_PROG(REG_00B4H, 0x0019006eU);
        WR1_PROG(REG_00B8H, 0x000f000aU);

        WR1_PROG(REG_00A4H, 0x04040000U);
        WR1_PROG(REG_0008H, 0x00020000U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);
        WR1_PROG(REG_0040H, 0x00000d00U);

        r_rsip_func073_sub001(0x005a000fU, 0x0014000aU, 0x04040002U);

        r_rsip_func073_sub002(0x00001423U, 0x00c00021U);

        r_rsip_func073_sub001(0x0023007eU, 0x000f0000U, 0x04040009U);

        r_rsip_func073_sub001(0x0014000fU, 0x000f000aU, 0x04040002U);

        r_rsip_func073_sub001(0x00140069U, 0x0032000aU, 0x04040002U);

        WR1_PROG(REG_00B8H, 0x00000005U);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        r_rsip_func073_sub001(0x00230069U, 0x000a0000U, 0x04040009U);

        r_rsip_func073_sub001(0x00370076U, 0x004b0005U, 0x04040002U);

        r_rsip_func073_sub001(0x0037007aU, 0x00500005U, 0x04040002U);

        r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        r_rsip_func073_sub001(0x00140037U, 0x00550005U, 0x04040002U);

        r_rsip_func073_sub001(0x0023005fU, 0x00280000U, 0x04040009U);

        r_rsip_func073_sub001(0x00230005U, 0x002d0000U, 0x04040009U);

        r_rsip_func073_sub002(0x00000415U, 0x00c00009U);

        r_rsip_func073_sub002(0x0000041aU, 0x00c00009U);
        r_rsip_func071(ARG1);

        r_rsip_func073_sub001(0x00230019U, 0x005a0000U, 0x04040009U);

        r_rsip_func073_sub001(0x0023001eU, 0x005f0000U, 0x04040009U);

        r_rsip_func073_sub001(0x00230055U, 0x00640000U, 0x04040009U);

        r_rsip_func073_sub001(0x004b005aU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func073_sub001(0x005a004bU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func073_sub001(0x0050005fU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func073_sub001(0x005f0050U, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0xb9566077U), bswap_32big(0xa869a624U), bswap_32big(0x91c0a503U),
                       bswap_32big(0xb237a2feU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func073_sub001(0x00550064U, 0x00730005U, 0x04040013U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func101(bswap_32big(0xd7e3cecdU), bswap_32big(0x8b7b1ee1U), bswap_32big(0xbc67898aU),
                           bswap_32big(0x8b664f2cU));
        }
        else
        {
            r_rsip_func073_sub001(0x00000064U, 0x0073002dU, 0x04040014U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func101(bswap_32big(0xbedc3908U), bswap_32big(0x59a03f6bU), bswap_32big(0xe822c771U),
                           bswap_32big(0x836f8299U));
        }

        r_rsip_func073_sub001(0x0023000fU, 0x00370000U, 0x04040009U);

        r_rsip_func073_sub001(0x00190019U, 0x00190000U, 0x0404000aU);

        r_rsip_func073_sub001(0x001e001eU, 0x001e0000U, 0x0404000aU);

        r_rsip_func073_sub001(0x00230023U, 0x00230000U, 0x0404000aU);

        WR1_PROG(REG_0094H, 0x00000800U);
        for (iLoop = 0U; iLoop < 2U; iLoop++)
        {
            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            r_rsip_func100(bswap_32big(0x7e0f99f1U), bswap_32big(0x81ee8e4bU), bswap_32big(0x5086e2c3U),
                           bswap_32big(0xd795b1a0U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func073_sub003(0x00000834U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                r_rsip_func073_sub003(0x00000835U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                r_rsip_func073_sub003(0x0000082fU);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                r_rsip_func073_sub003(0x00000830U);

                r_rsip_func101(bswap_32big(0xdf46a32cU),
                               bswap_32big(0x72583a76U),
                               bswap_32big(0xe3721519U),
                               bswap_32big(0xe77e20c1U));
            }
            else
            {
                r_rsip_func073_sub003(0x00000836U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                r_rsip_func073_sub003(0x00000837U);
                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                r_rsip_func073_sub003(0x00000831U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                r_rsip_func073_sub003(0x00000832U);

                r_rsip_func101(bswap_32big(0x96205348U),
                               bswap_32big(0xdfbab52aU),
                               bswap_32big(0xe2032801U),
                               bswap_32big(0x738733c3U));
            }

            WR1_PROG(REG_0094H, 0x00000821U);

            for (jLoop = 0U; jLoop < 4; jLoop++)
            {
                WR1_PROG(REG_0094H, 0x000034a1U);

                WR1_PROG(REG_0094H, 0x00026ca5U);

                WR1_PROG(REG_0094H, 0x00003865U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000010U);

                WR1_PROG(REG_0094H, 0x00003885U);

                WR1_PROG(REG_0094H, 0x00000842U);

                for (kLoop = 0U; kLoop < 32U; kLoop++)
                {
                    WR1_PROG(REG_0094H, 0x000008a5U);

                    WR1_PROG(REG_0094H, 0x01816ca3U);
                    WR1_PROG(REG_0094H, 0x01816ca4U);
                    WR1_PROG(REG_0094H, 0x00016c63U);
                    WR1_PROG(REG_0094H, 0x00016c84U);

                    r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
                    WR1_PROG(REG_0014H, 0x000000a5U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                    r_rsip_func073_sub001(0x00140019U, 0x000f0000U, 0x0404000aU);

                    WR1_PROG(REG_0040H, 0x00a10000U);

                    r_rsip_func073_sub001(0x00140023U, 0x000f0000U, 0x0404000aU);

                    WR1_PROG(REG_0040H, 0x00a10000U);

                    r_rsip_func100(bswap_32big(0x2b1f86b5U),
                                   bswap_32big(0xf5b9d861U),
                                   bswap_32big(0xc82f2c65U),
                                   bswap_32big(0xc4687346U));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func073_sub001(0x00000023U, 0x0023002dU, 0x04040014U);
                        WR1_PROG(REG_0040H, 0x00000d00U);

                        r_rsip_func101(bswap_32big(0xbde49965U),
                                       bswap_32big(0x0d0d1696U),
                                       bswap_32big(0x1c607d76U),
                                       bswap_32big(0x7f417cf7U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x6b2aaa69U),
                                       bswap_32big(0x00bf2424U),
                                       bswap_32big(0xf2ffd601U),
                                       bswap_32big(0xaba2b99dU));
                    }

                    WR1_PROG(REG_0094H, 0x38000ca5U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00A60000U);

                    r_rsip_func100(bswap_32big(0x67212861U),
                                   bswap_32big(0xd8c310acU),
                                   bswap_32big(0x9b689d3cU),
                                   bswap_32big(0x9afd5f3aU));
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        r_rsip_func100(bswap_32big(0xf479a314U),
                                       bswap_32big(0xdfe9af19U),
                                       bswap_32big(0x185e9d85U),
                                       bswap_32big(0x4f87fb86U));

                        r_rsip_func073_sub002(0x00001414U, 0x00c00021U);

                        WR1_PROG(REG_0094H, 0x00007c05U);
                        WR1_PROG(REG_0040H, 0x00600000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                        {
                            r_rsip_func073_sub001(0x0014004bU, 0x003c0000U, 0x04040009U);

                            r_rsip_func073_sub001(0x00140050U, 0x00410000U, 0x04040009U);

                            r_rsip_func073_sub001(0x00140055U, 0x00460000U, 0x04040009U);

                            r_rsip_func101(bswap_32big(0x1425e8e3U),
                                           bswap_32big(0x31e98008U),
                                           bswap_32big(0x2877e31bU),
                                           bswap_32big(0xb45b870aU));
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                        {
                            r_rsip_func073_sub001(0x0014005aU, 0x003c0000U, 0x04040009U);

                            r_rsip_func073_sub001(0x0014005fU, 0x00410000U, 0x04040009U);

                            r_rsip_func073_sub001(0x00140064U, 0x00460000U, 0x04040009U);

                            r_rsip_func101(bswap_32big(0xe12eda4eU),
                                           bswap_32big(0xb8c2ed9fU),
                                           bswap_32big(0x10f27d9dU),
                                           bswap_32big(0x73707f8dU));
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                        {
                            r_rsip_func073_sub001(0x00140069U, 0x003c0000U, 0x04040009U);

                            r_rsip_func073_sub001(0x0014006eU, 0x00410000U, 0x04040009U);

                            r_rsip_func073_sub001(0x00140073U, 0x00460000U, 0x04040009U);

                            r_rsip_func101(bswap_32big(0x623a11c3U),
                                           bswap_32big(0xf034b81eU),
                                           bswap_32big(0xc4078888U),
                                           bswap_32big(0xbd54d177U));
                        }

                        r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
                        WR1_PROG(REG_0014H, 0x000000a5U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

                        r_rsip_func073_sub001(0x00140019U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        r_rsip_func073_sub001(0x00140023U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        r_rsip_func100(bswap_32big(0xdaa956deU),
                                       bswap_32big(0x0c7c031eU),
                                       bswap_32big(0x7c42c768U),
                                       bswap_32big(0xfe329550U));
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            r_rsip_func073_sub001(0x0014003cU, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            r_rsip_func073_sub001(0x00140046U, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            r_rsip_func100(bswap_32big(0x59d010c3U),
                                           bswap_32big(0x1fc32a4cU),
                                           bswap_32big(0x0aacd4b9U),
                                           bswap_32big(0xc083d948U));
                            WR1_PROG(REG_0040H, 0x00400000U);
                            WR1_PROG(REG_0024H, 0x00000000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                r_rsip_func073_sub001(0x003c0019U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func073_sub001(0x0019003cU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func073_sub001(0x0041001eU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func073_sub001(0x001e0041U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func073_sub001(0x00460023U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func073_sub001(0x00230046U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                r_rsip_func100(bswap_32big(0x7fa3a6f4U), bswap_32big(0x35b13a28U),
                                               bswap_32big(0xf73f700bU), bswap_32big(0x2d1d21cfU));
                                WR1_PROG(REG_0040H, 0x00400000U);
                                WR1_PROG(REG_0024H, 0x00000000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    r_rsip_func073_sub001(0x00460023U, 0x00230005U, 0x04040013U);
                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xcc940023U), bswap_32big(0x9773c658U),
                                                   bswap_32big(0x1cbf869fU), bswap_32big(0xa3c137ccU));
                                }
                                else
                                {
                                    r_rsip_func073_sub001(0x00000023U, 0x0023002dU, 0x04040014U);
                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    r_rsip_func101(bswap_32big(0xab00fed4U), bswap_32big(0xea4b72ceU),
                                                   bswap_32big(0xd2d32f79U), bswap_32big(0xb80bf60cU));
                                }
                            }
                            else
                            {
                                r_rsip_func101(bswap_32big(0x2f10472bU), bswap_32big(0xa565ceabU),
                                               bswap_32big(0x84fb7398U), bswap_32big(0x79aa14b7U));
                            }
                        }
                        else
                        {
                            r_rsip_func073_sub002(0x00001414U, 0x00c00021U);

                            r_rsip_func073_sub001(0x0014003cU, 0x00190000U, 0x04040009U);

                            r_rsip_func073_sub001(0x00140041U, 0x001e0000U, 0x04040009U);

                            r_rsip_func073_sub001(0x00140046U, 0x00230000U, 0x04040009U);

                            r_rsip_func101(bswap_32big(0x52fb41bdU),
                                           bswap_32big(0x99656440U),
                                           bswap_32big(0xd8a369d6U),
                                           bswap_32big(0xed622873U));
                        }
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0x4af66ec9U),
                                       bswap_32big(0x1f247ddaU),
                                       bswap_32big(0x42447029U),
                                       bswap_32big(0x06ad03a0U));
                    }

                    WR1_PROG(REG_0094H, 0x00002c40U);
                    r_rsip_func101(bswap_32big(0x38cc1e35U),
                                   bswap_32big(0x10cde69dU),
                                   bswap_32big(0xb85b0c0dU),
                                   bswap_32big(0x4b92ca7aU));
                }

                WR1_PROG(REG_0094H, 0x38008840U);
                WR1_PROG(REG_0094H, 0x00000020U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00002c20U);

                r_rsip_func101(bswap_32big(0xc997ce56U),
                               bswap_32big(0x92887195U),
                               bswap_32big(0x8307ccfeU),
                               bswap_32big(0x52858abaU));
            }

            WR1_PROG(REG_0094H, 0x38008820U);
            WR1_PROG(REG_0094H, 0x00000004U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            WR1_PROG(REG_0040H, 0x00402000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x00002c00U);

            r_rsip_func101(bswap_32big(0x7122c320U), bswap_32big(0x33c9265dU), bswap_32big(0xff4872d5U),
                           bswap_32big(0x9775d9ebU));
        }

        WR1_PROG(REG_0094H, 0x38008800U);
        WR1_PROG(REG_0094H, 0x00000002U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        WR1_PROG(REG_0040H, 0x00402000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func073_sub002(0x00001414U, 0x00c00021U);

        r_rsip_func073_sub001(0x0014000aU, 0x00690000U, 0x04040009U);

        r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000001U));

        r_rsip_func073_sub001(0x00140023U, 0x002d0000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x03cb7535U), bswap_32big(0x24719250U), bswap_32big(0x8a837ee3U),
                       bswap_32big(0x760a920bU));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            r_rsip_func101(bswap_32big(0x5953f40eU), bswap_32big(0x96487652U), bswap_32big(0x9b0925e2U),
                           bswap_32big(0x2f78b031U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x643c0951U), bswap_32big(0x6782e12aU), bswap_32big(0x17098bcfU),
                           bswap_32big(0x0e3ac121U));

            r_rsip_func073_sub001(0x00140023U, 0x00280005U, 0x04040002U);

            r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, bswap_32big(0x00000002U));

            r_rsip_func073_sub001(0x00140005U, 0x000f0000U, 0x0404000aU);

            WR1_PROG(REG_00B4H, 0x000f0028U);
            WR1_PROG(REG_00B8H, 0x00140005U);

            WR1_PROG(REG_00A4H, 0x04040000U);
            WR1_PROG(REG_0008H, 0x00020000U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            r_rsip_func073_sub001(0x00140019U, 0x00280005U, 0x04040002U);

            r_rsip_func073_sub001(0x00690028U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func073_sub001(0x00280069U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_0040H, 0x00210000U);

            r_rsip_func100(bswap_32big(0xf7d1e4a6U), bswap_32big(0xddf205c8U), bswap_32big(0xc5208fc0U),
                           bswap_32big(0xa45a0551U));
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00000800U);

                r_rsip_func101(bswap_32big(0x13ac2c4eU),
                               bswap_32big(0x5fb35462U),
                               bswap_32big(0x74e9ad80U),
                               bswap_32big(0xdb70185fU));
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0x665331ecU);

                r_rsip_func101(bswap_32big(0x6058aaeaU),
                               bswap_32big(0xbdb73076U),
                               bswap_32big(0x7cef9943U),
                               bswap_32big(0xc19bf57eU));
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x665331ecU);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
