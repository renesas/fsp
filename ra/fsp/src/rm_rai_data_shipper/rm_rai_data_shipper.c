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
#include <string.h>
#include <stdlib.h>

#include "rm_rai_data_shipper.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "RMDS" in ASCII, used to determine if module is open. */
#define RAI_DATA_SHIPPER_PRV_OPEN                       (0X524D4453ULL)

#define RAI_DATA_SHIPPER_PRV_HEADER_BUFFER_BASE_SIZE    (17U) ///< Size of rai_data_shipper_header_buffer_t excluding data_type array

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#define RM_RAI_DATA_SHIPPER_HEADER_BUFFER_VERSION       (0)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static void rai_data_shipper_write_callback(rm_comms_callback_args_t * p_args);
static void rai_data_shipper_notify_application(rai_data_shipper_instance_ctrl_t * p_ctrl, rm_comms_event_t event);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const rai_data_shipper_api_t g_ds_on_rai_data_shipper =
{
    .open  = RM_RAI_DATA_SHIPPER_Open,
    .read  = RM_RAI_DATA_SHIPPER_Read,
    .write = RM_RAI_DATA_SHIPPER_Write,
    .close = RM_RAI_DATA_SHIPPER_Close
};

/*******************************************************************************************************************//**
 * Opens and configures the Data Shipper module.
 *
 * Implements @ref rai_data_shipper_api_t::open().
 *
 * @retval FSP_SUCCESS                  Data Shipper successfully configured.
 * @retval FSP_ERR_ALREADY_OPEN         Module already open.
 * @retval FSP_ERR_ASSERTION            One or more pointers point to NULL or callback is NULL.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 ***********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_SHIPPER_Open (rai_data_shipper_ctrl_t * const      p_api_ctrl,
                                    rai_data_shipper_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rai_data_shipper_instance_ctrl_t * p_ctrl = (rai_data_shipper_instance_ctrl_t *) p_api_ctrl;

    /* Validate the parameters and check if the module is initialized */
#if RM_RAI_DATA_SHIPPER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms);
    FSP_ERROR_RETURN(RAI_DATA_SHIPPER_PRV_OPEN != p_ctrl->opened, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg = p_cfg;

    if (p_cfg->p_crc != NULL)
    {
        err = p_cfg->p_crc->p_api->open(p_cfg->p_crc->p_ctrl, p_cfg->p_crc->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    err = p_cfg->p_comms->p_api->open(p_cfg->p_comms->p_ctrl, p_cfg->p_comms->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = p_cfg->p_comms->p_api->callbackSet(p_cfg->p_comms->p_ctrl, rai_data_shipper_write_callback, p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_ctrl->tx_info.header.rssn[0]    = 'R';
    p_ctrl->tx_info.header.rssn[1]    = 'S';
    p_ctrl->tx_info.header.rssn[2]    = 'S';
    p_ctrl->tx_info.header.rssn[3]    = 'N';
    p_ctrl->tx_info.header.crc_enable = (p_cfg->p_crc != NULL) ? 1 : 0;
    p_ctrl->tx_info.header.version    = RM_RAI_DATA_SHIPPER_HEADER_BUFFER_VERSION;

    p_ctrl->opened = RAI_DATA_SHIPPER_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read data.
 *
 * Implements @ref rai_data_shipper_api_t::read().
 *
 * @retval FSP_ERR_UNSUPPORTED          Data Shipper module read not supported
 *
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_SHIPPER_Read (rai_data_shipper_ctrl_t * const p_api_ctrl,
                                    void * const                    p_buf,
                                    uint32_t * const                buf_len)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_buf);
    FSP_PARAMETER_NOT_USED(buf_len);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Write data. Note this funciton may be called in ISR.
 *
 * Implements @ref rai_data_shipper_api_t::write().
 *
 * @retval FSP_SUCCESS                  Tx buf list created and transmission starts, or write request skipped.
 * @retval FSP_ERR_ASSERTION            An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN             Module not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_SHIPPER_Write (rai_data_shipper_ctrl_t * const         p_api_ctrl,
                                     rai_data_shipper_write_params_t const * p_write_params)
{
    rai_data_shipper_instance_ctrl_t * p_ctrl = (rai_data_shipper_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_SHIPPER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_write_params);
    FSP_ASSERT(NULL != p_write_params->p_diagnostic_data || NULL != p_write_params->p_sensor_data);
    FSP_ERROR_RETURN(RAI_DATA_SHIPPER_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Skip write requests */
    if (p_ctrl->tx_info.write_requests < p_ctrl->p_cfg->divider)
    {
        p_ctrl->tx_info.write_requests++;
        rai_data_shipper_notify_application(p_ctrl, RM_COMMS_EVENT_TX_OPERATION_COMPLETE);

        return FSP_SUCCESS;
    }

    p_ctrl->tx_info.write_requests = 0;

    p_ctrl->tx_info.current  = 0;
    p_ctrl->tx_info.channels = 0;

    if (p_write_params->p_sensor_data)
    {
        /* Fill up header buffer */
        p_ctrl->tx_info.header.channels      = p_write_params->p_sensor_data->frames;
        p_ctrl->tx_info.header.instance_id   = p_write_params->p_sensor_data->instance_id;
        p_ctrl->tx_info.header.frame_buf_len = p_write_params->p_sensor_data->frame_buf_len;

        for (uint8_t i = 0; i < p_write_params->p_sensor_data->frames; i++)
        {
            /*
             * Data shipper shall be designed with maximum throughput in mind. So data type needs to be converted from "rai_data_collector_data_type_t" to 4 bits.
             * The 4-bit data type value is encoded in bits [4:7] in rai_data_collector_data_type_t.
             */
            if (i & 1)
            {
                /* Odd channels use high 4 bits */
                uint8_t val =
                    (uint8_t) (p_write_params->p_sensor_data->p_frame_buf[i].data_type &
                               (uint32_t) (~RAI_DATA_COLLECTOR_DATA_TYPE_SIZE_MASK));
                p_ctrl->tx_info.header.data_type[i >> 1] |= val;
            }
            else
            {
                /* Even channels use lower 4 bits */
                p_ctrl->tx_info.header.data_type[i >>
                                                 1] =
                    (uint8_t) ((p_write_params->p_sensor_data->p_frame_buf[i].data_type >> 4) &
                               RAI_DATA_COLLECTOR_DATA_TYPE_SIZE_MASK);
            }

            p_ctrl->tx_info.data[p_ctrl->tx_info.channels].p_buf = p_write_params->p_sensor_data->p_frame_buf[i].p_buf;
            p_ctrl->tx_info.data[p_ctrl->tx_info.channels].len   = p_write_params->p_sensor_data->frame_buf_len *
                                                                   (p_write_params->p_sensor_data->p_frame_buf[i].
                                                                    data_type &
                                                                    RAI_DATA_COLLECTOR_DATA_TYPE_SIZE_MASK);
            p_ctrl->tx_info.channels++;
        }
    }
    else
    {
        p_ctrl->tx_info.header.instance_id   = 0;
        p_ctrl->tx_info.header.channels      = 0;
        p_ctrl->tx_info.header.frame_buf_len = 0;
    }

    uint32_t header_buffer_len = RAI_DATA_SHIPPER_PRV_HEADER_BUFFER_BASE_SIZE +
                                 (uint32_t) ((p_ctrl->tx_info.header.channels + 1) >> 1);

    p_ctrl->tx_info.header.events              = p_write_params->events;
    p_ctrl->tx_info.header.diagnostic_data_len = p_write_params->diagnostic_data_len;

    if (p_write_params->p_diagnostic_data && (p_write_params->diagnostic_data_len > 0))
    {
        p_ctrl->tx_info.data[p_ctrl->tx_info.channels].p_buf = (void *) p_write_params->p_diagnostic_data;
        p_ctrl->tx_info.data[p_ctrl->tx_info.channels].len   = p_write_params->diagnostic_data_len;
        p_ctrl->tx_info.channels++;
    }

    if (p_ctrl->p_cfg->p_crc)
    {
        uint32_t    crc = 0;
        crc_input_t input;

        input.p_input_buffer = (void *) &p_ctrl->tx_info.header;
        input.num_bytes      = header_buffer_len;
        input.crc_seed       = crc;
        p_ctrl->p_cfg->p_crc->p_api->calculate(p_ctrl->p_cfg->p_crc->p_ctrl, &input, &crc);

        for (uint8_t i = 0; i < p_ctrl->tx_info.channels; i++)
        {
            input.p_input_buffer = p_ctrl->tx_info.data[i].p_buf;
            input.num_bytes      = p_ctrl->tx_info.data[i].len;
            input.crc_seed       = crc;
            p_ctrl->p_cfg->p_crc->p_api->calculate(p_ctrl->p_cfg->p_crc->p_ctrl, &input, &crc);
        }

        p_ctrl->tx_info.crc = (uint8_t) crc;
        p_ctrl->tx_info.data[p_ctrl->tx_info.channels].p_buf = &p_ctrl->tx_info.crc;
        p_ctrl->tx_info.data[p_ctrl->tx_info.channels].len   = 1;
        p_ctrl->tx_info.channels++;
    }

    p_ctrl->p_cfg->p_comms->p_api->write(p_ctrl->p_cfg->p_comms->p_ctrl,
                                         (uint8_t *) &p_ctrl->tx_info.header,
                                         header_buffer_len);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes Data Shipper module instance.
 *
 * Implements @ref rai_data_shipper_api_t::close().
 *
 * @retval FSP_SUCCESS           Data Shipper module closed.
 * @retval FSP_ERR_ASSERTION     An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN      Module not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_SHIPPER_Close (rai_data_shipper_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rai_data_shipper_instance_ctrl_t * p_ctrl = (rai_data_shipper_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_SHIPPER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RAI_DATA_SHIPPER_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    if (p_ctrl->p_cfg->p_crc)
    {
        p_ctrl->p_cfg->p_crc->p_api->close(p_ctrl->p_cfg->p_crc->p_ctrl);
    }

    p_ctrl->p_cfg->p_comms->p_api->close(p_ctrl->p_cfg->p_comms->p_ctrl);

    p_ctrl->opened = 0;

    return err;
}

static void rai_data_shipper_notify_application (rai_data_shipper_instance_ctrl_t * p_ctrl, rm_comms_event_t event)
{
    // Callback to application to release buffer etc.
    rai_data_shipper_callback_args_t args =
    {
        .result    = event,
        .p_context = p_ctrl->p_cfg->p_context,
    };

    p_ctrl->p_cfg->p_callback(&args);
}

static void rai_data_shipper_write_callback (rm_comms_callback_args_t * p_args)
{
    rai_data_shipper_instance_ctrl_t * p_ctrl = (rai_data_shipper_instance_ctrl_t *) p_args->p_context;

    if (p_args->event == RM_COMMS_EVENT_ERROR)
    {
        rai_data_shipper_notify_application(p_ctrl, p_args->event);

        return;
    }

    if (p_ctrl->tx_info.current == p_ctrl->tx_info.channels)
    {
        rai_data_shipper_notify_application(p_ctrl, p_args->event);

        return;
    }

    fsp_err_t err =
        p_ctrl->p_cfg->p_comms->p_api->write(p_ctrl->p_cfg->p_comms->p_ctrl,
                                             p_ctrl->tx_info.data[p_ctrl->tx_info.current].p_buf,
                                             p_ctrl->tx_info.data[p_ctrl->tx_info.current].len);
    if (FSP_SUCCESS != err)
    {
        rai_data_shipper_notify_application(p_ctrl, RM_COMMS_EVENT_ERROR);

        return;
    }

    p_ctrl->tx_info.current++;
}
