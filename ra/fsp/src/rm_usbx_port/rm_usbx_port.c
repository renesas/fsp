/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include <string.h>
#include "../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "../r_usb_basic/src/hw/inc/r_usb_reg_access.h"

#if (BSP_CFG_RTOS == 1)
 #include "ux_api.h"
 #include "ux_system.h"
 #include "ux_utility.h"
 #include "ux_device_stack.h"

 #if defined(USB_CFG_PMSC_USE)
  #include "r_usb_pmsc_cfg.h"
  #include "ux_device_class_storage.h"
  #include "rm_block_media_api.h"
 #endif                                /* defined(USB_CFG_PMSC_USE) */

 #if defined(USB_CFG_HHID_USE)
  #include "r_usb_hhid_cfg.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */

 #if defined(USB_CFG_HCDC_USE)
  #include "ux_host_class_cdc_acm.h"
 #endif                                /* defined(USB_CFG_HCDC_USE) */

 #if defined(USB_CFG_PHID_USE)
  #include "r_usb_phid_cfg.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */

 #if defined(USB_CFG_HPRN_USE)
  #include "ux_host_class_printer.h"
 #endif                                /* defined(USB_CFG_HPRN_USE) */

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
  #include "ux_host_stack.h"
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

/*******************************************************************************
 * Macro definitions
 ******************************************************************************/
 #define VALUE_1000UL                      (1000UL)
 #if defined(USB_CFG_HHID_USE)
  #define UX_FSP_HC_AVAILABLE_BANDWIDTH    (2322UL)
 #else
  #define UX_FSP_HC_AVAILABLE_BANDWIDTH    (2304UL)
 #endif                                /* defined(USB_CFG_HHID_USE) */
 #define UX_FSP_MAX_BULK_PAYLOAD           (512UL)
 #define UX_FSP_MAX_INTERRUPT_PAYLOAD      (512UL)
 #define UX_FSP_MAX_CONTROL_PAYLOAD        (512UL)
 #define UX_FSP_MAX_ISO_PAYLOAD            (512UL)

 #define UX_FSP_MAX_SELF_POWER             (500U / 2)
 #define UX_FSP_MASK_ENDPOINT_TYPE         (3U)
 #define UX_FSP_CONTROL_ENDPOINT           (0U)
 #define UX_FSP_SET_CONFIGURATION          (9U)
 #define UX_FSP_SETUP_REQUEST_TYPE         (0U)
 #define UX_FSP_BULK_ENDPOINT              (2U)
 #define UX_FSP_INTERRUPT_ENDPOINT         (3U)
 #define UX_FSP_ISOCHRONOUS_ENDPOINT       (1U)

 #define USB_PERI_USBX_REMOVABLE_MEDIA     (0x80U)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static UINT     usb_peri_usbx_to_basic(UX_SLAVE_DCD * dcd, UINT function, VOID * parameter);
static void     usb_peri_usbx_transfer_complete_cb(usb_utr_t * p_mess, uint16_t data1, uint16_t data2);
static uint32_t usb_peri_usbx_initialize_common(uint32_t dcd_io);
static void     usb_peri_usbx_initialize_common_complete(void);

static ULONG * g_p_usb_actural_length[USB_MAX_PIPE_NO + 1U];
  #if defined(USB_CFG_PMSC_USE)
static UX_SLAVE_CLASS_STORAGE_PARAMETER g_usb_peri_usbx_pmsc_parameter;
static uint32_t g_media_total_sector;
static uint32_t g_media_sector_size_bytes;
static bool     g_media_write_protected = 0;
static rm_block_media_instance_t * gp_block_media_instance;
volatile bool        g_blockmedia_complete_event     = false;
static volatile bool g_blockmedia_poll_status_events = false;
static volatile bool g_status_busy = false;

static UINT usb_peri_usbx_media_read(VOID  * storage,
                                     ULONG   lun,
                                     UCHAR * data_pointer,
                                     ULONG   number_blocks,
                                     ULONG   lba,
                                     ULONG * media_status);
static UINT usb_peri_usbx_media_write(VOID  * storage,
                                      ULONG   lun,
                                      UCHAR * data_pointer,
                                      ULONG   number_blocks,
                                      ULONG   lba,
                                      ULONG * media_status);
static UINT usb_peri_usbx_media_status(VOID * storage, ULONG lun, ULONG media_id, ULONG * media_status);
static void usb_peri_usbx_pmsc_storage_init(void);
static void usb_peri_usbx_pmsc_storage_uninit(void);

  #endif                               /* defined(USB_CFG_PMSC_USE) */
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

 #if defined(USB_CFG_OTG_USE)
static UINT usb_otg_hnp_swap(ULONG type);
static UINT usb2_otg_hnp_swap(ULONG type);

 #endif                                /* defined(USB_CFG_OTG_USE) */

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint8_t  usb_host_usbx_endpoint_to_pipe(uint8_t module_number, uint8_t ep_number);
static void     usb_host_usbx_configured(usb_utr_t * p_utr, uint16_t devadr, uint16_t data2);
static void     usb_host_usbx_set_pipe_registration(usb_utr_t * ptr, uint16_t dev_addr);
static void     usb_host_usbx_detach(usb_utr_t * p_utr, uint16_t devadr, uint16_t data2);
static void     usb_host_usbx_init(usb_utr_t * p_utr, uint16_t data1, uint16_t data2);
static void     usb_host_usbx_class_check(usb_utr_t * p_utr, uint16_t ** table);
static uint32_t usb_host_usbx_get_speed(UX_HCD * hcd);
static UINT     usb_host_usbx_to_basic(UX_HCD * hcd, UINT function, VOID * parameter);
static void     usb_host_usbx_initialize_common_complete(UX_HCD * hcd);
static uint32_t usb_host_usbx_initialize_common(UX_HCD * hcd);

static uint16_t  g_usb_host_usbx_request[USB_NUM_USBIP][5];
static usb_utr_t g_usb_host_usbx_req_msg[USB_NUM_USBIP];

static uint32_t * g_p_usb_host_actural_length[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

static UX_TRANSFER * g_p_usb_host_usbx_transfer_request[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

static const uint16_t g_usb_host_usbx_device_tpl[] =
{
    USB_CFG_TPLCNT,                    /* Number of tpl table */
    0,                                 /* Reserved */
    USB_CFG_TPL                        /* Vendor ID, Product ID */
};
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
uint32_t  usb_peri_usbx_initialize(uint32_t dcd_io);
uint32_t  usb_peri_usbx_uninitialize(uint32_t dcd_io);
uint32_t  usb_peri_usbx_remote_wakeup(uint8_t module_number);
fsp_err_t usb_peri_usbx_pmsc_media_initialize(void const * p_context);
void      usb_peri_usbx_set_control_length(usb_setup_t * p_req);

bool                g_usb_peri_usbx_is_detach[USB_MAX_PIPE_NO + 1];
extern TX_SEMAPHORE g_usb_peri_usbx_sem[USB_MAX_PIPE_NO + 1];

  #if defined(USB_CFG_PMSC_USE)
fsp_err_t usb_peri_usbx_media_initialize(void const * p_context);
fsp_err_t usb_peri_usbx_media_close(void);
void      r_usb_pmsc_block_media_event_callback(rm_block_media_callback_args_t * p_args);

volatile bool g_card_inserted = false;

  #endif                               /* defined(USB_CFG_PMSC_USE) */
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
UINT     usb_host_usbx_initialize(UX_HCD * hcd);
uint32_t usb_host_usbx_uninitialize(uint32_t hcd_io);

UX_DEVICE  * g_p_usbx_device[USB_NUM_USBIP];
TX_SEMAPHORE g_usb_host_usbx_sem[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1];

  #if defined(USB_CFG_HMSC_USE)
static uint16_t             g_usb_hmsc_in_pipectr[USB_NUM_USBIP][1];  /* Pipectr(SQTGL) */
static uint16_t             g_usb_hmsc_out_pipectr[USB_NUM_USBIP][1]; /* Pipectr(SQTGL) */
static usb_pipe_table_reg_t g_usb_hmsc_pipe_table[1][USB_PIPE_DIR_MAX];
static uint16_t             g_usb_hmsc_in_pipe[USB_NUM_USBIP][1];
static uint16_t             g_usb_hmsc_out_pipe[USB_NUM_USBIP][1];
   #if (USB_CFG_DMA == USB_CFG_ENABLE)
static void * g_p_usbx_hmsc_dma_buf[USB_MAXDEVADDR] = {0};
   #endif                              /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */
  #endif /* #if defined(USB_CFG_HMSC_USE) */
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

 #if defined(USB_CFG_OTG_USE)
uint8_t g_usb_otg_hnp_process[USB_NUM_USBIP] =
{
    USB_OFF,
  #if USB_NUM_USBIP == 2
    USB_OFF
  #endif
};
 #endif                                /* defined(USB_CFG_OTG_USE) */

 #if (USB_CFG_DMA == USB_CFG_ENABLE)
extern const transfer_instance_t * g_p_usbx_transfer_tx;
extern const transfer_instance_t * g_p_usbx_transfer_rx;
 #endif                                /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */

 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern const uint16_t USB_CFG_TPL_TABLE[];
 #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Function Name   : usb_peri_usbx_initialize
 * Description     : Initialization processing
 * Argument        : uint32_t dcd_io : Address of USB module 0 or USB module 1
 * Return          : UX_SUCCESS
 ******************************************************************************/
uint32_t usb_peri_usbx_initialize (uint32_t dcd_io)
{
    uint32_t status;

  #if defined(USB_CFG_PMSC_USE)
    usb_peri_usbx_pmsc_storage_init();
  #endif                               /* defined(USB_CFG_PMSC_USE) */

    status = usb_peri_usbx_initialize_common(dcd_io);
    if (UX_SUCCESS == status)
    {
        usb_peri_usbx_initialize_common_complete();
    }

    return status;
}                                      /* End of function usb_peri_usbx_initialize() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_uninitialize
 * Description     : Uninitialization processing
 * Argument        : uint32_t dcd_io : Address of USB module 0 or USB module 1
 * Return          : UX_SUCCESS
 ******************************************************************************/
uint32_t usb_peri_usbx_uninitialize (uint32_t dcd_io)
{
    UX_SLAVE_DCD * dcd;

  #if defined(R_USB_HS0_BASE)
    if ((dcd_io != R_USB_HS0_BASE) && (dcd_io != R_USB_FS0_BASE))
  #else
    if (dcd_io != R_USB_FS0_BASE)
  #endif
    {
        return (uint32_t) FSP_ERR_USB_FAILED;
    }

    dcd = &_ux_system_slave->ux_system_slave_dcd;

    dcd->ux_slave_dcd_status   = (uint32_t) UX_UNUSED;
    dcd->ux_slave_dcd_io       = 0U;
    dcd->ux_slave_dcd_function = UX_NULL;

  #if defined(USB_CFG_PMSC_USE)
    usb_peri_usbx_pmsc_storage_uninit();
  #endif                               /* defined(USB_CFG_PMSC_USE) */

    return (uint32_t) UX_SUCCESS;
}                                      /* End of function usb_peri_usbx_uninitialize() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_initialize_common
 * Description     : Initialization processing
 * Argument        : uint32_t dcd_io : Address of USB module 0 or USB module 1
 * Return          : UX_SUCCESS
 ******************************************************************************/
static uint32_t usb_peri_usbx_initialize_common (uint32_t dcd_io)
{
    UX_SLAVE_DCD * dcd;

    /* Get the pointer to the DCD.  */
    dcd = &_ux_system_slave->ux_system_slave_dcd;

    /* Save the base address of the controller.  */
    dcd->ux_slave_dcd_io = dcd_io;

    dcd->ux_slave_dcd_function = usb_peri_usbx_to_basic;

    /* Return successful completion.  */
    return (uint32_t) UX_SUCCESS;
}                                      /* End of function usb_peri_usbx_initialize_common() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_initialize_common_complete
 * Description     : Initialization processing
 * Argument        : None
 * Return          : None
 ******************************************************************************/
static void usb_peri_usbx_initialize_common_complete (void)
{
    UX_SLAVE_DCD * dcd = &_ux_system_slave->ux_system_slave_dcd;

    dcd->ux_slave_dcd_status = (uint32_t) UX_DCD_STATUS_OPERATIONAL;
}                                      /* End of function usb_peri_usbx_initialize_common_complete() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_initialize_complete
 * Description     : Initialization processing
 * Argument        : None
 * Return          : None
 ******************************************************************************/
uint32_t usb_peri_usbx_initialize_complete (void)
{
    UX_SLAVE_DCD      * dcd;
    UX_SLAVE_DEVICE   * device;
    uint8_t           * device_framework;
    UX_SLAVE_TRANSFER * transfer_request;

    /* Get the pointer to the DCD.  */
    dcd = &_ux_system_slave->ux_system_slave_dcd;

    /* Get the pointer to the device.  */
    device = &_ux_system_slave->ux_system_slave_device;

    /* Check the speed and set the correct descriptor.  */
    if (_ux_system_slave->ux_system_slave_speed == (uint32_t) UX_FULL_SPEED_DEVICE)
    {
        /* The device is operating at full speed.  */
        _ux_system_slave->ux_system_slave_device_framework =
            _ux_system_slave->ux_system_slave_device_framework_full_speed;
        _ux_system_slave->ux_system_slave_device_framework_length =
            _ux_system_slave->ux_system_slave_device_framework_length_full_speed;
    }
    else
    {
        /* The device is operating at high speed.  */
        _ux_system_slave->ux_system_slave_device_framework =
            _ux_system_slave->ux_system_slave_device_framework_high_speed;
        _ux_system_slave->ux_system_slave_device_framework_length =
            _ux_system_slave->ux_system_slave_device_framework_length_high_speed;
    }

    /* Get the device framework pointer.  */
    device_framework = _ux_system_slave->ux_system_slave_device_framework;

    /* And create the decompressed device descriptor structure.  */
    _ux_utility_descriptor_parse(device_framework,
                                 (uint8_t *) _ux_system_device_descriptor_structure,
                                 (uint32_t) UX_DEVICE_DESCRIPTOR_ENTRIES,
                                 (uint8_t *) (&device->ux_slave_device_descriptor));

    /* Now we create a transfer request to accept the first SETUP packet
     * and get the ball running. First get the address of the endpoint
     * transfer request container.  */
    transfer_request = &device->ux_slave_device_control_endpoint.ux_slave_endpoint_transfer_request;

    /* Set the timeout to be for Control Endpoint.  */
    transfer_request->ux_slave_transfer_request_timeout =
        (((uint32_t) (UX_CONTROL_TRANSFER_TIMEOUT_IN_MS) *(uint32_t) (UX_PERIODIC_RATE)) / VALUE_1000UL);

    /* Adjust the current data pointer as well.  */
    transfer_request->ux_slave_transfer_request_current_data_pointer =
        transfer_request->ux_slave_transfer_request_data_pointer;

    /* Update the transfer request endpoint pointer with the default endpoint.  */
    transfer_request->ux_slave_transfer_request_endpoint = &device->ux_slave_device_control_endpoint;

    /* The control endpoint max packet size needs to be filled manually in its descriptor.  */
    transfer_request->ux_slave_transfer_request_endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize =
        device->ux_slave_device_descriptor.bMaxPacketSize0;

    /* On the control endpoint, always expect the maximum.  */
    transfer_request->ux_slave_transfer_request_requested_length =
        device->ux_slave_device_descriptor.bMaxPacketSize0;

    /* Attach the control endpoint to the transfer request.  */
    transfer_request->ux_slave_transfer_request_endpoint = &device->ux_slave_device_control_endpoint;

    /* Create the default control endpoint attached to the device.
     * Once this endpoint is enabled, the host can then send a setup packet
     * The device controller will receive it and will call the setup function
     * module.  */
    dcd->ux_slave_dcd_function(dcd, UX_DCD_CREATE_ENDPOINT, (void *) &device->ux_slave_device_control_endpoint);

    /* Ensure the control endpoint is properly reset.  */
    device->ux_slave_device_control_endpoint.ux_slave_endpoint_state = (uint32_t) UX_ENDPOINT_RESET;

    /* A SETUP packet is a DATA IN operation.  */
    transfer_request->ux_slave_transfer_request_phase = (uint32_t) UX_TRANSFER_PHASE_DATA_IN;

    /* Check the status change callback.  */
    if (_ux_system_slave->ux_system_slave_change_function != UX_NULL)
    {
        /* Inform the application if a callback function was programmed.  */
        _ux_system_slave->ux_system_slave_change_function(UX_DEVICE_ATTACHED);
    }

    /* We are now ready for the USB device to accept the first packet when connected.  */
    return UX_SUCCESS;
}                                      /* End of function usb_peri_usbx_initialize_complete() */

  #if defined(USB_CFG_PAUD_USE)

/******************************************************************************
 * Function Name   : usb_peri_usbx_set_control_length
 * Description     :
 * Argument        : usb_setup_t  *p_req        : Pointer to usb_utr_t structure
 * Return          : none
 ******************************************************************************/
void usb_peri_usbx_set_control_length (usb_setup_t * p_req)
{
    *g_p_usb_actural_length[USB_PIPE0] = p_req->request_length;
}                                      /* End of function usb_peri_usbx_set_control_length() */

  #endif /* #if defined(USB_CFG_PAUD_USE) */

/******************************************************************************
 * Function Name   : usb_peri_usbx_transfer_complete_cb
 * Description     : CallBack Function called when the data transfer completion
 * Argument        : usb_utr_t  *p_mess         : Pointer to usb_utr_t structure
 *                 : uint16_t   data1           : Not used
 *                 : uint16_t   data2           : Not used
 * Return          : none
 ******************************************************************************/
static void usb_peri_usbx_transfer_complete_cb (usb_utr_t * p_mess, uint16_t data1, uint16_t data2)
{
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);
    uint16_t pipe;
    uint16_t pipe_reg;

    pipe = p_mess->keyword;

    tx_semaphore_put(&g_usb_peri_usbx_sem[pipe]);

    hw_usb_write_pipesel(p_mess, pipe);
    pipe_reg = hw_usb_read_pipecfg(p_mess);

    if (0 != (pipe_reg & USB_DIRFIELD))
    {
        /* transmission */
        *g_p_usb_actural_length[pipe] = p_mess->read_req_len;
    }
    else
    {
        /* reception */
        *g_p_usb_actural_length[pipe] = p_mess->read_req_len - p_mess->tranlen;
    }
}                                      /* End of function usb_peri_usbx_transfer_complete_cb() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_to_basic
 * Description     : Porting Layer from USBX to USB basic driver
 * Argument        : UX_SLAVE_DCD *dcd  :
 *                 : UINT function      :
 *                 : VOID *parameter    :
 * Return          : none
 ******************************************************************************/
static UINT usb_peri_usbx_to_basic (UX_SLAVE_DCD * dcd, UINT function, VOID * parameter)
{
    volatile uint32_t   status = (uint32_t) UX_SUCCESS;
    UX_SLAVE_ENDPOINT * endpoint;
    UX_SLAVE_TRANSFER * transfer_request;
    usb_utr_t           tran_data;
    uint32_t            size;
    uint16_t            pipe = 0;
    usb_er_t            err;
    uint8_t             module_number;
    uint32_t            endpoint_index;

    /* Check the status of the controller.  */
    if (dcd->ux_slave_dcd_status == (uint32_t) UX_UNUSED)
    {
        return (uint32_t) UX_CONTROLLER_UNKNOWN;
    }

    module_number = USB_CFG_IP0;
  #if defined(R_USB_HS0_BASE)
    if (R_USB_HS0_BASE == dcd->ux_slave_dcd_io)
    {
        module_number = USB_CFG_IP1;
    }
  #endif                               /* defined(R_USB_HS0_BASE) */
    tran_data.ip = module_number;

    /* Look at the function and route it.  */
    switch (function)
    {
        case (uint32_t) UX_DCD_GET_FRAME_NUMBER:
        {
            status = (uint32_t) UX_SUCCESS;
            break;
        }

        case (uint32_t) UX_DCD_TRANSFER_REQUEST:
        {
            transfer_request = (UX_SLAVE_TRANSFER *) parameter;
            endpoint         = transfer_request->ux_slave_transfer_request_endpoint;
            endpoint_index   = endpoint->ux_slave_endpoint_descriptor.bEndpointAddress;
            if (0 != endpoint_index)
            {
                pipe = usb_pstd_epadr2pipe((uint16_t) endpoint_index, &tran_data);
            }
            else
            {
                pipe = USB_PIPE0;
  #if defined(USB_CFG_PAUD_USE)
                if ((transfer_request->ux_slave_transfer_request_setup[0] & UX_ENDPOINT_DIRECTION) == UX_ENDPOINT_IN)
                {
                    transfer_request->ux_slave_transfer_request_phase = UX_TRANSFER_PHASE_DATA_OUT;
                }
                else
                {
                    transfer_request->ux_slave_transfer_request_phase = UX_TRANSFER_PHASE_DATA_IN;
                }
  #endif                                                                         /* #if defined(USB_CFG_PAUD_USE) */
            }

            size = transfer_request->ux_slave_transfer_request_requested_length; /* Save Read Request Length */
            g_p_usb_actural_length[pipe] = &(transfer_request->ux_slave_transfer_request_actual_length);

            if (pipe != USB_PIPE0)
            {
                tran_data.read_req_len = size;
                tran_data.keyword      = pipe;                                                     /* Pipe Number */
                tran_data.p_tranadr    = transfer_request->ux_slave_transfer_request_data_pointer; /* Data address */
                tran_data.tranlen      = size;                                                     /* Data Size */
                tran_data.complete     = usb_peri_usbx_transfer_complete_cb;                       /* Callback function */
  #if (USB_CFG_DMA == USB_CFG_ENABLE)
                if (0 != g_p_usbx_transfer_tx)
                {
                    tran_data.p_transfer_tx = g_p_usbx_transfer_tx;
                }
                else
                {
                    tran_data.p_transfer_tx = 0;
                }

                if (0 != g_p_usbx_transfer_rx)
                {
                    tran_data.p_transfer_rx = g_p_usbx_transfer_rx;
                }
                else
                {
                    tran_data.p_transfer_rx = 0;
                }
  #endif
                err = usb_pstd_transfer_start(&tran_data);

                if (USB_OK == err)
                {
                    if (USB_YES == g_usb_peri_usbx_is_detach[pipe])
                    {
                        g_usb_peri_usbx_is_detach[pipe] = USB_NO;
  #if defined(USB_CFG_PMSC_USE)
                        if ((USB_CFG_PMSC_BULK_IN == pipe) || (USB_CFG_PMSC_BULK_OUT == pipe))
                        {
                            status = (uint32_t) UX_TRANSFER_ERROR;
                        }
                        else
                        {
                            status = (uint32_t) UX_SUCCESS;
                        }

  #elif defined(USB_CFG_PHID_USE)
                        if (USB_CFG_PHID_INT_OUT == pipe)
                        {
                            status = (uint32_t) UX_TRANSFER_ERROR;
                        }
                        else
                        {
                            status = (uint32_t) UX_SUCCESS;
                        }

  #else                                /* defined(USB_CFG_PMSC_USE) */
   #if defined(USB_CFG_PCDC_USE)
                        transfer_request->ux_slave_transfer_request_completion_code = UX_TRANSFER_ERROR;
   #endif                              /* defined(USB_PCDC_USE) */
                        status = (uint32_t) UX_SUCCESS;
  #endif /* define(USB_CFG_PMSC_USE */
                    }
                    else
                    {
  #if defined(USB_CFG_PMSC_USE)

                        /*  The error code other UX_SUCCESS must be returned than       *
                         *  when USB peripheral device status is not CONFIGURED status. */
                        uint16_t dvsq;
                        dvsq = hw_usb_read_intsts(module_number);

                        if (USB_DS_CNFG == (dvsq & USB_DVSQ))
                        {
                            status = (uint32_t) UX_SUCCESS;
                        }
                        else
                        {
                            status = (uint32_t) UX_TRANSFER_ERROR;
                        }

  #else                                /* defined(USB_CFG_PMSC_USE) */
   #if defined(USB_CFG_PCDC_USE)
                        transfer_request->ux_slave_transfer_request_completion_code = UX_SUCCESS;
   #endif                              /* defined(USB_PCDC_USE) */
                        status = (uint32_t) UX_SUCCESS;
  #endif /* define(USB_CFG_PMSC_USE */
                    }
                }
                else
                {
                    status = (uint32_t) UX_TRANSFER_ERROR;
                }
            }
            else
            {
                if (transfer_request->ux_slave_transfer_request_phase == UX_TRANSFER_PHASE_DATA_OUT)
                {
                    if (USB_MODE_PERI == g_usb_usbmode[tran_data.ip])
                    {
                        if (USB_YES == g_usb_pstd_pipe0_request)
                        {
                            status = (uint32_t) UX_TRANSFER_ERROR;
                        }

                        g_usb_pstd_std_request = USB_YES;
                        usb_pstd_ctrl_read(size, transfer_request->ux_slave_transfer_request_data_pointer, &tran_data);
                    }
                }
                else
                {
                    if (USB_MODE_PERI == g_usb_usbmode[module_number])
                    {
                        {
                            if (USB_ON == g_usb_pstd_pipe0_request)
                            {
                                // return USB_QOVR;
                                status = (uint32_t) UX_TRANSFER_ERROR;
                            }

                            g_usb_pstd_std_request = USB_YES;
                            usb_pstd_ctrl_write(size,
                                                transfer_request->ux_slave_transfer_request_data_pointer,
                                                &tran_data);
                        }
                    }
                }
            }

            break;
        }

        case (uint32_t) UX_DCD_TRANSFER_ABORT:
  #if defined(USB_CFG_PCDC_USE)
            {
                CHAR         * name;
                ULONG          current_value;
                TX_THREAD    * first_suspended;
                ULONG          suspended_count;
                TX_SEMAPHORE * next_semaphore;

                transfer_request = (UX_SLAVE_TRANSFER *) parameter;
                endpoint         = transfer_request->ux_slave_transfer_request_endpoint;
                endpoint_index   = endpoint->ux_slave_endpoint_descriptor.bEndpointAddress;
                if (0 != endpoint_index)
                {
                    pipe = usb_pstd_epadr2pipe((uint16_t) endpoint_index, &tran_data);
                }

                tx_semaphore_info_get(&g_usb_peri_usbx_sem[pipe],
                                      &name,
                                      &current_value,
                                      &first_suspended,
                                      &suspended_count,
                                      &next_semaphore);

                if (suspended_count == 1)
                {
                    _ux_utility_thread_suspend(first_suspended);
                    tx_semaphore_put(&g_usb_peri_usbx_sem[pipe]);
                }

                break;
            }
  #elif defined(USB_CFG_PPRN_USE)      /* #if defined(USB_CFG_PCDC_USE) */
            {
                for (pipe = USB_MIN_PIPE_NO; pipe < (USB_MAXPIPE_NUM + 1); pipe++)
                {
                    if (USB_TRUE == g_usb_pipe_table[tran_data.ip][pipe].use_flag)
                    {
                        usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_STOP, &tran_data);
                    }
                }

                break;
            }
  #endif

        case (uint32_t) UX_DCD_CREATE_ENDPOINT:
        {
            break;
        }

        case (uint32_t) UX_DCD_DESTROY_ENDPOINT:
        {
            status = (uint32_t) UX_SUCCESS;
            break;
        }

        case (uint32_t) UX_DCD_RESET_ENDPOINT:
        {
            break;
        }

        case (uint32_t) UX_DCD_STALL_ENDPOINT:
        {
            endpoint       = (UX_SLAVE_ENDPOINT *) parameter;
            endpoint_index = endpoint->ux_slave_endpoint_descriptor.bEndpointAddress;
            if (0 != endpoint_index)
            {
                pipe = usb_pstd_epadr2pipe((uint16_t) endpoint_index, &tran_data);
            }
            else
            {
                pipe = USB_PIPE0;
            }

            usb_pstd_set_stall(pipe, &tran_data);

            status = (uint32_t) UX_SUCCESS;

            break;
        }

        case (uint32_t) UX_DCD_SET_DEVICE_ADDRESS:
        {
            status = (uint32_t) UX_SUCCESS;
            break;
        }

        case (uint32_t) UX_DCD_CHANGE_STATE:
        {
            if (parameter == (void *) UX_DEVICE_REMOTE_WAKEUP)
            {
                /* This function is called when the device wants to wake up the host.  */
                usb_peri_usbx_remote_wakeup(module_number);
            }
            else
            {
                if (parameter == (void *) UX_DEVICE_CONFIGURED)
                {
                    if (UX_NULL != _ux_system_slave->ux_system_slave_change_function)
                    {
                        _ux_system_slave->ux_system_slave_change_function(UX_DEVICE_CONFIGURED);
                    }
                }

                status = (uint32_t) UX_SUCCESS;
            }

            break;
        }

        case (uint32_t) UX_DCD_ENDPOINT_STATUS:
        {
            break;
        }

        default:
        {
            /* If trace is enabled, insert this event into the trace buffer.  */
            status = (uint32_t) UX_FUNCTION_NOT_SUPPORTED;
            break;
        }
    }

    /* Return completion status.  */
    return status;
}                                      /* End of function usb_peri_usbx_to_basic() */

/*******************************************************************************************************************//**
 * Function Name   : usb_peri_usbx_remote_wakeup
 * Description     : Remote wake up
 * Argument        : uint8_t module_number :
 * Return          : UX_SUCCESS
 *                 : UX_ERROR
 **********************************************************************************************************************/
uint32_t usb_peri_usbx_remote_wakeup (uint8_t module_number)
{
    uint16_t buf;
    buf  = hw_usb_read_intsts(module_number);
    buf &= USB_DVSQ;
    if (USB_DS_SPD_CNFG == buf)
    {
        _ux_utility_delay_ms(5U);
        hw_usb_pset_wkup(module_number);

        return (uint32_t) UX_SUCCESS;
    }

    return (uint32_t) UX_ERROR;
}

  #if defined(USB_CFG_PMSC_USE)

/******************************************************************************
 * Function Name   : usb_peri_usbx_media_read
 * Description     : Wrapper function for media read
 * Argument        : VOID   *storage        : Pointer to VOID area
 *                 : ULONG  lun             : Logical Unit Number
 *                 : UCHAR  *data_pointer   : Pointer to area to store read data
 *                 : ULONG  number_blocks   : Read data size
 *                 : ULONG  lba             : logical block address
 *                 : ULNG   *media_status   : Pointer to area to store media status
 * Return          : UX_SUCCESS
 ******************************************************************************/
static UINT usb_peri_usbx_media_read (VOID  * storage,
                                      ULONG   lun,
                                      UCHAR * data_pointer,
                                      ULONG   number_blocks,
                                      ULONG   lba,
                                      ULONG * media_status)
{
    FSP_PARAMETER_NOT_USED(storage);
    FSP_PARAMETER_NOT_USED(lun);
    FSP_PARAMETER_NOT_USED(media_status);

    fsp_err_t               err_code;
    rm_block_media_status_t status;
    uint32_t                timeout = UINT32_MAX;
    rm_block_media_status_t status_wait;
    uint32_t                timeout_wait = UINT32_MAX;

    err_code = gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err_code, err_code);
    if ((status.initialized == true) && (status.busy == false) && (status.media_inserted == true))
    {
        err_code = gp_block_media_instance->p_api->read(gp_block_media_instance->p_ctrl,
                                                        (uint8_t * const) data_pointer,
                                                        (uint32_t const) lba,
                                                        (uint32_t const) number_blocks);
        if (err_code == FSP_SUCCESS)
        {
            while (timeout > 0)
            {
                timeout--;
                if (g_blockmedia_complete_event == true)
                {
                    break;
                }

                if (g_blockmedia_poll_status_events == true)
                {
                    memset(&status_wait, 0U, sizeof(status_wait));
                    do
                    {
                        timeout_wait--;
                        if (0U == timeout_wait)
                        {
                            break;
                        }

                        gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status_wait);
                    } while (status.busy);

                    g_blockmedia_complete_event     = false;
                    g_blockmedia_poll_status_events = false;
                    break;
                }
            }

            g_blockmedia_complete_event = false;
        }
    }
    else
    {
        g_status_busy = true;
    }

    if (err_code == FSP_SUCCESS)
    {
        return UX_SUCCESS;
    }
    else
    {
        return UX_ERROR;
    }
}                                      /* End of function usb_peri_usbx_media_read() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_media_write
 * Description     : Wrapper function for media write
 * Argument        : VOID   *storage        : Pointer to VOID area
 *                 : ULONG  lun             : Logical Unit Number
 *                 : UCHAR  *data_pointer   : Pointer to the area write data is stored
 *                 : ULONG  number_blocks   : Write data size
 *                 : ULONG  lba             : logical block address
 *                 : ULNG   *media_status   : Pointer to area to store media status
 * Return          : UX_SUCCESS
 ******************************************************************************/
static UINT usb_peri_usbx_media_write (VOID  * storage,
                                       ULONG   lun,
                                       UCHAR * data_pointer,
                                       ULONG   number_blocks,
                                       ULONG   lba,
                                       ULONG * media_status)
{
    FSP_PARAMETER_NOT_USED(storage);
    FSP_PARAMETER_NOT_USED(lun);
    FSP_PARAMETER_NOT_USED(media_status);

    fsp_err_t               err_code;
    rm_block_media_status_t status;
    uint32_t                timeout = UINT32_MAX;
    rm_block_media_status_t status_wait;
    uint32_t                timeout_wait = UINT32_MAX;

    err_code = gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err_code, err_code);
    if ((status.initialized == true) && (status.busy == false) && (status.media_inserted == true))
    {
        err_code =
            gp_block_media_instance->p_api->write(gp_block_media_instance->p_ctrl, (uint8_t * const) data_pointer,
                                                  (uint32_t const) lba, (uint32_t const) number_blocks);
        if (err_code == FSP_SUCCESS)
        {
            while (timeout > 0)
            {
                timeout--;
                if (g_blockmedia_complete_event == true)
                {
                    break;
                }

                if (g_blockmedia_poll_status_events == true)
                {
                    memset(&status_wait, 0U, sizeof(status_wait));
                    do
                    {
                        timeout_wait--;
                        if (0U == timeout_wait)
                        {
                            break;
                        }

                        gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status_wait);
                    } while (status.busy);

                    g_blockmedia_complete_event     = false;
                    g_blockmedia_poll_status_events = false;
                    break;
                }
            }

            g_blockmedia_complete_event = false;
        }
    }
    else
    {
        g_status_busy = true;
    }

    if (err_code == FSP_SUCCESS)
    {
        return UX_SUCCESS;
    }
    else
    {
        return UX_ERROR;
    }
}                                      /* End of function usb_peri_usbx_media_write() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_media_status
 * Description     : Block media status check function
 * Argument        : VOID   *storage        : Pointer to VOID area
 *                 : ULONG  lun             : Logical Unit Number
 *                 : ULONG  media_id        : Media ID number
 *                 : ULNG   *media_status   : Pointer to area to store media status
 * Return          : UX_SUCCESS
 ******************************************************************************/
static UINT usb_peri_usbx_media_status (VOID * storage, ULONG lun, ULONG media_id, ULONG * media_status)
{
    (void) storage;
    (void) lun;
    (void) media_id;
    (void) media_status;

    return UX_SUCCESS;
}                                      /* End of function usb_peri_usbx_media_status() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_pmsc_media_initialize
 * Description     : Block media initialize processing
 * Argument        : void const * p_context :
 * Return          : FSP_SUCCESS/FSP_ERR_USB_FAILED
 ******************************************************************************/
fsp_err_t usb_peri_usbx_pmsc_media_initialize (void const * p_context)
{
    fsp_err_t               err_code = FSP_ERR_USB_FAILED;
    rm_block_media_status_t status;
    rm_block_media_info_t   info;

    if (USB_NULL != p_context)
    {
        gp_block_media_instance = (rm_block_media_instance_t *) p_context;
        err_code                = gp_block_media_instance->p_api->open(gp_block_media_instance->p_ctrl,
                                                                       gp_block_media_instance->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err_code, FSP_ERR_USB_FAILED);
        err_code = gp_block_media_instance->p_api->mediaInit(gp_block_media_instance->p_ctrl);
        if (FSP_SUCCESS == err_code)
        {
            err_code = gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status);
            if (FSP_SUCCESS == err_code)
            {
                if ((status.initialized == true) && (status.busy == false) && (status.media_inserted == true))
                {
                    err_code = gp_block_media_instance->p_api->infoGet(gp_block_media_instance->p_ctrl, &info);
                    if (FSP_SUCCESS == err_code)
                    {
                        g_media_total_sector      = info.num_sectors;
                        g_media_sector_size_bytes = info.sector_size_bytes;
                        g_media_write_protected   = info.write_protected;
                    }
                    else
                    {
                        gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
                        err_code = FSP_ERR_USB_FAILED;
                    }
                }
                else
                {
                    gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
                    err_code = FSP_ERR_USB_FAILED;
                }
            }
            else
            {
                gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
                err_code = FSP_ERR_USB_FAILED;
            }
        }
        else
        {
            gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
            err_code = FSP_ERR_USB_FAILED;
        }
    }

    return err_code;
}                                      /* End of function usb_peri_usbx_pmsc_media_initialize() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_media_close
 * Description     : Block media close processing
 * Argument        : void const * p_context :
 * Return          : FSP_SUCCESS
 ******************************************************************************/
fsp_err_t usb_peri_usbx_media_close (void)
{
    fsp_err_t err_code;

    err_code = gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);

    return err_code;
}                                      /* End of function usb_peri_usbx_media_close() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_pmsc_storage_init
 * Description     : Initialization processing for USBX PMSC
 * Argument        : None
 * Return          : None
 ******************************************************************************/
static void usb_peri_usbx_pmsc_storage_init (void)
{
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_number_lun = 1;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_last_lba =
        (g_media_total_sector - 1);
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_block_length =
        g_media_sector_size_bytes;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_type =
        UX_SLAVE_CLASS_STORAGE_MEDIA_FAT_DISK;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_removable_flag =
        USB_PERI_USBX_REMOVABLE_MEDIA;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_read_only_flag =
        g_media_write_protected;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_read =
        usb_peri_usbx_media_read;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_write =
        usb_peri_usbx_media_write;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_flush =
        UX_NULL;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_status =
        usb_peri_usbx_media_status;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_notification =
        UX_NULL;

    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_instance_activate        = UX_NULL;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_instance_deactivate      = UX_NULL;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_vendor_id      = (UCHAR *) USB_CFG_PMSC_VENDOR;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_product_id     = (UCHAR *) USB_CFG_PMSC_PRODUCT;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_product_rev    = (UCHAR *) USB_CFG_PMSC_REVISION;
    g_usb_peri_usbx_pmsc_parameter.ux_slave_class_storage_parameter_product_serial = (uint8_t *) "NULL";

    ux_device_stack_class_register(_ux_system_slave_class_storage_name,
                                   ux_device_class_storage_entry,
                                   1,
                                   0x00,
                                   (void *) &g_usb_peri_usbx_pmsc_parameter);
}                                      /* End of function usb_peri_usbx_pmsc_storage_init() */

/******************************************************************************
 * Function Name   : usb_peri_usbx_pmsc_storage_uninit
 * Description     : Uninitialization processing for USBX PMSC
 * Argument        : None
 * Return          : None
 ******************************************************************************/
static void usb_peri_usbx_pmsc_storage_uninit (void)
{
    ux_device_stack_class_unregister(_ux_system_slave_class_storage_name, ux_device_class_storage_entry);
}                                      /* End of function usb_peri_usbx_pmsc_storage_uninit() */

/******************************************************************************
 * Function Name   : r_usb_pmsc_block_media_event_callback
 * Description     : Callback for USBX PMSC
 * Argument        : p_args : Pointer to rm_block_media_callback_args_t structure
 * Return          : None
 ******************************************************************************/
void r_usb_pmsc_block_media_event_callback (rm_block_media_callback_args_t * p_args)
{
    if (RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED == p_args->event)
    {
        g_card_inserted = true;
    }

    if (RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED == p_args->event)
    {
        g_card_inserted = false;
    }

    if (RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE == p_args->event)
    {
        g_blockmedia_complete_event = true;
    }

    if (RM_BLOCK_MEDIA_EVENT_POLL_STATUS & p_args->event)
    {
        g_blockmedia_poll_status_events = true;
    }
}                                      /* End of function r_usb_pmsc_block_media_event_callback() */

  #endif                               /* defined(USB_CFG_PMSC_USE) */

 #endif                                /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : usb_host_usbx_initialize
 * Description     : Initialization processing
 * Argument        : UX_HCD * hcd : Pointer to UX_HCD structure
 * Return          : UX_SUCCESS
 ******************************************************************************/
UINT usb_host_usbx_initialize (UX_HCD * hcd)
{
    uint32_t status;

    /* Initialize USB peripheral except interrupts. */
    status = usb_host_usbx_initialize_common(hcd);
    if (UX_SUCCESS == status)
    {
        /* Enable USB interrupts to activate USB port. */
        usb_host_usbx_initialize_common_complete(hcd);
    }

    return status;
}                                      /* End of function usb_host_usbx_initialize() */

/******************************************************************************
 * Function Name   : usb_host_usbx_initialize_common
 * Description     : Initialization processing
 * Argument        : UX_HCD * hcd : Pointer to UX_HCD structure
 * Return          : UX_SUCCESS
 ******************************************************************************/
static uint32_t usb_host_usbx_initialize_common (UX_HCD * hcd)
{
    /* Set the state of the controller to HALTED first.  */
    hcd->ux_hcd_status = (uint32_t) UX_HCD_STATUS_HALTED;

    hcd->ux_hcd_available_bandwidth = UX_FSP_HC_AVAILABLE_BANDWIDTH;

    /* Initialize the function collector for this HCD.  */
    hcd->ux_hcd_entry_function = usb_host_usbx_to_basic;

    /* Get the number of ports on the controller. The number of ports needs to be reflected both
     * for the generic HCD container and the local Synergy container.  */
    hcd->ux_hcd_nb_root_hubs = 1U;

  #if defined(USB_CFG_OTG_USE)
    if (R_USB_HS0_BASE == hcd->ux_hcd_io)
    {
        _ux_system_otg->ux_system_otg_function = usb2_otg_hnp_swap;
    }
    else
    {
        _ux_system_otg->ux_system_otg_function = usb_otg_hnp_swap;
    }
  #endif                               /* defined(USB_CFG_OTG_USE) */

    /* Return successful completion.  */
    return (uint32_t) UX_SUCCESS;
}                                      /* End of function usb_host_usbx_initialize_common() */

/******************************************************************************
 * Function Name   : usb_host_usbx_initialize_common_complete
 * Description     : Initialization processing
 * Argument        : UX_HCD * hcd : Pointer to UX_HCD structure
 * Return          : None
 ******************************************************************************/
static void usb_host_usbx_initialize_common_complete (UX_HCD * hcd)
{
    /* Set the controller to operational mode.  */
    hcd->ux_hcd_status = (uint32_t) UX_HCD_STATUS_OPERATIONAL;
}                                      /* End of function usb_host_usbx_initialize_common_complete() */

/******************************************************************************
 * Function Name   : usb_host_usbx_uninitialize
 * Description     : Uninitialization processing
 * Argument        : hcd_io: USB module start address
 * Return          : UX_SUCCESS
 ******************************************************************************/
uint32_t usb_host_usbx_uninitialize (uint32_t hcd_io)
{
    UX_HCD * hcd;

    (void) hcd_io;

    hcd = _ux_system_host->ux_system_host_hcd_array;

    hcd->ux_hcd_status = (uint32_t) UX_UNUSED;

    /* Set the hcd controller hardware to unknown.  */
    hcd->ux_hcd_controller_hardware = UX_NULL;

    /* Reset HCD controller type. */
    hcd->ux_hcd_controller_type = 0U;

    /* Initialize the max bandwidth for periodic endpoints to zero. */
    hcd->ux_hcd_available_bandwidth = 0UL;

    /* Initialize the function collector for this HCD to NULL.  */
    hcd->ux_hcd_entry_function = UX_NULL;

    /* Set the number of ports on the controller to zero.  */
    hcd->ux_hcd_nb_root_hubs = 0U;

    return (uint32_t) UX_SUCCESS;
}                                      /* End of function usb_host_usbx_uninitialize() */

/******************************************************************************
 * Function Name    : usb_host_usbx_configured
 * Description      : Callback function for CDC device configuered
 * Argument         : usb_utr_t    *p_utr    : Pointer to usb_utr_t structure.
 *                  : uint16_t     devadr  : Device Adrress
 *                  : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
static void usb_host_usbx_configured (usb_utr_t * p_utr, uint16_t devadr, uint16_t data2)
{
    (void) data2;
    (void) p_utr;
    (void) devadr;
}                                      /* End of function usb_host_usbx_configured() */

/******************************************************************************
 * Function Name    : usb_host_usbx_configured
 * Description      : USB pipe registration processing
 * Argument         : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *                  : uint16_t     devadr  : Device Adrress
 * Return value    : none
 ******************************************************************************/
static void usb_host_usbx_set_pipe_registration (usb_utr_t * ptr, uint16_t dev_addr)
{
    uint8_t pipe_no;

    /* Device address check */
    if (0 != dev_addr)
    {
        /* Search use pipe block */
        /* WAIT_LOOP */
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
        {
            /* Check use block */
            if (USB_TRUE == g_usb_pipe_table[ptr->ip][pipe_no].use_flag)
            {
                /* Check USB Device address */
                if ((uint16_t) (dev_addr << USB_DEVADDRBIT) ==
                    (uint16_t) (g_usb_pipe_table[ptr->ip][pipe_no].pipe_maxp & USB_DEVSEL))
                {
                    usb_hstd_set_pipe_reg(ptr, pipe_no);
                }
            }
        }
    }
    else
    {
        /* Error */
        USB_PRINTF1("SmplOpen adr error %x\n", dev_addr);
    }
}                                      /* End of function usb_host_usbx_set_pipe_registration() */

/******************************************************************************
 * Function Name   : usb_hcdc_detach
 * Description     : Callback function for USB device detach
 * Argument        : usb_utr_t    *p_utr  : Pointer to usb_utr_t structure.
 *                 : uint16_t     devadr  : Device Adrress
 *                 : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
static void usb_host_usbx_detach (usb_utr_t * p_utr, uint16_t devadr, uint16_t data2)
{
    UX_HCD * hcd;

    (void) data2;
    hcd = _ux_system_host->ux_system_host_hcd_array;

    usb_hstd_clr_pipe_table(p_utr->ip, devadr);
    _ux_host_stack_rh_device_extraction(hcd, 0);
}                                      /* End of function usb_host_usbx_detach() */

/******************************************************************************
 * Function Name : usb_hcdc_init
 * Description   : Initialize of Host USB driver.
 * Arguments     : usb_utr_t    *p_utr  : Pointer to usb_utr_t structure.
 *               : uint16_t     data1   : not use
 *               : uint16_t     data2   : not use
 * Return value    : none
 ******************************************************************************/
static void usb_host_usbx_init (usb_utr_t * p_utr, uint16_t data1, uint16_t data2)
{
    (void) p_utr;
    (void) data1;
    (void) data2;
}                                      /* End of function usb_host_usbx_init() */

/******************************************************************************
 * Function Name   : usb_host_usbx_registration
 * Description     : registration of Communications Devices class Driver
 * Argument        : usb_utr_t    *p_utr    : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_host_usbx_registration (usb_utr_t * p_utr)
{
    usb_hcdreg_t driver;
  #if USB_CFG_HUB == USB_CFG_ENABLE
    uint8_t i;
  #endif                               /* USB_CFG_HUB == USB_CFG_ENABLE */

    /* Driver registration */
  #if defined(USB_CFG_HCDC_USE)
   #if USB_CFG_HCDC_IFCLS == USB_CFG_CDC
    driver.ifclass = (uint16_t) USB_IFCLS_CDC; /* Interface class : CDC Communications Interface */
   #else                                       /* USB_CFG_HCDC_IFCLS == USB_CFG_CDC */
    driver.ifclass = (uint16_t) USB_IFCLS_VEN; /* CDC Communications Interface */
   #endif /* USB_CFG_HCDC_IFCLS == USB_CFG_CDC */
  #endif /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_HHID_USE)
    driver.ifclass = (uint16_t) USB_IFCLS_HID; /* Interface class : HID */
  #endif /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_HMSC_USE)
    driver.ifclass = (uint16_t) USB_IFCLS_MAS; /* Interface class : HID */
  #endif /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_HPRN_USE)
    driver.ifclass = (uint16_t) USB_IFCLS_PRN; /* Interface class : Printer */
  #endif /* defined(USB_CFG_HPRN_USE) */

  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    driver.p_tpl = (uint16_t *) USB_CFG_TPL_TABLE;
  #else                                                              /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.p_tpl = (uint16_t *) &g_usb_host_usbx_device_tpl;         /* Target peripheral list */
  #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.classinit  = (usb_cb_t) &usb_host_usbx_init;              /* Driver init */
    driver.classcheck = (usb_cb_check_t) &usb_host_usbx_class_check; /* Driver check */
    driver.devconfig  = (usb_cb_t) &usb_host_usbx_configured;        /* Device configuered */
    driver.devdetach  = (usb_cb_t) &usb_host_usbx_detach;            /* Device detach */

    driver.devsuspend = (usb_cb_t) &usb_hstd_dummy_function;         /* Device suspend */
    driver.devresume  = (usb_cb_t) &usb_hstd_dummy_function;         /* Device resume */

  #if USB_CFG_HUB == USB_CFG_ENABLE

    /* WAIT_LOOP */
    for (i = 0; i < USB_MAX_CONNECT_DEVICE_NUM; i++)  /* Loop support CDC device count */
    {
        usb_hstd_driver_registration(p_utr, &driver); /* Host CDC class driver registration. */
    }

   #if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HUB_TSK, USB_PRI_3);    /* Hub Task Priority set */
   #endif /* (BSP_CFG_RTOS == 0) */
    usb_hhub_registration(p_utr, USB_NULL);           /* Hub registration. */
  #else                                               /* USB_CFG_HUB == USB_CFG_ENABLE */
    usb_hstd_driver_registration(p_utr, &driver);     /* Host CDC class driver registration. */
  #endif /* USB_CFG_HUB == USB_CFG_ENABLE */
}                                                     /* End of function usb_host_usbx_registration() */

/******************************************************************************
 * Function Name    : usb_host_usbx_class_check
 * Description      : class check.
 * Arguments        : usb_utr_t    *p_utr   : Pointer to usb_utr_t structure.
 *                  : uint16_t     **table  : Pointer to data table.
 * Return           : none
 ******************************************************************************/
void usb_host_usbx_class_check (usb_utr_t * p_utr, uint16_t ** table)
{
  #if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HPRN_USE)
    uint16_t  speed;
    uint16_t  length;
    uint16_t  offset;
    uint16_t  usb_class;
    uint8_t * p_config;
   #if !defined(USB_CFG_HMSC_USE)
    uint8_t              pipe_no;
    usb_pipe_table_reg_t ep_tbl;
   #endif                              /* #if !defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HHID_USE)
    uint8_t num_set_pipe   = 0;
    uint8_t set_pipe_no[2] = {0, 0};
   #endif                              /* defined(USB_CFG_HHID_USE) */

    speed    = *table[6];
    p_config = (uint8_t *) table[1];
    length   = (uint16_t) (*(p_config + 3) << 8);
    length   = (uint16_t) (length + *(p_config + 2));

   #if defined(USB_CFG_HCDC_USE)
    usb_class = USB_CLASS_INTERNAL_HCDC;
   #endif

   #if defined(USB_CFG_HHID_USE)
    usb_class = USB_CLASS_INTERNAL_HHID;
   #endif

   #if defined(USB_CFG_HMSC_USE)
    usb_class = USB_CLASS_INTERNAL_HMSC;
   #endif

   #if defined(USB_CFG_HPRN_USE)
    usb_class = USB_CLASS_INTERNAL_HPRN;
   #endif

    offset = 0;
    while (offset < length)
    {
        if (USB_DT_ENDPOINT == *(p_config + offset + USB_EP_B_DESCRIPTORTYPE))
        {
   #if defined(USB_CFG_HMSC_USE)
            if (USB_EP_IN == (*(p_config + offset + USB_EP_B_ENDPOINTADDRESS) & USB_EP_DIRMASK))
            {
                g_usb_hmsc_in_pipe[p_utr->ip][0] = usb_hstd_make_pipe_reg_info(p_utr->ip,
                                                                               USB_DEVICEADDR,
                                                                               usb_class,
                                                                               speed,
                                                                               (p_config + offset),
                                                                               &g_usb_hmsc_pipe_table[0][
                                                                                   USB_PIPE_DIR_IN]);

                g_usb_hmsc_in_pipectr[p_utr->ip][0] = 0;
            }
            else
            {
                g_usb_hmsc_out_pipe[p_utr->ip][0] = usb_hstd_make_pipe_reg_info(p_utr->ip,
                                                                                USB_DEVICEADDR,
                                                                                usb_class,
                                                                                speed,
                                                                                (p_config + offset),
                                                                                &g_usb_hmsc_pipe_table[0][
                                                                                    USB_PIPE_DIR_OUT]);

                g_usb_hmsc_out_pipectr[p_utr->ip][0] = 0;
            }

   #else                               /* defined(USB_CFG_HMSC_USE) */
            pipe_no = usb_hstd_make_pipe_reg_info(p_utr->ip,
                                                  USB_DEVICEADDR,
                                                  usb_class,
                                                  speed,
                                                  (p_config + offset),
                                                  &ep_tbl);
            if (USB_NULL != pipe_no)
            {
    #if defined(USB_CFG_HHID_USE)
                if ((pipe_no != set_pipe_no[0]) && (pipe_no != set_pipe_no[1]) && (num_set_pipe < 2))
                {
                    set_pipe_no[num_set_pipe] = pipe_no;
                    num_set_pipe++;
                    usb_hstd_set_pipe_info(p_utr->ip, pipe_no, &ep_tbl);
                }

    #else                              /* defined(USB_CFG_HHID_USE) */
                usb_hstd_set_pipe_info(p_utr->ip, pipe_no, &ep_tbl);
    #endif /* defined(USB_CFG_HHID_USE) */
            }
            else
            {
                while (1)
                {
                    ;
                }
            }
   #endif                              /* defined(USB_CFG_HMSC_USE) */
        }

        offset = (uint16_t) (offset + (*(p_config + offset)));
    }
  #endif                               /* defined(USB_CFG_HCDC_USE) | defined(USB_CFG_HHID_USE) */

    *table[3] = USB_OK;                /* Set class check done  */
}                                      /* End of function usb_host_usbx_class_check() */

/******************************************************************************
 * Function Name    : usb_host_usbx_get_speed
 * Description      : Get the connected USB device speed.
 * Arguments        : UX_HCD    *hcd    : Pointer to UX_HCD structure.
 * Return           : USB speed valule
 ******************************************************************************/
static uint32_t usb_host_usbx_get_speed (UX_HCD * hcd)
{
    usb_utr_t utr;
    uint16_t  connect_inf;
    uint32_t  speed;

    if (R_USB_HS0_BASE == hcd->ux_hcd_io)
    {
        utr.ip = USB_IP1;
    }
    else
    {
        utr.ip = USB_IP0;
    }

    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

    connect_inf = usb_cstd_port_speed(&utr);

    if (USB_HSCONNECT == connect_inf)
    {
        speed = (uint32_t) UX_HIGH_SPEED_DEVICE;
    }
    else if (USB_FSCONNECT == connect_inf)
    {
        speed = (uint32_t) UX_FULL_SPEED_DEVICE;
    }
    else
    {
        speed = (uint32_t) UX_LOW_SPEED_DEVICE;
    }

    return speed;
}                                      /* End of function usb_host_usbx_get_speed() */

/******************************************************************************
 * Function Name    : usb_hstd_attach_init_usbx
 * Description      : USBX initialization when attaching USB device
 * Arguments        : None
 * Return           : None
 ******************************************************************************/
void usb_host_usbx_attach_init (uint8_t module_number)
{
    UX_HCD      * hcd;
    UX_DEVICE   * device;
    UX_ENDPOINT * control_endpoint;

    hcd    = _ux_system_host->ux_system_host_hcd_array;
    device = _ux_host_stack_new_device_get();

    device->ux_device_handle        = (uint32_t) device;
    device->ux_device_state         = UX_DEVICE_ATTACHED;
    device->ux_device_parent        = UX_NULL;
    device->ux_device_hcd           = hcd;
    device->ux_device_speed         = usb_host_usbx_get_speed(hcd);
    device->ux_device_port_location = 0;
    device->ux_device_max_power     = UX_FSP_MAX_SELF_POWER;
    device->ux_device_address       = USB_DEVICEADDR;

    control_endpoint                            = &device->ux_device_control_endpoint;
    control_endpoint->ux_endpoint               = (uint32_t) control_endpoint;
    control_endpoint->ux_endpoint_next_endpoint = UX_NULL;
    control_endpoint->ux_endpoint_interface     = UX_NULL;
    control_endpoint->ux_endpoint_device        = device;
    control_endpoint->ux_endpoint_transfer_request.ux_transfer_request_endpoint = control_endpoint;
    control_endpoint->ux_endpoint_descriptor.wMaxPacketSize = UX_DEFAULT_MPS;

    g_p_usbx_device[module_number] = device;

    _ux_utility_semaphore_create(&device->ux_device_protection_semaphore, "ux_host_endpoint0_semaphore", 1);
    tx_semaphore_create(&g_usb_host_usbx_sem[module_number][USB_PIPE0], "USB_FSP_SEMX_HOST", 0);
}                                      /* End of function usb_host_usbx_attach_init() */

/******************************************************************************
 * Function Name   : usb_host_usbx_endpoint_to_pipe
 * Description     : Get USB pipe number based on endpoint.
 * Argument        : uint8_t    module_number   : USB module number
 *                 : uint8_t    ep_number       : Endpoint number
 * Return          : Pipe Number
 ******************************************************************************/
static uint8_t usb_host_usbx_endpoint_to_pipe (uint8_t module_number, uint8_t ep_number)
{
    uint16_t endpoint;
    uint8_t  pipe_no;

    for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
    {
        if (USB_TRUE == g_usb_pipe_table[module_number][pipe_no].use_flag)
        {
            endpoint = g_usb_pipe_table[module_number][pipe_no].pipe_cfg & USB_EPNUMFIELD;
            if ((uint8_t) endpoint == ep_number)
            {
                break;
            }
        }
    }

    return pipe_no;
}                                      /* End of function usb_host_usbx_endpoint_to_pipe() */

/******************************************************************************
 * Function Name   : usb_host_usbx_set_configuration_cb
 * Description     : CallBack Function
 * Argument        : usb_utr_t *p_utr   : Pointer to usb_utr_t structure
 * Return          : none
 ******************************************************************************/
static void usb_host_usbx_set_configuration_cb (usb_utr_t * p_utr, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;
    uint8_t pipe;

    pipe = (uint8_t) p_utr->keyword;

    g_usb_hstd_mgr_mode[p_utr->ip] = USB_CONFIGURED;
    tx_semaphore_put(&g_usb_host_usbx_sem[p_utr->ip][pipe]);
    usb_host_usbx_set_pipe_registration(p_utr, g_usb_hstd_device_addr[p_utr->ip]); /* Host Pipe registration */
    usb_hstd_mgr_snd_mbx(p_utr, (uint16_t) USB_MSG_MGR_SUBMITRESULT, p_utr->keyword, p_utr->status);
} /* End of function usb_pstd_transfer_complete_cb() */

/******************************************************************************
 * Function Name   : usb_host_usbx_class_request_cb
 * Description     : CallBack Function
 * Argument        : usb_utr_t *p_utr   : Pointer to usb_utr_t structure
 * Return          : none
 ******************************************************************************/
static void usb_host_usbx_class_request_cb (usb_utr_t * p_utr, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;
    uint8_t pipe;

    pipe = (uint8_t) p_utr->keyword;

  #if (defined(USB_CFG_HHID_USE) | defined(USB_CFG_OTG_USE))
    *g_p_usb_host_actural_length[p_utr->ip][0] = p_utr->read_req_len - p_utr->tranlen;
  #endif                               /* #if defined(USB_CFG_HHID_USE) */

  #if defined(USB_CFG_HPRN_USE)
    *g_p_usb_host_actural_length[p_utr->ip][0] = p_utr->read_req_len - p_utr->tranlen;
  #endif                               /* #if defined(USB_CFG_HPRN_USE) */

    tx_semaphore_put(&g_usb_host_usbx_sem[p_utr->ip][pipe]);
}                                      /* End of function usb_pstd_transfer_complete_cb() */

/******************************************************************************
 * Function Name   : usb_hstd_transfer_complete_cb
 * Description     : CallBack Function
 * Argument        : usb_utr_t *p_utr   : Pointer to usb_utr_t structure
 * Return          : none
 ******************************************************************************/
static void usb_host_usbx_transfer_complete_cb (usb_utr_t * p_utr, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;
    uint8_t       pipe;
    UX_TRANSFER * transfer_request;
    uint16_t      pipe_reg;
  #if defined(USB_CFG_HCDC_USE)
    UX_HOST_CLASS_CDC_ACM * cdc_acm;
  #endif                               /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_OTG_USE)
    UINT           status;
    CHAR         * p_sem_name;
    ULONG          current_value;
    TX_THREAD    * p_suspend_thread;
    ULONG          suspend_count;
    TX_SEMAPHORE * p_next_sem;
  #endif                               /* defined(USB_CFG_OTG_USE) */

  #if defined(USB_CFG_HMSC_USE)
   #if (USB_CFG_DMA == USB_CFG_ENABLE)
    uint32_t  counter;
    uint8_t * p_read;
    uint8_t * p_write;
   #endif                              /* (USB_CFG_DMA == USB_CFG_ENABLE) */
  #endif                               /* defined(USB_CFG_HMSC_USE) */

    pipe             = (uint8_t) p_utr->keyword;
    transfer_request = g_p_usb_host_usbx_transfer_request[p_utr->ip][pipe];

  #if defined(USB_CFG_HCDC_USE)

    /* Get the class instance for this transfer request.  */
    cdc_acm = (UX_HOST_CLASS_CDC_ACM *) transfer_request->ux_transfer_request_class_instance;
  #endif                               /* defined(USB_CFG_HCDC_USE) */

    if (USB_PIPE0 == pipe)
    {
        tx_semaphore_put(&g_usb_host_usbx_sem[p_utr->ip][pipe]);
    }

    hw_usb_write_pipesel(p_utr, pipe);
    pipe_reg = hw_usb_read_pipecfg(p_utr);

    if (0 != (pipe_reg & USB_DIRFIELD))
    {
        /* OUT */
        *g_p_usb_host_actural_length[p_utr->ip][pipe] = p_utr->read_req_len;
    }
    else
    {
        /* IN */
        *g_p_usb_host_actural_length[p_utr->ip][pipe] = p_utr->read_req_len - p_utr->tranlen;
    }

  #if defined(USB_CFG_HMSC_USE)
    if (USB_DATA_STALL == p_utr->status)
    {
        g_usb_hmsc_in_pipectr[p_utr->ip][0] = 0;
        transfer_request->ux_transfer_request_completion_code = UX_TRANSFER_STALLED;
    }
    else
    {
        transfer_request->ux_transfer_request_completion_code = UX_SUCCESS;

        if (0 != (pipe_reg & USB_DIRFIELD))
        {
            /* OUT */
            g_usb_hmsc_out_pipectr[p_utr->ip][0] = hw_usb_read_pipectr(p_utr, pipe);
        }
        else
        {
            /* IN */
   #if (USB_CFG_DMA == USB_CFG_ENABLE)
            if (0 != g_p_usbx_hmsc_dma_buf[USB_DEVICEADDR - 1])
            {
                p_read  = (uint8_t *) g_p_usbx_hmsc_dma_buf[USB_DEVICEADDR - 1];
                p_write = transfer_request->ux_transfer_request_data_pointer;

                for (counter = 0UL; counter != p_utr->read_req_len; counter++)
                {
                    *(p_write + counter) = *(p_read + counter);
                }

                _ux_utility_memory_free(g_p_usbx_hmsc_dma_buf[USB_DEVICEADDR - 1]);
                g_p_usbx_hmsc_dma_buf[USB_DEVICEADDR - 1] = (void *) 0;
            }
   #endif                              /* (USB_CFG_DMA == USB_CFG_ENABLE) */
            g_usb_hmsc_in_pipectr[p_utr->ip][0] = hw_usb_read_pipectr(p_utr, pipe);
        }
    }
  #endif                               /* #if defined(USB_CFG_HMSC_USE) */

  #if defined(USB_CFG_HHID_USE)
    transfer_request->ux_transfer_request_completion_code = UX_SUCCESS;
    if (UX_NULL != transfer_request->ux_transfer_request_completion_function)
    {
        transfer_request->ux_transfer_request_completion_function(transfer_request);
    }
  #endif                               /* defined(USB_CFG_HHID_USE) */

  #if defined(USB_CFG_HPRN_USE)
    transfer_request->ux_transfer_request_completion_code = UX_SUCCESS;
    if (UX_NULL != transfer_request->ux_transfer_request_completion_function)
    {
        transfer_request->ux_transfer_request_completion_function(transfer_request);
    }
  #endif                               /* defined(USB_CFG_HPRN_USE) */

  #if defined(USB_CFG_HCDC_USE)

    /* Check for the CDC-Data Class.*/
    /* Check if there is a transfer request completion callback function is registered.*/
    /* Check the error condition */
    if ((USB_IFCLS_CDCD == cdc_acm->ux_host_class_cdc_acm_interface->ux_interface_descriptor.bInterfaceClass) &&
        (NULL != transfer_request->ux_transfer_request_completion_function) &&
        (USB_DATA_ERR != p_utr->status))
    {
        /* Set the transfer code to completed.*/
        transfer_request->ux_transfer_request_completion_code = UX_SUCCESS;

        /* Invoke the transfer completion callback function */
        transfer_request->ux_transfer_request_completion_function(transfer_request);
    }
  #endif                               /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_OTG_USE)
    status = tx_semaphore_info_get(&transfer_request->ux_transfer_request_semaphore,
                                   &p_sem_name,
                                   &current_value,
                                   &p_suspend_thread,
                                   &suspend_count,
                                   &p_next_sem);
    if (TX_SUCCESS == status)
    {
        if (0UL != suspend_count)
        {
            _ux_utility_semaphore_put(&transfer_request->ux_transfer_request_semaphore);
        }
    }

  #else                                /* defined(USB_CFG_OTG_USE) */
    _ux_utility_semaphore_put(&transfer_request->ux_transfer_request_semaphore);
  #endif /* defined(USB_CFG_OTG_USE) */
}                                      /* End of function usb_hstd_transfer_complete_cb() */

/******************************************************************************
 * Function Name   : usb_host_usbx_to_basic
 * Description     : Porting Layer from USBX to USB basic driver
 * Argument        : UX_HCD *dcd        :
 *                 : uint32_t function      :
 *                 : void *parameter    :
 * Return          : none
 ******************************************************************************/
static UINT usb_host_usbx_to_basic (UX_HCD * hcd, UINT function, VOID * parameter)
{
    uint32_t      status = (uint32_t) UX_SUCCESS;
    UX_ENDPOINT * endpoint;
    uint8_t       module_number;
    UX_TRANSFER * transfer_request;
    uint8_t       ep_number;
    uint32_t      size;
    uint8_t       pipe_number;
    usb_er_t      err;
  #if defined(USB_CFG_HMSC_USE)
   #if (USB_CFG_DMA == USB_CFG_ENABLE)
    uint32_t allocation_size;
    uint16_t max_packet_size;
    uint8_t  is_in_transfer = USB_NO;
   #endif                              /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */
  #endif                               /* #if defined(USB_CFG_HMSC_USE) */

    if (R_USB_HS0_BASE == hcd->ux_hcd_io)
    {
        module_number = USB_IP1;
    }
    else
    {
        module_number = USB_IP0;
    }

    switch (function)
    {
        case (uint32_t) UX_HCD_TRANSFER_REQUEST:
        {
            transfer_request = (UX_TRANSFER *) parameter;
            endpoint         = (UX_ENDPOINT *) transfer_request->ux_transfer_request_endpoint;
            transfer_request->ux_transfer_request_actual_length = 0UL;

            switch ((endpoint->ux_endpoint_descriptor.bmAttributes) & (uint32_t) UX_FSP_MASK_ENDPOINT_TYPE)
            {
                case (uint32_t) UX_FSP_CONTROL_ENDPOINT:
                {
  #if defined(USB_CFG_HHID_USE)
                    if (0x0 == (transfer_request->ux_transfer_request_type & UX_REQUEST_TYPE_CLASS))
                    {
                        /* In this "case", only SetConfiguraion or the class request is processed.  */
                        if (UX_FSP_SET_CONFIGURATION == transfer_request->ux_transfer_request_function)
                        {
                            g_usb_host_usbx_request[module_number][0] =
                                USB_SET_CONFIGURATION | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
                            g_usb_host_usbx_request[module_number][1] =
                                (uint16_t) transfer_request->ux_transfer_request_value; /* Configuration Number */
                            g_usb_host_usbx_request[module_number][2] = (uint16_t) 0x0000;
                            g_usb_host_usbx_request[module_number][3] = (uint16_t) 0x0000;

                            g_usb_host_usbx_req_msg[module_number].complete =
                                (usb_cb_t) &usb_host_usbx_set_configuration_cb;
                        }
                        else
                        {
                            g_usb_host_usbx_request[module_number][UX_FSP_SETUP_REQUEST_TYPE] =
                                (uint16_t) ((transfer_request->ux_transfer_request_function << 8) |
                                            (transfer_request->ux_transfer_request_type));
                            g_usb_host_usbx_request[module_number][1] =
                                (uint16_t) transfer_request->ux_transfer_request_value;
                            g_usb_host_usbx_request[module_number][2] =
                                (uint16_t) transfer_request->ux_transfer_request_index;
                            g_usb_host_usbx_request[module_number][3] =
                                (uint16_t) transfer_request->ux_transfer_request_requested_length;
                            g_usb_host_usbx_req_msg[module_number].complete =
                                (usb_cb_t) &usb_host_usbx_class_request_cb;
                        }
                    }
                    else
                    {
                        /* Class Request */
                        g_usb_host_usbx_request[module_number][UX_FSP_SETUP_REQUEST_TYPE] =
                            (uint16_t) ((transfer_request->ux_transfer_request_function << 8) |
                                        (transfer_request->ux_transfer_request_type));
                        g_usb_host_usbx_request[module_number][1] =
                            (uint16_t) transfer_request->ux_transfer_request_value;
                        g_usb_host_usbx_request[module_number][2] =
                            (uint16_t) transfer_request->ux_transfer_request_index;
                        g_usb_host_usbx_request[module_number][3] =
                            (uint16_t) transfer_request->ux_transfer_request_requested_length;
                        g_usb_host_usbx_req_msg[module_number].complete = (usb_cb_t) &usb_host_usbx_class_request_cb;
                    }

  #else                                /* #if defined(USB_CFG_HHID_USE) */
                    /* In this "case", only SetConfiguraion or the class request is processed.  */
                    if (UX_FSP_SET_CONFIGURATION == transfer_request->ux_transfer_request_function)
                    {
                        g_usb_host_usbx_request[module_number][0] =
                            USB_SET_CONFIGURATION | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
                        g_usb_host_usbx_request[module_number][1] =
                            (uint16_t) transfer_request->ux_transfer_request_value; /* Configuration Number */
                        g_usb_host_usbx_request[module_number][2] = (uint16_t) 0x0000;
                        g_usb_host_usbx_request[module_number][3] = (uint16_t) 0x0000;

                        g_usb_host_usbx_req_msg[module_number].complete =
                            (usb_cb_t) &usb_host_usbx_set_configuration_cb;
                    }
                    else
                    {
                        /* Class Request */
                        g_usb_host_usbx_request[module_number][UX_FSP_SETUP_REQUEST_TYPE] =
                            (uint16_t) ((transfer_request->ux_transfer_request_function << 8) |
                                        (transfer_request->ux_transfer_request_type));
                        g_usb_host_usbx_request[module_number][1] =
                            (uint16_t) transfer_request->ux_transfer_request_value;
                        g_usb_host_usbx_request[module_number][2] =
                            (uint16_t) transfer_request->ux_transfer_request_index;
                        g_usb_host_usbx_request[module_number][3] =
                            (uint16_t) transfer_request->ux_transfer_request_requested_length;
                        g_usb_host_usbx_req_msg[module_number].complete = (usb_cb_t) &usb_host_usbx_class_request_cb;
                    }
  #endif                               /* #if defined(USB_CFG_HHID_USE) */

                    g_usb_host_usbx_request[module_number][4] = USB_DEVICEADDR;

                    g_usb_host_usbx_req_msg[module_number].keyword   = USB_PIPE0;
                    g_usb_host_usbx_req_msg[module_number].p_tranadr =
                        transfer_request->ux_transfer_request_data_pointer;
                    g_usb_host_usbx_req_msg[module_number].tranlen =
                        (uint32_t) transfer_request->ux_transfer_request_requested_length;
                    g_usb_host_usbx_req_msg[module_number].p_setup = g_usb_host_usbx_request[module_number];
                    g_usb_host_usbx_req_msg[module_number].status  = USB_DATA_NONE;
                    g_usb_host_usbx_req_msg[module_number].segment = USB_TRAN_END;
                    g_usb_host_usbx_req_msg[module_number].ip      = module_number;
                    g_usb_host_usbx_req_msg[module_number].ipp     = usb_hstd_get_usb_ip_adr(module_number);
                    g_p_usb_host_actural_length[module_number][0]  =
                        (uint32_t *) &(transfer_request->ux_transfer_request_actual_length);
                    g_usb_host_usbx_req_msg[module_number].read_req_len =
                        (uint32_t) transfer_request->ux_transfer_request_requested_length;

                    usb_hstd_transfer_start_req(&g_usb_host_usbx_req_msg[module_number]);

                    tx_semaphore_get(&g_usb_host_usbx_sem[module_number][USB_PIPE0], TX_WAIT_FOREVER);
                    break;
                }

                case (uint32_t) UX_FSP_BULK_ENDPOINT:
                case (uint32_t) UX_FSP_INTERRUPT_ENDPOINT:
                {
  #if defined(USB_CFG_HMSC_USE)
                    if (endpoint->ux_endpoint_descriptor.bEndpointAddress & USB_ENDPOINT_DIRECTION)
                    {
                        /* IN */
   #if (USB_CFG_DMA == USB_CFG_ENABLE)
                        is_in_transfer = USB_YES;
   #endif                              /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */

                        usb_hstd_set_pipe_info(module_number,
                                               g_usb_hmsc_in_pipe[module_number][0],
                                               &g_usb_hmsc_pipe_table[0][USB_PIPE_DIR_IN]);
                        usb_hstd_set_pipe_reg(&g_usb_host_usbx_req_msg[module_number],
                                              g_usb_hmsc_in_pipe[module_number][0]);

                        if (USB_SQMON == (USB_SQMON & g_usb_hmsc_in_pipectr[module_number][0]))
                        {
                            hw_usb_set_sqset(&g_usb_host_usbx_req_msg[module_number],
                                             g_usb_hmsc_in_pipe[module_number][0]);
                        }
                        else
                        {
                            hw_usb_set_sqclr(&g_usb_host_usbx_req_msg[module_number],
                                             g_usb_hmsc_in_pipe[module_number][0]);
                        }
                    }
                    else
                    {
                        /* OUT */
   #if (USB_CFG_DMA == USB_CFG_ENABLE)
                        is_in_transfer = USB_NO;
   #endif                              /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */

                        usb_hstd_set_pipe_info(module_number,
                                               g_usb_hmsc_out_pipe[module_number][0],
                                               &g_usb_hmsc_pipe_table[0][USB_PIPE_DIR_OUT]);
                        usb_hstd_set_pipe_reg(&g_usb_host_usbx_req_msg[module_number],
                                              g_usb_hmsc_out_pipe[module_number][0]);

                        if (USB_SQMON == (USB_SQMON & g_usb_hmsc_out_pipectr[module_number][0]))
                        {
                            hw_usb_set_sqset(&g_usb_host_usbx_req_msg[module_number],
                                             g_usb_hmsc_out_pipe[module_number][0]);
                        }
                        else
                        {
                            hw_usb_set_sqclr(&g_usb_host_usbx_req_msg[module_number],
                                             g_usb_hmsc_out_pipe[module_number][0]);
                        }
                    }
  #endif

                    size        = transfer_request->ux_transfer_request_requested_length;
                    ep_number   = endpoint->ux_endpoint_descriptor.bEndpointAddress & USB_EPNUMFIELD;
                    pipe_number = usb_host_usbx_endpoint_to_pipe(module_number, ep_number); /* Pipe Number */
                    g_usb_host_usbx_req_msg[module_number].read_req_len = size;             /* Request Data Size */
                    g_usb_host_usbx_req_msg[module_number].keyword      = pipe_number;      /* Pipe Number */
                    g_usb_host_usbx_req_msg[module_number].p_tranadr    =
                        transfer_request->ux_transfer_request_data_pointer;                 /* Data address */

  #if defined(USB_CFG_HMSC_USE)
   #if (USB_CFG_DMA == USB_CFG_ENABLE)
                    if (USB_YES == is_in_transfer)
                    {
                        // IN transfere
                        max_packet_size = (uint16_t) endpoint->ux_endpoint_descriptor.wMaxPacketSize;
                        if (0 != (size % max_packet_size))
                        {
                            allocation_size = ((size / max_packet_size) + 1) * max_packet_size;
                            g_p_usbx_hmsc_dma_buf[USB_DEVICEADDR - 1] =
                                _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY, allocation_size);

                            g_usb_host_usbx_req_msg[module_number].p_tranadr =
                                g_p_usbx_hmsc_dma_buf[USB_DEVICEADDR - 1];
                        }
                    }
   #endif                                                                   /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */
  #endif                                                                    /* #if defined(USB_CFG_HMSC_USE) */
                    g_usb_host_usbx_req_msg[module_number].tranlen  = size; /* Request Data Size */
                    g_usb_host_usbx_req_msg[module_number].complete = usb_host_usbx_transfer_complete_cb;

                    /* Callback function */
                    g_usb_host_usbx_req_msg[module_number].segment = USB_TRAN_END;
                    g_usb_host_usbx_req_msg[module_number].ip      = module_number;
                    g_usb_host_usbx_req_msg[module_number].ipp     = usb_hstd_get_usb_ip_adr(module_number);
  #if (USB_CFG_DMA == USB_CFG_ENABLE)
                    g_usb_host_usbx_req_msg[module_number].p_transfer_tx = g_p_usbx_transfer_tx;
                    g_usb_host_usbx_req_msg[module_number].p_transfer_rx = g_p_usbx_transfer_rx;
  #endif                               /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */
                    g_p_usb_host_actural_length[module_number][pipe_number] =
                        (uint32_t *) &(transfer_request->ux_transfer_request_actual_length);

                    g_p_usb_host_usbx_transfer_request[module_number][pipe_number] = transfer_request;
                    err = usb_hstd_transfer_start(&g_usb_host_usbx_req_msg[module_number]);

                    if (USB_OK == err)
                    {
                        status = (uint32_t) UX_SUCCESS;
                    }
                    else
                    {
                        status = (uint32_t) UX_TRANSFER_ERROR;
                    }

                    break;
                }

                case (uint32_t) UX_FSP_ISOCHRONOUS_ENDPOINT:
                default:
                {
                    break;
                }
            }

            break;
        }

        case (uint32_t) UX_HCD_TRANSFER_ABORT:
        {
            break;
        }

        case (uint32_t) UX_HCD_CREATE_ENDPOINT:
        {
            ((UX_ENDPOINT *) parameter)->ux_endpoint_ed = parameter;

            switch ((((UX_ENDPOINT *) parameter)->ux_endpoint_descriptor.bmAttributes) & UX_FSP_MASK_ENDPOINT_TYPE)
            {
                case (uint32_t) UX_FSP_CONTROL_ENDPOINT:
                {
                    ((UX_ENDPOINT *) parameter)->ux_endpoint_transfer_request.ux_transfer_request_maximum_length =
                        UX_FSP_MAX_CONTROL_PAYLOAD;
                    break;
                }

                case (uint32_t) UX_FSP_BULK_ENDPOINT:
                {
                    ((UX_ENDPOINT *) parameter)->ux_endpoint_transfer_request.ux_transfer_request_maximum_length =
                        UX_FSP_MAX_BULK_PAYLOAD;
                    break;
                }

                case (uint32_t) UX_FSP_INTERRUPT_ENDPOINT:
                {
                    ((UX_ENDPOINT *) parameter)->ux_endpoint_transfer_request.ux_transfer_request_maximum_length =
                        UX_FSP_MAX_INTERRUPT_PAYLOAD;
                    break;
                }

                case (uint32_t) UX_FSP_ISOCHRONOUS_ENDPOINT:
                {
                    ((UX_ENDPOINT *) parameter)->ux_endpoint_transfer_request.ux_transfer_request_maximum_length =
                        UX_FSP_MAX_ISO_PAYLOAD;
                    break;
                }

                default:
                {
                    break;
                }
            }

            status = (uint32_t) UX_SUCCESS;

            break;
        }

        case (uint32_t) UX_HCD_GET_PORT_STATUS:
        {
  #if defined(USB_CFG_OTG_USE)
            uint16_t  port_status = 0;
            uint16_t  reg_dvstctr;
            uint16_t  speed;
            usb_utr_t utr;

            if (USB_MODE_HOST == g_usb_usbmode[module_number])
            {
                utr.ip = module_number;

                reg_dvstctr = hw_usb_read_dvstctr(&utr);

                /* Isolate speed.  */
                speed = reg_dvstctr & (uint16_t) USB_RHST;
                if (USB_NULL != speed)
                {
                    /* Detect Port Device Attached speed.   */
                    switch (speed)
                    {
                        case USB_FSMODE:
                        {
                            port_status |= (ULONG) UX_PS_DS_FS;
                            break;
                        }

                        case USB_HSMODE:
                        {
                            port_status |= (ULONG) UX_PS_DS_HS;
                            break;
                        }

                        default:
                        {
                            port_status |= (ULONG) UX_PS_DS_LS;
                            break;
                        }
                    }

                    /*  Device connection detected .  */
                    port_status |= UX_PS_CCS;

   #if !defined(USB_CFG_OTG_USE)
                    / *Port Enabled. * /
                    hcd_synergy->ux_hcd_synergy_port_status = (ULONG) UX_SYNERGY_HC_PORT_ENABLED;
   #endif                              /* !defined(USB_CFG_OTG_USE) */

                    /* Port Enable Status.  */
                    if (reg_dvstctr & USB_UACT)
                    {
                        port_status |= UX_PS_PES;
                    }

                    port_status |= UX_PS_PPS;
                    status       = (uint32_t) port_status;
                }
                else
                {
                    status = 0;
                }
            }

  #else                                /* defined(USB_CFG_OTG_USE) */
            status = 0;
  #endif                               /* defined(USB_CFG_OTG_USE) */
            break;
        }

        default:
        {
            /* Error trap. */
            _ux_system_error_handler((uint32_t) UX_SYSTEM_LEVEL_THREAD,
                                     (uint32_t) UX_SYSTEM_CONTEXT_HCD,
                                     (uint32_t) UX_FUNCTION_NOT_SUPPORTED);

            /* Unknown request, return an error.  */
            status = (uint32_t) UX_FUNCTION_NOT_SUPPORTED;
            break;
        }
    }

    /* Return completion status.  */
    return status;
}                                      /* End of function usb_host_usbx_to_basic() */

 #endif                                /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

 #if defined(USB_CFG_OTG_USE)

/******************************************************************************
 * Function Name   : usb_otg_hnp_swap
 * Description     : OTG swap start processing for USB IP0
 * Argument        : LONG type : UX_OTG_HOST_TO_SLAVE
 * Return          : UX_SUCCESS
 ******************************************************************************/
static UINT usb_otg_hnp_swap (ULONG type)
{
    FSP_PARAMETER_NOT_USED(type);
    usb_utr_t utr;

    g_usb_otg_hnp_process[0] = USB_ON;

    utr.ip = USB_IP0;
    usb_hstd_hcd_snd_mbx(&utr, USB_MSG_HCD_OTG_SUSPEND, 0, (uint16_t *) 0, 0);

    return UX_SUCCESS;
}

  #if USB_NUM_USBIP == 2

/******************************************************************************
 * Function Name   : usb_otg_hnp_swap
 * Description     : OTG swap start processing for USB IP0
 * Argument        : LONG type : UX_OTG_HOST_TO_SLAVE
 * Return          : UX_SUCCESS
 ******************************************************************************/
static UINT usb2_otg_hnp_swap (ULONG type)
{
    FSP_PARAMETER_NOT_USED(type);
    usb_utr_t utr;

    g_usb_otg_hnp_process[1] = USB_ON;

    utr.ip = USB_IP1;
    usb_hstd_hcd_snd_mbx(&utr, USB_MSG_HCD_OTG_SUSPEND, 0, (uint16_t *) 0, 0);

    return UX_SUCCESS;
}

  #endif                               /* USB_NUM_USBIP == 2 */
 #endif
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
