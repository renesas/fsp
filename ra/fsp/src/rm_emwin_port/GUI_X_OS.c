/**********************************************************************
 *                SEGGER MICROCONTROLLER GmbH & Co. KG                *
 *        Solutions for real time microcontroller applications        *
 **********************************************************************
 *                                                                    *
 *        (c) 2003-2015     SEGGER Microcontroller GmbH & Co KG       *
 *                                                                    *
 *        Internet: www.segger.com    Support:  support@segger.com    *
 *                                                                    *
 **********************************************************************
 *
 * -------------------------------------------------------------------
 * File        : GUI_X_OS.c
 * Purpose     : Config / System dependent externals for GUI
 * ---------------------------END-OF-HEADER---------------------------
 */

#include <stdio.h>
#include "GUI.h"
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
 #include "FreeRTOS.h"
 #include "semphr.h"
 #include "task.h"
#else
 #include "bsp_api.h"
#endif

#define EMWIN_OS_PRV_SYSTICK_HZ    (1000U)

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
static SemaphoreHandle_t _Semaphore;
static StaticSemaphore_t _Semaphore_Memory;
#else
static volatile uint32_t g_gui_time_ms = 0;
#endif

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *      Timing:
 *                 GUI_GetTime()
 *                 GUI_Delay(int)
 *
 * Some timing dependent routines require a GetTime
 * and delay funtion. Default time unit (tick), normally is
 * 1 ms.
 */
#if EMWIN_CFG_RTOS == 0                // No RTOS
void SysTick_Handler(void);

void SysTick_Handler (void)
{
    g_gui_time_ms++;
}

#endif

GUI_TIMER_TIME GUI_X_GetTime (void)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
    return (GUI_TIMER_TIME) (xTaskGetTickCount() * portTICK_PERIOD_MS);
#else
    return (GUI_TIMER_TIME) g_gui_time_ms;
#endif
}

void GUI_X_Delay (int Period)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(Period));
#else
    uint32_t time_start = g_gui_time_ms;

    /* Wait for the specified number of ticks */
    do
    {
 #if !defined(BSP_CFG_RTOS_IDLE_SLEEP) || BSP_CFG_RTOS_IDLE_SLEEP
        __WFI();
 #else
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
 #endif
    } while ((int) (g_gui_time_ms - time_start) < Period);
#endif
}

/*********************************************************************
 *
 *       GUI_X_ExecIdle()
 *
 */
void GUI_X_ExecIdle (void)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(1));
#endif
}

/*********************************************************************
 *
 *      Multitasking:
 *
 *                 GUI_X_InitOS()
 *                 GUI_X_GetTaskId()
 *                 GUI_X_Lock()
 *                 GUI_X_Unlock()
 *
 * Note:
 *   The following routines are required only if emWin is used in a
 *   true multi task environment, which means you have more than one
 *   thread using the emWin API.
 *   In this case the
 *                       #define GUI_OS 1
 *  needs to be in GUIConf.h
 */
void GUI_X_InitOS (void)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
    _Semaphore = xSemaphoreCreateCountingStatic(1, 0, &_Semaphore_Memory);
#endif
}

void GUI_X_Unlock (void)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
    xSemaphoreGive(_Semaphore);
#endif
}

void GUI_X_Lock (void)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
    xSemaphoreTake(_Semaphore, 0);
#endif
}

unsigned long GUI_X_GetTaskId (void)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
    return (uint32_t) xTaskGetCurrentTaskHandle();
#else
    return 1;
#endif
}

/*********************************************************************
 *
 *      Logging: OS dependent
 *
 * Note:
 * Logging is used in higher debug levels only. The typical target
 * build does not use logging and does therefor not require any of
 * the logging routines below. For a release build without logging
 * the routines below may be eliminated to save some space.
 * (If the linker is not function aware and eliminates unreferenced
 * functions automatically)
 *
 */
#if EMWIN_CFG_RTOS == 2                // FreeRTOS
 #define OS_SendString(s)    printf("%s", s)
#else
 #define OS_SendString(s)    GUI_USE_PARA(s)
#endif

__attribute__((weak)) void GUI_X_Log (const char * s)
{
    OS_SendString(s);
}

__attribute__((weak)) void GUI_X_Warn (const char * s)
{
    OS_SendString(s);
}

__attribute__((weak)) void GUI_X_ErrorOut (const char * s)
{
    OS_SendString(s);
}

/*********************************************************************
 *
 *      GUI_X_Init()
 *
 * Note:
 *   This routine is called from GUI_Init() in any case whether there
 *   is an RTOS or not. You can use it for additional initializations
 *   needed.
 */

void GUI_X_Init (void)
{
#if EMWIN_CFG_RTOS == 2                // FreeRTOS

    /* Do nothing */
#else

    /* Configure SysTick to interrupt at 1KHz. */
    SysTick_Config(SystemCoreClock / EMWIN_OS_PRV_SYSTICK_HZ);
#endif
}

/*************************** End of file ****************************/
