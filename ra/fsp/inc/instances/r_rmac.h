/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RMAC_H
#define R_RMAC_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ether_api.h"
#include "r_layer3_switch.h"

FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_ether_previous_link_status
{
    ETHER_PREVIOUS_LINK_STATUS_DOWN = 0, ///< Previous link status is down
    ETHER_PREVIOUS_LINK_STATUS_UP   = 1, ///< Previous link status is up
} ether_previous_link_status_t;

typedef enum e_ether_link_change
{
    ETHER_LINK_CHANGE_NO_CHANGE = 0,   ///< Link status is no change
    ETHER_LINK_CHANGE_LINK_DOWN = 1,   ///< Link status changes to down
    ETHER_LINK_CHANGE_LINK_UP   = 2,   ///< Link status changes to up
} ether_link_change_t;

typedef enum e_ether_link_establish_status
{
    ETHER_LINK_ESTABLISH_STATUS_DOWN = 0, ///< Link establish status is down
    ETHER_LINK_ESTABLISH_STATUS_UP   = 1, ///< Link establish status is up
} ether_link_establish_status_t;

typedef struct st_rmac_queue_info
{
    layer3_switch_descriptor_queue_cfg_t queue_cfg; ///< Queue configuration.
    uint32_t index;                                 ///< Queue index.
} rmac_queue_info_t;

/* Extended configuration. */
typedef struct st_rmac_extended_cfg
{
    ether_switch_instance_t const * p_ether_switch; ///< Pointer to ETHER_SWITCH instance.

    uint32_t tx_queue_num;                          ///< Number of TX descriptor queues.
    uint32_t rx_queue_num;                          ///< Number of RX descriptor queues.

    rmac_queue_info_t * p_tx_queue_list;            ///< TX queue list.
    rmac_queue_info_t * p_rx_queue_list;            ///< RX queue list.

    IRQn_Type rmpi_irq;                             ///< Magic packet detection interrupt number
    uint32_t  rmpi_ipl;                             ///< Magic packet detection interrupt priority
} rmac_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_flash_api_t::open is called */
typedef struct st_rmac_instance_ctrl
{
    uint32_t            open;          // Whether or not driver is open
    ether_cfg_t const * p_cfg;         // Pointer to initial configuration

    /* IP dependent members. */
    R_ETHA0_Type * p_reg_etha;
    R_RMAC0_Type * p_reg_rmac;

    /* Descriptor queue indexes. */
    uint32_t read_queue_index;                           ///< RX queue that used for next Read API.
    uint32_t write_queue_index;                          ///< TX queue that used for next Write API.

    uint32_t rx_pending_queue_map;                       ///< Count of empty RX queue.
    uint32_t rx_running_queue_index;                     ///< Whether a RX queue is running or not.

    uint32_t tx_pending_queue_map;                       ///< TX data is pending because it has been written but not yet sent.
    uint32_t tx_running_queue_index;                     ///< Whether a TX queue is running or not.

    /* FIXME: It is not needed if using internal buffer. */
    uint32_t rx_reset_descriptor_count;                  ///< Count of descriptor that already read in active queue.

    /* Status of ethernet driver. */
    ether_previous_link_status_t  previous_link_status;  ///< Previous link status
    ether_link_change_t           link_change;           ///< Status of link change
    ether_link_establish_status_t link_establish_status; ///< Current Link status
    ether_wake_on_lan_t           wake_on_lan;           ///< Wake on LAN mode.

    /* Pointer to callback and optional working memory */
    void (* p_callback)(ether_callback_args_t *);
    ether_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} rmac_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ether_api_t g_ether_on_rmac;

/** @endcond */

fsp_err_t R_RMAC_Open(ether_ctrl_t * p_ctrl, ether_cfg_t const * const p_cfg);
fsp_err_t R_RMAC_Close(ether_ctrl_t * p_ctrl);
fsp_err_t R_RMAC_BufferRelease(ether_ctrl_t * const p_ctrl);
fsp_err_t R_RMAC_RxBufferUpdate(ether_ctrl_t * const p_ctrl, void * const p_buffer);
fsp_err_t R_RMAC_LinkProcess(ether_ctrl_t * const p_ctrl);
fsp_err_t R_RMAC_WakeOnLANEnable(ether_ctrl_t * const p_ctrl);
fsp_err_t R_RMAC_Read(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes);
fsp_err_t R_RMAC_Write(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length);
fsp_err_t R_RMAC_TxStatusGet(ether_ctrl_t * const p_ctrl, void * const p_buffer_address);
fsp_err_t R_RMAC_CallbackSet(ether_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(ether_callback_args_t *),
                             void * const                  p_context,
                             ether_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_RMAC_H */
