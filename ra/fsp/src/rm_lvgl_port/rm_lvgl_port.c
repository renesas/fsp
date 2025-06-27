/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_lvgl_port.h"
#include "rm_lvgl_port_cfg.h"

#include "r_glcdc.h"

#if (BSP_CFG_RTOS == 2)
 #include "FreeRTOS.h"
 #include "semphr.h"
#else
 #include "bsp_api.h"
#endif

#include "lv_display.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_LVGL_PORT_OPEN              (('L' << 24U) | ('V' << 16U) | ('G' << 8U) | ('L' << 0U))
#define RM_LVGL_PORT_PRV_SYSTICK_HZ    (1000U)

/***********************************************************************************************************************
 * External definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

void _rm_lvgl_port_display_callback(display_callback_args_t * p_args);

static void rm_lvgl_port_flush_cb(lv_display_t * p_lv_display, const lv_area_t * p_lv_area, uint8_t * p_px_map);
static void rm_lvgl_port_flush_wait_cb(lv_display_t * p_lv_display);

#if RM_LVGL_PORT_CFG_PROVIDE_TICK_CALLBACK
static uint32_t rm_lvgl_port_tick_get_cb(void);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
#if (BSP_CFG_RTOS == 2)
static SemaphoreHandle_t g_semaphore_vpos;
static StaticSemaphore_t g_semaphore_buffer_vpos;
#else
static volatile uint8_t  g_vpos_flag;
static volatile uint32_t g_systick_ms;
#endif

/***********************************************************************************************************************
 * Functions
 ***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_LVGL_PORT
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open the LVGL port driver module.
 *
 * Example:
 * @snippet rm_lvgl_port_example.c RM_LVGL_PORT_Open
 *
 * @note This function should be called after the LVGL function lv_init() has been called.
 *
 * @retval FSP_SUCCESS LVGL port successfully opened.
 * @retval FSP_ERR_OUT_OF_MEMORY Internal call to lv_display_create() failed to allocate memory for a display.
 *
 * See @ref Common_Error_Codes for other possible return codes. This function calls R_GLCDC_Open(), R_GLCDC_Start(), and
 * R_GLCDC_BufferChange().
 **********************************************************************************************************************/
fsp_err_t RM_LVGL_PORT_Open (rm_lvgl_port_instance_ctrl_t * const p_instance_ctrl,
                             rm_lvgl_port_cfg_t const * const     p_cfg)
{
#if RM_LVGL_PORT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ERROR_RETURN(RM_LVGL_PORT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    fsp_err_t error;

#if (BSP_CFG_RTOS == 2)
    g_semaphore_vpos = xSemaphoreCreateBinaryStatic(&g_semaphore_buffer_vpos);
#endif

    p_instance_ctrl->p_display_instance  = p_cfg->p_display_instance;
    p_instance_ctrl->inherit_frame_layer = p_cfg->inherit_frame_layer;
    p_instance_ctrl->p_framebuffer_0     = p_cfg->p_framebuffer_0;
    p_instance_ctrl->p_framebuffer_1     = p_cfg->p_framebuffer_1;
    p_instance_ctrl->p_callback          = p_cfg->p_callback;

    if (NULL != p_instance_ctrl->p_framebuffer_0)
    {
        memset(p_instance_ctrl->p_framebuffer_0, 0,
               (LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT * LVGL_DISPLAY_VSIZE_INPUT));
    }

    if (NULL != p_instance_ctrl->p_framebuffer_1)
    {
        memset(p_instance_ctrl->p_framebuffer_1, 0,
               (LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT * LVGL_DISPLAY_VSIZE_INPUT));
    }

    error = R_GLCDC_Open(p_instance_ctrl->p_display_instance->p_ctrl, p_instance_ctrl->p_display_instance->p_cfg);
    FSP_ERROR_RETURN(error == FSP_SUCCESS, error);

    error = R_GLCDC_Start(p_instance_ctrl->p_display_instance->p_ctrl);
    if (error != FSP_SUCCESS)
    {
        R_GLCDC_Close(p_instance_ctrl->p_display_instance->p_ctrl);
        FSP_ERROR_RETURN(error == FSP_SUCCESS, error);
    }

    /* Display the inactive buffer if double-buffering is used. */
    if (NULL != p_instance_ctrl->p_framebuffer_1)
    {
        do
        {
            error = R_GLCDC_BufferChange(p_instance_ctrl->p_display_instance->p_ctrl,
                                         p_instance_ctrl->p_framebuffer_1,
                                         p_instance_ctrl->inherit_frame_layer);
        } while (FSP_ERR_INVALID_UPDATE_TIMING == error);

        if (error != FSP_SUCCESS)
        {
            R_GLCDC_Close(p_instance_ctrl->p_display_instance->p_ctrl);
            FSP_ERROR_RETURN(error == FSP_SUCCESS, error);
        }
    }

    p_instance_ctrl->p_lv_display = lv_display_create(LVGL_DISPLAY_HSIZE_INPUT, LVGL_DISPLAY_VSIZE_INPUT);

    if (NULL == p_instance_ctrl->p_lv_display)
    {
        R_GLCDC_Close(p_instance_ctrl->p_display_instance->p_ctrl);

        return FSP_ERR_OUT_OF_MEMORY;
    }

    lv_display_set_flush_cb(p_instance_ctrl->p_lv_display, rm_lvgl_port_flush_cb);
    lv_display_set_flush_wait_cb(p_instance_ctrl->p_lv_display, rm_lvgl_port_flush_wait_cb);
    lv_display_set_buffers_with_stride(p_instance_ctrl->p_lv_display,
                                       p_instance_ctrl->p_framebuffer_0,
                                       p_instance_ctrl->p_framebuffer_1,
                                       (LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT * LVGL_DISPLAY_VSIZE_INPUT),
                                       LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT,
                                       LV_DISPLAY_RENDER_MODE_DIRECT);

#if RM_LVGL_PORT_CFG_PROVIDE_TICK_CALLBACK
 #if (BSP_CFG_RTOS == 0)
    SysTick_Config(SystemCoreClock / RM_LVGL_PORT_PRV_SYSTICK_HZ);
 #endif

    lv_tick_set_cb(rm_lvgl_port_tick_get_cb);
#endif

    p_instance_ctrl->open = RM_LVGL_PORT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_LVGL_PORT)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Callback function for LVGL Port. This function is called back from a Display HAL driver module.
 * If DISPLAY_EVENT_LINE_DETECTION is returned from Display HAL driver module, it sets the semaphore for rendering and
 * displaying synchronization. This function invokes a user callback function if registered through RM_LVGL_PORT_Open()
 * function.
 * @param[in]    p_args   Pointer to the Display interface callback argument.
 **********************************************************************************************************************/
void _rm_lvgl_port_display_callback (display_callback_args_t * p_args)
{
    rm_lvgl_port_callback_args_t cb_arg;

    if (DISPLAY_EVENT_LINE_DETECTION == p_args->event)
    {
#if (BSP_CFG_RTOS == 2)
        BaseType_t context_switch;

        xSemaphoreGiveFromISR(g_semaphore_vpos, &context_switch);
        portYIELD_FROM_ISR(context_switch);
#else
        g_vpos_flag = 1;
#endif
        cb_arg.event = RM_LVGL_PORT_EVENT_DISPLAY_VPOS;
    }
    else if ((DISPLAY_EVENT_GR1_UNDERFLOW == p_args->event) || (DISPLAY_EVENT_GR2_UNDERFLOW == p_args->event))
    {
        cb_arg.event = RM_LVGL_PORT_EVENT_UNDERFLOW;
    }
    else
    {
    }

    if (g_lvgl_port_ctrl.p_callback)
    {
        cb_arg.device = RM_LVGL_PORT_DEVICE_DISPLAY;
        cb_arg.error  = FSP_SUCCESS;
        g_lvgl_port_ctrl.p_callback(&cb_arg);
    }
}

/*******************************************************************************************************************//**
 * @brief Display flush callback required for LVGL.
 * @param[in] p_lv_display Pointer to the lv_display_t which is being flushed.
 * @param[in] p_lv_area Pointer to an lv_area_t which is the destination region in the frame buffer to copy the render
 * buffer data to, given in pixel coordinates.
 * @param[in] p_px_map Pointer to the render buffer from which pixel data should be copied.
 **********************************************************************************************************************/
static void rm_lvgl_port_flush_cb (lv_display_t * p_lv_display, const lv_area_t * p_lv_area, uint8_t * p_px_map)
{
    fsp_err_t error;
    FSP_PARAMETER_NOT_USED(p_lv_area);

    if (lv_display_flush_is_last(p_lv_display))
    {
#if BSP_CFG_DCACHE_ENABLED
        SCB_CleanInvalidateDCache_by_Addr(p_px_map,
                                          (LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT * LVGL_DISPLAY_VSIZE_INPUT));
#endif
        do
        {
            error = R_GLCDC_BufferChange(g_lvgl_port_ctrl.p_display_instance->p_ctrl,
                                         p_px_map,
                                         g_lvgl_port_ctrl.inherit_frame_layer);
        } while (FSP_ERR_INVALID_UPDATE_TIMING == error);
    }
    else
    {
    }
}

/*******************************************************************************************************************//**
 * @brief Display flush wait callback required for LVGL.
 * @param[in] p_lv_display Pointer to the lv_display_t which is being waited upon.
 **********************************************************************************************************************/
static void rm_lvgl_port_flush_wait_cb (lv_display_t * p_lv_display)
{
    if (lv_display_flush_is_last(p_lv_display))
    {
#if (BSP_CFG_RTOS == 2)

        /* Try to take the semaphore once without waiting to clear it if already set, then take it again. */
        xSemaphoreTake(g_semaphore_vpos, 0);
        xSemaphoreTake(g_semaphore_vpos, portMAX_DELAY);
#else
        g_vpos_flag = 0;
        while (0 == g_vpos_flag)
        {
        }
#endif
    }
    else
    {
    }
}

#if RM_LVGL_PORT_CFG_PROVIDE_TICK_CALLBACK

/*******************************************************************************************************************//**
 * @brief Millisecond tick get callback required for LVGL.
 **********************************************************************************************************************/
static uint32_t rm_lvgl_port_tick_get_cb (void)
{
 #if (BSP_CFG_RTOS == 2)

    return (uint32_t) (pdTICKS_TO_MS(xTaskGetTickCount()));
 #else

    return g_systick_ms;
 #endif
}

 #if (BSP_CFG_RTOS == 0)
void SysTick_Handler(void);

void SysTick_Handler (void)
{
    g_systick_ms++;
}

 #endif

#endif
