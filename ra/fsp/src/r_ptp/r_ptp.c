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
#include "r_ptp.h"
#include "r_ptp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define PTP_OPEN                      (('P' << 16U) | ('T' << 8U) | ('P' << 0U))

#ifndef PTP_SYNFP_SYCONFR_TCYC
 #define PTP_SYNFP_SYCONFR_TCYC       (0x28U)
#endif

#ifndef PTP_VERSION
 #define PTP_VERSION                  (2U)
#endif

#define PTP_SHIFT_32                  (32U)

#define PTP_NUM_PULSE_TIMER           (5U)

#define PTP_MILLISECONDS_IN_SECOND    (1000U)
#define PTP_MICROSECONDS_IN_SECOND    (PTP_MILLISECONDS_IN_SECOND * 1000U)
#define PTP_NANOSECONDS_IN_SECOND     (PTP_MICROSECONDS_IN_SECOND * 1000U)
#define PTP_TIMEOUT_DIVIDER           (1024U)
#define PTP_PCLKA_RESET_CYCLES        (64U)

#define PTP_BYTES_TO_UINT32(ary)    ((uint32_t) (((ary)[0] << 24U) | ((ary)[1] << 16U) | ((ary)[2] << 8U) | \
                                                 ((ary)[3] << 0U)))

#define PTP_CMP_RETURN(p_result, a, ret) \
    {                                    \
        if ((a))                         \
        {                                \
            *p_result = ret;             \
            return FSP_SUCCESS;          \
        }                                \
    }

#define PTP_ETHER_HEADER_SIZE                  (14U)
#define PTP_ETHER_MAX_PACKET_SIZE              (1514U)
#define PTP_ETHER_MIN_PACKET_SIZE              (60U)
#define PTP_ETHER_TYPE_IPV4                    (0x0800U)
#define PTP_ETHER_TYPE_PTP                     (0x88F7U)

#define PTP_LLC_HEADER_SIZE                    (0x03U)
#define PTP_LLC_MAX_LEN                        (1500U)
#define PTP_LLC_SAP_DSAP_OFFSET                (0x00U)
#define PTP_LLC_SAP_SSAP_OFFSET                (0x01U)
#define PTP_LLC_SAP_SNAP                       (0xAAU)
#define PTP_LLC_SAP_MASK                       (0xFEU)
#define PTP_LLC_CTRL_OFFSET                    (0x02U)
#define PTP_LLC_CTRL_FORMAT_U                  (0x03U)

#define PTP_SNAP_HEADER_SIZE                   (5U)
#define PTP_SNAP_OID_OFFSET                    (0x00U)
#define PTP_SNAP_PID_OFFSET                    (0x03U)

#define PTP_IPV4_HEADER_SIZE                   (20U)
#define PTP_IP_VERSION                         (4U)
#define PTP_IP_PROTOCOL_UDP                    (17U)
#define PTP_IP_MULTICAST_ADDRESS_MASK          (0x007FFFFFU)
#define PTP_IP_MULTICAST_MAC_ADDRESS_PREFIX    (0x0001005EU)

#define PTP_UDP_HEADER_SIZE                    (8U)

#define PTP_ETHER_PHY_MII                      (0U)
#define PTP_ETHER_PHY_RMII                     (1U)

#define PTP_ETHER_PHY_10MHZ                    (0U)
#define PTP_ETHER_PHY_100MHZ                   (1U)

#define PTP_SYRFL1R_MASK                       (R_ETHERC_EPTPC_SYRFL1R_ANCE0_Msk    \
                                                | R_ETHERC_EPTPC_SYRFL1R_SYNC0_Msk  \
                                                | R_ETHERC_EPTPC_SYRFL1R_SYNC2_Msk  \
                                                | R_ETHERC_EPTPC_SYRFL1R_FUP0_Msk   \
                                                | R_ETHERC_EPTPC_SYRFL1R_FUP2_Msk   \
                                                | R_ETHERC_EPTPC_SYRFL1R_DRQ0_Msk   \
                                                | R_ETHERC_EPTPC_SYRFL1R_DRQ2_Msk   \
                                                | R_ETHERC_EPTPC_SYRFL1R_DRP0_Msk   \
                                                | R_ETHERC_EPTPC_SYRFL1R_DRP2_Msk   \
                                                | R_ETHERC_EPTPC_SYRFL1R_PDRQ0_Msk  \
                                                | R_ETHERC_EPTPC_SYRFL1R_PDRQ2_Msk  \
                                                | R_ETHERC_EPTPC_SYRFL1R_PDRP0_Msk  \
                                                | R_ETHERC_EPTPC_SYRFL1R_PDRP2_Msk  \
                                                | R_ETHERC_EPTPC_SYRFL1R_PDFUP0_Msk \
                                                | R_ETHERC_EPTPC_SYRFL1R_PDFUP2_Msk)

#define PTP_SYRFL2R_MASK                       (R_ETHERC_EPTPC_SYRFL2R_MAN0_Msk \
                                                | R_ETHERC_EPTPC_SYRFL2R_SIG0_Msk)

#define PTP_SYTRENR_MASK                       (R_ETHERC_EPTPC_SYTRENR_ANCE_Msk   \
                                                | R_ETHERC_EPTPC_SYTRENR_SYNC_Msk \
                                                | R_ETHERC_EPTPC_SYTRENR_DRQ_Msk  \
                                                | R_ETHERC_EPTPC_SYTRENR_PDRQ_Msk)

#define PTP_STIPR_MASK                         (R_ETHERC_EPTPC_COMMON_STIPR_SYNC_Msk      \
                                                | R_ETHERC_EPTPC_COMMON_STIPR_SYNCOUT_Msk \
                                                | R_ETHERC_EPTPC_COMMON_STIPR_SYNTOUT_Msk \
                                                | R_ETHERC_EPTPC_COMMON_STIPR_W10D_Msk)

#define PTP_SYIPR_MASK                         (R_ETHERC_EPTPC_SYIPR_OFMUD_Msk    \
                                                | R_ETHERC_EPTPC_SYIPR_INTCHG_Msk \
                                                | R_ETHERC_EPTPC_SYIPR_MPDUD_Msk  \
                                                | R_ETHERC_EPTPC_SYIPR_DRPTO_Msk  \
                                                | R_ETHERC_EPTPC_SYIPR_INTDEV_Msk \
                                                | R_ETHERC_EPTPC_SYIPR_DRQOVR_Msk \
                                                | R_ETHERC_EPTPC_SYIPR_RECLP_Msk  \
                                                | R_ETHERC_EPTPC_SYIPR_INFABT_Msk \
                                                | R_ETHERC_EPTPC_SYIPR_RESDN_Msk  \
                                                | R_ETHERC_EPTPC_SYIPR_GENDN_Msk)

/* Valid flags for annonuce messages. */
#define PTP_ANNOUNCE_FLAGS_MASK                (R_ETHERC_EPTPC_ANFR_FLAG0_Msk    \
                                                | R_ETHERC_EPTPC_ANFR_FLAG1_Msk  \
                                                | R_ETHERC_EPTPC_ANFR_FLAG2_Msk  \
                                                | R_ETHERC_EPTPC_ANFR_FLAG3_Msk  \
                                                | R_ETHERC_EPTPC_ANFR_FLAG4_Msk  \
                                                | R_ETHERC_EPTPC_ANFR_FLAG5_Msk  \
                                                | R_ETHERC_EPTPC_ANFR_FLAG8_Msk  \
                                                | R_ETHERC_EPTPC_ANFR_FLAG10_Msk \
                                                | R_ETHERC_EPTPC_ANFR_FLAG13_Msk \
                                                | R_ETHERC_EPTPC_ANFR_FLAG14_Msk)

/* Valid flags for sync messages. */
#define PTP_SYNC_FLAGS_MASK                    (R_ETHERC_EPTPC_SYNFR_FLAG8_Msk    \
                                                | R_ETHERC_EPTPC_SYNFR_FLAG9_Msk  \
                                                | R_ETHERC_EPTPC_SYNFR_FLAG10_Msk \
                                                | R_ETHERC_EPTPC_SYNFR_FLAG13_Msk \
                                                | R_ETHERC_EPTPC_SYNFR_FLAG14_Msk)

/* Valid flags for delay_req and pdelay_req messages. */
#define PTP_P_DELAY_REQ_FLAGS_MASK             (R_ETHERC_EPTPC_DYRQFR_FLAG10_Msk   \
                                                | R_ETHERC_EPTPC_DYRQFR_FLAG13_Msk \
                                                | R_ETHERC_EPTPC_DYRQFR_FLAG14_Msk)

/* Valid flags for delay_resp and pdelay_resp messages. */
#define PTP_P_DELAY_RESP_FLAGS_MASK            (R_ETHERC_EPTPC_DYRPFR_FLAG8_Msk    \
                                                | R_ETHERC_EPTPC_DYRPFR_FLAG9_Msk  \
                                                | R_ETHERC_EPTPC_DYRPFR_FLAG10_Msk \
                                                | R_ETHERC_EPTPC_DYRPFR_FLAG13_Msk \
                                                | R_ETHERC_EPTPC_DYRPFR_FLAG14_Msk)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Structure of an Ethernet packet. */
typedef struct PTP_PACKED
{
    uint8_t  destination_mac_address[6];
    uint8_t  source_mac_address[6];
    uint16_t ether_type;
} ptp_ether_header_t;

/* Structure of an IP packet header. */
typedef struct PTP_PACKED
{
    uint8_t  ihl     : 4;
    uint8_t  version : 4;
    uint8_t  tos;
    uint16_t total_length;
    uint16_t id;
    uint16_t fragment_offset : 14;
    uint16_t flags           : 2;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint32_t source_address;
    uint32_t destination_address;
} ptp_ip_header_t;

/* Structure of a UDP packet header. */
typedef struct PTP_PACKED
{
    uint16_t source_port;
    uint16_t destination_port;
    uint16_t length;
    uint16_t checksum;
} ptp_udp_header_t;

/* Configuration values for the Timestamp Latency Setting Register. */
typedef struct
{
    uint32_t egp;
    uint32_t ingp;
} ptp_tslatr_setting_t;

/***********************************************************************************************************************
 * Private function declarations
 **********************************************************************************************************************/
static void r_ptp_hw_reset(void);

static void r_ptp_hw_config(ptp_instance_ctrl_t * p_instance_ctrl);

static uint32_t r_ptp_calculate_timeout(ptp_instance_ctrl_t * p_instance_ctrl, int8_t log_interval);

static void r_ptp_message_endian_swap(ptp_message_t * p_message);

static fsp_err_t r_ptp_process_llc_snap_packet(uint8_t const * const p_llc_snap_packet,
                                               uint16_t              llc_snap_packet_length,
                                               uint16_t            * p_ether_type,
                                               uint8_t ** const      p_payload,
                                               uint16_t * const      payload_length);
static void r_ptp_append_ether_header(ptp_instance_ctrl_t * p_instance_ctrl,
                                      uint8_t             * p_packet,
                                      uint16_t              packet_length);
static void r_ptp_append_ieee802_3_llc_snap_header(ptp_instance_ctrl_t * p_instance_ctrl, uint8_t * p_packet);
uint16_t    r_ptp_ip_checksum(uint8_t * p_ip_header);
static void r_ptp_append_ipv4_udp_header(ptp_instance_ctrl_t * p_instance_ctrl,
                                         uint8_t             * p_packet,
                                         uint16_t              packet_length);

static fsp_err_t r_ptp_process_ipv4_udp_packet(ptp_instance_ctrl_t * p_instance_ctrl,
                                               uint8_t const * const p_ip_packet,
                                               uint16_t              ip_packet_length,
                                               uint8_t ** const      p_payload,
                                               uint16_t * const      payload_length);

static fsp_err_t r_ptp_process_ptp_packet(ptp_instance_ctrl_t * p_instance_ctrl,
                                          uint8_t const * const p_ptp_packet,
                                          uint16_t              ptp_packet_length);

static fsp_err_t r_ptp_process_ether_packet(ptp_instance_ctrl_t * p_instance_ctrl,
                                            uint8_t const * const p_ether_packet,
                                            uint16_t              ether_packet_length);

void r_ptp_edmac_callback(edmac_callback_args_t * p_args);
void r_ptp_mint_isr(void);
void r_ptp_ipls_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Lookup table for calcualting TSLATR. */
static const ptp_tslatr_setting_t g_tslatr_lut[2][2][4] =
{
    /* MMI */
    {
        /* PHY Speed 10Mbs */
        {
            /* STCA Input Clock Frequency 20Mhz */
            {
                9230U /* EGP */, 8980U /* INGP */
            },

            /* STCA Input Clock Frequency 25Mhz */
            {
                9265U /* EGP */, 8945U /* INGP */
            },

            /* STCA Input Clock Frequency 50Mhz */
            {
                9335U /* EGP */, 8875U /* INGP */
            },

            /* STCA Input Clock Frequency 100Mhz */
            {
                9370U /* EGP */, 8815U /* INGP */
            },
        },

        /* PHY Speed 100Mbs */
        {
            /* STCA Input Clock Frequency 20Mhz */
            {
                7430U /* EGP */, 8180U /* INGP */
            },

            /* STCA Input Clock Frequency 25Mhz */
            {
                7465U /* EGP */, 8145U /* INGP */
            },

            /* STCA Input Clock Frequency 50Mhz */
            {
                7535U /* EGP */, 8075U /* INGP */
            },

            /* STCA Input Clock Frequency 100Mhz */
            {
                7570U /* EGP */, 8015U /* INGP */
            },
        }
    },

    /* RMMI */
    {
        /* PHY Speed 10Mbs */
        {
            /* STCA Input Clock Frequency 20Mhz */
            {
                9230U /* EGP */, 8980U /* INGP */
            },

            /* STCA Input Clock Frequency 25Mhz */
            {
                9265U /* EGP */, 8945U /* INGP */
            },

            /* STCA Input Clock Frequency 50Mhz */
            {
                9335U /* EGP */, 8875U /* INGP */
            },

            /* STCA Input Clock Frequency 100Mhz */
            {
                9370U /* EGP */, 8815U /* INGP */
            },
        },

        /* PHY Speed 100Mbs */
        {
            /* STCA Input Clock Frequency 20Mhz */
            {
                770U /* EGP */, 1060U  /* INGP */
            },

            /* STCA Input Clock Frequency 25Mhz */
            {
                805U /* EGP */, 1025U  /* INGP */
            },

            /* STCA Input Clock Frequency 50Mhz */
            {
                875U /* EGP */, 955U   /* INGP */
            },

            /* STCA Input Clock Frequency 100Mhz */
            {
                910U /* EGP */, 920U   /* INGP */
            },
        }
    }
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const ptp_api_t g_ptp_api =
{
    .open                   = R_PTP_Open,
    .macAddrSet             = R_PTP_MacAddrSet,
    .ipAddrSet              = R_PTP_IpAddrSet,
    .localClockIdSet        = R_PTP_LocalClockIdSet,
    .masterClockIdSet       = R_PTP_MasterClockIdSet,
    .messageFlagsSet        = R_PTP_MessageFlagsSet,
    .currentUtcOffsetSet    = R_PTP_CurrentUtcOffsetSet,
    .portStateSet           = R_PTP_PortStateSet,
    .messageSend            = R_PTP_MessageSend,
    .localClockValueSet     = R_PTP_LocalClockValueSet,
    .localClockValueGet     = R_PTP_LocalClockValueGet,
    .pulseTimerCommonConfig = R_PTP_PulseTimerCommonConfig,
    .pulseTimerEnable       = R_PTP_PulseTimerEnable,
    .pulseTimerDisable      = R_PTP_PulseTimerDisable,
    .close                  = R_PTP_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup PTP
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This function initializes PTP. Implements @ref ptp_api_t::open.
 *
 * This function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Configures the peripheral registers acording to the configuration.
 * - Initialize the control structure for use in other @ref PTP_API functions.
 *
 * @retval     FSP_SUCCESS                     The instance has been successfully configured.
 * @retval     FSP_ERR_ALREADY_OPEN            Instance was already initialized.
 * @retval     FSP_ERR_NOT_OPEN                The EDMAC instance was not opened correctly.
 * @retval     FSP_ERR_ASSERTION               An invalid argument was given in the configuration structure.
 **********************************************************************************************************************/
fsp_err_t R_PTP_Open (ptp_ctrl_t * const p_ctrl, ptp_cfg_t const * const p_cfg)
{
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_edmac_instance);
    if (PTP_CLOCK_CORRECTION_MODE2 == p_cfg->stca.clock_correction_mode)
    {
        FSP_ASSERT(0U != p_cfg->stca.gradient_worst10_interval);
    }

    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(p_cfg->mint_irq >= 0);
    FSP_ASSERT(p_cfg->ipls_irq >= 0);
#endif

    p_instance_ctrl->p_cfg  = p_cfg;
    p_instance_ctrl->tslatr = 0U;

    r_ptp_hw_config(p_instance_ctrl);

    p_instance_ctrl->rx_buffer_index          = 0U;
    p_instance_ctrl->tx_buffer_write_index    = 0U;
    p_instance_ctrl->tx_buffer_complete_index = 0U;
    edmac_instance_t * p_edmac_instance = p_instance_ctrl->p_cfg->p_edmac_instance;
    fsp_err_t          err              = R_EDMAC_Open(p_edmac_instance->p_ctrl, p_edmac_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    for (uint32_t i = 0; i < p_edmac_instance->p_cfg->num_rx_desc; i++)
    {
        err = R_EDMAC_DescriptorUpdate(p_edmac_instance->p_ctrl,
                                       EDMAC_DESC_RECEIVE,
                                       i,
                                       &p_instance_ctrl->p_cfg->p_rx_buffers[i][0],
                                       p_instance_ctrl->p_cfg->buffer_size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->mint_irq, p_instance_ctrl->p_cfg->mint_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->ipls_irq, p_instance_ctrl->p_cfg->ipls_ipl, p_ctrl);

    p_instance_ctrl->open = PTP_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets the MAC address for the PTP instance. Implements @ref ptp_api_t::macAddrSet.
 * @note This function may only be called while the PTP instance is in @ref ptp_port_state_t::PTP_PORT_STATE_DISABLE.
 *
 * @retval     FSP_SUCCESS                     The MAC address has been set.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL
 * @retval     FSP_ERR_INVALID_MODE            The instance is not in the correct state.
 **********************************************************************************************************************/
fsp_err_t R_PTP_MacAddrSet (ptp_ctrl_t * const p_ctrl, uint8_t const * const p_mac_addr)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_mac_addr);
    FSP_ERROR_RETURN(0U == R_ETHERC_EPTPC->SYRFL1R &&
                     0U == R_ETHERC_EPTPC->SYRFL2R &&
                     0U == R_ETHERC_EPTPC->SYTRENR,
                     FSP_ERR_INVALID_MODE);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    uint32_t symacru = 0U;
    uint32_t symacrl = 0U;

    symacru |= (uint32_t) p_mac_addr[0] << 16U;
    symacru |= (uint32_t) p_mac_addr[1] << 8U;
    symacru |= (uint32_t) p_mac_addr[2] << 0U;
    symacrl |= (uint32_t) p_mac_addr[3] << 16U;
    symacrl |= (uint32_t) p_mac_addr[4] << 8U;
    symacrl |= (uint32_t) p_mac_addr[5] << 0U;

    R_ETHERC_EPTPC->SYMACRU = symacru;
    R_ETHERC_EPTPC->SYMACRL = symacrl;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets the IP address for the PTP instance. Implements @ref ptp_api_t::ipAddrSet.
 * @note This function may only be called while the PTP instance is in @ref ptp_port_state_t::PTP_PORT_STATE_DISABLE.
 *
 * @retval     FSP_SUCCESS                     The IP address has been set.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL.
 * @retval     FSP_ERR_INVALID_MODE            The configured ptp_synfp_cfg_t::frame_format is not configured to
 *                                             use IP packets, or the instance is not in the correct state.
 **********************************************************************************************************************/
fsp_err_t R_PTP_IpAddrSet (ptp_ctrl_t * const p_ctrl, uint32_t ip_addr)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(PTP_FRAME_FORMAT_ETHERII != p_instance_ctrl->p_cfg->synfp.frame_format &&
                     PTP_FRAME_FORMAT_IEEE802_3 != p_instance_ctrl->p_cfg->synfp.frame_format,
                     FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(0U == R_ETHERC_EPTPC->SYRFL1R &&
                     0U == R_ETHERC_EPTPC->SYRFL2R &&
                     0U == R_ETHERC_EPTPC->SYTRENR,
                     FSP_ERR_INVALID_MODE);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Set SYNFP Local IP Address Register. */
    R_ETHERC_EPTPC->SYIPADDRR = ip_addr;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets the local clock ID for the PTP instance. Implements @ref ptp_api_t::localClockIdSet.
 * @note This function may only be called while the PTP instance is in @ref ptp_port_state_t::PTP_PORT_STATE_DISABLE.
 * @note Typically the clock ID is derived from the MAC address (E.g. {b1,b2,b3,0xFF,0xFE,b4,b5,b6}).
 *
 * @retval     FSP_SUCCESS                     The local clock ID has been set.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL
 * @retval     FSP_ERR_INVALID_MODE            The instance is not in the correct state.
 **********************************************************************************************************************/
fsp_err_t R_PTP_LocalClockIdSet (ptp_ctrl_t * const p_ctrl, uint8_t const * const p_clock_id)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_clock_id);
    FSP_ERROR_RETURN(0U == R_ETHERC_EPTPC->SYRFL1R &&
                     0U == R_ETHERC_EPTPC->SYRFL2R &&
                     0U == R_ETHERC_EPTPC->SYTRENR,
                     FSP_ERR_INVALID_MODE);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    uint32_t sycidru = PTP_BYTES_TO_UINT32(p_clock_id);
    uint32_t sycidrl = PTP_BYTES_TO_UINT32(p_clock_id + 4U);

    /* SYNFP Local Clock ID Register (SYCIDRU, SYCIDRL). */
    R_ETHERC_EPTPC->SYCIDRU = sycidru;
    R_ETHERC_EPTPC->SYCIDRL = sycidrl;

    /* grandmasterIdentity Field Setting Register. */
    R_ETHERC_EPTPC->GMIDRU = sycidru;
    R_ETHERC_EPTPC->GMIDRL = sycidrl;

    /* Load GMIDRU and GMIDRL into the internal registers. */
    R_ETHERC_EPTPC->SYRVLDR = R_ETHERC_EPTPC_SYRVLDR_ANUP_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets the master clock ID and port ID that the local clock will synchronize with.
 * Implements @ref ptp_api_t::masterClockIdSet.
 *
 * @retval     FSP_SUCCESS                     The master clock ID and port ID have been set.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL
 **********************************************************************************************************************/
fsp_err_t R_PTP_MasterClockIdSet (ptp_ctrl_t * const p_ctrl, uint8_t const * const p_clock_id, uint16_t port_id)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_clock_id);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    uint32_t mtcidu = PTP_BYTES_TO_UINT32(p_clock_id);
    uint32_t mtcidl = PTP_BYTES_TO_UINT32(p_clock_id + 4U);

    /* Update master clock ID. */
    R_ETHERC_EPTPC->MTCIDU  = mtcidu;
    R_ETHERC_EPTPC->MTCIDL  = mtcidl;
    R_ETHERC_EPTPC->MTPID   = port_id;
    R_ETHERC_EPTPC->SYRVLDR = R_ETHERC_EPTPC_SYRVLDR_BMUP_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets the flags field for the given message type.
 * Implements @ref ptp_api_t::messageFlagsSet.
 *
 * @retval     FSP_SUCCESS                     The master clock ID and port ID have been set.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL or invalid.
 **********************************************************************************************************************/
fsp_err_t R_PTP_MessageFlagsSet (ptp_ctrl_t * const p_ctrl, ptp_message_type_t message_type, ptp_message_flags_t flags)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    switch (message_type)
    {
        case PTP_MESSAGE_TYPE_ANNOUNCE:
        {
#if PTP_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(0U == ((~PTP_ANNOUNCE_FLAGS_MASK) & flags.value));
#endif
            R_ETHERC_EPTPC->ANFR = flags.value;
            break;
        }

        case PTP_MESSAGE_TYPE_SYNC:
        {
#if PTP_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(0U == ((~PTP_SYNC_FLAGS_MASK) & flags.value));
#endif
            R_ETHERC_EPTPC->SYNFR = flags.value;
            break;
        }

        case PTP_MESSAGE_TYPE_DELAY_REQ:
        case PTP_MESSAGE_TYPE_PDELAY_REQ:
        {
#if PTP_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(0U == ((~PTP_P_DELAY_REQ_FLAGS_MASK) & flags.value));
#endif
            R_ETHERC_EPTPC->DYRQFR = flags.value;
            break;
        }

        case PTP_MESSAGE_TYPE_DELAY_RESP:
        case PTP_MESSAGE_TYPE_PDELAY_RESP:
        {
#if PTP_CFG_PARAM_CHECKING_ENABLE
            FSP_ASSERT(0U == ((~PTP_P_DELAY_RESP_FLAGS_MASK) & flags.value));
#endif
            R_ETHERC_EPTPC->DYRPFR = flags.value;
            break;
        }

        default:
        {
            return FSP_ERR_ASSERTION;
        }
    }

    /* Load settings into internal registers. */
    R_ETHERC_EPTPC->SYRVLDR = R_ETHERC_EPTPC_SYRVLDR_ANUP_Msk | R_ETHERC_EPTPC_SYRVLDR_STUP_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets the currentUtcOffset value in announce messages. @ref ptp_api_t::currentUtcOffsetSet.
 *
 * @retval     FSP_SUCCESS                              The currentUtcOffset has been updated.
 * @retval     FSP_ERR_NOT_OPEN                         The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION                        An argument was NULL or invalid.
 **********************************************************************************************************************/
fsp_err_t R_PTP_CurrentUtcOffsetSet (ptp_ctrl_t * const p_ctrl, uint16_t offset)
{
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;

#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    R_ETHERC_EPTPC->CUOTSR =
        (uint32_t) (p_instance_ctrl->p_cfg->synfp.timesource | (offset << R_ETHERC_EPTPC_CUOTSR_CUTO_Pos));

    /* Load settings into internal registers. */
    R_ETHERC_EPTPC->SYRVLDR = R_ETHERC_EPTPC_SYRVLDR_ANUP_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function changes the current state of the PTP instance. Implements @ref ptp_api_t::portStateSet.
 *
 * @retval     FSP_SUCCESS                     The instance will transition to the new state.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL
 **********************************************************************************************************************/
fsp_err_t R_PTP_PortStateSet (ptp_ctrl_t * const p_ctrl, uint32_t state)
{
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set TSLATR if it has not already be set. */
    if (0U == p_instance_ctrl->tslatr)
    {
        /* Read ECMR in order to determine the PHY bitrate. */
        uint32_t ecmr = R_ETHERC0->ECMR;
        uint32_t rtm  = (ecmr & R_ETHERC0_ECMR_RTM_Msk) >> R_ETHERC0_ECMR_RTM_Pos;

        /* Get the value of tslatr from lookup table. */
        ptp_tslatr_setting_t tsaltr_setting =
            g_tslatr_lut[p_instance_ctrl->p_cfg->synfp.ethernet_phy_interface][rtm][p_instance_ctrl->p_cfg->stca.
                                                                                    clock_freq];

        p_instance_ctrl->tslatr = tsaltr_setting.egp | (tsaltr_setting.ingp << R_ETHERC_EPTPC_TSLATR_INGP_Pos);
        R_ETHERC_EPTPC->TSLATR  = p_instance_ctrl->tslatr;
    }

    /*
     * A critical section is required in order to clear the delay request timeout status
     * without generating an IRQ.
     */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Disable clock synchronization when changing port state. */
    R_ETHERC_EPTPC_COMMON->SYNSTARTR = 0U;

    /* Enum values defined in ptp_port_state_t related to SYRFL1R map directly to the bitfields. */
    R_ETHERC_EPTPC->SYRFL1R = state & PTP_SYRFL1R_MASK;

    /*
     * Enum values defined in ptp_port_state_t related to SYRFL2R map directly to the bitfields but are shifted by 1 so that
     * all port state settings can fit in a 32 bit integer.
     */
    R_ETHERC_EPTPC->SYRFL2R = (state >> 1U) & PTP_SYRFL2R_MASK;

    /*
     * Enum values defined in ptp_port_state_t related to SYTRENR map directly to the bitfields but are shifted by 3 so that
     * all port state settings can fit in a 32 bit integer.
     */
    R_ETHERC_EPTPC->SYTRENR = (state >> 3U) & PTP_SYTRENR_MASK;

    /* Load settings into internal registers. */
    R_ETHERC_EPTPC->SYRVLDR = R_ETHERC_EPTPC_SYRVLDR_STUP_Msk;

    /* Suppress delay_req timeout IRQ when entering slave mode. */
    R_ETHERC_EPTPC->SYSR = R_ETHERC_EPTPC_SYSR_DRPTO_Msk;

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sends a PTP message. @ref ptp_api_t::messageSend.
 *
 * @retval     FSP_SUCCESS                              The packet has been written to the transmit descriptor.
 * @retval     FSP_ERR_NOT_OPEN                         The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION                        An argument was NULL or invalid.
 * @retval     FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL There is no space for the packet in the transmit queue.
 **********************************************************************************************************************/
fsp_err_t R_PTP_MessageSend (ptp_ctrl_t * const          p_ctrl,
                             ptp_message_t const * const p_message,
                             uint8_t const * const       p_tlv_data,
                             uint16_t                    tlv_data_size)
{
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;

#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_message);
    FSP_ASSERT(sizeof(ptp_message_header_t) < p_message->header.message_length);
    if (NULL == p_tlv_data)
    {
        FSP_ASSERT(0 == tlv_data_size);
    }
#endif

    /* Calculate the total size of the ethernet packet. */
    uint16_t packet_size = (uint16_t) (p_message->header.message_length + PTP_ETHER_HEADER_SIZE);

    if ((PTP_FRAME_FORMAT_IEEE802_3 == p_instance_ctrl->p_cfg->synfp.frame_format) ||
        (PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format))
    {
        packet_size = (uint16_t) (packet_size + PTP_LLC_HEADER_SIZE + PTP_SNAP_HEADER_SIZE);
    }

    if ((PTP_FRAME_FORMAT_ETHERII_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format) ||
        (PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format))
    {
        packet_size = (uint16_t) (packet_size + PTP_IPV4_HEADER_SIZE + PTP_UDP_HEADER_SIZE);
    }

#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl->p_cfg->buffer_size >= packet_size);
    FSP_ASSERT(PTP_ETHER_MAX_PACKET_SIZE >= packet_size);
#endif

    uint8_t          * p_packet         = p_instance_ctrl->p_cfg->p_tx_buffers[p_instance_ctrl->tx_buffer_write_index];
    edmac_instance_t * p_edmac_instance = p_instance_ctrl->p_cfg->p_edmac_instance;

    edmac_desc_t * p_desc;
    fsp_err_t      err = R_EDMAC_DescriptorGet(p_edmac_instance->p_ctrl,
                                               EDMAC_DESC_TRANSMIT,
                                               p_instance_ctrl->tx_buffer_write_index,
                                               &p_desc);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If the current buffer descriptor is active, then there is no more space in the transmit queue. */
    if (1U == p_desc->status.raw_b.active)
    {
        return FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL;
    }

    /* Add the Ethernet header. */
    r_ptp_append_ether_header(p_instance_ctrl, p_packet, packet_size);
    uint8_t * p_packet_append       = p_packet + PTP_ETHER_HEADER_SIZE;
    uint16_t  packet_size_remaining = (uint16_t) (packet_size - PTP_ETHER_HEADER_SIZE);

    if ((PTP_FRAME_FORMAT_IEEE802_3 == p_instance_ctrl->p_cfg->synfp.frame_format) ||
        (PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format))
    {
        /* Add LLC and SNAP headers. */
        r_ptp_append_ieee802_3_llc_snap_header(p_instance_ctrl, p_packet_append);

        p_packet_append      += PTP_LLC_HEADER_SIZE + PTP_SNAP_HEADER_SIZE;
        packet_size_remaining = (uint16_t) (packet_size_remaining - PTP_LLC_HEADER_SIZE - PTP_SNAP_HEADER_SIZE);
    }

    if ((PTP_FRAME_FORMAT_ETHERII_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format) ||
        (PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format))
    {
        /* Add IP and UDP header. */
        r_ptp_append_ipv4_udp_header(p_instance_ctrl, p_packet_append, packet_size_remaining);
        p_packet_append += PTP_IPV4_HEADER_SIZE + PTP_UDP_HEADER_SIZE;
    }

    uint32_t message_length = p_message->header.message_length;

    /* Copy the PTP message into the packet. */
    memcpy(p_packet_append, p_message, message_length - tlv_data_size);

    /* Convert PTP message fields to big endian. */
    r_ptp_message_endian_swap((ptp_message_t *) p_packet_append);

    p_packet_append += message_length - tlv_data_size;

    if (NULL != p_tlv_data)
    {
        /* Copy TLV data into the packet. */
        memcpy(p_packet_append, p_tlv_data, tlv_data_size);
        p_packet_append += tlv_data_size;
    }

    if (PTP_ETHER_MIN_PACKET_SIZE > packet_size)
    {
        /* Zero pad if the packet is smaller than the minimum Ethernet packet. */
        memset(p_packet_append, 0, PTP_ETHER_MIN_PACKET_SIZE - packet_size);
        packet_size = PTP_ETHER_MIN_PACKET_SIZE;
    }

    /* Disable the PTP EDMAC IRQ so that a transmit complete interrupt does not occur
     * before tx_buffer_write_index is incremented. */
    R_BSP_IrqDisable(p_edmac_instance->p_cfg->edmac_irq);

    /* Write the buffer into the buffer descriptor and set the status to active. */
    err = R_EDMAC_DescriptorUpdate(p_edmac_instance->p_ctrl,
                                   EDMAC_DESC_TRANSMIT,
                                   p_instance_ctrl->tx_buffer_write_index,
                                   p_packet,
                                   packet_size);

    if (FSP_SUCCESS != err)
    {
        R_BSP_IrqEnable(p_edmac_instance->p_cfg->edmac_irq);

        return err;
    }

    /* Go to the next space in the queue. */
    p_instance_ctrl->tx_buffer_write_index++;
    if (p_instance_ctrl->tx_buffer_write_index == p_edmac_instance->p_cfg->num_tx_desc)
    {
        p_instance_ctrl->tx_buffer_write_index = 0U;
    }

    R_BSP_IrqEnable(p_edmac_instance->p_cfg->edmac_irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets the local clock value. Implements @ref ptp_api_t::localClockValueSet.
 *
 * @retval     FSP_SUCCESS                     The local clock value has been set.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL or invalid.
 **********************************************************************************************************************/
fsp_err_t R_PTP_LocalClockValueSet (ptp_ctrl_t * const p_ctrl, ptp_time_t const * const p_time)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_time);
    FSP_ASSERT(1000000000U > p_time->nanoseconds);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /** IRQs disabled because LCIVRn registers must be set in consecutive operations
     * (See section 30.2.18 in the RA6M3 manual R01UH0886EJ0100). */
    __disable_irq();

    /* Set an initial value in the local clock counter. */
    R_ETHERC_EPTPC_COMMON->LCIVRU = (uint32_t) p_time->seconds_upper;
    R_ETHERC_EPTPC_COMMON->LCIVRM = p_time->seconds_lower;
    R_ETHERC_EPTPC_COMMON->LCIVRL = p_time->nanoseconds;

    /* Load the initial value into the local clock counter. */
    R_ETHERC_EPTPC_COMMON->LCIVLDR = 1;

    __enable_irq();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function gets the local clock value. Implements @ref ptp_api_t::localClockValueGet.
 *
 * @retval     FSP_SUCCESS                     The local clock value has been written in p_time.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL
 **********************************************************************************************************************/
fsp_err_t R_PTP_LocalClockValueGet (ptp_ctrl_t * const p_ctrl, ptp_time_t * const p_time)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_time);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Issue a directive to capture information. */
    R_ETHERC_EPTPC_COMMON->GETINFOR = 1U;

    /* Waiting for information capturing to complete.
     * (See Figure 30.27 in the RA6M3 manual R01UH0886EJ0100) */
    FSP_HARDWARE_REGISTER_WAIT(R_ETHERC_EPTPC_COMMON->GETINFOR, 0U);

    /* Read the value of the local clock counter from the LCCVR register. */
    p_time->seconds_upper = (uint16_t) R_ETHERC_EPTPC_COMMON->LCCVRU;
    p_time->seconds_lower = R_ETHERC_EPTPC_COMMON->LCCVRM;
    p_time->nanoseconds   = R_ETHERC_EPTPC_COMMON->LCCVRL;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function configures IPLS IRQ settings that are common to all pulse timer channels.
 * Implements @ref ptp_api_t::pulseTimerCommonConfig.
 *
 * @retval     FSP_SUCCESS                     The pulse timer has been enabled.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL or invalid.
 **********************************************************************************************************************/
fsp_err_t R_PTP_PulseTimerCommonConfig (ptp_ctrl_t * const p_ctrl, ptp_pulse_timer_common_cfg_t * const p_timer_cfg)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_timer_cfg);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /*
     * A critical section is required because timer functions cannot be re-entered while accessing common registers.
     */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Configure the IPLS IRQ for rising and falling edge for all channels. */
    uint32_t elippr = R_ETHERC_EPTPC_COMMON->ELIPPR;
    elippr &= ~(R_ETHERC_EPTPC_COMMON_ELIPPR_PLSP_Msk | R_ETHERC_EPTPC_COMMON_ELIPPR_PLSN_Msk);
    elippr |= (uint32_t) (p_timer_cfg->ipls_rising_irq << R_ETHERC_EPTPC_COMMON_ELIPPR_PLSP_Pos);
    elippr |= (uint32_t) (p_timer_cfg->ipls_falling_irq << R_ETHERC_EPTPC_COMMON_ELIPPR_PLSN_Pos);

    /* Configure auto clearing of the IPLS IRQ enable bits for rising and falling edges. */
    uint32_t elipacr = R_ETHERC_EPTPC_COMMON->ELIPACR;
    elipacr &= ~(R_ETHERC_EPTPC_COMMON_ELIPACR_PLSP_Msk | R_ETHERC_EPTPC_COMMON_ELIPACR_PLSN_Msk);
    elipacr |= (uint32_t) (p_timer_cfg->ipls_rising_irq_auto_clear << R_ETHERC_EPTPC_COMMON_ELIPACR_PLSP_Pos);
    elipacr |= (uint32_t) (p_timer_cfg->ipls_falling_irq_auto_clear << R_ETHERC_EPTPC_COMMON_ELIPACR_PLSN_Pos);

    /* Write settings to registers. */
    R_ETHERC_EPTPC_COMMON->ELIPPR  = elippr;
    R_ETHERC_EPTPC_COMMON->ELIPACR = elipacr;

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function enables a pulse timer channel. Implements @ref ptp_api_t::pulseTimerEnable.
 *
 * @retval     FSP_SUCCESS                     The pulse timer has been enabled.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL or invalid.
 **********************************************************************************************************************/
fsp_err_t R_PTP_PulseTimerEnable (ptp_ctrl_t * const p_ctrl, uint32_t channel,
                                  ptp_pulse_timer_cfg_t * const p_timer_cfg)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_timer_cfg);
    FSP_ASSERT(PTP_NUM_PULSE_TIMER >= channel);
    FSP_ASSERT(1000000000U > p_timer_cfg->start_time.nanoseconds);
    FSP_ASSERT(p_timer_cfg->period > p_timer_cfg->pulse);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Convert the time to nanoseconds. */
    uint64_t start_time = ((uint64_t) p_timer_cfg->start_time.seconds_upper << PTP_SHIFT_32) |
                          (uint64_t) p_timer_cfg->start_time.seconds_lower;
    start_time *= PTP_NANOSECONDS_IN_SECOND;
    start_time += p_timer_cfg->start_time.nanoseconds;

    /* Get pointer to the registers for this channel. */
    R_ETHERC_EPTPC_COMMON_TM_Type volatile * p_tm = &R_ETHERC_EPTPC_COMMON->TM[channel];

    p_tm->STTRU = (uint32_t) (start_time >> PTP_SHIFT_32);
    p_tm->STTRL = (uint32_t) (start_time & UINT32_MAX);
    p_tm->CYCR  = p_timer_cfg->period;
    p_tm->PLSR  = p_timer_cfg->pulse;

    /*
     * A critical section is required because timer functions cannot be re-entered while accessing common registers.
     */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Configure MINT IRQ for this channel. */
    uint32_t mieipr = R_ETHERC_EPTPC_COMMON->MIEIPR;
    mieipr &= ~(1U << (R_ETHERC_EPTPC_COMMON_MIEIPR_CYC0_Pos + channel));
    mieipr |= (uint32_t) p_timer_cfg->mint_rising_irq << (R_ETHERC_EPTPC_COMMON_MIEIPR_CYC0_Pos + channel);
    uint32_t mitselr = R_ETHERC_EPTPC_COMMON->MITSELR;
    mitselr &= ~(1U << channel);
    mitselr |= (uint32_t) p_timer_cfg->mint_rising_irq << channel;

    /* Configure rising and falling edge ELC events for this channel. */
    uint32_t elippr = R_ETHERC_EPTPC_COMMON->ELIPPR;
    elippr &= ~(1U << channel);
    elippr &= ~(1U << (R_ETHERC_EPTPC_COMMON_ELIPPR_CYCN0_Pos + channel));
    elippr |= (uint32_t) (p_timer_cfg->ipls_rising_event << channel);
    elippr |= (uint32_t) (p_timer_cfg->ipls_falling_event << (R_ETHERC_EPTPC_COMMON_ELIPPR_CYCN0_Pos + channel));

    /* Configure auto clearing of ELC event enable bits for rising and falling edge. */
    uint32_t elipacr = R_ETHERC_EPTPC_COMMON->ELIPACR;
    elipacr &= ~(1U << channel);
    elipacr &= ~(1U << (R_ETHERC_EPTPC_COMMON_ELIPACR_CYCN0_Pos + channel));
    elipacr |= (uint32_t) (p_timer_cfg->ipls_rising_event_auto_clear << channel);
    elipacr |=
        (uint32_t) (p_timer_cfg->ipls_falling_event_auto_clear << (R_ETHERC_EPTPC_COMMON_ELIPACR_CYCN0_Pos + channel));

    /* Configure IPLS IRQ for this channel. */
    uint32_t iptselr = R_ETHERC_EPTPC_COMMON->IPTSELR;
    iptselr &= ~(1U << channel);
    iptselr |= (uint32_t) (p_timer_cfg->ipls_irq_source << channel);

    /* Write settings to registers. */
    R_ETHERC_EPTPC_COMMON->MIEIPR  = mieipr;
    R_ETHERC_EPTPC_COMMON->ELIPPR  = elippr;
    R_ETHERC_EPTPC_COMMON->ELIPACR = elipacr;
    R_ETHERC_EPTPC_COMMON->IPTSELR = iptselr;
    R_ETHERC_EPTPC_COMMON->MITSELR = mitselr;

    /* Start the pulse timer. */
    R_ETHERC_EPTPC_COMMON->TMSTARTR |= (1U << channel);

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function disables a pulse timer channel. Implements @ref ptp_api_t::pulseTimerDisable.
 *
 * @retval     FSP_SUCCESS                     The pulse timer has been disabled.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL or invalid.
 **********************************************************************************************************************/
fsp_err_t R_PTP_PulseTimerDisable (ptp_ctrl_t * const p_ctrl, uint32_t channel)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(PTP_NUM_PULSE_TIMER >= channel);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /*
     * A critical section is required because timer functions cannot be re-entered while accessing common registers.
     */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Disable the pulse timer. */
    R_ETHERC_EPTPC_COMMON->TMSTARTR &= ~(1U << channel);

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable the PTP instance. Implements @ref ptp_api_t::close.
 *
 * @retval     FSP_SUCCESS                     The pulse timer has been disabled.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL or invalid.
 **********************************************************************************************************************/
fsp_err_t R_PTP_Close (ptp_ctrl_t * const p_ctrl)
{
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) p_ctrl;
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(PTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    edmac_instance_t * p_edmac_instance = p_instance_ctrl->p_cfg->p_edmac_instance;

    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->mint_irq);
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->ipls_irq);

    R_EDMAC_Close(p_edmac_instance->p_ctrl);

    r_ptp_hw_reset();

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function compares two clocks to determine which one is the better master clock.
 *
 * p_comparison:
 * - Set to -1 if p_announce1 defines the best master clock.
 * - Set to 1 if p_announce2 defines the best master clock.
 * - Set to 0 if p_announce1 and p_announce2 define the same clock.
 *
 * @retval     FSP_SUCCESS                     The valid result has been written to p_use_announce_clock.
 * @retval     FSP_ERR_ASSERTION               An argument was NULL.
 **********************************************************************************************************************/
fsp_err_t R_PTP_BestMasterClock (ptp_message_t const * const p_announce1,
                                 ptp_message_t const * const p_announce2,
                                 int8_t * const              p_comparison)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_announce1);
    FSP_ASSERT(NULL != p_announce2);
    FSP_ASSERT(NULL != p_comparison);
    FSP_ASSERT(PTP_MESSAGE_TYPE_ANNOUNCE == p_announce1->header.message_type);
    FSP_ASSERT(PTP_MESSAGE_TYPE_ANNOUNCE == p_announce2->header.message_type);
#endif

    int parent_id_comparison      = memcmp(p_announce1->header.clock_id, p_announce2->header.clock_id, 8);
    int grandmaster_id_comparison = memcmp(p_announce1->announce.clock_id, p_announce2->announce.clock_id, 8);

    /** If the parent ID is identical than these messages originate from the same clock. */
    PTP_CMP_RETURN(p_comparison, 0 == parent_id_comparison, 0);

    if (0 != grandmaster_id_comparison)
    {
        /* Compare clock properties to determine which grandmaster clock is the best. */
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.priority1 < p_announce2->announce.clock_properties.priority1,
                       -1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.priority1 > p_announce2->announce.clock_properties.priority1,
                       1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.cclass < p_announce2->announce.clock_properties.cclass,
                       -1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.cclass > p_announce2->announce.clock_properties.cclass,
                       1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.accuracy < p_announce2->announce.clock_properties.accuracy,
                       -1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.accuracy > p_announce2->announce.clock_properties.accuracy,
                       1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.variance < p_announce2->announce.clock_properties.variance,
                       -1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.variance > p_announce2->announce.clock_properties.variance,
                       1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.priority2 < p_announce2->announce.clock_properties.priority2,
                       -1);
        PTP_CMP_RETURN(p_comparison,
                       p_announce1->announce.clock_properties.priority2 > p_announce2->announce.clock_properties.priority2,
                       1);

        /* If all of the clock properties are equal, then the smallest grandmaster clock ID is best. */
        *p_comparison = (int8_t) grandmaster_id_comparison;

        return FSP_SUCCESS;
    }

    /* If the grandmaster clock ID is identical then determine which parent clock is best. */

    PTP_CMP_RETURN(p_comparison, p_announce1->announce.steps_removed < p_announce2->announce.steps_removed, -1);
    PTP_CMP_RETURN(p_comparison, p_announce1->announce.steps_removed > p_announce2->announce.steps_removed, 1);

    *p_comparison = (int8_t) parent_id_comparison;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup PTP)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Reset the PTP peripheral using PTRSTR.
 **********************************************************************************************************************/
static void r_ptp_hw_reset (void)
{
    uint32_t pclka_freq = SystemCoreClock << R_SYSTEM->SCKDIVCR_b.ICK;
    pclka_freq >>= R_SYSTEM->SCKDIVCR_b.PCKA;

    uint32_t delay_microseconds = PTP_PCLKA_RESET_CYCLES * BSP_DELAY_UNITS_SECONDS / pclka_freq + 1U;

    /* Reset the PTP module. */
    R_ETHERC_EPTPC_CFG->PTRSTR = 1;

    /* Wait 64 cycles of PCLKA for the PTP peripheral to reset
     * (See section 30.2.77 of the RA6M3 manual R01UH0886EJ0100). */
    R_BSP_SoftwareDelay(delay_microseconds, BSP_DELAY_UNITS_MICROSECONDS);

    R_ETHERC_EPTPC_CFG->PTRSTR = 0;
}

/*******************************************************************************************************************//**
 * Writes the configuration settings into the PTP registers.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 **********************************************************************************************************************/
static void r_ptp_hw_config (ptp_instance_ctrl_t * p_instance_ctrl)
{
    ptp_cfg_t const * const p_cfg = p_instance_ctrl->p_cfg;

    /* Set the number of times the offsetFromMaster must be above the threshold for sync to be lost. */
    uint32_t stmr = (uint32_t) (p_cfg->stca.sync_threshold.count << R_ETHERC_EPTPC_COMMON_STMR_DVTH_Pos);

    /* Set the number of times the offsetFromMaster must be below the threshold for sync to be aquired. */
    stmr |= (uint32_t) (p_cfg->stca.sync_loss_threshold.count << R_ETHERC_EPTPC_COMMON_STMR_SYTH_Pos);

    /* Enable the SYNCOUT and SYNTOUT flags in STSR. */
    stmr |= R_ETHERC_EPTPC_COMMON_STMR_ALEN0_Msk | R_ETHERC_EPTPC_COMMON_STMR_ALEN1_Msk;

    /* Configure gradient worst10 aquisition. */
    if (PTP_CLOCK_CORRECTION_MODE2 == p_cfg->stca.clock_correction_mode)
    {
        /* Enable clock correction mode 2. */
        stmr |= R_ETHERC_EPTPC_COMMON_STMR_CMOD_Msk;

        /* Set the interval for calculating worst10 gradients. */
        stmr |= (uint32_t) (p_cfg->stca.gradient_worst10_interval << R_ETHERC_EPTPC_COMMON_STMR_WINT_Pos);

        /* Set worst10 aquistion mode to software start. */
        stmr |= R_ETHERC_EPTPC_COMMON_STMR_W10S_Msk;
    }

    /* Set the value of Synchronization Loss Detection Threshold Register. */
    uint32_t syntdaru = (uint32_t) (p_cfg->stca.sync_loss_threshold.threshold >> PTP_SHIFT_32);
    uint32_t syntdarl =
        (uint32_t) (p_cfg->stca.sync_loss_threshold.threshold & R_ETHERC_EPTPC_COMMON_SYNTDARL_SYNTDARL_Msk);

    /* Set the value of Synchronization Detection Threshold Register. */
    uint32_t syntdbru = (uint32_t) (p_cfg->stca.sync_threshold.threshold >> PTP_SHIFT_32);
    uint32_t syntdbrl = (uint32_t) (p_cfg->stca.sync_threshold.threshold & R_ETHERC_EPTPC_COMMON_SYNTDBRL_SYNTDBRL_Msk);

    /* SYNFP Transmission Interval Setting Register. */
    uint32_t sytlir = (uint32_t) p_cfg->synfp.announce_interval << R_ETHERC_EPTPC_SYTLIR_ANCE_Pos;
    sytlir |= (uint32_t) p_cfg->synfp.sync_interval << R_ETHERC_EPTPC_SYTLIR_SYNC_Pos;
    sytlir |= (uint32_t) p_cfg->synfp.delay_req_interval << R_ETHERC_EPTPC_SYTLIR_DREQ_Pos;

    /* grandmasterClockQuality Field Setting Register. */
    uint32_t gmcqr = 0;
    gmcqr |= (uint32_t) (p_cfg->synfp.clock_properties.cclass << 24U);
    gmcqr |= (uint32_t) (p_cfg->synfp.clock_properties.accuracy << 16U);
    gmcqr |= (uint32_t) (p_cfg->synfp.clock_properties.variance << 0U);

    uint64_t delay_resp_timeout = (uint64_t) p_cfg->synfp.message_timeout *
                                  (PTP_NANOSECONDS_IN_SECOND / PTP_MILLISECONDS_IN_SECOND / PTP_TIMEOUT_DIVIDER);
    if (delay_resp_timeout > UINT32_MAX)
    {
        delay_resp_timeout = UINT32_MAX;
    }

    R_BSP_MODULE_START(FSP_IP_EPTPC, 0);

    r_ptp_hw_reset();

    /* Set the value of STCA Clock Select Register. */
    R_ETHERC_EPTPC_CFG->STCSELR = (uint32_t) p_cfg->stca.clock_sel;

    /* Set the value of the STCA Clock Frequency Setting Register. */
    R_ETHERC_EPTPC_COMMON->STCFR = (uint32_t) p_cfg->stca.clock_freq;

    if (PTP_FRAME_FILTER_MODE_UNICAST_MULTICAST_FILTERED == p_cfg->synfp.frame_filter)
    {
        /* Set the value of Frame Reception Filter MAC Address 0 Setting Register */
        uint32_t fmac0ru = (uint32_t) (p_cfg->synfp.p_multicast_addr_filter[0] << 16U);
        fmac0ru |= (uint32_t) (p_cfg->synfp.p_multicast_addr_filter[1] << 8U);
        fmac0ru |= (uint32_t) (p_cfg->synfp.p_multicast_addr_filter[2] << 0U);
        uint32_t fmac0rl = (uint32_t) (p_cfg->synfp.p_multicast_addr_filter[3] << 16U);
        fmac0rl |= (uint32_t) (p_cfg->synfp.p_multicast_addr_filter[4] << 8U);
        fmac0rl |= (uint32_t) (p_cfg->synfp.p_multicast_addr_filter[5] << 0U);

        R_ETHERC_EPTPC->FMAC0RU = fmac0ru;
        R_ETHERC_EPTPC->FMAC0RL = fmac0rl;
    }

    if ((PTP_FRAME_FORMAT_ETHERII == p_cfg->synfp.frame_format) ||
        (PTP_FRAME_FORMAT_IEEE802_3 == p_cfg->synfp.frame_format))
    {
        /* Set the value of PTP-primary Message Destination MAC Address Setting Register. */
        uint32_t ppmacru = (uint32_t) (p_cfg->synfp.ether.p_primary_mac_addr[0] << 16U);
        ppmacru |= (uint32_t) (p_cfg->synfp.ether.p_primary_mac_addr[1] << 8U);
        ppmacru |= (uint32_t) (p_cfg->synfp.ether.p_primary_mac_addr[2] << 0U);
        uint32_t ppmacrl = (uint32_t) (p_cfg->synfp.ether.p_primary_mac_addr[3] << 16U);
        ppmacrl |= (uint32_t) (p_cfg->synfp.ether.p_primary_mac_addr[4] << 8U);
        ppmacrl |= (uint32_t) (p_cfg->synfp.ether.p_primary_mac_addr[5] << 0U);

        /* Set the value of PTP-pdelay Message MAC Address Setting Register. */
        uint32_t pdmacru = (uint32_t) (p_cfg->synfp.ether.p_pdelay_mac_addr[0] << 16U);
        pdmacru |= (uint32_t) (p_cfg->synfp.ether.p_pdelay_mac_addr[1] << 8U);
        pdmacru |= (uint32_t) (p_cfg->synfp.ether.p_pdelay_mac_addr[2] << 0U);
        uint32_t pdmacrl = (uint32_t) (p_cfg->synfp.ether.p_pdelay_mac_addr[3] << 16U);
        pdmacrl |= (uint32_t) (p_cfg->synfp.ether.p_pdelay_mac_addr[4] << 8U);
        pdmacrl |= (uint32_t) (p_cfg->synfp.ether.p_pdelay_mac_addr[5] << 0U);

        R_ETHERC_EPTPC->PPMACRU = ppmacru;
        R_ETHERC_EPTPC->PPMACRL = ppmacrl;
        R_ETHERC_EPTPC->PDMACRU = pdmacru;
        R_ETHERC_EPTPC->PDMACRL = pdmacrl;
    }
    else
    {
        /* Set the value of the PTP-primary Message Destination IP Address Setting Register. */
        R_ETHERC_EPTPC->PPIPR = p_cfg->synfp.ipv4.primary_ip_addr;

        /* Set the value of the PTP-pdelay Message Destination IP Address Setting Register. */
        R_ETHERC_EPTPC->PDIPR = p_cfg->synfp.ipv4.pdelay_ip_addr;

        /* Set the value of the PTP Event Message TOS Register. */
        R_ETHERC_EPTPC->PETOSR = p_cfg->synfp.ipv4.event_tos;

        /* Set the value of the PTP General Message TOS Register. */
        R_ETHERC_EPTPC->PGTOSR = p_cfg->synfp.ipv4.general_tos;

        /* Set the value of the PTP-primary Message TTL Settig Register. */
        R_ETHERC_EPTPC->PPTTLR = p_cfg->synfp.ipv4.primary_ttl;

        /* Set the value of the PTP-pdelay Message TTL Settig Register. */
        R_ETHERC_EPTPC->PDTTLR = p_cfg->synfp.ipv4.pdelay_ttl;

        /* Set the value of the PTP Event Message UDP Destination Port Number Setting Register. */
        R_ETHERC_EPTPC->PEUDPR = p_cfg->synfp.ipv4.event_udp_port;

        /* Set the value of the PTP General Message UDP Destination Port Number Setting Register. */
        R_ETHERC_EPTPC->PGUDPR = p_cfg->synfp.ipv4.general_udp_port;
    }

    /* Write to PTP registers. */
    R_ETHERC_EPTPC_COMMON->MIEIPR   = R_ETHERC_EPTPC_COMMON_MIEIPR_SY0_Msk | R_ETHERC_EPTPC_COMMON_MIEIPR_ST_Msk;
    R_ETHERC_EPTPC_COMMON->STIPR    = PTP_STIPR_MASK;
    R_ETHERC_EPTPC_COMMON->STMR     = stmr;
    R_ETHERC_EPTPC_COMMON->SYNTOR   = p_cfg->synfp.message_timeout / PTP_TIMEOUT_DIVIDER;
    R_ETHERC_EPTPC_COMMON->SYNTDARU = syntdaru;
    R_ETHERC_EPTPC_COMMON->SYNTDARL = syntdarl;
    R_ETHERC_EPTPC_COMMON->SYNTDBRU = syntdbru;
    R_ETHERC_EPTPC_COMMON->SYNTDBRL = syntdbrl;
    R_ETHERC_EPTPC->SYIPR           = PTP_SYIPR_MASK;
    R_ETHERC_EPTPC->SYSPVRR         = (PTP_VERSION << R_ETHERC_EPTPC_SYSPVRR_VER_Pos);
    R_ETHERC_EPTPC->SYDOMR          = p_cfg->synfp.clock_domain;
    R_ETHERC_EPTPC->SYPNUMR         = 1U;
    R_ETHERC_EPTPC->GMPR            = (uint32_t) (p_cfg->synfp.clock_properties.priority2 |
                                                  (p_cfg->synfp.clock_properties.priority1 <<
                                        R_ETHERC_EPTPC_GMPR_GMPR1_Pos));
    R_ETHERC_EPTPC->GMCQR   = gmcqr;
    R_ETHERC_EPTPC->CUOTSR  = (uint32_t) p_cfg->synfp.timesource;
    R_ETHERC_EPTPC->SYTLIR  = sytlir;
    R_ETHERC_EPTPC->PETYPER = PTP_ETHER_TYPE_PTP;
    R_ETHERC_EPTPC->FFLTR   = (uint32_t) p_cfg->synfp.frame_filter;
    R_ETHERC_EPTPC->SYCONFR = (uint32_t) (p_cfg->synfp.clock_domain_filter << R_ETHERC_EPTPC_SYCONFR_FILDIS_Pos) |
                              PTP_SYNFP_SYCONFR_TCYC;
    R_ETHERC_EPTPC->SYFORMR = (uint32_t) p_cfg->synfp.frame_format;
    R_ETHERC_EPTPC->RSTOUTR = (uint32_t) delay_resp_timeout;

    /* Load settings into internal registers. */
    R_ETHERC_EPTPC->SYRVLDR = R_ETHERC_EPTPC_SYRVLDR_BMUP_Msk |
                              R_ETHERC_EPTPC_SYRVLDR_STUP_Msk |
                              R_ETHERC_EPTPC_SYRVLDR_ANUP_Msk;
}

/*******************************************************************************************************************//**
 * Calcualtes the appropriate timeout value based off of the given log_interval.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 * @param[in]  log_interval              log_interval
 *
 * @return     Timeout value
 **********************************************************************************************************************/
static uint32_t r_ptp_calculate_timeout (ptp_instance_ctrl_t * p_instance_ctrl, int8_t log_interval)
{
    /* If the inteval is less then (1 / 128) seconds, assume interval is (1 / 128) seconds. */
    if (PTP_MESSAGE_INTERVAL_1_128 > log_interval)
    {
        log_interval = PTP_MESSAGE_INTERVAL_1_128;
    }
    /* If the interval is greater than 64 seconds, assume interval is 64 seconds. */
    else if (PTP_MESSAGE_INTERVAL_64 < log_interval)
    {
        log_interval = PTP_MESSAGE_INTERVAL_64;
    }
    else
    {
    }

    uint64_t timeout = 0;

    /** Convert the message timeout to nanoseconds. */
    uint64_t message_timeout_ns = (uint64_t) p_instance_ctrl->p_cfg->synfp.message_timeout *
                                  (PTP_NANOSECONDS_IN_SECOND / PTP_MILLISECONDS_IN_SECOND / PTP_TIMEOUT_DIVIDER);

    /* Set the timeout to (message period + message_timeout). */
    if (log_interval < 0)
    {
        log_interval = (int8_t) (log_interval * -1);
        timeout      = (PTP_NANOSECONDS_IN_SECOND / PTP_TIMEOUT_DIVIDER) >> log_interval;
    }
    else
    {
        timeout = (PTP_NANOSECONDS_IN_SECOND / PTP_TIMEOUT_DIVIDER) << log_interval;
    }

    timeout += message_timeout_ns;

    /* If the timeout is to large to fit in a 32bit int, clamp the value at UINT32_MAX. */
    if (timeout > UINT32_MAX)
    {
        timeout = UINT32_MAX;
    }

    return (uint32_t) (timeout & UINT32_MAX);
}

/*******************************************************************************************************************//**
 * Performs endian swap on PTP message fields.
 *
 * @param[in]  p_message                 Pointer to message to endian swap.
 **********************************************************************************************************************/
static void r_ptp_message_endian_swap (ptp_message_t * p_message)
{
    p_message->header.message_length = (uint16_t) __REV16(p_message->header.message_length);
    p_message->header.flags.value    = (uint16_t) __REV16(p_message->header.flags.value);
    p_message->header.source_port_id = (uint16_t) __REV16(p_message->header.source_port_id);
    p_message->header.sequence_id    = (uint16_t) __REV16(p_message->header.sequence_id);

    uint32_t correction_upper = (uint32_t) (p_message->header.correction_field >> PTP_SHIFT_32);
    uint32_t correction_lower = (uint32_t) (p_message->header.correction_field & UINT32_MAX);
    p_message->header.correction_field = ((uint64_t) __REV(correction_lower) << PTP_SHIFT_32) | __REV(correction_upper);

    if (PTP_MESSAGE_TYPE_ANNOUNCE == p_message->header.message_type)
    {
        p_message->announce.current_utc_offset        = (uint16_t) __REV16(p_message->announce.current_utc_offset);
        p_message->announce.clock_properties.variance =
            (uint16_t) __REV16(p_message->announce.clock_properties.variance);
        p_message->announce.steps_removed = (uint16_t) __REV16(p_message->announce.steps_removed);
    }

    if ((PTP_MESSAGE_TYPE_MANAGEMENT == p_message->header.message_type) ||
        (PTP_MESSAGE_TYPE_SIGNALING == p_message->header.message_type))
    {
        /* Target Port ID is common to both management and signaling messages. */
        p_message->management.target_port_id = (uint16_t) __REV16(p_message->management.target_port_id);
    }
    else
    {
        /* Origin timestamp is common to all other message types. */
        p_message->sync.origin_timestamp.seconds_upper = (uint16_t) __REV16(
            p_message->sync.origin_timestamp.seconds_upper);
        p_message->sync.origin_timestamp.seconds_lower = __REV(p_message->sync.origin_timestamp.seconds_lower);
        p_message->sync.origin_timestamp.nanoseconds   = __REV(p_message->sync.origin_timestamp.nanoseconds);
    }
}

/*******************************************************************************************************************//**
 * Add an Ethernet header to a packet.
 *
 * @param[in]  p_instance_ctrl           Instance control block.
 * @param[in]  p_packet                  packet to add an Ethernet header to.
 * @param[in]  packet_length             size of the packet in bytes.
 **********************************************************************************************************************/
static void r_ptp_append_ether_header (ptp_instance_ctrl_t * p_instance_ctrl, uint8_t * p_packet,
                                       uint16_t packet_length)
{
    ptp_ether_header_t * p_ether_header = (ptp_ether_header_t *) p_packet;

    /* Write the source MAC address. */
    uint32_t symacru = R_ETHERC_EPTPC->SYMACRU;
    uint32_t symacrl = R_ETHERC_EPTPC->SYMACRL;
    p_ether_header->source_mac_address[0U] = (uint8_t) (symacru >> 16U) & UINT8_MAX;
    p_ether_header->source_mac_address[1U] = (uint8_t) (symacru >> 8U) & UINT8_MAX;
    p_ether_header->source_mac_address[2U] = (uint8_t) (symacru >> 0U) & UINT8_MAX;
    p_ether_header->source_mac_address[3U] = (uint8_t) (symacrl >> 16U) & UINT8_MAX;
    p_ether_header->source_mac_address[4U] = (uint8_t) (symacrl >> 8U) & UINT8_MAX;
    p_ether_header->source_mac_address[5U] = (uint8_t) (symacrl >> 0U) & UINT8_MAX;

    if ((PTP_FRAME_FORMAT_ETHERII == p_instance_ctrl->p_cfg->synfp.frame_format) ||
        (PTP_FRAME_FORMAT_IEEE802_3 == p_instance_ctrl->p_cfg->synfp.frame_format))
    {
        /* Write the destination MAC address. */
        memcpy(p_ether_header->destination_mac_address, p_instance_ctrl->p_cfg->synfp.ether.p_primary_mac_addr,
               sizeof(p_ether_header->destination_mac_address));
    }
    else
    {
        uint32_t dest_ip_addr = p_instance_ctrl->p_cfg->synfp.ipv4.primary_ip_addr;
        dest_ip_addr &= PTP_IP_MULTICAST_ADDRESS_MASK;

        /* Compute the multicast MAC address from the IP address. */
        p_ether_header->destination_mac_address[0U] = (PTP_IP_MULTICAST_MAC_ADDRESS_PREFIX >> 16U) & UINT8_MAX;
        p_ether_header->destination_mac_address[1U] = (PTP_IP_MULTICAST_MAC_ADDRESS_PREFIX >> 8U) & UINT8_MAX;
        p_ether_header->destination_mac_address[2U] = (PTP_IP_MULTICAST_MAC_ADDRESS_PREFIX >> 0U) & UINT8_MAX;
        p_ether_header->destination_mac_address[3U] = (dest_ip_addr >> 16U) & UINT8_MAX;
        p_ether_header->destination_mac_address[4U] = (dest_ip_addr >> 8U) & UINT8_MAX;
        p_ether_header->destination_mac_address[5U] = (dest_ip_addr >> 0U) & UINT8_MAX;
    }

    /* Write the EtherType field. */
    switch (p_instance_ctrl->p_cfg->synfp.frame_format)
    {
        case PTP_FRAME_FORMAT_ETHERII:
        {
            p_ether_header->ether_type = (uint16_t) __REV16(PTP_ETHER_TYPE_PTP);
            break;
        }

        case PTP_FRAME_FORMAT_ETHERII_IPV4_UDP:
        {
            p_ether_header->ether_type = (uint16_t) __REV16(PTP_ETHER_TYPE_IPV4);
            break;
        }

        case PTP_FRAME_FORMAT_IEEE802_3:
        case PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP:
        {
            uint16_t size = (uint16_t) (packet_length - PTP_ETHER_HEADER_SIZE);
            p_ether_header->ether_type = (uint16_t) __REV16(size);
            break;
        }

        default:
        {
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Add the LLC and SNAP headers to the ieee802_3 header.
 *
 * @param[in]  p_instance_ctrl           Instance control block.
 * @param[in]  p_packet                  Packet to add an LLC and SNAP header to.
 **********************************************************************************************************************/
static void r_ptp_append_ieee802_3_llc_snap_header (ptp_instance_ctrl_t * p_instance_ctrl, uint8_t * p_packet)
{
    uint8_t * p_llc_header  = p_packet;
    uint8_t * p_snap_header = p_packet + PTP_LLC_HEADER_SIZE;

    p_llc_header[PTP_LLC_SAP_SSAP_OFFSET] = PTP_LLC_SAP_SNAP;
    p_llc_header[PTP_LLC_SAP_DSAP_OFFSET] = PTP_LLC_SAP_SNAP;
    p_llc_header[PTP_LLC_CTRL_OFFSET]     = PTP_LLC_CTRL_FORMAT_U;

    uint32_t symacru = R_ETHERC_EPTPC->SYMACRU;
    p_snap_header[PTP_SNAP_OID_OFFSET + 0] = (uint8_t) (symacru >> 16U) & UINT8_MAX;
    p_snap_header[PTP_SNAP_OID_OFFSET + 1] = (uint8_t) (symacru >> 8U) & UINT8_MAX;
    p_snap_header[PTP_SNAP_OID_OFFSET + 2] = (uint8_t) (symacru >> 0U) & UINT8_MAX;

    if ((PTP_FRAME_FORMAT_ETHERII_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format) ||
        (PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP == p_instance_ctrl->p_cfg->synfp.frame_format))
    {
        p_snap_header[PTP_SNAP_PID_OFFSET + 0] = PTP_ETHER_TYPE_IPV4 >> 8;
        p_snap_header[PTP_SNAP_PID_OFFSET + 1] = PTP_ETHER_TYPE_IPV4 & UINT8_MAX;
    }
    else
    {
        p_snap_header[PTP_SNAP_PID_OFFSET + 0] = PTP_ETHER_TYPE_PTP >> 8;
        p_snap_header[PTP_SNAP_PID_OFFSET + 1] = PTP_ETHER_TYPE_PTP & UINT8_MAX;
    }
}

/*******************************************************************************************************************//**
 * Compute the checksum of an IP header.
 *
 * @param[in]  p_ip_header               Pointer to an IP header.
 **********************************************************************************************************************/
uint16_t r_ptp_ip_checksum (uint8_t * p_ip_header)
{
    uint16_t * p_ip_header16 = (uint16_t *) p_ip_header;

    /* Get the IP header length in words. */
    uint32_t ihl = p_ip_header16[0] & 0x0FU;

    /* Compunte checksum. */
    uint32_t sum = 0;
    for (uint32_t i = 0; i < ihl * 2; i++)
    {
        sum += p_ip_header16[i];
    }

    /* Add the carry bits to the sum and clear them. */
    uint32_t carry = sum >> 16U;
    sum &= UINT16_MAX;
    sum += carry;

    /* Do it again in case a carry occurred when adding carry bits. */
    carry = sum >> 16U;
    sum  &= UINT16_MAX;
    sum  += carry;

    /* One's complement the result. */
    uint16_t sum16 = sum & UINT16_MAX;
    sum16 = (uint16_t) ~sum16 & UINT16_MAX;

    return sum16;
}

/*******************************************************************************************************************//**
 * Add an IP and UDP header to a packet.
 *
 * @param[in]  p_instance_ctrl           Instance control block.
 * @param[in]  p_packet                  Packet to add an IP and UDP header to.
 * @param[in]  packet_length             Size of the packet in bytes.
 **********************************************************************************************************************/
static void r_ptp_append_ipv4_udp_header (ptp_instance_ctrl_t * p_instance_ctrl,
                                          uint8_t             * p_packet,
                                          uint16_t              packet_length)
{
    ptp_ip_header_t  * p_ip_header  = (ptp_ip_header_t *) p_packet;
    ptp_udp_header_t * p_udp_header = (ptp_udp_header_t *) (p_packet + sizeof(ptp_ip_header_t));

    p_ip_header->version             = PTP_IP_VERSION;
    p_ip_header->ihl                 = 5;
    p_ip_header->tos                 = p_instance_ctrl->p_cfg->synfp.ipv4.general_tos;
    p_ip_header->total_length        = (uint16_t) __REV16(packet_length);
    p_ip_header->id                  = 0;
    p_ip_header->flags               = 0;
    p_ip_header->fragment_offset     = 0;
    p_ip_header->ttl                 = p_instance_ctrl->p_cfg->synfp.ipv4.primary_ttl;
    p_ip_header->protocol            = PTP_IP_PROTOCOL_UDP;
    p_ip_header->checksum            = 0;
    p_ip_header->source_address      = __REV(R_ETHERC_EPTPC->SYIPADDRR);
    p_ip_header->destination_address = __REV(p_instance_ctrl->p_cfg->synfp.ipv4.primary_ip_addr);
    p_udp_header->source_port        = (uint16_t) __REV16(p_instance_ctrl->p_cfg->synfp.ipv4.general_udp_port);
    p_udp_header->destination_port   = (uint16_t) __REV16(p_instance_ctrl->p_cfg->synfp.ipv4.general_udp_port);
    p_udp_header->length             = (uint16_t) __REV16((packet_length - sizeof(ptp_ip_header_t)));
    p_udp_header->checksum           = 0;

    p_ip_header->checksum = r_ptp_ip_checksum(p_packet);
}

/*******************************************************************************************************************//**
 * Removes the IEEE802.3 + LLC + SNAP header from a packet.
 *
 * @param[in]  p_llc_snap_packet         Pointer to an IEEE802.3 + LLC + SNAP frame.
 * @param[in]  llc_snap_packet_length    Length of the packet.
 * @param[out] p_ether_type              EtherType field defined in the SNAP header.
 * @param[out] p_payload                 Pointer to a pointer to store the payload of the packet.
 * @param[out] payload_length            Pointer to store the payload length.
 *
 * @retval     FSP_SUCCESS               The frame was successfully processed.
 * @retval     FSP_ERR_ASSERTION         There was an error parsing the frame.
 **********************************************************************************************************************/
static fsp_err_t r_ptp_process_llc_snap_packet (uint8_t const * const p_llc_snap_packet,
                                                uint16_t              llc_snap_packet_length,
                                                uint16_t            * p_ether_type,
                                                uint8_t ** const      p_payload,
                                                uint16_t * const      payload_length)
{
    /* Extract LLC header information. */
    uint8_t dsap = p_llc_snap_packet[PTP_LLC_SAP_DSAP_OFFSET] & PTP_LLC_SAP_MASK;
    uint8_t ssap = p_llc_snap_packet[PTP_LLC_SAP_SSAP_OFFSET] & PTP_LLC_SAP_MASK;
    uint8_t ctrl = p_llc_snap_packet[PTP_LLC_CTRL_OFFSET];

    if ((PTP_LLC_SAP_SNAP != dsap) || (PTP_LLC_SAP_SNAP != ssap) || (PTP_LLC_CTRL_FORMAT_U != ctrl))
    {

        /* Packet does not have snap header. */
        return FSP_ERR_ASSERTION;
    }

    *p_ether_type = (uint16_t) ((p_llc_snap_packet[PTP_LLC_HEADER_SIZE + PTP_SNAP_PID_OFFSET + 0U] << 8U) |
                                (p_llc_snap_packet[PTP_LLC_HEADER_SIZE + PTP_SNAP_PID_OFFSET + 1U] << 0U));

    *p_payload      = (uint8_t *) &p_llc_snap_packet[PTP_LLC_HEADER_SIZE + PTP_SNAP_HEADER_SIZE];
    *payload_length = (uint16_t) (llc_snap_packet_length - 8U);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Removes IP header from a packet.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 * @param[in]  p_ip_packet               Pointer to an IP packet.
 * @param[in]  ip_packet_length          Length of the packet.
 * @param[out] p_payload                 Pointer to a pointer to store the payload of the packet.
 * @param[out] payload_length            Pointer to store the payload length.
 *
 * @retval     FSP_SUCCESS               The frame was successfully processed.
 * @retval     FSP_ERR_ASSERTION         There was an error parsing the frame.
 **********************************************************************************************************************/
static fsp_err_t r_ptp_process_ipv4_udp_packet (ptp_instance_ctrl_t * p_instance_ctrl,
                                                uint8_t const * const p_ip_packet,
                                                uint16_t              ip_packet_length,
                                                uint8_t ** const      p_payload,
                                                uint16_t * const      payload_length)
{
    ptp_ip_header_t * p_ip_header = (ptp_ip_header_t *) p_ip_packet;
    p_ip_header->total_length        = (uint16_t) __REV16(p_ip_header->total_length);
    p_ip_header->destination_address = __REV(p_ip_header->destination_address);
    uint32_t header_size = p_ip_header->ihl * 4U;

    ptp_udp_header_t * p_udp_header = (ptp_udp_header_t *) (p_ip_packet + header_size);
    p_udp_header->destination_port = (uint16_t) __REV16(p_udp_header->destination_port);
    p_udp_header->source_port      = (uint16_t) __REV16(p_udp_header->source_port);
    p_udp_header->length           = (uint16_t) __REV16(p_udp_header->length);

    /* Verify that the packet is a valid IPv4 + UDP packet. */
    if ((PTP_IP_VERSION != p_ip_header->version) ||
        (p_ip_header->total_length != ip_packet_length) ||
        (PTP_IP_PROTOCOL_UDP != p_ip_header->protocol))
    {
        return FSP_ERR_ASSERTION;
    }

    /* Check to make sure the destination ip address matches the configured ptp message IPv4 address. */
    if ((p_instance_ctrl->p_cfg->synfp.ipv4.primary_ip_addr != p_ip_header->destination_address) &&
        (p_instance_ctrl->p_cfg->synfp.ipv4.pdelay_ip_addr != p_ip_header->destination_address))
    {
        return FSP_ERR_ASSERTION;
    }

    /* Check to make sure the destination port matches the configured ptp message UDP port. */
    if ((p_instance_ctrl->p_cfg->synfp.ipv4.general_udp_port != p_udp_header->destination_port) &&
        (p_instance_ctrl->p_cfg->synfp.ipv4.event_udp_port != p_udp_header->destination_port))
    {
        return FSP_ERR_ASSERTION;
    }

    *p_payload      = (uint8_t *) (p_ip_packet + header_size + PTP_UDP_HEADER_SIZE);
    *payload_length = (uint16_t) (p_udp_header->length - PTP_UDP_HEADER_SIZE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Processes PTP messages and then calls a user callback.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 * @param[in]  p_ptp_packet              Pointer to an IP packet.
 * @param[in]  ptp_packet_length         Length of the packet.
 *
 * @retval     FSP_SUCCESS               The frame was successfully processed.
 **********************************************************************************************************************/
static fsp_err_t r_ptp_process_ptp_packet (ptp_instance_ctrl_t * p_instance_ctrl,
                                           uint8_t const * const p_ptp_packet,
                                           uint16_t              ptp_packet_length)
{
    FSP_PARAMETER_NOT_USED(ptp_packet_length);

    ptp_message_t * p_ptp_message = (ptp_message_t *) p_ptp_packet;

    /* Convert message fields to little endian. */
    r_ptp_message_endian_swap(p_ptp_message);

    uint16_t message_type_size;

    /* Calculate the size of the PTP message excluding TLV data. */
    switch (p_ptp_message->header.message_type)
    {
        case PTP_MESSAGE_TYPE_ANNOUNCE:
        {
            message_type_size = sizeof(ptp_message_header_t) + sizeof(ptp_message_announce_t);
            break;
        }

        case PTP_MESSAGE_TYPE_MANAGEMENT:
        {
            message_type_size = sizeof(ptp_message_header_t) + sizeof(ptp_message_management_t);
            break;
        }

        case PTP_MESSAGE_TYPE_SIGNALING:
        {
            message_type_size = sizeof(ptp_message_header_t) + sizeof(ptp_message_signaling_t);
            break;
        }

        default:
        {
            /* Other PTP messages do not have TLV data. */
            message_type_size = p_ptp_message->header.message_length;
            break;
        }
    }

    /* Calculate the start of TLV data. */
    uint8_t const * p_tlv_data    = NULL;
    uint16_t        tlv_data_size = (uint16_t) (p_ptp_message->header.message_length - message_type_size);

    if (0 < tlv_data_size)
    {
        p_tlv_data = p_ptp_packet + message_type_size;
    }

    ptp_callback_args_t callback_args =
    {
        .event         = PTP_EVENT_MESSAGE_RECEIVED,
        .p_message     = p_ptp_message,
        .p_tlv_data    = p_tlv_data,
        .tlv_data_size = tlv_data_size,
        .p_context     = p_instance_ctrl->p_cfg->p_context
    };

    /* Send the application the processed PTP message. */
    p_instance_ctrl->p_cfg->p_callback(&callback_args);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Processes incoming ethernet packet. Notify the user if the packet contiains a PTP message.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 * @param[in]  p_ether_packet            Pointer to an IP packet.
 * @param[in]  ether_packet_length       Length of the packet.
 *
 * @retval     FSP_SUCCESS               The frame was successfully processed.
 * @retval     FSP_ERR_ASSERTION         There was an error parsing the frame.
 **********************************************************************************************************************/
static fsp_err_t r_ptp_process_ether_packet (ptp_instance_ctrl_t * p_instance_ctrl,
                                             uint8_t const * const p_ether_packet,
                                             uint16_t              ether_packet_length)
{
    fsp_err_t err;

    ptp_ether_header_t * p_ether_header = (ptp_ether_header_t *) p_ether_packet;

    uint16_t ether_type = (uint16_t) __REV16(p_ether_header->ether_type);

    uint16_t ether_header_length =
        (uint16_t) (PTP_ETHER_HEADER_SIZE + p_instance_ctrl->p_cfg->p_edmac_instance->p_cfg->padding);
    uint8_t * p_payload      = (uint8_t *) p_ether_packet + ether_header_length;
    uint16_t  payload_length = (uint16_t) (ether_packet_length - ether_header_length);

    /*
     * If length is less than the max frame length then the ethertype field contains the length of the packet.
     * This means that this frame is an IEEE802.3 packet.
     */
    if (PTP_LLC_MAX_LEN >= ether_type)
    {
        /* Remove the IEEE802.3 + LLC + SNAP headers. */
        err = r_ptp_process_llc_snap_packet(p_payload, payload_length, &ether_type, &p_payload, &payload_length);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (PTP_ETHER_TYPE_IPV4 == ether_type)
    {
        /* Remove the IP + UDP headers. */
        err = r_ptp_process_ipv4_udp_packet(p_instance_ctrl, p_payload, payload_length, &p_payload, &payload_length);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
    else if (PTP_ETHER_TYPE_PTP != ether_type)
    {

        /* Unsupported Ethernet packet type. */
        return FSP_ERR_ASSERTION;
    }
    else
    {
    }

    err = r_ptp_process_ptp_packet(p_instance_ctrl, p_payload, payload_length);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Callback from internal EDMAC module.
 *
 * Notifies the user of all transmitted and received ptp messages using ptp_cfg_t::p_callback.
 *
 * @param[in]  p_args                    Pointer to callback args.
 **********************************************************************************************************************/
void r_ptp_edmac_callback (edmac_callback_args_t * p_args)
{
    ptp_instance_t      * p_ptp_instance   = (ptp_instance_t *) p_args->p_context;
    ptp_instance_ctrl_t * p_instance_ctrl  = (ptp_instance_ctrl_t *) p_ptp_instance->p_ctrl;
    edmac_instance_t    * p_edmac_instance = p_ptp_instance->p_cfg->p_edmac_instance;

    /* Handle frame receive IRQ. */
    if (0 != (p_args->status & R_ETHERC_EDMAC_EESR_FR_Msk))
    {
        edmac_desc_t * p_desc = NULL;

        uint32_t desc_status = 0;
        do
        {
            /* Get the next receive buffer descriptor. */
            fsp_err_t err = R_EDMAC_DescriptorGet(p_edmac_instance->p_ctrl,
                                                  EDMAC_DESC_RECEIVE,
                                                  p_instance_ctrl->rx_buffer_index,
                                                  &p_desc);
            if (FSP_SUCCESS != err)
            {
                FSP_LOG_PRINT("Failed to get receive buffer descriptor.");
            }

            desc_status = p_desc->status.raw_b.active;

            /* Check if the buffer descriptor is active. */
            if (0U == desc_status)
            {
                /* Process the received Ethernet packet and notify the user if it contains a PTP message. */
                err =
                    r_ptp_process_ether_packet(p_instance_ctrl,
                                               p_desc->p_buffer,
                                               (uint16_t) (p_desc->size +
                                                           p_instance_ctrl->p_cfg->p_edmac_instance->p_cfg->padding));
                if (FSP_SUCCESS != err)
                {
                    FSP_LOG_PRINT("Failed to parse packet because the format was invalid.");
                }

                /* Set the buffer descriptor to active so that it receive future Ethernet packets. */
                err = R_EDMAC_DescriptorUpdate(p_edmac_instance->p_ctrl,
                                               EDMAC_DESC_RECEIVE,
                                               p_instance_ctrl->rx_buffer_index,
                                               p_desc->p_buffer,
                                               p_desc->buffer_size);
                if (FSP_SUCCESS != err)
                {
                    FSP_LOG_PRINT("Failed to re-activate the processed packet.");
                }

                /* Move to the next buffer descriptor. */
                p_instance_ctrl->rx_buffer_index++;
                if (p_instance_ctrl->rx_buffer_index == p_edmac_instance->p_cfg->num_rx_desc)
                {
                    p_instance_ctrl->rx_buffer_index = 0;
                }
            }

            /*
             * Continue reading packets until an active descriptor is found. This indicates there are
             * no more inactive buffers to process.
             */
        } while (0 == desc_status);
    }

    /* Handle transmit Complete IRQ. */
    if (0U != (p_args->status & R_ETHERC_EDMAC_EESR_TC_Msk))
    {
        edmac_desc_status_t status;
        uint32_t            tx_buffer_write_index    = p_instance_ctrl->tx_buffer_write_index;
        uint32_t            tx_buffer_complete_index = p_instance_ctrl->tx_buffer_complete_index;
        do
        {
            edmac_desc_t * p_desc;

            /* Get the next transmit buffer descriptor. */
            fsp_err_t err = R_EDMAC_DescriptorGet(p_edmac_instance->p_ctrl,
                                                  EDMAC_DESC_TRANSMIT,
                                                  tx_buffer_complete_index,
                                                  &p_desc);
            if (FSP_SUCCESS != err)
            {
                FSP_LOG_PRINT("Failed to get transmit buffer descriptor.");
            }

            status = p_desc->status;

            /* If the status is no longer active, then the buffer has been transmitted. */
            if (0U == status.raw_b.active)
            {
                ptp_callback_args_t callback_args;
                callback_args.event = PTP_EVENT_MESSAGE_TRANSMIT_COMPLETE;
                p_instance_ctrl->p_cfg->p_callback(&callback_args);
            }

            tx_buffer_complete_index++;
            if (tx_buffer_complete_index == p_edmac_instance->p_cfg->num_tx_desc)
            {
                tx_buffer_complete_index = 0U;
            }
        } while (tx_buffer_complete_index != tx_buffer_write_index && 0U == status.raw_b.active);

        p_instance_ctrl->tx_buffer_complete_index = tx_buffer_complete_index;
    }
}

/*******************************************************************************************************************//**
 * PTP MINT interrupt handler
 *
 * Notifies the user of all ptp events using ptp_cfg_t::p_callback.
 **********************************************************************************************************************/
void r_ptp_mint_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq             = R_FSP_CurrentIrqGet();
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    ptp_callback_args_t callback_args =
    {
        .p_message = NULL
    };

    /* ETHER_MINT Interrupt Source Status Register. */
    uint32_t miesr = R_ETHERC_EPTPC_COMMON->MIESR;

    /* STCA Status Register. */
    uint32_t stsr = R_ETHERC_EPTPC_COMMON->STSR;

    /* SYNFP Status Register. */
    uint32_t sysr = R_ETHERC_EPTPC->SYSR;

    /* Notify user of STCA events. */
    uint32_t stsr_tmp = stsr;
    while (stsr_tmp)
    {
        /* Get the offset of the next status bit that is set to one. */
        uint32_t event = 31U - __CLZ(stsr_tmp);

        /* Convert the status offset to its corresponding enum value. */
        callback_args.event = (ptp_event_t) (event + PTP_EVENT_SYNC_ACQUIRED);

        /* Notify the application of the event. */
        p_instance_ctrl->p_cfg->p_callback(&callback_args);

        /* Clear the status bit so the next event can be processed. */
        stsr_tmp &= ~(1U << event);
    }

    /* Notify user of SYNFP events. */
    uint32_t sysr_tmp = sysr;
    while (sysr_tmp)
    {
        /* Get the offset of the next status bit that is set to one. */
        uint32_t event = 31U - __CLZ(sysr_tmp);

        /* Convert the status offset to its corresponding enum value. */
        callback_args.event = (ptp_event_t) event;

        /* Notify the application of the event. */
        p_instance_ctrl->p_cfg->p_callback(&callback_args);

        /* Clear the status bit so the next event can be processed. */
        sysr_tmp &= ~(1U << event);
    }

    /* Notify user of Pulse Timer rising edge events. */
    uint32_t miesr_tmp = miesr >> R_ETHERC_EPTPC_COMMON_MIESR_CYC0_Pos;
    while (miesr_tmp)
    {
        /* Get the offset of the next status bit that is set to one. */
        uint32_t event = 31U - __CLZ(miesr_tmp);

        /* Convert the status offset to its corresponding enum value. */
        callback_args.pulse_timer_channel = event;
        callback_args.event               = PTP_EVENT_PULSE_TIMER_MINT_RISING_EDGE;

        /* Notify the application of the event. */
        p_instance_ctrl->p_cfg->p_callback(&callback_args);

        /* Clear the status bit so the next event can be processed. */
        miesr_tmp &= ~(1U << event);
    }

    /* Handle STCA events. */

    if ((stsr & R_ETHERC_EPTPC_COMMON_STSR_W10D_Msk) != 0)
    {
        /* Issue a directive to capture information. */
        R_ETHERC_EPTPC_COMMON->GETINFOR = 1U;

        /* Waiting for information capturing to complete
         * (See figure 30.25 of the RA6M3 manual R01UH0886EJ0100). */
        FSP_HARDWARE_REGISTER_WAIT(R_ETHERC_EPTPC_COMMON->GETINFOR, 0U);

        /** Disable IRQs because PW10VRn, and MW10Rn registers must be set in consecutive operations
         * (See section 30.2.20 in the RA6M3 manual R01UH0886EJ0100). */
        __disable_irq();

        /* Read the gradient worst 10 values. */
        uint32_t pw10vru = R_ETHERC_EPTPC_COMMON->PW10VRU;
        uint32_t pw10vrm = R_ETHERC_EPTPC_COMMON->PW10VRM;
        uint32_t pw10vrl = R_ETHERC_EPTPC_COMMON->PW10VRL;
        uint32_t mw10ru  = R_ETHERC_EPTPC_COMMON->MW10RU;
        uint32_t mw10rm  = R_ETHERC_EPTPC_COMMON->MW10RM;
        uint32_t mw10rl  = R_ETHERC_EPTPC_COMMON->MW10RL;

        /* Write the gradient worst 10 values to the gradient limit registers. */
        R_ETHERC_EPTPC_COMMON->PLIMITRU = pw10vru & R_ETHERC_EPTPC_COMMON_PLIMITRU_PLIMITRU_Msk;
        R_ETHERC_EPTPC_COMMON->PLIMITRM = pw10vrm;
        R_ETHERC_EPTPC_COMMON->PLIMITRL = pw10vrl;
        R_ETHERC_EPTPC_COMMON->MLIMITRU = mw10ru & R_ETHERC_EPTPC_COMMON_MLIMITRU_MLIMITRU_Msk;
        R_ETHERC_EPTPC_COMMON->MLIMITRM = mw10rm;
        R_ETHERC_EPTPC_COMMON->MLIMITRL = mw10rl;

        __enable_irq();
    }

    /* Handle SYNFP events. */

    if ((sysr & R_ETHERC_EPTPC_SYSR_OFMUD_Msk) != 0)
    {
        /* offsetFromMaster value updated. */
        if (0U == R_ETHERC_EPTPC_COMMON->SYNSTARTR)
        {
            /* Clear SYNTOUT and SYNCOUT flags immediately after starting synchronization
             * (See 30.2.5 of the RA6M3 manual R01UH0886EJ0100). */
            stsr |= R_ETHERC_EPTPC_COMMON_STSR_SYNTOUT_Msk | R_ETHERC_EPTPC_COMMON_STSR_SYNCOUT_Msk;

            /* Start syncronization. */
            R_ETHERC_EPTPC_COMMON->SYNSTARTR = 1U;

            if (PTP_CLOCK_CORRECTION_MODE2 == p_instance_ctrl->p_cfg->stca.clock_correction_mode)
            {
                /* Start acquiring gradient worst 10 values. */
                R_ETHERC_EPTPC_COMMON->GETW10R = 1U;
            }
        }
    }

    if ((sysr & R_ETHERC_EPTPC_SYSR_INTCHG_Msk) != 0)
    {
        /* Receive LogMessageInterval value changed. */

        /* Read the SYNFP Received Log Interval register. */
        uint32_t syrlir = R_ETHERC_EPTPC->SYRLIR;

        /* Get the delay_resp log interval. */
        int8_t sync_log_int = (int8_t) ((syrlir & R_ETHERC_EPTPC_SYRLIR_SYNC_Msk) >> R_ETHERC_EPTPC_SYRLIR_SYNC_Pos);

        /* Recalculate Sync message timeout based on the new Sync message interval. */
        R_ETHERC_EPTPC_COMMON->SYNTOR = r_ptp_calculate_timeout(p_instance_ctrl, sync_log_int);
        R_ETHERC_EPTPC->SYRVLDR       = R_ETHERC_EPTPC_SYRVLDR_STUP_Msk;
    }

    /* Clear interrupt status flags. */

    R_ETHERC_EPTPC_COMMON->MIESR = miesr;
    R_ETHERC_EPTPC_COMMON->STSR  = stsr;
    R_ETHERC_EPTPC->SYSR         = sysr;

    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * PTP IPLS interrupt handler
 *
 * Notifies the user of all ptp pulse timer events using ptp_cfg_t::p_pulse_timer_callback.
 **********************************************************************************************************************/
void r_ptp_ipls_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq             = R_FSP_CurrentIrqGet();
    ptp_instance_ctrl_t * p_instance_ctrl = (ptp_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    R_BSP_IrqStatusClear(irq);

    ptp_callback_args_t callback_args =
    {
        .p_message = NULL
    };

    callback_args.event = PTP_EVENT_PULSE_TIMER_IPLS_COMMON;

    /* Notify the application of the event. */
    p_instance_ctrl->p_cfg->p_callback(&callback_args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
