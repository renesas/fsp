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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup BLE_API BLE Interface
 * @brief Interface for Bluetooth Low Energy functions.
 *
 * @section BLE_API_SUMMARY Summary
 * The BLE interface for the Bluetooth Low Energy (BLE) peripheral provides Bluetooth Low Energy functionality.
 *
 * The Bluetooth Low Energy interface can be implemented by:
 * - @ref BLE
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_BLE_API_H
#define R_BLE_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

#include "r_ble_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BLE_API_VERSION_MAJOR    (1U)
#define BLE_API_VERSION_MINOR    (0U)

/* =================================================== Main Macro =================================================== */

/**
 * @def BLE_VERSION_MAJOR
 * BLE Module Major Version.
 */
#define BLE_VERSION_MAJOR        (0x0000)

/**
 * @def BLE_VERSION_MINOR
 * BLE Module Minor Version.
 */
#define BLE_VERSION_MINOR        (0x0009)

/**
 * @def BLE_LIB_ALL_FEATS
 * BLE Protocol Stack Library All Features type.
 */
#define BLE_LIB_ALL_FEATS        (0x00)

/**
 * @def BLE_LIB_BALANCE
 * BLE Protocol Stack Library Balance type.
 */
#define BLE_LIB_BALANCE          (0x01)

/**
 * @def BLE_LIB_COMPACT
 * BLE Protocol Stack Library Compacy type.
 */
#define BLE_LIB_COMPACT          (0x02)

/* =============================================== Spec Error Group ID ============================================== */
#define BLE_ERR_GROUP_HC         (0x1000)
#define BLE_ERR_GROUP_GAP        (0x2000)
#define BLE_ERR_GROUP_GATT       (0x3000)
#define BLE_ERR_GROUP_L2CAP      (0x4000)
#define BLE_ERR_GROUP_VS         (0x5000)

/******************************************************************************************************************//**
 * @typedef ble_status_t
 **********************************************************************************************************************/
typedef uint16_t ble_status_t;

/* error code */
enum RBLE_STATUS_enum
{
    BLE_SUCCESS = 0x0000,

    /* commom error code */
    BLE_ERR_INVALID_PTR         = 0x0001,
    BLE_ERR_INVALID_DATA        = 0x0002,
    BLE_ERR_INVALID_ARG         = 0x0003,
    BLE_ERR_INVALID_FUNC        = 0x0004,
    BLE_ERR_INVALID_CHAN        = 0x0005,
    BLE_ERR_INVALID_MODE        = 0x0006,
    BLE_ERR_UNSUPPORTED         = 0x0007,
    BLE_ERR_INVALID_STATE       = 0x0008,
    BLE_ERR_INVALID_OPERATION   = 0x0009,
    BLE_ERR_ALREADY_IN_PROGRESS = 0x000A,
    BLE_ERR_CONTEXT_FULL        = 0x000B,
    BLE_ERR_MEM_ALLOC_FAILED    = 0x000C,
    BLE_ERR_NOT_FOUND           = 0x000D,
    BLE_ERR_INVALID_HDL         = 0x000E,
    BLE_ERR_DISCONNECTED        = 0x000F,
    BLE_ERR_LIMIT_EXCEEDED      = 0x0010,
    BLE_ERR_RSP_TIMEOUT         = 0x0011,
    BLE_ERR_NOT_YET_READY       = 0x0012,
    BLE_ERR_UNSPECIFIED         = 0x0013,

    /* HCI Spec Error */
    BLE_ERR_HC_UNKNOWN_HCI_CMD              = 0x1001,
    BLE_ERR_HC_NO_CONN                      = 0x1002,
    BLE_ERR_HC_HW_FAIL                      = 0x1003,
    BLE_ERR_HC_PAGE_TO                      = 0x1004,
    BLE_ERR_HC_AUTH_FAIL                    = 0x1005,
    BLE_ERR_HC_KEY_MISSING                  = 0x1006,
    BLE_ERR_HC_MEM_FULL                     = 0x1007,
    BLE_ERR_HC_CONN_TO                      = 0x1008,
    BLE_ERR_HC_MAX_NUM_OF_CONN              = 0x1009,
    BLE_ERR_HC_MAX_NUM_OF_SCO_CONN          = 0x100A,
    BLE_ERR_HC_ACL_CONN_ALREADY_EXISTS      = 0x100B,
    BLE_ERR_HC_CMD_DISALLOWED               = 0x100C,
    BLE_ERR_HC_HOST_REJ_LIMITED_RESRC       = 0x100D,
    BLE_ERR_HC_HOST_REJ_SEC_REASONS         = 0x100E,
    BLE_ERR_HC_HOST_REJ_PERSONAL_DEV        = 0x100F,
    BLE_ERR_HC_HOST_TO                      = 0x1010,
    BLE_ERR_HC_UNSPRT_FEAT_OR_PARAM         = 0x1011,
    BLE_ERR_HC_INVALID_HCI_CMD_PARAM        = 0x1012,
    BLE_ERR_HC_OTHER_END_TERM_USER          = 0x1013,
    BLE_ERR_HC_OTHER_END_TERM_LOW_RESRC     = 0x1014,
    BLE_ERR_HC_OTHER_END_TERM_PW_OFF        = 0x1015,
    BLE_ERR_HC_CONN_TERM_BY_LOCAL_HOST      = 0x1016,
    BLE_ERR_HC_REPEATED_ATTEMPTS            = 0x1017,
    BLE_ERR_HC_PAIRING_NOT_ALLOWED          = 0x1018,
    BLE_ERR_HC_UNKNOWN_LMP_PDU              = 0x1019,
    BLE_ERR_HC_UNSPRT_REM_FEAT              = 0x101A,
    BLE_ERR_HC_SCO_OFFSET_REJ               = 0x101B,
    BLE_ERR_HC_SCO_INTERVAL_REJ             = 0x101C,
    BLE_ERR_HC_SCO_AIR_MODE_REJ             = 0x101D,
    BLE_ERR_HC_INVALID_LMP_PARAM            = 0x101E,
    BLE_ERR_HC_UNSPECIFIED_ERR              = 0x101F,
    BLE_ERR_HC_UNSPRT_LMP_PARAM_VAL         = 0x1020,
    BLE_ERR_HC_ROLE_CHANGE_NOT_ALLOWED      = 0x1021,
    BLE_ERR_HC_LMP_RSP_TO                   = 0x1022,
    BLE_ERR_HC_LMP_ERR_TX_COLLISION         = 0x1023,
    BLE_ERR_HC_LMP_PDU_NOT_ALLOWED          = 0x1024,
    BLE_ERR_HC_ENC_MODE_NOT_ACCEPTABLE      = 0x1025,
    BLE_ERR_HC_UNIT_KEY_USED                = 0x1026,
    BLE_ERR_HC_QOS_IS_NOT_SPRT              = 0x1027,
    BLE_ERR_HC_INSTANT_PASSED               = 0x1028,
    BLE_ERR_HC_PAIRING_UNIT_KEY_NOT_SPRT    = 0x1029,
    BLE_ERR_HC_DIFF_TRANSACTION_COLLISION   = 0x102A,
    BLE_ERR_HC_QOS_UNACCEPTABLE_PARAM       = 0x102C,
    BLE_ERR_HC_QOS_REJ                      = 0x102D,
    BLE_ERR_HC_CH_CLASSIFICATION_NOT_SPRT   = 0x102E,
    BLE_ERR_HC_INSUFFICIENT_SEC             = 0x102F,
    BLE_ERR_HC_PARAM_OUT_OF_MANDATORY_RANGE = 0x1030,
    BLE_ERR_HC_ROLE_SWITCH_PENDING          = 0x1032,
    BLE_ERR_HC_RESERVED_SLOT_VIOLATION      = 0x1034,
    BLE_ERR_HC_ROLE_SWITCH_FAIL             = 0x1035,
    BLE_ERR_HC_EXT_INQUIRY_RSP_TOO_LARGE    = 0x1036,
    BLE_ERR_HC_SSP_NOT_SPRT_BY_HOST         = 0x1037,
    BLE_ERR_HC_HOST_BUSY_PAIRING            = 0x1038,
    BLE_ERR_HC_CONN_REJ_NO_SUIT_CH_FOUND    = 0x1039,
    BLE_ERR_HC_CTRL_BUSY                    = 0x103A,
    BLE_ERR_HC_UNACCEPTEBALE_CONN_INTERVAL  = 0x103B,
    BLE_ERR_HC_ADV_TO = 0x103C,
    BLE_ERR_HC_CONN_TREM_DUE_TO_MIC_FAIL = 0x103D,
    BLE_ERR_HC_CONN_FAIL_TO_BE_EST       = 0x103E,
    BLE_ERR_HC_MAC_CONN_FAIL             = 0x103F,
    BLE_ERR_HC_COARSE_CLK_ADJUST_REJ     = 0x1040,
    BLE_ERR_HC_TYPE0_SUBMAP_NOT_DEFINED  = 0x1041,
    BLE_ERR_HC_UNKNOWN_ADV_ID            = 0x1042,
    BLE_ERR_HC_LIMIT_REACHED             = 0x1043,
    BLE_ERR_HC_OP_CANCELLED_BY_HOST      = 0x1044,

    /* SMP Spec Error */
    BLE_ERR_SMP_LE_PASSKEY_ENTRY_FAIL        = 0x2001,
    BLE_ERR_SMP_LE_OOB_DATA_NOT_AVAILABLE    = 0x2002,
    BLE_ERR_SMP_LE_AUTH_REQ_NOT_MET          = 0x2003,
    BLE_ERR_SMP_LE_CONFIRM_VAL_NOT_MATCH     = 0x2004,
    BLE_ERR_SMP_LE_PAIRING_NOT_SPRT          = 0x2005,
    BLE_ERR_SMP_LE_INSUFFICIENT_ENC_KEY_SIZE = 0x2006,
    BLE_ERR_SMP_LE_CMD_NOT_SPRT              = 0x2007,
    BLE_ERR_SMP_LE_UNSPECIFIED_REASON        = 0x2008,
    BLE_ERR_SMP_LE_REPEATED_ATTEMPTS         = 0x2009,
    BLE_ERR_SMP_LE_INVALID_PARAM             = 0x200A,
    BLE_ERR_SMP_LE_DHKEY_CHECK_FAIL          = 0x200B,
    BLE_ERR_SMP_LE_NUM_COMP_FAIL             = 0x200C,
    BLE_ERR_SMP_LE_BREDR_PAIRING_IN_PROGRESS = 0x200D,
    BLE_ERR_SMP_LE_CT_KEY_GEN_NOT_ALLOWED    = 0x200E,
    BLE_ERR_SMP_LE_DISCONNECTED              = 0x200F,
    BLE_ERR_SMP_LE_TO              = 0x2011,
    BLE_ERR_SMP_LE_LOC_KEY_MISSING = 0x2014,

    /* GATT Spec Error */
    BLE_ERR_GATT_INVALID_HANDLE              = 0x3001,
    BLE_ERR_GATT_READ_NOT_PERMITTED          = 0x3002,
    BLE_ERR_GATT_WRITE_NOT_PERMITTED         = 0x3003,
    BLE_ERR_GATT_INVALID_PDU                 = 0x3004,
    BLE_ERR_GATT_INSUFFICIENT_AUTHENTICATION = 0x3005,
    BLE_ERR_GATT_REQUEST_NOT_SUPPORTED       = 0x3006,
    BLE_ERR_GATT_INVALID_OFFSET              = 0x3007,
    BLE_ERR_GATT_INSUFFICIENT_AUTHORIZATION  = 0x3008,
    BLE_ERR_GATT_PREPARE_WRITE_QUEUE_FULL    = 0x3009,
    BLE_ERR_GATT_ATTRIBUTE_NOT_FOUND         = 0x300A,
    BLE_ERR_GATT_ATTRIBUTE_NOT_LONG          = 0x300B,
    BLE_ERR_GATT_INSUFFICIENT_ENC_KEY_SIZE   = 0x300C,
    BLE_ERR_GATT_INVALID_ATTRIBUTE_LEN       = 0x300D,
    BLE_ERR_GATT_UNLIKELY_ERROR              = 0x300E,
    BLE_ERR_GATT_INSUFFICIENT_ENCRYPTION     = 0x300F,
    BLE_ERR_GATT_UNSUPPORTED_GROUP_TYPE      = 0x3010,
    BLE_ERR_GATT_INSUFFICIENT_RESOURCES      = 0x3011,

    /* defined in CSS */
    BLE_ERR_GATT_WRITE_REQ_REJECTED       = 0x30FC,
    BLE_ERR_GATT_CCCD_IMPROPERLY_CFG      = 0x30FD,
    BLE_ERR_GATT_PROC_ALREADY_IN_PROGRESS = 0x30FE,
    BLE_ERR_GATT_OUT_OF_RANGE             = 0x30FF,

    /* L2CAP Spec Error */
    BLE_ERR_L2CAP_PSM_NOT_SUPPORTED         = 0x4002,
    BLE_ERR_L2CAP_NO_RESOURCE               = 0x4004,
    BLE_ERR_L2CAP_INSUF_AUTHEN              = 0x4005,
    BLE_ERR_L2CAP_INSUF_AUTHOR              = 0x4006,
    BLE_ERR_L2CAP_INSUF_ENC_KEY_SIZE        = 0x4007,
    BLE_ERR_L2CAP_REFUSE_INSUF_ENC          = 0x4008,
    BLE_ERR_L2CAP_REFUSE_INVALID_SCID       = 0x4009,
    BLE_ERR_L2CAP_REFUSE_SCID_ALREADY_ALLOC = 0x400A,
    BLE_ERR_L2CAP_REFUSE_UNACCEPTABLE_PARAM = 0x400B,
};

/*******************************************************************************************************************//**
 * @} (end addtogroup BLE_API)
 **********************************************************************************************************************/

/* =================================================== GAP Macro ==================================================== */

/** @addtogroup GAP_API
 *  @ingroup BLE
 *  @{
 */

/**
 * @ingroup GAP_API
 * @def BLE_BD_ADDR_LEN
 * Bluetooth Device Address Size
 */
#define BLE_BD_ADDR_LEN                                (0x06)

/**
 * @def BLE_MASTER
 * Master Role.
 */
#define BLE_MASTER                                     (0x00)

/**
 * @def BLE_SLAVE
 * Slave Role.
 */
#define BLE_SLAVE                                      (0x01)

/* Bluetooth Device Address Type */

/**
 * @def BLE_GAP_ADDR_PUBLIC
 * Public Address.
 */
#define BLE_GAP_ADDR_PUBLIC                            (0x00)

/**
 * @def BLE_GAP_ADDR_RAND
 * Random Address.
 */
#define BLE_GAP_ADDR_RAND                              (0x01)

/**
 * @def BLE_GAP_ADDR_RPA_ID_PUBLIC
 * @brief Resolvable Private Address.
 * @details If the IRK of local device has not been registered in Resolving List,
 *          public address is used.
 */
#define BLE_GAP_ADDR_RPA_ID_PUBLIC                     (0x02)

/**
 * @def BLE_GAP_ADDR_RPA_ID_RANDOM
 * @brief Resolvable Private Address.
 * @details If the IRK of local device has not been registered in Resolving List,
 *          random address is used.
 */
#define BLE_GAP_ADDR_RPA_ID_RANDOM                     (0x03)

/* Adv Flag */

/**
 * @def BLE_GAP_AD_FLAGS_LE_LIM_DISC_MODE
 * @brief LE Limited Discoverable Mode flag used in AD type.
 */
#define BLE_GAP_AD_FLAGS_LE_LIM_DISC_MODE              (0x01)

/**
 * @def BLE_GAP_AD_FLAGS_LE_GEN_DISC_MODE
 * @brief LE General Discoverable Mode flag used in AD type.
 */
#define BLE_GAP_AD_FLAGS_LE_GEN_DISC_MODE              (0x02)

/**
 * @def BLE_GAP_AD_FLAGS_BR_EDR_NOT_SUPPORTED
 * @brief BR/EDR Not Supported flag used in AD type.
 */
#define BLE_GAP_AD_FLAGS_BR_EDR_NOT_SUPPORTED          (0x04)

/**
 * @def BLE_GAP_ADV_DATA_MODE
 * @brief Advertising data.
 */
#define BLE_GAP_ADV_DATA_MODE                          (0x00)

/**
 * @def BLE_GAP_SCAN_RSP_DATA_MODE
 * @brief Scan response data.
 */
#define BLE_GAP_SCAN_RSP_DATA_MODE                     (0x01)

/**
 * @def BLE_GAP_PERD_ADV_DATA_MODE
 * @brief Periodic advertising data.
 */
#define BLE_GAP_PERD_ADV_DATA_MODE                     (0x02)

/* Advertising channel map */

/**
 * @def BLE_GAP_ADV_CH_37
 * @brief Use 37 CH.
 */
#define BLE_GAP_ADV_CH_37                              (0x01)

/**
 * @def BLE_GAP_ADV_CH_38
 * @brief Use 38 CH.
 */
#define BLE_GAP_ADV_CH_38                              (0x02)

/**
 * @def BLE_GAP_ADV_CH_39
 * @brief Use 39 CH.
 */
#define BLE_GAP_ADV_CH_39                              (0x04)

/**
 * @def BLE_GAP_ADV_CH_ALL
 * @brief Use 37 - 39 CH.
 */
#define BLE_GAP_ADV_CH_ALL                             (0x07)

/* Scan Type */

/**
 * @def BLE_GAP_SCAN_PASSIVE
 * @brief Passive Scan.
 */
#define BLE_GAP_SCAN_PASSIVE                           (0x00)

/**
 * @def BLE_GAP_SCAN_ACTIVE
 * @brief Active Scan.
 */
#define BLE_GAP_SCAN_ACTIVE                            (0x01)

/*  Scan interval */

/**
 * @def BLE_GAP_SCAN_INTV_MIN
 * @brief Active Scan.
 */
#define BLE_GAP_SCAN_INTV_MIN                          (0x0004)

/*  Filter duplicates */

/**
 * @def BLE_GAP_SCAN_FILT_DUPLIC_DISABLE
 * @brief Duplicate filter disabled.
 */
#define BLE_GAP_SCAN_FILT_DUPLIC_DISABLE               (0x00)

/**
 * @def BLE_GAP_SCAN_FILT_DUPLIC_ENABLE
 * @brief Duplicate filter enabled.
 */
#define BLE_GAP_SCAN_FILT_DUPLIC_ENABLE                (0x01)

/**
 * @def BLE_GAP_SCAN_FILT_DUPLIC_ENABLE_FOR_PERIOD
 * @brief Duplicate filtering enabled, reset for each scan period.
 */
#define BLE_GAP_SCAN_FILT_DUPLIC_ENABLE_FOR_PERIOD     (0x02)

/*   Scan filter policy */

/**
 * @def BLE_GAP_SCAN_ALLOW_ADV_ALL
 * @brief Accept all advertising and scan response PDUs except directed advertising PDUs not addressed to local device.
 */
#define BLE_GAP_SCAN_ALLOW_ADV_ALL                     (0x00)

/**
 * @def BLE_GAP_SCAN_ALLOW_ADV_WLST
 * @brief Accept only advertising and scan response PDUs from remote devices
 *        whose address is registered in the White List.
 *        Directed advertising PDUs which are not addressed to local device is ignored.
 */
#define BLE_GAP_SCAN_ALLOW_ADV_WLST                    (0x01)

/**
 * @def BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED
 * @brief Accept all advertising and scan response PDUs except directed advertising PDUs
 *        whose the target address is identity address but doesn't address local device.
 *        However directed advertising PDUs whose the target address is the local resolvable private address
 *        are accepted.
 */
#define BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED         (0x02)

/**
 * @def BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED_WLST
 * @brief Accept all advertising and scan response PDUs.<BR/>
 *        The following are excluded.
 *        - Advertising and scan response PDUs where the advertiser's identity address is not in the White List.
 *        - Directed advertising PDUs whose the target address is identity address
 *          but doesn't address local device. However directed advertising PDUs
 *          whose the target address is the local resolvable private address are accepted.
 */
#define BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED_WLST    (0x03)

/*  Initiator Filter policy */

/**
 * @def BLE_GAP_INIT_FILT_USE_ADDR
 * @brief White List is not used.
 */
#define BLE_GAP_INIT_FILT_USE_ADDR                     (0x00)

/**
 * @def BLE_GAP_INIT_FILT_USE_WLST
 * @brief White List is used.
 */
#define BLE_GAP_INIT_FILT_USE_WLST                     (0x01)

/**
 * @def BLE_GAP_DATA_0_CLEAR
 * @brief Clear the advertising data/scan response data/periodic advertising data in the advertising set.
 */
#define BLE_GAP_DATA_0_CLEAR                           (0x01)

/**
 * @def BLE_GAP_DATA_0_DID_UPD
 * @brief Update Advertising DID without changing advertising data.
 */
#define BLE_GAP_DATA_0_DID_UPD                         (0x02)

/* Privacy Mode related Definitions */

/**
 * @def BLE_GAP_NET_PRIV_MODE
 * @brief Network Privacy Mode.
 */
#define BLE_GAP_NET_PRIV_MODE                          (0x00)

/**
 * @def BLE_GAP_DEV_PRIV_MODE
 * @brief Device Privacy Mode.
 */
#define BLE_GAP_DEV_PRIV_MODE                          (0x01)

/**
 * @def BLE_GAP_REM_FEATURE_SIZE
 * @brief The length of the features supported by a remote device.
 */
#define BLE_GAP_REM_FEATURE_SIZE                       (0x08)

/* Authorization Flag Definitions */

/**
 * @def BLE_GAP_NOT_AUTHORIZED
 * @brief Not authorize the remote device.
 */
#define BLE_GAP_NOT_AUTHORIZED                         (0x00)

/**
 * @def BLE_GAP_AUTHORIZED
 * @brief Authorize the remote device.
 */
#define BLE_GAP_AUTHORIZED                             (0x01)

/* Remove ADV Set related */

/**
 * @def BLE_GAP_RMV_ADV_SET_REM_OP
 * @brief Delete an advertising set.
 */
#define BLE_GAP_RMV_ADV_SET_REM_OP                     (0x01)

/**
 * @def BLE_GAP_RMV_ADV_SET_CLR_OP
 * @brief Delete all the advertising sets.
 */
#define BLE_GAP_RMV_ADV_SET_CLR_OP                     (0x02)

/* scan procedure type */

/**
 * @def BLE_GAP_SC_PROC_GEN
 * @brief General Discovery Procedure.
 */
#define BLE_GAP_SC_PROC_GEN                            (0x02)

/**
 * @def BLE_GAP_SC_PROC_LIM
 * @brief Limited Discovery Procedure.
 */
#define BLE_GAP_SC_PROC_LIM                            (0x01)

/**
 * @def BLE_GAP_SC_PROC_OBS
 * @brief Observation Procedure.
 */
#define BLE_GAP_SC_PROC_OBS                            (0x00)

/* White List Operation */
/* Resolvable List Operation */
/* Periodic advertiser List Operation */

/**
 * @def BLE_GAP_LIST_ADD_DEV
 * @brief Add the device to the list.
 */
#define BLE_GAP_LIST_ADD_DEV                (0x01)

/**
 * @def BLE_GAP_LIST_REM_DEV
 * @brief Delete the device from the list.
 */
#define BLE_GAP_LIST_REM_DEV                (0x02)

/**
 * @def BLE_GAP_LIST_CLR
 * @brief Clear the list.
 */
#define BLE_GAP_LIST_CLR                    (0x03)

/**
 * @def BLE_GAP_WHITE_LIST_MAX_ENTRY
 * @brief The maximum entry number of White List.
 */
#define BLE_GAP_WHITE_LIST_MAX_ENTRY        (0x04)

/**
 * @def BLE_GAP_RSLV_LIST_MAX_ENTRY
 * @brief The maximum entry number of Resolving List.
 */
#define BLE_GAP_RSLV_LIST_MAX_ENTRY         (0x08)

/**
 * @def BLE_GAP_PERD_LIST_MAX_ENTRY
 * @brief The maximum entry number of Periodic Advertiser List.
 */
#define BLE_GAP_PERD_LIST_MAX_ENTRY         (0x04)

/* Set Address Resolution */

/**
 * @def BLE_GAP_RPA_DISABLED
 * @brief Disable RPA generation/resolution.
 */
#define BLE_GAP_RPA_DISABLED                (0x00)

/**
 * @def BLE_GAP_RPA_ENABLED
 * @brief Enable RPA generation/resolution.
 */
#define BLE_GAP_RPA_ENABLED                 (0x01)

/* Set Local IRK type */

/**
 * @def BLE_GAP_RL_LOC_KEY_ALL_ZERO
 * @brief  All-zero IRK.
 */
#define BLE_GAP_RL_LOC_KEY_ALL_ZERO         (0x00)

/**
 * @def BLE_GAP_RL_LOC_KEY_REGISTERED
 * @brief  The IRK registered by R_BLE_GAP_SetLocIdInfo().
 */
#define BLE_GAP_RL_LOC_KEY_REGISTERED       (0x01)

/* Number of advertising set supported */

/**
 * @def BLE_MAX_NO_OF_ADV_SETS_SUPPORTED
 * @brief  The maximum number of advertising set for the Abstraction API.
 */
#define BLE_MAX_NO_OF_ADV_SETS_SUPPORTED    (BLE_ABS_CFG_RF_ADVERTISING_SET_MAXIMUM)

/* Advertising Properties  */
/* Legacy Advertising PDU */
#if (BLE_CFG_LIBRARY_TYPE == 0)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_IND
 * @brief  Connectable and scannable undirected Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_IND               (0x0013)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_DIRECT_IND
 * @brief  Connectable directed (low duty cycle) Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_DIRECT_IND        (0x0015)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_HDC_DIRECT_IND
 * @brief  Connectable directed (high duty cycle) Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_HDC_DIRECT_IND    (0x001D)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_SCAN_IND
 * @brief  Scannable undirected Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_SCAN_IND          (0x0012)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND
 * @brief  Non-connectable and non-scannable undirected Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND       (0x0010)

#else                                  /* (BLE_CFG_LIBRARY_TYPE == 0) */

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_IND
 * @brief  Connectable and scannable undirected Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_IND               (0x0000)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_DIRECT_IND
 * @brief  Connectable directed (low duty cycle) Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_DIRECT_IND        (0x0004)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_HDC_DIRECT_IND
 * @brief  Connectable directed (high duty cycle) Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_HDC_DIRECT_IND    (0x0001)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_SCAN_IND
 * @brief  Scannable undirected Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_SCAN_IND          (0x0002)

/**
 * @def BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND
 * @brief  Non-connectable and non-scannable undirected Legacy Advertising Packet.
 */
 #define BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND       (0x0003)

#endif                                 /* (BLE_CFG_LIBRARY_TYPE == 0) */

/* Extended Advertising PDU */

/**
 * @def BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_UNDIRECT
 * @brief  Connectable and non-scannable undirected Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_UNDIRECT        (0x0001)

/**
 * @def BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_DIRECT
 * @brief  Connectable and non-scannable directed (low duty cycle) Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_DIRECT          (0x0005)

/**
 * @def BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_HDC_DIRECT
 * @brief  Connectable and non-scannable directed (high duty cycle) Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_HDC_DIRECT      (0x000D)

/**
 * @def BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_UNDIRECT
 * @brief  Non-connectable and scannable undirected Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_UNDIRECT        (0x0002)

/**
 * @def BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_DIRECT
 * @brief  Non-connectable and scannable directed (low duty cycle) Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_DIRECT          (0x0006)

/**
 * @def BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_HDC_DIRECT
 * @brief  Non-connectable and scannable directed (high duty cycle) Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_HDC_DIRECT      (0x000E)

/**
 * @def BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_UNDIRECT
 * @brief  Non-connectable and non-scannable undirected Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_UNDIRECT      (0x0000)

/**
 * @def BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_DIRECT
 * @brief  Non-connectable and non-scannable directed (low duty cycle) Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_DIRECT        (0x0004)

/**
 * @def BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_HDC_DIRECT
 * @brief  Non-connectable and non-scannable directed (high duty cycle) Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_HDC_DIRECT    (0x000C)

/* Anonymous advertising  */

/**
 * @def BLE_GAP_EXT_PROP_ADV_ANONYMOUS
 * @brief  Omit the advertiser address from Extended Advertising Packet.
 */
#define BLE_GAP_EXT_PROP_ADV_ANONYMOUS                   (0x0020)

/**
 * @def BLE_GAP_EXT_PROP_ADV_INCLUDE_TX_POWER
 * @brief  Indicate that the advertising data includes TX Power.
 */
#define BLE_GAP_EXT_PROP_ADV_INCLUDE_TX_POWER            (0x0040)

/* Advertising Filter Policy */

/**
 * @def BLE_GAP_ADV_ALLOW_SCAN_ANY_CONN_ANY
 * @brief  Process scan and connection requests from all devices.
 */
#define BLE_GAP_ADV_ALLOW_SCAN_ANY_CONN_ANY              (0x00)

/**
 * @def BLE_GAP_ADV_ALLOW_SCAN_WLST_CONN_ANY
 * @brief  Process connection requests from all devices and scan requests from only devices that are in the White List.
 */
#define BLE_GAP_ADV_ALLOW_SCAN_WLST_CONN_ANY             (0x01)

/**
 * @def BLE_GAP_ADV_ALLOW_SCAN_ANY_CONN_WLST
 * @brief  Process scan requests from all devices and connection requests from only devices that are in the White List.
 */
#define BLE_GAP_ADV_ALLOW_SCAN_ANY_CONN_WLST             (0x02)

/**
 * @def BLE_GAP_ADV_ALLOW_SCAN_WLST_CONN_WLST
 * @brief  Process scan and connection requests from only devices in the White List.
 */
#define BLE_GAP_ADV_ALLOW_SCAN_WLST_CONN_WLST            (0x03)

/* Primary & Secondary Advertising PHY  */

/**
 * @def BLE_GAP_ADV_PHY_1M
 * @brief  Use 1M PHY.
 */
#define BLE_GAP_ADV_PHY_1M                               (0x01)

/**
 * @def BLE_GAP_ADV_PHY_2M
 * @brief  Use 2M PHY.
 */
#define BLE_GAP_ADV_PHY_2M                               (0x02)

/**
 * @def BLE_GAP_ADV_PHY_CD
 * @brief  Use Coded PHY.
 */
#define BLE_GAP_ADV_PHY_CD                               (0x03)

/* Scan Request Notification Enable */

/**
 * @def BLE_GAP_SCAN_REQ_NTF_DISABLE
 * @brief  Disable Scan Request Notification.
 */
#define BLE_GAP_SCAN_REQ_NTF_DISABLE                     (0x00)

/**
 * @def BLE_GAP_SCAN_REQ_NTF_ENABLE
 * @brief  Enable Scan Request Notification.
 */
#define BLE_GAP_SCAN_REQ_NTF_ENABLE                      (0x01)

/* Periodic Advertising Properties  */

/**
 * @def BLE_GAP_PERD_PROP_TX_POWER
 * @brief  Indicate that periodic advertising data includes Tx Power.
 */
#define BLE_GAP_PERD_PROP_TX_POWER                       (0x0040)

/**
 * @def BLE_GAP_INVALID_ADV_HDL
 * @brief  Invalid advertising handle.
 */
#define BLE_GAP_INVALID_ADV_HDL                          (0xFF)

/**
 * @def BLE_GAP_SET_PHYS_HOST_PREF_1M
 * @brief  Use 1M PHY.
 */
#define BLE_GAP_SET_PHYS_HOST_PREF_1M                    (0x01)

/**
 * @def BLE_GAP_SET_PHYS_HOST_PREF_2M
 * @brief  Use 2M PHY.
 */
#define BLE_GAP_SET_PHYS_HOST_PREF_2M                    (0x02)

/**
 * @def BLE_GAP_SET_PHYS_HOST_PREF_CD
 * @brief  Use Coded PHY.
 */
#define BLE_GAP_SET_PHYS_HOST_PREF_CD                    (0x04)

/**
 * @def BLE_GAP_SET_PHYS_OP_HOST_NO_PREF
 * @brief  No preferred coding.
 */
#define BLE_GAP_SET_PHYS_OP_HOST_NO_PREF                 (0x00)

/**
 * @def BLE_GAP_SET_PHYS_OP_HOST_PREF_S_2
 * @brief  Use S=2 coding.
 */
#define BLE_GAP_SET_PHYS_OP_HOST_PREF_S_2                (0x01)

/**
 * @def BLE_GAP_SET_PHYS_OP_HOST_PREF_S_8
 * @brief  Use S=8 coding.
 */
#define BLE_GAP_SET_PHYS_OP_HOST_PREF_S_8                (0x02)

/* connection update parameter */

/**
 * @def BLE_GAP_CONN_UPD_MODE_REQ
 * @brief  Request for updating the connection parameters.
 */
#define BLE_GAP_CONN_UPD_MODE_REQ                        (0x01)

/**
 * @def BLE_GAP_CONN_UPD_MODE_RSP
 * @brief  Reply a connection parameter update request.
 */
#define BLE_GAP_CONN_UPD_MODE_RSP                        (0x02)

/* connection update response  */

/**
 * @def BLE_GAP_CONN_UPD_ACCEPT
 * @brief  Accept the update request.
 */
#define BLE_GAP_CONN_UPD_ACCEPT                          (0x0000)

/**
 * @def BLE_GAP_CONN_UPD_REJECT
 * @brief  Reject the update request.
 */
#define BLE_GAP_CONN_UPD_REJECT                          (0x0001)

/* channel map size */

/**
 * @def BLE_GAP_CH_MAP_SIZE
 * @brief  The size of channel map.
 */
#define BLE_GAP_CH_MAP_SIZE                              (0x05)

/**
 * @def BLE_GAP_INVALID_CONN_HDL
 * @brief  Invalid Connection handle.
 */
#define BLE_GAP_INVALID_CONN_HDL                         (0xFFFF)

/**
 * @def BLE_GAP_NOT_USE_CONN_HDL
 * @brief  This macro indicates that connection handle is not used.
 */
#define BLE_GAP_NOT_USE_CONN_HDL                         BLE_GAP_INVALID_CONN_HDL

/**
 * @def BLE_GAP_INIT_CONN_HDL
 * @brief  Initial Connection handle.
 */
#define BLE_GAP_INIT_CONN_HDL                            BLE_GAP_INVALID_CONN_HDL

/**
 * @def BLE_GAP_PAIRING_ACCEPT
 * @brief  Accept a request regarding pairing.
 */
#define BLE_GAP_PAIRING_ACCEPT                           (0x00)

/**
 * @def BLE_GAP_PAIRING_REJECT
 * @brief  Reject a request regarding pairing.
 */
#define BLE_GAP_PAIRING_REJECT                           (0x01)

/**
 * @def BLE_GAP_LTK_REQ_ACCEPT
 * @brief  Reply for the LTK request.
 */
#define BLE_GAP_LTK_REQ_ACCEPT                           (0x00)

/**
 * @def BLE_GAP_LTK_REQ_DENY
 * @brief  Reject the LTK request.
 */
#define BLE_GAP_LTK_REQ_DENY                             (0x01)

/**
 * @def BLE_GAP_LESC_PASSKEY_ENTRY_STARTED
 * @brief  Notify that passkey entry started.
 */
#define BLE_GAP_LESC_PASSKEY_ENTRY_STARTED               (0x00)

/**
 * @def BLE_GAP_LESC_PASSKEY_DIGIT_ENTERED
 * @brief  Notify that passkey digit entered.
 */
#define BLE_GAP_LESC_PASSKEY_DIGIT_ENTERED               (0x01)

/**
 * @def BLE_GAP_LESC_PASSKEY_DIGIT_ERASED
 * @brief  Notify that passkey digit erased.
 */
#define BLE_GAP_LESC_PASSKEY_DIGIT_ERASED                (0x02)

/**
 * @def BLE_GAP_LESC_PASSKEY_CLEARED
 * @brief  Notify that passkey cleared.
 */
#define BLE_GAP_LESC_PASSKEY_CLEARED                     (0x03)

/**
 * @def BLE_GAP_LESC_PASSKEY_ENTRY_COMPLETED
 * @brief  Notify that passkey entry completed.
 */
#define BLE_GAP_LESC_PASSKEY_ENTRY_COMPLETED             (0x04)

/**
 * @def BLE_GAP_SEC_MITM_BEST_EFFORT
 * @brief  MITM Protection not required.
 */
#define BLE_GAP_SEC_MITM_BEST_EFFORT                     (0x00)

/**
 * @def BLE_GAP_SEC_MITM_STRICT
 * @brief  MITM Protection required.
 */
#define BLE_GAP_SEC_MITM_STRICT                          (0x01)

/**
 * @def BLE_GAP_KEY_DIST_ENCKEY
 * @brief  LTK
 */
#define BLE_GAP_KEY_DIST_ENCKEY                          (0x01)

/**
 * @def BLE_GAP_KEY_DIST_IDKEY
 * @brief  IRK and Identity Address.
 */
#define BLE_GAP_KEY_DIST_IDKEY                           (0x02)

/**
 * @def BLE_GAP_KEY_DIST_SIGNKEY
 * @brief  CSRK
 */
#define BLE_GAP_KEY_DIST_SIGNKEY                         (0x04)

/**
 * @def BLE_GAP_ID_ADDR_SIZE
 * @brief  The size of identity address.
 */
#define BLE_GAP_ID_ADDR_SIZE                             (0x07)

/**
 * @def BLE_GAP_IRK_SIZE
 * @brief  The size of IRK.
 */
#define BLE_GAP_IRK_SIZE                                 (0x10)

/**
 * @def BLE_GAP_CSRK_SIZE
 * @brief  The size of CSRK.
 */
#define BLE_GAP_CSRK_SIZE                                (0x10)

/**
 * @def BLE_GAP_LTK_SIZE
 * @brief  The size of LTK.
 */
#define BLE_GAP_LTK_SIZE                                 (0x10)

/**
 * @def BLE_GAP_EDIV_SIZE
 * @brief  The size of EDIV.
 */
#define BLE_GAP_EDIV_SIZE                                (0x02)

/**
 * @def BLE_GAP_RAND_64_BIT_SIZE
 * @brief The size of Rand.
 */
#define BLE_GAP_RAND_64_BIT_SIZE                         (0x08)

/**
 * @def BLE_GAP_UNAUTH_PAIRING
 * @brief Unauthenticated pairing.
 */
#define BLE_GAP_UNAUTH_PAIRING                           (0x01)

/**
 * @def BLE_GAP_AUTH_PAIRING
 * @brief Authenticated pairing.
 */
#define BLE_GAP_AUTH_PAIRING                             (0x02)

/**
 * @def BLE_GAP_LEGACY_PAIRING
 * @brief  Legacy pairing.
 */
#define BLE_GAP_LEGACY_PAIRING                           (0x01)

/**
 * @def BLE_GAP_LESC_PAIRING
 * @brief Secure Connections.
 */
#define BLE_GAP_LESC_PAIRING                             (0x02)

/**
 * @def BLE_GAP_BONDING_NONE
 * @brief The device doesn't support Bonding.
 */
#define BLE_GAP_BONDING_NONE                             (0x00)

/**
 * @def BLE_GAP_BONDING
 * @brief The device supports Bonding.
 */
#define BLE_GAP_BONDING                                  (0x01)

/**
 * @def BLE_GAP_IOCAP_DISPLAY_ONLY
 * @brief Display Only iocapability.
 * @details  Output function : Local device has the ability to display a 6 digit decimal number.\n
 *           Input function : None
 */
#define BLE_GAP_IOCAP_DISPLAY_ONLY                       (0x00)

/**
 * @def BLE_GAP_IOCAP_DISPLAY_YESNO
 * @brief Display Yes/No iocapability.
 * @details  Output function : Output function : Local device has the ability to display a 6 digit decimal number.\n
 *           Input function : Local device has the ability to indicate 'yes' or 'no'
 */
#define BLE_GAP_IOCAP_DISPLAY_YESNO                      (0x01)

/**
 * @def BLE_GAP_IOCAP_KEYBOARD_ONLY
 * @brief Keyboard Only iocapability.
 * @details  Output function : None\n
 *           Input function : Local device has the ability to input the number '0' - '9'.
 */
#define BLE_GAP_IOCAP_KEYBOARD_ONLY                      (0x02)

/**
 * @def BLE_GAP_IOCAP_NOINPUT_NOOUTPUT
 * @brief No Input No Output iocapability.
 * @details  Output function : None\n
 *           Input function : None
 */
#define BLE_GAP_IOCAP_NOINPUT_NOOUTPUT                   (0x03)

/**
 * @def BLE_GAP_IOCAP_KEYBOARD_DISPLAY
 * @brief Keyboard Display iocapability.
 * @details  Output function : Output function : Local device has the ability to display a 6 digit decimal number.\n
 *           Input function : Local device has the ability to input the number '0' - '9'.
 */
#define BLE_GAP_IOCAP_KEYBOARD_DISPLAY                   (0x04)

/**
 * @def BLE_GAP_OOB_DATA_NOT_PRESENT
 * @brief Reply that No OOB data has been received when pairing.
 */
#define BLE_GAP_OOB_DATA_NOT_PRESENT                     (0x00)

/**
 * @def BLE_GAP_OOB_DATA_PRESENT
 * @brief Reply that the OOB data has been received when pairing.
 */
#define BLE_GAP_OOB_DATA_PRESENT                         (0x01)

/**
 * @def BLE_GAP_SC_BEST_EFFORT
 * @brief Accept Legacy pairing and Secure Connections.
 */
#define BLE_GAP_SC_BEST_EFFORT                           (0x00)

/**
 * @def BLE_GAP_SC_STRICT
 * @brief Accept only Secure Connections.
 */
#define BLE_GAP_SC_STRICT                                (0x01)

/**
 * @def BLE_GAP_SC_KEY_PRESS_NTF_NOT_SPRT
 * @brief Not support for Key Press Notification.
 */
#define BLE_GAP_SC_KEY_PRESS_NTF_NOT_SPRT                (0x00)

/**
 * @def BLE_GAP_SC_KEY_PRESS_NTF_SPRT
 * @brief Support for Key Press Notification.
 */
#define BLE_GAP_SC_KEY_PRESS_NTF_SPRT                    (0x01)

/**
 * @def BLE_GAP_LEGACY_OOB_SIZE
 * @brief The size of Temporary Key for OOB in legacy pairing.
 */
#define BLE_GAP_LEGACY_OOB_SIZE                          (0x10)

/**
 * @def BLE_GAP_OOB_CONFIRM_VAL_SIZE
 * @brief The size of Confirmation Value for OOB in Secure Connections.
 */
#define BLE_GAP_OOB_CONFIRM_VAL_SIZE                     (0x10)

/**
 * @def BLE_GAP_OOB_RANDOM_VAL_SIZE
 * @brief The size of Rand for OOB in Secure Connections.
 */
#define BLE_GAP_OOB_RANDOM_VAL_SIZE                      (0x10)

/**
 * @def BLE_GAP_SEC_DEL_LOC_NONE
 * @brief Delete no local keys.
 */
#define BLE_GAP_SEC_DEL_LOC_NONE                         (0x00)

/**
 * @def BLE_GAP_SEC_DEL_LOC_IRK
 * @brief Delete local IRK.
 */
#define BLE_GAP_SEC_DEL_LOC_IRK                          (0x01)

/**
 * @def BLE_GAP_SEC_DEL_LOC_CSRK
 * @brief Delete local CSRK.
 */
#define BLE_GAP_SEC_DEL_LOC_CSRK                         (0x02)

/**
 * @def BLE_GAP_SEC_DEL_LOC_ALL
 * @brief Delete all local keys.
 */
#define BLE_GAP_SEC_DEL_LOC_ALL                          (0x03)

/**
 * @def BLE_GAP_SEC_DEL_REM_NONE
 * @brief Delete no remote device keys.
 */
#define BLE_GAP_SEC_DEL_REM_NONE                         (0x00)

/**
 * @def BLE_GAP_SEC_DEL_REM_SA
 * @brief Delete a key specified by the p_addr parameter.
 */
#define BLE_GAP_SEC_DEL_REM_SA                           (0x01)

/**
 * @def BLE_GAP_SEC_DEL_REM_NOT_CONN
 * @brief Delete keys of not connected remote devices.
 */
#define BLE_GAP_SEC_DEL_REM_NOT_CONN                     (0x02)

/**
 * @def BLE_GAP_SEC_DEL_REM_ALL
 * @brief Delete all remote device keys.
 */
#define BLE_GAP_SEC_DEL_REM_ALL                          (0x03)

/**@} (end addtogroup GAP_API)*/

/* =================================================== GATT Macro =================================================== */

/** @addtogroup GATT_SERVER_API
 *  @ingroup BLE
 *  @{
 */

/* GATT Common Macro */

/**
 * @ingroup GATT_SERVER_API
 * @def BLE_GATT_DEFAULT_MTU
 * @brief GATT Default MTU.
 */
#define BLE_GATT_DEFAULT_MTU                         (23)

/**
 * @def BLE_GATT_16_BIT_UUID_FORMAT
 * @brief GATT Identification for 16-bit UUID Format.
 */
#define BLE_GATT_16_BIT_UUID_FORMAT                  (0x01)

/**
 * @def BLE_GATT_128_BIT_UUID_FORMAT
 * @brief GATT Identification for 128-bit UUID Format.
 */
#define BLE_GATT_128_BIT_UUID_FORMAT                 (0x02)

/**
 * @def BLE_GATT_16_BIT_UUID_SIZE
 * @brief GATT 16-bit UUID Size.
 */
#define BLE_GATT_16_BIT_UUID_SIZE                    (2)

/**
 * @def BLE_GATT_128_BIT_UUID_SIZE
 * @brief GATT 128-bit UUID Size.
 */
#define BLE_GATT_128_BIT_UUID_SIZE                   (16)

/**
 * @def BLE_GATT_INVALID_ATTR_HDL_VAL
 * @brief GATT Invalid Attribute Handle Value.
 */
#define BLE_GATT_INVALID_ATTR_HDL_VAL                (0x0000)

/**
 * @def BLE_GATT_ATTR_HDL_START_RANGE
 * @brief GATT Attribute Handle Start Range.
 */
#define BLE_GATT_ATTR_HDL_START_RANGE                (0x0001)

/**
 * @def BLE_GATT_ATTR_HDL_END_RANGE
 * @brief GATT Attribute Handle End Range.
 */
#define BLE_GATT_ATTR_HDL_END_RANGE                  (0xFFFF)

/* GATT Server Macro */

/**
 * @def BLE_GATTS_CLI_CNFG_NOTIFICATION
 * @brief GATT Client Configuration values. Enable Notification.
 */
#define BLE_GATTS_CLI_CNFG_NOTIFICATION              (0x0001)

/**
 * @def BLE_GATTS_CLI_CNFG_INDICATION
 * @brief GATT Client Configuration values. Enable Indication.
 */
#define BLE_GATTS_CLI_CNFG_INDICATION                (0x0002)

/**
 * @def BLE_GATTS_CLI_CNFG_DEFAULT
 * @brief GATT Client Configuration values. Default value or disable notification/indication.
 */
#define BLE_GATTS_CLI_CNFG_DEFAULT                   (0x0000)

/**
 * @def BLE_GATTS_SER_CNFG_BROADCAST
 * @brief GATT Server Configuration values. Enable broadcast.
 */
#define BLE_GATTS_SER_CNFG_BROADCAST                 (0x0001)

/**
 * @def BLE_GATTS_SER_CNFG_DEFAULT
 * @brief GATT Server Configuration values. Default value.
 */
#define BLE_GATTS_SER_CNFG_DEFAULT                   (0x0000)

/**
 * @def BLE_GATTS_MAX_CB
 * @brief GATT Server Callback Number.
 */
#define BLE_GATTS_MAX_CB                             (15)

/* GATT Server Operation */

/**
 * @def BLE_GATTS_OP_CHAR_VALUE_READ_REQ
 * @brief Characteristic Value Local Read Operation.
 */
#define BLE_GATTS_OP_CHAR_VALUE_READ_REQ             (0x01)

/**
 * @def BLE_GATTS_OP_CHAR_VALUE_WRITE_REQ
 * @brief Characteristic Value Local Write Operation.
 */
#define BLE_GATTS_OP_CHAR_VALUE_WRITE_REQ            (0x02)

/**
 * @def BLE_GATTS_OP_CHAR_VALUE_WRITE_WITHOUT_REQ
 * @brief Characteristic Value Local Write Without Response Operation.
 */
#define BLE_GATTS_OP_CHAR_VALUE_WRITE_WITHOUT_REQ    (0x03)

/**
 * @def BLE_GATTS_OP_CHAR_CLI_CNFG_READ_REQ
 * @brief Characteristic Client Configuration Local Read Operation.
 */
#define BLE_GATTS_OP_CHAR_CLI_CNFG_READ_REQ          (0x11)

/**
 * @def BLE_GATTS_OP_CHAR_CLI_CNFG_WRITE_REQ
 * @brief Characteristic Client Configuration Local Write Operation.
 */
#define BLE_GATTS_OP_CHAR_CLI_CNFG_WRITE_REQ         (0x12)

/**
 * @def BLE_GATTS_OP_CHAR_SER_CNFG_READ_REQ
 * @brief Characteristic Server Configuration Local Read Operation.
 */
#define BLE_GATTS_OP_CHAR_SER_CNFG_READ_REQ          (0x21)

/**
 * @def BLE_GATTS_OP_CHAR_SER_CNFG_WRITE_REQ
 * @brief Characteristic Server Configuration Local Write Operation.
 */
#define BLE_GATTS_OP_CHAR_SER_CNFG_WRITE_REQ         (0x22)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_READ_REQ
 * @brief Characteristic Value Peer Read Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_READ_REQ              (0x81)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_WRITE_REQ
 * @brief Characteristic Value Peer Write Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_WRITE_REQ             (0x82)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_WRITE_CMD
 * @brief Characteristic Value Peer Write Command.
 */
#define BLE_GATTS_OP_CHAR_PEER_WRITE_CMD             (0x84)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_CLI_CNFG_READ_REQ
 * @brief Characteristic Client Configuration Peer Read Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_CLI_CNFG_READ_REQ     (0x91)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_CLI_CNFG_WRITE_REQ
 * @brief Characteristic Client Configuration Peer Write Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_CLI_CNFG_WRITE_REQ    (0x92)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_SER_CNFG_READ_REQ
 * @brief Characteristic Server Configuration Peer Read Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_SER_CNFG_READ_REQ     (0xA1)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_SER_CNFG_WRITE_REQ
 * @brief Characteristic Server Configuration Peer Write Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_SER_CNFG_WRITE_REQ    (0xA2)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_USR_DESC_READ_REQ
 * @brief Characteristic User Description Peer Read Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_USR_DESC_READ_REQ     (0xB1)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_USR_DESC_WRITE_REQ
 * @brief Characteristic User Description Peer Write Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_USR_DESC_WRITE_REQ    (0xB2)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_HLD_DESC_READ_REQ
 * @brief Characteristic Higher Layer Defined Descriptor Peer Read Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_HLD_DESC_READ_REQ     (0xF1)

/**
 * @def BLE_GATTS_OP_CHAR_PEER_HLD_DESC_WRITE_REQ
 * @brief Characteristic Higher Layer Defined Descriptor Peer Write Operation.
 */
#define BLE_GATTS_OP_CHAR_PEER_HLD_DESC_WRITE_REQ    (0xF2)

/**
 * @def BLE_GATTS_OP_CHAR_REQ_AUTHOR
 * @brief Operation Required Authorization.
 */
#define BLE_GATTS_OP_CHAR_REQ_AUTHOR                 (0x08)

/* GATT Database */

/**
 * @def BLE_GATT_DB_READ
 * @brief Allow clients to read.
 */
#define BLE_GATT_DB_READ                             (0x01)

/**
 * @def BLE_GATT_DB_WRITE
 * @brief Allow clients to write.
 */
#define BLE_GATT_DB_WRITE                            (0x02)

/**
 * @def BLE_GATT_DB_WRITE_WITHOUT_RSP
 * @brief Allow clients to write without response.
 */
#define BLE_GATT_DB_WRITE_WITHOUT_RSP                (0x04)

/**
 * @def BLE_GATT_DB_READ_WRITE
 * @brief Allow clients to access of all.
 */
#define BLE_GATT_DB_READ_WRITE \
    (BLE_GATT_DB_READ | BLE_GATT_DB_WRITE | BLE_GATT_DB_WRITE_WITHOUT_RSP)

/**
 * @def BLE_GATT_DB_NO_AUXILIARY_PROPERTY
 * @brief No auxiliary properties.
 */
#define BLE_GATT_DB_NO_AUXILIARY_PROPERTY         (0x00)

/**
 * @def BLE_GATT_DB_FIXED_LENGTH_PROPERTY
 * @brief Fixed length attribute value.
 */
#define BLE_GATT_DB_FIXED_LENGTH_PROPERTY         (0x01)

/**
 * @def BLE_GATT_DB_AUTHORIZATION_PROPERTY
 * @brief  Attributes requiring authorization.
 */
#define BLE_GATT_DB_AUTHORIZATION_PROPERTY        (0x02)

/**
 * @def BLE_GATT_DB_ATTR_DISABLED
 * @brief  The attribute is disabled.
 *         If this value is set, the attribute cannot be found and accessed by a GATT Client.
 */
#define BLE_GATT_DB_ATTR_DISABLED                 (0x10)

/**
 * @def BLE_GATT_DB_128_BIT_UUID_FORMAT
 * @brief Attribute with 128 bit UUID.
 */
#define BLE_GATT_DB_128_BIT_UUID_FORMAT           (0x20)

/**
 * @def BLE_GATT_DB_PEER_SPECIFIC_VAL_PROPERTY
 * @brief Attribute managed by each GATT Client.
 */
#define BLE_GATT_DB_PEER_SPECIFIC_VAL_PROPERTY    (0x40)

/**
 * @def BLE_GATT_DB_CONST_ATTR_VAL_PROPERTY
 * @brief Fixed attribute value.
 */
#define BLE_GATT_DB_CONST_ATTR_VAL_PROPERTY       (0x80)

/**
 * @def BLE_GATT_DB_SER_SECURITY_UNAUTH
 * @brief Unauthenticated pairing(Security Mode1 Security Level 2, Security Mode 2 Security Level 1).
 *        Unauthenticated pairing is required to access the service.
 */
#define BLE_GATT_DB_SER_SECURITY_UNAUTH           (0x00000001)

/**
 * @def BLE_GATT_DB_SER_SECURITY_AUTH
 * @brief Authenticated pairing(Security Mode1 Security Level 3, Security Mode 2 Security Level 2).
 *        Authenticated pairing is required to access the service.
 */
#define BLE_GATT_DB_SER_SECURITY_AUTH             (0x00000002)

/**
 * @def BLE_GATT_DB_SER_SECURITY_SECONN
 * @brief Authenticated LE secure connections that generates 16bytes LTK(Security Mode1 Security Level 4).
 *        Authenticated LE secure connections pairing that generates 16bytes LTK is required to access the service.
 *        If this bit is set, bit24-27 are ignored.
 */
#define BLE_GATT_DB_SER_SECURITY_SECONN           (0x00000004)

/**
 * @def BLE_GATT_DB_SER_SECURITY_ENC
 * @brief Encryption.
 *        Encryption by the LTK exchanged in pairing is required to access.
 */
#define BLE_GATT_DB_SER_SECURITY_ENC              (0x00000010)

/**
 * @def BLE_GATT_DB_SER_NO_SECURITY_PROPERTY
 * @brief No Security(Security Mode1 Security Level 1).
 */
#define BLE_GATT_DB_SER_NO_SECURITY_PROPERTY      (0x00000000)

/**
 * @def BLE_GATT_DB_SER_ENC_KEY_SIZE_DONT_CARE
 * @brief 7-byte or larger encryption key.
 */
#define BLE_GATT_DB_SER_ENC_KEY_SIZE_DONT_CARE    (0x00000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_7
 * @brief 7-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_7        (0x01000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_8
 * @brief 8-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_8        (0x02000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_9
 * @brief 9-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_9        (0x03000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_10
 * @brief 10-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_10       (0x04000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_11
 * @brief 11-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_11       (0x05000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_12
 * @brief 12-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_12       (0x06000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_13
 * @brief 13-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_13       (0x07000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_14
 * @brief 14-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_14       (0x08000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_15
 * @brief 15-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_15       (0x09000000)

/**
 * @def BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_16
 * @brief 16-byte encryption key.
 */
#define BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_16       (0x0A000000)

/******************************************************************************************************************//**
 * @enum e_r_ble_gatts_evt_t
 * @brief  GATT Server Event Identifier
 **********************************************************************************************************************/
typedef enum
{
    /**
     *  @brief  MTU Exchange Request has been received.
     *  @details
     *  This event notifies the application layer that a MTU Exchange Request PDU has been received from a GATT Client.
     *  Need to reply to the request by R_BLE_GATTS_RspExMtu().
     *
     * ## Event Code: 0x3002
     *
     *  ## Event Data:
     *  st_ble_gatts_ex_mtu_req_evt_t
     */
    BLE_GATTS_EVENT_EX_MTU_REQ = 0x3002,             //!< BLE_GATTS_EVENT_EX_MTU_REQ

    /**
     *  @brief   Read By Type Response has been sent.
     *  @details
     *  This event notifies the application layer that a Read By Type Response PDU has been sent
     *  from GATT Server to the GATT Client.
     *
     * ## Event Code: 0x3009
     *
     *  ## Event Data:
     *  st_ble_gatts_read_by_type_rsp_evt_t
     */
    BLE_GATTS_EVENT_READ_BY_TYPE_RSP_COMP = 0x3009,  //!< BLE_GATTS_EVENT_READ_BY_TYPE_RSP_COMP

    /**
     *  @brief   Read Response has been sent.
     *  @details
     *  This event notifies the application layer that a Read Response PDU has been sent
     *  from GATT Server to the GATT Client.
     *
     * ## Event Code: 0x300B
     *
     *  ## Event Data:
     *  st_ble_gatts_read_rsp_evt_t
     */
    BLE_GATTS_EVENT_READ_RSP_COMP = 0x300B,          //!< BLE_GATTS_EVENT_READ_RSP_COMP

    /**
     *  @brief   Read Blob Response has been sent.
     *  @details
     *  This event notifies the application layer that a Read Blob Response PDU has been sent
     *  from GATT Server to the GATT Client.
     *
     * ## Event Code: 0x300D
     *
     *  ## Event Data:
     *  st_ble_gatts_read_blob_rsp_evt_t
     */
    BLE_GATTS_EVENT_READ_BLOB_RSP_COMP = 0x300D,     //!< BLE_GATTS_EVENT_READ_BLOB_RSP_COMP

    /**
     *  @brief   Read Multiple Response has been sent.
     *  @details
     *  This event notifies the application layer that a Read Multiple Response PDU has been sent
     *  from GATT Server to the GATT Client.
     *
     * ## Event Code: 0x300F
     *
     *  ## Event Data:
     *  st_ble_gatts_read_multi_rsp_evt_t
     */
    BLE_GATTS_EVENT_READ_MULTI_RSP_COMP = 0x300F,    //!< BLE_GATTS_EVENT_READ_MULTI_RSP_COMP

    /**
     *  @brief   Write Response has been sent.
     *  @details
     *  This event notifies the application layer that a Write Response PDU has been sent
     *  from GATT Server to the GATT Client.
     *
     * ## Event Code: 0x3013
     *
     *  ## Event Data:
     *  st_ble_gatts_write_rsp_evt_t
     */
    BLE_GATTS_EVENT_WRITE_RSP_COMP = 0x3013,         //!< BLE_GATTS_EVENT_WRITE_RSP_COMP

    /**
     *  @brief   Prepare Write Response has been sent.
     *  @details
     *  This event notifies the application layer that a Prepare Write Response PDU has been sent
     *  from GATT Server to the GATT Client.
     *
     * ## Event Code: 0x3017
     *
     *  ## Event Data:
     *  st_ble_gatts_prepare_write_rsp_evt_t
     */
    BLE_GATTS_EVENT_PREPARE_WRITE_RSP_COMP = 0x3017, //!< BLE_GATTS_EVENT_PREPARE_WRITE_RSP_COMP

    /**
     *  @brief   Execute Write Response has been sent.
     *  @details
     *  This event notifies the application layer that a Execute Write Response PDU has been sent
     *  from GATT Server to the GATT Client.
     *
     * ## Event Code: 0x3019
     *
     *  ## Event Data:
     *  st_ble_gatts_exe_write_rsp_evt_t
     */
    BLE_GATTS_EVENT_EXE_WRITE_RSP_COMP = 0x3019,     //!< BLE_GATTS_EVENT_EXE_WRITE_RSP_COMP

    /**
     *  @brief   Confirmation has been received.
     *  @details
     *  This event notifies the application layer that a Confirmation PDU has been received from a GATT Client.
     *
     * ## Event Code: 0x301E
     *
     *  ## Event Data:
     *  st_ble_gatts_cfm_evt_t
     */
    BLE_GATTS_EVENT_HDL_VAL_CNF = 0x301E,            //!< BLE_GATTS_EVENT_HDL_VAL_CNF

    /**
     *  @brief   The GATT Database has been accessed from a GATT Client.
     *  @details
     *  This event notifies the application layer that the GATT Database has been accessed from a GATT Client.
     *
     * ## Event Code: 0x3040
     *
     *  ## Event Data:
     *  st_ble_gatts_db_access_evt_t
     */
    BLE_GATTS_EVENT_DB_ACCESS_IND = 0x3040,          //!< BLE_GATTS_EVENT_DB_ACCESS_IND

    /**
     *  @brief   A connection has been established.
     *  @details
     *  This event notifies the application layer that the link with the GATT Client has been established.
     *
     * ## Event Code: 0x3081
     *
     *  ## Event Data:
     *  st_ble_gatts_conn_evt_t
     */
    BLE_GATTS_EVENT_CONN_IND = 0x3081,               //!< BLE_GATTS_EVENT_CONN_IND

    /**
     *  @brief   A connection has been disconnected.
     *  @details
     *  This event notifies the application layer that the link with the GATT Client has been disconnected.
     *
     * ## Event Code: 0x3082
     *
     *  ## Event Data:
     *  st_ble_gatts_disconn_evt_t
     */
    BLE_GATTS_EVENT_DISCONN_IND = 0x3082,            //!< BLE_GATTS_EVENT_DISCONN_IND

    /**
     *  @brief   Invalid GATT Server Event.
     *
     * ## Event Code: 0x30FF
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTS_EVENT_INVALID = 0x30FF                 //!< BLE_GATTS_EVENT_INVALID
} e_r_ble_gatts_evt_t;

/*@}*/

/** @addtogroup GATT_CLIENT_API
 *  @ingroup BLE
 *  @{
 */

/**
 * @ingroup GATT_CLIENT_API
 * @def BLE_GATTC_EXECUTE_WRITE_CANCEL_FLAG
 * GATT Execute Write Cancel Flag.
 */
#define BLE_GATTC_EXECUTE_WRITE_CANCEL_FLAG        (0x00)

/**
 * @def BLE_GATTC_EXECUTE_WRITE_EXEC_FLAG
 * GATT Execute Write Execute Flag.
 */
#define BLE_GATTC_EXECUTE_WRITE_EXEC_FLAG          (0x01)

/**
 * @def BLE_GATTC_MAX_CB
 * @brief GATT Client Callback Number.
 */
#define BLE_GATTC_MAX_CB                           (15)

/**
 * @def BLE_GATTC_EXEC_AUTO
 * @brief Auto execution.
 */
#define BLE_GATTC_EXEC_AUTO                        (0x01)

/**
 * @def BLE_GATTC_EXEC_NOT_AUTO
 * @brief Not auto execution.
 */
#define BLE_GATTC_EXEC_NOT_AUTO                    (0x02)

/* To be moved to parameter files */

/**
 * @def BLE_GATTC_RELIABLE_WRITES_MAX_CHAR_PAIR
 * @brief Length of the Queue used with Prepare Write procedure to write a characteristic
 *        whose size is larger than MTU.
 */
#define BLE_GATTC_RELIABLE_WRITES_MAX_CHAR_PAIR    (10)

/******************************************************************************************************************//**
 * @enum e_r_ble_gattc_evt_t
 * @brief  GATT Client Event Identifier
 **********************************************************************************************************************/
typedef enum
{
    /**
     *  @brief  This event notifies the application layer that a problem has occurred in the GATT Server while
     *          processing a request from GATT Client.
     *  @details When GATT Client has received a Error Response PDU from a GATT Server, BLE_GATTC_EVENT_ERROR_RSP
     *           event is notified the application layer.
     *
     * ## Event Code: 0x4001
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_err_rsp_evt_t
     */
    BLE_GATTC_EVENT_ERROR_RSP = 0x4001,                 //!< BLE_GATTC_EVENT_ERROR_RSP

    /**
     *  @brief  This event notifies the application layer that a MTU Exchange Response PDU has been received
     *          from a GATT Server.
     *
     * ## Event Code: 0x4003
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a Exchange MTU Response
     *                      since GATT Client sent a Exchange MTU Request PDU to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_ex_mtu_rsp_evt_t
     */
    BLE_GATTC_EVENT_EX_MTU_RSP = 0x4003,                //!< BLE_GATTC_EVENT_EX_MTU_RSP

    /**
     *  @brief  When the read of Characteristic specified by UUID has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x4009
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a Exchange MTU Response
     *                      since GATT Client sent a Exchange MTU Request PDU to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_rd_char_evt_t
     */
    BLE_GATTC_EVENT_CHAR_READ_BY_UUID_RSP = 0x4009,     //!< BLE_GATTC_EVENT_CHAR_READ_BY_UUID_RSP

    /**
     *  @brief  When the read of Characteristic/Characteristic Descriptor has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x400B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a read response
     *                      since GATT Client sent a request for read by R_BLE_GATTC_ReadCharUsingUuid()
     *                      to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_rd_char_evt_t
     */
    BLE_GATTC_EVENT_CHAR_READ_RSP = 0x400B,             //!< BLE_GATTC_EVENT_CHAR_READ_RSP

    /**
     *  @brief  After calling R_BLE_GATTC_ReadLongChar(), this event notifies the application layer
     *          that the partial contents of Long Characteristic/Long Characteristic Descriptor
     *          has been received from the GATT Server.
     *
     * ## Event Code: 0x400D
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a read response
     *                      since GATT Client sent a request for read by R_BLE_GATTC_ReadLongChar() to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_rd_char_evt_t
     */
    BLE_GATTC_EVENT_CHAR_PART_READ_RSP = 0x400D,        //!< BLE_GATTC_EVENT_CHAR_PART_READ_RSP

    /**
     *  @brief  This event notifies the application layer that
     *          the read of multiple Characteristics has been completed.
     *
     * ## Event Code: 0x400F
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a read response
     *                      since GATT Client sent a request for read by R_BLE_GATTC_ReadMultiChar() to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_rd_multi_char_evt_t
     */
    BLE_GATTC_EVENT_MULTI_CHAR_READ_RSP = 0x400F,       //!< BLE_GATTC_EVENT_MULTI_CHAR_READ_RSP

    /**
     *  @brief  This event notifies the application layer that the write of
     *          Characteristic/Characteristic Descriptor has been completed.
     *
     * ## Event Code: 0x4013
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a write response
     *                      since GATT Client sent a request for write by R_BLE_GATTC_WriteChar() to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_wr_char_evt_t
     */
    BLE_GATTC_EVENT_CHAR_WRITE_RSP = 0x4013,            //!< BLE_GATTC_EVENT_CHAR_WRITE_RSP

    /**
     *  @brief  This event notifies the application layer of the one of the following.
     *          - A segmentation to be written to Long Characteristic/Long Characteristic Descriptor
     *            has been sent to the GATT Server.
     *          - The data written to one Characteristic by Reliable Writes has been sent to the GATT Server.
     *
     * ## Event Code: 0x4017
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a response since GATT Client sent a
     *                      request for segmentation write by R_BLE_GATTC_WriteLongChar(),
     *                      or 1 Characteristic write by R_BLE_GATTC_ReliableWrites() to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_char_part_wr_evt_t
     */
    BLE_GATTC_EVENT_CHAR_PART_WRITE_RSP = 0x4017,       //!< BLE_GATTC_EVENT_CHAR_PART_WRITE_RSP

    /**
     *  @brief  This event notifies the application layer that a Notification has been received from a GATT Server.
     *
     * ## Event Code: 0x401B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_ntf_evt_t
     */
    BLE_GATTC_EVENT_HDL_VAL_NTF = 0x401B,               //!< BLE_GATTC_EVENT_HDL_VAL_NTF

    /**
     *  @brief  This event notifies the application layer that a Indication has been received from a GATT Server.
     *  @details When the GATT Client has received a Indication, host stack automatically sends a Confirmation
     *           to the GATT Server.
     *
     * ## Event Code: 0x401D
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_MEM_ALLOC_FAILED(0x000C)</td>
     *                  <td>Insufficient resource is needed to generate the confirmation packet. </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_ind_evt_t
     */
    BLE_GATTC_EVENT_HDL_VAL_IND = 0x401D,               //!< BLE_GATTC_EVENT_HDL_VAL_IND

    /**
     *  @brief  This event notifies the application layer that the link with the GATT Server has been established.
     *
     * ## Event Code: 0x4081
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_conn_evt_t
     */
    BLE_GATTC_EVENT_CONN_IND = 0x4081,                  //!< BLE_GATTC_EVENT_CONN_IND

    /**
     *  @brief  This event notifies the application layer that the link with the GATT Server has been disconnected.
     *
     * ## Event Code: 0x4082
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_disconn_evt_t
     */
    BLE_GATTC_EVENT_DISCONN_IND = 0x4082,               //!< BLE_GATTC_EVENT_DISCONN_IND

    /**
     *  @brief  This event notifies the application layer that 16-bit UUID Primary Service has been discovered.
     *
     * ## Event Code: 0x40E0
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_serv_16_evt_t
     */
    BLE_GATTC_EVENT_PRIM_SERV_16_DISC_IND = 0x40E0,     //!< BLE_GATTC_EVENT_PRIM_SERV_16_DISC_IND

    /**
     *  @brief  This event notifies the application layer that 128-bit UUID Primary Service has been discovered.
     *
     * ## Event Code: 0x40E1
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_serv_128_evt_t
     */
    BLE_GATTC_EVENT_PRIM_SERV_128_DISC_IND = 0x40E1,    //!< BLE_GATTC_EVENT_PRIM_SERV_128_DISC_IND

    /**
     *  @brief  When the Primary Service discovery by R_BLE_GATTC_DiscAllPrimServ() has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x40E2
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_ALL_PRIM_SERV_DISC_COMP = 0x40E2,   //!< BLE_GATTC_EVENT_ALL_PRIM_SERV_DISC_COMP

    /**
     *  @brief  When the Primary Service discovery by R_BLE_GATTC_DiscPrimServ() has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x40E3
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_PRIM_SERV_DISC_COMP = 0x40E3,       //!< BLE_GATTC_EVENT_PRIM_SERV_DISC_COMP

    /**
     *  @brief  This event notifies the application layer that 16-bit UUID Secondary Service has been discovered.
     *
     * ## Event Code: 0x40E4
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_serv_16_evt_t
     */
    BLE_GATTC_EVENT_SECOND_SERV_16_DISC_IND = 0x40E4,   //!< BLE_GATTC_EVENT_SECOND_SERV_16_DISC_IND

    /**
     *  @brief  This event notifies the application layer that 128-bit UUID Secondary Service has been discovered.
     *
     * ## Event Code: 0x40E5
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_serv_128_evt_t
     */
    BLE_GATTC_EVENT_SECOND_SERV_128_DISC_IND = 0x40E5,  //!< BLE_GATTC_EVENT_SECOND_SERV_128_DISC_IND

    /**
     *  @brief  When the Primary Service discovery by R_BLE_GATTC_DiscAllSecondServ() has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x40E6
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_ALL_SECOND_SERV_DISC_COMP = 0x40E6, //!< BLE_GATTC_EVENT_ALL_SECOND_SERV_DISC_COMP

    /**
     *  @brief  This event notifies the application layer that Included Service that
     *          includes 16-bit UUID Service has been discovered.
     *
     * ## Event Code: 0x40E7
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_inc_serv_16_evt_t
     */
    BLE_GATTC_EVENT_INC_SERV_16_DISC_IND = 0x40E7,      //!< BLE_GATTC_EVENT_INC_SERV_16_DISC_IND

    /**
     *  @brief  This event notifies the application layer that Included Service that
     *          includes 128-bit UUID Service has been discovered.
     *
     * ## Event Code: 0x40E8
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_inc_serv_128_evt_t
     */
    BLE_GATTC_EVENT_INC_SERV_128_DISC_IND = 0x40E8,     //!< BLE_GATTC_EVENT_INC_SERV_128_DISC_IND

    /**
     *  @brief  When the Included Service discovery by R_BLE_GATTC_DiscIncServ() has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x40E9
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_INC_SERV_DISC_COMP = 0x40E9,        //!< BLE_GATTC_EVENT_INC_SERV_DISC_COMP

    /**
     *  @brief  This event notifies the application layer that 16-bit UUID Characteristic has been discovered.
     *
     * ## Event Code: 0x40EA
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_char_16_evt_t
     */
    BLE_GATTC_EVENT_CHAR_16_DISC_IND = 0x40EA,          //!< BLE_GATTC_EVENT_CHAR_16_DISC_IND

    /**
     *  @brief  This event notifies the application layer that 128-bit UUID Characteristic has been discovered.
     *
     * ## Event Code: 0x40EB
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_char_128_evt_t
     */
    BLE_GATTC_EVENT_CHAR_128_DISC_IND = 0x40EB,         //!< BLE_GATTC_EVENT_CHAR_128_DISC_IND

    /**
     *  @brief  When the Characteristic discovery by R_BLE_GATTC_DiscAllChar() has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x40EC
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_ALL_CHAR_DISC_COMP = 0x40EC,        //!< BLE_GATTC_EVENT_ALL_CHAR_DISC_COMP

    /**
     *  @brief  When the Characteristic discovery by R_BLE_GATTC_DiscCharByUuid() has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x40ED
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_CHAR_DISC_COMP = 0x40ED,            //!< BLE_GATTC_EVENT_CHAR_DISC_COMP

    /**
     *  @brief  This event notifies the application layer that 16-bit UUID Characteristic Descriptor
     *          has been discovered.
     *
     * ## Event Code: 0x40EE
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_char_desc_16_evt_t
     */
    BLE_GATTC_EVENT_CHAR_DESC_16_DISC_IND = 0x40EE,     //!< BLE_GATTC_EVENT_CHAR_DESC_16_DISC_IND

    /**
     *  @brief  This event notifies the application layer that 128-bit UUID Characteristic Descriptor
     *          has been discovered.
     *
     * ## Event Code: 0x40EF
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_char_desc_128_evt_t
     */
    BLE_GATTC_EVENT_CHAR_DESC_128_DISC_IND = 0x40EF,    //!< BLE_GATTC_EVENT_CHAR_DESC_128_DISC_IND

    /**
     *  @brief  When the Characteristic Descriptor discovery by R_BLE_GATTC_DiscAllCharDesc() has been completed,
     *          this event is notified to the application layer.
     *
     * ## Event Code: 0x40F0
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_ALL_CHAR_DESC_DISC_COMP = 0x40F0,   //!< BLE_GATTC_EVENT_ALL_CHAR_DESC_DISC_COMP

    /**
     *  @brief  After calling R_BLE_GATTC_ReadLongChar(), this event notifies the application layer that all of
     *          the contents of the Characteristic/Long Characteristic Descriptor has been received
     *          from the GATT Server.
     *
     * ## Event Code: 0x40F1
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_LONG_CHAR_READ_COMP = 0x40F1,       //!< BLE_GATTC_EVENT_LONG_CHAR_READ_COMP

    /**
     *  @brief  This event notifies that the application layer that the write of
     *          Long Characteristic/Long Characteristic Descriptor has been completed.
     *
     * ## Event Code: 0x40F2
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a response since GATT Client sent
     *                      a request for write by R_BLE_GATTC_WriteLongChar() to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_LONG_CHAR_WRITE_COMP = 0x40F2,      //!< BLE_GATTC_EVENT_LONG_CHAR_WRITE_COMP

    /**
     *  @brief  This event notifies that the application layer that
     *          the GATT Server has received the data to be written to the Characteristics.
     *
     * ## Event Code: 0x40F3
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_RELIABLE_WRITES_TX_COMP = 0x40F3,   //!< BLE_GATTC_EVENT_RELIABLE_WRITES_TX_COMP

    /**
     *  @brief  This event notifies the application layer that the Reliable Writes has been completed.
     *
     * ## Event Code: 0x40F4
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>30 seconds or more have passed without receiving a response since GATT Client sent a
     *                      request for execute write by R_BLE_GATTC_ReliableWrites() or
     *                      R_BLE_GATTC_ExecWrite() to the GATT Server.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gattc_reliable_writes_comp_evt_t
     */
    BLE_GATTC_EVENT_RELIABLE_WRITES_COMP = 0x40F4,      //!< BLE_GATTC_EVENT_RELIABLE_WRITES_COMP

    /**
     *  @brief  Invalid GATT Client Event.
     *
     * ## Event Code: 0x40FF
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GATTC_EVENT_INVALID = 0x40FF                    //!< BLE_GATTC_EVENT_INVALID
} e_r_ble_gattc_evt_t;

/*@}*/

/* ================================================== L2CAP Macro =================================================== */

/** @addtogroup L2CAP_API
 *  @ingroup BLE
 *  @{
 */

/**
 * @ingroup l2cap_api
 * @def BLE_L2CAP_MAX_CBFC_PSM
 * @brief The maximum number of callbacks that host stack can register.
 */
#define BLE_L2CAP_MAX_CBFC_PSM                (2)

/**
 * @def BLE_L2CAP_CF_RSP_SUCCESS
 * @brief Notify the remote device that the connection can be established.
 */
#define BLE_L2CAP_CF_RSP_SUCCESS              (0x0000)

/**
 * @def BLE_L2CAP_CF_RSP_RFSD_INSF_AUTH
 * @brief Notify the remote device that the connection can not be established because of insufficient authentication.
 */
#define BLE_L2CAP_CF_RSP_RFSD_INSF_AUTH       (0x0005)

/**
 * @def BLE_L2CAP_CF_RSP_RFSD_INSF_AUTRZ
 * @brief Notify the remote device that the connection can not be established because of insufficient Authorization.
 */
#define BLE_L2CAP_CF_RSP_RFSD_INSF_AUTRZ      (0x0006)

/**
 * @def BLE_L2CAP_CF_RSP_RFSD_INSF_ENC_KEY
 * @brief Notify the remote device that the connection can not be established because of Encryption Key Size.
 */
#define BLE_L2CAP_CF_RSP_RFSD_INSF_ENC_KEY    (0x0007)

/**
 * @def BLE_L2CAP_CF_RSP_RFSD_INSF_ENC
 * @brief Notify the remote device that the connection can not be established because of Encryption.
 */
#define BLE_L2CAP_CF_RSP_RFSD_INSF_ENC        (0x0008)

/**
 * @def BLE_L2CAP_CF_RSP_RFSD_UNAC_PARAM
 * @brief Notify the remote device that the connection can not be established
 *        because the parameters is unacceptable to local device.
 */
#define BLE_L2CAP_CF_RSP_RFSD_UNAC_PARAM      (0x000B)

/*@}*/

/* ============================================= Vendor Specific Macro ============================================== */

/** @addtogroup VS_API
 *  @ingroup BLE
 *  @{
 */

/**
 * @ingroup vs_api
 * @def BLE_VS_TX_POWER_HIGH
 * @brief High power level.
 */
#define BLE_VS_TX_POWER_HIGH            (0x00)

/**
 * @def BLE_VS_TX_POWER_MID
 * @brief Middle power level.
 */
#define BLE_VS_TX_POWER_MID             (0x01)

/**
 * @def BLE_VS_TX_POWER_LOW
 * @brief Low power level.
 */
#define BLE_VS_TX_POWER_LOW             (0x02)

/**
 * @def BLE_VS_ADDR_AREA_REG
 * @brief Address in register is written or read.
 */
#define BLE_VS_ADDR_AREA_REG            (0x00)

/**
 * @def BLE_VS_ADDR_AREA_DATA_FLASH
 * @brief Address in DataFlash is written or read.
 */
#define BLE_VS_ADDR_AREA_DATA_FLASH     (0x01)

/**
 * @def BLE_VS_EH_TX_PL_PRBS9
 * @brief PRBS9 sequence '11111111100000111101..'.
 */
#define BLE_VS_EH_TX_PL_PRBS9           (0x00)

/**
 * @def BLE_VS_EH_TX_PL_11110000
 * @brief Repeated '11110000'
 */
#define BLE_VS_EH_TX_PL_11110000        (0x01)

/**
 * @def BLE_VS_EH_TX_PL_10101010
 * @brief Repeated '10101010'
 */
#define BLE_VS_EH_TX_PL_10101010        (0x02)

/**
 * @def BLE_VS_EH_TX_PL_PRBS15
 * @brief PRBS15 sequence
 */
#define BLE_VS_EH_TX_PL_PRBS15          (0x03)

/**
 * @def BLE_VS_EH_TX_PL_11111111
 * @brief Repeated '11111111'
 */
#define BLE_VS_EH_TX_PL_11111111        (0x04)

/**
 * @def BLE_VS_EH_TX_PL_00000000
 * @brief Repeated '00000000'
 */
#define BLE_VS_EH_TX_PL_00000000        (0x05)

/**
 * @def BLE_VS_EH_TX_PL_00001111
 * @brief Repeated '00001111'
 */
#define BLE_VS_EH_TX_PL_00001111        (0x06)

/**
 * @def BLE_VS_EH_TX_PL_01010101
 * @brief Repeated '01010101'
 */
#define BLE_VS_EH_TX_PL_01010101        (0x07)

/**
 * @def BLE_VS_EH_TEST_PHY_1M
 * @brief 1M PHY used in Transmitter/Receiver test.
 */
#define BLE_VS_EH_TEST_PHY_1M           (0x01)

/**
 * @def BLE_VS_EH_TEST_PHY_2M
 * @brief 2M PHY used in Transmitter/Receiver test.
 */
#define BLE_VS_EH_TEST_PHY_2M           (0x02)

/**
 * @def BLE_VS_EH_TEST_PHY_CODED
 * @brief Coded PHY used in Receiver test.
 */
#define BLE_VS_EH_TEST_PHY_CODED        (0x03)

/**
 * @def BLE_VS_EH_TEST_PHY_CODED_S_8
 * @brief Coded PHY(S=8) used in Transmitter test.
 */
#define BLE_VS_EH_TEST_PHY_CODED_S_8    (0x03)

/**
 * @def BLE_VS_EH_TEST_PHY_CODED_S_2
 * @brief Coded PHY(S=2) used in Transmitter test.
 */
#define BLE_VS_EH_TEST_PHY_CODED_S_2    (0x04)

/**
 * @def BLE_VS_RF_OFF
 * @brief RF power off.
 */
#define BLE_VS_RF_OFF                   (0x00)

/**
 * @def BLE_VS_RF_ON
 * @brief RF power on.
 */
#define BLE_VS_RF_ON                    (0x01)

/**
 * @def BLE_VS_RF_INIT_PARAM_NOT_CHG
 * @brief The parameters are not changed in RF power on.
 */
#define BLE_VS_RF_INIT_PARAM_NOT_CHG    (0x00)

/**
 * @def BLE_VS_RF_INIT_PARAM_CHG
 * @brief The parameters are changed in RF power on.
 */
#define BLE_VS_RF_INIT_PARAM_CHG        (0x01)

/**
 * @def BLE_VS_CS_PRIM_ADV_S_8
 * @brief Coding scheme for Primary Advertising PHY(S=8).
 */
#define BLE_VS_CS_PRIM_ADV_S_8          (0x00)

/**
 * @def BLE_VS_CS_PRIM_ADV_S_2
 * @brief Coding scheme for Primary Advertising PHY(S=2).
 */
#define BLE_VS_CS_PRIM_ADV_S_2          (0x01)

/**
 * @def BLE_VS_CS_SECOND_ADV_S_8
 * @brief Coding scheme for Secondary Advertising PHY(S=8).
 */
#define BLE_VS_CS_SECOND_ADV_S_8        (0x00)

/**
 * @def BLE_VS_CS_SECOND_ADV_S_2
 * @brief Coding scheme for Secondary Advertising PHY(S=2).
 */
#define BLE_VS_CS_SECOND_ADV_S_2        (0x02)

/**
 * @def BLE_VS_CS_CONN_S_8
 * @brief Coding scheme for request for link establishment(S=8).
 */
#define BLE_VS_CS_CONN_S_8              (0x00)

/**
 * @def BLE_VS_CS_CONN_S_2
 * @brief Coding scheme for request for link establishment(S=2).
 */
#define BLE_VS_CS_CONN_S_2              (0x04)

/**
 * @def BLE_VS_TX_FLOW_CTL_ON
 * @brief  It means that the number of buffer has reached the High Water Mark from flow off state.
 */
#define BLE_VS_TX_FLOW_CTL_ON           (0x00)

/**
 * @def BLE_VS_TX_FLOW_CTL_OFF
 * @brief  It means that the number of buffer has reached the Low Water Mark from flow on state.
 */
#define BLE_VS_TX_FLOW_CTL_OFF          (0x01)

/*@}*/

/* ============================================== GAP Type Definitions ============================================== */

/** @addtogroup GAP_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @struct st_ble_evt_data_t
 * @brief  st_ble_evt_data_t is the type of the data notified in a GAP Event.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief The size of GAP Event parameters.
     */
    uint16_t param_len;

    /**
     *  @brief GAP Event parameters. This parameter differs in each GAP Event.
     */
    void * p_param;
} st_ble_evt_data_t;

/******************************************************************************************************************//**
 *  @struct st_ble_dev_addr_t
 *  @brief  st_ble_dev_addr_t is the type of bluetooth device address(BD_ADDR).
 *  @note   The BD address setting format is little endian. \n
 *          If the address is "AA:BB:CC:DD:EE:FF", set the byte array in the order {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA}.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief BD_ADDR.
     */
    uint8_t addr[BLE_BD_ADDR_LEN];

    /**
     *  @brief Bluetooth address type.
     *  @details
     *               |              macro        |   description     |
     *               |:------------------------- |:----------------- |
     *               | BLE_GAP_ADDR_PUBLIC(0x00) | Public Address.   |
     *               | BLE_GAP_ADDR_RAND(0x01)   | Random Address.   |
     */
    uint8_t type;
} st_ble_dev_addr_t;

/******************************************************************************************************************//**
 * @typedef ble_gap_app_cb_t
 * @brief   ble_gap_app_cb_t is the GAP Event callback function type.
 * @param[in] event_type    The type of GAP Event.
 * @param[in] event_result  The result of API call which generates the GAP Event.
 * @param[in] p_event_data  Data notified in the GAP Event.
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_gap_app_cb_t)(uint16_t event_type, ble_status_t event_result, st_ble_evt_data_t * p_event_data);

/******************************************************************************************************************//**
 * @typedef ble_gap_del_bond_cb_t
 * @brief   ble_gap_del_bond_cb_t is the type of the callback function for delete bonding information
 *          stored in non-volatile area. \n This type is used in R_BLE_GAP_DeleteBondInfo().
 * @param[in] p_addr The parameter returns the address of the remote device whose keys are deleted
 *            by R_BLE_GAP_DeleteBondInfo(). \n
 *            If R_BLE_GAP_DeleteBondInfo() deletes the keys of all remote devices, the parameter returns NULL.
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_gap_del_bond_cb_t)(st_ble_dev_addr_t * p_addr);

/* =========================================== GAP API Params Definitions =========================================== */

/******************************************************************************************************************//**
 * @struct st_ble_gap_ext_adv_param_t
 * @brief  Advertising parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Advertising handle identifying the advertising set to be set the advertising parameters.
     *  @details
     *  Valid range is 0x00 - 0x03.\n
     *  In the first advertising parameters setting, the advertising set specified by adv_hdl is generated.\n
     *  The Advertising Set ID(Advertising SID) of the advertising set is same as adv_hdl.
     */
    uint8_t adv_hdl;

    /**
     *  @brief Advertising packet type.
     *  @details
     *  Legacy advertising PDU type, or bitwise or of Extended advertising PDU type and Extended advertising option.
     *  <table>
     *      <tr>
     *          <th>category</th>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td rowspan="5">Legacy Advertising PDU type</td>
     *          <td>BLE_GAP_LEGACY_PROP_ADV_IND(0x0013)</td>
     *          <td>Connectable and scannable undirected Legacy Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_LEGACY_PROP_ADV_DIRECT_IND(0x0015)</td>
     *          <td>Connectable directed (low duty cycle) Legacy Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_LEGACY_PROP_ADV_HDC_DIRECT_IND(0x001D)</td>
     *          <td>Connectable directed (high duty cycle) Legacy Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_LEGACY_PROP_ADV_SCAN_IND(0x0012)</td>
     *          <td>Scannable undirected Legacy Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND(0x0010)</td>
     *          <td>Non-connectable and non-scannable undirected Legacy Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td rowspan="9">Extended Advertising PDU type</td>
     *          <td>BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_UNDIRECT(0x0001)</td>
     *          <td>Connectable and non-scannable undirected Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_DIRECT(0x0005)</td>
     *          <td>Connectable and non-scannable directed (low duty cycle) Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_CONN_NOSCAN_HDC_DIRECT(0x000D)</td>
     *          <td>Connectable and non-scannable directed (high duty cycle) Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_UNDIRECT(0x0002)</td>
     *          <td>Non-connectable and scannable undirected Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_DIRECT(0x0006)</td>
     *          <td>Non-connectable and scannable directed (low duty cycle) Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_NOCONN_SCAN_HDC_DIRECT(0x000E)</td>
     *          <td>Non-connectable and scannable directed (high duty cycle) Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_UNDIRECT(0x0000)</td>
     *          <td>Non-connectable and non-scannable undirected Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_DIRECT(0x0004)</td>
     *          <td>Non-connectable and non-scannable directed (low duty cycle) Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_NOCONN_NOSCAN_HDC_DIRECT(0x000C)</td>
     *          <td>Non-connectable and non-scannable directed (high duty cycle) Extended Advertising Packet</td>
     *      </tr>
     *      <tr>
     *          <td rowspan="2">Extended Advertising Option</td>
     *          <td>BLE_GAP_EXT_PROP_ADV_ANONYMOUS(0x0020)</td>
     *          <td>Omit the advertiser address from Extended Advertising Packet.</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_EXT_PROP_ADV_INCLUDE_TX_POWER(0x0040)</td>
     *          <td>Indicate that the advertising data includes TX Power.</td>
     *      </tr>
     *  </table>
     */
    uint16_t adv_prop_type;

    /**
     *  @brief Minimum advertising interval.
     *  @details
     *  Time(ms) = adv_intv_min * 0.625.\n
     *  Valid range is 0x00000020 - 0x00FFFFFF.
     */
    uint32_t adv_intv_min;

    /**
     *  @brief Maximum Advertising interval.
     *  @details
     *  Time(ms) = adv_intv_max * 0.625.\n
     *  Valid range is 0x00000020 - 0x00FFFFFF.
     */
    uint32_t adv_intv_max;

    /**
     *  @brief The adv_ch_map is channels used in advertising with primary advertising channels.
     *  @details
     *  It is a bitwise OR of the following values.
     *               |              macro        |   description     |
     *               |:------------------------- |:----------------- |
     *               | BLE_GAP_ADV_CH_37(0x01)   | Use 37 CH.        |
     *               | BLE_GAP_ADV_CH_38(0x02)   | Use 38 CH.        |
     *               | BLE_GAP_ADV_CH_39(0x04)   | Use 39 CH.        |
     *               | BLE_GAP_ADV_CH_ALL(0x07)  | Use 37 - 39 CH.   |
     */
    uint8_t adv_ch_map;

    /**
     *  @brief Own BD Address Type.
     *  @details
     *  <table>
     *      <tr>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_PUBLIC(0x00)</td>
     *          <td>Public Address</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_RAND(0x01)</td>
     *          <td>Random Address</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_RPA_ID_PUBLIC(0x02)</td>
     *          <td>
     *              Resolvable Private Address.<BR/>
     *              If the IRK of local device has not been registered in Resolving List,
     *              public address is used.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_RPA_ID_RANDOM(0x03)</td>
     *          <td>
     *              Resolvable Private Address.<BR/>
     *              If the IRK of local device has not been registered in Resolving List,
     *              the random address specified by the o_addr field is used.
     *          </td>
     *      </tr>
     *  </table>
     */
    uint8_t o_addr_type;

    /**
     *  @brief Random address set to the advertising set, when the o_addr_type field is BLE_GAP_ADDR_RAND.
     *  @details When the o_addr_type field is other than BLE_GAP_ADDR_RAND, this field is ignored.
     *  @note   The BD address setting format is little endian. \n
     *          If the address is "AA:BB:CC:DD:EE:FF", set the byte array in the order
     *          {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA}.
     */
    uint8_t o_addr[BLE_BD_ADDR_LEN];

    /**
     *  @brief Peer address type.
     *  @details
     *  When the Advertising PDU type is other than directed or the o_addr_type is BLE_GAP_ADDR_PUBLIC or
     *  BLE_GAP_ADDR_RAND,this field is ignored.
     *               |              macro        |   description     |
     *               |:------------------------- |:----------------- |
     *               | BLE_GAP_ADDR_PUBLIC(0x00) | Public Address    |
     *               | BLE_GAP_ADDR_RAND(0x01)   | Random Address    |
     */
    uint8_t p_addr_type;

    /**
     *  @brief Peer address.
     *  @details When the Advertising PDU type is other than directed or
     *           the o_addr_type is BLE_GAP_ADDR_PUBLIC or BLE_GAP_ADDR_RAND,this field is ignored.
     *  @note   The BD address setting format is little endian. \n
     *          If the address is "AA:BB:CC:DD:EE:FF", set the byte array in the order
     *          {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA}.
     */
    uint8_t p_addr[BLE_BD_ADDR_LEN];

    /**
     *  @brief Advertising Filter Policy.
     *  @details
     *  <table>
     *      <tr>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADV_ALLOW_SCAN_ANY_CONN_ANY(0x00)</td>
     *          <td>Process scan and connection requests from all devices.</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADV_ALLOW_SCAN_WLST_CONN_ANY(0x01)</td>
     *          <td>
     *              Process connection requests from all devices and scan requests
     *              from only devices that are in the White List.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADV_ALLOW_SCAN_ANY_CONN_WLST(0x02)</td>
     *          <td>
     *              Process scan requests from all devices and connection requests from
     *              only devices that are in the White List.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADV_ALLOW_SCAN_WLST_CONN_WLST(0x03)</td>
     *          <td>Process scan and connection requests from only devices in the White List.</td>
     *      </tr>
     *  </table>
     */
    uint8_t filter_policy;

    /**
     *  @brief Primary ADV PHY.
     *  @details
     *  In this parameter, only 1M PHY and Coded PHY can be specified, and 2M PHY cannot be specified.
     *  <table>
     *      <tr>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADV_PHY_1M(0x01)</td>
     *          <td>
     *              Use 1M PHY as Primary Advertising PHY.<BR/>
     *              When the adv_prop_type field is Legacy Advertising PDU type, <BR/>
     *              this field shall be set to BLE_GAP_ADV_PHY_1M.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADV_PHY_CD(0x03)</td>
     *          <td>Use Coded PHY(S=8) as Primary Advertising PHY.
     *               Coding scheme is configured by @ref R_BLE_VS_SetCodingScheme().</td>
     *      </tr>
     *  </table>
     */
    uint8_t adv_phy;

    /**
     *  @brief Secondary ADV Max Skip.
     *  @details
     *  Valid range is 0x00 - 0xFF.\n
     *  When this field is 0x00, AUX_ADV_IND is sent before the next advertising event.\n
     *  When the adv_prop_type field is Legacy Advertising PDU, this field is ignored.
     */
    uint8_t sec_adv_max_skip;

    /**
     *  @brief Secondary ADV Phy.
     *  @details
     *  When the adv_prop_type is Legacy Advertising PDU, this field is ignored.
     *               |              macro        |   description                                    |
     *               |:------------------------- |:------------------------------------------------ |
     *               | BLE_GAP_ADV_PHY_1M(0x01)  | Use 1M PHY as Secondary Advertising PHY.         |
     *               | BLE_GAP_ADV_PHY_2M(0x02)  | Use 2M PHY as Secondary Advertising PHY.         |
     *               | BLE_GAP_ADV_PHY_CD(0x03)  | Use Coded PHY(S=8) as Secondary Advertising PHY. |
     *
     *  Coding scheme is configured by @ref R_BLE_VS_SetCodingScheme().
     */
    uint8_t sec_adv_phy;

    /**
     *  @brief Scan Request Notifications Flag.
     *  @details
     *  When the adv_prop_type field is non-scannable Advertising PDU, this field is ignored.
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_SCAN_REQ_NTF_DISABLE(0x00)</td>
     *              <td>Disable Scan Request Notification.</td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_SCAN_REQ_NTF_ENABLE(0x01)</td>
     *              <td>
     *                  Enable Scan Request Notification.<BR/>
     *                  When a Scan Request Packet from Scanner has been received,
     *                  the BLE_GAP_EVENT_SCAN_REQ_RECV event is notified.
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t scan_req_ntf_flag;
} st_ble_gap_ext_adv_param_t;

/******************************************************************************************************************//**
 * @brief  Advertising parameters.
 * @sa st_ble_gap_ext_adv_param_t
 **********************************************************************************************************************/
typedef st_ble_gap_ext_adv_param_t st_ble_gap_adv_param_t;

/******************************************************************************************************************//**
 * @struct st_ble_gap_adv_data_t
 * @brief  Advertising data/scan response data/periodic advertising data.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Advertising handle identifying the advertising set to be
     *         set advertising data/scan response/periodic advertising data.
     *  @details
     *  Valid range is 0x00 - 0x03.
     */
    uint8_t adv_hdl;

    /**
     *  @brief Data type.
     *  @details
     *               |              macro                 |   description              |
     *               |:---------------------------------- |:-------------------------- |
     *               | BLE_GAP_ADV_DATA_MODE (0x00)       | Advertising data.          |
     *               | BLE_GAP_SCAN_RSP_DATA_MODE(0x01)   | Scan response data.        |
     *               | BLE_GAP_PERD_ADV_DATA_MODE(0x02)   | Periodic advertising data. |
     */
    uint8_t data_type;

    /**
     *  @brief The length of advertising data/scan response data/periodic advertising data (in bytes).
     *  @details
     *   In case of Legacy Advertising PDU, the length is 0 - 31 bytes.\n
     *   In case of Extended Advertising PDU, the length is 0 - 1650 bytes.\n
     *   Note that the length of the advertising data/scan response data in
     *   the BLE_MAX_NO_OF_ADV_SETS_SUPPORTED number of the advertising sets may not exceed
     *   the buffer size(4250 bytes) in Controller. \n
     *   \n
     *   In case of periodic advertising data, the length is 0 - 1650 bytes.\n
     *   Note that the length of the periodic advertising data in the BLE_MAX_NO_OF_ADV_SETS_SUPPORTED number of
     *   the advertising sets may not exceed the buffer size(4306 bytes) in Controller.\n
     *   \n
     *   When this field is 0, the operations specified by the zero_length_flag is executed.
     */
    uint16_t data_length;

    /**
     *  @brief Advertising data/scan response data/periodic advertising data.
     *  @details
     *  When the data_length field is 0, this field is ignored.
     */
    uint8_t * p_data;

    /**
     *  @brief Operation when the data_length field is 0.
     *  @details
     *   If the data_length is other than 0, this field is ignored.
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_DATA_0_CLEAR(0x01)</td>
     *              <td>
     *                  Clear the advertising data/scan response data/periodic advertising data
     *                  in the advertising set.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_DATA_0_DID_UPD(0x02)</td>
     *              <td>Update Advertising DID without changing advertising data.
     *                  If the data_type field is BLE_GAP_ADV_DATA_MODE, this value is allowed.
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t zero_length_flag;
} st_ble_gap_adv_data_t;

/******************************************************************************************************************//**
 * @struct st_ble_gap_perd_adv_param_t
 * @brief  Periodic advertising parameter.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Advertising handle identifying the advertising set to be set periodic advertising parameter.
     *  @details
     *  Valid range is 0x00 - 0x03.
     */
    uint8_t adv_hdl;

    /**
     *  @brief Periodic ADV Properties.
     *  @details
     *  The prop_type field is set to the following values.\n
     *  If the type of the periodic advertising data cannot be applied from the following, set 0x0000.
     *    |              macro                 |   description                                                |
     *    |:---------------------------------- |:------------------------------------------------------------ |
     *    | BLE_GAP_PERD_PROP_TX_POWER(0x0040) |  Indicate that periodic advertising data includes Tx Power.  |
     */
    uint16_t prop_type;

    /**
     *  @brief Minimum Periodic Advertising Interval.
     *  @details
     *  Time(ms) = perd_intv_min * 1.25.\n
     *  Valid range is 0x0006 - 0xFFFF.
     */
    uint16_t perd_intv_min;

    /**
     *  @brief Maximum Periodic Advertising Interval.
     *  @details
     *  Time(ms) = perd_intv_max * 1.25.\n
     *  Valid range is 0x0006 - 0xFFFF.
     */
    uint16_t perd_intv_max;
} st_ble_gap_perd_adv_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_scan_phy_param_t
 *  @brief  Scan parameters per scan PHY.
 *  @details In case of start scanning with both 1M PHY and Coded PHY,
 *           adjust scan windows and scan intervals according to the following.\n
 *           ``` p_phy_param_1M->scan_window / p_phy_param_1M->scan_intv +
 *                p_phy_param_coded->scan_window / p_phy_param_coded->scan_intv <= 1  ```
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Scan type.
     *  @details
     *    |              macro             |   description               |
     *    |:-------------------------------|:--------------------------- |
     *    | BLE_GAP_SCAN_PASSIVE(0x00)     | Passive Scan.               |
     *    | BLE_GAP_SCAN_ACTIVE(0x01)      | Active Scan.                |
     */
    uint8_t scan_type;

    /**
     *  @brief Scan interval.
     *  @details
     *  interval(ms) = scan_intv * 0.625.\n
     *  Valid range is 0x0000 and 0x0004 - 0xFFFF.
     */
    uint16_t scan_intv;

    /**
     *  @brief Scan window.
     *  @details
     *  window(ms) = scan_window * 0.625.\n
     *  Valid range is 0x0000 and 0x0004 - 0xFFFF.
     */
    uint16_t scan_window;
} st_ble_gap_scan_phy_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_ext_scan_param_t
 *  @brief  Scan parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Own BD Address Type.
     *  @details
     *  In case of passive scan, this field is ignored.
     *  <table>
     *      <tr>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_PUBLIC(0x00)</td>
     *          <td>Public Address</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_RAND(0x01)</td>
     *          <td>Random Address</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_RPA_ID_PUBLIC(0x02)</td>
     *          <td>
     *              Resolvable Private Address.<BR/>
     *              If the IRK of local device has not been registered in Resolving List,
     *              public address is used.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_ADDR_RPA_ID_RANDOM(0x03)</td>
     *          <td>
     *              Resolvable Private Address.<BR/>
     *              If the IRK of local device has not been registered in Resolving List,
     *              the random address set by R_BLE_GAP_SetRandAddr() is used.
     *          </td>
     *      </tr>
     *  </table>
     */
    uint8_t o_addr_type;

    /**
     *  @brief Scan Filter Policy.
     *  @details
     *  <table>
     *      <tr>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SCAN_ALLOW_ADV_ALL(0x00)</td>
     *          <td>
     *              Accept all advertising and scan response PDUs except directed advertising
     *              PDUs not addressed to local device.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SCAN_ALLOW_ADV_WLST(0x01)</td>
     *          <td>
     *              Accept only advertising and scan response PDUs from remote devices
     *              whose address is registered in the White List.<BR/>
     *              Directed advertising PDUs which are not addressed to local device is ignored.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED(0x02)</td>
     *          <td>
     *              Accept all advertising and scan response PDUs except directed advertising
     *              PDUs whose the target address is identity address but doesn't address local device.
     *              However directed advertising PDUs whose the target address is the local resolvable private address
     *              are accepted.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SCAN_ALLOW_ADV_EXCEPT_DIRECTED_WLST(0x03)</td>
     *          <td>Accept all advertising and scan response PDUs.<BR/>
     *              The following are excluded.<BR/>
     *              <ul>
     *                  <li>
     *                      Advertising and scan response PDUs where the advertiser's
     *                      identity address is not in the White List.
     *                  </li>
     *                  <li>
     *                      Directed advertising PDUs whose the target address is identity address
     *                      but doesn't address local device.
     *                      However directed advertising PDUs whose the target address is the local
     *                      resolvable private address are accepted.
     *                  </li>
     *              </ul>
     *          </td>
     *      </tr>
     *  </table>
     */
    uint8_t filter_policy;

    /**
     *  @brief Scan parameters 1M PHY.
     *  @details When this field is NULL, Controller doesn't set the scan parameters for 1M PHY.
     */
    st_ble_gap_scan_phy_param_t * p_phy_param_1M;

    /**
     *  @brief Scan parameters Coded PHY.
     *  @details When this field is NULL, Controller doesn't set the scan parameters for Coded PHY.
     */
    st_ble_gap_scan_phy_param_t * p_phy_param_coded;
} st_ble_gap_ext_scan_param_t;

/******************************************************************************************************************//**
 * @brief  Scan parameters.
 * @sa st_ble_gap_ext_scan_param_t
 **********************************************************************************************************************/
typedef st_ble_gap_ext_scan_param_t st_ble_gap_scan_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_scan_on_t
 *  @brief  Parameters configured when scanning starts.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Procedure type.
     *  @details
     *  <table>
     *      <tr>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SC_PROC_OBS(0x00)</td>
     *          <td>
     *              Observation Procedure.<BR/>
     *              Notify all advertising PDUs.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SC_PROC_LIM(0x01)</td>
     *          <td>
     *              Limited Discovery Procedure.<BR/>
     *              Notify advertising PDUs from only devices in the limited discoverable mode.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SC_PROC_GEN(0x02)</td>
     *          <td>
     *              General Discovery Procedure.<BR/>
     *              Notify advertising PDUs from devices in the limited discoverable mode and
     *              the general discoverable mode.
     *          </td>
     *      </tr>
     *  </table>
     */
    uint8_t proc_type;

    /**
     *  @brief Filter duplicates.
     *  @details
     *  <table>
     *      <tr>
     *          <th>macro</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SCAN_FILT_DUPLIC_DISABLE(0x00)</td>
     *          <td>Duplicate filter disabled.</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SCAN_FILT_DUPLIC_ENABLE(0x01)</td>
     *          <td>Duplicate filter enabled.</td>
     *      </tr>
     *      <tr>
     *          <td>BLE_GAP_SCAN_FILT_DUPLIC_ENABLE_FOR_PERIOD(0x02)</td>
     *          <td>Duplicate filtering enabled, reset for each scan period</td>
     *      </tr>
     *  </table>
     */
    uint8_t filter_dups;

    /**
     *  @brief Scan duration.
     *  @details Time(ms) = duration * 10.\n
     *           Valid range is 0x0000 - 0xFFFF.\n
     *           If this field is set to 0x0000, scanning is continued until R_BLE_GAP_StopScan() is called.\n
     *           When the period field is zero and the time specified the duration field expires,
     *           BLE_GAP_EVENT_SCAN_TO event notifies the application layer that scanning stops.
     */
    uint16_t duration;

    /**
     *  @brief Scan period.
     *  @details Time(s) = N * 1.28.\n
     *           Valid range is 0x0000 - 0xFFFF.\n
     *           If the duration field is set to 0x0000, this field is ignored.
     */
    uint16_t period;
} st_ble_gap_scan_on_t;

/******************************************************************************************************************//**
 * @struct st_ble_gap_conn_param_t
 * @brief  Connection parameters included in connection interval, slave latency, supervision timeout, ce length.
 * @details This structure is used in R_BLE_GAP_CreateConn() and R_BLE_GAP_UpdConn().
 *
 * Set the fields in this structure to match the following condition.
 *
 * Supervision_timeout(ms) >= (1 + conn_latency) * conn_intv_max_Time(ms)
 *
 *  conn_intv_max_Time(ms) = conn_intv_max * 1.25
 *  Supervision_timeout(ms) = sup_to * 10
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Minimum connection interval.
     *  @details
     *           Time(ms) = conn_intv_min * 1.25.\n
     *           Valid range is 0x0006 - 0x0C80.
     */
    uint16_t conn_intv_min;

    /**
     *  @brief Maximum connection interval.
     *  @details
     *           Time(ms) = conn_intv_max * 1.25.\n
     *           Valid range is 0x0006 - 0x0C80.
     */
    uint16_t conn_intv_max;

    /**
     *  @brief Slave latency.
     *  @details
     *           Valid range is 0x0000 - 0x01F3.
     */
    uint16_t conn_latency;

    /**
     *  @brief Supervision timeout.
     *  @details
     *           Time(ms) = sup_to * 10.\n
     *           Valid range is 0x000A - 0x0C80.
     */
    uint16_t sup_to;

    /**
     *  @brief Minimum CE Length.
     *  @details
     *           Valid range is 0x0000 - 0xFFFF.
     */
    uint16_t min_ce_length;

    /**
     *  @brief Maximum CE Length.
     *  @details
     *           Valid range is 0x0000 - 0xFFFF.
     */
    uint16_t max_ce_length;
} st_ble_gap_conn_param_t;

/******************************************************************************************************************//**
 * @struct st_ble_gap_conn_phy_param_t
 * @brief  Connection parameters per PHY.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief  Scan interval.
     *  @details
     *  Time(ms) = scan_intv * 0.625.\n
     *  Valid range is 0x0004 - 0xFFFF.
     */
    uint16_t scan_intv;

    /**
     *  @brief  Scan window.
     *  @details
     *  Time(ms) = scan_window  * 0.625.\n
     *  Valid range is 0x0004 - 0xFFFF.
     */
    uint16_t scan_window;

    /**
     *  @brief  Connection interval, slave latency, supervision timeout, and CE length.
     */
    st_ble_gap_conn_param_t * p_conn_param;
} st_ble_gap_conn_phy_param_t;

/******************************************************************************************************************//**
 * @struct st_ble_gap_create_conn_param_t
 * @brief  Connection parameters used in R_BLE_GAP_CreateConn().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief This field specifies whether the White List is used or not, when connecting with a remote device.
     *  @details
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_INIT_FILT_USE_ADDR(0x00)</td>
     *              <td>White List is not used.<BR/>
     *                  The remote device to be connected is specified by the <i>remote_bd_addr</i> field and <BR/>
     *                  the <i>remote_bd_addr_type</i> field is used.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_INIT_FILT_USE_WLST(0x01)</td>
     *              <td>White List is used.<BR/>
     *                  The remote device registered in White List is connected with local device.<BR/>
     *                  The <i>remote_bd_addr</i> field and the <i>remote_bd_addr_type</i> field are ignored.
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t init_filter_policy;

    /**
     *  @brief Address of the device to be connected.
     *  @note   The BD address setting format is little endian. \n
     *          If the address is "AA:BB:CC:DD:EE:FF", set the byte array in the order
     *          {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA}.
     */
    uint8_t remote_bd_addr[BLE_BD_ADDR_LEN];

    /**
     *  @brief  Address type of the device to be connected.
     *  @details
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_ADDR_PUBLIC(0x00)</td>
     *              <td>Public Address or Public Identity Address</td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_ADDR_RAND(0x01)</td>
     *              <td>Random Address or Random (Static) Identity Address</td>
     *          </tr>
     *      </table>
     */
    uint8_t remote_bd_addr_type;

    /**
     *  @brief  Address type which local device uses in creating a link with the remote device.
     *  @details
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_ADDR_PUBLIC(0x00)</td>
     *              <td>Public Address</td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_ADDR_RAND(0x01)</td>
     *              <td>Random Address</td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_ADDR_RPA_ID_PUBLIC(0x02)</td>
     *              <td>
     *                  Resolvable Private Address.\n
     *                  If the IRK of local device has not been registered in Resolving List,
     *                  public address is used.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_ADDR_RPA_ID_RANDOM(0x03)</td>
     *              <td>
     *                  Resolvable Private Address.\n
     *                  If the IRK of local device has not been registered in Resolving List,
     *                  the random address set by R_BLE_GAP_SetRandAddr().
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t own_addr_type;

    /**
     *  @brief Connection parameters for 1M PHY.
     *  @details If this field is set to NULL, 1M PHY is not used in connecting.
     */
    st_ble_gap_conn_phy_param_t * p_conn_param_1M;

    /**
     *  @brief Connection parameters for 2M PHY.
     *  @details If this field is set to NULL, 2M PHY is not used in connecting.
     */
    st_ble_gap_conn_phy_param_t * p_conn_param_2M;

    /**
     *  @brief Connection parameters for Coded PHY.
     *  @details If this field is set to NULL, Coded PHY is not used in connecting.
     */
    st_ble_gap_conn_phy_param_t * p_conn_param_coded;
} st_ble_gap_create_conn_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_rslv_list_key_set_t
 *  @brief  IRK of a remote device and IRK type of local device used in R_BLE_GAP_ConfRslvList().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief IRK of a remote device to be registered in the Resolving List.
     */
    uint8_t remote_irk[BLE_GAP_IRK_SIZE];

    /**
     *  @brief IRK type of the local device to be registered in the Resolving List.
     *  @details
     *               |              macro                    |   description                                      |
     *               |:------------------------------------- |:-------------------------------------------------- |
     *               | BLE_GAP_RL_LOC_KEY_ALL_ZERO(0x00)     | All-zero IRK.                                      |
     *               | BLE_GAP_RL_LOC_KEY_REGISTERED(0x01)    | The IRK registered by R_BLE_GAP_SetLocIdInfo().   |
     */
    uint8_t local_irk_type;
} st_ble_gap_rslv_list_key_set_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_set_phy_param_t
 *  @brief  PHY configuration parameters used in R_BLE_GAP_SetPhy().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Transmitter PHY preference.
     *  @details The tx_phys field is set to a bitwise OR of the following values. All other values are ignored.
     *               |              macro                    |   description                      |
     *               |:------------------------------------- |:---------------------------------- |
     *               | BLE_GAP_SET_PHYS_HOST_PREF_1M(0x01)   | Use 1M PHY for Transmitter PHY.    |
     *               | BLE_GAP_SET_PHYS_HOST_PREF_2M(0x02)   | Use 2M PHY for Transmitter PHY.    |
     *               | BLE_GAP_SET_PHYS_HOST_PREF_CD(0x04)   | Use Coded PHY for Transmitter PHY. |
     */
    uint8_t tx_phys;

    /**
     *  @brief Receiver PHY preference.
     *  @details The rx_phys field is set to a bitwise OR of the following values. All other values are ignored.
     *               |              macro                    |   description                      |
     *               |:------------------------------------- |:---------------------------------- |
     *               | BLE_GAP_SET_PHYS_HOST_PREF_1M(0x01)   | Use 1M PHY for Receiver PHY.       |
     *               | BLE_GAP_SET_PHYS_HOST_PREF_2M(0x02)   | Use 2M PHY for Receiver PHY.       |
     *               | BLE_GAP_SET_PHYS_HOST_PREF_CD(0x04)   | Use Coded PHY for Receiver PHY.    |
     */
    uint8_t rx_phys;

    /**
     *  @brief Coding scheme used in Coded PHY.
     *  @details Select one of the following.
     *               |              macro                       |   description           |
     *               |:---------------------------------------- |:----------------------- |
     *               | BLE_GAP_SET_PHYS_OP_HOST_NO_PREF(0x00)   | No preferred coding.    |
     *               | BLE_GAP_SET_PHYS_OP_HOST_PREF_S_2(0x01)  | Use S=2 coding.         |
     *               | BLE_GAP_SET_PHYS_OP_HOST_PREF_S_8(0x02)  | Use S=8 coding.         |
     */
    uint16_t phy_options;
} st_ble_gap_set_phy_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_set_def_phy_param_t
 *  @brief  PHY preferences which allows a remote device to set used in R_BLE_GAP_SetDefPhy().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Transmitter PHY preferences which a remote device may change.
     *  @details The tx_phys field is set to a bitwise OR of the following values.
     *           All other values are ignored.
     *          |              macro                    |   description                                               |
     *          |:------------------------------------- |:----------------------------------------------------------- |
     *          | BLE_GAP_SET_PHYS_HOST_PREF_1M(0x01)   | Allow a remote device to set 1M PHY for transmitter PHY.    |
     *          | BLE_GAP_SET_PHYS_HOST_PREF_2M(0x02)   | Allow a remote device to set 2M PHY for transmitter PHY.    |
     *          | BLE_GAP_SET_PHYS_HOST_PREF_CD(0x04)   | Allow a remote device to set Coded PHY for transmitter PHY. |
     */
    uint8_t tx_phys;

    /**
     *  @brief Receiver PHY preferences which a remote device may change.
     *  @details The rx_phys field is set to a bitwise OR of the following values.
     *           All other values are ignored.
     *          |              macro                    |   description                                            |
     *          |:------------------------------------- |:-------------------------------------------------------- |
     *          | BLE_GAP_SET_PHYS_HOST_PREF_1M(0x01)   | Allow a remote device to set 1M PHY for receiver PHY.    |
     *          | BLE_GAP_SET_PHYS_HOST_PREF_2M(0x02)   | Allow a remote device to set 2M PHY for receiver PHY.    |
     *          | BLE_GAP_SET_PHYS_HOST_PREF_CD(0x04)   | Allow a remote device to set Coded PHY for receiver PHY. |
     */
    uint8_t rx_phys;
} st_ble_gap_set_def_phy_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_auth_info_t
 *  @brief  Pairing parameters required from a remote device or
 *          information about keys distributed from a remote device.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Security level.
     *  @details
     *    |  value  |   description                                         |
     *    |:--------|:----------------------------------------------------- |
     *    | 0x01    | The remote device requests Unauthenticated pairing.   |
     *    | 0x02    | The remote device requests Authenticated pairing.     |
     */
    uint8_t security;

    /**
     *  @brief  Pairing mode.
     *  @details
     *    |  value  |   description                                         |
     *    |:--------|:----------------------------------------------------- |
     *    | 0x01    | The remote device requests Legacy pairing.            |
     *    | 0x02    | The remote device requests Secure Connections.        |
     */
    uint8_t pair_mode;

    /**
     *  @brief  Bonding policy.
     *  @details
     *    |  value  |   description                                                   |
     *    |:--------|:--------------------------------------------------------------- |
     *    | 0x00    | The remote device does not store the Bonding information.       |
     *    | 0x01    | The remote device stores the Bonding information.               |
     */
    uint8_t bonding;

    /**
     *  @brief  Encryption key size.
     */
    uint8_t ekey_size;
} st_ble_gap_auth_info_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_key_dist_t
 *  @brief  Keys distributed from a remote device.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   LTK.
     */
    uint8_t enc_info[BLE_GAP_LTK_SIZE];

    /**
     *  @brief   Ediv and rand.
     *           The first two bytes is ediv, the remaining bytes are rand.
     */
    uint8_t mid_info[BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE];

    /**
     *  @brief   IRK
     */
    uint8_t id_info[BLE_GAP_IRK_SIZE];

    /**
     *  @brief   Identity address. The first byte is address type. The remaining bytes are device address.
     */
    uint8_t id_addr_info[BLE_GAP_ID_ADDR_SIZE];

    /**
     *  @brief   CSRK
     */
    uint8_t sign_info[BLE_GAP_CSRK_SIZE];
} st_ble_gap_key_dist_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_key_ex_param_t
 *  @brief  This structure includes the distributed keys and negotiated LTK size.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   Key information.
     */
    st_ble_gap_key_dist_t * p_keys_info;

    /**
     * @brief   Type of the distributed keys.
     * @details
     *  This field is a bitwise OR of the following values.
     *  <table>
     *      <tr>
     *          <th>Bit Number</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>0</td>
     *          <td>
     *              LTK and Master Identification.<BR/>
     *              LTK is distributed in Secure Connections, even if the bit is 1.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>1</td>
     *          <td>IRK and Identity Address Information.</td>
     *      </tr>
     *      <tr>
     *          <td>2</td>
     *          <td>CSRK</td>
     *      </tr>
     *  </table>
     */
    uint8_t keys;

    /**
     *  @brief   The negotiated LTK size.
     */
    uint8_t ekey_size;
} st_ble_gap_key_ex_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_pairing_param_t
 *  @brief  Pairing parameters used in R_BLE_GAP_SetPairingParams().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief  IO capabilities of local device.
     *  @details
     *   Select one of the following.
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_IOCAP_DISPLAY_ONLY(0x00)</td>
     *              <td>
     *                  Output function : Local device has the ability to display a 6 digit decimal number.<BR/>
     *                  Input function  : None<BR/>
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_IOCAP_DISPLAY_YESNO(0x01)</td>
     *              <td>
     *                  Output function : Output function : Local device has the ability to
     *                                    display a 6 digit decimal number.<BR/>
     *                  Input function  : Local device has the ability to indicate 'yes' or 'no'<BR/>
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_IOCAP_KEYBOARD_ONLY(0x02)</td>
     *              <td>
     *                  Output function : None<BR/>
     *                  Input function  : Local device has the ability to input the number '0' - '9'.<BR/>
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_IOCAP_NOINPUT_NOOUTPUT(0x03)</td>
     *              <td>
     *                  Output function : None<BR/>
     *                  Input function  : None<BR/>
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_IOCAP_KEYBOARD_DISPLAY(0x04)</td>
     *              <td>
     *                  Output function : Output function : Local device has the ability to
     *                                                      display a 6 digit decimal number.<BR/>
     *                  Input function  : Local device has the ability to input the number '0' - '9'.<BR/>
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t iocap;

    /**
     *  @brief  MITM protection policy.
     *  @details
     *   Select one of the following.
     *    |              macro                 |  description                   |
     *    |:---------------------------------- |:------------------------------ |
     *    | BLE_GAP_SEC_MITM_BEST_EFFORT(0x00) | MITM Protection not required.  |
     *    | BLE_GAP_SEC_MITM_STRICT (0x01)     | MITM Protection required.      |
     */
    uint8_t mitm;

    /**
     *  @brief  Bonding policy.
     *  @details
     *    |              macro                 |   description                                     |
     *    |:---------------------------------- |:------------------------------------------------- |
     *    | BLE_GAP_BONDING_NONE(0x00)         | Local device doesn't stores Bonding information.  |
     *    | BLE_GAP_BONDING (0x01)             | Local device stores Bonding information.          |
     */
    uint8_t bonding;

    /**
     *  @brief Maximum LTK size(in bytes).
     *  @details
     *  Valid range is 7 - 16.\n
     *  This field shall be set to a value not less than the min_key_size field.
     */
    uint8_t max_key_size;

    /**
     *  @brief Minimum LTK size(in bytes).
     *  @details
     *  Valid range is 7 - 16.\n
     *  This field shall be set to a value not more than the max_key_size field.
     */
    uint8_t min_key_size;

    /**
     *  @brief Type of keys to be distributed from local device.
     *  @details
     *  The loc_key_dist field is set to a bitwise OR of the following values.
     *    |              macro             |   description               |
     *    |:-------------------------------|:--------------------------- |
     *    | BLE_GAP_KEY_DIST_ENCKEY(0x01)  | LTK                         |
     *    | BLE_GAP_KEY_DIST_IDKEY(0x02)   | IRK and Identity Address.   |
     *    | BLE_GAP_KEY_DIST_SIGNKEY(0x04) | CSRK                        |
     */
    uint8_t loc_key_dist;

    /**
     *  @brief Type of keys which local device requests a remote device to distribute.
     *  @details
     *  The rem_key_dist field is set to a bitwise OR of the following values.
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_KEY_DIST_ENCKEY(0x01)</td>
     *              <td>
     *                  LTK. In case of Secure Connections, LTK is notified even if this bit is not set.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_KEY_DIST_IDKEY(0x02)</td>
     *              <td>
     *                  IRK and Identity Address.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GAP_KEY_DIST_SIGNKEY(0x04)</td>
     *              <td>
     *                  CSRK
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t rem_key_dist;

    /**
     *  @brief Support for Key Press Notification in Passkey Entry.
     *  @details
     *    |              macro                       |   description                            |
     *    |:-----------------------------------------|:---------------------------------------- |
     *    | BLE_GAP_SC_KEY_PRESS_NTF_NOT_SPRT(0x00)  | Not support for Key Press Notification.  |
     *    | BLE_GAP_SC_KEY_PRESS_NTF_SPRT(0x01)      | Support for Key Press Notification.      |
     */
    uint8_t key_notf;

    /**
     *  @brief Determine whether to accept only Secure Connections or not.
     *  @details
     *    |              macro            |   description                                 |
     *    |:------------------------------|:--------------------------------------------- |
     *    | BLE_GAP_SC_BEST_EFFORT(0x00)  | Accept Legacy pairing and Secure Connections.  |
     *    | BLE_GAP_SC_STRICT(0x01)       |  Accept only Secure Connections.               |
     */
    uint8_t sec_conn_only;
} st_ble_gap_pairing_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_oob_data_t
 *  @brief  Oob data received from the remote device. This is used in R_BLE_GAP_SetRemOobData().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief OOB data used in Legacy Pairing.
     */
    uint8_t legacy_oob[BLE_GAP_LEGACY_OOB_SIZE];

    /**
     *  @brief OOB confirmation value used in Secure Connections.
     */
    uint8_t sc_cnf_val[BLE_GAP_OOB_CONFIRM_VAL_SIZE];

    /**
     *  @brief OOB rand used in Secure Connections.
     */
    uint8_t sc_rand[BLE_GAP_OOB_RANDOM_VAL_SIZE];
} st_ble_gap_oob_data_t;

/* ============================================== GAP Event Parameters ============================================== */

/*  Event Code : BLE_GAP_EVENT_STACK_ON  : none */

/*  Event Code : BLE_GAP_EVENT_STACK_OFF : none */

/*  Event Code : BLE_GAP_EVENT_LOC_VER_INFO : st_ble_gap_loc_dev_info_evt_t */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_ver_num_t
 *  @brief  Version number of host stack.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief  Major version number.
     */
    uint8_t major;

    /**
     *  @brief  Minor version number.
     */
    uint8_t minor;

    /**
     *  @brief  Subminor version number.
     */
    uint8_t subminor;
} st_ble_gap_ver_num_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_loc_ver_info_t
 *  @brief  Version number of Controller.
 *  @details Refer Bluetooth SIG Assigned Number(https://www.bluetooth.com/specifications/assigned-numbers).
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief  Bluetooth HCI version.
     */
    uint8_t hci_ver;

    /**
     *  @brief   Bluetooth HCI revision.
     */
    uint16_t hci_rev;

    /**
     *  @brief   Link Layer revision.
     */
    uint8_t lmp_ver;

    /**
     *  @brief   Manufacturer ID.
     */
    uint16_t mnf_name;

    /**
     *  @brief   Link Layer subversion.
     */
    uint16_t lmp_sub_ver;
} st_ble_gap_loc_ver_info_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_loc_dev_info_evt_t
 *  @brief  Version information of local device.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   Bluetooth Device Address.
     */
    st_ble_dev_addr_t l_dev_addr;

    /**
     *  @brief   Version number of host stack in local device.
     */
    st_ble_gap_ver_num_t l_ver_num;

    /**
     *  @brief   Version number of Controller in local device.
     */
    st_ble_gap_loc_ver_info_t l_bt_info;
} st_ble_gap_loc_dev_info_evt_t;

/*  Event Code : BLE_GAP_EVENT_HW_ERR : st_ble_gap_hw_err_evt_t */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_hw_err_evt_t
 *  @brief  Hardware error that is notified from Controller.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   The hw_code field indicates the cause of the hardware error.
     */
    uint8_t hw_code;
} st_ble_gap_hw_err_evt_t;

/*  Event Code : BLE_GAP_EVENT_CMD_ERR: st_ble_gap_cmd_err_evt_t */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_cmd_err_evt_t
 *  @brief  HCI Command error.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   The opcode of HCI Command which caused the error.
     */
    uint16_t op_code;

    /**
     *  @brief   Module ID which caused the error.
     */
    uint32_t module_id;
} st_ble_gap_cmd_err_evt_t;

/*  Event Code : BLE_GAP_EVENT_ADV_REPT_IND: st_ble_gap_adv_rept_evt_t */
/* ADV report related Event defines */
/* Legacy ADV Report related structure */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_adv_rept_t
 *  @brief  Advertising Report.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief The number of Advertising Reports received.
     */
    uint8_t num;

    /**
     *  @brief Type of Advertising Packet.
     *  @details
     *  <table>
     *      <tr>
     *          <th>valuer</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>0x00</td>
     *          <td>Connectable and scannable undirected advertising(ADV_IND).</td>
     *      </tr>
     *      <tr>
     *          <td>0x01</td>
     *          <td>Connectable directed advertising(ADV_DIRECT_IND).</td>
     *      </tr>
     *      <tr>
     *          <td>0x02</td>
     *          <td>Scannable undirected advertising(ADV_SCAN_IND).</td>
     *      </tr>
     *      <tr>
     *          <td>0x03</td>
     *          <td>Non-connectable undirected advertising(ADV_NONCONN_IND).</td>
     *      </tr>
     *      <tr>
     *          <td>0x04</td>
     *          <td>Scan response(SCAN_RSP).</td>
     *      </tr>
     *  </table>
     */
    uint8_t adv_type;

    /**
     *  @brief Address type of the advertiser.
     *  @details
     *               |   value   |   description                                                   |
     *               |:--------- |:--------------------------------------------------------------- |
     *               | 0x00      | Public Address.                                                 |
     *               | 0x01      | Random Address.                                                 |
     *               | 0x02      | Public Identity Address which could be resolved in Controller.  |
     *               | 0x03      | Random Identity Address which could be resolved in Controller.  |
     */
    uint8_t addr_type;

    /**
     *  @brief Address of the advertiser.
     *  @note   The BD address setting format is little endian.
     */
    uint8_t * p_addr;

    /**
     *  @brief   Length of Advertising data(in bytes).
     *  @details Valid range is 0 - 31.
     */
    uint8_t len;

    /**
     *  @brief  RSSI(in dBm).
     *  @details Valid range is -127 <= tx_pwr <= 20 and 127.\n
     *           If the tx_pwr is 127, it means that RSSI could not be retrieved.
     */
    int8_t rssi;

    /**
     *  @brief   Advertising data/Scan Response Data.
     */
    uint8_t * p_data;
} st_ble_gap_adv_rept_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_ext_adv_rept_t
 *  @brief  Extended Advertising Report.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief The number of Advertising Reports received.
     */
    uint8_t num;

    /**
     *  @brief Type of Advertising Packet.
     *  @details
     *  <table>
     *      <tr>
     *          <th>Bit Number</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>0</td>
     *          <td>Connectable advertising.</td>
     *      </tr>
     *      <tr>
     *          <td>1</td>
     *          <td>Scannable advertising.</td>
     *      </tr>
     *      <tr>
     *          <td>2</td>
     *          <td>Directed advertising.</td>
     *      </tr>
     *      <tr>
     *          <td>3</td>
     *          <td>Scan response.</td>
     *      </tr>
     *      <tr>
     *          <td>4</td>
     *          <td>Legacy advertising PDU.</td>
     *      </tr>
     *      <tr>
     *          <td>5-6</td>
     *          <td>The status of Advertising Data/Scan Response Data.<BR/>
     *          Data Status:<BR/>
     *          00b = Complete <BR/>
     *          01b = Incomplete, more data come <BR/>
     *          10b = Incomplete, data truncated, no more to come <BR/>
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>All other bits</td>
     *          <td>Reserved for future use</td>
     *      </tr>
     *  </table>
     */
    uint16_t adv_type;

    /**
     *  @brief Address type of the advertiser.
     *  @details
     *               |   value   |   description                                                   |
     *               |:--------- |:--------------------------------------------------------------- |
     *               | 0x00      | Public Address.                                                 |
     *               | 0x01      | Random Address.                                                 |
     *               | 0x02      | Public Identity Address which could be resolved in Controller.  |
     *               | 0x03      | Random Identity Address which could be resolved in Controller.  |
     *               | 0xFF      | Anonymous advertisement.                                        |
     */
    uint8_t addr_type;

    /**
     *  @brief Address of the advertiser.
     *  @note  The BD address setting format is little endian.
     */
    uint8_t * p_addr;

    /**
     *  @brief The primary PHY configuration of the advertiser.
     *  @details
     *   The primary PHY configuration of the advertiser.
     *               |   value   |   description            |
     *               |:--------- |:------------------------ |
     *               | 0x01      | 1M PHY                   |
     *               | 0x03      | Coded PHY                |
     */
    uint8_t adv_phy;

    /**
     *  @brief The secondary PHY configuration of the advertiser.
     *  @details
     *               |   value   |   description                                                    |
     *               |:--------- |:---------------------------------------------------------------- |
     *               | 0x00      | Nothing has been received with Secondary Advertising Channel.    |
     *               | 0x01      | The Secondary Advertising PHY configuration was 1M PHY.          |
     *               | 0x02      | The Secondary Advertising PHY configuration was 2M PHY.          |
     *               | 0x03      | The Secondary Advertising PHY configuration was Coded PHY.       |
     */
    uint8_t sec_adv_phy;

    /**
     *  @brief Advertising SID included in the received Advertising Report.
     *  @details Valid range is 0 <= adv_sid <= 0x0F and 0xFF.\n
     *           If the adv_sid is 0xFF, there is no field which includes SID.
     */
    uint8_t adv_sid;

    /**
     *  @brief  TX power(in dBm).
     *  @details Valid range is -127 <= tx_pwr <= 20 and 127.\n
     *           If the tx_pwr is 127, it means that Tx power could not be retrieved.
     */
    int8_t tx_pwr;

    /**
     *  @brief  RSSI(in dBm).
     *  @details Valid range is -127 <= tx_pwr <= 20 and 127.\n
     *           If the tx_pwr is 127, it means that RSSI could not be retrieved.
     */
    int8_t rssi;

    /**
     *  @brief  Periodic Advertising interval.
     *  @details If the perd_adv_intv is 0x0000, it means that this advertising is not periodic advertising.\n
     *           If the perd_adv_intv is 0x0006 - 0xFFFF,
     *           it means that this field is the Periodic Advertising interval.\n
     *           Periodic Advertising interval = per_adv_intr * 1.25ms.
     */
    uint16_t perd_adv_intv;

    /**
     *  @brief The address type of Direct Advertising PDU.
     *  @details
     *               |   value   |   description                                                         |
     *               |:--------- |:--------------------------------------------------------------------- |
     *               | 0x00      | Public Address.                                                       |
     *               | 0x01      | Random Address.                                                       |
     *               | 0x02      | Public Identity Address which could be resolved in Controller.        |
     *               | 0x03      | Random Identity Address which could be resolved in Controller.        |
     *               | 0xFE      | Resolvable Privacy Address which could not be resolved in Controller. |
     */
    uint8_t dir_addr_type;

    /**
     *  @brief   Address of Direct Advertising PDU.
     *  @note   The BD address setting format is little endian.
     */
    uint8_t * p_dir_addr;

    /**
     *  @brief   Length of Advertising data(in bytes).
     *  @details Valid range is 0 - 229.
     */
    uint8_t len;

    /**
     *  @brief   Advertising data/Scan Response Data.
     */
    uint8_t * p_data;
} st_ble_gap_ext_adv_rept_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_perd_adv_rept_t
 *  @brief  Periodic Advertising Report.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   Sync handle.
     *  @details Valid range is 0x0000 - 0x0EFF.
     */
    uint16_t sync_hdl;

    /**
     *  @brief  TX power(in dBm).
     *  @details Valid range is -127 <= tx_pwr <= 20 and 127.\n
     *           If tx_pwr is 127, it means that Tx power could not be retrieved.
     */
    int8_t tx_pwr;

    /**
     *  @brief  RSSI(in dBm).
     *  @details Valid range is -127 <= rssi <= 20 and 127.\n
     *           If rssi is 127, it means that RSSI could not be retrieved.
     */
    int8_t rssi;

    /**
     *  @brief  Reserved for future use.
     */
    uint8_t rfu;

    /**
     *  @brief  Reserved for future use.
     *  @details
     *               |   value   |   description                                           |
     *               |:--------- |:------------------------------------------------------- |
     *               | 0x00      | Data Complete.                                          |
     *               | 0x01      | Data incomplete, more data to come.                     |
     *               | 0x02      | Data incomplete, data truncated, no more to come.       |
     */
    uint8_t data_status;

    /**
     *  @brief  Length of Periodic Advertising data(in bytes).
     *  @details Valid range is 0 - 247.
     */
    uint8_t len;

    /**
     *  @brief  Periodic Advertising data.
     */
    uint8_t * p_data;
} st_ble_gap_perd_adv_rept_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_adv_rept_evt_t
 *  @brief  Advertising report.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Data type.
     *  @details
     *               |        value         |   description                   |
     *               |:-------------------- |:---------------------------------- |
     *               | 0x00                 | Advertising Report.                |
     *               | 0x01                 |  Extended Advertising Report.   |
     *               | 0x02                 | Periodic Advertising Report.    |
     *
     *   If the BLE Protocol Stack library type is "all features",
     *   the adv_rpt_type field in a Legacy Advertising Report event is 0x01.
     */
    uint8_t adv_rpt_type;

    /**
     *  @brief Advertising Report.
     */
    union
    {
        /**
         *  @brief Advertising Report.
         */
        st_ble_gap_adv_rept_t * p_adv_rpt;

        /**
         *  @brief Extended Advertising Report.
         */
        st_ble_gap_ext_adv_rept_t * p_ext_adv_rpt;

        /**
         *  @brief Periodic Advertising Report.
         */
        st_ble_gap_perd_adv_rept_t * p_per_adv_rpt;
    } param;
} st_ble_gap_adv_rept_evt_t;

/* Event Code : BLE_GAP_EVENT_ADV_PARAM_SET_COMP       : st_ble_gap_adv_set_evt_t */
/* Event Code : BLE_GAP_EVENT_ADV_ON                   : st_ble_gap_adv_set_evt_t  */
/* Event Code : BLE_GAP_EVENT_PERD_ADV_ON              : st_ble_gap_adv_set_evt_t */
/* Event Code : BLE_GAP_EVENT_PERD_ADV_OFF             : st_ble_gap_adv_set_evt_t */
/* Event Code : BLE_GAP_EVENT_PERD_ADV_PARAM_SET_COMP  : st_ble_gap_adv_set_evt_t */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_adv_set_evt_t
 *  @brief  Advertising handle.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Advertising handle specifying the advertising set configured advertising parameters.
     */
    uint8_t adv_hdl;
} st_ble_gap_adv_set_evt_t;

/* Event Code : BLE_GAP_EVENT_ADV_OFF              : st_ble_gap_adv_off_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_adv_off_evt_t
 *  @brief  Information about the advertising set which stops advertising.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Advertising handle identifying the advertising set which has stopped advertising.
     *  @details Valid range is 0x00 - 0x03.
     */
    uint8_t adv_hdl;

    /**
     *  @brief  The reason for stopping advertising.
     *  @details
     *      <table>
     *          <tr>
     *              <th>value</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>0x01</td>
     *              <td>
     *                  Advertising has been stopped by R_BLE_GAP_StopAdv().
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>0x02</td>
     *              <td>
     *                  Because the duration specified by R_BLE_GAP_StartAdv() was expired,
     *                  advertising has terminated.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>0x03</td>
     *              <td>
     *                  Because the max_extd_adv_evts parameter specified by R_BLE_GAP_StartAdv() was reached,
     *                  advertising has terminated.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>0x04</td>
     *              <td>
     *                   Because the connection was established with the remote device, advertising has terminated.
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t reason;

    /**
     *  @brief Connection handle.
     *  @details  If the reason field is 0x04, this field indicates connection handle identifying
     *            the remote device connected with local device.
     *            If other reasons, ignore this field.
     */
    uint16_t conn_hdl;

    /**
     *  @brief  The number of the advertising event that has been received until advertising has terminated.
     *  @details  If max_extd_adv_evts by R_BLE_GAP_StartAdv() is not 0, this parameter is valid.
     */
    uint8_t num_comp_ext_adv_evts;
} st_ble_gap_adv_off_evt_t;

/* Event Code : BLE_GAP_EVENT_ADV_DATA_UPD_COMP : st_ble_gap_adv_data_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_adv_data_evt_t
 *  @brief  This structure notifies that advertising data has been set to Controller by R_BLE_GAP_SetAdvSresData().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Advertising handle identifying the advertising set to
     *         which advertising data/scan response data/periodic advertising data is set.
     */
    uint8_t adv_hdl;

    /**
     *  @brief Type of the data set to the advertising set.
     *  @details
     *    | value                                |   description               |
     *    |:------------------------------------ |:--------------------------- |
     *    | BLE_GAP_ADV_DATA_MODE(0x00)          |  Advertising data           |
     *    | BLE_GAP_SCAN_RSP_DATA_MODE(0x01)     |  Scan response data         |
     *    | BLE_GAP_PERD_ADV_DATA_MODE(0x02)     |  Periodic advertising data  |
     */
    uint8_t data_type;
} st_ble_gap_adv_data_evt_t;

/* Event Code : BLE_GAP_EVENT_ADV_SET_REMOVE_COMP : st_ble_gap_rem_adv_set_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_rem_adv_set_evt_t
 *  @brief  This structure notifies that an advertising set has been removed.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief  This field indicates that the advertising set has been removed or cleared.
     *  @details
     *    | value    |   description                           |
     *    |:-------- |:--------------------------------------- |
     *    | 0x01     |  The advertising set has been removed.  |
     *    | 0x02     |  The advertising set has been cleared.  |
     */
    uint8_t remove_op;

    /**
     *  @brief Advertising handle identifying the advertising set which has been removed.
     *  @details  If the advertising set has been cleared, this field is ignored.
     */
    uint8_t adv_hdl;
} st_ble_gap_rem_adv_set_evt_t;

/* Event Code : BLE_GAP_EVENT_SCAN_ON  : none  */
/* Event Code : BLE_GAP_EVENT_SCAN_OFF : none  */

/* Event Code : BLE_GAP_EVENT_CONN_IND : st_ble_gap_conn_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_conn_evt_t
 *  @brief  This structure notifies that a link has been established.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Connection handle identifying the created link.
     */
    uint16_t conn_hdl;

    /**
     *  @brief  The role of the link.
     *  @details
     *    | value    |   description  |
     *    |:-------- |:-------------- |
     *    | 0x00     |  Master        |
     *    | 0x01     |  Slave         |
     */
    uint8_t role;

    /**
     *  @brief  Address type of the remote device.
     *  @details
     *  <table>
     *      <tr>
     *          <th>value</th>
     *          <th>description</th>
     *      </tr>
     *      <tr>
     *          <td>0x00</td>
     *          <td>Public Address</td>
     *      </tr>
     *      <tr>
     *          <td>0x01</td>
     *          <td>Random Address</td>
     *      </tr>
     *      <tr>
     *          <td>0x02</td>
     *          <td>Public Identity Address.<BR/>
     *              It indicates that the Controller could resolve the resolvable private address of the remote device.
     *          </td>
     *      </tr>
     *      <tr>
     *          <td>0x03</td>
     *          <td>Random Identity Address.<BR/>
     *              It indicates that the Controller could resolve the resolvable private address of the remote device.
     *          <td>
     *      </tr>
     *  </table>
     */
    uint8_t remote_addr_type;

    /**
     *  @brief Address of the remote device.
     *  @note   The BD address setting format is little endian.
     */
    uint8_t remote_addr[BLE_BD_ADDR_LEN];

    /**
     *  @brief Resolvable private address that local device used in connection procedure.
     *  @details
     *  The local device address used in creating the link when the address type was set to
     *  BLE_GAP_ADDR_RPA_ID_PUBLIC or BLE_GAP_ADDR_RPA_ID_RANDOM by R_BLE_GAP_SetAdvParam() or
     *  R_BLE_GAP_CreateConn().
     *  If the address type was set to other than BLE_GAP_ADDR_RPA_ID_PUBLIC and
     *  BLE_GAP_ADDR_RPA_ID_RANDOM, this field is set to all-zero.
     *  @note   The BD address setting format is little endian.
     */
    uint8_t local_rpa[BLE_BD_ADDR_LEN];

    /**
     *  @brief Resolvable private address that the remote device used in connection procedure.
     *  @details
     *  This field indicates the remote resolvable private address when remote_addr_type is 0x02 or 0x03.
     *  If remote_addr_type is other than 0x02 and 0x03, this field is set to all-zero.
     *  @note   The BD address setting format is little endian.
     */
    uint8_t remote_rpa[BLE_BD_ADDR_LEN];

    /**
     *  @brief  Connection interval.
     *  @details
     *  Valid range is 0x0006 - 0x0C80.\n
     *  Time(ms) = conn_intv * 1.25.
     */
    uint16_t conn_intv;

    /**
     *  @brief  Slave latency.
     *  @details
     *  Valid range is 0x0000 - 0x01F3.
     */
    uint16_t conn_latency;

    /**
     *  @brief  Supervision timeout.
     *  @details
     *  Valid range is 0x000A - 0x0C80.Time(ms) = sup_to * 10.
     */
    uint16_t sup_to;

    /**
     *  @brief  Master_Clock_Accuracy.
     *  @details
     *    |  value   |   description               |
     *    |:---------|:--------------------------- |
     *    | 0x00     | 500ppm                      |
     *    | 0x01     | 250ppm                      |
     *    | 0x02     | 150ppm                      |
     *    | 0x03     | 100ppm                      |
     *    | 0x04     | 75ppm                       |
     *    | 0x05     | 50ppm                       |
     *    | 0x06     | 30ppm                       |
     *    | 0x07     | 20ppm                       |
     */
    uint8_t clk_acc;
} st_ble_gap_conn_evt_t;

/* Event Code : BLE_GAP_EVENT_DISCONN_IND : st_ble_gap_disconn_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_disconn_evt_t
 *  @brief  This structure notifies that a link has been disconnected.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   Connection handle identifying the link disconnected.
     */
    uint16_t conn_hdl;

    /**
     *  @brief   The reason for disconnection.
     *  @details
     *  Refer Core Specification Vol.2 Part D ,"2 Error Code Descriptions".
     */
    uint8_t reason;
} st_ble_gap_disconn_evt_t;

/* Event Code : BLE_GAP_EVENT_CONN_CANCEL_COMP : none  */

/* Event Code : BLE_GAP_EVENT_WHITE_LIST_CONF_COMP : st_ble_gap_white_list_conf_evt_t  */

/* Event Code : BLE_GAP_EVENT_RAND_ADDR_SET_COMP : none  */

/* Event Code : BLE_GAP_EVENT_CH_MAP_RD_COMP : st_ble_gap_rd_ch_map_evt_t  */
/* Read Channel MAP */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_rd_ch_map_evt_t
 *  @brief  This structure notifies that Channel Map has been retrieved by R_BLE_GAP_ReadChMap().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Connection handle identifying the link whose Channel Map was retrieved.
     */
    uint16_t conn_hdl;

    /**
     *  @brief   Channel Map.
     */
    uint8_t ch_map[BLE_GAP_CH_MAP_SIZE];
} st_ble_gap_rd_ch_map_evt_t;

/* Event Code : BLE_GAP_EVENT_CH_MAP_SET_COMP : none  */

/* Event Code : BLE_GAP_EVENT_RSSI_RD_COMP  : st_ble_gap_rd_rssi_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_rd_rssi_evt_t
 *  @brief  This structure notifies that RSSI has been retrieved by R_BLE_GAP_ReadRssi().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Connection handle identifying the link whose RSSI was retrieved.
     */
    uint16_t conn_hdl;

    /**
     *  @brief    RSSI(in dBm).
     *  @details
     *  Valid range is -127 < rssi < 20 and 127.\n
     *  If this field is 127, it indicates that RSSI could not be retrieved.
     */
    int8_t rssi;
} st_ble_gap_rd_rssi_evt_t;

/* Event Code : BLE_GAP_EVENT_GET_REM_DEV_INFO  : st_ble_gap_dev_info_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_dev_info_evt_t
 *  @brief This structure notifies that information about remote device has been retrieved by R_BLE_GAP_GetRemDevInfo().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device whose information has been retrieved.
     */
    uint16_t conn_hdl;

    /**
     *  @brief  Information about the remote device. This field is a bitwise OR of the following values.
     *  @details
     *    |  Bit Number        |   description                   |
     *    |:-------------------|:------------------------------- |
     *    | bit0               | Address                         |
     *    | bit1               | Version, company_id, subversion |
     *    | bit2               | Feature                         |
     *    | All other bits     | Reserved for future use         |
     */
    uint8_t get_status;

    /**
     *  @brief      Address of the remote device.
     */
    st_ble_dev_addr_t addr;

    /**
     *  @brief    The version of Link Layer of the remote device.
     *  @details
     *  Refer to Bluetooth SIG Assigned Number
     *  (https://www.bluetooth.com/specifications/assigned-numbers) regarding defined number.
     */
    uint8_t version;

    /**
     *  @brief    The manufacturer ID of the remote device.
     *  @details
     *  Refer to Bluetooth SIG Assigned Number
     *  (https://www.bluetooth.com/specifications/assigned-numbers) regarding defined number.
     */
    uint16_t company_id;

    /**
     *  @brief       The subversion of Link Layer.
     */
    uint16_t subversion;

    /**
     *  @brief    LE feature supported in the remote device.
     *  @details
     *  Refer to Core Spec Vol 6, Part B 4.6 FEATURE SUPPORT.
     */
    uint8_t features[BLE_GAP_REM_FEATURE_SIZE];
} st_ble_gap_dev_info_evt_t;

/* Event Code : BLE_GAP_EVENT_CONN_PARAM_UPD_COMP  : st_ble_gap_conn_upd_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_conn_upd_evt_t
 *  @brief  This structure notifies that connection parameters has been updated.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the connection whose parameters has been updated.
     */
    uint16_t conn_hdl;

    /**
     *  @brief    Updated Connection Interval.
     *  @details
     *  Valid range is 0x0006 - 0x0C80.\n
     *  Time(ms) = conn_intv * 1.25.
     */
    uint16_t conn_intv;

    /**
     *  @brief    Updated slave latency.
     *  @details
     *  Valid range is 0x0000 - 0x01F3.
     */
    uint16_t conn_latency;

    /**
     *  @brief    Updated supervision timeout.
     *  @details
     *  Valid range is 0x000A - 0x0C80.\n
     *  Time(ms) = sup_to * 10.
     */
    uint16_t sup_to;
} st_ble_gap_conn_upd_evt_t;

/* Event Code : BLE_GAP_EVENT_CONN_PARAM_UPD_REQ   : st_ble_gap_conn_upd_req_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_conn_upd_req_evt_t
 *  @brief  This structure notifies that a request for connection parameters update has been received.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief      Connection handle identifying the link that was requested to update connection parameters.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Minimum connection interval.
     *  @details
     *  Valid range is 0x0006 - 0x0C80.\n
     *  Time(ms) = conn_intv_min * 1.25.
     */
    uint16_t conn_intv_min;

    /**
     *  @brief     Maximum connection interval.
     *  @details
     *  Valid range is 0x0006 - 0x0C80.\n
     *  Time(ms) = conn_intv_max * 1.25.
     */
    uint16_t conn_intv_max;

    /**
     *  @brief     Slave latency.
     *  @details
     *  Valid range is 0x0000 - 0x01F3.
     */
    uint16_t conn_latency;

    /**
     *  @brief     Supervision timeout.
     *  @details
     *  Valid range is 0x000A - 0x0C80.\n
     *  Time(ms) = sup_to * 10
     */
    uint16_t sup_to;
} st_ble_gap_conn_upd_req_evt_t;

/* Event Code : RBLE_GAP_EVENT_CONN_PARAM_UPD_RSP        : st_ble_gap_conn_hdl_evt_t  */
/* Event Code : BLE_GAP_EVENT_AUTH_PL_TO_EXPIRED   : st_ble_gap_conn_hdl_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_conn_hdl_evt_t
 *  @brief  This structure notifies that a GAP Event that includes only connection handle has occurred.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle.
     */
    uint16_t conn_hdl;
} st_ble_gap_conn_hdl_evt_t;

/* Event Code : BLE_GAP_EVENT_DATA_LEN_CHG : st_ble_gap_data_len_chg_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_data_len_chg_evt_t
 *  @brief  This structure notifies that the packet data length has been updated.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the link that updated Data Length.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Updated transmission packet size(in bytes).
     *  @details
     *  Valid range is 0x001B - 0x00FB.
     */
    uint16_t tx_octets;

    /**
     *  @brief     Updated transmission time(us).
     *  @details
     *  Valid range is 0x0148 - 0x4290.
     */
    uint16_t tx_time;

    /**
     *  @brief     Updated receive packet size(in bytes).
     *  @details
     *  Valid range is 0x001B - 0x00FB.
     */
    uint16_t rx_octets;

    /**
     *  @brief     Updated receive time(us).
     *  @details
     *  Valid range is 0x0148 - 0x4290.
     */
    uint16_t rx_time;
} st_ble_gap_data_len_chg_evt_t;

/* Event Code : BLE_GAP_EVENT_RSLV_LIST_CONF_COMP : st_ble_gap_rslv_list_conf_evt_t  */

/* Event Code : BLE_GAP_EVENT_RPA_EN_COMP : none  */
/* Event Code : BLE_GAP_EVENT_SET_RPA_TO_COMP       : none  */
/* Event Code : BLE_GAP_EVENT_RD_RPA_COMP           : st_ble_gap_rd_rpa_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_rd_rpa_evt_t
 *  @brief  This structure notifies that the local resolvable private address has been retrieved by R_BLE_GAP_ReadRpa().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     The resolvable private address of local device.
     */
    st_ble_dev_addr_t addr;
} st_ble_gap_rd_rpa_evt_t;

/* Event Code : BLE_GAP_EVENT_PHY_UPD      : st_ble_gap_phy_upd_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_phy_upd_evt_t
 *  @brief  This structure notifies that PHY for a connection has been updated.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the link that has been updated.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Transmitter PHY.
     *  @details
     *    |  value     |   description                                                |
     *    |:-----------|:------------------------------------------------------------ |
     *    | 0x01       | The transmitter PHY has been updated to 1M PHY.              |
     *    | 0x02       | The transmitter PHY has been updated to 2M PHY.              |
     *    | 0x03       | The transmitter PHY has been updated to Coded PHY.           |
     */
    uint8_t tx_phy;

    /**
     *  @brief     Receiver PHY.
     *  @details
     *    |  value     |   description                                                |
     *    |:-----------|:------------------------------------------------------------ |
     *    | 0x01       | The receiver PHY has been updated to 1M PHY.              |
     *    | 0x02       | The receiver PHY has been updated to 2M PHY.              |
     *    | 0x03       | The receiver PHY has been updated to Coded PHY.           |
     */
    uint8_t rx_phy;
} st_ble_gap_phy_upd_evt_t;

/* Event Code : BLE_GAP_EVENT_PHY_RD_COMP  : st_ble_gap_phy_rd_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_phy_rd_evt_t
 *  @brief  This structure notifies that the PHY settings has been retrieved by R_BLE_GAP_ReadPhy().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the link that has been retrieved the PHY settings.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Transmitter PHY.
     *  @details
     *    |  value     |   description                                                |
     *    |:-----------|:------------------------------------------------------------ |
     *    | 0x01       | The transmitter PHY has been updated to 1M PHY.              |
     *    | 0x02       | The transmitter PHY has been updated to 2M PHY.              |
     *    | 0x03       | The transmitter PHY has been updated to Coded PHY.           |
     */
    uint8_t tx_phy;

    /**
     *  @brief     Receiver PHY.
     *  @details
     *    |  value     |   description                                                |
     *    |:-----------|:------------------------------------------------------------ |
     *    | 0x01       | The receiver PHY has been updated to 1M PHY.              |
     *    | 0x02       | The receiver PHY has been updated to 2M PHY.              |
     *    | 0x03       | The receiver PHY has been updated to Coded PHY.           |
     */
    uint8_t rx_phy;
} st_ble_gap_phy_rd_evt_t;

/* Event Code : BLE_GAP_EVENT_PHY_SET_COMP   : st_ble_gap_conn_hdl_evt_t  */
/* Event Code : BLE_GAP_EVENT_SCAN_REQ_RECV  : st_ble_gap_scan_req_recv_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_scan_req_recv_evt_t
 *  @brief  This structure notifies that a Scan Request packet has been received from a Scanner.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Advertising handle identifying the advertising set that has received the Scan Request.
     */
    uint8_t adv_hdl;

    /**
     *  @brief      Address type of the Scanner.
     *  @details
     *    |  value     |   description                                                  |
     *    |:-----------|:-------------------------------------------------------------- |
     *    | 0x00       | Public Address.                                                |
     *    | 0x01       | Random Address.                                                |
     *    | 0x02       | Public Identity Address which could be resolved in Controller. |
     *    | 0x03       | Random Identity Address which could be resolved in Controller. |
     */
    uint8_t scanner_addr_type;

    /**
     *  @brief     Address of the Scanner.
     *  @note      The BD address setting format is little endian.
     */
    uint8_t scanner_addr[BLE_BD_ADDR_LEN];
} st_ble_gap_scan_req_recv_evt_t;

/* Event Code : BLE_GAP_EVENT_SYNC_EST  : st_ble_gap_sync_est_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_sync_est_evt_t
 *  @brief  This structure notifies that a Periodic sync has been established.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Sync handle identifying the Periodic Sync that has been established.
     */
    uint16_t sync_hdl;

    /**
     *  @brief     Advertising SID identifying the advertising set that has established the Periodic Sync.
     */
    uint8_t adv_sid;

    /**
     *  @brief      Address type of the advertiser.
     *  @details
     *    |  value     |   description                                                  |
     *    |:-----------|:-------------------------------------------------------------- |
     *    | 0x00       | Public Address.                                                |
     *    | 0x01       | Random Address.                                                |
     *    | 0x02       | Public Identity Address which could be resolved in Controller. |
     *    | 0x03       | Random Identity Address which could be resolved in Controller. |
     */
    uint8_t adv_addr_type;

    /**
     *  @brief     Address of the advertiser.
     *  @note   The BD address setting format is little endian.
     */
    uint8_t * p_adv_addr;

    /**
     *  @brief      Advertising PHY.
     *  @details
     *    |  value     |   description                |
     *    |:-----------|:---------------------------- |
     *    | 0x01       | Advertiser PHY is 1M PHY.    |
     *    | 0x02       | Advertiser PHY is 2M PHY.    |
     *    | 0x03       | Advertiser PHY is Coded PHY. |
     */
    uint8_t adv_phy;

    /**
     *  @brief     Periodic Advertising Interval.
     *  @details
     *  Valid range is 0x0006 - 0xFFFF.\n
     *  Time(ms) = perd_adv_intv * 1.25.
     */
    uint16_t perd_adv_intv;

    /**
     *  @brief  Advertiser Clock Accuracy.
     *  @details
     *    |  value   |   description               |
     *    |:---------|:--------------------------- |
     *    | 0x00     | 500ppm                      |
     *    | 0x01     | 250ppm                      |
     *    | 0x02     | 150ppm                      |
     *    | 0x03     | 100ppm                      |
     *    | 0x04     | 75ppm                       |
     *    | 0x05     | 50ppm                       |
     *    | 0x06     | 30ppm                       |
     *    | 0x07     | 20ppm                       |
     */
    uint8_t adv_clk_acc;
} st_ble_gap_sync_est_evt_t;

/* Event Code : BLE_GAP_EVENT_SYNC_TERM    : st_ble_gap_sync_hdl_evt_t  */
/* Event Code : BLE_GAP_EVENT_SYNC_LOST         : st_ble_gap_sync_hdl_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_sync_hdl_evt_t
 *  @brief  This structure notifies that a GAP Event that includes only sync handle has occurred.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Sync handle.
     */
    uint16_t sync_hdl;
} st_ble_gap_sync_hdl_evt_t;

/* Event Code : BLE_GAP_EVENT_SYNC_CREATE_CANCEL_COMP   : none  */
/* Event Code : BLE_GAP_EVENT_PERD_LIST_CONF_COMP       : st_ble_gap_perd_list_conf_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_white_list_conf_evt_t
 *  @brief  This structure notifies that White List has been configured.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     The operation for White List.
     *  @details
     *    |  value   |   description                            |
     *    |:---------|:---------------------------------------- |
     *    | 0x01     | A device was added to White List.        |
     *    | 0x02     | A device was deleted from White List.    |
     *    | 0x03     | White List was cleared.                  |
     */
    uint8_t op_code;

    /**
     *  @brief     The number or devices which have been added to or deleted from White List.
     */
    uint8_t num;
} st_ble_gap_white_list_conf_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_rslv_list_conf_evt_t
 *  @brief  This structure notifies that Resolving List has been configured.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     The operation for Resolving List.
     *  @details
     *    |  value   |   description                                |
     *    |:---------|:-------------------------------------------- |
     *    | 0x01     | A device was added to Resolving List.        |
     *    | 0x02     | A device was deleted from Resolving List.    |
     *    | 0x03     | Resolving List was cleared.                  |
     */
    uint8_t op_code;

    /**
     *  @brief     The number or devices which have been added to or deleted from Resolving List.
     */
    uint8_t num;
} st_ble_gap_rslv_list_conf_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_perd_list_conf_evt_t
 *  @brief  This structure notifies that Periodic Advertiser List has been configured.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     The operation for Periodic Advertiser List.
     *  @details
     *    |  value   |   description                                          |
     *    |:---------|:------------------------------------------------------ |
     *    | 0x01     | A device was added to Periodic Advertiser List.        |
     *    | 0x02     | A device was deleted from Periodic Advertiser List.    |
     *    | 0x03     | Periodic Advertiser List was cleared.                  |
     */
    uint8_t op_code;

    /**
     *  @brief     The number or devices which have been added to or deleted from Periodic Advertiser List.
     */
    uint8_t num;
} st_ble_gap_perd_list_conf_evt_t;

/* Event Code : BLE_GAP_EVENT_PRIV_MODE_SET_COMP   : st_ble_gap_set_priv_mode_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_set_priv_mode_evt_t
 *  @brief  This structure notifies that Privacy Mode has been configured.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     The number or devices which have been set privacy mode.
     */
    uint8_t num;
} st_ble_gap_set_priv_mode_evt_t;

/* Event Code : BLE_GAP_EVENT_PAIRING_REQ   : st_ble_gap_pairing_req_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_pairing_req_evt_t
 *  @brief  This structure notifies that a pairing request from a remote device has been received.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device that sent the pairing request.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     The address of the remote device.
     */
    st_ble_dev_addr_t bd_addr;

    /**
     *  @brief     The Pairing parameters of the remote device.
     */
    st_ble_gap_auth_info_t auth_info;
} st_ble_gap_pairing_req_evt_t;

/* Event Code : BLE_GAP_EVENT_PASSKEY_ENTRY_REQ   : st_ble_gap_conn_hdl_evt_t  */

/* Event Code : BLE_GAP_EVENT_PASSKEY_DISPLAY_REQ   : st_ble_gap_passkey_display_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_passkey_display_evt_t
 *  @brief  This structure notifies that a request for Passkey display in pairing has been received.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device that requested Passkey display.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Passkey.
     *  @details   This field is a 6 digit decimal number(000000-999999).
     */
    uint32_t passkey;
} st_ble_gap_passkey_display_evt_t;

/* Event Code : BLE_GAP_EVENT_NUM_COMP_REQ   : st_ble_gap_num_comp_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_num_comp_evt_t
 *  @brief  This structure notifies that a request for Numeric Comparison in pairing has been received.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device that requested Numeric Comparison.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     The number to be confirmed in Numeric Comparison.
     *  @details   This field is a 6 digit decimal number(000000-999999).
     */
    uint32_t numeric;
} st_ble_gap_num_comp_evt_t;

/* Event Code : BLE_GAP_EVENT_KEY_PRESS_NTF     : st_ble_gap_key_press_ntf_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_key_press_ntf_evt_t
 *  @brief  This structure notifies that the remote device has input a key in Passkey Entry
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device that input a key.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Type of the key that the remote device input.
     *  @details
     *    |  value   |   description                 |
     *    |:---------|:----------------------------- |
     *    | 0x00     | Passkey entry started.        |
     *    | 0x01     | Passkey digit entered.        |
     *    | 0x02     | Passkey digit erased.         |
     *    | 0x03     | Passkey cleared.              |
     *    | 0x04     | Passkey entry completed.      |
     */
    uint8_t key_type;
} st_ble_gap_key_press_ntf_evt_t;

/* Event Code : BLE_GAP_EVENT_PAIRING_COMP   : st_ble_gap_pairing_info_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_pairing_info_evt_t
 *  @brief  This structure notifies that the pairing has completed.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device that the pairing has been done with.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Address of the remote device.
     */
    st_ble_dev_addr_t bd_addr;

    /**
     *  @brief     Key information exchanged in pairing.
     *  @details   If local device supports bonding, store the information in non-volatile memory
     *             in order to set it to host stack after power re-supply.
     */
    st_ble_gap_auth_info_t auth_info;
} st_ble_gap_pairing_info_evt_t;

/* Event Code : BLE_GAP_EVENT_ENC_CHG   : st_ble_gap_enc_chg_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_enc_chg_evt_t
 *  @brief  This structure notifies that the encryption status of a link has been changed.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the link that has been changed.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Encryption Status.
     *  @details
     *    |  value   |   description                                            |
     *    |:---------|:-------------------------------------------------------- |
     *    | 0x00     | Encryption OFF.                                          |
     *    | 0x01     | Encryption ON.                                           |
     *    | 0x03     | Encryption updated by Encryption Key Refresh Completed.  |
     */
    uint8_t enc_status;
} st_ble_gap_enc_chg_evt_t;

/* Event Code : BLE_GAP_EVENT_PEER_KEY_INFO   : st_ble_gap_peer_key_info_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_peer_key_info_evt_t
 *  @brief  This structure notifies that the remote device has distributed the keys.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device that has distributed the keys.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Address of the remote device.
     */
    st_ble_dev_addr_t bd_addr;

    /**
     *  @brief     Distributed keys.
     *  @details
     *  If local device supports bonding, store the keys in non-volatile memory and
     *  at power re-supply set to the host stack by R_BLE_GAP_SetBondInfo().
     */
    st_ble_gap_key_ex_param_t key_ex_param;
} st_ble_gap_peer_key_info_evt_t;

/* Event Code : BLE_GAP_EVENT_EX_KEY_REQ   : st_ble_gap_conn_hdl_evt_t  */

/* Event Code : BLE_GAP_EVENT_LTK_REQ      : st_ble_gap_ltk_req_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_ltk_req_evt_t
 *  @brief  This structure notifies that a LTK request from a remote device has been received.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device which requests for the LTK.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     Ediv.
     */
    uint16_t ediv;

    /**
     *  @brief     Rand.
     */
    uint8_t * p_peer_rand;
} st_ble_gap_ltk_req_evt_t;

/* Event Code : BLE_GAP_EVENT_LTK_RSP_COMP      : st_ble_gap_ltk_req_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_ltk_rsp_evt_t
 *  @brief  This structure notifies that local device has replied to the LTK request from the remote device.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Connection handle identifying the remote device to be sent the response to the LTK request.
     */
    uint16_t conn_hdl;

    /**
     *  @brief     The response to the LTK request.
     *  @details
     *    |  value   |   description                                                           |
     *    |:---------|:----------------------------------------------------------------------- |
     *    | 0x00     | Local device replied with the stored LTK.                               |
     *    | 0x01     | Local device rejected the LTK request, because the LTK was not found.   |
     */
    uint8_t response;
} st_ble_gap_ltk_rsp_evt_t;

/* Event Code : BLE_GAP_EVENT_SC_OOB_CREATE_COMP      : st_ble_gap_sc_oob_data_evt_t  */

/******************************************************************************************************************//**
 *  @struct st_ble_gap_sc_oob_data_evt_t
 *  @brief  This structure notifies that OOB data for Secure Connections has been generated by R_BLE_GAP_CreateScOobData().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Confirmation value(16 bytes) of OOB Data.
     */
    uint8_t * p_sc_oob_conf;

    /**
     *  @brief Rand(16bytes) of OOB Data.
     */
    uint8_t * p_sc_oob_rand;
} st_ble_gap_sc_oob_data_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gap_bond_info_t
 *  @brief  Bonding information used in R_BLE_GAP_SetBondInfo().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Address of the device which exchanged the keys.
     */
    st_ble_dev_addr_t * p_addr;

    /**
     *  @brief Information about the keys.
     */
    st_ble_gap_auth_info_t * p_auth_info;

    /**
     *  @brief Keys distributed from the remote device in paring.
     */
    st_ble_gap_key_ex_param_t * p_keys;
} st_ble_gap_bond_info_t;

/*@}*/

/* ================================================= GAP Event Code ================================================= */

/** @addtogroup GAP_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @enum e_ble_gap_evt_t
 * @brief  GAP Event Identifier
 **********************************************************************************************************************/
typedef enum
{
    /**
     *  @brief  Invalid GAP Event.
     *
     * ## Event Code: 0x1001
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_INVALID = 0x1001,

    /* Range for Generic events - 0x01 to 0x0F */

    /**
     *  @brief  Host Stack has been initialized.
     *  @details
     *  When initializing host stack by R_BLE_GAP_Init() has been completed,
     *  BLE_GAP_EVENT_STACK_ON event is notified.
     *
     * ## Event Code: 0x1002
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_STACK_ON,

    /**
     *  @brief  Host Stack has been terminated.
     *  @details
     *  When terminating host stack by R_BLE_GAP_Terminate() has been completed,
     *  BLE_GAP_EVENT_STACK_OFF event is notified.
     *
     * ## Event Code: 0x1003
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_STATE(0x0008)</td>
     *                  <td>When function was called, host stack has not yet been initialized.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_STACK_OFF,

    /**
     *  @brief  Version information of local device.
     *  @details
     *  When version information of local device has been retrieved by R_BLE_GAP_GetVerInfo(),
     *  BLE_GAP_EVENT_LOC_VER_INFO event is notified.
     *
     * ## Event Code: 0x1004
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_loc_dev_info_evt_t
     */
    BLE_GAP_EVENT_LOC_VER_INFO,

    /**
     *  @brief  Hardware Error.
     *  @details
     *  When hardware error has been received from Controller, BLE_GAP_EVENT_HW_ERR event is notified.
     *
     * ## Event Code: 0x1005
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_hw_err_evt_t
     */
    BLE_GAP_EVENT_HW_ERR,

    /**
     *  @brief  Command Status Error.
     *  @details
     *  When the error of HCI Command has occurred after a R_BLE GAP API call, BLE_GAP_EVENT_CMD_ERR event is notified.
     *
     * ## Event Code: 0x1101
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_cmd_err_evt_t
     */
    BLE_GAP_EVENT_CMD_ERR = 0x1101,

    /**
     *  @brief  Advertising Report.
     *  @details
     *  When advertising PDUs has been received after scanning was started by R_BLE_GAP_StartScan().
     *
     * ## Event Code: 0x1102
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_rept_evt_t
     */
    BLE_GAP_EVENT_ADV_REPT_IND,

    /**
     *  @brief  Advertising parameters have been set.
     *  @details
     *  Advertising parameters have been configured by R_BLE_GAP_SetAdvParam().
     *
     * ## Event Code: 0x1103
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                      The advertising type that doesn't support advertising data/scan response data was
     *                      specified to the advertising set which has already set
     *                      advertising data/scan response data.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                      The reason for this error is as follows.<BR/>
     *                      - Advertising parameters were configured to the advertising set in advertising.<BR/>
     *                      - The sec_adv_phy field in adv_paran was not specified
     *                        when Periodic Advertising was started.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_set_evt_t
     */
    BLE_GAP_EVENT_ADV_PARAM_SET_COMP,

    /**
     *  @brief  Advertising data has been set.
     *  @details
     *  This event notifies that Advertising Data/Scan Response Data/Periodic Advertising Data has been
     *  set to the advertising set by R_BLE_GAP_SetAdvSresData().
     *
     * ## Event Code: 0x1104
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                      The reason for this error is as follows.<BR/>
     *                      - The advertising set that doesn't support advertising data/scan response data
     *                        was set to the data. <BR/>
     *                      - The advertising set that supports legacy advertising was set to
     *                        advertising data/scan response data larger than 31 bytes. <BR/>
     *                      - The advertising set that has advertising data/scan response data greater
     *                        than or equal to 252 bytes was set the data in advertising. <BR/>
     *                      - The advertising set that has periodic advertising data greater than or equal to
     *                        253 bytes was set the data in advertising.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_MEM_ALLOC_FAILED(0x000C)</td>
     *                  <td>
     *                      Length exceeded the length that the advertising set could be set.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_SetAdvSresData() has not been created.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_data_evt_t
     */
    BLE_GAP_EVENT_ADV_DATA_UPD_COMP,

    /**
     *  @brief   Advertising has started.
     *  @details
     *  When advertising has been started by R_BLE_GAP_StartAdv(), this event is notified to the application layer.
     *
     * ## Event Code: 0x1105
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                      The reason for this error is as follows.<BR/>
     *                      - The advertising data length set to the advertising set
     *                        for connectable extended advertising was invalid.<BR/>
     *                      - If o_addr_type field in adv_param used in R_BLE_GAP_SetAdvParam() is 0x03,
     *                        the address which is set in o_addr field of adv_param
     *                        has not been registered in Resolving List.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>Setting of advertising data/scan response data has not been completed.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_StartAdv() has not been created.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_LIMIT_EXCEEDED(0x0010)</td>
     *                  <td>When the maximum connections are established, a new connectable advertising tried starting.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_set_evt_t
     */
    BLE_GAP_EVENT_ADV_ON,

    /**
     *  @brief   Advertising has stopped.
     *  @details
     *  This event notifies the application layer that advertising has stopped.
     *
     * ## Event Code: 0x1106
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_StopAdv() has not been created.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_off_evt_t
     */
    BLE_GAP_EVENT_ADV_OFF,

    /**
     *  @brief   Periodic advertising parameters have been set.
     *  @details
     *  This event notifies the application layer that Periodic Advertising Parameters
     *  has been configured by R_BLE_GAP_SetPerdAdvParam().
     *
     * ## Event Code: 0x1107
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                      The advertising set was the setting for anonymous advertising.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                      The advertising set was configured to the parameters in periodic advertising.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_SetPerdAdvParam() has not been created.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_set_evt_t
     */
    BLE_GAP_EVENT_PERD_ADV_PARAM_SET_COMP,

    /**
     *  @brief    Periodic advertising has started.
     *  @details
     *  When Periodic Advertising has been started by R_BLE_GAP_StartPerdAdv(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x1108
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                      The periodic advertising data set in the advertising set has not been completed.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_StartPerdAdv() has not been created.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_set_evt_t
     */
    BLE_GAP_EVENT_PERD_ADV_ON,

    /**
     *  @brief    Periodic advertising has stopped.
     *  @details
     *  When Periodic Advertising has terminated by R_BLE_GAP_StopPerdAdv(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x1109
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_StopPerdAdv() has not been created.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_adv_set_evt_t
     */
    BLE_GAP_EVENT_PERD_ADV_OFF,

    /**
     *  @brief    Advertising set has been deleted.
     *  @details
     *  When the advertising set has been removed by R_BLE_GAP_RemoveAdvSet(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x110A
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       When the advertising set was in advertising, R_BLE_GAP_RemoveAdvSet() was called.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_RemoveAdvSet() has not been created.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_rem_adv_set_evt_t
     */
    BLE_GAP_EVENT_ADV_SET_REMOVE_COMP,

    /**
     *  @brief    Scanning has started.
     *  @details
     *  When scanning has started by R_BLE_GAP_StartScan(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x110B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                      The reason for this error is as follows:<BR/>
     *                      - Scan interval or scan window was invalid.
     *                      - When filter_dup field in scan_enable was BLE_GAP_SCAN_FILT_DUPLIC_ENABLE_FOR_PERIOD(0x02),
     *                        period field in scan_enable was 0.
     *                      - duration field in scan_enable was larger than period in scan_enable.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       In scanning, R_BLE_GAP_StartScan() was called.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_SCAN_ON,

    /**
     *  @brief    Scanning has stopped.
     *  @details
     *  When scanning has been stopped by R_BLE_GAP_StopScan(), this event is notified to the application layer.
     *
     * ## Event Code: 0x110C
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_SCAN_OFF,

    /**
     *  @brief    Scanning has stopped, because duration specified by API expired.
     *  @details
     *  When the scan duration specified by R_BLE_GAP_StartScan() has expired,
     *  this event notifies scanning has stopped.
     *
     * ## Event Code: 0x110D
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_SCAN_TO,

    /**
     *  @brief    Connection Request has been sent to Controller.
     *  @details
     *  This event notifies a request for a connection has been sent to Controller.
     *
     * ## Event Code: 0x110E
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                      The reason for this error is as follows:<BR/>
     *                      - Scan interval or scan windows specified by R_BLE_GAP_CreateConn() is invalid.
     *                      - Although the own_addr_type field in p_param was set to 0x03,
     *                        random address had not been registered in Resolving List.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       R_BLE_GAP_CreateConn() was called while creating a link
     *                       by previous R_BLE_GAP_CreateConn() call .
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_LIMIT_EXCEEDED(0x0010)</td>
     *                  <td>
     *                       When the maximum connections are established, R_BLE_GAP_CreateConn() was called.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_CREATE_CONN_COMP,

    /**
     *  @brief    Link has been established.
     *  @details
     *  This event notifies a link has been established.
     *
     * ## Event Code: 0x110F
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                       The request for a connection has been cancelled by R_BLE_GAP_CancelCreateConn().
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_evt_t
     */
    BLE_GAP_EVENT_CONN_IND,

    /**
     *  @brief    Link has been disconnected.
     *  @details
     *  This event notifies a link has been disconnected.
     *
     * ## Event Code: 0x1110
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_disconn_evt_t
     */
    BLE_GAP_EVENT_DISCONN_IND,

    /**
     *  @brief    Connection Cancel Request has been sent to Controller.
     *  @details
     *  This event notifies the request for a connection has been cancelled by R_BLE_GAP_CancelCreateConn().
     *
     * ## Event Code: 0x1111
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       When a request for a connection has not been sent to Controller,
     *                       R_BLE_GAP_CancelCreateConn() was called.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_CONN_CANCEL_COMP,

    /**
     *  @brief    The White List has been configured.
     *  @details
     *  When White List has been configured, this event is notified to the application layer.
     *
     * ## Event Code: 0x1112
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_STATE(0x0008)</td>
     *                  <td>
     *                       The add or delete operation was called, before the previous clear operation has been completed.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       While doing advertising or scanning or creating a link with the White List,
     *                       R_BLE_GAP_ConfWhiteList() was called.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_MEM_ALLOC_FAILED(0x000C)</td>
     *                  <td>
     *                       White List has already registered the maximum number of devices.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_white_list_conf_evt_t
     */
    BLE_GAP_EVENT_WHITE_LIST_CONF_COMP,

    /**
     *  @brief     Random address has been set to Controller.
     *  @details
     *  This event notifies Controller has been set the random address by R_BLE_GAP_SetRandAddr().
     *
     * ## Event Code: 0x1113
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       When local device was in legacy advertising, R_BLE_GAP_SetRandAddr() was called.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_RAND_ADDR_SET_COMP,

    /**
     *  @brief     Channel Map has been retrieved.
     *  @details
     *  This event notifies Channel Map has been retrieved by R_BLE_GAP_ReadChMap().
     *
     * ## Event Code: 0x1114
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                       The remote device specified by R_BLE_GAP_ReadChMap() was not found.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_rd_ch_map_evt_t
     */
    BLE_GAP_EVENT_CH_MAP_RD_COMP,

    /**
     *  @brief     Channel Map has set.
     *  @details
     *  This event notifies Channel Map has been configured by R_BLE_GAP_SetChMap().
     *
     * ## Event Code: 0x1115
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                       The channel map specified by R_BLE_GAP_SetChMap() was all-zero.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_CH_MAP_SET_COMP,

    /**
     *  @brief     RSSl has been retrieved.
     *  @details
     *  This event notifies RSSI has been retrieved by R_BLE_GAP_ReadRssi().
     *
     * ## Event Code: 0x1116
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                       The remote device specified by R_BLE_GAP_ReadRssi() was not found.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_rd_rssi_evt_t
     */
    BLE_GAP_EVENT_RSSI_RD_COMP,

    /**
     *  @brief     Information about the remote device has been retrieved.
     *  @details
     *  This event notifies information about the remote device has been retrieved by R_BLE_GAP_GetRemDevInfo().
     *
     * ## Event Code: 0x1117
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_dev_info_evt_t
     */
    BLE_GAP_EVENT_GET_REM_DEV_INFO,

    /**
     *  @brief     Connection parameters has been configured.
     *  @details
     *  This event notifies the connection parameters has been updated.
     *
     * ## Event Code: 0x1118
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_DATA(0x0002)</td>
     *                  <td>
     *                       Local device rejected the request for updating connection parameters.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                       The remote device rejected the connection parameters suggested from local device.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_UNSUPPORTED(0x0007)</td>
     *                  <td>
     *                       The remote device doesn't support connection parameters update feature.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_upd_evt_t
     */
    BLE_GAP_EVENT_CONN_PARAM_UPD_COMP,

    /**
     *  @brief     Local device has received the request for configuration of connection parameters.
     *  @details
     *  This event notifies the request for connection parameters update has been received.
     *
     * ## Event Code: 0x1119
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_upd_req_evt_t
     */
    BLE_GAP_EVENT_CONN_PARAM_UPD_REQ,

    /**
     *  @brief     Authenticated Payload Timeout.
     *  @details
     *  This event notifies Authenticated Payload Timeout has occurred.
     *
     * ## Event Code: 0x111A
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_hdl_evt_t
     */
    BLE_GAP_EVENT_AUTH_PL_TO_EXPIRED,

    /**
     *  @brief     The request for update transmission packet size and transmission time have been sent to Controller.
     *  @details
     *  This event notifies a request for updating packet data length and transmission timer has been sent to Controller.
     *
     * ## Event Code: 0x111B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                       The tx_octets or tx_time parameter specified by R_BLE_GAP_SetDataLen() is invalid.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_UNSUPPORTED(0x0007)</td>
     *                  <td>
     *                       The remote device does not support updating packet data length and transmission time.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                        When R_BLE_GAP_SetDataLen() was called, the connection was not established.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_hdl_evt_t
     */
    BLE_GAP_EVENT_SET_DATA_LEN_COMP,

    /**
     *  @brief     Transmission packet size and transmission time have been changed.
     *  @details
     *  This event notifies packet data length and transmission time have been updated.
     *
     * ## Event Code: 0x111C
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_data_len_chg_evt_t
     */
    BLE_GAP_EVENT_DATA_LEN_CHG,

    /**
     *  @brief     The Resolving List has been configured.
     *  @details
     *  When Resolving List has been configured by R_BLE_GAP_ConfRslvList(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x111D
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_STATE(0x0008)</td>
     *                  <td>
     *                       The add or delete operation was called,
     *                       before the previous clear operation has been completed.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       While doing advertising or scanning or creating a link with resolvable private address,
     *                       R_BLE_GAP_ConfRslvList() was called.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_MEM_ALLOC_FAILED(0x000C)</td>
     *                  <td>
     *                       Resolving List has already registered the maximum number of devices.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                       The specified Identity Address was not found in Resolving List.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_rslv_list_conf_evt_t
     */
    BLE_GAP_EVENT_RSLV_LIST_CONF_COMP,

    /**
     *  @brief     Resolvable private address function has been enabled or disabled.
     *  @details
     *  When Resolvable Private Address function in Controller has been enabled by R_BLE_GAP_EnableRpa(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x111E
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                      While advertising, scanning, or establishing a link with resolvable private address,
     *                      R_BLE_GAP_EnableRpa() was called.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_RPA_EN_COMP,

    /**
     *  @brief      The update time of resolvable private address has been changed.
     *  @details
     *  When Resolvable Private Address Timeout in Controller has been updated by R_BLE_GAP_SetRpaTo(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x111F
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                      The rpa_timeout parameter specified by R_BLE_GAP_SetRpaTo() is out of range.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_SET_RPA_TO_COMP,

    /**
     *  @brief      The resolvable private address of local device has been retrieved.
     *  @details
     *  When the resolvable private address of local device has been retrieved by R_BLE_GAP_ReadRpa(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x1120
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The identity address specified by R_BLE_GAP_ReadRpa() was not registered in Resolving List.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_rd_rpa_evt_t
     */
    BLE_GAP_EVENT_RD_RPA_COMP,

    /**
     *  @brief       PHY for connection has been changed.
     *  @details
     *  This event notifies the application layer that PHY for a connection has been updated.
     *
     * ## Event Code: 0x1121
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_phy_upd_evt_t
     */
    BLE_GAP_EVENT_PHY_UPD,

    /**
     *  @brief      The request for updating PHY for connection has been sent to Controller.
     *  @details
     *  When Controller has received a request for updating PHY for a connection by R_BLE_GAP_SetPhy(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x1122
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The remote device specified by R_BLE_GAP_SetPhy() was not found.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_hdl_evt_t
     */
    BLE_GAP_EVENT_PHY_SET_COMP,

    /**
     *  @brief      The request for setting default PHY has been sent to Controller.
     *  @details
     *  When the PHY preferences which a remote device may change has been configured by R_BLE_GAP_SetDefPhy(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x1123
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_DEF_PHY_SET_COMP,

    /**
     *  @brief      PHY configuration has been retrieved.
     *  @details
     *  When the PHY settings has been retrieved by R_BLE_GAP_ReadPhy(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x1124
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                      The link specified by R_BLE_GAP_ReadPhy() was not found.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_phy_rd_evt_t
     */
    BLE_GAP_EVENT_PHY_RD_COMP,

    /**
     *  @brief      Scan Request has been received.
     *  @details
     *  This event notifies the application layer that a Scan Request packet has been received from a Scanner.
     *
     * ## Event Code: 0x1125
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_scan_req_recv_evt_t
     */
    BLE_GAP_EVENT_SCAN_REQ_RECV,

    /**
     *  @brief      The request for establishing a periodic sync has been sent to Controller.
     *  @details
     *  This event notifies the application layer that Controller has received a request
     *  for a Periodic Sync establishment.
     *
     * ## Event Code: 0x1126
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       When R_BLE_GAP_CreateSync() was called,
     *                       this event for previous the API call has not been received.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_ALREADY_IN_PROGRESS(0x000A)</td>
     *                  <td>
     *                      The advertising set specified by R_BLE_GAP_CreateSync() has already established
     *                      a periodic sync.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_CREATE_SYNC_COMP,

    /**
     *  @brief      The periodic advertising sync has been established.
     *  @details
     *  This event notifies the application layer that a Periodic sync has been established.
     *
     * ## Event Code: 0x1127
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_NOT_YET_READY(0x0012)</td>
     *                  <td>
     *                      The request for a Periodic Sync establishment was cancelled by R_BLE_GAP_CancelCreateSync().
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_sync_est_evt_t
     */
    BLE_GAP_EVENT_SYNC_EST,

    /**
     *  @brief       The periodic advertising sync has been terminated.
     *  @details
     *  This event notifies the application layer that the Periodic Sync has been terminated
     *  by R_BLE_GAP_TerminateSync().
     *
     * ## Event Code: 0x1128
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       While establishing a Periodic Sync by R_BLE_GAP_CreateSync(),
     *                       R_BLE_GAP_TerminateSync() was called.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                       The sync handle specified by R_BLE_GAP_TerminateSync() was not found.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_sync_hdl_evt_t
     */
    BLE_GAP_EVENT_SYNC_TERM,

    /**
     *  @brief       The periodic advertising sync has been lost.
     *  @details
     *  This event notifies the application layer that the Periodic Sync has been lost.
     *
     * ## Event Code: 0x1129
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_sync_hdl_evt_t
     */
    BLE_GAP_EVENT_SYNC_LOST,

    /**
     *  @brief       The request for cancel of establishing a periodic advertising sync has been sent to Controller.
     *  @details
     *  This event notifies the request for a Periodic Sync establishment has been cancelled
     *  by R_BLE_GAP_CancelCreateSync().
     *
     * ## Event Code: 0x112A
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                       When R_BLE_GAP_CancelCreateSync() was called,
     *                       a request for a Periodic Sync establishment by R_BLE_GAP_CreateSync()
     *                       has not been sent to Controller.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_SYNC_CREATE_CANCEL_COMP,

    /**
     *  @brief       The Periodic Advertiser list has been configured.
     *  @details
     *  When Periodic Advertiser List has been configured by R_BLE_GAP_ConfPerdAdvList(),
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x112B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>
     *                        The advertiser has already been registered in Periodic Advertiser List.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_STATE(0x0008)</td>
     *                  <td>
     *                       The add or delete operation was called, before the previous clear operation has been completed.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                         When establishing a periodic sync by R_BLE_GAP_CreateSync(),
     *                         R_BLE_GAP_ConfPerdAdvList() was called.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_MEM_ALLOC_FAILED(0x000C)</td>
     *                  <td>
     *                         Periodic Advertiser List has already registered the maximum number of devices.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                         The device specified by R_BLE_GAP_ConfPerdAdvList() was not found.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_perd_list_conf_evt_t
     */
    BLE_GAP_EVENT_PERD_LIST_CONF_COMP,

    /**
     *  @brief       Privacy Mode has been configured.
     *  @details
     *  This event notifies the application layer that the Privacy Mode has been configured by R_BLE_GAP_SetPrivMode().
     *
     * ## Event Code: 0x112B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>Address type or privacy mode is out of range.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>
     *                         While advertising, scanning, or establishing a link with resolvable private address,
     *                         R_BLE_GAP_SetPrivMode() was called.
     *                  </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>
     *                         The address specified by R_BLE_GAP_SetPrivMode() has not been registered
     *                         in Resolving List.
     *                  </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_GAP_EVENT_PRIV_MODE_SET_COMP,

    /**
     *  @brief       The pairing request from a remote device has been received.
     *  @details
     *  This event notifies the application layer that a pairing request from a remote device has been received.
     *
     * ## Event Code: 0x1401
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_pairing_info_evt_t
     */
    BLE_GAP_EVENT_PAIRING_REQ = 0x1401,

    /**
     *  @brief       The request for input passkey has been received.
     *  @details
     *  This event notifies that a request for Passkey input in pairing has been received.
     *
     * ## Event Code: 0x1402
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_hdl_evt_t
     */
    BLE_GAP_EVENT_PASSKEY_ENTRY_REQ,

    /**
     *  @brief       The request for displaying a passkey has been received.
     *  @details
     *  This event notifies that a request for Passkey display in pairing has been received.
     *
     * ## Event Code: 0x1403
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_passkey_display_evt_t
     */
    BLE_GAP_EVENT_PASSKEY_DISPLAY_REQ,

    /**
     *  @brief     The request for confirmation with Numeric Comparison has received.
     *  @details
     *  This event notifies that a request for Numeric Comparison in pairing has been received.
     *
     * ## Event Code: 0x1404
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_num_comp_evt_t
     */
    BLE_GAP_EVENT_NUM_COMP_REQ,

    /**
     *  @brief     Key Notification from a remote device has been received.
     *  @details
     *  This event notifies the application layer that the remote device has input a key in Passkey Entry.
     *
     * ## Event Code: 0x1405
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_key_press_ntf_evt_t
     */
    BLE_GAP_EVENT_KEY_PRESS_NTF,

    /**
     *  @brief     Pairing has been completed.
     *  @details
     *  This event notifies the application layer that the pairing has completed.
     *
     * ## Event Code: 0x1406
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_PASSKEY_ENTRY_FAIL(0x2001)</td>
     *                  <td>PassKey Entry is failed.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_OOB_DATA_NOT_AVAILABLE(0x2002)</td>
     *                  <td>OOB Data is not available.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_AUTH_REQ_NOT_MET(0x2003)</td>
     *                  <td>The requested pairing can not be performed because of IO Capability. </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_CONFIRM_VAL_NOT_MATCH(0x2004)</td>
     *                  <td>Confirmation value does not match.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_PAIRING_NOT_SPRT(0x2005)</td>
     *                  <td>Pairing is not supported.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_INSUFFICIENT_ENC_KEY_SIZE(0x2006)</td>
     *                  <td>Encryption Key Size is insufficient.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_CMD_NOT_SPRT(0x2007)</td>
     *                  <td>The pairing command received is not supported.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_UNSPECIFIED_REASON(0x2008)</td>
     *                  <td>Pairing failed with an unspecified reason.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_REPEATED_ATTEMPTS(0x2009)</td>
     *                  <td>The number of repetition exceeded the upper limit.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_INVALID_PARAM(0x200A)</td>
     *                  <td>Invalid parameter is set.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_DHKEY_CHECK_FAIL(0x200B)</td>
     *                  <td>DHKey Check error.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_NUM_COMP_FAIL(0x200C)</td>
     *                  <td>Numeric Comparison failure.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_DISCONNECTED(0x200F)</td>
     *                  <td>Disconnection in pairing.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_TO(0x2011)</td>
     *                  <td> Failure due to timeout.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_SMP_LE_LOC_KEY_MISSING(0x2014)</td>
     *                  <td>Pairing/Encryption failure because local device lost the LTK.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_pairing_info_evt_t
     */
    BLE_GAP_EVENT_PAIRING_COMP,

    /**
     *  @brief     Key Notification from a remote device has been received.
     *  @details
     *  This event notifies the application layer that the encryption status of a link has been changed.
     *
     * ## Event Code: 0x1407
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_enc_chg_evt_t
     */
    BLE_GAP_EVENT_ENC_CHG,

    /**
     *  @brief     Keys has been received from a remote device.
     *  @details
     *  This event notifies the application layer that the remote device has distributed the keys.
     *
     * ## Event Code: 0x1408
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_peer_key_info_evt_t
     */
    BLE_GAP_EVENT_PEER_KEY_INFO,

    /**
     *  @brief     The request for key distribution has been received.
     *  @details
     *  When local device has been received a request for key distribution to remote device,
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x1409
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_conn_hdl_evt_t
     */
    BLE_GAP_EVENT_EX_KEY_REQ,

    /**
     *  @brief     LTK has been request from a remote device.
     *  @details
     *  When local device has been received a LTK request from a remote device,
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x140A
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_ltk_req_evt_t
     */
    BLE_GAP_EVENT_LTK_REQ,

    /**
     *  @brief     LTK reply has been sent to Controller.
     *  @details
     *  When local device has replied to the LTK request from the remote device,
     *  this event is notified to the application layer.
     *
     * ## Event Code: 0x140B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_ltk_rsp_evt_t
     */
    BLE_GAP_EVENT_LTK_RSP_COMP,

    /**
     *  @brief     The authentication data to be used in Secure Connections OOB has been created.
     *  @details
     *  This event notifies OOB data for Secure Connections has been generated by R_BLE_GAP_CreateScOobData().
     *
     * ## Event Code: 0x140C
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_gap_sc_oob_data_evt_t
     */
    BLE_GAP_EVENT_SC_OOB_CREATE_COMP,
} e_ble_gap_evt_t;

/*@}*/

/* ========================================== GATT Server Type Definitions ========================================== */

/** @addtogroup GATT_SERVER_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup GATT_SERVER_API
 * @ingroup GATT_CLIENT_API
 *  @struct st_ble_gatt_value_t
 *  @brief  Attribute Value.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Length of the attribute value.
     */
    uint16_t value_len;

    /**
     *  @brief     Attribute Value.
     */
    uint8_t * p_value;
} st_ble_gatt_value_t;

/******************************************************************************************************************//**
 * @ingroup GATT_SERVER_API
 * @ingroup GATT_CLIENT_API
 *  @struct st_ble_gatt_hdl_value_pair_t
 *  @brief  Attribute handle and attribute Value.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Attribute Handle
     */
    uint16_t attr_hdl;

    /**
     *  @brief     Attribute Value
     */
    st_ble_gatt_value_t value;
} st_ble_gatt_hdl_value_pair_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatt_queue_att_val_t
 *  @brief  Queued writes Attribute Value.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Attribute Value for Queued Write .
     */
    uint8_t * p_value;

    /**
     *  @brief     Length of the attribute value.
     */
    uint16_t value_len;

    /**
     *  @brief     padding.
     */
    uint16_t padding;
} st_ble_gatt_queue_att_val_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatt_queue_pair_t
 *  @brief  Queued writes Attribute Value.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     Attribute Value for Queued Write
     */
    st_ble_gatt_queue_att_val_t queue_value;

    /**
     *  @brief     Attribute Handle
     */
    uint16_t attr_hdl;
} st_ble_gatt_queue_pair_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatt_queue_elm_t
 *  @brief  Prepare Write Queue element for long chracteristic.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Part of Long Characteristic Value and Characteristic Value Handle.
     */
    st_ble_gatt_queue_pair_t queue_value_pair;

    /**
     *  @brief    Offset that indicates the location to be written.
     */
    uint16_t offset;
} st_ble_gatt_queue_elm_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatt_pre_queue_t
 *  @brief  Prepare Write Queue for long chracteristic.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Buffer start address for Write Long Characteristic Request.
     */
    uint8_t * p_buf_start;

    /**
     *  @brief    Prepare Write Queue for Long Characteristic Value.
     */
    st_ble_gatt_queue_elm_t * p_queue;

    /**
     *  @brief    Buffer length.
     */
    uint16_t buffer_len;

    /**
     *  @brief    Connection Handle.
     */
    uint16_t conn_hdl;

    /**
     *  @brief    Current buffer offset.
     */
    uint16_t buf_offset;

    /**
     *  @brief    Number of elements in the prepare write queue.
     */
    uint8_t queue_size;

    /**
     *  @brief    Index of Prepare Write Queue.
     */
    uint8_t queue_idx;
} st_ble_gatt_pre_queue_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_params_t
 *  @brief  Attribute value to be set to or retrieved from the GATT Database and the access type from the GATT Client.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute value to be set to or retrieved from the GATT Database.
     *            Note that the address of the value field in the value field is invalid in case of read access.
     */
    st_ble_gatt_value_t value;

    /**
     *  @brief    Attribute handle identifying the attribute to be set or retrieved.
     */
    uint16_t attr_hdl;

    /**
     *  @brief    Type of the access to GATT Database from the GATT Client.
     *  @sa       access_type_to_gatt_database
     */
    uint8_t db_op;
} st_ble_gatts_db_params_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_conn_hdl_t
 *  @brief  Information about the service or the characteristic that the attribute belongs to.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Connection handle identifying the GATT Client that accesses to the GATT DataBase.
     */
    uint16_t conn_hdl;

    /**
     *  @brief    ID of the service that the attribute belongs to.
     */
    uint8_t service_id;

    /**
     *  @brief    ID of the Characteristic that the attribute belongs to.
     */
    uint8_t char_id;
} st_ble_gatts_db_conn_hdl_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_access_evt_t
 *  @brief  This structure notifies that the GATT Database has been accessed from a GATT Client.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Information about the service or the characteristic that the attribute belongs to.
     */
    st_ble_gatts_db_conn_hdl_t * p_handle;

    /**
     *  @brief    Attribute value to be set to or retrieved from the GATT Database
     *            and the access type from the GATT Client.
     */
    st_ble_gatts_db_params_t * p_params;
} st_ble_gatts_db_access_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_conn_evt_t
 *  @brief  This structure notifies that the link with the GATT Client has been established.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Address of the GATT Client.
     */
    st_ble_dev_addr_t * p_addr;
} st_ble_gatts_conn_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_disconn_evt_t
 *  @brief  This structure notifies that the link with the GATT Client has been disconnected.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Address of the GATT Client.
     */
    st_ble_dev_addr_t * p_addr;
} st_ble_gatts_disconn_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_ex_mtu_req_evt_t
 *  @brief  This structure notifies that a MTU Exchange Request PDU has been received from a GATT Client.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Maximum receive MTU size by GATT Client.
     */
    uint16_t mtu;
} st_ble_gatts_ex_mtu_req_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_cfm_evt_t
 *  @brief  This structure notifies that a Confirmation PDU has been received from a GATT Client.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle identifying the Characteristic sent by the Indication PDU.
     */
    uint16_t attr_hdl;
} st_ble_gatts_cfm_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_read_by_type_rsp_evt_t
 *  @brief  This structure notifies that a Read By Type Response PDU has been sent from GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle identifying the Characteristic read by the Read By Type Request PDU.
     */
    uint16_t attr_hdl;
} st_ble_gatts_read_by_type_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_read_rsp_evt_t
 *  @brief  This structure notifies that a Read Response PDU has been sent from GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle identifying the Characteristic read by the Read Request PDU.
     */
    uint16_t attr_hdl;
} st_ble_gatts_read_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_read_blob_rsp_evt_t
 *  @brief  This structure notifies that a Read Blob Response PDU has been sent from GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle identifying the Characteristic read by the Read Blob Request PDU.
     */
    uint16_t attr_hdl;
} st_ble_gatts_read_blob_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_read_multi_rsp_evt_t
 *  @brief  This structure notifies that a Read Multiple Response PDU has been sent from GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The number of attribute read by the Read Multiple Request PDU.
     */
    uint8_t count;

    /**
     *  @brief    The list of attribute read by the Read Multiple Request PDU.
     */
    uint16_t * p_attr_hdl_list;
} st_ble_gatts_read_multi_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_write_rsp_evt_t
 *  @brief  This structure notifies that a Write Response PDU has been sent from GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle identifying the Characteristic written by the Write Request PDU.
     */
    uint16_t attr_hdl;
} st_ble_gatts_write_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_prepare_write_rsp_evt_t
 *  @brief  This structure notifies that a Prepare Write Response PDU has been sent from GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle identifying the Characteristic written by the Prepare Write Request PDU.
     */
    uint16_t attr_hdl;

    /**
     *  @brief     The length of written bytes by the Prepare Write Request PDU.
     */
    uint16_t length;

    /**
     *  @brief     The offset of the first octet to be written.
     */
    uint16_t offset;
} st_ble_gatts_prepare_write_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_exe_write_rsp_evt_t
 *  @brief  This structure notifies that a Execute Write Response PDU has been sent from GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The flag that indicates whether execution or cancellation.
     *  @details
     *    |  value     |   description     |
     *    |:-----------|:----------------- |
     *    | 0x00       | Cancellation.     |
     *    | 0x01       | Execution.        |
     */
    uint8_t exe_flag;
} st_ble_gatts_exe_write_rsp_evt_t;

/* GATT DB Structure */

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_uuid_cfg_t
 *  @brief  A structure that defines the information on the position where UUIDs are used.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The position of the defined UUID is specified by offset value in uuid_table of st_ble_gatts_db_cfg_t.
     */
    uint16_t offset;

    /**
     *  @brief    The attribute handle that indicates the first position in st_ble_gatts_db_attr_cfg_t
     *            for the defined UUID is specified.
     */
    uint16_t first;

    /**
     *  @brief    The attribute handle that indicates the last position in st_ble_gatts_db_attr_cfg_t
     *            for the defined UUID is specified.
     */
    uint16_t last;
} st_ble_gatts_db_uuid_cfg_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_attr_cfg_t
 *  @brief  A structure that defines the detailed information of the attributes.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The properties of attribute are specified.
     *  @details  Set the following properties by a bitwise OR.
     *    |              macro                        |   description                          |
     *    |:------------------------------------------|:-------------------------------------- |
     *    | BLE_GATT_DB_READ(0x01)                    | Allow clients to read.                 |
     *    | BLE_GATT_DB_WRITE(0x02)                   |  Allow clients to write.               |
     *    | BLE_GATT_DB_WRITE_WITHOUT_RSP(0x04)       |  Allow clients to write.               |
     *    | BLE_GATT_DB_READ_WRITE(0x07)              |  Allow clients to access of all.       |
     */
    uint8_t desc_prop;

    /**
     *  @brief    The auxiliary properties of attribute are specified.
     *  @details  Set the following properties by a bitwise OR.
     *      <table>
     *          <tr>
     *              <th>macro</th>
     *              <th>description</th>
     *          </tr>
     *          <tr>
     *              <td>BLE_GATT_DB_NO_AUXILIARY_PROPERTY(0x00)</td>
     *              <td>
     *                  No auxiliary properties.\n
     *                  It is invalid when used with other properties at the same time.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GATT_DB_FIXED_LENGTH_PROPERTY(0x01)</td>
     *              <td>
     *                  Fixed length attribute value.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GATT_DB_AUTHORIZATION_PROPERTY(0x02)</td>
     *              <td>
     *                  Attributes requiring authorization.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GATT_DB_ATTR_DISABLED(0x10)</td>
     *              <td>
     *                  The attribute is disabled.
     *                  If this value is set, the attribute cannot be found and accessed by a GATT Client.
     *                  It is invalid when used with other properties at the same time.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GATT_DB_128_BIT_UUID_FORMAT(0x20)</td>
     *              <td>
     *                  Attribute with 128 bit UUID.\n
     *                  If this macro is not set, the attribute value is 16-bits UUID.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GATT_DB_PEER_SPECIFIC_VAL_PROPERTY(0x40)</td>
     *              <td>
     *                  Attribute managed by each GATT Client.
     *              </td>
     *          </tr>
     *          <tr>
     *              <td>BLE_GATT_DB_CONST_ATTR_VAL_PROPERTY(0x80)</td>
     *              <td>
     *                  Fixed attribute value.\n
     *                  Writing from Client and setting from Server are prohibited.
     *              </td>
     *          </tr>
     *      </table>
     */
    uint8_t aux_prop;

    /**
     *  @brief    The length of the attribute value is specified.
     */
    uint16_t length;

    /**
     *  @brief    The position of the next attribute with the same UUID
     *            as the defined attribute is specified by an attribute handle.
     */
    uint16_t next;

    /**
     *  @brief    The storage area of attribute value.
     *  @details  UUID of the defined attribute is set by specifying the position of the UUID registered
     *            in uuid_table of st_ble_gatts_db_cfg_t with the array offset value.
     */
    uint16_t uuid_offset;

    /**
     *  @brief    Storage area of attribute value.
     *  @details  The address in the array registered in No.1-No.4 is specified to set the attribute value storage area of the defined attribute.
     */
    uint8_t * p_data_offset;
} st_ble_gatts_db_attr_cfg_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_attr_list_t
 *  @brief  The number of attributes are stored.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The number of the services or the characteristics.
     */
    uint8_t count;
} st_ble_gatts_db_attr_list_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_char_cfg_t
 *  @brief  A structure that defines the detailed information of the characteristics.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The total number of attributes in the defined characteristic is specified.
     */
    st_ble_gatts_db_attr_list_t list;

    /**
     *  @brief    The first attribute handle of the characteristic is specified.
     */
    uint16_t start_hdl;

    /**
     *  @brief    The index of service to which the characteristic belongs is specified.
     */
    uint8_t service_id;
} st_ble_gatts_db_char_cfg_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_serv_cfg_t
 *  @brief  A structure that defines the detailed information of the characteristics.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief     The total number of service declarations in the defined service is specified.
     */
    st_ble_gatts_db_attr_list_t list;

    /**
     *  @brief    The properties of the defined service are specified.
     *  @details  Set the security level, the security mode and the key size with a bitwise OR.
     *            The bit0-bit3 are specified as the security level.
     *            Select one of the following.
     *              <table>
     *                  <tr>
     *                      <th>macro</th>
     *                      <th>description</th>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_SECURITY_UNAUTH(0x00000001)</td>
     *                      <td>Unauthenticated pairing(Security Mode1 Security Level 2, Security Mode 2 Security Level 1)<BR/>
     *                      Unauthenticated pairing is required to access the service.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_SECURITY_AUTH(0x00000002)</td>
     *                      <td>Authenticated pairing(Security Mode1 Security Level 3, Security Mode 2 Security Level 2)<BR/>
     *                      Authenticated pairing is required to access the service.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_SECURITY_SECONN(0x00000004)</td>
     *                      <td>Authenticated LE secure connections that generates 16bytes LTK(Security Mode1 Security Level 4)<BR/>
     *                      Authenticated LE secure connections pairing that generates 16bytes LTK is required to access the service. If this bit is set, bit24-27 are ignored.
     *                      </td>
     *                  </tr>
     *              </table>
     *              <BR/>
     *              The bit4 is specified as the security mode.<BR/>
     *              <table>
     *                  <tr>
     *                      <th>macro</th>
     *                      <th>description</th>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_SECURITY_ENC(0x00000010)</td>
     *                      <td>Encryption<BR/>
     *                      Encryption by the LTK exchanged in pairing is required to access.</td>
     *                  </tr>
     *              </table>
     *              <BR/>
     *              If the security requirement of the service is not needed,
     *              specify the bit0-bit4 to BLE_GATT_DB_SER_NO_SECURITY_PROPERTY(0x00000000).(Security Mode1 Security Level 1)<BR/>
     *              The bit24-bit27 are specified as the key size required by the defined service.<BR/>
     *              Select one of the following.<BR/>
     *              <table>
     *                  <tr>
     *                      <th>macro</th>
     *                      <th>description</th>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_7(0x01000000)</td>
     *                      <td>7-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_8(0x02000000)</td>
     *                      <td>8-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_9(0x03000000)</td>
     *                      <td>9-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_10(0x04000000)</td>
     *                      <td>10-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_11(0x05000000)</td>
     *                      <td>11-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_12(0x06000000)</td>
     *                      <td>12-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_13(0x07000000)</td>
     *                      <td>13-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_14(0x08000000)</td>
     *                      <td>14-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_15(0x09000000)</td>
     *                      <td>15-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_16(0x0A000000)</td>
     *                      <td>16-byte encryption key.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_GATT_DB_SER_ENC_KEY_SIZE_DONT_CARE(0x00000000)</td>
     *                      <td>7-byte or larger encryption key.</td>
     *                  </tr>
     *              </table>
     *              <BR/>
     *              Other bits are reserved.<BR/>
     */
    uint32_t desc;

    /**
     *  @brief     The start attribute handle of the defined service is specified.
     */
    uint16_t start_hdl;

    /**
     *  @brief      The end attribute handle of the defined service is specified.
     */
    uint16_t end_hdl;

    /**
     *  @brief      The start index of the characteristic that belongs to the defined service is specified.
     */
    uint8_t char_start_idx;

    /**
     *  @brief      The end index of the characteristic that belongs to the defined service is specified.
     */
    uint8_t char_end_idx;
} st_ble_gatts_db_serv_cfg_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_db_cfg_t
 *  @brief  This is the structure of GATT Database that is specified in R_BLE_GATTS_SetDbInst().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief      The array to register the UUID to be used.
     */
    const uint8_t * p_uuid_table;

    /**
     *  @brief      The array to register variable attribute values.
     */
    uint8_t * p_attr_val_table;

    /**
     *  @brief      The array to register fixed attribute values.
     */
    const uint8_t * p_const_attr_val_table;

    /**
     *  @brief      The array to manage the attribute values handled for each GATT client.
     */
    uint8_t * p_rem_spec_val_table;

    /**
     *  @brief      The array to register the default of the attribute value handled by each GATT client.
     */
    const uint8_t * p_const_rem_spec_val_table;

    /**
     *  @brief      The array to register information on the position where UUIDs are used.
     */
    const st_ble_gatts_db_uuid_cfg_t * p_uuid_cfg;

    /**
     *  @brief      The array to register the detailed information of attributes.
     */
    const st_ble_gatts_db_attr_cfg_t * p_attr_cfg;

    /**
     *  @brief       The array to register the detailed information of characteristics.
     */
    const st_ble_gatts_db_char_cfg_t * p_char_cfg;

    /**
     *  @brief        The array to register the detailed information of services.
     */
    const st_ble_gatts_db_serv_cfg_t * p_serv_cfg;

    /**
     *  @brief        The number of services included in the GATT Database.
     */
    uint8_t serv_cnt;

    /**
     *  @brief        The number of characteristics included in the GATT Database.
     */
    uint8_t char_cnt;

    /**
     *  @brief        The number of UUIDs included in the GATT Database.
     */
    uint8_t uuid_type_cnt;

    /**
     *  @brief        The total size of attribute value that needs to be managed for each GATT client.
     */
    uint8_t peer_spec_val_cnt;
} st_ble_gatts_db_cfg_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gatts_evt_data_t
 *  @brief  st_ble_gatts_evt_data_t is the type of the data notified in a GATT Server Event.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief        Connection handle identifying the GATT Client.
     */
    uint16_t conn_hdl;

    /**
     *  @brief        The size of GATT Server Event parameters.
     */
    uint16_t param_len;

    /**
     *  @brief         GATT Server Event parameters. This parameter differs in each GATT Server Event.
     */
    void * p_param;
} st_ble_gatts_evt_data_t;

/******************************************************************************************************************//**
 * @typedef ble_gatts_app_cb_t
 * @brief   ble_gatts_app_cb_t is the GATT Server Event callback function type.
 * @param[in] event_type    The type of GATT Server Event.
 * @param[in] event_result  The result of GATT Server Event
 * @param[in] p_event_data    Data notified by GATT Server Event.
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_gatts_app_cb_t)(uint16_t event_type, ble_status_t event_result,
                                    st_ble_gatts_evt_data_t * p_event_data);

/*@}*/

/* ========================================== GATT Client Type Definitions ========================================== */

/** @addtogroup GATT_CLIENT_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 *  @ingroup GATT_CLIENT_API
 *  @struct st_ble_gatt_hdl_range_t
 *  @brief  Attribute handle range.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief          Start Attribute Handle.
     */
    uint16_t start_hdl;

    /**
     *  @brief         End Attribute Handle.
     */
    uint16_t end_hdl;
} st_ble_gatt_hdl_range_t;

/******************************************************************************************************************//**
 * @ingroup GATT_CLIENT_API
 *  @struct st_ble_gattc_reliable_writes_char_pair_t
 *  @brief  This is used in R_BLE_GATTC_ReliableWrites() to specify the pair of Characteristic Value and
 *          Characteristic Value Handle.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief         Pair of Characteristic Value and Characteristic Value Handle.
     */
    st_ble_gatt_hdl_value_pair_t write_data;

    /**
     *  @brief         Offset that indicates the location to be written.
     *  @details       Normally, set 0 to this parameter.\n
     *                 If this parameter sets to a value other than 0,Adjust the offset parameter and the length of
     *                 the value to be written not to exceed the length of the Characteristic.
     */
    uint16_t offset;
} st_ble_gattc_reliable_writes_char_pair_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_conn_evt_t
 *  @brief  This structure notifies that the link with the GATT Server has been established.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Address of the GATT Server.
     */
    st_ble_dev_addr_t * p_addr;
} st_ble_gattc_conn_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_disconn_evt_t
 *  @brief  This structure notifies that the link with the GATT Server has been disconnected.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Address of the GATT Server.
     */
    st_ble_dev_addr_t * p_addr;
} st_ble_gattc_disconn_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_ex_mtu_rsp_evt_t
 *  @brief  This structure notifies that a MTU Exchange Response PDU has been received from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    MTU size(in bytes) that GATT Server can receive.
     */
    uint16_t mtu;
} st_ble_gattc_ex_mtu_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_serv_16_evt_t
 *  @brief  This structure notifies that a 16-bit UUID Service has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle range of the 16-bit UUID service.
     */
    st_ble_gatt_hdl_range_t range;

    /**
     *  @brief    Service UUID.
     */
    uint16_t uuid_16;
} st_ble_gattc_serv_16_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_serv_128_evt_t
 *  @brief  This structure notifies that a 128-bit UUID Service has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle range of the 128-bit UUID service.
     */
    st_ble_gatt_hdl_range_t range;

    /**
     *  @brief    Service UUID.
     */
    uint8_t uuid_128[BLE_GATT_128_BIT_UUID_SIZE];
} st_ble_gattc_serv_128_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_inc_serv_16_evt_t
 *  @brief  This structure notifies that a 16-bit UUID Included Service has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Service Declaration handle of the 16-bit UUID Included Service.
     */
    uint16_t decl_hdl;

    /**
     *  @brief    The contents of the Included Service.
     */
    st_ble_gattc_serv_16_evt_t service;
} st_ble_gattc_inc_serv_16_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_inc_serv_128_evt_t
 *  @brief  This structure notifies that a 128-bit UUID Included Service has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Service Declaration handle of the 128-bit UUID Included Service.
     */
    uint16_t decl_hdl;

    /**
     *  @brief    The contents of the Included Service.
     */
    st_ble_gattc_serv_128_evt_t service;
} st_ble_gattc_inc_serv_128_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_char_16_evt_t
 *  @brief  This structure notifies that a 16-bit UUID Characteristic has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute handle of Characteristic Declaration.
     */
    uint16_t decl_hdl;

    /**
     *  @brief    Characteristic Properties.
     *  @details  It is a bitwise OR of the following values.\n
     *            Refer to Core Spec [Vol.3] Generic Attribute Profile(GATT) "3.3.1.1 Characteristic Properties"
     *            regarding the details of the Characteristic Properties.
     *            |  value     |   description                        |
     *            |:-----------|:------------------------------------ |
     *            | 0x01       | Broadcast property                   |
     *            | 0x02       | Read property                        |
     *            | 0x04       | Write Without Response property      |
     *            | 0x08       | Write property                       |
     *            | 0x10       | Notify property                      |
     *            | 0x20       | Indicate property                    |
     *            | 0x40       | Authenticated Signed Writes property |
     *            | 0x80       | Extended Properties property         |
     */
    uint8_t cproperty;

    /**
     *  @brief    Value Handle of the Characteristic.
     */
    uint16_t value_hdl;

    /**
     *  @brief    Characteristic UUID.
     */
    uint16_t uuid_16;
} st_ble_gattc_char_16_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_char_128_evt_t
 *  @brief  This structure notifies that a 128-bit UUID Characteristic has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute Handle of Characteristic Declaration.
     */
    uint16_t decl_hdl;

    /**
     *  @brief    Characteristic Properties.
     *  @details  It is a bitwise OR of the following values.\n
     *            Refer to Core Spec [Vol.3] Generic Attribute Profile(GATT) "3.3.1.1 Characteristic Properties"
     *            regarding the details of the Characteristic Properties.
     *            |  value     |   description                        |
     *            |:-----------|:------------------------------------ |
     *            | 0x01       | Broadcast property                   |
     *            | 0x02       | Read property                        |
     *            | 0x04       | Write Without Response property      |
     *            | 0x08       | Write property                       |
     *            | 0x10       | Notify property                      |
     *            | 0x20       | Indicate property                    |
     *            | 0x40       | Authenticated Signed Writes property |
     *            | 0x80       | Extended Properties property         |
     */
    uint8_t cproperty;

    /**
     *  @brief    Value Handle of the Characteristic.
     */
    uint16_t value_hdl;

    /**
     *  @brief    Characteristic UUID.
     */
    uint8_t uuid_128[BLE_GATT_128_BIT_UUID_SIZE];
} st_ble_gattc_char_128_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_char_desc_16_evt_t
 *  @brief  This structure notifies that a 16-bit UUID Characteristic Descriptor has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute Handle of Characteristic Descriptor.
     */
    uint16_t desc_hdl;

    /**
     *  @brief    Characteristic Descriptor UUID.
     */
    uint16_t uuid_16;
} st_ble_gattc_char_desc_16_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_char_desc_128_evt_t
 *  @brief  This structure notifies that a 128-bit UUID Characteristic Descriptor has been discovered.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Attribute Handle of Characteristic Descriptor.
     */
    uint16_t desc_hdl;

    /**
     *  @brief    Characteristic Descriptor UUID.
     */
    uint8_t uuid_128[BLE_GATT_128_BIT_UUID_SIZE];
} st_ble_gattc_char_desc_128_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_err_rsp_evt_t
 *  @brief  This structure notifies that a Error Response PDU has been received from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The op code of the ATT Request that causes the Error Response.
     *            |             op_code                   |
     *            |:--------------------------------------|
     *            |  Exchange MTU Request(0x02)           |
     *            |  Find Information Request(0x04)       |
     *            |  Find By Type Value Request(0x06)     |
     *            |  Read By Type Request(0x08)           |
     *            |  Read Request(0x0A)                   |
     *            |  Read Blob Request(0x0C)              |
     *            |  Read Multiple Request(0x0E)          |
     *            |  Read by Group Type Request(0x10)     |
     *            |  Write Request(0x12)                  |
     *            |  Prepare Write Request(0x16)          |
     *            |  Execute Write Request(0x18)          |
     */
    uint8_t op_code;

    /**
     *  @brief    Attribute handle that is target for the request.
     */
    uint16_t attr_hdl;

    /**
     *  @brief    The error codes notified from the GATT Server.
     *  @details  It is a bitwise OR of GATT Error Group ID : 0x3000 and the following error codes defined in
     *            Core Spec and Core Spec Supplement.
     *              <table>
     *                  <tr>
     *                      <th>Error Code</th>
     *                      <th>description</th>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INVALID_HANDLE(0x3001)</td>
     *                      <td>Invalid attribute handle</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_READ_NOT_PERMITTED(0x3002)</td>
     *                      <td>The attribute cannot be read.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_WRITE_NOT_PERMITTED(0x3003)</td>
     *                      <td>The attribute cannot be written.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INVALID_PDU(0x3004)</td>
     *                      <td>Invalid PDU.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INSUFFICIENT_AUTHENTICATION(0x3005)</td>
     *                      <td>The authentication to access the attribute is insufficient.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_REQUEST_NOT_SUPPORTED(0x3006)</td>
     *                      <td>The request is not supported.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INVALID_OFFSET(0x3007)</td>
     *                      <td>The specified offset is larger than the length of the attribute value.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INSUFFICIENT_AUTHORIZATION(0x3008)</td>
     *                      <td>Authorization is required to access the attribute.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_PREPARE_WRITE_QUEUE_FULL(0x3009)</td>
     *                      <td>The Write Queue in the GATT Server is full.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_ATTRIBUTE_NOT_FOUND(0x300A)</td>
     *                      <td>The specified attribute is not found.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_ATTRIBUTE_NOT_LONG(0x300B)</td>
     *                      <td>The attribute cannot be read by Read Blob Request.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INSUFFICIENT_ENC_KEY_SIZE(0x300C)</td>
     *                      <td>The Encryption Key Size is insufficient.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INVALID_ATTRIBUTE_LEN(0x300D)</td>
     *                      <td>The length of the specified attribute is invalid.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_UNLIKELY_ERROR(0x300E)</td>
     *                      <td>Because an error has occurred,  the process cannot be advanced.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INSUFFICIENT_ENCRYPTION(0x300F)</td>
     *                      <td>Encryption is required to access the attribute.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_UNSUPPORTED_GROUP_TYPE(0x3010)</td>
     *                      <td>The type of the specified attribute is not supported.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_INSUFFICIENT_RESOURCES(0x3011)</td>
     *                      <td>The resource to complete the request is insufficient.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>0x3080 - 0x309F</td>
     *                      <td>
     *                          Application Error.
     *                          The upper layer defines the error codes.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>0x30E0 - 0x30FF</td>
     *                      <td>
     *                          The error code defined in Common Profile and
     *                          Service Error Core Specification Supplement(CSS).<BR/>
     *                          CSS ver.7 defines the error codes from 0x30FC to 0x30FF.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_WRITE_REQ_REJECTED(0x30FC)</td>
     *                      <td>
     *                          The Write Request has not been completed due to the reason other than Permission.
     *                      </td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_CCCD_IMPROPERLY_CFG(0x30FD)</td>
     *                      <td>The CCCD is set to be invalid.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_PROC_ALREADY_IN_PROGRESS(0x30FE)</td>
     *                      <td>The request is now in progress.</td>
     *                  </tr>
     *                  <tr>
     *                      <td>BLE_ERR_GATT_OUT_OF_RANGE(0x30FF)</td>
     *                      <td>The attribute value is out of range.</td>
     *                  </tr>
     *              </table>
     */
    uint16_t rsp_code;
} st_ble_gattc_err_rsp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_ntf_evt_t
 *  @brief  This structure notifies that a Notification PDU has been received from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Characteristic that causes the Notification.
     */
    st_ble_gatt_hdl_value_pair_t data;
} st_ble_gattc_ntf_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_ind_evt_t
 *  @brief  This structure notifies that a Indication PDU has been received from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    Characteristic that causes the Indication.
     */
    st_ble_gatt_hdl_value_pair_t data;
} st_ble_gattc_ind_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_rd_char_evt_t
 *  @brief  This structure notifies that read response to R_BLE_GATTC_ReadChar() or R_BLE_GATTC_ReadCharUsingUuid()
 *          has been received from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief    The contents of the Characteristic that has been read.
     */
    st_ble_gatt_hdl_value_pair_t read_data;
} st_ble_gattc_rd_char_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_wr_char_evt_t
 *  @brief  This structure notifies that write response to R_BLE_GATTC_WriteChar() has been received from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   Value Handle of the Characteristic/Characteristic Descriptor that has been written.
     */
    uint16_t value_hdl;
} st_ble_gattc_wr_char_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_rd_multi_char_evt_t
 *  @brief  This structure notifies that read response to R_BLE_GATTC_ReadMultiChar() has been received
 *          from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   The number of Value Handles of the Characteristics that has been read.
     */
    uint16_t value_hdl_num;

    /**
     *  @brief   The contents of multiple Characteristics that have been read.
     */
    st_ble_gatt_value_t multi_char_val;
} st_ble_gattc_rd_multi_char_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_char_part_wr_evt_t
 *  @brief  This structure notifies that write response to R_BLE_GATTC_WriteLongChar() or R_BLE_GATTC_ReliableWrites()
 *          has been received from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   The data to be written to the Characteristic/Long Characteristic/Long Characteristic Descriptor.
     */
    st_ble_gatt_hdl_value_pair_t write_data;

    /**
     *  @brief   Offset that indicates the location to be written.
     */
    uint16_t offset;
} st_ble_gattc_char_part_wr_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_reliable_writes_comp_evt_t
 *  @brief  This structure notifies that a response to R_BLE_GATTC_ExecWrite() has been received
 *          from a GATT Server.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   This field indicates the command of the Execute Write that has been done.
     *  @details
     *            |  value     |   description       |
     *            |:-----------|:------------------- |
     *            | 0x00       | Cancel the write.   |
     *            | 0x01       | Execute the write.  |
     */
    uint8_t exe_flag;
} st_ble_gattc_reliable_writes_comp_evt_t;

/* RBLE GATT Client Command Parameters */

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_rd_multi_req_param_t
 *  @brief  This is used in R_BLE_GATTC_ReadMultiChar() to specify multiple Characteristics to be read.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   List of Value Handles that point the Characteristics to be read.
     */
    uint16_t * p_hdl_list;

    /**
     *  @brief   The number of Value Handles included in the hdl_list parameter.
     */
    uint16_t list_count;
} st_ble_gattc_rd_multi_req_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_gattc_evt_data_t
 *  @brief  st_ble_gattc_evt_data_t is the type of the data notified in a GATT Client Event.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief   Connection handle identifying the GATT Server.
     */
    uint16_t conn_hdl;

    /**
     *  @brief    The size of GATT Client Event parameters.
     */
    uint16_t param_len;

    /**
     *  @brief   GATT Client Event parameters. This parameter differs in each GATT Client Event.
     */
    void * p_param;
} st_ble_gattc_evt_data_t;

/******************************************************************************************************************//**
 * @typedef ble_gattc_app_cb_t
 * @brief   ble_gattc_app_cb_t is the GATT Client Event callback function type.
 * @param[in] event_type    The type of GATT Client Event.
 * @param[in] event_result  The result of GATT Client Event
 * @param[in] p_event_data  Data notified by GATT Client Event.
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_gattc_app_cb_t)(uint16_t event_type, ble_status_t event_result,
                                    st_ble_gattc_evt_data_t * p_event_data);

/*@}*/

/* ============================================= L2CAP Type Definitions ============================================= */

/** @addtogroup L2CAP_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup L2CAP_API
 * @struct st_ble_l2cap_conn_req_param_t
 * @brief  L2CAP CBFC Channel connection request parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Identifier indicating the protocol/profile that uses L2CAP CBFC Channel on local device.
     */
    uint16_t local_psm;

    /**
     *  @brief Identifier indicating the protocol/profile that uses L2CAP CBFC Channel on remote device.
     */
    uint16_t remote_psm;

    /**
     *  @brief MTU size(byte) receivable on L2CAP CBFC Channel.
     */
    uint16_t mtu;

    /**
     *  @brief MPS size(byte) receivable on L2CAP CBFC Channel.
     */
    uint16_t mps;

    /**
     *  @brief The number of LE-Frame that local device can receive.
     */
    uint16_t credit;
} st_ble_l2cap_conn_req_param_t;

/******************************************************************************************************************//**
 * @struct st_ble_l2cap_conn_rsp_param_t
 * @brief  L2CAP CBFC Channel connection response parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief CID identifying the L2CAP CBFC Channel on local device.
     *         The valid range is 0x40-0x40 + BLE_L2CAP_MAX_CBFC_PSM - 1.
     */
    uint16_t lcid;

    /**
     *  @brief  The response to the connection request. Select one of the following.
     *                  <table>
     *                      <tr>
     *                          <th>macro</th>
     *                          <th>description</th>
     *                      </tr>
     *                      <tr>
     *                          <td><span style="color:#307D7E">BLE_L2CAP_CF_RSP_SUCCESS(0x0000)</span></td>
     *                          <td>Notify the remote device that the connection can be established.</td>
     *                      </tr>
     *                      <tr>
     *                          <td><span style="color:#307D7E">BLE_L2CAP_CF_RSP_RFSD_INSF_AUTH(0x0005)</span></td>
     *                          <td>Notify the remote device that the connection can not be established
     *                              because of insufficient authentication.</td>
     *                      </tr>
     *                      <tr>
     *                          <td><span style="color:#307D7E">BLE_L2CAP_CF_RSP_RFSD_INSF_AUTRZ(0x0006)</span></td>
     *                          <td>Notify the remote device that the connection can not be established
     *                              because of insufficient Authorization.</td>
     *                      </tr>
     *                      <tr>
     *                          <td><span style="color:#307D7E">BLE_L2CAP_CF_RSP_RFSD_INSF_ENC_KEY(0x0007)</span></td>
     *                          <td>Notify the remote device that the connection can not be established
     *                              because of Encryption Key Size.</td>
     *                      </tr>
     *                      <tr>
     *                          <td><span style="color:#307D7E">BLE_L2CAP_CF_RSP_RFSD_INSF_ENC(0x0008)</span></td>
     *                          <td>Notify the remote device that the connection can not be established
     *                              because of Encryption.</td>
     *                      </tr>
     *                      <tr>
     *                          <td><span style="color:#307D7E">BLE_L2CAP_CF_RSP_RFSD_UNAC_PARAM(0x000B)</span></td>
     *                          <td>Notify the remote device that the connection can not be established
     *                              because the parameters is unacceptable to local device.</td>
     *                      </tr>
     *                  </table>
     */
    uint16_t response;

    /**
     *  @brief MTU(byte) of packet that L2CAP CBFC Channel on local device can receive.
     */
    uint16_t mtu;

    /**
     *  @brief MPS(byte) of packet that L2CAP CBFC Channel on local device can receive.
     */
    uint16_t mps;

    /**
     *  @brief The number of LE-Frame that L2CAP CBFC Channel on local device can receive.
     */
    uint16_t credit;
} st_ble_l2cap_conn_rsp_param_t;

/******************************************************************************************************************//**
 * @struct st_ble_l2cap_cf_conn_evt_t
 * @brief  L2CAP CBFC Channel connection parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief CID identifying the L2CAP CBFC Channel.
     */
    uint16_t cid;

    /**
     *  @brief PSM allocated by the cid field.
     */
    uint16_t psm;

    /**
     *  @brief MTU of local/remote device.
     */
    uint16_t mtu;

    /**
     *  @brief MPS of local/remote device.
     */
    uint16_t mps;

    /**
     *  @brief Credit of local/remote device.
     */
    uint16_t credit;
} st_ble_l2cap_cf_conn_evt_t;

/******************************************************************************************************************//**
 * @struct st_ble_l2cap_cf_data_evt_t
 * @brief  Sent/Received Data parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief CID identifying the L2CAP CBFC Channel that has sent or received the data .
     */
    uint16_t cid;

    /**
     *  @brief PSM allocated by the cid field.
     */
    uint16_t psm;

    /**
     *  @brief Data length.
     */
    uint16_t data_len;

    /**
     *  @brief Sent/Received data.
     */
    uint8_t * p_data;
} st_ble_l2cap_cf_data_evt_t;

/******************************************************************************************************************//**
 * @struct st_ble_l2cap_cf_credit_evt_t
 * @brief  Credit parameters of local or remote device.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief CID identifying the L2CAP CBFC Channel.
     */
    uint16_t cid;

    /**
     *  @brief PSM allocated by the cid field.
     */
    uint16_t psm;

    /**
     *  @brief Current credit of local/remote device.
     */
    uint16_t credit;
} st_ble_l2cap_cf_credit_evt_t;

/******************************************************************************************************************//**
 * @struct st_ble_l2cap_cf_disconn_evt_t
 * @brief  Disconnection parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief CID identifying the L2CAP CBFC Channel that has been disconnected.
     */
    uint16_t cid;
} st_ble_l2cap_cf_disconn_evt_t;

/******************************************************************************************************************//**
 * @struct st_ble_l2cap_rej_evt_t
 * @brief  Command Reject parameters.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief  The reason that the remote device has sent Command Reject.
     */
    uint16_t reason;

    /**
     *  @brief  Optional information about the reason that the remote device has sent Command Reject.
     */
    uint16_t data_1;

    /**
     *  @brief  Optional information about the reason that the remote device has sent Command Reject.
     */
    uint16_t data_2;
} st_ble_l2cap_rej_evt_t;

/******************************************************************************************************************//**
 * @struct st_ble_l2cap_cf_evt_data_t
 * @brief st_ble_l2cap_cf_evt_data_t is the type of the data notified in a L2CAP Event.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief  Connection handle identifying the remote device.
     */
    uint16_t conn_hdl;

    /**
     *  @brief  The size of L2CAP Event parameters.
     */
    uint16_t param_len;

    /**
     *  @brief  L2CAP Event parameters. This parameter differs in each L2CAP Event.
     */
    void * p_param;
} st_ble_l2cap_cf_evt_data_t;

/******************************************************************************************************************//**
 * @typedef ble_l2cap_cf_app_cb_t
 * @brief   ble_l2cap_cf_app_cb_t is the L2CAP Event callback function type.
 * @param[in] event_type    The type of L2CAP Event.
 * @param[in] event_result  The result of L2CAP Event
 * @param[in] p_event_data    Data notified by L2CAP Event.
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_l2cap_cf_app_cb_t)(uint16_t event_type, ble_status_t event_result,
                                       st_ble_l2cap_cf_evt_data_t * p_event_data);

/*@}*/

/* ================================================ L2CAP Event Code ================================================ */

/** @addtogroup L2CAP_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup L2CAP_API
 * @enum e_r_ble_l2cap_cf_evt_t
 * @brief  L2CAP Event Identifier
 **********************************************************************************************************************/
typedef enum
{
    /**
     *  @brief After the connection request for L2CAP CBFC Channel has been sent with R_BLE_L2CAP_ReqCfConn(),
     *         when the L2CAP CBFC Channel connection response has been received,
     *         BLE_L2CAP_EVENT_CF_CONN_CNF event occurs.
     *
     * ## Event Code: 0x5001
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_RSP_TIMEOUT(0x0011)</td>
     *                  <td>L2CAP Command timeout.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_PSM_NOT_SUPPORTED(0x4002)</td>
     *                  <td>PSM specified by R_BLE_L2CAP_ReqCfConn() is not supported.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_NO_RESOURCE(0x4004)</td>
     *                  <td>No resource for connection.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_INSUF_AUTHEN(0x4005)</td>
     *                  <td>Insufficient authentication.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_INSUF_AUTHOR(0x4006)</td>
     *                  <td>Insufficient authorization.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_INSUF_ENC_KEY_SIZE(0x4007)</td>
     *                  <td>Insufficient encryption key size.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_REFUSE_INSUF_ENC(0x4008)</td>
     *                  <td>Insufficient encryption.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_REFUSE_INVALID_SCID(0x4009)</td>
     *                  <td> Invalid Source CID. </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_REFUSE_SCID_ALREADY_ALLOC(0x400A)</td>
     *                  <td>Source CID already allocated.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_REFUSE_UNACCEPTABLE_PARAM(0x400B)</td>
     *                  <td>Unacceptable parameters.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_conn_evt_t
     */
    BLE_L2CAP_EVENT_CF_CONN_CNF = 0x5001,

    /**
     *  @brief  When a connection request for L2CPA CBFC Channel has been received from a remote device,
     *          BLE_L2CAP_EVENT_CF_CONN_IND event occurs.
     *
     * ## Event Code: 0x5002
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_NOT_FOUND(0x000D)</td>
     *                  <td>CF connection request has not been received or lcid not found. </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_L2CAP_PSM_NOT_SUPPORTED(0x4002)</td>
     *                  <td>PSM specified by R_BLE_L2CAP_ReqCfConn() is not supported.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_conn_evt_t
     */
    BLE_L2CAP_EVENT_CF_CONN_IND = 0x5002,

    /**
     *  @brief  After local device has sent a disconnection request for L2CAP CBFC Channel by
     *          R_BLE_L2CAP_DisconnectCf(), when the local device has received the response,
     *          BLE_L2CAP_EVENT_CF_DISCONN_CNF event occurs.
     *
     * ## Event Code: 0x5003
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_disconn_evt_t
     */
    BLE_L2CAP_EVENT_CF_DISCONN_CNF = 0x5003,

    /**
     *  @brief  When local device has received a disconnection request for L2CAP CBFC Channel from the remote device,
     *          BLE_L2CAP_EVENT_CF_DISCONN_IND event occurs.\n
     *          Host stack automatically replies the to the disconnection request.
     *
     * ## Event Code: 0x5004
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_disconn_evt_t
     */
    BLE_L2CAP_EVENT_CF_DISCONN_IND = 0x5004,

    /**
     *  @brief  When local device has received data on L2CAP CBFC Channel, BLE_L2CAP_EVENT_CF_RX_DATA_IND event occurs.
     *
     * ## Event Code: 0x5005
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_data_evt_t
     */
    BLE_L2CAP_EVENT_CF_RX_DATA_IND = 0x5005,

    /**
     *  @brief  When the credit of the L2CAP CBFC Channel has reached the Low Water Mark,
     *          BLE_L2CAP_EVENT_CF_LOW_RX_CRD_IND event occurs.
     *
     * ## Event Code: 0x5006
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_credit_evt_t
     */
    BLE_L2CAP_EVENT_CF_LOW_RX_CRD_IND = 0x5006,

    /**
     *  @brief  When local device has received credit from a remote device, BLE_L2CAP_EVENT_CF_TX_CRD_IND event occurs.
     *
     * ## Event Code: 0x5007
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_credit_evt_t
     */
    BLE_L2CAP_EVENT_CF_TX_CRD_IND = 0x5007,

    /**
     *  @brief  When the data transmission has been completed from host stack to Controller,
     *          BLE_L2CAP_EVENT_CF_TX_DATA_CNF event occurs.
     *
     * ## Event Code: 0x5008
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_DISCONNECTED(0x000F)  </td>
     *                  <td>While transmitting data, L2CAP CBFC Channel has been disconnected.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_cf_data_evt_t
     */
    BLE_L2CAP_EVENT_CF_TX_DATA_CNF = 0x5008,

    /**
     *  @brief  When local device has received Command Reject PDU, BLE_L2CAP_EVENT_CMD_REJ event occurs.
     *
     * ## Event Code: 0x5009
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_l2cap_rej_evt_t
     */
    BLE_L2CAP_EVENT_CMD_REJ = 0x5009
} e_r_ble_l2cap_cf_evt_t;

/*@}*/

/* ======================================== Vendor Specific Type Definitions ======================================== */

/** @addtogroup VS_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 *  @ingroup VS_API
 *  @struct st_ble_vs_tx_test_param_t
 *  @brief  This is the extended transmitter test parameters used in R_BLE_VS_StartTxTest().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Channel used in Tx test.
     */
    uint8_t ch;

    /**
     *  @brief Length(in bytes) of the packet used in Tx Test.
     */
    uint8_t test_data_len;

    /**
     *  @brief Packet Payload.
     */
    uint8_t packet_payload;

    /**
     *  @brief Transmitter PHY used in test.
     */
    uint8_t phy;

    /**
     *  @brief Tx Power Level used in DTM Tx Test.
     */
    uint8_t tx_power;

    /**
     *  @brief Option.
     */
    uint8_t option;

    /**
     *  @brief The number of packet to be sent.
     */
    uint16_t num_of_packet;
} st_ble_vs_tx_test_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_rx_test_param_t
 *  @brief  This is the extended receiver test parameters used in R_BLE_VS_StartRxTest().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Channel used in Rx test.
     */
    uint8_t ch;

    /**
     *  @brief Receiver PHY used in the test.
     */
    uint8_t phy;
} st_ble_vs_rx_test_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_set_rf_ctrl_param_t
 *  @brief  This is the RF parameters used in R_BLE_VS_SetRfControl().
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief RF power on/off.
     */
    uint8_t power;

    /**
     *  @brief This field indicates whether the parameters change in RF power on.
     */
    uint8_t option;

    /**
     *  @brief RF rapid clock frequency adjust value(OSC internal CL adjust).
     */
    uint8_t clval;

    /**
     *  @brief RF slow clock configurations.
     */
    uint8_t slow_clock;

    /**
     *  @brief Set tx power in power on.
     */
    uint8_t tx_power;

    /**
     *  @brief Set RF option.
     */
    uint8_t rf_option;
} st_ble_vs_set_rf_ctrl_param_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_test_end_evt_t
 *  @brief  This structure notifies that the extended test has been terminated.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief The number of packet successfully received in the receiver test.
     */
    uint16_t num_of_packet;

    /**
     *  @brief The number of CRC error packets in the receiver test.
     */
    uint16_t num_of_crc_err_packet;

    /**
     *  @brief Average RSSI(dBm) in the receiver test.
     */
    int8_t ave_rssi;

    /**
     *  @brief Maximum RSSI(dBm) in the receiver test.
     */
    int8_t max_rssi;

    /**
     *  @brief Minimum RSSI(dBm) in the receiver test.
     */
    int8_t min_rssi;
} st_ble_vs_test_end_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_set_tx_pwr_comp_evt_t
 *  @brief  This structure notifies that tx power has been set.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Connection handle that identifying the link whose tx power has been set.
     */
    uint16_t conn_hdl;

    /**
     *  @brief Tx power that has been set(dBm).
     */
    int8_t curr_tx_pwr;
} st_ble_vs_set_tx_pwr_comp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_get_tx_pwr_comp_evt_t
 *  @brief  This structure notifies that tx power has been retrieved.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Connection handle that identifying the link whose tx power has been retrieved.
     */
    uint16_t conn_hdl;

    /**
     *  @brief Current tx power(dBm).
     */
    int8_t curr_tx_pwr;

    /**
     *  @brief Maximum tx power(dBm).
     */
    int8_t max_tx_pwr;
} st_ble_vs_get_tx_pwr_comp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_set_rf_ctrl_comp_evt_t
 *  @brief  This structure notifies that RF has been configured.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief The result of RF power control.
     */
    uint8_t ctrl;
} st_ble_vs_set_rf_ctrl_comp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_get_bd_addr_comp_evt_t
 *  @brief  This structure notifies that BD_ADDR has been retrieved.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief The area that public/random address has been retrieved.
     *    |  value                              |   description       |
     *    |:------------------------------------|:------------------- |
     *    | BLE_VS_ADDR_AREA_REG(0x00)          | Register.           |
     *    | BLE_VS_ADDR_AREA_DATA_FLASH(0x01)   | Data Flash.         |
     */
    uint8_t area;

    /**
     *  @brief The address that has been retrieved.
     */
    st_ble_dev_addr_t addr;
} st_ble_vs_get_bd_addr_comp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_get_rand_comp_evt_t
 *  @brief  This structure notifies that random number has been generated.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief Length of random number.
     */
    uint8_t rand_size;

    /**
     *  @brief Random number.
     */
    uint8_t * p_rand;
} st_ble_vs_get_rand_comp_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_tx_flow_chg_evt_t
 *  @brief  This structure notifies that the state transition of TxFlow has been changed.
 **********************************************************************************************************************/
typedef struct
{
    /**
     * @brief The state of the flow control.
     * |        value                 |   description                                                              |
     * |:---------------------------- |:-------------------------------------------------------------------------- |
     * | BLE_VS_TX_FLOW_CTL_ON(0x00)  | The number of buffer has reached the High Water Mark from flow off state.  |
     * | BLE_VS_TX_FLOW_CTL_OFF(0x01) | The number of buffer has reached the Low Water Mark from flow on state.    |
     */
    uint8_t state;

    /**
     *  @brief The number of the current transmission buffers.
     */
    uint32_t buffer_num;
} st_ble_vs_tx_flow_chg_evt_t;

/******************************************************************************************************************//**
 *  @struct st_ble_vs_evt_data_t
 *  @brief  st_ble_vs_evt_data_t is the type of the data notified in a Vendor Specific Event.
 **********************************************************************************************************************/
typedef struct
{
    /**
     *  @brief The size of Vendor Specific Event parameters.
     */
    uint16_t param_len;

    /**
     *  @brief Vendor Specific Event parameters. This parameter differs in each Vendor Specific Event.
     */
    void * p_param;
} st_ble_vs_evt_data_t;

/******************************************************************************************************************//**
 * @typedef ble_vs_app_cb_t
 * @brief   ble_vs_app_cb_t is the Vendor Specific Event callback function type.
 * @param[in] event_type    The type of Vendor Specific Event.
 * @param[in] event_result  The result of API call which generates the Vendor Specific Event.
 * @param[in] p_event_data  Data notified in the Vendor Specific Event.
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_vs_app_cb_t)(uint16_t event_type, ble_status_t event_result, st_ble_vs_evt_data_t * p_event_data);

/*@}*/

/* =========================================== Vendor Specific Event Code =========================================== */

/** @addtogroup VS_API
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup VS_API
 * @enum e_r_ble_vs_evt_t
 * @brief  Vendor Specific Event Identifier
 **********************************************************************************************************************/
typedef enum
{
    /**
     *  @brief This event notifies that the tx power has been set by R_BLE_VS_SetTxPower().
     *
     * ## Event Code: 0x8001
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The tx_power parameter specified by R_BLE_VS_SetTxPower() is out of range.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>The link identified with the conn_hdl specified by R_BLE_VS_SetTxPower() is not found.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_vs_set_tx_pwr_comp_evt_t
     */
    BLE_VS_EVENT_SET_TX_POWER = 0x8001,

    /**
     *  @brief This event notifies that the tx power has been retrieved by R_BLE_VS_GetTxPower().
     *
     * ## Event Code: 0x8002
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_HDL(0x000E)</td>
     *                  <td>The link identified with the conn_hdl specified by R_BLE_VS_GetTxPower() is not found.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_vs_get_tx_pwr_comp_evt_t
     */
    BLE_VS_EVENT_GET_TX_POWER = 0x8002,

    /**
     *  @brief This event notifies that the extended transmitter test has been started by R_BLE_VS_StartTxTest().
     *
     * ## Event Code: 0x8003
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The parameter specified by R_BLE_VS_StartTxTest() is out of range.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_VS_EVENT_TX_TEST_START = 0x8003,

    /**
     *  @brief This event notifies that the number specified by R_BLE_VS_StartTxTest() of packets has been sent.
     *
     * ## Event Code: 0x8004
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_VS_EVENT_TX_TEST_TERM = 0x8004,

    /**
     *  @brief This event notifies that the extended receiver test has been started by R_BLE_VS_StartRxTest().
     *
     * ## Event Code: 0x8005
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The parameter specified by R_BLE_VS_StartRxTest() is out of range.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_VS_EVENT_RX_TEST_START = 0x8005,

    /**
     *  @brief This event notifies that the extended test has been terminated by R_BLE_VS_EndTest().
     *
     * ## Event Code: 0x8006
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_vs_test_end_evt_t
     */
    BLE_VS_EVENT_TEST_END = 0x8006,

    /**
     *  @brief This event notifies that the coding scheme has been configured by R_BLE_VS_SetCodingScheme().
     *
     * ## Event Code: 0x8007
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The coding_scheme parameter specified by R_BLE_VS_SetCodingScheme() is out of range.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_VS_EVENT_SET_CODING_SCHEME_COMP = 0x8007,

    /**
     *  @brief This event notifies that the RF has been configured by R_BLE_VS_SetRfControl().
     *
     * ## Event Code: 0x8008
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The parameter specified by R_BLE_VS_SetRfControl() is out of range.</td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_OPERATION(0x0009)</td>
     *                  <td>During the power on or the power off, the same power state is specified
     *                      by R_BLE_VS_SetRfControl().</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_vs_set_rf_ctrl_comp_evt_t
     */
    BLE_VS_EVENT_RF_CONTROL_COMP = 0x8008,

    /**
     *  @brief This event notifies that public/random address has been set by R_BLE_VS_SetBdAddr().
     *
     * ## Event Code: 0x8009
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The area parameter or the type field in the p_addr parameter specified
     *                      by R_BLE_VS_SetBdAddr() is out of range.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_VS_EVENT_SET_ADDR_COMP = 0x8009,

    /**
     *  @brief This event notifies that public/random address has been retrieved by R_BLE_VS_GetBdAddr().
     *
     * ## Event Code: 0x800A
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The area parameter or the type field in the p_addr parameter specified
     *                      by R_BLE_VS_GetBdAddr() is out of range.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_vs_get_bd_addr_comp_evt_t
     */
    BLE_VS_EVENT_GET_ADDR_COMP = 0x800A,

    /**
     *  @brief This event notifies the application layer that random number has been generated by R_BLE_VS_GetRand().
     *
     * ## Event Code: 0x800B
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *              <tr>
     *                  <td class="paramname">BLE_ERR_INVALID_ARG(0x0003)</td>
     *                  <td>The rand_size parameter specified by R_BLE_VS_GetRand() is out of range.</td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_vs_get_rand_comp_evt_t
     */
    BLE_VS_EVENT_GET_RAND = 0x800B,

    /**
     *  @brief This event notifies the application layer of the state transition of TxFlow.
     *
     * ## Event Code: 0x800C
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  st_ble_vs_tx_flow_chg_evt_t
     */
    BLE_VS_EVENT_TX_FLOW_STATE_CHG = 0x800C,

    /**
     *  @brief This event notifies a failure occurs in RF. After receiving the event, reset MCU or RF.
     *
     * ## Event Code: 0x800D
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  None
     */
    BLE_VS_EVENT_FAIL_DETECT = 0x800D,

    /**
     *  @brief  Invalid VS Event.
     *
     * ## Event Code: 0x80FF
     *
     *  ## result:
     *  <dl class="retval"><dt><dd>
     *          <table class="retval">
     *              <tr>
     *                  <td class="paramname">BLE_SUCCESS(0x0000)</td>
     *                  <td>Success </td>
     *              </tr>
     *          </table>
     *  </dd></dt></dl>
     *
     *  ## Event Data:
     *  none
     */
    BLE_VS_EVENT_INVALID = 0x80FF
} e_r_ble_vs_evt_t;

/*@}*/

/* ============================================= APP Callback Definition ============================================ */

typedef void (* ble_app_init_cb_t)(uint8_t param);

/* ============================================ Event Callback Definition =========================================== */

/******************************************************************************************************************//**
 * @ingroup BLE
 * @typedef ble_event_cb_t
 * @brief   ble_event_cb_t is the callback function type for R_BLE_SetEvent().
 * @param[in] void
 * @return none
 **********************************************************************************************************************/
typedef void (* ble_event_cb_t)(void);

/* ============================================== MAIN API Declarations ============================================== */

/** @addtogroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_Open(void)
 * @brief   Open the BLE protocol stack.
 * @details This function should be called once before using the BLE protocol stack.
 * @retval  BLE_SUCCESS(0x0000) Success
 **********************************************************************************************************************/
ble_status_t R_BLE_Open(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_Close(void)
 * @brief   Close the BLE protocol stack.
 * @details This function should be called once to close the BLE protocol stack.
 * @retval  BLE_SUCCESS(0x0000) Success
 **********************************************************************************************************************/
ble_status_t R_BLE_Close(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_Execute(void)
 * @brief   Execute the BLE task.
 * @details This  handles all the task queued in the BLE protocol stack internal task queue and return.
 *          This function should be called repeatedly in the main loop.
 * @retval  BLE_SUCCESS(0x0000) Success
 **********************************************************************************************************************/
ble_status_t R_BLE_Execute(void);

/******************************************************************************************************************//**
 * @fn uint32_t R_BLE_IsTaskFree(void)
 * @brief   Check the BLE task queue is free or not.
 * @details This function returns the BLE task queue free status.
 *          When this function returns 0x0, call R_BLE_Execute() to execute the BLE task.
 * @retval  0x0 BLE task queue is not free
 * @retval  0x1 BLE task queue is free
 **********************************************************************************************************************/
uint32_t R_BLE_IsTaskFree(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_SetEvent(ble_event_cb_t cb)
 * @brief   Set event.
 * @details This function add an event in the BLE protocol stack internal queue. The event is handled in R_BLE_Execute
 *          just like Bluetooth event. This function is intended to be called in hardware interrupt context.
 *          Even if calling this function with the same cb before the cb is invoked, only one event is registered.
 *          The maximum number of the events can be registered at a time is eight.
 * @param   cb The callback for the event.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_ALREADY_IN_PROGRESS(0x000A) The event already registered with the callback.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) No free slot for the event.
 **********************************************************************************************************************/
ble_status_t R_BLE_SetEvent(ble_event_cb_t cb);

/******************************************************************************************************************//**
 * @fn uint32_t R_BLE_GetVersion(void)
 * @brief   Get the BLE FIT module version.
 * @details This function returns the BLE FIT module version. \n
 *          The major version(BLE_VERSION_MAJOR) is contained in the two most significant bytes,
 *          and the minor version(BLE_VERSION_MINOR) occupies the remaining two bytes.
 * @retval  "BLE_VERSION_MAJOR | BLE_VERSION_MINOR"
 **********************************************************************************************************************/
uint32_t R_BLE_GetVersion(void);

/******************************************************************************************************************//**
 * @fn uint32_t R_BLE_GetLibType(void)
 * @brief   Get the type of BLE protocol stack library.
 * @details This function returns the type of BLE protocol stack library.
 * @retval  BLE_LIB_ALL_FEATS(0x00)  All Features
 * @retval  BLE_LIB_BALANCE(0x01)    Balance
 * @retval  BLE_LIB_COMPACT(0x02)    Compact
 **********************************************************************************************************************/
uint32_t R_BLE_GetLibType(void);

/*@}*/

/* ============================================== GAP API Declarations ============================================== */

/** @defgroup GAP_API GAP
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup GAP_API
 * @fn ble_status_t R_BLE_GAP_Init(ble_gap_app_cb_t gap_cb)
 * @brief   Initialize the Host Stack.
 * @details Host stack is initialized with this function. Before using All the R_BLE APIs,
 *          it's necessary to call this function. A callback function is registered with this function.
 *          In order to receive the GAP event, it's necessary to register a callback function.
 *          The result of this API call is notified in BLE_GAP_EVENT_STACK_ON event.
 * @param[in] gap_cb A callback function registered with this function.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) gap_cb is specified as NULL.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows:
 *          - Host Stack was already initialized.
 *          - The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_Init(ble_gap_app_cb_t gap_cb);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_Terminate(void)
 * @brief   Terminate the Host Stack.
 * @details Host stack is terminated with this function.
 *          In order to reset all the Bluetooth functions, it's necessary to call this function.
 *          The result of this API call is notified in BLE_GAP_EVENT_STACK_OFF event.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) Host stack hasn't been initialized.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_Terminate(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_UpdConn(uint16_t conn_hdl,
 *                                    uint8_t mode,
 *                                    uint16_t accept,
 *                                    st_ble_gap_conn_param_t * p_conn_updt_param
 *                                   )
 * @brief   Update the connection parameters.
 * @details This function updates the connection parameters or replies a request for
 *          updating connection parameters notified by BLE_GAP_EVENT_CONN_PARAM_UPD_REQ event.
 *          When the connection parameters has been updated,
 *          BLE_GAP_EVENT_CONN_PARAM_UPD_COMP event is notified to the application layer.
 * @param[in]   conn_hdl Connection handle identifying the link to be updated.
 * @param[in]   mode Connection parameter update request or response.
 *               |              macro                     |           description                                |
 *               |:-------------------------------------- |:---------------------------------------------------- |
 *               | BLE_GAP_CONN_UPD_MODE_REQ (0x01)       | Request for updating the connection parameters.      |
 *               | BLE_GAP_CONN_UPD_MODE_RSP (0x02)       | Reply a connection parameter update request.         |
 *
 * @param[in]   accept When mode is BLE_GAP_CONN_UPD_MODE_RSP,
 *                     accept or reject the connection parameters update request.
 *                     If mode is BLE_GAP_CONN_UPD_MODE_REQ, accept is ignored.
 *               |              macro                     |           description             |
 *               |:-------------------------------------- |:--------------------------------- |
 *               | BLE_GAP_CONN_UPD_ACCEPT (0x0000)       | Accept the update request.        |
 *               | BLE_GAP_CONN_UPD_REJECT (0x0001)       | Reject the update request.        |
 *
 * @param[in]   p_conn_updt_param Connection parameters to be updated.
 *                                When mode is BLE_GAP_CONN_UPD_MODE_RSP and
 *                                accept is BLE_GAP_CONN_UPD_REJECT, p_conn_updt_param is ignored.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) When accept is BLE_GAP_CONN_UPD_ACCEPT,
 *                                      p_conn_updt_param is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The following is out of range.
 *                                      - mode
 *                                      - accept
 *                                      - conn_intv_min field in p_conn_updt_param
 *                                      - conn_intv_max field in p_conn_updt_param
 *                                      - conn_latency in p_conn_updt_param
 *                                      - sup_to in p_conn_updt_param
 *                                      - conn_hdl
 * @retval  BLE_ERR_INVALID_STATE(0x0008) Not connected with the remote device.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B)  Sending a L2CAP command, an error occurred.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_UpdConn(uint16_t                  conn_hdl,
                               uint8_t                   mode,
                               uint16_t                  accept,
                               st_ble_gap_conn_param_t * p_conn_updt_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetDataLen(uint16_t conn_hdl, uint16_t tx_octets, uint16_t tx_time)
 * @brief   Update the packet size and the packet transmit time.
 * @details This function requests for changing the maximum transmission packet size
 *          and the maximum packet transmission time.
 *          When Controller has received the request from host stack,
 *          BLE_GAP_EVENT_SET_DATA_LEN_COMP event is notified to the application layer.
 *          When the transmission packet size or the transmission time has been changed,
 *          BLE_GAP_EVENT_DATA_LEN_CHG event is notified to the application layer.
 * @param[in] conn_hdl  Connection handle identifying the link whose the transmission packet size or
 *                      the transmission time to be changed.
 * @param[in] tx_octets Maximum transmission packet size.
 *                      Valid range is 0x001B - 0x00FB.
 * @param[in] tx_time   Maximum transmission time(us).
 *                     Valid range is 0x0148 - 0x4290.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetDataLen(uint16_t conn_hdl, uint16_t tx_octets, uint16_t tx_time);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_Disconnect(uint16_t conn_hdl, uint8_t reason)
 * @brief   Disconnect the link.
 * @details This function disconnects a link.
 *          When the link has disconnected, BLE_GAP_EVENT_DISCONN_IND event is notified to the application layer.
 * @param[in]   conn_hdl Connection handle identifying the link to be disconnected.
 * @param[in]   reason The reason for disconnection.
 *                     Usually, set 0x13 which indicates that a user disconnects the link.
 *                     If setting other than 0x13, refer the error code described
 *                     in Core Specification Vol.2 Part D ,"2 Error Code Descriptions".
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) conn_hdl is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_Disconnect(uint16_t conn_hdl, uint8_t reason);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetPhy(uint16_t conn_hdl, st_ble_gap_set_phy_param_t * p_phy_param)
 * @brief   Set the phy for connection.
 * @details This function sets the PHY preferences for the connection.
 *          The result of this API call is notified in BLE_GAP_EVENT_PHY_SET_COMP event.
 *          When the PHY has been updated, BLE_GAP_EVENT_PHY_UPD event is notified to the application layer.
 *
 *          After PHY update, the PHY accept configuration of local device is the same as the values
 *          in BLE_GAP_EVENT_PHY_UPD event. \n
 *          For example, after calling R_BLE_GAP_SetPhy(), if tx_phy,
 *          rx_phy by BLE_GAP_EVENT_PHY_UPD event are updated to 2M PHY,
 *          the PHY accept configuration is 2M PHY only. \n
 *          Therefore after receiving BLE_GAP_EVENT_PHY_UPD event, if local device wants to accept the other PHY
 *          configuration, it needs to call R_BLE_GAP_SetPhy() with the desired PHY accept configuration.
 *
 *          Because the maximum transmission packet size or the maximum transmission time might be updated by
 *          PHY update, if the same packet size or transmission time as the previous one is desired,
 *          change the maximum transmission packet size or the maximum transmission time by @ref R_BLE_GAP_SetDataLen().
 *
 * @param[in] conn_hdl  Connection handle identifying the link whose PHY to be updated.
 * @param[in] p_phy_param PHY preferences.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_phy_param is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) conn_hdl or option field in p_phy_param is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetPhy(uint16_t conn_hdl, st_ble_gap_set_phy_param_t * p_phy_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetDefPhy(st_ble_gap_set_def_phy_param_t * p_def_phy_param)
 * @brief   Set the default phy which allows remote device to change.
 * @details This function sets the PHY preferences which a remote device may change.
 *          The result of this API call is notified in BLE_GAP_EVENT_DEF_PHY_SET_COMP event.
 * @param[in] p_def_phy_param  The PHY preference which a remote device may change.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_def_phy_param is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) tx_phys or tx_phys field in p_def_phy_param is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetDefPhy(st_ble_gap_set_def_phy_param_t * p_def_phy_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetPrivMode(st_ble_dev_addr_t * p_addr,
 *                                        uint8_t * p_privacy_mode,
 *                                        uint8_t device_num
 *                                       )
 * @brief   Set the privacy mode.
 * @details This function sets privacy mode for the remote device registered in Resolving List.
 *          By default, Network Privacy Mode is set.\n
 *          The result of this API call is notified in BLE_GAP_EVENT_PRIV_MODE_SET_COMP event.
 * @param[in] p_addr  An array of identity address of the remote device to set privacy mode.
 *                    The number of elements is specified by device_num.\n\n
 * @param[in] p_privacy_mode  An array of privacy mode to set to remote device.
 *            The number of elements is specified by device_num.\n
 *            The following value is set as the privacy mode.
 *               |              macro                     |           description             |
 *               |:-------------------------------------- |:--------------------------------- |
 *               | BLE_GAP_NET_PRIV_MODE (0x00)           | Network Privacy Mode.             |
 *               | BLE_GAP_DEV_PRIV_MODE (0x01)           | Device Privacy Mode.              |
 * @param[in] device_num  The number of devices to set privacy mode.
 *                        Valid range is 1-BLE_GAP_RSLV_LIST_MAX_ENTRY.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_addr or p_privacy_mode is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The following parameter is out of range.
 *                                       - The address type in p_addr.
 *                                       - The privacy mode specified by p_privacy_mode.
 *                                       - device_num
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows:
 *                                         - While configuring privacy mode, this function was called.
 *                                         - The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetPrivMode(st_ble_dev_addr_t * p_addr, uint8_t * p_privacy_mode, uint8_t device_num);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ConfWhiteList(uint8_t op_code, st_ble_dev_addr_t * p_addr, uint8_t device_num)
 * @brief   Set White List.
 * @details This function supports the following operations regarding White List.
 *          - Add the device to White List.
 *          - Delete the device from White List.
 *          - Clear White List.
 *
 *           The total number of White List entries is defined as BLE_GAP_WHITE_LIST_MAX_ENTRY.
 *           The result of this API call is notified in BLE_GAP_EVENT_WHITE_LIST_CONF_COMP event.
 * @param[in]  op_code
 *              The operation for  White List.
 *               |              macro            |           description            |
 *               |:----------------------------- |:-------------------------------- |
 *               | BLE_GAP_LIST_ADD_DEV(0x01)    | Add the device to the list.      |
 *               | BLE_GAP_LIST_REM_DEV(0x02)    | Delete the device from the list. |
 *               | BLE_GAP_LIST_CLR(0x03)        | Clear the list.                  |
 * @param[in]  p_addr An array of device address to add / delete to the list.
 *                    The number of elements is specified by device_num.
 *                    If op_code is BLE_GAP_LIST_CLR, p_addr is ignored.
 * @param[in]  device_num The number of devices add / delete to the list.
 *                        Valid range is 1-BLE_GAP_WHITE_LIST_MAX_ENTRY.
 *                        If op_code is BLE_GAP_LIST_CLR, device_num is ignored.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) When op_code is BLE_GAP_LIST_ADD_DEV or BLE_GAP_LIST_REM_DEV,
 *                                      p_addr is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) op_code or address type field in p_addr is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows:
 *                                        - While operating White List, this function was called.
 *                                        - The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for operating the White List.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ConfWhiteList(uint8_t op_code, st_ble_dev_addr_t * p_addr, uint8_t device_num);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_GetVerInfo(void)
 * @brief   Get the version number of the Controller and the host stack.
 * @details This function retrieves the version information of local device.
 *          The result of this API call is notified in BLE_GAP_EVENT_LOC_VER_INFO event.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_GetVerInfo(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReadPhy(uint16_t conn_hdl)
 * @brief   Get the phy settings.
 * @details This function gets the PHY settings for the connection.
 *          The result of this API call is notified in BLE_GAP_EVENT_PHY_RD_COMP event.
 * @param[in] conn_hdl  Connection handle identifying the link whose PHY settings to be retrieved.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) conn_hdl is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReadPhy(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ConfRslvList(uint8_t op_code,
 *                                         st_ble_dev_addr_t * p_addr,
 *                                         st_ble_gap_rslv_list_key_set_t * p_peer_irk,
 *                                         uint8_t device_num
 *                                         )
 * @brief   Set Resolving List.
 * @details This function supports the following operations regarding Resolving List.
 *          - Add the device to Resolving List.
 *          - Delete the device from Resolving List.
 *          - Clear Resolving List.
 *
 *           In order to generate a resolvable private address,
 *           a local IRK needs to be registered by R_BLE_GAP_SetLocIdInfo().
 *           If communicating with the identity address, register all-zero IRK as local IRK.
 *           In order to resolve resolvable private address of the remote device,
 *           the IRK distributed from the remote device needs to be added to Resolving List.
 *           The total number of Resolving List entries is defined as BLE_GAP_RESOLV_LIST_MAX_ENTRY.
 *           The result of this API call is notified in BLE_GAP_EVENT_RSLV_LIST_CONF_COMP event.
 * @param[in]  op_code
 *              The operation for Resolving List.
 *               |              macro            |           description            |
 *               |:----------------------------- |:-------------------------------- |
 *               | BLE_GAP_LIST_ADD_DEV(0x01)    | Add the device to the list.      |
 *               | BLE_GAP_LIST_REM_DEV(0x02)    | Delete the device from the list. |
 *               | BLE_GAP_LIST_CLR(0x03)        | Clear the list.                  |
 * @param[in]  p_addr An array of Identity Addresses to add / delete to the list.
 *                    The number of elements is specified by device_num.
 *                    If op_code is BLE_GAP_LIST_CLR, p_addr is ignored.
 * @param[in]  p_peer_irk The remote IRK and the type of local IRK added to Resolving List.
 *                        If op_code is other than BLE_GAP_LIST_ADD_DEV, p_peer_irk is ignored.
 *                        The number of elements is specified by device_num.
 * @param[in]  device_num The number of devices add / delete to the list.
 *                        Valid range is 1-BLE_GAP_RSLV_LIST_MAX_ENTRY.
 *                        If op_code is BLE_GAP_LIST_CLR, device_num is ignored.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The reason for this error is as follows:
 *                                      - When added to or deleted from the list, p_addr is specified as NULL.
 *                                      - When added to the list, p_peer_irk is specified as NULL.
 *
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *                                      - op_code is out of range.
 *                                      - When op_code is BLE_GAP_LIST_ADD_DEV or
 *                                        BLE_GAP_LIST_REM_DEV, device_num is out of range.
 *                                      - When op_code is BLE_GAP_LIST_ADD_DEV or
 *                                        BLE_GAP_LIST_REM_DEV, address type field in p_addr is out of range.
 *
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows:
 *                                        - While operating Resolving List, this function was called.
 *                                        - The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for operating the Resolving List.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The specified Identity Address was not found in Resolving List.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ConfRslvList(uint8_t                          op_code,
                                    st_ble_dev_addr_t              * p_addr,
                                    st_ble_gap_rslv_list_key_set_t * p_peer_irk,
                                    uint8_t                          device_num);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_EnableRpa(uint8_t enable)
 * @brief   Enable/Disable address resolution and generation of a resolvable private address.
 * @details This function enables or disables RPA functionality. The RPA functionality includes the following.
 *          - Generation of local resolvable private address
 *          - Resolution of remote resolvable private address
 *
 *          In order to do advertising, scanning or creating a link with local resolvable private address,
 *          the RPA functionality needs to be enabled.
 *          After enabling the RPA functionality and the identity address of remote device and
 *          the IRKs of local/remote device is registered,
 *          local device can generate own resolvable private address in the time interval set by R_BLE_GAP_SetRpaTo(),
 *          and can resolve a resolvable private address of a remote device.
 *          It is recommended that the RPA functionality is called immediately
 *          after the initialization by R_BLE_GAP_Init().
 *          The result of this API call is notified in BLE_GAP_EVENT_RPA_EN_COMP event.
 * @param[in] enable  Enable or disable address resolution function.
 *               |              macro              |           description                     |
 *               |:------------------------------- |:----------------------------------------- |
 *               | BLE_GAP_RPA_DISABLED(0x00)      | Disable RPA generation/resolution.        |
 *               | BLE_GAP_RPA_ENABLED(0x01)       | Enable RPA generation/resolution.         |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) enable is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_EnableRpa(uint8_t enable);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetRpaTo(uint16_t rpa_timeout)
 * @brief   Set the update time of resolvable private address.
 * @details This function sets the time interval to update the resolvable private address.
 *          The result of this API call is notified in BLE_GAP_EVENT_SET_RPA_TO_COMP event.
 * @param[in] rpa_timeout  Time interval to update resolvable private address in seconds.
 *                         Valid range is 0x003C - 0xA1B8.
 *                         Default is 900s.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetRpaTo(uint16_t rpa_timeout);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReadRpa(st_ble_dev_addr_t * p_addr)
 * @brief   Get the resolvable private address of local device.
 * @details This function retrieves the local resolvable private address.
 *          Before getting the address, enable the resolvable private address function by R_BLE_GAP_EnableRpa().
 *          The result of this API call is notified in BLE_GAP_EVENT_RD_RPA_COMP event.
 * @param[in] p_addr  Identity address registered in Resolving List.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_addr is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) Address type in p_addr is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows.
 *                                        - When retrieving the local resolvable private address,
 *                                          this function was called.
 *                                        - The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReadRpa(st_ble_dev_addr_t * p_addr);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReadRssi(uint16_t conn_hdl)
 * @brief   Get RSSI.
 * @details This function retrieves RSSI.
 *          The result of this API call is notified in BLE_GAP_EVENT_RSSI_RD_COMP event.
 * @param[in] conn_hdl  Connection handle identifying the link whose RSSI to be retrieved.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) conn_hdl is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReadRssi(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReadChMap(uint16_t conn_hdl)
 * @brief   Get the Channel Map.
 * @details This function retrieves the channel map.
 *          The result of this API call is notified in BLE_GAP_EVENT_CH_MAP_RD_COMP event.
 * @param[in] conn_hdl  Connection handle identifying the link whose channel map to be retrieved.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) conn_hdl is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReadChMap(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetRandAddr(uint8_t * p_random_addr)
 * @brief   Set a random address.
 * @details This function sets static address or non-resolvable private address to Controller.
 *          Refer to Core Specification Vol 6, PartB,
 *          "1.3.2 Random Device Address" regarding the format of the random address.
 *          Resolvable private address cannot set by this API.
 *          The result of this API call is notified in BLE_GAP_EVENT_RAND_ADDR_SET_COMP event.
 * @param[in] p_random_addr  Static address or non-resolvable private address. \n
 *                           The BD address setting format is little endian.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_random_addr is specified as NULL.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetRandAddr(uint8_t * p_random_addr);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetAdvParam(st_ble_gap_adv_param_t * p_adv_param)
 * @brief   Set advertising parameters.
 * @details This function sets advertising parameters.
 *          It's possible to do advertising where the advertising parameters are different every each advertising set.
 *          The number of advertising set in the Controller is defined as BLE_MAX_NO_OF_ADV_SETS_SUPPORTED.
 *          Each advertising set is identified with advertising handle (0x00-0x03).
 *          Create an advertising set with this function before start advertising,
 *          setting periodic advertising parameters, start periodic advertising,
 *          setting advertising data/scan response data/periodic advertising data.
 *          The result of this API call is notified in BLE_GAP_EVENT_ADV_PARAM_SET_COMP event.
 * @param[in]   p_adv_param Advertising parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_adv_param is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The below p_adv_param field value is out of range.
 *          - adv_handle
 *          - adv_intv_min/adv_intv_max
 *          - adv_ch_map
 *          - o_addr_type
 *          - p_addr_type
 *          - adv_phy
 *          - sec_adv_phy
 *          - scan_req_ntf_flag
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetAdvParam(st_ble_gap_adv_param_t * p_adv_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetAdvSresData(st_ble_gap_adv_data_t * p_adv_srsp_data)
 * @brief   Set advertising data/scan response data/periodic advertising data.
 * @details This function sets advertising data/scan response data/periodic advertising data to the advertising set.
 *          It is necessary to create an advertising set by R_BLE_GAP_SetAdvParam(), before calling this function.
 *          Set advertising data/scan response data/periodic advertising data, after allocating the memory for the data.
 *          The following shall be applied regarding the adv_prop_type field and the data_type field in
 *          st_ble_gap_adv_param_t parameter specified in R_BLE_GAP_SetAdvParam().
 *
 *          The following shall be applied regarding the adv_prop_type field and the data_type field in
 *          st_ble_gap_adv_param_t parameter specified in R_BLE_GAP_SetAdvParam().
 *          - When adv_prop_type is Legacy Advertising PDU type,
 *            - it's possible to set advertising data/scan response data up to 31 bytes.
 *            - advertising data/scan response data can be updated by this function in advertising.
 *          - When adv_prop_type is Extended Advertising PDU type,
 *            - it's possible to set at most 1650 bytes of data as advertising data/scan response data
 *              per 1 advertising set.
 *            - the total buffer size in Controller for advertising data/scan response data is 4250 bytes.
 *              Therefore please note that more than 4250 bytes of advertising data/scan response data
 *              can not be set to all the advertising sets.
 *              Please refer to Figure 1.1 and Figure 1.2 about examples of setting advertising data/scan response data.
 *            - it's possible to update advertising data/scan response data in advertising,
 *              if the data_length field in st_ble_gap_adv_data_t parameter is up to 251 bytes.
 *              @image html "adv_data_alloc_fail_en.svg" "Figure 1.1" width=700px
 *              @image html "adv_data_alloc_success_en.svg" "Figure 1.2" width=700px
 *          - When periodic advertising data is set,
 *            - At most 1650 bytes of data can be set to 1 advertising set.
 *            - The total buffer size in Controller for periodic advertising data is 4306 bytes.
 *              Therefore please note that more than 4306 bytes of periodic advertising data can not be
 *              set to all the advertising sets.
 *            - it's possible to update periodic advertising data in advertising,
 *              if the data_length field in st_ble_gap_adv_data_t parameter is up to 252 bytes.
 *
 *         The result of this API call is notified in @ref BLE_GAP_EVENT_ADV_DATA_UPD_COMP event.
 *
 * @param[in]   p_adv_srsp_data   Advertising data/scan response data/periodic advertising data.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The reason for this error is as follows:
 *          - p_adv_srsp_data is specified as NULL.
 *          - data_length field in p_adv_srsp_data parameter is not 0 and p_data field is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The following field in p_adv_srsp_data parameter is out of range.
 *          - adv_hdl
 *          - data_type
 *          - data_length
 *          - zero_length_flag
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetAdvSresData(st_ble_gap_adv_data_t * p_adv_srsp_data);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StartAdv(uint8_t adv_hdl, uint16_t duration, uint8_t max_extd_adv_evts)
 * @brief   Start advertising.
 * @details This function starts advertising.
 *          Create the advertising set specified with adv_hdl by R_BLE_GAP_SetAdvParam(),
 *          before calling this function.
 *          The result of this API call is notified in BLE_GAP_EVENT_ADV_ON event.
 * @param[in]   adv_hdl
 *              The advertising handle pointing to the advertising set which starts advertising.
 *              The valid range is 0x00 - 0x03.
 * @param[in]   duration
 *              The duration for which the advertising set identified by adv_hdl is enabled.
 *              Time = duration * 10ms.
 *              When the duration expires, BLE_GAP_EVENT_ADV_OFF event notifies that advertising is stopped.
 *              The valid range is 0x0000 - 0xFFFF.
 *              The duration parameter is ignored when the value is set to 0x0000.
 * @param[in]   max_extd_adv_evts
 *              The maximum number of advertising events that be sent during advertising.
 *              When all the advertising events(max_extd_adv_evts) have been sent,
 *              BLE_GAP_EVENT_ADV_OFF event notifies that advertising is stopped.
 *              The max_extd_adv_evts parameter is ignored when the value is set to 0x00.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) adv_hdl is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StartAdv(uint8_t adv_hdl, uint16_t duration, uint8_t max_extd_adv_evts);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StopAdv(uint8_t adv_hdl)
 * @brief   Stop advertising.
 * @details This function stops advertising. The result of this API call is notified in BLE_GAP_EVENT_ADV_OFF event.
 * @param[in]   adv_hdl
 *              The advertising handle pointing to the advertising set which stops advertising.
 *              The valid range is 0x00 - 0x03.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) adv_hdl is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StopAdv(uint8_t adv_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetPerdAdvParam(st_ble_gap_perd_adv_param_t * p_perd_adv_param)
 * @brief   Set periodic advertising parameters.
 * @details This function sets periodic advertising parameters.
 *          Create the advertising set which supports Non-Connectable,
 *          Non-Scannable advertising by R_BLE_GAP_SetAdvParam() before setting periodic advertising parameters.
 *          The result of this API call is notified in BLE_GAP_EVENT_PERD_ADV_PARAM_SET_COMP event.
 * @param[in]  p_perd_adv_param  Periodic advertising parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_perd_adv_param is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The following field in the p_perd_adv_param parameter is out of range.
 *          - adv_hdl
 *          - perd_intv_min or perd_intv_max
 *          - prop_type is neither 0x0000 nor 0x0040(BLE_GAP_PERD_PROP_TX_POWER)
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetPerdAdvParam(st_ble_gap_perd_adv_param_t * p_perd_adv_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StartPerdAdv(uint8_t adv_hdl)
 * @brief   Start periodic advertising.
 * @details This function starts periodic advertising.
 *          Set periodic advertising parameters to the advertising set, before starting periodic advertising.
 *          The result of this API call is notified in BLE_GAP_EVENT_PERD_ADV_ON event.
 * @param[in]  adv_hdl   Advertising handle identifying the advertising set which starts periodic advertising.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) adv_hdl is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StartPerdAdv(uint8_t adv_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StopPerdAdv(uint8_t adv_hdl)
 * @brief   Stop periodic advertising.
 * @details This function stops periodic advertising.
 *          If the return value of this API is BLE_SUCCESS, the result is notified in BLE_GAP_EVENT_PERD_ADV_OFF event.
 * @param[in]  adv_hdl   Specify the handle of Advertising Set to stop Periodic Advertising.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) adv_hdl is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StopPerdAdv(uint8_t adv_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_GetRemainAdvBufSize(uint16_t * p_remain_adv_data_size,
 *                                                uint16_t * p_remain_perd_adv_data_size
 *                                               )
 * @brief   Get buffer size for advertising data/scan response data/periodic advertising data in the Controller.
 * @details This function gets the total size of advertising data/scan response data/periodic advertising data
 *          which can be currently set to Controller(all of the advertising sets).
 *          The application layer gets the data sizes via the parameters.
 *          By this API function call, no events occur.
 * @param[out]  p_remain_adv_data_size
 *              The free buffer size of Controller to which advertising data/scan response data can be currently set.
 * @param[out]  p_remain_perd_adv_data_size
 *              The free buffer size of Controller to which periodic advertising data can be currently set.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_remain_adv_data_size or p_remain_perd_adv_data_size is specified as NULL.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_GetRemainAdvBufSize(uint16_t * p_remain_adv_data_size, uint16_t * p_remain_perd_adv_data_size);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_RemoveAdvSet(uint8_t op_code, uint8_t adv_hdl)
 * @brief   Delete advertising set.
 * @details This function deletes an advertising set or deletes all the advertising sets.
 *          The result of this API call is notified in BLE_GAP_EVENT_ADV_SET_REMOVE_COMP event.
 * @param[in]  op_code The operation for delete or clear.
 *               |              macro               |           description            |
 *               |:-------------------------------- |:-------------------------------- |
 *               | BLE_GAP_RMV_ADV_SET_REM_OP(0x01) | Delete an advertising set.       |
 *               | BLE_GAP_RMV_ADV_SET_CLR_OP(0x02) | Delete all the advertising sets. |
 * @param[in]  adv_hdl
 *             Advertising handle identifying the advertising set deleted.
 *             If op_code is BLE_GAP_RMV_ADV_SET_CLR_OP, adv_hdl is ignored.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *                                      - op_code is out of range.
 *                                      - When op_code is BLE_GAP_RMV_ADV_SET_REM_OP(0x01), adv_hdl is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_RemoveAdvSet(uint8_t op_code, uint8_t adv_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_CreateConn(st_ble_gap_create_conn_param_t * p_param)
 * @brief   Request for a link establishment.
 * @details This function sends a connection request to a remote device to create a link.
 *          When Controller has received a request for establishment of a link from host stack,
 *          BLE_GAP_EVENT_CREATE_CONN_COMP event is notified to the application layer.
 *          When the link is established, BLE_GAP_EVENT_CONN_IND event is notified to the application layer.
 * @param[in] p_param Connection parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The reason for this error is as follows:
 *                                      - p_param is specified as NULL.
 *                                      - p_conn_param_1M field and p_conn_param_2M and
 *                                        p_conn_param_coded field in p_param are specified as NULL.
 *                                      - When creating a link with 1M PHY, p_conn_param
 *                                        in p_conn_param_1M field in p_param is specified as NULL.
 *                                      - When creating a link with 2M PHY,
 *                                        p_conn_param in p_conn_param_2M field in p_param is specified as NULL.
 *                                      - When creating a link with coded MPHY,
 *                                        p_conn_param in p_conn_param_coded field in p_param is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *                                      - init_filter_policy in p_param is out of range.
 *                                      - remote_bd_addr_type field or own_addr_type address field
 *                                        in p_param is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_CreateConn(st_ble_gap_create_conn_param_t * p_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_CancelCreateConn(void)
 * @brief   Cancel the request for a link establishment.
 * @details This function cancels a request for establishing a link.
 *          When Controller has received the cancel request from host stack,
 *          BLE_GAP_EVENT_CONN_CANCEL_COMP event is notified to the application layer.
 *          When the cancel procedure has completed,
 *          BLE_GAP_EVENT_CONN_IND event is notified to the application layer.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_CancelCreateConn(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetChMap(uint8_t * p_channel_map)
 * @brief   Set the Channel Map.
 * @details This function sets the channel map.
 *          The result of this API call is notified in BLE_GAP_EVENT_CH_MAP_SET_COMP event.
 * @param[in] p_channel_map  Channel map.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_channel_map is specified as NULL.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetChMap(uint8_t * p_channel_map);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StartScan(st_ble_gap_scan_param_t * p_scan_param,
 *                                      st_ble_gap_scan_on_t * p_scan_enable
 *                                     )
 * @brief   Set scan parameter and start scan.
 * @details This function starts scanning.
 *          When scanning for the first time, set the p_scan_param.
 *          Setting scan parameters can be omitted by specifying p_scan_param as NULL after next time.
 *          The result of this API call is notified in BLE_GAP_EVENT_SCAN_ON event.
 *          Advertising report is notified in BLE_GAP_EVENT_ADV_REPT_IND event.
 *          Figure 1.3 shows the relationship between scan period, scan duration, scan interval and scan window.
 *          @image html "scan_period_en.svg" "Figure 1.3"
 *
 *          When scan duration is non-zero, scan period is zero and scan duration expires,
 *          BLE_GAP_EVENT_SCAN_TO event is notified to the application layer.
 * @param[in]  p_scan_param
 *              Scan parameter.
 *              When p_scan_param is specified as NULL,
 *              host stack doesn't set scan parameters and start scanning with the previous parameters.
 * @param[in]  p_scan_enable
 *             Scan period, scan duration, duplicate filter and procedure type.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The reason for this error is as follows:
 *                                      - p_scan_enable is specified as NULL.
 *                                      - p_phy_param_1M field and p_phy_param_coded field in
 *                                        p_scan_param are specified as NULL.
 *
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *                                      - proc_type field in p_scan_enable is out of range.
 *                                      - filter_dups in p_scan_enable is out of range.
 *                                      - o_addr_type in p_scan_param is out of range.
 *                                      - filter_policy in p_scan_param is out of range.
 *                                      - scan_type of p_scan_param's p_phy_param_1M or p_phy_param_coded is out of range.
 *
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StartScan(st_ble_gap_scan_param_t * p_scan_param, st_ble_gap_scan_on_t * p_scan_enable);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StopScan(void)
 * @brief   Stop scan.
 * @details This function stops scanning.
 *          The result of this API call is notified in BLE_GAP_EVENT_SCAN_OFF event.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StopScan(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_CreateSync(st_ble_dev_addr_t * p_addr,
 *                                       uint8_t adv_sid,
 *                                       uint16_t skip,
 *                                       uint16_t sync_to
 *                                      )
 * @brief   Request for a periodic sync establishment.
 * @details This function sends a request for establishment of a periodic sync to a advertiser.
 *          In order to create a periodic sync, scan needs to be starting by R_BLE_GAP_StartScan().
 *          When Controller has received the request from host stack,
 *          BLE_GAP_EVENT_CREATE_SYNC_COMP event is notified to the application layer.
 *          When the periodic sync is established, BLE_GAP_EVENT_SYNC_EST event is notified to the application layer.
 * @param[in]  p_addr
 *             The address of periodic advertiser.When p_addr is specified as NULL,
 *             local device creates a periodic sync with the advertiser registered in Periodic Advertiser List.
 * @param[in]  adv_sid
 *             Advertising SID. When p_addr is specified as NULL, adv_sid is ignored.
 *             Valid range is 0x00 - 0x0F.
 * @param[in]  skip
 *             The number of consecutive periodic advertising packets
 *             that local device may skip after receiving a periodic advertising packet.
 *             Valid range is 0x0000 - 0x01F3.
 * @param[in]  sync_to
 *             The maximum permitted time between successful receives.When sync_to expires,
 *             the periodic sync is lost.
 *             Time(ms) = sync_to * 10.
 *             Valid range is 0x000A - 0x4000.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_addr is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The following parameter is out of range.
 *                                      - address type in p_addr
 *                                      - adv_sid
 *                                      - skip
 *                                      - sync_to
 *
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_CreateSync(st_ble_dev_addr_t * p_addr, uint8_t adv_sid, uint16_t skip, uint16_t sync_to);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_CancelCreateSync(void)
 * @brief   Cancel the request for a periodic sync establishment.
 * @details This function cancels a request for establishing a periodic sync.
 *          The result of this API call is notified in BLE_GAP_EVENT_SYNC_CREATE_CANCEL_COMP event.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_CancelCreateSync(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_TerminateSync(uint16_t sync_hdl)
 * @brief   Terminate the periodic sync.
 * @details This function terminates a periodic sync.
 *          The result of this API call is notified in BLE_GAP_EVENT_SYNC_TERM event.
 * @param[in]  sync_hdl Sync handle identifying the periodic sync to be terminated.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) sync_hdl is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_TerminateSync(uint16_t sync_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ConfPerdAdvList(uint8_t op_code,
 *                                            st_ble_dev_addr_t * p_addr,
 *                                            uint8_t * p_adv_sid_set,
 *                                            uint8_t device_num
 *                                           )
 * @brief   Set Periodic Advertiser List.
 * @details This function supports the following operations regarding Periodic Advertiser List.
 *          - Add the device to Periodic Advertiser List.
 *          - Delete the device from Periodic Advertiser List.
 *          - Clear Periodic Advertiser List.
 *
 *           The total number of Periodic Advertiser List entries is defined as BLE_GAP_PERD_LIST_MAX_ENTRY.
 *           The result of this API call is notified in BLE_GAP_EVENT_PERD_LIST_CONF_COMP event.
 * @param[in]  op_code
 *              The operation for Periodic Advertiser List.
 *               |              macro            |           description            |
 *               |:----------------------------- |:-------------------------------- |
 *               | BLE_GAP_LIST_ADD_DEV(0x01)    | Add the device to the list.      |
 *               | BLE_GAP_LIST_REM_DEV(0x02)    | Delete the device from the list. |
 *               | BLE_GAP_LIST_CLR(0x03)        | Clear the list.                  |
 * @param[in]  p_addr An array of device address to add / delete to the list.
 *                    The number of elements is specified by device_num.
 *                    If op_code is BLE_GAP_LIST_CLR, p_addr is ignored.
 * @param[in]  p_adv_sid_set An array of SID of the advertiser to add / delete to the list.
 *                           The number of elements is specified by device_num.
 *                           If op_code is BLE_GAP_LIST_CLR, p_adv_sid_set is ignored.
 * @param[in]  device_num The number of devices add / delete to the list.
 *                        Valid range is 1-BLE_GAP_PERD_LIST_MAX_ENTRY.
 *                        If op_code is BLE_GAP_LIST_CLR, device_num is ignored.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) When op_code is BLE_GAP_LIST_ADD_DEV or BLE_GAP_LIST_REM_DEV,
 *                                      p_addr or p_adv_sid_set is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) op_code or address type field in p_addr or p_adv_sid_set or
 *                                      device_num is out of range.
 * @retval  BLE_ERR_UNSUPPORTED(0x0007) Not supported.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows:
 *                                        - While operating Periodic Advertiser List, this function was called.
 *                                        - The task for host stack is not running.
 *
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for operating periodic advertiser.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ConfPerdAdvList(uint8_t             op_code,
                                       st_ble_dev_addr_t * p_addr,
                                       uint8_t           * p_adv_sid_set,
                                       uint8_t             device_num);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_AuthorizeDev(uint16_t conn_hdl, uint8_t author_flag)
 * @brief   Authorize a remote device.
 * @details User authorizes a remote device by this function.
 *          This function is used when a remote device accesses a GATT Characteristic
 *          in local device which requests user authorization.
 *          The result of this API call is returned by a return value.
 * @param[in] conn_hdl  Connection handle identifying the remote device to be authorized or not by user.
 * @param[in] author_flag  Authorize or not the remote device.
 *               |              macro            |           description            |
 *               |:----------------------------- |:-------------------------------- |
 *               | BLE_GAP_NOT_AUTHORIZED(0x00)  | Not authorize the remote device. |
 *               | BLE_GAP_AUTHORIZED(0x01)      | Authorize the remote device.     |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) author_flag is out of range.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_AuthorizeDev(uint16_t conn_hdl, uint8_t author_flag);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_GetRemDevInfo(uint16_t conn_hdl)
 * @brief   Get the information about remote device.
 * @details This function retrieves information about the remote device.
 *          The information includes BD_ADDR, the version number and LE features.
 *          The result of this API call is notified in BLE_GAP_EVENT_GET_REM_DEV_INFO event.
 * @param[in] conn_hdl  Connection handle identifying the remote device whose information to be retrieved.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_GetRemDevInfo(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetPairingParams(st_ble_gap_pairing_param_t * p_pair_param)
 * @brief   Set the parameters using pairing.
 * @details This function sets the parameters used in pairing.
 *          The parameters set by this API are sent to the remote device when pairing occurred.
 *          The result of this API call is returned by a return value.
 * @param[in] p_pair_param    Pairing parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The following field in p_pair_param is out of range.
 *                                      - iocap
 *                                      - max_key_size
 *                                      - mitm
 *                                      - bonding
 *                                      - key_notf
 *                                      - sec_conn_only
 *
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetPairingParams(st_ble_gap_pairing_param_t * p_pair_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetLocIdInfo(st_ble_dev_addr_t * p_lc_id_addr, uint8_t * p_lc_irk)
 * @brief   Set the IRK and the identity address distributed to a remote device.
 * @details This function registers local IRK and identity address of local device in host stack.
 *          The IRK and the identity address are distributed to a remote device in pairing.
 *          The result of this API call is returned by a return value.
 * @param[in] p_lc_id_addr  Identity address to be registered in host stack.
 * @param[in] p_lc_irk  IRK to be registered in host stack.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_lc_id_addr or p_lc_irk is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) Address type field in p_lc_id_addr is out of range.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetLocIdInfo(st_ble_dev_addr_t * p_lc_id_addr, uint8_t * p_lc_irk);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetLocCsrk(uint8_t * p_local_csrk)
 * @brief   Set the CSRK distributed to a remote device.
 * @details This function registers local CSRK in host stack.
 *          The CSRK is distributed to a remote device in pairing.
 *          The result of this API call is returned by a return value.
 * @param[in] p_local_csrk    CSRK to be registered in host stack.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_local_csrk is specified as NULL.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetLocCsrk(uint8_t * p_local_csrk);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StartPairing(uint16_t conn_hdl)
 * @brief   Start pairing.
 * @details This function starts pairing with a remote device.
 *          The result of this API call is returned by a return value.
 *          The result of pairing is notified in BLE_GAP_EVENT_PAIRING_COMP event.
 * @param[in] conn_hdl    Connection handle identifying the remote device which local device starts pairing with.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) While generating OOB data, this function was called.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) While pairing, this function was called.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StartPairing(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReplyPairing(uint16_t conn_hdl, uint8_t response)
 * @brief   Reply the pairing request from a remote device.
 * @details This function replies to the pairing request from the remote device.
 *          The pairing request from the remote device is notified in BLE_GAP_EVENT_PAIRING_REQ event.
 *          The result of this API call is returned by a return value.
 *          The result of pairing is notified in BLE_GAP_EVENT_PAIRING_COMP event.
 * @param[in] conn_hdl    Connection handle identifying the remote device which local device starts pairing with.
 * @param[in] response    Accept or reject the pairing request from the remote device.
 *               |              macro            |           description            |
 *               |:----------------------------- |:-------------------------------- |
 *               | BLE_GAP_PAIRING_ACCEPT(0x00)  | Accept the pairing request.      |
 *               | BLE_GAP_PAIRING_REJECT(0x01)  | Reject the pairing request.      |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) response is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) While generating OOB data, this function was called.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 * @retval  BLE_ERR_NOT_YET_READY(0x0012) When this function was called,
 *                                        host stack has not yet received BLE_GAP_EVENT_PAIRING_REQ event.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReplyPairing(uint16_t conn_hdl, uint8_t response);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_StartEnc(uint16_t conn_hdl)
 * @brief   Encryption the link.
 * @details This function starts encryption of the link.
 *          In case of master device, the local device requests for the encryption to a remote device.
 *          In case of slave device, the local device sends a Security Request to a remote device.
 *          After receiving the Security Request, the remote device requests for the encryption to the local device.
 *          The result of the encryption is returned in BLE_GAP_EVENT_ENC_CHG event.
 * @param[in] conn_hdl  Connection handle identifying the link which is encrypted.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows:
 *                                        - Pairing has not been completed.
 *                                        - The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_StartEnc(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReplyPasskeyEntry(uint16_t conn_hdl, uint32_t passkey, uint8_t response)
 * @brief   Reply the passkey entry request.
 * @details When BLE_GAP_EVENT_PASSKEY_ENTRY_REQ event is notified,
 *          the response to passkey entry is sent by this function.
 *          The result of this API call is returned by a return value.
 * @param[in] conn_hdl    Connection handle identifying the remote device which the reply to passkey entry is sent.
 * @param[in] passkey     Passkey.
 *                        The valid range is 000000 - 999999 in decimal.
 * @param[in] response    Active or negative reply to passkey entry.
 *               |              macro            |           description              |
 *               |:----------------------------- |:---------------------------------- |
 *               | BLE_GAP_PAIRING_ACCEPT(0x00)  | Accept the passkey entry pairing.  |
 *               | BLE_GAP_PAIRING_REJECT(0x01)  | Reject the passkey entry pairing.  |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) passkey or response is out of range.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 * @retval  BLE_ERR_NOT_YET_READY(0x0012) When this function was called, pairing has not yet started.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReplyPasskeyEntry(uint16_t conn_hdl, uint32_t passkey, uint8_t response);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReplyNumComp(uint16_t conn_hdl, uint8_t response)
 * @brief   Reply the numeric comparison request.
 * @details When BLE_GAP_EVENT_NUM_COMP_REQ event is notified,
 *          the response to Numeric Comparison is sent by this function.
 *          The result of this API call is returned by a return value.
 * @param[in] conn_hdl  Connection handle identifying the remote device which the reply to Numeric Comparison is sent.
 * @param[in] response  Active or negative reply in Numeric Comparison.
 *            |              macro         |           description                                                   |
 *            |:-------------------------- |:----------------------------------------------------------------------- |
 *            |BLE_GAP_PAIRING_ACCEPT(0x00)| The number displayed in the local is the same as the one of the remote. |
 *            |BLE_GAP_PAIRING_REJECT(0x01)| The number displayed in the local is differs from the one of the remote.|
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) response is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) When this function was called,
 *                                        host stack has not yet received @ref BLE_GAP_EVENT_NUM_COMP_REQ event.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 * @retval  BLE_ERR_NOT_YET_READY(0x0012) When this function was called, pairing has not yet started.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReplyNumComp(uint16_t conn_hdl, uint8_t response);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_NotifyKeyPress(uint16_t conn_hdl, uint8_t key_press)
 * @brief   Notify the input key type which a remote device inputs in the passkey entry.
 * @details This function notifies the input key type to the remote device in passkey entry.
 *          The result is returned from this API.
 * @param[in] conn_hdl  Connection handle identifying the remote device to which the key notification is sent.
 * @param[in] key_press Input key type.
 *               |              macro                         |           description                 |
 *               |:------------------------------------------ |:------------------------------------- |
 *               | BLE_GAP_LESC_PASSKEY_ENTRY_STARTED(0x00)   | Notify that passkey entry started.    |
 *               | BLE_GAP_LESC_PASSKEY_DIGIT_ENTERED(0x01)   | Notify that passkey digit entered.    |
 *               | BLE_GAP_LESC_PASSKEY_DIGIT_ERASED(0x02)    | Notify that passkey digit erased.     |
 *               | BLE_GAP_LESC_PASSKEY_CLEARED(0x03)         | Notify that passkey cleared.          |
 *               | BLE_GAP_LESC_PASSKEY_ENTRY_COMPLETED(0x04) | Notify that passkey entry completed.  |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) key_press parameter is out of range.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 * @retval  BLE_ERR_NOT_YET_READY(0x0012) When this function was called, pairing has not yet started.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_NotifyKeyPress(uint16_t conn_hdl, uint8_t key_press);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_GetDevSecInfo(uint16_t conn_hdl, st_ble_gap_auth_info_t * p_sec_info)
 * @brief   Get the security information about the remote device.
 * @details This function gets the parameters which has been negotiated with the remote device in pairing.
 *          The parameters can be retrieved after pairing.
 *          The result is returned by p_sec_info.
 * @param[in] conn_hdl  Connection handle identifying the remote device whose bonding information is retrieved.
 * @param[in] p_sec_info  Return the security information which has been negotiated in pairing.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_sec_info is specified as NULL.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The remote device bonding information has not been set to host stack.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_GetDevSecInfo(uint16_t conn_hdl, st_ble_gap_auth_info_t * p_sec_info);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReplyExKeyInfoReq(uint16_t conn_hdl)
 * @brief   Distribute the keys of local device.
 * @details When key exchange request is notified by BLE_GAP_EVENT_EX_KEY_REQ event at pairing,
 *          keys of the local device are distributed.
 *          The result is returned from this API.
 * @param[in] conn_hdl  Connection handle identifying the remote device to which the key is distributed.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 * @retval  BLE_ERR_NOT_YET_READY(0x0012) When this function was called, pairing has not yet started.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReplyExKeyInfoReq(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetRemOobData( st_ble_dev_addr_t * p_addr,
 *                                           uint8_t oob_data_flag,
 *                                           st_ble_gap_oob_data_t * p_oob
 *                                         )
 * @brief   Set the oob data from a remote device.
 * @details This function registers the OOB data received from a remote device.
 *          When oob_data_flag indicates that the OOB data has been received,
 *          the setting regarding OOB data is reflected in pairing.
 *          In order to do OOB pairing, set the OOB data received from the remote device before pairing.
 *          The result is returned from this API.
 * @param[in] p_addr The remote device address.
 * @param[in] oob_data_flag This parameter indicates whether the local device has received the OOB data
 *                          from the remote device or not.
 *               |              macro                |           description                                   |
 *               |:--------------------------------- |:------------------------------------------------------- |
 *               | BLE_GAP_OOB_DATA_NOT_PRESENT(0x00)| Reply that No OOB data has been received when pairing.  |
 *               | BLE_GAP_OOB_DATA_PRESENT(0x01)    | Reply that the OOB data has been received when pairing. |
 * @param[in] p_oob The OOB data received from the remote device.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The reason for this error is as follows.
 *                                      - p_addr is specified as NULL.
 *                                      - oob_data_flag is BLE_GAP_OOB_DATA_PRESENT and p_oob is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) oob_data_flag is out of range.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) There is no room to register the OOB data received from a remote device.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetRemOobData(st_ble_dev_addr_t * p_addr, uint8_t oob_data_flag, st_ble_gap_oob_data_t * p_oob);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_CreateScOobData(void)
 * @brief   Create data for oob in secure connection.
 * @details This function generates the OOB data distributed to a remote device in Secure Connections.
 *          The result of this API call is notified in BLE_GAP_EVENT_SC_OOB_CREATE_COMP event.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The reason for this error is as follows:
 *                                        - This function was called in pairing.
 *                                        - The task for host stack is not running.
 * @retval  BLE_ERR_ALREADY_IN_PROGRESS(0x000A) This function was called in creating OOB data.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_CreateScOobData(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_SetBondInfo(st_ble_gap_bond_info_t * p_bond_info,
 *                                        uint8_t device_num,
 *                                        uint8_t * p_set_num
 *                                       )
 * @brief   Set the bonding information stored in non-volatile memory to the host stack.
 * @details Set the bonding information of the remote device in the host stack.
 *          After power re-supply, when the remote device bonding information stored in non-volatile memory is
 *          set to host stack, this function is used.
 *          Host stack can be set the number specified by the device_num parameter of bonding information.
 * @param[in] p_bond_info An array of bonding information. The number of elements is specified by device_num.
 * @param[in] device_num  The number of the devices of which host stack registers bonding information.
 * @param[in] p_set_num   The number of the devices whose bonding information was registered in host stack.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_bond_info or p_set_num is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) device_num is out of range.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) Host stack already has the maximum number of bonding information.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_SetBondInfo(st_ble_gap_bond_info_t * p_bond_info, uint8_t device_num, uint8_t * p_set_num);

/******************************************************************************************************************//**
 * @fn void R_BLE_GAP_DeleteBondInfo(int32_t local,
 *                                        int32_t remote,
 *                                        st_ble_dev_addr_t * p_addr,
 *                                        ble_gap_del_bond_cb_t gap_del_bond_cb)
 * @brief This function deletes the bonding information in Host Stack.\n
 *          When a function for deleting the bonding information stored in non-volatile area is registered by the
 *          gap_del_bond_cb parameter, it is deleted as well as the bonding information in Host Stack.
 *
 * @param[in] local The type of the local bonding information to be deleted.
 *               |              macro                |           description                                   |
 *               |:--------------------------------- |:------------------------------------------------------- |
 *               | BLE_GAP_SEC_DEL_LOC_NONE(0x00)    | Delete no local keys.                                   |
 *               | BLE_GAP_SEC_DEL_LOC_IRK(0x01)     | Delete local IRK and identity address.                  |
 *               | BLE_GAP_SEC_DEL_LOC_CSRK(0x02)    | Delete local CSRK.                                      |
 *               | BLE_GAP_SEC_DEL_LOC_ALL(0x03)     | Delete all local keys.                                  |
 * @param[in] remote The type of the remote bonding information to be deleted.
 *               |              macro                |           description                                   |
 *               |:--------------------------------- |:------------------------------------------------------- |
 *               | BLE_GAP_SEC_DEL_REM_NONE(0x00)    | Delete no remote device keys.                           |
 *               | BLE_GAP_SEC_DEL_REM_SA(0x01)      | Delete the keys specified by the p_addr parameter.      |
 *               | BLE_GAP_SEC_DEL_REM_NOT_CONN(0x02)| Delete keys of not connected remote devices.            |
 *               | BLE_GAP_SEC_DEL_REM_ALL(0x03)     | Delete all remote device keys.                          |
 *               \n\n
 * @param[in] p_addr p_addr is specified as the address of the remote device whose keys are deleted
 *                   when the rem_info parameter is set to @ref BLE_GAP_SEC_DEL_REM_SA(0x01).
 *                   \n\n
 * @param[in] gap_del_bond_cb This parameter is a callback function which deletes the bonding information stored
 *                            in non-volatile area. \n After deleting the bonding information stored in Host Stack,
 *                            the callback function is called. If no bonding information is stored in
 *                            non-volatile area, specify the parameter as NULL.
 * @retval  none
 **********************************************************************************************************************/
void R_BLE_GAP_DeleteBondInfo(int32_t               local,
                              int32_t               remote,
                              st_ble_dev_addr_t   * p_addr,
                              ble_gap_del_bond_cb_t gap_del_bond_cb);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GAP_ReplyLtkReq(uint16_t conn_hdl,
 *                                        uint16_t ediv,
 *                                        uint8_t * p_peer_rand,
 *                                        uint8_t response
 *                                       )
 * @brief   Reply the LTK request from a remote device.
 * @details This function replies to the LTK request in BLE_GAP_EVENT_LTK_REQ event from a remote device.
 *          The result of the LTK reply is returned in BLE_GAP_EVENT_LTK_RSP_COMP event.
 *          When the link encryption has completed, BLE_GAP_EVENT_ENC_CHG event is notified.
 * @param[in] conn_hdl  Connection handle identifying the remote device which sent the LTK request.
 * @param[in] ediv  Ediv notified in BLE_GAP_EVENT_LTK_REQ event.
 * @param[in] p_peer_rand  Rand notified in BLE_GAP_EVENT_LTK_REQ event.
 * @param[in] response  Response to the LTK request.
 *                      If "BLE_GAP_LTK_REQ_ACCEPT" is specified,
 *                      when no LTK has been exchanged in pairing, reject the LTK request.
 *                      |              macro            |           description              |
 *                      |:----------------------------- |:---------------------------------- |
 *                      | BLE_GAP_LTK_REQ_ACCEPT(0x00)  | Reply for the LTK request.         |
 *                      | BLE_GAP_LTK_REQ_DENY(0x01)    | Reject the LTK request.            |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) p_peer_rand is specified as NULL in case of legacy pairing.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) response is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GAP_ReplyLtkReq(uint16_t conn_hdl, uint16_t ediv, uint8_t * p_peer_rand, uint8_t response);

/*@}*/

/* ========================================== GATT Common API Declarations ========================================== */

/** @defgroup GATT_COMMON_API GATT_COMMON
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup GATT_COMMON_API
 * @fn ble_status_t R_BLE_GATT_GetMtu(uint16_t conn_hdl, uint16_t * p_mtu)
 * @brief   This function gets the current MTU used in GATT communication.
 * @details Both GATT server and GATT Client can use this function. \n
 *          The result of this API call is returned by a return value.
 * @param[in] conn_hdl Connection handle identifying the GATT Server or the GATT Client.
 * @param[in] p_mtu The Current MTU. Before MTU exchange, this parameter is 23 bytes. \n
 *                  After MTU exchange, this parameter is the negotiated MTU.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The mtu parameter is NULL.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server or the GATT Client specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATT_GetMtu(uint16_t conn_hdl, uint16_t * p_mtu);

/*@}*/

/* ========================================== GATT Server API Declarations ========================================== */

/** @defgroup GATT_SERVER_API GATT_SERVER
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup GATT_SERVER_API
 * @fn ble_status_t R_BLE_GATTS_Init(uint8_t cb_num)
 * @brief   This function initializes the GATT Server and registers the number of the callbacks for GATT Server event.
 * @details Specify the cb_num parameter to a value between 1 and BLE_GATTS_MAX_CB.\n
 *          R_BLE_GATTS_RegisterCb() registers the callback.\n
 *          The result of this API call is returned by a return value.
 * @param[in] cb_num The number of callbacks to be registered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The cb_num parameter is out of range.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_Init(uint8_t cb_num);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_SetDbInst(st_ble_gatts_db_cfg_t * p_db_inst)
 * @brief   This function sets GATT Database to host stack.
 * @details The result of this API call is returned by a return value.
 * @param[in] p_db_inst GATT Database to be set.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The reason for this error is as follows.
 *                                      - The db_inst parameter is specified as NULL.
 *                                      - The array in the db_inst is specified as NULL.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_SetDbInst(st_ble_gatts_db_cfg_t * p_db_inst);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_RegisterCb(ble_gatts_app_cb_t cb, uint8_t priority)
 * @brief   This function registers a callback for GATT Server event.
 * @details The number of the callback that may be registered by this function is the value specified
 *          by R_BLE_GATTS_Init().\n
 *          The result of this API call is returned by a return value.
 * @param[in] cb Callback function for GATT Server event.
 * @param[in] priority  The priority of the callback function.\n
 *                      Valid range is 1 <= priority <= BLE_GATTS_MAX_CB.\n
 *                      A lower priority number means a higher priority level.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The cb parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The priority parameter is out of range.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) Host stack has already registered the maximum number of callbacks.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_RegisterCb(ble_gatts_app_cb_t cb, uint8_t priority);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_DeregisterCb(ble_gatts_app_cb_t cb)
 * @brief   This function deregisters the callback function for GATT Server event.
 * @details The result of this API call is returned by a return value.
 * @param[in] cb The callback function to be deregistered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The cb parameter is specified as NULL.
 * @retval  BLE_ERR_NOT_FOUND(0x000D) The callback has not been registered.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_DeregisterCb(ble_gatts_app_cb_t cb);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_Notification(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ntf_data)
 * @brief   This function sends a notification of an attribute's value.
 * @details The maximum length of the attribute value that can be sent with notification is MTU-3.\n
 *          The result of this API call is returned by a return value.
 * @param[in] conn_hdl Connection handle identifying the remote device to be sent the notification.
 * @param[in] p_ntf_data The attribute value to send.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_ntf_data parameter or the value field in the value field in
 *                                      the p_ntf_data parameter is NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The value_len field in the value field in the p_ntf_data parameter is 0
 *                                      or the attr_hdl field in the p_ntf_data parameters is 0.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) This function was called while processing other request.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_Notification(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ntf_data);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_Indication(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ind_data)
 * @brief   This function sends a indication of an attribute's value.
 * @details  The maximum length of the attribute value that can be sent with indication is MTU-3.\n
 *           The result of this API call is returned by a return value.\n
 *           The remote device that receives a indication sends a confirmation.\n
 *           BLE_GATTS_EVENT_HDL_VAL_CNF event notifies the application layer that the confirmation has been received.
 * @param[in] conn_hdl Connection handle identifying the remote device to be sent the indication.
 * @param[in] p_ind_data The attribute value to send.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_ind_data parameter or the value field in the value field in
 *                                      the p_ind_data parameter is NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The value_len field in the value field in the p_ind_data parameter is 0
 *                                      or the attr_hdl field in the p_ind_data parameters is 0.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) This function was called while processing other request.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_Indication(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ind_data);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_GetAttr(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
 * @brief   This function gets a attribute value from the GATT Database.
 * @details  The result of this API call is returned by a return value.
 * @param[in] conn_hdl If the attribute value that has information about the remote device is retrieved,
 *                     specify the remote device with the conn_hdl parameter.
 *                     When information about the remote device is not required,
 *                     set the conn_hdl parameter to BLE_GAP_INVALID_CONN_HDL.
 * @param[in] attr_hdl The attribute handle of the attribute value to be retrieved.
 * @param[out] p_value  The attribute value to be retrieved.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001)  The p_value parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The attr_hdl parameter is 0 or larger than the last attribute handle
 *                                      of GATT Database.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The attribute is not in a state to be read.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) The attribute cannot be read.
 * @retval  BLE_ERR_NOT_FOUND(0x000D) The attribute specified by the attr_hdl parameter is not belonging to
 *                                    any services or characteristics.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by the conn_hdl parameter was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_GetAttr(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_SetAttr(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
 * @brief   This function sets an attribute value to the GATT Database.
 * @details  The result of this API call is returned by a return value.
 * @param[in] conn_hdl If the attribute value that has information about the remote device is retrieved,
 *                     specify the remote device with the conn_hdl parameter.
 *                     When information about the remote device is not required,
 *                     set the conn_hdl parameter to BLE_GAP_INVALID_CONN_HDL.
 * @param[in] attr_hdl The attribute handle of the attribute value to be set.
 * @param[in] p_value  The attribute value to be set.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_value parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_DATA(0x0002) The write size is larger than the length of the attribute value.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The attr_hdl parameter is 0 or larger than the last attribute handle
 *                                      of GATT Database.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The attribute is not in a state to be written.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) The attribute cannot be written.
 * @retval  BLE_ERR_NOT_FOUND(0x000D) The attribute specified by the attr_hdl parameter is not belonging to
 *                                    any services or characteristics.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by the conn_hdl parameter was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_SetAttr(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_SendErrRsp(uint16_t error_code)
 * @brief   This function sends an error response to a remote device.
 * @details  The result is returned from the API.\n
 *           The error code specified in the callback is notified as Error Response to the remote device.\n
 *           The result of this API call is returned by a return value.
 * @param[in] error_code The error codes to be notified the client.\n
 *                       It is a bitwise OR of GATT Error Group ID : 0x3000 and the following error codes defined
 *                       in Core Spec and Core Spec Supplement.
 *                      <table>
 *                          <tr>
 *                              <th>Error Code</th>
 *                              <th>description</th>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INVALID_HANDLE(0x3001)</td>
 *                              <td>Invalid attribute handle</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_READ_NOT_PERMITTED(0x3002)</td>
 *                              <td>The attribute cannot be read.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_WRITE_NOT_PERMITTED(0x3003)</td>
 *                              <td>The attribute cannot be written.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INVALID_PDU(0x3004)</td>
 *                              <td>Invalid PDU.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INSUFFICIENT_AUTHENTICATION(0x3005)</td>
 *                              <td>The authentication to access the attribute is insufficient.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_REQUEST_NOT_SUPPORTED(0x3006)</td>
 *                              <td>The request is not supported.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INVALID_OFFSET(0x3007)</td>
 *                              <td>The specified offset is larger than the length of the attribute value.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INSUFFICIENT_AUTHORIZATION(0x3008)</td>
 *                              <td>Authorization is required to access the attribute.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_PREPARE_WRITE_QUEUE_FULL(0x3009)</td>
 *                              <td>The Write Queue in the GATT Server is full.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_ATTRIBUTE_NOT_FOUND(0x300A)</td>
 *                              <td>The specified attribute is not found.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_ATTRIBUTE_NOT_LONG(0x300B)</td>
 *                              <td>The attribute cannot be read by Read Blob Request.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INSUFFICIENT_ENC_KEY_SIZE(0x300C)</td>
 *                              <td>The Encryption Key Size is insufficient.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INVALID_ATTRIBUTE_LEN(0x300D)</td>
 *                              <td>The length of the specified attribute is invalid.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_UNLIKELY_ERROR(0x300E)</td>
 *                              <td>Because an error has occurred,  the process cannot be advanced.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INSUFFICIENT_ENCRYPTION(0x300F)</td>
 *                              <td>Encryption is required to access the attribute.
 *                              </td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_UNSUPPORTED_GROUP_TYPE(0x3010)</td>
 *                              <td>The type of the specified attribute is not supported.
 *                              </td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_INSUFFICIENT_RESOURCES(0x3011)</td>
 *                              <td>The resource to complete the request is insufficient.
 *                              </td>
 *                          </tr>
 *                          <tr>
 *                              <td>0x3080 - 0x309F</td>
 *                              <td>Application Error.
 *                              The upper layer defines the error codes.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>0x30E0 - 0x30FF</td>
 *                              <td>
 *                                  The error code defined in Common Profile and Service Error
 *                                  Core Specification Supplement(CSS).<BR/>
 *                                  CSS ver.7 defines the error codes from 0x30FC to 0x30FF.
 *                              </td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_WRITE_REQ_REJECTED(0x30FC)</td>
 *                              <td>The Write Request has not been completed due to the reason other than Permission.
 *                              </td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_CCCD_IMPROPERLY_CFG(0x30FD)</td>
 *                              <td>The CCCD is set to be invalid.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_PROC_ALREADY_IN_PROGRESS(0x30FE)</td>
 *                              <td>The request is now in progress.</td>
 *                          </tr>
 *                          <tr>
 *                              <td>BLE_ERR_GATT_OUT_OF_RANGE(0x30FF)</td>
 *                              <td>The attribute value is out of range.</td>
 *                          </tr>
 *                      </table>
 *
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The Group ID of the error_code parameter is not 0x3000, or it is 0x3000.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other error response,this function was called.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_SendErrRsp(uint16_t error_code);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_RspExMtu(uint16_t conn_hdl, uint16_t mtu)
 * @brief   This function replies to a MTU Exchange Request from a remote device.
 * @details  BLE_GATTS_EVENT_EX_MTU_REQ event notifies the application layer
 *           that a MTU Exchange Request has been received.
 *           Therefore when the callback has received the event, call this function.\n
 *           The new MTU is the minimum of the mtu parameter specified by this function
 *           and the mtu field in BLE_GATTS_EVENT_EX_MTU_REQ event.\n
 *           Default MTU size is 23 bytes.\n
 *           The result of this API call is returned by a return value.\n
 * @param[in] conn_hdl Connection handle identifying the remote device to be sent MTU Exchange Response.
 * @param[in] mtu The maximum size(in bytes) of the GATT PDU that GATT Server can receive.\n
 *                Valid range is 23 <= mtu <= 247.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The mtu parameter is out of range.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) This function was called while processing other request.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_RspExMtu(uint16_t conn_hdl, uint16_t mtu);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTS_SetPrepareQueue(st_ble_gatt_pre_queue_t * p_pre_queues, uint8_t queue_num)
 * @brief   Register prepare queue and buffer in Host Stack.
 * @details  This function registers the prepare queue and buffer for long chracteristic write and reliable writes.
 *           The result of this API call is returned by a return value.\n
 * @param[in] p_pre_queues The prepare write queues to be registered.
 * @param[in] queue_num The number of prepare write queues to be registered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_pre_queue parameter is specified as NULL.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTS_SetPrepareQueue(st_ble_gatt_pre_queue_t * p_pre_queues, uint8_t queue_num);

/*@}*/

/* ========================================== GATT Client API Declarations ========================================== */

/** @defgroup GATT_CLIENT_API GATT_CLIENT
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup GATT_CLIENT_API
 * @fn ble_status_t R_BLE_GATTC_Init(uint8_t cb_num)
 * @brief   This function initializes the GATT Client and registers the number of the callbacks for GATT Client event.
 * @details Specify the cb_num parameter to a value between 1 and BLE_GATTC_MAX_CB.\n
 *          R_BLE_GATTC_RegisterCb() registers the callback.\n
 *          The result of this API call is returned by a return value.
 * @param[in] cb_num The number of callbacks to be registered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The cb_num parameter is out of range.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_Init(uint8_t cb_num);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_RegisterCb(ble_gattc_app_cb_t cb, uint8_t priority)
 * @brief   This function registers a callback function for GATT Client event.
 * @details The number of the callback that may be registered by this function is the value specified
 *          by R_BLE_GATTC_Init().\n
 *          The result of this API call is returned by a return value.
 * @param[in] cb Callback function for GATT Client event.
 * @param[in] priority  The priority of the callback function.\n
 *                      Valid range is 1 <= priority <= BLE_GATTC_MAX_CB.\n
 *                      A lower priority number means a higher priority level.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The cb parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The priority parameter is out of range.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) Host stack has already registered the maximum number of callbacks.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_RegisterCb(ble_gattc_app_cb_t cb, uint8_t priority);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DeregisterCb(ble_gattc_app_cb_t cb)
 * @brief   This function deregisters the callback function for GATT Client event.
 * @details The result of this API call is returned by a return value.
 * @param[in] cb The callback function to be deregistered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The cb parameter is specified as NULL.
 * @retval  BLE_ERR_NOT_FOUND(0x000D) The callback has not been registered.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DeregisterCb(ble_gattc_app_cb_t cb);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_ReqExMtu(uint16_t conn_hdl, uint16_t mtu)
 * @brief   This function sends a MTU Exchange Request PDU to a GATT Server in order to change the current MTU.
 * @details  MTU Exchange Response is notified by BLE_GATTC_EVENT_EX_MTU_RSP event.\n
 *           The new MTU is the minimum value of the mtu parameter specified by this function and
 *           the mtu field in BLE_GATTC_EVENT_EX_MTU_RSP event.
 *           Default MTU size is 23 bytes.\n
 *           The result of this API call is returned by a return value.\n
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be sent.
 * @param[in] mtu  The maximum size(in bytes) of the GATT PDU that GATT Client can receive. \n
 *                 Valid range is 23 <= mtu <= 247.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The mtu parameter is out of range.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_ReqExMtu(uint16_t conn_hdl, uint16_t mtu);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DiscAllPrimServ(uint16_t conn_hdl)
 * @brief   This function discovers all Primary Services in a GATT Server.
 * @details  When 16-bit UUID Primary Service has been discovered, BLE_GATTC_EVENT_PRIM_SERV_16_DISC_IND event
 *           is notified to the application layer.\n
 *           When 128-bit UUID Primary Service has been discovered, BLE_GATTC_EVENT_PRIM_SERV_128_DISC_IND event
 *           is notified to the application layer.\n
 *           When the Primary Service discovery has been completed, BLE_GATTC_EVENT_ALL_PRIM_SERV_DISC_COMP event
 *           is notified to the application layer.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be discovered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) This function was called while processing other request.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DiscAllPrimServ(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DiscPrimServ(uint16_t conn_hdl, uint8_t * p_uuid, uint8_t uuid_type)
 * @brief   This function discovers Primary Service specified by p_uuid in a GATT Server.
 * @details  When Primary Service whose uuid is the same as the specified uuid has been discovered,
 *           BLE_GATTC_EVENT_PRIM_SERV_16_DISC_IND event or BLE_GATTC_EVENT_PRIM_SERV_128_DISC_IND event is
 *           notified to the application layer.\n
 *           When the Primary Service discovery has been completed, BLE_GATTC_EVENT_PRIM_SERV_DISC_COMP event
 *           is notified to the application layer.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be discovered.
 * @param[in] p_uuid UUID of Primary Service to be discovered.
 * @param[in] uuid_type UUID type(16-bit or 128-bit).
 *                      |              macro                 | description      |
 *                      |:---------------------------------- |:---------------- |
 *                      | BLE_GATT_16_BIT_UUID_FORMAT(0x01)  | 16-bit UUID      |
 *                      | BLE_GATT_128_BIT_UUID_FORMAT(0x02) | 128-bit UUID     |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_uuid parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The uuid_type parameter is out of range.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DiscPrimServ(uint16_t conn_hdl, uint8_t * p_uuid, uint8_t uuid_type);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DiscAllSecondServ( uint16_t conn_hdl)
 * @brief   This function discovers all Secondary Services in a GATT Server.
 * @details  When a 16-bit UUID Secondary Service has been discovered, BLE_GATTC_EVENT_SECOND_SERV_16_DISC_IND event
 *           is notified to the application layer.\n
 *           When a 128-bit UUID Secondary Service has been discovered, BLE_GATTC_EVENT_SECOND_SERV_128_DISC_IND event
 *           is notified to the application layer.\n
 *           When the Secondary Service discovery has been completed, BLE_GATTC_EVENT_ALL_SECOND_SERV_DISC_COMP event
 *           is notified to the application layer.\n
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be discovered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DiscAllSecondServ(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DiscIncServ(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
 * @brief   This function discovers Included Services within the specified attribute handle range in a GATT Server.
 * @details  When Included Service that includes 16-bit UUID Service has been discovered,
 *           BLE_GATTC_EVENT_INC_SERV_16_DISC_IND event is notified to the application layer.\n
 *           When Included Service that includes 128-bit UUID Service has been discovered,
 *           BLE_GATTC_EVENT_INC_SERV_128_DISC_IND event is notified to the application layer.\n
 *           When the Included Service discovery has been completed,
 *           BLE_GATTC_EVENT_INC_SERV_DISC_COMP event is notified to the application layer.\n
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be discovered.
 * @param[in] p_range Retrieval range of Included Service.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_range parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DiscIncServ(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DiscAllChar(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
 * @brief   This function discovers Characteristic within the specified attribute handle range in a GATT Server.
 * @details  When 16-bit UUID Characteristic has been discovered, BLE_GATTC_EVENT_CHAR_16_DISC_IND event
 *           is notified to the application layer.\n
 *           When 128-bit UUID Characteristic has been discovered, BLE_GATTC_EVENT_CHAR_128_DISC_IND event
 *           is notified to the application layer.\n
 *           When the Characteristic discovery has been completed, BLE_GATTC_EVENT_ALL_CHAR_DISC_COMP event
 *           is notified to the application layer.\n
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be discovered.
 * @param[in] p_range Retrieval range of Characteristic.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_range parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DiscAllChar(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DiscCharByUuid(uint16_t conn_hdl,
 *                                             uint8_t * p_uuid,
 *                                             uint8_t uuid_type,
 *                                             st_ble_gatt_hdl_range_t * p_range
 *                                            )
 * @brief   This function discovers Characteristic specified by uuid within the specified attribute handle range
 *          in a GATT Server.
 * @details  When 16-bit UUID Characteristic has been discovered, BLE_GATTC_EVENT_CHAR_16_DISC_IND event
 *           is notified to the application layer.\n
 *           When 128-bit UUID Characteristic has been discovered, BLE_GATTC_EVENT_CHAR_128_DISC_IND event
 *           is notified to the application layer.\n
 *           When the Characteristic discovery has been completed, BLE_GATTC_EVENT_CHAR_DISC_COMP event
 *           is notified to the application layer.\n
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be discovered.
 * @param[in] p_uuid UUID of Characteristic to be discovered.
 * @param[in] uuid_type UUID type of Characteristic to be discovered.
 *                      |              macro                 |           description                 |
 *                      |:---------------------------------- |:------------------------------------- |
 *                      | BLE_GATT_16_BIT_UUID_FORMAT(0x01)  | The p_uuid parameter is 16-bit UUID.  |
 *                      | BLE_GATT_128_BIT_UUID_FORMAT(0x02) | The p_uuid parameter is 128-bit UUID. |
 * @param[in] p_range Retrieval range of Characteristic.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_uuid parameter or the p_range parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The uuid_type parameter is out of range.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DiscCharByUuid(uint16_t                  conn_hdl,
                                        uint8_t                 * p_uuid,
                                        uint8_t                   uuid_type,
                                        st_ble_gatt_hdl_range_t * p_range);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_DiscAllCharDesc(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
 * @brief   This function discovers Characteristic Descriptor within the specified attribute handle range
 *          in a GATT Server.
 * @details When 16-bit UUID Characteristic Descriptor has been discovered, BLE_GATTC_EVENT_CHAR_DESC_16_DISC_IND
 *          event is notified to the application layer.
 *          When 128-bit UUID Characteristic Descriptor has been discovered, BLE_GATTC_EVENT_CHAR_DESC_128_DISC_IND
 *          event is notified to the application layer.
 *          When the Characteristic Descriptor discovery has been completed, BLE_GATTC_EVENT_ALL_CHAR_DESC_DISC_COMP
 *          event is notified to the application layer.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be discovered.
 * @param[in] p_range Retrieval range of Characteristic Descriptor.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_range parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_DiscAllCharDesc(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_ReadChar(uint16_t conn_hdl, uint16_t value_hdl)
 * @brief   This function reads a Characteristic/Characteristic Descriptor in a GATT Server.
 * @details The result of the read is notified in BLE_GATTC_EVENT_CHAR_READ_RSP event.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be read.
 * @param[in] value_hdl Value handle of the Characteristic/Characteristic Descriptor to be read.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) 0 is specified in the value_hdl parameter.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_ReadChar(uint16_t conn_hdl, uint16_t value_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_ReadCharUsingUuid(uint16_t conn_hdl,
 *                                             uint8_t * p_uuid,
 *                                             uint8_t uuid_type,
 *                                             st_ble_gatt_hdl_range_t * p_range
 *                                            );
 * @brief   This function reads a Characteristic in a GATT Server using a specified UUID.
 * @details  The result of the read is notified in BLE_GATTC_EVENT_CHAR_READ_BY_UUID_RSP event.
 * @param[in] conn_hdl Connection handle that identifies Characteristic to be read to GATT Server.
 * @param[in] p_uuid UUID of the Characteristic to be read.
 * @param[in] uuid_type  UUID type of the Characteristic to be read.
 *                      |              macro                 |           description                 |
 *                      |:---------------------------------- |:------------------------------------- |
 *                      | BLE_GATT_16_BIT_UUID_FORMAT(0x01)  | The p_uuid parameter is 16-bit UUID.  |
 *                      | BLE_GATT_128_BIT_UUID_FORMAT(0x02) | The p_uuid parameter is 128-bit UUID. |
 * @param[in] p_range Retrieval range of Characteristic.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_uuid parameter or the p_range parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The uuid_type parameter is out of range.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_ReadCharUsingUuid(uint16_t                  conn_hdl,
                                           uint8_t                 * p_uuid,
                                           uint8_t                   uuid_type,
                                           st_ble_gatt_hdl_range_t * p_range);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_ReadLongChar(uint16_t conn_hdl, uint16_t value_hdl, uint16_t offset)
 * @brief   This function reads a Long Characteristic in a GATT Server.
 * @details The contents of the Long Characteristic that has been read is notified every MTU-1 bytes to
 *          the application layer by BLE_GATTC_EVENT_CHAR_READ_RSP event.\n
 *          When all of the contents has been received in GATT Client, BLE_GATTC_EVENT_LONG_CHAR_READ_COMP event
 *          is notified to the application layer.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be read.
 * @param[in] value_hdl Value handle of the Long Characteristic to be read.
 * @param[in] offset Offset that indicates the location to be read.\n
 *                   Normally, set 0 to this parameter.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) 0 is specified in the value_hdl parameter.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_ReadLongChar(uint16_t conn_hdl, uint16_t value_hdl, uint16_t offset);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_ReadMultiChar(uint16_t conn_hdl, st_ble_gattc_rd_multi_req_param_t * p_list)
 * @brief   This function reads multiple Characteristics in a GATT Server.
 * @details The contents of the multiple Characteristics that has been read is notified to the application layer
 *          by BLE_GATTC_EVENT_MULTI_CHAR_READ_RSP event.
 * @param[in] conn_hdl Connection handle that identifies Characteristic to be read to GATT Server.
 * @param[in] p_list List of Value Handles that point the Characteristics to be read.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_list parameter or the p_hdl_list field in the p_list parameter is
 *                                      specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) 0 is specified in the list_count field in the p_list parameter.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_ReadMultiChar(uint16_t conn_hdl, st_ble_gattc_rd_multi_req_param_t * p_list);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_WriteCharWithoutRsp(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
 * @brief   This function writes a Characteristic in a GATT Server without response.
 * @details The result is returned from the API.
 * @param[in] conn_hdl Connection handle that identifies Characteristic to be read to GATT Server.
 * @param[in] p_write_data Value to be written to the Characteristic.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_write_data parameter or the p_value field in the value field
 *                                      in the p_write_data parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *                      - 0 is specified in the value_len field in the p_value field in the p_write_data parameter.
 *                      - 0 is specified in the attr_hdl field in the p_write_data parameter.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_WriteCharWithoutRsp(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_SignedWriteChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
 * @brief   This function writes Signed Data to a Characteristic in a GATT Server without response.
 * @details The result of this API call is returned by a return value.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be written.
 * @param[in] p_write_data Signed Data to be written to the Characteristic.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_write_data parameter or the p_value field in the value field
 *                                      in the p_write_data parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *                      - 0 is specified in the value_len field in the value field in the p_write_data parameter.
 *                      - 0 is specified in the attr_hdl field in the p_write_data parameter.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function or Signed Data.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_SignedWriteChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_WriteChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
 * @brief   This function writes a Characteristic in a GATT Server.
 * @details The result of the write is notified in BLE_GATTC_EVENT_CHAR_WRITE_RSP event.
 * @param[in] conn_hdl  Connection handle identifying the GATT Server to be written.
 * @param[in] p_write_data Value to be written to the Characteristic.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_write_data parameter or the p_value field in the value field
 *                                      in the p_write_data parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *                      - 0 is specified in the value_len field in the value field in the p_write_data parameter.
 *                      - 0 is specified in the attr_hdl field in the p_write_data parameter.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_WriteChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_WriteLongChar(uint16_t conn_hdl,
 *                                            st_ble_gatt_hdl_value_pair_t * p_write_data,
 *                                            uint16_t offset
 *                                            )
 * @brief   This function writes a Long Characteristic in a GATT Server.
 * @details The result of a write that has been done every segmentation is notified to the application layer
 *          in BLE_GATTC_EVENT_CHAR_PART_WRITE_RSP event.\n
 *          The maximum writable size to a Long Characteristic with this function is 512 bytes.\n
 *          When all of the contents has been written to the Long Characteristic, BLE_GATTC_EVENT_LONG_CHAR_WRITE_COMP
 *          event is notified to the application layer.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be written.
 * @param[in] p_write_data Value to be written to the Long Characteristic.
 * @param[in] offset Offset that indicates the location to be written.
 *                   Normally, set 0 to this parameter.\n
 *                   If this parameter sets to a value other than 0, adjust the offset parameter and
 *                   the length of the value to be written not to exceed the length of the Long Characteristic.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_write_data parameter or the p_value field in the value field in
 *                                      the p_write_data parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *            - The value_len field in the value field in the p_write_data parameter is 0.
 *            - The sum of the value_len field in the value field in the p_write_data parameter
 *              and the offset parameter larger than 512.
 *            - The attr_hdl field in the p_write_data parameter is 0.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_WriteLongChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data, uint16_t offset);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_ReliableWrites(uint16_t conn_hdl,
 *                                             st_ble_gattc_reliable_writes_char_pair_t * p_char_pair,
 *                                             uint8_t pair_num,
 *                                             uint8_t auto_flag
 *                                            )
 * @brief   This function performs the Reliable Writes procedure described in GATT Specification.
 * @details When the data written to the Characteristic has been transmitted, BLE_GATTC_EVENT_CHAR_PART_WRITE_RSP
 *          event is notified to the application layer.\n
 *          If the data included in the event is different from the data that GATT Client has sent,
 *          host stack automatically cancels the Reliable Writes.\n
 *          After all of the contents has been sent to the GATT Server, if the auto_flag parameter has been set to
 *          BLE_GATTC_EXEC_AUTO, the GATT Server automatically writes the data to the Characteristic.\n
 *          If the auto_flag parameter has been set to BLE_GATTC_EXEC_NOT_AUTO,  BLE_GATTC_EVENT_RELIABLE_WRITES_TX_COMP
 *          event notifies the application layer in GATT Client that all of the contents has been sent to
 *          the GATT Server. Then GATT Client requests for writing the data to the Characteristic to the GATT Server
 *          with R_BLE_GATTC_ExecWrite().\n
 *          When the write has been done, BLE_GATTC_EVENT_RELIABLE_WRITES_COMP event is notified to
 *          the application layer.
 * @param[in] conn_hdl Connection handle identifying the GATT Server to be written.
 * @param[in] p_char_pair Pair of Characteristic Value and Characteristic Value Handle identifying the Characteristic
 *                        to be written by Reliable Writes.
 * @param[in] pair_num The number of the pairs specified by the p_char_pair parameter.\n
 *                   Valid range is 0 < pair_num <= BLE_GATTC_RELIABLE_WRITES_MAX_CHAR_PAIR.
 * @param[in] auto_flag  The flag that indicates whether auto execution or not.
 *        |              macro             |   description       |
 *        |:------------------------------ |:------------------- |
 *        | BLE_GATTC_EXEC_AUTO(0x01)      | Auto execution.     |
 *        | BLE_GATTC_EXEC_NOT_AUTO (0x02) | Not auto execution. |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The reason for this error is as follows:
 *       - The p_char_pair parameter is specified as NULL.
 *       - The p_value field in the value field in the write_data field in the p_char_pair parameter
 *         is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The reason for this error is as follows:
 *       - The pair_num parameter or the auto_flag parameter is out of range.
 *       - The value_len field in the value field in the write_data field in the p_char_pair parameter is 0.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) While processing other request, this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function or
 *                                           to store the temporary write data.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_ReliableWrites(uint16_t                                   conn_hdl,
                                        st_ble_gattc_reliable_writes_char_pair_t * p_char_pair,
                                        uint8_t                                    pair_num,
                                        uint8_t                                    auto_flag);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_GATTC_ExecWrite(uint16_t conn_hdl, uint8_t exe_flag)
 * @brief   If the auto execute of Reliable Writes is not specified by R_BLE_GATTC_ReliableWrites(),
 *          this function is used to execute a write to Characteristic.
 * @details When all of the contents has been sent to the GATT Server, BLE_GATTC_EVENT_RELIABLE_WRITES_TX_COMP event
 *          notifies the application layer.\n
 *          After this event has been received, execute the write by this function.\n
 *          The result of the write is notified by BLE_GATTC_EVENT_RELIABLE_WRITES_COMP event.
 * @param[in] conn_hdl Connection handle identifying the target GATT Server.
 * @param[in] exe_flag The flag that indicates whether execution or cancellation.
 *        |              macro                          |   description       |
 *        |:------------------------------------------- |:------------------- |
 *        | BLE_GATTC_EXECUTE_WRITE_CANCEL_FLAG(0x00)   | Execute the write.  |
 *        | BLE_GATTC_EXECUTE_WRITE_EXEC_FLAG(0x01)     | Cancel the write.   |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The exe_flag parameter is out of range.
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) The reason for this error is as follows:
 *           - GATT Client has not requested for Reliable Writes by R_BLE_GATTC_ReliableWrites().
 *           - Although auto execution has been specified by R_BLE_GATTC_ReliableWrites(), this function was called.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The GATT Server specified by conn_hdl was not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_GATTC_ExecWrite(uint16_t conn_hdl, uint8_t exe_flag);

/*@}*/

/* ============================================= L2CAP API Declarations ============================================= */

/** @defgroup L2CAP_API L2CAP
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup L2CAP_API
 * @fn ble_status_t R_BLE_L2CAP_RegisterCfPsm(ble_l2cap_cf_app_cb_t cb, uint16_t psm, uint16_t lwm)
 * @brief   This function registers PSM that uses L2CAP CBFC Channel and a callback for L2CAP event.
 * @details Only one callback is available per PSM. Configure in each PSM the Low Water Mark of the LE-Frames
 *          that the local device can receive.\n
 *          When the number of the credit reaches the Low Water Mark, BLE_L2CAP_EVENT_CF_LOW_RX_CRD_IND event is
 *          notified to the application layer.\n
 *          The number of PSM is defined as BLE_L2CAP_MAX_CBFC_PSM.\n
 *          The result of this API call is returned by a return value.
 * @param[in] cb Callback function for L2CAP event.
 * @param[in] psm  Identifier indicating the protocol/profile that uses L2CAP CBFC Channel.
 *              <table>
 *                  <tr>
 *                      <th>type</th>
 *                      <th>range</th>
 *                      <th>description</th>
 *                  </tr>
 *                  <tr>
 *                      <td>Fixed, SIG assigned</td>
 *                      <td>0x0001 - 0x007F</td>
 *                      <td>PSM defined by SIG. For more information on PSM, refer Bluetooth SIG Assigned Number
 *                          (https://www.bluetooth.com/specifications/assigned-numbers).
 *                      </td>
 *                  </tr>
 *                  <tr>
 *                      <td>Dynamic</td>
 *                      <td>0x0080 - 0x00FF</td>
 *                      <td>
 *                          Statically allocated PSM by custom protocol or dynamically allocated PSM by GATT Service.
 *                      </td>
 *                  </tr>
 *              </table>
 * @param[in] lwm Low Water Mark that indicates the LE-Frame numbers that the local device can receive.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The cb parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The psm parameter is out of range.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) More than BLE_L2CAP_MAX_CBFC_PSM+1 PSMs, callbacks has been registered.
 **********************************************************************************************************************/
ble_status_t R_BLE_L2CAP_RegisterCfPsm(ble_l2cap_cf_app_cb_t cb, uint16_t psm, uint16_t lwm);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_L2CAP_DeregisterCfPsm(uint16_t psm)
 * @brief   This function stops the use of the L2CAP CBFC Channel specified by the psm parameter and
 *          deregisters the callback function for L2CAP event.
 * @details The result of this API call is returned by a return value.
 * @param[in] psm PSM that is to be stopped to use the L2CAP CBFC Channel.\n
 *                Set the PSM registered by R_BLE_L2CAP_RegisterCfPsm().
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_NOT_FOUND(0x000D) The callback function allocated by the psm parameter is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_L2CAP_DeregisterCfPsm(uint16_t psm);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_L2CAP_ReqCfConn(uint16_t conn_hdl, st_ble_l2cap_conn_req_param_t * p_conn_req_param)
 * @brief   This function sends a connection request for L2CAP CBFC Channel.
 * @details The connection response is notified by BLE_L2CAP_EVENT_CF_CONN_CNF event.\n
 *          The result of this API call is returned by a return value.
 * @param[in] conn_hdl Connection handle identifying the remote device that the connection request is sent to.
 * @param[in] p_conn_req_param Connection request parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_conn_req_param parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The mtu parameter or the mps parameter is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) CF Channel connection has not been established.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) New CF Channel can not be registered or other L2CAP Command is processing.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) Insufficient memory is needed to generate this function.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by conn_hdl is not found.
 * @retval  BLE_ERR_NOT_YET_READY(0x0012) The psm parameter is not registered.
 **********************************************************************************************************************/
ble_status_t R_BLE_L2CAP_ReqCfConn(uint16_t conn_hdl, st_ble_l2cap_conn_req_param_t * p_conn_req_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_L2CAP_RspCfConn(st_ble_l2cap_conn_rsp_param_t * p_conn_rsp_param)
 * @brief   This function replies to the connection request for L2CAP CBFC Channel from the remote device.
 * @details The connection request is notified by BLE_L2CAP_EVENT_CF_CONN_IND event.
 *          The result of this API call is returned by a return value.
 * @param[in] p_conn_rsp_param Connection response parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_conn_rsp_param parameter is specified as NULL.
 * @retval  BLE_ERR_NOT_FOUND(0x000D) A connection request for L2CAP CBFC Channel has not been received,
 *                                    or CID specified by the lcid field in the p_conn_rsp_param parameter is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_L2CAP_RspCfConn(st_ble_l2cap_conn_rsp_param_t * p_conn_rsp_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_L2CAP_DisconnectCf(uint16_t lcid)
 * @brief   This function sends a disconnection request for L2CAP CBFC Channel.
 * @details When L2CAP CBFC Channel has been disconnected,
 *          BLE_L2CAP_EVENT_CF_DISCONN_CNF event is notified to the application layer.
 * @param[in] lcid CID identifying the L2CAP CBFC Channel that has been disconnected.\n
 *                 The valid range is 0x40 - (0x40 + BLE_L2CAP_MAX_CBFC_PSM - 1).
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_OPERATION(0x0009) CF Channel connection has not been established.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) This function was called while processing other L2CAP command.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for L2CAP Command.
 * @retval  BLE_ERR_NOT_FOUND(0x000D) CID specified the lcid parameter is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_L2CAP_DisconnectCf(uint16_t lcid);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_L2CAP_SendCfCredit(uint16_t lcid, uint16_t credit)
 * @brief   This function sends credit to a remote device.
 * @details In L2CAP CBFC communication, if credit is 0, the remote device stops data transmission.\n
 *          Therefore when processing the received data has been completed and local device affords to receive data,
 *          the remote device is notified of the number of LE-Frame that local device can receive
 *          by this function and local device can continue to receive data from the remote device.\n
 *          The result of this API call is returned by a return value.
 * @param[in] lcid CID identifying the L2CAP CBFC Channel on local device that sends credit.
 * @param[in] credit  Credit to be sent to the remote device.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The credit parameter is set to 0.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) This function was called while processing other L2CAP command.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for L2CAP Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_L2CAP_SendCfCredit(uint16_t lcid, uint16_t credit);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_L2CAP_SendCfData(uint16_t conn_hdl, uint16_t lcid, uint16_t data_len, uint8_t * p_sdu)
 * @brief   This function sends the data to a remote device via L2CAP CBFC Channel.
 * @details When the data transmission to Controller has been completed,
 *          BLE_L2CAP_EVENT_CF_TX_DATA_CNF event is notified to the application layer.
 * @param[in] conn_hdl Connection handle identifying the remote device to be sent the data.
 * @param[in] lcid  CID identifying the L2CAP CBFC Channel on local device used in the data transmission.
 * @param[in] data_len Length of the data.
 * @param[in] p_sdu Service Data Unit. \n
 *            Input the data length specified by the data_len parameter to the first 2 bytes (Little Endian).
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_data parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The length parameter is out of range.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) CF Channel connection has not been established or the data whose length
 *                                        exceeds the MTU has been sent.
 * @retval  BLE_ERR_ALREADY_IN_PROGRESS(0x000A) Data transmission has been already started.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) L2CAP task queue is full.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for L2CAP Command.
 * @retval  BLE_ERR_NOT_FOUND(0x000D) CID specified the lcid parameter is not found.
 * @retval  BLE_ERR_INVALID_HDL(0x000E) The remote device specified by the conn_hdl parameter is not found.
 **********************************************************************************************************************/
ble_status_t R_BLE_L2CAP_SendCfData(uint16_t conn_hdl, uint16_t lcid, uint16_t data_len, uint8_t * p_sdu);

/*@}*/

/* ======================================== Vendor Specific API Declarations ======================================== */

/** @defgroup VS_API VS
 *  @ingroup BLE
 *  @{
 */

/******************************************************************************************************************//**
 * @ingroup VS_API
 * @fn ble_status_t R_BLE_VS_Init(ble_vs_app_cb_t vs_cb)
 * @brief   This function initializes Vendor Specific API and registers a callback function for Vendor Specific Event.
 * @details The result of this API call is returned by a return value.
 * @param[in] vs_cb Callback function to be registered.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The vs_cb parameter is specified as NULL.
 * @retval  BLE_ERR_CONTEXT_FULL(0x000B) Callback function has already been registered.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_Init(ble_vs_app_cb_t vs_cb);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_StartTxTest(st_ble_vs_tx_test_param_t * p_tx_test_param)
 * @brief   This function starts extended Transmitter Test.
 * @details The following extended transmitter test functions of DTM Tx are supported by this function.
 *            - Tx Power
 *            - Tx Modulation Enable/Modulation Disable
 *            - Tx packet transmission/continuous transmission
 *            - Tx packets count
 *
 *           The result of this API call is notified in BLE_VS_EVENT_TX_TEST_START event.\n
 *           If the num_of_packet field in the p_tx_test_param parameter is other than 0x0000,
 *           BLE_VS_EVENT_TX_TEST_TERM event notifies the application layer that the number of packet has been sent.\n
 *           If R_BLE_VS_EndTest() is called before the specified number of packets completions,
 *           BLE_VS_EVENT_TX_TEST_TERM event is not notified to the application layer.
 *
 *           The condition that phy field in the p_tx_test_param parameter is @ref BLE_VS_EH_TEST_PHY_CODED_S_8(0x03)
 *           and option field is modulation(bit0:0) & continuous transmission(bit1:1) is not supported.
 *
 * @param[in] p_tx_test_param Tx Test parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_tx_test_param parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_StartTxTest(st_ble_vs_tx_test_param_t * p_tx_test_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_StartRxTest(st_ble_vs_rx_test_param_t * p_rx_test_param)
 * @brief   This function starts extended Receiver Test.
 * @details The result of this API call is notified in BLE_VS_EVENT_RX_TEST_START event.
 *          The following extended receiver test functions of DTM Rx are supported by this function.
 *            - Calculating the maximum, the minimum and the average of RSSI in the receiver test.
 *            - The number of CRC error packets in the receiver test.
 *
 *          The transmitter is configured to one of the following, the receiver can't receive the packets by this function.\n
 *          - Tx Non-Modulation Enable
 *          - Tx continuous transmission
 *          \n
 *          After R_BLE_VS_EndTest() has been called,
 *          the receiver test result value are notified in BLE_VS_EVENT_TEST_END event.
 *
 * @param[in] p_rx_test_param The extended receiver test parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_rx_test_param parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_StartRxTest(st_ble_vs_rx_test_param_t * p_rx_test_param);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_EndTest(void)
 * @brief   This function terminates the extended transmitter or receiver test.
 * @details The result of this API call is notified in BLE_VS_EVENT_TEST_END event.
 *          In case of extended receiver test, this event notifies the application layer of
 *          the result of the extended receiver test.
 *
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_EndTest(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_SetTxPower(uint16_t conn_hdl, uint8_t tx_power)
 * @brief   This function configures transmit power.
 * @details This function configures the following transmit power.
 *          - The transmit power used in sending advertising PDU, scan request PDU,
 *             connection request PDU (in not connected state)
 *          - The transmit power used in sending PDU in connected state.
 *          When configuring the transmit power used in not connected state, set the conn_hdl parameter
 *          to BLE_GAP_INIT_CONN_HDL(0xFFFF).\n
 *          When the transmit power used in connected state is configured, set the conn_hdl parameter
 *          to the connection handle of the link.\n
 *          Select one of the following transmit power levels.
 *          - High
 *          - Middle
 *          - Low
 *
 *          Max transmit power of "High" is dependent on the configuration of the firmware.
 *          The result of this API call is notified in BLE_VS_EVENT_SET_TX_POWER event.
 *
 * @param[in] conn_hdl Connection handle identifying the link whose transmit power to be configured.
 *            If non connected state, set BLE_GAP_INIT_CONN_HDL(0xFFFF).
 * @param[in] tx_power Transmission power. Select one of the following.
 *                     - BLE_VS_TX_POWER_HIGH(0x00)
 *                     - BLE_VS_TX_POWER_MID(0x01)
 *                     - BLE_VS_TX_POWER_LOW(0x02)
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_SetTxPower(uint16_t conn_hdl, uint8_t tx_power);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_GetTxPower(uint16_t conn_hdl)
 * @brief   This function gets transmit power.
 * @details This function gets the following transmit power.
 *            - The transmit power used in sending advertising PDU, scan request PDU,
 *              connection request PDU (in not connected state)
 *            - The transmit power used in sending PDU in connected state.
 *          When getting the transmit power used in not connected state, set the conn_hdl parameter to
 *          BLE_GAP_INIT_CONN_HDL(0xFFFF).\n
 *          When the transmit power used in connected state is retrieved, set the conn_hdl parameter to
 *          the connection handle of the link.
 *          The result of this API call is notified in BLE_VS_EVENT_GET_TX_POWER event.
 *
 * @param[in] conn_hdl Connection handle identifying the link whose transmit power to be retrieved.
 *                     If non connected state, set BLE_GAP_INIT_CONN_HDL(0xFFFF).
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_GetTxPower(uint16_t conn_hdl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_SetCodingScheme(uint8_t coding_scheme)
 * @brief   This function configure default Coding scheme(S=8 or S=2) that is used in the case of selecting Coded PHY
 *          in Primary advertising PHY or Secondary advertising PHY advertising or request for link establishment.
 * @details After setting the default Coding scheme by this function, configure the advertising parameters
 *          by R_BLE_GAP_SetAdvParam() or send a request for link establishment.\n
 *          The result of this API call is notified in BLE_VS_EVENT_SET_CODING_SCHEME_COMP event.
 * @param[in] coding_scheme Coding scheme for Primary advertising PHY, Secondary advertising PHY,
 *                          request for link establishment.The coding_scheme field is set to a bitwise OR
 *                          of the following values.
 *        | bit            |   description                                                  |
 *        |:-------------- |:-------------------------------------------------------------- |
 *        | bit0           | Coding scheme for Primary Advertising PHY(0:S=8/1:S=2).        |
 *        | bit1           | Coding scheme for Secondary Advertising PHY(0:S=8/1:S=2).      |
 *        | bit2           | Coding scheme for request for link establishment(0:S=8/1:S=2). |
 *        | All other bits | Reserved for future use.                                       |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_SetCodingScheme(uint8_t coding_scheme);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_SetRfControl(st_ble_vs_set_rf_ctrl_param_t * p_rf_ctrl)
 * @brief   This function performs power control on RF.
 * @details If BLE communication is not used for a long time, RF reduces the power consumption by moving to
 *          the RF Power-Down Mode.\n
 *          When RF power on, RF initialization processing is executed.\n
 *          After RF power off by this function, API functions other than this are not available
 *          until RF power on again.\n
 *          The result of this API call is notified in BLE_VS_EVENT_RF_CONTROL_COMP event.
 *          After RF power on again with this function, call R_BLE_GAP_Terminate(),
 *          R_BLE_GAP_Init() in order to restart the host stack.
 * @param[in] p_rf_ctrl RF parameters.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_rf_ctrl parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_SetRfControl(st_ble_vs_set_rf_ctrl_param_t * p_rf_ctrl);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_SetBdAddr(uint8_t area, st_ble_dev_addr_t * p_addr)
 * @brief   This function sets public/random address of local device to the area specified by the parameter.
 * @details If the address is written in non-volatile area, the address is used as default address
 *          on the next MCU reset.\n
 *          For more information on the random address, refer to Core Specification Vol 6, PartB,
 *          "1.3.2 Random Device Address".\n
 *          The result of this API call is notified in BLE_VS_EVENT_SET_ADDR_COMP event.
 * @param[in] area The area that the address is to be written in.\n
 *                 Select one of the following.
 *                  <table>
 *                      <tr>
 *                          <th>macro</th>
 *                          <th>description</th>
 *                      </tr>
 *                      <tr>
 *                          <td>BLE_VS_ADDR_AREA_REG(0x00)</td>
 *                          <td>
 *                              Address writing to non-volatile area is not performed.<br/>
 *                              Only the address in register is written.
 *                          </td>
 *                      </tr>
 *                      <tr>
 *                          <td>BLE_VS_ADDR_AREA_DATA_FLASH(0x01)</td>
 *                          <td>Address wiring to DataFlash area is performed.</td>
 *                      </tr>
 *                  </table>
 * @param[in] p_addr The address to be set to the area.
 *                   Set BLE_GAP_ADDR_PUBLIC(0x00) or BLE_GAP_ADDR_RAND(0x01) to the type field in the p_addr parameter.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_addr parameter is specified as NULL.
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_SetBdAddr(uint8_t area, st_ble_dev_addr_t * p_addr);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_GetBdAddr(uint8_t area, uint8_t addr_type)
 * @brief   This function gets currently configured public/random address.
 * @details The area parameter specifies the place where this function retrieves public/random address.\n
 *          The result of this API call is notified in BLE_VS_EVENT_GET_ADDR_COMP event.
 * @param[in] area The area that the address is to be retrieved.\n
 *                 Select one of the following.
 *                  <table>
 *                      <tr>
 *                          <th>macro</th>
 *                          <th>description</th>
 *                      </tr>
 *                      <tr>
 *                          <td>BLE_VS_ADDR_AREA_REG(0x00)</td>
 *                          <td>Retrieve the address in register.</td>
 *                      </tr>
 *                      <tr>
 *                          <td>BLE_VS_ADDR_AREA_DATA_FLASH(0x01)</td>
 *                          <td>Retrieve the address in DataFlash area.</td>
 *                      </tr>
 *                  </table>
 * @param[in] addr_type The address type that is type of the address to be retrieved.
 *        | macro                     |   description      |
 *        |:------------------------- |:------------------ |
 *        | BLE_GAP_ADDR_PUBLIC(0x00) | Public address.    |
 *        | BLE_GAP_ADDR_RAND(0x01)   | Random address.    |
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_GetBdAddr(uint8_t area, uint8_t addr_type);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_GetRand(uint8_t rand_size)
 * @brief   This function generates 4-16 bytes of random number used in creating keys.
 * @details The result of this API call is notified in BLE_VS_EVENT_GET_RAND event.
 * @param[in] rand_size Length of the random number (byte).\n
 *                      The valid range is 4<=rand_size<=16.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_STATE(0x0008) The task for host stack is not running.
 * @retval  BLE_ERR_MEM_ALLOC_FAILED(0x000C) There are no memories for Vendor Specific Command.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_GetRand(uint8_t rand_size);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_StartTxFlowEvtNtf(void)
 * @brief   This function starts the notification(BLE_VS_EVENT_TX_FLOW_STATE_CHG event) of
 *          the state transition of TxFlow.
 * @details If the number of the available transmission packet buffers is the following,
 *          BLE_VS_EVENT_TX_FLOW_STATE_CHG event notifies the application layer of the state of the TxFlow.
 *          - The number of the available transmission packet buffers is less than Low Water Mark.
 *          - The number of the available transmission packet buffers is more than High Water Mark.
 *          The result of this API call is returned by a return value.
 * @retval  BLE_SUCCESS(0x0000) Success
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_StartTxFlowEvtNtf(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_StopTxFlowEvtNtf(void)
 * @brief   This function stops the notification(BLE_VS_EVENT_TX_FLOW_STATE_CHG event) of
 *          the state transition of TxFlow.
 * @details The result of this API call is returned by a return value.
 * @retval  BLE_SUCCESS(0x0000) Success
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_StopTxFlowEvtNtf(void);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_GetTxBufferNum(uint32_t * p_buffer_num)
 * @brief   This function retrieves the number of the available transmission packet buffers.
 * @details The maximum number of the available buffers is 10.\n
 *          The result of this API call is returned by a return value.
 * @param[out] p_buffer_num The number of the available transmission packet buffers.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_PTR(0x0001) The p_buffer_num parameter is specified as NULL.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_GetTxBufferNum(uint32_t * p_buffer_num);

/******************************************************************************************************************//**
 * @fn ble_status_t R_BLE_VS_SetTxLimit(uint32_t tx_queue_lwm, uint32_t tx_queue_hwm)
 * @brief   This function sets the threshold for notifying the application layer of the TxFlow state.
 * @details Call this function before the notification(BLE_VS_EVENT_TX_FLOW_STATE_CHG event) has been started
 *          by R_BLE_VS_StartTxFlowEvtNtf(). \n
 *          The result is returned from this API.\n
 *          Vendor Specific API supports the flow control function(TxFlow) for the transmission
 *          on L2CAP fixed channel in Basic Mode such as GATT.\n
 *          Host stack has 10 transmission packet buffers for the transmission.\n
 *          When the number of the available transmission packet buffers has been less than Low Water Mark,
 *          the state of TxFlow transmits into the TxFlow OFF state from the TxFlow ON state
 *          that is the initial state and host stack notifies the application layer of
 *          timing to stop packet transmission.\n
 *          When host stack has sent the transmission packets to Controller and the number of the available
 *          transmission packet buffers has been more than High Water Mark, the state of TxFlow transmits into
 *          the TxFlow ON state from the TxFlow OFF state and host stack notifies the application layer of
 *          timing to restart packet transmission.\n
 *          It is possible to perform flow control on a fixed channel by using the event notification.
 * @param[in] tx_queue_lwm Low Water Mark.
 *                         Set 0-9 less than tx_queue_hwm to the parameter.
 *                         When the number of the available transmission packet buffers has been less than the value
 *                         specified by the tx_queue_lwm parameter, host stack notifies the application layer of
 *                         the timing to stop packet transmission.
 * @param[in] tx_queue_hwm High Water Mark.
 *                         Set 1-10 more than tx_queue_lwm to the parameter.
 *                         When the number of the available transmission packet buffers has been more than
 *                         the value specified by the tx_queue_hwm parameter, host stack notifies
 *                         the application layer of the timing to restart packet transmission.
 * @retval  BLE_SUCCESS(0x0000) Success
 * @retval  BLE_ERR_INVALID_ARG(0x0003) The tx_queue_lwm parameter or the tx_queue_hwm parameter is out of range.
 **********************************************************************************************************************/
ble_status_t R_BLE_VS_SetTxLimit(uint32_t tx_queue_lwm, uint32_t tx_queue_hwm);

/*@}*/

/*******************************************************************************************************************//**
 * @} (end addtogroup BLE_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
