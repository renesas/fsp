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
 * @addtogroup ETHER
 * @{
 **********************************************************************************************************************/

#ifndef R_ETHER_H
#define R_ETHER_H

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ether_cfg.h"
#include "r_ether_api.h"

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

typedef enum e_ether_magic_packet
{
    ETHER_MAGIC_PACKET_NOT_DETECTED = 0, ///< Magic packet is not detected
    ETHER_MAGIC_PACKET_DETECTED     = 1, ///< Magic packet is detected
} ether_magic_packet_t;

typedef enum e_ether_link_establish_status
{
    ETHER_LINK_ESTABLISH_STATUS_DOWN = 0, ///< Link establish status is down
    ETHER_LINK_ESTABLISH_STATUS_UP   = 1, ///< Link establish status is up
} ether_link_establish_status_t;

/** ETHER control block. DO NOT INITIALIZE.  Initialization occurs when @ref ether_api_t::open is called. */
typedef struct st_ether_instance_ctrl
{
    uint32_t open;                                       ///< Used to determine if the channel is configured

    /* Configuration of ethernet module. */
    ether_cfg_t const * p_ether_cfg;                     ///< Pointer to initial configurations.

    /* Buffer of ethernet module. */
    ether_instance_descriptor_t * p_rx_descriptor;       ///< Pointer to the currently referenced transmit descriptor
    ether_instance_descriptor_t * p_tx_descriptor;       ///< Pointer to the currently referenced receive descriptor

    /* Interface for PHY-LSI chip. */
    void * p_reg_etherc;                                 ///< Base register of ethernet controller for this channel
    void * p_reg_edmac;                                  ///< Base register of EDMA controller for this channel

    /* Status of ethernet driver. */
    ether_previous_link_status_t  previous_link_status;  ///< Previous link status
    ether_link_change_t           link_change;           ///< status of link change
    ether_magic_packet_t          magic_packet;          ///< status of magic packet detection
    ether_link_establish_status_t link_establish_status; ///< Current Link status
} ether_instance_ctrl_t;

/*
 * PauseMaskE, PauseValE and pause_resolutionS are use to create
 * PAUSE resolution Table 28B-3 in IEEE 802.3-2008 standard.
 */
typedef enum e_ether_pause_mask
{
    ETHER_PAUSE_MASK0,
    ETHER_PAUSE_MASK1,
    ETHER_PAUSE_MASK2,
    ETHER_PAUSE_MASK3,
    ETHER_PAUSE_MASK4,
    ETHER_PAUSE_MASK5,
    ETHER_PAUSE_MASK6,
    ETHER_PAUSE_MASK7,
    ETHER_PAUSE_MASK8,
    ETHER_PAUSE_MASK9,
    ETHER_PAUSE_MASKA,
    ETHER_PAUSE_MASKB,
    ETHER_PAUSE_MASKC,
    ETHER_PAUSE_MASKD,
    ETHER_PAUSE_MASKE,
    ETHER_PAUSE_MASKF
} ether_pause_mask_t;

typedef enum e_ether_pause_val
{
    ETHER_PAUSE_VAL0,
    ETHER_PAUSE_VAL1,
    ETHER_PAUSE_VAL2,
    ETHER_PAUSE_VAL3,
    ETHER_PAUSE_VAL4,
    ETHER_PAUSE_VAL5,
    ETHER_PAUSE_VAL6,
    ETHER_PAUSE_VAL7,
    ETHER_PAUSE_VAL8,
    ETHER_PAUSE_VAL9,
    ETHER_PAUSE_VALA,
    ETHER_PAUSE_VALB,
    ETHER_PAUSE_VALC,
    ETHER_PAUSE_VALD,
    ETHER_PAUSE_VALE,
    ETHER_PAUSE_VALF
} ether_pause_val_t;

typedef struct st_ether_pause_resolution
{
    ether_pause_mask_t mask;
    ether_pause_val_t  value;
    uint8_t            transmit;
    uint8_t            receive;
} ether_pause_resolution_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ether_api_t g_ether_on_ether;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_ETHER_Open(ether_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg);

fsp_err_t R_ETHER_Close(ether_ctrl_t * const p_ctrl);

fsp_err_t R_ETHER_Read(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes);

fsp_err_t R_ETHER_BufferRelease(ether_ctrl_t * const p_ctrl);

fsp_err_t R_ETHER_RxBufferUpdate(ether_ctrl_t * const p_ctrl, void * const p_buffer);

fsp_err_t R_ETHER_Write(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length);

fsp_err_t R_ETHER_LinkProcess(ether_ctrl_t * const p_ctrl);

fsp_err_t R_ETHER_WakeOnLANEnable(ether_ctrl_t * const p_ctrl);

fsp_err_t R_ETHER_TxStatusGet(ether_ctrl_t * const p_ctrl, void * const p_buffer_address);

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHER)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ETHER_H
