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

fsp_err_t HW_SCE_Ecc521ScalarMultiplicationSub (const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_PubKey[],
                                                uint32_t       OutData_R[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00140001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    WR1_PROG(REG_1600H, 0x00000bdeU);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000027c7U);
    WR1_PROG(REG_1608H, 0x80a8001eU);
    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = 0U; iLoop < 40U; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_PubKey[iLoop]);
        WR1_PROG(REG_1458H, 0x00000000U);
    }

    WR1_PROG(REG_1600H, 0x00000bffU);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00000bbdU);
    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 2U; iLoop++)
    {
        for (jLoop = 0U; jLoop < 3U; jLoop++)
        {
            WR1_PROG(REG_1600H, 0x0000381eU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x38000c00U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x100053fdU);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x00002fa0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000a7c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1600H, 0x0000381eU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38008c00U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0xfffffe00U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x100053fdU);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00002fa0U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x0000b7c0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000050U);
        WR1_PROG(REG_1458H, 0x00000000U);
    }

    WR1_PROG(REG_1600H, 0x38008be0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x000000ffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0x2fdb53b5U, 0x4c4e6e45U, 0x5dfb16d9U, 0xbbdcfb5bU);
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xeefaf335U, 0x68bb8237U, 0xf1b0ce1cU, 0x984480f7U);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
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
        WR1_PROG(REG_1420H, change_endian_long(0x00000014U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x0ba227e1U, 0x37c6c9bfU, 0x658f228cU, 0x338075d9U);
        HW_SCE_p_func043();

        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000025U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000014U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xde586d4dU, 0xe221cfa1U, 0x9e3d7ab0U, 0xa1951439U);
        HW_SCE_p_func044();

        WR1_PROG(REG_1444H, 0x000013c2U);
        WR1_PROG(REG_1A2CH, 0x40000400U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);

        WR1_PROG(REG_1404H, 0x12f00000U);

        for (iLoop = 0U; iLoop < 20U; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);
            WR1_PROG(REG_1400H, 0x00c20011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0xdd3b4331U, 0x6be56c3cU, 0xd6f35230U, 0xa003e5fdU);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x10970d87U, 0x1cdc8ed2U, 0x9983d7edU, 0x3b62203dU);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0xa9a76adbU, 0xa3ffd4c1U, 0x85857600U, 0xa4f99bf4U);
            WR1_PROG(REG_1600H, 0x0000b400U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000340U);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1608H, 0x81010000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);
            OFS_ADR = S_RAM[0];

            HW_SCE_p_func100(0xb3cc917eU, 0x688d3994U, 0xa034ea15U, 0x4f5900e4U);
            HW_SCE_p_func086(OFS_ADR);

            WR1_PROG(REG_1010H, 0x00000020U);
            WR1_PROG(REG_101CH, 0x000000c0U);

            WR1_PROG(REG_1004H, 0x09090010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000070U);

            WR1_PROG(REG_1004H, 0x09090010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1600H, 0x00000bdeU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x81a8001eU);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1404H, 0x10c00000U);
            WR1_PROG(REG_1400H, 0x00c90051U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x11100000U);
            WR1_PROG(REG_1400H, 0x00c90051U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x09090002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000200U);

            WR1_PROG(REG_1004H, 0x09090002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x09090001U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000890U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x09090005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x09090002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x000008e0U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x09090005U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000200U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x09090001U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x0909000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x0909000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x990484aaU, 0xa79c9600U, 0xf79c27d7U, 0x13492c76U);
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x6d5722fdU, 0x1f20a700U, 0xe074f769U, 0x1c4cc1edU);
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_1404H, 0x10c80000U);
                WR1_PROG(REG_1400H, 0x00c00049U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000200U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_1020H, 0x00000200U);

                WR1_PROG(REG_1004H, 0x09090009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000001b0U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_1020H, 0x000001b0U);

                WR1_PROG(REG_1004H, 0x09090009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000014U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x2a30d970U, 0xd4104df7U, 0xa7ba2922U, 0x1e02e871U);
                HW_SCE_p_func091();

                HW_SCE_p_func100(0x0e2edb98U, 0xe815f177U, 0x4d827278U, 0xc3c25f58U);
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0xd0fb95ffU, 0xd9969eefU, 0x8a63179eU, 0x7da0a139U);
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func100(0xfb283ff1U, 0xc35dea02U, 0xab097e8fU, 0x30dee908U);
                    WR1_PROG(REG_1404H, 0x12500000U);
                    WR1_PROG(REG_1A2CH, 0x00000200U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830031U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002032U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[0]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[4]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[8]);

                    HW_SCE_p_func100(0x12661751U, 0xf07d1e85U, 0xa4213ef6U, 0x3a457f67U);
                    WR1_PROG(REG_1A2CH, 0x00000100U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002022U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[12]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[16]);

                    HW_SCE_p_func100(0x9448be0aU, 0x49223d04U, 0x559baed6U, 0x2e18486dU);
                    WR1_PROG(REG_1404H, 0x12a00000U);
                    WR1_PROG(REG_1A2CH, 0x00000200U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830031U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002032U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[20]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[24]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[28]);

                    HW_SCE_p_func100(0x8852687dU, 0xb1a4d26aU, 0xb572c9ddU, 0x7dbb26d2U);
                    WR1_PROG(REG_1A2CH, 0x00000100U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002022U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[32]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[36]);

                    HW_SCE_p_func102(0x80bced55U, 0xa4422b79U, 0x145cabccU, 0x1913587aU);
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}

