/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SENSOR_INTERFACES
 * @defgroup RM_FSXXXX_API FSXXXX Middleware Interface
 * @brief Interface for FSXXXX Middleware functions.
 *
 * @section RM_FSXXXX_API_Summary Summary
 * The FSXXXX interface provides FSXXXX functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_FSXXXX_API_H_
#define RM_FSXXXX_API_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include <string.h>
 #include "platform.h"
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
 #include <string.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
 #include "bsp_api.h"
#endif

#include "rm_comms_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event in the callback function */
typedef enum e_rm_fsxxxx_event
{
    RM_FSXXXX_EVENT_SUCCESS = 0,
    RM_FSXXXX_EVENT_ERROR,
} rm_fsxxxx_event_t;

/** FSXXXX callback parameter definition */
typedef struct st_rm_fsxxxx_callback_args
{
    void            * p_context;
    rm_fsxxxx_event_t event;
} rm_fsxxxx_callback_args_t;

/** FSXXXX raw data */
typedef struct st_rm_fsxxxx_raw_data
{
    uint8_t adc_data[5];
} rm_fsxxxx_raw_data_t;

/** FSXXXX sensor data block */
typedef struct st_rm_fsxxxx_sensor_data
{
    int16_t integer_part;
    int16_t decimal_part;              ///< To two decimal places
} rm_fsxxxx_sensor_data_t;

/** FSXXXX data block */
typedef struct st_rm_fsxxxx_data
{
    rm_fsxxxx_sensor_data_t flow;
    uint32_t                count;
} rm_fsxxxx_data_t;

/** FSXXXX Configuration */
typedef struct st_rm_fsxxxx_cfg
{
    rm_comms_instance_t const * p_instance;                  ///< Pointer to Communications Middleware instance.
    void       * p_context;                                  ///< Pointer to the user-provided context.
    void const * p_extend;                                   ///< Pointer to extended configuration by instance of interface.
    void (* p_callback)(rm_fsxxxx_callback_args_t * p_args); ///< Pointer to callback function.
} rm_fsxxxx_cfg_t;

/** FSXXXX control block.  Allocate an instance specific control block to pass into the FSXXXX API calls.
 */
typedef void rm_fsxxxx_ctrl_t;

/** FSXXXX APIs */
typedef struct st_rm_fsxxxx_api
{
    /** Open sensor.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_fsxxxx_ctrl_t * const p_ctrl, rm_fsxxxx_cfg_t const * const p_cfg);

    /** Read ADC data from FSXXXX.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     */
    fsp_err_t (* read)(rm_fsxxxx_ctrl_t * const p_ctrl, rm_fsxxxx_raw_data_t * const p_raw_data);

    /** Calculate flow values from ADC data.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data.
     * @param[in]  p_fsxxxx_data    Pointer to FSXXXX data structure.
     */
    fsp_err_t (* dataCalculate)(rm_fsxxxx_ctrl_t * const p_ctrl, rm_fsxxxx_raw_data_t * const p_raw_data,
                                rm_fsxxxx_data_t * const p_fsxxxx_data);

    /** Close FSXXXX.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_fsxxxx_ctrl_t * const p_ctrl);
} rm_fsxxxx_api_t;

/** FSXXXX instance */
typedef struct st_rm_fsxxxx_instance
{
    rm_fsxxxx_ctrl_t      * p_ctrl;    /**< Pointer to the control structure for this instance */
    rm_fsxxxx_cfg_t const * p_cfg;     /**< Pointer to the configuration structure for this instance */
    rm_fsxxxx_api_t const * p_api;     /**< Pointer to the API structure for this instance */
} rm_fsxxxx_instance_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_FSXXXX_API_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_FSXXXX_API)
 **********************************************************************************************************************/
