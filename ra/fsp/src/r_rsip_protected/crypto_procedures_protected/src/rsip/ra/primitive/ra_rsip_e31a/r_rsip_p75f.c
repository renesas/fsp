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

rsip_ret_t r_rsip_p75f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Msg[],
                        const uint32_t InData_MAC[],
                        const uint32_t InData_length[],
                        uint32_t       MAX_CNT,
                        uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_0118H, 0, 1);

    WR1_PROG(REG_0014H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR16_ADDR(REG_002CH, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_0014H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_002CH, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_0014H, 0x00000000U);
    WAIT_STS(REG_0118H, 8, 0);
    WR1_PROG(REG_0040H, 0x00001600U);

    WAIT_STS(REG_0118H, 4, 1);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x1000b480U);
    WR1_PROG(REG_0094H, 0x00000002U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00270000U);

    r_rsip_func100(bswap_32big(0xc804ffebU),
                   bswap_32big(0x26845802U),
                   bswap_32big(0xc9cd8cfdU),
                   bswap_32big(0xc1a99009U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func100(bswap_32big(0xcf547221U), bswap_32big(0x005453bbU), bswap_32big(0xe0165c3dU),
                       bswap_32big(0x120bf70cU));

        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            r_rsip_func100(bswap_32big(0xac7b7390U), bswap_32big(0xbc1bca0fU), bswap_32big(0x59c728cbU),
                           bswap_32big(0xc16fa142U));
            WR1_PROG(REG_0008H, 0x00004022U);
            WAIT_STS(REG_0008H, 30, 1);
            RD8_ADDR(REG_002CH, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0xcb60cd78U), bswap_32big(0xfbfc5e79U), bswap_32big(0x35b7a68eU),
                           bswap_32big(0x57ef7c51U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            r_rsip_func100(bswap_32big(0xd59155f3U), bswap_32big(0x3b15c752U), bswap_32big(0x9aa85cebU),
                           bswap_32big(0x14027b3aU));
            WR1_PROG(REG_0008H, 0x0000401eU);
            WAIT_STS(REG_0008H, 30, 1);
            RD7_ADDR(REG_002CH, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0x47b1204cU), bswap_32big(0x046f1a18U), bswap_32big(0x6bf11294U),
                           bswap_32big(0xb67f7532U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            r_rsip_func100(bswap_32big(0x28ec35caU), bswap_32big(0x08206558U), bswap_32big(0x91594faeU),
                           bswap_32big(0x52157764U));
            WR1_PROG(REG_0008H, 0x00004032U);
            WAIT_STS(REG_0008H, 30, 1);
            RD12_ADDR(REG_002CH, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0x198db8baU), bswap_32big(0x8563c421U), bswap_32big(0xde3e0a29U),
                           bswap_32big(0x55702096U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            r_rsip_func100(bswap_32big(0x4443231eU), bswap_32big(0xe40aede0U), bswap_32big(0xfb2f24ebU),
                           bswap_32big(0x7c636397U));
            WR1_PROG(REG_0008H, 0x00004042U);
            WAIT_STS(REG_0008H, 30, 1);
            RD16_ADDR(REG_002CH, &OutData_MAC[0]);

            r_rsip_func102(bswap_32big(0x91661b6cU), bswap_32big(0xe88d5083U), bswap_32big(0x02a175e4U),
                           bswap_32big(0x1b942fe6U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);
        }

        return RSIP_RET_PASS;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x7418a982U), bswap_32big(0x6e2c1a02U), bswap_32big(0x5f52c846U),
                       bswap_32big(0x65bf5b9fU));

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010020U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_length[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0094H, 0x0000b440U);
            WR1_PROG(REG_0094H, 0x00000020U);

            r_rsip_func101(bswap_32big(0x3d75fd16U), bswap_32big(0xab91f882U), bswap_32big(0x3c2eb166U),
                           bswap_32big(0x960acdd5U));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0094H, 0x0000b440U);
            WR1_PROG(REG_0094H, 0x0000001cU);

            r_rsip_func101(bswap_32big(0x025a0f7eU), bswap_32big(0xc22bbc0cU), bswap_32big(0x0f12f27dU),
                           bswap_32big(0x95e1152dU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000005U)
        {
            WR1_PROG(REG_0094H, 0x0000b440U);
            WR1_PROG(REG_0094H, 0x00000030U);

            r_rsip_func101(bswap_32big(0xf2ca4ab1U), bswap_32big(0x3ef93e51U), bswap_32big(0x25c1297aU),
                           bswap_32big(0xf28ae78bU));
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000006U)
        {
            WR1_PROG(REG_0094H, 0x0000b440U);
            WR1_PROG(REG_0094H, 0x00000040U);

            r_rsip_func101(bswap_32big(0x0f14e019U), bswap_32big(0x81701c20U), bswap_32big(0xb922a6a9U),
                           bswap_32big(0x28895353U));
        }

        WR1_PROG(REG_0094H, 0x3420a820U);
        WR1_PROG(REG_0094H, 0x00000004U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        WR1_PROG(REG_0094H, 0x34202841U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00270000U);

        r_rsip_func100(bswap_32big(0x4e3bf61eU), bswap_32big(0xdb075a96U), bswap_32big(0x244900a3U),
                       bswap_32big(0x2e615c48U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0x6ffd75f0U), bswap_32big(0xaed03082U), bswap_32big(0x83d71c37U),
                           bswap_32big(0xaaa9fd7dU));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x2a91c254U), bswap_32big(0xbb2973e5U), bswap_32big(0x969fdac2U),
                           bswap_32big(0xc363c3d8U));

            WR1_PROG(REG_0094H, 0x000008c6U);

            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x0000a440U);
            WR1_PROG(REG_0094H, 0x0000000fU);
            WR1_PROG(REG_0094H, 0x00046842U);
            WR1_PROG(REG_0094H, 0x00026c42U);

            WR1_PROG(REG_009CH, 0x81010040U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &S_RAM[0]);
            S_RAM[0] = bswap_32big(S_RAM[0]);

            for (iLoop = 0U; iLoop < S_RAM[0]; )
            {
                r_rsip_func100(bswap_32big(0xe1c09621U),
                               bswap_32big(0x2b25e470U),
                               bswap_32big(0x86565725U),
                               bswap_32big(0x6d85ea43U));

                WR1_PROG(REG_0094H, 0x000008e7U);

                WR1_PROG(REG_0094H, 0x00000863U);

                WR1_PROG(REG_0094H, 0x380088c0U);
                WR1_PROG(REG_0094H, 0x00000004U);
                WR1_PROG(REG_0094H, 0x2000d060U);

                WR1_PROG(REG_0094H, 0x38008880U);
                WR1_PROG(REG_0094H, 0x00000003U);
                WR1_PROG(REG_0094H, 0x2000d060U);

                WR1_PROG(REG_0094H, 0x00007c03U);
                WR1_PROG(REG_0040H, 0x00600000U);

                if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
                {
                    WR1_PROG(REG_009CH, 0x80830007U);
                    WR1_PROG(REG_0000H, 0x0345000dU);

                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0014H, 0x000002c1U);
                    WR1_PROG(REG_00D0H, 0x08000045U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR3_ADDR(REG_002CH, &InData_MAC[iLoop]);
                    WR1_PROG(REG_0014H, 0x000000a1U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

                    r_rsip_func101(bswap_32big(0x33b99784U),
                                   bswap_32big(0x7f033d55U),
                                   bswap_32big(0x5af14d38U),
                                   bswap_32big(0x6fb85706U));
                }
                else
                {
                    WR1_PROG(REG_009CH, 0x80840007U);
                    WR1_PROG(REG_0000H, 0x03450011U);

                    WAIT_STS(REG_0004H, 30, 0);
                    WR1_PROG(REG_0040H, 0x00001800U);

                    WR1_PROG(REG_0014H, 0x000003c1U);
                    WR1_PROG(REG_00D0H, 0x08000045U);
                    WAIT_STS(REG_0014H, 31, 1);
                    WR4_ADDR(REG_002CH, &InData_MAC[iLoop]);

                    r_rsip_func101(bswap_32big(0xedbcb1a4U),
                                   bswap_32big(0x2421498eU),
                                   bswap_32big(0x6d2f87d6U),
                                   bswap_32big(0xe7da88b6U));
                }

                WR1_PROG(REG_0094H, 0x00000800U);
                for (jLoop = 0U; jLoop < 16U; jLoop++)
                {
                    WR1_PROG(REG_0094H, 0x3c0028a1U);
                    WR1_PROG(REG_0094H, 0x12003c07U);
                    WR1_PROG(REG_0094H, 0x00002ce0U);
                    WR1_PROG(REG_0094H, 0x00002ca0U);
                }

                WR1_PROG(REG_00D0H, 0x9c000005U);
                WR1_PROG(REG_0094H, 0x000008e7U);
                WR1_PROG(REG_009CH, 0x81840007U);
                WR1_PROG(REG_0000H, 0x00490011U);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);

                WR1_PROG(REG_0094H, 0x0000a4c0U);
                WR1_PROG(REG_0094H, 0x00000004U);

                r_rsip_func101(bswap_32big(0x4d6a3c37U),
                               bswap_32big(0xd78f1487U),
                               bswap_32big(0x919e88a0U),
                               bswap_32big(0x4c10a08fU));
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_0094H, 0x000008c2U);

            WR1_PROG(REG_0094H, 0x00007c06U);
            WR1_PROG(REG_0040H, 0x00602000U);

            r_rsip_func100(bswap_32big(0x0b5eaa49U), bswap_32big(0x58ee993fU), bswap_32big(0x1cc81ccdU),
                           bswap_32big(0x872b9da5U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xc51e996bU),
                               bswap_32big(0x586b7f9bU),
                               bswap_32big(0xf8e594a7U),
                               bswap_32big(0x9b348cd0U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0x7cb9840dU),
                               bswap_32big(0x5e1108b0U),
                               bswap_32big(0xe491a274U),
                               bswap_32big(0x907056ceU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
