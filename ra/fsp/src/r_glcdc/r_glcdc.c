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
#include <string.h>

#include "bsp_api.h"

#include "r_glcdc.h"
#include "r_glcdc_cfg.h"

#if defined(GLCDC_CFG_USING_DSI)
 #include "r_mipi_dsi_api.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* The macro to use for 64-byte alignment checking, calculation */
#define GLCDC_PRV_ADDRESS_ALIGNMENT_64B                (64U)

/* This enables the GLCDC to locate the foreground/background layer image, at the physical start of the left side of
 * the display, if the offset of layer start position is a negative value, compared to the active video area.
 *  Shifting the base address of the layer image can be used in this operation, but it must be aligned to 64 byte
 * boundary, so that the layer position adjustment can be made.
 */
#define GLCDC_PRV_OFFSET_MARGIN_MINUS_64PIX            (64U)

#define GLCDC_PRV_OUT_CLKPHASE_ALL_RISING              (0x00000000)
#define GLCDC_PRV_OUT_CLKPHASE_ALL_FALLING             (0x00000178)

/* Color look up table entry size */
#define GLCDC_PRV_CLUT_ENTRY_SIZE                      (256U)

/* Panel timing, Maximum threshold */
#define GLCDC_PRV_BG_PLANE_H_CYC_MAX                   (2047U)         ///< BG_PERI.FH
#define GLCDC_PRV_BG_PLANE_V_CYC_MAX                   (2047U)         ///< BG_PERI.FV
#define GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_SIZE_MAX       (2039U)         ///< BG_HSIZE.HW (Max=2039)
#define GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_SIZE_MAX       (2043U)         ///< BG_VSIZE.VW (Max=2043)
#define GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_POS_MAX        (2029U)         ///< BG_HSIZE.HP (Max=2029, note that this value is 1cycle larger than GRn_AB3.GRCHS)
#define GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_POS_MAX        (2030U)         ///< BG_VSIZE.VP (Max=2030, note that this value is 1cycle larger than GRn_AB3.GRCVS)
#define GLCDC_PRV_GR_PLANE_TOTAL_TRANSFER_TIMES_MAX    (65536U)        ///< GRn_FLM5.DATANUM (Max=65536)
#define GLCDC_PRV_GR_PLANE_V_CYC_ACTIVE_SIZE_MAX       (2043U)         ///< GRn_AB2.GRCVW (Max=2043) ; Image Area, GRn_AB4.ARCVW (Max=2043); Rectangular Area
#define GLCDC_PRV_GR_PLANE_H_CYC_ACTIVE_POS_MAX        (2028U)         ///< GRn_AB3.GRCHS (Max=2028) ; Image Area, GRn_AB5.ARCHS (Max=2028); Rectangular Area
#define GLCDC_PRV_GR_PLANE_V_CYC_ACTIVE_POS_MAX        (2029U)         ///< GRn_AB2.GRCVS (Max=2029) ; Image Area, GRn_AB4.ARCVS (Max=2029); Rectangular Area
#define GLCDC_PRV_TCON_SIGNAL_ASSERT_WIDTH_MAX         (2046U)

/* Panel timing, Minimum threshold */
#define GLCDC_PRV_BG_PLANE_H_CYC_MIN                   ((uint16_t) 23) ///< BG_PERI.FH
#define GLCDC_PRV_BG_PLANE_V_CYC_MIN                   ((uint16_t) 19) ///< BG_PERI.FV
#define GLCDC_PRV_BG_PLANE_HSYNC_POS_MIN               ((uint16_t) 1)  ///< BG_HSYNC.HP (Min=1)
#define GLCDC_PRV_BG_PLANE_VSYNC_POS_MIN               ((uint16_t) 1)  ///< BG_HSYNC.VP (Min=1)
#define GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_SIZE_MIN       ((uint16_t) 16) ///< BG_HSIZE.HW (Min=16)
#define GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_SIZE_MIN       ((uint16_t) 16) ///< BG_VSIZE.VW (Min=16)
#define GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_POS_MIN        ((uint16_t) 6)  ///< BG_HSIZE.HP (Min= 6)
#define GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_POS_MIN        ((uint16_t) 3)  ///< BG_VSIZE.VP (Min= 3)

/* This driver sets same value to GRn_AB2.GRCVW and GRn_AB4.ARCVW, so the value of this macro
 * is defined as the number of GRn_AB2.GRCVW(larger value).
 */
#define GLCDC_PRV_GR_PLANE_H_CYC_ACTIVE_POS_MIN        (5U)            ///< GRn_AB3.GRCHS (Min= 5) ; Image Area, GRn_AB5.ARCHS (Min= 5); Rectangular Area
#define GLCDC_PRV_GR_PLANE_V_CYC_ACTIVE_POS_MIN        (2U)            ///< GRn_AB2.GRCVS (Min= 2) ; Image Area, GRn_AB4.ARCVS (Min= 2); Rectangular Area
#define GLCDC_PRV_TCON_SIGNAL_ASSERT_WIDTH_MIN         (0U)

/* Color correction setting threshold */
#define GLCDC_PRV_BRIGHTNESS_DEFAULT                   (512U)          ///< OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Mid=512)
#define GLCDC_PRV_BRIGHTNESS_MIN                       (0U)            ///< OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Min=0)
#define GLCDC_PRV_BRIGHTNESS_MAX                       (1023U)         ///< OUT_BRIGHT1.BRTG, OUT_BRIGHT2.BRTR and .BRTB (Max=1023)
#define GLCDC_PRV_CONTRAST_DEFAULT                     (128U)          ///< OUT_CONTRAST.CONTG and .CONTB and .CONTR (Mid=128)
#define GLCDC_PRV_CONTRAST_MIN                         (0U)            ///< OUT_CONTRAST.CONTG and .CONTB and .CONTR (Min=0)
#define GLCDC_PRV_CONTRAST_MAX                         (255U)          ///< OUT_CONTRAST.CONTG and .CONTB and .CONTR (Max=255)
#define GLCDC_PRV_GAMMA_GAIN_MAX                       (2047U)         ///< GAMx_LUTn.GAIN15 - GAIN0 (Max=2047)
#define GLCDC_PRV_GAMMA_THRESHOLD_MAX                  (1023U)         ///< GAMx_AREAn.TH15  - TH0   (Max=1023)

/* Registers for Background Frame Control Block */
#define GLCDC_PRV_BG_PERI_FV_MASK                      (0x7FFU)
#define GLCDC_PRV_BG_PERI_FH_MASK                      (0x7FFU)
#define GLCDC_PRV_BG_SYNC_VP_MASK                      (0xFU)
#define GLCDC_PRV_BG_SYNC_HP_MASK                      (0xFU)
#define GLCDC_PRV_BG_VSIZE_VP_MASK                     (0x7FFU)
#define GLCDC_PRV_BG_VSIZE_VW_MASK                     (0x7FFU)
#define GLCDC_PRV_BG_HSIZE_HP_MASK                     (0x7FFU)
#define GLCDC_PRV_BG_HSIZE_HW_MASK                     (0x7FFU)

/* Register bit definition for Graphics Frame Control Block */
#define GLCDC_PRV_GR_FLM3_LNOFF_MASK                   (0xFFFFU)
#define GLCDC_PRV_GR_FLM3_FLNUM_MASK                   (0x3FFU)
#define GLCDC_PRV_GR_FLM4_FLOFF_MASK                   (0xFFFFFFU)
#define GLCDC_PRV_GR_FLM5_LNNUM_MASK                   (0x7FFU)
#define GLCDC_PRV_GR_FLM5_DATANUM_MASK                 (0xFFFFU)
#define GLCDC_PRV_GR_FLM6_FORMAT_MASK                  (0x7U)

#define GLCDC_PRV_GR_AB1_DISPSEL_MASK                  (0x3U)
#define GLCDC_PRV_GR_AB1_ARCON_SET                     (1 << 12)
#define GLCDC_PRV_GR_AB2_GRCVS_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB2_GRCVW_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB3_GRCHS_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB3_GRCHW_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB4_ARCVS_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB4_ARCVW_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB5_ARCHS_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB5_ARCHW_MASK                    (0x7FFU)
#define GLCDC_PRV_GR_AB6_ARCCOEF_MASK                  (0x1FFU)
#define GLCDC_PRV_GR_AB6_ARCRATE_MASK                  (0xFFU)
#define GLCDC_PRV_GR_AB7_ARCDEF_MASK                   (0xFFU)
#define GLCDC_PRV_GR_CLUTINT_LINE_MASK                 (0x7FFU)

/* Register bit definition for Output Control Block */
#define GLCDC_PRV_GAMX_LUTX_GAIN_MASK                  (0x7FFU)
#define GLCDC_PRV_GAMX_AREAX_MASK                      (0x3FFU)

#define GLCDC_PRV_OUT_SET_FRQSEL_NO_DIVISION           (0U)
#define GLCDC_PRV_OUT_SET_FRQSEL_QUARTER_DIVISION      (2U)
#define GLCDC_PRV_OUT_SET_FORMAT_SHIFT                 (12U)
#define GLCDC_PRV_OUT_SET_ENDIANON_ENABLE              (1 << 28)
#define GLCDC_PRV_OUT_SET_SWAPON_ENABLE                (1 << 24)

#define GLCDC_PRV_OUT_PDTHA_SEL_SHIFT                  (20U)
#define GLCDC_PRV_OUT_PDTHA_FORM_SHIFT                 (16U)
#define GLCDC_PRV_OUT_PDTHA_PA_SHIFT                   (12U)
#define GLCDC_PRV_OUT_PDTHA_PB_SHIFT                   (8U)
#define GLCDC_PRV_OUT_PDTHA_PC_SHIFT                   (4U)

#define GLCDC_PRV_OUT_BRIGHT1_BRTG_MASK                (0x3FFU)
#define GLCDC_PRV_OUT_BRIGHT2_BRTB_MASK                (0x3FFU)
#define GLCDC_PRV_OUT_BRIGHT2_BRTR_MASK                (0x3FFU)

#define GLCDC_PRV_OUT_CONTRAST_CONTG_MASK              (0xFFU)
#define GLCDC_PRV_OUT_CONTRAST_CONTB_MASK              (0xFFU)
#define GLCDC_PRV_OUT_CONTRAST_CONTR_MASK              (0xFFU)

#define GLCDC_PRV_TCON_STHX1_HS_MASK                   (0x7FFU)
#define GLCDC_PRV_TCON_STHX1_HW_MASK                   (0x7FFU)
#define GLCDC_PRV_TCON_STVX1_VS_MASK                   (0x7FFU)
#define GLCDC_PRV_TCON_STVX1_VW_MASK                   (0x7FFU)
#define GLCDC_PRV_TCON_STXX2_INV_SET                   (1 << 4)

#define GLCDC_PRV_SYSCNT_PANEL_CLK_PIXSEL_SERIALRGB    (1 << 12)
#define GLCDC_PRV_SYSCNT_PANEL_CLK_CLKSEL_PLL          (1 << 8)
#define GLCDC_PRV_SYSCNT_PANEL_CLK_CLKEN_ENABLE        (1 << 6)
#define GLCDC_PRV_SYSCNT_PANEL_CLK_DCDR_MASK           (0x3FU)

#define GLCDC_PRV_SYSCNT_DTCTEN_INIT                   (6U)
#define GLCDC_PRV_SYSCNT_INTEN_INIT                    (7U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* RGB color order select */
typedef enum e_glcdc_plane_blend
{
    GLCDC_PLANE_BLEND_TRANSPARENT     = 1, ///< Current graphics layer is transparent and the lower layer is displayed
    GLCDC_PLANE_BLEND_NON_TRANSPARENT = 2, ///< Current graphics layer is displayed
    GLCDC_PLANE_BLEND_ON_LOWER_LAYER  = 3  ///< Current graphics layer is blended with the lower layer
} glcdc_plane_blend_t;

/* RGB color order select */
typedef enum e_glcdc_fading_control_initial_alpha
{
    GLCDC_FADING_CONTROL_INITIAL_ALPHA_MIN = 0,   ///< Initial alpha value setting for a graphics plane is zero
    GLCDC_FADING_CONTROL_INITIAL_ALPHA_MAX = 0xff ///< Initial alpha value setting for a graphics plane is maximum
} glcdc_fading_control_initial_alpha_t;

/* The structure for the layer parameter recalculation */
typedef struct st_recalculated_param
{
    uint16_t hpix_size;
    uint16_t vpix_size;
    int16_t  hpix_offset;              /* Offset can be signed value */
    int16_t  vpix_offset;
    uint32_t hread_size;
    uint32_t base_address;
} glcdc_recalculated_param_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_stop(glcdc_instance_ctrl_t * const p_ctrl);
static void      r_glcdc_sync_signal_set(display_cfg_t const * const p_cfg);

static void r_glcdc_background_screen_set(display_cfg_t const * const p_cfg);

static void r_glcdc_graphics_layer_set(display_input_cfg_t const * const p_input,
                                       display_layer_t const * const     p_layer,
                                       display_frame_layer_t const       layer);

static void r_glcdc_output_block_set(display_cfg_t const * const p_cfg);

static void r_glcdc_hsync_set(glcdc_tcon_pin_t tcon, display_timing_t const * timing);

static void r_glcdc_vsync_set(glcdc_tcon_pin_t tcon, display_timing_t const * const timing);

static void r_glcdc_data_enable_set(glcdc_tcon_pin_t const          tcon,
                                    display_timing_t const * const  vtiming,
                                    display_timing_t const * const  htiming,
                                    display_signal_polarity_t const polarity);

static void r_glcdc_clock_set(display_cfg_t const * const p_cfg);

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_glcdc_open_param_check(display_cfg_t const * const p_cfg);

 #if GLCDC_CFG_COLOR_CORRECTION_ENABLE

static fsp_err_t r_glcdc_param_check_brightness(display_brightness_t const * const p_brightness);

 #endif

#endif

static inline uint16_t r_glcdc_get_bit_size(display_in_format_t const format);

static void r_glcdc_interrupt_enable(glcdc_instance_ctrl_t * p_instance_ctrl);

static void r_glcdc_pixel_size_recalculate(display_input_cfg_t const * const p_input,
                                           display_layer_t const * const     p_layer,
                                           glcdc_recalculated_param_t      * p_recalculated,
                                           uint16_t                          bit_size);

#if GLCDC_CFG_COLOR_CORRECTION_ENABLE

static void r_glcdc_brightness_correction(glcdc_instance_ctrl_t const * const p_ctrl,
                                          display_brightness_t const * const  p_brightness);

static void r_glcdc_contrast_correction(glcdc_instance_ctrl_t const * const p_ctrl,
                                        display_contrast_t const * const    p_contrast);

static void r_glcdc_color_correction_order(display_cfg_t const * const p_cfg);

static void r_glcdc_gamma_correction(display_cfg_t const * const p_cfg);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* GLCDC HAL module API function pointer list */
const display_api_t g_display_on_glcdc =
{
    .open         = R_GLCDC_Open,
    .close        = R_GLCDC_Close,
    .start        = R_GLCDC_Start,
    .stop         = R_GLCDC_Stop,
    .layerChange  = R_GLCDC_LayerChange,
    .bufferChange = R_GLCDC_BufferChange,
    .clut         = R_GLCDC_ClutUpdate,
    .clutEdit     = R_GLCDC_ClutEdit,
    .correction   = R_GLCDC_ColorCorrection,
    .colorKeySet  = R_GLCDC_ColorKeySet,
    .statusGet    = R_GLCDC_StatusGet,
};

/* GLCDC control block */
static glcdc_ctrl_t g_ctrl_blk =
{
    .back_porch = {0U, 0U},
    .hsize      = 0U,
    .vsize      = 0U,
    .p_context  = NULL
};

void glcdc_line_detect_isr(void);
void glcdc_underflow_1_isr(void);
void glcdc_underflow_2_isr(void);

/* Needed to track fade status */
static uint32_t          g_fade_pending[2] = {false, false};
static volatile uint32_t g_frame_ctr       = 0;

/* Tracks when an edited CLUT has been latched in */
static volatile bool g_clut_data_latched[2] = {true, true};

/* Look-up table for r_glcdc_tcon_set */
static uint32_t volatile * g_tcon_lut[] =
{
    &(R_GLCDC->TCON.STVA2), &(R_GLCDC->TCON.STVB2), &(R_GLCDC->TCON.STHA2), &(R_GLCDC->TCON.STHB2),
};

/* Look-up table for converting display_in_format_t to glcdc_input_interface_format_t */
static glcdc_input_interface_format_t g_format_lut[] =
{
    GLCDC_INPUT_INTERFACE_FORMAT_ARGB8888,
    GLCDC_INPUT_INTERFACE_FORMAT_RGB888,
    GLCDC_INPUT_INTERFACE_FORMAT_RGB565,
    GLCDC_INPUT_INTERFACE_FORMAT_ARGB1555,
    GLCDC_INPUT_INTERFACE_FORMAT_ARGB4444,
    GLCDC_INPUT_INTERFACE_FORMAT_CLUT8,
    GLCDC_INPUT_INTERFACE_FORMAT_CLUT4,
    GLCDC_INPUT_INTERFACE_FORMAT_CLUT1
};

/* Look-up table for r_glcdc_get_bit_size */
static uint16_t g_pixsize_lut[] = {32, 32, 16, 16, 16, 8, 4, 1}; // NOLINT(readability-magic-numbers)

/* Look-up tables for use in r_glcdc_output_block_set */
static glcdc_output_interface_format_t g_outset_lut[] =
{
    GLCDC_OUTPUT_INTERFACE_FORMAT_RGB888,
    GLCDC_OUTPUT_INTERFACE_FORMAT_RGB666,
    GLCDC_OUTPUT_INTERFACE_FORMAT_RGB565,
    GLCDC_OUTPUT_INTERFACE_FORMAT_SERIAL_RGB
};
static glcdc_dithering_output_format_t g_pdtha_lut[] =
{
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB888,
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB666,
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB565,
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB888
};

/*******************************************************************************************************************//**
 * @addtogroup GLCDC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open GLCDC module. Implements @ref display_api_t::open.
 *
 * @retval  FSP_SUCCESS                        Device was opened successfully.
 * @retval  FSP_ERR_ALREADY_OPEN               Device was already open.
 * @retval  FSP_ERR_ASSERTION                  Pointer to the control block or the configuration structure is NULL.
 * @retval  FSP_ERR_CLOCK_GENERATION           Dot clock cannot be generated from clock source.
 * @retval  FSP_ERR_INVALID_TIMING_SETTING     Invalid panel timing parameter.
 * @retval  FSP_ERR_INVALID_LAYER_SETTING      Invalid layer setting found.
 * @retval  FSP_ERR_INVALID_ALIGNMENT          Input buffer alignment invalid.
 * @retval  FSP_ERR_INVALID_GAMMA_SETTING      Invalid gamma correction setting found
 * @retval  FSP_ERR_INVALID_BRIGHTNESS_SETTING Invalid brightness correction setting found
 * @note    PCLKA  must be supplied to Graphics LCD Controller (GLCDC) and  GLCDC pins must be set in IOPORT before
 *           calling this API.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_Open (display_ctrl_t * const p_api_ctrl, display_cfg_t const * const p_cfg)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters */
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->state <= DISPLAY_STATE_CLOSED, FSP_ERR_ALREADY_OPEN);
    err = r_glcdc_open_param_check(p_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }
#endif

    p_ctrl->state = DISPLAY_STATE_CLOSED;

    /* Supply the peripheral clock to the GLCDC module */
    R_BSP_MODULE_START(FSP_IP_GLCDC, 0);

    /* Release GLCDC from a SW reset status. */
    R_GLCDC->BG.EN_b.SWRST = 1U;

    /* Set the dot clock frequency */
    r_glcdc_clock_set(p_cfg);

    /* Set the panel signal timing */
    r_glcdc_sync_signal_set(p_cfg);

    /* Configure the background screen */
    r_glcdc_background_screen_set(p_cfg);

    /* Store back porch position to the control block (needed to define the layer blending position later) */
    g_ctrl_blk.back_porch.x = (int16_t) (p_cfg->output.htiming.back_porch);
    g_ctrl_blk.back_porch.y = (int16_t) (p_cfg->output.vtiming.back_porch);
    g_ctrl_blk.hsize        = p_cfg->output.htiming.display_cyc;
    g_ctrl_blk.vsize        = p_cfg->output.vtiming.display_cyc;

    /* Configure the graphics plane layers */
    for (uint32_t layer = 0U; layer <= DISPLAY_FRAME_LAYER_2; layer++)
    {
        r_glcdc_graphics_layer_set(&(p_cfg->input[layer]), &(p_cfg->layer[layer]), (display_frame_layer_t) layer);
    }

    /* Configure the output control block */
    r_glcdc_output_block_set(p_cfg);

#if GLCDC_CFG_COLOR_CORRECTION_ENABLE

    /* Configure the color correction setting (brightness, brightness and gamma correction) */
    r_glcdc_brightness_correction(p_ctrl, &p_cfg->output.brightness);
    r_glcdc_contrast_correction(p_ctrl, &p_cfg->output.contrast);
    if (p_cfg->output.p_gamma_correction)
    {
        r_glcdc_gamma_correction(p_cfg);
    }

    /* Set the color correction order (brightness/contrast or gamma first) */
    r_glcdc_color_correction_order(p_cfg);
#else

    /* Set default brightness and contrast */
    R_GLCDC->OUT.BRIGHT1 = GLCDC_PRV_BRIGHTNESS_DEFAULT & GLCDC_PRV_OUT_BRIGHT1_BRTG_MASK;
    R_GLCDC->OUT.BRIGHT2 = ((GLCDC_PRV_BRIGHTNESS_DEFAULT & GLCDC_PRV_OUT_BRIGHT2_BRTB_MASK) << 16) +
                           (GLCDC_PRV_BRIGHTNESS_DEFAULT & GLCDC_PRV_OUT_BRIGHT2_BRTR_MASK);
    R_GLCDC->OUT.CONTRAST = ((GLCDC_PRV_CONTRAST_DEFAULT & GLCDC_PRV_OUT_CONTRAST_CONTG_MASK) << 16) +
                            ((GLCDC_PRV_CONTRAST_DEFAULT & GLCDC_PRV_OUT_CONTRAST_CONTB_MASK) << 8) +
                            (GLCDC_PRV_CONTRAST_DEFAULT & GLCDC_PRV_OUT_CONTRAST_CONTR_MASK);
#endif

    p_ctrl->p_callback   = p_cfg->p_callback; /// Save callback function
    p_ctrl->p_context    = p_cfg->p_context;  /// Save user defined context
    p_ctrl->p_cfg        = p_cfg;             /// Save user configuration
    g_ctrl_blk.p_context = p_ctrl;            /// Save the display interface context into GLCDC HAL control block

    /* Set the line number to trigger the line detect interrupt */
    R_GLCDC->GR[1].CLUTINT_b.LINE = (uint16_t) (p_cfg->output.vtiming.back_porch +
                                                p_cfg->output.vtiming.display_cyc +
                                                GLCDC_PRV_BG_PLANE_HSYNC_POS_MIN) & GLCDC_PRV_GR_CLUTINT_LINE_MASK;

#if defined(GLCDC_CFG_USING_DSI)

    /* DSI must be opened after GLCDC configuration. See RA8 UM R01UH0995EJ0050 Section 56.3.1 */
    glcdc_extended_cfg_t * p_extend     = (glcdc_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    mipi_dsi_instance_t  * dsi_instance = (mipi_dsi_instance_t *) p_extend->phy_layer;
    err = dsi_instance->p_api->open(dsi_instance->p_ctrl, dsi_instance->p_cfg);
#endif

    if (FSP_SUCCESS == err)
    {
        /* Enable GLCDC interrupts */
        r_glcdc_interrupt_enable(p_api_ctrl);
        p_ctrl->state = DISPLAY_STATE_OPENED; /// Change GLCDC driver state
    }
    else
    {
        R_BSP_MODULE_STOP(FSP_IP_GLCDC, 0);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Close GLCDC module. Implements @ref display_api_t::close.
 *
 * @retval  FSP_SUCCESS                     Device was closed successfully.
 * @retval  FSP_ERR_ASSERTION               Pointer to the control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                The function call is performed when the driver state is not equal to
 *                                           DISPLAY_STATE_CLOSED.
 * @retval  FSP_ERR_INVALID_UPDATE_TIMING   A function call is performed when the GLCDC is updating register values
 *                                           internally.
 * @note    This API can be called when the driver is not in DISPLAY_STATE_CLOSED state. It returns an error
 *           if the register update operation for the background screen generation block is being held.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_Close (display_ctrl_t * const p_api_ctrl)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(DISPLAY_STATE_CLOSED != p_ctrl->state, FSP_ERR_NOT_OPEN);
#endif

    /* Stop video if running */
    if (R_GLCDC->BG.EN_b.EN)
    {
        r_glcdc_stop(p_api_ctrl);
    }

#if defined(GLCDC_CFG_USING_DSI)

    /* DSI must be closed before GLCDC. See RA8 UM R01UH0995EJ0050 Section 56.3.7.2 */
    glcdc_extended_cfg_t * p_extend     = (glcdc_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    mipi_dsi_instance_t  * dsi_instance = (mipi_dsi_instance_t *) p_extend->phy_layer;
    err = dsi_instance->p_api->close(dsi_instance->p_ctrl);
#endif

    /* Return immediately if the background block register updating is performed. */
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->BG.MON_b.VEN & 1U), FSP_ERR_INVALID_UPDATE_TIMING);

    /* Disable the GLCDC interrupts in the NVIC */
    if (p_ctrl->p_cfg->line_detect_irq >= 0)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->line_detect_irq);
    }

    if (p_ctrl->p_cfg->underflow_1_irq >= 0)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->underflow_1_irq);
    }

    if (p_ctrl->p_cfg->underflow_2_irq >= 0)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->underflow_2_irq);
    }

    /* Disable the GLCDC interrupts */
    R_GLCDC->SYSCNT.DTCTEN = 0U;
    R_GLCDC->SYSCNT.INTEN  = 0U;

    /* Disable background plane operation */
    R_GLCDC->BG.EN_b.EN = 0U;

    /* Reset the GLCDC hardware */
    R_GLCDC->BG.EN_b.SWRST = 0U;

    /* Halt the peripheral clock to the GLCDC module */
    R_BSP_MODULE_STOP(FSP_IP_GLCDC, 0);

    p_ctrl->state = DISPLAY_STATE_CLOSED;

    return err;
}

/*******************************************************************************************************************//**
 * Start GLCDC module. Implements @ref display_api_t::start.
 *
 * @retval  FSP_SUCCESS                  Device was started successfully.
 * @retval  FSP_ERR_NOT_OPEN             GLCDC module has not been opened.
 * @retval  FSP_ERR_ASSERTION            Pointer to the control block is NULL.
 * @note    This API can be called when the driver is not in DISPLAY_STATE_OPENED status.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_Start (display_ctrl_t * const p_api_ctrl)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(DISPLAY_STATE_OPENED == p_ctrl->state, FSP_ERR_NOT_OPEN);
#endif

#if defined(GLCDC_CFG_USING_DSI)

    /* DSI must be started before GLCDC. See RA8 UM R01UH0995EJ0050 Section 56.3.7.1 */
    glcdc_extended_cfg_t * p_extend     = (glcdc_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    mipi_dsi_instance_t  * dsi_instance = (mipi_dsi_instance_t *) p_extend->phy_layer;
    err = dsi_instance->p_api->start(dsi_instance->p_ctrl);
#endif

    /* Start to output the vertical and horizontal synchronization signals and screen data. */

    /* enables background plane operation and internal register value reflection. */
    R_GLCDC->BG.EN_b.VEN = 1U;
    R_GLCDC->BG.EN_b.EN  = 1U;

    /* Enable Line detect function    */
    R_GLCDC->SYSCNT.DTCTEN_b.VPOSDTC = 1U;

    p_ctrl->state = DISPLAY_STATE_DISPLAYING;

    return err;
}

/*******************************************************************************************************************//**
 * Stop GLCDC module. Implements @ref display_api_t::stop.
 *
 * @retval  FSP_SUCCESS                   Device was stopped successfully
 * @retval  FSP_ERR_ASSERTION             Pointer to the control block is NULL
 * @retval  FSP_ERR_INVALID_MODE          Function call is performed when the driver state is not
 *                                        DISPLAY_STATE_DISPLAYING.
 * @retval  FSP_ERR_INVALID_UPDATE_TIMING The function call is performed while the GLCDC is updating register values
 *                                          internally.
 * @note    This API can be called when the driver is in the DISPLAY_STATE_DISPLAYING state. It returns an
 *          error if the register update operation for the background screen generation blocks, the graphics data I/F
 *          blocks, or the output control block is being held.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_Stop (display_ctrl_t * const p_api_ctrl)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN((DISPLAY_STATE_DISPLAYING == p_ctrl->state), FSP_ERR_INVALID_MODE);
#endif

    return r_glcdc_stop(p_ctrl);
}

/*******************************************************************************************************************//**
 * Change layer parameters of GLCDC module at runtime. Implements display_api_t::layerChange.
 *
 * @retval  FSP_SUCCESS                      Changed layer parameters of GLCDC module successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block or the configuration structure is NULL.
 * @retval  FSP_ERR_INVALID_MODE             A function call is performed when the driver state is not
 *                                            DISPLAY_STATE_DISPLAYING.
 * @retval  FSP_ERR_INVALID_UPDATE_TIMING    A function call is performed while the GLCDC is updating register values
 *                                            internally.
 * @note    This API can be called when the driver is in DISPLAY_STATE_DISPLAYING state. It returns an error if
 *           the register update operation for the background screen generation blocks or the graphics data I/F block
 *           is being held.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_LayerChange (display_ctrl_t const * const        p_api_ctrl,
                               display_runtime_cfg_t const * const p_cfg,
                               display_frame_layer_t               layer)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ERROR_RETURN((DISPLAY_STATE_DISPLAYING == p_ctrl->state), FSP_ERR_INVALID_MODE);
#endif

    /* Return immediately if the register updating is in progress */
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->GR[layer].VEN_b.PVEN), FSP_ERR_INVALID_UPDATE_TIMING);
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->BG.EN_b.VEN), FSP_ERR_INVALID_UPDATE_TIMING);

    /* Configure the graphics plane layers */
    r_glcdc_graphics_layer_set(&p_cfg->input, &p_cfg->layer, layer);

    /* Reflect the graphics module register value to the GLCDC internal operations (at the timing of the next Vsync
     * assertion) */
    R_GLCDC->GR[layer].VEN_b.PVEN = 1U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Change the framebuffer pointer for a layer. Implements @ref display_api_t::bufferChange.
 *
 * @retval  FSP_SUCCESS                      Changed layer parameters of GLCDC module successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block is NULL.
 * @retval  FSP_ERR_INVALID_MODE             A function call is performed when the driver state is not
 *                                            DISPLAY_STATE_DISPLAYING.
 * @retval  FSP_ERR_INVALID_ALIGNMENT        The framebuffer pointer is not 64-byte aligned.
 * @retval  FSP_ERR_INVALID_UPDATE_TIMING    A function call is performed while the GLCDC is updating register values
 *                                            internally.
 * @note    This API can be called when the driver is in DISPLAY_STATE_OPENED state or higher. It returns an error if
 *           the register update operation for the background screen generation blocks or the graphics data I/F block
 *           is being held.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_BufferChange (display_ctrl_t const * const p_api_ctrl,
                                uint8_t * const              framebuffer,
                                display_frame_layer_t        layer)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN((DISPLAY_STATE_DISPLAYING == p_ctrl->state), FSP_ERR_INVALID_MODE);

    /* Buffer address must be aligned to 64-byte boundary */
    FSP_ERROR_RETURN(0U == (((uint32_t) framebuffer) % GLCDC_PRV_ADDRESS_ALIGNMENT_64B), FSP_ERR_INVALID_ALIGNMENT);
#endif

    /* Return immediately if the register updating is in progress */
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->GR[layer].VEN_b.PVEN), FSP_ERR_INVALID_UPDATE_TIMING);
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->BG.EN_b.VEN), FSP_ERR_INVALID_UPDATE_TIMING);

    uint32_t dispsel;
    uint32_t flmrd;

    /* If the base address is NULL set the layer as transparent and disable read memory access */
    if (framebuffer == NULL)
    {
        dispsel = GLCDC_PLANE_BLEND_TRANSPARENT;
        flmrd   = 0U;
    }
    else
    {
        dispsel = GLCDC_PLANE_BLEND_ON_LOWER_LAYER;
        flmrd   = 1U;
    }

    /* Enable or disable the layer */
    R_GLCDC->GR[layer].AB1_b.DISPSEL = dispsel & GLCDC_PRV_GR_AB1_DISPSEL_MASK; /* Set layer transparent */
    R_GLCDC->GR[layer].FLMRD         = flmrd;

    /* Set the buffer address */
    R_GLCDC->GR[layer].FLM2 = (uint32_t) framebuffer;

    /* Reflect the shadow registers on the next Vsync */
    R_GLCDC->GR[layer].VEN_b.PVEN = 1U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Perform color correction through the GLCDC module. Implements display_api_t::correction.
 *
 * @retval  FSP_SUCCESS                        Color correction by GLCDC module was performed successfully.
 * @retval  FSP_ERR_ASSERTION                  Pointer to the control block or the display correction structure is NULL.
 * @retval  FSP_ERR_INVALID_MODE               Function call is performed when the driver state is not
 *                                              DISPLAY_STATE_DISPLAYING.
 * @retval  FSP_ERR_INVALID_UPDATE_TIMING      A function call is performed while the GLCDC is updating registers
 *                                              internally.
 * @retval  FSP_ERR_UNSUPPORTED                Feature not supported with the current configuration.
 *
 * @retval  FSP_ERR_INVALID_BRIGHTNESS_SETTING Invalid brightness correction setting found
 * @note    This API can be called when the driver is in the DISPLAY_STATE_DISPLAYING state. It returns an error if
 *           the register update operation for the background screen generation blocks or the output control block is
 *           being held.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_ColorCorrection (display_ctrl_t const * const       p_api_ctrl,
                                   display_correction_t const * const p_correction)
{
#if GLCDC_CFG_COLOR_CORRECTION_ENABLE
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;

 #if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_correction);
    FSP_ERROR_RETURN((DISPLAY_STATE_DISPLAYING == p_ctrl->state), FSP_ERR_INVALID_MODE);

    if (p_correction->brightness.enable)
    {
        /* Ensure brightness settings are in range */
        FSP_ERROR_RETURN((FSP_SUCCESS == r_glcdc_param_check_brightness(&(p_correction->brightness))),
                         FSP_ERR_INVALID_BRIGHTNESS_SETTING);
    }
 #endif

    /* Return immediately if the register updatings are performed */
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->OUT.VLATCH_b.VEN), FSP_ERR_INVALID_UPDATE_TIMING);
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->BG.EN_b.VEN), FSP_ERR_INVALID_UPDATE_TIMING);

    /* Configure the brightness and contrast correction register setting. */
    r_glcdc_brightness_correction(p_ctrl, &p_correction->brightness);
    r_glcdc_contrast_correction(p_ctrl, &p_correction->contrast);

    /* Update the Output block register setting. */
    R_GLCDC->OUT.VLATCH_b.VEN = 1U;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_correction);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Write an entire color look-up table (CLUT) in the GLCDC module. Implements display_api_t::clut.
 *
 * @retval  FSP_SUCCESS                    CLUT written successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to the control block or CLUT source data is NULL.
 * @retval  FSP_ERR_INVALID_UPDATE_TIMING  R_GLCDC_ClutEdit was already used to edit the specified CLUT this frame.
 * @retval  FSP_ERR_INVALID_CLUT_ACCESS    Illegal CLUT entry or size is specified.
 * @note    This API can be called any time. The written data will be used after the next vertical sync event.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_ClutUpdate (display_ctrl_t const * const     p_api_ctrl,
                              display_clut_cfg_t const * const p_clut_cfg,
                              display_frame_layer_t            layer)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_clut_cfg);
    FSP_ERROR_RETURN(g_clut_data_latched[layer], FSP_ERR_INVALID_UPDATE_TIMING);
    FSP_ERROR_RETURN((GLCDC_PRV_CLUT_ENTRY_SIZE > p_clut_cfg->start), FSP_ERR_INVALID_CLUT_ACCESS);
    FSP_ERROR_RETURN((GLCDC_PRV_CLUT_ENTRY_SIZE >= p_clut_cfg->size), FSP_ERR_INVALID_CLUT_ACCESS);
#endif

    /* Get the index of the CLUT not in use */
    uint32_t target_plane = R_GLCDC->GR[layer].CLUTINT_b.SEL ? 0 : 1;

    /* Get the start address in the destination CLUT hardware array based on the currently selected table and layer */
    uint32_t volatile * clut_hw = R_GLCDC->GR1_CLUT0 +
                                  ((target_plane + (uint32_t) (layer << 1)) * GLCDC_PRV_CLUT_ENTRY_SIZE) +
                                  p_clut_cfg->start;

    /* Copy the new CLUT data from the source memory to the CLUT SRAM in the GLCDC module */
    memcpy((void *) clut_hw, p_clut_cfg->p_base, sizeof(uint32_t) * p_clut_cfg->size);

    /* Swap to the new CLUT table data on the next frame */
    R_GLCDC->GR[layer].CLUTINT_b.SEL = target_plane & 1;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Update an element of a color look-up table (CLUT) in the GLCDC module. Implements display_api_t::clutEdit.
 *
 * @retval  FSP_SUCCESS                  CLUT element updated successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to the control block is NULL.
 * @note    This API can be called any time. The written data will be used after the next vertical sync event.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_ClutEdit (display_ctrl_t const * const p_api_ctrl,
                            display_frame_layer_t        layer,
                            uint8_t                      index,
                            uint32_t                     color)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
#endif

    static uint32_t volatile * clut_hw[2] = {R_GLCDC->GR1_CLUT0, R_GLCDC->GR2_CLUT0};

    /* If the previously written CLUT has been selected, switch to the unused one */
    if (g_clut_data_latched[layer])
    {
        g_clut_data_latched[layer] = false;

        /* Get the index of the CLUT not in use */
        uint32_t target_plane = R_GLCDC->GR[layer].CLUTINT_b.SEL ? 0 : 1;

        /* Get the start address of the destination CLUT hardware array */
        uint32_t volatile * clut_hw_new = R_GLCDC->GR1_CLUT0 +
                                          ((target_plane + (uint32_t) (layer << 1)) * GLCDC_PRV_CLUT_ENTRY_SIZE);

        /* Copy the old data to the new table then save the new table address */
        memcpy((void *) clut_hw_new, (void *) clut_hw[layer], GLCDC_PRV_CLUT_ENTRY_SIZE * 4U);
        clut_hw[layer] = clut_hw_new;

        /* Swap to the new CLUT table data on the next frame */
        R_GLCDC->GR[layer].CLUTINT_b.SEL = target_plane & 1;
    }

    /* Set the CLUT element */
    clut_hw[layer][index] = color;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configuring color key is not supported for GLCDC.
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_ColorKeySet (display_ctrl_t const * const p_api_ctrl,
                               display_colorkeying_layer_t  key_cfg,
                               display_frame_layer_t        layer)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(key_cfg);
    FSP_PARAMETER_NOT_USED(layer);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Get status of GLCDC module. Implements display_api_t::statusGet.
 *
 * @retval  FSP_SUCCESS         Got status successfully.
 * @retval  FSP_ERR_ASSERTION   Pointer to the control block or the status structure is NULL.
 * @note    The GLCDC hardware starts the fading processing at the first Vsync after the previous LayerChange() call is
 * held.
 *      Due to this behavior of the hardware, this API may not return DISPLAY_FADE_STATUS_FADING_UNDERWAY as the fading
 *       status, if it is called before the first Vsync after LayerChange() is called. In this case, the API returns
 *       DISPLAY_FADE_STATUS_PENDING, instead of DISPLAY_FADE_STATUS_NOT_UNDERWAY.
 **********************************************************************************************************************/
fsp_err_t R_GLCDC_StatusGet (display_ctrl_t const * const p_api_ctrl, display_status_t * const p_status)
{
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) p_api_ctrl;

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_status);
#endif

    /* Return the GLCDC HAL driver state */
    p_status->state = p_ctrl->state;

    /* Return the fading status for the layers */
    for (display_frame_layer_t layer = (display_frame_layer_t) 0; layer <= DISPLAY_FRAME_LAYER_2; layer++)
    {
        if ((bool) (R_GLCDC->GR[layer].VEN & 1U) || (g_fade_pending[layer] > g_frame_ctr))
        {
            /* Fading status is uncertain (the reason is described above). */
            p_status->fade_status[layer] = DISPLAY_FADE_STATUS_PENDING;
        }
        else
        {
            if (R_GLCDC->GR[layer].MON & 1U)
            {
                p_status->fade_status[layer] = DISPLAY_FADE_STATUS_FADING_UNDERWAY;
            }
            else
            {
                p_status->fade_status[layer] = DISPLAY_FADE_STATUS_NOT_UNDERWAY;
            }
        }
    }

    return FSP_SUCCESS;
}

/* @} (end addtogroup GLCDC) */

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * The GLCDC stop subroutine for R_GLCDC_Stop API.
 * @param[in]     p_ctrl                       Pointer to the configuration structure for display interface
 * @retval  FSP_SUCCESS                   Stoped successfully.
 * @retval  FSP_ERR_INVALID_UPDATE_TIMING The function call is performed while the GLCDC is updating register values
 *                                          internally.
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_stop (glcdc_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

#if defined(GLCDC_CFG_USING_DSI)

    /* DSI must be stopped before GLCDC. See RA8 UM R01UH0995EJ0050 Section 56.3.7.2 */
    glcdc_extended_cfg_t * p_extend     = (glcdc_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    mipi_dsi_instance_t  * dsi_instance = (mipi_dsi_instance_t *) p_extend->phy_layer;
    err = dsi_instance->p_api->stop(dsi_instance->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Return immediately if the register is being updated */
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->GR[DISPLAY_FRAME_LAYER_1].VEN_b.PVEN), FSP_ERR_INVALID_UPDATE_TIMING);
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->GR[DISPLAY_FRAME_LAYER_2].VEN_b.PVEN), FSP_ERR_INVALID_UPDATE_TIMING);
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->OUT.VLATCH_b.VEN), FSP_ERR_INVALID_UPDATE_TIMING);
    FSP_ERROR_RETURN(false == (bool) (R_GLCDC->BG.EN_b.VEN), FSP_ERR_INVALID_UPDATE_TIMING);

    /* Disable background plane operation */
    R_GLCDC->BG.EN_b.EN = 0U;

    p_ctrl->state = DISPLAY_STATE_OPENED;

    return err;
}

#if (GLCDC_CFG_PARAM_CHECKING_ENABLE)
 #if GLCDC_CFG_COLOR_CORRECTION_ENABLE

/*******************************************************************************************************************//**
 * The parameter checking subroutine for brightness correction.
 * @param[in]     p_brightness   Pointer to a brightness setting struct
 * @retval  FSP_SUCCESS                           No parameter error found
 * @retval  FSP_ERR_INVALID_BRIGHTNESS_SETTING    Invalid brightness setting found
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_param_check_brightness (display_brightness_t const * const p_brightness)
{
    if ((p_brightness->r > GLCDC_PRV_BRIGHTNESS_MAX) ||
        (p_brightness->g > GLCDC_PRV_BRIGHTNESS_MAX) ||
        (p_brightness->b > GLCDC_PRV_BRIGHTNESS_MAX))
    {
        return FSP_ERR_INVALID_BRIGHTNESS_SETTING;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The parameter checking subroutine for R_GLCDC_Open API.
 * @param[in]     p_gamma_correction   Pointer to the gamma configuration struct
 * @retval  FSP_SUCCESS                      No parameter error found
 * @retval  FSP_ERR_ASSERTION                Gain or threshold table pointers are NULL
 * @retval  FSP_ERR_INVALID_GAMMA_SETTING    Invalid gamma correction setting found
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_param_check_gamma_correction (gamma_correction_t const * const p_gamma_correction)
{
    uint16_t previous_threshold = 0;

    /* Verify gain/threshold tables are not NULL */
    FSP_ASSERT(p_gamma_correction->gain);
    FSP_ASSERT(p_gamma_correction->threshold);

    for (int32_t i = 0; i < DISPLAY_GAMMA_CURVE_ELEMENT_NUM; i++)
    {
        /* Each of the gamma correction threshold values must be less than GLCDC_PRV_GAMMA_THRESHOLD_MAX */
        FSP_ERROR_RETURN((GLCDC_PRV_GAMMA_THRESHOLD_MAX >= p_gamma_correction->threshold[i]),
                         FSP_ERR_INVALID_GAMMA_SETTING);

        /* The Gamma correction threshold[N] must be less than threshold[N+1] */
        FSP_ERROR_RETURN(previous_threshold <= p_gamma_correction->threshold[i], FSP_ERR_INVALID_GAMMA_SETTING);
        previous_threshold = p_gamma_correction->threshold[i];

        /* Each of gamma correction gain values must be less than GLCDC_PRV_GAMMA_GAIN_MAX */
        FSP_ERROR_RETURN((GLCDC_PRV_GAMMA_GAIN_MAX >= p_gamma_correction->gain[i]), FSP_ERR_INVALID_GAMMA_SETTING);
    }

    return FSP_SUCCESS;
}

 #endif

/*******************************************************************************************************************//**
 * The parameter checking subroutine for the R_GLCDC_Open API.
 * @param[in]     p_cfg   Pointer to the configuration structure for display interface
 * @param[in]     layer   Layer number to check
 * @retval  FSP_SUCCESS                      No parameter error found
 * @retval  FSP_ERR_INVALID_ALIGNMENT        Invalid setting for base address and memory stride
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_param_check_layer_setting_alignment (display_cfg_t const * const p_cfg,
                                                              display_frame_layer_t       layer)
{
    /* Base address and memory stride have to be aligned to 64-byte boundary */
    FSP_ERROR_RETURN(0U == ((uint32_t) (p_cfg->input[layer].p_base) % GLCDC_PRV_ADDRESS_ALIGNMENT_64B),
                     FSP_ERR_INVALID_ALIGNMENT);
    FSP_ERROR_RETURN((uint16_t) 0 ==
                     (((p_cfg->input[layer].hstride *
                        r_glcdc_get_bit_size(p_cfg->input[layer].format)) >> 3) % GLCDC_PRV_ADDRESS_ALIGNMENT_64B),
                     FSP_ERR_INVALID_ALIGNMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This is the parameter checking subroutine for the R_GLCDC_Open API.
 * @param[in]     p_cfg   Pointer to the configuration structure for display interface
 * @retval  FSP_SUCCESS                      No parameter error found
 * @retval  FSP_ERR_INVALID_TIMING_SETTING   Invalid panel timing parameter
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_param_check_display_cycle (display_cfg_t const * const p_cfg)
{
    FSP_ERROR_RETURN((GLCDC_PRV_BG_PLANE_H_CYC_MIN <= p_cfg->output.htiming.total_cyc) &&
                     (GLCDC_PRV_BG_PLANE_H_CYC_MAX >= p_cfg->output.htiming.total_cyc),
                     FSP_ERR_INVALID_TIMING_SETTING);
    FSP_ERROR_RETURN((GLCDC_PRV_BG_PLANE_V_CYC_MIN <= p_cfg->output.vtiming.total_cyc) &&
                     (GLCDC_PRV_BG_PLANE_V_CYC_MAX >= p_cfg->output.vtiming.total_cyc),
                     FSP_ERR_INVALID_TIMING_SETTING);
    FSP_ERROR_RETURN((GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_SIZE_MIN <= p_cfg->output.htiming.display_cyc) &&
                     (GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_SIZE_MAX >= p_cfg->output.htiming.display_cyc),
                     FSP_ERR_INVALID_TIMING_SETTING);
    FSP_ERROR_RETURN((GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_SIZE_MIN <= p_cfg->output.vtiming.display_cyc) &&
                     (GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_SIZE_MAX >= p_cfg->output.vtiming.display_cyc),
                     FSP_ERR_INVALID_TIMING_SETTING);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This is the parameter checking subroutine for the R_GLCDC_Open API.
 * @param[in]     p_cfg   Pointer to the configuration structure for display interface
 * @retval  FSP_SUCCESS                      No parameter error found
 * @retval  FSP_ERR_INVALID_TIMING_SETTING   Invalid panel timing parameter
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_param_check_display_timing (display_cfg_t const * const p_cfg)
{
    /* p_cfg->output.htiming.back_porch / p_cfg->output.vtiming.back_porch
     * |_ <Sync> __________________________________
     * | |______|    |
     * |1|<---BP---->|
     *                ^GLCDC_PRV_BG_PLANE_X_CYC_ACTIVE_POS_xxx
     */
    FSP_ERROR_RETURN(((GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_POS_MIN - GLCDC_PRV_BG_PLANE_HSYNC_POS_MIN) <=
                      p_cfg->output.htiming.back_porch) &&
                     ((GLCDC_PRV_BG_PLANE_H_CYC_ACTIVE_POS_MAX - GLCDC_PRV_BG_PLANE_HSYNC_POS_MIN) >=
                      p_cfg->output.htiming.back_porch),
                     FSP_ERR_INVALID_TIMING_SETTING);
    FSP_ERROR_RETURN(((GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_POS_MIN - GLCDC_PRV_BG_PLANE_VSYNC_POS_MIN) <=
                      p_cfg->output.vtiming.back_porch) &&
                     ((GLCDC_PRV_BG_PLANE_V_CYC_ACTIVE_POS_MAX - GLCDC_PRV_BG_PLANE_VSYNC_POS_MIN) >=
                      p_cfg->output.vtiming.back_porch),
                     FSP_ERR_INVALID_TIMING_SETTING);
    FSP_ERROR_RETURN((GLCDC_PRV_TCON_SIGNAL_ASSERT_WIDTH_MAX >= p_cfg->output.htiming.sync_width),
                     FSP_ERR_INVALID_TIMING_SETTING);
    FSP_ERROR_RETURN((GLCDC_PRV_TCON_SIGNAL_ASSERT_WIDTH_MAX >= p_cfg->output.vtiming.sync_width),
                     FSP_ERR_INVALID_TIMING_SETTING);

    /* See S7G2 H/W manual figure 57.26 about 3cycles */
    FSP_ERROR_RETURN((p_cfg->output.htiming.total_cyc >=
                      (p_cfg->output.htiming.back_porch + p_cfg->output.htiming.display_cyc + 3)),
                     FSP_ERR_INVALID_TIMING_SETTING);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This is the parameter checking subroutine for the R_GLCDC_Open API.
 * @param[in]     p_cfg   Pointer to the configuration structure for display interface
 * @retval  FSP_SUCCESS                      No parameter error found
 * @retval  FSP_ERR_INVALID_TIMING_SETTING   Invalid panel timing parameter
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_open_param_check_sync_signal (display_cfg_t const * const p_cfg)
{
    fsp_err_t error;

    error = r_glcdc_param_check_display_cycle(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == error, error);

    error = r_glcdc_param_check_display_timing(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == error, error);

    /* See RA6M3 User's Manual (R01UH0886EJ0100) Figure 58.26 "Definition of background screen" for explanation of +2 */
    FSP_ERROR_RETURN((p_cfg->output.vtiming.total_cyc >=
                      (p_cfg->output.vtiming.back_porch + p_cfg->output.vtiming.display_cyc + 2)),
                     FSP_ERR_INVALID_TIMING_SETTING);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The parameter checking subroutine for the R_GLCDC_Open API.
 * @param[in]     p_cfg   Pointer to the configuration structure for display interface
 * @retval  FSP_SUCCESS                      No parameter error found
 * @retval  FSP_ERR_INVALID_LAYER_SETTING    Invalid layer setting found
 * @retval  FSP_ERR_INVALID_ALIGNMENT        Invalid setting for base address and memory stride
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_open_param_check_layer_setting (display_cfg_t const * const p_cfg)
{
    fsp_err_t error;
    for (uint32_t i = 0U; i <= DISPLAY_FRAME_LAYER_2; i++)
    {
        if (p_cfg->input[i].p_base)
        {
            error = r_glcdc_param_check_layer_setting_alignment(p_cfg, (display_frame_layer_t) i);
            FSP_ERROR_RETURN(FSP_SUCCESS == error, error);

            /* Check horizontal/vertical pixels is less than or equal to maximum value, also horizontal pixel
             * must not be an odd value. Horizontal check is intently not performed because of supporting line
             * repeating mode.*/

            uint16_t vline_size = p_cfg->input[i].vsize;
            if (p_cfg->input[i].lines_repeat_enable)
            {
                vline_size = (uint16_t) (vline_size * p_cfg->input[i].lines_repeat_times);
            }

            FSP_ERROR_RETURN((GLCDC_PRV_GR_PLANE_V_CYC_ACTIVE_SIZE_MAX >= vline_size), FSP_ERR_INVALID_LAYER_SETTING);

            /* Check horizontal/vertical pixels is less than or equal to the maximum value, also horizontal pixel must
             * not be an odd value*/
            FSP_ERROR_RETURN((uint16_t) 0 == ((p_cfg->input[i].hsize) % (uint16_t) 2), FSP_ERR_INVALID_LAYER_SETTING);

            /* Check the number of data transfer times per a line (64bytes/transfer) */
            FSP_ERROR_RETURN((GLCDC_PRV_GR_PLANE_TOTAL_TRANSFER_TIMES_MAX >=
                              (((p_cfg->input[i].hstride *
                                 r_glcdc_get_bit_size(p_cfg->input[i].format)) / 8) /
                               GLCDC_PRV_ADDRESS_ALIGNMENT_64B)),
                             FSP_ERR_INVALID_LAYER_SETTING);
        }
    }

    return FSP_SUCCESS;
}

 #if GLCDC_CFG_COLOR_CORRECTION_ENABLE

/*******************************************************************************************************************//**
 * The parameter checking subroutine for R_GLCDC_Open API.
 * @param[in]     p_cfg   Pointer to the configuration structure for display interface
 * @retval  FSP_SUCCESS                        No parameter error found
 * @retval  FSP_ERR_ASSERTION                  Gain or threshold table pointers are NULL
 * @retval  FSP_ERR_INVALID_GAMMA_SETTING      Invalid gamma correction setting found
 * @retval  FSP_ERR_INVALID_BRIGHTNESS_SETTING Invalid brightness correction setting found
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_open_param_check_correction_setting (display_cfg_t const * const p_cfg)
{
    fsp_err_t error;

    if (p_cfg->output.brightness.enable)
    {
        error = r_glcdc_param_check_brightness(&(p_cfg->output.brightness));
        FSP_ERROR_RETURN(FSP_SUCCESS == error, error);
    }

    if (p_cfg->output.p_gamma_correction)
    {
        if (p_cfg->output.p_gamma_correction->b.enable)
        {
            error = r_glcdc_param_check_gamma_correction(&(p_cfg->output.p_gamma_correction->b));
            FSP_ERROR_RETURN(FSP_SUCCESS == error, error);
        }

        if (p_cfg->output.p_gamma_correction->g.enable)
        {
            error = r_glcdc_param_check_gamma_correction(&(p_cfg->output.p_gamma_correction->g));
            FSP_ERROR_RETURN(FSP_SUCCESS == error, error);
        }

        if (p_cfg->output.p_gamma_correction->r.enable)
        {
            error = r_glcdc_param_check_gamma_correction(&(p_cfg->output.p_gamma_correction->r));
            FSP_ERROR_RETURN(FSP_SUCCESS == error, error);
        }
    }

    return FSP_SUCCESS;
}

 #endif

/*******************************************************************************************************************//**
 * The parameter checking subroutine for R_GLCDC_Open API.
 * @param[in] p_cfg   Pointer to the configuration structure for display interface
 * @retval  FSP_SUCCESS                        No parameter error found
 * @retval  FSP_ERR_ASSERTION                  Pointer to the control block is NULL
 * @retval  FSP_ERR_CLOCK_GENERATION           Clock ratio setting is invalid
 * @retval  FSP_ERR_INVALID_TIMING_SETTING     Invalid panel timing parameter
 * @retval  FSP_ERR_INVALID_LAYER_SETTING      Invalid layer setting found
 * @retval  FSP_ERR_INVALID_ALIGNMENT          Input data alignment invalid
 * @retval  FSP_ERR_INVALID_GAMMA_SETTING      Invalid gamma correction setting found
 * @retval  FSP_ERR_INVALID_BRIGHTNESS_SETTING Invalid brightness correction setting found
 **********************************************************************************************************************/
static fsp_err_t r_glcdc_open_param_check (display_cfg_t const * const p_cfg)
{
    fsp_err_t error;

    FSP_ASSERT(p_cfg);
    FSP_ASSERT(p_cfg->p_extend);

    glcdc_extended_cfg_t * pextend = (glcdc_extended_cfg_t *) p_cfg->p_extend;

    /* Sync signal parameter check */
    error = r_glcdc_open_param_check_sync_signal(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == error, error);

    /* Layer setting parameter check */
    error = r_glcdc_open_param_check_layer_setting(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == error, error);

 #if GLCDC_CFG_COLOR_CORRECTION_ENABLE

    /* Color correction setting parameter check */
    error = r_glcdc_open_param_check_correction_setting(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == error, error);
 #endif

    /* Ensure clock division ratio is initialized */
    FSP_ERROR_RETURN(0 != pextend->clock_div_ratio, FSP_ERR_CLOCK_GENERATION);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Subroutine to configure dot clock setting
 * @param[in]     p_cfg        Pointer to the configuration structure for display interface
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_clock_set (display_cfg_t const * const p_cfg)
{
    glcdc_extended_cfg_t * pextend = (glcdc_extended_cfg_t *) p_cfg->p_extend;

    /* Build PANEL_CLK bitfields */
    uint32_t pixsel =
        ((DISPLAY_OUT_FORMAT_8BITS_SERIAL !=
          p_cfg->output.format) ? 0 : GLCDC_PRV_SYSCNT_PANEL_CLK_PIXSEL_SERIALRGB);
    uint32_t clksel = ((GLCDC_CLK_SRC_INTERNAL == pextend->clksrc) ? GLCDC_PRV_SYSCNT_PANEL_CLK_CLKSEL_PLL : 0);
    uint32_t clken  = GLCDC_PRV_SYSCNT_PANEL_CLK_CLKEN_ENABLE;
    uint32_t dcdr   = (pextend->clock_div_ratio & GLCDC_PRV_SYSCNT_PANEL_CLK_DCDR_MASK);

    /* Set panel clock configuration */
    R_GLCDC->SYSCNT.PANEL_CLK = pixsel | clksel | clken | dcdr;
}

/*******************************************************************************************************************//**
 * Subroutine to configure the sync signal setting (TCON block setting)
 * @param[in]     p_cfg        Pointer to the configuration structure for display interface
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_sync_signal_set (display_cfg_t const * const p_cfg)
{
    glcdc_extended_cfg_t * pextend = (glcdc_extended_cfg_t *) p_cfg->p_extend;
    glcdc_tcon_pin_t       tcon_hsync;
    glcdc_tcon_pin_t       tcon_vsync;
    glcdc_tcon_pin_t       tcon_de;

    /* Because this function is called before gamma correction is enabled we can clobber the CLKPHASE register */
    if (DISPLAY_SIGNAL_SYNC_EDGE_RISING == p_cfg->output.sync_edge)
    {
        /* Set all phases to rising edge */
        R_GLCDC->OUT.CLKPHASE = GLCDC_PRV_OUT_CLKPHASE_ALL_RISING;
    }
    else
    {
        /* Set all phases to falling edge */
        R_GLCDC->OUT.CLKPHASE = GLCDC_PRV_OUT_CLKPHASE_ALL_FALLING;
    }

    /* Clear signal reference timing */
    R_GLCDC->TCON.TIM = 0;

    tcon_hsync = pextend->tcon_hsync;
    tcon_vsync = pextend->tcon_vsync;
    tcon_de    = pextend->tcon_de;

    if (GLCDC_TCON_PIN_NONE != tcon_hsync)
    {
        r_glcdc_hsync_set(tcon_hsync, &p_cfg->output.htiming);
    }

    if (GLCDC_TCON_PIN_NONE != tcon_vsync)
    {
        r_glcdc_vsync_set(tcon_vsync, &p_cfg->output.vtiming);
    }

    if (GLCDC_TCON_PIN_NONE != tcon_de)
    {
        r_glcdc_data_enable_set(tcon_de,
                                &p_cfg->output.vtiming,
                                &p_cfg->output.htiming,
                                p_cfg->output.data_enable_polarity);
    }
}

/*******************************************************************************************************************//**
 * Subroutine to configure a TCON signal output
 * @param[in]     tcon         TCON pin select(GLCDC_TCON_PIN_0|GLCDC_TCON_PIN_1|GLCDC_TCON_PIN_2|GLCDC_TCON_PIN_3)
 * @param[in]     signal       Signal to output
 * @param[in]     polarity     Signal polarity
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_tcon_set (glcdc_tcon_pin_t           tcon,
                              glcdc_tcon_signal_select_t signal,
                              display_signal_polarity_t  polarity)
{
    /* Set signal polarity */
    if (DISPLAY_SIGNAL_POLARITY_LOACTIVE == polarity)
    {
        /* Set INV bit depending on register */
        if (GLCDC_TCON_SIGNAL_SELECT_DE != signal)
        {
            *g_tcon_lut[signal] |= GLCDC_PRV_TCON_STXX2_INV_SET;
        }
        else
        {
            R_GLCDC->TCON.DE = 1;
        }
    }

    /* Set TCON signal */
    *g_tcon_lut[tcon] |= signal;
}

/*******************************************************************************************************************//**
 * Subroutine to configure the horizontal signal setting
 * @param[in]     tcon        TCON pin select(GLCDC_TCON_PIN_0|GLCDC_TCON_PIN_1|GLCDC_TCON_PIN_2|GLCDC_TCON_PIN_3)
 * @param[in]     timing      Hsync signal timing
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_hsync_set (glcdc_tcon_pin_t tcon, display_timing_t const * timing)
{
    r_glcdc_tcon_set(tcon, GLCDC_TCON_SIGNAL_SELECT_STHA_HS, timing->sync_polarity);

    R_GLCDC->TCON.STHA1 = timing->sync_width & GLCDC_PRV_TCON_STHX1_HW_MASK;
}

/*******************************************************************************************************************//**
 * Subroutine to configure the vertical signal setting
 * @param[in]     tcon        TCON pin select(GLCDC_TCON_PIN_0|GLCDC_TCON_PIN_1|GLCDC_TCON_PIN_2|GLCDC_TCON_PIN_3)
 * @param[in]     timing      Vsync signal timing
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_vsync_set (glcdc_tcon_pin_t tcon, display_timing_t const * const timing)
{
    r_glcdc_tcon_set(tcon, GLCDC_TCON_SIGNAL_SELECT_STVA_VS, timing->sync_polarity);

    R_GLCDC->TCON.STVA1 = timing->sync_width & GLCDC_PRV_TCON_STVX1_VW_MASK;
}

/*******************************************************************************************************************//**
 * Subroutine to configure the data enable(DE) signal setting
 * @param[in]     tcon        TCON pin select(GLCDC_TCON_PIN_0|GLCDC_TCON_PIN_1|GLCDC_TCON_PIN_2|GLCDC_TCON_PIN_3)
 * @param[in]     vtiming     DE signal vertical timing
 * @param[in]     htiming     DE signal horizontal timing
 * @param[in]     polarity    DE signal porarity(DISPLAY_SIGNAL_POLARITY_LOACTIVE|DISPLAY_SIGNAL_POLARITY_HIACTIVE)
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_data_enable_set (glcdc_tcon_pin_t const          tcon,
                                     display_timing_t const * const  vtiming,
                                     display_timing_t const * const  htiming,
                                     display_signal_polarity_t const polarity)
{
    r_glcdc_tcon_set(tcon, GLCDC_TCON_SIGNAL_SELECT_DE, polarity);

    R_GLCDC->TCON.STHB1 = ((htiming->back_porch & GLCDC_PRV_TCON_STHX1_HS_MASK) << 16) +
                          (htiming->display_cyc & GLCDC_PRV_TCON_STHX1_HW_MASK);
    R_GLCDC->TCON.STVB1 = ((vtiming->back_porch & GLCDC_PRV_TCON_STVX1_VS_MASK) << 16) +
                          (vtiming->display_cyc & GLCDC_PRV_TCON_STVX1_VW_MASK);
}

/*******************************************************************************************************************//**
 * Subroutine to configure the background screen setting
 *          - Panel timing setting
 *          - Color setting for the background screen
 * @param[in]     p_cfg      Pointer to the configuration structure for display interface
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_background_screen_set (display_cfg_t const * const p_cfg)
{
    /* Set number of total cycles for a line including sync, back porch and Front porch */
    R_GLCDC->BG.PERI = ((p_cfg->output.vtiming.total_cyc & GLCDC_PRV_BG_PERI_FV_MASK) << 16) +
                       (p_cfg->output.htiming.total_cyc & GLCDC_PRV_BG_PERI_FH_MASK);
    R_GLCDC->BG.SYNC = ((GLCDC_PRV_BG_PLANE_VSYNC_POS_MIN & GLCDC_PRV_BG_SYNC_VP_MASK) << 16) +
                       (GLCDC_PRV_BG_PLANE_HSYNC_POS_MIN & GLCDC_PRV_BG_SYNC_HP_MASK);

    /* Set the start position and width of the background screen */
    R_GLCDC->BG.HSIZE = ((((uint32_t) (p_cfg->output.htiming.back_porch) + GLCDC_PRV_BG_PLANE_HSYNC_POS_MIN) &
                          GLCDC_PRV_BG_HSIZE_HP_MASK) << 16) +
                        (p_cfg->output.htiming.display_cyc & GLCDC_PRV_BG_HSIZE_HW_MASK);
    R_GLCDC->BG.VSIZE = ((((uint32_t) (p_cfg->output.vtiming.back_porch) + GLCDC_PRV_BG_PLANE_VSYNC_POS_MIN) &
                          GLCDC_PRV_BG_VSIZE_VP_MASK) << 16) +
                        (p_cfg->output.vtiming.display_cyc & GLCDC_PRV_BG_VSIZE_VW_MASK);

    /* Set the background color */
    R_GLCDC->BG.BGC = ((uint32_t) (p_cfg->output.bg_color.byte.r) << 16) +
                      ((uint32_t) (p_cfg->output.bg_color.byte.g) << 8) +
                      ((uint32_t) (p_cfg->output.bg_color.byte.b));
}

/*******************************************************************************************************************//**
 * Subroutine to configure the blending setting for the graphics planes
 * @param[in]     p_layer     The layer configuration
 * @param[in]     layer       Layer number
 * @retval        void
 * @note    This function does not perform parameter check and it would be expected to be done in the caller function.
 **********************************************************************************************************************/
static void r_glcdc_graphics_layer_blend_condition_set (display_layer_t const * const p_layer,
                                                        display_frame_layer_t const   layer)
{
    uint32_t arcon_temp = 0;
    uint32_t ab6_temp;
    uint32_t ab7_temp;

    if (DISPLAY_FADE_CONTROL_NONE != p_layer->fade_control)
    {
        /* Enable alpha blending */
        arcon_temp = GLCDC_PRV_GR_AB1_ARCON_SET;

        /* Set AB6 and AB7 for fade in or fade out */
        if (DISPLAY_FADE_CONTROL_FADEIN == p_layer->fade_control)
        {
            ab7_temp = (GLCDC_FADING_CONTROL_INITIAL_ALPHA_MIN & GLCDC_PRV_GR_AB7_ARCDEF_MASK) << 16;
            ab6_temp = ((uint32_t) p_layer->fade_speed & GLCDC_PRV_GR_AB6_ARCCOEF_MASK) << 16;
        }
        else
        {
            ab7_temp = (GLCDC_FADING_CONTROL_INITIAL_ALPHA_MAX & GLCDC_PRV_GR_AB7_ARCDEF_MASK) << 16;
            ab6_temp = ((uint32_t) (p_layer->fade_speed | (1U << 8)) & GLCDC_PRV_GR_AB6_ARCCOEF_MASK) << 16;
        }

        R_GLCDC->GR[layer].AB6 = ab6_temp;
        R_GLCDC->GR[layer].AB7 = ab7_temp;

        /* Set g_fade_pending flag to inform R_GLCDC_StatusGet that a fade is scheduled */
        g_fade_pending[layer] = g_frame_ctr + 2;
    }

    /* Set blend mode and enable if configured */
    R_GLCDC->GR[layer].AB1 = (GLCDC_PLANE_BLEND_ON_LOWER_LAYER & GLCDC_PRV_GR_AB1_DISPSEL_MASK) + arcon_temp;

    /* Graphics data read enable */
    R_GLCDC->GR[layer].FLMRD = 1U;
}

/*******************************************************************************************************************//**
 * Subroutine to recalculate the configuration for the graphics planes. This routine recalculates the layer
 *           configuration if the layer is beyond the left/right/top/bottom end of the active video region.
 * @param[in]     p_input         The input frame buffer configuration
 * @param[in]     p_layer         The layer configuration
 * @param[in,out] p_recalculated  Pointer to store recalculated parameter
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_graphics_layer_param_recalculation (display_input_cfg_t const * const p_input,
                                                        display_layer_t const * const     p_layer,
                                                        glcdc_recalculated_param_t      * p_recalculated)
{
    uint16_t bit_size    = r_glcdc_get_bit_size(p_input->format);
    int32_t  line_offset = (int32_t) ((p_input->hstride * bit_size) / 8);

    p_recalculated->hpix_size   = 0U;
    p_recalculated->vpix_size   = 0U;
    p_recalculated->hpix_offset = 0;
    p_recalculated->vpix_offset = 0;

    r_glcdc_pixel_size_recalculate(p_input, p_layer, p_recalculated, bit_size);

    int16_t coord_y = p_layer->coordinate.y;

    /* Get data size to be read in a line */
    p_recalculated->hread_size = ((uint32_t) p_recalculated->hpix_size * bit_size) / 8;

    /* If line repeat mode is enabled, data number to be read (in a line) is multiplied by line number of image */
    if (p_input->lines_repeat_enable)
    {
        p_recalculated->hread_size *= p_input->vsize;
    }

    /* Calculate data size to be aligned to a 64-byte boundary. This is required by hardware */
    if (p_recalculated->hread_size % GLCDC_PRV_ADDRESS_ALIGNMENT_64B)
    {
        p_recalculated->hread_size = (p_recalculated->hread_size & (uint32_t) (~0x3F)) + // NOLINT(readability-magic-numbers)
                                     GLCDC_PRV_ADDRESS_ALIGNMENT_64B;
    }

    if ((g_ctrl_blk.vsize >= coord_y) && (0 <= coord_y))
    {
        /* If graphics layer offset is less than or equal to display window size, calculate the actual pixel size to
         * display */
        if ((g_ctrl_blk.vsize - coord_y) < p_input->vsize)
        {
            /* Actual pixel size to display is less than display window size */
            p_recalculated->vpix_size = (uint16_t) (g_ctrl_blk.vsize - coord_y);
        }
        else
        {
            /* Actual pixel size to display is the same as display window size */
            p_recalculated->vpix_size = p_input->vsize;
        }

        p_recalculated->vpix_offset = coord_y;
    }
    else if ((0 > coord_y) && (p_input->vsize + coord_y > 0))
    {
        /* If the offset of the graphics layer is less than the top end of display window but some part of the layer
         * may still be visible, calculate actual pixel size to display */

        /* Calculate actual pixel size, the pixels to be displayed is less than the display window size */
        p_recalculated->vpix_size     = (uint16_t) (p_input->vsize + coord_y);
        p_recalculated->base_address += (uint32_t) (line_offset * ((coord_y) * (-1)));
    }
    else
    {
        p_recalculated->vpix_size = 0U;
    }
}

/*******************************************************************************************************************//**
 * Subroutine to configure the graphics layer register settings which includes...
 *          - Blend setting of foreground or background plane on background plane
 *          - Rectangle area blending settings
 * @param[in]     p_input         The input frame buffer configuration
 * @param[in]     p_layer         The layer configuration
 * @param[in]     layer           Layer number
 * @retval        void
 * @note    This function does not perform parameter check and it would be expected to be done in the caller function.
 **********************************************************************************************************************/
static void r_glcdc_graphics_layer_set (display_input_cfg_t const * const p_input,
                                        display_layer_t const * const     p_layer,
                                        display_frame_layer_t const       layer)
{
    uint32_t bit_size    = r_glcdc_get_bit_size(p_input->format);
    int32_t  line_offset = (int32_t) ((p_input->hstride * bit_size) / 8);
    glcdc_recalculated_param_t recalculated;
    uint32_t lnnum_temp;
    uint32_t grcvw_temp;
    uint32_t arcvw_temp;

    /* If the base address is NULL, just set the layer transparent and disable read memory access */
    if (NULL == p_input->p_base)
    {
        R_GLCDC->GR[layer].AB1   = GLCDC_PLANE_BLEND_TRANSPARENT & GLCDC_PRV_GR_AB1_DISPSEL_MASK; /* Set layer transparent */
        R_GLCDC->GR[layer].FLMRD = 0U;

        return;
    }

    /* Set layer pixel color format */
    R_GLCDC->GR[layer].FLM6 = ((uint32_t) g_format_lut[p_input->format]) << 28;

    r_glcdc_graphics_layer_param_recalculation(p_input, p_layer, &recalculated);

    /* Set the base address of graphics plane */
    R_GLCDC->GR[layer].FLM2 = recalculated.base_address;

    /* If line number descending mode is enable, change its sign */
    if (p_input->line_descending_enable)
    {
        line_offset *= (-1);
    }

    /* In line repeat mode, the GLCDC is configured to treat the entire repeated region of the buffer as a single line.
     * The number of lines given in the configuration reflects how many times the pattern is repeated. */
    if (p_input->lines_repeat_enable)
    {
        /* Set the line offset address for accessing the graphics data on graphics plane */
        lnnum_temp = (uint32_t) (p_input->lines_repeat_times);

        /* When line repeating mode, always read data on same line(s) */
        R_GLCDC->GR[layer].FLM3 = 0;

        /* Set the total visible line count based on the size and number of the repeated region */
        grcvw_temp = (uint32_t) (recalculated.vpix_size * p_input->lines_repeat_times);
        arcvw_temp = grcvw_temp;
    }
    else
    {
        /* Set the line offset address for accessing the graphics data */
        lnnum_temp = (uint32_t) (recalculated.vpix_size);

        /* Set the line offset address for accessing the graphics data on graphics plane */
        R_GLCDC->GR[layer].FLM3 = ((uint32_t) line_offset & GLCDC_PRV_GR_FLM3_LNOFF_MASK) << 16;

        /* Set the total visible line count */
        grcvw_temp = recalculated.vpix_size;
        arcvw_temp = grcvw_temp;
    }

    /* Set the number of data transfer times per line, 64 bytes are transferred in each transfer */
    /* Set (actual transfer times - 1) */
    R_GLCDC->GR[layer].FLM5 = (((lnnum_temp - 1) & GLCDC_PRV_GR_FLM5_LNNUM_MASK) << 16) +
                              (((recalculated.hread_size >> 6) - 1) & GLCDC_PRV_GR_FLM5_DATANUM_MASK);

    /* Set the graphics area horizontal dimensions */
    R_GLCDC->GR[layer].AB3 =
        (((uint32_t) (g_ctrl_blk.back_porch.x + recalculated.hpix_offset) & GLCDC_PRV_GR_AB3_GRCHS_MASK) << 16) +
        (recalculated.hpix_size & GLCDC_PRV_GR_AB3_GRCHW_MASK);

    /* Set the alpha blending area horizontal dimensions */
    R_GLCDC->GR[layer].AB5 =
        (((uint32_t) (g_ctrl_blk.back_porch.x + recalculated.hpix_offset) & GLCDC_PRV_GR_AB5_ARCHS_MASK) << 16) +
        (recalculated.hpix_size & GLCDC_PRV_GR_AB5_ARCHW_MASK);

    /* Set the graphics area vertical dimensions */
    R_GLCDC->GR[layer].AB2 =
        (grcvw_temp & GLCDC_PRV_GR_AB2_GRCVW_MASK) +
        (((uint32_t) (g_ctrl_blk.back_porch.y + recalculated.vpix_offset) & GLCDC_PRV_GR_AB2_GRCVS_MASK) << 16);

    /* Set the alpha blending area vertical dimensions */
    R_GLCDC->GR[layer].AB4 =
        (arcvw_temp & GLCDC_PRV_GR_AB4_ARCVW_MASK) +
        (((uint32_t) (g_ctrl_blk.back_porch.y + recalculated.vpix_offset) & GLCDC_PRV_GR_AB4_ARCVS_MASK) << 16);

    /* Set the alpha blending condition */
    r_glcdc_graphics_layer_blend_condition_set(p_layer, layer);

    /* Reset CLUT table selection */
    R_GLCDC->GR[layer].CLUTINT = 0;
    g_clut_data_latched[0]     = true;
    g_clut_data_latched[1]     = true;
}

/*******************************************************************************************************************//**
 * Subroutine to configure the output control block register settings which includes...
 *          - Bit endian / color order setting
 *          - Output color setting
 *          - Color correction setting
 * @param[in]     p_cfg       Pointer to the configuration structure for display interface
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_output_block_set (display_cfg_t const * const p_cfg)
{
    glcdc_extended_cfg_t * pextend     = (glcdc_extended_cfg_t *) p_cfg->p_extend;
    uint32_t               outset_temp = 0;
    uint32_t               pdtha_temp  = 0;

    /* Select the output format */
    outset_temp = ((uint32_t) g_outset_lut[p_cfg->output.format]) << GLCDC_PRV_OUT_SET_FORMAT_SHIFT;
    pdtha_temp  = ((uint32_t) g_pdtha_lut[p_cfg->output.format]) << GLCDC_PRV_OUT_PDTHA_FORM_SHIFT;

    /* Selects big or little endian for output data */
    if (DISPLAY_ENDIAN_BIG == p_cfg->output.endian)
    {
        outset_temp |= GLCDC_PRV_OUT_SET_ENDIANON_ENABLE;
    }

    /* Selects the output byte order swapping */
    if (DISPLAY_COLOR_ORDER_BGR == p_cfg->output.color_order)
    {
        outset_temp |= GLCDC_PRV_OUT_SET_SWAPON_ENABLE;
    }

    /* Sets the pixel clock (the GLCDC internal signal) frequency in case that the output format is 8-bit serial RGB */
    if (DISPLAY_OUT_FORMAT_8BITS_SERIAL == p_cfg->output.format)
    {
        outset_temp |= GLCDC_PRV_OUT_SET_FRQSEL_QUARTER_DIVISION << 8;
    }

    /* Set the dithering mode */
    if (p_cfg->output.dithering_on)
    {
        if (GLCDC_DITHERING_MODE_2X2PATTERN == pextend->dithering_mode)
        {
            pdtha_temp |= (uint32_t) ((GLCDC_DITHERING_MODE_2X2PATTERN << GLCDC_PRV_OUT_PDTHA_SEL_SHIFT) |
                                      (pextend->dithering_pattern_A << GLCDC_PRV_OUT_PDTHA_PA_SHIFT) |
                                      (pextend->dithering_pattern_B << GLCDC_PRV_OUT_PDTHA_PB_SHIFT) |
                                      (pextend->dithering_pattern_C << GLCDC_PRV_OUT_PDTHA_PC_SHIFT) |
                                      (pextend->dithering_pattern_D));
        }
        else
        {
            pdtha_temp |= GLCDC_DITHERING_MODE_ROUND_OFF << GLCDC_PRV_OUT_PDTHA_SEL_SHIFT;
        }
    }

    /* Set registers */
    R_GLCDC->OUT.SET   = outset_temp;
    R_GLCDC->OUT.PDTHA = pdtha_temp;
}

#if GLCDC_CFG_COLOR_CORRECTION_ENABLE

/*******************************************************************************************************************//**
 * Subroutine to configure the brightness register settings. Pixel color output comes to be the value
 *           shown below processed by the brightness control block.
 *          - Gout = Gin + p_cfg->output.brightness.g - 512 (output.brightness.g must be 10 bits value; up to 512)
 *          - Bout = Bin + p_cfg->output.brightness.b - 512 (output.brightness.b must be 10 bits value; up to 512)
 *          - Rout = Rin + p_cfg->output.brightness.r - 512 (output.brightness.r must be 10 bits value; up to 512)
 * @param[in]  p_ctrl       Pointer to the control block for Display Interface
 * @param[in]  p_brightness Pointer to brightness configuration structure
 * @retval     void
 **********************************************************************************************************************/
static void r_glcdc_brightness_correction (glcdc_instance_ctrl_t const * const p_ctrl,
                                           display_brightness_t const * const  p_brightness)
{
    uint32_t r;
    uint32_t g;
    uint32_t b;

    if (p_brightness->enable)
    {
        g = p_brightness->g;
        b = p_brightness->b;
        r = p_brightness->r;
    }
    else
    {
        if (DISPLAY_STATE_CLOSED == p_ctrl->state)
        {
            /* If brightness setting in configuration is 'off', apply default value */
            g = GLCDC_PRV_BRIGHTNESS_DEFAULT;
            b = GLCDC_PRV_BRIGHTNESS_DEFAULT;
            r = GLCDC_PRV_BRIGHTNESS_DEFAULT;
        }
        else
        {
            return;
        }
    }

    /* Sets brightness correction register for each color in a pixel. */
    R_GLCDC->OUT.BRIGHT1 = g & GLCDC_PRV_OUT_BRIGHT1_BRTG_MASK;
    R_GLCDC->OUT.BRIGHT2 = ((b & GLCDC_PRV_OUT_BRIGHT2_BRTB_MASK) << 16) + (r & GLCDC_PRV_OUT_BRIGHT2_BRTR_MASK);
}

/*******************************************************************************************************************//**
 * Subroutine to configure the contrast register settings. Pixel color output becomes the value
 *           shown below, processed by the contrast control block. Contrast can be changed between x0.000 to x1.992
 *           (0x0:x0.000 / 0x80:x1.000 / 0xFF:x1.992).
 *          - Gout = (Gin + p_contrast->g)/128
 *          - Bout = (Bin + p_contrast->b)/128
 *          - Rout = (Rin + p_contrast->r)/128
 * @param[in]  p_ctrl     Pointer to the control block for the Display Interface
 * @param[in]  p_contrast Pointer to the contrast configuration structure
 * @retval     void
 **********************************************************************************************************************/
static void r_glcdc_contrast_correction (glcdc_instance_ctrl_t const * const p_ctrl,
                                         display_contrast_t const * const    p_contrast)
{
    uint32_t r;
    uint32_t g;
    uint32_t b;

    if (p_contrast->enable)
    {
        g = p_contrast->g;
        b = p_contrast->b;
        r = p_contrast->r;
    }
    else
    {
        if (DISPLAY_STATE_CLOSED == p_ctrl->state)
        {
            /* If the contrast setting in the configuration is set to 'off', apply default value */
            g = GLCDC_PRV_CONTRAST_DEFAULT;
            b = GLCDC_PRV_CONTRAST_DEFAULT;
            r = GLCDC_PRV_CONTRAST_DEFAULT;
        }
        else
        {
            return;
        }
    }

    /* Sets the contrast correction register for each color in a pixel. */
    R_GLCDC->OUT.CONTRAST = ((g & GLCDC_PRV_OUT_CONTRAST_CONTG_MASK) << 16) +
                            ((b & GLCDC_PRV_OUT_CONTRAST_CONTB_MASK) << 8) +
                            (r & GLCDC_PRV_OUT_CONTRAST_CONTR_MASK);
}

/*******************************************************************************************************************//**
 * Subroutine to configure the color correction order.
 *
 * @param[in]  p_cfg      Pointer to the configuration structure for the display interface
 * @retval     void
 **********************************************************************************************************************/
static void r_glcdc_color_correction_order (display_cfg_t const * const p_cfg)
{
    glcdc_extended_cfg_t * pextend = (glcdc_extended_cfg_t *) p_cfg->p_extend;

    /* Sets the Brightness/contrast and Gamma Correction processing order */
    if (GLCDC_CORRECTION_PROC_ORDER_BRIGHTNESS_CONTRAST2GAMMA == pextend->correction_proc_order)
    {
        /* OUT_CLKPHASE (LCDC clock source is PLCKA)
         * b12   FRONTGAM  = 0(Brightness/contrast correction is followed by gamma correction.)
         */
        R_GLCDC->OUT.CLKPHASE_b.FRONTGAM = 0U;
    }
    else
    {
        /* OUT_CLKPHASE (LCDC clock source is PLCKA)
         * b12   FRONTGAM  = 1(Gamma correction is followed by Brightness/contrast correction)
         */
        R_GLCDC->OUT.CLKPHASE_b.FRONTGAM = 1U;
    }
}

/*******************************************************************************************************************//**
 * Subroutine to configure the gamma correction register setting.
 * @param[in]     p_cfg      Pointer to the configuration structure for the display interface
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_gamma_correction (display_cfg_t const * const p_cfg)
{
    uint8_t i;
    uint8_t j;

    gamma_correction_t * LUT_ptr;

    /* Set gamma correction LUTs based on config struct */
    for (j = 0U; j < 3U; j++)
    {
        /* Get pointer to LUT */
        switch (j)
        {
            default:
            case 0:
            {
                LUT_ptr = &(p_cfg->output.p_gamma_correction->g);
                break;
            }

            case 1:
            {
                LUT_ptr = &(p_cfg->output.p_gamma_correction->b);
                break;
            }

            case 2:
            {
                LUT_ptr = &(p_cfg->output.p_gamma_correction->r);
                break;
            }
        }

        if (LUT_ptr->enable)
        {
            for (i = 0U; i < (uint8_t) (DISPLAY_GAMMA_CURVE_ELEMENT_NUM / 2); i++)
            {
                R_GLCDC->GAM[j].LUT[i] = ((LUT_ptr->gain[i * 2U] & GLCDC_PRV_GAMX_LUTX_GAIN_MASK) << 16) +
                                         (LUT_ptr->gain[(i * 2U) + 1U] & GLCDC_PRV_GAMX_LUTX_GAIN_MASK);
            }

            for (i = 0U; i < (uint8_t) (DISPLAY_GAMMA_CURVE_ELEMENT_NUM / 3); i++)
            {
                R_GLCDC->GAM[j].AREA[i] = ((LUT_ptr->threshold[(i * 3U) + 1U] & GLCDC_PRV_GAMX_AREAX_MASK) << 20) +
                                          ((LUT_ptr->threshold[(i * 3U) + 2U] & GLCDC_PRV_GAMX_AREAX_MASK) << 10) +
                                          (LUT_ptr->threshold[(i * 3U) + 3U] & GLCDC_PRV_GAMX_AREAX_MASK);
            }

            /* Enable LUT */
            R_GLCDC->GAM[j].GAM_SW = 1U;
        }
        else
        {
            R_GLCDC->GAM[j].GAM_SW = 0U;
        }

        R_GLCDC->GAM[j].LATCH = 1U;
    }
}

#endif

/*******************************************************************************************************************//**
 * Subroutine to get the bit size of the specified format.
 * @param[in]     format   Color format (specify display_in_format_t type enumeration value)
 * @retval        Bit size
 **********************************************************************************************************************/
static inline uint16_t r_glcdc_get_bit_size (display_in_format_t const format)
{
    return g_pixsize_lut[format];
}

/*******************************************************************************************************************//**
 * The line detection interrupt service routine.
 *           This ISR is called when the number of the display line reaches the designated number of lines. If a
 *           callback function is registered in R_GLCDC_Open(), it is called from this ISR and the
 *           DISPLAY_EVENT_LINE_DETECTION event code is set as its argument.
 * @retval        none
 **********************************************************************************************************************/
void glcdc_line_detect_isr (void)
{
    FSP_CONTEXT_SAVE

    display_callback_args_t args;
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) g_ctrl_blk.p_context;

    /* Increment frame counter */
    g_frame_ctr++;

    /* Handle overflow case for g_frame_ctr vs. g_fade_pending
     * (at 60FPS this should occur once every 2.25 years of uptime) */
    if (!g_frame_ctr)
    {
        g_fade_pending[0] = 0;
        g_fade_pending[1] = 0;
    }

    /* Set CLUT state to latched */
    g_clut_data_latched[0] = true;
    g_clut_data_latched[1] = true;

    /* Call back callback function if it is registered */
    if (NULL != p_ctrl->p_callback)
    {
        args.event     = DISPLAY_EVENT_LINE_DETECTION;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args);
    }

    /* Clear interrupt flag in the register of the GLCDC module */
    R_GLCDC->SYSCNT.STCLR_b.VPOSCLR = 1U;

    /* Clear interrupt flag in the register of the NVIC module */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * The graphics plane 1 underflow detection interrupt service routine.
 *           This ISR is called when the underflow occurs in the graphics plane 1 control block. If a callback function
 *           is registered in R_GLCDC_Open(), it is called back from this ISR and the DISPLAY_EVENT_GR1_UNDERFLOW event
 *           code is set as its argument.
 * @retval        none
 **********************************************************************************************************************/
void glcdc_underflow_1_isr (void)
{
    FSP_CONTEXT_SAVE

    display_callback_args_t args;
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) g_ctrl_blk.p_context;

    /* Call back callback function if it is registered */
    if (NULL != p_ctrl->p_callback)
    {
        args.event     = DISPLAY_EVENT_GR1_UNDERFLOW;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args);
    }

    /* Clear interrupt flag in the register of the GLCDC module */
    R_GLCDC->SYSCNT.STCLR_b.L1UNDFCLR = 1U;

    /* Clear interrupt flag in the register of the NVIC module */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * The graphics plane 2 underflow detection interrupt service routine.
 *           This ISR is called when the underflow occurs in the graphics plane 2 control block. If a callback function
 *           is registered in R_GLCDC_Open(), it is called from this ISR and the DISPLAY_EVENT_GR2_UNDERFLOW event
 *           code is set as its argument.
 * @retval        none
 **********************************************************************************************************************/
void glcdc_underflow_2_isr (void)
{
    FSP_CONTEXT_SAVE

    display_callback_args_t args;
    glcdc_instance_ctrl_t * p_ctrl = (glcdc_instance_ctrl_t *) g_ctrl_blk.p_context;

    /* Call the callback function if it is registered */
    if (NULL != p_ctrl->p_callback)
    {
        args.event     = DISPLAY_EVENT_GR2_UNDERFLOW;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args);
    }

    /* Clear interrupt flag in the register of the GLCDC module */
    R_GLCDC->SYSCNT.STCLR_b.L2UNDFCLR = 1U;

    /* Clear interrupt flag in the register of the NVIC module */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Enable the glcdc interrupt.
 * @param[in]     p_instance_ctrl   Pointer to GLCDC instance struct
 * @retval        none
 **********************************************************************************************************************/
static void r_glcdc_interrupt_enable (glcdc_instance_ctrl_t * p_instance_ctrl)
{
    /* Enable the GLCDC interrupts */
    R_GLCDC->SYSCNT.DTCTEN = GLCDC_PRV_SYSCNT_DTCTEN_INIT; // VPOS interrupt is enabled in R_GLCDC_Start
    R_GLCDC->SYSCNT.INTEN  = GLCDC_PRV_SYSCNT_INTEN_INIT;

    if (p_instance_ctrl->p_cfg->line_detect_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->line_detect_irq,
                           p_instance_ctrl->p_cfg->line_detect_ipl,
                           p_instance_ctrl);
    }

    if (p_instance_ctrl->p_cfg->underflow_1_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->underflow_1_irq,
                           p_instance_ctrl->p_cfg->underflow_1_ipl,
                           p_instance_ctrl);
    }

    if (p_instance_ctrl->p_cfg->underflow_2_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->underflow_2_irq,
                           p_instance_ctrl->p_cfg->underflow_2_ipl,
                           p_instance_ctrl);
    }
}

/*******************************************************************************************************************//**
 * Calculate the pixels to be displayed on window based on the offset of the graphic layer.
 * @param[in]     p_input         The input frame buffer configuration
 * @param[in]     p_layer         The layer configuration
 * @param[in,out] p_recalculated  Pointer to store recalculated parameter
 * @param[in]     bit_size        Pointer to bit size of the color format
 * @retval        void
 **********************************************************************************************************************/
static void r_glcdc_pixel_size_recalculate (display_input_cfg_t const * const p_input,
                                            display_layer_t const * const     p_layer,
                                            glcdc_recalculated_param_t      * p_recalculated,
                                            uint16_t                          bit_size)
{
    uint16_t hpix_size_temp;
    int16_t  hpix_offset_temp;         /* Offset can be signed value */
    uint32_t base_address_temp;

    int16_t coord_x = p_layer->coordinate.x;

    if ((g_ctrl_blk.hsize >= coord_x) && (0 <= coord_x))
    {
        /* If the offset of the graphics layer is greater than or equal to zero and it is less than or
         *  equal to the size of the display window, calculate actual pixel size to display.
         */
        if ((g_ctrl_blk.hsize - (uint16_t) coord_x) < p_input->hsize)
        {
            /* Calculate actual pixel size, the pixels to be displayed is less than the display window size */
            hpix_size_temp = (uint16_t) (g_ctrl_blk.hsize - (uint16_t) coord_x);
        }
        else
        {
            /* Actual pixel size to display is same as the display window size */
            hpix_size_temp = p_input->hsize;
        }

        p_recalculated->hpix_offset = coord_x;
        base_address_temp           = (uint32_t) p_input->p_base;
    }
    else if ((0 > coord_x) && (p_input->hsize + coord_x > 0))
    {
        /* If the offset of the graphics layer is less than zero but part of the layer would still be visible, calculate
         * the actual pixel size to display. */

        /* If coordinate.x is a minus value, the layer image position can be adjusted not only by adjusting
         *  the horizontal offset but also by changing the base address of layer image. Since the base address
         *  has to be aligned to 64 bytes, we need to adjust the horizontal offset, which is the cycles from
         *  the 'internal zero' to the start cycle of active video region to achieve 1 pixel unit offset.
         *  We need to adjust the size of image to display as well.
         */
        int16_t adj_cycles = 1;
        if (bit_size >= 8)
        {
            adj_cycles = (int16_t) (GLCDC_PRV_OFFSET_MARGIN_MINUS_64PIX / ((bit_size) / 8));
        }

        if (g_ctrl_blk.back_porch.x < adj_cycles)
        {
            /* If there is not enough cycles for the offset adjustment, simply do not adjust. */
            hpix_offset_temp = 0;
            hpix_size_temp   = (uint16_t) (p_input->hsize - (((coord_x * (-1)) / adj_cycles) * adj_cycles));
        }
        else
        {
            /* If there are cycles for the offset adjustment, adjust pixel offset and size */
            hpix_offset_temp = (int16_t) (((coord_x * (-1)) % adj_cycles) * (-1));
            hpix_size_temp   = (uint16_t) ((p_input->hsize + coord_x) + ((coord_x * (-1)) % adj_cycles));
        }

        p_recalculated->hpix_offset = hpix_offset_temp;

        /* Base address must be aligned to a 64-bit address */
        uint32_t offset_address = (uint32_t) (((coord_x * (-1)) * (bit_size)) / 8);
        base_address_temp = ((uint32_t) p_input->p_base + offset_address) & (uint32_t) (~0x3F); // NOLINT(readability-magic-numbers)
    }
    else
    {
        /* If graphics layer offset is beyond the display window size, set the pixel size to display to zero */
        hpix_size_temp    = 0U;
        base_address_temp = (uint32_t) p_input->p_base;
    }

    p_recalculated->hpix_size    = hpix_size_temp;
    p_recalculated->base_address = base_address_temp;
}
