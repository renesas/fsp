/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_I2C_SLAVE_API_H
#define R_I2C_SLAVE_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup I2C_SLAVE_API I2C Slave Interface
 * @brief Interface for I2C slave communication.
 *
 * @section I2C_SLAVE_API_SUMMARY Summary
 * The I2C slave interface provides a common API for I2C HAL drivers. The I2C slave interface supports:
 *        - Interrupt driven transmit/receive processing
 *        - Callback function support which returns a event codes
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Communication speed options */
typedef enum e_i2c_slave_rate
{
    I2C_SLAVE_RATE_STANDARD = 100000,  ///< 100 kHz
    I2C_SLAVE_RATE_FAST     = 400000,  ///< 400 kHz
    I2C_SLAVE_RATE_FASTPLUS = 1000000  ///< 1 MHz
} i2c_slave_rate_t;

/** Addressing mode options */
typedef enum e_i2c_slave_addr_mode
{
    I2C_SLAVE_ADDR_MODE_7BIT = 1,      ///< Use 7-bit addressing mode
    I2C_SLAVE_ADDR_MODE_10BIT          ///< Use 10-bit addressing mode
} i2c_slave_addr_mode_t;

/** Callback events */
typedef enum e_i2c_slave_event
{
    I2C_SLAVE_EVENT_ABORTED         = 1, ///< A transfer was aborted
    I2C_SLAVE_EVENT_RX_COMPLETE     = 2, ///< A receive operation was completed successfully
    I2C_SLAVE_EVENT_TX_COMPLETE     = 3, ///< A transmit operation was completed successfully
    I2C_SLAVE_EVENT_RX_REQUEST      = 4, ///< A read operation expected from slave. Detected a write from master
    I2C_SLAVE_EVENT_TX_REQUEST      = 5, ///< A write operation expected from slave. Detected a read from master
    I2C_SLAVE_EVENT_RX_MORE_REQUEST = 6, ///< A read operation expected from slave. Master sends out more data than configured to be read in slave.
    I2C_SLAVE_EVENT_TX_MORE_REQUEST = 7, ///< A write operation expected from slave. Master requests more data than configured to be written by slave.
    I2C_SLAVE_EVENT_GENERAL_CALL    = 8, ///< General Call address received from Master. Detected a write from master
} i2c_slave_event_t;

/** I2C callback parameter definition */
typedef struct st_i2c_slave_callback_args
{
    void const      * p_context;       ///< Pointer to user-provided context
    uint32_t          bytes;           ///< Number of received/transmitted bytes in buffer
    i2c_slave_event_t event;           ///< Event code
} i2c_slave_callback_args_t;

/** I2C configuration block */
typedef struct st_i2c_slave_cfg
{
    /** Generic configuration */
    uint8_t               channel;                           ///< Identifier recognizable by implementation
    i2c_slave_rate_t      rate;                              ///< Device's maximum clock rate from enum i2c_rate_t
    uint16_t              slave;                             ///< The address of the slave device
    i2c_slave_addr_mode_t addr_mode;                         ///< Indicates how slave fields should be interpreted
    bool general_call_enable;                                ///< Allow a General call from master

    IRQn_Type rxi_irq;                                       ///< Receive IRQ number
    IRQn_Type txi_irq;                                       ///< Transmit IRQ number
    IRQn_Type tei_irq;                                       ///< Transmit end IRQ number
    IRQn_Type eri_irq;                                       ///< Error IRQ number
    uint8_t   ipl;                                           ///< Interrupt priority level for receive, transmit, and transmit end interrupts
    uint8_t   eri_ipl;                                       ///< Interrupt priority level for error interrupt
    bool      clock_stretching_enable;                       ///< Low Hold SCL during reception for the period between the 9th and the 1st clock cycle

    /** DTC support */
    transfer_instance_t const * p_transfer_tx;               ///< DTC instance for I2C transmit.Set to NULL if unused.
    transfer_instance_t const * p_transfer_rx;               ///< DTC instance for I2C receive. Set to NULL if unused.

    /** Parameters to control software behavior */
    void (* p_callback)(i2c_slave_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                                  ///< Pointer to the user-provided context

    /** Implementation-specific configuration */
    void const * p_extend;                                   ///< Any configuration data needed by the hardware
} i2c_slave_cfg_t;

/** I2C control block.  Allocate an instance specific control block to pass into the I2C API calls.
 */
typedef void i2c_slave_ctrl_t;

/** Interface definition for I2C access as slave */
typedef struct st_i2c_slave_api
{
    /** Opens the I2C Slave driver and initializes the hardware.
     *
     * @param[in] p_ctrl    Pointer to control block. Must be declared by user. Elements are set here.
     * @param[in] p_cfg     Pointer to configuration structure.
     */
    fsp_err_t (* open)(i2c_slave_ctrl_t * const p_ctrl, i2c_slave_cfg_t const * const p_cfg);

    /** Performs a read operation on an I2C Slave device.
     *
     * @param[in] p_ctrl    Pointer to control block set in @ref i2c_slave_api_t::open call.
     * @param[in] p_dest    Pointer to the location to store read data.
     * @param[in] bytes     Number of bytes to read.
     */
    fsp_err_t (* read)(i2c_slave_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes);

    /** Performs a write operation on an I2C Slave device.
     *
     * @param[in] p_ctrl    Pointer to control block set in @ref i2c_slave_api_t::open call.
     * @param[in] p_src     Pointer to the location to get write data from.
     * @param[in] bytes     Number of bytes to write.
     */
    fsp_err_t (* write)(i2c_slave_ctrl_t * const p_ctrl, uint8_t * const p_src, uint32_t const bytes);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the IIC Slave control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(i2c_slave_ctrl_t * const p_ctrl, void (* p_callback)(i2c_slave_callback_args_t *),
                              void const * const p_context, i2c_slave_callback_args_t * const p_callback_memory);

    /** Closes the driver and releases the I2C Slave device.
     *
     * @param[in] p_ctrl    Pointer to control block set in @ref i2c_slave_api_t::open call.
     */
    fsp_err_t (* close)(i2c_slave_ctrl_t * const p_ctrl);
} i2c_slave_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_i2c_slave_instance
{
    i2c_slave_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    i2c_slave_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    i2c_slave_api_t const * p_api;     ///< Pointer to the API structure for this instance
} i2c_slave_instance_t;

/******************************************************************************************************************//**
 * @} (end defgroup I2C_SLAVE_API)
 *********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
