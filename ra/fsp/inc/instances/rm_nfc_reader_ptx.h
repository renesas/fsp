/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_NFC_READER_PTX
 * @{
 **********************************************************************************************************************/

#ifndef RM_NFC_READER_PTX_H_
#define RM_NFC_READER_PTX_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "ptx_IOT_READER.h"
#include "ptxNDEF.h"
#include "ptxNativeTag_T2T.h"
#include "ptxNativeTag_T3T.h"
#include "ptxNativeTag_T4T.h"
#include "ptxNativeTag_T5T.h"
#include "ptxPLAT_GPIO.h"
#include "ptxPLAT_SPI.h"
#include "ptxPLAT_TIMER.h"
#include "ptxPERIPH_APPTIMER.h"
#include "rm_nfc_reader_ptx_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** NFC Native-tag Optional Parameters for Read Operation */
typedef union u_nfc_reader_ptx_native_tag_read_params
{
    struct
    {
        uint8_t t2t_block_number;                     ///< Type 2 tag block number for Native-Tag Read/Write functions
    };
    struct
    {
        ptxNativeTag_T3T_Services_t t3t_service_info; ///< Type 3 tag service code information for Native-Tag Check/Update functions
        ptxNativeTag_T3T_Blocks_t   t3t_block_info;   ///< Type 3 tag block information for Native-Tag Check/Update functions
        uint8_t * t3t_nfcid2;                         ///< Type 3 tag NFCID2 identifier for Native-Tag Check/Update functions
        uint8_t   t3t_nfcid2_len;                     ///< Type 3 tag NFCID2 identifier length for Native-Tag Check/Update functions
    };
    struct
    {
        uint32_t t4t_file_offset;                     ///< Type 4 tag file offset for Native-Tag Read/Update (and ODO) functions
        uint8_t  t4t_data_num_bytes;                  ///< Type 4 tag number of expected response bytes for Native-Tag Read (and ODO) functions
    };
    struct
    {
        uint8_t  t5t_option_flag;                     ///< Type 5 tag command option flag for Native-Tag Read/Write/Select/Lock/Sleep functions
        uint16_t t5t_block_number;                    ///< Type 5 tag starting block number for Native-Tag Read function
        uint8_t  t5t_num_blocks;                      ///< Type 5 tag number of blocks to read for Native-Tag Read function
    };
} nfc_reader_ptx_native_tag_read_params_t;

/** NFC Native-tag Optional Parameters for Write Operation */
typedef union u_nfc_reader_ptx_native_tag_write_params
{
    struct
    {
        uint8_t t2t_block_number;                     ///< Type 2 tag block number for Native-Tag Read/Write functions
    };
    struct
    {
        ptxNativeTag_T3T_Services_t t3t_service_info; ///< Type 3 tag service code information for Native-Tag Check/Update functions
        ptxNativeTag_T3T_Blocks_t   t3t_block_info;   ///< Type 3 tag block information for Native-Tag Check/Update functions
        uint8_t * t3t_nfcid2;                         ///< Type 3 tag NFCID2 identifier for Native-Tag Check/Update functions
        uint8_t   t3t_nfcid2_len;                     ///< Type 3 tag NFCID2 identifier length for Native-Tag Check/Update functions
    };
    struct
    {
        uint32_t t4t_file_offset;                     ///< Type 4 tag file offset for Native-Tag Read/Update (and ODO) functions
    };
    struct
    {
        uint16_t t5t_block_number;                    ///< Type 5 tag starting block number for Native-Tag Write function
        uint8_t  t5t_option_flag;                     ///< Type 5 tag command option flag for Native-Tag Read/Write/Select/Lock/Sleep functions
    };
} nfc_reader_ptx_native_tag_write_params_t;

/** NFC Native-tag Optional Parameters for Select Operation */
typedef union u_nfc_reader_ptx_native_tag_select_params
{
    struct
    {
        uint8_t t2t_sector_number;     ///< Type 2 tag sector number for Native-Tag Select function
    };
    struct
    {
        uint32_t t4t_file_offset;      ///< Type 4 tag file offset for Native-Tag Read/Update (and ODO) functions
        uint8_t  t4t_apdu_byte_1;      ///< Type 4 tag APDU (command header) first byte for Native-Tag Select function
        uint8_t  t4t_apdu_byte_2;      ///< Type 4 tag APDU (command header) second byte for Native-Tag Select function
        uint8_t  t4t_expected_len;     ///< Type 4 tag expected length of response for Native-Tag Select function
    };
    struct
    {
        uint8_t   t5t_option_flag;     ///< Type 5 tag command option flag for Native-Tag Read/Write/Select/Lock/Sleep functions
        uint8_t * t5t_uid;             ///< Type 5 tag UID identifier for Native-Tag Select/Sleep functions
        uint8_t   t5t_uid_len;         ///< Type 5 tag UID identifier length for Native-Tag Select/Sleep functions
    };
} nfc_reader_ptx_native_tag_select_params_t;

/** NFC Native-tag Optional Parameters for Lock Operation */
typedef union u_nfc_reader_ptx_native_tag_lock_params
{
    struct
    {
        uint8_t  t5t_option_flag;      ///< Type 5 tag command option flag for Native-Tag Read/Write/Select/Lock/Sleep functions
        uint16_t t5t_block_number;     ///< Type 5 tag starting block number for Native-Tag Lock function
    };
} nfc_reader_ptx_native_tag_lock_params_t;

/** NFC Native-tag Optional Parameters for Sleep Operation */
typedef union u_nfc_reader_ptx_native_tag_sleep_params
{
    struct
    {
        uint8_t   t5t_option_flag;     ///< Type 5 tag command option flag for Native-Tag Read/Write/Select/Lock/Sleep functions
        uint8_t * t5t_uid;             ///< Type 5 tag UID identifier for Native-Tag Select/Sleep functions
        uint8_t   t5t_uid_len;         ///< Type 5 tag UID identifier length for Native-Tag Select/Sleep functions
    };
} nfc_reader_ptx_native_tag_sleep_params_t;

/** NFC Native-tag Tag Type Flag */
typedef enum e_nfc_reader_ptx_native_tag_type
{
    NFC_READER_PTX_NATIVE_TAG_TYPE_NONE = 0,         ///< No tag was selected for Native-Tag add-on APIs
    NFC_READER_PTX_NATIVE_TAG_TYPE_T2T  = (1U << 0), ///< Type 2 tag bit mask for Native-Tag add-on APIs
    NFC_READER_PTX_NATIVE_TAG_TYPE_T3T  = (1U << 1), ///< Type 3 tag bit mask for Native-Tag add-on APIs
    NFC_READER_PTX_NATIVE_TAG_TYPE_T4T  = (1U << 2), ///< Type 4 tag bit mask for Native-Tag add-on APIs
    NFC_READER_PTX_NATIVE_TAG_TYPE_T5T  = (1U << 3), ///< Type 5 tag bit mask for Native-Tag add-on APIs
} nfc_reader_ptx_native_tag_type_t;

/** NFC NDEF data exchange flags */
typedef enum e_nfc_reader_ptx_ndef_read_write
{
    NFC_READER_PTX_NDEF_WRITE = 0x01,  ///< Write flag for NDEF data exchange
    NFC_READER_PTX_NDEF_READ  = 0x02,  ///< Read flag for NDEF data exchange
} nfc_reader_ptx_ndef_read_write_t;

/** NFC power mode flags */
typedef enum e_nfc_reader_ptx_power_mode
{
    NFC_READER_PTX_ACTIVE_MODE  = 0x00, ///< Active mode (default), all features enabled
    NFC_READER_PTX_STANDBY_MODE = 0x01, ///< Stand-by mode, most features disabled for low power
} nfc_reader_ptx_power_mode_t;

/** NFC state machine status */
typedef enum e_nfc_reader_ptx_state
{
    NFC_READER_PTX_IDLE       = 0x01,  ///< Idle state before starting discovery
    NFC_READER_PTX_POLLING    = 0x02,  ///< Polling state for discovering tags
    NFC_READER_PTX_DISCOVERED = 0x03,  ///< Discovered state for tags that were found
    NFC_READER_PTX_ACTIVATED  = 0x04,  ///< Activated state for activating a discovered tag
} nfc_reader_ptx_state_t;

/** NFC de-activation return state */
typedef enum e_nfc_reader_ptx_return_state
{
    NFC_READER_PTX_RETURN_IDLE               = PTX_IOTRD_RF_DEACTIVATION_TYPE_IDLE,               ///< Rf-Deactivation Type 0 - Turn off RF-field
    NFC_READER_PTX_RETURN_DISCOVER           = PTX_IOTRD_RF_DEACTIVATION_TYPE_DISCOVER,           ///< Rf-Deactivation Type 1 - Restart RF-Discovery
    NFC_READER_PTX_RETURN_SLEEP              = PTX_IOTRD_RF_DEACTIVATION_TYPE_SLEEP,              ///< Rf-Deactivation Type 2 - Put remote device to sleep
    NFC_READER_PTX_RETURN_SLEEP_NON_BLOCKING = PTX_IOTRD_RF_DEACTIVATION_TYPE_SLEEP_NON_BLOCKING, ///< Rf-Deactivation Type 3 - Put remote device to sleep (non-blocking)
    NFC_READER_PTX_RETURN_NO_RF_RESET        = PTX_IOTRD_RF_DEACTIVATION_TYPE_NO_RF_RESET,        ///< Rf-Deactivation Type 4 - Common RF Deactivate but no Field Reset
    NFC_READER_PTX_RETURN_IDLE_PROTOCOL      = PTX_IOTRD_RF_DEACTIVATION_TYPE_IDLE_PROTOCOL,      ///< Rf-Deactivation Type 5 - Use protocol-specific Deactivation, IDLE afterwards
    NFC_READER_PTX_RETURN_DISCOVER_PROTOCOL  = PTX_IOTRD_RF_DEACTIVATION_TYPE_DISCOVER_PROTOCOL,  ///< Rf-Deactivation Type 6 - Use protocol-specific Deactivation, RF-Discovery started afterwards
} nfc_reader_ptx_return_state_t;

/** NFC data exchange packet parameters */
typedef struct st_nfc_reader_ptx_data_info
{
    uint8_t * p_tx_buf;                ///< Pointer to buffer holding data to send.
    uint32_t  tx_length;               ///< Length of data to send.
    uint8_t * p_rx_buf;                ///< Pointer to buffer for data to receive.
    uint32_t  rx_length;               ///< Length of data to receive.
} nfc_reader_ptx_data_info_t;

/** NFC Configuration */
typedef struct st_nfc_reader_ptx_cfg
{
    bool    poll_type_a;                             ///< Flag to indicate enabling discovery for Type-A tags.
    bool    poll_type_b;                             ///< Flag to indicate enabling discovery for Type-B tags.
    bool    poll_type_f;                             ///< Flag to indicate enabling discovery for Type-F tags.
    bool    poll_type_v;                             ///< Flag to indicate enabling discovery for Type-V tags.
    uint8_t device_limit;                            ///< Defines the maximum number of devices that can be connected at once.
    uint8_t discover_mode;                           ///< Set polling mode, where 0 = Regular Polling, 1 = Low-Power Card Detection (LPCD), 2-255 = LPCD with every n-th Cycle Regular Polling

    uint32_t idle_time_ms;                           ///< RF-Discovery Loop. Idle time between polling cycles in milliseconds.
    uint8_t  temp_sensor_calibrate;                  ///< Flag to enable/disable temperature sensor calibration
    uint8_t  temp_sensor_shutdown;                   ///< Expected thermal shutdown threshold value.
    uint8_t  temp_sensor_ambient;                    ///< Ambient temperature at which temperature sensor calibration takes place.

    const bsp_io_port_pin_t   interrupt_pin;         ///< Interrupt pin for NFC chip to signal for communication.
    ptxIoTRd_t              * iot_reader_context;    ///< Instance of the NFC SDK IoT Reader main structure.
    rm_comms_instance_t     * p_comms_instance_ctrl; ///< Pointer to the NFC module's Comms instance.
    ioport_instance_t       * p_gpio_context;        ///< Pointer to the NFC module's GPIO instance.
    external_irq_instance_t * p_irq_context;         ///< Pointer to the NFC module's SPI external interrupt instance.
    timer_instance_t        * p_timer_context;       ///< Pointer to the NFC module's sleep timer instance.
    timer_instance_t        * p_app_timer;           ///< Pointer to the NFC module's Transparent Data Channel (TDC) timer instance.
    ptxNDEF_t               * p_ndef_context;        ///< Pointer to the optional NDEF API context.
} nfc_reader_ptx_cfg_t;

/** NFC_READER_PTX private control block. DO NOT MODIFY. */
typedef struct st_nfc_reader_ptx_instance_ctrl
{
    uint8_t                ndef_work_buf[NFC_READER_PTX_NDEF_WORK_BUF_SIZE]; ///< Buffer for NDEF internal data exchange.
    uint32_t               open;                                             ///< Flag to indicate if NFC has been opened.
    uint32_t               ndef_open;                                        ///< Flag to indicate if NFC NDEF has been initialized.
    uint32_t               native_tag_open;                                  ///< Flag to indicate if NFC Native-Tag has been initialized.
    nfc_reader_ptx_state_t state_flag;                                       ///< Flag to track Idle/discovered/activated.

#if (RM_NFC_READER_NATIVE_TAG_SUPPORT)
    ptxNativeTag_T2T_t            t2t_comp;                                  ///< Type 2 tag component for Native-Tag add-on API
    ptxNativeTag_T2T_InitParams_t t2t_params;                                ///< Type 2 tag parameters for Native-Tag add-on API component
    ptxNativeTag_T3T_t            t3t_comp;                                  ///< Type 3 tag component for Native-Tag add-on API
    ptxNativeTag_T3T_InitParams_t t3t_params;                                ///< Type 3 tag parameters for Native-Tag add-on API component
    ptxNativeTag_T4T_t            t4t_comp;                                  ///< Type 3 tag component for Native-Tag add-on API
    ptxNativeTag_T4T_InitParams_t t4t_params;                                ///< Type 3 tag parameters for Native-Tag add-on API component
    ptxNativeTag_T5T_t            t5t_comp;                                  ///< Type 3 tag component for Native-Tag add-on API
    ptxNativeTag_T5T_InitParams_t t5t_params;                                ///< Type 3 tag parameters for Native-Tag add-on API component

    uint8_t enabled_tag_mask;                                                ///< Bitmask of which tag types were initialized
#endif

    nfc_reader_ptx_cfg_t const * p_cfg;                                      ///< Pointer to p_cfg for NFC.
} nfc_reader_ptx_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_NFC_READER_PTX_Open(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                 nfc_reader_ptx_cfg_t const * const     p_cfg);
fsp_err_t RM_NFC_READER_PTX_DiscoveryStart(nfc_reader_ptx_instance_ctrl_t * const p_ctrl);
fsp_err_t RM_NFC_READER_PTX_StatusGet(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                      ptxIoTRd_StatusType_t                  status_type,
                                      uint8_t * const                        p_status);
fsp_err_t RM_NFC_READER_PTX_CardRegistryGet(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                            ptxIoTRd_CardRegistry_t             ** pp_card_registry);
fsp_err_t RM_NFC_READER_PTX_CardActivate(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                         ptxIoTRd_CardParams_t * const          p_card_params,
                                         ptxIoTRd_CardProtocol_t                protocol);
fsp_err_t RM_NFC_READER_PTX_DataExchange(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                         nfc_reader_ptx_data_info_t * const     p_data_info);
fsp_err_t RM_NFC_READER_PTX_ReaderDeactivation(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                               nfc_reader_ptx_return_state_t          return_state);
fsp_err_t RM_NFC_READER_PTX_PowerModeSet(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                         nfc_reader_ptx_power_mode_t            power_mode);
fsp_err_t RM_NFC_READER_PTX_NDEF_Init(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                      nfc_reader_ptx_data_info_t * const     p_data_info);
fsp_err_t RM_NFC_READER_PTX_NDEF_DataExchange(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                              uint8_t                              * p_ndef_message,
                                              uint32_t                               message_length,
                                              nfc_reader_ptx_ndef_read_write_t       ndef_read_write_flag);
fsp_err_t RM_NFC_READER_PTX_NDEF_Lock(nfc_reader_ptx_instance_ctrl_t * const p_ctrl);
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Init(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                            nfc_reader_ptx_data_info_t * const     p_data_info,
                                            uint8_t                                tag_select);
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Read(nfc_reader_ptx_instance_ctrl_t * const          p_ctrl,
                                            nfc_reader_ptx_native_tag_read_params_t * const p_read_params,
                                            nfc_reader_ptx_native_tag_type_t                tag_type,
                                            nfc_reader_ptx_data_info_t * const              p_data_info);
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Write(nfc_reader_ptx_instance_ctrl_t * const           p_ctrl,
                                             nfc_reader_ptx_native_tag_write_params_t * const p_write_params,
                                             nfc_reader_ptx_native_tag_type_t                 tag_type,
                                             nfc_reader_ptx_data_info_t * const               p_data_info);
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Select(nfc_reader_ptx_instance_ctrl_t * const            p_ctrl,
                                              nfc_reader_ptx_native_tag_select_params_t * const p_select_params,
                                              nfc_reader_ptx_native_tag_type_t                  tag_type,
                                              nfc_reader_ptx_data_info_t * const                p_data_info);
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Lock(nfc_reader_ptx_instance_ctrl_t * const          p_ctrl,
                                            nfc_reader_ptx_native_tag_lock_params_t * const p_lock_params,
                                            nfc_reader_ptx_native_tag_type_t                tag_type,
                                            nfc_reader_ptx_data_info_t * const              p_data_info);
fsp_err_t RM_NFC_READER_PTX_Native_Tag_Sleep(nfc_reader_ptx_instance_ctrl_t * const           p_ctrl,
                                             nfc_reader_ptx_native_tag_sleep_params_t * const p_sleep_params,
                                             nfc_reader_ptx_native_tag_type_t                 tag_type,
                                             nfc_reader_ptx_data_info_t * const               p_data_info);

fsp_err_t RM_NFC_READER_PTX_Close(nfc_reader_ptx_instance_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_NFC_READER_PTX_H_ */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NFC_READER_PTX)
 **********************************************************************************************************************/
