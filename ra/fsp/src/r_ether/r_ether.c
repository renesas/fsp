/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include <string.h>
#include "r_ether.h"
#include "r_ether_phy.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#ifndef ETHER_ERROR_RETURN

 #define ETHER_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

#define ETHER_ETHERC_REG_SIZE                           (0x400UL)
#define ETHER_ETHERC_EDMAC_REG_SIZE                     (0x100UL)

#define ETHER_ETHERC_INITIALIZATION_WAIT_CYCLE          (0x64UL)

/** "ETHE" in ASCII.  Used to determine if the control block is open. */
#define ETHER_OPEN                                      (0x45544845U)

/* Definition of the maximum / minimum number of data that can be sent at one time in the Ethernet */
#define ETHER_MAXIMUM_FRAME_SIZE                        (1514U) /* Maximum number of transmitted data */
#define ETHER_MINIMUM_FRAME_SIZE                        (60U)   /* Minimum number of transmitted data */

/* Definition of the maximum padding offset */
#define ETHER_MAXIMUM_PADDING_OFFSET                    (63U)

/* Bit definition of Ethernet interrupt factor*/
#define ETHER_ETHERC_INTERRUPT_FACTOR_ALL               (0x00000037UL)

#define ETHER_ETHERC_INTERRUPT_FACTOR_LCHNG             (1UL << 2)
#define ETHER_ETHERC_INTERRUPT_FACTOR_MPD               (1UL << 1)

#define ETHER_EDMAC_INTERRUPT_FACTOR_ALL                (0x47FF0F9FUL)

#define ETHER_EDMAC_INTERRUPT_FACTOR_RFCOF              (1UL << 24)
#define ETHER_EDMAC_INTERRUPT_FACTOR_ECI                (1UL << 22)
#define ETHER_EDMAC_INTERRUPT_FACTOR_TC                 (1UL << 21)
#define ETHER_EDMAC_INTERRUPT_FACTOR_FR                 (1UL << 18)
#define ETHER_EDMAC_INTERRUPT_FACTOR_RDE                (1UL << 17)
#define ETHER_EDMAC_INTERRUPT_FACTOR_RFOF               (1UL << 16)

/* Bit definition of Ethernet interrupt enable */
#define ETHER_ETHERC_INTERRUPT_ENABLE_LCHNG             (1UL << 2)
#define ETHER_ETHERC_INTERRUPT_ENABLE_MPD               (1UL << 1)

/* Bit definitions of status member of DescriptorS */

#define ETHER_TD0_TACT                                  (0x80000000UL)
#define ETHER_TD0_TDLE                                  (0x40000000UL)
#define ETHER_TD0_TFP1                                  (0x20000000UL)
#define ETHER_TD0_TFP0                                  (0x10000000UL)
#define ETHER_TD0_TFE                                   (0x08000000UL)

#define ETHER_TD0_TWBI                                  (0x04000000UL)
#define ETHER_TD0_TFS8_TAD                              (0x00000100UL)
#define ETHER_TD0_TFS3_CND                              (0x00000008UL)
#define ETHER_TD0_TFS2_DLC                              (0x00000004UL)
#define ETHER_TD0_TFS1_CD                               (0x00000002UL)
#define ETHER_TD0_TFS0_TRO                              (0x00000001UL)

#define ETHER_RD0_RACT                                  (0x80000000UL)
#define ETHER_RD0_RDLE                                  (0x40000000UL)
#define ETHER_RD0_RFP1                                  (0x20000000UL)
#define ETHER_RD0_RFP0                                  (0x10000000UL)
#define ETHER_RD0_RFE                                   (0x08000000UL)

#define ETHER_RD0_RFS9_RFOVER                           (0x00000200UL)
#define ETHER_RD0_RFS8_RAD                              (0x00000100UL)
#define ETHER_RD0_RFS7_RMAF                             (0x00000080UL)
#define ETHER_RD0_RFS4_RRF                              (0x00000010UL)
#define ETHER_RD0_RFS3_RTLF                             (0x00000008UL)
#define ETHER_RD0_RFS2_RTSF                             (0x00000004UL)
#define ETHER_RD0_RFS1_PRE                              (0x00000002UL)
#define ETHER_RD0_RFS0_CERF                             (0x00000001UL)

/* Macro definitions of ETHERC/EDMAC configurations */
#define ETHER_ETHERC_ECMR_MODE_CLEAR                    (0x00000000UL)
#define ETHER_ETHERC_RFLR_DEFAULT_VALUE                 (1518U)
#define ETHER_ETHERC_IPGR_DEFAULT_VALUE                 (0x00000014UL)
#define ETHER_ETHERC_APR_MAXIMUM_VALUE                  (0x0000FFFFUL)
#define ETHER_ETHERC_FCFTR_MINIMUM_VALUE                (0x00000000UL)

#define ETHER_EDMAC_TRSCER_MULTICAST_DISABLE            (0x00000000UL)
#define ETHER_EDMAC_TRSCER_MULTICAST_ENABLE             (0x00000080UL)
#define ETHER_EDMAC_RMCR_MULTIPLE_FRAMES_ENABLE         (0x00000001UL)
#define ETHER_EDMAC_TFTR_STORE_AND_FORWARD_MODE         (0x00000000UL)

/* Macro definitions of EDMAC requests */
#define ETHER_EDMAC_EDRRR_RECEIVE_REQUEST               (0x00000001UL)
#define ETHER_EDMAC_EDTRR_TRANSMIT_REQUEST              (0x00000001UL)

/* Number of entries in PAUSE resolution table */
#define ETHER_PAUSE_TABLE_ENTRIES                       (8)

/* Local device and link partner PAUSE settings */
#define ETHER_PAUSE_XMIT_OFF                            (0)      /* The pause frame transmission is prohibited. */
#define ETHER_PAUSE_RECV_OFF                            (0)      /* The pause frame reception is prohibited.    */
#define ETHER_PAUSE_XMIT_ON                             (1)      /* The pause frame transmission is permitted.  */
#define ETHER_PAUSE_RECV_ON                             (1)      /* The pause frame reception is permitted.     */

/* Macro definition for buffer alignment adjustment */
#define ETHER_BUFFER_32BYTE_ALIGNMENT_MASK              (0x1FUL) /* Mask for checking whether or not 32-bit alignment. */

/* PAUSE link mask and shift values */

/*
 * The mask value and shift value which are for that shift the bits form a line and
 * for comparing the bit information of PAUSE function which support the local device and
 * Link partner with the assorted table(pause_resolution) which enable or disable the PAUSE frame.
 */
#define ETHER_LINK_RESOLUTION_ABILITY_MASK              (3)
#define ETHER_LINK_RESOLUTION_LOCAL_ABILITY_BITSHIFT    (2)

/* Etherc mode */
#define ETHER_NO_USE_MAGIC_PACKET_DETECT                (0)
#define ETHER_USE_MAGIC_PACKET_DETECT                   (1)

/* ETHER_NO_DATA is the return value that indicates that no received data. */
#define ETHER_NO_DATA                                   (0)

/* PAUSE link mask and shift values */

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
void ether_eint_isr(void);

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t ether_open_param_check(ether_instance_ctrl_t const * const p_instance_ctrl,
                                        ether_cfg_t const * const           p_cfg);

#endif

static void      ether_enable_icu(ether_instance_ctrl_t * const p_instance_ctrl);
static void      ether_disable_icu(ether_instance_ctrl_t * const p_instance_ctrl);
static void      ether_reset_mac(R_ETHERC_EDMAC_Type * const p_reg);
static void      ether_init_descriptors(ether_instance_ctrl_t * const p_instance_ctrl);
static void      ether_init_buffers(ether_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ether_buffer_get(ether_instance_ctrl_t * const p_instance_ctrl,
                                  void ** const                 p_buffer,
                                  uint32_t                    * p_buffer_size);
static void ether_config_ethernet(ether_instance_ctrl_t const * const p_instance_ctrl, const uint8_t mode);
static void ether_pause_resolution(uint32_t const local_ability,
                                   uint32_t const partner_ability,
                                   uint32_t     * ptx_pause,
                                   uint32_t     * prx_pause);
static void ether_configure_mac(ether_instance_ctrl_t * const p_instance_ctrl,
                                const uint8_t                 mac_addr[],
                                const uint8_t                 mode);
static fsp_err_t ether_do_link(ether_instance_ctrl_t * const p_instance_ctrl, const uint8_t mode);
static fsp_err_t ether_link_status_check(ether_instance_ctrl_t const * const p_instance_ctrl);
static uint8_t   ether_check_magic_packet_detection_bit(ether_instance_ctrl_t const * const p_instance_ctrl);
static void      ether_configure_padding(ether_instance_ctrl_t * const p_instance_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "ether";
#endif

#if defined(__GNUC__)

/* This structure is affected by warnings from a GCC compiler bug. This pragma suppresses the warnings in this
 * structure only.*/

 #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

/** ETHER HAL API mapping for Ethernet Controller interface. */
const ether_api_t g_ether_on_ether =
{
    .open            = R_ETHER_Open,
    .close           = R_ETHER_Close,
    .read            = R_ETHER_Read,
    .bufferRelease   = R_ETHER_BufferRelease,
    .rxBufferUpdate  = R_ETHER_RxBufferUpdate,
    .write           = R_ETHER_Write,
    .linkProcess     = R_ETHER_LinkProcess,
    .wakeOnLANEnable = R_ETHER_WakeOnLANEnable,
    .txStatusGet     = R_ETHER_TxStatusGet,
};

/*
 * PAUSE Resolution as documented in IEEE 802.3-2008_section2 Annex
 * 28B, Table 28B-3. The following table codify logic that
 * determines how the PAUSE is configured for local transmitter
 * and receiver and partner transmitter and receiver.
 */
static const ether_pause_resolution_t pause_resolution[ETHER_PAUSE_TABLE_ENTRIES] =
{
    {ETHER_PAUSE_MASKC, ETHER_PAUSE_VAL0, ETHER_PAUSE_XMIT_OFF, ETHER_PAUSE_RECV_OFF  },
    {ETHER_PAUSE_MASKE, ETHER_PAUSE_VAL4, ETHER_PAUSE_XMIT_OFF, ETHER_PAUSE_RECV_OFF  },
    {ETHER_PAUSE_MASKF, ETHER_PAUSE_VAL6, ETHER_PAUSE_XMIT_OFF, ETHER_PAUSE_RECV_OFF  },
    {ETHER_PAUSE_MASKF, ETHER_PAUSE_VAL7, ETHER_PAUSE_XMIT_ON,  ETHER_PAUSE_RECV_OFF  },
    {ETHER_PAUSE_MASKE, ETHER_PAUSE_VAL8, ETHER_PAUSE_XMIT_OFF, ETHER_PAUSE_RECV_OFF  },
    {ETHER_PAUSE_MASKA, ETHER_PAUSE_VALA, ETHER_PAUSE_XMIT_ON,  ETHER_PAUSE_RECV_ON   },
    {ETHER_PAUSE_MASKF, ETHER_PAUSE_VALC, ETHER_PAUSE_XMIT_OFF, ETHER_PAUSE_RECV_OFF  },
    {ETHER_PAUSE_MASKF, ETHER_PAUSE_VALD, ETHER_PAUSE_XMIT_OFF, ETHER_PAUSE_RECV_ON   }
};

/*******************************************************************************************************************//**
 * @addtogroup ETHER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * @brief After ETHERC, EDMAC and PHY-LSI are reset in software, an auto negotiation of PHY-LSI is begun.
 * Afterwards, the link signal change interrupt is permitted. Implements @ref ether_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to ETHER control block or configuration structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN                    Control block has already been opened or channel is being used by another
 *                                                  instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION   Initialization of PHY-LSI failed.
 * @retval  FSP_ERR_INVALID_CHANNEL                 Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_POINTER                 Pointer to MAC address is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                Interrupt is not enabled.
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK            Initialization of PHY-LSI failed.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_Open (ether_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    R_ETHERC0_Type        * p_reg_etherc;
    R_ETHERC_EDMAC_Type   * p_reg_edmac;

    fsp_err_t phy_ret;

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)

    /** Check parameters. */
    err = ether_open_param_check(p_instance_ctrl, p_cfg); /** check arguments */
    ETHER_ERROR_RETURN((FSP_SUCCESS == err), err);
#endif

    /** Make sure this channel exists. */
    p_instance_ctrl->p_reg_etherc = ((R_ETHERC0_Type *) (R_ETHERC0_BASE + (ETHER_ETHERC_REG_SIZE * p_cfg->channel)));
    p_instance_ctrl->p_reg_edmac  =
        ((R_ETHERC_EDMAC_Type *) (R_ETHERC_EDMAC_BASE + (ETHER_ETHERC_EDMAC_REG_SIZE * p_cfg->channel)));

    p_reg_etherc = p_instance_ctrl->p_reg_etherc;
    p_reg_edmac  = p_instance_ctrl->p_reg_edmac;

    /* Initialize configuration of Ethernet module. */
    p_instance_ctrl->p_ether_cfg = p_cfg;

    /* Initialize the flags */
    p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
    p_instance_ctrl->magic_packet          = ETHER_MAGIC_PACKET_NOT_DETECTED;
    p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_NO_CHANGE;
    p_instance_ctrl->previous_link_status  = ETHER_PREVIOUS_LINK_STATUS_DOWN;

    /* Initialize the transmit and receive descriptor */
    memset(p_instance_ctrl->p_ether_cfg->p_rx_descriptors,
           0x00,
           sizeof(ether_instance_descriptor_t) *
           p_instance_ctrl->p_ether_cfg->num_rx_descriptors);
    memset(p_instance_ctrl->p_ether_cfg->p_tx_descriptors,
           0x00,
           sizeof(ether_instance_descriptor_t) *
           p_instance_ctrl->p_ether_cfg->num_tx_descriptors);

    /* Initialize the Ethernet buffer */
    ether_init_buffers(p_instance_ctrl);

    R_BSP_MODULE_START(FSP_IP_ETHER, p_instance_ctrl->p_ether_cfg->channel);

    /* Software reset */
    ether_reset_mac(p_instance_ctrl->p_reg_edmac);

    /* Setting the padding function */
    ether_configure_padding(p_instance_ctrl);

    /* Software reset the PHY */
    phy_ret = p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_api->open(
        p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_ctrl,
        p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_cfg);

    if (FSP_SUCCESS == phy_ret)
    {
        p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_api->startAutoNegotiate(
            p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_ctrl);

        /* Clear all ETHERC status BFR, PSRTO, LCHNG, MPD, ICD */
        p_reg_etherc->ECSR = ETHER_ETHERC_INTERRUPT_FACTOR_ALL;

        /* Clear all EDMAC status bits */
        p_reg_edmac->EESR = ETHER_EDMAC_INTERRUPT_FACTOR_ALL;

#if (ETHER_CFG_USE_LINKSTA == 1)

        /* Enable interrupts of interest only. */
        p_reg_etherc->ECSIPR_b.LCHNGIP = 1;
#endif

        p_reg_edmac->EESIPR_b.ECIIP = 1;

        /* Set Ethernet interrupt level and enable */
        ether_enable_icu(p_instance_ctrl);

        p_instance_ctrl->open = ETHER_OPEN;

        err = FSP_SUCCESS;
    }
    else
    {
        if (FSP_ERR_ETHER_PHY_ERROR_LINK == phy_ret)
        {
            err = FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION;
        }
        else
        {
            err = phy_ret;
        }
    }

    return err;
}                                      /* End of function R_ETHER_Open() */

/********************************************************************************************************************//**
 * @brief Disables interrupts. Removes power and releases hardware lock. Implements @ref ether_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_Close (ether_ctrl_t * const p_ctrl)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    R_ETHERC0_Type        * p_reg_etherc;
    R_ETHERC_EDMAC_Type   * p_reg_edmac;

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;
    p_reg_edmac  = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

    /* Disable Ethernet interrupt. */
    ether_disable_icu(p_instance_ctrl);

    p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_api->close(
        p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_ctrl);

    p_reg_etherc->ECSIPR_b.LCHNGIP = 0;
    p_reg_edmac->EESIPR_b.ECIIP    = 0;

    /* Disable TE and RE  */
    p_reg_etherc->ECMR = ETHER_ETHERC_ECMR_MODE_CLEAR;

    /* Initialize the flags */
    p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
    p_instance_ctrl->magic_packet          = ETHER_MAGIC_PACKET_NOT_DETECTED;
    p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_NO_CHANGE;
#if (ETHER_CFG_USE_LINKSTA == 0)
    p_instance_ctrl->previous_link_status = ETHER_PREVIOUS_LINK_STATUS_DOWN;
#endif

    /** Remove power to the channel. */
    R_BSP_MODULE_STOP(FSP_IP_ETHER, p_instance_ctrl->p_ether_cfg->channel);

    /** Clear configure block parameters. */
    p_instance_ctrl->p_ether_cfg = NULL;

    /** Mark the channel not open so other APIs cannot use it. */
    p_instance_ctrl->open = 0U;

    return err;
}                                      /* End of function R_ETHER_Close() */

/********************************************************************************************************************//**
 * @brief Move to the next buffer in the circular receive buffer list. Implements @ref ether_api_t::bufferRelease.
 *
 * @retval  FSP_SUCCESS                             Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                        The control block has not been opened
 * @retval  FSP_ERR_ETHER_ERROR_LINK                Auto-negotiation is not completed, and reception is not enabled.
 * @retval  FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE   As a Magic Packet is being detected, transmission and reception is
 *                                                  not enabled.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_BufferRelease (ether_ctrl_t * const p_ctrl)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    R_ETHERC_EDMAC_Type   * p_reg_edmac;

    uint32_t status;

    /* Check argument */
#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* When the Link up processing is not completed, return error */
    ETHER_ERROR_RETURN(ETHER_LINK_ESTABLISH_STATUS_UP == p_instance_ctrl->link_establish_status,
                       FSP_ERR_ETHER_ERROR_LINK);

    /* In case of detection mode of magic packet, return error. */
    ETHER_ERROR_RETURN(0 == ether_check_magic_packet_detection_bit(p_instance_ctrl),
                       FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE);

    /* When receive data exists */
    if (ETHER_RD0_RACT != (p_instance_ctrl->p_rx_descriptor->status & ETHER_RD0_RACT))
    {
        /* Reset current descriptor */
        status  = ETHER_RD0_RFP1;
        status |= ETHER_RD0_RFP0;
        status |= ETHER_RD0_RFE;
        status |= ETHER_RD0_RFS9_RFOVER;
        status |= ETHER_RD0_RFS8_RAD;
        status |= ETHER_RD0_RFS7_RMAF;
        status |= ETHER_RD0_RFS4_RRF;
        status |= ETHER_RD0_RFS3_RTLF;
        status |= ETHER_RD0_RFS2_RTSF;
        status |= ETHER_RD0_RFS1_PRE;
        status |= ETHER_RD0_RFS0_CERF;

        p_instance_ctrl->p_rx_descriptor->status &= (~status);

        /* Enable current descriptor */
        p_instance_ctrl->p_rx_descriptor->status |= ETHER_RD0_RACT;

        /* Move to next descriptor */
        p_instance_ctrl->p_rx_descriptor = p_instance_ctrl->p_rx_descriptor->p_next;
    }

    p_reg_edmac = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

    if (ETHER_EDMAC_EDRRR_RECEIVE_REQUEST != p_reg_edmac->EDRRR)
    {
        /* Restart if stopped */
        p_reg_edmac->EDRRR = ETHER_EDMAC_EDRRR_RECEIVE_REQUEST;
    }

    err = FSP_SUCCESS;

    return err;
}                                      /* End of function R_ETHER_BufferRelease() */

/********************************************************************************************************************//**
 * @brief Change the buffer pointer of the current rx buffer descriptor. Implements @ref ether_api_t::rxBufferUpdate.
 *
 * @retval  FSP_SUCCESS                             Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION                       A pointer argument is NULL.
 * @retval  FSP_ERR_NOT_OPEN                        The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER                 The pointer of buffer is NULL or not aligned on a 32-bit boundary.
 * @retval  FSP_ERR_INVALID_MODE                    Driver is configured to non zero copy mode.
 * @retval  FSP_ERR_ETHER_RECEIVE_BUFFER_ACTIVE     All descriptor is active.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_RxBufferUpdate (ether_ctrl_t * const p_ctrl, void * const p_buffer)
{
    fsp_err_t               err = FSP_SUCCESS;
    R_ETHERC_EDMAC_Type   * p_reg_edmac;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    uint32_t                status;

    /* Check argument */
#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHER_ERROR_RETURN(NULL != p_buffer, FSP_ERR_INVALID_POINTER);
    ETHER_ERROR_RETURN(0 == ((uint32_t) p_buffer & (uint32_t) ETHER_BUFFER_32BYTE_ALIGNMENT_MASK),
                       FSP_ERR_INVALID_POINTER);
    ETHER_ERROR_RETURN(ETHER_ZEROCOPY_ENABLE == p_instance_ctrl->p_ether_cfg->zerocopy, FSP_ERR_INVALID_MODE);
#endif

    if (ETHER_RD0_RACT != (p_instance_ctrl->p_rx_descriptor->status & ETHER_RD0_RACT))
    {
        p_instance_ctrl->p_rx_descriptor->p_buffer = p_buffer;

        /* Reset current descriptor */
        status  = ETHER_RD0_RFP1;
        status |= ETHER_RD0_RFP0;
        status |= ETHER_RD0_RFE;
        status |= ETHER_RD0_RFS9_RFOVER;
        status |= ETHER_RD0_RFS8_RAD;
        status |= ETHER_RD0_RFS7_RMAF;
        status |= ETHER_RD0_RFS4_RRF;
        status |= ETHER_RD0_RFS3_RTLF;
        status |= ETHER_RD0_RFS2_RTSF;
        status |= ETHER_RD0_RFS1_PRE;
        status |= ETHER_RD0_RFS0_CERF;

        p_instance_ctrl->p_rx_descriptor->status &= (~status);

        /* Enable current descriptor */
        p_instance_ctrl->p_rx_descriptor->status |= ETHER_RD0_RACT;

        /* Move to next descriptor */
        p_instance_ctrl->p_rx_descriptor = p_instance_ctrl->p_rx_descriptor->p_next;

        p_reg_edmac = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

        if (ETHER_EDMAC_EDRRR_RECEIVE_REQUEST != p_reg_edmac->EDRRR)
        {
            /* Restart if stopped */
            p_reg_edmac->EDRRR = ETHER_EDMAC_EDRRR_RECEIVE_REQUEST;
        }
    }
    else
    {
        err = FSP_ERR_ETHER_RECEIVE_BUFFER_ACTIVE;
    }

    return err;
}

/********************************************************************************************************************//**
 * @brief The Link up processing, the Link down processing, and the magic packet detection processing are executed.
 *  Implements @ref ether_api_t::linkProcess.
 *
 * @retval  FSP_SUCCESS                                 Link is up.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_ETHER_ERROR_LINK                    Link is down.
 * @retval  FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION       When reopening the PHY interface initialization of the PHY-LSI failed.
 * @retval  FSP_ERR_ALREADY_OPEN                        When reopening the PHY interface it was already opened.
 * @retval  FSP_ERR_INVALID_CHANNEL                     When reopening the PHY interface an invalid channel was passed.
 * @retval  FSP_ERR_INVALID_POINTER                     When reopening the PHY interface the MAC address pointer was NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    When reopening the PHY interface the interrupt was not enabled.
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                Initialization of the PHY-LSI failed.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_LinkProcess (ether_ctrl_t * const p_ctrl)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    R_ETHERC0_Type        * p_reg_etherc;

    ether_callback_args_t                 callback_arg;
    ether_cfg_t const                   * p_ether_cfg;
    volatile ether_previous_link_status_t previous_link_status;

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* When the magic packet is detected. */
    if (ETHER_MAGIC_PACKET_DETECTED == p_instance_ctrl->magic_packet)
    {
        p_instance_ctrl->magic_packet = ETHER_MAGIC_PACKET_NOT_DETECTED;

        if (NULL != p_instance_ctrl->p_ether_cfg->p_callback)
        {
            callback_arg.channel = p_instance_ctrl->p_ether_cfg->channel;
            callback_arg.event   = ETHER_EVENT_WAKEON_LAN;
            (*p_instance_ctrl->p_ether_cfg->p_callback)((void *) &callback_arg);
        }

        /*
         * After the close function is called, the open function is called
         * to have to set ETHERC to a usual operational mode
         * to usually communicate after magic packet is detected.
         *//* back up previous_link_status */
        previous_link_status = p_instance_ctrl->previous_link_status;

        p_ether_cfg = p_instance_ctrl->p_ether_cfg;

        err = R_ETHER_Close((ether_ctrl_t *) p_instance_ctrl);
        ETHER_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = R_ETHER_Open((ether_ctrl_t *) p_instance_ctrl, (ether_cfg_t *) p_ether_cfg);
        ETHER_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* restore previous_link_status */
        p_instance_ctrl->previous_link_status = previous_link_status;
    }

#if (ETHER_CFG_USE_LINKSTA == 0)
    err = ether_link_status_check(p_instance_ctrl);

    /* The state of the link status in PHY-LSI is confirmed and Link Up/Down is judged. */
    if (FSP_SUCCESS == err)
    {
        /* When becoming Link up */
        if (ETHER_PREVIOUS_LINK_STATUS_DOWN == p_instance_ctrl->previous_link_status)
        {
            p_instance_ctrl->link_change = ETHER_LINK_CHANGE_LINK_UP;

            /* Update Link status */
            p_instance_ctrl->previous_link_status = ETHER_PREVIOUS_LINK_STATUS_UP;
        }
    }
    else
    {
        /* When becoming Link down */
        if (ETHER_PREVIOUS_LINK_STATUS_UP == p_instance_ctrl->previous_link_status)
        {
            p_instance_ctrl->link_change = ETHER_LINK_CHANGE_LINK_DOWN;

            /* Update Link status */
            p_instance_ctrl->previous_link_status = ETHER_PREVIOUS_LINK_STATUS_DOWN;
        }
    }
#endif

    /* When the link is up */
    if (ETHER_LINK_CHANGE_LINK_UP == p_instance_ctrl->link_change)
    {
#if (ETHER_CFG_USE_LINKSTA == 1)

        /*
         * The Link Up/Down is confirmed by the Link Status bit of PHY register1,
         * because the LINK signal of PHY-LSI is used for LED indicator, and
         * isn't used for notifing the Link Up/Down to external device.
         */
        err = ether_link_status_check(p_instance_ctrl);

        if (FSP_SUCCESS == err)
        {
            /*
             * The status of the LINK signal became "link-up" even if PHY-LSI did not detect "link-up"
             * after a reset. To avoid this wrong detection, processing in R_ETHER_LinkProcess has been modified to
             * clear the flag after link-up is confirmed in R_ETHER_CheckLink_ZC.
             */
            p_instance_ctrl->link_change = ETHER_LINK_CHANGE_LINK_DOWN;

            /* Initialize the transmit and receive descriptor */
            memset(p_instance_ctrl->p_ether_cfg->p_rx_descriptors,
                   0x00,
                   sizeof(ether_instance_descriptor_t) * p_instance_ctrl->p_ether_cfg->num_rx_descriptors);
            memset(p_instance_ctrl->p_ether_cfg->p_tx_descriptors,
                   0x00,
                   sizeof(ether_instance_descriptor_t) * p_instance_ctrl->p_ether_cfg->num_tx_descriptors);

            /* Initialize the Ethernet buffer */
            ether_init_buffers(p_instance_ctrl);

            p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_UP;

            /*
             * ETHERC and EDMAC are set after ETHERC and EDMAC are reset in software
             * and sending and receiving is permitted.
             */
            ether_configure_mac(p_instance_ctrl,
                                p_instance_ctrl->p_ether_cfg->p_mac_address,
                                ETHER_NO_USE_MAGIC_PACKET_DETECT);
            err = ether_do_link(p_instance_ctrl, ETHER_NO_USE_MAGIC_PACKET_DETECT);

            if (FSP_SUCCESS == err)
            {
                if (NULL != p_instance_ctrl->p_ether_cfg->p_callback)
                {
                    callback_arg.channel = p_instance_ctrl->p_ether_cfg->channel;
                    callback_arg.event   = ETHER_EVENT_LINK_ON;
                    (*p_instance_ctrl->p_ether_cfg->p_callback)((void *) &callback_arg);
                }
            }
            else
            {
                /* When PHY auto-negotiation is not completed */
                p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
                p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_LINK_UP;
            }
        }
        else
        {
            /* no process */
        }

#elif (ETHER_CFG_USE_LINKSTA == 0)

        /*
         * The status of the LINK signal became "link-up" even if PHY-LSI did not detect "link-up"
         * after a reset. To avoid this wrong detection, processing in R_ETHER_LinkProcess has been modified to
         * clear the flag after link-up is confirmed in R_ETHER_CheckLink_ZC.
         */
        p_instance_ctrl->link_change = ETHER_LINK_CHANGE_NO_CHANGE;

        /* Initialize the transmit and receive descriptor */
        memset(p_instance_ctrl->p_ether_cfg->p_rx_descriptors,
               0x00,
               sizeof(ether_instance_descriptor_t) * p_instance_ctrl->p_ether_cfg->num_rx_descriptors);
        memset(p_instance_ctrl->p_ether_cfg->p_tx_descriptors,
               0x00,
               sizeof(ether_instance_descriptor_t) * p_instance_ctrl->p_ether_cfg->num_tx_descriptors);

        /* Initialize the Ethernet buffer */
        ether_init_buffers(p_instance_ctrl);

        p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_UP;

        /*
         * ETHERC and EDMAC are set after ETHERC and EDMAC are reset in software
         * and sending and receiving is permitted.
         */
        ether_configure_mac(p_instance_ctrl,
                            p_instance_ctrl->p_ether_cfg->p_mac_address,
                            ETHER_NO_USE_MAGIC_PACKET_DETECT);
        err = ether_do_link(p_instance_ctrl, ETHER_NO_USE_MAGIC_PACKET_DETECT);

        if (FSP_SUCCESS == err)
        {
            if (NULL != p_instance_ctrl->p_ether_cfg->p_callback)
            {
                callback_arg.channel   = p_instance_ctrl->p_ether_cfg->channel;
                callback_arg.event     = ETHER_EVENT_LINK_ON;
                callback_arg.p_context = p_instance_ctrl->p_ether_cfg->p_context;
                (*p_instance_ctrl->p_ether_cfg->p_callback)((void *) &callback_arg);
            }
        }
        else
        {
            /* When PHY auto-negotiation is not completed */
            p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
            p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_LINK_UP;
        }
#endif
    }
    /* When the link is down */
    else if (ETHER_LINK_CHANGE_LINK_DOWN == p_instance_ctrl->link_change)
    {
        p_instance_ctrl->link_change = ETHER_LINK_CHANGE_NO_CHANGE;

#if (ETHER_CFG_USE_LINKSTA == 1)

        /*
         * The Link Up/Down is confirmed by the Link Status bit of PHY register1,
         * because the LINK signal of PHY-LSI is used for LED indicator, and
         * isn't used for notifying the Link Up/Down to external device.
         */
        err = ether_link_status_check(p_instance_ctrl);
        if (FSP_ERR_ETHER_ERROR_LINK == err)
        {
            p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;

            /* Disable receive and transmit. */
            p_reg_etherc->ECMR_b.RE = 0;
            p_reg_etherc->ECMR_b.TE = 0;

            p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;

            if (NULL != p_instance_ctrl->p_ether_cfg->p_callback)
            {
                callback_arg.channel   = p_instance_ctrl->p_ether_cfg->channel;
                callback_arg.event     = ETHER_EVENT_LINK_OFF;
                callback_arg.p_context = p_instance_ctrl->p_ether_cfg->p_context;
                (*p_instance_ctrl->p_ether_cfg->p_callback)((void *) &callback_arg);
            }
        }
        else
        {
            ;                          /* no operation */
        }

#elif (ETHER_CFG_USE_LINKSTA == 0)
        p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;

        /* Disable receive and transmit. */
        p_reg_etherc->ECMR_b.RE = 0;
        p_reg_etherc->ECMR_b.TE = 0;

        p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;

        if (NULL != p_instance_ctrl->p_ether_cfg->p_callback)
        {
            callback_arg.channel   = p_instance_ctrl->p_ether_cfg->channel;
            callback_arg.event     = ETHER_EVENT_LINK_OFF;
            callback_arg.p_context = p_instance_ctrl->p_ether_cfg->p_context;
            (*p_instance_ctrl->p_ether_cfg->p_callback)((void *) &callback_arg);
        }
#endif
    }
    else
    {
        ;                              /* no operation */
    }

    return err;
} /* End of function R_ETHER_LinkProcess() */

/********************************************************************************************************************//**
 * @brief The setting of ETHERC is changed from normal sending and receiving mode to magic packet detection mode.
 * Implements @ref ether_api_t::wakeOnLANEnable.
 *
 * @retval  FSP_SUCCESS                                 Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_ETHER_ERROR_LINK                    Auto-negotiation is not completed, and reception is not enabled.
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                Initialization of PHY-LSI failed.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_WakeOnLANEnable (ether_ctrl_t * const p_ctrl)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;

#if (ETHER_CFG_USE_LINKSTA == 1)
    R_ETHERC0_Type * p_reg_etherc;
#endif

    /* Check argument */
#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* When the Link up processing is not completed, return error */
    ETHER_ERROR_RETURN(ETHER_LINK_ESTABLISH_STATUS_UP == p_instance_ctrl->link_establish_status,
                       FSP_ERR_ETHER_ERROR_LINK);

    /* When the Link up processing is completed */
    /* Change to the magic packet detection mode.  */
    ether_configure_mac(p_instance_ctrl, p_instance_ctrl->p_ether_cfg->p_mac_address, ETHER_USE_MAGIC_PACKET_DETECT);
    err = ether_do_link(p_instance_ctrl, ETHER_USE_MAGIC_PACKET_DETECT);
    if (FSP_SUCCESS == err)
    {
#if (ETHER_CFG_USE_LINKSTA == 1)
        p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;

        /* It is confirmed not to become Link down while changing the setting. */
        if (ETHER_CFG_LINK_PRESENT == p_reg_etherc->PSR_b.LMON)
        {
            err = FSP_SUCCESS;
        }
        else
        {
            err = FSP_ERR_ETHER_ERROR_LINK;
        }

#else

        /* It is confirmed not to become Link down while changing the setting. */
        err = ether_link_status_check(p_instance_ctrl);
#endif
    }
    else
    {
        err = FSP_ERR_ETHER_ERROR_LINK;
    }

    return err;
}                                      /* End of function R_ETHER_WakeOnLANEnable() */

/********************************************************************************************************************//**
 * @brief Receive Ethernet frame. Receives data to the location specified by the pointer to the receive buffer.
 * In zero copy mode, the address of the receive buffer is returned.
 * In non zero copy mode, the received data in the internal buffer is copied to the pointer passed by the argument.
 * Implements @ref ether_api_t::read.
 *
 * @retval  FSP_SUCCESS                                 Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_ETHER_ERROR_NO_DATA                 There is no data in receive buffer.
 * @retval  FSP_ERR_ETHER_ERROR_LINK                    Auto-negotiation is not completed, and reception is not enabled.
 * @retval  FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE       As a Magic Packet is being detected, transmission and reception
 *                                                      is not enabled.
 * @retval  FSP_ERR_ETHER_ERROR_FILTERING               Multicast Frame filter is enable, and Multicast Address Frame is
 *                                                      received.
 * @retval  FSP_ERR_INVALID_POINTER                     Value of the pointer is NULL.
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_Read (ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    uint8_t               * p_read_buffer   = NULL; /* Buffer location controlled by the Ethernet driver */
    uint32_t                received_size   = ETHER_NO_DATA;
    uint8_t              ** pp_read_buffer  = (uint8_t **) p_buffer;

    /* Check argument */
#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHER_ERROR_RETURN(NULL != p_buffer, FSP_ERR_INVALID_POINTER);
    ETHER_ERROR_RETURN(NULL != length_bytes, FSP_ERR_INVALID_POINTER);
#endif

    /* (1) Retrieve the receive buffer location controlled by the  descriptor. */
    /* When the Link up processing is not completed, return error */
    ETHER_ERROR_RETURN(ETHER_LINK_ESTABLISH_STATUS_UP == p_instance_ctrl->link_establish_status,
                       FSP_ERR_ETHER_ERROR_LINK);

    /* In case of detection mode of magic packet, return error. */
    ETHER_ERROR_RETURN(0 == ether_check_magic_packet_detection_bit(p_instance_ctrl),
                       FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE);

    while (FSP_SUCCESS == err)
    {
        /* When receive data exists. */

        if (ETHER_RD0_RACT != (p_instance_ctrl->p_rx_descriptor->status & ETHER_RD0_RACT))
        {
            /* Check multicast is detected when multicast frame filter is enabled */

            if (ETHER_MULTICAST_DISABLE == p_instance_ctrl->p_ether_cfg->multicast)
            {
                if (ETHER_RD0_RFS7_RMAF == (p_instance_ctrl->p_rx_descriptor->status & ETHER_RD0_RFS7_RMAF))
                {
                    /* The buffer is released at the multicast frame detect.  */

                    err = R_ETHER_BufferRelease((ether_ctrl_t *) p_instance_ctrl);

                    if (FSP_SUCCESS == err)
                    {
                        err = FSP_ERR_ETHER_ERROR_FILTERING;
                    }

                    break;
                }
            }

            if (ETHER_RD0_RFE == (p_instance_ctrl->p_rx_descriptor->status & ETHER_RD0_RFE))
            {
                /* The buffer is released at the error.  */
                err = R_ETHER_BufferRelease((ether_ctrl_t *) p_instance_ctrl);
            }
            else
            {
                /**
                 * Pass the pointer to received data to application.  This is
                 * zero-copy operation.
                 */
                p_read_buffer = p_instance_ctrl->p_rx_descriptor->p_buffer;

                /* Get bytes received */
                received_size =
                    (uint32_t) (p_instance_ctrl->p_rx_descriptor->size +
                                (uint16_t) p_instance_ctrl->p_ether_cfg->padding);
                break;
            }
        }
        else
        {
            break;
        }
    }

    if (FSP_SUCCESS == err)
    {
        /* When there is data to receive */
        if (received_size > ETHER_NO_DATA)
        {
            if (ETHER_ZEROCOPY_DISABLE == p_instance_ctrl->p_ether_cfg->zerocopy)
            {
                /* (2) Copy the data read from the receive buffer which is controlled
                 *     by the descriptor to the buffer which is specified by the user (up to 1024 bytes). */
                memcpy(p_buffer, p_read_buffer, received_size);

                /* (3) Read the receive data from the receive buffer controlled by the descriptor,
                 * and then release the receive buffer. */
                err = R_ETHER_BufferRelease((ether_ctrl_t *) p_instance_ctrl);
            }
            else
            {
                *pp_read_buffer = p_read_buffer;
            }

            *length_bytes = received_size;
        }
        /* When there is no data to receive */
        else
        {
            err = FSP_ERR_ETHER_ERROR_NO_DATA;
        }
    }

    return err;
}                                      /* End of function R_ETHER_Read() */

/********************************************************************************************************************//**
 * @brief Transmit Ethernet frame. Transmits data from the location specified by the pointer to the transmit
 *  buffer, with the data size equal to the specified frame length.
 *  In the non zero copy mode, transmits data after being copied to the internal buffer.
 *  Implements @ref ether_api_t::write.
 *
 * @retval  FSP_SUCCESS                                 Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_ETHER_ERROR_LINK                    Auto-negotiation is not completed, and reception is not enabled.
 * @retval  FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE       As a Magic Packet is being detected, transmission and reception
 *                                                      is not enabled.
 * @retval  FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL    Transmit buffer is not empty.
 * @retval  FSP_ERR_INVALID_POINTER                     Value of the pointer is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Value of the send frame size is out of range.
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_Write (ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    R_ETHERC_EDMAC_Type   * p_reg_edmac;

    uint8_t * p_write_buffer;
    uint32_t  write_buffer_size;

    /* Check argument */
#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHER_ERROR_RETURN(NULL != p_buffer, FSP_ERR_INVALID_POINTER);
    ETHER_ERROR_RETURN((ETHER_MINIMUM_FRAME_SIZE <= frame_length) && (ETHER_MAXIMUM_FRAME_SIZE >= frame_length),
                       FSP_ERR_INVALID_ARGUMENT);
#endif

    /* When the Link up processing is not completed, return error */
    ETHER_ERROR_RETURN(ETHER_LINK_ESTABLISH_STATUS_UP == p_instance_ctrl->link_establish_status,
                       FSP_ERR_ETHER_ERROR_LINK);

    /* In case of detection mode of magic packet, return error. */
    ETHER_ERROR_RETURN(0 == ether_check_magic_packet_detection_bit(p_instance_ctrl),
                       FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE);

    if (ETHER_ZEROCOPY_DISABLE == p_instance_ctrl->p_ether_cfg->zerocopy)
    {
        /* (1) Retrieve the transmit buffer location controlled by the  descriptor. */
        err = ether_buffer_get(p_instance_ctrl, (void **) &p_write_buffer, &write_buffer_size);

        /* Writing to the transmit buffer (buf) is enabled. */
        if (FSP_SUCCESS == err)
        {
            if (write_buffer_size < frame_length)
            {
                err = FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL; /* Transmit buffer overflow */
            }
            else
            {
                /* Write the transmit data to the transmit buffer. */

                /* (2) Write the data to the transmit buffer controlled by the  descriptor. */
                memcpy(p_write_buffer, p_buffer, frame_length);
            }
        }
    }

    /* Writing to the transmit buffer (buf) is enabled. */
    if (FSP_SUCCESS == err)
    {
        /* (3) Enable the EDMAC to transmit data in the transmit buffer. */
        /* When the Link up processing is not completed, return error */

        /* The data of the buffer is made active.  */
        if (ETHER_ZEROCOPY_ENABLE == p_instance_ctrl->p_ether_cfg->zerocopy)
        {
            p_instance_ctrl->p_tx_descriptor->p_buffer = (uint8_t *) p_buffer;
        }

        p_instance_ctrl->p_tx_descriptor->buffer_size = (uint16_t) frame_length;
        p_instance_ctrl->p_tx_descriptor->status     &= (~(ETHER_TD0_TFP1 | ETHER_TD0_TFP0));
        p_instance_ctrl->p_tx_descriptor->status     |= ((ETHER_TD0_TFP1 | ETHER_TD0_TFP0) | ETHER_TD0_TACT);
        p_instance_ctrl->p_tx_descriptor              = p_instance_ctrl->p_tx_descriptor->p_next;

        p_reg_edmac = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

        if (ETHER_EDMAC_EDTRR_TRANSMIT_REQUEST != p_reg_edmac->EDTRR)
        {
            /* Restart if stopped */
            p_reg_edmac->EDTRR = ETHER_EDMAC_EDTRR_TRANSMIT_REQUEST;
        }
    }

    return err;
}                                      /* End of function R_ETHER_Write() */

/**********************************************************************************************************************//**
 * Provides status of Ethernet driver in the user provided pointer. Implements @ref ether_api_t::txStatusGet.
 *
 * @retval  FSP_SUCCESS                  Transmit buffer address is stored in provided p_buffer_address.
 * @retval  FSP_ERR_ASSERTION            Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      p_status is NULL.
 * @retval  FSP_ERR_NOT_FOUND            Transmit buffer address has been overwritten in transmit descriptor.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_TxStatusGet (ether_ctrl_t * const p_ctrl, void * const p_buffer_address)
{
    ether_instance_ctrl_t       * p_instance_ctrl = (ether_instance_ctrl_t *) p_ctrl;
    R_ETHERC_EDMAC_Type         * p_reg_edmac;
    ether_instance_descriptor_t * p_descriptor;
    uint8_t ** p_sent_buffer_address = (uint8_t **) p_buffer_address;
    fsp_err_t  err = FSP_ERR_NOT_FOUND;

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHER_ERROR_RETURN(NULL != p_buffer_address, FSP_ERR_INVALID_POINTER);
#endif

    p_reg_edmac = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

    p_descriptor = (ether_instance_descriptor_t *) p_reg_edmac->TDFAR;

    /* Descriptor is NULL, when no packet transmitted. */
    if (NULL != p_descriptor)
    {
        uint32_t num_tx_descriptors = p_instance_ctrl->p_ether_cfg->num_tx_descriptors;
        ether_instance_descriptor_t * p_tx_descriptors = p_instance_ctrl->p_ether_cfg->p_tx_descriptors;

        p_descriptor = (ether_instance_descriptor_t *) ((uint8_t *) p_descriptor - sizeof(ether_instance_descriptor_t));

        if (p_descriptor < p_tx_descriptors)
        {
            p_descriptor = &p_tx_descriptors[num_tx_descriptors - 1];
        }

        /* Check that the descriptor is not overridden. */
        if ((NULL != p_descriptor->p_buffer) && (ETHER_TD0_TACT != (p_descriptor->status & ETHER_TD0_TACT)))
        {
            *p_sent_buffer_address = p_descriptor->p_buffer;
            err = FSP_SUCCESS;
        }
        else
        {
            ;
        }
    }

    return err;
}                                      /* End of function R_ETHER_VersionGet() */

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * @brief Parameter error check function for open.
 *
 * @param[in] p_instance_ctrl   Pointer to the control block for the channel
 * @param[in] p_cfg             Pointer to the configuration structure specific to UART mode
 *
 * @retval  FSP_SUCCESS                  No parameter error found
 * @retval  FSP_ERR_ASSERTION            Pointer to ETHER control block or configuration structure is NULL
 * @retval  FSP_ERR_ALREADY_OPEN         Control block has already been opened
 * @retval  FSP_ERR_INVALID_CHANNEL      Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to MAC address is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Irq number lower then 0.
 **********************************************************************************************************************/
static fsp_err_t ether_open_param_check (ether_instance_ctrl_t const * const p_instance_ctrl,
                                         ether_cfg_t const * const           p_cfg)
{
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN((NULL != p_cfg), FSP_ERR_INVALID_POINTER);
    ETHER_ERROR_RETURN((NULL != p_cfg->p_mac_address), FSP_ERR_INVALID_POINTER);
    ETHER_ERROR_RETURN((BSP_FEATURE_ETHER_MAX_CHANNELS > p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
    ETHER_ERROR_RETURN((0 <= p_cfg->irq), FSP_ERR_INVALID_ARGUMENT);
    ETHER_ERROR_RETURN((p_cfg->padding <= ETHER_PADDING_3BYTE), FSP_ERR_INVALID_ARGUMENT);

    if (p_cfg->padding != ETHER_PADDING_DISABLE)
    {
        ETHER_ERROR_RETURN((p_cfg->padding_offset <= ETHER_MAXIMUM_PADDING_OFFSET), FSP_ERR_INVALID_ARGUMENT);
    }

    if (p_cfg->zerocopy == ETHER_ZEROCOPY_DISABLE)
    {
        ETHER_ERROR_RETURN((p_cfg->pp_ether_buffers != NULL), FSP_ERR_INVALID_ARGUMENT);
    }

    ETHER_ERROR_RETURN((ETHER_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);

    return FSP_SUCCESS;
}

#endif

/***********************************************************************************************************************
 * Function Name: ether_reset_mac
 * Description  : The EDMAC and EtherC are reset through the software reset.
 * Arguments    : channel -
 *                    ETHERC channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_reset_mac (R_ETHERC_EDMAC_Type * const p_reg)
{
    p_reg->EDMR_b.SWR = 1;

    /*
     * Waiting time until the initialization of ETHERC and EDMAC is completed is 64 cycles
     * in the clock conversion of an internal bus of EDMAC.
     */
    R_BSP_SoftwareDelay(ETHER_ETHERC_INITIALIZATION_WAIT_CYCLE * BSP_DELAY_UNITS_SECONDS / SystemCoreClock + 1,
                        BSP_DELAY_UNITS_MICROSECONDS);
}                                      /* End of function ether_reset_mac() */

/***********************************************************************************************************************
 * Function Name: ether_init_descriptors
 * Description  : The EDMAC descriptors and the driver buffers are initialized.
 * Arguments    : channel -
 *                    ETHERC channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_init_descriptors (ether_instance_ctrl_t * const p_instance_ctrl)
{
    ether_instance_descriptor_t * p_descriptor = NULL;
    uint32_t i;

    /* Initialize the receive descriptors */
    for (i = 0; i < p_instance_ctrl->p_ether_cfg->num_rx_descriptors; i++)
    {
        p_descriptor              = &p_instance_ctrl->p_ether_cfg->p_rx_descriptors[i];
        p_descriptor->buffer_size = (uint16_t) p_instance_ctrl->p_ether_cfg->ether_buffer_size;
        p_descriptor->size        = 0;
        p_descriptor->p_next      = &p_instance_ctrl->p_ether_cfg->p_rx_descriptors[(i + 1)];

        if (NULL != p_instance_ctrl->p_ether_cfg->pp_ether_buffers)
        {
            p_descriptor->p_buffer = p_instance_ctrl->p_ether_cfg->pp_ether_buffers[i];
            p_descriptor->status   = ETHER_RD0_RACT;
        }
        else
        {
            p_descriptor->p_buffer = NULL;
        }
    }

    if (NULL != p_descriptor)
    {
        /* The last descriptor points back to the start */
        p_descriptor->status |= ETHER_RD0_RDLE;
        p_descriptor->p_next  = &p_instance_ctrl->p_ether_cfg->p_rx_descriptors[0];

        /* Initialize application receive descriptor pointer */
        p_instance_ctrl->p_rx_descriptor = &p_instance_ctrl->p_ether_cfg->p_rx_descriptors[0];
    }

    /* Initialize the transmit descriptors */
    for (i = 0; i < p_instance_ctrl->p_ether_cfg->num_tx_descriptors; i++)
    {
        p_descriptor              = &p_instance_ctrl->p_ether_cfg->p_tx_descriptors[i];
        p_descriptor->buffer_size = 1; /* Set a value equal to or greater than 1. (reference to UMH)
                                        * When transmitting data, the value of size is set to the function argument
                                        * R_ETHER_Write. */
        p_descriptor->size        = 0; /* Reserved : The write value should be 0. (reference to UMH) */
        p_descriptor->status      = 0;
        p_descriptor->p_next      = &p_instance_ctrl->p_ether_cfg->p_tx_descriptors[(i + 1)];

        if ((ETHER_ZEROCOPY_DISABLE == p_instance_ctrl->p_ether_cfg->zerocopy) &&
            (NULL != p_instance_ctrl->p_ether_cfg->pp_ether_buffers))
        {
            p_descriptor->p_buffer =
                p_instance_ctrl->p_ether_cfg->pp_ether_buffers[(p_instance_ctrl->p_ether_cfg->num_rx_descriptors + i)];
        }
        else
        {
            p_descriptor->p_buffer = NULL;
        }
    }

    if (NULL != p_descriptor)
    {
        /* The last descriptor points back to the start */
        p_descriptor->status |= ETHER_TD0_TDLE;
        p_descriptor->p_next  = &p_instance_ctrl->p_ether_cfg->p_tx_descriptors[0];

        /* Initialize application transmit descriptor pointer */
        p_instance_ctrl->p_tx_descriptor = &p_instance_ctrl->p_ether_cfg->p_tx_descriptors[0];
    }
}                                      /* End of function ether_init_descriptors() */

/***********************************************************************************************************************
 * Function Name: ether_init_buffers
 * Description  : The driver buffers are initialized.
 * Arguments    : p_instance_ctrl -
 *                    ETHERC control block.
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_init_buffers (ether_instance_ctrl_t * const p_instance_ctrl)
{
    uint32_t i;
    uint32_t buffer_num;

    if (NULL != p_instance_ctrl->p_ether_cfg->pp_ether_buffers)
    {
        if (ETHER_ZEROCOPY_DISABLE == p_instance_ctrl->p_ether_cfg->zerocopy)
        {
            buffer_num =
                (uint32_t) (p_instance_ctrl->p_ether_cfg->num_tx_descriptors +
                            p_instance_ctrl->p_ether_cfg->num_rx_descriptors);
        }
        else
        {
            buffer_num = (uint32_t) p_instance_ctrl->p_ether_cfg->num_rx_descriptors;
        }

        for (i = 0; i < buffer_num; i++)
        {
            memset(p_instance_ctrl->p_ether_cfg->pp_ether_buffers[i],
                   0x00,
                   p_instance_ctrl->p_ether_cfg->ether_buffer_size);
        }
    }
}                                      /* End of function ether_init_buffers() */

/********************************************************************************************************************//**
 * @brief Get Points to the buffer pointer used by the stack.
 * @param[in]  p_instance_ctrl                              Ethernet driver control block.
 * @param[out] p_buffer                                     Pointer to location to store the buffer pointer
 * @param[out] p_buffer_size                                Pointer to location to store the buffer size
 * @retval     FSP_SUCCESS                                  Processing completed successfully.
 * @retval     FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL     Transmit buffer is not empty.
 *
 ***********************************************************************************************************************/
static fsp_err_t ether_buffer_get (ether_instance_ctrl_t * const p_instance_ctrl,
                                   void ** const                 p_buffer,
                                   uint32_t                    * p_buffer_size)
{
    fsp_err_t err = FSP_SUCCESS;

    /* When the Link up processing is completed */
    /* All transmit buffers are full */
    if (ETHER_TD0_TACT == (p_instance_ctrl->p_tx_descriptor->status & ETHER_TD0_TACT))
    {
        err = FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL;
    }
    else
    {
        /* Give application another buffer to work with */
        (*p_buffer)      = p_instance_ctrl->p_tx_descriptor->p_buffer;
        (*p_buffer_size) = p_instance_ctrl->p_ether_cfg->ether_buffer_size;
        err              = FSP_SUCCESS;
    }

    return err;
}                                      /* End of function ether_buffer_get() */

/***********************************************************************************************************************
 * Function Name: ether_config_ethernet
 * Description  : Configure the Ethernet Controller (EtherC) and the Ethernet
 *                Direct Memory Access controller (EDMAC).
 * Arguments    : channel -
 *                    ETHERC channel number
 *                mode -
 *                   The operational mode is specified.
 *                   NO_USE_MAGIC_PACKET_DETECT (0) - Communicate mode usually
 *                   USE_MAGIC_PACKET_DETECT    (1) - Magic packet detection mode
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_config_ethernet (ether_instance_ctrl_t const * const p_instance_ctrl, const uint8_t mode)
{
    R_ETHERC0_Type      * p_reg_etherc;
    R_ETHERC_EDMAC_Type * p_reg_edmac;

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)

    /* Check argument */
    if ((NULL == p_instance_ctrl) || (ETHER_OPEN != p_instance_ctrl->open))
    {
        return;
    }
#endif

    p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;
    p_reg_edmac  = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

    /* Magic packet detection mode */
    if (ETHER_USE_MAGIC_PACKET_DETECT == mode)
    {
#if (ETHER_CFG_USE_LINKSTA == 1)
        p_reg_etherc->ECSIPR = (ETHER_ETHERC_INTERRUPT_ENABLE_LCHNG | ETHER_ETHERC_INTERRUPT_ENABLE_MPD);
#elif (ETHER_CFG_USE_LINKSTA == 0)
        p_reg_etherc->ECSIPR_b.MPDIP = 1;
#endif
        p_reg_edmac->EESIPR_b.ECIIP = 1;
    }
    /* Normal mode */
    else
    {
#if (ETHER_CFG_USE_LINKSTA == 1)

        /* LINK Signal Change Interrupt Enable */
        p_reg_etherc->ECSR_b.LCHNG     = 1;
        p_reg_etherc->ECSIPR_b.LCHNGIP = 1;
#endif
        p_reg_edmac->EESIPR_b.ECIIP = 1;

        /* Frame receive interrupt and frame transmit end interrupt */
        p_reg_edmac->EESIPR_b.FRIP = 1;                   /* Enable the frame receive interrupt. */
        p_reg_edmac->EESIPR_b.TCIP = 1;                   /* Enable the frame transmit end interrupt. */
    }

    /* Ethernet length 1514bytes + CRC and intergap is 96-bit time */
    p_reg_etherc->RFLR = ETHER_ETHERC_RFLR_DEFAULT_VALUE; /* Ethernet length (1514bytes) + CRC(4byte) */
    p_reg_etherc->IPGR = ETHER_ETHERC_IPGR_DEFAULT_VALUE; /* Interpacket Gap is 96-bit time */

    /* Continuous reception number of Broadcast frame */
    p_reg_etherc->BCFRR = p_instance_ctrl->p_ether_cfg->broadcast_filter;

#if ((defined(__GNUC__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || (defined(__ARMCC_VERSION) && \
    !defined(__ARM_BIG_ENDIAN)) || (defined(__ICCARM__) && (__LITTLE_ENDIAN__)))

    /* Set little endian mode */
    p_reg_edmac->EDMR_b.DE = 1;
#endif

    /* Initialize Rx descriptor list address */
    /* Casting the pointer to a uint32_t type is valid because the Renesas Compiler uses 4 bytes per pointer. */
    p_reg_edmac->RDLAR = (uint32_t) p_instance_ctrl->p_rx_descriptor;

    /* Initialize Tx descriptor list address */
    /* Casting the pointer to a uint32_t type is valid because the Renesas Compiler uses 4 bytes per pointer. */
    p_reg_edmac->TDLAR = (uint32_t) p_instance_ctrl->p_tx_descriptor;

    if (ETHER_MULTICAST_DISABLE == p_instance_ctrl->p_ether_cfg->multicast)
    {
        /* Reflect the EESR.RMAF bit status in the RD0.RFS bit in the receive descriptor */
        p_reg_edmac->TRSCER = ETHER_EDMAC_TRSCER_MULTICAST_DISABLE;
    }
    else
    {
        /* Don't reflect the EESR.RMAF bit status in the RD0.RFS bit in the receive descriptor */
        p_reg_edmac->TRSCER = ETHER_EDMAC_TRSCER_MULTICAST_ENABLE;
    }

    /* Threshold of Tx_FIFO */
    /* To prevent a transmit underflow, setting the initial value (store and forward modes) is recommended. */
    p_reg_edmac->TFTR = ETHER_EDMAC_TFTR_STORE_AND_FORWARD_MODE;

    p_reg_edmac->FDR = BSP_FEATURE_ETHER_FIFO_DEPTH;

    /*  Configure receiving method
     * b0      RNR - Receive Request Bit Reset - Continuous reception of multiple frames is possible.
     * b31:b1  Reserved set to 0
     */
    p_reg_edmac->RMCR = ETHER_EDMAC_RMCR_MULTIPLE_FRAMES_ENABLE;
}                                      /* End of function ether_config_ethernet() */

/***********************************************************************************************************************
 * Function Name: ether_pause_resolution
 * Description  : Determines PAUSE frame generation and handling. Uses
 *                the resolution Table 28B-3 of IEEE 802.3-2008.
 * Arguments    : local_ability -
 *                    local PAUSE capability (2 least significant bits)
 *                partner_ability -
 *                    link partner PAUSE capability (2 least significant bits)
 *                *ptx_pause -
 *                    pointer to location to store the result of the table lookup for transmit
 *                    PAUSE. 1 is enable, 0 is disable.
 *                *prx_pause -
 *                    pointer to location to store the result of the table lookup for receive
 *                    PAUSE. 1 is enable, 0 is disable.
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_pause_resolution (uint32_t const local_ability,
                                    uint32_t const partner_ability,
                                    uint32_t     * ptx_pause,
                                    uint32_t     * prx_pause)
{
    uint32_t i;
    uint32_t ability_compare;

    /*
     * Arrange the bits so that they correspond to the Table 28B-3
     * of the IEEE 802.3 values.
     */
    ability_compare =
        (uint32_t) (((local_ability & ETHER_LINK_RESOLUTION_ABILITY_MASK) <<
                     ETHER_LINK_RESOLUTION_LOCAL_ABILITY_BITSHIFT) |
                    (partner_ability & ETHER_LINK_RESOLUTION_ABILITY_MASK));

    /* Walk through the look up table */
    for (i = 0; i < ETHER_PAUSE_TABLE_ENTRIES; i++)
    {
        if ((ability_compare & pause_resolution[i].mask) == pause_resolution[i].value)
        {
            (*ptx_pause) = pause_resolution[i].transmit;
            (*prx_pause) = pause_resolution[i].receive;

            return;
        }
    }
}                                      /* End of function ether_pause_resolution() */

/***********************************************************************************************************************
 * Function Name: ether_configure_mac
 * Description  : Software reset is executed, and ETHERC and EDMAC are configured.
 * Arguments    : channel -
 *                    ETHERC channel number
 *                mac_addr -
 *                    The MAC address of ETHERC
 *                mode -
 *                    The operational mode is specified.
 *                    NO_USE_MAGIC_PACKET_DETECT (0) - Communicate mode usually
 *                    USE_MAGIC_PACKET_DETECT    (1) - Magic packet detection mode
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_configure_mac (ether_instance_ctrl_t * const p_instance_ctrl,
                                 const uint8_t                 mac_addr[],
                                 const uint8_t                 mode)
{
    R_ETHERC0_Type * p_reg_etherc;
    uint32_t         mac_h;
    uint32_t         mac_l;

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)

    /* Check argument */
    if ((NULL == p_instance_ctrl) || (ETHER_OPEN != p_instance_ctrl->open))
    {
        return;
    }
#endif

    p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;

    /* Software reset */
    ether_reset_mac(p_instance_ctrl->p_reg_edmac);

    /* Setting the padding function */
    ether_configure_padding(p_instance_ctrl);

    /* Set MAC address */
    mac_h = (((((uint32_t) mac_addr[0] << 24) | ((uint32_t) mac_addr[1] << 16)) | ((uint32_t) mac_addr[2] << 8)) |
             (uint32_t) mac_addr[3]);

    mac_l = (((uint32_t) mac_addr[4] << 8) | (uint32_t) mac_addr[5]);

    p_reg_etherc->MAHR = mac_h;
    p_reg_etherc->MALR = mac_l;

    /* Initialize receive and transmit descriptors */
    ether_init_descriptors(p_instance_ctrl);

    /* Perform reset of hardware interface configuration */
    ether_config_ethernet(p_instance_ctrl, mode);
}                                      /* End of function ether_configure_mac() */

/********************************************************************************************************************//**
 * @brief Determines the partner PHY capability through auto-negotiation process. The link abilities
 *        are handled to determine duplex, speed and flow control (PAUSE frames).
 *
 * @param[in] p_instance_ctrl           Pointer to the control block for the channel
 * @param[in] mode                      The operational mode is specified.
 *                                      NO_USE_MAGIC_PACKET_DETECT (0) - Communicate mode usually
 *                                      USE_MAGIC_PACKET_DETECT    (1) - Magic packet detection mode
 * @retval  FSP_SUCCESS                 Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block or configuration structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_ETHER_ERROR_LINK    Auto-negotiation of PHY-LSI is not completed
 *                                      or result of Auto-negotiation is abnormal.
 *
 ***********************************************************************************************************************/
static fsp_err_t ether_do_link (ether_instance_ctrl_t * const p_instance_ctrl, const uint8_t mode)
{
    fsp_err_t             err;
    R_ETHERC0_Type      * p_reg_etherc;
    R_ETHERC_EDMAC_Type * p_reg_edmac;

    uint32_t  link_speed_duplex  = 0;
    uint32_t  local_pause_bits   = 0;
    uint32_t  partner_pause_bits = 0;
    uint32_t  transmit_pause_set = 0;
    uint32_t  receive_pause_set  = 0;
    uint32_t  full_duplex        = 0;
    fsp_err_t link_result;

#if (ETHER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_ERROR_RETURN(ETHER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;
    p_reg_edmac  = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

    /* Set the link status */
    link_result = p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_api->linkPartnerAbilityGet(
        p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_ctrl,
        &link_speed_duplex,
        &local_pause_bits,
        &partner_pause_bits);

    if (FSP_SUCCESS == link_result)
    {
        switch (link_speed_duplex)
        {
            /* Half duplex link */
            case ETHER_PHY_LINK_SPEED_100H:
            {
                p_reg_etherc->ECMR_b.DM  = 0;
                p_reg_etherc->ECMR_b.RTM = 1;
                err = FSP_SUCCESS;
                break;
            }

            case ETHER_PHY_LINK_SPEED_10H:
            {
                p_reg_etherc->ECMR_b.DM  = 0;
                p_reg_etherc->ECMR_b.RTM = 0;
                err = FSP_SUCCESS;
                break;
            }

            /* Full duplex link */
            case ETHER_PHY_LINK_SPEED_100F:
            {
                p_reg_etherc->ECMR_b.DM  = 1;
                p_reg_etherc->ECMR_b.RTM = 1;
                full_duplex              = 1;
                err = FSP_SUCCESS;
                break;
            }

            case ETHER_PHY_LINK_SPEED_10F:
            {
                p_reg_etherc->ECMR_b.DM  = 1;
                p_reg_etherc->ECMR_b.RTM = 0;
                full_duplex              = 1;
                err = FSP_SUCCESS;
                break;
            }

            default:
            {
                err = FSP_ERR_ETHER_ERROR_LINK;
                break;
            }
        }

        /* At the communicate mode usually */
        if (FSP_SUCCESS == err)
        {
            if (ETHER_NO_USE_MAGIC_PACKET_DETECT == mode)
            {
                /* When pause frame is used */
                if ((full_duplex) && (ETHER_FLOW_CONTROL_ENABLE == p_instance_ctrl->p_ether_cfg->flow_control))
                {
                    /* Set automatic PAUSE for 512 bit-time */
                    p_reg_etherc->APR = ETHER_ETHERC_APR_MAXIMUM_VALUE;

                    /* Set unlimited retransmit of PAUSE frames */
                    p_reg_etherc->TPAUSER = 0;

                    /* PAUSE flow control FIFO settings. */
                    p_reg_edmac->FCFTR = ETHER_ETHERC_FCFTR_MINIMUM_VALUE;

                    /* Control of a PAUSE frame whose TIME parameter value is 0 is enabled. */
                    p_reg_etherc->ECMR_b.ZPF = 1;

                    /**
                     * Enable PAUSE for full duplex link depending on
                     * the pause resolution results
                     */
                    ether_pause_resolution(local_pause_bits, partner_pause_bits, &transmit_pause_set,
                                           &receive_pause_set);

                    if (ETHER_PAUSE_XMIT_ON == transmit_pause_set)
                    {
                        /* Enable automatic PAUSE frame transmission */
                        p_reg_etherc->ECMR_b.TXF = 1;
                    }
                    else
                    {
                        /* Disable automatic PAUSE frame transmission */
                        p_reg_etherc->ECMR_b.TXF = 0;
                    }

                    if (ETHER_PAUSE_RECV_ON == receive_pause_set)
                    {
                        /* Enable reception of PAUSE frames */
                        p_reg_etherc->ECMR_b.RXF = 1;
                    }
                    else
                    {
                        /* Disable reception of PAUSE frames */
                        p_reg_etherc->ECMR_b.RXF = 0;
                    }
                }
                /* When pause frame is not used */
                else
                {
                    /* Disable PAUSE for half duplex link */
                    p_reg_etherc->ECMR_b.TXF = 0;
                    p_reg_etherc->ECMR_b.RXF = 0;
                }

                /* Set the promiscuous mode bit */
                p_reg_etherc->ECMR_b.PRM = p_instance_ctrl->p_ether_cfg->promiscuous;

                /* Enable receive and transmit. */
                p_reg_etherc->ECMR_b.RE = 1;
                p_reg_etherc->ECMR_b.TE = 1;

                /* Enable EDMAC receive */
                p_reg_edmac->EDRRR = 0x1;
            }
            /* At the magic packet detection mode */
            else
            {
                /* The magic packet detection is permitted. */
                p_reg_etherc->ECMR_b.MPDE = 1;

                /* Because data is not transmitted for the magic packet detection waiting,
                 * only the reception is permitted. */
                p_reg_etherc->ECMR_b.RE = 1;

                /*
                 * The reception function of EDMAC keep invalidity
                 * because the receive data don't need to be read when the magic packet detection mode.
                 */
            }
        }
    }
    else
    {
        err = FSP_ERR_ETHER_ERROR_LINK;
    }

    return err;
}                                      /* End of function ether_do_link() */

/***********************************************************************************************************************
 * Function Name: ether_check_magic_packet_detection_bit
 * Description  :
 * Arguments    : ether_instance_ctrl_t const * const p_instance_ctrl
 * Return Value : 1: Magic Packet detection is enabled.
 *                0: Magic Packet detection is disabled.
 ***********************************************************************************************************************/
static uint8_t ether_check_magic_packet_detection_bit (ether_instance_ctrl_t const * const p_instance_ctrl)
{
    R_ETHERC0_Type * p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;
    uint8_t          ret          = 0;

    /* The MPDE bit can be referred to only when ETHERC operates. */
    if ((1 == p_reg_etherc->ECMR_b.MPDE))
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}                                      /* End of function ether_check_magic_packet_detection_bit() */

/*******************************************************************************************************************//**
 * @brief Verifies the Etherent link is up or not.
 *
 * @param[in] p_instance_ctrl   Pointer to the control block for the channel
 *
 * @retval  FSP_SUCCESS:                  Link is up
 * @retval  FSP_ERR_ETHER_ERROR_LINK:     Link is down
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK  Initialization of PHY-LSI failed.
 **********************************************************************************************************************/
static fsp_err_t ether_link_status_check (ether_instance_ctrl_t const * const p_instance_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    fsp_err_t link_status;

    link_status = p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_api->linkStatusGet(
        p_instance_ctrl->p_ether_cfg->p_ether_phy_instance->p_ctrl);

    if (FSP_ERR_ETHER_PHY_ERROR_LINK == link_status)
    {
        /* Link is down */
        err = FSP_ERR_ETHER_ERROR_LINK;
    }
    else
    {
        /* Link is up */
        err = FSP_SUCCESS;
    }

    return err;
}                                      /* End of function ether_link_status_check() */

/***********************************************************************************************************************
 * Function Name: ether_eint_isr
 * Description  : Interrupt handler for Ethernet receive and transmit interrupts.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void ether_eint_isr (void)
{
    uint32_t status_ecsr;
    uint32_t status_eesr;

    ether_callback_args_t callback_arg;
    R_ETHERC0_Type      * p_reg_etherc;
    R_ETHERC_EDMAC_Type * p_reg_edmac;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    ether_instance_ctrl_t * p_instance_ctrl = (ether_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    p_reg_etherc = (R_ETHERC0_Type *) p_instance_ctrl->p_reg_etherc;
    p_reg_edmac  = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;

    status_ecsr = p_reg_etherc->ECSR;
    status_eesr = p_reg_edmac->EESR;

    /* When the ETHERC status interrupt is generated */
    if (status_eesr & ETHER_EDMAC_INTERRUPT_FACTOR_ECI)
    {
#if (ETHER_CFG_USE_LINKSTA == 1)

        /* When the link signal change interrupt is generated */
        if (ETHER_ETHERC_INTERRUPT_FACTOR_LCHNG == (status_ecsr & ETHER_ETHERC_INTERRUPT_FACTOR_LCHNG))
        {
            /* The state of the link signal is confirmed and Link Up/Down is judged. */
            /* When becoming Link up */
            if (ETHER_CFG_LINK_PRESENT == p_reg_etherc->PSR_b.LMON)
            {
                p_instance_ctrl->link_change = ETHER_LINK_CHANGE_LINK_UP;
            }
            /* When Link becomes down */
            else
            {
                p_instance_ctrl->link_change = ETHER_LINK_CHANGE_LINK_DOWN;
            }
        }
#endif

        /* When the Magic Packet detection interrupt is generated */
        if (ETHER_ETHERC_INTERRUPT_FACTOR_MPD == (status_ecsr & ETHER_ETHERC_INTERRUPT_FACTOR_MPD))
        {
            p_instance_ctrl->magic_packet = ETHER_MAGIC_PACKET_DETECTED;
        }

        /*
         * Because each bit of the ECSR register is cleared when one is written,
         * the value read from the register is written and the bit is cleared.
         */
        p_reg_etherc->ECSR = status_ecsr; /* Clear all ETHERC status BFR, PSRTO, LCHNG, MPD, ICD */
    }

    /*
     * Because each bit of the EESR register is cleared when one is written,
     * the value read from the register is written and the bit is cleared.
     */
    p_reg_edmac->EESR = status_eesr;      /* Clear EDMAC status bits */

    /* Callback : Interrupt handler */
    if (NULL != p_instance_ctrl->p_ether_cfg->p_callback)
    {
        callback_arg.channel     = p_instance_ctrl->p_ether_cfg->channel;
        callback_arg.event       = ETHER_EVENT_INTERRUPT;
        callback_arg.status_ecsr = status_ecsr;
        callback_arg.status_eesr = status_eesr;
        callback_arg.p_context   = p_instance_ctrl->p_ether_cfg->p_context;
        (*p_instance_ctrl->p_ether_cfg->p_callback)((void *) &callback_arg);
    }

    /* Clear pending interrupt flag to make sure it doesn't fire again
     * after exiting. */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());
}                                      /* End of function ether_eint_isr() */

/***********************************************************************************************************************
 * Function Name: ether_enable_icu
 * Description  :
 * Arguments    : channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_enable_icu (ether_instance_ctrl_t * const p_instance_ctrl)
{
    /** Configure the Ethernet interrupt. */
    R_BSP_IrqCfgEnable(p_instance_ctrl->p_ether_cfg->irq,
                       p_instance_ctrl->p_ether_cfg->interrupt_priority,
                       p_instance_ctrl);
}                                      /* End of function ether_enable_icu() */

/***********************************************************************************************************************
 * Function Name: ether_disable_icu
 * Description  :
 * Arguments    : channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_disable_icu (ether_instance_ctrl_t * const p_instance_ctrl)
{
    /* Get IRQ number for EDMAC_EINT interrupt. */
    NVIC_DisableIRQ(p_instance_ctrl->p_ether_cfg->irq);
    R_FSP_IsrContextSet(p_instance_ctrl->p_ether_cfg->irq, NULL);
}                                      /* End of function ether_disable_icu() */

/***********************************************************************************************************************
 * Function Name: ether_configure_padding
 * Description  :
 * Arguments    : channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_configure_padding (ether_instance_ctrl_t * const p_instance_ctrl)
{
    R_ETHERC_EDMAC_Type * p_reg_edmac;
    p_reg_edmac                = (R_ETHERC_EDMAC_Type *) p_instance_ctrl->p_reg_edmac;
    p_reg_edmac->RPADIR_b.PADR = (unsigned) p_instance_ctrl->p_ether_cfg->padding_offset & ETHER_MAXIMUM_PADDING_OFFSET;
    p_reg_edmac->RPADIR_b.PADS = p_instance_ctrl->p_ether_cfg->padding;
}
