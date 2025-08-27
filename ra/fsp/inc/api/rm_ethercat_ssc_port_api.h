/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_NETWORKING_INTERFACES
 * @defgroup ETHERCAT_SSC_PORT_API EtherCAT SSC Interface
 * @brief Interface for EtherCAT SSC functions.
 *
 * @section ETHERCAT_SSC_PORT_API_SUMMARY Summary
 * The EtherCAT SSC port module (rm_ethercat_ssc_port) provides an API for EtherCAT Slave Stack Code that use
 * the EtherCAT Slave Controler peripheral.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_ETHERCAT_SSC_PORT_API_H
#define RM_ETHERCAT_SSC_PORT_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event code of callback function */
typedef enum e_ethercat_ssc_port_event
{
    ETHERCAT_SSC_PORT_EVENT_ESC_CAT_INTERRUPT,   ///< EtherCAT Interrupt event
    ETHERCAT_SSC_PORT_EVENT_ESC_SYNC0_INTERRUPT, ///< EtherCAT Sync0 Interrupt event
    ETHERCAT_SSC_PORT_EVENT_ESC_SYNC1_INTERRUPT, ///< EtherCAT Sync1 Interrupt event
} ethercat_ssc_port_event_t;

/** Callback function parameter data */
typedef struct st_ethercat_ssc_port_callback_args
{
    ethercat_ssc_port_event_t event;   ///< Event code
    void * p_context;                  ///< Placeholder for user data.  Set in @ref ethercat_ssc_port_api_t::open function in @ref ethercat_ssc_port_cfg_t.
} ethercat_ssc_port_callback_args_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls. */
typedef void ethercat_ssc_port_ctrl_t;

/** Configuration parameters. */
typedef struct st_ethercat_ssc_port_cfg
{
    uint32_t reset_hold_time;                                        ///< PHY Reset signal hold time (ms)
    uint32_t reset_wait_time;                                        ///< Wait time after PHY reset relase (us)
    uint32_t address_offset;                                         ///< Offset of the PHY address

    IRQn_Type common_irq;                                            ///< EtherCAT IRQ interrupt number
    uint8_t   common_ipl;                                            ///< EtherCAT interrupt priority

    IRQn_Type sync0_irq;                                             ///< EtherCAT Sync0 IRQ interrupt number
    uint8_t   sync0_ipl;                                             ///< EtherCAT Sync0 interrupt priority

    IRQn_Type sync1_irq;                                             ///< EtherCAT Sync1 IRQ interrupt number
    uint8_t   sync1_ipl;                                             ///< EtherCAT Sync1 interrupt priority

    void (* p_callback)(ethercat_ssc_port_callback_args_t * p_args); ///< Callback provided when an ISR occurs.

    timer_instance_t const * p_timer_instance;                       ///< Pointer to Timer instance

    /** Placeholder for user data.  Passed to the user callback in ethercat_ssc_port_callback_args_t. */
    void       * p_context;
    void const * p_extend;                                           ///< Placeholder for user extension.
} ethercat_ssc_port_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ethercat_ssc_port_api
{
    /** Open driver.
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     * @param[in]  p_cfg            Pointer to EtherCAT SSC port configuration structure.
     */
    fsp_err_t (* open)(ethercat_ssc_port_ctrl_t * const p_api_ctrl, ethercat_ssc_port_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_api_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ethercat_ssc_port_ctrl_t * const p_api_ctrl);
} ethercat_ssc_port_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ethercat_ssc_port_instance
{
    ethercat_ssc_port_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    ethercat_ssc_port_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    ethercat_ssc_port_api_t const * p_api;  ///< Pointer to the API structure for this instance
} ethercat_ssc_port_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHERCAT_SSC_PORT_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_ETHERCAT_SSC_PORT_API_H */
