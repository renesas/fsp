/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!********************************************************************************************************************
* \file             : r_sb_cmn.h
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : Does not depend on specific hardware
* \par Description  : This file defines the common macros, types and declarations for SB-Lib.
***********************************************************************************************************************/

#ifndef R_SB_CMN_H
/* Multiple inclusion protection macro */
#define R_SB_CMN_H

/*=====================================================================================================================
 Public macro definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBCommonDefinesInternal
 * \{******************************************************************/
#define SB_PRV_VERSION_MAJOR   (1UL)            /**< SB Library Major version */
#define SB_PRV_VERSION_MINOR   (0UL)            /**< SB Library Minor version */

/** Secure Boot function Flow verification counter Initial value */
#define SB_PRV_CMN_FC_SECUREBOOT_INIT           (0xEB536A03UL)
/** Count value for Secure Boot function flow verification */
#define SB_PRV_CMN_FC_SECUREBOOT_CNT            (0xB65FC3UL)
/** Number of times the Secure Boot function Flow verification count is add */
#define SB_PRV_CMN_FC_SECUREBOOT_NUM            (5UL)
/** Total add value of Secure Boot function flow verification count value */
#define SB_PRV_CMN_FC_SECUREBOOT_TOTAL_CNT      ((SB_PRV_CMN_FC_SECUREBOOT_CNT)*(SB_PRV_CMN_FC_SECUREBOOT_NUM))

/** CheckIntegrity function Flow verification counter Initial value */
#define SB_PRV_CMN_FC_CHECKINTEGRITY_INIT       (0xB5270907UL)
/** Count value for CheckIntegrity function flow verification */
#define SB_PRV_CMN_FC_CHECKINTEGRITY_CNT        (0xF29113UL)
/** Number of times the CheckIntegrity function Flow verification count is add */
#define SB_PRV_CMN_FC_CHECKINTEGRITY_NUM        (2UL)
/** Total add value of CheckIntegrity function flow verification count value */
#define SB_PRV_CMN_FC_CHECKINTEGRITY_TOTAL_CNT  ((SB_PRV_CMN_FC_CHECKINTEGRITY_CNT)*(SB_PRV_CMN_FC_CHECKINTEGRITY_NUM))

#define SB_PRV_REMAINDER_DIV4                   (0x3UL)             /**< Remainder of divided by 4 */
#define SB_PRV_REMAINDER_DIV16                  (0xFUL)             /**< Remainder of divided by 16 */

#define SB_PRV_TRUE  ((sb_bool_t)0x55555555UL) /**< True value. Defines a value other than 0/1 to prevent glitches */
#define SB_PRV_FALSE ((sb_bool_t)0xAAAAAAAAUL) /**< False value. Defines a value other than 0/1 to prevent glitches */
/*! \}*/


/*=====================================================================================================================
 Public type definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBCommonTypesInternal
 * \{******************************************************************/
typedef uint32_t sb_bool_t;                     /**< SB-Lib Boolean type */
/*! \}*/

/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/
extern volatile uint32_t g_sb_flow_counter;

/*=====================================================================================================================
 Public global functions
=====================================================================================================================*/
/**********************************************************************************************************************
* Function Name : r_sb_cmn_fc_sb_init
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Initialize SecureBoot flow counter \n
 *              This function is an inline function
 * \return
 *  - None
 * \par Global Variables
 *  - #g_sb_flow_counter
 *
 * \callgraph
 *********************************************************************************************************************/
static inline void r_sb_cmn_fc_sb_init(void)
{
    g_sb_flow_counter = SB_PRV_CMN_FC_SECUREBOOT_INIT;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_fc_sb_init()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_cmn_fc_ci_init
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Initialize CheckIntegrity flow counter \n
 *              This function is an inline function
 * \return
 *  - None
 * \par Global Variables
 *  - #g_sb_flow_counter
 *
 * \callgraph
 *********************************************************************************************************************/
static inline void r_sb_cmn_fc_ci_init(void)
{
    g_sb_flow_counter = SB_PRV_CMN_FC_CHECKINTEGRITY_INIT;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_fc_ci_init()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_cmn_fc_is_ci_flow_correct
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Check if the CheckIntegrity flow is correct \n
 *              This function is an inline function
 * \return
 *  - SB_PRV_TRUE: (#SB_PRV_CMN_FC_CHECKINTEGRITY_INIT + #SB_PRV_CMN_FC_CHECKINTEGRITY_TOTAL_CNT) == #g_sb_flow_counter
 *  - SB_PRV_FALSE:(#SB_PRV_CMN_FC_CHECKINTEGRITY_INIT + #SB_PRV_CMN_FC_CHECKINTEGRITY_TOTAL_CNT) != #g_sb_flow_counter
 * \par Global Variables
 *  - #g_sb_flow_counter
 *
 * \callgraph
 *********************************************************************************************************************/
static inline sb_bool_t r_sb_cmn_fc_is_ci_flow_correct(void)
{
    const uint32_t flow_counter = g_sb_flow_counter;
    return ((SB_PRV_CMN_FC_CHECKINTEGRITY_INIT + SB_PRV_CMN_FC_CHECKINTEGRITY_TOTAL_CNT) == flow_counter) ?
            SB_PRV_TRUE : SB_PRV_FALSE;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_fc_is_ci_flow_correct()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_cmn_fc_add_counter
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBCommonAPIsInternal
 * \brief       Add flow counter \n
 *              This function is an inline function
 * \param       [in]   cnt                 Flow counter value to be added
 * \return
 *  - None
 * \par Global Variables
 *  - #g_sb_flow_counter
 *
 * \callgraph
 *********************************************************************************************************************/
static inline void r_sb_cmn_fc_add_counter(const uint32_t cnt)
{
    g_sb_flow_counter += cnt;
}
/**********************************************************************************************************************
* End of function r_sb_cmn_fc_add_counter()
**********************************************************************************************************************/

#endif /* R_SB_CMN_H */
/*=====================================================================================================================
 End of File
=====================================================================================================================*/
