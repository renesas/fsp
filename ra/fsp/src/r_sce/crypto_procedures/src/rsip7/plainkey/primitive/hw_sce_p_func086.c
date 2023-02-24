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

void HW_SCE_p_func086 (uint32_t ARG1)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1A24H, 0x4a070044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1A24H, 0x0e0704c4U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0123ba68U));
    WAIT_STS(REG_1A28H, 6, 0);
    WR1_PROG(REG_143CH, 0x00000900U);

    WR1_PROG(REG_1444H, 0x000077c2U);
    WR1_PROG(REG_1A2CH, 0x00001d00U);
    WR1_PROG(REG_1A24H, 0xf7049d07U);

    WR1_PROG(REG_1404H, 0x10200000U);
    for (iLoop = ARG1 + 44U; iLoop < ARG1 + 64U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &S_FLASH2[iLoop]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1404H, 0x13400000U);
    for (iLoop = ARG1 + 64U; iLoop < ARG1 + 84U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &S_FLASH2[iLoop]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1404H, 0x18400000U);
    for (iLoop = ARG1 + 84U; iLoop < ARG1 + 104U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &S_FLASH2[iLoop]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1404H, 0x18900000U);
    for (iLoop = ARG1 + 104U; iLoop < ARG1 + 124U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &S_FLASH2[iLoop]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1404H, 0x10700000U);
    for (iLoop = ARG1 + 124U; iLoop < ARG1 + 144U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &S_FLASH2[iLoop]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1404H, 0x17f00000U);
    for (iLoop = ARG1 + 144U; iLoop < ARG1 + 164U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &S_FLASH2[iLoop]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1A24H, 0x07040d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_FLASH2[iLoop]);

    WR1_PROG(REG_1A24H, 0x8c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
}

