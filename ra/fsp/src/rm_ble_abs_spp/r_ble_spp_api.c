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

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <rm_ble_abs.h>
#include <rm_ble_abs_api.h>
#include <rm_ble_abs_spp_cfg.h>
#include "r_ble_api.h"
#include "r_ble_spp.h"
#include "qe_ble_profile.h"
#if (BSP_CFG_RTOS == 2)
 #include "FreeRTOS.h"
 #include "task.h"
 #include "event_groups.h"
#endif

/******************************************************************************
 * Macros
 ******************************************************************************/
#define BLE_MODULE_RESET_TIMEOUT                 (50)
#define BLE_MODULE_STABILIZE_TIMEOUT             (500)
#define BLE_MODULE_COMMAND_RECV_TIMEOUT          (10)
#ifndef BLE_MODULE_START_FW_UPLOAD_TIMEOUT
 #define BLE_MODULE_START_FW_UPLOAD_TIMEOUT      (4000)
#endif
#ifndef BLE_MODULE_END_FW_UPLOAD_TIMEOUT
 #define BLE_MODULE_END_FW_UPLOAD_TIMEOUT        (4000)
#endif
#define BLE_MODULE_MTU_MAX                       (128)
#define BLE_MODULE_SEND_FIRMWARE_DATA_SIZE       (128)
#define BLE_MODULE_READY_RETRY_COUNT             (15)

#define BLE_MODULE_SPP_SPI_READ_HEADER_SIZE      (4U)
#define BLE_MODULE_SPP_SPI_READ_CHECKSUM_SIZE    (2U)
#define BLE_MODULE_SPP_SPI_READ_EVENT_SIZE       (2U)
#define BLE_MODULE_SPP_MAX_PACKET_SIZE           (255)

#define BLE_PARAMETER_NOT_USED(p)    (void) ((p))

#define ENDIAN_LSB16(n)              (uint8_t) (n & 0xFF)
#define ENDIAN_MSB16(n)              (uint8_t) (n >> 8)

/*
 * State the current SPI read operation:
 * - IDLE:     No SPI read operation in progress.
 * - HEADER:   Reading the packet header in order to get the length of the payload.
 * - BODY:     Packet header has been read and the payload is in progress.
 */
#define BLE_MODULE_SPI_READ_STATE_IDLE      (0)
#define BLE_MODULE_SPI_READ_STATE_HEADER    (1)
#define BLE_MODULE_SPI_READ_STATE_BODY      (2)

#define R_BLE_SPP_EVENT_CONN_IND            (0x0783)
#define R_BLE_SPP_EVENT_DISCONN_IND         (0x0784)
#define R_BLE_SPP_EVENT_SET_DISABLE_ADV     (0x0721)
#define R_BLE_SPP_EVENT_SET_ENABLE_ADV      (0x070A)
#define R_BLE_SPP_EVENT_SET_ADV_SRES        (0x0722)
#define R_BLE_SPP_EVENT_SET_ADV_PARAM       (0x0720)
#define R_BLE_SPP_EVENT_GET_ATTR            (0x072A)
#define R_BLE_SPP_EVENT_SET_ATTR            (0x0729)
#define R_BLE_SPP_EVENT_DATA_RECEIVED       (0x07A0)
#define R_BLE_SPP_EVENT_SET_MAC_ID          (0x0725)
#define R_BLE_SPP_EVENT_SEND_NOTIFY         (0x071C)
#define R_BLE_SPP_EVENT_SEND_INDICATION     (0x0726)
#define R_BLE_SPP_EVENT_SET_TX_POWER        (0x0705)

#define BLE_SPP_COMMAND(command, reply_event, timeout)                           \
    {                                                                            \
        uint16_t cmd_status = (uint16_t) (command);                              \
                                                                                 \
        if (!cmd_status)                                                         \
        {                                                                        \
            cmd_status = r_ble_spp_api_check_return_valid(reply_event, timeout); \
        }                                                                        \
                                                                                 \
        if (cmd_status)                                                          \
        {                                                                        \
            return BLE_ERR_INVALID_PTR;                                          \
        }                                                                        \
    }

/******************************************************************************
 * Enums
 ******************************************************************************/
typedef enum
{
    BLE_SPP_COMMS_UART,
    BLE_SPP_COMMS_SPI
} ble_abs_spp_comms_transport_mode_t;

/******************************************************************************
 * Externals
 ******************************************************************************/
extern ble_abs_instance_ctrl_t * gp_instance_ctrl;

/******************************************************************************
 * Static Private Function Definitions
 ******************************************************************************/
static void r_ble_spp_api_set_ryz012_communication_mode(ble_abs_spp_comms_transport_mode_t mode);
static int  r_ble_spp_api_fsp_callback_open(void * p_context);
static int  r_ble_spp_api_fsp_callback_write(void * p_context, uint8_t * p_data, uint32_t len);

#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
static int r_ble_spp_api_fsp_callback_read(void * const   p_context,
                                           void const   * p_src,
                                           void         * p_dest,
                                           uint32_t const len,
                                           uint8_t const  bit_width);

#endif
static int          r_ble_spp_api_fsp_callback_close(void * p_context);
static void         r_ble_spp_api_mw_callback(r_ble_spp_payload_t * p_payload);
static ble_status_t r_ble_spp_api_check_return_valid(uint32_t expected_spp_reply, uint32_t timeout);
static void         r_ble_spp_api_delay_ms(uint32_t ms);

/******************************************************************************
 * Static Private Variables
 ******************************************************************************/

static r_ble_spp_payload_t g_current_spp_payload;
static r_ble_spp_payload_t g_current_spp_async_payload;
static volatile uint32_t   g_spp_cmd_ready     = 0;
static volatile uint32_t   g_spp_cmd_unknown   = 0;
static volatile uint32_t   g_spp_cmd_failed    = 0;
static volatile uint32_t   g_spp_cmd_async     = 0;
static volatile uint32_t   g_transfer_complete = 0;
static r_ble_spp_cfg_t     r_ble_spp_api_transport_api;
static bool                g_dynamic_profile_set;

ble_gap_app_cb_t g_gap_cb   = NULL;
ble_event_cb_t   g_cb_event = NULL;
ble_gatt_client_application_callback_t     g_spp_gatt_client_cb = NULL;
ble_gatt_server_application_callback_t     g_spp_gatt_server_cb = NULL;
ble_vendor_specific_application_callback_t g_spp_vendor_cb      = NULL;

uint32_t ble_version_major   = 0;
uint32_t ble_version_minor   = 0;
uint32_t ble_version_special = 0;

/* LUT used in R_BLE_GAP_SetAdvParam */
static const uint8_t g_ch_map_lut[8] = {0, 0, 1, 0, 2, 0, 1, 3};

#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)

/* Global state for managing SPI read operations. */
static uint8_t  g_spi_rx_buffer[BLE_MODULE_SPP_MAX_PACKET_SIZE];
static uint8_t  g_spi_tx_buffer[BLE_MODULE_SPP_MAX_PACKET_SIZE];
static uint32_t g_spi_read_state;

#endif

/******************************************************************************
 * Public Function Prototypes
 ******************************************************************************/
#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_UART)
void rm_ble_spp_callback(uart_callback_args_t * p_args);

#elif defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
void rm_ble_spp_host_spi_callback(spi_callback_args_t * p_args);
void rm_ble_spp_data_ready_callback(external_irq_callback_args_t * p_args);

#endif

/******************************************************************************
 * Public Functions
 ******************************************************************************/

ble_status_t R_BLE_Open (void)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(gp_instance_ctrl);
    FSP_ASSERT(gp_instance_ctrl->p_cfg);
 #if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_UART)
    FSP_ASSERT(gp_instance_ctrl->p_cfg->p_uart_instance);
 #elif defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
    FSP_ASSERT(gp_instance_ctrl->p_cfg->p_spi_instance);
    FSP_ASSERT(gp_instance_ctrl->p_cfg->p_irq_instance);
 #endif
#endif

    g_spp_cmd_ready     = 0;
    g_spp_cmd_unknown   = 0;
    g_spp_cmd_failed    = 0;
    g_spp_cmd_async     = 0;
    g_transfer_complete = 0;
    g_spp_vendor_cb     = gp_instance_ctrl->p_cfg->vendor_specific_callback;

    r_ble_spp_api_transport_api.p_context = (void *) gp_instance_ctrl->p_cfg;

#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_UART)
    r_ble_spp_api_transport_api.config_flag = BLE_SPP_COMMS_UART;
#elif defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
    g_spi_read_state                        = BLE_MODULE_SPI_READ_STATE_IDLE;
    r_ble_spp_api_transport_api.Read        = r_ble_spp_api_fsp_callback_read;
    r_ble_spp_api_transport_api.config_flag = BLE_SPP_COMMS_SPI;
#endif
    r_ble_spp_api_transport_api.open        = r_ble_spp_api_fsp_callback_open;
    r_ble_spp_api_transport_api.write       = r_ble_spp_api_fsp_callback_write;
    r_ble_spp_api_transport_api.close       = r_ble_spp_api_fsp_callback_close;
    r_ble_spp_api_transport_api.mw_callback = &r_ble_spp_api_mw_callback;

#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_UART)
    r_ble_spp_api_set_ryz012_communication_mode(BLE_SPP_COMMS_UART);
#elif defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
    r_ble_spp_api_set_ryz012_communication_mode(BLE_SPP_COMMS_SPI);
#endif

    if (R_BLE_SPP_GAP_Open(&r_ble_spp_api_transport_api) == R_BLE_SPP_SUCCESS)
    {
        FSP_ERROR_RETURN(BLE_SUCCESS,
                         r_ble_spp_api_check_return_valid(R_BLE_SPP_EVENT_BLE_READY, BLE_MODULE_RESET_TIMEOUT));
    }

    return BLE_SUCCESS;
}

ble_status_t R_BLE_Close (void)
{
    /* Close the communication port */
    R_BLE_SPP_GAP_Close(&r_ble_spp_api_transport_api);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_Init (ble_gap_app_cb_t gap_cb)
{
    if (gap_cb == NULL)
    {
        return BLE_ERR_INVALID_PTR;
    }

    g_gap_cb = gap_cb;
    g_gap_cb(BLE_GAP_EVENT_STACK_ON, BLE_SUCCESS, NULL);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_SetDbInst (st_ble_gatts_db_cfg_t * p_db_inst)
{
    BLE_PARAMETER_NOT_USED(p_db_inst);

    /* Only set this once (QE currently calls this twice, once in RM_BLE_ABS_Open and a second time by itself) */
    if (!g_dynamic_profile_set)
    {
        /* Get number of loop attributes */
        uint16_t attributes = qe_ble_profile[0].encapsulated_attributes;

        r_ble_spp_profile_params_t params;

        /* Add profile attributes to BLE module internal table. */
        for (uint32_t i = 0; i < attributes + 1U; i++)
        {
            params.attNum         = qe_ble_profile[i].encapsulated_attributes;
            params.attrLen        = qe_ble_profile[i].value_length;
            params.pAttrValue     = qe_ble_profile[i].value;
            params.payload_length = (uint16_t) (8 + qe_ble_profile[i].uuid_length + qe_ble_profile[i].value_length);
            params.perm           = qe_ble_profile[i].permissions;
            params.read_flag      = qe_ble_profile[i].notify_read;
            params.uuid           = qe_ble_profile[i].uuid;
            params.uuidLen        = qe_ble_profile[i].uuid_length;
            params.write_flag     = qe_ble_profile[i].notify_write;

            BLE_SPP_COMMAND(R_BLE_SPP_GAP_Config_Profile(&params),
                            R_BLE_SPP_EVENT_DYNAMIC_ATTRIBUTE_CREATE,
                            BLE_MODULE_RESET_TIMEOUT);
        }

        /* Finalize the profile table on the device */
        BLE_SPP_COMMAND(R_BLE_SPP_GAP_Profile_Complete(),
                        R_BLE_SPP_EVENT_DYNAMIC_ATTRIBUTE_COMPLETE,
                        BLE_MODULE_RESET_TIMEOUT);

        g_gap_cb(BLE_GAP_EVENT_DISCONN_IND, BLE_SUCCESS, NULL);

        g_dynamic_profile_set = true;
    }

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_StopAdv (uint8_t adv_hdl)
{
    BLE_PARAMETER_NOT_USED(adv_hdl);

    BLE_SPP_COMMAND(R_BLE_SPP_GAP_StopAdv(), R_BLE_SPP_EVENT_SET_DISABLE_ADV, BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_SetAdvSresData (st_ble_gap_adv_data_t * p_adv_srsp_data)
{
    r_ble_spp_adv_data_t advertising_data;
    advertising_data.data_type   = (r_ble_spp_adv_type_t) p_adv_srsp_data->data_type;
    advertising_data.data_length = p_adv_srsp_data->data_length;
    advertising_data.p_data      = p_adv_srsp_data->p_data;

    /* Set advertising data */
    BLE_SPP_COMMAND(R_BLE_SPP_GAP_SetAdvSresData(&advertising_data),
                    R_BLE_SPP_EVENT_SET_ADV_SRES,
                    BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_StartPerdAdv (uint8_t adv_hdl)
{
    BLE_PARAMETER_NOT_USED(adv_hdl);

    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_SetPerdAdvParam (st_ble_gap_perd_adv_param_t * p_perd_adv_param)
{
    BLE_PARAMETER_NOT_USED(p_perd_adv_param);

    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GAP_StartAdv (uint8_t adv_hdl, uint16_t duration, uint8_t max_extd_adv_evts)
{
    BLE_PARAMETER_NOT_USED(adv_hdl);
    BLE_PARAMETER_NOT_USED(duration);
    BLE_PARAMETER_NOT_USED(max_extd_adv_evts);

    BLE_SPP_COMMAND(R_BLE_SPP_GAP_StartAdv(), R_BLE_SPP_EVENT_SET_ENABLE_ADV, BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_SetAdvParam (st_ble_gap_adv_param_t * p_adv_param)
{
    uint8_t chan_map;

    /* Select lowest configured channel or all three */
    chan_map = g_ch_map_lut[p_adv_param->adv_ch_map];

    r_ble_spp_adv_param_t adv_param;
    adv_param.adv_ch_map    = chan_map;
    adv_param.filter_policy = (r_ble_spp_filter_policy_t) p_adv_param->filter_policy;
    adv_param.adv_phy       = R_BLE_SPP_SET_PHYS_PREF_1M;
    adv_param.sec_adv_phy   = R_BLE_SPP_SET_PHYS_PREF_1M;
    adv_param.adv_prop_type = R_BLE_SPP_ADV_TYPE_CONNECTABLE_UNDIRECTED;
    adv_param.adv_intv_min  = p_adv_param->adv_intv_min;
    adv_param.adv_intv_max  = p_adv_param->adv_intv_max;

    BLE_SPP_COMMAND(R_BLE_SPP_GAP_SetAdvParam(&adv_param), R_BLE_SPP_EVENT_SET_ADV_PARAM, BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_Init (uint8_t cb_num)
{
    BLE_PARAMETER_NOT_USED(cb_num);
    ble_status_t err;

    err = R_BLE_GATTS_SetDbInst(NULL);

    return err;
}

uint32_t R_BLE_IsTaskFree (void)
{
    return 0;
}

ble_status_t R_BLE_GATT_GetMtu (uint16_t conn_hdl, uint16_t * p_mtu)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_mtu);
#endif

    *p_mtu = BLE_MODULE_MTU_MAX;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_GetAttr (uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_value);
#endif

    r_ble_spp_gatt_hdl_value_pair_t value;
    r_ble_spp_gatt_value_t          gatt_value;
    gatt_value.value_len = qe_ble_profile[attr_hdl].value_length;
    value.attr_hdl       = attr_hdl;
    value.value          = gatt_value;

    BLE_SPP_COMMAND(R_BLE_SPP_GATTS_GetAttr(&value), R_BLE_SPP_EVENT_GET_ATTR, BLE_MODULE_RESET_TIMEOUT);

    p_value->p_value   = &g_current_spp_payload.out_data[1];
    p_value->value_len = gatt_value.value_len;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_SetAttr (uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);

    r_ble_spp_gatt_hdl_value_pair_t value;
    r_ble_spp_gatt_value_t          gatt_value;
    gatt_value.value_len = p_value->value_len;
    gatt_value.p_value   = p_value->p_value;
    value.attr_hdl       = attr_hdl;
    value.value          = gatt_value;

    BLE_SPP_COMMAND(R_BLE_SPP_GATTS_SetAttr(&value), R_BLE_SPP_EVENT_SET_ATTR, BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_Notification (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ntf_data)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);

    r_ble_spp_gatt_hdl_value_pair_t value;
    r_ble_spp_gatt_value_t          gatt_value;
    gatt_value.value_len = p_ntf_data->value.value_len;
    gatt_value.p_value   = p_ntf_data->value.p_value;
    value.attr_hdl       = p_ntf_data->attr_hdl;
    value.value          = gatt_value;

    BLE_SPP_COMMAND(R_BLE_SPP_GATTS_Notification(&value), R_BLE_SPP_EVENT_SEND_NOTIFY, BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_Indication (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ind_data)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);

    r_ble_spp_gatt_hdl_value_pair_t value;
    r_ble_spp_gatt_value_t          gatt_value;
    gatt_value.value_len = p_ind_data->value.value_len;
    gatt_value.p_value   = p_ind_data->value.p_value;
    value.attr_hdl       = p_ind_data->attr_hdl;
    value.value          = gatt_value;

    BLE_SPP_COMMAND(R_BLE_SPP_GATTS_Indication(&value), R_BLE_SPP_EVENT_SEND_INDICATION, BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_SetBdAddr (uint8_t area, st_ble_dev_addr_t * p_addr)
{
    BLE_PARAMETER_NOT_USED(area);
    ble_status_t status;

    if (R_BLE_SPP_GAP_SetMACID((r_ble_spp_peer_addrType_t) p_addr->type, (uint8_t *) p_addr->addr) == R_BLE_SPP_SUCCESS)
    {
        status = r_ble_spp_api_check_return_valid(R_BLE_SPP_EVENT_SET_MAC_ID, BLE_MODULE_RESET_TIMEOUT);
        if (status)
        {
            return BLE_ERR_INVALID_PTR;
        }
    }

    BLE_SPP_COMMAND(R_BLE_SPP_GAP_Init(), R_BLE_SPP_EVENT_BLE_INIT, BLE_MODULE_RESET_TIMEOUT);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_SetEvent (ble_event_cb_t cb)
{
    g_cb_event = cb;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_GetVerInfo (void)
{
    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_RegisterCb (ble_gatts_app_cb_t cb, uint8_t priority)
{
    BLE_PARAMETER_NOT_USED(priority);

    g_spp_gatt_server_cb = cb;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_Init (uint8_t cb_num)
{
    BLE_PARAMETER_NOT_USED(cb_num);

    g_spp_gatt_client_cb = NULL;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_RegisterCb (ble_gattc_app_cb_t cb, uint8_t priority)
{
    BLE_PARAMETER_NOT_USED(priority);

    g_spp_gatt_client_cb = cb;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_SetTxPower (uint16_t conn_hdl, uint8_t tx_power)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    ble_status_t status;

    if (R_BLE_SPP_GAP_SetTxPower(tx_power) == R_BLE_SPP_SUCCESS)
    {
        status = r_ble_spp_api_check_return_valid(R_BLE_SPP_EVENT_SET_TX_POWER, BLE_MODULE_RESET_TIMEOUT);
        if (status)
        {
            return BLE_ERR_INVALID_PTR;
        }
    }
    else
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_StartFirmwareUpdate (void)
{
    /* Send the 'Start firmware Update' command. */
    if (R_BLE_SPP_SUCCESS != R_BLE_SPP_GAP_Start_Firmware_Update())
    {
        return BLE_ERR_INVALID_MODE;
    }

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_SendFirmwareData (uint16_t index, uint16_t length, uint8_t const * const p_data)
{
    /* The maximum data size is 128 bytes. */
    if ((BLE_MODULE_SEND_FIRMWARE_DATA_SIZE < length) || (NULL == p_data))
    {
        return BLE_ERR_INVALID_ARG;
    }

    /* Send the 'Send Firmware Data' command. */
    if (R_BLE_SPP_SUCCESS != R_BLE_SPP_GAP_Send_Firmware_Data(index, length, (uint8_t *) p_data))
    {
        return BLE_ERR_INVALID_MODE;
    }

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_EndFirmwareUpdate (uint16_t end_index)
{
    /* Send the 'End Firmware Update' command. */
    if (R_BLE_SPP_SUCCESS != R_BLE_SPP_GAP_End_Firmware_Update(end_index, ~end_index))
    {
        return BLE_ERR_INVALID_MODE;
    }

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_GetFirmwareVersion (void)
{
    if (R_BLE_SPP_SUCCESS != R_BLE_SPP_GAP_GetVersion())
    {
        return BLE_ERR_INVALID_MODE;
    }

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_RestartModule (void)
{
    /* Send the Reboot command. */
    if (R_BLE_SPP_SUCCESS != R_BLE_SPP_GAP_Reboot())
    {
        return BLE_ERR_INVALID_MODE;
    }

    /* Wait for the command to be sent. */
    uint32_t timeout = BLE_MODULE_COMMAND_RECV_TIMEOUT;
    while (--timeout && 0 == g_transfer_complete)
    {
        r_ble_spp_api_delay_ms(1);
    }

    /* Verify that the command was sent successfully. */
    if (0 == timeout)
    {
        return BLE_ERR_RSP_TIMEOUT;
    }

    /* There is no response to the Reboot command. Periodically poll the device until it is ready. */
    for (uint32_t i = 0; i < BLE_MODULE_READY_RETRY_COUNT; i++)
    {
        /* Reset global state used for synchronization with interrupts. */
        g_spp_cmd_ready  = 0;
        g_spp_cmd_failed = 0;

        /* The R_BLE_SPP driver must be closed first, in order to issue the 'BLE Ready' command. */
        if (R_BLE_SPP_SUCCESS != R_BLE_SPP_GAP_Close(&r_ble_spp_api_transport_api))
        {
            return BLE_ERR_INVALID_MODE;
        }

        if (R_BLE_SPP_SUCCESS != R_BLE_SPP_GAP_Open(&r_ble_spp_api_transport_api))
        {
            return BLE_ERR_INVALID_MODE;
        }

        if (BLE_SUCCESS == r_ble_spp_api_check_return_valid(R_BLE_SPP_EVENT_BLE_READY, BLE_MODULE_COMMAND_RECV_TIMEOUT))
        {
            /* Get the status field from the command response. */
            ble_status_t response_status = g_current_spp_payload.out_data[0];

            /* Notify the application that the device is ready (The firmware update procedure has completed). */
            g_spp_vendor_cb((uint16_t) g_current_spp_payload.event_id, response_status, NULL);

            return BLE_SUCCESS;
        }
    }

    return BLE_ERR_RSP_TIMEOUT;
}

ble_status_t R_BLE_VS_UpdateModuleFirmware (uint8_t const * const p_firmware_image, uint32_t firmware_image_size)
{
    /* Start the firmware update procedure and wait for a response. */
    BLE_SPP_COMMAND(R_BLE_VS_StartFirmwareUpdate(),
                    BLE_VS_EVENT_START_FW_UPDATE_COMP,
                    BLE_MODULE_START_FW_UPLOAD_TIMEOUT);

    /* Calculate the total number of frames to send. */
    uint16_t total_frames =
        (uint16_t) ((firmware_image_size + BLE_MODULE_SEND_FIRMWARE_DATA_SIZE - 1) /
                    BLE_MODULE_SEND_FIRMWARE_DATA_SIZE);
    uint16_t last_index = total_frames - 1;

    for (uint16_t i = 0; i < last_index; i++)
    {
        /* Send the next 'Send Firmware Data' command and wait for a response. */
        BLE_SPP_COMMAND(R_BLE_VS_SendFirmwareData(i, BLE_MODULE_SEND_FIRMWARE_DATA_SIZE,
                                                  p_firmware_image + (i * BLE_MODULE_SEND_FIRMWARE_DATA_SIZE)),
                        BLE_VS_EVENT_SEND_FW_DATA_COMP,
                        BLE_MODULE_RESET_TIMEOUT);
    }

    /* Calculate the size of the last data frame. */
    uint16_t last_frame_size = firmware_image_size % BLE_MODULE_SEND_FIRMWARE_DATA_SIZE;
    if (0 == last_frame_size)
    {
        last_frame_size = BLE_MODULE_SEND_FIRMWARE_DATA_SIZE;
    }

    /* Send the last 'Send Firmware Data' command and wait for a response. */
    BLE_SPP_COMMAND(R_BLE_VS_SendFirmwareData(last_index, last_frame_size,
                                              p_firmware_image + (last_index * BLE_MODULE_SEND_FIRMWARE_DATA_SIZE)),
                    BLE_VS_EVENT_SEND_FW_DATA_COMP,
                    BLE_MODULE_RESET_TIMEOUT);

    /* Send the 'End Firmware Update' command and wait for a response. */
    BLE_SPP_COMMAND(R_BLE_VS_EndFirmwareUpdate(last_index),
                    BLE_VS_EVENT_END_FW_UPDATE_COMP,
                    BLE_MODULE_END_FW_UPLOAD_TIMEOUT);

    /* Reboot the module. */
    return R_BLE_VS_RestartModule();
}

///////////////////////////////////////////////////////////////////////////////
// Functions not implemented
///////////////////////////////////////////////////////////////////////////////

ble_status_t R_BLE_VS_Init (ble_vs_app_cb_t vs_cb)
{
    BLE_PARAMETER_NOT_USED(vs_cb);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_SetPairingParams (st_ble_gap_pairing_param_t * p_pair_param)
{
    BLE_PARAMETER_NOT_USED(p_pair_param);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_SetLocIdInfo (st_ble_dev_addr_t * p_lc_id_addr, uint8_t * p_lc_irk)
{
    BLE_PARAMETER_NOT_USED(p_lc_id_addr);
    BLE_PARAMETER_NOT_USED(p_lc_irk);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_ReadChar (uint16_t conn_hdl, uint16_t value_hdl)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(value_hdl);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_WriteChar (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(p_write_data);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_WriteCharWithoutRsp (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(p_write_data);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_ReadLongChar (uint16_t conn_hdl, uint16_t value_hdl, uint16_t offset)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(value_hdl);
    BLE_PARAMETER_NOT_USED(offset);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_WriteLongChar (uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data, uint16_t offset)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(p_write_data);
    BLE_PARAMETER_NOT_USED(offset);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_RspExMtu (uint16_t conn_hdl, uint16_t mtu)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(mtu);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_GetTxBufferNum (uint32_t * p_buffer_num)
{
    BLE_PARAMETER_NOT_USED(p_buffer_num);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_StartTxFlowEvtNtf (void)
{
    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_DiscPrimServ (uint16_t conn_hdl, uint8_t * p_uuid, uint8_t uuid_type)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(p_uuid);
    BLE_PARAMETER_NOT_USED(uuid_type);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_DiscIncServ (uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(p_range);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_DiscAllChar (uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(p_range);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTC_DiscAllCharDesc (uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(p_range);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GATTS_SetPrepareQueue (st_ble_gatt_pre_queue_t * p_pre_queues, uint8_t queue_num)
{
    BLE_PARAMETER_NOT_USED(p_pre_queues);
    BLE_PARAMETER_NOT_USED(queue_num);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GAP_UpdConn (uint16_t                  conn_hdl,
                                uint8_t                   mode,
                                uint16_t                  accept,
                                st_ble_gap_conn_param_t * p_conn_updt_param)
{
    BLE_PARAMETER_NOT_USED(conn_hdl);
    BLE_PARAMETER_NOT_USED(mode);
    BLE_PARAMETER_NOT_USED(accept);
    BLE_PARAMETER_NOT_USED(p_conn_updt_param);

    return BLE_SUCCESS;
}

ble_status_t R_BLE_VS_GetBdAddr (uint8_t area, uint8_t addr_type)
{
    BLE_PARAMETER_NOT_USED(area);
    BLE_PARAMETER_NOT_USED(addr_type);

    return BLE_SUCCESS;
}

/******************************************************************************
 * Static Private Functions
 ******************************************************************************/

static void r_ble_spp_api_set_ryz012_communication_mode (ble_abs_spp_comms_transport_mode_t mode)
{
    R_BSP_PinAccessEnable();

    /* Pull reset down on RYZ012 */
    R_BSP_PinWrite(BLE_ABS_CFG_RESET_PIN, BSP_IO_LEVEL_LOW);

    /* Set communications pin (PB5/GPIO_10 UART/SPI select) to proper mode */
    if (mode == BLE_SPP_COMMS_UART)
    {
        R_BSP_PinWrite(BLE_ABS_CFG_PB5_PIN, BSP_IO_LEVEL_LOW);
    }
    else
    {
        R_BSP_PinWrite(BLE_ABS_CFG_PB5_PIN, BSP_IO_LEVEL_HIGH);
    }

    /* Disable pin access while waiting for reset */
    R_BSP_PinAccessDisable();

    /* hold RYZ012 in reset/allow power to settle */
    r_ble_spp_api_delay_ms(BLE_MODULE_RESET_TIMEOUT);

    R_BSP_PinAccessEnable();

    /* Release reset pin on RYZ012 */
    R_BSP_PinWrite(BLE_ABS_CFG_RESET_PIN, BSP_IO_LEVEL_HIGH);

    R_BSP_PinAccessDisable();

    /* Allow device to come out of reset and stabilize */
    r_ble_spp_api_delay_ms(BLE_MODULE_STABILIZE_TIMEOUT);

    /* Dynamic profile can now be configured again */
    g_dynamic_profile_set = false;
}

static int r_ble_spp_api_fsp_callback_open (void * p_context)
{
    fsp_err_t       err;
    ble_abs_cfg_t * bkup_context = (ble_abs_cfg_t *) p_context;
#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_UART)
    err = bkup_context->p_uart_instance->p_api->open(bkup_context->p_uart_instance->p_ctrl,
                                                     bkup_context->p_uart_instance->p_cfg);
#elif defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
    err = bkup_context->p_spi_instance->p_api->open(bkup_context->p_spi_instance->p_ctrl,
                                                    bkup_context->p_spi_instance->p_cfg);
    bkup_context->p_irq_instance->p_api->open(bkup_context->p_irq_instance->p_ctrl,
                                              bkup_context->p_irq_instance->p_cfg);
    bkup_context->p_irq_instance->p_api->enable(bkup_context->p_irq_instance->p_ctrl);
#endif

    if (FSP_SUCCESS != err)
    {
        return R_BLE_SPP_DEVICE_NOT_OPEN;
    }

    return R_BLE_SPP_SUCCESS;
}

static int r_ble_spp_api_fsp_callback_write (void * p_context, uint8_t * p_data, uint32_t len)
{
    fsp_err_t err;
    g_transfer_complete = 0;

    ble_abs_cfg_t * bkup_context = (ble_abs_cfg_t *) p_context;
#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
 #if defined(BLE_ABS_CFG_SSL_PIN)
    R_BSP_PinAccessEnable();

    /* If the software SSL Pin is defined, then assert SSL. */
    R_BSP_PinWrite(BLE_ABS_CFG_SSL_PIN, BSP_IO_LEVEL_LOW);

    R_BSP_PinAccessDisable();
 #endif
    err = bkup_context->p_spi_instance->p_api->write(bkup_context->p_spi_instance->p_ctrl,
                                                     p_data,
                                                     len,
                                                     SPI_BIT_WIDTH_8_BITS);
#else
    err = bkup_context->p_uart_instance->p_api->write(bkup_context->p_uart_instance->p_ctrl, p_data, len);
#endif

    if (FSP_SUCCESS != err)
    {
        return R_BLE_APP_TRANSPORT_WRITE_ERROR;
    }

    return R_BLE_SPP_SUCCESS;
}

#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
static int r_ble_spp_api_fsp_callback_read (void * const   p_context,
                                            void const   * p_src,
                                            void         * p_dest,
                                            uint32_t const len,
                                            uint8_t const  bit_width)
{
    BLE_PARAMETER_NOT_USED(bit_width);

    fsp_err_t err = FSP_SUCCESS;
 #if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
  #if defined(BLE_ABS_CFG_SSL_PIN)
    R_BSP_PinAccessEnable();

    /* If the software SSL Pin is defined, then assert SSL. */
    R_BSP_PinWrite(BLE_ABS_CFG_SSL_PIN, BSP_IO_LEVEL_LOW);

    R_BSP_PinAccessDisable();
  #endif

    ble_abs_cfg_t * bkup_context = (ble_abs_cfg_t *) p_context;
    err = bkup_context->p_spi_instance->p_api->writeRead(bkup_context->p_spi_instance->p_ctrl,
                                                         p_src,
                                                         p_dest,
                                                         len,
                                                         SPI_BIT_WIDTH_8_BITS);
 #endif

    if (FSP_SUCCESS != err)
    {
        return R_BLE_APP_TRANSPORT_READ_ERROR;
    }

    return R_BLE_SPP_SUCCESS;
}

#endif

static int r_ble_spp_api_fsp_callback_close (void * p_context)
{
    fsp_err_t       err          = FSP_SUCCESS;
    ble_abs_cfg_t * bkup_context = (ble_abs_cfg_t *) p_context;
#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_UART)
    err = bkup_context->p_uart_instance->p_api->close(bkup_context->p_uart_instance->p_ctrl);
#elif defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
    err = bkup_context->p_spi_instance->p_api->close(bkup_context->p_spi_instance->p_ctrl);
#endif

    if (FSP_SUCCESS != err)
    {
        return R_BLE_APP_TRANSPORT_READ_ERROR;
    }

    return R_BLE_SPP_SUCCESS;
}

ble_status_t R_BLE_Execute (void)
{
    st_ble_gatt_value_t value;
    ble_status_t        status   = BLE_SUCCESS;
    uint16_t            attr_hdl = 0;

    if (NULL != g_cb_event)
    {
        g_cb_event();
        g_cb_event = NULL;
    }

    if (g_spp_cmd_async)
    {
        switch (g_current_spp_async_payload.event_id)
        {
            case R_BLE_SPP_EVENT_CONN_IND:
            {
                g_gap_cb(BLE_GAP_EVENT_CONN_IND, BLE_SUCCESS, NULL);
                if (NULL != g_spp_gatt_server_cb)
                {
                    g_spp_gatt_server_cb(BLE_GATTC_EVENT_CONN_IND, BLE_SUCCESS, NULL);
                }

                if (NULL != g_spp_gatt_client_cb)
                {
                    g_spp_gatt_client_cb(BLE_GATTS_EVENT_CONN_IND, BLE_SUCCESS, NULL);
                }

                break;
            }

            case R_BLE_SPP_EVENT_DISCONN_IND:
            {
                g_gap_cb(BLE_GAP_EVENT_DISCONN_IND, BLE_SUCCESS, NULL);
                if (NULL != g_spp_gatt_server_cb)
                {
                    g_spp_gatt_server_cb(BLE_GATTC_EVENT_DISCONN_IND, BLE_SUCCESS, NULL);
                }

                if (NULL != g_spp_gatt_client_cb)
                {
                    g_spp_gatt_client_cb(BLE_GATTS_EVENT_DISCONN_IND, BLE_SUCCESS, NULL);
                }

                break;
            }

            case R_BLE_SPP_EVENT_DATA_RECEIVED:
            {
                attr_hdl        = *((uint16_t *) (&g_current_spp_async_payload.out_data[1]));
                value.value_len = (uint16_t) (g_current_spp_async_payload.out_len - 5);
                value.p_value   = &g_current_spp_async_payload.out_data[3];

                status = R_BLE_GATTS_SetAttr(0, attr_hdl, &value);

                if (NULL != g_spp_gatt_server_cb)
                {
                    st_ble_gatts_evt_data_t      event_write_data;
                    st_ble_gatts_write_rsp_evt_t event_write;
                    event_write.attr_hdl       = attr_hdl;
                    event_write_data.conn_hdl  = 0;
                    event_write_data.param_len = value.value_len;
                    event_write_data.p_param   = (void *) &event_write;
                    g_spp_gatt_server_cb(BLE_GATTS_EVENT_WRITE_RSP_COMP, BLE_SUCCESS, (void *) &event_write_data);
                }

                break;
            }

            case R_BLE_SPP_EVENT_SET_ENABLE_ADV:
            {
                g_gap_cb(BLE_GAP_EVENT_ADV_ON, BLE_SUCCESS, NULL);
                break;
            }

            case R_BLE_SPP_EVENT_SET_DISABLE_ADV:
            {
                g_gap_cb(BLE_GAP_EVENT_ADV_OFF, BLE_SUCCESS, NULL);
                break;
            }

            case R_BLE_SPP_EVENT_BLE_READY:
            case BLE_VS_EVENT_START_FW_UPDATE_COMP:
            case BLE_VS_EVENT_SEND_FW_DATA_COMP:
            case BLE_VS_EVENT_END_FW_UPDATE_COMP:
            case BLE_VS_EVENT_OTA_START_NOTIFY:
            case BLE_VS_EVENT_OTA_END_NOTIFY:
            case BLE_VS_EVENT_OTA_ERROR_NOTIFY:
            {
                /* Get the status field from the command response. */
                ble_status_t response_status = g_current_spp_async_payload.out_data[0];

                g_spp_vendor_cb((uint16_t) g_current_spp_async_payload.event_id, response_status, NULL);
                break;
            }

            case BLE_VS_EVENT_GET_FW_VERSION_COMP:
            {
                /* Get the status field from the command response. */
                ble_status_t response_status = g_current_spp_async_payload.out_data[0];

                /* Get the firmware version field from the command response. */
                st_ble_vs_evt_data_t vendor_data =
                {
                    .p_param   = &g_current_spp_async_payload.out_data[1],
                    .param_len = sizeof(st_ble_vs_get_fw_version_comp_evt_t)
                };

                g_spp_vendor_cb((uint16_t) g_current_spp_async_payload.event_id, response_status, &vendor_data);

                break;
            }
        }

        g_spp_cmd_async = 0;
    }

    return status;
}

static void r_ble_spp_api_mw_callback (r_ble_spp_payload_t * p_payload)
{
    /* NOTE: Async event will be detected and sent to upper layer callback */
    switch (p_payload->event_id)
    {
        case R_BLE_SPP_EVENT_CONN_IND:
        case R_BLE_SPP_EVENT_DISCONN_IND:
        case R_BLE_SPP_EVENT_DATA_RECEIVED:
        case BLE_VS_EVENT_OTA_START_NOTIFY:
        case BLE_VS_EVENT_OTA_END_NOTIFY:
        case BLE_VS_EVENT_OTA_ERROR_NOTIFY:
        case BLE_VS_EVENT_GET_FW_VERSION_COMP:
        {
            g_current_spp_async_payload = *p_payload;
            g_spp_cmd_async             = 1;
            break;
        }

        case BLE_VS_EVENT_START_FW_UPDATE_COMP:
        case BLE_VS_EVENT_SEND_FW_DATA_COMP:
        case BLE_VS_EVENT_END_FW_UPDATE_COMP:
        case R_BLE_SPP_EVENT_SET_ENABLE_ADV:
        case R_BLE_SPP_EVENT_SET_DISABLE_ADV:
        {
            g_current_spp_payload       = *p_payload;
            g_current_spp_async_payload = *p_payload;

            if ((p_payload->out_data[0] == 0) && (p_payload->out_len >= 1))
            {
                g_spp_cmd_ready = 1;
                g_spp_cmd_async = 1;
            }
            else
            {
                g_spp_cmd_failed = 1;
            }

            break;
        }

        case R_BLE_SPP_EVENT_BLE_READY:
        case R_BLE_SPP_EVENT_SET_MAC_ID:
        case R_BLE_SPP_EVENT_DYNAMIC_ATTRIBUTE_CREATE:
        case R_BLE_SPP_EVENT_DYNAMIC_ATTRIBUTE_COMPLETE:
        case R_BLE_SPP_EVENT_BLE_INIT:
        case R_BLE_SPP_EVENT_SET_ADV_SRES:
        case R_BLE_SPP_EVENT_GET_ATTR:
        case R_BLE_SPP_EVENT_SET_ATTR:
        case R_BLE_SPP_EVENT_SET_ADV_PARAM:
        case R_BLE_SPP_EVENT_SET_TX_POWER:
        {
            g_current_spp_payload = *p_payload;

            if ((p_payload->out_data[0] == 0) && (p_payload->out_len >= 1))
            {
                g_spp_cmd_ready = 1;
            }
            else
            {
                g_spp_cmd_failed = 1;
            }

            break;
        }

        default:
        {
            g_current_spp_payload = *p_payload;
            g_spp_cmd_unknown     = 1;
            break;
        }
    }
}

#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_UART)
void rm_ble_spp_callback (uart_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
            r_ble_spp_rx_char_callback((uint8_t) p_args->data);
            break;
        }

        case UART_EVENT_TX_COMPLETE:
        {
            g_transfer_complete = 1;
            break;
        }

        default:
        {
            break;
        }
    }
}

#endif

#if defined(RM_BLE_ABS_SPP_TRANSPORT_INTERFACE_SPI)
void rm_ble_spp_host_spi_callback (spi_callback_args_t * p_args)
{
    if (p_args->event == SPI_EVENT_TRANSFER_COMPLETE)
    {
 #if defined(BLE_ABS_CFG_SSL_PIN)
        R_BSP_PinAccessEnable();

        /* If the software SSL Pin is defined, then negate SSL. */
        R_BSP_PinWrite(BLE_ABS_CFG_SSL_PIN, BSP_IO_LEVEL_HIGH);

        R_BSP_PinAccessDisable();
 #endif

        if (BLE_MODULE_SPI_READ_STATE_IDLE != g_spi_read_state)
        {
            /* A SPI read operation has completed. */
            static uint32_t g_event_length = 0;

            /* If the body of the packet has been read successfully, then pass the data on to the r_ble_spp layer. */
            if (BLE_MODULE_SPI_READ_STATE_BODY == g_spi_read_state)
            {
                uint8_t * p_payload = &g_spi_rx_buffer[BLE_MODULE_SPP_SPI_READ_HEADER_SIZE];
                for (uint32_t i = 0; i < g_event_length; i++)
                {
                    r_ble_spp_rx_char_callback(p_payload[i]);
                }

                /* The SPI read operation has completed. */
                g_spi_read_state = BLE_MODULE_SPI_READ_STATE_IDLE;

                /* Re-enable the data ready IRQ so that the next event can be processed. */
                R_BSP_IrqEnableNoClear(gp_instance_ctrl->p_cfg->p_irq_instance->p_cfg->irq);
            }
            else
            {
                /* The packet header has been read, the body must now be read. */
                g_spi_read_state = BLE_MODULE_SPI_READ_STATE_BODY;

                /* Get the length of the payload from the header. */
                g_event_length = g_spi_rx_buffer[5];

                /* Calculate the total event length. */
                g_event_length += BLE_MODULE_SPP_SPI_READ_EVENT_SIZE;
                g_event_length += BLE_MODULE_SPP_SPI_READ_CHECKSUM_SIZE;

                r_ble_spp_api_fsp_callback_read((void * const) gp_instance_ctrl->p_cfg,
                                                g_spi_tx_buffer,
                                                g_spi_rx_buffer,
                                                BLE_MODULE_SPP_SPI_READ_HEADER_SIZE + g_event_length,
                                                8);
            }
        }
        else
        {
            /* A SPI write operation has been completed. */
            g_transfer_complete = 1;
        }
    }
}

void rm_ble_spp_data_ready_callback (external_irq_callback_args_t * p_args)
{
    BLE_PARAMETER_NOT_USED(p_args);

    /* Temporarily mask the data ready interrupt so that SPI read operations don't interrupted. */
    R_BSP_IrqDisable(gp_instance_ctrl->p_cfg->p_irq_instance->p_cfg->irq);

    /* Kick off first read operation. This reads the length of the event packet. */
    g_spi_read_state = BLE_MODULE_SPI_READ_STATE_HEADER;

    /* Set SPI transmit data used to start a read operation. */
    g_spi_tx_buffer[0] = 0x04;         // NOLINT(readability-magic-numbers)
    g_spi_tx_buffer[1] = 0x8B;         // NOLINT(readability-magic-numbers)
    g_spi_tx_buffer[2] = 0x00;         // NOLINT(readability-magic-numbers)
    g_spi_tx_buffer[3] = 0x80;         // NOLINT(readability-magic-numbers)

    r_ble_spp_api_fsp_callback_read((void * const) gp_instance_ctrl->p_cfg,
                                    g_spi_tx_buffer,
                                    g_spi_rx_buffer,
                                    BLE_MODULE_SPP_SPI_READ_HEADER_SIZE + BLE_MODULE_SPP_SPI_READ_EVENT_SIZE,
                                    8);
}

#endif

static ble_status_t r_ble_spp_api_check_return_valid (uint32_t expected_spp_reply, uint32_t timeout)
{
    ble_status_t status = BLE_SUCCESS;

    uint32_t countdown = timeout;

    /* Wait for data transmit to complete */
    while (--countdown && !g_transfer_complete)
    {
        r_ble_spp_api_delay_ms(1);
    }

    /* Wait for data receive to complete */
    while (--countdown && !g_spp_cmd_ready && !g_spp_cmd_failed)
    {
        r_ble_spp_api_delay_ms(1);
    }

    /* Check if the command response is ready. */
    if (g_spp_cmd_ready)
    {
        /* Check if the expected response was received. */
        if (g_current_spp_payload.event_id != expected_spp_reply)
        {
            status = BLE_ERR_HC_UNKNOWN_HCI_CMD;
        }
    }
    /* Check if the command failed. */
    else if (g_spp_cmd_failed)
    {
        status = BLE_ERR_HC_CMD_DISALLOWED;
    }
    else
    {
        /* No response was received. */
        status = BLE_ERR_RSP_TIMEOUT;
    }

    g_spp_cmd_ready  = 0;
    g_spp_cmd_failed = 0;

    return status;
}

static void r_ble_spp_api_delay_ms (uint32_t ms)
{
#if (BSP_CFG_RTOS == 2)
    vTaskDelay(pdMS_TO_TICKS(ms));
#else
    R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS);
#endif
}
