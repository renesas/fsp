/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_LWIP_SYS_BAREMETAL_H
#define RM_LWIP_SYS_BAREMETAL_H

#include "lwip/sys.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

typedef struct st_rm_lwip_sys_baremetal_ctrl
{
    /* The one and only timeout list. */
    struct sys_timeo * p_next_timeout;

    /* Current timeout duration. */
    uint32_t current_timeout_due_time;

    /* Current system time [ms]. */
    uint32_t timer_count;
} rm_lwip_sys_baremetal_ctrl_t;

typedef struct st_rm_lwip_sys_baremetal_cfg
{
    /* Timer driver */
    const timer_instance_t * p_timer_instance;
} rm_lwip_sys_baremetal_cfg_t;

typedef struct st_rm_lwip_sys_baremetal_instance
{
    rm_lwip_sys_baremetal_ctrl_t * p_ctrl;
    rm_lwip_sys_baremetal_cfg_t  * p_cfg;
} rm_lwip_sys_baremetal_instance_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
