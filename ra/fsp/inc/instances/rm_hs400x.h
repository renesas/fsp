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
 * @addtogroup RM_HS400X
 * @{
 **********************************************************************************************************************/

#ifndef RM_HS400X_H
#define RM_HS400X_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_hs400x_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_hs400x_rx_config.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include "r_hs400x_rl_config.h"
#else
 #include "rm_hs400x_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** HS400X initialization process block */
typedef struct st_rm_hs400x_init_process_params
{
    volatile bool              communication_finished; ///< Communication flag for blocking.
    volatile rm_hs400x_event_t event;                  ///< Callback event
} rm_hs400x_init_process_params_t;

/** HS400x Control Block */
typedef struct rm_hs400x_instance_ctrl
{
    uint32_t                        open;                          ///< Open flag
    rm_hs400x_cfg_t const         * p_cfg;                         ///< Pointer to HS400X Configuration
    rm_comms_instance_t const     * p_comms_i2c_instance;          ///< Pointer of I2C Communications Middleware instance structure
    void const                    * p_context;                     ///< Pointer to the user-provided context
    rm_hs400x_init_process_params_t init_process_params;           ///< For the initialization process.
    uint8_t       resolution_register;                             ///< Register for temperature and humidity measurement resolution settings
    uint8_t       periodic_measurement_register[2];                ///< Register for periodic measurement settings
    volatile bool periodic_measurement_stop;                       ///< Flag for stop of periodic measurement
    volatile bool no_hold_measurement_read;                        ///< Flag for data read of No-Hold measurement
    uint8_t       write_buf[18];                                   ///< Buffer for data write

    /* Pointer to callback and optional working memory */
    void (* p_comms_callback)(rm_hs400x_callback_args_t * p_args); ///< I2C Communications callback
} rm_hs400x_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_hs400x_api_t const g_hs400x_on_hs400x;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_HS400X_Open(rm_hs400x_ctrl_t * const p_api_ctrl, rm_hs400x_cfg_t const * const p_cfg);
fsp_err_t RM_HS400X_Close(rm_hs400x_ctrl_t * const p_api_ctrl);
fsp_err_t RM_HS400X_MeasurementStart(rm_hs400x_ctrl_t * const p_api_ctrl);
fsp_err_t RM_HS400X_MeasurementStop(rm_hs400x_ctrl_t * const p_api_ctrl);
fsp_err_t RM_HS400X_Read(rm_hs400x_ctrl_t * const p_api_ctrl, rm_hs400x_raw_data_t * const p_raw_data);
fsp_err_t RM_HS400X_DataCalculate(rm_hs400x_ctrl_t * const     p_api_ctrl,
                                  rm_hs400x_raw_data_t * const p_raw_data,
                                  rm_hs400x_data_t * const     p_hs400x_data);

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_HS400X_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_HS400X)
 **********************************************************************************************************************/
