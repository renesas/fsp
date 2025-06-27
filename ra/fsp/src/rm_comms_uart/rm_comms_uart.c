/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_comms_uart.h"
#include "../rm_comms_lock/rm_comms_lock.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag "COUT" */
#define RM_COMMS_UART_OPEN    (0x434F5554UL)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_comms_uart_callback(uart_callback_args_t * p_args);
static void rm_comms_uart_notify_application(rm_comms_uart_instance_ctrl_t const * p_ctrl, rm_comms_event_t event);

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_comms_api_t const g_comms_on_comms_uart =
{
    .open        = RM_COMMS_UART_Open,
    .read        = RM_COMMS_UART_Read,
    .write       = RM_COMMS_UART_Write,
    .writeRead   = RM_COMMS_UART_WriteRead,
    .callbackSet = RM_COMMS_UART_CallbackSet,
    .close       = RM_COMMS_UART_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_UART
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the UART Comms module. Implements @ref rm_comms_api_t::open.
 *
 *
 * @retval FSP_SUCCESS                  UART Comms module successfully configured.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.  This module can only be opened once.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_Open (rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_uart_instance_ctrl_t * p_ctrl = (rm_comms_uart_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_UART_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(RM_COMMS_UART_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    rm_comms_uart_extended_cfg_t * p_extend = (rm_comms_uart_extended_cfg_t *) p_cfg->p_extend;

#if RM_COMMS_UART_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extend);
    FSP_ASSERT(NULL != p_extend->p_uart);
#endif

    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->p_extend   = p_extend;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

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

    /*  Calls open function of UART HAL driver */
    uart_api_t const * p_uart_api = p_extend->p_uart->p_api;
    err = p_uart_api->open(p_extend->p_uart->p_ctrl, p_extend->p_uart->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set callback function */
    err = p_uart_api->callbackSet(p_extend->p_uart->p_ctrl, rm_comms_uart_callback, p_ctrl, NULL);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set open flag */
    p_ctrl->open = RM_COMMS_UART_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified UART Comms module. Implements @ref rm_comms_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_Close (rm_comms_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_uart_instance_ctrl_t * p_ctrl = (rm_comms_uart_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_UART_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_COMMS_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_uart_extended_cfg_t const * p_extend = p_ctrl->p_extend;
    uart_api_t const * p_uart_api                 = p_extend->p_uart->p_api;

    err = p_uart_api->close(p_extend->p_uart->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

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

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Updates the UART Comms callback. Implements @ref rm_comms_api_t::callbackSet.
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_CallbackSet (rm_comms_ctrl_t * const p_api_ctrl,
                                     void (                * p_callback)(rm_comms_callback_args_t *),
                                     void * const            p_context)
{
    rm_comms_uart_instance_ctrl_t * p_ctrl = (rm_comms_uart_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_UART_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(RM_COMMS_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Performs a read from the UART device. Implements @ref rm_comms_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_Read (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_uart_instance_ctrl_t * p_ctrl = (rm_comms_uart_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_UART_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_dest);
    FSP_ERROR_RETURN(RM_COMMS_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_uart_extended_cfg_t const * p_extend = p_ctrl->p_extend;
    uart_api_t const * p_uart_api                 = p_extend->p_uart->p_api;

#if BSP_CFG_RTOS
    if (NULL != p_extend->p_rx_mutex)
    {
        /* Acquire read mutex */
        err = rm_comms_recursive_mutex_acquire(p_extend->p_rx_mutex, p_extend->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Use UART driver to read data */
    err = p_uart_api->read(p_extend->p_uart->p_ctrl, p_dest, bytes);

#if BSP_CFG_RTOS
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
 * @brief Performs a write to the UART device. Implements @ref rm_comms_api_t::write.
 *
 * @retval FSP_SUCCESS              Successfully writing data .
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_Write (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_uart_instance_ctrl_t * p_ctrl = (rm_comms_uart_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_UART_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ERROR_RETURN(RM_COMMS_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_uart_extended_cfg_t const * p_extend = p_ctrl->p_extend;
    uart_api_t const * p_uart_api                 = p_extend->p_uart->p_api;

#if BSP_CFG_RTOS
    if (NULL != p_extend->p_tx_mutex)
    {
        /* Acquire write mutex */
        err = rm_comms_recursive_mutex_acquire(p_extend->p_tx_mutex, p_extend->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Use UART driver to write data */
    err = p_uart_api->write(p_extend->p_uart->p_ctrl, p_src, bytes);

#if BSP_CFG_RTOS
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
 * @brief Performs a write to, then a read from the UART device. Implements @ref rm_comms_api_t::writeRead.
 *
 * @retval FSP_ERR_UNSUPPORTED      Not supported.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_WriteRead (rm_comms_ctrl_t * const            p_api_ctrl,
                                   rm_comms_write_read_params_t const write_read_params)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(write_read_params);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_UART)
 **********************************************************************************************************************/

static void rm_comms_uart_notify_application (rm_comms_uart_instance_ctrl_t const * p_ctrl, rm_comms_event_t event)
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
 * @brief Common callback function called in the UART driver callback function.
 **********************************************************************************************************************/
static void rm_comms_uart_callback (uart_callback_args_t * p_args)
{
    rm_comms_uart_instance_ctrl_t * p_ctrl = (rm_comms_uart_instance_ctrl_t *) (p_args->p_context);
#if BSP_CFG_RTOS
    rm_comms_uart_extended_cfg_t const * p_extend = p_ctrl->p_extend;
#endif

    switch (p_args->event)
    {
        case UART_EVENT_TX_COMPLETE:
        {
#if BSP_CFG_RTOS
            if (NULL != p_extend->p_tx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_tx_semaphore);
            }
#endif
            rm_comms_uart_notify_application(p_ctrl, RM_COMMS_EVENT_TX_OPERATION_COMPLETE);
            break;
        }

        case UART_EVENT_RX_COMPLETE:
        {
#if BSP_CFG_RTOS
            if (NULL != p_extend->p_rx_semaphore)
            {
                rm_comms_semaphore_release(p_extend->p_rx_semaphore);
            }
#endif
            rm_comms_uart_notify_application(p_ctrl, RM_COMMS_EVENT_RX_OPERATION_COMPLETE);
            break;
        }

        case UART_EVENT_RX_CHAR:
        case UART_EVENT_TX_DATA_EMPTY: // Continue Tx/Rx
        {
            break;
        }

        default:                       // Stop both Tx and Rx on UART Error
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
            rm_comms_uart_notify_application(p_ctrl, RM_COMMS_EVENT_ERROR);

            break;
        }
    }
}
