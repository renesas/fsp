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
 * File        : GUI_X_FreeRTOS.c
 * Purpose     : Config / System dependent externals for GUI
 * ---------------------------END-OF-HEADER---------------------------
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "GUI.h"

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */
static SemaphoreHandle_t _Semaphore;
static StaticSemaphore_t _Semaphore_Memory;

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

int GUI_X_GetTime (void)
{
    return (int) (xTaskGetTickCount() * portTICK_PERIOD_MS);
}

void GUI_X_Delay (int Period)
{
    vTaskDelay(pdMS_TO_TICKS(Period));
}

/*********************************************************************
 *
 *       GUI_X_ExecIdle()
 *
 */
void GUI_X_ExecIdle (void)
{
    vTaskDelay(pdMS_TO_TICKS(1));
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
    _Semaphore = xSemaphoreCreateCountingStatic(1, 0, &_Semaphore_Memory);
}

void GUI_X_Unlock (void)
{
    xSemaphoreGive(_Semaphore);
}

void GUI_X_Lock (void)
{
    xSemaphoreTake(_Semaphore, 0);
}

unsigned long GUI_X_GetTaskId (void)
{
    return (uint32_t) xTaskGetCurrentTaskHandle();
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
#define OS_SendString(s)    GUI_USE_PARA(s)

__attribute__((weak)) void GUI_X_Log (const char * s)
{
    printf("%s", s);
}

__attribute__((weak)) void GUI_X_Warn (const char * s)
{
    printf("%s", s);
}

__attribute__((weak)) void GUI_X_ErrorOut (const char * s)
{
    printf("%s", s);
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
    /* Do nothing */
}

/*************************** End of file ****************************/
