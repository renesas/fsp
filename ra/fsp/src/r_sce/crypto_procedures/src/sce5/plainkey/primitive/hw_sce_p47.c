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

fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_DataALen, const uint32_t *InData_DataT, const uint32_t *InData_DataTLen, uint32_t *OutData_Text)
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
    HW_SCE_func001(0x0541cb7cU, 0x602ed641U, 0x9623725aU, 0x69334525U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_1CH = 0x002d0000U;
        HW_SCE_func001(0x46fb9bb4U, 0xf24287b1U, 0x611bf16fU, 0xe4cad300U);
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
            HW_SCE_func002(0x15ca5f3dU, 0x8c6e9a06U, 0x2ce282c2U, 0x527884efU);
        }
        else
        {
            HW_SCE_func002(0xd6ffdfd0U, 0x9a68e15bU, 0x4bc38c0fU, 0xf2d17922U);
        }
        HW_SCE_func003(0xc963406eU, 0x0a254c37U, 0x9cab8cdcU, 0x647f95d6U);
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
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_104H = 0x00000168U;
        SCE->REG_E0H = 0x80820001U;
        SCE->REG_1D0H = 0x00000000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_TextLen[0];
        SCE->REG_1D0H = 0x00000000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_TextLen[1];
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000b440U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00003822U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000a440U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00003802U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000b440U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000007FU;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0000b460U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0xFFFFFF00U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x0c002860U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x04a02841U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010040U;
        SCE->REG_1D0H = 0x00000000U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_DataTLen[0];
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x38008840U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_ECH = 0x0000b460U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_ECH = 0x34202862U;
        SCE->REG_1D0H = 0x00000000U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_func001(0xd56502c5U, 0x8dedc70aU, 0x43737485U, 0x620b3250U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func003(0x7b44fedaU, 0x18946a25U, 0xee56a374U, 0x226fe029U);
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
            SCE->REG_ECH = 0x00036800U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x08008c00U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x0000000fU;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            HW_SCE_func001(0x24a2919dU, 0x56bba70bU, 0x405ae47fU, 0x754cb155U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func001(0xc5bbd165U, 0x4f251a62U, 0x98088995U, 0x756e5341U);
                SCE->REG_B0H = 0x40000020U;
                SCE->REG_104H = 0x00000365U;
                SCE->REG_A4H = 0x000086bdU;
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
                HW_SCE_func002(0xf0b780b1U, 0xfbcebcf6U, 0xb9bb1883U, 0x22748e54U);
            }
            SCE->REG_104H = 0x00000164U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_DataALen[0];
            SCE->REG_100H = InData_DataALen[1];
            SCE->REG_ECH = 0x0000b420U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_ECH = 0x00000010U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x81820001U;
            SCE->REG_1D0H = 0x00000000U;
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
            SCE->REG_A4H = 0x00040805U;
            SCE->REG_E0H = 0x81040080U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00001813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_B0H = 0x40000020U;
            SCE->REG_A4H = 0x000086bdU;
            SCE->REG_00H = 0x00001513U;
            SCE->REG_74H = 0x00000008U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
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
                SCE->REG_ECH = 0x3c002862U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x12003c23U;
                SCE->REG_1D0H = 0x00000000U;
                SCE->REG_ECH = 0x00002c60U;
                SCE->REG_1D0H = 0x00000000U;
            }
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x00050805U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_DataT[0];
            SCE->REG_100H = InData_DataT[1];
            SCE->REG_100H = InData_DataT[2];
            SCE->REG_100H = InData_DataT[3];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_ECH = 0x00000821U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_E0H = 0x81840001U;
            SCE->REG_1D0H = 0x00000000U;
            SCE->REG_00H = 0x00001813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_A4H = 0x00000000U;
            SCE->REG_1D0H = 0x00000000U;
            HW_SCE_func001(0xbd7d54bcU, 0x1fe8fc2aU, 0x3fd628bdU, 0xc24ed7f7U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func003(0x53d5e107U, 0xe5c7ca0aU, 0xeb52af17U, 0xb3df007eU);
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
                HW_SCE_func003(0xa37a7191U, 0x3959cfc9U, 0x8cf58b51U, 0x7f541d46U);
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
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE_Sec_200408/200408/RA4M1/Cryptographic/HW_SCE_p47.prc
***********************************************************************************************************************/
