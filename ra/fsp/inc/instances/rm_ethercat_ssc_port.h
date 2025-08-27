/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_ETHERCAT_SSC_PORT
 * @{
 **********************************************************************************************************************/

#ifndef RM_ETHERCAT_SSC_PORT_H
#define RM_ETHERCAT_SSC_PORT_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ether_phy_api.h"
#include "rm_ethercat_ssc_port_cfg.h"
#include "rm_ethercat_ssc_port_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** EEPROM memory size of the EtherCAT */
typedef enum e_ethercat_ssc_port_eeprom_size
{
    ETHERCAT_SSC_PORT_EEPROM_SIZE_UNDER_32KBIT = 0, ///< Up to 16KBit
    ETHERCAT_SSC_PORT_EEPROM_SIZE_OVER_32KBIT  = 1, ///< 32KBit to 4MBit
} ethercat_ssc_port_eeprom_size_t;

/** Delay time of TX signal */
typedef enum e_ethercat_ssc_port_tx_signal_delay
{
    ETHERCAT_SSC_PORT_TX_SIGNAL_DELAY_00NS = 0, ///< 0 ns
    ETHERCAT_SSC_PORT_TX_SIGNAL_DELAY_10NS = 1, ///< 10 ns
    ETHERCAT_SSC_PORT_TX_SIGNAL_DELAY_20NS = 2, ///< 20 ns
    ETHERCAT_SSC_PORT_TX_SIGNAL_DELAY_30NS = 3, ///< 30 ns
} ethercat_ssc_port_tx_signal_delay_t;

/** EtherCAT SSC port control block. DO NOT INITIALIZE.  Initialization occurs when @ref ethercat_ssc_port_api_t::open is called. */
typedef struct st_ethercat_ssc_port_instance_ctrl
{
    uint32_t open;                         ///< Flag to indicate if EtherCAT SSC port instance has been initialized.
    uint16_t sys_time;                     ///< System time of EtherCAT Slave Controller.

    /* Configuration of EtherCAT SSC port module. */
    ethercat_ssc_port_cfg_t const * p_cfg; ///< Pointer to initial configurations.

    /* Interface for EtherCAT SSC port */
    R_ESC_INI_Type * p_reg_esc_ini;        ///< Pointer to EtherCAT Initial Configuration registers.
    R_ESC_Type     * p_reg_esc;            ///< Pointer to EtherCAT Slave Controller registers.
} ethercat_ssc_port_instance_ctrl_t;

/** Extended configuration */
typedef struct s_ethercat_ssc_port_extend_cfg
{
    ethercat_ssc_port_eeprom_size_t     eeprom_size;                              ///< EEPROM memory size.
    ethercat_ssc_port_tx_signal_delay_t tx_signal_delay_port0;                    ///< Port 0 TX signal delay time.
    ethercat_ssc_port_tx_signal_delay_t tx_signal_delay_port1;                    ///< Port 1 TX signal delay time.

    ether_phy_instance_t const * p_ether_phy_instance[BSP_FEATURE_ESC_NUM_PORTS]; ///< Pointer to ETHER_PHY instance.
} ethercat_ssc_port_extend_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ethercat_ssc_port_api_t g_ethercat_ssc_port_on_ethercat_ssc_port;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_ETHERCAT_SSC_PORT_Open(ethercat_ssc_port_ctrl_t * const      p_ctrl,
                                    ethercat_ssc_port_cfg_t const * const p_cfg);

fsp_err_t RM_ETHERCAT_SSC_PORT_Close(ethercat_ssc_port_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHERCAT_SSC_PORT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_ETHERCAT_SSC_PORT_H
