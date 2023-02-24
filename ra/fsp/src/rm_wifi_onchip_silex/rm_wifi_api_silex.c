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
#include <string.h>

#include "rm_wifi_onchip_silex.h"

#if (BSP_CFG_RTOS == 2)

/* FreeRTOS includes. */
 #include "FreeRTOS.h"

/* Socket and WiFi interface includes. */
 #include "rm_wifi_api.h"

/* WiFi configuration includes. */
 #include "rm_wifi_config.h"

/**
 *  Turns on Wi-Fi.
 *
 * This function turns on Wi-Fi module,initializes the drivers and must be called
 * before calling any other Wi-Fi API
 *
 * @return eWiFiSuccess if Wi-Fi module was successfully turned on, failure code otherwise.
 */
WIFIReturnCode_t WIFI_On (void) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    fsp_err_t        ret     = FSP_ERR_WIFI_FAILED;

    ret = rm_wifi_onchip_silex_open(&g_wifi_onchip_silex_cfg);
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

/**
 *  Turns off Wi-Fi.
 *
 * This function turns off the Wi-Fi module. The Wi-Fi peripheral should be put in a
 * low power or off state in this routine.
 *
 * @return eWiFiSuccess if Wi-Fi module was successfully turned off, failure code otherwise.
 */
WIFIReturnCode_t WIFI_Off (void) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    int32_t          ret     = FSP_ERR_WIFI_FAILED;

    ret = (int32_t) rm_wifi_onchip_silex_close();
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

/**
 *  Connects to the Wi-Fi Access Point (AP) specified in the input.
 *
 * The Wi-Fi should stay connected when the same Access Point it is currently connected to
 * is specified. Otherwise, the Wi-Fi should disconnect and connect to the new Access Point
 * specified. If the new Access Point specifed has invalid parameters, then the Wi-Fi should be
 * disconnected.
 *
 * @param[in] pxNetworkParams Configuration to join AP.
 *
 * @return eWiFiSuccess if connection is successful, failure code otherwise.
 *
 * @code
 * WIFINetworkParams_t xNetworkParams;
 * WIFIReturnCode_t xWifiStatus;
 * xNetworkParams.pcSSID = "SSID String";
 * xNetworkParams.ucSSIDLength = SSIDLen;
 * xNetworkParams.pcPassword = "Password String";
 * xNetworkParams.ucPasswordLength = PassLength;
 * xNetworkParams.xSecurity = eWiFiSecurityWPA2;
 * xWifiStatus = WIFI_ConnectAP( &( xNetworkParams ) );
 * if(xWifiStatus == eWiFiSuccess)
 * {
 *     //Connected to AP.
 * }
 * @endcode
 *
 * @see WIFINetworkParams_t
 */
WIFIReturnCode_t WIFI_ConnectAP (const WIFINetworkParams_t * const pxNetworkParams) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    int32_t          ret     = -1;

    if ((NULL == pxNetworkParams) || (0 == pxNetworkParams->ucSSIDLength) ||
        (0 == pxNetworkParams->xPassword.xWPA.ucLength))
    {
        return eWiFiFailure;
    }

    if (pxNetworkParams->xSecurity >= eWiFiSecurityNotSupported)
    {
        return eWiFiFailure;
    }

    if ((0 == pxNetworkParams->xPassword.xWPA.ucLength) &&
        (eWiFiSecurityOpen != pxNetworkParams->xSecurity))
    {
        return eWiFiFailure;
    }

    if (pxNetworkParams->ucSSIDLength > wificonfigMAX_SSID_LEN)
    {
        return eWiFiFailure;
    }

    if (pxNetworkParams->xPassword.xWPA.ucLength > wificonfigMAX_PASSPHRASE_LEN)
    {
        return eWiFiFailure;
    }

    ret =
        (int32_t) rm_wifi_onchip_silex_connect((char *) pxNetworkParams->ucSSID,
                                               pxNetworkParams->xSecurity,
                                               pxNetworkParams->xPassword.xWPA.cPassphrase);
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

/**
 *  Disconnects from the currently connected Access Point.
 *
 * @return eWiFiSuccess if disconnection was successful or if the device is already
 * disconnected, failure code otherwise.
 */
WIFIReturnCode_t WIFI_Disconnect (void) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    int32_t          ret     = -1;

    ret = (int32_t) rm_wifi_onchip_silex_disconnect();
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

/**
 *  Resets the Wi-Fi Module.
 *
 * @return eWiFiSuccess if Wi-Fi module was successfully reset, failure code otherwise.
 */
WIFIReturnCode_t WIFI_Reset (void)
{
    WIFIReturnCode_t ret;

    ret = WIFI_Off();
    if (ret)
    {
        return eWiFiFailure;
    }

    ret = WIFI_On();
    if (ret)
    {
        return eWiFiFailure;
    }

    return eWiFiSuccess;
}

/**
 *  Perform a Wi-Fi network Scan.
 *
 * @param[in] pxBuffer - Buffer for scan results.
 * @param[in] ucNumNetworks - Number of networks to retrieve in scan result.
 *
 * @return eWiFiSuccess if the Wi-Fi network scan was successful, failure code otherwise.
 *
 * @note The input buffer will have the results of the scan.
 *
 * @code
 * const uint8_t ucNumNetworks = 10; //Get 10 scan results
 * WIFIScanResult_t xScanResults[ ucNumNetworks ];
 * WIFI_Scan( xScanResults, ucNumNetworks );
 * @endcode
 */
WIFIReturnCode_t WIFI_Scan (WIFIScanResult_t * pxBuffer, uint8_t ucNumNetworks)
{
    fsp_err_t err = FSP_SUCCESS;

    err = rm_wifi_onchip_silex_scan(pxBuffer, ucNumNetworks);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, eWiFiFailure);

    return eWiFiSuccess;
}

WIFIReturnCode_t WIFI_SetMode (WIFIDeviceMode_t xDeviceMode)
{
    FSP_PARAMETER_NOT_USED(xDeviceMode);

    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_GetMode (WIFIDeviceMode_t * pxDeviceMode)
{
    FSP_PARAMETER_NOT_USED(pxDeviceMode);

    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_NetworkAdd (const WIFINetworkProfile_t * const pxNetworkProfile, uint16_t * pusIndex)
{
    FSP_PARAMETER_NOT_USED(pxNetworkProfile);
    FSP_PARAMETER_NOT_USED(pusIndex);

    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_NetworkGet (WIFINetworkProfile_t * pxNetworkProfile, uint16_t usIndex)
{
    FSP_PARAMETER_NOT_USED(pxNetworkProfile);
    FSP_PARAMETER_NOT_USED(usIndex);

    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_NetworkDelete (uint16_t usIndex)
{
    FSP_PARAMETER_NOT_USED(usIndex);

    return eWiFiNotSupported;
}

/**
 *  Ping an IP address in the network.
 *
 * @param[in] pucIPAddr     IP Address array to ping.
 * @param[in] usCount       Number of times to ping
 * @param[in] ulIntervalMS  Interval in milliseconds for ping operation
 *
 * @return eWiFiSuccess if ping was successful, other failure code otherwise.
 */
WIFIReturnCode_t WIFI_Ping (uint8_t * pucIPAddr, uint16_t usCount, uint32_t ulIntervalMS) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    int32_t          ret     = -1;

    ret = (int32_t) rm_wifi_onchip_silex_ping(pucIPAddr, usCount, ulIntervalMS);
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

/**
 * @brief Get IP configuration (IP address, NetworkMask, Gateway and
 *        DNS server addresses).
 *
 * @param[out] pxIPInfo - Current IP configuration.
 *
 * @return eWiFiSuccess if successful and IP Address buffer has the interface's IP address,
 * failure code otherwise.
 *
 * **Example**
 * @code
 * WIFIIPConfiguration_t xIPInfo;
 * WIFI_GetIPInfo( &xIPInfo );
 * @endcode
 */
WIFIReturnCode_t WIFI_GetIPInfo (WIFIIPConfiguration_t * pxIPInfo) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    int32_t          ret     = -1;

    ret = (int32_t) rm_wifi_onchip_silex_ip_addr_get(pxIPInfo->xIPAddress.ulAddress);
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

/**
 *  Retrieves the Wi-Fi interface's MAC address.
 *
 * @param[out] pucMac   MAC Address buffer sized 6 bytes.
 *
 * @code
 * uint8_t ucMacAddressVal[ wificonfigMAX_BSSID_LEN ];
 * WIFI_GetMAC( &ucMacAddressVal[0] );
 * @endcode
 *
 * @return eWiFiSuccess if the MAC address was successfully retrieved, failure code
 * otherwise. The returned MAC address must be 6 consecutive bytes with no delimitters.
 */
WIFIReturnCode_t WIFI_GetMAC (uint8_t * pucMac) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    int32_t          ret     = -1;

    ret = (int32_t) rm_wifi_onchip_silex_mac_addr_get(pucMac);
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

/**
 *  Retrieves the host IP address from a host name using DNS.
 *
 * @param[in] pcHost - Host (node) name.
 * @param[in] pucIPAddr - IP Address buffer.
 *
 * @return eWiFiSuccess if the host IP address was successfully retrieved, failure code
 * otherwise.
 *
 * @code
 * uint8_t ucIPAddr[ 4 ];
 * WIFI_GetHostIP( "amazon.com", &ucIPAddr[0] );
 * @endcode
 */
WIFIReturnCode_t WIFI_GetHostIP (char * pcHost, uint8_t * pucIPAddr) {
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    int32_t          ret     = -1;

    if ((NULL == pcHost) || (NULL == pucIPAddr))
    {
        return eWiFiFailure;
    }

    ret = (int32_t) rm_wifi_onchip_silex_dns_query(pcHost, pucIPAddr);
    if (!ret)
    {
        xRetVal = eWiFiSuccess;
    }

    return xRetVal;
}

WIFIReturnCode_t WIFI_StartAP (void) {
    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_StopAP (void) {
    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_ConfigureAP (const WIFINetworkParams_t * const pxNetworkParams) {
    /* FIX ME. */
    FSP_PARAMETER_NOT_USED(pxNetworkParams);

    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_SetPMMode (WIFIPMMode_t xPMModeType, const void * pvOptionValue) {
    /* FIX ME. */
    FSP_PARAMETER_NOT_USED(xPMModeType);
    FSP_PARAMETER_NOT_USED(pvOptionValue);

    return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_GetPMMode (WIFIPMMode_t * pxPMModeType, void * pvOptionValue) {
    /* FIX ME. */
    FSP_PARAMETER_NOT_USED(pxPMModeType);
    FSP_PARAMETER_NOT_USED(pvOptionValue);

    return eWiFiNotSupported;
}

/**
 *
 * @brief Check if the Wi-Fi is connected and the AP configuration matches the query.
 *
 * param[in] pxNetworkParams - Network parameters to query, if NULL then just check the
 * Wi-Fi link status.
 */
BaseType_t WIFI_IsConnected (const WIFINetworkParams_t * pxNetworkParams) {
    BaseType_t xIsConnected = pdFALSE;
    fsp_err_t  status       = FSP_SUCCESS;

    FSP_PARAMETER_NOT_USED(pxNetworkParams);

    rm_wifi_onchip_silex_socket_connected(&status);
    if (0 == status)
    {
        xIsConnected = pdTRUE;
    }

    return xIsConnected;
}

#endif
