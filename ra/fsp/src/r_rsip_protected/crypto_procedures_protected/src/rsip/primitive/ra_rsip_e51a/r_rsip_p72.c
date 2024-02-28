/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_p72 (const uint32_t InData_HashType[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_Msg[],
                       const uint32_t InData_MsgLen[],
                       const uint32_t InData_State[],
                       uint32_t       OutData_MsgDigest[],
                       uint32_t       OutData_State[],
                       uint32_t       MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00720001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x9c7d57acU), bswap_32big(0xbeaca82cU), bswap_32big(0x1ed3bda7U), bswap_32big(0x9c158296U));
    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000001c7U);
    WR1_PROG(REG_1608H, 0x80020000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000006U);

    WR1_PROG(REG_1600H, 0x3420a820U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x2000b420U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x000037e1U);
    WR1_PROG(REG_1600H, 0x00008fe0U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1600H, 0x00046fffU);

    WR1_PROG(REG_1600H, 0x000013e0U);

    WR1_PROG(REG_1600H, 0x00007c1fU);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2004H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xa9ba84c2U), bswap_32big(0x726aebd1U), bswap_32big(0x17713092U), bswap_32big(0x5399ff62U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000020U)
    {
        WR1_PROG(REG_2004H, 0x00001000U);

        r_rsip_func101(bswap_32big(0x2dba89daU), bswap_32big(0x55835517U), bswap_32big(0x8ac417eeU), bswap_32big(0x1113c758U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2004H, 0x00000040U);

        r_rsip_func101(bswap_32big(0xb8288ecbU), bswap_32big(0x616da1b0U), bswap_32big(0x4d78c61bU), bswap_32big(0xeaed7b7cU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000021U)
    {
        WR1_PROG(REG_2004H, 0x00001040U);

        r_rsip_func101(bswap_32big(0x7ea05301U), bswap_32big(0x0644c4d7U), bswap_32big(0xb80da9abU), bswap_32big(0xa3ce0fcfU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2004H, 0x00000050U);

        r_rsip_func101(bswap_32big(0xf8ee8793U), bswap_32big(0x30a900ddU), bswap_32big(0xa41cb008U), bswap_32big(0xa112043aU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000022U)
    {
        WR1_PROG(REG_2004H, 0x00001050U);

        r_rsip_func101(bswap_32big(0xa1612261U), bswap_32big(0x7bc298f2U), bswap_32big(0x88cf1842U), bswap_32big(0xf7ff5ed7U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2004H, 0x00000080U);

        r_rsip_func101(bswap_32big(0x49f1bd01U), bswap_32big(0x208c73cbU), bswap_32big(0x41a4334eU), bswap_32big(0x5b2c8152U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000023U)
    {
        WR1_PROG(REG_2004H, 0x00001080U);

        r_rsip_func101(bswap_32big(0x080020a0U), bswap_32big(0xd6317bbaU), bswap_32big(0x1692e712U), bswap_32big(0x683fa089U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_2004H, 0x00000090U);

        r_rsip_func101(bswap_32big(0xb88e7b35U), bswap_32big(0x51bf2974U), bswap_32big(0x30e07cbaU), bswap_32big(0x99136c0eU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000024U)
    {
        WR1_PROG(REG_2004H, 0x00001090U);

        r_rsip_func101(bswap_32big(0x0e03211dU), bswap_32big(0x567ac0b4U), bswap_32big(0x944cc54cU), bswap_32big(0xbcda2403U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        WR1_PROG(REG_2004H, 0x000000a0U);

        r_rsip_func101(bswap_32big(0x5d70f497U), bswap_32big(0x989f2d80U), bswap_32big(0xc35fa8ebU), bswap_32big(0xca6496d3U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000025U)
    {
        WR1_PROG(REG_2004H, 0x000010a0U);

        r_rsip_func101(bswap_32big(0x7004d3b1U), bswap_32big(0x47bb832bU), bswap_32big(0x69b07a26U), bswap_32big(0x67477513U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        WR1_PROG(REG_2004H, 0x000000b0U);

        r_rsip_func101(bswap_32big(0x494bd172U), bswap_32big(0x004530f0U), bswap_32big(0xda7913ceU), bswap_32big(0x9143c668U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000026U)
    {
        WR1_PROG(REG_2004H, 0x000010b0U);

        r_rsip_func101(bswap_32big(0xf4a051abU), bswap_32big(0x524ba351U), bswap_32big(0x08143ec2U), bswap_32big(0x8f7fa5a7U));
    }

    WR1_PROG(REG_1600H, 0x38008c20U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0xdfaf1cfdU), bswap_32big(0x9869e0cbU), bswap_32big(0xa569168bU), bswap_32big(0xd57a78c8U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
        {
            WR1_PROG(REG_200CH, 0x00000100U);

            r_rsip_func101(bswap_32big(0x89919595U), bswap_32big(0x3de2459dU), bswap_32big(0xcf5b8127U), bswap_32big(0xe411f0f8U));
        }
        else
        {
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, InData_MsgLen[0]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, InData_MsgLen[1]);

            r_rsip_func101(bswap_32big(0xd7e31e84U), bswap_32big(0x9e7f306dU), bswap_32big(0xe7ffdc84U), bswap_32big(0x1a9e1b34U));
        }
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, InData_State[18]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, InData_State[19]);

        for (iLoop = 0U; iLoop < 18U; iLoop++)
        {
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2028H, InData_State[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func101(bswap_32big(0xa13b88e9U), bswap_32big(0x39c55df6U), bswap_32big(0x8ce8ebfdU), bswap_32big(0xcef4c7a0U));
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

    WR1_PROG(REG_1600H, 0x38008820U);
    WR1_PROG(REG_1600H, 0x00000001U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x38008820U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0xb976fc9eU), bswap_32big(0x59d68416U), bswap_32big(0x60c329f3U), bswap_32big(0xdcfadda5U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WAIT_STS(REG_2030H, 8, 0);
        for (iLoop = 0U; iLoop < 18U; iLoop++)
        {
            RD1_ADDR(REG_202CH, &OutData_State[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        RD1_ADDR(REG_2014H, &OutData_State[18]);
        RD1_ADDR(REG_2010H, &OutData_State[19]);

        r_rsip_func102(bswap_32big(0x9dbedc0fU), bswap_32big(0xd371c17cU), bswap_32big(0x609681e2U), bswap_32big(0x443ae86aU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else
    {
        WAIT_STS(REG_2030H, 4, 1);

        r_rsip_func100(bswap_32big(0xbf38f3fcU), bswap_32big(0x0453199eU), bswap_32big(0x46e9af40U), bswap_32big(0x39e84223U));
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
            r_rsip_func100(bswap_32big(0xdfd99981U), bswap_32big(0xd4a308d7U), bswap_32big(0x328e83b5U), bswap_32big(0x6331a945U));
            WR1_PROG(REG_1408H, 0x00004016U);
            for (iLoop = 0U; iLoop < 5U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func102(bswap_32big(0x02f230c0U), bswap_32big(0x7e3d0402U), bswap_32big(0x7cf07aa7U), bswap_32big(0x0d7cd872U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            r_rsip_func100(bswap_32big(0x9f247c53U), bswap_32big(0x21f860a7U), bswap_32big(0x9e5bccf7U), bswap_32big(0x5f5ba292U));
            WR1_PROG(REG_1408H, 0x0000401eU);
            for (iLoop = 0U; iLoop < 7U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func102(bswap_32big(0x026ed8ebU), bswap_32big(0x7e3fa35eU), bswap_32big(0x4bd92ca8U), bswap_32big(0x6a1114acU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            r_rsip_func100(bswap_32big(0xfaaaffb1U), bswap_32big(0x87c613f3U), bswap_32big(0xf021065aU), bswap_32big(0x2923a7e6U));
            WR1_PROG(REG_1408H, 0x00004022U);
            for (iLoop = 0U; iLoop < 8U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func102(bswap_32big(0x6938f984U), bswap_32big(0x8cdbb61aU), bswap_32big(0x55ed2f1aU), bswap_32big(0xa123726aU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
        {
            r_rsip_func100(bswap_32big(0x2e7de48fU), bswap_32big(0x16d7f06bU), bswap_32big(0x1e5549beU), bswap_32big(0xbe20d002U));
            WR1_PROG(REG_1408H, 0x00004032U);
            for (iLoop = 0U; iLoop < 12U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func102(bswap_32big(0x96e45d57U), bswap_32big(0x4710eb89U), bswap_32big(0x661e8bc1U), bswap_32big(0x6069da36U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
        {
            r_rsip_func100(bswap_32big(0x010601baU), bswap_32big(0x9fd9defeU), bswap_32big(0xf5c220f4U), bswap_32big(0x04bc24b8U));
            WR1_PROG(REG_1408H, 0x00004042U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MsgDigest[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            r_rsip_func102(bswap_32big(0x1d244f62U), bswap_32big(0x5e06ae9fU), bswap_32big(0xef50dcd9U), bswap_32big(0xd231116bU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);
        }
    }

    return RSIP_RET_PASS;
}
