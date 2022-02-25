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

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
