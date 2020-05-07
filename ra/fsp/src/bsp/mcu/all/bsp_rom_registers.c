/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
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

/** @} (end addtogroup BSP_MCU) */
