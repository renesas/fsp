/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/

/* Standard library headers */
#include <math.h>
#include <stdbool.h>
#include <float.h>
#include "bsp_api.h"
#include "rm_motor_tuner_function.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define AIDF_PRV_TWOPI                    (2 * 3.14159265F) /* 2 * pi */
#define TUNER_FUNCTION_DFT_RESULT_MULT    (2.0F)

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_dft_init
 * Description  : Initializes DFT module
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_dft_init (motor_tuner_dft_t * p_dft)
{
    p_dft->a_sum = 0;
    p_dft->b_sum = 0;
    p_dft->cnt   = 0;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_dft_sum
 * Description  : Inputs data/signal to the DFT module
 * Arguments    : angle
 *                   - The angle of signal in [rad]
 *                signal
 *                   - The value of signal
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_dft_sum (motor_tuner_dft_t * p_dft, float angle, float signal)
{
    float sin;
    float cos;

#if BSP_FEATURE_TFU_SUPPORTED
    sincosf(angle, &sin, &cos);
#else
    sin = sinf(angle);
    cos = cosf(angle);
#endif

    p_dft->a_sum += (signal * sin);
    p_dft->b_sum -= (signal * cos);
    p_dft->cnt++;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_dft_result
 * Description  : Gets the latest result of DFT module
 * Arguments    : real
 *                   - Where to store real part of the result
 *                imag
 *                   - Where to store imaginary part of the result
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_dft_result (motor_tuner_dft_t * p_dft, float * real, float * imag)
{
    *real = (p_dft->a_sum / p_dft->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
    *imag = (p_dft->b_sum / p_dft->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_dftdiff_init
 * Description  : Initializes DFT module
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_dftdiff_init (motor_tuner_dftdiff_t * p_dftdiff)
{
    p_dftdiff->a_sum[0] = 0;
    p_dftdiff->a_sum[1] = 0;
    p_dftdiff->b_sum[0] = 0;
    p_dftdiff->b_sum[1] = 0;
    p_dftdiff->cnt      = 0;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_dftdiff_sum
 * Description  : Inputs data/signal to the DFT module
 * Arguments    : angle
 *                   - The angle of signal in [rad]
 *                signal_num
 *                   - The value of signal that is numerator (input of system)
 *                signal_den
 *                   - The value of signal that is denominator (output of system)
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_dftdiff_sum (motor_tuner_dftdiff_t * p_dftdiff, float angle, float signal_num, float signal_den)
{
    float sin;
    float cos;

#if BSP_FEATURE_TFU_SUPPORTED
    sincosf(angle, &sin, &cos);
#else
    sin = sinf(angle);
    cos = cosf(angle);
#endif

    p_dftdiff->a_sum[0] += (signal_num * sin);
    p_dftdiff->b_sum[0] += (signal_num * cos);
    p_dftdiff->a_sum[1] += (signal_den * sin);
    p_dftdiff->b_sum[1] += (signal_den * cos);
    p_dftdiff->cnt++;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_dftdiff_result_div
 * Description  : Gets the numerator/denominator (input/output) result of DFT module
 * Arguments    : real
 *                   - Where to store real part of the result
 *                imag
 *                   - Where to store imaginary part of the result
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_dftdiff_result_div (motor_tuner_dftdiff_t * p_dftdiff, float * real, float * imag)
{
    float real_num;
    float real_den;
    float imag_num;
    float imag_den;
    float den;

    real_num = (p_dftdiff->a_sum[0] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
    imag_num = (p_dftdiff->b_sum[0] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
    real_den = (p_dftdiff->a_sum[1] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
    imag_den = (p_dftdiff->b_sum[1] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;

    den   = 1.0F / ((real_den * real_den) + (imag_den * imag_den));
    *real = den * ((real_num * real_den) + (imag_num * imag_den));
    *imag = den * ((imag_num * real_den) - (real_num * imag_den));
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_dftdiff_get_result_amp
 * Description  : Gets the amplitude of numerator and denominator
 * Arguments    : real
 *                   - Where to store real part of the result
 *                imag
 *                   - Where to store imaginary part of the result
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_dftdiff_get_result_amp (motor_tuner_dftdiff_t * p_dftdiff, float * amp_num, float * amp_den)
{
    float real_num;
    float real_den;
    float imag_num;
    float imag_den;

    real_num = (p_dftdiff->a_sum[0] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
    imag_num = (p_dftdiff->b_sum[0] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
    real_den = (p_dftdiff->a_sum[1] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;
    imag_den = (p_dftdiff->b_sum[1] / p_dftdiff->cnt) * TUNER_FUNCTION_DFT_RESULT_MULT;

    *amp_num = sqrtf((real_num * real_num) + (imag_num * imag_num));
    *amp_den = sqrtf((real_den * real_den) + (imag_den * imag_den));
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_sinref_init
 * Description  : Initializes sine signal function generator, the angle of sine will be reset to 0
 * Arguments    : freq
 *                   - The frequency of the output signal in [Hz]
 *                amp
 *                   - The amplitude of the output signal
 *                offset
 *                   - The offset of the output signal
 *                ctrl_period
 *                   - The sampling/control period in [s]
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_sinref_init (motor_tuner_sinref_t * p_sinref, float freq, float amp, float offset,
                                 float ctrl_period)
{
    p_sinref->freq        = freq;
    p_sinref->amp         = amp;
    p_sinref->offset      = offset;
    p_sinref->ctrl_period = ctrl_period;
    p_sinref->w_ref       = 0;
    p_sinref->angle_ref   = 0;
    p_sinref->sinref      = 0;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_sinref_set_amp
 * Description  : Set the amplitude of sine signal generator
 * Arguments    : freq
 *                   - The frequency of the output signal in [Hz]
 *                amp
 *                   - The amplitude of the output signal
 *                offset
 *                   - The offset of the output signal
 *                ctrl_period
 *                   - The sampling/control period in [s]
 * Return Value : None
 ***********************************************************************************************************************/
void rm_motor_tuner_sinref_set_amp (motor_tuner_sinref_t * p_sinref, float amp)
{
    p_sinref->amp = amp;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_sinref_generate
 * Description  : Increases one step/sample and gets the output value from the sine signal generator
 * Arguments    : None
 * Return Value : Output value
 ***********************************************************************************************************************/
float rm_motor_tuner_sinref_generate (motor_tuner_sinref_t * p_sinref)
{
    float sin;

    p_sinref->w_ref      = p_sinref->freq * AIDF_PRV_TWOPI;
    p_sinref->angle_ref += (p_sinref->w_ref * p_sinref->ctrl_period);
    if (p_sinref->angle_ref > AIDF_PRV_TWOPI)
    {
        p_sinref->angle_ref -= AIDF_PRV_TWOPI;
    }

    sin              = sinf(p_sinref->angle_ref);
    p_sinref->sinref = (p_sinref->amp * sin) + p_sinref->offset;

    return p_sinref->sinref;
}

/***********************************************************************************************************************
 * Function Name: rm_motor_tuner_sinref_get_angle
 * Description  : Gets angle of current sine signal in [rad]
 * Arguments    : None
 * Return Value : Current angle [rad]
 ***********************************************************************************************************************/
float rm_motor_tuner_sinref_get_angle (motor_tuner_sinref_t * p_sinref)
{
    return p_sinref->angle_ref;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_tuner_linear_regression
 * Description   : Linear regression, calculate slope and intercept of the linear fitting of given points
 * Arguments     : px - Start address of horizontal axis points
 *                 py - Start address of vertical axis points
 *                 n - Number of points
 *                 slope - Where to store the slope information
 *                 intercept - Where to store the intercept information
 * Return Value  : None
 ***********************************************************************************************************************/
void rm_motor_tuner_linear_regression (const float * px, const float * py, int32_t n, float * slope, float * intercept)
{
    int32_t i          = 0;
    float   x_sum      = 0.0F;
    float   y_sum      = 0.0F;
    float   cov_xy_sum = 0.0F;         /* Accumulator for calculating covariance of x and y */
    float   x_var_sum  = 0.0F;
    float   x_mean;
    float   y_mean;
    float   x_diff;
    float   y_diff;

    /* Calculate mean */
    for (i = 0; i < n; i++)
    {
        x_sum += px[i];
        y_sum += py[i];
    }

    x_mean = x_sum / (float) n;
    y_mean = y_sum / (float) n;

    /* Calculate covariance and variance of x (not divided by number of samples) */
    for (i = 0; i < n; i++)
    {
        x_diff      = px[i] - x_mean;
        y_diff      = py[i] - y_mean;
        x_var_sum  += (x_diff * x_diff);
        cov_xy_sum += (x_diff * y_diff);
    }

    /* Calculate slope and intercept */
    *slope     = cov_xy_sum / x_var_sum;
    *intercept = y_mean - (x_mean * (*slope));
}

/*******************************************************************************************************************//**
 * @brief  Compares two float values for equality within a small tolerance
 * @return true if the values are considered equal, false otherwise
 **********************************************************************************************************************/
bool rm_motor_tuner_is_equalf (float a, float b)
{
    float diff = a - b;

    return (bool) ((diff < FLT_EPSILON) && (diff > -FLT_EPSILON));
}
