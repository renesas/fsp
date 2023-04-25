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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdio.h>

/* Cellular module includes. */
#include "cellular_ryz.h"

/* Cellular includes. */
#include "cellular_types.h"
#include "cellular_api.h"
#include "cellular_common_api.h"
#include "cellular_common.h"
#include "cellular_at_core.h"
#include "cellular_common_internal.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef RM_CELLULAR_RYZ_PDN_ACT_PACKET_REQ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_PDN_ACT_PACKET_REQ_TIMEOUT_MS              (150000UL)
#endif
#ifndef RM_CELLULAR_RYZ_PDN_DEACT_PACKET_REQ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_PDN_DEACT_PACKET_REQ_TIMEOUT_MS            (40000UL)
#endif
#ifndef RM_CELLULAR_RYZ_GPRS_ATTACH_REQ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_GPRS_ATTACH_REQ_TIMEOUT_MS                 (180000UL)
#endif
#ifndef RM_CELLULAR_RYZ_DNS_QUERY_REQ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_DNS_QUERY_REQ_TIMEOUT_MS                   (120000UL)
#endif
#ifndef RM_CELLULAR_RYZ_SOCKET_CONNECT_PACKET_REQ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_SOCKET_CONNECT_PACKET_REQ_TIMEOUT_MS       (120000U)
#endif
#ifndef RM_CELLULAR_RYZ_PACKET_REQ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_PACKET_REQ_TIMEOUT_MS                      (10000U)
#endif
#ifndef RM_CELLULAR_RYZ_DATA_SEND_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_DATA_SEND_TIMEOUT_MS                       (10000U)
#endif
#ifndef RM_CELLULAR_RYZ_DATA_SEND_INTER_DELAY_MS
 #define RM_CELLULAR_RYZ_DATA_SEND_INTER_DELAY_MS                   (200U)
#endif
#ifndef RM_CELLULAR_RYZ_DATA_READ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_DATA_READ_TIMEOUT_MS                       (50000UL)
#endif
#ifndef RM_CELLULAR_RYZ_SOCKET_DISCONNECT_PACKET_REQ_TIMEOUT_MS
 #define RM_CELLULAR_RYZ_SOCKET_DISCONNECT_PACKET_REQ_TIMEOUT_MS    (12000UL)
#endif

#define RM_CELLULAR_RYZ_SOCKET_DATA_PREFIX_TOKEN                    "+SQNSRECV: "
#define RM_CELLULAR_RYZ_SOCKET_DATA_PREFIX_TOKEN_LEN                (11U)
#define RM_CELLULAR_RYZ_SOCKET_DATA_PREFIX_STRING_LENGTH            (SOCKET_DATA_PREFIX_TOKEN_LEN + 6U)
#define RM_CELLULAR_RYZ_MAX_SQNSSRECV_STRING_PREFIX_STRING          (21U)            // The max data prefix string is "+SQNSRECV: 1,1500\r\n"
#define RM_CELLULAR_RYZ_DATA_PREFIX_STRING_CHANGELINE_LENGTH        (2U)             // The length of the change line "\r\n".
#define RM_CELLULAR_RYZ_GET_MODEM_SOCKET_ID(socket_id)    ((uint16_t) socket_id + 1) // Socket ID on modem starts at index 1
#define RM_CELLULAR_RYZ_CRSM_HPLMN_RAT_LENGTH                       (9U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct _socketDataRecv
{
    uint32_t * pDataLen;
    uint8_t  * pData;
} _socketDataRecv_t;

typedef struct cellularOperatorInfo
{
    CellularPlmnInfo_t                plmnInfo;            /* Device registered PLMN info (MCC and MNC).  */
    CellularRat_t                     rat;                 /* Device registered Radio Access Technology (Cat-M, Cat-NB, GPRS etc).  */
    CellularNetworkRegistrationMode_t networkRegMode;      /* Network Registered mode of the device (Manual, Auto etc).   */
    CellularOperatorNameFormat_t      operatorNameFormat;  /* Format of registered network operator name. */
    char operatorName[CELLULAR_NETWORK_NAME_MAX_SIZE + 1]; /* Registered network operator name. */
} cellularOperatorInfo_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static CellularError_t _Cellular_GetContextActivationStatus(CellularHandle_t              cellularHandle,
                                                            CellularPdnContextActInfo_t * pPdpContextsActInfo);
static CellularError_t     _Cellular_GetPacketSwitchStatus(CellularHandle_t cellularHandle, bool * pPacketSwitchStatus);
static CellularPktStatus_t _Cellular_RecvFuncGetPdpContextActState(CellularContext_t                 * pContext,
                                                                   const CellularATCommandResponse_t * pAtResp,
                                                                   void                              * pData,
                                                                   uint16_t                            dataLen);
static CellularPktStatus_t _Cellular_RecvFuncPacketSwitchStatus(CellularContext_t                 * pContext,
                                                                const CellularATCommandResponse_t * pAtResp,
                                                                void                              * pData,
                                                                uint16_t                            dataLen);
static CellularPktStatus_t _Cellular_RecvFuncGetPdpContextSettings(CellularContext_t                 * pContext,
                                                                   const CellularATCommandResponse_t * pAtResp,
                                                                   void                              * pData,
                                                                   uint16_t                            dataLen);
static CellularPktStatus_t _Cellular_RecvFuncGetSignalInfo(CellularContext_t                 * pContext,
                                                           const CellularATCommandResponse_t * pAtResp,
                                                           void                              * pData,
                                                           uint16_t                            dataLen);
static bool                _parseExtendedSignalQuality(char * pQcsqPayload, CellularSignalInfo_t * pSignalInfo);
static bool                _parseSignalQuality(char * pQcsqPayload, CellularSignalInfo_t * pSignalInfo);
static CellularPktStatus_t _Cellular_RecvFuncResolveDomainToIpAddress(CellularContext_t                 * pContext,
                                                                      const CellularATCommandResponse_t * pAtResp,
                                                                      void                              * pData,
                                                                      uint16_t                            dataLen);
static CellularPktStatus_t socketSendDataPrefix(void * pCallbackContext, char * pLine, uint32_t * pBytesRead);
static CellularPktStatus_t _Cellular_RecvFuncData(CellularContext_t                 * pContext,
                                                  const CellularATCommandResponse_t * pAtResp,
                                                  void                              * pData,
                                                  uint16_t                            dataLen);
static CellularATError_t getDataFromResp(const CellularATCommandResponse_t * pAtResp,
                                         const _socketDataRecv_t           * pDataRecv,
                                         uint32_t                            outBufSize);
static CellularPktStatus_t socketRecvDataPrefix(void     * pCallbackContext,
                                                char     * pLine,
                                                uint32_t   lineLength,
                                                char    ** ppDataStart,
                                                uint32_t * pDataLength);
static bool                _checkCrsmMemoryStatus(const char * pToken);
static bool                _checkCrsmReadStatus(const char * pToken);
static bool                _parseHplmn(char * pToken, void * pData);
static CellularPktStatus_t _Cellular_RecvFuncGetHplmn(CellularContext_t                 * pContext,
                                                      const CellularATCommandResponse_t * pAtResp,
                                                      void                              * pData,
                                                      uint16_t                            dataLen);
static CellularPktStatus_t _Cellular_RecvFuncGetIccid(CellularContext_t                 * pContext,
                                                      const CellularATCommandResponse_t * pAtResp,
                                                      void                              * pData,
                                                      uint16_t                            dataLen);
static CellularPktStatus_t _Cellular_RecvFuncGetImsi(CellularContext_t                 * pContext,
                                                     const CellularATCommandResponse_t * pAtResp,
                                                     void                              * pData,
                                                     uint16_t                            dataLen);
static CellularPktStatus_t _Cellular_RecvFuncGetNetworkReg(CellularContext_t                 * pContext,
                                                           const CellularATCommandResponse_t * pAtResp,
                                                           void                              * pData,
                                                           uint16_t                            dataLen);
static CellularPktStatus_t _Cellular_RecvFuncUpdateMccMnc(CellularContext_t                 * pContext,
                                                          const CellularATCommandResponse_t * pAtResp,
                                                          void                              * pData,
                                                          uint16_t                            dataLen);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Implementation of Cellular_Init */
CellularError_t Cellular_Init (CellularHandle_t * pCellularHandle, const CellularCommInterface_t * pCommInterface)
{
    CellularTokenTable_t cellularTokenTable =
    {
        .pCellularUrcHandlerTable              = cellular_urc_handler_table,
        .cellularPrefixToParserMapSize         = cellular_urc_handler_table_size,
        .pCellularSrcTokenErrorTable           = CellularSrcTokenErrorTable,
        .cellularSrcTokenErrorTableSize        = CellularSrcTokenErrorTableSize,
        .pCellularSrcTokenSuccessTable         = CellularSrcTokenSuccessTable,
        .cellularSrcTokenSuccessTableSize      = CellularSrcTokenSuccessTableSize,
        .pCellularUrcTokenWoPrefixTable        = CellularUrcTokenWoPrefixTable,
        .cellularUrcTokenWoPrefixTableSize     = CellularUrcTokenWoPrefixTableSize,
        .pCellularSrcExtraTokenSuccessTable    = CellularSrcExtraTokenSuccessTable,
        .cellularSrcExtraTokenSuccessTableSize = CellularSrcExtraTokenSuccessTableSize
    };

    return Cellular_CommonInit(pCellularHandle, pCommInterface, &cellularTokenTable);
}

/* Implementation of Cellular_GetSimCardStatus */
CellularError_t Cellular_GetSimCardStatus (CellularHandle_t cellularHandle, CellularSimCardStatus_t * pSimCardStatus)
{
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;

    /* pContext is checked in _Cellular_CheckLibraryStatus function. */
    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogDebug(("Cellular_GetSimCardStatus : _Cellular_CheckLibraryStatus failed"));
    }
    else if (pSimCardStatus == NULL)
    {
        LogWarn(("Cellular_GetSimCardStatus : Bad input Parameter"));
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else
    {
        /* Parameters are checked in this API. */
        pSimCardStatus->simCardState     = CELLULAR_SIM_CARD_UNKNOWN;
        pSimCardStatus->simCardLockState = CELLULAR_SIM_CARD_LOCK_UNKNOWN;

        cellularStatus = Cellular_CommonGetSimCardLockStatus(cellularHandle, pSimCardStatus);

        if (cellularStatus == CELLULAR_SUCCESS)
        {
            if ((pSimCardStatus->simCardLockState != CELLULAR_SIM_CARD_INVALID) &&
                (pSimCardStatus->simCardLockState != CELLULAR_SIM_CARD_LOCK_UNKNOWN))
            {
                pSimCardStatus->simCardState = CELLULAR_SIM_CARD_INSERTED;
            }
            else
            {
                pSimCardStatus->simCardState = CELLULAR_SIM_CARD_UNKNOWN;
            }
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_GetSimCardInfo */
CellularError_t Cellular_GetSimCardInfo (CellularHandle_t cellularHandle, CellularSimCardInfo_t * pSimCardInfo)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    CellularAtReq_t     atReqGetIccid  = {0};
    CellularAtReq_t     atReqGetImsi   = {0};
    CellularAtReq_t     atReqGetHplmn  = {0};

    atReqGetIccid.pAtCmd       = "AT+SQNCCID?";
    atReqGetIccid.atCmdType    = CELLULAR_AT_WITH_PREFIX;
    atReqGetIccid.pAtRspPrefix = "+SQNCCID";
    atReqGetIccid.respCallback = _Cellular_RecvFuncGetIccid;
    atReqGetIccid.pData        = pSimCardInfo->iccid;
    atReqGetIccid.dataLen      = CELLULAR_ICCID_MAX_SIZE + 1U;

    atReqGetImsi.pAtCmd       = "AT+CIMI";
    atReqGetImsi.atCmdType    = CELLULAR_AT_WO_PREFIX;
    atReqGetImsi.pAtRspPrefix = NULL;
    atReqGetImsi.respCallback = _Cellular_RecvFuncGetImsi;
    atReqGetImsi.pData        = pSimCardInfo->imsi;
    atReqGetImsi.dataLen      = CELLULAR_IMSI_MAX_SIZE + 1U;

    atReqGetHplmn.pAtCmd       = "AT+CRSM=176,28514,0,0,0"; /* READ BINARY commmand. HPLMN Selector with Access Technology( 6F62 ). */
    atReqGetHplmn.atCmdType    = CELLULAR_AT_WITH_PREFIX;
    atReqGetHplmn.pAtRspPrefix = "+CRSM";
    atReqGetHplmn.respCallback = _Cellular_RecvFuncGetHplmn;
    atReqGetHplmn.pData        = &pSimCardInfo->plmn;
    atReqGetHplmn.dataLen      = (uint16_t) sizeof(CellularPlmnInfo_t);

    /* pContext is checked in _Cellular_CheckLibraryStatus function. */
    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogError(("_Cellular_CheckLibraryStatus failed"));
    }
    else if (pSimCardInfo == NULL)
    {
        LogError(("Cellular_GetSimCardInfo : Bad parameter"));
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else
    {
        (void) memset(pSimCardInfo, 0, sizeof(CellularSimCardInfo_t));
        pktStatus = _Cellular_AtcmdRequestWithCallback(pContext, atReqGetImsi);

        if (pktStatus == CELLULAR_PKT_STATUS_OK)
        {
            pktStatus = _Cellular_AtcmdRequestWithCallback(pContext, atReqGetHplmn);
        }

        if (pktStatus == CELLULAR_PKT_STATUS_OK)
        {
            pktStatus = _Cellular_AtcmdRequestWithCallback(pContext, atReqGetIccid);
        }

        if (pktStatus != CELLULAR_PKT_STATUS_OK)
        {
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
        }
        else
        {
            LogDebug(("SimInfo updated: IMSI:%s, Hplmn:%s%s, ICCID:%s",
                      pSimCardInfo->imsi, pSimCardInfo->plmn.mcc, pSimCardInfo->plmn.mnc,
                      pSimCardInfo->iccid));
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_GetPdnStatus */
CellularError_t Cellular_GetPdnStatus (CellularHandle_t      cellularHandle,
                                       CellularPdnStatus_t * pPdnStatusBuffers,
                                       uint8_t               numStatusBuffers,
                                       uint8_t             * pNumStatus)
{
    CellularContext_t         * pContext           = (CellularContext_t *) cellularHandle;
    CellularError_t             cellularStatus     = CELLULAR_SUCCESS;
    CellularPktStatus_t         pktStatus          = CELLULAR_PKT_STATUS_OK;
    CellularPdnContextActInfo_t pdpContextsActInfo = {0};
    CellularPdnContextInfo_t    pdpContextsInfo    = {0};
    *pNumStatus = 0;

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Make sure the library is open. */
        cellularStatus = _Cellular_CheckLibraryStatus(pContext);
    }

    if ((pPdnStatusBuffers == NULL) || (pNumStatus == NULL) || (numStatusBuffers < 1))
    {
        cellularStatus = CELLULAR_BAD_PARAMETER;
        LogWarn(("_Cellular_GetPdnStatus: Bad input Parameter "));
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Check the current <Act> status of contexts. */
        cellularStatus = _Cellular_GetContextActivationStatus(cellularHandle, &pdpContextsActInfo);

        if (cellularStatus == CELLULAR_SUCCESS)
        {
            /* Get PDP config info */
            CellularAtReq_t atReqGetCurrentApnName =
            {
                "AT+CGDCONT?",
                CELLULAR_AT_MULTI_WITH_PREFIX,
                "+CGDCONT",
                _Cellular_RecvFuncGetPdpContextSettings,
                &pdpContextsInfo,
                sizeof(CellularPdnContextInfo_t),
            };

            pktStatus      = _Cellular_AtcmdRequestWithCallback(pContext, atReqGetCurrentApnName);
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);

            if (cellularStatus == CELLULAR_SUCCESS)
            {
                for (uint8_t i = 0; i < RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS; i++)
                {
                    if (*pNumStatus == numStatusBuffers)
                    {
                        /* stop if the number of status buffers has been filled */
                        break;
                    }

                    if (pdpContextsInfo.contextsPresent[i] && pdpContextsActInfo.contextsPresent[i])
                    {
                        /* Set CID */
                        pPdnStatusBuffers[i].contextId = (uint8_t) (i + 1);

                        /* Get IP Address */
                        cellularStatus = Cellular_GetIPAddress(cellularHandle,
                                                               (uint8_t) (i + 1),
                                                               pPdnStatusBuffers[i].ipAddress.ipAddress,
                                                               CELLULAR_IP_ADDRESS_MAX_SIZE + 1);

                        if (cellularStatus != CELLULAR_SUCCESS)
                        {
                            break;
                        }

                        /* Set IP type */
                        if (0 == strcmp(pdpContextsInfo.ipType[i], "IPV4"))
                        {
                            pPdnStatusBuffers[i].ipAddress.ipAddressType = CELLULAR_IP_ADDRESS_V4;
                            pPdnStatusBuffers[i].pdnContextType          = CELLULAR_PDN_CONTEXT_IPV4;
                        }
                        else if (0 == strcmp(pdpContextsInfo.ipType[i], "IPV6"))
                        {
                            pPdnStatusBuffers[i].ipAddress.ipAddressType = CELLULAR_IP_ADDRESS_V6;
                            pPdnStatusBuffers[i].pdnContextType          = CELLULAR_PDN_CONTEXT_IPV6;
                        }
                        else
                        {
                            pPdnStatusBuffers[i].ipAddress.ipAddressType = CELLULAR_IP_ADDRESS_V4;
                            pPdnStatusBuffers[i].pdnContextType          = CELLULAR_PDN_CONTEXT_IPV4V6;
                        }

                        /* Set activation state */
                        LogDebug(("Context [%d], Act State [%d]\r\n", i + 1,
                                  pdpContextsActInfo.contextActState[i]));
                        pPdnStatusBuffers[i].state = pdpContextsActInfo.contextActState[i];

                        (*pNumStatus)++;
                    }
                }
            }
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_ActivatePdn */
CellularError_t Cellular_ActivatePdn (CellularHandle_t cellularHandle, uint8_t contextId)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    char                cmdBuf[CELLULAR_AT_CMD_MAX_SIZE] = {'\0'};

    CellularPdnContextActInfo_t pdpContextsActInfo = {0};

    CellularAtReq_t atReqActPdn =
    {
        cmdBuf,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0,
    };

    cellularStatus = _Cellular_IsValidPdn(contextId);

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Make sure the library is open. */
        cellularStatus = _Cellular_CheckLibraryStatus(pContext);
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Check the current <Act> status of context. If not activated, activate the PDN context ID. */
        cellularStatus = _Cellular_GetContextActivationStatus(cellularHandle, &pdpContextsActInfo);

        /* Activate context if not already active */
        if (pdpContextsActInfo.contextActState[contextId - 1] == false)
        {
            if (pktStatus == CELLULAR_PKT_STATUS_OK)
            {
                (void) snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "%s=1,%u", "AT+CGACT", contextId);
                pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                                      atReqActPdn,
                                                                      RM_CELLULAR_RYZ_PDN_ACT_PACKET_REQ_TIMEOUT_MS);
            }

            if (pktStatus != CELLULAR_PKT_STATUS_OK)
            {
                LogError(("Cellular_ActivatePdn: can't activate PDN, PktRet: %d", pktStatus));
                cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
            }
        }
        else
        {
            LogInfo(("Cellular_ActivatePdn: Context id [%d] is already active", contextId));
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_DeactivatePdn */
CellularError_t Cellular_DeactivatePdn (CellularHandle_t cellularHandle, uint8_t contextId)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    char                cmdBuf[CELLULAR_AT_CMD_MAX_SIZE] = {'\0'};
    bool                packetSwitchStatus               = false;

    CellularServiceStatus_t     serviceStatus;
    CellularPdnContextActInfo_t pdpContextsActInfo = {0};

    CellularAtReq_t atReqDeactPdn =
    {
        cmdBuf,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0,
    };

    memset(&serviceStatus, 0, sizeof(serviceStatus));

    cellularStatus = _Cellular_IsValidPdn(contextId);

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Make sure the library is open. */
        cellularStatus = _Cellular_CheckLibraryStatus(pContext);
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Get current network operator settings. */
        cellularStatus = Cellular_GetServiceStatus(cellularHandle, &serviceStatus);

        if (cellularStatus == CELLULAR_SUCCESS)
        {
            /* Check the current <Act> status of context. */
            cellularStatus = _Cellular_GetContextActivationStatus(cellularHandle, &pdpContextsActInfo);
        }

        if (cellularStatus == CELLULAR_SUCCESS)
        {
            LogDebug(("Cellular_DeactivatePdn: Listing operator and context details below."));

            /* Deactivate context if active */
            if (pdpContextsActInfo.contextActState[contextId - 1] == true)
            {
                /* Don't deactivate LTE default bearer context */
                /* Otherwise sending AT command "+CGACT=0,1" for deactivation will result in ERROR */
                if ((serviceStatus.rat >= CELLULAR_RAT_LTE) && (contextId == RM_CELLULAR_RYZ_DEFAULT_BEARER_CONTEXT_ID))
                {
                    LogInfo(("Cellular_DeactivatePdn: Default Bearer context %d Active. Not allowed to deactivate.",
                             contextId));
                    cellularStatus = CELLULAR_NOT_ALLOWED;
                }
                else
                {
                    (void) snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "%s=0,%u", "AT+CGACT", contextId);
                    pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                                          atReqDeactPdn,
                                                                          RM_CELLULAR_RYZ_PDN_DEACT_PACKET_REQ_TIMEOUT_MS);
                    cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
                }

                if ((cellularStatus != CELLULAR_SUCCESS) && (cellularStatus != CELLULAR_NOT_ALLOWED))
                {
                    LogError(("Cellular_DeactivatePdn: can't deactivate PDN, PktRet: %d", pktStatus));

                    /* Sometimes +CGACT deactivation fails in 2G. Then check packet switch attach. If attached, detach packet switch. */
                    if ((serviceStatus.rat == CELLULAR_RAT_GSM) || (serviceStatus.rat == CELLULAR_RAT_EDGE))
                    {
                        cellularStatus = _Cellular_GetPacketSwitchStatus(cellularHandle, &packetSwitchStatus);

                        if ((cellularStatus == CELLULAR_SUCCESS) && (packetSwitchStatus == true))
                        {
                            LogError(("Deactivate Packet switch"));
                            (void) snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "%s", "AT+CGATT=0");
                            pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                                                  atReqDeactPdn,
                                                                                  RM_CELLULAR_RYZ_GPRS_ATTACH_REQ_TIMEOUT_MS);
                            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
                        }
                        else if (cellularStatus != CELLULAR_SUCCESS)
                        {
                            LogError(("Packet switch query failed"));
                            pktStatus      = CELLULAR_PKT_STATUS_FAILURE;
                            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
                        }
                        else
                        {
                            LogInfo(("Packet switch detached"));
                        }
                    }
                }
            }
            else
            {
                LogInfo(("Cellular_DeactivatePdn: Context id [%d] is already deactive", contextId));
            }
        }
        else
        {
            LogError(("Cellular_DeactivatePdn: Unable to list operator and context details."));
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_GetSignalInfo */
CellularError_t Cellular_GetSignalInfo (CellularHandle_t cellularHandle, CellularSignalInfo_t * pSignalInfo)
{
    CellularContext_t * pContext             = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus       = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus            = CELLULAR_PKT_STATUS_OK;
    CellularRat_t       rat                  = CELLULAR_RAT_INVALID;
    CellularAtReq_t     atReqQuerySignalInfo =
    {
        "AT+CSQ",
        CELLULAR_AT_WITH_PREFIX,
        "+CSQ",
        _Cellular_RecvFuncGetSignalInfo,
        pSignalInfo,
        sizeof(CellularSignalInfo_t),
    };
    CellularAtReq_t atReqQueryExtendedSignalInfo =
    {
        "AT+CESQ",
        CELLULAR_AT_WITH_PREFIX,
        "+CESQ",
        _Cellular_RecvFuncGetSignalInfo,
        pSignalInfo,
        sizeof(CellularSignalInfo_t),
    };

    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogDebug(("Cellular_GetSignalInfo: _Cellular_CheckLibraryStatus failed"));
    }
    else if (pSignalInfo == NULL)
    {
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else
    {
        cellularStatus = _Cellular_GetCurrentRat(pContext, &rat);
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Get +CSQ response */
        pktStatus = _Cellular_AtcmdRequestWithCallback(pContext, atReqQuerySignalInfo);

        if (pktStatus == CELLULAR_PKT_STATUS_OK)
        {
            /* Get +CESQ response */
            pktStatus = _Cellular_AtcmdRequestWithCallback(pContext, atReqQueryExtendedSignalInfo);

            if (pktStatus == CELLULAR_PKT_STATUS_OK)
            {
                /* If the convert failed, the API will return CELLULAR_INVALID_SIGNAL_BAR_VALUE in bars field. */
                (void) _Cellular_ComputeSignalBars(rat, pSignalInfo);
            }

            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_GetHostByName */
CellularError_t Cellular_GetHostByName (CellularHandle_t cellularHandle,
                                        uint8_t          contextId,
                                        const char     * pcHostName,
                                        char           * pResolvedAddress)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    char                cmdBuf[CELLULAR_AT_CMD_MAX_SIZE] = {'\0'};

    CellularAtReq_t atReqQueryDns =
    {
        cmdBuf,
        CELLULAR_AT_MULTI_WITH_PREFIX,
        "+SQNDNSLKUP",
        _Cellular_RecvFuncResolveDomainToIpAddress,
        pResolvedAddress,
        CELLULAR_IP_ADDRESS_MAX_SIZE,
    };

    FSP_PARAMETER_NOT_USED(contextId);

    /* pContext is checked in _Cellular_CheckLibraryStatus function. */
    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogDebug(("Cellular_GetHostByName: _Cellular_CheckLibraryStatus failed"));
    }
    else
    {
        if ((pcHostName == NULL) || (pResolvedAddress == NULL))
        {
            LogError(("Cellular_GetHostByName: Bad input Parameter "));
            cellularStatus = CELLULAR_BAD_PARAMETER;
        }
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        (void) snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "AT+SQNDNSLKUP=\"%s\"", pcHostName);

        pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                              atReqQueryDns,
                                                              RM_CELLULAR_RYZ_DNS_QUERY_REQ_TIMEOUT_MS);

        if (pktStatus != CELLULAR_PKT_STATUS_OK)
        {
            LogError(("Cellular_GetHostByName: couldn't resolve host name"));
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_SocketConnect */
CellularError_t Cellular_SocketConnect (CellularHandle_t                cellularHandle,
                                        CellularSocketHandle_t          socketHandle,
                                        CellularSocketAccessMode_t      dataAccessMode,
                                        const CellularSocketAddress_t * pRemoteSocketAddress)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    char                cmdBuf[CELLULAR_AT_CMD_MAX_SIZE] = {'\0'};
    CellularAtReq_t     atReqSocketConnect               =
    {
        cmdBuf,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0,
    };
    CellularSocketOpenCallback_t openCallback = NULL;

    /* Make sure the library is open. */
    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogDebug(("Cellular_SocketConnect: _Cellular_CheckLibraryStatus failed"));
    }
    else if (pRemoteSocketAddress == NULL)
    {
        LogDebug(("Cellular_SocketConnect: Invalid socket address"));
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else if (socketHandle == NULL)
    {
        LogDebug(("Cellular_SocketConnect: Invalid socket handle"));
        cellularStatus = CELLULAR_INVALID_HANDLE;
    }
    else
    {
        if (socketHandle->socketState != SOCKETSTATE_ALLOCATED)
        {
            LogError(("storeAccessModeAndAddress, bad socket state %d",
                      socketHandle->socketState));
            cellularStatus = CELLULAR_INTERNAL_FAILURE;
        }
        else if (dataAccessMode != CELLULAR_ACCESSMODE_BUFFER)
        {
            LogError(("storeAccessModeAndAddress, Access mode not supported %d",
                      dataAccessMode));
            cellularStatus = CELLULAR_UNSUPPORTED;
        }
        else
        {
            socketHandle->remoteSocketAddress.port = pRemoteSocketAddress->port;
            socketHandle->dataMode                 = dataAccessMode;
            socketHandle->remoteSocketAddress.ipAddress.ipAddressType =
                pRemoteSocketAddress->ipAddress.ipAddressType;
            (void) strncpy(socketHandle->remoteSocketAddress.ipAddress.ipAddress,
                           pRemoteSocketAddress->ipAddress.ipAddress,
                           CELLULAR_IP_ADDRESS_MAX_SIZE + 1U);

            if (socketHandle->openCallback != NULL)
            {
                openCallback = socketHandle->openCallback;
            }
        }
    }

    /* Configure the socket. */
    if (cellularStatus == CELLULAR_SUCCESS)
    {
        snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "AT+SQNSCFG=%u,%d,0,90,600,50",
                 RM_CELLULAR_RYZ_GET_MODEM_SOCKET_ID(socketHandle->socketId), socketHandle->contextId);

        pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                              atReqSocketConnect,
                                                              RM_CELLULAR_RYZ_SOCKET_CONNECT_PACKET_REQ_TIMEOUT_MS);

        if (pktStatus == CELLULAR_PKT_STATUS_OK)
        {
            snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "AT+SQNSCFGEXT=%u,0,0,0",
                     RM_CELLULAR_RYZ_GET_MODEM_SOCKET_ID(socketHandle->socketId));

            pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                                  atReqSocketConnect,
                                                                  RM_CELLULAR_RYZ_SOCKET_CONNECT_PACKET_REQ_TIMEOUT_MS);

            if (pktStatus != CELLULAR_PKT_STATUS_OK)
            {
                LogError(("Cellular_SocketConnect: Socket configure failed, cmdBuf:%s, PktRet: %d", cmdBuf, pktStatus));
                cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
            }
        }
        else
        {
            LogError(("Cellular_SocketConnect: Socket configure failed, cmdBuf:%s, PktRet: %d", cmdBuf, pktStatus));
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
        }
    }

    /* Start the connection. */
    if (cellularStatus == CELLULAR_SUCCESS)
    {
        uint8_t protocol = (CELLULAR_SOCKET_PROTOCOL_TCP == socketHandle->socketProtocol) ? 0 : 1;

        snprintf(cmdBuf,
                 CELLULAR_AT_CMD_MAX_SIZE,
                 "AT+SQNSD=%u,%d,%d,\"%s\",0,%d,1,0",
                 RM_CELLULAR_RYZ_GET_MODEM_SOCKET_ID(socketHandle->socketId),
                 protocol,
                 socketHandle->remoteSocketAddress.port,
                 socketHandle->remoteSocketAddress.ipAddress.ipAddress,
                 socketHandle->localPort);

        pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                              atReqSocketConnect,
                                                              RM_CELLULAR_RYZ_SOCKET_CONNECT_PACKET_REQ_TIMEOUT_MS);

        if (pktStatus != CELLULAR_PKT_STATUS_OK)
        {
            LogError(("Cellular_SocketConnect: Socket connect failed, cmdBuf:%s, PktRet: %d", cmdBuf, pktStatus));
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
        }
        else
        {
            socketHandle->socketState = SOCKETSTATE_CONNECTED;
        }
    }

    /* Call callback */
    if (openCallback != NULL)
    {
        if (CELLULAR_SUCCESS == cellularStatus)
        {
            openCallback(CELLULAR_URC_SOCKET_OPENED, socketHandle, socketHandle->pOpenCallbackContext);
        }
        else
        {
            openCallback(CELLULAR_URC_SOCKET_OPEN_FAILED, socketHandle, socketHandle->pOpenCallbackContext);
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_SocketSend */
CellularError_t Cellular_SocketSend (CellularHandle_t       cellularHandle,
                                     CellularSocketHandle_t socketHandle,
                                     const uint8_t        * pData,
                                     uint32_t               dataLength,
                                     uint32_t             * pSentDataLength)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    uint32_t            sendTimeout    = RM_CELLULAR_RYZ_DATA_SEND_TIMEOUT_MS;
    char                cmdBuf[CELLULAR_AT_CMD_MAX_SIZE] = {'\0'};
    CellularAtReq_t     atReqSocketSend =
    {
        cmdBuf,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0,
    };
    CellularAtDataReq_t atDataReqSocketSend =
    {
        pData,
        dataLength,
        pSentDataLength,
        NULL,
        0
    };

    /* pContext is checked in _Cellular_CheckLibraryStatus function. */
    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogDebug(("Cellular_SocketSend: _Cellular_CheckLibraryStatus failed"));
    }
    else if (socketHandle == NULL)
    {
        cellularStatus = CELLULAR_INVALID_HANDLE;
    }
    else if ((pData == NULL) || (pSentDataLength == NULL) || (dataLength == 0U))
    {
        LogDebug(("Cellular_SocketSend: Invalid parameter"));
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else if (socketHandle->socketState != SOCKETSTATE_CONNECTED)
    {
        /* Check the socket connection state. */
        if ((socketHandle->socketState == SOCKETSTATE_ALLOCATED) ||
            (socketHandle->socketState == SOCKETSTATE_CONNECTING))
        {
            cellularStatus = CELLULAR_SOCKET_NOT_CONNECTED;
        }
        else
        {
            cellularStatus = CELLULAR_SOCKET_CLOSED;
        }
    }
    else
    {
        /* Send data length check. */
        if (dataLength > (uint32_t) CELLULAR_MAX_SEND_DATA_LEN)
        {
            atDataReqSocketSend.dataLen = (uint32_t) CELLULAR_MAX_SEND_DATA_LEN;
        }

        /* Check send timeout. If not set by setsockopt, use default value. */
        if (socketHandle->sendTimeoutMs != 0U)
        {
            sendTimeout = socketHandle->sendTimeoutMs;
        }

        snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "AT+SQNSSENDEXT=%u,%u",
                 RM_CELLULAR_RYZ_GET_MODEM_SOCKET_ID(socketHandle->socketId), (uint16_t) atDataReqSocketSend.dataLen);

        pktStatus = _Cellular_AtcmdDataSend(pContext,
                                            atReqSocketSend,
                                            atDataReqSocketSend,
                                            socketSendDataPrefix,
                                            NULL,
                                            RM_CELLULAR_RYZ_PACKET_REQ_TIMEOUT_MS,
                                            sendTimeout,
                                            RM_CELLULAR_RYZ_DATA_SEND_INTER_DELAY_MS);

        if (pktStatus != CELLULAR_PKT_STATUS_OK)
        {
            if (socketHandle->socketState == SOCKETSTATE_DISCONNECTED)
            {
                LogInfo(("Cellular_SocketSend: Data send fail, socket already closed"));
                cellularStatus = CELLULAR_SOCKET_CLOSED;
            }
            else
            {
                LogError(("Cellular_SocketSend: Data send fail, PktRet: %d", pktStatus));
                cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
            }
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_SocketRecv */
CellularError_t Cellular_SocketRecv (CellularHandle_t       cellularHandle,
                                     CellularSocketHandle_t socketHandle,
                                     uint8_t              * pBuffer,
                                     uint32_t               bufferLength,
                                     uint32_t             * pReceivedDataLength)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    char                cmdBuf[CELLULAR_AT_CMD_MAX_SIZE] = {'\0'};
    uint32_t            recvTimeout     = RM_CELLULAR_RYZ_DATA_READ_TIMEOUT_MS;
    uint32_t            recvLen         = bufferLength;
    _socketDataRecv_t   dataRecv        = {0};
    CellularAtReq_t     atReqSocketRecv =
    {
        cmdBuf,
        CELLULAR_AT_MULTI_DATA_WO_PREFIX,
        "+SQNSRECV",
        _Cellular_RecvFuncData,
        (void *) &dataRecv,
        (uint16_t) bufferLength,
    };

    dataRecv.pDataLen = pReceivedDataLength;
    dataRecv.pData    = pBuffer;

    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogDebug(("Cellular_SocketRecv: _Cellular_CheckLibraryStatus failed"));
    }
    else if (socketHandle == NULL)
    {
        cellularStatus = CELLULAR_INVALID_HANDLE;
    }
    else if ((pBuffer == NULL) || (pReceivedDataLength == NULL) || (bufferLength == 0U))
    {
        LogDebug(("Cellular_SocketRecv: Bad input Param"));
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else
    {
        /* Update recvLen to maximum module length. */
        if (CELLULAR_MAX_RECV_DATA_LEN <= bufferLength)
        {
            recvLen = (uint32_t) CELLULAR_MAX_RECV_DATA_LEN;
        }

        if (recvLen > 0)
        {
            /* Update receive timeout to default timeout if not set with setsocketopt. */
            if (socketHandle->recvTimeoutMs != 0U)
            {
                recvTimeout = socketHandle->recvTimeoutMs;
            }

            snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "AT+SQNSRECV=%u,%u",
                     RM_CELLULAR_RYZ_GET_MODEM_SOCKET_ID(socketHandle->socketId), (uint16_t) recvLen);
            pktStatus = _Cellular_TimeoutAtcmdDataRecvRequestWithCallback(pContext,
                                                                          atReqSocketRecv,
                                                                          recvTimeout,
                                                                          socketRecvDataPrefix,
                                                                          NULL);

            if (pktStatus != CELLULAR_PKT_STATUS_OK)
            {
                /* Reset data handling parameters. */
                LogError(("Cellular_SocketRecv: Data Receive fail, pktStatus: %d", pktStatus));
                cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
            }
        }
    }

    return cellularStatus;
}

/* Implementation of Cellular_SocketClose */
CellularError_t Cellular_SocketClose (CellularHandle_t cellularHandle, CellularSocketHandle_t socketHandle)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;
    char                cmdBuf[CELLULAR_AT_CMD_MAX_SIZE] = {'\0'};
    CellularAtReq_t     atReqSockClose =
    {
        cmdBuf,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0,
    };

    /* Make sure the library is open. */
    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogDebug(("_Cellular_CheckLibraryStatus failed"));
    }
    else if (socketHandle == NULL)
    {
        cellularStatus = CELLULAR_INVALID_HANDLE;
    }
    else
    {
        if ((socketHandle->socketState == SOCKETSTATE_CONNECTING) ||
            (socketHandle->socketState == SOCKETSTATE_CONNECTED) ||
            (socketHandle->socketState == SOCKETSTATE_DISCONNECTED))
        {
            /* Form the AT command. */
            snprintf(cmdBuf, CELLULAR_AT_CMD_MAX_SIZE, "AT+SQNSH=%u",
                     RM_CELLULAR_RYZ_GET_MODEM_SOCKET_ID(socketHandle->socketId));
            pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                                  atReqSockClose,
                                                                  RM_CELLULAR_RYZ_SOCKET_DISCONNECT_PACKET_REQ_TIMEOUT_MS);

            if (pktStatus != CELLULAR_PKT_STATUS_OK)
            {
                LogError(("Cellular_SocketClose: Socket close failed, cmdBuf:%s, PktRet: %d", cmdBuf, pktStatus));
            }
        }

        /* Ignore the result from the info, and force to remove the socket. */
        cellularStatus = _Cellular_RemoveSocketData(pContext, socketHandle);
    }

    return cellularStatus;
}

/* Implementation of Cellular_GetServiceStatus */
CellularError_t Cellular_GetServiceStatus (CellularHandle_t cellularHandle, CellularServiceStatus_t * pServiceStatus)
{
    CellularContext_t    * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t        cellularStatus = CELLULAR_SUCCESS;
    cellularOperatorInfo_t operatorInfo;

    (void) memset(&operatorInfo, 0, sizeof(cellularOperatorInfo_t));

    /* pContext is checked in _Cellular_CheckLibraryStatus function. */
    cellularStatus = _Cellular_CheckLibraryStatus(pContext);

    if (cellularStatus != CELLULAR_SUCCESS)
    {
        LogError(("_Cellular_CheckLibraryStatus failed"));
    }
    else if (pServiceStatus == NULL)
    {
        LogError(("Cellular_GetServiceStatus : Bad parameter"));
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }
    else
    {
        const cellularAtData_t * pLibAtData     = NULL;
        CellularPktStatus_t      pktStatus      = CELLULAR_PKT_STATUS_OK;
        CellularAtReq_t          atReqGetResult = {0};

        atReqGetResult.pAtCmd       = "AT+CEREG?";
        atReqGetResult.atCmdType    = CELLULAR_AT_MULTI_WITH_PREFIX;
        atReqGetResult.pAtRspPrefix = "+CEREG";
        atReqGetResult.respCallback = _Cellular_RecvFuncGetNetworkReg;
        atReqGetResult.pData        = NULL;
        atReqGetResult.dataLen      = 0;

        pktStatus      = _Cellular_AtcmdRequestWithCallback(pContext, atReqGetResult);
        cellularStatus = _Cellular_TranslatePktStatus(pktStatus);

        /* Get the service status from lib AT data. */
        if (cellularStatus == CELLULAR_SUCCESS)
        {
            pLibAtData = &pContext->libAtData;
            _Cellular_LockAtDataMutex(pContext);
            pServiceStatus->rat = pLibAtData->rat;
            pServiceStatus->csRegistrationStatus = pLibAtData->csRegStatus;
            pServiceStatus->psRegistrationStatus = pLibAtData->psRegStatus;
            pServiceStatus->csRejectionCause     = pLibAtData->csRejCause;
            pServiceStatus->csRejectionType      = pLibAtData->csRejectType;
            pServiceStatus->psRejectionCause     = pLibAtData->psRejCause;
            pServiceStatus->psRejectionType      = pLibAtData->psRejectType;
            _Cellular_UnlockAtDataMutex(pContext);
        }

        CellularAtReq_t atReqGetMccMnc = {0};

        atReqGetMccMnc.pAtCmd       = "AT+COPS?";
        atReqGetMccMnc.atCmdType    = CELLULAR_AT_WITH_PREFIX;
        atReqGetMccMnc.pAtRspPrefix = "+COPS";
        atReqGetMccMnc.respCallback = _Cellular_RecvFuncUpdateMccMnc;
        atReqGetMccMnc.pData        = &operatorInfo;
        atReqGetMccMnc.dataLen      = (uint16_t) sizeof(cellularOperatorInfo_t);

        pktStatus      = _Cellular_AtcmdRequestWithCallback(pContext, atReqGetMccMnc);
        cellularStatus = _Cellular_TranslatePktStatus(pktStatus);

        /* Service status data from operator info. */
        pServiceStatus->networkRegistrationMode = operatorInfo.networkRegMode;
        pServiceStatus->plmnInfo                = operatorInfo.plmnInfo;
        (void) strncpy(pServiceStatus->operatorName, operatorInfo.operatorName, sizeof(operatorInfo.operatorName));
        pServiceStatus->operatorNameFormat = operatorInfo.operatorNameFormat;

        LogDebug(("SrvStatus: rat %d cs %d, ps %d, mode %d, csRejType %d,",
                  pServiceStatus->rat,
                  pServiceStatus->csRegistrationStatus,
                  pServiceStatus->psRegistrationStatus,
                  pServiceStatus->networkRegistrationMode,
                  pServiceStatus->csRejectionType));

        LogDebug(("csRej %d, psRejType %d, psRej %d, plmn %s%s",
                  pServiceStatus->csRejectionCause,
                  pServiceStatus->psRejectionType,
                  pServiceStatus->psRejectionCause,
                  pServiceStatus->plmnInfo.mcc,
                  pServiceStatus->plmnInfo.mnc));
    }

    return cellularStatus;
}

/*******************************************************************************************************************//**
 * Callback to process AT+CEREG response.
 *
 * @param[in] pContext  Pointer to cellular context.
 * @param[in] pAtResp   Pointer to AT command response.
 * @param[in] pData     Pointer to where to store parsed data.
 * @param[in] dataLen   Length of where to store parsed data.
 *
 * @retval  CELLULAR_PKT_STATUS_OK          Response processing succeeded
 * @retval  CELLULAR_PKT_STATUS_FAILURE     Parsing failure
 * @retval  CELLULAR_PKT_STATUS_BAD_PARAM   Bad parameter passed to callback
 **********************************************************************************************************************/
static CellularPktStatus_t _Cellular_RecvFuncGetNetworkReg (CellularContext_t                 * pContext,
                                                            const CellularATCommandResponse_t * pAtResp,
                                                            void                              * pData,
                                                            uint16_t                            dataLen)
{
    char              * pPregLine    = NULL;
    CellularPktStatus_t pktStatus    = CELLULAR_PKT_STATUS_OK;
    CellularATError_t   atCoreStatus = CELLULAR_AT_SUCCESS;

    FSP_PARAMETER_NOT_USED(pData);
    FSP_PARAMETER_NOT_USED(dataLen);

    if (pContext == NULL)
    {
        pktStatus = CELLULAR_PKT_STATUS_INVALID_HANDLE;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("_Cellular_RecvFuncGetNetworkReg: response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else
    {
        pPregLine    = pAtResp->pItm->pLine;
        atCoreStatus = Cellular_ATRemoveLeadingWhiteSpaces(&pPregLine);
        pktStatus    = _Cellular_TranslateAtCoreStatus(atCoreStatus);

        if (pktStatus == CELLULAR_PKT_STATUS_OK)
        {
            /* Assumption is that the data is null terminated so we don't need the dataLen. */
            _Cellular_LockAtDataMutex(pContext);
            pktStatus = _Cellular_ParseRegStatus(pContext, pPregLine, false, CELLULAR_REG_TYPE_CEREG);
            pContext->libAtData.csRegStatus = pContext->libAtData.psRegStatus;
            _Cellular_UnlockAtDataMutex(pContext);
        }

        LogDebug(("atcmd network register status pktStatus:%d", pktStatus));
    }

    return pktStatus;
}

/*******************************************************************************************************************//**
 * Callback to process AT+COPS response.
 *
 * @param[in] pContext  Pointer to cellular context.
 * @param[in] pAtResp   Pointer to AT command response.
 * @param[in] pData     Pointer to where to store parsed data.
 * @param[in] dataLen   Length of where to store parsed data.
 *
 * @retval  CELLULAR_PKT_STATUS_OK          Response processing succeeded
 * @retval  CELLULAR_PKT_STATUS_FAILURE     Parsing failure
 * @retval  CELLULAR_PKT_STATUS_BAD_PARAM   Bad parameter passed to callback
 **********************************************************************************************************************/
static CellularPktStatus_t _Cellular_RecvFuncUpdateMccMnc (CellularContext_t                 * pContext,
                                                           const CellularATCommandResponse_t * pAtResp,
                                                           void                              * pData,
                                                           uint16_t                            dataLen)
{
    char                   * pCopsResponse = NULL;
    CellularPktStatus_t      pktStatus     = CELLULAR_PKT_STATUS_OK;
    CellularATError_t        atCoreStatus  = CELLULAR_AT_SUCCESS;
    cellularOperatorInfo_t * pOperatorInfo = NULL;

    if (pContext == NULL)
    {
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("UpdateMccMnc: Response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pData == NULL) || (dataLen != sizeof(cellularOperatorInfo_t)))
    {
        LogError(("UpdateMccMnc: pData is invalid or dataLen is wrong"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else
    {
        pCopsResponse = pAtResp->pItm->pLine;
        pOperatorInfo = (cellularOperatorInfo_t *) pData;

        /* Remove COPS Prefix. */
        atCoreStatus = Cellular_ATRemovePrefix(&pCopsResponse);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Removing all the Quotes from the COPS response. */
            atCoreStatus = Cellular_ATRemoveAllDoubleQuote(pCopsResponse);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Removing all Space from the COPS response. */
            atCoreStatus = Cellular_ATRemoveAllWhiteSpaces(pCopsResponse);
        }

        /* parse all the data from cops. */
        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            char * pToken            = NULL;
            char * pTempCopsResponse = pCopsResponse;
            bool   parseStatus       = true;

            /* Getting next token from COPS response. */
            atCoreStatus = Cellular_ATGetNextTok(&pTempCopsResponse, &pToken);

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                int32_t var = 0;

                atCoreStatus = Cellular_ATStrtoi(pToken, 10, &var);

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    if ((var >= 0) && (var < (int32_t) REGISTRATION_MODE_MAX))
                    {
                        /* Variable "var" is ensured that it is valid and within
                         * a valid range. Hence, assigning the value of the variable to
                         * networkRegMode with a enum cast. */

                        /* coverity[misra_c_2012_rule_10_5_violation] */
                        pOperatorInfo->networkRegMode = (CellularNetworkRegistrationMode_t) var;
                    }
                    else
                    {
                        LogError(("_parseCopsRegMode: Error in processing Network Registration mode. Token %s",
                                  pToken));
                        parseStatus = false;
                    }
                }

                if (parseStatus == false)
                {
                    atCoreStatus = CELLULAR_AT_ERROR;
                }
            }

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                atCoreStatus = Cellular_ATGetNextTok(&pTempCopsResponse, &pToken);
            }

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                int32_t var = 0;

                atCoreStatus = Cellular_ATStrtoi(pToken, 10, &var);

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    if ((var >= 0) &&
                        (var < (int32_t) OPERATOR_NAME_FORMAT_MAX))
                    {
                        /* Variable "var" is ensured that it is valid and within
                         * a valid range. Hence, assigning the value of the variable to
                         * operatorNameFormat with a enum cast. */

                        /* coverity[misra_c_2012_rule_10_5_violation] */
                        pOperatorInfo->operatorNameFormat = (CellularOperatorNameFormat_t) var;
                    }
                    else
                    {
                        LogError((
                                     "_parseCopsNetworkNameFormat: Error in processing Network Registration mode. Token %s",
                                     pToken));
                        parseStatus = false;
                    }
                }

                if (parseStatus == false)
                {
                    atCoreStatus = CELLULAR_AT_ERROR;
                }
            }

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                atCoreStatus = Cellular_ATGetNextTok(&pTempCopsResponse, &pToken);
            }

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                uint32_t mccMncLen = 0U;

                if ((pOperatorInfo->operatorNameFormat == OPERATOR_NAME_FORMAT_LONG) ||
                    (pOperatorInfo->operatorNameFormat == OPERATOR_NAME_FORMAT_SHORT))
                {
                    (void) strncpy(pOperatorInfo->operatorName, pToken, CELLULAR_NETWORK_NAME_MAX_SIZE);
                }
                else if (pOperatorInfo->operatorNameFormat == OPERATOR_NAME_FORMAT_NUMERIC)
                {
                    mccMncLen = (uint32_t) strlen(pToken);

                    if ((mccMncLen == (CELLULAR_MCC_MAX_SIZE + CELLULAR_MNC_MAX_SIZE)) ||
                        (mccMncLen == (CELLULAR_MCC_MAX_SIZE + CELLULAR_MNC_MAX_SIZE - 1U)))
                    {
                        (void) strncpy(pOperatorInfo->plmnInfo.mcc, pToken, CELLULAR_MCC_MAX_SIZE);
                        pOperatorInfo->plmnInfo.mcc[CELLULAR_MCC_MAX_SIZE] = '\0';
                        (void) strncpy(pOperatorInfo->plmnInfo.mnc, &pToken[CELLULAR_MCC_MAX_SIZE],
                                       (uint32_t) (mccMncLen - CELLULAR_MCC_MAX_SIZE + 1U));
                        pOperatorInfo->plmnInfo.mnc[CELLULAR_MNC_MAX_SIZE] = '\0';
                    }
                    else
                    {
                        LogError(("_parseCopsNetworkName: Error in processing Network MCC MNC: Length not Valid"));
                        parseStatus = false;
                    }
                }
                else
                {
                    LogError(("Error in processing Operator Name: Format Unknown"));
                    parseStatus = false;
                }

                if (parseStatus == false)
                {
                    atCoreStatus = CELLULAR_AT_ERROR;
                }
            }

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                atCoreStatus = Cellular_ATGetNextTok(&pTempCopsResponse, &pToken);
            }

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                int32_t var = 0;

                atCoreStatus = Cellular_ATStrtoi(pToken, 10, &var);

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    if ((var < (int32_t) CELLULAR_RAT_MAX) && (var >= 0))
                    {
                        /* Variable "var" is ensured that it is valid and within
                         * a valid range. Hence, assigning the value of the variable to
                         * rat with a enum cast. */

                        /* coverity[misra_c_2012_rule_10_5_violation] */
                        pOperatorInfo->rat = (CellularRat_t) var;
                    }
                    else
                    {
                        LogError(("_parseCopsNetworkName: Error in processing RAT. Token %s", pToken));
                        parseStatus = false;
                    }
                }

                if (parseStatus == false)
                {
                    atCoreStatus = CELLULAR_AT_ERROR;
                }
            }
        }

        if (atCoreStatus == CELLULAR_AT_ERROR)
        {
            LogError(("ERROR: COPS %s", pCopsResponse));
            pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);
        }
    }

    return pktStatus;
}

/*******************************************************************************************************************//**
 * Get activation status with AT+CGACT command.
 *
 * @param[in] cellularHandle        Cellular handle provided by init command.
 * @param[in] pPdpContextsActInfo   Struct to store activation info in.
 *
 * @retval  See _Cellular_AtcmdRequestWithCallback
 **********************************************************************************************************************/
static CellularError_t _Cellular_GetContextActivationStatus (CellularHandle_t              cellularHandle,
                                                             CellularPdnContextActInfo_t * pPdpContextsActInfo)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;

    CellularAtReq_t atReqPacketSwitchStatus =
    {
        "AT+CGACT?",
        CELLULAR_AT_MULTI_WITH_PREFIX,
        "+CGACT",
        _Cellular_RecvFuncGetPdpContextActState,
        pPdpContextsActInfo,
        sizeof(CellularPdnContextActInfo_t),
    };

    /* Internal function. Callee check parameters. */
    pktStatus      = _Cellular_AtcmdRequestWithCallback(pContext, atReqPacketSwitchStatus);
    cellularStatus = _Cellular_TranslatePktStatus(pktStatus);

    return cellularStatus;
}

/*******************************************************************************************************************//**
 * Callback to process AT+CGACT response.
 *
 * @param[in] pContext  Pointer to cellular context.
 * @param[in] pAtResp   Pointer to AT command response.
 * @param[in] pData     Pointer to where to store parsed data.
 * @param[in] dataLen   Length of where to store parsed data.
 *
 * @retval  CELLULAR_PKT_STATUS_OK          Response processing succeeded
 * @retval  CELLULAR_PKT_STATUS_FAILURE     Parsing failure
 * @retval  CELLULAR_PKT_STATUS_BAD_PARAM   Bad parameter passed to callback
 **********************************************************************************************************************/
static CellularPktStatus_t _Cellular_RecvFuncGetPdpContextActState (CellularContext_t                 * pContext,
                                                                    const CellularATCommandResponse_t * pAtResp,
                                                                    void                              * pData,
                                                                    uint16_t                            dataLen)
{
    char * pRespLine = NULL;
    CellularPdnContextActInfo_t   * pPDPContextsActInfo = (CellularPdnContextActInfo_t *) pData;
    CellularPktStatus_t             pktStatus           = CELLULAR_PKT_STATUS_OK;
    CellularATError_t               atCoreStatus        = CELLULAR_AT_SUCCESS;
    const CellularATCommandLine_t * pCommandItem        = NULL;
    uint8_t tokenIndex = 0;
    uint8_t contextId  = 0;
    int32_t tempValue  = 0;
    char  * pToken     = NULL;

    if (pContext == NULL)
    {
        LogError(("_Cellular_RecvFuncGetPdpContextActState: invalid context"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pPDPContextsActInfo == NULL) || (dataLen != sizeof(CellularPdnContextActInfo_t)))
    {
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if (pAtResp == NULL)
    {
        LogError(("_Cellular_RecvFuncGetPdpContextActState: Response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("_Cellular_RecvFuncGetPdpContextActState: no PDN context available"));
        pktStatus = CELLULAR_PKT_STATUS_OK;
    }
    else
    {
        pRespLine = pAtResp->pItm->pLine;

        pCommandItem = pAtResp->pItm;

        while (pCommandItem != NULL)
        {
            pRespLine = pCommandItem->pLine;
            LogDebug(("_Cellular_RecvFuncGetPdpContextActState: pRespLine [%s]", pRespLine));

            /* Removing all the Spaces in the AT Response. */
            atCoreStatus = Cellular_ATRemoveAllWhiteSpaces(pRespLine);

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                atCoreStatus = Cellular_ATRemovePrefix(&pRespLine);

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    atCoreStatus = Cellular_ATRemoveAllDoubleQuote(pRespLine);
                }

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    atCoreStatus = Cellular_ATGetNextTok(&pRespLine, &pToken);
                }

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    tokenIndex = 0;

                    while ((pToken != NULL) && (atCoreStatus == CELLULAR_AT_SUCCESS))
                    {
                        switch (tokenIndex)
                        {
                            case (RM_CELLULAR_RYZ_PDN_ACT_STATUS_POS_CONTEXT_ID):
                            {
                                LogDebug(("_Cellular_RecvFuncGetPdpContextActState: Context Id pToken: %s", pToken));
                                atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

                                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                                {
                                    if ((tempValue >= (int32_t) CELLULAR_PDN_CONTEXT_ID_MIN) &&
                                        (tempValue <= (int32_t) RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS))
                                    {
                                        contextId = (uint8_t) tempValue;
                                        pPDPContextsActInfo->contextsPresent[contextId - 1] = true;
                                        LogDebug(("_Cellular_RecvFuncGetPdpContextActState: Context Id: %d",
                                                  contextId));
                                    }
                                    else
                                    {
                                        LogError((
                                                     "_Cellular_RecvFuncGetPdpContextActState: Invalid Context Id. Token %s",
                                                     pToken));
                                        atCoreStatus = CELLULAR_AT_ERROR;
                                    }
                                }

                                break;
                            }

                            case (RM_CELLULAR_RYZ_PDN_ACT_STATUS_POS_CONTEXT_STATE):
                            {
                                LogDebug(("_Cellular_RecvFuncGetPdpContextActState: Context <Act> pToken: %s", pToken));
                                atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

                                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                                {
                                    pPDPContextsActInfo->contextActState[contextId - 1] = (bool) tempValue;
                                    LogDebug(("_Cellular_RecvFuncGetPdpContextActState: Context <Act>: %d",
                                              pPDPContextsActInfo->contextActState[contextId - 1]));
                                }

                                break;
                            }

                            default:
                            {
                                break;
                            }
                        }

                        tokenIndex++;

                        if (Cellular_ATGetNextTok(&pRespLine, &pToken) != CELLULAR_AT_SUCCESS)
                        {
                            break;
                        }
                    }
                }
            }

            pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);

            if (pktStatus != CELLULAR_PKT_STATUS_OK)
            {
                LogError(("_Cellular_RecvFuncGetPdpContextActState: parse %s failed", pRespLine));
                break;
            }

            pCommandItem = pCommandItem->pNext;
        }
    }

    return pktStatus;
}

/*******************************************************************************************************************//**
 * Get packet switch status with AT+CGATT?
 *
 * @param[in] cellularHandle        Cellular handle provided by init command.
 * @param[in] pPacketSwitchStatus   Location to store status.
 *
 * @retval  See _Cellular_TimeoutAtcmdRequestWithCallback
 **********************************************************************************************************************/
static CellularError_t _Cellular_GetPacketSwitchStatus (CellularHandle_t cellularHandle, bool * pPacketSwitchStatus)
{
    CellularContext_t * pContext                = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus          = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus               = CELLULAR_PKT_STATUS_OK;
    CellularAtReq_t     atReqPacketSwitchStatus =
    {
        "AT+CGATT?",
        CELLULAR_AT_WITH_PREFIX,
        "+CGATT",
        _Cellular_RecvFuncPacketSwitchStatus,
        pPacketSwitchStatus,
        sizeof(bool),
    };

    /* Internal function. Callee check parameters. */
    pktStatus = _Cellular_TimeoutAtcmdRequestWithCallback(pContext,
                                                          atReqPacketSwitchStatus,
                                                          RM_CELLULAR_RYZ_PDN_ACT_PACKET_REQ_TIMEOUT_MS);
    cellularStatus = _Cellular_TranslatePktStatus(pktStatus);

    return cellularStatus;
}

/*******************************************************************************************************************//**
 * Callback to process AT+CGATT response.
 *
 * @param[in] pContext  Pointer to cellular context.
 * @param[in] pAtResp   Pointer to AT command response.
 * @param[in] pData     Pointer to where to store parsed data.
 * @param[in] dataLen   Length of where to store parsed data.
 *
 * @retval  CELLULAR_PKT_STATUS_OK          Response processing succeeded
 * @retval  CELLULAR_PKT_STATUS_FAILURE     Parsing failure
 * @retval  CELLULAR_PKT_STATUS_BAD_PARAM   Bad parameter passed to callback
 **********************************************************************************************************************/
static CellularPktStatus_t _Cellular_RecvFuncPacketSwitchStatus (CellularContext_t                 * pContext,
                                                                 const CellularATCommandResponse_t * pAtResp,
                                                                 void                              * pData,
                                                                 uint16_t                            dataLen)
{
    char              * pInputLine          = NULL;
    CellularPktStatus_t pktStatus           = CELLULAR_PKT_STATUS_OK;
    CellularATError_t   atCoreStatus        = CELLULAR_AT_SUCCESS;
    bool              * pPacketSwitchStatus = (bool *) pData;

    if (pContext == NULL)
    {
        LogError(("PacketSwitchStatus: Invalid handle"));
        pktStatus = CELLULAR_PKT_STATUS_INVALID_HANDLE;
    }
    else if ((pData == NULL) || (dataLen != sizeof(bool)))
    {
        LogError(("GetPacketSwitchStatus: Invalid param"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("GetPacketSwitchStatus: Input Line passed is NULL"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else
    {
        pInputLine = pAtResp->pItm->pLine;

        /* Remove prefix. */
        atCoreStatus = Cellular_ATRemovePrefix(&pInputLine);

        /* Remove leading space. */
        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            atCoreStatus = Cellular_ATRemoveLeadingWhiteSpaces(&pInputLine);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            if (*pInputLine == '0')
            {
                *pPacketSwitchStatus = false;
            }
            else if (*pInputLine == '1')
            {
                *pPacketSwitchStatus = true;
            }
            else
            {
                atCoreStatus = CELLULAR_AT_ERROR;
            }
        }

        pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);
    }

    return pktStatus;
}

/*******************************************************************************************************************//**
 * Callback to process AT+CGDCONT response.
 *
 * @param[in] pContext  Pointer to cellular context.
 * @param[in] pAtResp   Pointer to AT command response.
 * @param[in] pData     Pointer to where to store parsed data.
 * @param[in] dataLen   Length of where to store parsed data.
 *
 * @retval  CELLULAR_PKT_STATUS_OK          Response processing succeeded
 * @retval  CELLULAR_PKT_STATUS_FAILURE     Parsing failure
 * @retval  CELLULAR_PKT_STATUS_BAD_PARAM   Bad parameter passed to callback
 **********************************************************************************************************************/
static CellularPktStatus_t _Cellular_RecvFuncGetPdpContextSettings (CellularContext_t                 * pContext,
                                                                    const CellularATCommandResponse_t * pAtResp,
                                                                    void                              * pData,
                                                                    uint16_t                            dataLen)
{
    char * pRespLine = NULL;
    CellularPdnContextInfo_t      * pPDPContextsInfo = (CellularPdnContextInfo_t *) pData;
    CellularPktStatus_t             pktStatus        = CELLULAR_PKT_STATUS_OK;
    CellularATError_t               atCoreStatus     = CELLULAR_AT_SUCCESS;
    const CellularATCommandLine_t * pCommandItem     = NULL;
    uint8_t tokenIndex = 0;
    uint8_t contextId  = 0;
    int32_t tempValue  = 0;
    char  * pToken     = NULL;

    FSP_PARAMETER_NOT_USED(dataLen);

    if (pContext == NULL)
    {
        LogError(("_Cellular_RecvFuncGetPdpContextSettings: invalid context"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if (pPDPContextsInfo == NULL)
    {
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if (pAtResp == NULL)
    {
        LogError(("_Cellular_RecvFuncGetPdpContextSettings: Response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("_Cellular_RecvFuncGetPdpContextSettings: no PDN context available"));
        pktStatus = CELLULAR_PKT_STATUS_OK;
    }
    else
    {
        pRespLine = pAtResp->pItm->pLine;

        pCommandItem = pAtResp->pItm;

        while (pCommandItem != NULL)
        {
            pRespLine = pCommandItem->pLine;
            LogDebug(("_Cellular_RecvFuncGetPdpContextSettings: pRespLine [%s]", pRespLine));

            /* Removing all the Spaces in the AT Response. */
            atCoreStatus = Cellular_ATRemoveAllWhiteSpaces(pRespLine);

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                atCoreStatus = Cellular_ATRemovePrefix(&pRespLine);

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    atCoreStatus = Cellular_ATRemoveAllDoubleQuote(pRespLine);
                }

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    atCoreStatus = Cellular_ATGetNextTok(&pRespLine, &pToken);
                }

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    tokenIndex = 0;

                    while ((pToken != NULL) && (atCoreStatus == CELLULAR_AT_SUCCESS))
                    {
                        switch (tokenIndex)
                        {
                            case (RM_CELLULAR_RYZ_PDN_STATUS_POS_CONTEXT_ID):
                            {
                                LogDebug(("_Cellular_RecvFuncGetPdpContextSettings: Context Id pToken: %s", pToken));
                                atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

                                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                                {
                                    if ((tempValue >= (int32_t) CELLULAR_PDN_CONTEXT_ID_MIN) &&
                                        (tempValue <= (int32_t) RM_CELLULAR_RYZ_MAX_PDP_CONTEXTS))
                                    {
                                        contextId = (uint8_t) tempValue;
                                        pPDPContextsInfo->contextsPresent[contextId - 1] = true;
                                        LogDebug(("_Cellular_RecvFuncGetPdpContextSettings: Context Id: %d",
                                                  contextId));
                                    }
                                    else
                                    {
                                        LogError((
                                                     "_Cellular_RecvFuncGetPdpContextSettings: Invalid Context Id. Token %s",
                                                     pToken));
                                        atCoreStatus = CELLULAR_AT_ERROR;
                                    }
                                }

                                break;
                            }

                            case (RM_CELLULAR_RYZ_PDN_STATUS_POS_CONTEXT_TYPE):
                            {
                                LogDebug(("_Cellular_RecvFuncGetPdpContextSettings: Context Type pToken: %s", pToken));

                                (void) memcpy((void *) pPDPContextsInfo->ipType[contextId - 1],
                                              (void *) pToken,
                                              RM_CELLULAR_RYZ_PDN_CONTEXT_TYPE_MAX_SIZE);
                                break;
                            }

                            case (RM_CELLULAR_RYZ_PDN_STATUS_POS_APN_NAME):
                            {
                                LogDebug(("_Cellular_RecvFuncGetPdpContextSettings: Context APN name pToken: %s",
                                          pToken));

                                (void) memcpy((void *) pPDPContextsInfo->apnName[contextId - 1],
                                              (void *) pToken,
                                              CELLULAR_APN_MAX_SIZE);
                                break;
                            }

                            case (RM_CELLULAR_RYZ_PDN_STATUS_POS_IP_ADDRESS):
                            {
                                LogDebug(("_Cellular_RecvFuncGetPdpContextSettings: Context IP address pToken: %s",
                                          pToken));

                                (void) memcpy((void *) pPDPContextsInfo->ipAddress[contextId - 1],
                                              (void *) pToken,
                                              CELLULAR_IP_ADDRESS_MAX_SIZE + 1U);
                                break;
                            }

                            default:
                            {
                                break;
                            }
                        }

                        tokenIndex++;

                        if (Cellular_ATGetNextTok(&pRespLine, &pToken) != CELLULAR_AT_SUCCESS)
                        {
                            break;
                        }
                    }
                }
            }

            pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);

            if (pktStatus != CELLULAR_PKT_STATUS_OK)
            {
                LogError(("_Cellular_RecvFuncGetPdpContextSettings: parse %s failed", pRespLine));
                break;
            }

            pCommandItem = pCommandItem->pNext;
        }
    }

    return pktStatus;
}

static CellularPktStatus_t _Cellular_RecvFuncGetSignalInfo (CellularContext_t                 * pContext,
                                                            const CellularATCommandResponse_t * pAtResp,
                                                            void                              * pData,
                                                            uint16_t                            dataLen)
{
    char                 * pInputLine      = NULL;
    CellularSignalInfo_t * pSignalInfo     = (CellularSignalInfo_t *) pData;
    bool                parseStatus        = true;
    CellularPktStatus_t pktStatus          = CELLULAR_PKT_STATUS_OK;
    CellularATError_t   atCoreStatus       = CELLULAR_AT_SUCCESS;
    bool                isExtendedResponse = false;

    if (pContext == NULL)
    {
        pktStatus = CELLULAR_PKT_STATUS_INVALID_HANDLE;
    }
    else if ((pSignalInfo == NULL) || (dataLen != sizeof(CellularSignalInfo_t)))
    {
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("GetSignalInfo: Input Line passed is NULL"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else
    {
        pInputLine = pAtResp->pItm->pLine;

        if (strstr(pInputLine, "+CESQ"))
        {
            LogDebug(("GetSignalInfo: ExtendedResponse received."));
            isExtendedResponse = true;
        }

        atCoreStatus = Cellular_ATRemovePrefix(&pInputLine);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            atCoreStatus = Cellular_ATRemoveAllWhiteSpaces(pInputLine);
        }

        if (atCoreStatus != CELLULAR_AT_SUCCESS)
        {
            pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);
        }
    }

    if (pktStatus == CELLULAR_PKT_STATUS_OK)
    {
        if (isExtendedResponse)
        {
            parseStatus = _parseExtendedSignalQuality(pInputLine, pSignalInfo);
        }
        else
        {
            parseStatus = _parseSignalQuality(pInputLine, pSignalInfo);
        }

        if (parseStatus != true)
        {
            pSignalInfo->rssi = CELLULAR_INVALID_SIGNAL_VALUE;
            pSignalInfo->rsrp = CELLULAR_INVALID_SIGNAL_VALUE;
            pSignalInfo->rsrq = CELLULAR_INVALID_SIGNAL_VALUE;
            pSignalInfo->ber  = CELLULAR_INVALID_SIGNAL_VALUE;
            pSignalInfo->bars = CELLULAR_INVALID_SIGNAL_BAR_VALUE;
            pktStatus         = CELLULAR_PKT_STATUS_FAILURE;
        }
    }

    return pktStatus;
}

static bool _parseExtendedSignalQuality (char * pQcsqPayload, CellularSignalInfo_t * pSignalInfo)
{
    char            * pToken          = NULL;
    char            * pTmpQcsqPayload = pQcsqPayload;
    int32_t           tempValue       = 0;
    bool              parseStatus     = true;
    CellularATError_t atCoreStatus    = CELLULAR_AT_SUCCESS;

    if ((pSignalInfo == NULL) || (pQcsqPayload == NULL))
    {
        LogError(("_parseExtendedSignalQuality: Invalid Input Parameters"));
        parseStatus = false;
    }

    /*  +CESQ: <rxlev>,<ber>,<rscp>,<ecn0>,<rsrq>,<rsrp>. */

    /* Skip <rxlev>. */
    atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);

    /* Parse <ber>. */
    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);
    }

    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

        if ((atCoreStatus == CELLULAR_AT_SUCCESS) && (tempValue <= INT16_MAX) && (tempValue >= INT16_MIN))
        {
            /*
             * Bit Error Rate (BER):
             *  0..7: as RXQUAL values in the table in 3GPP TS 45.008 [124], subclause 8.2.4
             *  99: not known or not detectable
             */
            if ((tempValue >= 0) && (tempValue <= 7))
            {
                pSignalInfo->ber = (int16_t) tempValue;
            }
            else
            {
                pSignalInfo->ber = CELLULAR_INVALID_SIGNAL_VALUE;
            }
        }
        else
        {
            LogError(("_parseExtendedSignalQuality: Error in processing BER. Token %s", pToken));
            atCoreStatus = CELLULAR_AT_ERROR;
        }
    }

    /* Skip <rscp>. */
    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);
    }

    /* Skip <ecno>. */
    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);
    }

    /* Parse <rsrq>. */
    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);
    }

    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /*
             * Reference Signal Received Quality (RSRQ):
             *  0: less than -19.5 dB
             *  1..33: from -19.5 dB to -3.5 dB with 0.5 dB steps
             *  34: -3 dB or greater
             *  255: not known or not detectable
             */
            if ((tempValue >= 0) && (tempValue <= 34))                     // NOLINT(readability-magic-numbers)
            {
                pSignalInfo->rsrq = (int16_t) ((-20) + (tempValue * 0.5)); // NOLINT(readability-magic-numbers)
            }
            else
            {
                pSignalInfo->rsrq = CELLULAR_INVALID_SIGNAL_VALUE;
            }
        }
        else
        {
            LogError(("_parseExtendedSignalQuality: Error in processing RSRP. Token %s", pToken));
            parseStatus = false;
        }
    }

    /* Parse <rsrp>. */
    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);
    }

    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /*
             * Reference Signal Received Power(RSRP) :
             *  0 : less than - 140 dBm
             *  1..96 : from - 140 dBm to - 45 dBm with 1 dBm steps
             *  97 : -44 dBm or greater
             *  255 : not known or not detectable
             */
            if ((tempValue >= 0) && (tempValue <= 97))                // NOLINT(readability-magic-numbers)
            {
                pSignalInfo->rsrp = (int16_t) ((-141) + (tempValue)); // NOLINT(readability-magic-numbers)
            }
            else
            {
                pSignalInfo->rsrp = CELLULAR_INVALID_SIGNAL_VALUE;
            }
        }
        else
        {
            LogError(("_parseExtendedSignalQuality: Error in processing RSRP. Token %s", pToken));
            parseStatus = false;
        }
    }

    return parseStatus;
}

static bool _parseSignalQuality (char * pQcsqPayload, CellularSignalInfo_t * pSignalInfo)
{
    char            * pToken          = NULL;
    char            * pTmpQcsqPayload = pQcsqPayload;
    int32_t           tempValue       = 0;
    bool              parseStatus     = true;
    CellularATError_t atCoreStatus    = CELLULAR_AT_SUCCESS;

    if ((pSignalInfo == NULL) || (pQcsqPayload == NULL))
    {
        LogError(("_parseSignalQuality: Invalid Input Parameters"));
        parseStatus = false;
    }

    /* +CSQ: <signal_power>,<qual>. */

    /* Parse <signal_power>. */
    atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);

    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /*
             * The allowed range is 0-31 and 99.
             *  0           RSSI of the network <= -113 dBm
             *  1           -111 dBm
             *  2...30      -109 dBm <= RSSI of the network <= -53 dBm
             *  31          -51 dBm <= RSSI of the network
             *  99          Not known or not detectable
             */
            if ((tempValue >= 0) && (tempValue <= 31))                    // NOLINT(readability-magic-numbers)
            {
                pSignalInfo->rssi = (int16_t) ((-113) + (tempValue * 2)); // NOLINT(readability-magic-numbers)
            }
            else if (tempValue == 99)                                     // NOLINT(readability-magic-numbers)
            {
                pSignalInfo->rssi = -113;                                 // NOLINT(readability-magic-numbers)
            }
            else
            {
                pSignalInfo->rssi = CELLULAR_INVALID_SIGNAL_VALUE;
            }
        }
        else
        {
            LogError(("_parseSignalQuality: Error in processing RSSI. Token %s", pToken));
            parseStatus = false;
        }
    }

    /* Parse <qual>. */
    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATGetNextTok(&pTmpQcsqPayload, &pToken);
    }

    if (atCoreStatus == CELLULAR_AT_SUCCESS)
    {
        atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /*
             * The allowed range is 0-7 and 99 :
             *  In 2G RAT CS dedicated and GPRS packet transfer mode indicates the Bit Error Rate (BER) as specified in 3GPP TS 45.008
             */
            if ((tempValue >= 0) && (tempValue <= 7))
            {
                pSignalInfo->ber = (int16_t) tempValue;
            }
            else
            {
                pSignalInfo->ber = CELLULAR_INVALID_SIGNAL_VALUE;
            }
        }
        else
        {
            LogError(("_parseSignalQuality: Error in processing ber. Token %s", pToken));
            parseStatus = false;
        }
    }

    return parseStatus;
}

static CellularPktStatus_t _Cellular_RecvFuncResolveDomainToIpAddress (CellularContext_t                 * pContext,
                                                                       const CellularATCommandResponse_t * pAtResp,
                                                                       void                              * pData,
                                                                       uint16_t                            dataLen)
{
    char                          * pRespLine          = NULL;
    char                          * pResolvedIpAddress = (char *) pData;
    CellularPktStatus_t             pktStatus          = CELLULAR_PKT_STATUS_OK;
    CellularATError_t               atCoreStatus       = CELLULAR_AT_SUCCESS;
    const CellularATCommandLine_t * pCommnadItem       = NULL;
    char                          * pToken             = NULL;

    if (pContext == NULL)
    {
        LogError(("_Cellular_RecvFuncResolveDomainToIpAddress: invalid context"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pResolvedIpAddress == NULL) || (dataLen != CELLULAR_IP_ADDRESS_MAX_SIZE))
    {
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if (pAtResp == NULL)
    {
        LogError(("_Cellular_RecvFuncResolveDomainToIpAddress: Response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("_Cellular_RecvFuncResolveDomainToIpAddress: Address not resolved"));
        pktStatus = CELLULAR_PKT_STATUS_OK;
    }
    else
    {
        pRespLine = pAtResp->pItm->pLine;

        pCommnadItem = pAtResp->pItm;

        while (pCommnadItem != NULL)
        {
            pRespLine = pCommnadItem->pLine;
            LogDebug(("_Cellular_RecvFuncResolveDomainToIpAddress: pRespLine [%s]", pRespLine));

            /* Removing all the Spaces in the AT Response. */
            atCoreStatus = Cellular_ATRemoveAllWhiteSpaces(pRespLine);

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                atCoreStatus = Cellular_ATRemovePrefix(&pRespLine);

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    atCoreStatus = Cellular_ATRemoveAllDoubleQuote(pRespLine);
                }

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    Cellular_ATGetNextTok(&pRespLine, &pToken);
                    atCoreStatus = Cellular_ATGetNextTok(&pRespLine, &pToken);
                }

                if (atCoreStatus == CELLULAR_AT_SUCCESS)
                {
                    (void) strncpy(pResolvedIpAddress, pToken, dataLen);

                    LogDebug(("_Cellular_RecvFuncResolveDomainToIpAddress: Resolved IP Address: [%s]",
                              pResolvedIpAddress));
                }
            }

            pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);

            if (pktStatus != CELLULAR_PKT_STATUS_OK)
            {
                LogError(("_Cellular_RecvFuncResolveDomainToIpAddress: parse %s failed", pRespLine));
                break;
            }

            pCommnadItem = pCommnadItem->pNext;
        }
    }

    return pktStatus;
}

static CellularPktStatus_t socketSendDataPrefix (void * pCallbackContext, char * pLine, uint32_t * pBytesRead)
{
    CellularPktStatus_t pktStatus = CELLULAR_PKT_STATUS_OK;

    if ((pLine == NULL) || (pBytesRead == NULL))
    {
        LogError(("socketSendDataPrefix: pLine is invalid or pBytesRead is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if (pCallbackContext != NULL)
    {
        LogError(("socketSendDataPrefix: pCallbackContext is not NULL"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if (*pBytesRead != 2U)
    {
        LogDebug(("socketSendDataPrefix: pBytesRead %u %s is not 2", (unsigned int) *pBytesRead, pLine));
    }
    else
    {
        /* After the data prefix, there should not be any data in stream.
         * Cellular commmon processes AT command in lines. Add a '\0' after '@'. */
        if (strcmp(pLine, "> ") == 0)
        {
            pLine[2]    = '\n';
            *pBytesRead = 3;
        }
    }

    return pktStatus;
}

static CellularPktStatus_t _Cellular_RecvFuncData (CellularContext_t                 * pContext,
                                                   const CellularATCommandResponse_t * pAtResp,
                                                   void                              * pData,
                                                   uint16_t                            dataLen)
{
    CellularATError_t         atCoreStatus = CELLULAR_AT_SUCCESS;
    CellularPktStatus_t       pktStatus    = CELLULAR_PKT_STATUS_OK;
    char                    * pInputLine   = NULL;
    char                    * pToken       = NULL;
    const _socketDataRecv_t * pDataRecv    = (_socketDataRecv_t *) pData;
    int32_t                   tempValue    = 0;

    (void) dataLen;

    if (pContext == NULL)
    {
        LogError(("Receive Data: invalid context"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("Receive Data: response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_FAILURE;
    }
    else if ((pDataRecv == NULL) || (pDataRecv->pData == NULL) || (pDataRecv->pDataLen == NULL))
    {
        LogError(("Receive Data: Bad parameters"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else
    {
        pInputLine = pAtResp->pItm->pLine; /* The first item is the data prefix. */

        /* Check the data prefix token "+SQNSRECV: ". */
        if (strncmp(pInputLine, RM_CELLULAR_RYZ_SOCKET_DATA_PREFIX_TOKEN,
                    RM_CELLULAR_RYZ_SOCKET_DATA_PREFIX_TOKEN_LEN) != 0)
        {
            LogError(("response item error in prefix"));
            atCoreStatus = CELLULAR_AT_ERROR;
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Get the socket ID */
            atCoreStatus = Cellular_ATGetNextTok(&pInputLine, &pToken);

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                /* Get the bytes received */
                atCoreStatus = Cellular_ATGetNextTok(&pInputLine, &pToken);
            }

            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                atCoreStatus = Cellular_ATStrtoi(pToken, 10, &tempValue);
            }

            /* Process the data buffer. */
            if (atCoreStatus == CELLULAR_AT_SUCCESS)
            {
                *pDataRecv->pDataLen = (uint32_t) tempValue;
                atCoreStatus         = getDataFromResp(pAtResp, pDataRecv, *pDataRecv->pDataLen);
            }
        }

        pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);
    }

    return pktStatus;
}

static CellularATError_t getDataFromResp (const CellularATCommandResponse_t * pAtResp,
                                          const _socketDataRecv_t           * pDataRecv,
                                          uint32_t                            outBufSize)
{
    CellularATError_t atCoreStatus  = CELLULAR_AT_SUCCESS;
    const char      * pInputLine    = NULL;
    uint32_t          dataLenToCopy = 0;

    /* Check if the received data size is greater than the output buffer size. */
    if (*pDataRecv->pDataLen > outBufSize)
    {
        LogError(("Data is truncated, received data length %u, out buffer size %u",
                  (unsigned int) *pDataRecv->pDataLen, (unsigned int) outBufSize));
        dataLenToCopy        = outBufSize;
        *pDataRecv->pDataLen = outBufSize;
    }
    else
    {
        dataLenToCopy = *pDataRecv->pDataLen;
    }

    /* Data is stored in the next intermediate response. */
    if (pAtResp->pItm->pNext != NULL)
    {
        pInputLine = pAtResp->pItm->pNext->pLine;

        if ((pInputLine != NULL) && (dataLenToCopy > 0U))
        {
            /* Copy the data to the out buffer. */
            (void) memcpy((void *) pDataRecv->pData, (const void *) pInputLine, dataLenToCopy);
        }
        else
        {
            LogError(("Receive Data: paramerter error, data pointer %p, data to copy %u",
                      pInputLine, (unsigned int) dataLenToCopy));
            atCoreStatus = CELLULAR_AT_BAD_PARAMETER;
        }
    }
    else if (*pDataRecv->pDataLen == 0U)
    {
        /* Receive command success but no data. */
        LogDebug(("Receive Data: no data"));
    }
    else
    {
        LogError(("Receive Data: Intermediate response empty"));
        atCoreStatus = CELLULAR_AT_BAD_PARAMETER;
    }

    return atCoreStatus;
}

static CellularPktStatus_t socketRecvDataPrefix (void     * pCallbackContext,
                                                 char     * pLine,
                                                 uint32_t   lineLength,
                                                 char    ** ppDataStart,
                                                 uint32_t * pDataLength)
{
    char              * pDataStart       = NULL;
    uint32_t            prefixLineLength = 0U;
    int32_t             tempValue        = 0;
    CellularATError_t   atResult         = CELLULAR_AT_SUCCESS;
    CellularPktStatus_t pktStatus        = CELLULAR_PKT_STATUS_OK;
    uint32_t            i                = 0;
    char                pLocalLine[RM_CELLULAR_RYZ_MAX_SQNSSRECV_STRING_PREFIX_STRING + 1] = "\0";
    uint32_t            localLineLength = RM_CELLULAR_RYZ_MAX_SQNSSRECV_STRING_PREFIX_STRING >
                                          lineLength ? lineLength : RM_CELLULAR_RYZ_MAX_SQNSSRECV_STRING_PREFIX_STRING;

    (void) pCallbackContext;

    if ((pLine == NULL) || (ppDataStart == NULL) || (pDataLength == NULL))
    {
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else
    {
        /* Check if the message is a data response. */
        if (strncmp(pLine, RM_CELLULAR_RYZ_SOCKET_DATA_PREFIX_TOKEN, RM_CELLULAR_RYZ_SOCKET_DATA_PREFIX_TOKEN_LEN) == 0)
        {
            strncpy(pLocalLine, pLine, RM_CELLULAR_RYZ_MAX_SQNSSRECV_STRING_PREFIX_STRING);
            pLocalLine[RM_CELLULAR_RYZ_MAX_SQNSSRECV_STRING_PREFIX_STRING] = '\0';
            pDataStart = pLocalLine;

            /* Add a '\0' char at the end of the line. */
            for (i = 0; i < localLineLength; i++)
            {
                if ((pDataStart[i] == '\r') || (pDataStart[i] == '\n'))
                {
                    pDataStart[i]    = '\0';
                    prefixLineLength = i;
                    break;
                }
            }

            if (i == localLineLength)
            {
                LogDebug(("Data prefix invalid line : %s", pLocalLine));
                pDataStart = NULL;
            }
        }

        if (pDataStart != NULL)
        {
            atResult = Cellular_ATStrtoi(&pDataStart[strlen("+SQNSRECV: 1,")], 10, &tempValue);

            if ((atResult == CELLULAR_AT_SUCCESS) && (tempValue >= 0) &&
                (tempValue <= (int32_t) CELLULAR_MAX_RECV_DATA_LEN))
            {
                if ((prefixLineLength + RM_CELLULAR_RYZ_DATA_PREFIX_STRING_CHANGELINE_LENGTH) > lineLength)
                {
                    /* More data is required. */
                    *pDataLength = 0;
                    pDataStart   = NULL;
                    pktStatus    = CELLULAR_PKT_STATUS_SIZE_MISMATCH;
                }
                else
                {
                    pDataStart    = &pLine[prefixLineLength];
                    pDataStart[0] = '\0';
                    pDataStart    = &pDataStart[RM_CELLULAR_RYZ_DATA_PREFIX_STRING_CHANGELINE_LENGTH];
                    *pDataLength  = (uint32_t) tempValue;
                }

                LogDebug(("DataLength %p at pktIo = %d", pDataStart, (unsigned int) *pDataLength));
            }
            else
            {
                *pDataLength = 0;
                pDataStart   = NULL;
                LogError(("Data response received with wrong size"));
            }
        }

        *ppDataStart = pDataStart;
    }

    return pktStatus;
}

static bool _checkCrsmMemoryStatus (const char * pToken)
{
    bool memoryStatus = true;

    if (pToken == NULL)
    {
        LogError(("Input Parameter NULL"));
        memoryStatus = false;
    }

    if (memoryStatus == true)
    {
        /* Checking the value sw2 in AT command response for memory problem during CRSM read.
         * Refer 3GPP Spec TS 51.011 Section 9.4. */
        if (strcmp(pToken, "64") == 0) /* '40' memory problem. */
        {
            LogError(("_checkCrsmMemoryStatus: Error in Processing HPLMN: CRSM Memory Error"));
            memoryStatus = false;
        }
    }

    return memoryStatus;
}

/*-----------------------------------------------------------*/

static bool _checkCrsmReadStatus (const char * pToken)
{
    bool readStatus = true;

    if (pToken == NULL)
    {
        LogError(("Input Parameter NULL"));
        readStatus = false;
    }

    if (readStatus == true)
    {
        /* Checking the parameter sw1 in AT command response for successful CRSM read.
         * Refer 3GPP Spec TS 51.011 Section 9.4. */
        if ((strcmp(pToken, "144") != 0) && /* '90' normal ending of the command. */
            (strcmp(pToken, "145") != 0) && /* '91' normal ending of the command, with extra information. */
            (strcmp(pToken, "146") != 0))   /* '92' command successful but after using an internal update retry routine 'X' times. */
        {
            LogError(("_checkCrsmReadStatus: Error in Processing HPLMN: CRSM Read Error"));
            readStatus = false;
        }
    }

    return readStatus;
}

/*-----------------------------------------------------------*/

static bool _parseHplmn (char * pToken, void * pData)
{
    bool                 parseStatus = true;
    CellularPlmnInfo_t * plmn        = (CellularPlmnInfo_t *) pData;

    if (pToken == NULL)
    {
        LogError(("_parseHplmn: pToken is NULL or pData is NULL"));
        parseStatus = false;
    }
    else if (strlen(pToken) < (RM_CELLULAR_RYZ_CRSM_HPLMN_RAT_LENGTH))
    {
        LogError(("_parseHplmn: Error in processing HPLMN invalid token %s", pToken));
        parseStatus = false;
    }
    else
    {
        /* Returning only the very first HPLMN present in EFHPLMNwACT in SIM.
         * EF-HPLMNwACT can contain a maximum of 10 HPLMN entries in decreasing order of priority.
         * In this implementation, returning the very first HPLMN is the PLMN priority list. */

        /* Refer TS 51.011 Section 10.3.37 for encoding. */
        plmn->mcc[0] = pToken[1];
        plmn->mcc[1] = pToken[0];
        plmn->mcc[2] = pToken[3];
        plmn->mnc[0] = pToken[5];
        plmn->mnc[1] = pToken[4];

        if (pToken[2] != 'F')
        {
            plmn->mnc[2] = pToken[2];
            plmn->mnc[3] = '\0';
        }
        else
        {
            plmn->mnc[2] = '\0';
        }
    }

    return parseStatus;
}

/*-----------------------------------------------------------*/

static CellularPktStatus_t _Cellular_RecvFuncGetHplmn (CellularContext_t                 * pContext,
                                                       const CellularATCommandResponse_t * pAtResp,
                                                       void                              * pData,
                                                       uint16_t                            dataLen)
{
    bool                parseStatus   = true;
    CellularPktStatus_t pktStatus     = CELLULAR_PKT_STATUS_OK;
    CellularATError_t   atCoreStatus  = CELLULAR_AT_SUCCESS;
    char              * pCrsmResponse = NULL;
    char              * pToken        = NULL;

    if (pContext == NULL)
    {
        LogError(("GetHplmn: pContext is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_INVALID_HANDLE;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("GetHplmn: Response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if ((pData == NULL) || (dataLen != sizeof(CellularPlmnInfo_t)))
    {
        LogError(("GetHplmn: pData is invalid or dataLen is wrong"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else
    {
        pCrsmResponse = pAtResp->pItm->pLine;
        atCoreStatus  = Cellular_ATRemoveAllWhiteSpaces(pCrsmResponse);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Removing the CRSM prefix in AT Response. */
            atCoreStatus = Cellular_ATRemovePrefix(&pCrsmResponse);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Removing All quotes in the AT Response. */
            atCoreStatus = Cellular_ATRemoveAllDoubleQuote(pCrsmResponse);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Getting the next token separated by comma in At Response. */
            atCoreStatus = Cellular_ATGetNextTok(&pCrsmResponse, &pToken);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            parseStatus = _checkCrsmReadStatus(pToken);

            if (parseStatus == false)
            {
                atCoreStatus = CELLULAR_AT_ERROR;
            }
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            atCoreStatus = Cellular_ATGetNextTok(&pCrsmResponse, &pToken);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            parseStatus = _checkCrsmMemoryStatus(pToken);

            if (parseStatus == false)
            {
                atCoreStatus = CELLULAR_AT_ERROR;
            }
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            atCoreStatus = Cellular_ATGetNextTok(&pCrsmResponse, &pToken);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            parseStatus = _parseHplmn(pToken, pData);

            if (parseStatus == false)
            {
                atCoreStatus = CELLULAR_AT_ERROR;
            }
        }

        pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);
    }

    return pktStatus;
}

/*-----------------------------------------------------------*/

static CellularPktStatus_t _Cellular_RecvFuncGetIccid (CellularContext_t                 * pContext,
                                                       const CellularATCommandResponse_t * pAtResp,
                                                       void                              * pData,
                                                       uint16_t                            dataLen)
{
    CellularPktStatus_t pktStatus    = CELLULAR_PKT_STATUS_OK;
    CellularATError_t   atCoreStatus = CELLULAR_AT_SUCCESS;
    char              * pRespLine    = NULL;
    char              * pToken       = NULL;

    if (pContext == NULL)
    {
        LogError(("getIccid: pContext is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_INVALID_HANDLE;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) ||
             (pAtResp->pItm->pLine == NULL))
    {
        LogError(("getIccid: Response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if ((pData == NULL) || (dataLen != (CELLULAR_ICCID_MAX_SIZE + 1U)))
    {
        LogError(("getIccid: pData is invalid or dataLen is wrong"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else
    {
        pRespLine    = pAtResp->pItm->pLine;
        atCoreStatus = Cellular_ATRemoveAllWhiteSpaces(pRespLine);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Removing QCCID Prefix in AT Response. */
            atCoreStatus = Cellular_ATRemovePrefix(&pRespLine);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Removing All quotes in the AT Response. */
            atCoreStatus = Cellular_ATRemoveAllDoubleQuote(pRespLine);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Getting the next token separated by comma in At Response. */
            atCoreStatus = Cellular_ATGetNextTok(&pRespLine, &pToken);
        }

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            /* Storing the ICCID value in the AT Response. */
            if (strlen(pToken) < ((size_t) CELLULAR_ICCID_MAX_SIZE + 1U))
            {
                (void) strncpy(pData, pToken, dataLen);
            }
            else
            {
                atCoreStatus = CELLULAR_AT_BAD_PARAMETER;
            }
        }

        pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);
    }

    return pktStatus;
}

/*-----------------------------------------------------------*/

static CellularPktStatus_t _Cellular_RecvFuncGetImsi (CellularContext_t                 * pContext,
                                                      const CellularATCommandResponse_t * pAtResp,
                                                      void                              * pData,
                                                      uint16_t                            dataLen)
{
    CellularPktStatus_t pktStatus    = CELLULAR_PKT_STATUS_OK;
    CellularATError_t   atCoreStatus = CELLULAR_AT_SUCCESS;
    char              * pRespLine    = NULL;

    if (pContext == NULL)
    {
        LogError(("getImsi: pContext is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_INVALID_HANDLE;
    }
    else if ((pAtResp == NULL) || (pAtResp->pItm == NULL) || (pAtResp->pItm->pLine == NULL))
    {
        LogError(("getImsi: Response is invalid"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else if ((pData == NULL) || (dataLen != (CELLULAR_IMSI_MAX_SIZE + 1U)))
    {
        LogError(("getImsi: pData is invalid or dataLen is wrong"));
        pktStatus = CELLULAR_PKT_STATUS_BAD_PARAM;
    }
    else
    {
        pRespLine = pAtResp->pItm->pLine;

        /* Removing all the Spaces in the AT Response. */
        atCoreStatus = Cellular_ATRemoveAllWhiteSpaces(pRespLine);

        if (atCoreStatus == CELLULAR_AT_SUCCESS)
        {
            if (strlen(pRespLine) < (CELLULAR_IMSI_MAX_SIZE + 1U))
            {
                (void) strncpy((char *) pData, pRespLine, dataLen);
            }
            else
            {
                atCoreStatus = CELLULAR_AT_ERROR;
            }
        }

        pktStatus = _Cellular_TranslateAtCoreStatus(atCoreStatus);
    }

    return pktStatus;
}

/* Implementation of Cellular_SetPdnConfig */
CellularError_t Cellular_SetPdnConfig (CellularHandle_t            cellularHandle,
                                       uint8_t                     contextId,
                                       const CellularPdnConfig_t * pPdnConfig)
{
    CellularContext_t * pContext       = (CellularContext_t *) cellularHandle;
    CellularError_t     cellularStatus = CELLULAR_SUCCESS;
    CellularPktStatus_t pktStatus      = CELLULAR_PKT_STATUS_OK;

    char cmdBuf[CELLULAR_AT_CMD_MAX_SIZE * 2] = {'\0'}; /* APN and auth info is too long */

    CellularAtReq_t atReqSetPdn =
    {
        cmdBuf,
        CELLULAR_AT_NO_RESULT,
        NULL,
        NULL,
        NULL,
        0,
    };

    if (pPdnConfig == NULL)
    {
        LogError(("Cellular_ATCommandRaw: Input parameter is NULL"));
        cellularStatus = CELLULAR_BAD_PARAMETER;
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        cellularStatus = _Cellular_IsValidPdn(contextId);
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        /* Make sure the library is open. */
        cellularStatus = _Cellular_CheckLibraryStatus(pContext);
    }

    if (cellularStatus == CELLULAR_SUCCESS)
    {
        const char * pPdnType;

        /* Set PDN context IP type string for AT+CGDCONT */
        if (pPdnConfig->pdnContextType == CELLULAR_PDN_CONTEXT_IPV6)
        {
            pPdnType = "IPV6";
        }
        else if (pPdnConfig->pdnContextType == CELLULAR_PDN_CONTEXT_IPV4V6)
        {
            pPdnType = "IPV4V6";
        }
        else
        {
            pPdnType = "IP";           // default: CELLULAR_PDN_CONTEXT_IPV4
        }

        /* Build AT+CGDCONT command to set the PDN context type and APN name */
        (void) snprintf(cmdBuf, sizeof(cmdBuf), "AT+CGDCONT=%d,\"%s\",\"%s\"", contextId, pPdnType,
                        pPdnConfig->apnName);

        pktStatus = _Cellular_AtcmdRequestWithCallback(pContext, atReqSetPdn);

        if (pktStatus != CELLULAR_PKT_STATUS_OK)
        {
            LogError(("Cellular_SetPdnConfig: can't set PDN, cmdBuf:%s, PktRet: %d", cmdBuf, pktStatus));
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
        }

        /* Check if APN authentication is specified */
        if (pPdnConfig->pdnAuthType == 0)
        {
            (void) snprintf(cmdBuf, sizeof(cmdBuf), "AT+CGAUTH=%d,0", contextId);
        }
        else
        {
            /* Send AT+CGAUTH command to set APN authentication type, username, and password */
            (void) snprintf(cmdBuf,
                            sizeof(cmdBuf),
                            "AT+CGAUTH=%d,%d,\"%s\",\"%s\"",
                            contextId,
                            pPdnConfig->pdnAuthType,
                            pPdnConfig->username,
                            pPdnConfig->password);
        }

        pktStatus = _Cellular_AtcmdRequestWithCallback(pContext, atReqSetPdn);

        if (pktStatus != CELLULAR_PKT_STATUS_OK)
        {
            LogError(("Cellular_SetPdnConfig: can't set PDN, cmdBuf:%s, PktRet: %d", cmdBuf, pktStatus));
            cellularStatus = _Cellular_TranslatePktStatus(pktStatus);
        }
    }

    return cellularStatus;
}
