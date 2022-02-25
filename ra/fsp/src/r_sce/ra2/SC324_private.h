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

#ifndef SC324_PRIVATE_H
#define SC324_PRIVATE_H

#include <stdint.h>
#include "SCE_module.h"

typedef struct                              /*!< SCE register structure        */
{
    volatile uint8_t REG_00H;               /*!< TRNG seed data register       */
    volatile uint8_t REG_01H;               /*!< Reserved                      */
    union
    {
        volatile uint8_t REG_02H;           /*!< TRNG seed command register 0  */
        struct
        {
            volatile         uint8_t   : 2;
            volatile uint8_t rng_start : 1; /// !< seed generation start, this bit is read as 0
            volatile uint8_t core_en   : 1; /// !< seed generation enable/disable bit
            volatile         uint8_t   : 3;
            volatile uint8_t rdrdy     : 1; /// !< indicates if seed generation completed. when core_en bit is 0, this bit is read as 0
        } TRNGSCR0;
    };
    volatile uint8_t REG_03H;               /*!< TRNG seed command register 1  */
    volatile uint8_t REG_04H;               /*!< Reserved                      */
    volatile uint8_t REG_05H;               /*!< Reserved                      */
    volatile uint8_t REG_06H;               /*!< Reserved                      */
    volatile uint8_t REG_07H;               /*!< Reserved                      */
} SCE1_TRNG_Type;

#define SCE1_TRNG    ((volatile SCE1_TRNG_Type *) SCE1_TRNG_BASE)

typedef struct
{
    union
    {
        volatile uint32_t AESMOD;               ///< AES Mode register
        struct
        {
            volatile uint32_t module_en    : 1; /// !< AES Module enable bit
            volatile          uint32_t     : 6;
            volatile uint32_t read_req_en  : 1; /// !< Enable or disable processed of data read using DTC
            volatile uint32_t write_req_en : 1; /// !< Enable or disable processing of data written using DTC
        } AESMOD_b;
    };

    union
    {
        volatile uint32_t AESCMD;                    ///< AES Command register
        struct
        {
            volatile uint32_t inverse_cipher    : 1; /// !< Select data encryption or decryption
            volatile uint32_t key_length        : 1; /// !< Select the key length
            volatile          uint32_t          : 2;
            volatile uint32_t chaining          : 2; /// !< Select the chaining mode
            volatile          uint32_t          : 2;
            volatile          uint32_t          : 2; /// !< Select output destination of an operation result
            volatile          uint32_t          : 2;
            volatile uint32_t key_select        : 1; /// !< Select the key-register
            volatile          uint32_t          : 11;
            volatile uint32_t write_ready       : 1; /// !< Select the key-register
            volatile uint32_t read_ready        : 1; /// !< Select the key-register
            volatile uint32_t com_write_ready   : 1; /// !< Select the key-register
            volatile uint32_t iv_write_ready    : 1; /// !< Select the key-register
            volatile uint32_t iv_read_ready     : 1; /// !< Select the key-register
            volatile uint32_t key_write_ready0  : 1; /// !< Select the key-register
            volatile uint32_t key_write_ready1  : 1; /// !< Select the key-register
            volatile uint32_t illegal_operation : 1; /// !< Select the key-register
        } AESCMD_b;
    };

    volatile uint32_t AESDW;                         ///< AES Data Windows register
    volatile uint32_t AESIVW;                        ///< AES IV Window register
    volatile uint32_t AESKW0;                        ///< AES Key Window 0 register
    volatile uint32_t AESKW1;                        ///< AES Key Window 1 register
} SCE1_AES_Type;

#define SCE1_AES    ((volatile SCE1_AES_Type *) SCE1_AES_BASE)

#endif                                 /* SC324_PRIVATE_H */
