/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_COMMS_LOCK_H
#define RM_COMMS_LOCK_H

#include "bsp_api.h"

#if BSP_CFG_RTOS

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

 #if BSP_CFG_RTOS == 1                 // ThreadX
  #include    "tx_api.h"
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
  #include    "FreeRTOS.h"
  #include    "task.h"
  #include    "queue.h"
  #include    "semphr.h"
 #else
 #endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Mutex structure */
typedef struct st_rm_comms_mutex
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    TX_MUTEX handle;
    CHAR   * p_name;
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    SemaphoreHandle_t handle;
    StaticSemaphore_t buffer;
 #else
 #endif
} rm_comms_mutex_t;

/* Semaphore Structure */
typedef struct st_rm_comms_semaphore
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    TX_SEMAPHORE handle;
    CHAR       * p_name;
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    SemaphoreHandle_t handle;
    StaticSemaphore_t buffer;
 #else
 #endif
} rm_comms_semaphore_t;

/**********************************************************************************************************************
 * @brief rm_comms_lock API
 *
 * @retval FSP_SUCCESS              Function call succeeds.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_recursive_mutex_initialize(rm_comms_mutex_t * p_mutex);
fsp_err_t rm_comms_recursive_mutex_destroy(rm_comms_mutex_t * p_mutex);
fsp_err_t rm_comms_recursive_mutex_acquire(rm_comms_mutex_t * p_mutex, uint32_t const timeout);
fsp_err_t rm_comms_recursive_mutex_release(rm_comms_mutex_t * p_mutex);

fsp_err_t rm_comms_semaphore_initialize(rm_comms_semaphore_t * p_semaphore);
fsp_err_t rm_comms_semaphore_destroy(rm_comms_semaphore_t * p_semaphore);
fsp_err_t rm_comms_semaphore_acquire(rm_comms_semaphore_t * p_semaphore, uint32_t const timeout);
fsp_err_t rm_comms_semaphore_release(rm_comms_semaphore_t * p_semaphore);

#endif                                 /* RM_COMMS_LOCK_H */

#endif
