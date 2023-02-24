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

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "rm_ob1203.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
fsp_err_t rm_ob1203_delay_ms(rm_ob1203_ctrl_t * const p_ctrl, uint32_t const delay_ms);
fsp_err_t rm_ob1203_irq_open(rm_ob1203_ctrl_t * const p_api_ctrl);
fsp_err_t rm_ob1203_irq_close(rm_ob1203_ctrl_t * const p_api_ctrl);
void      rm_ob1203_irq_callback(external_irq_callback_args_t * p_args);

#if BSP_CFG_RTOS
fsp_err_t rm_ob1203_os_semaphore_create(rm_ob1203_semaphore_t const * p_semaphore);
fsp_err_t rm_ob1203_os_semaphore_delete(rm_ob1203_semaphore_t const * p_semaphore);
fsp_err_t rm_ob1203_os_semaphore_acquire(rm_ob1203_semaphore_t const * p_semaphore, uint32_t const timeout);
fsp_err_t rm_ob1203_os_semaphore_release_from_ISR(rm_ob1203_semaphore_t const * p_semaphore);

#endif

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Delay some milliseconds.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_delay_ms (rm_ob1203_ctrl_t * const p_ctrl, uint32_t const delay_ms)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Software delay */
    R_BSP_SoftwareDelay(delay_ms, BSP_DELAY_UNITS_MILLISECONDS);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Open IRQ driver and set callback function.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_irq_open (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl         = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    external_irq_instance_t   * p_irq_instance = (external_irq_instance_t *) p_ctrl->p_irq_instance;

    /* Open IRQ driver */
    err = p_irq_instance->p_api->open(p_irq_instance->p_ctrl, p_irq_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set callback function and current control block */
    err = p_irq_instance->p_api->callbackSet(p_irq_instance->p_ctrl, rm_ob1203_irq_callback, p_ctrl, NULL);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Enable IRQ */
    err = p_irq_instance->p_api->enable(p_irq_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Close IRQ driver.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_irq_close (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    rm_ob1203_instance_ctrl_t * p_ctrl         = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    external_irq_instance_t   * p_irq_instance = (external_irq_instance_t *) p_ctrl->p_irq_instance;

    /* Close IRQ driver */
    p_irq_instance->p_api->close(p_irq_instance->p_ctrl);

    return FSP_SUCCESS;
}

void rm_ob1203_irq_callback (external_irq_callback_args_t * p_args)
{
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_args->p_context;
    rm_ob1203_callback_args_t   ob1203_callback_args;

    /* Set context */
    ob1203_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_ctrl->p_mode->mode_irq)
    {
        case RM_OB1203_OPERATION_MODE_LIGHT:
        {
            ob1203_callback_args.event = RM_OB1203_EVENT_THRESHOLD_CROSSED;
            break;
        }

        case RM_OB1203_OPERATION_MODE_PROXIMITY:
        {
            if (RM_OB1203_PROX_INTERRUPT_TYPE_LOGIC == p_ctrl->p_mode->prox_interrupt_type)
            {
                ob1203_callback_args.event = RM_OB1203_EVENT_OBJECT_NEAR;
            }
            else
            {
                /* RM_OB1203_PROX_INTERRUPT_TYPE_NORMAL */
                ob1203_callback_args.event = RM_OB1203_EVENT_THRESHOLD_CROSSED;
            }

            break;
        }

        case RM_OB1203_OPERATION_MODE_PPG:
        {
            ob1203_callback_args.event = RM_OB1203_EVENT_MEASUREMENT_COMPLETE;
            break;
        }

        default:
        {
            ob1203_callback_args.event = RM_OB1203_EVENT_ERROR;
            break;
        }
    }

    if (NULL != p_ctrl->p_irq_callback)
    {
        /* Call callback function */
        p_ctrl->p_irq_callback(&ob1203_callback_args);
    }
}

#if BSP_CFG_RTOS

/**********************************************************************************************************************
 * @brief Create a mutex.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 *********************************************************************************************************************/
fsp_err_t rm_ob1203_os_semaphore_create (rm_ob1203_semaphore_t const * p_semaphore)
{
 #if BSP_CFG_RTOS == 1                 // AzureOS
    UINT status;
    status = tx_semaphore_create(p_semaphore->p_semaphore_handle, p_semaphore->p_semaphore_name, (ULONG) 0);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    *(p_semaphore->p_semaphore_handle) =
        xSemaphoreCreateCountingStatic((UBaseType_t) 1, (UBaseType_t) 0, p_semaphore->p_semaphore_memory);
 #endif

    return FSP_SUCCESS;
}

/**********************************************************************************************************************
 * @brief Create a mutex.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 *********************************************************************************************************************/
fsp_err_t rm_ob1203_os_semaphore_delete (rm_ob1203_semaphore_t const * p_semaphore)
{
 #if BSP_CFG_RTOS == 1                 // AzureOS
    UINT status;
    status = tx_semaphore_delete(p_semaphore->p_semaphore_handle);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    vSemaphoreDelete(*(p_semaphore->p_semaphore_handle));
 #endif

    return FSP_SUCCESS;
}

/**********************************************************************************************************************
 * @brief Acquire a semaphore.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 *********************************************************************************************************************/
fsp_err_t rm_ob1203_os_semaphore_acquire (rm_ob1203_semaphore_t const * p_semaphore, uint32_t const timeout)
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
fsp_err_t rm_ob1203_os_semaphore_release_from_ISR (rm_ob1203_semaphore_t const * p_semaphore)
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
