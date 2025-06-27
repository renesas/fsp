/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

#include "r_usb_basic.h"
#include "r_usb_hcdc.h"
#include "r_usb_extern.h"
#include "r_usb_hcdc_driver.h"
#include "r_ether_api.h"
#include <stdlib.h>
#include "r_usb_hcdc_ecm.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define USB_HCDC_ECM_MAXIMUM_ETHERNET_FRAME_SIZE          (1514U)

#define USB_HCDC_ECM_INT_IN_RCV_BUF_SIZE                  (64)
#define USB_HCDC_ECM_DISCRIPTOR_BUF_SIZE                  (512)

#define USB_HCDC_ECM_USB_MAX_PACKET_SIZE_FS               (64)
#define USB_HCDC_ECM_USB_MAX_PACKET_SIZE_HS               (512)
#define USB_HCDC_ECM_USB_CALLBACK_QUEUE_SIZE              (10)
#define USB_HCDC_ECM_USB_WRITE_COMPLETE_QUEUE_SIZE        (1)
#define USB_HCDC_ECM_USB_EVENT_PROCESS_TASK_STACK_SIZE    (1024)
#define USB_HCDC_ECM_USB_EVENT_PROCESS_TASK_PRIORITY      configMAX_PRIORITIES - 3

#define USB_HCDC_ECM_CDC_SUB_CLASS_ACM                    (0x02)
#define USB_HCDC_ECM_CDC_SUB_CLASS_ECM                    (0x06)
#define USB_HCDC_ECM_CDC_READ_DATA_LEN                    USB_HCDC_ECM_MAXIMUM_ETHERNET_FRAME_SIZE * 2
#define USB_HCDC_ECM_CDC_INTERRUPT_READ_DATA_LEN          (16)

#define USB_HCDC_ECM_LANG_ID_USA                          (0x0409)
#define USB_HCDC_ECM_DESCRITOR_TYPE_CS_INTERFACE          (0x24)
#define USB_HCDC_ECM_DESCRITOR_SUBTYPE_NETWORKING         (0x0F)
#define USB_HCDC_ECM_DESCRITOR_SUBTYPE_INDEX              (2)
#define USB_HCDC_ECM_DESCRITOR_IMACADDRESS_INDEX          (3)
#define USB_HCDC_ECM_NUM_OF_MACADDRESS_BYTES              (6)
#define USB_HCDC_ECM_SET_ETHERNET_PACKET_FILTER           (0x4300)

#define USB_HCDC_ECM_VALUE_9                              (9)
#define USB_HCDC_ECM_VALUE_0001H                          (0x0001)
#define USB_HCDC_ECM_VALUE_0002H                          (0x0002)
#define USB_HCDC_ECM_VALUE_0003H                          (0x0003)
#define USB_HCDC_ECM_VALUE_0012H                          (0x0012)
#define USB_HCDC_ECM_VALUE_001FH                          (0x001F)
#define USB_HCDC_ECM_VALUE_00FFH                          (0x00FF)

#define USB_HCDC_ECM_NO_WAIT_TIME                         (0)
#define USB_HCDC_ECM_VALUE_ZERO                           (0)

#define USB_HCDC_ECM_OPEN                                 (('U' << 24U) | ('H' << 16U) | ('C' << 8U) | ('E' << 0U))

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
void     usb_rtos_callback(usb_event_info_t * p_event_info, usb_hdl_t cur_task, usb_onoff_t usb_state);
uint16_t usb_hcdc_ecm_pre_check_config(uint8_t * table, uint16_t length);
uint16_t usb_hcdc_ecm_check_config(uint8_t * table, uint16_t length);

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
const ether_api_t g_ether_on_usb_ecm =
{
    .open            = R_USB_HCDC_ECM_Open,
    .close           = R_USB_HCDC_ECM_Close,
    .read            = R_USB_HCDC_ECM_Read,
    .bufferRelease   = R_USB_HCDC_ECM_BufferRelease,
    .rxBufferUpdate  = R_USB_HCDC_ECM_RxBufferUpdate,
    .write           = R_USB_HCDC_ECM_Write,
    .linkProcess     = R_USB_HCDC_ECM_LinkProcess,
    .wakeOnLANEnable = R_USB_HCDC_ECM_WakeOnLANEnable,
    .txStatusGet     = R_USB_HCDC_ECM_TxStatusGet,
    .callbackSet     = R_USB_HCDC_ECM_CallbackSet,
};

static const uint8_t g_notification_networkconnection_connect[8] =
{
    0xA1,                              /* bmRequestType */
    0x00,                              /* bRequest */
    0x01,                              /* wValue (lo) */
    0x00,                              /* wValue (hi) */
    0x01,                              /* wIndex (lo) */
    0x00,                              /* wIndex (hi) */
    0x00,                              /* wLength (lo) */
    0x00                               /* wLength (hi) */
};

static const uint8_t g_notification_networkconnection_disconnect[8] =
{
    0xA1,                              /* bmRequestType */
    0x00,                              /* bRequest */
    0x00,                              /* wValue (lo) */
    0x00,                              /* wValue (hi) */
    0x01,                              /* wIndex (lo) */
    0x00,                              /* wIndex (hi) */
    0x00,                              /* wLength (lo) */
    0x00                               /* wLength (hi) */
};

typedef struct st_usb_ecm_target_process_item
{
    BaseType_t target_process_complete;
    uint8_t  * p_ecm_mac_address;
    uint8_t  * p_ecm_configuration_descriptor;
    uint8_t    start_of_sequence_number;
} usb_ecm_target_process_item_t;

static TaskHandle_t     xUsbEventProcessTaskHandle = NULL;
static QueueHandle_t    g_usb_write_complete_queue;
static QueueHandle_t    g_usb_callback_queue;
static uint16_t         g_i_mac_address;
static uint8_t          g_mac_address[6] = {0};
static ether_nic_info_t g_nic_info;

static usb_ecm_target_process_item_t g_target_info = {pdFALSE, NULL, NULL, 0};
#if (USB_CFG_DMA == USB_CFG_ENABLE)
static uint8_t g_snd_buf[USB_HCDC_ECM_CDC_READ_DATA_LEN] BSP_ALIGN_VARIABLE(4) = {USB_HCDC_ECM_VALUE_ZERO}; /* Send buffer (Bulk OUT) */
#endif /* (USB_CFG_DMA == USB_CFG_ENABLE) */
static uint8_t g_interrupt_in_rcv_buf[USB_HCDC_ECM_INT_IN_RCV_BUF_SIZE] BSP_ALIGN_VARIABLE(4) =
{
    USB_HCDC_ECM_VALUE_ZERO
};                                                                                                                    /* Receive buffer (Interrupt IN) */

static uint8_t g_usb_dummy = USB_HCDC_ECM_VALUE_ZERO;                                                                 /* dummy variable to send */
static uint8_t g_disc_buf[USB_HCDC_ECM_DISCRIPTOR_BUF_SIZE] BSP_ALIGN_VARIABLE(4)        = {USB_HCDC_ECM_VALUE_ZERO}; /* Receive buffer for GetDescriptor Request */
static uint8_t g_string_disc_buf[USB_HCDC_ECM_DISCRIPTOR_BUF_SIZE] BSP_ALIGN_VARIABLE(4) = {USB_HCDC_ECM_VALUE_ZERO}; /* Receive buffer for GetDescriptor Request */

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void prvUsbEventProcessTask(void * const pvParameters);

static void usb_hcdc_ecm_device_activation(usb_hcdc_ecm_instance_ctrl_t * const  p_hcdc_ecm_ctrl,
                                           usb_ctrl_t * const                    p_usb_ctrl,
                                           uint8_t                               device_address,
                                           usb_ecm_target_process_item_t * const p_target_process_info);
static void usb_hcdc_ecm_get_mac_address(uint8_t const * const table, uint8_t * const mac_address);
static void usb_hcdc_ecm_set_configuration(usb_instance_ctrl_t * const p_ctrl,
                                           uint8_t                     device_address,
                                           uint16_t                    config_value);
static void usb_hcdc_ecm_get_device_descriptor(usb_instance_ctrl_t * const p_ctrl, const uint8_t device_address);
static void usb_hcdc_ecm_get_configuration_descriptor(usb_instance_ctrl_t * const p_ctrl,
                                                      uint8_t                     device_address,
                                                      uint16_t                    length,
                                                      uint16_t                    config_index);
static void usb_hcdc_ecm_set_interface(usb_instance_ctrl_t * const p_ctrl, uint8_t device_address);
static void usb_hcdc_ecm_set_ethernet_packet_filter(usb_instance_ctrl_t * const p_ctrl, uint8_t device_address);
static void usb_hcdc_ecm_get_string_descriptor(usb_instance_ctrl_t * const p_ctrl,
                                               uint8_t                     device_address,
                                               uint16_t                    index);

void usb_hcdc_ecm_call_callback(usb_hcdc_ecm_instance_ctrl_t * p_instance_ctrl,
                                ether_callback_args_t        * p_callback_args);

/*******************************************************************************************************************//**
 * @addtogroup USB_HCDC_ECM
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * @brief After USB, CDC are reset in software.Implements @ref ether_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Channel opened successfully.
 * @retval  FSP_ERR_USB_NOT_OPEN                    USB module is not open..
 * @retval  FSP_ERR_ALREADY_OPEN                    RTOS internal error.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_Open (ether_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg)
{
    fsp_err_t    err;
    BaseType_t   xReturn = pdFAIL;
    usb_ctrl_t * p_usb_ctrl;
    usb_cfg_t  * p_usb_cfg;
    usb_hcdc_ecm_instance_ctrl_t * p_hcdc_ecm_ctrl = (usb_hcdc_ecm_instance_ctrl_t *) p_ctrl;
    usb_hcdc_ecm_extended_cfg_t  * p_extended_cfg;

    /* Check argument */
#if (USB_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_hcdc_ecm_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ASSERT(p_cfg->p_extend);
#endif
    FSP_ERROR_RETURN((USB_HCDC_ECM_OPEN != p_hcdc_ecm_ctrl->open), FSP_ERR_ALREADY_OPEN);

    p_hcdc_ecm_ctrl->p_cfg = (ether_cfg_t *) p_cfg;

    p_hcdc_ecm_ctrl->p_callback        = p_cfg->p_callback;
    p_hcdc_ecm_ctrl->p_context         = p_cfg->p_context;
    p_hcdc_ecm_ctrl->p_callback_memory = NULL;

    p_extended_cfg = (usb_hcdc_ecm_extended_cfg_t *) p_hcdc_ecm_ctrl->p_cfg->p_extend;

    p_usb_ctrl = (usb_instance_ctrl_t *) p_extended_cfg->p_usb->p_ctrl;
    p_usb_cfg  = (usb_cfg_t *) p_extended_cfg->p_usb->p_cfg;

    g_usb_callback_queue = xQueueCreate(USB_HCDC_ECM_USB_CALLBACK_QUEUE_SIZE, sizeof(void *));
    FSP_ERROR_RETURN((NULL != g_usb_callback_queue), FSP_ERR_INTERNAL);

    g_usb_write_complete_queue = xQueueCreate(USB_HCDC_ECM_USB_WRITE_COMPLETE_QUEUE_SIZE, sizeof(unsigned long));
    if (NULL == g_usb_write_complete_queue)
    {
        vQueueDelete(g_usb_callback_queue);
        FSP_ERROR_RETURN((NULL != g_usb_write_complete_queue), FSP_ERR_INTERNAL);
    }

    xReturn = xTaskCreate(prvUsbEventProcessTask,
                          "UsbEventProcessTask",
                          USB_HCDC_ECM_USB_EVENT_PROCESS_TASK_STACK_SIZE,
                          (void *) p_hcdc_ecm_ctrl,
                          USB_HCDC_ECM_USB_EVENT_PROCESS_TASK_PRIORITY,
                          &xUsbEventProcessTaskHandle);

    FSP_ERROR_RETURN((pdPASS == xReturn), FSP_ERR_INTERNAL);

    err = R_USB_Open(p_usb_ctrl, p_usb_cfg);

    FSP_ERROR_RETURN((FSP_SUCCESS == err), FSP_ERR_USB_NOT_OPEN);

    p_hcdc_ecm_ctrl->open = USB_HCDC_ECM_OPEN;

    return FSP_SUCCESS;
}                                      /* End of function R_USB_HCDC_ECM_Open() */

/********************************************************************************************************************//**
 * @brief Disables interrupts. Removes power and releases hardware lock. Implements @ref ether_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 *
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_Close (ether_ctrl_t * const p_ctrl)
{
    usb_ctrl_t * p_usb_ctrl;
    usb_hcdc_ecm_instance_ctrl_t * p_hcdc_ecm_ctrl = (usb_hcdc_ecm_instance_ctrl_t *) p_ctrl;
    usb_hcdc_ecm_extended_cfg_t  * p_extended_cfg;

    /* Check argument */
#if (USB_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_hcdc_ecm_ctrl);
    FSP_ERROR_RETURN(USB_HCDC_ECM_OPEN == p_hcdc_ecm_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_extended_cfg = (usb_hcdc_ecm_extended_cfg_t *) p_hcdc_ecm_ctrl->p_cfg->p_extend;
    p_usb_ctrl     = (usb_instance_ctrl_t *) p_extended_cfg->p_usb->p_ctrl;

    /* close opened USB module */
    R_USB_Close(p_usb_ctrl);

    if (NULL != xUsbEventProcessTaskHandle)
    {
        vTaskDelete(xUsbEventProcessTaskHandle);
    }

    if (NULL != g_usb_callback_queue)
    {
        vQueueDelete(g_usb_callback_queue);
    }

    if (NULL != g_usb_write_complete_queue)
    {
        vQueueDelete(g_usb_write_complete_queue);
    }

    p_hcdc_ecm_ctrl->open = 0;

    return FSP_SUCCESS;
}                                      /* End of function R_USB_HCDC_ECM_Close() */

/********************************************************************************************************************//**
 * @brief Move to the next buffer in the circular receive buffer list. Implements @ref ether_api_t::bufferRelease.
 *
 * @retval  FSP_ERR_UNSUPPORTED         This function is not supported.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_BufferRelease (ether_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function R_USB_ECM_BufferRelease() */

/********************************************************************************************************************//**
 * @brief Not support this function in HCDC-ECM. Implements @ref ether_api_t::rxBufferUpdate.
 *
 * @retval  FSP_ERR_UNSUPPORTED         This function is not supported.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_RxBufferUpdate (ether_ctrl_t * const p_ctrl, void * const p_buffer)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_buffer);

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function R_USB_HCDC_ECM_RxBufferUpdate() */

/********************************************************************************************************************//**
 * @brief The Link up processing, the Link down processing, and the magic packet detection processing are executed.
 *  Implements @ref ether_api_t::linkProcess.
 *
 * @retval  FSP_SUCCESS                                 Link is up.
 * @retval  FSP_ERR_USB_FAILED                          Link is not up.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_LinkProcess (ether_ctrl_t * const p_ctrl)
{
    usb_hcdc_ecm_instance_ctrl_t * p_hcdc_ecm_ctrl = (usb_hcdc_ecm_instance_ctrl_t *) p_ctrl;
    fsp_err_t err;

    /* Check argument */
#if (USB_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_hcdc_ecm_ctrl);
    FSP_ERROR_RETURN(USB_HCDC_ECM_OPEN == p_hcdc_ecm_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (pdTRUE == p_hcdc_ecm_ctrl->ecm_connected)
    {
        err = FSP_SUCCESS;
    }
    else
    {
        err = FSP_ERR_ETHER_ERROR_LINK;
    }

    return err;
}                                      /* End of function R_USB_HCDC_ECM_LinkProcess() */

/********************************************************************************************************************//**
 * @brief Not support this function in HCDC-ECM. Implements @ref ether_api_t::wakeOnLANEnable.
 *
 * @retval  FSP_ERR_UNSUPPORTED         This function is not supported.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_WakeOnLANEnable (ether_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function R_USB_HCDC_ECM_WakeOnLANEnable() */

/********************************************************************************************************************//**
 * @brief Receive USB data. Receives data to the location specified by the pointer to the receive buffer.
 * Implements @ref ether_api_t::read.
 *
 * @retval  FSP_SUCCESS                                 Processing completed successfully.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_STATE                       USB data read failure.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_Read (ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const p_length_bytes)
{
    usb_hcdc_ecm_instance_ctrl_t * p_hcdc_ecm_ctrl = (usb_hcdc_ecm_instance_ctrl_t *) p_ctrl;
    usb_hcdc_ecm_extended_cfg_t  * p_extended_cfg;
    usb_instance_ctrl_t          * p_usb_ctrl;

    /* Check argument */
#if (USB_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_hcdc_ecm_ctrl);
    FSP_ERROR_RETURN(USB_HCDC_ECM_OPEN == p_hcdc_ecm_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_buffer, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_length_bytes, FSP_ERR_INVALID_POINTER);
#endif

    p_extended_cfg = (usb_hcdc_ecm_extended_cfg_t *) p_hcdc_ecm_ctrl->p_cfg->p_extend;
    p_usb_ctrl     = (usb_instance_ctrl_t *) p_extended_cfg->p_usb->p_ctrl;

    FSP_ERROR_RETURN((FSP_ERR_USB_FAILED != p_hcdc_ecm_ctrl->receive_status), FSP_ERR_INVALID_STATE);

    /* Setting of Received data and data length */
    memcpy(p_buffer, p_hcdc_ecm_ctrl->read_buffer, p_hcdc_ecm_ctrl->receive_size);
    *p_length_bytes = p_hcdc_ecm_ctrl->receive_size;

    p_hcdc_ecm_ctrl->receive_size   = 0;
    p_hcdc_ecm_ctrl->receive_status = FSP_ERR_USB_FAILED;

    R_USB_Read(p_usb_ctrl, p_hcdc_ecm_ctrl->read_buffer, USB_HCDC_ECM_CDC_READ_DATA_LEN,
               p_hcdc_ecm_ctrl->device_address);

    return FSP_SUCCESS;
}                                      /* End of function R_USB_HCDC_ECM_Read() */

/********************************************************************************************************************//**
 * @brief Transmit USB data. Transmits data from the location specified by the pointer to the transmit
 *  buffer, with the data size equal to the specified frame length.
 *  Implements @ref ether_api_t::write.
 *
 * @retval  FSP_SUCCESS                                 Processing completed successfully.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_STATE                       USB data write failure.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Value of the send frame size is out of range.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_Write (ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const length)
{
    usb_hcdc_ecm_instance_ctrl_t * p_hcdc_ecm_ctrl = (usb_hcdc_ecm_instance_ctrl_t *) p_ctrl;
    usb_hcdc_ecm_extended_cfg_t  * p_extended_cfg;
    usb_instance_ctrl_t          * p_usb_ctrl;
    usb_cfg_t        * p_usb_cfg;
    usb_event_info_t * p_event_info;
    fsp_err_t          err = FSP_SUCCESS;
    uint16_t           usb_max_packet_size;

    /* Check argument */
#if (USB_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_hcdc_ecm_ctrl);
    FSP_ERROR_RETURN(USB_HCDC_ECM_OPEN == p_hcdc_ecm_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_buffer, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(0 != length, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_extended_cfg = (usb_hcdc_ecm_extended_cfg_t *) p_hcdc_ecm_ctrl->p_cfg->p_extend;
    p_usb_ctrl     = (usb_instance_ctrl_t *) p_extended_cfg->p_usb->p_ctrl;
    p_usb_cfg      = (usb_cfg_t *) p_extended_cfg->p_usb->p_cfg;

#if (USB_CFG_DMA == USB_CFG_ENABLE)
    if ((USB_IP1 == p_usb_ctrl->module_number) && (0 != ((uint32_t) p_buffer) % sizeof(uint32_t)))
    {
        memcpy(g_snd_buf, p_buffer, length);

        err = R_USB_Write(p_usb_ctrl, g_snd_buf, length, p_hcdc_ecm_ctrl->device_address);
    }
    else
    {
        err = R_USB_Write(p_usb_ctrl, p_buffer, length, p_hcdc_ecm_ctrl->device_address);
    }

#else
    err = R_USB_Write(p_usb_ctrl, (uint8_t *) p_buffer, length, p_hcdc_ecm_ctrl->device_address);
#endif

    FSP_ERROR_RETURN(err == FSP_SUCCESS, FSP_ERR_INVALID_STATE);

    if (USB_SPEED_FS == p_usb_cfg->usb_speed)
    {
        usb_max_packet_size = USB_HCDC_ECM_USB_MAX_PACKET_SIZE_FS;
    }
    else
    {
        usb_max_packet_size = USB_HCDC_ECM_USB_MAX_PACKET_SIZE_HS;
    }

    xQueueReceive(g_usb_write_complete_queue, &p_event_info, portMAX_DELAY);

    if (FSP_ERR_USB_FAILED != p_event_info->status)
    {
        if (0 == length % usb_max_packet_size)
        {
            /* Send 0-Length Packet */
            err = R_USB_Write(p_usb_ctrl, NULL, USB_HCDC_ECM_VALUE_ZERO, p_hcdc_ecm_ctrl->device_address);

            xQueueReceive(g_usb_write_complete_queue, &p_event_info, portMAX_DELAY);
        }
    }

    return err;
}                                      /* End of function R_USB_HCDC_ECM_Write() */

/**********************************************************************************************************************//**
 * @brief Not support this function in HCDC-ECM. Implements @ref ether_api_t::txStatusGet.
 *
 * @retval  FSP_ERR_UNSUPPORTED         This function is not supported.
 ***********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_TxStatusGet (ether_ctrl_t * const p_ctrl, void * const p_buffer_address)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_buffer_address);

    return FSP_ERR_UNSUPPORTED;
}                                      /* End of function R_USB_HCDC_ECM_TxStatusGet() */

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref ether_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_USB_HCDC_ECM_CallbackSet (ether_ctrl_t * const          p_api_ctrl,
                                      void (                      * p_callback)(ether_callback_args_t *),
                                      void * const                  p_context,
                                      ether_callback_args_t * const p_callback_memory)
{
    usb_hcdc_ecm_instance_ctrl_t * p_ctrl = (usb_hcdc_ecm_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if USB_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    usb_hcdc_ecm_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                               CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(usb_hcdc_ecm_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}                                      /* End of function R_USB_HCDC_ECM_CallbackSet() */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_ECM)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
static void prvUsbEventProcessTask (void * const pvParameters)
{
    /* Avoid compiler warning about unreferenced parameter. */
    uint32_t               i   = 0;
    uint32_t               flg = 0;
    fsp_err_t              err;
    usb_hcdc_device_info_t device_info;
    uint16_t             * vendor_table;
    uint16_t               vendor_id;
    uint16_t               product_id;

    usb_hcdc_ecm_instance_ctrl_t * p_hcdc_ecm_ctrl = (usb_hcdc_ecm_instance_ctrl_t *) pvParameters;
    usb_hcdc_ecm_extended_cfg_t  * p_extended_cfg;
    usb_ctrl_t * p_usb_ctrl;
    usb_cfg_t  * p_usb_cfg;

    usb_event_info_t * p_event_info = NULL;
    usb_utr_t          utr;

    uint8_t * p_config_descriptor;

    ether_callback_args_t arg;

    p_extended_cfg = (usb_hcdc_ecm_extended_cfg_t *) p_hcdc_ecm_ctrl->p_cfg->p_extend;
    p_usb_ctrl     = (usb_instance_ctrl_t *) p_extended_cfg->p_usb->p_ctrl;
    p_usb_cfg      = (usb_cfg_t *) p_extended_cfg->p_usb->p_cfg;

    utr.ip  = p_usb_cfg->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr((uint16_t) p_usb_cfg->module_number);

#if (USB_CFG_DMA == USB_CFG_ENABLE)
    utr.p_transfer_rx = p_usb_cfg->p_transfer_rx;
    utr.p_transfer_tx = p_usb_cfg->p_transfer_tx;
#endif

    for ( ; ; )
    {
        /* Receive message from queue and analyzing the received message*/
        xQueueReceive(g_usb_callback_queue, &p_event_info, (portMAX_DELAY));
        switch (p_event_info->event)
        {
            case USB_STATUS_CONFIGURED:
            {
                p_hcdc_ecm_ctrl->device_address = p_event_info->device_address;

                err = R_USB_HCDC_DeviceInfoGet(p_usb_ctrl, &device_info, p_event_info->device_address);

                if (FSP_SUCCESS == err)
                {
                    if (USB_HCDC_ECM_CDC_SUB_CLASS_ECM == device_info.subclass)
                    {
                        R_USB_HCDC_ControlDataRead(p_usb_ctrl,
                                                   &g_interrupt_in_rcv_buf[USB_HCDC_ECM_VALUE_ZERO],
                                                   USB_HCDC_ECM_CDC_INTERRUPT_READ_DATA_LEN,
                                                   p_event_info->device_address);
                    }
                    else if (USB_HCDC_ECM_CDC_SUB_CLASS_ACM == device_info.subclass)
                    {
                        /* none */
                    }
                    else
                    {
                        flg = 0;
                        g_target_info.start_of_sequence_number = 0;

                        vendor_table = usb_hcdc_get_vendor_table();

                        for ( ; i < USB_HCDC_SPECIFIC_DEV_MAX; i++)
                        {
                            vendor_id  = vendor_table[(i * 2) + 2];
                            product_id = vendor_table[(i * 2) + 3];

                            if ((vendor_id == device_info.vendor_id) && (product_id == device_info.product_id))
                            {
                                flg = 1;
                                break;
                            }
                        }

                        if (0 == flg)
                        {
                            /* Since the ECM subclass has already been analyzed */
                            /* by the Basic driver's MGR task, the process here */
                            /* starts with the SetEthernetPacketFilter request. */
                            g_target_info.start_of_sequence_number = 5;
                        }

                        usb_hcdc_ecm_device_activation(p_hcdc_ecm_ctrl,
                                                       p_usb_ctrl,
                                                       p_hcdc_ecm_ctrl->device_address,
                                                       &g_target_info);
                    }
                }

                break;
            }

            case USB_STATUS_READ_COMPLETE:
            {
                if (USB_CLASS_HCDC == p_event_info->type)
                {
                    if (FSP_ERR_USB_FAILED != p_event_info->status)
                    {
                        p_hcdc_ecm_ctrl->receive_size   = p_event_info->data_size;
                        p_hcdc_ecm_ctrl->receive_status = p_event_info->status;
                        p_hcdc_ecm_ctrl->device_address = p_event_info->device_address;

                        arg.event      = ETHER_EVENT_RX_COMPLETE;
                        arg.p_nic_info = NULL;
                        usb_hcdc_ecm_call_callback(p_hcdc_ecm_ctrl, &arg);
                    }
                    else
                    {
                        if (pdTRUE == p_hcdc_ecm_ctrl->ecm_connected)
                        {
                            R_USB_Read(p_usb_ctrl,
                                       p_hcdc_ecm_ctrl->read_buffer,
                                       USB_HCDC_ECM_CDC_READ_DATA_LEN,
                                       p_event_info->device_address);
                        }
                    }
                }
                else
                {
                    if (0 ==
                        memcmp((void *) g_notification_networkconnection_connect, g_interrupt_in_rcv_buf,
                               sizeof(g_notification_networkconnection_connect)))
                    {
                        /* Received NETWORKCONNECTION "Connected". */

                        if (pdFALSE == p_hcdc_ecm_ctrl->ecm_connected)
                        {
                            p_hcdc_ecm_ctrl->ecm_connected = pdTRUE; /* link up */

                            R_USB_Read(p_usb_ctrl,
                                       p_hcdc_ecm_ctrl->read_buffer,
                                       USB_HCDC_ECM_CDC_READ_DATA_LEN,
                                       p_event_info->device_address);
                        }
                    }
                    else if (0 ==
                             memcmp((void *) g_notification_networkconnection_disconnect, g_interrupt_in_rcv_buf,
                                    sizeof(g_notification_networkconnection_disconnect)))
                    {
                        /* Received NETWORKCONNECTION "Disconnect". */

                        p_hcdc_ecm_ctrl->ecm_connected = pdFALSE; /* link down */

                        /* Cancel a bulk IN transfer request.*/
                        R_USB_Stop(p_usb_ctrl, USB_TRANSFER_READ, p_event_info->device_address);
                    }
                    else
                    {
                        /* none */
                    }

                    R_USB_HCDC_ControlDataRead(p_usb_ctrl,
                                               &g_interrupt_in_rcv_buf[USB_HCDC_ECM_VALUE_ZERO],
                                               USB_HCDC_ECM_CDC_INTERRUPT_READ_DATA_LEN,
                                               p_event_info->device_address);
                }

                break;
            }

            case USB_STATUS_WRITE_COMPLETE:
            {
                xQueueSend(g_usb_write_complete_queue, &p_event_info, (TickType_t) portMAX_DELAY);
                break;
            }

            case USB_STATUS_REQUEST_COMPLETE:
            {
                if (pdTRUE != g_target_info.target_process_complete)
                {
                    usb_hcdc_ecm_device_activation(p_hcdc_ecm_ctrl,
                                                   p_usb_ctrl,
                                                   p_hcdc_ecm_ctrl->device_address,
                                                   &g_target_info);

                    if (pdTRUE == g_target_info.target_process_complete)
                    {
                        p_config_descriptor = (uint8_t *) g_usb_hstd_config_descriptor[utr.ip];
                        if (NULL != g_target_info.p_ecm_configuration_descriptor)
                        {
                            if (p_config_descriptor[5] !=
                                g_target_info.p_ecm_configuration_descriptor[5])
                            {
                                memcpy(p_config_descriptor,
                                       g_target_info.p_ecm_configuration_descriptor,
                                       (uint16_t) (((uint16_t) g_target_info.p_ecm_configuration_descriptor[3] << 8) +
                                                   (uint16_t) g_target_info.p_ecm_configuration_descriptor[2]));
                            }
                        }

                        /* Pipe setting  */
                        usb_hcdc_pipe_info(&utr,
                                           p_config_descriptor,
                                           g_usb_hcdc_speed[utr.ip],
                                           (uint16_t) (((uint16_t) p_config_descriptor[3] << 8) +
                                                       (uint16_t) p_config_descriptor[2]));
                        usb_hcdc_set_pipe_registration(&utr, p_event_info->device_address);

                        R_USB_HCDC_ControlDataRead(p_usb_ctrl,
                                                   &g_interrupt_in_rcv_buf[USB_HCDC_ECM_VALUE_ZERO],
                                                   USB_HCDC_ECM_CDC_INTERRUPT_READ_DATA_LEN,
                                                   p_event_info->device_address);
                    }
                }

                break;
            }

            case USB_STATUS_DETACH:
            {
                p_hcdc_ecm_ctrl->ecm_connected        = pdFALSE; /* link down */
                g_target_info.target_process_complete = pdFALSE;
                break;
            }

            default:
            {
                /* No operation to do*/
                break;
            }
        }
    }
}

uint16_t usb_hcdc_ecm_pre_check_config (uint8_t * table, uint16_t length)
{
    /* This function checks if the device is a normal CDC device.                      */
    /* If it is a normal CDC device, it returns USB_OK, otherwise it returns USB_ERROR.*/

    uint16_t ofdsc;
    uint16_t result_code = USB_ERROR;

    if (1 == table[USB_DEV_B_CONFIGURATION_VALUE])
    {
        /* Check Interface Descriptor */
        ofdsc = table[0];

        /* WAIT_LOOP */
        while (ofdsc < length)
        {
            /* Interface Descriptor */
            if (USB_DT_INTERFACE == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
            {
                if ((USB_IFCLS_CDCC == table[ofdsc + USB_IF_B_INTERFACECLASS]) &&
                    (USB_HCDC_ECM_CDC_SUB_CLASS_ECM != table[ofdsc + USB_IF_B_INTERFACESUBCLASS]))
                {
                    result_code = USB_OK; /* Device has normal CDC Class Interface. */
                    break;
                }
            }

            ofdsc = (uint16_t) (ofdsc + table[ofdsc]);
        }
    }

    return result_code;
}                                      /* End of function usb_hcdc_ecm_pre_check_config */

uint16_t usb_hcdc_ecm_check_config (uint8_t * table, uint16_t length)
{
    uint16_t ofdsc;
    uint16_t result_code = USB_ERROR;

    /* Check Interface Descriptor */
    ofdsc = table[0];

    /* WAIT_LOOP */
    while (ofdsc < length)
    {
        /* Interface Descriptor */
        if (USB_DT_INTERFACE == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
        {
            if ((USB_IFCLS_CDCC == table[ofdsc + USB_IF_B_INTERFACECLASS]) &&
                (USB_HCDC_ECM_CDC_SUB_CLASS_ECM == table[ofdsc + USB_IF_B_INTERFACESUBCLASS]))
            {
                result_code = USB_OK;
            }
        }

        /* Ethernet Networking Functional Descriptor */
        if (USB_HCDC_ECM_DESCRITOR_TYPE_CS_INTERFACE == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
        {
            if (USB_HCDC_ECM_DESCRITOR_SUBTYPE_NETWORKING == table[ofdsc + USB_HCDC_ECM_DESCRITOR_SUBTYPE_INDEX])
            {
                g_i_mac_address = table[ofdsc + USB_HCDC_ECM_DESCRITOR_IMACADDRESS_INDEX];
            }
        }

        ofdsc = (uint16_t) (ofdsc + table[ofdsc]);
    }

    return result_code;
}                                      /* End of function usb_hcdc_ecm_check_config */

static void usb_hcdc_ecm_device_activation (usb_hcdc_ecm_instance_ctrl_t * const  p_hcdc_ecm_ctrl,
                                            usb_ctrl_t * const                    p_usb_ctrl,
                                            uint8_t                               device_address,
                                            usb_ecm_target_process_item_t * const p_target_process_info)
{
    static uint8_t        sequence_number   = 0;
    static uint8_t        num_configuration = 0;
    static uint8_t        idx_configuration = 0;
    static uint8_t        configuration_value;
    uint16_t              get_ecm_config_no;
    ether_callback_args_t arg;

    if ((0 == sequence_number) && (0 != p_target_process_info->start_of_sequence_number))
    {
        sequence_number = p_target_process_info->start_of_sequence_number;
    }

    switch (sequence_number)
    {
        case 0:
        {
            /* Get Device Descrptor (18 byte) */
            usb_hcdc_ecm_get_device_descriptor(p_usb_ctrl, device_address);
            sequence_number++;
            break;
        }

        case 1:
        {
            /* Get bNumConfigurations */
            num_configuration = g_disc_buf[USB_DEV_B_NUM_CONFIGURATION];
            idx_configuration = 0;

            /* Get Configuration Descrptor (9 byte) */
            usb_hcdc_ecm_get_configuration_descriptor(p_usb_ctrl,
                                                      device_address,
                                                      (uint16_t) USB_HCDC_ECM_VALUE_9,
                                                      idx_configuration);
            sequence_number++;
            break;
        }

        case 2:
        {
            /* Get Current ConfigurationValue */
            configuration_value = g_disc_buf[USB_DEV_B_CONFIGURATION_VALUE];

            /* Get Configuration Descrptor (all byte) */
            usb_hcdc_ecm_get_configuration_descriptor(p_usb_ctrl,
                                                      device_address,
                                                      (uint16_t) (((uint16_t) g_disc_buf[3] << 8) +
                                                                  (uint16_t) g_disc_buf[2]),
                                                      idx_configuration);
            sequence_number++;
            break;
        }

        case 3:
        {
            p_target_process_info->p_ecm_configuration_descriptor = &g_disc_buf[0];

            /* Check CDC-ECM Configuration */
            get_ecm_config_no =
                usb_hcdc_ecm_check_config(&g_disc_buf[0],
                                          (uint16_t) (((uint16_t) g_disc_buf[3] << 8) + (uint16_t) g_disc_buf[2]));
            if (USB_OK == get_ecm_config_no)
            {
                /* Set Configuration (0) */
                usb_hcdc_ecm_set_configuration(p_usb_ctrl, device_address, USB_HCDC_ECM_VALUE_ZERO);
                sequence_number++;
            }
            else
            {
                /* Next Configuration Descriptor */
                idx_configuration++;
                if (idx_configuration < num_configuration)
                {
                    /* Get Configuration Descrptor (9 byte) */
                    usb_hcdc_ecm_get_configuration_descriptor(p_usb_ctrl,
                                                              device_address,
                                                              (uint16_t) USB_HCDC_ECM_VALUE_9,
                                                              idx_configuration);
                    sequence_number--;
                }
                else
                {
                    sequence_number = 0;
                }
            }

            break;
        }

        case 4:
        {
            /* Set Configuration (Configuration number as ECM) */
            usb_hcdc_ecm_set_configuration(p_usb_ctrl, device_address, configuration_value);
            sequence_number++;
            break;
        }

        case 5:
        {
            usb_hcdc_ecm_get_string_descriptor(p_usb_ctrl, device_address, g_i_mac_address);
            sequence_number++;
            break;
        }

        case 6:
        {
            /* Create MAC address information for callback which update MAC address. */
            usb_hcdc_ecm_get_mac_address(g_string_disc_buf, g_mac_address);

            /* Callback to "rm_freertos_plus_tcp" to notify MAC address. */
            arg.event                     = ETHER_EVENT_GET_NIC_INFO;
            arg.p_nic_info                = &g_nic_info;
            arg.p_nic_info->p_mac_address = g_mac_address;
            usb_hcdc_ecm_call_callback(p_hcdc_ecm_ctrl, &arg);

            /* Set Ethernet Packet Filter (No filtering)*/
            usb_hcdc_ecm_set_ethernet_packet_filter(p_usb_ctrl, device_address);
            sequence_number++;
            break;
        }

        case 7:
        {
            /* Set Interface (IF=1/ALT=1) */
            usb_hcdc_ecm_set_interface(p_usb_ctrl, device_address);
            sequence_number++;
            break;
        }

        case 8:
        {
            /* Set the completion flag for this function. (To be on the safe side, */
            /* do this after the Set Interface Request has completed.)             */
            p_target_process_info->target_process_complete = 1;
            sequence_number = 0;
            break;
        }

        default:
        {
            break;
        }
    }
}                                      /* End of function usb_hcdc_ecm_device_activation */

static void usb_hcdc_ecm_get_mac_address (uint8_t const * const table, uint8_t * const mac_address)
{
    uint32_t length = table[0];
    uint32_t i      = 0;
    uint16_t ofdsc  = 0;
    uint16_t unicode;
    char   * p_end;                                 /* Use "char" instead of "int8_t" to avoid a warning */
    char   * p_mac_address  = (char *) mac_address; /* Use "char" instead of "int8_t" to avoid a warning */
    char     mac_string[20] = {0};                  /* Use "char" instead of "int8_t" to avoid a warning */
    char     chara[3]       = {0};                  /* Use "char" instead of "int8_t" to avoid a warning */

    /* Generate a MAC address string from Unicode. */
    for (ofdsc = 2; ofdsc < length; )
    {
        memcpy(&unicode, &table[ofdsc], 2);
        strncat(mac_string, (const char *) &unicode, sizeof(uint16_t));
        ofdsc = ofdsc + 2;
    }

    /* Convert it to a number and store it in a 6-byte array. */
    for (i = 0; i < USB_HCDC_ECM_NUM_OF_MACADDRESS_BYTES; i++)
    {
        memcpy(chara, &mac_string[i * 2], 2);
        p_mac_address[i] = (char) strtol(chara, &p_end, 16);
    }
}                                      /* End of function usb_hcdc_ecm_get_mac_address */

static void usb_hcdc_ecm_set_configuration (usb_instance_ctrl_t * const p_ctrl,
                                            uint8_t                     device_address,
                                            uint16_t                    config_value)
{
    usb_setup_t setup;
    setup.request_type   = USB_SET_CONFIGURATION | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
    setup.request_value  = config_value;
    setup.request_index  = USB_HCDC_ECM_VALUE_ZERO;
    setup.request_length = USB_HCDC_ECM_VALUE_ZERO;

    /* Request Control transfer */
    R_USB_HostControlTransfer(p_ctrl, &setup, &g_usb_dummy, device_address);
}                                      /* End of function usb_hcdc_ecm_set_configuration */

static void usb_hcdc_ecm_get_device_descriptor (usb_instance_ctrl_t * const p_ctrl, uint8_t device_address)
{
    usb_setup_t setup;
    setup.request_type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    setup.request_value  = (uint16_t) USB_DEV_DESCRIPTOR;
    setup.request_index  = USB_HCDC_ECM_VALUE_ZERO;
    setup.request_length = USB_HCDC_ECM_VALUE_0012H;

    /* Request Control transfer */
    R_USB_HostControlTransfer(p_ctrl, &setup, &g_disc_buf[0], device_address);
}                                      /* End of function usb_hcdc_ecm_get_device_descriptor */

static void usb_hcdc_ecm_get_configuration_descriptor (usb_instance_ctrl_t * const p_ctrl,
                                                       uint8_t                     device_address,
                                                       uint16_t                    length,
                                                       uint16_t                    config_index)
{
    usb_setup_t setup;
    setup.request_type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    setup.request_value  = (uint16_t) USB_CONF_DESCRIPTOR | config_index; /* index of config disc */
    setup.request_index  = USB_HCDC_ECM_VALUE_ZERO;
    setup.request_length = length;

    /* Request Control transfer */
    R_USB_HostControlTransfer(p_ctrl, &setup, &g_disc_buf[0], device_address);
}                                      /* End of function usb_hcdc_ecm_get_configuration_descriptor */

static void usb_hcdc_ecm_set_interface (usb_instance_ctrl_t * const p_ctrl, uint8_t device_address)
{
    usb_setup_t setup;
    setup.request_type   = USB_SET_INTERFACE | USB_HOST_TO_DEV | USB_STANDARD | USB_INTERFACE;
    setup.request_value  = USB_HCDC_ECM_VALUE_0001H;
    setup.request_index  = USB_HCDC_ECM_VALUE_0001H;
    setup.request_length = USB_HCDC_ECM_VALUE_ZERO;

    /* Request Control transfer */
    R_USB_HostControlTransfer(p_ctrl, &setup, &g_usb_dummy, device_address);
}                                      /* End of function usb_hcdc_ecm_set_interface */

static void usb_hcdc_ecm_set_ethernet_packet_filter (usb_instance_ctrl_t * const p_ctrl, uint8_t device_address)
{
    usb_setup_t setup;
    setup.request_type   = (USB_HCDC_ECM_SET_ETHERNET_PACKET_FILTER | USB_HOST_TO_DEV | USB_CLASS | USB_INTERFACE);
    setup.request_value  = USB_HCDC_ECM_VALUE_001FH; /* No packet filter */
    setup.request_index  = USB_HCDC_ECM_VALUE_0001H; /* wIndex:Interface */
    setup.request_length = USB_HCDC_ECM_VALUE_ZERO;  /* wLength:Zero */

    R_USB_HostControlTransfer(p_ctrl, &setup, &g_usb_dummy, device_address);
}                                                    /* End of function usb_hcdc_ecm_set_ethernet_packet_filter */

static void usb_hcdc_ecm_get_string_descriptor (usb_instance_ctrl_t * const p_ctrl,
                                                uint8_t                     device_address,
                                                uint16_t                    index)
{
    usb_setup_t setup;
    setup.request_type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    setup.request_value  = (uint16_t) USB_STRING_DESCRIPTOR | index;
    setup.request_index  = USB_HCDC_ECM_LANG_ID_USA;
    setup.request_length = USB_HCDC_ECM_VALUE_00FFH;

    /* Request Control transfer */
    R_USB_HostControlTransfer(p_ctrl, &setup, &g_string_disc_buf[0], device_address);
}                                      /* End of function usb_hcdc_ecm_get_string_descriptor */

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_instance_ctrl      Pointer to block media usb instance control block
 * @param[in]     p_callback_args      Pointer to callback args
 **********************************************************************************************************************/
void usb_hcdc_ecm_call_callback (usb_hcdc_ecm_instance_ctrl_t * p_instance_ctrl,
                                 ether_callback_args_t        * p_callback_args)
{
    ether_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    ether_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->event = p_callback_args->event;

    if (NULL != p_callback_args->p_nic_info)
    {
        p_args->p_nic_info = p_callback_args->p_nic_info;
    }

    p_args->p_context = p_instance_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_instance_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_instance_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        usb_ecm_prv_ns_callback p_callback = (usb_ecm_prv_ns_callback) (p_instance_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_instance_ctrl->p_callback(p_args);
#endif

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }
}

void usb_rtos_callback (usb_event_info_t * p_event_info, usb_hdl_t cur_task, usb_onoff_t usb_state)
{
    FSP_PARAMETER_NOT_USED(cur_task);
    FSP_PARAMETER_NOT_USED(usb_state);

    /* Send event received to queue */
    xQueueSend(g_usb_callback_queue, (const void *) &p_event_info, (TickType_t) (USB_HCDC_ECM_NO_WAIT_TIME));
}                                      /* End of function usb_rtos_callback */
