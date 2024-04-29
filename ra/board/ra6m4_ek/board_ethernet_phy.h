/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup BOARD_RA6M4_EK
 * @defgroup BOARD_RA6M4_EK_ETHERNET_PHY Board Ethernet Phy
 * @brief Ethernet Phy information for this board.
 *
 * This is code specific to the RA6M4_EK board.
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
#define ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE    (1)
#define ETHER_PHY_LSI_TYPE_KIT_COMPONENT          ETHER_PHY_LSI_TYPE_KSZ8091RNB
#define BOARD_PHY_REF_CLK                         (1)

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

/** @} (end defgroup BOARD_RA6M4_EK_ETHERNET_PHY) */
