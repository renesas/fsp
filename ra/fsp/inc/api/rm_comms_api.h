/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup RM_COMMS_API Communicatons Middleware Interface
 * @brief Interface for Communications Middleware functions.
 *
 * @section RM_COMMS_API_Summary Summary
 * The Communications interface provides multiple communications functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_API_H_
#define RM_COMMS_API_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "platform.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include <stddef.h>
 #include <stdbool.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
 #include "bsp_api.h"
#endif

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event in the callback function */
typedef enum e_rm_comms_event
{
    RM_COMMS_EVENT_OPERATION_COMPLETE = 0,
    RM_COMMS_EVENT_TX_OPERATION_COMPLETE,
    RM_COMMS_EVENT_RX_OPERATION_COMPLETE,
    RM_COMMS_EVENT_ERROR,
} rm_comms_event_t;

/** Struct to pack params for writeRead */
typedef struct st_rm_comms_write_read_params
{
    uint8_t * p_src;
    uint8_t * p_dest;
    uint8_t   src_bytes;
    uint8_t   dest_bytes;
} rm_comms_write_read_params_t;

/** Communications middleware callback parameter definition */
typedef struct st_rm_comms_callback_args
{
    void const     * p_context;
    rm_comms_event_t event;
} rm_comms_callback_args_t;

/** Communications middleware configuration block */
typedef struct st_rm_comms_cfg
{
    uint32_t semaphore_timeout;                             ///< Timeout for read/write.

    void const * p_extend;                                  ///< Pointer to extended configuration by instance of interface.
    void const * p_lower_level_cfg;                         ///< Pointer to lower level driver configuration structure.

    void const * p_context;                                 ///< Pointer to the user-provided context
    void (* p_callback)(rm_comms_callback_args_t * p_args); ///< Pointer to callback function, mostly used if using non-blocking functionality.
} rm_comms_cfg_t;

/** Communications control block.  Allocate an instance specific control block to pass into the Communications API calls.
 */
typedef void rm_comms_ctrl_t;

/** COMM APIs */
typedef struct st_rm_comms_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  p_cfg    Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_comms_ctrl_t * const p_ctrl, rm_comms_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_comms_ctrl_t * const p_ctrl);

    /** Read data.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in] 　p_dest   Pointer to the location to store read data.
     * @param[in] 　bytes    Number of bytes to read.
     */
    fsp_err_t (* read)(rm_comms_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes);

    /** Write data.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  p_src    Pointer to the location to get write data from.
     * @param[in]  bytes    Number of bytes to write.
     */
    fsp_err_t (* write)(rm_comms_ctrl_t * const p_ctrl, uint8_t * const p_src, uint32_t const bytes);

    /** Write bytes over comms followed by a read, will have a struct for params.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  write_read_params    Parameters structure.
     */
    fsp_err_t (* writeRead)(rm_comms_ctrl_t * const p_ctrl, rm_comms_write_read_params_t write_read_params);

    /**
     * Specify callback function and optional context pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     */
    fsp_err_t (* callbackSet)(rm_comms_ctrl_t * const p_ctrl, void (* p_callback)(rm_comms_callback_args_t *),
                              void const * const p_context);
} rm_comms_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_comms_instance
{
    rm_comms_ctrl_t      * p_ctrl;
    rm_comms_cfg_t const * p_cfg;
    rm_comms_api_t const * p_api;
} rm_comms_instance_t;

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_COMMS_API_H_ */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_API)
 **********************************************************************************************************************/
