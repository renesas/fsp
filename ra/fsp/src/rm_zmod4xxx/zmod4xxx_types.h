/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/**
 * @file   zmod4xxx_types.h
 * @brief  zmod4xxx types
 * @version 2.5.1
 * @author Renesas Electronics Corporation
 */

#ifndef _ZMOD4XXX_TYPES_H
 #define _ZMOD4XXX_TYPES_H

 #include <stdint.h>
 #include <stdio.h>

 #ifdef __cplusplus
extern "C" {
 #endif

 #if 1                                 // For multiple operations

/**
 * @brief Variables that describe the library version
 */
typedef struct
{
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
} algorithm_version;
 #endif

/**
 * @brief error_codes Error codes
 */
typedef enum
{
    ZMOD4XXX_OK             = 0,
    ERROR_INIT_OUT_OF_RANGE =
        -1,                            /**< The initialization value is out of range. */
    ERROR_GAS_TIMEOUT        = -2,     /**< The operation took too long. */
    ERROR_I2C                = -3,     /**< Failure in i2c communication. */
    ERROR_SENSOR_UNSUPPORTED =
        -4,                            /**< Sensor is not supported with this firmware. */
    ERROR_CONFIG_MISSING =
        -5,                            /**< There is no pointer to a valid configuration. */
    ERROR_ACCESS_CONFLICT = -6,        /**< Access Conflict. */
    ERROR_POR_EVENT       =
        -7,                            /**< “Power-on reset event. Check power supply and reset pin. */
    ERROR_CLEANING = -8,               /**< Error cleaning. */
    ERROR_NULL_PTR = -9                /**< Null pointer error. */
} zmod4xxx_err;

/**
 * @brief   function pointer type for i2c access
 * @param   [in] addr 7-bit I2C slave address of the ZMOD4xxx
 * @param   [in] reg_addr address of internal register to read/write
 * @param   [in,out] data pointer to the read/write data value
 * @param   [in] len number of bytes to read/write
 * @return  error code
 * @retval  0 success
 * @retval  "!= 0" error
 */
typedef int8_t (* zmod4xxx_i2c_ptr_t)(uint8_t addr, uint8_t reg_addr, uint8_t * data_buf, uint8_t len);

/**
 * @brief function pointer to hardware dependent delay function
 * @param [in] delay in milliseconds
 * @return none
 */
typedef void (* zmod4xxx_delay_ptr_p)(uint32_t ms);

/**
 * @brief A single data set for the configuration
 */
typedef struct
{
    uint8_t   addr;
    uint8_t   len;
    uint8_t * data_buf;
} zmod4xxx_conf_str;

/**
 * @brief Structure to hold the gas sensor module configuration.
 */
typedef struct
{
    uint8_t           start;
    zmod4xxx_conf_str h;
    zmod4xxx_conf_str d;
    zmod4xxx_conf_str m;
    zmod4xxx_conf_str s;
    zmod4xxx_conf_str r;
    uint8_t           prod_data_len;
} zmod4xxx_conf;

/**
 * @brief Device structure ZMOD4xxx
 */
typedef struct
{
    uint8_t              i2c_addr;     /**< i2c address of the sensor */
    uint8_t              config[6];    /**< configuration parameter set */
    uint16_t             mox_er;       /**< sensor specific parameter */
    uint16_t             mox_lr;       /**< sensor specific parameter */
    uint16_t             pid;          /**< product id of the sensor */
    uint8_t            * prod_data;    /**< production data */
    zmod4xxx_i2c_ptr_t   read;         /**< function pointer to i2c read */
    zmod4xxx_i2c_ptr_t   write;        /**< function pointer to i2c write */
    zmod4xxx_delay_ptr_p delay_ms;     /**< function pointer to delay function */
    zmod4xxx_conf      * init_conf;    /**< pointer to the init configuration */
    zmod4xxx_conf      * meas_conf;    /**< pointer to the measurement configuration */
} zmod4xxx_dev_t;

 #ifdef __cplusplus
}
 #endif

#endif                                 // _ZMOD4XXX_TYPES_H
