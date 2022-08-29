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

void HW_SCE_SelfCheck1SubSub(void)
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
    SCE->REG_138H = 0xf597806AU;
    SCE->REG_10CH = 0x00010001U;
    SCE->REG_80H = 0x00000001U;
    SCE->REG_A4H = 0x00000008U;
    SCE->REG_8CH = 0x00000100U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_7CH = 0x00000001U;
    SCE->REG_14H = 0x10103005U;
    SCE->REG_10H = 0x01234567U;
    SCE->REG_14H = 0x10103015U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_138H = 0xf597806AU;
    SCE->REG_F0H = 0x00000000U;
    SCE->REG_10CH = 0x00010001U;
    SCE->REG_80H = 0x00000001U;
    SCE->REG_A4H = 0x00000008U;
    SCE->REG_8CH = 0x00000102U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_7CH = 0x00000001U;
    SCE->REG_14H = 0x10303005U;
    SCE->REG_10H = 0xefa59826U;
    SCE->REG_14H = 0x10303015U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_138H = 0xf597806AU;
    SCE->REG_F0H = 0x00000000U;
    SCE->REG_10CH = 0x00010001U;
    SCE->REG_80H = 0x00000001U;
    SCE->REG_A4H = 0x00000008U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_8CH = 0x00000100U;
    SCE->REG_7CH = 0x00000001U;
    SCE->REG_78H = 0x00000001U;
    SCE->REG_14H = 0x10303005U;
    SCE->REG_10H = 0x6159465eU;
    SCE->REG_14H = 0x10303015U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_138H = 0xf597806AU;
    SCE->REG_F0H = 0x00000000U;
    SCE->REG_10CH = 0x00010001U;
    SCE->REG_80H = 0x00000001U;
    SCE->REG_A4H = 0x00000008U;
    SCE->REG_8CH = 0x00000103U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_68H = 0x00000005U;
    SCE->REG_7CH = 0x00000001U;
    SCE->REG_78H = 0x00000005U;
    SCE->REG_14H = 0x70303005U;
    SCE->REG_10H = 0xb785467cU;
    SCE->REG_14H = 0x70303015U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_138H = 0xf597806AU;
    SCE->REG_F0H = 0x00000000U;
    SCE->REG_10CH = 0x00010001U;
    SCE->REG_ECH = 0x00000c00U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_00H = 0x08008802U;
    SCE->REG_80H = 0x00000001U;
    SCE->REG_A4H = 0x00000008U;
    SCE->REG_8CH = 0xfffff1dfU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_64H_b.B11)
    {
        /* waiting */
    }
    SCE->REG_64H = 0x00000008U;
    SCE->REG_68H = 0x00000005U;
    SCE->REG_7CH = 0x00000001U;
    SCE->REG_78H = 0x00000005U;
    SCE->REG_14H = 0x10300007U;
    SCE->REG_10H = 0x9a59a424U;
    SCE->REG_14H = 0x10300017U;
    SCE->REG_1D0H = 0x00000000U;
    SCE->REG_1D0H = 0x00000000U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B31)
    {
        /* waiting */
    }
}

/***********************************************************************************************************************
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/StoreExtraArea/HW_SCE_subprc01.prc
***********************************************************************************************************************/
