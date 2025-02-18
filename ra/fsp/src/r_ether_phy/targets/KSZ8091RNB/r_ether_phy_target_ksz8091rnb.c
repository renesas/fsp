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
#include "r_ether_phy.h"

#if (ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE)

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Vendor Specific PHY Registers */
 #define ETHER_PHY_REG_INTERRUPT_CONTROL                (0x1B)
 #define ETHER_PHY_REG_PHY_CONTROL2                     (0x1F)

 #define ETHER_PHY_REG_INTERRUPT_CONTROL_LUIE_OFFSET    (0x8)
 #define ETHER_PHY_REG_INTERRUPT_CONTROL_LDIE_OFFSET    (0xA)
 #define ETHER_PHY_REG_PHY_CONTROL2_RMII_RCS_OFFSET     (0x7)
 #define ETHER_PHY_REG_PHY_CONTROL2_RMII_IL_OFFSET      (0x9)

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
void ether_phy_target_ksz8091rnb_initialize(ether_phy_instance_ctrl_t * p_instance_ctrl);
bool ether_phy_target_ksz8091rnb_is_support_link_partner_ability(ether_phy_instance_ctrl_t * p_instance_ctrl,
                                                                 uint32_t                    line_speed_duplex);

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: ether_phy_targets_initialize
 * Description  : PHY-LSI specific initialization processing
 * Arguments    : p_api_ctrl -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
void ether_phy_target_ksz8091rnb_initialize (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    uint32_t reg;

    /* When KSZ8091RNB of the Micrel, Inc. is used.
     * This processing is a setting to use Link -up and Link-down as a factor of INTPR.
     * b10=1:Enable link-down interrupt
     * b8=1 :Enable link-up interrupt
     */
    R_ETHER_PHY_Write(p_instance_ctrl,
                      ETHER_PHY_REG_INTERRUPT_CONTROL,
                      (0x1 << ETHER_PHY_REG_INTERRUPT_CONTROL_LUIE_OFFSET | 0x1 <<
                       ETHER_PHY_REG_INTERRUPT_CONTROL_LDIE_OFFSET));
    R_ETHER_PHY_Read(p_instance_ctrl, ETHER_PHY_REG_INTERRUPT_CONTROL, &reg);
    R_ETHER_PHY_Read(p_instance_ctrl, ETHER_PHY_REG_PHY_CONTROL2, &reg);

    /* b7=1:RMII 50MHz clock mode; clock input to XI(pin 9) is 50MHz */
 #if (ETHER_PHY_CFG_USE_REF_CLK == 0)
    reg |= (0x1 << ETHER_PHY_REG_PHY_CONTROL2_RMII_RCS_OFFSET);
 #endif

    /* b9=0:Interrupt pin active low */
    reg &= (uint16_t) ~(0x1 << ETHER_PHY_REG_PHY_CONTROL2_RMII_IL_OFFSET);
    R_ETHER_PHY_Write(p_instance_ctrl, ETHER_PHY_REG_PHY_CONTROL2, reg);
}                                      /* End of function ether_phy_targets_initialize() */

/***********************************************************************************************************************
 * Function Name: ether_phy_targets_is_support_link_partner_ability
 * Description  : Check if the PHY-LSI connected Ethernet controller supports link ability
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 *                line_speed_duplex -
 *                    Line speed duplex of link partner PHY-LSI
 * Return Value : bool
 ***********************************************************************************************************************/
bool ether_phy_target_ksz8091rnb_is_support_link_partner_ability (ether_phy_instance_ctrl_t * p_instance_ctrl,
                                                                  uint32_t                    line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    /* This PHY-LSI supports half and full duplex mode. */
    return true;
}                                      /* End of function ether_phy_targets_is_support_link_partner_ability() */

#endif /* ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE */
