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

/** NFC NDEF data exchange flags */
typedef enum e_nfc_reader_ptx_ndef_read_write
{
    NFC_READER_PTX_NDEF_WRITE = 0x01,  ///< Write flag for NDEF data exchange
    NFC_READER_PTX_NDEF_READ  = 0x02,  ///< Read flag for NDEF data exchange
} nfc_reader_ptx_ndef_read_write_t;

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
    nfc_reader_ptx_state_t state_flag;                                       ///< Flag to track Idle/discovered/activated.

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
fsp_err_t RM_NFC_READER_PTX_NDEF_Init(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                      nfc_reader_ptx_data_info_t * const     p_data_info);
fsp_err_t RM_NFC_READER_PTX_NDEF_DataExchange(nfc_reader_ptx_instance_ctrl_t * const p_ctrl,
                                              uint8_t                              * p_ndef_message,
                                              uint32_t                               message_length,
                                              nfc_reader_ptx_ndef_read_write_t       ndef_read_write_flag);
fsp_err_t RM_NFC_READER_PTX_NDEF_Lock(nfc_reader_ptx_instance_ctrl_t * const p_ctrl);

fsp_err_t RM_NFC_READER_PTX_Close(nfc_reader_ptx_instance_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_NFC_READER_PTX_H_ */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NFC_READER_PTX)
 **********************************************************************************************************************/
