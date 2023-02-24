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
#include "rm_comms_i2c.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_comms_i2c_process_in_callback(rm_comms_ctrl_t * const          p_api_ctrl,
                                             rm_comms_callback_args_t * const p_args);
static fsp_err_t rm_comms_i2c_bus_reconfigure(rm_comms_ctrl_t * const p_api_ctrl);

#if BSP_CFG_RTOS
static fsp_err_t rm_comms_i2c_os_recursive_mutex_acquire(rm_comms_i2c_mutex_t const * p_mutex, uint32_t const timeout);
static fsp_err_t rm_comms_i2c_os_recursive_mutex_release(rm_comms_i2c_mutex_t const * p_mutex);
static fsp_err_t rm_comms_i2c_os_semaphore_acquire(rm_comms_i2c_semaphore_t const * p_semaphore,
                                                   uint32_t const                   timeout);
static fsp_err_t rm_comms_i2c_os_semaphore_release_from_ISR(rm_comms_i2c_semaphore_t const * p_semaphore);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_status_check(rm_comms_ctrl_t * const p_api_ctrl);
fsp_err_t rm_comms_i2c_bus_read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t rm_comms_i2c_bus_write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t rm_comms_i2c_bus_write_read(rm_comms_ctrl_t * const            p_api_ctrl,
                                      rm_comms_write_read_params_t const write_read_params);

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Checks if the I2C driver module is open.
 *
 * @retval FSP_SUCCESS                  successfully configured.
 * @retval FSP_ERR_COMMS_BUS_NOT_OPEN   I2C driver is not open.
 **********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_status_check (rm_comms_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_master_instance_t        * p_driver_instance = (i2c_master_instance_t *) p_ctrl->p_bus->p_driver_instance;
    i2c_master_status_t            status;

    /* Check if RA I2C driver has already been opened */
    err = p_driver_instance->p_api->statusGet(p_driver_instance->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(true == status.open, FSP_ERR_COMMS_BUS_NOT_OPEN);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read data from the device using the I2C driver module.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_read (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_master_instance_t        * p_driver_instance = (i2c_master_instance_t *) p_ctrl->p_bus->p_driver_instance;

    /* Reconfigure a bus */
    err = rm_comms_i2c_bus_reconfigure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear transfer data */
    p_ctrl->p_transfer_data     = NULL;
    p_ctrl->transfer_data_bytes = 0;

    /* Use RA I2C driver to read data */
    err = p_driver_instance->p_api->read(p_driver_instance->p_ctrl, p_dest, bytes, false);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS
    if (NULL != p_ctrl->p_bus->p_blocking_semaphore)
    {
        /* Acquire a semaphore for blocking */
        err = rm_comms_i2c_os_semaphore_acquire(p_ctrl->p_bus->p_blocking_semaphore, p_ctrl->p_cfg->semaphore_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_ctrl->p_bus->p_bus_recursive_mutex)
    {
        /* Release a mutex for bus */
        err = rm_comms_i2c_os_recursive_mutex_release(p_ctrl->p_bus->p_bus_recursive_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write data to the device using the I2C driver module.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_write (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_master_instance_t        * p_driver_instance = (i2c_master_instance_t *) p_ctrl->p_bus->p_driver_instance;

    /* Reconfigure a bus */
    err = rm_comms_i2c_bus_reconfigure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear transfer data */
    p_ctrl->p_transfer_data     = NULL;
    p_ctrl->transfer_data_bytes = 0;

    /* Use RA I2C driver to write data */
    err = p_driver_instance->p_api->write(p_driver_instance->p_ctrl, p_src, bytes, false);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS
    if (NULL != p_ctrl->p_bus->p_blocking_semaphore)
    {
        /* Acquire a semaphore for blocking */
        err = rm_comms_i2c_os_semaphore_acquire(p_ctrl->p_bus->p_blocking_semaphore, p_ctrl->p_cfg->semaphore_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_ctrl->p_bus->p_bus_recursive_mutex)
    {
        /* Release a mutex for bus */
        err = rm_comms_i2c_os_recursive_mutex_release(p_ctrl->p_bus->p_bus_recursive_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Writes to I2C bus, then reads with restart.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_write_read (rm_comms_ctrl_t * const            p_api_ctrl,
                                       rm_comms_write_read_params_t const write_read_params)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_master_instance_t        * p_driver_instance = (i2c_master_instance_t *) p_ctrl->p_bus->p_driver_instance;

    /* Reconfigure a bus */
    err = rm_comms_i2c_bus_reconfigure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set read data */
    p_ctrl->p_transfer_data     = write_read_params.p_dest;
    p_ctrl->transfer_data_bytes = write_read_params.dest_bytes;

    /* Use RA I2C driver to write data */
    err = p_driver_instance->p_api->write(p_driver_instance->p_ctrl,
                                          write_read_params.p_src,
                                          write_read_params.src_bytes,
                                          true);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS
    if (NULL != p_ctrl->p_bus->p_blocking_semaphore)
    {
        /* Acquire a semaphore for blocking */
        err = rm_comms_i2c_os_semaphore_acquire(p_ctrl->p_bus->p_blocking_semaphore, p_ctrl->p_cfg->semaphore_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_ctrl->p_bus->p_bus_recursive_mutex)
    {
        /* Release a mutex for bus */
        err = rm_comms_i2c_os_recursive_mutex_release(p_ctrl->p_bus->p_bus_recursive_mutex);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Common callback function called in the I2C driver callback function.
 **********************************************************************************************************************/
void rm_comms_i2c_callback (i2c_master_callback_args_t * p_args)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_args->p_context;
    i2c_master_instance_t        * p_driver_instance = (i2c_master_instance_t *) p_ctrl->p_bus->p_driver_instance;
    rm_comms_callback_args_t       comms_i2c_args;

    /* Set context */
    comms_i2c_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case I2C_MASTER_EVENT_RX_COMPLETE:
        {
            comms_i2c_args.event = RM_COMMS_EVENT_OPERATION_COMPLETE;
            break;
        }

        case I2C_MASTER_EVENT_TX_COMPLETE:
        {
            comms_i2c_args.event = RM_COMMS_EVENT_OPERATION_COMPLETE;
            break;
        }

        case I2C_MASTER_EVENT_ABORTED:
        default:
        {
            /* Safely abort RA I2C driver */
            p_driver_instance->p_api->abort(p_driver_instance->p_ctrl);
            comms_i2c_args.event = RM_COMMS_EVENT_ERROR;

            break;
        }
    }

    if ((NULL != p_ctrl->p_transfer_data) &&
        (RM_COMMS_EVENT_OPERATION_COMPLETE == comms_i2c_args.event))
    {
        /* Read data with restart */
        err = p_driver_instance->p_api->read(p_driver_instance->p_ctrl,
                                             p_ctrl->p_transfer_data,
                                             p_ctrl->transfer_data_bytes,
                                             false);

        /* Clear transfer data */
        p_ctrl->p_transfer_data     = NULL;
        p_ctrl->transfer_data_bytes = 0;

        if (FSP_SUCCESS != err)
        {
            /* Set event */
            comms_i2c_args.event = RM_COMMS_EVENT_ERROR;

            /* Release semaphore in OS and call user callback function */
            rm_comms_i2c_process_in_callback(p_ctrl, &comms_i2c_args);
        }
    }
    else
    {
        /* Release semaphore in OS and call user callback function */
        rm_comms_i2c_process_in_callback(p_ctrl, &comms_i2c_args);
    }
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal Communications Middleware I2C driver private function.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Process in callback function. Release semaphores in RTOS and call user callback.
 **********************************************************************************************************************/
static void rm_comms_i2c_process_in_callback (rm_comms_ctrl_t * const          p_api_ctrl,
                                              rm_comms_callback_args_t * const p_args)
{
    rm_comms_i2c_instance_ctrl_t * p_ctrl = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;

#if BSP_CFG_RTOS
    if (NULL != p_ctrl->p_bus->p_blocking_semaphore)
    {
        /* Release a semaphore for blocking */
        rm_comms_i2c_os_semaphore_release_from_ISR(p_ctrl->p_bus->p_blocking_semaphore);
    }
#endif

    if (NULL != p_ctrl->p_callback)
    {
        /* Call user callback */
        p_ctrl->p_callback(p_args);
    }
}

/*******************************************************************************************************************//**
 * @brief Reconfigure I2C bus.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
static fsp_err_t rm_comms_i2c_bus_reconfigure (rm_comms_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_master_instance_t        * p_driver_instance = (i2c_master_instance_t *) p_ctrl->p_bus->p_driver_instance;
    i2c_master_cfg_t             * p_lower_level_cfg = (i2c_master_cfg_t *) p_ctrl->p_lower_level_cfg;

#if BSP_CFG_RTOS
    if (NULL != p_ctrl->p_bus->p_bus_recursive_mutex)
    {
        /* Acquire a mutex */
        err = rm_comms_i2c_os_recursive_mutex_acquire(p_ctrl->p_bus->p_bus_recursive_mutex, p_ctrl->p_bus->bus_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    if (p_ctrl->p_bus->p_current_ctrl != p_ctrl)
    {
        /* Update a slave address */
        err = p_driver_instance->p_api->slaveAddressSet(p_driver_instance->p_ctrl,
                                                        p_lower_level_cfg->slave,
                                                        p_lower_level_cfg->addr_mode);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Update control block on bus */
        p_ctrl->p_bus->p_current_ctrl = (rm_comms_ctrl_t *) p_ctrl;

        /* Set callback function and current control block */
        err = p_driver_instance->p_api->callbackSet(p_driver_instance->p_ctrl,
                                                    (void (*)(i2c_master_callback_args_t *))rm_comms_i2c_callback,
                                                    p_ctrl,
                                                    NULL);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    return FSP_SUCCESS;
}

#if BSP_CFG_RTOS

/**********************************************************************************************************************
 * @brief Acquire a recursive mutex.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 *********************************************************************************************************************/
static fsp_err_t rm_comms_i2c_os_recursive_mutex_acquire (rm_comms_i2c_mutex_t const * p_mutex, uint32_t const timeout)
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status;
    status = tx_mutex_get(p_mutex->p_mutex_handle, (ULONG) timeout);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err;
    sem_err = xSemaphoreTakeRecursive(*(p_mutex->p_mutex_handle), (TickType_t) timeout);
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #endif

    return FSP_SUCCESS;
}

/**********************************************************************************************************************
 * @brief Release a recursive mutex.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 *********************************************************************************************************************/
static fsp_err_t rm_comms_i2c_os_recursive_mutex_release (rm_comms_i2c_mutex_t const * p_mutex)
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status;
    status = tx_mutex_put(p_mutex->p_mutex_handle);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err;
    sem_err = xSemaphoreGiveRecursive(*(p_mutex->p_mutex_handle));
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #endif

    return FSP_SUCCESS;
}

/**********************************************************************************************************************
 * @brief Acquire a semaphore.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 *********************************************************************************************************************/
static fsp_err_t rm_comms_i2c_os_semaphore_acquire (rm_comms_i2c_semaphore_t const * p_semaphore,
                                                    uint32_t const                   timeout)
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status;
    status = tx_semaphore_get(p_semaphore->p_semaphore_handle, (ULONG) timeout);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err;
    sem_err = xSemaphoreTake(*(p_semaphore->p_semaphore_handle), (TickType_t) timeout);
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #endif

    return FSP_SUCCESS;
}

/**********************************************************************************************************************
 * @brief Release a semaphore from an interrupt.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 *********************************************************************************************************************/
static fsp_err_t rm_comms_i2c_os_semaphore_release_from_ISR (rm_comms_i2c_semaphore_t const * p_semaphore)
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status;
    status = tx_semaphore_put(p_semaphore->p_semaphore_handle);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err;
    sem_err = xSemaphoreGiveFromISR(*(p_semaphore->p_semaphore_handle), NULL);
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #endif

    return FSP_SUCCESS;
}

#endif
