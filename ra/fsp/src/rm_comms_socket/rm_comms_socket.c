/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_comms_socket.h"
#include "../rm_comms_lock/rm_comms_lock.h"

#if !NO_SYS
 #include "lwip/tcpip.h"
 #include "lwip/priv/tcpip_priv.h"
#endif

#if LWIP_DHCP
 #include "lwip/dhcp.h"
 #include "lwip/prot/dhcp.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag "COSP" */
#define RM_COMMS_SOCKET_OPEN    (0x434F5350UL)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void rm_comms_socket_notify_application(rm_comms_socket_instance_ctrl_t const * p_ctrl, rm_comms_event_t event);

/* TCP callbacks */

#if LWIP_TCP
static err_t rm_comms_socket_tcp_sent(void * arg, struct tcp_pcb * tpcb, u16_t len);
static err_t rm_comms_socket_tcp_recv(void * arg, struct tcp_pcb * tpcb, struct pbuf * p, err_t err);
static void  rm_comms_socket_tcp_err(void * arg, err_t err);
static err_t rm_comms_socket_tcp_accept(void * arg, struct tcp_pcb * new_pcb, err_t err);

static err_t rm_comms_socket_tcp_write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);

 #if !NO_SYS
static void rm_comms_socket_tcp_rtos_write(rm_comms_socket_msg_t * msg);

 #endif

#endif

/* Common helpers */
static fsp_err_t rm_comms_socket_connect(rm_comms_socket_instance_ctrl_t * p_ctrl);
static void      rm_comms_socket_callback_handler(rm_comms_socket_instance_ctrl_t * p_ctrl,
                                                  rm_comms_socket_event_t           event);

#if !NO_SYS
static struct tcpip_msg * rm_comms_socket_new_msg_callback(rm_comms_socket_instance_ctrl_t * p_ctrl,
                                                           tcpip_callback_fn                 cb);
static void rm_comms_socket_rtos_connect(rm_comms_socket_instance_ctrl_t * p_ctrl);

#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_comms_api_t const g_comms_on_comms_socket =
{
    .open        = RM_COMMS_SOCKET_Open,
    .read        = RM_COMMS_SOCKET_Read,
    .write       = RM_COMMS_SOCKET_Write,
    .writeRead   = RM_COMMS_SOCKET_WriteRead,
    .callbackSet = RM_COMMS_SOCKET_CallbackSet,
    .close       = RM_COMMS_SOCKET_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_SOCKET
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the SOCKET Comms module. Implements @ref rm_comms_api_t::open.
 *
 *
 * @retval FSP_SUCCESS                  SOCKET Comms module successfully configured.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ABORTED              Module is not successfully open.
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_UNSUPPORTED          Socket type is not supported.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SOCKET_Open (rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if RM_COMMS_SOCKET_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(RM_COMMS_SOCKET_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg->p_extend);
#endif

    rm_comms_socket_extended_cfg_t * p_extend =
        (rm_comms_socket_extended_cfg_t *) p_cfg->p_extend;

#if !NO_SYS
    FSP_ERROR_RETURN(sys_sem_new(&p_ctrl->op_completed, 0) == ERR_OK, FSP_ERR_ABORTED);
#endif

    p_ctrl->p_cfg    = p_cfg;
    p_ctrl->p_extend = p_extend;

    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

    p_ctrl->pending_snd_buf = NULL;
    p_ctrl->pending_snd_len = 0;

    p_ctrl->pending_rcv_buf = NULL;
    p_ctrl->pending_rcv_len = 0;

    switch (p_extend->type)
    {
#if LWIP_TCP
        case RM_COMMS_SOCKET_TYPE_TCP:
        {
            p_ctrl->pcb_listener = tcp_new();
            break;
        }
#endif
        default:
        {
            return FSP_ERR_UNSUPPORTED;
        }
    }

    FSP_ERROR_RETURN(NULL != p_ctrl->pcb_listener, FSP_ERR_ABORTED);

#if BSP_CFG_RTOS
    if (NULL != p_extend->p_tx_mutex)
    {
        /* Init mutex for writing */
        err = rm_comms_recursive_mutex_initialize(p_extend->p_tx_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_rx_mutex)
    {
        /* Init mutex for reading */
        err = rm_comms_recursive_mutex_initialize(p_extend->p_rx_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_tx_semaphore)
    {
        /* Init semaphore for writing */
        err = rm_comms_semaphore_initialize(p_extend->p_tx_semaphore);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_rx_semaphore)
    {
        /* Init semaphore for reading */
        err = rm_comms_semaphore_initialize(p_extend->p_rx_semaphore);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

#if LWIP_TCP
    tcp_bind_netif(p_ctrl->pcb_listener, p_extend->p_lwip_ether->p_ctrl->p_netif);
    p_ctrl->netif_idx = p_ctrl->pcb_listener->netif_idx;
#endif

    rm_comms_socket_connect(p_ctrl);

    if (RM_COMMS_SOCKET_STAT_CONNECT_WAIT == p_ctrl->status)
    {
#if NO_SYS
        rm_comms_socket_connect(p_ctrl);
#else
        struct tcpip_msg * new_msg = rm_comms_socket_new_msg_callback(p_ctrl,
                                                                      (tcpip_callback_fn) rm_comms_socket_rtos_connect);

        tcpip_callbackmsg_trycallback_fromisr((struct tcpip_callback_msg *) new_msg);
#endif
    }

#if !NO_SYS
    p_ctrl->msg_idx = 0;
#endif

    /* Set open flag */
    p_ctrl->open = RM_COMMS_SOCKET_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Disables specified SOCKET Comms module. Implements @ref rm_comms_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_UNSUPPORTED      Socket type is not supported.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SOCKET_Close (rm_comms_ctrl_t * const p_api_ctrl)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if RM_COMMS_SOCKET_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl && NULL != p_ctrl->p_cfg && NULL != p_ctrl->p_extend);
    FSP_ERROR_RETURN(RM_COMMS_SOCKET_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    rm_comms_socket_extended_cfg_t * p_extend = p_ctrl->p_extend;

    switch (p_extend->type)
    {
#if LWIP_TCP
        case RM_COMMS_SOCKET_TYPE_TCP:
        {
            tcp_abort(p_ctrl->pcb.tcp);
            err_t lwip_err = tcp_close(p_ctrl->pcb_listener);
            if (lwip_err != ERR_OK)
            {
                tcp_abort(p_ctrl->pcb_listener);
            }

            break;
        }
#endif
        default:
        {
            return FSP_ERR_UNSUPPORTED;
        }
    }

#if !NO_SYS
    sys_sem_free(&p_ctrl->op_completed);
#endif

    p_ctrl->pcb_listener = NULL;
    p_ctrl->pcb.tcp      = NULL;
    p_ctrl->status       = RM_COMMS_SOCKET_STAT_IDLE;

#if BSP_CFG_RTOS
    if (NULL != p_extend->p_tx_mutex)
    {
        err = rm_comms_recursive_mutex_destroy(p_extend->p_tx_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_rx_mutex)
    {
        err = rm_comms_recursive_mutex_destroy(p_extend->p_rx_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_tx_semaphore)
    {
        err = rm_comms_semaphore_destroy(p_extend->p_tx_semaphore);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_rx_semaphore)
    {
        err = rm_comms_semaphore_destroy(p_extend->p_rx_semaphore);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Clear open flag */
    p_ctrl->open = 0;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Updates the SOCKET Comms callback. Implements @ref rm_comms_api_t::callbackSet.
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SOCKET_CallbackSet (rm_comms_ctrl_t * const p_api_ctrl,
                                       void (                * p_callback)(rm_comms_callback_args_t *),
                                       void * const            p_context)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SOCKET_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(RM_COMMS_SOCKET_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Performs a read from the SOCKET bus. Implements @ref rm_comms_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_ENABLED      Operation is disabled when there is no TCP connection.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @note   Do not call this API in Interrupt function when enabling mutex or semaphore
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SOCKET_Read (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if RM_COMMS_SOCKET_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl && NULL != p_ctrl->p_extend);
    FSP_ASSERT(NULL != p_dest);
    FSP_ERROR_RETURN(RM_COMMS_SOCKET_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_ERROR_RETURN((RM_COMMS_SOCKET_STAT_CONNECTED == p_ctrl->status), FSP_ERR_NOT_ENABLED);

#if BSP_CFG_RTOS
    fsp_err_t sem_err   = FSP_SUCCESS;
    fsp_err_t mutex_err = FSP_SUCCESS;

    rm_comms_socket_extended_cfg_t * p_extend = p_ctrl->p_extend;

    if (NULL != p_extend->p_rx_mutex)
    {
        /* Acquire read mutex */
        mutex_err = rm_comms_recursive_mutex_acquire(p_extend->p_rx_mutex, p_extend->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == mutex_err, mutex_err);
    }
#endif

#if LWIP_TCP
    p_ctrl->pending_rcv_buf = p_dest;
    p_ctrl->pending_rcv_len = bytes;
#else
    err = FSP_ERR_UNSUPPORTED;
#endif

#if BSP_CFG_RTOS
    if ((FSP_SUCCESS == err) && (NULL != p_extend->p_rx_semaphore))
    {
        /* Wait for read to complete */
        sem_err = rm_comms_semaphore_acquire(p_extend->p_rx_semaphore, p_ctrl->p_cfg->semaphore_timeout);
    }

    if (NULL != p_extend->p_rx_mutex)
    {
        /* Release read mutex */
        mutex_err = rm_comms_recursive_mutex_release(p_extend->p_rx_mutex);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == sem_err, sem_err);
    FSP_ERROR_RETURN(FSP_SUCCESS == mutex_err, mutex_err);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @brief Performs a write to the SOCKET bus. Implements @ref rm_comms_api_t::write.
 *
 * @retval FSP_SUCCESS              Successfully writing data .
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_WRITE_FAILED     No bytes were transferred.
 * @retval FSP_ERR_NOT_ENABLED      Operation is disabled when there is no active TCP connection.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @note   Do not call this API in Interrupt function when enabling mutex or semaphore
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SOCKET_Write (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    err_t lwip_err = ERR_OK;
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SOCKET_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl && NULL != p_ctrl->p_extend);
    FSP_ASSERT(NULL != p_src);
    FSP_ERROR_RETURN(RM_COMMS_SOCKET_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_ERROR_RETURN((RM_COMMS_SOCKET_STAT_CONNECTED == p_ctrl->status), FSP_ERR_NOT_ENABLED);
    rm_comms_socket_extended_cfg_t * p_extend = p_ctrl->p_extend;

#if BSP_CFG_RTOS
    fsp_err_t sem_err   = FSP_SUCCESS;
    fsp_err_t mutex_err = FSP_SUCCESS;

    if (NULL != p_extend->p_tx_mutex)
    {
        /* Acquire write mutex */
        mutex_err = rm_comms_recursive_mutex_acquire(p_extend->p_tx_mutex, p_extend->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == mutex_err, mutex_err);
    }
#endif

#if !NO_SYS
    rm_comms_socket_msg_t msg =
    {
        .p_ctrl = p_ctrl,
        .bytes  = bytes,
        .p_src  = p_src,
    };
#endif

    switch (p_extend->type)
    {
#if LWIP_TCP
        case RM_COMMS_SOCKET_TYPE_TCP:
        {
            p_ctrl->total_snd_len = bytes;
 #if NO_SYS
            lwip_err = rm_comms_socket_tcp_write(p_ctrl, p_src, bytes);
 #else
            (void) tcpip_send_msg_wait_sem((tcpip_callback_fn) rm_comms_socket_tcp_rtos_write,
                                           &msg,
                                           &p_ctrl->op_completed);
            lwip_err = msg.err;
 #endif
            break;
        }
#endif
        default:
        {
            lwip_err = ERR_VAL;
            break;
        }
    }

#if BSP_CFG_RTOS
    if ((ERR_OK == lwip_err) && (NULL != p_extend->p_tx_semaphore))
    {
        /* Wait for write to complete */
        sem_err = rm_comms_semaphore_acquire(p_extend->p_tx_semaphore, p_ctrl->p_cfg->semaphore_timeout);
    }

    if (NULL != p_extend->p_tx_mutex)
    {
        /* Release write mutex */
        mutex_err = rm_comms_recursive_mutex_release(p_extend->p_tx_mutex);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == sem_err, sem_err);
    FSP_ERROR_RETURN(FSP_SUCCESS == mutex_err, mutex_err);
#endif

    return (lwip_err == ERR_OK) ? FSP_SUCCESS : FSP_ERR_WRITE_FAILED;
}

/*******************************************************************************************************************//**
 * @brief Performs simultaneous read and write. Implements @ref rm_comms_api_t::writeRead..
 *
 * @retval FSP_SUCCESS              Transfer was started successfully.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Read bytes and write bytes are not the same.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SOCKET_WriteRead (rm_comms_ctrl_t * const            p_api_ctrl,
                                     rm_comms_write_read_params_t const write_read_params)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(write_read_params);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_SOCKET)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/
void rm_comms_socket_notify_application (rm_comms_socket_instance_ctrl_t const * p_ctrl, rm_comms_event_t event)
{
    if (p_ctrl->p_callback)
    {
        rm_comms_callback_args_t args =
        {
            .p_context = p_ctrl->p_context,
            .event     = event,
        };

        p_ctrl->p_callback(&args);
    }
}

#if !NO_SYS

static void rm_comms_socket_rtos_connect (rm_comms_socket_instance_ctrl_t * p_ctrl) {
    rm_comms_socket_connect(p_ctrl);
}

#endif

/*******************************************************************************************************************//**
 * @brief Private function handles Socket connection request.
 **********************************************************************************************************************/
static fsp_err_t rm_comms_socket_connect (rm_comms_socket_instance_ctrl_t * p_ctrl)
{
    rm_comms_socket_extended_cfg_t * p_extend = p_ctrl->p_extend;
    struct netif * p_netif      = p_extend->p_lwip_ether->p_ctrl->p_netif;
    bool           connect_wait = !netif_is_link_up(p_netif);

    if (connect_wait)
    {
        p_ctrl->status = RM_COMMS_SOCKET_STAT_CONNECT_WAIT;

        return FSP_ERR_ABORTED;
    }

    switch (p_extend->type)
    {
#if LWIP_TCP
        case RM_COMMS_SOCKET_TYPE_TCP:
        {
            tcp_bind(p_ctrl->pcb_listener, NULL, p_ctrl->p_extend->port);
            p_ctrl->pcb_listener = tcp_listen(p_ctrl->pcb_listener);
            tcp_arg(p_ctrl->pcb_listener, p_ctrl);
            tcp_accept(p_ctrl->pcb_listener, rm_comms_socket_tcp_accept);
            p_ctrl->status = RM_COMMS_SOCKET_STAT_LISTENING;
            break;
        }
#endif
        default:
        {
            return FSP_ERR_UNSUPPORTED;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Private common callback handles internal Socket events
 **********************************************************************************************************************/
static void rm_comms_socket_callback_handler (rm_comms_socket_instance_ctrl_t * p_ctrl, rm_comms_socket_event_t event)
{
#if BSP_CFG_RTOS
    rm_comms_socket_extended_cfg_t * p_extend = p_ctrl->p_extend;
#endif

    switch (event)
    {
#if LWIP_TCP
        case RM_COMMS_SOCKET_TCP_CONNECTED:
        {
            p_ctrl->status = RM_COMMS_SOCKET_STAT_CONNECTED;

            rm_comms_socket_notify_application(p_ctrl, RM_COMMS_EVENT_OPERATION_COMPLETE);

            break;
        }
#endif
        case RM_COMMS_SOCKET_TX_COMPLETE:
        {
#if BSP_CFG_RTOS
            if (NULL != p_extend->p_tx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_tx_semaphore);
            }
#endif
            rm_comms_socket_notify_application(p_ctrl, RM_COMMS_EVENT_TX_OPERATION_COMPLETE);

            break;
        }

        case RM_COMMS_SOCKET_RX_COMPLETE:
        {
#if BSP_CFG_RTOS
            if (NULL != p_extend->p_rx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_rx_semaphore);
            }
#endif
            rm_comms_socket_notify_application(p_ctrl, RM_COMMS_EVENT_RX_OPERATION_COMPLETE);

            break;
        }

        case RM_COMMS_SOCKET_ERROR:
        {
#if BSP_CFG_RTOS
            if (NULL != p_extend->p_tx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_tx_semaphore);
            }

            if (NULL != p_extend->p_rx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_rx_semaphore);
            }
#endif
            rm_comms_socket_notify_application(p_ctrl, RM_COMMS_EVENT_ERROR);

            switch (p_ctrl->p_extend->type)
            {
#if LWIP_TCP
                case RM_COMMS_SOCKET_TYPE_TCP:
                {
                    if (p_ctrl->pcb.tcp != NULL)
                    {
                        tcp_abort(p_ctrl->pcb.tcp);
                        p_ctrl->pcb.tcp = NULL;
                    }

                    p_ctrl->status = RM_COMMS_SOCKET_STAT_IDLE;

                    break;
                }
#endif
                default:
                {
                    break;
                }
            }

            p_ctrl->status = RM_COMMS_SOCKET_STAT_IDLE;

            break;
        }

        default:
        {
            break;
        }
    }
}

#if !NO_SYS

/*******************************************************************************************************************//**
 * @brief A private ring buffer provides a static tcpip callback message.
 **********************************************************************************************************************/
static struct tcpip_msg * rm_comms_socket_new_msg_callback (rm_comms_socket_instance_ctrl_t * p_ctrl,
                                                            tcpip_callback_fn                 cb)
{
    p_ctrl->msg_idx = (uint8_t) (p_ctrl->msg_idx + 1) % RM_COMMS_SOCKET_MSG_POOL_SIZE;
    struct tcpip_msg * p_msg = &p_ctrl->msgs[p_ctrl->msg_idx];
    p_msg->msg.cb.function = cb;
    p_msg->msg.cb.ctx      = (void *) p_ctrl;
    p_msg->type            = TCPIP_MSG_CALLBACK_STATIC;

    return &p_ctrl->msgs[p_ctrl->msg_idx];
}

#endif

#if LWIP_TCP

/*******************************************************************************************************************//**
 * @brief TCP callback waits for a TCP connection request from the other end.
 **********************************************************************************************************************/
static err_t rm_comms_socket_tcp_accept (void * arg, struct tcp_pcb * new_pcb, err_t err)
{
    err_t ret_err = ERR_OK;
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) arg;

    if ((err != ERR_OK) || (p_ctrl == NULL) || (new_pcb == NULL) || (p_ctrl->pcb.tcp != NULL))
    {
        ret_err = ERR_VAL;
    }
    else
    {
        p_ctrl->pcb.tcp = new_pcb;
        tcp_arg(p_ctrl->pcb.tcp, p_ctrl);
        tcp_sent(p_ctrl->pcb.tcp, rm_comms_socket_tcp_sent);
        tcp_recv(p_ctrl->pcb.tcp, rm_comms_socket_tcp_recv);
        tcp_err(p_ctrl->pcb.tcp, rm_comms_socket_tcp_err);

        rm_comms_socket_callback_handler(p_ctrl, RM_COMMS_SOCKET_TCP_CONNECTED);
    }

    return ret_err;
}

/*******************************************************************************************************************//**
 * @brief Function splits user data into maximum TCP payload packets.
 **********************************************************************************************************************/
err_t rm_comms_socket_tcp_write (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) p_api_ctrl;

    err_t            err = ERR_OK;
    struct tcp_pcb * pcb = p_ctrl->pcb.tcp;

    uint8_t * buf = p_src;
    uint32_t  len = bytes;

    while (len > 0)
    {
        u16_t send_len = (uint16_t) LWIP_MIN(TCP_MSS, len);

        err = tcp_write(pcb, buf, (uint16_t) send_len, 0);
        if (err != ERR_OK)
        {
            break;
        }

        len -= send_len;
        buf += send_len;
    }

    p_ctrl->pending_snd_buf = buf;
    p_ctrl->pending_snd_len = len;

    if (len < bytes)
    {
        err = tcp_output(pcb);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief TCP error callback removes TCP's pcb when there is error events reported.
 **********************************************************************************************************************/
static void rm_comms_socket_tcp_err (void * arg, err_t err)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) arg;

    p_ctrl->pcb.tcp = NULL;
    rm_comms_socket_callback_handler(p_ctrl, RM_COMMS_SOCKET_ERROR);

    FSP_PARAMETER_NOT_USED(err);
};

/*******************************************************************************************************************//**
 * @brief TCP callback handles complete data transmission
 **********************************************************************************************************************/
static err_t rm_comms_socket_tcp_sent (void * arg, struct tcp_pcb * tpcb, u16_t len)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) arg;

    err_t err = ERR_OK;

    FSP_ERROR_RETURN(RM_COMMS_SOCKET_STAT_CONNECTED == p_ctrl->status, FSP_ERR_NOT_ENABLED);

    p_ctrl->total_snd_len -= len;

    if (p_ctrl->pending_snd_len > 0)
    {
        err = rm_comms_socket_tcp_write(p_ctrl, p_ctrl->pending_snd_buf, p_ctrl->pending_snd_len);
    }
    else if (0 == p_ctrl->total_snd_len)
    {
        rm_comms_socket_callback_handler(p_ctrl, RM_COMMS_SOCKET_TX_COMPLETE);
    }
    else
    {
        // Do nothing
    }

    FSP_PARAMETER_NOT_USED(tpcb);
    FSP_PARAMETER_NOT_USED(len);

    return err;
}

/*******************************************************************************************************************//**
 * @brief TCP callback handles data received
 **********************************************************************************************************************/
static err_t rm_comms_socket_tcp_recv (void * arg, struct tcp_pcb * tpcb, struct pbuf * p, err_t err)
{
    rm_comms_socket_instance_ctrl_t * p_ctrl = (rm_comms_socket_instance_ctrl_t *) arg;

    if ((p_ctrl == NULL) || (p_ctrl->pcb.tcp != tpcb))
    {
        return ERR_VAL;
    }

    if ((p != NULL) &&
        (p_ctrl->pending_rcv_buf != NULL) &&
        (p_ctrl->pending_rcv_len > 0))
    {
        uint16_t recv_len = p->tot_len;
        if (recv_len > p_ctrl->pending_rcv_len)
        {
            recv_len = (uint16_t) p_ctrl->pending_rcv_len;
        }

        memcpy(p_ctrl->pending_rcv_buf, p->payload, recv_len);

        p_ctrl->pending_rcv_len -= recv_len;
        p_ctrl->pending_rcv_buf += recv_len;

        if (p_ctrl->pending_rcv_len <= 0)
        {
            p_ctrl->pending_rcv_len = 0;
            p_ctrl->pending_rcv_buf = NULL;

            rm_comms_socket_callback_handler(p_ctrl, RM_COMMS_SOCKET_RX_COMPLETE);
        }
    }

    if (p != NULL)
    {
        tcp_recved(tpcb, p->tot_len);
        pbuf_free(p);
    }
    else
    {
        tcp_abort(tpcb);

        return ERR_ABRT;
    }

    FSP_PARAMETER_NOT_USED(err);

    return ERR_OK;
};

 #if !NO_SYS
void rm_comms_socket_tcp_rtos_write (rm_comms_socket_msg_t * msg) {
    msg->err = rm_comms_socket_tcp_write(msg->p_ctrl, msg->p_src, msg->bytes);
};
 #endif

#endif
