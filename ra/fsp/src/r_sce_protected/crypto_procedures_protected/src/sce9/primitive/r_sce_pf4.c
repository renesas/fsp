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

fsp_err_t R_SCE_GenerateEccRandomKeyIndexSub(uint32_t *InData_CurveType, uint32_t *InData_Cmd, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PrivKeyIndex)
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
    SCE->REG_84H = 0x0000f402U;
    SCE->REG_108H = 0x00000000U;
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
    SCE->REG_ECH = 0x3020ab80U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_ECH = 0x00060020U;
    SCE->REG_ECH = 0x0000b780U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_ECH = 0x30000f5aU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d3e1U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x38000f9cU;
    SCE->REG_ECH = 0x1000d3e1U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x38008be0U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x8155dc50U, 0x0d1869b9U, 0x7213dafbU, 0x29d38597U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0xa05109acU, 0xd0e24564U, 0x0f9c3ca0U, 0xaf6b7352U);
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
        R_SCE_func100(0x411f0528U, 0x15c03807U, 0x83cc0c83U, 0xaca27c2dU);
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
        R_SCE_func100(0x89e767c7U, 0x3b5adcdcU, 0x166c61e0U, 0x42952bfaU);
        R_SCE_func070_r2(OFS_ADR);
        R_SCE_func100(0xfc4a946bU, 0xb61d5f70U, 0x0ebd9f53U, 0x8d13364aU);
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
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x8000c0d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00890001U;
        R_SCE_func103();
        R_SCE_func100(0x8f7ac3b7U, 0x218684ddU, 0xfe14a6c4U, 0x838c4da6U);
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
        R_SCE_func100(0x482a2664U, 0x9938e8a3U, 0x57ba858cU, 0xe5f47d50U);
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
        R_SCE_func100(0xde0838d4U, 0x5f03e854U, 0x328d488dU, 0x2e545c0fU);
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
        SCE->REG_ECH = 0x00007c1cU;
        SCE->REG_1CH = 0x00600000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00890001U;
            R_SCE_func101(0xaddbfa7aU, 0x9d98446aU, 0x5c8c28bfU, 0x8fcf0da8U);
        }
        else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00880001U;
            R_SCE_func101(0x7cfe0a7cU, 0xc42a03a3U, 0x02d6630dU, 0xeaa1c652U);
        }
        else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
        {
            SCE->REG_28H = 0x00870001U;
            R_SCE_func101(0xbc44913aU, 0x2e9dd705U, 0xf8112889U, 0x4b75da35U);
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
        SCE->REG_28H = 0x00870001U;
        SCE->REG_ECH = 0x0000b7e0U;
        SCE->REG_ECH = 0x00000140U;
        SCE->REG_E0H = 0x8088001fU;
        SCE->REG_00H = 0x00008323U;
        SCE->REG_2CH = 0x00000021U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0xc22a42f0U, 0xd7513ef3U, 0x141945b8U, 0x4f9677cbU);
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
        R_SCE_func100(0x0a80b6b0U, 0xd0860a65U, 0xb3795e56U, 0x738ec97aU);
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
        R_SCE_func100(0x33b12a00U, 0x5f8a73ffU, 0x6cfe2a4cU, 0x97d6bd7cU);
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
        R_SCE_func100(0xe5b76a52U, 0x4d78dc94U, 0x0689ede0U, 0xaacd6c42U);
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
        SCE->REG_ECH = 0x000000f4U;
        SCE->REG_ECH = 0x0000377cU;
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
            R_SCE_func101(0xc91d7184U, 0x21193a7dU, 0xd6243ba3U, 0xee90d6c5U);
            R_SCE_func300();
            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }
            R_SCE_func101(0x7c8eadaeU, 0x7dcb07ebU, 0x260f06b4U, 0x41d8a178U);
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
        R_SCE_func100(0xbc10b89dU, 0x39391c8cU, 0xe24b5d13U, 0x3c1a8ba2U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x432a1136U, 0xda828672U, 0x50fa59ecU, 0x561f4660U);
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
            R_SCE_func100(0xec9c2d1eU, 0xb6c118b9U, 0xbde212c7U, 0xcdfed6d5U);
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
            SCE->REG_ECH = 0x00000005U;
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
                R_SCE_func101(0x7f728af4U, 0x9ee9c0c1U, 0xb2c2115cU, 0x51d5f5aeU);
                R_SCE_func300();
                if (S_RAM[0] == 0x00000001U)
                {
                    break;
                }
                R_SCE_func101(0xdbd0a215U, 0x381d8b8aU, 0x1e5c7897U, 0xb706692fU);
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
            R_SCE_func100(0x6e8596f1U, 0x40c25e30U, 0xce5ac6a9U, 0x67388ce1U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x9ee0f0ecU, 0x59940651U, 0xedb5f553U, 0x5c33c111U);
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
                SCE->REG_100H = change_endian_long(0x000000f4U);
                R_SCE_func101(0x4fd23f3eU, 0x8ccf2e1cU, 0xaa410902U, 0x35952722U);
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
                R_SCE_func100(0x8034e0c2U, 0x1d984d4fU, 0x124cb87bU, 0x09f02c0cU);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    R_SCE_func102(0xb28ad0c6U, 0x5f17e046U, 0x18d69106U, 0xfcd9f238U);
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
                    SCE->REG_100H = change_endian_long(0x00000008U);
                    R_SCE_func101(0xcd2be246U, 0x764dbf66U, 0x5b73978aU, 0x3e5fc7caU);
                    R_SCE_func303();
                    R_SCE_func301();
                    R_SCE_func100(0x49ac0cc8U, 0x255c3125U, 0xff9b57cfU, 0xa1c1a0e7U);
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
                    SCE->REG_100H = change_endian_long(0x000000f4U);
                    R_SCE_func101(0x704820f0U, 0xbfaa4790U, 0xeb57dc91U, 0x134f733bU);
                    R_SCE_func043();
                    SCE->REG_ECH = 0x0000379bU;
                    R_SCE_func074_r1();
                    SCE->REG_ECH = 0x000034feU;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x000000f4U);
                    R_SCE_func101(0xfa1e3b20U, 0xa1b1b225U, 0xd9b69d10U, 0xa2e0dd0eU);
                    R_SCE_func044();
                    R_SCE_func100(0xd83ba1ccU, 0x1eee6285U, 0x1b2b6e07U, 0x6989a98cU);
                    SCE->REG_D0H = 0x40000100U;
                    SCE->REG_C4H = 0x02e087b7U;
                    SCE->REG_ECH = 0x0000b7e0U;
                    SCE->REG_ECH = 0x00000140U;
                    SCE->REG_E0H = 0x8188001fU;
                    SCE->REG_00H = 0x00002823U;
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
                    R_SCE_func100(0x7e889b5eU, 0xdd638f3dU, 0x9c2841e2U, 0xe10cc3b9U);
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
                    OutData_PrivKeyIndex[9] = SCE->REG_100H;
                    OutData_PrivKeyIndex[10] = SCE->REG_100H;
                    OutData_PrivKeyIndex[11] = SCE->REG_100H;
                    OutData_PrivKeyIndex[12] = SCE->REG_100H;
                    R_SCE_func100(0xcb315cd5U, 0xb29c331aU, 0x5698c4a9U, 0x57e92ceaU);
                    SCE->REG_E0H = 0x81010000U;
                    SCE->REG_04H = 0x00000606U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    OutData_PrivKeyIndex[0] = SCE->REG_100H;
                    R_SCE_func100(0xbdeab0a1U, 0x7e8f4addU, 0x19e92afdU, 0xa7945b04U);
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
                    SCE->REG_100H = change_endian_long(0x00000001U);
                    R_SCE_func101(0xa5f69687U, 0x0ff1f787U, 0x09eadd7eU, 0xa27b413aU);
                    R_SCE_func043();
                    R_SCE_func075_r1();
                    SCE->REG_ECH = 0x000034feU;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000002U);
                    R_SCE_func101(0x08a7c0d0U, 0x2be8f4e7U, 0x18659546U, 0x45c92644U);
                    R_SCE_func044();
                    R_SCE_func100(0x8f48872bU, 0x7b9007fbU, 0xc94927edU, 0x76ecbb1bU);
                    SCE->REG_D0H = 0x40000200U;
                    SCE->REG_C4H = 0x02e08887U;
                    SCE->REG_00H = 0x00002323U;
                    SCE->REG_2CH = 0x00000022U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_00H = 0x00002313U;
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
                    R_SCE_func100(0xc557b19bU, 0xdbbdcffbU, 0xf2f98ccaU, 0xff226369U);
                    SCE->REG_D0H = 0x40000000U;
                    SCE->REG_C4H = 0x00e08885U;
                    SCE->REG_00H = 0x00002313U;
                    /* WAIT_LOOP */
                    while (0U != SCE->REG_00H_b.B25)
                    {
                        /* waiting */
                    }
                    SCE->REG_1CH = 0x00001800U;
                    SCE->REG_104H = 0x00000052U;
                    SCE->REG_D0H = 0x40000000U;
                    SCE->REG_C4H = 0x000089c4U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000000U);
                    SCE->REG_04H = 0x00000222U;
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
                    R_SCE_func100(0x8b7e2612U, 0xd2051faaU, 0xb9904e1eU, 0x603d6860U);
                    SCE->REG_E0H = 0x81010000U;
                    SCE->REG_04H = 0x00000606U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    OutData_PubKeyIndex[0] = SCE->REG_100H;
                    R_SCE_func102(0x584df465U, 0x76e68729U, 0x9667a566U, 0x6c6f89e8U);
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

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pf4_r5.prc
***********************************************************************************************************************/
