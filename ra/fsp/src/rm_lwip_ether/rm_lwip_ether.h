/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_LWIP_ETHER_H
#define RM_LWIP_ETHER_H

#include "lwip/netif.h"
#include "r_ether_api.h"
#include "lwip/sys.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

typedef struct st_rm_lwip_ether_ctrl
{
    /* lwIP Network interface. */
    struct netif * p_netif;

    /* Whether the input thread is alive or not. */
    bool input_thread_exist;

    /* Mbox for notifing read complete. */
    sys_mbox_t * p_read_complete_mbox;

    /* Message to notify that the read process is complete.  */
    bool read_complete_message;
} rm_lwip_ether_ctrl_t;

typedef struct st_rm_lwip_ether_cfg
{
    /* Ethenet driver */
    ether_instance_t * p_ether_instance;

    /* Set flags indicating the capability of the netif. The meaning of each flag is defined in lwIP. */
    uint8_t flags;

    /* Set maximum transfer unit. */
    uint16_t mtu;

    /* Memory pool for receive buffer. */
    void const * p_rx_buffers_mempool;

    /* Memory pool for RX pbuf. */
    void const * p_rx_pbuf_mempool;

    /* Interval of processing to check link status  */
    uint32_t link_check_interval;

    /* Stack size for input thread. */
    int32_t input_thread_stacksize;

    /* Priority for input thread. */
    int32_t input_thread_priority;

    void       * p_context;
    void const * p_extend;
} rm_lwip_ether_cfg_t;

typedef struct st_rm_lwip_ether_instance
{
    rm_lwip_ether_ctrl_t * p_ctrl;
    rm_lwip_ether_cfg_t  * p_cfg;
} rm_lwip_ether_instance_t;

/* Pbuf customized for RX usage. */
typedef struct st_rm_lwip_rx_pbuf
{
    struct pbuf_custom         pbuf;
    void                     * p_buffer;
    rm_lwip_ether_instance_t * p_lwip_instance;
} rm_lwip_rx_pbuf_t;

err_t rm_lwip_ether_init(struct netif * netif);
void  rm_lwip_ether_callback(ether_callback_args_t * p_args);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
