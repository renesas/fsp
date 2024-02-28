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

rsip_ret_t r_rsip_p82 (void)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00820001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0b070194U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x01c7ba56U));
    WAIT_STS(REG_1A28H, 6, 0);
    WR1_PROG(REG_143CH, 0x00000900U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000074U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1600H, 0x3000a820U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WAIT_STS(REG_1708H, 0, 0);
    WAIT_STS(REG_1708H, 0, 0);
    WR1_PROG(REG_1704H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x00000863U);

    WR1_PROG(REG_1600H, 0x00000884U);

    WR1_PROG(REG_1600H, 0x000008a5U);

    WR1_PROG(REG_1600H, 0x0000b4c0U);
    WR1_PROG(REG_1600H, 0x00000013U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000348U);

    WR1_PROG(REG_1600H, 0x0000b500U);
    WR1_PROG(REG_1600H, 0x000000b7U);

    for (jLoop = 0U; jLoop < 1U; jLoop++)
    {
        r_rsip_func100(bswap_32big(0x7f9c1a0bU), bswap_32big(0x445defb0U), bswap_32big(0x70975a0fU), bswap_32big(0xface3941U));
        WR1_PROG(REG_1600H, 0x00007c01U);
        WR1_PROG(REG_143CH, 0x00600000U);

        if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
        {
            WAIT_STS(REG_1708H, 0, 0);
            WAIT_STS(REG_1708H, 0, 0);
            WR1_PROG(REG_1704H, 0x00200007U);

            r_rsip_func101(bswap_32big(0x01088ddcU), bswap_32big(0x6ec2a400U), bswap_32big(0x4b117bb8U), bswap_32big(0x8ee47b43U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
        {
            WAIT_STS(REG_1708H, 0, 0);
            WAIT_STS(REG_1708H, 0, 0);
            WR1_PROG(REG_1704H, 0x00200005U);

            r_rsip_func101(bswap_32big(0x530c6897U), bswap_32big(0xfef16c5aU), bswap_32big(0x502a091dU), bswap_32big(0xb93fd515U));
        }
        else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
        {
            WAIT_STS(REG_1708H, 0, 0);
            WAIT_STS(REG_1708H, 0, 0);
            WR1_PROG(REG_1704H, 0x00200006U);

            r_rsip_func101(bswap_32big(0xccaf6c06U), bswap_32big(0x15ab0cbeU), bswap_32big(0x32c98f9dU), bswap_32big(0x2358b972U));
        }

        WR1_PROG(REG_1A2CH, 0x00000700U);
        WR1_PROG(REG_1A24H, 0x0e3d8407U);
        WR1_PROG(REG_1400H, 0x00840081U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_1708H, 2, 1);
        WR1_PROG(REG_143CH, 0x00001200U);

        WAIT_STS(REG_1A28H, 6, 0);
        WR1_PROG(REG_143CH, 0x00000a00U);
        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1608H, 0x808a0000U);
        WR1_PROG(REG_1400H, 0x03440029U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x000038a0U);
        WR1_PROG(REG_1600H, 0x00003405U);
        WR1_PROG(REG_1600H, 0x00002804U);

        WR1_PROG(REG_1600H, 0x342028e0U);
        WR1_PROG(REG_1600H, 0x10005066U);

        WR1_PROG(REG_1600H, 0x34202808U);
        WR1_PROG(REG_1600H, 0x10005066U);

        WR1_PROG(REG_1600H, 0x00003485U);

        r_rsip_func101(bswap_32big(0x73cfe8a2U), bswap_32big(0x650ace97U), bswap_32big(0x9661d3f7U), bswap_32big(0xa154c1edU));
    }

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0000005AU);

    WR1_PROG(REG_1600H, 0x00000842U);

    WR1_PROG(REG_1600H, 0x000008c6U);

    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000004U);

    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000002U);

    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x01003804U);

        WR1_PROG(REG_1600H, 0x342028e0U);
        WR1_PROG(REG_1600H, 0x10005066U);

        WR1_PROG(REG_1600H, 0x00002440U);

        WR1_PROG(REG_1600H, 0x00002cc0U);

        WR1_PROG(REG_1600H, 0x00002485U);
    }

    WR1_PROG(REG_1600H, 0x00002c20U);

    WR1_PROG(REG_1600H, 0x38008840U);
    WR1_PROG(REG_1600H, 0x00000100U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000033U);

    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000024U);

    WR1_PROG(REG_1600H, 0x01003804U);

    WR1_PROG(REG_1600H, 0x342028e0U);
    WR1_PROG(REG_1600H, 0x10005066U);

    WR1_PROG(REG_1600H, 0x00002cc0U);

    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0x00000026U);

    WR1_PROG(REG_1600H, 0x01003804U);

    WR1_PROG(REG_1600H, 0x342028e0U);
    WR1_PROG(REG_1600H, 0x10005066U);

    WR1_PROG(REG_1600H, 0x38008860U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x2a8853fbU), bswap_32big(0x1a6ae647U), bswap_32big(0xe85624feU), bswap_32big(0x11f547deU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        r_rsip_func102(bswap_32big(0xf7adb5e0U), bswap_32big(0x4796a5bcU), bswap_32big(0x7b6d9891U), bswap_32big(0xbea40d4fU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_RETRY;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x0c0f8d14U), bswap_32big(0x96d467fdU), bswap_32big(0x1deba031U), bswap_32big(0xf6ba872dU));

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c300104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A2CH, 0x00000600U);
        WR1_PROG(REG_1A24H, 0x0e3d9407U);
        WAIT_STS(REG_1708H, 0, 0);
        WAIT_STS(REG_1708H, 0, 0);
        WR1_PROG(REG_1704H, 0x001c0013U);
        WR1_PROG(REG_1400H, 0x00840071U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1A24H, 0x0e3d0505U);
        WAIT_STS(REG_1708H, 0, 0);
        WAIT_STS(REG_1708H, 0, 0);
        WR1_PROG(REG_1704H, 0x00040013U);
        WR1_PROG(REG_1400H, 0x00840011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WAIT_STS(REG_1708H, 3, 0);
        WR1_PROG(REG_1700H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x80040080U);
        WR1_PROG(REG_1400H, 0x03420011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x080000b4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WAIT_STS(REG_1A28H, 6, 0);
        WR1_PROG(REG_143CH, 0x00000900U);

        r_rsip_func100(bswap_32big(0x31d4f322U), bswap_32big(0xc31e5c20U), bswap_32big(0x46b25497U), bswap_32big(0x52280cb5U));
        WR1_PROG(REG_1444H, 0x000003a2U);
        WR1_PROG(REG_1A24H, 0x08000075U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_PROG(REG_1420H, bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000000U), bswap_32big(0x00000001U));

        WR1_PROG(REG_1A2CH, 0x00000100U);
        WR1_PROG(REG_1A24H, 0x07338d07U);
        WR1_PROG(REG_1608H, 0x81080000U);
        WR1_PROG(REG_1400H, 0x00890021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1A24H, 0x080000b5U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func100(bswap_32big(0x14bfc28fU), bswap_32big(0xeb41ddbaU), bswap_32big(0x6075540cU), bswap_32big(0xa7cea305U));
        WR1_PROG(REG_1A24H, 0x08000075U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func103();
        r_rsip_func100(bswap_32big(0x4c07de9aU), bswap_32big(0xace51394U), bswap_32big(0xa6e05ed1U), bswap_32big(0xcf113c48U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c2000d4U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WAIT_STS(REG_1A28H, 6, 0);
        WR1_PROG(REG_143CH, 0x00000900U);

        r_rsip_func100(bswap_32big(0x742e8834U), bswap_32big(0x69be03fbU), bswap_32big(0xf9798ca4U), bswap_32big(0x796f0d73U));
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0xe06f96ffU), bswap_32big(0xbe845c0aU), bswap_32big(0xb661847dU), bswap_32big(0xa478e302U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &S_RAM[16]);

        r_rsip_func100(bswap_32big(0xe2485abbU), bswap_32big(0x704604fcU), bswap_32big(0xfbc3f6ecU), bswap_32big(0x48329768U));
        r_rsip_func103();
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

        WR1_PROG(REG_1404H, 0x20000000U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1404H, 0x10000000U);
        WR1_PROG(REG_1400H, 0x00c01001U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1B00H, 0x00008002U);
        WR1_PROG(REG_1B08H, 0x00000d01U);

        WR1_PROG(REG_1B00H, 0x00008001U);

        WR1_PROG(REG_1B08H, 0x00000214U);

        r_rsip_func102(bswap_32big(0xb3c47476U), bswap_32big(0x4861ea94U), bswap_32big(0x23ec4a53U), bswap_32big(0xd8b3b975U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return RSIP_RET_PASS;
    }
}
