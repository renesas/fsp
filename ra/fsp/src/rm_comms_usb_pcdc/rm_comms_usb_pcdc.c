/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_comms_usb_pcdc.h"
#include "../rm_comms_lock/rm_comms_lock.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag "COUT" */
#define RM_COMMS_USB_PCDC_OPEN                                        (0x434F5554UL)

/* Number of bytes to transfer on data stage for Line Coding Class request */
#define RM_COMMS_USB_PCDC_LINE_CODING_LENGTH                          (0x07U)

/* Connection and Disconnection detection type */
#define RM_COMMS_USB_PCDC_CONNECT_DETECTION_DISABLED                  (0)
#define RM_COMMS_USB_PCDC_CONNECT_DETECTION_BAUDRATE_CONFIGURATION    (1)
#define RM_COMMS_USB_PCDC_CONNECT_DETECTION_CONTROL_LINE_STATE        (2)
#define RM_COMMS_USB_PCDC_CLEAR_DETECTION_STATUS_VAL                  (0)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static rm_comms_event_t rm_comms_usb_pcdc_update_detection_status(rm_comms_usb_pcdc_instance_ctrl_t * const p_ctrl,
                                                                  uint16_t                                  value);

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_comms_api_t const g_comms_on_comms_usb_pcdc =
{
    .open        = RM_COMMS_USB_PCDC_Open,
    .read        = RM_COMMS_USB_PCDC_Read,
    .write       = RM_COMMS_USB_PCDC_Write,
    .writeRead   = RM_COMMS_USB_PCDC_WriteRead,
    .callbackSet = RM_COMMS_USB_PCDC_CallbackSet,
    .close       = RM_COMMS_USB_PCDC_Close,
};

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Comms USB variable to store p_ctrl, which is used for invoking Comms Callback in callback handler */
static rm_comms_usb_pcdc_instance_ctrl_t * g_comms_usb_pcdc_crtl[USB_NUM_USBIP];

#if BSP_CFG_RTOS == 0

/* Comms USB pcdc variable for usb callback event */
static usb_callback_args_t g_comms_usb_pcdc_event_callback[USB_NUM_USBIP];
#endif

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_USB_PCDC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the USB PCDC Comms module. Implements @ref rm_comms_api_t::open.
 *
 *
 * @retval FSP_SUCCESS                  USB PCDC Comms module successfully configured.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.  This module can only be opened once.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_USB_PCDC_Open (rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_usb_pcdc_instance_ctrl_t * p_ctrl = (rm_comms_usb_pcdc_instance_ctrl_t *) p_api_ctrl;
#if RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(RM_COMMS_USB_PCDC_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    rm_comms_usb_pcdc_extended_cfg_t * p_extend = (rm_comms_usb_pcdc_extended_cfg_t *) p_cfg->p_extend;

#if RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extend);
    FSP_ASSERT(NULL != p_extend->p_usb);
    FSP_ASSERT(NULL != p_extend->p_usb->p_cfg);
#endif

    usb_instance_t * p_usb_instance = (usb_instance_t *) p_extend->p_usb;

    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->p_extend   = p_extend;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

    /* Store rm_comms_ctrl to g_comms_usb_pcdc_crtl */
    g_comms_usb_pcdc_crtl[p_usb_instance->p_cfg->module_number] = p_ctrl;

#if BSP_CFG_RTOS == 2
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

#if BSP_CFG_RTOS == 0
 #if RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extend->p_gpt);
 #endif

    timer_api_t const * p_timer_api = p_extend->p_gpt->p_api;

    err = p_timer_api->open(p_extend->p_gpt->p_ctrl, p_extend->p_gpt->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err || FSP_ERR_ALREADY_OPEN == err, err);

    /* Set callback function for Timer driver */
    err =
        p_timer_api->callbackSet(p_extend->p_gpt->p_ctrl,
                                 rm_comms_usb_pcdc_timer_handler,
                                 (void *) p_usb_instance->p_api,
                                 NULL);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    usb_api_t const * p_usb_api = p_usb_instance->p_api;

    /* Open USB driver */
    err = p_usb_api->open(p_usb_instance->p_ctrl, p_usb_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS == 2

    /* Set callback function for USB driver */
    err = p_usb_api->callback(rm_comms_usb_pcdc_callback_handler);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

#if BSP_CFG_RTOS == 0

    /* Specify the area to store USB events to USB driver */
    err =
        p_usb_api->callbackMemorySet(p_usb_instance->p_ctrl,
                                     &g_comms_usb_pcdc_event_callback[p_usb_instance->p_cfg->module_number]);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Start timer */
    err = p_timer_api->start(p_extend->p_gpt->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set open flag */
    p_ctrl->open = RM_COMMS_USB_PCDC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified USB PCDC Comms module. Implements @ref rm_comms_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_USB_PCDC_Close (rm_comms_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_usb_pcdc_instance_ctrl_t * p_ctrl = (rm_comms_usb_pcdc_instance_ctrl_t *) p_api_ctrl;
#if RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_COMMS_USB_PCDC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_usb_pcdc_extended_cfg_t const * p_extend = (rm_comms_usb_pcdc_extended_cfg_t *) p_ctrl->p_extend;

#if BSP_CFG_RTOS == 0

    /* Close Timer */
    timer_instance_t const * p_timer_instance = p_extend->p_gpt;

    err = p_timer_instance->p_api->close(p_timer_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err || FSP_ERR_NOT_OPEN == err, err);
#endif

    usb_api_t const * p_usb_api = p_extend->p_usb->p_api;

    err = p_usb_api->close(p_extend->p_usb->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS == 2
    if (NULL != p_extend->p_tx_mutex)
    {
        /* Destroy mutex for writing */
        err = rm_comms_recursive_mutex_destroy(p_extend->p_tx_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_rx_mutex)
    {
        /* Destroy mutex for reading */
        err = rm_comms_recursive_mutex_destroy(p_extend->p_rx_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_tx_semaphore)
    {
        /* Destroy semaphore for writing */
        err = rm_comms_semaphore_destroy(p_extend->p_tx_semaphore);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_extend->p_rx_semaphore)
    {
        /* Destroy semaphore for reading */
        err = rm_comms_semaphore_destroy(p_extend->p_rx_semaphore);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Clear open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Updates the USB PCDC Comms callback. Implements @ref rm_comms_api_t::callbackSet.
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_USB_PCDC_CallbackSet (rm_comms_ctrl_t * const p_api_ctrl,
                                         void (                * p_callback)(rm_comms_callback_args_t *),
                                         void * const            p_context)
{
    rm_comms_usb_pcdc_instance_ctrl_t * p_ctrl = (rm_comms_usb_pcdc_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(RM_COMMS_USB_PCDC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Performs a read from the USB PCDC device. Implements @ref rm_comms_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_NOT_ENABLED      USB device needs connecting from USB host to operate.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_USB_PCDC_Read (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_usb_pcdc_instance_ctrl_t * p_ctrl = (rm_comms_usb_pcdc_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_dest);
    FSP_ERROR_RETURN(RM_COMMS_USB_PCDC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_usb_pcdc_extended_cfg_t const * p_extend = p_ctrl->p_extend;
    usb_instance_t const * p_usb = p_extend->p_usb;

    if ((p_extend->connect_detection_en == RM_COMMS_USB_PCDC_CONNECT_DETECTION_BAUDRATE_CONFIGURATION) &&
        (p_ctrl->line_coding.dw_dte_rate == 0))
    {
        FSP_RETURN(FSP_ERR_NOT_ENABLED);
    }

    if ((p_extend->connect_detection_en == RM_COMMS_USB_PCDC_CONNECT_DETECTION_CONTROL_LINE_STATE) &&
        (p_ctrl->ctrl_line_state.bdtr == 0))
    {
        FSP_RETURN(FSP_ERR_NOT_ENABLED);
    }

#if BSP_CFG_RTOS == 2
    if (NULL != p_extend->p_rx_mutex)
    {
        /* Acquire read mutex */
        err = rm_comms_recursive_mutex_acquire(p_extend->p_rx_mutex, p_extend->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Use USB PDCD driver to read data */
    err = p_usb->p_api->read(p_usb->p_ctrl, p_dest, bytes, USB_CLASS_PCDC);

#if BSP_CFG_RTOS == 2
    fsp_err_t sem_err   = FSP_SUCCESS;
    fsp_err_t mutex_err = FSP_SUCCESS;
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
 * @brief Performs a write to the USB PCDC device. Implements @ref rm_comms_api_t::write.
 *
 * @retval FSP_SUCCESS              Successfully writing data .
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_NOT_ENABLED      USB device needs connecting from USB host to operate.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_USB_PCDC_Write (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_usb_pcdc_instance_ctrl_t * p_ctrl = (rm_comms_usb_pcdc_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ERROR_RETURN(RM_COMMS_USB_PCDC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_usb_pcdc_extended_cfg_t const * p_extend = p_ctrl->p_extend;
    usb_instance_t const * p_usb = p_extend->p_usb;

    if ((p_extend->connect_detection_en == RM_COMMS_USB_PCDC_CONNECT_DETECTION_BAUDRATE_CONFIGURATION) &&
        (p_ctrl->line_coding.dw_dte_rate == 0))
    {
        FSP_RETURN(FSP_ERR_NOT_ENABLED);
    }

    if ((p_extend->connect_detection_en == RM_COMMS_USB_PCDC_CONNECT_DETECTION_CONTROL_LINE_STATE) &&
        (p_ctrl->ctrl_line_state.bdtr == 0))
    {
        FSP_RETURN(FSP_ERR_NOT_ENABLED);
    }

#if BSP_CFG_RTOS == 2
    if (NULL != p_extend->p_tx_mutex)
    {
        /* Acquire write mutex */
        err = rm_comms_recursive_mutex_acquire(p_extend->p_tx_mutex, p_extend->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Use USB PDCD driver to write data */
    err = p_usb->p_api->write(p_usb->p_ctrl, p_src, bytes, USB_CLASS_PCDC);

#if BSP_CFG_RTOS == 2
    fsp_err_t sem_err   = FSP_SUCCESS;
    fsp_err_t mutex_err = FSP_SUCCESS;
    if ((FSP_SUCCESS == err) && (NULL != p_extend->p_tx_semaphore))
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

    return err;
}

/*******************************************************************************************************************//**
 * @brief Performs a write to, then a read from the USB device. Implements @ref rm_comms_api_t::writeRead.
 *
 * @retval FSP_ERR_UNSUPPORTED      Not supported.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_USB_PCDC_WriteRead (rm_comms_ctrl_t * const            p_api_ctrl,
                                       rm_comms_write_read_params_t const write_read_params)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(write_read_params);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_USB_PCDC)
 **********************************************************************************************************************/

void rm_comms_usb_pcdc_notify_application (rm_comms_usb_pcdc_instance_ctrl_t const * p_ctrl, rm_comms_event_t event)
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

/*******************************************************************************************************************//**
 * @brief Common function to update dectection status.
 **********************************************************************************************************************/
static rm_comms_event_t rm_comms_usb_pcdc_update_detection_status (rm_comms_usb_pcdc_instance_ctrl_t * const p_ctrl,
                                                                   uint16_t                                  line_state_value)
{
    rm_comms_event_t err = RM_COMMS_EVENT_ERROR;

    if (p_ctrl->p_extend->connect_detection_en == RM_COMMS_USB_PCDC_CONNECT_DETECTION_BAUDRATE_CONFIGURATION)
    {
        p_ctrl->line_coding.dw_dte_rate = 0;
    }
    else if (p_ctrl->p_extend->connect_detection_en == RM_COMMS_USB_PCDC_CONNECT_DETECTION_CONTROL_LINE_STATE)
    {
        uint16_t * p_line_state = (uint16_t *) &p_ctrl->ctrl_line_state;
        *p_line_state = line_state_value;

        err = (p_ctrl->ctrl_line_state.bdtr) ? RM_COMMS_EVENT_TX_OPERATION_COMPLETE : RM_COMMS_EVENT_ERROR;
    }
    else
    {
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Common callback function called in the USB PCDC driver callback function.
 **********************************************************************************************************************/
#if BSP_CFG_RTOS == 2
void rm_comms_usb_pcdc_callback_handler (usb_instance_ctrl_t * p_args,
                                         usb_hdl_t             usb_handle,
                                         usb_onoff_t           usb_onoff_status)
#elif BSP_CFG_RTOS == 0
void rm_comms_usb_pcdc_callback_handler (usb_callback_args_t * p_args)
#endif
{
    rm_comms_usb_pcdc_instance_ctrl_t * p_ctrl = g_comms_usb_pcdc_crtl[p_args->module_number];

#if BSP_CFG_RTOS == 2
    rm_comms_usb_pcdc_extended_cfg_t const * p_extend = p_ctrl->p_extend;
#endif

    p_ctrl->p_usb_args = p_args;

    switch (p_args->event)
    {
        case USB_STATUS_CONFIGURED:
        {
            rm_comms_usb_pcdc_update_detection_status(p_ctrl, RM_COMMS_USB_PCDC_CLEAR_DETECTION_STATUS_VAL);

            break;
        }

        case USB_STATUS_RESUME:
        {
            rm_comms_usb_pcdc_notify_application(p_ctrl, RM_COMMS_EVENT_OPERATION_COMPLETE);
            break;
        }

        case USB_STATUS_WRITE_COMPLETE:
        {
#if BSP_CFG_RTOS == 2
            if (NULL != p_extend->p_tx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_tx_semaphore);
            }
#endif
            rm_comms_usb_pcdc_notify_application(p_ctrl, RM_COMMS_EVENT_TX_OPERATION_COMPLETE);
            break;
        }

        case USB_STATUS_READ_COMPLETE:
        {
#if BSP_CFG_RTOS == 2
            if (NULL != p_extend->p_rx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_rx_semaphore);
            }
#endif
            rm_comms_usb_pcdc_notify_application(p_ctrl, RM_COMMS_EVENT_RX_OPERATION_COMPLETE);
            break;
        }

        case USB_STATUS_REQUEST:       /* Receive Class Request */
        {
            usb_instance_t * p_usb_instance = (usb_instance_t *) p_ctrl->p_extend->p_usb;

            /* Check for the specific CDC class request IDs */
            if (USB_PCDC_SET_LINE_CODING == (p_args->setup.request_type & USB_BREQUEST))
            {
                p_usb_instance->p_api->periControlDataGet(p_usb_instance->p_ctrl,
                                                          (uint8_t *) &p_ctrl->line_coding,
                                                          RM_COMMS_USB_PCDC_LINE_CODING_LENGTH);
            }
            else if (USB_PCDC_GET_LINE_CODING == (p_args->setup.request_type & USB_BREQUEST))
            {
                p_usb_instance->p_api->periControlDataSet(p_usb_instance->p_ctrl,
                                                          (uint8_t *) &p_ctrl->line_coding,
                                                          RM_COMMS_USB_PCDC_LINE_CODING_LENGTH);
            }
            else if (USB_PCDC_SET_CONTROL_LINE_STATE == (p_args->setup.request_type & USB_BREQUEST))
            {
                rm_comms_event_t err = rm_comms_usb_pcdc_update_detection_status(p_ctrl, p_args->setup.request_value);

                rm_comms_usb_pcdc_notify_application(p_ctrl, err);

                p_usb_instance->p_api->periControlStatusSet(p_usb_instance->p_ctrl, USB_SETUP_STATUS_ACK);
            }
            else
            {
                p_usb_instance->p_api->periControlStatusSet(p_usb_instance->p_ctrl, USB_SETUP_STATUS_ACK);
            }

            break;
        }

        case USB_STATUS_DETACH:
        {
#if BSP_CFG_RTOS == 2
            if (NULL != p_extend->p_tx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_tx_semaphore);
            }

            if (NULL != p_extend->p_rx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_rx_semaphore);
            }
#endif
            rm_comms_usb_pcdc_update_detection_status(p_ctrl, RM_COMMS_USB_PCDC_CLEAR_DETECTION_STATUS_VAL);

            rm_comms_usb_pcdc_notify_application(p_ctrl, RM_COMMS_EVENT_ERROR);
            break;
        }

        case USB_STATUS_SUSPEND:
        {
#if BSP_CFG_RTOS == 2
            if (NULL != p_extend->p_tx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_tx_semaphore);
            }

            if (NULL != p_extend->p_rx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_rx_semaphore);
            }
#endif
            rm_comms_usb_pcdc_notify_application(p_ctrl, RM_COMMS_EVENT_ERROR);
            break;
        }

        case USB_STATUS_REQUEST_COMPLETE:
        case USB_STATUS_DEFAULT:
        {
            break;
        }

        default:
        {
#if BSP_CFG_RTOS == 2
            if (NULL != p_extend->p_tx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_tx_semaphore);
            }

            if (NULL != p_extend->p_rx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_rx_semaphore);
            }
#endif
            break;
        }
    }

#if BSP_CFG_RTOS == 2
    FSP_PARAMETER_NOT_USED(usb_handle);
    FSP_PARAMETER_NOT_USED(usb_onoff_status);
#endif
}

#if BSP_CFG_RTOS == 0

/*******************************************************************************************************************//**
 * @brief Timer callback function.
 **********************************************************************************************************************/
void rm_comms_usb_pcdc_timer_handler (timer_callback_args_t * p_args)
{
    usb_api_t const   * p_usb_api = (usb_api_t *) (p_args->p_context);
    usb_instance_ctrl_t ctrl;

    p_usb_api->eventGet(&ctrl, &ctrl.event);
    if (ctrl.event != USB_STATUS_NONE)
    {
        rm_comms_usb_pcdc_callback_handler(&ctrl);
    }
}

#endif
