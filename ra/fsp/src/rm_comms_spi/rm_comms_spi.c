/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_comms_spi.h"
#include "../rm_comms_lock/rm_comms_lock.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag "COSP" */
#define RM_COMMS_SPI_OPEN    (0x434F5350UL)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* SPI operations */
typedef enum e_rm_comms_spi_op
{
    RM_COMMS_SPI_READ,
    RM_COMMS_SPI_WRITE,
    RM_COMMS_SPI_WRITEREAD,
} rm_comms_spi_op_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if RM_COMMS_SPI_CFG_SLAVE_SELECT_ENABLE
static void rm_comms_spi_config_ssl(uint32_t delay, bsp_io_port_pin_t pin, uint32_t level);

#endif
static void      rm_comms_spi_notify_application(rm_comms_spi_instance_ctrl_t const * p_ctrl, rm_comms_event_t event);
static fsp_err_t rm_comms_spi_read_write_common(rm_comms_ctrl_t       * p_api_ctrl,
                                                rm_comms_spi_op_t const rw,
                                                uint8_t * const         p_src,
                                                uint8_t * const         p_dest,
                                                uint32_t const          bytes);

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_comms_api_t const g_comms_on_comms_spi =
{
    .open        = RM_COMMS_SPI_Open,
    .read        = RM_COMMS_SPI_Read,
    .write       = RM_COMMS_SPI_Write,
    .writeRead   = RM_COMMS_SPI_WriteRead,
    .callbackSet = RM_COMMS_SPI_CallbackSet,
    .close       = RM_COMMS_SPI_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_SPI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the SPI Comms module. Implements @ref rm_comms_api_t::open.
 *
 *
 * @retval FSP_SUCCESS                  SPI Comms module successfully configured.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.  This module can only be opened once.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SPI_Open (rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg)
{
    rm_comms_spi_instance_ctrl_t * p_ctrl = (rm_comms_spi_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(RM_COMMS_SPI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg->p_extend);
#endif

    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->p_bus      = (rm_comms_spi_bus_extended_cfg_t *) p_cfg->p_extend;
    p_ctrl->p_device   = (rm_comms_spi_device_extended_cfg_t *) p_cfg->p_lower_level_cfg;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

#if BSP_CFG_RTOS
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if (!p_ctrl->p_bus->initialized)
    {
        p_ctrl->p_bus->initialized = true;
        FSP_CRITICAL_SECTION_EXIT;

        /* Create semaphore. */
        if (NULL != p_ctrl->p_bus->p_semaphore)
        {
            rm_comms_semaphore_initialize(p_ctrl->p_bus->p_semaphore);
        }

        /* Create recursive mutex. */
        if (NULL != p_ctrl->p_bus->p_mutex)
        {
            rm_comms_recursive_mutex_initialize(p_ctrl->p_bus->p_mutex);
        }
    }
    else
    {
        FSP_CRITICAL_SECTION_EXIT;
    }
#endif

    /* Set open flag */
    p_ctrl->open = RM_COMMS_SPI_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified SPI Comms module. Implements @ref rm_comms_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SPI_Close (rm_comms_ctrl_t * const p_api_ctrl)
{
    rm_comms_spi_instance_ctrl_t * p_ctrl = (rm_comms_spi_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_COMMS_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_spi_bus_extended_cfg_t * p_bus             = p_ctrl->p_bus;
    spi_instance_t const            * p_driver_instance = p_ctrl->p_device->p_driver_instance;

#if BSP_CFG_RTOS
    if (NULL != p_bus->p_mutex)
    {
        /* Acquire mutex */
        fsp_err_t err = rm_comms_recursive_mutex_acquire(p_bus->p_mutex, p_bus->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Close only if it is the active device on the bus. */
    if (p_bus->p_current_ctrl == p_ctrl)
    {
#if RM_COMMS_SPI_CFG_SLAVE_SELECT_ENABLE
        rm_comms_spi_device_extended_cfg_t * p_device = p_ctrl->p_device;

        /* De-select slave */
        rm_comms_spi_config_ssl(p_device->ssl_delay, p_device->ssl_pin, BSP_IO_LEVEL_HIGH - p_device->ssl_level);
#endif

        p_driver_instance->p_api->close(p_driver_instance->p_ctrl);
        p_bus->p_current_ctrl = NULL;
    }

    /* Clear open flag */
    p_ctrl->open = 0;

#if BSP_CFG_RTOS
    if (NULL != p_bus->p_mutex)
    {
        /* Release mutex */
        rm_comms_recursive_mutex_release(p_bus->p_mutex);
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Updates the SPI Comms callback. Implements @ref rm_comms_api_t::callbackSet.
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SPI_CallbackSet (rm_comms_ctrl_t * const p_api_ctrl,
                                    void (                * p_callback)(rm_comms_callback_args_t *),
                                    void * const            p_context)
{
    rm_comms_spi_instance_ctrl_t * p_ctrl = (rm_comms_spi_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(RM_COMMS_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Performs a read from the SPI bus. Implements @ref rm_comms_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SPI_Read (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
#if RM_COMMS_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_dest);
#endif

    return rm_comms_spi_read_write_common(p_api_ctrl, RM_COMMS_SPI_READ, NULL, p_dest, bytes);
}

/*******************************************************************************************************************//**
 * @brief Performs a write to the SPI bus. Implements @ref rm_comms_api_t::write.
 *
 * @retval FSP_SUCCESS              Successfully writing data .
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SPI_Write (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
#if RM_COMMS_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_src);
#endif

    return rm_comms_spi_read_write_common(p_api_ctrl, RM_COMMS_SPI_WRITE, p_src, NULL, bytes);
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
fsp_err_t RM_COMMS_SPI_WriteRead (rm_comms_ctrl_t * const            p_api_ctrl,
                                  rm_comms_write_read_params_t const write_read_params)
{
#if RM_COMMS_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != write_read_params.p_src);
    FSP_ASSERT(NULL != write_read_params.p_dest);
    FSP_ERROR_RETURN(write_read_params.src_bytes == write_read_params.dest_bytes, FSP_ERR_INVALID_ARGUMENT);
#endif

    return rm_comms_spi_read_write_common(p_api_ctrl,
                                          RM_COMMS_SPI_WRITEREAD,
                                          write_read_params.p_src,
                                          write_read_params.p_dest,
                                          write_read_params.src_bytes);
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_SPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initiates a SPI transfer for all operation modes. When mutex is used, bus will be acquired first. When semaphore
 * is used, operation will be blocked until it is completed.
 *
 * @param[in]  p_api_ctrl        pointer to control structure.
 * @param[in]  rw                operation mode.
 * @param      p_src             Buffer to transmit data from.
 * @param      p_dest            Buffer to store received data in.
 * @param[in]  bytes             Number of transfers
 *
 * @retval     FSP_SUCCESS       Transfer was started successfully.
 * @retval     FSP_ERR_ASSERTION An argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN  Module is not open..
 * @return                       See @ref RENESAS_ERROR_CODES for other possible return codes. This function internally
 *                               calls @ref transfer_api_t::reconfigure.
 **********************************************************************************************************************/
static fsp_err_t rm_comms_spi_read_write_common (rm_comms_ctrl_t       * p_api_ctrl,
                                                 rm_comms_spi_op_t const rw,
                                                 uint8_t * const         p_src,
                                                 uint8_t * const         p_dest,
                                                 uint32_t const          bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_spi_instance_ctrl_t * p_ctrl = (rm_comms_spi_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_COMMS_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0 != bytes);
#endif

    spi_instance_t const               * p_driver_instance;
    rm_comms_spi_device_extended_cfg_t * p_device       = p_ctrl->p_device;
    rm_comms_spi_bus_extended_cfg_t    * p_bus          = p_ctrl->p_bus;
    rm_comms_spi_instance_ctrl_t       * p_current_ctrl = (rm_comms_spi_instance_ctrl_t *) p_bus->p_current_ctrl;

#if BSP_CFG_RTOS
    if (NULL != p_bus->p_mutex)
    {
        /* Acquire mutex */
        err = rm_comms_recursive_mutex_acquire(p_bus->p_mutex, p_bus->mutex_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    if (p_current_ctrl != p_ctrl)
    {
        /* If a different device is to be accessed, close the current one first. */
        if (NULL != p_current_ctrl)
        {
            p_driver_instance = p_current_ctrl->p_device->p_driver_instance;
            p_driver_instance->p_api->close(p_driver_instance->p_ctrl);

#if RM_COMMS_SPI_CFG_SLAVE_SELECT_ENABLE

            /* De-select SSL */
            rm_comms_spi_config_ssl(p_current_ctrl->p_device->ssl_delay,
                                    p_current_ctrl->p_device->ssl_pin,
                                    BSP_IO_LEVEL_HIGH - p_current_ctrl->p_device->ssl_level);
#endif

            p_bus->p_current_ctrl = NULL;
        }

        p_driver_instance = p_device->p_driver_instance;
        err               = p_driver_instance->p_api->open(p_driver_instance->p_ctrl, p_driver_instance->p_cfg);
        if (FSP_SUCCESS == err)
        {
            /* Update the current device. */
            p_bus->p_current_ctrl = p_ctrl;

            /* Set callback function */
            p_driver_instance->p_api->callbackSet(p_driver_instance->p_ctrl, rm_comms_spi_callback, p_ctrl, NULL);

#if RM_COMMS_SPI_CFG_SLAVE_SELECT_ENABLE

            /* Select SSL */
            rm_comms_spi_config_ssl(p_device->ssl_delay, p_device->ssl_pin, p_device->ssl_level);
#endif
        }
    }
    else
    {
        p_driver_instance = p_device->p_driver_instance;
    }

    if (FSP_SUCCESS == err)
    {
        switch (rw)
        {
            case RM_COMMS_SPI_WRITE:
            {
                err = p_driver_instance->p_api->write(p_device->p_driver_instance->p_ctrl,
                                                      p_src,
                                                      bytes,
                                                      SPI_BIT_WIDTH_8_BITS);
                break;
            }

            case RM_COMMS_SPI_WRITEREAD:
            {
                err = p_driver_instance->p_api->writeRead(p_device->p_driver_instance->p_ctrl,
                                                          p_src,
                                                          p_dest,
                                                          bytes,
                                                          SPI_BIT_WIDTH_8_BITS);
                break;
            }

            default:
            {
                err = p_driver_instance->p_api->read(p_device->p_driver_instance->p_ctrl,
                                                     p_dest,
                                                     bytes,
                                                     SPI_BIT_WIDTH_8_BITS);
                break;
            }
        }
    }

#if BSP_CFG_RTOS
    fsp_err_t sem_err   = FSP_SUCCESS;
    fsp_err_t mutex_err = FSP_SUCCESS;
    if ((FSP_SUCCESS == err) && (NULL != p_bus->p_semaphore))
    {
        /* Wait for read/write to complete */
        sem_err = rm_comms_semaphore_acquire(p_bus->p_semaphore, p_ctrl->p_cfg->semaphore_timeout);
    }

    if (NULL != p_bus->p_mutex)
    {
        /* Release mutex */
        mutex_err = rm_comms_recursive_mutex_release(p_bus->p_mutex);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == sem_err, sem_err);
    FSP_ERROR_RETURN(FSP_SUCCESS == mutex_err, mutex_err);
#endif

    return err;
}

#if RM_COMMS_SPI_CFG_SLAVE_SELECT_ENABLE

/*******************************************************************************************************************//**
 * @brief Configure slave select.
 **********************************************************************************************************************/
static void rm_comms_spi_config_ssl (uint32_t delay, bsp_io_port_pin_t pin, uint32_t level)
{
    if (pin != BSP_IO_PORT_FF_PIN_FF)
    {
        /* Configure SSL pin settings */
        R_BSP_PinAccessEnable();
        R_BSP_PinWrite(pin, (bsp_io_level_t) level);
        R_BSP_PinAccessDisable();

        R_BSP_SoftwareDelay(delay, BSP_DELAY_UNITS_MICROSECONDS);
    }
}

#endif

static void rm_comms_spi_notify_application (rm_comms_spi_instance_ctrl_t const * p_ctrl, rm_comms_event_t event)
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
 * @brief Common callback function called in the SPI driver callback function.
 **********************************************************************************************************************/
void rm_comms_spi_callback (spi_callback_args_t * p_args)
{
    rm_comms_spi_instance_ctrl_t * p_ctrl = (rm_comms_spi_instance_ctrl_t *) (p_args->p_context);

#if BSP_CFG_RTOS
    rm_comms_spi_bus_extended_cfg_t const * p_bus = p_ctrl->p_bus;
    if (NULL != p_bus->p_semaphore)
    {
        rm_comms_semaphore_release(p_bus->p_semaphore);
    }
#endif

    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        rm_comms_spi_notify_application(p_ctrl, RM_COMMS_EVENT_OPERATION_COMPLETE);
    }
    else
    {
        rm_comms_spi_notify_application(p_ctrl, RM_COMMS_EVENT_ERROR);
    }
}
