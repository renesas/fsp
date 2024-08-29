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

void HW_SCE_p_func309_r1(void)
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
    HW_SCE_p_func100(0x507efdf0U, 0x2d03401aU, 0xf5398ec0U, 0x286217ffU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000028U;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000b7bU;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x230f406fU, 0xda7f5edcU, 0x27c3bebbU, 0x1ca2d98fU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(476);
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func312(612);
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000090U;
    HW_SCE_p_func101(0x6cc0e7d9U, 0x458cdd1fU, 0x11511bb6U, 0x77d8e29aU);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0xb8612113U, 0xf762b28aU, 0x1e228883U, 0x606b460fU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x00003fbeU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x07650df4U, 0x218ae494U, 0x62a374a7U, 0x69f77c6dU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func313(884);
    HW_SCE_p_func100(0x3b9e2e17U, 0x00dc30b0U, 0xd4f87fbdU, 0x78cc9f77U);
    HW_SCE_p_func314(884+64);
    HW_SCE_p_func100(0x34f500c3U, 0x1e7d953dU, 0x5a457d14U, 0x1456c4e7U);
    SCE->REG_ECH = 0x3000db72U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d770U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_24H = 0x0000d0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x045fd001U, 0x1c068ffcU, 0xf9ad4dc2U, 0x0dc15f12U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x23ee48a2U, 0x420f6666U, 0x7f916148U, 0xbcaeb32fU);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0xedc72e02U, 0x9067ecb0U, 0xbd01da64U, 0x475ec240U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x000000a0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04000991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xa0d2af88U, 0x564963feU, 0xfda15b9fU, 0x0a9b6eb2U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(952);
    HW_SCE_p_func100(0x8efeada1U, 0x86c947d3U, 0x97c19f1dU, 0xc42b5457U);
    HW_SCE_p_func314(952+64);
    HW_SCE_p_func100(0x9b785ba7U, 0xca31ebe8U, 0xf0c98a00U, 0x3de02bd5U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbc1763d6U, 0xbaf51d99U, 0x286abac4U, 0x4afbbf25U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(544);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x20f12a95U, 0x2310397aU, 0x9acc6944U, 0x9593ac91U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func312(612);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xffceae7aU, 0x6ced0145U, 0xa2b22416U, 0x66e29adcU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(408);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func312(476);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_34H = 0x00000008U;
    SCE->REG_24H = 0x800011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000000cU;
    SCE->REG_24H = 0x82001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000028U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000091U;
    HW_SCE_p_func101(0x38ac0cdfU, 0x425c549bU, 0x4671434cU, 0xe7db001cU);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0xdcd705d9U, 0xc956e1baU, 0x824590e2U, 0xe2a4d2baU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0xc5cbb3acU, 0x5a613e5fU, 0xe6719980U, 0xf4de0324U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0x5618de29U, 0x7dbf376bU, 0xdc848924U, 0xc3253b00U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0xb8196e42U, 0x78ff726aU, 0xcffc4955U, 0x6a8728b9U);
    }
    HW_SCE_p_func100(0x2f82a82dU, 0xbf4bcf6aU, 0x553f6038U, 0x8cac813cU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x89e121cdU, 0x93dc5382U, 0x515ddcadU, 0x04b38724U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0xae198934U, 0x9f1bc69cU, 0x05bffac6U, 0x9ba4919fU);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x8459fdfbU, 0x6264fd2cU, 0x58015355U, 0x6a1a691fU);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(952);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x3800db71U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x13094415U, 0x7c03e279U, 0x87253dceU, 0x8671997bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0xf526deaaU, 0x635f2504U, 0x0c669acaU, 0x08b6f407U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0xc43db222U, 0xe635f693U, 0xeba2377dU, 0xd87d0b4cU);
    }
    HW_SCE_p_func100(0xabd3f950U, 0x60198146U, 0xadd1361cU, 0xd933adc9U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0737b74fU, 0x953016b6U, 0xb66797cbU, 0x75808618U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(952);
    HW_SCE_p_func100(0x78ef5134U, 0x844af139U, 0xd4823d75U, 0xf6f97fd9U);
    HW_SCE_p_func314(952+64);
    HW_SCE_p_func100(0xe5f9bbbeU, 0x96509cc3U, 0x8318b854U, 0x9bd50be0U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xaa1376c8U, 0x78c0ff2aU, 0xbe1af5b8U, 0xda3a88cfU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(408);
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9bedacc0U, 0x8f425520U, 0x027f1c14U, 0xc15dde50U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func312(544);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func312(680);
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000092U;
    HW_SCE_p_func101(0xb3093a43U, 0xac9c9129U, 0x503622eeU, 0x14cdab75U);
    HW_SCE_p_func304_r1();
    HW_SCE_p_func100(0xe32e76f5U, 0x11a6942dU, 0xdf08bb94U, 0x69570b0dU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x62b11180U, 0x0ee880b8U, 0xc1c11bd2U, 0x15f65922U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190U);
        HW_SCE_p_func101(0x0d868a6aU, 0x65052db0U, 0xe774b17aU, 0xab134626U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x4507bc11U, 0xdf51099eU, 0x7400ad3bU, 0xadedb23dU);
    }
    HW_SCE_p_func100(0x1db9f65dU, 0x7a78d897U, 0xb589b7baU, 0x0d86c3a2U);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x90e33230U, 0xd7da6c0cU, 0xabd9d876U, 0x2d38ff3bU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x9fd81c3dU, 0x58ca1673U, 0xa58d4cbbU, 0x1a9d9068U);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x0d1d631dU, 0x1c5ababaU, 0xd136b9c0U, 0x6a317f80U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(952);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x3800db71U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x0e836fc7U, 0x884c03cfU, 0x77ffdf45U, 0x4db53950U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0xe5becc29U, 0x9802628eU, 0xae42ccabU, 0xd07c1c64U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x29b7a504U, 0xc94a398dU, 0x66872d1bU, 0x8601d289U);
    }
    HW_SCE_p_func100(0x0b00de3dU, 0x621ec070U, 0xab514fd4U, 0x37132da0U);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcc64659cU, 0x8f163d4aU, 0x02a5e2a5U, 0x5b33e3c2U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(952);
    HW_SCE_p_func100(0x5ca187ebU, 0x6d8317b9U, 0x3a029136U, 0x64db1852U);
    HW_SCE_p_func314(952+64);
    HW_SCE_p_func100(0xe3b6589cU, 0xab1e9255U, 0x276afe4cU, 0x0aabeb6fU);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_ECH = 0x00003b9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x3000db68U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37aU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func312(748);
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000093U;
    HW_SCE_p_func101(0x297b5087U, 0xb154b2a1U, 0x00f202ecU, 0x33047f78U);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0x86e1c646U, 0x99aeac35U, 0x85f6aae8U, 0x98139038U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(884);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0xd506cd07U, 0xc57d0308U, 0x73a273d2U, 0x115959dfU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190U);
        HW_SCE_p_func101(0xe51785d3U, 0x16e71b98U, 0x2b674987U, 0xecd2eb45U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0xec1d90edU, 0xafea5063U, 0x4014965aU, 0xc4644ea5U);
    }
    HW_SCE_p_func100(0x8212523fU, 0x83dc322dU, 0x9e84585dU, 0xf22dd763U);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d370U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d770U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcfb1c7c9U, 0xb6df7dcdU, 0x49ba0092U, 0x5d22b17dU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(884);
    HW_SCE_p_func100(0x1de4b4b9U, 0xab0b62a0U, 0x23a8f5e1U, 0x3cf5363eU);
    HW_SCE_p_func314(884+64);
    HW_SCE_p_func100(0xd2cfce67U, 0xfb8ed3a2U, 0x08f387faU, 0xda42e922U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x6d365454U, 0x4239bc0bU, 0x853c3d8dU, 0x207b1244U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0x3945b5a2U, 0x4da29a16U, 0x105b508eU, 0xac563ff4U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x964d6119U, 0x7782c2d7U, 0x7e79dd33U, 0xce9d6cd1U);
    }
    HW_SCE_p_func100(0xeb4eea4aU, 0xadad34cfU, 0x6f717270U, 0xc9e241eeU);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xdf42a902U, 0x8d143a96U, 0x81d9c449U, 0x99d9b6a3U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x5f571992U, 0x76ecf695U, 0xf56636dfU, 0x4d8743e8U);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x58beab10U, 0x244d3763U, 0x6eea2fb4U, 0x309d7802U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c90cfU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(952);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x3800db71U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x933c9b61U, 0x0b68a76bU, 0xf68bd356U, 0x641ef71fU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0xf6014c4cU, 0x8056f7b7U, 0x72b2ba3aU, 0xa19a3635U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x1764ff9fU, 0x1a8492b3U, 0xc49a1d32U, 0x2dc11287U);
    }
    HW_SCE_p_func100(0xad074cdcU, 0xea7ae448U, 0x7324e020U, 0xd3129bcbU);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d371U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d771U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000014U;
    SCE->REG_ECH = 0x00003b9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_ECH = 0x3000db71U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37aU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000581U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func312(680);
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000094U;
    HW_SCE_p_func101(0x51e65f45U, 0x2cdb1de0U, 0xf57eea4aU, 0x2c370be4U);
    HW_SCE_p_func304_r1();
    HW_SCE_p_func100(0x725794c2U, 0x871ac300U, 0xac83aff0U, 0xf400d18dU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x0000d0d0U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0xc31cbbd1U, 0x268d2b25U, 0xe7a62786U, 0x27e369bcU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0x4ca8e691U, 0xd83998faU, 0x26c5f9f2U, 0xe71b8a45U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0xf54c3628U, 0x49f01760U, 0xcd33d93dU, 0xfeedfa57U);
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x239e8ef4U, 0x45342004U, 0x4cd0d273U, 0x246ec09dU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190U);
        HW_SCE_p_func101(0x73401201U, 0xa84dc3b4U, 0x54435447U, 0x3f45b6bdU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x69bf6174U, 0xbd2a73a4U, 0x831c564bU, 0xc86a28cfU);
    }
    HW_SCE_p_func100(0xcece2e3dU, 0x451a005bU, 0x84c56b5eU, 0x0934d294U);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x14512db2U, 0x44a5245aU, 0x46a63ddaU, 0xe66d64d7U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(816);
    HW_SCE_p_func100(0x8e38417cU, 0x84dd6705U, 0x34259ec4U, 0xad64a68dU);
    HW_SCE_p_func314(816+64);
    HW_SCE_p_func100(0x2f4e25f7U, 0x508e0b9aU, 0x9d404c48U, 0x813169cdU);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_ECH = 0x00003b9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x3000db68U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77aU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37aU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003f9eU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func312(748);
    SCE->REG_ECH = 0x0000d77bU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000095U;
    HW_SCE_p_func101(0x882fccf7U, 0xa9db782bU, 0x0cb6d375U, 0x49f70d6dU);
    HW_SCE_p_func308();
    HW_SCE_p_func100(0x023d5574U, 0xd6d309ffU, 0x25ba5b5eU, 0x580371f1U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
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
    SCE->REG_100H = change_endian_long(0x010b238bU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(816);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x7455c717U, 0x6006723aU, 0x42eb0f2dU, 0x9b272b9dU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0xa1bc46c7U, 0x07125db3U, 0xa32ee9a0U, 0x47f7555cU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0xc879e5dcU, 0x17888d82U, 0x5f5c4d9bU, 0xc82298aeU);
    }
    HW_SCE_p_func100(0x0d5b76d6U, 0xb70cd2cfU, 0x3b074b32U, 0xb6516a0fU);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x8181001eU;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000090U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d366U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d766U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f0b809U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func312(884);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x3800db70U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x5dfa8bb0U, 0xf9addc81U, 0x8a267091U, 0x100b0e96U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000110U);
        HW_SCE_p_func101(0x97d49d5cU, 0xb0f0efeaU, 0xeee5ba07U, 0x48ea7fe7U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x77cef942U, 0x2ac856acU, 0x6ee1e859U, 0x95e98234U);
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_ECH = 0x3800db72U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x0b686405U, 0x878db4bbU, 0xd8c40795U, 0xfe6a6eb6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190U);
        HW_SCE_p_func101(0xdb27deefU, 0xd2f2fcedU, 0x462b8a78U, 0x7eabc0c4U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x99186c2fU, 0xd463674bU, 0xa9b83865U, 0xedc5f09dU);
    }
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001991U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001191U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000000cU;
    SCE->REG_ECH = 0x3800db66U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x7c788bcaU, 0xa3bb3c75U, 0xb469bc2fU, 0x85b3a642U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00870001U;
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x04000591U;
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
        SCE->REG_28H = 0x00870001U;
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x800011c0U;
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
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x00000030U;
        SCE->REG_E0H = 0x8088001eU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000024U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x0000000cU;
        SCE->REG_ECH = 0x00003b9eU;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x0000004cU;
        SCE->REG_ECH = 0x00003f9eU;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x00000030U;
        SCE->REG_E0H = 0x8188001eU;
        SCE->REG_00H = 0x00003823U;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_28H = 0x00800001U;
        SCE->REG_104H = 0x00000257U;
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001U);
        SCE->REG_2CH = 0x00000190U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xFFFFFFFFU);
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x775d82a9U, 0x6e093bcdU, 0xaee304d3U, 0xd1452d0bU);
    }
    else
    {
        SCE->REG_24H = 0x000001c0U;
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
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000014U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000001c0U;
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
        SCE->REG_28H = 0x00bf0001U;
        HW_SCE_p_func101(0x68e145aeU, 0xf73293aaU, 0x898193e4U, 0x8bab27edU);
    }
    HW_SCE_p_func100(0x5ec7873dU, 0x6d0dd9e3U, 0xeef645ecU, 0xc612a596U);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
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
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
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
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d37eU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000020U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
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
    SCE->REG_100H = change_endian_long(0x01b9d3a9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb9165f89U, 0xf87676caU, 0x3bc818f5U, 0x726d1a94U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func312(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012dc3c7U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func312(748);
    SCE->REG_ECH = 0x3800db7eU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x084f91efU, 0xd3cb359bU, 0x5514cb43U, 0xeb853283U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000000a0U;
        SCE->REG_E0H = 0x80c0001eU;
        SCE->REG_00H = 0x00018303U;
        SCE->REG_2CH = 0x00000022U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000049c1U;
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
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        SCE->REG_24H = 0x000049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x000000a0U;
        SCE->REG_E0H = 0x81c0001eU;
        SCE->REG_00H = 0x00013803U;
        SCE->REG_2CH = 0x00000012U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            HW_SCE_p_func100(0x053fe767U, 0x7e88b106U, 0x364f0755U, 0x687c7376U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
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
                SCE->REG_24H = 0x06001181U;
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
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x80c0001eU;
                SCE->REG_00H = 0x00018303U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x000000a0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_28H = 0x00800001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_104H = 0x00000157U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000001U);
                SCE->REG_E0H = 0x8181001eU;
                SCE->REG_00H = 0x00003807U;
                SCE->REG_2CH = 0x00000110U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_24H = 0x000001c0U;
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
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001181U;
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
                SCE->REG_E0H = 0x8081001eU;
                SCE->REG_00H = 0x00008307U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_1CH = 0x00210000U;
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000090U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x81c0001eU;
                SCE->REG_00H = 0x00013803U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func101(0xfe9804e6U, 0x12645ab9U, 0xdae649f1U, 0x0ec657c8U);
            }
            else
            {
                HW_SCE_p_func101(0x9e0b8c35U, 0xdd07524aU, 0x03cc62faU, 0x826984e6U);
                oLoop1 = 0;
            }
        }
        HW_SCE_p_func101(0x1f5625b7U, 0xda5863eeU, 0x88bfd0b1U, 0x9cba4d84U);
    }
    else
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x80c0001eU;
            SCE->REG_00H = 0x00018303U;
            SCE->REG_2CH = 0x00000022U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
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
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x81c0001eU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000012U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x80c0001eU;
            SCE->REG_00H = 0x00018303U;
            SCE->REG_2CH = 0x00000022U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x06001191U;
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
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x81c0001eU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000012U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x80c0001eU;
            SCE->REG_00H = 0x00018303U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000050U;
            SCE->REG_E0H = 0x8088001eU;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x00000020U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000070U;
            SCE->REG_E0H = 0x8088001eU;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x000000a0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_28H = 0x00800001U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000020U;
            SCE->REG_E0H = 0x8181001eU;
            SCE->REG_00H = 0x00003807U;
            SCE->REG_2CH = 0x00000090U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_24H = 0x000001c0U;
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
            SCE->REG_34H = 0x00000004U;
            SCE->REG_24H = 0x800011c0U;
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
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_1CH = 0x00210000U;
            SCE->REG_28H = 0x00870001U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000050U;
            SCE->REG_E0H = 0x8188001eU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x00000070U;
            SCE->REG_E0H = 0x8188001eU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000090U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x000000a0U;
            SCE->REG_E0H = 0x81c0001eU;
            SCE->REG_00H = 0x00013803U;
            SCE->REG_2CH = 0x00000010U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func100(0xa5d602dcU, 0x83ac45edU, 0x9d872697U, 0x8b1a9561U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func101(0xcad68de3U, 0xaf4e1f11U, 0x82c8a327U, 0x940029c3U);
                oLoop1 = 0;
            }
            else
            {
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
                SCE->REG_24H = 0x06001191U;
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
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x80c0001eU;
                SCE->REG_00H = 0x00018303U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8088001eU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x000000a0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_28H = 0x00800001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_104H = 0x00000157U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000001U);
                SCE->REG_E0H = 0x8181001eU;
                SCE->REG_00H = 0x00003807U;
                SCE->REG_2CH = 0x00000110U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_2CH = 0x00000050U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_24H = 0x000001c0U;
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
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001191U;
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
                SCE->REG_E0H = 0x8081001eU;
                SCE->REG_00H = 0x00008307U;
                SCE->REG_2CH = 0x00000020U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_28H = 0x00870001U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000050U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000070U;
                SCE->REG_E0H = 0x8188001eU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000090U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x000000a0U;
                SCE->REG_E0H = 0x81c0001eU;
                SCE->REG_00H = 0x00013803U;
                SCE->REG_2CH = 0x00000010U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func101(0xe24acd49U, 0x60443dd8U, 0x248474a6U, 0x58cab95eU);
            }
        }
        HW_SCE_p_func101(0xdd2a0b5cU, 0x766c6608U, 0xe17bc4d7U, 0xa3f93441U);
    }
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
    SCE->REG_ECH = 0x00000028U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCEp_func309_r1.prc
***********************************************************************************************************************/
