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

/* =========================================================================================================================== */
/* ================                                          R_PORT0                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief I/O Ports (R_PORT0)
 */

typedef struct                         /*!< (@ 0x40040000) R_PORT0 Structure                                          */
{
    union
    {
        union
        {
            __IOM uint32_t PCNTR1;        /*!< (@ 0x00000000) Port Control Register 1                                    */

            struct
            {
                __IOM uint32_t PDR  : 16; /*!< [15..0] Pmn Direction                                                     */
                __IOM uint32_t PODR : 16; /*!< [31..16] Pmn Output Data                                                  */
            } PCNTR1_b;
        };

        struct
        {
            union
            {
                __IOM uint16_t PDR;           /*!< (@ 0x00000000) Data direction register                                    */

                struct
                {
                    __IOM uint16_t PDR0  : 1; /*!< [0..0] Pmn Direction                                                      */
                    __IOM uint16_t PDR1  : 1; /*!< [1..1] Pmn Direction                                                      */
                    __IOM uint16_t PDR2  : 1; /*!< [2..2] Pmn Direction                                                      */
                    __IOM uint16_t PDR3  : 1; /*!< [3..3] Pmn Direction                                                      */
                    __IOM uint16_t PDR4  : 1; /*!< [4..4] Pmn Direction                                                      */
                    __IOM uint16_t PDR5  : 1; /*!< [5..5] Pmn Direction                                                      */
                    __IOM uint16_t PDR6  : 1; /*!< [6..6] Pmn Direction                                                      */
                    __IOM uint16_t PDR7  : 1; /*!< [7..7] Pmn Direction                                                      */
                    __IOM uint16_t PDR8  : 1; /*!< [8..8] Pmn Direction                                                      */
                    __IOM uint16_t PDR9  : 1; /*!< [9..9] Pmn Direction                                                      */
                    __IOM uint16_t PDR10 : 1; /*!< [10..10] Pmn Direction                                                    */
                    __IOM uint16_t PDR11 : 1; /*!< [11..11] Pmn Direction                                                    */
                    __IOM uint16_t PDR12 : 1; /*!< [12..12] Pmn Direction                                                    */
                    __IOM uint16_t PDR13 : 1; /*!< [13..13] Pmn Direction                                                    */
                    __IOM uint16_t PDR14 : 1; /*!< [14..14] Pmn Direction                                                    */
                    __IOM uint16_t PDR15 : 1; /*!< [15..15] Pmn Direction                                                    */
                } PDR_b;
            };

            union
            {
                __IOM uint16_t PODR;           /*!< (@ 0x00000002) Output data register                                       */

                struct
                {
                    __IOM uint16_t PODR0  : 1; /*!< [0..0] Pmn Output Data                                                    */
                    __IOM uint16_t PODR1  : 1; /*!< [1..1] Pmn Output Data                                                    */
                    __IOM uint16_t PODR2  : 1; /*!< [2..2] Pmn Output Data                                                    */
                    __IOM uint16_t PODR3  : 1; /*!< [3..3] Pmn Output Data                                                    */
                    __IOM uint16_t PODR4  : 1; /*!< [4..4] Pmn Output Data                                                    */
                    __IOM uint16_t PODR5  : 1; /*!< [5..5] Pmn Output Data                                                    */
                    __IOM uint16_t PODR6  : 1; /*!< [6..6] Pmn Output Data                                                    */
                    __IOM uint16_t PODR7  : 1; /*!< [7..7] Pmn Output Data                                                    */
                    __IOM uint16_t PODR8  : 1; /*!< [8..8] Pmn Output Data                                                    */
                    __IOM uint16_t PODR9  : 1; /*!< [9..9] Pmn Output Data                                                    */
                    __IOM uint16_t PODR10 : 1; /*!< [10..10] Pmn Output Data                                                  */
                    __IOM uint16_t PODR11 : 1; /*!< [11..11] Pmn Output Data                                                  */
                    __IOM uint16_t PODR12 : 1; /*!< [12..12] Pmn Output Data                                                  */
                    __IOM uint16_t PODR13 : 1; /*!< [13..13] Pmn Output Data                                                  */
                    __IOM uint16_t PODR14 : 1; /*!< [14..14] Pmn Output Data                                                  */
                    __IOM uint16_t PODR15 : 1; /*!< [15..15] Pmn Output Data                                                  */
                } PODR_b;
            };
        };
    };

    union
    {
        union
        {
            __IM uint32_t PCNTR2;        /*!< (@ 0x00000004) Port Control Register 2                                    */

            struct
            {
                __IM uint32_t PIDR : 16; /*!< [15..0] Pmn Input Data                                                    */
                __IM uint32_t EIDR : 16; /*!< [31..16] Pmn Event Input Data                                             */
            } PCNTR2_b;
        };

        struct
        {
            union
            {
                __IM uint16_t PIDR;           /*!< (@ 0x00000004) Input data register                                        */

                struct
                {
                    __IM uint16_t PIDR0  : 1; /*!< [0..0] Pmn Input Data                                                     */
                    __IM uint16_t PIDR1  : 1; /*!< [1..1] Pmn Input Data                                                     */
                    __IM uint16_t PIDR2  : 1; /*!< [2..2] Pmn Input Data                                                     */
                    __IM uint16_t PIDR3  : 1; /*!< [3..3] Pmn Input Data                                                     */
                    __IM uint16_t PIDR4  : 1; /*!< [4..4] Pmn Input Data                                                     */
                    __IM uint16_t PIDR5  : 1; /*!< [5..5] Pmn Input Data                                                     */
                    __IM uint16_t PIDR6  : 1; /*!< [6..6] Pmn Input Data                                                     */
                    __IM uint16_t PIDR7  : 1; /*!< [7..7] Pmn Input Data                                                     */
                    __IM uint16_t PIDR8  : 1; /*!< [8..8] Pmn Input Data                                                     */
                    __IM uint16_t PIDR9  : 1; /*!< [9..9] Pmn Input Data                                                     */
                    __IM uint16_t PIDR10 : 1; /*!< [10..10] Pmn Input Data                                                   */
                    __IM uint16_t PIDR11 : 1; /*!< [11..11] Pmn Input Data                                                   */
                    __IM uint16_t PIDR12 : 1; /*!< [12..12] Pmn Input Data                                                   */
                    __IM uint16_t PIDR13 : 1; /*!< [13..13] Pmn Input Data                                                   */
                    __IM uint16_t PIDR14 : 1; /*!< [14..14] Pmn Input Data                                                   */
                    __IM uint16_t PIDR15 : 1; /*!< [15..15] Pmn Input Data                                                   */
                } PIDR_b;
            };

            union
            {
                __IM uint16_t EIDR;           /*!< (@ 0x00000006) Event input data register                                  */

                struct
                {
                    __IM uint16_t EIDR0  : 1; /*!< [0..0] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR1  : 1; /*!< [1..1] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR2  : 1; /*!< [2..2] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR3  : 1; /*!< [3..3] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR4  : 1; /*!< [4..4] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR5  : 1; /*!< [5..5] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR6  : 1; /*!< [6..6] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR7  : 1; /*!< [7..7] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR8  : 1; /*!< [8..8] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR9  : 1; /*!< [9..9] Pmn Event Input Data                                               */
                    __IM uint16_t EIDR10 : 1; /*!< [10..10] Pmn Event Input Data                                             */
                    __IM uint16_t EIDR11 : 1; /*!< [11..11] Pmn Event Input Data                                             */
                    __IM uint16_t EIDR12 : 1; /*!< [12..12] Pmn Event Input Data                                             */
                    __IM uint16_t EIDR13 : 1; /*!< [13..13] Pmn Event Input Data                                             */
                    __IM uint16_t EIDR14 : 1; /*!< [14..14] Pmn Event Input Data                                             */
                    __IM uint16_t EIDR15 : 1; /*!< [15..15] Pmn Event Input Data                                             */
                } EIDR_b;
            };
        };
    };

    union
    {
        union
        {
            __OM uint32_t PCNTR3;        /*!< (@ 0x00000008) Port Control Register 3                                    */

            struct
            {
                __OM uint32_t POSR : 16; /*!< [15..0] Pmn Output Set                                                    */
                __OM uint32_t PORR : 16; /*!< [31..16] Pmn Output Reset                                                 */
            } PCNTR3_b;
        };

        struct
        {
            union
            {
                __OM uint16_t POSR;           /*!< (@ 0x00000008) Output reset register                                      */

                struct
                {
                    __OM uint16_t POSR0  : 1; /*!< [0..0] Pmn Output Set                                                     */
                    __OM uint16_t POSR1  : 1; /*!< [1..1] Pmn Output Set                                                     */
                    __OM uint16_t POSR2  : 1; /*!< [2..2] Pmn Output Set                                                     */
                    __OM uint16_t POSR3  : 1; /*!< [3..3] Pmn Output Set                                                     */
                    __OM uint16_t POSR4  : 1; /*!< [4..4] Pmn Output Set                                                     */
                    __OM uint16_t POSR5  : 1; /*!< [5..5] Pmn Output Set                                                     */
                    __OM uint16_t POSR6  : 1; /*!< [6..6] Pmn Output Set                                                     */
                    __OM uint16_t POSR7  : 1; /*!< [7..7] Pmn Output Set                                                     */
                    __OM uint16_t POSR8  : 1; /*!< [8..8] Pmn Output Set                                                     */
                    __OM uint16_t POSR9  : 1; /*!< [9..9] Pmn Output Set                                                     */
                    __OM uint16_t POSR10 : 1; /*!< [10..10] Pmn Output Set                                                   */
                    __OM uint16_t POSR11 : 1; /*!< [11..11] Pmn Output Set                                                   */
                    __OM uint16_t POSR12 : 1; /*!< [12..12] Pmn Output Set                                                   */
                    __OM uint16_t POSR13 : 1; /*!< [13..13] Pmn Output Set                                                   */
                    __OM uint16_t POSR14 : 1; /*!< [14..14] Pmn Output Set                                                   */
                    __OM uint16_t POSR15 : 1; /*!< [15..15] Pmn Output Set                                                   */
                } POSR_b;
            };

            union
            {
                __OM uint16_t PORR;           /*!< (@ 0x0000000A) Output set register                                        */

                struct
                {
                    __OM uint16_t PORR0  : 1; /*!< [0..0] Pmn Output Reset                                                   */
                    __OM uint16_t PORR1  : 1; /*!< [1..1] Pmn Output Reset                                                   */
                    __OM uint16_t PORR2  : 1; /*!< [2..2] Pmn Output Reset                                                   */
                    __OM uint16_t PORR3  : 1; /*!< [3..3] Pmn Output Reset                                                   */
                    __OM uint16_t PORR4  : 1; /*!< [4..4] Pmn Output Reset                                                   */
                    __OM uint16_t PORR5  : 1; /*!< [5..5] Pmn Output Reset                                                   */
                    __OM uint16_t PORR6  : 1; /*!< [6..6] Pmn Output Reset                                                   */
                    __OM uint16_t PORR7  : 1; /*!< [7..7] Pmn Output Reset                                                   */
                    __OM uint16_t PORR8  : 1; /*!< [8..8] Pmn Output Reset                                                   */
                    __OM uint16_t PORR9  : 1; /*!< [9..9] Pmn Output Reset                                                   */
                    __OM uint16_t PORR10 : 1; /*!< [10..10] Pmn Output Reset                                                 */
                    __OM uint16_t PORR11 : 1; /*!< [11..11] Pmn Output Reset                                                 */
                    __OM uint16_t PORR12 : 1; /*!< [12..12] Pmn Output Reset                                                 */
                    __OM uint16_t PORR13 : 1; /*!< [13..13] Pmn Output Reset                                                 */
                    __OM uint16_t PORR14 : 1; /*!< [14..14] Pmn Output Reset                                                 */
                    __OM uint16_t PORR15 : 1; /*!< [15..15] Pmn Output Reset                                                 */
                } PORR_b;
            };
        };
    };

    union
    {
        union
        {
            __IOM uint32_t PCNTR4;        /*!< (@ 0x0000000C) Port Control Register 4                                    */

            struct
            {
                __IOM uint32_t EOSR : 16; /*!< [15..0] Pmn Event Output Set                                              */
                __IOM uint32_t EORR : 16; /*!< [31..16] Pmn Event Output Reset                                           */
            } PCNTR4_b;
        };

        struct
        {
            union
            {
                __IOM uint16_t EOSR;           /*!< (@ 0x0000000C) Event output reset register                                */

                struct
                {
                    __IOM uint16_t EOSR0  : 1; /*!< [0..0] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR1  : 1; /*!< [1..1] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR2  : 1; /*!< [2..2] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR3  : 1; /*!< [3..3] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR4  : 1; /*!< [4..4] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR5  : 1; /*!< [5..5] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR6  : 1; /*!< [6..6] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR7  : 1; /*!< [7..7] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR8  : 1; /*!< [8..8] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR9  : 1; /*!< [9..9] Pmn Event Output Set                                               */
                    __IOM uint16_t EOSR10 : 1; /*!< [10..10] Pmn Event Output Set                                             */
                    __IOM uint16_t EOSR11 : 1; /*!< [11..11] Pmn Event Output Set                                             */
                    __IOM uint16_t EOSR12 : 1; /*!< [12..12] Pmn Event Output Set                                             */
                    __IOM uint16_t EOSR13 : 1; /*!< [13..13] Pmn Event Output Set                                             */
                    __IOM uint16_t EOSR14 : 1; /*!< [14..14] Pmn Event Output Set                                             */
                    __IOM uint16_t EOSR15 : 1; /*!< [15..15] Pmn Event Output Set                                             */
                } EOSR_b;
            };

            union
            {
                __IOM uint16_t EORR;           /*!< (@ 0x0000000E) Event output set register                                  */

                struct
                {
                    __IOM uint16_t EORR0  : 1; /*!< [0..0] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR1  : 1; /*!< [1..1] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR2  : 1; /*!< [2..2] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR3  : 1; /*!< [3..3] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR4  : 1; /*!< [4..4] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR5  : 1; /*!< [5..5] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR6  : 1; /*!< [6..6] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR7  : 1; /*!< [7..7] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR8  : 1; /*!< [8..8] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR9  : 1; /*!< [9..9] Pmn Event Output Reset                                             */
                    __IOM uint16_t EORR10 : 1; /*!< [10..10] Pmn Event Output Reset                                           */
                    __IOM uint16_t EORR11 : 1; /*!< [11..11] Pmn Event Output Reset                                           */
                    __IOM uint16_t EORR12 : 1; /*!< [12..12] Pmn Event Output Reset                                           */
                    __IOM uint16_t EORR13 : 1; /*!< [13..13] Pmn Event Output Reset                                           */
                    __IOM uint16_t EORR14 : 1; /*!< [14..14] Pmn Event Output Reset                                           */
                    __IOM uint16_t EORR15 : 1; /*!< [15..15] Pmn Event Output Reset                                           */
                } EORR_b;
            };
        };
    };
} R_PORT0_Type;                        /*!< Size = 16 (0x10)                                                          */

/* =========================================================================================================================== */
/* ================                                Pos/Mask Peripheral Section                                ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                                           R_ELC                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  ELCR  ========================================================== */
#define R_ELC_ELCR_ELCON_Pos         (7UL)          /*!< ELCON (Bit 7)                                         */
#define R_ELC_ELCR_ELCON_Msk         (0x80UL)       /*!< ELCON (Bitfield-Mask: 0x01)                           */
/* ========================================================  ELCSARA  ======================================================== */
#define R_ELC_ELCSARA_ELCR_Pos       (0UL)          /*!< ELCR (Bit 0)                                          */
#define R_ELC_ELCSARA_ELCR_Msk       (0x1UL)        /*!< ELCR (Bitfield-Mask: 0x01)                            */
#define R_ELC_ELCSARA_ELSEGR0_Pos    (1UL)          /*!< ELSEGR0 (Bit 1)                                       */
#define R_ELC_ELCSARA_ELSEGR0_Msk    (0x2UL)        /*!< ELSEGR0 (Bitfield-Mask: 0x01)                         */
#define R_ELC_ELCSARA_ELSEGR1_Pos    (2UL)          /*!< ELSEGR1 (Bit 2)                                       */
#define R_ELC_ELCSARA_ELSEGR1_Msk    (0x4UL)        /*!< ELSEGR1 (Bitfield-Mask: 0x01)                         */
/* ========================================================  ELCSARB  ======================================================== */
#define R_ELC_ELCSARB_ELSR0_Pos      (0UL)          /*!< ELSR0 (Bit 0)                                         */
#define R_ELC_ELCSARB_ELSR0_Msk      (0x1UL)        /*!< ELSR0 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR1_Pos      (1UL)          /*!< ELSR1 (Bit 1)                                         */
#define R_ELC_ELCSARB_ELSR1_Msk      (0x2UL)        /*!< ELSR1 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR2_Pos      (2UL)          /*!< ELSR2 (Bit 2)                                         */
#define R_ELC_ELCSARB_ELSR2_Msk      (0x4UL)        /*!< ELSR2 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR3_Pos      (3UL)          /*!< ELSR3 (Bit 3)                                         */
#define R_ELC_ELCSARB_ELSR3_Msk      (0x8UL)        /*!< ELSR3 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR4_Pos      (4UL)          /*!< ELSR4 (Bit 4)                                         */
#define R_ELC_ELCSARB_ELSR4_Msk      (0x10UL)       /*!< ELSR4 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR5_Pos      (5UL)          /*!< ELSR5 (Bit 5)                                         */
#define R_ELC_ELCSARB_ELSR5_Msk      (0x20UL)       /*!< ELSR5 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR6_Pos      (6UL)          /*!< ELSR6 (Bit 6)                                         */
#define R_ELC_ELCSARB_ELSR6_Msk      (0x40UL)       /*!< ELSR6 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR7_Pos      (7UL)          /*!< ELSR7 (Bit 7)                                         */
#define R_ELC_ELCSARB_ELSR7_Msk      (0x80UL)       /*!< ELSR7 (Bitfield-Mask: 0x01)                           */
#define R_ELC_ELCSARB_ELSR12_Pos     (12UL)         /*!< ELSR12 (Bit 12)                                       */
#define R_ELC_ELCSARB_ELSR12_Msk     (0x1000UL)     /*!< ELSR12 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR13_Pos     (13UL)         /*!< ELSR13 (Bit 13)                                       */
#define R_ELC_ELCSARB_ELSR13_Msk     (0x2000UL)     /*!< ELSR13 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR14_Pos     (14UL)         /*!< ELSR14 (Bit 14)                                       */
#define R_ELC_ELCSARB_ELSR14_Msk     (0x4000UL)     /*!< ELSR14 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR15_Pos     (15UL)         /*!< ELSR15 (Bit 15)                                       */
#define R_ELC_ELCSARB_ELSR15_Msk     (0x8000UL)     /*!< ELSR15 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR16_Pos     (16UL)         /*!< ELSR16 (Bit 16)                                       */
#define R_ELC_ELCSARB_ELSR16_Msk     (0x10000UL)    /*!< ELSR16 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR17_Pos     (17UL)         /*!< ELSR17 (Bit 17)                                       */
#define R_ELC_ELCSARB_ELSR17_Msk     (0x20000UL)    /*!< ELSR17 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR19_Pos     (19UL)         /*!< ELSR19 (Bit 19)                                       */
#define R_ELC_ELCSARB_ELSR19_Msk     (0x80000UL)    /*!< ELSR19 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR20_Pos     (20UL)         /*!< ELSR20 (Bit 20)                                       */
#define R_ELC_ELCSARB_ELSR20_Msk     (0x100000UL)   /*!< ELSR20 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR21_Pos     (21UL)         /*!< ELSR21 (Bit 21)                                       */
#define R_ELC_ELCSARB_ELSR21_Msk     (0x200000UL)   /*!< ELSR21 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR22_Pos     (22UL)         /*!< ELSR22 (Bit 22)                                       */
#define R_ELC_ELCSARB_ELSR22_Msk     (0x400000UL)   /*!< ELSR22 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR23_Pos     (23UL)         /*!< ELSR23 (Bit 23)                                       */
#define R_ELC_ELCSARB_ELSR23_Msk     (0x800000UL)   /*!< ELSR23 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR24_Pos     (24UL)         /*!< ELSR24 (Bit 24)                                       */
#define R_ELC_ELCSARB_ELSR24_Msk     (0x1000000UL)  /*!< ELSR24 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR28_Pos     (28UL)         /*!< ELSR28 (Bit 28)                                       */
#define R_ELC_ELCSARB_ELSR28_Msk     (0x10000000UL) /*!< ELSR28 (Bitfield-Mask: 0x01)                          */
#define R_ELC_ELCSARB_ELSR29_Pos     (29UL)         /*!< ELSR29 (Bit 29)                                       */
#define R_ELC_ELCSARB_ELSR29_Msk     (0x20000000UL) /*!< ELSR29 (Bitfield-Mask: 0x01)                          */

/* =========================================================================================================================== */
/* ================                                           R_SYSTEM                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  SBYCR  ========================================================= */
#define R_SYSTEM_SBYCR_SSBY_Pos                   (15UL)         /*!< SSBY (Bit 15)                                         */
#define R_SYSTEM_SBYCR_SSBY_Msk                   (0x8000UL)     /*!< SSBY (Bitfield-Mask: 0x01)                            */
/* =======================================================  SCKDIVCR  ======================================================== */
#define R_SYSTEM_SCKDIVCR_PCKD_Pos                (0UL)          /*!< PCKD (Bit 0)                                          */
#define R_SYSTEM_SCKDIVCR_PCKD_Msk                (0x7UL)        /*!< PCKD (Bitfield-Mask: 0x07)                            */
#define R_SYSTEM_SCKDIVCR_PCKC_Pos                (4UL)          /*!< PCKC (Bit 4)                                          */
#define R_SYSTEM_SCKDIVCR_PCKC_Msk                (0x70UL)       /*!< PCKC (Bitfield-Mask: 0x07)                            */
#define R_SYSTEM_SCKDIVCR_PCKB_Pos                (8UL)          /*!< PCKB (Bit 8)                                          */
#define R_SYSTEM_SCKDIVCR_PCKB_Msk                (0x700UL)      /*!< PCKB (Bitfield-Mask: 0x07)                            */
#define R_SYSTEM_SCKDIVCR_PCKA_Pos                (12UL)         /*!< PCKA (Bit 12)                                         */
#define R_SYSTEM_SCKDIVCR_PCKA_Msk                (0x7000UL)     /*!< PCKA (Bitfield-Mask: 0x07)                            */
#define R_SYSTEM_SCKDIVCR_RSV_Pos                 (16UL)         /*!< RSV (Bit 16)                                          */
#define R_SYSTEM_SCKDIVCR_RSV_Msk                 (0x70000UL)    /*!< RSV (Bitfield-Mask: 0x07)                             */
#define R_SYSTEM_SCKDIVCR_ICK_Pos                 (24UL)         /*!< ICK (Bit 24)                                          */
#define R_SYSTEM_SCKDIVCR_ICK_Msk                 (0x7000000UL)  /*!< ICK (Bitfield-Mask: 0x07)                             */
#define R_SYSTEM_SCKDIVCR_FCK_Pos                 (28UL)         /*!< FCK (Bit 28)                                          */
#define R_SYSTEM_SCKDIVCR_FCK_Msk                 (0x70000000UL) /*!< FCK (Bitfield-Mask: 0x07)                             */
/* ========================================================  SCKSCR  ========================================================= */
#define R_SYSTEM_SCKSCR_CKSEL_Pos                 (0UL)          /*!< CKSEL (Bit 0)                                         */
#define R_SYSTEM_SCKSCR_CKSEL_Msk                 (0x7UL)        /*!< CKSEL (Bitfield-Mask: 0x07)                           */
/* ========================================================  PLLCCR  ========================================================= */
#define R_SYSTEM_PLLCCR_PLIDIV_Pos                (0UL)          /*!< PLIDIV (Bit 0)                                        */
#define R_SYSTEM_PLLCCR_PLIDIV_Msk                (0x3UL)        /*!< PLIDIV (Bitfield-Mask: 0x03)                          */
#define R_SYSTEM_PLLCCR_PLSRCSEL_Pos              (4UL)          /*!< PLSRCSEL (Bit 4)                                      */
#define R_SYSTEM_PLLCCR_PLSRCSEL_Msk              (0x10UL)       /*!< PLSRCSEL (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_PLLCCR_PLLMUL_Pos                (8UL)          /*!< PLLMUL (Bit 8)                                        */
#define R_SYSTEM_PLLCCR_PLLMUL_Msk                (0x3f00UL)     /*!< PLLMUL (Bitfield-Mask: 0x3f)                          */
/* =========================================================  PLLCR  ========================================================= */
#define R_SYSTEM_PLLCR_PLLSTP_Pos                 (0UL)          /*!< PLLSTP (Bit 0)                                        */
#define R_SYSTEM_PLLCR_PLLSTP_Msk                 (0x1UL)        /*!< PLLSTP (Bitfield-Mask: 0x01)                          */
/* ========================================================  MOSCCR  ========================================================= */
#define R_SYSTEM_MOSCCR_MOSTP_Pos                 (0UL)          /*!< MOSTP (Bit 0)                                         */
#define R_SYSTEM_MOSCCR_MOSTP_Msk                 (0x1UL)        /*!< MOSTP (Bitfield-Mask: 0x01)                           */
/* ========================================================  HOCOCR  ========================================================= */
#define R_SYSTEM_HOCOCR_HCSTP_Pos                 (0UL)          /*!< HCSTP (Bit 0)                                         */
#define R_SYSTEM_HOCOCR_HCSTP_Msk                 (0x1UL)        /*!< HCSTP (Bitfield-Mask: 0x01)                           */
/* ========================================================  MOCOCR  ========================================================= */
#define R_SYSTEM_MOCOCR_MCSTP_Pos                 (0UL)          /*!< MCSTP (Bit 0)                                         */
#define R_SYSTEM_MOCOCR_MCSTP_Msk                 (0x1UL)        /*!< MCSTP (Bitfield-Mask: 0x01)                           */
/* =========================================================  OSCSF  ========================================================= */
#define R_SYSTEM_OSCSF_HOCOSF_Pos                 (0UL)          /*!< HOCOSF (Bit 0)                                        */
#define R_SYSTEM_OSCSF_HOCOSF_Msk                 (0x1UL)        /*!< HOCOSF (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_OSCSF_MOSCSF_Pos                 (3UL)          /*!< MOSCSF (Bit 3)                                        */
#define R_SYSTEM_OSCSF_MOSCSF_Msk                 (0x8UL)        /*!< MOSCSF (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_OSCSF_PLLSF_Pos                  (5UL)          /*!< PLLSF (Bit 5)                                         */
#define R_SYSTEM_OSCSF_PLLSF_Msk                  (0x20UL)       /*!< PLLSF (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_OSCSF_PLL2SF_Pos                 (6UL)          /*!< PLL2SF (Bit 6)                                        */
#define R_SYSTEM_OSCSF_PLL2SF_Msk                 (0x40UL)       /*!< PLL2SF (Bitfield-Mask: 0x01)                          */
/* =========================================================  CKOCR  ========================================================= */
#define R_SYSTEM_CKOCR_CKOSEL_Pos                 (0UL)          /*!< CKOSEL (Bit 0)                                        */
#define R_SYSTEM_CKOCR_CKOSEL_Msk                 (0x7UL)        /*!< CKOSEL (Bitfield-Mask: 0x07)                          */
#define R_SYSTEM_CKOCR_CKODIV_Pos                 (4UL)          /*!< CKODIV (Bit 4)                                        */
#define R_SYSTEM_CKOCR_CKODIV_Msk                 (0x70UL)       /*!< CKODIV (Bitfield-Mask: 0x07)                          */
#define R_SYSTEM_CKOCR_CKOEN_Pos                  (7UL)          /*!< CKOEN (Bit 7)                                         */
#define R_SYSTEM_CKOCR_CKOEN_Msk                  (0x80UL)       /*!< CKOEN (Bitfield-Mask: 0x01)                           */
/* ========================================================  TRCKCR  ========================================================= */
#define R_SYSTEM_TRCKCR_TRCK_Pos                  (0UL)          /*!< TRCK (Bit 0)                                          */
#define R_SYSTEM_TRCKCR_TRCK_Msk                  (0xfUL)        /*!< TRCK (Bitfield-Mask: 0x0f)                            */
#define R_SYSTEM_TRCKCR_TRCKEN_Pos                (7UL)          /*!< TRCKEN (Bit 7)                                        */
#define R_SYSTEM_TRCKCR_TRCKEN_Msk                (0x80UL)       /*!< TRCKEN (Bitfield-Mask: 0x01)                          */
/* ========================================================  OSTDCR  ========================================================= */
#define R_SYSTEM_OSTDCR_OSTDIE_Pos                (0UL)          /*!< OSTDIE (Bit 0)                                        */
#define R_SYSTEM_OSTDCR_OSTDIE_Msk                (0x1UL)        /*!< OSTDIE (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_OSTDCR_OSTDE_Pos                 (7UL)          /*!< OSTDE (Bit 7)                                         */
#define R_SYSTEM_OSTDCR_OSTDE_Msk                 (0x80UL)       /*!< OSTDE (Bitfield-Mask: 0x01)                           */
/* ========================================================  OSTDSR  ========================================================= */
#define R_SYSTEM_OSTDSR_OSTDF_Pos                 (0UL)          /*!< OSTDF (Bit 0)                                         */
#define R_SYSTEM_OSTDSR_OSTDF_Msk                 (0x1UL)        /*!< OSTDF (Bitfield-Mask: 0x01)                           */
/* ========================================================  PLL2CCR  ======================================================== */
#define R_SYSTEM_PLL2CCR_PL2IDIV_Pos              (0UL)          /*!< PL2IDIV (Bit 0)                                       */
#define R_SYSTEM_PLL2CCR_PL2IDIV_Msk              (0x3UL)        /*!< PL2IDIV (Bitfield-Mask: 0x03)                         */
#define R_SYSTEM_PLL2CCR_PL2SRCSEL_Pos            (4UL)          /*!< PL2SRCSEL (Bit 4)                                     */
#define R_SYSTEM_PLL2CCR_PL2SRCSEL_Msk            (0x10UL)       /*!< PL2SRCSEL (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_PLL2CCR_PLL2MUL_Pos              (8UL)          /*!< PLL2MUL (Bit 8)                                       */
#define R_SYSTEM_PLL2CCR_PLL2MUL_Msk              (0x3f00UL)     /*!< PLL2MUL (Bitfield-Mask: 0x3f)                         */
/* ========================================================  PLL2CR  ========================================================= */
#define R_SYSTEM_PLL2CR_PLL2STP_Pos               (0UL)          /*!< PLL2STP (Bit 0)                                       */
#define R_SYSTEM_PLL2CR_PLL2STP_Msk               (0x1UL)        /*!< PLL2STP (Bitfield-Mask: 0x01)                         */
/* =======================================================  MOCOUTCR  ======================================================== */
#define R_SYSTEM_MOCOUTCR_MOCOUTRM_Pos            (0UL)          /*!< MOCOUTRM (Bit 0)                                      */
#define R_SYSTEM_MOCOUTCR_MOCOUTRM_Msk            (0xffUL)       /*!< MOCOUTRM (Bitfield-Mask: 0xff)                        */
/* =======================================================  HOCOUTCR  ======================================================== */
#define R_SYSTEM_HOCOUTCR_HOCOUTRM_Pos            (0UL)          /*!< HOCOUTRM (Bit 0)                                      */
#define R_SYSTEM_HOCOUTCR_HOCOUTRM_Msk            (0xffUL)       /*!< HOCOUTRM (Bitfield-Mask: 0xff)                        */
/* =====================================================  SCISPICKDIVCR  ===================================================== */
#define R_SYSTEM_SCISPICKDIVCR_SCISPICKDIV_Pos    (0UL)          /*!< SCISPICKDIV (Bit 0)                                   */
#define R_SYSTEM_SCISPICKDIVCR_SCISPICKDIV_Msk    (0x7UL)        /*!< SCISPICKDIV (Bitfield-Mask: 0x07)                     */
/* =====================================================  CANFDCKDIVCR  ====================================================== */
#define R_SYSTEM_CANFDCKDIVCR_CANFDCKDIV_Pos      (0UL)          /*!< CANFDCKDIV (Bit 0)                                    */
#define R_SYSTEM_CANFDCKDIVCR_CANFDCKDIV_Msk      (0x7UL)        /*!< CANFDCKDIV (Bitfield-Mask: 0x07)                      */
/* ======================================================  GPTCKDIVCR  ======================================================= */
#define R_SYSTEM_GPTCKDIVCR_GPTCKDIV_Pos          (0UL)          /*!< GPTCKDIV (Bit 0)                                      */
#define R_SYSTEM_GPTCKDIVCR_GPTCKDIV_Msk          (0x7UL)        /*!< GPTCKDIV (Bitfield-Mask: 0x07)                        */
/* ======================================================  IICCKDIVCR  ======================================================= */
#define R_SYSTEM_IICCKDIVCR_IICCKDIV_Pos          (0UL)          /*!< IICCKDIV (Bit 0)                                      */
#define R_SYSTEM_IICCKDIVCR_IICCKDIV_Msk          (0x7UL)        /*!< IICCKDIV (Bitfield-Mask: 0x07)                        */
/* ======================================================  SCISPICKCR  ======================================================= */
#define R_SYSTEM_SCISPICKCR_SCISPICKSEL_Pos       (0UL)          /*!< SCISPICKSEL (Bit 0)                                   */
#define R_SYSTEM_SCISPICKCR_SCISPICKSEL_Msk       (0x7UL)        /*!< SCISPICKSEL (Bitfield-Mask: 0x07)                     */
#define R_SYSTEM_SCISPICKCR_SCISPICKSREQ_Pos      (6UL)          /*!< SCISPICKSREQ (Bit 6)                                  */
#define R_SYSTEM_SCISPICKCR_SCISPICKSREQ_Msk      (0x40UL)       /*!< SCISPICKSREQ (Bitfield-Mask: 0x01)                    */
#define R_SYSTEM_SCISPICKCR_SCISPICKSRDY_Pos      (7UL)          /*!< SCISPICKSRDY (Bit 7)                                  */
#define R_SYSTEM_SCISPICKCR_SCISPICKSRDY_Msk      (0x80UL)       /*!< SCISPICKSRDY (Bitfield-Mask: 0x01)                    */
/* =======================================================  CANFDCKCR  ======================================================= */
#define R_SYSTEM_CANFDCKCR_CANFDCKSEL_Pos         (0UL)          /*!< CANFDCKSEL (Bit 0)                                    */
#define R_SYSTEM_CANFDCKCR_CANFDCKSEL_Msk         (0x7UL)        /*!< CANFDCKSEL (Bitfield-Mask: 0x07)                      */
#define R_SYSTEM_CANFDCKCR_CANFDCKSREQ_Pos        (6UL)          /*!< CANFDCKSREQ (Bit 6)                                   */
#define R_SYSTEM_CANFDCKCR_CANFDCKSREQ_Msk        (0x40UL)       /*!< CANFDCKSREQ (Bitfield-Mask: 0x01)                     */
#define R_SYSTEM_CANFDCKCR_CANFDCKSRDY_Pos        (7UL)          /*!< CANFDCKSRDY (Bit 7)                                   */
#define R_SYSTEM_CANFDCKCR_CANFDCKSRDY_Msk        (0x80UL)       /*!< CANFDCKSRDY (Bitfield-Mask: 0x01)                     */
/* ========================================================  GPTCKCR  ======================================================== */
#define R_SYSTEM_GPTCKCR_GPTCKSEL_Pos             (0UL)          /*!< GPTCKSEL (Bit 0)                                      */
#define R_SYSTEM_GPTCKCR_GPTCKSEL_Msk             (0x7UL)        /*!< GPTCKSEL (Bitfield-Mask: 0x07)                        */
#define R_SYSTEM_GPTCKCR_GPTCKSREQ_Pos            (6UL)          /*!< GPTCKSREQ (Bit 6)                                     */
#define R_SYSTEM_GPTCKCR_GPTCKSREQ_Msk            (0x40UL)       /*!< GPTCKSREQ (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_GPTCKCR_GPTCKSRDY_Pos            (7UL)          /*!< GPTCKSRDY (Bit 7)                                     */
#define R_SYSTEM_GPTCKCR_GPTCKSRDY_Msk            (0x80UL)       /*!< GPTCKSRDY (Bitfield-Mask: 0x01)                       */
/* ========================================================  IICCKCR  ======================================================== */
#define R_SYSTEM_IICCKCR_IICCKSEL_Pos             (0UL)          /*!< IICCKSEL (Bit 0)                                      */
#define R_SYSTEM_IICCKCR_IICCKSEL_Msk             (0x7UL)        /*!< IICCKSEL (Bitfield-Mask: 0x07)                        */
#define R_SYSTEM_IICCKCR_IICCKSREQ_Pos            (6UL)          /*!< IICCKSREQ (Bit 6)                                     */
#define R_SYSTEM_IICCKCR_IICCKSREQ_Msk            (0x40UL)       /*!< IICCKSREQ (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_IICCKCR_IICCKSRDY_Pos            (7UL)          /*!< IICCKSRDY (Bit 7)                                     */
#define R_SYSTEM_IICCKCR_IICCKSRDY_Msk            (0x80UL)       /*!< IICCKSRDY (Bitfield-Mask: 0x01)                       */
/* =========================================================  SNZCR  ========================================================= */
#define R_SYSTEM_SNZCR_RXDREQEN_Pos               (0UL)          /*!< RXDREQEN (Bit 0)                                      */
#define R_SYSTEM_SNZCR_RXDREQEN_Msk               (0x1UL)        /*!< RXDREQEN (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_SNZCR_SNZDTCEN_Pos               (1UL)          /*!< SNZDTCEN (Bit 1)                                      */
#define R_SYSTEM_SNZCR_SNZDTCEN_Msk               (0x2UL)        /*!< SNZDTCEN (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_SNZCR_SNZE_Pos                   (7UL)          /*!< SNZE (Bit 7)                                          */
#define R_SYSTEM_SNZCR_SNZE_Msk                   (0x80UL)       /*!< SNZE (Bitfield-Mask: 0x01)                            */
/* =======================================================  SNZEDCR0  ======================================================== */
#define R_SYSTEM_SNZEDCR0_AGTUNFED_Pos            (0UL)          /*!< AGTUNFED (Bit 0)                                      */
#define R_SYSTEM_SNZEDCR0_AGTUNFED_Msk            (0x1UL)        /*!< AGTUNFED (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_SNZEDCR0_DTCZRED_Pos             (1UL)          /*!< DTCZRED (Bit 1)                                       */
#define R_SYSTEM_SNZEDCR0_DTCZRED_Msk             (0x2UL)        /*!< DTCZRED (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_SNZEDCR0_DTCNZRED_Pos            (2UL)          /*!< DTCNZRED (Bit 2)                                      */
#define R_SYSTEM_SNZEDCR0_DTCNZRED_Msk            (0x4UL)        /*!< DTCNZRED (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_SNZEDCR0_AD0MATED_Pos            (3UL)          /*!< AD0MATED (Bit 3)                                      */
#define R_SYSTEM_SNZEDCR0_AD0MATED_Msk            (0x8UL)        /*!< AD0MATED (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_SNZEDCR0_AD1MATED_Pos            (5UL)          /*!< AD1MATED (Bit 5)                                      */
#define R_SYSTEM_SNZEDCR0_AD1MATED_Msk            (0x20UL)       /*!< AD1MATED (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_SNZEDCR0_SCI0UMTED_Pos           (7UL)          /*!< SCI0UMTED (Bit 7)                                     */
#define R_SYSTEM_SNZEDCR0_SCI0UMTED_Msk           (0x80UL)       /*!< SCI0UMTED (Bitfield-Mask: 0x01)                       */
/* =======================================================  SNZREQCR0  ======================================================= */
#define R_SYSTEM_SNZREQCR0_SNZREQEN0_Pos          (0UL)          /*!< SNZREQEN0 (Bit 0)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN0_Msk          (0x1UL)        /*!< SNZREQEN0 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN1_Pos          (1UL)          /*!< SNZREQEN1 (Bit 1)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN1_Msk          (0x2UL)        /*!< SNZREQEN1 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN2_Pos          (2UL)          /*!< SNZREQEN2 (Bit 2)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN2_Msk          (0x4UL)        /*!< SNZREQEN2 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN3_Pos          (3UL)          /*!< SNZREQEN3 (Bit 3)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN3_Msk          (0x8UL)        /*!< SNZREQEN3 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN4_Pos          (4UL)          /*!< SNZREQEN4 (Bit 4)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN4_Msk          (0x10UL)       /*!< SNZREQEN4 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN5_Pos          (5UL)          /*!< SNZREQEN5 (Bit 5)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN5_Msk          (0x20UL)       /*!< SNZREQEN5 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN6_Pos          (6UL)          /*!< SNZREQEN6 (Bit 6)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN6_Msk          (0x40UL)       /*!< SNZREQEN6 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN7_Pos          (7UL)          /*!< SNZREQEN7 (Bit 7)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN7_Msk          (0x80UL)       /*!< SNZREQEN7 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN8_Pos          (8UL)          /*!< SNZREQEN8 (Bit 8)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN8_Msk          (0x100UL)      /*!< SNZREQEN8 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN9_Pos          (9UL)          /*!< SNZREQEN9 (Bit 9)                                     */
#define R_SYSTEM_SNZREQCR0_SNZREQEN9_Msk          (0x200UL)      /*!< SNZREQEN9 (Bitfield-Mask: 0x01)                       */
#define R_SYSTEM_SNZREQCR0_SNZREQEN10_Pos         (10UL)         /*!< SNZREQEN10 (Bit 10)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN10_Msk         (0x400UL)      /*!< SNZREQEN10 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN11_Pos         (11UL)         /*!< SNZREQEN11 (Bit 11)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN11_Msk         (0x800UL)      /*!< SNZREQEN11 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN12_Pos         (12UL)         /*!< SNZREQEN12 (Bit 12)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN12_Msk         (0x1000UL)     /*!< SNZREQEN12 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN13_Pos         (13UL)         /*!< SNZREQEN13 (Bit 13)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN13_Msk         (0x2000UL)     /*!< SNZREQEN13 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN14_Pos         (14UL)         /*!< SNZREQEN14 (Bit 14)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN14_Msk         (0x4000UL)     /*!< SNZREQEN14 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN15_Pos         (15UL)         /*!< SNZREQEN15 (Bit 15)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN15_Msk         (0x8000UL)     /*!< SNZREQEN15 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN17_Pos         (17UL)         /*!< SNZREQEN17 (Bit 17)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN17_Msk         (0x20000UL)    /*!< SNZREQEN17 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN28_Pos         (28UL)         /*!< SNZREQEN28 (Bit 28)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN28_Msk         (0x10000000UL) /*!< SNZREQEN28 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN29_Pos         (29UL)         /*!< SNZREQEN29 (Bit 29)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN29_Msk         (0x20000000UL) /*!< SNZREQEN29 (Bitfield-Mask: 0x01)                      */
#define R_SYSTEM_SNZREQCR0_SNZREQEN30_Pos         (30UL)         /*!< SNZREQEN30 (Bit 30)                                   */
#define R_SYSTEM_SNZREQCR0_SNZREQEN30_Msk         (0x40000000UL) /*!< SNZREQEN30 (Bitfield-Mask: 0x01)                      */
/* =========================================================  OPCCR  ========================================================= */
#define R_SYSTEM_OPCCR_OPCM_Pos                   (0UL)          /*!< OPCM (Bit 0)                                          */
#define R_SYSTEM_OPCCR_OPCM_Msk                   (0x3UL)        /*!< OPCM (Bitfield-Mask: 0x03)                            */
#define R_SYSTEM_OPCCR_OPCMTSF_Pos                (4UL)          /*!< OPCMTSF (Bit 4)                                       */
#define R_SYSTEM_OPCCR_OPCMTSF_Msk                (0x10UL)       /*!< OPCMTSF (Bitfield-Mask: 0x01)                         */
/* =======================================================  MOSCWTCR  ======================================================== */
#define R_SYSTEM_MOSCWTCR_MSTS_Pos                (0UL)          /*!< MSTS (Bit 0)                                          */
#define R_SYSTEM_MOSCWTCR_MSTS_Msk                (0xfUL)        /*!< MSTS (Bitfield-Mask: 0x0f)                            */
/* ========================================================  RSTSR1  ========================================================= */
#define R_SYSTEM_RSTSR1_IWDTRF_Pos                (0UL)          /*!< IWDTRF (Bit 0)                                        */
#define R_SYSTEM_RSTSR1_IWDTRF_Msk                (0x1UL)        /*!< IWDTRF (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_RSTSR1_WDTRF_Pos                 (1UL)          /*!< WDTRF (Bit 1)                                         */
#define R_SYSTEM_RSTSR1_WDTRF_Msk                 (0x2UL)        /*!< WDTRF (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_RSTSR1_SWRF_Pos                  (2UL)          /*!< SWRF (Bit 2)                                          */
#define R_SYSTEM_RSTSR1_SWRF_Msk                  (0x4UL)        /*!< SWRF (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_RSTSR1_RPERF_Pos                 (8UL)          /*!< RPERF (Bit 8)                                         */
#define R_SYSTEM_RSTSR1_RPERF_Msk                 (0x100UL)      /*!< RPERF (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_RSTSR1_REERF_Pos                 (9UL)          /*!< REERF (Bit 9)                                         */
#define R_SYSTEM_RSTSR1_REERF_Msk                 (0x200UL)      /*!< REERF (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_RSTSR1_BUSMRF_Pos                (11UL)         /*!< BUSMRF (Bit 11)                                       */
#define R_SYSTEM_RSTSR1_BUSMRF_Msk                (0x800UL)      /*!< BUSMRF (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_RSTSR1_TZERF_Pos                 (13UL)         /*!< TZERF (Bit 13)                                        */
#define R_SYSTEM_RSTSR1_TZERF_Msk                 (0x2000UL)     /*!< TZERF (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_RSTSR1_CPERF_Pos                 (15UL)         /*!< CPERF (Bit 15)                                        */
#define R_SYSTEM_RSTSR1_CPERF_Msk                 (0x8000UL)     /*!< CPERF (Bitfield-Mask: 0x01)                           */
/* ========================================================  LVD1CR1  ======================================================== */
#define R_SYSTEM_LVD1CR1_IDTSEL_Pos               (0UL)          /*!< IDTSEL (Bit 0)                                        */
#define R_SYSTEM_LVD1CR1_IDTSEL_Msk               (0x3UL)        /*!< IDTSEL (Bitfield-Mask: 0x03)                          */
#define R_SYSTEM_LVD1CR1_IRQSEL_Pos               (2UL)          /*!< IRQSEL (Bit 2)                                        */
#define R_SYSTEM_LVD1CR1_IRQSEL_Msk               (0x4UL)        /*!< IRQSEL (Bitfield-Mask: 0x01)                          */
/* ========================================================  LVD1SR  ========================================================= */
#define R_SYSTEM_LVD1SR_DET_Pos                   (0UL)          /*!< DET (Bit 0)                                           */
#define R_SYSTEM_LVD1SR_DET_Msk                   (0x1UL)        /*!< DET (Bitfield-Mask: 0x01)                             */
#define R_SYSTEM_LVD1SR_MON_Pos                   (1UL)          /*!< MON (Bit 1)                                           */
#define R_SYSTEM_LVD1SR_MON_Msk                   (0x2UL)        /*!< MON (Bitfield-Mask: 0x01)                             */
/* ========================================================  LVD2CR1  ======================================================== */
#define R_SYSTEM_LVD2CR1_IDTSEL_Pos               (0UL)          /*!< IDTSEL (Bit 0)                                        */
#define R_SYSTEM_LVD2CR1_IDTSEL_Msk               (0x3UL)        /*!< IDTSEL (Bitfield-Mask: 0x03)                          */
#define R_SYSTEM_LVD2CR1_IRQSEL_Pos               (2UL)          /*!< IRQSEL (Bit 2)                                        */
#define R_SYSTEM_LVD2CR1_IRQSEL_Msk               (0x4UL)        /*!< IRQSEL (Bitfield-Mask: 0x01)                          */
/* ========================================================  LVD2SR  ========================================================= */
#define R_SYSTEM_LVD2SR_DET_Pos                   (0UL)          /*!< DET (Bit 0)                                           */
#define R_SYSTEM_LVD2SR_DET_Msk                   (0x1UL)        /*!< DET (Bitfield-Mask: 0x01)                             */
#define R_SYSTEM_LVD2SR_MON_Pos                   (1UL)          /*!< MON (Bit 1)                                           */
#define R_SYSTEM_LVD2SR_MON_Msk                   (0x2UL)        /*!< MON (Bitfield-Mask: 0x01)                             */
/* ========================================================  CGFSAR  ========================================================= */
#define R_SYSTEM_CGFSAR_NONSEC00_Pos              (0UL)          /*!< NONSEC00 (Bit 0)                                      */
#define R_SYSTEM_CGFSAR_NONSEC00_Msk              (0x1UL)        /*!< NONSEC00 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC02_Pos              (2UL)          /*!< NONSEC02 (Bit 2)                                      */
#define R_SYSTEM_CGFSAR_NONSEC02_Msk              (0x4UL)        /*!< NONSEC02 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC03_Pos              (3UL)          /*!< NONSEC03 (Bit 3)                                      */
#define R_SYSTEM_CGFSAR_NONSEC03_Msk              (0x8UL)        /*!< NONSEC03 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC04_Pos              (4UL)          /*!< NONSEC04 (Bit 4)                                      */
#define R_SYSTEM_CGFSAR_NONSEC04_Msk              (0x10UL)       /*!< NONSEC04 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC05_Pos              (5UL)          /*!< NONSEC05 (Bit 5)                                      */
#define R_SYSTEM_CGFSAR_NONSEC05_Msk              (0x20UL)       /*!< NONSEC05 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC06_Pos              (6UL)          /*!< NONSEC06 (Bit 6)                                      */
#define R_SYSTEM_CGFSAR_NONSEC06_Msk              (0x40UL)       /*!< NONSEC06 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC08_Pos              (8UL)          /*!< NONSEC08 (Bit 8)                                      */
#define R_SYSTEM_CGFSAR_NONSEC08_Msk              (0x100UL)      /*!< NONSEC08 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC09_Pos              (9UL)          /*!< NONSEC09 (Bit 9)                                      */
#define R_SYSTEM_CGFSAR_NONSEC09_Msk              (0x200UL)      /*!< NONSEC09 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC11_Pos              (11UL)         /*!< NONSEC11 (Bit 11)                                     */
#define R_SYSTEM_CGFSAR_NONSEC11_Msk              (0x800UL)      /*!< NONSEC11 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC17_Pos              (17UL)         /*!< NONSEC17 (Bit 17)                                     */
#define R_SYSTEM_CGFSAR_NONSEC17_Msk              (0x20000UL)    /*!< NONSEC17 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC18_Pos              (18UL)         /*!< NONSEC18 (Bit 18)                                     */
#define R_SYSTEM_CGFSAR_NONSEC18_Msk              (0x40000UL)    /*!< NONSEC18 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC19_Pos              (19UL)         /*!< NONSEC19 (Bit 19)                                     */
#define R_SYSTEM_CGFSAR_NONSEC19_Msk              (0x80000UL)    /*!< NONSEC19 (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_CGFSAR_NONSEC20_Pos              (20UL)         /*!< NONSEC20 (Bit 20)                                     */
#define R_SYSTEM_CGFSAR_NONSEC20_Msk              (0x100000UL)   /*!< NONSEC20 (Bitfield-Mask: 0x01)                        */
/* ========================================================  RSTSAR  ========================================================= */
#define R_SYSTEM_RSTSAR_NONSEC0_Pos               (0UL)          /*!< NONSEC0 (Bit 0)                                       */
#define R_SYSTEM_RSTSAR_NONSEC0_Msk               (0x1UL)        /*!< NONSEC0 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_RSTSAR_NONSEC1_Pos               (1UL)          /*!< NONSEC1 (Bit 1)                                       */
#define R_SYSTEM_RSTSAR_NONSEC1_Msk               (0x2UL)        /*!< NONSEC1 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_RSTSAR_NONSEC2_Pos               (2UL)          /*!< NONSEC2 (Bit 2)                                       */
#define R_SYSTEM_RSTSAR_NONSEC2_Msk               (0x4UL)        /*!< NONSEC2 (Bitfield-Mask: 0x01)                         */
/* ========================================================  LPMSAR  ========================================================= */
#define R_SYSTEM_LPMSAR_NONSEC0_Pos               (0UL)          /*!< NONSEC0 (Bit 0)                                       */
#define R_SYSTEM_LPMSAR_NONSEC0_Msk               (0x1UL)        /*!< NONSEC0 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_LPMSAR_NONSEC2_Pos               (2UL)          /*!< NONSEC2 (Bit 2)                                       */
#define R_SYSTEM_LPMSAR_NONSEC2_Msk               (0x4UL)        /*!< NONSEC2 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_LPMSAR_NONSEC4_Pos               (4UL)          /*!< NONSEC4 (Bit 4)                                       */
#define R_SYSTEM_LPMSAR_NONSEC4_Msk               (0x10UL)       /*!< NONSEC4 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_LPMSAR_NONSEC8_Pos               (8UL)          /*!< NONSEC8 (Bit 8)                                       */
#define R_SYSTEM_LPMSAR_NONSEC8_Msk               (0x100UL)      /*!< NONSEC8 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_LPMSAR_NONSEC9_Pos               (9UL)          /*!< NONSEC9 (Bit 9)                                       */
#define R_SYSTEM_LPMSAR_NONSEC9_Msk               (0x200UL)      /*!< NONSEC9 (Bitfield-Mask: 0x01)                         */
/* ========================================================  LVDSAR  ========================================================= */
#define R_SYSTEM_LVDSAR_NONSEC0_Pos               (0UL)          /*!< NONSEC0 (Bit 0)                                       */
#define R_SYSTEM_LVDSAR_NONSEC0_Msk               (0x1UL)        /*!< NONSEC0 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_LVDSAR_NONSEC1_Pos               (1UL)          /*!< NONSEC1 (Bit 1)                                       */
#define R_SYSTEM_LVDSAR_NONSEC1_Msk               (0x2UL)        /*!< NONSEC1 (Bitfield-Mask: 0x01)                         */
/* ========================================================  DPFSAR  ========================================================= */
#define R_SYSTEM_DPFSAR_DPFSA0_Pos                (0UL)          /*!< DPFSA0 (Bit 0)                                        */
#define R_SYSTEM_DPFSAR_DPFSA0_Msk                (0x1UL)        /*!< DPFSA0 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA1_Pos                (1UL)          /*!< DPFSA1 (Bit 1)                                        */
#define R_SYSTEM_DPFSAR_DPFSA1_Msk                (0x2UL)        /*!< DPFSA1 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA2_Pos                (2UL)          /*!< DPFSA2 (Bit 2)                                        */
#define R_SYSTEM_DPFSAR_DPFSA2_Msk                (0x4UL)        /*!< DPFSA2 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA3_Pos                (3UL)          /*!< DPFSA3 (Bit 3)                                        */
#define R_SYSTEM_DPFSAR_DPFSA3_Msk                (0x8UL)        /*!< DPFSA3 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA4_Pos                (4UL)          /*!< DPFSA4 (Bit 4)                                        */
#define R_SYSTEM_DPFSAR_DPFSA4_Msk                (0x10UL)       /*!< DPFSA4 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA5_Pos                (5UL)          /*!< DPFSA5 (Bit 5)                                        */
#define R_SYSTEM_DPFSAR_DPFSA5_Msk                (0x20UL)       /*!< DPFSA5 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA6_Pos                (6UL)          /*!< DPFSA6 (Bit 6)                                        */
#define R_SYSTEM_DPFSAR_DPFSA6_Msk                (0x40UL)       /*!< DPFSA6 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA7_Pos                (7UL)          /*!< DPFSA7 (Bit 7)                                        */
#define R_SYSTEM_DPFSAR_DPFSA7_Msk                (0x80UL)       /*!< DPFSA7 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA8_Pos                (8UL)          /*!< DPFSA8 (Bit 8)                                        */
#define R_SYSTEM_DPFSAR_DPFSA8_Msk                (0x100UL)      /*!< DPFSA8 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA9_Pos                (9UL)          /*!< DPFSA9 (Bit 9)                                        */
#define R_SYSTEM_DPFSAR_DPFSA9_Msk                (0x200UL)      /*!< DPFSA9 (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPFSAR_DPFSA10_Pos               (10UL)         /*!< DPFSA10 (Bit 10)                                      */
#define R_SYSTEM_DPFSAR_DPFSA10_Msk               (0x400UL)      /*!< DPFSA10 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA11_Pos               (11UL)         /*!< DPFSA11 (Bit 11)                                      */
#define R_SYSTEM_DPFSAR_DPFSA11_Msk               (0x800UL)      /*!< DPFSA11 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA12_Pos               (12UL)         /*!< DPFSA12 (Bit 12)                                      */
#define R_SYSTEM_DPFSAR_DPFSA12_Msk               (0x1000UL)     /*!< DPFSA12 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA13_Pos               (13UL)         /*!< DPFSA13 (Bit 13)                                      */
#define R_SYSTEM_DPFSAR_DPFSA13_Msk               (0x2000UL)     /*!< DPFSA13 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA14_Pos               (14UL)         /*!< DPFSA14 (Bit 14)                                      */
#define R_SYSTEM_DPFSAR_DPFSA14_Msk               (0x4000UL)     /*!< DPFSA14 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA15_Pos               (15UL)         /*!< DPFSA15 (Bit 15)                                      */
#define R_SYSTEM_DPFSAR_DPFSA15_Msk               (0x8000UL)     /*!< DPFSA15 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA16_Pos               (16UL)         /*!< DPFSA16 (Bit 16)                                      */
#define R_SYSTEM_DPFSAR_DPFSA16_Msk               (0x10000UL)    /*!< DPFSA16 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA17_Pos               (17UL)         /*!< DPFSA17 (Bit 17)                                      */
#define R_SYSTEM_DPFSAR_DPFSA17_Msk               (0x20000UL)    /*!< DPFSA17 (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPFSAR_DPFSA20_Pos               (20UL)         /*!< DPFSA20 (Bit 20)                                      */
#define R_SYSTEM_DPFSAR_DPFSA20_Msk               (0x100000UL)   /*!< DPFSA20 (Bitfield-Mask: 0x01)                         */
/* =========================================================  PRCR  ========================================================== */
#define R_SYSTEM_PRCR_PRC0_Pos                    (0UL)          /*!< PRC0 (Bit 0)                                          */
#define R_SYSTEM_PRCR_PRC0_Msk                    (0x1UL)        /*!< PRC0 (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_PRCR_PRC1_Pos                    (1UL)          /*!< PRC1 (Bit 1)                                          */
#define R_SYSTEM_PRCR_PRC1_Msk                    (0x2UL)        /*!< PRC1 (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_PRCR_PRC3_Pos                    (3UL)          /*!< PRC3 (Bit 3)                                          */
#define R_SYSTEM_PRCR_PRC3_Msk                    (0x8UL)        /*!< PRC3 (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_PRCR_PRC4_Pos                    (4UL)          /*!< PRC4 (Bit 4)                                          */
#define R_SYSTEM_PRCR_PRC4_Msk                    (0x10UL)       /*!< PRC4 (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_PRCR_PRKEY_Pos                   (8UL)          /*!< PRKEY (Bit 8)                                         */
#define R_SYSTEM_PRCR_PRKEY_Msk                   (0xff00UL)     /*!< PRKEY (Bitfield-Mask: 0xff)                           */
/* ========================================================  DPSBYCR  ======================================================== */
#define R_SYSTEM_DPSBYCR_DEEPCUT_Pos              (0UL)          /*!< DEEPCUT (Bit 0)                                       */
#define R_SYSTEM_DPSBYCR_DEEPCUT_Msk              (0x3UL)        /*!< DEEPCUT (Bitfield-Mask: 0x03)                         */
#define R_SYSTEM_DPSBYCR_IOKEEP_Pos               (6UL)          /*!< IOKEEP (Bit 6)                                        */
#define R_SYSTEM_DPSBYCR_IOKEEP_Msk               (0x40UL)       /*!< IOKEEP (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSBYCR_DPSBY_Pos                (7UL)          /*!< DPSBY (Bit 7)                                         */
#define R_SYSTEM_DPSBYCR_DPSBY_Msk                (0x80UL)       /*!< DPSBY (Bitfield-Mask: 0x01)                           */
/* ========================================================  DPSWCR  ========================================================= */
#define R_SYSTEM_DPSWCR_WTSTS_Pos                 (0UL)          /*!< WTSTS (Bit 0)                                         */
#define R_SYSTEM_DPSWCR_WTSTS_Msk                 (0x3fUL)       /*!< WTSTS (Bitfield-Mask: 0x3f)                           */
/* ========================================================  DPSIER0  ======================================================== */
#define R_SYSTEM_DPSIER0_DIRQ0E_Pos               (0UL)          /*!< DIRQ0E (Bit 0)                                        */
#define R_SYSTEM_DPSIER0_DIRQ0E_Msk               (0x1UL)        /*!< DIRQ0E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER0_DIRQ1E_Pos               (1UL)          /*!< DIRQ1E (Bit 1)                                        */
#define R_SYSTEM_DPSIER0_DIRQ1E_Msk               (0x2UL)        /*!< DIRQ1E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER0_DIRQ2E_Pos               (2UL)          /*!< DIRQ2E (Bit 2)                                        */
#define R_SYSTEM_DPSIER0_DIRQ2E_Msk               (0x4UL)        /*!< DIRQ2E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER0_DIRQ3E_Pos               (3UL)          /*!< DIRQ3E (Bit 3)                                        */
#define R_SYSTEM_DPSIER0_DIRQ3E_Msk               (0x8UL)        /*!< DIRQ3E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER0_DIRQ4E_Pos               (4UL)          /*!< DIRQ4E (Bit 4)                                        */
#define R_SYSTEM_DPSIER0_DIRQ4E_Msk               (0x10UL)       /*!< DIRQ4E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER0_DIRQ5E_Pos               (5UL)          /*!< DIRQ5E (Bit 5)                                        */
#define R_SYSTEM_DPSIER0_DIRQ5E_Msk               (0x20UL)       /*!< DIRQ5E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER0_DIRQ6E_Pos               (6UL)          /*!< DIRQ6E (Bit 6)                                        */
#define R_SYSTEM_DPSIER0_DIRQ6E_Msk               (0x40UL)       /*!< DIRQ6E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER0_DIRQ7E_Pos               (7UL)          /*!< DIRQ7E (Bit 7)                                        */
#define R_SYSTEM_DPSIER0_DIRQ7E_Msk               (0x80UL)       /*!< DIRQ7E (Bitfield-Mask: 0x01)                          */
/* ========================================================  DPSIER1  ======================================================== */
#define R_SYSTEM_DPSIER1_DIRQ8E_Pos               (0UL)          /*!< DIRQ8E (Bit 0)                                        */
#define R_SYSTEM_DPSIER1_DIRQ8E_Msk               (0x1UL)        /*!< DIRQ8E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER1_DIRQ9E_Pos               (1UL)          /*!< DIRQ9E (Bit 1)                                        */
#define R_SYSTEM_DPSIER1_DIRQ9E_Msk               (0x2UL)        /*!< DIRQ9E (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIER1_DIRQ10E_Pos              (2UL)          /*!< DIRQ10E (Bit 2)                                       */
#define R_SYSTEM_DPSIER1_DIRQ10E_Msk              (0x4UL)        /*!< DIRQ10E (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIER1_DIRQ11E_Pos              (3UL)          /*!< DIRQ11E (Bit 3)                                       */
#define R_SYSTEM_DPSIER1_DIRQ11E_Msk              (0x8UL)        /*!< DIRQ11E (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIER1_DIRQ12E_Pos              (4UL)          /*!< DIRQ12E (Bit 4)                                       */
#define R_SYSTEM_DPSIER1_DIRQ12E_Msk              (0x10UL)       /*!< DIRQ12E (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIER1_DIRQ13E_Pos              (5UL)          /*!< DIRQ13E (Bit 5)                                       */
#define R_SYSTEM_DPSIER1_DIRQ13E_Msk              (0x20UL)       /*!< DIRQ13E (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIER1_DIRQ14E_Pos              (6UL)          /*!< DIRQ14E (Bit 6)                                       */
#define R_SYSTEM_DPSIER1_DIRQ14E_Msk              (0x40UL)       /*!< DIRQ14E (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIER1_DIRQ15E_Pos              (7UL)          /*!< DIRQ15E (Bit 7)                                       */
#define R_SYSTEM_DPSIER1_DIRQ15E_Msk              (0x80UL)       /*!< DIRQ15E (Bitfield-Mask: 0x01)                         */
/* ========================================================  DPSIER2  ======================================================== */
#define R_SYSTEM_DPSIER2_DLVD1IE_Pos              (0UL)          /*!< DLVD1IE (Bit 0)                                       */
#define R_SYSTEM_DPSIER2_DLVD1IE_Msk              (0x1UL)        /*!< DLVD1IE (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIER2_DLVD2IE_Pos              (1UL)          /*!< DLVD2IE (Bit 1)                                       */
#define R_SYSTEM_DPSIER2_DLVD2IE_Msk              (0x2UL)        /*!< DLVD2IE (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIER2_DNMIE_Pos                (4UL)          /*!< DNMIE (Bit 4)                                         */
#define R_SYSTEM_DPSIER2_DNMIE_Msk                (0x10UL)       /*!< DNMIE (Bitfield-Mask: 0x01)                           */
/* ========================================================  DPSIFR0  ======================================================== */
#define R_SYSTEM_DPSIFR0_DIRQ0F_Pos               (0UL)          /*!< DIRQ0F (Bit 0)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ0F_Msk               (0x1UL)        /*!< DIRQ0F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR0_DIRQ1F_Pos               (1UL)          /*!< DIRQ1F (Bit 1)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ1F_Msk               (0x2UL)        /*!< DIRQ1F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR0_DIRQ2F_Pos               (2UL)          /*!< DIRQ2F (Bit 2)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ2F_Msk               (0x4UL)        /*!< DIRQ2F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR0_DIRQ3F_Pos               (3UL)          /*!< DIRQ3F (Bit 3)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ3F_Msk               (0x8UL)        /*!< DIRQ3F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR0_DIRQ4F_Pos               (4UL)          /*!< DIRQ4F (Bit 4)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ4F_Msk               (0x10UL)       /*!< DIRQ4F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR0_DIRQ5F_Pos               (5UL)          /*!< DIRQ5F (Bit 5)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ5F_Msk               (0x20UL)       /*!< DIRQ5F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR0_DIRQ6F_Pos               (6UL)          /*!< DIRQ6F (Bit 6)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ6F_Msk               (0x40UL)       /*!< DIRQ6F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR0_DIRQ7F_Pos               (7UL)          /*!< DIRQ7F (Bit 7)                                        */
#define R_SYSTEM_DPSIFR0_DIRQ7F_Msk               (0x80UL)       /*!< DIRQ7F (Bitfield-Mask: 0x01)                          */
/* ========================================================  DPSIFR1  ======================================================== */
#define R_SYSTEM_DPSIFR1_DIRQ8F_Pos               (0UL)          /*!< DIRQ8F (Bit 0)                                        */
#define R_SYSTEM_DPSIFR1_DIRQ8F_Msk               (0x1UL)        /*!< DIRQ8F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR1_DIRQ9F_Pos               (1UL)          /*!< DIRQ9F (Bit 1)                                        */
#define R_SYSTEM_DPSIFR1_DIRQ9F_Msk               (0x2UL)        /*!< DIRQ9F (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_DPSIFR1_DIRQ10F_Pos              (2UL)          /*!< DIRQ10F (Bit 2)                                       */
#define R_SYSTEM_DPSIFR1_DIRQ10F_Msk              (0x4UL)        /*!< DIRQ10F (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIFR1_DIRQ11F_Pos              (3UL)          /*!< DIRQ11F (Bit 3)                                       */
#define R_SYSTEM_DPSIFR1_DIRQ11F_Msk              (0x8UL)        /*!< DIRQ11F (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIFR1_DIRQ12F_Pos              (4UL)          /*!< DIRQ12F (Bit 4)                                       */
#define R_SYSTEM_DPSIFR1_DIRQ12F_Msk              (0x10UL)       /*!< DIRQ12F (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIFR1_DIRQ13F_Pos              (5UL)          /*!< DIRQ13F (Bit 5)                                       */
#define R_SYSTEM_DPSIFR1_DIRQ13F_Msk              (0x20UL)       /*!< DIRQ13F (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIFR1_DIRQ14F_Pos              (6UL)          /*!< DIRQ14F (Bit 6)                                       */
#define R_SYSTEM_DPSIFR1_DIRQ14F_Msk              (0x40UL)       /*!< DIRQ14F (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIFR1_DIRQ15F_Pos              (7UL)          /*!< DIRQ15F (Bit 7)                                       */
#define R_SYSTEM_DPSIFR1_DIRQ15F_Msk              (0x80UL)       /*!< DIRQ15F (Bitfield-Mask: 0x01)                         */
/* ========================================================  DPSIFR2  ======================================================== */
#define R_SYSTEM_DPSIFR2_DLVD1IF_Pos              (0UL)          /*!< DLVD1IF (Bit 0)                                       */
#define R_SYSTEM_DPSIFR2_DLVD1IF_Msk              (0x1UL)        /*!< DLVD1IF (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIFR2_DLVD2IF_Pos              (1UL)          /*!< DLVD2IF (Bit 1)                                       */
#define R_SYSTEM_DPSIFR2_DLVD2IF_Msk              (0x2UL)        /*!< DLVD2IF (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIFR2_DNMIF_Pos                (4UL)          /*!< DNMIF (Bit 4)                                         */
#define R_SYSTEM_DPSIFR2_DNMIF_Msk                (0x10UL)       /*!< DNMIF (Bitfield-Mask: 0x01)                           */
/* =======================================================  DPSIEGR0  ======================================================== */
#define R_SYSTEM_DPSIEGR0_DIRQ0EG_Pos             (0UL)          /*!< DIRQ0EG (Bit 0)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ0EG_Msk             (0x1UL)        /*!< DIRQ0EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR0_DIRQ1EG_Pos             (1UL)          /*!< DIRQ1EG (Bit 1)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ1EG_Msk             (0x2UL)        /*!< DIRQ1EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR0_DIRQ2EG_Pos             (2UL)          /*!< DIRQ2EG (Bit 2)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ2EG_Msk             (0x4UL)        /*!< DIRQ2EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR0_DIRQ3EG_Pos             (3UL)          /*!< DIRQ3EG (Bit 3)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ3EG_Msk             (0x8UL)        /*!< DIRQ3EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR0_DIRQ4EG_Pos             (4UL)          /*!< DIRQ4EG (Bit 4)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ4EG_Msk             (0x10UL)       /*!< DIRQ4EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR0_DIRQ5EG_Pos             (5UL)          /*!< DIRQ5EG (Bit 5)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ5EG_Msk             (0x20UL)       /*!< DIRQ5EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR0_DIRQ6EG_Pos             (6UL)          /*!< DIRQ6EG (Bit 6)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ6EG_Msk             (0x40UL)       /*!< DIRQ6EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR0_DIRQ7EG_Pos             (7UL)          /*!< DIRQ7EG (Bit 7)                                       */
#define R_SYSTEM_DPSIEGR0_DIRQ7EG_Msk             (0x80UL)       /*!< DIRQ7EG (Bitfield-Mask: 0x01)                         */
/* =======================================================  DPSIEGR1  ======================================================== */
#define R_SYSTEM_DPSIEGR1_DIRQ8EG_Pos             (0UL)          /*!< DIRQ8EG (Bit 0)                                       */
#define R_SYSTEM_DPSIEGR1_DIRQ8EG_Msk             (0x1UL)        /*!< DIRQ8EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR1_DIRQ9EG_Pos             (1UL)          /*!< DIRQ9EG (Bit 1)                                       */
#define R_SYSTEM_DPSIEGR1_DIRQ9EG_Msk             (0x2UL)        /*!< DIRQ9EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR1_DIRQ10EG_Pos            (2UL)          /*!< DIRQ10EG (Bit 2)                                      */
#define R_SYSTEM_DPSIEGR1_DIRQ10EG_Msk            (0x4UL)        /*!< DIRQ10EG (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_DPSIEGR1_DIRQ11EG_Pos            (3UL)          /*!< DIRQ11EG (Bit 3)                                      */
#define R_SYSTEM_DPSIEGR1_DIRQ11EG_Msk            (0x8UL)        /*!< DIRQ11EG (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_DPSIEGR1_DIRQ12EG_Pos            (4UL)          /*!< DIRQ12EG (Bit 4)                                      */
#define R_SYSTEM_DPSIEGR1_DIRQ12EG_Msk            (0x10UL)       /*!< DIRQ12EG (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_DPSIEGR1_DIRQ13EG_Pos            (5UL)          /*!< DIRQ13EG (Bit 5)                                      */
#define R_SYSTEM_DPSIEGR1_DIRQ13EG_Msk            (0x20UL)       /*!< DIRQ13EG (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_DPSIEGR1_DIRQ14EG_Pos            (6UL)          /*!< DIRQ14EG (Bit 6)                                      */
#define R_SYSTEM_DPSIEGR1_DIRQ14EG_Msk            (0x40UL)       /*!< DIRQ14EG (Bitfield-Mask: 0x01)                        */
#define R_SYSTEM_DPSIEGR1_DIRQ15EG_Pos            (7UL)          /*!< DIRQ15EG (Bit 7)                                      */
#define R_SYSTEM_DPSIEGR1_DIRQ15EG_Msk            (0x80UL)       /*!< DIRQ15EG (Bitfield-Mask: 0x01)                        */
/* =======================================================  DPSIEGR2  ======================================================== */
#define R_SYSTEM_DPSIEGR2_DLVD1EG_Pos             (0UL)          /*!< DLVD1EG (Bit 0)                                       */
#define R_SYSTEM_DPSIEGR2_DLVD1EG_Msk             (0x1UL)        /*!< DLVD1EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR2_DLVD2EG_Pos             (1UL)          /*!< DLVD2EG (Bit 1)                                       */
#define R_SYSTEM_DPSIEGR2_DLVD2EG_Msk             (0x2UL)        /*!< DLVD2EG (Bitfield-Mask: 0x01)                         */
#define R_SYSTEM_DPSIEGR2_DNMIEG_Pos              (4UL)          /*!< DNMIEG (Bit 4)                                        */
#define R_SYSTEM_DPSIEGR2_DNMIEG_Msk              (0x10UL)       /*!< DNMIEG (Bitfield-Mask: 0x01)                          */
/* ========================================================  SYOCDCR  ======================================================== */
#define R_SYSTEM_SYOCDCR_DOCDF_Pos                (0UL)          /*!< DOCDF (Bit 0)                                         */
#define R_SYSTEM_SYOCDCR_DOCDF_Msk                (0x1UL)        /*!< DOCDF (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_SYOCDCR_DBGEN_Pos                (7UL)          /*!< DBGEN (Bit 7)                                         */
#define R_SYSTEM_SYOCDCR_DBGEN_Msk                (0x80UL)       /*!< DBGEN (Bitfield-Mask: 0x01)                           */
/* ========================================================  RSTSR0  ========================================================= */
#define R_SYSTEM_RSTSR0_PORF_Pos                  (0UL)          /*!< PORF (Bit 0)                                          */
#define R_SYSTEM_RSTSR0_PORF_Msk                  (0x1UL)        /*!< PORF (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_RSTSR0_LVD0RF_Pos                (1UL)          /*!< LVD0RF (Bit 1)                                        */
#define R_SYSTEM_RSTSR0_LVD0RF_Msk                (0x2UL)        /*!< LVD0RF (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_RSTSR0_LVD1RF_Pos                (2UL)          /*!< LVD1RF (Bit 2)                                        */
#define R_SYSTEM_RSTSR0_LVD1RF_Msk                (0x4UL)        /*!< LVD1RF (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_RSTSR0_LVD2RF_Pos                (3UL)          /*!< LVD2RF (Bit 3)                                        */
#define R_SYSTEM_RSTSR0_LVD2RF_Msk                (0x8UL)        /*!< LVD2RF (Bitfield-Mask: 0x01)                          */
#define R_SYSTEM_RSTSR0_DPSRSTF_Pos               (7UL)          /*!< DPSRSTF (Bit 7)                                       */
#define R_SYSTEM_RSTSR0_DPSRSTF_Msk               (0x80UL)       /*!< DPSRSTF (Bitfield-Mask: 0x01)                         */
/* ========================================================  RSTSR2  ========================================================= */
#define R_SYSTEM_RSTSR2_CWSF_Pos                  (0UL)          /*!< CWSF (Bit 0)                                          */
#define R_SYSTEM_RSTSR2_CWSF_Msk                  (0x1UL)        /*!< CWSF (Bitfield-Mask: 0x01)                            */
/* =========================================================  MOMCR  ========================================================= */
#define R_SYSTEM_MOMCR_MODRV_Pos                  (4UL)          /*!< MODRV (Bit 4)                                         */
#define R_SYSTEM_MOMCR_MODRV_Msk                  (0x30UL)       /*!< MODRV (Bitfield-Mask: 0x03)                           */
#define R_SYSTEM_MOMCR_MOSEL_Pos                  (6UL)          /*!< MOSEL (Bit 6)                                         */
#define R_SYSTEM_MOMCR_MOSEL_Msk                  (0x40UL)       /*!< MOSEL (Bitfield-Mask: 0x01)                           */
/* ========================================================  FWEPROR  ======================================================== */
#define R_SYSTEM_FWEPROR_FLWE_Pos                 (0UL)          /*!< FLWE (Bit 0)                                          */
#define R_SYSTEM_FWEPROR_FLWE_Msk                 (0x3UL)        /*!< FLWE (Bitfield-Mask: 0x03)                            */
/* =======================================================  LVD1CMPCR  ======================================================= */
#define R_SYSTEM_LVD1CMPCR_LVD1LVL_Pos            (0UL)          /*!< LVD1LVL (Bit 0)                                       */
#define R_SYSTEM_LVD1CMPCR_LVD1LVL_Msk            (0x1fUL)       /*!< LVD1LVL (Bitfield-Mask: 0x1f)                         */
#define R_SYSTEM_LVD1CMPCR_LVD1E_Pos              (7UL)          /*!< LVD1E (Bit 7)                                         */
#define R_SYSTEM_LVD1CMPCR_LVD1E_Msk              (0x80UL)       /*!< LVD1E (Bitfield-Mask: 0x01)                           */
/* =======================================================  LVD2CMPCR  ======================================================= */
#define R_SYSTEM_LVD2CMPCR_LVD2LVL_Pos            (0UL)          /*!< LVD2LVL (Bit 0)                                       */
#define R_SYSTEM_LVD2CMPCR_LVD2LVL_Msk            (0x7UL)        /*!< LVD2LVL (Bitfield-Mask: 0x07)                         */
#define R_SYSTEM_LVD2CMPCR_LVD2E_Pos              (7UL)          /*!< LVD2E (Bit 7)                                         */
#define R_SYSTEM_LVD2CMPCR_LVD2E_Msk              (0x80UL)       /*!< LVD2E (Bitfield-Mask: 0x01)                           */
/* ========================================================  LVD1CR0  ======================================================== */
#define R_SYSTEM_LVD1CR0_RIE_Pos                  (0UL)          /*!< RIE (Bit 0)                                           */
#define R_SYSTEM_LVD1CR0_RIE_Msk                  (0x1UL)        /*!< RIE (Bitfield-Mask: 0x01)                             */
#define R_SYSTEM_LVD1CR0_DFDIS_Pos                (1UL)          /*!< DFDIS (Bit 1)                                         */
#define R_SYSTEM_LVD1CR0_DFDIS_Msk                (0x2UL)        /*!< DFDIS (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_LVD1CR0_CMPE_Pos                 (2UL)          /*!< CMPE (Bit 2)                                          */
#define R_SYSTEM_LVD1CR0_CMPE_Msk                 (0x4UL)        /*!< CMPE (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_LVD1CR0_FSAMP_Pos                (4UL)          /*!< FSAMP (Bit 4)                                         */
#define R_SYSTEM_LVD1CR0_FSAMP_Msk                (0x30UL)       /*!< FSAMP (Bitfield-Mask: 0x03)                           */
#define R_SYSTEM_LVD1CR0_RI_Pos                   (6UL)          /*!< RI (Bit 6)                                            */
#define R_SYSTEM_LVD1CR0_RI_Msk                   (0x40UL)       /*!< RI (Bitfield-Mask: 0x01)                              */
#define R_SYSTEM_LVD1CR0_RN_Pos                   (7UL)          /*!< RN (Bit 7)                                            */
#define R_SYSTEM_LVD1CR0_RN_Msk                   (0x80UL)       /*!< RN (Bitfield-Mask: 0x01)                              */
/* ========================================================  LVD2CR0  ======================================================== */
#define R_SYSTEM_LVD2CR0_RIE_Pos                  (0UL)          /*!< RIE (Bit 0)                                           */
#define R_SYSTEM_LVD2CR0_RIE_Msk                  (0x1UL)        /*!< RIE (Bitfield-Mask: 0x01)                             */
#define R_SYSTEM_LVD2CR0_DFDIS_Pos                (1UL)          /*!< DFDIS (Bit 1)                                         */
#define R_SYSTEM_LVD2CR0_DFDIS_Msk                (0x2UL)        /*!< DFDIS (Bitfield-Mask: 0x01)                           */
#define R_SYSTEM_LVD2CR0_CMPE_Pos                 (2UL)          /*!< CMPE (Bit 2)                                          */
#define R_SYSTEM_LVD2CR0_CMPE_Msk                 (0x4UL)        /*!< CMPE (Bitfield-Mask: 0x01)                            */
#define R_SYSTEM_LVD2CR0_FSAMP_Pos                (4UL)          /*!< FSAMP (Bit 4)                                         */
#define R_SYSTEM_LVD2CR0_FSAMP_Msk                (0x30UL)       /*!< FSAMP (Bitfield-Mask: 0x03)                           */
#define R_SYSTEM_LVD2CR0_RI_Pos                   (6UL)          /*!< RI (Bit 6)                                            */
#define R_SYSTEM_LVD2CR0_RI_Msk                   (0x40UL)       /*!< RI (Bitfield-Mask: 0x01)                              */
#define R_SYSTEM_LVD2CR0_RN_Pos                   (7UL)          /*!< RN (Bit 7)                                            */
#define R_SYSTEM_LVD2CR0_RN_Msk                   (0x80UL)       /*!< RN (Bitfield-Mask: 0x01)                              */
/* ========================================================  LOCOCR  ========================================================= */
#define R_SYSTEM_LOCOCR_LCSTP_Pos                 (0UL)          /*!< LCSTP (Bit 0)                                         */
#define R_SYSTEM_LOCOCR_LCSTP_Msk                 (0x1UL)        /*!< LCSTP (Bitfield-Mask: 0x01)                           */
/* =======================================================  LOCOUTCR  ======================================================== */
#define R_SYSTEM_LOCOUTCR_LOCOUTRM_Pos            (0UL)          /*!< LOCOUTRM (Bit 0)                                      */
#define R_SYSTEM_LOCOUTCR_LOCOUTRM_Msk            (0xffUL)       /*!< LOCOUTRM (Bitfield-Mask: 0xff)                        */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
