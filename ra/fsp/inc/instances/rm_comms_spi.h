/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_SPI
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_SPI_H
#define RM_COMMS_SPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_api.h"
#include "rm_comms_api.h"
#include "rm_comms_spi_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* SPI bus configuration */
typedef struct st_rm_comms_spi_bus_extended_cfg
{
    rm_comms_ctrl_t * p_current_ctrl;  ///< Current device using the SPI bus
#if BSP_CFG_RTOS
    void * const   p_semaphore;        ///< Block read/write operations. If this is NULL then operations will be non-blocking and require a callback.
    void * const   p_mutex;            ///< Lock SPI bus for read/write operation.
    uint32_t const mutex_timeout;      ///< Timeout for locking operation.
    bool           initialized;        ///< Whether mutex and semaphore are initialized
#endif
} rm_comms_spi_bus_extended_cfg_t;

/* SPI device configuration */
typedef struct st_rm_comms_spi_device_extended_cfg
{
    spi_instance_t const * p_driver_instance; ///< Pointer to SPI HAL interface to be used in the framework
    uint32_t               ssl_delay;         ///< SSL next access delay (Microseconds)
    bsp_io_port_pin_t      ssl_pin;           ///< Select which slave to use
    bsp_io_level_t         ssl_level;         ///< SSL active level
} rm_comms_spi_device_extended_cfg_t;

/** Communications middleware control structure. */
typedef struct st_rm_comms_spi_instance_ctrl
{
    uint32_t                             open;              ///< Open flag
    rm_comms_cfg_t const               * p_cfg;             ///< Middleware configuration
    rm_comms_spi_bus_extended_cfg_t    * p_bus;             ///< Pointer to extended configuration structure
    rm_comms_spi_device_extended_cfg_t * p_device;          ///< Pointer to device specific settings (lower level configuration structure)
    void (* p_callback)(rm_comms_callback_args_t * p_args); ///< Pointer to callback that is called when a spi_event_t occurs
    void * p_context;                                       ///< Pointer to context passed into callback function
} rm_comms_spi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern rm_comms_api_t const g_comms_on_comms_spi;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SPI_Open(rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg);
fsp_err_t RM_COMMS_SPI_Close(rm_comms_ctrl_t * const p_api_ctrl);
fsp_err_t RM_COMMS_SPI_Read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t RM_COMMS_SPI_Write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t RM_COMMS_SPI_WriteRead(rm_comms_ctrl_t * const            p_api_ctrl,
                                 rm_comms_write_read_params_t const write_read_params);
fsp_err_t RM_COMMS_SPI_CallbackSet(rm_comms_ctrl_t * const p_api_ctrl,
                                   void (                * p_callback)(rm_comms_callback_args_t *),
                                   void * const            p_context);
void rm_comms_spi_callback(spi_callback_args_t * p_args);

FSP_FOOTER

#endif                                 /* RM_COMMS_SPI_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_SPI)
 **********************************************************************************************************************/
