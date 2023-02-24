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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>                    // memset(), memcpy();
#include "rm_vee_flash_cfg.h"
#include "rm_vee_flash.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* INTERRUPT TIMEOUT VALUES (for Open() to catch user global interrupt disable) */
#ifndef RM_VEE_FLASH_TIMEOUT_US
 #define RM_VEE_FLASH_TIMEOUT_US             (1000000)
#endif
#ifndef RM_VEE_FLASH_TIMEOUT_REFRESH_US
 #define RM_VEE_FLASH_TIMEOUT_REFRESH_US     (5000000)
#endif

#define RM_VEE_FLASH_OPEN                    (0x52564545U)
#define RM_VEE_FLASH_VALID_CODE              (0xBEAD)
#define RM_VEE_FLASH_ID_INVALID              (UINT16_MAX)
#define RM_VEE_FLASH_LOGICAL_END_ADDRESS     (p_ctrl->p_cfg->start_addr + p_ctrl->p_cfg->total_size)
#define RM_VEE_FLASH_PHYSICAL_END_ADDRESS    (BSP_FEATURE_FLASH_DATA_FLASH_START + BSP_DATA_FLASH_SIZE_BYTES)
#define RM_VEE_FLASH_REC_OVERHEAD            (sizeof(rm_vee_rec_hdr_t) + sizeof(rm_vee_rec_end_t))
#define RM_VEE_FLASH_REF_DATA_COUNT          (2)
#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
 #define RM_VEE_FLASH_REF_DATA_AREA_SIZE     ((sizeof(rm_vee_ref_hdr_t) + \
                                               (p_ctrl->p_cfg->ref_data_size * RM_VEE_FLASH_REF_DATA_COUNT)))
#else
 #define RM_VEE_FLASH_REF_DATA_AREA_SIZE     (0)
#endif

/* Use appropriate macros for Flash HP or LP */
#if (BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE > 0)
 #define RM_VEE_FLASH_DF_BLOCK_SIZE          (BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE)
#else
 #define RM_VEE_FLASH_DF_BLOCK_SIZE          (BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE)
#endif

#define RM_VEE_FLASH_DF_WRITE_MASK           (RM_VEE_FLASH_DF_WRITE_SIZE - 1U)

#define RM_VEE_ADDRESS_ALIGN(x)    ((x + RM_VEE_FLASH_DF_WRITE_MASK) & (~RM_VEE_FLASH_DF_WRITE_MASK))

#define RM_VEE_FLASH_REC_DATA_MAX_SIZE       (p_ctrl->segment_size -                                           \
                                              (sizeof(rm_vee_seg_hdr_t) + (p_ctrl->p_cfg->ref_data_size * 2) + \
                                               sizeof(rm_vee_ref_hdr_t) + RM_VEE_FLASH_REC_OVERHEAD))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Driver Modes */
typedef enum e_rm_vee_flash_prv_mode
{
    RM_VEE_FLASH_PRV_MODE_NORMAL        = 0,
    RM_VEE_FLASH_PRV_MODE_REFRESH       = RM_VEE_STATE_REFRESH,
    RM_VEE_FLASH_PRV_MODE_OVERFLOW      = RM_VEE_STATE_OVERFLOW,
    RM_VEE_FLASH_PRV_MODE_FLASH_PE_FAIL = RM_VEE_STATE_HARDWARE_FAIL,
} rm_vee_flash_prv_mode_t;

/* Driver States (used in NORMAL and REFRESH modes) */
typedef enum e_rm_vee_flash_prv_states
{
    RM_VEE_FLASH_PRV_STATES_UNINITIALIZED = 0,
    RM_VEE_FLASH_PRV_STATES_READY,
    RM_VEE_FLASH_PRV_STATES_WRITE_REC_HDR,
    RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA,
    RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA_TAIL,
    RM_VEE_FLASH_PRV_STATES_WRITE_REC_END,
    RM_VEE_FLASH_PRV_STATES_WRITE_REC_REFRESH,
    RM_VEE_FLASH_PRV_STATES_WRITE_NEW_REFDATA,
    RM_VEE_FLASH_PRV_STATES_WRITE_NEW_REFDATA_HDR,
    RM_VEE_FLASH_PRV_STATES_WRITE_REFDATA,
    RM_VEE_FLASH_PRV_STATES_WRITE_SEG_HDR,
    RM_VEE_FLASH_PRV_STATES_ERASE_SEG,
} rm_vee_flash_prv_states_t;

typedef enum e_rm_vee_flash_refresh_refresh
{
    RM_VEE_FLASH_PRV_REFRESH_USER_REQ,
    RM_VEE_FLASH_PRV_REFRESH_REFDATA_OVFL,
    RM_VEE_FLASH_PRV_REFRESH_RECORD_OVFL
} rm_vee_flash_refresh_refresh_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * rm_vee_flash_prv_ns_callback)(rm_vee_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile rm_vee_flash_prv_ns_callback)(rm_vee_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * External functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/* Internal functions */
static fsp_err_t rm_vee_internal_open(rm_vee_flash_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_vee_inspect_segments(rm_vee_flash_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_vee_refresh_next_data_source(rm_vee_flash_instance_ctrl_t * const p_ctrl);
static uint32_t  rm_vee_get_next_id(rm_vee_flash_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_vee_restore_previous_seg(rm_vee_flash_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_vee_write_seg_hdr(rm_vee_flash_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_vee_init_record_xfer(rm_vee_flash_instance_ctrl_t * const p_ctrl, uint32_t id);
static fsp_err_t rm_vee_xfer_next_chunk(rm_vee_flash_instance_ctrl_t * const p_ctrl, rm_vee_flash_prv_states_t state);
static void      rm_vee_flash_err_handle(rm_vee_flash_instance_ctrl_t * const p_ctrl, fsp_err_t err);
static fsp_err_t rm_vee_state_get(rm_vee_flash_instance_ctrl_t * const p_ctrl, rm_vee_state_t * p_state);
static fsp_err_t rm_vee_blocking_erase_segment(rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                               uint32_t                             seg_addr,
                                               bool                                 contains_refdata);
static fsp_err_t rm_vee_load_record_table(rm_vee_flash_instance_ctrl_t * const p_ctrl, bool initial_load);
static fsp_err_t rm_vee_blocking_blankcheck(rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                            uint32_t                             addr,
                                            uint32_t                             num_bytes,
                                            flash_event_t                      * p_event);
static fsp_err_t rm_vee_blocking_erase(rm_vee_flash_instance_ctrl_t * const p_ctrl, uint32_t addr, uint32_t num_blocks);
static fsp_err_t rm_vee_blocking_write(rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                       uint32_t                             src_addr,
                                       uint32_t                             dst_addr,
                                       uint32_t                             num_bytes);
static fsp_err_t rm_vee_internal_write_rec(rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                           uint32_t                             rec_id,
                                           uint8_t const * const                p_rec_data,
                                           uint32_t                             num_bytes);
static fsp_err_t rm_vee_start_seg_refresh(rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                          rm_vee_flash_refresh_refresh_t       refresh_type,
                                          uint32_t                             rec_id,
                                          uint32_t                             addr,
                                          uint32_t                             num_bytes);

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
static fsp_err_t rm_vee_inspect_new_refdata(rm_vee_flash_instance_ctrl_t * const p_ctrl);
static void      rm_vee_init_refdata_xfer(rm_vee_flash_instance_ctrl_t * const p_ctrl);

#endif

void rm_vee_flash_callback(flash_callback_args_t * p_args);

const rm_vee_api_t g_rm_vee_on_flash =
{
    .open          = RM_VEE_FLASH_Open,
    .recordWrite   = RM_VEE_FLASH_RecordWrite,
    .recordPtrGet  = RM_VEE_FLASH_RecordPtrGet,
    .refDataWrite  = RM_VEE_FLASH_RefDataWrite,
    .refDataPtrGet = RM_VEE_FLASH_RefDataPtrGet,
    .statusGet     = RM_VEE_FLASH_StatusGet,
    .refresh       = RM_VEE_FLASH_Refresh,
    .format        = RM_VEE_FLASH_Format,
    .close         = RM_VEE_FLASH_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_VEE_FLASH
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open the RM_VEE_FLASH driver module
 *
 * Implements @ref rm_vee_api_t::open
 *
 * Initializes the driver's internal structures and opens the Flash driver. The Flash driver must be closed prior to
 * opening VEE. The error code FSP_SUCCESS_RECOVERY indicates that VEE detected corrupted data; most likely due to a power
 * loss during a data flash write or erase. In these cases, an automatic internal Refresh is performed and the partially
 * written data is lost.
 *
 * @retval FSP_SUCCESS               Successful. FSP_SUCCESS_RECOVERY changed to FSP_SUCCESS
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 * @retval FSP_ERR_ALREADY_OPEN      This function has already been called.
 * @retval FSP_ERR_PE_FAILURE        This error indicates that a flash programming, erase, or blankcheck operation has failed
 *                                   in hardware.
 * @retval FSP_ERR_TIMEOUT           Interrupts disabled outside of VEE
 * @retval FSP_ERR_NOT_INITIALIZED   Corruption found. A refresh is required.
 * @retval FSP_ERR_INVALID_ARGUMENT  The supplied configuration is invalid.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_Open (rm_vee_ctrl_t * const p_api_ctrl, rm_vee_cfg_t const * const p_cfg)
{
    uint32_t  i;
    fsp_err_t err;
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;

#if RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE == 1
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);

    /* Interface isn't already open and is configured for more than one segment */
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(2 <= p_cfg->num_segments, FSP_ERR_INVALID_ARGUMENT);

    /* Start and end adress are valid */
    FSP_ERROR_RETURN(BSP_FEATURE_FLASH_DATA_FLASH_START <= p_cfg->start_addr, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PHYSICAL_END_ADDRESS >= (p_cfg->start_addr + p_cfg->total_size),
                     FSP_ERR_INVALID_ARGUMENT);

    /* All memory segments are correctly aligned */
    FSP_ERROR_RETURN(0 == (p_cfg->start_addr - BSP_FEATURE_FLASH_DATA_FLASH_START) % RM_VEE_FLASH_DF_BLOCK_SIZE,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0 == p_cfg->total_size % RM_VEE_FLASH_DF_BLOCK_SIZE, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0 == (p_cfg->total_size / RM_VEE_FLASH_DF_BLOCK_SIZE) % p_cfg->num_segments,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0 == (p_cfg->total_size % p_cfg->num_segments), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0 == ((p_cfg->total_size / p_cfg->num_segments) % 4), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0 == (p_cfg->ref_data_size % RM_VEE_FLASH_DF_WRITE_SIZE), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_ctrl->p_cfg        = p_cfg;
    p_ctrl->p_flash      = ((rm_vee_flash_cfg_t *) p_ctrl->p_cfg->p_extend)->p_flash;
    p_ctrl->segment_size = p_cfg->total_size / p_cfg->num_segments;

    /* Open flash */
    err = p_ctrl->p_flash->p_api->open(p_ctrl->p_flash->p_ctrl, p_ctrl->p_flash->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_UNINITIALIZED;

    /* Initialize VEE */
    err = rm_vee_internal_open(p_ctrl);

    /* Do a refresh if active segment corrupted */
    if (FSP_ERR_NOT_INITIALIZED == err)
    {
        err = rm_vee_start_seg_refresh(p_ctrl, RM_VEE_FLASH_PRV_REFRESH_USER_REQ, 0, 0, 0);

        if (FSP_SUCCESS == err)
        {
            /* Block until Refresh done (Refresh and/or error condition will clear driver lock in callback function) */
            for (i = 0; i < RM_VEE_FLASH_TIMEOUT_REFRESH_US; i++)
            {
                if (p_ctrl->state == RM_VEE_FLASH_PRV_STATES_READY)
                {
                    break;
                }

                R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
            }

            if (RM_VEE_FLASH_TIMEOUT_REFRESH_US == i)
            {
                err = FSP_ERR_TIMEOUT;
            }
            else if (RM_VEE_FLASH_PRV_MODE_FLASH_PE_FAIL == p_ctrl->mode)
            {
                err = FSP_ERR_PE_FAILURE;
            }
            else
            {
                /* Do nothing. */
            }
        }
    }

    /* Close Flash if fatal error */
    if (FSP_SUCCESS != err)
    {
        /* NOTE: If a timeout occurred, the Flash driver is "hung" in a BUSY condition and cannot close.
         * This will cause an error at the next VEE open. This is considered a user development issue
         * and should not be addressed by modifying the drivers.
         */
        p_ctrl->p_flash->p_api->close(p_ctrl->p_flash->p_ctrl);
    }
    else
    {
        p_ctrl->seg_hdr.refresh_cnt = ((rm_vee_seg_hdr_t *) p_ctrl->active_seg_addr)->refresh_cnt;
        p_ctrl->seg_hdr.pad         = 0;
        p_ctrl->seg_hdr.valid_code  = RM_VEE_FLASH_VALID_CODE;

        p_ctrl->rec_hdr.length = 0;
        p_ctrl->rec_hdr.offset = 0;
        p_ctrl->p_rec_data     = NULL;

        p_ctrl->rec_end.id         = (uint16_t) RM_VEE_FLASH_ID_INVALID;
        p_ctrl->rec_end.valid_code = RM_VEE_FLASH_VALID_CODE;

        p_ctrl->ref_hdr.pad        = 0;
        p_ctrl->ref_hdr.valid_code = RM_VEE_FLASH_VALID_CODE;

        p_ctrl->p_callback        = p_cfg->p_callback;
        p_ctrl->p_context         = p_cfg->p_context;
        p_ctrl->p_callback_memory = NULL;

        p_ctrl->mode = RM_VEE_FLASH_PRV_MODE_NORMAL;

        p_ctrl->open = RM_VEE_FLASH_OPEN;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Writes a record to data flash.
 *
 * Implements @ref rm_vee_api_t::recordWrite
 *
 * This function writes num_bytes of data pointed to by p_rec_data to data flash. This function returns immediately
 * after starting the flash write. BE SURE NOT TO MODIFY the data buffer contents until after the write completes. This
 * includes exiting the calling function when the data buffer is a local variable (stack may be used by another function
 * and corrupt the data buffer contents).
 *
 * @retval FSP_SUCCESS               Write started successfully.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT  An argument contains an illegal value.
 * @retval FSP_ERR_INVALID_MODE      The operation cannot be started in the current mode.
 * @retval FSP_ERR_IN_USE            Last API call still executing.
 * @retval FSP_ERR_PE_FAILURE        This error indicates that a flash programming, erase, or blankcheck operation has failed
 *                                   in hardware.
 * @retval FSP_ERR_TIMEOUT           Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED   Corruption found. A refresh is required.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_RecordWrite (rm_vee_ctrl_t * const p_api_ctrl,
                                    uint32_t const        rec_id,
                                    uint8_t const * const p_rec_data,
                                    uint32_t const        num_bytes)
{
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;

#if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_rec_data);

    FSP_ERROR_RETURN(rec_id <= p_ctrl->p_cfg->record_max_id, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0 != num_bytes, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(RM_VEE_FLASH_REC_DATA_MAX_SIZE >= num_bytes, FSP_ERR_INVALID_ARGUMENT);

    FSP_ASSERT(NULL != p_rec_data);

    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_MODE_OVERFLOW != p_ctrl->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_MODE_FLASH_PE_FAIL != p_ctrl->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state, FSP_ERR_IN_USE);
#endif

    fsp_err_t err = rm_vee_internal_write_rec(p_ctrl, rec_id, p_rec_data, num_bytes);
    rm_vee_flash_err_handle(p_ctrl, err);

    return err;
}

/*******************************************************************************************************************//**
 * Writes new Reference data to the reference update area.
 *
 * Implements @ref rm_vee_api_t::refDataWrite
 *
 * This function writes VEE_CFG_REF_DATA_SIZE bytes pointed to by p_ref_data to data flash. This function
 * returns immediately after starting the flash write. BE SURE NOT TO MODIFY the data buffer contents until after the
 * write completes.
 *
 * @retval FSP_SUCCESS               Write started successfully.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_IN_USE            Last API call still executing.
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 * @retval FSP_ERR_INVALID_MODE      The operation cannot be started in the current mode.
 * @retval FSP_ERR_PE_FAILURE        This error indicates that a flash programming, erase, or blankcheck operation has failed
 *                                   in hardware.
 * @retval FSP_ERR_TIMEOUT           Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_UNSUPPORTED       Reference data is not supported in the current configuration.
 * @retval FSP_ERR_NOT_INITIALIZED   Corruption found. A refresh is required.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_RefDataWrite (rm_vee_ctrl_t * const p_api_ctrl, uint8_t const * const p_ref_data)
{
#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err;
 #if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_ref_data);

    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_MODE_OVERFLOW != p_ctrl->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_MODE_FLASH_PE_FAIL != p_ctrl->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state, FSP_ERR_IN_USE);

    FSP_ERROR_RETURN(0 < p_ctrl->p_cfg->ref_data_size, FSP_ERR_UNSUPPORTED);
 #endif

    if (false == p_ctrl->new_refdata_valid)
    {
        /* Initiate refdata write */
        p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_NEW_REFDATA;
        err           = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                                      (uint32_t) p_ref_data,
                                                      p_ctrl->ref_hdr_addr + sizeof(rm_vee_ref_hdr_t),
                                                      p_ctrl->p_cfg->ref_data_size);
    }
    else
    {
        /* Start refresh */
        err = rm_vee_start_seg_refresh(p_ctrl,
                                       RM_VEE_FLASH_PRV_REFRESH_REFDATA_OVFL,
                                       RM_VEE_FLASH_ID_INVALID,
                                       (uint32_t) p_ref_data,
                                       p_ctrl->p_cfg->ref_data_size);
    }

    rm_vee_flash_err_handle(p_ctrl, err);

    return err;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_ref_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Gets a pointer to the most recent record data.
 *
 * Implements @ref rm_vee_api_t::recordPtrGet
 *
 * This function sets the argument pointer to the most recent version of the record data in flash. Flash cannot be
 * accessed for reading and writing at the same time. Therefore, reading the data at p_ref_data must be completed prior
 * to initiating any type of Flash write.
 *
 * @retval FSP_SUCCESS               Successful.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_IN_USE            Last API call still executing.
 * @retval FSP_ERR_ASSERTION         p_ref_data is NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT  Record data not configured.
 * @retval FSP_ERR_NOT_FOUND         The record associated with the requested ID could not be found.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_RecordPtrGet (rm_vee_ctrl_t * const p_api_ctrl,
                                     uint32_t const        rec_id,
                                     uint8_t ** const      pp_rec_data,
                                     uint32_t * const      p_num_bytes)
{
    rm_vee_rec_hdr_t * p_hdr;
    fsp_err_t          err;
    uint32_t           addr;
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;

#if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(pp_rec_data);
    FSP_ASSERT(p_num_bytes);
    FSP_ERROR_RETURN(p_ctrl->p_cfg->record_max_id >= rec_id, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state, FSP_ERR_IN_USE);
#endif

    if (0 == p_ctrl->p_cfg->rec_offset[rec_id])
    {
        err = FSP_ERR_NOT_FOUND;
    }
    else
    {
        addr = p_ctrl->active_seg_addr + p_ctrl->p_cfg->rec_offset[rec_id];

        /* Load start of record data and its length */
        p_hdr        = (rm_vee_rec_hdr_t *) addr;
        *p_num_bytes = p_hdr->length;
        addr        += sizeof(rm_vee_rec_hdr_t);
        *pp_rec_data = (uint8_t *) addr;
        err          = FSP_SUCCESS;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Gets a pointer to the most recent reference data.
 *
 * Implements @ref rm_vee_api_t::recordPtrGet
 *
 * This function sets the argument pointer to the most recent version of the reference data in flash. Flash cannot be
 * accessed for reading and writing at the same time.
 *
 * @retval FSP_SUCCESS               Successful.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_IN_USE            Last API call still executing.
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 * @retval FSP_ERR_UNSUPPORTED       Reference data is not supported in the current configuration.
 * @retval FSP_ERR_NOT_FOUND         No reference data was found.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_RefDataPtrGet (rm_vee_ctrl_t * const p_api_ctrl, uint8_t ** const pp_ref_data)
{
#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;
 #if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(pp_ref_data);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state, FSP_ERR_IN_USE);

    FSP_ERROR_RETURN(0 < p_ctrl->p_cfg->ref_data_size, FSP_ERR_UNSUPPORTED);
 #endif

    if (true == p_ctrl->new_refdata_valid)
    {
        *pp_ref_data =
            (uint8_t *) (p_ctrl->active_seg_addr + (p_ctrl->segment_size - (2 * p_ctrl->p_cfg->ref_data_size)));
    }
    else if (true == p_ctrl->factory_refdata)
    {
        *pp_ref_data = (uint8_t *) (p_ctrl->active_seg_addr + (p_ctrl->segment_size - p_ctrl->p_cfg->ref_data_size));
    }
    else
    {
        err = FSP_ERR_NOT_FOUND;
    }

    return err;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(pp_ref_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Manually start a refresh operation
 *
 * Implements @ref rm_vee_api_t::refresh
 *
 * This function is used to start a segment Refresh at any time. The Refresh process by default occurs automatically
 * when no more record or reference data space is available and a Write is requested. However, the app may desire to
 * force a refresh when it knows it is running low on space and large amounts of data are about to be recorded.
 *
 * @retval FSP_SUCCESS               Successful.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 * @retval FSP_ERR_IN_USE            Last API call still executing.
 * @retval FSP_ERR_PE_FAILURE        This error indicates that a flash programming, erase, or blankcheck operation has failed
 *                                   in hardware.
 * @retval FSP_ERR_INVALID_MODE      The operation cannot be started in the current mode.
 * @retval FSP_ERR_TIMEOUT           Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED   Corruption found. A refresh is required.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_Refresh (rm_vee_ctrl_t * const p_api_ctrl)
{
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;
#if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_MODE_OVERFLOW != p_ctrl->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_MODE_FLASH_PE_FAIL != p_ctrl->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state, FSP_ERR_IN_USE);
#endif

    fsp_err_t err = rm_vee_start_seg_refresh(p_ctrl, RM_VEE_FLASH_PRV_REFRESH_USER_REQ, 0, 0, 0);
    rm_vee_flash_err_handle(p_ctrl, err);

    return err;
}

/*******************************************************************************************************************//**
 * Start a manual format operation.
 *
 * Implements @ref rm_vee_api_t::format
 *
 * @retval FSP_SUCCESS               Successful.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_IN_USE            Last API call still executing.
 * @retval FSP_ERR_PE_FAILURE        This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 * @retval FSP_ERR_TIMEOUT           Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED   Corruption found. A refresh is required.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_Format (rm_vee_ctrl_t * const p_api_ctrl, uint8_t const * const p_ref_data)
{
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;
#if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state, FSP_ERR_IN_USE);
#endif
    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_UNINITIALIZED;
    fsp_err_t err =
        rm_vee_blocking_erase(p_ctrl,
                              p_ctrl->p_cfg->start_addr,
                              (p_ctrl->p_cfg->total_size / RM_VEE_FLASH_DF_BLOCK_SIZE));

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
    if ((0 != p_ctrl->p_cfg->ref_data_size) && (NULL != p_ref_data) && (FSP_SUCCESS == err))
    {
        err =
            rm_vee_blocking_write(p_ctrl,
                                  (uint32_t) p_ref_data,
                                  (RM_VEE_FLASH_LOGICAL_END_ADDRESS - p_ctrl->p_cfg->ref_data_size),
                                  p_ctrl->p_cfg->ref_data_size);
    }

#else
    FSP_PARAMETER_NOT_USED(p_ref_data);
#endif

    if (FSP_SUCCESS == err)
    {
        err = rm_vee_internal_open(p_ctrl);
    }

    rm_vee_flash_err_handle(p_ctrl, err);

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 *
 * Implements @ref rm_vee_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_CallbackSet (rm_vee_ctrl_t * const          p_api_ctrl,
                                    void (                       * p_callback)(rm_vee_callback_args_t *),
                                    void const * const             p_context,
                                    rm_vee_callback_args_t * const p_callback_memory)
{
    rm_vee_flash_instance_ctrl_t * p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;

#if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    rm_vee_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                         CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(rm_vee_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the current status of the driver.
 *
 * Implements @ref rm_vee_api_t::statusGet
 *
 * This command is typically used to verify that the last Write or Refresh command has completed before attempting to
 * perform another API call.
 *
 * @retval FSP_SUCCESS               Successful.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_StatusGet (rm_vee_ctrl_t * const p_api_ctrl, rm_vee_status_t * const p_status)
{
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;
#if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_status);
#endif

    fsp_err_t err = FSP_SUCCESS;

    err = rm_vee_state_get(p_ctrl, &p_status->state);

    p_status->last_id = p_ctrl->last_id;

    p_status->segment_erase_count = ((rm_vee_seg_hdr_t *) p_ctrl->active_seg_addr)->refresh_cnt;

    p_status->space_available = p_ctrl->ref_hdr_addr - p_ctrl->next_write_addr;

    return err;
}

/*******************************************************************************************************************//**
 * Closes the Flash driver and VEE driver.
 *
 * Implements @ref rm_vee_api_t::close
 *
 * @retval FSP_SUCCESS               Successful.
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened.
 * @retval FSP_ERR_ASSERTION         An input parameter is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_VEE_FLASH_Close (rm_vee_ctrl_t * const p_api_ctrl)
{
    rm_vee_flash_instance_ctrl_t * const p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_api_ctrl;

#if (RM_VEE_FLASH_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_VEE_FLASH_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->open = 0;

    p_ctrl->p_flash->p_api->close(p_ctrl->p_flash->p_ctrl);

    p_ctrl->mode  = RM_VEE_FLASH_PRV_MODE_NORMAL;
    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_UNINITIALIZED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end defgroup RM_VEE_FLASH)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This function is called by the API Open function and the Control() CMD_FORMAT operation. It handles
 * all VEE initialization other than opening the flash driver. No locking/unlocking occurs within this
 * function.
 *
 * @param  p_ctrl                   Pointer to the control block
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_internal_open (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err;

    /* Clear record offset cache */
    memset((void *) &p_ctrl->p_cfg->rec_offset[0], 0,
           ((p_ctrl->p_cfg->record_max_id + 1) * sizeof(p_ctrl->p_cfg->rec_offset[0])));

    p_ctrl->irq_flag = false;
    p_ctrl->last_id  = (uint16_t) RM_VEE_FLASH_ID_INVALID;

    /* Determine active segment and erase incomplete segments if any (refresh or erase interrupted). */
    err = rm_vee_inspect_segments(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Get latest record location for each ID and determine next write location. */
    err = rm_vee_load_record_table(p_ctrl, true);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_ctrl->new_refdata_valid = false;
    p_ctrl->factory_refdata   = false;

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
    if (0 != p_ctrl->p_cfg->ref_data_size)
    {
        /* Determine if reference data update area is used and is valid */
        err = rm_vee_inspect_new_refdata(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_READY;

    return err;
}

/*******************************************************************************************************************//**
 * This function walks through each data flash segment. If it is not the active segment, it is erased
 * if not blank. If more than one active segment is detected, the older one is erased. If no active segment
 * is found, the final segment is made the active segment.
 *
 * @param  p_ctrl                   Pointer to the control block
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_inspect_segments (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    bool               must_have_factory_refdata = false;
    uint32_t           addr;
    uint32_t           num_bytes;
    fsp_err_t          err = FSP_SUCCESS;
    rm_vee_seg_hdr_t * p_current_segment;
    rm_vee_seg_hdr_t * p_active_segment;
    flash_event_t      event;

    /* Set active segment to 0 (active seg not found yet) */
    p_ctrl->active_seg_addr = 0;

    /* Loop through each segment */
    for (uint32_t i = 0; i < p_ctrl->p_cfg->num_segments; i++)
    {
        addr = p_ctrl->p_cfg->start_addr + (i * p_ctrl->segment_size);

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT

        /* Set flag if on final segment and have not found active segment yet and refdata should be present. */
        if ((p_ctrl->active_seg_addr == 0) && (i == (p_ctrl->p_cfg->num_segments - 1)) &&
            (0 != p_ctrl->p_cfg->ref_data_size))
        {
            must_have_factory_refdata = true;
        }
#endif

        /* See if segment header is blank */
        err = rm_vee_blocking_blankcheck(p_ctrl, addr, sizeof(rm_vee_seg_hdr_t), &event);
        if (FSP_SUCCESS != err)
        {
            break;
        }

        /* If header is blank, make sure record area is blank (refresh or erase may have been interrupted). */
        if (FLASH_EVENT_BLANK == event)
        {
            /* Get size of record data area */
            num_bytes = p_ctrl->segment_size;

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
            if (must_have_factory_refdata == true)
            {
                num_bytes -= RM_VEE_FLASH_REF_DATA_AREA_SIZE;
            }
#endif

            /* See if any record data present (should not be any) */
            err = rm_vee_blocking_blankcheck(p_ctrl, addr, num_bytes, &event);
            if ((FSP_SUCCESS == err) && (FLASH_EVENT_NOT_BLANK == event))
            {
                /* Erase segment if reference data not present */
                err = rm_vee_blocking_erase_segment(p_ctrl, addr, must_have_factory_refdata);
            }
        }
        else
        {
            /* If header is not blank, see if has valid header */
            p_current_segment = (rm_vee_seg_hdr_t *) addr;

            if (RM_VEE_FLASH_VALID_CODE == p_current_segment->valid_code)
            {
                /* If another active segment was already found, erase the older segment */
                if (p_ctrl->active_seg_addr != 0)
                {
                    p_active_segment = (rm_vee_seg_hdr_t *) p_ctrl->active_seg_addr;

                    if (p_current_segment->refresh_cnt > p_active_segment->refresh_cnt)
                    {
                        /* Current segment is newer, erase older */
                        err =
                            rm_vee_blocking_erase(p_ctrl, p_ctrl->active_seg_addr,
                                                  (p_ctrl->segment_size / RM_VEE_FLASH_DF_BLOCK_SIZE));
                        p_ctrl->active_seg_addr = addr;
                    }
                    else
                    {
                        /* Else current segment is older */
                        err = rm_vee_blocking_erase(p_ctrl, addr, (p_ctrl->segment_size / RM_VEE_FLASH_DF_BLOCK_SIZE));
                    }
                }
                else
                {
                    /* Save this segment as active segment */
                    p_ctrl->active_seg_addr = addr;
                }
            }
            else
            {
                /* Erase segment if reference data not present */
                err = rm_vee_blocking_erase_segment(p_ctrl, addr, must_have_factory_refdata);
            }
        }

        /* If a flash operation has failed break out of the loop */
        if (FSP_SUCCESS != err)
        {
            break;
        }
    }

    /* If no active segment found, set highest flash segment as active in driver control structure. */
    if (0 == p_ctrl->active_seg_addr)
    {
        p_ctrl->active_seg_addr = RM_VEE_FLASH_LOGICAL_END_ADDRESS - p_ctrl->segment_size;

        /* Make segment active in flash if no errors were encountered */
        if (FSP_SUCCESS == err)
        {
            p_ctrl->seg_hdr.refresh_cnt = 0;
            p_ctrl->seg_hdr.valid_code  = RM_VEE_FLASH_VALID_CODE;
            err = rm_vee_blocking_write(p_ctrl,
                                        (uint32_t) &p_ctrl->seg_hdr,
                                        RM_VEE_FLASH_LOGICAL_END_ADDRESS - p_ctrl->segment_size,
                                        sizeof(rm_vee_seg_hdr_t));
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function erases the segment specified IF it does not contain reference data.
 *
 * @param  p_ctrl                   Pointer to the control block
 * @param  seg_addr                 Address of segment to erase.
 * @param  contains_refdata         true = segment contains reference data. Segment will not be erased.
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_blocking_erase_segment (rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                                uint32_t                             seg_addr,
                                                bool                                 contains_refdata)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Erase segment only if reference data not present */
    if (false == contains_refdata)
    {
        err = rm_vee_blocking_erase(p_ctrl, seg_addr, (p_ctrl->segment_size / RM_VEE_FLASH_DF_BLOCK_SIZE));
    }
    else
    {
        err = FSP_ERR_NOT_INITIALIZED;
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function walks through the active segment and loads the offset for the start of each record found
 * into p_ctrl->rec_offset[] using the record ID as the array index. When the last record is found,
 * p_ctrl->next_write_addr is loaded with the next available address to write a record to.
 *
 * @param  p_ctrl                   Pointer to the control block
 * @param  initial_load             true = Use blankcheck to determine end of record area.
 *                                      (called by Open() or VEE_CMD_FORMAT. State=RM_VEE_FLASH_PRV_STATES_UNITIALIZED)
 *                                      false = Use p_ctrl->refresh_src_rec_end_addr to determine end of record area.
 *                                      (called by failed Refresh process. Need to reload p_ctrl->rec_offset[] with original segment)
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_load_record_table (rm_vee_flash_instance_ctrl_t * const p_ctrl, bool initial_load)
{
    rm_vee_rec_hdr_t * p_hdr;
    fsp_err_t          err = FSP_SUCCESS;
    uint32_t           addr;
    rm_vee_rec_end_t * p_end;
    flash_event_t      event = FLASH_EVENT_BLANK;

    /* Get start of record area */
    addr = p_ctrl->active_seg_addr + sizeof(rm_vee_seg_hdr_t);;

    /* Get end of record area */
    p_ctrl->ref_hdr_addr  = p_ctrl->active_seg_addr + p_ctrl->segment_size;
    p_ctrl->ref_hdr_addr -= RM_VEE_FLASH_REF_DATA_AREA_SIZE;

    /* Loop through every record until find empty space */
    while (addr < p_ctrl->ref_hdr_addr)
    {
        /* Exit loop when no more records found */
        if (initial_load == true)
        {
            /* When this function is called by Open() or VEE_CMD_FORMAT, stop when find blank flash */
            err = rm_vee_blocking_blankcheck(p_ctrl, addr, RM_VEE_FLASH_DF_WRITE_SIZE, &event);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            if (FLASH_EVENT_BLANK == event)
            {
                break;
            }
        }
        else
        {
            /* When this function is called by failed Refresh, stop when at end address from original segment */
            if (addr == p_ctrl->refresh_src_rec_end_addr)
            {
                break;
            }
        }

        /* Get header for current record */
        p_hdr = (rm_vee_rec_hdr_t *) addr;

        /* Variable length records */
        if (RM_VEE_FLASH_REC_DATA_MAX_SIZE >= p_hdr->length)
        {
            p_end = (rm_vee_rec_end_t *) RM_VEE_ADDRESS_ALIGN(addr + sizeof(rm_vee_rec_hdr_t) + p_hdr->length);
        }
        else
        {
            err = FSP_ERR_NOT_INITIALIZED;
            break;
        }

        /* Save record offset if complete record found (reset may have occurred during a write) */
        if (RM_VEE_FLASH_VALID_CODE == p_end->valid_code)
        {
            p_ctrl->p_cfg->rec_offset[p_end->id] = (uint16_t) (addr - p_ctrl->active_seg_addr);

            /* Save for statusGet */
            p_ctrl->last_id = p_end->id;
        }
        else
        {
            err = FSP_ERR_NOT_INITIALIZED;
            break;
        }

        /* Set address to start of next record */
        addr = (uint32_t) p_end + sizeof(rm_vee_rec_end_t);
    }

    /* NOTE: The Refresh process copies records from locations identified by p_ctrl->p_cfg->rec_offset[].
     * During the Refresh process, the array is updated for the new record locations in the new segment.
     * Should the Refresh process fail, the array will contain a mixture of offsets from both segments.
     * In that case, p_ctrl->p_cfg->rec_offset[] should be set back to the original segment record locations.
     * Because Refresh may have failed due to flash error (vs Overflow condition), it is desirable
     *   not to perform more flash operations like blankcheck.
     * For this reason, where the record parsing should end is saved in p_ctrl->refresh_src_rec_end_addr.
     */
    p_ctrl->refresh_src_rec_end_addr = addr;

    /* NOTE: p_ctrl->next_write_addr is set to the next record location available to write.
     * This value will not be used if an error condition was encountered.
     */
    p_ctrl->next_write_addr = addr;

    return err;
}

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT

/*******************************************************************************************************************//**
 * This function inspects the reference data update area to see if it has been written to. The reference
 * data header is also inspected to see if a valid code exists (determines if updated data is real or
 * just garbage). The flags new_refdata_used and new_refdata_valid are set appropriately in the main
 * VEE control structure.
 *
 * @param  p_ctrl                   Pointer to the control block
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_inspect_new_refdata (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    uint32_t           addr;
    rm_vee_ref_hdr_t * p_hdr;
    flash_event_t      event;

    /* Get refdata header address */
    addr = p_ctrl->active_seg_addr + (p_ctrl->segment_size - RM_VEE_FLASH_REF_DATA_AREA_SIZE);

    err = rm_vee_blocking_blankcheck(p_ctrl, addr, sizeof(rm_vee_ref_hdr_t), &event);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (FLASH_EVENT_BLANK == event)
    {
        /* Header never written. Update area should be blank. See if incomplete write occurred */
        addr += sizeof(rm_vee_ref_hdr_t);

        /* Just blankcheck first few bytes; app may not use entire reserved area */
        err = rm_vee_blocking_blankcheck(p_ctrl, addr, RM_VEE_FLASH_DF_WRITE_SIZE, &event);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (FLASH_EVENT_NOT_BLANK == event)
        {
            err = FSP_ERR_NOT_INITIALIZED;
        }
    }
    else
    {
        /* Header written. Make sure is valid. */
        p_hdr = (rm_vee_ref_hdr_t *) addr;
        if (RM_VEE_FLASH_VALID_CODE == p_hdr->valid_code)
        {
            p_ctrl->new_refdata_valid = true;
        }
        else
        {
            err = FSP_ERR_NOT_INITIALIZED;
        }
    }

    addr = p_ctrl->active_seg_addr + (p_ctrl->segment_size - p_ctrl->p_cfg->ref_data_size);

    fsp_err_t err2 = rm_vee_blocking_blankcheck(p_ctrl, addr, RM_VEE_FLASH_DF_WRITE_SIZE, &event);
    FSP_ERROR_RETURN(FSP_SUCCESS == err2, err2);

    if (FLASH_EVENT_NOT_BLANK == event)
    {
        p_ctrl->factory_refdata = true;
    }

    return err;
}

#endif

/*******************************************************************************************************************//**
 * This function performs a blankcheck on the number of bytes passed in starting at the address specified.
 * This function blocks until the flash operation completes. A failure condition should never occur unless
 * bad flash hardware exists. If flash does fail, the error event is stored in flash_err_event in the
 * main control structure.
 *
 * @param  p_ctrl                   Pointer to the control block
 * @param  addr                     Address to start blankcheck (already verified on FLASH_CF_MIN_PGM_SIZE boundary)
 * @param  num_bytes                Number of bytes to blankcheck
 *                                  (already verified to be multiple of FLASH_CF_MIN_PGM_SIZE bytes)
 * @param  p_event                Destination loaded with FLASH_EVENT_BLANK if address range specified is blank
 *                                  Destination loaded with FLASH_EVENT_NOT_BLANK if address range specified is not blank
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 **********************************************************************************************************************/
static fsp_err_t rm_vee_blocking_blankcheck (rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                             uint32_t                             addr,
                                             uint32_t                             num_bytes,
                                             flash_event_t                      * p_event)
{
    uint32_t       i;
    fsp_err_t      err = FSP_SUCCESS;
    flash_result_t result;

    /* Clear interrupt-occurred flag */
    p_ctrl->irq_flag = false;

    /* Start blankcheck. "result" ignored because in BGO mode. */
    err = p_ctrl->p_flash->p_api->blankCheck(p_ctrl->p_flash->p_ctrl, addr, num_bytes, &result);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Poll for interrupt complete. Do timeout check in case app disabled interrupts.
     * Blankcheck is for RM_VEE_FLASH_DF_WRITE_SIZE to p_ctrl->segment_size bytes.
     */
    for (i = 0; i < RM_VEE_FLASH_TIMEOUT_US; i++)
    {
        if (p_ctrl->irq_flag == true)
        {
            break;
        }

        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
    }

    *p_event = p_ctrl->flash_event;

    FSP_ERROR_RETURN(RM_VEE_FLASH_TIMEOUT_US != i, FSP_ERR_TIMEOUT);

    if ((FLASH_EVENT_BLANK != p_ctrl->flash_event) && (FLASH_EVENT_NOT_BLANK != p_ctrl->flash_event))
    {
        p_ctrl->flash_err_event = p_ctrl->flash_event;
        err = FSP_ERR_PE_FAILURE;
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function erases the number of blocks specified starting at the address specified. This function
 * blocks until the erase operation completes. A failure condition should never occur unless bad flash
 * hardware exists. If flash does fail, the error event is stored in flash_err_event in the main
 * control structure.
 *
 * @param  p_ctrl                Pointer to the control block
 * @param  addr                  Block address to start erase
 * @param  num_blocks            Number of blocks to erase
 *
 * @retval FSP_SUCCESS           Successful.
 * @retval FSP_ERR_PE_FAILURE    This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT       Flash write timed out (Should not be possible when flash bgo is used).
 **********************************************************************************************************************/
static fsp_err_t rm_vee_blocking_erase (rm_vee_flash_instance_ctrl_t * const p_ctrl, uint32_t addr, uint32_t num_blocks)
{
    uint32_t  i;
    fsp_err_t err = FSP_SUCCESS;

    /* Clear interrupt-occurred flag */
    p_ctrl->irq_flag = false;

    err = p_ctrl->p_flash->p_api->erase(p_ctrl->p_flash->p_ctrl, addr, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Poll for interrupt complete. Do timeout check in case app disabled interrupts.
     * Erase is for (p_ctrl->segment_size/RM_VEE_FLASH_DF_BLOCK_SIZE).
     */
    for (i = 0; (i < RM_VEE_FLASH_TIMEOUT_US) && (p_ctrl->irq_flag != true); i++)
    {
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
    }

    FSP_ERROR_RETURN(RM_VEE_FLASH_TIMEOUT_US != i, FSP_ERR_TIMEOUT);

    if (FLASH_EVENT_ERASE_COMPLETE != p_ctrl->flash_event)
    {
        p_ctrl->flash_err_event = p_ctrl->flash_event;
        err = FSP_ERR_PE_FAILURE;
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function writes the num_bytes from src addr to dst_addr. This function blocks until the write
 * operation completes. A failure condition should never occur unless bad flash hardware exists. If flash
 * does fail, the error event is stored in flash_err_event in the main control structure.
 *
 * @param  p_ctrl                Pointer to the control block
 * @param  src_addr              Address of data to write (already verified to be on FLASH_CF_MIN_PGM_SIZE boundary)
 * @param  dst_addr              Address to write to (already verified to be on FLASH_CF_MIN_PGM_SIZE boundary)
 * @param  num_bytes             Number of bytes to write
 *
 * @retval FSP_SUCCESS           Successful.
 * @retval FSP_ERR_PE_FAILURE    This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT       Flash write timed out (Should not be possible when flash bgo is used).
 **********************************************************************************************************************/
static fsp_err_t rm_vee_blocking_write (rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                        uint32_t                             src_addr,
                                        uint32_t                             dst_addr,
                                        uint32_t                             num_bytes)
{
    uint32_t  i;
    fsp_err_t err = FSP_SUCCESS;

    /* Clear interrupt-occurred flag */
    p_ctrl->irq_flag = false;

    err = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl, src_addr, dst_addr, num_bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Poll for interrupt complete. Do timeout check in case app disabled interrupts.
     * Write is for sizeof(rm_vee_seg_hdr_t) to p_ctrl->p_cfg->ref_data_size bytes.
     */
    for (i = 0; i < RM_VEE_FLASH_TIMEOUT_US; i++)
    {
        if (p_ctrl->irq_flag == true)
        {
            break;
        }

        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
    }

    FSP_ERROR_RETURN(RM_VEE_FLASH_TIMEOUT_US != i, FSP_ERR_TIMEOUT);

    if (FLASH_EVENT_WRITE_COMPLETE != p_ctrl->flash_event)
    {
        p_ctrl->flash_err_event = p_ctrl->flash_event;
        err = FSP_ERR_PE_FAILURE;
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function determines if there is enough space left in the record area to write the new record.
 * If insufficient space is available, a refresh process is initiated. If sufficient space does exist,
 * a write process is initiated. For variable length records, a record header is written first. For fixed
 * length records, the header is omitted and the record data is written immediately. This function does
 * not block for write completion.
 *
 * @param  p_ctrl                   Pointer to the control block
 * @param  rec_id                   ID for record
 * @param  p_rec_data             Pointer to record data to write
 * @param  num_bytes                Number of bytes to write
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_internal_write_rec (rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                            uint32_t                             rec_id,
                                            uint8_t const * const                p_rec_data,
                                            uint32_t                             num_bytes)
{
    fsp_err_t err;

    /* Check if space available */
    if (RM_VEE_ADDRESS_ALIGN(p_ctrl->next_write_addr + RM_VEE_FLASH_REC_OVERHEAD + num_bytes) <= p_ctrl->ref_hdr_addr)
    {
        /* Got space. Save values needed at interrupt level. Though the header is only written when variable length
         * records are configured, its contents are still used for fixed length records too.
         */
        p_ctrl->rec_end.id     = (uint16_t) rec_id;
        p_ctrl->rec_hdr.length = (uint16_t) num_bytes;

        /* NOTE: The ".offset" field is technically not needed for the record (originally was ".pad").
         * It serves the purpose of "passing a value" to the callback function for efficiency in avoiding
         * a lengthy calculation later.
         */
        p_ctrl->rec_hdr.offset = (uint16_t) (p_ctrl->next_write_addr - p_ctrl->active_seg_addr);

        /* Initiate record write */
        p_ctrl->state      = RM_VEE_FLASH_PRV_STATES_WRITE_REC_HDR;
        p_ctrl->p_rec_data = p_rec_data;
        err                = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                                           (uint32_t) &p_ctrl->rec_hdr,
                                                           p_ctrl->next_write_addr,
                                                           (uint32_t) sizeof(rm_vee_rec_hdr_t));
    }
    else
    {
        /* Start refresh */
        err = rm_vee_start_seg_refresh(p_ctrl,
                                       RM_VEE_FLASH_PRV_REFRESH_RECORD_OVFL,
                                       rec_id,
                                       (uint32_t) p_rec_data,
                                       num_bytes);
    }

    return err;
}

/*******************************************************************************************************************//**
 * The VEE driver is locked prior to calling this function. The next segment is set as active in the VEE
 * driver control structure and the driver mode is changed to RM_VEE_FLASH_PRV_MODE_REFRESH. If this function is called
 * due to RM_VEE_FLASH_PRV_REFRESH_RECORD_OVFL (lack of record space), the refresh begins with writing the record passed
 * in. Otherwise, the refresh begins with the first offset found in p_ctrl->rec_offset[]. Because flash cannot be
 * read and written to at the same time, the records (and reference data) are copied first into an interim
 * RAM buffer then written to flash. Ideally, the buffer is large enough to hold the largest record so only
 * one flash write is required (unlike the 2 or 3 required when a record is initially written). If the
 * buffer is not large enough, the data is transferred in buffer-size chunks until the entire record/
 * reference data is transferred.
 *
 * @param  p_ctrl                   Pointer to the control block
 * @param  refresh_type             Indicates contents of other arguments/cause of refresh.
 * @param  rec_id                   Record ID if refresh type is RM_VEE_FLASH_PRV_REFRESH_RECORD_OVFL. NULL otherwise.
 * @param  addr                     Address of data to write. NULL if refresh type is RM_VEE_FLASH_PRV_REFRESH_USER_REQ.
 * @param  num_bytes                Number of bytes to write. NULL if refresh type is RM_VEE_FLASH_PRV_REFRESH_USER_REQ.
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_start_seg_refresh (rm_vee_flash_instance_ctrl_t * const p_ctrl,
                                           rm_vee_flash_refresh_refresh_t       refresh_type,
                                           uint32_t                             rec_id,
                                           uint32_t                             addr,
                                           uint32_t                             num_bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  new_seg_addr;

    /* Set refresh mode */
    p_ctrl->mode         = RM_VEE_FLASH_PRV_MODE_REFRESH;
    p_ctrl->refresh_type = refresh_type;

    /* Determine first record ID to refresh if not passed in */
    if (RM_VEE_FLASH_PRV_REFRESH_RECORD_OVFL != refresh_type)
    {
        for (rec_id = 0; rec_id <= p_ctrl->p_cfg->record_max_id; rec_id++)
        {
            if (p_ctrl->p_cfg->rec_offset[rec_id] != 0)
            {
                break;
            }
        }
    }

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
    if (0 != p_ctrl->p_cfg->ref_data_size)
    {
        /* Determine reference data refresh source */
        if (RM_VEE_FLASH_PRV_REFRESH_REFDATA_OVFL == refresh_type)
        {
            /* NOTE: The user cannot modify the new RAM reference data until refresh is complete! */
            p_ctrl->refresh_src_refdata_addr = addr;
        }
        else if (true == p_ctrl->new_refdata_valid)
        {
            p_ctrl->refresh_src_refdata_addr = p_ctrl->active_seg_addr +
                                               (p_ctrl->segment_size - (2 * p_ctrl->p_cfg->ref_data_size));
        }
        else
        {
            p_ctrl->refresh_src_refdata_addr = p_ctrl->active_seg_addr +
                                               (p_ctrl->segment_size - p_ctrl->p_cfg->ref_data_size);
        }
    }
#endif

    /* Get refresh segment address. Handle wrap-around case. */
    new_seg_addr = p_ctrl->active_seg_addr + p_ctrl->segment_size;
    if (RM_VEE_FLASH_LOGICAL_END_ADDRESS == new_seg_addr)
    {
        new_seg_addr = p_ctrl->p_cfg->start_addr;
    }

    /* Setup control structure for new segment */
    p_ctrl->refresh_src_seg_addr = p_ctrl->active_seg_addr;
    p_ctrl->active_seg_addr      = new_seg_addr;
    p_ctrl->ref_hdr_addr         = p_ctrl->active_seg_addr + (p_ctrl->segment_size - RM_VEE_FLASH_REF_DATA_AREA_SIZE);

    /* If record(s) exist to refresh, start a record write */
    if (rec_id <= p_ctrl->p_cfg->record_max_id)
    {
        p_ctrl->next_write_addr = new_seg_addr + sizeof(rm_vee_seg_hdr_t);

        /* NOTE: "start_rec_id" is the ID (index of p_ctrl->p_cfg->rec_offset[]) of the first record copied.
         * Refresh walks through p_ctrl->p_cfg->rec_offset[] (including wrap around) using "cur_rec_id" as the index.
         * When "cur_rec_id" matches "start_rec_id" again, record copying is complete.
         */
        p_ctrl->refresh_start_rec_id = (uint16_t) rec_id;
        p_ctrl->refresh_cur_rec_id   = (uint16_t) rec_id;

        if (RM_VEE_FLASH_PRV_REFRESH_RECORD_OVFL == refresh_type)
        {
            /* Write the record passed in */
            err = rm_vee_internal_write_rec(p_ctrl, rec_id, (uint8_t *) addr, num_bytes);
        }
        else
        {
            /* Write the record from previous segment */
            err = rm_vee_init_record_xfer(p_ctrl, rec_id);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            err = rm_vee_xfer_next_chunk(p_ctrl, RM_VEE_FLASH_PRV_STATES_WRITE_REC_REFRESH);
        }
    }
    else
    {
        /* No records exist.*/
#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT

        /* If reference data exists, start data copy */
        if (RM_VEE_FLASH_PRV_REFRESH_REFDATA_OVFL == refresh_type)
        {
            /* Write data passed in */
            p_ctrl->refresh_xfer_bytes_left = 0;
            p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_REFDATA;
            err           =
                p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                              addr,
                                              p_ctrl->active_seg_addr +
                                              (p_ctrl->segment_size - p_ctrl->p_cfg->ref_data_size),
                                              p_ctrl->p_cfg->ref_data_size);
        }
        else if ((true == p_ctrl->factory_refdata) || (true == p_ctrl->new_refdata_valid))
        {
            /* Copy data from flash */
            rm_vee_init_refdata_xfer(p_ctrl);

            err = rm_vee_xfer_next_chunk(p_ctrl, RM_VEE_FLASH_PRV_STATES_WRITE_REFDATA);
        }
        else
#endif
        {
            /* Highly obscure case where no data exists, but the last segment has an invalid segment header */
            err = rm_vee_write_seg_hdr(p_ctrl);
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to the control block
 * @param[in]     p_args     Pointer to arguments on stack
 **********************************************************************************************************************/
static void rm_vee_call_callback (rm_vee_flash_instance_ctrl_t * p_ctrl, rm_vee_callback_args_t * p_args)
{
    rm_vee_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    rm_vee_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = p_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args_memory;

        /* Copy the stacked args to callback memory */
        *p_args_memory = *p_args;
    }

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args_memory);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        rm_vee_flash_prv_ns_callback p_callback = (rm_vee_flash_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args_memory);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args_memory);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * This function is called at the interrupt level every time a flash operation completes. If this function
 * is called during VEE initialization, a global flag is set and the function exits immediately (driver is
 * blocking). In normal operation, this function handles the main state machine for the driver. The state
 * machine includes the following sequences:
 *
 * Normal Mode:
 * Write a record: [RM_VEE_FLASH_PRV_STATES_WRITE_REC_HDR], WRITE_REC_DATA, WRITE_REC_END
 *    (header only written with variable recs)
 * Write reference data: RM_VEE_FLASH_PRV_STATES_WRITE_NEW_REFDATA. WRITE_NEW_REFDATA_HDR
 *
 * Refresh Mode:
 * [RM_VEE_FLASH_PRV_STATES_WRITE_REC_HDR, WRITE_REC_DATA, WRITE_REC_END] if started with RECORD_OVFL
 * RM_VEE_FLASH_PRV_STATES_WRITE_REC_REFRESH (uses interim RAM buffer; and how start if not RECORD_OVFL)
 * RM_VEE_FLASH_PRV_STATES_WRITE_REF_DATA
 * RM_VEE_FLASH_PRV_STATES_WRITE_SEG_HDR
 * RM_VEE_FLASH_PRV_STATES_ERASE_SEG
 *
 * @param  p_args    callback arguments used to process the flash event.
 **********************************************************************************************************************/
void rm_vee_flash_callback (flash_callback_args_t * p_args)
{
    flash_event_t flash_event             = p_args->event;
    rm_vee_flash_instance_ctrl_t * p_ctrl = (rm_vee_flash_instance_ctrl_t *) p_args->p_context;
    fsp_err_t err = FSP_SUCCESS;

    p_ctrl->flash_event = flash_event;

    /* Starting up. Blocking on various events. Just set flag. */
    if (RM_VEE_FLASH_PRV_STATES_UNINITIALIZED == p_ctrl->state)
    {
        p_ctrl->irq_flag = true;

        return;
    }

    /* WRITE COMPLETE state machine */
    if (FLASH_EVENT_WRITE_COMPLETE == p_ctrl->flash_event)
    {
        switch (p_ctrl->state)
        {
            case RM_VEE_FLASH_PRV_STATES_WRITE_REC_HDR:
            {
                /* Record header write complete (variable length records only) */
                p_ctrl->next_write_addr += sizeof(rm_vee_rec_hdr_t);

                uint32_t src    = (uint32_t) p_ctrl->p_rec_data;
                uint32_t length = p_ctrl->rec_hdr.length;

                p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA;

                /* If the record can be written in one write set the next state to write end. */
                if (0 == (p_ctrl->rec_hdr.length % RM_VEE_FLASH_DF_WRITE_SIZE))
                {
                    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA;
                }
                else if (RM_VEE_FLASH_DF_WRITE_SIZE > p_ctrl->rec_hdr.length)
                {
                    /* The record is smaller than the DF write size and needs to be buffered before write. */
                    memset(&p_ctrl->data_buffer[0], 0, RM_VEE_FLASH_DF_WRITE_SIZE);
                    memcpy(&p_ctrl->data_buffer[0],
                           p_ctrl->p_rec_data,
                           p_ctrl->rec_hdr.length & RM_VEE_FLASH_DF_WRITE_MASK);
                    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA;
                    src           = (uint32_t) &p_ctrl->data_buffer[0];
                    length        = RM_VEE_FLASH_DF_WRITE_SIZE;
                }
                else
                {
                    /* The end of the record must be written seperately. */
                    length        = length & (~RM_VEE_FLASH_DF_WRITE_MASK);
                    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA_TAIL;
                }

                /* Write record data */
                err = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl, src, p_ctrl->next_write_addr, length);
                break;
            }

            case RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA_TAIL:
            {
                uint32_t written = p_ctrl->rec_hdr.length & (~RM_VEE_FLASH_DF_WRITE_MASK);

                p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA;

                /* Buffer the last few bytes of the record and pad with zeros */
                memset(&p_ctrl->data_buffer[0], 0, RM_VEE_FLASH_DF_WRITE_SIZE);
                memcpy(&p_ctrl->data_buffer[0],
                       p_ctrl->p_rec_data + written,
                       p_ctrl->rec_hdr.length & RM_VEE_FLASH_DF_WRITE_MASK);

                p_ctrl->next_write_addr += written;

                /* Write record data */
                err = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                                    (uint32_t) &p_ctrl->data_buffer[0],
                                                    p_ctrl->next_write_addr,
                                                    RM_VEE_FLASH_DF_WRITE_SIZE);
                break;
            }

            case RM_VEE_FLASH_PRV_STATES_WRITE_REC_DATA:
            {
                /* Record data write complete */
                if (0 != (p_ctrl->rec_hdr.length % RM_VEE_FLASH_DF_WRITE_SIZE))
                {
                    p_ctrl->next_write_addr += RM_VEE_FLASH_DF_WRITE_SIZE;
                }
                else
                {
                    p_ctrl->next_write_addr += p_ctrl->rec_hdr.length;
                }

                /* Write record trailer */
                p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_REC_END;
                err           = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                                              (uint32_t) &p_ctrl->rec_end,
                                                              p_ctrl->next_write_addr,
                                                              sizeof(rm_vee_rec_end_t));
                break;
            }

            case RM_VEE_FLASH_PRV_STATES_WRITE_REC_END:
            {
                /* Record trailer write complete */
                p_ctrl->last_id          = p_ctrl->rec_end.id;
                p_ctrl->next_write_addr += sizeof(rm_vee_rec_end_t);

                p_ctrl->p_cfg->rec_offset[p_ctrl->rec_end.id] = p_ctrl->rec_hdr.offset;

                if (RM_VEE_FLASH_PRV_MODE_NORMAL == p_ctrl->mode)
                {
                    /* Done writing if in normal mode */
                    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_READY;

                    /* Save address for Refresh to end record copy */
                    p_ctrl->refresh_src_rec_end_addr = p_ctrl->next_write_addr;
                }
                else
                {
                    /* Begin copying next rec, refdata; or write segment hdr */
                    err = rm_vee_refresh_next_data_source(p_ctrl);
                }

                break;
            }

            case RM_VEE_FLASH_PRV_STATES_WRITE_REC_REFRESH:
            {
                if (0 != p_ctrl->refresh_xfer_bytes_left)
                {
                    /* Continue transferring current record */
                    err = rm_vee_xfer_next_chunk(p_ctrl, RM_VEE_FLASH_PRV_STATES_WRITE_REC_REFRESH);
                }
                else
                {
                    /* Begin copying next rec, refdata; or write segment hdr */
                    err = rm_vee_refresh_next_data_source(p_ctrl);
                }

                break;
            }

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT
            case RM_VEE_FLASH_PRV_STATES_WRITE_REFDATA:
            {
                if (0 != p_ctrl->refresh_xfer_bytes_left)
                {
                    /* Continue transferring refdata */
                    err = rm_vee_xfer_next_chunk(p_ctrl, RM_VEE_FLASH_PRV_STATES_WRITE_REFDATA);
                }
                else
                {
                    /* Finished copying reference data. Write segment header (mark segment active). */
                    p_ctrl->factory_refdata = true;
                    err = rm_vee_write_seg_hdr(p_ctrl);
                }

                break;
            }

            case RM_VEE_FLASH_PRV_STATES_WRITE_NEW_REFDATA:
            {
                /* New refdata location written; write the header to show that it is used */
                p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_NEW_REFDATA_HDR;
                err           = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                                              (uint32_t) &p_ctrl->ref_hdr,
                                                              p_ctrl->ref_hdr_addr,
                                                              sizeof(rm_vee_ref_hdr_t));

                break;
            }

            case RM_VEE_FLASH_PRV_STATES_WRITE_NEW_REFDATA_HDR:
            {
                /* New refdata header written; refdata update complete */
                p_ctrl->new_refdata_valid = true;
                p_ctrl->state             = RM_VEE_FLASH_PRV_STATES_READY;
                break;
            }
#endif

            case RM_VEE_FLASH_PRV_STATES_WRITE_SEG_HDR:
            {
                /* Segment header (from a Refresh) write complete */

                /* Logically, one would update the reference data info after that write completes in
                 * RM_VEE_FLASH_PRV_STATES_WRITE_REFDATA. But functionally there is no harm in waiting until now to do it.
                 * And an advantage of doing it here is that if writing the segment header fails, there is no need
                 * to re-inspect the reference data area when doing a restore to the previous segment.
                 */
                p_ctrl->ref_hdr_addr = p_ctrl->active_seg_addr +
                                       (p_ctrl->segment_size - RM_VEE_FLASH_REF_DATA_AREA_SIZE);
                p_ctrl->new_refdata_valid = false;

                /* Since copying data is done, set location for next record-write */
                p_ctrl->next_write_addr = p_ctrl->refresh_dst_rec_end_addr;

                /* Erase previous segment */
                p_ctrl->state = RM_VEE_FLASH_PRV_STATES_ERASE_SEG;

                err =
                    p_ctrl->p_flash->p_api->erase(p_ctrl->p_flash->p_ctrl, p_ctrl->refresh_src_seg_addr,
                                                  (p_ctrl->segment_size / RM_VEE_FLASH_DF_BLOCK_SIZE));
                break;
            }

            default:
            {
                /* Do nothing. */
                break;
            }
        }
    }
    else if (FLASH_EVENT_ERASE_COMPLETE == p_ctrl->flash_event)
    {
        /* Old segment erased; refresh operation complete; return to normal operations */
        p_ctrl->mode  = RM_VEE_FLASH_PRV_MODE_NORMAL;
        p_ctrl->state = RM_VEE_FLASH_PRV_STATES_READY;
    }
    else
    {
        /* ERROR EVENT */

        /* If a flash failure occurred during a Refresh, restore driver control structures such that
         * the previous segment's data can still be read providing the previous segment was not in
         * the process of being erased.
         */
        if ((RM_VEE_FLASH_PRV_MODE_REFRESH == p_ctrl->mode) && (RM_VEE_FLASH_PRV_STATES_ERASE_SEG != p_ctrl->state))
        {
            err = rm_vee_restore_previous_seg(p_ctrl);
        }

        p_ctrl->flash_err_event = p_ctrl->flash_event;
        p_ctrl->mode            = RM_VEE_FLASH_PRV_MODE_FLASH_PE_FAIL;
        p_ctrl->state           = RM_VEE_FLASH_PRV_STATES_READY;
    }

    rm_vee_flash_err_handle(p_ctrl, err);

    if ((RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state) && (NULL != p_ctrl->p_callback))
    {
        rm_vee_callback_args_t args;

        rm_vee_state_get(p_ctrl, &args.state);
        args.p_context = p_ctrl->p_context;
        rm_vee_call_callback(p_ctrl, &args);
    }
}

static void rm_vee_flash_err_handle (rm_vee_flash_instance_ctrl_t * const p_ctrl, fsp_err_t err)
{
    if ((FSP_SUCCESS != err) &&
        ((p_ctrl->mode == RM_VEE_FLASH_PRV_MODE_NORMAL) || (p_ctrl->mode == RM_VEE_FLASH_PRV_MODE_REFRESH)))
    {
        p_ctrl->mode  = RM_VEE_FLASH_PRV_MODE_FLASH_PE_FAIL;
        p_ctrl->state = RM_VEE_FLASH_PRV_STATES_READY;
    }
}

/*******************************************************************************************************************//**
 * This function determines the next ID with a record in flash. If it has yet to be copied to the new
 * segment, the write process is started. If all records have been copied, a write is started for the most
 * recent reference data. If no reference data is present, a write is started for the segment header.
 *
 * @param  p_ctrl                   Pointer to the control block
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_refresh_next_data_source (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    uint32_t  id;
    fsp_err_t err = FSP_SUCCESS;

    /* Get next record ID */
    id = rm_vee_get_next_id(p_ctrl);

    /* Write next record if more remain */
    if (id != p_ctrl->refresh_start_rec_id)
    {
        err = rm_vee_init_record_xfer(p_ctrl, id);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = rm_vee_xfer_next_chunk(p_ctrl, RM_VEE_FLASH_PRV_STATES_WRITE_REC_REFRESH);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
    else
    {
        /* No more records; save address for next record write location.
         * Must save because next_write_addr is overwritten if reference data exists. */
        p_ctrl->refresh_dst_rec_end_addr = p_ctrl->next_write_addr;

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT

        /* Determine what to write next */
        if ((0 != p_ctrl->p_cfg->ref_data_size) &&
            ((true == p_ctrl->factory_refdata) || (true == p_ctrl->new_refdata_valid)))
        {
            /* Write reference data */
            rm_vee_init_refdata_xfer(p_ctrl);

            err = rm_vee_xfer_next_chunk(p_ctrl, RM_VEE_FLASH_PRV_STATES_WRITE_REFDATA);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }
        else
#endif
        {
            /* No reference data; mark segment as active by writing segment header */
            err = rm_vee_write_seg_hdr(p_ctrl);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function gets the next ID after p_ctrl->refresh_cur_rec_id in p_ctrl->rec_offset[]. If the end of the
 * array is reached, this function wraps around and begins searching again. The index of the array
 * corresponds to the ID value. An offset value of 0 (illegal value) indicates that no record is present
 * for that ID.
 *
 * @param  p_ctrl                Pointer to the control block
 *
 * @retval Next ID which has a record in flash.
 **********************************************************************************************************************/
static uint32_t rm_vee_get_next_id (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    /* NOTE: This function is only called after a record has been written.
     * Because at least one record does exist, this can never be an infinite loop.
     * Worst case: The "next" ID is the one just written.
     */
    do
    {
        /* Increment id; check for wrap around */
        if (++p_ctrl->refresh_cur_rec_id > p_ctrl->p_cfg->record_max_id)
        {
            p_ctrl->refresh_cur_rec_id = 0;
        }

        /* Stop when valid offset found */
    } while (p_ctrl->p_cfg->rec_offset[p_ctrl->refresh_cur_rec_id] == 0);

    return p_ctrl->refresh_cur_rec_id;
}

/*******************************************************************************************************************//**
 * This function initializes in global control structures the source address and length of the record to
 * be copied over as specified by "id" during the refresh process. The new offset for the soon to be
 * copied record is saved in the segment offset array (p_ctrl->rec_offset[]) for later lookup.
 *
 * @param  p_ctrl                   Pointer to the control block
 * @param  id                       ID for record to be copied to the refresh segment
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_init_record_xfer (rm_vee_flash_instance_ctrl_t * const p_ctrl, uint32_t id)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Get record address to transfer */
    p_ctrl->refresh_xfer_src_addr = p_ctrl->refresh_src_seg_addr + p_ctrl->p_cfg->rec_offset[id];

    /* Get complete record size (number of bytes to transfer) */
    rm_vee_rec_hdr_t * p_hdr = (rm_vee_rec_hdr_t *) p_ctrl->refresh_xfer_src_addr;

    p_ctrl->refresh_xfer_bytes_left = RM_VEE_ADDRESS_ALIGN(p_hdr->length + RM_VEE_FLASH_REC_OVERHEAD);

    /* Save offset of record's new location */
    p_ctrl->p_cfg->rec_offset[id] = (uint16_t) (p_ctrl->next_write_addr - p_ctrl->active_seg_addr);

    /* If this record will not fit in remaining record area, then bad configuration exists. Go into error mode. */
    if ((p_ctrl->next_write_addr + p_ctrl->refresh_xfer_bytes_left) >
        (p_ctrl->active_seg_addr + (p_ctrl->segment_size - RM_VEE_FLASH_REF_DATA_AREA_SIZE)))
    {
        /* Make previous segment active again and set error mode */
        err = rm_vee_restore_previous_seg(p_ctrl);

        p_ctrl->mode  = RM_VEE_FLASH_PRV_MODE_OVERFLOW;
        p_ctrl->state = RM_VEE_FLASH_PRV_STATES_READY;
    }

    return err;
}

#if RM_VEE_FLASH_CFG_REF_DATA_SUPPORT

/*******************************************************************************************************************//**
 * This function initializes in global control structures the source address and length of the latest
 * reference data to be copied over during the refresh process. The "next_write_addr" is also updated
 * for the destination address in the new segment.
 *
 * @param  p_ctrl        Pointer to the control block
 **********************************************************************************************************************/
static void rm_vee_init_refdata_xfer (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    /* Get source refdata address to transfer */
    p_ctrl->refresh_xfer_src_addr = p_ctrl->refresh_src_refdata_addr;

    /* Set destination addr */
    p_ctrl->next_write_addr = p_ctrl->active_seg_addr + (p_ctrl->segment_size - p_ctrl->p_cfg->ref_data_size);

    /* Set refdata size (number of bytes to transfer) */
    p_ctrl->refresh_xfer_bytes_left = (uint16_t) p_ctrl->p_cfg->ref_data_size;
}

#endif

/*******************************************************************************************************************//**
 * This function determines how much data is left to transfer, and copies whichever is less (remaining
 * data or buffer size) into a ram buffer. The state passed into this function specifies the type of
 * data being transferred, and is stored in the control structure so the callback function knows what step
 * to process next is. Finally, the write process for the data is started.
 *
 * @param  p_ctrl    Pointer to the control block
 * @param  state     State to store in the vee control structure (specifies transfer type - record or reference data).
 *
 * @retval FSP_SUCCESS    Successfully started transfer of next chunk of data.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_xfer_next_chunk (rm_vee_flash_instance_ctrl_t * const p_ctrl, rm_vee_flash_prv_states_t state)
{
    uint32_t  length;
    fsp_err_t err = FSP_SUCCESS;

    /* Do not write if mode is overflow. Error condition will be handled in state machine. */
    if (RM_VEE_FLASH_PRV_MODE_OVERFLOW != p_ctrl->mode)
    {
        /* Determine number of bytes to transfer in this chunk */
        if (RM_VEE_FLASH_REFRESH_BUFFER_SIZE <= p_ctrl->refresh_xfer_bytes_left)
        {
            length = RM_VEE_FLASH_REFRESH_BUFFER_SIZE;
        }
        else
        {
            length = p_ctrl->refresh_xfer_bytes_left;
        }

        /* Copy next chunk into buffer */
        memcpy((void *) p_ctrl->xfer_buf, (void *) p_ctrl->refresh_xfer_src_addr, length);

        /* Set state so know how what data is being transferred (record or reference info) */
        p_ctrl->state = state;

        /* Start write */
        err = p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                            (uint32_t) p_ctrl->xfer_buf,
                                            p_ctrl->next_write_addr,
                                            length);

        /* Update transfer info */
        p_ctrl->next_write_addr        += length;
        p_ctrl->refresh_xfer_src_addr  += length;
        p_ctrl->refresh_xfer_bytes_left = p_ctrl->refresh_xfer_bytes_left - length;
    }

    return err;
}

/*******************************************************************************************************************//**
 * A flash error may occur at any time during a Refresh. There may be only 1 record, half the records,
 * or only part of reference data transferred when flash fails. To allow reads after failure, the
 * driver reverts to the last known good data, which is the previous (src) segment. This function
 * sets the active segment back to the previous segment and reloads the record offset table for reads.
 *
 * @param  p_ctrl                   Pointer to the control block
 *
 * @retval FSP_SUCCESS              Successful.
 * @retval FSP_ERR_PE_FAILURE       This error indicates that a flash programming, erase, or blankcheck operation has failed
 * @retval FSP_ERR_TIMEOUT          Flash write timed out (Should not be possible when flash bgo is used).
 * @retval FSP_ERR_NOT_INITIALIZED  Corruption found. A refresh is required.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_restore_previous_seg (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    p_ctrl->active_seg_addr = p_ctrl->refresh_src_seg_addr;

    /* In the case of a Refresh aborting due to discovering an Overflow condition, all but one entry in
     * p_ctrl->p_cfg->rec_offset[] will be overwritten, so erase entire array before reloading offsets.
     */
    memset((void *) &p_ctrl->p_cfg->rec_offset[0], 0,
           ((p_ctrl->p_cfg->record_max_id + 1) * sizeof(p_ctrl->p_cfg->rec_offset[0])));

    return rm_vee_load_record_table(p_ctrl, false);

    /* NOTE: The reference data info (p_ctrl->ref_hdr_addr/new_refdata_used/new_refdata_valid) is changed only
     * after the new segment header has been written. And this function is only called if that has not happened
     * yet, so there is nothing relative to reference data that needs to be restored here.
     */
}

/*******************************************************************************************************************//**
 * This function starts the write process for a segment header.
 *
 * @param  p_ctrl              Pointer to the control block
 **********************************************************************************************************************/
static fsp_err_t rm_vee_write_seg_hdr (rm_vee_flash_instance_ctrl_t * const p_ctrl)
{
    p_ctrl->state = RM_VEE_FLASH_PRV_STATES_WRITE_SEG_HDR;
    p_ctrl->seg_hdr.refresh_cnt++;

    return p_ctrl->p_flash->p_api->write(p_ctrl->p_flash->p_ctrl,
                                         (uint32_t) &p_ctrl->seg_hdr,
                                         p_ctrl->active_seg_addr,
                                         sizeof(rm_vee_seg_hdr_t));
}

/*******************************************************************************************************************//**
 * This function starts the write process for a segment header.
 *
 * @param  p_ctrl              Pointer to the control block
 * @param  p_state             Pointer to the rm_vee state
 *
 * @retval FSP_SUCCESS              Successful.
 **********************************************************************************************************************/
static fsp_err_t rm_vee_state_get (rm_vee_flash_instance_ctrl_t * const p_ctrl, rm_vee_state_t * p_state)
{
    if (RM_VEE_FLASH_PRV_MODE_NORMAL == p_ctrl->mode)
    {
        if (RM_VEE_FLASH_PRV_STATES_READY == p_ctrl->state)
        {
            *p_state = RM_VEE_STATE_READY;
        }
        else
        {
            *p_state = RM_VEE_STATE_BUSY;
        }
    }
    else
    {
        *p_state = (rm_vee_state_t) p_ctrl->mode;
    }

    return FSP_SUCCESS;
}
