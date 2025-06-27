/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "cellular_gm.h"

#include "cellular_common.h"
#include "cellular_common_portable.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_CELLULAR_GM_ENABLE_MODULE_UE_RETRY_COUNT      (3U)
#define RM_CELLULAR_GM_ENABLE_MODULE_UE_RETRY_TIMEOUT    (5000U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

static CellularError_t sendAtCommandWithRetryTimeout(CellularContext_t * pContext, const CellularAtReq_t * pAtReq);

const char * CellularSrcTokenErrorTable[] =
{"ERROR", "BUSY", "NO CARRIER", "+CMS ERROR", "+CME ERROR"};
uint32_t CellularSrcTokenErrorTableSize = sizeof(CellularSrcTokenErrorTable) / sizeof(char *);

const char * CellularSrcTokenSuccessTable[]   = {"OK"};
uint32_t     CellularSrcTokenSuccessTableSize = sizeof(CellularSrcTokenSuccessTable) / sizeof(char *);

const char * CellularSrcExtraTokenSuccessTable[]   = {"> "};
uint32_t     CellularSrcExtraTokenSuccessTableSize = sizeof(CellularSrcExtraTokenSuccessTable) / sizeof(char *);

const char * CellularUrcTokenWoPrefixTable[]   = {"RDY", "+SHUTDOWN", "+SYSSTART"};
uint32_t     CellularUrcTokenWoPrefixTableSize = sizeof(CellularUrcTokenWoPrefixTable) / sizeof(char *);

/*******************************************************************************************************************//**
 * Implements Cellular_ModuleInit
 **********************************************************************************************************************/
CellularError_t Cellular_ModuleInit (const CellularContext_t * pContext, void ** ppModuleContext)
{
    CellularError_t cellular_status = CELLULAR_SUCCESS;

    if (pContext == NULL)
    {
        cellular_status = CELLULAR_INVALID_HANDLE;
    }
    else if (ppModuleContext == NULL)
    {
        cellular_status = CELLULAR_BAD_PARAMETER;
    }
    else
    {
        /* GM has no instance-specific module context. */
        *ppModuleContext = NULL;
    }

    return cellular_status;
}

/*******************************************************************************************************************//**
 * Implements Cellular_ModuleCleanUp
 **********************************************************************************************************************/
CellularError_t Cellular_ModuleCleanUp (const CellularContext_t * pContext)
{
    CellularError_t cellular_status = CELLULAR_SUCCESS;

    if (pContext == NULL)
    {
        cellular_status = CELLULAR_INVALID_HANDLE;
    }

    return cellular_status;
}

/*******************************************************************************************************************//**
 * Implements Cellular_ModuleEnableUE
 **********************************************************************************************************************/
CellularError_t Cellular_ModuleEnableUE (CellularContext_t * pContext)
{
    CellularError_t cellular_status  = CELLULAR_SUCCESS;
    CellularAtReq_t at_req_no_result =
    {
        NULL,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0
    };
    CellularAtReq_t at_req_with_result =
    {
        NULL,
        CELLULAR_AT_MULTI_WO_PREFIX,
        NULL,
        NULL,
        NULL,
        0
    };

    if (pContext != NULL)
    {
        /* Disable echo. */
        at_req_with_result.pAtCmd = "ATE0";
        cellular_status           = sendAtCommandWithRetryTimeout(pContext, &at_req_with_result);

        if (cellular_status == CELLULAR_SUCCESS)
        {
            /* Enable RTS/CTS hardware flow control. */
            at_req_no_result.pAtCmd = "AT+IFC=2,2";
            cellular_status         = sendAtCommandWithRetryTimeout(pContext, &at_req_no_result);
        }
    }

    return cellular_status;
}

/*******************************************************************************************************************//**
 * Implements Cellular_ModuleEnableUrc
 **********************************************************************************************************************/
CellularError_t Cellular_ModuleEnableUrc (CellularContext_t * pContext)
{
    CellularError_t cellular_status  = CELLULAR_SUCCESS;
    CellularAtReq_t at_req_no_result =
    {
        NULL,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0
    };

    /* Set operator format for PLMN command to numeric */
    at_req_no_result.pAtCmd = "AT+COPS=3,2";
    _Cellular_AtcmdRequestWithCallback(pContext, at_req_no_result);

    /* Enable CEREG URC with format +CEREG: <stat>[,[<tac>],[<ci>],[<AcT>]] */
    at_req_no_result.pAtCmd = "AT+CEREG=2";
    _Cellular_AtcmdRequestWithCallback(pContext, at_req_no_result);

    /* Enable CTZR */
    at_req_no_result.pAtCmd = "AT+CTZR=1";
    _Cellular_AtcmdRequestWithCallback(pContext, at_req_no_result);

    return cellular_status;
}

/*******************************************************************************************************************//**
 * Send AT command with retry timeout function.
 *
 * @param[in] pContext  Cellular context pointer
 * @param[in] pAtReq    Pointer to AT request
 *
 * @retval  CELLULAR_SUCCESS        AT command succeeded
 * @retval  CELLULAR_BAD_PARAMETER  Bad parameter passed in
 **********************************************************************************************************************/
static CellularError_t sendAtCommandWithRetryTimeout (CellularContext_t * pContext, const CellularAtReq_t * pAtReq)
{
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    uint8_t             tryCount       = 0;

    if (pAtReq == NULL)
    {
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else
    {
        for ( ; tryCount < RM_CELLULAR_GM_ENABLE_MODULE_UE_RETRY_COUNT; tryCount++)
        {
            pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                                  *pAtReq,
                                                                  RM_CELLULAR_GM_ENABLE_MODULE_UE_RETRY_TIMEOUT);
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);

            if (cellularStatus == CELLULAR_SUCCESS)
            {
                break;
            }
        }
    }

    return cellularStatus;
}
