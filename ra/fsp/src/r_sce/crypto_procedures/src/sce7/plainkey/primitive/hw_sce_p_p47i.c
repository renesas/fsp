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

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub(const uint32_t * InData_KeyType, const uint32_t * InData_Cmd,
                                                     const uint32_t * InData_KeyIndex,
                                                     const uint32_t * InData_IV)
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
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00004701U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_C4H = 0x200e1a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[16+0 + 0];
    SCE->REG_100H = S_RAM[16+0 + 1];
    SCE->REG_100H = S_RAM[16+0 + 2];
    SCE->REG_100H = S_RAM[16+0 + 3];
    SCE->REG_E0H = 0x80020000U;
    SCE->REG_104H = 0x00000168U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38008820U;
    SCE->REG_ECH = 0x00000001U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x3745745fU, 0x9a03daf2U, 0x7b5e13a6U, 0xdf4db3e6U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xd06b7632U, 0x716fb30fU, 0x0635a223U, 0x97840afaU);
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
        SCE->REG_ECH = 0x3000a800U;
        SCE->REG_ECH = 0x00000006U;
        SCE->REG_ECH = 0x00010020U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x00000006U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_ECH = 0x3420a800U;
        SCE->REG_ECH = 0x00000005U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x0afe5b3dU, 0xe567174eU, 0x63a6d156U, 0x720bd433U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x38000c21U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x65252417U, 0x69ca265bU, 0x8949957aU, 0x71345bb9U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x200c3b0dU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[0];
                SCE->REG_100H = InData_KeyIndex[1];
                SCE->REG_100H = InData_KeyIndex[2];
                SCE->REG_100H = InData_KeyIndex[3];
                SCE->REG_A4H = 0x000c0b0cU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x4e2279dbU);
                HW_SCE_p_func101(0xcf4f8bf3U, 0x6cc8c683U, 0x30153e1bU, 0xee591faaU);
            }
            else
            {
                SCE->REG_A4H = 0x000c2b0dU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[0];
                SCE->REG_100H = InData_KeyIndex[1];
                SCE->REG_100H = InData_KeyIndex[2];
                SCE->REG_100H = InData_KeyIndex[3];
                SCE->REG_A4H = 0x000c0b0cU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x2a46c04bU);
                HW_SCE_p_func101(0x6b28a43eU, 0xbfb6b0d8U, 0x418703acU, 0xc1253679U);
            }
            HW_SCE_p_func100(0xe4913fe9U, 0x00eabd22U, 0x30f429c3U, 0xed06bd68U);
            SCE->REG_A4H = 0x02f8073dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[4];
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_A4H = 0x000007bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_100H = InData_KeyIndex[9];
            SCE->REG_100H = InData_KeyIndex[10];
            SCE->REG_100H = InData_KeyIndex[11];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0xd6c4e594U, 0xb5e89a1bU, 0xf8dc052fU, 0xc56ee6caU);
        }
        else
        {
            SCE->REG_104H = 0x00000368U;
            SCE->REG_E0H = 0x80040040U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[0];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[1];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[2];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[3];
            SCE->REG_ECH = 0x00000bdeU;
            SCE->REG_ECH = 0x000037e2U;
            SCE->REG_ECH = 0x00008fe0U;
            SCE->REG_ECH = 0xff000000U;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_ECH = 0x1000d3c0U;
            SCE->REG_ECH = 0x38008800U;
            SCE->REG_ECH = 0x00000005U;
            SCE->REG_ECH = 0x1000b540U;
            SCE->REG_ECH = 0x00000017U;
            SCE->REG_ECH = 0x2000b540U;
            SCE->REG_ECH = 0x00000016U;
            SCE->REG_ECH = 0x3800584aU;
            SCE->REG_ECH = 0x2000d3c1U;
            SCE->REG_ECH = 0x000037e2U;
            SCE->REG_ECH = 0x00008fe0U;
            SCE->REG_ECH = 0x0000fe00U;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_ECH = 0x1000d3c2U;
            SCE->REG_ECH = 0x38008bc0U;
            SCE->REG_ECH = 0x00000007U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_ECH = 0x0000a800U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_C4H = 0x00082b8dU;
            SCE->REG_E0H = 0x81040040U;
            SCE->REG_00H = 0x00002813U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func100(0x3e0f7edaU, 0x27b6e8d6U, 0xbab6354dU, 0x93329713U);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x42f8073dU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[4];
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x400007bdU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_100H = InData_KeyIndex[9];
            SCE->REG_100H = InData_KeyIndex[10];
            SCE->REG_100H = InData_KeyIndex[11];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0x61d251a8U, 0xf3a9b324U, 0x5a3a7b76U, 0x3f5dd92aU);
        }
        HW_SCE_p_func100(0x816add39U, 0xbeb643eeU, 0xfa4db455U, 0xbaabc553U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x59c77048U, 0xf1d0bfaaU, 0xdf48e938U, 0xc7752802U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0xe6805878U, 0xeb9560baU, 0x1aeef205U, 0x090bdb43U);
            SCE->REG_ECH = 0x00007c00U;
            SCE->REG_1CH = 0x00600000U;
            SCE->REG_1D0H = 0x00000000U;
            if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
            {
                HW_SCE_p_func101(0xe75cf77bU, 0xee4c7825U, 0xaed6e263U, 0x20e8bf91U);
            }
            else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
            {
                HW_SCE_p_func101(0x1735ab11U, 0x518bdf93U, 0x79cb1ae7U, 0xd6630025U);
            }
            else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00040805U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_IV[0];
                SCE->REG_100H = InData_IV[1];
                SCE->REG_100H = InData_IV[2];
                SCE->REG_100H = InData_IV[3];
                HW_SCE_p_func101(0xf30b018dU, 0xa9de1b68U, 0x4670b7eeU, 0xd69ef3c0U);
            }
            else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00040805U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_IV[0];
                SCE->REG_100H = InData_IV[1];
                SCE->REG_100H = InData_IV[2];
                SCE->REG_100H = InData_IV[3];
                HW_SCE_p_func101(0x7c101086U, 0x5886f019U, 0x23e86876U, 0x0be495c6U);
            }
            else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00040805U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_IV[0];
                SCE->REG_100H = InData_IV[1];
                SCE->REG_100H = InData_IV[2];
                SCE->REG_100H = InData_IV[3];
                HW_SCE_p_func101(0xbaf5fa54U, 0xdb7f3b3fU, 0x53f27f5aU, 0x649c987dU);
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p47i_r1.prc
***********************************************************************************************************************/
