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

/* Access to peripherals and board defines. */
#include "bsp_api.h"
#include "r_ether_phy.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

#ifndef ETHER_PHY_ERROR_RETURN

 #define ETHER_PHY_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

#define ETHERC_REG_SIZE                         (0x400UL)

/** "RPHY" in ASCII.  Used to determine if the control block is open. */
#define ETHER_PHY_OPEN                          (0x52504859U)

/* Media Independent Interface */
#define ETHER_PHY_MII_ST                        (1)
#define ETHER_PHY_MII_READ                      (2)
#define ETHER_PHY_MII_WRITE                     (1)

/* Standard PHY Registers */
#define ETHER_PHY_REG_CONTROL                   (0)
#define ETHER_PHY_REG_STATUS                    (1)
#define ETHER_PHY_REG_IDENTIFIER1               (2)
#define ETHER_PHY_REG_IDENTIFIER2               (3)
#define ETHER_PHY_REG_AN_ADVERTISEMENT          (4)
#define ETHER_PHY_REG_AN_LINK_PARTNER           (5)
#define ETHER_PHY_REG_AN_EXPANSION              (6)

/* Basic Mode Control Register Bit Definitions */
#define ETHER_PHY_CONTROL_RESET                 (1 << 15)
#define ETHER_PHY_CONTROL_LOOPBACK              (1 << 14)
#define ETHER_PHY_CONTROL_100_MBPS              (1 << 13)
#define ETHER_PHY_CONTROL_AN_ENABLE             (1 << 12)
#define ETHER_PHY_CONTROL_POWER_DOWN            (1 << 11)
#define ETHER_PHY_CONTROL_ISOLATE               (1 << 10)
#define ETHER_PHY_CONTROL_AN_RESTART            (1 << 9)
#define ETHER_PHY_CONTROL_FULL_DUPLEX           (1 << 8)
#define ETHER_PHY_CONTROL_COLLISION             (1 << 7)

/* Basic Mode Status Register Bit Definitions */
#define ETHER_PHY_STATUS_100_T4                 (1 << 15)
#define ETHER_PHY_STATUS_100F                   (1 << 14)
#define ETHER_PHY_STATUS_100H                   (1 << 13)
#define ETHER_PHY_STATUS_10F                    (1 << 12)
#define ETHER_PHY_STATUS_10H                    (1 << 11)
#define ETHER_PHY_STATUS_AN_COMPLETE            (1 << 5)
#define ETHER_PHY_STATUS_RM_FAULT               (1 << 4)
#define ETHER_PHY_STATUS_AN_ABILITY             (1 << 3)
#define ETHER_PHY_STATUS_LINK_UP                (1 << 2)
#define ETHER_PHY_STATUS_JABBER                 (1 << 1)
#define ETHER_PHY_STATUS_EX_CAPABILITY          (1 << 0)

/* Auto Negotiation Advertisement Bit Definitions */
#define ETHER_PHY_AN_ADVERTISEMENT_NEXT_PAGE    (1 << 15)
#define ETHER_PHY_AN_ADVERTISEMENT_RM_FAULT     (1 << 13)
#define ETHER_PHY_AN_ADVERTISEMENT_ASM_DIR      (1 << 11)
#define ETHER_PHY_AN_ADVERTISEMENT_PAUSE        (1 << 10)
#define ETHER_PHY_AN_ADVERTISEMENT_100_T4       (1 << 9)
#define ETHER_PHY_AN_ADVERTISEMENT_100F         (1 << 8)
#define ETHER_PHY_AN_ADVERTISEMENT_100H         (1 << 7)
#define ETHER_PHY_AN_ADVERTISEMENT_10F          (1 << 6)
#define ETHER_PHY_AN_ADVERTISEMENT_10H          (1 << 5)
#define ETHER_PHY_AN_ADVERTISEMENT_SELECTOR     (1 << 0)

/* Auto Negotiate Link Partner Ability Bit Definitions */
#define ETHER_PHY_AN_LINK_PARTNER_NEXT_PAGE     (1 << 15)
#define ETHER_PHY_AN_LINK_PARTNER_ACK           (1 << 14)
#define ETHER_PHY_AN_LINK_PARTNER_RM_FAULT      (1 << 13)
#define ETHER_PHY_AN_LINK_PARTNER_ASM_DIR       (1 << 11)
#define ETHER_PHY_AN_LINK_PARTNER_PAUSE         (1 << 10)
#define ETHER_PHY_AN_LINK_PARTNER_100_T4        (1 << 9)
#define ETHER_PHY_AN_LINK_PARTNER_100F          (1 << 8)
#define ETHER_PHY_AN_LINK_PARTNER_100H          (1 << 7)
#define ETHER_PHY_AN_LINK_PARTNER_10F           (1 << 6)
#define ETHER_PHY_AN_LINK_PARTNER_10H           (1 << 5)
#define ETHER_PHY_AN_LINK_PARTNER_SELECTOR      (1 << 0)

#define ETHER_PHY_PIR_MDI_MASK                  (1 << 3)
#define ETHER_PHY_PIR_MDO_HIGH                  (0x04)
#define ETHER_PHY_PIR_MDO_LOW                   (0x00)
#define ETHER_PHY_PIR_MMD_WRITE                 (0x02)
#define ETHER_PHY_PIR_MMD_READ                  (0x00)
#define ETHER_PHY_PIR_MDC_HIGH                  (0x01)
#define ETHER_PHY_PIR_MDC_LOW                   (0x00)

#define ETHER_PHY_PREAMBLE_LENGTH               (32U)
#define ETHER_PHY_WRITE_DATA_BIT_MASK           (0x8000)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
uint32_t ether_phy_read(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr);
void     ether_phy_write(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr, uint32_t data);
void     ether_phy_targets_initialize(ether_phy_instance_ctrl_t * p_instance_ctrl) __attribute__((weak));

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
static void ether_phy_preamble(ether_phy_instance_ctrl_t * p_instance_ctrl);
static void ether_phy_reg_set(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr, int32_t option);
static void ether_phy_reg_read(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t * pdata);
static void ether_phy_reg_write(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t data);
static void ether_phy_trans_zto0(ether_phy_instance_ctrl_t * p_instance_ctrl);
static void ether_phy_trans_1to0(ether_phy_instance_ctrl_t * p_instance_ctrl);
static void ether_phy_mii_write1(ether_phy_instance_ctrl_t * p_instance_ctrl);
static void ether_phy_mii_write0(ether_phy_instance_ctrl_t * p_instance_ctrl);

/** ETHER_PHY HAL API mapping for Ethernet PHY Controller interface */
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const ether_phy_api_t g_ether_phy_on_ether_phy =
{
    .open                  = R_ETHER_PHY_Open,
    .close                 = R_ETHER_PHY_Close,
    .startAutoNegotiate    = R_ETHER_PHY_StartAutoNegotiate,
    .linkPartnerAbilityGet = R_ETHER_PHY_LinkPartnerAbilityGet,
    .linkStatusGet         = R_ETHER_PHY_LinkStatusGet,
};

/*******************************************************************************************************************//**
 * @addtogroup ETHER_PHY
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * @brief Resets Ethernet PHY device. Implements @ref ether_phy_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to ETHER_PHY control block or configuration structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN                    Control block has already been opened or channel is being used by another
 *                                                  instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_CHANNEL                 Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_POINTER                 Pointer to p_cfg is NULL.
 * @retval  FSP_ERR_TIMEOUT                         PHY-LSI Reset wait timeout.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_PHY_Open (ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    ether_phy_instance_ctrl_t * p_instance_ctrl = (ether_phy_instance_ctrl_t *) p_ctrl;
    R_ETHERC0_Type            * p_reg_etherc;
    uint32_t reg;
    uint32_t count = 0;

#if (ETHER_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_PHY_ERROR_RETURN(NULL != p_cfg, FSP_ERR_INVALID_POINTER);
    ETHER_PHY_ERROR_RETURN((ETHER_PHY_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);
    ETHER_PHY_ERROR_RETURN((BSP_FEATURE_ETHER_MAX_CHANNELS > p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
#endif

    /** Make sure this channel exists. */
    p_reg_etherc                     = ((R_ETHERC0_Type *) (R_ETHERC0_BASE + (ETHERC_REG_SIZE * p_cfg->channel)));
    p_instance_ctrl->p_reg_pir       = (uint32_t *) &p_reg_etherc->PIR;
    p_instance_ctrl->local_advertise = 0;

    /* Initialize configuration of ethernet phy module. */
    p_instance_ctrl->p_ether_phy_cfg = p_cfg;

    /* Configure pins for MII or RMII. Set PHYMODE0 if MII is selected. */
    R_PMISC->PFENET = (uint8_t) ((ETHER_PHY_MII_TYPE_MII == p_cfg->mii_type) << R_PMISC_PFENET_PHYMODE0_Pos);

    /* Reset PHY */
    ether_phy_write(p_instance_ctrl, ETHER_PHY_REG_CONTROL, ETHER_PHY_CONTROL_RESET);

    /* Reset completion waiting */
    do
    {
        reg = ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_CONTROL);
        count++;
    } while ((reg & ETHER_PHY_CONTROL_RESET) && (count < p_cfg->phy_reset_wait_time));

    if (count < p_cfg->phy_reset_wait_time)
    {
        ether_phy_targets_initialize(p_instance_ctrl);

        p_instance_ctrl->open = ETHER_PHY_OPEN;

        err = FSP_SUCCESS;
    }
    else
    {
        err = FSP_ERR_TIMEOUT;
    }

    return err;
}                                      /* End of function R_ETHER_PHY_Open() */

/********************************************************************************************************************//**
 * @brief Close Ethernet PHY device. Implements @ref ether_phy_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_PHY_Close (ether_phy_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    ether_phy_instance_ctrl_t * p_instance_ctrl = (ether_phy_instance_ctrl_t *) p_ctrl;

#if (ETHER_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_PHY_ERROR_RETURN(ETHER_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /** Clear configure block parameters. */
    p_instance_ctrl->p_ether_phy_cfg = NULL;
    p_instance_ctrl->local_advertise = 0;
    p_instance_ctrl->p_reg_pir       = NULL;

    p_instance_ctrl->open = 0;

    return err;
}                                      /* End of function R_ETHER_PHY_Close() */

/********************************************************************************************************************//**
 * @brief Starts auto-negotiate. Implements @ref ether_phy_api_t::startAutoNegotiate.
 *
 * @retval  FSP_SUCCESS                                 ETHER_PHY successfully starts auto-negotiate.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_PHY_StartAutoNegotiate (ether_phy_ctrl_t * const p_ctrl)
{
    ether_phy_instance_ctrl_t * p_instance_ctrl = (ether_phy_instance_ctrl_t *) p_ctrl;

#if (ETHER_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_PHY_ERROR_RETURN(ETHER_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set local ability */
    /* When pause frame is not used */
    if (ETHER_PHY_FLOW_CONTROL_DISABLE == p_instance_ctrl->p_ether_phy_cfg->flow_control)
    {
        p_instance_ctrl->local_advertise = ((((ETHER_PHY_AN_ADVERTISEMENT_100F |
                                               ETHER_PHY_AN_ADVERTISEMENT_100H) |
                                              ETHER_PHY_AN_ADVERTISEMENT_10F) |
                                             ETHER_PHY_AN_ADVERTISEMENT_10H) |
                                            ETHER_PHY_AN_ADVERTISEMENT_SELECTOR);
    }
    /* When pause frame is used */
    else
    {
        p_instance_ctrl->local_advertise = ((((((ETHER_PHY_AN_ADVERTISEMENT_ASM_DIR |
                                                 ETHER_PHY_AN_ADVERTISEMENT_PAUSE) |
                                                ETHER_PHY_AN_ADVERTISEMENT_100F) |
                                               ETHER_PHY_AN_ADVERTISEMENT_100H) |
                                              ETHER_PHY_AN_ADVERTISEMENT_10F) |
                                             ETHER_PHY_AN_ADVERTISEMENT_10H) |
                                            ETHER_PHY_AN_ADVERTISEMENT_SELECTOR);
    }

    /* Configure what the PHY and the Ethernet controller on this board supports */
    ether_phy_write(p_instance_ctrl, ETHER_PHY_REG_AN_ADVERTISEMENT, p_instance_ctrl->local_advertise);
    ether_phy_write(p_instance_ctrl,
                    ETHER_PHY_REG_CONTROL,
                    (ETHER_PHY_CONTROL_AN_ENABLE |
                     ETHER_PHY_CONTROL_AN_RESTART));

    ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_AN_ADVERTISEMENT);

    return FSP_SUCCESS;
}                                      /* End of function R_ETHER_PHY_StartAutoNegotiate() */

/********************************************************************************************************************//**
 * @brief Reports the other side's physical capability. Implements @ref ether_phy_api_t::linkPartnerAbilityGet.
 *
 * @retval  FSP_SUCCESS                                 ETHER_PHY successfully get link partner ability.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER_PHY control block is NULL.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to arguments are NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                PHY-LSI is not link up.
 * @retval  FSP_ERR_ETHER_PHY_NOT_READY                 The auto-negotiation isn't completed
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_PHY_LinkPartnerAbilityGet (ether_phy_ctrl_t * const p_ctrl,
                                             uint32_t * const         p_line_speed_duplex,
                                             uint32_t * const         p_local_pause,
                                             uint32_t * const         p_partner_pause)
{
    ether_phy_instance_ctrl_t * p_instance_ctrl = (ether_phy_instance_ctrl_t *) p_ctrl;
    uint32_t reg;

#if (ETHER_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_PHY_ERROR_RETURN(ETHER_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHER_PHY_ERROR_RETURN(NULL != p_line_speed_duplex, FSP_ERR_INVALID_POINTER);
    ETHER_PHY_ERROR_RETURN(NULL != p_local_pause, FSP_ERR_INVALID_POINTER);
    ETHER_PHY_ERROR_RETURN(NULL != p_partner_pause, FSP_ERR_INVALID_POINTER);
#endif

    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_STATUS);
    reg = ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_STATUS);

    /* When the link isn't up, return error */
    ETHER_PHY_ERROR_RETURN(ETHER_PHY_STATUS_LINK_UP == (reg & ETHER_PHY_STATUS_LINK_UP), FSP_ERR_ETHER_PHY_ERROR_LINK);

    /* Establish local pause capability */
    if (ETHER_PHY_AN_ADVERTISEMENT_PAUSE == (p_instance_ctrl->local_advertise & ETHER_PHY_AN_ADVERTISEMENT_PAUSE))
    {
        (*p_local_pause) |= (1 << 1);
    }

    if (ETHER_PHY_AN_ADVERTISEMENT_ASM_DIR == (p_instance_ctrl->local_advertise & ETHER_PHY_AN_ADVERTISEMENT_ASM_DIR))
    {
        (*p_local_pause) |= 1;
    }

    /* When the auto-negotiation isn't completed, return error */
    ETHER_PHY_ERROR_RETURN(ETHER_PHY_STATUS_AN_COMPLETE == (reg & ETHER_PHY_STATUS_AN_COMPLETE),
                           FSP_ERR_ETHER_PHY_NOT_READY);

    /* Get the link partner response */
    reg = ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_AN_LINK_PARTNER);

    /* Establish partner pause capability */
    if (ETHER_PHY_AN_LINK_PARTNER_PAUSE == (reg & ETHER_PHY_AN_LINK_PARTNER_PAUSE))
    {
        (*p_partner_pause) = (1 << 1);
    }

    if (ETHER_PHY_AN_LINK_PARTNER_ASM_DIR == (reg & ETHER_PHY_AN_LINK_PARTNER_ASM_DIR))
    {
        (*p_partner_pause) |= 1;
    }

    /* Establish the line speed and the duplex */
    if (ETHER_PHY_AN_LINK_PARTNER_10H == (reg & ETHER_PHY_AN_LINK_PARTNER_10H))
    {
        (*p_line_speed_duplex) = ETHER_PHY_LINK_SPEED_10H;
    }

    if (ETHER_PHY_AN_LINK_PARTNER_10F == (reg & ETHER_PHY_AN_LINK_PARTNER_10F))
    {
        (*p_line_speed_duplex) = ETHER_PHY_LINK_SPEED_10F;
    }

    if (ETHER_PHY_AN_LINK_PARTNER_100H == (reg & ETHER_PHY_AN_LINK_PARTNER_100H))
    {
        (*p_line_speed_duplex) = ETHER_PHY_LINK_SPEED_100H;
    }

    if (ETHER_PHY_AN_LINK_PARTNER_100F == (reg & ETHER_PHY_AN_LINK_PARTNER_100F))
    {
        (*p_line_speed_duplex) = ETHER_PHY_LINK_SPEED_100F;
    }

    return FSP_SUCCESS;
}                                      /* End of function R_ETHER_PHY_LinkPartnerAbilityGet() */

/********************************************************************************************************************//**
 * @brief Returns the status of the physical link. Implements @ref ether_phy_api_t::linkStatusGet.
 *
 * @retval  FSP_SUCCESS                                 ETHER_PHY successfully get link partner ability.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                PHY-LSI is not link up.
 ***********************************************************************************************************************/
fsp_err_t R_ETHER_PHY_LinkStatusGet (ether_phy_ctrl_t * const p_ctrl)
{
    ether_phy_instance_ctrl_t * p_instance_ctrl = (ether_phy_instance_ctrl_t *) p_ctrl;
    uint32_t  reg;
    fsp_err_t err = FSP_SUCCESS;

#if (ETHER_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHER_PHY_ERROR_RETURN(ETHER_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_STATUS);
    reg = ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_STATUS);

    /* When the link isn't up, return error */
    if (ETHER_PHY_STATUS_LINK_UP != (reg & ETHER_PHY_STATUS_LINK_UP))
    {
        /* Link is down */
        err = FSP_ERR_ETHER_PHY_ERROR_LINK;
    }
    else
    {
        /* Link is up */
        err = FSP_SUCCESS;
    }

    return err;
}                                      /* End of function R_ETHER_PHY_LinkStatusGet() */

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHER_PHY)
 **********************************************************************************************************************/

/**
 * Private functions
 */

/***********************************************************************************************************************
 * Function Name: ether_phy_read
 * Description  : Reads a PHY register
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 *                reg_addr -
 *                    address of the PHY register
 * Return Value : read value
 ***********************************************************************************************************************/
uint32_t ether_phy_read (ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr)
{
    uint32_t data;

    /*
     * The value is read from the PHY register by the frame format of MII Management Interface provided
     * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2.
     */
    ether_phy_preamble(p_instance_ctrl);
    ether_phy_reg_set(p_instance_ctrl, reg_addr, ETHER_PHY_MII_READ);
    ether_phy_trans_zto0(p_instance_ctrl);
    ether_phy_reg_read(p_instance_ctrl, &data);
    ether_phy_trans_zto0(p_instance_ctrl);

    return data;
}                                      /* End of function ether_phy_read() */

/***********************************************************************************************************************
 * Function Name: ether_phy_write
 * Description  : Writes to a PHY register
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 *                reg_addr -
 *                    address of the PHY register
 *                data -
 *                    value
 * Return Value : none
 ***********************************************************************************************************************/
void ether_phy_write (ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr, uint32_t data)
{
    /*
     * The value is read from the PHY register by the frame format of MII Management Interface provided
     * for by Table 22-12 of 22.2.4.5 of IEEE 802.3-2008_section2.
     */
    ether_phy_preamble(p_instance_ctrl);
    ether_phy_reg_set(p_instance_ctrl, reg_addr, ETHER_PHY_MII_WRITE);
    ether_phy_trans_1to0(p_instance_ctrl);
    ether_phy_reg_write(p_instance_ctrl, data);
    ether_phy_trans_zto0(p_instance_ctrl);
}                                      /* End of function ether_phy_write() */

/***********************************************************************************************************************
 * Function Name: phy_preamble
 * Description  : As preliminary preparation for access to the PHY module register,
 *                "1" is output via the MII management interface.
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_preamble (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    int16_t i;

    /*
     * The processing of PRE (preamble) about the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    i = ETHER_PHY_PREAMBLE_LENGTH;
    while (i > 0)
    {
        ether_phy_mii_write1(p_instance_ctrl);
        i--;
    }
}                                      /* End of function ether_phy_preamble() */

/***********************************************************************************************************************
 * Function Name: ether_phy_reg_set
 * Description  : Sets a PHY device to read or write mode
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 *                reg_addr -
 *                    address of the PHY register
 *                option -
 *                    mode
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_reg_set (ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr, int32_t option)
{
    int32_t  i;
    uint32_t data = 0;

    /*
     * The processing of ST (start of frame),OP (operation code), PHYAD (PHY Address), and
     * REGAD (Register Address)  about the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    data = (ETHER_PHY_MII_ST << 14);                                             /* ST code    */

    if (ETHER_PHY_MII_READ == option)
    {
        data |= (ETHER_PHY_MII_READ << 12);                                      /* OP code(RD)  */
    }
    else
    {
        data |= (ETHER_PHY_MII_WRITE << 12);                                     /* OP code(WT)  */
    }

    data |= (uint32_t) (p_instance_ctrl->p_ether_phy_cfg->phy_lsi_address << 7); /* PHY Address  */

    data |= (reg_addr << 2);                                                     /* Reg Address  */

    i = 14;
    while (i > 0)
    {
        if (0 == (data & ETHER_PHY_WRITE_DATA_BIT_MASK))
        {
            ether_phy_mii_write0(p_instance_ctrl);
        }
        else
        {
            ether_phy_mii_write1(p_instance_ctrl);
        }

        data = (data << 1);
        i--;
    }
}                                      /* End of function ether_phy_reg_set() */

/***********************************************************************************************************************
 * Function Name: ether_phy_reg_read
 * Description  : Reads PHY register through MII interface
 * Arguments    : p_instance_ctrl -
 *                    Ethernet channel number
 *                pdata -
 *                    pointer to store the data read
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_reg_read (ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t * pdata)
{
    int32_t  i;
    int32_t  j;
    uint32_t reg_data;

    volatile uint32_t * petherc_pir;

    petherc_pir = p_instance_ctrl->p_reg_pir;

    /*
     * The processing of DATA (data) about reading of the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    reg_data = 0;
    i        = 16;
    while (i > 0)
    {
        for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
        {
            (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_LOW);
        }

        for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
        {
            (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_HIGH);
        }

        reg_data = (reg_data << 1);

        reg_data |= (uint32_t) (((*petherc_pir) & ETHER_PHY_PIR_MDI_MASK) >> 3); /* MDI read  */

        for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
        {
            (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_HIGH);
        }

        for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
        {
            (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_LOW);
        }

        i--;
    }

    (*pdata) = reg_data;
}                                      /* End of function ether_phy_reg_read() */

/***********************************************************************************************************************
 * Function Name: ether_phy_reg_write
 * Description  : Writes to PHY register through MII interface
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 *                data -
 *                    value to write
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_reg_write (ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t data)
{
    int32_t i;

    /*
     * The processing of DATA (data) about writing of the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    i = 16;
    while (i > 0)
    {
        if (0 == (data & ETHER_PHY_WRITE_DATA_BIT_MASK))
        {
            ether_phy_mii_write0(p_instance_ctrl);
        }
        else
        {
            ether_phy_mii_write1(p_instance_ctrl);
        }

        i--;
        data = (data << 1);
    }
}                                      /* End of function ether_phy_reg_write() */

/***********************************************************************************************************************
 * Function Name: ether_phy_trans_zto0
 * Description  : Performs bus release so that PHY can drive data
 *              : for read operation
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_trans_zto0 (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    int32_t j;

    volatile uint32_t * petherc_pir;

    petherc_pir = p_instance_ctrl->p_reg_pir;

    /*
     * The processing of TA (turnaround) about reading of the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_LOW);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_HIGH);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_HIGH);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_READ | ETHER_PHY_PIR_MDC_LOW);
    }
}                                      /* End of function ether_phy_trans_zto0() */

/***********************************************************************************************************************
 * Function Name: phy_trans_1to0
 * Description  : Switches data bus so MII interface can drive data
 *              : for write operation
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_trans_1to0 (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    /*
     * The processing of TA (turnaround) about writing of the frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     */
    ether_phy_mii_write1(p_instance_ctrl);
    ether_phy_mii_write0(p_instance_ctrl);
}                                      /* End of function ether_phy_trans_1to0() */

/***********************************************************************************************************************
 * Function Name: ether_phy_mii_write1
 * Description  : Outputs 1 to the MII interface
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_mii_write1 (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    int32_t             j;
    volatile uint32_t * petherc_pir;

    petherc_pir = p_instance_ctrl->p_reg_pir;

    /*
     * The processing of one bit about frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     * The data that 1 is output.
     */
    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_HIGH | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_LOW);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_HIGH | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_HIGH);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_HIGH | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_HIGH);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_HIGH | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_LOW);
    }
}                                      /* End of function ether_phy_mii_write1() */

/***********************************************************************************************************************
 * Function Name: ether_phy_mii_write0
 * Description  : Outputs 0 to the MII interface
 * Arguments    : ether_channel -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
static void ether_phy_mii_write0 (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    int32_t             j;
    volatile uint32_t * petherc_pir;

    petherc_pir = p_instance_ctrl->p_reg_pir;

    /*
     * The processing of one bit about frame format of MII Management Interface which is
     * provided by "Table 22-12" of "22.2.4.5" of "IEEE 802.3-2008_section2".
     * The data that 0 is output.
     */
    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_LOW);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_HIGH);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_HIGH);
    }

    for (j = p_instance_ctrl->p_ether_phy_cfg->mii_bit_access_wait_time; j > 0; j--)
    {
        (*petherc_pir) = (ETHER_PHY_PIR_MDO_LOW | ETHER_PHY_PIR_MMD_WRITE | ETHER_PHY_PIR_MDC_LOW);
    }
}                                      /* End of function ether_phy_mii_write0() */

/***********************************************************************************************************************
 * Function Name: ether_phy_targets_initialize
 * Description  : PHY-LSI specific initialization processing
 * Arguments    : p_ctrl -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
void ether_phy_targets_initialize (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    (void) p_instance_ctrl;
}                                      /* End of function ether_phy_targets_initialize() */
