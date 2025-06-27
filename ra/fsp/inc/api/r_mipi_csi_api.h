/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_GRAPHICS_INTERFACES
 * @defgroup MIPI_CSI_API MIPI CSI Interface
 * @brief Interface for MIPI CSI communications.
 *
 * @section MIPI_CSI_API_SUMMARY Summary
 * The MIPI CSI interface provides functionality involved with driving display panels over MIPI.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_MIPI_CSI_API_H
#define R_MIPI_CSI_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_mipi_cmd_types.h"
#include "r_mipi_csi_cfg.h"

#include "r_mipi_phy.h"

#if __has_include("r_mipi_csi_device_types.h")
 #include "r_mipi_csi_device_types.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

/** MIPI CSI State type */
typedef enum e_mipi_csi_state
{
    MIPI_CSI_STATE_NONE      = 0,      ///< MIPI CSI State Uninitialized
    MIPI_CSI_STATE_IDLE      = 1,      ///< MIPI CSI State Idle
    MIPI_CSI_STATE_RECEIVING = 2,      ///< MIPI CSI State Reception in progress
} mipi_csi_state_t;

/** MIPI CSI Data Lane Error IDs */
typedef enum e_mipi_csi_data_lane_error
{
    MIPI_CSI_DATA_LANE_ERROR_ERR_SOTHS     = 0X01,   ///< High-speed SOT leader sequence is corrupted
    MIPI_CSI_DATA_LANE_ERROR_ERR_SOTSYNCHS = 0X02,   ///< High-speed SOT synchronization error
    MIPI_CSI_DATA_LANE_ERROR_ERR_CONTROL   = 0X04,   ///< Incorrect line sequence detected
    MIPI_CSI_DATA_LANE_ERROR_ERR_ESC       = 0X80,   ///< Escape entry error
} mipi_csi_data_lane_error_t;

/** MIPI CSI Short Packet Type */
typedef union st_mipi_csi_short_packet
{
    struct
    {
        uint32_t data            : 16; ///< Short Packet Data
        uint32_t data_type       : 6;  ///< Short Packet Data Type
        uint32_t                 : 2;
        uint32_t virtual_channel : 4;  ///< Short Packet Virtual Channel
        uint32_t                 : 4;
    }        bits;
    uint32_t mask;
} mipi_csi_short_packet_t;

/** MIPI CSI status type */
typedef struct st_mipi_csi_status
{
    mipi_csi_state_t state;            ///< CSI State
} mipi_csi_status_t;

/** MIPI CSI Event ID */
typedef enum e_mipi_csi_event
{
    MIPI_CSI_EVENT_FRAME_DATA,         ///< Virtual Channel Frame Receive Event
    MIPI_CSI_EVENT_DATA_LANE,          ///< Data Lane Event
    MIPI_CSI_EVENT_VIRTUAL_CHANNEL,    ///< Virtual Channel Event
    MIPI_CSI_EVENT_POWER,              ///< Power Management Event
    MIPI_CSI_EVENT_SHORT_PACKET_FIFO,  ///< Generic Short Packet Event
} mipi_csi_event_t;

/** MIPI CSI Callback Arguments */
typedef struct st_mipi_csi_callback_args
{
    mipi_csi_event_t      event;       ///< Event code
    uint8_t               event_idx;   ///< Index for event type, if applicable
    mipi_csi_event_data_t event_data;  ///< Data correspondiong to event code
    void                * p_context;   ///< Context provided to user during callback
} mipi_csi_callback_args_t;

/** MIPI CSI main configuration structure */
typedef struct st_mipi_csi_cfg
{
    mipi_phy_instance_t const * p_mipi_phy_instance; ///< Pointer to mipi physical layer instance

    mipi_csi_ctrl_data_t      ctrl_data;       ///< Control register data
    mipi_csi_option_data_t    option_data;     ///< Option register data
    mipi_csi_interrupt_cfg_t  interrupt_cfg;   ///< Interrupt configuration

    /** Callback configuration */
    void (* p_callback)(mipi_csi_callback_args_t * p_args); ///< Pointer to callback function
    void * p_context;                                       ///< User defined context passed into callback function

    /** Pointer to display peripheral specific configuration */
    void const * p_extend;                                  ///< MIPI hardware dependent configuration
} mipi_csi_cfg_t;

/** MIPI CSI control block. Allocate an instance specific control block to pass into the MIPI CSI API calls. */
typedef void mipi_csi_ctrl_t;

/** Shared Interface definition for MIPI CSI peripheral */
typedef struct st_mipi_csi_api
{
    /** Open MIPI CSI device.
     *
     * @param[in,out]  p_ctrl   Pointer to MIPI CSI interface control block. Must be declared by user. Value set here.
     * @param[in]      p_cfg    Pointer to MIPI CSI configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(mipi_csi_ctrl_t * const p_ctrl, mipi_csi_cfg_t const * const p_cfg);

    /** Close MIPI CSI device.
     *
     * @param[in]     p_ctrl   Pointer to MIPI CSI interface control block.
     */
    fsp_err_t (* close)(mipi_csi_ctrl_t * const p_ctrl);

    /** Start pixel data output.
     *
     * @param[in]     p_ctrl   Pointer to MIPI CSI interface control block.
     */
    fsp_err_t (* start)(mipi_csi_ctrl_t * const p_ctrl);

    /** Stop pixel data output.
     *
     * @param[in]     p_ctrl   Pointer to MIPI CSI interface control block.
     */
    fsp_err_t (* stop)(mipi_csi_ctrl_t * const p_ctrl);

    /** Read Short Packet
     *
     * @param[in]    p_ctrl     Pointer to MIPI CSI interface control block.
     * @param[out]   p_data     Pointer to MIPI CSI data structure to read to
     */
    fsp_err_t (* read)(mipi_csi_ctrl_t * const p_ctrl, mipi_csi_short_packet_t * p_data);

    /** Get status of MIPI link.
     *
     * @param[in]    p_ctrl     Pointer to MIPI CSI interface control block.
     * @param[out]   p_status   Pointer to MIPI CSI interface status structure.
     */
    fsp_err_t (* statusGet)(mipi_csi_ctrl_t * const p_ctrl, mipi_csi_status_t * p_status);
} mipi_csi_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_mipi_csi_instance
{
    mipi_csi_ctrl_t      * p_ctrl;     ///< Pointer to the control structure for this instance
    mipi_csi_cfg_t const * p_cfg;      ///< Pointer to the configuration structure for this instance
    mipi_csi_api_t const * p_api;      ///< Pointer to the API structure for this instance
} mipi_csi_instance_t;

/* @} (end defgroup MIPI_CSI_API) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
