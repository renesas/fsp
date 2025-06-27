/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include <stdlib.h>

#include "rm_rai_data_collector.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "RMDC" in ASCII, used to determine if module is open. */
#define RAI_DATA_COLLECTOR_PRV_OPEN    (0X524D4443ULL)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static void rm_rai_data_collector_submit_frame_buffers(rai_data_collector_instance_ctrl_t * const p_ctrl, uint32_t idx);
static void rm_rai_data_collector_prepare_next_buffer(rai_data_collector_instance_ctrl_t * const p_ctrl,
                                                      uint8_t                                    channel);
static void rm_rai_data_collector_error_notification(rai_data_collector_instance_ctrl_t * const p_ctrl,
                                                     rai_data_collector_error_event_t           event);

static void rm_rai_data_collector_dtc_end_cb(timer_callback_args_t * p_args);
static void rm_rai_data_collector_dtc_update_info(rai_data_collector_instance_ctrl_t * const p_ctrl, uint8_t channel);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const rai_data_collector_api_t g_dc_on_rai_data_collector =
{
    .open                    = RM_RAI_DATA_COLLECTOR_Open,
    .snapshotChannelRegister = RM_RAI_DATA_COLLECTOR_SnapshotChannelRegister,
    .snapshotStart           = RM_RAI_DATA_COLLECTOR_SnapshotStart,
    .snapshotStop            = RM_RAI_DATA_COLLECTOR_SnapshotStop,
    .channelBufferGet        = RM_RAI_DATA_COLLECTOR_ChannelBufferGet,
    .channelWrite            = RM_RAI_DATA_COLLECTOR_ChannelWrite,
    .bufferRelease           = RM_RAI_DATA_COLLECTOR_BufferRelease,
    .bufferReset             = RM_RAI_DATA_COLLECTOR_BufferReset,
    .close                   = RM_RAI_DATA_COLLECTOR_Close,
};

/*******************************************************************************************************************//**
 * Opens and configures the Data Collector module.
 *
 * Implements @ref rai_data_collector_api_t::open().
 *
 * @retval FSP_SUCCESS                  Data Collector successfully configured.
 * @retval FSP_ERR_ALREADY_OPEN         Module already open.
 * @retval FSP_ERR_ASSERTION            One or more pointers point to NULL or callback is NULL.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 ***********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_Open (rai_data_collector_ctrl_t * const      p_api_ctrl,
                                      rai_data_collector_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

    /* Validate the parameters and check if the module is initialized */
#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(NULL != p_cfg->p_snapshot_cfg);
    FSP_ASSERT(NULL != p_cfg->p_data_feed_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(p_cfg->required_frame_len > 0);
    FSP_ASSERT(p_cfg->channels > 0 && p_cfg->virt_channels > 0);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN != p_ctrl->opened, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg    = p_cfg;
    p_ctrl->p_extend = (rai_data_collector_extended_cfg_t *) p_cfg->p_extend;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl->p_extend->p_ping_pong_buf);
    FSP_ASSERT(NULL != p_ctrl->p_extend->p_ping_pong_buf_hnd);
#endif

    if (p_cfg->p_snapshot_cfg->channels > 0)
    {
        rai_data_collector_snapshot_cfg_t const * p_snapshot_cfg = p_cfg->p_snapshot_cfg;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
        FSP_ASSERT(NULL != p_snapshot_cfg->p_timer);
        FSP_ASSERT(NULL != p_snapshot_cfg->p_transfer);
        FSP_ASSERT(0 < p_snapshot_cfg->transfer_len);
        FSP_ASSERT(NULL != p_ctrl->p_extend->p_transfer_info);
#endif
        err = p_snapshot_cfg->p_transfer->p_api->open(p_snapshot_cfg->p_transfer->p_ctrl,
                                                      p_snapshot_cfg->p_transfer->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = p_snapshot_cfg->p_timer->p_api->open(p_snapshot_cfg->p_timer->p_ctrl, p_snapshot_cfg->p_timer->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = p_snapshot_cfg->p_timer->p_api->callbackSet(p_snapshot_cfg->p_timer->p_ctrl,
                                                          rm_rai_data_collector_dtc_end_cb,
                                                          p_ctrl,
                                                          NULL);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    p_ctrl->channel_ready = 0;
    p_ctrl->buf_status    = RAI_DATA_COLLECTOR_BUFFER_STATUS_IDLE;

    for (uint8_t i = 0; i < p_cfg->virt_channels; i++)
    {
        p_ctrl->p_extend->p_ping_pong_buf_hnd[i].buf_idx         = 0;
        p_ctrl->p_extend->p_ping_pong_buf_hnd[i].accumulated_len = 0;
    }

    p_ctrl->opened = RAI_DATA_COLLECTOR_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Config transfer src address for snapshot mode channel
 *
 * Implements @ref rai_data_collector_api_t::snapshotChannelRegister().
 *
 * @retval FSP_SUCCESS                  Src addresses are set.
 * @retval FSP_ERR_ASSERTION            An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN             Module not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_SnapshotChannelRegister (rai_data_collector_ctrl_t * const p_api_ctrl,
                                                         uint8_t                           channel,
                                                         void const                      * p_src)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(channel < p_ctrl->p_cfg->p_snapshot_cfg->channels);
#endif

    p_ctrl->p_extend->p_transfer_info[channel].p_src = p_src;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Release frame buffer
 *
 * Implements @ref rai_data_collector_api_t::bufferRelease().
 *
 * @retval FSP_SUCCESS                  Buffer released.
 * @retval FSP_ERR_ASSERTION            An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN             Module not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_BufferRelease (rai_data_collector_ctrl_t * const p_api_ctrl)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->buf_status = RAI_DATA_COLLECTOR_BUFFER_STATUS_IDLE;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reset to discard accumulated data and start with PING buffer.
 * @note Application must stop data transfer on all channels first.
 *
 * Implements @ref rai_data_collector_api_t::bufferReset().
 *
 * @retval FSP_SUCCESS                  Data Collector module internal buffers reset.
 * @retval FSP_ERR_ASSERTION            An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN             Module not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_BufferReset (rai_data_collector_ctrl_t * const p_api_ctrl)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->channel_ready = 0;
    p_ctrl->buf_status    = RAI_DATA_COLLECTOR_BUFFER_STATUS_IDLE;

    for (uint8_t i = 0; i < p_ctrl->p_cfg->virt_channels; i++)
    {
        p_ctrl->p_extend->p_ping_pong_buf_hnd[i].buf_idx         = 0;
        p_ctrl->p_extend->p_ping_pong_buf_hnd[i].accumulated_len = 0;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts snapshot mode channels
 *
 * Implements @ref rai_data_collector_api_t::snapshotStart().
 *
 * @retval FSP_SUCCESS                  Snapshot mode started.
 * @retval FSP_ERR_ASSERTION            An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN             Module not open.
 * @retval FSP_ERR_UNSUPPORTED          No snapshot mode channel
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_SnapshotStart (rai_data_collector_ctrl_t * const p_api_ctrl)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0 < p_ctrl->p_cfg->p_snapshot_cfg->channels, FSP_ERR_UNSUPPORTED);
#endif

    rm_rai_data_collector_dtc_update_info(p_ctrl, p_ctrl->p_cfg->p_data_feed_cfg->channels);

    timer_instance_t const * p_timer = p_ctrl->p_cfg->p_snapshot_cfg->p_timer;
    fsp_err_t                err     = p_timer->p_api->reset(p_timer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = p_timer->p_api->start(p_timer->p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * Stops snapshot mode channels
 *
 * Implements @ref rai_data_collector_api_t::snapshotStop().
 *
 * @retval FSP_SUCCESS           Snapshot mode stopped.
 * @retval FSP_ERR_ASSERTION     An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN      Module not open.
 * @retval FSP_ERR_UNSUPPORTED   No snapshot mode channel
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_SnapshotStop (rai_data_collector_ctrl_t * const p_api_ctrl)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0 < p_ctrl->p_cfg->p_snapshot_cfg->channels, FSP_ERR_UNSUPPORTED);
#endif

    timer_instance_t const * p_timer = p_ctrl->p_cfg->p_snapshot_cfg->p_timer;
    fsp_err_t                err     = p_timer->p_api->stop(p_timer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    transfer_instance_t const * p_transfer = p_ctrl->p_cfg->p_snapshot_cfg->p_transfer;
    err = p_transfer->p_api->disable(p_transfer->p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * Get channel destination buffer address for asynchronous data transfer.
 *
 * Implements @ref rai_data_collector_api_t::channelBufferGet().
 *
 * @retval FSP_SUCCESS              Buffer available.
 * @retval FSP_ERR_ASSERTION        An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN         Module not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_ChannelBufferGet (rai_data_collector_ctrl_t * const p_api_ctrl,
                                                  uint8_t                           channel,
                                                  void                           ** pp_buf)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != pp_buf);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(channel < p_ctrl->p_cfg->p_data_feed_cfg->channels);
#endif

    rm_rai_data_collector_prepare_next_buffer(p_ctrl, channel);

    uint32_t unit_size = p_ctrl->p_extend->p_ping_pong_buf[channel].data_type & RAI_DATA_COLLECTOR_DATA_TYPE_SIZE_MASK;
    *pp_buf = (uint8_t *) p_ctrl->p_extend->p_ping_pong_buf[channel].p_buf +
              p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].buf_idx * p_ctrl->p_cfg->required_frame_len *
              unit_size +
              p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len * unit_size;

    p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len += p_ctrl->p_cfg->required_frame_len;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Synchronouse data transfer using CPU copy.
 *
 * Implements @ref rai_data_collector_api_t::channelWrite().
 *
 * @retval FSP_SUCCESS                  Data copy completed.
 * @retval FSP_ERR_ASSERTION            An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN             Module not open.
 *
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_ChannelWrite (rai_data_collector_ctrl_t * const p_api_ctrl,
                                              uint8_t                           channel,
                                              const void                      * p_buf,
                                              uint32_t                          len)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_buf);
    FSP_ASSERT(len > 0);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(channel < p_ctrl->p_cfg->p_data_feed_cfg->channels);
    FSP_ASSERT(len + p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len <=
               p_ctrl->p_cfg->required_frame_len);
#endif

    uint32_t  unit_size = p_ctrl->p_extend->p_ping_pong_buf[channel].data_type & RAI_DATA_COLLECTOR_DATA_TYPE_SIZE_MASK;
    uint8_t * p_dest    = (uint8_t *) p_ctrl->p_extend->p_ping_pong_buf[channel].p_buf +
                          (p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].buf_idx *
                           p_ctrl->p_cfg->required_frame_len +
                           p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len) * unit_size;

    memcpy(p_dest, p_buf, len * unit_size);

    p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len += len;
    rm_rai_data_collector_prepare_next_buffer(p_ctrl, channel);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes Data Collector module instance.
 *
 * Implements @ref rai_data_collector_api_t::close().
 *
 * @retval FSP_SUCCESS           Data Collector module closed.
 * @retval FSP_ERR_ASSERTION     An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN      Module not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_Close (rai_data_collector_ctrl_t * const p_api_ctrl)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_api_ctrl;

#if RM_RAI_DATA_COLLECTOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RAI_DATA_COLLECTOR_PRV_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    if (p_ctrl->p_cfg->p_snapshot_cfg->channels > 0)
    {
        timer_instance_t const * p_timer = p_ctrl->p_cfg->p_snapshot_cfg->p_timer;
        fsp_err_t                err     = p_timer->p_api->close(p_timer->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        transfer_instance_t const * p_transfer = p_ctrl->p_cfg->p_snapshot_cfg->p_transfer;
        err = p_transfer->p_api->close(p_transfer->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    p_ctrl->opened = 0;

    return FSP_SUCCESS;
}

/* Data ready callback */
static void rm_rai_data_collector_submit_frame_buffers (rai_data_collector_instance_ctrl_t * const p_ctrl, uint32_t idx)
{
    rai_data_collector_frame_buffer_t frame_buf[RM_RAI_DATA_COLLECTOR_CFG_MAX_CHANNELS];

    rai_data_collector_callback_args_t args =
    {
        .instance_id   = p_ctrl->p_cfg->instance_id,
        .p_context     = p_ctrl->p_cfg->p_context,
        .frame_buf_len = p_ctrl->p_cfg->required_frame_len,
        .frames        = p_ctrl->p_cfg->channels,
        .p_frame_buf   = frame_buf,
    };

    for (uint8_t i = 0; i < p_ctrl->p_cfg->channels; i++)
    {
        uint32_t unit_size = p_ctrl->p_extend->p_ping_pong_buf[i].data_type & RAI_DATA_COLLECTOR_DATA_TYPE_SIZE_MASK;
        frame_buf[i].p_buf = (uint8_t *) p_ctrl->p_extend->p_ping_pong_buf[i].p_buf + idx *
                             p_ctrl->p_cfg->required_frame_len *
                             unit_size;

        frame_buf[i].data_type = p_ctrl->p_extend->p_ping_pong_buf[i].data_type;
    }

    p_ctrl->p_cfg->p_callback(&args);
}

/* Error callback */
static void rm_rai_data_collector_error_notification (rai_data_collector_instance_ctrl_t * const p_ctrl,
                                                      rai_data_collector_error_event_t           event)
{
    if (p_ctrl->p_cfg->p_error_callback)
    {
        rai_data_collector_error_callback_args_t arg =
        {
            .instance_id = p_ctrl->p_cfg->instance_id,
            .event       = event,
        };

        p_ctrl->p_cfg->p_error_callback(&arg);
    }
}

/* Prepare frame buffer for next data transfer. Note this function may be called in ISRs. It is possible
 * that application will be notified multpile times for the same error events (disabling global interrupt
 * should be avoided in FSP). It is strongly recommended for the application to handle error event in the
 * main loop, but not in the callback.
 */
static void rm_rai_data_collector_prepare_next_buffer (rai_data_collector_instance_ctrl_t * const p_ctrl,
                                                       uint8_t                                    channel)
{
    if (p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len >= p_ctrl->p_cfg->required_frame_len)
    {
        /* Current frame buffer is filled up */

        if (!(RAI_DATA_COLLECTOR_BUFFER_STATUS_OVERRUN & p_ctrl->buf_status))
        {
            if (RAI_DATA_COLLECTOR_BUFFER_STATUS_BUSY & p_ctrl->buf_status)
            {
                /* Overwrite the current frame buffer if next buffer has not been released yet */
                p_ctrl->buf_status |= RAI_DATA_COLLECTOR_BUFFER_STATUS_OVERRUN;
                rm_rai_data_collector_error_notification(p_ctrl, RAI_DATA_COLLECTOR_ERROR_TYPE_BUF_OVERRUN);
            }
            else
            {
                /* PING-PONG buffer: the other buffer is available */

                if (p_ctrl->channel_ready & (1 << channel))
                {
                    /* Fatal: The other buffer has not been submitted, e.g some channel stopped collecting data */
                    rm_rai_data_collector_error_notification(p_ctrl, RAI_DATA_COLLECTOR_ERROR_TYPE_BUF_OUT_OF_SYNC);
                }
                else
                {
                    /* Mark frame buffer as ready */
                    p_ctrl->channel_ready |= 1 << channel;

                    /* Check whether all frame buffers are ready */
                    if (p_ctrl->p_cfg->channel_ready_mask == p_ctrl->channel_ready)
                    {
                        p_ctrl->buf_status   |= RAI_DATA_COLLECTOR_BUFFER_STATUS_BUSY;
                        p_ctrl->channel_ready = 0;
                        rm_rai_data_collector_submit_frame_buffers(p_ctrl,
                                                                   p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].buf_idx);
                    }
                }

                /* Switch Ping-Pong buffer */
                p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].buf_idx ^= 1;
            }
        }

        p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len = 0;
    }
}

static void rm_rai_data_collector_dtc_end_cb (timer_callback_args_t * p_args)
{
    rai_data_collector_instance_ctrl_t * p_ctrl = (rai_data_collector_instance_ctrl_t *) p_args->p_context;

    rm_rai_data_collector_dtc_update_info(p_ctrl, p_ctrl->p_cfg->p_data_feed_cfg->channels);
}

static void rm_rai_data_collector_dtc_update_info (rai_data_collector_instance_ctrl_t * const p_ctrl, uint8_t channel)
{
    /* Snapshot mode channels shall have the same accumulated length and idx */
    transfer_info_t * p_info = p_ctrl->p_extend->p_transfer_info;

    rm_rai_data_collector_prepare_next_buffer(p_ctrl, channel);

    uint32_t offset = p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].buf_idx * p_ctrl->p_cfg->required_frame_len;
    for (uint8_t i = 0; i < p_ctrl->p_cfg->p_snapshot_cfg->channels; i++)
    {
        if (p_ctrl->p_extend->p_ping_pong_buf[i + channel].data_type !=
            RAI_DATA_COLLECTOR_DATA_TYPE_DOUBLE)
        {
            p_info[i].length = p_ctrl->p_cfg->p_snapshot_cfg->transfer_len;
            p_info[i].p_dest =
                (uint8_t *) p_ctrl->p_extend->p_ping_pong_buf[i + channel].p_buf +
                ((offset + p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len) <<
                    p_info[i].transfer_settings_word_b.size);
        }
        else
        {
            /* The unit transfer size of DTC is 1 byte, 2bytes or 4 bytes. The transfer len for type "double" needs to be doubled
             * when the unit transfer size is initialized to 4 Bytes.
             */
            p_info[i].length = (uint16_t) (p_ctrl->p_cfg->p_snapshot_cfg->transfer_len << 1);
            p_info[i].p_dest =
                (uint8_t *) p_ctrl->p_extend->p_ping_pong_buf[i + channel].p_buf +
                ((offset + p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len) << 3);
        }

        p_info[i].num_blocks = 1;
    }

    p_ctrl->p_extend->p_ping_pong_buf_hnd[channel].accumulated_len += p_ctrl->p_cfg->p_snapshot_cfg->transfer_len;

    p_ctrl->p_cfg->p_snapshot_cfg->p_transfer->p_api->reconfigure(p_ctrl->p_cfg->p_snapshot_cfg->p_transfer->p_ctrl,
                                                                  p_info);
}
