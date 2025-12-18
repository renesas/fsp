/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "lwip/memp.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "netif/ppp/ppp_opts.h"

#include "rm_lwip_sys_baremetal.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#if LWIP_DEBUG_TIMERNAMES
 #define HANDLER(x)    x, #x
#else                                  /* LWIP_DEBUG_TIMERNAMES */
 #define HANDLER(x)    x
#endif /* LWIP_DEBUG_TIMERNAMES */

#define LWIP_MAX_TIMEOUT    0x7fffffff

/* Check if timer's expiry time is greater than time and care about u32_t wraparounds */
#define TIME_LESS_THAN(t, compare_to)    ((((u32_t) ((t) - (compare_to))) > LWIP_MAX_TIMEOUT) ? 1 : 0)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
extern rm_lwip_sys_baremetal_instance_t * rm_lwip_sys_baremetal_set_instance(void);
void                                      rm_lwip_sys_baremetal_timer_callback(timer_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
static void rm_lwip_sys_baremetal_timer_setup(void);

/* Declare memory pool for sys_timeouts. */
LWIP_MEMPOOL_DECLARE(SYS_TIMEOUT, MEMP_NUM_SYS_TIMEOUT, sizeof(struct sys_timeo), "SYS_TIMEOUT");

static rm_lwip_sys_baremetal_instance_t * gp_lwip_sys_baremetal_instance;

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*
 * Return current count in raw.
 */
u32_t sys_jiffies (void)
{
    return gp_lwip_sys_baremetal_instance->p_ctrl->timer_count;
}

/*
 * Return current count in milliseconds.
 * This funcition is called by lwIP timeouts.
 */
u32_t sys_now (void)
{
    return sys_jiffies();
}

static void
#if LWIP_DEBUG_TIMERNAMES
sys_timeout_abs (u32_t abs_time, sys_timeout_handler handler, void * arg, const char * handler_name)
#else                                  /* LWIP_DEBUG_TIMERNAMES */
sys_timeout_abs(u32_t abs_time, sys_timeout_handler handler, void * arg)
#endif
{
    struct sys_timeo * timeout;
    struct sys_timeo * t;

    timeout = (struct sys_timeo *) LWIP_MEMPOOL_ALLOC(SYS_TIMEOUT);
    if (timeout == NULL)
    {
        LWIP_ASSERT("sys_timeout: timeout != NULL, pool MEMP_SYS_TIMEOUT is empty", timeout != NULL);

        return;
    }

    timeout->next = NULL;
    timeout->h    = handler;
    timeout->arg  = arg;
    timeout->time = abs_time;

#if LWIP_DEBUG_TIMERNAMES
    timeout->handler_name = handler_name;
    LWIP_DEBUGF(TIMERS_DEBUG,
                ("sys_timeout: %p abs_time=%"U32_F " handler=%s arg=%p\n",
                 (void *) timeout, abs_time, handler_name, (void *) arg));
#endif                                 /* LWIP_DEBUG_TIMERNAMES */

    if (gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout == NULL)
    {
        gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout = timeout;

        return;
    }

    if (TIME_LESS_THAN(timeout->time, gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout->time))
    {
        timeout->next = gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout;
        gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout = timeout;
    }
    else
    {
        t = gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout;
        while (t != NULL)
        {
            if ((t->next == NULL) || TIME_LESS_THAN(timeout->time, t->next->time))
            {
                timeout->next = t->next;
                t->next       = timeout;
                break;
            }

            t = t->next;
        }
    }
}

/*
 * Timer callback function that calls cyclic->handler() and reschedules itself.
 *
 * @param arg unused argument
 */
static
void lwip_cyclic_timer (void * arg)
{
    u32_t now;
    u32_t next_timeout_time;
    const struct lwip_cyclic_timer * cyclic = (const struct lwip_cyclic_timer *) arg;

#if LWIP_DEBUG_TIMERNAMES
    LWIP_DEBUGF(TIMERS_DEBUG, ("tcpip: %s()\n", cyclic->handler_name));
#endif
    cyclic->handler();

    now               = sys_now();
    next_timeout_time =
        (u32_t) (gp_lwip_sys_baremetal_instance->p_ctrl->current_timeout_due_time + cyclic->interval_ms); /* overflow handled by TIME_LESS_THAN macro */
    if (TIME_LESS_THAN(next_timeout_time, now))
    {
        /* timer would immediately expire again -> "overload" -> restart without any correction */
#if LWIP_DEBUG_TIMERNAMES
        sys_timeout_abs((u32_t) (now + cyclic->interval_ms), lwip_cyclic_timer, arg, cyclic->handler_name);
#else
        sys_timeout_abs((u32_t) (now + cyclic->interval_ms), lwip_cyclic_timer, arg);
#endif
    }
    else
    {
        /* correct cyclic interval with handler execution delay and sys_check_timeouts jitter */
#if LWIP_DEBUG_TIMERNAMES
        sys_timeout_abs(next_timeout_time, lwip_cyclic_timer, arg, cyclic->handler_name);
#else
        sys_timeout_abs(next_timeout_time, lwip_cyclic_timer, arg);
#endif
    }
}

/* Initialize this module */
void sys_timeouts_init (void)
{
    int i;

    /* Initialize memory pool for sys_timeouts. */
    LWIP_MEMPOOL_INIT(SYS_TIMEOUT);

    /* Initialize FSP timer. */
    rm_lwip_sys_baremetal_timer_setup();

    for (i = 0; i < lwip_num_cyclic_timers; i++)
    {
        /* we have to cast via size_t to get rid of const warning
         * (this is OK as cyclic_timer() casts back to const* */
        sys_timeout(lwip_cyclic_timers[i].interval_ms,
                    lwip_cyclic_timer,
                    LWIP_CONST_CAST(void *, &lwip_cyclic_timers[i]));
    }
}

/*
 * Create a one-shot timer (aka timeout). Timeouts are processed in the
 * following cases:
 * - while waiting for a message using sys_timeouts_mbox_fetch()
 * - by calling sys_check_timeouts() (NO_SYS==1 only)
 *
 * @param msecs time in milliseconds after that the timer should expire
 * @param handler callback function to call when msecs have elapsed
 * @param arg argument to pass to the callback function
 */
#if LWIP_DEBUG_TIMERNAMES
void sys_timeout_debug (u32_t msecs, sys_timeout_handler handler, void * arg, const char * handler_name)
#else                                  /* LWIP_DEBUG_TIMERNAMES */
void sys_timeout (u32_t msecs, sys_timeout_handler handler, void * arg)
#endif /* LWIP_DEBUG_TIMERNAMES */
{
    u32_t next_timeout_time;

    LWIP_ASSERT_CORE_LOCKED();

    LWIP_ASSERT("Timeout time too long, max is LWIP_UINT32_MAX/4 msecs", msecs <= (LWIP_UINT32_MAX / 4));

    next_timeout_time = (u32_t) (sys_now() + msecs); /* overflow handled by TIME_LESS_THAN macro */

#if LWIP_DEBUG_TIMERNAMES
    sys_timeout_abs(next_timeout_time, handler, arg, handler_name);
#else
    sys_timeout_abs(next_timeout_time, handler, arg);
#endif
}

/*
 * Go through timeout list (for this task only) and remove the first matching
 * entry (subsequent entries remain untouched), even though the timeout has not
 * triggered yet.
 *
 * @param handler callback function that would be called by the timeout
 * @param arg callback argument that would be passed to handler
 */
void sys_untimeout (sys_timeout_handler handler, void * arg)
{
    struct sys_timeo * prev_t;
    struct sys_timeo * t;

    LWIP_ASSERT_CORE_LOCKED();

    if (gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout == NULL)
    {
        return;
    }

    prev_t = NULL;
    t      = gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout;
    while (t != NULL)
    {
        if ((t->h == handler) && (t->arg == arg))
        {
            /* We have a match */
            /* Unlink from previous in list */
            if (prev_t == NULL)
            {
                gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout = t->next;
            }
            else
            {
                prev_t->next = t->next;
            }

            LWIP_MEMPOOL_FREE(SYS_TIMEOUT, t);

            return;
        }

        prev_t = t;
        t      = t->next;
    }
}

/*
 * @ingroup lwip_nosys
 * Handle timeouts for NO_SYS==1 (i.e. without using
 * tcpip_thread/sys_timeouts_mbox_fetch(). Uses sys_now() to call timeout
 * handler functions when timeouts expire.
 *
 * Must be called periodically from your main loop.
 */
void sys_check_timeouts (void)
{
    u32_t now;

    LWIP_ASSERT_CORE_LOCKED();

    /* Process only timers expired at the start of the function. */
    now = sys_now();

    do
    {
        struct sys_timeo  * tmptimeout;
        sys_timeout_handler handler;
        void              * arg;

        PBUF_CHECK_FREE_OOSEQ();

        tmptimeout = gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout;
        if (tmptimeout == NULL)
        {
            return;
        }

        if (TIME_LESS_THAN(now, tmptimeout->time))
        {
            return;
        }

        /* Timeout has expired */
        gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout = tmptimeout->next;
        handler = tmptimeout->h;
        arg     = tmptimeout->arg;
        gp_lwip_sys_baremetal_instance->p_ctrl->current_timeout_due_time = tmptimeout->time;
#if LWIP_DEBUG_TIMERNAMES
        if (handler != NULL)
        {
            LWIP_DEBUGF(TIMERS_DEBUG,
                        ("sct calling h=%s t=%"U32_F " arg=%p\n",
                         tmptimeout->handler_name, sys_now() - tmptimeout->time, arg));
        }
#endif                                 /* LWIP_DEBUG_TIMERNAMES */
        LWIP_MEMPOOL_FREE(SYS_TIMEOUT, tmptimeout);
        if (handler != NULL)
        {
            handler(arg);
        }

        LWIP_TCPIP_THREAD_ALIVE();

        /* Repeat until all expired timers have been called */
    } while (1);
}

/* Rebase the timeout times to the current time.
 * This is necessary if sys_check_timeouts() hasn't been called for a long
 * time (e.g. while saving energy) to prevent all timer functions of that
 * period being called.
 */
void sys_restart_timeouts (void)
{
    u32_t              now;
    u32_t              base;
    struct sys_timeo * t;

    if (gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout == NULL)
    {
        return;
    }

    now  = sys_now();
    base = gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout->time;

    t = gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout;
    while (t != NULL)
    {
        t->time = (t->time - base) + now;
        t       = t->next;
    }
}

/* Return the time left before the next timeout is due. If no timeouts are
 * enqueued, returns 0xffffffff
 */
u32_t sys_timeouts_sleeptime (void)
{
    u32_t now;
    u32_t ret;

    LWIP_ASSERT_CORE_LOCKED();

    if (gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout == NULL)
    {
        return SYS_TIMEOUTS_SLEEPTIME_INFINITE;
    }

    now = sys_now();
    if (TIME_LESS_THAN(gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout->time, now))
    {
        ret = 0;
    }
    else
    {
        ret = (u32_t) (gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout->time - now);
        LWIP_ASSERT("invalid sleeptime", ret <= LWIP_MAX_TIMEOUT);
    }

    return ret;
}

/***********************************************************************************************************************
 * Increments system time.
 **********************************************************************************************************************/
void rm_lwip_sys_baremetal_timer_callback (timer_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    gp_lwip_sys_baremetal_instance->p_ctrl->timer_count += 1;
}

/***********************************************************************************************************************
 * Return an instance of this porting layer.
 **********************************************************************************************************************/
BSP_WEAK_REFERENCE rm_lwip_sys_baremetal_instance_t * rm_lwip_sys_baremetal_set_instance (void)
{
    /* Not implemented in this code and must be generated by configuration. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(0);

    return NULL;
}

/***********************************************************************************************************************
 * Initialize and start timers used by the lwIP timeouts features.
 * This function is called from sys_timeouts_init.
 **********************************************************************************************************************/
static void rm_lwip_sys_baremetal_timer_setup (void)
{
    const timer_instance_t * p_timer_instance;

    /* Get instance of baremetal porting layer. */
    gp_lwip_sys_baremetal_instance = rm_lwip_sys_baremetal_set_instance();

    /* Null check for each parameters. */
    FSP_ERROR_RETURN(NULL != gp_lwip_sys_baremetal_instance, );
    FSP_ERROR_RETURN(NULL != gp_lwip_sys_baremetal_instance->p_cfg, );
    FSP_ERROR_RETURN(NULL != gp_lwip_sys_baremetal_instance->p_ctrl, );
    FSP_ERROR_RETURN(NULL != gp_lwip_sys_baremetal_instance->p_cfg->p_timer_instance, );

    /* Initialize control block. */
    gp_lwip_sys_baremetal_instance->p_ctrl->current_timeout_due_time = 0;
    gp_lwip_sys_baremetal_instance->p_ctrl->p_next_timeout           = NULL;
    gp_lwip_sys_baremetal_instance->p_ctrl->timer_count              = 0;

    /* Start timer. */
    p_timer_instance = gp_lwip_sys_baremetal_instance->p_cfg->p_timer_instance;
    p_timer_instance->p_api->open(p_timer_instance->p_ctrl, p_timer_instance->p_cfg);
    p_timer_instance->p_api->callbackSet(p_timer_instance->p_ctrl, rm_lwip_sys_baremetal_timer_callback, NULL, NULL);
    p_timer_instance->p_api->start(p_timer_instance->p_ctrl);
}
