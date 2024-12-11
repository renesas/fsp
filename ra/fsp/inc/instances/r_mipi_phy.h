/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_MIPI_PHY_H
#define R_MIPI_PHY_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup MIPI_PHY
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* MIPI_PHY PLL speed configuration */
typedef union
{
    __PACKED_STRUCT
    {
        uint8_t  div;                  ///< PHY PLL divisor
        uint8_t  mul_frac;             ///< PHY PLL fractional multiplier (0, 1/3, 2/3, or 1/2)
        uint16_t mul_int;              ///< PHY PLL integer multiplier (1-based)
    };
    uint32_t raw;
} mipi_phy_pll_cfg_t;

/** MIPI PHY D-PHY power mode transition timing */
typedef struct st_mipi_phy_timing
{
    uint32_t t_init : 19;              ///< Minimum duration of the TINIT state (Units: PCLKA cycles)
    uint32_t        : 13;              // Padding
    uint8_t t_clk_prep;                ///< Duration of the clock lane LP-00 state (immediately before entry to the HS-0 state)
    uint8_t t_hs_prep;                 ///< Duration of the data lane LP-00 state (immediately before entry to the HS-0 state)
    union
    {
        __PACKED_STRUCT
        {
            uint8_t t_clk_zero;        ///< TCLKZERO setting. See Figure 57.1 in User Manual (R01UH0995EJ0060) for more information
            uint8_t t_clk_pre;         ///< TCLKPRE setting. See Figure 57.1 in User Manual (R01UH0995EJ0060) for more information
            uint8_t t_clk_post;        ///< TCLKPOST setting. See Figure 57.1 in User Manual (R01UH0995EJ0060) for more information
            uint8_t t_clk_trail;       ///< TCLKTRAIL setting. See Figure 57.1 in User Manual (R01UH0995EJ0060) for more information
        } dphytim4_b;
        uint32_t dphytim4;             ///< Clock lane pre and post data timing settings
    };
    union
    {
        __PACKED_STRUCT
        {
            uint8_t t_hs_zero;         ///< THSZERO setting. See Figure 57.1 in User Maual (R01UH0995EJ0060) for more information
            uint8_t t_hs_trail;        ///< THSTRAIL setting. See Figure 57.1 in User Maual (R01UH0995EJ0060) for more information
            uint8_t t_hs_exit;         ///< THSEXIT setting. See Figure 57.1 in User Maual (R01UH0995EJ0060) for more information
            uint8_t : 8;
        } dphytim5_b;
        uint32_t dphytim5;             ///< High-Speed data lane timing settings
    };
    uint8_t t_lp_exit;                 ///< Low-power transition time to High-Speed mode
} mipi_phy_timing_t;

/** MIPI_PHY configuration structure. */
typedef struct st_mipi_phy_cfg
{
    mipi_phy_pll_cfg_t        pll_settings;   ///< PHY PLL configuration (DPHYPLFCR)
    uint8_t                   lp_divisor : 5; ///< PHY PLL LP speed divisor setting (DPHYESCCR)
    mipi_phy_timing_t const * p_timing;       ///< Pointer to D-PHY HS/LP transition timing values
} mipi_phy_cfg_t;

/** MIPI_PHY instance control block. */
typedef struct st_mipi_phy_ctrl
{
    uint32_t               open;
    mipi_phy_cfg_t const * p_cfg;
} mipi_phy_ctrl_t;

/** Private Interface definition for MIPI PHY peripheral */
typedef struct st_mipi_phy_api
{
    /** Open MIPI PHY device.
     * @param[in,out]  p_ctrl       Pointer to MIPI PHY interface control block.
     * @param[in]      p_cfg        Pointer to MIPI PHY configuration structure.
     */
    fsp_err_t (* open)(mipi_phy_ctrl_t * const p_ctrl, mipi_phy_cfg_t const * const p_cfg);

    /** Close MIPI PHY device.
     * @param[in]     p_ctrl        Pointer to MIPI PHY interface control block.
     */
    fsp_err_t (* close)(mipi_phy_ctrl_t * const p_ctrl);
} mipi_phy_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_mipi_phy_instance
{
    mipi_phy_ctrl_t      * p_ctrl;     ///< Pointer to the control structure for this instance
    mipi_phy_cfg_t const * p_cfg;      ///< Pointer to the configuration structure for this instance
    mipi_phy_api_t const * p_api;      ///< Pointer to the API structure for this instance
} mipi_phy_instance_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const mipi_phy_api_t g_mipi_phy;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Instance Functions (Note: This is not a public API and should not be called directly)
 **********************************************************************************************************************/
fsp_err_t r_mipi_phy_open(mipi_phy_ctrl_t * const p_api_ctrl, mipi_phy_cfg_t const * const p_cfg);
fsp_err_t r_mipi_phy_close(mipi_phy_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup MIPI_PHY)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_MIPI_PHY_H
