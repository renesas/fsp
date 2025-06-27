/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef COMPS_PLAT_PTXPLAT_TIMER_H_
 #define COMPS_PLAT_PTXPLAT_TIMER_H_

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */
 #include "ptxStatus.h"
 #include "ptxPLAT.h"
 #include "r_timer_api.h"
 #include <stddef.h>

 #ifdef __cplusplus
extern "C" {
 #endif

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

/**
 * Timer state.
 */
typedef enum ptxPlatTimerState
{
    Timer_NotInitialized = 0,          /*< Initial state after allocation. */
    Timer_Free,                        /*< Available to be used. */
    Timer_InUse,                       /*< Timer already used. */
} ptxPlatTimerState_t;

/**
 * Platform-specific. TIMER Main structure.
 */
typedef struct ptxPlatTimer
{
    void                   * TimerInstance; /*< Timer driver API instance. */
    ptxPlatTimerState_t      TimerState;    /*< Timer State. */
    volatile uint8_t         IsElapsed;     /*< Timer Elapsed variable. */
    pptxPlat_TimerCallBack_t ISRCallBack;   /*< Callback used by timer for asynchronous notification to upper layers. */
    void                   * ISRCxt;        /*< Context used by callback. */
} ptxPlatTimer_t;

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */
ptxStatus_t ptxPLAT_TIMER_Open(timer_instance_t * timer_instance);

/**
 * \brief Get an initialized timer.
 *
 * \note This function is in charge of provide an available (e.g.not in use) Timer, and initialize it.
 *
 * \note This function shall be successfully executed before any other call to the functions in this module.
 *
 * \param[out]       timer             Pointer to pointer where the allocated and initialized timer context is going to be provided.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_TIMER_GetInitializedTimer(ptxPlatTimer_t ** timer);

/**
 * \brief Start timer for some milliseconds.
 *
 * \note This function shall be able to be used on two different ways:
 *
 *        1./ It blocks and waits until the time elapses.
 *        2./ It does not block, It register a callback that will be called asyncrhously when the time elapses.
 *
 * \param[in]       timer             Pointer to an initialized timer context.
 * \param[in]       ms                Milliseconds to wait.
 * \param[in]       isBlock           Set to 0 if the function is not blocking. Set to 1 if it blocks.
 * \param[in]       fnISRCb           Callback function that may be used in case of not-blocking call. NULL to be provided if not-used.
 * \param[in]       ISRCxt            Context to be used by /ref fnISRCb. NULL to be provided if not-used.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_TIMER_Start(ptxPlatTimer_t         * timer,
                                uint32_t                 ms,
                                uint8_t                  isBlock,
                                pptxPlat_TimerCallBack_t fnISRCb,
                                void                   * ISRCxt);

/**
 * \brief Get Elapse state of the timer.
 *
 * \note This function shall be called once that the timer has been started
 *
 * \param[in]       timer             Pointer to an initialized timer context.
 * \param[out]      isElapsed         Pointer where the elapse state is going to be written.(e.g. 1 if timer is elapsed, 0 if timer is not elapsed)
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_TIMER_IsElapsed(ptxPlatTimer_t * timer, uint8_t * isElapsed);

/**
 * \brief Stop the timer.
 *
 * \note This function shall be called once that the timer has been started.
 *
 * \param[in]       timer             Pointer to an initialized timer context.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_TIMER_Stop(ptxPlatTimer_t * timer);

/**
 * \brief De initialize the timer.
 *
 * \note This function shall be called once that the timer has been used.
 *       It shall :
 *          1./ Stop the timer in case that is still in-use.
 *          2./ Release the timer to be available by the system.
 *
 * \param[in]       timer             Pointer to an initialized timer context.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_TIMER_Deinit(ptxPlatTimer_t * timer);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* Guard */
