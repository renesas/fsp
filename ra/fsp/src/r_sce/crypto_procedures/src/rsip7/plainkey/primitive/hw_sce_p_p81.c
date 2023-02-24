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

fsp_err_t HW_SCE_SelfCheck1Sub (void)
{
    WR1_PROG(REG_1D04H, 0x00043cb3U);
    WR1_PROG(REG_1D08H, 0x000d5151U);

    WR1_PROG(REG_1D00H, 0x00000001U);

    WAIT_STS(REG_1D00H, 1, 0);

    if (RD1_MASK(REG_1D00H, 0x00030000U) != 0x00000000U)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_140CH, 0x38c60eedU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1448H, 0x00000000U);

        WR1_PROG(REG_1408H, 0x00000001U);
        WR1_PROG(REG_1414H, 0x00001601U);

        if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
        {
            return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
        }
        else
        {
            ;
        }

        WR1_PROG(REG_1800H, 0x00000001U);
        WR1_PROG(REG_1700H, 0x00000001U);

        WR1_PROG(REG_1B00H, 0x00818001U);
        WR1_PROG(REG_1B08H, 0x00000d00U);

        WR1_PROG(REG_1804H, 0x00008002U);

        WR1_PROG(REG_1444H, 0x000003a2U);
        HW_SCE_p_func101(change_endian_long(0x761c3212U), change_endian_long(0x5929b561U), change_endian_long(0x41d63d71U), change_endian_long(0xc203e20eU));
        WR1_PROG(REG_1804H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x0a0700f5U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, 0xb45a1978U, 0x5a5a637bU, 0xe29d7bddU, 0x6d004e9bU);
        WAIT_STS(REG_1A28H, 6, 0);
        WR1_PROG(REG_143CH, 0x00000900U);

        HW_SCE_p_func101(change_endian_long(0xf9e62180U), change_endian_long(0x81a998d0U), change_endian_long(0x19561115U), change_endian_long(0x985f70c1U));

        HW_SCE_p_func100(change_endian_long(0x0c85360bU), change_endian_long(0x8794147aU), change_endian_long(0x9fe177e4U), change_endian_long(0x38d62ae4U));

        WR1_PROG(REG_1408H, 0x00020000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        if (CHCK_STS(REG_142CH, 13, 0))
        {
            WR1_PROG(REG_14BCH, 0x00000020U);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1430H, 0x0000FFFFU);

            WR1_PROG(REG_1B08H, 0x00000220U);

            HW_SCE_p_func102(change_endian_long(0x3ef67e43U), change_endian_long(0xbf82d536U), change_endian_long(0x648d23c9U), change_endian_long(0xabad7ea7U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}

