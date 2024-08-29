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

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV)
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
    uint32_t InData_DataType[1] = {0};
    uint32_t InData_Cmd[1]      = {0};
    uint32_t InData_SeqNum[2]   = {0, 0};
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
    SCE->REG_84H = 0x00002902U;
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
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010100U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38008900U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x6b382aa4U, 0x33174681U, 0xefbf17aeU, 0x06fadd5bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xe522b6b7U, 0x4f9df3d1U, 0x8bf4a601U, 0x8588e7f8U);
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
        SCE->REG_ECH = 0x38000d08U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        SCE->REG_ECH = 0x38008900U;
        SCE->REG_ECH = 0x00000002U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x0bde1b8fU, 0x7b7dd407U, 0xe9706775U, 0x5a99bf42U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[0];
            SCE->REG_ECH = 0x38000d08U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x4c369988U, 0x4f4d8a68U, 0x1bc827d6U, 0x7a926df4U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000029U);
                HW_SCE_p_func101(0x052b7216U, 0x91f9cb7eU, 0xa126049fU, 0x464ed006U);
                HW_SCE_p_func043();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000005U;
                HW_SCE_p_func101(0xe901524bU, 0x3472aa7bU, 0xaba040b0U, 0xa105b27bU);
            }
            else
            {
                SCE->REG_ECH = 0x00003547U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000029U);
                HW_SCE_p_func101(0x0305165dU, 0x12770d2cU, 0x638119d4U, 0xab9f838cU);
                HW_SCE_p_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x0146c04bU;
                HW_SCE_p_func101(0xe420a06fU, 0x2d5c4d73U, 0x07a4a937U, 0x9a0afc88U);
            }
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000029U);
            HW_SCE_p_func101(0x41acb932U, 0x1a93d263U, 0x1040891fU, 0x85c5664eU);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0xd177a4d2U, 0x55fd89a4U, 0x4101c1d1U, 0xdbacd9feU);
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x02f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[1];
            SCE->REG_100H = InData_KeyIndex[2];
            SCE->REG_100H = InData_KeyIndex[3];
            SCE->REG_100H = InData_KeyIndex[4];
            SCE->REG_A4H = 0x00080805U;
            SCE->REG_00H = 0x00001213U;
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
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_104H = 0x00000368U;
            SCE->REG_E0H = 0x80040080U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[0];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[1];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[2];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_IV[3];
            HW_SCE_p_func101(0x7c240052U, 0x386c9704U, 0xb361b7ffU, 0x1e4f00bfU);
        }
        else
        {
            SCE->REG_ECH = 0x38008900U;
            SCE->REG_ECH = 0x00000001U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xf7f5d62fU, 0xd414c789U, 0x62d34fcaU, 0xa08c4049U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000368U;
                SCE->REG_E0H = 0x80040000U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[1];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[2];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[3];
                SCE->REG_ECH = 0x00000bdeU;
                SCE->REG_ECH = 0x000037e0U;
                SCE->REG_ECH = 0x00008fe0U;
                SCE->REG_ECH = 0x00ff0000U;
                SCE->REG_ECH = 0x38008be0U;
                SCE->REG_ECH = 0x00120000U;
                SCE->REG_ECH = 0x1000d3c0U;
                SCE->REG_ECH = 0x3800d80fU;
                SCE->REG_ECH = 0x2000d3c1U;
                SCE->REG_ECH = 0x000037e0U;
                SCE->REG_ECH = 0x00008fe0U;
                SCE->REG_ECH = 0x000000feU;
                SCE->REG_ECH = 0x38008be0U;
                SCE->REG_ECH = 0x00000000U;
                SCE->REG_ECH = 0x1000d3c2U;
                SCE->REG_ECH = 0x38008bc0U;
                SCE->REG_ECH = 0x00000007U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00A60000U;
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
                SCE->REG_100H = change_endian_long(0x00000029U);
                HW_SCE_p_func101(0x0e8dc5a7U, 0xb49ecf91U, 0x36535c56U, 0x9d795f50U);
                HW_SCE_p_func059();
                HW_SCE_p_func100(0x85c33db3U, 0xfaf76717U, 0x874d3287U, 0x50161587U);
                SCE->REG_104H = 0x00000362U;
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x02f087b5U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[4];
                SCE->REG_100H = InData_KeyIndex[5];
                SCE->REG_100H = InData_KeyIndex[6];
                SCE->REG_100H = InData_KeyIndex[7];
                SCE->REG_A4H = 0x00080805U;
                SCE->REG_00H = 0x00001213U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000362U;
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x00f087b5U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[8];
                SCE->REG_100H = InData_KeyIndex[9];
                SCE->REG_100H = InData_KeyIndex[10];
                SCE->REG_100H = InData_KeyIndex[11];
                SCE->REG_E0H = 0x80040080U;
                SCE->REG_00H = 0x00008213U;
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
                SCE->REG_100H = InData_KeyIndex[12];
                SCE->REG_100H = InData_KeyIndex[13];
                SCE->REG_100H = InData_KeyIndex[14];
                SCE->REG_100H = InData_KeyIndex[15];
                SCE->REG_C4H = 0x00900c45U;
                SCE->REG_00H = 0x00002213U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func101(0x3f2fe7f5U, 0x739749ffU, 0x44e9ba49U, 0x61bce77aU);
            }
            else
            {
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x80010140U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[0];
                SCE->REG_104H = 0x00000068U;
                SCE->REG_E0H = 0x80010020U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_DataType[0];
                SCE->REG_ECH = 0x38000c21U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                HW_SCE_p_func100(0xeff93c39U, 0x77b1edbcU, 0x4f973ac1U, 0x672ecef6U);
                SCE->REG_1CH = 0x00400000U;
                SCE->REG_1D0H = 0x00000000U;
                if (1U == (SCE->REG_1CH_b.B22))
                {
                    SCE->REG_104H = 0x00000068U;
                    SCE->REG_E0H = 0x80010000U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = InData_Cmd[0];
                    SCE->REG_ECH = 0x000036a0U;
                    SCE->REG_ECH = 0x0000b6c0U;
                    SCE->REG_ECH = 0x01c18a1aU;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x00000029U);
                    HW_SCE_p_func101(0x89e3d905U, 0x08b0f537U, 0xc476c938U, 0x75c7d7b7U);
                    HW_SCE_p_func082();
                    HW_SCE_p_func101(0xe8b5a5cfU, 0xfa50c674U, 0x343c3f83U, 0xe8899844U);
                }
                else
                {
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x000000edU);
                    HW_SCE_p_func101(0x01b680e5U, 0x22cf6c6aU, 0xe9ae05ecU, 0x4cbb570eU);
                    HW_SCE_p_func068();
                    SCE->REG_ECH = 0x0000b4e0U;
                    SCE->REG_ECH = 0x01d6575eU;
                    SCE->REG_104H = 0x00000058U;
                    SCE->REG_E0H = 0x800103a0U;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = change_endian_long(0x000000edU);
                    HW_SCE_p_func101(0x22447b96U, 0x29e0435bU, 0x2fc3a7feU, 0xb6c60312U);
                    HW_SCE_p_func044();
                    HW_SCE_p_func101(0x6e4d01daU, 0x0527013aU, 0x6981610fU, 0xb912b293U);
                }
                SCE->REG_104H = 0x00000168U;
                SCE->REG_E0H = 0x80020360U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_SeqNum[0];
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_SeqNum[1];
                HW_SCE_p_func100(0xbb207189U, 0x5c201d05U, 0x5555ed55U, 0xda785248U);
                SCE->REG_104H = 0x00000362U;
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x02f087b5U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[1];
                SCE->REG_100H = InData_KeyIndex[2];
                SCE->REG_100H = InData_KeyIndex[3];
                SCE->REG_100H = InData_KeyIndex[4];
                SCE->REG_A4H = 0x00080805U;
                SCE->REG_00H = 0x00001213U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000362U;
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x00f087b5U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_KeyIndex[5];
                SCE->REG_100H = InData_KeyIndex[6];
                SCE->REG_100H = InData_KeyIndex[7];
                SCE->REG_100H = InData_KeyIndex[8];
                SCE->REG_E0H = 0x80040080U;
                SCE->REG_00H = 0x00008213U;
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
                SCE->REG_100H = InData_KeyIndex[9];
                SCE->REG_100H = InData_KeyIndex[10];
                SCE->REG_100H = InData_KeyIndex[11];
                SCE->REG_100H = InData_KeyIndex[12];
                SCE->REG_C4H = 0x00900c45U;
                SCE->REG_00H = 0x00002213U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                HW_SCE_p_func101(0x3fcf986cU, 0x93ab7bdaU, 0x7568a4b5U, 0x17ae5806U);
            }
            HW_SCE_p_func101(0xe857747eU, 0x860c8888U, 0x1a7b13d1U, 0x87d92187U);
        }
        HW_SCE_p_func100(0x8bff74d4U, 0x226b6052U, 0x135a49e1U, 0xaf348c2bU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x66eabf73U, 0xf41d1e94U, 0xf9a72548U, 0x06165eacU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            SCE->REG_ECH = 0x3000a900U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_ECH = 0x00010020U;
            SCE->REG_ECH = 0x000008bbU;
            SCE->REG_ECH = 0x000008dcU;
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x00000001U;
            SCE->REG_ECH = 0x00000080U;
            SCE->REG_7CH = 0x00000001U;
            SCE->REG_7CH = 0x00000041U;
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00000a84U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_00H = 0x00005113U;
            SCE->REG_74H = 0x00001000U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_74H = 0x00000004U;
            SCE->REG_104H = 0x00000354U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_74H = 0x00000002U;
            HW_SCE_p_func101(0xdd6d541cU, 0x9bcf665cU, 0x1cdc93f5U, 0xf6d0f1c1U);
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p29i_r3.prc
***********************************************************************************************************************/
