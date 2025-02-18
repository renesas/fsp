/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Cellular module includes. */
#include "cellular_gm.h"

#include "cellular_types.h"
#include "cellular_common.h"
#include "cellular_common_api.h"
#include "cellular_common_portable.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void cellular_gm_urc_process_sqnsring(CellularContext_t * pContext, char * pInputLine);
static void cellular_gm_urc_process_sysstart(CellularContext_t * pContext, char * pInputLine);
static void cellular_gm_urc_process_shutdown(CellularContext_t * pContext, char * pInputLine);
static void cellular_gm_urc_process_socket_shutdown(CellularContext_t * pContext, char * pInputLine);

/* Remapping these common functions because function pointer in CellularAtParseTokenMap_t doesn't match */
static void cellular_gm_urc_process_cereg(CellularContext_t * pContext, char * pInputLine);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* URC mapping. Try to Keep this map in Alphabetical order.
 * Not currently supported, many of these would go through the generic callback if implemented:
 *      - SQNFGETREPORT
 *      - SQNFGETRING
 *      - SQNFPUT
 *      - SQNHTTPRING
 *      - SQNSMQTTONCONNECT
 *      - SQNSMQTTDISCONNECT
 *      - SQNSMQTTONPUBLISH
 *      - SQNSMQTTONMESSAGE
 *      - SQNSMQTTONSUBSCRIBE
 *      - SQNHWDT
 *      - SQNTMON
 *      - SQNFOTA
 *      - SQNSUPGRADE
 *      - SQNSMSSENDRES
 *      - SQNSIMST
 */
CellularAtParseTokenMap_t cellular_urc_handler_table[] =
{
    {"CEREG",    cellular_gm_urc_process_cereg          },
    {"SHUTDOWN", cellular_gm_urc_process_shutdown       }, // Power down completed, safe to turn cut power supply
    {"SQNSH",    cellular_gm_urc_process_socket_shutdown}, // Socket closed
    {"SQNSRING", cellular_gm_urc_process_sqnsring       }, // Socket notification (receive)
    {"SYSSTART", cellular_gm_urc_process_sysstart       }, // System start/restarted notification
};

uint32_t cellular_urc_handler_table_size = sizeof(cellular_urc_handler_table) / sizeof(CellularAtParseTokenMap_t);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

static void cellular_gm_urc_process_sqnsring (CellularContext_t * pContext, char * pInputLine)
{
    CellularATError_t         atCoreStatus    = CELLULAR_AT_SUCCESS;
    char                    * pLocalInputLine = pInputLine;
    char                    * pToken          = NULL;
    CellularSocketContext_t * pSocketData     = NULL;
    int32_t                   socketId        = 0;

    if ((pContext != NULL) && (pInputLine != NULL))
    {
        /* The inputline is in this format +SQNSRING:<connId> */
        atCoreStatus = Cellular_ATGetNextTok(&pLocalInputLine, &pToken);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            atCoreStatus = Cellular_ATStrtoi(pToken, 10, &socketId);
        }

        /* Call the callback function of this session. */
        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            pSocketData = _Cellular_GetSocketData(pContext, (uint32_t) socketId - 1);

            if (pSocketData == NULL)
            {
                LogError(("cellular_gm_urc_process_socket_shutdown : invalid socket index %d", (int) socketId - 1));
            }
            else
            {
                /* Indicate the upper layer about the data reception. */
                if (pSocketData->dataReadyCallback != NULL)
                {
                    pSocketData->dataReadyCallback(pSocketData, pSocketData->pDataReadyCallbackContext);
                }
                else
                {
                    LogDebug(("cellular_gm_urc_process_socket_shutdown: Data ready callback not set!!"));
                }
            }
        }
    }
}

static void cellular_gm_urc_process_socket_shutdown (CellularContext_t * pContext, char * pInputLine)
{
    CellularATError_t         atCoreStatus    = CELLULAR_AT_SUCCESS;
    char                    * pLocalInputLine = pInputLine;
    char                    * pToken          = NULL;
    CellularSocketContext_t * pSocketData     = NULL;
    int32_t                   socketId        = 0;

    if ((pContext != NULL) && (pInputLine != NULL))
    {
        /* The inputline is in this format +SQNSH:<connId> */
        atCoreStatus = Cellular_ATGetNextTok(&pLocalInputLine, &pToken);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            atCoreStatus = Cellular_ATStrtoi(pToken, 10, &socketId);
        }

        /* Call the callback function of this session. */
        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            pSocketData = _Cellular_GetSocketData(pContext, (uint32_t) socketId - 1);

            if (pSocketData == NULL)
            {
                LogError(("cellular_gm_urc_process_socket_shutdown : invalid socket index %d", (int) socketId - 1));
            }
            else
            {
                /* Indicate the upper layer about the data reception. */
                if (pSocketData->closedCallback != NULL)
                {
                    pSocketData->closedCallback(pSocketData, pSocketData->pClosedCallbackContext);
                }
                else
                {
                    LogDebug(("cellular_gm_urc_process_socket_shutdown: socket close callback not set!!"));
                }
            }
        }
    }
}

static void cellular_gm_urc_process_sysstart (CellularContext_t * pContext, char * pInputLine)
{
    /* The token is the pInputLine. No need to process the pInputLine. */
    FSP_PARAMETER_NOT_USED(pInputLine);

    if (pContext == NULL)
    {
        LogWarn(("cellular_gm_urc_process_sysstart: Context not set"));
    }
    else
    {
        LogDebug(("cellular_gm_urc_process_sysstart: Modem Ready event received"));
        _Cellular_ModemEventCallback(pContext, CELLULAR_MODEM_EVENT_BOOTUP_OR_REBOOT);
    }
}

static void cellular_gm_urc_process_shutdown (CellularContext_t * pContext, char * pInputLine)
{
    /* The token is the pInputLine. No need to process the pInputLine. */
    FSP_PARAMETER_NOT_USED(pInputLine);

    if (pContext == NULL)
    {
        LogWarn(("cellular_gm_urc_process_sqnsshdn: Context not set"));
    }
    else
    {
        LogDebug(("cellular_gm_urc_process_sqnsshdn: Modem Shutdown event received"));
        _Cellular_ModemEventCallback(pContext, CELLULAR_MODEM_EVENT_POWERED_DOWN);
    }
}

static void cellular_gm_urc_process_cereg (CellularContext_t * pContext, char * pInputLine)
{
    Cellular_CommonUrcProcessCereg(pContext, pInputLine);
}
