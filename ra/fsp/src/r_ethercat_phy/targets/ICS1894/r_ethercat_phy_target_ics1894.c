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

#if (ETHER_PHY_CFG_TARGET_ICS1894_ENABLE)

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Vendor Specific PHY Registers */
 #define ETHERCAT_PHY_REG_PHY_CONTROL_20    (0x14)
 #define ETHERCAT_PHY_CLEAR_LED             (0xffc0U)
 #define ETHERCAT_PHY_ACTIVATE_LED          (0x000dU)

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
void ethercat_phy_target_ics1894_initialize(ethercat_phy_instance_ctrl_t * p_instance_ctrl);
bool ethercat_phy_target_ics1894_is_support_link_partner_ability(ethercat_phy_instance_ctrl_t * p_instance_ctrl,
                                                                 uint32_t                       line_speed_duplex);

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: ethercat_phy_targets_initialize
 * Description  : PHY-LSI specific initialization processing
 * Arguments    : p_instance_ctrl -
 *                    Ethercat control block
 * Return Value : none
 ***********************************************************************************************************************/
void ethercat_phy_target_ics1894_initialize (ethercat_phy_instance_ctrl_t * p_instance_ctrl)
{
    uint32_t reg;

    /*
     * When ICS1894NL of the the Renesas Electronics Corporation. is used,
     * the pin that outputs the state of LINK is used combinedly with ACTIVITY in default.
     * The setting of the pin is changed so that only the state of LINK is output.
     */
    R_ETHERCAT_PHY_Read(p_instance_ctrl, ETHERCAT_PHY_REG_PHY_CONTROL_20, &reg);
    reg &= ETHERCAT_PHY_CLEAR_LED;     // LED0, LED1 Mode clear
    reg |= ETHERCAT_PHY_ACTIVATE_LED;  // LED1 Mode = activity/no activity, LED0 Mode = 100/10 mode (speed is used as link)
    R_ETHERCAT_PHY_Write(p_instance_ctrl, ETHERCAT_PHY_REG_PHY_CONTROL_20, reg);
}                                      /* End of function ethercat_phy_targets_initialize() */

/***********************************************************************************************************************
 * Function Name: ethercat_phy_targets_is_support_link_partner_ability
 * Description  : Check if the PHY-LSI connected Ethercat controller supports link ability
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 *                line_speed_duplex -
 *                    Line speed duplex of link partner PHY-LSI
 * Return Value : bool
 ***********************************************************************************************************************/
bool ethercat_phy_target_ics1894_is_support_link_partner_ability (ethercat_phy_instance_ctrl_t * p_instance_ctrl,
                                                                  uint32_t                       line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    bool ret = false;

    /* This PHY-LSI only supports full duplex mode. */
    switch (line_speed_duplex)
    {
        /* 10Mbps full duplex */
        case ETHER_PHY_LINK_SPEED_10F:
        {
            ret = true;
            break;
        }

        /* 100Mbps full duplex */
        case ETHER_PHY_LINK_SPEED_100F:
        {
            ret = true;
            break;
        }

        /* Half duplex is not supported */
        default:
        {
            break;
        }
    }

    return ret;
}                                      /* End of function ethercat_phy_targets_is_support_link_partner_ability() */

#endif /* ETHER_PHY_CFG_TARGET_ICS1894_ENABLE */
