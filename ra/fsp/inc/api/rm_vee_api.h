/**********************************************************************************************************
* Copyright (c) 2020 - 2025, Renesas Electronics Corporation and/or its affiliates
*
*
* By installing, copying, downloading, accessing, or otherwise using this software
* or any part thereof and the related documentation from Renesas Electronics Corporation
* and/or its affiliates ("Renesas"), You, either individually  or on behalf of an entity
* employing or engaging You, agree to be bound by this Software License Agreement.
* If you do not agree or no longer agree, you are not permitted to use this software or
* related documentation.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form, except as embedded into a Renesas
*    integrated circuit in a product or a software update for
*    such product, must reproduce the above copyright notice, this list of
*    conditions and the following disclaimer in the documentation and/or other
*    materials provided with the distribution.
*
* 3. Neither the name of Renesas nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* 4. This software, with or without modification, must only be used with a
*    Renesas integrated circuit, or other such integrated circuit permitted by Renesas in writing.
*
* 5. Any software provided in binary form under this license must not be reverse
*    engineered, decompiled, modified and/or disassembled.
*
* THIS SOFTWARE IS PROVIDED BY RENESAS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL RENESAS OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
* GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********************************************************************************************************/

#ifndef RM_VEE_API_H
#define RM_VEE_API_H

/*******************************************************************************************************************//**
 * @defgroup RM_VEE_API Virtual EEPROM Interface
 * @ingroup RENESAS_STORAGE_INTERFACES
 * @brief Interface for Virtual EEPROM access
 *
 * @section RM_VEE_API_SUMMARY Summary
 * The Virtual EEPROM Port configures a fail-safe key value store designed for microcontrollers on top of a lower
 * level storage device.
 *
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
    void         * p_context;          ///< Placeholder for user data. Set in @ref rm_vee_api_t::open function in::rm_vee_cfg_t.
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
    void       * p_context;                               ///< Placeholder for user data.
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
 */
typedef void rm_vee_ctrl_t;

/** Virtual EEPROM interface API. */
typedef struct st_rm_vee_api
{
    /** Initializes the driver’s internal structures and opens the Flash driver.
     *
     * @param[in]   p_ctrl              Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg               Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(rm_vee_ctrl_t * const p_ctrl, rm_vee_cfg_t const * const p_cfg);

    /** Writes a record to data flash.
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   rec_id              ID of record to write.
     * @param[in]   p_rec_data          Pointer to record data to write.
     * @param[in]   num_bytes           Length of data to write.
     */
    fsp_err_t (* recordWrite)(rm_vee_ctrl_t * const p_ctrl, uint32_t const rec_id, uint8_t const * const p_rec_data,
                              uint32_t num_bytes);

    /** This function gets the pointer to the most recent version of a record specified by ID.
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   rec_id              ID of record to locate.
     * @param[in]   pp_rec_data         Pointer to set to the most recent version of the record.
     * @param[in]   p_num_bytes         Variable to load with record length.
     */
    fsp_err_t (* recordPtrGet)(rm_vee_ctrl_t * const p_ctrl, uint32_t rec_id, uint8_t ** const pp_rec_data,
                               uint32_t * const p_num_bytes);

    /** Writes new Reference data to the reference update area.
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   p_ref_data          Pointer to data to write to the reference data update area.
     */
    fsp_err_t (* refDataWrite)(rm_vee_ctrl_t * const p_ctrl, uint8_t const * const p_ref_data);

    /** Gets a pointer to the most recent reference data.
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   pp_ref_data         Pointer to set to the most recent valid reference data.
     */
    fsp_err_t (* refDataPtrGet)(rm_vee_ctrl_t * const p_ctrl, uint8_t ** const pp_ref_data);

    /** Get the current status of the VEE driver.
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   p_status            Pointer to store the current status of the VEE driver.
     */
    fsp_err_t (* statusGet)(rm_vee_ctrl_t * const p_ctrl, rm_vee_status_t * const p_status);

    /** Manually start a refresh operation.
     *
     * @param[in]   p_ctrl              Pointer to control block.
     */
    fsp_err_t (* refresh)(rm_vee_ctrl_t * const p_ctrl);

    /** Format the Virtual EEPROM.
     *
     * @param[in]   p_ctrl              Pointer to control block.
     * @param[in]   p_ref_data          Optional pointer to reference data to write during format.
     */
    fsp_err_t (* format)(rm_vee_ctrl_t * const p_ctrl, uint8_t const * const p_ref_data);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Control block set in @ref rm_vee_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(rm_vee_ctrl_t * const p_ctrl, void (* p_callback)(rm_vee_callback_args_t *),
                              void * const p_context, rm_vee_callback_args_t * const p_callback_memory);

    /** Closes the module and lower level storage device.
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
