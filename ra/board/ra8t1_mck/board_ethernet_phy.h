/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup BOARD_RA8D1_EK
 * @defgroup BOARD_RA8D1_EK_ETHERNET_PHY Board Ethernet Phy
 * @brief Ethernet Phy information for this board.
 *
 * This is code specific to the RA8D1_EK board.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_ETHERNET_PHY_H
#define BSP_ETHERNET_PHY_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ETHER_PHY_CFG_TARGET_ICS1894_ENABLE    (1)
#define ETHER_PHY_LSI_TYPE_KIT_COMPONENT       ETHER_PHY_LSI_TYPE_ICS1894
#define BOARD_PHY_REF_CLK                      (1)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public Functions
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/** @} (end defgroup BOARD_RA8D1_EK_ETHERNET_PHY) */
