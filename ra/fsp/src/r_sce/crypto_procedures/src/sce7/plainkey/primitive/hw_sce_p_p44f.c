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

fsp_err_t HW_SCE_Aes256CmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_Text, uint32_t *InData_DataT, uint32_t *InData_DataTLen, uint32_t *OutData_DataT)
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
    HW_SCE_p_func100(0xb060c2f8U, 0xdbcb01b0U, 0x42d1ed81U, 0x1ec8fcdfU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xde4fd58aU, 0x1d440d06U, 0x9dfbd34aU, 0x3205bb06U);
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
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            SCE->REG_104H = 0x00000051U;
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00408a84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_p_func101(0x53e25420U, 0x62bb6a2aU, 0xcaef5387U, 0x59eca0b3U);
        }
        else
        {
            SCE->REG_104H = 0x00000051U;
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00508a84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            HW_SCE_p_func101(0x4c8fb73cU, 0x95614b30U, 0x206dd170U, 0xd0c1f9b3U);
        }
        SCE->REG_A4H = 0x00040c05U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
        {
            HW_SCE_p_func100(0xe83564adU, 0xe80f1523U, 0xf4646700U, 0xa9a0af1cU);
            SCE->REG_104H = 0x00000361U;
            SCE->REG_B0H = 0x40000000U;
            SCE->REG_A4H = 0x00008e95U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_Text[0];
            SCE->REG_100H = InData_Text[1];
            SCE->REG_100H = InData_Text[2];
            SCE->REG_100H = InData_Text[3];
            SCE->REG_04H = 0x00000112U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_DataT[0] = SCE->REG_100H;
            OutData_DataT[1] = SCE->REG_100H;
            OutData_DataT[2] = SCE->REG_100H;
            OutData_DataT[3] = SCE->REG_100H;
            HW_SCE_p_func102(0x3ba2c38aU, 0x1a0d8a8aU, 0x719eeaf4U, 0x3b9e14f4U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
        else
        {
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x80010040U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_DataTLen[0];
            SCE->REG_ECH = 0x3420a840U;
            SCE->REG_ECH = 0x00000010U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x0000b460U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_ECH = 0x34202862U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x90a35862U, 0x922f2c16U, 0x13e5b621U, 0x5baf11faU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x42256946U, 0xb9eb52f1U, 0x7c111d83U, 0x248d2f49U);
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
                SCE->REG_104H = 0x00000361U;
                SCE->REG_B0H = 0x40000000U;
                SCE->REG_A4H = 0x00008e95U;
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
                SCE->REG_E0H = 0x80840001U;
                SCE->REG_00H = 0x00008113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x000034e2U;
                SCE->REG_ECH = 0x000568e7U;
                SCE->REG_ECH = 0x00026ce7U;
                SCE->REG_ECH = 0x00003827U;
                SCE->REG_ECH = 0x0000b4c0U;
                SCE->REG_ECH = 0x00000020U;
                SCE->REG_ECH = 0x00003402U;
                SCE->REG_ECH = 0x00008c00U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x000028c0U;
                SCE->REG_ECH = 0x00008cc0U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x00004406U;
                SCE->REG_ECH = 0x00007421U;
                SCE->REG_ECH = 0x00007821U;
                SCE->REG_ECH = 0x00003c27U;
                SCE->REG_ECH = 0x000034c2U;
                SCE->REG_ECH = 0x0000a4c0U;
                SCE->REG_ECH = 0x0000001fU;
                SCE->REG_ECH = 0x000568c6U;
                SCE->REG_ECH = 0x000034e6U;
                SCE->REG_ECH = 0x00026ce7U;
                SCE->REG_ECH = 0x00000821U;
                for (iLoop = 0; iLoop < 4; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3420a8e0U;
                    SCE->REG_ECH = 0x0000000dU;
                    SCE->REG_ECH = 0x10003c27U;
                    SCE->REG_ECH = 0x1000a4e0U;
                    SCE->REG_ECH = 0x00000004U;
                }
                SCE->REG_A4H = 0x00040805U;
                SCE->REG_E0H = 0x81840001U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00900c05U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_DataT[0];
                SCE->REG_100H = InData_DataT[1];
                SCE->REG_100H = InData_DataT[2];
                SCE->REG_100H = InData_DataT[3];
                HW_SCE_p_func100(0xb4fbfc90U, 0x792ea3fdU, 0x15bf2b4bU, 0xabd75113U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x3a920974U, 0x464a37ffU, 0x1c0f3aefU, 0x15a1f102U);
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
                    HW_SCE_p_func102(0x4d5245f4U, 0x60f91572U, 0x0233abf5U, 0xcc1654b2U);
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
}

/***********************************************************************************************************************
End of function ./input_dir/HW_SCE/HW_SCEp/HW_SCEp_p44f.prc
***********************************************************************************************************************/
