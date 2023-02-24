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

fsp_err_t HW_SCE_EcdsaP512SignatureVerificationSub (const uint32_t InData_KeyIndex[],
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

    WR1_PROG(REG_1B00H, 0x007e0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

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
    WR1_PROG(REG_1420H, change_endian_long(0x0000007eU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xb746c054U, 0xe581f3acU, 0x80c1a421U, 0x871de6b8U);
    HW_SCE_p_func043();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000020U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x0000007eU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xf03b4119U, 0xde1eb383U, 0xc8d68218U, 0x7bc5d1deU);
    HW_SCE_p_func044();

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x00001fc2U);
    WR1_PROG(REG_1A2CH, 0x40000700U);
    WR1_PROG(REG_1A24H, 0xe8009107U);

    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x80a00001U);
    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = 0U; iLoop < 16U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    for (iLoop = 0U; iLoop < 16U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 17]);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[33]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func100(0x5ee36677U, 0xbafd2fffU, 0xf81821dfU, 0xfeadc77aU);
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xe54ea67dU, 0x411d826dU, 0x3761d5bfU, 0xafae9898U);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x00000fc7U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x8090001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_MsgDgst[iLoop]);
            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x80010360U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x0000007eU));
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1000H, 0x00010000U);
        WR1_PROG(REG_1024H, 0x000007f0U);

        HW_SCE_p_func100(0xbe2c9489U, 0x2b85cd29U, 0xa4ef8160U, 0x3cbfda71U);

        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000270U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);
        OFS_ADR = S_RAM[0];

        HW_SCE_p_func100(0x37acd9c8U, 0x59a8c6a0U, 0xa423f788U, 0x9e45fca7U);
        HW_SCE_p_func078(OFS_ADR);

        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x000000c0U);

        WR1_PROG(REG_1004H, 0x08080010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000070U);

        WR1_PROG(REG_1004H, 0x08080010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x18f00000U);
        WR1_PROG(REG_1444H, 0x00001fc2U);
        WR1_PROG(REG_1A2CH, 0x00000700U);
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
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[12]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x19400000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[16]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[20]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[24]);
        WR1_PROG(REG_1400H, 0x00c20031U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Signature[28]);
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x11c00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0003dU);
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

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000930U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);

        WR1_PROG(REG_1004H, 0x0808000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_143CH, 0x00210000U);

        HW_SCE_p_func100(0x7812bcb7U, 0x9e5ed5efU, 0xf01fb28bU, 0x87ab5a74U);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0xce0d89a5U, 0xab773285U, 0x80501a1cU, 0x0bd8f0c1U);
        }
        else
        {
            HW_SCE_p_func100(0xbd5bb4b6U, 0x279b7d74U, 0x6f881cefU, 0x311d3d86U);

            WR1_PROG(REG_1014H, 0x00000160U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000001b0U);

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_1018H, 0x000001b0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);
            WR1_PROG(REG_1010H, 0x00000020U);

            WR1_PROG(REG_1004H, 0x0808000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000840U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000160U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10d00000U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x8190001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x00c90041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000340U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000930U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x00000110U);

            WR1_PROG(REG_1004H, 0x08080002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func100(0x4045b29bU, 0x58a72eb3U, 0x2a8882dcU, 0xf2b9facbU);
            WR1_PROG(REG_1010H, 0x00000018U);

            WR1_PROG(REG_1404H, 0x11600000U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func079(OFS_ADR);

            WR1_PROG(REG_1014H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);

            WR1_PROG(REG_1004H, 0x08080004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x11200000U);
            WR1_PROG(REG_1400H, 0x00c00041U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x00000890U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002a8U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            HW_SCE_p_func100(0x6c340799U, 0x3b1bd78dU, 0x3544a977U, 0x04a55c4fU);
            WR1_PROG(REG_1014H, 0x00000070U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x000002f0U);

            WR1_PROG(REG_1004H, 0x08080009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000480U);

            WR1_PROG(REG_1004H, 0x08080015U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);
            WR1_PROG(REG_143CH, 0x00000d00U);

            WR1_PROG(REG_1404H, 0x11c00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0003dU);
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

            WR1_PROG(REG_1004H, 0x0808000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x70f1f88bU, 0x9435b402U, 0x6fe7d1c2U, 0x9eaeeecaU);
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x941d2338U, 0xf58e9855U, 0x24f12d7bU, 0x281a64d7U);
            }
            else
            {
                HW_SCE_p_func100(0x4042e5dcU, 0x0bb511fcU, 0x475323a2U, 0xcc262939U);
                WR1_PROG(REG_1404H, 0x11800000U);
                WR1_PROG(REG_1400H, 0x00c00041U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x000001c0U);
                WR1_PROG(REG_1020H, 0x00000340U);

                WR1_PROG(REG_1004H, 0x08080009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x10d00000U);
                WR1_PROG(REG_1608H, 0x81900001U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x00c90041U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x00000390U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000001c0U);

                WR1_PROG(REG_1004H, 0x08080002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1404H, 0x10d00000U);
                WR1_PROG(REG_1600H, 0x000037e1U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000a7e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000040U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x8190001fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x00c90041U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x00000390U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000208U);

                WR1_PROG(REG_1004H, 0x08080002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000340U);
                WR1_PROG(REG_101CH, 0x000002f0U);
                WR1_PROG(REG_1020H, 0x00000570U);

                WR1_PROG(REG_1004H, 0x08080015U);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1404H, 0x11c00000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                WR1_PROG(REG_1400H, 0x00c0003dU);
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

                WR1_PROG(REG_1004H, 0x0808000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_143CH, 0x00210000U);

                HW_SCE_p_func100(0x0d6720c9U, 0xee48d2c2U, 0xd47c00b0U, 0xa00387b6U);
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    HW_SCE_p_func101(0x185fdc7aU, 0xd5d55621U, 0x038820edU, 0x27a8f3dcU);
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000480U);
                    WR1_PROG(REG_1018H, 0x00000570U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000250U);

                    WR1_PROG(REG_1004H, 0x08080013U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);
                    WR1_PROG(REG_143CH, 0x00000d00U);

                    WR1_PROG(REG_1404H, 0x12600000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                    WR1_PROG(REG_1400H, 0x00c0003dU);
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

                    WR1_PROG(REG_1004H, 0x0808000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    HW_SCE_p_func100(0xbc6fc267U, 0xc3c2904eU, 0xf242c321U, 0x3c0c1ebdU);
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        HW_SCE_p_func101(0xd115d0f6U, 0x53f07113U, 0xb18d748bU, 0xff1e8f53U);
                    }
                    else
                    {
                        HW_SCE_p_func100(0xe6dd9046U, 0x154253e1U, 0xddc760b4U, 0x371c6320U);

                        WR1_PROG(REG_1014H, 0x00000250U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x000002a0U);

                        WR1_PROG(REG_1004H, 0x08080004U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_1404H, 0x11200000U);
                        WR1_PROG(REG_1444H, 0x000000a2U);
                        WR1_PROG(REG_1A24H, 0x08000104U);
                        WAIT_STS(REG_1444H, 31, 1);
                        WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                        WR1_PROG(REG_1400H, 0x00c0003dU);
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

                        WR1_PROG(REG_1004H, 0x0808000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_1014H, 0x000002a0U);
                        WR1_PROG(REG_1018H, 0x00000110U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x00000160U);

                        WR1_PROG(REG_1004H, 0x0808000fU);
                        WR1_PROG(REG_1408H, 0x00020000U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);
                        WR1_PROG(REG_143CH, 0x00000d00U);

                        WR1_PROG(REG_1014H, 0x000001c0U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x000002a0U);

                        WR1_PROG(REG_1004H, 0x08080002U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_1014H, 0x000002a0U);
                        WR1_PROG(REG_1018H, 0x00000930U);
                        WR1_PROG(REG_1020H, 0x000001b0U);

                        WR1_PROG(REG_1004H, 0x0808000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        WR1_PROG(REG_1014H, 0x00000930U);
                        WR1_PROG(REG_1018H, 0x000002a0U);
                        WR1_PROG(REG_1020H, 0x000001b0U);

                        WR1_PROG(REG_1004H, 0x0808000aU);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0, 0);

                        WR1_PROG(REG_143CH, 0x00210000U);

                        HW_SCE_p_func100(0xa64ca8c0U, 0x28b252ebU, 0x69f5ff56U, 0x4fb9398dU);
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);

                        if (CHCK_STS(REG_143CH, 22, 1))
                        {
                            WR1_PROG(REG_1600H, 0x00000800U);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            HW_SCE_p_func101(0x60f3dbe4U, 0x957ca780U, 0x4aee27e4U, 0xc5f43059U);
                        }
                        else
                        {
                            WR1_PROG(REG_1600H, 0x0000b400U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x797935bbU);
                            WR1_PROG(REG_1458H, 0x00000000U);

                            HW_SCE_p_func101(0x1c1f8dbbU, 0x87d0e4bbU, 0x6629f3b7U, 0xda35538cU);
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

        HW_SCE_p_func100(0xfb795218U, 0x81152a78U, 0x54cdacc0U, 0x6715d108U);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xee6a4ca7U, 0x5e354fe3U, 0x477f2504U, 0x71c39cffU);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0xf8007f76U, 0xdce4555dU, 0x87229698U, 0x7f2632adU);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}

