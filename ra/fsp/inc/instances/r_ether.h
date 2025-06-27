/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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

/** EDMAC descriptor as defined in the hardware manual.
 * Structure must be packed at 1 byte.
 */
typedef struct st_ether_instance_descriptor
{
    volatile uint32_t status;
#if ((defined(__GNUC__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || (defined(__ARMCC_VERSION) && \
    !defined(__ARM_BIG_ENDIAN)) || (defined(__ICCARM__) && (__LITTLE_ENDIAN__)))

    /* Little endian */
    volatile uint16_t size;
    volatile uint16_t buffer_size;
#else

    /* Big endian */
    volatile uint16_t buffer_size;
    volatile uint16_t size;
#endif
    uint8_t * p_buffer;
    struct st_ether_instance_descriptor * p_next;
} ether_instance_descriptor_t;

/** Event mask for EESR register */
typedef enum e_ether_eesr_event_mask
{
    ETHER_EESR_EVENT_MASK_CERF  = (1U << 0U),  ///< CERF event
    ETHER_EESR_EVENT_MASK_PRE   = (1U << 1U),  ///< PRE event
    ETHER_EESR_EVENT_MASK_RTSF  = (1U << 2U),  ///< RTSF event
    ETHER_EESR_EVENT_MASK_RTLF  = (1U << 3U),  ///< RTLF event
    ETHER_EESR_EVENT_MASK_RRF   = (1U << 4U),  ///< PRF event
    ETHER_EESR_EVENT_MASK_RMAF  = (1U << 7U),  ///< RMAF event
    ETHER_EESR_EVENT_MASK_TRO   = (1U << 8U),  ///< TRO event
    ETHER_EESR_EVENT_MASK_CD    = (1U << 9U),  ///< CD event
    ETHER_EESR_EVENT_MASK_DLC   = (1U << 10U), ///< DLC event
    ETHER_EESR_EVENT_MASK_CND   = (1U << 11U), ///< CND event
    ETHER_EESR_EVENT_MASK_RFOF  = (1U << 16U), ///< RFOF event
    ETHER_EESR_EVENT_MASK_RDE   = (1U << 17U), ///< RDE event
    ETHER_EESR_EVENT_MASK_FR    = (1U << 18U), ///< FR event
    ETHER_EESR_EVENT_MASK_TFUF  = (1U << 19U), ///< TFUF event
    ETHER_EESR_EVENT_MASK_TDE   = (1U << 20U), ///< TDE event
    ETHER_EESR_EVENT_MASK_TC    = (1U << 21U), ///< TC event
    ETHER_EESR_EVENT_MASK_ECI   = (1U << 22U), ///< ECI event
    ETHER_EESR_EVENT_MASK_ADE   = (1U << 23U), ///< ADE event
    ETHER_EESR_EVENT_MASK_RFCOF = (1U << 24U), ///< RFCOF event
    ETHER_EESR_EVENT_MASK_RABT  = (1U << 25U), ///< RABT event
    ETHER_EESR_EVENT_MASK_TABT  = (1U << 26U), ///< TABT event
    ETHER_EESR_EVENT_MASK_TWB   = (1U << 30U), ///< TWB event
} ether_eesr_event_mask_t;

/** Event mask for ECSR register */
typedef enum e_ether_ecsr_event_mask
{
    ETHER_ECSR_EVENT_MASK_ICD   = (1U << 0U), ///< ICD event
    ETHER_ECSR_EVENT_MASK_MPD   = (1U << 1U), ///< MPD event
    ETHER_ECSR_EVENT_MASK_LCHNG = (1U << 2U), ///< LCHNG event
    ETHER_ECSR_EVENT_MASK_PSRTO = (1U << 4U), ///< PSRTO event
    ETHER_ECSR_EVENT_MASK_BFR   = (1U << 5U), ///< BFR event
} ether_ecsr_event_mask_t;

/** ETHER extension configures the buffer descriptor for ETHER. */
typedef struct st_ether_extended_cfg
{
    ether_instance_descriptor_t * p_rx_descriptors; ///< Receive descriptor buffer pool
    ether_instance_descriptor_t * p_tx_descriptors; ///< Transmit descriptor buffer pool
    uint32_t eesr_event_filter;                     ///< Filter for EESR related event
    uint8_t  ecsr_event_filter;                     ///< Filter for ECSR related event
} ether_extended_cfg_t;

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

    /* Pointer to callback and optional working memory */
    void (* p_callback)(ether_callback_args_t *);
    ether_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
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

fsp_err_t R_ETHER_CallbackSet(ether_ctrl_t * const          p_api_ctrl,
                              void (                      * p_callback)(ether_callback_args_t *),
                              void * const                  p_context,
                              ether_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHER)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ETHER_H
