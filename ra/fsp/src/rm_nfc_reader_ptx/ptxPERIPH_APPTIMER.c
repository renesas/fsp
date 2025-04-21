/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "ptxPERIPH_APPTIMER.h"

#define PTX_PLAT_APP_TIMER_DIVIDER    (1000U)

static timer_instance_t * timer;

/*
 * ####################################################################################################################
 * INTERNAL FUNCTIONS / HELPERS
 * ####################################################################################################################
 */
void ptxPERIPH_APPTIMER_IsrCallback(timer_callback_args_t * p_args);

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */
ptxStatus_t ptxPERIPH_APPTIMER_Open (timer_instance_t * timer_instance)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer_instance)
    {
        timer = timer_instance;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPERIPH_APPTIMER_Start (uint32_t ms)
{
    ptxStatus_t status = ptxStatus_Success;

    fsp_err_t r_status = timer->p_api->open(timer->p_ctrl, timer->p_cfg);

    if (FSP_SUCCESS == r_status)
    {
        r_status = timer->p_api->callbackSet(timer->p_ctrl, ptxPERIPH_APPTIMER_IsrCallback, NULL, NULL);
    }

    if (FSP_SUCCESS == r_status)
    {
        uint32_t timer_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD) >> timer->p_cfg->source_div;
        uint32_t period_counts = (uint32_t) (((uint64_t) timer_freq_hz * ms) / PTX_PLAT_APP_TIMER_DIVIDER);
        r_status = timer->p_api->periodSet(timer->p_ctrl, period_counts);

        if (FSP_SUCCESS == r_status)
        {
            r_status = timer->p_api->start(timer->p_ctrl);
        }
    }

    if (FSP_SUCCESS != r_status)
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
    }

    return status;
}

ptxStatus_t ptxPERIPH_APPTIMER_Status (TimerStatus_t * timerStatus)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timerStatus)
    {
        timer_status_t timer_status;

        fsp_err_t r_status = timer->p_api->statusGet(timer->p_ctrl, &timer_status);
        if (FSP_SUCCESS == r_status)
        {
            if (timer_status.state == TIMER_STATE_STOPPED)
            {
                timerStatus->IsElapsed   = 1U;
                timerStatus->ElapsedTime = 0U;
            }
            else
            {
                timerStatus->IsElapsed = 0U;
                uint32_t timer_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD) >> timer->p_cfg->source_div;
                timerStatus->ElapsedTime =
                    (uint32_t) (((uint64_t) timer_status.counter * PTX_PLAT_APP_TIMER_DIVIDER) / timer_freq_hz);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPERIPH_APPTIMER_Stop ()
{
    ptxStatus_t status = ptxStatus_Success;

    fsp_err_t r_status = timer->p_api->stop(timer->p_ctrl);
    if (FSP_SUCCESS == r_status)
    {
        r_status = timer->p_api->close(timer->p_ctrl);
    }

    if (FSP_SUCCESS != r_status)
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
    }

    return status;
}

void ptxPERIPH_APPTIMER_IsrCallback (timer_callback_args_t * p_args)
{
    timer->p_api->stop(timer->p_ctrl);
    (void) p_args;
}
