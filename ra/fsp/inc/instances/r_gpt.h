/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_GPT_H
#define R_GPT_H

/*******************************************************************************************************************//**
 * @addtogroup GPT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define GPT_CODE_VERSION_MAJOR    (1U)
#define GPT_CODE_VERSION_MINOR    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Input/Output pins, used to select which duty cycle to update in R_GPT_DutyCycleSet(). */
typedef enum e_gpt_io_pin
{
    GPT_IO_PIN_GTIOCA            = 0,  ///< GTIOCA
    GPT_IO_PIN_GTIOCB            = 1,  ///< GTIOCB
    GPT_IO_PIN_GTIOCA_AND_GTIOCB = 2,  ///< GTIOCA and GTIOCB
} gpt_io_pin_t;

/** Level of GPT pin */
typedef enum e_gpt_pin_level
{
    GPT_PIN_LEVEL_LOW  = 0,            ///< Pin level low
    GPT_PIN_LEVEL_HIGH = 1,            ///< Pin level high
} gpt_pin_level_t;

/** GPT PWM shortest pin level */
typedef enum e_gpt_shortest_level
{
    /** 1 extra PCLK in ON time. Minimum ON time will be limited to 2 PCLK raw counts. */
    GPT_SHORTEST_LEVEL_OFF = 0,

    /** 1 extra PCLK in OFF time. Minimum ON time will be limited to 1 PCLK raw counts. */
    GPT_SHORTEST_LEVEL_ON = 1,
} gpt_shortest_level_t;

/** Sources can be used to start the timer, stop the timer, count up, or count down. These enumerations represent
 * a bitmask. Multiple sources can be ORed together. */
typedef enum e_gpt_source
{
    /** No active event sources. */
    GPT_SOURCE_NONE = 0U,

    /** Action performed on GTETRGA rising edge. **/
    GPT_SOURCE_GTETRGA_RISING = (1U << 0),

    /** Action performed on GTETRGA falling edge. **/
    GPT_SOURCE_GTETRGA_FALLING = (1U << 1),

    /** Action performed on GTETRGB rising edge. **/
    GPT_SOURCE_GTETRGB_RISING = (1U << 2),

    /** Action performed on GTETRGB falling edge. **/
    GPT_SOURCE_GTETRGB_FALLING = (1U << 3),

    /** Action performed on GTETRGC rising edge. **/
    GPT_SOURCE_GTETRGC_RISING = (1U << 4),

    /** Action performed on GTETRGC falling edge. **/
    GPT_SOURCE_GTETRGC_FALLING = (1U << 5),

    /** Action performed on GTETRGB rising edge. **/
    GPT_SOURCE_GTETRGD_RISING = (1U << 6),

    /** Action performed on GTETRGB falling edge. **/
    GPT_SOURCE_GTETRGD_FALLING = (1U << 7),

    /** Action performed when GTIOCA input rises while GTIOCB is low. **/
    GPT_SOURCE_GTIOCA_RISING_WHILE_GTIOCB_LOW = (1U << 8),

    /** Action performed when GTIOCA input rises while GTIOCB is high. **/
    GPT_SOURCE_GTIOCA_RISING_WHILE_GTIOCB_HIGH = (1U << 9),

    /** Action performed when GTIOCA input falls while GTIOCB is low. **/
    GPT_SOURCE_GTIOCA_FALLING_WHILE_GTIOCB_LOW = (1U << 10),

    /** Action performed when GTIOCA input falls while GTIOCB is high. **/
    GPT_SOURCE_GTIOCA_FALLING_WHILE_GTIOCB_HIGH = (1U << 11),

    /** Action performed when GTIOCB input rises while GTIOCA is low. **/
    GPT_SOURCE_GTIOCB_RISING_WHILE_GTIOCA_LOW = (1U << 12),

    /** Action performed when GTIOCB input rises while GTIOCA is high. **/
    GPT_SOURCE_GTIOCB_RISING_WHILE_GTIOCA_HIGH = (1U << 13),

    /** Action performed when GTIOCB input falls while GTIOCA is low. **/
    GPT_SOURCE_GTIOCB_FALLING_WHILE_GTIOCA_LOW = (1U << 14),

    /** Action performed when GTIOCB input falls while GTIOCA is high. **/
    GPT_SOURCE_GTIOCB_FALLING_WHILE_GTIOCA_HIGH = (1U << 15),

    /** Action performed on ELC GPTA event. **/
    GPT_SOURCE_GPT_A = (1U << 16),

    /** Action performed on ELC GPTB event. **/
    GPT_SOURCE_GPT_B = (1U << 17),

    /** Action performed on ELC GPTC event. **/
    GPT_SOURCE_GPT_C = (1U << 18),

    /** Action performed on ELC GPTD event. **/
    GPT_SOURCE_GPT_D = (1U << 19),

    /** Action performed on ELC GPTE event. **/
    GPT_SOURCE_GPT_E = (1U << 20),

    /** Action performed on ELC GPTF event. **/
    GPT_SOURCE_GPT_F = (1U << 21),

    /** Action performed on ELC GPTG event. **/
    GPT_SOURCE_GPT_G = (1U << 22),

    /** Action performed on ELC GPTH event. **/
    GPT_SOURCE_GPT_H = (1U << 23),
} gpt_source_t;

/** Configurations for output pins. */
typedef struct s_gpt_output_pin
{
    bool            output_enabled;    ///< Set to true to enable output, false to disable output
    gpt_pin_level_t stop_level;        ///< Select a stop level from ::gpt_pin_level_t
} gpt_output_pin_t;

/** Input capture signal noise filter (debounce) setting. Only available for input signals GTIOCxA and GTIOCxB.
 *   The noise filter samples the external signal at intervals of the PCLK divided by one of the values.
 *   When 3 consecutive samples are at the same level (high or low), then that level is passed on as
 *   the observed state of the signal. See "Noise Filter Function" in the hardware manual, GPT section.
 */
typedef enum e_gpt_capture_filter
{
    GPT_CAPTURE_FILTER_NONE         = 0U, ///< None - no filtering
    GPT_CAPTURE_FILTER_PCLKD_DIV_1  = 1U, ///< PCLK/1 - fast sampling
    GPT_CAPTURE_FILTER_PCLKD_DIV_4  = 3U, ///< PCLK/4
    GPT_CAPTURE_FILTER_PCLKD_DIV_16 = 5U, ///< PCLK/16
    GPT_CAPTURE_FILTER_PCLKD_DIV_64 = 7U, ///< PCLK/64 - slow sampling
} gpt_capture_filter_t;

/** Trigger options to start A/D conversion. */
typedef enum e_gpt_adc_trigger
{
    GPT_ADC_TRIGGER_NONE                   = 0U,      ///< None - no output disable request
    GPT_ADC_TRIGGER_UP_COUNT_START_ADC_A   = 1U << 0, ///< Request A/D conversion from ADC unit 0 at up counting compare match of @ref gpt_extended_pwm_cfg_t::adc_a_compare_match
    GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A = 1U << 1, ///< Request A/D conversion from ADC unit 0 at down counting compare match of @ref gpt_extended_pwm_cfg_t::adc_a_compare_match
    GPT_ADC_TRIGGER_UP_COUNT_START_ADC_B   = 1U << 2, ///< Request A/D conversion from ADC unit 1 at up counting compare match of @ref gpt_extended_pwm_cfg_t::adc_b_compare_match
    GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_B = 1U << 3, ///< Request A/D conversion from ADC unit 1 at down counting compare match of @ref gpt_extended_pwm_cfg_t::adc_b_compare_match
} gpt_adc_trigger_t;

/** POEG channel to link to this channel. */
typedef enum e_gpt_poeg_link
{
    GPT_POEG_LINK_POEG0 = 0U,          ///< Link this GPT channel to POEG channel 0 (GTETRGA)
    GPT_POEG_LINK_POEG1 = 1U,          ///< Link this GPT channel to POEG channel 1 (GTETRGB)
    GPT_POEG_LINK_POEG2 = 2U,          ///< Link this GPT channel to POEG channel 2 (GTETRGC)
    GPT_POEG_LINK_POEG3 = 3U,          ///< Link this GPT channel to POEG channel 3 (GTETRGD)
} gpt_poeg_link_t;

/** Select trigger to send output disable request to POEG. */
typedef enum e_gpt_output_disable
{
    GPT_OUTPUT_DISABLE_NONE               = 0U,      ///< None - no output disable request
    GPT_OUTPUT_DISABLE_DEAD_TIME_ERROR    = 1U << 0, ///< Request output disable if a dead time error occurs
    GPT_OUTPUT_DISABLE_GTIOCA_GTIOCB_HIGH = 1U << 1, ///< Request output disable if GTIOCA and GTIOCB are high at the same time
    GPT_OUTPUT_DISABLE_GTIOCA_GTIOCB_LOW  = 1U << 2, ///< Request output disable if GTIOCA and GTIOCB are low at the same time
} gpt_output_disable_t;

/** Disable level options for GTIOC pins. */
typedef enum e_gpt_gtioc_disable
{
    GPT_GTIOC_DISABLE_PROHIBITED = 0U, ///< Do not allow output disable
    GPT_GTIOC_DISABLE_SET_HI_Z   = 1U, ///< Set GTIOC to high impedance when output is disabled
    GPT_GTIOC_DISABLE_LEVEL_LOW  = 2U, ///< Set GTIOC level low when output is disabled
    GPT_GTIOC_DISABLE_LEVEL_HIGH = 3U, ///< Set GTIOC level high when output is disabled
} gpt_gtioc_disable_t;

/** Trigger options to start A/D conversion. */
typedef enum e_gpt_adc_compare_match
{
    GPT_ADC_COMPARE_MATCH_ADC_A = 0U,  ///< Set A/D conversion start request value for GPT A/D converter start request A
    GPT_ADC_COMPARE_MATCH_ADC_B = 3U,  ///< Set A/D conversion start request value for GPT A/D converter start request B
} gpt_adc_compare_match_t;

/** Interrupt skipping modes */
typedef enum e_gpt_interrupt_skip_source
{
    GPT_INTERRUPT_SKIP_SOURCE_NONE               = 0U, ///< Do not skip interrupts
    GPT_INTERRUPT_SKIP_SOURCE_OVERFLOW_UNDERFLOW = 1U, ///< Count and skip overflow and underflow interrupts

    /** Count crest interrupts for interrupt skipping. Skip the number of crest and trough interrupts configured in
     *  @ref gpt_interrupt_skip_count_t. When the interrupt does fire, the trough interrupt fires before the crest
     * interrupt. */
    GPT_INTERRUPT_SKIP_SOURCE_CREST = 1U,

    /** Count trough interrupts for interrupt skipping. Skip the number of crest and trough interrupts configured in
     *  @ref gpt_interrupt_skip_count_t. When the interrupt does fire, the crest interrupt fires before the trough
     *  interrupt. */
    GPT_INTERRUPT_SKIP_SOURCE_TROUGH = 2U,
} gpt_interrupt_skip_source_t;

/** Number of interrupts to skip between events */
typedef enum e_gpt_interrupt_skip_count
{
    GPT_INTERRUPT_SKIP_COUNT_0 = 0U,   ///< Do not skip interrupts
    GPT_INTERRUPT_SKIP_COUNT_1,        ///< Skip one interrupt
    GPT_INTERRUPT_SKIP_COUNT_2,        ///< Skip two interrupts
    GPT_INTERRUPT_SKIP_COUNT_3,        ///< Skip three interrupts
    GPT_INTERRUPT_SKIP_COUNT_4,        ///< Skip four interrupts
    GPT_INTERRUPT_SKIP_COUNT_5,        ///< Skip five interrupts
    GPT_INTERRUPT_SKIP_COUNT_6,        ///< Skip six interrupts
    GPT_INTERRUPT_SKIP_COUNT_7,        ///< Skip seven interrupts
} gpt_interrupt_skip_count_t;

/** ADC events to skip during interrupt skipping */
typedef enum e_gpt_interrupt_skip_adc
{
    GPT_INTERRUPT_SKIP_ADC_NONE    = 0U, ///< Do not skip ADC events
    GPT_INTERRUPT_SKIP_ADC_A       = 1U, ///< Skip ADC A events
    GPT_INTERRUPT_SKIP_ADC_B       = 4U, ///< Skip ADC B events
    GPT_INTERRUPT_SKIP_ADC_A_AND_B = 5U, ///< Skip ADC A and B events
} gpt_interrupt_skip_adc_t;

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref timer_api_t::open is called. */
typedef struct st_gpt_instance_ctrl
{
    uint32_t            open;          // Whether or not channel is open
    const timer_cfg_t * p_cfg;         // Pointer to initial configurations
    R_GPT0_Type       * p_reg;         // Base register for this channel
    uint32_t            channel_mask;  // Channel bitmask
    timer_variant_t     variant;       // Timer variant
} gpt_instance_ctrl_t;

/** GPT extension for advanced PWM features. */
typedef struct st_gpt_extended_pwm_cfg
{
    uint8_t                     trough_ipl;             ///< Trough interrupt priority
    IRQn_Type                   trough_irq;             ///< Trough interrupt
    gpt_poeg_link_t             poeg_link;              ///< Select which POEG channel controls output disable for this GPT channel
    gpt_output_disable_t        output_disable;         ///< Select which trigger sources request output disable from POEG
    gpt_adc_trigger_t           adc_trigger;            ///< Select trigger sources to start A/D conversion
    uint32_t                    dead_time_count_up;     ///< Set a dead time value for counting up
    uint32_t                    dead_time_count_down;   ///< Set a dead time value for counting down (available on GPT32E and GPT32EH only)
    uint32_t                    adc_a_compare_match;    ///< Select the compare match value used to trigger an A/D conversion start request using ELC_EVENT_GPT<channel>_AD_TRIG_A
    uint32_t                    adc_b_compare_match;    ///< Select the compare match value used to trigger an A/D conversion start request using ELC_EVENT_GPT<channel>_AD_TRIG_B
    gpt_interrupt_skip_source_t interrupt_skip_source;  ///< Interrupt source to count for interrupt skipping
    gpt_interrupt_skip_count_t  interrupt_skip_count;   ///< Number of interrupts to skip between events
    gpt_interrupt_skip_adc_t    interrupt_skip_adc;     ///< ADC events to skip when interrupt skipping is enabled
    gpt_gtioc_disable_t         gtioca_disable_setting; ///< Select how to configure GTIOCA when output is disabled
    gpt_gtioc_disable_t         gtiocb_disable_setting; ///< Select how to configure GTIOCB when output is disabled
} gpt_extended_pwm_cfg_t;

/** GPT extension configures the output pins for GPT. */
typedef struct st_gpt_extended_cfg
{
    gpt_output_pin_t     gtioca;              ///< Configuration for GPT I/O pin A
    gpt_output_pin_t     gtiocb;              ///< Configuration for GPT I/O pin B
    gpt_shortest_level_t shortest_pwm_signal; ///< Shortest PWM signal level
    gpt_source_t         start_source;        ///< Event sources that trigger the timer to start
    gpt_source_t         stop_source;         ///< Event sources that trigger the timer to stop
    gpt_source_t         clear_source;        ///< Event sources that trigger the timer to clear
    gpt_source_t         capture_a_source;    ///< Event sources that trigger capture of GTIOCA
    gpt_source_t         capture_b_source;    ///< Event sources that trigger capture of GTIOCB

    /** Event sources that trigger a single up count. If GPT_SOURCE_NONE is selected for both count_up_source
     * and count_down_source, then the timer count source is PCLK.  */
    gpt_source_t count_up_source;

    /** Event sources that trigger a single down count. If GPT_SOURCE_NONE is selected for both count_up_source
     * and count_down_source, then the timer count source is PCLK.  */
    gpt_source_t count_down_source;

    /* Debounce filter for GTIOCxA input signal pin. */
    gpt_capture_filter_t capture_filter_gtioca;

    /* Debounce filter for GTIOCxB input signal pin. */
    gpt_capture_filter_t capture_filter_gtiocb;

    uint8_t   capture_a_ipl;                  ///< Capture A interrupt priority
    uint8_t   capture_b_ipl;                  ///< Capture B interrupt priority
    IRQn_Type capture_a_irq;                  ///< Capture A interrupt
    IRQn_Type capture_b_irq;                  ///< Capture B interrupt
    gpt_extended_pwm_cfg_t const * p_pwm_cfg; ///< Advanced PWM features, optional
} gpt_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_gpt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_GPT_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_GPT_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_GPT_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_GPT_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_GPT_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_GPT_CounterSet(timer_ctrl_t * const p_ctrl, uint32_t counter);
fsp_err_t R_GPT_OutputEnable(timer_ctrl_t * const p_ctrl, gpt_io_pin_t pin);
fsp_err_t R_GPT_OutputDisable(timer_ctrl_t * const p_ctrl, gpt_io_pin_t pin);
fsp_err_t R_GPT_AdcTriggerSet(timer_ctrl_t * const    p_ctrl,
                              gpt_adc_compare_match_t which_compare_match,
                              uint32_t                compare_match_value);
fsp_err_t R_GPT_Close(timer_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_VersionGet(fsp_version_t * const p_version);

/*******************************************************************************************************************//**
 * @} (end defgroup GPT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
