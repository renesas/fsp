/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_comms_smbus.h"
#include "rm_comms_i2c.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "OPEN" in ASCII, used to determine if middleware is open. */
#define RM_COMMS_SMBUS_OPEN                     (0x4F50454EUL) // Open state

/* This macro contains 32 data bytes + 1 command code byte + 2 count bytes + 1 PEC byte. Exclude 1 byte of slave
 * address. */
#define RM_COMMS_SMBUS_PROCESS_CALL_MAX_BYTE    (RM_COMMS_SMBUS_TRANSMISSION_MAX_BYTES - 1U)

/* This macro contains 32 data bytes + 1 command code byte + 1 count bytes + 1 PEC byte. Exclude 1 byte of slave
 * address and and 1 count byte. */
#define RM_COMMS_SMBUS_WRITE_MAX_BYTE           (RM_COMMS_SMBUS_TRANSMISSION_MAX_BYTES - 2U)

#define RM_COMMS_SMBUS_WRITE_OPERATION          (0x0)
#define RM_COMMS_SMBUS_READ_OPERATION           (0x1)

#define RM_COMMS_SMBUS_CRC_SEED_VAL_0           (0U) // Seed value 0 for PEC byte calculation

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#define GPT_OPEN_FLAG                           (0x00475054ULL)
#define ELC_OPEN_FLAG                           (0x00454C43ULL)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
__STATIC_INLINE void rm_comms_smbus_pec_byte_calculate(uint8_t const * p_data, uint32_t num_bytes, uint8_t * p_crc_val);
static fsp_err_t     rm_comms_smbus_setup_timer(rm_comms_smbus_instance_ctrl_t * const p_ctrl);

__STATIC_INLINE fsp_err_t rm_comms_smbus_update_mext_val(rm_comms_smbus_instance_ctrl_t * const p_ctrl);

#if BSP_CFG_RTOS
__STATIC_INLINE fsp_err_t rm_comms_smbus_semaphore_err_handler(rm_comms_i2c_instance_ctrl_t * const p_ctrl,
                                                               fsp_err_t                            semphr_err);

#endif

/**********************************************************************************************************************
 * Extern functions
 **********************************************************************************************************************/
extern fsp_err_t rm_comms_i2c_bus_status_check(rm_comms_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_comms_i2c_bus_read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest,
                                       uint32_t const bytes);
extern fsp_err_t rm_comms_i2c_bus_write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src,
                                        uint32_t const bytes);
extern fsp_err_t rm_comms_i2c_bus_write_read(rm_comms_ctrl_t * const            p_api_ctrl,
                                             rm_comms_write_read_params_t const write_read_params);
extern void rm_comms_i2c_process_in_callback(rm_comms_ctrl_t * const          p_api_ctrl,
                                             rm_comms_callback_args_t * const p_args);

#if BSP_CFG_RTOS
extern fsp_err_t rm_comms_i2c_os_recursive_mutex_acquire(rm_comms_i2c_mutex_t const * p_mutex, uint32_t const timeout);
extern fsp_err_t rm_comms_i2c_os_recursive_mutex_release(rm_comms_i2c_mutex_t const * p_mutex);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Store CRC 8-bit result as lookup table */
uint8_t const g_crc_lookup_table[] =
{
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15,
    0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
    0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5,
    0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85,
    0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
    0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2,
    0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32,
    0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
    0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c,
    0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec,
    0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
    0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c,
    0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b,
    0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
    0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb,
    0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb,
    0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3,
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_comms_api_t const g_comms_on_comms_smbus =
{
    .open        = RM_COMMS_SMBUS_Open,
    .read        = RM_COMMS_SMBUS_Read,
    .write       = RM_COMMS_SMBUS_Write,
    .writeRead   = RM_COMMS_SMBUS_WriteRead,
    .callbackSet = RM_COMMS_SMBUS_CallbackSet,
    .close       = RM_COMMS_SMBUS_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_SMBUS
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the SMBUS Comms module. Implements @ref rm_comms_api_t::open.
 *
 * @retval FSP_SUCCESS              Communications Middle module successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open. This module can only be opened once.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SMBUS_Open (rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    rm_comms_smbus_instance_ctrl_t * p_ctrl = (rm_comms_smbus_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(RM_COMMS_SMBUS_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    rm_comms_smbus_extended_cfg_t * p_smbus_extend_cfg = (rm_comms_smbus_extended_cfg_t *) p_cfg->p_extend;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_smbus_extend_cfg);
    FSP_ASSERT(NULL != p_smbus_extend_cfg->p_comms_i2c_ctrl);
    FSP_ASSERT(NULL != p_smbus_extend_cfg->p_comms_i2c_extend_cfg);
    FSP_ASSERT(NULL != p_smbus_extend_cfg->p_comms_i2c_extend_cfg->p_driver_instance);
    FSP_ASSERT(NULL != p_smbus_extend_cfg->p_comms_i2c_extend_cfg->p_elc);
    FSP_ASSERT(NULL != p_smbus_extend_cfg->p_comms_i2c_extend_cfg->p_timer);
    FSP_ASSERT(NULL != p_cfg->p_lower_level_cfg);
#endif

    p_ctrl->p_comms_i2c_ctrl = p_smbus_extend_cfg->p_comms_i2c_ctrl;
    rm_comms_i2c_instance_ctrl_t * p_comms_i2c_ctrl = p_ctrl->p_comms_i2c_ctrl;

    p_comms_i2c_ctrl->p_cfg           = p_cfg;
    p_comms_i2c_ctrl->p_bus           = p_smbus_extend_cfg->p_comms_i2c_extend_cfg;
    p_comms_i2c_ctrl->p_callback      = p_cfg->p_callback;
    p_comms_i2c_ctrl->p_context       = p_ctrl;
    p_comms_i2c_ctrl->smbus_operation = true;
    p_ctrl->p_context                 = p_cfg->p_context;

    /* Set lower level driver configuration */
    p_comms_i2c_ctrl->p_lower_level_cfg = (void *) p_cfg->p_lower_level_cfg;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE

    /* Ensure that IIC already opened */
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_comms_i2c_bus_status_check(p_comms_i2c_ctrl), FSP_ERR_COMMS_BUS_NOT_OPEN);

    /* If both ELC and GPT instance pointers are not NULL, which mean SMBus is being used. Check open flag of ELC and
     * GPT to ensure that those modules already opened.
     */
    elc_instance_t   * p_elc_instance   = (elc_instance_t *) p_comms_i2c_ctrl->p_bus->p_elc;
    timer_instance_t * p_timer_instance = (timer_instance_t *) p_comms_i2c_ctrl->p_bus->p_timer;

    FSP_ERROR_RETURN(ELC_OPEN_FLAG == ((elc_instance_ctrl_t *) p_elc_instance->p_ctrl)->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(GPT_OPEN_FLAG == ((gpt_instance_ctrl_t *) p_timer_instance->p_ctrl)->open, FSP_ERR_NOT_OPEN);
#endif

    err =
        ((elc_instance_t *) p_comms_i2c_ctrl->p_bus->p_elc)->p_api->enable(((elc_instance_t *) p_comms_i2c_ctrl->p_bus->
                                                                            p_elc)->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set open flag */
    p_ctrl->open = RM_COMMS_SMBUS_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified SMBUS Comms module. Implements @ref rm_comms_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SMBUS_Close (rm_comms_ctrl_t * const p_api_ctrl)
{
    rm_comms_smbus_instance_ctrl_t * p_ctrl = (rm_comms_smbus_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_COMMS_SMBUS_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Updates the SMBUS Comms callback. Implements @ref rm_comms_api_t::callbackSet.
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SMBUS_CallbackSet (rm_comms_ctrl_t * const p_api_ctrl,
                                      void (                * p_callback)(rm_comms_callback_args_t *),
                                      void * const            p_context)
{
    rm_comms_smbus_instance_ctrl_t * p_ctrl = (rm_comms_smbus_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(RM_COMMS_SMBUS_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_comms_i2c_ctrl->p_callback = p_callback;
    p_ctrl->p_context = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Performs a read from the SMBUS device. Implements @ref rm_comms_api_t::read.
 *
 * @note When Packet Error Check (PEC) is used, size of destination buffer and the number of reading bytes must have
 * 1-byte in addition for PEC byte.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_SIZE     Read data size is invalid.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SMBUS_Read (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    /* This API only handle for Receive byte command of SMBus. As the result, bytes will be 1 or 2 (1 data byte and
     * 1 optional PEC byte) for following the SMBus protocol standard. Ignore the param to eliminate compile warning.
     */
    FSP_PARAMETER_NOT_USED(bytes);

    fsp_err_t err = FSP_SUCCESS;

    rm_comms_smbus_instance_ctrl_t * p_ctrl = (rm_comms_smbus_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_dest);
    FSP_ERROR_RETURN(1 == bytes, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN(RM_COMMS_SMBUS_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint8_t read_size = 1U;

    rm_comms_i2c_instance_ctrl_t * p_comms_i2c_ctrl = p_ctrl->p_comms_i2c_ctrl;

    if (((rm_comms_smbus_extended_cfg_t *) (p_comms_i2c_ctrl->p_cfg->p_extend))->pec_enable)
    {
        read_size = 2U;                // 1 data byte + PEC byte
    }

    /* Assign read buffer, size and crc_seed value for processing in callback function */
    p_ctrl->receive_crc_seed = RM_COMMS_SMBUS_CRC_SEED_VAL_0;

    err = rm_comms_smbus_setup_timer(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_ctrl->timer_is_enabled = false;

    err = rm_comms_i2c_bus_read(p_comms_i2c_ctrl, p_dest, read_size);

#if BSP_CFG_RTOS

    /* Check the error returned from lower layer */
    err = rm_comms_smbus_semaphore_err_handler(p_comms_i2c_ctrl, err);
#endif

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Performs a write from the SMBUS device. Implements @ref rm_comms_api_t::write.
 *
 * @retval FSP_SUCCESS              Successfully writing data .
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_SIZE     Transfer data size is invalid.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SMBUS_Write (rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;

    rm_comms_smbus_instance_ctrl_t * p_ctrl = (rm_comms_smbus_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ERROR_RETURN(RM_COMMS_SMBUS_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_i2c_instance_ctrl_t * p_comms_i2c_ctrl = p_ctrl->p_comms_i2c_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    if (((rm_comms_smbus_extended_cfg_t *) (p_comms_i2c_ctrl->p_cfg->p_extend))->pec_enable)
    {
        FSP_ERROR_RETURN(RM_COMMS_SMBUS_WRITE_MAX_BYTE >= bytes, FSP_ERR_INVALID_SIZE);
    }
    else
    {
        FSP_ERROR_RETURN(RM_COMMS_SMBUS_WRITE_MAX_BYTE > bytes, FSP_ERR_INVALID_SIZE);
    }
#endif

    uint8_t * p_write;
    uint32_t  write_byte;

    if (!(((rm_comms_smbus_extended_cfg_t *) (p_comms_i2c_ctrl->p_cfg->p_extend))->pec_enable) || (0 == bytes))
    {
        /* Handle for SMBus command Write API without PEC and Quick command */
        write_byte = bytes;
        p_write    = p_src;
    }
    else
    {
        /* Handle for SMBus command Write API with PEC byte */
        uint8_t slave_addr;
        uint8_t pec_byte = RM_COMMS_SMBUS_CRC_SEED_VAL_0;

        i2c_master_cfg_t * p_lower_level_cfg = (i2c_master_cfg_t *) p_comms_i2c_ctrl->p_lower_level_cfg;

        slave_addr = (uint8_t) ((p_lower_level_cfg->slave << 1) | (uint8_t) RM_COMMS_SMBUS_WRITE_OPERATION);

        /* Prepare data for PEC byte calculation */
        p_ctrl->write_buff[0] = slave_addr;
        memcpy(&p_ctrl->write_buff[1], p_src, bytes);

        write_byte = bytes + 1U;       // numbers of byte of p_src + 1 PEC byte

        /* Calculate PEC byte for transmit data with seed value of 0 */
        rm_comms_smbus_pec_byte_calculate(p_ctrl->write_buff, write_byte, &pec_byte);

        p_ctrl->write_buff[write_byte] = pec_byte; // Assign PEC byte to last byte of data stream

        p_write = &p_ctrl->write_buff[1];
    }

    err = rm_comms_smbus_setup_timer(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_ctrl->timer_is_enabled = false;

    err = rm_comms_i2c_bus_write(p_comms_i2c_ctrl, p_write, write_byte);

#if BSP_CFG_RTOS

    /* Check the error returned from lower layer */
    err = rm_comms_smbus_semaphore_err_handler(p_comms_i2c_ctrl, err);
#endif

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Performs a write to, then a read from the SMBUS device. Implements @ref rm_comms_api_t::writeRead.
 *
 * @note When Packet Error Check (PEC) is used, size of destination buffer and the number of reading bytes must have
 * 1-byte in addition for PEC byte.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_SIZE     Transfer data size is invalid.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SMBUS_WriteRead (rm_comms_ctrl_t * const            p_api_ctrl,
                                    rm_comms_write_read_params_t const write_read_params)
{
    fsp_err_t err = FSP_SUCCESS;

    rm_comms_smbus_instance_ctrl_t * p_ctrl = (rm_comms_smbus_instance_ctrl_t *) p_api_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    uint8_t total_bytes = write_read_params.src_bytes + write_read_params.dest_bytes;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != write_read_params.p_src);
    FSP_ASSERT(NULL != write_read_params.p_dest);
    FSP_ASSERT(0 < write_read_params.src_bytes);
    FSP_ASSERT(1 < write_read_params.dest_bytes);

    FSP_ERROR_RETURN(RM_COMMS_SMBUS_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_comms_i2c_instance_ctrl_t * p_comms_i2c_ctrl = p_ctrl->p_comms_i2c_ctrl;

#if RM_COMMS_SMBUS_CFG_PARAM_CHECKING_ENABLE
    if (((rm_comms_smbus_extended_cfg_t *) (p_comms_i2c_ctrl->p_cfg->p_extend))->pec_enable)
    {
        FSP_ERROR_RETURN(RM_COMMS_SMBUS_PROCESS_CALL_MAX_BYTE >= total_bytes, FSP_ERR_INVALID_SIZE);
    }
    else
    {
        FSP_ERROR_RETURN(RM_COMMS_SMBUS_PROCESS_CALL_MAX_BYTE > total_bytes, FSP_ERR_INVALID_SIZE);
    }
#endif

    if (((rm_comms_smbus_extended_cfg_t *) (p_comms_i2c_ctrl->p_cfg->p_extend))->pec_enable)
    {
        uint8_t  slave_addr;
        uint32_t crc_calculate_num_byte;

        i2c_master_cfg_t * p_lower_level_cfg = (i2c_master_cfg_t *) p_comms_i2c_ctrl->p_lower_level_cfg;

        crc_calculate_num_byte = write_read_params.src_bytes + 1U; // 1 slave addr byte + n-bytes data of p_src
        slave_addr             = (uint8_t) ((p_lower_level_cfg->slave << 1) | (uint8_t) RM_COMMS_SMBUS_WRITE_OPERATION);

        /* Prepare data for PEC byte calculation */
        p_ctrl->write_buff[0] = slave_addr;
        memcpy(&p_ctrl->write_buff[1], write_read_params.p_src, write_read_params.src_bytes);

        /* Calculate PEC byte */
        p_ctrl->receive_crc_seed = RM_COMMS_SMBUS_CRC_SEED_VAL_0;
        rm_comms_smbus_pec_byte_calculate(p_ctrl->write_buff, crc_calculate_num_byte, &(p_ctrl->receive_crc_seed));
    }

    err = rm_comms_smbus_setup_timer(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_ctrl->timer_is_enabled = false;

    err = rm_comms_i2c_bus_write_read(p_comms_i2c_ctrl, write_read_params);

#if BSP_CFG_RTOS

    /* Check the error returned from lower layer */
    err = rm_comms_smbus_semaphore_err_handler(p_comms_i2c_ctrl, err);
#endif

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMM_SMBUS)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Calculate PEC byte with CRC-8 (x^8 + x^2 + x + 1) format by using lookup table.
 *
 * @retval PEC byte.
 **********************************************************************************************************************/
__STATIC_INLINE void rm_comms_smbus_pec_byte_calculate (uint8_t const * p_data, uint32_t num_bytes, uint8_t * p_crc_val)
{
    uint8_t cur_data;
    uint8_t prv_data;

    /* Init the first value */
    prv_data = *p_crc_val;

    /* The CRC 8 has 255 possible result which stored at g_crc_lookup_table. For each input byte (except the seed value)
     * we will perform the XOR operation between current and previous data byte.
     *
     * The result of XOR operation above is the location of the CRC result in lookup table. After got the CRC value from
     * the table, assign back to prv_data for next calculation. When all bytes of data calculated, prv_data is returned
     * as PEC byte of entire data stream.
     */
    for (uint16_t i = 0; i < num_bytes; i++)
    {
        cur_data = prv_data ^ p_data[i];
        prv_data = g_crc_lookup_table[cur_data];
    }

    *p_crc_val = prv_data;
}

/*******************************************************************************************************************//**
 * @brief Update MEXT count value.
 *
 * @retval FSP_SUCCESS Update value for MEXT successfully.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
__STATIC_INLINE fsp_err_t rm_comms_smbus_update_mext_val (rm_comms_smbus_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    rm_comms_i2c_instance_ctrl_t * p_comms_i2c_ctrl = p_ctrl->p_comms_i2c_ctrl;

    timer_instance_t * p_timer_instance = (timer_instance_t *) p_comms_i2c_ctrl->p_bus->p_timer;

    timer_api_t         * p_gpt_api        = (timer_api_t *) p_timer_instance->p_api;
    gpt_instance_ctrl_t * p_gpt_ctrl       = (gpt_instance_ctrl_t *) p_timer_instance->p_ctrl;
    gpt_extended_cfg_t  * p_gpt_extend_cfg = (gpt_extended_cfg_t *) p_timer_instance->p_cfg->p_extend;

    if (!p_ctrl->timer_is_enabled)
    {
        err = p_gpt_api->stop(p_gpt_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = p_gpt_api->enable(p_gpt_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        p_ctrl->timer_is_enabled = true;
    }

    /* Get current count and set new value for compare match, this operation help to ensure transmission time between
     * ACK events will not exceed 10 (ms). */
    timer_status_t cur_status;

    err = p_gpt_api->statusGet(p_gpt_ctrl, &cur_status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    uint32_t next_val = cur_status.counter + p_gpt_extend_cfg->compare_match_value[0];

    err = p_gpt_api->compareMatchSet(p_gpt_ctrl, next_val, TIMER_COMPARE_MATCH_A);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Start the GPT again */
    err = p_gpt_api->start(p_gpt_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief  Setup timer for SMBus before starting the transmission when using I2C Shared Bus.
 *
 * @retval FSP_SUCCESS              Successfully configured.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
static fsp_err_t rm_comms_smbus_setup_timer (rm_comms_smbus_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    rm_comms_i2c_instance_ctrl_t * p_iic_ctrl = p_ctrl->p_comms_i2c_ctrl;

    timer_instance_t * p_timer_instance = (timer_instance_t *) p_iic_ctrl->p_bus->p_timer;

    timer_api_t        * p_timer_api      = (timer_api_t *) p_timer_instance->p_api;
    timer_ctrl_t       * p_timer_ctrl     = p_timer_instance->p_ctrl;
    gpt_extended_cfg_t * p_gpt_extend_cfg = (gpt_extended_cfg_t *) p_timer_instance->p_cfg->p_extend;

#if BSP_CFG_RTOS
    err = rm_comms_i2c_os_recursive_mutex_acquire(p_iic_ctrl->p_bus->p_bus_recursive_mutex,
                                                  p_iic_ctrl->p_bus->bus_timeout);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Disable a linkage between elc and timers before starting off a new operation */
    err = p_timer_api->disable(p_timer_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Reset timer counter before starting off a new operation */
    err = p_timer_api->reset(p_timer_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set callback function and current control block */
    err = p_timer_api->callbackSet(p_timer_ctrl, rm_comms_smbus_timeout_callback, p_ctrl, NULL);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set 10 (ms) as compare match value */
    err = p_timer_api->compareMatchSet(p_timer_ctrl, p_gpt_extend_cfg->compare_match_value[0], TIMER_COMPARE_MATCH_A);

    return err;
}

#if BSP_CFG_RTOS

/*******************************************************************************************************************//**
 * @brief  Handling error when failed to acquire semaphore.
 *
 * @retval FSP_SUCCESS              Handling error successfully.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
__STATIC_INLINE fsp_err_t rm_comms_smbus_semaphore_err_handler (rm_comms_i2c_instance_ctrl_t * const p_api_ctrl,
                                                                fsp_err_t                            semphr_err)
{
    fsp_err_t timer_err = FSP_SUCCESS;
    fsp_err_t i2c_err   = FSP_SUCCESS;
    fsp_err_t mutex_err = FSP_SUCCESS;

    if (FSP_SUCCESS != semphr_err)
    {
        i2c_master_instance_t * p_driver_instance = (i2c_master_instance_t *) p_api_ctrl->p_bus->p_driver_instance;
        i2c_err = p_driver_instance->p_api->abort(p_driver_instance->p_ctrl);

        timer_instance_t * p_timer_instance = (timer_instance_t *) p_api_ctrl->p_bus->p_timer;
        timer_err = p_timer_instance->p_api->stop(p_timer_instance->p_ctrl);
    }

    /* Because mutex was locked 2 times, at rm_comms_smbus_setup_timer() and rm_comms_i2c_bus_reconfigure(), it's
     * necessary to release mutex 1 more time here, the other was released at lower layer. */
    if (NULL != p_api_ctrl->p_bus->p_bus_recursive_mutex)
    {
        mutex_err = rm_comms_i2c_os_recursive_mutex_release(p_api_ctrl->p_bus->p_bus_recursive_mutex);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == i2c_err, i2c_err);
    FSP_ERROR_RETURN(FSP_SUCCESS == timer_err, timer_err);
    FSP_ERROR_RETURN(FSP_SUCCESS == mutex_err, mutex_err);

    return semphr_err;
}

#endif

/*******************************************************************************************************************//**
 * @brief Common callback function called in the I2C driver callback function when SMBus is used.
 **********************************************************************************************************************/
void rm_comms_smbus_transmission_callback (i2c_master_callback_args_t * p_args)
{
    fsp_err_t err = FSP_SUCCESS;

    rm_comms_i2c_instance_ctrl_t   * p_comms_i2c_ctrl = (rm_comms_i2c_instance_ctrl_t *) (p_args->p_context);
    rm_comms_smbus_instance_ctrl_t * p_ctrl           =
        (rm_comms_smbus_instance_ctrl_t *) (p_comms_i2c_ctrl->p_context);

    rm_comms_callback_args_t comms_smbus_args;
    rm_comms_smbus_error_t   smbus_error;
    bool transition_complete_flag = false;

    /* Initialize the event */
    comms_smbus_args.event = RM_COMMS_EVENT_ERROR;

    /* Set context */
    comms_smbus_args.p_context = p_ctrl->p_context;

    /* Initialize the error block */
    smbus_error.smbus_event = RM_COMMS_SMBUS_NO_ERROR;

    /* Set event */
    switch (p_args->event)
    {
        case I2C_MASTER_EVENT_RX_COMPLETE:
        {
            /* Update the transition complete flag to call user callback */
            transition_complete_flag = true;

            comms_smbus_args.event = RM_COMMS_EVENT_OPERATION_COMPLETE;

            /* If PEC is used, calculate PEC byte from received data and compare with PEC byte with PEC byte from
             * received data.
             */
            if (((rm_comms_smbus_extended_cfg_t *) (p_comms_i2c_ctrl->p_cfg->p_extend))->pec_enable)
            {
                /* If PEC is used, start checking the PEC byte */
                uint8_t   slave_addr;
                uint8_t   ref_pec;
                uint8_t * p_read_buff;
                uint8_t   data_pec;

                i2c_master_cfg_t * p_lower_level_cfg = (i2c_master_cfg_t *) p_comms_i2c_ctrl->p_lower_level_cfg;

                p_read_buff = p_comms_i2c_ctrl->p_transfer_data;

                slave_addr =
                    (uint8_t) ((p_lower_level_cfg->slave << 1) | (uint8_t) RM_COMMS_SMBUS_READ_OPERATION);

                /* Calculate CRC value of slave address */
                data_pec = p_ctrl->receive_crc_seed;
                rm_comms_smbus_pec_byte_calculate(&slave_addr, 1U, &data_pec);

                /* After acquired CRC value of slave addr, this value will play as seed to generate the CRC value of
                 * read data.
                 *
                 * PEC byte in destination buffer will be excluded when calculate CRC value of read data.
                 */
                rm_comms_smbus_pec_byte_calculate(p_read_buff, (p_comms_i2c_ctrl->transfer_data_bytes - 1U), &data_pec);

                /* Get PEC byte from dest buffer */
                ref_pec = p_read_buff[p_comms_i2c_ctrl->transfer_data_bytes - 1U]; // PEC byte place at last byte of data stream

                /* Compare PEC byte and return event */
                if (ref_pec != data_pec)
                {
                    comms_smbus_args.event  = RM_COMMS_EVENT_ERROR;
                    smbus_error.smbus_event = RM_COMMS_SMBUS_DATA_CORRUPT;
                }
            }

            break;
        }

        case I2C_MASTER_EVENT_TX_COMPLETE:
        {
            /* If p_read_buff is NULL which mean middleware is implementing SMBus Write command, I2C raise TX complete
             * mean all data was written, middleware update event and invoke user's callback.
             */
            if (NULL == p_comms_i2c_ctrl->p_transfer_data)
            {
                comms_smbus_args.event = RM_COMMS_EVENT_OPERATION_COMPLETE;

                /* Set the transition flag as true to call user callback function */
                transition_complete_flag = true;
            }
            else
            {
                i2c_master_instance_t * p_iic_instance =
                    (i2c_master_instance_t *) p_comms_i2c_ctrl->p_bus->p_driver_instance;

                /* Update the compare match value and start the timer again, we do not need to stop the timer here
                 * because when IIC completed the transmission, interrupt raises and GPT was stopped by ELC. */
                err = rm_comms_smbus_update_mext_val(p_ctrl);

                if (FSP_SUCCESS != err)
                {
                    transition_complete_flag = true;
                    comms_smbus_args.event   = RM_COMMS_EVENT_ERROR;
                    smbus_error.smbus_event  = RM_COMMS_SMBUS_MISC_ERROR;
                }
                else
                {
                    /* When NULL != p_comms_i2c_ctrl->p_transfer_data, SMBus middleware is implementing WriteRead API. After receive I2C
                     * TX complete, invoke I2C Read API for start reading with restart.
                     */
                    err =
                        p_iic_instance->p_api->read(p_iic_instance->p_ctrl,
                                                    p_comms_i2c_ctrl->p_transfer_data,
                                                    p_comms_i2c_ctrl->transfer_data_bytes,
                                                    false);

                    if (FSP_SUCCESS != err)
                    {
                        transition_complete_flag = true;
                        comms_smbus_args.event   = RM_COMMS_EVENT_ERROR;
                        smbus_error.smbus_event  = RM_COMMS_SMBUS_MISC_ERROR;
                    }
                    else
                    {
                        /* Update the flag to avoid calling user callback since the transition has not complete */
                        transition_complete_flag = false;
                    }
                }
            }

            break;
        }

        case I2C_MASTER_EVENT_START:
        {
            timer_instance_t * p_timer_instance = (timer_instance_t *) p_comms_i2c_ctrl->p_bus->p_timer;

            err = p_timer_instance->p_api->start(p_timer_instance->p_ctrl);

            if (FSP_SUCCESS != err)
            {
                transition_complete_flag = true;
                comms_smbus_args.event   = RM_COMMS_EVENT_ERROR;
                smbus_error.smbus_event  = RM_COMMS_SMBUS_MISC_ERROR;
            }

            break;
        }

        case I2C_MASTER_EVENT_BYTE_ACK:
        {
            err = rm_comms_smbus_update_mext_val(p_ctrl);

            if (FSP_SUCCESS != err)
            {
                transition_complete_flag = true;
                comms_smbus_args.event   = RM_COMMS_EVENT_ERROR;
                smbus_error.smbus_event  = RM_COMMS_SMBUS_MISC_ERROR;
            }

            break;
        }

        case I2C_MASTER_EVENT_ABORTED:
        {
            i2c_master_instance_t * p_iic_instance =
                (i2c_master_instance_t *) p_comms_i2c_ctrl->p_bus->p_driver_instance;

            /* If IIC returned error before timer is enabled, which mean ELC cannot stop the timer via IIC event ,
             * stopping timer by software is needed. */
            if (!p_ctrl->timer_is_enabled)
            {
                timer_instance_t * p_timer_instance = (timer_instance_t *) p_comms_i2c_ctrl->p_bus->p_timer;

                p_timer_instance->p_api->stop(p_timer_instance->p_ctrl);
            }

            /* Safely abort RA I2C driver */
            p_iic_instance->p_api->abort(p_iic_instance->p_ctrl);

            /* Update the transition complete flag to call user callback*/
            transition_complete_flag = true;

            /* Update the event which returned to user's callback */
            comms_smbus_args.event  = RM_COMMS_EVENT_ERROR;
            smbus_error.smbus_event = RM_COMMS_SMBUS_MISC_ERROR;

            break;
        }

        default:
        {
            /* All possible events are handled by above case. Nothing to do here. */
        }
    }

    if (transition_complete_flag)
    {
        /* Assign error control block of current context to callback args */
        comms_smbus_args.p_instance_args = &smbus_error;

        rm_comms_i2c_process_in_callback(p_comms_i2c_ctrl, &comms_smbus_args);
    }
}

/*******************************************************************************************************************//**
 * @brief Callback function called in the GPT driver callback function when SMBus is used.
 **********************************************************************************************************************/
void rm_comms_smbus_timeout_callback (timer_callback_args_t * p_args)
{
    rm_comms_smbus_instance_ctrl_t * p_ctrl = (rm_comms_smbus_instance_ctrl_t *) (p_args->p_context);

    rm_comms_i2c_instance_ctrl_t * p_comms_i2c = p_ctrl->p_comms_i2c_ctrl;

    rm_comms_callback_args_t comms_smbus_args;
    rm_comms_smbus_error_t   smbus_error;

    /* Set context and return event */
    comms_smbus_args.p_context = p_comms_i2c->p_context;
    comms_smbus_args.event     = RM_COMMS_EVENT_ERROR;
    smbus_error.smbus_event    = RM_COMMS_SMBUS_NO_ERROR;

    i2c_master_instance_t const * p_iic_instance = p_comms_i2c->p_bus->p_driver_instance;

    /* Abort the current transmission */
    p_iic_instance->p_api->abort(p_iic_instance->p_ctrl);

    /* Because HW will not stop timer when compare match event hits, it's necessary to be stopped by software */
    if (TIMER_EVENT_COMPARE_A == p_args->event)
    {
        timer_instance_t * p_timer_instance = (timer_instance_t *) p_comms_i2c->p_bus->p_timer;

        smbus_error.smbus_event = RM_COMMS_SMBUS_MEXT_TIMEOUT;
        p_timer_instance->p_api->stop(p_timer_instance->p_ctrl);
    }
    else if (TIMER_EVENT_CYCLE_END == p_args->event)
    {
        smbus_error.smbus_event = RM_COMMS_SMBUS_SEXT_TIMEOUT;
    }
    else
    {
        /* Remain events of timer will be treated as miscellaneous error to SMBus because they're not expected
         * to be raised. */
        smbus_error.smbus_event = RM_COMMS_SMBUS_MISC_ERROR;
    }

    /* Assign error control block of current context to callback args */
    comms_smbus_args.p_instance_args = &smbus_error;

    rm_comms_i2c_process_in_callback(p_comms_i2c, &comms_smbus_args);
}
