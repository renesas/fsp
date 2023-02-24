/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_guix_port.h"
#include "rm_guix_port_cfg.h"

#include "r_glcdc.h"

#if GX_RENESAS_DAVE2D_DRAW
 #include "dave_driver.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Mutex timeout count */
#define RM_GUIX_PORT_MUTEX_WAIT_TIMER             (300)

/** Display device timeout count */
#define RM_GUIX_PORT_DISPLAY_HW_WAIT_COUNT_MAX    (5000)

/** A macro to mean GUIX color format invalid. */
#ifndef GX_COLOR_FORMAT_INVALID
 #define GX_COLOR_FORMAT_INVALID                  (0)
#endif

/***********************************************************************************************************************
 * External definitions
 **********************************************************************************************************************/
extern rm_guix_port_instance_ctrl_t _g_guix_port_ctrl;
extern rm_guix_port_cfg_t const     _g_guix_port_cfg;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
fsp_err_t rm_guix_port_hw_deinitialize(void);

static fsp_err_t rm_guix_port_driver_setup(GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl);

static fsp_err_t rm_guix_port_display_open(rm_guix_port_instance_ctrl_t * const p_ctrl);

static void rm_guix_port_canvas_clear(GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl);

void _rm_guix_port_display_callback(display_callback_args_t * p_args);

#if GX_RENESAS_DAVE2D_DRAW
static d2_s32 rm_guix_port_d2_open_format_get(GX_DISPLAY * p_display);

static fsp_err_t rm_guix_port_d2_open(GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl);

static fsp_err_t rm_guix_port_d2_close(rm_guix_port_instance_ctrl_t * const p_ctrl);

#endif

/* GUIX common callback functions setup function */
extern UINT _gx_ra_display_driver_setup(GX_DISPLAY * display);

/* GUIX FSP Port callback functions */
void rm_guix_port_frame_pointers_get(ULONG display_handle, GX_UBYTE ** pp_visible, GX_UBYTE ** pp_working);

void rm_guix_port_frame_toggle(ULONG display_handle, GX_BYTE ** pp_visible_frame);

void * rm_guix_port_jpeg_buffer_get(ULONG display_handle, INT * p_memory_size);

void * rm_guix_port_jpeg_instance_get(ULONG display_handle);

INT rm_guix_port_display_rotation_get(ULONG handle);

void rm_guix_port_display_actual_size_get(ULONG display_handle, INT * p_width, INT * p_height);

void rm_guix_port_display_8bit_palette_assign(ULONG display_handle);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static TX_SEMAPHORE gx_renesas_display_semaphore;
TX_SEMAPHORE        gx_renesas_jpeg_semaphore;

/* LUT for GX_COLOR_FORMAT_ macros corresponding to display_in_format_t enum values */
static const GX_VALUE gx_display_color_format_lut[8] =
{
    GX_COLOR_FORMAT_32ARGB,            // ARGB8888, 32 bits
    GX_COLOR_FORMAT_24XRGB,            // RGB888,   32 bits
    GX_COLOR_FORMAT_565RGB,            // RGB565,   16 bits
    GX_COLOR_FORMAT_INVALID,           // ARGB1555, 16 bits
    GX_COLOR_FORMAT_4444ARGB,          // ARGB4444, 16 bits
    GX_COLOR_FORMAT_8BIT_PALETTE,      // CLUT8
    GX_COLOR_FORMAT_INVALID,           // CLUT4
    GX_COLOR_FORMAT_INVALID,           // CLUT1
};

/***********************************************************************************************************************
 * Functions
 ***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_GUIX_PORT
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Callback function to be passed to gx_studio_display_configure in order to start hardware modules.
 *
 * Example:
 * @snippet rm_guix_port_example.c rm_guix_port_hw_initialize
 *
 * @note This function should only be called by GUIX.
 *
 * @retval  GX_SUCCESS    Device driver setup is successfully done.
 * @retval  GX_FAILURE    Device driver setup failed.
 **********************************************************************************************************************/
UINT rm_guix_port_hw_initialize (GX_DISPLAY * p_display)
{
    UINT      status;
    fsp_err_t error;

    /* Returns if GUIX display driver context is NULL. */
    if (NULL == p_display)
    {
        return (UINT) GX_FAILURE;
    }

    /** Creates a semaphore for frame buffer flip */
    status = tx_semaphore_create(&gx_renesas_display_semaphore, (CHAR *) "rm_guix_drv_display_sem", 0);
    if (TX_SUCCESS != status)
    {
        return GX_FAILURE;
    }

    /** Creates a semaphore for frame buffer flip */
    status = tx_semaphore_create(&gx_renesas_jpeg_semaphore, (CHAR *) "rm_guix_drv_jpeg_sem", 0);
    if (TX_SUCCESS != status)
    {
        tx_semaphore_delete(&gx_renesas_display_semaphore);

        return GX_FAILURE;
    }

    /** Initializes the RM_GUIX_PORT control block */
    _g_guix_port_ctrl.p_display_instance  = _g_guix_port_cfg.p_display_instance;
    _g_guix_port_ctrl.p_callback          = _g_guix_port_cfg.p_callback;
    _g_guix_port_ctrl.inherit_frame_layer = _g_guix_port_cfg.inherit_frame_layer;
    _g_guix_port_ctrl.p_framebuffer_read  = _g_guix_port_cfg.p_framebuffer_a;
    if (NULL != _g_guix_port_cfg.p_framebuffer_b)
    {
        _g_guix_port_ctrl.p_framebuffer_write = _g_guix_port_cfg.p_framebuffer_b;
    }
    else
    {
        /* If frame buffer B is NULL, specify frame buffer A instead. */
        _g_guix_port_ctrl.p_framebuffer_write = _g_guix_port_cfg.p_framebuffer_a;
    }

    _g_guix_port_ctrl.p_jpegbuffer     = _g_guix_port_cfg.p_jpegbuffer;
    _g_guix_port_ctrl.jpegbuffer_size  = _g_guix_port_cfg.jpegbuffer_size;
    _g_guix_port_ctrl.rendering_enable = false;
    _g_guix_port_ctrl.rotation_angle   = _g_guix_port_cfg.rotation_angle;
    _g_guix_port_ctrl.p_jpeg_instance  = _g_guix_port_cfg.p_jpeg_instance;

    /* Get the GUIX color format corresponding to the format configured for the Display module */
    p_display->gx_display_color_format =
        (GX_UBYTE) gx_display_color_format_lut[_g_guix_port_ctrl.p_display_instance->p_cfg->input[0].format];

    /* Check that the configured Display input format is compatible with GUIX */
    if (GX_COLOR_FORMAT_INVALID == (INT) p_display->gx_display_color_format)
    {
        FSP_ERROR_LOG(FSP_ERR_INVALID_ARGUMENT);

        tx_semaphore_delete(&gx_renesas_display_semaphore);
        tx_semaphore_delete(&gx_renesas_jpeg_semaphore);

        return (UINT) GX_FAILURE;
    }

    /** Copies the GX_DISPLAY context for later use. */
    _g_guix_port_ctrl.p_display = p_display;

    /** Setup GUIX low level device drivers */
    error = rm_guix_port_driver_setup(p_display, &_g_guix_port_ctrl);
    if (FSP_SUCCESS != error)
    {
        FSP_ERROR_LOG(error);

        tx_semaphore_delete(&gx_renesas_display_semaphore);
        tx_semaphore_delete(&gx_renesas_jpeg_semaphore);

        return (UINT) GX_FAILURE;
    }

    return (UINT) GX_SUCCESS;
}                                      /* End of function rm_guix_port_hw_initialize() */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_GUIX_PORT)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Optional function allowing clean deinitialization of hardware peripherals and semaphores if GUIX is stopped.
 *
 * @retval  FSP_SUCCESS                    Closed the module successfully.
 **********************************************************************************************************************/
fsp_err_t rm_guix_port_hw_deinitialize ()
{
    /** Stop display */
    uint32_t attempts = 10;
    while (FSP_SUCCESS != R_GLCDC_Close(_g_guix_port_ctrl.p_display_instance->p_ctrl) && (attempts-- > 0))
    {
        tx_thread_sleep(1);
    }

#if GX_RENESAS_DAVE2D_DRAW

    /** Stop DRW Engine */
    rm_guix_port_d2_close(&_g_guix_port_ctrl);
#endif

    /** Delete semaphores */
    tx_semaphore_delete(&gx_renesas_display_semaphore);
    tx_semaphore_delete(&gx_renesas_jpeg_semaphore);

    return FSP_SUCCESS;
}                                      /* End of function rm_guix_port_hw_deinitialize() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get frame buffer address.
 * This function is called by GUIX.
 * @param[in]     display_handle    Pointer to the RM_GUIX_PORT control block
 * @param[in,out] pp_visible        Pointer to a pointer to store visible frame buffer
 * @param[in,out] pp_working        Pointer to a pointer to store working frame buffer
 * @note NULL check for the frame buffers are not performed. This function does not expect NULL for them but does
 *       nothing even if the caller function passed NULL.
 **********************************************************************************************************************/
void rm_guix_port_frame_pointers_get (ULONG display_handle, GX_UBYTE ** pp_visible, GX_UBYTE ** pp_working)
{
    /** Gets control block */
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (display_handle);

    *pp_visible = p_ctrl->p_framebuffer_read;
    *pp_working = p_ctrl->p_framebuffer_write;
}                                      /* End of function rm_guix_port_frame_pointers_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, toggle frame buffer.
 * This function calls display_api_t::layerChange to flips the frame buffer and tx_semaphore_get to suspend a thread
 * until a display device going into blanking period.
 * This function is called by GUIX when following functions are executed.
 * - _gx_canvas_drawing_complete()
 * - _gx_system_canvas_refresh()
 * @param[in]     display_handle     Pointer to the RM_GUIX_PORT control block
 * @param[in,out] pp_visible_frame   Pointer to a pointer to store visible frame buffer
 **********************************************************************************************************************/
void rm_guix_port_frame_toggle (ULONG display_handle, GX_BYTE ** pp_visible_frame)
{
    /** Gets control block */
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) display_handle;

    /** Requests display driver to toggle frame buffer */
    R_GLCDC_BufferChange(p_ctrl->p_display_instance->p_ctrl, p_ctrl->p_framebuffer_write, p_ctrl->inherit_frame_layer);

    /** Updates the frame buffer addresses */
    void * p_next_temp = p_ctrl->p_framebuffer_read;
    p_ctrl->p_framebuffer_read  = p_ctrl->p_framebuffer_write;
    p_ctrl->p_framebuffer_write = p_next_temp;

    /** Returns the address of visible frame buffer */
    *(pp_visible_frame) = (GX_BYTE *) p_next_temp;

    /** Sets rendering_enable flag to the display driver to synchronize the timing */
    p_ctrl->rendering_enable = true;

    /** Waits until the set of semaphore which is set when the display device going into blanking period */
    tx_semaphore_get(&gx_renesas_display_semaphore, TX_WAIT_FOREVER);
}                                      /* End of function rm_guix_port_frame_toggle() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, Display interface setup function
 * This function calls display_api_t::open and display_api_t::start.
 * This function is called by rm_guix_port_driver_setup().
 * @param[in]    p_ctrl       Pointer to a RM_GUIX_PORT control block
 * @retval  FSP_SUCCESS       Display device was opened successfully.
 *
 * See @ref Common_Error_Codes for other possible return codes. This function calls
 * display_api_t::open and display_api_t::start.
 *
 * @note This function is only allowed to be called by rm_guix_port_driver_setup().
 * @note Parameter check is not required since it is done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static fsp_err_t rm_guix_port_display_open (rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t            error;
    display_instance_t * p_display_instance = p_ctrl->p_display_instance;

    /**  Display driver open */
    error = R_GLCDC_Open(p_display_instance->p_ctrl, p_display_instance->p_cfg);
    if (FSP_SUCCESS == error)
    {
        /**  Display driver start */
        error = R_GLCDC_Start(p_display_instance->p_ctrl);
    }

    return error;
}                                      /* End of function rm_guix_port_display_open() */

/*******************************************************************************************************************//**
 * @brief  Setups GUIX display driver.
 * This function calls _gx_ra_display_driver_setup(), which is generated by GUIX Studio, and calls subroutines
 * rm_guix_port_d2_open() and rm_guix_port_display_open() to setup graphics hardwares, also calls rm_guix_port_canvas_clear to clear
 * a canvas.
 * This function is called by rm_guix_port_hw_initialize().
 * @param[in]    p_display     Pointer to the GUIX display control block
 * @param[in]    p_ctrl        Pointer to a RM_GUIX_PORT control block
 * @retval  FSP_SUCCESS  The GUIX drivers are successfully configured.
 *
 * See @ref Common_Error_Codes for other possible return codes.
 * This function calls display_api_t::open and display_api_t::start.
 *
 * @note Parameter checks are not required since they are done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static fsp_err_t rm_guix_port_driver_setup (GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t error;

    /** Setups GUIX draw functions */
    _gx_ra_display_driver_setup(p_display);

#if GX_RENESAS_DAVE2D_DRAW

    /** Setups D/AVE 2D */
    error = rm_guix_port_d2_open(p_display, p_ctrl);
    FSP_ERROR_RETURN(error == FSP_SUCCESS, error);
#endif

    /** Clear canvas with zero */
    rm_guix_port_canvas_clear(p_display, p_ctrl);

    /** Setups Display interface */
    error = rm_guix_port_display_open(p_ctrl);
    FSP_ERROR_RETURN(error == FSP_SUCCESS, error);

    /** Registers the RM_GUIX_PORT context to GUIX display handle */
    p_display->gx_display_handle = (ULONG) p_ctrl;

    return FSP_SUCCESS;
}                                      /* End of function rm_guix_port_driver_setup() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, Canvas clear function, clear the frame buffers with zero.
 * This function is called by rm_guix_port_driver_setup().
 * @param[in]    p_display    Pointer to a GUIX display control block
 * @param[in]    p_ctrl       Pointer to a RM_GUIX_PORT control block
 * @retval  none.
 * @note This function is designed to be called by rm_guix_port_driver_setup().
 * @note Parameter checks are not required since they are done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static void rm_guix_port_canvas_clear (GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    int32_t divisor;
    ULONG * put;

    INT format = (INT) p_display->gx_display_color_format;

    /* Determine how many pixels are in one 32-bit span */
    if ((GX_COLOR_FORMAT_24XRGB == format) || (GX_COLOR_FORMAT_32ARGB == format))
    {
        divisor = 1;
    }
    else if ((GX_COLOR_FORMAT_565RGB == format) || (GX_COLOR_FORMAT_4444ARGB == format))
    {
        divisor = 2;
    }
    else
    {
        divisor = 4;
    }

    /** Clear the frame buffers */

    int32_t len = (p_display->gx_display_width * p_display->gx_display_height) / divisor;
    put = (ULONG *) p_ctrl->p_framebuffer_read;
    for (int32_t loop = 0; loop < len; loop++)
    {
        *put = 0UL;
        ++put;
    }

    put = (ULONG *) p_ctrl->p_framebuffer_write;
    for (int32_t loop = 0; loop < len; loop++)
    {
        *put = 0UL;
        ++put;
    }
}                                      /* End of function rm_guix_port_canvas_clear() */

#if GX_RENESAS_DAVE2D_DRAW

/*******************************************************************************************************************//**
 * @brief  rm_guix_port_d2_open sub-routine to select a D/AVE 2D color format corresponding to the GUIX color format.
 * This function is called by rm_guix_port_d2_open().
 * @param[in]    p_display     Pointer to a GUIX display control block
 * @retval  format             d2_mode_rgb565, d2_mode_argb4444, d2_mode_rgb888, d2_mode_argb8888 or d2_mode_clut.
 * @retval  FSP_ERR_D2D_ERROR_INIT      The D/AVE 2D returns error at the initialization.
 * @retval  FSP_ERR_D2D_ERROR_RENDERING The D/AVE 2D returns error at opening a display list buffer.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Specified display parameter is invalid.
 * @note This function is only allowed to be called by rm_guix_port_driver_setup().
 * @note Parameter check is not required since it is done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static d2_s32 rm_guix_port_d2_open_format_get (GX_DISPLAY * p_display)
{
    d2_s32 format = d2_mode_rgb565;

    /** Gets output color format of D/AVE 2D interface */
    switch ((INT) p_display->gx_display_color_format)
    {
        case GX_COLOR_FORMAT_565RGB:   ///< RGB565, 16 bits
        {
            /* Initial value applied */
            break;
        }

        case GX_COLOR_FORMAT_4444ARGB: ///< ARGB4444, 16 bits
        {
            format = d2_mode_argb4444;
            break;
        }

        case GX_COLOR_FORMAT_24XRGB:   ///< RGB888, 24 bits, unpacked
        {
            format = d2_mode_rgb888;
            break;
        }

        case GX_COLOR_FORMAT_32ARGB:   ///< ARGB8888, 32 bits
        {
            format = d2_mode_argb8888;
            break;
        }

        default:                       /* Apply 8-bit CLUT format for 8-bit Palette. */
        {
            format = d2_mode_clut;
            break;
        }
    }

    return format;
}

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP,D/AVE 2D(2D Drawing Engine) open function
 * This function calls following D/AVE 2D functions:
 * - d2_opendevice()           Creates a new device handle of the D/AVE 2D driver
 * - d2_inithw()               Initializes 2D Drawing Engine hardware
 * - d2_startframe()           Mark the begin of a scene
 * - d2_framebuffer()          Specifies the rendering target
 * This function is called by rm_guix_port_driver_setup().
 * @param[in]    p_display     Pointer to a GUIX display control block
 * @param[in]    p_ctrl        Pointer to a RM_GUIX_PORT control block
 * @retval  FSP_SUCCESS             The D/AVE 2D driver is successfully opened.
 * @retval  FSP_ERR_D2D_ERROR_INIT      The D/AVE 2D returns error at the initialization.
 * @retval  FSP_ERR_D2D_ERROR_RENDERING The D/AVE 2D returns error at opening a display list buffer.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Specified display parameter is invalid.
 * @note This function is only allowed to be called by rm_guix_port_driver_setup().
 * @note Parameter checks are not required since they are done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static fsp_err_t rm_guix_port_d2_open (GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    d2_s32 d2_err;

    /** Creates a device handle */
 #if !RM_GUIX_PORT_CFG_DRW_BURST_WRITE_ENABLED

    /* Disable the cache of the Dave2D so it doesn't do burst writes. */
    p_display->gx_display_accelerator = d2_opendevice(d2_df_no_fbcache);
 #else

    /* Enable the cache of the Dave2D so it perform burst writes. */
    p_display->gx_display_accelerator = d2_opendevice(0U);
 #endif

    /** Initializes 2D Drawing Engine hardware */
    d2_err = d2_inithw(p_display->gx_display_accelerator, 0);
    FSP_ERROR_RETURN(D2_OK == d2_err, FSP_ERR_D2D_ERROR_INIT);

    /** Opens a display list buffer for drawing commands */
    d2_err = d2_startframe(p_display->gx_display_accelerator);
    FSP_ERROR_RETURN(D2_OK == d2_err, FSP_ERR_D2D_ERROR_RENDERING);

    /** Gets output color format of D/AVE 2D interface */
    d2_s32 format = rm_guix_port_d2_open_format_get(p_display);

    /** Defines the framebuffer memory area and layout */
    d2_err = d2_framebuffer(p_display->gx_display_accelerator,
                            p_ctrl->p_framebuffer_write,
                            (d2_s32) p_display->gx_display_width,
                            (d2_u32) p_display->gx_display_width,
                            (d2_u32) p_display->gx_display_height,
                            format);
    FSP_ERROR_RETURN(D2_OK == d2_err, FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}                                      /* End of function rm_guix_port_d2_open() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, D/AVE 2D(2D Drawing Engine) close function
 * This function calls D/AVE 2D function d2_closedevice() to destroy a device handle.
 * This function is called by rm_guix_port_hw_deinitialize().
 * @param[in]    p_ctrl        Pointer to a RM_GUIX_PORT control block
 * @retval  FSP_SUCCESS              The D/AVE 2D driver is successfully closed.
 * @retval  FSP_ERR_D2D_ERROR_DEINIT  D/AVE 2D has an error in the initialization.
 * @note This function is only allowed to be called by rm_guix_port_hw_deinitialize().
 **********************************************************************************************************************/
static fsp_err_t rm_guix_port_d2_close (rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    d2_s32 d2_err;

    /** Destroy a device handle */
    d2_err = d2_closedevice(p_ctrl->p_display->gx_display_accelerator);
    FSP_ERROR_RETURN(D2_OK == d2_err, FSP_ERR_D2D_ERROR_DEINIT);

    return FSP_SUCCESS;
}                                      /* End of function rm_guix_port_d2_close() */

#endif

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get screen rotation angle.
 * This function is called by GUIX.
 * @param[in]   display_handle      Pointer to the RM_GUIX_PORT control block
 * @retval      Angle               Screen rotation angle. {0, 90, 180 or 270} is supposed to be returned.
 **********************************************************************************************************************/
INT rm_guix_port_display_rotation_get (ULONG display_handle)
{
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (display_handle);

    return (INT) (p_ctrl->rotation_angle);
}                                      /* End of function rm_guix_port_display_rotation_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get active video screen size.
 * This function is called by GUIX.
 * @param[in]     display_handle     Pointer to the RM_GUIX_PORT control block
 * @param[out]    p_width            Pointer to an int size memory to return screen width in pixels
 * @param[out]    p_height           Pointer to an int size memory to return screen height in pixels
 **********************************************************************************************************************/
void rm_guix_port_display_actual_size_get (ULONG display_handle, INT * p_width, INT * p_height)
{
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (display_handle);
    *p_width  = (INT) p_ctrl->p_display_instance->p_cfg->output.htiming.display_cyc;
    *p_height = (INT) p_ctrl->p_display_instance->p_cfg->output.vtiming.display_cyc;
}                                      /* End of function rm_guix_port_display_actual_size_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get JPEG work buffer address.
 * This function is called by GUIX.
 * @param[in]     display_handle    Pointer to the RM_GUIX_PORT control block
 * @param[in,out] p_memory_size     Pointer to caller defined variable to store JPEG work buffer
 * @retval        Address           JPEG work buffer address
 **********************************************************************************************************************/
void * rm_guix_port_jpeg_buffer_get (ULONG display_handle, INT * p_memory_size)
{
#if GX_USE_RENESAS_JPEG
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (display_handle);

    if (p_memory_size)
    {
        *p_memory_size = (INT) p_ctrl->jpegbuffer_size;
    }

    return p_ctrl->p_jpegbuffer;
#else
    FSP_PARAMETER_NOT_USED(display_handle);

    if (p_memory_size)
    {
        *p_memory_size = 0;
    }
    return NULL;
#endif
}                                      /* End of function rm_guix_port_jpeg_buffer_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get the instance of JPEG Framework module.
 * This function is called by _gx_renesas_jpeg_draw().
 * @param[in]     display_handle    Pointer to the RM_GUIX_PORT control block.
 * @retval        Address           Pointer to an instance of JPEG Framework module.
 **********************************************************************************************************************/
void * rm_guix_port_jpeg_instance_get (ULONG display_handle)
{
#if GX_USE_RENESAS_JPEG
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (display_handle);

    return p_ctrl->p_jpeg_instance;
#else
    FSP_PARAMETER_NOT_USED(display_handle);

    return NULL;
#endif
}                                      /* End of function rm_guix_port_jpeg_instance_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, set CLUT table in the display module by calling display_api_t::clut.
 * This function is called by GUIX.
 * @param[in]     display_handle     Pointer to the RM_GUIX_PORT control block
 **********************************************************************************************************************/
void rm_guix_port_display_8bit_palette_assign (ULONG display_handle)
{
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (display_handle);
    display_clut_cfg_t             clut_cfg;

    clut_cfg.p_base = (uint32_t *) p_ctrl->p_display->gx_display_palette;
    clut_cfg.start  = (uint16_t) 0;
    clut_cfg.size   = (uint16_t) p_ctrl->p_display->gx_display_palette_size;

    /* Write palette data to GLCDC CLUT */
    R_GLCDC_ClutUpdate(p_ctrl->p_display_instance->p_ctrl, &clut_cfg, p_ctrl->inherit_frame_layer);
}                                      /* End of function rm_guix_port_display_8bit_palette_assign() */

/*******************************************************************************************************************//**
 * @brief  Callback function for GUIX Port. This function is called back from a Display HAL driver module.
 * If DISPLAY_EVENT_LINE_DETECTION is returned from Display HAL driver module, it sets the semaphore for rendering and
 * displaying synchronization. This function invokes a user callback function if registered through rm_guix_port_hw_initialize()
 * function.
 * @param[in]    p_args   Pointer to the Display interface callback argument.
 **********************************************************************************************************************/
void _rm_guix_port_display_callback (display_callback_args_t * p_args)
{
    rm_guix_port_callback_args_t cb_arg;

    if (DISPLAY_EVENT_LINE_DETECTION == p_args->event)
    {
        if (_g_guix_port_ctrl.rendering_enable)
        {
            /** Let GUIX know the display been in blanking period */

            /* Return code not checked here as this RTOS object is called inside callback
             * function and there is no return from it */
            tx_semaphore_ceiling_put(&gx_renesas_display_semaphore, 1UL);
            _g_guix_port_ctrl.rendering_enable = false;
        }

        cb_arg.event = RM_GUIX_PORT_EVENT_DISPLAY_VSYNC;
    }
    else if (DISPLAY_EVENT_GR1_UNDERFLOW == p_args->event)
    {
        cb_arg.event = RM_GUIX_PORT_EVENT_UNDERFLOW;
    }
    else
    {
        /* Do nothing */
    }

    /** Invoke a user callback function if registered */
    if (_g_guix_port_ctrl.p_callback)
    {
        cb_arg.device = RM_GUIX_PORT_DEVICE_DISPLAY;
        cb_arg.error  = FSP_SUCCESS;
        _g_guix_port_ctrl.p_callback(&cb_arg);
    }
}                                      /* End of function rm_guix_port_callback() */
