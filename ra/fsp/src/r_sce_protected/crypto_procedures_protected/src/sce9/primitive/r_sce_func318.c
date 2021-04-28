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

void R_SCE_func318(void)
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
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_ECH = 0x00003fbeU;
    R_SCE_func100(0x7301f6afU, 0xa2e43a96U, 0x085014d4U, 0xa0f1f332U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    R_SCE_func080();
    R_SCE_func100(0x7ea9a8e8U, 0x9dae87abU, 0xb8e4ff4eU, 0xfc14f36dU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    R_SCE_func320(480);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    R_SCE_func080();
    R_SCE_func100(0x02ee115fU, 0x2006eda8U, 0xaad9dc2dU, 0xf0b445c6U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(616);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    R_SCE_func080();
    R_SCE_func100(0xdbc3d67bU, 0xa17d647aU, 0xdb90f11cU, 0xe7534d1bU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func320(444);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    R_SCE_func080();
    R_SCE_func100(0xb4fec5a8U, 0x63aea9ceU, 0x06617566U, 0x56ea99f2U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(580);
    R_SCE_func323();
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x48d10106U, 0x57af76b9U, 0xe79e1fcbU, 0x2fcbb474U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func321(816);
    R_SCE_func100(0x6fcb3e02U, 0xeeebc6d7U, 0xe56480a7U, 0x5b584bc5U);
    R_SCE_func314(816+36);
    R_SCE_func100(0x2f95e115U, 0x0af86cc9U, 0xc18848b6U, 0x382c6423U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x752ad143U, 0xffc2321cU, 0x0e4bd426U, 0x246202cbU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func321(856);
    R_SCE_func100(0xac0039f7U, 0xbb30222aU, 0xc7e41d63U, 0x7977476dU);
    R_SCE_func314(856+36);
    R_SCE_func100(0xbdb02592U, 0x55ef0f19U, 0x1fe1c157U, 0x52a442f3U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x00005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0U;
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
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    R_SCE_func080();
    R_SCE_func100(0x9a64096fU, 0x9abb165aU, 0xa3cc1273U, 0xdaba5b9cU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    R_SCE_func320(408);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    R_SCE_func080();
    R_SCE_func100(0xc276bbeaU, 0xcbb1d556U, 0x89709a9fU, 0xb8ffbc92U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(544);
    R_SCE_func323();
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x59189e01U, 0xf2cde2beU, 0xbd0dabadU, 0xbebe0b3bU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func321(992);
    R_SCE_func100(0x4b49462fU, 0xc8367d3dU, 0xd74562ceU, 0x1d07df5eU);
    R_SCE_func314(992+36);
    R_SCE_func100(0xfdffaa80U, 0x5f9d355fU, 0xa4505dc0U, 0x856b5316U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x326bd82fU, 0x4365081bU, 0x652f03a6U, 0xf1e9fe2bU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x05a121d4U, 0x01e6f8a2U, 0xa87fca3aU, 0x4e92a9b3U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func321(816);
    R_SCE_func100(0xa6b0b307U, 0xc81babd4U, 0x3384194cU, 0x7a17a1d2U);
    R_SCE_func314(816+36);
    R_SCE_func100(0x26380096U, 0x66d2d381U, 0xc73e996eU, 0x23e0c7d9U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x00005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0U;
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
    SCE->REG_100H = change_endian_long(0x0130aeffU);
    R_SCE_func080();
    R_SCE_func100(0xd88f20ecU, 0x702f8689U, 0x33b8fbdfU, 0x8b48ad27U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    R_SCE_func320(444);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01f11123U);
    R_SCE_func080();
    R_SCE_func100(0x42b788dcU, 0x0bf39b64U, 0x62136015U, 0xcb2b6e3cU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(580);
    R_SCE_func323();
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    R_SCE_func100(0x0523fc19U, 0x3424c82eU, 0x1ab204adU, 0x885928eeU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func321(952);
    R_SCE_func100(0x66bd04e9U, 0xdcab4797U, 0x0ba98d72U, 0xd78b72ffU);
    R_SCE_func314(952+36);
    R_SCE_func100(0xa40e00deU, 0xd40f5a52U, 0x1ca31476U, 0xa859f3faU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0xf1c84e91U, 0x824b1944U, 0xacea390eU, 0xbba43d47U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x64fb6cc4U, 0x52adecabU, 0x38bbcf54U, 0xd58ea7eaU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000020U;
    R_SCE_func321(992);
    R_SCE_func100(0xb8b173e8U, 0x3aa7754cU, 0x5ff735eaU, 0x938539c2U);
    R_SCE_func314(992+36);
    R_SCE_func100(0x4bd64f5bU, 0xc9cec4cdU, 0x9f7b4506U, 0x033a86e9U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x00005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000098d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x000060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x70057b1cU, 0xc1228d3eU, 0x63d8a6afU, 0xc932fba9U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x8a092b3eU, 0xbd455d61U, 0x0954606cU, 0x5ccb541bU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(856);
    R_SCE_func100(0x2fc4762fU, 0x975ae16aU, 0x57abfd77U, 0xbde3b98bU);
    R_SCE_func314(856+36);
    R_SCE_func100(0x93302376U, 0xefcd0c66U, 0x519a401bU, 0x792080afU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x2beceb85U, 0x107833d1U, 0xa5561c14U, 0xff56f181U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0xe57e8ab1U, 0xcd9aa59dU, 0xa45e377bU, 0x5e573ce1U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(992);
    R_SCE_func100(0x6e9f78c1U, 0x84f6ede8U, 0x4c0b8da7U, 0x22bbcd78U);
    R_SCE_func314(992+36);
    R_SCE_func100(0xf5ea4d87U, 0x31cf7783U, 0xa660fc6cU, 0x6a4c655fU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x3d41c989U, 0x992167d1U, 0xcb4f9467U, 0x423b7dd0U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x17d5f624U, 0x2f612252U, 0x332fbe63U, 0xfb97779eU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0x573e62c3U, 0x3d443ebaU, 0xed1d0b0fU, 0x74f20245U);
    R_SCE_func314(816+36);
    R_SCE_func100(0xd76526dfU, 0x0a92a236U, 0x0d3cb2abU, 0xde6a21aaU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    R_SCE_func100(0x7d1770c2U, 0x64b25e21U, 0xfca12774U, 0x9f7dee90U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(952);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    R_SCE_func100(0xc4ca9045U, 0xfbc63f32U, 0xfcdad2d2U, 0x620dc579U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(952);
    R_SCE_func100(0xf972ac1eU, 0x6515ba68U, 0x4018c867U, 0x755cf6c3U);
    R_SCE_func314(952+36);
    R_SCE_func100(0x2958a235U, 0x5856a072U, 0x4a0a4083U, 0xefe8ed3aU);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010964eaU);
    R_SCE_func080();
    R_SCE_func100(0x5ee4997bU, 0x71c13469U, 0x409ab06fU, 0x957c5797U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func320(480);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ac62c9U);
    R_SCE_func080();
    R_SCE_func100(0x5c53d776U, 0x92c70653U, 0x38df44e5U, 0xdbd53b16U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(616);
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x000060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x0000c8d0U;
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
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    R_SCE_func080();
    R_SCE_func100(0x6df97ecaU, 0x26849aa3U, 0x050465c8U, 0x8a12278dU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(896);
    R_SCE_func100(0x6949b5f8U, 0x4529de33U, 0xa2c9c04aU, 0xb66414f9U);
    R_SCE_func314(896+36);
    R_SCE_func100(0xfe8204eaU, 0x446377c6U, 0x94046ab5U, 0x3ff2d743U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x1d5943c8U, 0x813f931cU, 0x480f3522U, 0xb6818432U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x5be27d18U, 0xc5675cdbU, 0x676e536eU, 0xf0e929daU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(856);
    R_SCE_func100(0xc2b48322U, 0x78681058U, 0x36379134U, 0x753f1745U);
    R_SCE_func314(856+36);
    R_SCE_func100(0xfde6f63eU, 0xfb4e4cabU, 0x10c4b876U, 0xbe3596ccU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0xee8793b0U, 0x3d2a84b4U, 0xc6415643U, 0x55942a21U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x14db0b1fU, 0x43891444U, 0x8549b8f3U, 0xa21f4eedU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0x3ed36b49U, 0xe3fa47a8U, 0xfcfe5d9aU, 0x9b9b30d1U);
    R_SCE_func314(816+36);
    R_SCE_func100(0x248100ebU, 0x7e089cc6U, 0xeba85e04U, 0x5cb0a332U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0xe6241337U, 0xa4d5b1dfU, 0xb01b4176U, 0x432b6d66U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x3ab4d3fcU, 0xc4d0ece9U, 0x9b0bc83bU, 0x6a0dbecbU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(992);
    R_SCE_func100(0x1ac9c4f0U, 0x33eb3da9U, 0xdee6f4b4U, 0xc8d550a4U);
    R_SCE_func314(992+36);
    R_SCE_func100(0x13d9e8c4U, 0x80aae640U, 0x7eed3fa9U, 0xa4e455c8U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfU);
    R_SCE_func080();
    R_SCE_func100(0x811f9244U, 0x847adc84U, 0x3da44a58U, 0xc3593a96U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x011af8f9U);
    R_SCE_func080();
    R_SCE_func100(0x4836a1f7U, 0x6abeb483U, 0x6ae3b9eaU, 0x28d4e723U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func320(408);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01574730U);
    R_SCE_func080();
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(544);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x000060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f0U;
    R_SCE_func101(0xdea3f7faU, 0xa08f46e9U, 0x5f0cf626U, 0x80ac51b5U);
    R_SCE_func316();
    R_SCE_func100(0x43f38674U, 0xccdc8f42U, 0x9cc9f784U, 0x2cf2535eU);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0xed26a6bfU, 0xaa36f104U, 0x39112e62U, 0x0f0a647aU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0xa05c50a5U, 0xc10a0ac6U, 0x6ef2ee05U, 0x7191c4bbU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0xf853314aU, 0x7e295d32U, 0x3df236b2U, 0x10602cfbU);
    R_SCE_func314(816+36);
    R_SCE_func100(0xfe8c8406U, 0xab608ac9U, 0x554ee475U, 0x9c66e46fU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    R_SCE_func100(0x722236ddU, 0x57bb3c22U, 0xd80968e1U, 0x9e1dc6a8U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(952);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    R_SCE_func100(0x2f72d0a8U, 0xaf4b377eU, 0x25e03009U, 0x71b5c0c5U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(952);
    R_SCE_func100(0x3f440a36U, 0x0a5378c5U, 0x45abae51U, 0xc05fdaf7U);
    R_SCE_func314(952+36);
    R_SCE_func100(0x645c0551U, 0xab4271e6U, 0x3fdb667dU, 0x19c419daU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0xe0f23592U, 0xd1b03f8eU, 0x5f1ba51bU, 0xe62fb898U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x77850f1eU, 0x59c634eeU, 0xa99d1f3eU, 0x6dc3e242U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(992);
    R_SCE_func100(0x1b7193ecU, 0x159d8e03U, 0xadcb540eU, 0xfba64c84U);
    R_SCE_func314(992+36);
    R_SCE_func100(0x40b14cb8U, 0x84e9f7f0U, 0x81e7e6e5U, 0x63758ed2U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000408U;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cU;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x8000f4d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x000050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    R_SCE_func080();
    R_SCE_func100(0xf14fd41fU, 0xbdbeee1fU, 0x819b1f09U, 0x42d00685U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(752);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    R_SCE_func080();
    R_SCE_func100(0xde9406d7U, 0x05927008U, 0x202477c7U, 0x3a33491bU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(896);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    R_SCE_func080();
    R_SCE_func100(0x88606427U, 0x6036f077U, 0xb3867c22U, 0xff9623f0U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(896);
    R_SCE_func100(0x77c94cd9U, 0xc6ad2e99U, 0xc92bca69U, 0x9385c14bU);
    R_SCE_func314(896+36);
    R_SCE_func100(0x09dd2f1cU, 0xb140a30fU, 0x17bbc0f6U, 0xf475a11dU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x86ccd603U, 0xe286b95fU, 0x14a77c6eU, 0x16873e05U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x743fda67U, 0x62cc1e27U, 0xbeba3639U, 0x217ce92eU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(856);
    R_SCE_func100(0x240c5821U, 0x25c41b17U, 0x5a6ba87cU, 0x13cf1460U);
    R_SCE_func314(856+36);
    R_SCE_func100(0x6b475705U, 0x89094f3aU, 0xe89f2f5dU, 0x658ffb52U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x61ad790fU, 0x8da28e8bU, 0x9c83c181U, 0xc9cd002cU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0xb86aa76fU, 0x3fc8f4f8U, 0x6b518a04U, 0xb010e0f2U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0x7e428dfcU, 0xcfcbf0ceU, 0xd7ff64b5U, 0x9d7c2cfcU);
    R_SCE_func314(816+36);
    R_SCE_func100(0xb0e5e3b6U, 0x9df372c9U, 0xddaf35c6U, 0x0e4db241U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x36e0d5b6U, 0x93f9096cU, 0x2091bfcfU, 0x1588ee52U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x9cc00091U, 0x1d36c01eU, 0x74aaa668U, 0x7728753dU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(992);
    R_SCE_func100(0x3ec5ca73U, 0x697904daU, 0x5cb61c0cU, 0xfe026a09U);
    R_SCE_func314(992+36);
    R_SCE_func100(0x537723a1U, 0xa5a12c9fU, 0xd3a0fc3eU, 0x7c535b92U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000002U;
    SCE->REG_24H = 0x80004cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000810U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030U;
    SCE->REG_24H = 0x80007cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    R_SCE_func080();
    R_SCE_func100(0x2743d1e2U, 0x1d020bf8U, 0x0a876514U, 0x442a71dcU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(716);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0xc9229d76U, 0xc1cd23b8U, 0x4f8e869dU, 0xb6144740U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0xf07a11b4U, 0x10b43c37U, 0x42ae9daaU, 0x1fdda8f2U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(856);
    R_SCE_func100(0x403a7598U, 0xb42694bbU, 0x2f796521U, 0x02268955U);
    R_SCE_func314(856+36);
    R_SCE_func100(0xd7a26be2U, 0x51610ad5U, 0x34fa706aU, 0x2996a10bU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x922dd6d0U, 0x0b5a99e8U, 0x93618b64U, 0x2b4f903aU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x03e00fe4U, 0x6bcdc3caU, 0x72a4f9efU, 0x3d1e4086U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0x4ce79edeU, 0x181d2741U, 0x0eb99d6cU, 0xbb775ad3U);
    R_SCE_func314(816+36);
    R_SCE_func100(0x1fe53d97U, 0xfdca5332U, 0x207d37b2U, 0x2b33c950U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    R_SCE_func100(0xef88d05eU, 0x12a93706U, 0x9f389d7dU, 0x52daf208U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(952);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    R_SCE_func100(0x0bf610d8U, 0x8f8b0151U, 0xe1359a54U, 0x9f44e9cbU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(952);
    R_SCE_func100(0xdec039f3U, 0xd8aa1f66U, 0x011510e4U, 0xcb14f413U);
    R_SCE_func314(952+36);
    R_SCE_func100(0x6854292aU, 0x53637b51U, 0xa1484812U, 0x582ba503U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0xe036f3a4U, 0x91c5bb93U, 0x977fa2d8U, 0x3cd91265U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x49ec776eU, 0x6d9db6e0U, 0x8c72e89eU, 0x38247d82U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(992);
    R_SCE_func100(0xc13ff91cU, 0x6a3cab99U, 0x77b0216cU, 0xbfd759c8U);
    R_SCE_func314(992+36);
    R_SCE_func100(0x6b82e003U, 0xf7c17b5cU, 0x47d3c4eeU, 0x0f992698U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfU);
    R_SCE_func080();
    R_SCE_func100(0x2e47e91dU, 0xb323c5a7U, 0xda241b39U, 0x2f4771e1U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(680);
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ff6162U);
    R_SCE_func080();
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func322(952);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f1U;
    R_SCE_func101(0x4c7fc365U, 0x32b6b13dU, 0xb9aef57aU, 0xdace120aU);
    R_SCE_func316();
    R_SCE_func100(0x984a67cfU, 0x1d8ff24fU, 0x693552b6U, 0x03b4193eU);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0xc8b85d56U, 0x121a1d2dU, 0xed50ecd9U, 0x388c29edU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0xe1599e90U, 0xd998a93aU, 0xe4289afeU, 0x88be2404U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(992);
    R_SCE_func100(0xbc397e43U, 0x5a214cd6U, 0xe33e86f4U, 0x54de26f5U);
    R_SCE_func314(992+36);
    R_SCE_func100(0xbe038b01U, 0xd43d933eU, 0x52d8e9d5U, 0xa2f890a7U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000408U;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cU;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x8000f4d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_24H = 0x000050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    R_SCE_func080();
    R_SCE_func100(0x3fdd0ef1U, 0x82d6f36fU, 0x901b0933U, 0x4787ec5aU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(752);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0xb3b89345U, 0x69612f4eU, 0x3fc7b4caU, 0xc80e1f5cU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0xc3ddf579U, 0x2da37448U, 0xd8935424U, 0xa15c7b78U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(856);
    R_SCE_func100(0x30ae294dU, 0xfcd7157aU, 0xb86f7f3aU, 0xdf387158U);
    R_SCE_func314(856+36);
    R_SCE_func100(0x21482dcdU, 0x4ff04b9fU, 0xc5ccfa8fU, 0x4d5e6059U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x1444ca15U, 0xa2a96786U, 0x5734a6a8U, 0xb620b0d1U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x726b3ec5U, 0xfb2d0d3cU, 0x5c0c9ec3U, 0xaae221b5U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0x110666c2U, 0xb0c52da3U, 0x429d7097U, 0x9591f50eU);
    R_SCE_func314(816+36);
    R_SCE_func100(0x5cbb4691U, 0xaadcfd5eU, 0x7780130dU, 0x2bb5d57cU);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000002U;
    SCE->REG_24H = 0x80004cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000810U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030U;
    SCE->REG_24H = 0x80007cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    R_SCE_func080();
    R_SCE_func100(0xfb6e2134U, 0x09f7c91bU, 0xf9ea5865U, 0xedf4f446U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(716);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x8b78e5ccU, 0x800c7c29U, 0x22eefb04U, 0x565375c7U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0xfca22bb2U, 0x52d7c5c1U, 0x655cb6a8U, 0xa6a5daedU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0x604c6980U, 0x5be6fb00U, 0xf0506ad3U, 0x536a2aa5U);
    R_SCE_func314(816+36);
    R_SCE_func100(0x5e23272cU, 0x43b5f301U, 0x48042cbfU, 0x82db1a81U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x0440b8e4U, 0x0b364ca9U, 0xdf6309adU, 0xab4a598dU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(992);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    R_SCE_func100(0x4a971b28U, 0xf38ff73eU, 0x6ce1ec63U, 0x21ad9d5bU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(992);
    R_SCE_func100(0x58dcfedeU, 0xa3fec5d7U, 0xf3c7654cU, 0x1216e257U);
    R_SCE_func314(992+36);
    R_SCE_func100(0x78e69936U, 0x47a9638fU, 0x4802fd7cU, 0x9d394316U);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x019410dfU);
    R_SCE_func080();
    R_SCE_func100(0xc7b10292U, 0xa6580db6U, 0xe7922787U, 0xaa9a9afcU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(680);
    SCE->REG_24H = 0x000084d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x014842beU);
    R_SCE_func080();
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func322(992);
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x000000f2U;
    R_SCE_func101(0xdded1fd4U, 0x23dab4ddU, 0x586378b6U, 0xdef4ea11U);
    R_SCE_func316();
    R_SCE_func100(0x63f8abe6U, 0x7d1d9cd9U, 0x5e033906U, 0x4626bd04U);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x139f3f4cU, 0xbc1b1f44U, 0xe2be2abbU, 0x6dabf567U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000981U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0xd09d83ecU, 0x81ce8424U, 0x72696314U, 0x260f5d88U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0xacfb40e3U, 0x56fb170fU, 0x42239336U, 0x6b00e166U);
    R_SCE_func314(816+36);
    R_SCE_func100(0x9609949fU, 0x154f5562U, 0x600f1f93U, 0xcc487c25U);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800070d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000408U;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x0000080cU;
    SCE->REG_24H = 0x8000f0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x8000f4d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_24H = 0x000050d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    R_SCE_func080();
    R_SCE_func100(0xfb853215U, 0xc01b4dfbU, 0x66d123a6U, 0xb42a1211U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(752);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    R_SCE_func080();
    R_SCE_func100(0x372a899fU, 0x05b2990cU, 0x9a23f97bU, 0xdbe9bcb5U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(896);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    R_SCE_func080();
    R_SCE_func100(0x03e607b1U, 0x153ab930U, 0x69b99779U, 0x6ef64341U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(896);
    R_SCE_func100(0xb53a0a02U, 0xbc8f728aU, 0xf8d4e2c0U, 0xe0aea320U);
    R_SCE_func314(896+36);
    R_SCE_func100(0x6a9ec828U, 0xeadb95f6U, 0x38290728U, 0x00535632U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x5be8f1b4U, 0xeddfc668U, 0xa9135cafU, 0x02b06c39U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0xe30f0785U, 0x534b0b88U, 0xf67684e9U, 0x39e9ad62U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(856);
    R_SCE_func100(0x30a29e72U, 0x1aaee90fU, 0x0b2a6848U, 0x2dce8f9dU);
    R_SCE_func314(856+36);
    R_SCE_func100(0xd734cdfeU, 0x4a9c3852U, 0x7d3bdd37U, 0xd223d74dU);
    SCE->REG_28H = 0x008f0001U;
    SCE->REG_34H = 0x00000002U;
    SCE->REG_24H = 0x80004cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000810U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c20U;
    SCE->REG_24H = 0x80005cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000030U;
    SCE->REG_24H = 0x80007cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    R_SCE_func080();
    R_SCE_func100(0x0f28538fU, 0x2d9e2b97U, 0x80f1104cU, 0x98f70fc5U);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(716);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a70001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000480aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000003U;
    SCE->REG_24H = 0x800068d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c02U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000801U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800048d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000054d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x82ce615aU, 0xf3f4c11aU, 0x791257c0U, 0xc835effeU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(856);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00000991U;
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
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x04f1679dU, 0x9386f125U, 0xe79207d8U, 0x2b4e7ce3U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000019c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191U;
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
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x56b968d4U, 0xbb4542c4U, 0xc7fdf1a6U, 0xb74902e8U);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func321(816);
    R_SCE_func100(0x91bccc1eU, 0xe9aa700bU, 0x2f16c337U, 0xd42f1beeU);
    R_SCE_func314(816+36);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_24H = 0x00009cd0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103e0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x800103c0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x3800dbffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xa0a32930U, 0xee7ad79dU, 0x8a9b73b0U, 0x72e3f467U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0xffffffffU;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func101(0xacdb7295U, 0x481a09cdU, 0xe19df18cU, 0x0e6d7070U);
    }
    else
    {
        SCE->REG_ECH = 0x00000800U;
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func101(0x472d3a91U, 0x41c50148U, 0xfa167367U, 0x071d944cU);
    }
    R_SCE_func100(0xd7f90576U, 0xc6d8e8edU, 0xc11dd4bcU, 0xe0889a30U);
    SCE->REG_ECH = 0x000034ffU;
    SCE->REG_ECH = 0x00003420U;
    SCE->REG_ECH = 0x00003440U;
    SCE->REG_ECH = 0x00003460U;
    SCE->REG_ECH = 0x00003480U;
    SCE->REG_ECH = 0x000034a0U;
    SCE->REG_ECH = 0x000034c0U;
    SCE->REG_E0H = 0x81080000U;
    SCE->REG_00H = 0x00003823U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000804U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c04U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x8000b0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001181U;
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
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x2baf06cdU, 0xceabba9dU, 0x6f325b5fU, 0x128c3dfbU);
    SCE->REG_00H = 0x00002393U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func321(856);
    R_SCE_func100(0x06a281abU, 0x29577c24U, 0x6a60fabaU, 0x3c4fd844U);
    R_SCE_func314(856+36);
    R_SCE_func100(0xd218cc15U, 0x5b32e7b5U, 0x9cf75f12U, 0xe7e27ac7U);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01d3c420U);
    R_SCE_func080();
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func322(896);
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02001181U;
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
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x3800dbdfU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x2b323db5U, 0xec65dceaU, 0x10c67c33U, 0x673bfdccU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0xffffffffU;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000591U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000800U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000008U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func101(0x8a78a013U, 0xba3c256dU, 0x8cecbd71U, 0xe1b1f2b5U);
    }
    else
    {
        SCE->REG_ECH = 0x00000800U;
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func101(0x8945eb8fU, 0x02f1b21cU, 0x0c0670e7U, 0x6c8ccd5eU);
    }
    SCE->REG_ECH = 0x000034feU;
    SCE->REG_ECH = 0x00003420U;
    SCE->REG_ECH = 0x00003440U;
    SCE->REG_ECH = 0x00003460U;
    SCE->REG_ECH = 0x00003480U;
    SCE->REG_ECH = 0x000034a0U;
    SCE->REG_ECH = 0x000034c0U;
    SCE->REG_E0H = 0x81080000U;
    SCE->REG_00H = 0x00003823U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_34H = 0x00000804U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c04U;
    SCE->REG_24H = 0x800090d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x8000b0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00a30001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001181U;
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
    R_SCE_func100(0x0bbfba54U, 0xbe72dc2eU, 0x70ff4cc5U, 0xf901d02cU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018fa058U);
    R_SCE_func080();
    R_SCE_func100(0x6b9735d3U, 0xbf036b7cU, 0x9ca9e12fU, 0x194aaa27U);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func322(816);
    SCE->REG_24H = 0x000011c0U;
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
    SCE->REG_100H = change_endian_long(0x01ef0d63U);
    R_SCE_func080();
    R_SCE_func100(0x5fdd5dedU, 0x648128f9U, 0x2a6600e9U, 0x7b573f5dU);
    SCE->REG_00H = 0x00003293U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func322(856);
    SCE->REG_28H = 0x009f0001U;
    SCE->REG_24H = 0x000012c0U;
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
    SCE->REG_100H = change_endian_long(0x019410dfU);
    R_SCE_func080();
    R_SCE_func100(0xae90bdbdU, 0xc2ad7a3cU, 0x0fdcf164U, 0xcb258d9cU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func320(680);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x010273a4U);
    R_SCE_func080();
    R_SCE_func100(0x64628748U, 0x8c07f7e1U, 0xb8d692b2U, 0xb8b193eeU);
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000015U;
    R_SCE_func320(716);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x018e0c4cU);
    R_SCE_func080();
    SCE->REG_00H = 0x00003283U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func320(752);
    SCE->REG_24H = 0x0000a0d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00870001U;
    SCE->REG_34H = 0x00000400U;
    SCE->REG_24H = 0x800060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000800U;
    SCE->REG_24H = 0x800060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x800060d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103e0U;
    SCE->REG_00H = 0x0000031fU;
    SCE->REG_2CH = 0x00000023U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x00008307U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x3800dbffU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x36902af6U, 0x5e67376dU, 0x90349b01U, 0xab907f1aU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x04001981U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x02001181U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001U;
            SCE->REG_E0H = 0x800103e0U;
            SCE->REG_00H = 0x0000031fU;
            SCE->REG_2CH = 0x00000023U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00008307U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x3800dbffU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            R_SCE_func100(0x6854bf0bU, 0xbd60364dU, 0xaa9b54dbU, 0x709ad19bU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func101(0x9ac23d34U, 0x03a9e720U, 0x9cc54721U, 0x178492eaU);
                oLoop1 = 0;
            }
            else
            {
                R_SCE_func101(0x00dfd565U, 0x568cd553U, 0xa872e139U, 0x978c7965U);
            }
        }
    }
    else
    {
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_24H = 0x04001991U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x02001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000049c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00870001U;
            SCE->REG_E0H = 0x800103e0U;
            SCE->REG_00H = 0x0000031fU;
            SCE->REG_2CH = 0x00000023U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_00H = 0x00008307U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            SCE->REG_ECH = 0x3800dbffU;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            R_SCE_func100(0xccbb14a0U, 0x64e553c2U, 0xd459eed0U, 0x53d4c0e3U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_24H = 0x04001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x02001181U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000049c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                R_SCE_func101(0x3e3faeb8U, 0xe332932fU, 0x74810598U, 0x70b6d1f5U);
                oLoop1 = 0;
            }
            else
            {
                R_SCE_func101(0xbcf0e6b4U, 0x8c156494U, 0x028cdf93U, 0xe04f4ec8U);
            }
        }
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000088d0U;
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_ECH = 0x00003bbeU;
    SCE->REG_ECH = 0x00007c1dU;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func318.prc
***********************************************************************************************************************/
