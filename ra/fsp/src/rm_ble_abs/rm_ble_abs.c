/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include <stdlib.h>

#include "rm_ble_abs_api.h"
#include "rm_ble_abs.h"

#include "fsp_common_api.h"

#if ((BSP_CFG_RTOS == 2))
 #include "FreeRTOS.h"
 #include "task.h"
 #include "event_groups.h"
 #define BLE_EVENT_PATTERN    (0x0A0A)
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "BLE_ABS" in ASCII, used to determine if module is open. */
#define BLE_ABS_OPEN    (0X00424C45ULL)

/**********************************/
/** Define for advertising handle */
/**********************************/
/** Advertising Handle for Legacy Advertising. */
#define BLE_ABS_LEGACY_HDL      (0x00)

/** Advertising Handle for Extended Advertising. */
#define BLE_ABS_EXT_HDL         (0x01)

/** Advertising Handle for Non-Connectable Advertising. */
#define BLE_ABS_NON_CONN_HDL    (0x02)

/** Advertising Handle for Periodic Advertising. */
#define BLE_ABS_PERD_HDL        (0x03)

/** Advertising Handle for Legacy Advertising */
#define BLE_ABS_COMMON_HDL      (0x00)

/**********************************/
/** Define for advertising status */
/**********************************/
/** set fast advertising parameters */
#define BLE_ABS_ADV_STATUS_PARAM_FAST        (0x00000001)

/** set slow advertising parameters */
#define BLE_ABS_ADV_STATUS_PARAM_SLOW        (0x00000002)

/** set advertising data */
#define BLE_ABS_ADV_STATUS_ADV_DATA          (0x00000010)

/** set scan response data */
#define BLE_ABS_ADV_STATUS_SRES_DATA         (0x00000020)

/** set periodic advertising data */
#define BLE_ABS_ADV_STATUS_PERD_DATA         (0x00000040)

/** start fast advertising */
#define BLE_ABS_ADV_STATUS_ADV_FAST_START    (0x00000100)

/** start slow advertising */
#define BLE_ABS_ADV_STATUS_ADV_SLOW_START    (0x00000200)

/** set periodic advertising parameters */
#define BLE_ABS_ADV_STATUS_PERD_PARAM        (0x00001000)

/** start periodic advertising */
#define BLE_ABS_ADV_STATUS_PERD_START        (0x00010000)

/** set legacy adv for legacy advertising  */
#define BLE_ABS_ADV_COMM_LEG                 (0x00100000)

/** set non-connectable adv for legacy advertising  */
#define BLE_ABS_ADV_COMM_NON                 (0x00200000)

/** set non-connectable adv for legacy advertising  */
#define BLE_ABS_ADV_COMM_TO                  (0x01000000)

/**********************************/
/** Define for scan status        */
/**********************************/
/** start fast scan */
#define BLE_ABS_SCAN_STATUS_FAST_START    (0x00000001)

/** start slow scan */
#define BLE_ABS_SCAN_STATUS_SLOW_START    (0x00000002)

/**********************************/
/** Define for privacy status     */
/**********************************/
/** create irk */
#define BLE_ABS_PV_STATUS_CREATE_IRK    (0x00000001)

/** add irk to resolving list */
#define BLE_ABS_PV_STATUS_ADD_RSLV      (0x00000002)

/** set privacy mode */
#define BLE_ABS_PV_STATUS_SET_MODE      (0x00000004)

/** enable resolvable private address function */
#define BLE_ABS_PV_STATUS_EN_RPA        (0x00000008)

/**********************************/
/** Define for create connection  */
/**********************************/
/** scan interval for connection request with 1M & 2M PHY */
#define BLE_ABS_CONN_SC_INTV_FAST                              (0x0060)

/** scan window for connection request with 1M & 2M PHY */
#define BLE_ABS_CONN_SC_WINDOW_FAST                            (0x0030)

/** scan interval for connection request with coded PHY */
#define BLE_ABS_CONN_SC_INTV_SLOW                              (0x0180)

/** scan window for connection request with coded PHY */
#define BLE_ABS_CONN_SC_WINDOW_SLOW                            (0x0090)

/** minimum advertising data length */
#define BLE_ABS_LEGACY_ADV_DATA_LEN                            (31)
#define BLE_ABS_CONN_EXT_ADV_DATA_LEN                          (229)

/** add magic number value set */
#define BLE_ABS_GAP_CONNECTION_CE_LENGTH                       (0xFFFF)
#define BLE_ABS_SET_PAIRING_MAXIMUM_LTK_SIZE                   (0x10)
#define BLE_ABS_SECURE_DATA_BOND_ADDRESS_FF                    (0xFF)
#define BLE_ABS_GAP_REMOTE_IRK_AA                              (0xAA)
#define BLE_ABS_REMOTE_DEVICE_ADDRESS_55                       (0x55)
#define BLE_ABS_GAP_EVENT_CONNECTION_TIMEOUT_1000              (1000)

/*** r_ble_sec_data functions added start ***/
#if (BLE_ABS_CFG_ENABLE_SECURE_DATA == 1)
 #define BLE_SECD_UPD_BN_ADD                                   (0x00)
 #define BLE_SECD_UPD_BN_ADD_OVERWR                            (0x01)
 #define BLE_SECD_UPD_BN_DEL                                   (0x02)
 #define BLE_SECD_UPD_BN_ALL_DEL                               (0x03)
 #define BLE_ABS_SECURE_DATA_DELETE_LOCAL_FF                   (0xFF)
 #define BLE_ABS_SECURE_DATA_UPDATE_BOND_NUMBER_FF             (0xFF)
 #define BLE_ABS_SECURE_DATA_REMOTE_BOND_NUMBER_FF             (0xFF)
 #define BLE_ABS_SECURE_DATA_BOND_ADDRESS_FF                   (0xFF)
 #define BLE_ABS_SECURE_DATA_BOND_CHECK_FF                     (0xFF)
#endif

#if (BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE != 0)
 #define BLE_DEV_DATA_DF_ADDR                                  _BLE_DF_ADDR(BLE_CFG_DEV_DATA_DF_BLOCK)
 #define BLE_ABS_SECURE_DATA_DF_ADDR                           _BLE_DF_ADDR(BLE_CFG_SECD_DATA_DF_BLOCK)
#elif (BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE != 0)
 #define BLE_DEV_DATA_DF_ADDR                                  _BLE_DF_ADDR(BLE_CFG_DEV_DATA_DF_BLOCK)
 #define BLE_ABS_SECURE_DATA_DF_ADDR                           _BLE_DF_ADDR(BLE_CFG_SECD_DATA_DF_BLOCK)
#endif

/**** RF event notify function pointer ****/
#define BLE_EVENT_TYPE_CONN                                    (0x0000U)
#define BLE_EVENT_TYPE_ADV                                     (0x0001U)
#define BLE_EVENT_TYPE_SCAN                                    (0x0002U)
#define BLE_EVENT_TYPE_INITIATOR                               (0x0003U)

#define BLE_EVENT_NOTIFY_CONN_START_POS                        (0)
#define BLE_EVENT_NOTIFY_ADV_START_POS                         (1)
#define BLE_EVENT_NOTIFY_SCAN_START_POS                        (2)
#define BLE_EVENT_NOTIFY_INIT_START_POS                        (3)
#define BLE_EVENT_NOTIFY_CONN_CLOSE_POS                        (4)
#define BLE_EVENT_NOTIFY_ADV_CLOSE_POS                         (5)
#define BLE_EVENT_NOTIFY_SCAN_CLOSE_POS                        (6)
#define BLE_EVENT_NOTIFY_INIT_CLOSE_POS                        (7)
#define BLE_EVENT_NOTIFY_DS_START_POS                          (8)
#define BLE_EVENT_NOTIFY_DS_CLOSE_POS                          (9)

#define BLE_EVENT_TYPE_RF_DS_START                             (0x0U)
#define BLE_EVENT_TYPE_RF_DS_CLOSE                             (0x1U)

#define BLE_EVENT_NOTIFY_CONN_START_BIT                        (0x1U << BLE_EVENT_NOTIFY_CONN_START_POS)
#define BLE_EVENT_NOTIFY_ADV_START_BIT                         (0x1U << BLE_EVENT_NOTIFY_ADV_START_POS)
#define BLE_EVENT_NOTIFY_SCAN_START_BIT                        (0x1U << BLE_EVENT_NOTIFY_SCAN_START_POS)
#define BLE_EVENT_NOTIFY_INIT_START_BIT                        (0x1U << BLE_EVENT_NOTIFY_INIT_START_POS)

#define BLE_EVENT_NOTIFY_CONN_CLOSE_BIT                        (0x1U << BLE_EVENT_NOTIFY_CONN_CLOSE_POS)
#define BLE_EVENT_NOTIFY_ADV_CLOSE_BIT                         (0x1U << BLE_EVENT_NOTIFY_ADV_CLOSE_POS)
#define BLE_EVENT_NOTIFY_SCAN_CLOSE_BIT                        (0x1U << BLE_EVENT_NOTIFY_SCAN_CLOSE_POS)
#define BLE_EVENT_NOTIFY_INIT_CLOSE_BIT                        (0x1U << BLE_EVENT_NOTIFY_INIT_CLOSE_POS)

#define BLE_EVENT_NOTIFY_DS_START_BIT                          (0x1U << BLE_EVENT_NOTIFY_DS_START_POS)
#define BLE_EVENT_NOTIFY_DS_CLOSE_BIT                          (0x1U << BLE_EVENT_NOTIFY_DS_CLOSE_POS)

#define BLE_EVENT_NOTIFY_START_MASK                            ( \
        (BLE_EVENT_NOTIFY_CONN_START_BIT) |                      \
        (BLE_EVENT_NOTIFY_ADV_START_BIT) |                       \
        (BLE_EVENT_NOTIFY_SCAN_START_BIT) |                      \
        (BLE_EVENT_NOTIFY_INIT_START_BIT) |                      \
        (0x0U))

#define BLE_EVENT_NOTIFY_CLOSE_MASK                            ( \
        (BLE_EVENT_NOTIFY_CONN_CLOSE_BIT) |                      \
        (BLE_EVENT_NOTIFY_ADV_CLOSE_BIT) |                       \
        (BLE_EVENT_NOTIFY_SCAN_CLOSE_BIT) |                      \
        (BLE_EVENT_NOTIFY_INIT_CLOSE_BIT) |                      \
        (0x0U))

#define BLE_EVENT_NOTIFY_DS_MASK                               ( \
        (BLE_EVENT_NOTIFY_DS_START_BIT) |                        \
        (BLE_EVENT_NOTIFY_DS_CLOSE_BIT) |                        \
        (0x0U))

#define BLE_HOST_TBL_NUM                                       8

#define BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE                  (4)
#define BLE_ABS_SECURE_DATA_MAGIC_NUMBER                       (0x12345678)

/** Internal data flash base address. */
#define BLE_ABS_SECURE_DATA_BLOCK_BASE                         (0x40100000)

#if (BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE != 0)
 #define BLE_ABS_SECURE_DATA_BLOCK_SIZE                        (BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE)
#elif (BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE != 0)
 #define BLE_ABS_SECURE_DATA_BLOCK_SIZE                        (BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE)
#endif

#define BLE_ABS_SECURE_DATA_BONDING_NUMBER_OFFSET              BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE
#define BLE_ABS_SECURE_DATA_OUT_BONDING_OFFSET                 (5)
#define BLE_ABS_SECURE_DATA_SECURITY_INFOMATION_OFFSET         (8)
#define BLE_ABS_SECURE_DATA_SECURITY_KEYS_INFOMATION_OFFSET    (12)
#define BLE_ABS_SECURE_DATA_SECURITY_KEYS_OFFSET               (20)
#define BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET             (48)

#define BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE                (88)
#define BLE_ABS_SECURE_DATA_LOCAL_AREA_SIZE                    (40)
#define BLE_ABS_SECURE_DATA_LOCAL_INFOMATION_SIZE              (1)
#define BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE      (7)
#define BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE               (8)
#define BLE_ABS_SECURE_DATA_REMOTE_KEY_ATTRIBUTE_SIZE          (6)
#define BLE_ABS_SECURE_DATA_REMOTE_KEYS_SIZE                   (65)
#define BLE_ABS_SECURE_DATA_REMOTE_KEYS_INFOMATION_SIZE        (4)

#define BLE_ABS_SECURE_DATA_BASE_ADDR                          (BLE_ABS_SECURE_DATA_BLOCK_BASE +           \
                                                                (BLE_ABS_CFG_SECURE_DATA_DATAFLASH_BLOCK * \
                                                                 BLE_ABS_SECURE_DATA_BLOCK_SIZE))
#define BLE_ABS_SECURE_DATA_ADDR_MGN_DATA                      (BLE_ABS_SECURE_DATA_BASE_ADDR)
#define BLE_ABS_SECURE_DATA_SEC_BOND_NUM                       (BLE_ABS_SECURE_DATA_ADDR_MGN_DATA + \
                                                                BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE)
#define BLE_ABS_SECURE_DATA_ADDR_LOC_AREA                      (BLE_ABS_SECURE_DATA_BASE_ADDR + \
                                                                BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE)
#define BLE_ABS_SECURE_DATA_ADDR_LOC_IRK                       (BLE_ABS_SECURE_DATA_ADDR_LOC_AREA)
#define BLE_ABS_SECURE_DATA_ADDR_LOC_CSRK                      (BLE_ABS_SECURE_DATA_ADDR_LOC_IRK + BLE_GAP_IRK_SIZE)
#define BLE_ABS_SECURE_DATA_ADDR_LOC_IDADDR                    (BLE_ABS_SECURE_DATA_ADDR_LOC_CSRK + BLE_GAP_CSRK_SIZE)
#define BLE_ABS_SECURE_DATA_ADDR_LOC_INFO                      (BLE_ABS_SECURE_DATA_ADDR_LOC_IDADDR + \
                                                                BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE)
#define BLE_ABS_SECURE_DATA_ADDR_REM_START                     (BLE_ABS_SECURE_DATA_ADDR_LOC_INFO + \
                                                                BLE_ABS_SECURE_DATA_LOCAL_INFOMATION_SIZE)
#define BLE_ABS_SECURE_DATA_MAX_SIZE                           (BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + \
                                                                BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE *    \
                                                                BLE_ABS_CFG_NUMBER_BONDING)
#define BLE_ABS_SECURE_DATA_BLOCK_SIZE_MASK                    (BLE_ABS_SECURE_DATA_BLOCK_SIZE - 1UL)

/** The invalid timer handle. */
#define BLE_TIMER_INVALID_HDL                                  (0xFF)

/** add magic number value set */
#define BLE_ABS_TIMER_REMAIN_TIMESHORTEST                      (0xFFFFFFFF)
#define BLE_ABS_TIMER_DEFAULT_TIMEOUT_MS                       (1000)
#define BLE_ABS_TIMER_METRIC_PREFIX                            (1000)

/***********************************************************************************************************************
 * Local Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static fsp_err_t ble_abs_set_pairing_parameter(ble_abs_pairing_parameter_t * p_pairing_parameter);
static fsp_err_t ble_abs_convert_legacy_advertising_parameter(
    ble_abs_legacy_advertising_parameter_t * p_legacy_advertising_parameter,
    st_ble_gap_adv_param_t                 * p_gap_advertising_parameter);

#if (BLE_CFG_LIBRARY_TYPE == 0)
static fsp_err_t ble_abs_convert_extend_advertising_parameter(
    ble_abs_extend_advertising_parameter_t * advertising_parameter,
    st_ble_gap_adv_param_t                 * p_gap_advertising_parameter);

#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
static fsp_err_t ble_abs_convert_non_connectable_advertising_parameter(
    ble_abs_non_connectable_advertising_parameter_t * p_non_connectable_advertising_parameter,
    st_ble_gap_adv_param_t                          * p_gap_advertising_parameter,
    uint8_t                                           advertising_handle);
static fsp_err_t ble_abs_advertising_report_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                    st_ble_evt_data_t             * p_event_data);
static fsp_err_t ble_abs_check_scan_phy_parameter(ble_abs_scan_phy_parameter_t * p_scan_phy);
static fsp_err_t ble_abs_set_scan_parameter(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                            ble_abs_scan_parameter_t      * p_scan_parameter);

static void ble_abs_gap_callback(uint16_t event_type, ble_status_t event_result, st_ble_evt_data_t * p_event_data);
static void ble_abs_vendor_specific_callback(uint16_t               event_type,
                                             ble_status_t           event_result,
                                             st_ble_vs_evt_data_t * p_event_data);
static void ble_abs_set_abs_callback(ble_abs_instance_ctrl_t * const            p_instance_ctrl,
                                     ble_gap_application_callback_t             gap_callback,
                                     ble_vendor_specific_application_callback_t vendor_specific_callback);
static void ble_abs_set_advertising_status(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                           uint8_t                         advertising_handle,
                                           uint32_t                        set,
                                           uint32_t                        clear);
static void ble_abs_set_advertising_parameter(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                              void                          * p_advertising_parameter,
                                              uint8_t                         advertising_handle);
static void ble_abs_cancel_connection_function(void);

#if (BLE_CFG_LIBRARY_TYPE != 0)
static void ble_abs_advertising_to_function(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_handle);

#endif                                 /* (BLE_CFG_LIBRARY_TYPE != 0) */
static void ble_abs_set_scan_status(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t set, uint32_t clear);
static void ble_abs_update_data_status(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                       uint32_t                        advertising_status,
                                       uint8_t                       * p_advertising_data,
                                       uint16_t                        advertising_data_len,
                                       uint8_t                         advertising_handle);
static void ble_abs_connection_indication_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void ble_abs_scan_to_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void ble_abs_loc_ver_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl, st_ble_evt_data_t * p_event_data);
static void ble_abs_advertising_parameter_set_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                      st_ble_evt_data_t             * p_event_data);
static void ble_abs_advertising_data_set_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                 st_ble_evt_data_t             * p_event_data);
static void ble_abs_periodic_parameter_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void ble_abs_advertising_off_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                            st_ble_evt_data_t             * p_event_data);
static void ble_abs_conflict_resolving_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                               st_ble_evt_data_t             * p_event_data);
static void ble_abs_random_handler(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                   st_ble_vs_evt_data_t          * p_event_data);
static void ble_abs_set_irk_to_resolving_list(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint8_t * p_lc_irk);
static void ble_abs_advertising_start(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint8_t advertising_handle);
static void ble_abs_advertising_set_data(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                         uint8_t                         advertising_handle,
                                         uint8_t                         data_type);
static void ble_abs_set_legacy_scan_response_data(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void ble_abs_convert_scan_phy_parameter(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                               ble_abs_scan_phy_parameter_t  * p_abs_phy,
                                               ble_gap_scan_phy_parameter_t  * p_gap_phy,
                                               ble_gap_scan_on_t             * p_scan_enable);
static void ble_abs_set_connection_parameter(ble_abs_connection_phy_parameter_t * p_abs_connection_parameter,
                                             ble_gap_connection_phy_parameter_t * p_connection_phy_parameter,
                                             ble_gap_connection_parameter_t     * p_connection_parameter);
static void ble_abs_convert_scan_parameter(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                           st_ble_gap_scan_param_t       * p_scan_parameter,
                                           ble_gap_scan_on_t             * p_scan_enable,
                                           uint32_t                        status);
static void ble_abs_set_connection_advertising_interval(st_ble_gap_adv_param_t * p_advertising_parameter,
                                                        uint32_t                 fast_advertising_interval,
                                                        uint32_t                 slow_advertising_interval,
                                                        uint16_t                 fast_period);

/*** ble secure data functions start ***/

static fsp_err_t ble_abs_secure_data_writelocinfo(flash_instance_t const * p_instance,
                                                  ble_device_address_t   * p_lc_id_addr,
                                                  uint8_t                * p_lc_irk,
                                                  uint8_t                * p_lc_csrk);
static fsp_err_t ble_abs_secure_data_readlocinfo(flash_instance_t const * p_instance,
                                                 ble_device_address_t   * p_lc_id_addr,
                                                 uint8_t                * p_lc_irk,
                                                 uint8_t                * p_lc_csrk);
static void      ble_abs_secure_data_recvremkeys(ble_device_address_t * p_addr, st_ble_gap_key_ex_param_t * p_keys);
static fsp_err_t ble_abs_secure_data_writeremkeys(flash_instance_t const * p_instance,
                                                  ble_device_address_t   * p_addr,
                                                  st_ble_gap_auth_info_t * p_keyinfo);
static fsp_err_t ble_abs_secure_data_init(flash_instance_t const * p_instance);

#if (BLE_ABS_CFG_ENABLE_SECURE_DATA == 1)

static st_ble_gap_key_ex_param_t gs_key_ex_param;
static st_ble_gap_key_dist_t     gs_key_dist;

static const ble_device_address_t invalid_rem_addr =
{
    .addr = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    .type = 0xFF
};

static fsp_err_t ble_abs_secure_data_find_entry(ble_device_address_t * p_dev_addr,
                                                int32_t              * p_entry,
                                                uint8_t              * p_sec_data);
static void      ble_abs_secure_data_find_oldest_entry(flash_instance_t const * p_instance, int32_t * p_entry);
static fsp_err_t ble_abs_secure_data_update_bond_num(flash_instance_t const * p_instance,
                                                     int32_t                  entry,
                                                     int32_t                  op_code,
                                                     uint8_t                * p_alloc_bond_num,
                                                     uint8_t                * p_sec_data);
static void ble_abs_secure_data_update_bond_order(flash_instance_t const * p_instance,
                                                  int32_t                  entry,
                                                  uint8_t                * p_sec_data,
                                                  uint8_t                  bond_order);
static fsp_err_t ble_abs_secure_data_is_valid_entry(flash_instance_t const * p_instance, int32_t entry);
static fsp_err_t ble_abs_secure_data_read_bond_info(flash_instance_t const * p_instance,
                                                    uint8_t                * p_out_bond_num,
                                                    uint8_t               ** pp_sec_data,
                                                    st_ble_gap_bond_info_t * p_bond_info);
static void ble_abs_secure_data_release_bond_info_buf(uint8_t * p_sec_data);

#endif
static fsp_err_t ble_abs_secure_data_flash_read(flash_instance_t const * p_instance,
                                                uint32_t                 addr,
                                                uint8_t                * buff,
                                                uint16_t                 len);
static fsp_err_t ble_abs_secure_data_flash_write(flash_instance_t const * p_instance,
                                                 uint32_t                 addr,
                                                 uint8_t                * buff,
                                                 uint16_t                 len);

uint8_t r_dflash_read(uint32_t addr, uint8_t * buff, uint16_t len);
uint8_t r_dflash_write(uint32_t addr, uint8_t * buff, uint16_t len);

/*** ble secure data functions end ***/

/*** platform control functions added start ***/

void    r_ble_rf_control_error(uint32_t err_no);
uint8_t r_ble_rf_power_save_mode(void);

#if (BSP_CFG_RTOS == 2)
void r_ble_wake_up_task(void * EventGroupHandle);
void r_ble_wake_up_task_from_isr(void * EventGroupHandle);

#endif

/*** platform control functions end ***/

/*** ble timer functions start ***/
static void      ble_abs_timer_update_remaining_time_ms(ble_abs_instance_ctrl_t * const p_instance_ctrl, bool expired);
static uint32_t  ble_abs_timer_alloc_timer(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void      ble_abs_timer_free_timer(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl);
static void      ble_abs_timer_start_timer(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void      ble_abs_timer_stop_timer(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void      ble_abs_timer_add_timer(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl);
static void      ble_abs_timer_remove_timer(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl);
static void      ble_abs_timer_event_cb(ble_abs_instance_ctrl_t * const p_instance_ctrl);
void             ble_abs_timer_process_timer_expire(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void      ble_abs_timer_init(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static void      ble_abs_timer_terminate(ble_abs_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ble_abs_timer_create(ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                      uint32_t                      * p_timer_hdl,
                                      uint32_t                        timeout_ms,
                                      uint8_t                         type,
                                      ble_abs_timer_cb_t              cb);
static fsp_err_t ble_abs_timer_delete(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t * p_timer_hdl);
static fsp_err_t ble_abs_timer_start(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl);
static fsp_err_t ble_abs_timer_stop(ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl);
static void      ble_abs_init_hw_timer(timer_instance_t const * p_instance);
static void      ble_abs_terminate_hw_timer(timer_instance_t const * p_instance);
static void      ble_abs_start_hw_timer(timer_instance_t const * p_instance,
                                        uint32_t               * current_timeout_ms,
                                        uint32_t               * elapsed_timeout_ms,
                                        uint32_t                 timeout_ms);
static void ble_abs_stop_hw_timer(timer_instance_t const * p_instance,
                                  uint32_t               * current_timeout_ms,
                                  uint32_t               * elapsed_timeout_ms);
static uint32_t ble_abs_get_elapsed_time_ms(timer_instance_t const * p_instance,
                                            bool                     expired,
                                            const uint32_t           current_timeout_ms,
                                            uint32_t               * elapsed_timeout_ms);
void ble_abs_hw_timer_callback(timer_callback_args_t * callback_args);

/*** ble timer functions end ***/

/* Version data structure. */
static const fsp_version_t g_ble_abs_version =
{
    .api_version_minor  = BLE_ABS_API_VERSION_MINOR,
    .api_version_major  = BLE_ABS_API_VERSION_MAJOR,
    .code_version_minor = BLE_ABS_CODE_VERSION_MINOR,
    .code_version_major = BLE_ABS_CODE_VERSION_MAJOR
};

/** BLE ABS on BLE HAL API mapping for BLE ABS interface */
const ble_abs_api_t g_ble_abs_on_ble =
{
    .open                           = RM_BLE_ABS_Open,
    .close                          = RM_BLE_ABS_Close,
    .reset                          = RM_BLE_ABS_Reset,
    .versionGet                     = RM_BLE_ABS_VersionGet,
    .startLegacyAdvertising         = RM_BLE_ABS_StartLegacyAdvertising,
    .startExtendedAdvertising       = RM_BLE_ABS_StartExtendedAdvertising,
    .startNonConnectableAdvertising = RM_BLE_ABS_StartNonConnectableAdvertising,
    .startPeriodicAdvertising       = RM_BLE_ABS_StartPeriodicAdvertising,
    .startScanning                  = RM_BLE_ABS_StartScanning,
    .createConnection               = RM_BLE_ABS_CreateConnection,
    .setLocalPrivacy                = RM_BLE_ABS_SetLocalPrivacy,
    .startAuthentication            = RM_BLE_ABS_StartAuthentication,
};

static ble_abs_instance_ctrl_t * gp_instance_ctrl;

/***********************************************************************************************************************
 * Exported global functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Host stack is initialized with this function. Before using All the R_BLE APIs,
 * it's necessary to call this function. A callback functions are registered with this function.
 * In order to receive the GAP, GATT, Vendor specific event,
 * it's necessary to register a callback function.
 * The result of this API call is notified in BLE_GAP_EVENT_STACK_ON event.
 * Implements @ref ble_abs_api_t::open.
 *
 * Example:
 * @snippet rm_ble_abs_example.c RM_BLE_ABS_Open
 *
 * @retval FSP_SUCCESS                                 Channel opened successfully.
 * @retval FSP_ERR_ASSERTION                           Null pointer presented.
 * @retval FSP_ERR_INVALID_CHANNEL                     The channel number is invalid.
 * @retval FSP_ERR_ALREADY_OPEN                        Requested channel is already open in a different configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT                    Invalid input parameter.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_Open (ble_abs_ctrl_t * const p_ctrl, ble_abs_cfg_t const * const p_cfg)
{
    int32_t      i;
    fsp_err_t    err        = FSP_SUCCESS;
    ble_status_t ble_status = BLE_SUCCESS;

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);

    FSP_ASSERT(p_cfg->gap_callback);
    FSP_ERROR_RETURN(0 == p_cfg->channel, FSP_ERR_INVALID_CHANNEL);
#endif
    FSP_ERROR_RETURN(BLE_ABS_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    gp_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    (*p_instance_ctrl).abs_gap_callback             = NULL;
    (*p_instance_ctrl).abs_vendor_specific_callback = NULL;
    (*p_instance_ctrl).privacy_mode                 = BLE_GAP_NET_PRIV_MODE;
    (*p_instance_ctrl).set_privacy_status           = 0;
    (*p_instance_ctrl).p_cfg = p_cfg;

    R_BLE_Open();

    /* check pairing parameter */
    err = ble_abs_set_pairing_parameter(p_cfg->p_pairing_parameter);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_INVALID_ARGUMENT);

    /* initialize GAP layer */
    ble_status = R_BLE_GAP_Init(ble_abs_gap_callback);
    FSP_ERROR_RETURN(BLE_SUCCESS == ble_status, FSP_ERR_INVALID_ARGUMENT);

    for (i = 0; i < BLE_MAX_NO_OF_ADV_SETS_SUPPORTED; i++)
    {
        p_instance_ctrl->advertising_sets[i].advertising_status = 0;
    }

    p_instance_ctrl->abs_scan.scan_status      = 0;
    (*p_instance_ctrl).connection_timer_handle = BLE_TIMER_INVALID_HDL;
#if (BLE_CFG_LIBRARY_TYPE != 0)
    (*p_instance_ctrl).advertising_timer_handle = BLE_TIMER_INVALID_HDL;
#endif                                 /* (BLE_CFG_LIBRARY_TYPE != 0) */
    (*p_instance_ctrl).set_privacy_status = 0;

    /* set pairing parameter */
    ble_abs_set_pairing_parameter(p_cfg->p_pairing_parameter);
    ble_abs_set_abs_callback(p_instance_ctrl, p_cfg->gap_callback, p_cfg->vendor_specific_callback);

    if ((0 < p_cfg->gatt_server_callback_list_number) && (NULL != p_cfg->p_gatt_server_callback_list))
    {
        FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GATTS_Init(p_cfg->gatt_server_callback_list_number),
                         FSP_ERR_INVALID_ARGUMENT);

        for (i = 0; i < p_cfg->gatt_server_callback_list_number; i++)
        {
            if (NULL != p_cfg->p_gatt_server_callback_list[i].gatt_server_callback_function)
            {
                FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GATTS_RegisterCb(
                                     p_cfg->p_gatt_server_callback_list[i].gatt_server_callback_function,
                                     p_cfg->p_gatt_server_callback_list[i].gatt_server_callback_priority
                                     ),
                                 FSP_ERR_INVALID_ARGUMENT);
            }
            else
            {
                break;
            }
        }
    }

#if (BLE_CFG_LIBRARY_TYPE != 2)
    if ((0 < p_cfg->gatt_client_callback_list_number) && (NULL != p_cfg->p_gatt_client_callback_list))
    {
        FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GATTC_Init(p_cfg->gatt_client_callback_list_number),
                         FSP_ERR_INVALID_ARGUMENT);

        for (i = 0; i < p_cfg->gatt_client_callback_list_number; i++)
        {
            if (NULL != p_cfg->p_gatt_client_callback_list[i].gatt_client_callback_function)
            {
                FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_GATTC_RegisterCb(
                                     p_cfg->p_gatt_client_callback_list[i].gatt_client_callback_function,
                                     p_cfg->p_gatt_client_callback_list[i].gatt_client_callback_priority),
                                 FSP_ERR_INVALID_ARGUMENT);
            }
            else
            {
                break;
            }
        }
    }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE != 2) */

    FSP_ERROR_RETURN(BLE_SUCCESS == R_BLE_VS_Init(ble_abs_vendor_specific_callback), FSP_ERR_INVALID_ARGUMENT);

    ble_abs_timer_init(p_instance_ctrl);

    p_instance_ctrl->open = BLE_ABS_OPEN;

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_Open() */

/*******************************************************************************************************************//**
 * @brief Close the BLE channel.
 * Implements @ref ble_abs_api_t::close.
 *
 * Example:
 * @snippet rm_ble_abs_example.c RM_BLE_ABS_Close
 *
 * @retval  FSP_SUCCESS              Channel closed successfully.
 * @retval  FSP_ERR_ASSERTION        Null pointer presented.
 * @retval  FSP_ERR_NOT_OPEN         Control block not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_Close (ble_abs_ctrl_t * const p_ctrl)
{
    ble_abs_instance_ctrl_t * p_ble_abs_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ble_abs_ctrl);
#endif
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_ble_abs_ctrl->open, FSP_ERR_NOT_OPEN);

    R_BLE_Close();

    R_BLE_GAP_Terminate();

    ble_abs_timer_terminate(p_ble_abs_ctrl);

    p_ble_abs_ctrl->open = 0;

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_Close() */

/*******************************************************************************************************************//**
 * BLE is reset with this function.  The process is carried out in the following order.
 * R_BLE_Close() -> R_BLE_GAP_Terminate() -> R_BLE_Open() -> R_BLE_SetEvent().
 * The init_cb callback initializes the others (Host Stack, timer, etc...).
 * Implements @ref ble_abs_api_t::reset.
 *
 * @retval  FSP_SUCCESS              Channel closed successfully.
 * @retval  FSP_ERR_ASSERTION        Null pointer presented.
 * @retval  FSP_ERR_NOT_OPEN         Control block not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_Reset (ble_abs_ctrl_t * const p_ctrl, ble_event_cb_t init_callback)
{
    ble_abs_instance_ctrl_t * p_ble_abs_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ble_abs_ctrl);
#endif
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_ble_abs_ctrl->open, FSP_ERR_NOT_OPEN);

    R_BLE_Close();

    R_BLE_GAP_Terminate();

    R_BLE_Open();

    if (NULL != init_callback)
    {
        R_BLE_SetEvent(init_callback);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get BLE module code and API versions.
 * Implements @ref ble_abs_api_t::versionGet.
 *
 * @retval      FSP_SUCCESS            Operation succeeded.
 * @retval      FSP_ERR_ASSERTION      The parameter p_version is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_VersionGet (fsp_version_t * const p_version)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_version);
#endif

    p_version->version_id = g_ble_abs_version.version_id;

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_VersionGet() */

/*******************************************************************************************************************//**
 * Start Legacy Advertising after setting advertising parameters, advertising data and scan response data.
 * The legacy advertising uses the advertising set whose advertising handle is 0.
 * The advertising type is connectable and scannable(ADV_IND).
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Implements @ref ble_abs_api_t::startLegacyAdvertising
 *
 * Example:
 * @snippet rm_ble_abs_example.c RM_BLE_ABS_StartLegacyAdvertising
 *
 * @retval FSP_SUCCESS                                 Operation succeeded
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_STATE                       Host stack hasn't been initialized.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartLegacyAdvertising (ble_abs_ctrl_t * const                               p_ctrl,
                                             ble_abs_legacy_advertising_parameter_t const * const p_advertising_parameter)
{
    st_ble_gap_adv_param_t    advertising_parameter;
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

#if (BLE_CFG_LIBRARY_TYPE == 0)
    uint8_t advertising_handle = BLE_ABS_LEGACY_HDL;
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    uint8_t advertising_handle = BLE_ABS_COMMON_HDL;
#endif /* (BLE_CFG_LIBRARY_TYPE != 0) */

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
#endif

    /** status check */
    FSP_ERROR_RETURN(0 == (p_instance_ctrl->advertising_sets[advertising_handle].advertising_status &
                           (BLE_ABS_ADV_STATUS_ADV_FAST_START | BLE_ABS_ADV_STATUS_ADV_SLOW_START)),
                     FSP_ERR_INVALID_STATE);

#if (BLE_CFG_LIBRARY_TYPE == 0)
    ble_abs_set_advertising_status(p_instance_ctrl,
                                   advertising_handle,
                                   0,
                                   (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW));
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    ble_abs_set_advertising_status(p_instance_ctrl,
                                   advertising_handle,
                                   0,
                                   (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW |
                                    BLE_ABS_ADV_COMM_LEG | BLE_ABS_ADV_COMM_NON));
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     ble_abs_convert_legacy_advertising_parameter((ble_abs_legacy_advertising_parameter_t *)
                                                                  p_advertising_parameter,
                                                                  &advertising_parameter),
                     FSP_ERR_INVALID_ARGUMENT);

    /** check data length */
    FSP_ERROR_RETURN((BLE_ABS_LEGACY_ADV_DATA_LEN >= p_advertising_parameter->advertising_data_length) &&
                     (BLE_ABS_LEGACY_ADV_DATA_LEN >= p_advertising_parameter->scan_response_data_length),
                     FSP_ERR_INVALID_ARGUMENT);

    ble_abs_set_connection_advertising_interval(&advertising_parameter,
                                                p_advertising_parameter->fast_advertising_interval,
                                                p_advertising_parameter->slow_advertising_interval,
                                                p_advertising_parameter->fast_advertising_period); ///< check advertising interval

    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_ADV_DATA,
                               p_advertising_parameter->p_advertising_data,
                               p_advertising_parameter->advertising_data_length,
                               advertising_handle); ///< advertising data update check

    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_SRES_DATA,
                               p_advertising_parameter->p_scan_response_data,
                               p_advertising_parameter->scan_response_data_length,
                               advertising_handle); ///< scan response data update check

    ble_abs_set_advertising_parameter(p_instance_ctrl,
                                      (ble_abs_legacy_advertising_parameter_t *) p_advertising_parameter,
                                      BLE_ABS_LEGACY_HDL);

    FSP_ERROR_RETURN(FSP_SUCCESS == R_BLE_GAP_SetAdvParam(&advertising_parameter), FSP_ERR_INVALID_ARGUMENT);

#if (BLE_CFG_LIBRARY_TYPE == 0)
    uint32_t status =
        p_advertising_parameter->fast_advertising_period ? BLE_ABS_ADV_STATUS_PARAM_FAST : BLE_ABS_ADV_STATUS_PARAM_SLOW;
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    uint32_t status =
        p_advertising_parameter->fast_advertising_period ? (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_COMM_LEG) :
        (BLE_ABS_ADV_STATUS_PARAM_SLOW | BLE_ABS_ADV_COMM_LEG);
#endif /* (BLE_CFG_LIBRARY_TYPE == 0) */
    ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, status, 0);

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_StartLegacyAdvertising() */

/*******************************************************************************************************************//**
 * Start Extended Advertising after setting advertising parameters, advertising data.
 * The extended advertising uses the advertising set whose advertising handle is 1.
 * The advertising type is connectable and non-scannable.
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Implements @ref ble_abs_api_t::startExtendedAdvertising
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_STATE                       Host stack hasn't been initialized.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 * @retval FSP_ERR_UNSUPPORTED                         Subordinate modules do not support this feature.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartExtendedAdvertising (ble_abs_ctrl_t * const                               p_ctrl,
                                               ble_abs_extend_advertising_parameter_t const * const p_advertising_parameter)
{
#if (BLE_CFG_LIBRARY_TYPE == 0)
    st_ble_gap_adv_param_t advertising_parameter;

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
 #if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /** status check */
    FSP_ERROR_RETURN(0 == (p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_status &
                           (BLE_ABS_ADV_STATUS_ADV_FAST_START | BLE_ABS_ADV_STATUS_ADV_SLOW_START)),
                     FSP_ERR_INVALID_STATE);

    ble_abs_set_advertising_status(p_instance_ctrl,
                                   BLE_ABS_EXT_HDL,
                                   0,
                                   (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW));

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     ble_abs_convert_extend_advertising_parameter((ble_abs_extend_advertising_parameter_t *)
                                                                  p_advertising_parameter,
                                                                  &advertising_parameter),
                     FSP_ERR_INVALID_ARGUMENT);

    FSP_ERROR_RETURN(BLE_ABS_CONN_EXT_ADV_DATA_LEN >= p_advertising_parameter->advertising_data_length,
                     FSP_ERR_INVALID_ARGUMENT); ///< check data length

    ble_abs_set_connection_advertising_interval(&advertising_parameter,
                                                p_advertising_parameter->fast_advertising_interval,
                                                p_advertising_parameter->slow_advertising_interval,
                                                p_advertising_parameter->fast_advertising_period); ///< check advertising interval

    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_ADV_DATA,
                               p_advertising_parameter->p_advertising_data,
                               p_advertising_parameter->advertising_data_length,
                               BLE_ABS_EXT_HDL); ///< data update check

    ble_abs_set_advertising_parameter(p_instance_ctrl,
                                      (ble_abs_extend_advertising_parameter_t *) p_advertising_parameter,
                                      BLE_ABS_EXT_HDL);

    FSP_ERROR_RETURN(FSP_SUCCESS == R_BLE_GAP_SetAdvParam(&advertising_parameter), FSP_ERR_INVALID_ARGUMENT);

    uint32_t status =
        p_advertising_parameter->fast_advertising_period ? BLE_ABS_ADV_STATUS_PARAM_FAST : BLE_ABS_ADV_STATUS_PARAM_SLOW;
    ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_EXT_HDL, status, 0);

    return FSP_SUCCESS;
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    return FSP_ERR_UNSUPPORTED;
#endif /* (BLE_CFG_LIBRARY_TYPE == 0) */
}                                      /* End of function RM_BLE_ABS_StartExtendedAdvertising() */

/*******************************************************************************************************************//**
 * Start Non-Connectable Advertising after setting advertising parameters, advertising data.
 * The non-connectable advertising uses the advertising set whose advertising handle is 2.
 * The advertising type is non-connectable and non-scannable.
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Secondary Advertising Max Skip is 0.
 * Implements @ref ble_abs_api_t::startNonConnectableAdvertising.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_STATE                       Host stack hasn't been initialized.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartNonConnectableAdvertising (
    ble_abs_ctrl_t * const                                        p_ctrl,
    ble_abs_non_connectable_advertising_parameter_t const * const p_advertising_parameter)
{
    st_ble_gap_adv_param_t advertising_parameter;

#if (BLE_CFG_LIBRARY_TYPE == 0)
    uint8_t advertising_handle = BLE_ABS_NON_CONN_HDL;
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    uint8_t advertising_handle = BLE_ABS_COMMON_HDL;
#endif /* (BLE_CFG_LIBRARY_TYPE == 0) */

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /** status check */
    FSP_ERROR_RETURN(0 == (p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_status &
                           (BLE_ABS_ADV_STATUS_ADV_FAST_START | BLE_ABS_ADV_STATUS_ADV_SLOW_START)),
                     FSP_ERR_INVALID_STATE);

#if (BLE_CFG_LIBRARY_TYPE == 0)
    ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, 0, BLE_ABS_ADV_STATUS_PARAM_SLOW);
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    ble_abs_set_advertising_status(p_instance_ctrl,
                                   advertising_handle,
                                   0,
                                   (BLE_ABS_ADV_STATUS_PARAM_SLOW |
                                    BLE_ABS_ADV_COMM_LEG | BLE_ABS_ADV_COMM_NON));
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     ble_abs_convert_non_connectable_advertising_parameter((
                                                                               ble_abs_non_connectable_advertising_parameter_t
                                                                               *)
                                                                           p_advertising_parameter,
                                                                           &advertising_parameter,
                                                                           advertising_handle),
                     FSP_ERR_INVALID_ARGUMENT);

    advertising_parameter.adv_intv_min = p_advertising_parameter->advertising_interval;
    advertising_parameter.adv_intv_max = p_advertising_parameter->advertising_interval;

    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_ADV_DATA,
                               p_advertising_parameter->p_advertising_data,
                               p_advertising_parameter->advertising_data_length,
                               advertising_handle); ///< data update check

    ble_abs_set_advertising_parameter(p_instance_ctrl,
                                      (ble_abs_non_connectable_advertising_parameter_t *) p_advertising_parameter,
                                      BLE_ABS_NON_CONN_HDL);

    FSP_ERROR_RETURN(FSP_SUCCESS == R_BLE_GAP_SetAdvParam(&advertising_parameter), FSP_ERR_INVALID_ARGUMENT);

#if (BLE_CFG_LIBRARY_TYPE == 0)
    ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, BLE_ABS_ADV_STATUS_PARAM_SLOW, 0);
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    ble_abs_set_advertising_status(p_instance_ctrl,
                                   advertising_handle,
                                   (BLE_ABS_ADV_STATUS_PARAM_SLOW | BLE_ABS_ADV_COMM_NON),
                                   0);
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

    return FSP_SUCCESS;
} /* End of function RM_BLE_ABS_StartNonConnectableAdvertising() */

/*******************************************************************************************************************//**
 * Start Periodic Advertising after setting advertising parameters, periodic advertising parameters,
 * advertising data and periodic advertising data.
 * The periodic advertising uses the advertising set whose advertising handle is 3.
 * The advertising type is non-connectable and non-scannable.
 * The address type of local device is Public Identity Address or
 * RPA(If the resolving list contains no matching entry, use the public address.).
 * Scan request event(BLE_GAP_EVENT_SCAN_REQ_RECV) is not notified.
 * Secondary Advertising Max Skip is 0.
 * Implements @ref ble_abs_api_t::startPeriodicAdvertising
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_advertising_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 * @retval FSP_ERR_UNSUPPORTED                         Subordinate modules do not support this feature.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartPeriodicAdvertising (ble_abs_ctrl_t * const                                 p_ctrl,
                                               ble_abs_periodic_advertising_parameter_t const * const p_advertising_parameter)
{
#if (BLE_CFG_LIBRARY_TYPE == 0)
    st_ble_gap_adv_param_t advertising_parameter;

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
 #if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_advertising_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /** status check */
    FSP_ASSERT(!(p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_status &
                 (BLE_ABS_ADV_STATUS_ADV_SLOW_START | BLE_ABS_ADV_STATUS_PERD_START)));

    ble_abs_set_advertising_status(p_instance_ctrl,
                                   BLE_ABS_PERD_HDL,
                                   0,
                                   (BLE_ABS_ADV_STATUS_PARAM_SLOW | BLE_ABS_ADV_STATUS_PERD_PARAM));

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     ble_abs_convert_non_connectable_advertising_parameter((
                                                                               ble_abs_non_connectable_advertising_parameter_t
                                                                               *) (&
                                                                                   p_advertising_parameter
                                                                                   ->
                                                                                   advertising_parameter),
                                                                           &advertising_parameter,
                                                                           BLE_ABS_PERD_HDL),
                     FSP_ERR_INVALID_ARGUMENT);

    advertising_parameter.adv_intv_min = p_advertising_parameter->advertising_parameter.advertising_interval;
    advertising_parameter.adv_intv_max = p_advertising_parameter->advertising_parameter.advertising_interval;

    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_ADV_DATA,
                               p_advertising_parameter->advertising_parameter.p_advertising_data,
                               p_advertising_parameter->advertising_parameter.advertising_data_length,
                               BLE_ABS_PERD_HDL); ///< advertising data update check

    ble_abs_update_data_status(p_instance_ctrl,
                               BLE_ABS_ADV_STATUS_PERD_DATA,
                               p_advertising_parameter->p_periodic_advertising_data,
                               p_advertising_parameter->periodic_advertising_data_length,
                               BLE_ABS_PERD_HDL); ///< periodic advertising data update check

    ble_abs_set_advertising_parameter(p_instance_ctrl,
                                      (ble_abs_periodic_advertising_parameter_t *) p_advertising_parameter,
                                      BLE_ABS_PERD_HDL);

    FSP_ERROR_RETURN(FSP_SUCCESS == R_BLE_GAP_SetAdvParam(&advertising_parameter), FSP_ERR_INVALID_ARGUMENT);

    ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_PERD_HDL, BLE_ABS_ADV_STATUS_PARAM_SLOW, 0);

    return FSP_SUCCESS;
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    return FSP_ERR_UNSUPPORTED;
#endif /* (BLE_CFG_LIBRARY_TYPE == 0) */
}                                      /* End of function RM_BLE_ABS_StartPeriodicAdvertising() */

/*******************************************************************************************************************//**
 * Start scanning after setting scan parameters.
 * The scanner address type is Public Identity Address.
 * Fast scan is followed by slow scan.
 * The end of fast scan or slow scan is notified with BLE_GAP_EVENT_SCAN_TO event.
 * If fast_period is 0, only slow scan is carried out.
 * If scan_period is 0, slow scan continues.
 * Implements @ref ble_abs_api_t::startScanning.
 *
 * Example:
 * @snippet rm_ble_abs_example.c RM_BLE_ABS_StartScanning
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_scan_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The scan parameter is out of range.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartScanning (ble_abs_ctrl_t * const                 p_ctrl,
                                    ble_abs_scan_parameter_t const * const p_scan_parameter)
{
    st_ble_gap_scan_param_t     gap_scan_parameter;
    st_ble_gap_scan_phy_param_t phy_parameter_1M;
    st_ble_gap_scan_phy_param_t phy_parameter_coded;
    ble_gap_scan_on_t           gap_scan_enable;

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_scan_parameter, FSP_ERR_INVALID_POINTER);
#endif

    gap_scan_parameter.p_phy_param_1M    = p_scan_parameter->p_phy_parameter_1M ? &phy_parameter_1M : NULL;       ///< set scan phy parameter for 1M
    gap_scan_parameter.p_phy_param_coded = p_scan_parameter->p_phy_parameter_coded ? &phy_parameter_coded : NULL; ///< set scan phy parameter for coded

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     ble_abs_set_scan_parameter(p_instance_ctrl, (ble_abs_scan_parameter_t *) p_scan_parameter),
                     FSP_ERR_INVALID_ARGUMENT);                                                                   ///< scan parameter check

    ble_abs_convert_scan_parameter(p_instance_ctrl,
                                   &gap_scan_parameter,
                                   &gap_scan_enable,
                                   BLE_ABS_SCAN_STATUS_FAST_START);

    FSP_ERROR_RETURN(FSP_SUCCESS == R_BLE_GAP_StartScan(&gap_scan_parameter,
                                                        (st_ble_gap_scan_on_t *) (&gap_scan_enable)),
                     FSP_ERR_INVALID_ARGUMENT);
    if (0 == p_scan_parameter->fast_scan_period)
    {
        ble_abs_set_scan_status(p_instance_ctrl, BLE_ABS_SCAN_STATUS_SLOW_START, 0);
    }
    else
    {
        ble_abs_set_scan_status(p_instance_ctrl, BLE_ABS_SCAN_STATUS_FAST_START, 0);
    }

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_StartScanning() */

/*******************************************************************************************************************//**
 * Generate a IRK, add it to the resolving list, set privacy mode and enable RPA function.
 * Register vendor specific callback function, if IRK is generated by this function.
 * After configuring local device privacy,
 * BLE_GAP_ADDR_RPA_ID_PUBLIC is specified as own device address
 * in theadvertising/scan/create connection API.
 * Implements @ref ble_abs_api_t::setLocalPrivacy
 *
 * Example:
 * @snippet rm_ble_abs_example.c RM_BLE_ABS_SetLocalPrivacy
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The privacy_mode parameter is out of range.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Host stack hasn't been initialized.
 *                                                     configuring the resolving list or privacy mode.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_SetLocalPrivacy (ble_abs_ctrl_t * const p_ctrl,
                                      uint8_t const * const  p_lc_irk,
                                      uint8_t                privacy_mode)
{
    ble_status_t ble_status = BLE_SUCCESS;

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BLE_GAP_DEV_PRIV_MODE >= privacy_mode, FSP_ERR_INVALID_ARGUMENT);
#endif

    if (NULL == p_lc_irk)
    {
        ble_status = R_BLE_VS_GetRand(BLE_GAP_IRK_SIZE);
        p_instance_ctrl->set_privacy_status = (BLE_SUCCESS == ble_status) ? BLE_ABS_PV_STATUS_CREATE_IRK : 0;
    }
    else
    {
        ble_abs_set_irk_to_resolving_list(p_instance_ctrl, (uint8_t *) p_lc_irk);
        FSP_ERROR_RETURN(0 != p_instance_ctrl->set_privacy_status, FSP_ERR_BLE_ABS_INVALID_OPERATION);
    }

    p_instance_ctrl->privacy_mode = privacy_mode;

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_SetLocalPrivacy() */

/*******************************************************************************************************************//**
 * Request create connection.
 * The initiator address type is Public Identity Address.
 * The scan interval is 60ms and the scan window is 30ms in case of 1M PHY or 2M PHY.
 * The scan interval is 180ms and the scan window is 90ms in case of coded PHY.
 * The Minimum CE Length and the Maximum CE Length are 0xFFFF.
 * When the request for a connection has been received by the Controller,
 * BLE_GAP_EVENT_CREATE_CONN_COMP event is notified.
 * When a link has beens established, BLE_GAP_EVENT_CONN_IND event is notified.
 * Implements @ref ble_abs_api_t::createConnection.
 *
 * Example:
 * @snippet rm_ble_abs_example.c RM_BLE_ABS_CreateConnection
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl is specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_POINTER                     p_connection_parameter is specified as NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The create connection parameter is out of range.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                   Couldn't find a valid timer.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Invalid operation for the selected timer.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_CreateConnection (ble_abs_ctrl_t * const                       p_ctrl,
                                       ble_abs_connection_parameter_t const * const p_connection_parameter)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_connection_parameter, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(10 >= p_connection_parameter->connection_timeout, FSP_ERR_INVALID_ARGUMENT);
#endif

    st_ble_gap_create_conn_param_t connection_parameter;
    fsp_err_t ret = FSP_SUCCESS;
    connection_parameter.init_filter_policy = p_connection_parameter->filter_parameter;
    connection_parameter.own_addr_type      = BLE_GAP_ADDR_PUBLIC;

    if (BLE_GAP_INIT_FILT_USE_ADDR == p_connection_parameter->filter_parameter)
    {
        memcpy(connection_parameter.remote_bd_addr, p_connection_parameter->p_device_address->addr, BLE_BD_ADDR_LEN);
        connection_parameter.remote_bd_addr_type = p_connection_parameter->p_device_address->type;
    }
    else
    {
        connection_parameter.remote_bd_addr_type = BLE_GAP_ADDR_PUBLIC;
    }

    /** set connection parameters for 1M */
    ble_gap_connection_parameter_t     connection_parameter_1M;    ///< connection parameter for 1M
    ble_gap_connection_phy_parameter_t connection_phy_1M;          ///< connection phy for 1M
    ble_abs_set_connection_parameter(p_connection_parameter->p_connection_phy_parameter_1M,
                                     &connection_phy_1M,
                                     &connection_parameter_1M);    ///< select connection parameters for 1M
    connection_parameter.p_conn_param_1M =
        p_connection_parameter->p_connection_phy_parameter_1M ? (st_ble_gap_conn_phy_param_t *) (&connection_phy_1M) :
        NULL;                                                      ///< set connection parameters for 1M

    /** set connection parameters for 2M */
    ble_gap_connection_parameter_t     connection_parameter_2M;    ///< connection parameter for 2M
    ble_gap_connection_phy_parameter_t connection_phy_2M;          ///< connection phy for 2M
    ble_abs_set_connection_parameter(p_connection_parameter->p_connection_phy_parameter_2M,
                                     &connection_phy_2M,
                                     &connection_parameter_2M);    ///< select connection parameters for 2M
    connection_parameter.p_conn_param_2M =
        p_connection_parameter->p_connection_phy_parameter_2M ? (st_ble_gap_conn_phy_param_t *) (&connection_phy_2M) :
        NULL;                                                      ///< set connection parameters for 2M

    /** set connection parameters for coded */
    ble_gap_connection_parameter_t     connection_parameter_coded; ///< connection parameter for coded
    ble_gap_connection_phy_parameter_t connection_phy_coded;       ///< connection phy for coded
    ble_abs_set_connection_parameter(p_connection_parameter->p_connection_phy_parameter_coded,
                                     &connection_phy_coded,
                                     &connection_parameter_coded); ///< select connection parameters for coded
    connection_parameter.p_conn_param_coded =
        p_connection_parameter->p_connection_phy_parameter_coded ? (st_ble_gap_conn_phy_param_t *) (&
                                                                                                    connection_phy_coded)
        :
        NULL;                          ///< set connection parameters for coded
    if (NULL != p_connection_parameter->p_connection_phy_parameter_coded)
    {
        connection_phy_coded.scan_intv   = BLE_ABS_CONN_SC_INTV_SLOW;
        connection_phy_coded.scan_window = BLE_ABS_CONN_SC_WINDOW_SLOW;
    }

    /** create timer for cancel */
    if (0 != p_connection_parameter->connection_timeout)
    {
        ble_abs_timer_create(p_instance_ctrl,
                             &p_instance_ctrl->connection_timer_handle,
                             (uint32_t) (p_connection_parameter->connection_timeout *
                                         BLE_ABS_GAP_EVENT_CONNECTION_TIMEOUT_1000),
                             BLE_TIMER_ONE_SHOT,
                             (ble_abs_timer_cb_t) ble_abs_cancel_connection_function);
    }

    ble_status_t retval = BLE_SUCCESS;
    retval = R_BLE_GAP_CreateConn(&connection_parameter); ///< create connection
    if (0 != p_connection_parameter->connection_timeout)
    {
        if (BLE_SUCCESS == retval)
        {
            ret = ble_abs_timer_start(p_instance_ctrl, p_instance_ctrl->connection_timer_handle);
        }
        else
        {
            ret = ble_abs_timer_delete(p_instance_ctrl, &p_instance_ctrl->connection_timer_handle);
        }
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, ret);

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_CreateConnection() */

/*******************************************************************************************************************//**
 * Start pairing or encryption. If pairing has been done, start encryption.
 * The pairing parameters are configured by RM_BLE_ABS_Open() or R_BLE_GAP_SetPairingParams().
 * If the pairing parameters are configure by RM_BLE_ABS_Open(),
 *    - bonding policy is that bonding information is stored.
 *    - Key press notification is not supported.
 * Implements @ref ble_abs_api_t::startAuthentication.
 *
 * Example:
 * @snippet rm_ble_abs_example.c RM_BLE_ABS_StartAuthentication
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           p_instance_ctrl or connection_handle are specified as NULL.
 * @retval FSP_ERR_NOT_OPEN                            Control block not open.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The connection handle parameter is out of range.
 **********************************************************************************************************************/
fsp_err_t RM_BLE_ABS_StartAuthentication (ble_abs_ctrl_t * const p_ctrl, uint16_t connection_handle)
{
    st_ble_gap_auth_info_t security_information;
    ble_status_t           retval;

    ble_abs_instance_ctrl_t * p_instance_ctrl = (ble_abs_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(BLE_ABS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    retval = R_BLE_GAP_GetDevSecInfo(connection_handle, &security_information); ///< check security information
    if (BLE_SUCCESS == retval)
    {
        retval = R_BLE_GAP_StartEnc(connection_handle);
    }
    else
    {
        retval = R_BLE_GAP_StartPairing(connection_handle);
    }

    FSP_ERROR_RETURN(BLE_ERR_INVALID_HDL != retval, FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}                                      /* End of function RM_BLE_ABS_StartAuthentication() */

/************************************************
 *   static function definitions                *
 ***********************************************/

/*******************************************************************************************************************//**
 * Set Abstraction API connection parameters to GAP connection parameters.
 **********************************************************************************************************************/
static void ble_abs_set_connection_parameter (ble_abs_connection_phy_parameter_t * p_abs_connection_parameter,
                                              ble_gap_connection_phy_parameter_t * p_connection_phy_parameter,
                                              ble_gap_connection_parameter_t     * p_connection_parameter)
{
    if (NULL != p_abs_connection_parameter)
    {
        p_connection_parameter->conn_intv_min    = p_abs_connection_parameter->connection_interval;
        p_connection_parameter->conn_intv_max    = p_abs_connection_parameter->connection_interval;
        p_connection_parameter->conn_latency     = p_abs_connection_parameter->connection_slave_latency;
        p_connection_parameter->sup_to           = p_abs_connection_parameter->supervision_timeout;
        p_connection_parameter->min_ce_length    = BLE_ABS_GAP_CONNECTION_CE_LENGTH;
        p_connection_parameter->max_ce_length    = BLE_ABS_GAP_CONNECTION_CE_LENGTH;
        p_connection_phy_parameter->scan_intv    = BLE_ABS_CONN_SC_INTV_FAST;
        p_connection_phy_parameter->scan_window  = BLE_ABS_CONN_SC_WINDOW_FAST;
        p_connection_phy_parameter->p_conn_param = p_connection_parameter;
    }
}                                      /* End of function ble_abs_set_connection_parameter() */

/*******************************************************************************************************************//**
 * Set pairing parameters.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_ASSERTION                           parameter is NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The pairing parameter is out of range.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_set_pairing_parameter (ble_abs_pairing_parameter_t * p_pairing_parameter)
{
    FSP_ASSERT(p_pairing_parameter);

    st_ble_gap_pairing_param_t pairing_parameter;

    pairing_parameter.iocap         = p_pairing_parameter->io_capabilitie_local_device;
    pairing_parameter.mitm          = p_pairing_parameter->mitm_protection_policy;
    pairing_parameter.bonding       = BLE_GAP_BONDING;
    pairing_parameter.max_key_size  = BLE_ABS_SET_PAIRING_MAXIMUM_LTK_SIZE;
    pairing_parameter.min_key_size  = p_pairing_parameter->maximum_key_size;
    pairing_parameter.loc_key_dist  = p_pairing_parameter->local_key_distribute;
    pairing_parameter.rem_key_dist  = p_pairing_parameter->remote_key_distribute;
    pairing_parameter.key_notf      = BLE_GAP_SC_KEY_PRESS_NTF_NOT_SPRT;
    pairing_parameter.sec_conn_only = p_pairing_parameter->secure_connection_only;

    FSP_ERROR_RETURN(FSP_SUCCESS == R_BLE_GAP_SetPairingParams(&pairing_parameter), FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_set_pairing_parameter() */

#if (BLE_CFG_LIBRARY_TYPE != 0)

/*******************************************************************************************************************//**
 * Advertising timer handler for legacy advertising.
 **********************************************************************************************************************/
static void ble_abs_advertising_to_function (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_handle)
{
    R_BLE_GAP_StopAdv(BLE_ABS_COMMON_HDL);
    ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_COMMON_HDL, BLE_ABS_ADV_COMM_TO, 0);
}                                      /* End of function ble_abs_advertising_to_function() */

#endif /* (BLE_CFG_LIBRARY_TYPE != 0) */

/*******************************************************************************************************************//**
 * Cancel a request for connection.
 **********************************************************************************************************************/
static void ble_abs_cancel_connection_function (void)
{
    R_BLE_GAP_CancelCreateConn();
}                                      /* End of function ble_abs_cancel_connection_function() */

/*******************************************************************************************************************//**
 * Configure scan response data and start legacy advertising.
 **********************************************************************************************************************/
static void ble_abs_set_legacy_scan_response_data (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    if ((p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.legacy_advertising_parameter.
         scan_response_data_length) &&
        (p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.legacy_advertising_parameter.
         p_scan_response_data))
    {
        if (p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_status & BLE_ABS_ADV_STATUS_SRES_DATA)
        {
            ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_LEGACY_HDL);
        }
        else
        {
            ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_LEGACY_HDL, BLE_GAP_SCAN_RSP_DATA_MODE);
        }
    }
    else
    {
        ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_LEGACY_HDL);
    }
}                                      /* End of function ble_abs_set_legacy_scan_response_data() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_ADV_PARAM_SET_COMP event.
 **********************************************************************************************************************/
void ble_abs_advertising_parameter_set_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                st_ble_evt_data_t             * p_event_data)
{
#if (BLE_CFG_LIBRARY_TYPE == 0)
    st_ble_gap_adv_set_evt_t * p_advertising_set_parameter;
    p_advertising_set_parameter = (st_ble_gap_adv_set_evt_t *) p_event_data->p_param;

    switch (p_advertising_set_parameter->adv_hdl)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            if ((p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_status &
                 (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW)))
            {
                if ((p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                     legacy_advertising_parameter.advertising_data_length) &&
                    (p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                     legacy_advertising_parameter.p_advertising_data))
                {
                    if (p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_status &
                        BLE_ABS_ADV_STATUS_ADV_DATA)
                    {
                        ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
                    }
                    else
                    {
                        ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_LEGACY_HDL, BLE_GAP_ADV_DATA_MODE);
                    }
                }
                else
                {
                    ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
                }
            }

            break;
        }

        case BLE_ABS_EXT_HDL:
        {
            if ((p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_status &
                 (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW)))
            {
                if ((p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_parameter.
                     extend_advertising_parameter.advertising_data_length) &&
                    (p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_parameter.
                     extend_advertising_parameter.p_advertising_data))
                {
                    if (p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_status &
                        BLE_ABS_ADV_STATUS_ADV_DATA)
                    {
                        ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_EXT_HDL);
                    }
                    else
                    {
                        ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_EXT_HDL, BLE_GAP_ADV_DATA_MODE);
                    }
                }
                else
                {
                    ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_EXT_HDL);
                }
            }

            break;
        }

        case BLE_ABS_NON_CONN_HDL:
        {
            if (p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_status &
                BLE_ABS_ADV_STATUS_PARAM_SLOW)
            {
                if ((p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_parameter.
                     non_connectable_advertising_parameter.advertising_data_length) &&
                    (p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_parameter.
                     non_connectable_advertising_parameter.p_advertising_data))
                {
                    ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_NON_CONN_HDL, BLE_GAP_ADV_DATA_MODE);
                }
                else
                {
                    ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_NON_CONN_HDL);
                }
            }

            break;
        }

        default /* BLE_ABS_PERD_HDL */:
        {
            if (p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_status & BLE_ABS_ADV_STATUS_PARAM_SLOW)
            {
                st_ble_gap_perd_adv_param_t periodic_parameter;
                periodic_parameter.adv_hdl       = BLE_ABS_PERD_HDL;
                periodic_parameter.prop_type     = 0x0000;
                periodic_parameter.perd_intv_min =
                    p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.
                    periodic_advertising_parameter
                    .periodic_advertising_interval;
                periodic_parameter.perd_intv_max = periodic_parameter.perd_intv_min;
                R_BLE_GAP_SetPerdAdvParam(&periodic_parameter);
                ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_PERD_HDL, BLE_ABS_ADV_STATUS_PERD_PARAM, 0);
            }

            break;
        }
    }

#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    if (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status & BLE_ABS_ADV_COMM_LEG)
    {
        if ((p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status &
             (BLE_ABS_ADV_STATUS_PARAM_FAST | BLE_ABS_ADV_STATUS_PARAM_SLOW)))
        {
            if ((p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                 legacy_advertising_parameter.advertising_data_length) &&
                (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                 legacy_advertising_parameter.p_advertising_data))
            {
                if (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status &
                    BLE_ABS_ADV_STATUS_ADV_DATA)
                {
                    ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
                }
                else
                {
                    ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_COMMON_HDL, BLE_GAP_ADV_DATA_MODE);
                }
            }
            else
            {
                ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
            }
        }
    }
    else
    {
        if (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status & BLE_ABS_ADV_STATUS_PARAM_SLOW)
        {
            if ((p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                 non_connectable_advertising_parameter.advertising_data_length) &&
                (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                 non_connectable_advertising_parameter.p_advertising_data))
            {
                ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_COMMON_HDL, BLE_GAP_ADV_DATA_MODE);
            }
            else
            {
                ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_NON_CONN_HDL);
            }
        }
    }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
} /* End of function ble_abs_advertising_parameter_set_handler() */

/*******************************************************************************************************************//**
 * Start advertising.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_advertising_start (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint8_t advertising_handle)
{
    ble_status_t retval = BLE_SUCCESS;

    uint32_t status = 0;

#if (BLE_CFG_LIBRARY_TYPE == 0)
    uint16_t fast_period = (uint16_t) ((BLE_ABS_LEGACY_HDL == advertising_handle) ?
                                       p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                                       legacy_advertising_parameter.fast_advertising_period :
                                       (BLE_ABS_EXT_HDL == advertising_handle) ?
                                       p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_parameter.
                                       extend_advertising_parameter.fast_advertising_period :
                                       0x0000);
    uint16_t slow_period = (uint16_t) ((BLE_ABS_LEGACY_HDL == advertising_handle) ?
                                       p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                                       legacy_advertising_parameter.slow_advertising_period :
                                       (BLE_ABS_EXT_HDL == advertising_handle) ?
                                       p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_parameter.
                                       extend_advertising_parameter.slow_advertising_period :
                                       (BLE_ABS_NON_CONN_HDL == advertising_handle) ?
                                       p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_parameter.
                                       non_connectable_advertising_parameter.advertising_duration :
                                       p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.
                                       periodic_advertising_parameter.advertising_parameter.advertising_duration);
#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    uint16_t fast_period =
        p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.legacy_advertising_parameter.
        fast_advertising_period;
    uint16_t slow_period =
        (uint16_t) ((0 !=
                     (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status &
                      BLE_ABS_ADV_COMM_LEG)) ?
                    p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                    legacy_advertising_parameter.slow_advertising_period :
                    p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                    non_connectable_advertising_parameter.advertising_duration);
    uint32_t to = slow_period;
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

    if (0x0000 == fast_period)
    {
#if (BLE_CFG_LIBRARY_TYPE == 0)
        if ((BLE_ABS_PERD_HDL == advertising_handle) &&
            (!(p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_status & BLE_ABS_ADV_STATUS_PERD_START)))
        {
            retval = R_BLE_GAP_StartPerdAdv(BLE_ABS_PERD_HDL);
            status = BLE_ABS_ADV_STATUS_PERD_START;
        }
        else
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
        {
            retval = R_BLE_GAP_StartAdv(advertising_handle, slow_period, 0x0000);
            status = BLE_ABS_ADV_STATUS_ADV_SLOW_START;
        }
    }
    else
    {
        if (p_instance_ctrl->advertising_sets[advertising_handle].advertising_status & BLE_ABS_ADV_STATUS_PARAM_SLOW)
        {
            retval = R_BLE_GAP_StartAdv(advertising_handle, slow_period, 0x0000);
            status = BLE_ABS_ADV_STATUS_ADV_SLOW_START;
        }
        else
        {
#if (BLE_CFG_LIBRARY_TYPE != 0)
            to = fast_period;
#endif                                 /* (BLE_CFG_LIBRARY_TYPE != 0) */
            retval = R_BLE_GAP_StartAdv(advertising_handle, fast_period, 0x0000);
            status = BLE_ABS_ADV_STATUS_ADV_FAST_START;
        }
    }

    if (BLE_SUCCESS == retval)
    {
#if (BLE_CFG_LIBRARY_TYPE != 0)
        if (0 != to)
        {
            ble_abs_timer_create(p_instance_ctrl,
                                 &p_instance_ctrl->advertising_timer_handle,
                                 (to * 10),
                                 BLE_TIMER_ONE_SHOT,
                                 ble_abs_advertising_to_function);
            ble_abs_timer_start(p_instance_ctrl, p_instance_ctrl->advertising_timer_handle);
        }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE  != 0) */
        ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, status, 0);
    }
}                                      /* End of function ble_abs_advertising_start() */

/*******************************************************************************************************************//**
 * Configure advertising data or scan response data or periodic advertising data.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_advertising_set_data (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                          uint8_t                         advertising_handle,
                                          uint8_t                         data_type)
{
    st_ble_gap_adv_data_t advertising_data;
    ble_status_t          retval = BLE_SUCCESS;
    uint32_t              status = 0;

    advertising_data.adv_hdl          = advertising_handle;
    advertising_data.zero_length_flag = BLE_GAP_DATA_0_CLEAR;
#if (BLE_CFG_LIBRARY_TYPE == 0)
    switch (advertising_handle)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            status = (BLE_GAP_ADV_DATA_MODE == data_type) ?
                     BLE_ABS_ADV_STATUS_ADV_DATA :
                     BLE_ABS_ADV_STATUS_SRES_DATA;
            advertising_data.data_type = (uint8_t) ((BLE_GAP_ADV_DATA_MODE == data_type) ?
                                                    BLE_GAP_ADV_DATA_MODE :
                                                    BLE_GAP_SCAN_RSP_DATA_MODE);
            advertising_data.data_length = (uint16_t) ((BLE_GAP_ADV_DATA_MODE == data_type) ?
                                                       p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].
                                                       advertising_parameter.legacy_advertising_parameter.
                                                       advertising_data_length :
                                                       p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].
                                                       advertising_parameter.legacy_advertising_parameter.
                                                       scan_response_data_length);
            advertising_data.p_data = (BLE_GAP_ADV_DATA_MODE == data_type) ?
                                      p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                                      legacy_advertising_parameter.p_advertising_data :
                                      p_instance_ctrl->advertising_sets[BLE_ABS_LEGACY_HDL].advertising_parameter.
                                      legacy_advertising_parameter.p_scan_response_data;
            break;
        }

        case BLE_ABS_EXT_HDL:
        case BLE_ABS_NON_CONN_HDL:
        {
            status = BLE_ABS_ADV_STATUS_ADV_DATA;
            advertising_data.data_type   = BLE_GAP_ADV_DATA_MODE;
            advertising_data.data_length = (uint16_t) ((BLE_ABS_EXT_HDL == advertising_handle) ?
                                                       p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].
                                                       advertising_parameter.extend_advertising_parameter.
                                                       advertising_data_length :
                                                       p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].
                                                       advertising_parameter.non_connectable_advertising_parameter.
                                                       advertising_data_length);
            advertising_data.p_data = (BLE_ABS_EXT_HDL == advertising_handle) ?
                                      p_instance_ctrl->advertising_sets[BLE_ABS_EXT_HDL].advertising_parameter.
                                      extend_advertising_parameter.p_advertising_data :
                                      p_instance_ctrl->advertising_sets[BLE_ABS_NON_CONN_HDL].advertising_parameter.
                                      non_connectable_advertising_parameter.p_advertising_data;
            break;
        }

        default /* BLE_ABS_PERD_HDL */:
        {
            status = (BLE_GAP_ADV_DATA_MODE == data_type) ?
                     BLE_ABS_ADV_STATUS_ADV_DATA :
                     BLE_ABS_ADV_STATUS_PERD_DATA;
            advertising_data.data_type = (uint8_t) ((BLE_GAP_ADV_DATA_MODE == data_type) ?
                                                    BLE_GAP_ADV_DATA_MODE :
                                                    BLE_GAP_PERD_ADV_DATA_MODE);
            advertising_data.data_length = (uint16_t) ((BLE_GAP_ADV_DATA_MODE == data_type) ?
                                                       p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].
                                                       advertising_parameter.periodic_advertising_parameter.
                                                       advertising_parameter.advertising_data_length :
                                                       p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].
                                                       advertising_parameter.periodic_advertising_parameter.
                                                       periodic_advertising_data_length);
            advertising_data.p_data = (BLE_GAP_ADV_DATA_MODE == data_type) ?
                                      p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.
                                      periodic_advertising_parameter.advertising_parameter.p_advertising_data :
                                      p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.
                                      periodic_advertising_parameter.p_periodic_advertising_data;
            break;
        }
    }

#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    if (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status & BLE_ABS_ADV_COMM_LEG)
    {
        status = (BLE_GAP_ADV_DATA_MODE == data_type) ?
                 BLE_ABS_ADV_STATUS_ADV_DATA :
                 BLE_ABS_ADV_STATUS_SRES_DATA;
        advertising_data.data_type = (uint8_t) ((BLE_GAP_ADV_DATA_MODE == data_type) ?
                                                BLE_GAP_ADV_DATA_MODE :
                                                BLE_GAP_SCAN_RSP_DATA_MODE);
        advertising_data.data_length = (uint16_t) ((BLE_GAP_ADV_DATA_MODE == data_type) ?
                                                   p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].
                                                   advertising_parameter.legacy_advertising_parameter.
                                                   advertising_data_length :
                                                   p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].
                                                   advertising_parameter.legacy_advertising_parameter.
                                                   scan_response_data_length);
        advertising_data.p_data = (BLE_GAP_ADV_DATA_MODE == data_type) ?
                                  p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                                  legacy_advertising_parameter.p_advertising_data :
                                  p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                                  legacy_advertising_parameter.p_scan_response_data;
    }
    else
    {
        status = BLE_ABS_ADV_STATUS_ADV_DATA;
        advertising_data.data_type   = BLE_GAP_ADV_DATA_MODE;
        advertising_data.data_length =
            p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
            non_connectable_advertising_parameter
            .advertising_data_length;
        advertising_data.p_data =
            p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
            non_connectable_advertising_parameter
            .p_advertising_data;
    }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

    retval = R_BLE_GAP_SetAdvSresData(&advertising_data);
    if (BLE_SUCCESS == retval)
    {
        ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, status, 0);
    }
}                                      /* End of function ble_abs_advertising_set_data() */

/*******************************************************************************************************************//**
 * Configure advertising data or scan response data or periodic advertising data.
 **********************************************************************************************************************/
static void ble_abs_periodic_parameter_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
#if (BLE_CFG_LIBRARY_TYPE == 0)
    if (p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_status & BLE_ABS_ADV_STATUS_PERD_PARAM)
    {
        if ((p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.periodic_advertising_parameter.
             advertising_parameter.advertising_data_length) &&
            (p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.periodic_advertising_parameter.
             advertising_parameter.p_advertising_data))
        {
            ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_PERD_HDL, BLE_GAP_ADV_DATA_MODE);
        }
        else
        {
            if ((p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.
                 periodic_advertising_parameter.periodic_advertising_data_length) &&
                (p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_parameter.
                 periodic_advertising_parameter.p_periodic_advertising_data))
            {
                ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_PERD_HDL, BLE_GAP_PERD_ADV_DATA_MODE);
            }
            else
            {
                ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_PERD_HDL);
            }
        }
    }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
} /* End of function ble_abs_periodic_parameter_handler() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_ADV_DATA_UPD_COMP event.
 **********************************************************************************************************************/
static void ble_abs_advertising_data_set_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                  st_ble_evt_data_t             * p_event_data)
{
    st_ble_gap_adv_data_evt_t * p_advertising_data_set_parameter;

    p_advertising_data_set_parameter = (st_ble_gap_adv_data_evt_t *) p_event_data->p_param;

#if (BLE_CFG_LIBRARY_TYPE == 0)
    switch (p_advertising_data_set_parameter->adv_hdl)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            if (BLE_GAP_ADV_DATA_MODE == p_advertising_data_set_parameter->data_type)
            {
                ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
            }
            else
            {
                ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_LEGACY_HDL);
            }

            break;
        }

        case BLE_ABS_EXT_HDL:
        case BLE_ABS_NON_CONN_HDL:
        {
            ble_abs_advertising_start(p_instance_ctrl, p_advertising_data_set_parameter->adv_hdl);
            break;
        }

        default:                       /* BLE_ABS_PERD_HDL */
        {
            if (BLE_GAP_ADV_DATA_MODE == p_advertising_data_set_parameter->data_type)
            {
                ble_abs_advertising_set_data(p_instance_ctrl, BLE_ABS_PERD_HDL, BLE_GAP_PERD_ADV_DATA_MODE);
            }
            else
            {
                ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_PERD_HDL);
            }

            break;
        }
    }

#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    if (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status & BLE_ABS_ADV_COMM_LEG)
    {
        if (BLE_GAP_ADV_DATA_MODE == p_advertising_data_set_parameter->data_type)
        {
            ble_abs_set_legacy_scan_response_data(p_instance_ctrl);
        }
        else
        {
            ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_COMMON_HDL);
        }
    }
    else
    {
        ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_COMMON_HDL);
    }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
} /* End of function ble_abs_advertising_data_set_handler() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_ADV_OFF event.
 **********************************************************************************************************************/
static void ble_abs_advertising_off_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                             st_ble_evt_data_t             * p_event_data)
{
    st_ble_gap_adv_off_evt_t * p_advertising_off_parameter;

    p_advertising_off_parameter = (st_ble_gap_adv_off_evt_t *) p_event_data->p_param;

#if (BLE_CFG_LIBRARY_TYPE == 0)
    switch (p_advertising_off_parameter->adv_hdl)
    {
        case BLE_ABS_LEGACY_HDL:
        case BLE_ABS_EXT_HDL:
        {
            if (0x02 == p_advertising_off_parameter->reason)
            {
                if ((p_instance_ctrl->advertising_sets[p_advertising_off_parameter->adv_hdl].advertising_status &
                     BLE_ABS_ADV_STATUS_ADV_FAST_START))
                {
                    st_ble_gap_adv_param_t advertising_parameter;

                    ble_abs_set_advertising_status(p_instance_ctrl,
                                                   p_advertising_off_parameter->adv_hdl,
                                                   0,
                                                   BLE_ABS_ADV_STATUS_ADV_FAST_START); ///< fast -> slow

                    if (BLE_ABS_LEGACY_HDL == p_advertising_off_parameter->adv_hdl)
                    {
                        ble_abs_convert_legacy_advertising_parameter(&p_instance_ctrl->advertising_sets[
                                                                         p_advertising_off_parameter->adv_hdl].advertising_parameter.legacy_advertising_parameter,
                                                                     &advertising_parameter);
                        advertising_parameter.adv_intv_min =
                            p_instance_ctrl->advertising_sets[p_advertising_off_parameter->adv_hdl].
                            advertising_parameter.
                            legacy_advertising_parameter.slow_advertising_interval;
                        advertising_parameter.adv_intv_max =
                            p_instance_ctrl->advertising_sets[p_advertising_off_parameter->adv_hdl].
                            advertising_parameter.
                            legacy_advertising_parameter.slow_advertising_interval;
                    }
                    else
                    {
                        ble_abs_convert_extend_advertising_parameter(&p_instance_ctrl->advertising_sets[
                                                                         p_advertising_off_parameter->adv_hdl].advertising_parameter.extend_advertising_parameter,
                                                                     &advertising_parameter);
                        advertising_parameter.adv_intv_min =
                            p_instance_ctrl->advertising_sets[p_advertising_off_parameter->adv_hdl].
                            advertising_parameter.
                            extend_advertising_parameter.slow_advertising_interval;
                        advertising_parameter.adv_intv_max =
                            p_instance_ctrl->advertising_sets[p_advertising_off_parameter->adv_hdl].
                            advertising_parameter.
                            extend_advertising_parameter.slow_advertising_interval;
                    }

                    R_BLE_GAP_SetAdvParam(&advertising_parameter);
                    ble_abs_set_advertising_status(p_instance_ctrl,
                                                   p_advertising_off_parameter->adv_hdl,
                                                   BLE_ABS_ADV_STATUS_PARAM_SLOW,
                                                   0);
                }
                else
                {
                    if ((p_instance_ctrl->advertising_sets[p_advertising_off_parameter->adv_hdl].advertising_status &
                         BLE_ABS_ADV_STATUS_ADV_SLOW_START))
                    {
                        ble_abs_set_advertising_status(p_instance_ctrl,
                                                       p_advertising_off_parameter->adv_hdl,
                                                       0,
                                                       BLE_ABS_ADV_STATUS_ADV_SLOW_START); ///< slow -> off
                    }
                }
            }
            else
            {
                ble_abs_set_advertising_status(p_instance_ctrl,
                                               p_advertising_off_parameter->adv_hdl,
                                               0,
                                               (BLE_ABS_ADV_STATUS_ADV_SLOW_START | BLE_ABS_ADV_STATUS_ADV_FAST_START));
            }

            break;
        }

        case BLE_ABS_NON_CONN_HDL:
        {
            ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_NON_CONN_HDL, 0, BLE_ABS_ADV_STATUS_ADV_SLOW_START); ///< slow -> off
            break;
        }

        default:                                                                                                         /* BLE_ABS_PERD_HDL */
        {
            ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_PERD_HDL, 0, BLE_ABS_ADV_STATUS_ADV_SLOW_START);
            if (0 !=
                (p_instance_ctrl->advertising_sets[BLE_ABS_PERD_HDL].advertising_status &
                 BLE_ABS_ADV_STATUS_PERD_START))
            {
                R_BLE_GAP_StopPerdAdv(BLE_ABS_PERD_HDL);
            }

            break;
        }
    }

#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */
    if (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status & BLE_ABS_ADV_COMM_TO)
    {
        p_advertising_off_parameter->reason = 0x02;
        ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_COMMON_HDL, 0, BLE_ABS_ADV_COMM_TO);
    }

    if (p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status & BLE_ABS_ADV_COMM_LEG)
    {
        if (0x02 == p_advertising_off_parameter->reason)
        {
            if ((p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status &
                 BLE_ABS_ADV_STATUS_ADV_FAST_START))
            {
                st_ble_gap_adv_param_t advertising_parameter;

                ble_abs_set_advertising_status(p_instance_ctrl,
                                               BLE_ABS_COMMON_HDL,
                                               0,
                                               BLE_ABS_ADV_STATUS_ADV_FAST_START); ///< fast -> slow

                ble_abs_convert_legacy_advertising_parameter(
                    &p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.legacy_advertising_parameter,
                    &advertising_parameter);
                advertising_parameter.adv_intv_min =
                    p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                    legacy_advertising_parameter
                    .slow_advertising_interval;
                advertising_parameter.adv_intv_max =
                    p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_parameter.
                    legacy_advertising_parameter
                    .slow_advertising_interval;

                R_BLE_GAP_SetAdvParam(&advertising_parameter);
                ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_COMMON_HDL, BLE_ABS_ADV_STATUS_PARAM_SLOW, 0);
            }
            else
            {
                if ((p_instance_ctrl->advertising_sets[BLE_ABS_COMMON_HDL].advertising_status &
                     BLE_ABS_ADV_STATUS_ADV_SLOW_START))
                {
                    ble_abs_set_advertising_status(p_instance_ctrl,
                                                   BLE_ABS_COMMON_HDL,
                                                   0,
                                                   BLE_ABS_ADV_STATUS_ADV_SLOW_START); ///< slow -> off
                }
            }
        }
        else
        {
            ble_abs_set_advertising_status(p_instance_ctrl,
                                           BLE_ABS_COMMON_HDL,
                                           0,
                                           (BLE_ABS_ADV_STATUS_ADV_SLOW_START | BLE_ABS_ADV_STATUS_ADV_FAST_START |
                                            BLE_ABS_ADV_COMM_LEG));
        }
    }
    else
    {
        ble_abs_set_advertising_status(p_instance_ctrl,
                                       BLE_ABS_COMMON_HDL,
                                       0,
                                       (BLE_ABS_ADV_STATUS_ADV_SLOW_START | BLE_ABS_ADV_COMM_NON)); ///< slow -> off
    }
#endif /* (BLE_CFG_LIBRARY_TYPE == 0) */
} /* End of function ble_abs_advertising_off_handler() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_ADV_REPT_IND event.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                   Filtering data is not included in the advertising data.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_advertising_report_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                     st_ble_evt_data_t             * p_event_data)
{
    st_ble_gap_adv_rept_evt_t * p_advertising_report_parameter;
    uint8_t * p_buf  = NULL;
    uint32_t  len    = 0;
    fsp_err_t retval = FSP_ERR_BLE_ABS_NOT_FOUND;

    if ((NULL == p_instance_ctrl->abs_scan.scan_parameter.p_filter_data) ||
        (0 == p_instance_ctrl->abs_scan.scan_parameter.filter_data_length))
    {
        retval = FSP_SUCCESS;
    }
    else
    {
        p_advertising_report_parameter = (st_ble_gap_adv_rept_evt_t *) p_event_data->p_param;

        switch (p_advertising_report_parameter->adv_rpt_type)
        {
            /*Legacy Advertising Report.*/
            case 0x00:
            {
                p_buf = p_advertising_report_parameter->param.p_adv_rpt->p_data;
                len   = p_advertising_report_parameter->param.p_adv_rpt->len;

                break;
            }

            /*Extended Advertising Report.*/
            case 0x01:
            {
                p_buf = p_advertising_report_parameter->param.p_ext_adv_rpt->p_data;
                len   = p_advertising_report_parameter->param.p_ext_adv_rpt->len;

                break;
            }

            /*Periodic Advertising Report.*/
            case 0x02:
            {
                p_buf = p_advertising_report_parameter->param.p_per_adv_rpt->p_data;
                len   = p_advertising_report_parameter->param.p_per_adv_rpt->len;
                break;
            }

            default:
            {
                break;
            }
        }

        uint32_t cnt = len - (uint32_t) p_instance_ctrl->abs_scan.scan_parameter.filter_data_length + 1;

        if (1 <= cnt)
        {
            uint32_t i;
            uint16_t pos = 0U;

            while (pos < len)
            {
                /* Each advertising structure have following constructs.
                 * - Lenght: 1 byte (The length of AD type + AD data)
                 * - AD type: 1 byte
                 * - AD data: variable
                 */
                uint8_t ad_len = (uint8_t) (p_buf[pos] - 1);
                uint8_t type   = p_buf[pos + 1];

                if (type == p_instance_ctrl->abs_scan.scan_parameter.filter_ad_type)
                {
                    for (i = 0; i < ad_len; i++)
                    {
                        if (0 == memcmp(&p_buf[pos + 2U + i],
                                        p_instance_ctrl->abs_scan.scan_parameter.p_filter_data,
                                        (uint32_t) p_instance_ctrl->abs_scan.scan_parameter.filter_data_length))
                        {
                            return FSP_SUCCESS;
                        }
                    }
                }

                pos = (uint16_t) (pos + ad_len);
                pos = (uint16_t) (pos + 2UL);
            }
        }
    }

    return retval;
}                                      /* End of function ble_abs_advertising_report_handler() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_LOC_VER_INFO event.
 **********************************************************************************************************************/
static void ble_abs_loc_ver_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl, st_ble_evt_data_t * p_event_data)
{
    st_ble_gap_loc_dev_info_evt_t * event_parameter;
    event_parameter              = (st_ble_gap_loc_dev_info_evt_t *) p_event_data->p_param;
    p_instance_ctrl->loc_bd_addr = event_parameter->l_dev_addr;
}                                      /* End of function ble_abs_loc_ver_handler() */

/*******************************************************************************************************************//**
 * Convert Abstraction API scan phy parameters to GAP scan phy parameters.
 **********************************************************************************************************************/
static void ble_abs_convert_scan_phy_parameter (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                ble_abs_scan_phy_parameter_t  * p_abs_phy,
                                                ble_gap_scan_phy_parameter_t  * p_gap_phy,
                                                ble_gap_scan_on_t             * p_scan_enable)
{
    if ((NULL != p_abs_phy) && (NULL != p_gap_phy))
    {
        p_gap_phy->scan_type = p_abs_phy->scan_type;

        if (p_instance_ctrl->abs_scan.scan_parameter.fast_scan_period)
        {
            p_gap_phy->scan_intv    = p_abs_phy->fast_scan_interval;
            p_gap_phy->scan_window  = p_abs_phy->fast_scan_window;
            p_scan_enable->duration = p_instance_ctrl->abs_scan.scan_parameter.fast_scan_period;
        }
        else
        {
            p_gap_phy->scan_intv    = p_abs_phy->slow_scan_interval;
            p_gap_phy->scan_window  = p_abs_phy->slow_scan_window;
            p_scan_enable->duration = p_instance_ctrl->abs_scan.scan_parameter.slow_scan_period;
        }
    }
}                                      /* End of function ble_abs_convert_scan_phy_parameter() */

/*******************************************************************************************************************//**
 * Convert Abstraction API scan parameters to GAP scan parameters.
 **********************************************************************************************************************/
static void ble_abs_convert_scan_parameter (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                            st_ble_gap_scan_param_t       * p_gap_scan_parameter,
                                            ble_gap_scan_on_t             * p_gap_scan_enable,
                                            uint32_t                        status)
{
    p_gap_scan_parameter->o_addr_type   = BLE_GAP_ADDR_PUBLIC;
    p_gap_scan_parameter->filter_policy = p_instance_ctrl->abs_scan.scan_parameter.device_scan_filter_policy;
    p_gap_scan_enable->proc_type        = BLE_GAP_SC_PROC_OBS;
    p_gap_scan_enable->period           = 0;
    p_gap_scan_enable->filter_dups      = p_instance_ctrl->abs_scan.scan_parameter.filter_duplicate;

    if (BLE_ABS_SCAN_STATUS_FAST_START == status)
    {
        if (p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M)
        {
            ble_abs_convert_scan_phy_parameter(p_instance_ctrl,
                                               p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M,
                                               (ble_gap_scan_phy_parameter_t *) p_gap_scan_parameter->p_phy_param_1M,
                                               p_gap_scan_enable);
        }

        if (p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded)
        {
            ble_abs_convert_scan_phy_parameter(p_instance_ctrl,
                                               p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded,
                                               (ble_gap_scan_phy_parameter_t *) p_gap_scan_parameter->p_phy_param_coded,
                                               p_gap_scan_enable);
        }
    }
    else
    {
        if (p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M)
        {
            p_gap_scan_parameter->p_phy_param_1M->scan_type =
                p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M->scan_type;
            p_gap_scan_parameter->p_phy_param_1M->scan_intv =
                p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M->slow_scan_interval;
            p_gap_scan_parameter->p_phy_param_1M->scan_window =
                p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M->slow_scan_window;
        }

        if (p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded)
        {
            p_gap_scan_parameter->p_phy_param_coded->scan_type =
                p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded->scan_type;
            p_gap_scan_parameter->p_phy_param_coded->scan_intv =
                p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded->slow_scan_interval;
            p_gap_scan_parameter->p_phy_param_coded->scan_window =
                p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded->slow_scan_window;
        }

        p_gap_scan_enable->duration = p_instance_ctrl->abs_scan.scan_parameter.slow_scan_period;
    }
}                                      /* End of function ble_abs_convert_scan_parameter() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_SCAN_TO event.
 **********************************************************************************************************************/
static void ble_abs_scan_to_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    st_ble_gap_scan_param_t      scan_parameter;
    ble_gap_scan_phy_parameter_t phy_parameter_1M;
    ble_gap_scan_phy_parameter_t phy_parameter_coded;
    ble_gap_scan_on_t            scan_enable;

    if (p_instance_ctrl->abs_scan.scan_status & BLE_ABS_SCAN_STATUS_FAST_START)
    {
        ble_abs_set_scan_status(p_instance_ctrl, 0, BLE_ABS_SCAN_STATUS_SLOW_START); ///< fast -> slow
        scan_parameter.p_phy_param_1M =
            p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M ? (st_ble_gap_scan_phy_param_t *) (&
                                                                                                           phy_parameter_1M)
            :
            NULL;
        scan_parameter.p_phy_param_coded =
            p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded ? (st_ble_gap_scan_phy_param_t *) (&
                                                                                                              phy_parameter_coded)
            :
            NULL;

        ble_abs_convert_scan_parameter(p_instance_ctrl, &scan_parameter, &scan_enable, BLE_ABS_SCAN_STATUS_SLOW_START);

        R_BLE_GAP_StartScan(&scan_parameter, (st_ble_gap_scan_on_t *) &scan_enable);
        ble_abs_set_scan_status(p_instance_ctrl, BLE_ABS_SCAN_STATUS_SLOW_START, BLE_ABS_SCAN_STATUS_FAST_START);
    }
    else
    {
        if (p_instance_ctrl->abs_scan.scan_status & BLE_ABS_SCAN_STATUS_SLOW_START)
        {
            ble_abs_set_scan_status(p_instance_ctrl, 0, BLE_ABS_SCAN_STATUS_SLOW_START); ///< slow -> off
        }
    }
} /* End of function ble_abs_scan_to_handler() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_CONN_IND event.
 **********************************************************************************************************************/
static void ble_abs_connection_indication_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    ble_abs_timer_stop(p_instance_ctrl, p_instance_ctrl->connection_timer_handle);
    ble_abs_timer_delete(p_instance_ctrl, &p_instance_ctrl->connection_timer_handle);

#if (BLE_CFG_LIBRARY_TYPE != 0)
    ble_abs_timer_stop(p_instance_ctrl, p_instance_ctrl->advertising_timer_handle);

    ble_abs_set_advertising_status(p_instance_ctrl,
                                   BLE_ABS_COMMON_HDL,
                                   0,
                                   (BLE_ABS_ADV_STATUS_ADV_SLOW_START | BLE_ABS_ADV_STATUS_ADV_FAST_START |
                                    BLE_ABS_ADV_COMM_LEG));
#endif                                 /* (BLE_CFG_LIBRARY_TYPE != 0) */
} /* End of function ble_abs_connection_indication_handler() */

/*******************************************************************************************************************//**
 * Set gap callback and vendor specific callback function.
 **********************************************************************************************************************/
static void ble_abs_set_abs_callback (ble_abs_instance_ctrl_t * const            p_instance_ctrl,
                                      ble_gap_application_callback_t             gap_callback,
                                      ble_vendor_specific_application_callback_t vendor_specific_callback)
{
    p_instance_ctrl->abs_gap_callback             = gap_callback;
    p_instance_ctrl->abs_vendor_specific_callback = vendor_specific_callback;
}                                      /* End of function ble_abs_set_abs_callback() */

/*******************************************************************************************************************//**
 * Set advertising interval.
 **********************************************************************************************************************/
static void ble_abs_set_connection_advertising_interval (st_ble_gap_adv_param_t * p_advertising_parameter,
                                                         uint32_t                 fast_advertising_interval,
                                                         uint32_t                 slow_advertising_interval,
                                                         uint16_t                 fast_period)
{
    /** check advertising interval */
    if (fast_period)
    {
        p_advertising_parameter->adv_intv_min = fast_advertising_interval;
        p_advertising_parameter->adv_intv_max = fast_advertising_interval;
    }
    else
    {
        p_advertising_parameter->adv_intv_min = slow_advertising_interval;
        p_advertising_parameter->adv_intv_max = slow_advertising_interval;
    }
}                                      /* End of function ble_abs_set_connection_advertising_interval() */

/*******************************************************************************************************************//**
 * Update advertising data status.
 **********************************************************************************************************************/
static void ble_abs_update_data_status (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                        uint32_t                        advertising_status,
                                        uint8_t                       * p_advertising_data,
                                        uint16_t                        advertising_data_len,
                                        uint8_t                         advertising_handle)
{
    if (p_instance_ctrl->advertising_sets[advertising_handle].advertising_status & advertising_status)
    {
        if ((0 != advertising_data_len) && (NULL != p_advertising_data))
        {
            ble_abs_set_advertising_status(p_instance_ctrl, advertising_handle, 0, advertising_status);
        }
    }
}                                      /* End of function ble_abs_update_data_status() */

/*******************************************************************************************************************//**
 * Convert the legacy advertising parameters to GAP advertising parameters.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_convert_legacy_advertising_parameter (
    ble_abs_legacy_advertising_parameter_t * p_legacy_advertising_parameter,
    st_ble_gap_adv_param_t                 * p_gap_advertising_parameter)
{
    p_gap_advertising_parameter->adv_hdl       = BLE_ABS_LEGACY_HDL;
    p_gap_advertising_parameter->adv_prop_type = BLE_GAP_LEGACY_PROP_ADV_IND;
    p_gap_advertising_parameter->adv_ch_map    = p_legacy_advertising_parameter->advertising_channel_map;

    FSP_ERROR_RETURN((BLE_GAP_ADDR_RPA_ID_PUBLIC >= p_legacy_advertising_parameter->own_bluetooth_address_type),
                     FSP_ERR_INVALID_ARGUMENT);

    memcpy(p_gap_advertising_parameter->o_addr,
           (void *) p_legacy_advertising_parameter->own_bluetooth_address,
           BLE_BD_ADDR_LEN);

    p_gap_advertising_parameter->o_addr_type = p_legacy_advertising_parameter->own_bluetooth_address_type;

    if (p_legacy_advertising_parameter->p_peer_address)
    {
        memcpy(p_gap_advertising_parameter->p_addr,
               p_legacy_advertising_parameter->p_peer_address->addr,
               BLE_BD_ADDR_LEN);
        p_gap_advertising_parameter->p_addr_type = p_legacy_advertising_parameter->p_peer_address->type;
    }
    else
    {
        p_gap_advertising_parameter->p_addr_type = BLE_GAP_ADDR_PUBLIC;
    }

    FSP_ERROR_RETURN(
        BLE_ABS_ADVERTISING_FILTER_ALLOW_WHITE_LIST >= p_legacy_advertising_parameter->advertising_filter_policy,
        FSP_ERR_INVALID_ARGUMENT);

    p_gap_advertising_parameter->filter_policy = p_legacy_advertising_parameter->advertising_filter_policy;

    p_gap_advertising_parameter->adv_phy           = BLE_GAP_ADV_PHY_1M;
    p_gap_advertising_parameter->sec_adv_max_skip  = 0x00;
    p_gap_advertising_parameter->sec_adv_phy       = BLE_GAP_ADV_PHY_1M;
    p_gap_advertising_parameter->scan_req_ntf_flag = BLE_GAP_SCAN_REQ_NTF_DISABLE;

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_convert_legacy_advertising_parameter() */

/*******************************************************************************************************************//**
 * Convert the extended advertising parameters to GAP advertising parameters.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
#if (BLE_CFG_LIBRARY_TYPE == 0)
static fsp_err_t ble_abs_convert_extend_advertising_parameter (
    ble_abs_extend_advertising_parameter_t * p_extend_advertising_parameter,
    st_ble_gap_adv_param_t                 * p_gap_advertising_parameter)
{
    p_gap_advertising_parameter->adv_hdl    = BLE_ABS_EXT_HDL;
    p_gap_advertising_parameter->adv_ch_map = p_extend_advertising_parameter->advertising_channel_map;

    FSP_ERROR_RETURN((BLE_GAP_ADDR_RPA_ID_PUBLIC >= p_extend_advertising_parameter->own_bluetooth_address_type),
                     FSP_ERR_INVALID_ARGUMENT);

    memcpy(p_gap_advertising_parameter->o_addr,
           (void *) p_extend_advertising_parameter->own_bluetooth_address,
           BLE_BD_ADDR_LEN);

    p_gap_advertising_parameter->o_addr_type = p_extend_advertising_parameter->own_bluetooth_address_type;

    if (p_extend_advertising_parameter->p_peer_address)
    {
        memcpy(p_gap_advertising_parameter->p_addr,
               p_extend_advertising_parameter->p_peer_address->addr,
               BLE_BD_ADDR_LEN);
        p_gap_advertising_parameter->p_addr_type   = p_extend_advertising_parameter->p_peer_address->type;
        p_gap_advertising_parameter->adv_prop_type = BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_DIRECT;
    }
    else
    {
        p_gap_advertising_parameter->p_addr_type   = BLE_GAP_ADDR_PUBLIC;
        p_gap_advertising_parameter->adv_prop_type = BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_UNDIRECT;
    }

    FSP_ERROR_RETURN(
        BLE_ABS_ADVERTISING_FILTER_ALLOW_WHITE_LIST >= p_extend_advertising_parameter->advertising_filter_policy,
        FSP_ERR_INVALID_ARGUMENT);

    p_gap_advertising_parameter->filter_policy = p_extend_advertising_parameter->advertising_filter_policy;

    FSP_ERROR_RETURN((BLE_GAP_ADV_PHY_1M == p_extend_advertising_parameter->primary_advertising_phy) ||
                     (BLE_GAP_ADV_PHY_CD == p_extend_advertising_parameter->primary_advertising_phy),
                     FSP_ERR_INVALID_ARGUMENT);

    p_gap_advertising_parameter->adv_phy          = p_extend_advertising_parameter->primary_advertising_phy;
    p_gap_advertising_parameter->sec_adv_max_skip = 0x00;

    FSP_ERROR_RETURN((BLE_GAP_ADV_PHY_1M <= p_extend_advertising_parameter->secondary_advertising_phy) &&
                     (BLE_GAP_ADV_PHY_CD >= p_extend_advertising_parameter->secondary_advertising_phy),
                     FSP_ERR_INVALID_ARGUMENT);

    p_gap_advertising_parameter->sec_adv_phy       = p_extend_advertising_parameter->secondary_advertising_phy;
    p_gap_advertising_parameter->scan_req_ntf_flag = BLE_GAP_SCAN_REQ_NTF_DISABLE;

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_convert_extend_advertising_parameter() */

#endif /* (BLE_CFG_LIBRARY_TYPE == 0) */

/*******************************************************************************************************************//**
 * Convert the non-connectable advertising parameters to GAP advertising parameters.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_convert_non_connectable_advertising_parameter (
    ble_abs_non_connectable_advertising_parameter_t * p_non_connectable_advertising_parameter,
    st_ble_gap_adv_param_t                          * p_gap_advertising_parameter,
    uint8_t                                           advertising_handle)
{
    p_gap_advertising_parameter->adv_hdl    = advertising_handle;
    p_gap_advertising_parameter->adv_ch_map = p_non_connectable_advertising_parameter->advertising_channel_map;

    FSP_ERROR_RETURN(
        (BLE_GAP_ADDR_RPA_ID_PUBLIC >= p_non_connectable_advertising_parameter->own_bluetooth_address_type),
        FSP_ERR_INVALID_ARGUMENT);

    memcpy(p_gap_advertising_parameter->o_addr,
           (void *) p_non_connectable_advertising_parameter->own_bluetooth_address,
           BLE_BD_ADDR_LEN);

    p_gap_advertising_parameter->o_addr_type = p_non_connectable_advertising_parameter->own_bluetooth_address_type;
#if (BLE_CFG_LIBRARY_TYPE != 0)
    p_non_connectable_advertising_parameter->primary_advertising_phy = BLE_ABS_ADVERTISING_PHY_LEGACY;
#endif                                 /* (BLE_CFG_LIBRARY_TYPE != 0) */
    FSP_ERROR_RETURN((BLE_GAP_ADV_PHY_1M >= p_non_connectable_advertising_parameter->primary_advertising_phy) ||
                     (BLE_GAP_ADV_PHY_CD == p_non_connectable_advertising_parameter->primary_advertising_phy),
                     FSP_ERR_INVALID_ARGUMENT);
#if (BLE_CFG_LIBRARY_TYPE == 0)
    FSP_ERROR_RETURN((BLE_ABS_ADVERTISING_PHY_LEGACY != p_non_connectable_advertising_parameter->primary_advertising_phy) ||
                     (BLE_ABS_PERD_HDL != advertising_handle),
                     FSP_ERR_INVALID_ARGUMENT);
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

    p_gap_advertising_parameter->adv_phy =
        (uint8_t) ((BLE_ABS_ADVERTISING_PHY_LEGACY ==
                    p_non_connectable_advertising_parameter->primary_advertising_phy) ?
                   BLE_GAP_ADV_PHY_1M :
                   p_non_connectable_advertising_parameter->primary_advertising_phy);

    if (p_non_connectable_advertising_parameter->p_peer_address)
    {
        memcpy(p_gap_advertising_parameter->p_addr,
               p_non_connectable_advertising_parameter->p_peer_address->addr,
               BLE_BD_ADDR_LEN);
        p_gap_advertising_parameter->p_addr_type   = p_non_connectable_advertising_parameter->p_peer_address->type;
        p_gap_advertising_parameter->adv_prop_type =
            (uint16_t) ((BLE_ABS_ADVERTISING_PHY_LEGACY !=
                         p_non_connectable_advertising_parameter->primary_advertising_phy) ?
                        BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_DIRECT :
                        BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND);
    }
    else
    {
        p_gap_advertising_parameter->p_addr_type   = BLE_GAP_ADDR_PUBLIC;
        p_gap_advertising_parameter->adv_prop_type =
            (uint16_t) ((BLE_ABS_ADVERTISING_PHY_LEGACY !=
                         p_non_connectable_advertising_parameter->primary_advertising_phy) ?
                        BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_UNDIRECT :
                        BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND);
    }

    p_gap_advertising_parameter->filter_policy    = BLE_ABS_ADVERTISING_FILTER_ALLOW_ANY;
    p_gap_advertising_parameter->sec_adv_max_skip = 0x00;

    FSP_ERROR_RETURN((BLE_GAP_ADV_PHY_1M <= p_non_connectable_advertising_parameter->secondary_advertising_phy) &&
                     (BLE_GAP_ADV_PHY_CD >= p_non_connectable_advertising_parameter->secondary_advertising_phy),
                     FSP_ERR_INVALID_ARGUMENT);

    p_gap_advertising_parameter->sec_adv_phy       = p_non_connectable_advertising_parameter->secondary_advertising_phy;
    p_gap_advertising_parameter->scan_req_ntf_flag = BLE_GAP_SCAN_REQ_NTF_DISABLE;

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_convert_non_connectable_advertising_parameter() */

/*******************************************************************************************************************//**
 * Set advertising status.
 **********************************************************************************************************************/
static void ble_abs_set_advertising_status (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                            uint8_t                         advertising_handle,
                                            uint32_t                        set,
                                            uint32_t                        clear)
{
    p_instance_ctrl->advertising_sets[advertising_handle].advertising_status |= set;
    p_instance_ctrl->advertising_sets[advertising_handle].advertising_status &= ~clear;
}                                      /* End of function ble_abs_set_advertising_status() */

/*******************************************************************************************************************//**
 * Store advertising configuration.
 **********************************************************************************************************************/
static void ble_abs_set_advertising_parameter (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                               void                          * p_advertising_parameter,
                                               uint8_t                         advertising_handle)
{
    switch (advertising_handle)
    {
        case BLE_ABS_LEGACY_HDL:
        {
            ble_abs_legacy_advertising_parameter_t * p_abs_legacy;
            p_abs_legacy = (ble_abs_legacy_advertising_parameter_t *) p_advertising_parameter;
#if (BLE_CFG_LIBRARY_TYPE != 0)
            advertising_handle = BLE_ABS_COMMON_HDL;
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
            memcpy(
                &p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.legacy_advertising_parameter,
                p_abs_legacy,
                sizeof(ble_abs_legacy_advertising_parameter_t));
            if (NULL != p_abs_legacy->p_peer_address)
            {
                memcpy(&p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address,
                       p_abs_legacy->p_peer_address,
                       sizeof(ble_device_address_t));
                p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.legacy_advertising_parameter
                .p_peer_address = &p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address;
            }

            break;
        }

#if (BLE_CFG_LIBRARY_TYPE == 0)
        case BLE_ABS_EXT_HDL:
        {
            ble_abs_extend_advertising_parameter_t * p_abs_ext;
            p_abs_ext = (ble_abs_extend_advertising_parameter_t *) p_advertising_parameter;
            memcpy(
                &p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.extend_advertising_parameter,
                p_abs_ext,
                sizeof(ble_abs_extend_advertising_parameter_t));
            if (NULL != p_abs_ext->p_peer_address)
            {
                memcpy(&p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address,
                       p_abs_ext->p_peer_address,
                       sizeof(ble_device_address_t));
                p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.extend_advertising_parameter
                .p_peer_address = &p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address;
            }

            break;
        }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

        case BLE_ABS_NON_CONN_HDL:
        {
            ble_abs_non_connectable_advertising_parameter_t * p_abs_non_conn;
            p_abs_non_conn = (ble_abs_non_connectable_advertising_parameter_t *) p_advertising_parameter;
#if (BLE_CFG_LIBRARY_TYPE != 0)
            advertising_handle = BLE_ABS_COMMON_HDL;
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
            memcpy(
                &p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.non_connectable_advertising_parameter,
                p_abs_non_conn,
                sizeof(ble_abs_non_connectable_advertising_parameter_t));
            if (NULL != p_abs_non_conn->p_peer_address)
            {
                memcpy(&p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address,
                       p_abs_non_conn->p_peer_address,
                       sizeof(ble_device_address_t));
                p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.
                non_connectable_advertising_parameter.p_peer_address =
                    &p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address;
            }

            break;
        }

        default:                       /** BLE_ABS_PERD_HDL */
#if (BLE_CFG_LIBRARY_TYPE == 0)
            {
                ble_abs_periodic_advertising_parameter_t * p_abs_perd;
                p_abs_perd = (ble_abs_periodic_advertising_parameter_t *) p_advertising_parameter;
                memcpy(
                    &p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.periodic_advertising_parameter,
                    p_abs_perd,
                    sizeof(ble_abs_periodic_advertising_parameter_t));
                if (NULL != p_abs_perd->advertising_parameter.p_peer_address)
                {
                    memcpy(&p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address,
                           p_abs_perd->advertising_parameter.p_peer_address,
                           sizeof(ble_device_address_t));
                    p_instance_ctrl->advertising_sets[advertising_handle].advertising_parameter.
                    periodic_advertising_parameter.advertising_parameter.p_peer_address =
                        &p_instance_ctrl->advertising_sets[advertising_handle].remote_device_address;
                }
            }
#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */
            break;
    }
} /* End of function ble_abs_set_advertising_parameter() */

/*******************************************************************************************************************//**
 * Check scan phy parameters.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    The advertising parameter is out of range.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_check_scan_phy_parameter (ble_abs_scan_phy_parameter_t * p_scan_phy)
{
    FSP_ERROR_RETURN((BLE_GAP_SCAN_INTV_MIN <= p_scan_phy->fast_scan_interval) &&
                     (BLE_GAP_SCAN_INTV_MIN <= p_scan_phy->slow_scan_interval) &&
                     (BLE_GAP_SCAN_INTV_MIN <= p_scan_phy->fast_scan_window) &&
                     (BLE_GAP_SCAN_INTV_MIN <= p_scan_phy->slow_scan_window) &&
                     (BLE_GAP_SCAN_ACTIVE >= p_scan_phy->scan_type),
                     FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Store scan configuration.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    Scan phy parameter is out of range.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_set_scan_parameter (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                             ble_abs_scan_parameter_t      * p_scan_parameter)
{
    if (p_scan_parameter->p_phy_parameter_1M)
    {
        FSP_ERROR_RETURN(FSP_SUCCESS == ble_abs_check_scan_phy_parameter(p_scan_parameter->p_phy_parameter_1M),
                         FSP_ERR_INVALID_ARGUMENT); ///< check abs scan parameters 1M
    }

    if (p_scan_parameter->p_phy_parameter_coded)
    {
        FSP_ERROR_RETURN(FSP_SUCCESS == ble_abs_check_scan_phy_parameter(p_scan_parameter->p_phy_parameter_coded),
                         FSP_ERR_INVALID_ARGUMENT); ///< check abs scan parameters coded
    }

    FSP_ERROR_RETURN(BLE_ABS_CONN_EXT_ADV_DATA_LEN >= p_scan_parameter->filter_data_length, FSP_ERR_INVALID_ARGUMENT);

    memcpy(&p_instance_ctrl->abs_scan.scan_parameter, p_scan_parameter, sizeof(ble_abs_scan_parameter_t));
    if (p_scan_parameter->p_phy_parameter_1M)
    {
        memcpy(&p_instance_ctrl->abs_scan.scan_phy_parameter_1M,
               p_scan_parameter->p_phy_parameter_1M,
               sizeof(ble_abs_scan_phy_parameter_t));
        p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_1M = &p_instance_ctrl->abs_scan.scan_phy_parameter_1M;
    }

    if (p_scan_parameter->p_phy_parameter_coded)
    {
        memcpy(&p_instance_ctrl->abs_scan.scan_phy_parameter_coded,
               p_scan_parameter->p_phy_parameter_coded,
               sizeof(ble_abs_scan_phy_parameter_t));
        p_instance_ctrl->abs_scan.scan_parameter.p_phy_parameter_coded =
            &p_instance_ctrl->abs_scan.scan_phy_parameter_coded;
    }

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_set_scan_parameter() */

/*******************************************************************************************************************//**
 * Set scan status.
 **********************************************************************************************************************/
static void ble_abs_set_scan_status (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t set, uint32_t clear)
{
    p_instance_ctrl->abs_scan.scan_status |= set;
    p_instance_ctrl->abs_scan.scan_status &= ~clear;
}                                      /* End of function ble_abs_set_scan_status() */

/*******************************************************************************************************************//**
 * Register IRK to the Resolving List.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_set_irk_to_resolving_list (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint8_t * p_lc_irk)
{
    st_ble_gap_rslv_list_key_set_t peer_irk;
    ble_device_address_t           remote_device_address;
    ble_status_t retval = BLE_SUCCESS;

    memset(peer_irk.remote_irk, BLE_ABS_GAP_REMOTE_IRK_AA, BLE_GAP_IRK_SIZE);
    peer_irk.local_irk_type = BLE_GAP_RL_LOC_KEY_REGISTERED;
    memset(remote_device_address.addr, BLE_ABS_REMOTE_DEVICE_ADDRESS_55, BLE_BD_ADDR_LEN);
    remote_device_address.type = BLE_GAP_ADDR_PUBLIC;

    R_BLE_GAP_SetLocIdInfo(&p_instance_ctrl->loc_bd_addr, p_lc_irk);

    /** store local id info */
    ble_abs_secure_data_writelocinfo(p_instance_ctrl->p_cfg->p_flash_instance,
                                     (ble_device_address_t *) (&p_instance_ctrl->loc_bd_addr),
                                     p_lc_irk,
                                     NULL); ///< store local id info

    retval = R_BLE_GAP_ConfRslvList(BLE_GAP_LIST_ADD_DEV, (st_ble_dev_addr_t *) (&remote_device_address), &peer_irk, 1);
    p_instance_ctrl->set_privacy_status = (BLE_SUCCESS == retval) ? BLE_ABS_PV_STATUS_ADD_RSLV : 0;
} /* End of function ble_abs_set_irk_to_resolving_list() */

/*******************************************************************************************************************//**
 * Handler for GAP BLE_GAP_EVENT_RSLV_LIST_CONF_COMP event.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_conflict_resolving_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                                st_ble_evt_data_t             * p_event_data)
{
    if (p_instance_ctrl->set_privacy_status)
    {
        st_ble_gap_rslv_list_conf_evt_t * p_resolving_list_config;
        ble_status_t retval = BLE_SUCCESS;

        p_resolving_list_config = (st_ble_gap_rslv_list_conf_evt_t *) p_event_data->p_param;
        if (BLE_GAP_LIST_ADD_DEV == p_resolving_list_config->op_code)
        {
            ble_device_address_t remote_device_address;
            memset(remote_device_address.addr, BLE_ABS_REMOTE_DEVICE_ADDRESS_55, BLE_BD_ADDR_LEN);
            remote_device_address.type = 0x00;
            retval = R_BLE_GAP_SetPrivMode((st_ble_dev_addr_t *) (&remote_device_address),
                                           &p_instance_ctrl->privacy_mode,
                                           1);
            p_instance_ctrl->set_privacy_status = (BLE_SUCCESS == retval) ?
                                                  BLE_ABS_PV_STATUS_SET_MODE :
                                                  0;
        }
    }
}                                      /* End of function ble_abs_conflict_resolving_handler() */

/*******************************************************************************************************************//**
 * GAP Event handler.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 **********************************************************************************************************************/
static void ble_abs_gap_callback (uint16_t event_type, ble_status_t event_result, st_ble_evt_data_t * p_event_data)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = gp_instance_ctrl;

    switch (event_type)
    {
        case BLE_GAP_EVENT_STACK_ON:
        {
            R_BLE_GAP_GetVerInfo();
            uint8_t              irk[BLE_GAP_IRK_SIZE];
            ble_device_address_t identity_address;
            fsp_err_t            retval;

            ble_abs_secure_data_init(p_instance_ctrl->p_cfg->p_flash_instance);
            retval = ble_abs_secure_data_readlocinfo(p_instance_ctrl->p_cfg->p_flash_instance,
                                                     &identity_address,
                                                     irk,
                                                     NULL);
            if (FSP_SUCCESS == retval)
            {
                R_BLE_GAP_SetLocIdInfo((st_ble_dev_addr_t *) (&identity_address), irk);
            }

            break;
        }

        case BLE_GAP_EVENT_LOC_VER_INFO:
        {
            ble_abs_loc_ver_handler(p_instance_ctrl, p_event_data);
            break;
        }

        case BLE_GAP_EVENT_ADV_REPT_IND:
        {
            if (FSP_SUCCESS != ble_abs_advertising_report_handler(p_instance_ctrl, p_event_data))
            {
                return;
            }

            break;
        }

        case BLE_GAP_EVENT_ADV_PARAM_SET_COMP:
        {
            ble_abs_advertising_parameter_set_handler(p_instance_ctrl, p_event_data);
            break;
        }

        case BLE_GAP_EVENT_ADV_DATA_UPD_COMP:
        {
            ble_abs_advertising_data_set_handler(p_instance_ctrl, p_event_data);
            break;
        }

        case BLE_GAP_EVENT_PERD_ADV_PARAM_SET_COMP:
        {
            ble_abs_periodic_parameter_handler(p_instance_ctrl);
            break;
        }

        case BLE_GAP_EVENT_PERD_ADV_ON:
        {
            ble_abs_advertising_start(p_instance_ctrl, BLE_ABS_PERD_HDL);
            break;
        }

        case BLE_GAP_EVENT_PERD_ADV_OFF:
        {
            ble_abs_set_advertising_status(p_instance_ctrl, BLE_ABS_PERD_HDL, 0, BLE_ABS_ADV_STATUS_PERD_START);
            break;
        }

        case BLE_GAP_EVENT_ADV_OFF:
        {
            ble_abs_advertising_off_handler(p_instance_ctrl, p_event_data);
            break;
        }

        case BLE_GAP_EVENT_SCAN_TO:
        {
            ble_abs_scan_to_handler(p_instance_ctrl);
            break;
        }

        case BLE_GAP_EVENT_CONN_IND:
        {
            ble_abs_connection_indication_handler(p_instance_ctrl);
            break;
        }

        case BLE_GAP_EVENT_CONN_PARAM_UPD_REQ:
        {
            st_ble_gap_conn_upd_req_evt_t * p_conn_upd_req_evt_param =
                (st_ble_gap_conn_upd_req_evt_t *) p_event_data->p_param;

            st_ble_gap_conn_param_t conn_updt_param =
            {
                .conn_intv_min = p_conn_upd_req_evt_param->conn_intv_min,
                .conn_intv_max = p_conn_upd_req_evt_param->conn_intv_max,
                .conn_latency  = p_conn_upd_req_evt_param->conn_latency,
                .sup_to        = p_conn_upd_req_evt_param->sup_to,
            };

            R_BLE_GAP_UpdConn(p_conn_upd_req_evt_param->conn_hdl,
                              BLE_GAP_CONN_UPD_MODE_RSP,
                              BLE_GAP_CONN_UPD_ACCEPT,
                              &conn_updt_param);
            break;
        }

        case BLE_GAP_EVENT_RSLV_LIST_CONF_COMP:
        {
            ble_abs_conflict_resolving_handler(p_instance_ctrl, p_event_data);
            break;
        }

        case BLE_GAP_EVENT_RPA_EN_COMP:
        {
            p_instance_ctrl->set_privacy_status = 0;
            break;
        }

        case BLE_GAP_EVENT_PRIV_MODE_SET_COMP:
        {
            if (BLE_ABS_PV_STATUS_SET_MODE == p_instance_ctrl->set_privacy_status)
            {
                ble_status_t retval = BLE_SUCCESS;
                retval = R_BLE_GAP_EnableRpa(BLE_GAP_RPA_ENABLED);
                p_instance_ctrl->set_privacy_status = (BLE_SUCCESS == retval) ?
                                                      BLE_ABS_PV_STATUS_EN_RPA :
                                                      0;
            }

            break;
        }

        case BLE_GAP_EVENT_PAIRING_REQ:
        {
            st_ble_gap_pairing_info_evt_t * p_param;
            p_param = (st_ble_gap_pairing_info_evt_t *) p_event_data->p_param;
            R_BLE_GAP_ReplyPairing(p_param->conn_hdl, BLE_GAP_PAIRING_ACCEPT);
            break;
        }

        case BLE_GAP_EVENT_PAIRING_COMP:
        {
            if (FSP_SUCCESS == event_result)
            {
                st_ble_gap_pairing_info_evt_t * p_param;
                p_param = (st_ble_gap_pairing_info_evt_t *) p_event_data->p_param;
                ble_abs_secure_data_writeremkeys(p_instance_ctrl->p_cfg->p_flash_instance,
                                                 (ble_device_address_t *) (&p_param->bd_addr),
                                                 &p_param->auth_info);
            }

            break;
        }

        case BLE_GAP_EVENT_PEER_KEY_INFO:
        {
            st_ble_gap_peer_key_info_evt_t * p_param;
            p_param = (st_ble_gap_peer_key_info_evt_t *) p_event_data->p_param;
            ble_abs_secure_data_recvremkeys((ble_device_address_t *) (&p_param->bd_addr), &p_param->key_ex_param);
            break;
        }

        case BLE_GAP_EVENT_EX_KEY_REQ:
        {
            st_ble_gap_conn_hdl_evt_t * p_param;
            p_param = (st_ble_gap_conn_hdl_evt_t *) p_event_data->p_param;
            R_BLE_GAP_ReplyExKeyInfoReq(p_param->conn_hdl);
            break;
        }

        case BLE_GAP_EVENT_LTK_REQ:
        {
            st_ble_gap_ltk_req_evt_t * p_param;
            p_param = (st_ble_gap_ltk_req_evt_t *) p_event_data->p_param;
            R_BLE_GAP_ReplyLtkReq(p_param->conn_hdl, p_param->ediv, p_param->p_peer_rand, BLE_GAP_LTK_REQ_ACCEPT);
            break;
        }

        default:
        {
            break;
        }
    }

    (*p_instance_ctrl).abs_gap_callback(event_type, event_result, p_event_data);
}                                      /* End of function ble_abs_gap_callback() */

/*******************************************************************************************************************//**
 * Handler for Vendor Specific BLE_VS_EVENT_GET_RAND event.
 **********************************************************************************************************************/
static void ble_abs_random_handler (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                    st_ble_vs_evt_data_t          * p_event_data)
{
    if (p_instance_ctrl->set_privacy_status)
    {
        st_ble_vs_get_rand_comp_evt_t * p_random_parameter;
        p_random_parameter = (st_ble_vs_get_rand_comp_evt_t *) p_event_data->p_param;
        ble_abs_set_irk_to_resolving_list(p_instance_ctrl, p_random_parameter->p_rand);
    }
}                                      /* End of function ble_abs_random_handler() */

/*******************************************************************************************************************//**
 * Vendor Specific Event handler.
 **********************************************************************************************************************/
static void ble_abs_vendor_specific_callback (uint16_t               event_type,
                                              ble_status_t           event_result,
                                              st_ble_vs_evt_data_t * p_event_data)
{
    ble_abs_instance_ctrl_t * p_instance_ctrl = gp_instance_ctrl;

    switch (event_type)
    {
        case BLE_VS_EVENT_GET_RAND:
        {
            ble_abs_random_handler(p_instance_ctrl, p_event_data);
            break;
        }

        default:
        {
            break;
        }
    }

    if (p_instance_ctrl->abs_vendor_specific_callback)
    {
        p_instance_ctrl->abs_vendor_specific_callback(event_type, event_result, p_event_data);
    }
}                                      /* End of function ble_abs_vendor_specific_callback() */

/*** platform control functions added start ***/

void r_ble_rf_control_error (uint32_t err_no)
{
    FSP_PARAMETER_NOT_USED(err_no);
}

uint8_t r_ble_rf_power_save_mode (void)
{
    uint8_t ret = BLE_ABS_CFG_RF_DEEP_SLEEP_EN;

    return ret;
}

#if (BSP_CFG_RTOS == 2)
void r_ble_wake_up_task (void * EventGroupHandle)
{
    EventGroupHandle_t event_group_handle = (EventGroupHandle_t) EventGroupHandle;

    if (event_group_handle != NULL)
    {
        xEventGroupSetBits(event_group_handle, (EventBits_t) BLE_EVENT_PATTERN);
        portYIELD();
    }
}

void r_ble_wake_up_task_from_isr (void * EventGroupHandle)
{
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    EventGroupHandle_t event_group_handle = (EventGroupHandle_t) EventGroupHandle;

    if (event_group_handle != NULL)
    {
        xEventGroupSetBitsFromISR(event_group_handle,
                                  (EventBits_t) BLE_EVENT_PATTERN,
                                  &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

#endif

/*** platform control functions end ***/

/*** r_ble_sec_data functions added start ***/
#if (BLE_ABS_CFG_ENABLE_SECURE_DATA == 1)

/*******************************************************************************************************************//**
 * Write Local device Identity Address, IRK and/or CSRK in DataFlash.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_POINTER                     IRK(p_lc_id_addr or p_lc_irk) or CSRK(p_lc_csrk)
 *                                                     is specified and as NULL.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Write to DataFlash is failed.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_writelocinfo (flash_instance_t const * p_instance,
                                                   ble_device_address_t   * p_lc_id_addr,
                                                   uint8_t                * p_lc_irk,
                                                   uint8_t                * p_lc_csrk)
{
    uint32_t local_tmp_data[(BLE_ABS_SECURE_DATA_LOCAL_AREA_SIZE + BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE + 3) / 4];

    FSP_ASSERT(p_lc_id_addr);
    FSP_ASSERT(p_lc_irk);
    FSP_ASSERT(p_lc_csrk);

    FSP_ERROR_RETURN(FSP_SUCCESS == ble_abs_secure_data_flash_read(p_instance,
                                                                   BLE_ABS_SECURE_DATA_BASE_ADDR,
                                                                   (uint8_t *) local_tmp_data,
                                                                   BLE_ABS_SECURE_DATA_LOCAL_AREA_SIZE +
                                                                   BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE),
                     FSP_ERR_BLE_ABS_INVALID_OPERATION);

    if (NULL != p_lc_irk)
    {
        memcpy((uint8_t *) local_tmp_data + BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE, p_lc_irk, BLE_GAP_IRK_SIZE);
        memcpy(
            (uint8_t *) local_tmp_data + BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE + BLE_GAP_IRK_SIZE + BLE_GAP_CSRK_SIZE,
            p_lc_id_addr,
            BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE);
    }

    if (NULL != p_lc_csrk)
    {
        memcpy((uint8_t *) local_tmp_data + BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE + BLE_GAP_IRK_SIZE,
               p_lc_csrk,
               BLE_GAP_CSRK_SIZE);
    }

    local_tmp_data[0] = BLE_ABS_SECURE_DATA_MAGIC_NUMBER;

    FSP_ERROR_RETURN(FSP_SUCCESS == ble_abs_secure_data_flash_write(p_instance,
                                                                    BLE_ABS_SECURE_DATA_BASE_ADDR,
                                                                    (uint8_t *) local_tmp_data,
                                                                    BLE_ABS_SECURE_DATA_LOCAL_AREA_SIZE +
                                                                    BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE),
                     FSP_ERR_BLE_ABS_INVALID_OPERATION);

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_secure_data_writelocinfo() */

/*******************************************************************************************************************//**
 * Read Local device Identity Address and IRK and/or CSRK in DataFlash.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_POINTER                     IRK(p_lc_id_addr or p_lc_irk) or CSRK(p_lc_csrk)
 *                                                     is specified and as NULL.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Read to DataFlash is failed.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                           IRK and Identity Address not found.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_readlocinfo (flash_instance_t const * p_instance,
                                                  ble_device_address_t   * p_lc_id_addr,
                                                  uint8_t                * p_lc_irk,
                                                  uint8_t                * p_lc_csrk)
{
    fsp_err_t retval;
    uint8_t * p_loc_area;
    uint32_t  mgc_num;

    p_loc_area = malloc(BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE + BLE_ABS_SECURE_DATA_LOCAL_AREA_SIZE);
    FSP_ERROR_RETURN(NULL != p_loc_area, FSP_ERR_BLE_ABS_NOT_FOUND);

    retval = ble_abs_secure_data_flash_read(p_instance,
                                            BLE_ABS_SECURE_DATA_ADDR_MGN_DATA,
                                            p_loc_area,
                                            BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE +
                                            BLE_ABS_SECURE_DATA_LOCAL_AREA_SIZE);
    if (FSP_SUCCESS != retval)
    {
        free(p_loc_area);
        p_loc_area = NULL;
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == retval, FSP_ERR_BLE_ABS_INVALID_OPERATION);

    memcpy(&mgc_num, p_loc_area, BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE);
    if ((BLE_ABS_SECURE_DATA_MAGIC_NUMBER != mgc_num) && (NULL == p_loc_area))
    {
        free(p_loc_area);
        p_loc_area = NULL;
    }

    FSP_ERROR_RETURN(BLE_ABS_SECURE_DATA_MAGIC_NUMBER != mgc_num, FSP_ERR_BLE_ABS_NOT_FOUND);

    if ((NULL != p_lc_irk) && (NULL != p_lc_id_addr))
    {
        memcpy(p_lc_irk, &p_loc_area[BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE], BLE_GAP_IRK_SIZE);
        memcpy(p_lc_id_addr,
               &p_loc_area[BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE + BLE_GAP_IRK_SIZE + BLE_GAP_CSRK_SIZE],
               BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE);
    }

    if (NULL != p_lc_csrk)
    {
        memcpy(p_lc_csrk, &p_loc_area[BLE_ABS_SECURE_DATA_MANEGEMENT_DATA_SIZE + BLE_GAP_IRK_SIZE], BLE_GAP_CSRK_SIZE);
    }

    if (NULL == p_loc_area)
    {
        free(p_loc_area);
    }

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_secure_data_readlocinfo() */

/*******************************************************************************************************************//**
 * Receive remote keys for write in DataFlash.
 **********************************************************************************************************************/
static void ble_abs_secure_data_recvremkeys (ble_device_address_t * p_addr, st_ble_gap_key_ex_param_t * p_keys)
{
    if ((NULL == p_addr) || (NULL == p_keys))
    {
        return;
    }

    (void) p_addr;

    memcpy((uint8_t *) &gs_key_ex_param, (uint8_t *) p_keys, BLE_ABS_SECURE_DATA_REMOTE_KEY_ATTRIBUTE_SIZE); ///< key_ex_parma

    memcpy((uint8_t *) &gs_key_dist, (uint8_t *) p_keys->p_keys_info, BLE_ABS_SECURE_DATA_REMOTE_KEYS_SIZE); ///< keys
} /* End of function ble_abs_secure_data_recvremkeys() */

/*******************************************************************************************************************//**
 * Write Remote Keys in DataFlash.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_POINTER                     p_addr or p_keyinfo is specified as NULL.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Write to DataFlash is failed.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND              Memory allocation is failed.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_writeremkeys (flash_instance_t const * p_instance,
                                                   ble_device_address_t   * p_addr,
                                                   st_ble_gap_auth_info_t * p_keyinfo)
{
    fsp_err_t retval = FSP_SUCCESS;
    int32_t   entry;
    int32_t   op_code = BLE_SECD_UPD_BN_ADD;
    uint32_t  start_addr;
    uint8_t   bond_num;
    uint8_t * p_sec_data;

    FSP_ASSERT(p_addr);
    FSP_ASSERT(p_keyinfo);

    p_sec_data = malloc(BLE_ABS_SECURE_DATA_MAX_SIZE); ///< memory allocation
    FSP_ERROR_RETURN(NULL != p_sec_data, FSP_ERR_BLE_ABS_NOT_FOUND);

    retval = ble_abs_secure_data_flash_read(p_instance,
                                            BLE_ABS_SECURE_DATA_BASE_ADDR,
                                            p_sec_data,
                                            BLE_ABS_SECURE_DATA_MAX_SIZE); ///< read remote area
    if (FSP_SUCCESS != retval)
    {
        free(p_sec_data);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == retval, FSP_ERR_BLE_ABS_INVALID_OPERATION);

    retval = ble_abs_secure_data_find_entry(p_addr, &entry, p_sec_data);   ///< find entry with p_addr
    if (FSP_SUCCESS != retval)
    {
        retval = ble_abs_secure_data_find_entry(NULL, &entry, p_sec_data); ///< find empty entry
        if (FSP_SUCCESS != retval)
        {
            ble_abs_secure_data_find_oldest_entry(p_instance, &entry);     ///< find oldest entry

            op_code = BLE_SECD_UPD_BN_ADD_OVERWR;                          ///< found the entry for overwrite
        }
    }

    start_addr = BLE_ABS_SECURE_DATA_ADDR_REM_START + (uint32_t) entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE;

    memcpy(&p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE],
           (uint8_t *) p_addr,
           BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE);                                                       ///< addr

    gs_key_ex_param.p_keys_info = (st_ble_gap_key_dist_t *) (start_addr + BLE_ABS_SECURE_DATA_SECURITY_KEYS_OFFSET); ///< ex_key_param
    memcpy(&p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE +
                       BLE_ABS_SECURE_DATA_SECURITY_KEYS_INFOMATION_OFFSET],
           (uint8_t *) &gs_key_ex_param,
           BLE_ABS_SECURE_DATA_REMOTE_KEY_ATTRIBUTE_SIZE);

    memcpy(&p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE +
                       BLE_ABS_SECURE_DATA_SECURITY_KEYS_OFFSET],
           (uint8_t *) &gs_key_dist,
           BLE_ABS_SECURE_DATA_REMOTE_KEYS_SIZE); ///< keys

    memcpy(&p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE +
                       BLE_ABS_SECURE_DATA_SECURITY_INFOMATION_OFFSET],
           (uint8_t *) p_keyinfo,
           BLE_ABS_SECURE_DATA_REMOTE_KEYS_INFOMATION_SIZE);                                ///< keyinfo

    ble_abs_secure_data_update_bond_num(p_instance, entry, op_code, &bond_num, p_sec_data); ///< update bond order and the number of bonds.

    p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE +
               BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE] = bond_num;

    retval = ble_abs_secure_data_flash_write(p_instance,
                                             BLE_ABS_SECURE_DATA_BASE_ADDR,
                                             p_sec_data,
                                             BLE_ABS_SECURE_DATA_MAX_SIZE); ///< write to DataFlash
    free(p_sec_data);

    return retval;
} /* End of function ble_abs_secure_data_writeremkeys() */

/*******************************************************************************************************************//**
 * Set bonding information in DataFlash to Host Stack.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_POINTER                     p_addr or p_keys is specified as NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT                    Number of bonding information is out of range.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_init (flash_instance_t const * p_instance)
{
    uint8_t                in_bond_num = 0;
    uint8_t                out_bond_num;
    fsp_err_t              ret = FSP_SUCCESS;
    uint8_t              * p_sec_data;
    st_ble_gap_bond_info_t bond_info[BLE_ABS_CFG_NUMBER_BONDING] = {0};

    ret = ble_abs_secure_data_read_bond_info(p_instance, &in_bond_num, &p_sec_data, bond_info);
    FSP_ERROR_RETURN((FSP_SUCCESS == ret) || (FSP_ERR_BLE_ABS_NOT_FOUND == ret), ret); ///< Read bonding information from DataFlash.

    FSP_ERROR_RETURN(0 != in_bond_num, FSP_SUCCESS);                                   ///< No bonding information is written in DataFlash.

    R_BLE_GAP_SetBondInfo(bond_info, in_bond_num, &out_bond_num);                      ///< Set bonding information in DataFlash to Host Stack.

    /** bonding info buffer release */
    ble_abs_secure_data_release_bond_info_buf(p_sec_data);                             ///< bonding info buffer release

    return ret;
} /* End of function ble_abs_secure_data_init() */

/*******************************************************************************************************************//**
 * Find entry.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                           Empty entry is not found.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_find_entry (ble_device_address_t * p_dev_addr,
                                                 int32_t              * p_entry,
                                                 uint8_t              * p_sec_data)
{
    ble_device_address_t * p_addr;
    int32_t                i;
    uint32_t               mgc_num = BLE_ABS_SECURE_DATA_MAGIC_NUMBER;
    fsp_err_t              retval  = FSP_ERR_BLE_ABS_NOT_FOUND;

    FSP_ERROR_RETURN((NULL == p_dev_addr) ||
                     (0 == memcmp(p_sec_data, (uint8_t *) &mgc_num, BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE)),
                     FSP_ERR_BLE_ABS_NOT_FOUND); ///< check magic number

    p_addr = (NULL == p_dev_addr) ? (ble_device_address_t *) &invalid_rem_addr : p_dev_addr;

    for (i = 0; i < BLE_ABS_CFG_NUMBER_BONDING; i++)
    {
        if (0 ==
            memcmp(&p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + i *
                               BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE],
                   p_addr,
                   BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE))
        {
            *p_entry = i;
            retval   = FSP_SUCCESS;
        }
    }

    return retval;
}                                      /* End of function ble_abs_secure_data_find_entry() */

/*******************************************************************************************************************//**
 * Find the oldest entry.
 **********************************************************************************************************************/
static void ble_abs_secure_data_find_oldest_entry (flash_instance_t const * p_instance, int32_t * p_entry)
{
    uint8_t bond_order;
    int32_t out_bond;

    ble_abs_secure_data_flash_read(p_instance,
                                   BLE_ABS_SECURE_DATA_ADDR_MGN_DATA + BLE_ABS_SECURE_DATA_OUT_BONDING_OFFSET,
                                   &bond_order,
                                   1);
    out_bond = (int32_t) bond_order;
    *p_entry = out_bond;
}                                      /* End of function ble_abs_secure_data_find_oldest_entry() */

/*******************************************************************************************************************//**
 * Update Bond Number
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Magic Numver read or write failuire.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_update_bond_num (flash_instance_t const * p_instance,
                                                      int32_t                  entry,
                                                      int32_t                  op_code,
                                                      uint8_t                * p_alloc_bond_num,
                                                      uint8_t                * p_sec_data)
{
    fsp_err_t retval = FSP_ERR_BLE_ABS_INVALID_OPERATION;
    uint8_t   bond_num;
    uint8_t   bond_order;

    bond_num = p_sec_data[BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE];

    switch (op_code)
    {
        case BLE_SECD_UPD_BN_ADD:
        case BLE_SECD_UPD_BN_ADD_OVERWR:
        {
            /* update bond_num */
            if (BLE_ABS_SECURE_DATA_UPDATE_BOND_NUMBER_FF == bond_num)
            {
                bond_num = 1;
                p_sec_data[BLE_ABS_SECURE_DATA_OUT_BONDING_OFFSET] = 0;
                uint32_t mgc_num = BLE_ABS_SECURE_DATA_MAGIC_NUMBER;
                memcpy(p_sec_data, (uint8_t *) &mgc_num, BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE);
            }
            else if (BLE_ABS_CFG_NUMBER_BONDING <= bond_num)
            {
                bond_num = BLE_ABS_CFG_NUMBER_BONDING;
            }
            else
            {
                bond_num++;
            }

            p_sec_data[BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE] = bond_num;

            /* update bond order */
            if (BLE_SECD_UPD_BN_ADD_OVERWR == op_code)
            {
                ble_abs_secure_data_update_bond_order(p_instance, entry, p_sec_data, 1);
            }

            *p_alloc_bond_num = bond_num;
            retval            = FSP_SUCCESS;
            break;
        }

        default:                       /* BLE_SECD_UPD_BN_DEL & BLE_SECD_UPD_BN_ALL_DEL */
        {
            if (BLE_ABS_CFG_NUMBER_BONDING >= bond_num)
            {
                /* update bond_num */
                if ((BLE_SECD_UPD_BN_ALL_DEL == op_code) || (0 == bond_num - 1))
                {
                    bond_num = BLE_ABS_SECURE_DATA_UPDATE_BOND_NUMBER_FF;
                    p_sec_data[BLE_ABS_SECURE_DATA_OUT_BONDING_OFFSET] = BLE_ABS_SECURE_DATA_UPDATE_BOND_NUMBER_FF;
                }
                else
                {
                    bond_num = (uint8_t) (bond_num - 1);
                }

                p_sec_data[BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE] = bond_num;

                if (BLE_ABS_SECURE_DATA_UPDATE_BOND_NUMBER_FF != bond_num)
                {
                    bond_order = p_sec_data[BLE_ABS_SECURE_DATA_ADDR_REM_START +
                                            (uint32_t) entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE +
                                            BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE];
                    ble_abs_secure_data_update_bond_order(p_instance, entry, p_sec_data, bond_order);
                }

                retval = FSP_SUCCESS;
            }

            break;
        }
    }

    return retval;
}                                      /* End of function ble_abs_secure_data_update_bond_num() */

/*******************************************************************************************************************//**
 * Check entry validation
 **********************************************************************************************************************/
static void ble_abs_secure_data_update_bond_order (flash_instance_t const * p_instance,
                                                   int32_t                  entry,
                                                   uint8_t                * p_sec_data,
                                                   uint8_t                  bond_order)
{
    fsp_err_t retval = FSP_ERR_BLE_ABS_INVALID_OPERATION;
    int32_t   i;

    for (i = 0; i < BLE_ABS_CFG_NUMBER_BONDING; i++)
    {
        if (entry != i)
        {
            retval = ble_abs_secure_data_is_valid_entry(p_instance, i);
            if (FSP_SUCCESS != retval)
            {
                continue;
            }

            uint8_t tmp_order;
            tmp_order =
                p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + i * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE +
                           BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE];

            if (bond_order < tmp_order)
            {
                tmp_order = (uint8_t) (tmp_order - 1);
                p_sec_data[BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + i * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE +
                           BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE] = tmp_order;
                if (1 == tmp_order)
                {
                    p_sec_data[BLE_ABS_SECURE_DATA_OUT_BONDING_OFFSET] = (uint8_t) i;
                }
            }
        }
    }
}                                      /* End of function ble_abs_secure_data_update_bond_order() */

/*******************************************************************************************************************//**
 * Check entry validation
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Read BD_ADDR is failed.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                           invalid entry
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_is_valid_entry (flash_instance_t const * p_instance, int32_t entry)
{
    uint8_t  bd_addr[BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE];
    uint8_t  invalid_bd_addr[BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE];
    uint32_t start_addr;

    start_addr = BLE_ABS_SECURE_DATA_ADDR_REM_START + (uint32_t) entry * BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE;

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     ble_abs_secure_data_flash_read(p_instance,
                                                    start_addr,
                                                    bd_addr,
                                                    BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE),
                     FSP_ERR_BLE_ABS_INVALID_OPERATION);

    memset(invalid_bd_addr, BLE_ABS_SECURE_DATA_BOND_ADDRESS_FF, BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE);
    FSP_ERROR_RETURN(0 != memcmp(bd_addr, invalid_bd_addr, BLE_ABS_SECURE_DATA_BLUETOOTH_DEVICE_ADDRESS_SIZE),
                     FSP_ERR_BLE_ABS_NOT_FOUND);

    return FSP_SUCCESS;
}                                      /* End of function ble_abs_secure_data_is_valid_entry() */

/*******************************************************************************************************************//**
 * Read Remote bonding information in DataFlash.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND              Memory allocation is failed.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                           No security data is stored in DataFlash.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_read_bond_info (flash_instance_t const * p_instance,
                                                     uint8_t                * p_out_bond_num,
                                                     uint8_t               ** pp_sec_data,
                                                     st_ble_gap_bond_info_t * p_bond_info)
{
    fsp_err_t retval = FSP_SUCCESS;
    int32_t   i;
    uint32_t  start_addr;
    uint8_t * p_bonds;
    uint32_t  magic_num;

    *pp_sec_data = malloc(BLE_ABS_SECURE_DATA_MAX_SIZE);
    p_bonds      = *pp_sec_data;
    FSP_ERROR_RETURN(NULL != p_bonds, FSP_ERR_BLE_ABS_NOT_FOUND);

    ble_abs_secure_data_flash_read(p_instance,
                                   (uint32_t) BLE_ABS_SECURE_DATA_BASE_ADDR,
                                   p_bonds,
                                   BLE_ABS_SECURE_DATA_MAX_SIZE);

    /** check magic number and bond number */
    *p_out_bond_num = 0;
    memcpy((uint8_t *) &magic_num, p_bonds, BLE_ABS_SECURE_DATA_MAGIC_NUMBER_SIZE);
    if ((BLE_ABS_SECURE_DATA_MAGIC_NUMBER != magic_num) ||
        (BLE_ABS_SECURE_DATA_BOND_CHECK_FF == p_bonds[BLE_ABS_SECURE_DATA_BONDING_NUMBER_OFFSET]) ||
        (0x00 == p_bonds[BLE_ABS_SECURE_DATA_BONDING_NUMBER_OFFSET]))
    {
        free(p_bonds);
        retval = FSP_ERR_BLE_ABS_NOT_FOUND;
    }

    FSP_ERROR_RETURN((retval != FSP_ERR_BLE_ABS_NOT_FOUND), FSP_ERR_BLE_ABS_NOT_FOUND);

    if (BLE_ABS_CFG_NUMBER_BONDING < p_bonds[BLE_ABS_SECURE_DATA_BONDING_NUMBER_OFFSET])
    {
        free(p_bonds);
        retval = FSP_ERR_BLE_ABS_NOT_FOUND;
    }

    FSP_ERROR_RETURN((retval != FSP_ERR_BLE_ABS_NOT_FOUND), FSP_ERR_BLE_ABS_NOT_FOUND);

    for (i = 0; i < p_bonds[BLE_ABS_SECURE_DATA_BONDING_NUMBER_OFFSET]; i++)
    {
        start_addr = BLE_ABS_SECURE_DATA_SECURITY_REMOTE_OFFSET + (uint32_t) i *
                     BLE_ABS_SECURE_DATA_REMOTE_BONDING_SIZE;
        p_bond_info[i].p_addr      = (st_ble_dev_addr_t *) (p_bonds + start_addr);
        p_bond_info[i].p_auth_info =
            (st_ble_gap_auth_info_t *) (p_bonds + start_addr + BLE_ABS_SECURE_DATA_SECURITY_INFOMATION_OFFSET);
        p_bond_info[i].p_keys =
            (st_ble_gap_key_ex_param_t *) (p_bonds + start_addr + BLE_ABS_SECURE_DATA_SECURITY_KEYS_INFOMATION_OFFSET);
        p_bond_info[i].p_keys->p_keys_info =
            (st_ble_gap_key_dist_t *) (p_bonds + start_addr + BLE_ABS_SECURE_DATA_SECURITY_KEYS_OFFSET);
        (*p_out_bond_num)++;
    }

    return retval;
}                                      /* End of function ble_abs_secure_data_read_bond_info() */

/*******************************************************************************************************************//**
 * Release bonding information buffer.
 **********************************************************************************************************************/
static void ble_abs_secure_data_release_bond_info_buf (uint8_t * p_sec_data)
{
    free(p_sec_data);
}                                      /* End of function ble_abs_secure_data_release_bond_info_buf() */

#else                                  /* (BLE_ABS_CFG_ENABLE_SECURE_DATA == 1) */

/*******************************************************************************************************************//**
 * Write Local device Identity Address, IRK and/or CSRK in DataFlash.
 * @retval FSP_ERR_UNSUPPORTED                                 This feature is not supported in this configuration.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_writelocinfo (flash_instance_t const * p_instance,
                                                   ble_device_address_t   * p_lc_id_addr,
                                                   uint8_t                * p_lc_irk,
                                                   uint8_t                * p_lc_csrk)
{
    (void) p_instance;
    (void) p_lc_id_addr;
    (void) p_lc_irk;
    (void) p_lc_csrk;

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Read Local device Identity Address and IRK and/or CSRK in DataFlash.
 * @retval FSP_ERR_UNSUPPORTED                                 This feature is not supported in this configuration.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_readlocinfo (flash_instance_t const * p_instance,
                                                  ble_device_address_t   * p_lc_id_addr,
                                                  uint8_t                * p_lc_irk,
                                                  uint8_t                * p_lc_csrk)
{
    (void) p_instance;
    (void) p_lc_id_addr;
    (void) p_lc_irk;
    (void) p_lc_csrk;

    return FSP_ERR_UNSUPPORTED;
}

static void ble_abs_secure_data_recvremkeys (ble_device_address_t * p_addr, st_ble_gap_key_ex_param_t * p_keys)
{
    (void) p_addr;
    (void) p_keys;
}

/*******************************************************************************************************************//**
 * Write Remote Keys in DataFlash.
 * @retval FSP_ERR_UNSUPPORTED                                 This feature is not supported in this configuration.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_writeremkeys (flash_instance_t const * p_instance,
                                                   ble_device_address_t   * p_addr,
                                                   st_ble_gap_auth_info_t * p_keyinfo)
{
    (void) p_instance;
    (void) p_addr;
    (void) p_keyinfo;

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Set bonding information in DataFlash to Host Stack.
 * @retval FSP_ERR_UNSUPPORTED                                 This feature is not supported in this configuration.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_secure_data_init (flash_instance_t const * p_instance)
{
    (void) p_instance;

    return FSP_ERR_UNSUPPORTED;
}

#endif                                 /* (BLE_ABS_CFG_ENABLE_SECURE_DATA == 1) */

/**************************************************************************************//**
 * Read the value of the specified data flash
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    parameter is invalid.
 *****************************************************************************************/
static fsp_err_t ble_abs_secure_data_flash_read (flash_instance_t const * p_instance,
                                                 uint32_t                 addr,
                                                 uint8_t                * buff,
                                                 uint16_t                 len)
{
    fsp_err_t    err       = FSP_SUCCESS;
    uint8_t    * p_address = (uint8_t *) addr;
    flash_info_t info;

    /* Open driver */
    err = p_instance->p_api->open(p_instance->p_ctrl, p_instance->p_cfg);

    /* Check for a valid address. */
    if (FSP_SUCCESS != err)
    {
        err = p_instance->p_api->infoGet(p_instance->p_ctrl, &info);

        if (((addr) < info.data_flash.p_block_array->block_section_st_addr) ||
            ((addr + len) >= info.data_flash.p_block_array->block_section_end_addr))
        {
            err = FSP_ERR_INVALID_ARGUMENT;
        }
    }

    /* Directly read data flush*/
    while ((len--) && (FSP_SUCCESS == err))
    {
        *buff++ = *p_address++;
    }

    /* Close driver */
    p_instance->p_api->close(p_instance->p_ctrl);

    return err;
}

/**************************************************************************************//**
 * Write data flash and Read data that has already been written and overwrite the value.
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT                    parameter is invalid.
 *****************************************************************************************/
static fsp_err_t ble_abs_secure_data_flash_write (flash_instance_t const * p_instance,
                                                  uint32_t                 addr,
                                                  uint8_t                * buff,
                                                  uint16_t                 len)
{
    fsp_err_t    err        = FSP_SUCCESS;
    uint8_t    * block_addr = (uint8_t *) (addr & ~BLE_ABS_SECURE_DATA_BLOCK_SIZE_MASK);
    uint16_t     offset     = (uint16_t) (addr & BLE_ABS_SECURE_DATA_BLOCK_SIZE_MASK);
    uint32_t     i;
    flash_info_t info;
    uint8_t      temporary_buffer[BLE_ABS_SECURE_DATA_BLOCK_SIZE];

    /* Open driver */
    if (FSP_SUCCESS != err)
    {
        err = p_instance->p_api->open(p_instance->p_ctrl, p_instance->p_cfg);
    }

    /* Check for a valid address. */
    if (FSP_SUCCESS != err)
    {
        err = p_instance->p_api->infoGet(p_instance->p_ctrl, &info);

        if (((addr) < info.data_flash.p_block_array->block_section_st_addr) ||
            ((addr + len) >= info.data_flash.p_block_array->block_section_end_addr))
        {
            err = FSP_ERR_INVALID_ARGUMENT;
        }
    }

    while (FSP_SUCCESS != err)
    {
        /* set write data */
        for (i = 0; i < BLE_ABS_SECURE_DATA_BLOCK_SIZE; i++)
        {
            if ((i >= offset) && (i < (offset + len)))
            {
                temporary_buffer[i] = *buff++;
            }
            else
            {
                temporary_buffer[i] = block_addr[i];
            }
        }

        /* Erase data block */
        err = p_instance->p_api->erase(p_instance->p_ctrl, (uint32_t) block_addr, 1);

        /* Write data flash */
        if (FSP_SUCCESS != err)
        {
            err = p_instance->p_api->write(p_instance->p_ctrl,
                                           (uint32_t) temporary_buffer,
                                           (uint32_t) block_addr,
                                           BLE_ABS_SECURE_DATA_BLOCK_SIZE);
        }
    }

    /* Close driver */
    p_instance->p_api->close(p_instance->p_ctrl);

    return err;
}

uint8_t r_dflash_read (uint32_t addr, uint8_t * buff, uint16_t len) {
    ble_abs_secure_data_flash_read(gp_instance_ctrl->p_cfg->p_flash_instance, addr, buff, len);

    return FSP_SUCCESS;
}

uint8_t r_dflash_write (uint32_t addr, uint8_t * buff, uint16_t len) {
    ble_abs_secure_data_flash_write(gp_instance_ctrl->p_cfg->p_flash_instance, addr, buff, len);

    return FSP_SUCCESS;
}

/*** r_ble_sec_data functions added end ***/

static void ble_abs_timer_update_remaining_time_ms (ble_abs_instance_ctrl_t * const p_instance_ctrl, bool expired)
{
    uint32_t elapsed_time_ms = ble_abs_get_elapsed_time_ms(p_instance_ctrl->p_cfg->p_timer_instance,
                                                           expired,
                                                           p_instance_ctrl->current_timeout_ms,
                                                           &p_instance_ctrl->elapsed_timeout_ms);

    for (uint32_t i = 0; i < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT; i++)
    {
        if (BLE_TIMER_STATUS_STARTED == p_instance_ctrl->timer[i].status)
        {
            p_instance_ctrl->timer[i].remaining_time_ms -= elapsed_time_ms;
        }
    }
}

static uint32_t ble_abs_timer_alloc_timer (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    for (uint32_t i = 0; i < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT; i++)
    {
        if (p_instance_ctrl->timer[i].status == BLE_TIMER_STATUS_FREE)
        {
            p_instance_ctrl->timer[i].status = BLE_TIMER_STATUS_IDLE;

            return i;
        }
    }

    return BLE_TIMER_INVALID_HDL;
}

static void ble_abs_timer_free_timer (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl)
{
    p_instance_ctrl->timer[timer_hdl].status     = BLE_TIMER_STATUS_FREE;
    p_instance_ctrl->timer[timer_hdl].timer_hdl  = BLE_TIMER_INVALID_HDL;
    p_instance_ctrl->timer[timer_hdl].timeout_ms = 0;
    p_instance_ctrl->timer[timer_hdl].type       = BLE_TIMER_ONE_SHOT;
    p_instance_ctrl->timer[timer_hdl].cb         = NULL;
}

static void ble_abs_timer_start_timer (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    uint32_t next_hdl = BLE_TIMER_INVALID_HDL;
    uint32_t shortest = BLE_ABS_TIMER_REMAIN_TIMESHORTEST;

    for (uint32_t i = 0; i < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT; i++)
    {
        if ((BLE_TIMER_STATUS_STARTED == p_instance_ctrl->timer[i].status) &&
            (shortest > p_instance_ctrl->timer[i].remaining_time_ms))
        {
            shortest = p_instance_ctrl->timer[i].remaining_time_ms;
            next_hdl = i;
        }
    }

    if (BLE_TIMER_INVALID_HDL != next_hdl)
    {
        ble_abs_start_hw_timer(p_instance_ctrl->p_cfg->p_timer_instance,
                               &p_instance_ctrl->current_timeout_ms,
                               &p_instance_ctrl->elapsed_timeout_ms,
                               p_instance_ctrl->timer[next_hdl].remaining_time_ms);
    }
}

static void ble_abs_timer_stop_timer (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    ble_abs_stop_hw_timer(p_instance_ctrl->p_cfg->p_timer_instance,
                          &p_instance_ctrl->current_timeout_ms,
                          &p_instance_ctrl->elapsed_timeout_ms);
}

static void ble_abs_timer_add_timer (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl)
{
    p_instance_ctrl->timer[timer_hdl].status            = BLE_TIMER_STATUS_STARTED;
    p_instance_ctrl->timer[timer_hdl].remaining_time_ms = p_instance_ctrl->timer[timer_hdl].timeout_ms;
}

static void ble_abs_timer_remove_timer (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl)
{
    p_instance_ctrl->timer[timer_hdl].status = BLE_TIMER_STATUS_IDLE;
}

static void ble_abs_timer_event_cb (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    for (uint32_t i = 0; i < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT; i++)
    {
        if (BLE_TIMER_STATUS_EXPIRED == p_instance_ctrl->timer[i].status)
        {
            p_instance_ctrl->timer[i].cb(i);

            if (BLE_TIMER_PERIODIC == p_instance_ctrl->timer[i].type)
            {
                ble_abs_timer_add_timer(p_instance_ctrl, i);
            }
            else
            {
                ble_abs_timer_remove_timer(p_instance_ctrl, i);
            }
        }
    }

    ble_abs_timer_stop_timer(p_instance_ctrl);
    ble_abs_timer_start_timer(p_instance_ctrl);
}

void ble_abs_timer_process_timer_expire (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    ble_abs_timer_update_remaining_time_ms(p_instance_ctrl, true);

    for (uint32_t i = 0; i < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT; i++)
    {
        if ((BLE_TIMER_STATUS_STARTED == p_instance_ctrl->timer[i].status) &&
            (0 == p_instance_ctrl->timer[i].remaining_time_ms))
        {
            p_instance_ctrl->timer[i].status = BLE_TIMER_STATUS_EXPIRED;
            ble_abs_timer_event_cb(p_instance_ctrl);
        }
    }

    ble_abs_timer_start_timer(p_instance_ctrl);
}

static void ble_abs_timer_init (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    for (uint32_t i = 0; i < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT; i++)
    {
        ble_abs_timer_free_timer(p_instance_ctrl, i);
    }

    ble_abs_init_hw_timer(p_instance_ctrl->p_cfg->p_timer_instance);
}

static void ble_abs_timer_terminate (ble_abs_instance_ctrl_t * const p_instance_ctrl)
{
    for (uint32_t i = 0; i < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT; i++)
    {
        ble_abs_timer_free_timer(p_instance_ctrl, i);
    }

    ble_abs_terminate_hw_timer(p_instance_ctrl->p_cfg->p_timer_instance);
}

/*******************************************************************************************************************//**
 * Create timer for communication.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_NOT_FOUND                   Couldn't find a valid timer.
 * @retval FSP_ERR_INVALID_ARGUMENT                    Invalid parameter is given.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_timer_create (ble_abs_instance_ctrl_t * const p_instance_ctrl,
                                       uint32_t                      * p_timer_hdl,
                                       uint32_t                        timeout_ms,
                                       uint8_t                         type,
                                       ble_abs_timer_cb_t              cb)
{
    uint32_t timer_hdl;

    FSP_ERROR_RETURN((NULL != p_timer_hdl) && (timeout_ms != 0) && (NULL != cb) &&
                     ((type == BLE_TIMER_ONE_SHOT) || (type == BLE_TIMER_PERIODIC)),
                     FSP_ERR_INVALID_ARGUMENT);

    timer_hdl = ble_abs_timer_alloc_timer(p_instance_ctrl);

    FSP_ERROR_RETURN((timer_hdl != BLE_TIMER_INVALID_HDL), FSP_ERR_BLE_ABS_NOT_FOUND);

    *p_timer_hdl = timer_hdl;

    p_instance_ctrl->timer[timer_hdl].timeout_ms = timeout_ms;
    p_instance_ctrl->timer[timer_hdl].type       = type;
    p_instance_ctrl->timer[timer_hdl].cb         = cb;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Delete timer for communication.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Invalid operation for the selected timer.
 * @retval FSP_ERR_INVALID_ARGUMENT                    Invalid timer handle.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_timer_delete (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t * p_timer_hdl)
{
    FSP_ERROR_RETURN((NULL != p_timer_hdl), FSP_ERR_INVALID_ARGUMENT);

    uint32_t timer_hdl = *p_timer_hdl;
    FSP_ERROR_RETURN((BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT > timer_hdl), FSP_ERR_BLE_ABS_INVALID_OPERATION);

    *p_timer_hdl = BLE_TIMER_INVALID_HDL;

    if (BLE_TIMER_STATUS_STARTED == p_instance_ctrl->timer[timer_hdl].status)
    {
        ble_abs_timer_stop(p_instance_ctrl, timer_hdl);
    }

    ble_abs_timer_update_remaining_time_ms(p_instance_ctrl, false);
    ble_abs_timer_stop_timer(p_instance_ctrl);
    ble_abs_timer_remove_timer(p_instance_ctrl, timer_hdl);
    ble_abs_timer_free_timer(p_instance_ctrl, timer_hdl);
    ble_abs_timer_start_timer(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Start timer for communication.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Invalid operation for the selected timer.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_timer_start (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl)
{
    FSP_ERROR_RETURN((timer_hdl < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT), FSP_ERR_BLE_ABS_INVALID_OPERATION);

    FSP_ERROR_RETURN((BLE_TIMER_STATUS_FREE != p_instance_ctrl->timer[timer_hdl].status) &&
                     (BLE_TIMER_STATUS_EXPIRED != p_instance_ctrl->timer[timer_hdl].status),
                     FSP_ERR_BLE_ABS_INVALID_OPERATION);

    ble_abs_timer_update_remaining_time_ms(p_instance_ctrl, false);
    ble_abs_timer_stop_timer(p_instance_ctrl);
    ble_abs_timer_add_timer(p_instance_ctrl, timer_hdl);
    ble_abs_timer_start_timer(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stop timer for communication.
 *
 * @retval FSP_SUCCESS                                 Operation succeeded.
 * @retval FSP_ERR_BLE_ABS_INVALID_OPERATION           Invalid operation for the selected timer.
 **********************************************************************************************************************/
static fsp_err_t ble_abs_timer_stop (ble_abs_instance_ctrl_t * const p_instance_ctrl, uint32_t timer_hdl)
{
    FSP_ERROR_RETURN((timer_hdl < BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT), FSP_ERR_BLE_ABS_INVALID_OPERATION);

    ble_abs_timer_update_remaining_time_ms(p_instance_ctrl, false);
    ble_abs_timer_stop_timer(p_instance_ctrl);
    ble_abs_timer_remove_timer(p_instance_ctrl, timer_hdl);
    ble_abs_timer_start_timer(p_instance_ctrl);

    return FSP_SUCCESS;
}

static void ble_abs_init_hw_timer (timer_instance_t const * p_instance)
{
    p_instance->p_api->open(p_instance->p_ctrl, p_instance->p_cfg);
}

static void ble_abs_terminate_hw_timer (timer_instance_t const * p_instance)
{
    p_instance->p_api->stop(p_instance->p_ctrl);
    p_instance->p_api->close(p_instance->p_ctrl);
}

static void ble_abs_start_hw_timer (timer_instance_t const * p_instance,
                                    uint32_t               * current_timeout_ms,
                                    uint32_t               * elapsed_timeout_ms,
                                    uint32_t                 timeout_ms)
{
    uint32_t     timer_count;
    timer_info_t timer_info;

    if (timeout_ms > BLE_ABS_TIMER_DEFAULT_TIMEOUT_MS)
    {
        *current_timeout_ms = BLE_ABS_TIMER_DEFAULT_TIMEOUT_MS;
    }
    else
    {
        *current_timeout_ms = timeout_ms;
    }

    *elapsed_timeout_ms = 0;

    p_instance->p_api->infoGet(p_instance->p_ctrl, &timer_info);

    timer_count = *current_timeout_ms * (timer_info.clock_frequency / BLE_ABS_TIMER_METRIC_PREFIX);
    p_instance->p_api->periodSet(p_instance->p_ctrl, timer_count);
    p_instance->p_api->start(p_instance->p_ctrl);
}

static void ble_abs_stop_hw_timer (timer_instance_t const * p_instance,
                                   uint32_t               * current_timeout_ms,
                                   uint32_t               * elapsed_timeout_ms)
{
    *current_timeout_ms = 0;
    *elapsed_timeout_ms = 0;
    p_instance->p_api->stop(p_instance->p_ctrl);
}

void ble_abs_hw_timer_callback (timer_callback_args_t * callback_args)
{
    ble_abs_instance_t * p_instance = (ble_abs_instance_t *) callback_args->p_context;
    ble_abs_timer_process_timer_expire(p_instance->p_ctrl);
}

static uint32_t ble_abs_get_elapsed_time_ms (timer_instance_t const * p_instance,
                                             bool                     expired,
                                             const uint32_t           current_timeout_ms,
                                             uint32_t               * elapsed_timeout_ms)
{
    uint32_t elapsed_time_from_prev_update_ms = 0;
    uint32_t total_elapsed_timeout_ms;

    timer_status_t status;
    timer_info_t   info;

    p_instance->p_api->statusGet(p_instance->p_ctrl, &status);
    p_instance->p_api->infoGet(p_instance->p_ctrl, &info);

    if (expired)
    {
        elapsed_time_from_prev_update_ms = current_timeout_ms - *elapsed_timeout_ms;
        *elapsed_timeout_ms              = current_timeout_ms;
    }
    else if (status.state == TIMER_STATE_COUNTING)
    {
        total_elapsed_timeout_ms         = (status.counter / info.clock_frequency) / BLE_ABS_TIMER_METRIC_PREFIX;
        elapsed_time_from_prev_update_ms = total_elapsed_timeout_ms - *elapsed_timeout_ms;
        *elapsed_timeout_ms              = total_elapsed_timeout_ms;
    }
    else if (0 == current_timeout_ms)
    {
        elapsed_time_from_prev_update_ms = 0;
    }
    else
    {
    }

    return elapsed_time_from_prev_update_ms;
}
