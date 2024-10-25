/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigest_SingleOpSub (const uint32_t InData_HashType[],
                                                       const uint32_t InData_Msg[],
                                                       const uint32_t InData_MsgLen[],
                                                       uint32_t       OutData_MsgDigest[],
                                                       const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00310001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func100(0x06336df3U, 0xab85d439U, 0x54b9b3d8U, 0x24431313U);
    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00000000U);

        HW_SCE_p_func101(0x020fef1bU, 0xc3094b22U, 0x8f21d8b6U, 0xc315aea3U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x00000040U);

        HW_SCE_p_func101(0x1050e48bU, 0x7891d177U, 0xbee7818cU, 0xd2a3b53cU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x00000050U);

        HW_SCE_p_func101(0x3c3c1383U, 0x1193f2ebU, 0x1b2486cfU, 0x3a1fb9b3U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2004H, 0x00000080U);

        HW_SCE_p_func101(0x8dd46d0aU, 0xf7a290ecU, 0xdba70b9cU, 0x504b8b5dU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_2004H, 0x00000090U);

        HW_SCE_p_func101(0x954eb008U, 0x9c374813U, 0x41d2af63U, 0x3505c905U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        WR1_PROG(REG_2004H, 0x000000a0U);

        HW_SCE_p_func101(0x40cce1c6U, 0x5b34bfc1U, 0x96864887U, 0x1f2e1100U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        WR1_PROG(REG_2004H, 0x000000b0U);

        HW_SCE_p_func101(0x8ca120c8U, 0x5fb5677dU, 0x6c491f50U, 0xf1d847f2U);
    }

    if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
    {
        WR1_PROG(REG_200CH, 0x00000100U);

        HW_SCE_p_func101(0x558a93d1U, 0xbd0ed3f5U, 0x15d6bf65U, 0xa397ffd2U);
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, InData_MsgLen[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, InData_MsgLen[1]);

        HW_SCE_p_func101(0x63e91d2dU, 0x148da98dU, 0xff760573U, 0x8ee4534fU);
    }

    WR1_PROG(REG_1444H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);

        iLoop = iLoop + 16U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);

    WAIT_STS(REG_2030H, 4, 1);

    HW_SCE_p_func100(0xce486c47U, 0xdf9091e6U, 0x437c57a9U, 0xe0973527U);
    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x1000b400U);
    WR1_PROG(REG_1600H, 0x00000001U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x1000b400U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func100(0x249bdd5bU, 0x7dfcc471U, 0x54fd58daU, 0x0ef0522fU);
        WR1_PROG(REG_1408H, 0x00004016U);
        for (iLoop = 0U; iLoop < 5U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func102(0x7624d2daU, 0x8407a426U, 0x5073bc83U, 0xd5496bb0U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func100(0x5aa5ae70U, 0x1d9d1ac6U, 0xb1838b95U, 0xbaf09801U);
        WR1_PROG(REG_1408H, 0x0000401eU);
        for (iLoop = 0U; iLoop < 7U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func102(0x17a493abU, 0xe350db22U, 0x5ad51f7dU, 0x87b2bf9dU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func100(0x279cd5e5U, 0x1d598e7fU, 0x347860acU, 0x6fef98a1U);
        WR1_PROG(REG_1408H, 0x00004022U);
        for (iLoop = 0U; iLoop < 8U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func102(0x71da4feaU, 0x9ebe899cU, 0x7e60374fU, 0x7d7fdb8aU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        HW_SCE_p_func100(0x306096a0U, 0xc89a32b0U, 0xef76ae1fU, 0xfb5c3506U);
        WR1_PROG(REG_1408H, 0x00004032U);
        for (iLoop = 0U; iLoop < 12U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func102(0x68645677U, 0x94a4a7f0U, 0x3b0384c1U, 0x2025b31dU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        HW_SCE_p_func100(0x0f5a5709U, 0x0812c3bbU, 0xd764f87dU, 0x89819af6U);
        WR1_PROG(REG_1408H, 0x00004042U);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func102(0xff4a8991U, 0x6f11a3faU, 0xa5bed21fU, 0x9c52410dU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }

    return FSP_SUCCESS;
}
