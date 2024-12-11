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
 * File        : GUIConf.h
 * Purpose     : Configuration of available features and default values
 *----------------------------------------------------------------------
 */

#ifndef GUICONF_H
 #define GUICONF_H

 #include "rm_emwin_port_cfg.h"

 #ifdef __cplusplus
extern "C" {
 #endif

 #define EMWIN_SUFFIX    __attribute__((aligned(8)))

void APPW_X_FS_Init(void);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* Avoid multiple inclusion */

/*************************** End of file ****************************/
