/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "rm_zmod4xxx.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_delay_ms(rm_zmod4xxx_ctrl_t * const p_ctrl, uint32_t const delay_ms);
fsp_err_t rm_zmod4xxx_irq_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t rm_zmod4xxx_irq_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
void      rm_zmod4xxx_irq_callback(external_irq_callback_args_t * p_args);

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Delay some milliseconds.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_delay_ms (rm_zmod4xxx_ctrl_t * const p_ctrl, uint32_t const delay_ms)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Software delay */
    R_BSP_SoftwareDelay(delay_ms, BSP_DELAY_UNITS_MILLISECONDS);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Open IRQ driver and set callback function.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_irq_open (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl         = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    external_irq_instance_t     * p_irq_instance = (external_irq_instance_t *) p_ctrl->p_irq_instance;

    /* Open IRQ driver */
    err = p_irq_instance->p_api->open(p_irq_instance->p_ctrl,
                                      p_irq_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set callback */
    err = p_irq_instance->p_api->callbackSet(p_irq_instance->p_ctrl,
                                             rm_zmod4xxx_irq_callback,
                                             p_ctrl,
                                             NULL);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Enable callback */
    err = p_irq_instance->p_api->enable(p_irq_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Close IRQ driver.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_irq_close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    rm_zmod4xxx_instance_ctrl_t * p_ctrl         = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    external_irq_instance_t     * p_irq_instance = (external_irq_instance_t *) p_ctrl->p_irq_instance;

    /* Close IRQ driver */
    p_irq_instance->p_api->close(p_irq_instance->p_ctrl);

    return FSP_SUCCESS;
}

void rm_zmod4xxx_irq_callback (external_irq_callback_args_t * p_args)
{
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_args->p_context;
    rm_zmod4xxx_callback_args_t   zmod4xxx_callback_args;

    if (0 == p_ctrl->open)
    {
        /* Set IRQ flag */
        p_ctrl->init_process_params.measurement_finished = true;
    }
    else
    {
        /* Set context */
        zmod4xxx_callback_args.p_context = p_ctrl->p_context;

        /* Set event */
        zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
        p_ctrl->event                = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;

        if (NULL != p_ctrl->p_irq_callback)
        {
            /* Call callback function */
            p_ctrl->p_irq_callback(&zmod4xxx_callback_args);
        }
    }
}
