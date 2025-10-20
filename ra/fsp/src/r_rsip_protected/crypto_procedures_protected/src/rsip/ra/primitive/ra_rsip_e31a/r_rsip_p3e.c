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

rsip_ret_t r_rsip_p3e (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x003e0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0xf52fa34eU),
                   bswap_32big(0x4851320fU),
                   bswap_32big(0xfa4a5371U),
                   bswap_32big(0x6ba142e3U));
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
    WR1_PROG(REG_002CH, bswap_32big(0x0000003eU));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xfebba530U),
                   bswap_32big(0x4530bb54U),
                   bswap_32big(0x730a9591U),
                   bswap_32big(0xb4dcdb94U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000002aU);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000003eU));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xf0ab4a92U),
                   bswap_32big(0x500d53fdU),
                   bswap_32big(0x35cf621eU),
                   bswap_32big(0x573e84b7U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x886dc89cU),
                   bswap_32big(0xa06132acU),
                   bswap_32big(0xdba85c47U),
                   bswap_32big(0x967451beU));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x7cd2f111U),
                   bswap_32big(0x7e19a07aU),
                   bswap_32big(0x7cb1f91fU),
                   bswap_32big(0xcce1b04fU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_009CH, 0x80840001U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    WR1_PROG(REG_009CH, 0x80840001U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x730de062U),
                   bswap_32big(0x002939ebU),
                   bswap_32big(0x7fde051bU),
                   bswap_32big(0xc61a635fU));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7009d07U);
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_009CH, 0x81880001U);
    WR1_PROG(REG_0000H, 0x00490021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[5]);

    r_rsip_func100(bswap_32big(0xf71f48e1U),
                   bswap_32big(0x6a79edd2U),
                   bswap_32big(0xcc6886adU),
                   bswap_32big(0xb4de92cfU));
    r_rsip_func103();

    r_rsip_func100(bswap_32big(0x146f4142U),
                   bswap_32big(0x9177a191U),
                   bswap_32big(0xe00de519U),
                   bswap_32big(0xf6deecfdU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_009CH, 0x80840001U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func103();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    WR1_PROG(REG_009CH, 0x80840001U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x591cf07cU),
                   bswap_32big(0xc6dafeedU),
                   bswap_32big(0x0d4a5978U),
                   bswap_32big(0x44891055U));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe7008d07U);
    WR1_PROG(REG_0094H, 0x00000821U);
    WR1_PROG(REG_009CH, 0x81880001U);
    WR1_PROG(REG_0000H, 0x00490021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[9]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[13]);

    r_rsip_func100(bswap_32big(0x46d94879U),
                   bswap_32big(0x26bd2fc9U),
                   bswap_32big(0x990b4fc1U),
                   bswap_32big(0x03e80c7fU));
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
    RD4_ADDR(REG_002CH, &OutData_KeyIndex[17]);

    r_rsip_func100(bswap_32big(0x2ac5bf13U),
                   bswap_32big(0x3a66d01fU),
                   bswap_32big(0x5c32cc92U),
                   bswap_32big(0x03daefdbU));
    WR1_PROG(REG_009CH, 0x81010000U);
    WR1_PROG(REG_0008H, 0x00005006U);
    WAIT_STS(REG_0008H, 30, 1);
    RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

    r_rsip_func102(bswap_32big(0xdb13097bU),
                   bswap_32big(0xdea3f035U),
                   bswap_32big(0x12a142f3U),
                   bswap_32big(0xe301d012U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
