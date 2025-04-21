/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */

#include "ptxPLAT_TIMER.h"
#include <string.h>

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

#define PTX_PLAT_TIMER_DIVIDER    (1000)

extern void ptxPLAT_TIMER_IsrCallback(timer_callback_args_t * p_args);

/**
 * Timer Context.
 */
ptxPlatTimer_t timer_ctx;

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */

ptxStatus_t ptxPLAT_TIMER_Open (timer_instance_t * timer_instance)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer_instance)
    {
        /**
         * Initialization of the TIMER Context
         */
        memset(&timer_ctx, 0, sizeof(ptxPlatTimer_t));

        timer_ctx.TimerInstance = timer_instance;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TIMER_GetInitializedTimer (ptxPlatTimer_t ** timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer)
    {
        timer_instance_t * timer_instance = timer_ctx.TimerInstance;

        fsp_err_t r_status = timer_instance->p_api->open(timer_instance->p_ctrl, timer_instance->p_cfg);

        if (FSP_SUCCESS == r_status)
        {
            *timer = &timer_ctx;
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TIMER_Start (ptxPlatTimer_t         * timer,
                                 uint32_t                 ms,
                                 uint8_t                  isBlock,
                                 pptxPlat_TimerCallBack_t fnISRCb,
                                 void                   * ISRCxt)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != timer) && (ms > 0) && ((0 == isBlock) || (1U == isBlock)))
    {
        /** Clear IsElpased state */
        timer->IsElapsed = 0;

        /** Stop Timer, first. Then, set period. Finally, start timer counter. */
        timer_instance_t * timer_instance = (timer_instance_t *) timer->TimerInstance;
        fsp_err_t          r_status       = timer_instance->p_api->stop(timer_instance->p_ctrl);

        if (FSP_SUCCESS == r_status)
        {
            uint32_t timer_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD) >> timer_instance->p_cfg->source_div;
            uint32_t period_counts = (uint32_t) (((uint64_t) timer_freq_hz * ms) / PTX_PLAT_TIMER_DIVIDER);
            r_status = timer_instance->p_api->periodSet(timer_instance->p_ctrl, period_counts);
        }

        if (FSP_SUCCESS == r_status)
        {
            timer->ISRCallBack = fnISRCb;
            timer->ISRCxt      = ISRCxt;

            r_status = timer_instance->p_api->start(timer_instance->p_ctrl);

            if (FSP_SUCCESS == r_status)
            {
                timer->TimerState = Timer_InUse;
                if (1U == isBlock)
                {
                    /**
                     * WFI until Timer is elapsed. Suitable for Pause() functionality.
                     *
                     * Note: Usage of DSB and ISB here should ensure that MCU-internal memory and instruction operations should
                     *       be completed before and after WFI() to ensure checking the "IsElapsed"-flag is done "in order".
                     *       If the timer-ISR is called exactly between checking the flag and the WFI-instruction, the system might
                     *       stay in sleep-state. This case is prevented here, by letting the timer periodically trigger (kind of watchdog, to be ),
                     *       stopped at the calling level), but it is advised on certain system / MCUs to use - for example - a critical section
                     *       before the check and after exiting the WFI-state.
                     */
                    while (0 == timer->IsElapsed)
                    {
                        __DSB();
                        __WFI();
                        __ISB();
                        __NOP();
                    }
                }
            }
        }

        if (FSP_SUCCESS != r_status)
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

ptxStatus_t ptxPLAT_TIMER_IsElapsed (ptxPlatTimer_t * timer, uint8_t * isElapsed)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != timer) && (NULL != isElapsed))
    {
        *isElapsed = timer->IsElapsed;

        if (0 != *isElapsed)
        {
            ptxPLAT_TIMER_Stop(timer);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TIMER_Stop (ptxPlatTimer_t * timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer)
    {
        timer_instance_t * timer_instance = (timer_instance_t *) timer->TimerInstance;
        fsp_err_t          r_status       = timer_instance->p_api->stop(timer_instance->p_ctrl);
        if (FSP_SUCCESS == r_status)
        {
            timer->IsElapsed  = 0;
            timer->TimerState = Timer_Free;
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

ptxStatus_t ptxPLAT_TIMER_Deinit (ptxPlatTimer_t * timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer)
    {
        /** Timer driver API close stops the timer, disables interrupts and performs other cleanup. */
        timer_instance_t * timer_instance = (timer_instance_t *) timer->TimerInstance;
        fsp_err_t          r_status       = timer_instance->p_api->close(timer_instance->p_ctrl);
        if (FSP_SUCCESS == r_status)
        {
            memset(&timer_ctx, 0, sizeof(ptxPlatTimer_t));
            timer_ctx.TimerInstance = timer_instance;
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

/*
 * ####################################################################################################################
 * INTERNAL FUNCTIONS
 * ####################################################################################################################
 */
void ptxPLAT_TIMER_IsrCallback (timer_callback_args_t * p_args)
{
    /**
     * PERIODIC_MODE is used for timer operation:
     *      -interrupt flags are cleared in ISR routine
     *      -timer counter is not automatically stopped (unless a Callback-routine is used), as this periodic mechanism is
     *       is used to prevent a potential race condition between checking the "IsElapsed"-flag and the WFI-instruction in "ptxPLAT_TIMER_Start".
     *
     * It is assumed p_args has been properly set and is not NULL.
     * It is assumed that p_context is timer instance used. Should this be checked, use g_timer0.p_ctrl.
     * So, far only one timer and one channel is used.
     */
    timer_ctx.IsElapsed = 1U;

    /*Let's call back if defined. */
    if (NULL != timer_ctx.ISRCallBack)
    {
        timer_instance_t * timer_instance = (timer_instance_t *) timer_ctx.TimerInstance;
        timer_instance->p_api->stop(timer_instance->p_ctrl);

        if (NULL != timer_ctx.ISRCxt)
        {
            timer_ctx.ISRCallBack(timer_ctx.ISRCxt);
        }
    }

    (void) p_args;
}
