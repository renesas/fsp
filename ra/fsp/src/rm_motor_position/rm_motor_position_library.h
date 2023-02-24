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

/* guard against multiple inclusion */
#ifndef RM_MOTOR_POSITION_LIBRARY_H
#define RM_MOTOR_POSITION_LIBRARY_H

/***********************************************************************************************************************
 * Includes <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "rm_motor_position.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Global structure
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Global function definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : motor_position_ipd_ctrl_init
 * Description   : Initialize variables when IPD control init
 * Arguments     : st_ipd - The pointer to the IPD control structure
 * Return Value  : None
 ***********************************************************************************************************************/
void motor_position_ipd_ctrl_init(motor_position_ipd_t                  * st_ipd,
                                  motor_position_ipd_lpf_t                ipd_lpf,
                                  motor_position_ipd_design_parameter_t * d_param);

/***********************************************************************************************************************
 * Function Name : motor_position_ipd_ctrl_reset
 * Description   : Reset variables when IPD control reset
 * Arguments     : st_ipd - The pointer to the IPD control structure
 * Return Value  : None
 ***********************************************************************************************************************/
void motor_position_ipd_ctrl_reset(motor_position_ipd_t * st_ipd);

/***********************************************************************************************************************
 * Function Name : motor_position_ipd_ctrl_gain_calc
 * Description   : Gain calculation for IPD control
 * Arguments     : st_motor             - The pointer to the motor parameter structure
 *                st_ipd               - The pointer to the IPD control structure
 *                f4_pos_omega         - Position Control Natural frequency for loop gain design
 *                f4_speed_ctrl_period - control period for speed loop
 * Return Value  : None
 ***********************************************************************************************************************/
void motor_position_ipd_ctrl_gain_calc(motor_position_motor_parameter_t * st_motor,
                                       motor_position_ipd_t             * st_ipd,
                                       float                              f4_pos_omega,
                                       float                              f4_speed_ctrl_period);

/***********************************************************************************************************************
 * Function Name : motor_position_ipd_speed_p_ctrl
 * Description   : Speed propotional control for IPD
 * Arguments     : st_ipd               - The pointer to the IPD control structure
 *                 f4_ref_speed_rad     - command value of speed value [rad/s]
 *                 f4_speed_rad         - speed [rad/s] (electrical)
 * Return Value  : f4_iq_ref_calc       - q axis current reference
 ***********************************************************************************************************************/
float motor_position_ipd_speed_p_ctrl(motor_position_ipd_t * st_ipd, float f4_ref_speed_rad, float f4_speed_rad);

/***********************************************************************************************************************
 * Function Name : motor_position_ipd_error_calc
 * Description   : position error calcuration for IPD
 * Arguments     : st_ipd               - The pointer to the IPD control structure
 *                 f4_pos_rad           - position [rad] (mechancal)
 *                 f4_ref_pos_rad_ctrl  - command value of position control
 * Return Value  : f4_pos_err           - position error [rad] (mechanical)
 ***********************************************************************************************************************/
float motor_position_ipd_error_calc(motor_position_ipd_t * st_ipd, float f4_pos_rad, float f4_ref_pos_rad_ctrl);

/***********************************************************************************************************************
 * Function Name : motor_position_ipd_ctrl
 * Description   : IPD control
 * Arguments     : st_ipd                - The pointer to the IPD control structure
 *                 st_motor              - The pointer to the motor parameter structure
 *                 f4_pos_err_rad        - position error [rad] (mechanical)
 *                 f4_max_speed_rad      - maximum speed [rad/s]
 * Return Value  : f4_speed_ref_calc_rad - Speed reference [rad/s]
 ***********************************************************************************************************************/
float motor_position_ipd_ctrl(motor_position_ipd_t             * st_ipd,
                              motor_position_motor_parameter_t * st_motor,
                              float                              f4_pos_err_rad,
                              float                              f4_max_speed_rad);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_POSITION_LIBRARY_H */
