/**********************************************************************
 *                SEGGER Microcontroller GmbH & Co. KG                *
 *                        The Embedded Experts                        *
 **********************************************************************
 *                                                                    *
 *       (c) 2003 - 2017  SEGGER Microcontroller GmbH & Co. KG        *
 *                                                                    *
 *       www.segger.com     Support: support@segger.com               *
 *                                                                    *
 **********************************************************************
 * -------------------------------------------------------------------
 * File        : JPEGConf.h
 * Purpose     : Configuration header file to draw JPEG with hardware
 * -------------------------------------------------------------------
 */

#ifndef JPEGCONF_H
#define JPEGCONF_H

#include <stdint.h>

#include "rm_emwin_port_cfg.h"

#if EMWIN_JPEG_USE_HW && EMWIN_LCD_USE_DAVE

typedef struct
{
    uint32_t WorkBufferSize;
    void * (*pfMalloc)(size_t size);
    void (* pfFree)(void * ptr);
    int32_t             ColorFormat;
    uint8_t           * pWorkBuffer;
    GUI_HMEM            hWorkBuffer;
    uint8_t           * pOutBuffer;
    GUI_HMEM            hOutBuffer;
    uint32_t            OutBufferSize;
    uint8_t           * pInBuffer;
    uint32_t            NumBytesInBuffer;
    int32_t             BitsPerPixel;
    int32_t             BytesPerLine;
    GUI_GET_DATA_FUNC * pfGetData;
    void              * pVoid;
    uint32_t            Off;
    uint32_t            xPos;
    uint32_t            yPos;
    uint32_t            xSize;
    uint32_t            ySize;
    uint32_t            BlockSize;
    uint32_t            TotalMCUs;
    uint32_t            IndexMCU;
    uint32_t (* pfConvert)(uint32_t BlockIndex);
    uint8_t  VFactor;
    uint32_t xSizeExtended;
    uint8_t  Error;
    uint8_t  IRQFlag;
 #if GUI_SUPPORT_MEMDEV
    GUI_MEMDEV_Handle hMem;
 #endif
} JPEG_X_CONTEXT;

#endif

#endif                                 /* LCDCONF_H */

/*************************** End of file ****************************/
