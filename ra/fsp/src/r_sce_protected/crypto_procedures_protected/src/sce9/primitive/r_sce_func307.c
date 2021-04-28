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

void R_SCE_func307(void)
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000090U;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000080U;
    R_SCE_func101(0x89e510feU, 0x394c1c77U, 0xd552f2e2U, 0x6ac5d5aaU);
    R_SCE_func311();
    SCE->REG_ECH = 0x00000a73U;
    SCE->REG_ECH = 0x00000a31U;
    for(jLoop = 0; jLoop < 32; jLoop = jLoop + 1)
    {
        SCE->REG_ECH = 0x00002e20U;
        SCE->REG_ECH = 0x38002673U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func100(0x61daf1ddU, 0x3ee980fbU, 0xcdef1fceU, 0x18899658U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0x0086bf00U, 0xf2bc533fU, 0x8f0aba9aU, 0x051899ccU);
        }
        else
        {
            R_SCE_func100(0x2bfa9d5fU, 0x2dc12fecU, 0x52a3134cU, 0x319750beU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            R_SCE_func080();
            R_SCE_func100(0x3a2013c3U, 0xd669fc60U, 0xeb24818dU, 0xaea9b0c6U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000010U;
            R_SCE_func312(204);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            R_SCE_func080();
            R_SCE_func100(0x1181c28cU, 0xfbff07a7U, 0xa43865ddU, 0xce1e7827U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            R_SCE_func312(136);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01a67f45U);
            R_SCE_func080();
            R_SCE_func100(0x2ca72a98U, 0xa3faf9e9U, 0x4c2440b8U, 0x7805dbe7U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func313(476);
            R_SCE_func100(0x2e5a1e50U, 0x2bfda642U, 0x5911957cU, 0xe6bbfd15U);
            R_SCE_func314(476+64);
            R_SCE_func100(0x38550e61U, 0xca22047aU, 0x734955faU, 0x881bdd0cU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019fce91U);
            R_SCE_func080();
            R_SCE_func100(0x4a6f1244U, 0x6f2b65a2U, 0x14ad6998U, 0x94d29709U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func313(612);
            R_SCE_func100(0xb02e1c9dU, 0x81d2d607U, 0x19430f7eU, 0x51961d36U);
            R_SCE_func314(612+64);
            R_SCE_func100(0x40e9e6b1U, 0x64a3945eU, 0xa63fc42bU, 0xc2a79424U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011f5dcdU);
            R_SCE_func080();
            R_SCE_func100(0x62fb4204U, 0x8290c756U, 0xc455a66bU, 0x7caef83eU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func313(408);
            R_SCE_func100(0xc82c09c6U, 0x0241efeaU, 0x420d1d29U, 0xaeb0e145U);
            R_SCE_func314(408+64);
            R_SCE_func100(0xec5c5ffbU, 0x5abee79eU, 0x1a441a53U, 0x60c468e9U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01e59c3dU);
            R_SCE_func080();
            R_SCE_func100(0x13968a26U, 0x8c211329U, 0xb83768a4U, 0xd8693026U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func313(544);
            R_SCE_func100(0x10a68846U, 0x08636b6fU, 0x5ae4fa29U, 0x822e4f1fU);
            R_SCE_func314(544+64);
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x00000081U;
            R_SCE_func101(0x59e2797cU, 0x9b3a97d6U, 0x0d8cad4cU, 0xccf47f58U);
            R_SCE_func309();
            R_SCE_func100(0x4d425083U, 0xab1bd6e2U, 0x32f75dc3U, 0x0a0d3f01U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            R_SCE_func080();
            R_SCE_func100(0xc2fcfbe0U, 0x2af3b8a4U, 0x7c6bc05dU, 0xf82d796aU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func313(204);
            R_SCE_func100(0x57639e92U, 0x0bbfedcaU, 0x2ce6433cU, 0x99e24a79U);
            R_SCE_func314(204+64);
            R_SCE_func100(0xa7b2a175U, 0xe220547eU, 0xa0200b97U, 0x842e0187U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            R_SCE_func080();
            R_SCE_func100(0xaf2aef4eU, 0xa21fd2e4U, 0x85719cb1U, 0xfef6ad92U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func313(136);
            R_SCE_func100(0x930d52b5U, 0xdcf0bf05U, 0x4217e47dU, 0x865a86cdU);
            R_SCE_func314(136+64);
            R_SCE_func101(0x6afebc6fU, 0x01926f79U, 0xc2bb4135U, 0xe1777db3U);
        }
        SCE->REG_ECH = 0x3800da9fU;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        R_SCE_func100(0xd131ee14U, 0x0560e33cU, 0xdf44e4ccU, 0x2af89076U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (0U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func101(0xcbf6dbc7U, 0x0fa7a039U, 0xc8445df8U, 0x636729feU);
        }
        else
        {
            R_SCE_func100(0x09140813U, 0xc3224ddfU, 0xe4c93453U, 0x7945f068U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            R_SCE_func080();
            R_SCE_func100(0x2424db58U, 0x7ffb18a8U, 0x9f76e498U, 0xd416be93U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000010U;
            R_SCE_func312(204);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            R_SCE_func080();
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            R_SCE_func312(136);
            R_SCE_func100(0xf4795071U, 0xeab4e990U, 0xa5b67fdaU, 0xd4b2759fU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01a67f45U);
            R_SCE_func080();
            R_SCE_func100(0x884a8911U, 0x3acaf644U, 0xfda7ca34U, 0x1d7d19cfU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func313(476);
            R_SCE_func100(0x56381697U, 0xc6ee8f18U, 0xed459860U, 0xfec25ca4U);
            R_SCE_func314(476+64);
            R_SCE_func100(0x5fd6098eU, 0xb0a4aa6fU, 0x6fbf8a9bU, 0x8d3d485cU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x011f5dcdU);
            R_SCE_func080();
            R_SCE_func100(0x95d32d78U, 0xa45457b5U, 0xe5f8e953U, 0x38f617afU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func313(408);
            R_SCE_func100(0x734032afU, 0xdb8e964cU, 0x99579a76U, 0x77372250U);
            R_SCE_func314(408+64);
            R_SCE_func100(0x05d01d46U, 0x51c80911U, 0x1f9533bbU, 0x559a990cU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0132d44bU);
            R_SCE_func080();
            R_SCE_func100(0x26ec1a66U, 0xa360484aU, 0x1fc4554aU, 0xec5faf33U);
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000010U;
            R_SCE_func312(68);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01432c7aU);
            R_SCE_func080();
            SCE->REG_00H = 0x00013203U;
            SCE->REG_2CH = 0x00000012U;
            R_SCE_func312(0);
            R_SCE_func100(0x5f778260U, 0xe3de8be1U, 0x812451fcU, 0x1fe75f22U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019fce91U);
            R_SCE_func080();
            R_SCE_func100(0xd8080861U, 0xcf4e71c6U, 0x6139f572U, 0xca85541aU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func313(612);
            R_SCE_func100(0x7bace3d0U, 0xf031163fU, 0x89edc410U, 0x753d81f2U);
            R_SCE_func314(612+64);
            R_SCE_func100(0x9aaa72f5U, 0x2cc19247U, 0x5ed1ebc1U, 0x31ad1ebcU);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01e59c3dU);
            R_SCE_func080();
            R_SCE_func100(0xac0242f2U, 0x02712c2fU, 0x67bf3657U, 0xefa0c8a9U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func313(544);
            R_SCE_func100(0x03654065U, 0xe7dc14aaU, 0x18333d86U, 0x09ef6142U);
            R_SCE_func314(544+64);
            SCE->REG_ECH = 0x0000b400U;
            SCE->REG_ECH = 0x00000082U;
            R_SCE_func101(0xb813cd50U, 0xaa5a905cU, 0x8b4a9838U, 0x864d3a8fU);
            R_SCE_func309();
            R_SCE_func100(0xe86ac439U, 0x52299c20U, 0x34cb67a5U, 0x9406a945U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x019c85beU);
            R_SCE_func080();
            R_SCE_func100(0xb8f0ebd6U, 0x59ca3d05U, 0x4cd45e93U, 0x3f4e0c81U);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000020U;
            R_SCE_func313(204);
            R_SCE_func100(0x47accc40U, 0xfef83151U, 0x8db0ab0bU, 0xb47061efU);
            R_SCE_func314(204+64);
            R_SCE_func100(0xfe6a2d71U, 0x87544900U, 0xefa8d3cfU, 0x24dc7d30U);
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x80010020U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x016bcaa1U);
            R_SCE_func080();
            R_SCE_func100(0x2743f352U, 0x033635bdU, 0x7422794bU, 0x940927bfU);
            SCE->REG_00H = 0x00012303U;
            SCE->REG_2CH = 0x00000022U;
            R_SCE_func313(136);
            R_SCE_func100(0xc775d898U, 0xabfd9871U, 0x28a2e994U, 0xdf9e4dfcU);
            R_SCE_func314(136+64);
            SCE->REG_ECH = 0x0000d260U;
            R_SCE_func101(0x81c8537aU, 0x705d86b7U, 0x819bd7adU, 0xb6ba1cdfU);
        }
        SCE->REG_ECH = 0x01816e94U;
        R_SCE_func101(0x5ed5f9eaU, 0x14860d1aU, 0x8571a921U, 0xac206235U);
    }
    SCE->REG_ECH = 0x38008a20U;
    SCE->REG_ECH = 0x00000020U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    R_SCE_func100(0xd16111aaU, 0xdac93babU, 0x81f19e66U, 0xfdd4e647U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019c85beU);
    R_SCE_func080();
    R_SCE_func100(0x2e29d960U, 0x6a155b86U, 0x3c9eb07eU, 0xcc418cacU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(204);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016bcaa1U);
    R_SCE_func080();
    R_SCE_func100(0x9436ca24U, 0x9893f89dU, 0xede2c2f5U, 0xeda17933U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(136);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a67f45U);
    R_SCE_func080();
    R_SCE_func100(0x67ddbb73U, 0xae88e0b5U, 0xfdc29736U, 0x5907a3bfU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func313(476);
    R_SCE_func100(0x9c7f220aU, 0x91fa1ae6U, 0xbbdaa77dU, 0x94004114U);
    R_SCE_func314(476+64);
    R_SCE_func100(0x1553daabU, 0x2f499705U, 0xeeb4dbfcU, 0x17caeee7U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011f5dcdU);
    R_SCE_func080();
    R_SCE_func100(0x6bbeceb9U, 0x6dc208d7U, 0x20b99a2aU, 0x9a590740U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(408);
    R_SCE_func100(0xfd77d1a1U, 0x5d4f6bb3U, 0xb25cbde6U, 0x370c6a7fU);
    R_SCE_func314(408+64);
    R_SCE_func100(0xa70adc0cU, 0x282235caU, 0x5246eefdU, 0x3a8acb3fU);
    SCE->REG_24H = 0x000001c0U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019fce91U);
    R_SCE_func080();
    R_SCE_func100(0xedd5d76dU, 0x30e4c572U, 0xae423d4aU, 0xb1505115U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func313(612);
    R_SCE_func100(0x7d722467U, 0xdcfa17a6U, 0xc268e6f1U, 0xf56a728eU);
    R_SCE_func314(612+64);
    R_SCE_func100(0x845df7abU, 0x175293b7U, 0x16d25074U, 0x386c2376U);
    SCE->REG_24H = 0x00000581U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01e59c3dU);
    R_SCE_func080();
    R_SCE_func100(0x4962e3c6U, 0x39ba3becU, 0xa2e3f229U, 0xd5fb2bfdU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(544);
    R_SCE_func100(0x660ac077U, 0x4c484ec5U, 0xa5ef837dU, 0xfd258a4bU);
    R_SCE_func314(544+64);
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000083U;
    R_SCE_func101(0x0a8b5e81U, 0x3381ec5fU, 0x8db9ae0bU, 0x3ee54ba8U);
    R_SCE_func309();
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000090U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func307.prc
***********************************************************************************************************************/
