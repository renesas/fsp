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

fsp_err_t R_SCE_Sha256HmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_MAC, uint32_t *InData_length, uint32_t *OutData_MAC)
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
    SCE->REG_74H = 0x00000000U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_00H = 0x00003523U;
    SCE->REG_74H = 0x00000008U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_7CH = 0x00000011U;
    SCE->REG_104H = 0x00000754U;
    SCE->REG_74H = 0x00000004U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x6a09e667U);
    SCE->REG_100H = change_endian_long(0xbb67ae85U);
    SCE->REG_100H = change_endian_long(0x3c6ef372U);
    SCE->REG_100H = change_endian_long(0xa54ff53aU);
    SCE->REG_100H = change_endian_long(0x510e527fU);
    SCE->REG_100H = change_endian_long(0x9b05688cU);
    SCE->REG_100H = change_endian_long(0x1f83d9abU);
    SCE->REG_100H = change_endian_long(0x5be0cd19U);
    SCE->REG_74H = 0x00000002U;
    R_SCE_func002();
    SCE->REG_00H = 0x00005323U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_104H = 0x00000054U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x80000000U);
    SCE->REG_F8H = 0x00000040U;
    SCE->REG_104H = 0x00000154U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000300U);
    /* WAIT_LOOP */
    while (0U != SCE->REG_74H_b.B18)
    {
        /* waiting */
    }
    SCE->REG_74H = 0x00000000U;
    SCE->REG_1CH = 0x00001600U;
    SCE->REG_E0H = 0x80010000U;
    SCE->REG_104H = 0x00000068U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_Cmd[0];
    SCE->REG_ECH = 0x38000c00U;
    SCE->REG_ECH = 0x1000b780U;
    SCE->REG_ECH = 0x00002000U;
    SCE->REG_ECH = 0x2000b780U;
    SCE->REG_ECH = 0x00001000U;
    SCE->REG_ECH = 0x38000f9bU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    R_SCE_func100(0x8ed66e4dU, 0x615bc8d3U, 0x8a006271U, 0x7d6cfe05U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x0f463b4dU, 0x16904ff1U, 0xd88fe44bU, 0x04b5ff30U);
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
        SCE->REG_ECH = 0x38000c00U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0xf518bd90U, 0xd723455eU, 0xa4c21b91U, 0xe70a347cU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func100(0x6c3eda06U, 0xfabde0adU, 0xb0a7a91bU, 0x14627794U);
            SCE->REG_74H = 0x00000008U;
            SCE->REG_04H = 0x00000523U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_04H_b.B30)
            {
                /* waiting */
            }
            OutData_MAC[0] = SCE->REG_100H;
            OutData_MAC[1] = SCE->REG_100H;
            OutData_MAC[2] = SCE->REG_100H;
            OutData_MAC[3] = SCE->REG_100H;
            OutData_MAC[4] = SCE->REG_100H;
            OutData_MAC[5] = SCE->REG_100H;
            OutData_MAC[6] = SCE->REG_100H;
            OutData_MAC[7] = SCE->REG_100H;
            R_SCE_func102(0x7632454fU, 0xd66a870dU, 0x37b6ae62U, 0xca4a4017U);
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
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_length[0];
            SCE->REG_ECH = 0x3420a820U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_ECH = 0x3420a820U;
            SCE->REG_ECH = 0x00000021U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            R_SCE_func100(0x9bba432fU, 0x90ff31d8U, 0xd20bc5ebU, 0x3bad6d87U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x25dc0061U, 0xe51833a0U, 0x33b95ac2U, 0x909bf44bU);
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
                SCE->REG_ECH = 0x00000bffU;
                SCE->REG_E0H = 0x8088001fU;
                SCE->REG_00H = 0x00008523U;
                SCE->REG_74H = 0x00000008U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x00000800U;
                for (iLoop = 0; iLoop < 32; iLoop = iLoop+1)
                {
                    SCE->REG_ECH = 0x3c002be1U;
                    SCE->REG_ECH = 0x12003c1fU;
                    SCE->REG_ECH = 0x00002fe0U;
                }
                SCE->REG_A4H = 0x00040805U;
                SCE->REG_ECH = 0x00000bffU;
                SCE->REG_E0H = 0x8188001fU;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_A4H = 0x00050805U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000761U;
                SCE->REG_A4H = 0x00900c05U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_MAC[0];
                SCE->REG_100H = InData_MAC[1];
                SCE->REG_100H = InData_MAC[2];
                SCE->REG_100H = InData_MAC[3];
                SCE->REG_A4H = 0x00900c45U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_MAC[4];
                SCE->REG_100H = InData_MAC[5];
                SCE->REG_100H = InData_MAC[6];
                SCE->REG_100H = InData_MAC[7];
                R_SCE_func100(0x29c4a913U, 0xa12e9e66U, 0x89c4a9d0U, 0x54429e24U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    R_SCE_func102(0x6b8cef9cU, 0x78c8da32U, 0x10d7f8b7U, 0x46c192d6U);
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
                    R_SCE_func102(0xd8d9c817U, 0x307becf7U, 0xd9349aabU, 0x873ecdf7U);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p76f_r2.prc
***********************************************************************************************************************/
