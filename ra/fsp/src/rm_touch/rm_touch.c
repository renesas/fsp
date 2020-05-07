/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#ifdef QE_TOUCH_CONFIGURATION
 #include "qe_touch_define.h"
#endif
#include "rm_touch.h"
#include "r_ctsu.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef TOUCH_ERROR_RETURN

/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
 #define TOUCH_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/** "TOUC" in ASCII, used to determine if device is open. */
#define TOUCH_OPEN                            (0x544F5543ULL)

#define TOUCH_COUNT_MAX                       (0xFFFF)
#define TOUCH_OFF_VALUE                       (0xFFFF)
#define TOUCH_SLIDER_ELEMENTS_MIN             (3)
#define TOUCH_SLIDER_ELEMENTS_MAX             (10)
#define TOUCH_WHEEL_ELEMENTS_SMALL            (4)
#define TOUCH_WHEEL_ELEMENTS_LARGE            (8)
#define TOUCH_SLIDER_RESOLUTION               (100)
#define TOUCH_WHEEL_RESOLUTION                (360)
#define TOUCH_DECIMAL_POINT_PRECISION         (100)

#if TOUCH_CFG_MONITOR_ENABLE
 #define TOUCH_MONITOR_BLOCK_MAX              (8)
 #define TOUCH_MONITOR_HEADER_SIZE            (4)
 #define TOUCH_MONITOR_SELF_ELEMENT_SIZE      (2)
 #define TOUCH_MONITOR_MUTUAL_ELEMENT_SIZE    (4)
 #if (TOUCH_CFG_NUM_BUTTONS != 0)
  #define TOUCH_MONITOR_BHEAD_SIZE            (2)
 #else
  #define TOUCH_MONITOR_BHEAD_SIZE            (0)
 #endif
 #if (TOUCH_CFG_NUM_SLIDERS != 0)
  #define TOUCH_MONITOR_SHEAD_SIZE            (2)
 #else
  #define TOUCH_MONITOR_SHEAD_SIZE            (0)
 #endif
 #if (TOUCH_CFG_NUM_WHEELS != 0)
  #define TOUCH_MONITOR_WHEAD_SIZE            (2)
 #else
  #define TOUCH_MONITOR_WHEAD_SIZE            (0)
 #endif
 #define TOUCH_MONITOR_BUTTON_SIZE            (7)
 #define TOUCH_MONITOR_SLIDER_SIZE            (4)
 #define TOUCH_MONITOR_WHEEL_SIZE             (4)
 #define TOUCH_MONITOR_FOOTER_SIZE            (1)
 #define TOUCH_MONITOR_BUFFER_SIZE            ((TOUCH_MONITOR_HEADER_SIZE * TOUCH_MONITOR_BLOCK_MAX) +              \
                                               (TOUCH_MONITOR_SELF_ELEMENT_SIZE * CTSU_CFG_NUM_SELF_ELEMENTS) +     \
                                               (TOUCH_MONITOR_MUTUAL_ELEMENT_SIZE * CTSU_CFG_NUM_MUTUAL_ELEMENTS) + \
                                               (TOUCH_MONITOR_BHEAD_SIZE * TOUCH_MONITOR_BLOCK_MAX) +               \
                                               (TOUCH_MONITOR_BUTTON_SIZE * TOUCH_CFG_NUM_BUTTONS) +                \
                                               (TOUCH_MONITOR_SHEAD_SIZE * TOUCH_MONITOR_BLOCK_MAX) +               \
                                               (TOUCH_MONITOR_SLIDER_SIZE * TOUCH_CFG_NUM_SLIDERS) +                \
                                               (TOUCH_MONITOR_WHEAD_SIZE * TOUCH_MONITOR_BLOCK_MAX) +               \
                                               (TOUCH_MONITOR_WHEEL_SIZE * TOUCH_CFG_NUM_WHEELS) +                  \
                                               TOUCH_MONITOR_FOOTER_SIZE)

 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)

/* Monitor none value */
  #define TOUCH_UART_MONITOR_NONE             (0xFF)

/* Control byte */
  #define TOUCH_UART_HEADER                   (0x55)
  #define TOUCH_UART_FOOTER                   (0x0A)

/* Command ID */
  #define TOUCH_UART_COMMAND_START            (0x11)
  #define TOUCH_UART_COMMAND_STOP             (0x12)
  #define TOUCH_UART_COMMAND_READ             (0x13)
  #define TOUCH_UART_COMMAND_WRITE            (0x14)
  #define TOUCH_UART_COMMAND_VERSION          (0x15)

/* Response ID */
  #define TOUCH_UART_RESPONSE_BIT             (0x80)
  #define TOUCH_UART_RESPONSE_ERROR_BIT       (0xA0)
  #define TOUCH_UART_RESPONSE_MONITOR         (0xA1)

/* Write Request Type */
  #define TOUCH_UART_WRITE_DRIFT              (0x01)
  #define TOUCH_UART_WRITE_CANCEL             (0x02)
  #define TOUCH_UART_WRITE_POSITIVE           (0x03)
  #define TOUCH_UART_WRITE_NEGATIVE           (0x04)
  #define TOUCH_UART_WRITE_MOVING_AVG         (0x05)
  #define TOUCH_UART_WRITE_THRESHOLD          (0x06)
  #define TOUCH_UART_WRITE_HYSTERESIS         (0x07)
  #define TOUCH_UART_WRITE_THRESH_SLDR        (0x08)
  #define TOUCH_UART_WRITE_THRESH_WHEL        (0x09)
  #define TOUCH_UART_WRITE_CTSUSO             (0x0A)
  #define TOUCH_UART_WRITE_CTSUSNUM           (0x0B)
  #define TOUCH_UART_WRITE_CTSUSDPA           (0x0C)

/* Method Number Maximum */
  #define TOUCH_UART_INSTANCE_MAX             (32)

/* UART Receive Buffer Size */
  #define TOUCH_UART_RECIEVE_BUF_SIZE         (13)

/* Register mask and bitshift */
  #if (BSP_FEATURE_CTSU_VERSION == 2)
   #define TOUCH_UART_CTSUSO_MASK             (0x3FF)
   #define TOUCH_UART_CTSUSNUM_MASK           (0xFF)
   #define TOUCH_UART_CTSUSDPA_MASK           (0xFF)
   #define TOUCH_UART_CTSUSNUM_SHIFT          (10)
   #define TOUCH_UART_CTSUSDPA_SHIFT          (24)
  #endif
  #if (BSP_FEATURE_CTSU_VERSION == 1)
   #define TOUCH_UART_CTSUSO_MASK             (0x3FF)
   #define TOUCH_UART_CTSUSNUM_MASK           (0x3F)
   #define TOUCH_UART_CTSUSDPA_MASK           (0x1F)
   #define TOUCH_UART_CTSUSNUM_SHIFT          (10)
   #define TOUCH_UART_CTSUSDPA_SHIFT          (8)
  #endif
 #endif
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (TOUCH_CFG_NUM_BUTTONS != 0)
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
static void touch_button_self_decode(touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id);

 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
static void touch_button_mutual_decode(touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id);

 #endif
static void touch_button_on(touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id);
static void touch_button_off(touch_button_info_t * p_binfo, uint8_t button_id);
static void touch_button_drift(touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id);

#endif
#if (TOUCH_CFG_NUM_SLIDERS != 0)
static void touch_slider_decode(touch_slider_info_t * p_sinfo,
                                uint16_t            * slider_data,
                                uint8_t               num_elements,
                                uint8_t               slider_id);

#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
static void touch_wheel_decode(touch_wheel_info_t * p_winfo,
                               uint16_t           * wheel_data,
                               uint8_t              num_elements,
                               uint8_t              wheel_id);

#endif

#if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)
void touch_uart_callback(uart_callback_args_t * p_args);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure used by error logger macro. */
static const fsp_version_t g_touch_version =
{
    .api_version_minor  = TOUCH_API_VERSION_MINOR,
    .api_version_major  = TOUCH_API_VERSION_MAJOR,
    .code_version_major = TOUCH_CODE_VERSION_MAJOR,
    .code_version_minor = TOUCH_CODE_VERSION_MINOR
};
#if (TOUCH_CFG_NUM_BUTTONS != 0)
static uint8_t  g_touch_button_index = 0;
static uint16_t g_touch_button_threshold[TOUCH_CFG_NUM_BUTTONS];
static uint16_t g_touch_button_hysteresis[TOUCH_CFG_NUM_BUTTONS];
static uint16_t g_touch_button_reference[TOUCH_CFG_NUM_BUTTONS];
static uint16_t g_touch_button_on_count[TOUCH_CFG_NUM_BUTTONS];
static uint16_t g_touch_button_off_count[TOUCH_CFG_NUM_BUTTONS];
static uint32_t g_touch_button_drift_buf[TOUCH_CFG_NUM_BUTTONS];
static uint16_t g_touch_button_drift_count[TOUCH_CFG_NUM_BUTTONS];
#endif
#if (TOUCH_CFG_NUM_SLIDERS != 0)
static uint8_t  g_touch_slider_index = 0;
static uint16_t g_touch_slider_position[TOUCH_CFG_NUM_SLIDERS];
static uint16_t g_touch_slider_threshold[TOUCH_CFG_NUM_SLIDERS];
#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
static uint8_t  g_touch_wheel_index = 0;
static uint16_t g_touch_wheel_position[TOUCH_CFG_NUM_WHEELS];
static uint16_t g_touch_wheel_threshold[TOUCH_CFG_NUM_WHEELS];
#endif
#if TOUCH_CFG_MONITOR_ENABLE
static volatile uint8_t g_touch_monitor_buf[TOUCH_MONITOR_BUFFER_SIZE];
static uint8_t          g_touch_monitor_id;
static uint16_t         g_touch_monitor_size[TOUCH_MONITOR_BLOCK_MAX];

 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)
static touch_instance_ctrl_t * gp_touch_ctrl_list[TOUCH_UART_INSTANCE_MAX];
static uart_instance_t       * gp_touch_uart_instance;
static uint8_t                 g_touch_uart_rx_buf[TOUCH_UART_RECIEVE_BUF_SIZE];

/* data transmit flag */
volatile uint8_t g_touch_uart_transmit_flag;

/* Detect method number */
uint32_t g_touch_uart_open_bitmap;

/* Monitoring method number */
uint8_t g_touch_uart_monitor_num;
 #endif
#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const touch_api_t g_touch_on_ctsu =
{
    .open       = RM_TOUCH_Open,
    .scanStart  = RM_TOUCH_ScanStart,
    .dataGet    = RM_TOUCH_DataGet,
    .close      = RM_TOUCH_Close,
    .versionGet = RM_TOUCH_VersionGet,
};

/*******************************************************************************************************************//**
 * @addtogroup TOUCH
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the TOUCH Middle module. Implements @ref touch_api_t::open.
 *
 * Example:
 * @snippet rm_touch_example.c RM_TOUCH_Open
 *
 * @retval FSP_SUCCESS              TOUCH successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Configuration parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_TOUCH_Open (touch_ctrl_t * const p_ctrl, touch_cfg_t const * const p_cfg)
{
    touch_instance_ctrl_t * p_instance_ctrl = (touch_instance_ctrl_t *) p_ctrl;
#if ((TOUCH_CFG_NUM_BUTTONS != 0) || (TOUCH_CFG_NUM_SLIDERS != 0) || (TOUCH_CFG_NUM_WHEELS != 0))
    uint8_t id;
#endif
    fsp_err_t err = FSP_SUCCESS;
#if TOUCH_CFG_MONITOR_ENABLE
    uint8_t num;
#endif

#if (TOUCH_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
#endif
    TOUCH_ERROR_RETURN(TOUCH_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    p_instance_ctrl->p_touch_cfg = p_cfg;

    /** Parameter Setting */
#if (TOUCH_CFG_NUM_BUTTONS != 0)
    if (TOUCH_CFG_NUM_BUTTONS >= g_touch_button_index)
    {
        p_instance_ctrl->binfo.p_reference   = &g_touch_button_reference[g_touch_button_index];
        p_instance_ctrl->binfo.p_on_count    = &g_touch_button_on_count[g_touch_button_index];
        p_instance_ctrl->binfo.p_off_count   = &g_touch_button_off_count[g_touch_button_index];
        p_instance_ctrl->binfo.p_drift_buf   = &g_touch_button_drift_buf[g_touch_button_index];
        p_instance_ctrl->binfo.p_drift_count = &g_touch_button_drift_count[g_touch_button_index];
        p_instance_ctrl->binfo.p_threshold   = &g_touch_button_threshold[g_touch_button_index];
        p_instance_ctrl->binfo.p_hysteresis  = &g_touch_button_hysteresis[g_touch_button_index];
        g_touch_button_index                 =
            (uint8_t) (g_touch_button_index + p_instance_ctrl->p_touch_cfg->num_buttons);
    }

    if (0 == p_cfg->on_freq)
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    if (0 == p_cfg->off_freq)
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    if (0 != p_cfg->cancel_freq)
    {
        if (p_cfg->cancel_freq < p_cfg->on_freq)
        {
            err = FSP_ERR_INVALID_ARGUMENT;
        }
    }

    p_instance_ctrl->binfo.on_freq     = p_cfg->on_freq;
    p_instance_ctrl->binfo.off_freq    = p_cfg->off_freq;
    p_instance_ctrl->binfo.drift_freq  = p_cfg->drift_freq;
    p_instance_ctrl->binfo.cancel_freq = p_cfg->cancel_freq;

    for (id = 0; id < p_cfg->num_buttons; id++)
    {
        if (p_cfg->p_buttons[id].threshold < p_cfg->p_buttons[id].hysteresis)
        {
            err = FSP_ERR_INVALID_ARGUMENT;
        }

        *(p_instance_ctrl->binfo.p_reference + id)   = 0;
        *(p_instance_ctrl->binfo.p_on_count + id)    = 0;
        *(p_instance_ctrl->binfo.p_off_count + id)   = 0;
        *(p_instance_ctrl->binfo.p_drift_buf + id)   = 0;
        *(p_instance_ctrl->binfo.p_drift_count + id) = 0;
        *(p_instance_ctrl->binfo.p_threshold + id)   = p_cfg->p_buttons[id].threshold;
        *(p_instance_ctrl->binfo.p_hysteresis + id)  = p_cfg->p_buttons[id].hysteresis;
    }
#endif
#if (TOUCH_CFG_NUM_SLIDERS != 0)
    if (TOUCH_CFG_NUM_SLIDERS >= g_touch_slider_index)
    {
        p_instance_ctrl->sinfo.p_position  = &g_touch_slider_position[g_touch_slider_index];
        p_instance_ctrl->sinfo.p_threshold = &g_touch_slider_threshold[g_touch_slider_index];
        g_touch_slider_index               = (uint8_t) (g_touch_slider_index + p_cfg->num_sliders);
    }

    for (id = 0; id < p_cfg->num_sliders; id++)
    {
        if ((TOUCH_SLIDER_ELEMENTS_MIN > p_cfg->p_sliders[id].num_elements) ||
            (TOUCH_SLIDER_ELEMENTS_MAX < p_cfg->p_sliders[id].num_elements))
        {
            err = FSP_ERR_INVALID_ARGUMENT;
        }

        *(p_instance_ctrl->sinfo.p_threshold + id) = p_cfg->p_sliders[id].threshold;
    }
#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
    if (TOUCH_CFG_NUM_WHEELS >= g_touch_wheel_index)
    {
        p_instance_ctrl->winfo.p_position  = &g_touch_wheel_position[g_touch_wheel_index];
        p_instance_ctrl->winfo.p_threshold = &g_touch_wheel_threshold[g_touch_wheel_index];
        g_touch_wheel_index                = (uint8_t) (g_touch_wheel_index + p_cfg->num_wheels);
    }

    for (id = 0; id < p_cfg->num_wheels; id++)
    {
        if ((TOUCH_WHEEL_ELEMENTS_LARGE != p_cfg->p_wheels[id].num_elements) &&
            (TOUCH_WHEEL_ELEMENTS_SMALL != p_cfg->p_wheels[id].num_elements))
        {
            err = FSP_ERR_INVALID_ARGUMENT;
        }

        *(p_instance_ctrl->winfo.p_threshold + id) = p_cfg->p_wheels[id].threshold;
    }
#endif

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->p_ctsu_instance = p_cfg->p_ctsu_instance;
        err = p_instance_ctrl->p_ctsu_instance->p_api->open(p_cfg->p_ctsu_instance->p_ctrl,
                                                            p_cfg->p_ctsu_instance->p_cfg);
    }

#if TOUCH_CFG_MONITOR_ENABLE
    num = p_cfg->number;
    g_touch_monitor_size[num] = (uint16_t) (TOUCH_MONITOR_SELF_ELEMENT_SIZE * p_cfg->p_ctsu_instance->p_cfg->num_rx);

 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_instance->p_cfg->md))
    {
        g_touch_monitor_size[num] =
            (uint16_t) (TOUCH_MONITOR_MUTUAL_ELEMENT_SIZE *
                        p_cfg->p_ctsu_instance->p_cfg->num_rx * p_cfg->p_ctsu_instance->p_cfg->num_tx);
    }
 #endif
 #if (TOUCH_CFG_NUM_BUTTONS != 0)
    if (0 < p_cfg->num_buttons)
    {
        g_touch_monitor_size[num] =
            (uint16_t) (g_touch_monitor_size[num] + TOUCH_MONITOR_BHEAD_SIZE +
                        (TOUCH_MONITOR_BUTTON_SIZE * p_cfg->num_buttons));
    }
 #endif
 #if (TOUCH_CFG_NUM_SLIDERS != 0)
    if (0 < p_cfg->num_sliders)
    {
        g_touch_monitor_size[num] =
            (uint16_t) (g_touch_monitor_size[num] + TOUCH_MONITOR_SHEAD_SIZE +
                        (TOUCH_MONITOR_SLIDER_SIZE * p_cfg->num_sliders));
    }
 #endif
 #if (TOUCH_CFG_NUM_WHEELS != 0)
    if (0 < p_cfg->num_wheels)
    {
        g_touch_monitor_size[num] =
            (uint16_t) (g_touch_monitor_size[num] + TOUCH_MONITOR_WHEAD_SIZE +
                        (TOUCH_MONITOR_WHEEL_SIZE * p_cfg->num_wheels));
    }
 #endif
    g_touch_monitor_size[num] =
        (uint16_t) (g_touch_monitor_size[num] + TOUCH_MONITOR_HEADER_SIZE + TOUCH_MONITOR_FOOTER_SIZE);

 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)
    if (0 == g_touch_uart_open_bitmap)
    {
        p_instance_ctrl->p_touch_cfg->p_uart_instance->p_api->open(p_cfg->p_uart_instance->p_ctrl,
                                                                   p_cfg->p_uart_instance->p_cfg);
        p_instance_ctrl->p_touch_cfg->p_uart_instance->p_api->read(p_cfg->p_uart_instance->p_ctrl,
                                                                   &g_touch_uart_rx_buf[0],
                                                                   TOUCH_UART_RECIEVE_BUF_SIZE);
        gp_touch_uart_instance   = (uart_instance_t *) p_cfg->p_uart_instance;
        g_touch_uart_monitor_num = TOUCH_UART_MONITOR_NONE;
    }

    g_touch_uart_open_bitmap |= (uint32_t) (1 << num);
    gp_touch_ctrl_list[num]   = p_instance_ctrl;
 #endif
#endif

    /* Mark driver as open */
    p_instance_ctrl->open = TOUCH_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function should be called each time a periodic timer expires.
 * If initial offset tuning is enabled, The first several calls are used to tuning for the sensors.
 * Before starting the next scan, first get the data with RM_TOUCH_DataGet().
 * If a different control block scan should be run, check the scan is complete before executing.
 * Implements @ref touch_api_t::scanStart.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_CTSU_SCANNING    Scanning this instance or other.
 * @retval FSP_ERR_CTSU_NOT_GET_DATA    The previous data has not been retrieved by DataGet.
 **********************************************************************************************************************/
fsp_err_t RM_TOUCH_ScanStart (touch_ctrl_t * const p_ctrl)
{
    fsp_err_t               err             = FSP_SUCCESS;
    touch_instance_ctrl_t * p_instance_ctrl = (touch_instance_ctrl_t *) p_ctrl;

#if (TOUCH_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    TOUCH_ERROR_RETURN(TOUCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    err = p_instance_ctrl->p_ctsu_instance->p_api->scanStart(p_instance_ctrl->p_ctsu_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_ERR_CTSU_SCANNING != err, FSP_ERR_CTSU_SCANNING);
    FSP_ERROR_RETURN(FSP_ERR_CTSU_NOT_GET_DATA != err, FSP_ERR_CTSU_NOT_GET_DATA);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets the 64-bit mask indicating which buttons are pressed.
 * Also, this function gets the current position of where slider or wheel is being pressed.
 * If initial offset tuning is enabled, The first several calls are used to tuning for the sensors.
 * Implements @ref touch_api_t::dataGet.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_CTSU_SCANNING    Scanning this instance.
 * @retval FSP_ERR_CTSU_INCOMPLETE_TUNING      Incomplete initial offset tuning.
 **********************************************************************************************************************/
fsp_err_t RM_TOUCH_DataGet (touch_ctrl_t * const p_ctrl,
                            uint64_t           * p_button_status,
                            uint16_t           * p_slider_position,
                            uint16_t           * p_wheel_position)
{
    fsp_err_t               err             = FSP_SUCCESS;
    touch_instance_ctrl_t * p_instance_ctrl = (touch_instance_ctrl_t *) p_ctrl;
    uint16_t                data[CTSU_CFG_NUM_SELF_ELEMENTS + (CTSU_CFG_NUM_MUTUAL_ELEMENTS * 2)];
#if ((TOUCH_CFG_NUM_BUTTONS != 0) || (TOUCH_CFG_NUM_SLIDERS != 0) || (TOUCH_CFG_NUM_WHEELS != 0))
    uint16_t sensor_val = 0;
#endif
#if (TOUCH_CFG_NUM_BUTTONS != 0)
    uint8_t button_id;
#endif
#if (TOUCH_CFG_NUM_SLIDERS != 0)
    const touch_slider_cfg_t * p_slider;
    uint8_t  slider_id;
    uint16_t slider_data[TOUCH_SLIDER_ELEMENTS_MAX];
#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
    const touch_wheel_cfg_t * p_wheel;
    uint8_t  wheel_id;
    uint16_t wheel_data[TOUCH_WHEEL_ELEMENTS_LARGE];
#endif
#if ((TOUCH_CFG_NUM_SLIDERS != 0) || (TOUCH_CFG_NUM_WHEELS != 0))
    uint8_t element_id;
#endif
#if TOUCH_CFG_MONITOR_ENABLE
    uint16_t i;
    uint16_t index       = 0;
    uint8_t  element_num = 0;
#endif

#if (TOUCH_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
 #if (TOUCH_CFG_NUM_BUTTONS != 0)
    FSP_ASSERT(p_button_status);
 #endif
 #if (TOUCH_CFG_NUM_SLIDERS != 0)
    FSP_ASSERT(p_slider_position);
 #endif
 #if (TOUCH_CFG_NUM_WHEELS != 0)
    FSP_ASSERT(p_wheel_position);
 #endif
    TOUCH_ERROR_RETURN(TOUCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* get results from previous scan */
    err = p_instance_ctrl->p_ctsu_instance->p_api->dataGet(p_instance_ctrl->p_ctsu_instance->p_ctrl, data);
    FSP_ERROR_RETURN(FSP_ERR_CTSU_SCANNING != err, FSP_ERR_CTSU_SCANNING);
    FSP_ERROR_RETURN(FSP_ERR_CTSU_INCOMPLETE_TUNING != err, FSP_ERR_CTSU_INCOMPLETE_TUNING);

#if (TOUCH_CFG_NUM_BUTTONS != 0)
    for (button_id = 0; button_id < p_instance_ctrl->p_touch_cfg->num_buttons; button_id++)
    {
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_instance->p_cfg->md)
        {
            sensor_val = *(data + p_instance_ctrl->p_touch_cfg->p_buttons[button_id].elem_index);
        }
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_instance->p_cfg->md))
        {
            /* The value of Primary count minus secondary count */
            sensor_val = (uint16_t) (*(data + (p_instance_ctrl->p_touch_cfg->p_buttons[button_id].elem_index * 2) + 1) -
                                     *(data + (p_instance_ctrl->p_touch_cfg->p_buttons[button_id].elem_index * 2)));
        }
 #endif
        if (0 == *(p_instance_ctrl->binfo.p_reference + button_id))
        {
            *(p_instance_ctrl->binfo.p_reference + button_id) = sensor_val;
        }
        else
        {
            /* Create button status */
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
            if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_instance->p_cfg->md)
            {
                touch_button_self_decode(&p_instance_ctrl->binfo, sensor_val, button_id);
            }
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
            if (CTSU_MODE_MUTUAL_FULL_SCAN ==
                (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_instance->p_cfg->md))
            {
                touch_button_mutual_decode(&p_instance_ctrl->binfo, sensor_val, button_id);
            }
 #endif
            touch_button_drift(&p_instance_ctrl->binfo, sensor_val, button_id);
        }
    }

    /** status is 64-bitmap */
    *p_button_status = p_instance_ctrl->binfo.status;
#else
    FSP_PARAMETER_NOT_USED(p_button_status);
#endif

#if (TOUCH_CFG_NUM_SLIDERS != 0)

    /* Create slider position */
    for (slider_id = 0; slider_id < p_instance_ctrl->p_touch_cfg->num_sliders; slider_id++)
    {
        p_slider = (p_instance_ctrl->p_touch_cfg->p_sliders + slider_id);
        for (element_id = 0; element_id < p_slider->num_elements; element_id++)
        {
            sensor_val              = *(data + p_slider->p_elem_index[element_id]);
            slider_data[element_id] = sensor_val;
        }

        touch_slider_decode(&p_instance_ctrl->sinfo, slider_data, p_slider->num_elements, slider_id);

        *p_slider_position = *(p_instance_ctrl->sinfo.p_position + slider_id);
        p_slider_position++;
    }

#else
    FSP_PARAMETER_NOT_USED(p_slider_position);
#endif

#if (TOUCH_CFG_NUM_WHEELS != 0)
    for (wheel_id = 0; wheel_id < p_instance_ctrl->p_touch_cfg->num_wheels; wheel_id++)
    {
        p_wheel = (p_instance_ctrl->p_touch_cfg->p_wheels + wheel_id);
        for (element_id = 0; element_id < p_wheel->num_elements; element_id++)
        {
            sensor_val             = *(data + p_wheel->p_elem_index[element_id]);
            wheel_data[element_id] = sensor_val;
        }

        touch_wheel_decode(&p_instance_ctrl->winfo, wheel_data, p_wheel->num_elements, wheel_id);

        *p_wheel_position = *(p_instance_ctrl->winfo.p_position + wheel_id);
        p_wheel_position++;
    }

#else
    FSP_PARAMETER_NOT_USED(p_wheel_position);
#endif

#if TOUCH_CFG_MONITOR_ENABLE
 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)
    if (!g_touch_uart_transmit_flag && (p_instance_ctrl->p_touch_cfg->number == g_touch_uart_monitor_num))
    {
        /* Monitor Data Notification */
        g_touch_monitor_buf[index++] = TOUCH_UART_HEADER;
        g_touch_monitor_buf[index++] = TOUCH_UART_RESPONSE_MONITOR;
        g_touch_monitor_buf[index++] = 0; /* Temporarily input the size */
        g_touch_monitor_buf[index++] = 0; /* Temporarily input the size */
    }

    if (!g_touch_uart_transmit_flag &&
        ((p_instance_ctrl->p_touch_cfg->number == g_touch_uart_monitor_num) ||
         (TOUCH_UART_MONITOR_NONE == g_touch_uart_monitor_num)))
    {
        if (TOUCH_UART_MONITOR_NONE == g_touch_uart_monitor_num)
        {
 #endif
    for (i = 0; i < p_instance_ctrl->p_touch_cfg->number; i++)
    {
        index = (uint16_t) (index + g_touch_monitor_size[i]);
    }

 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)
}
 #endif

    g_touch_monitor_buf[index++] = g_touch_monitor_id;
    g_touch_monitor_buf[index++] = p_instance_ctrl->p_touch_cfg->number;
    if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_instance->p_cfg->md)
    {
        g_touch_monitor_buf[index++] = 0x00;
        element_num = p_instance_ctrl->p_touch_cfg->p_ctsu_instance->p_cfg->num_rx;
        g_touch_monitor_buf[index++] = element_num;
        for (i = 0; i < element_num; i++)
        {
            g_touch_monitor_buf[index++] = (uint8_t) (data[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (data[i] >> 8);
        }
    }
    else
    {
        g_touch_monitor_buf[index++] = 0x01;
        element_num = (uint8_t) (p_instance_ctrl->p_touch_cfg->p_ctsu_instance->p_cfg->num_rx *
                                 p_instance_ctrl->p_touch_cfg->p_ctsu_instance->p_cfg->num_tx);
        g_touch_monitor_buf[index++] = element_num;
        for (i = 0; i < (element_num * 2); i++)
        {
            g_touch_monitor_buf[index++] = (uint8_t) (data[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (data[i] >> 8);
        }
    }

 #if (TOUCH_CFG_NUM_BUTTONS != 0)
    if (0 < p_instance_ctrl->p_touch_cfg->num_buttons)
    {
        g_touch_monitor_buf[index++] = 0x00;
        g_touch_monitor_buf[index++] = p_instance_ctrl->p_touch_cfg->num_buttons;
        for (i = 0; i < p_instance_ctrl->p_touch_cfg->num_buttons; i++)
        {
            g_touch_monitor_buf[index++] = (uint8_t) ((p_instance_ctrl->binfo.status >> i) & 0x01);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->binfo.p_reference[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->binfo.p_reference[i] >> 8);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->binfo.p_threshold[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->binfo.p_threshold[i] >> 8);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->binfo.p_hysteresis[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->binfo.p_hysteresis[i] >> 8);
        }
    }
 #endif
 #if (TOUCH_CFG_NUM_SLIDERS != 0)
    if (0 < p_instance_ctrl->p_touch_cfg->num_sliders)
    {
        g_touch_monitor_buf[index++] = 0x01;
        g_touch_monitor_buf[index++] = p_instance_ctrl->p_touch_cfg->num_sliders;
        for (i = 0; i < p_instance_ctrl->p_touch_cfg->num_sliders; i++)
        {
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->sinfo.p_position[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->sinfo.p_position[i] >> 8);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->sinfo.p_threshold[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->sinfo.p_threshold[i] >> 8);
        }
    }
 #endif
 #if (TOUCH_CFG_NUM_WHEELS != 0)
    if (0 < p_instance_ctrl->p_touch_cfg->num_wheels)
    {
        g_touch_monitor_buf[index++] = 0x02;
        g_touch_monitor_buf[index++] = p_instance_ctrl->p_touch_cfg->num_wheels;
        for (i = 0; i < p_instance_ctrl->p_touch_cfg->num_wheels; i++)
        {
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->winfo.p_position[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->winfo.p_position[i] >> 8);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->winfo.p_threshold[i]);
            g_touch_monitor_buf[index++] = (uint8_t) (p_instance_ctrl->winfo.p_threshold[i] >> 8);
        }
    }
 #endif
    g_touch_monitor_buf[index++] = g_touch_monitor_id++;

 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)
}

if (!g_touch_uart_transmit_flag && (p_instance_ctrl->p_touch_cfg->number == g_touch_uart_monitor_num))
{
    g_touch_monitor_buf[index++] = TOUCH_UART_FOOTER;
    g_touch_monitor_buf[2]       = (uint8_t) (index);
    g_touch_monitor_buf[3]       = (uint8_t) (index >> 8);
    g_touch_uart_transmit_flag   = 1;
    gp_touch_uart_instance->p_api->write(gp_touch_uart_instance->p_ctrl,
                                         (uint8_t const * const) &g_touch_monitor_buf,
                                         index);
}
 #endif
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified TOUCH control block. Implements @ref touch_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_TOUCH_Close (touch_ctrl_t * const p_ctrl)
{
    touch_instance_ctrl_t * p_instance_ctrl = (touch_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

    FSP_ASSERT(p_instance_ctrl);
    TOUCH_ERROR_RETURN(TOUCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

#if (TOUCH_CFG_NUM_BUTTONS != 0)
    g_touch_button_index = (uint8_t) (g_touch_button_index - p_instance_ctrl->p_touch_cfg->num_buttons);
#endif
#if (TOUCH_CFG_NUM_SLIDERS != 0)
    g_touch_slider_index = (uint8_t) (g_touch_slider_index - p_instance_ctrl->p_touch_cfg->num_sliders);
#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
    g_touch_wheel_index = (uint8_t) (g_touch_wheel_index - p_instance_ctrl->p_touch_cfg->num_wheels);
#endif

    err = p_instance_ctrl->p_ctsu_instance->p_api->close(p_instance_ctrl->p_ctsu_instance->p_ctrl);
    p_instance_ctrl->open = false;

#if TOUCH_CFG_MONITOR_ENABLE
 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)
    g_touch_uart_open_bitmap &= (uint32_t) ~(1 << p_instance_ctrl->p_touch_cfg->number);
    gp_touch_ctrl_list[p_instance_ctrl->p_touch_cfg->number] = p_instance_ctrl;
    if (0 == g_touch_uart_open_bitmap)
    {
        p_instance_ctrl->p_touch_cfg->p_uart_instance->p_api->open(gp_touch_uart_instance->p_ctrl,
                                                                   gp_touch_uart_instance->p_cfg);
        p_instance_ctrl->p_touch_cfg->p_uart_instance->p_api->read(gp_touch_uart_instance->p_ctrl,
                                                                   &g_touch_uart_rx_buf[0],
                                                                   TOUCH_UART_RECIEVE_BUF_SIZE);
        gp_touch_uart_instance   = NULL;
        g_touch_uart_monitor_num = TOUCH_UART_MONITOR_NONE;
    }
 #endif
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Return TOUCH Middle module version. Implements @ref touch_api_t::versionGet.
 *
 * @retval      FSP_SUCCESS             Version information successfully read.
 * @retval      FSP_ERR_ASSERTION       Null pointer passed as a parameter
 **********************************************************************************************************************/
fsp_err_t RM_TOUCH_VersionGet (fsp_version_t * const p_version)
{
#if TOUCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_version);
#endif

    p_version->version_id = g_touch_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup TOUCH)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal touch private function.
 **********************************************************************************************************************/

#if (TOUCH_CFG_NUM_BUTTONS != 0)
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)

/***********************************************************************************************************************
 * Function Name: touch_button_self_decode
 * Description  : Self Touch Button decoding
 * Arguments    : touch_button_info_t  p_binfo : Pointer to Button Information structure
 *              : uint16_t value               : Sensor value from CTSU
 *              : uint8_t  button_id           : Button ID
 * Return Value : None
 ***********************************************************************************************************************/
void touch_button_self_decode (touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id)
{
    uint32_t threshold;
    uint16_t threshold_sub_hys;

    threshold = (uint32_t) (*(p_binfo->p_reference + button_id) + *(p_binfo->p_threshold + button_id));
    if (TOUCH_COUNT_MAX < threshold)
    {
        return;
    }

    threshold_sub_hys = (uint16_t) (threshold - (*(p_binfo->p_hysteresis + button_id)));

    /* threshold_sub_hys < scan value = Touch */
    if (threshold < value)
    {
        touch_button_on(p_binfo, value, button_id);
    }
    else if (threshold_sub_hys > value)
    {
        touch_button_off(p_binfo, button_id);
    }
    else
    {
        /* Do nothing during hysteresis */
    }
}

 #endif

 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)

/***********************************************************************************************************************
 * Function Name: touch_button_mutual_decode
 * Description  : Mutual Touch Button decoding
 * Arguments    : touch_button_info_t  p_binfo : Pointer to Button Information structure
 *              : uint16_t value               : Sensor value from CTSU
 *              : uint8_t  button_id           : Button ID
 * Return Value : None
 ***********************************************************************************************************************/
void touch_button_mutual_decode (touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id)
{
    uint16_t threshold;
    uint32_t threshold_add_hys;

    if (*(p_binfo->p_reference + button_id) > *(p_binfo->p_threshold + button_id))
    {
        threshold = (uint16_t) (*(p_binfo->p_reference + button_id) - *(p_binfo->p_threshold + button_id));
    }
    else
    {
        return;
    }

    /* get current threshold_add_hys */
    threshold_add_hys = (uint32_t) (threshold + (*(p_binfo->p_hysteresis + button_id)));
    if (TOUCH_COUNT_MAX < threshold_add_hys) /* error process (touch_cnt is 16bit) */
    {
        return;
    }

    /* threshold_add_hys > scan value = Touch */
    if (threshold > value)
    {
        touch_button_on(p_binfo, value, button_id);
    }
    else if (threshold_add_hys < value)
    {
        touch_button_off(p_binfo, button_id);
    }
    else
    {
        /* Do nothing during hysteresis */
    }
}                                      /* End of function touch_button_decode() */

 #endif

/***********************************************************************************************************************
 * Function Name: touch_button_on
 * Description  : Touch Button ON judge process
 * Arguments    : touch_button_info_t  p_binfo : Pointer to Button Information structure
 *              : uint16_t value               : Sensor value from CTSU
 *              : uint8_t  button_id           : Button ID
 * Return Value : None
 ***********************************************************************************************************************/
void touch_button_on (touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id)
{
    *(p_binfo->p_off_count + button_id) = 0; /* non_touch count reset */

    /* ===== touch ON result ===== */
    if (p_binfo->on_freq <= (*(p_binfo->p_on_count + button_id)))
    {
        p_binfo->status |= (uint64_t) (1 << button_id);
    }
    else
    {
        (*(p_binfo->p_on_count + button_id))++;
    }

    /* ===== The reset judgment processing at the time of continuation on ===== */
    if (p_binfo->cancel_freq > p_binfo->on_freq)
    {
        /* If reaching max_on_threshold, it makes result off and it revises a drift. */
        if (p_binfo->cancel_freq <= (*(p_binfo->p_on_count + button_id)))
        {
            p_binfo->status &= ~((uint64_t) (1 << button_id));
            *(p_binfo->p_on_count + button_id)  = 0;
            *(p_binfo->p_reference + button_id) = value;
        }
        else
        {
            (*(p_binfo->p_on_count + button_id))++;
        }
    }
}                                      /* End of function touch_button_on() */

/***********************************************************************************************************************
 * Function Name: touch_button_off
 * Description  : Touch Button OFF judge process
 * Arguments    : touch_button_info_t  p_binfo : Pointer to Button Information structure
 *              : uint16_t value               : Sensor value from CTSU
 *              : uint8_t  button_id           : Button ID
 * Return Value : None
 ***********************************************************************************************************************/
void touch_button_off (touch_button_info_t * p_binfo, uint8_t button_id)
{
    *(p_binfo->p_on_count + button_id) = 0; /* touch count reset */

    /* ===== touch OFF result ===== */
    if (p_binfo->off_freq <= (*(p_binfo->p_off_count + button_id)))
    {
        p_binfo->status &= ~((uint64_t) (1 << button_id));
    }
    else
    {
        (*(p_binfo->p_off_count + button_id))++;
    }
}                                      /* End of function touch_button_off() */

/***********************************************************************************************************************
 * Function Name: touch_button_drift
 * Description  : Touch Button drift process
 * Arguments    : touch_button_info_t  p_binfo : Pointer to Button Information structure
 *              : uint16_t value               : Sensor value from CTSU
 *              : uint8_t  button_id           : Button ID
 * Return Value : None
 ***********************************************************************************************************************/
void touch_button_drift (touch_button_info_t * p_binfo, uint16_t value, uint8_t button_id)
{
    if (0 != p_binfo->drift_freq)
    {
        /* In case of doing drift correction being and moreover On/Off judgment result 1=OFF */
        if (0 == (p_binfo->status & ((uint64_t) (1 << button_id))))
        {
            /* It is an addition for the drift correction average calculation */
            *(p_binfo->p_drift_buf + button_id) += value;

            /* Drift correction counter's being incremented */
            (*(p_binfo->p_drift_count + button_id))++;

            if (*(p_binfo->p_drift_count + button_id) >= p_binfo->drift_freq)
            {
                /* If reaching the correction number of times */
                *(p_binfo->p_reference +
                  button_id) = (uint16_t) (*(p_binfo->p_drift_buf + button_id) / p_binfo->drift_freq);

                /* To REF of the average */
                *(p_binfo->p_drift_buf + button_id) = 0;

                /* Work clear */
                *(p_binfo->p_drift_count + button_id) = 0;
            }
        }
        else
        {
            /* To REF of the average */
            *(p_binfo->p_drift_buf + button_id) = 0;

            /* Work clear */
            *(p_binfo->p_drift_count + button_id) = 0;
        }
    }
}

#endif

#if (TOUCH_CFG_NUM_SLIDERS != 0)

/***********************************************************************************************************************
 * Function Name: touch_slider_decode
 * Description  : Slider decode function
 * Arguments    : touch_slider_info_t  p_sinfo : Pointer to Slider Information structure
 *              : uint16_t *slider_data        : Pointer to Slider data array
 *              : uint8_t  num_elements        : Number of element on slider
 *              : uint8_t  slider_id           : Slider ID
 * Return Value : None
 ***********************************************************************************************************************/
void touch_slider_decode (touch_slider_info_t * p_sinfo, uint16_t * slider_data, uint8_t num_elements,
                          uint8_t slider_id)
{
    uint8_t loop;
    uint8_t max_data_num;
    uint16_t d1;
    uint16_t d2;
    uint16_t d3;
    uint16_t slider_rpos;
    uint16_t resol_plus;
    uint16_t dsum;

    if (num_elements < 3)
    {
        return;
    }

    /* Search max data in slider */
    max_data_num = 0;
    for (loop = 0; loop < (num_elements - 1); loop++)
    {
        if (slider_data[max_data_num] < slider_data[loop + 1])
        {
            max_data_num = (uint8_t) (loop + 1);
        }
    }

    /* Array making for slider operation-------------*/
    /*     |    Maximum change CH_No -----> Array"0"    */
    /*     |    Maximum change CH_No + 1 -> Array"2"    */
    /*     |    Maximum change CH_No - 1 -> Array"1"    */
    if (0 == max_data_num)
    {
        d1 = (uint16_t) (slider_data[0] - slider_data[2]);
        d2 = (uint16_t) (slider_data[0] - slider_data[1]);
    }
    else if ((num_elements - 1) == max_data_num)
    {
        d1 = (uint16_t) (slider_data[num_elements - 1] - slider_data[num_elements - 2]);
        d2 = (uint16_t) (slider_data[num_elements - 1] - slider_data[num_elements - 3]);
    }
    else
    {
        d1 = (uint16_t) (slider_data[max_data_num] - slider_data[max_data_num - 1]);
        d2 = (uint16_t) (slider_data[max_data_num] - slider_data[max_data_num + 1]);
    }

    dsum = (uint16_t) (d1 + d2);

    /* Constant decision for operation of angle of slider */
    /* Scale results to be 0-TOUCH_SLIDER_RESOLUTION */
    if (dsum > *(p_sinfo->p_threshold + slider_id))
    {
        if (0 == d1)
        {
            d1 = 1;
        }

        /* x : y = d1 : d2 */
        d3 = (uint16_t) (TOUCH_DECIMAL_POINT_PRECISION + ((d2 * TOUCH_DECIMAL_POINT_PRECISION) / d1));

        slider_rpos = (uint16_t) (((TOUCH_DECIMAL_POINT_PRECISION * TOUCH_SLIDER_RESOLUTION) / d3) +
                                  (TOUCH_SLIDER_RESOLUTION * max_data_num));

        resol_plus = (uint16_t) (TOUCH_SLIDER_RESOLUTION * (num_elements - 1));

        if (0 == slider_rpos)
        {
            slider_rpos = 1;
        }
        else if (slider_rpos >= resol_plus)
        {
            slider_rpos = (uint16_t) (((slider_rpos - resol_plus) * 2) + resol_plus);
            if (slider_rpos > (TOUCH_SLIDER_RESOLUTION * num_elements))
            {
                slider_rpos = TOUCH_SLIDER_RESOLUTION;
            }
            else
            {
                slider_rpos = (uint16_t) (slider_rpos / num_elements);
            }
        }
        else if (slider_rpos <= TOUCH_SLIDER_RESOLUTION)
        {
            if (slider_rpos < (TOUCH_SLIDER_RESOLUTION / 2))
            {
                slider_rpos = 1;
            }
            else
            {
                slider_rpos = (uint16_t) (slider_rpos - (TOUCH_SLIDER_RESOLUTION / 2));
                if (0 == slider_rpos)
                {
                    slider_rpos = 1;
                }
                else
                {
                    slider_rpos = (uint16_t) ((slider_rpos * 2) / num_elements);
                }
            }
        }
        else
        {
            slider_rpos = (uint16_t) (slider_rpos / num_elements);
        }
    }
    else
    {
        slider_rpos = TOUCH_OFF_VALUE;
    }

    *(p_sinfo->p_position + slider_id) = slider_rpos;
}                                      /* End of function touch_slider_decode() */

#endif                                 // SLIDER_USE

#if (TOUCH_CFG_NUM_WHEELS != 0)

/***********************************************************************************************************************
 * Function Name: touch_wheel_decode
 * Description  : Wheel Decode function
 * Arguments    : touch_wheel_info_t  p_sinfo : Pointer to Wheel Information structure
 *              : uint16_t *wheel_data        : Pointer to Wheel data array
 *              : uint8_t  num_elements       : Number of element on wheel
 *              : uint8_t  wheel_id           : Wheel ID
 * Return Value : None
 ***********************************************************************************************************************/
void touch_wheel_decode (touch_wheel_info_t * p_winfo, uint16_t * wheel_data, uint8_t num_elements, uint8_t wheel_id)
{
    uint8_t loop;
    uint8_t max_data_num;
    uint16_t d1;
    uint16_t d2;
    uint16_t d3;
    uint16_t wheel_rpos;
    uint16_t dsum;
    uint16_t unit;

    if (num_elements < 3)
    {
        return;
    }

    /* Search max data in slider */
    max_data_num = 0;
    for (loop = 0; loop < (num_elements - 1); loop++)
    {
        if (wheel_data[max_data_num] < wheel_data[loop + 1])
        {
            max_data_num = (uint8_t) (loop + 1);
        }
    }

    /* Array making for wheel operation          */
    /*    Maximum change CH_No -----> Array"0"    */
    /*    Maximum change CH_No + 1 -> Array"2"    */
    /*    Maximum change CH_No - 1 -> Array"1"    */
    if (0 == max_data_num)
    {
        d1 = (uint16_t) (wheel_data[0] - wheel_data[num_elements - 1]);
        d2 = (uint16_t) (wheel_data[0] - wheel_data[1]);
    }
    else if ((num_elements - 1) == max_data_num)
    {
        d1 = (uint16_t) (wheel_data[num_elements - 1] - wheel_data[num_elements - 2]);
        d2 = (uint16_t) (wheel_data[num_elements - 1] - wheel_data[0]);
    }
    else
    {
        d1 = (uint16_t) (wheel_data[max_data_num] - wheel_data[max_data_num - 1]);
        d2 = (uint16_t) (wheel_data[max_data_num] - wheel_data[max_data_num + 1]);
    }

    dsum = (uint16_t) (d1 + d2);

    if (0 == d1)
    {
        d1 = 1;
    }

    /* Constant decision for operation of angle of wheel    */
    if (dsum > *(p_winfo->p_threshold + wheel_id))
    {
        d3 = (uint16_t) (TOUCH_DECIMAL_POINT_PRECISION + ((d2 * TOUCH_DECIMAL_POINT_PRECISION) / d1));

        unit       = (uint16_t) (TOUCH_WHEEL_RESOLUTION / num_elements);
        wheel_rpos = (uint16_t) (((unit * TOUCH_DECIMAL_POINT_PRECISION) / d3) + (unit * max_data_num));

        /* Angle division output */
        /* diff_angle_ch = 0 -> 359 ------ diff_angle_ch output 1 to 360 */
        if (0 == wheel_rpos)
        {
            wheel_rpos = TOUCH_WHEEL_RESOLUTION;
        }
        else if ((TOUCH_WHEEL_RESOLUTION + 1) < wheel_rpos)
        {
            wheel_rpos = 1;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        wheel_rpos = TOUCH_OFF_VALUE;
    }

    *(p_winfo->p_position + wheel_id) = wheel_rpos;
}                                      /* End of function touch_wheel_decode() */

#endif

#if TOUCH_CFG_MONITOR_ENABLE
 #if (TOUCH_CFG_UART_MONITOR_SUPPORT == 1)

/***********************************************************************************************************************
 * Function Name: user_uart_qe_callback
 * Description  : QE UART callback function
 * Arguments    : uart_callback_args_t * p_args : callback parameters
 * Return Value : None
 ***********************************************************************************************************************/
void touch_uart_callback (uart_callback_args_t * p_args)
{
    ctsu_instance_ctrl_t * p_ctsu_ctrl;
    uint16_t write_data;
    uint16_t ctsuso;
    uint8_t ctsusdpa;
    uint8_t ctsusnum;
  #if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t * p_ctsuso;
    uint32_t * p_ctsusdpa;
    uint32_t * p_ctsusnum;
  #endif
  #if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t * p_ctsuso;
    uint16_t * p_ctsusdpa;
    uint16_t * p_ctsusnum;
  #endif
    uint8_t num;
    uint8_t element;
    uint16_t index;

    if (NULL == gp_touch_uart_instance)
    {
        return;
    }

    if (p_args->event == UART_EVENT_TX_DATA_EMPTY)
    {
        g_touch_uart_transmit_flag = 0;
    }
    else if (p_args->event == UART_EVENT_RX_COMPLETE)
    {
        if (1 == g_touch_uart_transmit_flag)
        {
            /* Abort while sending response */
            gp_touch_uart_instance->p_api->communicationAbort(gp_touch_uart_instance->p_ctrl, UART_DIR_TX);
            g_touch_uart_transmit_flag = 0;
        }

        /* Set fixed header */
        g_touch_monitor_buf[0] = TOUCH_UART_HEADER;

        /* Create response command */
        if ((g_touch_uart_rx_buf[0] == TOUCH_UART_HEADER) && (g_touch_uart_rx_buf[12] == TOUCH_UART_FOOTER))
        {
            g_touch_monitor_buf[1] = g_touch_uart_rx_buf[1] | TOUCH_UART_RESPONSE_BIT;
        }
        else
        {
            g_touch_monitor_buf[1] = g_touch_uart_rx_buf[1] | TOUCH_UART_RESPONSE_ERROR_BIT;
            g_touch_uart_rx_buf[1] = g_touch_monitor_buf[1];
        }

        /* Set same ID */
        g_touch_monitor_buf[4] = g_touch_uart_rx_buf[4];

        /* Set index, Fixed data up to index 4. After index 5, it depends on the command. */
        index = 5;

        if (g_touch_uart_rx_buf[1] == TOUCH_UART_COMMAND_START)
        {
            num = g_touch_uart_rx_buf[5];
            if (0 == ((uint32_t) (1 << num) & g_touch_uart_open_bitmap))
            {
                /* Unopened methods generate errors */
                g_touch_monitor_buf[1] = g_touch_uart_rx_buf[1] | TOUCH_UART_RESPONSE_ERROR_BIT;
            }
            else
            {
                g_touch_uart_monitor_num = num;
            }

            g_touch_monitor_buf[index++] = (uint8_t) g_touch_uart_open_bitmap;
            g_touch_monitor_buf[index++] = (uint8_t) (g_touch_uart_open_bitmap >> 8);
            g_touch_monitor_buf[index++] = (uint8_t) (g_touch_uart_open_bitmap >> 16);
            g_touch_monitor_buf[index++] = (uint8_t) (g_touch_uart_open_bitmap >> 24);
        }
        else if (g_touch_uart_rx_buf[1] == TOUCH_UART_COMMAND_STOP)
        {
            g_touch_uart_monitor_num = TOUCH_UART_MONITOR_NONE;
        }
        else if ((g_touch_uart_rx_buf[1] == TOUCH_UART_COMMAND_READ) ||
                 (g_touch_uart_rx_buf[1] == TOUCH_UART_COMMAND_WRITE))
        {
            num     = g_touch_uart_rx_buf[5];
            element = g_touch_uart_rx_buf[7];

            if (0 == ((uint32_t) (1 << num) & g_touch_uart_open_bitmap))
            {
                /* Unopened methods generate errors */
                g_touch_monitor_buf[1] = g_touch_uart_rx_buf[1] | TOUCH_UART_RESPONSE_ERROR_BIT;
            }
            else
            {
                p_ctsu_ctrl = (ctsu_instance_ctrl_t *) gp_touch_ctrl_list[num]->p_ctsu_instance->p_ctrl;
  #if (BSP_FEATURE_CTSU_VERSION == 2)
                p_ctsuso   = &(p_ctsu_ctrl->p_ctsuwr[element].ctsuso);
                p_ctsusnum = &(p_ctsu_ctrl->p_ctsuwr[element].ctsuso);
                p_ctsusdpa = &(p_ctsu_ctrl->p_ctsuwr[element].ctsuso);
  #endif
  #if (BSP_FEATURE_CTSU_VERSION == 1)
                p_ctsuso   = &(p_ctsu_ctrl->p_ctsuwr[element].ctsuso0);
                p_ctsusnum = &(p_ctsu_ctrl->p_ctsuwr[element].ctsuso0);
                p_ctsusdpa = &(p_ctsu_ctrl->p_ctsuwr[element].ctsuso1);
  #endif
                ctsuso   = (uint16_t) (*p_ctsuso & TOUCH_UART_CTSUSO_MASK);
                ctsusnum = (uint8_t) ((*p_ctsusnum >> TOUCH_UART_CTSUSNUM_SHIFT) & TOUCH_UART_CTSUSNUM_MASK);
                ctsusdpa = (uint8_t) ((*p_ctsusdpa >> TOUCH_UART_CTSUSDPA_SHIFT) & TOUCH_UART_CTSUSDPA_MASK);
                if (g_touch_uart_rx_buf[1] == TOUCH_UART_COMMAND_READ)
                {
                    /* Drift Correction */
                    g_touch_monitor_buf[index++] = (uint8_t) (gp_touch_ctrl_list[num]->binfo.drift_freq);
                    g_touch_monitor_buf[index++] = (uint8_t) (gp_touch_ctrl_list[num]->binfo.drift_freq >> 8);

                    /* Long Press Cancel */
                    g_touch_monitor_buf[index++] = (uint8_t) (gp_touch_ctrl_list[num]->binfo.cancel_freq);
                    g_touch_monitor_buf[index++] = (uint8_t) (gp_touch_ctrl_list[num]->binfo.cancel_freq >> 8);

                    /* Positive Noise Filter */
                    g_touch_monitor_buf[index++] = gp_touch_ctrl_list[num]->binfo.on_freq;
                    g_touch_monitor_buf[index++] = 0x00;

                    /* Negative Noise Filter */
                    g_touch_monitor_buf[index++] = gp_touch_ctrl_list[num]->binfo.off_freq;
                    g_touch_monitor_buf[index++] = 0x00;

                    /* Depth of Moving Average Filter */
                    g_touch_monitor_buf[index++] = (uint8_t) (p_ctsu_ctrl->num_moving_average);
                    g_touch_monitor_buf[index++] = (uint8_t) (p_ctsu_ctrl->num_moving_average >> 8);

                    /* CTSUSO (element) */
                    g_touch_monitor_buf[index++] = (uint8_t) (ctsuso);
                    g_touch_monitor_buf[index++] = (uint8_t) (ctsuso >> 8);

                    /* CTSUSNUM (element) */
                    g_touch_monitor_buf[index++] = ctsusnum;

                    /* CTSUSDPA (element) */
                    g_touch_monitor_buf[index++] = ctsusdpa;
                }
                else
                {
                    /* Write Action */
                    write_data = (uint16_t) ((g_touch_uart_rx_buf[9] << 8) | g_touch_uart_rx_buf[8]);
                    switch (g_touch_uart_rx_buf[6]) /* data type */
                    {
                        case TOUCH_UART_WRITE_DRIFT:
                        {
                            gp_touch_ctrl_list[num]->binfo.drift_freq = write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_CANCEL:
                        {
                            gp_touch_ctrl_list[num]->binfo.cancel_freq = write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_POSITIVE:
                        {
                            gp_touch_ctrl_list[num]->binfo.on_freq = (uint8_t) write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_NEGATIVE:
                        {
                            gp_touch_ctrl_list[num]->binfo.off_freq = (uint8_t) write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_MOVING_AVG:
                        {
                            p_ctsu_ctrl->num_moving_average = write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_THRESHOLD:
                        {
                            gp_touch_ctrl_list[num]->binfo.p_threshold[element] = write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_HYSTERESIS:
                        {
                            gp_touch_ctrl_list[num]->binfo.p_hysteresis[element] = write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_THRESH_SLDR:
                        {
                            gp_touch_ctrl_list[num]->sinfo.p_threshold[element] = write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_THRESH_WHEL:
                        {
                            gp_touch_ctrl_list[num]->winfo.p_threshold[element] = write_data;
                            break;
                        }

                        case TOUCH_UART_WRITE_CTSUSO:
                        {
  #if (BSP_FEATURE_CTSU_VERSION == 2)
                            *p_ctsuso &= (uint32_t) (~TOUCH_UART_CTSUSO_MASK);
                            *p_ctsuso |= write_data;
  #endif
  #if (BSP_FEATURE_CTSU_VERSION == 1)
                            *p_ctsuso &= (uint16_t) (~TOUCH_UART_CTSUSO_MASK);
                            *p_ctsuso |= write_data;
  #endif
                            break;
                        }

                        case TOUCH_UART_WRITE_CTSUSNUM:
                        {
  #if (BSP_FEATURE_CTSU_VERSION == 2)
                            *p_ctsusnum &= (uint32_t) (~(TOUCH_UART_CTSUSNUM_MASK << TOUCH_UART_CTSUSNUM_SHIFT));
                            *p_ctsusnum |= (uint32_t) (write_data << TOUCH_UART_CTSUSNUM_SHIFT);
  #endif
  #if (BSP_FEATURE_CTSU_VERSION == 1)
                            *p_ctsusnum &= (uint16_t) (~(TOUCH_UART_CTSUSNUM_MASK << TOUCH_UART_CTSUSNUM_SHIFT));
                            *p_ctsusnum |= (uint16_t) (write_data << TOUCH_UART_CTSUSNUM_SHIFT);
  #endif
                            break;
                        }

                        case TOUCH_UART_WRITE_CTSUSDPA:
                        {
  #if (BSP_FEATURE_CTSU_VERSION == 2)
                            *p_ctsusdpa &= (uint32_t) (~(TOUCH_UART_CTSUSDPA_MASK << TOUCH_UART_CTSUSDPA_SHIFT));
                            *p_ctsusdpa |= (uint32_t) (write_data << TOUCH_UART_CTSUSDPA_SHIFT);
  #endif
  #if (BSP_FEATURE_CTSU_VERSION == 1)
                            *p_ctsusdpa &= (uint16_t) (~(TOUCH_UART_CTSUSDPA_MASK << TOUCH_UART_CTSUSDPA_SHIFT));
                            *p_ctsusdpa |= (uint16_t) (write_data << TOUCH_UART_CTSUSDPA_SHIFT);
  #endif
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
            }
        }
        else if (g_touch_uart_rx_buf[1] == TOUCH_UART_COMMAND_VERSION)
        {
            g_touch_monitor_buf[index++] = g_touch_version.code_version_minor;
            g_touch_monitor_buf[index++] = g_touch_version.code_version_major;
        }
        else
        {
        }

        /* Set fixed footer */
        g_touch_monitor_buf[index++] = TOUCH_UART_FOOTER;

        /* Set data size */
        g_touch_monitor_buf[2] = (uint8_t) index;
        g_touch_monitor_buf[3] = (uint8_t) (index >> 8);

        /* Start transmission */
        g_touch_uart_transmit_flag = 1;
        gp_touch_uart_instance->p_api->write(gp_touch_uart_instance->p_ctrl,
                                             (uint8_t const * const) &g_touch_monitor_buf,
                                             index);

        /* Restart reception */
        gp_touch_uart_instance->p_api->read(gp_touch_uart_instance->p_ctrl,
                                            &g_touch_uart_rx_buf[0],
                                            TOUCH_UART_RECIEVE_BUF_SIZE);
    }
    else
    {
    }

    /* End user code. Do not edit comment generated here */
}

 #endif
#endif
