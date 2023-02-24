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

fsp_err_t HW_SCE_Sha256HmacInitSub (const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_Cmd[], const uint32_t InData_MsgLen[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00760001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1A24H, 0x0a4500e5U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &S_RAM[16 + 0]);
    WAIT_STS(REG_1A28H, 6, 0);
    WR1_PROG(REG_143CH, 0x00000900U);

    WR1_PROG(REG_2000H, 0x00000001U);

    WR1_PROG(REG_2004H, 0x00000050U);

    WR1_PROG(REG_2008H, 0x00000013U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0xd7403fbeU, 0x1450b501U, 0x1185220cU, 0x60e0be31U);
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x384a67c9U, 0x93a38a97U, 0x1aaba0e7U, 0x9e90bdceU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x38008800U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x1ce5a9ddU, 0x110ccdb1U, 0x3c8a10e1U, 0xd0d49d65U);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x38000c00U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x5f414bd8U, 0x1a7aaf2cU, 0x3b3643bdU, 0x9880ea1aU);
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x2bd3eb66U, 0xcf901062U, 0xea16091fU, 0x0e7e8720U);
                HW_SCE_p_func043();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000001bU);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x8330600fU, 0x5eb345a4U, 0xc358baffU, 0x30bbd80cU);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010140U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x8f022ab5U, 0xfd513cc0U, 0x38e50ccdU, 0x49fa4f4aU);
                HW_SCE_p_func068();

                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0xb6e3697fU);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xc20c85f1U, 0x6c08e2b6U, 0x04158dc0U, 0x162ccec1U);
            }

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x0b07b776U, 0x799de06aU, 0xaf4578b3U, 0x043c88dbU);
            HW_SCE_p_func044();

            WR1_PROG(REG_1444H, 0x000007c2U);
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xf7009d07U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

            WR1_PROG(REG_1400H, 0x01420021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x0000b760U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00003000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xdfdb3940U, 0x6a18dd37U, 0x0f42d739U, 0x09b88f2cU);
        }
        else
        {
            WR1_PROG(REG_1600H, 0x38008800U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000001U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x012558dbU, 0x2f9d56bdU, 0x8fce8850U, 0x78c51279U);
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1444H, 0x000003c7U);
                WR1_PROG(REG_1608H, 0x80040000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[1]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[2]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[3]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00000bdeU);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000037e0U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00008fe0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00ff0000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38008be0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00020000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x1000d3c0U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000037e0U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38008fe0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x2000d3c1U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003760U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00008f60U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000037e0U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00008fe0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000000feU);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38008be0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x1000d3c2U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x38008bc0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000007U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                WR1_PROG(REG_1600H, 0x00003540U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003561U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003582U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000035a3U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x9844abd1U, 0x6b869e44U, 0x6a6ac7a2U, 0x2021f671U);
                HW_SCE_p_func059();

                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[4]);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[8]);

                WR1_PROG(REG_1400H, 0x01420021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[12]);

                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                HW_SCE_p_func101(0xb00e7028U, 0xb6a01584U, 0xb29674ccU, 0xbdb19aaeU);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_Cmd[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010280U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x00003554U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x000036a0U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x0000b6c0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x01249674U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000076U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x0a71da85U, 0x8131e6b3U, 0xb002e027U, 0xd8e8b1dcU);
                HW_SCE_p_func092();

                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

                WR1_PROG(REG_1400H, 0x01420021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                HW_SCE_p_func101(0x71fd1862U, 0xe26be3e6U, 0x4508977cU, 0xb4829f16U);
            }

            HW_SCE_p_func101(0x01d9eda1U, 0x4f1ab3cdU, 0x8f734c7fU, 0xc5272f73U);
        }

        HW_SCE_p_func100(0x207c754bU, 0x9c341ed8U, 0x5f359042U, 0x85ecf528U);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x8799e705U, 0xbe7e68faU, 0xf9d5d3a3U, 0xa32a5c37U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
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

                HW_SCE_p_func101(0x312ac86dU, 0x2b203894U, 0x320feb06U, 0x229c4e25U);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, InData_MsgLen[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, InData_MsgLen[1]);

                WR1_PROG(REG_200CH, 0x00000001U);

                HW_SCE_p_func101(0x1aac2855U, 0x37843e26U, 0x1e2e9891U, 0xc13a84f3U);
            }

            return FSP_SUCCESS;
        }
    }
}

