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
 * @defgroup ETHER_API Ethernet Interface
 * @brief Interface for Ethernet functions.
 *
 * @section ETHER_API_Summary Summary
 * The Ethernet interface provides Ethernet functionality.
 * The Ethernet interface supports the following features:
 * - Transmit/receive processing (Blocking and Non-Blocking)
 * - Callback function with returned event code
 * - Magic packet detection mode support
 * - Auto negotiation support
 * - Flow control support
 * - Multicast filtering support
 *
 * Implemented by:
 * - @ref ETHER
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ETHER_API_H
#define R_ETHER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_ether_phy_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Wake on LAN */
typedef enum e_ether_wake_on_lan
{
    ETHER_WAKE_ON_LAN_DISABLE = 0,     ///< Disable Wake on LAN
    ETHER_WAKE_ON_LAN_ENABLE  = 1,     ///< Enable Wake on LAN
} ether_wake_on_lan_t;

/** Flow control functionality  */
typedef enum e_ether_flow_control
{
    ETHER_FLOW_CONTROL_DISABLE = 0,    ///< Disable flow control functionality
    ETHER_FLOW_CONTROL_ENABLE  = 1,    ///< Enable flow control functionality with pause frames
} ether_flow_control_t;

/** Multicast Filter */
typedef enum e_ether_multicast
{
    ETHER_MULTICAST_DISABLE = 0,       ///< Disable reception of multicast frames
    ETHER_MULTICAST_ENABLE  = 1,       ///< Enable reception of multicast frames
} ether_multicast_t;

/** Promiscuous Mode */
typedef enum e_ether_promiscuous
{
    ETHER_PROMISCUOUS_DISABLE = 0,     ///< Only receive packets with current MAC address, multicast, and broadcast
    ETHER_PROMISCUOUS_ENABLE  = 1,     ///< Receive all packets
} ether_promiscuous_t;

/** Zero copy */
typedef enum e_ether_zerocopy
{
    ETHER_ZEROCOPY_DISABLE = 0,        ///< Disable zero copy in Read/Write function
    ETHER_ZEROCOPY_ENABLE  = 1,        ///< Enable zero copy in Read/Write function
} ether_zerocopy_t;

typedef enum e_ether_padding
{
    ETHER_PADDING_DISABLE = 0,
    ETHER_PADDING_1BYTE   = 1,
    ETHER_PADDING_2BYTE   = 2,
    ETHER_PADDING_3BYTE   = 3,
} ether_padding_t;

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

/** Event code of callback function */
typedef enum
{
    ETHER_EVENT_WAKEON_LAN,            ///< Magic packet detection event
    ETHER_EVENT_LINK_ON,               ///< Link up detection event
    ETHER_EVENT_LINK_OFF,              ///< Link down detection event
    ETHER_EVENT_INTERRUPT,             ///< Interrupt event
} ether_event_t;

/** Callback function parameter data */
typedef struct st_ether_callback_args
{
    uint32_t      channel;             ///< Device channel number
    ether_event_t event;               ///< Event code
    uint32_t      status_ecsr;         ///< ETHERC status register for interrupt handler
    uint32_t      status_eesr;         ///< ETHERC/EDMAC status register for interrupt handler

    void const * p_context;            ///< Placeholder for user data.  Set in @ref ether_api_t::open function in @ref ether_cfg_t.
} ether_callback_args_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - ether_instance_ctrl_t
 */
typedef void ether_ctrl_t;

/** Configuration parameters. */
typedef struct st_ether_cfg
{
    uint8_t              channel;                        ///< Channel
    ether_zerocopy_t     zerocopy;                       ///< Zero copy enable or disable in Read/Write function
    ether_multicast_t    multicast;                      ///< Multicast enable or disable
    ether_promiscuous_t  promiscuous;                    ///< Promiscuous mode enable or disable
    ether_flow_control_t flow_control;                   ///< Flow control functionally enable or disable
    ether_padding_t      padding;                        ///< Padding length inserted into the received Ethernet frame.
    uint32_t             padding_offset;                 ///< Offset of the padding inserted into the received Ethernet frame.
    uint32_t             broadcast_filter;               ///< Limit of the number of broadcast frames received continuously
    uint8_t            * p_mac_address;                  ///< Pointer of MAC address

    ether_instance_descriptor_t * p_rx_descriptors;      ///< Receive descriptor buffer pool
    ether_instance_descriptor_t * p_tx_descriptors;      ///< Transmit descriptor buffer pool

    uint8_t num_tx_descriptors;                          ///< Number of transmission descriptor
    uint8_t num_rx_descriptors;                          ///< Number of receive descriptor

    uint8_t ** pp_ether_buffers;                         ///< Transmit and receive buffer

    uint32_t ether_buffer_size;                          ///< Size of transmit and receive buffer

    IRQn_Type irq;                                       ///< NVIC interrupt number
    uint32_t  interrupt_priority;                        ///< NVIC interrupt priority

    void (* p_callback)(ether_callback_args_t * p_args); ///< Callback provided when an ISR occurs.

    ether_phy_instance_t const * p_ether_phy_instance;   ///< Pointer to ETHER_PHY instance

    /** Placeholder for user data.  Passed to the user callback in ether_callback_args_t. */
    void const * p_context;                              ///< Placeholder for user data.
    void const * p_extend;                               ///< Placeholder for user extension.
} ether_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ether_api
{
    /** Open driver.
     * @par Implemented as
     * - @ref R_ETHER_Open()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ether_ctrl_t * const p_api_ctrl, ether_cfg_t const * const p_cfg);

    /** Close driver.
     * @par Implemented as
     * - @ref R_ETHER_Close()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ether_ctrl_t * const p_api_ctrl);

    /** Read packet if data is available.
     * @par Implemented as
     * - @ref R_ETHER_Read()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     * @param[in]  p_buffer     Pointer to where to store read data.
     * @param[in]  length_bytes Number of bytes in buffer
     */
    fsp_err_t (* read)(ether_ctrl_t * const p_api_ctrl, void * const p_buffer, uint32_t * const length_bytes);

    /** Release rx buffer from buffer pool process in zero-copy read operation.
     * @par Implemented as
     * - @ref R_ETHER_BufferRelease()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* bufferRelease)(ether_ctrl_t * const p_api_ctrl);

    /** Update the buffer pointer in the current receive descriptor.
     * @par Implemented as
     * - @ref R_ETHER_RxBufferUpdate()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     * @param[in]  p_buffer         New address to write into the rx buffer descriptor.
     */
    fsp_err_t (* rxBufferUpdate)(ether_ctrl_t * const p_api_ctrl, void * const p_buffer);

    /** Write packet.
     * @par Implemented as
     * - @ref R_ETHER_Write()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     * @param[in]  p_buffer     Pointer to data to write.
     * @param[in]  frame_length Send ethernet frame size (without 4 bytes of CRC data size).
     */
    fsp_err_t (* write)(ether_ctrl_t * const p_api_ctrl, void * const p_buffer, uint32_t const frame_length);

    /** Process link.
     * @par Implemented as
     * - @ref R_ETHER_LinkProcess()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* linkProcess)(ether_ctrl_t * const p_api_ctrl);

    /** Enable magic packet detection.
     * @par Implemented as
     * - @ref R_ETHER_WakeOnLANEnable()
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* wakeOnLANEnable)(ether_ctrl_t * const p_api_ctrl);

    /** Get the address of the most recently sent buffer.
     * @par Implemented as
     * - @ref R_ETHER_TxStatusGet()
     *
     * @param[in]   p_api_ctrl     Pointer to control structure.
     * @param[out]  p_buffer_address   Pointer to the address of the most recently sent buffer.
     */
    fsp_err_t (* txStatusGet)(ether_ctrl_t * const p_api_ctrl, void * const p_buffer_address);
} ether_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ether_instance
{
    ether_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    ether_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    ether_api_t const * p_api;         ///< Pointer to the API structure for this instance
} ether_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHER_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_ETHERNET_API_H */
