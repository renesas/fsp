/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_IPC_API_H
#define R_IPC_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SYSTEM_INTERFACES
 * @defgroup IPC_API IPC Interface
 * @brief Interface for inter-processor communications (IPC).
 *
 * @section IPC_INTERFACE_SUMMARY Summary
 * The IPC interface provides common APIs for IPC HAL drivers. The IPC interface supports the following features:
 *  - Sending and receiving messages between cores via IPC one-way FIFOs
 *  - Triggering maskable interrupts between cores
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IPC Events */
typedef enum e_ipc_event
{
    IPC_EVENT_IRQ0             = (1UL << 0),  ///< IRQ Event 0 set
    IPC_EVENT_IRQ1             = (1UL << 1),  ///< IRQ Event 1 set
    IPC_EVENT_IRQ2             = (1UL << 2),  ///< IRQ Event 2 set
    IPC_EVENT_IRQ3             = (1UL << 3),  ///< IRQ Event 3 set
    IPC_EVENT_IRQ4             = (1UL << 4),  ///< IRQ Event 4 set
    IPC_EVENT_IRQ5             = (1UL << 5),  ///< IRQ Event 5 set
    IPC_EVENT_IRQ6             = (1UL << 6),  ///< IRQ Event 6 set
    IPC_EVENT_IRQ7             = (1UL << 7),  ///< IRQ Event 7 set
    IPC_EVENT_MESSAGE_RECEIVED = (1UL << 16), ///< Message received over FIFO
    IPC_EVENT_FIFO_ERROR_EMPTY = (1UL << 24), ///< A read was attempted on an empty FIFO
    IPC_EVENT_FIFO_ERROR_FULL  = (1UL << 25), ///< Data couldn't be written to a full FIFO
} ipc_event_t;

/** IPC Generate Events */
typedef enum e_ipc_generate_event
{
    IPC_GENERATE_EVENT_IRQ0 = (1UL << 0), ///< Generate IRQ Event 0
    IPC_GENERATE_EVENT_IRQ1 = (1UL << 1), ///< Generate IRQ Event 1
    IPC_GENERATE_EVENT_IRQ2 = (1UL << 2), ///< Generate IRQ Event 2
    IPC_GENERATE_EVENT_IRQ3 = (1UL << 3), ///< Generate IRQ Event 3
    IPC_GENERATE_EVENT_IRQ4 = (1UL << 4), ///< Generate IRQ Event 4
    IPC_GENERATE_EVENT_IRQ5 = (1UL << 5), ///< Generate IRQ Event 5
    IPC_GENERATE_EVENT_IRQ6 = (1UL << 6), ///< Generate IRQ Event 6
    IPC_GENERATE_EVENT_IRQ7 = (1UL << 7), ///< Generate IRQ Event 7
} ipc_generate_event_t;

/** IPC Callback parameter definition */
typedef struct st_ipc_callback_args
{
    uint32_t    channel;               ///< IPC channel
    uint32_t    message;               ///< Received message data
    ipc_event_t event;                 ///< Event code
    void      * p_context;             ///< Context provided to user during callback
} ipc_callback_args_t;

/** IPC Configuration */
typedef struct st_ipc_cfg
{
    uint32_t channel;                  ///< IPC channel

    /** IPC IRQ number
     * @note Only required if the user wants to receive messages or interrupts over IPC.
     *       IRQ should be set to FSP_INVALID_VECTOR when not used.
     */
    IRQn_Type irq;

    /** IPC Interrupt priority
     * @note Only required if the user wants to receive messages or interrupts over IPC.
     */
    uint8_t ipl;

    /** Pointer to callback function
     * @note Only required if the user wants to receive messages or interrupts over IPC.
     *       p_callback should be set to NULL when not used.
     */
    void (* p_callback)(ipc_callback_args_t * p_args);
    void * p_context;                  ///< User defined context passed into callback function
} ipc_cfg_t;

/** IPC control block. Allocate an instance specific control block to pass into the IPC API calls.
 */
typedef void ipc_ctrl_t;

/** Interface definition for IPC */
typedef struct st_ipc_api
{
    /** Open IPC instance.
     *
     * @param[in,out]  p_ctrl   Pointer to the IPC control block. Must be declared by user. Value set here.
     * @param[in]      p_cfg    Pointer to IPC configuration structure. All elements of this structure must be set by
     *                           user.
     */
    fsp_err_t (* open)(ipc_ctrl_t * const p_ctrl, ipc_cfg_t const * const p_cfg);

    /** Send message through the FIFO of the configured IPC channel.
     * @note Should only be called from the core on the transmit side of the IPC channel.
     *
     * @param[in]   p_ctrl   Pointer to the IPC control block.
     * @param[in]   message  Message to send.
     */
    fsp_err_t (* messageSend)(ipc_ctrl_t * const p_ctrl, uint32_t message);

    /** Generate event through configured IPC channel interrupt.
     * @note Should only be called from the core on the transmit side of the IPC channel.
     *
     * @param[in]   p_ctrl     Pointer to the IPC control block.
     * @param[in]   event      Event to generate interrupt for.
     */
    fsp_err_t (* eventGenerate)(ipc_ctrl_t * const p_ctrl, ipc_generate_event_t event);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl            Pointer to the IPC control block.
     * @param[in]   p_callback        Callback function
     * @param[in]   p_context         Pointer to send to callback function
     * @param[in]   p_callback_memory Pointer to volatile memory where callback structure can be allocated.
     *                                 Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(ipc_ctrl_t * const p_ctrl, void (* p_callback)(ipc_callback_args_t *),
                              void * const p_context, ipc_callback_args_t * const p_callback_memory);

    /** Close IPC instance.
     *
     * @param[in]   p_ctrl     Pointer to the IPC control block.
     */
    fsp_err_t (* close)(ipc_ctrl_t * const p_ctrl);
} ipc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ipc_instance
{
    ipc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    ipc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    ipc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} ipc_instance_t;

/******************************************************************************************************************//**
 * @} (end defgroup IPC_API)
 *********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
