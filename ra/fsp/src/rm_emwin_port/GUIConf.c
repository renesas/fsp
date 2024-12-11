/**********************************************************************
 *                    SEGGER Microcontroller GmbH                     *
 *        Solutions for real time microcontroller applications        *
 **********************************************************************
 *                                                                    *
 *        (c) 1996 - 2019  SEGGER Microcontroller GmbH                *
 *                                                                    *
 *        Internet: www.segger.com    Support:  support@segger.com    *
 *                                                                    *
 **********************************************************************
 *
 ** emWin V5.50 - Graphical user interface for embedded applications **
 * emWin is protected by international copyright laws.   Knowledge of the
 * source code may not be used to write a similar product.  This file may
 * only  be used  in accordance  with  a license  and should  not be  re-
 * distributed in any way. We appreciate your understanding and fairness.
 *----------------------------------------------------------------------
 * File        : GUIConf.c
 * Purpose     : Display controller initialization
 *---------------------------END-OF-HEADER------------------------------
 */

#include <stdint.h>

#include "GUI.h"
#include "GUIConf.h"

//
// 32 bit aligned memory area
//
static uint32_t aMemory[GUI_NUMBYTES / 4] __attribute__((section(GUI_HEAPSECTION))) __attribute__((aligned(8))); // Align for JPEG processing

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       GUI_X_Config
 *
 * Purpose:
 *   Called during the initialization process in order to set up the
 *   available memory for the GUI.
 */
void GUI_X_Config (void)
{
    //
    // Assign memory to emWin
    //
    GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);

    //
    // Set default font
    //
    GUI_SetDefaultFont(GUI_FONT_6X8);
}

/* Unused weak definition for AppWizard-required function. */
__attribute__((weak)) void APPW_X_FS_Init (void)
{
    /* Function not used. */
}

/*************************** End of file ****************************/
