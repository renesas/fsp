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

fsp_err_t HW_SCE_Sha256HmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_MAC, uint32_t *InData_length, uint32_t *OutData_MAC)
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
    HW_SCE_p_func002();
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
    HW_SCE_p_func100(0x5645d712U, 0xf440c1a2U, 0x355c8516U, 0x48ad4f74U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x9f0753abU, 0x672d8e04U, 0x33faac82U, 0xa4233a9eU);
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
        HW_SCE_p_func100(0x63745b29U, 0xaebe8cc7U, 0x7085ee73U, 0x8e5d85a1U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func100(0x5b5be3a7U, 0x336987a4U, 0x9aa80c8cU, 0x48f5e12aU);
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
            HW_SCE_p_func102(0xf3b0da21U, 0xaa2c1883U, 0x81dcbe92U, 0x1211e78fU);
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
            HW_SCE_p_func100(0x787f2c3cU, 0x51494157U, 0x8d21dbdaU, 0xae4b1106U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0x48ebd1e7U, 0x8950bad9U, 0xacd6fb88U, 0x66f4b1edU);
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
                HW_SCE_p_func100(0xfcc31f34U, 0x1b5c3390U, 0x9e47672dU, 0x93c96d76U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    HW_SCE_p_func102(0x7db6d140U, 0xac1e40a8U, 0x55d31ba6U, 0xdf750b0bU);
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
                    HW_SCE_p_func102(0x8e622b72U, 0x844d725fU, 0xd2e4a8e7U, 0x6bff87e6U);
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
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p76f_r1.prc
***********************************************************************************************************************/
