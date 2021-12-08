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

fsp_err_t R_SCE_TlsGeneratePreMasterSecretSub(uint32_t *OutData_PreMasterSecret)
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
    SCE->REG_84H = 0x0000e302U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_C4H = 0x200e1a0dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[20+0 + 0];
    SCE->REG_100H = S_RAM[20+0 + 1];
    SCE->REG_100H = S_RAM[20+0 + 2];
    SCE->REG_100H = S_RAM[20+0 + 3];
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000070U;
    SCE->REG_ECH = 0x00003441U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000010U;
    R_SCE_func100(0x859b003bU, 0x8cbaa106U, 0xacb2f580U, 0xc319a807U);
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80840001U;
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00002420U;
    R_SCE_func100(0x6a612639U, 0x0c8f9f71U, 0x68cbfc56U, 0xfa4eabb2U);
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80840001U;
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00002420U;
    R_SCE_func100(0x16b25d08U, 0xde9e5bdeU, 0x53b7658eU, 0x991d9670U);
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80840001U;
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00003422U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000303U;
    SCE->REG_ECH = 0x01003c01U;
    R_SCE_func100(0x5ee4705bU, 0x4ced1fecU, 0xeb52b6b3U, 0xad23577dU);
    R_SCE_func103();
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_E0H = 0x80040000U;
    SCE->REG_00H = 0x00008213U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00003540U;
    SCE->REG_ECH = 0x00003561U;
    SCE->REG_ECH = 0x00003582U;
    SCE->REG_ECH = 0x000035a3U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000e3U);
    R_SCE_func101(0x4d905202U, 0xfc30a9f0U, 0x6d1b0354U, 0x9dec6a9bU);
    R_SCE_func059();
    SCE->REG_E0H = 0x81040000U;
    SCE->REG_C4H = 0x00060805U;
    SCE->REG_00H = 0x00002813U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b4e0U;
    SCE->REG_ECH = 0x0154569cU;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x800103a0U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x000000e3U);
    R_SCE_func101(0x330a8f2bU, 0x7da8d6c6U, 0xa258f5cfU, 0x3b3f78c9U);
    R_SCE_func044();
    R_SCE_func100(0xd7bf3fd4U, 0x9fd30b57U, 0x97867224U, 0xfc437c46U);
    SCE->REG_D0H = 0x40000200U;
    SCE->REG_C4H = 0x02e087b7U;
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000070U;
    SCE->REG_E0H = 0x818c0001U;
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
    OutData_PreMasterSecret[4] = SCE->REG_100H;
    OutData_PreMasterSecret[5] = SCE->REG_100H;
    OutData_PreMasterSecret[6] = SCE->REG_100H;
    OutData_PreMasterSecret[7] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PreMasterSecret[8] = SCE->REG_100H;
    OutData_PreMasterSecret[9] = SCE->REG_100H;
    OutData_PreMasterSecret[10] = SCE->REG_100H;
    OutData_PreMasterSecret[11] = SCE->REG_100H;
    /* WAIT_LOOP */
    while (1U != SCE->REG_04H_b.B30)
    {
        /* waiting */
    }
    OutData_PreMasterSecret[12] = SCE->REG_100H;
    OutData_PreMasterSecret[13] = SCE->REG_100H;
    OutData_PreMasterSecret[14] = SCE->REG_100H;
    OutData_PreMasterSecret[15] = SCE->REG_100H;
    R_SCE_func100(0xf0b143e2U, 0x21b3f041U, 0xf361845fU, 0x47796392U);
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
    OutData_PreMasterSecret[16] = SCE->REG_100H;
    OutData_PreMasterSecret[17] = SCE->REG_100H;
    OutData_PreMasterSecret[18] = SCE->REG_100H;
    OutData_PreMasterSecret[19] = SCE->REG_100H;
    R_SCE_func100(0x42f7380cU, 0x3a2937c7U, 0xd0d22060U, 0x505c1df5U);
    SCE->REG_104H = 0x00000052U;
    SCE->REG_C4H = 0x01000c84U;
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
    OutData_PreMasterSecret[0] = SCE->REG_100H;
    OutData_PreMasterSecret[1] = SCE->REG_100H;
    OutData_PreMasterSecret[2] = SCE->REG_100H;
    OutData_PreMasterSecret[3] = SCE->REG_100H;
    R_SCE_func102(0x843f5e60U, 0x8b89b89cU, 0xad49c1cbU, 0x07db4a0fU);
    SCE->REG_1BCH = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_18H_b.B12)
    {
        /* waiting */
    }
    return FSP_SUCCESS;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_pe3_r2.prc
***********************************************************************************************************************/
