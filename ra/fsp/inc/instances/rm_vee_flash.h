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

#ifndef RM_VEE_FLASH_H
#define RM_VEE_FLASH_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_vee_api.h"
#include "r_flash_api.h"
#include "rm_vee_flash_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_VEE_FLASH
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* On MCUs with single byte data flash writes this can be lowered to 2. However, data
 *  returned via RM_VEE_FLASH_RecordPtrGet will not be guaranteed to be 32 bit aligned. */
#ifndef RM_VEE_FLASH_DF_WRITE_SIZE
 #define RM_VEE_FLASH_DF_WRITE_SIZE    (4)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** User configuration structure, used in open function */
typedef struct st_rm_vee_flash_cfg
{
    flash_instance_t const * p_flash;  ///< Pointer to a flash instance
} rm_vee_flash_cfg_t;

/* Segment Header */
typedef struct
{
    uint32_t refresh_cnt;
    uint16_t pad;
    uint16_t valid_code;
} rm_vee_seg_hdr_t;

/* Record Header (only written to flash when variable length records are configured) */
typedef struct
{
    uint16_t length;                   // length of data portion of this record
    uint16_t offset;                   // temp value "passed to"/used at interrupt level
} rm_vee_rec_hdr_t;

/* Record Trailer */
typedef struct
{
    uint16_t id;
    uint16_t valid_code;
} rm_vee_rec_end_t;

/* Reference Data Update Area Header */
typedef struct
{
    uint16_t pad;
    uint16_t valid_code;               // alternate area contains updated refdata
} rm_vee_ref_hdr_t;

/** Instance control block.  This is private to the FSP and should not be used or modified by the application. */
typedef struct st_rm_vee_flash_instance_ctrl
{
    uint32_t                 open;
    volatile uint32_t        mode;
    volatile uint32_t        state;
    uint32_t                 active_seg_addr;
    uint32_t                 next_write_addr;
    uint32_t                 ref_hdr_addr;
    rm_vee_cfg_t const     * p_cfg;
    bool                     new_refdata_valid; // update area written successfully
    bool                     factory_refdata;   // update area written successfully
    volatile bool            irq_flag;
    uint8_t                  xfer_buf[RM_VEE_FLASH_REFRESH_BUFFER_SIZE];
    rm_vee_seg_hdr_t         seg_hdr;
    rm_vee_rec_hdr_t         rec_hdr;
    uint8_t const          * p_rec_data;
    rm_vee_rec_end_t         rec_end;
    rm_vee_ref_hdr_t         ref_hdr;
    volatile flash_event_t   flash_event;
    flash_event_t            flash_err_event;          // error event from Flash driver
    uint32_t                 last_id;                  // ID of last record successfully written
    uint32_t                 refresh_type;
    uint32_t                 refresh_src_seg_addr;
    uint32_t                 refresh_src_rec_end_addr; // addr of first byte after last record
    uint32_t                 refresh_src_refdata_addr;
    uint32_t                 refresh_start_rec_id;     // ID of first record copied during Refresh
    uint32_t                 refresh_cur_rec_id;       // g_rec_offset[] index used during Refresh
    uint32_t                 refresh_dst_rec_end_addr; // addr of first byte after last record
    uint32_t                 refresh_xfer_src_addr;
    uint32_t                 refresh_xfer_bytes_left;
    flash_instance_t const * p_flash;
    uint32_t                 segment_size;
    uint8_t                  data_buffer[RM_VEE_FLASH_DF_WRITE_SIZE];

    void (* p_callback)(rm_vee_callback_args_t *); // Pointer to callback
    rm_vee_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void * p_context;                              // Pointer to context to be passed into callback function
} rm_vee_flash_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_vee_api_t g_rm_vee_on_flash;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_Open(rm_vee_ctrl_t * const p_api_ctrl, rm_vee_cfg_t const * const p_cfg);
fsp_err_t RM_VEE_FLASH_RecordWrite(rm_vee_ctrl_t * const p_api_ctrl,
                                   uint32_t const        rec_id,
                                   uint8_t const * const p_rec_data,
                                   uint32_t const        num_bytes);
fsp_err_t RM_VEE_FLASH_RecordPtrGet(rm_vee_ctrl_t * const p_api_ctrl,
                                    uint32_t const        rec_id,
                                    uint8_t ** const      pp_rec_data,
                                    uint32_t * const      p_num_bytes);
fsp_err_t RM_VEE_FLASH_RefDataWrite(rm_vee_ctrl_t * const p_api_ctrl, uint8_t const * const p_ref_data);
fsp_err_t RM_VEE_FLASH_RefDataPtrGet(rm_vee_ctrl_t * const p_api_ctrl, uint8_t ** const pp_ref_data);
fsp_err_t RM_VEE_FLASH_StatusGet(rm_vee_ctrl_t * const p_api_ctrl, rm_vee_status_t * const p_status);
fsp_err_t RM_VEE_FLASH_Refresh(rm_vee_ctrl_t * const p_api_ctrl);
fsp_err_t RM_VEE_FLASH_Format(rm_vee_ctrl_t * const p_api_ctrl, uint8_t const * const p_ref_data);
fsp_err_t RM_VEE_FLASH_CallbackSet(rm_vee_ctrl_t * const          p_api_ctrl,
                                   void (                       * p_callback)(rm_vee_callback_args_t *),
                                   void * const                   p_context,
                                   rm_vee_callback_args_t * const p_callback_memory);
fsp_err_t RM_VEE_FLASH_Close(rm_vee_ctrl_t * const p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_VEE_FLASH_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_VEE_FLASH)
 **********************************************************************************************************************/
