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

void HW_SCE_p_func093 (const uint32_t ARG1[], uint32_t ARG2[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    HW_SCE_p_func100(0x700d45a4U, 0xc88e4b39U, 0xfb9a3a88U, 0xcb7bd92eU);
    HW_SCE_p_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1400H, 0x03420005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x0002000dU);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x000034e0U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x000000ffU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x5a6fa76cU, 0xc3f5a279U, 0x76947271U, 0xac64b2fcU);
    HW_SCE_p_func043();

    WR1_PROG(REG_1600H, 0x000034e4U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x000000feU));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x81188bcdU, 0xd465cb3aU, 0x5460ee88U, 0xfa6e9d6dU);
    HW_SCE_p_func044();

    HW_SCE_p_func100(0xea88f7e8U, 0x8c73c3daU, 0xada49d15U, 0xe6e78f26U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1000H, 0x00010000U);

    HW_SCE_p_func081();

    WR1_PROG(REG_1600H, 0x00007c01U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    oLoop = 0;
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE); )
        {
            HW_SCE_p_func100(0xcaf0e3ddU, 0x2bafaf44U, 0x2d6379ccU, 0x634d5e35U);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG1[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe7008d05U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG2[1 + iLoop]);

            HW_SCE_p_func101(0xfd2a99ceU, 0xa2612117U, 0x1267722aU, 0x67fddc1fU);
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        HW_SCE_p_func101(0x2f8b022fU, 0xd4fcbf20U, 0x268da526U, 0xa0043c95U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000aU)
    {
        HW_SCE_p_func100(0x883efbd9U, 0x10be4127U, 0x9e42ed06U, 0x2a6f8bccU);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func094(0U, ARG1);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG2);
        HW_SCE_p_func100(0x0e7fe377U, 0x0057afc8U, 0x955969efU, 0x7faefecaU);
        HW_SCE_p_func065(8U, ARG2);
        HW_SCE_p_func100(0x7c53609cU, 0x4adc0feeU, 0xc88f44c3U, 0x5486ffadU);
        HW_SCE_p_func065(16U, ARG2);
        HW_SCE_p_func100(0x95c3d45eU, 0x645838d0U, 0x7e7729e0U, 0xfb7646e7U);
        HW_SCE_p_func065(24U, ARG2);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0x4a0cb2b5U, 0x7eeb4cb4U, 0x150c3bf0U, 0xc0d1c58bU);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x08000105U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG1[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG2[1 + oLoop]);

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func100(0xe4427ea5U, 0xb923a279U, 0xf20e1de6U, 0xcc2db4fbU);
        HW_SCE_p_func060();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(36U, ARG2);
        HW_SCE_p_func100(0x697637e6U, 0xab9f06a8U, 0x7c17be0dU, 0xa727a23cU);
        HW_SCE_p_func062(44U, ARG2);
        HW_SCE_p_func100(0xc9262b8aU, 0x047cd05bU, 0x3e8f12b2U, 0xc31d9b1dU);
        HW_SCE_p_func062(52U, ARG2);
        HW_SCE_p_func100(0xa1206d57U, 0xc68191cdU, 0xc9b3bddcU, 0xae966368U);
        HW_SCE_p_func062(60U, ARG2);
        oLoop = 36U + 32U;

        HW_SCE_p_func101(0xa6054347U, 0xfebb0bd4U, 0xebca76feU, 0x51a0bb78U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000bU)
    {
        HW_SCE_p_func100(0x465fc8d1U, 0x400001a6U, 0x424d5e49U, 0x2078dcf6U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func094(0U, ARG1);
        iLoop = 32U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG2);
        HW_SCE_p_func100(0xf10a8e46U, 0xe3002cabU, 0x0f086e01U, 0xb264a8edU);
        HW_SCE_p_func062(8U, ARG2);
        HW_SCE_p_func100(0x59eaca4dU, 0xb8d66c8eU, 0xf38fe05aU, 0x594803c7U);
        HW_SCE_p_func062(16U, ARG2);
        HW_SCE_p_func100(0x860a541eU, 0xc1d26135U, 0xfd4a7c66U, 0x108a8ac3U);
        HW_SCE_p_func062(24U, ARG2);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0x118a2be6U, 0xec5ba1d7U, 0xa6767038U, 0xe95230eeU);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func094(32U, ARG1);
        iLoop = 32U + 32U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(32U, ARG2);
        HW_SCE_p_func100(0x6d22b147U, 0x256e53d1U, 0xbf01a614U, 0xcae8cf46U);
        HW_SCE_p_func062(40U, ARG2);
        HW_SCE_p_func100(0xd5d5a40cU, 0x06d07f06U, 0x4c86d89aU, 0x1f69f627U);
        HW_SCE_p_func062(48U, ARG2);
        HW_SCE_p_func100(0x466fe75aU, 0x43adda6cU, 0xc3c67be2U, 0x102a971fU);
        HW_SCE_p_func062(56U, ARG2);
        oLoop = oLoop + 32U;

        HW_SCE_p_func100(0x2ef43445U, 0x37f6a287U, 0x7db606edU, 0x63813895U);
        HW_SCE_p_func060();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(64U, ARG2);
        HW_SCE_p_func100(0xea83f41aU, 0x2b7e8254U, 0x33e0fc5bU, 0x322613c6U);
        HW_SCE_p_func062(72U, ARG2);
        HW_SCE_p_func100(0x14724698U, 0x3314682bU, 0x0f4ce1dbU, 0x2370fa3cU);
        HW_SCE_p_func062(80U, ARG2);
        HW_SCE_p_func100(0x62949a4dU, 0xca452050U, 0x525d9a06U, 0x408bab26U);
        HW_SCE_p_func062(88U, ARG2);
        oLoop = 64U + 32U;

        HW_SCE_p_func101(0x810607edU, 0xfa0c2f3bU, 0x4adfa484U, 0xc4b5bfbdU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000cU)
    {
        HW_SCE_p_func100(0xf4df8689U, 0x7e905961U, 0x770489d9U, 0x42bea35bU);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func095(0U, ARG1);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func065(0U, ARG2);
        HW_SCE_p_func100(0x82f0d2eaU, 0x9ac9e7a8U, 0xd15dcca9U, 0xa5f34f08U);
        HW_SCE_p_func065(8U, ARG2);
        HW_SCE_p_func100(0x22e8b5eaU, 0x3273f226U, 0xdde0b5a8U, 0xfeff2cd3U);
        HW_SCE_p_func065(16U, ARG2);
        HW_SCE_p_func100(0x83e15e6cU, 0x4d25fc27U, 0x7810be5bU, 0xafd1e06aU);
        HW_SCE_p_func065(24U, ARG2);
        HW_SCE_p_func100(0x70a3caacU, 0x5d1b46e5U, 0x7186268bU, 0x1608ad09U);
        HW_SCE_p_func065(32U, ARG2);
        HW_SCE_p_func100(0x1869fa48U, 0x803c5e42U, 0x537d7bc3U, 0x73ed45e9U);
        HW_SCE_p_func065(40U, ARG2);
        HW_SCE_p_func100(0x1999ad95U, 0x89516147U, 0x346608bdU, 0xbf8c0b0aU);
        HW_SCE_p_func065(48U, ARG2);
        HW_SCE_p_func100(0xa8853929U, 0x80f97c28U, 0xb883e053U, 0x7e31fcd3U);
        HW_SCE_p_func065(56U, ARG2);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0xefdbccb9U, 0xcaf62151U, 0x59a90bb3U, 0x233f618fU);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x08000105U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG1[iLoop]);
        iLoop = iLoop + 4U;

        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0xe8008105U);
        WR1_PROG(REG_1400H, 0x00810011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &ARG2[1 + oLoop]);

        WAIT_STS(REG_1A28H, 6, 0);

        HW_SCE_p_func100(0xa45b4f5fU, 0x26a39228U, 0x401ef2ccU, 0x4dd2f366U);
        HW_SCE_p_func066();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(68U, ARG2);
        HW_SCE_p_func100(0x711a9774U, 0xa483956dU, 0x7ee799f8U, 0xa5e0da1fU);
        HW_SCE_p_func062(76U, ARG2);
        HW_SCE_p_func100(0xfc30c578U, 0x905bcbeeU, 0x57c84f4bU, 0xec2c4ee9U);
        HW_SCE_p_func062(84U, ARG2);
        HW_SCE_p_func100(0x86c104cfU, 0x983f80b5U, 0x9ed08ba8U, 0x389b1a32U);
        HW_SCE_p_func062(92U, ARG2);
        HW_SCE_p_func100(0x85e63e4bU, 0xc51ba1a8U, 0xde52085dU, 0x86ac5bc7U);
        HW_SCE_p_func062(100U, ARG2);
        HW_SCE_p_func100(0x179c9b1aU, 0x1f605dbbU, 0x0712d896U, 0x1dfbb1a6U);
        HW_SCE_p_func062(108U, ARG2);
        HW_SCE_p_func100(0x35484559U, 0xf5a5c5e9U, 0xd09af002U, 0xca781271U);
        HW_SCE_p_func062(116U, ARG2);
        HW_SCE_p_func100(0xcf259f52U, 0x9fd2f79dU, 0x5e15ef07U, 0xdae4bebeU);
        HW_SCE_p_func062(124U, ARG2);
        oLoop = 68U + 64U;

        HW_SCE_p_func101(0xc754a252U, 0xfd1be47cU, 0xdfd985acU, 0xf333779fU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x0000000dU)
    {
        HW_SCE_p_func100(0x4f2061c5U, 0xfd862feeU, 0x1ac89a20U, 0x5e422cf1U);
        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func095(0U, ARG1);
        iLoop = 64U;

        WR1_PROG(REG_1404H, 0x10000000U);
        HW_SCE_p_func062(0U, ARG2);
        HW_SCE_p_func100(0x9742b7fdU, 0xf0763297U, 0x51e50993U, 0x5cf76f91U);
        HW_SCE_p_func062(8U, ARG2);
        HW_SCE_p_func100(0x8de602aeU, 0x08168872U, 0x7f34367aU, 0xe8c1cbe9U);
        HW_SCE_p_func062(16U, ARG2);
        HW_SCE_p_func100(0xd4376114U, 0x46d10b9dU, 0xa59e6636U, 0xf45e8609U);
        HW_SCE_p_func062(24U, ARG2);
        HW_SCE_p_func100(0x0813c025U, 0xc87a6178U, 0xa8e78ad8U, 0x10fe30abU);
        HW_SCE_p_func062(32U, ARG2);
        HW_SCE_p_func100(0x053e1561U, 0xe46a349bU, 0xfa597c68U, 0x2770d863U);
        HW_SCE_p_func062(40U, ARG2);
        HW_SCE_p_func100(0x124a3edfU, 0x87b92b32U, 0xef781c02U, 0xdcc7ec46U);
        HW_SCE_p_func062(48U, ARG2);
        HW_SCE_p_func100(0x202debbaU, 0xa85a68d8U, 0xc6c868d1U, 0x70f0c9fdU);
        HW_SCE_p_func062(56U, ARG2);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0x240f1facU, 0xf7d9b6e0U, 0xfe6fe211U, 0xbf082b84U);
        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func095(64U, ARG1);
        iLoop = 64U + 64U;

        WR1_PROG(REG_1404H, 0x11100000U);
        HW_SCE_p_func062(64U, ARG2);
        HW_SCE_p_func100(0xc92d660cU, 0x44467a53U, 0x81cdebd7U, 0x49f7ae62U);
        HW_SCE_p_func062(72U, ARG2);
        HW_SCE_p_func100(0x80e9dcabU, 0x7b970d10U, 0x0c6af314U, 0xd5761810U);
        HW_SCE_p_func062(80U, ARG2);
        HW_SCE_p_func100(0x86f337eeU, 0x7e11979bU, 0x7059287bU, 0x851bd86fU);
        HW_SCE_p_func062(88U, ARG2);
        HW_SCE_p_func100(0x7d3d7152U, 0x6fb85144U, 0x53556a56U, 0x42967bceU);
        HW_SCE_p_func062(96U, ARG2);
        HW_SCE_p_func100(0x2df9b663U, 0x4db2038fU, 0x4c816069U, 0x8ba89da3U);
        HW_SCE_p_func062(104U, ARG2);
        HW_SCE_p_func100(0xa1271485U, 0x7021b6afU, 0x89e6df79U, 0x200a15afU);
        HW_SCE_p_func062(112U, ARG2);
        HW_SCE_p_func100(0x5ce0eff0U, 0x07847ed5U, 0x419ce2a2U, 0xf6882a81U);
        HW_SCE_p_func062(120U, ARG2);
        oLoop = oLoop + 64U;

        HW_SCE_p_func100(0x1670048eU, 0x1d65f7e4U, 0xcb782416U, 0x77e06f17U);
        HW_SCE_p_func066();

        WR1_PROG(REG_1404H, 0x11180000U);
        HW_SCE_p_func062(128U, ARG2);
        HW_SCE_p_func100(0x07379295U, 0x96be1f33U, 0x781df0f3U, 0x3644a5d6U);
        HW_SCE_p_func062(136U, ARG2);
        HW_SCE_p_func100(0xd0efa1f3U, 0x1c515ecbU, 0x3b3bb1eeU, 0x2ac2f752U);
        HW_SCE_p_func062(144U, ARG2);
        HW_SCE_p_func100(0x56b8287bU, 0x20fb42c9U, 0x91e58c77U, 0x9299a6f9U);
        HW_SCE_p_func062(152U, ARG2);
        HW_SCE_p_func100(0x386ee0ddU, 0x90e2b77eU, 0x0da4cf4aU, 0x39625da9U);
        HW_SCE_p_func062(160U, ARG2);
        HW_SCE_p_func100(0xe8bbb2c8U, 0x618c05b7U, 0x178c8491U, 0x57741c31U);
        HW_SCE_p_func062(168U, ARG2);
        HW_SCE_p_func100(0x2ba2c379U, 0x2128d84eU, 0xcacaa775U, 0xc6b911ebU);
        HW_SCE_p_func062(176U, ARG2);
        HW_SCE_p_func100(0x214e604dU, 0x85f45d5aU, 0xe8b6d0acU, 0x66afb1d3U);
        HW_SCE_p_func062(184U, ARG2);
        oLoop = 128U + 64U;

        HW_SCE_p_func101(0xd2ce4facU, 0x11d07619U, 0x308989b3U, 0x5523843fU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000012U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE); )
        {
            HW_SCE_p_func100(0x6d1d8addU, 0x003a7380U, 0x8a196597U, 0xeda48acdU);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000105U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &ARG1[iLoop]);

            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xe8008105U);
            WR1_PROG(REG_1400H, 0x00810011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &ARG2[1 + iLoop]);

            HW_SCE_p_func101(0x7a3f3191U, 0x6fb2bf7eU, 0x8ae82f99U, 0xe9a29251U);
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        HW_SCE_p_func101(0xb6e01d24U, 0x495319dfU, 0xbae6fc17U, 0x164fd4e8U);
    }

    HW_SCE_p_func100(0x5f7f7e31U, 0x738c66fdU, 0x3c478859U, 0xab9d49b1U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &ARG2[1 + oLoop]);

    WR1_PROG(REG_1600H, 0x00007c1cU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}

