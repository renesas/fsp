#include "GUI.h"
#include "WM.h"
#include "GUIDRV_Lin.h"
#include "LCDConf.h"
#include "JPEGConf.h"

#include "r_glcdc.h"
#include "dave_driver.h"
#include "FreeRTOS.h"
#include "semphr.h"

#include <stdlib.h>
#include <string.h>

/*********************************************************************
 *
 *       Configuration checking
 *
 **********************************************************************
 */
#ifndef   VRAM_ADDR
 #define VRAM_ADDR    (void *) _fb_emwin
#endif
#ifndef   XSIZE_PHYS
 #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
 #error Physical Y size of display is not defined!
#endif
#ifndef   NUM_BUFFERS
 #error Number of framebuffers is not defined!
#endif
#ifndef   COLOR_CONVERSION
 #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
 #error No display driver defined!
#endif

/*********************************************************************
 *
 *       Extern data
 *
 **********************************************************************
 */
extern const display_instance_t * _g_display_emwin;
extern uint8_t * _fb_emwin;

#if EMWIN_USE_DAVE
extern d2_device ** _d2_handle_emwin;
#endif

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */
#if (NUM_BUFFERS != 2)
static volatile int32_t _PendingBuffer = -1;
#endif

//
// Dave2D
//
static uint32_t _WriteBufferIndex;

#if EMWIN_USE_DAVE
static d2_renderbuffer * renderbuffer;
static uint32_t          _FB_BufferSize;
static uint32_t          _aBufferAddress[NUM_BUFFERS];
#endif

//
// Semaphores
//
static SemaphoreHandle_t _SemaphoreVsync;
static StaticSemaphore_t _SemaphoreVsync_Memory;

//
// Function Prototypes
//
void   _DisplayVsyncCallback(display_callback_args_t * p_args);
void * LCDCONF_GetWriteBuffer(void);
void * LCDCONF_GetBufferAddr(void);

#if EMWIN_USE_DAVE
void LCDCONF_DisableDave2D(void);
void LCDCONF_EnableDave2D(void);

 #if EMWIN_USE_JPEG_HW
extern void JPEG_X_Init(JPEG_X_CONTEXT * pContext);
void        LCDCONF_DrawJPEG(int32_t      LayerIndex,
                             int32_t      x,
                             int32_t      y,
                             const void * p,
                             int32_t      xSize,
                             int32_t      ySize,
                             int32_t      BytesPerLine);

 #endif
#endif

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       _DisplayVsyncCallback
 */
void _DisplayVsyncCallback (display_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    BaseType_t context_switch;

    //
    // Set Vsync semaphore
    //
    xSemaphoreGiveFromISR(_SemaphoreVsync, &context_switch);

    //
    // Return to the highest priority available task
    //
    portYIELD_FROM_ISR(context_switch);
}

/*********************************************************************
 *
 *       _GraphicsHWInit
 */
static void _GraphicsHWInit (void)
{
#if EMWIN_USE_DAVE

    //
    // Initialize D/AVE 2D driver
    //
    *_d2_handle_emwin = d2_opendevice(0);
    d2_inithw(*_d2_handle_emwin, 0);

    //
    // Clear both buffers
    //
    d2_framebuffer(*_d2_handle_emwin, _fb_emwin, XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS * NUM_BUFFERS, d2_mode_rgb565);
    d2_clear(*_d2_handle_emwin, 0x000000);

    //
    // Set various D2 parameters
    //
    d2_setblendmode(*_d2_handle_emwin, d2_bm_alpha, d2_bm_one_minus_alpha);
    d2_setalphamode(*_d2_handle_emwin, d2_am_constant);
    d2_setalpha(*_d2_handle_emwin, UINT8_MAX);
    d2_setantialiasing(*_d2_handle_emwin, 1);
    d2_setlinecap(*_d2_handle_emwin, d2_lc_butt);
    d2_setlinejoin(*_d2_handle_emwin, d2_lj_miter);

    //
    // Initialize JPEG Codec
    //
 #if EMWIN_USE_JPEG_HW
    JPEG_X_Init(NULL);
 #endif
#endif

    //
    // Initialize LCD controller semaphore
    //
    _SemaphoreVsync = xSemaphoreCreateBinaryStatic(&_SemaphoreVsync_Memory);

    //
    // Start graphics LCD controller
    //
    R_GLCDC_Open(_g_display_emwin->p_ctrl, _g_display_emwin->p_cfg);
    R_GLCDC_Start(_g_display_emwin->p_ctrl);
}

/*********************************************************************
 *
 *       _SetLUTEntry
 *
 * Purpose:
 *   Should set the desired LUT entry
 */
static void _SetLUTEntry (LCD_COLOR Color, uint8_t Pos)
{
    GUI_USE_PARA(Color);
    GUI_USE_PARA(Pos);
}

/*********************************************************************
 *
 *       _SwitchBuffersOnVSYNC
 */
#if (NUM_BUFFERS == 2)

static void _SwitchBuffersOnVSYNC (int32_t Index)
{
    xSemaphoreTake(_SemaphoreVsync, portMAX_DELAY);
    R_GLCDC_BufferChange(_g_display_emwin->p_ctrl,
                         _fb_emwin + (_WriteBufferIndex * XSIZE_PHYS * YSIZE_PHYS * BITS_PER_PIXEL / 8),
                         (display_frame_layer_t) 0);
    GUI_MULTIBUF_ConfirmEx(0, Index);  // Tell emWin that buffer is used
}

#endif

/*********************************************************************
 *
 *       Dave2D related code
 *
 **********************************************************************
 */

#if EMWIN_USE_DAVE

/*********************************************************************
 *
 *       _GetD2Mode
 */
static uint32_t _GetD2Mode (void)
{
    uint32_t r;
 #if   (BITS_PER_PIXEL == 32)
    r = d2_mode_argb8888;
 #elif (BITS_PER_PIXEL == 16)
    r = d2_mode_rgb565;
 #elif (BITS_PER_PIXEL == 8)
    r = d2_mode_i8;
 #elif (BITS_PER_PIXEL == 4)
    r = d2_mode_i4;
 #elif (BITS_PER_PIXEL == 1)
    r = d2_mode_i1;
 #endif

    return r;
}

/*********************************************************************
 *
 *       _LCD_FillRect
 */
static void _LCD_FillRect (int32_t LayerIndex, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t PixelIndex)
{
    uint32_t         Mode;
    d2_color         Color;
    const GUI_RECT * pRect;
    int32_t          xSize;
    int32_t          ySize;

    GUI_USE_PARA(LayerIndex);
    Mode = _GetD2Mode();

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin, (void *) _aBufferAddress[_WriteBufferIndex], XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    Color = GUI_Index2Color((int) PixelIndex);
    d2_setcolor(*_d2_handle_emwin, 0, Color);
    pRect = GUI__GetClipRect();
    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
    xSize = (x1 - x0) + 1;
    ySize = (y1 - y0) + 1;
    d2_renderbox(*_d2_handle_emwin, (d2_point) (x0 << 4), (d2_point) (y0 << 4), (d2_width) (xSize << 4),
                 (d2_width) (ySize << 4));

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);
}

/*********************************************************************
 *
 *       _DrawMemdevAlpha
 */
static void _DrawMemdevAlpha (void       * pDst,
                              const void * pSrc,
                              int          xSize,
                              int          ySize,
                              int          BytesPerLineDst,
                              int          BytesPerLineSrc)
{
    d2_u32 PitchSrc;
    d2_u32 PitchDst;
    d2_u32 Mode;

    PitchDst = (d2_u32) (BytesPerLineDst / 4);
    PitchSrc = (d2_u32) (BytesPerLineSrc / 4);
    Mode     = _GetD2Mode();

    //
    // Set address of destination memory device as frame buffer to be used
    //
    d2_framebuffer(*_d2_handle_emwin, pDst, (d2_s32) PitchDst, PitchDst, (d2_u32) ySize, d2_mode_argb8888);

    //
    // Generate render operations
    //
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    d2_setblitsrc(*_d2_handle_emwin, (void *) pSrc, (d2_s32) PitchSrc, xSize, ySize, d2_mode_argb8888);
    d2_blitcopy(*_d2_handle_emwin,
                xSize,
                ySize,
                0,
                0,
                (d2_width) (xSize << 4),
                (d2_width) (ySize << 4),
                0,
                0,
                d2_bf_usealpha);

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);

    //
    // Restore frame buffer
    //
    d2_framebuffer(*_d2_handle_emwin, (void *) _aBufferAddress[_WriteBufferIndex], XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS,
                   (d2_s32) Mode);
}

/*********************************************************************
 *
 *       _DrawBitmapAlpha
 */
static void _DrawBitmapAlpha (int LayerIndex, int x, int y, const void * p, int xSize, int ySize, int BytesPerLine)
{
    uint32_t Mode;

    GUI_USE_PARA(LayerIndex);
    Mode = _GetD2Mode();

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) _aBufferAddress[_WriteBufferIndex],
                   (d2_s32) XSIZE_PHYS,
                   XSIZE_PHYS,
                   YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    d2_setblitsrc(*_d2_handle_emwin, (void *) p, BytesPerLine / 4, xSize, ySize, d2_mode_argb8888);
    d2_blitcopy(*_d2_handle_emwin, xSize, ySize, 0, 0, (d2_width) (xSize << 4), (d2_width) (ySize << 4),
                (d2_point) (x << 4), (d2_point) (y << 4), d2_bf_usealpha);

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);
}

/*********************************************************************
 *
 *       _DrawBitmap16bpp
 */
static void _DrawBitmap16bpp (int LayerIndex, int x, int y, const void * p, int xSize, int ySize, int BytesPerLine)
{
    uint32_t Mode;
    uint32_t ModeSrc;

    GUI_USE_PARA(LayerIndex);
    GUI_USE_PARA(BytesPerLine);
    Mode    = _GetD2Mode();
    ModeSrc = d2_mode_rgb565;

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin, (void *) _aBufferAddress[_WriteBufferIndex], XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    d2_setblitsrc(*_d2_handle_emwin, (void *) p, BytesPerLine / 2, xSize, ySize, ModeSrc);
    d2_blitcopy(*_d2_handle_emwin, xSize, ySize, 0, 0, (d2_width) (xSize << 4), (d2_width) (ySize << 4),
                (d2_point) (x << 4), (d2_point) (y << 4), 0);

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);
}

 #if EMWIN_USE_JPEG_HW

/*********************************************************************
 *
 *       LCDCONF_DrawJPEG
 */
void LCDCONF_DrawJPEG (int32_t      LayerIndex,
                       int32_t      x,
                       int32_t      y,
                       const void * p,
                       int32_t      xSize,
                       int32_t      ySize,
                       int32_t      BytesPerLine)
{
    uint32_t Mode;
    uint32_t ModeSrc;

    GUI_USE_PARA(LayerIndex);
    GUI_USE_PARA(BytesPerLine);
    Mode    = _GetD2Mode();
    ModeSrc = ((BytesPerLine / xSize) == 2) ? d2_mode_rgb565 : d2_mode_argb8888;

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin, (void *) _aBufferAddress[_WriteBufferIndex], XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);

    const GUI_RECT * pRect = GUI__GetClipRect();
    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
    d2_setblitsrc(*_d2_handle_emwin, (void *) p, xSize, xSize, ySize, ModeSrc);
    d2_blitcopy(*_d2_handle_emwin, xSize, ySize, 0, 0, (d2_width) (xSize << 4), (d2_width) (ySize << 4),
                (d2_point) (x << 4), (d2_point) (y << 4), 0);

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);
}

 #endif

/*********************************************************************
 *
 *       _CircleAA
 */
static int32_t _CircleAA (int32_t x0, int32_t y0, int32_t r, int32_t w)
{
    uint32_t         Mode;
    int32_t          ret;
    d2_color         Color;
    const GUI_RECT * pRect;

    Mode = _GetD2Mode();

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin, (void *) _aBufferAddress[_WriteBufferIndex], XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    Color = GUI_GetColor();
    d2_setcolor(*_d2_handle_emwin, 0, Color);
    pRect = GUI__GetClipRect();
    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
    ret = d2_rendercircle(*_d2_handle_emwin,
                          (d2_point) (x0 << 4),
                          (d2_point) (y0 << 4),
                          (d2_width) (r << 4),
                          (d2_width) (w << 4));

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);
    while (d2_commandspending(*_d2_handle_emwin))
    {
        /* Do nothing */
    }

    return ret;
}

/*********************************************************************
 *
 *       _FillCircleAA
 */
static int _FillCircleAA (int x0, int y0, int r)
{
    return _CircleAA(x0, y0, r, 0);
}

/*********************************************************************
 *
 *       _DrawCircleAA
 */
static int _DrawCircleAA (int x0, int y0, int r)
{
    uint16_t PenSize;

    PenSize = GUI_GetPenSize();

    return _CircleAA(x0, y0, r, PenSize);
}

/*********************************************************************
 *
 *       _FillPolygonAA
 */
static int _FillPolygonAA (const GUI_POINT * pPoints, int NumPoints, int x0, int y0)
{
    uint32_t         Mode;
    d2_point       * pData;
    d2_point       * pDataI;
    int32_t          i;
    int32_t          ret;
    d2_color         Color;
    const GUI_RECT * pRect;

    Mode  = _GetD2Mode();
    pData = malloc(sizeof(d2_point) * (uint32_t) NumPoints * 2);
    ret   = 1;
    if (pData)
    {
        pDataI = pData;
        for (i = 0; i < NumPoints; i++)
        {
            *pDataI++ = (d2_point) ((pPoints->x + x0) << 4);
            *pDataI++ = (d2_point) ((pPoints->y + y0) << 4);
            pPoints++;
        }

        //
        // Generate render operations
        //
        d2_framebuffer(*_d2_handle_emwin,
                       (void *) _aBufferAddress[_WriteBufferIndex],
                       XSIZE_PHYS,
                       XSIZE_PHYS,
                       YSIZE_PHYS,
                       (d2_s32) Mode);
        d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
        Color = GUI_GetColor();
        d2_setcolor(*_d2_handle_emwin, 0, Color);
        pRect = GUI__GetClipRect();
        d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
        ret = d2_renderpolygon(*_d2_handle_emwin, pData, (d2_u32) NumPoints, d2_le_closed);

        //
        // Execute render operations
        //
        d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
        d2_flushframe(*_d2_handle_emwin);
        free(pData);
    }

    return ret;
}

/*********************************************************************
 *
 *       _DrawPolyOutlineAA
 */
static int _DrawPolyOutlineAA (const GUI_POINT * pPoints, int NumPoints, int Thickness, int x, int y)
{
    uint32_t         Mode;
    d2_point       * pData;
    d2_point       * pDataI;
    int32_t          i;
    int32_t          ret;
    d2_color         Color;
    const GUI_RECT * pRect;

    Mode  = _GetD2Mode();
    pData = malloc(sizeof(d2_point) * (uint32_t) NumPoints * 2);
    ret   = 1;
    if (pData)
    {
        pDataI = pData;
        for (i = 0; i < NumPoints; i++)
        {
            *pDataI++ = (d2_point) ((pPoints->x + x) << 4);
            *pDataI++ = (d2_point) ((pPoints->y + y) << 4);
            pPoints++;
        }

        //
        // Generate render operations
        //
        d2_framebuffer(*_d2_handle_emwin,
                       (void *) _aBufferAddress[_WriteBufferIndex],
                       XSIZE_PHYS,
                       XSIZE_PHYS,
                       YSIZE_PHYS,
                       (d2_s32) Mode);
        d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
        Color = GUI_GetColor();
        d2_setcolor(*_d2_handle_emwin, 0, Color);
        pRect = GUI__GetClipRect();
        d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
        d2_selectrendermode(*_d2_handle_emwin, d2_rm_outline);
        ret =
            d2_renderpolyline(*_d2_handle_emwin, pData, (d2_u32) NumPoints, (d2_width) (Thickness << 4), d2_le_closed);
        d2_selectrendermode(*_d2_handle_emwin, d2_rm_solid);

        //
        // Execute render operations
        //
        d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
        d2_flushframe(*_d2_handle_emwin);
        free(pData);
    }

    return ret;
}

/*********************************************************************
 *
 *       _DrawLineAA
 */
static int _DrawLineAA (int x0, int y0, int x1, int y1)
{
    uint32_t         Mode;
    int32_t          ret;
    d2_color         Color;
    const GUI_RECT * pRect;
    uint16_t         PenSize;

    Mode    = _GetD2Mode();
    PenSize = GUI_GetPenSize();

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin, (void *) _aBufferAddress[_WriteBufferIndex], XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    Color = GUI_GetColor();
    d2_setcolor(*_d2_handle_emwin, 0, Color);
    pRect = GUI__GetClipRect();
    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
    ret =
        d2_renderline(*_d2_handle_emwin, (d2_point) (x0 << 4), (d2_point) (y0 << 4), (d2_point) (x1 << 4),
                      (d2_point) (y1 << 4), (d2_width) (PenSize << 4), d2_le_exclude_none);

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);

    return ret;
}

/*********************************************************************
 *
 *       _DrawArcAA
 */
static int _DrawArcAA (int x0, int y0, int rx, int ry, int a0, int a1)
{
    uint32_t         Mode;
    int32_t          ret;
    int32_t          nx0;
    int32_t          ny0;
    int32_t          nx1;
    int32_t          ny1;
    d2_color         Color;
    const GUI_RECT * pRect;
    uint16_t         PenSize;

    GUI_USE_PARA(ry);
    PenSize = GUI_GetPenSize();
    Mode    = _GetD2Mode();
    while (a1 < a0)
    {
        a1 += 360;
    }

    a0 *= 1000;
    a1 *= 1000;
    nx0 = GUI__SinHQ(a0);
    ny0 = GUI__CosHQ(a0);
    nx1 = GUI__SinHQ(a1);
    ny1 = GUI__CosHQ(a1);
    if ((a1 - a0) <= 180000)
    {
        nx0 *= -1;
        ny0 *= -1;
    }

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin, (void *) _aBufferAddress[_WriteBufferIndex], XSIZE_PHYS, XSIZE_PHYS, YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    Color = GUI_GetColor();
    d2_setcolor(*_d2_handle_emwin, 0, Color);
    pRect = GUI__GetClipRect();
    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
    ret = d2_renderwedge(*_d2_handle_emwin,
                         (d2_point) (x0 << 4),
                         (d2_point) (y0 << 4),
                         (d2_width) (rx << 4),
                         (d2_width) (PenSize << 4),
                         nx0,
                         ny0,
                         nx1,
                         ny1,
                         0);

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);

    return ret;
}

/*********************************************************************
 *
 *       _CopyBuffer
 */
static void _CopyBuffer (int LayerIndex, int IndexSrc, int IndexDst)
{
    void * pDst;
    void * pSrc;

    GUI_USE_PARA(LayerIndex);
    pSrc = (void *) _aBufferAddress[IndexSrc];
    pDst = (void *) _aBufferAddress[IndexDst];
    memcpy(pDst, pSrc, _FB_BufferSize);
    _WriteBufferIndex = (uint32_t) IndexDst;
}

#endif

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */

#if EMWIN_USE_DAVE

/*********************************************************************
 *
 *       LCDCONF_EnableDave2D
 */
void LCDCONF_EnableDave2D (void)
{
 #if (BITS_PER_PIXEL > 8)
    GUI_SetFuncDrawAlpha(_DrawMemdevAlpha, _DrawBitmapAlpha);
    GUI_SetFuncDrawM565(_DrawMemdevAlpha, _DrawBitmapAlpha);
    LCD_SetDevFunc(0, LCD_DEVFUNC_DRAWBMP_16BPP, (void (*)(void))_DrawBitmap16bpp);
    GUI_AA_SetFuncFillCircle(_FillCircleAA);
    GUI_AA_SetFuncFillPolygon(_FillPolygonAA);
    GUI_AA_SetFuncDrawCircle(_DrawCircleAA);
    GUI_AA_SetFuncDrawLine(_DrawLineAA);
    GUI_AA_SetFuncDrawPolyOutline(_DrawPolyOutlineAA);
    GUI_AA_SetFuncDrawArc(_DrawArcAA);
 #endif
}

/*********************************************************************
 *
 *       LCDCONF_DisableDave2D
 */
void LCDCONF_DisableDave2D (void)
{
 #if (BITS_PER_PIXEL > 8)
    GUI_SetFuncDrawAlpha(NULL, NULL);
    GUI_AA_SetFuncFillCircle(NULL);
    GUI_AA_SetFuncFillPolygon(NULL);
    GUI_AA_SetFuncDrawCircle(NULL);
    GUI_AA_SetFuncDrawLine(NULL);
    GUI_AA_SetFuncDrawPolyOutline(NULL);
    GUI_AA_SetFuncDrawArc(NULL);
 #endif
}

#endif

/*********************************************************************
 *
 *       LCD_X_Config
 *
 * Purpose:
 *   Called during the initialization process in order to set up the
 *   display driver configuration.
 *
 */
void LCD_X_Config (void)
{
    //
    // Initialize graphics HW
    //
    _GraphicsHWInit();

#if (NUM_BUFFERS > 1)

    //
    // Enable multibuffering
    //
    GUI_MULTIBUF_ConfigEx(0, NUM_BUFFERS);
    WM_MULTIBUF_Enable(1);
#endif

    //
    // Set display driver and color conversion for 1st layer
    //
    GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);

    //
    // Display driver configuration
    //
    if (LCD_GetSwapXY())
    {
        LCD_SetSizeEx(0, YSIZE_PHYS, XSIZE_PHYS);
        LCD_SetVSizeEx(0, YSIZE_PHYS, XSIZE_PHYS);
    }
    else
    {
        LCD_SetSizeEx(0, XSIZE_PHYS, YSIZE_PHYS);
        LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS);
    }

    LCD_SetVRAMAddrEx(0, VRAM_ADDR);

    //
    // Set user palette data (only required if no fixed palette is used)
    //
#if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
#endif

#if EMWIN_USE_DAVE
    renderbuffer = d2_newrenderbuffer(*_d2_handle_emwin, 20, 20);
    LCD_SetDevFunc(0, LCD_DEVFUNC_COPYBUFFER, (void (*)(void))_CopyBuffer);
    LCD_SetDevFunc(0, LCD_DEVFUNC_FILLRECT, (void (*)(void))_LCD_FillRect);
    LCDCONF_EnableDave2D();
#endif
}

/*********************************************************************
 *
 *       LCD_X_DisplayDriver
 *
 * Purpose:
 *   This function is called by the display driver for several purposes.
 *   To support the according task the routine needs to be adapted to
 *   the display controller. Please note that the commands marked with
 *   'optional' are not cogently required and should only be adapted if
 *   the display controller supports these features.
 *
 * Parameter:
 *   LayerIndex - Index of layer to be configured
 *   Cmd        - Please refer to the details in the switch statement below
 *   pData      - Pointer to a LCD_X_DATA structure
 *
 * Return Value:
 *   < -1 - Error
 *     -1 - Command not handled
 *      0 - Ok
 */
int LCD_X_DisplayDriver (unsigned LayerIndex, unsigned Cmd, void * pData)
{
    int32_t r;

    GUI_USE_PARA(LayerIndex);
    switch (Cmd)
    {
        //
        // Required
        //
        case LCD_X_INITCONTROLLER:
        {
#if EMWIN_USE_DAVE

            //
            // Controller initialization is already done so we simply store the frame buffer addresses
            //
            _FB_BufferSize     = ((XSIZE_PHYS * YSIZE_PHYS * BITS_PER_PIXEL) >> 3);
            _aBufferAddress[0] = (uint32_t) _fb_emwin;
 #if (NUM_BUFFERS > 1)
            _aBufferAddress[1] = (uint32_t) _fb_emwin + ((XSIZE_PHYS * YSIZE_PHYS * BITS_PER_PIXEL) >> 3);
 #endif
#endif

            return 0;
        }

        case LCD_X_SHOWBUFFER:
        {
            //
            // Required if multiple buffers are used. The 'Index' element of p contains the buffer index.
            //
            LCD_X_SHOWBUFFER_INFO * p;

            p = (LCD_X_SHOWBUFFER_INFO *) pData;
#if (NUM_BUFFERS == 2)
            _SwitchBuffersOnVSYNC(p->Index);
#else
            _PendingBuffer = p->Index;
#endif

            return 0;
        }

        case LCD_X_SETLUTENTRY:
        {
            //
            // Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p
            //
            LCD_X_SETLUTENTRY_INFO * p;
            p = (LCD_X_SETLUTENTRY_INFO *) pData;
            _SetLUTEntry(p->Color, p->Pos);

            return 0;
        }

        case LCD_X_ON:
        {
            //
            // Required if the display controller should support switching on and off
            //

            return 0;
        }

        case LCD_X_OFF:
        {
            //
            // Required if the display controller should support switching on and off
            //

            return 0;
        }

        default:
            r = -1;
    }

    return r;
}

/*************************** End of file ****************************/
