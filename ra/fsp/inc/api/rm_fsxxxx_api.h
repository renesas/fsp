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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup RM_FSXXXX_API FSXXXX Middleware Interface
 * @brief Interface for FSXXXX Middleware functions.
 *
 * @section RM_FSXXXX_API_Summary Summary
 * The FSXXXX interface provides FSXXXX functionality.
 *
 * The FSXXXX interface can be implemented by:
 * - @ref RM_FS2012
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
    void const      * p_context;
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
    void const                * p_context;                   ///< Pointer to the user-provided context.
    void const                * p_extend;                    ///< Pointer to extended configuration by instance of interface.
    void (* p_callback)(rm_fsxxxx_callback_args_t * p_args); ///< Pointer to callback function.
} rm_fsxxxx_cfg_t;

/** FSXXXX control block.  Allocate an instance specific control block to pass into the FSXXXX API calls.
 * @par Implemented as
 * - rm_fsxxxx_instance_ctrl_t
 */
typedef void rm_fsxxxx_ctrl_t;

/** FSXXXX APIs */
typedef struct st_rm_fsxxxx_api
{
    /** Open sensor.
     * @par Implemented as
     * - @ref RM_FS2012_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_fsxxxx_ctrl_t * const p_ctrl, rm_fsxxxx_cfg_t const * const p_cfg);

    /** Read ADC data from FSXXXX.
     * @par Implemented as
     * - @ref RM_FS2012_Read()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data structure.
     */
    fsp_err_t (* read)(rm_fsxxxx_ctrl_t * const p_ctrl, rm_fsxxxx_raw_data_t * const p_raw_data);

    /** Calculate flow values from ADC data.
     * @par Implemented as
     * - @ref RM_FS2012_DataCalculate()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data       Pointer to raw data.
     * @param[in]  p_fsxxxx_data    Pointer to FSXXXX data structure.
     */
    fsp_err_t (* dataCalculate)(rm_fsxxxx_ctrl_t * const p_ctrl, rm_fsxxxx_raw_data_t * const p_raw_data,
                                rm_fsxxxx_data_t * const p_fsxxxx_data);

    /** Close FSXXXX.
     * @par Implemented as
     * - @ref RM_FS2012_Close()
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
