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
#include "r_sce.h"
#include "r_sce_private.h"

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

fsp_err_t R_SCE_GenerateEccP384RandomKeyIndexSub(uint32_t *InData_CurveType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PrivKeyIndex)
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
    if (0x0U != (SCE->REG_1B8H & 0x1eU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x0000f902U;
    SCE->REG_108H = 0x00000000U;
    R_SCE_func100(0xc7afef81U, 0x48345805U, 0x93156e87U, 0xc74abc8aU);
    SCE->REG_28H = 0x008b0001U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010340U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_ECH = 0x38000f5aU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x000002B4U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x000003D8U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x81010000U;
    SCE->REG_04H = 0x00000606U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    OFS_ADR = S_RAM[0];
    R_SCE_func100(0x46e7df26U, 0x81f3e8b6U, 0xa396710dU, 0xfdefaaefU);
    R_SCE_func027_r2(OFS_ADR);
    R_SCE_func100(0xa7841f65U, 0xb187cdb0U, 0xcf849412U, 0x151372c9U);
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000025U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7e0U;
    SCE->REG_ECH = 0x00000040U;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7e0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000024U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x008d0001U;
    R_SCE_func103();
    R_SCE_func100(0x10f916f8U, 0xa801ce29U, 0x8253997cU, 0xde19254fU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00003213U;
    SCE->REG_2CH = 0x00000011U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func103();
    R_SCE_func100(0x3b9dc7cbU, 0x5b37795aU, 0xe136d56cU, 0x709b3213U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00003213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func103();
    R_SCE_func100(0x2a37054dU, 0x4bc6cb0bU, 0x08b9ca7cU, 0x1e6483daU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00003213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x0000320bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000020bU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000004U;
    SCE->REG_24H = 0x0000a206U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B10)
    {
        /* waiting */
    }
    SCE->REG_18H = 0x00000000U;
    SCE->REG_24H = 0x000016c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000682U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c2U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x008b0001U;
    SCE->REG_ECH = 0x0000b7e0U;
    SCE->REG_ECH = 0x00000140U;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000021U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func100(0x3a0e2512U, 0xe2ef86edU, 0x69a6588dU, 0x77641f10U);
    R_SCE_func028_r2(OFS_ADR);
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x800088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000802U;
    SCE->REG_24H = 0x8000acd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000dcd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00021028U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x100019b1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00008cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001028U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x100019b1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000e0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    R_SCE_func100(0xc25e97abU, 0xea176d21U, 0xd43f80d4U, 0xdef20804U);
    SCE->REG_ECH = 0x0000b7e0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x818c001fU;
    SCE->REG_00H = 0x00003833U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00021028U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x100019b1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    R_SCE_func103();
    R_SCE_func100(0x8ea04f22U, 0x24a15cecU, 0x319a6a88U, 0x2c98d571U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00003213U;
    SCE->REG_2CH = 0x00000013U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func103();
    R_SCE_func100(0xf8218e10U, 0x1f2c97fcU, 0xe91247e8U, 0xe8bb190fU);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00003213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    R_SCE_func103();
    R_SCE_func100(0x65536e29U, 0xc4642c00U, 0xfe80bd7aU, 0x06f04bc8U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_00H = 0x00003213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x00000c28U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x100019b1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000060c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000015c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000d41U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_E0H = 0x818c001fU;
    SCE->REG_00H = 0x00003833U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00021028U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x100019b1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x8000c0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7e0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_E0H = 0x808c001fU;
    SCE->REG_00H = 0x00008333U;
    SCE->REG_2CH = 0x00000021U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x00000842U;
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x0000b480U;
    SCE->REG_ECH = 0x00000180U;
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f9U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_E0H = 0x81010380U;
    SCE->REG_04H = 0x00000607U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    S_RAM[0] = change_endian_long(SCE->REG_100H);
    for(iLoop=0;iLoop<384;iLoop=iLoop+1)
    {
        R_SCE_func101(0x361c125fU, 0xfdfc9737U, 0xedd62214U, 0x1b17d0b5U);
        R_SCE_func300();
        if (S_RAM[0] == 0x00000001U)
        {
            break;
        }
        R_SCE_func101(0xdda84da8U, 0x54de67b1U, 0x7f9336d7U, 0x1175c629U);
    }
    SCE->REG_24H = 0x00001dc0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000591U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001f00U;
    SCE->REG_1CH = 0x00210000U;
    R_SCE_func100(0x982ff807U, 0x7eb84b02U, 0xc1713c28U, 0x53ed0d1eU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0xb3365104U, 0x8b33fcf5U, 0x88a70324U, 0x5f4cb20dU);
        SCE->REG_1B8H = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_E0H = 0x818c001fU;
        SCE->REG_00H = 0x00003833U;
        SCE->REG_2CH = 0x00000013U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_E0H = 0x808c001fU;
        SCE->REG_00H = 0x00008333U;
        SCE->REG_2CH = 0x00000028U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x000000c0U;
        SCE->REG_E0H = 0x808c001fU;
        SCE->REG_00H = 0x00008333U;
        SCE->REG_2CH = 0x00000029U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000100U;
        SCE->REG_E0H = 0x808c001fU;
        SCE->REG_00H = 0x00008333U;
        SCE->REG_2CH = 0x00000025U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_34H = 0x00000802U;
        SCE->REG_24H = 0x800088d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000802U;
        SCE->REG_24H = 0x8000acd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000040U;
        SCE->REG_E0H = 0x818c001fU;
        SCE->REG_00H = 0x00003833U;
        SCE->REG_2CH = 0x00000012U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x00000828U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x100019b1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000019a1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000e0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000acd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func100(0xf823cb0dU, 0x8533930fU, 0x7a86ad39U, 0x6c2a8bb3U);
        SCE->REG_ECH = 0x00000bffU;
        SCE->REG_E0H = 0x808c001fU;
        SCE->REG_00H = 0x00008333U;
        SCE->REG_2CH = 0x00000021U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x00000bdeU;
        SCE->REG_ECH = 0x00000842U;
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_ECH = 0x0000b480U;
        SCE->REG_ECH = 0x00000180U;
        SCE->REG_ECH = 0x0000b7a0U;
        SCE->REG_ECH = 0x00000007U;
        SCE->REG_ECH = 0x00000b9cU;
        SCE->REG_E0H = 0x81010380U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for(iLoop=0;iLoop<384;iLoop=iLoop+1)
        {
            R_SCE_func101(0x8f63dc4eU, 0x8a36e097U, 0xbc47e32eU, 0xac7d8b6cU);
            R_SCE_func300();
            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }
            R_SCE_func101(0x254d1b5aU, 0x004fb84aU, 0x0e89e7d0U, 0x94871414U);
        }
        SCE->REG_24H = 0x00001dc0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001f00U;
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0x88c47862U, 0xab80ab75U, 0x6602dc7cU, 0x60a9e92dU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0xf6d060b8U, 0xf77ba8b8U, 0x6e22e11aU, 0x02e96631U);
            SCE->REG_1B8H = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            SCE->REG_24H = 0x00009cd0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x0000a0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x00000bffU;
            SCE->REG_E0H = 0x808c001fU;
            SCE->REG_00H = 0x00008333U;
            SCE->REG_2CH = 0x00000021U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7c0U;
            SCE->REG_ECH = 0x0000000cU;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x000000f9U);
            R_SCE_func101(0x21363b46U, 0x671f5d1cU, 0x6c6263ddU, 0xcfd62e64U);
            R_SCE_func303();
            R_SCE_func301();
            SCE->REG_24H = 0x000019c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000d91U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x8000a0c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000040U;
            SCE->REG_E0H = 0x818c001fU;
            SCE->REG_00H = 0x00003833U;
            SCE->REG_2CH = 0x0000001aU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_34H = 0x0000000aU;
            SCE->REG_24H = 0x80000a2cU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x800060c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x800088d0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x0000000aU;
            SCE->REG_24H = 0x8000082cU;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x100019b1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000019a1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000800U;
            SCE->REG_24H = 0x800040c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_E0H = 0x818c001fU;
            SCE->REG_00H = 0x00003833U;
            SCE->REG_2CH = 0x00000018U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x000000c0U;
            SCE->REG_E0H = 0x818c001fU;
            SCE->REG_00H = 0x00003833U;
            SCE->REG_2CH = 0x00000019U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000100U;
            SCE->REG_E0H = 0x818c001fU;
            SCE->REG_00H = 0x00003833U;
            SCE->REG_2CH = 0x00000015U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func305();
            SCE->REG_24H = 0x00001dc0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x00000591U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001f00U;
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0xa057fd81U, 0xc1b8bf0fU, 0x29906e9cU, 0x249e1454U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x03c73c0dU, 0x24847ce1U, 0xd1a04157U, 0x9329a5b1U);
                SCE->REG_1B8H = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_18H_b.B12)
                {
                    /* waiting */
                }
                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                SCE->REG_24H = 0x00009cd0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000019c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x00000591U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x0000a0c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_ECH = 0x00000bffU;
                SCE->REG_E0H = 0x808c001fU;
                SCE->REG_00H = 0x00008333U;
                SCE->REG_2CH = 0x00000021U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x0000000cU;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000014U);
                R_SCE_func101(0x0cb80e60U, 0x1a1ffc94U, 0x916436bcU, 0x9ee1ae7fU);
                R_SCE_func303();
                R_SCE_func301();
                R_SCE_func100(0x66d3eef4U, 0xb3e7f42fU, 0xb67ef69bU, 0x464b0f80U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80010000U;
                SCE->REG_00H = 0x00008207U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000020fU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x000034e0U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000f9U);
                R_SCE_func101(0x45966ffaU, 0x5e90be93U, 0x00a08602U, 0xf71fa1f2U);
                R_SCE_func043();
                R_SCE_func076();
                SCE->REG_ECH = 0x000034feU;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000f9U);
                R_SCE_func101(0x9d95aaeaU, 0xf69a2b63U, 0x69374eb2U, 0x1816c351U);
                R_SCE_func044();
                R_SCE_func100(0x50c95905U, 0xcafd39d0U, 0x44b053e8U, 0x8bd072efU);
                SCE->REG_D0H = 0x40000200U;
                SCE->REG_C4H = 0x02e087b7U;
                SCE->REG_ECH = 0x0000b7e0U;
                SCE->REG_ECH = 0x00000140U;
                SCE->REG_E0H = 0x818c001fU;
                SCE->REG_00H = 0x00002833U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000232U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[1] = SCE->REG_100H;
                OutData_PrivKeyIndex[2] = SCE->REG_100H;
                OutData_PrivKeyIndex[3] = SCE->REG_100H;
                OutData_PrivKeyIndex[4] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[5] = SCE->REG_100H;
                OutData_PrivKeyIndex[6] = SCE->REG_100H;
                OutData_PrivKeyIndex[7] = SCE->REG_100H;
                OutData_PrivKeyIndex[8] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[9] = SCE->REG_100H;
                OutData_PrivKeyIndex[10] = SCE->REG_100H;
                OutData_PrivKeyIndex[11] = SCE->REG_100H;
                OutData_PrivKeyIndex[12] = SCE->REG_100H;
                R_SCE_func100(0x02051f83U, 0xff7a5860U, 0xc9b56e52U, 0x9406b088U);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x00000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x000089c5U;
                SCE->REG_00H = 0x00002213U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000212U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[13] = SCE->REG_100H;
                OutData_PrivKeyIndex[14] = SCE->REG_100H;
                OutData_PrivKeyIndex[15] = SCE->REG_100H;
                OutData_PrivKeyIndex[16] = SCE->REG_100H;
                R_SCE_func100(0x3903097dU, 0xbc45f4baU, 0x6fc46f67U, 0xc686ffb4U);
                SCE->REG_E0H = 0x81010000U;
                SCE->REG_04H = 0x00000606U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PrivKeyIndex[0] = SCE->REG_100H;
                R_SCE_func100(0x537a1aafU, 0x17d59a23U, 0x0e6839e9U, 0x4e990fe3U);
                R_SCE_func103();
                SCE->REG_104H = 0x00000052U;
                SCE->REG_C4H = 0x01000c84U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_E0H = 0x80010000U;
                SCE->REG_00H = 0x00008207U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_00H = 0x0000020fU;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x000034e0U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000027U);
                R_SCE_func101(0xf028941cU, 0x40ae6233U, 0x9d13746cU, 0x94d40692U);
                R_SCE_func043();
                R_SCE_func077();
                SCE->REG_ECH = 0x000034feU;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000028U);
                R_SCE_func101(0x28cd0f41U, 0x665c946dU, 0x7d055887U, 0xda792d85U);
                R_SCE_func044();
                R_SCE_func100(0x0a59a206U, 0x2b22a646U, 0x827d3755U, 0x9443a4deU);
                SCE->REG_D0H = 0x40000200U;
                SCE->REG_C4H = 0x02e08887U;
                SCE->REG_00H = 0x00002333U;
                SCE->REG_2CH = 0x00000022U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000232U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[1] = SCE->REG_100H;
                OutData_PubKeyIndex[2] = SCE->REG_100H;
                OutData_PubKeyIndex[3] = SCE->REG_100H;
                OutData_PubKeyIndex[4] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[5] = SCE->REG_100H;
                OutData_PubKeyIndex[6] = SCE->REG_100H;
                OutData_PubKeyIndex[7] = SCE->REG_100H;
                OutData_PubKeyIndex[8] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[9] = SCE->REG_100H;
                OutData_PubKeyIndex[10] = SCE->REG_100H;
                OutData_PubKeyIndex[11] = SCE->REG_100H;
                OutData_PubKeyIndex[12] = SCE->REG_100H;
                R_SCE_func100(0xb7232ec8U, 0x82ae7eceU, 0xa325d6e0U, 0x5569f582U);
                SCE->REG_D0H = 0x40000200U;
                SCE->REG_C4H = 0x00e08887U;
                SCE->REG_00H = 0x00002333U;
                SCE->REG_2CH = 0x00000023U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_04H = 0x00000232U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[13] = SCE->REG_100H;
                OutData_PubKeyIndex[14] = SCE->REG_100H;
                OutData_PubKeyIndex[15] = SCE->REG_100H;
                OutData_PubKeyIndex[16] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[17] = SCE->REG_100H;
                OutData_PubKeyIndex[18] = SCE->REG_100H;
                OutData_PubKeyIndex[19] = SCE->REG_100H;
                OutData_PubKeyIndex[20] = SCE->REG_100H;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[21] = SCE->REG_100H;
                OutData_PubKeyIndex[22] = SCE->REG_100H;
                OutData_PubKeyIndex[23] = SCE->REG_100H;
                OutData_PubKeyIndex[24] = SCE->REG_100H;
                R_SCE_func100(0xd619fdb5U, 0xdc06410cU, 0xc7c61fbbU, 0x9819ffcbU);
                SCE->REG_104H = 0x00000052U;
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x000089c4U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_04H = 0x00000212U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[25] = SCE->REG_100H;
                OutData_PubKeyIndex[26] = SCE->REG_100H;
                OutData_PubKeyIndex[27] = SCE->REG_100H;
                OutData_PubKeyIndex[28] = SCE->REG_100H;
                R_SCE_func100(0x48ba2865U, 0x9b9af849U, 0xf04412f3U, 0x4aaaa45eU);
                SCE->REG_E0H = 0x81010000U;
                SCE->REG_04H = 0x00000606U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_04H_b.B30)
                {
                    /* waiting */
                }
                OutData_PubKeyIndex[0] = SCE->REG_100H;
                R_SCE_func102(0xef2c39afU, 0x6aa8b7efU, 0x22db227eU, 0x38824fe2U);
                SCE->REG_1B8H = 0x00000040U;
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pf9_r5.prc
***********************************************************************************************************************/
