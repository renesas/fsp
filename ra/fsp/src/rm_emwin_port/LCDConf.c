#include <stdlib.h>
#include <string.h>

#include "GUI.h"
#include "WM.h"
#include "GUIDRV_Lin.h"
#include "LCDConf.h"

#if EMWIN_LCD_USE_DAVE
 #include "dave_driver.h"
 #if EMWIN_JPEG_USE_HW
  #include "JPEGConf.h"
 #endif
#endif

#include "r_glcdc.h"

#if EMWIN_CFG_RTOS == 2
 #include "FreeRTOS.h"
 #include "semphr.h"
#endif

/*********************************************************************
 *
 *       Configuration checking
 *
 **********************************************************************
 */
#ifndef   VRAM_ADDR
 #define VRAM_ADDR    (void *) _fb_emwin
#endif
#ifndef   EMWIN_LCD_XSIZE_PHYS
 #error Physical X size of display is not defined!
#endif
#ifndef   EMWIN_LCD_YSIZE_PHYS
 #error Physical Y size of display is not defined!
#endif
#ifndef   EMWIN_LCD_NUM_FRAMEBUFFERS
 #error Number of framebuffers is not defined!
#endif
#ifndef   EMWIN_LCD_COLOR_CONVERSION
 #error Color conversion not defined!
#endif
#ifndef   EMWIN_LCD_DISPLAY_DRIVER
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

#if EMWIN_LCD_USE_DAVE
extern d2_device ** _d2_handle_emwin;
#endif

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */
#if (EMWIN_LCD_NUM_FRAMEBUFFERS != 2)
static volatile int32_t _PendingBuffer = -1;
#endif

#if (EMWIN_LCD_BITS_PER_PIXEL <= 8)
 #define NUM_COLORS      (1 << EMWIN_LCD_BITS_PER_PIXEL)
#else
 #define NUM_COLORS      (256)
#endif

#if (EMWIN_CFG_RTOS == 2)              // FreeRTOS
 #if configSUPPORT_DYNAMIC_ALLOCATION
  #define EMWIN_ALLOC    pvPortMalloc
  #define EMWIN_FREE     vPortFree
 #else
  #define EMWIN_ALLOC    malloc
  #define EMWIN_FREE     free
 #endif
#else
 #define EMWIN_ALLOC     malloc
 #define EMWIN_FREE      free
#endif

//
// Framebuffer management
//
static uint32_t pp_buffer_address[EMWIN_LCD_NUM_FRAMEBUFFERS];

//
// Dave2D
//
#if EMWIN_LCD_USE_DAVE
static uint32_t          _WriteBufferIndex;
static d2_renderbuffer * renderbuffer;

//
// Array for swapped nibble data
//
static uint8_t glyph_mirror[EMWIN_LCD_AA_FONT_CONV_BUFFER_SIZE];

//
// Array for speeding up nibble conversion for A4 bitmaps
//
static const uint8_t lut_nibble_mirror[] =
{
    0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0,
    0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71, 0x81, 0x91, 0xA1, 0xB1, 0xC1, 0xD1, 0xE1, 0xF1,
    0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72, 0x82, 0x92, 0xA2, 0xB2, 0xC2, 0xD2, 0xE2, 0xF2,
    0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73, 0x83, 0x93, 0xA3, 0xB3, 0xC3, 0xD3, 0xE3, 0xF3,
    0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74, 0x84, 0x94, 0xA4, 0xB4, 0xC4, 0xD4, 0xE4, 0xF4,
    0x05, 0x15, 0x25, 0x35, 0x45, 0x55, 0x65, 0x75, 0x85, 0x95, 0xA5, 0xB5, 0xC5, 0xD5, 0xE5, 0xF5,
    0x06, 0x16, 0x26, 0x36, 0x46, 0x56, 0x66, 0x76, 0x86, 0x96, 0xA6, 0xB6, 0xC6, 0xD6, 0xE6, 0xF6,
    0x07, 0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xA7, 0xB7, 0xC7, 0xD7, 0xE7, 0xF7,
    0x08, 0x18, 0x28, 0x38, 0x48, 0x58, 0x68, 0x78, 0x88, 0x98, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8,
    0x09, 0x19, 0x29, 0x39, 0x49, 0x59, 0x69, 0x79, 0x89, 0x99, 0xA9, 0xB9, 0xC9, 0xD9, 0xE9, 0xF9,
    0x0A, 0x1A, 0x2A, 0x3A, 0x4A, 0x5A, 0x6A, 0x7A, 0x8A, 0x9A, 0xAA, 0xBA, 0xCA, 0xDA, 0xEA, 0xFA,
    0x0B, 0x1B, 0x2B, 0x3B, 0x4B, 0x5B, 0x6B, 0x7B, 0x8B, 0x9B, 0xAB, 0xBB, 0xCB, 0xDB, 0xEB, 0xFB,
    0x0C, 0x1C, 0x2C, 0x3C, 0x4C, 0x5C, 0x6C, 0x7C, 0x8C, 0x9C, 0xAC, 0xBC, 0xCC, 0xDC, 0xEC, 0xFC,
    0x0D, 0x1D, 0x2D, 0x3D, 0x4D, 0x5D, 0x6D, 0x7D, 0x8D, 0x9D, 0xAD, 0xBD, 0xCD, 0xDD, 0xED, 0xFD,
    0x0E, 0x1E, 0x2E, 0x3E, 0x4E, 0x5E, 0x6E, 0x7E, 0x8E, 0x9E, 0xAE, 0xBE, 0xCE, 0xDE, 0xEE, 0xFE,
    0x0F, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F, 0x6F, 0x7F, 0x8F, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFF,
};

//
// LUT for 4bpp fonts
//
static const uint32_t clut_i4[] =
{
    0x00FFFFFF, 0x10FFFFFF, 0x20FFFFFF, 0x30FFFFFF,
    0x40FFFFFF, 0x50FFFFFF, 0x60FFFFFF, 0x70FFFFFF,
    0x80FFFFFF, 0x90FFFFFF, 0xA0FFFFFF, 0xB0FFFFFF,
    0xC0FFFFFF, 0xD0FFFFFF, 0xE0FFFFFF, 0xF0FFFFFF
};

#endif

#if EMWIN_LCD_VSYNC_WAIT
 #if EMWIN_CFG_RTOS == 2               // FreeRTOS
//
// Semaphores
//
static SemaphoreHandle_t _SemaphoreVsync;
static StaticSemaphore_t _SemaphoreVsync_Memory;
 #else
static volatile uint8_t _vsync_flag = 0;
 #endif
#endif

//
// Function Prototypes
//
void   _DisplayVsyncCallback(display_callback_args_t * p_args);
void * LCDCONF_GetWriteBuffer(void);
void * LCDCONF_GetBufferAddr(void);

#if EMWIN_LCD_USE_DAVE
static uint32_t _GetD2Mode(void);
void            LCDCONF_DisableDave2D(void);
void            LCDCONF_EnableDave2D(void);

 #if EMWIN_JPEG_USE_HW
extern void JPEG_X_Init(void);
void        LCDCONF_DrawJPEG(int32_t      LayerIndex,
                             int32_t      x,
                             int32_t      y,
                             const void * p,
                             int32_t      xSize,
                             int32_t      ySize,
                             int32_t      BytesPerLine);

  #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT
void LCDCONF_FlushJPEG(void);

  #endif
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
#if EMWIN_LCD_VSYNC_WAIT
 #if EMWIN_CFG_RTOS == 2               // FreeRTOS
    BaseType_t context_switch;

    //
    // Set Vsync semaphore
    //
    xSemaphoreGiveFromISR(_SemaphoreVsync, &context_switch);

    //
    // Return to the highest priority available task
    //
    portYIELD_FROM_ISR(context_switch);
 #else
    _vsync_flag = 1;
 #endif
#endif
}

/*********************************************************************
 *
 *       _GraphicsHWInit
 */
static void _GraphicsHWInit (void)
{
#if EMWIN_LCD_USE_DAVE

    //
    // Initialize D/AVE 2D driver
    //
    *_d2_handle_emwin = d2_opendevice(0);
    d2_inithw(*_d2_handle_emwin, 0);

    //
    // Clear both buffers
    //
    d2_framebuffer(*_d2_handle_emwin,
                   _fb_emwin,
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS * EMWIN_LCD_NUM_FRAMEBUFFERS,
                   (d2_s32) _GetD2Mode());
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
 #if EMWIN_JPEG_USE_HW
    JPEG_X_Init();
 #endif
#endif

#if EMWIN_LCD_VSYNC_WAIT
 #if EMWIN_CFG_RTOS == 2               // FreeRTOS
    //
    // Initialize LCD controller semaphore
    //
    _SemaphoreVsync = xSemaphoreCreateBinaryStatic(&_SemaphoreVsync_Memory);
 #endif
#endif

    //
    // Start graphics LCD controller
    //
    R_GLCDC_Open(_g_display_emwin->p_ctrl, _g_display_emwin->p_cfg);
    R_GLCDC_Start(_g_display_emwin->p_ctrl);
}

/*********************************************************************
 *
 *       _GraphicsHWDeInit
 */
static void _GraphicsHWDeInit (void)
{
    //
    // Stop graphics LCD controller
    //
    while (FSP_SUCCESS != R_GLCDC_Stop(_g_display_emwin->p_ctrl))
    {
        /* Wait for GLCDC register update to complete before closing driver. */
    }

    R_GLCDC_Close(_g_display_emwin->p_ctrl);

#if EMWIN_LCD_USE_DAVE

    //
    // Deinitialize D/AVE 2D driver
    //
    d2_freerenderbuffer(*_d2_handle_emwin, renderbuffer);
    d2_deinithw(*_d2_handle_emwin);
    d2_closedevice(*_d2_handle_emwin);
#endif
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
#if (EMWIN_LCD_BITS_PER_PIXEL < 16)

    /* Set GLCDC CLUT entry */
    R_GLCDC_ClutEdit(_g_display_emwin->p_ctrl, DISPLAY_FRAME_LAYER_1, Pos, Color);
#else
    GUI_USE_PARA(Color);
    GUI_USE_PARA(Pos);
#endif
}

#if (EMWIN_LCD_NUM_FRAMEBUFFERS == 2)

static void vsync_wait (void)
{
 #if EMWIN_LCD_VSYNC_WAIT
  #if EMWIN_CFG_RTOS == 2              // FreeRTOS
    //
    // If Vsync semaphore has already been set, clear it then wait to avoid tearing
    //
    if (uxSemaphoreGetCount(_SemaphoreVsync))
    {
        xSemaphoreTake(_SemaphoreVsync, 10);
    }

    xSemaphoreTake(_SemaphoreVsync, portMAX_DELAY);
  #else
    _vsync_flag = 0;
    while (!_vsync_flag)
    {
        /* Do nothing. */
    }
  #endif
 #endif
}

/*********************************************************************
 *
 *       _SwitchBuffersOnVSYNC
 */
static void _SwitchBuffersOnVSYNC (int32_t Index)
{
    //
    // Swap buffer
    //
    fsp_err_t err;
    do
    {
        err =
            R_GLCDC_BufferChange(_g_display_emwin->p_ctrl,
                                 (uint8_t *) pp_buffer_address[Index],
                                 (display_frame_layer_t) 0);
        if (err)
        {
            vsync_wait();
        }
    } while (FSP_ERR_INVALID_UPDATE_TIMING == err);

    GUI_MULTIBUF_ConfirmEx(0, Index);  // Tell emWin that buffer is used

    vsync_wait();
}

#endif

/*********************************************************************
 *
 *       Dave2D related code
 *
 **********************************************************************
 */

#if EMWIN_LCD_USE_DAVE && (EMWIN_LCD_BITS_PER_PIXEL > 8)

/*********************************************************************
 *
 *       _GetD2Mode
 */
static uint32_t _GetD2Mode (void)
{
    uint32_t r;
 #if   (EMWIN_LCD_BITS_PER_PIXEL == 32)
    r = d2_mode_argb8888;
 #elif defined(DISPLAY_IN_FORMAT_16BITS_ARGB4444_0)
    r = d2_mode_argb4444;
 #else
    r = d2_mode_rgb565;
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
    const GUI_RECT * pRect;
    int32_t          xSize;
    int32_t          ySize;

    GUI_USE_PARA(LayerIndex);
    Mode = _GetD2Mode();

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    d2_setcolor(*_d2_handle_emwin, 0, GUI_Index2Color((int) PixelIndex));
    d2_setalpha(*_d2_handle_emwin, GUI_GetAlpha());
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
    d2_setalpha(*_d2_handle_emwin, UINT8_MAX);
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
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
                   (d2_s32) Mode);

 #if BSP_CFG_DCACHE_ENABLED

    //
    // Clean cache to ensure subsequent CPU alpha blending operations are correct
    //
    SCB_CleanInvalidateDCache();
 #endif
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
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   (d2_s32) EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
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

 #if BSP_CFG_DCACHE_ENABLED

    //
    // If the Data Cache is enabled invalidate the drawn area
    //
    uint32_t * p_start =
        (uint32_t *) ((uint16_t *) (pp_buffer_address[_WriteBufferIndex]) +
                      ((((uint32_t) y * EMWIN_LCD_XSTRIDE_PHYS) + (uint32_t) x)));
    int32_t size_bytes =
        (int32_t) ((((uint32_t) (ySize - 1) * EMWIN_LCD_XSTRIDE_PHYS) + (uint32_t) xSize) <<
                   (EMWIN_LCD_BITS_PER_PIXEL >> 3));
    SCB_CleanInvalidateDCache_by_Addr(p_start, size_bytes);
 #endif
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
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
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

 #if BSP_CFG_DCACHE_ENABLED

    //
    // If the Data Cache is enabled invalidate the drawn area
    //
    uint32_t * p_start =
        (uint32_t *) ((uint16_t *) (pp_buffer_address[_WriteBufferIndex]) +
                      ((((uint32_t) y * EMWIN_LCD_XSTRIDE_PHYS) + (uint32_t) x)));
    int32_t size_bytes =
        (int32_t) ((((uint32_t) (ySize - 1) * EMWIN_LCD_XSTRIDE_PHYS) + (uint32_t) xSize) <<
                   (EMWIN_LCD_BITS_PER_PIXEL >> 3));
    SCB_CleanInvalidateDCache_by_Addr(p_start, size_bytes);
 #endif
}

/*********************************************************************
 *
 *       _CompactPixelIndices
 */
static void _CompactPixelIndices (LCD_PIXELINDEX * pBuffer, uint32_t NumPixels, int BitsPerPixel)
{
    if (BitsPerPixel <= 8)
    {
        uint8_t * pDest;
        pDest = (uint8_t *) pBuffer;
        for (uint32_t i = 0; i < NumPixels; i++)
        {
            pDest[i] = (uint8_t) pBuffer[i];
        }
    }
    else if (BitsPerPixel <= 16)
    {
        uint16_t * pDest;
        pDest = (uint16_t *) pBuffer;
        for (uint32_t i = 0; i < NumPixels; i++)
        {
            pDest[i] = (uint16_t) pBuffer[i];
        }
    }
    else
    {
        /* Do nothing. */
    }
}

/*********************************************************************
 *
 *       _DrawBitmap8bpp
 */
static void _DrawBitmap8bpp (int                    LayerIndex,
                             int                    x,
                             int                    y,
                             const void           * p,
                             int                    xSize,
                             int                    ySize,
                             int                    BytesPerLine,
                             const LCD_PIXELINDEX * pTrans)
{
    uint32_t         Mode;
    uint32_t         ModeSrc;
    uint32_t         NumEntries;
    const GUI_RECT * pRect;

    GUI_USE_PARA(LayerIndex);
    GUI_USE_PARA(BytesPerLine);
    Mode       = _GetD2Mode();
    ModeSrc    = d2_mode_i8 | d2_mode_clut;
    NumEntries = NUM_COLORS;

    _CompactPixelIndices((LCD_PIXELINDEX *) pTrans, NumEntries, EMWIN_LCD_BITS_PER_PIXEL);

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    pRect = GUI_GetClipRect();
    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
    d2_setblitsrc(*_d2_handle_emwin, (void *) p, BytesPerLine, xSize, ySize, ModeSrc);
    d2_settexclut_format(*_d2_handle_emwin, Mode);
    d2_settexclut(*_d2_handle_emwin, (d2_color *) pTrans);
    d2_blitcopy(*_d2_handle_emwin, xSize, ySize, 0, 0, (d2_width) (xSize << 4), (d2_width) (ySize << 4),
                (d2_point) (x << 4), (d2_point) (y << 4), 0);

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);
}

/*********************************************************************
 *
 *       _DrawChar4bpp
 */
static int _DrawChar4bpp (int LayerIndex, int x, int y, U8 const * p, int xSize, int ySize, int BytesPerLine)
{
    uint32_t         Mode;
    d2_color         Color;
    const GUI_RECT * pRect;
    uint32_t         NumBytes;
    uint8_t        * pRD;
    uint8_t        * pWR;
    int              ret;

    FSP_PARAMETER_NOT_USED(LayerIndex);

    pRect = GUI_GetClipRect();

    //
    // Check size of conversion buffer
    //
    NumBytes = ((((uint32_t) xSize + 1U) & (uint32_t) ~1U) * (uint32_t) ySize) >> 1U;
    if ((NumBytes > sizeof(glyph_mirror)) || (NumBytes == 0))
    {
        return 1;
    }

    //
    // Swap nibbles
    //
    pWR = (uint8_t *) glyph_mirror;
    pRD = (uint8_t *) p;
    for (uint32_t i = 0; i < NumBytes; i++)
    {
        pWR[i] = lut_nibble_mirror[pRD[i]];
    }

    Mode = _GetD2Mode();

    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);

    Color = GUI_GetColor();
    d2_setcolor(*_d2_handle_emwin, 0, Color);

    /* Set D2 driver to replace RGB channels, preserving only alpha */
    d2_settextureoperation(*_d2_handle_emwin, d2_to_copy, d2_to_replace, d2_to_replace, d2_to_replace);
    d2_settexopparam(*_d2_handle_emwin, d2_cc_red, Color >> 16, 0);
    d2_settexopparam(*_d2_handle_emwin, d2_cc_green, (Color & 0x0000FF00) >> 8, 0);
    d2_settexopparam(*_d2_handle_emwin, d2_cc_blue, Color & 0x000000FF, 0);

    /* Set the graphics fill mode to use texture mapped data */
    d2_u8 prevfillmode = d2_getfillmode(*_d2_handle_emwin);
    d2_setfillmode(*_d2_handle_emwin, d2_fm_texture);

    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);

    /* Set texture buffer in D2 driver and assign CLUT */
    d2_settexclut_format(*_d2_handle_emwin, d2_mode_i4);
    d2_settexture(*_d2_handle_emwin, (void *) glyph_mirror, BytesPerLine * 2, xSize, ySize, d2_mode_i4 | d2_mode_clut);
    d2_settexclut(*_d2_handle_emwin, (d2_color *) clut_i4);

    /* Set texture mapping for the following:
     *   - Map on the display starting at x, y
     *   - Start in the texture at 0, 0 (each char his its own texture)
     *   - For each pixel in the X and Y direction on the display move exactly one pixel in the respective
     *     direction in the texture
     */
    d2_settexturemapping(*_d2_handle_emwin,
                         (d2_point) (x << 4),
                         (d2_point) (y << 4),
                         (0 << 16),
                         (0 << 16),
                         (1 << 16),
                         0,
                         0,
                         (1 << 16));

    /* Render a box the size of the character (it will be filled with the texture based on the configured
     *   parameters)
     */
    ret = d2_renderbox(*_d2_handle_emwin,
                       (d2_point) (x << 4),
                       (d2_point) (y << 4),
                       (d2_width) (xSize << 4),
                       (d2_width) (ySize << 4));

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);

    /* Revert fill mode */
    d2_setfillmode(*_d2_handle_emwin, prevfillmode);

    return ret;
}

 #if EMWIN_JPEG_USE_HW

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
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);

    const GUI_RECT * pRect = GUI__GetClipRect();
    d2_cliprect(*_d2_handle_emwin, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
    d2_setblitsrc(*_d2_handle_emwin, (void *) p, xSize, xSize, ySize, ModeSrc);
    d2_blitcopy(*_d2_handle_emwin, xSize, ySize, 0, 0, (d2_width) (xSize << 4), (d2_width) (ySize << 4),
                (d2_point) (x << 4), (d2_point) (y << 4), 0);

    //
    // In double-buffered mode only wait if DRW is busy before executing a new render buffer
    //
  #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT
    d2_flushframe(*_d2_handle_emwin);
  #endif

    //
    // Execute render operations
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);

    //
    // In single-buffered mode always wait for DRW to finish before returning
    //
  #if !(EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT)
    d2_flushframe(*_d2_handle_emwin);
  #endif
}

  #if EMWIN_JPEG_DOUBLE_BUFFER_OUTPUT

/*********************************************************************
 *
 *       LCDCONF_FlushJPEG
 */
void LCDCONF_FlushJPEG (void)
{
    //
    // Wait for DRW operation to finish
    //
    d2_flushframe(*_d2_handle_emwin);
}

  #endif

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
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
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
    pData = EMWIN_ALLOC(sizeof(d2_point) * (uint32_t) NumPoints * 2);

    ret = 1;
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
                       (void *) pp_buffer_address[_WriteBufferIndex],
                       EMWIN_LCD_XSTRIDE_PHYS,
                       EMWIN_LCD_XSIZE_PHYS,
                       EMWIN_LCD_YSIZE_PHYS,
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
        EMWIN_FREE(pData);
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
    pData = EMWIN_ALLOC(sizeof(d2_point) * (uint32_t) NumPoints * 2);

    ret = 1;
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
                       (void *) pp_buffer_address[_WriteBufferIndex],
                       EMWIN_LCD_XSTRIDE_PHYS,
                       EMWIN_LCD_XSIZE_PHYS,
                       EMWIN_LCD_YSIZE_PHYS,
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
        EMWIN_FREE(pData);
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
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
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
static int _DrawArcAA (int x0, int y0, int rx, int ry, long a0, long a1)
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
    U32              Flag;

    GUI_USE_PARA(ry);

    //
    // If both angles are equal (e.g. 0 and 0 or 180 and 180) nothing has to be done
    //
    if (a0 == a1)
    {
        return 0;                      // Nothing to do, no angle - no arc
    }

    if (a1 < a0)
    {
        return 0;                      // Nothing to do, emWin doesn't support this one
    }

    //
    // If the angles not equal, but meet at the same position
    // we don't draw an arc but a circle instead.
    //
    if (a1 > (a0 + 360000))
    {
        return _DrawCircleAA(x0, y0, rx); // a1 meets a0 after one round so we have a circle
    }

    if ((a0 % 360000) == (a1 % 360000))
    {
        return _DrawCircleAA(x0, y0, rx); // Both angles are at the same position but not equal, so we have a circle
    }

    PenSize = GUI_GetPenSize();
    Mode    = _GetD2Mode();

    nx0 = -GUI__SinHQ(a0);
    ny0 = -GUI__CosHQ(a0);
    nx1 = GUI__SinHQ(a1);
    ny1 = GUI__CosHQ(a1);

    //
    // If the difference between both is larger than 180 degrees we must use the concave flag
    //
    if (((a1 - a0) % 360000) <= 180000)
    {
        Flag = 0;
    }
    else
    {
        Flag = d2_wf_concave;
    }

    //
    // Generate render operations
    //
    d2_framebuffer(*_d2_handle_emwin,
                   (void *) pp_buffer_address[_WriteBufferIndex],
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
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
                         Flag);

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
    void   * pDst;
    void   * pSrc;
    uint32_t Mode;

    GUI_USE_PARA(LayerIndex);
    pSrc = (void *) pp_buffer_address[IndexSrc];
    pDst = (void *) pp_buffer_address[IndexDst];

    Mode = _GetD2Mode();

    //
    // Set up blit operation
    //
    d2_framebuffer(*_d2_handle_emwin,
                   pDst,
                   EMWIN_LCD_XSTRIDE_PHYS,
                   EMWIN_LCD_XSIZE_PHYS,
                   EMWIN_LCD_YSIZE_PHYS,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(*_d2_handle_emwin, renderbuffer);
    d2_setblitsrc(*_d2_handle_emwin, pSrc, EMWIN_LCD_XSTRIDE_PHYS, EMWIN_LCD_XSIZE_PHYS, EMWIN_LCD_YSIZE_PHYS, Mode);
    d2_blitcopy(*_d2_handle_emwin, EMWIN_LCD_XSIZE_PHYS, EMWIN_LCD_YSIZE_PHYS, 0, 0,
                (d2_width) (EMWIN_LCD_XSIZE_PHYS << 4), (d2_width) (EMWIN_LCD_YSIZE_PHYS << 4), 0, 0, 0);

    //
    // Execute blit
    //
    d2_executerenderbuffer(*_d2_handle_emwin, renderbuffer, 0);
    d2_flushframe(*_d2_handle_emwin);

    _WriteBufferIndex = (uint32_t) IndexDst;
}

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       LCDCONF_EnableDave2D
 */
void LCDCONF_EnableDave2D (void)
{
    /* D/AVE 2D does not support output to LUT formats */
 #if (EMWIN_LCD_BITS_PER_PIXEL > 8)
    GUI_SetFuncDrawAlpha(_DrawMemdevAlpha, _DrawBitmapAlpha);
    GUI_SetFuncDrawM565(_DrawMemdevAlpha, _DrawBitmapAlpha);
    LCD_SetDevFunc(0, LCD_DEVFUNC_DRAWBMP_16BPP, (void (*)(void))_DrawBitmap16bpp);
    LCD_SetDevFunc(0, LCD_DEVFUNC_DRAWBMP_8BPP, (void (*)(void))_DrawBitmap8bpp);
    GUI_AA_SetFuncFillCircle(_FillCircleAA);
    GUI_AA_SetFuncFillPolygon(_FillPolygonAA);
    GUI_AA_SetFuncDrawCircle(_DrawCircleAA);
    GUI_AA_SetFuncDrawLine(_DrawLineAA);
    GUI_AA_SetFuncDrawPolyOutline(_DrawPolyOutlineAA);
    GUI_AA_SetFuncDrawArc(_DrawArcAA);
    GUI_AA_SetpfDrawCharAA4(_DrawChar4bpp);
    LCD_SetDevFunc(0, LCD_DEVFUNC_COPYBUFFER, (void (*)(void))_CopyBuffer);
    LCD_SetDevFunc(0, LCD_DEVFUNC_FILLRECT, (void (*)(void))_LCD_FillRect);
    GUI_AlphaEnableFillRectHW(1);
 #endif
}

/*********************************************************************
 *
 *       LCDCONF_DisableDave2D
 */
void LCDCONF_DisableDave2D (void)
{
    /* D/AVE 2D does not support output to LUT formats */
 #if (EMWIN_LCD_BITS_PER_PIXEL > 8)
    GUI_SetFuncDrawAlpha(NULL, NULL);
    GUI_SetFuncDrawM565(NULL, NULL);
    LCD_SetDevFunc(0, LCD_DEVFUNC_DRAWBMP_16BPP, NULL);
    LCD_SetDevFunc(0, LCD_DEVFUNC_DRAWBMP_8BPP, NULL);
    GUI_AA_SetFuncFillCircle(NULL);
    GUI_AA_SetFuncFillPolygon(NULL);
    GUI_AA_SetFuncDrawCircle(NULL);
    GUI_AA_SetFuncDrawLine(NULL);
    GUI_AA_SetFuncDrawPolyOutline(NULL);
    GUI_AA_SetFuncDrawArc(NULL);
    GUI_AA_SetpfDrawCharAA4(NULL);
    LCD_SetDevFunc(0, LCD_DEVFUNC_COPYBUFFER, (void (*)(void))NULL);
    LCD_SetDevFunc(0, LCD_DEVFUNC_FILLRECT, (void (*)(void))NULL);
    GUI_AlphaEnableFillRectHW(0);
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
    // Set framebuffer pointer
    //
    _fb_emwin = EMWIN_LCD_FRAMEBUFFER_PTR;

    //
    // Initialize graphics HW
    //
    _GraphicsHWInit();

    //
    // Set graphics HW deinit callback for GUI_Exit
    //
    static GUI_REGISTER_EXIT RegisterExit;
    RegisterExit.pfVoid = _GraphicsHWDeInit;
    GUI__RegisterExit(&RegisterExit);

#if (EMWIN_LCD_NUM_FRAMEBUFFERS > 1)

    //
    // Enable multibuffering
    //
    GUI_MULTIBUF_ConfigEx(0, EMWIN_LCD_NUM_FRAMEBUFFERS);
    WM_MULTIBUF_Enable(1);
#endif

    //
    // Set display driver and color conversion for 1st layer
    //
    GUI_DEVICE_CreateAndLink(EMWIN_LCD_DISPLAY_DRIVER, EMWIN_LCD_COLOR_CONVERSION, 0, 0);

    //
    // Display driver configuration
    //
    if (LCD_GetSwapXY())
    {
        LCD_SetSizeEx(0, EMWIN_LCD_YSIZE_PHYS, EMWIN_LCD_XSIZE_PHYS);
        LCD_SetVSizeEx(0, EMWIN_LCD_YSIZE_PHYS, EMWIN_LCD_XSIZE_PHYS);
    }
    else
    {
        LCD_SetSizeEx(0, EMWIN_LCD_XSIZE_PHYS, EMWIN_LCD_YSIZE_PHYS);
        LCD_SetVSizeEx(0, EMWIN_LCD_XSTRIDE_PHYS, EMWIN_LCD_YSIZE_PHYS);
    }

    LCD_SetVRAMAddrEx(0, VRAM_ADDR);

    //
    // Set user palette data (only required if no fixed palette is used)
    //
#if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
#endif

#if EMWIN_LCD_USE_DAVE
    renderbuffer = d2_newrenderbuffer(*_d2_handle_emwin, 20, 20);
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
            //
            // Controller initialization is already done so we simply store the frame buffer addresses
            //
#if (EMWIN_LCD_NUM_FRAMEBUFFERS > 1)
            for (uint32_t i = 0; i < EMWIN_LCD_NUM_FRAMEBUFFERS; i++)
            {
                pp_buffer_address[i] = (uint32_t) _fb_emwin +
                                       (i *
                                        ((EMWIN_LCD_XSTRIDE_PHYS * EMWIN_LCD_YSIZE_PHYS * EMWIN_LCD_BITS_PER_PIXEL) >>
                                         3));
            }

#else
            pp_buffer_address[0] = (uint32_t) _fb_emwin;
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
#if (EMWIN_LCD_NUM_FRAMEBUFFERS > 1)
            _SwitchBuffersOnVSYNC(p->Index);
 #if (EMWIN_LCD_NUM_FRAMEBUFFERS > 2)
            _PendingBuffer = p->Index;
 #endif
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
