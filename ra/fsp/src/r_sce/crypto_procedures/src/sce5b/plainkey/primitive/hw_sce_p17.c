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

fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub(uint32_t *OutData_KeyIndex)
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
    SCE->REG_84H = 0x00001701U;
    SCE->REG_108H = 0x00000000U;
    HW_SCE_func100(0x053cc9e9U, 0xe296f52bU, 0xe360339aU, 0x5fdbec82U);
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
    SCE->REG_100H = change_endian_long(0x00000017U);
    HW_SCE_func101(0x29cf48c0U, 0x1280ed7dU, 0xcade3e9dU, 0xa222d261U);
    HW_SCE_func043();
    HW_SCE_func100(0x13ab8662U, 0x484f5d4fU, 0xe1e89fb9U, 0x8c972bf9U);
    SCE->REG_ECH = 0x0000b4a0U;
    SCE->REG_ECH = 0x00000009U;
    HW_SCE_func044();
    HW_SCE_func100(0x36979b23U, 0xc87584e4U, 0x3f2c0feeU, 0xbe55ea78U);
    SCE->REG_ECH = 0x0000b4c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x00003ce6U;
    HW_SCE_func103();
    HW_SCE_func100(0xc3a1e3f8U, 0x9a5ca673U, 0x0694c594U, 0x0710b0dbU);
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
    HW_SCE_func100(0x0566aee6U, 0x173280ecU, 0xb272b4f0U, 0x0e949171U);
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
    SCE->REG_04H = 0x00000122U;
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
    HW_SCE_func100(0x06d34346U, 0x0a9bc90fU, 0x85d8199dU, 0x4ea6bf1eU);
    HW_SCE_func103();
    HW_SCE_func100(0x577fb671U, 0x27b6e79dU, 0x0eb99917U, 0x0121ca69U);
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
    HW_SCE_func100(0xf267ad32U, 0xb288cb13U, 0x30200584U, 0xfb4a7929U);
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
    SCE->REG_A4H = 0x00e4a6bfU;
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
    SCE->REG_100H = change_endian_long(0x00000004U);
    SCE->REG_04H = 0x00000132U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[9] = SCE->REG_100H;
    OutData_KeyIndex[10] = SCE->REG_100H;
    OutData_KeyIndex[11] = SCE->REG_100H;
    OutData_KeyIndex[12] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[13] = SCE->REG_100H;
    OutData_KeyIndex[14] = SCE->REG_100H;
    OutData_KeyIndex[15] = SCE->REG_100H;
    OutData_KeyIndex[16] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[17] = SCE->REG_100H;
    OutData_KeyIndex[18] = SCE->REG_100H;
    OutData_KeyIndex[19] = SCE->REG_100H;
    OutData_KeyIndex[20] = SCE->REG_100H;
    HW_SCE_func100(0x5288b937U, 0x93531447U, 0x318e445bU, 0xeb8adcf9U);
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
    HW_SCE_func102(0xc9b7f81eU, 0x93979747U, 0xcc20f4e7U, 0x249c0b53U);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_p17.prc
***********************************************************************************************************************/
