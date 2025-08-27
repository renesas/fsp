/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

/* Access to peripherals and board defines. */
#include "bsp_api.h"
#include "r_ethercat_phy.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

#ifndef ETHERCAT_PHY_ERROR_RETURN
 #define ETHERCAT_PHY_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/** "ECPH" in ASCII.  Used to determine if the control block is open. */
#define ETHERCAT_PHY_OPEN                           (('C' << 24U) | ('P' << 16U) | ('H' << 8U) | ('Y' << 0U))

/* Standard PHY Registers */
#define ETHERCAT_PHY_REG_CONTROL                    (0)
#define ETHERCAT_PHY_REG_STATUS                     (1)
#define ETHERCAT_PHY_REG_IDENTIFIER1                (2)
#define ETHERCAT_PHY_REG_IDENTIFIER2                (3)
#define ETHERCAT_PHY_REG_AN_ADVERTISEMENT           (4)
#define ETHERCAT_PHY_REG_AN_LINK_PARTNER            (5)
#define ETHERCAT_PHY_REG_AN_EXPANSION               (6)
#define ETHERCAT_PHY_REG_GIGABIT_CONTROL            (9)

/* Basic Mode Control Register Bit Definitions */
#define ETHERCAT_PHY_CONTROL_RESET                  (1 << 15)
#define ETHERCAT_PHY_CONTROL_LOOPBACK               (1 << 14)
#define ETHERCAT_PHY_CONTROL_100_MBPS               (1 << 13)
#define ETHERCAT_PHY_CONTROL_AN_ENABLE              (1 << 12)
#define ETHERCAT_PHY_CONTROL_POWER_DOWN             (1 << 11)
#define ETHERCAT_PHY_CONTROL_ISOLATE                (1 << 10)
#define ETHERCAT_PHY_CONTROL_AN_RESTART             (1 << 9)
#define ETHERCAT_PHY_CONTROL_FULL_DUPLEX            (1 << 8)
#define ETHERCAT_PHY_CONTROL_COLLISION              (1 << 7)

/* Basic Mode Status Register Bit Definitions */
#define ETHERCAT_PHY_STATUS_100_T4                  (1 << 15)
#define ETHERCAT_PHY_STATUS_100F                    (1 << 14)
#define ETHERCAT_PHY_STATUS_100H                    (1 << 13)
#define ETHERCAT_PHY_STATUS_10F                     (1 << 12)
#define ETHERCAT_PHY_STATUS_10H                     (1 << 11)
#define ETHERCAT_PHY_STATUS_AN_COMPLETE             (1 << 5)
#define ETHERCAT_PHY_STATUS_RM_FAULT                (1 << 4)
#define ETHERCAT_PHY_STATUS_AN_ABILITY              (1 << 3)
#define ETHERCAT_PHY_STATUS_LINK_UP                 (1 << 2)
#define ETHERCAT_PHY_STATUS_JABBER                  (1 << 1)
#define ETHERCAT_PHY_STATUS_EX_CAPABILITY           (1 << 0)

/* Auto Negotiation Advertisement Bit Definitions */
#define ETHERCAT_PHY_AN_ADVERTISEMENT_NEXT_PAGE     (1 << 15)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_RM_FAULT      (1 << 13)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_ASM_DIR       (1 << 11)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_PAUSE         (1 << 10)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_100_T4        (1 << 9)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_100F          (1 << 8)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_100H          (1 << 7)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_10F           (1 << 6)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_10H           (1 << 5)
#define ETHERCAT_PHY_AN_ADVERTISEMENT_SELECTOR      (1 << 0)

/* Auto Negotiate Link Partner Ability Bit Definitions */
#define ETHERCAT_PHY_AN_LINK_PARTNER_NEXT_PAGE      (1 << 15)
#define ETHERCAT_PHY_AN_LINK_PARTNER_ACK            (1 << 14)
#define ETHERCAT_PHY_AN_LINK_PARTNER_RM_FAULT       (1 << 13)
#define ETHERCAT_PHY_AN_LINK_PARTNER_ASM_DIR        (1 << 11)
#define ETHERCAT_PHY_AN_LINK_PARTNER_PAUSE          (1 << 10)
#define ETHERCAT_PHY_AN_LINK_PARTNER_100_T4         (1 << 9)
#define ETHERCAT_PHY_AN_LINK_PARTNER_100F           (1 << 8)
#define ETHERCAT_PHY_AN_LINK_PARTNER_100H           (1 << 7)
#define ETHERCAT_PHY_AN_LINK_PARTNER_10F            (1 << 6)
#define ETHERCAT_PHY_AN_LINK_PARTNER_10H            (1 << 5)
#define ETHERCAT_PHY_AN_LINK_PARTNER_SELECTOR       (1 << 0)

#define ETHERCAT_PHY_PIR_MDI_MASK                   (1 << 3)
#define ETHERCAT_PHY_PIR_MDO_HIGH                   (0x04)
#define ETHERCAT_PHY_PIR_MDO_LOW                    (0x00)
#define ETHERCAT_PHY_PIR_MMD_WRITE                  (0x02)
#define ETHERCAT_PHY_PIR_MMD_READ                   (0x00)
#define ETHERCAT_PHY_PIR_MDC_HIGH                   (0x01)
#define ETHERCAT_PHY_PIR_MDC_LOW                    (0x00)

/* Gigabit Control Bit Definitions */
#define ETHERCAT_PHY_GIGABIT_CONTROL_1000F          (1 << 9)
#define ETHERCAT_PHY_GIGABIT_CONTROL_1000H          (1 << 8)

#define ETHERCAT_PHY_ADDRESS_SIZE                   (0x1fU)
#define ETHERCAT_PHY_REGISTER_DATA_SIZE             (0xffffU)

#define ETHERCAT_PHY_MII_CONT_STAT_READ_COMMAND     (1)
#define ETHERCAT_PHY_MII_CONT_STAT_WRITE_COMMAND    (2)
#define ETHERCAT_PHY_ERROR_DATA                     (0xffff)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
#if (ETHER_PHY_CFG_TARGET_ICS1894_ENABLE)
extern void ethercat_phy_target_ics1894_initialize(ethercat_phy_instance_ctrl_t * p_instance_ctrl);
extern bool ethercat_phy_target_ics1894_is_support_link_partner_ability(ethercat_phy_instance_ctrl_t * p_instance_ctrl,
                                                                        uint32_t                       line_speed_duplex);

#endif

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
static void ethercat_phy_targets_initialize(ethercat_phy_instance_ctrl_t * p_instance_ctrl);
static bool ethercat_phy_targets_is_support_link_partner_ability(ethercat_phy_instance_ctrl_t * p_instance_ctrl,
                                                                 uint32_t                       line_speed_duplex);

/** ETHERCAT_PHY HAL API mapping for Ethercat PHY Controller interface */
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const ether_phy_api_t g_ether_phy_on_ethercat_phy =
{
    .open                  = R_ETHERCAT_PHY_Open,
    .close                 = R_ETHERCAT_PHY_Close,
    .startAutoNegotiate    = R_ETHERCAT_PHY_StartAutoNegotiate,
    .linkPartnerAbilityGet = R_ETHERCAT_PHY_LinkPartnerAbilityGet,
    .linkStatusGet         = R_ETHERCAT_PHY_LinkStatusGet,
    .chipInit              = R_ETHERCAT_PHY_ChipInit,
    .read                  = R_ETHERCAT_PHY_Read,
    .write                 = R_ETHERCAT_PHY_Write
};

/*******************************************************************************************************************//**
 * @addtogroup ETHERCAT_PHY
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * @brief Resets Ethercat PHY device. Implements @ref ether_phy_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to ETHERCAT_PHY control block or configuration structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN                    Control block has already been opened or channel is being used by another
 *                                                  instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_CHANNEL                 Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_POINTER                 Pointer to p_cfg is NULL.
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_Open (ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(NULL != p_cfg, FSP_ERR_INVALID_POINTER);
    ETHERCAT_PHY_ERROR_RETURN((ETHERCAT_PHY_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);
    ETHERCAT_PHY_ERROR_RETURN((BSP_FEATURE_ETHER_NUM_CHANNELS > p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
#endif

    /* Initialize configuration of ethernet phy module. */
    p_instance_ctrl->p_ether_phy_cfg = p_cfg;

    p_instance_ctrl->local_advertise = 0;

    /* Configure pins for MII or RMII. Set PHYMODE0 if MII is selected. */
    R_PMISC->PFENET =
        (uint8_t) ((ETHER_PHY_MII_TYPE_MII == p_cfg->mii_type) << (R_PMISC_PFENET_PHYMODE0_Pos + p_cfg->channel));

    p_instance_ctrl->open = ETHERCAT_PHY_OPEN;

    return err;
}                                      /* End of function R_ETHERCAT_PHY_Open() */

/********************************************************************************************************************//**
 * @brief Close Ethercat PHY device. Implements @ref ether_phy_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHERCAT_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_Close (ether_phy_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /** Clear configure block parameters. */
    p_instance_ctrl->p_ether_phy_cfg  = NULL;
    p_instance_ctrl->local_advertise  = 0;
    p_instance_ctrl->interface_status = ETHERCAT_PHY_INTERFACE_STATUS_UNINITIALIZED;
    p_instance_ctrl->open             = 0;

    return err;
}                                      /* End of function R_ETHERCAT_PHY_Close() */

/********************************************************************************************************************//**
 * @brief Starts auto-negotiate. Implements @ref ether_phy_api_t::startAutoNegotiate.
 *
 * @retval  FSP_SUCCESS                                 ETHERCAT_PHY successfully starts auto-negotiate.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHERCAT_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Register address is incorrect
 * @retval  FSP_ERR_INVALID_MODE                        Command is invalid.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to read buffer is NULL.
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_StartAutoNegotiate (ether_phy_ctrl_t * const p_ctrl)
{
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;
    uint32_t reg = 0;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                              FSP_ERR_NOT_INITIALIZED);
#endif

    /* Set local ability */
    /* When pause frame is not used */
    if (ETHER_PHY_FLOW_CONTROL_DISABLE == p_instance_ctrl->p_ether_phy_cfg->flow_control)
    {
        p_instance_ctrl->local_advertise = ((((ETHERCAT_PHY_AN_ADVERTISEMENT_100F |
                                               ETHERCAT_PHY_AN_ADVERTISEMENT_100H) |
                                              ETHERCAT_PHY_AN_ADVERTISEMENT_10F) |
                                             ETHERCAT_PHY_AN_ADVERTISEMENT_10H) |
                                            ETHERCAT_PHY_AN_ADVERTISEMENT_SELECTOR);
    }
    /* When pause frame is used */
    else
    {
        p_instance_ctrl->local_advertise = ((((((ETHERCAT_PHY_AN_ADVERTISEMENT_ASM_DIR |
                                                 ETHERCAT_PHY_AN_ADVERTISEMENT_PAUSE) |
                                                ETHERCAT_PHY_AN_ADVERTISEMENT_100F) |
                                               ETHERCAT_PHY_AN_ADVERTISEMENT_100H) |
                                              ETHERCAT_PHY_AN_ADVERTISEMENT_10F) |
                                             ETHERCAT_PHY_AN_ADVERTISEMENT_10H) |
                                            ETHERCAT_PHY_AN_ADVERTISEMENT_SELECTOR);
    }

    /* Configure what the PHY and the Ethernet controller on this board supports */
    R_ETHERCAT_PHY_Write(p_instance_ctrl, ETHERCAT_PHY_REG_AN_ADVERTISEMENT, p_instance_ctrl->local_advertise);

    /* Advertise Gigabit Ethernet capacity when using RGMII or GMII. */
    if ((ETHER_PHY_MII_TYPE_RGMII == p_instance_ctrl->p_ether_phy_cfg->mii_type) ||
        (ETHER_PHY_MII_TYPE_GMII == p_instance_ctrl->p_ether_phy_cfg->mii_type))
    {
        R_ETHERCAT_PHY_Write(p_instance_ctrl, ETHERCAT_PHY_REG_GIGABIT_CONTROL,
                             (ETHERCAT_PHY_GIGABIT_CONTROL_1000F | ETHERCAT_PHY_GIGABIT_CONTROL_1000H));
    }

    /* Start auto-negotiation. */
    R_ETHERCAT_PHY_Write(p_instance_ctrl,
                         ETHERCAT_PHY_REG_CONTROL,
                         (ETHERCAT_PHY_CONTROL_AN_ENABLE |
                          ETHERCAT_PHY_CONTROL_AN_RESTART));

    R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_AN_ADVERTISEMENT, &reg);

    return FSP_SUCCESS;
}                                      /* End of function R_ETHERCAT_PHY_StartAutoNegotiate() */

/********************************************************************************************************************//**
 * @brief Reports the other side's physical capability. Implements @ref ether_phy_api_t::linkPartnerAbilityGet.
 *
 * @retval  FSP_SUCCESS                                 ETHERCAT_PHY successfully get link partner ability.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHERCAT_PHY control block is NULL.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to arguments are NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                PHY-LSI is not link up.
 * @retval  FSP_ERR_ETHER_PHY_NOT_READY                 The auto-negotiation isn't completed
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Status register address is incorrect
 * @retval  FSP_ERR_INVALID_MODE                        Command is invalid.
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_LinkPartnerAbilityGet (ether_phy_ctrl_t * const p_ctrl,
                                                uint32_t * const         p_line_speed_duplex,
                                                uint32_t * const         p_local_pause,
                                                uint32_t * const         p_partner_pause)
{
    fsp_err_t err = FSP_SUCCESS;
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;
    uint32_t reg               = 0;
    uint32_t line_speed_duplex = ETHER_PHY_LINK_SPEED_NO_LINK;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHERCAT_PHY_ERROR_RETURN(NULL != p_line_speed_duplex, FSP_ERR_INVALID_POINTER);
    ETHERCAT_PHY_ERROR_RETURN(NULL != p_local_pause, FSP_ERR_INVALID_POINTER);
    ETHERCAT_PHY_ERROR_RETURN(NULL != p_partner_pause, FSP_ERR_INVALID_POINTER);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                              FSP_ERR_NOT_INITIALIZED);
#endif

    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_STATUS, &reg);
    R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_STATUS, &reg);

    /* When the link isn't up, return error */
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_STATUS_LINK_UP == (reg & ETHERCAT_PHY_STATUS_LINK_UP),
                              FSP_ERR_ETHER_PHY_ERROR_LINK);

    /* Establish local pause capability */
    if (ETHERCAT_PHY_AN_ADVERTISEMENT_PAUSE == (p_instance_ctrl->local_advertise & ETHERCAT_PHY_AN_ADVERTISEMENT_PAUSE))
    {
        (*p_local_pause) |= (1 << 1);
    }

    if (ETHERCAT_PHY_AN_ADVERTISEMENT_ASM_DIR ==
        (p_instance_ctrl->local_advertise & ETHERCAT_PHY_AN_ADVERTISEMENT_ASM_DIR))
    {
        (*p_local_pause) |= 1;
    }

    /* When the auto-negotiation isn't completed, return error */
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_STATUS_AN_COMPLETE == (reg & ETHERCAT_PHY_STATUS_AN_COMPLETE),
                              FSP_ERR_ETHER_PHY_NOT_READY);

    /* Get the link partner response */
    R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_AN_LINK_PARTNER, &reg);

    /* Establish partner pause capability */
    if (ETHERCAT_PHY_AN_LINK_PARTNER_PAUSE == (reg & ETHERCAT_PHY_AN_LINK_PARTNER_PAUSE))
    {
        (*p_partner_pause) = (1 << 1);
    }

    if (ETHERCAT_PHY_AN_LINK_PARTNER_ASM_DIR == (reg & ETHERCAT_PHY_AN_LINK_PARTNER_ASM_DIR))
    {
        (*p_partner_pause) |= 1;
    }

    /* Establish the line speed and the duplex */
    if ((ETHERCAT_PHY_AN_LINK_PARTNER_10H == (reg & ETHERCAT_PHY_AN_LINK_PARTNER_10H)) &&
        ethercat_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_10H))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_10H;
    }

    if ((ETHERCAT_PHY_AN_LINK_PARTNER_10F == (reg & ETHERCAT_PHY_AN_LINK_PARTNER_10F)) &&
        ethercat_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_10F))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_10F;
    }

    if ((ETHERCAT_PHY_AN_LINK_PARTNER_100H == (reg & ETHERCAT_PHY_AN_LINK_PARTNER_100H)) &&
        ethercat_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_100H))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_100H;
    }

    if ((ETHERCAT_PHY_AN_LINK_PARTNER_100F == (reg & ETHERCAT_PHY_AN_LINK_PARTNER_100F)) &&
        ethercat_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_100F))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_100F;
    }

    /* When MII type is RGMII, check also Gigabit Ethernet ability. */
    if ((ETHER_PHY_MII_TYPE_RGMII == p_instance_ctrl->p_ether_phy_cfg->mii_type) ||
        (ETHER_PHY_MII_TYPE_GMII == p_instance_ctrl->p_ether_phy_cfg->mii_type))
    {
        R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_GIGABIT_CONTROL, &reg);

        if ((ETHERCAT_PHY_GIGABIT_CONTROL_1000H == (reg & ETHERCAT_PHY_GIGABIT_CONTROL_1000H)) &&
            ethercat_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_1000H))
        {
            line_speed_duplex = ETHER_PHY_LINK_SPEED_1000H;
        }

        if ((ETHERCAT_PHY_GIGABIT_CONTROL_1000F == (reg & ETHERCAT_PHY_GIGABIT_CONTROL_1000F)) &&
            ethercat_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_1000F))
        {
            line_speed_duplex = ETHER_PHY_LINK_SPEED_1000F;
        }
    }

    if (ETHER_PHY_LINK_SPEED_NO_LINK == line_speed_duplex)
    {
        err = FSP_ERR_ETHER_PHY_ERROR_LINK;
    }
    else
    {
        (*p_line_speed_duplex) = line_speed_duplex;
    }

    return err;
}                                      /* End of function R_ETHERCAT_PHY_LinkPartnerAbilityGet() */

/********************************************************************************************************************//**
 * @brief Returns the status of the physical link. Implements @ref ether_phy_api_t::linkStatusGet.
 *
 * @retval  FSP_SUCCESS                                 ETHERCAT_PHY successfully get link partner ability.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHERCAT_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                PHY-LSI is not link up.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Status register address is incorrect
 * @retval  FSP_ERR_INVALID_MODE                        Command is invalid.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to read buffer is NULL.
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_LinkStatusGet (ether_phy_ctrl_t * const p_ctrl)
{
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;
    uint32_t  reg = 0;
    fsp_err_t err = FSP_SUCCESS;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                              FSP_ERR_NOT_INITIALIZED);
#endif

    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_STATUS, &reg);
    R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_STATUS, &reg);

    /* When the link isn't up, return error */
    if (ETHERCAT_PHY_STATUS_LINK_UP != (reg & ETHERCAT_PHY_STATUS_LINK_UP))
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
}                                      /* End of function R_ETHERCAT_PHY_LinkStatusGet() */

/********************************************************************************************************************//**
 * @brief Initialize Ethercat PHY device. Implements @ref ether_phy_api_t::chipInit.
 *
 * @retval  FSP_SUCCESS                             PHY device initialized successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to ETHERCAT_PHY control block or configuration structure is NULL.
 * @retval  FSP_ERR_INVALID_POINTER                 Pointer to p_cfg is NULL.
 * @retval  FSP_ERR_NOT_OPEN                        The control block has not been opened.
 * @retval  FSP_ERR_TIMEOUT                         PHY-LSI Reset wait timeout.
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_ChipInit (ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;
    uint32_t count = 0;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(NULL != p_cfg, FSP_ERR_INVALID_POINTER);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->interface_status = ETHERCAT_PHY_INTERFACE_STATUS_INITIALIZED;

    if (count < p_cfg->phy_reset_wait_time)
    {
        ethercat_phy_targets_initialize(p_instance_ctrl);
    }
    else
    {
        err = FSP_ERR_TIMEOUT;
    }

    return err;
}                                      /* End of function R_ETHERCAT_PHY_ChipInit() */

/********************************************************************************************************************//**
 * @brief Read data from register of PHY-LSI . Implements @ref ether_phy_api_t::read.
 *
 * @retval  FSP_SUCCESS                                 ETHERCAT_PHY successfully read data.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHERCAT_PHY control block is NULL.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to read buffer is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Address is not a valid size
 * @retval  FSP_ERR_INVALID_MODE                        Command is invalid.
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_Read (ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t * const p_data)
{
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;
    fsp_err_t    err       = FSP_SUCCESS;
    R_ESC_Type * p_reg_esc = (R_ESC_Type *) R_ESC_BASE;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(NULL != p_data, FSP_ERR_INVALID_POINTER);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_ADDRESS_SIZE >= reg_addr, FSP_ERR_INVALID_ARGUMENT);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                              FSP_ERR_NOT_INITIALIZED);
#endif

    /* If the management interface is busy, wait until it is no longer so. */
    FSP_HARDWARE_REGISTER_WAIT(p_reg_esc->MII_CONT_STAT_b.BUSY, 0U)

    if (FSP_SUCCESS == err)
    {
        /* Get PDI access right */
        p_reg_esc->MII_PDI_ACS_STAT_b.ACSMII = 1;

        /* Confirm that access rights switch to PDI. */
        FSP_HARDWARE_REGISTER_WAIT(p_reg_esc->MII_ECAT_ACS_STAT_b.ACSMII, 0U)
    }

    if (FSP_SUCCESS == err)
    {
        /* Read PHY register */
        p_reg_esc->PHY_ADR = (uint8_t) R_ESC_PHY_ADR_PHYADDR_Msk &
                             (p_instance_ctrl->p_ether_phy_cfg->phy_lsi_address << R_ESC_PHY_ADR_PHYADDR_Pos);
        p_reg_esc->PHY_REG_ADR = (uint8_t) R_ESC_PHY_REG_ADR_PHYREGADDR_Msk &
                                 (reg_addr << R_ESC_PHY_REG_ADR_PHYREGADDR_Pos);
        p_reg_esc->MII_CONT_STAT = ETHERCAT_PHY_MII_CONT_STAT_READ_COMMAND << R_ESC_MII_CONT_STAT_COMMAND_Pos; // < Read command

        /* Start read access to the phy register and wait for completion. */
        FSP_HARDWARE_REGISTER_WAIT(p_reg_esc->MII_CONT_STAT_b.BUSY, 0U)
    }

    if (FSP_SUCCESS == err)
    {
        /* Check the error bit */
        if ((p_reg_esc->MII_CONT_STAT &
             (R_ESC_MII_CONT_STAT_CMDERR_Msk | R_ESC_MII_CONT_STAT_READERR_Msk)))
        {
            /*  Error operation */
            err = FSP_ERR_INVALID_MODE;

            /* Clear error bit */
            p_reg_esc->MII_CONT_STAT_b.COMMAND = 0x0;
        }
    }

    if (FSP_SUCCESS == err)
    {
        /* Get read data */
        *p_data = p_reg_esc->PHY_DATA;

        /* Give the access right to ECAT */
        p_reg_esc->MII_PDI_ACS_STAT_b.ACSMII = 0;
    }
    else
    {
        *p_data = ETHERCAT_PHY_ERROR_DATA;
    }

    return err;
}                                      /* End of function R_ETHERCAT_PHY_Read() */

/********************************************************************************************************************//**
 * @brief Write data to register of PHY-LSI . Implements @ref ether_phy_api_t::write.
 *
 * @retval  FSP_SUCCESS                                 ETHERCAT_PHY successfully write data.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHERCAT_PHY control block is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Address or data is not a valid size
 * @retval  FSP_ERR_INVALID_MODE                        Command is invalid.
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 ***********************************************************************************************************************/
fsp_err_t R_ETHERCAT_PHY_Write (ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t data)
{
    ethercat_phy_instance_ctrl_t * p_instance_ctrl = (ethercat_phy_instance_ctrl_t *) p_ctrl;
    fsp_err_t    err       = FSP_SUCCESS;
    R_ESC_Type * p_reg_esc = (R_ESC_Type *) R_ESC_BASE;

#if (ETHERCAT_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_ADDRESS_SIZE >= reg_addr, FSP_ERR_INVALID_ARGUMENT);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_REGISTER_DATA_SIZE >= data, FSP_ERR_INVALID_ARGUMENT);
    ETHERCAT_PHY_ERROR_RETURN(ETHERCAT_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                              FSP_ERR_NOT_INITIALIZED);
#endif

    /* If the management interface is busy, wait until it is no longer so. */
    FSP_HARDWARE_REGISTER_WAIT(p_reg_esc->MII_CONT_STAT_b.BUSY, 0U)

    if (FSP_SUCCESS == err)
    {
        /* Get PDI access right */
        p_reg_esc->MII_PDI_ACS_STAT_b.ACSMII = 1;

        /* Confirm that access rights switch to PDI. */
        FSP_HARDWARE_REGISTER_WAIT(p_reg_esc->MII_ECAT_ACS_STAT_b.ACSMII, 0U)
    }

    if (FSP_SUCCESS == err)
    {
        /* Write PHY register */
        p_reg_esc->PHY_ADR = (uint8_t) R_ESC_PHY_ADR_PHYADDR_Msk &
                             (p_instance_ctrl->p_ether_phy_cfg->phy_lsi_address << R_ESC_PHY_ADR_PHYADDR_Pos);
        p_reg_esc->PHY_REG_ADR = (uint8_t) R_ESC_PHY_REG_ADR_PHYREGADDR_Msk &
                                 (reg_addr << R_ESC_PHY_REG_ADR_PHYREGADDR_Pos);
        p_reg_esc->PHY_DATA = (uint16_t) R_ESC_PHY_DATA_PHYREGDATA_Msk &
                              (data << R_ESC_PHY_DATA_PHYREGDATA_Pos);
        p_reg_esc->MII_CONT_STAT = ETHERCAT_PHY_MII_CONT_STAT_WRITE_COMMAND << R_ESC_MII_CONT_STAT_COMMAND_Pos; // < Write command

        /* Start write access to the phy register and wait for completion. */
        FSP_HARDWARE_REGISTER_WAIT(p_reg_esc->MII_CONT_STAT_b.BUSY, 0U)
    }

    if (FSP_SUCCESS == err)
    {
        /* Check the error bit */
        if ((p_reg_esc->MII_CONT_STAT &
             R_ESC_MII_CONT_STAT_CMDERR_Msk))
        {
            /*  Error operation */
            err = FSP_ERR_INVALID_MODE;

            /* Clear error bit */
            p_reg_esc->MII_CONT_STAT_b.COMMAND = 0x0;
        }

        /* Give the access right to ECAT */
        p_reg_esc->MII_PDI_ACS_STAT_b.ACSMII = 0;
    }

    return err;
}

/* End of function R_ETHERCAT_PHY_Write() */

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHERCAT_PHY)
 **********************************************************************************************************************/

/**
 * Private functions
 */

/***********************************************************************************************************************
 * Function Name: ethercat_phy_targets_initialize
 * Description  : PHY-LSI specific initialization processing
 * Arguments    : p_instance_ctrl -
 *                    Ethercat control block
 * Return Value : none
 ***********************************************************************************************************************/
static void ethercat_phy_targets_initialize (ethercat_phy_instance_ctrl_t * p_instance_ctrl)
{
    switch (p_instance_ctrl->p_ether_phy_cfg->phy_lsi_type)
    {
        /* Use ICS1894 */
#if (ETHER_PHY_CFG_TARGET_ICS1894_ENABLE)
        case ETHER_PHY_LSI_TYPE_ICS1894:
        {
            ethercat_phy_target_ics1894_initialize(p_instance_ctrl);
            break;
        }
#endif

        /* User custom */
#if (ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE)
        case ETHER_PHY_LSI_TYPE_CUSTOM:
        {
            if (NULL != p_instance_ctrl->p_ether_phy_cfg->p_extend)
            {
                ether_phy_extended_cfg_t const * p_callback = p_instance_ctrl->p_ether_phy_cfg->p_extend;
                if (NULL != p_callback->p_target_init)
                {
                    p_callback->p_target_init(p_instance_ctrl);
                }
            }

            break;
        }
#endif

        /* If module is configured for default LSI */
        default:
        {
            break;
        }
    }
}                                      /* End of function ethercat_phy_targets_initialize() */

/***********************************************************************************************************************
 * Function Name: ethercat_phy_targets_is_support_link_partner_ability
 * Description  : Check if the PHY-LSI connected Ethercat controller supports link ability
 * Arguments    : p_instance_ctrl -
 *                    Ethercat control block
 *                line_speed_duplex -
 *                    Line speed duplex of link partner PHY-LSI
 * Return Value : bool
 ***********************************************************************************************************************/
static bool ethercat_phy_targets_is_support_link_partner_ability (ethercat_phy_instance_ctrl_t * p_instance_ctrl,
                                                                  uint32_t                       line_speed_duplex)
{
    bool result = false;
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    switch (p_instance_ctrl->p_ether_phy_cfg->phy_lsi_type)
    {
        /* Use ICS1894 */
#if (ETHER_PHY_CFG_TARGET_ICS1894_ENABLE)
        case ETHER_PHY_LSI_TYPE_ICS1894:
        {
            result = ethercat_phy_target_ics1894_is_support_link_partner_ability(p_instance_ctrl, line_speed_duplex);
            break;
        }
#endif

        /* User custom */
#if (ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE)
        case ETHER_PHY_LSI_TYPE_CUSTOM:
        {
            if (NULL != p_instance_ctrl->p_ether_phy_cfg->p_extend)
            {
                ether_phy_extended_cfg_t const * p_callback = p_instance_ctrl->p_ether_phy_cfg->p_extend;
                if (NULL != p_callback->p_target_link_partner_ability_get)
                {
                    result = p_callback->p_target_link_partner_ability_get(p_instance_ctrl, line_speed_duplex);
                }
            }

            break;
        }
#endif

        /* If module is configured for default LSI, always return true */
        default:
        {
            result = true;
            break;
        }
    }

    return result;
}                                      /* End of function ethercat_phy_targets_is_support_link_partner_ability() */
