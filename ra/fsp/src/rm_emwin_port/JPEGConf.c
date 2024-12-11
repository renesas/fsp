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
 * File    : JPEGConf.c
 * Purpose : Configuration file for emWin.
 * --------  END-OF-HEADER  ------------------------------------------
 */

#include <stdlib.h>
#include <string.h>

#include "GUI_Private.h"
#include "LCDConf.h"

#if EMWIN_CFG_RTOS == 2
 #include "FreeRTOS.h"
 #include "semphr.h"
#endif

#if EMWIN_JPEG_USE_HW && EMWIN_LCD_USE_DAVE

 #include "JPEGConf.h"
 #include "r_jpeg.h"

void _JPEGDecodeCallback(jpeg_callback_args_t * p_args);
void JPEG_X_Init(void);
int  JPEG_X_Draw(GUI_GET_DATA_FUNC * pfGetData, void * p, int x0, int y0);
void JPEG_X_DeInit(void);
void JPEG_X_SetStayAlive(int32_t OnOff);
void JPEG_X_IncStayAlive(void);
void JPEG_X_DecStayAlive(void);

void MOVIE_X_cbNotify(GUI_MOVIE_HANDLE hMovie, int32_t Notification, uint32_t CurrentFrame);

/*********************************************************************
 *
 *       Extern data
 *
 **********************************************************************
 */
extern const jpeg_instance_t * _g_jpeg_emwin_decode;

extern void LCDCONF_DrawJPEG(int32_t      LayerIndex,
                             int32_t      x,
                             int32_t      y,
                             const void * p,
                             int32_t      xSize,
                             int32_t      ySize,
                             int32_t      BytesPerLine);

 #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT
extern void LCDCONF_FlushJPEG(void);

 #endif

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */

 #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT
static uint8_t _aBuffer[EMWIN_JPEG_NUMBYTES_OUTBUFFER * 2] __attribute__((section(EMWIN_JPEG_BUFFER_SECTION)))
BSP_ALIGN_VARIABLE(8);
 #else
static uint8_t _aBuffer[EMWIN_JPEG_NUMBYTES_OUTBUFFER] __attribute__((section(EMWIN_JPEG_BUFFER_SECTION)))
BSP_ALIGN_VARIABLE(8);
 #endif

 #if !EMWIN_JPEG_NOCOPY
static uint8_t _aInBuffer[EMWIN_JPEG_NUMBYTES_INBUFFER] __attribute__((section(EMWIN_JPEG_BUFFER_SECTION)))
BSP_ALIGN_VARIABLE(8);
 #endif

static volatile jpeg_status_t g_jpeg_status = JPEG_STATUS_NONE;

 #if EMWIN_CFG_RTOS == 2               // FreeRTOS
static SemaphoreHandle_t _SemaphoreJPEG;
static StaticSemaphore_t _SemaphoreJPEG_Memory;
 #else
static volatile uint8_t _jpeg_done = 0;
 #endif

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       _JPEGDecodeCallback
 */
void _JPEGDecodeCallback (jpeg_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    //
    // Get status
    //
    g_jpeg_status = p_args->status;

 #if EMWIN_CFG_RTOS == 2               // FreeRTOS
    BaseType_t context_switch;

    //
    // Set JPEG semaphore
    //
    xSemaphoreGiveFromISR(_SemaphoreJPEG, &context_switch);

    //
    // Return to the highest priority available task
    //
    portYIELD_FROM_ISR(context_switch);
 #else
    _jpeg_done = 1;
 #endif
}

/*********************************************************************
 *
 *       _DrawBitmap
 */
static void _DrawBitmap (int32_t x, int32_t y, void const * p, int32_t xSize, int32_t ySize, int32_t BytesPerLine)
{
 #if (GUI_WINSUPPORT)
    GUI_RECT r;

    WM_ADDORG(x, y);
    r.x0 = (int16_t) x;
    r.x1 = (int16_t) (r.x0 + xSize - 1);
    r.y0 = (int16_t) y;
    r.y1 = (int16_t) (r.y0 + ySize - 1);
    WM_ITERATE_START(&r)
 #endif
    {
        LCDCONF_DrawJPEG(0, x, y, p, xSize, ySize, BytesPerLine);
    }

 #if (GUI_WINSUPPORT)
    WM_ITERATE_END();
 #endif
}

 #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT

/*********************************************************************
 *
 *       _FlushBitmap
 */
static void _FlushBitmap (void)
{
    LCDCONF_FlushJPEG();
}

 #endif

/*********************************************************************
 *
 *       _WaitForCallbackTimed
 */
static int32_t _WaitForCallbackTimed (uint32_t TimeOut)
{
 #if EMWIN_CFG_RTOS == 2               // FreeRTOS
    return xSemaphoreTake(_SemaphoreJPEG, TimeOut) ? 0 : 1;
 #else
    while (!_jpeg_done && TimeOut--)
    {
        GUI_X_Delay(1);
    }

    _jpeg_done = 0;

    return !TimeOut;
 #endif
}

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       JPEG_X_Init
 */
void JPEG_X_Init (void)
{
 #if EMWIN_CFG_RTOS == 2               // FreeRTOS
    _SemaphoreJPEG = xSemaphoreCreateBinaryStatic(&_SemaphoreJPEG_Memory);
 #endif
    GUI_JPEG_SetpfDrawEx(JPEG_X_Draw);
}

/*********************************************************************
 *
 *       JPEG_X_Draw
 */
int JPEG_X_Draw (GUI_GET_DATA_FUNC * pfGetData, void * p, int x0, int y0)
{
    int32_t            Error;
    int32_t            x;
    int32_t            y;
    int32_t            xSize;
    int32_t            ySize;
    int32_t            BitsPerPixel;
    int32_t            BytesPerLine;
    int32_t            Off;
    int32_t            NumBytesInBuffer;
    int32_t            OutBufferSize;
    uint32_t           LinesDecoded;
    void             * pInBuffer;
    void             * pOutBuffer;
    jpeg_color_space_t ColorSpace;
 #if EMWIN_JPEG_NOCOPY
    uint8_t * _aInBuffer;
 #endif

    GUI_LOCK();
    x             = x0;
    y             = y0;
    xSize         = 0;
    ySize         = 0;
    Error         = 0;
    g_jpeg_status = JPEG_STATUS_NONE;

    //
    // Initialize JPEG decoder
    //
    if (R_JPEG_Open(_g_jpeg_emwin_decode->p_ctrl, _g_jpeg_emwin_decode->p_cfg) != FSP_SUCCESS)
    {
        GUI_UNLOCK();

        return 1;
    }

    NumBytesInBuffer = 0;

    while (!(g_jpeg_status & JPEG_STATUS_ERROR))
    {
        //
        // Get data
        //
        Off = pfGetData(p,
                        (const uint8_t **) &pInBuffer,
                        (uint32_t) EMWIN_JPEG_NUMBYTES_INBUFFER,
                        (uint32_t) NumBytesInBuffer);
 #if EMWIN_JPEG_NOCOPY
        _aInBuffer = pInBuffer;
 #else
        memcpy(_aInBuffer, pInBuffer, (size_t) Off);
 #endif
        NumBytesInBuffer += Off;

        //
        // Set in-buffer to get some information about the JPEG
        //
        if (R_JPEG_InputBufferSet(_g_jpeg_emwin_decode->p_ctrl, (void *) _aInBuffer,
                                  EMWIN_JPEG_NUMBYTES_INBUFFER) != FSP_SUCCESS)
        {
            Error = 2;

            break;
        }

        //
        // Wait for callback
        //
        if (_WaitForCallbackTimed(EMWIN_JPEG_TIMEOUT))
        {
            Error = 3;

            break;
        }

        if (g_jpeg_status & JPEG_STATUS_IMAGE_SIZE_READY)
        {
            break;
        }
    }

    if (!Error)
    {
        //
        // Get image dimensions
        //
        if (R_JPEG_DecodeImageSizeGet(_g_jpeg_emwin_decode->p_ctrl, (uint16_t *) &xSize,
                                      (uint16_t *) &ySize) != FSP_SUCCESS)
        {
            Error = 4;
        }
    }

    if (!Error)
    {
        //
        // Get color space and check dimensions accordingly
        //
        R_JPEG_DecodePixelFormatGet(_g_jpeg_emwin_decode->p_ctrl, &ColorSpace);
        if (g_jpeg_status & JPEG_STATUS_ERROR)
        {
            //
            // Image dimensions incompatible with JPEG Codec
            //
            Error = 5;
        }
    }

    if (!Error)
    {
        //
        // Set up out buffer
        //
        BitsPerPixel  = (_g_jpeg_emwin_decode->p_cfg->pixel_format == JPEG_DECODE_PIXEL_FORMAT_ARGB8888) ? 32 : 16;
        BytesPerLine  = (xSize * BitsPerPixel) >> 3;
        OutBufferSize = EMWIN_JPEG_NUMBYTES_OUTBUFFER;
        pOutBuffer    = (void *) _aBuffer;

        //
        // Set stride value
        //
        if (R_JPEG_DecodeHorizontalStrideSet(_g_jpeg_emwin_decode->p_ctrl, (uint32_t) xSize) != FSP_SUCCESS)
        {
            Error = 6;
        }
    }

    if (!Error)
    {
        //
        // Start decoding process by setting out-buffer
        //
        if (R_JPEG_OutputBufferSet(_g_jpeg_emwin_decode->p_ctrl, pOutBuffer, (uint32_t) OutBufferSize) != FSP_SUCCESS)
        {
            Error = 7;
        }
    }

    if (!Error)
    {
        while (!(g_jpeg_status & JPEG_STATUS_ERROR))
        {
            //
            // Do not wait forever, it might fail and we will hang
            //
            if (_WaitForCallbackTimed(EMWIN_JPEG_TIMEOUT))
            {
                Error = 8;

                break;
            }

            if ((g_jpeg_status & JPEG_STATUS_OUTPUT_PAUSE) || (g_jpeg_status & JPEG_STATUS_OPERATION_COMPLETE))
            {
                //
                // Draw the JPEG work buffer to the framebuffer
                //
                R_JPEG_DecodeLinesDecodedGet(_g_jpeg_emwin_decode->p_ctrl, &LinesDecoded);
                _DrawBitmap(x, y, (void const *) pOutBuffer, xSize, (int32_t) LinesDecoded, BytesPerLine);
                y = y + (int32_t) LinesDecoded;
 #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT
                pOutBuffer = (pOutBuffer == _aBuffer) ? (&_aBuffer[EMWIN_JPEG_NUMBYTES_OUTBUFFER]) : (_aBuffer);
 #endif
                if (!(g_jpeg_status & JPEG_STATUS_OPERATION_COMPLETE))
                {
                    //
                    // Set the output buffer to the next 16-line block
                    //
                    if (R_JPEG_OutputBufferSet(_g_jpeg_emwin_decode->p_ctrl, pOutBuffer,
                                               (uint32_t) OutBufferSize) != FSP_SUCCESS)
                    {
                        Error = 10;

                        break;
                    }
                }
            }

            if (g_jpeg_status & JPEG_STATUS_INPUT_PAUSE)
            {
                //
                // Get next block of input data
                //
                Off = pfGetData(p,
                                (const uint8_t **) &pInBuffer,
                                (uint32_t) EMWIN_JPEG_NUMBYTES_INBUFFER,
                                (uint32_t) NumBytesInBuffer);
 #if EMWIN_JPEG_NOCOPY
                _aInBuffer = pInBuffer;
 #else
                memcpy(_aInBuffer, pInBuffer, (size_t) Off);
 #endif
                NumBytesInBuffer += Off;

                //
                // Set the new input buffer pointer
                //
                if (R_JPEG_InputBufferSet(_g_jpeg_emwin_decode->p_ctrl, (void *) _aInBuffer,
                                          EMWIN_JPEG_NUMBYTES_INBUFFER) != FSP_SUCCESS)
                {
                    Error = 9;

                    break;
                }
            }

            if (g_jpeg_status & JPEG_STATUS_OPERATION_COMPLETE)
            {
 #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT

                //
                // Wait for any remaining draw operation to finish
                //
                _FlushBitmap();
 #endif
                break;
            }
        }
    }

    if ((g_jpeg_status & JPEG_STATUS_ERROR) && (!Error))
    {
        Error = 11;
    }

    //
    // De-Init
    //
    R_JPEG_Close(_g_jpeg_emwin_decode->p_ctrl);

    GUI_UNLOCK();

    return Error;
}

#endif

/*************************** End of file ****************************/
