/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic.h"
#include "../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../r_usb_basic/src/hw/inc/r_usb_reg_access.h"

#include "r_usb_hcdc_api.h"
#include "r_usb_hcdc.h"
#include "r_usb_hcdc_driver.h"

/*******************************************************************************************************************//**
 * @addtogroup USB_HCDC USB_HCDC
 * @{
 **********************************************************************************************************************/

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define USB_VALUE_7FH    (0x7F)
#define USB_VALUE_00H    (0x00)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
extern volatile uint32_t g_usb_open_class[];
extern uint16_t          g_usb_hcdc_vendor_table[];

/*************************************************************************//**
 * @brief Read Control Data.(CDC Interrupt IN data)
 *
 *
 * @retval FSP_SUCCESS           Successfully completed (Data read request completed).
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY      Data receive request already in process for
 *                               USB device with same device address.
 * @retval FSP_ERR_ASSERTION     Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note 1. Do not call this API in the following function.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HCDC_ControlDataRead (usb_ctrl_t * const p_api_ctrl,
                                      uint8_t          * p_buf,
                                      uint32_t           size,
                                      uint8_t            device_address)
{
    usb_info_t info;
    usb_er_t   err;
    fsp_err_t  result = FSP_ERR_USB_FAILED;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    FSP_ERROR_RETURN(0 != device_address, FSP_ERR_USB_PARAMETER);
    FSP_ERROR_RETURN(USB_ADDRESS5 >= device_address, FSP_ERR_USB_PARAMETER)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->device_address = device_address;
    p_ctrl->type           = (usb_class_t) (USB_CLASS_HCDCC & USB_VALUE_7FH);

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(!(((USB_NULL == p_buf)) || (USB_NULL == size)))

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] &
                                  (1 << p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
#endif  /* USB_CFG_PARAM_CHECKING_ENABLE */

    (void) R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        err = usb_data_read(p_ctrl, p_buf, size);

        if (USB_OK == err)
        {
            result = FSP_SUCCESS;
        }
        else if (USB_QOVR == err)
        {
            result = FSP_ERR_USB_BUSY;
        }
        else
        {
            /* Noting */
        }
    }

    return result;
}

/******************************************************************************
 * End of function R_USB_HCDC_ControlDataRead
 ******************************************************************************/

/*************************************************************************//**
 * @brief Register the specified vendor class device in the device table.
 *
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HCDC_SpecificDeviceRegister (usb_ctrl_t * const p_api_ctrl, uint16_t vendor_id, uint16_t product_id)
{
    fsp_err_t err = FSP_ERR_USB_FAILED;
    uint32_t  i;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    FSP_PARAMETER_NOT_USED(*p_ctrl);

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)
    FSP_ASSERT((0x0000 != vendor_id) && (0x0000 != product_id))

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] &
                                  (1 << p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
#endif                                      /* USB_CFG_PARAM_CHECKING_ENABLE */

    i = (uint32_t) g_usb_hcdc_vendor_table[0];

    if (i < USB_HCDC_SPECIFIC_DEV_MAX)
    {
        g_usb_hcdc_vendor_table[(i * 2) + 2] = vendor_id;
        g_usb_hcdc_vendor_table[(i * 2) + 3] = product_id;

        g_usb_hcdc_vendor_table[0]++;

        err = FSP_SUCCESS;
    }

    return err;
}

/******************************************************************************
 * End of R_USB_HCDC_SpecificDeviceRegister
 ******************************************************************************/

/*************************************************************************//**
 * @brief Get the VID, PID and subclass code of the connected device.
 *
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HCDC_DeviceInfoGet (usb_ctrl_t * const       p_api_ctrl,
                                    usb_hcdc_device_info_t * p_info,
                                    uint8_t                  device_address)
{
    usb_info_t info;
    fsp_err_t  err        = FSP_ERR_USB_FAILED;
    uint8_t  * descriptor = NULL;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)
    FSP_ASSERT(USB_NULL != p_info)

    FSP_ERROR_RETURN(0 != device_address, FSP_ERR_USB_PARAMETER);
    FSP_ERROR_RETURN(USB_ADDRESS5 >= device_address, FSP_ERR_USB_PARAMETER)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->device_address = device_address;

#if USB_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] &
                                  (1 << p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
#endif                                      /* USB_CFG_PARAM_CHECKING_ENABLE */

    (void) R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        descriptor = (uint8_t *) &g_usb_hstd_device_descriptor[p_ctrl->module_number];

        p_info->vendor_id = (uint16_t) (descriptor[USB_DEV_ID_VENDOR_L] +
                                        ((uint16_t) descriptor[USB_DEV_ID_VENDOR_H] << 8));
        p_info->product_id = (uint16_t) (descriptor[USB_DEV_ID_PRODUCT_L] +
                                         ((uint16_t) descriptor[USB_DEV_ID_PRODUCT_H] << 8));

        if (NULL != g_p_usb_hcdc_interface_table[p_ctrl->module_number])
        {
            p_info->subclass = g_p_usb_hcdc_interface_table[p_ctrl->module_number][6];
        }
        else
        {
            p_info->subclass = USB_VALUE_00H; /* Reserved */
        }

        err = FSP_SUCCESS;
    }

    return err;
}

/******************************************************************************
 * End of R_USB_HCDC_DeviceInfoGet
 ******************************************************************************/

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HCDC)
 **********************************************************************************************************************/
