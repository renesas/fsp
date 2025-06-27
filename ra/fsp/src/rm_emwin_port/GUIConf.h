/*********************************************************************
 *                    SEGGER Microcontroller GmbH                     *
 *        Solutions for real time microcontroller applications        *
 **********************************************************************
 *                                                                    *
 *        (c) 1996 - 2024  SEGGER Microcontroller GmbH                *
 *                                                                    *
 *        Internet: www.segger.com    Support:  support@segger.com    *
 *                                                                    *
 **********************************************************************
 *
 * ** emWin V6.48 - Graphical user interface for embedded applications **
 * emWin is protected by international copyright laws.   Knowledge of the
 * source code may not be used to write a similar product.  This file may
 * only  be used  in accordance  with  a license  and should  not be  re-
 * distributed in any way. We appreciate your understanding and fairness.
 * ----------------------------------------------------------------------
 * Licensing information
 * Licensor:                 SEGGER Software GmbH
 * Licensed to:              Renesas Electronics America Inc., 1001 Murphy Ranch Road, Milpitas, California 95035, USA
 * Licensed SEGGER software: emWin
 * License number:           GUI-00785
 * License model:            emWin License and Service Agreement, signed May 9th, 2019
 *                           and Amendment No. 1, signed June 29, 2021
 *                           and Amendment No. 2, signed June 27, 2022
 * Licensed platform:        ARM Cortex-M4, -M33, -M23 and -M85 based devices of the RA family of the 32-bit Microcontroller Units, designed, marketed and manufactured by LICENSEE only
 * ---------------------------------------------------------------------
 * File        : GUIConf.h
 * Purpose     : Configuration of available features and default values
 * ----------------------------END-OF-HEADER----------------------------
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
