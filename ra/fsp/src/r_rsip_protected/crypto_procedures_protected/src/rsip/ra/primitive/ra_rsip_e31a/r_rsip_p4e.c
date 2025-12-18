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

rsip_ret_t r_rsip_p4e (const uint32_t InData_CurveType[],
                       const uint32_t InData_PubKeyType[],
                       const uint32_t InData_PubKey[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_DomainParam[],
                       uint32_t       OutData_EncSecret[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x004e0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x00010000U);

    r_rsip_func_sub014(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    r_rsip_func_sub018(0x00000000U, 0x3420a800U, 0x00000002U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000001U);

    r_rsip_func027(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_00B8H, 0x00000007U);

    WR1_PROG(REG_00A4H, 0x06060010U);

    r_rsip_func_sub020(0x20010001U, 0x00000001U);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, InData_KeyIndex[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004e01U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xbade05a6U),
                   bswap_32big(0x543c5d02U),
                   bswap_32big(0x9ee54e58U),
                   bswap_32big(0x11ba3f18U));
    r_rsip_func043();

    r_rsip_func076();

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004e01U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xa21554adU),
                   bswap_32big(0x04724f19U),
                   bswap_32big(0x57104bfeU),
                   bswap_32big(0xb468e55eU));
    r_rsip_func044();

    r_rsip_func_sub011(0x00000bc1U, 0x40000200U, 0xf7009d07U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

    r_rsip_func_sub009(0x00009446U, 0x00c10031U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &InData_KeyIndex[13]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    r_rsip_func100(bswap_32big(0xe7dc83e7U),
                   bswap_32big(0xba25cb52U),
                   bswap_32big(0xd5c4e858U),
                   bswap_32big(0x9decf68cU));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func102(bswap_32big(0x1f3f595dU), bswap_32big(0xb39a9ca5U), bswap_32big(0x00ba165eU),
                       bswap_32big(0xb1d415f4U));
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func_sub014(0x000000c7U, 0x80010060U);
        WR1_PROG(REG_002CH, InData_PubKeyType[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func_sub016(0x38000c63U, 0x00000080U, 0x00270000U);

        r_rsip_func100(bswap_32big(0xc12e89e6U), bswap_32big(0x7c5ed210U), bswap_32big(0x16df0fe9U),
                       bswap_32big(0xd98f00acU));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0014H, 0x000017c5U);
            WR1_PROG(REG_00B0H, 0x00009415U);
            WAIT_STS(REG_0014H, 31, 1);
            WR12_ADDR(REG_002CH, &InData_PubKey[0]);

            WR1_PROG(REG_00B0H, 0x0000941cU);
            WAIT_STS(REG_0014H, 31, 1);
            WR12_ADDR(REG_002CH, &InData_PubKey[12]);

            r_rsip_func101(bswap_32big(0x2b439b82U), bswap_32big(0x66330650U), bswap_32big(0x92cb8acbU),
                           bswap_32big(0x74bf6dc3U));
        }
        else
        {
            r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
            WR1_PROG(REG_002CH, InData_PubKey[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004e02U, 0x00000000U);

            r_rsip_func101(bswap_32big(0xc9095cf6U), bswap_32big(0x81998052U), bswap_32big(0x561c18b1U),
                           bswap_32big(0x74a3107eU));
            r_rsip_func043();

            r_rsip_func077();

            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004e02U, 0x00000000U);

            r_rsip_func101(bswap_32big(0x594b9575U), bswap_32big(0xc24158bcU), bswap_32big(0x16c329e2U),
                           bswap_32big(0x857cbbacU));
            r_rsip_func044();

            r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);

            r_rsip_func_sub011(0x000017c1U, 0x40000500U, 0xe8009107U);
            WR4_ADDR(REG_002CH, &InData_PubKey[1]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[5]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[9]);

            r_rsip_func_sub009(0x00009415U, 0x00c10031U, 0x00001800U);

            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[13]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[17]);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_PubKey[21]);

            r_rsip_func_sub009(0x0000941cU, 0x00c10031U, 0x00001800U);

            r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
            WR4_ADDR(REG_002CH, &InData_PubKey[25]);

            r_rsip_func_sub013(0x9c100005U, 0x00410011U);

            r_rsip_func100(bswap_32big(0x27ccc9d9U), bswap_32big(0x1abb3c76U), bswap_32big(0xfd2ce282U),
                           bswap_32big(0xe61d2177U));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0x0adbeb65U),
                               bswap_32big(0x1e2b70a2U),
                               bswap_32big(0xecd237ddU),
                               bswap_32big(0xfc32159bU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xfd512effU),
                               bswap_32big(0x9515d50cU),
                               bswap_32big(0xdfeb504dU),
                               bswap_32big(0x003e4beeU));
            }
        }

        r_rsip_func_sub001(0x004d0015U, 0x00230007U, 0x06060002U);

        r_rsip_func_sub001(0x004d001cU, 0x002a0007U, 0x06060002U);

        r_rsip_func_sub001(0x00230023U, 0x00150007U, 0x06060002U);

        r_rsip_func_sub001(0x00850015U, 0x001c0007U, 0x06060005U);

        r_rsip_func_sub001(0x0023001cU, 0x00150007U, 0x06060002U);

        r_rsip_func_sub001(0x008c0015U, 0x001c0007U, 0x06060005U);

        r_rsip_func_sub001(0x002a002aU, 0x00150007U, 0x06060002U);

        r_rsip_func_sub001(0x001c0015U, 0x00310000U, 0x0606000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func_sub001(0x0015001cU, 0x00310000U, 0x0606000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        r_rsip_func100(bswap_32big(0x25521cecU), bswap_32big(0x52f45274U), bswap_32big(0xfed75d3dU),
                       bswap_32big(0xbbfb5d48U));
        WR1_PROG(REG_0040H, 0x00400000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            r_rsip_func102(bswap_32big(0xe25102fcU), bswap_32big(0x866328cdU), bswap_32big(0xe1c8c9f0U),
                           bswap_32big(0x14f22f85U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000004eU, 0x00000000U);

            r_rsip_func101(bswap_32big(0xf8c61bd2U), bswap_32big(0x4cdb1281U), bswap_32big(0xa91c005aU),
                           bswap_32big(0x580378ebU));
            r_rsip_func089();

            r_rsip_func100(bswap_32big(0xad2cb81cU), bswap_32big(0x67c7b1d6U), bswap_32big(0x41cf3d39U),
                           bswap_32big(0xd20b045eU));
            WR1_PROG(REG_0040H, 0x00400000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                r_rsip_func102(bswap_32big(0xa4531e35U),
                               bswap_32big(0xcc3855b1U),
                               bswap_32big(0xc2c81c61U),
                               bswap_32big(0x7bf2d44eU));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xe0d3120aU),
                               bswap_32big(0xf9bf0e64U),
                               bswap_32big(0x1015145cU),
                               bswap_32big(0x69b1c7edU));
                r_rsip_func103();

                r_rsip_func_sub008(0x000000a1U, 0x0c200104U, 0x00000000U);

                r_rsip_func_sub005(0x80010000U, 0x03410005U, 0x0001000dU);

                WR1_PROG(REG_0094H, 0x000034c0U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004e03U, 0x00000000U);

                r_rsip_func101(bswap_32big(0x6d9c3c71U),
                               bswap_32big(0x919381c7U),
                               bswap_32big(0x0f46ea3bU),
                               bswap_32big(0x1a73dd00U));
                r_rsip_func043();

                WR1_PROG(REG_0094H, 0x0000b4c0U);
                WR1_PROG(REG_0094H, 0x0165e3d8U);

                r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00004e03U, 0x00000000U);

                r_rsip_func101(bswap_32big(0x073a1a0aU),
                               bswap_32big(0x1fa0acf7U),
                               bswap_32big(0x01fa3145U),
                               bswap_32big(0x75a2d08cU));
                r_rsip_func044();

                r_rsip_func100(bswap_32big(0x04cac0e6U),
                               bswap_32big(0x08d035f7U),
                               bswap_32big(0xd5b4c498U),
                               bswap_32big(0x0e8fa1beU));
                WR1_PROG(REG_00B0H, 0x00009838U);

                r_rsip_func_sub004(0x40000200U, 0xe7009d07U, 0x00430031U, 0x00001032U);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[1]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[5]);
                WAIT_STS(REG_0008H, 30, 1);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[9]);

                r_rsip_func100(bswap_32big(0x152ec865U),
                               bswap_32big(0x56a56499U),
                               bswap_32big(0x4092aeffU),
                               bswap_32big(0xfbca4362U));
                r_rsip_func_sub008(0x000000a1U, 0x0c000104U, 0x00000000U);

                r_rsip_func_sub004(0x40000000U, 0x09108105U, 0x00410011U, 0x00001012U);
                RD4_ADDR(REG_002CH, &OutData_EncSecret[13]);

                r_rsip_func100(bswap_32big(0xce730911U),
                               bswap_32big(0xd387c461U),
                               bswap_32big(0x7d5eb719U),
                               bswap_32big(0xded8e8c4U));
                r_rsip_func_sub017(0x81010000U, 0x00005006U);
                RD1_ADDR(REG_002CH, &OutData_EncSecret[0]);

                r_rsip_func102(bswap_32big(0xb0cad132U),
                               bswap_32big(0xef580084U),
                               bswap_32big(0xdfb1542bU),
                               bswap_32big(0x66298457U));
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return RSIP_RET_PASS;
            }
        }
    }
}
