/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rmac_cfg.h"
#include "r_rmac.h"
#include "r_layer3_switch.h"
#include "r_rmac_phy.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RMAC_OPEN                                   (('R' << 24U) | ('M' << 16U) | ('A' << 8U) | ('C' << 0U))

#define RMAC_ETHA_REG_SIZE                          (R_ETHA1_BASE - R_ETHA0_BASE)
#define RMAC_RMAC_REG_SIZE                          (R_RMAC1_BASE - R_RMAC0_BASE)

/* Register values */
#define RMAC_REG_MRAFC_PROMISCUOUS_VALUE            (R_RMAC0_MRAFC_UCENE_Msk | R_RMAC0_MRAFC_MCENE_Msk |    \
                                                     R_RMAC0_MRAFC_BCENE_Msk | R_RMAC0_MRAFC_BCACE_Msk |    \
                                                     R_RMAC0_MRAFC_NDAREE_Msk | R_RMAC0_MRAFC_SDSFREE_Msk | \
                                                     R_RMAC0_MRAFC_NSAREE_Msk | R_RMAC0_MRAFC_UCENP_Msk |   \
                                                     R_RMAC0_MRAFC_MCENP_Msk | R_RMAC0_MRAFC_BCENP_Msk |    \
                                                     R_RMAC0_MRAFC_BCACP_Msk | R_RMAC0_MRAFC_NDAREP_Msk |   \
                                                     R_RMAC0_MRAFC_SDSFREP_Msk | R_RMAC0_MRAFC_NSAREP_Msk)

/* For descriptor fields */
#define RMAC_DESCRIPTOR_FIELD_DS_UPPER_MASK         (0xF00)
#define RMAC_DESCRIPTOR_FIELD_DS_LOWER_MASK         (0x00FF)
#define RMAC_DESCRIPTOR_FIELD_DS_UPPER_POSITION     (0x8)
#define RMAC_DESCRIPTOR_FIELD_DV_MASK               (0x7F)
#define RMAC_DESCRIPTOR_FIELD_PTR_UPPER_MASK        (0xFF00000000)
#define RMAC_DESCRIPTOR_FIELD_PTR_LOWER_MASK        (0xFFFFFFFF)
#define RMAC_DESCRIPTOR_FIELD_PTR_UPPER_POSITION    (32)

/* Definition of the maximum / minimum number of data that can be sent at one time in the Ethernet */
#define RMAC_MAXIMUM_FRAME_SIZE                     (1514U) /* Maximum number of transmitted data */
#define RMAC_MINIMUM_FRAME_SIZE                     (60U)   /* Minimum number of transmitted data */
#define RMAC_NO_DATA                                (0)

/* Invalid value that mean all queue is not running or not available. */
#define RMAC_INVALID_QUEUE_INDEX                    (0xFFFFFFFF)

/* Increments a index and wraps around to 0 if it exceeds the maximum value */
#define RMAC_INCREMENT_INDEX(x, max)    (x = (x + 1) % max)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * ether_prv_ns_callback)(ether_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile ether_prv_ns_callback)(ether_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t rmac_open_param_check(rmac_instance_ctrl_t const * const p_instance_ctrl,
                                       ether_cfg_t const * const          p_cfg);

#endif

static void      rmac_init_descriptors(rmac_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t rmac_init_descriptor_queues(rmac_instance_ctrl_t * const p_instance_ctrl);
static void      rmac_init_buffers(rmac_instance_ctrl_t * const p_instance_ctrl);

static void      rmac_configure_reception_filter(rmac_instance_ctrl_t const * const p_instance_ctrl);
static fsp_err_t rmac_do_link(rmac_instance_ctrl_t * const                 p_instance_ctrl,
                              const layer3_switch_magic_packet_detection_t mode);
static fsp_err_t rmac_link_status_check(rmac_instance_ctrl_t const * const p_instance_ctrl);

static void      rmac_call_callback(rmac_instance_ctrl_t * p_instance_ctrl, ether_callback_args_t * p_callback_args);
static void      r_rmac_switch_interrupt_callback(ether_switch_callback_args_t * p_args);
static fsp_err_t r_rmac_reset_rx_descriptor(rmac_instance_ctrl_t * p_instance_ctrl, void * p_buffer);
static void      r_rmac_disable_reception(rmac_instance_ctrl_t * p_instance_ctrl);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void rmac_rmpi_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* RMAC implementation of ether interface  */
const ether_api_t g_ether_on_rmac =
{
    .open            = R_RMAC_Open,
    .close           = R_RMAC_Close,
    .bufferRelease   = R_RMAC_BufferRelease,
    .rxBufferUpdate  = R_RMAC_RxBufferUpdate,
    .linkProcess     = R_RMAC_LinkProcess,
    .wakeOnLANEnable = R_RMAC_WakeOnLANEnable,
    .read            = R_RMAC_Read,
    .write           = R_RMAC_Write,
    .txStatusGet     = R_RMAC_TxStatusGet,
    .callbackSet     = R_RMAC_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup RMAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the ether module and applies configurations. Implements @ref ether_api_t::open.
 *
 * @brief After RMAC, Switch and PHY-LSI are reset in software, an auto negotiation of PHY-LSI is begun.
 * Afterwards, the link signal change interrupt is permitted. Implements @ref ether_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to ETHER control block or configuration structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN                    Control block has already been opened or channel is being used by another
 *                                                  instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION   Initialization of PHY-LSI failed.
 * @retval  FSP_ERR_INVALID_CHANNEL                 Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_POINTER                 Pointer to extend config structure or MAC address is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                Interrupt is not enabled.
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK            Initialization of PHY-LSI failed.
 **********************************************************************************************************************/
fsp_err_t R_RMAC_Open (ether_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg)
{
    fsp_err_t                       err             = FSP_SUCCESS;
    rmac_instance_ctrl_t          * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    rmac_extended_cfg_t           * p_rmac_extended_cfg;
    const ether_switch_instance_t * p_ether_switch;

#if (RMAC_CFG_PARAM_CHECKING_ENABLE)

    /** Check parameters. */
    err = rmac_open_param_check(p_instance_ctrl, p_cfg); /** check arguments */
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);
#endif
    FSP_ERROR_RETURN((RMAC_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);

    p_rmac_extended_cfg = (rmac_extended_cfg_t *) p_cfg->p_extend;
    p_ether_switch      = p_rmac_extended_cfg->p_ether_switch;

    /* Store register addresses. */
    p_instance_ctrl->p_reg_rmac = (R_RMAC0_Type *) (R_RMAC0_BASE + (RMAC_RMAC_REG_SIZE * p_cfg->channel));
    p_instance_ctrl->p_reg_etha =
        (R_ETHA0_Type *) (R_ETHA0_BASE + (RMAC_ETHA_REG_SIZE * p_cfg->channel));

    /* Initialize the flags */
    p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
    p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_NO_CHANGE;
    p_instance_ctrl->previous_link_status  = ETHER_PREVIOUS_LINK_STATUS_DOWN;
    p_instance_ctrl->wake_on_lan           = ETHER_WAKE_ON_LAN_DISABLE;

    /* Initialize configuration of Ethernet module. */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* Open ethernet switch module.  */
    err = p_ether_switch->p_api->open(p_ether_switch->p_ctrl, p_ether_switch->p_cfg);

    /* Already open is acceptable because switch module is common for each RMAC port. */
    if ((FSP_SUCCESS == err) || (FSP_ERR_ALREADY_OPEN == err))
    {
        /* Initialize the Ethernet buffer */
        rmac_init_buffers(p_instance_ctrl);

        /* Create descriptor queues. */
        err = rmac_init_descriptor_queues(p_instance_ctrl);
    }

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->open = RMAC_OPEN;
    }

    return err;
}

/********************************************************************************************************************//**
 * @brief Disables interrupts. Removes power and releases hardware lock. Implements @ref ether_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_Close (ether_ctrl_t * const p_ctrl)
{
    fsp_err_t                err             = FSP_SUCCESS;
    rmac_instance_ctrl_t   * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    rmac_extended_cfg_t    * p_extend;
    layer3_switch_port_cfg_t port_cfg = {0};

#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RMAC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_extend = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Reset port configuration to disable IRQ on the switch. */
    port_cfg.p_callback = NULL;
    R_LAYER3_SWITCH_ConfigurePort(p_extend->p_ether_switch->p_ctrl, p_instance_ctrl->p_cfg->channel, &port_cfg);

    /* Disable IRQ. */
    p_instance_ctrl->p_reg_rmac->MMID2_b.MPDID = 1;
    NVIC_DisableIRQ(p_extend->rmpi_irq);
    R_FSP_IsrContextSet(p_extend->rmpi_irq, NULL);

    /* Initialize the flags */
    p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
    p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_NO_CHANGE;
    p_instance_ctrl->previous_link_status  = ETHER_PREVIOUS_LINK_STATUS_DOWN;

    /** Clear configure block parameters. */
    p_instance_ctrl->p_cfg = NULL;

    /** Mark the channel not open so other APIs cannot use it. */
    p_instance_ctrl->open = 0U;

    return err;
}                                      /* End of function R_RMAC_Close() */

/********************************************************************************************************************//**
 * @brief Move to the next buffer in the circular receive buffer list. Implements @ref ether_api_t::bufferRelease.
 *
 * @retval  FSP_SUCCESS                             Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                        The control block has not been opened
 * @retval  FSP_ERR_ETHER_ERROR_LINK                Auto-negotiation is not completed, and reception is not enabled.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_BufferRelease (ether_ctrl_t * const p_ctrl)
{
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function R_RMAC_BufferRelease() */

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
fsp_err_t R_RMAC_RxBufferUpdate (ether_ctrl_t * const p_ctrl, void * const p_buffer)
{
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_buffer);

    return FSP_ERR_UNSUPPORTED;
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
fsp_err_t R_RMAC_LinkProcess (ether_ctrl_t * const p_ctrl)
{
    fsp_err_t              err             = FSP_SUCCESS;
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    ether_callback_args_t  callback_arg;

    /* Check argument */
#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RMAC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    err = rmac_link_status_check(p_instance_ctrl);

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

    /* When the link is up */
    if (ETHER_LINK_CHANGE_LINK_UP == p_instance_ctrl->link_change)
    {
        p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_NO_CHANGE;
        p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_UP;

        /* Initialize the Ethernet buffer */
        rmac_init_buffers(p_instance_ctrl);

        /* Initialize receive and transmit descriptors */
        rmac_init_descriptors(p_instance_ctrl);

        /* Configure reception filters. */
        rmac_configure_reception_filter(p_instance_ctrl);

        err = rmac_do_link(p_instance_ctrl, LAYER3_SWITCH_MAGIC_PACKET_DETECTION_DISABLE);

        if (FSP_SUCCESS == err)
        {
            /* If a callback is provided, then call it with callback argument. */
            if (NULL != p_instance_ctrl->p_callback)
            {
                callback_arg.channel   = p_instance_ctrl->p_cfg->channel;
                callback_arg.event     = ETHER_EVENT_LINK_ON;
                callback_arg.p_context = p_instance_ctrl->p_cfg->p_context;
                rmac_call_callback(p_instance_ctrl, &callback_arg);
            }
        }
        else
        {
            /* When PHY auto-negotiation is not completed */
            p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
            p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_LINK_UP;
        }
    }
    /* When the link is down */
    else if (ETHER_LINK_CHANGE_LINK_DOWN == p_instance_ctrl->link_change)
    {
        p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_NO_CHANGE;
        p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;

        /* Disable reception. */
        r_rmac_disable_reception(p_instance_ctrl);

        /* If a callback is provided, then call it with callback argument. */
        if (NULL != p_instance_ctrl->p_callback)
        {
            callback_arg.channel   = p_instance_ctrl->p_cfg->channel;
            callback_arg.event     = ETHER_EVENT_LINK_OFF;
            callback_arg.p_context = p_instance_ctrl->p_cfg->p_context;
            rmac_call_callback(p_instance_ctrl, &callback_arg);
        }
    }
    else
    {
        /* no operation */
    }

    return err;
}                                      /* End of function R_RMAC_LinkProcess() */

/********************************************************************************************************************//**
 * @brief The setting of RMAC is changed from normal sending and receiving mode to magic packet detection mode.
 * Implements @ref ether_api_t::wakeOnLANEnable.
 *
 * @retval  FSP_SUCCESS                                 Processing completed successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_ETHER_ERROR_LINK                    Auto-negotiation is not completed, and reception is not enabled.
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                Initialization of PHY-LSI failed.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_WakeOnLANEnable (ether_ctrl_t * const p_ctrl)
{
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    fsp_err_t              err             = FSP_SUCCESS;

    /* Check argument */
#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RMAC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* When the Link up processing is not completed, return error */
    FSP_ERROR_RETURN(ETHER_LINK_ESTABLISH_STATUS_UP == p_instance_ctrl->link_establish_status,
                     FSP_ERR_ETHER_ERROR_LINK);

    /* When the Link up processing is completed */
    /* Change to the magic packet detection mode. */
    rmac_do_link(p_instance_ctrl, LAYER3_SWITCH_MAGIC_PACKET_DETECTION_ENABLE);

    /* It is confirmed not to become Link down while changing the setting. */
    err = rmac_link_status_check(p_instance_ctrl);

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->wake_on_lan = ETHER_WAKE_ON_LAN_ENABLE;
    }
    else
    {
        err = FSP_ERR_ETHER_ERROR_LINK;
    }

    return err;
}                                      /* End of function R_RMAC_WakeOnLANEnable() */

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
 * @retval  FSP_ERR_ETHER_ERROR_FILTERING               Multicast Frame filter is enable, and Multicast Address Frame is
 *                                                      received.
 * @retval  FSP_ERR_INVALID_POINTER                     Value of the pointer is NULL.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_Read (ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes)
{
    fsp_err_t              err             = FSP_SUCCESS;
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    uint8_t              * p_read_buffer   = NULL; /* Buffer location controlled by the Ethernet driver */
    uint64_t               buffer_address;
    uint32_t               received_size = RMAC_NO_DATA;

    layer3_switch_descriptor_t descriptor;
    rmac_extended_cfg_t      * p_extend;

    /* Check argument */
#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RMAC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_buffer, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != length_bytes, FSP_ERR_INVALID_POINTER);
#endif

    p_extend = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* (1) Retrieve the receive buffer location controlled by the  descriptor. */
    /* When the Link up processing is not completed, return error */
    FSP_ERROR_RETURN(ETHER_LINK_ESTABLISH_STATUS_UP == p_instance_ctrl->link_establish_status,
                     FSP_ERR_ETHER_ERROR_LINK);

    err =
        R_LAYER3_SWITCH_GetDescriptor(p_extend->p_ether_switch->p_ctrl,
                                      p_extend->p_rx_queue_list[p_instance_ctrl->read_queue_index].index, &descriptor);

    /* When receive data exists. */
    if (FSP_SUCCESS == err)
    {
        /**
         * Pass the pointer to received data to application.  This is
         * zero-copy operation.
         */
        buffer_address  = (uint64_t) (descriptor.basic.ptr_h) << RMAC_DESCRIPTOR_FIELD_PTR_UPPER_POSITION;
        buffer_address += descriptor.basic.ptr_l;
        p_read_buffer   = (void *) (uintptr_t) buffer_address;

        /* Get bytes received */
        received_size =
            (uint32_t) ((descriptor.basic.ds_h << RMAC_DESCRIPTOR_FIELD_DS_UPPER_POSITION) + descriptor.basic.ds_l);
    }

    /* When there is data to receive */
    if (received_size > RMAC_NO_DATA)
    {
        /* (2) Copy the data read from the receive buffer which is controlled
         *     by the descriptor to the buffer which is specified by the user (up to 1024 bytes). */
        memcpy(p_buffer, p_read_buffer, received_size);

        /* (3) Read the receive data from the receive buffer controlled by the descriptor,
         * and then release the receive buffer. */

        err = r_rmac_reset_rx_descriptor(p_instance_ctrl, p_read_buffer);

        *length_bytes = received_size;
    }
    /* When there is no data to receive */
    else
    {
        err = FSP_ERR_ETHER_ERROR_NO_DATA;
    }

    return err;
}                                      /* End of function R_RMAC_Read() */

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
 * @retval  FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL    Transmit buffer is not empty.
 * @retval  FSP_ERR_INVALID_POINTER                     Value of the pointer is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Value of the send frame size is out of range.
 *
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_Write (ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length)
{
    fsp_err_t              err             = FSP_SUCCESS;
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    rmac_extended_cfg_t  * p_extend;

    uint8_t * p_write_buffer;
    layer3_switch_descriptor_t descriptor;
    uint64_t buffer_address;

    /* Check argument */
#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RMAC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_buffer, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN((RMAC_MINIMUM_FRAME_SIZE <= frame_length) && (RMAC_MAXIMUM_FRAME_SIZE >= frame_length),
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_instance_ctrl->p_cfg->ether_buffer_size >= frame_length, FSP_ERR_OVERFLOW);
#endif

    p_extend = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* When the Link up processing is not completed, return error */
    FSP_ERROR_RETURN(ETHER_LINK_ESTABLISH_STATUS_UP == p_instance_ctrl->link_establish_status,
                     FSP_ERR_ETHER_ERROR_LINK);

    err =
        R_LAYER3_SWITCH_GetDescriptor(p_extend->p_ether_switch->p_ctrl,
                                      p_extend->p_tx_queue_list[p_instance_ctrl->write_queue_index].index, &descriptor);

    /* When target queue is full, use a next one. */
    if ((FSP_ERR_NOT_INITIALIZED == err) || (NULL == (void *) descriptor.basic.ptr_l))
    {
        RMAC_INCREMENT_INDEX(p_instance_ctrl->write_queue_index, p_extend->tx_queue_num);
        err =
            R_LAYER3_SWITCH_GetDescriptor(p_extend->p_ether_switch->p_ctrl,
                                          p_extend->p_tx_queue_list[p_instance_ctrl->write_queue_index].index,
                                          &descriptor);
    }

    /* Retrieve the transmit buffer location controlled by the  descriptor. */
    if (FSP_SUCCESS == err)
    {
        /* Get buffer address. */
        buffer_address  = (uint64_t) (descriptor.basic.ptr_h) << RMAC_DESCRIPTOR_FIELD_PTR_UPPER_POSITION;
        buffer_address += descriptor.basic.ptr_l;

        p_write_buffer = (void *) (uintptr_t) buffer_address;

        /* Write the data to the transmit buffer that controlled by the  descriptor. */
        memcpy(p_write_buffer, p_buffer, frame_length);

        /* Configure transmission descriptor. */
        descriptor.basic.ds_h = (RMAC_DESCRIPTOR_FIELD_DS_UPPER_MASK & frame_length) >>
                                RMAC_DESCRIPTOR_FIELD_DS_UPPER_POSITION;
        descriptor.basic.ds_l = RMAC_DESCRIPTOR_FIELD_DS_LOWER_MASK & frame_length;
        descriptor.basic.dt   = LAYER3_SWITCH_DESCRIPTOR_TYPE_FSINGLE;

        R_LAYER3_SWITCH_SetDescriptor(p_extend->p_ether_switch->p_ctrl,
                                      p_extend->p_tx_queue_list[p_instance_ctrl->write_queue_index].index, &descriptor);

        /* Check if any TX queue is running. */
        if (p_instance_ctrl->tx_running_queue_index != RMAC_INVALID_QUEUE_INDEX)
        {
            /* Pending this data until the complete transmission of other queues. */
            p_instance_ctrl->tx_pending_queue_map |= p_instance_ctrl->write_queue_index;
        }
        else
        {
            /* When all TX queues are stopped, start transmission. */
            p_instance_ctrl->tx_running_queue_index = p_instance_ctrl->write_queue_index;
            R_LAYER3_SWITCH_StartDescriptorQueue(p_extend->p_ether_switch->p_ctrl,
                                                 p_extend->p_tx_queue_list[p_instance_ctrl->tx_running_queue_index].index);

            /* Update the queue that used to next write operation. */
            RMAC_INCREMENT_INDEX(p_instance_ctrl->write_queue_index, p_extend->tx_queue_num);
        }
    }
    else
    {
        err = FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL; /* Transmit buffer overflow */
    }

    return err;
}                                                       /* End of function R_RMAC_Write() */

/**********************************************************************************************************************//**
 * Provides status of Ethernet driver in the user provided pointer. Implements @ref ether_api_t::txStatusGet.
 *
 * @retval  FSP_SUCCESS                  Transmit buffer address is stored in provided p_buffer_address.
 * @retval  FSP_ERR_ASSERTION            Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      p_status is NULL.
 * @retval  FSP_ERR_NOT_FOUND            Transmit buffer address has been overwritten in transmit descriptor.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_TxStatusGet (ether_ctrl_t * const p_ctrl, void * const p_buffer_address)
{
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_buffer_address);

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function R_RMAC_VersionGet() */

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref ether_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_RMAC_CallbackSet (ether_ctrl_t * const          p_api_ctrl,
                              void (                      * p_callback)(ether_callback_args_t *),
                              void * const                  p_context,
                              ether_callback_args_t * const p_callback_memory)
{
    rmac_instance_ctrl_t * p_ctrl = (rmac_instance_ctrl_t *) p_api_ctrl;

    /* Check argument */
#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(RMAC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD && BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if RMAC_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    ether_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                        CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD && BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(ether_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RMAC)
 **********************************************************************************************************************/

#if (RMAC_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * @brief Parameter error check function for open.
 *
 * @param[in] p_instance_ctrl   Pointer to the control block for the channel
 * @param[in] p_cfg             Pointer to the configuration structure specific to UART mode
 *
 * @retval  FSP_SUCCESS                  No parameter error found
 * @retval  FSP_ERR_ASSERTION            Pointer to RMAC control block or configuration structure is NULL
 * @retval  FSP_ERR_INVALID_CHANNEL      Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to MAC address is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Irq number lower then 0.
 **********************************************************************************************************************/
static fsp_err_t rmac_open_param_check (rmac_instance_ctrl_t const * const p_instance_ctrl,
                                        ether_cfg_t const * const          p_cfg)
{
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_cfg->p_mac_address, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_cfg->p_extend, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BSP_FEATURE_ETHER_MAX_CHANNELS > p_cfg->channel, FSP_ERR_INVALID_CHANNEL);

    /* RMAC does not support padding feature. */
    FSP_ERROR_RETURN(p_cfg->padding == ETHER_PADDING_DISABLE, FSP_ERR_UNSUPPORTED);

    /* Zerocopy mode is not support now. */
    FSP_ERROR_RETURN(p_cfg->zerocopy == ETHER_ZEROCOPY_DISABLE, FSP_ERR_UNSUPPORTED);

    return FSP_SUCCESS;
}

#endif

/***********************************************************************************************************************
 * Function Name: rmac_configure_reception_filter
 * Description  : Configure the ETHA and RMAC feature.
 * Arguments    : channel -
 *                    RMAC channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void rmac_configure_reception_filter (rmac_instance_ctrl_t const * const p_instance_ctrl)
{
    uint32_t mrafc = p_instance_ctrl->p_reg_rmac->MRAFC;

    if (ETHER_PROMISCUOUS_ENABLE == p_instance_ctrl->p_cfg->promiscuous)
    {
        /* Enable promiscuous reception. */
        mrafc = RMAC_REG_MRAFC_PROMISCUOUS_VALUE;
    }
    else
    {
        /* Configure multicast reception features. */
        if (ETHER_MULTICAST_ENABLE == p_instance_ctrl->p_cfg->multicast)
        {
            /* Enable multicast reception. */
            mrafc |= R_RMAC0_MRAFC_MCENE_Msk | R_RMAC0_MRAFC_MCENP_Msk;
        }
        else
        {
            mrafc &= ~(R_RMAC0_MRAFC_MCENE_Msk | R_RMAC0_MRAFC_MCENP_Msk);
        }

        /* Configure broadcast reception features. */
        if (0 < p_instance_ctrl->p_cfg->broadcast_filter)
        {
            /* Enable broadcast reception. */
            mrafc |= R_RMAC0_MRAFC_BCENE_Msk | R_RMAC0_MRAFC_BCENP_Msk;
        }
        else
        {
            mrafc &=
                ~(R_RMAC0_MRAFC_BCENE_Msk | R_RMAC0_MRAFC_BCENP_Msk);
        }
    }

    /* Set the broadcast storm filter regardless of the promiscuous mode configuration. */
    if (0 < p_instance_ctrl->p_cfg->broadcast_filter)
    {
        /* Enable the broadcast storm filter */
        mrafc |= R_RMAC0_MRAFC_BCACE_Msk | R_RMAC0_MRAFC_BSTENE_Msk |
                 R_RMAC0_MRAFC_BSTENP_Msk | R_RMAC0_MRAFC_BCACP_Msk;

        /*  Configure how many broadcast frames can be received consecutively. */
        p_instance_ctrl->p_reg_rmac->MRSCE_b.CBFE = (R_RMAC0_MRSCE_CBFE_Msk >> R_RMAC0_MRSCE_CBFE_Pos) &
                                                    (p_instance_ctrl->p_cfg->broadcast_filter - 1);
    }

    p_instance_ctrl->p_reg_rmac->MRAFC = mrafc;
}                                      /* End of function rmac_configure_reception_filter() */

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
static fsp_err_t rmac_do_link (rmac_instance_ctrl_t * const                 p_instance_ctrl,
                               const layer3_switch_magic_packet_detection_t mode)
{
    fsp_err_t err = FSP_SUCCESS;

    rmac_extended_cfg_t          * p_rmac_extended_cfg;
    layer3_switch_extended_cfg_t * p_switch_extended_cfg;
    const ether_phy_instance_t   * p_phy_instance;

    layer3_switch_port_cfg_t port_cfg;
    uint32_t                 link_speed_duplex  = 0;
    uint32_t                 local_pause_bits   = 0;
    uint32_t                 partner_pause_bits = 0;
    fsp_err_t                link_result;

#if (RMAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RMAC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_rmac_extended_cfg   = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    p_switch_extended_cfg = (layer3_switch_extended_cfg_t *) p_rmac_extended_cfg->p_ether_switch->p_cfg->p_extend;
    p_phy_instance        =
        (ether_phy_instance_t *) p_switch_extended_cfg->p_ether_phy_instances[p_instance_ctrl->p_cfg->channel];

    /* Set the link status */
    R_RMAC_PHY_ChipSelect(p_phy_instance->p_ctrl, p_instance_ctrl->p_cfg->channel);
    link_result = p_phy_instance->p_api->linkPartnerAbilityGet(p_phy_instance->p_ctrl,
                                                               &link_speed_duplex,
                                                               &local_pause_bits,
                                                               &partner_pause_bits);

    if (FSP_SUCCESS == link_result)
    {
        /* Set MAC address. */
        port_cfg.p_mac_address = p_instance_ctrl->p_cfg->p_mac_address;

        if (LAYER3_SWITCH_MAGIC_PACKET_DETECTION_DISABLE == mode)
        {
            /*
             * To prevent reception from starting at an invalid descriptor, the queue must be reloaded first.
             * Until then, reception is kept disabled.
             */
            port_cfg.forwarding_to_cpu_enable = false;
            R_LAYER3_SWITCH_ConfigurePort(p_rmac_extended_cfg->p_ether_switch->p_ctrl,
                                          p_instance_ctrl->p_cfg->channel,
                                          &port_cfg);

            /* Reload RX queue. */
            p_instance_ctrl->rx_running_queue_index = 0;
            err = R_LAYER3_SWITCH_StartDescriptorQueue(p_rmac_extended_cfg->p_ether_switch->p_ctrl,
                                                       p_rmac_extended_cfg->p_rx_queue_list[0].index);

            /* Set callback for switch data interrupt. */
            port_cfg.p_callback        = r_rmac_switch_interrupt_callback;
            port_cfg.p_context         = p_instance_ctrl;
            port_cfg.p_callback_memory = NULL;

            /* Enable reception. */
            port_cfg.forwarding_to_cpu_enable = true;
            R_LAYER3_SWITCH_ConfigurePort(p_rmac_extended_cfg->p_ether_switch->p_ctrl,
                                          p_instance_ctrl->p_cfg->channel,
                                          &port_cfg);
        }
        else
        {
            /* Disable reception. */
            r_rmac_disable_reception(p_instance_ctrl);

            /* Enable a magic packet interrupt. */
            R_BSP_IrqCfgEnable(p_rmac_extended_cfg->rmpi_irq, p_rmac_extended_cfg->rmpi_ipl, p_instance_ctrl);
            p_instance_ctrl->p_reg_rmac->MMIE2_b.MPDIE = 1;
        }
    }
    else
    {
        err = FSP_ERR_ETHER_ERROR_LINK;
    }

    return err;
}                                      /* End of function rmac_do_link() */

/*******************************************************************************************************************//**
 * @brief Verifies the Ethernet link is up or not.
 *
 * @param[in] p_instance_ctrl   Pointer to the control block for the channel
 *
 * @retval  FSP_SUCCESS:                  Link is up
 * @retval  FSP_ERR_ETHER_ERROR_LINK:     Link is down
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK  Initialization of PHY-LSI failed.
 **********************************************************************************************************************/
static fsp_err_t rmac_link_status_check (rmac_instance_ctrl_t const * const p_instance_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    fsp_err_t link_status;

    rmac_extended_cfg_t          * p_rmac_extended_cfg;
    layer3_switch_extended_cfg_t * p_switch_extended_cfg;
    const ether_phy_instance_t   * p_phy_instance;

    p_rmac_extended_cfg   = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    p_switch_extended_cfg = (layer3_switch_extended_cfg_t *) p_rmac_extended_cfg->p_ether_switch->p_cfg->p_extend;
    p_phy_instance        =
        (ether_phy_instance_t *) p_switch_extended_cfg->p_ether_phy_instances[p_instance_ctrl->p_cfg->channel];

    /* Update PHY LSI information */
    R_RMAC_PHY_ChipSelect(p_phy_instance->p_ctrl, p_instance_ctrl->p_cfg->channel);

    /* Get link status */
    link_status = p_phy_instance->p_api->linkStatusGet(p_phy_instance->p_ctrl);

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
}                                      /* End of function rmac_link_status_check() */

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_instance_ctrl      Pointer to ether instance control block
 * @param[in]     p_callback_args      Pointer to callback args
 **********************************************************************************************************************/
static void rmac_call_callback (rmac_instance_ctrl_t * p_instance_ctrl, ether_callback_args_t * p_callback_args)
{
    ether_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    ether_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->event     = p_callback_args->event;
    p_args->channel   = p_instance_ctrl->p_cfg->channel;
    p_args->p_context = p_instance_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD && BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_instance_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_instance_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        ether_prv_ns_callback p_callback = (ether_prv_ns_callback) (p_instance_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_instance_ctrl->p_callback(p_args);
#endif

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }
}

/***********************************************************************************************************************
 * Function Name: rmac_init_descriptors
 * Description  : Initialize descriptors and set buffers to these.
 * Arguments    : channel -
 *                    RMAC channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void rmac_init_descriptors (rmac_instance_ctrl_t * const p_instance_ctrl)
{
    layer3_switch_descriptor_t descriptor = {0};

    rmac_extended_cfg_t * p_extend = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint32_t              buffers_index;

    /* Enable Data interrupt for RX and TX descriptor. */
    descriptor.basic.die = 1;

    /* Initialize descriptors of each RX queue if buffers are allocated by configuration. */
    if (NULL != p_instance_ctrl->p_cfg->pp_ether_buffers)
    {
        /* Settings for RX descriptors */
        descriptor.basic.ds_h = (RMAC_DESCRIPTOR_FIELD_DS_UPPER_MASK & RMAC_MAXIMUM_FRAME_SIZE) >>
                                RMAC_DESCRIPTOR_FIELD_DS_UPPER_POSITION;
        descriptor.basic.ds_l = RMAC_DESCRIPTOR_FIELD_DS_LOWER_MASK & RMAC_MAXIMUM_FRAME_SIZE;
        descriptor.basic.dt   = LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY;

        for (uint32_t i = 0; i < p_extend->rx_queue_num; i++)
        {
            /* For each RX descriptor exclude the last. */
            for (uint32_t j = 0; j < p_extend->p_rx_queue_list[i].queue_cfg.array_length - 1; j++)
            {
                /* Initialize buffer address. */
                buffers_index          = i * (p_extend->p_rx_queue_list[i].queue_cfg.array_length - 1) + j;
                descriptor.basic.ptr_h =
                    (RMAC_DESCRIPTOR_FIELD_PTR_UPPER_MASK &
                     (uint64_t) (uintptr_t) p_instance_ctrl->p_cfg->pp_ether_buffers[buffers_index]) >>
                    RMAC_DESCRIPTOR_FIELD_PTR_UPPER_POSITION;
                descriptor.basic.ptr_l = RMAC_DESCRIPTOR_FIELD_PTR_LOWER_MASK &
                                         (uintptr_t) p_instance_ctrl->p_cfg->pp_ether_buffers[buffers_index];

                /* Set data to descriptor. */
                R_LAYER3_SWITCH_SetDescriptor(p_extend->p_ether_switch->p_ctrl,
                                              p_extend->p_rx_queue_list[i].index,
                                              &descriptor);
            }
        }
    }

    /* Initialize variables that used for RX. */
    p_instance_ctrl->read_queue_index          = 0;
    p_instance_ctrl->rx_reset_descriptor_count = 0;
    p_instance_ctrl->rx_running_queue_index    = RMAC_INVALID_QUEUE_INDEX;

    /* The running queue is assumed to be non-empty. */
    p_instance_ctrl->rx_pending_queue_map = 1;

    /* Settings for TX descriptors */
    /* Set output port. */
    descriptor.info1_tx.dv  = RMAC_DESCRIPTOR_FIELD_DV_MASK & (1 << p_instance_ctrl->p_cfg->channel);
    descriptor.info1_tx.fmt = 1;

    /*  Set descriptor type as no data. */
    descriptor.basic.dt = LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY;

    /* Initialize descriptors of each TX queue */
    for (uint32_t i = 0; i < p_extend->tx_queue_num; i++)
    {
        /* For each TX descriptor exclude the last. */
        for (uint32_t j = 0; j < p_extend->p_tx_queue_list[i].queue_cfg.array_length - 1; j++)
        {
            if (NULL != p_instance_ctrl->p_cfg->pp_ether_buffers)
            {
                /* Initialize buffer address. */
                buffers_index = i * (p_extend->p_tx_queue_list[i].queue_cfg.array_length - 1) + j +
                                p_instance_ctrl->p_cfg->num_rx_descriptors;
                descriptor.basic.ptr_l = (uintptr_t) p_instance_ctrl->p_cfg->pp_ether_buffers[buffers_index];

                /* Set data to descriptor. */
                R_LAYER3_SWITCH_SetDescriptor(p_extend->p_ether_switch->p_ctrl,
                                              p_extend->p_tx_queue_list[i].index,
                                              &descriptor);
            }
        }

        /* Performing a null transmission to initialize the TX queue.  */
        R_LAYER3_SWITCH_StartDescriptorQueue(p_extend->p_ether_switch->p_ctrl, p_extend->p_tx_queue_list[i].index);
    }

    /* Initialize application transmission queue index. */
    p_instance_ctrl->write_queue_index      = 0;
    p_instance_ctrl->tx_running_queue_index = RMAC_INVALID_QUEUE_INDEX;
    p_instance_ctrl->tx_pending_queue_map   = 0;
}                                      /* End of function ether_init_descriptors() */

/***********************************************************************************************************************
 * Function Name: rmac_init_buffers
 * Description  : The driver buffers are initialized.
 * Arguments    : p_instance_ctrl -
 *                    RMAC control block.
 * Return Value : none
 ***********************************************************************************************************************/
static void rmac_init_buffers (rmac_instance_ctrl_t * const p_instance_ctrl)
{
    uint32_t i;
    uint32_t buffer_num;

    if (NULL != p_instance_ctrl->p_cfg->pp_ether_buffers)
    {
        if (ETHER_ZEROCOPY_DISABLE == p_instance_ctrl->p_cfg->zerocopy)
        {
            buffer_num =
                (uint32_t) (p_instance_ctrl->p_cfg->num_tx_descriptors +
                            p_instance_ctrl->p_cfg->num_rx_descriptors);
        }
        else
        {
            buffer_num = (uint32_t) p_instance_ctrl->p_cfg->num_rx_descriptors;
        }

        for (i = 0; i < buffer_num; i++)
        {
            memset(p_instance_ctrl->p_cfg->pp_ether_buffers[i], 0x00, p_instance_ctrl->p_cfg->ether_buffer_size);
        }
    }
}                                      /* End of function rmac_init_buffers() */

static fsp_err_t rmac_init_descriptor_queues (rmac_instance_ctrl_t * const p_instance_ctrl)
{
    rmac_extended_cfg_t * p_extend = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    fsp_err_t             err      = FSP_SUCCESS;

    /* Initialize TX queues. */
    for (uint32_t i = 0; i < p_extend->tx_queue_num; i++)
    {
        err = R_LAYER3_SWITCH_CreateDescriptorQueue(p_extend->p_ether_switch->p_ctrl,
                                                    &p_extend->p_tx_queue_list[i].index,
                                                    &p_extend->p_tx_queue_list[i].queue_cfg);
        if (FSP_SUCCESS != err)
        {
            break;
        }
    }

    if (FSP_SUCCESS == err)
    {
        /* Initialize RX queues. */
        for (uint32_t i = 0; i < p_extend->rx_queue_num; i++)
        {
            err = R_LAYER3_SWITCH_CreateDescriptorQueue(p_extend->p_ether_switch->p_ctrl,
                                                        &p_extend->p_rx_queue_list[i].index,
                                                        &p_extend->p_rx_queue_list[i].queue_cfg);
            if (FSP_SUCCESS != err)
            {
                break;
            }
        }
    }

    return err;
}

static fsp_err_t r_rmac_reset_rx_descriptor (rmac_instance_ctrl_t * p_instance_ctrl, void * p_buffer)
{
    rmac_extended_cfg_t      * p_extend = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    layer3_switch_descriptor_t descriptor;
    fsp_err_t err;

    /* Reset descriptor as waiting for reception.  */
    descriptor.basic.err  = 0;
    descriptor.basic.ds_h = (RMAC_DESCRIPTOR_FIELD_DS_UPPER_MASK & RMAC_MAXIMUM_FRAME_SIZE) >>
                            RMAC_DESCRIPTOR_FIELD_DS_UPPER_POSITION;
    descriptor.basic.ds_l  = RMAC_DESCRIPTOR_FIELD_DS_LOWER_MASK & RMAC_MAXIMUM_FRAME_SIZE;
    descriptor.basic.dt    = LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY;
    descriptor.basic.ptr_h =
        (RMAC_DESCRIPTOR_FIELD_PTR_UPPER_MASK & (uint64_t) (uintptr_t) p_buffer) >>
        RMAC_DESCRIPTOR_FIELD_PTR_UPPER_POSITION;
    descriptor.basic.ptr_l = RMAC_DESCRIPTOR_FIELD_PTR_LOWER_MASK & (uintptr_t) p_buffer;

    /* Enable Data interrupt for RX and TX descriptor. */
    descriptor.basic.die = 1;

    err =
        R_LAYER3_SWITCH_SetDescriptor(p_extend->p_ether_switch->p_ctrl,
                                      p_extend->p_rx_queue_list[p_instance_ctrl->read_queue_index].index, &descriptor);

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->rx_reset_descriptor_count += 1;
    }

    /* When all descriptors in the queue are reset. */
    if ((p_extend->p_rx_queue_list[p_instance_ctrl->read_queue_index].queue_cfg.array_length - 1 ==
         p_instance_ctrl->rx_reset_descriptor_count))
    {
        if (RMAC_INVALID_QUEUE_INDEX == p_instance_ctrl->rx_running_queue_index)
        {
            /* If any RX queue is not running, restart this queue. */
            p_instance_ctrl->rx_running_queue_index = p_instance_ctrl->read_queue_index;
            err =
                R_LAYER3_SWITCH_StartDescriptorQueue(p_extend->p_ether_switch->p_ctrl,
                                                     p_extend->p_rx_queue_list[p_instance_ctrl->rx_running_queue_index].index);
        }
        else
        {
            /* Clear pending queue bitmap for this reading queue. */
            p_instance_ctrl->rx_pending_queue_map &= ~(uint32_t) (1 << p_instance_ctrl->read_queue_index);
        }

        /* Update the queue index that used for next Read(). */
        RMAC_INCREMENT_INDEX(p_instance_ctrl->read_queue_index, p_extend->rx_queue_num);
        p_instance_ctrl->rx_reset_descriptor_count = 0;
    }

    return err;
}

/*******************************************************************************************************************
 * Disable reception on this port.
 **********************************************************************************************************************/
static void r_rmac_disable_reception (rmac_instance_ctrl_t * p_instance_ctrl)
{
    rmac_extended_cfg_t      * p_extend           = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    layer3_switch_port_cfg_t   port_cfg           = {0};
    layer3_switch_descriptor_t descriptor         = {0};
    rmac_queue_info_t          running_queue_info = p_extend->p_rx_queue_list[p_instance_ctrl->rx_running_queue_index];

    /* When magic packet detection is enabled, disable data interrupt. */
    port_cfg.p_callback = NULL;

    /* Disable CPU reception from this port. */
    port_cfg.forwarding_to_cpu_enable = false;
    R_LAYER3_SWITCH_ConfigurePort(p_extend->p_ether_switch->p_ctrl, p_instance_ctrl->p_cfg->channel, &port_cfg);

    /* Set descriptors in RX running queue to stop state. */
    descriptor.basic.dt = LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY;
    for (size_t i = 0; i < running_queue_info.queue_cfg.array_length; i++)
    {
        R_LAYER3_SWITCH_SetDescriptor(p_extend->p_ether_switch->p_ctrl, running_queue_info.index, &descriptor);
    }

    /* Perform starting reception to initialize queue status. */
    R_LAYER3_SWITCH_StartDescriptorQueue(p_extend->p_ether_switch->p_ctrl, running_queue_info.index);
}

/***********************************************************************************************************************
 * Function Name: r_rmac_switch_interrupt_callback
 * Description  : Callback for RX/TX data interrupts. This function set to switch module callback.
 ***********************************************************************************************************************/
static void r_rmac_switch_interrupt_callback (ether_switch_callback_args_t * p_args)
{
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) p_args->p_context;
    rmac_extended_cfg_t  * p_extend        = (rmac_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    ether_callback_args_t  callback_args   = {0};
    uint32_t               next_running_queue_index;

    switch (p_args->event)
    {
        case ETHER_SWITCH_EVENT_TX_COMPLETE:
        {
            callback_args.event = ETHER_EVENT_TX_COMPLETE;

            /* Finish transmission on the queue. */
            p_instance_ctrl->tx_pending_queue_map &= ~(uint32_t) (1 << p_instance_ctrl->tx_running_queue_index);

            next_running_queue_index = p_instance_ctrl->tx_running_queue_index;
            RMAC_INCREMENT_INDEX(next_running_queue_index, p_extend->tx_queue_num);

            /* Check if pending data exists on a next TX queue. */
            if (0 != (p_instance_ctrl->tx_pending_queue_map & (1 << next_running_queue_index)))
            {
                /* When pending TX data exits, start the next queue. */
                p_instance_ctrl->tx_running_queue_index = next_running_queue_index;
                R_LAYER3_SWITCH_StartDescriptorQueue(p_extend->p_ether_switch->p_ctrl,
                                                     p_extend->p_tx_queue_list[next_running_queue_index].index);

                /* Update internal variables. */
                RMAC_INCREMENT_INDEX(p_instance_ctrl->write_queue_index, p_extend->tx_queue_num);
            }
            else
            {
                p_instance_ctrl->tx_running_queue_index = RMAC_INVALID_QUEUE_INDEX;
            }

            break;
        }

        case ETHER_SWITCH_EVENT_RX_COMPLETE:
        {
            callback_args.event = ETHER_EVENT_RX_COMPLETE;
            break;
        }

        case ETHER_SWITCH_EVENT_RX_QUEUE_FULL:
        {
            callback_args.event = ETHER_EVENT_RX_COMPLETE;

            if (p_args->queue_index != p_extend->p_rx_queue_list[p_instance_ctrl->rx_running_queue_index].index)
            {
                /* If the queue raising this interrupt is not the same as the currently running queue, no RX queue switch is needed. */
                break;
            }

            next_running_queue_index = p_instance_ctrl->rx_running_queue_index;
            RMAC_INCREMENT_INDEX(next_running_queue_index, p_extend->rx_queue_num);

            /* When next queue is empty. */
            if (0 == (p_instance_ctrl->rx_pending_queue_map & (1 << next_running_queue_index)))
            {
                /* Start reception on next queue. */
                p_instance_ctrl->rx_running_queue_index = next_running_queue_index;
                R_LAYER3_SWITCH_StartDescriptorQueue(p_extend->p_ether_switch->p_ctrl,
                                                     p_extend->p_rx_queue_list[next_running_queue_index].index);

                /* The running queue is assumed to have data. */
                p_instance_ctrl->rx_pending_queue_map |= (1 << next_running_queue_index);
            }
            else
            {
                /* Stop reception if the next queue is not empty. */
                p_instance_ctrl->rx_running_queue_index = RMAC_INVALID_QUEUE_INDEX;
            }

            break;
        }

        case ETHER_SWITCH_EVENT_RX_MESSAGE_LOST:
        {
            callback_args.event = ETHER_EVENT_RX_MESSAGE_LOST;
            break;
        }

        default:
        {
            break;
        }
    }

    if (NULL != p_instance_ctrl->p_callback)
    {
        rmac_call_callback(p_instance_ctrl, &callback_args);
    }
}

/***********************************************************************************************************************
 * Function Name: rmac_rmpi_isr
 * Description  : Interrupt handler for RMPI interrupts.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void rmac_rmpi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    ether_callback_args_t callback_arg;
    uint32_t              status_rmpi;

    IRQn_Type              irq             = R_FSP_CurrentIrqGet();
    rmac_instance_ctrl_t * p_instance_ctrl = (rmac_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    status_rmpi = p_instance_ctrl->p_reg_rmac->MMIS2;

    /* When the Magic Packet detection interrupt is generated */
    if (status_rmpi & R_RMAC0_MMIS2_MPDIS_Msk)
    {
        /* Disable the interrupt of Magic packet detection. */
        p_instance_ctrl->p_reg_rmac->MMID2_b.MPDID = 1;

        /* If a callback is provided, then call it with callback argument. */
        if (NULL != p_instance_ctrl->p_callback)
        {
            callback_arg.channel   = p_instance_ctrl->p_cfg->channel;
            callback_arg.event     = ETHER_EVENT_WAKEON_LAN;
            callback_arg.p_context = p_instance_ctrl->p_cfg->p_context;
            rmac_call_callback(p_instance_ctrl, &callback_arg);
        }

        if (ETHER_WAKE_ON_LAN_ENABLE == p_instance_ctrl->wake_on_lan)
        {
            /* Initialize the link status. */
            p_instance_ctrl->link_establish_status = ETHER_LINK_ESTABLISH_STATUS_DOWN;
            p_instance_ctrl->link_change           = ETHER_LINK_CHANGE_NO_CHANGE;
            p_instance_ctrl->previous_link_status  = ETHER_PREVIOUS_LINK_STATUS_DOWN;

            /*
             * Call LinkProcess to initialize descriptors and resume reception.
             * If the link is down, it need to call LinkProcess again after this interrput.
             */
            R_RMAC_LinkProcess(p_instance_ctrl);
        }
    }

    /* Clear RMPI status bit. */
    p_instance_ctrl->p_reg_rmac->MMIS2 = status_rmpi; /* Clear all ETHERC status BFR, PSRTO, LCHNG, MPD, ICD */

    /* Clear pending interrupt flag to make sure it doesn't fire again
     * after exiting. */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}                                      /* End of function rmac_rmpi_isr() */
