/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include    <stdio.h>
#include    <string.h>

#include    "gx_api.h"
#include    "gx_display.h"
#include    "gx_utility.h"

#if (GX_RENESAS_DAVE2D_DRAW == 1)
 #include    "dave_driver.h"
#endif
#if (GX_USE_RENESAS_JPEG == 1)
 #include    "r_jpeg.h"
#else
 #include    "bsp_api.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#ifndef GX_DISABLE_ERROR_CHECKING
 #define LOG_DAVE_ERRORS

/* Max number of error values we will keep */
 #define DAVE_ERROR_LIST_SIZE    (4)
#endif

/** Space used to store int to fixed point polygon vertices. */
#define MAX_POLYGON_VERTICES     GX_POLYGON_MAX_EDGE_NUM

#if defined(LOG_DAVE_ERRORS)

/** Macro to check for and log status code from Dave2D engine. */
 #define CHECK_DAVE_STATUS(a)    gx_log_dave_error(a);
#else

/* here is error logging not enabled */
 #define CHECK_DAVE_STATUS(a)    a;
#endif

/** Buffer alignment for JPEG draw */
#define JPEG_ALIGNMENT_8     (0x07U)
#define JPEG_ALIGNMENT_16    (0x0FU)
#define JPEG_ALIGNMENT_32    (0x1FU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if (GX_RENESAS_DAVE2D_DRAW == 1)

/** DAVE 2D screen rotation parameters */
typedef struct st_d2_rotation_param
{
    d2_border    xmin;
    d2_border    ymin;
    d2_border    xmax;
    d2_border    ymax;
    d2_point     x_texture_zero;
    d2_point     y_texture_zero;
    d2_s32       dxu;
    d2_s32       dxv;
    d2_s32       dyu;
    d2_s32       dyv;
    GX_VALUE     x_resolution;
    GX_VALUE     y_resolution;
    INT          copy_width;
    INT          copy_height;
    INT          copy_width_rotated;
    INT          copy_height_rotated;
    GX_RECTANGLE copy_clip;
    INT          angle;
} d2_rotation_param_t;

/** DAVE 2D rendering parameters */
typedef struct st_d2_render_param
{
    GX_BYTE      error_list_index;
    GX_BYTE      error_count;
    UCHAR        alpha;
    GX_BOOL      display_list_flushed;
    GX_RECTANGLE clip_rect;
    GX_COLOR     color0;
    GX_COLOR     color1;
    GX_FIXED_VAL line_width;
    INT          font_bits;
    GX_UBYTE     display_list_count;
    d2_u32       src_blend_mode;
    d2_u32       dst_blend_mode;
    d2_u32       render_mode;
    d2_u32       fill_mode;
    d2_u32       line_join;
    d2_u32       line_cap;
    d2_s32       aa_mode;
} d2_render_param_t;

#endif

#if (GX_USE_RENESAS_JPEG == 1)

/** JPEG output streaming control parameters */
typedef struct st_jpeg_output_streaming_param
{
    jpeg_instance_t * p_jpeg;
    GX_DRAW_CONTEXT * p_context;
    GX_PIXELMAP     * p_pixelmap;
    UCHAR           * output_buffer;
    INT               jpeg_buffer_size;
    INT               x;
    INT               y;
    GX_VALUE          image_width;
    GX_VALUE          image_height;
    UINT              bytes_per_pixel;
} jpeg_output_streaming_param_t;
#endif

/** Data structure to save pixel color data for four adjacent pixels */
typedef struct st_pixelmap_adjacent_pixels
{
    GX_COLOR a;
    GX_COLOR b;
    GX_COLOR c;
    GX_COLOR d;
} pixelmap_adjacent_pixels_t;

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** indicator for the number of visible frame buffer */
static GX_UBYTE * visible_frame = NULL;
static GX_UBYTE * working_frame = NULL;

#if (GX_RENESAS_DAVE2D_DRAW == 1)
static GX_BOOL gx_dave2d_first_draw = GX_TRUE;

static d2_color (* gx_d2_color)(GX_COLOR color) = NULL;

/* Variable to hold last state of common rendering params and flags */
static d2_render_param_t g_dave2d = {0};

/** Partial palettes used for drawing 1bpp and 4bpp fonts */
static const d2_color g_mono_palette[2] =
{
    0x00ffffff,
    0xffffffff
};

static const d2_color g_gray_palette[16] =
{
    0x00ffffff,
    0x11ffffff,
    0x22ffffff,
    0x33ffffff,
    0x44ffffff,
    0x55ffffff,
    0x66ffffff,
    0x77ffffff,
    0x88ffffff,
    0x99ffffff,
    0xaaffffff,
    0xbbffffff,
    0xccffffff,
    0xddffffff,
    0xeeffffff,
    0xffffffff,
};

/* 16-bit sine look-up table */
static const uint16_t d2_sin_lut[90] =
{
    0x0000, 0x0477, 0x08EF, 0x0D65, 0x11DB, 0x164F, 0x1AC2, 0x1F32,
    0x23A0, 0x280C, 0x2C74, 0x30D8, 0x3539, 0x3996, 0x3DEE, 0x4241,
    0x4690, 0x4AD8, 0x4F1B, 0x5358, 0x578E, 0x5BBE, 0x5FE6, 0x6406,
    0x681F, 0x6C30, 0x7039, 0x7438, 0x782F, 0x7C1C, 0x7FFF, 0x83D9,
    0x87A8, 0x8B6D, 0x8F27, 0x92D5, 0x9679, 0x9A10, 0x9D9B, 0xA11B,
    0xA48D, 0xA7F3, 0xAB4C, 0xAE97, 0xB1D5, 0xB504, 0xB826, 0xBB39,
    0xBE3E, 0xC134, 0xC41B, 0xC6F3, 0xC9BB, 0xCC73, 0xCF1B, 0xD1B3,
    0xD43B, 0xD6B3, 0xD919, 0xDB6F, 0xDDB3, 0xDFE7, 0xE208, 0xE419,
    0xE617, 0xE803, 0xE9DE, 0xEBA6, 0xED5B, 0xEEFF, 0xF08F, 0xF20D,
    0xF378, 0xF4D0, 0xF615, 0xF746, 0xF865, 0xF970, 0xFA67, 0xFB4B,
    0xFC1C, 0xFCD9, 0xFD82, 0xFE17, 0xFE98, 0xFF06, 0xFF60, 0xFFA6,
    0xFFD8, 0xFFF6
};

 #if defined(LOG_DAVE_ERRORS)
static d2_s32 dave_error_list[DAVE_ERROR_LIST_SIZE] = {0};
 #endif
#endif                                 /* (GX_RENESAS_DAVE2D_DRAW) */

#if (GX_USE_RENESAS_JPEG == 1)
extern TX_SEMAPHORE  gx_renesas_jpeg_semaphore;
static jpeg_status_t g_jpeg_status;
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (GX_RENESAS_DAVE2D_DRAW == 0)
static VOID gx_copy_visible_to_working(GX_CANVAS * canvas, GX_RECTANGLE * copy);
static VOID gx_rotate_canvas_to_working_16bpp(GX_CANVAS * canvas, GX_RECTANGLE * copy, INT angle);
static VOID gx_rotate_canvas_to_working_16bpp_draw(USHORT * pGetRow, USHORT * pPutRow, INT width, INT height,
                                                   INT stride);
static VOID gx_rotate_canvas_to_working_16bpp_draw_rotate90(USHORT * pGetRow,
                                                            USHORT * pPutRow,
                                                            INT      width,
                                                            INT      height,
                                                            INT      canvas_stride,
                                                            INT      disp_stride);
static VOID gx_rotate_canvas_to_working_16bpp_draw_rotate180(USHORT * pGetRow,
                                                             USHORT * pPutRow,
                                                             INT      width,
                                                             INT      height,
                                                             INT      stride);
static VOID gx_rotate_canvas_to_working_16bpp_draw_rotate270(USHORT * pGetRow,
                                                             USHORT * pPutRow,
                                                             INT      width,
                                                             INT      height,
                                                             INT      canvas_stride,
                                                             INT      disp_stride);
static VOID gx_rotate_canvas_to_working_32bpp(GX_CANVAS * canvas, GX_RECTANGLE * copy, INT angle);
static VOID gx_rotate_canvas_to_working_32bpp_draw(ULONG * pGetRow, ULONG * pPutRow, INT width, INT height, INT stride);
static VOID gx_rotate_canvas_to_working_32bpp_draw_rotate90(ULONG * pGetRow,
                                                            ULONG * pPutRow,
                                                            INT     width,
                                                            INT     height,
                                                            INT     canvas_stride,
                                                            INT     disp_stride);
static VOID gx_rotate_canvas_to_working_32bpp_draw_rotate180(ULONG * pGetRow,
                                                             ULONG * pPutRow,
                                                             INT     width,
                                                             INT     height,
                                                             INT     stride);
static VOID gx_rotate_canvas_to_working_32bpp_draw_rotate270(ULONG * pGetRow,
                                                             ULONG * pPutRow,
                                                             INT     width,
                                                             INT     height,
                                                             INT     canvas_stride,
                                                             INT     disp_stride);

#endif

#if (GX_RENESAS_DAVE2D_DRAW == 1)
static d2_color gx_rgb565_to_888(GX_COLOR color);
static d2_color gx_xrgb_to_xrgb(GX_COLOR color);
static d2_s32   gx_dave2d_fast_sin(INT angle);
static d2_u32   gx_dave2d_format_set(GX_PIXELMAP * map);
static VOID     gx_dave2d_pixelmap_draw(GX_DRAW_CONTEXT * context,
                                        INT               xpos,
                                        INT               ypos,
                                        GX_PIXELMAP     * pixelmap,
                                        GX_UBYTE          alpha);
static VOID gx_dave2d_set_texture(GX_DRAW_CONTEXT * context, d2_device * dave, INT xpos, INT ypos,
                                  GX_PIXELMAP * map);
static VOID gx_dave2d_glyph_8bit_draw(GX_DRAW_CONTEXT * context,
                                      GX_RECTANGLE    * draw_area,
                                      GX_POINT        * map_offset,
                                      const GX_GLYPH  * glyph,
                                      d2_u32            mode);
static VOID gx_dave2d_glyph_4bit_draw(GX_DRAW_CONTEXT * context,
                                      GX_RECTANGLE    * draw_area,
                                      GX_POINT        * map_offset,
                                      const GX_GLYPH  * glyph,
                                      d2_u32            mode);
static VOID gx_dave2d_glyph_1bit_draw(GX_DRAW_CONTEXT * context,
                                      GX_RECTANGLE    * draw_area,
                                      GX_POINT        * map_offset,
                                      const GX_GLYPH  * glyph,
                                      d2_u32            mode);
static VOID gx_dave2d_copy_visible_to_working(GX_CANVAS * canvas, GX_RECTANGLE * copy);
static VOID gx_dave2d_rotate_canvas_to_working(GX_CANVAS * canvas, GX_RECTANGLE * copy, INT rotation_angle);

static VOID gx_dave2d_rotate_canvas_to_working_image_draw(d2_device           * p_dave,
                                                          d2_rotation_param_t * p_param,
                                                          d2_u32                mode,
                                                          GX_DISPLAY          * p_display,
                                                          GX_CANVAS           * p_canvas);

#endif
#if (GX_USE_RENESAS_JPEG == 1)
void        _gx_renesas_jpeg_callback(jpeg_callback_args_t * p_args);
static INT  gx_renesas_jpeg_wait(jpeg_status_t * p_status, uint32_t timeout);
static INT  gx_renesas_jpeg_draw_open(GX_DRAW_CONTEXT * p_context, jpeg_instance_t * p_jpeg, UINT * p_bytes_per_pixel);
static VOID gx_renesas_jpeg_draw_output_streaming(jpeg_output_streaming_param_t * p_param);
static UINT gx_renesas_jpeg_draw_minimum_height_get(jpeg_color_space_t format, GX_VALUE width, GX_VALUE height);

static INT gx_renesas_jpeg_draw_output_streaming_wait(void);

#endif

/** functions shared in GUIX display driver files */
#if (GX_RENESAS_DAVE2D_DRAW == 1)
 #if defined(LOG_DAVE_ERRORS)
VOID gx_log_dave_error(d2_s32 status);
INT  gx_get_dave_error(INT get_index);

 #endif
VOID    gx_dave2d_display_list_count(GX_DISPLAY * display);
GX_BOOL gx_dave2d_convex_polygon_test(GX_POINT * vertex, INT num);
VOID    gx_display_list_flush(GX_DISPLAY * display);
VOID    gx_display_list_open(GX_DISPLAY * display);
VOID    gx_dave2d_canvas_composite(GX_CANVAS * canvas, GX_CANVAS * composite, UINT alpha);
VOID    gx_dave2d_circle_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, bool aa);
VOID    gx_dave2d_coordinate_rotate(GX_DRAW_CONTEXT * context, INT * x, INT * y);
VOID    gx_dave2d_pixelmap_coordinate_rotate(GX_DRAW_CONTEXT * context,
                                             INT             * xpos,
                                             INT             * ypos,
                                             GX_PIXELMAP     * pixelmap);
VOID gx_dave2d_rectangle_rotate(GX_DRAW_CONTEXT * context,
                                GX_RECTANGLE    * rectangle_in,
                                GX_RECTANGLE    * rectangle_out);
VOID               gx_dave2d_cliprect_set(d2_device * p_dave, GX_RECTANGLE * clip);
d2_device        * gx_dave2d_context_clip_set(GX_DRAW_CONTEXT * context);
VOID               gx_dave2d_outline_width_set(d2_device * dave, GX_FIXED_VAL width);
VOID               gx_dave2d_line_join_set(d2_device * dave, d2_u32 mode);
VOID               gx_dave2d_line_cap_set(d2_device * dave, d2_u32 mode);
VOID               gx_dave2d_color0_set(d2_device * dave, GX_COLOR color);
VOID               gx_dave2d_color1_set(d2_device * dave, GX_COLOR color);
VOID               gx_dave2d_alpha_set(d2_device * dave, UCHAR alpha);
VOID               gx_dave2d_fill_mode_set(d2_device * dave, d2_u32 mode);
VOID               gx_dave2d_blend_mode_set(d2_device * dave, d2_u32 srcmode, d2_u32 dstmode);
VOID               gx_dave2d_render_mode_set(d2_device * dave, d2_u32 mode);
VOID               gx_dave2d_anti_aliasing_set(d2_device * dave, d2_s32 mode);
static inline UINT gx_dave2d_brush_alpha_set(d2_device * dave, GX_DRAW_CONTEXT * context);
VOID               gx_dave2d_rotate_canvas_to_working_param_set(d2_rotation_param_t * p_param,
                                                                GX_DISPLAY          * p_display,
                                                                GX_CANVAS           * p_canvas);

#endif

/** functions provided by rm_guix_port.c */
extern void rm_guix_port_frame_toggle(ULONG display_handle, GX_UBYTE ** visible);
extern void rm_guix_port_frame_pointers_get(ULONG display_handle, GX_UBYTE ** visible, GX_UBYTE ** working);
extern INT  rm_guix_port_display_rotation_get(ULONG display_handle);
extern void rm_guix_port_display_actual_size_get(ULONG display_handle, INT * width, INT * height);

#if (GX_USE_RENESAS_JPEG == 1)
extern void * rm_guix_port_jpeg_buffer_get(ULONG display_handle, INT * memory_size);
extern void * rm_guix_port_jpeg_instance_get(ULONG display_handle);

#endif

/***********************************************************************************************************************
 * GUIX display driver function prototypes (called by GUIX)
 **********************************************************************************************************************/
VOID _gx_ra_buffer_toggle(GX_CANVAS * canvas, GX_RECTANGLE * dirty);
VOID _gx_ra_rotated_buffer_toggle(GX_CANVAS * canvas, GX_RECTANGLE * dirty);

#if (GX_USE_RENESAS_JPEG == 1)
VOID _gx_renesas_jpeg_draw(GX_DRAW_CONTEXT * p_context, INT x, INT y, GX_PIXELMAP * p_pixelmap);

#endif

#if (GX_RENESAS_DAVE2D_DRAW == 1)
VOID _gx_dave2d_drawing_initiate(GX_DISPLAY * display, GX_CANVAS * canvas);
VOID _gx_dave2d_drawing_complete(GX_DISPLAY * display, GX_CANVAS * canvas);
VOID _gx_dave2d_horizontal_line(GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos, INT width, GX_COLOR color);
VOID _gx_dave2d_vertical_line(GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos, INT width, GX_COLOR color);
VOID _gx_dave2d_canvas_copy(GX_CANVAS * canvas, GX_CANVAS * composite);
VOID _gx_dave2d_canvas_blend(GX_CANVAS * canvas, GX_CANVAS * composite);
VOID _gx_dave2d_simple_line_draw(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_simple_wide_line(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_aliased_line(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_horizontal_pattern_line_draw_565(GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos);
VOID _gx_dave2d_horizontal_pattern_line_draw_888(GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos);
VOID _gx_dave2d_vertical_pattern_line_draw_565(GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos);
VOID _gx_dave2d_vertical_pattern_line_draw_888(GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos);
VOID _gx_dave2d_aliased_wide_line(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_pixelmap_draw(GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap);
VOID _gx_dave2d_pixelmap_rotate_16bpp(GX_DRAW_CONTEXT * context,
                                      INT               xpos,
                                      INT               ypos,
                                      GX_PIXELMAP     * pixelmap,
                                      INT               angle,
                                      INT               rot_cx,
                                      INT               rot_cy);
VOID _gx_dave2d_pixelmap_blend(GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap, GX_UBYTE alpha);
VOID _gx_dave2d_horizontal_pixelmap_line_draw(GX_DRAW_CONTEXT       * context,
                                              INT                     xstart,
                                              INT                     xend,
                                              INT                     y,
                                              GX_FILL_PIXELMAP_INFO * info);
VOID _gx_dave2d_polygon_draw(GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num);
VOID _gx_dave2d_polygon_fill(GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num);
VOID _gx_dave2d_pixel_write_565(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color);
VOID _gx_dave2d_pixel_write_888(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color);
VOID _gx_dave2d_pixel_blend_565(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha);
VOID _gx_dave2d_pixel_blend_888(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha);
VOID _gx_dave2d_block_move(GX_DRAW_CONTEXT * context, GX_RECTANGLE * block, INT xshift, INT yshift);
VOID _gx_dave2d_alphamap_draw(GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap);
VOID _gx_dave2d_compressed_glyph_8bit_draw(GX_DRAW_CONTEXT * context,
                                           GX_RECTANGLE    * draw_area,
                                           GX_POINT        * map_offset,
                                           const GX_GLYPH  * glyph);
VOID _gx_dave2d_raw_glyph_8bit_draw(GX_DRAW_CONTEXT * context,
                                    GX_RECTANGLE    * draw_area,
                                    GX_POINT        * map_offset,
                                    const GX_GLYPH  * glyph);
VOID _gx_dave2d_compressed_glyph_4bit_draw(GX_DRAW_CONTEXT * context,
                                           GX_RECTANGLE    * draw_area,
                                           GX_POINT        * map_offset,
                                           const GX_GLYPH  * glyph);
VOID _gx_dave2d_raw_glyph_4bit_draw(GX_DRAW_CONTEXT * context,
                                    GX_RECTANGLE    * draw_area,
                                    GX_POINT        * map_offset,
                                    const GX_GLYPH  * glyph);
VOID _gx_dave2d_compressed_glyph_1bit_draw(GX_DRAW_CONTEXT * context,
                                           GX_RECTANGLE    * draw_area,
                                           GX_POINT        * map_offset,
                                           const GX_GLYPH  * glyph);
VOID _gx_dave2d_raw_glyph_1bit_draw(GX_DRAW_CONTEXT * context,
                                    GX_RECTANGLE    * draw_area,
                                    GX_POINT        * map_offset,
                                    const GX_GLYPH  * glyph);
VOID _gx_dave2d_aliased_circle_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_circle_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_circle_fill(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_pie_fill(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle);
VOID _gx_dave2d_aliased_arc_draw(GX_DRAW_CONTEXT * context,
                                 INT               xcenter,
                                 INT               ycenter,
                                 UINT              r,
                                 INT               start_angle,
                                 INT               end_angle);
VOID _gx_dave2d_arc_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle);
VOID _gx_dave2d_arc_fill(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle);
VOID _gx_dave2d_aliased_ellipse_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b);
VOID _gx_dave2d_ellipse_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b);
VOID _gx_dave2d_ellipse_fill(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b);
VOID _gx_dave2d_buffer_toggle(GX_CANVAS * canvas, GX_RECTANGLE * dirty);

/* Rotated screen mode prototypes */
VOID _gx_dave2d_rotated_horizontal_pattern_line_draw_565(GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos);
VOID _gx_dave2d_rotated_vertical_pattern_line_draw_565(GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos);
VOID _gx_dave2d_rotated_pixel_write_565(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color);
VOID _gx_dave2d_rotated_pixel_blend_565(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha);
VOID _gx_dave2d_rotated_horizontal_pattern_line_draw_888(GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos);
VOID _gx_dave2d_rotated_vertical_pattern_line_draw_888(GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos);
VOID _gx_dave2d_rotated_pixel_write_888(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color);
VOID _gx_dave2d_rotated_pixel_blend_888(GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha);
VOID _gx_dave2d_rotated_pixelmap_rotate_16bpp(GX_DRAW_CONTEXT * context,
                                              INT               xpos,
                                              INT               ypos,
                                              GX_PIXELMAP     * pixelmap,
                                              INT               angle,
                                              INT               rot_cx,
                                              INT               rot_cy);
VOID _gx_dave2d_rotated_drawing_initiate(GX_DISPLAY * display, GX_CANVAS * canvas);
VOID _gx_dave2d_rotated_drawing_complete(GX_DISPLAY * display, GX_CANVAS * canvas);
VOID _gx_dave2d_rotated_horizontal_line(GX_DRAW_CONTEXT * context,
                                        INT               xstart,
                                        INT               xend,
                                        INT               ypos,
                                        INT               width,
                                        GX_COLOR          color);
VOID _gx_dave2d_rotated_vertical_line(GX_DRAW_CONTEXT * context,
                                      INT               ystart,
                                      INT               yend,
                                      INT               xpos,
                                      INT               width,
                                      GX_COLOR          color);
VOID _gx_dave2d_rotated_canvas_copy(GX_CANVAS * canvas, GX_CANVAS * composite);
VOID _gx_dave2d_rotated_canvas_blend(GX_CANVAS * canvas, GX_CANVAS * composite);
VOID _gx_dave2d_rotated_simple_line_draw(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_rotated_simple_wide_line(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_rotated_aliased_line(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_rotated_aliased_wide_line(GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend);
VOID _gx_dave2d_rotated_pixelmap_draw(GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap);
VOID _gx_dave2d_rotated_horizontal_pixelmap_line_draw(GX_DRAW_CONTEXT       * context,
                                                      INT                     xstart,
                                                      INT                     xend,
                                                      INT                     y,
                                                      GX_FILL_PIXELMAP_INFO * info);
VOID _gx_dave2d_rotated_pixelmap_blend(GX_DRAW_CONTEXT * context,
                                       INT               xpos,
                                       INT               ypos,
                                       GX_PIXELMAP     * pixelmap,
                                       GX_UBYTE          alpha);
VOID _gx_dave2d_rotated_polygon_draw(GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num);
VOID _gx_dave2d_rotated_polygon_fill(GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num);
VOID _gx_dave2d_rotated_block_move(GX_DRAW_CONTEXT * context, GX_RECTANGLE * block, INT xshift, INT yshift);
VOID _gx_dave2d_rotated_alphamap_draw(GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap);
VOID _gx_dave2d_rotated_compressed_glyph_8bit_draw(GX_DRAW_CONTEXT * context,
                                                   GX_RECTANGLE    * draw_area,
                                                   GX_POINT        * map_offset,
                                                   const GX_GLYPH  * glyph);
VOID _gx_dave2d_rotated_raw_glyph_8bit_draw(GX_DRAW_CONTEXT * context,
                                            GX_RECTANGLE    * draw_area,
                                            GX_POINT        * map_offset,
                                            const GX_GLYPH  * glyph);
VOID _gx_dave2d_rotated_compressed_glyph_4bit_draw(GX_DRAW_CONTEXT * context,
                                                   GX_RECTANGLE    * draw_area,
                                                   GX_POINT        * map_offset,
                                                   const GX_GLYPH  * glyph);
VOID _gx_dave2d_rotated_raw_glyph_4bit_draw(GX_DRAW_CONTEXT * context,
                                            GX_RECTANGLE    * draw_area,
                                            GX_POINT        * map_offset,
                                            const GX_GLYPH  * glyph);
VOID _gx_dave2d_rotated_compressed_glyph_1bit_draw(GX_DRAW_CONTEXT * context,
                                                   GX_RECTANGLE    * draw_area,
                                                   GX_POINT        * map_offset,
                                                   const GX_GLYPH  * glyph);
VOID _gx_dave2d_rotated_raw_glyph_1bit_draw(GX_DRAW_CONTEXT * context,
                                            GX_RECTANGLE    * draw_area,
                                            GX_POINT        * map_offset,
                                            const GX_GLYPH  * glyph);
VOID _gx_dave2d_rotated_buffer_toggle(GX_CANVAS * canvas, GX_RECTANGLE * dirty);
VOID _gx_dave2d_rotated_aliased_circle_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_rotated_circle_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_rotated_circle_fill(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r);
VOID _gx_dave2d_rotated_pie_fill(GX_DRAW_CONTEXT * context,
                                 INT               xcenter,
                                 INT               ycenter,
                                 UINT              r,
                                 INT               start_angle,
                                 INT               end_angle);
VOID _gx_dave2d_rotated_aliased_arc_draw(GX_DRAW_CONTEXT * context,
                                         INT               xcenter,
                                         INT               ycenter,
                                         UINT              r,
                                         INT               start_angle,
                                         INT               end_angle);
VOID _gx_dave2d_rotated_arc_draw(GX_DRAW_CONTEXT * context,
                                 INT               xcenter,
                                 INT               ycenter,
                                 UINT              r,
                                 INT               start_angle,
                                 INT               end_angle);
VOID _gx_dave2d_rotated_arc_fill(GX_DRAW_CONTEXT * context,
                                 INT               xcenter,
                                 INT               ycenter,
                                 UINT              r,
                                 INT               start_angle,
                                 INT               end_angle);
VOID _gx_dave2d_rotated_aliased_ellipse_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b);
VOID _gx_dave2d_rotated_ellipse_draw(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b);
VOID _gx_dave2d_rotated_ellipse_fill(GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b);

#endif

/***********************************************************************************************************************
 * Functions
 ***********************************************************************************************************************/
#if (GX_RENESAS_DAVE2D_DRAW == 1)

/*******************************************************************************************************************//**
 * @addtogroup RM_GUIX_PORT
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Subroutine to define the width of geometry outlines.
 * @param  dave[in]            Pointer to dave device structure
 * @param  width[in]           Outline width in pixels
 **********************************************************************************************************************/
VOID gx_dave2d_outline_width_set (d2_device * dave, GX_FIXED_VAL width)
{
    if (g_dave2d.line_width != width)
    {
        CHECK_DAVE_STATUS(d2_outlinewidth(dave, (d2_width) ((ULONG) (D2_FIX4((ULONG) width)) >> GX_FIXED_VAL_SHIFT)))
        g_dave2d.line_width = width;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to specify polyline connection style. This is used while drawing the polygons.
 * @param  dave[in]            Pointer to dave device structure
 * @param  mode[in]            Linejoin mode
 **********************************************************************************************************************/
VOID gx_dave2d_line_join_set (d2_device * dave, d2_u32 mode)
{
    if (g_dave2d.line_join != mode)
    {
        CHECK_DAVE_STATUS(d2_setlinejoin(dave, mode))
        g_dave2d.line_join = mode;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to specify lineend style. This is used while drawing the lines.
 * @param  dave[in]            Pointer to dave device structure
 * @param  mode[in]            Linecap mode
 **********************************************************************************************************************/
VOID gx_dave2d_line_cap_set (d2_device * dave, d2_u32 mode)
{
    if (g_dave2d.line_cap != mode)
    {
        CHECK_DAVE_STATUS(d2_setlinecap(dave, mode))
        g_dave2d.line_cap = mode;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to set color registers. It set the color register with index 0. This is called when only one color
 * is used(when blending is not used).
 * @param  dave[in]            Pointer to dave device structure
 * @param  color[in]           24bit rgb color value
 **********************************************************************************************************************/
VOID gx_dave2d_color0_set (d2_device * dave, GX_COLOR color)
{
    if (g_dave2d.color0 != color)
    {
        CHECK_DAVE_STATUS(d2_setcolor(dave, 0, gx_d2_color(color)))
        g_dave2d.color0 = color;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to set color registers. It set the color register with index 1.
 * @param  dave[in]            Pointer to dave device structure
 * @param  color[in]           24bit rgb color value
 **********************************************************************************************************************/
VOID gx_dave2d_color1_set (d2_device * dave, GX_COLOR color)
{
    if (g_dave2d.color1 != color)
    {
        CHECK_DAVE_STATUS(d2_setcolor(dave, 1, gx_d2_color(color)))
        g_dave2d.color1 = color;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to set constant alpha value.
 * @param  dave[in]            Pointer to dave device structure
 * @param  alpha[in]           Alpha value (0 for transparent, 255 for opaque)
 **********************************************************************************************************************/
VOID gx_dave2d_alpha_set (d2_device * dave, UCHAR alpha)
{
    if (g_dave2d.alpha != alpha)
    {
        CHECK_DAVE_STATUS(d2_setalpha(dave, alpha))
        g_dave2d.alpha = alpha;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to set fill mode.
 * @param  dave[in]            Pointer to dave device structure
 * @param  mode[in]            fill mode(solid,patter,texture etc)
 **********************************************************************************************************************/
VOID gx_dave2d_fill_mode_set (d2_device * dave, d2_u32 mode)
{
    if (g_dave2d.fill_mode != mode)
    {
        CHECK_DAVE_STATUS(d2_setfillmode(dave, mode))
        g_dave2d.fill_mode = mode;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to set a rendering mode.
 * @param  dave[in]            Pointer to dave device structure
 * @param  mode[in]            rendering mode
 **********************************************************************************************************************/
VOID gx_dave2d_render_mode_set (d2_device * dave, d2_u32 mode)
{
    if (g_dave2d.render_mode != mode)
    {
        CHECK_DAVE_STATUS(d2_selectrendermode(dave, mode))
        g_dave2d.render_mode = mode;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to set a blending for the RGB channel. It defines how the RGB channels of new pixels (source) are
 * combined with already existing data in the framebuffer (destination).
 * @param  dave[in]            Pointer to dave device structure
 * @param  srcmode[in]         source blend factor
 * @param  dstmode[in]         destination blend factor
 **********************************************************************************************************************/
VOID gx_dave2d_blend_mode_set (d2_device * dave, d2_u32 srcmode, d2_u32 dstmode)
{
    if ((g_dave2d.src_blend_mode != srcmode) || (g_dave2d.dst_blend_mode != dstmode))
    {
        CHECK_DAVE_STATUS(d2_setblendmode(dave, srcmode, dstmode))
        g_dave2d.src_blend_mode = srcmode;
        g_dave2d.dst_blend_mode = dstmode;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to globally enable or disable the anti aliasing.
 * @param  dave[in]            Pointer to dave device structure
 * @param  mode[in]            boolean value(0 = disable, 1 = enable)
 **********************************************************************************************************************/
VOID gx_dave2d_anti_aliasing_set (d2_device * dave, d2_s32 mode)
{
    if (g_dave2d.aa_mode != mode)
    {
        CHECK_DAVE_STATUS(d2_setantialiasing(dave, mode))
        g_dave2d.aa_mode = mode;
    }
}

/*******************************************************************************************************************//**
 * @brief  Subroutine to set alpha from the current brush (if enabled). Returns 1 if alpha is 0 (invisible).
 * @param  dave[in]            Pointer to dave device structure
 * @param  mode[in]            Pointer to the current draw context
 **********************************************************************************************************************/
static inline UINT gx_dave2d_brush_alpha_set (d2_device * dave, GX_DRAW_CONTEXT * context)
{
 #if defined(GX_BRUSH_ALPHA_SUPPORT)
    GX_UBYTE brush_alpha = context->gx_draw_context_brush.gx_brush_alpha;

    if (brush_alpha == 0U)
    {
        return 1;
    }

    gx_dave2d_alpha_set(dave, (UCHAR) brush_alpha);
 #else
    gx_dave2d_alpha_set(dave, (UCHAR) GX_ALPHA_VALUE_OPAQUE);
 #endif

    return 0;
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, close previous frame and set new canvas drawing address.
 * This function is called by GUIX to initiate canvas drawing.
 * @param   display[in]         Pointer to a GUIX display context
 * @param   canvas[in]          Pointer to a GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_drawing_initiate (GX_DISPLAY * display, GX_CANVAS * canvas)
{
    d2_u32 mode = d2_mode_rgb565;

    if (GX_TRUE == gx_dave2d_first_draw)
    {
        d2_device * dave = display->gx_display_accelerator;

        /* Initialize dave2d rendering parameters. */
        memset(&g_dave2d, 0, sizeof(d2_render_param_t));
        g_dave2d.clip_rect.gx_rectangle_left   = -1;
        g_dave2d.clip_rect.gx_rectangle_top    = -1;
        g_dave2d.clip_rect.gx_rectangle_right  = -1;
        g_dave2d.clip_rect.gx_rectangle_bottom = -1;
        g_dave2d.src_blend_mode                = d2_bm_alpha;
        g_dave2d.dst_blend_mode                = d2_bm_one_minus_alpha;
        g_dave2d.display_list_flushed          = GX_FALSE;
        g_dave2d.display_list_count            = (GX_UBYTE) 0;

        /* Set default mode */
        CHECK_DAVE_STATUS(d2_setalphablendmode(dave, d2_bm_one, d2_bm_one_minus_alpha))
        CHECK_DAVE_STATUS(d2_setblendmode(dave, g_dave2d.src_blend_mode, g_dave2d.dst_blend_mode))
        CHECK_DAVE_STATUS(d2_outlinewidth(dave,
                                          (d2_width) ((ULONG) (D2_FIX4((ULONG) g_dave2d.line_width)) >>
                                                      GX_FIXED_VAL_SHIFT)))
        CHECK_DAVE_STATUS(d2_setlinejoin(dave, g_dave2d.line_join))
        CHECK_DAVE_STATUS(d2_setlinecap(dave, g_dave2d.line_cap))
        CHECK_DAVE_STATUS(d2_setcolor(dave, 0, g_dave2d.color0))
        CHECK_DAVE_STATUS(d2_setcolor(dave, 1, g_dave2d.color1))
        CHECK_DAVE_STATUS(d2_setalpha(dave, g_dave2d.alpha))
        CHECK_DAVE_STATUS(d2_setfillmode(dave, g_dave2d.fill_mode))
        CHECK_DAVE_STATUS(d2_selectrendermode(dave, g_dave2d.render_mode))
        CHECK_DAVE_STATUS(d2_setantialiasing(dave, g_dave2d.aa_mode))

        gx_dave2d_first_draw = GX_FALSE;
    }

    switch ((INT) display->gx_display_color_format)
    {
        case GX_COLOR_FORMAT_565RGB:
        {
            mode        = d2_mode_rgb565;
            gx_d2_color = gx_rgb565_to_888;
            break;
        }

        case GX_COLOR_FORMAT_24XRGB:
        case GX_COLOR_FORMAT_32ARGB:
        {
            mode        = d2_mode_argb8888;
            gx_d2_color = gx_xrgb_to_xrgb;
            break;
        }

        default:                       /* including GX_COLOR_FORMAT_8BIT_PALETTE */
        {
            mode        = d2_mode_alpha8;
            gx_d2_color = gx_xrgb_to_xrgb;
            break;
        }
    }

    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(display);

    /** Open next display list before we go. */
    gx_display_list_open(display);

    /* Swap dimensions if we're running in 'portrait' orientation */
    d2_u32 width;
    d2_u32 height;
    if ((display->gx_display_rotation_angle == 0) || (display->gx_display_rotation_angle == 180))
    {
        width  = (d2_u32) canvas->gx_canvas_x_resolution;
        height = (d2_u32) canvas->gx_canvas_y_resolution;
    }
    else
    {
        width  = (d2_u32) canvas->gx_canvas_y_resolution;
        height = (d2_u32) canvas->gx_canvas_x_resolution;
    }

    CHECK_DAVE_STATUS(d2_framebuffer(display->gx_display_accelerator, canvas->gx_canvas_memory, (d2_s32) width, width,
                                     height, (d2_s32) mode))
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, complete drawing. This function does nothing special. The buffer toggle
 * function takes care of toggling the display lists.
 * @param   display[in]         Pointer to a GUIX display context
 * @param   canvas[in]          Pointer to a GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_drawing_complete (GX_DISPLAY * display, GX_CANVAS * canvas)
{
    GX_PARAMETER_NOT_USED(display);

    GX_PARAMETER_NOT_USED(canvas);
}

/*******************************************************************************************************************//**
 * @brief  Subfunction for blending one canvas onto another
 * @param   canvas[in]          Pointer to a source GUIX canvas
 * @param   composite[in]       Pointer to a destination GUIX canvas
 * @param   alpha[in]           Composite canvas alpha
 **********************************************************************************************************************/
VOID gx_dave2d_canvas_composite (GX_CANVAS * canvas, GX_CANVAS * composite, UINT alpha)
{
    d2_u32       mode;
    GX_DISPLAY * display = canvas->gx_canvas_display;
    d2_device  * dave    = display->gx_display_accelerator;

    gx_dave2d_cliprect_set(dave, &composite->gx_canvas_dirty_area);

    switch ((INT) display->gx_display_color_format)
    {
        case GX_COLOR_FORMAT_565RGB:
        {
            mode = d2_mode_rgb565;
            break;
        }

        case GX_COLOR_FORMAT_24XRGB:
        case GX_COLOR_FORMAT_32ARGB:
        {
            mode = d2_mode_argb8888;
            break;
        }

        case GX_COLOR_FORMAT_8BIT_PALETTE:
        {
            mode = d2_mode_alpha8;
            break;
        }

        default:

            return;
    }

    /** Set the alpha blend value to opaque. */
    gx_dave2d_alpha_set(dave, (UCHAR) alpha);

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) canvas->gx_canvas_memory, canvas->gx_canvas_x_resolution,
                                    canvas->gx_canvas_x_resolution, canvas->gx_canvas_y_resolution, mode))

    CHECK_DAVE_STATUS(d2_blitcopy(dave, canvas->gx_canvas_x_resolution, canvas->gx_canvas_y_resolution, 0, 0,
                                  (d2_width) (D2_FIX4((USHORT) canvas->gx_canvas_x_resolution)),
                                  (d2_width) (D2_FIX4((USHORT) canvas->gx_canvas_y_resolution)),
                                  (d2_point) (D2_FIX4((USHORT) canvas->gx_canvas_display_offset_x)),
                                  (d2_point) (D2_FIX4((USHORT) canvas->gx_canvas_display_offset_y)),
                                  d2_bf_no_blitctxbackup))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, copy canvas function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to copy canvas data from one canvas to another.
 * @param   canvas[in]          Pointer to a source GUIX canvas
 * @param   composite[in]       Pointer to a destination GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_canvas_copy (GX_CANVAS * canvas, GX_CANVAS * composite)
{
    gx_dave2d_canvas_composite(canvas, composite, GX_ALPHA_VALUE_OPAQUE);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, blend canvas function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to blend source canvas with the existing data in the destination canvas.
 * @param   canvas[in]          Pointer to a source GUIX canvas
 * @param   composite[in]       Pointer to a destination GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_canvas_blend (GX_CANVAS * canvas, GX_CANVAS * composite)
{
    gx_dave2d_canvas_composite(canvas, composite, canvas->gx_canvas_alpha);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, horizontal line draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a horizontal line.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          x axis start position of a horizontal line in pixel unit
 * @param   xend[in]            x axis end position of a horizontal line in pixel unit
 * @param   ypos[in]            y position of a horizontal line
 * @param   width[in]           Line width in pixel unit
 * @param   color[in]           GUIX color data
 **********************************************************************************************************************/
VOID _gx_dave2d_horizontal_line (GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos, INT width, GX_COLOR color)
{
    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_fill_mode_set(dave, d2_fm_color);
    gx_dave2d_color0_set(dave, color);
    gx_dave2d_render_mode_set(dave, d2_rm_solid);

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        ypos -= width - 1;
    }

    CHECK_DAVE_STATUS(d2_renderbox(dave, (d2_point) (D2_FIX4((USHORT) xstart)), (d2_point) (D2_FIX4((USHORT) ypos)),
                                   (d2_point) (D2_FIX4((USHORT) ((xend - xstart) + 1))),
                                   (d2_point) (D2_FIX4((USHORT) width))))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, vertical line draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a vertical line.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   ystart[in]          y axis start position of a vertical line in pixel unit
 * @param   yend[in]            y axis end position of a vertical line in pixel unit
 * @param   xpos[in]            x position of a vertical line
 * @param   width[in]           Line width in pixel unit
 * @param   color[in]           GUIX color data
 **********************************************************************************************************************/
VOID _gx_dave2d_vertical_line (GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos, INT width, GX_COLOR color)
{
    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_fill_mode_set(dave, d2_fm_color);
    gx_dave2d_color0_set(dave, color);
    gx_dave2d_render_mode_set(dave, d2_rm_solid);

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CCW)
    {
        xpos -= width - 1;
    }

    CHECK_DAVE_STATUS(d2_renderbox(dave, (d2_point) (D2_FIX4((USHORT) xpos)), (d2_point) (D2_FIX4((USHORT) ystart)),
                                   (d2_point) (D2_FIX4((USHORT) width)),
                                   (d2_point) (D2_FIX4((USHORT) ((yend - ystart) + 1)))))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, aliased simple line draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a aliased simple line.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          x axis start position of a simple line in pixel unit
 * @param   ystart[in]          y axis start position of a simple line in pixel unit
 * @param   xend[in]            x axis end position of a simple line in pixel unit
 * @param   yend[in]            y axis end position of a simple line in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_simple_line_draw (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_render_mode_set(dave, d2_rm_solid);
    gx_dave2d_anti_aliasing_set(dave, 0);
    gx_dave2d_color0_set(dave, context->gx_draw_context_brush.gx_brush_line_color);

    CHECK_DAVE_STATUS(d2_renderline(dave, (d2_point) (D2_FIX4((USHORT) xstart)), (d2_point) (D2_FIX4((USHORT) ystart)),
                                    (d2_point) (D2_FIX4((USHORT) xend)), (d2_point) (D2_FIX4((USHORT) yend)),
                                    (d2_width) (D2_FIX4((USHORT) context->gx_draw_context_brush.gx_brush_width)),
                                    d2_le_exclude_none))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, aliased wide line draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a draw a aliased wide line.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          x axis start position of a wide line in pixel unit
 * @param   ystart[in]          y axis start position of a wide line in pixel unit
 * @param   xend[in]            x axis end position of a wide line in pixel unit
 * @param   yend[in]            y axis end position of a wide line in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_simple_wide_line (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    d2_device * dave  = gx_dave2d_context_clip_set(context);
    GX_BRUSH  * brush = &context->gx_draw_context_brush;

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    /** Set rendering mode to solid. */
    gx_dave2d_render_mode_set(dave, d2_rm_solid);
    gx_dave2d_anti_aliasing_set(dave, 0);
    gx_dave2d_color0_set(dave, context->gx_draw_context_brush.gx_brush_line_color);

    /** Set the lineend style based on brush style. */
    if (brush->gx_brush_style & GX_BRUSH_ROUND)
    {
        gx_dave2d_line_cap_set(dave, d2_lc_round);
    }
    else
    {
        gx_dave2d_line_cap_set(dave, d2_lc_butt);
    }

    CHECK_DAVE_STATUS(d2_renderline(dave, (d2_point) (D2_FIX4((USHORT) xstart)), (d2_point) (D2_FIX4((USHORT) ystart)),
                                    (d2_point) (D2_FIX4((USHORT) xend)), (d2_point) (D2_FIX4((USHORT) yend)),
                                    (d2_width) (D2_FIX4((USHORT) brush->gx_brush_width)), d2_le_exclude_none))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, anti-aliased line draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw an anti-aliased wide line.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          x axis start position of an anti-aliased line in pixel unit
 * @param   ystart[in]          y axis start position of an anti-aliased line in pixel unit
 * @param   xend[in]            x axis end position of an anti-aliased line in pixel unit
 * @param   yend[in]            y axis end position of an anti-aliased line in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_aliased_line (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    /** Set rendering mode to solid. */
    gx_dave2d_render_mode_set(dave, d2_rm_solid);
    gx_dave2d_anti_aliasing_set(dave, 1);
    gx_dave2d_color0_set(dave, context->gx_draw_context_brush.gx_brush_line_color);

    CHECK_DAVE_STATUS(d2_renderline(dave, (d2_point) (D2_FIX4((USHORT) xstart)), (d2_point) (D2_FIX4((USHORT) ystart)),
                                    (d2_point) (D2_FIX4((USHORT) xend)), (d2_point) (D2_FIX4((USHORT) yend)),
                                    (d2_width) (D2_FIX4((USHORT) context->gx_draw_context_brush.gx_brush_width)),
                                    d2_le_exclude_none))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, horizontal pattern draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a horizontal pattern line for RGB565 color format.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          x axis start position of a horizontal pattern line in pixel unit
 * @param   xend[in]            x axis end position of a horizontal pattern line in pixel unit
 * @param   ypos[in]            y position of a horizontal pattern line
 **********************************************************************************************************************/
VOID _gx_dave2d_horizontal_pattern_line_draw_565 (GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic 16bpp horizontal pattern line draw routine. */
    _gx_display_driver_16bpp_horizontal_pattern_line_draw(context, xstart, xend, ypos);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, horizontal pattern draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a horizontal pattern line for RGB888 color format.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          x axis start position of a horizontal pattern line in pixel unit
 * @param   xend[in]            x axis end position of a horizontal pattern line in pixel unit
 * @param   ypos[in]            y position of a horizontal pattern line
 **********************************************************************************************************************/
VOID _gx_dave2d_horizontal_pattern_line_draw_888 (GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic 32bpp horizontal pattern line draw routine. */
    _gx_display_driver_32bpp_horizontal_pattern_line_draw(context, xstart, xend, ypos);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, vertical pattern draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a vertical pattern line for RGB565 color format.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   ystart[in]          y axis start position of a vertical pattern line in pixel unit
 * @param   yend[in]            y axis end position of a vertical pattern line in pixel unit
 * @param   xpos[in]            x position of a vertical pattern line
 **********************************************************************************************************************/
VOID _gx_dave2d_vertical_pattern_line_draw_565 (GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic 16bpp vertical pattern line draw routine. */
    _gx_display_driver_16bpp_vertical_pattern_line_draw(context, ystart, yend, xpos);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, vertical pattern draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a vertical pattern line for RGB888 color format.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   ystart[in]          y axis start position of a vertical pattern line in pixel unit
 * @param   yend[in]            y axis end position of a vertical pattern line in pixel unit
 * @param   xpos[in]            x position of a vertical pattern line
 **********************************************************************************************************************/
VOID _gx_dave2d_vertical_pattern_line_draw_888 (GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos)
{
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic 32bpp vertical pattern line draw routine. */
    _gx_display_driver_32bpp_vertical_pattern_line_draw(context, ystart, yend, xpos);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, anti-aliased wide line draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw an anti-aliased wide line.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          x axis start position of an anti-aliased wide line in pixel unit
 * @param   ystart[in]          y axis start position of an anti-aliased wide line in pixel unit
 * @param   xend[in]            x axis end position of an anti-aliased wide line in pixel unit
 * @param   yend[in]            y axis end position of an anti-aliased wide line in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_aliased_wide_line (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    d2_device * dave  = gx_dave2d_context_clip_set(context);
    GX_BRUSH  * brush = &context->gx_draw_context_brush;

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_render_mode_set(dave, d2_rm_solid);
    gx_dave2d_anti_aliasing_set(dave, 1);
    gx_dave2d_color0_set(dave, context->gx_draw_context_brush.gx_brush_line_color);

    if (brush->gx_brush_style & GX_BRUSH_ROUND)
    {
        gx_dave2d_line_cap_set(dave, d2_lc_round);
    }
    else
    {
        gx_dave2d_line_cap_set(dave, d2_lc_butt);
    }

    CHECK_DAVE_STATUS(d2_renderline(dave, (d2_point) (D2_FIX4((USHORT) xstart)), (d2_point) (D2_FIX4((USHORT) ystart)),
                                    (d2_point) (D2_FIX4((USHORT) xend)), (d2_point) (D2_FIX4((USHORT) yend)),
                                    (d2_width) (D2_FIX4((USHORT) brush->gx_brush_width)), d2_le_exclude_none))

    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  Sine function optimized for use with D/AVE 2D d2_s32 16:16 fixed point type.
 * @param   angle[in]         Angle in whole degrees
 **********************************************************************************************************************/
static d2_s32 gx_dave2d_fast_sin (INT angle)
{
    /* Put angle in 0-359 range */
    while (angle < 0)
    {
        angle += 360;
    }

    while (angle >= 360)
    {
        angle -= 360;
    }

    /* Get sign of result */
    int32_t sign = 1;
    if (angle >= 180)
    {
        sign  *= -1;
        angle -= 180;
    }

    int32_t sin_val;

    /* Handle multiples of 90 degrees quickly but retrieve all others from look-up table */
    if (!angle || (angle == 90))
    {
        sin_val = ((int32_t) (angle > 0)) << 16;
    }
    else if (angle > 90)
    {
        sin_val = d2_sin_lut[180 - angle];
    }
    else
    {
        sin_val = d2_sin_lut[angle];
    }

    return (d2_s32) (sin_val * sign);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 16bpp pixelmap rotate function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a rotated pixelmap. 8bpp, 16bpp, and 32 bpp source formats are supported.
 *
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            x-coordinate of top-left draw point in pixel unit
 * @param   ypos[in]            y-coordinate of top-left draw point in pixel unit
 * @param   pixelmap[in]        Pointer to a GX_PIXELMAP structure
 * @param   angle[in]           The angle to rotate
 * @param   rot_cx[in]          x-coordinate of rotating center
 * @param   rot_cy[in]          y-coordinate of rotating center
 **********************************************************************************************************************/
VOID _gx_dave2d_pixelmap_rotate_16bpp (GX_DRAW_CONTEXT * context,
                                       INT               xpos,
                                       INT               ypos,
                                       GX_PIXELMAP     * pixelmap,
                                       INT               angle,
                                       INT               rot_cx,
                                       INT               rot_cy)
{
    GX_DISPLAY * display;

    display = context->gx_draw_context_display;

    angle = angle % 360;

    if (angle < 0)
    {
        angle += 360;
    }

    if (angle == 0)
    {
        if (display->gx_display_driver_pixelmap_draw)
        {
            display->gx_display_driver_pixelmap_draw(context, xpos, ypos, pixelmap);

            return;
        }
    }

    d2_u32      mode;
    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    mode = gx_dave2d_format_set(pixelmap);

    if ((mode & d2_mode_clut) == d2_mode_clut)
    {
        CHECK_DAVE_STATUS(d2_settexclut(dave, (d2_color *) pixelmap->gx_pixelmap_aux_data))
    }

    CHECK_DAVE_STATUS(d2_settexture(dave, (void *) pixelmap->gx_pixelmap_data, pixelmap->gx_pixelmap_width,
                                    pixelmap->gx_pixelmap_width, pixelmap->gx_pixelmap_height, mode))

    /* Set texture mode to apply bilinear filtering */
    CHECK_DAVE_STATUS(d2_settexturemode(dave, d2_tm_filter))

    /* Use alpha if supported by the pixelmap */
    d2_u8 alpha_mode =
        (pixelmap->gx_pixelmap_flags & (GX_PIXELMAP_ALPHA | GX_PIXELMAP_TRANSPARENT)) ? d2_to_copy : d2_to_one;
    CHECK_DAVE_STATUS(d2_settextureoperation(dave, alpha_mode, d2_to_copy, d2_to_copy, d2_to_copy))

    /* Set pixel center for mapped texture */
    CHECK_DAVE_STATUS(d2_settexelcenter(dave, 0, 0))

    struct st_d2_coord
    {
        d2_point x;
        d2_point y;
    };
    struct st_d2_coord coords[4] =
    {
        {
            .x = (short) xpos,
            .y = (short) ypos,
        },
        {
            .x = (short) (xpos + pixelmap->gx_pixelmap_width),
            .y = (short) ypos,
        },
        {
            .x = (short) (xpos + pixelmap->gx_pixelmap_width),
            .y = (short) (ypos + pixelmap->gx_pixelmap_height),
        },
        {
            .x = (short) xpos,
            .y = (short) (ypos + pixelmap->gx_pixelmap_height),
        },
    };

    /* Pre-calculate the sine and cosine values for the supplied angle using a look-up table */
    int32_t sine   = gx_dave2d_fast_sin(angle);
    int32_t cosine = gx_dave2d_fast_sin(angle + 90);

    INT rot_cx_adj = rot_cx + coords[0].x;
    INT rot_cy_adj = rot_cy + coords[0].y;

    /* Rotate corner points around center point
     *
     *   x, y: Original point
     *   cx, cy: Center point
     *   x', y': Final point rotated clockwise
     *
     *   x' = cos(theta) * (x-cx) - sin(theta) * (y-cy) + cx
     *   y' = sin(theta) * (x-cx) + cos(theta) * (y-cy) + cy
     */
    for (uint32_t i = 0; i < 4; i++)
    {
        INT x_adj = coords[i].x - rot_cx_adj;
        INT y_adj = coords[i].y - rot_cy_adj;

        coords[i].x = (d2_point) ((((cosine * x_adj) - (sine * y_adj)) >> 12) + (rot_cx_adj << 4));
        coords[i].y = (d2_point) ((((sine * x_adj) + (cosine * y_adj)) >> 12) + (rot_cy_adj << 4));
    }

    /* Set rotated texture mapping at the 'upper-left' coordinate
     *
     * Explanation:
     * ux, uy, vx and vy are multipliers that correspond to the pixel offset to reference in the mapped texture.
     * ux and uy are the multipliers for movement in the X direction, vx and vy for Y movement. For example, consider
     * the following settings:
     *
     *   ux, uy = 1, 0
     *   vx, vy = 0, 1
     *
     * (NOTE: These values are supplied to the function in 16:16 fixed-point notation but are shown in decimal form here
     * for clarity.)
     *
     * In this case, each time the renderer moves one pixel to the right on the frame buffer, the texture unit will
     * read one texel to the right on the texture. Likewise, one pixel down on the framebuffer is one texel down on the
     * texture. Now, consider the following settings:
     *
     *   ux, uy = 0.866, 0.5   ( cos(30), sin(30))
     *   vx, vy =  -0.5, 0.866 (-sin(30), cos(30))
     *
     * Now when moving one buffer pixel to the right the texture unit will move 0.866 texels to the right and 0.5 texels
     * down, and when moving one buffer pixel down the texture unit will move 0.5 texels to the left and 0.866 texels
     * down. This corresponds to a 30-degree clockwise rotation of the texture.
     *
     * For reference, the values for any given (clockwise) angle are:
     *
     *   ux = cos(angle)
     *   uy = sin(angle)
     *   vx = -sin(angle)
     *   vy = cos(angle)
     */
    CHECK_DAVE_STATUS(d2_settexturemapping(dave, coords[0].x, coords[0].y, 0, 0, cosine, sine, -1 * sine, cosine))

    /* Enable or Disable anti-aliasing based on the brush style */
    if (context->gx_draw_context_brush.gx_brush_style & GX_BRUSH_ALIAS)
    {
        gx_dave2d_anti_aliasing_set(dave, 1);
    }
    else
    {
        gx_dave2d_anti_aliasing_set(dave, 0);
    }

    /* Render a quad over the mapped texture to draw it to the buffer */
    gx_dave2d_render_mode_set(dave, d2_rm_solid);
    gx_dave2d_fill_mode_set(dave, d2_fm_texture);
    CHECK_DAVE_STATUS(d2_renderquad(dave, coords[0].x, coords[0].y, coords[1].x, coords[1].y, coords[2].x, coords[2].y,
                                    coords[3].x, coords[3].y, 0))

    /** Check if pixelmap is dynamically allocated. */
    if (pixelmap->gx_pixelmap_flags & GX_PIXELMAP_DYNAMICALLY_ALLOCATED)
    {
        /** Flush D/AVE 2D display list first to insure order of operation. */
        gx_display_list_flush(context->gx_draw_context_display);

        /** Open next display list before we go. */
        gx_display_list_open(context->gx_draw_context_display);
    }
    else
    {
        /** Count the used display list size. */
        gx_dave2d_display_list_count(context->gx_draw_context_display);
    }
}

/*******************************************************************************************************************//**
 * @brief  Subfunction to draw a pixelmap.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   x[in]              X-coordinate
 * @param   y[in]              Y-coordinate
 * @param   pixelmap[in]       Pointer to pixelmap
 * @param   alpha[in]          Pixelmap alpha
 **********************************************************************************************************************/
static VOID gx_dave2d_pixelmap_draw (GX_DRAW_CONTEXT * context,
                                     INT               xpos,
                                     INT               ypos,
                                     GX_PIXELMAP     * pixelmap,
                                     GX_UBYTE          alpha)
{
    d2_u32      mode = gx_dave2d_format_set(pixelmap);
    d2_device * dave = gx_dave2d_context_clip_set(context);

    gx_dave2d_alpha_set(dave, alpha);

    if (pixelmap->gx_pixelmap_flags & GX_PIXELMAP_COMPRESSED)
    {
        mode |= d2_mode_rle;
    }

    if ((mode & d2_mode_clut) == d2_mode_clut)
    {
        CHECK_DAVE_STATUS(d2_settexclut(dave, (d2_color *) pixelmap->gx_pixelmap_aux_data))
    }

    GX_VALUE width;
    GX_VALUE height;

    /* Swap width and height if image was generated in a rotated orientation */
    if (pixelmap->gx_pixelmap_flags & (GX_PIXELMAP_ROTATED_CW | GX_PIXELMAP_ROTATED_CCW))
    {
        width  = pixelmap->gx_pixelmap_height;
        height = pixelmap->gx_pixelmap_width;
    }
    else
    {
        width  = pixelmap->gx_pixelmap_width;
        height = pixelmap->gx_pixelmap_height;
    }

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) pixelmap->gx_pixelmap_data, width, width, height, mode))

    mode = (d2_u32) d2_bf_no_blitctxbackup;

    if ((pixelmap->gx_pixelmap_flags & GX_PIXELMAP_TRANSPARENT) || (pixelmap->gx_pixelmap_flags & GX_PIXELMAP_ALPHA))
    {
        mode |= (d2_u32) d2_bf_usealpha;
    }

    CHECK_DAVE_STATUS(d2_blitcopy(dave, width, height, 0, 0, (d2_width) (D2_FIX4((USHORT) width)),
                                  (d2_width) (D2_FIX4((USHORT) height)), (d2_point) (D2_FIX4((USHORT) xpos)),
                                  (d2_point) (D2_FIX4((USHORT) ypos)),
                                  mode))

    /** Reset the alpha value. */
    gx_dave2d_alpha_set(dave, (UCHAR) GX_ALPHA_VALUE_OPAQUE);

    /** Check pixelmap is dynamically allocated. */
    if (pixelmap->gx_pixelmap_flags & GX_PIXELMAP_DYNAMICALLY_ALLOCATED)
    {
        /** Flush D/AVE 2D display list first to insure order of operation. */
        gx_display_list_flush(context->gx_draw_context_display);

        /** Open next display list before we go. */
        gx_display_list_open(context->gx_draw_context_display);
    }
    else
    {
        /** Count the used display list size. */
        gx_dave2d_display_list_count(context->gx_draw_context_display);
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, pixelmap draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a pixelmap. Currently 8bpp, 16bpp, and 32 bpp source formats are supported.
 * RLE compression is available as an option.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            x axis position of a pixelmap in pixel unit
 * @param   ypos[in]            y axis position of a pixelmap in pixel unit
 * @param   pixelmap[in]        Pointer to a pixelmap
 **********************************************************************************************************************/
VOID _gx_dave2d_pixelmap_draw (GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap)
{
 #if defined(GX_BRUSH_ALPHA_SUPPORT)
    GX_UBYTE brush_alpha = context->gx_draw_context_brush.gx_brush_alpha;

    if (brush_alpha == 0U)
    {
        return;
    }

    if ((GX_UBYTE) GX_ALPHA_VALUE_OPAQUE != brush_alpha)
    {
        gx_dave2d_pixelmap_draw(context, xpos, ypos, pixelmap, brush_alpha);

        return;
    }
 #endif

    /** Draw pixelmap */
    gx_dave2d_pixelmap_draw(context, xpos, ypos, pixelmap, GX_ALPHA_VALUE_OPAQUE);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, pixelmap alpha-blend function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to alpha-blend a pixelmap.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            x axis position of a pixelmap in pixel unit
 * @param   ypos[in]            y axis position of a pixelmap in pixel unit
 * @param   pixelmap[in]        Pointer to a pixelmap
 * @param   alpha[in]           GUIX alpha value
 **********************************************************************************************************************/
VOID _gx_dave2d_pixelmap_blend (GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap, GX_UBYTE alpha)
{
    if (0U == alpha)
    {
        return;
    }

    /** Blend pixelmap */
    gx_dave2d_pixelmap_draw(context, xpos, ypos, pixelmap, alpha);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, horizontal pixelmap line draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a horizontal pixelmap.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            x axis position of a pixelmap in pixel unit
 * @param   ypos[in]            y axis position of a pixelmap in pixel unit
 * @param   xstart[in]          x axis start position of a horizontal pixelmap line in pixel unit
 * @param   xend[in]            x axis end position of a horizontal pixelmap line in pixel unit
 * @param   y[in]               y axis position of a horizontal pixelmap line in pixel unit
 * @param   pixelmap[in]        Pointer to a pixelmap
 **********************************************************************************************************************/
VOID _gx_dave2d_horizontal_pixelmap_line_draw (GX_DRAW_CONTEXT       * context,
                                               INT                     xstart,
                                               INT                     xend,
                                               INT                     y,
                                               GX_FILL_PIXELMAP_INFO * info)
{
    GX_RECTANGLE * old_clip;
    GX_RECTANGLE   clip;
    GX_PIXELMAP  * pixelmap = info->pixelmap;
    INT            xpos;
    INT            ypos;

    if ((info->draw) && (xstart <= xend))
    {
        old_clip = context->gx_draw_context_clip;
        context->gx_draw_context_clip = &clip;

        xpos = xstart - (info->x_offset % pixelmap->gx_pixelmap_width);
        ypos = y - info->y_offset;

        clip.gx_rectangle_left   = (GX_VALUE) xstart;
        clip.gx_rectangle_right  = (GX_VALUE) xend;
        clip.gx_rectangle_top    = (GX_VALUE) y;
        clip.gx_rectangle_bottom = (GX_VALUE) y;

        while (xstart <= xend)
        {
            clip.gx_rectangle_left = (GX_VALUE) xstart;

            /** Draw pixelmap. */
            _gx_dave2d_pixelmap_draw(context, xpos, ypos, pixelmap);

            xpos  += pixelmap->gx_pixelmap_width;
            xstart = xpos;
        }

        context->gx_draw_context_clip = old_clip;
    }

    info->y_offset++;
    if (info->y_offset >= pixelmap->gx_pixelmap_height)
    {
        info->y_offset = 0;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, polygon draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw a polygon.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   vertex[in]          Pointer to GUIX point data
 * @param   num[in]             Number of points
 **********************************************************************************************************************/
VOID _gx_dave2d_polygon_draw (GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num)
{
    INT        index = 0;
    d2_point   data[MAX_POLYGON_VERTICES * 2] = {0};
    GX_BRUSH * brush = &context->gx_draw_context_brush;

    /** Return to caller if brush width is 0. */
    if (brush->gx_brush_width < 1)
    {
        return;
    }

    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    /** Convert incoming point data to d2_point type. */
    for (INT loop = 0; loop < num; loop++)
    {
        data[index++] = (d2_point) (D2_FIX4((USHORT) vertex[loop].gx_point_x));
        data[index++] = (d2_point) (D2_FIX4((USHORT) vertex[loop].gx_point_y));
    }

    gx_dave2d_render_mode_set(dave, d2_rm_outline);
    gx_dave2d_outline_width_set(dave, (GX_FIXED_VAL) (((USHORT) brush->gx_brush_width << GX_FIXED_VAL_SHIFT)));
    gx_dave2d_fill_mode_set(dave, d2_fm_color);

    /** Enable or Disable anti-aliasing based on the brush style set. */
    if (brush->gx_brush_style & GX_BRUSH_ALIAS)
    {
        gx_dave2d_anti_aliasing_set(dave, 1);
    }
    else
    {
        gx_dave2d_anti_aliasing_set(dave, 0);
    }

    if (brush->gx_brush_style & GX_BRUSH_ROUND)
    {
        gx_dave2d_line_join_set(dave, d2_lj_round);
    }
    else
    {
        gx_dave2d_line_join_set(dave, d2_lj_miter);
    }

    gx_dave2d_color0_set(dave, brush->gx_brush_line_color);
    CHECK_DAVE_STATUS(d2_renderpolygon(dave, (d2_point *) data, (d2_u32) num, 0))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, polygon fill function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to fill a polygon.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   vertex[in]          Pointer to GUIX point data
 * @param   num[in]             Number of points
 **********************************************************************************************************************/
VOID _gx_dave2d_polygon_fill (GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num)
{
    /** Check if polygon to be render is convex polygon. */
    if (!gx_dave2d_convex_polygon_test(vertex, num))
    {
        /** Flush D/AVE 2D display list first to insure order of operation. */
        gx_display_list_flush(context->gx_draw_context_display);

        /** Open next display list before we go. */
        gx_display_list_open(context->gx_draw_context_display);

        /** Call the GUIX generic polygon fill function. */
        _gx_display_driver_generic_polygon_fill(context, vertex, num);

        return;
    }

    INT        index = 0;
    d2_point   data[MAX_POLYGON_VERTICES * 2] = {0};
    GX_BRUSH * brush = &context->gx_draw_context_brush;

    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    /** Convert incoming point data to d2_point type. */
    for (INT loop = 0; loop < num; loop++)
    {
        data[index++] = (d2_point) (D2_FIX4((USHORT) vertex[loop].gx_point_x));
        data[index++] = (d2_point) (D2_FIX4((USHORT) vertex[loop].gx_point_y));
    }

    gx_dave2d_render_mode_set(dave, d2_rm_solid);

    if (brush->gx_brush_style & GX_BRUSH_PIXELMAP_FILL)
    {
        gx_dave2d_fill_mode_set(dave, d2_fm_texture);
        gx_dave2d_set_texture(context,
                              dave,
                              context->gx_draw_context_clip->gx_rectangle_left,
                              context->gx_draw_context_clip->gx_rectangle_top,
                              brush->gx_brush_pixelmap);
    }
    else
    {
        gx_dave2d_fill_mode_set(dave, (d2_u32) d2_fm_color);
        gx_dave2d_color0_set(dave, brush->gx_brush_fill_color);
    }

    CHECK_DAVE_STATUS(d2_renderpolygon(dave, (d2_point *) data, (d2_u32) num, 0))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, pixel write function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to write a pixel for RGB565 color formats. Although D/AVE 2D acceleration
 * enabled, the GUIX generic pixel write routine is used since there is no performance benefit for single pixel write
 * operation.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               x position in pixel unit
 * @param   y[in]               y position in pixel unit
 * @param   color[in]           GUIX color data
 **********************************************************************************************************************/
VOID _gx_dave2d_pixel_write_565 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic 16bpp pixel write routine. */
    _gx_display_driver_16bpp_pixel_write(context, x, y, color);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, pixel write function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to write a pixel for 32-bit ARGB color formats. Although D/AVE 2D acceleration
 * enabled, the GUIX generic pixel write routine is used since there is no performance benefit for single pixel write
 * operation.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               x position in pixel unit
 * @param   y[in]               y position in pixel unit
 * @param   color[in]           GUIX color data
 **********************************************************************************************************************/
VOID _gx_dave2d_pixel_write_888 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic RGB888 pixel write routine. */
    _gx_display_driver_32bpp_pixel_write(context, x, y, color);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, pixel blend function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to blend a pixel for RGB565 color formats. Although D/AVE 2D acceleration
 * enabled, the GUIX generic pixel blend routine is used since there is no performance benefit for single pixel blend
 * operation.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               x position in pixel unit
 * @param   y[in]               y position in pixel unit
 * @param   fcolor[in]          GUIX color data
 * @param   alpha[in]           Alpha value
 **********************************************************************************************************************/
VOID _gx_dave2d_pixel_blend_565 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic RGB565 pixel blend routine. */
    _gx_display_driver_565rgb_pixel_blend(context, x, y, fcolor, alpha);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, pixel blend function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to blend a pixel for 32-bit ARGB color formats. Although D/AVE 2D acceleration
 * enabled, the GUIX generic pixel blend routine is used since there is no performance benefit for single pixel blend
 * operation.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               x position in pixel unit
 * @param   y[in]               y position in pixel unit
 * @param   fcolor[in]          GUIX color data
 * @param   alpha[in]           Alpha value
 **********************************************************************************************************************/
VOID _gx_dave2d_pixel_blend_888 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Call the GUIX generic 32ARGB pixel blend routine. */
    _gx_display_driver_32argb_pixel_blend(context, x, y, fcolor, alpha);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, block move function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to move a block of pixels within a working canvas memory. Mainly used for fast scrolling.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   block[in]           Pointer to a block to be moved
 * @param   xshift[in]          x axis shift in pixel unit
 * @param   yshift[in]          y axis shift in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_block_move (GX_DRAW_CONTEXT * context, GX_RECTANGLE * block, INT xshift, INT yshift)
{
    d2_device * dave = gx_dave2d_context_clip_set(context);

    INT width  = (block->gx_rectangle_right - block->gx_rectangle_left) + 1;
    INT height = (block->gx_rectangle_bottom - block->gx_rectangle_top) + 1;

    CHECK_DAVE_STATUS(d2_utility_fbblitcopy(dave, (d2_u16) width, (d2_u16) height,
                                            (d2_blitpos) (block->gx_rectangle_left),
                                            (d2_blitpos) (block->gx_rectangle_top),
                                            (d2_blitpos) (block->gx_rectangle_left + xshift),
                                            (d2_blitpos) (block->gx_rectangle_top + yshift),
                                            d2_bf_no_blitctxbackup))
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, alpha-map draw draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw alpha-map.
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            x axis position in pixel unit
 * @param   ypos[in]            y axis position in pixel unit
 * @param   pixelmap[in]        Pointer to pixelmap data
 **********************************************************************************************************************/
VOID _gx_dave2d_alphamap_draw (GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap)
{
    d2_u32 mode;

    mode = d2_mode_alpha8;

    if (pixelmap->gx_pixelmap_flags & GX_PIXELMAP_COMPRESSED)
    {
        mode |= d2_mode_rle;
    }

    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) pixelmap->gx_pixelmap_data, pixelmap->gx_pixelmap_width,
                                    pixelmap->gx_pixelmap_width, pixelmap->gx_pixelmap_height, mode))

    mode = (d2_u32) d2_bf_usealpha | (d2_u32) d2_bf_colorize | (d2_u32) d2_bf_no_blitctxbackup;

    gx_dave2d_color0_set(dave, context->gx_draw_context_brush.gx_brush_fill_color);

    CHECK_DAVE_STATUS(d2_blitcopy(dave, pixelmap->gx_pixelmap_width, pixelmap->gx_pixelmap_height, 0, 0,
                                  (d2_width) (D2_FIX4((USHORT) (pixelmap->gx_pixelmap_width))),
                                  (d2_width) (D2_FIX4((USHORT) (pixelmap->gx_pixelmap_height))),
                                  (d2_point) (D2_FIX4((USHORT) xpos)),
                                  (d2_point) (D2_FIX4((USHORT) ypos)), mode))

    /** Check pixelmap is dynamically allocated. */
    if (pixelmap->gx_pixelmap_flags & GX_PIXELMAP_DYNAMICALLY_ALLOCATED)
    {
        /** Flush D/AVE 2D display list first to insure order of operation. */
        gx_display_list_flush(context->gx_draw_context_display);

        /** Open next display list before we go. */
        gx_display_list_open(context->gx_draw_context_display);
    }
    else
    {
        /** Count the used display list size. */
        gx_dave2d_display_list_count(context->gx_draw_context_display);
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8-bit compressed glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw 8-bit compressed glyph.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the draw rectangle area
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_compressed_glyph_8bit_draw (GX_DRAW_CONTEXT * context,
                                            GX_RECTANGLE    * draw_area,
                                            GX_POINT        * map_offset,
                                            const GX_GLYPH  * glyph)
{
    d2_u32                mode = 0;
    GX_COMPRESSED_GLYPH * compressed_glyph;

    compressed_glyph = (GX_COMPRESSED_GLYPH *) glyph;
    if (compressed_glyph->gx_glyph_map_size & 0x8000)
    {
        mode |= d2_mode_rle;
    }

    gx_dave2d_glyph_8bit_draw(context, draw_area, map_offset, glyph, mode);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8-bit raw glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw 8-bit raw glyph.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the draw rectangle area
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_raw_glyph_8bit_draw (GX_DRAW_CONTEXT * context,
                                     GX_RECTANGLE    * draw_area,
                                     GX_POINT        * map_offset,
                                     const GX_GLYPH  * glyph)
{
    gx_dave2d_glyph_8bit_draw(context, draw_area, map_offset, glyph, 0);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 4-bit compressed glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw 4-bit compressed glyph.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the draw rectangle area
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_compressed_glyph_4bit_draw (GX_DRAW_CONTEXT * context,
                                            GX_RECTANGLE    * draw_area,
                                            GX_POINT        * map_offset,
                                            const GX_GLYPH  * glyph)
{
    d2_u32                mode = 0;
    GX_COMPRESSED_GLYPH * compressed_glyph;

    compressed_glyph = (GX_COMPRESSED_GLYPH *) glyph;
    if (compressed_glyph->gx_glyph_map_size & 0x8000)
    {
        mode |= d2_mode_rle;
    }

    gx_dave2d_glyph_4bit_draw(context, draw_area, map_offset, glyph, mode);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 4-bit raw glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw 4-bit raw glyph.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the draw rectangle area
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_raw_glyph_4bit_draw (GX_DRAW_CONTEXT * context,
                                     GX_RECTANGLE    * draw_area,
                                     GX_POINT        * map_offset,
                                     const GX_GLYPH  * glyph)
{
    gx_dave2d_glyph_4bit_draw(context, draw_area, map_offset, glyph, 0);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 1-bit compressed glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw 1-bit compressed glyph.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the draw rectangle area
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_compressed_glyph_1bit_draw (GX_DRAW_CONTEXT * context,
                                            GX_RECTANGLE    * draw_area,
                                            GX_POINT        * map_offset,
                                            const GX_GLYPH  * glyph)
{
    d2_u32                mode = 0;
    GX_COMPRESSED_GLYPH * compressed_glyph;

    compressed_glyph = (GX_COMPRESSED_GLYPH *) glyph;
    if (compressed_glyph->gx_glyph_map_size & 0x8000)
    {
        mode |= d2_mode_rle;
    }

    gx_dave2d_glyph_1bit_draw(context, draw_area, map_offset, glyph, mode);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 1-bit raw glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw 1-bit raw glyph.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the draw rectangle area
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_raw_glyph_1bit_draw (GX_DRAW_CONTEXT * context,
                                     GX_RECTANGLE    * draw_area,
                                     GX_POINT        * map_offset,
                                     const GX_GLYPH  * glyph)
{
    gx_dave2d_glyph_1bit_draw(context, draw_area, map_offset, glyph, 0);
}

 #if defined(GX_ARC_DRAWING_SUPPORT)

/*******************************************************************************************************************//**
 * @brief  Subfunction to draw a circle.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 * @param   aa[in]             Whether to apply anti-aliasing
 **********************************************************************************************************************/
VOID gx_dave2d_circle_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, bool aa)
{
    GX_BRUSH * brush = &context->gx_draw_context_brush;

    /** Return to caller if brush width is 0. */
    if (brush->gx_brush_width < 1)
    {
        return;
    }

    if (r < (UINT) ((brush->gx_brush_width + 1) / 2))
    {
        r = 0U;
    }
    else
    {
        r = (UINT) (r - (UINT) ((brush->gx_brush_width + 1) / 2));
    }

    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_anti_aliasing_set(dave, aa);
    gx_dave2d_render_mode_set(dave, d2_rm_outline);
    gx_dave2d_outline_width_set(dave, (GX_FIXED_VAL) (((USHORT) brush->gx_brush_width << GX_FIXED_VAL_SHIFT)));
    gx_dave2d_color0_set(dave, brush->gx_brush_line_color);
    gx_dave2d_fill_mode_set(dave, d2_fm_color);

    CHECK_DAVE_STATUS(d2_rendercircle(dave, (d2_point) (D2_FIX4((USHORT) xcenter)),
                                      (d2_point) (D2_FIX4((USHORT) ycenter)), (d2_width) (D2_FIX4((USHORT) r)), 0))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, anti-aliased circle outline draw function with D/AVE 2D acceleration
 * enabled. This function is called by GUIX to render anti-aliased circle outline.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_aliased_circle_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r)
{
    gx_dave2d_circle_draw(context, xcenter, ycenter, r, true);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, aliased circle outline draw function with D/AVE 2D acceleration
 * enabled. This function is called by GUIX to render aliased circle outline.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_circle_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r)
{
    gx_dave2d_circle_draw(context, xcenter, ycenter, r, false);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, circle fill function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to fill circle.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 **********************************************************************************************************************/
VOID _gx_dave2d_circle_fill (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r)
{
    GX_BRUSH * brush       = &context->gx_draw_context_brush;
    GX_COLOR   brush_color = brush->gx_brush_fill_color;

    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    /** Enable or Disable anti-aliasing based on the brush style set. */
    if (brush->gx_brush_style & GX_BRUSH_ALIAS)
    {
        gx_dave2d_anti_aliasing_set(dave, 1);
    }
    else
    {
        gx_dave2d_anti_aliasing_set(dave, 0);
    }

    gx_dave2d_render_mode_set(dave, d2_rm_solid);

    if (brush->gx_brush_style & GX_BRUSH_PIXELMAP_FILL)
    {
        gx_dave2d_fill_mode_set(dave, d2_fm_texture);
        gx_dave2d_set_texture(context, dave, xcenter - (INT) r, ycenter - (INT) r, brush->gx_brush_pixelmap);
    }
    else
    {
        gx_dave2d_fill_mode_set(dave, d2_fm_color);
        gx_dave2d_color0_set(dave, brush_color);
    }

    CHECK_DAVE_STATUS(d2_rendercircle(dave, (d2_point) (D2_FIX4((USHORT) xcenter)),
                                      (d2_point) (D2_FIX4((USHORT) ycenter)), (d2_width) (D2_FIX4((USHORT) r)), 0))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, pie fill function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to fill pie.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 * @param   start_angle[in]    Start angle in degree
 * @param   end_angle[in]      End angle in degree
 **********************************************************************************************************************/
VOID _gx_dave2d_pie_fill (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle)
{
    GX_BRUSH  * brush = &context->gx_draw_context_brush;
    INT         sin1;
    INT         cos1;
    INT         sin2;
    INT         cos2;
    d2_u32      flags;
    d2_device * dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    INT s_angle = -start_angle;
    INT e_angle = -end_angle;

    sin1 = (INT) _gx_utility_math_sin((GX_FIXED_VAL) ((UINT) (s_angle - 90) << GX_FIXED_VAL_SHIFT));
    cos1 = (INT) _gx_utility_math_cos((GX_FIXED_VAL) ((UINT) (s_angle - 90) << GX_FIXED_VAL_SHIFT));

    sin2 = (INT) _gx_utility_math_sin((GX_FIXED_VAL) ((UINT) (e_angle + 90) << GX_FIXED_VAL_SHIFT));
    cos2 = (INT) _gx_utility_math_cos((GX_FIXED_VAL) ((UINT) (e_angle + 90) << GX_FIXED_VAL_SHIFT));

    /** Set d2_wf_concave flag if the pie object to draw is concave shape. */
    if (((s_angle - e_angle) > 180) || ((s_angle - e_angle) < 0))
    {
        flags = d2_wf_concave;
    }
    else
    {
        flags = 0;
    }

    /** Enable or Disable anti-aliasing based on the brush style set. */
    if (brush->gx_brush_style & GX_BRUSH_ALIAS)
    {
        gx_dave2d_anti_aliasing_set(dave, 1);
    }
    else
    {
        gx_dave2d_anti_aliasing_set(dave, 0);
    }

    gx_dave2d_render_mode_set(dave, d2_rm_solid);

    if (brush->gx_brush_style & GX_BRUSH_PIXELMAP_FILL)
    {
        gx_dave2d_fill_mode_set(dave, d2_fm_texture);
        gx_dave2d_set_texture(context, dave, xcenter - (INT) r, ycenter - (INT) r, brush->gx_brush_pixelmap);
    }
    else
    {
        gx_dave2d_fill_mode_set(dave, d2_fm_color);
        gx_dave2d_color0_set(dave, brush->gx_brush_fill_color);
    }

    CHECK_DAVE_STATUS(d2_renderwedge(dave, (d2_point) (D2_FIX4((USHORT) xcenter)),
                                     (d2_point) (D2_FIX4((USHORT) ycenter)), (d2_width) (D2_FIX4((USHORT) (r + 1))), 0,
                                     (d2_s32) ((UINT) cos1 << 6),
                                     (d2_s32) ((UINT) sin1 << 6), (d2_s32) ((UINT) cos2 << 6),
                                     (d2_s32) ((UINT) sin2 << 6), flags))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, anti-aliased arc draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw anti-aliased arc.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 * @param   start_angle[in]    Start angle in degree
 * @param   end_angle[in]      End angle in degree
 **********************************************************************************************************************/
VOID _gx_dave2d_aliased_arc_draw (GX_DRAW_CONTEXT * context,
                                  INT               xcenter,
                                  INT               ycenter,
                                  UINT              r,
                                  INT               start_angle,
                                  INT               end_angle)
{
    GX_BRUSH  * brush;
    INT         sin1;
    INT         cos1;
    INT         sin2;
    INT         cos2;
    d2_u32      flags;
    d2_device * dave;

    brush = &context->gx_draw_context_brush;

    if (brush->gx_brush_width < 1)
    {
        return;
    }

    dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    INT s_angle = -start_angle;
    INT e_angle = -end_angle;

    sin1 = (INT) _gx_utility_math_sin((GX_FIXED_VAL) ((UINT) (s_angle - 90) << GX_FIXED_VAL_SHIFT));
    cos1 = (INT) _gx_utility_math_cos((GX_FIXED_VAL) ((UINT) (s_angle - 90) << GX_FIXED_VAL_SHIFT));

    sin2 = (INT) _gx_utility_math_sin((GX_FIXED_VAL) ((UINT) (e_angle + 90) << GX_FIXED_VAL_SHIFT));
    cos2 = (INT) _gx_utility_math_cos((GX_FIXED_VAL) ((UINT) (e_angle + 90) << GX_FIXED_VAL_SHIFT));

    /** Set d2_wf_concave flag if the pie object to draw is concave shape. */
    if (((s_angle - e_angle) > 180) || ((s_angle - e_angle) < 0))
    {
        flags = d2_wf_concave;
    }
    else
    {
        flags = 0;
    }

    gx_dave2d_anti_aliasing_set(dave, 1);
    gx_dave2d_render_mode_set(dave, d2_rm_outline);
    gx_dave2d_outline_width_set(dave,
                                (GX_FIXED_VAL) ((ULONG) ((USHORT) brush->gx_brush_width << GX_FIXED_VAL_SHIFT) >> 1));
    gx_dave2d_color0_set(dave, brush->gx_brush_line_color);
    gx_dave2d_fill_mode_set(dave, d2_fm_color);

    CHECK_DAVE_STATUS(d2_renderwedge(dave, (d2_point) (D2_FIX4((USHORT) xcenter)),
                                     (d2_point) (D2_FIX4((USHORT) ycenter)), (d2_width) (D2_FIX4((USHORT) r)), 0,
                                     (d2_s32) ((UINT) cos1 << 6),
                                     (d2_s32) ((UINT) sin1 << 6), (d2_s32) ((UINT) cos2 << 6),
                                     (d2_s32) ((UINT) sin2 << 6), flags))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);

    /** Check if line connection style is circle segment. */
    if (brush->gx_brush_style & GX_BRUSH_ROUND)
    {
        UINT     brush_width = (UINT) brush->gx_brush_width;
        GX_POINT startp      = {0};
        GX_POINT endp        = {0};

        /** Set a rendering mode to solid. */
        gx_dave2d_render_mode_set(dave, d2_rm_solid);

        r = (UINT) (r - (brush_width >> 1));

        /** Get the point on circle with specified angle and radius. */
        _gx_utility_circle_point_get(xcenter, ycenter, r, start_angle, &startp);
        _gx_utility_circle_point_get(xcenter, ycenter, r + brush_width, start_angle, &endp);

        /** Render a circle. */
        CHECK_DAVE_STATUS(d2_rendercircle(dave,
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_x + endp.gx_point_x)) >> 1),
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_y + endp.gx_point_y)) >> 1),
                                          (d2_width) (D2_FIX4(brush_width) >> 1), 0))

        /** Count the used display list size. */
        gx_dave2d_display_list_count(context->gx_draw_context_display);

        /** Get the point on circle with specified angle and radius. */
        _gx_utility_circle_point_get(xcenter, ycenter, r, end_angle, &startp);
        _gx_utility_circle_point_get(xcenter, ycenter, r + brush_width, end_angle, &endp);

        /** Render a circle. */
        CHECK_DAVE_STATUS(d2_rendercircle(dave,
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_x + endp.gx_point_x)) >> 1),
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_y + endp.gx_point_y)) >> 1),
                                          (d2_width) (D2_FIX4(brush_width) >> 1), 0))

        /** Count the used display list size. */
        gx_dave2d_display_list_count(context->gx_draw_context_display);
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, arc draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw arc.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 * @param   start_angle[in]    Start angle in degree
 * @param   end_angle[in]      End angle in degree
 **********************************************************************************************************************/
VOID _gx_dave2d_arc_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle)
{
    GX_BRUSH  * brush = &context->gx_draw_context_brush;
    INT         sin1;
    INT         cos1;
    INT         sin2;
    INT         cos2;
    d2_u32      flags;
    d2_device * dave;

    if (brush->gx_brush_width < 1)
    {
        return;
    }

    dave = gx_dave2d_context_clip_set(context);

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    INT s_angle = -start_angle;
    INT e_angle = -end_angle;

    sin1 = (INT) _gx_utility_math_sin((GX_FIXED_VAL) ((UINT) (s_angle - 90) << GX_FIXED_VAL_SHIFT));
    cos1 = (INT) _gx_utility_math_cos((GX_FIXED_VAL) ((UINT) (s_angle - 90) << GX_FIXED_VAL_SHIFT));

    sin2 = (INT) _gx_utility_math_sin((GX_FIXED_VAL) ((UINT) (e_angle + 90) << GX_FIXED_VAL_SHIFT));
    cos2 = (INT) _gx_utility_math_cos((GX_FIXED_VAL) ((UINT) (e_angle + 90) << GX_FIXED_VAL_SHIFT));

    /** Set d2_wf_concave flag if the pie object to draw is concave shape. */
    if (((s_angle - e_angle) > 180) || ((s_angle - e_angle) < 0))
    {
        flags = d2_wf_concave;
    }
    else
    {
        flags = 0;
    }

    gx_dave2d_anti_aliasing_set(dave, 0);
    gx_dave2d_render_mode_set(dave, d2_rm_outline);
    gx_dave2d_outline_width_set(dave,
                                (GX_FIXED_VAL) ((ULONG) ((USHORT) brush->gx_brush_width << GX_FIXED_VAL_SHIFT) >> 1));
    gx_dave2d_color0_set(dave, brush->gx_brush_line_color);
    gx_dave2d_fill_mode_set(dave, d2_fm_color);

    CHECK_DAVE_STATUS(d2_renderwedge(dave, (d2_point) (D2_FIX4((USHORT) xcenter)),
                                     (d2_point) (D2_FIX4((USHORT) ycenter)), (d2_width) (D2_FIX4((USHORT) r)), 0,
                                     (d2_s32) ((UINT) cos1 << 6),
                                     (d2_s32) ((UINT) sin1 << 6), (d2_s32) ((UINT) cos2 << 6),
                                     (d2_s32) ((UINT) sin2 << 6), flags))

    gx_dave2d_display_list_count(context->gx_draw_context_display);

    /** Check if line connection style is circle segment. */
    if (brush->gx_brush_style & GX_BRUSH_ROUND)
    {
        UINT     brush_width = (UINT) brush->gx_brush_width;
        GX_POINT startp      = {0};
        GX_POINT endp        = {0};

        /** Set a rendering mode to solid. */
        gx_dave2d_render_mode_set(dave, d2_rm_solid);

        r = (UINT) (r - (brush_width >> 1));

        /** Get the point on circle with specified angle and radius. */
        _gx_utility_circle_point_get(xcenter, ycenter, r, start_angle, &startp);
        _gx_utility_circle_point_get(xcenter, ycenter, r + brush_width, start_angle, &endp);

        /** Render a circle. */
        CHECK_DAVE_STATUS(d2_rendercircle(dave,
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_x + endp.gx_point_x)) >> 1),
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_y + endp.gx_point_y)) >> 1),
                                          (d2_width) (D2_FIX4(brush_width) >> 1), 0))

        /** Count the used display list size. */
        gx_dave2d_display_list_count(context->gx_draw_context_display);

        /** Gets the point on circle with specified angle and radius. */
        _gx_utility_circle_point_get(xcenter, ycenter, r, end_angle, &startp);
        _gx_utility_circle_point_get(xcenter, ycenter, r + brush_width, end_angle, &endp);

        /** Render a circle. */
        CHECK_DAVE_STATUS(d2_rendercircle(dave,
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_x + endp.gx_point_x)) >> 1),
                                          (d2_point) (D2_FIX4((USHORT) (startp.gx_point_y + endp.gx_point_y)) >> 1),
                                          (d2_width) (D2_FIX4(brush_width) >> 1), 0))

        /** Count the used display list size. */
        gx_dave2d_display_list_count(context->gx_draw_context_display);
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, arc fill function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to fill arc. Although D/AVE 2D acceleration enabled, arc fill is done by GUIX generic
 * software draw routine because chord (filled arc) operation is not supported by D/AVE 2D.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   r[in]              Radius in pixel unit
 * @param   start_angle[in]    Start angle in degree
 * @param   end_angle[in]      End angle in degree
 **********************************************************************************************************************/
VOID _gx_dave2d_arc_fill (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r, INT start_angle, INT end_angle)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);

    /** Call the GUIX generic arc fill routine. */
    _gx_display_driver_generic_arc_fill(context, xcenter, ycenter, r, start_angle, end_angle);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, anti-aliased ellipse draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw aliased ellipse. Although D/AVE 2D acceleration enabled, ellipse draw is
 * done by GUIX generic software draw routine because the operation is not supported by D/AVE 2D.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   a[in]              Semi-major axis
 * @param   b[in]              Semi-minor axis
 **********************************************************************************************************************/
VOID _gx_dave2d_aliased_ellipse_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    if (context->gx_draw_context_brush.gx_brush_width > 1)
    {
        /** Call the GUIX generic anti-aliased ellipse draw routine if bruch width is more than 1. */
        _gx_display_driver_generic_aliased_wide_ellipse_draw(context, xcenter, ycenter, a, b);
    }
    else
    {
        /** Call the GUIX generic anti-aliased ellipse draw routine if bruch width is not more than 1. */
        _gx_display_driver_generic_aliased_ellipse_draw(context, xcenter, ycenter, a, b);
    }

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, aliased ellipse draw function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to draw aliased ellipse. Although D/AVE 2D acceleration enabled, ellipse draw is
 * done by GUIX generic software draw routine because the operation is not supported by D/AVE 2D.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   a[in]              Semi-major axis
 * @param   b[in]              Semi-minor axis
 **********************************************************************************************************************/
VOID _gx_dave2d_ellipse_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    if (context->gx_draw_context_brush.gx_brush_width > 1)
    {
        /** Call the GUIX generic aliased ellipse draw routine if bruch width is more than 1. */
        _gx_display_driver_generic_wide_ellipse_draw(context, xcenter, ycenter, a, b);
    }
    else
    {
        /** Call the GUIX generic aliased ellipse draw routine if bruch width is not more than 1. */
        _gx_display_driver_generic_ellipse_draw(context, xcenter, ycenter, a, b);
    }

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, ellipse fill function with D/AVE 2D acceleration enabled.
 * This function is called by GUIX to perform ellipse fill. Although D/AVE 2D acceleration enabled, ellipse fill is done
 * by GUIX generic software draw routine.
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center pixel position in the horizontal axis
 * @param   ycenter[in]        Center pixel position in the vertical axis
 * @param   a[in]              Semi-major axis
 * @param   b[in]              Semi-minor axis
 **********************************************************************************************************************/
VOID _gx_dave2d_ellipse_fill (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);

    /** Call the GUIX generic ellipse fill routine. */
    _gx_display_driver_generic_ellipse_fill(context, xcenter, ycenter, a, b);
}

 #endif                                /* is GUIX arc drawing support enabled? */

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D accelerated draw function to toggle frame buffer.
 *  This function performs copies canvas memory to working frame buffer if a canvas is used, performs sequence of canvas
 *  refresh drawing commands, toggles frame buffer, and finally copies visible frame buffer to working frame buffer or
 *  copes canvas to working buffer if a canvas is used. This function is called by GUIX if D/AVE 2D hardware rendering
 *  acceleration is enabled.
 * @param   canvas[in]         Pointer to a GUIX canvas
 * @param   dirty[in]          Pointer to a dirty rectangle area
 **********************************************************************************************************************/
VOID _gx_dave2d_buffer_toggle (GX_CANVAS * canvas, GX_RECTANGLE * dirty)
{
    GX_PARAMETER_NOT_USED(dirty);

    GX_RECTANGLE Limit = {0};
    GX_RECTANGLE Copy  = {0};
    GX_DISPLAY * display;
    INT          rotation_angle;

    display = canvas->gx_canvas_display;

    rotation_angle = rm_guix_port_display_rotation_get(display->gx_display_handle);
    rm_guix_port_frame_pointers_get(display->gx_display_handle, &visible_frame, &working_frame);

    _gx_utility_rectangle_define(&Limit, 0, 0, (GX_VALUE) (canvas->gx_canvas_x_resolution - 1),
                                 (GX_VALUE) (canvas->gx_canvas_y_resolution - 1));

    if (canvas->gx_canvas_memory != (GX_COLOR *) working_frame)
    {
        if (_gx_utility_rectangle_overlap_detect(&Limit, &canvas->gx_canvas_dirty_area, &Copy))
        {
            gx_dave2d_rotate_canvas_to_working(canvas, &Copy, rotation_angle);
        }
    }

    gx_display_list_flush(display);
    gx_display_list_open(display);

    /* Wait till framebuffer writeback is busy. */
    CHECK_DAVE_STATUS(d2_flushframe(display->gx_display_accelerator))

    rm_guix_port_frame_toggle(display->gx_display_handle, &visible_frame);
    rm_guix_port_frame_pointers_get(display->gx_display_handle, &visible_frame, &working_frame);

    /** If canvas memory is pointing directly to frame buffer, toggle canvas memory. */
    if (canvas->gx_canvas_memory == (GX_COLOR *) visible_frame)
    {
        canvas->gx_canvas_memory = (GX_COLOR *) working_frame;
    }

    if (_gx_utility_rectangle_overlap_detect(&Limit, &canvas->gx_canvas_dirty_area, &Copy) &&
        (visible_frame != working_frame))
    {
        /** Copies canvas memory or visible frame buffer to working frame buffer. */
        if (canvas->gx_canvas_memory == (GX_COLOR *) working_frame)
        {
            gx_dave2d_copy_visible_to_working(canvas, &Copy);
        }
        else
        {
            gx_dave2d_rotate_canvas_to_working(canvas, &Copy, rotation_angle);
        }
    }
}

#else                                  /* GX_RENESAS_DAVE2D_DRAW */

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, software draw function to toggle frame buffer.
 *  This function performs copies canvas memory to working frame buffer if a canvas is used, then toggles frame buffer,
 *  finally copies visible frame buffer to working frame buffer. This function is called by GUIX if hardware rendering
 *  acceleration is not enabled.
 * @param[in]    canvas        Pointer to a GUIX canvas
 * @param[in]   dirty          Pointer to a dirty rectangle area
 **********************************************************************************************************************/
VOID _gx_ra_buffer_toggle (GX_CANVAS * canvas, GX_RECTANGLE * dirty)
{
    GX_PARAMETER_NOT_USED(dirty);

    GX_RECTANGLE Limit;
    GX_RECTANGLE Copy;
    GX_DISPLAY * display;
    INT          rotation_angle;

    display = canvas->gx_canvas_display;

    _gx_utility_rectangle_define(&Limit, 0, 0, (GX_VALUE) (canvas->gx_canvas_x_resolution - 1),
                                 (GX_VALUE) (canvas->gx_canvas_y_resolution - 1));

    rotation_angle = rm_guix_port_display_rotation_get(display->gx_display_handle);

    rm_guix_port_frame_pointers_get(display->gx_display_handle, &visible_frame, &working_frame);

    if (canvas->gx_canvas_memory != (GX_COLOR *) working_frame)
    {
        if (_gx_utility_rectangle_overlap_detect(&Limit, &canvas->gx_canvas_dirty_area, &Copy))
        {
            if ((INT) display->gx_display_color_format == GX_COLOR_FORMAT_565RGB)
            {
                gx_rotate_canvas_to_working_16bpp(canvas, &Copy, rotation_angle);
            }
            else
            {
                gx_rotate_canvas_to_working_32bpp(canvas, &Copy, rotation_angle);
            }
        }
    }

    rm_guix_port_frame_toggle(canvas->gx_canvas_display->gx_display_handle, &visible_frame);
    rm_guix_port_frame_pointers_get(canvas->gx_canvas_display->gx_display_handle, &visible_frame, &working_frame);

    if (canvas->gx_canvas_memory == (GX_COLOR *) visible_frame)
    {
        canvas->gx_canvas_memory = (GX_COLOR *) working_frame;
    }

    if (_gx_utility_rectangle_overlap_detect(&Limit, &canvas->gx_canvas_dirty_area, &Copy))
    {
        if (canvas->gx_canvas_memory == (GX_COLOR *) working_frame)
        {
            gx_copy_visible_to_working(canvas, &Copy);
        }
        else
        {
            if ((INT) display->gx_display_color_format == GX_COLOR_FORMAT_565RGB)
            {
                gx_rotate_canvas_to_working_16bpp(canvas, &Copy, rotation_angle);
            }
            else
            {
                gx_rotate_canvas_to_working_32bpp(canvas, &Copy, rotation_angle);
            }
        }
    }
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_ra_buffer_toggle
 * @param[in]    canvas        Pointer to a GUIX canvas
 * @param[in]   dirty          Pointer to a dirty rectangle area
 **********************************************************************************************************************/
VOID _gx_ra_rotated_buffer_toggle (GX_CANVAS * canvas, GX_RECTANGLE * dirty)
{
    _gx_ra_buffer_toggle(canvas, dirty);
}

#endif

#if (GX_USE_RENESAS_JPEG == 1)

/*******************************************************************************************************************//**
 * Wait for an event from the JPEG Codec.
 **********************************************************************************************************************/
static INT gx_renesas_jpeg_wait (jpeg_status_t * p_status, uint32_t timeout)
{
    /* Pend on JPEG semaphore to wait for next event */
    INT ret = (INT) tx_semaphore_get(&gx_renesas_jpeg_semaphore, timeout);

    /* Get JPEG status */
    *p_status = g_jpeg_status;

    return ret;
}

/*******************************************************************************************************************//**
 * JPEG decode ISR.
 **********************************************************************************************************************/
void _gx_renesas_jpeg_callback (jpeg_callback_args_t * p_args)
{
    g_jpeg_status = p_args->status;

    tx_semaphore_ceiling_put(&gx_renesas_jpeg_semaphore, 1U);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Hardware accelerated JPEG draw function.
 *  This function decodes JPEG image and draws in the frame buffer. This function is called by GUIX if JPEG hardware
 *  rendering is enabled.
 * @param   p_context[in]       Pointer to a GUIX draw context
 * @param   x[in]               x axis pixel offset
 * @param   y[in]               y axis pixel offset
 * @param   p_pixelmap[in]      Pointer to a pixelmap
 **********************************************************************************************************************/
VOID _gx_renesas_jpeg_draw (GX_DRAW_CONTEXT * p_context, INT x, INT y, GX_PIXELMAP * p_pixelmap)
{
    INT                           ret;
    jpeg_instance_t             * p_jpeg;
    jpeg_color_space_t            pixel_format    = JPEG_COLOR_SPACE_YCBCR422;
    jpeg_status_t                 jpeg_status     = JPEG_STATUS_NONE;
    jpeg_output_streaming_param_t param           = {0};
    UINT                          minimum_height  = 0;
    UINT                          memory_required = 0;

    /** Gets JPEG Framework driver instance.  */
    p_jpeg = (jpeg_instance_t *) rm_guix_port_jpeg_instance_get(p_context->gx_draw_context_display->gx_display_handle);

    /** Opens JPEG decode driver.  */
    ret = gx_renesas_jpeg_draw_open(p_context, p_jpeg, &param.bytes_per_pixel);

    /** Sets the input buffer address.  */
    ret += (INT) p_jpeg->p_api->inputBufferSet(p_jpeg->p_ctrl,
                                               (UCHAR *) p_pixelmap->gx_pixelmap_data,
                                               p_pixelmap->gx_pixelmap_data_size);

    /** Gets the JPEG hardware status.  */
    ret += gx_renesas_jpeg_wait(&jpeg_status, 1000);

    if ((ret) || (!((UINT) (JPEG_STATUS_IMAGE_SIZE_READY) &(UINT) jpeg_status)))
    {
        /* Nothing to draw. Close the device and return */
        p_jpeg->p_api->close(p_jpeg->p_ctrl);

        return;
    }

    /** Gets the size of JPEG image.  */
    ret +=
        (INT) p_jpeg->p_api->imageSizeGet(p_jpeg->p_ctrl,
                                          (uint16_t *) &param.image_width,
                                          (uint16_t *) &param.image_height);

    /** Gets the pixel format of JPEG image.  */
    ret += (INT) p_jpeg->p_api->pixelFormatGet(p_jpeg->p_ctrl, &pixel_format);

    if (ret)
    {
        /* Nothing to draw. Close the device and return */
        p_jpeg->p_api->close(p_jpeg->p_ctrl);

        return;
    }

    minimum_height = gx_renesas_jpeg_draw_minimum_height_get(pixel_format, param.image_width, param.image_height);
    if (0 == minimum_height)
    {
        p_jpeg->p_api->close(p_jpeg->p_ctrl);

        return;
    }

    memory_required = (UINT) (minimum_height * ((UINT) param.image_width * param.bytes_per_pixel));

    param.output_buffer = rm_guix_port_jpeg_buffer_get(p_context->gx_draw_context_display->gx_display_handle,
                                                       &param.jpeg_buffer_size);

    /* Verify JPEG output buffer size meets minimum memory requirement. */
    if ((UINT) param.jpeg_buffer_size < memory_required)
    {
        p_jpeg->p_api->close(p_jpeg->p_ctrl);

        return;
    }

    /** Detects memory allocation errors. */
    if (param.output_buffer == GX_NULL)
    {
        /* If the output buffer is not allocated, nothing to be done but close the JPEG device and return. */
        p_jpeg->p_api->close(p_jpeg->p_ctrl);

        return;
    }

    /** Reject the buffer if it is not 8-byte aligned.*/
    if ((ULONG) param.output_buffer & 0x7)
    {
        /* Close the JPEG device and return. */
        p_jpeg->p_api->close(p_jpeg->p_ctrl);

        return;
    }

    /** Sets the horizontal stride. */
    p_jpeg->p_api->horizontalStrideSet(p_jpeg->p_ctrl, (uint32_t) param.image_width);

    /** Sets JPEG output streaming mode parameters.  */
    param.p_context  = p_context;
    param.p_pixelmap = p_pixelmap;
    param.p_jpeg     = p_jpeg;
    param.x          = x;
    param.y          = y;

    /** Decode JPEG encoded data in the JPEG decode output streaming mode.  */
    gx_renesas_jpeg_draw_output_streaming(&param);

    p_jpeg->p_api->close(p_jpeg->p_ctrl);
}                                      /* End of function _gx_driver_jpeg_draw() */

#endif /* (GX_USE_RENESAS_JPEG)  */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_GUIX_PORT)
 **********************************************************************************************************************/

#if (GX_RENESAS_DAVE2D_DRAW == 1)

 #if defined(LOG_DAVE_ERRORS)

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D error code logging function. This function logs D/AVE 2D error
 * status to the FIFO named dave_error_list. If the FIFO gets full, restart logging from the first entry.
 * @param   status          D/AVE 2D error status code
 **********************************************************************************************************************/
VOID gx_log_dave_error (d2_s32 status)
{
    if (status)
    {
        dave_error_list[g_dave2d.error_list_index] = status;
        if (g_dave2d.error_count < DAVE_ERROR_LIST_SIZE)
        {
            g_dave2d.error_count++;
        }

        g_dave2d.error_list_index++;
        if (g_dave2d.error_list_index >= DAVE_ERROR_LIST_SIZE)
        {
            g_dave2d.error_list_index = 0;
        }
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D error code retrieve function. This function retrieves D/AVE 2D
 * error code from the FIFO named dave_error_list.
 * @param   get_index       Error log index number. Specify '0' to get latest error status, '1' to get previous one..
 * @retval  status              D/AVE 2D error status code
 **********************************************************************************************************************/
INT gx_get_dave_error (INT get_index)
{
    if (get_index > g_dave2d.error_count)
    {
        return 0;
    }

    INT list_index = g_dave2d.error_list_index;
    while (get_index > 0)
    {
        list_index--;
        if (list_index < 0)
        {
            list_index = DAVE_ERROR_LIST_SIZE;
        }

        get_index--;
    }

    return dave_error_list[list_index];
}

 #endif                                /* (LOG_DAVE_ERRORS) */

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, close and execute current D/AVE 2D display list, block until completed.
 * This is a common function for GUIX D/AVE 2D draw routines.
 * @param   display         Pointer to a GUIX display context
 **********************************************************************************************************************/
VOID gx_display_list_flush (GX_DISPLAY * display)
{
    if ((GX_FALSE == g_dave2d.display_list_flushed) && (GX_TRUE == d2_commandspending(display->gx_display_accelerator)))
    {
        CHECK_DAVE_STATUS(d2_endframe(display->gx_display_accelerator))
        CHECK_DAVE_STATUS(d2_startframe(display->gx_display_accelerator))

        /* Wait till framebuffer writeback is busy. */
        CHECK_DAVE_STATUS(d2_flushframe(display->gx_display_accelerator))

        g_dave2d.display_list_flushed = GX_TRUE;
        g_dave2d.display_list_count   = (GX_UBYTE) 0;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, open D/AVE 2D display list for drawing commands.
 * This is a common function for GUIX D/AVE 2D draw routines.
 * @param   display         Pointer to a GUIX display context
 **********************************************************************************************************************/
VOID gx_display_list_open (GX_DISPLAY * display)
{
    GX_PARAMETER_NOT_USED(display);

    if (g_dave2d.display_list_flushed)
    {
        g_dave2d.display_list_flushed = GX_FALSE;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, count the used display list size.
 * This function is called by _gx_dave2d_horizontal_pixelmap_line_draw and _gx_dave2d_horizontal_line.
 * @param   display         Pointer to a GUIX display context
 **********************************************************************************************************************/
VOID gx_dave2d_display_list_count (GX_DISPLAY * display)
{
    g_dave2d.display_list_count++;

    if ((INT) g_dave2d.display_list_count > GX_RENESAS_DAVE2D_COMMAND_COUNT_TO_REFRESH)
    {
        /** Flush D/AVE 2D display list first to insure order of operation. */
        gx_display_list_flush(display);

        /** Open next display list before we go. */
        gx_display_list_open(display);
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, test if polygon to be rendered is a convex polygon.
 * This function is called by _gx_dave2d_polygon_fill.
 * @param   vertex          Pointer to GUIX point data
 * @param   num             Number of points
 **********************************************************************************************************************/
GX_BOOL gx_dave2d_convex_polygon_test (GX_POINT * vertex, INT num)
{
    if (num <= 3)
    {
        return GX_TRUE;
    }

    GX_POINT a;
    GX_POINT b;
    GX_POINT c;
    GX_POINT b_a;
    GX_POINT c_b;
    GX_BOOL  negative;
    INT      index;

    a = vertex[0];
    b = vertex[1];
    c = vertex[2];

    b_a.gx_point_x = (GX_VALUE) (b.gx_point_x - a.gx_point_x);
    b_a.gx_point_y = (GX_VALUE) (b.gx_point_y - a.gx_point_y);

    c_b.gx_point_x = (GX_VALUE) (c.gx_point_x - b.gx_point_x);
    c_b.gx_point_y = (GX_VALUE) (c.gx_point_y - b.gx_point_y);

    negative = ((b_a.gx_point_x * c_b.gx_point_y) < (b_a.gx_point_y * c_b.gx_point_x));

    for (index = 3; index < num; index++)
    {
        a = b;
        b = c;
        c = vertex[index];

        b_a.gx_point_x = (GX_VALUE) (b.gx_point_x - a.gx_point_x);
        b_a.gx_point_y = (GX_VALUE) (b.gx_point_y - a.gx_point_y);

        c_b.gx_point_x = (GX_VALUE) (c.gx_point_x - b.gx_point_x);
        c_b.gx_point_y = (GX_VALUE) (c.gx_point_y - b.gx_point_y);

        if (((b_a.gx_point_x * c_b.gx_point_y) < (b_a.gx_point_y * c_b.gx_point_x)) != (INT) negative)
        {
            return GX_FALSE;
        }
    }

    return GX_TRUE;
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, assign clipping rectangle based on GUIX drawing clipping rectangle
 * information.
 * This is a common function for GUIX D/AVE 2D draw routines.
 * @param   dave         Pointer to D/AVE handle
 * @param   clip         Pointer to a GUIX clipping drawing rectangle
 **********************************************************************************************************************/
VOID gx_dave2d_cliprect_set (d2_device * dave, GX_RECTANGLE * clip)
{
    CHECK_DAVE_STATUS(d2_cliprect(dave, clip->gx_rectangle_left, clip->gx_rectangle_top, clip->gx_rectangle_right,
                                  clip->gx_rectangle_bottom))
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, assign clipping rectangle based on GUIX drawing context information.
 * This is a common function for GUIX D/AVE 2D draw routines.
 * @param   context         Pointer to a GUIX drawing context
 * @retval  Address             Pointer to a D/AVE 2D device structure
 **********************************************************************************************************************/
d2_device * gx_dave2d_context_clip_set (GX_DRAW_CONTEXT * context)
{
    d2_device * dave = context->gx_draw_context_display->gx_display_accelerator;

    INT screen_angle = context->gx_draw_context_display->gx_display_rotation_angle;

    if (context->gx_draw_context_clip)
    {
        GX_RECTANGLE   clip_rect;
        GX_RECTANGLE * p_clip_rect;

        if ((screen_angle == GX_SCREEN_ROTATION_CW) || (screen_angle == GX_SCREEN_ROTATION_CCW))
        {
            p_clip_rect = &clip_rect;
            gx_dave2d_rectangle_rotate(context, context->gx_draw_context_clip, &clip_rect);
        }
        else
        {
            p_clip_rect = context->gx_draw_context_clip;
        }

        CHECK_DAVE_STATUS(d2_cliprect(dave, (d2_border) p_clip_rect->gx_rectangle_left,
                                      (d2_border) p_clip_rect->gx_rectangle_top,
                                      (d2_border) p_clip_rect->gx_rectangle_right,
                                      (d2_border) p_clip_rect->gx_rectangle_bottom))
    }
    else
    {
        d2_border   canvas_x;
        d2_border   canvas_y;
        GX_CANVAS * canvas = context->gx_draw_context_canvas;

        if ((screen_angle == GX_SCREEN_ROTATION_CW) || (screen_angle == GX_SCREEN_ROTATION_CCW))
        {
            canvas_x = (d2_border) (canvas->gx_canvas_y_resolution - 1);
            canvas_y = (d2_border) (canvas->gx_canvas_x_resolution - 1);
        }
        else
        {
            canvas_x = (d2_border) (canvas->gx_canvas_x_resolution - 1);
            canvas_y = (d2_border) (canvas->gx_canvas_y_resolution - 1);
        }

        CHECK_DAVE_STATUS(d2_cliprect(dave, 0, 0, canvas_x, canvas_y))
    }

    return dave;
}

/*******************************************************************************************************************//**
 * @brief  Utility function to convert color data from GUIX RGB565 to D/AVE 2D 24-bit RGB.
 * This function is called by _gx_dave2d_drawing_initiate().
 * @param   color           GUIX color data
 **********************************************************************************************************************/
static d2_color gx_rgb565_to_888 (GX_COLOR color)
{
    d2_color out_color;
    out_color = (((color & 0xf800) << 8) | ((color & 0x7e0) << 5) | ((color & 0x1f) << 3));

    return out_color;
}

/*******************************************************************************************************************//**
 * @brief  Utility function to convert color data from GUIX XRGB to D/AVE 2D XRGB.
 * This function is called by _gx_dave2d_drawing_initiate().
 * @param   color           GUIX color data
 **********************************************************************************************************************/
static d2_color gx_xrgb_to_xrgb (GX_COLOR color)
{
    d2_color out_color = (d2_color) color;

    return out_color;
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D pixelmap draw/blend sub-routine to select a D/AVE 2D color format
 * corresponding to the GUIX color format.
 * This function is called by _gx_dave2d_pixelmap_draw() or _gx_dave2d_pixelmap_blend.
 * @param   map             Pointer to GUIX pixelmap
 * @retval  format              D/AVE2D color format d2_mode_rgb565, d2_mode_argb4444, d2_mode_argb8888, d2_mode_alpha8
 *                              or (d2_mode_i8|d2_mode_clut)
 **********************************************************************************************************************/
static d2_u32 gx_dave2d_format_set (GX_PIXELMAP * map)
{
    d2_u32 format;

    switch (map->gx_pixelmap_format)
    {
        case (GX_UBYTE) GX_COLOR_FORMAT_565RGB:
        {
            format = d2_mode_rgb565;
            break;
        }

        case (GX_UBYTE) GX_COLOR_FORMAT_4444ARGB:
        {
            format = d2_mode_argb4444;
            break;
        }

        case (GX_UBYTE) GX_COLOR_FORMAT_24XRGB:
        case (GX_UBYTE) GX_COLOR_FORMAT_32ARGB:
        {
            format = d2_mode_argb8888;
            break;
        }

        case (GX_UBYTE) GX_COLOR_FORMAT_8BIT_ALPHAMAP:
        {
            format = d2_mode_alpha8;
            break;
        }

        default:                       /* GX_COLOR_FORMAT_8BIT_PALETTE */
        {
            format = d2_mode_i8 | d2_mode_clut;
            break;
        }
    }

    return format;
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Support function used to apply texture source for all shape drawing.
 * This function is called by GUIX to draw a polygon.
 * @param   context         Pointer to a GUIX draw context
 * @param   dave            Pointer to D/AVE 2D device context
 * @param   xpos            X position in pixel unit
 * @param   ypos            y position in pixel unit
 * @param   map             Pointer to GUIX pixelmap
 **********************************************************************************************************************/
static VOID gx_dave2d_set_texture (GX_DRAW_CONTEXT * context, d2_device * dave, INT xpos, INT ypos, GX_PIXELMAP * map)
{
    GX_PARAMETER_NOT_USED(context);

    d2_u32 format = gx_dave2d_format_set(map);

    if ((format & (d2_u32) d2_mode_clut) == (d2_u32) d2_mode_clut)
    {
        CHECK_DAVE_STATUS(d2_settexclut(dave, (d2_color *) map->gx_pixelmap_aux_data))
    }

    if (map->gx_pixelmap_flags & GX_PIXELMAP_COMPRESSED)
    {
        format |= d2_mode_rle;
    }

    CHECK_DAVE_STATUS(d2_settexture(dave, (void *) map->gx_pixelmap_data, map->gx_pixelmap_width,
                                    map->gx_pixelmap_width, map->gx_pixelmap_height, format))

    /* Wrap texture over drawn area */
    CHECK_DAVE_STATUS(d2_settexturemode(dave, d2_tm_wrapu | d2_tm_wrapv))

    /* Set texture color processing */
    d2_u8 alpha_mode = d2_to_one;
    if (map->gx_pixelmap_flags & GX_PIXELMAP_ALPHA)
    {
        alpha_mode = d2_to_copy;
    }

    CHECK_DAVE_STATUS(d2_settextureoperation(dave, alpha_mode, d2_to_copy, d2_to_copy, d2_to_copy))

    /* Map texture to location */
    CHECK_DAVE_STATUS(d2_settexelcenter(dave, 0, 0))
    CHECK_DAVE_STATUS(d2_settexturemapping(dave, (d2_point) ((USHORT) xpos << 4), (d2_point) ((USHORT) ypos << 4), 0, 0,
                                           (d2_s32) (1U << 16), 0, 0, (d2_s32) (1U << 16)))
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8-bit glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by _gx_dave2d_compressed_glyph_8bit_draw() or _gx_dave2d_raw_glyph_8bit_draw().
 * @param   context        Pointer to a GUIX draw context
 * @param   draw_area      Pointer to the draw rectangle area
 * @param   map_offset     Mapping offset
 * @param   glyph          Pointer to glyph data
 * @param   mode           D/AVE 2D render mode option (none('0') or d2_mode_rle)
 **********************************************************************************************************************/
static VOID gx_dave2d_glyph_8bit_draw (GX_DRAW_CONTEXT * context,
                                       GX_RECTANGLE    * draw_area,
                                       GX_POINT        * map_offset,
                                       const GX_GLYPH  * glyph,
                                       d2_u32            mode)
{
    d2_device * dave;
    GX_COLOR    text_color;

    /* pickup pointer to current display driver */
    dave = context->gx_draw_context_display->gx_display_accelerator;

    text_color = context->gx_draw_context_brush.gx_brush_line_color;

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_cliprect_set(dave, draw_area);
    gx_dave2d_color0_set(dave, text_color);
    gx_dave2d_blend_mode_set(dave, d2_bm_one, d2_bm_one_minus_alpha);

    d2_s32 glyph_width  = glyph->gx_glyph_width;
    d2_s32 glyph_height = glyph->gx_glyph_height;

    /* Glyph data is pre-rotated in portrait orientations */
    if ((context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW) ||
        (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CCW))
    {
        glyph_width  = glyph->gx_glyph_height;
        glyph_height = glyph->gx_glyph_width;
    }

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) glyph->gx_glyph_map, glyph_width, glyph_width, glyph_height,
                                    mode | d2_mode_alpha8))

    CHECK_DAVE_STATUS(d2_blitcopy(dave, glyph_width, glyph_height, (d2_blitpos) (map_offset->gx_point_x),
                                  (d2_blitpos) (map_offset->gx_point_y), (d2_width) (D2_FIX4((USHORT) (glyph_width))),
                                  (d2_width) (D2_FIX4((USHORT) (glyph_height))),
                                  (d2_point) (D2_FIX4((USHORT) (draw_area->gx_rectangle_left))),
                                  (d2_point) (D2_FIX4((USHORT) (draw_area->gx_rectangle_top))),
                                  (d2_u32) d2_bf_usealpha | (d2_u32) d2_bf_colorize))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);

    /* Return back alpha blend mode. */
    gx_dave2d_blend_mode_set(dave, d2_bm_alpha, d2_bm_one_minus_alpha);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 4-bit glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by _gx_dave2d_compressed_glyph_4bit_draw() or _gx_dave2d_raw_glyph_4bit_draw().
 * @param   context        Pointer to a GUIX draw context
 * @param   draw_area      Pointer to the draw rectangle area
 * @param   map_offset     Mapping offset
 * @param   glyph          Pointer to glyph data
 * @param   mode           D/AVE 2D render mode option (none('0') or d2_mode_rle)
 **********************************************************************************************************************/
static VOID gx_dave2d_glyph_4bit_draw (GX_DRAW_CONTEXT * context,
                                       GX_RECTANGLE    * draw_area,
                                       GX_POINT        * map_offset,
                                       const GX_GLYPH  * glyph,
                                       d2_u32            mode)
{
    d2_device * dave;
    GX_COLOR    text_color;

    text_color = context->gx_draw_context_brush.gx_brush_line_color;
    dave       = context->gx_draw_context_display->gx_display_accelerator;

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_cliprect_set(dave, draw_area);

 #if 1
    gx_dave2d_color0_set(dave, text_color);
    gx_dave2d_blend_mode_set(dave, d2_bm_alpha, d2_bm_one_minus_alpha);

    if (g_dave2d.font_bits != 4)
    {
        /* setup a 16 entry alpha palette for drawing glyph */
        CHECK_DAVE_STATUS(d2_settexclut_part(dave, (d2_color *) g_gray_palette, 0, 16))
        g_dave2d.font_bits = 4;
    }

    d2_s32 glyph_width  = glyph->gx_glyph_width;
    d2_s32 glyph_height = glyph->gx_glyph_height;

    /* Glyph data is pre-rotated in portrait orientations */
    if ((context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW) ||
        (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CCW))
    {
        glyph_width  = glyph->gx_glyph_height;
        glyph_height = glyph->gx_glyph_width;
    }

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) glyph->gx_glyph_map,
                                    (d2_s32) (((USHORT) glyph_width + 1U) & 0xfffeU), (d2_s32) glyph_width,
                                    (d2_s32) glyph_height,
                                    (mode | d2_mode_i4 | d2_mode_clut)))
 #else

    /* This version uses d2_mode_alpha4 instead of setting up a 16-entry palette,
     * however currently this blitsrc mode is not supported by D/AVE2D. Keep this code here in case this supported is
     * added in future versions.
     */
    gx_dave2d_color0_set(dave, text_color);
    gx_dave2d_blend_mode_set(dave, d2_bm_one, d2_bm_one_minus_alpha);

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) glyph->gx_glyph_map,
                                    (d2_s32) (((USHORT) glyph->gx_glyph_width + 1U) & 0xfffeU), glyph->gx_glyph_width,
                                    glyph->gx_glyph_height,
                                    mode | d2_mode_alpha4))
 #endif
    CHECK_DAVE_STATUS(d2_blitcopy(dave,
                                  glyph_width,
                                  glyph_height,
                                  0,
                                  0,
                                  (d2_width) (D2_FIX4((USHORT) (glyph_width))),
                                  (d2_width) (D2_FIX4((USHORT) (glyph_height))),
                                  (d2_point) (D2_FIX4((USHORT) draw_area->gx_rectangle_left -
                                                      (USHORT) map_offset->gx_point_x)),
                                  (d2_point) (D2_FIX4((USHORT) draw_area->gx_rectangle_top -
                                                      (USHORT) map_offset->gx_point_y)),
                                  (d2_u32) d2_bf_colorize | (d2_u32) d2_bf_usealpha))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);

    /** Set blend mode. */
    gx_dave2d_blend_mode_set(dave, d2_bm_alpha, d2_bm_one_minus_alpha);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 1-bit glyph draw function with D/AVE 2D acceleration enabled.
 * This function is called by _gx_dave2d_compressed_glyph_1bit_draw() or _gx_dave2d_raw_glyph_1bit_draw().
 * @param   context        Pointer to a GUIX draw context
 * @param   draw_area      Pointer to the draw rectangle area
 * @param   map_offset     Mapping offset
 * @param   glyph          Pointer to glyph data
 * @param   mode           D/AVE 2D render mode option (none('0') or d2_mode_rle)
 **********************************************************************************************************************/
static VOID gx_dave2d_glyph_1bit_draw (GX_DRAW_CONTEXT * context,
                                       GX_RECTANGLE    * draw_area,
                                       GX_POINT        * map_offset,
                                       const GX_GLYPH  * glyph,
                                       d2_u32            mode)
{
    d2_device * dave;
    GX_COLOR    text_color;

    /** Pickup pointer to current display driver */
    dave = context->gx_draw_context_display->gx_display_accelerator;

    text_color = context->gx_draw_context_brush.gx_brush_line_color;

    if (gx_dave2d_brush_alpha_set(dave, context))
    {
        return;
    }

    gx_dave2d_cliprect_set(dave, draw_area);

 #if 1
    if (g_dave2d.font_bits != 1)
    {
        /* set up a 2-entry alpha palette for drawing glyph */
        CHECK_DAVE_STATUS(d2_settexclut_part(dave, (d2_color *) g_mono_palette, 0, 2))
        g_dave2d.font_bits = 1;
    }

    gx_dave2d_color0_set(dave, text_color);
    gx_dave2d_blend_mode_set(dave, d2_bm_alpha, d2_bm_one_minus_alpha);

    d2_s32 glyph_width  = glyph->gx_glyph_width;
    d2_s32 glyph_height = glyph->gx_glyph_height;

    /* Glyph data is pre-rotated in portrait orientations */
    if ((context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW) ||
        (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CCW))
    {
        glyph_width  = glyph->gx_glyph_height;
        glyph_height = glyph->gx_glyph_width;
    }

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) glyph->gx_glyph_map,
                                    (d2_s32) (((USHORT) glyph_width + 7U) & 0xfff8U), (d2_s32) glyph_width,
                                    (d2_s32) glyph_height,
                                    (mode | d2_mode_i1 | d2_mode_clut)))
 #else

    /* This version uses d2_mode_alpha1 instead of setting up a 16-entry palette,
     * however currently this blitsrc mode is not supported by D/AVE2D. Keep this code here in case this supported is
     * added in future versions.
     */
    gx_dave2d_color0_set(dave, text_color);
    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) glyph->gx_glyph_map, glyph->gx_glyph_width, glyph->gx_glyph_width,
                                    glyph->gx_glyph_height, mode | d2_mode_alpha1))
 #endif

    CHECK_DAVE_STATUS(d2_blitcopy(dave,
                                  glyph_width,
                                  glyph_height,
                                  0,
                                  0,
                                  (d2_width) (D2_FIX4((USHORT) glyph_width)),
                                  (d2_width) (D2_FIX4((USHORT) glyph_height)),
                                  (d2_point) (D2_FIX4((USHORT) draw_area->gx_rectangle_left -
                                                      (USHORT) map_offset->gx_point_x)),
                                  (d2_point) (D2_FIX4((USHORT) draw_area->gx_rectangle_top -
                                                      (USHORT) map_offset->gx_point_y)),
                                  (d2_u32) d2_bf_usealpha | (d2_u32) d2_bf_colorize))

    /** Count the used display list size. */
    gx_dave2d_display_list_count(context->gx_draw_context_display);

    /** Set blend mode. */
    gx_dave2d_blend_mode_set(dave, d2_bm_alpha, d2_bm_one_minus_alpha);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D draw function sub routine to copy visible frame buffer to working
 * frame buffer. This function is called by _gx_dave2d_buffer_toggle() to perform image data copy between frame buffers
 * after buffer toggle operation.
 * @param   canvas         Pointer to a GUIX canvas
 * @param   copy           Pointer to a rectangle area to be copied
 **********************************************************************************************************************/
static VOID gx_dave2d_copy_visible_to_working (GX_CANVAS * canvas, GX_RECTANGLE * copy)
{
    GX_RECTANGLE display_size;
    GX_RECTANGLE copy_clip;
    d2_u32       mode;

    ULONG * pGetRow;
    ULONG * pPutRow;

    INT copy_width;
    INT copy_height;

    GX_DISPLAY * display = canvas->gx_canvas_display;
    d2_device  * dave    = (d2_device *) display->gx_display_accelerator;

    _gx_utility_rectangle_define(&display_size, 0, 0, (GX_VALUE) (display->gx_display_width - 1),
                                 (GX_VALUE) (display->gx_display_height - 1));
    copy_clip = *copy;

    /** Align copy region on 32-bit memory boundary in case not aligned. */
    if ((INT) display->gx_display_color_format == GX_COLOR_FORMAT_565RGB)
    {
        /** If yes, align copy region on 32-bit boundary. */
        copy_clip.gx_rectangle_left  = (GX_VALUE) ((USHORT) (copy_clip.gx_rectangle_left) & 0xfffeU);
        copy_clip.gx_rectangle_right = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_right | 1U);
        mode = d2_mode_rgb565;
    }
    else
    {
        mode = d2_mode_argb8888;
    }

    /** Offset canvas within frame buffer */
    _gx_utility_rectangle_shift(&copy_clip, canvas->gx_canvas_display_offset_x, canvas->gx_canvas_display_offset_y);

    _gx_utility_rectangle_overlap_detect(&copy_clip, &display_size, &copy_clip);
    copy_width  = (copy_clip.gx_rectangle_right - copy_clip.gx_rectangle_left) + 1;
    copy_height = (copy_clip.gx_rectangle_bottom - copy_clip.gx_rectangle_top) + 1;

    if ((copy_width <= 0) || (copy_height <= 0))
    {
        return;
    }

    pGetRow = (ULONG *) visible_frame;
    pPutRow = (ULONG *) working_frame;

    d2_u32       width;
    d2_u32       height;
    GX_RECTANGLE rectangle_out;

    /* Swap dimensions if we're running in 'portrait' orientation */
    if ((display->gx_display_rotation_angle == GX_SCREEN_ROTATION_NONE) ||
        (display->gx_display_rotation_angle == GX_SCREEN_ROTATION_FLIP))
    {
        width  = (d2_u32) canvas->gx_canvas_x_resolution;
        height = (d2_u32) canvas->gx_canvas_y_resolution;
    }
    else
    {
        width  = (d2_u32) canvas->gx_canvas_y_resolution;
        height = (d2_u32) canvas->gx_canvas_x_resolution;

        INT temp = copy_width;
        copy_width  = copy_height;
        copy_height = temp;

        GX_VALUE x0 = copy_clip.gx_rectangle_left;
        GX_VALUE y0 = copy_clip.gx_rectangle_top;
        GX_VALUE x1 = copy_clip.gx_rectangle_right;
        GX_VALUE y1 = copy_clip.gx_rectangle_bottom;

        GX_VALUE canvas_x = (GX_VALUE) (canvas->gx_canvas_x_resolution - 1);
        GX_VALUE canvas_y = (GX_VALUE) (canvas->gx_canvas_y_resolution - 1);

        /* Swap coordinates if we're running in a 'portrait' orientation */
        if (display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
        {
            GX_VALUE rectangle_x = (GX_VALUE) (x1 - x0);

            rectangle_out.gx_rectangle_left   = y0;
            rectangle_out.gx_rectangle_top    = (GX_VALUE) (canvas_x - x0 - rectangle_x);
            rectangle_out.gx_rectangle_right  = y1;
            rectangle_out.gx_rectangle_bottom = (GX_VALUE) (canvas_x - x1 + rectangle_x);
        }
        else
        {
            rectangle_out.gx_rectangle_left   = (GX_VALUE) (canvas_y - y1);
            rectangle_out.gx_rectangle_top    = x0;
            rectangle_out.gx_rectangle_right  = (GX_VALUE) (canvas_y - y0);
            rectangle_out.gx_rectangle_bottom = x1;
        }

        copy_clip = rectangle_out;
    }

    CHECK_DAVE_STATUS(d2_framebuffer(dave, pPutRow, (d2_s32) width, width, height, (d2_s32) mode))

    gx_dave2d_cliprect_set(dave, &copy_clip);
    gx_dave2d_alpha_set(dave, (UCHAR) GX_ALPHA_VALUE_OPAQUE);

    CHECK_DAVE_STATUS(d2_setblitsrc(dave, (void *) pGetRow, (d2_s32) width, (d2_s32) width, (d2_s32) height, mode))

    CHECK_DAVE_STATUS(d2_blitcopy(dave, copy_width, copy_height, (d2_blitpos) (copy_clip.gx_rectangle_left),
                                  (d2_blitpos) (copy_clip.gx_rectangle_top), (d2_width) (D2_FIX4((UINT) copy_width)),
                                  (d2_width) (D2_FIX4((UINT) copy_height)),
                                  (d2_point) (D2_FIX4((USHORT) copy_clip.gx_rectangle_left)),
                                  (d2_point) (D2_FIX4((USHORT) copy_clip.gx_rectangle_top)), d2_bf_no_blitctxbackup))

    CHECK_DAVE_STATUS(d2_endframe(display->gx_display_accelerator))
    CHECK_DAVE_STATUS(d2_startframe(display->gx_display_accelerator))
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D draw function sub routine to set the screen rotation parameters.
 * This function is called by gx_dave2d_rotate_canvas_to_working().
 * @param[in]     p_param            Pointer to a rectangle area to be copied
 * @param[in]     p_display          Pointer to the GUIX display
 * @param[in]     p_canvas           Pointer to a GUIX canvas
 **********************************************************************************************************************/
void gx_dave2d_rotate_canvas_to_working_param_set (d2_rotation_param_t * p_param,
                                                   GX_DISPLAY          * p_display,
                                                   GX_CANVAS           * p_canvas)
{
    if (p_param->angle == GX_SCREEN_ROTATION_FLIP)
    {
        INT      actual_video_width    = 0;
        INT      actual_video_height   = 0;
        GX_VALUE clipped_display_width = p_display->gx_display_width;

        rm_guix_port_display_actual_size_get(p_display->gx_display_handle, &actual_video_width, &actual_video_height);
        if (p_param->copy_width > actual_video_width)
        {
            p_param->copy_width = actual_video_width;
        }

        if ((INT) p_param->copy_clip.gx_rectangle_right > actual_video_width)
        {
            p_param->copy_clip.gx_rectangle_right = (GX_VALUE) actual_video_width;
        }

        if ((INT) clipped_display_width > actual_video_width)
        {
            clipped_display_width = (GX_VALUE) actual_video_width;
        }

        p_param->xmin = (d2_border) (clipped_display_width - p_param->copy_clip.gx_rectangle_right - 1);
        p_param->xmax = (d2_border) (clipped_display_width - p_param->copy_clip.gx_rectangle_left - 1);
        p_param->ymin =
            (d2_border) (p_display->gx_display_height - p_param->copy_clip.gx_rectangle_bottom - 1);
        p_param->ymax =
            (d2_border) (p_display->gx_display_height - p_param->copy_clip.gx_rectangle_top - 1);
        p_param->x_texture_zero = (d2_point) (clipped_display_width - p_param->copy_clip.gx_rectangle_left - 1);
        p_param->y_texture_zero =
            (d2_point) (p_display->gx_display_height - p_param->copy_clip.gx_rectangle_top - 1);
        p_param->dxu = (d2_s32) (-D2_FIX16(1U));
        p_param->dyv = (d2_s32) (-D2_FIX16(1U));
    }
    else
    {
        p_param->xmin           = (d2_border) (p_param->copy_clip.gx_rectangle_left);
        p_param->xmax           = (d2_border) (p_param->copy_clip.gx_rectangle_right);
        p_param->ymin           = (d2_border) (p_param->copy_clip.gx_rectangle_top);
        p_param->ymax           = (d2_border) (p_param->copy_clip.gx_rectangle_bottom);
        p_param->x_texture_zero = (d2_point) (p_param->copy_clip.gx_rectangle_left);
        p_param->y_texture_zero = (d2_point) (p_param->copy_clip.gx_rectangle_top);
        p_param->dxu            = (d2_s32) (D2_FIX16(1U));
        p_param->dyv            = (d2_s32) (D2_FIX16(1U));
    }

    p_param->dxv                 = 0;
    p_param->dyu                 = 0;
    p_param->copy_width_rotated  = p_param->copy_width;
    p_param->copy_height_rotated = p_param->copy_height;
    p_param->x_resolution        = p_canvas->gx_canvas_x_resolution;
    p_param->y_resolution        = p_canvas->gx_canvas_y_resolution;
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D draw function sub routine.
 * This function is called by gx_dave2d_rotate_canvas_to_working() to perform D/AVE 2D render box operation.
 * @param[in]     p_dave             Pointer to the D/AVE 2D driver context
 * @param[in]     p_param            Pointer to a rectangle area to be copied
 * @param[in]     mode               D/AVE framebuffer mode
 * @param[in]     p_display          Pointer to the GUIX display
 * @param[in]     p_canvas           Pointer to destination canvas
 **********************************************************************************************************************/
static VOID gx_dave2d_rotate_canvas_to_working_image_draw (d2_device           * p_dave,
                                                           d2_rotation_param_t * p_param,
                                                           d2_u32                mode,
                                                           GX_DISPLAY          * p_display,
                                                           GX_CANVAS           * p_canvas)
{
    USHORT     * pGetRow16 = NULL;
    UINT       * pGetRow32 = NULL;
    GX_RECTANGLE clip      = {0};

    CHECK_DAVE_STATUS(d2_framebuffer(p_dave, (uint16_t *) working_frame, (d2_s32) p_param->x_resolution,
                                     (d2_u32) p_param->x_resolution, (d2_u32) p_param->y_resolution, (d2_s32) mode));

    gx_utility_rectangle_define(&clip, (GX_VALUE) p_param->xmin, (GX_VALUE) p_param->ymin, (GX_VALUE) p_param->xmax,
                                (GX_VALUE) p_param->ymax);

    gx_dave2d_cliprect_set(p_dave, &clip);
    gx_dave2d_fill_mode_set(p_dave, d2_fm_texture);
    gx_dave2d_render_mode_set(p_dave, d2_rm_solid);
    gx_dave2d_alpha_set(p_dave, (UCHAR) GX_ALPHA_VALUE_OPAQUE);

    if (mode == d2_mode_rgb565)
    {
        pGetRow16 = (USHORT *) p_canvas->gx_canvas_memory;
        pGetRow16 = pGetRow16 +
                    ((p_canvas->gx_canvas_display_offset_y + p_param->copy_clip.gx_rectangle_top) *
                     p_display->gx_display_width);
        pGetRow16 = pGetRow16 + (p_canvas->gx_canvas_display_offset_x + p_param->copy_clip.gx_rectangle_left);

        CHECK_DAVE_STATUS(d2_settexture(p_dave, pGetRow16, p_display->gx_display_width, p_param->copy_width,
                                        p_param->copy_height, mode));
    }
    else
    {
        pGetRow32 = (UINT *) p_canvas->gx_canvas_memory;
        pGetRow32 = pGetRow32 +
                    ((p_canvas->gx_canvas_display_offset_y + p_param->copy_clip.gx_rectangle_top) *
                     p_display->gx_display_width);
        pGetRow32 = pGetRow32 + (p_canvas->gx_canvas_display_offset_x + p_param->copy_clip.gx_rectangle_left);

        CHECK_DAVE_STATUS(d2_settexture(p_dave, pGetRow32, p_display->gx_display_width, p_param->copy_width,
                                        p_param->copy_height, mode));
    }

    CHECK_DAVE_STATUS(d2_settexturemode(p_dave, 0));
    CHECK_DAVE_STATUS(d2_settextureoperation(p_dave, d2_to_one, d2_to_copy, d2_to_copy, d2_to_copy));
    CHECK_DAVE_STATUS(d2_settexelcenter(p_dave, 0, 0));

    CHECK_DAVE_STATUS(d2_settexturemapping(p_dave, (d2_point) D2_FIX4(p_param->x_texture_zero),
                                           (d2_point) D2_FIX4(p_param->y_texture_zero), 0, 0, p_param->dxu,
                                           p_param->dxv, p_param->dyu, p_param->dyv));

    CHECK_DAVE_STATUS(d2_renderbox(p_dave, (d2_point) D2_FIX4((USHORT) p_param->xmin),
                                   (d2_point) D2_FIX4((USHORT) p_param->ymin),
                                   (d2_width) D2_FIX4((UINT) p_param->copy_width_rotated),
                                   (d2_width) D2_FIX4((UINT) p_param->copy_height_rotated)));

    /** Count the used display list size. */
    gx_dave2d_display_list_count(p_display);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, D/AVE 2D draw function sub routine.
 * This function is called by _gx_dave2d_buffer_toggle() to copy canvas memory to frame buffer with screen rotation.
 * @param[in]     canvas             Pointer to a GUIX canvas
 * @param[in]     copy               Pointer to a rectangle area to be copied
 * @param[in]     rotation_angle     Rotation angle (0, 90, 180 or 270)
 **********************************************************************************************************************/
static VOID gx_dave2d_rotate_canvas_to_working (GX_CANVAS * canvas, GX_RECTANGLE * copy, INT rotation_angle)
{
    GX_RECTANGLE        display_size;
    d2_u32              mode;
    d2_rotation_param_t param = {0};

    GX_DISPLAY * display = canvas->gx_canvas_display;
    d2_device  * dave    = (d2_device *) display->gx_display_accelerator;

    d2_u8 fillmode_bkup = d2_getfillmode(dave);

    _gx_utility_rectangle_define(&display_size, 0, 0, (GX_VALUE) (display->gx_display_width - 1),
                                 (GX_VALUE) (display->gx_display_height - 1));

    param.copy_clip = *copy;

    /* Is color format RGB565? */
    if ((INT) display->gx_display_color_format == GX_COLOR_FORMAT_565RGB)
    {
        /* If yes, align copy region on 32-bit boundary. */
        param.copy_clip.gx_rectangle_left =
            (GX_VALUE) ((USHORT) param.copy_clip.gx_rectangle_left & 0xfffeU);
        param.copy_clip.gx_rectangle_right =
            (GX_VALUE) ((USHORT) param.copy_clip.gx_rectangle_right | 1U);
        mode = d2_mode_rgb565;
    }
    else
    {
        mode = d2_mode_argb8888;
    }

    /* Offset canvas within frame buffer. */
    _gx_utility_rectangle_shift(&param.copy_clip, canvas->gx_canvas_display_offset_x,
                                canvas->gx_canvas_display_offset_y);

    _gx_utility_rectangle_overlap_detect(&param.copy_clip, &display_size, &param.copy_clip);

    param.copy_width  = (param.copy_clip.gx_rectangle_right - param.copy_clip.gx_rectangle_left) + 1;
    param.copy_height = (param.copy_clip.gx_rectangle_bottom - param.copy_clip.gx_rectangle_top) + 1;

    if ((param.copy_width <= 0) || (param.copy_height <= 0))
    {
        return;
    }

    /** Set parameters for the screen rotation. */
    param.angle = rotation_angle;
    gx_dave2d_rotate_canvas_to_working_param_set(&param, display, canvas);

    /** Perform D/AVE 2D texture mapping and render box operation. */
    gx_dave2d_rotate_canvas_to_working_image_draw(dave, &param, mode, display, canvas);
    gx_dave2d_fill_mode_set(dave, fillmode_bkup);
}

#endif

#if (GX_USE_RENESAS_JPEG == 1)

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Subroutine for Hardware accelerated JPEG draw to open JPEG driver.
 *  This function is called by _gx_renesas_jpeg_draw().
 * @param   p_context[in]               Pointer to a GUIX draw context
 * @param   p_jpeg[in,out]    Pointer to a JPEG driver instance
 * @param   p_jpeg[in,out]    Pointer to a JPEG driver instance
 * @param   p_bytes_per_pixel[out]      Pointer to the memory area to store bytes per pixel data
 * @retval  status                      Return code from a JPEG driver API
 **********************************************************************************************************************/
static INT gx_renesas_jpeg_draw_open (GX_DRAW_CONTEXT * p_context, jpeg_instance_t * p_jpeg, UINT * p_bytes_per_pixel)
{
    /* Get the GUIX output color format */
    GX_VALUE color_format = p_context->gx_draw_context_display->gx_display_color_format;

    if (GX_COLOR_FORMAT_32ARGB == color_format)
    {
        *p_bytes_per_pixel = 4U;
    }
    else if (GX_COLOR_FORMAT_565RGB == color_format)
    {
        *p_bytes_per_pixel = 2U;
    }
    else
    {

        /** Simply return to the caller if invalid color format is specified */
        return FSP_ERR_JPEG_ERR;
    }

    /** Opens the JPEG driver.  */
    return (INT) p_jpeg->p_api->open(p_jpeg->p_ctrl, p_jpeg->p_cfg);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Subroutine for Hardware accelerated JPEG draw to get minimum height.
 *  This function is called by _gx_renesas_jpeg_draw().
 * @param   format[in]          JPEG color format (YCbCr)
 * @param   width[in]           Image width
 * @param   height[in]          Image height
 * @retval  minimum_height      Minimum height for JPEG decoding
 **********************************************************************************************************************/
static UINT gx_renesas_jpeg_draw_minimum_height_get (jpeg_color_space_t format, GX_VALUE width, GX_VALUE height)
{
    UINT align_x = JPEG_ALIGNMENT_8;
    UINT align_y = JPEG_ALIGNMENT_8;

    /** Compute the decoding width and height based on pixel format. Return an error if the input JPEG size is not valid. */
    switch (format)
    {
        case JPEG_COLOR_SPACE_YCBCR444:
        {
            /* 8 lines by 8 pixels. */
            break;
        }

        case JPEG_COLOR_SPACE_YCBCR422:
        {
            /* 8 lines by 16 pixels. */
            align_x = JPEG_ALIGNMENT_16;

            break;
        }

        case JPEG_COLOR_SPACE_YCBCR411:
        {
            /* 8 lines by 32 pixels. */
            align_x = JPEG_ALIGNMENT_32;

            break;
        }

        case JPEG_COLOR_SPACE_YCBCR420:
        {
            /* 16 lines by 16 pixels. */
            align_x = JPEG_ALIGNMENT_16;
            align_y = JPEG_ALIGNMENT_16;

            break;
        }

        default:

            return 0U;
    }

    /* If the width and height are in even increments of JPEG MCUs then return the MCU height */
    if (!(((USHORT) width & align_x) || ((USHORT) height & align_y)))
    {
        return align_y + 1;
    }

    return 0U;
}

/*******************************************************************************************************************//**
 * @brief  Subroutine for Hardware accelerated JPEG draw to perform JPEG decoding in output streaming mode.
 *  This function is called by _gx_renesas_jpeg_draw_output_streaming().
 * @param   p_jpeg[in]                 Pointer to a parameter set for the JPEG decode framework instance
 * @retval  FSP_SUCCESS       Display device was opened successfully.
 * @retval  Others            See @ref Common_Error_Codes for other possible return codes. This function calls
 *                            jpeg_api_t::wait.
 **********************************************************************************************************************/
static INT gx_renesas_jpeg_draw_output_streaming_wait (void)
{
    INT ret;

    jpeg_status_t jpeg_status = JPEG_STATUS_NONE;

    while (((UINT) (JPEG_STATUS_OUTPUT_PAUSE) &(UINT) jpeg_status) == 0U)
    {
        ret = gx_renesas_jpeg_wait(&jpeg_status, 1000);
        if (ret != FSP_SUCCESS)
        {

            /* Nothing to draw. Just return. */
            return ret;
        }

        if ((UINT) (JPEG_STATUS_OPERATION_COMPLETE) &(UINT) jpeg_status)
        {
            /* Finished JPEG decoding. */
            break;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Subroutine for Hardware accelerated JPEG draw to perform JPEG decoding in
 * output streaming mode.
 *  This function is called by _gx_renesas_jpeg_draw().
 * @param   p_param[in]                 Pointer to a parameter set for the JPEG decode output steaming
 **********************************************************************************************************************/
static VOID gx_renesas_jpeg_draw_output_streaming (jpeg_output_streaming_param_t * p_param)
{
    INT               ret;
    jpeg_instance_t * p_jpeg              = p_param->p_jpeg;
    UINT              lines_decoded       = 0;
    UINT              remaining_lines     = 0;
    UINT              total_lines_decoded = 0;
    GX_VIEW         * view;
    GX_RECTANGLE      clip_rect;
    GX_PIXELMAP       out_pixelmap;
    GX_DRAW_CONTEXT * p_context    = p_param->p_context;
    GX_VALUE          color_format = p_context->gx_draw_context_display->gx_display_color_format;
    GX_RECTANGLE      bound;

    remaining_lines = (UINT) p_param->image_height;

    /** Sets up the out_pixelmap structure. */
    out_pixelmap.gx_pixelmap_data          = (GX_UBYTE *) (p_param->output_buffer);
    out_pixelmap.gx_pixelmap_data_size     = (ULONG) p_param->jpeg_buffer_size;
    out_pixelmap.gx_pixelmap_format        = (GX_UBYTE) color_format;
    out_pixelmap.gx_pixelmap_height        = p_param->image_height;
    out_pixelmap.gx_pixelmap_width         = p_param->image_width;
    out_pixelmap.gx_pixelmap_version_major = p_param->p_pixelmap->gx_pixelmap_version_major;
    out_pixelmap.gx_pixelmap_version_minor = p_param->p_pixelmap->gx_pixelmap_version_minor;
    out_pixelmap.gx_pixelmap_flags         = (GX_UBYTE) 0;

    /** Calculate rectangle that bounds the JPEG */
    gx_utility_rectangle_define(&bound, (GX_VALUE) p_param->x, (GX_VALUE) p_param->y,
                                (GX_VALUE) ((p_param->x + p_param->image_width) - 1),
                                (GX_VALUE) ((p_param->y + p_param->image_height) - 1));

    /** Clip the line bounding box to the dirty rectangle */
    if (!gx_utility_rectangle_overlap_detect(&bound, &p_context->gx_draw_context_dirty, &bound))
    {

        /* Nothing to draw. Just return. */
        return;
    }

    while (remaining_lines > 0U)
    {
        /* If running with Dave2D, make sure previous block drawing is completed before we attempt to decode
         * new jpeg block.
         */
 #if (GX_RENESAS_DAVE2D_DRAW == 1)
        CHECK_DAVE_STATUS(d2_endframe(p_context->gx_draw_context_display->gx_display_accelerator))

        /* trigger execution of previous display list, switch to new display list */
        CHECK_DAVE_STATUS(d2_startframe(p_context->gx_draw_context_display->gx_display_accelerator))
 #endif

        /** Assigns the output buffer to start the decoding process. */
        ret =
            (INT) p_jpeg->p_api->outputBufferSet(p_jpeg->p_ctrl,
                                                 (VOID *) (INT) (out_pixelmap.gx_pixelmap_data),
                                                 (UINT) p_param->jpeg_buffer_size);
        if (ret != FSP_SUCCESS)
        {

            /* Nothing to draw. Just return. */
            return;
        }

        /** Waits for the device to finish. */
        ret = gx_renesas_jpeg_draw_output_streaming_wait();
        if (ret != FSP_SUCCESS)
        {
            return;
        }

        ret = (INT) p_jpeg->p_api->linesDecodedGet(p_jpeg->p_ctrl, (uint32_t *) &lines_decoded);

        if ((ret != FSP_SUCCESS) || (lines_decoded == 0U))
        {

            /* Nothing to draw. Just return. */
            return;
        }

        remaining_lines -= lines_decoded;

        out_pixelmap.gx_pixelmap_height    = (GX_VALUE) lines_decoded;
        out_pixelmap.gx_pixelmap_data_size =
            (ULONG) (lines_decoded * ((UINT) p_param->image_width * p_param->bytes_per_pixel));

        view = p_context->gx_draw_context_view_head;

        while (view)
        {
            if (!gx_utility_rectangle_overlap_detect(&view->gx_view_rectangle, &bound, &clip_rect))
            {
                view = view->gx_view_next;
                continue;
            }

            p_context->gx_draw_context_clip = &clip_rect;

            /** Draws map.  */
            p_context->gx_draw_context_display->gx_display_driver_pixelmap_draw(p_context,
                                                                                p_param->x,
                                                                                p_param->y +
                                                                                (INT) total_lines_decoded,
                                                                                &out_pixelmap);

            /** Goes to the next view. */
            view = view->gx_view_next;
        }

        total_lines_decoded += lines_decoded;

 #if (GX_RENESAS_DAVE2D_DRAW == 1)
        CHECK_DAVE_STATUS(d2_endframe(p_context->gx_draw_context_display->gx_display_accelerator))

        /* trigger execution of previous display list, switch to new display list */
        CHECK_DAVE_STATUS(d2_startframe(p_context->gx_draw_context_display->gx_display_accelerator))
 #endif
    }
}

#endif                                 /* GX_USE_RENESAS_JPEG */

#if (GX_RENESAS_DAVE2D_DRAW == 0)

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Frame buffer toggle operation with copying data by software without
 * D/AVE 2D acceleration and screen rotation. This function is called by _gx_ra_buffer_toggle().
 * This function is called by _gx_ra_buffer_toggle.
 * @param[in]     canvas            Pointer to a canvas
 * @param[in]     copy              Pointer to a rectangle region to copy.
 **********************************************************************************************************************/
static VOID gx_copy_visible_to_working (GX_CANVAS * canvas, GX_RECTANGLE * copy)
{
    GX_RECTANGLE display_size;
    GX_RECTANGLE copy_clip;

    ULONG * pGetRow;
    ULONG * pPutRow;

    INT copy_width;
    INT copy_height;
    INT canvas_stride;
    INT display_stride;

    ULONG * pGet;
    ULONG * pPut;
    INT     row;
    INT     col;

    GX_DISPLAY * display = canvas->gx_canvas_display;
    gx_utility_rectangle_define(&display_size, 0, 0, (GX_VALUE) (display->gx_display_width - 1),
                                (GX_VALUE) (display->gx_display_height - 1));
    copy_clip = *copy;

    /** Is color format RGB565? */
    if ((INT) display->gx_display_color_format == GX_COLOR_FORMAT_565RGB)
    {
        /** If yes, align copy region on 32-bit boundary. */
        copy_clip.gx_rectangle_left  = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_left & 0xfffeU);
        copy_clip.gx_rectangle_right = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_right | 1U);
    }

    /** Offset canvas within frame buffer. */
    gx_utility_rectangle_shift(&copy_clip, canvas->gx_canvas_display_offset_x, canvas->gx_canvas_display_offset_y);

    gx_utility_rectangle_overlap_detect(&copy_clip, &display_size, &copy_clip);
    copy_width  = (copy_clip.gx_rectangle_right - copy_clip.gx_rectangle_left) + 1;
    copy_height = (copy_clip.gx_rectangle_bottom - copy_clip.gx_rectangle_top) + 1;

    /** Return if copy width or height was invalid. */
    if ((copy_width <= 0) || (copy_height <= 0))
    {
        return;
    }

    pGetRow = (ULONG *) visible_frame;
    pPutRow = (ULONG *) working_frame;

    /** Calculate copy width, canvas stride, source and destination pointer for data copy. */
    if ((INT) display->gx_display_color_format == GX_COLOR_FORMAT_565RGB)
    {
        copy_width   /= 2;
        canvas_stride = canvas->gx_canvas_x_resolution / 2;
        pPutRow       = pPutRow + ((INT) copy_clip.gx_rectangle_top * canvas_stride);
        pPutRow       = pPutRow + ((INT) copy_clip.gx_rectangle_left / 2);

        display_stride = display->gx_display_width / 2;
        pGetRow        = pGetRow +
                         ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * display_stride);
        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left) / 2);
    }
    else
    {
        canvas_stride = canvas->gx_canvas_x_resolution;
        pPutRow       = pPutRow + ((INT) copy_clip.gx_rectangle_top * canvas_stride);
        pPutRow       = pPutRow + (INT) copy_clip.gx_rectangle_left;

        display_stride = display->gx_display_width;
        pGetRow        = pGetRow +
                         ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * display_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);
    }

    /** Copy data by software. */
    for (row = 0; row < copy_height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (col = 0; col < copy_width; col++)
        {
            *pPut = *pGet;
            ++pPut;
            ++pGet;
        }

        pPutRow += canvas_stride;
        pGetRow += display_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 16bpp Frame buffer software draw function.
 * This function is called by gx_rotate_canvas_to_working_16bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     stride            Image memory stride
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_16bpp_draw (USHORT * pGetRow,
                                                    USHORT * pPutRow,
                                                    INT      width,
                                                    INT      height,
                                                    INT      stride)
{
    USHORT * pGet;
    USHORT * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;
        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pPut;
            ++pGet;
        }

        pGetRow += stride;
        pPutRow += stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 16bpp Frame buffer software draw function with rotating image 90 degree.
 * This function is called by gx_rotate_canvas_to_working_16bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     canvas_stride     Frame buffer memory stride (of the canvas)
 * @param[in]     disp_stride       Frame buffer memory stride (of the destination frame buffer)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_16bpp_draw_rotate90 (USHORT * pGetRow,
                                                             USHORT * pPutRow,
                                                             INT      width,
                                                             INT      height,
                                                             INT      canvas_stride,
                                                             INT      disp_stride)
{
    USHORT * pGet;
    USHORT * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pGet;
            pPut += disp_stride;
        }

        pPutRow--;
        pGetRow += canvas_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 16bpp Frame buffer software draw function with rotating image 180 degree.
 * This function is called by gx_rotate_canvas_to_working_16bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     stride            Image memory stride
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_16bpp_draw_rotate180 (USHORT * pGetRow,
                                                              USHORT * pPutRow,
                                                              INT      width,
                                                              INT      height,
                                                              INT      stride)
{
    USHORT * pGet;
    USHORT * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;
        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            --pPut;
            ++pGet;
        }

        pGetRow += stride;
        pPutRow -= stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 16bpp Frame buffer software draw function with rotating image 270 degree.
 * This function is called by gx_rotate_canvas_to_working_16bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     canvas_stride     Frame buffer memory stride (of the canvas)
 * @param[in]     disp_stride       Frame buffer memory stride (of the destination frame buffer)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_16bpp_draw_rotate270 (USHORT * pGetRow,
                                                              USHORT * pPutRow,
                                                              INT      width,
                                                              INT      height,
                                                              INT      canvas_stride,
                                                              INT      disp_stride)
{
    USHORT * pGet;
    USHORT * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pGet;
            pPut -= disp_stride;
        }

        pPutRow++;
        pGetRow += canvas_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Frame buffer software copy operation with screen rotation for 16bpp color
 * format. This function is called by _gx_ra_buffer_toggle().
 * @param[in]     canvas            Pointer to a canvas
 * @param[in]     copy              Pointer to a rectangle region to copy.
 * @param[in]     angle    Rotation angle (0, 90, 180 or 270)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_16bpp (GX_CANVAS * canvas, GX_RECTANGLE * copy, INT angle)
{
    GX_RECTANGLE display_size;
    GX_RECTANGLE copy_clip;

    USHORT * pGetRow;
    USHORT * pPutRow;

    INT copy_width;
    INT copy_height;
    INT canvas_stride;
    INT display_stride;

    GX_DISPLAY * display = canvas->gx_canvas_display;
    gx_utility_rectangle_define(&display_size, 0, 0, (GX_VALUE) (display->gx_display_width - 1),
                                (GX_VALUE) (display->gx_display_height - 1));
    copy_clip = *copy;

    /** Align copy region on 32-bit memory boundary. */
    copy_clip.gx_rectangle_left   = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_left & 0xfffeU);
    copy_clip.gx_rectangle_top    = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_top & 0xfffeU);
    copy_clip.gx_rectangle_right  = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_right | 1U);
    copy_clip.gx_rectangle_bottom = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_bottom | 1U);

    /** Offset canvas within frame buffer. */
    gx_utility_rectangle_shift(&copy_clip, canvas->gx_canvas_display_offset_x, canvas->gx_canvas_display_offset_y);

    gx_utility_rectangle_overlap_detect(&copy_clip, &display_size, &copy_clip);
    copy_width  = (copy_clip.gx_rectangle_right - copy_clip.gx_rectangle_left) + 1;
    copy_height = (copy_clip.gx_rectangle_bottom - copy_clip.gx_rectangle_top) + 1;

    if ((copy_width <= 0) || (copy_height <= 0))
    {
        return;
    }

    pGetRow = (USHORT *) canvas->gx_canvas_memory;
    pPutRow = (USHORT *) working_frame;

    display_stride = display->gx_display_height;
    canvas_stride  = canvas->gx_canvas_x_resolution;

    if (angle == GX_SCREEN_ROTATION_NONE)
    {
        pPutRow = pPutRow + ((INT) copy_clip.gx_rectangle_top * canvas_stride);
        pPutRow = pPutRow + (INT) copy_clip.gx_rectangle_left;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_16bpp_draw(pGetRow, pPutRow, copy_width, copy_height, canvas_stride);
    }
    else if (angle == GX_SCREEN_ROTATION_FLIP)
    {
        pPutRow = pPutRow + (INT) ((display->gx_display_height - copy_clip.gx_rectangle_top) * canvas_stride);
        pPutRow = pPutRow - (INT) (copy_clip.gx_rectangle_left + 1);

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_16bpp_draw_rotate180(pGetRow, pPutRow, copy_width, copy_height, canvas_stride);
    }
    else if (angle == GX_SCREEN_ROTATION_CCW)
    {
        pPutRow = pPutRow + ((INT) ((display->gx_display_width - 1) - copy_clip.gx_rectangle_left) * display_stride);
        pPutRow = pPutRow + (INT) copy_clip.gx_rectangle_top;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_16bpp_draw_rotate270(pGetRow,
                                                         pPutRow,
                                                         copy_width,
                                                         copy_height,
                                                         canvas_stride,
                                                         display_stride);
    }
    else                               /* angle == GX_SCREEN_ROTATION_CW */
    {
        pPutRow = pPutRow + ((INT) copy_clip.gx_rectangle_left * display_stride);
        pPutRow = pPutRow + (INT) (display_stride - 1);
        pPutRow = pPutRow - (INT) copy_clip.gx_rectangle_top;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_16bpp_draw_rotate90(pGetRow,
                                                        pPutRow,
                                                        copy_width,
                                                        copy_height,
                                                        canvas_stride,
                                                        display_stride);
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 32bpp Frame buffer software draw function.
 * This function is called by gx_rotate_canvas_to_working_32bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     stride            Image memory stride
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_32bpp_draw (ULONG * pGetRow, ULONG * pPutRow, INT width, INT height, INT stride)
{
    ULONG * pGet;
    ULONG * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;
        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pPut;
            ++pGet;
        }

        pGetRow += stride;
        pPutRow += stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 32bpp Frame buffer software draw function with rotating image 90 degree.
 * This function is called by gx_rotate_canvas_to_working_32bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     canvas_stride     Frame buffer memory stride (of the canvas)
 * @param[in]     disp_stride       Frame buffer memory stride (of the destination frame buffer)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_32bpp_draw_rotate90 (ULONG * pGetRow,
                                                             ULONG * pPutRow,
                                                             INT     width,
                                                             INT     height,
                                                             INT     canvas_stride,
                                                             INT     disp_stride)
{
    ULONG * pGet;
    ULONG * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pGet;
            pPut += disp_stride;
        }

        pPutRow--;
        pGetRow += canvas_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 32bpp Frame buffer software draw function with rotating image 180 degree.
 * This function is called by gx_rotate_canvas_to_working_32bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     stride            Image memory stride
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_32bpp_draw_rotate180 (ULONG * pGetRow,
                                                              ULONG * pPutRow,
                                                              INT     width,
                                                              INT     height,
                                                              INT     stride)
{
    ULONG * pGet;
    ULONG * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;
        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            --pPut;
            ++pGet;
        }

        pGetRow += stride;
        pPutRow -= stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 32bpp Frame buffer software draw function with rotating image 270 degree.
 * This function is called by gx_rotate_canvas_to_working_32bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     canvas_stride     Frame buffer memory stride (of the canvas)
 * @param[in]     disp_stride       Frame buffer memory stride (of the destination frame buffer)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_32bpp_draw_rotate270 (ULONG * pGetRow,
                                                              ULONG * pPutRow,
                                                              INT     width,
                                                              INT     height,
                                                              INT     canvas_stride,
                                                              INT     disp_stride)
{
    ULONG * pGet;
    ULONG * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pGet;
            pPut -= disp_stride;
        }

        pPutRow++;
        pGetRow += canvas_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Frame buffer software copy operation with screen rotation for 32bpp color
 * format. This function is called by _gx_ra_buffer_toggle().
 * @param[in]     canvas            Pointer to a canvas
 * @param[in]     copy              Pointer to a rectangle region to copy.
 * @param[in]     angle    Rotation angle (0, 90, 180 or 270)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_32bpp (GX_CANVAS * canvas, GX_RECTANGLE * copy, INT angle)
{
    GX_RECTANGLE display_size;
    GX_RECTANGLE copy_clip;

    ULONG * pGetRow;
    ULONG * pPutRow;

    INT copy_width;
    INT copy_height;
    INT canvas_stride;
    INT display_stride;

    GX_DISPLAY * display = canvas->gx_canvas_display;
    gx_utility_rectangle_define(&display_size, 0, 0, (GX_VALUE) (display->gx_display_width - 1),
                                (GX_VALUE) (display->gx_display_height - 1));
    copy_clip = *copy;

    /** Align copy region on 32-bit memory boundary. */
    copy_clip.gx_rectangle_left   = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_left & 0xfffeU);
    copy_clip.gx_rectangle_top    = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_top & 0xfffeU);
    copy_clip.gx_rectangle_right  = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_right | 1U);
    copy_clip.gx_rectangle_bottom = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_bottom | 1U);

    /** Offset canvas within frame buffer. */
    gx_utility_rectangle_shift(&copy_clip, canvas->gx_canvas_display_offset_x, canvas->gx_canvas_display_offset_y);

    gx_utility_rectangle_overlap_detect(&copy_clip, &display_size, &copy_clip);
    copy_width  = ((copy_clip.gx_rectangle_right - copy_clip.gx_rectangle_left) + 1);
    copy_height = (copy_clip.gx_rectangle_bottom - copy_clip.gx_rectangle_top) + 1;

    if ((copy_width <= 0) || (copy_height <= 0))
    {
        return;
    }

    pGetRow = (ULONG *) canvas->gx_canvas_memory;
    pPutRow = (ULONG *) working_frame;

    display_stride = (INT) display->gx_display_height;
    canvas_stride  = (INT) canvas->gx_canvas_x_resolution;

    if (angle == GX_SCREEN_ROTATION_NONE)
    {
        pPutRow = pPutRow + ((INT) copy_clip.gx_rectangle_top * canvas_stride);
        pPutRow = pPutRow + (INT) copy_clip.gx_rectangle_left;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_32bpp_draw(pGetRow, pPutRow, copy_width, copy_height, canvas_stride);
    }
    else if (angle == GX_SCREEN_ROTATION_FLIP)
    {
        pPutRow = pPutRow + ((INT) (display->gx_display_height - copy_clip.gx_rectangle_top) * canvas_stride);
        pPutRow = pPutRow - (INT) (copy_clip.gx_rectangle_left + 1);

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_32bpp_draw_rotate180(pGetRow, pPutRow, copy_width, copy_height, canvas_stride);
    }
    else if (angle == GX_SCREEN_ROTATION_CCW)
    {
        pPutRow = pPutRow + ((INT) ((display->gx_display_width - 1) - copy_clip.gx_rectangle_left) * display_stride);
        pPutRow = pPutRow + (INT) copy_clip.gx_rectangle_top;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_32bpp_draw_rotate270(pGetRow,
                                                         pPutRow,
                                                         copy_width,
                                                         copy_height,
                                                         canvas_stride,
                                                         display_stride);
    }
    else                               /* angle == GX_SCREEN_ROTATION_CW */
    {
        pPutRow = pPutRow + ((INT) copy_clip.gx_rectangle_left * display_stride);
        pPutRow = pPutRow + (INT) (display_stride - 1);
        pPutRow = pPutRow - (INT) copy_clip.gx_rectangle_top;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_32bpp_draw_rotate90(pGetRow,
                                                        pPutRow,
                                                        copy_width,
                                                        copy_height,
                                                        canvas_stride,
                                                        display_stride);
    }
}

#else                                  /* (GX_RENESAS_DAVE2D_DRAW == 1) */

/*******************************************************************************************************************//**
 * @brief  Rotate a coordinate to CW or CCW (90 or 270 degree) screen orientation.
 * @param[in]     context     Pointer to current draw context
 * @param[in]     x           Pointer to X coordinate
 * @param[in]     y           Pointer to Y coordinate
 **********************************************************************************************************************/
VOID gx_dave2d_coordinate_rotate (GX_DRAW_CONTEXT * context, INT * x, INT * y)
{
    /* Swap dimensions if we're running in a 'portrait' orientation */
    INT temp = *x;
    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        *x = *y;
        *y = context->gx_draw_context_canvas->gx_canvas_x_resolution - temp - 1;
    }
    else
    {
        *x = context->gx_draw_context_canvas->gx_canvas_y_resolution - *y - 1;
        *y = temp;
    }
}

/*******************************************************************************************************************//**
 * @brief  Rotate a pixelmap position coordinate to CW or CCW (90 or 270 degree) screen orientation.
 * @param[in]     context     Pointer to current draw context
 * @param[in]     xpos        Pointer to X coordinate of image-relative top-left corner
 * @param[in]     ypos        Pointer to Y coordinate of image-relative top-left corner
 * @param[in]     pixelmap    Pointer to pixelmap to be placed
 **********************************************************************************************************************/
VOID gx_dave2d_pixelmap_coordinate_rotate (GX_DRAW_CONTEXT * context, INT * xpos, INT * ypos, GX_PIXELMAP * pixelmap)
{
    /* Swap dimensions if we're running in a 'portrait' orientation */
    INT temp = *xpos;
    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        *xpos = *ypos;
        *ypos = context->gx_draw_context_canvas->gx_canvas_x_resolution - temp - pixelmap->gx_pixelmap_width;
    }
    else
    {
        *xpos = context->gx_draw_context_canvas->gx_canvas_y_resolution - *ypos - pixelmap->gx_pixelmap_height;
        *ypos = temp;
    }
}

/*******************************************************************************************************************//**
 * @brief  Rotate a rectangle to CW or CCW (90 or 270 degree) screen orientation.
 * @param[in]     context         Pointer to current draw context
 * @param[in]     rectangle_in    Pointer to input rectangle
 * @param[out]    rectangle_out   Pointer to output rectangle
 **********************************************************************************************************************/
VOID gx_dave2d_rectangle_rotate (GX_DRAW_CONTEXT * context, GX_RECTANGLE * rectangle_in, GX_RECTANGLE * rectangle_out)
{
    GX_VALUE x0 = rectangle_in->gx_rectangle_left;
    GX_VALUE y0 = rectangle_in->gx_rectangle_top;
    GX_VALUE x1 = rectangle_in->gx_rectangle_right;
    GX_VALUE y1 = rectangle_in->gx_rectangle_bottom;

    GX_VALUE canvas_x = (GX_VALUE) (context->gx_draw_context_canvas->gx_canvas_x_resolution - 1);
    GX_VALUE canvas_y = (GX_VALUE) (context->gx_draw_context_canvas->gx_canvas_y_resolution - 1);

    /* Swap coordinates if we're running in a 'portrait' orientation */
    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        GX_VALUE rectangle_x = (GX_VALUE) (x1 - x0);

        rectangle_out->gx_rectangle_left   = y0;
        rectangle_out->gx_rectangle_top    = (GX_VALUE) (canvas_x - x0 - rectangle_x - 1);
        rectangle_out->gx_rectangle_right  = y1;
        rectangle_out->gx_rectangle_bottom = (GX_VALUE) (canvas_x - x1 + rectangle_x);
    }
    else
    {
        rectangle_out->gx_rectangle_left   = (GX_VALUE) (canvas_y - y1);
        rectangle_out->gx_rectangle_top    = x0;
        rectangle_out->gx_rectangle_right  = (GX_VALUE) (canvas_y - y0);
        rectangle_out->gx_rectangle_bottom = x1;
    }
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_horizontal_pattern_line_draw_565
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          X axis start coordinate
 * @param   xend[in]            X axis end coordinate
 * @param   ypos[in]            Y coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_horizontal_pattern_line_draw_565 (GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos)
{
    INT ystart;
    INT yend;
    INT xpos;

    INT length = xend - xstart;

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        xpos   = ypos;
        ystart = context->gx_draw_context_canvas->gx_canvas_x_resolution - xend - 1;
        yend   = ystart + length;
    }
    else
    {
        xpos   = context->gx_draw_context_canvas->gx_canvas_y_resolution - ypos - 1;
        ystart = xstart;
        yend   = xend;
    }

    _gx_dave2d_vertical_pattern_line_draw_565(context, ystart, yend, xpos);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_vertical_pattern_line_draw_565
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   ystart[in]          Y axis start coordinate
 * @param   yend[in]            Y axis end coordinate
 * @param   xpos[in]            X coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_vertical_pattern_line_draw_565 (GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos)
{
    INT xstart;
    INT xend;
    INT ypos;

    INT length = yend - ystart;

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        xstart = ystart;
        xend   = yend;
        ypos   = context->gx_draw_context_canvas->gx_canvas_x_resolution - xpos - 1;
    }
    else
    {
        xstart = context->gx_draw_context_canvas->gx_canvas_y_resolution - yend - 1;
        xend   = xstart + length;
        ypos   = xpos;
    }

    _gx_dave2d_horizontal_pattern_line_draw_565(context, xstart, xend, ypos);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pixel_write_565
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               X coordinate
 * @param   y[in]               Y coordinate
 * @param   color[in]           Pixel color
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pixel_write_565 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color)
{
    gx_dave2d_coordinate_rotate(context, &x, &y);
    _gx_dave2d_pixel_write_565(context, x, y, color);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pixel_blend_565
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               X coordinate
 * @param   y[in]               Y coordinate
 * @param   fcolor[in]          Pixel color
 * @param   alpha[in]           Pixel alpha
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pixel_blend_565 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha)
{
    gx_dave2d_coordinate_rotate(context, &x, &y);
    _gx_dave2d_pixel_blend_565(context, x, y, fcolor, alpha);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_horizontal_pattern_line_draw_888
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          X axis start coordinate
 * @param   xend[in]            X axis end coordinate
 * @param   ypos[in]            Y coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_horizontal_pattern_line_draw_888 (GX_DRAW_CONTEXT * context, INT xstart, INT xend, INT ypos)
{
    INT ystart;
    INT yend;
    INT xpos;

    INT length = xend - xstart;

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        xpos   = ypos;
        ystart = context->gx_draw_context_canvas->gx_canvas_x_resolution - xend - 1;
        yend   = ystart + length;
    }
    else
    {
        xpos   = context->gx_draw_context_canvas->gx_canvas_y_resolution - ypos - 1;
        ystart = xstart;
        yend   = xend;
    }

    _gx_dave2d_vertical_pattern_line_draw_888(context, ystart, yend, xpos);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_vertical_pattern_line_draw_888
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   ystart[in]          Y axis start coordinate
 * @param   yend[in]            Y axis end coordinate
 * @param   xpos[in]            X coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_vertical_pattern_line_draw_888 (GX_DRAW_CONTEXT * context, INT ystart, INT yend, INT xpos)
{
    INT xstart;
    INT xend;
    INT ypos;

    INT length = yend - ystart;

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        xstart = ystart;
        xend   = yend;
        ypos   = context->gx_draw_context_canvas->gx_canvas_x_resolution - xpos - 1;
    }
    else
    {
        xstart = context->gx_draw_context_canvas->gx_canvas_y_resolution - yend - 1;
        xend   = xstart + length;
        ypos   = xpos;
    }

    _gx_dave2d_horizontal_pattern_line_draw_888(context, xstart, xend, ypos);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pixel_write_888
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               X coordinate
 * @param   y[in]               Y coordinate
 * @param   color[in]           Pixel color
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pixel_write_888 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR color)
{
    gx_dave2d_coordinate_rotate(context, &x, &y);
    _gx_dave2d_pixel_write_888(context, x, y, color);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pixel_blend_888
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   x[in]               X coordinate
 * @param   y[in]               Y coordinate
 * @param   fcolor[in]          Pixel color
 * @param   alpha[in]           Pixel alpha
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pixel_blend_888 (GX_DRAW_CONTEXT * context, INT x, INT y, GX_COLOR fcolor, GX_UBYTE alpha)
{
    gx_dave2d_coordinate_rotate(context, &x, &y);
    _gx_dave2d_pixel_blend_888(context, x, y, fcolor, alpha);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pixelmap_rotate_16bpp
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            X-coordinate of top-left pixel
 * @param   ypos[in]            Y-coordinate of top-left pixel
 * @param   pixelmap[in]        Pointer to a GX_PIXELMAP structure
 * @param   angle[in]           Pixelmap rotation angle
 * @param   rot_cx[in]          X-coordinate of rotation axis (-1 for center of pixelmap)
 * @param   rot_cy[in]          Y-coordinate of rotation axis (-1 for center of pixelmap)
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pixelmap_rotate_16bpp (GX_DRAW_CONTEXT * context,
                                               INT               xpos,
                                               INT               ypos,
                                               GX_PIXELMAP     * pixelmap,
                                               INT               angle,
                                               INT               rot_cx,
                                               INT               rot_cy)
{
    gx_dave2d_pixelmap_coordinate_rotate(context, &xpos, &ypos, pixelmap);

    INT temp = rot_cx;
    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        if (rot_cx != -1)
        {
            rot_cx = rot_cy;
        }

        if (rot_cy != -1)
        {
            rot_cy = pixelmap->gx_pixelmap_width - temp - 1;
        }
    }
    else
    {
        if (rot_cx != -1)
        {
            rot_cx = pixelmap->gx_pixelmap_height - rot_cy - 1;
        }

        if (rot_cy != -1)
        {
            rot_cy = temp;
        }
    }

    _gx_dave2d_pixelmap_rotate_16bpp(context, xpos, ypos, pixelmap, angle, rot_cx, rot_cy);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_drawing_initiate
 * @param   display[in]         Pointer to a GUIX display context
 * @param   canvas[in]          Pointer to a GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_drawing_initiate (GX_DISPLAY * display, GX_CANVAS * canvas)
{
    _gx_dave2d_drawing_initiate(display, canvas);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_drawing_complete
 * @param   display[in]         Pointer to a GUIX display context
 * @param   canvas[in]          Pointer to a GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_drawing_complete (GX_DISPLAY * display, GX_CANVAS * canvas)
{
    _gx_dave2d_drawing_complete(display, canvas);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_horizontal_line
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          X axis start coordinate
 * @param   xend[in]            X axis end coordinate
 * @param   ypos[in]            Y coordinate
 * @param   width[in]           Line width
 * @param   color[in]           Line color
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_horizontal_line (GX_DRAW_CONTEXT * context,
                                         INT               xstart,
                                         INT               xend,
                                         INT               ypos,
                                         INT               width,
                                         GX_COLOR          color)
{
    INT ystart;
    INT yend;
    INT xpos;

    INT length = xend - xstart;

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        xpos   = ypos;
        ystart = context->gx_draw_context_canvas->gx_canvas_x_resolution - xend - 1;
        yend   = ystart + length;
    }
    else
    {
        xpos   = context->gx_draw_context_canvas->gx_canvas_y_resolution - ypos - 1;
        ystart = xstart;
        yend   = xend;
    }

    _gx_dave2d_vertical_line(context, ystart, yend, xpos, width, color);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_vertical_line
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   ystart[in]          Y axis start coordinate
 * @param   yend[in]            Y axis end coordinate
 * @param   xpos[in]            X coordinate
 * @param   width[in]           Line width
 * @param   color[in]           Line color
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_vertical_line (GX_DRAW_CONTEXT * context,
                                       INT               ystart,
                                       INT               yend,
                                       INT               xpos,
                                       INT               width,
                                       GX_COLOR          color)
{
    INT xstart;
    INT xend;
    INT ypos;

    INT length = yend - ystart;

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        xstart = ystart;
        xend   = yend;
        ypos   = context->gx_draw_context_canvas->gx_canvas_x_resolution - xpos - 1;
    }
    else
    {
        xstart = context->gx_draw_context_canvas->gx_canvas_y_resolution - yend - 1;
        xend   = xstart + length;
        ypos   = xpos;
    }

    _gx_dave2d_horizontal_line(context, xstart, xend, ypos, width, color);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_canvas_copy
 * @param   canvas[in]          Pointer to a source GUIX canvas
 * @param   composite[in]       Pointer to a destination GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_canvas_copy (GX_CANVAS * canvas, GX_CANVAS * composite)
{
    FSP_PARAMETER_NOT_USED(canvas);
    FSP_PARAMETER_NOT_USED(composite);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_canvas_blend
 * @param   canvas[in]          Pointer to a source GUIX canvas
 * @param   composite[in]       Pointer to a destination GUIX canvas
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_canvas_blend (GX_CANVAS * canvas, GX_CANVAS * composite)
{
    FSP_PARAMETER_NOT_USED(canvas);
    FSP_PARAMETER_NOT_USED(composite);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_simple_line_draw
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          Start X coordinate
 * @param   ystart[in]          Start Y coordinate
 * @param   xend[in]            End X coordinate
 * @param   yend[in]            End Y coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_simple_line_draw (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    gx_dave2d_coordinate_rotate(context, &xstart, &ystart);
    gx_dave2d_coordinate_rotate(context, &xend, &yend);

    _gx_dave2d_simple_line_draw(context, xstart, ystart, xend, yend);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_simple_wide_line
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          Start X coordinate
 * @param   ystart[in]          Start Y coordinate
 * @param   xend[in]            End X coordinate
 * @param   yend[in]            End Y coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_simple_wide_line (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    gx_dave2d_coordinate_rotate(context, &xstart, &ystart);
    gx_dave2d_coordinate_rotate(context, &xend, &yend);

    _gx_dave2d_simple_wide_line(context, xstart, ystart, xend, yend);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_aliased_line
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          Start X coordinate
 * @param   ystart[in]          Start Y coordinate
 * @param   xend[in]            End X coordinate
 * @param   yend[in]            End Y coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_aliased_line (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    gx_dave2d_coordinate_rotate(context, &xstart, &ystart);
    gx_dave2d_coordinate_rotate(context, &xend, &yend);

    _gx_dave2d_aliased_line(context, xstart, ystart, xend, yend);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_aliased_wide_line
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xstart[in]          Start X coordinate
 * @param   ystart[in]          Start Y coordinate
 * @param   xend[in]            End X coordinate
 * @param   yend[in]            End Y coordinate
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_aliased_wide_line (GX_DRAW_CONTEXT * context, INT xstart, INT ystart, INT xend, INT yend)
{
    gx_dave2d_coordinate_rotate(context, &xstart, &ystart);
    gx_dave2d_coordinate_rotate(context, &xend, &yend);

    _gx_dave2d_aliased_wide_line(context, xstart, ystart, xend, yend);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pixelmap_draw
 *
 * @note   Pixelmaps are pre-rotated by GUIX Studio, so only the draw coordinate needs to be rotated
 *
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            Pixelmap X coordinate
 * @param   ypos[in]            Pixelmap Y coordinate
 * @param   pixelmap[in]        Pointer to a pixelmap
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pixelmap_draw (GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap)
{
    gx_dave2d_pixelmap_coordinate_rotate(context, &xpos, &ypos, pixelmap);

    _gx_dave2d_pixelmap_draw(context, xpos, ypos, pixelmap);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_horizontal_pixelmap_line_draw
 *
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   ystart[in]          Y start position
 * @param   yend[in]            Y end position
 * @param   x[in]               X position
 * @param   info[in]            Pointer to pixelmap fill tracking info
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_horizontal_pixelmap_line_draw (GX_DRAW_CONTEXT       * context,
                                                       INT                     ystart,
                                                       INT                     yend,
                                                       INT                     x,
                                                       GX_FILL_PIXELMAP_INFO * info)
{
    GX_RECTANGLE * old_clip;
    GX_RECTANGLE   clip;
    GX_PIXELMAP  * pixelmap = info->pixelmap;

    if ((info->draw) && (ystart <= yend))
    {
        old_clip = context->gx_draw_context_clip;
        context->gx_draw_context_clip = &clip;

        clip.gx_rectangle_left   = (GX_VALUE) x;
        clip.gx_rectangle_right  = (GX_VALUE) x;
        clip.gx_rectangle_top    = (GX_VALUE) ystart;
        clip.gx_rectangle_bottom = (GX_VALUE) yend;

        if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
        {
            ystart = ystart - (info->x_offset % pixelmap->gx_pixelmap_height);
            x      = x + info->y_offset - pixelmap->gx_pixelmap_width + 1;

            while (ystart <= yend)
            {
                _gx_dave2d_rotated_pixelmap_draw(context, x, ystart, pixelmap);

                ystart += pixelmap->gx_pixelmap_height;
            }
        }
        else
        {
            info->x_offset = (yend - ystart + info->x_offset) % info->pixelmap->gx_pixelmap_height;

            if (info->x_offset)
            {
                info->x_offset = info->pixelmap->gx_pixelmap_height - info->x_offset;
            }

            yend = yend + info->x_offset + 1;
            x    = x - info->y_offset;

            while (yend >= ystart)
            {
                yend -= pixelmap->gx_pixelmap_height;
                _gx_dave2d_rotated_pixelmap_draw(context, x, yend, pixelmap);
            }
        }

        context->gx_draw_context_clip = old_clip;
    }

    info->y_offset++;
    if (info->y_offset >= pixelmap->gx_pixelmap_width)
    {
        info->y_offset = 0;
    }
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pixelmap_blend
 *
 * @note   Pixelmaps are pre-rotated by GUIX Studio, so only the draw coordinate needs to be rotated
 *
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            Pixelmap X coordinate
 * @param   ypos[in]            Pixelmap Y coordinate
 * @param   pixelmap[in]        Pointer to a pixelmap
 * @param   alpha[in]           Alpha value
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pixelmap_blend (GX_DRAW_CONTEXT * context,
                                        INT               xpos,
                                        INT               ypos,
                                        GX_PIXELMAP     * pixelmap,
                                        GX_UBYTE          alpha)
{
    gx_dave2d_pixelmap_coordinate_rotate(context, &xpos, &ypos, pixelmap);

    _gx_dave2d_pixelmap_blend(context, xpos, ypos, pixelmap, alpha);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_polygon_draw
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   vertex[in]          Pointer to GUIX point data
 * @param   num[in]             Number of points
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_polygon_draw (GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num)
{
    /* Use D1 heap functions to allocate memory for swapped coordinates */
    GX_POINT * vertex_rotated = d1_allocmem((uint32_t) num * sizeof(GX_POINT));

    GX_POINT * vertex_ptr = vertex_rotated;

    /* Rotate all coordinates */
    for (INT i = 0; i < num; i++)
    {
        if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
        {
            vertex_ptr->gx_point_x = vertex->gx_point_y;
            vertex_ptr->gx_point_y =
                (GX_VALUE) (context->gx_draw_context_canvas->gx_canvas_x_resolution - vertex->gx_point_x - 1);
        }
        else
        {
            vertex_ptr->gx_point_x =
                (GX_VALUE) (context->gx_draw_context_canvas->gx_canvas_y_resolution - vertex->gx_point_y - 1);
            vertex_ptr->gx_point_y = vertex->gx_point_x;
        }

        vertex++;
        vertex_ptr++;
    }

    _gx_dave2d_polygon_draw(context, vertex_rotated, num);

    /* Free temporary swapped coordinate memory */
    d1_freemem(vertex_rotated);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_polygon_fill
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   vertex[in]          Pointer to GUIX point data
 * @param   num[in]             Number of points
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_polygon_fill (GX_DRAW_CONTEXT * context, GX_POINT * vertex, INT num)
{
    /* Use D1 heap functions to allocate memory for swapped coordinates */
    GX_POINT * vertex_rotated = d1_allocmem((uint32_t) num * sizeof(GX_POINT));

    GX_POINT * vertex_ptr = vertex_rotated;

    /* Rotate all coordinates */
    for (INT i = 0; i < num; i++)
    {
        if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
        {
            vertex_ptr->gx_point_x = vertex->gx_point_y;
            vertex_ptr->gx_point_y =
                (GX_VALUE) (context->gx_draw_context_canvas->gx_canvas_x_resolution - vertex->gx_point_x - 1);
        }
        else
        {
            vertex_ptr->gx_point_x =
                (GX_VALUE) (context->gx_draw_context_canvas->gx_canvas_y_resolution - vertex->gx_point_y - 1);
            vertex_ptr->gx_point_y = vertex->gx_point_x;
        }

        vertex++;
        vertex_ptr++;
    }

    _gx_dave2d_polygon_fill(context, vertex_rotated, num);

    /* Free temporary swapped coordinate memory */
    d1_freemem(vertex_rotated);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_block_move
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   block[in]           Pointer to a block to be moved
 * @param   xshift[in]          X axis shift
 * @param   yshift[in]          Y axis shift
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_block_move (GX_DRAW_CONTEXT * context, GX_RECTANGLE * block, INT xshift, INT yshift)
{
    GX_RECTANGLE block_rotated;
    gx_dave2d_rectangle_rotate(context, block, &block_rotated);

    if (context->gx_draw_context_display->gx_display_rotation_angle == GX_SCREEN_ROTATION_CW)
    {
        xshift *= -1;
    }
    else
    {
        yshift *= -1;
    }

    _gx_dave2d_block_move(context, &block_rotated, yshift, xshift);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_alphamap_draw
 * @param   context[in]         Pointer to a GUIX draw context
 * @param   xpos[in]            X coordinate
 * @param   ypos[in]            Y coordinate
 * @param   pixelmap[in]        Pointer to pixelmap
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_alphamap_draw (GX_DRAW_CONTEXT * context, INT xpos, INT ypos, GX_PIXELMAP * pixelmap)
{
    gx_dave2d_pixelmap_coordinate_rotate(context, &xpos, &ypos, pixelmap);

    _gx_dave2d_alphamap_draw(context, xpos, ypos, pixelmap);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_compressed_glyph_8bit_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the rectangle to draw in
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_compressed_glyph_8bit_draw (GX_DRAW_CONTEXT * context,
                                                    GX_RECTANGLE    * draw_area,
                                                    GX_POINT        * map_offset,
                                                    const GX_GLYPH  * glyph)
{
    GX_RECTANGLE draw_area_rotated;
    gx_dave2d_rectangle_rotate(context, draw_area, &draw_area_rotated);

    _gx_dave2d_compressed_glyph_8bit_draw(context, &draw_area_rotated, map_offset, glyph);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_raw_glyph_8bit_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the rectangle to draw in
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_raw_glyph_8bit_draw (GX_DRAW_CONTEXT * context,
                                             GX_RECTANGLE    * draw_area,
                                             GX_POINT        * map_offset,
                                             const GX_GLYPH  * glyph)
{
    GX_RECTANGLE draw_area_rotated;
    gx_dave2d_rectangle_rotate(context, draw_area, &draw_area_rotated);

    _gx_dave2d_raw_glyph_8bit_draw(context, &draw_area_rotated, map_offset, glyph);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_compressed_glyph_4bit_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the rectangle to draw in
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_compressed_glyph_4bit_draw (GX_DRAW_CONTEXT * context,
                                                    GX_RECTANGLE    * draw_area,
                                                    GX_POINT        * map_offset,
                                                    const GX_GLYPH  * glyph)
{
    GX_RECTANGLE draw_area_rotated;
    gx_dave2d_rectangle_rotate(context, draw_area, &draw_area_rotated);

    _gx_dave2d_compressed_glyph_4bit_draw(context, &draw_area_rotated, map_offset, glyph);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_raw_glyph_4bit_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the rectangle to draw in
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_raw_glyph_4bit_draw (GX_DRAW_CONTEXT * context,
                                             GX_RECTANGLE    * draw_area,
                                             GX_POINT        * map_offset,
                                             const GX_GLYPH  * glyph)
{
    GX_RECTANGLE draw_area_rotated;
    gx_dave2d_rectangle_rotate(context, draw_area, &draw_area_rotated);

    _gx_dave2d_raw_glyph_4bit_draw(context, &draw_area_rotated, map_offset, glyph);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_compressed_glyph_1bit_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the rectangle to draw in
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_compressed_glyph_1bit_draw (GX_DRAW_CONTEXT * context,
                                                    GX_RECTANGLE    * draw_area,
                                                    GX_POINT        * map_offset,
                                                    const GX_GLYPH  * glyph)
{
    GX_RECTANGLE draw_area_rotated;
    gx_dave2d_rectangle_rotate(context, draw_area, &draw_area_rotated);

    _gx_dave2d_compressed_glyph_1bit_draw(context, &draw_area_rotated, map_offset, glyph);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_raw_glyph_1bit_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   draw_area[in]      Pointer to the rectangle to draw in
 * @param   map_offset[in]     Mapping offset
 * @param   glyph[in]          Pointer to glyph data
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_raw_glyph_1bit_draw (GX_DRAW_CONTEXT * context,
                                             GX_RECTANGLE    * draw_area,
                                             GX_POINT        * map_offset,
                                             const GX_GLYPH  * glyph)
{
    GX_RECTANGLE draw_area_rotated;
    gx_dave2d_rectangle_rotate(context, draw_area, &draw_area_rotated);

    _gx_dave2d_raw_glyph_1bit_draw(context, &draw_area_rotated, map_offset, glyph);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_buffer_toggle
 * @param   canvas[in]         Pointer to a GUIX canvas
 * @param   dirty[in]          Pointer to a dirty rectangle area
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_buffer_toggle (GX_CANVAS * canvas, GX_RECTANGLE * dirty)
{
    _gx_dave2d_buffer_toggle(canvas, dirty);
}

 #if defined(GX_ARC_DRAWING_SUPPORT)

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_aliased_circle_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   r[in]              Radius
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_aliased_circle_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r)
{
    gx_dave2d_coordinate_rotate(context, &xcenter, &ycenter);
    _gx_dave2d_aliased_circle_draw(context, xcenter, ycenter, r);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_circle_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   r[in]              Radius
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_circle_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r)
{
    gx_dave2d_coordinate_rotate(context, &xcenter, &ycenter);
    _gx_dave2d_circle_draw(context, xcenter, ycenter, r);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_circle_fill
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   r[in]              Radius
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_circle_fill (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, UINT r)
{
    gx_dave2d_coordinate_rotate(context, &xcenter, &ycenter);
    _gx_dave2d_circle_fill(context, xcenter, ycenter, r);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_pie_fill
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   r[in]              Radius
 * @param   start_angle[in]    Start angle (degrees)
 * @param   end_angle[in]      End angle (degrees)
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_pie_fill (GX_DRAW_CONTEXT * context,
                                  INT               xcenter,
                                  INT               ycenter,
                                  UINT              r,
                                  INT               start_angle,
                                  INT               end_angle)
{
    gx_dave2d_coordinate_rotate(context, &xcenter, &ycenter);

    INT screen_angle = context->gx_draw_context_display->gx_display_rotation_angle;
    _gx_dave2d_pie_fill(context, xcenter, ycenter, r, start_angle + screen_angle, end_angle + screen_angle);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_aliased_arc_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   r[in]              Radius
 * @param   start_angle[in]    Start angle (degrees)
 * @param   end_angle[in]      End angle (degrees)
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_aliased_arc_draw (GX_DRAW_CONTEXT * context,
                                          INT               xcenter,
                                          INT               ycenter,
                                          UINT              r,
                                          INT               start_angle,
                                          INT               end_angle)
{
    gx_dave2d_coordinate_rotate(context, &xcenter, &ycenter);

    INT screen_angle = context->gx_draw_context_display->gx_display_rotation_angle;
    _gx_dave2d_aliased_arc_draw(context, xcenter, ycenter, r, start_angle + screen_angle, end_angle + screen_angle);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_arc_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   r[in]              Radius
 * @param   start_angle[in]    Start angle (degrees)
 * @param   end_angle[in]      End angle (degrees)
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_arc_draw (GX_DRAW_CONTEXT * context,
                                  INT               xcenter,
                                  INT               ycenter,
                                  UINT              r,
                                  INT               start_angle,
                                  INT               end_angle)
{
    gx_dave2d_coordinate_rotate(context, &xcenter, &ycenter);

    INT screen_angle = context->gx_draw_context_display->gx_display_rotation_angle;
    _gx_dave2d_arc_draw(context, xcenter, ycenter, r, start_angle + screen_angle, end_angle + screen_angle);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_arc_fill
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   r[in]              Radius
 * @param   start_angle[in]    Start angle (degrees)
 * @param   end_angle[in]      End angle (degrees)
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_arc_fill (GX_DRAW_CONTEXT * context,
                                  INT               xcenter,
                                  INT               ycenter,
                                  UINT              r,
                                  INT               start_angle,
                                  INT               end_angle)
{
    gx_display_list_flush(context->gx_draw_context_display);
    gx_display_list_open(context->gx_draw_context_display);

    /** Call the GUIX generic arc fill routine. */
    _gx_display_driver_generic_rotated_arc_fill(context, xcenter, ycenter, r, start_angle, end_angle);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_aliased_ellipse_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   a[in]              Semi-major axis
 * @param   b[in]              Semi-minor axis
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_aliased_ellipse_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    if (context->gx_draw_context_brush.gx_brush_width > 1)
    {
        /** Call the GUIX generic anti-aliased ellipse draw routine. */
        _gx_display_driver_generic_aliased_wide_ellipse_draw(context, xcenter, ycenter, a, b);
    }
    else
    {
        /** Call the GUIX generic anti-aliased ellipse draw routine. */
        _gx_display_driver_generic_aliased_ellipse_draw(context, xcenter, ycenter, a, b);
    }

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_ellipse_draw
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   a[in]              Semi-major axis
 * @param   b[in]              Semi-minor axis
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_ellipse_draw (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b)
{
    /** Flush D/AVE 2D display list first to insure order of operation. */
    gx_display_list_flush(context->gx_draw_context_display);

    if (context->gx_draw_context_brush.gx_brush_width > 1)
    {
        /** Call the GUIX generic aliased ellipse draw routine. */
        _gx_display_driver_generic_wide_ellipse_draw(context, xcenter, ycenter, a, b);
    }
    else
    {
        /** Call the GUIX generic aliased ellipse draw routine. */
        _gx_display_driver_generic_ellipse_draw(context, xcenter, ycenter, a, b);
    }

    /** Open next display list before we go. */
    gx_display_list_open(context->gx_draw_context_display);
}

/*******************************************************************************************************************//**
 * @brief  CW/CCW rotation shim for _gx_dave2d_ellipse_fill
 * @param   context[in]        Pointer to a GUIX draw context
 * @param   xcenter[in]        Center X coordinate
 * @param   ycenter[in]        Center Y coordinate
 * @param   a[in]              Semi-major axis
 * @param   b[in]              Semi-minor axis
 **********************************************************************************************************************/
VOID _gx_dave2d_rotated_ellipse_fill (GX_DRAW_CONTEXT * context, INT xcenter, INT ycenter, INT a, INT b)
{
    gx_display_list_flush(context->gx_draw_context_display);
    gx_display_list_open(context->gx_draw_context_display);

    /** Call the GUIX generic ellipse fill routine. */
    _gx_display_driver_generic_rotated_ellipse_fill(context, xcenter, ycenter, a, b);
}

 #endif

#endif
