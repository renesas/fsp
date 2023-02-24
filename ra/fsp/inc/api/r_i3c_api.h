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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup I3C_API I3C Interface
 * @brief Interface for I3C.
 *
 * @section I3C_API_SUMMARY Summary
 * @brief The I3C interface provides APIs and definitions for I3C communication.
 *
 * @section I3C_API_INSTANCES Known Implementations
 * @ref I3C
 * @{
 **********************************************************************************************************************/

#ifndef R_I3C_API_H
#define R_I3C_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Common Command Codes defined by MIPI I3C Specification v1.1. */
typedef enum e_i3c_common_command_code
{
    /* Broadcast Common Command Codes */
    I3C_CCC_BROADCAST_ENEC     = (0x00), ///< Enable Slave initiated events.
    I3C_CCC_BROADCAST_DISEC    = (0x01), ///< Disable Slave initiated events.
    I3C_CCC_BROADCAST_ENTAS0   = (0x02), ///< Enter Activity State 0.
    I3C_CCC_BROADCAST_ENTAS1   = (0x03), ///< Enter Activity State 1.
    I3C_CCC_BROADCAST_ENTAS2   = (0x04), ///< Enter Activity State 2.
    I3C_CCC_BROADCAST_ENTAS3   = (0x05), ///< Enter Activity State 3.
    I3C_CCC_BROADCAST_RSTDAA   = (0x06), ///< Reset Dynamic Address Assignment.
    I3C_CCC_BROADCAST_ENTDAA   = (0x07), ///< Enter Dynamic Address Assignment.
    I3C_CCC_BROADCAST_DEFSVLS  = (0x08), ///< Define List of Slaves.
    I3C_CCC_BROADCAST_SETMWL   = (0x09), ///< Set Max Write Length.
    I3C_CCC_BROADCAST_SETMRL   = (0x0A), ///< Set Max Read Length.
    I3C_CCC_BROADCAST_ENTTM    = (0x0B), ///< Enter Test Mode.
    I3C_CCC_BROADCAST_ENTHDR0  = (0x20), ///< Enter HDR Mode 0.
    I3C_CCC_BROADCAST_ENTHDR1  = (0x21), ///< Enter HDR Mode 1.
    I3C_CCC_BROADCAST_ENTHDR2  = (0x22), ///< Enter HDR Mode 2.
    I3C_CCC_BROADCAST_ENTHDR3  = (0x23), ///< Enter HDR Mode 3.
    I3C_CCC_BROADCAST_ENTHDR4  = (0x24), ///< Enter HDR Mode 4 (Reserved for future definition).
    I3C_CCC_BROADCAST_ENTHDR5  = (0x25), ///< Enter HDR Mode 5 (Reserved for future definition).
    I3C_CCC_BROADCAST_ENTHDR6  = (0x26), ///< Enter HDR Mode 6 (Reserved for future definition).
    I3C_CCC_BROADCAST_ENTHDR7  = (0x27), ///< Enter HDR Mode 7 (Reserved for future definition).
    I3C_CCC_BROADCAST_SETXTIME = (0x28), ///< Set Exchange Timing Info.
    I3C_CCC_BROADCAST_SETAASA  = (0x29), ///< Set All Addresses to Static Address.

    /* Direct Common Command Codes */
    I3C_CCC_DIRECT_ENEC      = (0x80),   ///< Enable Slave initiated events.
    I3C_CCC_DIRECT_DISEC     = (0x81),   ///< Disable Slave initiated events.
    I3C_CCC_DIRECT_ENTAS0    = (0x82),   ///< Enter Activity State 0.
    I3C_CCC_DIRECT_ENTAS1    = (0x83),   ///< Enter Activity State 1.
    I3C_CCC_DIRECT_ENTAS2    = (0x84),   ///< Enter Activity State 2.
    I3C_CCC_DIRECT_ENTAS3    = (0x85),   ///< Enter Activity State 3.
    I3C_CCC_DIRECT_RSTDAA    = (0x86),   ///< Reset Dynamic Address Assignment.
    I3C_CCC_DIRECT_SETDASA   = (0x87),   ///< Set Dynamic Address from Static Address.
    I3C_CCC_DIRECT_SETNEWDA  = (0x88),   ///< Set New Dynamic Address.
    I3C_CCC_DIRECT_SETMWL    = (0x89),   ///< Set Max Write Length.
    I3C_CCC_DIRECT_SETMRL    = (0x8A),   ///< Set Max Read Length.
    I3C_CCC_DIRECT_GETMWL    = (0x8B),   ///< Get Max Write Length.
    I3C_CCC_DIRECT_GETMRL    = (0x8C),   ///< Get Max Read Length.
    I3C_CCC_DIRECT_GETPID    = (0x8D),   ///< Get Provisional ID.
    I3C_CCC_DIRECT_GETBCR    = (0x8E),   ///< Get Bus Characteristic Register.
    I3C_CCC_DIRECT_GETDCR    = (0x8F),   ///< Get Device Characteristic Register.
    I3C_CCC_DIRECT_GETSTATUS = (0x90),   ///< Get Device Status.
    I3C_CCC_DIRECT_GETACCMST = (0x91),   ///< Get Accept Mastership.
    I3C_CCC_DIRECT_GETMXDS   = (0x94),   ///< Get Max Data Speed.
    I3C_CCC_DIRECT_SETXTIME  = (0x98),   ///< Set Exchange Timing Information.
    I3C_CCC_DIRECT_GETXTIME  = (0x99),   ///< Get Exchange Timing Information.
} i3c_common_command_code_t;

/** I3C Events that result in a callback. */
typedef enum e_i3c_event
{
    /** Events that only occur in Master mode. */

    /**
     * A Slave device has finished writing its PID, BCR, and DCR. This information is provided in
     * @ref i3c_callback_args_t::p_slave_info.
     */
    I3C_EVENT_ENTDAA_ADDRESS_PHASE,
    I3C_EVENT_IBI_READ_COMPLETE,       ///< An IBI has successfully been read.

    /**
     * There is no more space in the IBI read buffer. The application may provide another buffer by calling
     * @ref i3c_api_t::ibiRead.
     */
    I3C_EVENT_IBI_READ_BUFFER_FULL,

    /** Events that only occur in Slave mode. */

    /**
     * There is no more space in the read buffer. The application may provide another buffer by calling
     * @ref i3c_api_t::read.
     */
    I3C_EVENT_READ_BUFFER_FULL,
    I3C_EVENT_IBI_WRITE_COMPLETE,          ///< A IBI was written successfully.
    I3C_EVENT_HDR_EXIT_PATTERN_DETECTED,   ///< The HDR exit pattern was detected on the bus.

    /** Events that are common to Master and Slave mode. */

    I3C_EVENT_ADDRESS_ASSIGNMENT_COMPLETE, ///< Dynamic Address Assignment has completed.
    I3C_EVENT_COMMAND_COMPLETE,            ///< A command was completed.
    I3C_EVENT_WRITE_COMPLETE,              ///< A write transfer has completed.
    I3C_EVENT_READ_COMPLETE,               ///< A read transfer has completed.
    I3C_EVENT_TIMEOUT_DETECTED,            ///< SCL is stuck at the logic high or logic low level during a transfer.
    I3C_EVENT_INTERNAL_ERROR,              ///< An internal error occurred.
} i3c_event_t;

/** The type of device. */
typedef enum e_i3c_type
{
    /** The main master starts in master mode and is responsible for configuring the bus. */
    I3C_DEVICE_TYPE_MAIN_MASTER,

    /** A slave device listens to the bus for relevant I3C Commands (CCCs) sent by the current master, and responds accordingly.
     * Slave devices may also initiate In-band interrupts and Hot-Join requests. */
    I3C_DEVICE_TYPE_SLAVE,
} i3c_device_type_t;

/** Identifies the protocol for transferring data with the device on the bus. */
typedef enum e_i3c_device_protocol
{
    I3C_DEVICE_PROTOCOL_I2C,           ///< Transfers will use legacy I2C protocal with open-drain output at a reduced baudrate.
    I3C_DEVICE_PROTOCOL_I3C,           ///< Transfers will use I3C SDR mode.
} i3c_device_protocol_t;

/** Address Assignment Mode. */
typedef enum e_i3c_address_assignment_mode
{
    /**
     * Send the ENTDAA command to enter Dynamic Address Assignment mode and assign dynamic addresses in order, starting with the
     * starting device index. The procedure is completed after the specified number of devices have been configured. The callback will
     * be called after the PID, DCR, and BCR registers have been read for each device.
     */
    I3C_ADDRESS_ASSIGNMENT_MODE_ENTDAA = I3C_CCC_BROADCAST_ENTDAA,

    /* Send the SETDASA command to the device selected by the starting device index (Set the device count to 0). */
    I3C_ADDRESS_ASSIGNMENT_MODE_SETDASA = I3C_CCC_DIRECT_SETDASA,
} i3c_address_assignment_mode_t;

/** The type of In-Band Interrupt. */
typedef enum e_i3c_ibi_type
{
    I3C_IBI_TYPE_INTERRUPT,            ///< Application specific In-Band Interrupt for notifying the master when an event occurs.
    I3C_IBI_TYPE_HOT_JOIN,             ///< Request the master to perform the Dynamic Address Assignment process.
    I3C_IBI_TYPE_MASTERSHIP_REQUEST    ///< Request the master to give up control of the bus.
} i3c_ibi_type_t;

/** The current status of the slave device (See GETSTATUS in the MIPI I3C Specification v1.0). */
typedef struct s_i3c_device_status
{
    uint8_t pending_interrupt;         ///< Contains the interrupt number of any pending interrupt, or 0 if no interrupts are pending.
    uint8_t vendor_status;             ///< Reserved for vendor-specific meaning.
} i3c_device_status_t;

/** Device characteristics that define the I3C capabilities of a slave. */
typedef struct s_i3c_slave_info
{
    uint8_t pid[6];                    ///< Provisional ID.

    union
    {
        uint8_t bcr;                   ///< Bus Characteristics Register.

        struct
        {
            /**
             * Max Data Speed Limitation:
             * - No limitation.
             * - Limitation (If this is set, the master shall get the Max Data Speed using the GETMXDS command).
             */
            uint8_t max_data_speed_limitation : 1;

            /**
             * IBI Request Capable
             * - 0: Not Capable.
             * - 1: Capable.
             */
            uint8_t ibi_request_capable : 1;

            /**
             * IBI Payload:
             * - 0: No data byte follows the accepted IBI
             * - 1: Mandatory one or more data bytes follow the accepted IBI.
             */
            uint8_t ibi_payload : 1;

            /**
             * Offline Capable:
             * - 0: Not Capable.
             * - 1: Capable.
             */
            uint8_t offline_capable : 1;

            /**
             * Bridge Identifier:
             * - 0: Not a Bridge Device.
             * - 1: Is a Bridge Device.
             */
            uint8_t bridge_identifier : 1;
            uint8_t                   : 1; /* Reserved */

            /**
             * Device Role:
             * - 0: I3C Slave.
             * - 1: I3C Master (Device acting as the main master will set this to 1).
             * - 2: Reserved.
             * - 3: Reserved.
             */
            uint8_t device_role : 2;
        } bcr_b;
    };

    uint8_t dcr;                       ///< Device Characteristics Register.
} i3c_slave_info_t;

/**
 * Structure for configuring an entry in the device table when the driver is in master mode
 * (See @ref i3c_api_t::masterDeviceTableSet).
 */
typedef struct s_i3c_device_table_cfg
{
    uint8_t static_address;            ///< I3C Static address / I2C address for this device.

    /** Dynamic address for the device. This address will be assigned during Dynamic Address Assignment. */
    uint8_t dynamic_address;

    i3c_device_protocol_t device_protocol; ///< The protocol used to communicate with this device (I3C / I2C Legacy).
    bool ibi_accept;                       ///< Accept or reject IBI requests from this device.
    bool master_request_accept;            ///< Accept mastership requests from this device.

    /**
     * IBI requests from this device have a data payload.
     *
     * Note: When the device is configured using ENTDAA, the ibi_payload will automatically be updated
     *       based on the value of BCR.
     */
    bool ibi_payload;
} i3c_device_table_cfg_t;

/** Structure for configuring a slave address when the driver is in slave mode (See @ref i3c_api_t::deviceCfgSet). */
typedef struct s_i3c_slave_device_cfg
{
    uint8_t static_address;            ///< I3C Static address / I2C address for this device.

    /** Dynamic address for this device. Note that the dynamic address will automatically be updated when ENTDAA is
     * completed.*/
    uint8_t dynamic_address;

    i3c_slave_info_t slave_info;       ///< PID, BCR, and DCR registers for the device (Slave mode only).
} i3c_device_cfg_t;

/** Descriptor for completing CCC transfers. */
typedef struct s_i3c_command_descriptor
{
    uint8_t   command_code;            ///< Common Command Code for the transfer.
    uint8_t * p_buffer;                ///< Buffer for reading or writing data.
    uint32_t  length;                  ///< Length of the data portion of the command.
    bool      restart;                 ///< If true, issue a repeated-start after the transfer is completed.
    bool      rnw;                     ///< Set to true if the command type is Direct Get.
} i3c_command_descriptor_t;

/** Arguments that are passed to the user callback when an event occurs. */
typedef struct s_i3c_callback_args
{
    i3c_event_t              event;         ///< The type of event that has occurred.
    uint32_t                 event_status;  ///< Status flags associated with the event.
    uint32_t                 transfer_size; ///< Number of bytes transferred.
    i3c_slave_info_t const * p_slave_info;  ///< A pointer to the Characteristics Registers read during ENTDAA.
    uint8_t        dynamic_address;         ///< The dynamic address that was assigned to the slave during ENTDAA.
    i3c_ibi_type_t ibi_type;                ///< The type of IBI that has been received.
    uint8_t        ibi_address;             ///< The address of the device that sent the IBI.
    uint8_t        command_code;            ///< The command code of the received command.
    void const   * p_context;               ///< User defined context.
} i3c_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_i3c_cfg
{
    /** Select a channel corresponding to the channel number of the hardware. */
    uint32_t channel;

    /** The type of device. */
    i3c_device_type_t device_type;

    /** Pointer to the user callback. */
    void (* p_callback)(i3c_callback_args_t const * const p_args);

    void const * p_context;            ///< Pointer to the user-provided context

    /** Pointer to extended configuration. */
    void const * p_extend;
} i3c_cfg_t;

/** I3C control block.  Allocate an instance specific control block to pass into the I3C API calls.
 * @par Implemented as
 * - i3c_instance_ctrl_t
 */
typedef void i3c_ctrl_t;

/** I3C functions implemented at the HAL layer will follow this API. */
typedef struct st_i3c_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_I3C_Open()
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(i3c_ctrl_t * const p_ctrl, i3c_cfg_t const * const p_cfg);

    /**
     * Enable the I3C device.
     *
     * @par Implemented as
     * - @ref R_I3C_Enable()
     *
     * @param[in]   p_ctrl     Control block set in @ref i3c_api_t::open call for this instance.
     */
    fsp_err_t (* enable)(i3c_ctrl_t * const p_ctrl);

    /**
     * Set the configuration of this device.
     *
     * @par Implemented as
     * - @ref R_I3C_DeviceCfgSet()
     *
     * @param[in]   p_ctrl       Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   p_device_cfg Pointer to device configuration.
     */
    fsp_err_t (* deviceCfgSet)(i3c_ctrl_t * const p_ctrl, i3c_device_cfg_t const * const p_device_cfg);

    /**
     * Set the configuration for the device at the given index in the device table. The configuration will be used by transfers
     * when it is selected by @ref deviceSelect.
     *
     * Note: This function is not used in slave mode.
     *
     * @par Implemented as
     * - @ref R_I3C_MasterDeviceTableSet()
     *
     * @param[in]   p_ctrl             Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   device_index       Index into the device table.
     * @param[in]   p_device_table_cfg Pointer to the table settings for the entry in the master device table.
     */
    fsp_err_t (* masterDeviceTableSet)(i3c_ctrl_t * const p_ctrl, uint32_t device_index,
                                       i3c_device_table_cfg_t const * const p_device_table_cfg);

    /**
     * In master mode, select the device for the next transfer.
     *
     * Note: This function is not used in slave mode.
     *
     * @par Implemented as
     * - @ref R_I3C_DeviceSelect()
     *
     * @param[in]   p_ctrl          Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   device_index    Index into the device table.
     * @param[in]   bitrate_setting The bitrate settings for the selected device.
     */
    fsp_err_t (* deviceSelect)(i3c_ctrl_t * const p_ctrl, uint32_t device_index, uint32_t bitrate_mode);

    /** Start Dynamic Address Assignment by sending either the ENTDAA or SETDASA command See @ref i3c_address_assignment_mode_t
     * for more information.
     *
     * Note: This function is not used in slave mode.
     *
     * @par Implemented as
     * - @ref R_I3C_DynamicAddressAssignmentStart()
     *
     * @param[in]   p_ctrl                  Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   address_assignment_mode The command to use for Dynamic Address Assignment.
     * @param[in]   starting_device_index   The device index that will be used to assign the first device during Dynamic Address Assignment.
     * @param[in]   device_count            The number of devices to assign (Only used with @ref I3C_ADDRESS_ASSIGNMENT_MODE_ENTDAA).
     */
    fsp_err_t (* dynamicAddressAssignmentStart)(i3c_ctrl_t * const p_ctrl,
                                                i3c_address_assignment_mode_t address_assignment_mode,
                                                uint32_t starting_device_index, uint32_t device_count);

    /**
     * Set the status returned to the master in response to a GETSTATUS command.
     *
     * Note: This function is not used in master mode.
     *
     * @par Implemented as
     * - @ref R_I3C_SlaveStatusSet()
     *
     * @param[in]   p_ctrl          Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   device_status   New status settings for responding to the GETSTATUS command code.
     */
    fsp_err_t (* slaveStatusSet)(i3c_ctrl_t * const p_ctrl, i3c_device_status_t device_status);

    /**
     * Send a broadcast or directed command to slave devices on the bus.
     *
     * Note: This function is not used in slave mode.
     *
     * @par Implemented as
     * - @ref R_I3C_CommandSend()
     *
     * @param[in]   p_ctrl               Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   p_command_descriptor A descriptor for executing the command.
     */
    fsp_err_t (* commandSend)(i3c_ctrl_t * const p_ctrl, i3c_command_descriptor_t * p_command_descriptor);

    /**
     * In master mode: Start a write transfer. When the transfer is completed send a stop condition or a repeated-start.
     * In slave mode:  Set the write buffer and configure the number of bytes that will be transferred before the the transfer
     *                 is ended by the slave via the 'T' bit or by the master issueing a stop condition.
     *
     * @par Implemented as
     * - @ref R_I3C_Write()
     *
     * @param[in]   p_ctrl     Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   p_data     Pointer to a buffer to write.
     * @param[in]   length     Number of bytes to transfer.
     * @param[in]   restart    If true, issue a repeated-start after the transfer is completed (Master only).
     */
    fsp_err_t (* write)(i3c_ctrl_t * const p_ctrl, uint8_t const * const p_data, uint32_t length, bool restart);

    /**
     * In master mode: Start a read transfer. When the transfer is completed, send a stop condition or a repeated-start.
     * In slave mode:  Set the read buffer for storing data read during the transfer. When the buffer is full, the application
     *                 will receive a callback requesting a new read buffer. If no buffer is provided by the application, the driver will
     *                 discard any remaining bytes read during the transfer.
     *
     * @par Implemented as
     * - @ref R_I3C_Read()
     *
     * @param[in]   p_ctrl     Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   p_data     Pointer to a buffer to store the bytes read during the transfer.
     * @param[in]   length     Number of bytes to transfer.
     * @param[in]   restart    If true, issue a repeated-start after the transfer is completed (Master only).
     */
    fsp_err_t (* read)(i3c_ctrl_t * const p_ctrl, uint8_t * const p_data, uint32_t length, bool restart);

    /**
     * Initiate an IBI write operation.
     *
     * Note: This function is not used in master mode.
     *
     * @par Implemented as
     * - @ref R_I3C_IbiWrite()
     *
     * @param[in]   p_ctrl     Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   p_data     Pointer to a buffer to start the bytes read during the transfer.
     * @param[in]   length     Number of bytes to transfer.
     */
    fsp_err_t (* ibiWrite)(i3c_ctrl_t * const p_ctrl, i3c_ibi_type_t ibi_type, uint8_t const * const p_data,
                           uint32_t length);

    /**
     * Set the read buffer for storing received IBI data (This function is not used in slave mode).
     *
     * @par Implemented as
     * - @ref R_I3C_IbiRead()
     *
     * @param[in]   p_ctrl     Control block set in @ref i3c_api_t::open call for this instance.
     * @param[in]   p_data     Pointer to a buffer to store the bytes read during the transfer.
     * @param[in]   length     Number of bytes to transfer.
     */
    fsp_err_t (* ibiRead)(i3c_ctrl_t * const p_ctrl, uint8_t * const p_data, uint32_t length);

    /** Allows driver to be reconfigured and may reduce power consumption.
     * @par Implemented as
     * - @ref R_I3C_Close()
     *
     * @param[in]   p_ctrl     Control block set in @ref i3c_api_t::open call for this instance.
     */
    fsp_err_t (* close)(i3c_ctrl_t * const p_ctrl);
} i3c_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_i3c_instance
{
    i3c_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    i3c_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    i3c_api_t const * p_api;           ///< Pointer to the API structure for this instance
} i3c_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup I3C_API)
 **********************************************************************************************************************/
