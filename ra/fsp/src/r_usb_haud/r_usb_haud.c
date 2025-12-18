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

#include "r_usb_haud_api.h"
#include "r_usb_haud.h"
#include "r_usb_haud_driver.h"

/*******************************************************************************************************************//**
 * @addtogroup USB_HAUD USB_HAUD
 * @{
 **********************************************************************************************************************/

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
extern volatile uint32_t g_usb_open_class[];

/*************************************************************************//**
 * @brief Check audio version of connected device.
 *
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HAUD_DeviceInfoGet (usb_ctrl_t * const       p_api_ctrl,
                                    usb_haud_device_info_t * p_info,
                                    uint8_t                  device_address)
{
    usb_info_t info;
    fsp_err_t  err = FSP_ERR_USB_FAILED;

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
        if (NULL != g_p_usb_haud_interface_table[p_ctrl->module_number])
        {
            /* Device Protocol Version */
            p_info->protocol = g_p_usb_haud_interface_table[p_ctrl->module_number][7]; /* bInterfaceProtocol */
            err              = FSP_SUCCESS;
        }
    }

    return err;
}

/******************************************************************************
 * End of R_USB_HAUD_DeviceInfoGet
 ******************************************************************************/

/*************************************************************************//**
 * @brief Get the Clock Souuce
 *        (Audio 2.0 support only)
 *
 *        Restriction:
 *          This API does not support fallback handling if a Clock Source
 *          descriptor is not found.
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HAUD_ClockSourceGet (usb_ctrl_t * const    p_api_ctrl,
                                     usb_haud_sampling_t * p_info,
                                     uint8_t               direction,
                                     uint8_t               device_address)
{
    usb_info_t info;
    fsp_err_t  err = FSP_ERR_USB_FAILED;
    usb_utr_t  utr;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    uint8_t * descriptor;
    uint32_t  total_descriptor_length;
    uint32_t  descriptor_length;
    uint32_t  descriptor_type;
    uint32_t  interface_found       = USB_FALSE;
    uint32_t  ep_direction_checking = USB_FALSE;
    uint8_t * p_csd;
    uint8_t * header = NULL;

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
        utr.ip  = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr((uint16_t) p_ctrl->module_number);

        if (NULL != g_p_usb_haud_config_table[p_ctrl->module_number])
        {
            descriptor = g_p_usb_haud_config_table[p_ctrl->module_number];

            total_descriptor_length = *(descriptor + 2);

            while (total_descriptor_length)
            {
                descriptor_length = *descriptor;
                descriptor_type   = *(descriptor + 1);

                switch (descriptor_type)
                {
                    case USB_DT_INTERFACE:
                    {
                        if ((USB_IFCLS_AUD == descriptor[5]) &&             /* bInterfaceClass */
                            (USB_HAUD_SUBCLASS_STREAMING == descriptor[6])) /* bInterfaceSubClass */
                        {
                            p_info->interface_number = descriptor[2];       /* bInterfaceNumber */
                            p_info->alternate_number = descriptor[3];       /* bAlternateSetting */

                            interface_found = USB_TRUE;
                        }
                        else
                        {
                            interface_found = USB_FALSE;
                        }

                        break;
                    }

                    case USB_HAUD_CS_INTERFACE:
                    {
                        if (USB_TRUE == interface_found)
                        {
                            if (USB_HAUD_AUDIO20_AS_GENERAL == descriptor[2])               /* bDescriptorSubType */
                            {
                                /* Save for future use */
                                header                 = descriptor;
                                p_info->found_channels = header[10];                        /* bNrChannels */
                                break;
                            }

                            if ((USB_HAUD_AUDIO20_AS_FORMAT_TYPE == descriptor[2]) &&       /* bDescriptorSubType */
                                (USB_HAUD_AUDIO20_FORMAT_TYPE_I == descriptor[3]))          /* bFormatType */
                            {
                                if (NULL != header)
                                {
                                    p_info->found_resolution = descriptor[5];               /* bBitResolution */

                                    usb_haud_audio20_clock_source_descriptor_get(&utr,
                                                                                 header[3], /* bTerminalLink */
                                                                                 direction,
                                                                                 &p_csd);

                                    if (NULL != p_csd)
                                    {
                                        p_info->p_clock_source    = p_csd;
                                        p_info->clock_source_id   = p_csd[3]; /* bClockID */
                                        p_info->clock_numerator   = 1;
                                        p_info->clock_denominator = 1;
                                        ep_direction_checking     = USB_TRUE;
                                    }
                                }
                            }
                        }

                        break;
                    }

                    case USB_DT_ENDPOINT:
                    {
                        if (ep_direction_checking)
                        {
                            if (direction != (descriptor[2] & USB_EP_DIR)) /* bEndpointAddress */
                            {
                                ep_direction_checking         = USB_FALSE;
                                p_info->p_sampling_descriptor = NULL;
                            }
                            else
                            {
                                p_info->endpoint_address = descriptor[2]; /* bEndpointAddress */
                                p_info->max_packet_size  =
                                    (uint16_t) ((uint16_t) descriptor[4] + (((uint16_t) descriptor[5]) << 8));

                                return FSP_SUCCESS;
                            }
                        }

                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

                if (descriptor_length > total_descriptor_length)
                {
                    return FSP_ERR_USB_FAILED;
                }

                descriptor              += descriptor_length;
                total_descriptor_length -= descriptor_length;
            }

            return FSP_ERR_USB_FAILED;
        }
    }

    return err;
}

/******************************************************************************
 * End of R_USB_HAUD_ClockSourceGet
 ******************************************************************************/

/*************************************************************************//**
 * @brief Get the alternate number for SET_INTERFACE.
 *        (Audio 1.0 support only)
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HAUD_AlternateNumberGet (usb_ctrl_t * const    p_api_ctrl,
                                         usb_haud_sampling_t * p_info,
                                         uint8_t               direction,
                                         uint8_t               device_address)
{
    usb_info_t info;
    fsp_err_t  err = FSP_ERR_USB_FAILED;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    uint8_t * descriptor;
    uint32_t  total_descriptor_length;
    uint32_t  descriptor_length;
    uint32_t  descriptor_type;
    uint32_t  descriptor_subtype;
    uint32_t  interface_found = USB_FALSE;
    uint32_t  lower_frequency;
    uint32_t  higher_frequency;
    uint32_t  specific_frequency_count;
    uint32_t  ep_direction_checking = USB_FALSE;

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
        if (NULL != g_p_usb_haud_config_table[p_ctrl->module_number])
        {
            descriptor = g_p_usb_haud_config_table[p_ctrl->module_number];

            total_descriptor_length = *(descriptor + 2);

            while (total_descriptor_length)
            {
                descriptor_length  = *descriptor;
                descriptor_type    = *(descriptor + 1);
                descriptor_subtype = *(descriptor + 2);

                switch (descriptor_type)
                {
                    case USB_DT_INTERFACE:
                    {
                        if ((USB_IFCLS_AUD == descriptor[5]) &&             /* bInterfaceClass */
                            (USB_HAUD_SUBCLASS_STREAMING == descriptor[6])) /* bInterfaceSubClass */
                        {
                            p_info->interface_number = descriptor[2];       /* bInterfaceNumber */
                            p_info->alternate_number = descriptor[3];       /* bAlternateSetting */

                            interface_found = USB_TRUE;
                        }
                        else
                        {
                            interface_found = USB_FALSE;
                        }

                        break;
                    }

                    case USB_HAUD_CS_INTERFACE:
                    {
                        if ((USB_TRUE == interface_found) && (USB_HAUD_AUDIO10_CS_FORMAT_TYPE == descriptor_subtype))
                        {
                            if (USB_HAUD_AUDIO10_FORMAT_TYPE_I != descriptor[3]) /* bFormatType */
                            {
                                break;
                            }

                            if (p_info->channels != descriptor[4]) /* bNrChannels */
                            {
                                break;
                            }

                            if (p_info->resolution != descriptor[6]) /* bBitResolution */
                            {
                                break;
                            }

                            if (0 == descriptor[7]) /* bSamFreqType */
                            {
                                /* The declaration of frequency is contiguous, so get the minimum and maximum */
                                lower_frequency =
                                    (uint32_t) *(descriptor + USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH) |
                                    ((uint32_t) *(descriptor +
                                                  USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH + 1)) << 8 |
                                    ((uint32_t) *(descriptor +
                                                  USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH + 2)) << 16;

                                higher_frequency =
                                    (uint32_t) *(descriptor + USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH + 3) |
                                    ((uint32_t) *(descriptor +
                                                  USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH + 4)) << 8 |
                                    ((uint32_t) *(descriptor +
                                                  USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH + 5)) << 16;

                                if ((p_info->frequency >= lower_frequency) &&
                                    (p_info->frequency <= higher_frequency))
                                {
                                    /* Found the right alternate setting */
                                    p_info->p_sampling_descriptor = descriptor;
                                    ep_direction_checking         = USB_TRUE;
                                }
                            }
                            else
                            {
                                /* The declaration of the frequency is declared as an array of specific values */
                                for (specific_frequency_count = 0; specific_frequency_count < descriptor[7]; /* descriptor[7] : bSamFreqType */
                                     specific_frequency_count++)
                                {
                                    lower_frequency =
                                        (uint32_t) *(descriptor + USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH +
                                                     (specific_frequency_count * 3)) |
                                        ((uint32_t) *(descriptor +
                                                      USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH + 1 +
                                                      (specific_frequency_count * 3))) << 8 |
                                        ((uint32_t) *(descriptor +
                                                      USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH + 2 +
                                                      (specific_frequency_count * 3))) << 16;

                                    if (p_info->frequency == lower_frequency)
                                    {
                                        /* Found the right alternate setting */
                                        p_info->p_sampling_descriptor = descriptor;
                                        ep_direction_checking         = USB_TRUE;
                                    }
                                }
                            }
                        }

                        break;
                    }

                    case USB_DT_ENDPOINT:
                    {
                        if (ep_direction_checking)
                        {
                            if (direction != (descriptor[2] & USB_EP_DIR)) /* bEndpointAddress */
                            {
                                ep_direction_checking         = USB_FALSE;
                                p_info->p_sampling_descriptor = NULL;
                            }
                            else
                            {
                                p_info->endpoint_address = descriptor[2]; /* bEndpointAddress */
                                p_info->max_packet_size  =
                                    (uint16_t) ((uint16_t) descriptor[4] + (((uint16_t) descriptor[5]) << 8));

                                return FSP_SUCCESS;
                            }
                        }

                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

                if (descriptor_length > total_descriptor_length)
                {
                    return FSP_ERR_USB_FAILED;
                }

                descriptor              += descriptor_length;
                total_descriptor_length -= descriptor_length;
            }

            return FSP_ERR_USB_FAILED;
        }
    }

    return err;
}

/******************************************************************************
 * End of R_USB_HAUD_AlternateNumberGet
 ******************************************************************************/

/*************************************************************************//**
 * @brief Find the interface descriptor for streaming data transfer
 *        and configure the pipe.
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HAUD_PipeSet (usb_ctrl_t * const p_api_ctrl,
                              uint32_t           interface_number,
                              uint32_t           alternate_number,
                              uint8_t            device_address)
{
    usb_info_t info;
    fsp_err_t  err = FSP_ERR_USB_FAILED;
    usb_utr_t  utr;

    uint16_t             is_interface_discovered = 0;
    uint16_t             usb_class               = USB_CLASS_INTERNAL_HAUD;
    uint16_t             length = 0;
    uint16_t             offset = 0;
    uint8_t            * p_config;
    uint8_t              pipe_no;
    usb_pipe_table_reg_t ep_tbl;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

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
        utr.ip            = p_ctrl->module_number;
        utr.ipp           = usb_hstd_get_usb_ip_adr((uint16_t) p_ctrl->module_number);
        utr.p_transfer_rx = p_ctrl->p_transfer_rx;
        utr.p_transfer_tx = p_ctrl->p_transfer_tx;

        if (NULL != g_p_usb_haud_config_table[p_ctrl->module_number])
        {
            p_config = g_p_usb_haud_config_table[p_ctrl->module_number];
            length   = (uint16_t) (*(p_config + 3) << 8);
            length   = (uint16_t) (length + *(p_config + 2));
            offset   = 0;

            while (offset < length)
            {
                if (USB_DT_INTERFACE == *(p_config + offset + 1))
                {
                    if (interface_number == *(p_config + offset + 2))
                    {
                        if ((alternate_number == *(p_config + offset + 3)) &&
                            (USB_HAUD_SUBCLASS_STREAMING == *(p_config + offset + 6)))
                        {
                            is_interface_discovered = 1;
                        }
                    }
                }

                if (1 == is_interface_discovered)
                {
                    if (USB_DT_ENDPOINT == *(p_config + offset + USB_EP_B_DESCRIPTORTYPE))
                    {
                        pipe_no =
                            usb_hstd_make_pipe_reg_info(utr.ip, device_address, usb_class,
                                                        g_usb_hstd_device_speed[utr.ip], (p_config + offset), &ep_tbl);
                        if (USB_NULL != pipe_no)
                        {
                            usb_hstd_set_pipe_info(utr.ip, pipe_no, &ep_tbl);
                        }

                        usb_hstd_set_pipe_reg(&utr, pipe_no);
                        err = FSP_SUCCESS;
                        break;
                    }
                }

                offset = (uint16_t) (offset + (*(p_config + offset)));
            }
        }
    }

    return err;
}

/******************************************************************************
 * End of R_USB_HAUD_PipeSet
 ******************************************************************************/

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HAUD)
 **********************************************************************************************************************/
