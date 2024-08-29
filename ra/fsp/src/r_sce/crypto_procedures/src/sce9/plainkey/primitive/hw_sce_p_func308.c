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

void HW_SCE_p_func308(void)
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
    HW_SCE_p_func100(0x8c2d8cf6U, 0x8d56e617U, 0x4e381155U, 0x0522ae21U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000024U;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000b5aU;
    SCE->REG_ECH = 0x0000d77cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x3800db7aU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d37cU;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00002b5dU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x00003b5eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0161d833U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xe9363776U, 0x8ffc645cU, 0x22b826ccU, 0x70a25e76U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func313(1020);
    HW_SCE_p_func100(0x073d446bU, 0xeccd11c7U, 0x5b0e9e5fU, 0x98abb4ccU);
    HW_SCE_p_func314(1020+64);
    HW_SCE_p_func100(0xfbf01920U, 0xb35ecab2U, 0x10236fdfU, 0xa5cebfeaU);
    SCE->REG_ECH = 0x00000b39U;
    SCE->REG_ECH = 0x0000d77dU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x3800db7bU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d37dU;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00002b3dU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x00003b3eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x659d1915U, 0x355d44e1U, 0x0a383dc2U, 0xfc52da53U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func313(1088);
    HW_SCE_p_func100(0xff1123e5U, 0x5c8c6531U, 0x4477a46dU, 0x1d416236U);
    HW_SCE_p_func314(1088+64);
    HW_SCE_p_func100(0xd336b7c0U, 0xc1d5ac1cU, 0x38833731U, 0x970f8d08U);
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
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
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x81010320U;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x81010340U;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x80010300U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x3000db7cU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x00002fc0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x3000db7dU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x00002fc0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x3000dbc0U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37eU;
    SCE->REG_ECH = 0x00000080U;
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
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000058d0U;
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
    SCE->REG_100H = change_endian_long(0x013fd1d7U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func312(1088);
    SCE->REG_ECH = 0x3000db7cU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d76bU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d36bU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x000037daU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000097U;
    HW_SCE_p_func101(0x2d831169U, 0xf3e9c45fU, 0x86a9a7dbU, 0x48bfc00cU);
    HW_SCE_p_func310();
    HW_SCE_p_func100(0x5ba57e89U, 0x2ad0cf5cU, 0xc546cbb0U, 0xdfd6101dU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0161d833U);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    HW_SCE_p_func312(1020);
    SCE->REG_ECH = 0x3000db7dU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d76bU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d36bU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x000037d9U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000098U;
    HW_SCE_p_func101(0xfb0daf22U, 0xfc7f120eU, 0x6e4b02adU, 0x7c564c8aU);
    HW_SCE_p_func310();
    SCE->REG_ECH = 0x3800db7eU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    HW_SCE_p_func100(0x6ce6e688U, 0x1ca60eafU, 0x25c7e486U, 0x73068e9aU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x81010300U;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
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
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x80001191U;
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
        HW_SCE_p_func101(0x2a06ba12U, 0xe8bfbe05U, 0xfc7ae4e6U, 0x2454e45aU);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x81010300U;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
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
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x80001181U;
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
        HW_SCE_p_func101(0xa71d69d5U, 0x3fd3bbc8U, 0xcfd2107aU, 0xc1462c2cU);
    }
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d372U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d772U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000018U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x0000001cU;
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
    SCE->REG_ECH = 0x0000d768U;
    SCE->REG_24H = 0x000088d0U;
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
    SCE->REG_ECH = 0x00000024U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func308.prc
***********************************************************************************************************************/
