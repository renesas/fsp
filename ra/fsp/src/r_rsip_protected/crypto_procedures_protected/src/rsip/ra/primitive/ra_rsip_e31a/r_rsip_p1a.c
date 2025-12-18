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

RSIP_PRV_PRIMITIVE_FUNC

rsip_ret_t r_rsip_p1a (const uint32_t InData_DomainParam[],
                       uint32_t       OutData_PubKeyIndex[],
                       uint32_t       OutData_PrivKeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x0001a001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x000014a0U);

    r_rsip_func100(bswap_32big(0x7f72aa34U),
                   bswap_32big(0x3efbae99U),
                   bswap_32big(0x21efae5dU),
                   bswap_32big(0x692e2f19U));
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xde3a1f67U),
                   bswap_32big(0xa48a6ad6U),
                   bswap_32big(0x4fc602e5U),
                   bswap_32big(0xe56880a3U));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub015(0x00c10011U, 0x00001800U);

    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub015(0x00c10011U, 0x00001800U);

    WR1_PROG(REG_00F0H, 0x00000001U);
    WR1_PROG(REG_00F4H, 0x000000b0U);

    WR1_PROG(REG_0014H, 0x00000020U);
    WR1_PROG(REG_0104H, 0x00000000U);
    WR1_PROG(REG_0014H, 0x00000020U);
    WR1_PROG(REG_0100H, 0x00000100U);

    r_rsip_func_sub009(0x000018a0U, 0x01430021U, 0x00001800U);

    WAIT_STS(REG_0118H, 4, 1);

    WR1_PROG(REG_0094H, 0x00000800U);
    r_rsip_func_sub005(0x80880000U, 0x03450021U, 0x00050021U);

    r_rsip_func_sub022(0x00003820U, 0x00008c20U, 0xf8ffffffU);
    r_rsip_func_sub022(0x00003c20U, 0x0000b400U, 0x0000001cU);

    r_rsip_func_sub022(0x00003820U, 0x00008c20U, 0xffffff3fU);
    r_rsip_func_sub022(0x00009020U, 0x00000040U, 0x00003c20U);

    r_rsip_func_sub022(0x00000800U, 0x00000821U, 0x00000842U);
    WR1_PROG(REG_0094H, 0x0000b460U);
    WR1_PROG(REG_0094H, 0x0000001fU);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        r_rsip_func_sub022(0x02003801U, 0x02003843U, 0x02003c41U);
        r_rsip_func_sub022(0x02003c03U, 0x00002c20U, 0x00003060U);
    }

    r_rsip_func401(InData_DomainParam);

    r_rsip_func406(InData_DomainParam);

    r_rsip_func_sub009(0x00001487U, 0x00c00021U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00000840U);
    r_rsip_func_sub012(0x80020000U, 0x03430009U);
    WR1_PROG(REG_00B0H, 0x000004b1U);
    r_rsip_func_sub012(0x81020000U, 0x00c90009U);

    r_rsip_func_sub003(0x00001450U, 0x00c00015U, 0x00000026U);
    r_rsip_func_sub015(0x00c00009U, 0x00001800U);

    r_rsip_func_sub009(0x00001464U, 0x00c00021U, 0x00001800U);

    r_rsip_func_sub003(0x00001469U, 0x00c00015U, 0x00000026U);
    r_rsip_func_sub015(0x00c00009U, 0x00001800U);

    r_rsip_func_sub003(0x0000146eU, 0x00c00015U, 0x00000026U);
    r_rsip_func_sub015(0x00c00009U, 0x00001800U);

    r_rsip_func_sub009(0x0000148cU, 0x00c00021U, 0x00001800U);

    r_rsip_func_sub003(0x00001491U, 0x00c00015U, 0x00000026U);
    r_rsip_func_sub015(0x00c00009U, 0x00001800U);

    r_rsip_func_sub003(0x00001496U, 0x00c00015U, 0x00000026U);
    r_rsip_func_sub015(0x00c00009U, 0x00001800U);

    r_rsip_func_sub022(0x000008c6U, 0x00000800U, 0x0000b420U);
    r_rsip_func_sub022(0x0000001fU, 0x0000b440U, 0x00000001U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000001aU, 0x00000000U);

    for (iLoop = 0U; iLoop < 256U; iLoop++)
    {
        r_rsip_func405();

        r_rsip_func403();

        r_rsip_func101(bswap_32big(0x567a8c23U), bswap_32big(0x898796f0U), bswap_32big(0xcc2a15cdU),
                       bswap_32big(0x87d028c3U));
        r_rsip_func402();

        r_rsip_func404();

        WR1_PROG(REG_0094H, 0x00002cc0U);

        r_rsip_func101(bswap_32big(0xbfedc25bU), bswap_32big(0x375f4b46U), bswap_32big(0xb0bfebdaU),
                       bswap_32big(0x363b0c19U));
    }

    r_rsip_func_sub010(0x380088c0U, 0x00000100U, 0x00270000U);

    WR1_PROG(REG_0040H, 0x00402000U);

    r_rsip_func100(bswap_32big(0xd03a1851U),
                   bswap_32big(0x90315fa9U),
                   bswap_32big(0x50f4675eU),
                   bswap_32big(0xf6f688f5U));

    r_rsip_func_sub001(0x00870064U, 0x00550000U, 0x0404000aU);

    r_rsip_func_sub001(0x00870069U, 0x005a0000U, 0x0404000aU);

    r_rsip_func_sub001(0x0087006eU, 0x005f0000U, 0x0404000aU);

    r_rsip_func_sub003(0x00001482U, 0x00c0001dU, 0x00000001U);

    r_rsip_func_sub001(0x0082005fU, 0x00230005U, 0x04040002U);

    r_rsip_func_sub003(0x0000142dU, 0x00c0001dU, 0x00000002U);

    r_rsip_func_sub001(0x002d0005U, 0x00280000U, 0x0404000aU);

    r_rsip_func_sub021(0x00280023U, 0x002d0005U, 0x04040000U);
    r_rsip_func_sub020(0x20010001U, 0x00000001U);
    WR1_PROG(REG_0040H, 0x00000d00U);

    r_rsip_func_sub001(0x002d0055U, 0x00230005U, 0x04040002U);

    r_rsip_func_sub001(0x002d005aU, 0x00280005U, 0x04040002U);

    WR1_PROG(REG_00B0H, 0x00001823U);
    WR1_PROG(REG_0094H, 0x00000821U);
    r_rsip_func_sub006(0x80880001U, 0x03430021U, 0x0000b420U, 0x0000001cU);
    WR1_PROG(REG_0094H, 0x00003841U);

    WR1_PROG(REG_0094H, 0x001f6c42U);

    WR1_PROG(REG_00B0H, 0x00001828U);
    WR1_PROG(REG_0094H, 0x00000821U);
    r_rsip_func_sub006(0x80880001U, 0x03430021U, 0x00003801U, 0x00008c00U);
    r_rsip_func_sub022(0x7fffffffU, 0x00001002U, 0x00003c01U);

    r_rsip_func_sub022(0x00000800U, 0x00000821U, 0x00000842U);
    WR1_PROG(REG_0094H, 0x0000b460U);
    WR1_PROG(REG_0094H, 0x0000001fU);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        r_rsip_func_sub022(0x02003801U, 0x02003843U, 0x02003c41U);
        r_rsip_func_sub022(0x02003c03U, 0x00002c20U, 0x00003060U);
    }

    WR1_PROG(REG_0094H, 0x00000800U);

    WR1_PROG(REG_00B0H, 0x000014a5U);
    r_rsip_func_sub012(0x81880000U, 0x00c90021U);

    r_rsip_func100(bswap_32big(0x83c5af9fU),
                   bswap_32big(0xfef15c09U),
                   bswap_32big(0x8ff99f7cU),
                   bswap_32big(0x0c7f41a7U));
    r_rsip_func103();

    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00001a01U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x3b05c4f9U),
                   bswap_32big(0xe8bd2a04U),
                   bswap_32big(0x63e0bb16U),
                   bswap_32big(0x85b88f95U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000027U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00001a01U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xc1670e3fU),
                   bswap_32big(0xfe39a497U),
                   bswap_32big(0x4cec19c2U),
                   bswap_32big(0x24151ff1U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xc3b8d78bU),
                   bswap_32big(0x9a9b0a47U),
                   bswap_32big(0x5b987aaeU),
                   bswap_32big(0x6bd7b57eU));
    WR1_PROG(REG_00B0H, 0x000018a0U);

    r_rsip_func_sub004(0x40000100U, 0xe7009d07U, 0x00430021U, 0x00001022U);
    RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[5]);

    r_rsip_func100(bswap_32big(0x19f98e1fU),
                   bswap_32big(0xb284c875U),
                   bswap_32big(0x9a86de85U),
                   bswap_32big(0x4bc4f3e7U));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[9]);

    r_rsip_func100(bswap_32big(0xf9c1349cU),
                   bswap_32big(0x2325a667U),
                   bswap_32big(0x6917b236U),
                   bswap_32big(0x6ab09828U));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_PrivKeyIndex[0]);

    r_rsip_func100(bswap_32big(0x6e654757U),
                   bswap_32big(0x3eeedb19U),
                   bswap_32big(0xc1fe89c3U),
                   bswap_32big(0x0ea3b7f7U));
    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

    r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

    WR1_PROG(REG_0094H, 0x000034c0U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00001a02U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xfb4b0256U),
                   bswap_32big(0xc09dbc32U),
                   bswap_32big(0xe2598b02U),
                   bswap_32big(0x7d30f05dU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000026U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00001a02U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xed2225baU),
                   bswap_32big(0x924c7e98U),
                   bswap_32big(0xf6837d5aU),
                   bswap_32big(0xfbac3f7bU));
    r_rsip_func044();

    r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

    r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

    r_rsip_func100(bswap_32big(0x68249370U),
                   bswap_32big(0xe955ac24U),
                   bswap_32big(0x6f6ad3eaU),
                   bswap_32big(0xffc032faU));
    WR1_PROG(REG_00D4H, 0x40000100U);
    WR1_PROG(REG_00D0H, 0xe8008107U);
    r_rsip_func_sub009(0x000018a5U, 0x00430021U, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[1]);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[5]);

    r_rsip_func100(bswap_32big(0x1f4f3833U),
                   bswap_32big(0x58992e73U),
                   bswap_32big(0x116c1a2bU),
                   bswap_32big(0xdc12a38fU));
    r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
    RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[9]);

    r_rsip_func100(bswap_32big(0x65416297U),
                   bswap_32big(0x9aac5868U),
                   bswap_32big(0x75c85bd4U),
                   bswap_32big(0x16e8886eU));
    r_rsip_func_sub017(0x81010000U, 0x00005006U);
    RD1_ADDR(REG_002CH, &OutData_PubKeyIndex[0]);

    r_rsip_func102(bswap_32big(0xe3659444U),
                   bswap_32big(0xedaf0d68U),
                   bswap_32big(0x173c9684U),
                   bswap_32big(0x9f9c40beU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
