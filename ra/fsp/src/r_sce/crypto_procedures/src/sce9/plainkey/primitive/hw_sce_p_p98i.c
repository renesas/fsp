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

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_DataType, uint32_t *InData_Cmd, uint32_t *InData_TextLen, uint32_t *InData_MACLength, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header, uint32_t Header_Len, uint32_t *InData_SeqNum)
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
    SCE->REG_84H = 0x00009802U;
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
    SCE->REG_E0H = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x00003640U;
    SCE->REG_104H = 0x00000068U;
    SCE->REG_E0H = 0x80010120U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = InData_TextLen[0];
    SCE->REG_ECH = 0x00003689U;
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xfe107021U, 0x2c0bf976U, 0x0a0ae754U, 0x1e187b81U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_104H = 0x00000068U;
        SCE->REG_E0H = 0x80010140U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_MACLength[0];
        HW_SCE_p_func101(0x3c23d9a5U, 0x7bbd6cf0U, 0x954672a7U, 0xff301ed1U);
    }
    else
    {
        SCE->REG_ECH = 0x0000b540U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_ECH = 0x3420a920U;
        SCE->REG_ECH = 0x00004101U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func101(0xf28b6b15U, 0x24b88936U, 0x4951718eU, 0x8e28568eU);
    }
    SCE->REG_ECH = 0x0000366aU;
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000001U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xbd03be63U, 0x5acfa017U, 0x59c64d67U, 0xbe89ce07U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0xae46d292U, 0x9874cb67U, 0x2f89dc77U, 0xeff862dcU);
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
        SCE->REG_ECH = 0x3420a800U;
        SCE->REG_ECH = 0x00000004U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x09231be9U, 0x79a7045fU, 0x8615bd3cU, 0x92350c8fU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x38000c00U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x7e64c5d2U, 0xe0328a9cU, 0xdc55cc93U, 0xdc40b046U);
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
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000098U);
                HW_SCE_p_func101(0xbe95e98fU, 0x7b14d868U, 0x22a9108bU, 0x3bdfa7caU);
                HW_SCE_p_func043();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000005U;
                HW_SCE_p_func101(0xe1c588a8U, 0xa185ea37U, 0x92a8ebc2U, 0xc6ba3e53U);
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
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000098U);
                HW_SCE_p_func101(0xeb42863fU, 0x3cb151c3U, 0x49401fc4U, 0x89c0987dU);
                HW_SCE_p_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x0146c04bU;
                HW_SCE_p_func101(0xa49f0b45U, 0xd0e46b3fU, 0x49506eb0U, 0xd0040c29U);
            }
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000098U);
            HW_SCE_p_func101(0xbc08b804U, 0x074e9f88U, 0xdf36e17aU, 0x02c44201U);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0x5ee543bbU, 0xbe019c49U, 0x44a68e5fU, 0xf3593618U);
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
            HW_SCE_p_func101(0x5b0413a5U, 0xa11b707fU, 0xedf9c29dU, 0xda19fd49U);
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
            HW_SCE_p_func100(0xe3098454U, 0xc5646dafU, 0x43b2527cU, 0x7b5261bbU);
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
                SCE->REG_ECH = 0x0126ee7fU;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000098U);
                HW_SCE_p_func101(0x4e489fcfU, 0x7cfb3977U, 0xa5adde78U, 0x250da5b6U);
                HW_SCE_p_func082();
                HW_SCE_p_func101(0x59da29ceU, 0x415bccc5U, 0xe8dfcb7cU, 0xb3723783U);
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
                SCE->REG_100H = change_endian_long(0x00000003U);
                HW_SCE_p_func101(0x7ea7e6a2U, 0xc14df11eU, 0xd569df01U, 0x574f3714U);
                HW_SCE_p_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x01bae316U;
                SCE->REG_104H = 0x00000058U;
                SCE->REG_E0H = 0x800103a0U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x000000ccU);
                HW_SCE_p_func101(0x4fd122aeU, 0x6ada8620U, 0xc9d4c5d4U, 0xf5c020a0U);
                HW_SCE_p_func044();
                HW_SCE_p_func101(0xf8e909e8U, 0x331dcfacU, 0xa20d2e22U, 0xc7fc901bU);
            }
            HW_SCE_p_func100(0x11a07849U, 0x2d785852U, 0x5c07f7f2U, 0xdbf9049aU);
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
            HW_SCE_p_func101(0x4848b446U, 0x27c3f86dU, 0xebb9a2edU, 0x8234670cU);
        }
        HW_SCE_p_func100(0xf37c41eaU, 0x7aab28dfU, 0x4f0813bbU, 0x6fb28ef5U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x9d0c2ad1U, 0x2653702aU, 0xc270905cU, 0xbdfc186cU);
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
            SCE->REG_ECH = 0x00003534U;
            SCE->REG_ECH = 0x00003553U;
            SCE->REG_ECH = 0x00003412U;
            SCE->REG_ECH = 0x3420a800U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xc912f1edU, 0x89adc8ebU, 0xebc24832U, 0x23f70182U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00040885U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_IV[0];
                SCE->REG_100H = InData_IV[1];
                SCE->REG_100H = InData_IV[2];
                SCE->REG_100H = InData_IV[3];
                SCE->REG_A4H = 0x00060805U;
                SCE->REG_00H = 0x00001113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00000734U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00050804U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x000000b1U;
                SCE->REG_A4H = 0x00f00806U;
                for (iLoop = 0; iLoop < Header_Len; iLoop = iLoop + 4)
                {
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_104H_b.B31)
                    {
                        /* waiting */
                    }
                    SCE->REG_100H = InData_Header[iLoop + 0];
                    SCE->REG_100H = InData_Header[iLoop + 1];
                    SCE->REG_100H = InData_Header[iLoop + 2];
                    SCE->REG_100H = InData_Header[iLoop + 3];
                }
                HW_SCE_p_func205();//DisableINTEGRATE_WRRDYBinthisfunction.
                HW_SCE_p_func101(0x682f0742U, 0x7794d1a8U, 0x2c15c7acU, 0x13c0d6c9U);
            }
            else
            {
                SCE->REG_104H = 0x00000168U;
                SCE->REG_E0H = 0x800201c0U;
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
                SCE->REG_ECH = 0x000008aeU;
                SCE->REG_ECH = 0x000008cfU;
                SCE->REG_ECH = 0x0000b460U;
                SCE->REG_ECH = 0x00000002U;
                SCE->REG_ECH = 0x01986c64U;
                SCE->REG_ECH = 0x01986c85U;
                SCE->REG_ECH = 0x01986ca6U;
                SCE->REG_ECH = 0x00186cc6U;
                SCE->REG_A4H = 0x00040885U;
                SCE->REG_E0H = 0x81040060U;
                SCE->REG_00H = 0x00001813U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_A4H = 0x00060805U;
                SCE->REG_00H = 0x00001113U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00000734U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                SCE->REG_104H = 0x00000051U;
                SCE->REG_A4H = 0x00050804U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = change_endian_long(0x00000000U);
                HW_SCE_p_func031(InData_Header);
                HW_SCE_p_func101(0x70b3f957U, 0x0e7e6b9cU, 0xa46cfd01U, 0xce71fd1bU);
            }
            HW_SCE_p_func100(0xb06f69d5U, 0xdac52fbaU, 0xdaf8b050U, 0x579e944cU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xba154afaU, 0x74164f03U, 0x73419898U, 0x92ca8b80U);
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
                HW_SCE_p_func101(0xdfba0f27U, 0x0eb92c21U, 0xf0a41467U, 0xe83e652fU);
                return FSP_SUCCESS;
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p98i_r2.prc
***********************************************************************************************************************/
