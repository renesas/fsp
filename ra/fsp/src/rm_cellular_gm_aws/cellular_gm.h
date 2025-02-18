/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CELLULAR_GM_H
#define CELLULAR_GM_H

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
#define RM_CELLULAR_GM_MAX_PDP_CONTEXTS                    (4U) // MAX valid PDP contexts
#define RM_CELLULAR_GM_DEFAULT_BEARER_CONTEXT_ID           (1U)
#define RM_CELLULAR_GM_PDN_CONTEXT_TYPE_MAX_SIZE           (7U) // The length of IP type e.g. IPV4V6

/* +CGDCONT PDN context definition tokens */
#define RM_CELLULAR_GM_PDN_STATUS_POS_CONTEXT_ID           (0U)
#define RM_CELLULAR_GM_PDN_STATUS_POS_CONTEXT_TYPE         (1U)
#define RM_CELLULAR_GM_PDN_STATUS_POS_APN_NAME             (2U)
#define RM_CELLULAR_GM_PDN_STATUS_POS_IP_ADDRESS           (3U)

/* +CGACT PDN context activation tokens */
#define RM_CELLULAR_GM_PDN_ACT_STATUS_POS_CONTEXT_ID       (0U)
#define RM_CELLULAR_GM_PDN_ACT_STATUS_POS_CONTEXT_STATE    (1U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Context info from +CGDCONT (Context IP type, APN name, IP Address) */
typedef struct CellularPdnContextInfo
{
    bool contextsPresent[RM_CELLULAR_GM_MAX_PDP_CONTEXTS];                                  // Context present in +CGDCONT response or not.
    char ipType[RM_CELLULAR_GM_MAX_PDP_CONTEXTS][RM_CELLULAR_GM_PDN_CONTEXT_TYPE_MAX_SIZE]; // PDN Context type.
    char apnName[RM_CELLULAR_GM_MAX_PDP_CONTEXTS][CELLULAR_APN_MAX_SIZE];                   // APN name.
    char ipAddress[RM_CELLULAR_GM_MAX_PDP_CONTEXTS][CELLULAR_IP_ADDRESS_MAX_SIZE + 1];      // IP address.
} CellularPdnContextInfo_t;

/* Context Act state from +CGACT */
typedef struct CellularPdnContextActInfo
{
    bool contextsPresent[RM_CELLULAR_GM_MAX_PDP_CONTEXTS]; // Context present in +CGACT response or not.
    bool contextActState[RM_CELLULAR_GM_MAX_PDP_CONTEXTS]; // Context active state from +CGACT response.
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
