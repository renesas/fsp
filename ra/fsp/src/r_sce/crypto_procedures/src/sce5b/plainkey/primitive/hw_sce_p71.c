/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED  AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
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

fsp_err_t HW_SCE_GenerateOemKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_Cmd, uint32_t *InData_SharedKeyIndex,
						uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00007101U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x800100c0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38000cc6U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_func100(0x5f5b68d1U, 0x51871fdcU, 0xdc1f5590U, 0x8f16885bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func049(InData_Cmd);
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(InData_SharedKeyIndex[0]);
        SCE->REG_ECH = 0x3420a880U;
        SCE->REG_ECH = 0x00000005U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_ECH = 0x3420a880U;
        SCE->REG_ECH = 0x0000000aU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        SCE->REG_ECH = 0x38208880U;
        SCE->REG_ECH = 0x00000006U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_ECH = 0x3420a820U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func100(0xa921c356U, 0xecaafca6U, 0x12d1b815U, 0xa1bb745cU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func102(0x1a6b44a0U, 0x97412d03U, 0x8b62e683U, 0x332605fdU);
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
            OFS_ADR = InData_SharedKeyIndex[0] << 3;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800100c0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000071U);
            HW_SCE_func101(0x9017fb90U, 0xa0214933U, 0x64595cf8U, 0x0c3ce11dU);
            HW_SCE_func069(InData_SessionKey,OFS_ADR);
            HW_SCE_func100(0x55562313U, 0xd08bbd10U, 0x905d05a2U, 0xe60c963cU);
            HW_SCE_func103();
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x01000e84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_E0H = 0x80010000U;
            SCE->REG_00H = 0x00008107U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x0000010fU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x000034a0U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800100c0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000071U);
            HW_SCE_func101(0xf74d2a9dU, 0x3b71ea05U, 0xba5d2646U, 0x282875a9U);
            HW_SCE_func043();
            SCE->REG_ECH = 0x00003405U;
            HW_SCE_func100(0x55dc9f4eU, 0xa609c069U, 0x893e5c09U, 0xf4e6f911U);
            SCE->REG_ECH = 0x000034a4U;
            HW_SCE_func044();
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
            SCE->REG_104H = 0x00000251U;
            SCE->REG_A4H = 0x00050804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x00060804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x00070804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            for (iLoop = 0; iLoop < (INST_DATA_SIZE-4) ; iLoop = iLoop + 4)
            {
                HW_SCE_func100(0x2383c7b1U, 0x93928fb2U, 0xb9b5e198U, 0x75299b85U);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00d049adU;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_InstData[iLoop + 0];
                SCE->REG_100H = InData_InstData[iLoop + 1];
                SCE->REG_100H = InData_InstData[iLoop + 2];
                SCE->REG_100H = InData_InstData[iLoop + 3];
                SCE->REG_A4H = 0x01e026bdU;
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
                OutData_KeyIndex[1+iLoop + 0] = SCE->REG_100H;
                OutData_KeyIndex[1+iLoop + 1] = SCE->REG_100H;
                OutData_KeyIndex[1+iLoop + 2] = SCE->REG_100H;
                OutData_KeyIndex[1+iLoop + 3] = SCE->REG_100H;
                HW_SCE_func101(0x2890a981U, 0x52c62d14U, 0x961fba44U, 0x5eedd07fU);
            }
            HW_SCE_func100(0xd13d39f7U, 0x031f1784U, 0xbeaf1fbaU, 0x25771808U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x01000684U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x010029cdU;
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
            OutData_KeyIndex[1+iLoop + 0] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 1] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 2] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 3] = SCE->REG_100H;
            SCE->REG_104H = 0x00000361U;
            SCE->REG_A4H = 0x000049adU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_InstData[iLoop + 0];
            SCE->REG_100H = InData_InstData[iLoop + 1];
            SCE->REG_100H = InData_InstData[iLoop + 2];
            SCE->REG_100H = InData_InstData[iLoop + 3];
            SCE->REG_A4H = 0x00900c45U;
            SCE->REG_00H = 0x00001113U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_func100(0x6d57ca59U, 0xce51d7c7U, 0x332ece1eU, 0x97c9ff49U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_func102(0x974333caU, 0x4dfe1029U, 0xd2b17698U, 0x56f325f9U);
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
                HW_SCE_func100(0x7f075ffcU, 0xd6d16b59U, 0x887ce636U, 0x414a790dU);
                SCE->REG_E0H = 0x81010000U;
                SCE->REG_04H = 0x00000606U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_KeyIndex[0] = SCE->REG_100H;
                HW_SCE_func102(0xd9906a8bU, 0x68e301beU, 0xdf1f36f1U, 0x300a4d15U);
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
    else
    {
        HW_SCE_func049(InData_Cmd);
        SCE->REG_ECH = 0x3420a880U;
        SCE->REG_ECH = 0x00000005U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_ECH = 0x3420a880U;
        SCE->REG_ECH = 0x0000000aU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        SCE->REG_ECH = 0x38208880U;
        SCE->REG_ECH = 0x00000006U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_func100(0xf9e073c0U, 0x3a3ea20dU, 0xf2e9c911U, 0x2bba5375U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func102(0xd294e63bU, 0xcb672952U, 0x20ec9ae0U, 0x49d6fc56U);
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
            HW_SCE_func100(0xbab65a8dU, 0xd9111022U, 0x2ddef63eU, 0x54761e03U);
            HW_SCE_func103();
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x01000e84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_E0H = 0x80010000U;
            SCE->REG_00H = 0x00008107U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x0000010fU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x000034a0U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800100c0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000ffU);
            HW_SCE_func101(0xdc927c4dU, 0x0eadf65bU, 0x31bd3e36U, 0x8ab4797fU);
            HW_SCE_func043();
            SCE->REG_ECH = 0x00003405U;
            HW_SCE_func100(0x3b7c3e3fU, 0xd82a54e0U, 0xcc34de61U, 0x54e57360U);
            SCE->REG_ECH = 0x000034a4U;
            HW_SCE_func044();
            SCE->REG_104H = 0x00000161U;
            SCE->REG_A4H = 0x00060804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x00070804U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            for (iLoop = 0; iLoop < INST_DATA_SIZE; iLoop = iLoop + 4)
            {
                HW_SCE_func100(0xdf5e5a92U, 0x4cf14b2aU, 0x35d817a9U, 0x79f9295bU);
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00000885U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_InstData[iLoop + 0];
                SCE->REG_100H = InData_InstData[iLoop + 1];
                SCE->REG_100H = InData_InstData[iLoop + 2];
                SCE->REG_100H = InData_InstData[iLoop + 3];
                SCE->REG_A4H = 0x01e026bdU;
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
                OutData_KeyIndex[1+iLoop + 0] = SCE->REG_100H;
                OutData_KeyIndex[1+iLoop + 1] = SCE->REG_100H;
                OutData_KeyIndex[1+iLoop + 2] = SCE->REG_100H;
                OutData_KeyIndex[1+iLoop + 3] = SCE->REG_100H;
                HW_SCE_func101(0x79744299U, 0xbfd6bb6fU, 0x3350b6d6U, 0x98653d10U);
            }
            HW_SCE_func100(0x7da37adcU, 0xe8019eecU, 0xa6d9d2fdU, 0x829009b9U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x01000684U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x010029cdU;
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
            OutData_KeyIndex[1+iLoop + 0] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 1] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 2] = SCE->REG_100H;
            OutData_KeyIndex[1+iLoop + 3] = SCE->REG_100H;
            HW_SCE_func100(0x41d4a316U, 0x0c085772U, 0xe5e5f067U, 0x6bb95c26U);
            SCE->REG_E0H = 0x81010000U;
            SCE->REG_04H = 0x00000606U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_KeyIndex[0] = SCE->REG_100H;
            HW_SCE_func102(0xb570345fU, 0xffe8efcdU, 0x4eb177bfU, 0x53361584U);
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
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_p71.prc
***********************************************************************************************************************/
