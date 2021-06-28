/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
fsp_err_t rm_zmod4xxx_timer_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t rm_zmod4xxx_timer_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t rm_zmod4xxx_timer_start(rm_zmod4xxx_ctrl_t * const p_api_ctrl, uint32_t const delay_ms);
fsp_err_t rm_zmod4xxx_timer_stop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t rm_zmod4xxx_irq_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t rm_zmod4xxx_irq_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Open timer driver and set callback function.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_timer_open (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl           = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    timer_instance_t            * p_timer_instance = (timer_instance_t *) p_ctrl->p_timer_instance;

    /* Open timer driver */
    err = p_timer_instance->p_api->open(p_timer_instance->p_ctrl,
                                        p_timer_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set callback */
    err = p_timer_instance->p_api->callbackSet(p_timer_instance->p_ctrl,
                                               rm_zmod4xxx_timer_callback,
                                               p_ctrl,
                                               NULL);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Close timer driver.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_timer_close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    rm_zmod4xxx_instance_ctrl_t * p_ctrl           = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    timer_instance_t            * p_timer_instance = (timer_instance_t *) p_ctrl->p_timer_instance;

    /* Close timer driver */
    p_timer_instance->p_api->close(p_timer_instance->p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Start timer count.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_timer_start (rm_zmod4xxx_ctrl_t * const p_api_ctrl, uint32_t const delay_ms)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl           = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    timer_instance_t            * p_timer_instance = (timer_instance_t *) p_ctrl->p_timer_instance;

    /* Set delay times */
    p_ctrl->init_process_params.delay_ms = delay_ms;

    /* Reset timer driver */
    err = p_timer_instance->p_api->reset(p_timer_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Start timer driver */
    err = p_timer_instance->p_api->start(p_timer_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop timer count.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
fsp_err_t rm_zmod4xxx_timer_stop (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl           = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    timer_instance_t            * p_timer_instance = (timer_instance_t *) p_ctrl->p_timer_instance;

    /* Stop timer driver */
    err = p_timer_instance->p_api->stop(p_timer_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

void rm_zmod4xxx_timer_callback (timer_callback_args_t * p_args)
{
    rm_zmod4xxx_instance_ctrl_t * p_ctrl           = (rm_zmod4xxx_instance_ctrl_t *) p_args->p_context;
    timer_instance_t            * p_timer_instance = (timer_instance_t *) p_ctrl->p_timer_instance;

    if (0 < p_ctrl->init_process_params.delay_ms)
    {
        /* Decrement */
        p_ctrl->init_process_params.delay_ms--;
    }
    else
    {
        /* Stop timer driver */
        p_timer_instance->p_api->stop(p_timer_instance->p_ctrl);
    }
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
