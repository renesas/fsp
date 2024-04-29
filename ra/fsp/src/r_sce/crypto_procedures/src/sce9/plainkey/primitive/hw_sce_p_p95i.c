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

fsp_err_t HW_SCE_Aes128CcmEncryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_DataType, uint32_t *InData_Cmd, uint32_t *InData_TextLen, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header, uint32_t Header_Len, uint32_t *InData_SeqNum)
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
    SCE->REG_84H = 0x00009502U;
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
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0xb6d3d7aeU, 0x03f459d0U, 0x3cb9783aU, 0x1f0c76d4U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x3420a920U;
        SCE->REG_ECH = 0x00004101U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_p_func101(0xdce8ab0eU, 0xea170c82U, 0x65b077c3U, 0x3bddd9b6U);
    }
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000001U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_ECH = 0x38008800U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x32a26b65U, 0xe0b80ac4U, 0x386ec472U, 0x7f816533U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x7d1776bfU, 0x1c374f67U, 0xa4abd4c9U, 0x340bd235U);
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
        HW_SCE_p_func100(0x7c069788U, 0x57b0ae31U, 0xd9b2d6b4U, 0x38682636U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x38000c00U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xdf48dc71U, 0x74c3a437U, 0x094587f5U, 0xe7bee5d9U);
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
                SCE->REG_100H = change_endian_long(0x00000095U);
                HW_SCE_p_func101(0x083336eeU, 0x60b8c114U, 0x03ec69fcU, 0x96f1bc4eU);
                HW_SCE_p_func043();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000005U;
                HW_SCE_p_func101(0x44f176b3U, 0x0542a71eU, 0xf9677c0aU, 0xd57ffb5eU);
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
                SCE->REG_100H = change_endian_long(0x00000095U);
                HW_SCE_p_func101(0xc3d74994U, 0x2396f33aU, 0xde076f70U, 0x45910600U);
                HW_SCE_p_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x0146c04bU;
                HW_SCE_p_func101(0x4578cdf9U, 0x8cc5940bU, 0xfaee4bbdU, 0x999d9911U);
            }
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000095U);
            HW_SCE_p_func101(0x8a77630fU, 0x85838b13U, 0xacf95c17U, 0x3f5a3bffU);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0x29ccfd70U, 0x5f7a7f3fU, 0x1309d3e3U, 0xb3c106beU);
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
            HW_SCE_p_func101(0xaae410a7U, 0xf00e5a90U, 0x2410ec74U, 0x265bc778U);
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
            HW_SCE_p_func100(0xa0286701U, 0x7b258d53U, 0x952230bdU, 0xc64fe911U);
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
                SCE->REG_100H = change_endian_long(0x00000095U);
                HW_SCE_p_func101(0x645e69f2U, 0xbb125192U, 0xbe8a99eaU, 0x02067853U);
                HW_SCE_p_func082();
                HW_SCE_p_func101(0x99be7b5dU, 0xbef7c002U, 0xac667246U, 0xc6be6bfdU);
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
                SCE->REG_100H = change_endian_long(0x000000dfU);
                HW_SCE_p_func101(0xde1dd999U, 0x6cb89cd2U, 0x825102d6U, 0x8c8555ddU);
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
                SCE->REG_100H = change_endian_long(0x000000ebU);
                HW_SCE_p_func101(0x8c9e99e9U, 0x37554738U, 0xcdd61cb4U, 0xc8924910U);
                HW_SCE_p_func044();
                HW_SCE_p_func101(0x1cdebdebU, 0x9c5b7556U, 0xa53a1999U, 0x848fff3bU);
            }
            HW_SCE_p_func100(0x3e45fc6dU, 0x962c09ddU, 0x093b46c2U, 0xd3969b66U);
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
            HW_SCE_p_func101(0x84dc3d3eU, 0x5acc7e85U, 0xbda14854U, 0x01d016b8U);
        }
        HW_SCE_p_func100(0xff548021U, 0x70e8fca7U, 0x696ff4ccU, 0x000e04a5U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0x8234135dU, 0xa43a55aaU, 0x5977549aU, 0x775bd901U);
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
            SCE->REG_ECH = 0x00003412U;
            SCE->REG_ECH = 0x3420a800U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0xb1ccfaaeU, 0x6226c18cU, 0x059a3b6cU, 0xd3236dfaU);
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
                HW_SCE_p_func101(0x2f96d604U, 0xcd1b75c6U, 0xf083c04aU, 0x4221e51cU);
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
                SCE->REG_ECH = 0x0000b540U;
                SCE->REG_ECH = 0x00000010U;
                HW_SCE_p_func031(InData_Header);
                HW_SCE_p_func101(0x8c6ae1adU, 0x18269089U, 0x59571e54U, 0xedaa9de2U);
            }
            HW_SCE_p_func100(0x6c603327U, 0xae7570afU, 0x2a39d291U, 0x98fd10adU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                HW_SCE_p_func102(0xecf7f101U, 0xea31c459U, 0x69c3a2daU, 0x0c3a9ff1U);
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
                HW_SCE_p_func101(0x733fa2afU, 0xd52b796fU, 0x99673d12U, 0xd9024448U);
                return FSP_SUCCESS;
            }
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p95i_r2.prc
***********************************************************************************************************************/
