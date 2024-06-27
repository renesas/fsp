/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_I2C
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_I2C_H
#define RM_COMMS_I2C_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_comms_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_comms_i2c_rx_config.h"
 #if BSP_CFG_RTOS_USED == 1            // FreeRTOS
  #include    "FreeRTOS.h"
  #include    "task.h"
  #include    "queue.h"
  #include    "semphr.h"
  #define BSP_CFG_RTOS    2
 #elif BSP_CFG_RTOS_USED == 5          // ThreadX
  #define BSP_CFG_RTOS    1
 #else
  #define BSP_CFG_RTOS    0
 #endif
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include "r_comms_i2c_rl_config.h"
#else
 #include "r_i2c_master_api.h"
 #include "rm_comms_i2c_cfg.h"
 #if BSP_CFG_RTOS == 1                 // ThreadX
  #include    "tx_api.h"
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
  #include    "FreeRTOS.h"
  #include    "task.h"
  #include    "queue.h"
  #include    "semphr.h"
 #endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if BSP_CFG_RTOS

/* Mutex structure */
typedef struct st_rm_comms_i2c_mutex
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    TX_MUTEX * p_mutex_handle;
    CHAR     * p_mutex_name;
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    SemaphoreHandle_t * p_mutex_handle;
    StaticSemaphore_t * p_mutex_memory;
 #else
 #endif
} rm_comms_i2c_mutex_t;

/* Semaphore Structure */
typedef struct st_rm_comms_i2c_semaphore
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    TX_SEMAPHORE * p_semaphore_handle;
    CHAR         * p_semaphore_name;
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    SemaphoreHandle_t * p_semaphore_handle;
    StaticSemaphore_t * p_semaphore_memory;
 #else
 #endif
} rm_comms_i2c_semaphore_t;
#endif

/* I2C bus configuration */
typedef struct st_rm_comms_i2c_bus_extended_cfg
{
#if BSP_CFG_RTOS
    rm_comms_i2c_mutex_t const     * p_bus_recursive_mutex; ///< The mutex for the bus. If this is NULL then operations will not lock the bus while it is in use.
    rm_comms_i2c_semaphore_t const * p_blocking_semaphore;  ///< The semaphore for blocking operations. If this is NULL then operations will be non-blocking and require a callback.
#endif
    uint32_t          bus_timeout;                          ///< Possible in ticks.
    rm_comms_ctrl_t * p_current_ctrl;                       ///< Current device using the bus (by switching the address)
    void const      * p_driver_instance;                    ///< Pointer to I2C HAL interface to be used in the framework

    void const * p_elc;                                     ///< Pointer to ELC instance.
    void const * p_timer;                                   ///< Pointer to GPT instance.
} rm_comms_i2c_bus_extended_cfg_t;

/** Communications middleware control structure. */
typedef struct st_rm_comms_i2c_instance_ctrl
{
    rm_comms_cfg_t const            * p_cfg; ///< middleware configuration.
    rm_comms_i2c_bus_extended_cfg_t * p_bus; ///< Bus using this device;
    void    * p_lower_level_cfg;             ///< Used to reconfigure I2C driver
    uint32_t  open;                          ///< Open flag.
    uint32_t  transfer_data_bytes;           ///< Size of transfer data.
    uint8_t * p_transfer_data;               ///< Pointer to transfer data buffer.

    /* Specific control variable for SMBus */
    bool smbus_operation;                    ///< SMBus operation on I2C bus

    /* Pointer to callback and optional working memory */
    void (* p_callback)(rm_comms_callback_args_t * p_args);

    void const * p_context;            ///< Pointer to the user-provided context
} rm_comms_i2c_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_comms_api_t const g_comms_on_comms_i2c;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_I2C_Open(rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg);
fsp_err_t RM_COMMS_I2C_Close(rm_comms_ctrl_t * const p_api_ctrl);
fsp_err_t RM_COMMS_I2C_Read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t RM_COMMS_I2C_Write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t RM_COMMS_I2C_WriteRead(rm_comms_ctrl_t * const            p_api_ctrl,
                                 rm_comms_write_read_params_t const write_read_params);

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
void rm_comms_i2c_callback(rm_comms_ctrl_t const * p_api_ctrl);

#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
void rm_comms_i2c_callback(rm_comms_ctrl_t const * p_api_ctrl, bool aborted);

#else
void rm_comms_i2c_callback(i2c_master_callback_args_t * p_args);

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_COMM_I2C_BUS_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup COMM_I2C_BUS)
 **********************************************************************************************************************/
