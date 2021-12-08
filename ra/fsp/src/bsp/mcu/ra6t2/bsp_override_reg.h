/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA6T2
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA6T2) */

#ifndef BSP_OVERRIDE_REG_H
#define BSP_OVERRIDE_REG_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct                         /*!< (@ 0x40041000) R_ELC Structure                                            */
{
    union
    {
        __IOM uint8_t ELCR;            /*!< (@ 0x00000000) Event Link Controller Register                             */

        struct
        {
            uint8_t             : 7;
            __IOM uint8_t ELCON : 1;   /*!< [7..7] All Event Link Enable                                              */
        } ELCR_b;
    };
    __IM uint8_t            RESERVED[3];
    __IOM R_ELC_ELSEGR_Type ELSEGR[2]; /*!< (@ 0x00000004) Event Link Software Event Generation Register              */
    __IM uint16_t           RESERVED1[10];
    __IOM R_ELC_ELSR_Type   ELSR[30];  /*!< (@ 0x00000020) Event Link Setting Register [0..29]                        */
    __IM uint32_t           RESERVED2[18];

    union
    {
        __IOM uint32_t ELCSARA;         /*!< (@ 0x000000E0) Event Link Controller Security Attribution Register
                                         *                  A                                                          */

        struct
        {
            __IOM uint16_t ELCR    : 1; /*!< [0..0] Event Link Controller RegisterSecurity Attribution                 */
            __IOM uint16_t ELSEGR0 : 1; /*!< [1..1] Event Link Software Event Generation Register 0 Security
                                         *   Attribution                                                               */
            __IOM uint16_t ELSEGR1 : 1; /*!< [2..2] Event Link Software Event Generation Register 1 Security
                                         *   Attribution                                                               */
            uint32_t : 29;
        } ELCSARA_b;
    };

    union
    {
        __IOM uint32_t ELCSARB;        /*!< (@ 0x000000E4) Event Link Controller Security Attribution Register
                                        *                  B                                                          */

        struct
        {
            __IOM uint32_t ELSR0  : 1; /*!< [0..0] Event Link Setting Register 0Security Attribution                  */
            __IOM uint32_t ELSR1  : 1; /*!< [1..1] Event Link Setting Register 1Security Attribution                  */
            __IOM uint32_t ELSR2  : 1; /*!< [2..2] Event Link Setting Register 2Security Attribution                  */
            __IOM uint32_t ELSR3  : 1; /*!< [3..3] Event Link Setting Register 3Security Attribution                  */
            __IOM uint32_t ELSR4  : 1; /*!< [4..4] Event Link Setting Register 4Security Attribution                  */
            __IOM uint32_t ELSR5  : 1; /*!< [5..5] Event Link Setting Register 5Security Attribution                  */
            __IOM uint32_t ELSR6  : 1; /*!< [6..6] Event Link Setting Register 6Security Attribution                  */
            __IOM uint32_t ELSR7  : 1; /*!< [7..7] Event Link Setting Register 7Security Attribution                  */
            uint32_t              : 4;
            __IOM uint32_t ELSR12 : 1; /*!< [12..12] Event Link Setting Register 12Security Attribution               */
            __IOM uint32_t ELSR13 : 1; /*!< [13..13] Event Link Setting Register 13Security Attribution               */
            __IOM uint32_t ELSR14 : 1; /*!< [14..14] Event Link Setting Register 14Security Attribution               */
            __IOM uint32_t ELSR15 : 1; /*!< [15..15] Event Link Setting Register 15Security Attribution               */
            __IOM uint32_t ELSR16 : 1; /*!< [16..16] Event Link Setting Register 16Security Attribution               */
            __IOM uint32_t ELSR17 : 1; /*!< [17..17] Event Link Setting Register 17Security Attribution               */
            uint32_t              : 1;
            __IOM uint32_t ELSR19 : 1; /*!< [19..19] Event Link Setting Register 19Security Attribution               */
            __IOM uint32_t ELSR20 : 1; /*!< [20..20] Event Link Setting Register 20Security Attribution               */
            __IOM uint32_t ELSR21 : 1; /*!< [21..21] Event Link Setting Register 21Security Attribution               */
            __IOM uint32_t ELSR22 : 1; /*!< [22..22] Event Link Setting Register 22Security Attribution               */
            __IOM uint32_t ELSR23 : 1; /*!< [23..23] Event Link Setting Register 23Security Attribution               */
            __IOM uint32_t ELSR24 : 1; /*!< [24..24] Event Link Setting Register 24Security Attribution               */
            uint32_t              : 3;
            __IOM uint32_t ELSR28 : 1; /*!< [28..28] Event Link Setting Register 28Security Attribution               */
            __IOM uint32_t ELSR29 : 1; /*!< [29..29] Event Link Setting Register 29Security Attribution               */
            uint32_t              : 2;
        } ELCSARB_b;
    };
} R_ELC_Type;                          /*!< Size = 232 (0xE8)                                                         */

typedef struct                         /*!< (@ 0x4001FD00) R_PMISC Structure                                          */
{
    __IOM uint8_t PFENET;              /*!< does not exist but FSP will not build without this                        */

    __IM uint8_t  RESERVED[3];
    __IM uint32_t RESERVED1[2];

    union
    {
        __IOM uint8_t PWPR;            /*!< (@ 0x0000000C) Write-Protect Register                                     */

        struct
        {
            uint8_t             : 6;
            __IOM uint8_t PFSWE : 1;   /*!< [6..6] PmnPFS Register Write                                              */
            __IOM uint8_t B0WI  : 1;   /*!< [7..7] PFSWE Bit Write Disable                                            */
        } PWPR_b;
    };
    __IM uint8_t  RESERVED2[3];
    __IM uint32_t RESERVED3;

    union
    {
        __IOM uint8_t PWPRS;           /*!< (@ 0x00000014) Write-Protect Register for Secure                          */

        struct
        {
            uint8_t             : 6;
            __IOM uint8_t PFSWE : 1;   /*!< [6..6] PmnPFS Register Write                                              */
            __IOM uint8_t B0WI  : 1;   /*!< [7..7] PFSWE Bit Write Disable                                            */
        } PWPRS_b;
    };
    __IM uint16_t            RESERVED4;
    __IM uint32_t            RESERVED5[6];
    __IOM R_PMISC_PMSAR_Type PMSAR[15]; /*!< (@ 0x00000030) Port Security Attribution Register                        */
} R_PMISC_Type;                         /*!< Size = 108 (0x6C)                                                        */

typedef struct                          /*!< (@ 0x40084000) R_AGTW0 Structure                                          */
{
    union
    {
        __IOM uint32_t AGT;             /*!< (@ 0x00000000) AGT Counter Register                                       */

        struct
        {
            __IOM uint32_t AGT : 32;    /*!< [31..0] 16bit counter and reload registerNOTE : When 1 is written
                                         *   to the TSTOP bit in the AGTCRn register, the 16-bit counter
                                         *   is forcibly stopped and set to FFFFH.                                     */
        } AGT_b;
    };

    union
    {
        __IOM uint32_t AGTCMA;          /*!< (@ 0x00000004) AGT Compare Match A Register                               */

        struct
        {
            __IOM uint32_t AGTCMA : 32; /*!< [31..0] AGT Compare Match A data is stored.NOTE : When 1 is
                                         *   written to the TSTOP bit in the AGTCRn register, set to
                                         *   FFFFH                                                                     */
        } AGTCMA_b;
    };

    union
    {
        __IOM uint32_t AGTCMB;          /*!< (@ 0x00000008) AGT Compare Match B Register                               */

        struct
        {
            __IOM uint32_t AGTCMB : 32; /*!< [31..0] AGT Compare Match B data is stored.NOTE : When 1 is
                                         *   written to the TSTOP bit in the AGTCR register, set to
                                         *   FFFFH                                                                     */
        } AGTCMB_b;
    };

    union
    {
        __IOM uint8_t AGTCR;           /*!< (@ 0x0000000C) AGT Control Register                                       */

        struct
        {
            __IOM uint8_t TSTART : 1;  /*!< [0..0] AGT count start                                                    */
            __IM uint8_t  TCSTF  : 1;  /*!< [1..1] AGT count status flag                                              */
            __OM uint8_t  TSTOP  : 1;  /*!< [2..2] AGT count forced stop                                              */
            uint8_t              : 1;
            __IOM uint8_t TEDGF  : 1;  /*!< [4..4] Active edge judgment flag                                          */
            __IOM uint8_t TUNDF  : 1;  /*!< [5..5] Underflow flag                                                     */
            __IOM uint8_t TCMAF  : 1;  /*!< [6..6] Compare match A flag                                               */
            __IOM uint8_t TCMBF  : 1;  /*!< [7..7] Compare match B flag                                               */
        } AGTCR_b;
    };

    union
    {
        __IOM uint8_t AGTMR1;          /*!< (@ 0x0000000D) AGT Mode Register 1                                        */

        struct
        {
            __IOM uint8_t TMOD   : 3;  /*!< [2..0] Operating mode                                                     */
            __IOM uint8_t TEDGPL : 1;  /*!< [3..3] Edge polarity                                                      */
            __IOM uint8_t TCK    : 3;  /*!< [6..4] Count source                                                       */
            uint8_t              : 1;
        } AGTMR1_b;
    };

    union
    {
        __IOM uint8_t AGTMR2;          /*!< (@ 0x0000000E) AGT Mode Register 2                                        */

        struct
        {
            __IOM uint8_t CKS : 3;     /*!< [2..0] AGTLCLK/AGTSCLK count source clock frequency division
                                        *   ratio                                                                     */
            uint8_t           : 4;
            __IOM uint8_t LPM : 1;     /*!< [7..7] Low Power Mode                                                     */
        } AGTMR2_b;
    };
    __IM uint8_t RESERVED;

    union
    {
        __IOM uint8_t AGTIOC;          /*!< (@ 0x00000010) AGT I/O Control Register                                   */

        struct
        {
            __IOM uint8_t TEDGSEL : 1; /*!< [0..0] I/O polarity switchFunction varies depending on the operating
                                        *   mode.                                                                     */
            uint8_t             : 1;
            __IOM uint8_t TOE   : 1;   /*!< [2..2] AGTOn output enable                                                */
            uint8_t             : 1;
            __IOM uint8_t TIPF  : 2;   /*!< [5..4] Input filter                                                       */
            __IOM uint8_t TIOGT : 2;   /*!< [7..6] Count control                                                      */
        } AGTIOC_b;
    };

    union
    {
        __IOM uint8_t AGTISR;          /*!< (@ 0x00000011) AGT Event Pin Select Register                              */

        struct
        {
            uint8_t            : 2;
            __IOM uint8_t EEPS : 1;    /*!< [2..2] AGTEE polarty selection                                            */
            uint8_t            : 5;
        } AGTISR_b;
    };

    union
    {
        __IOM uint8_t AGTCMSR;         /*!< (@ 0x00000012) AGT Compare Match Function Select Register                 */

        struct
        {
            __IOM uint8_t TCMEA  : 1;  /*!< [0..0] Compare match A register enable                                    */
            __IOM uint8_t TOEA   : 1;  /*!< [1..1] AGTOA output enable                                                */
            __IOM uint8_t TOPOLA : 1;  /*!< [2..2] AGTOA polarity select                                              */
            uint8_t              : 1;
            __IOM uint8_t TCMEB  : 1;  /*!< [4..4] Compare match B register enable                                    */
            __IOM uint8_t TOEB   : 1;  /*!< [5..5] AGTOB output enable                                                */
            __IOM uint8_t TOPOLB : 1;  /*!< [6..6] AGTOB polarity select                                              */
            uint8_t              : 1;
        } AGTCMSR_b;
    };

    union
    {
        __IOM uint8_t AGTIOSEL;        /*!< (@ 0x000000013) AGT Pin Select Register                                   */

        struct
        {
            uint8_t            : 4;
            __IOM uint8_t TIES : 1;    /*!< [4..4] AGTIO input enable                                                 */
            uint8_t            : 3;
        } AGTIOSEL_b;
    };
} R_AGTW0_Type;                        /*!< Size = 20 (0x14)                                                          */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
