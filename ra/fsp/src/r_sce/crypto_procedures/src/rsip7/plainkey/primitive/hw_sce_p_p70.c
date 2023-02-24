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

fsp_err_t HW_SCE_OemKeyIndexValidationSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[])
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

    WR1_PROG(REG_1B00H, 0x00700001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    HW_SCE_p_func049(InData_Cmd);

    WR1_PROG(REG_1600H, 0x0000094aU);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x000037e4U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000027U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00040020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x000000ffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000b480U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x000000feU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000b480U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000005U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x3420a880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000028U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0x0d68e83fU, 0xb2e2696eU, 0x264d2195U, 0xfcdce7adU);
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xdfa53e99U, 0xc8d4ea09U, 0x00570085U, 0xf631213cU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x0000349fU);
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
        WR1_PROG(REG_1420H, change_endian_long(0x00000070U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xe9bc5f86U, 0x6e6f14b0U, 0xea9c5f38U, 0x6ae063fdU);
        HW_SCE_p_func043();

        WR1_PROG(REG_1600H, 0x000034e4U);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000070U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x413394fbU, 0x902f3acaU, 0xaabc9135U, 0x888c1d81U);
        HW_SCE_p_func044();

        HW_SCE_p_func100(0x1624914aU, 0xcc48fd3dU, 0xa4678fb4U, 0x125844daU);

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        HW_SCE_p_func081();

        WR1_PROG(REG_1600H, 0x00007c01U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            WR1_PROG(REG_1444H, 0x00020062U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009c06U);

            for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func209();

            HW_SCE_p_func101(0x2412a5bcU, 0x7632e858U, 0x1c4a7f40U, 0xc438f315U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
        {
            WR1_PROG(REG_1444H, 0x000023c2U);
            WR1_PROG(REG_1A2CH, 0x40000800U);
            WR1_PROG(REG_1A24H, 0xe8009007U);

            for (iLoop = 0U; iLoop < 36U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1444H, 0x00001fc2U);
            WR1_PROG(REG_1A2CH, 0x40000700U);
            WR1_PROG(REG_1A24H, 0xf7008c07U);

            for (iLoop = 36U; iLoop < 68U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func101(0x4507e9d2U, 0x2c6bb3f6U, 0x6b5d4166U, 0xc04fc143U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
        {
            WR1_PROG(REG_1444H, 0x00001fc2U);
            WR1_PROG(REG_1A2CH, 0x40000700U);
            WR1_PROG(REG_1A24H, 0xf7009c07U);

            for (iLoop = 0U; iLoop < 32U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1444H, 0x00003fc2U);
            WR1_PROG(REG_1A2CH, 0x40000f00U);
            WR1_PROG(REG_1A24H, 0xf7008c07U);

            for (iLoop = 32U; iLoop < 96U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func101(0x86bf6087U, 0x380f4308U, 0xabbe01c4U, 0xbe7f8f14U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
        {
            WR1_PROG(REG_1444H, 0x000043c2U);
            WR1_PROG(REG_1A2CH, 0x40001000U);
            WR1_PROG(REG_1A24H, 0xe8009007U);

            for (iLoop = 0U; iLoop < 68U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1444H, 0x00003fc2U);
            WR1_PROG(REG_1A2CH, 0x40000f00U);
            WR1_PROG(REG_1A24H, 0xf7008c07U);

            for (iLoop = 68U; iLoop < 132U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func101(0x806c0a7eU, 0xda9f2525U, 0x183989cdU, 0x6cc4cfd7U);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
        {
            WR1_PROG(REG_1444H, 0x00003fc2U);
            WR1_PROG(REG_1A2CH, 0x40000f00U);
            WR1_PROG(REG_1A24H, 0xf7009c07U);

            for (iLoop = 0U; iLoop < 64U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            WR1_PROG(REG_1444H, 0x00007fc2U);
            WR1_PROG(REG_1A2CH, 0x40001f00U);
            WR1_PROG(REG_1A24H, 0xf7008c07U);

            for (iLoop = 64U; iLoop < 192U; )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func101(0xa0451e9cU, 0xe8e012fbU, 0xcadc55c3U, 0xdad8a2efU);
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
        {
            WR1_PROG(REG_1444H, 0x00020062U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe8009006U);

            for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
            {
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func209();

            HW_SCE_p_func101(0x6a40712bU, 0x2ac99247U, 0x50a74dd6U, 0x8874f964U);
        }

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0x7adcd9bcU, 0x5487c2a5U, 0x97e3cd7fU, 0x5b141035U);
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xe5864acdU, 0x64829e6dU, 0x0365855eU, 0xa095d679U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0xf6ffd952U, 0x5cd8b580U, 0xf8dc2619U, 0xd4e88ddeU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}

