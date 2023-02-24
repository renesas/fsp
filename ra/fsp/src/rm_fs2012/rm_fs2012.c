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
#include "rm_fs2012.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_FS2012_OPEN                      (0x536C7181UL) // Open state

/* Definitions of data size */
#define RM_FS2012_DATA_SIZE                 (2)

/* Definitions of A/D data */
#define RM_FS2012_MASK_DATA_UPPER_0X0F      (0x0F)

/* Definitions for Calculation */
#define RM_FS2012_CALC_DECIMAL_VALUE_100    (100.0F)
#if RM_FS2012_CFG_DEVICE_TYPE
 #define RM_FS2012_CALC_DEVISOR             (10.0F)   // FS2012-xxxx-LQ
#else
 #define RM_FS2012_CALC_DEVISOR             (1000.0F) // FS2012-xxxx-NG
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global function prototypes
 **********************************************************************************************************************/
void rm_fs2012_callback(rm_comms_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_fsxxxx_api_t const g_fsxxxx_on_fs2012 =
{
    .open          = RM_FS2012_Open,
    .close         = RM_FS2012_Close,
    .read          = RM_FS2012_Read,
    .dataCalculate = RM_FS2012_DataCalculate,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_FS2012
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the FS2012 Middle module. Implements @ref rm_fsxxxx_api_t::open.
 *
 * Example:
 * @snippet rm_fs2012_example.c RM_FS2012_Open
 *
 * @retval FSP_SUCCESS              FS2012 successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 **********************************************************************************************************************/
fsp_err_t RM_FS2012_Open (rm_fsxxxx_ctrl_t * const p_api_ctrl, rm_fsxxxx_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_fs2012_instance_ctrl_t * p_ctrl = (rm_fs2012_instance_ctrl_t *) p_api_ctrl;

#if RM_FS2012_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_instance);
    FSP_ERROR_RETURN(RM_FS2012_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg                = p_cfg;
    p_ctrl->open                 = RM_FS2012_OPEN;
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
 * @brief Disables specified FS2012 control block. Implements @ref rm_fsxxxx_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_FS2012_Close (rm_fsxxxx_ctrl_t * const p_api_ctrl)
{
    rm_fs2012_instance_ctrl_t * p_ctrl = (rm_fs2012_instance_ctrl_t *) p_api_ctrl;

#if RM_FS2012_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_FS2012_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reads ADC data from FS2012.
 * Implements @ref rm_fsxxxx_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_FS2012_Read (rm_fsxxxx_ctrl_t * const p_api_ctrl, rm_fsxxxx_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_fs2012_instance_ctrl_t * p_ctrl = (rm_fs2012_instance_ctrl_t *) p_api_ctrl;

#if RM_FS2012_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_FS2012_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read 2 bytes raw data (See chapter 8 in FS2012 datasheet.) */
    err =
        p_ctrl->p_comms_i2c_instance->p_api->read(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                  (uint8_t *) p_raw_data,
                                                  RM_FS2012_DATA_SIZE);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculates flow from ADC data.
 * Unit of Gas flow is SLPM (Standard liter per minute)
 * Unit of Liquid flow is SCCM (Standard cubic centimeter per minute)
 * Implements @ref rm_fsxxxx_api_t::dataCalculate.
 *
 * @retval FSP_SUCCESS                  Successfully data decoded.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_FS2012_DataCalculate (rm_fsxxxx_ctrl_t * const     p_api_ctrl,
                                   rm_fsxxxx_raw_data_t * const p_raw_data,
                                   rm_fsxxxx_data_t * const     p_fs2012_data)
{
    rm_fs2012_instance_ctrl_t * p_ctrl = (rm_fs2012_instance_ctrl_t *) p_api_ctrl;
    float flow;

#if RM_FS2012_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_fs2012_data);
    FSP_ERROR_RETURN(RM_FS2012_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Calculate flow (Gas : [SLPM], Liquid : [SCCM]) */
    flow = (float) ((p_raw_data->adc_data[0] << 8) + p_raw_data->adc_data[1]) / RM_FS2012_CALC_DEVISOR;

    /* Set flow data */
    p_fs2012_data->flow.integer_part = (int16_t) flow;
    p_fs2012_data->flow.decimal_part =
        (int16_t) ((flow - (float) p_fs2012_data->flow.integer_part) * RM_FS2012_CALC_DECIMAL_VALUE_100);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup FS2012)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief FS2012 callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_fs2012_callback (rm_comms_callback_args_t * p_args)
{
    rm_fs2012_instance_ctrl_t * p_ctrl = (rm_fs2012_instance_ctrl_t *) p_args->p_context;
    rm_fsxxxx_callback_args_t   fs2012_callback_args;

    /* Set context */
    fs2012_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            fs2012_callback_args.event = RM_FSXXXX_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            fs2012_callback_args.event = RM_FSXXXX_EVENT_ERROR;
            break;
        }
    }

    if (NULL != p_ctrl->p_callback)
    {
        /* Call callback function */
        p_ctrl->p_callback(&fs2012_callback_args);
    }
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal fs2012 private function.
 **********************************************************************************************************************/
