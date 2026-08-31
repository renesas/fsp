/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <math.h>
#include <bsp_api.h>
#include "rm_motor_fundlib.h"
#include "rm_motor_transform.h"

/***********************************************************************************************************************
 * Prototype definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * DEPRECATED Perform absolute coordinate transformation from UVW 3-phase system to dq-axis.
 *
 * This function transforms the UVW-phase quantities to the dq-axis values using the provided rotor angle.
 *
 * @param[in]  f_angle  Rotor angle in radians.
 * @param[in]  f_uvw    Pointer to input array containing [U, V, W] phase quantities.
 * @param[out] f_dq     Pointer to output array where [D, Q] axis values will be stored.
 **********************************************************************************************************************/
void rm_motor_transform_uvw_dq_abs (const float f_angle, const float * f_uvw, float * f_dq)
{
    float f4_temp0   = 0.0F;
    float f4_temp1   = 0.0F;
    float f4_temp2   = 0.0F;
    float f4_temp3   = 0.0F;
    float f4_u       = f_uvw[0];
    float f4_v_sub_w = f_uvw[1] - f_uvw[2];
    float f4_cos     = 0.0F;
    float f4_sin     = 0.0F;

#if BSP_FEATURE_TFU_SUPPORTED
    sincosf(f_angle, &f4_sin, &f4_cos);
#else
    f4_sin = sinf(f_angle);
    f4_cos = cosf(f_angle);
#endif

    f4_temp0 = f4_cos * (1.0F / MOTOR_FUNDLIB_SQRT_2);
    f4_temp1 = f4_sin * (1.0F / MOTOR_FUNDLIB_SQRT_2);
    f4_temp2 = MOTOR_FUNDLIB_SQRT_3 * f4_temp0;
    f4_temp3 = MOTOR_FUNDLIB_SQRT_3 * f4_temp1;
    f_dq[0]  = (f4_temp2 * f4_u) + (f4_temp1 * f4_v_sub_w);
    f_dq[1]  = ((-f4_temp3) * f4_u) + (f4_temp0 * f4_v_sub_w);
}                                      /* End of function rm_motor_transform_uvw_dq_abs */

/***********************************************************************************************************************
 * DEPRECATED Perform absolute coordinate transformation from dq-axis to UVW 3-phase system.
 *
 * This function transforms the dq-axis quantities to the three-phase UVW values using the provided rotor angle.
 *
 * @param[in]  f_angle  Rotor angle in radians.
 * @param[in]  f_dq     Pointer to input array containing [D, Q] axis values.
 * @param[out] f_uvw    Pointer to output array where [U, V, W] phase quantities will be stored.
 **********************************************************************************************************************/
void rm_motor_transform_dq_uvw_abs (const float f_angle, const float * f_dq, float * f_uvw)
{
    float f4_cos_div_sqrt3 = 0.0F;
    float f4_sin_div_sqrt3 = 0.0F;
    float f4_output_d      = 0.0F;
    float f4_output_q      = 0.0F;
    float f4_input_d       = f_dq[0];
    float f4_input_q       = f_dq[1];
    float f4_cos           = 0.0F;
    float f4_sin           = 0.0F;

#if BSP_FEATURE_TFU_SUPPORTED
    sincosf(f_angle, &f4_sin, &f4_cos);
#else
    f4_sin = sinf(f_angle);
    f4_cos = cosf(f_angle);
#endif

    f4_cos_div_sqrt3 = f4_cos * (1.0F / MOTOR_FUNDLIB_SQRT_3);
    f4_sin_div_sqrt3 = f4_sin * (1.0F / MOTOR_FUNDLIB_SQRT_3);

    f_uvw[0] = MOTOR_FUNDLIB_SQRT_2 * ((f4_cos_div_sqrt3 * f4_input_d) - (f4_sin_div_sqrt3 * f4_input_q));

    f4_output_d = ((-f4_cos_div_sqrt3) + f4_sin) * f4_input_d;
    f4_output_q = (f4_sin_div_sqrt3 + f4_cos) * f4_input_q;
    f_uvw[1]    = (f4_output_d + f4_output_q) * (1.0F / MOTOR_FUNDLIB_SQRT_2);

    f4_output_d = ((-f4_cos_div_sqrt3) - f4_sin) * f4_input_d;
    f4_output_q = (f4_sin_div_sqrt3 - f4_cos) * f4_input_q;
    f_uvw[2]    = (f4_output_d + f4_output_q) * (1.0F / MOTOR_FUNDLIB_SQRT_2);
}                                      /* End of function rm_motor_transform_dq_uvw_abs */

/***********************************************************************************************************************
 * @brief Perform absolute coordinate transformation from UVW 3-phase system to dq-axis.
 *
 * This function transforms the UVW-phase quantities to the dq-axis values using the provided sine and cosine of the rotor angle.
 *
 * @param[in]  f_sin   Sine of the rotor angle.
 * @param[in]  f_cos   Cosine of the rotor angle.
 * @param[in]  f_uvw   Pointer to input array containing [U, V, W] phase quantities.
 * @param[out] f_dq    Pointer to output array where [D, Q] axis values will be stored.
 **********************************************************************************************************************/
void rm_motor_transform_uvw_dq_abs_trigo (const float f_sin, const float f_cos, const float * f_uvw, float * f_dq)
{
    float f4_temp0   = 0.0F;
    float f4_temp1   = 0.0F;
    float f4_temp2   = 0.0F;
    float f4_temp3   = 0.0F;
    float f4_u       = f_uvw[0];
    float f4_v_sub_w = f_uvw[1] - f_uvw[2];

    f4_temp0 = f_cos * (1.0F / MOTOR_FUNDLIB_SQRT_2);
    f4_temp1 = f_sin * (1.0F / MOTOR_FUNDLIB_SQRT_2);
    f4_temp2 = MOTOR_FUNDLIB_SQRT_3 * f4_temp0;
    f4_temp3 = MOTOR_FUNDLIB_SQRT_3 * f4_temp1;
    f_dq[0]  = (f4_temp2 * f4_u) + (f4_temp1 * f4_v_sub_w);
    f_dq[1]  = ((-f4_temp3) * f4_u) + (f4_temp0 * f4_v_sub_w);
}                                      /* End of function rm_motor_transform_uvw_dq_abs_trigo */

/***********************************************************************************************************************
 * @brief Perform absolute coordinate transformation from dq-axis to UVW 3-phase system.
 *
 * This function transforms the dq-axis quantities to the three-phase UVW values using the provided sine and cosine of the rotor angle.
 *
 * @param[in]  f_sin   Sine of the rotor angle.
 * @param[in]  f_cos   Cosine of the rotor angle.
 * @param[in]  f_dq    Pointer to input array containing [D, Q] axis values.
 * @param[out] f_uvw   Pointer to output array where [U, V, W] phase quantities will be stored.
 **********************************************************************************************************************/
void rm_motor_transform_dq_uvw_abs_trigo (const float f_sin, const float f_cos, const float * f_dq, float * f_uvw)
{
    float f4_cos_div_sqrt3 = 0.0F;
    float f4_sin_div_sqrt3 = 0.0F;
    float f4_output_d      = 0.0F;
    float f4_output_q      = 0.0F;
    float f4_input_d       = f_dq[0];
    float f4_input_q       = f_dq[1];

    f4_cos_div_sqrt3 = f_cos * (1.0F / MOTOR_FUNDLIB_SQRT_3);
    f4_sin_div_sqrt3 = f_sin * (1.0F / MOTOR_FUNDLIB_SQRT_3);

    f_uvw[0] = MOTOR_FUNDLIB_SQRT_2 * ((f4_cos_div_sqrt3 * f4_input_d) - (f4_sin_div_sqrt3 * f4_input_q));

    f4_output_d = ((-f4_cos_div_sqrt3) + f_sin) * f4_input_d;
    f4_output_q = (f4_sin_div_sqrt3 + f_cos) * f4_input_q;
    f_uvw[1]    = (f4_output_d + f4_output_q) * (1.0F / MOTOR_FUNDLIB_SQRT_2);

    f4_output_d = ((-f4_cos_div_sqrt3) - f_sin) * f4_input_d;
    f4_output_q = (f4_sin_div_sqrt3 - f_cos) * f4_input_q;
    f_uvw[2]    = (f4_output_d + f4_output_q) * (1.0F / MOTOR_FUNDLIB_SQRT_2);
}                                      /* End of function rm_motor_transform_dq_uvw_abs_trigo */

/***********************************************************************************************************************
 * @brief Compute sine and cosine of a given angle.
 *
 * This function computes the sine and cosine of the provided angle using hardware TFU
 * acceleration if available, or standard math library functions otherwise.
 * The computed values can be reused across multiple coordinate transformations
 * to avoid redundant trigonometric calculations.
 *
 * @param[in]  f_angle  Angle in radians.
 * @param[out] p_sin    Pointer to output variable where sine value will be stored.
 * @param[out] p_cos    Pointer to output variable where cosine value will be stored.
 **********************************************************************************************************************/
void rm_motor_transform_sincos (const float f_angle, float * p_sin, float * p_cos)
{
#if BSP_FEATURE_TFU_SUPPORTED
    sincosf(f_angle, p_sin, p_cos);
#else
    *p_sin = sinf(f_angle);
    *p_cos = cosf(f_angle);
#endif
}
