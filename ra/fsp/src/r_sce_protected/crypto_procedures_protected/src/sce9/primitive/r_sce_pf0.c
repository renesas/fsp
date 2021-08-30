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

fsp_err_t R_SCE_EcdsaSignatureGenerateSub(uint32_t *InData_CurveType, uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_MsgDgst, uint32_t *OutData_Signature)
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
    SCE->REG_84H = 0x0000f002U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010340U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_CurveType[0];
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010380U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000140U;
    SCE->REG_104H = 0x00000768U;
    SCE->REG_E0H = 0x8088001eU;
    for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
    {
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MsgDgst[iLoop + 0];
    }
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_ECH = 0x30003380U;
    SCE->REG_ECH = 0x00070020U;
    SCE->REG_ECH = 0x0000d3e0U;
    SCE->REG_ECH = 0x00030040U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x38000c00U;
    SCE->REG_ECH = 0x1000d3e0U;
    SCE->REG_ECH = 0x00050040U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x000037beU;
    SCE->REG_ECH = 0x0000a7a0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x0000383dU;
    SCE->REG_ECH = 0x38001001U;
    SCE->REG_ECH = 0x1000d3e0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x30000f5aU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d3e1U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x38000f9cU;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x1a448823U, 0x6a3a423fU, 0xbcd9e8e2U, 0xcacc0caeU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x8ed1208dU, 0xdbf7077fU, 0x507fb8b2U, 0x33c0ffdbU);
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
        R_SCE_func100(0x6a7bb13dU, 0x4d21208cU, 0x0404d573U, 0x6ba466e9U);
        SCE->REG_28H = 0x00870001U;
        SCE->REG_ECH = 0x30003340U;
        SCE->REG_ECH = 0x00050020U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x000004C8U;
        SCE->REG_ECH = 0x00030040U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x0000031CU;
        SCE->REG_ECH = 0x00070040U;
        SCE->REG_ECH = 0x30003380U;
        SCE->REG_ECH = 0x00070020U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_ECH = 0x00030040U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x0000013CU;
        SCE->REG_ECH = 0x00050040U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x000001F8U;
        SCE->REG_ECH = 0x00000080U;
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
        R_SCE_func100(0x75e6190dU, 0x75c068caU, 0xdb3f287fU, 0xdd0d8ad5U);
        R_SCE_func070_r2(OFS_ADR);
        R_SCE_func100(0xb897dde9U, 0x49145a8bU, 0x1080a889U, 0xfc598151U);
        SCE->REG_34H = 0x00000003U;
        SCE->REG_24H = 0x800068d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x00000bffU;
        SCE->REG_E0H = 0x8088001fU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000025U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000040U;
        SCE->REG_E0H = 0x8088001fU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000023U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_E0H = 0x8088001fU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000024U;
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
        R_SCE_func100(0x2402576fU, 0x097cdc2dU, 0xb8005e2dU, 0x91fa30ccU);
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
        SCE->REG_24H = 0x00001228U;
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
        SCE->REG_24H = 0x0000a0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func100(0x4d2112fcU, 0xa91850faU, 0x56bcdaadU, 0x6b15ee85U);
        R_SCE_func103();
        R_SCE_func100(0xcb8ab6ecU, 0xf31e9e6eU, 0x8c036f67U, 0x9d1873cdU);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x01080c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        R_SCE_func100(0x4e233698U, 0x8762b73aU, 0xaaf97837U, 0xfb15b664U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x42e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x00000024U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[0] = SCE->REG_100H;
        S_HEAP[1] = SCE->REG_100H;
        S_HEAP[2] = SCE->REG_100H;
        S_HEAP[3] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[4] = SCE->REG_100H;
        S_HEAP[5] = SCE->REG_100H;
        S_HEAP[6] = SCE->REG_100H;
        S_HEAP[7] = SCE->REG_100H;
        R_SCE_func100(0xb26b813dU, 0xdaf2e7c5U, 0x29d9a5e8U, 0x5749d586U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x0000002aU;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[8] = SCE->REG_100H;
        S_HEAP[9] = SCE->REG_100H;
        S_HEAP[10] = SCE->REG_100H;
        S_HEAP[11] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[12] = SCE->REG_100H;
        S_HEAP[13] = SCE->REG_100H;
        S_HEAP[14] = SCE->REG_100H;
        S_HEAP[15] = SCE->REG_100H;
        R_SCE_func100(0x34680293U, 0x39dd9da8U, 0x9de57739U, 0xf0213a92U);
        SCE->REG_D0H = 0x00000100U;
        SCE->REG_C4H = 0x40e087bfU;
        SCE->REG_00H = 0x00002323U;
        SCE->REG_2CH = 0x00000021U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_04H = 0x00000222U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[16] = SCE->REG_100H;
        S_HEAP[17] = SCE->REG_100H;
        S_HEAP[18] = SCE->REG_100H;
        S_HEAP[19] = SCE->REG_100H;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_HEAP[20] = SCE->REG_100H;
        S_HEAP[21] = SCE->REG_100H;
        S_HEAP[22] = SCE->REG_100H;
        S_HEAP[23] = SCE->REG_100H;
        R_SCE_func100(0x135be492U, 0xfcebca2fU, 0x13209927U, 0x69b81b01U);
        SCE->REG_104H = 0x00000052U;
        SCE->REG_C4H = 0x00000c84U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_C4H = 0x400009cdU;
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
        S_HEAP[24] = SCE->REG_100H;
        S_HEAP[25] = SCE->REG_100H;
        S_HEAP[26] = SCE->REG_100H;
        S_HEAP[27] = SCE->REG_100H;
        R_SCE_func100(0x08e7e299U, 0xbc12519eU, 0x04c40bbfU, 0xa614af79U);
        R_SCE_func071_r2(OFS_ADR);
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
        SCE->REG_24H = 0x00001dc0U;
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
        SCE->REG_24H = 0x00000dc0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
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
        SCE->REG_24H = 0x00000dc0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00005cd0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func100(0x38615939U, 0xd2efd875U, 0x9f932baaU, 0x32ba18ffU);
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_E0H = 0x8188001fU;
        SCE->REG_00H = 0x00003823U;
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
        R_SCE_func100(0x32dff07dU, 0x0579e031U, 0x3916c950U, 0x647d7461U);
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
        SCE->REG_E0H = 0x8188001fU;
        SCE->REG_00H = 0x00003823U;
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
        SCE->REG_E0H = 0x8088001fU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000023U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0x6f5c7973U, 0x5d3bb475U, 0x8d7ba199U, 0xa2e3c634U);
        SCE->REG_ECH = 0x00000bffU;
        SCE->REG_E0H = 0x8088001fU;
        SCE->REG_00H = 0x00008323U;
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
        SCE->REG_ECH = 0x00000100U;
        SCE->REG_ECH = 0x0000b7a0U;
        SCE->REG_ECH = 0x000000f0U;
        SCE->REG_ECH = 0x0000373cU;
        SCE->REG_ECH = 0x00000b9cU;
        SCE->REG_E0H = 0x81010380U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for(iLoop=0;iLoop<256;iLoop=iLoop+1)
        {
            R_SCE_func101(0x7a838a51U, 0x6cce7ddfU, 0xee2b1e5fU, 0xe71c048fU);
            R_SCE_func300();
            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }
            R_SCE_func101(0xb5ca6269U, 0xd2aa2e94U, 0x9a4952d4U, 0xee7c2192U);
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
        R_SCE_func100(0xd3d2ab1aU, 0x645767f3U, 0xd3f45929U, 0xaa121ce1U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x765d5237U, 0x65a3d761U, 0x00c15f28U, 0x7bc8560bU);
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
            SCE->REG_E0H = 0x8188001fU;
            SCE->REG_00H = 0x00003823U;
            SCE->REG_2CH = 0x00000013U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_E0H = 0x8088001fU;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x00000028U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x000000c0U;
            SCE->REG_E0H = 0x8088001fU;
            SCE->REG_00H = 0x00008323U;
            SCE->REG_2CH = 0x00000029U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000100U;
            SCE->REG_E0H = 0x8088001fU;
            SCE->REG_00H = 0x00008323U;
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
            SCE->REG_E0H = 0x8188001fU;
            SCE->REG_00H = 0x00003823U;
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
            R_SCE_func100(0xb8c94f32U, 0xd2bbbd16U, 0xef613e67U, 0xac60674aU);
            SCE->REG_ECH = 0x00000bffU;
            SCE->REG_E0H = 0x8088001fU;
            SCE->REG_00H = 0x00008323U;
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
            SCE->REG_ECH = 0x00000100U;
            SCE->REG_ECH = 0x0000b7a0U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_ECH = 0x00000b9cU;
            SCE->REG_E0H = 0x81010380U;
            SCE->REG_04H = 0x00000607U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            S_RAM[0] = change_endian_long(SCE->REG_100H);
            for(iLoop=0;iLoop<256;iLoop=iLoop+1)
            {
                R_SCE_func101(0x7a4e80f2U, 0xdf244a3cU, 0x932b9183U, 0x12582515U);
                R_SCE_func300();
                if (S_RAM[0] == 0x00000001U)
                {
                    break;
                }
                R_SCE_func101(0x759e4039U, 0x1747ee2fU, 0x736005abU, 0x2275520fU);
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
            R_SCE_func100(0x22e485b0U, 0x2d734131U, 0xfaeebc70U, 0xac70c4f6U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0xc4ac4363U, 0xac282526U, 0x8065d742U, 0x1f486f7aU);
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
                SCE->REG_E0H = 0x8088001fU;
                SCE->REG_00H = 0x00008323U;
                SCE->REG_2CH = 0x00000021U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7c0U;
                SCE->REG_ECH = 0x00000008U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000f0U);
                R_SCE_func101(0xaf83a94bU, 0x7c2b7d43U, 0xceccec83U, 0xbee4238fU);
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
                SCE->REG_E0H = 0x8188001fU;
                SCE->REG_00H = 0x00003823U;
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
                SCE->REG_E0H = 0x8188001fU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000018U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7e0U;
                SCE->REG_ECH = 0x000000c0U;
                SCE->REG_E0H = 0x8188001fU;
                SCE->REG_00H = 0x00003823U;
                SCE->REG_2CH = 0x00000019U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x0000b7e0U;
                SCE->REG_ECH = 0x00000100U;
                SCE->REG_E0H = 0x8188001fU;
                SCE->REG_00H = 0x00003823U;
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
                R_SCE_func100(0xb153a145U, 0x8f010bbdU, 0x2111b502U, 0x24e06cb0U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    R_SCE_func102(0x4d058847U, 0x732c3fd3U, 0xf8232eabU, 0xd256c1e3U);
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
                    SCE->REG_E0H = 0x8088001fU;
                    SCE->REG_00H = 0x00008323U;
                    SCE->REG_2CH = 0x00000021U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_ECH = 0x0000b7c0U;
                    SCE->REG_ECH = 0x00000008U;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000004U);
                    R_SCE_func101(0xac9d7a87U, 0x8a1a8270U, 0xa13b56caU, 0x76873dafU);
                    R_SCE_func303();
                    R_SCE_func301();
                    SCE->REG_104H = 0x00001762U;
                    SCE->REG_D0H = 0x00000500U;
                    SCE->REG_C4H = 0x42f087bfU;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = S_HEAP[0];
                    SCE->REG_100H = S_HEAP[1];
                    SCE->REG_100H = S_HEAP[2];
                    SCE->REG_100H = S_HEAP[3];
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = S_HEAP[4];
                    SCE->REG_100H = S_HEAP[5];
                    SCE->REG_100H = S_HEAP[6];
                    SCE->REG_100H = S_HEAP[7];
                    SCE->REG_00H = 0x00003223U;
                    SCE->REG_2CH = 0x00000014U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = S_HEAP[8];
                    SCE->REG_100H = S_HEAP[9];
                    SCE->REG_100H = S_HEAP[10];
                    SCE->REG_100H = S_HEAP[11];
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = S_HEAP[12];
                    SCE->REG_100H = S_HEAP[13];
                    SCE->REG_100H = S_HEAP[14];
                    SCE->REG_100H = S_HEAP[15];
                    SCE->REG_00H = 0x00003223U;
                    SCE->REG_2CH = 0x0000001dU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = S_HEAP[16];
                    SCE->REG_100H = S_HEAP[17];
                    SCE->REG_100H = S_HEAP[18];
                    SCE->REG_100H = S_HEAP[19];
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = S_HEAP[20];
                    SCE->REG_100H = S_HEAP[21];
                    SCE->REG_100H = S_HEAP[22];
                    SCE->REG_100H = S_HEAP[23];
                    SCE->REG_00H = 0x00003223U;
                    SCE->REG_2CH = 0x0000001aU;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_C4H = 0x400007bdU;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = S_HEAP[24];
                    SCE->REG_100H = S_HEAP[25];
                    SCE->REG_100H = S_HEAP[26];
                    SCE->REG_100H = S_HEAP[27];
                    SCE->REG_C4H = 0x00800c45U;
                    SCE->REG_00H = 0x00002213U;
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
                    SCE->REG_24H = 0x0000a8d0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_34H = 0x00000020U;
                    SCE->REG_24H = 0x80001dc0U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000040c1U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x00000a2cU;
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
                    SCE->REG_24H = 0x000040c1U;
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
                    SCE->REG_24H = 0x000040c1U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_24H_b.B21)
                    {
                        /* waiting */
                    }
                    SCE->REG_24H = 0x000009c0U;
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
                    R_SCE_func100(0x3a1a3204U, 0x07b935d2U, 0xc28bfa31U, 0xb83db6fbU);
                    SCE->REG_1CH = 0x00400000U;
                    SCE->REG_1D0H = 0x00000000U;
                    if (1U == (SCE->REG_1CH_b.B22))
                    {
                        R_SCE_func102(0xcb7335eeU, 0x310a5cbdU, 0x7c67bc91U, 0x5abc5de7U);
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
                        SCE->REG_24H = 0x00000ac0U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000800U;
                        SCE->REG_24H = 0x800060c2U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000002U;
                        SCE->REG_24H = 0x800088d0U;
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
                        SCE->REG_E0H = 0x8088001fU;
                        SCE->REG_00H = 0x00008323U;
                        SCE->REG_2CH = 0x00000021U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800U;
                        SCE->REG_ECH = 0x0000b7c0U;
                        SCE->REG_ECH = 0x00000008U;
                        SCE->REG_104H = 0x00000058U;
                        SCE->REG_E0H = 0x800103a0U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x00000005U);
                        R_SCE_func101(0xa4ab2b7dU, 0xf9acd790U, 0x2504beb9U, 0xfceb227eU);
                        R_SCE_func303();
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
                        SCE->REG_24H = 0x000080c1U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_ECH = 0x0000b7e0U;
                        SCE->REG_ECH = 0x00000140U;
                        SCE->REG_E0H = 0x8188001fU;
                        SCE->REG_00H = 0x00003823U;
                        SCE->REG_2CH = 0x00000011U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800U;
                        SCE->REG_34H = 0x00000020U;
                        SCE->REG_24H = 0x80001dc0U;
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
                        SCE->REG_34H = 0x00000002U;
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
                        SCE->REG_24H = 0x800040c1U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_24H_b.B21)
                        {
                            /* waiting */
                        }
                        SCE->REG_34H = 0x00000002U;
                        SCE->REG_24H = 0x800009c0U;
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
                        SCE->REG_34H = 0x00000020U;
                        SCE->REG_24H = 0x80001dc0U;
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
                        SCE->REG_104H = 0x00000068U;
                        SCE->REG_E0H = 0x800100e0U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = InData_KeyIndex[0];
                        SCE->REG_104H = 0x00000058U;
                        SCE->REG_E0H = 0x800103a0U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x000000f0U);
                        R_SCE_func101(0xaa191445U, 0xafee2bd5U, 0x9c17bdb8U, 0xe3948940U);
                        R_SCE_func043();
                        SCE->REG_ECH = 0x00003799U;
                        R_SCE_func074_r1();
                        SCE->REG_ECH = 0x000034feU;
                        SCE->REG_104H = 0x00000058U;
                        SCE->REG_E0H = 0x800103a0U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = change_endian_long(0x000000f0U);
                        R_SCE_func101(0xe8510b39U, 0xcca18a70U, 0xe151c6b3U, 0x39b7bdedU);
                        R_SCE_func044();
                        SCE->REG_104H = 0x00000762U;
                        SCE->REG_D0H = 0x40000100U;
                        SCE->REG_C4H = 0x02f087b7U;
                        SCE->REG_00H = 0x00003223U;
                        SCE->REG_2CH = 0x00000018U;
                        for (iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
                        {
                            /* WAIT_LOOP */
                            while (1U != SCE->REG_104H_b.B31)
                            {
                                /* waiting */
                            }
                            SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
                            SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
                            SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
                            SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
                        }
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800U;
                        SCE->REG_104H = 0x00000362U;
                        SCE->REG_D0H = 0x40000000U;
                        SCE->REG_C4H = 0x000087b5U;
                        /* WAIT_LOOP */
                        while (1U != SCE->REG_104H_b.B31)
                        {
                            /* waiting */
                        }
                        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 0];
                        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 1];
                        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 2];
                        SCE->REG_100H = InData_KeyIndex[iLoop+1 + 3];
                        SCE->REG_C4H = 0x00900c45U;
                        SCE->REG_00H = 0x00002213U;
                        /* WAIT_LOOP */
                        while (0U != SCE->REG_00H_b.B25)
                        {
                            /* waiting */
                        }
                        SCE->REG_1CH = 0x00001800U;
                        R_SCE_func100(0xc7bc8bf6U, 0x1ee0510aU, 0x67650962U, 0x8e587dfbU);
                        SCE->REG_1CH = 0x00400000U;
                        SCE->REG_1D0H = 0x00000000U;
                        if (1U == (SCE->REG_1CH_b.B22))
                        {
                            R_SCE_func102(0x907b6d34U, 0x94fbd420U, 0xc6323182U, 0x81ba2497U);
                            SCE->REG_1B8H = 0x00000040U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_18H_b.B12)
                            {
                                /* waiting */
                            }
                            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
                        }
                        else
                        {
                            SCE->REG_24H = 0x000015c0U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_34H = 0x00000008U;
                            SCE->REG_24H = 0x80000c2dU;
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
                            SCE->REG_24H = 0x00000c2cU;
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
                            SCE->REG_24H = 0x000080c1U;
                            /* WAIT_LOOP */
                            while (0U != SCE->REG_24H_b.B21)
                            {
                                /* waiting */
                            }
                            SCE->REG_34H = 0x00000002U;
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
                            SCE->REG_34H = 0x00000002U;
                            SCE->REG_24H = 0x800009c0U;
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
                            R_SCE_func100(0x33a8a531U, 0xf5d8f41eU, 0x7de14417U, 0xdc4d6438U);
                            SCE->REG_1CH = 0x00400000U;
                            SCE->REG_1D0H = 0x00000000U;
                            if (1U == (SCE->REG_1CH_b.B22))
                            {
                                R_SCE_func102(0x1d930db0U, 0x45cf8691U, 0x9532f2ebU, 0x3f70576aU);
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
                                R_SCE_func100(0xd1dda6abU, 0xfc0b53b0U, 0x720fbd8fU, 0xba3333eaU);
                                SCE->REG_2CH = 0x0000002bU;
                                SCE->REG_04H = 0x00000322U;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_Signature[0] = SCE->REG_100H;
                                OutData_Signature[1] = SCE->REG_100H;
                                OutData_Signature[2] = SCE->REG_100H;
                                OutData_Signature[3] = SCE->REG_100H;
                                OutData_Signature[4] = SCE->REG_100H;
                                OutData_Signature[5] = SCE->REG_100H;
                                OutData_Signature[6] = SCE->REG_100H;
                                OutData_Signature[7] = SCE->REG_100H;
                                R_SCE_func100(0x8102dd45U, 0xf907dcd3U, 0xcd465204U, 0xd195885aU);
                                SCE->REG_2CH = 0x0000002aU;
                                SCE->REG_04H = 0x00000322U;
                                /* WAIT_LOOP */
                                while (1U != SCE->REG_04H_b.B30)
                                {
                                    /* waiting */
                                }
                                OutData_Signature[8] = SCE->REG_100H;
                                OutData_Signature[9] = SCE->REG_100H;
                                OutData_Signature[10] = SCE->REG_100H;
                                OutData_Signature[11] = SCE->REG_100H;
                                OutData_Signature[12] = SCE->REG_100H;
                                OutData_Signature[13] = SCE->REG_100H;
                                OutData_Signature[14] = SCE->REG_100H;
                                OutData_Signature[15] = SCE->REG_100H;
                                R_SCE_func102(0x9a9a7812U, 0xbcade75fU, 0x588e4ce5U, 0x59fa7e00U);
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
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pf0_r4.prc
***********************************************************************************************************************/
