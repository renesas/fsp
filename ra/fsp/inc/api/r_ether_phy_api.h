/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup ETHER_PHY_API Ethernet PHY Interface
 * @brief Interface for Ethernet PHY functions.
 *
 * @section ETHER_PHY_API_Summary Summary
 * The Ethernet PHY module (r_ether_phy) provides an API for standard Ethernet PHY communications applications that use
 * the ETHERC peripheral.
 *
 * The Ethernet PHY interface supports the following features:
 * - Auto negotiation support
 * - Flow control support
 * - Link status check support
 *
 * Implemented by:
 * - @ref ETHER_PHY
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ETHER_PHY_API_H
#define R_ETHER_PHY_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Flow control functionality  */
typedef enum e_ether_phy_flow_control
{
    ETHER_PHY_FLOW_CONTROL_DISABLE = 0, ///< Disable flow control functionality
    ETHER_PHY_FLOW_CONTROL_ENABLE  = 1, ///< Enable flow control functionality with pause frames
} ether_phy_flow_control_t;

/** Link speed  */
typedef enum e_ether_phy_link_speed
{
    ETHER_PHY_LINK_SPEED_NO_LINK = 0,  ///< Link is not established
    ETHER_PHY_LINK_SPEED_10H     = 1,  ///< Link status is 10Mbit/s and half duplex
    ETHER_PHY_LINK_SPEED_10F     = 2,  ///< Link status is 10Mbit/s and full duplex
    ETHER_PHY_LINK_SPEED_100H    = 3,  ///< Link status is 100Mbit/s and half duplex
    ETHER_PHY_LINK_SPEED_100F    = 4   ///< Link status is 100Mbit/s and full duplex
} ether_phy_link_speed_t;

/** Media-independent interface */
typedef enum e_ether_phy_mii_type
{
    ETHER_PHY_MII_TYPE_MII  = 0,       ///< MII
    ETHER_PHY_MII_TYPE_RMII = 1,       ///< RMII
} ether_phy_mii_type_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - ether_phy_instance_ctrl_t
 */
typedef void ether_phy_ctrl_t;

/** Configuration parameters. */
typedef struct st_ether_phy_cfg
{
    uint8_t channel;                       ///< Channel
    uint8_t phy_lsi_address;               ///< Address of PHY-LSI

    uint32_t phy_reset_wait_time;          ///< Wait time for PHY-LSI reboot
    int32_t  mii_bit_access_wait_time;     ///< Wait time for MII/RMII access

    ether_phy_flow_control_t flow_control; ///< Flow control functionally enable or disable
    ether_phy_mii_type_t     mii_type;     ///< Interface type is MII or RMII

    /** Placeholder for user data.  Passed to the user callback in ether_phy_callback_args_t. */
    void const * p_context;
    void const * p_extend;                 ///< Placeholder for user extension.
} ether_phy_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ether_phy_api
{
    /** Open driver.
     * @par Implemented as
     * - @ref R_ETHER_PHY_Open()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ether_phy_ctrl_t * const p_api_ctrl, ether_phy_cfg_t const * const p_cfg);

    /** Close driver.
     * @par Implemented as
     * - @ref R_ETHER_PHY_Close()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ether_phy_ctrl_t * const p_api_ctrl);

    /** Start auto negotiation.
     * @par Implemented as
     * - @ref R_ETHER_PHY_StartAutoNegotiate()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* startAutoNegotiate)(ether_phy_ctrl_t * const p_api_ctrl);

    /** Get the partner ability.
     * @par Implemented as
     * - @ref R_ETHER_PHY_LinkPartnerAbilityGet()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     * @param[out] p_line_speed_duplex        Pointer to the location of both the line speed and the duplex.
     * @param[out] p_local_pause        Pointer to the location to store the local pause bits.
     * @param[out] p_partner_pause        Pointer to the location to store the partner pause bits.
     */
    fsp_err_t (* linkPartnerAbilityGet)(ether_phy_ctrl_t * const p_api_ctrl, uint32_t * const p_line_speed_duplex,
                                        uint32_t * const p_local_pause, uint32_t * const p_partner_pause);

    /** Get Link status from PHY-LSI interface.
     * @par Implemented as
     * - @ref R_ETHER_PHY_LinkStatusGet()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* linkStatusGet)(ether_phy_ctrl_t * const p_api_ctrl);
} ether_phy_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ether_phy_instance
{
    ether_phy_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    ether_phy_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    ether_phy_api_t const * p_api;     ///< Pointer to the API structure for this instance
} ether_phy_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHER_PHY_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_ETHER_PHY_API_H */
