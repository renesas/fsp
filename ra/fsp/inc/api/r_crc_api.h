/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CRC_API_H
#define R_CRC_API_H

/*******************************************************************************************************************//**
 * @defgroup CRC_API CRC Interface
 * @ingroup RENESAS_MONITORING_INTERFACES
 *
 * @brief Interface for cyclic redundancy checking.
 *
 * @section CRC_API_SUMMARY Summary
 * The CRC (Cyclic Redundancy Check) calculator generates CRC codes using five different polynomials including 8 bit,
 * 16 bit, and 32 bit variations. Calculation can be performed by sending data to the block using the CPU or by snooping
 * on read or write activity on one of SCI channels.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CRC Generating Polynomial Switching (GPS).  */
typedef enum e_crc_polynomial
{
    CRC_POLYNOMIAL_CRC_8 = 1,          ///< 8-bit CRC-8 (X^8 + X^2 + X + 1)
    CRC_POLYNOMIAL_CRC_16,             ///< 16-bit CRC-16 (X^16 + X^15 + X^2 + 1)
    CRC_POLYNOMIAL_CRC_CCITT,          ///< 16-bit CRC-CCITT (X^16 + X^12 + X^5 + 1)

    /** 32-bit CRC-32 (X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 + X^8 + X^7 + X^5 + X^4 + X^2 + X + 1) */
    CRC_POLYNOMIAL_CRC_32,

    /** 32-bit CRC-32C (X^32 + X^28 + X^27 + X^26 + X^25 + X^23 + X^22 + X^20 + X^19 + X^18 + X^14 + X^13 + X^11 + X^10 + X^9 + X^8 +
     * X^6 + 1) */
    CRC_POLYNOMIAL_CRC_32C,
} crc_polynomial_t;

/** CRC Calculation Switching (LMS) */
typedef enum e_crc_bit_order
{
    CRC_BIT_ORDER_LMS_LSB = 0,         ///< Generates CRC for LSB first communication
    CRC_BIT_ORDER_LMS_MSB,             ///< Generates CRC for MSB first communication
} crc_bit_order_t;

/** Snoop-On-Write/Read Switch (CRCSWR) */
typedef enum e_crc_snoop_direction
{
    CRC_SNOOP_DIRECTION_RECEIVE = 0,   ///< Snoop-on-read
    CRC_SNOOP_DIRECTION_TRANSMIT,      ///< Snoop-on-write
} crc_snoop_direction_t;

/** Structure for CRC inputs */
typedef struct st_crc_input_t
{
    uint32_t num_bytes;                // Length of input buffer
    uint32_t crc_seed;                 // CRC seed value
    void   * p_input_buffer;           // Pointer to input buffer
} crc_input_t;

/** CRC control block.  Allocate an instance specific control block to pass into the CRC API calls.
 */
typedef void crc_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_crc_cfg
{
    uint8_t          channel;          ///< Channel number
    crc_polynomial_t polynomial;       ///< CRC Generating Polynomial Switching (GPS)
    crc_bit_order_t  bit_order;        ///< CRC Calculation Switching (LMS)
    uint32_t         snoop_address;    ///< Register Snoop Address (CRCSA)
    void const     * p_extend;         ///< CRC Hardware Dependent Configuration
} crc_cfg_t;

/** CRC driver structure. General CRC functions implemented at the HAL layer will follow this API. */
typedef struct st_crc_api
{
    /** Open the CRC driver module.
     *
     * @param[in] p_ctrl               Pointer to CRC device handle.
     * @param[in] p_cfg                Pointer to a configuration structure.
     **/
    fsp_err_t (* open)(crc_ctrl_t * const p_ctrl, crc_cfg_t const * const p_cfg);

    /** Close the CRC module driver
     *
     * @param[in] p_ctrl               Pointer to CRC device handle
     * @retval FSP_SUCCESS             Configuration was successful.
     **/
    fsp_err_t (* close)(crc_ctrl_t * const p_ctrl);

    /** Return the current calculated value.
     *
     * @param[in]  p_ctrl              Pointer to CRC device handle.
     * @param[out] crc_result          The calculated value from the last CRC calculation.
     **/
    fsp_err_t (* crcResultGet)(crc_ctrl_t * const p_ctrl, uint32_t * crc_result);

    /** Configure and Enable snooping.
     *
     * @param[in] p_ctrl               Pointer to CRC device handle.
     * @param[in] crc_seed             CRC seed.
     **/
    fsp_err_t (* snoopEnable)(crc_ctrl_t * const p_ctrl, uint32_t crc_seed);

    /** Disable snooping.
     *
     * @param[in] p_ctrl               Pointer to CRC device handle.
     **/
    fsp_err_t (* snoopDisable)(crc_ctrl_t * const p_ctrl);

    /** Perform a CRC calculation on a block of data.
     *
     * @param[in]  p_ctrl         Pointer to CRC device handle.
     * @param[in]  p_crc_input    A pointer to structure for CRC inputs
     * @param[out] crc_result     The calculated value of the CRC calculation.
     **/
    fsp_err_t (* calculate)(crc_ctrl_t * const p_ctrl, crc_input_t * const p_crc_input, uint32_t * p_crc_result);
} crc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_crc_instance
{
    crc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    crc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    crc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} crc_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup CRC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
