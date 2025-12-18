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

rsip_ret_t r_rsip_pf4 (const uint32_t InData_CurveType[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_PubKeyIndex[],
                       uint32_t       OutData_PrivKeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f40001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func_sub014(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    r_rsip_func_sub018(0x00000000U, 0x3420a800U, 0x00000003U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);

    r_rsip_func070(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x000034c0U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x00002428U);

    r_rsip_func100(bswap_32big(0x13f1b684U),
                   bswap_32big(0x365a1141U),
                   bswap_32big(0x31071003U),
                   bswap_32big(0x11f8c2c0U));
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x911498f1U),
                   bswap_32big(0x261697f3U),
                   bswap_32big(0x77492b05U),
                   bswap_32big(0xa3f907cdU));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub015(0x00c10009U, 0x00001800U);
    r_rsip_func_sub015(0x00010009U, 0x00001800U);

    r_rsip_func103();
    r_rsip_func100(bswap_32big(0xf5b03aa5U),
                   bswap_32big(0x8d48c9d0U),
                   bswap_32big(0x72d8177dU),
                   bswap_32big(0x27ba43cbU));
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub015(0x00c10011U, 0x00001800U);

    r_rsip_func103();
    r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);
    r_rsip_func_sub015(0x00c10011U, 0x00001800U);

    r_rsip_func_sub003(0x0000140fU, 0x00c0001dU, 0x00000001U);

    r_rsip_func_sub001(0x000f000aU, 0x00140000U, 0x0404000aU);

    r_rsip_func_sub003(0x0000143cU, 0x00c0001dU, 0x00000002U);

    r_rsip_func_sub009(0x00001419U, 0x00c00021U, 0x00001800U);

    r_rsip_func_sub022(0x00000821U, 0x00000863U, 0x000008a5U);

    for (iLoop = 0U; iLoop < 64U; iLoop++)
    {
        r_rsip_func_sub001(0x00140027U, 0x001e0000U, 0x0404000aU);

        WR1_PROG(REG_00B0H, 0x0000081aU);
        r_rsip_func_sub006(0x80020000U, 0x03430009U, 0x00000884U, 0x38000c21U);
        r_rsip_func_sub022(0x2000d080U, 0x38000c63U, 0x1000d081U);

        r_rsip_func_sub010(0x38008880U, 0x00000003U, 0x00270000U);

        r_rsip_func100(bswap_32big(0xce48aec5U), bswap_32big(0xd2ed005dU), bswap_32big(0xe154b08bU),
                       bswap_32big(0x9dbd275eU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func_sub001(0x0019001eU, 0x004b0000U, 0x04040009U);

            r_rsip_func101(bswap_32big(0x0cc490a1U), bswap_32big(0xa102f2c9U), bswap_32big(0x9754effdU),
                           bswap_32big(0x9099a4b6U));
        }
        else
        {
            r_rsip_func_sub001(0x0019001eU, 0x00270000U, 0x04040009U);

            r_rsip_func101(bswap_32big(0xb9ad28c4U), bswap_32big(0xc0328791U), bswap_32big(0xe799f16bU),
                           bswap_32big(0x4a9c9d32U));
        }

        r_rsip_func_sub001(0x003c002bU, 0x001e0000U, 0x04040007U);

        r_rsip_func_sub001(0x003c0027U, 0x00230000U, 0x04040007U);

        WR1_PROG(REG_00B0H, 0x0000081fU);
        r_rsip_func_sub012(0x80020040U, 0x03430009U);

        r_rsip_func_sub001(0x0019001eU, 0x002b0000U, 0x04040009U);

        r_rsip_func_sub001(0x001a0023U, 0x00270000U, 0x04040009U);

        WR1_PROG(REG_0094H, 0x00002ca0U);

        r_rsip_func101(bswap_32big(0x93fd36d8U), bswap_32big(0x43463d05U), bswap_32big(0xd0b1ff66U),
                       bswap_32big(0x4abd6b63U));
    }

    r_rsip_func_sub010(0x380088a0U, 0x00000040U, 0x00270000U);

    WR1_PROG(REG_0040H, 0x00402000U);

    r_rsip_func_sub001(0x00140027U, 0x001e0000U, 0x0404000aU);

    WR1_PROG(REG_00B0H, 0x0000081aU);
    r_rsip_func_sub006(0x80020000U, 0x03430009U, 0x00000884U, 0x38000c21U);
    r_rsip_func_sub022(0x2000d080U, 0x38000c63U, 0x1000d081U);

    r_rsip_func_sub010(0x38008880U, 0x00000003U, 0x00270000U);

    r_rsip_func100(bswap_32big(0xf98a3d95U),
                   bswap_32big(0x02565abbU),
                   bswap_32big(0xd2096571U),
                   bswap_32big(0x3b77c0d2U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func_sub001(0x0019001eU, 0x004b0000U, 0x04040009U);

        r_rsip_func101(bswap_32big(0xc6c6a805U), bswap_32big(0x12018fcaU), bswap_32big(0xbdeed2b9U),
                       bswap_32big(0x8f5e67b5U));
    }
    else
    {
        r_rsip_func_sub001(0x0019001eU, 0x00270000U, 0x04040009U);

        r_rsip_func101(bswap_32big(0x8d4ad51cU), bswap_32big(0x8df7b2caU), bswap_32big(0x0034691eU),
                       bswap_32big(0xd0add1adU));
    }

    r_rsip_func_sub001(0x000f0027U, 0x00320000U, 0x04040009U);

    WR1_PROG(REG_0094H, 0x00003406U);

    r_rsip_func071(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x000000f4U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x91795881U),
                   bswap_32big(0x926ed40aU),
                   bswap_32big(0x01b0599dU),
                   bswap_32big(0xadf7fc94U));
    r_rsip_func088();

    r_rsip_func100(bswap_32big(0x0dad361bU),
                   bswap_32big(0x15b4e378U),
                   bswap_32big(0x00533265U),
                   bswap_32big(0x702821d9U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xbaec3eadU), bswap_32big(0x9bea23a5U), bswap_32big(0x90a5f53dU),
                       bswap_32big(0x8dbbcf46U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x02e93871U), bswap_32big(0x3c4bd4a2U), bswap_32big(0xb7dce22dU),
                       bswap_32big(0xeadcd567U));
        r_rsip_func103();
        r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

        r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

        WR1_PROG(REG_0094H, 0x000034c0U);

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f401U, 0x00000000U);

        r_rsip_func101(bswap_32big(0xc8cfcd69U), bswap_32big(0x7d68ab56U), bswap_32big(0x2b5964c7U),
                       bswap_32big(0x68fb59bdU));
        r_rsip_func043();

        r_rsip_func074();

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f401U, 0x00000000U);

        r_rsip_func101(bswap_32big(0xe7d89f86U), bswap_32big(0xf0b97e6fU), bswap_32big(0xdba6b238U),
                       bswap_32big(0xbab6d12bU));
        r_rsip_func044();

        r_rsip_func100(bswap_32big(0xc57e8272U), bswap_32big(0x02ceb6abU), bswap_32big(0x815c79aaU),
                       bswap_32big(0xde1a2cfcU));
        WR1_PROG(REG_00B0H, 0x00001832U);

        r_rsip_func_sub004(0x40000100U, 0xe7009d07U, 0x00430021U, 0x00001022U);
        RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[5]);

        r_rsip_func100(bswap_32big(0x7b8719ccU), bswap_32big(0xa2494cc9U), bswap_32big(0xfc640c5fU),
                       bswap_32big(0xc20bf7b7U));
        r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

        r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
        RD4_ADDR(REG_002CH, &OutData_PrivKeyIndex[9]);

        r_rsip_func100(bswap_32big(0xd35c73a0U), bswap_32big(0x79f5402eU), bswap_32big(0xa18dce30U),
                       bswap_32big(0x1f9614c1U));
        r_rsip_func_sub017(0x81010000U, 0x00005006U);
        RD1_ADDR(REG_002CH, &OutData_PrivKeyIndex[0]);

        r_rsip_func100(bswap_32big(0x3fb5c751U), bswap_32big(0xa650eda6U), bswap_32big(0x9335614bU),
                       bswap_32big(0x34f2e99eU));
        r_rsip_func103();
        r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

        r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

        WR1_PROG(REG_0094H, 0x000034c0U);

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f402U, 0x00000000U);

        r_rsip_func101(bswap_32big(0x94033fa7U), bswap_32big(0xa51b908cU), bswap_32big(0xb2611d04U),
                       bswap_32big(0x0ed88763U));
        r_rsip_func043();

        r_rsip_func075();

        r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f402U, 0x00000000U);

        r_rsip_func101(bswap_32big(0x2cc4fa38U), bswap_32big(0xffc76be3U), bswap_32big(0x58dab1b5U),
                       bswap_32big(0xcc8ee87fU));
        r_rsip_func044();

        r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

        r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

        r_rsip_func100(bswap_32big(0x9fab42dfU), bswap_32big(0xd457b86bU), bswap_32big(0xa26d110fU),
                       bswap_32big(0xec2d9cc5U));
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xe8008107U);
        r_rsip_func_sub009(0x00001828U, 0x00430021U, 0x00001800U);

        WR1_PROG(REG_0008H, 0x00001022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[5]);

        r_rsip_func100(bswap_32big(0xeb7fcb99U), bswap_32big(0x697747eaU), bswap_32big(0xff2a1caaU),
                       bswap_32big(0x045d0981U));
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xe8008107U);
        r_rsip_func_sub009(0x0000182dU, 0x00430021U, 0x00001800U);

        WR1_PROG(REG_0008H, 0x00001022U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[9]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[13]);

        r_rsip_func100(bswap_32big(0xf2d6fff1U), bswap_32big(0xe722bc5eU), bswap_32big(0x32cc805cU),
                       bswap_32big(0x1c73ef4cU));
        r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

        r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
        RD4_ADDR(REG_002CH, &OutData_PubKeyIndex[17]);

        r_rsip_func100(bswap_32big(0x60a72b01U), bswap_32big(0x8536c151U), bswap_32big(0xde26ca14U),
                       bswap_32big(0x201e2a4bU));
        r_rsip_func_sub017(0x81010000U, 0x00005006U);
        RD1_ADDR(REG_002CH, &OutData_PubKeyIndex[0]);

        r_rsip_func102(bswap_32big(0x207522f5U), bswap_32big(0x42951c70U), bswap_32big(0x4397f554U),
                       bswap_32big(0xf657201dU));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_PASS;
    }
}
