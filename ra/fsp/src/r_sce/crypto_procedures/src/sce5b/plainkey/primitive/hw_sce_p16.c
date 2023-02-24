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

fsp_err_t HW_SCE_GenerateAes128XtsRandomKeyIndexSub(uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00001601U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_func100(0x952bf9a2U, 0x7d944591U, 0x4540c78aU, 0x3f943db2U);
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
    SCE->REG_ECH = 0x000008c6U;
    SCE->REG_ECH = 0x00003c06U;
    SCE->REG_ECH = 0x000034a0U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800100c0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000016U);
    HW_SCE_func101(0x90881eafU, 0xdf5a5296U, 0x5b9581e7U, 0x1717d1bbU);
    HW_SCE_func043();
    HW_SCE_func100(0xd8e36327U, 0x36bc2c7aU, 0x91c4b9ceU, 0x2d1f6197U);
    SCE->REG_ECH = 0x0000b4a0U;
    SCE->REG_ECH = 0x00000008U;
    HW_SCE_func044();
    HW_SCE_func100(0x206f5183U, 0x114cf563U, 0xbf025f07U, 0x4bd2e6ebU);
    SCE->REG_ECH = 0x0000b4c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003ce6U;
    HW_SCE_func103();
    HW_SCE_func100(0x1d9ee0b4U, 0x4ef10f7cU, 0xb14e599dU, 0x7a03bb6dU);
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x01000e84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80080000U;
    SCE->REG_00H = 0x00008113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    HW_SCE_func103();
    HW_SCE_func100(0x6b425726U, 0x2720e12fU, 0x38905d5eU, 0x713e38cdU);
    SCE->REG_104H = 0x00000051U;
    SCE->REG_A4H = 0x01000e84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00008113U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_B0H = 0x00000100U;
    SCE->REG_A4H = 0x02e4a6bfU;
    SCE->REG_E0H = 0x81080000U;
    SCE->REG_00H = 0x00001823U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000351U;
    SCE->REG_A4H = 0x000029cdU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000002U);
    SCE->REG_04H = 0x00000132U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[1] = SCE->REG_100H;
    OutData_KeyIndex[2] = SCE->REG_100H;
    OutData_KeyIndex[3] = SCE->REG_100H;
    OutData_KeyIndex[4] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[5] = SCE->REG_100H;
    OutData_KeyIndex[6] = SCE->REG_100H;
    OutData_KeyIndex[7] = SCE->REG_100H;
    OutData_KeyIndex[8] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[9] = SCE->REG_100H;
    OutData_KeyIndex[10] = SCE->REG_100H;
    OutData_KeyIndex[11] = SCE->REG_100H;
    OutData_KeyIndex[12] = SCE->REG_100H;
    HW_SCE_func100(0xbd467f76U, 0x3f35e107U, 0x20bf8581U, 0x99a919e3U);
    SCE->REG_ECH = 0x0000b4c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x000038e6U;
    SCE->REG_ECH = 0x000008c6U;
    SCE->REG_E0H = 0x81810006U;
    SCE->REG_04H = 0x00000606U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[0] = SCE->REG_100H;
    HW_SCE_func102(0x266283fdU, 0x5bccc515U, 0x136c0c19U, 0x73faaa19U);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_p16.prc
***********************************************************************************************************************/
