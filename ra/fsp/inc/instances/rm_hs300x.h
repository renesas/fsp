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
 * @addtogroup RM_HS300X
 * @{
 **********************************************************************************************************************/

#ifndef RM_HS300X_H
#define RM_HS300X_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_hs300x_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_hs300x_rx_config.h"
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
 #include "r_hs300x_rl_config.h"
#else
 #include "rm_hs300x_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** HS300X programming mode process block */
typedef struct st_rm_hs300x_programmnig_mode_params
{
    volatile bool              enter;                  ///< Enter flag.
    volatile bool              blocking;               ///< Blocking flag.
    volatile bool              communication_finished; ///< Communication flag for blocking.
    volatile rm_hs300x_event_t event;                  ///< Callback event
} rm_hs300x_programmnig_mode_params_t;

/** HS300x Control Block */
typedef struct rm_hs300x_instance_ctrl
{
    uint32_t                            open;                 ///< Open flag
    rm_hs300x_cfg_t const             * p_cfg;                ///< Pointer to HS300X Configuration
    rm_comms_instance_t const         * p_comms_i2c_instance; ///< Pointer of I2C Communications Middleware instance structure
    void const                        * p_context;            ///< Pointer to the user-provided context
    rm_hs300x_programmnig_mode_params_t programming_mode;     ///< Programming mode flag
    uint8_t buf[3];                                           ///< Buffer for I2C communications

    /* Pointer to callback and optional working memory */
    void (* p_callback)(rm_hs300x_callback_args_t * p_args);
} rm_hs300x_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_hs300x_api_t const g_hs300x_on_hs300x;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_Open(rm_hs300x_ctrl_t * const p_api_ctrl, rm_hs300x_cfg_t const * const p_cfg);
fsp_err_t RM_HS300X_Close(rm_hs300x_ctrl_t * const p_api_ctrl);
fsp_err_t RM_HS300X_MeasurementStart(rm_hs300x_ctrl_t * const p_api_ctrl);
fsp_err_t RM_HS300X_Read(rm_hs300x_ctrl_t * const p_api_ctrl, rm_hs300x_raw_data_t * const p_raw_data);
fsp_err_t RM_HS300X_DataCalculate(rm_hs300x_ctrl_t * const     p_api_ctrl,
                                  rm_hs300x_raw_data_t * const p_raw_data,
                                  rm_hs300x_data_t * const     p_hs300x_data);
fsp_err_t RM_HS300X_ProgrammingModeEnter(rm_hs300x_ctrl_t * const p_api_ctrl);
fsp_err_t RM_HS300X_ResolutionChange(rm_hs300x_ctrl_t * const     p_api_ctrl,
                                     rm_hs300x_data_type_t const  data_type,
                                     rm_hs300x_resolution_t const resolution);
fsp_err_t RM_HS300X_SensorIdGet(rm_hs300x_ctrl_t * const p_api_ctrl, uint32_t * const p_sensor_id);
fsp_err_t RM_HS300X_ProgrammingModeExit(rm_hs300x_ctrl_t * const p_api_ctrl);

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_HS300X_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_HS300X)
 **********************************************************************************************************************/
