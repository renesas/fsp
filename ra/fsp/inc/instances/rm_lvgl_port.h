/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_LVGL_PORT
 * @{
 **********************************************************************************************************************/

#ifndef RM_LVGL_PORT_H
#define RM_LVGL_PORT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_display_api.h"
#include "lv_types.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Low level device code for the LVGL Port */
typedef enum e_rm_lvgl_port_device
{
    RM_LVGL_PORT_DEVICE_NONE    = 0,   ///< Non hardware
    RM_LVGL_PORT_DEVICE_DISPLAY = 1,   ///< Display device
} rm_lvgl_port_device_t;

/** Display event codes */
typedef enum e_rm_lvgl_port_event
{
    RM_LVGL_PORT_EVENT_DISPLAY_VPOS = 1, ///< Display interface VPOS
    RM_LVGL_PORT_EVENT_UNDERFLOW    = 2, ///< Display interface underflow
} rm_lvgl_port_event_t;

/** Callback arguments for the FSP LVGL Port */
typedef struct st_rm_lvgl_port_callback_args
{
    rm_lvgl_port_device_t device;      ///< Device code
    rm_lvgl_port_event_t  event;       ///< Event code of the low level hardware
    uint32_t              error;       ///< Error code if RM_LVGL_PORT_EVENT_ERROR
} rm_lvgl_port_callback_args_t;

/** Configuration structure for the FSP LVGL Port */
typedef struct st_rm_lvgl_port_cfg
{
    display_instance_t  * p_display_instance;                   // Pointer to a display instance
    display_frame_layer_t inherit_frame_layer;                  // Configured Inherit Screen Layer
    void                * p_framebuffer_0;                      // Pointer to frame buffer 0
    void                * p_framebuffer_1;                      // Pointer to frame buffer 1
    void (* p_callback)(rm_lvgl_port_callback_args_t * p_args); // Pointer to callback function
} rm_lvgl_port_cfg_t;

/** Instance control block for LVGL Port */
typedef struct st_rm_lvgl_port_instance_ctrl
{
    uint32_t              open;
    lv_display_t        * p_lv_display;                         // Pointer to the LVGL display context
    display_instance_t  * p_display_instance;                   // Pointer to a display instance
    display_frame_layer_t inherit_frame_layer;                  // Configured Inherit Screen Layer
    void                * p_framebuffer_0;                      // Pointer to frame buffer 0
    void                * p_framebuffer_1;                      // Pointer to frame buffer 1
    void (* p_callback)(rm_lvgl_port_callback_args_t * p_args); // Pointer to callback function
} rm_lvgl_port_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/
extern rm_lvgl_port_instance_ctrl_t g_lvgl_port_ctrl;
extern const rm_lvgl_port_cfg_t     g_lvgl_port_cfg;

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_LVGL_PORT_Open(rm_lvgl_port_instance_ctrl_t * const p_instance_ctrl,
                            rm_lvgl_port_cfg_t const * const     p_cfg);

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_LVGL_PORT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_LVGL_PORT_H
