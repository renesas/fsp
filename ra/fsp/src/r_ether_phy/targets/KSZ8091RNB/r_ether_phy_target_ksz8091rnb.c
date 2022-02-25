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

#if (ETHER_PHY_CFG_USE_PHY == ETHER_PHY_CFG_USE_PHY_KSZ8091RNB)

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
void            ether_phy_targets_initialize(ether_phy_instance_ctrl_t * p_instance_ctrl);
extern uint32_t ether_phy_read(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr);
extern void     ether_phy_write(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr, uint32_t data);

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
void ether_phy_targets_initialize (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    uint32_t reg;

    /* When KSZ8091RNB of the Micrel, Inc. is used.
     * This processing is a setting to use Link -up and Link-down as a factor of INTPR.
     * b10=1:Enable link-down interrupt
     * b8=1 :Enable link-up interrupt
     */
    ether_phy_write(p_instance_ctrl,
                    ETHER_PHY_REG_INTERRUPT_CONTROL,
                    (0x1 << ETHER_PHY_REG_INTERRUPT_CONTROL_LUIE_OFFSET | 0x1 <<
                     ETHER_PHY_REG_INTERRUPT_CONTROL_LDIE_OFFSET));
    ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_INTERRUPT_CONTROL);
    reg = ether_phy_read(p_instance_ctrl, ETHER_PHY_REG_PHY_CONTROL2);

    /* b7=1:RMII 50MHz clock mode; clock input to XI(pin 9) is 50MHz */
 #if (ETHER_PHY_CFG_USE_REF_CLK == 0)
    reg |= (0x1 << ETHER_PHY_REG_PHY_CONTROL2_RMII_RCS_OFFSET);
 #endif

    /* b9=0:Interrupt pin active low */
    reg &= (uint16_t) ~ETHER_PHY_REG_PHY_CONTROL2_RMII_IL_OFFSET;
    ether_phy_write(p_instance_ctrl, ETHER_PHY_REG_PHY_CONTROL2, reg);
}                                      /* End of function ether_phy_targets_initialize() */

#endif /* ETHER_PHY_CFG_USE_PHY == ETHER_PHY_CFG_USE_PHY_KSZ8091RNB */
