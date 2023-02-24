/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_IntegrityCheckSub(const uint32_t InData_Data[],
                      const uint32_t InData_DataLen[],
                      const uint32_t InData_MAC[],
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

    WR1_PROG(REG_1B00H, 0x00260001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_2004H, 0x00000050U);

    WR1_PROG(REG_2008H, 0x00000013U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x01522594U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000026U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x85aa7c53U, 0x6a60994eU, 0xc863ce5aU, 0x7e94b22eU);
    HW_SCE_p_func082();

    if ((InData_DataLen[0] == 0) && (InData_DataLen[1] == 0))
    {
        WR1_PROG(REG_1444H, 0x00000020U);
        WR1_PROG(REG_2014H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x00000020U);
        WR1_PROG(REG_2010H, 0x00000080U);

        WR1_PROG(REG_200CH, 0x00000001U);

        WAIT_STS(REG_2030H, 8, 0);

        WR1_PROG(REG_1444H, 0x00000020U);
        WR1_PROG(REG_2014H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x00000020U);
        WR1_PROG(REG_2010H, 0x00000000U);

        WR1_PROG(REG_200CH, 0x00000100U);

        HW_SCE_p_func101(0xd65948e6U, 0x872fd9d3U, 0x078314b5U, 0x0b50f513U);
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2014H, InData_DataLen[0]);
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2010H, InData_DataLen[1]);

        WR1_PROG(REG_200CH, 0x00000001U);

        HW_SCE_p_func101(0x0c365d2aU, 0x60a4403fU, 0x3d6f75faU, 0x2ce996c1U);
    }

    WAIT_STS(REG_2030H, 0, 1);

    WR1_PROG(REG_1444H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U);)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Data[iLoop]);
        WR4_ADDR(REG_1420H, &InData_Data[iLoop+4]);
        WR4_ADDR(REG_1420H, &InData_Data[iLoop+8]);
        WR4_ADDR(REG_1420H, &InData_Data[iLoop+12]);
        
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Data[iLoop]);
    }

    WR1_PROG(REG_1444H, 0x00000000U);

    WAIT_STS(REG_2030H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001600U);
    WAIT_STS(REG_2030H, 4, 1);

    WR1_PROG(REG_1A24H, 0x08000045U);
    WR1_PROG(REG_1400H, 0x00850011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A24H, 0x9c000005U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_MAC[0]);

    WR1_PROG(REG_1A24H, 0x08000055U);
    WR1_PROG(REG_1400H, 0x00850011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A24H, 0x9c100005U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_MAC[4]);

    HW_SCE_p_func100(0x8ccb1c59U, 0x090c8c4fU, 0xb730060bU, 0xb825c7bfU);
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xb212867cU, 0x7f962a54U, 0xb4550c73U, 0x57d07809U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func102(0x355c0de4U, 0x47c65d12U, 0x4525524fU, 0x7e29e30fU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
}

