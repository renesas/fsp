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

#ifndef RM_BLE_MESH_PROVISION_API_H
#define RM_BLE_MESH_PROVISION_API_H

/*******************************************************************************************************************//**
 * @ingroup  RENESAS_INTERFACES
 * @defgroup RM_BLE_MESH_PROVISION_API BLE Mesh Provision Interface
 * @brief    Interface for Bluetooth Low Energy Mesh Provision functions.
 *
 * @section RM_BLE_MESH_PROVISION_API_Summary Summary
 * The BLE Mesh Provision interface for the Bluetooth Low Energy Mesh Provision (BLE MESH PROVISION) peripheral provides Bluetooth Low Energy Mesh Provision functionality.
 *
 * The Bluetooth Low Energy Mesh interface can be implemented by:
 * - @ref RM_BLE_MESH_PROVISION
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#include "rm_ble_mesh_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Provisioning array size requirements */

/** Provisioning key NetKey size */
#define RM_BLE_MESH_PROVISION_KEY_NETKEY_SIZE    16

/** Provisioning ECDH Key size */
#define RM_BLE_MESH_PROVISION_ECDH_KEY_SIZE      32

/** Provisioning OOB value size */
#define RM_BLE_MESH_PROVISION_OOB_VALUE_SIZE     16

/** Provisioning URI hash size */
#define RM_BLE_MESH_PROVISION_URI_HASH_SIZE      4

/** Invalid Provisioning Handle */
#define RM_BLE_MESH_PROVISION_HANDLE_INVALID     0xFF

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Handle to reference the active provisioning context */
typedef uint8_t rm_ble_mesh_provision_handle_t;

/** Provisioning Roles */
typedef enum e_rm_ble_mesh_provision_role
{
    RM_BLE_MESH_PROVISION_ROLE_DEVICE      = 0x01, ///< Device role
    RM_BLE_MESH_PROVISION_ROLE_PROVISIONER = 0x02, ///< Provisioner role
} rm_ble_mesh_provision_role_t;

/** Provisioning Bearer Types */
typedef enum e_rm_ble_mesh_provision_bearer_type
{
    RM_BLE_MESH_PROVISION_BEARER_TYPE_ADV  = 0x01, ///< Advertising bearer type
    RM_BLE_MESH_PROVISION_BEARER_TYPE_GATT = 0x02, ///< GATT bearer type
} rm_ble_mesh_provision_bearer_type_t;

/** Provisioning PDU Types */
typedef enum e_rm_ble_mesh_provision_pdu_type
{
    RM_BLE_MESH_PROVISION_PDU_TYPE_INVITE         = 0x00, ///< Invite PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_CAPAB          = 0x01, ///< Capable PDu type
    RM_BLE_MESH_PROVISION_PDU_TYPE_START          = 0x02, ///< Start PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_PUBKEY         = 0x03, ///< Public key PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_INPUT_COMPLETE = 0x04, ///< Input complete PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_CONF           = 0x05, ///< Configuration PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_RAND           = 0x06, ///< Random PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_DATA           = 0x07, ///< Data PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_COMPLETE       = 0x08, ///< Complete PDU type
    RM_BLE_MESH_PROVISION_PDU_TYPE_FAILED         = 0x09, ///< Failed PDU type
} rm_ble_mesh_provision_pdu_type_t;

/** Provisioning public key values */
typedef enum e_rm_ble_mesh_provision_pubkey
{
    RM_BLE_MESH_PROVISION_PUBKEY_NO_OOB = 0x00, ///< Public key no OOB
    RM_BLE_MESH_PROVISION_PUBKEY_OOB    = 0x01, ///< Public key OOB
} rm_ble_mesh_provision_pub_key_value_t;

/** Provisioning authentication method values */
typedef enum e_rm_ble_mesh_provision_auth_method
{
    RM_BLE_MESH_PROVISION_AUTH_METHOD_OOB_NONE   = 0x00, ///< Authentication method none
    RM_BLE_MESH_PROVISION_AUTH_METHOD_OOB_STATIC = 0x01, ///< Authentication method static
    RM_BLE_MESH_PROVISION_AUTH_METHOD_OOB_OUTPUT = 0x02, ///< Authentication method output
    RM_BLE_MESH_PROVISION_AUTH_METHOD_OOB_INPUT  = 0x03, ///< Authentication method input
} rm_ble_mesh_provision_auth_method_t;

/** Provisioning Output OOB action values */
typedef enum e_rm_ble_mesh_provision_output_oob_action
{
    RM_BLE_MESH_PROVISION_OUTPUT_OOB_ACTION_BLINK        = (0), ///< Output OOB action blink
    RM_BLE_MESH_PROVISION_OUTPUT_OOB_ACTION_BEEP         = (1), ///< Output OOB action beep
    RM_BLE_MESH_PROVISION_OUTPUT_OOB_ACTION_VIBRATE      = (2), ///< Output OOB action vibrate
    RM_BLE_MESH_PROVISION_OUTPUT_OOB_ACTION_NUMERIC      = (3), ///< Output OOB action numeric
    RM_BLE_MESH_PROVISION_OUTPUT_OOB_ACTION_ALPHANUMERIC = (4), ///< Output OOB action alphanumeric
} rm_ble_mesh_provision_output_oob_action_t;

/** Provisioning Input OOB action values */
typedef enum e_rm_ble_mesh_provision_input_oob_action
{
    RM_BLE_MESH_PROVISION_INPUT_OOB_ACTION_PUSH         = (0), ///< Input OOB action push
    RM_BLE_MESH_PROVISION_INPUT_OOB_ACTION_TWIST        = (1), ///< Input OOB action twist
    RM_BLE_MESH_PROVISION_INPUT_OOB_ACTION_NUMERIC      = (2), ///< Input OOB action numeric
    RM_BLE_MESH_PROVISION_INPUT_OOB_ACTION_ALPHANUMERIC = (3), ///< Input OOB action alphanumeric
} rm_ble_mesh_provision_input_oob_action_t;

/** Specification defined transport Opcodes for PB-ADV bearer */
typedef enum e_rm_ble_mesh_provision_adv_transport_opcode
{
    /** Link Open Request */
    RM_BLE_MESH_PROVISION_ADV_TRANSPORT_OPECODE_OPEN_REQ = 0x00,

    /** Link Open Confirm */
    RM_BLE_MESH_PROVISION_ADV_TRANSPORT_OPECODE_OPEN_CNF = 0x01,

    /** Link Close Indication */
    RM_BLE_MESH_PROVISION_ADV_TRANSPORT_OPECODE_CLOSE_IND = 0x02,
} rm_ble_mesh_provision_adv_transport_opcode_t;

/** Implementation specific transport Opcodes for PB-GATT bearer */
typedef enum e_rm_ble_mesh_provision_gatt_transport_opcode
{
    /** Link Open Indication */
    RM_BLE_MESH_PROVISION_GATT_TRANSPORT_OPECODE_OPEN_IND = 0xF1,

    /** Link Close Indication */
    RM_BLE_MESH_PROVISION_GATT_TRANSPORT_OPECODE_CLOSE_IND = 0xF0,
} rm_ble_mesh_provision_gatt_transport_opcode_t;

/** Provisioning Failure Error Codes */
typedef enum e_rm_ble_mesh_provision_error_code
{
    RM_BLE_MESH_PROVISION_ERROR_CODE_PROHIBITED            = 0x00, ///< Failure error code prohibited
    RM_BLE_MESH_PROVISION_ERROR_CODE_INVALID_PDU           = 0x01, ///< Failure error code invalid PDU
    RM_BLE_MESH_PROVISION_ERROR_CODE_INVALID_FORMAT        = 0x02, ///< Failure error code invalid format
    RM_BLE_MESH_PROVISION_ERROR_CODE_UNEXPECTED_PDU        = 0x03, ///< Failure error code unexpected PDU
    RM_BLE_MESH_PROVISION_ERROR_CODE_CONFIRMATION_FAILED   = 0x04, ///< Failure error code confirmation failed
    RM_BLE_MESH_PROVISION_ERROR_CODE_OUT_OF_RESOURCES      = 0x05, ///< Failure error code out of resources
    RM_BLE_MESH_PROVISION_ERROR_CODE_DECRYPTION_FAILED     = 0x06, ///< Failure error code decryption failed
    RM_BLE_MESH_PROVISION_ERROR_CODE_UNEXPECTED_ERROR      = 0x07, ///< Failure error code unexpected error
    RM_BLE_MESH_PROVISION_ERROR_CODE_CANNOT_ASSIGN_ADDRESS = 0x08, ///< Failure error code cannot assign address
} rm_ble_mesh_provision_error_code_t;

/** Provisioning LinkClose Error codes */
typedef enum e_rm_ble_mesh_provision_link_close_reason
{
    RM_BLE_MESH_PROVISION_LINK_CLOSE_REASON_SUCCESS = 0x00, ///< Link close error code reason success
    RM_BLE_MESH_PROVISION_LINK_CLOSE_REASON_TIMEOUT = 0x01, ///< Link close error code reason timeout
    RM_BLE_MESH_PROVISION_LINK_CLOSE_REASON_FAIL    = 0x02, ///< Link close error code reason fail
} rm_ble_mesh_provision_link_close_reason_t;

/** Provisioning OOB type masks for ADV data */
typedef enum e_rm_ble_mesh_provision_oob_type
{
    RM_BLE_MESH_PROVISION_OOB_TYPE_OTHER          = (1 << 0),  ///< Other OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_URI            = (1 << 1),  ///< URI OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_2DMRC          = (1 << 2),  ///< 2DMRC OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_BARCODE        = (1 << 3),  ///< Bar code OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_NFC            = (1 << 4),  ///< NFC OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_NUMBER         = (1 << 5),  ///< Number OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_STRING         = (1 << 6),  ///< String OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_ONBOX          = (1 << 11), ///< On box OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_INSIDEBOX      = (1 << 12), ///< Inside box OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_ONPIECEOFPAPER = (1 << 13), ///< On piece of paper OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_INSIDEMANUAL   = (1 << 14), ///< Inside manual OOB type mask
    RM_BLE_MESH_PROVISION_OOB_TYPE_ONDEVICE       = (1 << 15), ///< On device OOB type mask
} rm_ble_mesh_provision_oob_type_t;

/**
 *  Provision Events
 *  The Asynchronous Events notified to Application by the
 *  Module.
 */
typedef enum e_rm_ble_mesh_provision_event_type
{
    /**
     * This event indicates the availability of an unprovisioned device beacon,
     * with the following values as parameters in the
     * @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_UNPROVISIONED_BEACON.
     * @param [in] event_result
     * @param [in] event_data     Pointer to the array with the UUID of the device.
     * @param [in] event_datalen  RM_BLE_MESH_DEVICE_UUID_SIZE
     *
     * \note This event is received by the Provisioner application. On reception of
     * this event, the application shall make use of the RM_BLE_MESH_PROVISION_Bind() to initiate
     * the provisioning procedure.
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_UNPROVISIONED_BEACON = 0x01,

    /**
     * This event indicates that the provisioning procedure capability exchange is
     * complete, with the following values as parameters in the
     * @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVISIONING_SETUP.
     * @param [in] event_result   FSP_SUCCESS on successful procedure completion, else an Error Code.
     * @param [in] event_data     When local provisioner, this contains peer device
     *                            capabilities and when local device,
     *                            this contains the attention timeout value.
     * @param [in] event_datalen  When local provisioner,
     *                            sizeof(@ref rm_ble_mesh_provision_capabilities_t)
     *                            and when local device, sizeof(uint32_t).
     *
     * \note When local provisioner, the appliation shall select the required
     * capability from the received capabilities and choose to start the procedure
     * by calling @ref RM_BLE_MESH_PROVISION_SendPdu() put RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVISIONING_SETUP as the third argument.
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVISIONING_SETUP = 0x02,

    /**
     * This event indicates to the application the OOB random data that is to be
     * displayed on the UI via the @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_OOB_DISPLAY.
     * @param [in] event_result   FSP_SUCCESS on successful procedure completion, else an Error Code.
     * @param [in] event_data     Pointer to OOB information as in @ref rm_ble_mesh_provision_oob_info_t.
     * @param [in] event_datalen  sizeof (@ref rm_ble_mesh_provision_oob_info_t).
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_OOB_DISPLAY = 0x03,

    /**
     * This event indicates to the application requesting for OOB random data that
     * is to be used in the procedure via the @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_OOB_ENTRY.
     * @param [in] event_result   FSP_SUCCESS on successful procedure completion, else an Error Code.
     * @param [in] event_data     Pointer to OOB information as in @ref rm_ble_mesh_provision_oob_info_t.
     * @param [in] event_datalen  sizeof (@ref rm_ble_mesh_provision_oob_info_t).
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_OOB_ENTRY = 0x04,

    /**
     * This event indicates to the application that the peer device has completed the
     * Input of OOB when this capability is negotiated via the
     * @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_DEVINPUT_COMPLETE.
     * @param [in] event_result   FSP_SUCCESS on successful procedure completion, else an Error Code.
     * @param [in] event_data     NULL.
     * @param [in] event_datalen  0.
     *
     * \note This event is generated only for the provisioner application.
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_DEVINPUT_COMPLETE = 0x05,

    /**
     * This event indicates to the application requesting for Provisional data to be
     * sent to the peer device via the @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVDATA_INFO_REQ.
     * @param [in] event_result   FSP_SUCCESS on successful procedure completion, else an Error Code.
     * @param [in] event_data     NULL.
     * @param [in] event_datalen  0.
     *
     * \note This event is generated only for the provisioner application.
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVDATA_INFO_REQ = 0x06,

    /**
     * This event indicates to the application the Provisional data received
     * from the Provisioner via the @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVDATA_INFO.
     * @param [in] event_result   FSP_SUCCESS on successful procedure completion, else an Error Code.
     * @param [in] event_data     Pointer to the provisioning data @ref rm_ble_mesh_provision_data_t.
     * @param [in] event_datalen  sizeof(@ref rm_ble_mesh_provision_data_t).
     *
     * \note This event is generated only for the device application.
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVDATA_INFO = 0x07,

    /**
     * This event indicates to the application that the provisioning procedure
     * is complete via the @ref rm_ble_mesh_provision_callback_args_t callback.
     *
     * @param [in] phandle        Pointer to the Provisioning context handle
     * @param [in] event_type     @ref RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVISIONING_COMPLETE.
     * @param [in] event_result   FSP_SUCCESS on successful procedure completion, else an Error Code.
     * @param [in] event_data     NULL.
     * @param [in] event_datalen  0.
     *
     */
    RM_BLE_MESH_PROVISION_EVENT_TYPE_PROVISIONING_COMPLETE = 0x08,
} rm_ble_mesh_provision_event_type_t;

/** Device Information used for Provisioning */
typedef struct st_rm_ble_mesh_provision_device
{
    /**
     * Device UUID -
     * Used in unprovisioned device beacon and Provisioning Invite
     */
    uint8_t uuid[RM_BLE_MESH_DEVICE_UUID_SIZE];

    /** OOB Information */
    uint16_t oob;

    /** URI if any, to be given in encoded form */
    rm_ble_mesh_buffer_t * uri;
} rm_ble_mesh_provision_device_t;

/** OOB type for provisioning */
typedef struct st_rm_ble_mesh_provision_oob_info
{
    /** OOB Action information */
    uint16_t action;

    /** OOB Size information */
    uint8_t size;
} rm_ble_mesh_provision_oob_info_t;

/** Device capabilities used for Provisioning */
typedef struct st_rm_ble_mesh_provision_capabilities
{
    /** Number of Elements */
    uint8_t num_elements;

    /** Supported algorithms */
    uint16_t supported_algorithms;

    /** Public key type */
    uint8_t supported_pubkey;

    /** Static OOB type */
    uint8_t supported_soob;

    /** Output OOB information */
    rm_ble_mesh_provision_oob_info_t output_oob;

    /** Input OOB information */
    rm_ble_mesh_provision_oob_info_t input_oob;
} rm_ble_mesh_provision_capabilities_t;

/** Provisioning method information */
typedef struct st_rm_ble_mesh_provision_method
{
    /** Algorithm selected */
    uint8_t algorithm;

    /** Public key usage */
    uint8_t pubkey;

    /** Authentication type */
    uint8_t auth;

    /** OOB type */
    rm_ble_mesh_provision_oob_info_t oob;
} rm_ble_mesh_provision_method_t;

/** Data exchanged during Provisioning procedure */
typedef struct st_rm_ble_mesh_provision_data
{
    /** NetKey */
    uint8_t netkey[RM_BLE_MESH_PROVISION_KEY_NETKEY_SIZE];

    /** Index of the NetKey */
    uint16_t keyid;

    /**
     * Flags bit-mask
     * bit 0: Key Refresh Flag.
     *        0: Not-In-Phase2
     *        1: In-Phase2
     * bit 1: IV Update Flag
     *        0: Normal operation
     *        1: IV Update active
     *
     * bits 2-7: RFU
     */
    uint8_t flags;

    /** Current value of the IV index */
    uint32_t iv_index;

    /** Unicast address of the primary element */
    uint16_t unicast_addr;
} rm_ble_mesh_provision_data_t;

/** Provisioning device information */
typedef struct st_rm_ble_mesh_provision_device_info
{
    rm_ble_mesh_provision_bearer_type_t type;     ///< Provisioning Bearer Types
    rm_ble_mesh_provision_device_t    * p_device; ///< Device Information used for Provisioning
} rm_ble_mesh_provision_device_info_t;

/** Mesh model client callback parameter definition */
typedef struct st_rm_ble_mesh_provision_callback_args
{
    rm_ble_mesh_provision_handle_t   * p_handle;     ///< Handle to reference the active provisioning context
    rm_ble_mesh_provision_event_type_t event_type;   ///< Provisioning event type
    rm_ble_mesh_error_code_t           event_result; ///< BLE MESH error code
    rm_ble_mesh_buffer_t               event_data;   ///< Payload type
    void const * p_context;
} rm_ble_mesh_provision_callback_args_t;

/** BLE MESH PROVISION control block.  Allocate an instance specific control block to pass into the BLE MESH API calls.
 * @par Implemented as
 * - rm_ble_mesh_provision_instance_ctrl_t
 */
typedef void rm_ble_mesh_provision_ctrl_t;

/** BLE MESH PROVISION configuration parameters. */
typedef struct st_rm_ble_mesh_provision_cfg
{
    /** the parameters for initialization. */
    uint32_t channel;                                                    ///< Select a channel corresponding to the channel number of the hardware.
    rm_ble_mesh_provision_capabilities_t * p_capabilities;               ///< Device capabilities used for Provisioning
    rm_ble_mesh_instance_t const         * p_mesh_instance;              ///< Instance structure of BLE Mesh
    void (* p_callback)(rm_ble_mesh_provision_callback_args_t * p_args); ///< Callback function.
    void const * p_context;                                              ///< Placeholder for user data.  Passed to the user callback in ble_abs_callback_args_t.
    void const * p_extend;                                               ///< Placeholder for user extension.
} rm_ble_mesh_provision_cfg_t;

/** BLE MESH PROVISION functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_ble_mesh_provision_api
{
    /** Open access middleware.
     * @par Implemented as
     * - RM_BLE_MESH_PROVISION_Open()
     *
     * @param [in]  p_ctrl  Pointer to control structure.
     * @param [in]  p_cfg   Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, rm_ble_mesh_provision_cfg_t const * const p_cfg);

    /** Close access middleware.
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_Close()
     *
     * @param [in]  p_ctrl  Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_provision_ctrl_t * const p_ctrl);

    /** Setup the device for provisioning.
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_Setup()
     *
     * @param [in]  p_ctrl   Pointer to control structure.
     * @param [in]  role     Provisioning role to be setup - Device or Provisioner.
     * @param [in]  info     Device information.
     * @param [in]  timeout  The time period for which the setup shall be active.
     */
    fsp_err_t (* setup)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, rm_ble_mesh_provision_role_t role,
                        rm_ble_mesh_provision_device_info_t info, uint16_t timeout);

    /** Bind to the peer device for provisioning
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_Bind()
     *
     * @param [in]  p_ctrl     Pointer to control structure.
     * @param [in]  info       Device information.
     * @param [in]  attention  Attention duration.
     * @param [out] p_handle   Pointer to handle.
     *
     * @note This API is for use by the Provisioner application only upon
     *  reception of an Unprovisioned Device Beacon.
     */
    fsp_err_t (* bind)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, rm_ble_mesh_provision_device_info_t info,
                       uint8_t attention, rm_ble_mesh_provision_handle_t * const p_handle);

    /** Send provisioning PDUs to the peer.
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_SendPdu()
     *
     * @param [in]  p_ctrl    Pointer to control structure.
     * @param [in]  p_handle  Pointer to provisioning context to be used.
     * @param [in]  type      Following PDU types are handled -
     *                         @ref RM_BLE_MESH_PROVISION_PDU_TYPE_START
     *                         @ref RM_BLE_MESH_PROVISION_PDU_TYPE_INPUT_COMPLETE
     *                         @ref RM_BLE_MESH_PROVISION_PDU_TYPE_DATA
     * @param [in]  pdu_data  Pointer to the data corresponding to the above PDUs.
     */
    fsp_err_t (* sendPdu)(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                          rm_ble_mesh_provision_handle_t const * const p_handle, rm_ble_mesh_provision_pdu_type_t type,
                          rm_ble_mesh_buffer_t pdu_data);

    /** Set the display Auth-Value.
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_SetAuthVal()
     *
     * @param [in]  p_ctrl      Pointer to control structure.
     * @param [in]  p_handle    Pointer to provisioning context to be used.
     * @param [in]  auth_value  Pointer to the Authval (UINT32 *) or (uint8_t *).
     */
    fsp_err_t (* setAuthVal)(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                             rm_ble_mesh_provision_handle_t const * const p_handle, rm_ble_mesh_buffer_t auth_value);

    /** Abort the provisioning procedure
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_Abort()
     *
     * @param [in] p_ctrl    Pointer to control structure.
     * @param [in] p_handle  Pointer to provisioning context to be used.
     * @param [in] reason    Reason for termination.
     */
    fsp_err_t (* abort)(rm_ble_mesh_provision_ctrl_t * const         p_ctrl,
                        rm_ble_mesh_provision_handle_t const * const p_handle,
                        rm_ble_mesh_provision_link_close_reason_t    reason);

    /** Utility API to get current ECDH Public Key to be used for Provisioning
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_GetLocalPublicKey()
     *
     * @param [in]  p_ctrl      Pointer to control structure.
     * @param [out] public_key  To a pointer of uint8_t array of length
     *                          @ref RM_BLE_MESH_PROVISION_KEY_NETKEY_SIZE.
     */
    fsp_err_t (* getLocalPublicKey)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, uint8_t * const public_key);

    /** Utility API to set current ECDH Public Key to be used for Provisioning
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_SetLocalPublicKey()
     *
     * @param [in]  p_ctrl      Pointer to control structure.
     * @param [out] public_key  To a pointer of uint8_t array of length
     *                          @ref RM_BLE_MESH_PROVISION_KEY_NETKEY_SIZE.
     */
    fsp_err_t (* setLocalPublicKey)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, uint8_t const * const public_key);

    /** Utility API to generate 128bits (16 bytes) randomized number to be used for provisioning.
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_GenerateRandomizedNumber()
     *
     * @param [in]  p_ctrl   Pointer to control structure.
     * @param [out] p_key    Pointer to buffer to store random number.
     */
    fsp_err_t (* generateRandomizedNumber)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, uint8_t * const p_key);

    /** Utility API to set device out of band public key for provisioning.
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_SetOobPublicKey()
     *
     * @param [in]  p_ctrl   Pointer to control structure.
     * @param [in]  p_key    Pointer to public key.
     * @param [in]  size     Size of public key.
     */
    fsp_err_t (* setOobPublicKey)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, uint8_t const * const p_key,
                                  uint8_t size);

    /** Utility API to set device out of band authentication information for provisioning.
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_SetOobAuthInfo()
     *
     * @param [in]  p_ctrl       Pointer to control structure.
     * @param [in]  p_auth_info  Pointer to authentication information.
     * @param [in]  size         Size of authentication information.
     */
    fsp_err_t (* setOobAuthInfo)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, uint8_t const * const p_auth_info,
                                 uint8_t size);

    /** Utility API to generate ECDH Public Key to be used for Provisioning
     * @par Implemented as
     * - @ref RM_BLE_MESH_PROVISION_GenerateEcdhKey()
     *
     * @param [in]  p_ctrl       Pointer to control structure.
     * @param [out] p_public_key Pointer to public key. Size of public key is @ref RM_BLE_MESH_PROVISION_ECDH_KEY_SIZE.
     */
    fsp_err_t (* generateEcdhKey)(rm_ble_mesh_provision_ctrl_t * const p_ctrl, uint8_t * const p_public_key);
} rm_ble_mesh_provision_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_provision_instance
{
    rm_ble_mesh_provision_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rm_ble_mesh_provision_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_ble_mesh_provision_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rm_ble_mesh_provision_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_PROVISION_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_PROVISION_API_H
