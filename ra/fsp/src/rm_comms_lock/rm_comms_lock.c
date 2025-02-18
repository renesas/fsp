/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "rm_comms_lock.h"

#if BSP_CFG_RTOS

/**********************************************************************************************************************
 * @brief Initialize a recursive mutex.
 *
 * @retval FSP_SUCCESS              successfully initialized.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_recursive_mutex_initialize (rm_comms_mutex_t * p_mutex)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1
    UINT status = tx_mutex_create(&p_mutex->handle, p_mutex->p_name, TX_INHERIT);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2
    p_mutex->handle = xSemaphoreCreateRecursiveMutexStatic(&p_mutex->buffer);
    FSP_ERROR_RETURN(p_mutex->handle != NULL, FSP_ERR_INTERNAL);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

/**********************************************************************************************************************
 * @brief Desctroy a recursive mutex.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_recursive_mutex_destroy (rm_comms_mutex_t * p_mutex)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1
    UINT status = tx_mutex_delete(&p_mutex->handle);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2
    vSemaphoreDelete(p_mutex->handle);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

/**********************************************************************************************************************
 * @brief Acquire a recursive mutex.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_recursive_mutex_acquire (rm_comms_mutex_t * p_mutex, uint32_t const timeout)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status = tx_mutex_get(&p_mutex->handle, (ULONG) timeout);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err = xSemaphoreTakeRecursive(p_mutex->handle, (TickType_t) timeout);
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

/**********************************************************************************************************************
 * @brief Release a recursive mutex.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_recursive_mutex_release (rm_comms_mutex_t * p_mutex)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status = tx_mutex_put(&p_mutex->handle);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err = xSemaphoreGiveRecursive(p_mutex->handle);
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

/**********************************************************************************************************************
 * @brief Initialize a semaphore.
 *
 * @retval FSP_SUCCESS              successfully initialized.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_semaphore_initialize (rm_comms_semaphore_t * p_semaphore)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1
    UINT status = tx_semaphore_create(&p_semaphore->handle, p_semaphore->p_name, (ULONG) 0);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2
    p_semaphore->handle = xSemaphoreCreateCountingStatic((UBaseType_t) 1, (UBaseType_t) 0, &p_semaphore->buffer);
    FSP_ERROR_RETURN(p_semaphore->handle != NULL, FSP_ERR_INTERNAL);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

/**********************************************************************************************************************
 * @brief Desctroy a semaphore.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_semaphore_destroy (rm_comms_semaphore_t * p_semaphore)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1
    UINT status = tx_semaphore_delete(&p_semaphore->handle);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2
    vSemaphoreDelete(p_semaphore->handle);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

/**********************************************************************************************************************
 * @brief Acquire a semaphore.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_semaphore_acquire (rm_comms_semaphore_t * p_semaphore, uint32_t const timeout)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status = tx_semaphore_get(&p_semaphore->handle, (ULONG) timeout);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err = xSemaphoreTake(p_semaphore->handle, (TickType_t) timeout);
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

/**********************************************************************************************************************
 * @brief Release a semaphore.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_semaphore_release (rm_comms_semaphore_t * p_semaphore)
{
    fsp_err_t ret = FSP_SUCCESS;

 #if BSP_CFG_RTOS == 1                 // ThreadX
    UINT status = tx_semaphore_put(&p_semaphore->handle);
    FSP_ERROR_RETURN(TX_SUCCESS == status, FSP_ERR_INTERNAL);
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    BaseType_t sem_err = xSemaphoreGiveFromISR(p_semaphore->handle, NULL);
    FSP_ERROR_RETURN(pdTRUE == sem_err, FSP_ERR_INTERNAL);
 #else
    ret = FSP_ERR_UNSUPPORTED;
 #endif

    return ret;
}

#endif
