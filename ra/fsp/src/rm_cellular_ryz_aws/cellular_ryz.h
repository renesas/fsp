/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef CELLULAR_RYZ_H
#define CELLULAR_RYZ_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#include "cellular_platform.h"
#include "cellular_config.h"
#include "cellular_config_defaults.h"
#include "cellular_common.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS                    (4U) // MAX valid PDP contexts
#define RM_CELLULAR_RYZ_DEFAULT_BEARER_CONTEXT_ID           (1U)
#define RM_CELLULAR_RYZ_PDN_CONTEXT_TYPE_MAX_SIZE           (7U) // The length of IP type e.g. IPV4V6

/* +CGDCONT PDN context definition tokens */
#define RM_CELLULAR_RYZ_PDN_STATUS_POS_CONTEXT_ID           (0U)
#define RM_CELLULAR_RYZ_PDN_STATUS_POS_CONTEXT_TYPE         (1U)
#define RM_CELLULAR_RYZ_PDN_STATUS_POS_APN_NAME             (2U)
#define RM_CELLULAR_RYZ_PDN_STATUS_POS_IP_ADDRESS           (3U)

/* +CGACT PDN context activation tokens */
#define RM_CELLULAR_RYZ_PDN_ACT_STATUS_POS_CONTEXT_ID       (0U)
#define RM_CELLULAR_RYZ_PDN_ACT_STATUS_POS_CONTEXT_STATE    (1U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Context info from +CGDCONT (Context IP type, APN name, IP Address) */
typedef struct CellularPdnContextInfo
{
    bool contextsPresent[RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS];                                   // Context present in +CGDCONT response or not.
    char ipType[RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS][RM_CELLULAR_RYZ_PDN_CONTEXT_TYPE_MAX_SIZE]; // PDN Context type.
    char apnName[RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS][CELLULAR_APN_MAX_SIZE];                    // APN name.
    char ipAddress[RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS][CELLULAR_IP_ADDRESS_MAX_SIZE + 1];       // IP address.
} CellularPdnContextInfo_t;

/* Context Act state from +CGACT */
typedef struct CellularPdnContextActInfo
{
    bool contextsPresent[RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS]; // Context present in +CGACT response or not.
    bool contextActState[RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS]; // Context active state from +CGACT response.
} CellularPdnContextActInfo_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern CellularAtParseTokenMap_t cellular_urc_handler_table[];
extern uint32_t     cellular_urc_handler_table_size;
extern const char * CellularSrcTokenErrorTable[];
extern uint32_t     CellularSrcTokenErrorTableSize;
extern const char * CellularSrcTokenSuccessTable[];
extern uint32_t     CellularSrcTokenSuccessTableSize;
extern const char * CellularSrcExtraTokenSuccessTable[];
extern uint32_t     CellularSrcExtraTokenSuccessTableSize;
extern const char * CellularUrcTokenWoPrefixTable[];
extern uint32_t     CellularUrcTokenWoPrefixTableSize;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
