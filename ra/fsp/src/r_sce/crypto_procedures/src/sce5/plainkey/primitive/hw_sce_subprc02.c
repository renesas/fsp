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

void HW_SCE_SelfCheck2SubSub(void)
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
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x40083a8cU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x63a83a19U);
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x00010804U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_ECH = 0x00000800U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x80880000U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_00H = 0x00008023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b460U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00400003U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_A4H = 0xc0200c1eU;
    for(iLoop=0; iLoop<1024; iLoop=iLoop+1)
    {
        SCE->REG_E0H = 0x80010020U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_00H = 0x00008407U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000034c1U;
        SCE->REG_1D0H = 0x00000000U;
        for(jLoop=0; jLoop<32; jLoop=jLoop+1)
        {
            SCE->REG_ECH = 0x0c016cc6U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x100008c7U;
            SCE->REG_1D0H = 0x00000000U;
        }
        SCE->REG_E0H = 0x810100c0U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_00H = 0x00001807U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        for(jLoop=0; jLoop<8; jLoop=jLoop+1)
        {
            SCE->REG_ECH = 0x00003441U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x00008c40U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x0000000fU;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x00000800U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x00000884U;
            SCE->REG_1D0H = 0x00000000U;
            for(kLoop=0; kLoop<16; kLoop=kLoop+1)
            {
                SCE->REG_ECH = 0x010038a0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x38000844U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x10002ca0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x01003ca0U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00002403U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00002c80U;
                SCE->REG_1D0H = 0x00000000U;
            }
            SCE->REG_ECH = 0x00046821U;
            SCE->REG_1D0H = 0x00000000U;
        }
    }
    /* WAIT_LOOP */
    while (0U != SCE->REG_A8H_b.B6)
    {
        /* waiting */
    }
    SCE->REG_A4H = 0x00000000U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_1CH = 0x00000400U;
    SCE->REG_ECH = 0x00000821U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000B50U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000800U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000863U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x000008c6U;
    SCE->REG_1D0H = 0x00000000U;
    for(iLoop=0; iLoop<16; iLoop=iLoop+1)
    {
        SCE->REG_ECH = 0x010038a0U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x30002885U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00070020U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00005023U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x000024c5U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000a400U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000002U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00002c60U;
        SCE->REG_1D0H = 0x00000000U;
    }
    SCE->REG_ECH = 0x380088c0U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00002000U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x38008820U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_subprc02.prc
***********************************************************************************************************************/
