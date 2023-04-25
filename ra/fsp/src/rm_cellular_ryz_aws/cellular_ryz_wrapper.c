/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* The config header is always included first. */
#include "cellular_platform.h"
#include "cellular_config.h"
#include "cellular_config_defaults.h"

#include "cellular_types.h"
#include "cellular_api.h"
#include "cellular_common.h"
#include "cellular_common_api.h"

/* Cellular module includes. */
#include "cellular_ryz.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Cellular_Cleanup wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_Cleanup (CellularHandle_t cellularHandle)
{
    return Cellular_CommonCleanup(cellularHandle);
}

/*******************************************************************************************************************//**
 * Cellular_RegisterUrcNetworkRegistrationEventCallback wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_RegisterUrcNetworkRegistrationEventCallback (
    CellularHandle_t                         cellularHandle,
    CellularUrcNetworkRegistrationCallback_t networkRegistrationCallback,
    void                                   * pCallbackContext)
{
    return Cellular_CommonRegisterUrcNetworkRegistrationEventCallback(cellularHandle,
                                                                      networkRegistrationCallback,
                                                                      pCallbackContext);
}

/*******************************************************************************************************************//**
 * Cellular_RegisterUrcPdnEventCallback wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_RegisterUrcPdnEventCallback (CellularHandle_t              cellularHandle,
                                                      CellularUrcPdnEventCallback_t pdnEventCallback,
                                                      void                        * pCallbackContext)
{
    return Cellular_CommonRegisterUrcPdnEventCallback(cellularHandle, pdnEventCallback, pCallbackContext);
}

/*******************************************************************************************************************//**
 * Cellular_RegisterUrcGenericCallback wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_RegisterUrcGenericCallback (CellularHandle_t             cellularHandle,
                                                     CellularUrcGenericCallback_t genericCallback,
                                                     void                       * pCallbackContext)
{
    return Cellular_CommonRegisterUrcGenericCallback(cellularHandle, genericCallback, pCallbackContext);
}

/*******************************************************************************************************************//**
 * Cellular_RegisterModemEventCallback wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_RegisterModemEventCallback (CellularHandle_t             cellularHandle,
                                                     CellularModemEventCallback_t modemEventCallback,
                                                     void                       * pCallbackContext)
{
    return Cellular_CommonRegisterModemEventCallback(cellularHandle, modemEventCallback, pCallbackContext);
}

/*******************************************************************************************************************//**
 * Cellular_ATCommandRaw wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_ATCommandRaw (CellularHandle_t                            cellularHandle,
                                       const char                                * pATCommandPrefix,
                                       const char                                * pATCommandPayload,
                                       CellularATCommandType_t                     atCommandType,
                                       CellularATCommandResponseReceivedCallback_t responseReceivedCallback,
                                       void                                      * pData,
                                       uint16_t                                    dataLen)
{
    return Cellular_CommonATCommandRaw(cellularHandle,
                                       pATCommandPrefix,
                                       pATCommandPayload,
                                       atCommandType,
                                       responseReceivedCallback,
                                       pData,
                                       dataLen);
}

/*******************************************************************************************************************//**
 * Cellular_CreateSocket wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_CreateSocket (CellularHandle_t         cellularHandle,
                                       uint8_t                  pdnContextId,
                                       CellularSocketDomain_t   socketDomain,
                                       CellularSocketType_t     socketType,
                                       CellularSocketProtocol_t socketProtocol,
                                       CellularSocketHandle_t * pSocketHandle)
{
    return Cellular_CommonCreateSocket(cellularHandle,
                                       pdnContextId,
                                       socketDomain,
                                       socketType,
                                       socketProtocol,
                                       pSocketHandle);
}

/*******************************************************************************************************************//**
 * Cellular_SocketSetSockOpt wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_SocketSetSockOpt (CellularHandle_t            cellularHandle,
                                           CellularSocketHandle_t      socketHandle,
                                           CellularSocketOptionLevel_t optionLevel,
                                           CellularSocketOption_t      option,
                                           const uint8_t             * pOptionValue,
                                           uint32_t                    optionValueLength)
{
    return Cellular_CommonSocketSetSockOpt(cellularHandle,
                                           socketHandle,
                                           optionLevel,
                                           option,
                                           pOptionValue,
                                           optionValueLength);
}

/*******************************************************************************************************************//**
 * Cellular_SocketRegisterDataReadyCallback wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_SocketRegisterDataReadyCallback (CellularHandle_t                  cellularHandle,
                                                          CellularSocketHandle_t            socketHandle,
                                                          CellularSocketDataReadyCallback_t dataReadyCallback,
                                                          void                            * pCallbackContext)
{
    return Cellular_CommonSocketRegisterDataReadyCallback(cellularHandle,
                                                          socketHandle,
                                                          dataReadyCallback,
                                                          pCallbackContext);
}

/*******************************************************************************************************************//**
 * Cellular_SocketRegisterSocketOpenCallback wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_SocketRegisterSocketOpenCallback (CellularHandle_t             cellularHandle,
                                                           CellularSocketHandle_t       socketHandle,
                                                           CellularSocketOpenCallback_t socketOpenCallback,
                                                           void                       * pCallbackContext)
{
    return Cellular_CommonSocketRegisterSocketOpenCallback(cellularHandle,
                                                           socketHandle,
                                                           socketOpenCallback,
                                                           pCallbackContext);
}

/*******************************************************************************************************************//**
 * Cellular_SocketRegisterClosedCallback wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_SocketRegisterClosedCallback (CellularHandle_t               cellularHandle,
                                                       CellularSocketHandle_t         socketHandle,
                                                       CellularSocketClosedCallback_t closedCallback,
                                                       void                         * pCallbackContext)
{
    return Cellular_CommonSocketRegisterClosedCallback(cellularHandle, socketHandle, closedCallback, pCallbackContext);
}

/*******************************************************************************************************************//**
 * Cellular_RfOn wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_RfOn (CellularHandle_t cellularHandle)
{
    return Cellular_CommonRfOn(cellularHandle);
}

/*******************************************************************************************************************//**
 * Cellular_RfOff wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_RfOff (CellularHandle_t cellularHandle)
{
    return Cellular_CommonRfOff(cellularHandle);
}

/*******************************************************************************************************************//**
 * Cellular_GetIPAddress wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_GetIPAddress (CellularHandle_t cellularHandle,
                                       uint8_t          contextId,
                                       char           * pBuffer,
                                       uint32_t         bufferLength)
{
    return Cellular_CommonGetIPAddress(cellularHandle, contextId, pBuffer, bufferLength);
}

/*******************************************************************************************************************//**
 * Cellular_GetModemInfo wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_GetModemInfo (CellularHandle_t cellularHandle, CellularModemInfo_t * pModemInfo)
{
    return Cellular_CommonGetModemInfo(cellularHandle, pModemInfo);
}

/*******************************************************************************************************************//**
 * Cellular_CommonGetRegisteredNetwork wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_GetRegisteredNetwork (CellularHandle_t cellularHandle, CellularPlmnInfo_t * pNetworkInfo)
{
    return Cellular_CommonGetRegisteredNetwork(cellularHandle, pNetworkInfo);
}

/*******************************************************************************************************************//**
 * Cellular_GetNetworkTime wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_GetNetworkTime (CellularHandle_t cellularHandle, CellularTime_t * pNetworkTime)
{
    return Cellular_CommonGetNetworkTime(cellularHandle, pNetworkTime);
}

/*******************************************************************************************************************//**
 * Cellular_GetPsmSettings wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_GetPsmSettings (CellularHandle_t cellularHandle, CellularPsmSettings_t * pPsmSettings)
{
    return Cellular_CommonGetPsmSettings(cellularHandle, pPsmSettings);
}

/*******************************************************************************************************************//**
 * Cellular_GetEidrxSettings wrapper, implemented by Cellular Common
 **********************************************************************************************************************/
CellularError_t Cellular_GetEidrxSettings (CellularHandle_t              cellularHandle,
                                           CellularEidrxSettingsList_t * pEidrxSettingsList)
{
    return Cellular_CommonGetEidrxSettings(cellularHandle, pEidrxSettingsList);
}

/*******************************************************************************************************************//**
 * Cellular_SetRatPriority wrapper, currently not supported since RYZ014A only supports CAT-M1
 **********************************************************************************************************************/
CellularError_t Cellular_SetRatPriority (CellularHandle_t      cellularHandle,
                                         const CellularRat_t * pRatPriorities,
                                         uint8_t               ratPrioritiesLength)
{
    FSP_PARAMETER_NOT_USED(cellularHandle);
    FSP_PARAMETER_NOT_USED(pRatPriorities);
    FSP_PARAMETER_NOT_USED(ratPrioritiesLength);

    return CELLULAR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Cellular_GetRatPriority wrapper, currently not supported since RYZ014A only supports CAT-M1
 **********************************************************************************************************************/
CellularError_t Cellular_GetRatPriority (CellularHandle_t cellularHandle,
                                         CellularRat_t  * pRatPriorities,
                                         uint8_t          ratPrioritiesLength,
                                         uint8_t        * pOutputRatPrioritiesLength)
{
    FSP_PARAMETER_NOT_USED(cellularHandle);
    FSP_PARAMETER_NOT_USED(pRatPriorities);
    FSP_PARAMETER_NOT_USED(ratPrioritiesLength);
    FSP_PARAMETER_NOT_USED(pOutputRatPrioritiesLength);

    return CELLULAR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Cellular_SetDns wrapper, currently not supported since RYZ014A uses dynamic DNS addresses.
 **********************************************************************************************************************/
CellularError_t Cellular_SetDns (CellularHandle_t cellularHandle, uint8_t contextId, const char * pDnsServerAddress)
{
    FSP_PARAMETER_NOT_USED(cellularHandle);
    FSP_PARAMETER_NOT_USED(contextId);
    FSP_PARAMETER_NOT_USED(pDnsServerAddress);

    return CELLULAR_UNSUPPORTED;
}
