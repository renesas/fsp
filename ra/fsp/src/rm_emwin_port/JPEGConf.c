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
#include "GUI_Private.h"
#include "JPEGConf.h"
#include "LCDConf.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include <string.h>

#if EMWIN_USE_JPEG_HW && EMWIN_USE_DAVE

 #include "r_jpeg.h"

void _JPEGDecodeCallback(jpeg_decode_callback_args_t * p_args);
void JPEG_X_Init(JPEG_X_CONTEXT * pContext);
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
extern const jpeg_decode_instance_t * _g_jpeg_emwin_decode;

extern void LCDCONF_DrawJPEG(int32_t      LayerIndex,
                             int32_t      x,
                             int32_t      y,
                             const void * p,
                             int32_t      xSize,
                             int32_t      ySize,
                             int32_t      BytesPerLine);

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */

static U8 _aBuffer[NUMBYTES_OUTBUFFER]  __attribute__((section(JPEG_BUFFER_SECTION))) BSP_ALIGN_VARIABLE(8);
static U8 _aInBuffer[NUMBYTES_INBUFFER] __attribute__((section(JPEG_BUFFER_SECTION))) BSP_ALIGN_VARIABLE(8);

static jpeg_decode_status_t g_jpeg_status = JPEG_DECODE_STATUS_NOT_OPEN;

static SemaphoreHandle_t _SemaphoreJPEG;
static StaticSemaphore_t _SemaphoreJPEG_Memory;

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
void _JPEGDecodeCallback (jpeg_decode_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    BaseType_t context_switch;

    //
    // Get status
    //
    g_jpeg_status = p_args->status;

    //
    // Set JPEG semaphore
    //
    xSemaphoreGiveFromISR(_SemaphoreJPEG, &context_switch);

    //
    // Return to the highest priority available task
    //
    portYIELD_FROM_ISR(context_switch);
}

/*********************************************************************
 *
 *       _DrawBitmap
 */
static void _DrawBitmap (int32_t x, int32_t y, void const * p, int32_t xSize, int32_t ySize, int32_t BytesPerLine)
{
 #if (GUI_WINSUPPORT)
    GUI_RECT r;
 #endif
 #if (GUI_WINSUPPORT)
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

/*********************************************************************
 *
 *       _WaitForCallbackTimed
 */
static int32_t _WaitForCallbackTimed (uint32_t TimeOut)
{
    return xSemaphoreTake(_SemaphoreJPEG, TimeOut) ? 0 : 1;
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
void JPEG_X_Init (JPEG_X_CONTEXT * pContext)
{
    GUI_USE_PARA(pContext);
    _SemaphoreJPEG = xSemaphoreCreateBinaryStatic(&_SemaphoreJPEG_Memory);
    GUI_JPEG_SetpfDrawEx(JPEG_X_Draw);
}

/*********************************************************************
 *
 *       JPEG_X_Draw
 */
int JPEG_X_Draw (GUI_GET_DATA_FUNC * pfGetData, void * p, int x0, int y0)
{
    int32_t  Error;
    int32_t  x;
    int32_t  y;
    int32_t  xSize;
    int32_t  ySize;
    int32_t  BitsPerPixel;
    int32_t  BytesPerLine;
    int32_t  Off;
    int32_t  NumBytesInBuffer;
    int32_t  OutBufferSize;
    uint32_t LinesDecoded;
    void   * pInBuffer;
    void   * pOutBuffer;
    jpeg_decode_color_space_t ColorSpace;

    GUI_LOCK();
    x             = x0;
    y             = y0;
    xSize         = 0;
    ySize         = 0;
    Error         = 0;
    g_jpeg_status = JPEG_DECODE_STATUS_NOT_OPEN;

    //
    // Initialize JPEG decoder
    //
    if (R_JPEG_Decode_Open(_g_jpeg_emwin_decode->p_ctrl, _g_jpeg_emwin_decode->p_cfg) != FSP_SUCCESS)
    {
        GUI_UNLOCK();

        return 1;
    }

    NumBytesInBuffer = 0;

    while (!(g_jpeg_status & JPEG_DECODE_STATUS_ERROR))
    {
        //
        // Get data
        //
        Off = pfGetData(p, (const U8 **) &pInBuffer, (uint32_t) NUMBYTES_INBUFFER, (uint32_t) NumBytesInBuffer);
        memcpy(_aInBuffer, pInBuffer, (size_t) Off);
        NumBytesInBuffer += Off;

        //
        // Set in-buffer to get some information about the JPEG
        //
        if (R_JPEG_Decode_InputBufferSet(_g_jpeg_emwin_decode->p_ctrl, (void *) _aInBuffer,
                                         NUMBYTES_INBUFFER) != FSP_SUCCESS)
        {
            Error = 1;

            break;
        }

        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);

        //
        // Wait for callback
        //
        if (_WaitForCallbackTimed(JPEG_TIMEOUT))
        {
            Error = 1;

            break;
        }

        if (g_jpeg_status & JPEG_DECODE_STATUS_IMAGE_SIZE_READY)
        {
            break;
        }
    }

    if (!Error)
    {
        //
        // Get image dimensions
        //
        if (R_JPEG_Decode_ImageSizeGet(_g_jpeg_emwin_decode->p_ctrl, (U16 *) &xSize, (U16 *) &ySize) != FSP_SUCCESS)
        {
            Error = 1;
        }
    }

    if (!Error)
    {
        //
        // Get color space and check dimensions accordingly
        //
        R_JPEG_Decode_PixelFormatGet(_g_jpeg_emwin_decode->p_ctrl, &ColorSpace);
        if (g_jpeg_status & JPEG_DECODE_STATUS_ERROR)
        {
            //
            // Image dimensions incompatible with JPEG Codec
            //
            Error = 1;
        }
    }

    if (!Error)
    {
        //
        // Set up out buffer
        //
        BitsPerPixel  = (_g_jpeg_emwin_decode->p_cfg->pixel_format == JPEG_DECODE_PIXEL_FORMAT_ARGB8888) ? 32 : 16;
        BytesPerLine  = (xSize * BitsPerPixel) >> 3;
        OutBufferSize = sizeof(_aBuffer);
        pOutBuffer    = (void *) _aBuffer;

        //
        // Set stride value
        //
        if (R_JPEG_Decode_HorizontalStrideSet(_g_jpeg_emwin_decode->p_ctrl, (uint32_t) xSize) != FSP_SUCCESS)
        {
            Error = 1;
        }
    }

    if (!Error)
    {
        //
        // Start decoding process by setting out-buffer
        //
        if (R_JPEG_Decode_OutputBufferSet(_g_jpeg_emwin_decode->p_ctrl, pOutBuffer,
                                          (uint32_t) OutBufferSize) != FSP_SUCCESS)
        {
            Error = 1;
        }
    }

    if (!Error)
    {
        while (!(g_jpeg_status & JPEG_DECODE_STATUS_ERROR))
        {
            //
            // Do not wait forever, it might fail and we will hang
            //
            if (_WaitForCallbackTimed(JPEG_TIMEOUT))
            {
                Error = 1;

                break;
            }

            if (g_jpeg_status & JPEG_DECODE_STATUS_INPUT_PAUSE)
            {
                //
                // Get next block of input data
                //
                Off = pfGetData(p, (const U8 **) &pInBuffer, (uint32_t) NUMBYTES_INBUFFER, (uint32_t) NumBytesInBuffer);
                memcpy(_aInBuffer, pInBuffer, (size_t) Off);
                NumBytesInBuffer += Off;

                //
                // Set the new input buffer pointer
                //
                if (R_JPEG_Decode_InputBufferSet(_g_jpeg_emwin_decode->p_ctrl, (void *) _aInBuffer,
                                                 NUMBYTES_INBUFFER) != FSP_SUCCESS)
                {
                    Error = 1;

                    break;
                }
            }

            if ((g_jpeg_status & JPEG_DECODE_STATUS_OUTPUT_PAUSE) || (g_jpeg_status & JPEG_DECODE_STATUS_DONE))
            {
                //
                // Draw the JPEG work buffer to the framebuffer
                //
                R_JPEG_Decode_LinesDecodedGet(_g_jpeg_emwin_decode->p_ctrl, &LinesDecoded);
                _DrawBitmap(x, y, (void const *) pOutBuffer, xSize, (int32_t) LinesDecoded, BytesPerLine);
                y = y + (int32_t) LinesDecoded;
                if (!(g_jpeg_status & JPEG_DECODE_STATUS_DONE))
                {
                    //
                    // Set the output buffer to the next 16-line block
                    //
                    if (R_JPEG_Decode_OutputBufferSet(_g_jpeg_emwin_decode->p_ctrl, pOutBuffer,
                                                      (uint32_t) OutBufferSize) != FSP_SUCCESS)
                    {
                        Error = 1;

                        break;
                    }
                }
            }

            if (g_jpeg_status & JPEG_DECODE_STATUS_DONE)
            {
                break;
            }
        }
    }

    if (g_jpeg_status & JPEG_DECODE_STATUS_ERROR)
    {
        Error = 1;
    }

    //
    // De-Init
    //
    R_JPEG_Decode_Close(_g_jpeg_emwin_decode->p_ctrl);

    GUI_UNLOCK();

    return Error;
}

#endif

/*************************** End of file ****************************/
