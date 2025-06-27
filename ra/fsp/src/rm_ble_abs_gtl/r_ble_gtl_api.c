/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include <rm_ble_abs.h>

#include "qe_ble_profile.h"
#include "r_ble_gtl.h"
#include "r_ble_gtl_security.h"

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/
extern ble_abs_instance_ctrl_t * gp_instance_ctrl;

/***********************************************************************************************************************
 * Enumerations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Static Private Variables
 **********************************************************************************************************************/
static r_ble_gtl_transport_api_t g_transport_api;

/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/
static int r_ble_gtl_api_transport_open(void * p_context);
static int r_ble_gtl_api_transport_write(void * p_context, uint8_t * p_data, uint32_t len);
static int r_ble_gtl_api_transport_close(void * p_context);

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/
ble_status_t R_BLE_Open (void)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(gp_instance_ctrl);
    FSP_ASSERT(gp_instance_ctrl->p_cfg);
 #if defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_UART)
    FSP_ASSERT(gp_instance_ctrl->p_cfg->p_uart_instance);
 #elif defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_SPI)
    FSP_ASSERT(gp_instance_ctrl->p_cfg->p_spi_instance);
    FSP_ASSERT(gp_instance_ctrl->p_cfg->p_irq_instance);
 #endif
#endif

    ble_status_t ret;

    g_transport_api.p_context = (void *) gp_instance_ctrl->p_cfg;
    g_transport_api.open      = r_ble_gtl_api_transport_open;
    g_transport_api.write     = r_ble_gtl_api_transport_write;
    g_transport_api.close     = r_ble_gtl_api_transport_close;

    ret = R_BLE_GTL_Open(&g_transport_api);

    return ret;
}

ble_status_t R_BLE_Close (void)
{
    return R_BLE_GTL_Close(&g_transport_api);
}

ble_status_t R_BLE_Execute (void)
{
    return R_BLE_GTL_Execute();
}

uint32_t R_BLE_IsTaskFree (void)
{
    return R_BLE_GTL_IsTaskFree();
}

ble_status_t R_BLE_SetEvent (ble_event_cb_t cb)
{
    FSP_PARAMETER_NOT_USED(cb);

    /* Not supported by GTL middleware */
    return BLE_ERR_UNSUPPORTED;
}

uint32_t R_BLE_GetVersion (void)
{

    /* Not supported by GTL middleware */
    return BLE_ERR_UNSUPPORTED;
}

uint32_t R_BLE_GetLibType (void)
{

    /* Not supported by GTL middleware */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_Init (ble_gap_app_cb_t gap_cb)
{
    return R_BLE_GTL_GAP_Init(gap_cb);
}

ble_status_t R_BLE_GAP_Terminate (void)
{
    return R_BLE_GTL_GAP_Terminate();
}

ble_status_t R_BLE_GAP_UpdConn (uint16_t                  conn_hdl,
                                uint8_t                   mode,
                                uint16_t                  accept,
                                st_ble_gap_conn_param_t * p_conn_updt_param)
{
    ble_status_t status;

    if (BLE_GAP_CONN_UPD_MODE_RSP == mode)
    {
        /* Send reply to a connection parameter update request */
        status = R_BLE_GTL_GAP_ConnParamUpdateCfm(conn_hdl, accept);
    }
    else if (BLE_GAP_CONN_UPD_MODE_REQ == mode)
    {
        /* Send request to update the connection parameters */
        status = R_BLE_GTL_GAP_ConnParamUpdateReq(conn_hdl, p_conn_updt_param);
    }
    else
    {
        /* Invalid mode */
        status = BLE_ERR_INVALID_ARG;
    }

    return status;
}

ble_status_t R_BLE_GAP_SetDataLen (uint16_t conn_hdl, uint16_t tx_octets, uint16_t tx_time)
{
    return R_BLE_GTL_GAP_SetDataLen(conn_hdl, tx_octets, tx_time);
}

ble_status_t R_BLE_GAP_Disconnect (uint16_t conn_hdl, uint8_t reason)
{
    return R_BLE_GTL_GAP_Disconnect(conn_hdl, reason);
}

ble_status_t R_BLE_GAP_SetPhy (uint16_t conn_hdl, st_ble_gap_set_phy_param_t * p_phy_param)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(p_phy_param);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_SetDefPhy (st_ble_gap_set_def_phy_param_t * p_def_phy_param)
{
    FSP_PARAMETER_NOT_USED(p_def_phy_param);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_SetPrivMode (st_ble_dev_addr_t * p_addr, uint8_t * p_privacy_mode, uint8_t device_num)
{
    FSP_PARAMETER_NOT_USED(p_addr);
    FSP_PARAMETER_NOT_USED(p_privacy_mode);
    FSP_PARAMETER_NOT_USED(device_num);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_ConfWhiteList (uint8_t op_code, st_ble_dev_addr_t * p_addr, uint8_t device_num)
{
    return R_BLE_GTL_GAP_ConfWhiteList(op_code, p_addr, device_num);
}

ble_status_t R_BLE_GAP_GetVerInfo (void)
{
    return R_BLE_GTL_GAP_GetVerInfo();
}

ble_status_t R_BLE_GAP_ReadPhy (uint16_t conn_hdl)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_ConfRslvList (uint8_t                          op_code,
                                     st_ble_dev_addr_t              * p_addr,
                                     st_ble_gap_rslv_list_key_set_t * p_peer_irk,
                                     uint8_t                          device_num)
{
    FSP_PARAMETER_NOT_USED(op_code);
    FSP_PARAMETER_NOT_USED(p_addr);
    FSP_PARAMETER_NOT_USED(p_peer_irk);
    FSP_PARAMETER_NOT_USED(device_num);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_EnableRpa (uint8_t enable)
{
    FSP_PARAMETER_NOT_USED(enable);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_SetRpaTo (uint16_t rpa_timeout)
{
    FSP_PARAMETER_NOT_USED(rpa_timeout);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_ReadRpa (st_ble_dev_addr_t * p_addr)
{
    FSP_PARAMETER_NOT_USED(p_addr);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_ReadRssi (uint16_t conn_hdl)
{
    return R_BLE_GTL_GAP_ReadRssi(conn_hdl);
}

ble_status_t R_BLE_GAP_ReadChMap (uint16_t conn_hdl)
{
    return R_BLE_GTL_GAP_ReadChMap(conn_hdl);
}

ble_status_t R_BLE_GAP_SetRandAddr (uint8_t * p_random_addr)
{
    FSP_PARAMETER_NOT_USED(p_random_addr);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_SetAdvParam (st_ble_gap_adv_param_t * p_adv_param)
{
    return R_BLE_GTL_GAP_SetAdvParam(p_adv_param);
}

ble_status_t R_BLE_GAP_SetAdvSresData (st_ble_gap_adv_data_t * p_adv_srsp_data)
{
    return R_BLE_GTL_GAP_SetAdvSresData(p_adv_srsp_data);
}

ble_status_t R_BLE_GAP_StartAdv (uint8_t adv_hdl, uint16_t duration, uint8_t max_extd_adv_evts)
{
    FSP_PARAMETER_NOT_USED(max_extd_adv_evts);

    return R_BLE_GTL_GAP_StartAdv(adv_hdl, duration);
}

ble_status_t R_BLE_GAP_StopAdv (uint8_t adv_hdl)
{
    return R_BLE_GTL_GAP_StopAdv(adv_hdl);
}

ble_status_t R_BLE_GAP_SetPerdAdvParam (st_ble_gap_perd_adv_param_t * p_perd_adv_param)
{
    FSP_PARAMETER_NOT_USED(p_perd_adv_param);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_StartPerdAdv (uint8_t adv_hdl)
{
    FSP_PARAMETER_NOT_USED(adv_hdl);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_StopPerdAdv (uint8_t adv_hdl)
{
    FSP_PARAMETER_NOT_USED(adv_hdl);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_GetRemainAdvBufSize (uint16_t * p_remain_adv_data_size, uint16_t * p_remain_perd_adv_data_size)
{
    return R_BLE_GTL_GAP_GetRemainAdvBufSize(p_remain_adv_data_size, p_remain_perd_adv_data_size);
}

ble_status_t R_BLE_GAP_RemoveAdvSet (uint8_t op_code, uint8_t adv_hdl)
{
    FSP_PARAMETER_NOT_USED(op_code);
    FSP_PARAMETER_NOT_USED(adv_hdl);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_CreateConn (st_ble_gap_create_conn_param_t * p_param)
{
    ble_status_t status;
    status = R_BLE_GTL_GAP_CreateConn(p_param);

    return status;
}

ble_status_t R_BLE_GAP_CancelCreateConn (void)
{
    ble_status_t status;
    status = R_BLE_GTL_GAP_CancelConn();

    return status;
}

ble_status_t R_BLE_GAP_SetChMap (uint8_t * p_channel_map)
{
    FSP_PARAMETER_NOT_USED(p_channel_map);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_StartScan (st_ble_gap_scan_param_t * p_scan_param, st_ble_gap_scan_on_t * p_scan_enable)
{
    ble_status_t status;
    status = R_BLE_GTL_GAP_StartScan(p_scan_param, p_scan_enable);

    return status;
}

ble_status_t R_BLE_GAP_StopScan (void)
{
    ble_status_t status = R_BLE_GTL_GAP_StopScan();

    return status;
}

ble_status_t R_BLE_GAP_CreateSync (st_ble_dev_addr_t * p_addr, uint8_t adv_sid, uint16_t skip, uint16_t sync_to)
{
    FSP_PARAMETER_NOT_USED(p_addr);
    FSP_PARAMETER_NOT_USED(adv_sid);
    FSP_PARAMETER_NOT_USED(skip);
    FSP_PARAMETER_NOT_USED(sync_to);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_CancelCreateSync (void)
{

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_TerminateSync (uint16_t sync_hdl)
{
    FSP_PARAMETER_NOT_USED(sync_hdl);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_ConfPerdAdvList (uint8_t             op_code,
                                        st_ble_dev_addr_t * p_addr,
                                        uint8_t           * p_adv_sid_set,
                                        uint8_t             device_num)
{
    FSP_PARAMETER_NOT_USED(op_code);
    FSP_PARAMETER_NOT_USED(p_addr);
    FSP_PARAMETER_NOT_USED(p_adv_sid_set);
    FSP_PARAMETER_NOT_USED(device_num);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_AuthorizeDev (uint16_t conn_hdl, uint8_t author_flag)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(author_flag);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_GetRemDevInfo (uint16_t conn_hdl)
{
    return R_BLE_GTL_GAP_GetRemDevInfo(conn_hdl);
}

ble_status_t R_BLE_GAP_SetPairingParams (st_ble_gap_pairing_param_t * p_pair_param)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;

    status = R_BLE_GTL_GAP_SetPairingParams(p_pair_param);

    return status;
}

ble_status_t R_BLE_GAP_SetLocIdInfo (st_ble_dev_addr_t * p_lc_id_addr, uint8_t * p_lc_irk)
{
    FSP_PARAMETER_NOT_USED(p_lc_id_addr);
    FSP_PARAMETER_NOT_USED(p_lc_irk);

    /* Functionality not yet implemented */

    /* Function registers local info to stack, not applicable to DA1453x attach */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_SetLocCsrk (uint8_t * p_local_csrk)
{
    FSP_PARAMETER_NOT_USED(p_local_csrk);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_StartPairing (uint16_t conn_hdl)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;
    if (r_ble_gtl_sec_get_dev_role(conn_hdl) == R_BLE_GTL_CENTRAL_ROLE) // CENTRAL_ROLE
    {
        status = r_ble_gtl_send_bond_cmd(conn_hdl);
    }
    else
    {
        status = r_ble_gtl_security_cmd(conn_hdl);
    }

    return status;
}

ble_status_t R_BLE_GAP_ReplyPairing (uint16_t conn_hdl, uint8_t response)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;

    status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_PAIRING_RSP, response, NULL_TK_VAL);

    return status;
}

ble_status_t R_BLE_GAP_StartEnc (uint16_t conn_hdl)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    ble_status_t status = BLE_ERR_UNSPECIFIED;

    if (r_ble_gtl_sec_get_dev_role(conn_hdl) == R_BLE_GTL_CENTRAL_ROLE)
    {
        status = r_ble_gtl_send_enc_cmd(conn_hdl);
    }
    else
    {
        status = BLE_ERR_UNSUPPORTED;
    }

    return status;
}

ble_status_t R_BLE_GAP_ReplyPasskeyEntry (uint16_t conn_hdl, uint32_t passkey, uint8_t response)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;

    status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_TK_EXCH, response, passkey);

    return status;
}

ble_status_t R_BLE_GAP_ReplyNumComp (uint16_t conn_hdl, uint8_t response)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;

    status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_TK_EXCH, response, NULL_TK_VAL);

    return status;
}

ble_status_t R_BLE_GAP_NotifyKeyPress (uint16_t conn_hdl, uint8_t key_press)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(key_press);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_GetDevSecInfo (uint16_t conn_hdl, st_ble_gap_auth_info_t * p_sec_info)
{
    FSP_PARAMETER_NOT_USED(p_sec_info);
    sec_ble_gap_bond_info_t * bond_info_loc_tmp = {0};
    ble_status_t              status            = BLE_ERR_NOT_FOUND;

    uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, conn_hdl, 0);
    if (INVALID_IDX == bond_index)
    {
        // No bonding available
        status = BLE_ERR_NOT_FOUND;
    }
    else
    {
        bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);
        if (bond_info_loc_tmp->p_auth_info.bonding == true)
        {
            // Bonding available
            status = BLE_SUCCESS;

            p_sec_info->security  = bond_info_loc_tmp->p_auth_info.security;
            p_sec_info->pair_mode = bond_info_loc_tmp->p_auth_info.pair_mode;
            p_sec_info->bonding   = bond_info_loc_tmp->p_auth_info.bonding;
            p_sec_info->ekey_size = bond_info_loc_tmp->p_auth_info.ekey_size;
        }
    }

    return status;
}

ble_status_t R_BLE_GAP_ReplyExKeyInfoReq (uint16_t conn_hdl)
{
    ble_status_t status           = BLE_ERR_UNSUPPORTED;
    uint8_t      loc_key_dist_var = (uint8_t) (conn_hdl >> 8);

    /* Clear the top byte */
    conn_hdl = conn_hdl & R_BLE_GTL_SRC_ID_MASK;

    /* The command does not have the key as separate param,
     * for this reason the key is hidden in the first byte of conn_hdl */
    if (loc_key_dist_var == R_BLE_GTL_GAPC_LTK_EXCH)
    {
        status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_LTK_EXCH, true, NULL_TK_VAL);
    }

    if (loc_key_dist_var == R_BLE_GTL_GAPC_IRK_EXCH)
    {
        status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_IRK_EXCH, true, NULL_TK_VAL);
    }

    if (loc_key_dist_var == R_BLE_GTL_GAPC_CSRK_EXCH)
    {
        status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_CSRK_EXCH, true, NULL_TK_VAL);
    }

    return status;
}

ble_status_t R_BLE_GAP_SetRemOobData (st_ble_dev_addr_t * p_addr, uint8_t oob_data_flag, st_ble_gap_oob_data_t * p_oob)
{
    FSP_PARAMETER_NOT_USED(p_addr);
    FSP_PARAMETER_NOT_USED(oob_data_flag);
    FSP_PARAMETER_NOT_USED(p_oob);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_CreateScOobData (void)
{

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_SetBondInfo (st_ble_gap_bond_info_t * p_bond_info, uint8_t device_num, uint8_t * p_set_num)
{
    FSP_PARAMETER_NOT_USED(p_bond_info);
    FSP_PARAMETER_NOT_USED(device_num);
    FSP_PARAMETER_NOT_USED(p_set_num);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

void R_BLE_GAP_DeleteBondInfo (int32_t               local,
                               int32_t               remote,
                               st_ble_dev_addr_t   * p_addr,
                               ble_gap_del_bond_cb_t gap_del_bond_cb)
{
    FSP_PARAMETER_NOT_USED(local);
    FSP_PARAMETER_NOT_USED(remote);
    FSP_PARAMETER_NOT_USED(p_addr);
    FSP_PARAMETER_NOT_USED(gap_del_bond_cb);

    /* Functionality not yet implemented */
}

ble_status_t R_BLE_GAP_ReplyLtkReq (uint16_t conn_hdl, uint16_t ediv, uint8_t * p_peer_rand, uint8_t response)
{
    ble_status_t status = BLE_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(response);

    if (r_ble_gtl_sec_get_sec_conn_var() != BLE_GAP_SC_STRICT)
    {
        /* Handle LEGACY PAIRING */
        bool comp_resp = r_ble_gtl_sec_encryption_req_resp(conn_hdl, ediv, p_peer_rand);

        if (comp_resp)
        {
            /* Values found in db */
            status = r_ble_gtl_send_gapc_encrypt_cfm(conn_hdl, BLE_GAP_LTK_REQ_ACCEPT);
        }
        else
        {
            /* Values NOT found in db */
            status = r_ble_gtl_send_gapc_encrypt_cfm(conn_hdl, BLE_GAP_LTK_REQ_DENY);
        }

        /* Notify the application */
        if (status == BLE_SUCCESS)
        {
            status = r_ble_gtl_gapc_ltk_rsp_comp(conn_hdl, comp_resp);
        }
    }
    else
    {
        /* Handle SECURE CONNECTIONS */
        status = r_ble_gtl_send_gapc_encrypt_cfm(conn_hdl, BLE_GAP_LTK_REQ_ACCEPT);
        if (status == BLE_SUCCESS)
        {
            status = r_ble_gtl_gapc_ltk_rsp_comp(conn_hdl, true);
        }
    }

    return status;
}

ble_status_t R_BLE_GATT_GetMtu (uint16_t conn_hdl, uint16_t * p_mtu)
{
    return R_BLE_GTL_GATT_GetMtu(conn_hdl, p_mtu);
}

ble_status_t R_BLE_GATTS_Init (uint8_t cb_num)
{
    FSP_PARAMETER_NOT_USED(cb_num);

    /* No initialization required */
    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_SetDbInst (st_ble_gatts_db_cfg_t * p_db_inst)
{
    return R_BLE_GTL_GATTS_SetDbInst(p_db_inst);
}

ble_status_t R_BLE_GATTS_RegisterCb (ble_gatts_app_cb_t cb, uint8_t priority)
{
    return R_BLE_GTL_GATTS_RegisterCb(cb, priority);
}

ble_status_t R_BLE_GATTS_DeregisterCb (ble_gatts_app_cb_t cb)
{
    return R_BLE_GTL_GATTS_DeregisterCb(cb);
}

ble_status_t R_BLE_GATTS_Notification (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ntf_data)
{
    return R_BLE_GTL_GATTS_Notification(conn_hdl, p_ntf_data);
}

ble_status_t R_BLE_GATTS_Indication (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ind_data)
{
    return R_BLE_GTL_GATTS_Indication(conn_hdl, p_ind_data);
}

ble_status_t R_BLE_GATTS_GetAttr (uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
    return R_BLE_GTL_GATTS_GetAttr(conn_hdl, attr_hdl, p_value);
}

ble_status_t R_BLE_GATTS_SetAttr (uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
    return R_BLE_GTL_GATTS_SetAttr(conn_hdl, attr_hdl, p_value);
}

ble_status_t R_BLE_GATTS_SendErrRsp (uint16_t error_code)
{
    FSP_PARAMETER_NOT_USED(error_code);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GATTS_RspExMtu (uint16_t conn_hdl, uint16_t mtu)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(mtu);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GATTS_SetPrepareQueue (st_ble_gatt_pre_queue_t * p_pre_queues, uint8_t queue_num)
{
    FSP_PARAMETER_NOT_USED(p_pre_queues);
    FSP_PARAMETER_NOT_USED(queue_num);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GATTC_Init (uint8_t cb_num)
{
    FSP_PARAMETER_NOT_USED(cb_num);

    /* No initialization required */
    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_RegisterCb (ble_gattc_app_cb_t cb, uint8_t priority)
{
    return R_BLE_GTL_GATTC_RegisterCb(cb, priority);
}

ble_status_t R_BLE_GATTC_DeregisterCb (ble_gattc_app_cb_t cb)
{
    return R_BLE_GTL_GATTC_DeregisterCb(cb);
}

ble_status_t R_BLE_GATTC_ReqExMtu (uint16_t conn_hdl, uint16_t mtu)
{
    return R_BLE_GTL_GATTC_ReqExMtu(conn_hdl, mtu);
}

ble_status_t R_BLE_GATTC_DiscAllPrimServ (uint16_t conn_hdl)
{
    return R_BLE_GTL_GATTC_DiscAllPrimServ(conn_hdl);
}

ble_status_t R_BLE_GATTC_DiscPrimServ (uint16_t conn_hdl, uint8_t * p_uuid, uint8_t uuid_type)
{
    return R_BLE_GTL_GATTC_DiscPrimServ(conn_hdl, p_uuid, uuid_type);
}

ble_status_t R_BLE_GATTC_DiscAllSecondServ (uint16_t conn_hdl)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GATTC_DiscIncServ (uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
    return R_BLE_GTL_GATTC_DiscIncServ(conn_hdl, p_range);
}

ble_status_t R_BLE_GATTC_DiscAllChar (uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
    return R_BLE_GTL_GATTC_DiscAllChar(conn_hdl, p_range);
}

ble_status_t R_BLE_GATTC_DiscCharByUuid (uint16_t                  conn_hdl,
                                         uint8_t                 * p_uuid,
                                         uint8_t                   uuid_type,
                                         st_ble_gatt_hdl_range_t * p_range)
{
    return R_BLE_GTL_GATTC_DiscCharByUuid(conn_hdl, p_uuid, uuid_type, p_range);
}

ble_status_t R_BLE_GATTC_DiscAllCharDesc (uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
    return R_BLE_GTL_GATTC_DiscAllCharDesc(conn_hdl, p_range);
}

ble_status_t R_BLE_GATTC_ReadChar (uint16_t conn_hdl, uint16_t value_hdl)
{
    return R_BLE_GTL_GATTC_ReadChar(conn_hdl, value_hdl);
}

ble_status_t R_BLE_GATTC_ReadCharUsingUuid (uint16_t                  conn_hdl,
                                            uint8_t                 * p_uuid,
                                            uint8_t                   uuid_type,
                                            st_ble_gatt_hdl_range_t * p_range)
{
    return R_BLE_GTL_GATTC_ReadCharUsingUuid(conn_hdl, p_uuid, uuid_type, p_range);
}

ble_status_t R_BLE_GATTC_ReadLongChar (uint16_t conn_hdl, uint16_t value_hdl, uint16_t offset)
{
    return R_BLE_GTL_GATTC_ReadLongChar(conn_hdl, value_hdl, offset, 0);
}

ble_status_t R_BLE_GATTC_ReadMultiChar (uint16_t conn_hdl, st_ble_gattc_rd_multi_req_param_t * p_list)
{
    return R_BLE_GTL_GATTC_ReadMultiChar(conn_hdl, p_list);
}

ble_status_t R_BLE_GATTC_WriteCharWithoutRsp (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
    return R_BLE_GTL_GATTC_WriteCharWithoutRsp(conn_hdl, p_write_data);
}

ble_status_t R_BLE_GATTC_SignedWriteChar (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(p_write_data);

    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GATTC_WriteChar (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
    return R_BLE_GTL_GATTC_WriteChar(conn_hdl, p_write_data);
}

ble_status_t R_BLE_GATTC_WriteLongChar (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data, uint16_t offset)
{
    return R_BLE_GTL_GATTC_WriteLongChar(conn_hdl, p_write_data, offset);
}

ble_status_t R_BLE_GATTC_ReliableWrites (uint16_t                                   conn_hdl,
                                         st_ble_gattc_reliable_writes_char_pair_t * p_char_pair,
                                         uint8_t                                    pair_num,
                                         uint8_t                                    auto_flag)
{
    FSP_PARAMETER_NOT_USED(auto_flag);

    return R_BLE_GTL_GATTC_ReliableWrites(conn_hdl, p_char_pair, pair_num, 0);
}

ble_status_t R_BLE_GATTC_ExecWrite (uint16_t conn_hdl, uint8_t exe_flag)
{
    return R_BLE_GTL_GATTC_ExecWrite(conn_hdl, exe_flag);
}

ble_status_t R_BLE_L2CAP_RegisterCfPsm (ble_l2cap_cf_app_cb_t cb, uint16_t psm, uint16_t lwm)
{
    FSP_PARAMETER_NOT_USED(cb);
    FSP_PARAMETER_NOT_USED(psm);
    FSP_PARAMETER_NOT_USED(lwm);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_L2CAP_DeregisterCfPsm (uint16_t psm)
{
    FSP_PARAMETER_NOT_USED(psm);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_L2CAP_ReqCfConn (uint16_t conn_hdl, st_ble_l2cap_conn_req_param_t * p_conn_req_param)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(p_conn_req_param);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_L2CAP_RspCfConn (st_ble_l2cap_conn_rsp_param_t * p_conn_rsp_param)
{
    FSP_PARAMETER_NOT_USED(p_conn_rsp_param);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_L2CAP_DisconnectCf (uint16_t lcid)
{
    FSP_PARAMETER_NOT_USED(lcid);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_L2CAP_SendCfCredit (uint16_t lcid, uint16_t credit)
{
    FSP_PARAMETER_NOT_USED(lcid);
    FSP_PARAMETER_NOT_USED(credit);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_L2CAP_SendCfData (uint16_t conn_hdl, uint16_t lcid, uint16_t data_len, uint8_t * p_sdu)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(lcid);
    FSP_PARAMETER_NOT_USED(data_len);
    FSP_PARAMETER_NOT_USED(p_sdu);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_Init (ble_vs_app_cb_t vs_cb)
{
    return R_BLE_GTL_VS_Init(vs_cb);
}

ble_status_t R_BLE_VS_StartTxTest (st_ble_vs_tx_test_param_t * p_tx_test_param)
{
    FSP_PARAMETER_NOT_USED(p_tx_test_param);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_StartRxTest (st_ble_vs_rx_test_param_t * p_rx_test_param)
{
    FSP_PARAMETER_NOT_USED(p_rx_test_param);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_EndTest (void)
{

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_SetTxPower (uint16_t conn_hdl, uint8_t tx_power)
{
    return R_BLE_GTL_VS_SetTxPower(conn_hdl, tx_power);
}

ble_status_t R_BLE_VS_GetTxPower (uint16_t conn_hdl)
{
    return R_BLE_GTL_VS_GetTxPower(conn_hdl);
}

ble_status_t R_BLE_VS_SetCodingScheme (uint8_t coding_scheme)
{
    FSP_PARAMETER_NOT_USED(coding_scheme);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_SetRfControl (st_ble_vs_set_rf_ctrl_param_t * p_rf_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_rf_ctrl);

    /* Functionality not yet implemented */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_SetBdAddr (uint8_t area, st_ble_dev_addr_t * p_addr)
{
    ble_status_t status = BLE_ERR_UNSUPPORTED;

    /* GTL middleware only supports BD address storage in registers */
    if (BLE_VS_ADDR_AREA_REG == area)
    {
        status = R_BLE_GTL_VS_SetBdAddr(p_addr);
    }
    /* Save BD address in data flash */
    else if (BLE_VS_ADDR_AREA_DATA_FLASH == area)
    {
#ifdef ENABLE_STORAGE
        status = R_BLE_GTL_VS_SetBdAddr_dflash(p_addr);
#endif
    }
    else
    {
        /* Invalid area */
        status = BLE_ERR_INVALID_ARG;
    }

    return status;
}

ble_status_t R_BLE_VS_GetBdAddr (uint8_t area, uint8_t addr_type)
{
    ble_status_t      status = BLE_ERR_UNSUPPORTED;
    st_ble_dev_addr_t ret_addr;

    /* GTL middleware only supports BD address storage in registers */
    if (BLE_VS_ADDR_AREA_REG == area)
    {
        status = R_BLE_GTL_VS_GetBdAddr(addr_type);
    }
    /* Get BD address from data flash */
    else if (BLE_VS_ADDR_AREA_DATA_FLASH == area)
    {
#ifdef ENABLE_STORAGE
        status = R_BLE_GTL_VS_GetBdAddr_dflash(addr_type, &ret_addr);
#endif
    }
    else
    {
        /* Invalid area */
        status = BLE_ERR_INVALID_ARG;
    }

    FSP_PARAMETER_NOT_USED(ret_addr);

    return status;
}

ble_status_t R_BLE_VS_GetRand (uint8_t rand_size)
{
    return R_BLE_GTL_VS_GetRand(rand_size);
}

ble_status_t R_BLE_VS_StartTxFlowEvtNtf (void)
{

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_StopTxFlowEvtNtf (void)
{

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_GetTxBufferNum (uint32_t * p_buffer_num)
{
    FSP_PARAMETER_NOT_USED(p_buffer_num);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_SetTxLimit (uint32_t tx_queue_lwm, uint32_t tx_queue_hwm)
{
    FSP_PARAMETER_NOT_USED(tx_queue_lwm);
    FSP_PARAMETER_NOT_USED(tx_queue_hwm);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_SetScanChMap (uint16_t ch_map)
{
    FSP_PARAMETER_NOT_USED(ch_map);

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_GetScanChMap (void)
{

    /* Functionality not supported by DA1453x */
    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_VS_SetSleepMode (uint8_t sleep_mode, uint8_t ram_retention, uint8_t pin_selection)
{
    return R_BLE_GTL_VS_SetSleepMode(sleep_mode, ram_retention, pin_selection);
}

ble_status_t R_BLE_VS_SetPublicBdAddress (st_ble_dev_addr_t * p_addr)
{
    FSP_PARAMETER_NOT_USED(p_addr);

    /* Functionality not supported by DA1453x, superseded by R_BLE_VS_SetBdAddr()  */
    return BLE_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 *  Open transport layer interface.
 *
 * @param[in]  p_context    Pointer to transport layer context
 *
 **********************************************************************************************************************/
static int r_ble_gtl_api_transport_open (void * p_context)
{
    fsp_err_t       err;
    ble_abs_cfg_t * bkup_context = (ble_abs_cfg_t *) p_context;

#if defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_UART)
    err = bkup_context->p_uart_instance->p_api->open(bkup_context->p_uart_instance->p_ctrl,
                                                     bkup_context->p_uart_instance->p_cfg);
#elif defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_SPI)

    /* SPI supported not yet implemented */
#endif

    return (int) err;
}

/*******************************************************************************************************************//**
 *  Write data to transport layer interface.
 *
 * @param[in]  p_context    Pointer to transport layer context
 * @param[in]  p_data       Pointer to data to be written
 * @param[in]  len          Number of bytes to write
 *
 **********************************************************************************************************************/
static int r_ble_gtl_api_transport_write (void * p_context, uint8_t * p_data, uint32_t len)
{
    fsp_err_t       err;
    ble_abs_cfg_t * bkup_context = (ble_abs_cfg_t *) p_context;

#if defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_UART)
    err = bkup_context->p_uart_instance->p_api->write(bkup_context->p_uart_instance->p_ctrl, p_data, len);
#elif defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_SPI)

    /* SPI supported not yet implemented */
#endif

    return (int) err;
}

/*******************************************************************************************************************//**
 *  Close transport layer interface.
 *
 * @param[in]  p_context    Pointer to transport layer context
 *
 **********************************************************************************************************************/
static int r_ble_gtl_api_transport_close (void * p_context)
{
    fsp_err_t       err          = FSP_SUCCESS;
    ble_abs_cfg_t * bkup_context = (ble_abs_cfg_t *) p_context;

#if defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_UART)
    err = bkup_context->p_uart_instance->p_api->close(bkup_context->p_uart_instance->p_ctrl);
#elif defined(RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_SPI)

    /* SPI supported not yet implemented */
#endif

    return (int) err;
}
