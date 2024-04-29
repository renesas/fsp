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

fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_MAC)
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
    HW_SCE_func001(0xe33fc47bU, 0x30fd9834U, 0x07a46aebU, 0x1b3e4bfeU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0xca49a938U, 0xdd98fe7eU, 0xf755568eU, 0x7f5c6088U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_00H = 0x00000113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func002(0xae59daf8U, 0x357657b3U, 0x783de32dU, 0x5a14c65bU);
        }
        else
        {
            HW_SCE_func002(0xa564cd90U, 0x63af148bU, 0x4bf414bdU, 0x50eb4925U);
        }
        HW_SCE_func003(0x2aaf06ddU, 0xec87a067U, 0x4d7e15ffU, 0x901854fcU);
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
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010000U;
        SCE->REG_1D0H = 0x00000000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_TextLen[0];
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00008c00U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000000fU;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x38008800U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func001(0xf9db203fU, 0xf5fb0808U, 0x93af0526U, 0x211add2fU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func001(0x6a5e5b39U, 0x79427bd5U, 0xb1c833c6U, 0xe72e9266U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00e086bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x80840001U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00008113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x00000863U;
            SCE->REG_1D0H = 0x00000000U;
            for (iLoop = 0; iLoop < 16; iLoop = iLoop+1)
            {
                SCE->REG_ECH = 0x3c002860U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x12003c23U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00002c60U;
                SCE->REG_1D0H = 0x00000000U;
            }
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x81840001U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_04H = 0x00000612U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[0] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[1] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[2] = SCE->REG_100H;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_Text[3] = SCE->REG_100H;
            HW_SCE_func002(0x173944a8U, 0x0e7bafd8U, 0x19114cb7U, 0xe75b3f8cU);
        }
        else
        {
            HW_SCE_func002(0xe72ebe74U, 0xaf093eddU, 0xe8f8b697U, 0xf6d4191fU);
        }
        HW_SCE_func001(0x66a54a33U, 0x2ebea6baU, 0x04519495U, 0x3ae3bc45U);
        SCE->REG_104H = 0x00000051U;
        SCE->REG_A4H = 0x01000e84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_B0H = 0x40000000U;
        SCE->REG_A4H = 0x000089cdU;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000112U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        OutData_MAC[0] = SCE->REG_100H;
        OutData_MAC[1] = SCE->REG_100H;
        OutData_MAC[2] = SCE->REG_100H;
        OutData_MAC[3] = SCE->REG_100H;
        HW_SCE_func003(0x15387217U, 0x8afab3beU, 0x2cca8763U, 0x51327d35U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_SUCCESS;
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p78.prc
***********************************************************************************************************************/
