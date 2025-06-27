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

rsip_ret_t r_rsip_p6f (const uint32_t InData_LC[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_InstData[],
                       uint32_t       OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x006f0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func048(InData_LC);

    WR1_PROG(REG_00A0H, 0x00010000U);

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000001cU);

    WR1_PROG(REG_00B0H, 0x000008b2U);
    WR1_PROG(REG_009CH, 0x80810006U);
    WR1_PROG(REG_0000H, 0x00030005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0000H, 0x03430005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func049(InData_Cmd);

    WR1_PROG(REG_0094H, 0x00000842U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000009U);
    WR1_PROG(REG_0094H, 0x00070020U);
    WR1_PROG(REG_0094H, 0x3020a880U);
    WR1_PROG(REG_0094H, 0x00000020U);
    WR1_PROG(REG_0094H, 0x00070020U);
    WR1_PROG(REG_0094H, 0x0000b440U);
    WR1_PROG(REG_0094H, 0xFBC003A0U);
    WR1_PROG(REG_0094H, 0x00000080U);
    WR1_PROG(REG_0094H, 0x3020a880U);
    WR1_PROG(REG_0094H, 0x00000040U);
    WR1_PROG(REG_0094H, 0x00070020U);
    WR1_PROG(REG_0094H, 0x3020a880U);
    WR1_PROG(REG_0094H, 0x00000020U);
    WR1_PROG(REG_0094H, 0x00060020U);
    WR1_PROG(REG_0094H, 0x0000b440U);
    WR1_PROG(REG_0094H, 0x00000FCCU);
    WR1_PROG(REG_0094H, 0x00000080U);
    WR1_PROG(REG_0094H, 0x00000080U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0094H, 0x000034a4U);

    WR1_PROG(REG_0094H, 0x00008c80U);
    WR1_PROG(REG_0094H, 0x0000001fU);

    r_rsip_func056();

    r_rsip_func100(bswap_32big(0x14185296U),
                   bswap_32big(0xfcc091e6U),
                   bswap_32big(0xcaf5e16aU),
                   bswap_32big(0x2c3afdcaU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x9cd5d356U), bswap_32big(0x37901565U), bswap_32big(0x83aeaec0U),
                       bswap_32big(0xefa17a8cU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003485U);

        WR1_PROG(REG_0014H, 0x000001a1U);
        WR1_PROG(REG_00D0H, 0x07330c04U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x07330d04U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_009CH, 0x80010000U);
        WR1_PROG(REG_0000H, 0x03410005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0000H, 0x0001000dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000001a1U);
        WR1_PROG(REG_00D0H, 0x07330d04U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00D0H, 0x06330104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

        WR1_PROG(REG_00B0H, 0x00001404U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, S_INST2[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000006fU));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xf53d890bU), bswap_32big(0xd99b6d94U), bswap_32big(0x39386d35U),
                       bswap_32big(0x064063e8U));
        r_rsip_func143();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x000000ffU);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000006fU));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xed634e32U), bswap_32big(0x43d18475U), bswap_32big(0x94dcadc2U),
                       bswap_32big(0x57b10c95U));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0x0fbff413U), bswap_32big(0x51bdb54dU), bswap_32big(0x903947f4U),
                       bswap_32big(0x147c0ffdU));
        WR1_PROG(REG_0014H, 0x000007c1U);
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xf7009d07U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &S_INST2[0 + 1]);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &S_INST2[0 + 5]);

        WR1_PROG(REG_00D0H, 0x080000a5U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x3171f90cU), bswap_32big(0xd184244fU), bswap_32big(0xbb0fd8ccU),
                       bswap_32big(0x979e7b58U));
        WR1_PROG(REG_00D0H, 0x080000b5U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &S_INST2[0 + 9]);

        WR1_PROG(REG_00D0H, 0x8c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000006fU));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xc67d6b95U), bswap_32big(0x8e1d7f3fU), bswap_32big(0x74172653U),
                       bswap_32big(0xbf54173bU));
        r_rsip_func057(InData_IV, InData_InstData, OutData_KeyIndex);

        r_rsip_func100(bswap_32big(0x0ca2ac4eU), bswap_32big(0x5b3c715aU), bswap_32big(0xffc4f756U),
                       bswap_32big(0xd3c65c63U));
        WR1_PROG(REG_00B0H, 0x00001804U);

        WR1_PROG(REG_00D0H, 0x080000b5U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D0H, 0x08000075U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x4622d79bU), bswap_32big(0x1e527dd4U), bswap_32big(0xf19a5367U),
                       bswap_32big(0xb252a1b0U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xc5b165eaU), bswap_32big(0x28fbb9faU), bswap_32big(0xacd471e3U),
                           bswap_32big(0x3f0b2315U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x08149a85U), bswap_32big(0xeeb341b5U), bswap_32big(0x5d0a044dU),
                           bswap_32big(0x815cefb1U));
            WR1_PROG(REG_009CH, 0x81010000U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

            r_rsip_func102(bswap_32big(0xcb360b30U), bswap_32big(0x61c6dc1dU), bswap_32big(0x2fed2bf0U),
                           bswap_32big(0x5ac1bb67U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_PASS;
        }
    }
}
