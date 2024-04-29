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

void HW_SCE_p_func324(void)
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
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003fbeU;
    HW_SCE_p_func100(0xba800165U, 0x9d0773f6U, 0xc404520bU, 0x64890201U);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000005c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000060c1U;
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
    SCE->REG_100H = change_endian_long(0x019410dfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xd5fc2c48U, 0x3ee36e03U, 0x5d0a4911U, 0x3a0bf64dU);
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
    HW_SCE_p_func100(0x8b104378U, 0x5c4821e6U, 0xd5ad0910U, 0x350a2659U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    HW_SCE_p_func320(716);
    SCE->REG_24H = 0x0000a0c1U;
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
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(752);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_24H = 0x060049c1U;
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
    SCE->REG_1CH = 0x00210000U;
    oLoop1 = 1;
    while(oLoop1 == 1)
    {
        HW_SCE_p_func100(0xf53e35c6U, 0xd82158c6U, 0xb88968fcU, 0xc7b36f20U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func101(0x905bfec7U, 0x34f45708U, 0x8a2c63ffU, 0x0f52cc31U);
            oLoop1 = 0;
        }
        else
        {
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
            SCE->REG_24H = 0x060049c1U;
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
            SCE->REG_1CH = 0x00210000U;
            HW_SCE_p_func101(0x6fd622f4U, 0xc5c30bdbU, 0x97754975U, 0xabab04e2U);
        }
    }
    HW_SCE_p_func100(0x21bbb393U, 0xcd9f14a3U, 0x26a0865fU, 0x7ab63a5fU);
    SCE->REG_24H = 0x000049c1U;
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
    SCE->REG_24H = 0x060049c1U;
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
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef2f1cU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xfc6ff514U, 0xa79a0df4U, 0x7e3fac51U, 0x4283d461U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(136);
    HW_SCE_p_func100(0x94f25a99U, 0xdcf9f94bU, 0xcc235501U, 0x569b42ddU);
    HW_SCE_p_func314(136+32);
    HW_SCE_p_func100(0xc3c50340U, 0x1fed1a99U, 0xc269950cU, 0xe7766b8eU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x012e06e6U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8cebb57cU, 0x04b0382fU, 0x60452136U, 0xde3445a7U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(172);
    HW_SCE_p_func100(0xf53e25d8U, 0x61d4a5ceU, 0xd3c4952aU, 0x9acca047U);
    HW_SCE_p_func314(172+32);
    HW_SCE_p_func100(0xb8a00ca9U, 0x28cfa0d8U, 0x81dd7ba0U, 0xa28e4d9fU);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000049c1U;
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
    SCE->REG_100H = change_endian_long(0x0100abe1U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6f9aab8fU, 0xabe2fdc1U, 0xd809f527U, 0x5f0cfc44U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(208);
    HW_SCE_p_func100(0x85986bc9U, 0xdfec6f9fU, 0xd0187c6dU, 0x35b96576U);
    HW_SCE_p_func314(208+32);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000a52U;
    for (iLoop = 0; iLoop < 128; iLoop = iLoop + 1)
    {
        HW_SCE_p_func100(0x676328e0U, 0x613dcc15U, 0xb5174525U, 0x35e75a6fU);
        SCE->REG_24H = 0x040049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000149U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x060049c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0400d0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02000149U;
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
        SCE->REG_100H = change_endian_long(0x019410dfU);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x23195e77U, 0x97f9f9e3U, 0x3a294c80U, 0x21a31b5fU);
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
        SCE->REG_00H = 0x00003283U;
        SCE->REG_2CH = 0x00000015U;
        HW_SCE_p_func320(716);
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_ECH = 0x00002e40U;
        HW_SCE_p_func101(0xe6f2fb13U, 0x44ac6782U, 0xacacfa2cU, 0xc6ce06baU);
    }
    SCE->REG_ECH = 0x38008a40U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    HW_SCE_p_func100(0xdff19989U, 0xed86b6e4U, 0x810692d1U, 0x4054ba1fU);
    SCE->REG_24H = 0x040049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x040019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x060049c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0400d0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x020019a1U;
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
    SCE->REG_100H = change_endian_long(0x019410dfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb252e8f6U, 0xa305ef14U, 0xae64b69aU, 0x585821f5U);
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
    HW_SCE_p_func100(0xe3ac09b8U, 0xed2ade8eU, 0x09e0d6a0U, 0x53c92617U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    HW_SCE_p_func320(716);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4a733c3dU, 0x2b978923U, 0xc70ac96aU, 0xf892a403U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x6a895ce5U, 0x6c42347fU, 0x214cfe83U, 0x59e7049eU);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0xdea06f25U, 0x53d8df33U, 0x9c88cf0eU, 0x67a0090aU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xbf3bc416U, 0x136f6b3eU, 0xacf5f90fU, 0x3425f707U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x1c85df96U, 0x3d70a07dU, 0x430218bcU, 0xb738452dU);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0x4894e0eaU, 0x1ed6fd66U, 0x44c98fa9U, 0x93476849U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x27653520U, 0xaf747027U, 0xdc554257U, 0xf7ab9d4bU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(544);
    HW_SCE_p_func100(0x799b94d4U, 0xc20a7cd7U, 0x9cca7baaU, 0x7cb589a4U);
    HW_SCE_p_func314(544+32);
    HW_SCE_p_func100(0x88fb9181U, 0xb55c73deU, 0x7d7588f0U, 0xf5f0778cU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf3a6d287U, 0xc0bae19aU, 0x4a678488U, 0x782770a3U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(580);
    HW_SCE_p_func100(0x713444a7U, 0xc18c9532U, 0x50c8e298U, 0x48490351U);
    HW_SCE_p_func314(580+32);
    HW_SCE_p_func100(0xc516255bU, 0xc4f1442cU, 0xe9885d55U, 0xb986eeb2U);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000049c1U;
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
    SCE->REG_100H = change_endian_long(0x010964eaU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x54c6a527U, 0x13c8e927U, 0xb44ce6aaU, 0xeb9e9d3fU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0x265120a7U, 0x73fc5c2eU, 0xef24e3f8U, 0x4fbcfaadU);
    HW_SCE_p_func314(480+32);
    HW_SCE_p_func100(0x61f0fe5eU, 0x0f4cbddfU, 0x1ad3a9e8U, 0x1a0d7668U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x7be00fceU, 0x9aeb3edeU, 0x25026ce9U, 0xc2d0db59U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(616);
    HW_SCE_p_func100(0x73a48fa9U, 0x38d334c0U, 0xadf63b4dU, 0xf330a5ccU);
    HW_SCE_p_func314(616+32);
    SCE->REG_ECH = 0x00000a52U;
    for (iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        SCE->REG_ECH = 0x0000b7a0U;
        SCE->REG_ECH = 0x000000f0U;
        HW_SCE_p_func101(0x20fa9c73U, 0xbbf1986dU, 0x9bfb0b9dU, 0x272b4a9eU);
        HW_SCE_p_func318();
        HW_SCE_p_func100(0x91e54cabU, 0xdaa2840bU, 0xe523dc34U, 0x667f6b46U);
        SCE->REG_28H = 0x009f0001U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x011af8f9U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xb669ddffU, 0xc3ef8260U, 0x5350ad91U, 0x9fa7b544U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func319(408);
        HW_SCE_p_func100(0x147c2639U, 0x9cc02970U, 0x583dd0dbU, 0x528abff7U);
        HW_SCE_p_func314(408+32);
        HW_SCE_p_func100(0x1714ce33U, 0x4aad3236U, 0x7b544d55U, 0xd9609333U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x0130aeffU);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x1cd470e5U, 0x633c9ff4U, 0x1cdcb115U, 0x26eda65cU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000023U;
        HW_SCE_p_func319(444);
        HW_SCE_p_func100(0xb9364cc7U, 0xbefc7673U, 0x0e7a2b28U, 0x2ad0bb86U);
        HW_SCE_p_func314(444+32);
        HW_SCE_p_func100(0x51f70bf0U, 0x01fd1d85U, 0x88cd7d7aU, 0xc11c13c1U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x010964eaU);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x859aa5c9U, 0x89c173aeU, 0x7aab7a3eU, 0x4bd05495U);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        HW_SCE_p_func319(480);
        HW_SCE_p_func100(0xa64744e4U, 0xa6a5a5c4U, 0x6f2d5dc6U, 0x2fe1048eU);
        HW_SCE_p_func314(480+32);
        HW_SCE_p_func100(0xfa4d90b8U, 0x0d966024U, 0x19970766U, 0x2c40f92eU);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01574730U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x7f6a3d31U, 0x15656e45U, 0x8350c92bU, 0xa29a076dU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000022U;
        HW_SCE_p_func319(544);
        HW_SCE_p_func100(0xe8a70fe7U, 0x4d8a9e70U, 0x3f48c23aU, 0x89eeb55eU);
        HW_SCE_p_func314(544+32);
        HW_SCE_p_func100(0x5c04f776U, 0x21f0f81fU, 0x4e3a8a5bU, 0x76098a00U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01f11123U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0x472aaf2aU, 0xf9d8f81cU, 0x07508940U, 0xd7a49d5aU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000023U;
        HW_SCE_p_func319(580);
        HW_SCE_p_func100(0x05d64b3fU, 0x793b0085U, 0xa705f245U, 0xe95259deU);
        HW_SCE_p_func314(580+32);
        HW_SCE_p_func100(0xfa3b4138U, 0xbe30de6cU, 0xfc3bd1eaU, 0x2e93d150U);
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01ac62c9U);
        HW_SCE_p_func080();
        HW_SCE_p_func100(0xa6ec6b8cU, 0xaa9fd90bU, 0x46b98ebeU, 0xfbe37dfcU);
        SCE->REG_00H = 0x00002383U;
        SCE->REG_2CH = 0x00000020U;
        HW_SCE_p_func319(616);
        HW_SCE_p_func100(0x0f67fcf6U, 0xd661c9b8U, 0x78b71659U, 0xdc1671e7U);
        HW_SCE_p_func314(616+32);
        SCE->REG_ECH = 0x00002e40U;
        HW_SCE_p_func101(0x61371d76U, 0x8955c0e3U, 0xf57d2ea6U, 0x6b052d94U);
    }
    SCE->REG_ECH = 0x38008a40U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f1U;
    HW_SCE_p_func101(0x8bba8cdbU, 0xa7e18e91U, 0xf71d87c8U, 0x797aa69cU);
    HW_SCE_p_func318();
    HW_SCE_p_func100(0x322547acU, 0x9b5539eeU, 0x631909e9U, 0xa317cbbbU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x1759ee18U, 0x3b01deecU, 0x6a8590f4U, 0xf6c5f969U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x96c47023U, 0x7df6d2ccU, 0xf3632006U, 0x6fe7f4f8U);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0x91a24210U, 0xcbb101b4U, 0xb5ba4705U, 0xfbf14b32U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x2c310da3U, 0x5ea30255U, 0xa29d782eU, 0x0bc1f93eU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x8b87eef7U, 0x213e09a1U, 0xa69cfedbU, 0xfb9276f3U);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0xd41003baU, 0x105fbe5aU, 0x561c8390U, 0x4b945c86U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x48db3531U, 0x94b996bdU, 0x060dbf20U, 0x9520a664U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0xb51fc317U, 0xc794cd92U, 0xb477efbcU, 0x81dce284U);
    HW_SCE_p_func314(480+32);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f2U;
    HW_SCE_p_func101(0xbf232622U, 0x10d13a51U, 0x848c8464U, 0x5f80635dU);
    HW_SCE_p_func318();
    HW_SCE_p_func100(0x30a00026U, 0x69802337U, 0x7cd74e4fU, 0x52041efcU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d34587U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x553d552eU, 0xb04761ecU, 0x3077aef8U, 0x831743f4U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(272);
    HW_SCE_p_func100(0x7432c608U, 0xc9fed9c7U, 0xec726f19U, 0x8d5f8875U);
    HW_SCE_p_func314(272+32);
    HW_SCE_p_func100(0xaace0e99U, 0x42f2e878U, 0xdd957896U, 0xcd0de241U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01315552U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x5c31900bU, 0x2680183dU, 0xe043b5a4U, 0x8db6cf2dU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(308);
    HW_SCE_p_func100(0xcdd8331eU, 0xa782fd53U, 0xc031e37eU, 0xf9541b33U);
    HW_SCE_p_func314(308+32);
    HW_SCE_p_func100(0x36ab5860U, 0x7d1990c3U, 0xd106d439U, 0xd15c9b71U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011a27dfU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6fc441bdU, 0x7bce0d3bU, 0xe350cbc9U, 0x0d856aceU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func319(344);
    HW_SCE_p_func100(0xe4f910e8U, 0x57082666U, 0x3975f343U, 0xeb5a48a4U);
    HW_SCE_p_func314(344+32);
    HW_SCE_p_func100(0x8de19a0bU, 0x8f9aed6fU, 0x47fdf7ecU, 0x62fb4c80U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x26831bc6U, 0xcde42f4fU, 0x8b4d5307U, 0xca3cecfeU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(408);
    HW_SCE_p_func100(0x68d5d8f0U, 0x2d218dd1U, 0xd6eea468U, 0xb35336b8U);
    HW_SCE_p_func314(408+32);
    HW_SCE_p_func100(0x021c7250U, 0x492cdf1fU, 0x3a45037fU, 0xefeca1b5U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x0cb3fc26U, 0xcb04bc14U, 0xb6de0377U, 0x53ba5f3fU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(444);
    HW_SCE_p_func100(0x2e642543U, 0x4902544aU, 0x51f5ebe8U, 0x72794910U);
    HW_SCE_p_func314(444+32);
    HW_SCE_p_func100(0x8f9d782eU, 0x81c16d66U, 0x5e85807eU, 0x6ef1b6d8U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc718fd71U, 0x78b1a7f1U, 0x20b0a1fcU, 0x08efeaa0U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func319(480);
    HW_SCE_p_func100(0x1703905fU, 0x2588568cU, 0x62ecbe40U, 0x232f9133U);
    HW_SCE_p_func314(480+32);
    HW_SCE_p_func100(0x3a1733d4U, 0x86275a46U, 0x6eccc0a1U, 0x33a7dc95U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01fe1091U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x8e52d68bU, 0x1f5c3894U, 0x691f3877U, 0x2243d7a3U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    HW_SCE_p_func320(0);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019969f4U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x29bf281fU, 0x90730ae8U, 0x5c16ffe4U, 0x9746b752U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000013U;
    HW_SCE_p_func320(36);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019de420U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xc6d651f1U, 0xea4e04fbU, 0x1e97b80eU, 0x728f545cU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    HW_SCE_p_func320(72);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x4f8d632aU, 0xfd956a83U, 0x8a13de73U, 0x6dd74cadU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(544);
    HW_SCE_p_func100(0xc1fe21f7U, 0x1494de69U, 0xb4a7584bU, 0x901cd492U);
    HW_SCE_p_func314(544+32);
    HW_SCE_p_func100(0x0e1dc5d7U, 0x2032e656U, 0x84c0fcffU, 0x1b85a4d7U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x085429ddU, 0x35c43703U, 0x5059446fU, 0x997691b1U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(580);
    HW_SCE_p_func100(0x6d916213U, 0xb2da4cceU, 0x367fbab5U, 0x2acea943U);
    HW_SCE_p_func314(580+32);
    HW_SCE_p_func100(0x18057ff5U, 0x754a8c51U, 0x086a4be3U, 0x90067525U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x325a9a89U, 0x535dc5d9U, 0x1f05a791U, 0xcd2f9884U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func319(616);
    HW_SCE_p_func100(0xc75b4b8fU, 0x620e68b0U, 0xbbebe121U, 0xe12fba81U);
    HW_SCE_p_func314(616+32);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f3U;
    HW_SCE_p_func101(0x06aa632cU, 0x2c294586U, 0x524b9262U, 0x937064feU);
    HW_SCE_p_func318();
    HW_SCE_p_func100(0x7ea795a3U, 0x8915f2cbU, 0xa7c41020U, 0x0f89207eU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01fe1091U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x9a6b4727U, 0x19829e58U, 0xb07a6fc7U, 0x1ec71baeU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000022U;
    HW_SCE_p_func319(0);
    HW_SCE_p_func100(0xb85e4c02U, 0x1065c4d4U, 0x565140bcU, 0x9e233683U);
    HW_SCE_p_func314(0+32);
    HW_SCE_p_func100(0x0f6b1778U, 0xbd59c987U, 0x90211bb5U, 0x109bfbf8U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019969f4U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xb356879fU, 0xa9e41716U, 0x28645099U, 0x0bf86938U);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000023U;
    HW_SCE_p_func319(36);
    HW_SCE_p_func100(0xb6a059a7U, 0xb27e1a91U, 0xe6575256U, 0x7d8b8dbcU);
    HW_SCE_p_func314(36+32);
    HW_SCE_p_func100(0xe0209cc9U, 0xc3e5b064U, 0xe233e02bU, 0xb82949e6U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019de420U);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcf7deda8U, 0xb4cb207eU, 0x706bb36cU, 0xd048408eU);
    SCE->REG_00H = 0x00002383U;
    SCE->REG_2CH = 0x00000020U;
    HW_SCE_p_func319(72);
    HW_SCE_p_func100(0x39eb6316U, 0x27f38705U, 0x8667e6f3U, 0xf04bff62U);
    HW_SCE_p_func314(72+32);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func324.prc
***********************************************************************************************************************/
