/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_pefi (const uint32_t InData_HashType[], const uint32_t InData_MsgLen[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00ef0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_2000H, 0x00000001U);

    r_rsip_func_sub010(0x000000c7U, 0x80010000U);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func_sub024(0x3000a800U, 0x00000003U, 0x00010020U, 0x0000b400U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x00000080U);

    static const uint32_t Param_pefi_func100_001[] =
    {
        BSWAP_32BIG_C(0x8e6ca25bU), BSWAP_32BIG_C(0x3c27e3c7U), BSWAP_32BIG_C(0x4e64c67bU), BSWAP_32BIG_C(0x2f1c8ad3U), 
    };
    r_rsip_func100(Param_pefi_func100_001);

    r_rsip_func_sub014(0x00007c00U, 0x00600000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00000050U);

        static const uint32_t Param_pefi_func101_001[] =
        {
            BSWAP_32BIG_C(0xb6ac4c59U), BSWAP_32BIG_C(0xbae18f67U), BSWAP_32BIG_C(0x90109e3aU), BSWAP_32BIG_C(0x6caee503U), 
        };
        r_rsip_func101(Param_pefi_func101_001);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x000000a0U);

        static const uint32_t Param_pefi_func101_002[] =
        {
            BSWAP_32BIG_C(0xc86161ebU), BSWAP_32BIG_C(0x72079603U), BSWAP_32BIG_C(0x915386d6U), BSWAP_32BIG_C(0x7d9ec47aU), 
        };
        r_rsip_func101(Param_pefi_func101_002);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x000000b0U);

        static const uint32_t Param_pefi_func101_003[] =
        {
            BSWAP_32BIG_C(0x22aa8823U), BSWAP_32BIG_C(0x92a28bcfU), BSWAP_32BIG_C(0x32c93839U), BSWAP_32BIG_C(0xaf3b9f17U), 
        };
        r_rsip_func101(Param_pefi_func101_003);
    }

    r_rsip_func_sub025(0x0000b420U, 0x00000010U, 0x00003c01U);

    if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
    {
        WR1_PROG(REG_200CH, 0x00000100U);

        static const uint32_t Param_pefi_func101_004[] =
        {
            BSWAP_32BIG_C(0x9d4ee5a3U), BSWAP_32BIG_C(0x2574e687U), BSWAP_32BIG_C(0x7eaa84f1U), BSWAP_32BIG_C(0x9bc9143eU), 
        };
        r_rsip_func101(Param_pefi_func101_004);
    }
    else
    {
        r_rsip_func_sub036(0x00000040U, InData_MsgLen[0], 0x00000040U, InData_MsgLen[1]);

        static const uint32_t Param_pefi_func101_005[] =
        {
            BSWAP_32BIG_C(0x87ecb52dU), BSWAP_32BIG_C(0x8ecb28a3U), BSWAP_32BIG_C(0x426d820aU), BSWAP_32BIG_C(0xbd5801fcU), 
        };
        r_rsip_func101(Param_pefi_func101_005);
    }

    return RSIP_RET_PASS;
}
