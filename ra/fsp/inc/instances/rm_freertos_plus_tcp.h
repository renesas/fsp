/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_FREERTOS_PLUS_TCP_H
#define RM_FREERTOS_PLUS_TCP_H

#include "r_ether_api.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

typedef struct st_rm_freertos_plus_tcp_cfg
{
    /* Ethernet driver */
    ether_instance_t * p_ether_instance;

    /* Priority for RX Handler task. */
    UBaseType_t rx_handler_task_priority;

    /* Stack size for RX Handler task. */
    configSTACK_DEPTH_TYPE rx_handler_task_stacksize;

    /* Priority for check link status task. */
    UBaseType_t check_link_status_task_priority;

    /* Stack size for check link status task. */
    configSTACK_DEPTH_TYPE check_link_status_task_stacksize;

    /* Interval of processing to check link status */
    TickType_t link_check_interval;
} rm_freertos_plus_tcp_cfg_t;

typedef struct st_rm_freertos_plus_tcp_ctrl
{
    /* Hold the handler of a task receiving packet */
    TaskHandle_t xRxHanderTaskHandle;

    /* Hold the handler of a task checking the link status. */
    TaskHandle_t xCheckLinkStatusTaskHandle;

    /* Pointer to the configuration structure */
    rm_freertos_plus_tcp_cfg_t const * p_cfg;

    /* Whether or not middleware instance is opened */
    uint32_t open;
} rm_freertos_plus_tcp_ctrl_t;

typedef struct st_rm_freertos_plus_tcp_instance
{
    rm_freertos_plus_tcp_ctrl_t * p_ctrl;
    rm_freertos_plus_tcp_cfg_t  * p_cfg;
} rm_freertos_plus_tcp_instance_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
