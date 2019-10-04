/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef R_CRC_API_H
#define R_CRC_API_H

/*******************************************************************************************************************//**
 * @defgroup CRC_API CRC Interface
 * @ingroup RENESAS_INTERFACES
 *
 * @brief Interface for cyclic redundancy checking.
 *
 * @section CRC_API_SUMMARY Summary
 * The CRC (Cyclic Redundancy Check) calculator generates CRC codes using five different polynomials including 8 bit,
 * 16 bit, and 32 bit variations. Calculation can be performed by sending data to the block using the CPU or by snooping
 * on read or write activity on one of 10 SCI channels.
 *
 * Implemented by:
 * - @ref CRC
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

#define CRC_API_VERSION_MAJOR    (1U)
#define CRC_API_VERSION_MINOR    (0U)

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

/* Snoop SCI register Address (lower 14 bits) */
typedef enum e_snoop_address_sci
{
    CRC_SNOOP_ADDRESS_NONE       = 0x00,
    CRC_SNOOP_ADDRESS_SCI0_TDR   = 0x003,
    CRC_SNOOP_ADDRESS_SCI1_TDR   = 0x023,
    CRC_SNOOP_ADDRESS_SCI2_TDR   = 0x043,
    CRC_SNOOP_ADDRESS_SCI3_TDR   = 0x063,
    CRC_SNOOP_ADDRESS_SCI4_TDR   = 0x083,
    CRC_SNOOP_ADDRESS_SCI5_TDR   = 0x0A3,
    CRC_SNOOP_ADDRESS_SCI6_TDR   = 0x0C3,
    CRC_SNOOP_ADDRESS_SCI7_TDR   = 0x0E3,
    CRC_SNOOP_ADDRESS_SCI8_TDR   = 0x103,
    CRC_SNOOP_ADDRESS_SCI9_TDR   = 0x123,
    CRC_SNOOP_ADDRESS_SCI0_FTDRL = 0x00F,
    CRC_SNOOP_ADDRESS_SCI1_FTDRL = 0x02F,
    CRC_SNOOP_ADDRESS_SCI2_FTDRL = 0x04F,
    CRC_SNOOP_ADDRESS_SCI3_FTDRL = 0x06F,
    CRC_SNOOP_ADDRESS_SCI4_FTDRL = 0x08F,
    CRC_SNOOP_ADDRESS_SCI5_FTDRL = 0x0AF,
    CRC_SNOOP_ADDRESS_SCI6_FTDRL = 0x0CF,
    CRC_SNOOP_ADDRESS_SCI7_FTDRL = 0x0EF,
    CRC_SNOOP_ADDRESS_SCI8_FTDRL = 0x10F,
    CRC_SNOOP_ADDRESS_SCI9_FTDRL = 0x12F,
    CRC_SNOOP_ADDRESS_SCI0_RDR   = 0x005,
    CRC_SNOOP_ADDRESS_SCI1_RDR   = 0x025,
    CRC_SNOOP_ADDRESS_SCI2_RDR   = 0x045,
    CRC_SNOOP_ADDRESS_SCI3_RDR   = 0x065,
    CRC_SNOOP_ADDRESS_SCI4_RDR   = 0x085,
    CRC_SNOOP_ADDRESS_SCI5_RDR   = 0x0A5,
    CRC_SNOOP_ADDRESS_SCI6_RDR   = 0x0C5,
    CRC_SNOOP_ADDRESS_SCI7_RDR   = 0x0E5,
    CRC_SNOOP_ADDRESS_SCI8_RDR   = 0x105,
    CRC_SNOOP_ADDRESS_SCI9_RDR   = 0x125,
    CRC_SNOOP_ADDRESS_SCI0_FRDRL = 0x011,
    CRC_SNOOP_ADDRESS_SCI1_FRDRL = 0x031,
    CRC_SNOOP_ADDRESS_SCI2_FRDRL = 0x051,
    CRC_SNOOP_ADDRESS_SCI3_FRDRL = 0x071,
    CRC_SNOOP_ADDRESS_SCI4_FRDRL = 0x091,
    CRC_SNOOP_ADDRESS_SCI5_FRDRL = 0x0B1,
    CRC_SNOOP_ADDRESS_SCI6_FRDRL = 0x0D1,
    CRC_SNOOP_ADDRESS_SCI7_FRDRL = 0x0F1,
    CRC_SNOOP_ADDRESS_SCI8_FRDRL = 0x111,
    CRC_SNOOP_ADDRESS_SCI9_FRDRL = 0x131,
} crc_snoop_address_t;

/* Structure for CRC inputs */
typedef struct st_crc_input_t
{
    uint32_t num_bytes;                // Length of input buffer
    uint32_t crc_seed;                 // CRC seed value
    void   * p_input_buffer;           // Pointer to input buffer
} crc_input_t;

/** CRC control block.  Allocate an instance specific control block to pass into the CRC API calls.
 * @par Implemented as
 * - crc_instance_ctrl_t
 */
typedef void crc_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_crc_cfg
{
    crc_polynomial_t    polynomial;    ///< CRC Generating Polynomial Switching (GPS)
    crc_bit_order_t     bit_order;     ///< CRC Calculation Switching (LMS)
    crc_snoop_address_t snoop_address; ///< Register Snoop Address (CRCSA)
    void const        * p_extend;      ///< CRC Hardware Dependent Configuration
} crc_cfg_t;

/** CRC driver structure. General CRC functions implemented at the HAL layer will follow this API. */
typedef struct st_crc_api
{
    /** Open the CRC driver module.
     * @par Implemented as
     * - R_CRC_Open()
     *
     * @param[in] p_ctrl               Pointer to CRC device handle.
     * @param[in] p_cfg                Pointer to a configuration structure.
     **/
    fsp_err_t (* open)(crc_ctrl_t * const p_ctrl, crc_cfg_t const * const p_cfg);

    /** Close the CRC module driver
     * @par Implemented as
     * - R_CRC_Close()
     *
     * @param[in] p_ctrl               Pointer to crc device handle
     * @retval FSP_SUCCESS             Configuration was successful.
     **/
    fsp_err_t (* close)(crc_ctrl_t * const p_ctrl);

    /** Return the current calculated value.
     * @par Implemented as
     * - R_CRC_CalculatedValueGet()
     *
     * @param[in]  p_ctrl              Pointer to CRC device handle.
     * @param[out] crc_result          The calculated value from the last CRC calculation.
     **/
    fsp_err_t (* crcResultGet)(crc_ctrl_t * const p_ctrl, uint32_t * crc_result);

    /** Configure and Enable snooping.
     * @par Implemented as
     * - R_CRC_SnoopEnable()
     *
     * @param[in] p_ctrl               Pointer to CRC device handle.
     * @param[in] crc_seed             CRC seed.
     **/
    fsp_err_t (* snoopEnable)(crc_ctrl_t * const p_ctrl, uint32_t crc_seed);

    /** Disable snooping.
     * @par Implemented as
     * - R_CRC_SnoopDisbale()
     *
     * @param[in] p_ctrl               Pointer to CRC device handle.
     **/
    fsp_err_t (* snoopDisable)(crc_ctrl_t * const p_ctrl);

    /** Perform a CRC calculation on a block of data.
     * @par Implemented as
     * - R_CRC_Calculate()
     *
     * @param[in]  p_ctrl         Pointer to crc device handle.
     * @param[in]  p_crc_input    A pointer to structure for CRC inputs
     * @param[out] crc_result     The calculated value of the CRC calculation.
     **/
    fsp_err_t (* calculate)(crc_ctrl_t * const p_ctrl, crc_input_t * const p_crc_input, uint32_t * p_crc_result);

    /** Get the driver version based on compile time macros.
     * @par Implemented as
     * - R_CRC_VersionGet()
     **/
    fsp_err_t (* versionGet)(fsp_version_t * version);
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
