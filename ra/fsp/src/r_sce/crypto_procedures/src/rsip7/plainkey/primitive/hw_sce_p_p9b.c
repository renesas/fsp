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

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_PubKey[],
                                                uint32_t       OutData_R[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x009b0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010340U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_CurveType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

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
    WR1_PROG(REG_1420H, change_endian_long(0x0000009bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x56f55492U, 0x7dc9cebeU, 0x41e32218U, 0xb745bc1bU);
    HW_SCE_p_func043();

    HW_SCE_p_func076();

    WR1_PROG(REG_1600H, 0x000034feU);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000009bU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x7983bab9U, 0x37dfa862U, 0x1e789385U, 0xc4b22d2dU);
    HW_SCE_p_func044();

    WR1_PROG(REG_1444H, 0x00000bc2U);
    WR1_PROG(REG_1A2CH, 0x40000200U);
    WR1_PROG(REG_1A24H, 0xf7009d07U);

    for (iLoop = 0U; iLoop < 12U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1404H, 0x13100000U);
    WR1_PROG(REG_1400H, 0x00c20031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func100(0x4429aabfU, 0xfbb1aa79U, 0x84ab4cb0U, 0x23478b9aU);
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x60a676f4U, 0x444af909U, 0xbdaa020dU, 0xd356052eU);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x8281dce6U, 0x43e6b7d8U, 0x4957da59U, 0x5163942fU);
        WR1_PROG(REG_1600H, 0x00000bdeU);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000017c7U);
        WR1_PROG(REG_1608H, 0x8098001eU);
        WR1_PROG(REG_1458H, 0x00000000U);
        for (iLoop = 0U; iLoop < 24U; iLoop++)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_PubKey[iLoop]);
            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1600H, 0x38000f5aU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00030020U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000158U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000208U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);
        OFS_ADR = S_RAM[0];

        HW_SCE_p_func100(0x2963c4ceU, 0x1f3d2ef2U, 0xccd4a8d9U, 0x59810c83U);
        HW_SCE_p_func027(OFS_ADR);

        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x000000c0U);

        WR1_PROG(REG_1004H, 0x06060010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000070U);

        WR1_PROG(REG_1004H, 0x06060010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1600H, 0x00000bdeU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x8198001eU);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1404H, 0x10e00000U);
        WR1_PROG(REG_1400H, 0x00c90031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x11300000U);
        WR1_PROG(REG_1400H, 0x00c90031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000390U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x06060002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000390U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000200U);

        WR1_PROG(REG_1004H, 0x06060002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000110U);

        WR1_PROG(REG_1004H, 0x06060001U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000890U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000160U);

        WR1_PROG(REG_1004H, 0x06060005U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000110U);

        WR1_PROG(REG_1004H, 0x06060002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x000008e0U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000160U);

        WR1_PROG(REG_1004H, 0x06060005U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000200U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000110U);

        WR1_PROG(REG_1004H, 0x06060001U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x00000250U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000110U);
        WR1_PROG(REG_1020H, 0x00000250U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x9bcde72fU, 0x56fbe2c3U, 0x705cc74eU, 0xfc28836fU);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x3529bdd1U, 0x672059d3U, 0x797ddd1fU, 0x3ba97de4U);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1400H, 0x00c00031U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000200U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_1020H, 0x00000218U);

            WR1_PROG(REG_1004H, 0x06060009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000001b0U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_1020H, 0x000001e0U);

            WR1_PROG(REG_1004H, 0x06060009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x0000009bU));
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x3e0f5752U, 0x7274363fU, 0xedbc2f7eU, 0xedaa8358U);
            HW_SCE_p_func089();

            HW_SCE_p_func100(0x1e2d13e1U, 0xc893d908U, 0xda19b2a2U, 0x9e3f2821U);
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x76a8148dU, 0xce5b9dc9U, 0x9d56c5b0U, 0xeca4a0ddU);
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0x1b6f5168U, 0x884c2065U, 0x47e94d03U, 0xae8a2949U);
                WR1_PROG(REG_1404H, 0x12700000U);
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

                HW_SCE_p_func100(0x229e74feU, 0x5bd396b1U, 0xe1d19990U, 0xdfb3a3acU);
                WR1_PROG(REG_1404H, 0x12c00000U);
                WR1_PROG(REG_1A2CH, 0x00000200U);
                WR1_PROG(REG_1A24H, 0x08008107U);
                WR1_PROG(REG_1400H, 0x00830031U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1408H, 0x00002032U);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_R[12]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_R[16]);
                WAIT_STS(REG_1408H, 30, 1);
                RD4_ADDR(REG_1420H, &OutData_R[20]);

                HW_SCE_p_func102(0xa61a9a8fU, 0xa5f0fb01U, 0xe15d9c29U, 0x97ec30d9U);
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}

