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
#include "rm_fs1015.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_FS1015_OPEN                      (0x673D448AUL) // Open state

/* Definitions of data size */
#define RM_FS1015_DATA_SIZE                 (3)

/* Definitions of table size */
#if RM_FS1015_CFG_DEVICE_TYPE
 #define RM_FS1015_TABLE_DATA_SIZE          (13)   // FS1015-1015
#else
 #define RM_FS1015_TABLE_DATA_SIZE          (9)    // FS1015-1005
#endif

/* Definitions of CheckSum and A/D data */
#define RM_FS1015_DATA_VALID                (0x00) // Valid data
#define RM_FS1015_MASK_CHECKSUM_0X00FF      (0x00FF)

/* Definitions for Calculation */
#define RM_FS1015_CALC_DECIMAL_VALUE_100    (100.0F)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global function prototypes
 **********************************************************************************************************************/
void rm_fs1015_callback(rm_comms_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_fs1015_flow_calculate(rm_fsxxxx_data_t * const p_fs1015_data);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Tables for FS1015 */
const int16_t g_fs1015_counts_table[RM_FS1015_TABLE_DATA_SIZE] =
{
#if RM_FS1015_CFG_DEVICE_TYPE
    409, 1203, 1597,  1908,  2187, 2400, 2629, 2801, 3006, 3178, 3309, 3563, 3686, // FS1015-1015
#else
    409, 915,  1522,  2066,  2523, 2908, 3256, 3572, 3686,                         // FS1015-1005
#endif
};

const float g_fs1015_flow_table[RM_FS1015_TABLE_DATA_SIZE] =
{
#if RM_FS1015_CFG_DEVICE_TYPE
    0.00F, 2.00F, 3.00F, 4.00F, 5.00F, 6.00F, 7.00F, 8.00F, 9.00F, 10.00F, 11.00F, 13.00F, 15.00F, // FS1015-1015
#else
    0.00F, 1.07F, 2.01F, 3.00F, 3.97F, 4.96F, 5.98F, 6.99F, 7.23F,                                 // FS1015-1005
#endif
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_fsxxxx_api_t const g_fsxxxx_on_fs1015 =
{
    .open          = RM_FS1015_Open,
    .close         = RM_FS1015_Close,
    .read          = RM_FS1015_Read,
    .dataCalculate = RM_FS1015_DataCalculate,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_FS1015
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the FS1015 Middle module. Implements @ref rm_fsxxxx_api_t::open.
 *
 * Example:
 * @snippet rm_fs1015_example.c RM_FS1015_Open
 *
 * @retval FSP_SUCCESS              FS1015 successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 **********************************************************************************************************************/
fsp_err_t RM_FS1015_Open (rm_fsxxxx_ctrl_t * const p_api_ctrl, rm_fsxxxx_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_fs1015_instance_ctrl_t * p_ctrl = (rm_fs1015_instance_ctrl_t *) p_api_ctrl;

#if RM_FS1015_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_instance);
    FSP_ERROR_RETURN(RM_FS1015_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg                = p_cfg;
    p_ctrl->open                 = RM_FS1015_OPEN;
    p_ctrl->p_comms_i2c_instance = p_cfg->p_instance;
    p_ctrl->p_context            = p_cfg->p_context;
    p_ctrl->p_callback           = p_cfg->p_callback;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified FS1015 control block. Implements @ref rm_fsxxxx_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_FS1015_Close (rm_fsxxxx_ctrl_t * const p_api_ctrl)
{
    rm_fs1015_instance_ctrl_t * p_ctrl = (rm_fs1015_instance_ctrl_t *) p_api_ctrl;

#if RM_FS1015_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_FS1015_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reads ADC data from FS1015.
 * Implements @ref rm_fsxxxx_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_FS1015_Read (rm_fsxxxx_ctrl_t * const p_api_ctrl, rm_fsxxxx_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_fs1015_instance_ctrl_t * p_ctrl = (rm_fs1015_instance_ctrl_t *) p_api_ctrl;

#if RM_FS1015_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_FS1015_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read 3 bytes raw data (See figure 2 in FS1015 datasheet.) */
    err =
        p_ctrl->p_comms_i2c_instance->p_api->read(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                  (uint8_t *) p_raw_data,
                                                  RM_FS1015_DATA_SIZE);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculates flow [m/sec] from ADC data.
 * Implements @ref rm_fsxxxx_api_t::dataCalculate.
 *
 * @retval FSP_SUCCESS                  Successfully data decoded.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_SENSOR_INVALID_DATA  Data is invalid.
 **********************************************************************************************************************/
fsp_err_t RM_FS1015_DataCalculate (rm_fsxxxx_ctrl_t * const     p_api_ctrl,
                                   rm_fsxxxx_raw_data_t * const p_raw_data,
                                   rm_fsxxxx_data_t * const     p_fs1015_data)
{
    rm_fs1015_instance_ctrl_t * p_ctrl = (rm_fs1015_instance_ctrl_t *) p_api_ctrl;
    uint8_t  checksum;
    uint16_t sum;
    uint16_t i;

#if RM_FS1015_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_fs1015_data);
    FSP_ERROR_RETURN(RM_FS1015_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Check checksum */
    sum = 0;
    for (i = 0; i < RM_FS1015_DATA_SIZE; i++)
    {
        sum = (uint16_t) (sum + (uint16_t) p_raw_data->adc_data[i]);
    }

    checksum = (uint8_t) (sum & RM_FS1015_MASK_CHECKSUM_0X00FF);
    FSP_ERROR_RETURN(RM_FS1015_DATA_VALID == checksum, FSP_ERR_SENSOR_INVALID_DATA);

    /* Calculate output count */
    p_fs1015_data->count =
        (uint32_t) ((p_raw_data->adc_data[1] << 8) + p_raw_data->adc_data[2]);

    /* Calculate flow [m/sec] */
    rm_fs1015_flow_calculate(p_fs1015_data);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup FS1015)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief FS1015 callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_fs1015_callback (rm_comms_callback_args_t * p_args)
{
    rm_fs1015_instance_ctrl_t * p_ctrl = (rm_fs1015_instance_ctrl_t *) p_args->p_context;
    rm_fsxxxx_callback_args_t   fs1015_callback_args;

    /* Set context */
    fs1015_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            fs1015_callback_args.event = RM_FSXXXX_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            fs1015_callback_args.event = RM_FSXXXX_EVENT_ERROR;
            break;
        }
    }

    if (NULL != p_ctrl->p_callback)
    {
        /* Call callback function */
        p_ctrl->p_callback(&fs1015_callback_args);
    }
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal fs1015 private function.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Calculate flow.
 **********************************************************************************************************************/
static void rm_fs1015_flow_calculate (rm_fsxxxx_data_t * const p_fs1015_data)
{
    uint8_t i;
    float   slope;
    float   intercept;
    float   flow = 0.00F;
    int16_t count;

    /* Set count */
    count = (int16_t) p_fs1015_data->count;

    /* Calculate flow using tables */
    if (g_fs1015_counts_table[0] > count)
    {
        flow = g_fs1015_flow_table[0];
    }
    else if (g_fs1015_counts_table[RM_FS1015_TABLE_DATA_SIZE - 1] <= count)
    {
        flow = g_fs1015_flow_table[RM_FS1015_TABLE_DATA_SIZE - 1];
    }
    else
    {
        for (i = 1; i < RM_FS1015_TABLE_DATA_SIZE; i++)
        {
            if (g_fs1015_counts_table[i] > count)
            {
                /* Calculate slope */
                slope = (g_fs1015_flow_table[i - 1] - g_fs1015_flow_table[i]) /
                        (float) (g_fs1015_counts_table[i - 1] - g_fs1015_counts_table[i]);

                /* Calculate intercept */
                intercept = ((float) g_fs1015_counts_table[i - 1] * g_fs1015_flow_table[i] -
                             (float) g_fs1015_counts_table[i] * g_fs1015_flow_table[i - 1]) /
                            (float) (g_fs1015_counts_table[i - 1] - g_fs1015_counts_table[i]);

                /* Calculate flow */
                flow = slope * (float) count + intercept;
                break;
            }
        }
    }

    /* Set flow data */
    p_fs1015_data->flow.integer_part = (int16_t) flow;
    p_fs1015_data->flow.decimal_part =
        (int16_t) ((flow - (float) p_fs1015_data->flow.integer_part) * RM_FS1015_CALC_DECIMAL_VALUE_100);
}
