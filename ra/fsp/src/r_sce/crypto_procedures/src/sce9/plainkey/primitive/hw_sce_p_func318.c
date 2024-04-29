/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 05.10.2020 1.00        First Release.
 *         : 02.12.2020 1.01        Added new functions such as the Brainpool curve.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_sce_if.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

void HW_SCE_p_func318(void)
{
    uint32_t iLoop    = 0U;
    uint32_t iLoop1   = 0U;
    uint32_t iLoop2   = 0U;
    int32_t  jLoop    = 0U;
    uint32_t kLoop    = 0U;
    uint32_t oLoop    = 0U;
    uint32_t oLoop1   = 0U;
    uint32_t oLoop2   = 0U;
    uint32_t dummy    = 0U;
    uint32_t KEY_ADR  = 0U;
    uint32_t OFS_ADR  = 0U;
    uint32_t MAX_CNT2 = 0U;
    (void)iLoop;
    (void)iLoop1;
    (void)iLoop2;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)oLoop1;
    (void)oLoop2;
    (void)dummy;
    (void)KEY_ADR;
    (void)OFS_ADR;
    (void)MAX_CNT2;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_ECH = 0x00003fbeU;
    HW_SCE_p_func100(0x8c693a67U, 0xb13f66fbU, 0xa25ea81bU, 0x560d7c20U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2074e03cU, 0x98ab4303U, 0xc1cce9b5U, 0xd43ba3ebU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    HW_SCE_p_func320(480);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf51ada8U, 0x1fc04491U, 0xc988fb18U, 0xfaa5c11dU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func320(616);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0dfaa529U, 0x282e920dU, 0xf64592dfU, 0x9f7c68adU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func320(444);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9c1a0702U, 0xedb2e972U, 0x22852fd3U, 0x1855837cU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(580);
    HW_SCE_p_func323();
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x38d4cc3dU, 0xce4e1aa8U, 0x561920b3U, 0x7adf0eb5U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x452bbfd4U, 0x121cc6aaU, 0xbd3daaf0U, 0xedaf7d58U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x45fea76aU, 0x2c6eb1dcU, 0xe2b278ceU, 0x6e651334U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa434e2acU, 0x846c8258U, 0x9bafbdf5U, 0xc50a1cf7U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0x451158f5U, 0x81c038e1U, 0x097a63bbU, 0xe2348aedU);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x65dae8bdU, 0x14d558ceU, 0x16b8aafcU, 0x6bd59a86U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x00005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x050df3ffU, 0x4aecfa26U, 0x639cc9a9U, 0xc359e623U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    HW_SCE_p_func320(408);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf1362f19U, 0x84c03fcfU, 0xb31f41a3U, 0x709874b2U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func320(544);
    HW_SCE_p_func323();
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0266126aU, 0x5478a930U, 0x489ca55cU, 0x04eecab0U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xedb8ae49U, 0xbfdb28e5U, 0x05f80921U, 0xc430a4acU);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x8b69697dU, 0x2c955d96U, 0x8ceae065U, 0x540a0614U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xea10d2f9U, 0xa280b4beU, 0x3834e872U, 0x0458f807U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x934fc829U, 0x8913448fU, 0x5fda9cfeU, 0x8343d6e1U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x83a90bf3U, 0xb6654be1U, 0xe1dbfccaU, 0xf7375c69U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x9536bf06U, 0x9ecd622aU, 0xd94cdfbcU, 0xf5391467U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x00005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x74787d02U, 0x0c72fbacU, 0xd30f6441U, 0x26867c12U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    HW_SCE_p_func320(444);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc61ecfffU, 0xa9953287U, 0xb4500ebfU, 0xd34162e6U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func320(580);
    HW_SCE_p_func323();
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x51aedde7U, 0x9413ad77U, 0xec2342bbU, 0xa4a9cbecU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0xf03ed4f3U, 0x5745c781U, 0x0b42d870U, 0x0c7db3cbU);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0x5674c372U, 0x77e8dea9U, 0x5a55452aU, 0xab9bb69dU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x70b5c05cU, 0x8660d602U, 0xd1c971cbU, 0x76e117c1U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2c5ddd9cU, 0x9b4b818aU, 0x1977f83dU, 0x1f6e88f4U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x10413e6aU, 0x338ea4acU, 0x559a535aU, 0x0e97cb42U);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0xc8d87a13U, 0x28ba25bdU, 0x4ece54ccU, 0x3d697361U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x00005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x000060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x52ffcbfbU, 0x25c68561U, 0x0eeed611U, 0x9cf5088dU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2114e727U, 0x4d307b50U, 0x94f1eb46U, 0xa38d9ce8U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0x09bae1beU, 0xd3e14145U, 0x7d2ba63fU, 0x23c194deU);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x05752256U, 0x4096e871U, 0xafb2d8f2U, 0x9810e5c7U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2ec33011U, 0xbcb2710eU, 0xc81ed862U, 0x457fdff6U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf2131abU, 0xab0a83eaU, 0x7065e26cU, 0xcd6c7bcdU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x1c4648e5U, 0x3a746a56U, 0x40a6b1c3U, 0x8b198efeU);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x413a569aU, 0x477e2227U, 0xcb5e412dU, 0x020d1af2U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5571223aU, 0xb8e696adU, 0xa27da0c5U, 0xa0de4e32U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4b3715c5U, 0x62ff3f7bU, 0xc93b1343U, 0x9e7c130aU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x21fecf08U, 0xc8e1e918U, 0x8addf0e1U, 0x930bd727U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0xae7ec822U, 0x07a1ce62U, 0x55ae5ea0U, 0x5cf840acU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xde7eba77U, 0x66ec29ebU, 0x09990687U, 0x799c56eeU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(952);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0b4fe097U, 0xc820684dU, 0x02412687U, 0x6e212565U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0x395026a9U, 0x6c42a3fbU, 0x07b2fd77U, 0x2c39ed94U);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0x2cbbbb51U, 0xb5c1b6d5U, 0x83276d22U, 0x0c8a2248U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xaaaa7ac4U, 0xfb5bed0eU, 0x8be2cb55U, 0xe7fd0473U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func320(480);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x31ff55c9U, 0x8140b0f5U, 0xceb9a311U, 0xf8a6f300U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(616);
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x000060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x0000c8d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xacaeb6e8U, 0xd069eaffU, 0xfd178003U, 0xc18b9d75U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(896);
    HW_SCE_p_func100(0xbf3b464fU, 0x49a9553fU, 0xc387c770U, 0xc7f9b17dU);
    HW_SCE_p_func314(896+36);
    HW_SCE_p_func100(0x1f7f68abU, 0x91a1a4efU, 0x664851deU, 0x26452beeU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x726ceea7U, 0xbde2b6e5U, 0xe19911d3U, 0xecccacfeU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa17ed11eU, 0x2ef17845U, 0x267746bfU, 0xb3fd52dfU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xfc753a2bU, 0xf34825afU, 0x03876e89U, 0x51b76719U);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0xf3047cc0U, 0x32c7c135U, 0x77bbf376U, 0xe4c5bdcaU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x61da3608U, 0x2332ad99U, 0x3f516d34U, 0xcd2305dfU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc8e8a814U, 0x05a35651U, 0xaca24a7fU, 0x0ea729faU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x1dde4b25U, 0x530e5bb0U, 0xc5becf97U, 0x35b81685U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x27d54b6dU, 0xeefed33fU, 0xc73bc03bU, 0xd427373dU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa900c2c0U, 0x602b64dcU, 0x5d44f94bU, 0x4fe44840U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xaf0d3c1cU, 0x50563233U, 0xe2b291b6U, 0xe0e17dd0U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xbea9c41cU, 0x79c109f4U, 0xc1a7ff55U, 0xcadfd250U);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x647ca49eU, 0xb06921a5U, 0xe84a252dU, 0xc598c5a4U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x91c27ea4U, 0x049f5f5aU, 0xc129ce0cU, 0x64a8e27bU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func320(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xd55a5390U, 0x35f33131U, 0xd6a62829U, 0x7d2fa738U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func320(408);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(544);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x000060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f0U;
    HW_SCE_p_func101(0x5b38f724U, 0xe9aa7946U, 0xa88a1bbfU, 0x4d8a1c23U);
    HW_SCE_p_func316();
    HW_SCE_p_func100(0xe81e581cU, 0x1b609ef3U, 0x346419fdU, 0x8a3fe878U);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa1941a0eU, 0xcdcde287U, 0x1b756ae4U, 0xe9bdb894U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xea1c0bbdU, 0x9ae71488U, 0xfa0a43b3U, 0xa5729ea2U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x066e4ff9U, 0xf8dbab9fU, 0xafc2b53aU, 0xf9846ca7U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x692d67d5U, 0xe8de307bU, 0xcb829d7fU, 0x92fe6f5cU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc1fc96f6U, 0x295eac95U, 0x7352e482U, 0x21ae2cb1U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(952);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1b397203U, 0xf394d796U, 0x8b40b8a1U, 0x7c0e538eU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0x0f0d9326U, 0x089c4bf1U, 0x39dc51eaU, 0x3703a5acU);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0xa124c08bU, 0xc2ecaa23U, 0x531ca0f3U, 0x40c3e724U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4b859310U, 0x0b9fd51fU, 0xf76e1dc8U, 0xff37911eU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5372057aU, 0xf005e4a0U, 0x4dbb9b05U, 0xa278ffb8U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x80f4b23dU, 0x05c58c40U, 0x4e36b493U, 0xb12e2146U);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x69e11c7fU, 0x60427693U, 0x38ce5d4cU, 0x8be945a7U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000408U;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cU;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x8000f4d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x000050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb76505f2U, 0xebf3eb95U, 0x4fa359a1U, 0x04a325bbU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x287e45eeU, 0xeb5626adU, 0x449bc603U, 0xf05aa3faU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(896);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xeb481312U, 0x27c8327dU, 0x7f4519acU, 0xde7645abU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(896);
    HW_SCE_p_func100(0x7feadcc7U, 0x4d7648c9U, 0xa9f88d13U, 0xbb0d7a6fU);
    HW_SCE_p_func314(896+36);
    HW_SCE_p_func100(0xc2684d93U, 0x6d5d6e62U, 0x909d3383U, 0x31c612e1U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe5b4cae5U, 0xbcfc9e35U, 0x66ccaeedU, 0x09b575afU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe7e196efU, 0x8bda93e4U, 0x06cfe5f7U, 0x42a9bdfeU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xb8a0f1b1U, 0x10d2babbU, 0xe39d0053U, 0xca6a2be4U);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0xc8bff03bU, 0x822949adU, 0x1d0275c3U, 0x66aa2304U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xd088dc87U, 0x1e079d65U, 0x58f71342U, 0xfe73372eU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6a449ba3U, 0x644592a8U, 0xe4c0d031U, 0x0111d512U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x136d4dceU, 0x8829fe81U, 0xe1fdab6cU, 0x90d661c3U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0xdd6d1badU, 0x3f4fd94fU, 0x17bb48e3U, 0x7955ea13U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x47c671eeU, 0xac239171U, 0x21208ac1U, 0x6f45b650U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x89c44f64U, 0xcbc5e25aU, 0x5f99f504U, 0x071f488eU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x79a12141U, 0x224ee8dcU, 0x5ab33560U, 0xc20b192aU);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x81c4a87bU, 0xe2676d1dU, 0xbac0211aU, 0x5ff29039U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000002U;
    SCE->REG_24H = 0x80004cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000810U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030U;
    SCE->REG_24H = 0x80007cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe1c00d44U, 0xa3b1d245U, 0x3379eef5U, 0xa7a32ecdU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x7e4caf6cU, 0xd26d5b9cU, 0x2009e623U, 0xd5135784U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcec6776eU, 0x068afdfbU, 0x5b95a84bU, 0x37dea6cdU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0x5bb04bc7U, 0x40307f33U, 0x4438611cU, 0xce77ef4cU);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0xc23e5bffU, 0x3ff2f682U, 0x86ffb501U, 0x4b33968bU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe6aa096dU, 0xd2c44e40U, 0x4bd7380eU, 0x1ee64b02U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x66651932U, 0xdd1276c0U, 0xcb505742U, 0xa96b774aU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0xc92bb4b8U, 0x3ec1b9beU, 0x6e7c1b1fU, 0x55983590U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x96245bd7U, 0x56105797U, 0x13f7872cU, 0xe823d68dU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf5e906f9U, 0x44bb39adU, 0xd0519e29U, 0x7475f442U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(952);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x06aff7d1U, 0x18aea6c8U, 0x86f229c2U, 0xf0e58cddU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(952);
    HW_SCE_p_func100(0x68d7ffdbU, 0x48eebde8U, 0x65c5ae8bU, 0xfcd43c74U);
    HW_SCE_p_func314(952+36);
    HW_SCE_p_func100(0x58880bd1U, 0xa03cce13U, 0x5cb152e7U, 0x54ed01dbU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbeb6df12U, 0xb51f6599U, 0x04dd5c6dU, 0xf91a1791U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x25cafafeU, 0x8c3c0489U, 0x66ca83ffU, 0xd6d66e08U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0x1f46ab53U, 0x124cc60cU, 0x8ad45ce5U, 0x7fb59dd1U);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x9b79a0f6U, 0xcb67c0b6U, 0xa3a3e1b3U, 0xd73496bbU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6e0e8a8aU, 0x6b6b1bf9U, 0xb4b8663bU, 0x628bad41U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func320(680);
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func322(952);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f1U;
    HW_SCE_p_func101(0x95bda937U, 0x8aa1ebf4U, 0x011ebbfbU, 0xc72e05a2U);
    HW_SCE_p_func316();
    HW_SCE_p_func100(0xd5706a1cU, 0x9efead44U, 0x8624f1b4U, 0xe4ed91eeU);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf27d42d7U, 0x9aebe897U, 0xa4bf4ed6U, 0xea904263U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x7b35e1c2U, 0x376987cdU, 0xffea7a71U, 0xfa1ff3f6U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xcc82736aU, 0x582bd5faU, 0x3a5ab3c7U, 0x73c1f935U);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0xc3892749U, 0x72d1a0c4U, 0x4bbe56d8U, 0x16968510U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000408U;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cU;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x8000f4d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_24H = 0x000050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1e9fc4b4U, 0xa5142e28U, 0x2f8d26a5U, 0xf5e585f3U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x48326af2U, 0x44f85d94U, 0x71fcc7abU, 0xb1d54290U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1c1d2aacU, 0xee5bfa48U, 0x15543797U, 0xd62be25cU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xbff66f32U, 0xdeaa2ffaU, 0xaeea0bf2U, 0x57221606U);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x3f4de62aU, 0xd4a7763cU, 0x72a2c25dU, 0xfee76446U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x408a6332U, 0x70c85823U, 0xba550647U, 0x6c7a0118U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xce068befU, 0x594ede3cU, 0xdd21f885U, 0x161bb234U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x06577a13U, 0x046c382aU, 0x87202106U, 0x4aadd486U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x693044b9U, 0xf444e09dU, 0x9cd38744U, 0xe79400dfU);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000002U;
    SCE->REG_24H = 0x80004cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000810U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030U;
    SCE->REG_24H = 0x80007cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x02c0a883U, 0x19bc9bf8U, 0x8a4d98f1U, 0xe96ed903U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfa3c622cU, 0xbe404837U, 0xeaf69b97U, 0x06fe547bU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x302b59aaU, 0x3c798675U, 0xb2620a09U, 0xabfc9999U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x2caa1a54U, 0x74f01619U, 0x52968b85U, 0xde32ac27U);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0xaf3e4354U, 0xc389c01cU, 0x8632c676U, 0x37f71c4fU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfa47bbbcU, 0x2186ab9bU, 0x6cbb06aeU, 0x24eec58dU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbba4691bU, 0xe809e7ecU, 0x87cc4caeU, 0x36e4d9ceU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(992);
    HW_SCE_p_func100(0xc300af1dU, 0x00630fe3U, 0x587a44c0U, 0x979fcffdU);
    HW_SCE_p_func314(992+36);
    HW_SCE_p_func100(0x1add51aaU, 0xd1792bb8U, 0x5da32e2dU, 0xd9009259U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6533e676U, 0x00320303U, 0x5c57fa97U, 0xcd8f78d4U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func320(680);
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func322(992);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f2U;
    HW_SCE_p_func101(0x20156d0dU, 0x4a6debf6U, 0xcd98c326U, 0xc2592cf4U);
    HW_SCE_p_func316();
    HW_SCE_p_func100(0xb2a69fbdU, 0xd54a0102U, 0xa4ae8bc1U, 0xb09ac9cbU);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x21279ea7U, 0x8885e559U, 0xfee5f26fU, 0xb8e8810eU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc61bc8d8U, 0xa17db7e5U, 0x4cf9ace0U, 0x8f4f62c0U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x3511825fU, 0xa1ad11c6U, 0x31304478U, 0x31441f8aU);
    HW_SCE_p_func314(816+36);
    HW_SCE_p_func100(0x7afc6944U, 0x3665a4b9U, 0xe89d431eU, 0x812626ecU);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000408U;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cU;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x8000f4d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_24H = 0x000050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9370c3b9U, 0x1148f325U, 0xe6e883c1U, 0x1554a40eU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5de51f5aU, 0xd2ab8b57U, 0x5b4abc0aU, 0xb66fa0ecU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(896);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x73ba7d8eU, 0x3ec086e9U, 0xb7f46379U, 0x9bfbb9e7U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(896);
    HW_SCE_p_func100(0x98fcf7c7U, 0xdb8e3b77U, 0x6d7956d9U, 0x27e79ea2U);
    HW_SCE_p_func314(896+36);
    HW_SCE_p_func100(0xf4cbee06U, 0x7c2204a2U, 0x9d9edc3fU, 0xf500a0deU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4327aa73U, 0xc6d287bbU, 0x43f83e20U, 0x2d47933dU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x898cf445U, 0xcd6ecfe9U, 0xb1e7dd5dU, 0x3e376e78U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xe04ac6d1U, 0xbbd060d9U, 0x5333fbedU, 0xb1c7a350U);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x78baf84bU, 0xd1b8ce55U, 0x026ec1a4U, 0x85342454U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000002U;
    SCE->REG_24H = 0x80004cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000810U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030U;
    SCE->REG_24H = 0x80007cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8da0cac8U, 0x7f4719efU, 0xdd188136U, 0xc4b4b9c7U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf53761fU, 0x094a3437U, 0xe9a062d0U, 0xd6a2d246U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcc697f8bU, 0x92ad849aU, 0xa4431439U, 0x9d2a656dU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x55bcde64U, 0x94f0b7ceU, 0xc4beae7eU, 0x801ee81dU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func321(816);
    HW_SCE_p_func100(0x20b7209eU, 0x64136fe8U, 0x7c127365U, 0xde84756bU);
    HW_SCE_p_func314(816+36);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x00009cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103e0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x800103c0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x3800dbffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x0e0631dfU, 0xffba1140U, 0xdb43c976U, 0xa4eb562cU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0xffffffffU;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x1d28f437U, 0x93b026e2U, 0xf16d82e8U, 0x9f89524aU);
    }
    else
    {
        SCE->REG_ECH = 0x00000800U;
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0xf946db7dU, 0x8ce722a7U, 0xd1bf9f9fU, 0x652119e5U);
    }
    HW_SCE_p_func100(0xf758d158U, 0x1da3af1cU, 0x8442f130U, 0x481aeb30U);
    SCE->REG_ECH = 0x000034ffU;
    SCE->REG_ECH = 0x00003420U;
    SCE->REG_ECH = 0x00003440U;
    SCE->REG_ECH = 0x00003460U;
    SCE->REG_ECH = 0x00003480U;
    SCE->REG_ECH = 0x000034a0U;
    SCE->REG_ECH = 0x000034c0U;
    SCE->REG_E0H = 0x81080000U;
    SCE->REG_00H = 0x00003823U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000804U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c04U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x8000b0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8ce9f145U, 0x0583725dU, 0x018addc6U, 0x34a422faU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func321(856);
    HW_SCE_p_func100(0xc6b3739cU, 0xd28a9d79U, 0x1a35fa37U, 0xa6242a49U);
    HW_SCE_p_func314(856+36);
    HW_SCE_p_func100(0x55afc622U, 0xa9d4b88eU, 0x14cfedb9U, 0x2b7144c8U);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func322(896);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x3800dbdfU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x1c438645U, 0x94e7987fU, 0xd13e1a83U, 0xe5515679U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0xffffffffU;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x94647d15U, 0xf787c49eU, 0xef925afeU, 0x6482c67eU);
    }
    else
    {
        SCE->REG_ECH = 0x00000800U;
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0x2a5c9e0bU, 0x8043cdf5U, 0x8b7f2110U, 0x0d8657c3U);
    }
    SCE->REG_ECH = 0x000034feU;
    SCE->REG_ECH = 0x00003420U;
    SCE->REG_ECH = 0x00003440U;
    SCE->REG_ECH = 0x00003460U;
    SCE->REG_ECH = 0x00003480U;
    SCE->REG_ECH = 0x000034a0U;
    SCE->REG_ECH = 0x000034c0U;
    SCE->REG_E0H = 0x81080000U;
    SCE->REG_00H = 0x00003823U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000804U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c04U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x8000b0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    HW_SCE_p_func100(0x9a8f5bd4U, 0x7c50c72bU, 0x2584aed1U, 0xbffc5331U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf8a9bcacU, 0xaa6f357fU, 0x644801e7U, 0x96ba6801U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func322(816);
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbb149186U, 0x526dc394U, 0xedf700e9U, 0x16c04c42U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func322(856);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000012c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1a9e726bU, 0xffb2129bU, 0x15e2b7fbU, 0x10575273U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func320(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4f21d1bcU, 0xb4adf116U, 0xa072f0c8U, 0x5bc08591U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    HW_SCE_p_func320(716);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(752);
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x800060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103e0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x3800dbffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0xbf8f24dcU, 0xa8611807U, 0xd3d73e92U, 0x917d5611U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x04001981U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x02001181U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001U;
            SCE->REG_E0H = 0x800103e0U;
            SCE->REG_00H = 0x0000031fU;
            SCE->REG_2CH = 0x00000023U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00008307U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x3800dbffU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x16bbe080U, 0x3a58b36dU, 0x9c3bd981U, 0x89c7e361U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0x74ef9fabU, 0x4f103f45U, 0x28e539d5U, 0x8781be87U);
                oLoop1 = 0;
            }
            else
            {
                HW_SCE_p_func101(0xa8588d4eU, 0xd6390acaU, 0x96539494U, 0x6e8e682fU);
            }
        }
    }
    else
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x04001991U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x02001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001U;
            SCE->REG_E0H = 0x800103e0U;
            SCE->REG_00H = 0x0000031fU;
            SCE->REG_2CH = 0x00000023U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00008307U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x3800dbffU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            HW_SCE_p_func100(0x362dfab8U, 0x92e5f78aU, 0x438ce431U, 0xf280d849U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_24H = 0x04001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x02001181U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                HW_SCE_p_func101(0x08586c47U, 0x91f65898U, 0xd0f33d44U, 0x5c1d4285U);
                oLoop1 = 0;
            }
            else
            {
                HW_SCE_p_func101(0x09a1a341U, 0x90a8d52aU, 0x83a061f8U, 0x02856805U);
            }
        }
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func318.prc
***********************************************************************************************************************/
