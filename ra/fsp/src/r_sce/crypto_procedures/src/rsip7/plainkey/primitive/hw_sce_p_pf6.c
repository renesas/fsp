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

fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSub (const uint32_t InData_CurveType[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_MsgDgst[],
                                                    const uint32_t InData_Signature[])
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

    WR1_PROG(REG_1B00H, 0x00f60001U);
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
    WR1_PROG(REG_1420H, change_endian_long(0x000000f6U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x8e154ae7U, 0x3298eb8dU, 0xe8be6798U, 0x083848b5U);
    HW_SCE_p_func043();

    HW_SCE_p_func077();

    WR1_PROG(REG_1600H, 0x000034feU);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x000000f6U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x437460f9U, 0x504ba536U, 0xb4362b46U, 0xb38716c3U);
    HW_SCE_p_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x000017c2U);
    WR1_PROG(REG_1A2CH, 0x40000500U);
    WR1_PROG(REG_1A24H, 0xe8009107U);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x80980001U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);
    WR1_PROG(REG_1400H, 0x03420031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[13]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[17]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[21]);
    WR1_PROG(REG_1400H, 0x03420031U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[25]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func100(0xc75cbf96U, 0xb8e1c2dcU, 0x1880d74bU, 0x05c32ce5U);
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xcd3c27a3U, 0xb8b2e571U, 0xe3095351U, 0xf8d78904U);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000bc7U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x808c001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        for (iLoop = 0U; iLoop < 12U; iLoop++)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_MsgDgst[iLoop]);
            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x80010360U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x000000f6U));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        HW_SCE_p_func100(0x12b341a6U, 0x34b5f214U, 0xc5996329U, 0x4871f9c7U);

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

        HW_SCE_p_func100(0x075caa26U, 0xad350f03U, 0x03b6da99U, 0x5c48631cU);
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

        WR1_PROG(REG_1404H, 0x19000000U);
        WR1_PROG(REG_1444H, 0x000017c2U);
        WR1_PROG(REG_1A2CH, 0x00000500U);
        WR1_PROG(REG_1A24H, 0x08008107U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[0]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[4]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[8]);
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x19500000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[12]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[16]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[20]);
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x11d00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0002dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x000000c0U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000160U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000930U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0606000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x27c7f36eU, 0xd8f23dbdU, 0xeb5375bfU, 0xc9ffb9f3U);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xd47493bbU, 0x90eb3bc9U, 0x0755340bU, 0x5e3a93f3U);
        }
        else
        {
            HW_SCE_p_func100(0x0be27cd5U, 0x42eea78eU, 0xd8def01aU, 0x6d155b6fU);

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0606000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);
            WR1_PROG(REG_1010H, 0x00000020U);

            WR1_PROG(REG_1004H, 0x0606000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000840U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10e00000U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x818c001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x00c90031U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000340U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000930U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x06060002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func100(0x198a94d0U, 0xfc6d5e60U, 0x1867967cU, 0x016a4be6U);
            WR1_PROG(REG_1010H, 0x00000018U);

            WR1_PROG(REG_1404H, 0x11600000U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func028(OFS_ADR);

            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x06060004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x11300000U);
            WR1_PROG(REG_1400H, 0x00c00031U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000890U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002b8U);

            WR1_PROG(REG_1004H, 0x06060009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func100(0x180b0c72U, 0x3acb0bebU, 0xf9b73a00U, 0xe7c956c9U);
            WR1_PROG(REG_1014H, 0x00000070U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002f0U);

            WR1_PROG(REG_1004H, 0x06060009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000480U);

            WR1_PROG(REG_1004H, 0x06060015U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1404H, 0x11d00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0002dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000480U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0606000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x27ae2ac8U, 0x9b102d65U, 0xd4d65f6bU, 0xc2ecd7f4U);
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xffc29c8dU, 0x2fe4bf20U, 0x73be19daU, 0x383eb419U);
            }
            else
            {
                HW_SCE_p_func100(0xfd6e5c73U, 0x857a641eU, 0xf0aba45bU, 0x75181e76U);
                WR1_PROG(REG_1404H, 0x11b00000U);
                WR1_PROG(REG_1400H, 0x00c00031U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x000001e0U);
                WR1_PROG(REG_1020H, 0x00000340U);

                WR1_PROG(REG_1004H, 0x06060009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x10e00000U);
                WR1_PROG(REG_1608H, 0x818c0001U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x00c90031U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x00000390U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000001e0U);

                WR1_PROG(REG_1004H, 0x06060002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x10e00000U);
                WR1_PROG(REG_1600H, 0x000037e1U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000a7e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000030U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x818c001fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x00c90031U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x00000390U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000218U);

                WR1_PROG(REG_1004H, 0x06060002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000340U);
                WR1_PROG(REG_101CH, 0x000002f0U);
                WR1_PROG(REG_1020H, 0x00000570U);

                WR1_PROG(REG_1004H, 0x06060015U);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1404H, 0x11d00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c0002dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000570U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_1020H, 0x000001b0U);

                WR1_PROG(REG_1004H, 0x0606000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                HW_SCE_p_func100(0xc965548eU, 0x25b8f076U, 0xe75a3112U, 0x19d25e5bU);
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x59f32118U, 0xb890f414U, 0x6bf6e250U, 0x1b9cfa71U);
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000480U);
                    WR1_PROG(REG_1018H, 0x00000570U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000250U);

                    WR1_PROG(REG_1004H, 0x06060013U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);
                    WR1_PROG(REG_143CH, 0x00000d00U);

                    WR1_PROG(REG_1404H, 0x12700000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                    WR1_PROG(REG_1400H, 0x00c0002dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000480U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_1020H, 0x000002f0U);

                    WR1_PROG(REG_1004H, 0x0606000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    HW_SCE_p_func100(0x5d58e9f2U, 0x544e6bf8U, 0xa3cf6707U, 0x5527b2d8U);
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        HW_SCE_p_func101(0xdcdea964U, 0xe2497bf3U, 0xdcf54b31U, 0xf889a735U);
                    }
                    else
                    {
                        HW_SCE_p_func100(0x8bd6311cU, 0x19ce5adeU, 0xa236db70U, 0x6d542c23U);

                        WR1_PROG(REG_1014H, 0x00000250U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x000002a0U);

                        WR1_PROG(REG_1004H, 0x06060004U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_1404H, 0x11300000U);
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000104U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                        WR1_PROG(REG_1400H, 0x00c0002dU);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x00c20005U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1400H, 0x0002000dU);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1014H, 0x00000070U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x00000110U);

                        WR1_PROG(REG_1004H, 0x0606000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_1014H, 0x000002a0U);
                        WR1_PROG(REG_1018H, 0x00000110U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x00000160U);

                        WR1_PROG(REG_1004H, 0x0606000fU);
                        WR1_PROG(REG_1408H, 0x00020000U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);
                        WR1_PROG(REG_143CH, 0x00000d00U);

                        WR1_PROG(REG_1014H, 0x000001e0U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x000002a0U);

                        WR1_PROG(REG_1004H, 0x06060002U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_1014H, 0x000002a0U);
                        WR1_PROG(REG_1018H, 0x00000930U);
                        WR1_PROG(REG_1020H, 0x000001b0U);

                        WR1_PROG(REG_1004H, 0x0606000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        WR1_PROG(REG_1014H, 0x00000930U);
                        WR1_PROG(REG_1018H, 0x000002a0U);
                        WR1_PROG(REG_1020H, 0x000001b0U);

                        WR1_PROG(REG_1004H, 0x0606000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        HW_SCE_p_func100(0xb0f16f8cU, 0xe246becdU, 0x65c78995U, 0x317d8929U);
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1600H, 0x00000800U);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            HW_SCE_p_func101(0x752d1c73U, 0xae8256c3U, 0x605cc9ddU, 0x0c80f8ecU);
                        }
                        else
                        {
                            WR1_PROG(REG_1600H, 0x0000b400U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x797935bbU);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            HW_SCE_p_func101(0xb9a81c05U, 0x89970b42U, 0x30b6d17aU, 0xc5e9bb78U);
                        }
                    }
                }
            }
        }

        WR1_PROG(REG_1600H, 0x38008800U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x797935bbU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        WR1_PROG(REG_1600H, 0x00007c1bU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x3e6f6a94U, 0x1df59ef0U, 0xd3f24b65U, 0x338a4016U);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xb8fc4686U, 0xbb5f4265U, 0xa9d02530U, 0x5bc6eb06U);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0xe175cb09U, 0xda1f11ebU, 0x37721350U, 0x421c9c01U);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}

