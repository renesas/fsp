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

#ifndef R_PTP_H
#define R_PTP_H

/*******************************************************************************************************************//**
 * @addtogroup PTP
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ptp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*************************************************************************************************
 * Type defines for the SPI interface API
 *************************************************************************************************/

/** PTP instance control block. */
typedef struct
{
    uint32_t          open;                     ///< Marks if the instance has been opened.
    uint32_t          tx_buffer_write_index;    ///< Index into the descriptor list to write the next packet.
    uint32_t          tx_buffer_complete_index; ///< Index into the descriptor list of the last transmitted packet.
    uint32_t          rx_buffer_index;          ///< Index into the descriptor of the last received packet.
    uint32_t          tslatr;                   ///< Keep track of whether tslatr was set.
    ptp_cfg_t const * p_cfg;                    ///< Pointer to the configuration structure.
} ptp_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ptp_api_t g_ptp_api;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_PTP_Open(ptp_ctrl_t * const p_ctrl, ptp_cfg_t const * const p_cfg);
fsp_err_t R_PTP_MacAddrSet(ptp_ctrl_t * const p_ctrl, uint8_t const * const p_mac_addr);
fsp_err_t R_PTP_IpAddrSet(ptp_ctrl_t * const p_ctrl, uint32_t ip_addr);
fsp_err_t R_PTP_LocalClockIdSet(ptp_ctrl_t * const p_ctrl, uint8_t const * const p_clock_id);
fsp_err_t R_PTP_MasterClockIdSet(ptp_ctrl_t * const p_ctrl, uint8_t const * const p_clock_id, uint16_t port_id);
fsp_err_t R_PTP_MessageFlagsSet(ptp_ctrl_t * const p_ctrl, ptp_message_type_t message_type, ptp_message_flags_t flags);
fsp_err_t R_PTP_CurrentUtcOffsetSet(ptp_ctrl_t * const p_ctrl, uint16_t offset);
fsp_err_t R_PTP_PortStateSet(ptp_ctrl_t * const p_ctrl, uint32_t state);
fsp_err_t R_PTP_MessageSend(ptp_ctrl_t * const          p_ctrl,
                            ptp_message_t const * const p_message,
                            uint8_t const * const       p_tlv_data,
                            uint16_t                    tlv_data_size);
fsp_err_t R_PTP_LocalClockValueSet(ptp_ctrl_t * const p_ctrl, ptp_time_t const * const p_time);
fsp_err_t R_PTP_LocalClockValueGet(ptp_ctrl_t * const p_ctrl, ptp_time_t * const p_time);
fsp_err_t R_PTP_PulseTimerCommonConfig(ptp_ctrl_t * const p_ctrl, ptp_pulse_timer_common_cfg_t * const p_timer_cfg);
fsp_err_t R_PTP_PulseTimerEnable(ptp_ctrl_t * const p_ctrl, uint32_t channel,
                                 ptp_pulse_timer_cfg_t * const p_timer_cfg);
fsp_err_t R_PTP_PulseTimerDisable(ptp_ctrl_t * const p_ctrl, uint32_t channel);
fsp_err_t R_PTP_Close(ptp_ctrl_t * const p_ctrl);

fsp_err_t R_PTP_BestMasterClock(ptp_message_t const * const p_announce1,
                                ptp_message_t const * const p_announce2,
                                int8_t * const              p_comparison);

/*******************************************************************************************************************//**
 * @} (end ingroup PTP)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
