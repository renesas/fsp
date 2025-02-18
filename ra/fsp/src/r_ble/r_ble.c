/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include <stdlib.h>

#include "r_ble_api.h"

#include "fsp_common_api.h"

#if (BSP_CFG_RTOS == 1)
 #include "tx_api.h"
#elif (BSP_CFG_RTOS == 2)
 #include "FreeRTOS.h"
 #include "task.h"
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 0)
  #include "semphr.h"
 #else
  #include "event_groups.h"
 #endif
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if (BSP_CFG_RTOS == 2)
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 1)
  #define BLE_EVENT_PATTERN    (0x0A0A)
 #endif
#endif

/***********************************************************************************************************************
 * Local Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions
 **********************************************************************************************************************/

ble_status_t R_BLE_GAP_SetPerAdvRecvEnable (uint16_t sync_hdl, uint8_t enable) {
    FSP_PARAMETER_NOT_USED(sync_hdl);
    FSP_PARAMETER_NOT_USED(enable);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetCteConnlessParam (st_ble_gap_cte_connless_t * p_cte_param) {
    FSP_PARAMETER_NOT_USED(p_cte_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_EnableCteConnless (uint16_t adv_hdl, uint8_t enable) {
    FSP_PARAMETER_NOT_USED(adv_hdl);
    FSP_PARAMETER_NOT_USED(enable);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_StartCteConnlessRecv (st_ble_gap_cte_connless_recv_t * p_cte_recv) {
    FSP_PARAMETER_NOT_USED(p_cte_recv);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_StopCteConnlessRecv (uint16_t sync_hdl) {
    FSP_PARAMETER_NOT_USED(sync_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetCteConnParam (st_ble_gap_cte_conn_t * p_cte_param) {
    FSP_PARAMETER_NOT_USED(p_cte_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_EnableCteConnRsp (uint16_t conn_hdl, uint8_t enable) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(enable);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetCteConnRecvParam (st_ble_gap_cte_conn_rx_param_t * p_cte_param) {
    FSP_PARAMETER_NOT_USED(p_cte_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_StopCteConnRecvSampling (uint16_t conn_hdl) {
    FSP_PARAMETER_NOT_USED(conn_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_StartCteConnReq (st_ble_gap_cte_conn_req_t * p_req) {
    FSP_PARAMETER_NOT_USED(p_req);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_StopCteConnReq (uint16_t handle) {
    FSP_PARAMETER_NOT_USED(handle);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetDefaultSubrate (st_ble_gap_subrate_param_t * p_subrate_param) {
    FSP_PARAMETER_NOT_USED(p_subrate_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_RequestSubrate (uint16_t conn_hdl, st_ble_gap_subrate_param_t * p_subrate_param) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(p_subrate_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_StartPerdAdvSetInfoTransfer (uint16_t adv_hdl, uint16_t conn_hdl, uint16_t service_data) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(adv_hdl);
    FSP_PARAMETER_NOT_USED(service_data);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_StartPerdAdvSyncTransfer (uint16_t sync_hdl, uint16_t conn_hdl, uint16_t service_data) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(sync_hdl);
    FSP_PARAMETER_NOT_USED(service_data);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetPerdAdvSyncTransferParam (uint16_t conn_hdl, st_ble_gap_past_param_t * p_past_param) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(p_past_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetDefPerdAdvSyncTransferParam (st_ble_gap_past_param_t * p_past_param) {
    FSP_PARAMETER_NOT_USED(p_past_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_ReadAntennaInfo (void) {
    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_ReceiverTest (st_ble_gap_recv_test_param_t * p_rx_test_param) {
    FSP_PARAMETER_NOT_USED(p_rx_test_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_TransmitterTest (st_ble_gap_trans_test_param_t * p_tx_test_param) {
    FSP_PARAMETER_NOT_USED(p_tx_test_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_ModifySleepClockAccuracy (uint8_t act) {
    FSP_PARAMETER_NOT_USED(act);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_ReadRemoteTransmitPowerLevel (uint16_t conn_hdl, uint8_t phy) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(phy);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetPathLossReportingParam (st_ble_gap_set_path_loss_rpt_param_t * p_loss_rpt_param) {
    FSP_PARAMETER_NOT_USED(p_loss_rpt_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetPathLossReportingEnable (uint16_t conn_hdl, uint8_t enable) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(enable);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetTransmitPowerReportingEnable (uint16_t conn_hdl, uint8_t local_enable,
                                                        uint8_t remote_enable) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(local_enable);
    FSP_PARAMETER_NOT_USED(remote_enable);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetDataRelatedAddrChanges (uint8_t adv_hdl, uint8_t change_reason) {
    FSP_PARAMETER_NOT_USED(adv_hdl);
    FSP_PARAMETER_NOT_USED(change_reason);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_TestEnd (void) {
    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_ReqPeerSCA (uint16_t conn_hdl) {
    FSP_PARAMETER_NOT_USED(conn_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_EnhancedReadTxPowerLevel (uint16_t conn_hdl, uint8_t phy) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(phy);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_GAP_SetHostFeat (uint8_t bit_number, uint8_t bit_value) {
    FSP_PARAMETER_NOT_USED(bit_number);
    FSP_PARAMETER_NOT_USED(bit_value);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_CreateBig (uint8_t * p_big_hdl, uint8_t adv_hdl, st_ble_iso_big_param_t * p_big_param) {
    FSP_PARAMETER_NOT_USED(p_big_hdl);
    FSP_PARAMETER_NOT_USED(adv_hdl);
    FSP_PARAMETER_NOT_USED(p_big_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_StopBig (uint8_t big_hdl, uint8_t reason) {
    FSP_PARAMETER_NOT_USED(big_hdl);
    FSP_PARAMETER_NOT_USED(reason);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_CreateBigSync (uint8_t                     * p_big_hdl,
                                      uint16_t                      sync_hdl,
                                      st_ble_iso_big_sync_param_t * p_big_sync_param) {
    FSP_PARAMETER_NOT_USED(p_big_hdl);
    FSP_PARAMETER_NOT_USED(sync_hdl);
    FSP_PARAMETER_NOT_USED(p_big_sync_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_TerminateBigSync (uint8_t big_hdl) {
    FSP_PARAMETER_NOT_USED(big_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_SetCigParam (uint8_t * p_cig_id, st_ble_iso_cig_param_t * p_cig_param) {
    FSP_PARAMETER_NOT_USED(p_cig_id);
    FSP_PARAMETER_NOT_USED(p_cig_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_CreateCis (st_ble_iso_cis_conn_t * p_cis_conn) {
    FSP_PARAMETER_NOT_USED(p_cis_conn);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_RemoveCig (uint8_t cig_id) {
    FSP_PARAMETER_NOT_USED(cig_id);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_ReplyCisRequest (uint8_t cig_id, uint8_t cis_id, uint8_t response, uint8_t reason) {
    FSP_PARAMETER_NOT_USED(cig_id);
    FSP_PARAMETER_NOT_USED(cis_id);
    FSP_PARAMETER_NOT_USED(response);
    FSP_PARAMETER_NOT_USED(reason);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_SetupDataPath (uint16_t conn_hdl, st_ble_iso_chan_path * p_path) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(p_path);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_SendData (st_ble_iso_sdu_t * p_sdu_info) {
    FSP_PARAMETER_NOT_USED(p_sdu_info);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_SendDataNoCopy (st_ble_iso_sdu_t * p_sdu_info) {
    FSP_PARAMETER_NOT_USED(p_sdu_info);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_GetTxSync (uint16_t conn_hdl) {
    FSP_PARAMETER_NOT_USED(conn_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_CreateBigTest (uint8_t                            * p_big_hdl,
                                      uint8_t                              adv_hdl,
                                      st_ble_iso_create_big_test_param_t * p_create_big_test_param) {
    FSP_PARAMETER_NOT_USED(p_big_hdl);
    FSP_PARAMETER_NOT_USED(adv_hdl);
    FSP_PARAMETER_NOT_USED(p_create_big_test_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_SetCigParamTest (uint8_t                               * p_cig_id,
                                        st_ble_iso_set_cig_param_test_param_t * p_set_cig_param_test_param) {
    FSP_PARAMETER_NOT_USED(p_cig_id);
    FSP_PARAMETER_NOT_USED(p_set_cig_param_test_param);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_TransmitTest (uint16_t conn_hdl, uint8_t payload_type) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(payload_type);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_ReceiveTest (uint16_t conn_hdl, uint8_t payload_type) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(payload_type);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_ReadTestCounters (uint16_t conn_hdl) {
    FSP_PARAMETER_NOT_USED(conn_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_TestEnd (uint16_t conn_hdl) {
    FSP_PARAMETER_NOT_USED(conn_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_ReadLinkQuality (uint16_t conn_hdl) {
    FSP_PARAMETER_NOT_USED(conn_hdl);

    return BLE_ERR_UNSUPPORTED;
};

ble_status_t R_BLE_ISO_RemoveDataPath (uint16_t conn_hdl, uint8_t dir) {
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(dir);

    return BLE_ERR_UNSUPPORTED;
};

void    r_ble_rf_control_error(uint32_t err_no);
uint8_t r_ble_rf_power_save_mode(void);

#if (BSP_CFG_RTOS == 1) || (BSP_CFG_RTOS == 2)
void r_ble_wake_up_task(void * EventGroupHandle);
void r_ble_wake_up_task_from_isr(void * EventGroupHandle);

#endif

/*** platform control functions added start ***/

void r_ble_rf_control_error (uint32_t err_no)
{
    FSP_PARAMETER_NOT_USED(err_no);
}

uint8_t r_ble_rf_power_save_mode (void)
{
    uint8_t ret = BLE_CFG_RF_DEEP_SLEEP_EN;

    return ret;
}

/*** platform control functions end ***/

#if (BSP_CFG_RTOS == 1)
void r_ble_wake_up_task (void * EventGroupHandle)
{
    if (NULL != EventGroupHandle)
    {
        tx_semaphore_put((TX_SEMAPHORE *) EventGroupHandle);
    }
}

void r_ble_wake_up_task_from_isr (void * EventGroupHandle)
{
    if (NULL != EventGroupHandle)
    {
        tx_semaphore_put((TX_SEMAPHORE *) EventGroupHandle);
    }
}

#elif (BSP_CFG_RTOS == 2)
void r_ble_wake_up_task (void * EventGroupHandle)
{
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 0)

    /* Semaphore notifications */
    SemaphoreHandle_t semaphore_handle = (SemaphoreHandle_t) EventGroupHandle;

    if (NULL != EventGroupHandle)
    {
        xSemaphoreGive(semaphore_handle);
    }

 #else
    EventGroupHandle_t event_group_handle = (EventGroupHandle_t) EventGroupHandle;

    /* Event flag notifications */

    if (event_group_handle != NULL)
    {
        xEventGroupSetBits(event_group_handle, (EventBits_t) BLE_EVENT_PATTERN);
        portYIELD();
    }
 #endif
}

void r_ble_wake_up_task_from_isr (void * EventGroupHandle)
{
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 0)

    /* Semaphore notifications */
    SemaphoreHandle_t semaphore_handle = (SemaphoreHandle_t) EventGroupHandle;

    if (NULL != EventGroupHandle)
    {
        xSemaphoreGiveFromISR(semaphore_handle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

 #else

    /* Event flag notifications */
    EventGroupHandle_t event_group_handle = (EventGroupHandle_t) EventGroupHandle;

    if (event_group_handle != NULL)
    {
        xEventGroupSetBitsFromISR(event_group_handle, (EventBits_t) BLE_EVENT_PATTERN, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
 #endif
}

#endif
