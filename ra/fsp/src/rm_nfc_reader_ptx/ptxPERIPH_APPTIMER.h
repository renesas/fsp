/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef STACK_COMPS_PERIPHERALS_PTXPERIPH_APPTIMER_H_
 #define STACK_COMPS_PERIPHERALS_PTXPERIPH_APPTIMER_H_

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */
 #include "ptxStatus.h"
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
 * \brief Timer Status Type for tracking timer elapsed time.
 */
typedef struct TimerStatus
{
    uint8_t  IsElapsed;
    uint32_t ElapsedTime;
} TimerStatus_t;

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */
ptxStatus_t ptxPERIPH_APPTIMER_Open(timer_instance_t * timer_instance);

/**
 * \brief Initializes and starts the timer for a given duration.
 *
 * \param[in]   ms  Milliseconds until the timer elapses.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPERIPH_APPTIMER_Start(uint32_t ms);

/**
 * \brief Retrieves status information from the timer.
 *
 * \param[in,out]   timerStatus Pointer to \ref TimerStatus_t.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPERIPH_APPTIMER_Status(TimerStatus_t * timerStatus);

/**
 * \brief Stops and deinitializes the timer.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPERIPH_APPTIMER_Stop();

 #ifdef __cplusplus
}
 #endif

#endif                                 /* Guard */
