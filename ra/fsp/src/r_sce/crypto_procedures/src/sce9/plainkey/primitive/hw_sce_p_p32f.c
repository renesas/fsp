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

fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_DataALen, const uint32_t *InData_DataT, const uint32_t *InData_DataTLen, uint32_t *OutData_Text)
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
    SCE->REG_ECH = 0x000035c8U;
    SCE->REG_104H = 0x00000168U;
    SCE->REG_E0H = 0x80020100U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[0];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[1];
    SCE->REG_ECH = 0x3420a9c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xb41d1f9eU, 0xe710bdb5U, 0xacaee47dU, 0xefa843beU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b580U;
        SCE->REG_ECH = 0x0000007FU;
        SCE->REG_ECH = 0x0000b5a0U;
        SCE->REG_ECH = 0xFFFFFF00U;
        SCE->REG_ECH = 0x0c0029a9U;
        SCE->REG_ECH = 0x04a02988U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func101(0xea31b4e7U, 0xdda25e33U, 0xc9fca5d6U, 0xd502596bU);
    }
    else
    {
        SCE->REG_ECH = 0x0000b580U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_ECH = 0x0000b5a0U;
        SCE->REG_ECH = 0x00020800U;
        SCE->REG_ECH = 0x0c0029a9U;
        SCE->REG_ECH = 0x04a02988U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func101(0x60e816a5U, 0xc35c8141U, 0xd34d1aebU, 0x1529b668U);
    }
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010140U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_DataTLen[0];
    SCE->REG_ECH = 0x38008940U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_ECH = 0x0000b7e0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x34202beaU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x69b6f2edU, 0xcc90f830U, 0xe9ba1093U, 0x7e674d71U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x5f413bf4U, 0x582ef8e3U, 0x45724ad0U, 0xd56e3a4dU);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_ECH = 0x00003409U;
        SCE->REG_ECH = 0x00036800U;
        SCE->REG_ECH = 0x08008c00U;
        SCE->REG_ECH = 0x0000000fU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func100(0x7b94995cU, 0xc775d50fU, 0x888e5dbfU, 0x76c1768fU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00000885U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_D0H = 0x00000020U;
            SCE->REG_C4H = 0x000087b5U;
            SCE->REG_00H = 0x00007113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_E0H = 0x80840001U;
            SCE->REG_00H = 0x00008213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00000bffU;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
            {
                SCE->REG_ECH = 0x3c002be0U;
                SCE->REG_ECH = 0x12003c3fU;
                SCE->REG_ECH = 0x00002fe0U;
            }
            HW_SCE_p_func100(0x76d42054U, 0x09f07003U, 0x4d85d74aU, 0xb09e3f91U);
            SCE->REG_C4H = 0x00000885U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_E0H = 0x81840001U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_04H = 0x00000213U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[0] = SCE->REG_100H;
            OutData_Text[1] = SCE->REG_100H;
            OutData_Text[2] = SCE->REG_100H;
            OutData_Text[3] = SCE->REG_100H;
            HW_SCE_p_func101(0x24faa837U, 0x86969c93U, 0x23100a1eU, 0x5881af9dU);
        }
        SCE->REG_104H = 0x00000164U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_DataALen[0];
        SCE->REG_100H = InData_DataALen[1];
        SCE->REG_E0H = 0x81020100U;
        SCE->REG_00H = 0x0000580bU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_74H_b.B18)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001600U;
        SCE->REG_74H = 0x00000000U;
        SCE->REG_C4H = 0x00040805U;
        SCE->REG_E0H = 0x81040080U;
        SCE->REG_00H = 0x00002813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_D0H = 0x00000020U;
        SCE->REG_C4H = 0x000087b5U;
        SCE->REG_00H = 0x00002513U;
        SCE->REG_74H = 0x00000008U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x00000821U;
        SCE->REG_E0H = 0x80840001U;
        SCE->REG_00H = 0x00008213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x00000bffU;
        for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
        {
            SCE->REG_ECH = 0x3c002beaU;
            SCE->REG_ECH = 0x12003c3fU;
            SCE->REG_ECH = 0x00002fe0U;
        }
        SCE->REG_104H = 0x00000362U;
        SCE->REG_C4H = 0x00050805U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_DataT[0];
        SCE->REG_100H = InData_DataT[1];
        SCE->REG_100H = InData_DataT[2];
        SCE->REG_100H = InData_DataT[3];
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_ECH = 0x00000821U;
        SCE->REG_E0H = 0x81840001U;
        SCE->REG_00H = 0x00002813U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_C4H = 0x00000000U;
        HW_SCE_p_func100(0x6592194cU, 0xfc26b76bU, 0x7a3e8c6dU, 0x747aab38U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x62f497e1U, 0xa35385d7U, 0xee460e14U, 0x9a5ffc83U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            HW_SCE_p_func102(0xb938f129U, 0x3612350eU, 0xfe790d4eU, 0x43169997U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p32f_r2.prc
***********************************************************************************************************************/
