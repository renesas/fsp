/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** OR in the HOCO frequency setting from bsp_clock_cfg.h with the OFS1 setting from bsp_cfg.h. */
#define BSP_ROM_REG_OFS1_SETTING                                             \
    (((uint32_t) BSP_CFG_ROM_REG_OFS1 & BSP_FEATURE_BSP_OFS1_HOCOFRQ_MASK) | \
     ((uint32_t) BSP_CFG_HOCO_FREQUENCY << BSP_FEATURE_BSP_OFS1_HOCOFRQ_OFFSET))

/** Build up SECMPUAC register based on MPU settings. */
#define BSP_ROM_REG_MPU_CONTROL_SETTING                     \
    ((0xFFFFFCF0U) |                                        \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_PC0_ENABLE << 8) |     \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_PC1_ENABLE << 9) |     \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION0_ENABLE) |      \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION1_ENABLE << 1) | \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION2_ENABLE << 2) | \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION3_ENABLE << 3))

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#ifndef RENESAS_CORTEX_M33

/** ROM registers defined here. Some have masks to make sure reserved bits are set appropriately. */
BSP_DONT_REMOVE static const uint32_t g_bsp_rom_registers[] BSP_PLACE_IN_SECTION (BSP_SECTION_ROM_REGISTERS) =
{
    (uint32_t) BSP_CFG_ROM_REG_OFS0,
    (uint32_t) BSP_ROM_REG_OFS1_SETTING,
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC0_START & 0xFFFFFFFCU),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC0_END | 0x00000003U),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC1_START & 0xFFFFFFFCU),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC1_END | 0x00000003U),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION0_START & BSP_FEATURE_BSP_MPU_REGION0_MASK & 0xFFFFFFFCU),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION0_END & BSP_FEATURE_BSP_MPU_REGION0_MASK) | 0x00000003U),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION1_START & 0xFFFFFFFCU),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION1_END | 0x00000003U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION2_START & 0x407FFFFCU) | 0x40000000U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION2_END & 0x407FFFFCU) | 0x40000003U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION3_START & 0x407FFFFCU) | 0x40000000U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION3_END & 0x407FFFFCU) | 0x40000003U),
    (uint32_t) BSP_ROM_REG_MPU_CONTROL_SETTING
};

/** ID code definitions defined here. */
BSP_DONT_REMOVE static const uint32_t g_bsp_id_codes[] BSP_PLACE_IN_SECTION (BSP_SECTION_ID_CODE) =
{
    BSP_CFG_ID_CODE_LONG_1,
 #if BSP_FEATURE_BSP_OSIS_PADDING
    0xFFFFFFFFU,
 #endif
    BSP_CFG_ID_CODE_LONG_2,
 #if BSP_FEATURE_BSP_OSIS_PADDING
    0xFFFFFFFFU,
 #endif
    BSP_CFG_ID_CODE_LONG_3,
 #if BSP_FEATURE_BSP_OSIS_PADDING
    0xFFFFFFFFU,
 #endif
    BSP_CFG_ID_CODE_LONG_4
};

#else                                  /* CM33 parts */

BSP_DONT_REMOVE const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs0") g_bsp_rom_ofs0 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_dualsel") g_bsp_rom_dualsel =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_sas") g_bsp_rom_sas =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1") g_bsp_rom_ofs1 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel") g_bsp_rom_banksel =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps") g_bsp_rom_bps0 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps") g_bsp_rom_bps1 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps") g_bsp_rom_bps2 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps") g_bsp_rom_pbps0 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps") g_bsp_rom_pbps1 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps") g_bsp_rom_pbps2 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sec") g_bsp_rom_ofs1_sec =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel_sec") g_bsp_rom_banksel_sec =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec") g_bsp_rom_bps_sec0 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec") g_bsp_rom_bps_sec1 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec") g_bsp_rom_bps_sec2 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec") g_bsp_rom_pbps_sec0 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec") g_bsp_rom_pbps_sec1 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec") g_bsp_rom_pbps_sec2 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sel") g_bsp_rom_ofs1_sel =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel_sel") g_bsp_rom_banksel_sel =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel") g_bsp_rom_bps_sel0 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel") g_bsp_rom_bps_sel1 =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel") g_bsp_rom_bps_sel2 =
    0xFFFFFFFF;

#endif

/** @} (end addtogroup BSP_MCU) */
