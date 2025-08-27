/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_SOCKET
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_SOCKET_H
#define RM_COMMS_SOCKET_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_comms_api.h"
#include "rm_comms_socket_cfg.h"
#include "rm_lwip_ether.h"
#include "lwip/netif.h"
#include "lwip/priv/tcpip_priv.h"

#if LWIP_TCP
 #include "lwip/tcp.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_COMMS_SOCKET_MSG_POOL_SIZE    10

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_rm_comms_socket_event
{
    RM_COMMS_SOCKET_TCP_CONNECTED,

    RM_COMMS_SOCKET_TX_COMPLETE,
    RM_COMMS_SOCKET_RX_COMPLETE,
    RM_COMMS_SOCKET_ERROR,
} rm_comms_socket_event_t;

typedef enum e_rm_comms_socket_type
{
    RM_COMMS_SOCKET_TYPE_TCP = 0,
} rm_comms_socket_type_t;

typedef enum e_rm_comms_socket_status
{
    RM_COMMS_SOCKET_STAT_IDLE         = 0,
    RM_COMMS_SOCKET_STAT_CONNECT_WAIT = 1,
    RM_COMMS_SOCKET_STAT_LISTENING    = 2,
    RM_COMMS_SOCKET_STAT_CONNECTED    = 3,
} rm_comms_socket_status_t;

/* LWIP device configuration */
typedef struct st_rm_comms_socket_extended_cfg
{
#if BSP_CFG_RTOS
    void * const   p_tx_mutex;         ///< Lock device for writing.
    void * const   p_rx_mutex;         ///< Lock device for reading.
    uint32_t const mutex_timeout;      ///< Timeout for locking device.
    void * const   p_tx_semaphore;     ///< Block write operations. If this is NULL then operations will be non-blocking and require a callback.
    void * const   p_rx_semaphore;     ///< Block read operations. If this is NULL then operations will be non-blocking and require a callback.
#endif
    uint16_t port;

    rm_comms_socket_type_t     type;
    rm_lwip_ether_instance_t * p_lwip_ether; ///< Pointer to Socket HAL interface to be used in the framework
} rm_comms_socket_extended_cfg_t;

/** Communications middleware control structure. */
typedef struct st_rm_comms_socket_instance_ctrl
{
    struct st_rm_comms_socket_instance_ctrl * next;
    uint32_t                         open;                  ///< Open flag
    rm_comms_cfg_t const           * p_cfg;                 ///< Middleware configuration
    rm_comms_socket_extended_cfg_t * p_extend;              ///< Pointer to device specific settings (lower level configuration structure)
    void (* p_callback)(rm_comms_callback_args_t * p_args); ///< Pointer to callback that is called when a socket_event_t occurs
    void * p_context;                                       ///< Pointer to context passed into callback function

    sys_sem_t op_completed;

    uint8_t netif_idx;

    struct tcp_pcb * pcb_listener;

    union
    {
        struct tcp_pcb * tcp;
    } pcb;

#if !NO_SYS
    uint8_t          msg_idx;
    struct tcpip_msg msgs[RM_COMMS_SOCKET_MSG_POOL_SIZE];
#endif

    uint32_t total_snd_len;

    uint8_t * pending_snd_buf;
    uint32_t  pending_snd_len;

    uint8_t * pending_rcv_buf;
    uint32_t  pending_rcv_len;

    rm_comms_socket_status_t status;
} rm_comms_socket_instance_ctrl_t;

struct rm_comms_socket_msg
{
    rm_comms_socket_instance_ctrl_t * p_ctrl;
    uint8_t * p_src;
    uint32_t  bytes;
    err_t     err;
};

typedef struct rm_comms_socket_msg rm_comms_socket_msg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern rm_comms_api_t const g_comms_on_comms_socket;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SOCKET_Open(rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg);
fsp_err_t RM_COMMS_SOCKET_Close(rm_comms_ctrl_t * const p_api_ctrl);
fsp_err_t RM_COMMS_SOCKET_Read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t RM_COMMS_SOCKET_Write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t RM_COMMS_SOCKET_WriteRead(rm_comms_ctrl_t * const            p_api_ctrl,
                                    rm_comms_write_read_params_t const write_read_params);
fsp_err_t RM_COMMS_SOCKET_CallbackSet(rm_comms_ctrl_t * const p_api_ctrl,
                                      void (                * p_callback)(rm_comms_callback_args_t *),
                                      void * const            p_context);

FSP_FOOTER

#endif                                 /* RM_COMMS_SOCKET_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_SOCKET)
 **********************************************************************************************************************/
