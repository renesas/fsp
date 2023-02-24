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

#ifndef RM_VEE_API_H
#define RM_VEE_API_H

/*******************************************************************************************************************//**
 * @defgroup RM_VEE_API Virtual EEPROM Interface
 * @ingroup RENESAS_INTERFACES
 * @brief Interface for Virtual EEPROM access
 *
 * @section RM_VEE_API_SUMMARY Summary
 * The Virtual EEPROM Port configures a fail-safe key value store designed for microcontrollers on top of a lower
 * level storage device.
 *
 * Implemented by:
 * @ref RM_VEE_FLASH
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Current state of the Virtual EEPROM */
typedef enum e_rm_vee_state
{
    RM_VEE_STATE_READY,                ///< Ready
    RM_VEE_STATE_BUSY,                 ///< Operation in progress
    RM_VEE_STATE_REFRESH,              ///< Refresh operation in progress
    RM_VEE_STATE_OVERFLOW,             ///< The amount of data written exceeds the space available
    RM_VEE_STATE_HARDWARE_FAIL,        ///< Lower level hardware failure
} rm_vee_state_t;

/** User configuration structure, used in open function */
typedef struct st_rm_vee_callback_args
{
    rm_vee_state_t state;              ///< State of the Virtual EEPROM
    void const   * p_context;          ///< Placeholder for user data. Set in @ref rm_vee_api_t::open function in::rm_vee_cfg_t.
} rm_vee_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_rm_vee_cfg
{
    uint32_t   start_addr;                                ///< Start address to be used for Virtual EEPROM memory
    uint32_t   num_segments;                              ///< Number of segments to divide the volume into
    uint32_t   total_size;                                ///< Total size of the volume
    uint32_t   ref_data_size;                             ///< Size of the reference data stored at the end of the segment
    uint32_t   record_max_id;                             ///< Maximum record ID that can be used
    uint16_t * rec_offset;                                ///< Pointer to buffer used for record offset caching
    void (* p_callback)(rm_vee_callback_args_t * p_args); ///< Callback provided when a Virtual EEPROM event occurs.
    void const * p_context;                               ///< Placeholder for user data.
    void const * p_extend;                                ///< Pointer to hardware dependent configuration
} rm_vee_cfg_t;

typedef struct st_rm_vee_status
{
    rm_vee_state_t state;               ///< Current state of the Virtual EEPROM
    uint32_t       last_id;             ///< Last ID written
    uint32_t       space_available;     ///< Remaining space available in the segment
    uint32_t       segment_erase_count; ///< Current segment erase count
} rm_vee_status_t;

/** Virtual EEPROM API control block.  Allocate an instance specific control block to pass into the VEE API calls.
 * @par Implemented as
 * - @ref rm_vee_flash_instance_ctrl_t
 */
typedef void rm_vee_ctrl_t;

/** Virtual EEPROM interface API. */
typedef struct st_rm_vee_api
{
    /** Initializes the driver’s internal structures and opens the Flash driver.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_Open
     *
     * @param[in]   p_ctrl              Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg               Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(rm_vee_ctrl_t * const p_ctrl, rm_vee_cfg_t const * const p_cfg);

    /** Writes a record to data flash.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_RecordWrite
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   rec_id              ID of record to write.
     * @param[in]   p_rec_data          Pointer to record data to write.
     * @param[in]   num_bytes           Length of data to write.
     */
    fsp_err_t (* recordWrite)(rm_vee_ctrl_t * const p_ctrl, uint32_t const rec_id, uint8_t const * const p_rec_data,
                              uint32_t num_bytes);

    /** This function gets the pointer to the most recent version of a record specified by ID.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_RecordPtrGet
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   rec_id              ID of record to locate.
     * @param[in]   pp_rec_data         Pointer to set to the most recent version of the record.
     * @param[in]   p_num_bytes         Variable to load with record length.
     */
    fsp_err_t (* recordPtrGet)(rm_vee_ctrl_t * const p_ctrl, uint32_t rec_id, uint8_t ** const pp_rec_data,
                               uint32_t * const p_num_bytes);

    /** Writes new Reference data to the reference update area.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_RefDataWrite
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   p_ref_data          Pointer to data to write to the reference data update area.
     */
    fsp_err_t (* refDataWrite)(rm_vee_ctrl_t * const p_ctrl, uint8_t const * const p_ref_data);

    /** Gets a pointer to the most recent reference data.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_RefDataPtrGet
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   pp_ref_data         Pointer to set to the most recent valid reference data.
     */
    fsp_err_t (* refDataPtrGet)(rm_vee_ctrl_t * const p_ctrl, uint8_t ** const pp_ref_data);

    /** Get the current status of the VEE driver.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_StatusGet
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   p_status            Pointer to store the current status of the VEE driver.
     */
    fsp_err_t (* statusGet)(rm_vee_ctrl_t * const p_ctrl, rm_vee_status_t * const p_status);

    /** Manually start a refresh operation.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_Refresh
     *
     * @param[in]   p_ctrl              Pointer to control block.
     */
    fsp_err_t (* refresh)(rm_vee_ctrl_t * const p_ctrl);

    /** Format the Virtual EEPROM.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_Format
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   p_ref_data          Optional pointer to reference data to write during format.
     */
    fsp_err_t (* format)(rm_vee_ctrl_t * const p_ctrl, uint8_t const * const p_ref_data);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref rm_vee_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(rm_vee_ctrl_t * const p_api_ctrl, void (* p_callback)(rm_vee_callback_args_t *),
                              void const * const p_context, rm_vee_callback_args_t * const p_callback_memory);

    /** Closes the module and lower level storage device.
     * @par Implemented as
     * - @ref RM_VEE_FLASH_Close
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_vee_api_t::open call.
     */
    fsp_err_t (* close)(rm_vee_ctrl_t * const p_ctrl);
} rm_vee_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_vee_instance
{
    rm_vee_ctrl_t      * p_ctrl;       ///< Pointer to the control structure for this instance
    rm_vee_cfg_t const * p_cfg;        ///< Pointer to the configuration structure for this instance
    rm_vee_api_t const * p_api;        ///< Pointer to the API structure for this instance
} rm_vee_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end defgroup RM_VEE_API)
 **********************************************************************************************************************/

#endif                                 /* RM_VEE_API_H */
