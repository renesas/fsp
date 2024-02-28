/*
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 *
 * @file     ./out/R7FA0E107.h
 * @brief    CMSIS HeaderFile
 * @version  0.60.04
 */

/** @addtogroup Renesas Electronics Corporation
 * @{
 */

/** @addtogroup R7FA0E107
 * @{
 */

#ifndef R7FA0E107_H
 #define R7FA0E107_H

 #ifdef __cplusplus
extern "C" {
 #endif

/** @addtogroup Configuration_of_CMSIS
 * @{
 */

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ==========================  Configuration of the ARM Cortex-M23 Processor and Core Peripherals  =========================== */
 #define __CM23_REV                0x0100U /*!< CM23 Core Revision                                                        */
 #define __NVIC_PRIO_BITS          2       /*!< Number of Bits used for Priority Levels                                   */
 #define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used                              */
 #define __VTOR_PRESENT            1       /*!< Set to 1 if CPU supports Vector Table Offset Register                     */
 #define __MPU_PRESENT             0       /*!< MPU present                                                               */
 #define __FPU_PRESENT             0       /*!< FPU present                                                               */
 #define __SAUREGION_PRESENT       0       /*!< SAU region present                                                        */

/** @} */ /* End of group Configuration_of_CMSIS */

 #include "core_cm23.h"                    /*!< ARM Cortex-M23 processor and core peripherals                             */
 #include "system.h"                       /*!< R7FA0E107 System                                                          */

 #ifndef __IM                              /*!< Fallback for older CMSIS versions                                         */
  #define __IM     __I
 #endif
 #ifndef __OM                              /*!< Fallback for older CMSIS versions                                         */
  #define __OM     __O
 #endif
 #ifndef __IOM                             /*!< Fallback for older CMSIS versions                                         */
  #define __IOM    __IO
 #endif

/* ========================================  Start of section using anonymous unions  ======================================== */
 #if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
 #elif defined(__ICCARM__)
  #pragma language=extended
 #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
 #elif defined(__GNUC__)

/* anonymous unions are enabled by default */
 #elif defined(__TMS470__)

/* anonymous unions are enabled by default */
 #elif defined(__TASKING__)
  #pragma warning 586
 #elif defined(__CSMC__)

/* anonymous unions are enabled by default */
 #else
  #warning Not supported compiler type
 #endif

/* =========================================================================================================================== */
/* ================                              Device Specific Cluster Section                              ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_clusters
 * @{
 */

/**
 * @brief R_BUS_CSa [CSa] (CS Registers)
 */
typedef struct
{
    __IM uint16_t RESERVED;

    union
    {
        __IOM uint16_t MOD;            /*!< (@ 0x00000002) Mode Register                                              */

        struct
        {
            __IOM uint16_t WRMOD : 1;  /*!< [0..0] Write Access Mode Select                                           */
            uint16_t             : 2;
            __IOM uint16_t EWENB : 1;  /*!< [3..3] External Wait Enable                                               */
            uint16_t             : 4;
            __IOM uint16_t PRENB : 1;  /*!< [8..8] Page Read Access Enable                                            */
            __IOM uint16_t PWENB : 1;  /*!< [9..9] Page Write Access Enable                                           */
            uint16_t             : 5;
            __IOM uint16_t PRMOD : 1;  /*!< [15..15] Page Read Access Mode Select                                     */
        } MOD_b;
    };

    union
    {
        __IOM uint32_t WCR1;             /*!< (@ 0x00000004) Wait Control Register 1                                    */

        struct
        {
            __IOM uint32_t CSPWWAIT : 3; /*!< [2..0] Page Write Cycle Wait Select                                       */
            uint32_t                : 5;
            __IOM uint32_t CSPRWAIT : 3; /*!< [10..8] Page Read Cycle Wait Select                                       */
            uint32_t                : 5;
            __IOM uint32_t CSWWAIT  : 5; /*!< [20..16] Normal Write Cycle Wait Select                                   */
            uint32_t                : 3;
            __IOM uint32_t CSRWAIT  : 5; /*!< [28..24] Normal Read Cycle Wait Select                                    */
            uint32_t                : 3;
        } WCR1_b;
    };

    union
    {
        __IOM uint32_t WCR2;           /*!< (@ 0x00000008) Wait Control Register 2                                    */

        struct
        {
            __IOM uint32_t CSROFF : 3; /*!< [2..0] Read-Access CS Extension Cycle Select                              */
            uint32_t              : 1;
            __IOM uint32_t CSWOFF : 3; /*!< [6..4] Write-Access CS Extension Cycle Select                             */
            uint32_t              : 1;
            __IOM uint32_t WDOFF  : 3; /*!< [10..8] Write Data Output Extension Cycle Select                          */
            uint32_t              : 1;
            __IOM uint32_t AWAIT  : 2; /*!< [13..12] CS Assert Wait Select                                            */
            uint32_t              : 2;
            __IOM uint32_t RDON   : 3; /*!< [18..16] RD Assert Wait Select                                            */
            uint32_t              : 1;
            __IOM uint32_t WRON   : 3; /*!< [22..20] WR Assert Wait Select                                            */
            uint32_t              : 1;
            __IOM uint32_t WDON   : 3; /*!< [26..24] Write Data Output Wait Select                                    */
            uint32_t              : 1;
            __IOM uint32_t CSON   : 3; /*!< [30..28] CS Assert Wait Select                                            */
            uint32_t              : 1;
        } WCR2_b;
    };
    __IM uint32_t RESERVED1;
} R_BUS_CSa_Type;                      /*!< Size = 16 (0x10)                                                          */

/**
 * @brief R_BUS_CSb [CSb] (CS Registers)
 */
typedef struct
{
    __IM uint16_t RESERVED;

    union
    {
        __IOM uint16_t CR;             /*!< (@ 0x00000002) Control Register                                           */

        struct
        {
            __IOM uint16_t EXENB : 1;  /*!< [0..0] Operation Enable                                                   */
            uint16_t             : 3;
            __IOM uint16_t BSIZE : 2;  /*!< [5..4] External Bus Width Select                                          */
            uint16_t             : 2;
            __IOM uint16_t EMODE : 1;  /*!< [8..8] Endian Mode                                                        */
            uint16_t             : 3;
            __IOM uint16_t MPXEN : 1;  /*!< [12..12] Address/Data Multiplexed I/O Interface Select                    */
            uint16_t             : 3;
        } CR_b;
    };
    __IM uint16_t RESERVED1[3];

    union
    {
        __IOM uint16_t REC;            /*!< (@ 0x0000000A) Recovery Cycle Register                                    */

        struct
        {
            __IOM uint16_t RRCV : 4;   /*!< [3..0] Read Recovery                                                      */
            uint16_t            : 4;
            __IOM uint16_t WRCV : 4;   /*!< [11..8] Write Recovery                                                    */
            uint16_t            : 4;
        } REC_b;
    };
    __IM uint16_t RESERVED2[2];
} R_BUS_CSb_Type;                      /*!< Size = 16 (0x10)                                                          */

/**
 * @brief R_BUS_SDRAM [SDRAM] (SDRAM Registers)
 */
typedef struct
{
    union
    {
        __IOM uint8_t SDCCR;           /*!< (@ 0x00000000) SDC Control Register                                       */

        struct
        {
            __IOM uint8_t EXENB : 1;   /*!< [0..0] Operation Enable                                                   */
            uint8_t             : 3;
            __IOM uint8_t BSIZE : 2;   /*!< [5..4] SDRAM Bus Width Select                                             */
            uint8_t             : 2;
        } SDCCR_b;
    };

    union
    {
        __IOM uint8_t SDCMOD;          /*!< (@ 0x00000001) SDC Mode Register                                          */

        struct
        {
            __IOM uint8_t EMODE : 1;   /*!< [0..0] Endian Mode                                                        */
            uint8_t             : 7;
        } SDCMOD_b;
    };

    union
    {
        __IOM uint8_t SDAMOD;          /*!< (@ 0x00000002) SDRAM Access Mode Register                                 */

        struct
        {
            __IOM uint8_t BE : 1;      /*!< [0..0] Continuous Access Enable                                           */
            uint8_t          : 7;
        } SDAMOD_b;
    };
    __IM uint8_t  RESERVED;
    __IM uint32_t RESERVED1[3];

    union
    {
        __IOM uint8_t SDSELF;          /*!< (@ 0x00000010) SDRAM Self-Refresh Control Register                        */

        struct
        {
            __IOM uint8_t SFEN : 1;    /*!< [0..0] SDRAM Self-Refresh Enable                                          */
            uint8_t            : 7;
        } SDSELF_b;
    };
    __IM uint8_t  RESERVED2;
    __IM uint16_t RESERVED3;

    union
    {
        __IOM uint16_t SDRFCR;         /*!< (@ 0x00000014) SDRAM Refresh Control Register                             */

        struct
        {
            __IOM uint16_t RFC  : 12;  /*!< [11..0] Auto-Refresh Request Interval Setting                             */
            __IOM uint16_t REFW : 4;   /*!< [15..12] Auto-Refresh Cycle/ Self-Refresh Clearing Cycle Count
                                        *   Setting. ( REFW+1 Cycles )                                                */
        } SDRFCR_b;
    };

    union
    {
        __IOM uint8_t SDRFEN;          /*!< (@ 0x00000016) SDRAM Auto-Refresh Control Register                        */

        struct
        {
            __IOM uint8_t RFEN : 1;    /*!< [0..0] Auto-Refresh Operation Enable                                      */
            uint8_t            : 7;
        } SDRFEN_b;
    };
    __IM uint8_t  RESERVED4;
    __IM uint32_t RESERVED5[2];

    union
    {
        __IOM uint8_t SDICR;           /*!< (@ 0x00000020) SDRAM Initialization Sequence Control Register             */

        struct
        {
            __IOM uint8_t INIRQ : 1;   /*!< [0..0] Initialization Sequence Start                                      */
            uint8_t             : 7;
        } SDICR_b;
    };
    __IM uint8_t  RESERVED6;
    __IM uint16_t RESERVED7;

    union
    {
        __IOM uint16_t SDIR;           /*!< (@ 0x00000024) SDRAM Initialization Register                              */

        struct
        {
            __IOM uint16_t ARFI : 4;   /*!< [3..0] Initialization Auto-Refresh Interval ( PRF+3 cycles )              */
            __IOM uint16_t ARFC : 4;   /*!< [7..4] Initialization Auto-Refresh Count                                  */
            __IOM uint16_t PRC  : 3;   /*!< [10..8] Initialization Precharge Cycle Count ( PRF+3 cycles
                                        *   )                                                                         */
            uint16_t : 5;
        } SDIR_b;
    };
    __IM uint16_t RESERVED8;
    __IM uint32_t RESERVED9[6];

    union
    {
        __IOM uint8_t SDADR;           /*!< (@ 0x00000040) SDRAM Address Register                                     */

        struct
        {
            __IOM uint8_t MXC : 2;     /*!< [1..0] Address Multiplex Select                                           */
            uint8_t           : 6;
        } SDADR_b;
    };
    __IM uint8_t  RESERVED10;
    __IM uint16_t RESERVED11;

    union
    {
        __IOM uint32_t SDTR;           /*!< (@ 0x00000044) SDRAM Timing Register                                      */

        struct
        {
            __IOM uint32_t CL  : 3;    /*!< [2..0] SDRAMC Column Latency                                              */
            uint32_t           : 5;
            __IOM uint32_t WR  : 1;    /*!< [8..8] Write Recovery Interval                                            */
            __IOM uint32_t RP  : 3;    /*!< [11..9] Row Precharge Interval ( RP+1 cycles )                            */
            __IOM uint32_t RCD : 2;    /*!< [13..12] Row Column Latency ( RCD+1 cycles )                              */
            uint32_t           : 2;
            __IOM uint32_t RAS : 3;    /*!< [18..16] Row Active Interval                                              */
            uint32_t           : 13;
        } SDTR_b;
    };

    union
    {
        __IOM uint16_t SDMOD;          /*!< (@ 0x00000048) SDRAM Mode Register                                        */

        struct
        {
            __IOM uint16_t MR : 15;    /*!< [14..0] Mode Register Setting                                             */
            uint16_t          : 1;
        } SDMOD_b;
    };
    __IM uint16_t RESERVED12;
    __IM uint32_t RESERVED13;

    union
    {
        __IM uint8_t SDSR;             /*!< (@ 0x00000050) SDRAM Status Register                                      */

        struct
        {
            __IM uint8_t MRSST : 1;    /*!< [0..0] Mode Register Setting Status                                       */
            uint8_t            : 2;
            __IM uint8_t INIST : 1;    /*!< [3..3] Initialization Status                                              */
            __IM uint8_t SRFST : 1;    /*!< [4..4] Self-Refresh Transition/Recovery Status                            */
            uint8_t            : 3;
        } SDSR_b;
    };
    __IM uint8_t  RESERVED14;
    __IM uint16_t RESERVED15;
} R_BUS_SDRAM_Type;                    /*!< Size = 84 (0x54)                                                          */

/**
 * @brief R_BUS_BUSERRa [BUSERRa] (Bus Error Registers)
 */
typedef struct
{
    union
    {
        __IM uint32_t ADD;             /*!< (@ 0x00000000) Bus Error Address Register                                 */

        struct
        {
            __IM uint32_t BERAD : 32;  /*!< [31..0] Bus Error Address                                                 */
        } ADD_b;
    };

    union
    {
        union
        {
            __IM uint8_t STAT;            /*!< (@ 0x00000004) Bus Error Status Register                                  */

            struct
            {
                __IM uint8_t ACCSTAT : 1; /*!< [0..0] Error access status                                                */
                uint8_t              : 6;
                __IM uint8_t ERRSTAT : 1; /*!< [7..7] Bus Error Status                                                   */
            } STAT_b;
        };

        union
        {
            __IM uint8_t RW;             /*!< (@ 0x00000004) Bus Error Read Write                                       */

            struct
            {
                __IM uint8_t RWSTAT : 1; /*!< [0..0] Error access Read/Write Status                                     */
                uint8_t             : 7;
            } RW_b;
        };
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1;
    __IM uint32_t RESERVED2[2];
} R_BUS_BUSERRa_Type;                  /*!< Size = 16 (0x10)                                                          */

/**
 * @brief R_BUS_BTZFERR [BTZFERR] (Bus TZF Error Registers)
 */
typedef struct
{
    union
    {
        __IM uint32_t ADD;               /*!< (@ 0x00000000) BUS TZF Error Address                                      */

        struct
        {
            __IM uint32_t BTZFERAD : 32; /*!< [31..0] Bus TrustZone Filter Error Address                                */
        } ADD_b;
    };

    union
    {
        __IM uint8_t RW;               /*!< (@ 0x00000004) BUS TZF Error Read Write                                   */

        struct
        {
            __IM uint8_t TRWSTAT : 1;  /*!< [0..0] TrustZone filter error access Read/Write Status                    */
            uint8_t              : 7;
        } RW_b;
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1;
    __IM uint32_t RESERVED2[2];
} R_BUS_BTZFERR_Type;                  /*!< Size = 16 (0x10)                                                          */

/**
 * @brief R_BUS_BUSERRb [BUSERRb] (Bus Error Registers)
 */
typedef struct
{
    union
    {
        __IM uint8_t STAT;              /*!< (@ 0x00000000) Bus Error Status Register                                  */

        struct
        {
            __IM uint8_t SLERRSTAT : 1; /*!< [0..0] Slave Bus Error Status.                                            */
            __IM uint8_t STERRSTAT : 1; /*!< [1..1] Slave TrustZone filter Error Status.                               */
            uint8_t                : 1;
            __IM uint8_t MMERRSTAT : 1; /*!< [3..3] Master MPU Error Status.                                           */
            __IM uint8_t ILERRSTAT : 1; /*!< [4..4] Illegal Address Access Error Status.                               */
            __IM uint8_t MSERRSTAT : 1; /*!< [5..5] Master Security Attribution Unit Error Status.                     */
            uint8_t                : 2;
        } STAT_b;
    };
    __IM uint8_t RESERVED[7];

    union
    {
        __IOM uint8_t CLR;              /*!< (@ 0x00000008) Bus Error Clear Register                                   */

        struct
        {
            __IOM uint8_t SLERRCLR : 1; /*!< [0..0] Slave Bus Error Clear.                                             */
            __IOM uint8_t STERRCLR : 1; /*!< [1..1] Slave TrustZone filter Error Status.                               */
            uint8_t                : 1;
            __IOM uint8_t MMERRCLR : 1; /*!< [3..3] Master MPU Error Clear.                                            */
            __IOM uint8_t ILERRCLR : 1; /*!< [4..4] Illegal Address Access Error Clear.                                */
            __IOM uint8_t MSERRCLR : 1; /*!< [5..5] Master Security Attribution Unit Error Clear.                      */
            uint8_t                : 2;
        } CLR_b;
    };
    __IM uint8_t RESERVED1[7];
} R_BUS_BUSERRb_Type;                  /*!< Size = 16 (0x10)                                                          */

/**
 * @brief R_BUS_DMACDTCERR [DMACDTCERR] (DMAC/DTC Error Registers)
 */
typedef struct
{
    __IM uint8_t RESERVED[36];

    union
    {
        __IM uint8_t STAT;              /*!< (@ 0x00000024) DMAC/DTC Error Status Register                             */

        struct
        {
            __IM uint8_t MTERRSTAT : 1; /*!< [0..0] Master TrustZone Filter Error Status                               */
            uint8_t                : 7;
        } STAT_b;
    };
    __IM uint8_t RESERVED1[7];

    union
    {
        __IOM uint8_t CLR;              /*!< (@ 0x0000002C) DMAC/DTC Error Clear Register                              */

        struct
        {
            __IOM uint8_t MTERRCLR : 1; /*!< [0..0] Master TrustZone filter Error Clear                                */
            uint8_t                : 7;
        } CLR_b;
    };
} R_BUS_DMACDTCERR_Type;                /*!< Size = 45 (0x2d)                                                          */

/**
 * @brief R_BUS_BUSSABT0 [BUSSABT0] (Bus Slave Arbitration Control 0 Registers)
 */
typedef struct
{
    __IM uint32_t RESERVED[2];

    union
    {
        __IOM uint32_t MRE0BI;         /*!< (@ 0x00000008) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } MRE0BI_b;
    };
    __IM uint32_t RESERVED1;

    union
    {
        __IOM uint32_t FLBI;           /*!< (@ 0x00000010) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } FLBI_b;
    };
    __IM uint32_t RESERVED2[3];

    union
    {
        __IOM uint32_t S0BI;           /*!< (@ 0x00000020) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } S0BI_b;
    };
    __IM uint32_t RESERVED3;

    union
    {
        __IOM uint32_t S1BI;           /*!< (@ 0x00000028) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } S1BI_b;
    };
    __IM uint32_t RESERVED4;

    union
    {
        __IOM uint32_t S2BI;           /*!< (@ 0x00000030) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } S2BI_b;
    };
    __IM uint32_t RESERVED5;

    union
    {
        __IOM uint32_t S3BI;           /*!< (@ 0x00000038) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } S3BI_b;
    };
    __IM uint32_t RESERVED6[3];

    union
    {
        __IOM uint32_t STBYSBI;        /*!< (@ 0x00000048) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } STBYSBI_b;
    };
    __IM uint32_t RESERVED7;

    union
    {
        union
        {
            __IOM uint32_t ECBI;         /*!< (@ 0x00000050) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } ECBI_b;
        };

        union
        {
            __IOM uint32_t SPI0BI;       /*!< (@ 0x00000050) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } SPI0BI_b;
        };
    };
    __IM uint32_t RESERVED8;

    union
    {
        union
        {
            __IOM uint32_t EOBI;         /*!< (@ 0x00000058) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } EOBI_b;
        };

        union
        {
            __IOM uint32_t SPI1BI;       /*!< (@ 0x00000058) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } SPI1BI_b;
        };
    };
    __IM uint32_t RESERVED9;

    union
    {
        __IOM uint32_t PBBI;           /*!< (@ 0x00000060) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } PBBI_b;
    };
    __IM uint32_t RESERVED10;

    union
    {
        union
        {
            __IOM uint32_t PABI;         /*!< (@ 0x00000068) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } PABI_b;
        };

        union
        {
            __IOM uint32_t CPU0SAHBI;    /*!< (@ 0x00000068) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } CPU0SAHBI_b;
        };
    };
    __IM uint32_t RESERVED11;

    union
    {
        union
        {
            __IOM uint32_t PIBI;         /*!< (@ 0x00000070) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } PIBI_b;
        };

        union
        {
            __IOM uint32_t CPU1TCMBI;    /*!< (@ 0x00000070) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for slave.                                      */
                uint32_t            : 31;
            } CPU1TCMBI_b;
        };
    };
    __IM uint32_t RESERVED12;

    union
    {
        __IOM uint32_t PSBI;           /*!< (@ 0x00000078) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 1;   /*!< [0..0] Arbitration Select for slave.                                      */
            uint32_t            : 31;
        } PSBI_b;
    };
} R_BUS_BUSSABT0_Type;                 /*!< Size = 124 (0x7c)                                                         */

/**
 * @brief R_BUS_BUSSABT1 [BUSSABT1] (Bus Slave Arbitration Control 1 Registers)
 */
typedef struct
{
    union
    {
        union
        {
            __IOM uint32_t FHBI;         /*!< (@ 0x00000000) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 2; /*!< [1..0] Arbitration Select for slave.                                      */
                uint32_t            : 30;
            } FHBI_b;
        };

        union
        {
            __IOM uint32_t MRC0BI;       /*!< (@ 0x00000000) Bus Slave Arbitration Control Register                     */

            struct
            {
                __IOM uint32_t ARBS : 2; /*!< [1..0] Arbitration Select for slave.                                      */
                uint32_t            : 30;
            } MRC0BI_b;
        };
    };
    __IM uint32_t RESERVED[5];

    union
    {
        __IOM uint32_t S0BI;           /*!< (@ 0x00000018) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 2;   /*!< [1..0] Arbitration Select for slave.                                      */
            uint32_t            : 30;
        } S0BI_b;
    };
    __IM uint32_t RESERVED1;

    union
    {
        __IOM uint32_t S1BI;           /*!< (@ 0x00000020) Bus Slave Arbitration Control Register                     */

        struct
        {
            __IOM uint32_t ARBS : 2;   /*!< [1..0] Arbitration Select for slave.                                      */
            uint32_t            : 30;
        } S1BI_b;
    };
} R_BUS_BUSSABT1_Type;                 /*!< Size = 36 (0x24)                                                          */

/**
 * @brief R_BUS_BMSAERR [BMSAERR] (Bus Master Security Attribution Unit Error Address and Read/Write Status registers.)
 */
typedef struct
{
    union
    {
        __IM uint32_t ADD;             /*!< (@ 0x00000000) Bus Master Security Attribution Unit Error Address.        */

        struct
        {
            __IM uint32_t MSERAD : 32; /*!< [31..0] Bus Master Security Attribution Unit Error Address.               */
        } ADD_b;
    };

    union
    {
        __IM uint8_t RW;                /*!< (@ 0x00000004) BUS Master Security Attribution Unit Error Read
                                         *                  Write.                                                     */

        struct
        {
            __IM uint8_t MSARWSTAT : 1; /*!< [0..0] Master Security Attribution Unit error access Read/Write
                                         *   Status.                                                                   */
            uint8_t : 7;
        } RW_b;
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1;
    __IM uint32_t RESERVED2[2];
} R_BUS_BMSAERR_Type;                  /*!< Size = 16 (0x10)                                                          */

/**
 * @brief R_BUS_OAD [OAD] (Bus Operation After Detection Registers)
 */
typedef struct
{
    union
    {
        __IOM uint16_t BUSOAD;           /*!< (@ 0x00000000) Bus Operation After Detection Register                     */

        struct
        {
            __IOM uint16_t ILERROAD : 1; /*!< [0..0] Illegal address access error operation after detection.            */
            __IOM uint16_t SLERROAD : 1; /*!< [1..1] Slave bus error operation after detection.                         */
            __IOM uint16_t BWERROAD : 1; /*!< [2..2] Bufferable write error operation after detection.                  */
            uint16_t                : 13;
        } BUSOAD_b;
    };
    __IM uint16_t RESERVED;

    union
    {
        __IOM uint16_t BUSOADPT;        /*!< (@ 0x00000004) BUS Operation After Detection Protect Register.            */

        struct
        {
            __IOM uint16_t PROTECT : 1; /*!< [0..0] Protection of BUSOAD register.                                     */
            uint16_t               : 7;
            __OM uint16_t KEY      : 8; /*!< [15..8] Key code                                                          */
        } BUSOADPT_b;
    };
    __IM uint16_t RESERVED1[5];

    union
    {
        __IOM uint16_t MSAOAD;         /*!< (@ 0x00000010) Master Security Attribution Operation After Detection
                                        *                  Register.                                                  */

        struct
        {
            __IOM uint16_t OAD : 1;    /*!< [0..0] Master Security Attribution operation after detection.             */
            uint16_t           : 7;
            __OM uint16_t KEY  : 8;    /*!< [15..8] Key Code.                                                         */
        } MSAOAD_b;
    };
    __IM uint16_t RESERVED2;

    union
    {
        __IOM uint16_t MSAPT;           /*!< (@ 0x00000014) Master Security Attribution Protect Register.              */

        struct
        {
            __IOM uint16_t PROTECT : 1; /*!< [0..0] Protection of MSAOAD register.                                     */
            uint16_t               : 7;
            __OM uint16_t KEY      : 8; /*!< [15..8] Key code                                                          */
        } MSAPT_b;
    };
} R_BUS_OAD_Type;                       /*!< Size = 22 (0x16)                                                          */

/**
 * @brief R_BUS_MBWERR [MBWERR] (Master Bufferable Write Error Registers)
 */
typedef struct
{
    union
    {
        __IM uint32_t STAT;            /*!< (@ 0x00000000) Bufferable Write Error Status Register                     */

        struct
        {
            __IM uint32_t BWERR0  : 1; /*!< [0..0] Bufferable Write Error in 0.                                       */
            __IM uint32_t BWERR1  : 1; /*!< [1..1] Bufferable Write Error in 1.                                       */
            __IM uint32_t BWERR2  : 1; /*!< [2..2] Bufferable Write Error in 2.                                       */
            __IM uint32_t BWERR3  : 1; /*!< [3..3] Bufferable Write Error in 3.                                       */
            __IM uint32_t BWERR4  : 1; /*!< [4..4] Bufferable Write Error in 4.                                       */
            __IM uint32_t BWERR5  : 1; /*!< [5..5] Bufferable Write Error in 5.                                       */
            __IM uint32_t BWERR6  : 1; /*!< [6..6] Bufferable Write Error in 6.                                       */
            __IM uint32_t BWERR7  : 1; /*!< [7..7] Bufferable Write Error in 7.                                       */
            __IM uint32_t BWERR8  : 1; /*!< [8..8] Bufferable Write Error in 8.                                       */
            __IM uint32_t BWERR9  : 1; /*!< [9..9] Bufferable Write Error in 9.                                       */
            __IM uint32_t BWERR10 : 1; /*!< [10..10] Bufferable Write Error in 10.                                    */
            __IM uint32_t BWERR11 : 1; /*!< [11..11] Bufferable Write Error in 11.                                    */
            __IM uint32_t BWERR12 : 1; /*!< [12..12] Bufferable Write Error in 12.                                    */
            __IM uint32_t BWERR13 : 1; /*!< [13..13] Bufferable Write Error in 13.                                    */
            __IM uint32_t BWERR14 : 1; /*!< [14..14] Bufferable Write Error in 14.                                    */
            __IM uint32_t BWERR15 : 1; /*!< [15..15] Bufferable Write Error in 15.                                    */
            __IM uint32_t BWERR16 : 1; /*!< [16..16] Bufferable Write Error in 16.                                    */
            __IM uint32_t BWERR17 : 1; /*!< [17..17] Bufferable Write Error in 17.                                    */
            __IM uint32_t BWERR18 : 1; /*!< [18..18] Bufferable Write Error in 18.                                    */
            __IM uint32_t BWERR19 : 1; /*!< [19..19] Bufferable Write Error in 19.                                    */
            __IM uint32_t BWERR20 : 1; /*!< [20..20] Bufferable Write Error in 20.                                    */
            __IM uint32_t BWERR21 : 1; /*!< [21..21] Bufferable Write Error in 21.                                    */
            __IM uint32_t BWERR22 : 1; /*!< [22..22] Bufferable Write Error in 22.                                    */
            __IM uint32_t BWERR23 : 1; /*!< [23..23] Bufferable Write Error in 23.                                    */
            __IM uint32_t BWERR24 : 1; /*!< [24..24] Bufferable Write Error in 24.                                    */
            __IM uint32_t BWERR25 : 1; /*!< [25..25] Bufferable Write Error in 25.                                    */
            __IM uint32_t BWERR26 : 1; /*!< [26..26] Bufferable Write Error in 26.                                    */
            __IM uint32_t BWERR27 : 1; /*!< [27..27] Bufferable Write Error in 27.                                    */
            __IM uint32_t BWERR28 : 1; /*!< [28..28] Bufferable Write Error in 28.                                    */
            __IM uint32_t BWERR29 : 1; /*!< [29..29] Bufferable Write Error in 29.                                    */
            __IM uint32_t BWERR30 : 1; /*!< [30..30] Bufferable Write Error in 30.                                    */
            __IM uint32_t BWERR31 : 1; /*!< [31..31] Bufferable Write Error in 31.                                    */
        } STAT_b;
    };
    __IM uint32_t RESERVED;

    union
    {
        __IOM uint32_t CLR;             /*!< (@ 0x00000008) Bufferable Write Error Clear Register.                     */

        struct
        {
            __IOM uint32_t BWERR0  : 1; /*!< [0..0] Bufferable Write Error Clear for 0.                                */
            __IOM uint32_t BWERR1  : 1; /*!< [1..1] Bufferable Write Error Clear for 1.                                */
            __IOM uint32_t BWERR2  : 1; /*!< [2..2] Bufferable Write Error Clear for 2.                                */
            __IOM uint32_t BWERR3  : 1; /*!< [3..3] Bufferable Write Error Clear for 3.                                */
            __IOM uint32_t BWERR4  : 1; /*!< [4..4] Bufferable Write Error Clear for 4.                                */
            __IOM uint32_t BWERR5  : 1; /*!< [5..5] Bufferable Write Error Clear for 5.                                */
            __IOM uint32_t BWERR6  : 1; /*!< [6..6] Bufferable Write Error Clear for 6.                                */
            __IOM uint32_t BWERR7  : 1; /*!< [7..7] Bufferable Write Error Clear for 7.                                */
            __IOM uint32_t BWERR8  : 1; /*!< [8..8] Bufferable Write Error Clear for 8.                                */
            __IOM uint32_t BWERR9  : 1; /*!< [9..9] Bufferable Write Error Clear for 9.                                */
            __IOM uint32_t BWERR10 : 1; /*!< [10..10] Bufferable Write Error Clear for 10.                             */
            __IOM uint32_t BWERR11 : 1; /*!< [11..11] Bufferable Write Error Clear for 11.                             */
            __IOM uint32_t BWERR12 : 1; /*!< [12..12] Bufferable Write Error Clear for 12.                             */
            __IOM uint32_t BWERR13 : 1; /*!< [13..13] Bufferable Write Error Clear for 13.                             */
            __IOM uint32_t BWERR14 : 1; /*!< [14..14] Bufferable Write Error Clear for 14.                             */
            __IOM uint32_t BWERR15 : 1; /*!< [15..15] Bufferable Write Error Clear for 15.                             */
            __IOM uint32_t BWERR16 : 1; /*!< [16..16] Bufferable Write Error Clear for 16.                             */
            __IOM uint32_t BWERR17 : 1; /*!< [17..17] Bufferable Write Error Clear for 17.                             */
            __IOM uint32_t BWERR18 : 1; /*!< [18..18] Bufferable Write Error Clear for 18.                             */
            __IOM uint32_t BWERR19 : 1; /*!< [19..19] Bufferable Write Error Clear for 19.                             */
            __IOM uint32_t BWERR20 : 1; /*!< [20..20] Bufferable Write Error Clear for 20.                             */
            __IOM uint32_t BWERR21 : 1; /*!< [21..21] Bufferable Write Error Clear for 21.                             */
            __IOM uint32_t BWERR22 : 1; /*!< [22..22] Bufferable Write Error Clear for 22.                             */
            __IOM uint32_t BWERR23 : 1; /*!< [23..23] Bufferable Write Error Clear for 23.                             */
            __IOM uint32_t BWERR24 : 1; /*!< [24..24] Bufferable Write Error Clear for 24.                             */
            __IOM uint32_t BWERR25 : 1; /*!< [25..25] Bufferable Write Error Clear for 25.                             */
            __IOM uint32_t BWERR26 : 1; /*!< [26..26] Bufferable Write Error Clear for 26.                             */
            __IOM uint32_t BWERR27 : 1; /*!< [27..27] Bufferable Write Error Clear for 27.                             */
            __IOM uint32_t BWERR28 : 1; /*!< [28..28] Bufferable Write Error Clear for 28.                             */
            __IOM uint32_t BWERR29 : 1; /*!< [29..29] Bufferable Write Error Clear for 29.                             */
            __IOM uint32_t BWERR30 : 1; /*!< [30..30] Bufferable Write Error Clear for 30.                             */
            __IOM uint32_t BWERR31 : 1; /*!< [31..31] Bufferable Write Error Clear for 31.                             */
        } CLR_b;
    };
} R_BUS_MBWERR_Type;                    /*!< Size = 12 (0xc)                                                           */

/**
 * @brief R_BUS_BUSM [BUSM] (Master Bus Control Registers)
 */
typedef struct
{
    union
    {
        __IOM uint16_t CNT;            /*!< (@ 0x00000000) Master Bus Control Register                                */

        struct
        {
            uint16_t             : 15;
            __IOM uint16_t IERES : 1;  /*!< [15..15] Ignore Error Responses                                           */
        } CNT_b;
    };
    __IM uint16_t RESERVED;
} R_BUS_BUSM_Type;                     /*!< Size = 4 (0x4)                                                            */

/**
 * @brief R_BUS_BUSS [BUSS] (Slave Bus Control Register Array)
 */
typedef struct
{
    union
    {
        __IOM uint16_t CNT;            /*!< (@ 0x00000000) Slave Bus Control Register                                 */

        struct
        {
            __IOM uint16_t ARBS   : 2; /*!< [1..0] Arbitration Select                                                 */
            uint16_t              : 2;
            __IOM uint16_t ARBMET : 2; /*!< [5..4] Arbitration Method                                                 */
            uint16_t              : 10;
        } CNT_b;
    };
    __IM uint16_t RESERVED;
} R_BUS_BUSS_Type;                     /*!< Size = 4 (0x4)                                                            */

/**
 * @brief R_ELC_ELSEGR [ELSEGR] (Event Link Software Event Generation Register)
 */
typedef struct
{
    union
    {
        __IOM uint8_t BY;              /*!< (@ 0x00000000) Event Link Software Event Generation Register              */

        struct
        {
            __OM uint8_t SEG : 1;      /*!< [0..0] Software Event Generation                                          */
            uint8_t          : 5;
            __IOM uint8_t WE : 1;      /*!< [6..6] SEG Bit Write Enable                                               */
            __OM uint8_t  WI : 1;      /*!< [7..7] ELSEGR Register Write Disable                                      */
        } BY_b;
    };
    __IM uint8_t RESERVED;
} R_ELC_ELSEGR_Type;                   /*!< Size = 2 (0x2)                                                            */

/**
 * @brief R_ELC_ELSR [ELSR] (Event Link Setting Register [0..28])
 */
typedef struct
{
    union
    {
        __IOM uint16_t HA;             /*!< (@ 0x00000000) Event Link Setting Register                                */

        struct
        {
            __IOM uint16_t ELS : 9;    /*!< [8..0] Event Link Select                                                  */
            uint16_t           : 7;
        } HA_b;
    };
    __IM uint16_t RESERVED;
} R_ELC_ELSR_Type;                     /*!< Size = 4 (0x4)                                                            */

/**
 * @brief R_PFS_PORT_PIN [PIN] (Pin Function Selects)
 */
typedef struct
{
    union
    {
        __IOM uint16_t PmnPFS;         /*!< (@ 0x00000000) Pin Function Control Register                              */

        struct
        {
            __IOM uint16_t PODR  : 1;  /*!< [0..0] Port Output Data                                                   */
            __IM uint16_t  PIDR  : 1;  /*!< [1..1] Pmn State                                                          */
            __IOM uint16_t PDR   : 1;  /*!< [2..2] PDR                                                                */
            uint16_t             : 1;
            __IOM uint16_t PCR   : 1;  /*!< [4..4] PCR                                                                */
            __IOM uint16_t PIM   : 1;  /*!< [5..5] PIM                                                                */
            __IOM uint16_t NCODR : 1;  /*!< [6..6] NCODR                                                              */
            uint16_t             : 1;
            __IOM uint16_t PSEL  : 3;  /*!< [10..8] These bits select the peripheral function. For individual
                                        *   pin functions, see the associated tables in this chapter.                 */
            uint16_t            : 3;
            __IOM uint16_t ISEL : 1;   /*!< [14..14] IRQ Input Enable                                                 */
            __IOM uint16_t PMC  : 1;   /*!< [15..15] Pin mode control                                                 */
        } PmnPFS_b;
    };
} R_PFS_PORT_PIN_Type;                 /*!< Size = 2 (0x2)                                                            */

/**
 * @brief R_PFS_PORT [PORT] (Port [0..9])
 */
typedef struct
{
    __IOM R_PFS_PORT_PIN_Type PIN[16]; /*!< (@ 0x00000000) Pin Function Selects                                       */
} R_PFS_PORT_Type;                     /*!< Size = 32 (0x20)                                                          */

/**
 * @brief R_TAU_TDR0 [TDR0] (Timer Data Registers 0[0..7])
 */
typedef struct
{
    union
    {
        __IOM uint16_t TDR0n;          /*!< (@ 0x00000000) Timer Data Register                                        */

        struct
        {
            __IOM uint8_t TDR0nL;      /*!< (@ 0x00000000) Timer Data Register L                                      */
            __IOM uint8_t TDR0nH;      /*!< (@ 0x00000001) Timer Data Register H                                      */
        };
    };
} R_TAU_TDR0_Type;                     /*!< Size = 2 (0x2)                                                            */

/** @} */ /* End of group Device_Peripheral_clusters */

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripherals
 * @{
 */

/* =========================================================================================================================== */
/* ================                                          R_ADC_D                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief A/D Converter (R_ADC_D)
 */

typedef struct                         /*!< (@ 0x400A1800) R_ADC_D Structure                                          */
{
    union
    {
        __IOM uint8_t ADM0;            /*!< (@ 0x00000000) A/D Converter Mode Register 0                              */

        struct
        {
            __IOM uint8_t ADCE : 1;    /*!< [0..0] A/D Voltage Comparator Operation Control                           */
            __IOM uint8_t LV   : 2;    /*!< [2..1] Select Operation Voltage Mode                                      */
            __IOM uint8_t FR   : 3;    /*!< [5..3] Select Conversion Clock (fAD)                                      */
            __IOM uint8_t ADMD : 1;    /*!< [6..6] Specification of the A/D Conversion Channel Selection
                                        *   Mode                                                                      */
            __IOM uint8_t ADCS : 1;    /*!< [7..7] A/D Conversion Operation Control                                   */
        } ADM0_b;
    };

    union
    {
        __IOM uint8_t ADS;             /*!< (@ 0x00000001) Analog Input Channel Specification Register                */

        struct
        {
            __IOM uint8_t ADS   : 5;   /*!< [4..0] Selection of the Analog Input Channel (See to )                    */
            uint8_t             : 2;
            __IOM uint8_t ADISS : 1;   /*!< [7..7] Select Internal or External of Analog Input (See to )              */
        } ADS_b;
    };

    union
    {
        __IOM uint8_t ADM1;            /*!< (@ 0x00000002) A/D Converter Mode Register 1                              */

        struct
        {
            __IOM uint8_t ADTRS : 3;   /*!< [2..0] Selection of the Hardware Trigger Signal                           */
            __IOM uint8_t ADLSP : 1;   /*!< [3..3] PCLKB Input Frequency Setting                                      */
            uint8_t             : 1;
            __IOM uint8_t ADSCM : 1;   /*!< [5..5] Specification of the A/D Conversion Mode                           */
            __IOM uint8_t ADTMD : 2;   /*!< [7..6] Selection of the A/D Conversion Trigger Mode                       */
        } ADM1_b;
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1;

    union
    {
        __IM uint16_t ADCR;            /*!< (@ 0x00000006) 12-bit or 10-bit A/D Conversion Result Register            */

        struct
        {
            __IM uint8_t RESERVED2;
            __IM uint8_t ADCRH;        /*!< (@ 0x00000007) 8-bit A/D Conversion Result Register                       */
        };
    };
    __IM uint16_t RESERVED3[132];

    union
    {
        __IOM uint8_t ADM2;            /*!< (@ 0x00000110) A/D Converter Mode Register 2                              */

        struct
        {
            __IOM uint8_t ADTYP  : 2;  /*!< [1..0] ADTYP                                                              */
            __IOM uint8_t AWC    : 1;  /*!< [2..2] AWC                                                                */
            __IOM uint8_t ADRCK  : 1;  /*!< [3..3] ADRCK                                                              */
            uint8_t              : 1;
            __IOM uint8_t ADREFM : 1;  /*!< [5..5] ADREFM                                                             */
            __IOM uint8_t ADREFP : 2;  /*!< [7..6] ADREFP                                                             */
        } ADM2_b;
    };
    __IOM uint8_t ADUL;                /*!< (@ 0x00000111) Conversion Result Comparison Upper Limit Setting
                                        *                  Register                                                   */
    __IOM uint8_t ADLL;                /*!< (@ 0x00000112) Conversion Result Comparison Lower Limit Setting
                                        *                  Register                                                   */

    union
    {
        __IOM uint8_t ADTES;           /*!< (@ 0x00000113) A/D Test Register                                          */

        struct
        {
            __IOM uint8_t ADTES : 2;   /*!< [1..0] Selection of A/D Conversion Target for Testing                     */
            uint8_t             : 6;
        } ADTES_b;
    };
    __IM uint16_t RESERVED4[6];

    union
    {
        __IM uint16_t ADCR0;           /*!< (@ 0x00000120) 12-bit or 10-bit A/D Conversion Result Register
                                        *                  0                                                          */

        struct
        {
            __IM uint8_t RESERVED5;
            __IM uint8_t ADCR0H;       /*!< (@ 0x00000121) 8-bit A/D Conversion Result Register 0                     */
        };
    };

    union
    {
        __IM uint16_t ADCR1;           /*!< (@ 0x00000122) 12-bit or 10-bit A/D Conversion Result Register
                                        *                  1                                                          */

        struct
        {
            __IM uint8_t RESERVED6;
            __IM uint8_t ADCR1H;       /*!< (@ 0x00000123) 8-bit A/D Conversion Result Register 1                     */
        };
    };

    union
    {
        __IM uint16_t ADCR2;           /*!< (@ 0x00000124) 12-bit or 10-bit A/D Conversion Result Register
                                        *                  2                                                          */

        struct
        {
            __IM uint8_t RESERVED7;
            __IM uint8_t ADCR2H;       /*!< (@ 0x00000125) 8-bit A/D Conversion Result Register 2                     */
        };
    };

    union
    {
        __IM uint16_t ADCR3;           /*!< (@ 0x00000126) 12-bit or 10-bit A/D Conversion Result Register
                                        *                  3                                                          */

        struct
        {
            __IM uint8_t RESERVED8;
            __IM uint8_t ADCR3H;       /*!< (@ 0x00000127) 8-bit A/D Conversion Result Register 3                     */
        };
    };
} R_ADC_D_Type;                        /*!< Size = 296 (0x128)                                                        */

/* =========================================================================================================================== */
/* ================                                           R_BUS                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Bus Interface (R_BUS)
 */

typedef struct                          /*!< (@ 0x40003000) R_BUS Structure                                            */
{
    __IOM R_BUS_CSa_Type CSa[8];        /*!< (@ 0x00000000) CS Registers                                               */
    __IM uint32_t        RESERVED[480];
    __IOM R_BUS_CSb_Type CSb[8];        /*!< (@ 0x00000800) CS Registers                                               */

    union
    {
        __IOM uint16_t CSRECEN;         /*!< (@ 0x00000880) CS Recovery Cycle Insertion Enable Register                */

        struct
        {
            __IOM uint16_t RCVEN0  : 1; /*!< [0..0] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVEN1  : 1; /*!< [1..1] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVEN2  : 1; /*!< [2..2] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVEN3  : 1; /*!< [3..3] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVEN4  : 1; /*!< [4..4] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVEN5  : 1; /*!< [5..5] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVEN6  : 1; /*!< [6..6] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVEN7  : 1; /*!< [7..7] Separate Bus Recovery Cycle Insertion Enable                       */
            __IOM uint16_t RCVENM0 : 1; /*!< [8..8] Multiplexed Bus Recovery Cycle Insertion Enable                    */
            __IOM uint16_t RCVENM1 : 1; /*!< [9..9] Multiplexed Bus Recovery Cycle Insertion Enable                    */
            __IOM uint16_t RCVENM2 : 1; /*!< [10..10] Multiplexed Bus Recovery Cycle Insertion Enable                  */
            __IOM uint16_t RCVENM3 : 1; /*!< [11..11] Multiplexed Bus Recovery Cycle Insertion Enable                  */
            __IOM uint16_t RCVENM4 : 1; /*!< [12..12] Multiplexed Bus Recovery Cycle Insertion Enable                  */
            __IOM uint16_t RCVENM5 : 1; /*!< [13..13] Multiplexed Bus Recovery Cycle Insertion Enable                  */
            __IOM uint16_t RCVENM6 : 1; /*!< [14..14] Multiplexed Bus Recovery Cycle Insertion Enable                  */
            __IOM uint16_t RCVENM7 : 1; /*!< [15..15] Multiplexed Bus Recovery Cycle Insertion Enable                  */
        } CSRECEN_b;
    };
    __IM uint16_t          RESERVED1;
    __IM uint32_t          RESERVED2[223];
    __IOM R_BUS_SDRAM_Type SDRAM;      /*!< (@ 0x00000C00) SDRAM Registers                                            */
    __IM uint32_t          RESERVED3[235];

    union
    {
        __IOM R_BUS_OAD_Type  OAD;     /*!< (@ 0x00001000) Bus Operation After Detection Registers                    */
        __IOM R_BUS_BUSM_Type BUSM[6]; /*!< (@ 0x00001000) Master Bus Control Registers                               */
    };
    __IM uint32_t RESERVED4[58];

    union
    {
        union
        {
            __IOM uint32_t BUSMABT;      /*!< (@ 0x00001100) Bus Master Arbitration Control Register.                   */

            struct
            {
                __IOM uint32_t ARBS : 1; /*!< [0..0] Arbitration Select for GDSSBI.                                     */
                uint32_t            : 31;
            } BUSMABT_b;
        };
        __IOM R_BUS_BUSS_Type BUSS[18];  /*!< (@ 0x00001100) Slave Bus Control Register Array                           */
    };
    __IM uint32_t RESERVED5[46];

    union
    {
        __IOM R_BUS_BUSSABT0_Type BUSSABT0; /*!< (@ 0x00001200) Bus Slave Arbitration Control 0 Registers                  */
        __IOM R_BUS_BUSSABT1_Type BUSSABT1; /*!< (@ 0x00001200) Bus Slave Arbitration Control 1 Registers                  */
    };
    __IM uint32_t RESERVED6[33];

    union
    {
        __IOM uint32_t BUSDIVBYP;        /*!< (@ 0x00001300) Bus Divider Bypass Register.                               */

        struct
        {
            __IOM uint32_t EDMABPE  : 1; /*!< [0..0] Divider for EDMACBI bypass enable.                                 */
            uint32_t                : 2;
            __IOM uint32_t GDSSBPE  : 1; /*!< [3..3] Divider for GDSSBI bypass enable.                                  */
            uint32_t                : 12;
            __IOM uint32_t CPU0SBPE : 1; /*!< [16..16] Divider for CPUSAHBI bypass enable.                              */
            uint32_t                : 15;
        } BUSDIVBYP_b;
    };
    __IM uint32_t            RESERVED7[319];
    __IOM R_BUS_BUSERRa_Type BUSERRa[12]; /*!< (@ 0x00001800) Bus Error Registers                                        */
    __IM uint32_t            RESERVED8[16];

    union
    {
        __IOM R_BUS_BTZFERR_Type BTZFERR[4]; /*!< (@ 0x00001900) Bus TZF Error Registers                                    */
        __IOM R_BUS_BMSAERR_Type BMSAERR[9]; /*!< (@ 0x00001900) Bus Master Security Attribution Unit Error Address
                                              *                  and Read/Write Status registers.                           */
    };
    __IM uint32_t RESERVED9[28];

    union
    {
        __IOM R_BUS_BUSERRb_Type    BUSERRb[12]; /*!< (@ 0x00001A00) Bus Error Registers                                        */
        __IOM R_BUS_DMACDTCERR_Type DMACDTCERR;  /*!< (@ 0x00001A00) DMAC/DTC Error Registers                                   */
    };
    __IM uint32_t           RESERVED10[16];
    __IOM R_BUS_MBWERR_Type MBWERR;              /*!< (@ 0x00001B00) Master Bufferable Write Error Registers                    */
    __IM uint32_t           RESERVED11[5];
    __IOM R_BUS_MBWERR_Type SBWERR;              /*!< (@ 0x00001B20) Slave Bufferable Write Error Registers                     */
} R_BUS_Type;                                    /*!< Size = 6956 (0x1b2c)                                                      */

/* =========================================================================================================================== */
/* ================                                           R_CRC                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Cyclic Redundancy Check (CRC) Calculator (R_CRC)
 */

typedef struct                         /*!< (@ 0x40074000) R_CRC Structure                                            */
{
    union
    {
        __IOM uint8_t CRCCR0;          /*!< (@ 0x00000000) CRC Control Register0                                      */

        struct
        {
            __IOM uint8_t GPS    : 3;  /*!< [2..0] CRC Generating Polynomial Switching                                */
            uint8_t              : 3;
            __IOM uint8_t LMS    : 1;  /*!< [6..6] CRC Calculation Switching                                          */
            __OM uint8_t  DORCLR : 1;  /*!< [7..7] CRCDOR Register Clear                                              */
        } CRCCR0_b;
    };

    union
    {
        __IOM uint8_t CRCCR1;          /*!< (@ 0x00000001) CRC Control Register1                                      */

        struct
        {
            uint8_t              : 6;
            __IOM uint8_t CRCSWR : 1;  /*!< [6..6] Snoop-on-write/read switch bit                                     */
            __IOM uint8_t CRCSEN : 1;  /*!< [7..7] Snoop enable bit                                                   */
        } CRCCR1_b;
    };
    __IM uint16_t RESERVED;

    union
    {
        union
        {
            __IOM uint32_t CRCDIR;          /*!< (@ 0x00000004) CRC Data Input Register                                    */

            struct
            {
                __IOM uint32_t CRCDIR : 32; /*!< [31..0] Calculation input Data (Case of CRC-32, CRC-32C )                 */
            } CRCDIR_b;
        };

        union
        {
            __IOM uint8_t CRCDIR_BY;         /*!< (@ 0x00000004) CRC Data Input Register (byte access)                      */

            struct
            {
                __IOM uint8_t CRCDIR_BY : 8; /*!< [7..0] Calculation input Data ( Case of CRC-8, CRC-16 or CRC-CCITT
                                              *   )                                                                         */
            } CRCDIR_BY_b;
        };
    };

    union
    {
        union
        {
            __IOM uint32_t CRCDOR;          /*!< (@ 0x00000008) CRC Data Output Register                                   */

            struct
            {
                __IOM uint32_t CRCDOR : 32; /*!< [31..0] Calculation output Data (Case of CRC-32, CRC-32C )                */
            } CRCDOR_b;
        };

        union
        {
            __IOM uint16_t CRCDOR_HA;          /*!< (@ 0x00000008) CRC Data Output Register (halfword access)                 */

            struct
            {
                __IOM uint16_t CRCDOR_HA : 16; /*!< [15..0] Calculation output Data (Case of CRC-16 or CRC-CCITT
                                                *   )                                                                         */
            } CRCDOR_HA_b;
        };

        union
        {
            __IOM uint8_t CRCDOR_BY;         /*!< (@ 0x00000008) CRC Data Output Register(byte access)                      */

            struct
            {
                __IOM uint8_t CRCDOR_BY : 8; /*!< [7..0] Calculation output Data (Case of CRC-8 )                           */
            } CRCDOR_BY_b;
        };
    };

    union
    {
        __IOM uint16_t CRCSAR;         /*!< (@ 0x0000000C) Snoop Address Register                                     */

        struct
        {
            __IOM uint16_t CRCSA : 14; /*!< [13..0] snoop address bitSet the I/O register address to snoop            */
            uint16_t             : 2;
        } CRCSAR_b;
    };
    __IM uint16_t RESERVED1;
} R_CRC_Type;                          /*!< Size = 16 (0x10)                                                          */

/* =========================================================================================================================== */
/* ================                                          R_DEBUG                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief Debug Function (R_DEBUG)
 */

typedef struct                         /*!< (@ 0x4001B000) R_DEBUG Structure                                          */
{
    union
    {
        __IM uint32_t DBGSTR;          /*!< (@ 0x00000000) Debug Status Register                                      */

        struct
        {
            uint32_t                   : 28;
            __IM uint32_t CDBGPWRUPREQ : 1; /*!< [28..28] Debug power-up request                                           */
            __IM uint32_t CDBGPWRUPACK : 1; /*!< [29..29] Debug power-up acknowledge                                       */
            uint32_t                   : 2;
        } DBGSTR_b;
    };
    __IM uint32_t RESERVED[3];

    union
    {
        __IOM uint32_t DBGSTOPCR;             /*!< (@ 0x00000010) Debug Stop Control Register                                */

        struct
        {
            __IOM uint32_t DBGSTOP_IWDT  : 1; /*!< [0..0] Mask bit for IWDT reset/interrupt                                  */
            __IOM uint32_t DBGSTOP_WDT   : 1; /*!< [1..1] Mask bit for WDT reset/interrupt                                   */
            uint32_t                     : 12;
            __IOM uint32_t DBGSTOP_TIM   : 1; /*!< [14..14] Mask bit for RTC, TAU reset/interrupt                            */
            __IOM uint32_t DBGSTOP_SIR   : 1; /*!< [15..15] Mask bit for SAU, IICA, PORT_IRQ0-5 reset/interrupt              */
            __IOM uint32_t DBGSTOP_LVD0  : 1; /*!< [16..16] Mask bit for LVD reset/interupt                                  */
            __IOM uint32_t DBGSTOP_LVD1  : 1; /*!< [17..17] Mask bit for LVD reset/interupt                                  */
            __IOM uint32_t DBGSTOP_LVD2  : 1; /*!< [18..18] Mask bit for LVD reset/interupt                                  */
            uint32_t                     : 5;
            __IOM uint32_t DBGSTOP_RPER  : 1; /*!< [24..24] Mask bit for SRAM parity error                                   */
            __IOM uint32_t DBGSTOP_RECCR : 1; /*!< [25..25] Mask bit for SRAM ECC error                                      */
            uint32_t                     : 5;
            __IOM uint32_t DBGSTOP_CPER  : 1; /*!< [31..31] Mask bit for Cache SRAM parity error reset/interrupt             */
        } DBGSTOPCR_b;
    };
    __IM uint32_t RESERVED1[123];

    union
    {
        __IOM uint32_t FSBLSTAT;       /*!< (@ 0x00000200) First Stage Boot Loader Status Register                    */

        struct
        {
            __IOM uint32_t CS     : 1; /*!< [0..0] FSBL completion status.                                            */
            __IOM uint32_t RS     : 1; /*!< [1..1] FSBL result status.                                                */
            uint32_t              : 6;
            __IM uint32_t FSBLCLK : 3; /*!< [10..8] System clock frequency selection during FSBL execution            */
            uint32_t              : 21;
        } FSBLSTAT_b;
    };
} R_DEBUG_Type;                        /*!< Size = 516 (0x204)                                                        */

/* =========================================================================================================================== */
/* ================                                           R_DTC                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Data Transfer Controller (R_DTC)
 */

typedef struct                         /*!< (@ 0x40005400) R_DTC Structure                                            */
{
    union
    {
        __IOM uint8_t DTCCR;           /*!< (@ 0x00000000) DTC Control Register                                       */

        struct
        {
            uint8_t           : 4;
            __IOM uint8_t RRS : 1;     /*!< [4..4] DTC Transfer Information Read Skip Enable.                         */
            uint8_t           : 3;
        } DTCCR_b;
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1;

    union
    {
        __IOM uint32_t DTCVBR;          /*!< (@ 0x00000004) DTC Vector Base Register                                   */

        struct
        {
            __IOM uint32_t DTCVBR : 32; /*!< [31..0] DTC Vector Base Address.Note: A value cannot be set
                                         *   in the lower-order 10 bits. These bits are fixed to 0.                    */
        } DTCVBR_b;
    };
    __IM uint32_t RESERVED2;

    union
    {
        __IOM uint8_t DTCST;           /*!< (@ 0x0000000C) DTC Module Start Register                                  */

        struct
        {
            __IOM uint8_t DTCST : 1;   /*!< [0..0] DTC Module Start                                                   */
            uint8_t             : 7;
        } DTCST_b;
    };
    __IM uint8_t RESERVED3;

    union
    {
        __IM uint16_t DTCSTS;          /*!< (@ 0x0000000E) DTC Status Register                                        */

        struct
        {
            __IM uint16_t VECN : 8;    /*!< [7..0] DTC-Activating Vector Number MonitoringThese bits indicate
                                        *   the vector number for the activating source when DTC transfer
                                        *   is in progress.The value is only valid if DTC transfer
                                        *   is in progress (the value of the ACT flag is 1)                           */
            uint16_t          : 7;
            __IM uint16_t ACT : 1;     /*!< [15..15] DTC Active Flag                                                  */
        } DTCSTS_b;
    };

    union
    {
        __IOM uint8_t DTCCR_SEC;       /*!< (@ 0x00000010) DTC Control Register for secure Region                     */

        struct
        {
            uint8_t            : 4;
            __IOM uint8_t RRSS : 1;    /*!< [4..4] DTC Transfer Information Read Skip Enable for Secure               */
            uint8_t            : 3;
        } DTCCR_SEC_b;
    };
    __IM uint8_t   RESERVED4;
    __IM uint16_t  RESERVED5;
    __IOM uint32_t DTCVBR_SEC;         /*!< (@ 0x00000014) DTC Vector Base Register for secure Region                 */
    __IM uint32_t  RESERVED6[2];

    union
    {
        __IOM uint32_t DTEVR;          /*!< (@ 0x00000020) DTC Error Vector Register                                  */

        struct
        {
            __IM uint32_t DTEV    : 8; /*!< [7..0] DTC Error Vector Number                                            */
            __IM uint32_t DTEVSAM : 1; /*!< [8..8] DTC Error Vector Number SA Monitor                                 */
            uint32_t              : 7;
            __IOM uint32_t DTESTA : 1; /*!< [16..16] DTC Error Status Flag                                            */
            uint32_t              : 15;
        } DTEVR_b;
    };
} R_DTC_Type;                          /*!< Size = 36 (0x24)                                                          */

/* =========================================================================================================================== */
/* ================                                           R_ELC                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Event Link Controller (R_ELC)
 */

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
    __IM uint8_t            RESERVED;
    __IOM R_ELC_ELSEGR_Type ELSEGR[2]; /*!< (@ 0x00000002) Event Link Software Event Generation Register              */
    __IM uint16_t           RESERVED1[5];
    __IOM R_ELC_ELSR_Type   ELSR[29];  /*!< (@ 0x00000010) Event Link Setting Register [0..28]                        */
} R_ELC_Type;                          /*!< Size = 132 (0x84)                                                         */

/* =========================================================================================================================== */
/* ================                                         R_FACI_LP                                         ================ */
/* =========================================================================================================================== */

/**
 * @brief Flash Application Command Interface (R_FACI_LP)
 */

typedef struct                         /*!< (@ 0x407EC000) R_FACI_LP Structure                                        */
{
    __IM uint32_t RESERVED[36];
    __IOM uint8_t DFLCTL;              /*!< (@ 0x00000090) Flash P/E Mode Control Register                            */
    __IM uint8_t  RESERVED1;
    __IM uint16_t RESERVED2;
    __IM uint32_t RESERVED3[27];

    union
    {
        __IOM uint8_t FPMCR;           /*!< (@ 0x00000100) Flash P/E Mode Control Register                            */

        struct
        {
            uint8_t            : 1;
            __IOM uint8_t FMS0 : 1;    /*!< [1..1] Flash Operating Mode Select 0FMS2,1,0: 000: Read mode
                                        *   011: Discharge mode 1 111: Discharge mode 2 101: Code Flash
                                        *   P/E mode 010: Data flash P/E mode Others: Setting prohibited.             */
            uint8_t             : 1;
            __IOM uint8_t RPDIS : 1;   /*!< [3..3] Code Flash P/E Disable                                             */
            __IOM uint8_t FMS1  : 1;   /*!< [4..4] The bit to make data flash a programming modeRefer to
                                        *   the description of the FMS0 bit.                                          */
            uint8_t            : 1;
            __IOM uint8_t VLPE : 1;    /*!< [6..6] Low-Voltage P/E Mode Enable                                        */
            __IOM uint8_t FMS2 : 1;    /*!< [7..7] Flash Operating Mode Select 2.Refer to the description
                                        *   of the FMS0 bit.                                                          */
        } FPMCR_b;
    };
    __IM uint8_t  RESERVED4;
    __IM uint16_t RESERVED5;

    union
    {
        __IOM uint8_t FASR;            /*!< (@ 0x00000104) Flash Area Select Register                                 */

        struct
        {
            __IOM uint8_t EXS : 1;     /*!< [0..0] Extra area select                                                  */
            uint8_t           : 7;
        } FASR_b;
    };
    __IM uint8_t  RESERVED6;
    __IM uint16_t RESERVED7;

    union
    {
        __IOM uint16_t FSARL;             /*!< (@ 0x00000108) Flash Processing Start Address Register L                  */

        struct
        {
            __IOM uint16_t FSAR15_0 : 16; /*!< [15..0] Start address                                                     */
        } FSARL_b;
    };
    __IM uint16_t RESERVED8;
    __IM uint32_t RESERVED9;

    union
    {
        __IOM uint16_t FSARH;             /*!< (@ 0x00000110) Flash Processing Start Address Register H                  */

        struct
        {
            __IOM uint16_t FSAR20_16 : 5; /*!< [4..0] Start address                                                      */
            uint16_t                 : 4;
            __IOM uint16_t FSAR31_25 : 7; /*!< [15..9] Start address                                                     */
        } FSARH_b;
    };
    __IM uint16_t RESERVED10;

    union
    {
        __IOM uint8_t FCR;             /*!< (@ 0x00000114) Flash Control Register                                     */

        struct
        {
            __IOM uint8_t CMD  : 4;    /*!< [3..0] Software Command Setting                                           */
            __IOM uint8_t DRC  : 1;    /*!< [4..4] Data Read Completion                                               */
            uint8_t            : 1;
            __IOM uint8_t STOP : 1;    /*!< [6..6] Forced Processing Stop                                             */
            __IOM uint8_t OPST : 1;    /*!< [7..7] Processing Start                                                   */
        } FCR_b;
    };
    __IM uint8_t  RESERVED11;
    __IM uint16_t RESERVED12;

    union
    {
        __IOM uint16_t FEARL;             /*!< (@ 0x00000118) Flash Processing End Address Register L                    */

        struct
        {
            __IOM uint16_t FEAR15_0 : 16; /*!< [15..0] End address                                                       */
        } FEARL_b;
    };
    __IM uint16_t RESERVED13;
    __IM uint32_t RESERVED14;

    union
    {
        __IOM uint32_t FEARH;             /*!< (@ 0x00000120) Flash Processing End Address Register H                    */

        struct
        {
            __IOM uint32_t FEAR20_16 : 5; /*!< [4..0] End address                                                        */
            uint32_t                 : 4;
            __IOM uint32_t FEAR31_25 : 7; /*!< [15..9] End address                                                       */
            uint32_t                 : 16;
        } FEARH_b;
    };

    union
    {
        __IOM uint32_t FRESETR;        /*!< (@ 0x00000124) Flash Reset Register                                       */

        struct
        {
            __IOM uint32_t FRESET : 1; /*!< [0..0] Software Reset of the registers                                    */
            uint32_t              : 31;
        } FRESETR_b;
    };

    union
    {
        __IM uint32_t FSTATR00;         /*!< (@ 0x00000128) Flash Status Register00                                    */

        struct
        {
            __IM uint32_t ERERR0   : 1; /*!< [0..0] Erase Error Flag0                                                  */
            __IM uint32_t PRGERR0  : 1; /*!< [1..1] Program Error Flag0                                                */
            __IM uint32_t PRGERR01 : 1; /*!< [2..2] Program Error Flag 01                                              */
            __IM uint32_t BCERR0   : 1; /*!< [3..3] Blank Check Error Flag0                                            */
            __IM uint32_t ILGLERR  : 1; /*!< [4..4] Illegal Command Error Flag                                         */
            __IM uint32_t EILGLERR : 1; /*!< [5..5] Extra Area Illegal Command Error Flag                              */
            uint32_t               : 26;
        } FSTATR00_b;
    };

    union
    {
        __IM uint32_t FSTATR1;         /*!< (@ 0x0000012C) Flash Status Register1                                     */

        struct
        {
            uint32_t            : 1;
            __IM uint32_t DRRDY : 1;   /*!< [1..1] Data read request                                                  */
            uint32_t            : 4;
            __IM uint32_t FRDY  : 1;   /*!< [6..6] End status signal of a sequencer                                   */
            __IM uint32_t EXRDY : 1;   /*!< [7..7] End status signal of a Extra programming sequencer                 */
            uint32_t            : 24;
        } FSTATR1_b;
    };

    union
    {
        __IOM uint32_t FWBL0;          /*!< (@ 0x00000130) Flash Write Buffer Register L0                             */

        struct
        {
            __IOM uint32_t WDATA : 16; /*!< [15..0] Program data of the program command                               */
            uint32_t             : 16;
        } FWBL0_b;
    };
    __IM uint32_t RESERVED15;

    union
    {
        __IOM uint32_t FWBH0;          /*!< (@ 0x00000138) Flash Write Buffer Register H0                             */

        struct
        {
            __IOM uint32_t WDATA : 16; /*!< [15..0] Program data of the program command                               */
            uint32_t             : 16;
        } FWBH0_b;
    };

    union
    {
        __IM uint32_t FSTATR01;        /*!< (@ 0x0000013C) Flash Status Register01                                    */

        struct
        {
            __IM uint32_t ERERR1  : 1; /*!< [0..0] Erase Error Flag1                                                  */
            __IM uint32_t PRGERR1 : 1; /*!< [1..1] Program Error Flag1                                                */
            uint32_t              : 1;
            __IM uint32_t BCERR1  : 1; /*!< [3..3] Blank Check Error Flag1                                            */
            uint32_t              : 28;
        } FSTATR01_b;
    };

    union
    {
        __IOM uint32_t FWBL1;               /*!< (@ 0x00000140) Flash Write Buffer Register L1                             */

        struct
        {
            __IOM uint32_t WDATA47_32 : 16; /*!< [15..0] Program data of the program command                               */
            uint32_t                  : 16;
        } FWBL1_b;
    };

    union
    {
        __IOM uint32_t FWBH1;               /*!< (@ 0x00000144) Flash Write Buffer Register H1                             */

        struct
        {
            __IOM uint32_t WDATA63_48 : 16; /*!< [15..0] Program data of the program command                               */
            uint32_t                  : 16;
        } FWBH1_b;
    };

    union
    {
        __IM uint32_t FRBL1;               /*!< (@ 0x00000148) Flash Read Buffer Register L1                              */

        struct
        {
            __IM uint32_t RDATA47_32 : 16; /*!< [15..0] Read data of the consecutive read command                         */
            uint32_t                 : 16;
        } FRBL1_b;
    };

    union
    {
        __IM uint32_t FRBH1;               /*!< (@ 0x0000014C) Flash Read Buffer Register H1                              */

        struct
        {
            __IM uint32_t RDATA63_48 : 16; /*!< [15..0] Read data of the consecutive read command                         */
            uint32_t                 : 16;
        } FRBH1_b;
    };
    __IM uint32_t RESERVED16[12];

    union
    {
        __OM uint32_t FPR;             /*!< (@ 0x00000180) Protection Unlock Register                                 */

        struct
        {
            __OM uint32_t FPR : 8;     /*!< [7..0] Protection Unlock Register                                         */
            uint32_t          : 24;
        } FPR_b;
    };

    union
    {
        __IM uint32_t FPSR;            /*!< (@ 0x00000184) Protection Unlock Status Register                          */

        struct
        {
            __IM uint32_t PERR : 1;    /*!< [0..0] Protect Error Flag                                                 */
            uint32_t           : 31;
        } FPSR_b;
    };

    union
    {
        __IM uint32_t FRBL0;           /*!< (@ 0x00000188) Flash Read Buffer Register L0                              */

        struct
        {
            __IM uint32_t RDATA : 16;  /*!< [15..0] Read data of the consecutive read command                         */
            uint32_t            : 16;
        } FRBL0_b;
    };
    __IM uint32_t RESERVED17;

    union
    {
        __IM uint32_t FRBH0;           /*!< (@ 0x00000190) Flash Read Buffer Register H0                              */

        struct
        {
            __IM uint32_t RDATA : 16;  /*!< [15..0] Read data of the consecutive read command                         */
            uint32_t            : 16;
        } FRBH0_b;
    };
    __IM uint32_t RESERVED18[11];

    union
    {
        __IM uint32_t FSCMR;           /*!< (@ 0x000001C0) Flash Start-Up Setting Monitor Register                    */

        struct
        {
            uint32_t            : 8;
            __IM uint32_t SASMF : 1;   /*!< [8..8] Start-up Area Setting Monitor Flag                                 */
            uint32_t            : 5;
            __IM uint32_t FSPR  : 1;   /*!< [14..14] Access Window Protection Flag                                    */
            uint32_t            : 17;
        } FSCMR_b;
    };
    __IM uint32_t RESERVED19;

    union
    {
        __IM uint32_t FAWSMR;          /*!< (@ 0x000001C8) Flash Access Window Start Address Monitor Register         */

        struct
        {
            __IM uint32_t FAWS : 12;   /*!< [11..0] Flash Access Window Start Address                                 */
            uint32_t           : 20;
        } FAWSMR_b;
    };
    __IM uint32_t RESERVED20;

    union
    {
        __IM uint32_t FAWEMR;          /*!< (@ 0x000001D0) Flash Access Window End Address Monitor Register           */

        struct
        {
            __IM uint32_t FAWE : 12;   /*!< [11..0] Flash Access Window End Address                                   */
            uint32_t           : 20;
        } FAWEMR_b;
    };
    __IM uint32_t RESERVED21;

    union
    {
        __IOM uint32_t FISR;           /*!< (@ 0x000001D8) Flash Initial Setting Register                             */

        struct
        {
            __IOM uint32_t PCKA : 6;   /*!< [5..0] Peripheral Clock Notification                                      */
            __IOM uint32_t SAS  : 2;   /*!< [7..6] Temporary boot swap mode                                           */
            uint32_t            : 24;
        } FISR_b;
    };

    union
    {
        __IOM uint32_t FEXCR;          /*!< (@ 0x000001DC) Flash Extra Area Control Register                          */

        struct
        {
            __IOM uint32_t CMD  : 3;   /*!< [2..0] Processing Start)                                                  */
            uint32_t            : 4;
            __IOM uint32_t OPST : 1;   /*!< [7..7] Software Command Setting                                           */
            uint32_t            : 24;
        } FEXCR_b;
    };

    union
    {
        __IM uint32_t FEAML;           /*!< (@ 0x000001E0) Flash Error Address Monitor Register L                     */

        struct
        {
            __IM uint32_t FEAM : 16;   /*!< [15..0] Flash Error Address Monitor Register                              */
            uint32_t           : 16;
        } FEAML_b;
    };
    __IM uint32_t RESERVED22;

    union
    {
        __IM uint32_t FEAMH;           /*!< (@ 0x000001E8) Flash Error Address Monitor Register H                     */

        struct
        {
            __IM uint32_t FEAM : 16;   /*!< [15..0] Flash Error Address Monitor Register                              */
            uint32_t           : 16;
        } FEAMH_b;
    };
    __IM uint32_t RESERVED23;

    union
    {
        __IM uint32_t FSTATR2;           /*!< (@ 0x000001F0) Flash Status Register2                                     */

        struct
        {
            __IM uint32_t  ERERR    : 1; /*!< [0..0] Erase Error Flag                                                   */
            __IM uint32_t  PRGERR1  : 1; /*!< [1..1] Program Error Flag                                                 */
            __IOM uint32_t PRGERR01 : 1; /*!< [2..2] Program Error Flag 01                                              */
            __IM uint32_t  BCERR    : 1; /*!< [3..3] Blank Check Error Flag                                             */
            __IM uint32_t  ILGLERR  : 1; /*!< [4..4] Illegal Command Error Flag                                         */
            __IM uint32_t  EILGLERR : 1; /*!< [5..5] Extra Area Illegal Command Error Flag                              */
            uint32_t                : 26;
        } FSTATR2_b;
    };
    __IM uint32_t RESERVED24[3];

    union
    {
        __IOM uint8_t HIOTRM;          /*!< (@ 0x00000200) High-speed On-chip Oscillator Trimming Register            */

        struct
        {
            __IOM uint8_t HIOTRM : 6;  /*!< [5..0] HOCO User Trimming                                                 */
            uint8_t              : 2;
        } HIOTRM_b;
    };
    __IM uint8_t  RESERVED25;
    __IM uint16_t RESERVED26;
    __IM uint32_t RESERVED27;
    __IM uint16_t RESERVED28;

    union
    {
        __IOM uint8_t FLMODE;          /*!< (@ 0x0000020A) Flash Operating Mode Control Register                      */

        struct
        {
            uint8_t            : 6;
            __IOM uint8_t MODE : 2;    /*!< [7..6] Operating Mode Select                                              */
        } FLMODE_b;
    };

    union
    {
        __IOM uint8_t FLMWRP;          /*!< (@ 0x0000020B) Flash Operating Mode Protect Register                      */

        struct
        {
            __IOM uint8_t FLMWEN : 1;  /*!< [0..0] Control of Flash Operation Mode Select Register                    */
            uint8_t              : 7;
        } FLMWRP_b;
    };
    __IM uint32_t  RESERVED29[3];
    __IM uint16_t  RESERVED30;
    __IOM uint16_t FENTRYR_MF4;        /*!< (@ 0x0000021A) Flash P/E Mode Entry Register for MF4                      */
    __IM uint32_t  RESERVED31[85];

    union
    {
        __IOM uint32_t FCTLFR;          /*!< (@ 0x00000370) Flash Control Flag Register                                */

        struct
        {
            __IOM uint32_t BANKSWP : 3; /*!< [2..0] Bank Swap Setting                                                  */
            uint32_t               : 29;
        } FCTLFR_b;
    };
    __IM uint32_t  RESERVED32[3855];
    __IM uint16_t  RESERVED33;
    __IOM uint16_t FENTRYR;            /*!< (@ 0x00003FB2) Flash P/E Mode Entry Register                              */
    __IM uint32_t  RESERVED34[3];
    __IOM uint8_t  FLWAITR;            /*!< (@ 0x00003FC0) Flash Wait Cycle Register                                  */
    __IM uint8_t   RESERVED35;
    __IM uint16_t  RESERVED36;

    union
    {
        __IOM uint8_t FLDWAITR;         /*!< (@ 0x00003FC4) Memory Wait Cycle Control Register for Data Flash          */

        struct
        {
            __IOM uint8_t FLDWAIT1 : 1; /*!< [0..0] Memory Wait Cycle Select for Data Flash                            */
            uint8_t                : 7;
        } FLDWAITR_b;
    };
    __IM uint8_t  RESERVED37;
    __IM uint16_t RESERVED38;
    __IOM uint8_t PFBER;               /*!< (@ 0x00003FC8) Prefetch Buffer Enable Register                            */
    __IM uint8_t  RESERVED39;
    __IM uint16_t RESERVED40;
    __IM uint32_t RESERVED41;

    union
    {
        __IOM uint16_t FBKPGCR;        /*!< (@ 0x00003FD0) Flash Bank Program Control Register                        */

        struct
        {
            __IOM uint16_t BKPGEN : 1; /*!< [0..0] Bank Programming Setting Enable                                    */
            uint16_t              : 7;
            __OM uint16_t FEKEY   : 8; /*!< [15..8] Key Code                                                          */
        } FBKPGCR_b;
    };
    __IM uint16_t RESERVED42;

    union
    {
        __IOM uint16_t FBKSWCR;          /*!< (@ 0x00003FD4) Flash Bank Swap Control Register                           */

        struct
        {
            __IOM uint16_t BKSWUPEN : 1; /*!< [0..0] Bank Swap Update Enable                                            */
            uint16_t                : 7;
            __OM uint16_t FEKEY     : 8; /*!< [15..8] Key Code                                                          */
        } FBKSWCR_b;
    };
    __IM uint16_t RESERVED43;
} R_FACI_LP_Type;                        /*!< Size = 16344 (0x3fd8)                                                     */

/* =========================================================================================================================== */
/* ================                                           R_ICU                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Interrupt Controller Unit (R_ICU)
 */

typedef struct                         /*!< (@ 0x40006000) R_ICU Structure                                            */
{
    union
    {
        __IOM uint8_t IRQCR[16];       /*!< (@ 0x00000000) IRQ Control Register [0..15]                               */

        struct
        {
            __IOM uint8_t IRQMD   : 2; /*!< [1..0] IRQ Detection Sense Select                                         */
            uint8_t               : 2;
            __IOM uint8_t FCLKSEL : 2; /*!< [5..4] IRQ Digital Filter Sampling Clock Select                           */
            uint8_t               : 1;
            __IOM uint8_t FLTEN   : 1; /*!< [7..7] IRQ Digital Filter Enable                                          */
        } IRQCR_b[16];
    };
    __IM uint32_t RESERVED[60];

    union
    {
        __IOM uint8_t NMICR;            /*!< (@ 0x00000100) NMI Pin Interrupt Control Register                         */

        struct
        {
            __IOM uint8_t NMIMD    : 1; /*!< [0..0] NMI Detection Set                                                  */
            uint8_t                : 3;
            __IOM uint8_t NFCLKSEL : 2; /*!< [5..4] NMI Digital Filter Sampling Clock Select                           */
            uint8_t                : 1;
            __IOM uint8_t NFLTEN   : 1; /*!< [7..7] NMI Digital Filter Enable                                          */
        } NMICR_b;
    };
    __IM uint8_t  RESERVED1;
    __IM uint16_t RESERVED2;
    __IM uint32_t RESERVED3[7];

    union
    {
        __IOM uint16_t NMIER;           /*!< (@ 0x00000120) Non-Maskable Interrupt Enable Register                     */

        struct
        {
            __IOM uint16_t IWDTEN  : 1; /*!< [0..0] IWDT Underflow/Refresh Error Interrupt Enable                      */
            __IOM uint16_t WDTEN   : 1; /*!< [1..1] WDT Underflow/Refresh Error Interrupt Enable                       */
            __IOM uint16_t LVD1EN  : 1; /*!< [2..2] Voltage-Monitoring 1 Interrupt Enable                              */
            __IOM uint16_t LVD2EN  : 1; /*!< [3..3] Voltage-Monitoring 2 Interrupt Enable                              */
            __IOM uint16_t VBATTEN : 1; /*!< [4..4] VBATT monitor Interrupt Enable                                     */
            uint16_t               : 1;
            __IOM uint16_t OSTEN   : 1; /*!< [6..6] Oscillation Stop Detection Interrupt Enable                        */
            __IOM uint16_t NMIEN   : 1; /*!< [7..7] NMI Pin Interrupt Enable                                           */
            __IOM uint16_t RPEEN   : 1; /*!< [8..8] RAM Parity Error Interrupt Enable                                  */
            __IOM uint16_t RECCEN  : 1; /*!< [9..9] RAM ECC Error Interrupt Enable                                     */
            __IOM uint16_t BUSSEN  : 1; /*!< [10..10] MPU Bus Slave Error Interrupt Enable                             */
            __IOM uint16_t BUSMEN  : 1; /*!< [11..11] MPU Bus Master Error Interrupt Enable                            */
            __IOM uint16_t SPEEN   : 1; /*!< [12..12] CPU Stack pointer monitor Interrupt Enable                       */
            __IOM uint16_t TZFEN   : 1; /*!< [13..13] TZFEN                                                            */
            uint16_t               : 1;
            __IOM uint16_t CPEEN   : 1; /*!< [15..15] CPEEN                                                            */
        } NMIER_b;
    };
    __IM uint16_t RESERVED4;
    __IM uint32_t RESERVED5[3];

    union
    {
        __IOM uint16_t NMICLR;          /*!< (@ 0x00000130) Non-Maskable Interrupt Status Clear Register               */

        struct
        {
            __OM uint16_t IWDTCLR  : 1; /*!< [0..0] IWDT Clear                                                         */
            __OM uint16_t WDTCLR   : 1; /*!< [1..1] WDT Clear                                                          */
            __OM uint16_t LVD1CLR  : 1; /*!< [2..2] LVD1 Clear                                                         */
            __OM uint16_t LVD2CLR  : 1; /*!< [3..3] LVD2 Clear                                                         */
            __OM uint16_t VBATTCLR : 1; /*!< [4..4] VBATT Clear                                                        */
            uint16_t               : 1;
            __OM uint16_t  OSTCLR  : 1; /*!< [6..6] OST Clear                                                          */
            __OM uint16_t  NMICLR  : 1; /*!< [7..7] NMI Clear                                                          */
            __OM uint16_t  RPECLR  : 1; /*!< [8..8] SRAM Parity Error Clear                                            */
            __OM uint16_t  RECCCLR : 1; /*!< [9..9] SRAM ECC Error Clear                                               */
            __OM uint16_t  BUSSCLR : 1; /*!< [10..10] Bus Slave Error Clear                                            */
            __OM uint16_t  BUSMCLR : 1; /*!< [11..11] Bus Master Error Clear                                           */
            __OM uint16_t  SPECLR  : 1; /*!< [12..12] CPU Stack Pointer Monitor Interrupt Clear                        */
            __IOM uint16_t TZFCLR  : 1; /*!< [13..13] TZFCLR                                                           */
            uint16_t               : 1;
            __IOM uint16_t CPECLR  : 1; /*!< [15..15] CPECLR                                                           */
        } NMICLR_b;
    };
    __IM uint16_t RESERVED6;
    __IM uint32_t RESERVED7[3];

    union
    {
        __IM uint16_t NMISR;           /*!< (@ 0x00000140) Non-Maskable Interrupt Status Register                     */

        struct
        {
            __IM uint16_t IWDTST  : 1; /*!< [0..0] IWDT Underflow/Refresh Error Status Flag                           */
            __IM uint16_t WDTST   : 1; /*!< [1..1] WDT Underflow/Refresh Error Status Flag                            */
            __IM uint16_t LVD1ST  : 1; /*!< [2..2] Voltage-Monitoring 1 Interrupt Status Flag                         */
            __IM uint16_t LVD2ST  : 1; /*!< [3..3] Voltage-Monitoring 2 Interrupt Status Flag                         */
            __IM uint16_t VBATTST : 1; /*!< [4..4] VBATT monitor Interrupt Status Flag                                */
            uint16_t              : 1;
            __IM uint16_t OSTST   : 1; /*!< [6..6] Oscillation Stop Detection Interrupt Status Flag                   */
            __IM uint16_t NMIST   : 1; /*!< [7..7] NMI Status Flag                                                    */
            __IM uint16_t RPEST   : 1; /*!< [8..8] RAM Parity Error Interrupt Status Flag                             */
            __IM uint16_t RECCST  : 1; /*!< [9..9] RAM ECC Error Interrupt Status Flag                                */
            __IM uint16_t BUSSST  : 1; /*!< [10..10] MPU Bus Slave Error Interrupt Status Flag                        */
            __IM uint16_t BUSMST  : 1; /*!< [11..11] MPU Bus Master Error Interrupt Status Flag                       */
            __IM uint16_t SPEST   : 1; /*!< [12..12] CPU Stack pointer monitor Interrupt Status Flag                  */
            __IM uint16_t TZFST   : 1; /*!< [13..13] TZFST                                                            */
            uint16_t              : 1;
            __IM uint16_t CPEST   : 1; /*!< [15..15] CPEST                                                            */
        } NMISR_b;
    };
    __IM uint16_t RESERVED8;
    __IM uint32_t RESERVED9[111];

    union
    {
        __IM uint32_t DTCENST[2];      /*!< (@ 0x00000300) DTC Enable Status Register [0..1]                          */

        struct
        {
            __IM uint32_t ST0  : 1;    /*!< [0..0] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST1  : 1;    /*!< [1..1] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST2  : 1;    /*!< [2..2] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST3  : 1;    /*!< [3..3] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST4  : 1;    /*!< [4..4] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST5  : 1;    /*!< [5..5] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST6  : 1;    /*!< [6..6] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST7  : 1;    /*!< [7..7] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST8  : 1;    /*!< [8..8] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST9  : 1;    /*!< [9..9] DTC Enable Status by Event Number i                                */
            __IM uint32_t ST10 : 1;    /*!< [10..10] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST11 : 1;    /*!< [11..11] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST12 : 1;    /*!< [12..12] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST13 : 1;    /*!< [13..13] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST14 : 1;    /*!< [14..14] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST15 : 1;    /*!< [15..15] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST16 : 1;    /*!< [16..16] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST17 : 1;    /*!< [17..17] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST18 : 1;    /*!< [18..18] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST19 : 1;    /*!< [19..19] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST20 : 1;    /*!< [20..20] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST21 : 1;    /*!< [21..21] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST22 : 1;    /*!< [22..22] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST23 : 1;    /*!< [23..23] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST24 : 1;    /*!< [24..24] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST25 : 1;    /*!< [25..25] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST26 : 1;    /*!< [26..26] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST27 : 1;    /*!< [27..27] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST28 : 1;    /*!< [28..28] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST29 : 1;    /*!< [29..29] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST30 : 1;    /*!< [30..30] DTC Enable Status by Event Number i                              */
            __IM uint32_t ST31 : 1;    /*!< [31..31] DTC Enable Status by Event Number i                              */
        } DTCENST_b[2];
    };
    __IM uint32_t RESERVED10[2];

    union
    {
        __IOM uint32_t DTCENSET[2];    /*!< (@ 0x00000310) DTC Enable Set Register [0..1]                             */

        struct
        {
            __IOM uint32_t SET0  : 1;  /*!< [0..0] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET1  : 1;  /*!< [1..1] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET2  : 1;  /*!< [2..2] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET3  : 1;  /*!< [3..3] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET4  : 1;  /*!< [4..4] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET5  : 1;  /*!< [5..5] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET6  : 1;  /*!< [6..6] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET7  : 1;  /*!< [7..7] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET8  : 1;  /*!< [8..8] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET9  : 1;  /*!< [9..9] DTC Enable Set by Event Number i                                   */
            __IOM uint32_t SET10 : 1;  /*!< [10..10] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET11 : 1;  /*!< [11..11] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET12 : 1;  /*!< [12..12] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET13 : 1;  /*!< [13..13] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET14 : 1;  /*!< [14..14] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET15 : 1;  /*!< [15..15] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET16 : 1;  /*!< [16..16] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET17 : 1;  /*!< [17..17] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET18 : 1;  /*!< [18..18] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET19 : 1;  /*!< [19..19] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET20 : 1;  /*!< [20..20] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET21 : 1;  /*!< [21..21] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET22 : 1;  /*!< [22..22] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET23 : 1;  /*!< [23..23] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET24 : 1;  /*!< [24..24] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET25 : 1;  /*!< [25..25] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET26 : 1;  /*!< [26..26] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET27 : 1;  /*!< [27..27] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET28 : 1;  /*!< [28..28] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET29 : 1;  /*!< [29..29] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET30 : 1;  /*!< [30..30] DTC Enable Set by Event Number i                                 */
            __IOM uint32_t SET31 : 1;  /*!< [31..31] DTC Enable Set by Event Number i                                 */
        } DTCENSET_b[2];
    };
    __IM uint32_t RESERVED11[2];

    union
    {
        __IOM uint32_t DTCENCLR[2];    /*!< (@ 0x00000320) DTC Enable Clear Register [0..1]                           */

        struct
        {
            __IOM uint32_t CLR0  : 1;  /*!< [0..0] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR1  : 1;  /*!< [1..1] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR2  : 1;  /*!< [2..2] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR3  : 1;  /*!< [3..3] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR4  : 1;  /*!< [4..4] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR5  : 1;  /*!< [5..5] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR6  : 1;  /*!< [6..6] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR7  : 1;  /*!< [7..7] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR8  : 1;  /*!< [8..8] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR9  : 1;  /*!< [9..9] DTC Enable Clear by Event Number i                                 */
            __IOM uint32_t CLR10 : 1;  /*!< [10..10] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR11 : 1;  /*!< [11..11] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR12 : 1;  /*!< [12..12] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR13 : 1;  /*!< [13..13] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR14 : 1;  /*!< [14..14] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR15 : 1;  /*!< [15..15] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR16 : 1;  /*!< [16..16] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR17 : 1;  /*!< [17..17] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR18 : 1;  /*!< [18..18] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR19 : 1;  /*!< [19..19] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR20 : 1;  /*!< [20..20] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR21 : 1;  /*!< [21..21] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR22 : 1;  /*!< [22..22] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR23 : 1;  /*!< [23..23] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR24 : 1;  /*!< [24..24] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR25 : 1;  /*!< [25..25] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR26 : 1;  /*!< [26..26] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR27 : 1;  /*!< [27..27] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR28 : 1;  /*!< [28..28] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR29 : 1;  /*!< [29..29] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR30 : 1;  /*!< [30..30] DTC Enable Clear by Event Number i                               */
            __IOM uint32_t CLR31 : 1;  /*!< [31..31] DTC Enable Clear by Event Number i                               */
        } DTCENCLR_b[2];
    };
    __IM uint32_t RESERVED12[2];

    union
    {
        __IM uint32_t INTFLAG[2];      /*!< (@ 0x00000330) Interrupt Request Flag Monitor Register [0..1]             */

        struct
        {
            __IM uint32_t IF0  : 1;    /*!< [0..0] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF1  : 1;    /*!< [1..1] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF2  : 1;    /*!< [2..2] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF3  : 1;    /*!< [3..3] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF4  : 1;    /*!< [4..4] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF5  : 1;    /*!< [5..5] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF6  : 1;    /*!< [6..6] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF7  : 1;    /*!< [7..7] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF8  : 1;    /*!< [8..8] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF9  : 1;    /*!< [9..9] Interrupt Request Flag Monitor                                     */
            __IM uint32_t IF10 : 1;    /*!< [10..10] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF11 : 1;    /*!< [11..11] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF12 : 1;    /*!< [12..12] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF13 : 1;    /*!< [13..13] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF14 : 1;    /*!< [14..14] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF15 : 1;    /*!< [15..15] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF16 : 1;    /*!< [16..16] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF17 : 1;    /*!< [17..17] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF18 : 1;    /*!< [18..18] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF19 : 1;    /*!< [19..19] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF20 : 1;    /*!< [20..20] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF21 : 1;    /*!< [21..21] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF22 : 1;    /*!< [22..22] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF23 : 1;    /*!< [23..23] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF24 : 1;    /*!< [24..24] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF25 : 1;    /*!< [25..25] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF26 : 1;    /*!< [26..26] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF27 : 1;    /*!< [27..27] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF28 : 1;    /*!< [28..28] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF29 : 1;    /*!< [29..29] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF30 : 1;    /*!< [30..30] Interrupt Request Flag Monitor                                   */
            __IM uint32_t IF31 : 1;    /*!< [31..31] Interrupt Request Flag Monitor                                   */
        } INTFLAG_b[2];
    };
    __IM uint32_t RESERVED13[2];

    union
    {
        __IOM uint32_t SBYEDCR0;           /*!< (@ 0x00000340) Software Standby/Snooze End Control Register
                                            *                  0                                                          */

        struct
        {
            __IOM uint32_t IWDTED : 1;     /*!< [0..0] IWDT Interrupt Software Standby/Snooze Mode Returns Enable         */
            __IOM uint32_t LVD1ED : 1;     /*!< [1..1] LVD1 Interrupt Software Standby/Snooze Mode Returns Enable         */
            __IOM uint32_t IRQ0ED : 1;     /*!< [2..2] IRQ0ED                                                             */
            __IOM uint32_t IRQ1ED : 1;     /*!< [3..3] IRQ1ED                                                             */
            __IOM uint32_t IRQ2ED : 1;     /*!< [4..4] IRQ2ED                                                             */
            __IOM uint32_t IRQ3ED : 1;     /*!< [5..5] IRQ3ED                                                             */
            __IOM uint32_t IRQ4ED : 1;     /*!< [6..6] IRQ4ED                                                             */
            __IOM uint32_t IRQ5ED : 1;     /*!< [7..7] IRQ5ED                                                             */
            uint32_t              : 2;
            __IOM uint32_t DTCED  : 1;     /*!< [10..10] DTC Transfer Complete Interrupt Snooze Mode Returns
                                            *   Enable                                                                    */
            uint32_t                 : 7;
            __IOM uint32_t SPI00RXED : 1;  /*!< [18..18] SPI00 Transfer End or Buffer Empty Interrupt Snooze
                                            *   Mode Returns Enable                                                       */
            uint32_t                  : 1;
            __IOM uint32_t UART0ERRED : 1; /*!< [20..20] UART0 Reception Communication Error Occurrence Interrupt
                                            *   Snooze Mode Returns Enable                                                */
            uint32_t               : 5;
            __IOM uint32_t IICA0ED : 1;    /*!< [26..26] IICA0 Address Match Interrupt Software Standby/Snooze
                                            *   Mode Returns Enable                                                       */
            __IOM uint32_t UART0RXED : 1;  /*!< [27..27] UART0 Reception Transfer End Interrupt Snooze Mode
                                            *   Returns Enable                                                            */
            uint32_t               : 3;
            __IOM uint32_t ADC12ED : 1;    /*!< [31..31] End of A/D Conversion Interrupt Snooze Mode Returns
                                            *   Enable                                                                    */
        } SBYEDCR0_b;
    };

    union
    {
        __IOM uint32_t SBYEDCR1;       /*!< (@ 0x00000344) Software Standby/Snooze End Control Register
                                        *                  1                                                          */

        struct
        {
            __IOM uint32_t RTCED : 1;  /*!< [0..0] RTC Interrupt Software Standby/Snooze Mode Returns Enable          */
            __IOM uint32_t ITLED : 1;  /*!< [1..1] Interval Signal of 32-bit Interval Timer Interrupt Software
                                        *   Standby/Snooze Mode Returns Enable                                        */
            uint32_t              : 5;
            __IOM uint32_t URE0ED : 1; /*!< [7..7] UARTA0 Reception Communication Error Interrupt Software
                                        *   Standby/Snooze Mode Returns Enable                                        */
            __IOM uint32_t UT0ED : 1;  /*!< [8..8] UARTA0 Transmission Transfer End or Buffer Empty Interrupt
                                        *   Software Standby/Snooze Mode Returns Enable                               */
            __IOM uint32_t UR0ED : 1;  /*!< [9..9] UARTA0 Reception Transfer End Interrupt Software Standby/Snooze
                                        *   Mode Returns Enable                                                       */
            uint32_t : 22;
        } SBYEDCR1_b;
    };
} R_ICU_Type;                          /*!< Size = 840 (0x348)                                                        */

/* =========================================================================================================================== */
/* ================                                          R_IICA                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Serial Interface IICA (R_IICA)
 */

typedef struct                         /*!< (@ 0x400A3000) R_IICA Structure                                           */
{
    __IOM uint8_t IICA0;               /*!< (@ 0x00000000) IICA Shift Register 0                                      */

    union
    {
        __IM uint8_t IICS0;            /*!< (@ 0x00000001) IICA Status Register 0                                     */

        struct
        {
            __IM uint8_t SPD  : 1;     /*!< [0..0] Detection of stop condition                                        */
            __IM uint8_t STD  : 1;     /*!< [1..1] Detection of start condition                                       */
            __IM uint8_t ACKD : 1;     /*!< [2..2] Detection of acknowledge (ACK)                                     */
            __IM uint8_t TRC  : 1;     /*!< [3..3] Detection of transmit and receive status                           */
            __IM uint8_t COI  : 1;     /*!< [4..4] Detection of matching addresses                                    */
            __IM uint8_t EXC  : 1;     /*!< [5..5] Detection of extension code reception                              */
            __IM uint8_t ALD  : 1;     /*!< [6..6] Detection of arbitration loss                                      */
            __IM uint8_t MSTS : 1;     /*!< [7..7] Master status check flag                                           */
        } IICS0_b;
    };

    union
    {
        __IOM uint8_t IICF0;           /*!< (@ 0x00000002) IICA Flag Register 0                                       */

        struct
        {
            __IOM uint8_t IICRSV : 1;  /*!< [0..0] Communication reservation function disable bit                     */
            __IOM uint8_t STCEN  : 1;  /*!< [1..1] Initial start enable trigger                                       */
            uint8_t              : 4;
            __IM uint8_t IICBSY  : 1;  /*!< [6..6] I2C bus status flag                                                */
            __IM uint8_t STCF    : 1;  /*!< [7..7] IICCTL00.STT clear flag                                            */
        } IICF0_b;
    };
    __IM uint8_t RESERVED[253];

    union
    {
        __IOM uint8_t IICCTL00;        /*!< (@ 0x00000100) IICA Control Register 00                                   */

        struct
        {
            __IOM uint8_t SPT  : 1;    /*!< [0..0] Stop condition trigger                                             */
            __IOM uint8_t STT  : 1;    /*!< [1..1] Start condition trigger                                            */
            __IOM uint8_t ACKE : 1;    /*!< [2..2] Acknowledgment control                                             */
            __IOM uint8_t WTIM : 1;    /*!< [3..3] Control of clock stretching and interrupt request generation       */
            __IOM uint8_t SPIE : 1;    /*!< [4..4] Enable and disable generation of interrupt request when
                                        *   stop condition is detected                                                */
            __IOM uint8_t WREL : 1;    /*!< [5..5] Release from the clock stretch state                               */
            __IOM uint8_t LREL : 1;    /*!< [6..6] Exit from communications                                           */
            __IOM uint8_t IICE : 1;    /*!< [7..7] I2C operation enable                                               */
        } IICCTL00_b;
    };

    union
    {
        __IOM uint8_t IICCTL01;        /*!< (@ 0x00000101) IICA Control Register 01                                   */

        struct
        {
            __IOM uint8_t PRS : 1;     /*!< [0..0] IICA operation clock (fMCK)                                        */
            uint8_t           : 1;
            __IOM uint8_t DFC : 1;     /*!< [2..2] Digital filter operation control                                   */
            __IOM uint8_t SMC : 1;     /*!< [3..3] Operation mode switching                                           */
            __IM uint8_t  DAD : 1;     /*!< [4..4] Detection of SDAA0 pin level (valid only when IICCTL00.IICE
                                        *   = 1)                                                                      */
            __IM uint8_t CLD : 1;      /*!< [5..5] Detection of SCLA0 pin level (valid only when IICCTL00.IICE
                                        *   = 1)                                                                      */
            __IOM uint8_t SVADIS : 1;  /*!< [6..6] Control of address match wakeup                                    */
            __IOM uint8_t WUP    : 1;  /*!< [7..7] IICCTL00.STT clear flag                                            */
        } IICCTL01_b;
    };
    __IOM uint8_t IICWL0;              /*!< (@ 0x00000102) IICA Low-level Width Setting Register 0                    */
    __IOM uint8_t IICWH0;              /*!< (@ 0x00000103) IICA High-level Width Setting Register 0                   */

    union
    {
        __IOM uint8_t SVA0;            /*!< (@ 0x00000104) Slave Address Register 0                                   */

        struct
        {
            uint8_t         : 1;
            __IOM uint8_t A : 7;       /*!< [7..1] 7-bit local address when in slave mode of unit 0                   */
        } SVA0_b;
    };
} R_IICA_Type;                         /*!< Size = 261 (0x105)                                                        */

/* =========================================================================================================================== */
/* ================                                          R_IWDT                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Independent Watchdog Timer (R_IWDT)
 */

typedef struct                         /*!< (@ 0x40044400) R_IWDT Structure                                           */
{
    union
    {
        __IOM uint8_t IWDTRR;          /*!< (@ 0x00000000) IWDT Refresh Register                                      */

        struct
        {
            __IOM uint8_t IWDTRR : 8;  /*!< [7..0] The counter is refreshed by writing 0x00 and then writing
                                        *   0xFF to this register.                                                    */
        } IWDTRR_b;
    };
    __IM uint8_t RESERVED;

    union
    {
        __IOM uint16_t IWDTCR;         /*!< (@ 0x00000002) IWDT Control Register                                      */

        struct
        {
            __IOM uint16_t TOPS : 2;   /*!< [1..0] Timeout Period Selection                                           */
            uint16_t            : 2;
            __IOM uint16_t CKS  : 4;   /*!< [7..4] Clock Division Ratio Selection                                     */
            __IOM uint16_t RPES : 2;   /*!< [9..8] Window End Position Selection                                      */
            uint16_t            : 2;
            __IOM uint16_t RPSS : 2;   /*!< [13..12] Window Start Position Selection                                  */
            uint16_t            : 2;
        } IWDTCR_b;
    };

    union
    {
        __IOM uint16_t IWDTSR;          /*!< (@ 0x00000004) IWDT Status Register                                       */

        struct
        {
            __IM uint16_t  CNTVAL : 14; /*!< [13..0] Down-Counter Value                                                */
            __IOM uint16_t UNDFF  : 1;  /*!< [14..14] Underflow Flag                                                   */
            __IOM uint16_t REFEF  : 1;  /*!< [15..15] Refresh Error Flag                                               */
        } IWDTSR_b;
    };

    union
    {
        __IOM uint8_t IWDTRCR;         /*!< (@ 0x00000006) IWDT Reset Control Register                                */

        struct
        {
            uint8_t               : 7;
            __IOM uint8_t RSTIRQS : 1; /*!< [7..7] Reset Interrupt Request Selection                                  */
        } IWDTRCR_b;
    };
    __IM uint8_t RESERVED1;

    union
    {
        __IOM uint8_t IWDTCSTPR;       /*!< (@ 0x00000008) IWDT Count Stop Control Register                           */

        struct
        {
            uint8_t              : 7;
            __IOM uint8_t SLCSTP : 1;  /*!< [7..7] Sleep-Mode Count Stop Control                                      */
        } IWDTCSTPR_b;
    };
    __IM uint8_t  RESERVED2;
    __IM uint16_t RESERVED3;
} R_IWDT_Type;                         /*!< Size = 12 (0xc)                                                           */

/* =========================================================================================================================== */
/* ================                                          R_MSTP                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief System-Module Stop (R_MSTP)
 */

typedef struct                          /*!< (@ 0x40047000) R_MSTP Structure                                           */
{
    union
    {
        __IOM uint32_t MSTPCRA;         /*!< (@ 0x00000000) Module Stop Control Register A                             */

        struct
        {
            __IOM uint32_t MSTPA0  : 1; /*!< [0..0] Module stop bit 0. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA1  : 1; /*!< [1..1] Module stop bit 1. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA2  : 1; /*!< [2..2] Module stop bit 2. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA3  : 1; /*!< [3..3] Module stop bit 3. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA4  : 1; /*!< [4..4] Module stop bit 4. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA5  : 1; /*!< [5..5] Module stop bit 5. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA6  : 1; /*!< [6..6] Module stop bit 6. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA7  : 1; /*!< [7..7] Module stop bit 7. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA8  : 1; /*!< [8..8] Module stop bit 8. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA9  : 1; /*!< [9..9] Module stop bit 9. See device hardware manual for usage.           */
            __IOM uint32_t MSTPA10 : 1; /*!< [10..10] Module stop bit 10. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA11 : 1; /*!< [11..11] Module stop bit 11. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA12 : 1; /*!< [12..12] Module stop bit 12. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA13 : 1; /*!< [13..13] Module stop bit 13. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA14 : 1; /*!< [14..14] Module stop bit 14. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA15 : 1; /*!< [15..15] Module stop bit 15. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA16 : 1; /*!< [16..16] Module stop bit 16. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA17 : 1; /*!< [17..17] Module stop bit 17. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA18 : 1; /*!< [18..18] Module stop bit 18. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA19 : 1; /*!< [19..19] Module stop bit 19. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA20 : 1; /*!< [20..20] Module stop bit 20. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA21 : 1; /*!< [21..21] Module stop bit 21. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA22 : 1; /*!< [22..22] Module stop bit 22. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA23 : 1; /*!< [23..23] Module stop bit 23. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA24 : 1; /*!< [24..24] Module stop bit 24. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA25 : 1; /*!< [25..25] Module stop bit 25. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA26 : 1; /*!< [26..26] Module stop bit 26. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA27 : 1; /*!< [27..27] Module stop bit 27. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA28 : 1; /*!< [28..28] Module stop bit 28. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA29 : 1; /*!< [29..29] Module stop bit 29. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA30 : 1; /*!< [30..30] Module stop bit 30. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPA31 : 1; /*!< [31..31] Module stop bit 31. See device hardware manual for
                                         *   usage.                                                                    */
        } MSTPCRA_b;
    };

    union
    {
        __IOM uint32_t MSTPCRB;         /*!< (@ 0x00000004) Module Stop Control Register B                             */

        struct
        {
            __IOM uint32_t MSTPB0  : 1; /*!< [0..0] Module stop bit 0. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB1  : 1; /*!< [1..1] Module stop bit 1. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB2  : 1; /*!< [2..2] Module stop bit 2. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB3  : 1; /*!< [3..3] Module stop bit 3. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB4  : 1; /*!< [4..4] Module stop bit 4. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB5  : 1; /*!< [5..5] Module stop bit 5. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB6  : 1; /*!< [6..6] Module stop bit 6. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB7  : 1; /*!< [7..7] Module stop bit 7. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB8  : 1; /*!< [8..8] Module stop bit 8. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB9  : 1; /*!< [9..9] Module stop bit 9. See device hardware manual for usage.           */
            __IOM uint32_t MSTPB10 : 1; /*!< [10..10] Module stop bit 10. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB11 : 1; /*!< [11..11] Module stop bit 11. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB12 : 1; /*!< [12..12] Module stop bit 12. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB13 : 1; /*!< [13..13] Module stop bit 13. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB14 : 1; /*!< [14..14] Module stop bit 14. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB15 : 1; /*!< [15..15] Module stop bit 15. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB16 : 1; /*!< [16..16] Module stop bit 16. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB17 : 1; /*!< [17..17] Module stop bit 17. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB18 : 1; /*!< [18..18] Module stop bit 18. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB19 : 1; /*!< [19..19] Module stop bit 19. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB20 : 1; /*!< [20..20] Module stop bit 20. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB21 : 1; /*!< [21..21] Module stop bit 21. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB22 : 1; /*!< [22..22] Module stop bit 22. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB23 : 1; /*!< [23..23] Module stop bit 23. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB24 : 1; /*!< [24..24] Module stop bit 24. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB25 : 1; /*!< [25..25] Module stop bit 25. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB26 : 1; /*!< [26..26] Module stop bit 26. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB27 : 1; /*!< [27..27] Module stop bit 27. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB28 : 1; /*!< [28..28] Module stop bit 28. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB29 : 1; /*!< [29..29] Module stop bit 29. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB30 : 1; /*!< [30..30] Module stop bit 30. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPB31 : 1; /*!< [31..31] Module stop bit 31. See device hardware manual for
                                         *   usage.                                                                    */
        } MSTPCRB_b;
    };

    union
    {
        __IOM uint32_t MSTPCRC;         /*!< (@ 0x00000008) Module Stop Control Register C                             */

        struct
        {
            __IOM uint32_t MSTPC0  : 1; /*!< [0..0] Module stop bit 0. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC1  : 1; /*!< [1..1] Module stop bit 1. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC2  : 1; /*!< [2..2] Module stop bit 2. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC3  : 1; /*!< [3..3] Module stop bit 3. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC4  : 1; /*!< [4..4] Module stop bit 4. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC5  : 1; /*!< [5..5] Module stop bit 5. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC6  : 1; /*!< [6..6] Module stop bit 6. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC7  : 1; /*!< [7..7] Module stop bit 7. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC8  : 1; /*!< [8..8] Module stop bit 8. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC9  : 1; /*!< [9..9] Module stop bit 9. See device hardware manual for usage.           */
            __IOM uint32_t MSTPC10 : 1; /*!< [10..10] Module stop bit 10. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC11 : 1; /*!< [11..11] Module stop bit 11. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC12 : 1; /*!< [12..12] Module stop bit 12. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC13 : 1; /*!< [13..13] Module stop bit 13. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC14 : 1; /*!< [14..14] Module stop bit 14. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC15 : 1; /*!< [15..15] Module stop bit 15. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC16 : 1; /*!< [16..16] Module stop bit 16. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC17 : 1; /*!< [17..17] Module stop bit 17. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC18 : 1; /*!< [18..18] Module stop bit 18. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC19 : 1; /*!< [19..19] Module stop bit 19. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC20 : 1; /*!< [20..20] Module stop bit 20. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC21 : 1; /*!< [21..21] Module stop bit 21. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC22 : 1; /*!< [22..22] Module stop bit 22. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC23 : 1; /*!< [23..23] Module stop bit 23. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC24 : 1; /*!< [24..24] Module stop bit 24. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC25 : 1; /*!< [25..25] Module stop bit 25. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC26 : 1; /*!< [26..26] Module stop bit 26. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC27 : 1; /*!< [27..27] Module stop bit 27. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC28 : 1; /*!< [28..28] Module stop bit 28. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC29 : 1; /*!< [29..29] Module stop bit 29. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC30 : 1; /*!< [30..30] Module stop bit 30. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPC31 : 1; /*!< [31..31] Module stop bit 31. See device hardware manual for
                                         *   usage.                                                                    */
        } MSTPCRC_b;
    };

    union
    {
        __IOM uint32_t MSTPCRD;         /*!< (@ 0x0000000C) Module Stop Control Register D                             */

        struct
        {
            __IOM uint32_t MSTPD0  : 1; /*!< [0..0] Module stop bit 0. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD1  : 1; /*!< [1..1] Module stop bit 1. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD2  : 1; /*!< [2..2] Module stop bit 2. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD3  : 1; /*!< [3..3] Module stop bit 3. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD4  : 1; /*!< [4..4] Module stop bit 4. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD5  : 1; /*!< [5..5] Module stop bit 5. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD6  : 1; /*!< [6..6] Module stop bit 6. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD7  : 1; /*!< [7..7] Module stop bit 7. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD8  : 1; /*!< [8..8] Module stop bit 8. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD9  : 1; /*!< [9..9] Module stop bit 9. See device hardware manual for usage.           */
            __IOM uint32_t MSTPD10 : 1; /*!< [10..10] Module stop bit 10. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD11 : 1; /*!< [11..11] Module stop bit 11. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD12 : 1; /*!< [12..12] Module stop bit 12. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD13 : 1; /*!< [13..13] Module stop bit 13. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD14 : 1; /*!< [14..14] Module stop bit 14. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD15 : 1; /*!< [15..15] Module stop bit 15. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD16 : 1; /*!< [16..16] Module stop bit 16. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD17 : 1; /*!< [17..17] Module stop bit 17. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD18 : 1; /*!< [18..18] Module stop bit 18. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD19 : 1; /*!< [19..19] Module stop bit 19. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD20 : 1; /*!< [20..20] Module stop bit 20. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD21 : 1; /*!< [21..21] Module stop bit 21. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD22 : 1; /*!< [22..22] Module stop bit 22. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD23 : 1; /*!< [23..23] Module stop bit 23. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD24 : 1; /*!< [24..24] Module stop bit 24. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD25 : 1; /*!< [25..25] Module stop bit 25. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD26 : 1; /*!< [26..26] Module stop bit 26. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD27 : 1; /*!< [27..27] Module stop bit 27. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD28 : 1; /*!< [28..28] Module stop bit 28. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD29 : 1; /*!< [29..29] Module stop bit 29. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD30 : 1; /*!< [30..30] Module stop bit 30. See device hardware manual for
                                         *   usage.                                                                    */
            __IOM uint32_t MSTPD31 : 1; /*!< [31..31] Module stop bit 31. See device hardware manual for
                                         *   usage.                                                                    */
        } MSTPCRD_b;
    };

    union
    {
        union
        {
            __IOM uint32_t MSTPCRE;         /*!< (@ 0x00000010) Module Stop Control Register E                             */

            struct
            {
                __IOM uint32_t MSTPE0  : 1; /*!< [0..0] Module stop bit 0. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE1  : 1; /*!< [1..1] Module stop bit 1. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE2  : 1; /*!< [2..2] Module stop bit 2. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE3  : 1; /*!< [3..3] Module stop bit 3. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE4  : 1; /*!< [4..4] Module stop bit 4. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE5  : 1; /*!< [5..5] Module stop bit 5. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE6  : 1; /*!< [6..6] Module stop bit 6. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE7  : 1; /*!< [7..7] Module stop bit 7. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE8  : 1; /*!< [8..8] Module stop bit 8. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE9  : 1; /*!< [9..9] Module stop bit 9. See device hardware manual for usage.           */
                __IOM uint32_t MSTPE10 : 1; /*!< [10..10] Module stop bit 10. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE11 : 1; /*!< [11..11] Module stop bit 11. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE12 : 1; /*!< [12..12] Module stop bit 12. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE13 : 1; /*!< [13..13] Module stop bit 13. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE14 : 1; /*!< [14..14] Module stop bit 14. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE15 : 1; /*!< [15..15] Module stop bit 15. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE16 : 1; /*!< [16..16] Module stop bit 16. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE17 : 1; /*!< [17..17] Module stop bit 17. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE18 : 1; /*!< [18..18] Module stop bit 18. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE19 : 1; /*!< [19..19] Module stop bit 19. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE20 : 1; /*!< [20..20] Module stop bit 20. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE21 : 1; /*!< [21..21] Module stop bit 21. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE22 : 1; /*!< [22..22] Module stop bit 22. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE23 : 1; /*!< [23..23] Module stop bit 23. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE24 : 1; /*!< [24..24] Module stop bit 24. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE25 : 1; /*!< [25..25] Module stop bit 25. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE26 : 1; /*!< [26..26] Module stop bit 26. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE27 : 1; /*!< [27..27] Module stop bit 27. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE28 : 1; /*!< [28..28] Module stop bit 28. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE29 : 1; /*!< [29..29] Module stop bit 29. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE30 : 1; /*!< [30..30] Module stop bit 30. See device hardware manual for
                                             *   usage.                                                                    */
                __IOM uint32_t MSTPE31 : 1; /*!< [31..31] Module stop bit 31. See device hardware manual for
                                             *   usage.                                                                    */
            } MSTPCRE_b;
        };

        union
        {
            __IOM uint16_t LSMRWDIS;         /*!< (@ 0x00000010) Low Speed Module R/W Disable Control Register              */

            struct
            {
                __IOM uint16_t RTCRWDIS : 1; /*!< [0..0] RTC Register R/W Enable Control                                    */
                __IOM uint16_t WDTDIS   : 1; /*!< [1..1] WDT Operate Clock Control                                          */
                __IOM uint16_t IWDTIDS  : 1; /*!< [2..2] IWDT Register Clock Control                                        */
                uint16_t                : 4;
                __IOM uint16_t WREN     : 1; /*!< [7..7] Write Enable for bits [2:0]                                        */
                __OM uint16_t  PRKEY    : 8; /*!< [15..8] LSMRWDIS Key Code                                                 */
            } LSMRWDIS_b;
        };
    };
} R_MSTP_Type;                               /*!< Size = 20 (0x14)                                                          */

/* =========================================================================================================================== */
/* ================                                          R_PORT0                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief I/O Ports (R_PORT0)
 */

typedef struct                         /*!< (@ 0x400A0000) R_PORT0 Structure                                          */
{
    union
    {
        __IOM uint16_t PODR;           /*!< (@ 0x00000000) Pmn Output Data Register                                   */

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

    union
    {
        __IOM uint16_t PDR;            /*!< (@ 0x00000002) Pmn Direction Register                                     */

        struct
        {
            __IOM uint16_t PDR0  : 1;  /*!< [0..0] Pmn Direction                                                      */
            __IOM uint16_t PDR1  : 1;  /*!< [1..1] Pmn Direction                                                      */
            __IOM uint16_t PDR2  : 1;  /*!< [2..2] Pmn Direction                                                      */
            __IOM uint16_t PDR3  : 1;  /*!< [3..3] Pmn Direction                                                      */
            __IOM uint16_t PDR4  : 1;  /*!< [4..4] Pmn Direction                                                      */
            __IOM uint16_t PDR5  : 1;  /*!< [5..5] Pmn Direction                                                      */
            __IOM uint16_t PDR6  : 1;  /*!< [6..6] Pmn Direction                                                      */
            __IOM uint16_t PDR7  : 1;  /*!< [7..7] Pmn Direction                                                      */
            __IOM uint16_t PDR8  : 1;  /*!< [8..8] Pmn Direction                                                      */
            __IOM uint16_t PDR9  : 1;  /*!< [9..9] Pmn Direction                                                      */
            __IOM uint16_t PDR10 : 1;  /*!< [10..10] Pmn Direction                                                    */
            __IOM uint16_t PDR11 : 1;  /*!< [11..11] Pmn Direction                                                    */
            __IOM uint16_t PDR12 : 1;  /*!< [12..12] Pmn Direction                                                    */
            __IOM uint16_t PDR13 : 1;  /*!< [13..13] Pmn Direction                                                    */
            __IOM uint16_t PDR14 : 1;  /*!< [14..14] Pmn Direction                                                    */
            __IOM uint16_t PDR15 : 1;  /*!< [15..15] Pmn Direction                                                    */
        } PDR_b;
    };
    __IM uint16_t RESERVED;

    union
    {
        __IM uint16_t PIDR;            /*!< (@ 0x00000006) Pmn State Register                                         */

        struct
        {
            __IM uint16_t PIDR0  : 1;  /*!< [0..0] Pmn State                                                          */
            __IM uint16_t PIDR1  : 1;  /*!< [1..1] Pmn State                                                          */
            __IM uint16_t PIDR2  : 1;  /*!< [2..2] Pmn State                                                          */
            __IM uint16_t PIDR3  : 1;  /*!< [3..3] Pmn State                                                          */
            __IM uint16_t PIDR4  : 1;  /*!< [4..4] Pmn State                                                          */
            __IM uint16_t PIDR5  : 1;  /*!< [5..5] Pmn State                                                          */
            __IM uint16_t PIDR6  : 1;  /*!< [6..6] Pmn State                                                          */
            __IM uint16_t PIDR7  : 1;  /*!< [7..7] Pmn State                                                          */
            __IM uint16_t PIDR8  : 1;  /*!< [8..8] Pmn State                                                          */
            __IM uint16_t PIDR9  : 1;  /*!< [9..9] Pmn State                                                          */
            __IM uint16_t PIDR10 : 1;  /*!< [10..10] Pmn State                                                        */
            __IM uint16_t PIDR11 : 1;  /*!< [11..11] Pmn State                                                        */
            __IM uint16_t PIDR12 : 1;  /*!< [12..12] Pmn State                                                        */
            __IM uint16_t PIDR13 : 1;  /*!< [13..13] Pmn State                                                        */
            __IM uint16_t PIDR14 : 1;  /*!< [14..14] Pmn State                                                        */
            __IM uint16_t PIDR15 : 1;  /*!< [15..15] Pmn State                                                        */
        } PIDR_b;
    };

    union
    {
        __OM uint16_t PORR;            /*!< (@ 0x00000008) Pmn Output Reset Register                                  */

        struct
        {
            __OM uint16_t PORR0  : 1;  /*!< [0..0] Pmn Output Reset                                                   */
            __OM uint16_t PORR1  : 1;  /*!< [1..1] Pmn Output Reset                                                   */
            __OM uint16_t PORR2  : 1;  /*!< [2..2] Pmn Output Reset                                                   */
            __OM uint16_t PORR3  : 1;  /*!< [3..3] Pmn Output Reset                                                   */
            __OM uint16_t PORR4  : 1;  /*!< [4..4] Pmn Output Reset                                                   */
            __OM uint16_t PORR5  : 1;  /*!< [5..5] Pmn Output Reset                                                   */
            __OM uint16_t PORR6  : 1;  /*!< [6..6] Pmn Output Reset                                                   */
            __OM uint16_t PORR7  : 1;  /*!< [7..7] Pmn Output Reset                                                   */
            __OM uint16_t PORR8  : 1;  /*!< [8..8] Pmn Output Reset                                                   */
            __OM uint16_t PORR9  : 1;  /*!< [9..9] Pmn Output Reset                                                   */
            __OM uint16_t PORR10 : 1;  /*!< [10..10] Pmn Output Reset                                                 */
            __OM uint16_t PORR11 : 1;  /*!< [11..11] Pmn Output Reset                                                 */
            __OM uint16_t PORR12 : 1;  /*!< [12..12] Pmn Output Reset                                                 */
            __OM uint16_t PORR13 : 1;  /*!< [13..13] Pmn Output Reset                                                 */
            __OM uint16_t PORR14 : 1;  /*!< [14..14] Pmn Output Reset                                                 */
            __OM uint16_t PORR15 : 1;  /*!< [15..15] Pmn Output Reset                                                 */
        } PORR_b;
    };

    union
    {
        __OM uint16_t POSR;            /*!< (@ 0x0000000A) Pmn Output Set Register                                    */

        struct
        {
            __OM uint16_t POSR0  : 1;  /*!< [0..0] Pmn Output Set                                                     */
            __OM uint16_t POSR1  : 1;  /*!< [1..1] Pmn Output Set                                                     */
            __OM uint16_t POSR2  : 1;  /*!< [2..2] Pmn Output Set                                                     */
            __OM uint16_t POSR3  : 1;  /*!< [3..3] Pmn Output Set                                                     */
            __OM uint16_t POSR4  : 1;  /*!< [4..4] Pmn Output Set                                                     */
            __OM uint16_t POSR5  : 1;  /*!< [5..5] Pmn Output Set                                                     */
            __OM uint16_t POSR6  : 1;  /*!< [6..6] Pmn Output Set                                                     */
            __OM uint16_t POSR7  : 1;  /*!< [7..7] Pmn Output Set                                                     */
            __OM uint16_t POSR8  : 1;  /*!< [8..8] Pmn Output Set                                                     */
            __OM uint16_t POSR9  : 1;  /*!< [9..9] Pmn Output Set                                                     */
            __OM uint16_t POSR10 : 1;  /*!< [10..10] Pmn Output Set                                                   */
            __OM uint16_t POSR11 : 1;  /*!< [11..11] Pmn Output Set                                                   */
            __OM uint16_t POSR12 : 1;  /*!< [12..12] Pmn Output Set                                                   */
            __OM uint16_t POSR13 : 1;  /*!< [13..13] Pmn Output Set                                                   */
            __OM uint16_t POSR14 : 1;  /*!< [14..14] Pmn Output Set                                                   */
            __OM uint16_t POSR15 : 1;  /*!< [15..15] Pmn Output Set                                                   */
        } POSR_b;
    };

    union
    {
        __IOM uint16_t EORR;           /*!< (@ 0x0000000C) Pmn Event Output Reset Register                            */

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

    union
    {
        __IOM uint16_t EOSR;           /*!< (@ 0x0000000E) Pmn Event Output Set Register                              */

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
} R_PORT0_Type;                        /*!< Size = 16 (0x10)                                                          */

/* =========================================================================================================================== */
/* ================                                          R_PORGA                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief Product Organize Register (R_PORGA)
 */

typedef struct                         /*!< (@ 0x400A1000) R_PORGA Structure                                          */
{
    union
    {
        __IOM uint8_t SNFEN;           /*!< (@ 0x00000000) SAU Noise Filter Enable Register                           */

        struct
        {
            __IOM uint8_t SNFEN00 : 1; /*!< [0..0] Use of Noise Filter of RxD0 Pin                                    */
            uint8_t               : 1;
            __IOM uint8_t SNFEN10 : 1; /*!< [2..2] Use of Noise Filter of RxD1 Pin                                    */
            uint8_t               : 1;
            __IOM uint8_t SNFEN20 : 1; /*!< [4..4] Use of Noise Filter of RxD2 Pin                                    */
            uint8_t               : 3;
        } SNFEN_b;
    };

    union
    {
        __IOM uint8_t TNFEN;           /*!< (@ 0x00000001) TAU Noise Filter Enable Register                           */

        struct
        {
            __IOM uint8_t TNFEN00 : 1; /*!< [0..0] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI00 Pin                                                                  */
            __IOM uint8_t TNFEN01 : 1; /*!< [1..1] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI01 Pin                                                                  */
            __IOM uint8_t TNFEN02 : 1; /*!< [2..2] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI02 Pin                                                                  */
            __IOM uint8_t TNFEN03 : 1; /*!< [3..3] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI03 Pin                                                                  */
            __IOM uint8_t TNFEN04 : 1; /*!< [4..4] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI04 Pin                                                                  */
            __IOM uint8_t TNFEN05 : 1; /*!< [5..5] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI05 Pin                                                                  */
            __IOM uint8_t TNFEN06 : 1; /*!< [6..6] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI06 Pin                                                                  */
            __IOM uint8_t TNFEN07 : 1; /*!< [7..7] Enabling or Disabling Use of the Noise Filter for the
                                        *   TI07 Pin                                                                  */
        } TNFEN_b;
    };
    __IM uint8_t RESERVED;

    union
    {
        __IOM uint8_t ISC;             /*!< (@ 0x00000003) Input Switch Control Register                              */

        struct
        {
            __IOM uint8_t ISC0   : 1;  /*!< [0..0] Switching External Interrupt (IRQ0) Input                          */
            __IOM uint8_t ISC1   : 1;  /*!< [1..1] Switching Channel 7 Input of Timer Array Unit                      */
            __IOM uint8_t SSIE00 : 1;  /*!< [2..2] Setting of the SSI00 Input of Channel 0 in the Communications
                                        *   Through SPI00 in the Slave Mode                                           */
            uint8_t : 5;
        } ISC_b;
    };

    union
    {
        __IOM uint8_t TIS0;            /*!< (@ 0x00000004) Timer Input Select Register 0                              */

        struct
        {
            __IOM uint8_t TIS : 3;     /*!< [2..0] Selection of Timer Input Used with Channel 5                       */
            uint8_t           : 5;
        } TIS0_b;
    };

    union
    {
        __IOM uint8_t TIS1;            /*!< (@ 0x00000005) Timer Input Select Register 1                              */

        struct
        {
            __IOM uint8_t TIS0 : 1;    /*!< [0..0] Selection of Timer Input Used with Channel 0                       */
            __IOM uint8_t TIS1 : 1;    /*!< [1..1] Selection of Timer Input Used with Channel 1                       */
            uint8_t            : 6;
        } TIS1_b;
    };
    __IM uint8_t RESERVED1[3];

    union
    {
        __IOM uint8_t ULBS;            /*!< (@ 0x00000009) UART Loopback Select Register                              */

        struct
        {
            __IOM uint8_t ULBS0 : 1;   /*!< [0..0] Selection of the UART0 Loopback Function                           */
            __IOM uint8_t ULBS1 : 1;   /*!< [1..1] Selection of the UART1 Loopback Function                           */
            __IOM uint8_t ULBS2 : 1;   /*!< [2..2] Selection of the UART2 Loopback Function                           */
            uint8_t             : 1;
            __IOM uint8_t ULBS4 : 1;   /*!< [4..4] Selection of the UARTA Loopback Function                           */
            uint8_t             : 3;
        } ULBS_b;
    };
} R_PORGA_Type;                        /*!< Size = 10 (0xa)                                                           */

/* =========================================================================================================================== */
/* ================                                           R_PFS                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief I/O Ports-PFS (R_PFS)
 */

typedef struct                         /*!< (@ 0x400A0200) R_PFS Structure                                            */
{
    __IOM R_PFS_PORT_Type PORT[10];    /*!< (@ 0x00000000) Port [0..9]                                                */
} R_PFS_Type;                          /*!< Size = 320 (0x140)                                                        */

/* =========================================================================================================================== */
/* ================                                          R_PMISC                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief I/O Ports-MISC (R_PMISC)
 */

typedef struct                         /*!< (@ 0x400A0340) R_PMISC Structure                                          */
{
    union
    {
        __IOM uint8_t PWPR;            /*!< (@ 0x00000000) Write-Protect Register                                     */

        struct
        {
            uint8_t             : 6;
            __IOM uint8_t PFSWE : 1;   /*!< [6..6] PmnPFS Register Write                                              */
            __IOM uint8_t B0WI  : 1;   /*!< [7..7] PFSWE Bit Write Disable                                            */
        } PWPR_b;
    };
} R_PMISC_Type;                        /*!< Size = 1 (0x1)                                                            */

/* =========================================================================================================================== */
/* ================                                          R_SAU0                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Serial Array Unit 0 (R_SAU0)
 */

typedef struct                         /*!< (@ 0x400A2000) R_SAU0 Structure                                           */
{
    union
    {
        __IOM uint16_t SDR[4];         /*!< (@ 0x00000000) Serial Data Register                                       */

        struct
        {
            __IOM uint16_t DAT   : 9;  /*!< [8..0] Data Buffer for Transmit and Receive                               */
            __IOM uint16_t STCLK : 7;  /*!< [15..9] Transfer Clock Setting by Dividing the Operation Clock            */
        } SDR_b[4];
    };
    __IM uint16_t RESERVED[124];

    union
    {
        __IM uint16_t SSR[4];          /*!< (@ 0x00000100) Serial Status Register                                     */

        struct
        {
            __IM uint16_t OVF : 1;     /*!< [0..0] Overrun Error Detection Flag                                       */
            __IM uint16_t PEF : 1;     /*!< [1..1] Parity or ACK Error Detection Flag                                 */
            __IM uint16_t FEF : 1;     /*!< [2..2] Framing Error Detection Flag                                       */
            uint16_t          : 2;
            __IM uint16_t BFF : 1;     /*!< [5..5] Flag Indicating the State of the Buffer Register                   */
            __IM uint16_t TSF : 1;     /*!< [6..6] Flag Indicating the State of Communications                        */
            uint16_t          : 9;
        } SSR_b[4];
    };

    union
    {
        __IOM uint16_t SIR[4];         /*!< (@ 0x00000108) Serial Flag Clear Trigger Register                         */

        struct
        {
            __IOM uint16_t OVCT : 1;   /*!< [0..0] Clear Trigger of Overrun Error Flag                                */
            __IOM uint16_t PECT : 1;   /*!< [1..1] Clear Trigger of Parity Error Flag                                 */
            __IOM uint16_t FECT : 1;   /*!< [2..2] Clear Trigger of Framing Error Flag                                */
            uint16_t            : 13;
        } SIR_b[4];
    };

    union
    {
        __IOM uint16_t SMR[4];         /*!< (@ 0x00000110) Serial Mode Register                                       */

        struct
        {
            __IOM uint16_t MD0  : 1;   /*!< [0..0] Interrupt Source                                                   */
            __IOM uint16_t MD1  : 2;   /*!< [2..1] Operation Mode                                                     */
            uint16_t            : 3;
            __IOM uint16_t SIS0 : 1;   /*!< [6..6] Inversion of Level Receive Data in UART Mode                       */
            uint16_t            : 1;
            __IOM uint16_t STS  : 1;   /*!< [8..8] Start Trigger Source                                               */
            uint16_t            : 5;
            __IOM uint16_t CCS  : 1;   /*!< [14..14] Transfer Clock (fTCLK)                                           */
            __IOM uint16_t CKS  : 1;   /*!< [15..15] Operation Clock (fMCK)                                           */
        } SMR_b[4];
    };

    union
    {
        __IOM uint16_t SCR[4];         /*!< (@ 0x00000118) Serial Communication Operation Setting Register            */

        struct
        {
            __IOM uint16_t DLS : 2;    /*!< [1..0] Data Length in Simplified SPI and UART Modes                       */
            uint16_t           : 2;
            __IOM uint16_t SLC : 2;    /*!< [5..4] Stop Bit in UART Mode                                              */
            uint16_t           : 1;
            __IOM uint16_t DIR : 1;    /*!< [7..7] Data Transfer Sequence in Simplified SPI and UART Modes            */
            __IOM uint16_t PTC : 2;    /*!< [9..8] Parity Bit in UART Mode                                            */
            __IOM uint16_t EOC : 1;    /*!< [10..10] Mask Control of Error Interrupt Signal SAU0_UART_ERRI0
                                        *   (m = 0), SAU1_UART_ERRI2 (m = 1)                                          */
            uint16_t            : 1;
            __IOM uint16_t DCP  : 2;   /*!< [13..12] Data and Clock Phase in Simplified SPI Mode                      */
            __IOM uint16_t TRXE : 2;   /*!< [15..14] Channel Operation Mode                                           */
        } SCR_b[4];
    };

    union
    {
        __IM uint16_t SE;              /*!< (@ 0x00000120) Serial Channel Enable Status                               */

        struct
        {
            __IM uint16_t SE : 4;      /*!< [3..0] Indication of whether Operation is Enabled or Stopped.             */
            uint16_t         : 12;
        } SE_b;
    };

    union
    {
        __IOM uint16_t SS;             /*!< (@ 0x00000122) Serial Channel Start Register                              */

        struct
        {
            __IOM uint16_t SS : 4;     /*!< [3..0] Operation Start Trigger                                            */
            uint16_t          : 12;
        } SS_b;
    };

    union
    {
        __IOM uint16_t ST;             /*!< (@ 0x00000124) Serial Channel Stop Register                               */

        struct
        {
            __IOM uint16_t ST : 4;     /*!< [3..0] Operation Stop Trigger                                             */
            uint16_t          : 12;
        } ST_b;
    };

    union
    {
        __IOM uint16_t SPS;            /*!< (@ 0x00000126) Serial Clock Select Register                               */

        struct
        {
            __IOM uint16_t PRS0 : 4;   /*!< [3..0] Operation Clock (CK0)                                              */
            __IOM uint16_t PRS1 : 4;   /*!< [7..4] Selection of Operation Clock (CK1)                                 */
            uint16_t            : 8;
        } SPS_b;
    };

    union
    {
        __IOM uint16_t SO;             /*!< (@ 0x00000128) Serial Output Register                                     */

        struct
        {
            __IOM uint16_t SO  : 4;    /*!< [3..0] Serial Data Output                                                 */
            uint16_t           : 4;
            __IOM uint16_t CKO : 4;    /*!< [11..8] Serial Clock Output                                               */
            uint16_t           : 4;
        } SO_b;
    };

    union
    {
        __IOM uint16_t SOE;            /*!< (@ 0x0000012A) Serial Output Enable Register                              */

        struct
        {
            __IOM uint16_t SOE : 4;    /*!< [3..0] Serial Output Enable or Stop                                       */
            uint16_t           : 12;
        } SOE_b;
    };
    __IM uint16_t RESERVED1[4];

    union
    {
        __IOM uint16_t SOL;            /*!< (@ 0x00000134) Serial Output Level Register                               */

        struct
        {
            __IOM uint16_t SOL0 : 1;   /*!< [0..0] Inverts the transmit signal in UART Mode                           */
            uint16_t            : 1;
            __IOM uint16_t SOL2 : 1;   /*!< [2..2] Inverts the transmit signal in UART Mode                           */
            uint16_t            : 13;
        } SOL_b;
    };
    __IM uint16_t RESERVED2;

    union
    {
        __IOM uint16_t SSC;            /*!< (@ 0x00000138) Serial Standby Control Register                            */

        struct
        {
            __IOM uint16_t SWC  : 1;   /*!< [0..0] Snooze Mode                                                        */
            __IOM uint16_t SSEC : 1;   /*!< [1..1] Generation of Communication Error Interrupts in Snooze
                                        *   Mode                                                                      */
            uint16_t : 14;
        } SSC_b;
    };
} R_SAU0_Type;                         /*!< Size = 314 (0x13a)                                                        */

/* =========================================================================================================================== */
/* ================                                          R_SRAM                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief SRAM (R_SRAM)
 */

typedef struct                         /*!< (@ 0x40002000) R_SRAM Structure                                           */
{
    union
    {
        __IOM uint8_t PARIOAD;         /*!< (@ 0x00000000) SRAM Parity Error Operation After Detection Register       */

        struct
        {
            __IOM uint8_t OAD : 1;     /*!< [0..0] Operation after Detection                                          */
            uint8_t           : 7;
        } PARIOAD_b;
    };
    __IM uint8_t RESERVED[3];

    union
    {
        __IOM uint8_t SRAMPRCR;         /*!< (@ 0x00000004) SRAM Protection Register                                   */

        struct
        {
            __IOM uint8_t SRAMPRCR : 1; /*!< [0..0] Register Write Control                                             */
            __OM uint8_t  KW       : 7; /*!< [7..1] Write Key Code                                                     */
        } SRAMPRCR_b;
    };
    __IM uint8_t  RESERVED1[3];
    __IOM uint8_t SRAMWTSC;             /*!< (@ 0x00000008) RAM Wait State Control Register                            */
    __IM uint8_t  RESERVED2[3];

    union
    {
        __IOM uint8_t SRAMPRCR2;         /*!< (@ 0x0000000C) SRAM Protection Register 2                                 */

        struct
        {
            __IOM uint8_t SRAMPRCR2 : 1; /*!< [0..0] Register Write Control                                             */
            __OM uint8_t  KW        : 7; /*!< [7..1] Write Key Code                                                     */
        } SRAMPRCR2_b;
    };
    __IM uint8_t RESERVED3[179];

    union
    {
        __IOM uint8_t ECCMODE;         /*!< (@ 0x000000C0) ECC Operating Mode Control Register                        */

        struct
        {
            __IOM uint8_t ECCMOD : 2;  /*!< [1..0] ECC Operating Mode Select                                          */
            uint8_t              : 6;
        } ECCMODE_b;
    };

    union
    {
        __IOM uint8_t ECC2STS;         /*!< (@ 0x000000C1) ECC 2-Bit Error Status Register                            */

        struct
        {
            __IOM uint8_t ECC2ERR : 1; /*!< [0..0] ECC 2-Bit Error Status                                             */
            uint8_t               : 7;
        } ECC2STS_b;
    };

    union
    {
        __IOM uint8_t ECC1STSEN;       /*!< (@ 0x000000C2) ECC 1-Bit Error Information Update Enable Register         */

        struct
        {
            __IOM uint8_t E1STSEN : 1; /*!< [0..0] ECC 1-Bit Error Information Update Enable                          */
            uint8_t               : 7;
        } ECC1STSEN_b;
    };

    union
    {
        __IOM uint8_t ECC1STS;         /*!< (@ 0x000000C3) ECC 1-Bit Error Status Register                            */

        struct
        {
            __IOM uint8_t ECC1ERR : 1; /*!< [0..0] ECC 1-Bit Error Status                                             */
            uint8_t               : 7;
        } ECC1STS_b;
    };

    union
    {
        __IOM uint8_t ECCPRCR;         /*!< (@ 0x000000C4) ECC Protection Register                                    */

        struct
        {
            __IOM uint8_t ECCPRCR : 1; /*!< [0..0] Register Write Control                                             */
            __OM uint8_t  KW      : 7; /*!< [7..1] Write Key Code                                                     */
        } ECCPRCR_b;
    };
    __IM uint8_t RESERVED4[11];

    union
    {
        __IOM uint8_t ECCPRCR2;         /*!< (@ 0x000000D0) ECC Protection Register 2                                  */

        struct
        {
            __IOM uint8_t ECCPRCR2 : 1; /*!< [0..0] Register Write Control                                             */
            __OM uint8_t  KW2      : 7; /*!< [7..1] Write Key Code                                                     */
        } ECCPRCR2_b;
    };
    __IM uint8_t RESERVED5[3];

    union
    {
        __IOM uint8_t ECCETST;         /*!< (@ 0x000000D4) ECC Test Control Register                                  */

        struct
        {
            __IOM uint8_t TSTBYP : 1;  /*!< [0..0] ECC Bypass Select                                                  */
            uint8_t              : 7;
        } ECCETST_b;
    };
    __IM uint8_t RESERVED6[3];

    union
    {
        __IOM uint8_t ECCOAD;          /*!< (@ 0x000000D8) SRAM ECC Error Operation After Detection Register          */

        struct
        {
            __IOM uint8_t OAD : 1;     /*!< [0..0] Operation after Detection                                          */
            uint8_t           : 7;
        } ECCOAD_b;
    };
} R_SRAM_Type;                         /*!< Size = 217 (0xd9)                                                         */

/* =========================================================================================================================== */
/* ================                                         R_SYSTEM                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief System Control (R_SYSTEM)
 */

typedef struct                         /*!< (@ 0x4001E000) R_SYSTEM Structure                                         */
{
    __IM uint16_t RESERVED[1024];

    union
    {
        __IOM uint8_t CMC;             /*!< (@ 0x00000800) Clock Operation Mode Control Register                      */

        struct
        {
            __IOM uint8_t MODRV : 1;   /*!< [0..0] Main Clock Oscillator Drive Capability Switching                   */
            __IOM uint8_t SODRV : 2;   /*!< [2..1] Sub-Clock Oscillator Drive Capability Switching                    */
            __IOM uint8_t XTSEL : 1;   /*!< [3..3] Selecting Clock Oscillator                                         */
            __IOM uint8_t SOSEL : 1;   /*!< [4..4] Sub Clock Oscillator Switching                                     */
            uint8_t             : 1;
            __IOM uint8_t MOSEL : 2;   /*!< [7..6] Main Clock Oscillator Switching                                    */
        } CMC_b;
    };
    __IM uint8_t RESERVED1[2];

    union
    {
        __IOM uint8_t SOMRG;           /*!< (@ 0x00000803) Sub-clock Oscillator Margin Check Register                 */

        struct
        {
            __IOM uint8_t SOSCMRG : 2; /*!< [1..0] Sub Clock Oscillator Margin Check Switching                        */
            uint8_t               : 6;
        } SOMRG_b;
    };

    union
    {
        __IOM uint8_t MIOTRM;          /*!< (@ 0x00000804) Middle-speed On-chip Oscillator Trimming Register          */

        struct
        {
            __IOM uint8_t MIOTRM : 8;  /*!< [7..0] MOCO User Trimming                                                 */
        } MIOTRM_b;
    };

    union
    {
        __IOM uint8_t LIOTRM;          /*!< (@ 0x00000805) Low-speed On-chip Oscillator Trimming Register             */

        struct
        {
            __IOM uint8_t LIOTRM : 8;  /*!< [7..0] LOCO User Trimming                                                 */
        } LIOTRM_b;
    };
    __IM uint16_t RESERVED2;

    union
    {
        __IOM uint8_t HOCOCR;          /*!< (@ 0x00000808) High-speed On-chip Oscillator Control Register             */

        struct
        {
            __IOM uint8_t HCSTP : 1;   /*!< [0..0] HOCO Stop                                                          */
            uint8_t             : 7;
        } HOCOCR_b;
    };

    union
    {
        __IOM uint8_t MOCOCR;          /*!< (@ 0x00000809) Middle-speed On-chip Oscillator Control Register           */

        struct
        {
            __IOM uint8_t MCSTP : 1;   /*!< [0..0] MOCO Stop                                                          */
            uint8_t             : 7;
        } MOCOCR_b;
    };

    union
    {
        __IOM uint8_t LOCOCR;          /*!< (@ 0x0000080A) Low-speed On-chip Oscillator Control Register              */

        struct
        {
            __IOM uint8_t LCSTP : 1;   /*!< [0..0] LOCO Stop                                                          */
            uint8_t             : 7;
        } LOCOCR_b;
    };

    union
    {
        __IOM uint8_t MOSCCR;          /*!< (@ 0x0000080B) Main Clock Oscillator Control Register                     */

        struct
        {
            __IOM uint8_t MOSTP : 1;   /*!< [0..0] Main Clock Oscillator Stop                                         */
            uint8_t             : 7;
        } MOSCCR_b;
    };

    union
    {
        __IOM uint8_t SOSCCR;          /*!< (@ 0x0000080C) Sub-clock Oscillator Control Register                      */

        struct
        {
            __IOM uint8_t SOSTP : 1;   /*!< [0..0] Sub Clock Oscillator Stop                                          */
            uint8_t             : 7;
        } SOSCCR_b;
    };
    __IM uint8_t  RESERVED3;
    __IM uint16_t RESERVED4;

    union
    {
        __IM uint8_t OSTC;             /*!< (@ 0x00000810) Oscillation Stabilization Time Counter Status
                                        *                  Register                                                   */

        struct
        {
            __IM uint8_t MOST : 8;     /*!< [7..0] Selection of the Oscillation Stabilization Time                    */
        } OSTC_b;
    };

    union
    {
        __IOM uint8_t OSTS;            /*!< (@ 0x00000811) Oscillation Stabilization Time Select Register             */

        struct
        {
            __IOM uint8_t OSTSB : 3;   /*!< [2..0] Selection of the Oscillation Stabilization Time                    */
            uint8_t             : 5;
        } OSTS_b;
    };

    union
    {
        __IM uint8_t OSCSF;            /*!< (@ 0x00000812) Oscillation Stabilization Flag Register                    */

        struct
        {
            __IM uint8_t HOCOSF : 1;   /*!< [0..0] HOCO Clock Oscillation Stabilization Flag                          */
            uint8_t             : 7;
        } OSCSF_b;
    };
    __IM uint8_t  RESERVED5;
    __IM uint16_t RESERVED6[2];

    union
    {
        __IOM uint8_t HOCODIV;         /*!< (@ 0x00000818) High-speed On-chip Oscillator Frequency Select
                                        *                  Register                                                   */

        struct
        {
            __IOM uint8_t DIV : 3;     /*!< [2..0] High-speed On-chip Oscillator Clock Division Ratio                 */
            uint8_t           : 5;
        } HOCODIV_b;
    };

    union
    {
        __IOM uint8_t MOCODIV;         /*!< (@ 0x00000819) Middle-speed On-chip Oscillator Frequency Select
                                        *                  Register                                                   */

        struct
        {
            __IOM uint8_t DIV : 2;     /*!< [1..0] Selection of the Middle-speed On-chip Oscillator Clock
                                        *   Frequency                                                                 */
            uint8_t : 6;
        } MOCODIV_b;
    };

    union
    {
        __IOM uint8_t MOSCDIV;         /*!< (@ 0x0000081A) Main System Clock Division Register                        */

        struct
        {
            __IOM uint8_t DIV : 3;     /*!< [2..0] Selection Division Ratio for the Main System Clock                 */
            uint8_t           : 5;
        } MOSCDIV_b;
    };
    __IM uint8_t  RESERVED7;
    __IM uint16_t RESERVED8[2];

    union
    {
        __IOM uint8_t FOCOSCR;         /*!< (@ 0x00000820) FOCO Clock Source Control Register                         */

        struct
        {
            __IOM uint8_t CKSEL : 1;   /*!< [0..0] FOCO Clock Source Select                                           */
            __IM uint8_t  CKST  : 1;   /*!< [1..1] FOCO Clock Source Status                                           */
            uint8_t             : 6;
        } FOCOSCR_b;
    };

    union
    {
        __IOM uint8_t FMAINSCR;        /*!< (@ 0x00000821) FMAIN Clock Source Control Register                        */

        struct
        {
            __IOM uint8_t CKSEL : 1;   /*!< [0..0] FMAIN Clock Source Select                                          */
            __IM uint8_t  CKST  : 1;   /*!< [1..1] FMAIN Clock Source Status                                          */
            uint8_t             : 6;
        } FMAINSCR_b;
    };

    union
    {
        __IOM uint8_t FSUBSCR;         /*!< (@ 0x00000822) FSUB Clock Source Control Register                         */

        struct
        {
            __IOM uint8_t CKSEL : 1;   /*!< [0..0] FSUB Clock Source Select                                           */
            uint8_t             : 7;
        } FSUBSCR_b;
    };

    union
    {
        __IOM uint8_t ICLKSCR;         /*!< (@ 0x00000823) ICLK Clock Source Control Register                         */

        struct
        {
            __IOM uint8_t CKSEL : 1;   /*!< [0..0] ICLK Clock Source Select                                           */
            __IM uint8_t  CKST  : 1;   /*!< [1..1] ICLK Clock Source Status                                           */
            uint8_t             : 6;
        } ICLKSCR_b;
    };

    union
    {
        __IOM uint8_t OSMC;            /*!< (@ 0x00000824) Subsystem Clock Supply Mode Control Register               */

        struct
        {
            uint8_t                : 4;
            __IOM uint8_t WUTMMCK0 : 1; /*!< [4..4] Selection of the Operating Clock for the Realtime Clock,
                                         *   32-bit Interval Timer, Serial Interfaces UARTA0                           */
            uint8_t : 3;
        } OSMC_b;
    };
    __IM uint8_t  RESERVED9;
    __IM uint16_t RESERVED10[5];

    union
    {
        __IM uint8_t RESF;             /*!< (@ 0x00000830) Reset Control Flag Register                                */

        struct
        {
            __IM uint8_t LVIRF  : 1;   /*!< [0..0] Internal Reset Request by Voltage Detector (LVD0 or LVD1)          */
            uint8_t             : 1;
            __IM uint8_t RPERF  : 1;   /*!< [2..2] Internal Reset Request by RAM Parity Error                         */
            uint8_t             : 1;
            __IM uint8_t IWDTRF : 1;   /*!< [4..4] Internal Reset Request by Independent Watchdog Timer
                                        *   (IWDT)                                                                    */
            __IM uint8_t SWRF : 1;     /*!< [5..5] Internal Reset Request by Software Reset                           */
            uint8_t           : 2;
        } RESF_b;
    };

    union
    {
        __IOM uint8_t PORSR;           /*!< (@ 0x00000831) Power-On Reset Status Register                             */

        struct
        {
            __IOM uint8_t PORF : 1;    /*!< [0..0] Checking Occurrence of Power-on Reset                              */
            uint8_t            : 7;
        } PORSR_b;
    };
    __IM uint16_t RESERVED11[7];

    union
    {
        __IOM uint8_t LVD1CR;          /*!< (@ 0x00000840) Voltage Monitor 1 Circuit Control Register                 */

        struct
        {
            __IOM uint8_t LVD1V   : 5; /*!< [4..0] Voltage Detection 1 Level Select                                   */
            __IOM uint8_t IRQSEL  : 1; /*!< [5..5] Voltage Monitor 1 Interrupt Type Select                            */
            __IOM uint8_t LVD1SEL : 1; /*!< [6..6] Operation mode of LVD1                                             */
            __IOM uint8_t LVD1EN  : 1; /*!< [7..7] Enabling Operation of LVD1                                         */
        } LVD1CR_b;
    };

    union
    {
        __IOM uint8_t LVD1MKR;         /*!< (@ 0x00000841) Voltage Monitor 1 Circuit Mask Register                    */

        struct
        {
            __IOM uint8_t MK : 1;      /*!< [0..0] Specification of Whether to Enable or Disable Rewriting
                                        *   th LVD1CR Register                                                        */
            uint8_t : 7;
        } LVD1MKR_b;
    };
    __IM uint8_t RESERVED12;

    union
    {
        __IOM uint8_t LVD1SR;          /*!< (@ 0x00000843) Voltage Monitor 1 Circuit Status Register                  */

        struct
        {
            __IOM uint8_t DET : 1;     /*!< [0..0] Voltage Monitor 1 Voltage Variation Detection Flag                 */
            __IM uint8_t  MON : 1;     /*!< [1..1] Voltage Monitor 1 Signal Monitor Flag                              */
            uint8_t           : 6;
        } LVD1SR_b;
    };
    __IM uint16_t RESERVED13[14];

    union
    {
        __IOM uint16_t SBYCR;          /*!< (@ 0x00000860) Standby Control Register                                   */

        struct
        {
            uint16_t             : 7;
            __IOM uint16_t FLSTP : 1;  /*!< [7..7] Flash Mode in Sleep Mode or in Snooze Mode                         */
            __IOM uint16_t FWKUP : 1;  /*!< [8..8] Setting for Starting the High-speed On-chip Oscillator
                                        *   at the Times of Release from Software Standby Mode and
                                        *   of Transitions to Snooze Mode                                             */
            __IOM uint16_t RTCLPC : 1; /*!< [9..9] SOSC Setting in Software Standby Mode or in Snooze Mode            */
            uint16_t              : 5;
            __IOM uint16_t SSBY   : 1; /*!< [15..15] Software Standby Mode Select                                     */
        } SBYCR_b;
    };

    union
    {
        __IOM uint8_t PSMCR;           /*!< (@ 0x00000862) Power Save Memory Control Register                         */

        struct
        {
            __IOM uint8_t RAMSD : 2;   /*!< [1..0] Operating Mode of the RAM                                          */
            uint8_t             : 6;
        } PSMCR_b;
    };

    union
    {
        __IOM uint8_t SYOCDCR;         /*!< (@ 0x00000863) System Control OCD Control Register                        */

        struct
        {
            uint8_t             : 7;
            __IOM uint8_t DBGEN : 1;   /*!< [7..7] Debugger Enable bit                                                */
        } SYOCDCR_b;
    };
    __IM uint16_t RESERVED14[77];

    union
    {
        __IOM uint16_t PRCR;           /*!< (@ 0x000008FE) Protect Register                                           */

        struct
        {
            __IOM uint16_t PRC0 : 1;   /*!< [0..0] Enable writing to the registers related to the clock
                                        *   generation circuit                                                        */
            __IOM uint16_t PRC1 : 1;   /*!< [1..1] Enable writing to the registers related to the low power
                                        *   modes                                                                     */
            uint16_t            : 1;
            __IOM uint16_t PRC3 : 1;   /*!< [3..3] Enable writing to the registers related to the LVD                 */
            uint16_t            : 4;
            __OM uint16_t PRKEY : 8;   /*!< [15..8] PRC Key Code                                                      */
        } PRCR_b;
    };
    __IM uint16_t RESERVED15[385];

    union
    {
        __IOM uint16_t MSTPCRA;        /*!< (@ 0x00000C02) Module Stop Control Register A                             */

        struct
        {
            uint16_t               : 6;
            __IOM uint16_t MSTPA22 : 1; /*!< [6..6] DTC Module Stop                                                    */
            uint16_t               : 9;
        } MSTPCRA_b;
    };

    union
    {
        __IOM uint8_t LPOPT;           /*!< (@ 0x00000C04) Lower Power Operation Control Register                     */

        struct
        {
            uint8_t                 : 1;
            __IOM uint8_t DCLKDIS   : 2; /*!< [2..1] Debug Clock Disable Control                                        */
            __IOM uint8_t BPFCLKDIS : 1; /*!< [3..3] BPF Clock Disable Control                                          */
            uint8_t                 : 3;
            __IOM uint8_t LPOPTEN   : 1; /*!< [7..7] Lower Power Operation Enable                                       */
        } LPOPT_b;
    };
    __IM uint8_t  RESERVED16;
    __IM uint16_t RESERVED17;
} R_SYSTEM_Type;                       /*!< Size = 3080 (0xc08)                                                       */

/* =========================================================================================================================== */
/* ================                                           R_TAU                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief Timer Array Unit (R_TAU)
 */

typedef struct                               /*!< (@ 0x400A2600) R_TAU Structure                                            */
{
    __IOM R_TAU_TDR0_Type TDR0[8];           /*!< (@ 0x00000000) Timer Data Registers 0[0..7]                               */
    __IM uint16_t         RESERVED[120];
    __IM uint16_t         TCR0[8];           /*!< (@ 0x00000100) Timer Counter Register 0[0..7]                             */

    union
    {
        __IOM uint16_t TMR0[8];              /*!< (@ 0x00000110) Timer Mode Register 0[0..7]                                */

        struct
        {
            __IOM uint16_t OPIRQ : 1;        /*!< [0..0] Setting of starting count and interrupt                            */
            __IOM uint16_t MD    : 3;        /*!< [3..1] Selection of operation mode at channel n                           */
            uint16_t             : 2;
            __IOM uint16_t CIS   : 2;        /*!< [7..6] Selection of TI0n pin input valid edge                             */
            __IOM uint16_t STS   : 3;        /*!< [10..8] Setting of start trigger or capture trigger of channel
                                              *   n                                                                         */
            __IOM uint16_t MASTER_SPLIT : 1; /*!< [11..11] Selection between using channel n independently or
                                              *   simultaneously with another channel (as a slave or master)                */
            __IOM uint16_t CCS : 1;          /*!< [12..12] Selection of counter clock (fTCLK) of channel n                  */
            uint16_t           : 1;
            __IOM uint16_t CKS : 2;          /*!< [15..14] Selection of operation clock (fMCK) of channel n                 */
        } TMR0_b[8];
    };

    union
    {
        __IM uint16_t TSR0[8];         /*!< (@ 0x00000120) Timer Status Register 0[0..7]                              */

        struct
        {
            __IM uint16_t OVF : 1;     /*!< [0..0] Counter overflow state of channel n                                */
            uint16_t          : 15;
        } TSR0_b[8];
    };

    union
    {
        __IM uint16_t TE0;             /*!< (@ 0x00000130) Timer Channel Enable Status Register 0                     */

        struct
        {
            __IM uint16_t TE : 8;      /*!< [7..0] Indication of operation enabled or stopped state of channel
                                        *   n                                                                         */
            uint16_t           : 1;
            __IM uint16_t TEH1 : 1;    /*!< [9..9] Indication of whether operation of the higher 8-bit timer
                                        *   is enabled or stopped when channel 1 is in the 8-bit timer
                                        *   mode                                                                      */
            uint16_t           : 1;
            __IM uint16_t TEH3 : 1;    /*!< [11..11] Indication of whether operation of the higher 8-bit
                                        *   timer is enabled or stopped when channel 3 is in the 8-bit
                                        *   timer mode                                                                */
            uint16_t : 4;
        } TE0_b;
    };

    union
    {
        __IOM uint16_t TS0;            /*!< (@ 0x00000132) Timer Channel Start Register 0                             */

        struct
        {
            __IOM uint16_t TS   : 8;   /*!< [7..0] Operation enable (start) trigger of channel n                      */
            uint16_t            : 1;
            __IOM uint16_t TSH1 : 1;   /*!< [9..9] Trigger to enable operation (start operation) of the
                                        *   higher 8-bit timer when channel 1 is in the 8-bit timer
                                        *   mode                                                                      */
            uint16_t            : 1;
            __IOM uint16_t TSH3 : 1;   /*!< [11..11] Trigger to enable operation (start operation) of the
                                        *   higher 8-bit timer when channel 3 is in the 8-bit timer
                                        *   mode                                                                      */
            uint16_t : 4;
        } TS0_b;
    };

    union
    {
        __IOM uint16_t TT0;            /*!< (@ 0x00000134) Timer Channel Stop Register 0                              */

        struct
        {
            __IOM uint16_t TT   : 8;   /*!< [7..0] Operation stop trigger of channel n                                */
            uint16_t            : 1;
            __IOM uint16_t TTH1 : 1;   /*!< [9..9] Trigger to stop operation of the higher 8-bit timer when
                                        *   channel 1 is in the 8-bit timer mode                                      */
            uint16_t            : 1;
            __IOM uint16_t TTH3 : 1;   /*!< [11..11] Trigger to stop operation of the higher 8-bit timer
                                        *   when channel 3 is in the 8-bit timer mode                                 */
            uint16_t : 4;
        } TT0_b;
    };

    union
    {
        __IOM uint16_t TPS0;           /*!< (@ 0x00000136) Timer Clock Select Register 0                              */

        struct
        {
            __IOM uint16_t PRS0 : 4;   /*!< [3..0] Selection of operation clock (CK00)                                */
            __IOM uint16_t PRS1 : 4;   /*!< [7..4] Selection of operation clock (CK01)                                */
            __IOM uint16_t PRS2 : 2;   /*!< [9..8] Selection of operation clock (CK02)                                */
            uint16_t            : 2;
            __IOM uint16_t PRS3 : 2;   /*!< [13..12] Selection of operation clock (CK03)                              */
            uint16_t            : 2;
        } TPS0_b;
    };

    union
    {
        __IOM uint16_t TO0;            /*!< (@ 0x00000138) Timer Output Register 0                                    */

        struct
        {
            __IOM uint16_t TO : 8;     /*!< [7..0] Timer output of channel n                                          */
            uint16_t          : 8;
        } TO0_b;
    };

    union
    {
        __IOM uint16_t TOE0;           /*!< (@ 0x0000013A) Timer Output Enable Register 0                             */

        struct
        {
            __IOM uint16_t TOE : 8;    /*!< [7..0] Enabling or disabling timer output for channel n                   */
            uint16_t           : 8;
        } TOE0_b;
    };

    union
    {
        __IOM uint16_t TOL0;           /*!< (@ 0x0000013C) Timer Output Level Register 0                              */

        struct
        {
            uint16_t           : 1;
            __IOM uint16_t TOL : 7;    /*!< [7..1] Control of timer output of channel n                               */
            uint16_t           : 8;
        } TOL0_b;
    };

    union
    {
        __IOM uint16_t TOM0;           /*!< (@ 0x0000013E) Timer Output Mode Register 0                               */

        struct
        {
            uint16_t           : 1;
            __IOM uint16_t TOM : 7;    /*!< [7..1] Control of timer output mode of channel n                          */
            uint16_t           : 8;
        } TOM0_b;
    };
} R_TAU_Type;                          /*!< Size = 320 (0x140)                                                        */

/* =========================================================================================================================== */
/* ================                                          R_TML32                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief 32-bit Interval Timer (R_TML32)
 */

typedef struct                         /*!< (@ 0x400A3800) R_TML32 Structure                                          */
{
    union
    {
        __IOM uint16_t ITLCMP00;       /*!< (@ 0x00000000) Interval Timer Compare Registers 00                        */

        struct
        {
            __IOM uint8_t ITLCMP00_L;  /*!< (@ 0x00000000) Interval Timer Compare Registers 00                        */
            __IOM uint8_t ITLCMP00_H;  /*!< (@ 0x00000001) Interval Timer Compare Registers 00                        */
        };
    };

    union
    {
        __IOM uint16_t ITLCMP01;       /*!< (@ 0x00000002) Interval Timer Compare Registers 01                        */

        struct
        {
            __IOM uint8_t ITLCMP01_L;  /*!< (@ 0x00000002) Interval Timer Compare Registers 01                        */
            __IOM uint8_t ITLCMP01_H;  /*!< (@ 0x00000003) Interval Timer Compare Registers 01                        */
        };
    };
    __IM uint16_t ITLCAP00;            /*!< (@ 0x00000004) Interval Timer Capture Register 00                         */

    union
    {
        __IOM uint8_t ITLCTL0;         /*!< (@ 0x00000006) Interval Timer Control Register                            */

        struct
        {
            __IOM uint8_t EN0 : 1;     /*!< [0..0] 8-bit Counter Mode: ITL000 Count Enable                            */
            __IOM uint8_t EN1 : 1;     /*!< [1..1] 8-bit Counter Mode: ITL001 Count Enable                            */
            __IOM uint8_t EN2 : 1;     /*!< [2..2] 8-bit Counter Mode: ITL012 Count Enable                            */
            __IOM uint8_t EN3 : 1;     /*!< [3..3] 8-bit Counter Mode: ITL013 Count Enable                            */
            uint8_t           : 2;
            __IOM uint8_t MD  : 2;     /*!< [7..6] Selection of 8-bit, 16-bit, or 32-bit Counter Mode                 */
        } ITLCTL0_b;
    };

    union
    {
        __IOM uint8_t ITLCSEL0;        /*!< (@ 0x00000007) Interval Timer Clock Select Register 0                     */

        struct
        {
            __IOM uint8_t ISEL : 3;    /*!< [2..0] Selection of Interval Timer Count Clock (fITL0)                    */
            uint8_t            : 1;
            __IOM uint8_t CSEL : 3;    /*!< [6..4] Selection of Interval Timer Count Clock for Capturing
                                        *   (fITL1)                                                                   */
            uint8_t : 1;
        } ITLCSEL0_b;
    };

    union
    {
        __IOM uint8_t ITLFDIV00;       /*!< (@ 0x00000008) Interval Timer Frequency Division Register 0               */

        struct
        {
            __IOM uint8_t FDIV0 : 3;   /*!< [2..0] 8-bit Counter Mode: Counter Clock for ITL000                       */
            uint8_t             : 1;
            __IOM uint8_t FDIV1 : 3;   /*!< [6..4] 8-bit Counter Mode: Counter Clock for ITL001                       */
            uint8_t             : 1;
        } ITLFDIV00_b;
    };

    union
    {
        __IOM uint8_t ITLFDIV01;       /*!< (@ 0x00000009) Interval Timer Frequency Division Register 1               */

        struct
        {
            __IOM uint8_t FDIV2 : 3;   /*!< [2..0] 8-bit Counter Mode: Counter Clock for ITL012                       */
            uint8_t             : 1;
            __IOM uint8_t FDIV3 : 3;   /*!< [6..4] 8-bit Counter Mode: Counter Clock for ITL013                       */
            uint8_t             : 1;
        } ITLFDIV01_b;
    };

    union
    {
        __IOM uint8_t ITLCC0;          /*!< (@ 0x0000000A) Interval Timer Capture Control Register 0                  */

        struct
        {
            __IOM uint8_t CTRS   : 2;  /*!< [1..0] Selection of Capture Trigger                                       */
            uint8_t              : 1;
            __IOM uint8_t CAPCCR : 1;  /*!< [3..3] Selection of Capture Counter Clearing After Capturing              */
            __IOM uint8_t CAPR   : 1;  /*!< [4..4] Software Capture Trigger                                           */
            __IM uint8_t  CAPF   : 1;  /*!< [5..5] Capture Completion Flag                                            */
            __IOM uint8_t CAPFCR : 1;  /*!< [6..6] Capture Completion Flag Clear                                      */
            __IOM uint8_t CAPEN  : 1;  /*!< [7..7] Capture Enable                                                     */
        } ITLCC0_b;
    };

    union
    {
        __IOM uint8_t ITLS0;           /*!< (@ 0x0000000B) Interval Timer Status Register                             */

        struct
        {
            __IOM uint8_t ITF00 : 1;   /*!< [0..0] Compare Match Detection Flag for Channel 0                         */
            __IOM uint8_t ITF01 : 1;   /*!< [1..1] Compare Match Detection Flag for Channel 1                         */
            __IOM uint8_t ITF02 : 1;   /*!< [2..2] Compare Match Detection Flag for Channel 2                         */
            __IOM uint8_t ITF03 : 1;   /*!< [3..3] Compare Match Detection Flag for Channel 3                         */
            __IOM uint8_t ITF0C : 1;   /*!< [4..4] Capture Detection Flag                                             */
            uint8_t             : 3;
        } ITLS0_b;
    };

    union
    {
        __IOM uint8_t ITLMKF0;         /*!< (@ 0x0000000C) Interval Timer Match Detection Mask Register               */

        struct
        {
            __IOM uint8_t MKF00 : 1;   /*!< [0..0] Mask for Compare Match Status Flag for Channel 0                   */
            __IOM uint8_t MKF01 : 1;   /*!< [1..1] Mask for Compare Match Status Flag for Channel 1                   */
            __IOM uint8_t MKF02 : 1;   /*!< [2..2] Mask for Compare Match Status Flag for Channel 2                   */
            __IOM uint8_t MKF03 : 1;   /*!< [3..3] Mask for Compare Match Status Flag for Channel 3                   */
            __IOM uint8_t MKF0C : 1;   /*!< [4..4] Mask for Capture Detection Status Flag                             */
            uint8_t             : 3;
        } ITLMKF0_b;
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1;
} R_TML32_Type;                        /*!< Size = 16 (0x10)                                                          */

/* =========================================================================================================================== */
/* ================                                          R_TRNG                                           ================ */
/* =========================================================================================================================== */

/**
 * @brief True Random Number Generator (R_TRNG)
 */

typedef struct                         /*!< (@ 0x400D1000) R_TRNG Structure                                           */
{
    union
    {
        __IM uint8_t TRNGSDR;          /*!< (@ 0x00000000) TRNG SEED Data Register                                    */

        struct
        {
            __IM uint8_t SDATA : 8;    /*!< [7..0] When RDRDY bit is 1, these bits hold the generated SEED.
                                        *   When RDRDY bit is 0, these bits are read as 00h.The SEED
                                        *   is generated as 32-bit data. When TRNGSDR is read 4 times
                                        *   while RDRDY = 1, SEED reading is completed and RDRDY bit
                                        *   changes to 0                                                              */
        } TRNGSDR_b;
    };
    __IM uint8_t RESERVED;

    union
    {
        __IOM uint8_t TRNGSCR0;        /*!< (@ 0x00000002) TRNG SEED Command Register 0                               */

        struct
        {
            uint8_t               : 2;
            __OM uint8_t  SGSTART : 1; /*!< [2..2] SEED Generation Start                                              */
            __IOM uint8_t SGCEN   : 1; /*!< [3..3] SEED Generation Circuit Enable                                     */
            uint8_t               : 3;
            __IM uint8_t RDRDY    : 1; /*!< [7..7] When SEED geenration is completed, this bit changes to
                                        *   0                                                                         */
        } TRNGSCR0_b;
    };

    union
    {
        __IOM uint8_t TRNGSCR1;        /*!< (@ 0x00000003) TRNG SEED Command Register 1                               */

        struct
        {
            __IOM uint8_t INTEN : 1;   /*!< [0..0] TRNG Interrupt Enable                                              */
            uint8_t             : 7;
        } TRNGSCR1_b;
    };
} R_TRNG_Type;                         /*!< Size = 4 (0x4)                                                            */

/* =========================================================================================================================== */
/* ================                                          R_UARTA                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief Serial Interface UARTA (R_UARTA)
 */

typedef struct                         /*!< (@ 0x400A3400) R_UARTA Structure                                          */
{
    __IOM uint8_t TXBA0;               /*!< (@ 0x00000000) Transmit Buffer Register 0                                 */
    __IM uint8_t  RXBA0;               /*!< (@ 0x00000001) Receive Buffer Register 0                                  */

    union
    {
        __IOM uint8_t ASIMA00;         /*!< (@ 0x00000002) Operation Mode Setting Register 00                         */

        struct
        {
            __IOM uint8_t ISRMA : 1;   /*!< [0..0] Receive Interrupt Mode Select                                      */
            __IOM uint8_t ISSMA : 1;   /*!< [1..1] Transmit Interrupt Mode Select                                     */
            uint8_t             : 3;
            __IOM uint8_t RXEA  : 1;   /*!< [5..5] Reception Enable                                                   */
            __IOM uint8_t TXEA  : 1;   /*!< [6..6] Transmission Enable                                                */
            __IOM uint8_t EN    : 1;   /*!< [7..7] UART Operation Enable                                              */
        } ASIMA00_b;
    };

    union
    {
        __IOM uint8_t ASIMA01;         /*!< (@ 0x00000003) Operation Mode Setting Register 01                         */

        struct
        {
            __IOM uint8_t ALV : 1;     /*!< [0..0] Transmission and Reception Level Setting                           */
            __IOM uint8_t DIR : 1;     /*!< [1..1] Transmission and Reception Order Setting                           */
            __IOM uint8_t SL  : 1;     /*!< [2..2] Transmission Stop Bit Length Setting                               */
            __IOM uint8_t CL  : 2;     /*!< [4..3] Transmission and Reception Character Length Setting                */
            __IOM uint8_t PS  : 2;     /*!< [6..5] Transmission and Reception Parity Bit Setting                      */
            uint8_t           : 1;
        } ASIMA01_b;
    };
    __IOM uint8_t BRGCA0;              /*!< (@ 0x00000004) Baud Rate Generator Control Register 0                     */

    union
    {
        __IM uint8_t ASISA0;           /*!< (@ 0x00000005) Status Register 0                                          */

        struct
        {
            __IM uint8_t OVEA  : 1;    /*!< [0..0] Overrun Error Flag                                                 */
            __IM uint8_t FEA   : 1;    /*!< [1..1] Framing Error Flag                                                 */
            __IM uint8_t PEA   : 1;    /*!< [2..2] Parity Error Flag                                                  */
            uint8_t            : 1;
            __IM uint8_t TXSFA : 1;    /*!< [4..4] Transmit Shift Register Data Flag                                  */
            __IM uint8_t TXBFA : 1;    /*!< [5..5] Transmit Buffer Data Flag                                          */
            uint8_t            : 2;
        } ASISA0_b;
    };

    union
    {
        __IOM uint8_t ASCTA0;          /*!< (@ 0x00000006) Status Clear Trigger Register 0                            */

        struct
        {
            __IOM uint8_t OVECTA : 1;  /*!< [0..0] Overrun Error Flag Clear Trigger                                   */
            __IOM uint8_t FECTA  : 1;  /*!< [1..1] Framing Error Flag Clear Trigger                                   */
            __IOM uint8_t PECTA  : 1;  /*!< [2..2] Parity Error Flag Clear Trigger                                    */
            uint8_t              : 5;
        } ASCTA0_b;
    };
    __IM uint8_t RESERVED[249];

    union
    {
        __IOM uint8_t UTA0CK;          /*!< (@ 0x00000100) UARTA Clock Select Register 0                              */

        struct
        {
            __IOM uint8_t CK  : 4;     /*!< [3..0] UARTA0 Operation Clock Select (fUTA0)                              */
            __IOM uint8_t SEL : 2;     /*!< [5..4] fSEL Clock Select                                                  */
            uint8_t           : 2;
        } UTA0CK_b;
    };
} R_UARTA_Type;                        /*!< Size = 257 (0x101)                                                        */

/* =========================================================================================================================== */
/* ================                                         R_PCLBUZ                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief Clock Output/Buzzer Output Controller (R_PCLBUZ)
 */

typedef struct                         /*!< (@ 0x400A3B00) R_PCLBUZ Structure                                         */
{
    __IM uint8_t RESERVED;

    union
    {
        __IOM uint8_t CKS0;            /*!< (@ 0x00000001) Clock Out Control Register 0                               */

        struct
        {
            __IOM uint8_t CCS   : 3;   /*!< [2..0] Clock Out Divide Select                                            */
            __IOM uint8_t CSEL  : 1;   /*!< [3..3] Clock Out Select                                                   */
            uint8_t             : 3;
            __IOM uint8_t PCLOE : 1;   /*!< [7..7] Clock Out Enable                                                   */
        } CKS0_b;
    };
} R_PCLBUZ_Type;                       /*!< Size = 2 (0x2)                                                            */

/* =========================================================================================================================== */
/* ================                                          R_RTC_C                                          ================ */
/* =========================================================================================================================== */

/**
 * @brief Real Time Clock (R_RTC_C)
 */

typedef struct                         /*!< (@ 0x400A2C00) R_RTC_C Structure                                          */
{
    union
    {
        __IOM uint8_t SEC;             /*!< (@ 0x00000000) Second Count Register                                      */

        struct
        {
            __IOM uint8_t SEC1  : 4;   /*!< [3..0] 1-second count                                                     */
            __IOM uint8_t SEC10 : 3;   /*!< [6..4] 10-second count                                                    */
            uint8_t             : 1;
        } SEC_b;
    };

    union
    {
        __IOM uint8_t MIN;             /*!< (@ 0x00000001) Minute Count Register                                      */

        struct
        {
            __IOM uint8_t MIN1  : 4;   /*!< [3..0] 1-minute count                                                     */
            __IOM uint8_t MIN10 : 3;   /*!< [6..4] 10- minute count                                                   */
            uint8_t             : 1;
        } MIN_b;
    };

    union
    {
        __IOM uint8_t HOUR;            /*!< (@ 0x00000002) Hour Count Register                                        */

        struct
        {
            __IOM uint8_t HOUR1  : 4;  /*!< [3..0] 1-hour count                                                       */
            __IOM uint8_t HOUR10 : 2;  /*!< [5..4] 10-hour count                                                      */
            uint8_t              : 2;
        } HOUR_b;
    };

    union
    {
        __IOM uint8_t WEEK;            /*!< (@ 0x00000003) Day-of-Week Count Register                                 */

        struct
        {
            __IOM uint8_t WEEK : 3;    /*!< [2..0] Day-of-Week Counting                                               */
            uint8_t            : 5;
        } WEEK_b;
    };

    union
    {
        __IOM uint8_t DAY;             /*!< (@ 0x00000004) Day Count Register                                         */

        struct
        {
            __IOM uint8_t DAY1  : 4;   /*!< [3..0] 1-day count                                                        */
            __IOM uint8_t DAY10 : 2;   /*!< [5..4] 10-day count                                                       */
            uint8_t             : 2;
        } DAY_b;
    };

    union
    {
        __IOM uint8_t MONTH;           /*!< (@ 0x00000005) Month Count Register                                       */

        struct
        {
            __IOM uint8_t MONTH1  : 4; /*!< [3..0] 1-month count                                                      */
            __IOM uint8_t MONTH10 : 1; /*!< [4..4] 10-month count                                                     */
            uint8_t               : 3;
        } MONTH_b;
    };

    union
    {
        __IOM uint8_t YEAR;            /*!< (@ 0x00000006) Year Count Register                                        */

        struct
        {
            __IOM uint8_t YEAR1  : 4;  /*!< [3..0] 1-year count                                                       */
            __IOM uint8_t YEAR10 : 4;  /*!< [7..4] 10-year count                                                      */
        } YEAR_b;
    };

    union
    {
        __IOM uint8_t SUBCUD;          /*!< (@ 0x00000007) Time Error Correction Register                             */

        struct
        {
            __IOM uint8_t F   : 6;     /*!< [5..0] Adjustment Value                                                   */
            __IOM uint8_t F6  : 1;     /*!< [6..6] Setting of time error correction value                             */
            __IOM uint8_t DEV : 1;     /*!< [7..7] Setting of time error correction timing                            */
        } SUBCUD_b;
    };

    union
    {
        __IOM uint8_t ALARMWM;         /*!< (@ 0x00000008) Alarm Minute Register                                      */

        struct
        {
            __IOM uint8_t WM1  : 4;    /*!< [3..0] 1-digit minute setting                                             */
            __IOM uint8_t WM10 : 3;    /*!< [6..4] 10-digit minute setting                                            */
            uint8_t            : 1;
        } ALARMWM_b;
    };

    union
    {
        __IOM uint8_t ALARMWH;         /*!< (@ 0x00000009) Alarm Hour Register                                        */

        struct
        {
            __IOM uint8_t WH1  : 4;    /*!< [3..0] 1-digit hour setting                                               */
            __IOM uint8_t WH10 : 2;    /*!< [5..4] 10-digit hour setting                                              */
            uint8_t            : 2;
        } ALARMWH_b;
    };

    union
    {
        __IOM uint8_t ALARMWW;         /*!< (@ 0x0000000A) Alarm Day-of-Week Register                                 */

        struct
        {
            __IOM uint8_t WW0 : 1;     /*!< [0..0] Alarm enabled setting 'Sunday'                                     */
            __IOM uint8_t WW1 : 1;     /*!< [1..1] Alarm enabled setting 'Monday'                                     */
            __IOM uint8_t WW2 : 1;     /*!< [2..2] Alarm enabled setting 'Tuesday'                                    */
            __IOM uint8_t WW3 : 1;     /*!< [3..3] Alarm enabled setting 'Wednesday'                                  */
            __IOM uint8_t WW4 : 1;     /*!< [4..4] Alarm enabled setting 'Thursday'                                   */
            __IOM uint8_t WW5 : 1;     /*!< [5..5] Alarm enabled setting 'Friday'                                     */
            __IOM uint8_t WW6 : 1;     /*!< [6..6] Alarm enabled setting 'Saturday'                                   */
            uint8_t           : 1;
        } ALARMWW_b;
    };

    union
    {
        __IOM uint8_t RTCC0;            /*!< (@ 0x0000000B) Realtime Clock Control Register 0                          */

        struct
        {
            __IOM uint8_t CT       : 3; /*!< [2..0] Fixed-cycle interrupt (RTC_ALM_OR_PRD) selection                   */
            __IOM uint8_t AMPM     : 1; /*!< [3..3] Selection of 12- or 24-hour system                                 */
            __IOM uint8_t RTC128EN : 1; /*!< [4..4] Selection of the operating clock for the realtime clock
                                         *   (RTCCLK)                                                                  */
            __IOM uint8_t RCLOE1 : 1;   /*!< [5..5] RTCOUT pin output control                                          */
            uint8_t              : 1;
            __IOM uint8_t RTCE   : 1;   /*!< [7..7] Realtime clock operation control                                   */
        } RTCC0_b;
    };

    union
    {
        __IOM uint8_t RTCC1;           /*!< (@ 0x0000000C) Realtime Clock Control Register 1                          */

        struct
        {
            __IOM uint8_t RWAIT : 1;   /*!< [0..0] Wait control of realtime clock                                     */
            __IM uint8_t  RWST  : 1;   /*!< [1..1] Wait status flag of realtime clock                                 */
            uint8_t             : 1;
            __IOM uint8_t RIFG  : 1;   /*!< [3..3] Fixed-cycle interrupt status flag                                  */
            __IOM uint8_t WAFG  : 1;   /*!< [4..4] Alarm detection status flag                                        */
            uint8_t             : 1;
            __IOM uint8_t WALIE : 1;   /*!< [6..6] Control of alarm interrupt (RTC_ALM_OR_PRD)                        */
            __IOM uint8_t WALE  : 1;   /*!< [7..7] Alarm operation control                                            */
        } RTCC1_b;
    };
} R_RTC_C_Type;                        /*!< Size = 13 (0xd)                                                           */

/** @} */ /* End of group Device_Peripheral_peripherals */

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripheralAddr
 * @{
 */

 #define R_ADC_D_BASE      0x400A1800UL
 #define R_BUS_BASE        0x40003000UL
 #define R_CRC_BASE        0x40074000UL
 #define R_DEBUG_BASE      0x4001B000UL
 #define R_DTC_BASE        0x40005400UL
 #define R_ELC_BASE        0x40041000UL
 #define R_FACI_LP_BASE    0x407EC000UL
 #define R_ICU_BASE        0x40006000UL
 #define R_IICA_BASE       0x400A3000UL
 #define R_IWDT_BASE       0x40044400UL
 #define R_MSTP_BASE       (0x40047000UL - 4UL) /* MSTPCRA is not located in R_MSTP so the base address must be moved so that MSTPCRB is located at 0x40047000. */
 #define R_PORT0_BASE      0x400A0000UL
 #define R_PORT1_BASE      0x400A0020UL
 #define R_PORT2_BASE      0x400A0040UL
 #define R_PORT3_BASE      0x400A0060UL
 #define R_PORT4_BASE      0x400A0080UL
 #define R_PORT9_BASE      0x400A0100UL
 #define R_PORGA_BASE      0x400A1000UL
 #define R_PFS_BASE        0x400A0200UL
 #define R_PMISC_BASE      0x400A0340UL
 #define R_SAU0_BASE       0x400A2000UL
 #define R_SAU1_BASE       0x400A2200UL
 #define R_SRAM_BASE       0x40002000UL
 #define R_SYSTEM_BASE     0x4001E000UL
 #define R_TAU_BASE        0x400A2600UL
 #define R_TML32_BASE      0x400A3800UL
 #define R_TRNG_BASE       0x400D1000UL
 #define R_UARTA_BASE      0x400A3400UL
 #define R_PCLBUZ_BASE     0x400A3B00UL
 #define R_RTC_C_BASE      0x400A2C00UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
 * @{
 */

 #define R_ADC_D      ((R_ADC_D_Type *) R_ADC_D_BASE)
 #define R_BUS        ((R_BUS_Type *) R_BUS_BASE)
 #define R_CRC        ((R_CRC_Type *) R_CRC_BASE)
 #define R_DEBUG      ((R_DEBUG_Type *) R_DEBUG_BASE)
 #define R_DTC        ((R_DTC_Type *) R_DTC_BASE)
 #define R_ELC        ((R_ELC_Type *) R_ELC_BASE)
 #define R_FACI_LP    ((R_FACI_LP_Type *) R_FACI_LP_BASE)
 #define R_ICU        ((R_ICU_Type *) R_ICU_BASE)
 #define R_IICA       ((R_IICA_Type *) R_IICA_BASE)
 #define R_IWDT       ((R_IWDT_Type *) R_IWDT_BASE)
 #define R_MSTP       ((R_MSTP_Type *) R_MSTP_BASE)
 #define R_PORT0      ((R_PORT0_Type *) R_PORT0_BASE)
 #define R_PORT1      ((R_PORT0_Type *) R_PORT1_BASE)
 #define R_PORT2      ((R_PORT0_Type *) R_PORT2_BASE)
 #define R_PORT3      ((R_PORT0_Type *) R_PORT3_BASE)
 #define R_PORT4      ((R_PORT0_Type *) R_PORT4_BASE)
 #define R_PORT9      ((R_PORT0_Type *) R_PORT9_BASE)
 #define R_PORGA      ((R_PORGA_Type *) R_PORGA_BASE)
 #define R_PFS        ((R_PFS_Type *) R_PFS_BASE)
 #define R_PMISC      ((R_PMISC_Type *) R_PMISC_BASE)
 #define R_SAU0       ((R_SAU0_Type *) R_SAU0_BASE)
 #define R_SAU1       ((R_SAU0_Type *) R_SAU1_BASE)
 #define R_SRAM       ((R_SRAM_Type *) R_SRAM_BASE)
 #define R_SYSTEM     ((R_SYSTEM_Type *) R_SYSTEM_BASE)
 #define R_TAU        ((R_TAU_Type *) R_TAU_BASE)
 #define R_TML32      ((R_TML32_Type *) R_TML32_BASE)
 #define R_TRNG       ((R_TRNG_Type *) R_TRNG_BASE)
 #define R_UARTA      ((R_UARTA_Type *) R_UARTA_BASE)
 #define R_PCLBUZ     ((R_PCLBUZ_Type *) R_PCLBUZ_BASE)
 #define R_RTC_C      ((R_RTC_C_Type *) R_RTC_C_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */

/* =========================================  End of section using anonymous unions  ========================================= */
 #if defined(__CC_ARM)
  #pragma pop
 #elif defined(__ICCARM__)

/* leave anonymous unions enabled */
 #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
 #elif defined(__GNUC__)

/* anonymous unions are enabled by default */
 #elif defined(__TMS470__)

/* anonymous unions are enabled by default */
 #elif defined(__TASKING__)
  #pragma warning restore
 #elif defined(__CSMC__)

/* anonymous unions are enabled by default */
 #endif

/* =========================================================================================================================== */
/* ================                                 Pos/Mask Cluster Section                                  ================ */
/* =========================================================================================================================== */

/** @addtogroup PosMask_clusters
 * @{
 */

/* =========================================================================================================================== */
/* ================                                            CSa                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  MOD  ========================================================== */
 #define R_BUS_CSa_MOD_PRMOD_Pos        (15UL)         /*!< PRMOD (Bit 15)                                        */
 #define R_BUS_CSa_MOD_PRMOD_Msk        (0x8000UL)     /*!< PRMOD (Bitfield-Mask: 0x01)                           */
 #define R_BUS_CSa_MOD_PWENB_Pos        (9UL)          /*!< PWENB (Bit 9)                                         */
 #define R_BUS_CSa_MOD_PWENB_Msk        (0x200UL)      /*!< PWENB (Bitfield-Mask: 0x01)                           */
 #define R_BUS_CSa_MOD_PRENB_Pos        (8UL)          /*!< PRENB (Bit 8)                                         */
 #define R_BUS_CSa_MOD_PRENB_Msk        (0x100UL)      /*!< PRENB (Bitfield-Mask: 0x01)                           */
 #define R_BUS_CSa_MOD_EWENB_Pos        (3UL)          /*!< EWENB (Bit 3)                                         */
 #define R_BUS_CSa_MOD_EWENB_Msk        (0x8UL)        /*!< EWENB (Bitfield-Mask: 0x01)                           */
 #define R_BUS_CSa_MOD_WRMOD_Pos        (0UL)          /*!< WRMOD (Bit 0)                                         */
 #define R_BUS_CSa_MOD_WRMOD_Msk        (0x1UL)        /*!< WRMOD (Bitfield-Mask: 0x01)                           */
/* =========================================================  WCR1  ========================================================== */
 #define R_BUS_CSa_WCR1_CSRWAIT_Pos     (24UL)         /*!< CSRWAIT (Bit 24)                                      */
 #define R_BUS_CSa_WCR1_CSRWAIT_Msk     (0x1f000000UL) /*!< CSRWAIT (Bitfield-Mask: 0x1f)                         */
 #define R_BUS_CSa_WCR1_CSWWAIT_Pos     (16UL)         /*!< CSWWAIT (Bit 16)                                      */
 #define R_BUS_CSa_WCR1_CSWWAIT_Msk     (0x1f0000UL)   /*!< CSWWAIT (Bitfield-Mask: 0x1f)                         */
 #define R_BUS_CSa_WCR1_CSPRWAIT_Pos    (8UL)          /*!< CSPRWAIT (Bit 8)                                      */
 #define R_BUS_CSa_WCR1_CSPRWAIT_Msk    (0x700UL)      /*!< CSPRWAIT (Bitfield-Mask: 0x07)                        */
 #define R_BUS_CSa_WCR1_CSPWWAIT_Pos    (0UL)          /*!< CSPWWAIT (Bit 0)                                      */
 #define R_BUS_CSa_WCR1_CSPWWAIT_Msk    (0x7UL)        /*!< CSPWWAIT (Bitfield-Mask: 0x07)                        */
/* =========================================================  WCR2  ========================================================== */
 #define R_BUS_CSa_WCR2_CSON_Pos        (28UL)         /*!< CSON (Bit 28)                                         */
 #define R_BUS_CSa_WCR2_CSON_Msk        (0x70000000UL) /*!< CSON (Bitfield-Mask: 0x07)                            */
 #define R_BUS_CSa_WCR2_WDON_Pos        (24UL)         /*!< WDON (Bit 24)                                         */
 #define R_BUS_CSa_WCR2_WDON_Msk        (0x7000000UL)  /*!< WDON (Bitfield-Mask: 0x07)                            */
 #define R_BUS_CSa_WCR2_WRON_Pos        (20UL)         /*!< WRON (Bit 20)                                         */
 #define R_BUS_CSa_WCR2_WRON_Msk        (0x700000UL)   /*!< WRON (Bitfield-Mask: 0x07)                            */
 #define R_BUS_CSa_WCR2_RDON_Pos        (16UL)         /*!< RDON (Bit 16)                                         */
 #define R_BUS_CSa_WCR2_RDON_Msk        (0x70000UL)    /*!< RDON (Bitfield-Mask: 0x07)                            */
 #define R_BUS_CSa_WCR2_AWAIT_Pos       (12UL)         /*!< AWAIT (Bit 12)                                        */
 #define R_BUS_CSa_WCR2_AWAIT_Msk       (0x3000UL)     /*!< AWAIT (Bitfield-Mask: 0x03)                           */
 #define R_BUS_CSa_WCR2_WDOFF_Pos       (8UL)          /*!< WDOFF (Bit 8)                                         */
 #define R_BUS_CSa_WCR2_WDOFF_Msk       (0x700UL)      /*!< WDOFF (Bitfield-Mask: 0x07)                           */
 #define R_BUS_CSa_WCR2_CSWOFF_Pos      (4UL)          /*!< CSWOFF (Bit 4)                                        */
 #define R_BUS_CSa_WCR2_CSWOFF_Msk      (0x70UL)       /*!< CSWOFF (Bitfield-Mask: 0x07)                          */
 #define R_BUS_CSa_WCR2_CSROFF_Pos      (0UL)          /*!< CSROFF (Bit 0)                                        */
 #define R_BUS_CSa_WCR2_CSROFF_Msk      (0x7UL)        /*!< CSROFF (Bitfield-Mask: 0x07)                          */

/* =========================================================================================================================== */
/* ================                                            CSb                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
 #define R_BUS_CSb_CR_MPXEN_Pos    (12UL)     /*!< MPXEN (Bit 12)                                        */
 #define R_BUS_CSb_CR_MPXEN_Msk    (0x1000UL) /*!< MPXEN (Bitfield-Mask: 0x01)                           */
 #define R_BUS_CSb_CR_EMODE_Pos    (8UL)      /*!< EMODE (Bit 8)                                         */
 #define R_BUS_CSb_CR_EMODE_Msk    (0x100UL)  /*!< EMODE (Bitfield-Mask: 0x01)                           */
 #define R_BUS_CSb_CR_BSIZE_Pos    (4UL)      /*!< BSIZE (Bit 4)                                         */
 #define R_BUS_CSb_CR_BSIZE_Msk    (0x30UL)   /*!< BSIZE (Bitfield-Mask: 0x03)                           */
 #define R_BUS_CSb_CR_EXENB_Pos    (0UL)      /*!< EXENB (Bit 0)                                         */
 #define R_BUS_CSb_CR_EXENB_Msk    (0x1UL)    /*!< EXENB (Bitfield-Mask: 0x01)                           */
/* ==========================================================  REC  ========================================================== */
 #define R_BUS_CSb_REC_WRCV_Pos    (8UL)      /*!< WRCV (Bit 8)                                          */
 #define R_BUS_CSb_REC_WRCV_Msk    (0xf00UL)  /*!< WRCV (Bitfield-Mask: 0x0f)                            */
 #define R_BUS_CSb_REC_RRCV_Pos    (0UL)      /*!< RRCV (Bit 0)                                          */
 #define R_BUS_CSb_REC_RRCV_Msk    (0xfUL)    /*!< RRCV (Bitfield-Mask: 0x0f)                            */

/* =========================================================================================================================== */
/* ================                                           SDRAM                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  SDCCR  ========================================================= */
 #define R_BUS_SDRAM_SDCCR_BSIZE_Pos     (4UL)       /*!< BSIZE (Bit 4)                                         */
 #define R_BUS_SDRAM_SDCCR_BSIZE_Msk     (0x30UL)    /*!< BSIZE (Bitfield-Mask: 0x03)                           */
 #define R_BUS_SDRAM_SDCCR_EXENB_Pos     (0UL)       /*!< EXENB (Bit 0)                                         */
 #define R_BUS_SDRAM_SDCCR_EXENB_Msk     (0x1UL)     /*!< EXENB (Bitfield-Mask: 0x01)                           */
/* ========================================================  SDCMOD  ========================================================= */
 #define R_BUS_SDRAM_SDCMOD_EMODE_Pos    (0UL)       /*!< EMODE (Bit 0)                                         */
 #define R_BUS_SDRAM_SDCMOD_EMODE_Msk    (0x1UL)     /*!< EMODE (Bitfield-Mask: 0x01)                           */
/* ========================================================  SDAMOD  ========================================================= */
 #define R_BUS_SDRAM_SDAMOD_BE_Pos       (0UL)       /*!< BE (Bit 0)                                            */
 #define R_BUS_SDRAM_SDAMOD_BE_Msk       (0x1UL)     /*!< BE (Bitfield-Mask: 0x01)                              */
/* ========================================================  SDSELF  ========================================================= */
 #define R_BUS_SDRAM_SDSELF_SFEN_Pos     (0UL)       /*!< SFEN (Bit 0)                                          */
 #define R_BUS_SDRAM_SDSELF_SFEN_Msk     (0x1UL)     /*!< SFEN (Bitfield-Mask: 0x01)                            */
/* ========================================================  SDRFCR  ========================================================= */
 #define R_BUS_SDRAM_SDRFCR_REFW_Pos     (12UL)      /*!< REFW (Bit 12)                                         */
 #define R_BUS_SDRAM_SDRFCR_REFW_Msk     (0xf000UL)  /*!< REFW (Bitfield-Mask: 0x0f)                            */
 #define R_BUS_SDRAM_SDRFCR_RFC_Pos      (0UL)       /*!< RFC (Bit 0)                                           */
 #define R_BUS_SDRAM_SDRFCR_RFC_Msk      (0xfffUL)   /*!< RFC (Bitfield-Mask: 0xfff)                            */
/* ========================================================  SDRFEN  ========================================================= */
 #define R_BUS_SDRAM_SDRFEN_RFEN_Pos     (0UL)       /*!< RFEN (Bit 0)                                          */
 #define R_BUS_SDRAM_SDRFEN_RFEN_Msk     (0x1UL)     /*!< RFEN (Bitfield-Mask: 0x01)                            */
/* =========================================================  SDICR  ========================================================= */
 #define R_BUS_SDRAM_SDICR_INIRQ_Pos     (0UL)       /*!< INIRQ (Bit 0)                                         */
 #define R_BUS_SDRAM_SDICR_INIRQ_Msk     (0x1UL)     /*!< INIRQ (Bitfield-Mask: 0x01)                           */
/* =========================================================  SDIR  ========================================================== */
 #define R_BUS_SDRAM_SDIR_PRC_Pos        (8UL)       /*!< PRC (Bit 8)                                           */
 #define R_BUS_SDRAM_SDIR_PRC_Msk        (0x700UL)   /*!< PRC (Bitfield-Mask: 0x07)                             */
 #define R_BUS_SDRAM_SDIR_ARFC_Pos       (4UL)       /*!< ARFC (Bit 4)                                          */
 #define R_BUS_SDRAM_SDIR_ARFC_Msk       (0xf0UL)    /*!< ARFC (Bitfield-Mask: 0x0f)                            */
 #define R_BUS_SDRAM_SDIR_ARFI_Pos       (0UL)       /*!< ARFI (Bit 0)                                          */
 #define R_BUS_SDRAM_SDIR_ARFI_Msk       (0xfUL)     /*!< ARFI (Bitfield-Mask: 0x0f)                            */
/* =========================================================  SDADR  ========================================================= */
 #define R_BUS_SDRAM_SDADR_MXC_Pos       (0UL)       /*!< MXC (Bit 0)                                           */
 #define R_BUS_SDRAM_SDADR_MXC_Msk       (0x3UL)     /*!< MXC (Bitfield-Mask: 0x03)                             */
/* =========================================================  SDTR  ========================================================== */
 #define R_BUS_SDRAM_SDTR_RAS_Pos        (16UL)      /*!< RAS (Bit 16)                                          */
 #define R_BUS_SDRAM_SDTR_RAS_Msk        (0x70000UL) /*!< RAS (Bitfield-Mask: 0x07)                             */
 #define R_BUS_SDRAM_SDTR_RCD_Pos        (12UL)      /*!< RCD (Bit 12)                                          */
 #define R_BUS_SDRAM_SDTR_RCD_Msk        (0x3000UL)  /*!< RCD (Bitfield-Mask: 0x03)                             */
 #define R_BUS_SDRAM_SDTR_RP_Pos         (9UL)       /*!< RP (Bit 9)                                            */
 #define R_BUS_SDRAM_SDTR_RP_Msk         (0xe00UL)   /*!< RP (Bitfield-Mask: 0x07)                              */
 #define R_BUS_SDRAM_SDTR_WR_Pos         (8UL)       /*!< WR (Bit 8)                                            */
 #define R_BUS_SDRAM_SDTR_WR_Msk         (0x100UL)   /*!< WR (Bitfield-Mask: 0x01)                              */
 #define R_BUS_SDRAM_SDTR_CL_Pos         (0UL)       /*!< CL (Bit 0)                                            */
 #define R_BUS_SDRAM_SDTR_CL_Msk         (0x7UL)     /*!< CL (Bitfield-Mask: 0x07)                              */
/* =========================================================  SDMOD  ========================================================= */
 #define R_BUS_SDRAM_SDMOD_MR_Pos        (0UL)       /*!< MR (Bit 0)                                            */
 #define R_BUS_SDRAM_SDMOD_MR_Msk        (0x7fffUL)  /*!< MR (Bitfield-Mask: 0x7fff)                            */
/* =========================================================  SDSR  ========================================================== */
 #define R_BUS_SDRAM_SDSR_SRFST_Pos      (4UL)       /*!< SRFST (Bit 4)                                         */
 #define R_BUS_SDRAM_SDSR_SRFST_Msk      (0x10UL)    /*!< SRFST (Bitfield-Mask: 0x01)                           */
 #define R_BUS_SDRAM_SDSR_INIST_Pos      (3UL)       /*!< INIST (Bit 3)                                         */
 #define R_BUS_SDRAM_SDSR_INIST_Msk      (0x8UL)     /*!< INIST (Bitfield-Mask: 0x01)                           */
 #define R_BUS_SDRAM_SDSR_MRSST_Pos      (0UL)       /*!< MRSST (Bit 0)                                         */
 #define R_BUS_SDRAM_SDSR_MRSST_Msk      (0x1UL)     /*!< MRSST (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                          BUSERRa                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  ADD  ========================================================== */
 #define R_BUS_BUSERRa_ADD_BERAD_Pos       (0UL)          /*!< BERAD (Bit 0)                                         */
 #define R_BUS_BUSERRa_ADD_BERAD_Msk       (0xffffffffUL) /*!< BERAD (Bitfield-Mask: 0xffffffff)                     */
/* =========================================================  STAT  ========================================================== */
 #define R_BUS_BUSERRa_STAT_ERRSTAT_Pos    (7UL)          /*!< ERRSTAT (Bit 7)                                       */
 #define R_BUS_BUSERRa_STAT_ERRSTAT_Msk    (0x80UL)       /*!< ERRSTAT (Bitfield-Mask: 0x01)                         */
 #define R_BUS_BUSERRa_STAT_ACCSTAT_Pos    (0UL)          /*!< ACCSTAT (Bit 0)                                       */
 #define R_BUS_BUSERRa_STAT_ACCSTAT_Msk    (0x1UL)        /*!< ACCSTAT (Bitfield-Mask: 0x01)                         */
/* ==========================================================  RW  =========================================================== */
 #define R_BUS_BUSERRa_RW_RWSTAT_Pos       (0UL)          /*!< RWSTAT (Bit 0)                                        */
 #define R_BUS_BUSERRa_RW_RWSTAT_Msk       (0x1UL)        /*!< RWSTAT (Bitfield-Mask: 0x01)                          */

/* =========================================================================================================================== */
/* ================                                          BTZFERR                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  ADD  ========================================================== */
 #define R_BUS_BTZFERR_ADD_BTZFERAD_Pos    (0UL)          /*!< BTZFERAD (Bit 0)                                      */
 #define R_BUS_BTZFERR_ADD_BTZFERAD_Msk    (0xffffffffUL) /*!< BTZFERAD (Bitfield-Mask: 0xffffffff)                  */
/* ==========================================================  RW  =========================================================== */
 #define R_BUS_BTZFERR_RW_TRWSTAT_Pos      (0UL)          /*!< TRWSTAT (Bit 0)                                       */
 #define R_BUS_BTZFERR_RW_TRWSTAT_Msk      (0x1UL)        /*!< TRWSTAT (Bitfield-Mask: 0x01)                         */

/* =========================================================================================================================== */
/* ================                                          BUSERRb                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  STAT  ========================================================== */
 #define R_BUS_BUSERRb_STAT_MSERRSTAT_Pos    (5UL)    /*!< MSERRSTAT (Bit 5)                                     */
 #define R_BUS_BUSERRb_STAT_MSERRSTAT_Msk    (0x20UL) /*!< MSERRSTAT (Bitfield-Mask: 0x01)                       */
 #define R_BUS_BUSERRb_STAT_ILERRSTAT_Pos    (4UL)    /*!< ILERRSTAT (Bit 4)                                     */
 #define R_BUS_BUSERRb_STAT_ILERRSTAT_Msk    (0x10UL) /*!< ILERRSTAT (Bitfield-Mask: 0x01)                       */
 #define R_BUS_BUSERRb_STAT_MMERRSTAT_Pos    (3UL)    /*!< MMERRSTAT (Bit 3)                                     */
 #define R_BUS_BUSERRb_STAT_MMERRSTAT_Msk    (0x8UL)  /*!< MMERRSTAT (Bitfield-Mask: 0x01)                       */
 #define R_BUS_BUSERRb_STAT_STERRSTAT_Pos    (1UL)    /*!< STERRSTAT (Bit 1)                                     */
 #define R_BUS_BUSERRb_STAT_STERRSTAT_Msk    (0x2UL)  /*!< STERRSTAT (Bitfield-Mask: 0x01)                       */
 #define R_BUS_BUSERRb_STAT_SLERRSTAT_Pos    (0UL)    /*!< SLERRSTAT (Bit 0)                                     */
 #define R_BUS_BUSERRb_STAT_SLERRSTAT_Msk    (0x1UL)  /*!< SLERRSTAT (Bitfield-Mask: 0x01)                       */
/* ==========================================================  CLR  ========================================================== */
 #define R_BUS_BUSERRb_CLR_MSERRCLR_Pos      (5UL)    /*!< MSERRCLR (Bit 5)                                      */
 #define R_BUS_BUSERRb_CLR_MSERRCLR_Msk      (0x20UL) /*!< MSERRCLR (Bitfield-Mask: 0x01)                        */
 #define R_BUS_BUSERRb_CLR_ILERRCLR_Pos      (4UL)    /*!< ILERRCLR (Bit 4)                                      */
 #define R_BUS_BUSERRb_CLR_ILERRCLR_Msk      (0x10UL) /*!< ILERRCLR (Bitfield-Mask: 0x01)                        */
 #define R_BUS_BUSERRb_CLR_MMERRCLR_Pos      (3UL)    /*!< MMERRCLR (Bit 3)                                      */
 #define R_BUS_BUSERRb_CLR_MMERRCLR_Msk      (0x8UL)  /*!< MMERRCLR (Bitfield-Mask: 0x01)                        */
 #define R_BUS_BUSERRb_CLR_STERRCLR_Pos      (1UL)    /*!< STERRCLR (Bit 1)                                      */
 #define R_BUS_BUSERRb_CLR_STERRCLR_Msk      (0x2UL)  /*!< STERRCLR (Bitfield-Mask: 0x01)                        */
 #define R_BUS_BUSERRb_CLR_SLERRCLR_Pos      (0UL)    /*!< SLERRCLR (Bit 0)                                      */
 #define R_BUS_BUSERRb_CLR_SLERRCLR_Msk      (0x1UL)  /*!< SLERRCLR (Bitfield-Mask: 0x01)                        */

/* =========================================================================================================================== */
/* ================                                        DMACDTCERR                                         ================ */
/* =========================================================================================================================== */

/* =========================================================  STAT  ========================================================== */
 #define R_BUS_DMACDTCERR_STAT_MTERRSTAT_Pos    (0UL)   /*!< MTERRSTAT (Bit 0)                                     */
 #define R_BUS_DMACDTCERR_STAT_MTERRSTAT_Msk    (0x1UL) /*!< MTERRSTAT (Bitfield-Mask: 0x01)                       */
/* ==========================================================  CLR  ========================================================== */
 #define R_BUS_DMACDTCERR_CLR_MTERRCLR_Pos      (0UL)   /*!< MTERRCLR (Bit 0)                                      */
 #define R_BUS_DMACDTCERR_CLR_MTERRCLR_Msk      (0x1UL) /*!< MTERRCLR (Bitfield-Mask: 0x01)                        */

/* =========================================================================================================================== */
/* ================                                         BUSSABT0                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  FLBI  ========================================================== */
 #define R_BUS_BUSSABT0_FLBI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_FLBI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* ========================================================  MRE0BI  ========================================================= */
 #define R_BUS_BUSSABT0_MRE0BI_ARBS_Pos       (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_MRE0BI_ARBS_Msk       (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  S0BI  ========================================================== */
 #define R_BUS_BUSSABT0_S0BI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_S0BI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  S1BI  ========================================================== */
 #define R_BUS_BUSSABT0_S1BI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_S1BI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  S2BI  ========================================================== */
 #define R_BUS_BUSSABT0_S2BI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_S2BI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  S3BI  ========================================================== */
 #define R_BUS_BUSSABT0_S3BI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_S3BI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* ========================================================  STBYSBI  ======================================================== */
 #define R_BUS_BUSSABT0_STBYSBI_ARBS_Pos      (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_STBYSBI_ARBS_Msk      (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  ECBI  ========================================================== */
 #define R_BUS_BUSSABT0_ECBI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_ECBI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  EOBI  ========================================================== */
 #define R_BUS_BUSSABT0_EOBI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_EOBI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* ========================================================  SPI0BI  ========================================================= */
 #define R_BUS_BUSSABT0_SPI0BI_ARBS_Pos       (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_SPI0BI_ARBS_Msk       (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* ========================================================  SPI1BI  ========================================================= */
 #define R_BUS_BUSSABT0_SPI1BI_ARBS_Pos       (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_SPI1BI_ARBS_Msk       (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  PBBI  ========================================================== */
 #define R_BUS_BUSSABT0_PBBI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_PBBI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  PABI  ========================================================== */
 #define R_BUS_BUSSABT0_PABI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_PABI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  PIBI  ========================================================== */
 #define R_BUS_BUSSABT0_PIBI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_PIBI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =========================================================  PSBI  ========================================================== */
 #define R_BUS_BUSSABT0_PSBI_ARBS_Pos         (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_PSBI_ARBS_Msk         (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =======================================================  CPU0SAHBI  ======================================================= */
 #define R_BUS_BUSSABT0_CPU0SAHBI_ARBS_Pos    (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_CPU0SAHBI_ARBS_Msk    (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =======================================================  CPU1TCMBI  ======================================================= */
 #define R_BUS_BUSSABT0_CPU1TCMBI_ARBS_Pos    (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT0_CPU1TCMBI_ARBS_Msk    (0x1UL) /*!< ARBS (Bitfield-Mask: 0x01)                            */

/* =========================================================================================================================== */
/* ================                                         BUSSABT1                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  FHBI  ========================================================== */
 #define R_BUS_BUSSABT1_FHBI_ARBS_Pos      (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT1_FHBI_ARBS_Msk      (0x3UL) /*!< ARBS (Bitfield-Mask: 0x03)                            */
/* ========================================================  MRC0BI  ========================================================= */
 #define R_BUS_BUSSABT1_MRC0BI_ARBS_Pos    (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT1_MRC0BI_ARBS_Msk    (0x3UL) /*!< ARBS (Bitfield-Mask: 0x03)                            */
/* =========================================================  S0BI  ========================================================== */
 #define R_BUS_BUSSABT1_S0BI_ARBS_Pos      (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT1_S0BI_ARBS_Msk      (0x3UL) /*!< ARBS (Bitfield-Mask: 0x03)                            */
/* =========================================================  S1BI  ========================================================== */
 #define R_BUS_BUSSABT1_S1BI_ARBS_Pos      (0UL)   /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSSABT1_S1BI_ARBS_Msk      (0x3UL) /*!< ARBS (Bitfield-Mask: 0x03)                            */

/* =========================================================================================================================== */
/* ================                                          BMSAERR                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  ADD  ========================================================== */
 #define R_BUS_BMSAERR_ADD_MSERAD_Pos      (0UL)          /*!< MSERAD (Bit 0)                                        */
 #define R_BUS_BMSAERR_ADD_MSERAD_Msk      (0xffffffffUL) /*!< MSERAD (Bitfield-Mask: 0xffffffff)                    */
/* ==========================================================  RW  =========================================================== */
 #define R_BUS_BMSAERR_RW_MSARWSTAT_Pos    (0UL)          /*!< MSARWSTAT (Bit 0)                                     */
 #define R_BUS_BMSAERR_RW_MSARWSTAT_Msk    (0x1UL)        /*!< MSARWSTAT (Bitfield-Mask: 0x01)                       */

/* =========================================================================================================================== */
/* ================                                            OAD                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  BUSOAD  ========================================================= */
 #define R_BUS_OAD_BUSOAD_BWERROAD_Pos     (2UL)      /*!< BWERROAD (Bit 2)                                      */
 #define R_BUS_OAD_BUSOAD_BWERROAD_Msk     (0x4UL)    /*!< BWERROAD (Bitfield-Mask: 0x01)                        */
 #define R_BUS_OAD_BUSOAD_SLERROAD_Pos     (1UL)      /*!< SLERROAD (Bit 1)                                      */
 #define R_BUS_OAD_BUSOAD_SLERROAD_Msk     (0x2UL)    /*!< SLERROAD (Bitfield-Mask: 0x01)                        */
 #define R_BUS_OAD_BUSOAD_ILERROAD_Pos     (0UL)      /*!< ILERROAD (Bit 0)                                      */
 #define R_BUS_OAD_BUSOAD_ILERROAD_Msk     (0x1UL)    /*!< ILERROAD (Bitfield-Mask: 0x01)                        */
/* =======================================================  BUSOADPT  ======================================================== */
 #define R_BUS_OAD_BUSOADPT_KEY_Pos        (8UL)      /*!< KEY (Bit 8)                                           */
 #define R_BUS_OAD_BUSOADPT_KEY_Msk        (0xff00UL) /*!< KEY (Bitfield-Mask: 0xff)                             */
 #define R_BUS_OAD_BUSOADPT_PROTECT_Pos    (0UL)      /*!< PROTECT (Bit 0)                                       */
 #define R_BUS_OAD_BUSOADPT_PROTECT_Msk    (0x1UL)    /*!< PROTECT (Bitfield-Mask: 0x01)                         */
/* ========================================================  MSAOAD  ========================================================= */
 #define R_BUS_OAD_MSAOAD_KEY_Pos          (8UL)      /*!< KEY (Bit 8)                                           */
 #define R_BUS_OAD_MSAOAD_KEY_Msk          (0xff00UL) /*!< KEY (Bitfield-Mask: 0xff)                             */
 #define R_BUS_OAD_MSAOAD_OAD_Pos          (0UL)      /*!< OAD (Bit 0)                                           */
 #define R_BUS_OAD_MSAOAD_OAD_Msk          (0x1UL)    /*!< OAD (Bitfield-Mask: 0x01)                             */
/* =========================================================  MSAPT  ========================================================= */
 #define R_BUS_OAD_MSAPT_KEY_Pos           (8UL)      /*!< KEY (Bit 8)                                           */
 #define R_BUS_OAD_MSAPT_KEY_Msk           (0xff00UL) /*!< KEY (Bitfield-Mask: 0xff)                             */
 #define R_BUS_OAD_MSAPT_PROTECT_Pos       (0UL)      /*!< PROTECT (Bit 0)                                       */
 #define R_BUS_OAD_MSAPT_PROTECT_Msk       (0x1UL)    /*!< PROTECT (Bitfield-Mask: 0x01)                         */

/* =========================================================================================================================== */
/* ================                                          MBWERR                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  STAT  ========================================================== */
 #define R_BUS_MBWERR_STAT_BWERR_Pos    (0UL)   /*!< BWERR (Bit 0)                                         */
 #define R_BUS_MBWERR_STAT_BWERR_Msk    (0x1UL) /*!< BWERR (Bitfield-Mask: 0x01)                           */
/* ==========================================================  CLR  ========================================================== */
 #define R_BUS_MBWERR_CLR_BWERR_Pos     (0UL)   /*!< BWERR (Bit 0)                                         */
 #define R_BUS_MBWERR_CLR_BWERR_Msk     (0x1UL) /*!< BWERR (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                           BUSM                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CNT  ========================================================== */
 #define R_BUS_BUSM_CNT_IERES_Pos    (15UL)     /*!< IERES (Bit 15)                                        */
 #define R_BUS_BUSM_CNT_IERES_Msk    (0x8000UL) /*!< IERES (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                           BUSS                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CNT  ========================================================== */
 #define R_BUS_BUSS_CNT_ARBMET_Pos    (4UL)    /*!< ARBMET (Bit 4)                                        */
 #define R_BUS_BUSS_CNT_ARBMET_Msk    (0x30UL) /*!< ARBMET (Bitfield-Mask: 0x03)                          */
 #define R_BUS_BUSS_CNT_ARBS_Pos      (0UL)    /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSS_CNT_ARBS_Msk      (0x3UL)  /*!< ARBS (Bitfield-Mask: 0x03)                            */

/* =========================================================================================================================== */
/* ================                                          ELSEGR                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  BY  =========================================================== */
 #define R_ELC_ELSEGR_BY_WI_Pos     (7UL)    /*!< WI (Bit 7)                                            */
 #define R_ELC_ELSEGR_BY_WI_Msk     (0x80UL) /*!< WI (Bitfield-Mask: 0x01)                              */
 #define R_ELC_ELSEGR_BY_WE_Pos     (6UL)    /*!< WE (Bit 6)                                            */
 #define R_ELC_ELSEGR_BY_WE_Msk     (0x40UL) /*!< WE (Bitfield-Mask: 0x01)                              */
 #define R_ELC_ELSEGR_BY_SEG_Pos    (0UL)    /*!< SEG (Bit 0)                                           */
 #define R_ELC_ELSEGR_BY_SEG_Msk    (0x1UL)  /*!< SEG (Bitfield-Mask: 0x01)                             */

/* =========================================================================================================================== */
/* ================                                           ELSR                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  HA  =========================================================== */
 #define R_ELC_ELSR_HA_ELS_Pos    (0UL)     /*!< ELS (Bit 0)                                           */
 #define R_ELC_ELSR_HA_ELS_Msk    (0x1ffUL) /*!< ELS (Bitfield-Mask: 0x1ff)                            */

/* =========================================================================================================================== */
/* ================                                            PIN                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  PmnPFS  ========================================================= */
 #define R_PFS_PORT_PIN_PmnPFS_PODR_Pos     (0UL)      /*!< PODR (Bit 0)                                          */
 #define R_PFS_PORT_PIN_PmnPFS_PODR_Msk     (0x1UL)    /*!< PODR (Bitfield-Mask: 0x01)                            */
 #define R_PFS_PORT_PIN_PmnPFS_PIDR_Pos     (1UL)      /*!< PIDR (Bit 1)                                          */
 #define R_PFS_PORT_PIN_PmnPFS_PIDR_Msk     (0x2UL)    /*!< PIDR (Bitfield-Mask: 0x01)                            */
 #define R_PFS_PORT_PIN_PmnPFS_PDR_Pos      (2UL)      /*!< PDR (Bit 2)                                           */
 #define R_PFS_PORT_PIN_PmnPFS_PDR_Msk      (0x4UL)    /*!< PDR (Bitfield-Mask: 0x01)                             */
 #define R_PFS_PORT_PIN_PmnPFS_PSEL_Pos     (8UL)      /*!< PSEL (Bit 8)                                          */
 #define R_PFS_PORT_PIN_PmnPFS_PSEL_Msk     (0x700UL)  /*!< PSEL (Bitfield-Mask: 0x07)                            */
 #define R_PFS_PORT_PIN_PmnPFS_ISEL_Pos     (14UL)     /*!< ISEL (Bit 14)                                         */
 #define R_PFS_PORT_PIN_PmnPFS_ISEL_Msk     (0x4000UL) /*!< ISEL (Bitfield-Mask: 0x01)                            */
 #define R_PFS_PORT_PIN_PmnPFS_PMC_Pos      (15UL)     /*!< PMC (Bit 15)                                          */
 #define R_PFS_PORT_PIN_PmnPFS_PMC_Msk      (0x8000UL) /*!< PMC (Bitfield-Mask: 0x01)                             */
 #define R_PFS_PORT_PIN_PmnPFS_PCR_Pos      (4UL)      /*!< PCR (Bit 4)                                           */
 #define R_PFS_PORT_PIN_PmnPFS_PCR_Msk      (0x10UL)   /*!< PCR (Bitfield-Mask: 0x01)                             */
 #define R_PFS_PORT_PIN_PmnPFS_PIM_Pos      (5UL)      /*!< PIM (Bit 5)                                           */
 #define R_PFS_PORT_PIN_PmnPFS_PIM_Msk      (0x20UL)   /*!< PIM (Bitfield-Mask: 0x01)                             */
 #define R_PFS_PORT_PIN_PmnPFS_NCODR_Pos    (6UL)      /*!< NCODR (Bit 6)                                         */
 #define R_PFS_PORT_PIN_PmnPFS_NCODR_Msk    (0x40UL)   /*!< NCODR (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                           PORT                                            ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                                           TDR0                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  TDR0n  ========================================================= */
/* ========================================================  TDR0nL  ========================================================= */
/* ========================================================  TDR0nH  ========================================================= */

/** @} */ /* End of group PosMask_clusters */

/* =========================================================================================================================== */
/* ================                                Pos/Mask Peripheral Section                                ================ */
/* =========================================================================================================================== */

/** @addtogroup PosMask_peripherals
 * @{
 */

/* =========================================================================================================================== */
/* ================                                          R_ADC_D                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  ADM0  ========================================================== */
 #define R_ADC_D_ADM0_ADCE_Pos      (0UL)    /*!< ADCE (Bit 0)                                          */
 #define R_ADC_D_ADM0_ADCE_Msk      (0x1UL)  /*!< ADCE (Bitfield-Mask: 0x01)                            */
 #define R_ADC_D_ADM0_LV_Pos        (1UL)    /*!< LV (Bit 1)                                            */
 #define R_ADC_D_ADM0_LV_Msk        (0x6UL)  /*!< LV (Bitfield-Mask: 0x03)                              */
 #define R_ADC_D_ADM0_FR_Pos        (3UL)    /*!< FR (Bit 3)                                            */
 #define R_ADC_D_ADM0_FR_Msk        (0x38UL) /*!< FR (Bitfield-Mask: 0x07)                              */
 #define R_ADC_D_ADM0_ADMD_Pos      (6UL)    /*!< ADMD (Bit 6)                                          */
 #define R_ADC_D_ADM0_ADMD_Msk      (0x40UL) /*!< ADMD (Bitfield-Mask: 0x01)                            */
 #define R_ADC_D_ADM0_ADCS_Pos      (7UL)    /*!< ADCS (Bit 7)                                          */
 #define R_ADC_D_ADM0_ADCS_Msk      (0x80UL) /*!< ADCS (Bitfield-Mask: 0x01)                            */
/* ==========================================================  ADS  ========================================================== */
 #define R_ADC_D_ADS_ADS_Pos        (0UL)    /*!< ADS (Bit 0)                                           */
 #define R_ADC_D_ADS_ADS_Msk        (0x1fUL) /*!< ADS (Bitfield-Mask: 0x1f)                             */
 #define R_ADC_D_ADS_ADISS_Pos      (7UL)    /*!< ADISS (Bit 7)                                         */
 #define R_ADC_D_ADS_ADISS_Msk      (0x80UL) /*!< ADISS (Bitfield-Mask: 0x01)                           */
/* =========================================================  ADM1  ========================================================== */
 #define R_ADC_D_ADM1_ADTRS_Pos     (0UL)    /*!< ADTRS (Bit 0)                                         */
 #define R_ADC_D_ADM1_ADTRS_Msk     (0x7UL)  /*!< ADTRS (Bitfield-Mask: 0x07)                           */
 #define R_ADC_D_ADM1_ADLSP_Pos     (3UL)    /*!< ADLSP (Bit 3)                                         */
 #define R_ADC_D_ADM1_ADLSP_Msk     (0x8UL)  /*!< ADLSP (Bitfield-Mask: 0x01)                           */
 #define R_ADC_D_ADM1_ADSCM_Pos     (5UL)    /*!< ADSCM (Bit 5)                                         */
 #define R_ADC_D_ADM1_ADSCM_Msk     (0x20UL) /*!< ADSCM (Bitfield-Mask: 0x01)                           */
 #define R_ADC_D_ADM1_ADTMD_Pos     (6UL)    /*!< ADTMD (Bit 6)                                         */
 #define R_ADC_D_ADM1_ADTMD_Msk     (0xc0UL) /*!< ADTMD (Bitfield-Mask: 0x03)                           */
/* =========================================================  ADCR  ========================================================== */
/* =========================================================  ADCRH  ========================================================= */
/* =========================================================  ADM2  ========================================================== */
 #define R_ADC_D_ADM2_ADTYP_Pos     (0UL)    /*!< ADTYP (Bit 0)                                         */
 #define R_ADC_D_ADM2_ADTYP_Msk     (0x3UL)  /*!< ADTYP (Bitfield-Mask: 0x03)                           */
 #define R_ADC_D_ADM2_AWC_Pos       (2UL)    /*!< AWC (Bit 2)                                           */
 #define R_ADC_D_ADM2_AWC_Msk       (0x4UL)  /*!< AWC (Bitfield-Mask: 0x01)                             */
 #define R_ADC_D_ADM2_ADRCK_Pos     (3UL)    /*!< ADRCK (Bit 3)                                         */
 #define R_ADC_D_ADM2_ADRCK_Msk     (0x8UL)  /*!< ADRCK (Bitfield-Mask: 0x01)                           */
 #define R_ADC_D_ADM2_ADREFM_Pos    (5UL)    /*!< ADREFM (Bit 5)                                        */
 #define R_ADC_D_ADM2_ADREFM_Msk    (0x20UL) /*!< ADREFM (Bitfield-Mask: 0x01)                          */
 #define R_ADC_D_ADM2_ADREFP_Pos    (6UL)    /*!< ADREFP (Bit 6)                                        */
 #define R_ADC_D_ADM2_ADREFP_Msk    (0xc0UL) /*!< ADREFP (Bitfield-Mask: 0x03)                          */
/* =========================================================  ADUL  ========================================================== */
/* =========================================================  ADLL  ========================================================== */
/* =========================================================  ADTES  ========================================================= */
 #define R_ADC_D_ADTES_ADTES_Pos    (0UL)    /*!< ADTES (Bit 0)                                         */
 #define R_ADC_D_ADTES_ADTES_Msk    (0x3UL)  /*!< ADTES (Bitfield-Mask: 0x03)                           */
/* =========================================================  ADCR0  ========================================================= */
/* ========================================================  ADCR0H  ========================================================= */
/* =========================================================  ADCR1  ========================================================= */
/* ========================================================  ADCR1H  ========================================================= */
/* =========================================================  ADCR2  ========================================================= */
/* ========================================================  ADCR2H  ========================================================= */
/* =========================================================  ADCR3  ========================================================= */
/* ========================================================  ADCR3H  ========================================================= */

/* =========================================================================================================================== */
/* ================                                           R_BUS                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  CSRECEN  ======================================================== */
 #define R_BUS_CSRECEN_RCVENM_Pos        (8UL)       /*!< RCVENM (Bit 8)                                        */
 #define R_BUS_CSRECEN_RCVENM_Msk        (0x100UL)   /*!< RCVENM (Bitfield-Mask: 0x01)                          */
 #define R_BUS_CSRECEN_RCVEN_Pos         (0UL)       /*!< RCVEN (Bit 0)                                         */
 #define R_BUS_CSRECEN_RCVEN_Msk         (0x1UL)     /*!< RCVEN (Bitfield-Mask: 0x01)                           */
/* ========================================================  BUSMABT  ======================================================== */
 #define R_BUS_BUSMABT_ARBS_Pos          (0UL)       /*!< ARBS (Bit 0)                                          */
 #define R_BUS_BUSMABT_ARBS_Msk          (0x1UL)     /*!< ARBS (Bitfield-Mask: 0x01)                            */
/* =======================================================  BUSDIVBYP  ======================================================= */
 #define R_BUS_BUSDIVBYP_CPU0SBPE_Pos    (16UL)      /*!< CPU0SBPE (Bit 16)                                     */
 #define R_BUS_BUSDIVBYP_CPU0SBPE_Msk    (0x10000UL) /*!< CPU0SBPE (Bitfield-Mask: 0x01)                        */
 #define R_BUS_BUSDIVBYP_GDSSBPE_Pos     (3UL)       /*!< GDSSBPE (Bit 3)                                       */
 #define R_BUS_BUSDIVBYP_GDSSBPE_Msk     (0x8UL)     /*!< GDSSBPE (Bitfield-Mask: 0x01)                         */
 #define R_BUS_BUSDIVBYP_EDMABPE_Pos     (0UL)       /*!< EDMABPE (Bit 0)                                       */
 #define R_BUS_BUSDIVBYP_EDMABPE_Msk     (0x1UL)     /*!< EDMABPE (Bitfield-Mask: 0x01)                         */

/* =========================================================================================================================== */
/* ================                                           R_CRC                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  CRCCR0  ========================================================= */
 #define R_CRC_CRCCR0_DORCLR_Pos          (7UL)          /*!< DORCLR (Bit 7)                                        */
 #define R_CRC_CRCCR0_DORCLR_Msk          (0x80UL)       /*!< DORCLR (Bitfield-Mask: 0x01)                          */
 #define R_CRC_CRCCR0_LMS_Pos             (6UL)          /*!< LMS (Bit 6)                                           */
 #define R_CRC_CRCCR0_LMS_Msk             (0x40UL)       /*!< LMS (Bitfield-Mask: 0x01)                             */
 #define R_CRC_CRCCR0_GPS_Pos             (0UL)          /*!< GPS (Bit 0)                                           */
 #define R_CRC_CRCCR0_GPS_Msk             (0x7UL)        /*!< GPS (Bitfield-Mask: 0x07)                             */
/* ========================================================  CRCCR1  ========================================================= */
 #define R_CRC_CRCCR1_CRCSEN_Pos          (7UL)          /*!< CRCSEN (Bit 7)                                        */
 #define R_CRC_CRCCR1_CRCSEN_Msk          (0x80UL)       /*!< CRCSEN (Bitfield-Mask: 0x01)                          */
 #define R_CRC_CRCCR1_CRCSWR_Pos          (6UL)          /*!< CRCSWR (Bit 6)                                        */
 #define R_CRC_CRCCR1_CRCSWR_Msk          (0x40UL)       /*!< CRCSWR (Bitfield-Mask: 0x01)                          */
/* ========================================================  CRCDIR  ========================================================= */
 #define R_CRC_CRCDIR_CRCDIR_Pos          (0UL)          /*!< CRCDIR (Bit 0)                                        */
 #define R_CRC_CRCDIR_CRCDIR_Msk          (0xffffffffUL) /*!< CRCDIR (Bitfield-Mask: 0xffffffff)                    */
/* =======================================================  CRCDIR_BY  ======================================================= */
 #define R_CRC_CRCDIR_BY_CRCDIR_BY_Pos    (0UL)          /*!< CRCDIR_BY (Bit 0)                                     */
 #define R_CRC_CRCDIR_BY_CRCDIR_BY_Msk    (0xffUL)       /*!< CRCDIR_BY (Bitfield-Mask: 0xff)                       */
/* ========================================================  CRCDOR  ========================================================= */
 #define R_CRC_CRCDOR_CRCDOR_Pos          (0UL)          /*!< CRCDOR (Bit 0)                                        */
 #define R_CRC_CRCDOR_CRCDOR_Msk          (0xffffffffUL) /*!< CRCDOR (Bitfield-Mask: 0xffffffff)                    */
/* =======================================================  CRCDOR_HA  ======================================================= */
 #define R_CRC_CRCDOR_HA_CRCDOR_HA_Pos    (0UL)          /*!< CRCDOR_HA (Bit 0)                                     */
 #define R_CRC_CRCDOR_HA_CRCDOR_HA_Msk    (0xffffUL)     /*!< CRCDOR_HA (Bitfield-Mask: 0xffff)                     */
/* =======================================================  CRCDOR_BY  ======================================================= */
 #define R_CRC_CRCDOR_BY_CRCDOR_BY_Pos    (0UL)          /*!< CRCDOR_BY (Bit 0)                                     */
 #define R_CRC_CRCDOR_BY_CRCDOR_BY_Msk    (0xffUL)       /*!< CRCDOR_BY (Bitfield-Mask: 0xff)                       */
/* ========================================================  CRCSAR  ========================================================= */
 #define R_CRC_CRCSAR_CRCSA_Pos           (0UL)          /*!< CRCSA (Bit 0)                                         */
 #define R_CRC_CRCSAR_CRCSA_Msk           (0x3fffUL)     /*!< CRCSA (Bitfield-Mask: 0x3fff)                         */

/* =========================================================================================================================== */
/* ================                                          R_DEBUG                                          ================ */
/* =========================================================================================================================== */

/* ========================================================  DBGSTR  ========================================================= */
 #define R_DEBUG_DBGSTR_CDBGPWRUPREQ_Pos        (28UL)         /*!< CDBGPWRUPREQ (Bit 28)                                 */
 #define R_DEBUG_DBGSTR_CDBGPWRUPREQ_Msk        (0x10000000UL) /*!< CDBGPWRUPREQ (Bitfield-Mask: 0x01)                    */
 #define R_DEBUG_DBGSTR_CDBGPWRUPACK_Pos        (29UL)         /*!< CDBGPWRUPACK (Bit 29)                                 */
 #define R_DEBUG_DBGSTR_CDBGPWRUPACK_Msk        (0x20000000UL) /*!< CDBGPWRUPACK (Bitfield-Mask: 0x01)                    */
/* =======================================================  DBGSTOPCR  ======================================================= */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_RPER_Pos     (24UL)         /*!< DBGSTOP_RPER (Bit 24)                                 */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_RPER_Msk     (0x1000000UL)  /*!< DBGSTOP_RPER (Bitfield-Mask: 0x01)                    */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_TIM_Pos      (14UL)         /*!< DBGSTOP_TIM (Bit 14)                                  */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_TIM_Msk      (0x4000UL)     /*!< DBGSTOP_TIM (Bitfield-Mask: 0x01)                     */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_SIR_Pos      (15UL)         /*!< DBGSTOP_SIR (Bit 15)                                  */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_SIR_Msk      (0x8000UL)     /*!< DBGSTOP_SIR (Bitfield-Mask: 0x01)                     */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_LVD_Pos      (16UL)         /*!< DBGSTOP_LVD (Bit 16)                                  */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_LVD_Msk      (0x10000UL)    /*!< DBGSTOP_LVD (Bitfield-Mask: 0x01)                     */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_RECCR_Pos    (25UL)         /*!< DBGSTOP_RECCR (Bit 25)                                */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_RECCR_Msk    (0x2000000UL)  /*!< DBGSTOP_RECCR (Bitfield-Mask: 0x01)                   */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_IWDT_Pos     (0UL)          /*!< DBGSTOP_IWDT (Bit 0)                                  */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_IWDT_Msk     (0x1UL)        /*!< DBGSTOP_IWDT (Bitfield-Mask: 0x01)                    */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_WDT_Pos      (1UL)          /*!< DBGSTOP_WDT (Bit 1)                                   */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_WDT_Msk      (0x2UL)        /*!< DBGSTOP_WDT (Bitfield-Mask: 0x01)                     */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_CPER_Pos     (31UL)         /*!< DBGSTOP_CPER (Bit 31)                                 */
 #define R_DEBUG_DBGSTOPCR_DBGSTOP_CPER_Msk     (0x80000000UL) /*!< DBGSTOP_CPER (Bitfield-Mask: 0x01)                    */
/* =======================================================  FSBLSTAT  ======================================================== */
 #define R_DEBUG_FSBLSTAT_CS_Pos                (0UL)          /*!< CS (Bit 0)                                            */
 #define R_DEBUG_FSBLSTAT_CS_Msk                (0x1UL)        /*!< CS (Bitfield-Mask: 0x01)                              */
 #define R_DEBUG_FSBLSTAT_RS_Pos                (1UL)          /*!< RS (Bit 1)                                            */
 #define R_DEBUG_FSBLSTAT_RS_Msk                (0x2UL)        /*!< RS (Bitfield-Mask: 0x01)                              */
 #define R_DEBUG_FSBLSTAT_FSBLCLK_Pos           (8UL)          /*!< FSBLCLK (Bit 8)                                       */
 #define R_DEBUG_FSBLSTAT_FSBLCLK_Msk           (0x700UL)      /*!< FSBLCLK (Bitfield-Mask: 0x07)                         */

/* =========================================================================================================================== */
/* ================                                           R_DTC                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  DTCCR  ========================================================= */
 #define R_DTC_DTCCR_RRS_Pos         (4UL)          /*!< RRS (Bit 4)                                           */
 #define R_DTC_DTCCR_RRS_Msk         (0x10UL)       /*!< RRS (Bitfield-Mask: 0x01)                             */
/* ========================================================  DTCVBR  ========================================================= */
 #define R_DTC_DTCVBR_DTCVBR_Pos     (0UL)          /*!< DTCVBR (Bit 0)                                        */
 #define R_DTC_DTCVBR_DTCVBR_Msk     (0xffffffffUL) /*!< DTCVBR (Bitfield-Mask: 0xffffffff)                    */
/* =========================================================  DTCST  ========================================================= */
 #define R_DTC_DTCST_DTCST_Pos       (0UL)          /*!< DTCST (Bit 0)                                         */
 #define R_DTC_DTCST_DTCST_Msk       (0x1UL)        /*!< DTCST (Bitfield-Mask: 0x01)                           */
/* ========================================================  DTCSTS  ========================================================= */
 #define R_DTC_DTCSTS_ACT_Pos        (15UL)         /*!< ACT (Bit 15)                                          */
 #define R_DTC_DTCSTS_ACT_Msk        (0x8000UL)     /*!< ACT (Bitfield-Mask: 0x01)                             */
 #define R_DTC_DTCSTS_VECN_Pos       (0UL)          /*!< VECN (Bit 0)                                          */
 #define R_DTC_DTCSTS_VECN_Msk       (0xffUL)       /*!< VECN (Bitfield-Mask: 0xff)                            */
/* =======================================================  DTCCR_SEC  ======================================================= */
 #define R_DTC_DTCCR_SEC_RRSS_Pos    (4UL)          /*!< RRSS (Bit 4)                                          */
 #define R_DTC_DTCCR_SEC_RRSS_Msk    (0x10UL)       /*!< RRSS (Bitfield-Mask: 0x01)                            */
/* ======================================================  DTCVBR_SEC  ======================================================= */
/* =========================================================  DTEVR  ========================================================= */
 #define R_DTC_DTEVR_DTEV_Pos        (0UL)          /*!< DTEV (Bit 0)                                          */
 #define R_DTC_DTEVR_DTEV_Msk        (0xffUL)       /*!< DTEV (Bitfield-Mask: 0xff)                            */
 #define R_DTC_DTEVR_DTEVSAM_Pos     (8UL)          /*!< DTEVSAM (Bit 8)                                       */
 #define R_DTC_DTEVR_DTEVSAM_Msk     (0x100UL)      /*!< DTEVSAM (Bitfield-Mask: 0x01)                         */
 #define R_DTC_DTEVR_DTESTA_Pos      (16UL)         /*!< DTESTA (Bit 16)                                       */
 #define R_DTC_DTEVR_DTESTA_Msk      (0x10000UL)    /*!< DTESTA (Bitfield-Mask: 0x01)                          */

/* =========================================================================================================================== */
/* ================                                           R_ELC                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  ELCR  ========================================================== */
 #define R_ELC_ELCR_ELCON_Pos    (7UL)    /*!< ELCON (Bit 7)                                         */
 #define R_ELC_ELCR_ELCON_Msk    (0x80UL) /*!< ELCON (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                         R_FACI_LP                                         ================ */
/* =========================================================================================================================== */

/* ========================================================  DFLCTL  ========================================================= */
/* =========================================================  FPMCR  ========================================================= */
 #define R_FACI_LP_FPMCR_FMS2_Pos           (7UL)      /*!< FMS2 (Bit 7)                                          */
 #define R_FACI_LP_FPMCR_FMS2_Msk           (0x80UL)   /*!< FMS2 (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FPMCR_VLPE_Pos           (6UL)      /*!< VLPE (Bit 6)                                          */
 #define R_FACI_LP_FPMCR_VLPE_Msk           (0x40UL)   /*!< VLPE (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FPMCR_FMS1_Pos           (4UL)      /*!< FMS1 (Bit 4)                                          */
 #define R_FACI_LP_FPMCR_FMS1_Msk           (0x10UL)   /*!< FMS1 (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FPMCR_RPDIS_Pos          (3UL)      /*!< RPDIS (Bit 3)                                         */
 #define R_FACI_LP_FPMCR_RPDIS_Msk          (0x8UL)    /*!< RPDIS (Bitfield-Mask: 0x01)                           */
 #define R_FACI_LP_FPMCR_FMS0_Pos           (1UL)      /*!< FMS0 (Bit 1)                                          */
 #define R_FACI_LP_FPMCR_FMS0_Msk           (0x2UL)    /*!< FMS0 (Bitfield-Mask: 0x01)                            */
/* =========================================================  FASR  ========================================================== */
 #define R_FACI_LP_FASR_EXS_Pos             (0UL)      /*!< EXS (Bit 0)                                           */
 #define R_FACI_LP_FASR_EXS_Msk             (0x1UL)    /*!< EXS (Bitfield-Mask: 0x01)                             */
/* =========================================================  FSARL  ========================================================= */
 #define R_FACI_LP_FSARL_FSAR15_0_Pos       (0UL)      /*!< FSAR15_0 (Bit 0)                                      */
 #define R_FACI_LP_FSARL_FSAR15_0_Msk       (0xffffUL) /*!< FSAR15_0 (Bitfield-Mask: 0xffff)                      */
/* =========================================================  FSARH  ========================================================= */
 #define R_FACI_LP_FSARH_FSAR31_25_Pos      (9UL)      /*!< FSAR31_25 (Bit 9)                                     */
 #define R_FACI_LP_FSARH_FSAR31_25_Msk      (0xfe00UL) /*!< FSAR31_25 (Bitfield-Mask: 0x7f)                       */
 #define R_FACI_LP_FSARH_FSAR20_16_Pos      (0UL)      /*!< FSAR20_16 (Bit 0)                                     */
 #define R_FACI_LP_FSARH_FSAR20_16_Msk      (0x1fUL)   /*!< FSAR20_16 (Bitfield-Mask: 0x1f)                       */
/* ==========================================================  FCR  ========================================================== */
 #define R_FACI_LP_FCR_OPST_Pos             (7UL)      /*!< OPST (Bit 7)                                          */
 #define R_FACI_LP_FCR_OPST_Msk             (0x80UL)   /*!< OPST (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FCR_STOP_Pos             (6UL)      /*!< STOP (Bit 6)                                          */
 #define R_FACI_LP_FCR_STOP_Msk             (0x40UL)   /*!< STOP (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FCR_DRC_Pos              (4UL)      /*!< DRC (Bit 4)                                           */
 #define R_FACI_LP_FCR_DRC_Msk              (0x10UL)   /*!< DRC (Bitfield-Mask: 0x01)                             */
 #define R_FACI_LP_FCR_CMD_Pos              (0UL)      /*!< CMD (Bit 0)                                           */
 #define R_FACI_LP_FCR_CMD_Msk              (0xfUL)    /*!< CMD (Bitfield-Mask: 0x0f)                             */
/* =========================================================  FEARL  ========================================================= */
 #define R_FACI_LP_FEARL_FEAR15_0_Pos       (0UL)      /*!< FEAR15_0 (Bit 0)                                      */
 #define R_FACI_LP_FEARL_FEAR15_0_Msk       (0xffffUL) /*!< FEAR15_0 (Bitfield-Mask: 0xffff)                      */
/* =========================================================  FEARH  ========================================================= */
 #define R_FACI_LP_FEARH_FEAR31_25_Pos      (9UL)      /*!< FEAR31_25 (Bit 9)                                     */
 #define R_FACI_LP_FEARH_FEAR31_25_Msk      (0xfe00UL) /*!< FEAR31_25 (Bitfield-Mask: 0x7f)                       */
 #define R_FACI_LP_FEARH_FEAR20_16_Pos      (0UL)      /*!< FEAR20_16 (Bit 0)                                     */
 #define R_FACI_LP_FEARH_FEAR20_16_Msk      (0x1fUL)   /*!< FEAR20_16 (Bitfield-Mask: 0x1f)                       */
/* ========================================================  FRESETR  ======================================================== */
 #define R_FACI_LP_FRESETR_FRESET_Pos       (0UL)      /*!< FRESET (Bit 0)                                        */
 #define R_FACI_LP_FRESETR_FRESET_Msk       (0x1UL)    /*!< FRESET (Bitfield-Mask: 0x01)                          */
/* =======================================================  FSTATR00  ======================================================== */
 #define R_FACI_LP_FSTATR00_EILGLERR_Pos    (5UL)      /*!< EILGLERR (Bit 5)                                      */
 #define R_FACI_LP_FSTATR00_EILGLERR_Msk    (0x20UL)   /*!< EILGLERR (Bitfield-Mask: 0x01)                        */
 #define R_FACI_LP_FSTATR00_ILGLERR_Pos     (4UL)      /*!< ILGLERR (Bit 4)                                       */
 #define R_FACI_LP_FSTATR00_ILGLERR_Msk     (0x10UL)   /*!< ILGLERR (Bitfield-Mask: 0x01)                         */
 #define R_FACI_LP_FSTATR00_BCERR0_Pos      (3UL)      /*!< BCERR0 (Bit 3)                                        */
 #define R_FACI_LP_FSTATR00_BCERR0_Msk      (0x8UL)    /*!< BCERR0 (Bitfield-Mask: 0x01)                          */
 #define R_FACI_LP_FSTATR00_PRGERR01_Pos    (2UL)      /*!< PRGERR01 (Bit 2)                                      */
 #define R_FACI_LP_FSTATR00_PRGERR01_Msk    (0x4UL)    /*!< PRGERR01 (Bitfield-Mask: 0x01)                        */
 #define R_FACI_LP_FSTATR00_PRGERR0_Pos     (1UL)      /*!< PRGERR0 (Bit 1)                                       */
 #define R_FACI_LP_FSTATR00_PRGERR0_Msk     (0x2UL)    /*!< PRGERR0 (Bitfield-Mask: 0x01)                         */
 #define R_FACI_LP_FSTATR00_ERERR0_Pos      (0UL)      /*!< ERERR0 (Bit 0)                                        */
 #define R_FACI_LP_FSTATR00_ERERR0_Msk      (0x1UL)    /*!< ERERR0 (Bitfield-Mask: 0x01)                          */
/* ========================================================  FSTATR1  ======================================================== */
 #define R_FACI_LP_FSTATR1_EXRDY_Pos        (7UL)      /*!< EXRDY (Bit 7)                                         */
 #define R_FACI_LP_FSTATR1_EXRDY_Msk        (0x80UL)   /*!< EXRDY (Bitfield-Mask: 0x01)                           */
 #define R_FACI_LP_FSTATR1_FRDY_Pos         (6UL)      /*!< FRDY (Bit 6)                                          */
 #define R_FACI_LP_FSTATR1_FRDY_Msk         (0x40UL)   /*!< FRDY (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FSTATR1_DRRDY_Pos        (1UL)      /*!< DRRDY (Bit 1)                                         */
 #define R_FACI_LP_FSTATR1_DRRDY_Msk        (0x2UL)    /*!< DRRDY (Bitfield-Mask: 0x01)                           */
/* =========================================================  FWBL0  ========================================================= */
 #define R_FACI_LP_FWBL0_WDATA_Pos          (0UL)      /*!< WDATA (Bit 0)                                         */
 #define R_FACI_LP_FWBL0_WDATA_Msk          (0xffffUL) /*!< WDATA (Bitfield-Mask: 0xffff)                         */
/* =========================================================  FWBH0  ========================================================= */
 #define R_FACI_LP_FWBH0_WDATA_Pos          (0UL)      /*!< WDATA (Bit 0)                                         */
 #define R_FACI_LP_FWBH0_WDATA_Msk          (0xffffUL) /*!< WDATA (Bitfield-Mask: 0xffff)                         */
/* =======================================================  FSTATR01  ======================================================== */
 #define R_FACI_LP_FSTATR01_BCERR1_Pos      (3UL)      /*!< BCERR1 (Bit 3)                                        */
 #define R_FACI_LP_FSTATR01_BCERR1_Msk      (0x8UL)    /*!< BCERR1 (Bitfield-Mask: 0x01)                          */
 #define R_FACI_LP_FSTATR01_PRGERR1_Pos     (1UL)      /*!< PRGERR1 (Bit 1)                                       */
 #define R_FACI_LP_FSTATR01_PRGERR1_Msk     (0x2UL)    /*!< PRGERR1 (Bitfield-Mask: 0x01)                         */
 #define R_FACI_LP_FSTATR01_ERERR1_Pos      (0UL)      /*!< ERERR1 (Bit 0)                                        */
 #define R_FACI_LP_FSTATR01_ERERR1_Msk      (0x1UL)    /*!< ERERR1 (Bitfield-Mask: 0x01)                          */
/* =========================================================  FWBL1  ========================================================= */
 #define R_FACI_LP_FWBL1_WDATA47_32_Pos     (0UL)      /*!< WDATA47_32 (Bit 0)                                    */
 #define R_FACI_LP_FWBL1_WDATA47_32_Msk     (0xffffUL) /*!< WDATA47_32 (Bitfield-Mask: 0xffff)                    */
/* =========================================================  FWBH1  ========================================================= */
 #define R_FACI_LP_FWBH1_WDATA63_48_Pos     (0UL)      /*!< WDATA63_48 (Bit 0)                                    */
 #define R_FACI_LP_FWBH1_WDATA63_48_Msk     (0xffffUL) /*!< WDATA63_48 (Bitfield-Mask: 0xffff)                    */
/* =========================================================  FRBL1  ========================================================= */
 #define R_FACI_LP_FRBL1_RDATA47_32_Pos     (0UL)      /*!< RDATA47_32 (Bit 0)                                    */
 #define R_FACI_LP_FRBL1_RDATA47_32_Msk     (0xffffUL) /*!< RDATA47_32 (Bitfield-Mask: 0xffff)                    */
/* =========================================================  FRBH1  ========================================================= */
 #define R_FACI_LP_FRBH1_RDATA63_48_Pos     (0UL)      /*!< RDATA63_48 (Bit 0)                                    */
 #define R_FACI_LP_FRBH1_RDATA63_48_Msk     (0xffffUL) /*!< RDATA63_48 (Bitfield-Mask: 0xffff)                    */
/* ==========================================================  FPR  ========================================================== */
 #define R_FACI_LP_FPR_FPR_Pos              (0UL)      /*!< FPR (Bit 0)                                           */
 #define R_FACI_LP_FPR_FPR_Msk              (0xffUL)   /*!< FPR (Bitfield-Mask: 0xff)                             */
/* =========================================================  FPSR  ========================================================== */
 #define R_FACI_LP_FPSR_PERR_Pos            (0UL)      /*!< PERR (Bit 0)                                          */
 #define R_FACI_LP_FPSR_PERR_Msk            (0x1UL)    /*!< PERR (Bitfield-Mask: 0x01)                            */
/* =========================================================  FRBL0  ========================================================= */
 #define R_FACI_LP_FRBL0_RDATA_Pos          (0UL)      /*!< RDATA (Bit 0)                                         */
 #define R_FACI_LP_FRBL0_RDATA_Msk          (0xffffUL) /*!< RDATA (Bitfield-Mask: 0xffff)                         */
/* =========================================================  FRBH0  ========================================================= */
 #define R_FACI_LP_FRBH0_RDATA_Pos          (0UL)      /*!< RDATA (Bit 0)                                         */
 #define R_FACI_LP_FRBH0_RDATA_Msk          (0xffffUL) /*!< RDATA (Bitfield-Mask: 0xffff)                         */
/* =========================================================  FSCMR  ========================================================= */
 #define R_FACI_LP_FSCMR_FSPR_Pos           (14UL)     /*!< FSPR (Bit 14)                                         */
 #define R_FACI_LP_FSCMR_FSPR_Msk           (0x4000UL) /*!< FSPR (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FSCMR_SASMF_Pos          (8UL)      /*!< SASMF (Bit 8)                                         */
 #define R_FACI_LP_FSCMR_SASMF_Msk          (0x100UL)  /*!< SASMF (Bitfield-Mask: 0x01)                           */
/* ========================================================  FAWSMR  ========================================================= */
 #define R_FACI_LP_FAWSMR_FAWS_Pos          (0UL)      /*!< FAWS (Bit 0)                                          */
 #define R_FACI_LP_FAWSMR_FAWS_Msk          (0xfffUL)  /*!< FAWS (Bitfield-Mask: 0xfff)                           */
/* ========================================================  FAWEMR  ========================================================= */
 #define R_FACI_LP_FAWEMR_FAWE_Pos          (0UL)      /*!< FAWE (Bit 0)                                          */
 #define R_FACI_LP_FAWEMR_FAWE_Msk          (0xfffUL)  /*!< FAWE (Bitfield-Mask: 0xfff)                           */
/* =========================================================  FISR  ========================================================== */
 #define R_FACI_LP_FISR_SAS_Pos             (6UL)      /*!< SAS (Bit 6)                                           */
 #define R_FACI_LP_FISR_SAS_Msk             (0xc0UL)   /*!< SAS (Bitfield-Mask: 0x03)                             */
 #define R_FACI_LP_FISR_PCKA_Pos            (0UL)      /*!< PCKA (Bit 0)                                          */
 #define R_FACI_LP_FISR_PCKA_Msk            (0x3fUL)   /*!< PCKA (Bitfield-Mask: 0x3f)                            */
/* =========================================================  FEXCR  ========================================================= */
 #define R_FACI_LP_FEXCR_OPST_Pos           (7UL)      /*!< OPST (Bit 7)                                          */
 #define R_FACI_LP_FEXCR_OPST_Msk           (0x80UL)   /*!< OPST (Bitfield-Mask: 0x01)                            */
 #define R_FACI_LP_FEXCR_CMD_Pos            (0UL)      /*!< CMD (Bit 0)                                           */
 #define R_FACI_LP_FEXCR_CMD_Msk            (0x7UL)    /*!< CMD (Bitfield-Mask: 0x07)                             */
/* =========================================================  FEAML  ========================================================= */
 #define R_FACI_LP_FEAML_FEAM_Pos           (0UL)      /*!< FEAM (Bit 0)                                          */
 #define R_FACI_LP_FEAML_FEAM_Msk           (0xffffUL) /*!< FEAM (Bitfield-Mask: 0xffff)                          */
/* =========================================================  FEAMH  ========================================================= */
 #define R_FACI_LP_FEAMH_FEAM_Pos           (0UL)      /*!< FEAM (Bit 0)                                          */
 #define R_FACI_LP_FEAMH_FEAM_Msk           (0xffffUL) /*!< FEAM (Bitfield-Mask: 0xffff)                          */
/* ========================================================  FSTATR2  ======================================================== */
 #define R_FACI_LP_FSTATR2_EILGLERR_Pos     (5UL)      /*!< EILGLERR (Bit 5)                                      */
 #define R_FACI_LP_FSTATR2_EILGLERR_Msk     (0x20UL)   /*!< EILGLERR (Bitfield-Mask: 0x01)                        */
 #define R_FACI_LP_FSTATR2_ILGLERR_Pos      (4UL)      /*!< ILGLERR (Bit 4)                                       */
 #define R_FACI_LP_FSTATR2_ILGLERR_Msk      (0x10UL)   /*!< ILGLERR (Bitfield-Mask: 0x01)                         */
 #define R_FACI_LP_FSTATR2_BCERR_Pos        (3UL)      /*!< BCERR (Bit 3)                                         */
 #define R_FACI_LP_FSTATR2_BCERR_Msk        (0x8UL)    /*!< BCERR (Bitfield-Mask: 0x01)                           */
 #define R_FACI_LP_FSTATR2_PRGERR01_Pos     (2UL)      /*!< PRGERR01 (Bit 2)                                      */
 #define R_FACI_LP_FSTATR2_PRGERR01_Msk     (0x4UL)    /*!< PRGERR01 (Bitfield-Mask: 0x01)                        */
 #define R_FACI_LP_FSTATR2_PRGERR1_Pos      (1UL)      /*!< PRGERR1 (Bit 1)                                       */
 #define R_FACI_LP_FSTATR2_PRGERR1_Msk      (0x2UL)    /*!< PRGERR1 (Bitfield-Mask: 0x01)                         */
 #define R_FACI_LP_FSTATR2_ERERR_Pos        (0UL)      /*!< ERERR (Bit 0)                                         */
 #define R_FACI_LP_FSTATR2_ERERR_Msk        (0x1UL)    /*!< ERERR (Bitfield-Mask: 0x01)                           */
/* ========================================================  FCTLFR  ========================================================= */
 #define R_FACI_LP_FCTLFR_BANKSWP_Pos       (0UL)      /*!< BANKSWP (Bit 0)                                       */
 #define R_FACI_LP_FCTLFR_BANKSWP_Msk       (0x7UL)    /*!< BANKSWP (Bitfield-Mask: 0x07)                         */
/* ======================================================  FENTRYR_MF4  ====================================================== */
/* ========================================================  FENTRYR  ======================================================== */
/* ========================================================  FLWAITR  ======================================================== */
/* =======================================================  FLDWAITR  ======================================================== */
 #define R_FACI_LP_FLDWAITR_FLDWAIT1_Pos    (0UL)      /*!< FLDWAIT1 (Bit 0)                                      */
 #define R_FACI_LP_FLDWAITR_FLDWAIT1_Msk    (0x1UL)    /*!< FLDWAIT1 (Bitfield-Mask: 0x01)                        */
/* =========================================================  PFBER  ========================================================= */
/* ========================================================  FBKPGCR  ======================================================== */
 #define R_FACI_LP_FBKPGCR_BKPGEN_Pos       (0UL)      /*!< BKPGEN (Bit 0)                                        */
 #define R_FACI_LP_FBKPGCR_BKPGEN_Msk       (0x1UL)    /*!< BKPGEN (Bitfield-Mask: 0x01)                          */
 #define R_FACI_LP_FBKPGCR_FEKEY_Pos        (8UL)      /*!< FEKEY (Bit 8)                                         */
 #define R_FACI_LP_FBKPGCR_FEKEY_Msk        (0xff00UL) /*!< FEKEY (Bitfield-Mask: 0xff)                           */
/* ========================================================  FBKSWCR  ======================================================== */
 #define R_FACI_LP_FBKSWCR_BKSWUPEN_Pos     (0UL)      /*!< BKSWUPEN (Bit 0)                                      */
 #define R_FACI_LP_FBKSWCR_BKSWUPEN_Msk     (0x1UL)    /*!< BKSWUPEN (Bitfield-Mask: 0x01)                        */
 #define R_FACI_LP_FBKSWCR_FEKEY_Pos        (8UL)      /*!< FEKEY (Bit 8)                                         */
 #define R_FACI_LP_FBKSWCR_FEKEY_Msk        (0xff00UL) /*!< FEKEY (Bitfield-Mask: 0xff)                           */
/* ========================================================  HIOTRM  ========================================================= */
 #define R_FACI_LP_HIOTRM_HIOTRM_Pos        (0UL)      /*!< HIOTRM (Bit 0)                                        */
 #define R_FACI_LP_HIOTRM_HIOTRM_Msk        (0x3fUL)   /*!< HIOTRM (Bitfield-Mask: 0x3f)                          */
/* ========================================================  FLMODE  ========================================================= */
 #define R_FACI_LP_FLMODE_MODE_Pos          (6UL)      /*!< MODE (Bit 6)                                          */
 #define R_FACI_LP_FLMODE_MODE_Msk          (0xc0UL)   /*!< MODE (Bitfield-Mask: 0x03)                            */
/* ========================================================  FLMWRP  ========================================================= */
 #define R_FACI_LP_FLMWRP_FLMWEN_Pos        (0UL)      /*!< FLMWEN (Bit 0)                                        */
 #define R_FACI_LP_FLMWRP_FLMWEN_Msk        (0x1UL)    /*!< FLMWEN (Bitfield-Mask: 0x01)                          */

/* =========================================================================================================================== */
/* ================                                           R_ICU                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  IRQCR  ========================================================= */
 #define R_ICU_IRQCR_FLTEN_Pos            (7UL)          /*!< FLTEN (Bit 7)                                         */
 #define R_ICU_IRQCR_FLTEN_Msk            (0x80UL)       /*!< FLTEN (Bitfield-Mask: 0x01)                           */
 #define R_ICU_IRQCR_FCLKSEL_Pos          (4UL)          /*!< FCLKSEL (Bit 4)                                       */
 #define R_ICU_IRQCR_FCLKSEL_Msk          (0x30UL)       /*!< FCLKSEL (Bitfield-Mask: 0x03)                         */
 #define R_ICU_IRQCR_IRQMD_Pos            (0UL)          /*!< IRQMD (Bit 0)                                         */
 #define R_ICU_IRQCR_IRQMD_Msk            (0x3UL)        /*!< IRQMD (Bitfield-Mask: 0x03)                           */
/* =========================================================  NMISR  ========================================================= */
 #define R_ICU_NMISR_SPEST_Pos            (12UL)         /*!< SPEST (Bit 12)                                        */
 #define R_ICU_NMISR_SPEST_Msk            (0x1000UL)     /*!< SPEST (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMISR_BUSMST_Pos           (11UL)         /*!< BUSMST (Bit 11)                                       */
 #define R_ICU_NMISR_BUSMST_Msk           (0x800UL)      /*!< BUSMST (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMISR_BUSSST_Pos           (10UL)         /*!< BUSSST (Bit 10)                                       */
 #define R_ICU_NMISR_BUSSST_Msk           (0x400UL)      /*!< BUSSST (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMISR_RECCST_Pos           (9UL)          /*!< RECCST (Bit 9)                                        */
 #define R_ICU_NMISR_RECCST_Msk           (0x200UL)      /*!< RECCST (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMISR_RPEST_Pos            (8UL)          /*!< RPEST (Bit 8)                                         */
 #define R_ICU_NMISR_RPEST_Msk            (0x100UL)      /*!< RPEST (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMISR_NMIST_Pos            (7UL)          /*!< NMIST (Bit 7)                                         */
 #define R_ICU_NMISR_NMIST_Msk            (0x80UL)       /*!< NMIST (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMISR_OSTST_Pos            (6UL)          /*!< OSTST (Bit 6)                                         */
 #define R_ICU_NMISR_OSTST_Msk            (0x40UL)       /*!< OSTST (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMISR_VBATTST_Pos          (4UL)          /*!< VBATTST (Bit 4)                                       */
 #define R_ICU_NMISR_VBATTST_Msk          (0x10UL)       /*!< VBATTST (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMISR_LVD2ST_Pos           (3UL)          /*!< LVD2ST (Bit 3)                                        */
 #define R_ICU_NMISR_LVD2ST_Msk           (0x8UL)        /*!< LVD2ST (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMISR_LVD1ST_Pos           (2UL)          /*!< LVD1ST (Bit 2)                                        */
 #define R_ICU_NMISR_LVD1ST_Msk           (0x4UL)        /*!< LVD1ST (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMISR_WDTST_Pos            (1UL)          /*!< WDTST (Bit 1)                                         */
 #define R_ICU_NMISR_WDTST_Msk            (0x2UL)        /*!< WDTST (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMISR_IWDTST_Pos           (0UL)          /*!< IWDTST (Bit 0)                                        */
 #define R_ICU_NMISR_IWDTST_Msk           (0x1UL)        /*!< IWDTST (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMISR_TZFST_Pos            (13UL)         /*!< TZFST (Bit 13)                                        */
 #define R_ICU_NMISR_TZFST_Msk            (0x2000UL)     /*!< TZFST (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMISR_CPEST_Pos            (15UL)         /*!< CPEST (Bit 15)                                        */
 #define R_ICU_NMISR_CPEST_Msk            (0x8000UL)     /*!< CPEST (Bitfield-Mask: 0x01)                           */
/* =========================================================  NMIER  ========================================================= */
 #define R_ICU_NMIER_SPEEN_Pos            (12UL)         /*!< SPEEN (Bit 12)                                        */
 #define R_ICU_NMIER_SPEEN_Msk            (0x1000UL)     /*!< SPEEN (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMIER_BUSMEN_Pos           (11UL)         /*!< BUSMEN (Bit 11)                                       */
 #define R_ICU_NMIER_BUSMEN_Msk           (0x800UL)      /*!< BUSMEN (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMIER_BUSSEN_Pos           (10UL)         /*!< BUSSEN (Bit 10)                                       */
 #define R_ICU_NMIER_BUSSEN_Msk           (0x400UL)      /*!< BUSSEN (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMIER_RECCEN_Pos           (9UL)          /*!< RECCEN (Bit 9)                                        */
 #define R_ICU_NMIER_RECCEN_Msk           (0x200UL)      /*!< RECCEN (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMIER_RPEEN_Pos            (8UL)          /*!< RPEEN (Bit 8)                                         */
 #define R_ICU_NMIER_RPEEN_Msk            (0x100UL)      /*!< RPEEN (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMIER_NMIEN_Pos            (7UL)          /*!< NMIEN (Bit 7)                                         */
 #define R_ICU_NMIER_NMIEN_Msk            (0x80UL)       /*!< NMIEN (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMIER_OSTEN_Pos            (6UL)          /*!< OSTEN (Bit 6)                                         */
 #define R_ICU_NMIER_OSTEN_Msk            (0x40UL)       /*!< OSTEN (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMIER_VBATTEN_Pos          (4UL)          /*!< VBATTEN (Bit 4)                                       */
 #define R_ICU_NMIER_VBATTEN_Msk          (0x10UL)       /*!< VBATTEN (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMIER_LVD2EN_Pos           (3UL)          /*!< LVD2EN (Bit 3)                                        */
 #define R_ICU_NMIER_LVD2EN_Msk           (0x8UL)        /*!< LVD2EN (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMIER_LVD1EN_Pos           (2UL)          /*!< LVD1EN (Bit 2)                                        */
 #define R_ICU_NMIER_LVD1EN_Msk           (0x4UL)        /*!< LVD1EN (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMIER_WDTEN_Pos            (1UL)          /*!< WDTEN (Bit 1)                                         */
 #define R_ICU_NMIER_WDTEN_Msk            (0x2UL)        /*!< WDTEN (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMIER_IWDTEN_Pos           (0UL)          /*!< IWDTEN (Bit 0)                                        */
 #define R_ICU_NMIER_IWDTEN_Msk           (0x1UL)        /*!< IWDTEN (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMIER_TZFEN_Pos            (13UL)         /*!< TZFEN (Bit 13)                                        */
 #define R_ICU_NMIER_TZFEN_Msk            (0x2000UL)     /*!< TZFEN (Bitfield-Mask: 0x01)                           */
 #define R_ICU_NMIER_CPEEN_Pos            (15UL)         /*!< CPEEN (Bit 15)                                        */
 #define R_ICU_NMIER_CPEEN_Msk            (0x8000UL)     /*!< CPEEN (Bitfield-Mask: 0x01)                           */
/* ========================================================  NMICLR  ========================================================= */
 #define R_ICU_NMICLR_SPECLR_Pos          (12UL)         /*!< SPECLR (Bit 12)                                       */
 #define R_ICU_NMICLR_SPECLR_Msk          (0x1000UL)     /*!< SPECLR (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMICLR_BUSMCLR_Pos         (11UL)         /*!< BUSMCLR (Bit 11)                                      */
 #define R_ICU_NMICLR_BUSMCLR_Msk         (0x800UL)      /*!< BUSMCLR (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMICLR_BUSSCLR_Pos         (10UL)         /*!< BUSSCLR (Bit 10)                                      */
 #define R_ICU_NMICLR_BUSSCLR_Msk         (0x400UL)      /*!< BUSSCLR (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMICLR_RECCCLR_Pos         (9UL)          /*!< RECCCLR (Bit 9)                                       */
 #define R_ICU_NMICLR_RECCCLR_Msk         (0x200UL)      /*!< RECCCLR (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMICLR_RPECLR_Pos          (8UL)          /*!< RPECLR (Bit 8)                                        */
 #define R_ICU_NMICLR_RPECLR_Msk          (0x100UL)      /*!< RPECLR (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMICLR_NMICLR_Pos          (7UL)          /*!< NMICLR (Bit 7)                                        */
 #define R_ICU_NMICLR_NMICLR_Msk          (0x80UL)       /*!< NMICLR (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMICLR_OSTCLR_Pos          (6UL)          /*!< OSTCLR (Bit 6)                                        */
 #define R_ICU_NMICLR_OSTCLR_Msk          (0x40UL)       /*!< OSTCLR (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMICLR_VBATTCLR_Pos        (4UL)          /*!< VBATTCLR (Bit 4)                                      */
 #define R_ICU_NMICLR_VBATTCLR_Msk        (0x10UL)       /*!< VBATTCLR (Bitfield-Mask: 0x01)                        */
 #define R_ICU_NMICLR_LVD2CLR_Pos         (3UL)          /*!< LVD2CLR (Bit 3)                                       */
 #define R_ICU_NMICLR_LVD2CLR_Msk         (0x8UL)        /*!< LVD2CLR (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMICLR_LVD1CLR_Pos         (2UL)          /*!< LVD1CLR (Bit 2)                                       */
 #define R_ICU_NMICLR_LVD1CLR_Msk         (0x4UL)        /*!< LVD1CLR (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMICLR_WDTCLR_Pos          (1UL)          /*!< WDTCLR (Bit 1)                                        */
 #define R_ICU_NMICLR_WDTCLR_Msk          (0x2UL)        /*!< WDTCLR (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMICLR_IWDTCLR_Pos         (0UL)          /*!< IWDTCLR (Bit 0)                                       */
 #define R_ICU_NMICLR_IWDTCLR_Msk         (0x1UL)        /*!< IWDTCLR (Bitfield-Mask: 0x01)                         */
 #define R_ICU_NMICLR_TZFCLR_Pos          (13UL)         /*!< TZFCLR (Bit 13)                                       */
 #define R_ICU_NMICLR_TZFCLR_Msk          (0x2000UL)     /*!< TZFCLR (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMICLR_CPECLR_Pos          (15UL)         /*!< CPECLR (Bit 15)                                       */
 #define R_ICU_NMICLR_CPECLR_Msk          (0x8000UL)     /*!< CPECLR (Bitfield-Mask: 0x01)                          */
/* =========================================================  NMICR  ========================================================= */
 #define R_ICU_NMICR_NFLTEN_Pos           (7UL)          /*!< NFLTEN (Bit 7)                                        */
 #define R_ICU_NMICR_NFLTEN_Msk           (0x80UL)       /*!< NFLTEN (Bitfield-Mask: 0x01)                          */
 #define R_ICU_NMICR_NFCLKSEL_Pos         (4UL)          /*!< NFCLKSEL (Bit 4)                                      */
 #define R_ICU_NMICR_NFCLKSEL_Msk         (0x30UL)       /*!< NFCLKSEL (Bitfield-Mask: 0x03)                        */
 #define R_ICU_NMICR_NMIMD_Pos            (0UL)          /*!< NMIMD (Bit 0)                                         */
 #define R_ICU_NMICR_NMIMD_Msk            (0x1UL)        /*!< NMIMD (Bitfield-Mask: 0x01)                           */
/* ========================================================  DTCENST  ======================================================== */
 #define R_ICU_DTCENST_ST_Pos             (0UL)          /*!< ST (Bit 0)                                            */
 #define R_ICU_DTCENST_ST_Msk             (0x1UL)        /*!< ST (Bitfield-Mask: 0x01)                              */
/* =======================================================  DTCENSET  ======================================================== */
 #define R_ICU_DTCENSET_SET_Pos           (0UL)          /*!< SET (Bit 0)                                           */
 #define R_ICU_DTCENSET_SET_Msk           (0x1UL)        /*!< SET (Bitfield-Mask: 0x01)                             */
/* =======================================================  DTCENCLR  ======================================================== */
 #define R_ICU_DTCENCLR_CLR_Pos           (0UL)          /*!< CLR (Bit 0)                                           */
 #define R_ICU_DTCENCLR_CLR_Msk           (0x1UL)        /*!< CLR (Bitfield-Mask: 0x01)                             */
/* ========================================================  INTFLAG  ======================================================== */
 #define R_ICU_INTFLAG_IF_Pos             (0UL)          /*!< IF (Bit 0)                                            */
 #define R_ICU_INTFLAG_IF_Msk             (0x1UL)        /*!< IF (Bitfield-Mask: 0x01)                              */
/* =======================================================  SBYEDCR0  ======================================================== */
 #define R_ICU_SBYEDCR0_IWDTED_Pos        (0UL)          /*!< IWDTED (Bit 0)                                        */
 #define R_ICU_SBYEDCR0_IWDTED_Msk        (0x1UL)        /*!< IWDTED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_LVD1ED_Pos        (1UL)          /*!< LVD1ED (Bit 1)                                        */
 #define R_ICU_SBYEDCR0_LVD1ED_Msk        (0x2UL)        /*!< LVD1ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_IRQ0ED_Pos        (2UL)          /*!< IRQ0ED (Bit 2)                                        */
 #define R_ICU_SBYEDCR0_IRQ0ED_Msk        (0x4UL)        /*!< IRQ0ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_IRQ1ED_Pos        (3UL)          /*!< IRQ1ED (Bit 3)                                        */
 #define R_ICU_SBYEDCR0_IRQ1ED_Msk        (0x8UL)        /*!< IRQ1ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_IRQ2ED_Pos        (4UL)          /*!< IRQ2ED (Bit 4)                                        */
 #define R_ICU_SBYEDCR0_IRQ2ED_Msk        (0x10UL)       /*!< IRQ2ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_IRQ3ED_Pos        (5UL)          /*!< IRQ3ED (Bit 5)                                        */
 #define R_ICU_SBYEDCR0_IRQ3ED_Msk        (0x20UL)       /*!< IRQ3ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_IRQ4ED_Pos        (6UL)          /*!< IRQ4ED (Bit 6)                                        */
 #define R_ICU_SBYEDCR0_IRQ4ED_Msk        (0x40UL)       /*!< IRQ4ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_IRQ5ED_Pos        (7UL)          /*!< IRQ5ED (Bit 7)                                        */
 #define R_ICU_SBYEDCR0_IRQ5ED_Msk        (0x80UL)       /*!< IRQ5ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR0_DTCED_Pos         (10UL)         /*!< DTCED (Bit 10)                                        */
 #define R_ICU_SBYEDCR0_DTCED_Msk         (0x400UL)      /*!< DTCED (Bitfield-Mask: 0x01)                           */
 #define R_ICU_SBYEDCR0_SPI00RXED_Pos     (18UL)         /*!< SPI00RXED (Bit 18)                                    */
 #define R_ICU_SBYEDCR0_SPI00RXED_Msk     (0x40000UL)    /*!< SPI00RXED (Bitfield-Mask: 0x01)                       */
 #define R_ICU_SBYEDCR0_UART0ERRED_Pos    (20UL)         /*!< UART0ERRED (Bit 20)                                   */
 #define R_ICU_SBYEDCR0_UART0ERRED_Msk    (0x100000UL)   /*!< UART0ERRED (Bitfield-Mask: 0x01)                      */
 #define R_ICU_SBYEDCR0_IICA0ED_Pos       (26UL)         /*!< IICA0ED (Bit 26)                                      */
 #define R_ICU_SBYEDCR0_IICA0ED_Msk       (0x4000000UL)  /*!< IICA0ED (Bitfield-Mask: 0x01)                         */
 #define R_ICU_SBYEDCR0_UART0RXED_Pos     (27UL)         /*!< UART0RXED (Bit 27)                                    */
 #define R_ICU_SBYEDCR0_UART0RXED_Msk     (0x8000000UL)  /*!< UART0RXED (Bitfield-Mask: 0x01)                       */
 #define R_ICU_SBYEDCR0_ADC12ED_Pos       (31UL)         /*!< ADC12ED (Bit 31)                                      */
 #define R_ICU_SBYEDCR0_ADC12ED_Msk       (0x80000000UL) /*!< ADC12ED (Bitfield-Mask: 0x01)                         */
/* =======================================================  SBYEDCR1  ======================================================== */
 #define R_ICU_SBYEDCR1_RTCED_Pos         (0UL)          /*!< RTCED (Bit 0)                                         */
 #define R_ICU_SBYEDCR1_RTCED_Msk         (0x1UL)        /*!< RTCED (Bitfield-Mask: 0x01)                           */
 #define R_ICU_SBYEDCR1_ITLED_Pos         (1UL)          /*!< ITLED (Bit 1)                                         */
 #define R_ICU_SBYEDCR1_ITLED_Msk         (0x2UL)        /*!< ITLED (Bitfield-Mask: 0x01)                           */
 #define R_ICU_SBYEDCR1_URE0ED_Pos        (7UL)          /*!< URE0ED (Bit 7)                                        */
 #define R_ICU_SBYEDCR1_URE0ED_Msk        (0x80UL)       /*!< URE0ED (Bitfield-Mask: 0x01)                          */
 #define R_ICU_SBYEDCR1_UT0ED_Pos         (8UL)          /*!< UT0ED (Bit 8)                                         */
 #define R_ICU_SBYEDCR1_UT0ED_Msk         (0x100UL)      /*!< UT0ED (Bitfield-Mask: 0x01)                           */
 #define R_ICU_SBYEDCR1_UR0ED_Pos         (9UL)          /*!< UR0ED (Bit 9)                                         */
 #define R_ICU_SBYEDCR1_UR0ED_Msk         (0x200UL)      /*!< UR0ED (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                          R_IICA                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  IICA0  ========================================================= */
/* =========================================================  IICS0  ========================================================= */
 #define R_IICA_IICS0_SPD_Pos          (0UL)    /*!< SPD (Bit 0)                                           */
 #define R_IICA_IICS0_SPD_Msk          (0x1UL)  /*!< SPD (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICS0_STD_Pos          (1UL)    /*!< STD (Bit 1)                                           */
 #define R_IICA_IICS0_STD_Msk          (0x2UL)  /*!< STD (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICS0_ACKD_Pos         (2UL)    /*!< ACKD (Bit 2)                                          */
 #define R_IICA_IICS0_ACKD_Msk         (0x4UL)  /*!< ACKD (Bitfield-Mask: 0x01)                            */
 #define R_IICA_IICS0_TRC_Pos          (3UL)    /*!< TRC (Bit 3)                                           */
 #define R_IICA_IICS0_TRC_Msk          (0x8UL)  /*!< TRC (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICS0_COI_Pos          (4UL)    /*!< COI (Bit 4)                                           */
 #define R_IICA_IICS0_COI_Msk          (0x10UL) /*!< COI (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICS0_EXC_Pos          (5UL)    /*!< EXC (Bit 5)                                           */
 #define R_IICA_IICS0_EXC_Msk          (0x20UL) /*!< EXC (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICS0_ALD_Pos          (6UL)    /*!< ALD (Bit 6)                                           */
 #define R_IICA_IICS0_ALD_Msk          (0x40UL) /*!< ALD (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICS0_MSTS_Pos         (7UL)    /*!< MSTS (Bit 7)                                          */
 #define R_IICA_IICS0_MSTS_Msk         (0x80UL) /*!< MSTS (Bitfield-Mask: 0x01)                            */
/* =========================================================  IICF0  ========================================================= */
 #define R_IICA_IICF0_IICRSV_Pos       (0UL)    /*!< IICRSV (Bit 0)                                        */
 #define R_IICA_IICF0_IICRSV_Msk       (0x1UL)  /*!< IICRSV (Bitfield-Mask: 0x01)                          */
 #define R_IICA_IICF0_STCEN_Pos        (1UL)    /*!< STCEN (Bit 1)                                         */
 #define R_IICA_IICF0_STCEN_Msk        (0x2UL)  /*!< STCEN (Bitfield-Mask: 0x01)                           */
 #define R_IICA_IICF0_IICBSY_Pos       (6UL)    /*!< IICBSY (Bit 6)                                        */
 #define R_IICA_IICF0_IICBSY_Msk       (0x40UL) /*!< IICBSY (Bitfield-Mask: 0x01)                          */
 #define R_IICA_IICF0_STCF_Pos         (7UL)    /*!< STCF (Bit 7)                                          */
 #define R_IICA_IICF0_STCF_Msk         (0x80UL) /*!< STCF (Bitfield-Mask: 0x01)                            */
/* =======================================================  IICCTL00  ======================================================== */
 #define R_IICA_IICCTL00_SPT_Pos       (0UL)    /*!< SPT (Bit 0)                                           */
 #define R_IICA_IICCTL00_SPT_Msk       (0x1UL)  /*!< SPT (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICCTL00_STT_Pos       (1UL)    /*!< STT (Bit 1)                                           */
 #define R_IICA_IICCTL00_STT_Msk       (0x2UL)  /*!< STT (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICCTL00_ACKE_Pos      (2UL)    /*!< ACKE (Bit 2)                                          */
 #define R_IICA_IICCTL00_ACKE_Msk      (0x4UL)  /*!< ACKE (Bitfield-Mask: 0x01)                            */
 #define R_IICA_IICCTL00_WTIM_Pos      (3UL)    /*!< WTIM (Bit 3)                                          */
 #define R_IICA_IICCTL00_WTIM_Msk      (0x8UL)  /*!< WTIM (Bitfield-Mask: 0x01)                            */
 #define R_IICA_IICCTL00_SPIE_Pos      (4UL)    /*!< SPIE (Bit 4)                                          */
 #define R_IICA_IICCTL00_SPIE_Msk      (0x10UL) /*!< SPIE (Bitfield-Mask: 0x01)                            */
 #define R_IICA_IICCTL00_WREL_Pos      (5UL)    /*!< WREL (Bit 5)                                          */
 #define R_IICA_IICCTL00_WREL_Msk      (0x20UL) /*!< WREL (Bitfield-Mask: 0x01)                            */
 #define R_IICA_IICCTL00_LREL_Pos      (6UL)    /*!< LREL (Bit 6)                                          */
 #define R_IICA_IICCTL00_LREL_Msk      (0x40UL) /*!< LREL (Bitfield-Mask: 0x01)                            */
 #define R_IICA_IICCTL00_IICE_Pos      (7UL)    /*!< IICE (Bit 7)                                          */
 #define R_IICA_IICCTL00_IICE_Msk      (0x80UL) /*!< IICE (Bitfield-Mask: 0x01)                            */
/* =======================================================  IICCTL01  ======================================================== */
 #define R_IICA_IICCTL01_PRS_Pos       (0UL)    /*!< PRS (Bit 0)                                           */
 #define R_IICA_IICCTL01_PRS_Msk       (0x1UL)  /*!< PRS (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICCTL01_DFC_Pos       (2UL)    /*!< DFC (Bit 2)                                           */
 #define R_IICA_IICCTL01_DFC_Msk       (0x4UL)  /*!< DFC (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICCTL01_SMC_Pos       (3UL)    /*!< SMC (Bit 3)                                           */
 #define R_IICA_IICCTL01_SMC_Msk       (0x8UL)  /*!< SMC (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICCTL01_DAD_Pos       (4UL)    /*!< DAD (Bit 4)                                           */
 #define R_IICA_IICCTL01_DAD_Msk       (0x10UL) /*!< DAD (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICCTL01_CLD_Pos       (5UL)    /*!< CLD (Bit 5)                                           */
 #define R_IICA_IICCTL01_CLD_Msk       (0x20UL) /*!< CLD (Bitfield-Mask: 0x01)                             */
 #define R_IICA_IICCTL01_SVADIS_Pos    (6UL)    /*!< SVADIS (Bit 6)                                        */
 #define R_IICA_IICCTL01_SVADIS_Msk    (0x40UL) /*!< SVADIS (Bitfield-Mask: 0x01)                          */
 #define R_IICA_IICCTL01_WUP_Pos       (7UL)    /*!< WUP (Bit 7)                                           */
 #define R_IICA_IICCTL01_WUP_Msk       (0x80UL) /*!< WUP (Bitfield-Mask: 0x01)                             */
/* ========================================================  IICWL0  ========================================================= */
/* ========================================================  IICWH0  ========================================================= */
/* =========================================================  SVA0  ========================================================== */
 #define R_IICA_SVA0_A_Pos             (1UL)    /*!< A (Bit 1)                                             */
 #define R_IICA_SVA0_A_Msk             (0xfeUL) /*!< A (Bitfield-Mask: 0x7f)                               */

/* =========================================================================================================================== */
/* ================                                          R_IWDT                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  IWDTRR  ========================================================= */
 #define R_IWDT_IWDTRR_IWDTRR_Pos       (0UL)      /*!< IWDTRR (Bit 0)                                        */
 #define R_IWDT_IWDTRR_IWDTRR_Msk       (0xffUL)   /*!< IWDTRR (Bitfield-Mask: 0xff)                          */
/* ========================================================  IWDTCR  ========================================================= */
 #define R_IWDT_IWDTCR_RPSS_Pos         (12UL)     /*!< RPSS (Bit 12)                                         */
 #define R_IWDT_IWDTCR_RPSS_Msk         (0x3000UL) /*!< RPSS (Bitfield-Mask: 0x03)                            */
 #define R_IWDT_IWDTCR_RPES_Pos         (8UL)      /*!< RPES (Bit 8)                                          */
 #define R_IWDT_IWDTCR_RPES_Msk         (0x300UL)  /*!< RPES (Bitfield-Mask: 0x03)                            */
 #define R_IWDT_IWDTCR_CKS_Pos          (4UL)      /*!< CKS (Bit 4)                                           */
 #define R_IWDT_IWDTCR_CKS_Msk          (0xf0UL)   /*!< CKS (Bitfield-Mask: 0x0f)                             */
 #define R_IWDT_IWDTCR_TOPS_Pos         (0UL)      /*!< TOPS (Bit 0)                                          */
 #define R_IWDT_IWDTCR_TOPS_Msk         (0x3UL)    /*!< TOPS (Bitfield-Mask: 0x03)                            */
/* ========================================================  IWDTSR  ========================================================= */
 #define R_IWDT_IWDTSR_REFEF_Pos        (15UL)     /*!< REFEF (Bit 15)                                        */
 #define R_IWDT_IWDTSR_REFEF_Msk        (0x8000UL) /*!< REFEF (Bitfield-Mask: 0x01)                           */
 #define R_IWDT_IWDTSR_UNDFF_Pos        (14UL)     /*!< UNDFF (Bit 14)                                        */
 #define R_IWDT_IWDTSR_UNDFF_Msk        (0x4000UL) /*!< UNDFF (Bitfield-Mask: 0x01)                           */
 #define R_IWDT_IWDTSR_CNTVAL_Pos       (0UL)      /*!< CNTVAL (Bit 0)                                        */
 #define R_IWDT_IWDTSR_CNTVAL_Msk       (0x3fffUL) /*!< CNTVAL (Bitfield-Mask: 0x3fff)                        */
/* ========================================================  IWDTRCR  ======================================================== */
 #define R_IWDT_IWDTRCR_RSTIRQS_Pos     (7UL)      /*!< RSTIRQS (Bit 7)                                       */
 #define R_IWDT_IWDTRCR_RSTIRQS_Msk     (0x80UL)   /*!< RSTIRQS (Bitfield-Mask: 0x01)                         */
/* =======================================================  IWDTCSTPR  ======================================================= */
 #define R_IWDT_IWDTCSTPR_SLCSTP_Pos    (7UL)      /*!< SLCSTP (Bit 7)                                        */
 #define R_IWDT_IWDTCSTPR_SLCSTP_Msk    (0x80UL)   /*!< SLCSTP (Bitfield-Mask: 0x01)                          */

/* =========================================================================================================================== */
/* ================                                          R_MSTP                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  MSTPCRA  ======================================================== */
 #define R_MSTP_MSTPCRA_MSTPA_Pos        (0UL)      /*!< MSTPA (Bit 0)                                         */
 #define R_MSTP_MSTPCRA_MSTPA_Msk        (0x1UL)    /*!< MSTPA (Bitfield-Mask: 0x01)                           */
/* ========================================================  MSTPCRB  ======================================================== */
 #define R_MSTP_MSTPCRB_MSTPB_Pos        (0UL)      /*!< MSTPB (Bit 0)                                         */
 #define R_MSTP_MSTPCRB_MSTPB_Msk        (0x1UL)    /*!< MSTPB (Bitfield-Mask: 0x01)                           */
/* ========================================================  MSTPCRC  ======================================================== */
 #define R_MSTP_MSTPCRC_MSTPC_Pos        (0UL)      /*!< MSTPC (Bit 0)                                         */
 #define R_MSTP_MSTPCRC_MSTPC_Msk        (0x1UL)    /*!< MSTPC (Bitfield-Mask: 0x01)                           */
/* ========================================================  MSTPCRD  ======================================================== */
 #define R_MSTP_MSTPCRD_MSTPD_Pos        (0UL)      /*!< MSTPD (Bit 0)                                         */
 #define R_MSTP_MSTPCRD_MSTPD_Msk        (0x1UL)    /*!< MSTPD (Bitfield-Mask: 0x01)                           */
/* ========================================================  MSTPCRE  ======================================================== */
 #define R_MSTP_MSTPCRE_MSTPE_Pos        (0UL)      /*!< MSTPE (Bit 0)                                         */
 #define R_MSTP_MSTPCRE_MSTPE_Msk        (0x1UL)    /*!< MSTPE (Bitfield-Mask: 0x01)                           */
/* =======================================================  LSMRWDIS  ======================================================== */
 #define R_MSTP_LSMRWDIS_RTCRWDIS_Pos    (0UL)      /*!< RTCRWDIS (Bit 0)                                      */
 #define R_MSTP_LSMRWDIS_RTCRWDIS_Msk    (0x1UL)    /*!< RTCRWDIS (Bitfield-Mask: 0x01)                        */
 #define R_MSTP_LSMRWDIS_WDTDIS_Pos      (1UL)      /*!< WDTDIS (Bit 1)                                        */
 #define R_MSTP_LSMRWDIS_WDTDIS_Msk      (0x2UL)    /*!< WDTDIS (Bitfield-Mask: 0x01)                          */
 #define R_MSTP_LSMRWDIS_IWDTIDS_Pos     (2UL)      /*!< IWDTIDS (Bit 2)                                       */
 #define R_MSTP_LSMRWDIS_IWDTIDS_Msk     (0x4UL)    /*!< IWDTIDS (Bitfield-Mask: 0x01)                         */
 #define R_MSTP_LSMRWDIS_WREN_Pos        (7UL)      /*!< WREN (Bit 7)                                          */
 #define R_MSTP_LSMRWDIS_WREN_Msk        (0x80UL)   /*!< WREN (Bitfield-Mask: 0x01)                            */
 #define R_MSTP_LSMRWDIS_PRKEY_Pos       (8UL)      /*!< PRKEY (Bit 8)                                         */
 #define R_MSTP_LSMRWDIS_PRKEY_Msk       (0xff00UL) /*!< PRKEY (Bitfield-Mask: 0xff)                           */

/* =========================================================================================================================== */
/* ================                                          R_PORT0                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  PODR  ========================================================== */
 #define R_PORT0_PODR_PODR_Pos    (0UL)   /*!< PODR (Bit 0)                                          */
 #define R_PORT0_PODR_PODR_Msk    (0x1UL) /*!< PODR (Bitfield-Mask: 0x01)                            */
/* ==========================================================  PDR  ========================================================== */
 #define R_PORT0_PDR_PDR_Pos      (0UL)   /*!< PDR (Bit 0)                                           */
 #define R_PORT0_PDR_PDR_Msk      (0x1UL) /*!< PDR (Bitfield-Mask: 0x01)                             */
/* =========================================================  PIDR  ========================================================== */
 #define R_PORT0_PIDR_PIDR_Pos    (0UL)   /*!< PIDR (Bit 0)                                          */
 #define R_PORT0_PIDR_PIDR_Msk    (0x1UL) /*!< PIDR (Bitfield-Mask: 0x01)                            */
/* =========================================================  PORR  ========================================================== */
 #define R_PORT0_PORR_PORR_Pos    (0UL)   /*!< PORR (Bit 0)                                          */
 #define R_PORT0_PORR_PORR_Msk    (0x1UL) /*!< PORR (Bitfield-Mask: 0x01)                            */
/* =========================================================  POSR  ========================================================== */
 #define R_PORT0_POSR_POSR_Pos    (0UL)   /*!< POSR (Bit 0)                                          */
 #define R_PORT0_POSR_POSR_Msk    (0x1UL) /*!< POSR (Bitfield-Mask: 0x01)                            */
/* =========================================================  EORR  ========================================================== */
 #define R_PORT0_EORR_EORR_Pos    (0UL)   /*!< EORR (Bit 0)                                          */
 #define R_PORT0_EORR_EORR_Msk    (0x1UL) /*!< EORR (Bitfield-Mask: 0x01)                            */
/* =========================================================  EOSR  ========================================================== */
 #define R_PORT0_EOSR_EOSR_Pos    (0UL)   /*!< EOSR (Bit 0)                                          */
 #define R_PORT0_EOSR_EOSR_Msk    (0x1UL) /*!< EOSR (Bitfield-Mask: 0x01)                            */

/* =========================================================================================================================== */
/* ================                                          R_PORGA                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  SNFEN  ========================================================= */
 #define R_PORGA_SNFEN_SNFEN00_Pos    (0UL)    /*!< SNFEN00 (Bit 0)                                       */
 #define R_PORGA_SNFEN_SNFEN00_Msk    (0x1UL)  /*!< SNFEN00 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_SNFEN_SNFEN10_Pos    (2UL)    /*!< SNFEN10 (Bit 2)                                       */
 #define R_PORGA_SNFEN_SNFEN10_Msk    (0x4UL)  /*!< SNFEN10 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_SNFEN_SNFEN20_Pos    (4UL)    /*!< SNFEN20 (Bit 4)                                       */
 #define R_PORGA_SNFEN_SNFEN20_Msk    (0x10UL) /*!< SNFEN20 (Bitfield-Mask: 0x01)                         */
/* =========================================================  TNFEN  ========================================================= */
 #define R_PORGA_TNFEN_TNFEN00_Pos    (0UL)    /*!< TNFEN00 (Bit 0)                                       */
 #define R_PORGA_TNFEN_TNFEN00_Msk    (0x1UL)  /*!< TNFEN00 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_TNFEN_TNFEN01_Pos    (1UL)    /*!< TNFEN01 (Bit 1)                                       */
 #define R_PORGA_TNFEN_TNFEN01_Msk    (0x2UL)  /*!< TNFEN01 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_TNFEN_TNFEN02_Pos    (2UL)    /*!< TNFEN02 (Bit 2)                                       */
 #define R_PORGA_TNFEN_TNFEN02_Msk    (0x4UL)  /*!< TNFEN02 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_TNFEN_TNFEN03_Pos    (3UL)    /*!< TNFEN03 (Bit 3)                                       */
 #define R_PORGA_TNFEN_TNFEN03_Msk    (0x8UL)  /*!< TNFEN03 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_TNFEN_TNFEN04_Pos    (4UL)    /*!< TNFEN04 (Bit 4)                                       */
 #define R_PORGA_TNFEN_TNFEN04_Msk    (0x10UL) /*!< TNFEN04 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_TNFEN_TNFEN05_Pos    (5UL)    /*!< TNFEN05 (Bit 5)                                       */
 #define R_PORGA_TNFEN_TNFEN05_Msk    (0x20UL) /*!< TNFEN05 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_TNFEN_TNFEN06_Pos    (6UL)    /*!< TNFEN06 (Bit 6)                                       */
 #define R_PORGA_TNFEN_TNFEN06_Msk    (0x40UL) /*!< TNFEN06 (Bitfield-Mask: 0x01)                         */
 #define R_PORGA_TNFEN_TNFEN07_Pos    (7UL)    /*!< TNFEN07 (Bit 7)                                       */
 #define R_PORGA_TNFEN_TNFEN07_Msk    (0x80UL) /*!< TNFEN07 (Bitfield-Mask: 0x01)                         */
/* ==========================================================  ISC  ========================================================== */
 #define R_PORGA_ISC_ISC0_Pos         (0UL)    /*!< ISC0 (Bit 0)                                          */
 #define R_PORGA_ISC_ISC0_Msk         (0x1UL)  /*!< ISC0 (Bitfield-Mask: 0x01)                            */
 #define R_PORGA_ISC_ISC1_Pos         (1UL)    /*!< ISC1 (Bit 1)                                          */
 #define R_PORGA_ISC_ISC1_Msk         (0x2UL)  /*!< ISC1 (Bitfield-Mask: 0x01)                            */
 #define R_PORGA_ISC_SSIE00_Pos       (2UL)    /*!< SSIE00 (Bit 2)                                        */
 #define R_PORGA_ISC_SSIE00_Msk       (0x4UL)  /*!< SSIE00 (Bitfield-Mask: 0x01)                          */
/* =========================================================  TIS0  ========================================================== */
 #define R_PORGA_TIS0_TIS_Pos         (0UL)    /*!< TIS (Bit 0)                                           */
 #define R_PORGA_TIS0_TIS_Msk         (0x7UL)  /*!< TIS (Bitfield-Mask: 0x07)                             */
/* =========================================================  TIS1  ========================================================== */
 #define R_PORGA_TIS1_TIS0_Pos        (0UL)    /*!< TIS0 (Bit 0)                                          */
 #define R_PORGA_TIS1_TIS0_Msk        (0x1UL)  /*!< TIS0 (Bitfield-Mask: 0x01)                            */
 #define R_PORGA_TIS1_TIS1_Pos        (1UL)    /*!< TIS1 (Bit 1)                                          */
 #define R_PORGA_TIS1_TIS1_Msk        (0x2UL)  /*!< TIS1 (Bitfield-Mask: 0x01)                            */
/* =========================================================  ULBS  ========================================================== */
 #define R_PORGA_ULBS_ULBS0_Pos       (0UL)    /*!< ULBS0 (Bit 0)                                         */
 #define R_PORGA_ULBS_ULBS0_Msk       (0x1UL)  /*!< ULBS0 (Bitfield-Mask: 0x01)                           */
 #define R_PORGA_ULBS_ULBS1_Pos       (1UL)    /*!< ULBS1 (Bit 1)                                         */
 #define R_PORGA_ULBS_ULBS1_Msk       (0x2UL)  /*!< ULBS1 (Bitfield-Mask: 0x01)                           */
 #define R_PORGA_ULBS_ULBS2_Pos       (2UL)    /*!< ULBS2 (Bit 2)                                         */
 #define R_PORGA_ULBS_ULBS2_Msk       (0x4UL)  /*!< ULBS2 (Bitfield-Mask: 0x01)                           */
 #define R_PORGA_ULBS_ULBS4_Pos       (4UL)    /*!< ULBS4 (Bit 4)                                         */
 #define R_PORGA_ULBS_ULBS4_Msk       (0x10UL) /*!< ULBS4 (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                           R_PFS                                           ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                                          R_PMISC                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  PWPR  ========================================================== */
 #define R_PMISC_PWPR_PFSWE_Pos    (6UL)    /*!< PFSWE (Bit 6)                                         */
 #define R_PMISC_PWPR_PFSWE_Msk    (0x40UL) /*!< PFSWE (Bitfield-Mask: 0x01)                           */
 #define R_PMISC_PWPR_B0WI_Pos     (7UL)    /*!< B0WI (Bit 7)                                          */
 #define R_PMISC_PWPR_B0WI_Msk     (0x80UL) /*!< B0WI (Bitfield-Mask: 0x01)                            */

/* =========================================================================================================================== */
/* ================                                          R_SAU0                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  SDR  ========================================================== */
 #define R_SAU0_SDR_DAT_Pos      (0UL)      /*!< DAT (Bit 0)                                           */
 #define R_SAU0_SDR_DAT_Msk      (0x1ffUL)  /*!< DAT (Bitfield-Mask: 0x1ff)                            */
 #define R_SAU0_SDR_STCLK_Pos    (9UL)      /*!< STCLK (Bit 9)                                         */
 #define R_SAU0_SDR_STCLK_Msk    (0xfe00UL) /*!< STCLK (Bitfield-Mask: 0x7f)                           */
/* ==========================================================  SSR  ========================================================== */
 #define R_SAU0_SSR_OVF_Pos      (0UL)      /*!< OVF (Bit 0)                                           */
 #define R_SAU0_SSR_OVF_Msk      (0x1UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SSR_PEF_Pos      (1UL)      /*!< PEF (Bit 1)                                           */
 #define R_SAU0_SSR_PEF_Msk      (0x2UL)    /*!< PEF (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SSR_FEF_Pos      (2UL)      /*!< FEF (Bit 2)                                           */
 #define R_SAU0_SSR_FEF_Msk      (0x4UL)    /*!< FEF (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SSR_BFF_Pos      (5UL)      /*!< BFF (Bit 5)                                           */
 #define R_SAU0_SSR_BFF_Msk      (0x20UL)   /*!< BFF (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SSR_TSF_Pos      (6UL)      /*!< TSF (Bit 6)                                           */
 #define R_SAU0_SSR_TSF_Msk      (0x40UL)   /*!< TSF (Bitfield-Mask: 0x01)                             */
/* ==========================================================  SIR  ========================================================== */
 #define R_SAU0_SIR_OVCT_Pos     (0UL)      /*!< OVCT (Bit 0)                                          */
 #define R_SAU0_SIR_OVCT_Msk     (0x1UL)    /*!< OVCT (Bitfield-Mask: 0x01)                            */
 #define R_SAU0_SIR_PECT_Pos     (1UL)      /*!< PECT (Bit 1)                                          */
 #define R_SAU0_SIR_PECT_Msk     (0x2UL)    /*!< PECT (Bitfield-Mask: 0x01)                            */
 #define R_SAU0_SIR_FECT_Pos     (2UL)      /*!< FECT (Bit 2)                                          */
 #define R_SAU0_SIR_FECT_Msk     (0x4UL)    /*!< FECT (Bitfield-Mask: 0x01)                            */
/* ==========================================================  SMR  ========================================================== */
 #define R_SAU0_SMR_MD0_Pos      (0UL)      /*!< MD0 (Bit 0)                                           */
 #define R_SAU0_SMR_MD0_Msk      (0x1UL)    /*!< MD0 (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SMR_MD1_Pos      (1UL)      /*!< MD1 (Bit 1)                                           */
 #define R_SAU0_SMR_MD1_Msk      (0x6UL)    /*!< MD1 (Bitfield-Mask: 0x03)                             */
 #define R_SAU0_SMR_SIS0_Pos     (6UL)      /*!< SIS0 (Bit 6)                                          */
 #define R_SAU0_SMR_SIS0_Msk     (0x40UL)   /*!< SIS0 (Bitfield-Mask: 0x01)                            */
 #define R_SAU0_SMR_STS_Pos      (8UL)      /*!< STS (Bit 8)                                           */
 #define R_SAU0_SMR_STS_Msk      (0x100UL)  /*!< STS (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SMR_CCS_Pos      (14UL)     /*!< CCS (Bit 14)                                          */
 #define R_SAU0_SMR_CCS_Msk      (0x4000UL) /*!< CCS (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SMR_CKS_Pos      (15UL)     /*!< CKS (Bit 15)                                          */
 #define R_SAU0_SMR_CKS_Msk      (0x8000UL) /*!< CKS (Bitfield-Mask: 0x01)                             */
/* ==========================================================  SCR  ========================================================== */
 #define R_SAU0_SCR_DLS_Pos      (0UL)      /*!< DLS (Bit 0)                                           */
 #define R_SAU0_SCR_DLS_Msk      (0x3UL)    /*!< DLS (Bitfield-Mask: 0x03)                             */
 #define R_SAU0_SCR_SLC_Pos      (4UL)      /*!< SLC (Bit 4)                                           */
 #define R_SAU0_SCR_SLC_Msk      (0x30UL)   /*!< SLC (Bitfield-Mask: 0x03)                             */
 #define R_SAU0_SCR_DIR_Pos      (7UL)      /*!< DIR (Bit 7)                                           */
 #define R_SAU0_SCR_DIR_Msk      (0x80UL)   /*!< DIR (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SCR_PTC_Pos      (8UL)      /*!< PTC (Bit 8)                                           */
 #define R_SAU0_SCR_PTC_Msk      (0x300UL)  /*!< PTC (Bitfield-Mask: 0x03)                             */
 #define R_SAU0_SCR_EOC_Pos      (10UL)     /*!< EOC (Bit 10)                                          */
 #define R_SAU0_SCR_EOC_Msk      (0x400UL)  /*!< EOC (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SCR_DCP_Pos      (12UL)     /*!< DCP (Bit 12)                                          */
 #define R_SAU0_SCR_DCP_Msk      (0x3000UL) /*!< DCP (Bitfield-Mask: 0x03)                             */
 #define R_SAU0_SCR_TRXE_Pos     (14UL)     /*!< TRXE (Bit 14)                                         */
 #define R_SAU0_SCR_TRXE_Msk     (0xc000UL) /*!< TRXE (Bitfield-Mask: 0x03)                            */
/* ==========================================================  SE  =========================================================== */
 #define R_SAU0_SE_SE_Pos        (0UL)      /*!< SE (Bit 0)                                            */
 #define R_SAU0_SE_SE_Msk        (0xfUL)    /*!< SE (Bitfield-Mask: 0x0f)                              */
/* ==========================================================  SS  =========================================================== */
 #define R_SAU0_SS_SS_Pos        (0UL)      /*!< SS (Bit 0)                                            */
 #define R_SAU0_SS_SS_Msk        (0xfUL)    /*!< SS (Bitfield-Mask: 0x0f)                              */
/* ==========================================================  ST  =========================================================== */
 #define R_SAU0_ST_ST_Pos        (0UL)      /*!< ST (Bit 0)                                            */
 #define R_SAU0_ST_ST_Msk        (0xfUL)    /*!< ST (Bitfield-Mask: 0x0f)                              */
/* ==========================================================  SPS  ========================================================== */
 #define R_SAU0_SPS_PRS0_Pos     (0UL)      /*!< PRS0 (Bit 0)                                          */
 #define R_SAU0_SPS_PRS0_Msk     (0xfUL)    /*!< PRS0 (Bitfield-Mask: 0x0f)                            */
 #define R_SAU0_SPS_PRS1_Pos     (4UL)      /*!< PRS1 (Bit 4)                                          */
 #define R_SAU0_SPS_PRS1_Msk     (0xf0UL)   /*!< PRS1 (Bitfield-Mask: 0x0f)                            */
/* ==========================================================  SO  =========================================================== */
 #define R_SAU0_SO_SO_Pos        (0UL)      /*!< SO (Bit 0)                                            */
 #define R_SAU0_SO_SO_Msk        (0xfUL)    /*!< SO (Bitfield-Mask: 0x0f)                              */
 #define R_SAU0_SO_CKO_Pos       (8UL)      /*!< CKO (Bit 8)                                           */
 #define R_SAU0_SO_CKO_Msk       (0xf00UL)  /*!< CKO (Bitfield-Mask: 0x0f)                             */
/* ==========================================================  SOE  ========================================================== */
 #define R_SAU0_SOE_SOE_Pos      (0UL)      /*!< SOE (Bit 0)                                           */
 #define R_SAU0_SOE_SOE_Msk      (0xfUL)    /*!< SOE (Bitfield-Mask: 0x0f)                             */
/* ==========================================================  SOL  ========================================================== */
 #define R_SAU0_SOL_SOL_Pos      (0UL)      /*!< SOL (Bit 0)                                           */
 #define R_SAU0_SOL_SOL_Msk      (0x1UL)    /*!< SOL (Bitfield-Mask: 0x01)                             */
/* ==========================================================  SSC  ========================================================== */
 #define R_SAU0_SSC_SWC_Pos      (0UL)      /*!< SWC (Bit 0)                                           */
 #define R_SAU0_SSC_SWC_Msk      (0x1UL)    /*!< SWC (Bitfield-Mask: 0x01)                             */
 #define R_SAU0_SSC_SSEC_Pos     (1UL)      /*!< SSEC (Bit 1)                                          */
 #define R_SAU0_SSC_SSEC_Msk     (0x2UL)    /*!< SSEC (Bitfield-Mask: 0x01)                            */

/* =========================================================================================================================== */
/* ================                                          R_SRAM                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  PARIOAD  ======================================================== */
 #define R_SRAM_PARIOAD_OAD_Pos            (0UL)    /*!< OAD (Bit 0)                                           */
 #define R_SRAM_PARIOAD_OAD_Msk            (0x1UL)  /*!< OAD (Bitfield-Mask: 0x01)                             */
/* =======================================================  SRAMPRCR  ======================================================== */
 #define R_SRAM_SRAMPRCR_KW_Pos            (1UL)    /*!< KW (Bit 1)                                            */
 #define R_SRAM_SRAMPRCR_KW_Msk            (0xfeUL) /*!< KW (Bitfield-Mask: 0x7f)                              */
 #define R_SRAM_SRAMPRCR_SRAMPRCR_Pos      (0UL)    /*!< SRAMPRCR (Bit 0)                                      */
 #define R_SRAM_SRAMPRCR_SRAMPRCR_Msk      (0x1UL)  /*!< SRAMPRCR (Bitfield-Mask: 0x01)                        */
/* =======================================================  SRAMWTSC  ======================================================== */
/* ========================================================  ECCMODE  ======================================================== */
 #define R_SRAM_ECCMODE_ECCMOD_Pos         (0UL)    /*!< ECCMOD (Bit 0)                                        */
 #define R_SRAM_ECCMODE_ECCMOD_Msk         (0x3UL)  /*!< ECCMOD (Bitfield-Mask: 0x03)                          */
/* ========================================================  ECC2STS  ======================================================== */
 #define R_SRAM_ECC2STS_ECC2ERR_Pos        (0UL)    /*!< ECC2ERR (Bit 0)                                       */
 #define R_SRAM_ECC2STS_ECC2ERR_Msk        (0x1UL)  /*!< ECC2ERR (Bitfield-Mask: 0x01)                         */
/* =======================================================  ECC1STSEN  ======================================================= */
 #define R_SRAM_ECC1STSEN_E1STSEN_Pos      (0UL)    /*!< E1STSEN (Bit 0)                                       */
 #define R_SRAM_ECC1STSEN_E1STSEN_Msk      (0x1UL)  /*!< E1STSEN (Bitfield-Mask: 0x01)                         */
/* ========================================================  ECC1STS  ======================================================== */
 #define R_SRAM_ECC1STS_ECC1ERR_Pos        (0UL)    /*!< ECC1ERR (Bit 0)                                       */
 #define R_SRAM_ECC1STS_ECC1ERR_Msk        (0x1UL)  /*!< ECC1ERR (Bitfield-Mask: 0x01)                         */
/* ========================================================  ECCPRCR  ======================================================== */
 #define R_SRAM_ECCPRCR_KW_Pos             (1UL)    /*!< KW (Bit 1)                                            */
 #define R_SRAM_ECCPRCR_KW_Msk             (0xfeUL) /*!< KW (Bitfield-Mask: 0x7f)                              */
 #define R_SRAM_ECCPRCR_ECCPRCR_Pos        (0UL)    /*!< ECCPRCR (Bit 0)                                       */
 #define R_SRAM_ECCPRCR_ECCPRCR_Msk        (0x1UL)  /*!< ECCPRCR (Bitfield-Mask: 0x01)                         */
/* =======================================================  ECCPRCR2  ======================================================== */
 #define R_SRAM_ECCPRCR2_KW2_Pos           (1UL)    /*!< KW2 (Bit 1)                                           */
 #define R_SRAM_ECCPRCR2_KW2_Msk           (0xfeUL) /*!< KW2 (Bitfield-Mask: 0x7f)                             */
 #define R_SRAM_ECCPRCR2_ECCPRCR2_Pos      (0UL)    /*!< ECCPRCR2 (Bit 0)                                      */
 #define R_SRAM_ECCPRCR2_ECCPRCR2_Msk      (0x1UL)  /*!< ECCPRCR2 (Bitfield-Mask: 0x01)                        */
/* ========================================================  ECCETST  ======================================================== */
 #define R_SRAM_ECCETST_TSTBYP_Pos         (0UL)    /*!< TSTBYP (Bit 0)                                        */
 #define R_SRAM_ECCETST_TSTBYP_Msk         (0x1UL)  /*!< TSTBYP (Bitfield-Mask: 0x01)                          */
/* ========================================================  ECCOAD  ========================================================= */
 #define R_SRAM_ECCOAD_OAD_Pos             (0UL)    /*!< OAD (Bit 0)                                           */
 #define R_SRAM_ECCOAD_OAD_Msk             (0x1UL)  /*!< OAD (Bitfield-Mask: 0x01)                             */
/* =======================================================  SRAMPRCR2  ======================================================= */
 #define R_SRAM_SRAMPRCR2_SRAMPRCR2_Pos    (0UL)    /*!< SRAMPRCR2 (Bit 0)                                     */
 #define R_SRAM_SRAMPRCR2_SRAMPRCR2_Msk    (0x1UL)  /*!< SRAMPRCR2 (Bitfield-Mask: 0x01)                       */
 #define R_SRAM_SRAMPRCR2_KW_Pos           (1UL)    /*!< KW (Bit 1)                                            */
 #define R_SRAM_SRAMPRCR2_KW_Msk           (0xfeUL) /*!< KW (Bitfield-Mask: 0x7f)                              */

/* =========================================================================================================================== */
/* ================                                         R_SYSTEM                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  CMC  ========================================================== */
 #define R_SYSTEM_CMC_MODRV_Pos          (0UL)      /*!< MODRV (Bit 0)                                         */
 #define R_SYSTEM_CMC_MODRV_Msk          (0x1UL)    /*!< MODRV (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_CMC_SODRV_Pos          (1UL)      /*!< SODRV (Bit 1)                                         */
 #define R_SYSTEM_CMC_SODRV_Msk          (0x6UL)    /*!< SODRV (Bitfield-Mask: 0x03)                           */
 #define R_SYSTEM_CMC_XTSEL_Pos          (3UL)      /*!< XTSEL (Bit 3)                                         */
 #define R_SYSTEM_CMC_XTSEL_Msk          (0x8UL)    /*!< XTSEL (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_CMC_SOSEL_Pos          (4UL)      /*!< SOSEL (Bit 4)                                         */
 #define R_SYSTEM_CMC_SOSEL_Msk          (0x10UL)   /*!< SOSEL (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_CMC_MOSEL_Pos          (6UL)      /*!< MOSEL (Bit 6)                                         */
 #define R_SYSTEM_CMC_MOSEL_Msk          (0xc0UL)   /*!< MOSEL (Bitfield-Mask: 0x03)                           */
/* =========================================================  SOMRG  ========================================================= */
 #define R_SYSTEM_SOMRG_SOSCMRG_Pos      (0UL)      /*!< SOSCMRG (Bit 0)                                       */
 #define R_SYSTEM_SOMRG_SOSCMRG_Msk      (0x3UL)    /*!< SOSCMRG (Bitfield-Mask: 0x03)                         */
/* ========================================================  MIOTRM  ========================================================= */
 #define R_SYSTEM_MIOTRM_MIOTRM_Pos      (0UL)      /*!< MIOTRM (Bit 0)                                        */
 #define R_SYSTEM_MIOTRM_MIOTRM_Msk      (0xffUL)   /*!< MIOTRM (Bitfield-Mask: 0xff)                          */
/* ========================================================  LIOTRM  ========================================================= */
 #define R_SYSTEM_LIOTRM_LIOTRM_Pos      (0UL)      /*!< LIOTRM (Bit 0)                                        */
 #define R_SYSTEM_LIOTRM_LIOTRM_Msk      (0xffUL)   /*!< LIOTRM (Bitfield-Mask: 0xff)                          */
/* ========================================================  HOCOCR  ========================================================= */
 #define R_SYSTEM_HOCOCR_HCSTP_Pos       (0UL)      /*!< HCSTP (Bit 0)                                         */
 #define R_SYSTEM_HOCOCR_HCSTP_Msk       (0x1UL)    /*!< HCSTP (Bitfield-Mask: 0x01)                           */
/* ========================================================  MOCOCR  ========================================================= */
 #define R_SYSTEM_MOCOCR_MCSTP_Pos       (0UL)      /*!< MCSTP (Bit 0)                                         */
 #define R_SYSTEM_MOCOCR_MCSTP_Msk       (0x1UL)    /*!< MCSTP (Bitfield-Mask: 0x01)                           */
/* ========================================================  LOCOCR  ========================================================= */
 #define R_SYSTEM_LOCOCR_LCSTP_Pos       (0UL)      /*!< LCSTP (Bit 0)                                         */
 #define R_SYSTEM_LOCOCR_LCSTP_Msk       (0x1UL)    /*!< LCSTP (Bitfield-Mask: 0x01)                           */
/* ========================================================  MOSCCR  ========================================================= */
 #define R_SYSTEM_MOSCCR_MOSTP_Pos       (0UL)      /*!< MOSTP (Bit 0)                                         */
 #define R_SYSTEM_MOSCCR_MOSTP_Msk       (0x1UL)    /*!< MOSTP (Bitfield-Mask: 0x01)                           */
/* ========================================================  SOSCCR  ========================================================= */
 #define R_SYSTEM_SOSCCR_SOSTP_Pos       (0UL)      /*!< SOSTP (Bit 0)                                         */
 #define R_SYSTEM_SOSCCR_SOSTP_Msk       (0x1UL)    /*!< SOSTP (Bitfield-Mask: 0x01)                           */
/* =========================================================  OSTC  ========================================================== */
 #define R_SYSTEM_OSTC_MOST_Pos          (0UL)      /*!< MOST (Bit 0)                                          */
 #define R_SYSTEM_OSTC_MOST_Msk          (0xffUL)   /*!< MOST (Bitfield-Mask: 0xff)                            */
/* =========================================================  OSTS  ========================================================== */
 #define R_SYSTEM_OSTS_OSTSB_Pos         (0UL)      /*!< OSTSB (Bit 0)                                         */
 #define R_SYSTEM_OSTS_OSTSB_Msk         (0x7UL)    /*!< OSTSB (Bitfield-Mask: 0x07)                           */
/* =========================================================  OSCSF  ========================================================= */
 #define R_SYSTEM_OSCSF_HOCOSF_Pos       (0UL)      /*!< HOCOSF (Bit 0)                                        */
 #define R_SYSTEM_OSCSF_HOCOSF_Msk       (0x1UL)    /*!< HOCOSF (Bitfield-Mask: 0x01)                          */
/* ========================================================  HOCODIV  ======================================================== */
 #define R_SYSTEM_HOCODIV_DIV_Pos        (0UL)      /*!< DIV (Bit 0)                                           */
 #define R_SYSTEM_HOCODIV_DIV_Msk        (0x7UL)    /*!< DIV (Bitfield-Mask: 0x07)                             */
/* ========================================================  MOCODIV  ======================================================== */
 #define R_SYSTEM_MOCODIV_DIV_Pos        (0UL)      /*!< DIV (Bit 0)                                           */
 #define R_SYSTEM_MOCODIV_DIV_Msk        (0x3UL)    /*!< DIV (Bitfield-Mask: 0x03)                             */
/* ========================================================  MOSCDIV  ======================================================== */
 #define R_SYSTEM_MOSCDIV_DIV_Pos        (0UL)      /*!< DIV (Bit 0)                                           */
 #define R_SYSTEM_MOSCDIV_DIV_Msk        (0x7UL)    /*!< DIV (Bitfield-Mask: 0x07)                             */
/* ========================================================  FOCOSCR  ======================================================== */
 #define R_SYSTEM_FOCOSCR_CKSEL_Pos      (0UL)      /*!< CKSEL (Bit 0)                                         */
 #define R_SYSTEM_FOCOSCR_CKSEL_Msk      (0x1UL)    /*!< CKSEL (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_FOCOSCR_CKST_Pos       (1UL)      /*!< CKST (Bit 1)                                          */
 #define R_SYSTEM_FOCOSCR_CKST_Msk       (0x2UL)    /*!< CKST (Bitfield-Mask: 0x01)                            */
/* =======================================================  FMAINSCR  ======================================================== */
 #define R_SYSTEM_FMAINSCR_CKSEL_Pos     (0UL)      /*!< CKSEL (Bit 0)                                         */
 #define R_SYSTEM_FMAINSCR_CKSEL_Msk     (0x1UL)    /*!< CKSEL (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_FMAINSCR_CKST_Pos      (1UL)      /*!< CKST (Bit 1)                                          */
 #define R_SYSTEM_FMAINSCR_CKST_Msk      (0x2UL)    /*!< CKST (Bitfield-Mask: 0x01)                            */
/* ========================================================  FSUBSCR  ======================================================== */
 #define R_SYSTEM_FSUBSCR_CKSEL_Pos      (0UL)      /*!< CKSEL (Bit 0)                                         */
 #define R_SYSTEM_FSUBSCR_CKSEL_Msk      (0x1UL)    /*!< CKSEL (Bitfield-Mask: 0x01)                           */
/* ========================================================  ICLKSCR  ======================================================== */
 #define R_SYSTEM_ICLKSCR_CKSEL_Pos      (0UL)      /*!< CKSEL (Bit 0)                                         */
 #define R_SYSTEM_ICLKSCR_CKSEL_Msk      (0x1UL)    /*!< CKSEL (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_ICLKSCR_CKST_Pos       (1UL)      /*!< CKST (Bit 1)                                          */
 #define R_SYSTEM_ICLKSCR_CKST_Msk       (0x2UL)    /*!< CKST (Bitfield-Mask: 0x01)                            */
/* =========================================================  OSMC  ========================================================== */
 #define R_SYSTEM_OSMC_WUTMMCK0_Pos      (4UL)      /*!< WUTMMCK0 (Bit 4)                                      */
 #define R_SYSTEM_OSMC_WUTMMCK0_Msk      (0x10UL)   /*!< WUTMMCK0 (Bitfield-Mask: 0x01)                        */
/* =========================================================  RESF  ========================================================== */
 #define R_SYSTEM_RESF_LVIRF_Pos         (0UL)      /*!< LVIRF (Bit 0)                                         */
 #define R_SYSTEM_RESF_LVIRF_Msk         (0x1UL)    /*!< LVIRF (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_RESF_RPERF_Pos         (2UL)      /*!< RPERF (Bit 2)                                         */
 #define R_SYSTEM_RESF_RPERF_Msk         (0x4UL)    /*!< RPERF (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_RESF_IWDTRF_Pos        (4UL)      /*!< IWDTRF (Bit 4)                                        */
 #define R_SYSTEM_RESF_IWDTRF_Msk        (0x10UL)   /*!< IWDTRF (Bitfield-Mask: 0x01)                          */
 #define R_SYSTEM_RESF_SWRF_Pos          (5UL)      /*!< SWRF (Bit 5)                                          */
 #define R_SYSTEM_RESF_SWRF_Msk          (0x20UL)   /*!< SWRF (Bitfield-Mask: 0x01)                            */
/* =========================================================  PORSR  ========================================================= */
 #define R_SYSTEM_PORSR_PORF_Pos         (0UL)      /*!< PORF (Bit 0)                                          */
 #define R_SYSTEM_PORSR_PORF_Msk         (0x1UL)    /*!< PORF (Bitfield-Mask: 0x01)                            */
/* ========================================================  LVD1CR  ========================================================= */
 #define R_SYSTEM_LVD1CR_LVD1V_Pos       (0UL)      /*!< LVD1V (Bit 0)                                         */
 #define R_SYSTEM_LVD1CR_LVD1V_Msk       (0x1fUL)   /*!< LVD1V (Bitfield-Mask: 0x1f)                           */
 #define R_SYSTEM_LVD1CR_IRQSEL_Pos      (5UL)      /*!< IRQSEL (Bit 5)                                        */
 #define R_SYSTEM_LVD1CR_IRQSEL_Msk      (0x20UL)   /*!< IRQSEL (Bitfield-Mask: 0x01)                          */
 #define R_SYSTEM_LVD1CR_LVD1SEL_Pos     (6UL)      /*!< LVD1SEL (Bit 6)                                       */
 #define R_SYSTEM_LVD1CR_LVD1SEL_Msk     (0x40UL)   /*!< LVD1SEL (Bitfield-Mask: 0x01)                         */
 #define R_SYSTEM_LVD1CR_LVD1EN_Pos      (7UL)      /*!< LVD1EN (Bit 7)                                        */
 #define R_SYSTEM_LVD1CR_LVD1EN_Msk      (0x80UL)   /*!< LVD1EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  LVD1MKR  ======================================================== */
 #define R_SYSTEM_LVD1MKR_MK_Pos         (0UL)      /*!< MK (Bit 0)                                            */
 #define R_SYSTEM_LVD1MKR_MK_Msk         (0x1UL)    /*!< MK (Bitfield-Mask: 0x01)                              */
/* ========================================================  LVD1SR  ========================================================= */
 #define R_SYSTEM_LVD1SR_DET_Pos         (0UL)      /*!< DET (Bit 0)                                           */
 #define R_SYSTEM_LVD1SR_DET_Msk         (0x1UL)    /*!< DET (Bitfield-Mask: 0x01)                             */
 #define R_SYSTEM_LVD1SR_MON_Pos         (1UL)      /*!< MON (Bit 1)                                           */
 #define R_SYSTEM_LVD1SR_MON_Msk         (0x2UL)    /*!< MON (Bitfield-Mask: 0x01)                             */
/* =========================================================  SBYCR  ========================================================= */
 #define R_SYSTEM_SBYCR_FLSTP_Pos        (7UL)      /*!< FLSTP (Bit 7)                                         */
 #define R_SYSTEM_SBYCR_FLSTP_Msk        (0x80UL)   /*!< FLSTP (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_SBYCR_FWKUP_Pos        (8UL)      /*!< FWKUP (Bit 8)                                         */
 #define R_SYSTEM_SBYCR_FWKUP_Msk        (0x100UL)  /*!< FWKUP (Bitfield-Mask: 0x01)                           */
 #define R_SYSTEM_SBYCR_RTCLPC_Pos       (9UL)      /*!< RTCLPC (Bit 9)                                        */
 #define R_SYSTEM_SBYCR_RTCLPC_Msk       (0x200UL)  /*!< RTCLPC (Bitfield-Mask: 0x01)                          */
 #define R_SYSTEM_SBYCR_SSBY_Pos         (15UL)     /*!< SSBY (Bit 15)                                         */
 #define R_SYSTEM_SBYCR_SSBY_Msk         (0x8000UL) /*!< SSBY (Bitfield-Mask: 0x01)                            */
/* =========================================================  PSMCR  ========================================================= */
 #define R_SYSTEM_PSMCR_RAMSD_Pos        (0UL)      /*!< RAMSD (Bit 0)                                         */
 #define R_SYSTEM_PSMCR_RAMSD_Msk        (0x3UL)    /*!< RAMSD (Bitfield-Mask: 0x03)                           */
/* ========================================================  SYOCDCR  ======================================================== */
 #define R_SYSTEM_SYOCDCR_DBGEN_Pos      (7UL)      /*!< DBGEN (Bit 7)                                         */
 #define R_SYSTEM_SYOCDCR_DBGEN_Msk      (0x80UL)   /*!< DBGEN (Bitfield-Mask: 0x01)                           */
/* =========================================================  PRCR  ========================================================== */
 #define R_SYSTEM_PRCR_PRC0_Pos          (0UL)      /*!< PRC0 (Bit 0)                                          */
 #define R_SYSTEM_PRCR_PRC0_Msk          (0x1UL)    /*!< PRC0 (Bitfield-Mask: 0x01)                            */
 #define R_SYSTEM_PRCR_PRC1_Pos          (1UL)      /*!< PRC1 (Bit 1)                                          */
 #define R_SYSTEM_PRCR_PRC1_Msk          (0x2UL)    /*!< PRC1 (Bitfield-Mask: 0x01)                            */
 #define R_SYSTEM_PRCR_PRC3_Pos          (3UL)      /*!< PRC3 (Bit 3)                                          */
 #define R_SYSTEM_PRCR_PRC3_Msk          (0x8UL)    /*!< PRC3 (Bitfield-Mask: 0x01)                            */
 #define R_SYSTEM_PRCR_PRKEY_Pos         (8UL)      /*!< PRKEY (Bit 8)                                         */
 #define R_SYSTEM_PRCR_PRKEY_Msk         (0xff00UL) /*!< PRKEY (Bitfield-Mask: 0xff)                           */
/* ========================================================  MSTPCRA  ======================================================== */
 #define R_SYSTEM_MSTPCRA_MSTPA22_Pos    (6UL)      /*!< MSTPA22 (Bit 6)                                       */
 #define R_SYSTEM_MSTPCRA_MSTPA22_Msk    (0x40UL)   /*!< MSTPA22 (Bitfield-Mask: 0x01)                         */
/* =========================================================  LPOPT  ========================================================= */
 #define R_SYSTEM_LPOPT_DCLKDIS_Pos      (1UL)      /*!< DCLKDIS (Bit 1)                                       */
 #define R_SYSTEM_LPOPT_DCLKDIS_Msk      (0x6UL)    /*!< DCLKDIS (Bitfield-Mask: 0x03)                         */
 #define R_SYSTEM_LPOPT_BPFCLKDIS_Pos    (3UL)      /*!< BPFCLKDIS (Bit 3)                                     */
 #define R_SYSTEM_LPOPT_BPFCLKDIS_Msk    (0x8UL)    /*!< BPFCLKDIS (Bitfield-Mask: 0x01)                       */
 #define R_SYSTEM_LPOPT_LPOPTEN_Pos      (7UL)      /*!< LPOPTEN (Bit 7)                                       */
 #define R_SYSTEM_LPOPT_LPOPTEN_Msk      (0x80UL)   /*!< LPOPTEN (Bitfield-Mask: 0x01)                         */

/* =========================================================================================================================== */
/* ================                                           R_TAU                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  TCR0  ========================================================== */
/* =========================================================  TMR0  ========================================================== */
 #define R_TAU_TMR0_OPIRQ_Pos           (0UL)      /*!< OPIRQ (Bit 0)                                         */
 #define R_TAU_TMR0_OPIRQ_Msk           (0x1UL)    /*!< OPIRQ (Bitfield-Mask: 0x01)                           */
 #define R_TAU_TMR0_MD_Pos              (1UL)      /*!< MD (Bit 1)                                            */
 #define R_TAU_TMR0_MD_Msk              (0xeUL)    /*!< MD (Bitfield-Mask: 0x07)                              */
 #define R_TAU_TMR0_CIS_Pos             (6UL)      /*!< CIS (Bit 6)                                           */
 #define R_TAU_TMR0_CIS_Msk             (0xc0UL)   /*!< CIS (Bitfield-Mask: 0x03)                             */
 #define R_TAU_TMR0_STS_Pos             (8UL)      /*!< STS (Bit 8)                                           */
 #define R_TAU_TMR0_STS_Msk             (0x700UL)  /*!< STS (Bitfield-Mask: 0x07)                             */
 #define R_TAU_TMR0_MASTER_SPLIT_Pos    (11UL)     /*!< MASTER_SPLIT (Bit 11)                                 */
 #define R_TAU_TMR0_MASTER_SPLIT_Msk    (0x800UL)  /*!< MASTER_SPLIT (Bitfield-Mask: 0x01)                    */
 #define R_TAU_TMR0_CCS_Pos             (12UL)     /*!< CCS (Bit 12)                                          */
 #define R_TAU_TMR0_CCS_Msk             (0x1000UL) /*!< CCS (Bitfield-Mask: 0x01)                             */
 #define R_TAU_TMR0_CKS_Pos             (14UL)     /*!< CKS (Bit 14)                                          */
 #define R_TAU_TMR0_CKS_Msk             (0xc000UL) /*!< CKS (Bitfield-Mask: 0x03)                             */
/* =========================================================  TSR0  ========================================================== */
 #define R_TAU_TSR0_OVF_Pos             (0UL)      /*!< OVF (Bit 0)                                           */
 #define R_TAU_TSR0_OVF_Msk             (0x1UL)    /*!< OVF (Bitfield-Mask: 0x01)                             */
/* ==========================================================  TE0  ========================================================== */
 #define R_TAU_TE0_TE_Pos               (0UL)      /*!< TE (Bit 0)                                            */
 #define R_TAU_TE0_TE_Msk               (0xffUL)   /*!< TE (Bitfield-Mask: 0xff)                              */
 #define R_TAU_TE0_TEH1_Pos             (9UL)      /*!< TEH1 (Bit 9)                                          */
 #define R_TAU_TE0_TEH1_Msk             (0x200UL)  /*!< TEH1 (Bitfield-Mask: 0x01)                            */
 #define R_TAU_TE0_TEH3_Pos             (11UL)     /*!< TEH3 (Bit 11)                                         */
 #define R_TAU_TE0_TEH3_Msk             (0x800UL)  /*!< TEH3 (Bitfield-Mask: 0x01)                            */
/* ==========================================================  TS0  ========================================================== */
 #define R_TAU_TS0_TS_Pos               (0UL)      /*!< TS (Bit 0)                                            */
 #define R_TAU_TS0_TS_Msk               (0xffUL)   /*!< TS (Bitfield-Mask: 0xff)                              */
 #define R_TAU_TS0_TSH1_Pos             (9UL)      /*!< TSH1 (Bit 9)                                          */
 #define R_TAU_TS0_TSH1_Msk             (0x200UL)  /*!< TSH1 (Bitfield-Mask: 0x01)                            */
 #define R_TAU_TS0_TSH3_Pos             (11UL)     /*!< TSH3 (Bit 11)                                         */
 #define R_TAU_TS0_TSH3_Msk             (0x800UL)  /*!< TSH3 (Bitfield-Mask: 0x01)                            */
/* ==========================================================  TT0  ========================================================== */
 #define R_TAU_TT0_TT_Pos               (0UL)      /*!< TT (Bit 0)                                            */
 #define R_TAU_TT0_TT_Msk               (0xffUL)   /*!< TT (Bitfield-Mask: 0xff)                              */
 #define R_TAU_TT0_TTH1_Pos             (9UL)      /*!< TTH1 (Bit 9)                                          */
 #define R_TAU_TT0_TTH1_Msk             (0x200UL)  /*!< TTH1 (Bitfield-Mask: 0x01)                            */
 #define R_TAU_TT0_TTH3_Pos             (11UL)     /*!< TTH3 (Bit 11)                                         */
 #define R_TAU_TT0_TTH3_Msk             (0x800UL)  /*!< TTH3 (Bitfield-Mask: 0x01)                            */
/* =========================================================  TPS0  ========================================================== */
 #define R_TAU_TPS0_PRS0_Pos            (0UL)      /*!< PRS0 (Bit 0)                                          */
 #define R_TAU_TPS0_PRS0_Msk            (0xfUL)    /*!< PRS0 (Bitfield-Mask: 0x0f)                            */
 #define R_TAU_TPS0_PRS1_Pos            (4UL)      /*!< PRS1 (Bit 4)                                          */
 #define R_TAU_TPS0_PRS1_Msk            (0xf0UL)   /*!< PRS1 (Bitfield-Mask: 0x0f)                            */
 #define R_TAU_TPS0_PRS2_Pos            (8UL)      /*!< PRS2 (Bit 8)                                          */
 #define R_TAU_TPS0_PRS2_Msk            (0x300UL)  /*!< PRS2 (Bitfield-Mask: 0x03)                            */
 #define R_TAU_TPS0_PRS3_Pos            (12UL)     /*!< PRS3 (Bit 12)                                         */
 #define R_TAU_TPS0_PRS3_Msk            (0x3000UL) /*!< PRS3 (Bitfield-Mask: 0x03)                            */
/* ==========================================================  TO0  ========================================================== */
 #define R_TAU_TO0_TO_Pos               (0UL)      /*!< TO (Bit 0)                                            */
 #define R_TAU_TO0_TO_Msk               (0xffUL)   /*!< TO (Bitfield-Mask: 0xff)                              */
/* =========================================================  TOE0  ========================================================== */
 #define R_TAU_TOE0_TOE_Pos             (0UL)      /*!< TOE (Bit 0)                                           */
 #define R_TAU_TOE0_TOE_Msk             (0xffUL)   /*!< TOE (Bitfield-Mask: 0xff)                             */
/* =========================================================  TOL0  ========================================================== */
 #define R_TAU_TOL0_TOL_Pos             (1UL)      /*!< TOL (Bit 1)                                           */
 #define R_TAU_TOL0_TOL_Msk             (0xfeUL)   /*!< TOL (Bitfield-Mask: 0x7f)                             */
/* =========================================================  TOM0  ========================================================== */
 #define R_TAU_TOM0_TOM_Pos             (1UL)      /*!< TOM (Bit 1)                                           */
 #define R_TAU_TOM0_TOM_Msk             (0xfeUL)   /*!< TOM (Bitfield-Mask: 0x7f)                             */

/* =========================================================================================================================== */
/* ================                                          R_TML32                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  ITLCMP00  ======================================================== */
/* =======================================================  ITLCMP01  ======================================================== */
/* ======================================================  ITLCMP00_L  ======================================================= */
/* ======================================================  ITLCMP01_L  ======================================================= */
/* ======================================================  ITLCMP00_H  ======================================================= */
/* ======================================================  ITLCMP01_H  ======================================================= */
/* =======================================================  ITLCAP00  ======================================================== */
/* ========================================================  ITLCTL0  ======================================================== */
 #define R_TML32_ITLCTL0_EN0_Pos        (0UL)    /*!< EN0 (Bit 0)                                           */
 #define R_TML32_ITLCTL0_EN0_Msk        (0x1UL)  /*!< EN0 (Bitfield-Mask: 0x01)                             */
 #define R_TML32_ITLCTL0_EN1_Pos        (1UL)    /*!< EN1 (Bit 1)                                           */
 #define R_TML32_ITLCTL0_EN1_Msk        (0x2UL)  /*!< EN1 (Bitfield-Mask: 0x01)                             */
 #define R_TML32_ITLCTL0_EN2_Pos        (2UL)    /*!< EN2 (Bit 2)                                           */
 #define R_TML32_ITLCTL0_EN2_Msk        (0x4UL)  /*!< EN2 (Bitfield-Mask: 0x01)                             */
 #define R_TML32_ITLCTL0_EN3_Pos        (3UL)    /*!< EN3 (Bit 3)                                           */
 #define R_TML32_ITLCTL0_EN3_Msk        (0x8UL)  /*!< EN3 (Bitfield-Mask: 0x01)                             */
 #define R_TML32_ITLCTL0_MD_Pos         (6UL)    /*!< MD (Bit 6)                                            */
 #define R_TML32_ITLCTL0_MD_Msk         (0xc0UL) /*!< MD (Bitfield-Mask: 0x03)                              */
/* =======================================================  ITLCSEL0  ======================================================== */
 #define R_TML32_ITLCSEL0_ISEL_Pos      (0UL)    /*!< ISEL (Bit 0)                                          */
 #define R_TML32_ITLCSEL0_ISEL_Msk      (0x7UL)  /*!< ISEL (Bitfield-Mask: 0x07)                            */
 #define R_TML32_ITLCSEL0_CSEL_Pos      (4UL)    /*!< CSEL (Bit 4)                                          */
 #define R_TML32_ITLCSEL0_CSEL_Msk      (0x70UL) /*!< CSEL (Bitfield-Mask: 0x07)                            */
/* =======================================================  ITLFDIV00  ======================================================= */
 #define R_TML32_ITLFDIV00_FDIV0_Pos    (0UL)    /*!< FDIV0 (Bit 0)                                         */
 #define R_TML32_ITLFDIV00_FDIV0_Msk    (0x7UL)  /*!< FDIV0 (Bitfield-Mask: 0x07)                           */
 #define R_TML32_ITLFDIV00_FDIV1_Pos    (4UL)    /*!< FDIV1 (Bit 4)                                         */
 #define R_TML32_ITLFDIV00_FDIV1_Msk    (0x70UL) /*!< FDIV1 (Bitfield-Mask: 0x07)                           */
/* =======================================================  ITLFDIV01  ======================================================= */
 #define R_TML32_ITLFDIV01_FDIV2_Pos    (0UL)    /*!< FDIV2 (Bit 0)                                         */
 #define R_TML32_ITLFDIV01_FDIV2_Msk    (0x7UL)  /*!< FDIV2 (Bitfield-Mask: 0x07)                           */
 #define R_TML32_ITLFDIV01_FDIV3_Pos    (4UL)    /*!< FDIV3 (Bit 4)                                         */
 #define R_TML32_ITLFDIV01_FDIV3_Msk    (0x70UL) /*!< FDIV3 (Bitfield-Mask: 0x07)                           */
/* ========================================================  ITLCC0  ========================================================= */
 #define R_TML32_ITLCC0_CTRS_Pos        (0UL)    /*!< CTRS (Bit 0)                                          */
 #define R_TML32_ITLCC0_CTRS_Msk        (0x3UL)  /*!< CTRS (Bitfield-Mask: 0x03)                            */
 #define R_TML32_ITLCC0_CAPCCR_Pos      (3UL)    /*!< CAPCCR (Bit 3)                                        */
 #define R_TML32_ITLCC0_CAPCCR_Msk      (0x8UL)  /*!< CAPCCR (Bitfield-Mask: 0x01)                          */
 #define R_TML32_ITLCC0_CAPR_Pos        (4UL)    /*!< CAPR (Bit 4)                                          */
 #define R_TML32_ITLCC0_CAPR_Msk        (0x10UL) /*!< CAPR (Bitfield-Mask: 0x01)                            */
 #define R_TML32_ITLCC0_CAPF_Pos        (5UL)    /*!< CAPF (Bit 5)                                          */
 #define R_TML32_ITLCC0_CAPF_Msk        (0x20UL) /*!< CAPF (Bitfield-Mask: 0x01)                            */
 #define R_TML32_ITLCC0_CAPFCR_Pos      (6UL)    /*!< CAPFCR (Bit 6)                                        */
 #define R_TML32_ITLCC0_CAPFCR_Msk      (0x40UL) /*!< CAPFCR (Bitfield-Mask: 0x01)                          */
 #define R_TML32_ITLCC0_CAPEN_Pos       (7UL)    /*!< CAPEN (Bit 7)                                         */
 #define R_TML32_ITLCC0_CAPEN_Msk       (0x80UL) /*!< CAPEN (Bitfield-Mask: 0x01)                           */
/* =========================================================  ITLS0  ========================================================= */
 #define R_TML32_ITLS0_ITF00_Pos        (0UL)    /*!< ITF00 (Bit 0)                                         */
 #define R_TML32_ITLS0_ITF00_Msk        (0x1UL)  /*!< ITF00 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLS0_ITF01_Pos        (1UL)    /*!< ITF01 (Bit 1)                                         */
 #define R_TML32_ITLS0_ITF01_Msk        (0x2UL)  /*!< ITF01 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLS0_ITF02_Pos        (2UL)    /*!< ITF02 (Bit 2)                                         */
 #define R_TML32_ITLS0_ITF02_Msk        (0x4UL)  /*!< ITF02 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLS0_ITF03_Pos        (3UL)    /*!< ITF03 (Bit 3)                                         */
 #define R_TML32_ITLS0_ITF03_Msk        (0x8UL)  /*!< ITF03 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLS0_ITF0C_Pos        (4UL)    /*!< ITF0C (Bit 4)                                         */
 #define R_TML32_ITLS0_ITF0C_Msk        (0x10UL) /*!< ITF0C (Bitfield-Mask: 0x01)                           */
/* ========================================================  ITLMKF0  ======================================================== */
 #define R_TML32_ITLMKF0_MKF00_Pos      (0UL)    /*!< MKF00 (Bit 0)                                         */
 #define R_TML32_ITLMKF0_MKF00_Msk      (0x1UL)  /*!< MKF00 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLMKF0_MKF01_Pos      (1UL)    /*!< MKF01 (Bit 1)                                         */
 #define R_TML32_ITLMKF0_MKF01_Msk      (0x2UL)  /*!< MKF01 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLMKF0_MKF02_Pos      (2UL)    /*!< MKF02 (Bit 2)                                         */
 #define R_TML32_ITLMKF0_MKF02_Msk      (0x4UL)  /*!< MKF02 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLMKF0_MKF03_Pos      (3UL)    /*!< MKF03 (Bit 3)                                         */
 #define R_TML32_ITLMKF0_MKF03_Msk      (0x8UL)  /*!< MKF03 (Bitfield-Mask: 0x01)                           */
 #define R_TML32_ITLMKF0_MKF0C_Pos      (4UL)    /*!< MKF0C (Bit 4)                                         */
 #define R_TML32_ITLMKF0_MKF0C_Msk      (0x10UL) /*!< MKF0C (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                          R_TRNG                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  TRNGSDR  ======================================================== */
 #define R_TRNG_TRNGSDR_SDATA_Pos       (0UL)    /*!< SDATA (Bit 0)                                         */
 #define R_TRNG_TRNGSDR_SDATA_Msk       (0xffUL) /*!< SDATA (Bitfield-Mask: 0xff)                           */
/* =======================================================  TRNGSCR0  ======================================================== */
 #define R_TRNG_TRNGSCR0_RDRDY_Pos      (7UL)    /*!< RDRDY (Bit 7)                                         */
 #define R_TRNG_TRNGSCR0_RDRDY_Msk      (0x80UL) /*!< RDRDY (Bitfield-Mask: 0x01)                           */
 #define R_TRNG_TRNGSCR0_SGCEN_Pos      (3UL)    /*!< SGCEN (Bit 3)                                         */
 #define R_TRNG_TRNGSCR0_SGCEN_Msk      (0x8UL)  /*!< SGCEN (Bitfield-Mask: 0x01)                           */
 #define R_TRNG_TRNGSCR0_SGSTART_Pos    (2UL)    /*!< SGSTART (Bit 2)                                       */
 #define R_TRNG_TRNGSCR0_SGSTART_Msk    (0x4UL)  /*!< SGSTART (Bitfield-Mask: 0x01)                         */
/* =======================================================  TRNGSCR1  ======================================================== */
 #define R_TRNG_TRNGSCR1_INTEN_Pos      (0UL)    /*!< INTEN (Bit 0)                                         */
 #define R_TRNG_TRNGSCR1_INTEN_Msk      (0x1UL)  /*!< INTEN (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                          R_UARTA                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  TXBA0  ========================================================= */
/* =========================================================  RXBA0  ========================================================= */
/* ========================================================  ASIMA00  ======================================================== */
 #define R_UARTA_ASIMA00_ISRMA_Pos    (0UL)    /*!< ISRMA (Bit 0)                                         */
 #define R_UARTA_ASIMA00_ISRMA_Msk    (0x1UL)  /*!< ISRMA (Bitfield-Mask: 0x01)                           */
 #define R_UARTA_ASIMA00_ISSMA_Pos    (1UL)    /*!< ISSMA (Bit 1)                                         */
 #define R_UARTA_ASIMA00_ISSMA_Msk    (0x2UL)  /*!< ISSMA (Bitfield-Mask: 0x01)                           */
 #define R_UARTA_ASIMA00_RXEA_Pos     (5UL)    /*!< RXEA (Bit 5)                                          */
 #define R_UARTA_ASIMA00_RXEA_Msk     (0x20UL) /*!< RXEA (Bitfield-Mask: 0x01)                            */
 #define R_UARTA_ASIMA00_TXEA_Pos     (6UL)    /*!< TXEA (Bit 6)                                          */
 #define R_UARTA_ASIMA00_TXEA_Msk     (0x40UL) /*!< TXEA (Bitfield-Mask: 0x01)                            */
 #define R_UARTA_ASIMA00_EN_Pos       (7UL)    /*!< EN (Bit 7)                                            */
 #define R_UARTA_ASIMA00_EN_Msk       (0x80UL) /*!< EN (Bitfield-Mask: 0x01)                              */
/* ========================================================  ASIMA01  ======================================================== */
 #define R_UARTA_ASIMA01_ALV_Pos      (0UL)    /*!< ALV (Bit 0)                                           */
 #define R_UARTA_ASIMA01_ALV_Msk      (0x1UL)  /*!< ALV (Bitfield-Mask: 0x01)                             */
 #define R_UARTA_ASIMA01_DIR_Pos      (1UL)    /*!< DIR (Bit 1)                                           */
 #define R_UARTA_ASIMA01_DIR_Msk      (0x2UL)  /*!< DIR (Bitfield-Mask: 0x01)                             */
 #define R_UARTA_ASIMA01_SL_Pos       (2UL)    /*!< SL (Bit 2)                                            */
 #define R_UARTA_ASIMA01_SL_Msk       (0x4UL)  /*!< SL (Bitfield-Mask: 0x01)                              */
 #define R_UARTA_ASIMA01_CL_Pos       (3UL)    /*!< CL (Bit 3)                                            */
 #define R_UARTA_ASIMA01_CL_Msk       (0x18UL) /*!< CL (Bitfield-Mask: 0x03)                              */
 #define R_UARTA_ASIMA01_PS_Pos       (5UL)    /*!< PS (Bit 5)                                            */
 #define R_UARTA_ASIMA01_PS_Msk       (0x60UL) /*!< PS (Bitfield-Mask: 0x03)                              */
/* ========================================================  BRGCA0  ========================================================= */
/* ========================================================  ASISA0  ========================================================= */
 #define R_UARTA_ASISA0_OVEA_Pos      (0UL)    /*!< OVEA (Bit 0)                                          */
 #define R_UARTA_ASISA0_OVEA_Msk      (0x1UL)  /*!< OVEA (Bitfield-Mask: 0x01)                            */
 #define R_UARTA_ASISA0_FEA_Pos       (1UL)    /*!< FEA (Bit 1)                                           */
 #define R_UARTA_ASISA0_FEA_Msk       (0x2UL)  /*!< FEA (Bitfield-Mask: 0x01)                             */
 #define R_UARTA_ASISA0_PEA_Pos       (2UL)    /*!< PEA (Bit 2)                                           */
 #define R_UARTA_ASISA0_PEA_Msk       (0x4UL)  /*!< PEA (Bitfield-Mask: 0x01)                             */
 #define R_UARTA_ASISA0_TXSFA_Pos     (4UL)    /*!< TXSFA (Bit 4)                                         */
 #define R_UARTA_ASISA0_TXSFA_Msk     (0x10UL) /*!< TXSFA (Bitfield-Mask: 0x01)                           */
 #define R_UARTA_ASISA0_TXBFA_Pos     (5UL)    /*!< TXBFA (Bit 5)                                         */
 #define R_UARTA_ASISA0_TXBFA_Msk     (0x20UL) /*!< TXBFA (Bitfield-Mask: 0x01)                           */
/* ========================================================  ASCTA0  ========================================================= */
 #define R_UARTA_ASCTA0_OVECTA_Pos    (0UL)    /*!< OVECTA (Bit 0)                                        */
 #define R_UARTA_ASCTA0_OVECTA_Msk    (0x1UL)  /*!< OVECTA (Bitfield-Mask: 0x01)                          */
 #define R_UARTA_ASCTA0_FECTA_Pos     (1UL)    /*!< FECTA (Bit 1)                                         */
 #define R_UARTA_ASCTA0_FECTA_Msk     (0x2UL)  /*!< FECTA (Bitfield-Mask: 0x01)                           */
 #define R_UARTA_ASCTA0_PECTA_Pos     (2UL)    /*!< PECTA (Bit 2)                                         */
 #define R_UARTA_ASCTA0_PECTA_Msk     (0x4UL)  /*!< PECTA (Bitfield-Mask: 0x01)                           */
/* ========================================================  UTA0CK  ========================================================= */
 #define R_UARTA_UTA0CK_CK_Pos        (0UL)    /*!< CK (Bit 0)                                            */
 #define R_UARTA_UTA0CK_CK_Msk        (0xfUL)  /*!< CK (Bitfield-Mask: 0x0f)                              */
 #define R_UARTA_UTA0CK_SEL_Pos       (4UL)    /*!< SEL (Bit 4)                                           */
 #define R_UARTA_UTA0CK_SEL_Msk       (0x30UL) /*!< SEL (Bitfield-Mask: 0x03)                             */

/* =========================================================================================================================== */
/* ================                                         R_PCLBUZ                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  CKS0  ========================================================== */
 #define R_PCLBUZ_CKS0_CCS_Pos      (0UL)    /*!< CCS (Bit 0)                                           */
 #define R_PCLBUZ_CKS0_CCS_Msk      (0x7UL)  /*!< CCS (Bitfield-Mask: 0x07)                             */
 #define R_PCLBUZ_CKS0_CSEL_Pos     (3UL)    /*!< CSEL (Bit 3)                                          */
 #define R_PCLBUZ_CKS0_CSEL_Msk     (0x8UL)  /*!< CSEL (Bitfield-Mask: 0x01)                            */
 #define R_PCLBUZ_CKS0_PCLOE_Pos    (7UL)    /*!< PCLOE (Bit 7)                                         */
 #define R_PCLBUZ_CKS0_PCLOE_Msk    (0x80UL) /*!< PCLOE (Bitfield-Mask: 0x01)                           */

/* =========================================================================================================================== */
/* ================                                          R_RTC_C                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  SEC  ========================================================== */
 #define R_RTC_C_SEC_SEC1_Pos          (0UL)    /*!< SEC1 (Bit 0)                                          */
 #define R_RTC_C_SEC_SEC1_Msk          (0xfUL)  /*!< SEC1 (Bitfield-Mask: 0x0f)                            */
 #define R_RTC_C_SEC_SEC10_Pos         (4UL)    /*!< SEC10 (Bit 4)                                         */
 #define R_RTC_C_SEC_SEC10_Msk         (0x70UL) /*!< SEC10 (Bitfield-Mask: 0x07)                           */
/* ==========================================================  MIN  ========================================================== */
 #define R_RTC_C_MIN_MIN1_Pos          (0UL)    /*!< MIN1 (Bit 0)                                          */
 #define R_RTC_C_MIN_MIN1_Msk          (0xfUL)  /*!< MIN1 (Bitfield-Mask: 0x0f)                            */
 #define R_RTC_C_MIN_MIN10_Pos         (4UL)    /*!< MIN10 (Bit 4)                                         */
 #define R_RTC_C_MIN_MIN10_Msk         (0x70UL) /*!< MIN10 (Bitfield-Mask: 0x07)                           */
/* =========================================================  HOUR  ========================================================== */
 #define R_RTC_C_HOUR_HOUR1_Pos        (0UL)    /*!< HOUR1 (Bit 0)                                         */
 #define R_RTC_C_HOUR_HOUR1_Msk        (0xfUL)  /*!< HOUR1 (Bitfield-Mask: 0x0f)                           */
 #define R_RTC_C_HOUR_HOUR10_Pos       (4UL)    /*!< HOUR10 (Bit 4)                                        */
 #define R_RTC_C_HOUR_HOUR10_Msk       (0x30UL) /*!< HOUR10 (Bitfield-Mask: 0x03)                          */
/* =========================================================  WEEK  ========================================================== */
 #define R_RTC_C_WEEK_WEEK_Pos         (0UL)    /*!< WEEK (Bit 0)                                          */
 #define R_RTC_C_WEEK_WEEK_Msk         (0x7UL)  /*!< WEEK (Bitfield-Mask: 0x07)                            */
/* ==========================================================  DAY  ========================================================== */
 #define R_RTC_C_DAY_DAY1_Pos          (0UL)    /*!< DAY1 (Bit 0)                                          */
 #define R_RTC_C_DAY_DAY1_Msk          (0xfUL)  /*!< DAY1 (Bitfield-Mask: 0x0f)                            */
 #define R_RTC_C_DAY_DAY10_Pos         (4UL)    /*!< DAY10 (Bit 4)                                         */
 #define R_RTC_C_DAY_DAY10_Msk         (0x30UL) /*!< DAY10 (Bitfield-Mask: 0x03)                           */
/* =========================================================  MONTH  ========================================================= */
 #define R_RTC_C_MONTH_MONTH1_Pos      (0UL)    /*!< MONTH1 (Bit 0)                                        */
 #define R_RTC_C_MONTH_MONTH1_Msk      (0xfUL)  /*!< MONTH1 (Bitfield-Mask: 0x0f)                          */
 #define R_RTC_C_MONTH_MONTH10_Pos     (4UL)    /*!< MONTH10 (Bit 4)                                       */
 #define R_RTC_C_MONTH_MONTH10_Msk     (0x10UL) /*!< MONTH10 (Bitfield-Mask: 0x01)                         */
/* =========================================================  YEAR  ========================================================== */
 #define R_RTC_C_YEAR_YEAR1_Pos        (0UL)    /*!< YEAR1 (Bit 0)                                         */
 #define R_RTC_C_YEAR_YEAR1_Msk        (0xfUL)  /*!< YEAR1 (Bitfield-Mask: 0x0f)                           */
 #define R_RTC_C_YEAR_YEAR10_Pos       (4UL)    /*!< YEAR10 (Bit 4)                                        */
 #define R_RTC_C_YEAR_YEAR10_Msk       (0xf0UL) /*!< YEAR10 (Bitfield-Mask: 0x0f)                          */
/* ========================================================  SUBCUD  ========================================================= */
 #define R_RTC_C_SUBCUD_F_Pos          (0UL)    /*!< F (Bit 0)                                             */
 #define R_RTC_C_SUBCUD_F_Msk          (0x3fUL) /*!< F (Bitfield-Mask: 0x3f)                               */
 #define R_RTC_C_SUBCUD_F6_Pos         (6UL)    /*!< F6 (Bit 6)                                            */
 #define R_RTC_C_SUBCUD_F6_Msk         (0x40UL) /*!< F6 (Bitfield-Mask: 0x01)                              */
 #define R_RTC_C_SUBCUD_DEV_Pos        (7UL)    /*!< DEV (Bit 7)                                           */
 #define R_RTC_C_SUBCUD_DEV_Msk        (0x80UL) /*!< DEV (Bitfield-Mask: 0x01)                             */
/* ========================================================  ALARMWM  ======================================================== */
 #define R_RTC_C_ALARMWM_WM1_Pos       (0UL)    /*!< WM1 (Bit 0)                                           */
 #define R_RTC_C_ALARMWM_WM1_Msk       (0xfUL)  /*!< WM1 (Bitfield-Mask: 0x0f)                             */
 #define R_RTC_C_ALARMWM_WM10_Pos      (4UL)    /*!< WM10 (Bit 4)                                          */
 #define R_RTC_C_ALARMWM_WM10_Msk      (0x70UL) /*!< WM10 (Bitfield-Mask: 0x07)                            */
/* ========================================================  ALARMWH  ======================================================== */
 #define R_RTC_C_ALARMWH_WH1_Pos       (0UL)    /*!< WH1 (Bit 0)                                           */
 #define R_RTC_C_ALARMWH_WH1_Msk       (0xfUL)  /*!< WH1 (Bitfield-Mask: 0x0f)                             */
 #define R_RTC_C_ALARMWH_WH10_Pos      (4UL)    /*!< WH10 (Bit 4)                                          */
 #define R_RTC_C_ALARMWH_WH10_Msk      (0x30UL) /*!< WH10 (Bitfield-Mask: 0x03)                            */
/* ========================================================  ALARMWW  ======================================================== */
 #define R_RTC_C_ALARMWW_WW0_Pos       (0UL)    /*!< WW0 (Bit 0)                                           */
 #define R_RTC_C_ALARMWW_WW0_Msk       (0x1UL)  /*!< WW0 (Bitfield-Mask: 0x01)                             */
 #define R_RTC_C_ALARMWW_WW1_Pos       (1UL)    /*!< WW1 (Bit 1)                                           */
 #define R_RTC_C_ALARMWW_WW1_Msk       (0x2UL)  /*!< WW1 (Bitfield-Mask: 0x01)                             */
 #define R_RTC_C_ALARMWW_WW2_Pos       (2UL)    /*!< WW2 (Bit 2)                                           */
 #define R_RTC_C_ALARMWW_WW2_Msk       (0x4UL)  /*!< WW2 (Bitfield-Mask: 0x01)                             */
 #define R_RTC_C_ALARMWW_WW3_Pos       (3UL)    /*!< WW3 (Bit 3)                                           */
 #define R_RTC_C_ALARMWW_WW3_Msk       (0x8UL)  /*!< WW3 (Bitfield-Mask: 0x01)                             */
 #define R_RTC_C_ALARMWW_WW4_Pos       (4UL)    /*!< WW4 (Bit 4)                                           */
 #define R_RTC_C_ALARMWW_WW4_Msk       (0x10UL) /*!< WW4 (Bitfield-Mask: 0x01)                             */
 #define R_RTC_C_ALARMWW_WW5_Pos       (5UL)    /*!< WW5 (Bit 5)                                           */
 #define R_RTC_C_ALARMWW_WW5_Msk       (0x20UL) /*!< WW5 (Bitfield-Mask: 0x01)                             */
 #define R_RTC_C_ALARMWW_WW6_Pos       (6UL)    /*!< WW6 (Bit 6)                                           */
 #define R_RTC_C_ALARMWW_WW6_Msk       (0x40UL) /*!< WW6 (Bitfield-Mask: 0x01)                             */
/* =========================================================  RTCC0  ========================================================= */
 #define R_RTC_C_RTCC0_CT_Pos          (0UL)    /*!< CT (Bit 0)                                            */
 #define R_RTC_C_RTCC0_CT_Msk          (0x7UL)  /*!< CT (Bitfield-Mask: 0x07)                              */
 #define R_RTC_C_RTCC0_AMPM_Pos        (3UL)    /*!< AMPM (Bit 3)                                          */
 #define R_RTC_C_RTCC0_AMPM_Msk        (0x8UL)  /*!< AMPM (Bitfield-Mask: 0x01)                            */
 #define R_RTC_C_RTCC0_RTC128EN_Pos    (4UL)    /*!< RTC128EN (Bit 4)                                      */
 #define R_RTC_C_RTCC0_RTC128EN_Msk    (0x10UL) /*!< RTC128EN (Bitfield-Mask: 0x01)                        */
 #define R_RTC_C_RTCC0_RCLOE1_Pos      (5UL)    /*!< RCLOE1 (Bit 5)                                        */
 #define R_RTC_C_RTCC0_RCLOE1_Msk      (0x20UL) /*!< RCLOE1 (Bitfield-Mask: 0x01)                          */
 #define R_RTC_C_RTCC0_RTCE_Pos        (7UL)    /*!< RTCE (Bit 7)                                          */
 #define R_RTC_C_RTCC0_RTCE_Msk        (0x80UL) /*!< RTCE (Bitfield-Mask: 0x01)                            */
/* =========================================================  RTCC1  ========================================================= */
 #define R_RTC_C_RTCC1_RWAIT_Pos       (0UL)    /*!< RWAIT (Bit 0)                                         */
 #define R_RTC_C_RTCC1_RWAIT_Msk       (0x1UL)  /*!< RWAIT (Bitfield-Mask: 0x01)                           */
 #define R_RTC_C_RTCC1_RWST_Pos        (1UL)    /*!< RWST (Bit 1)                                          */
 #define R_RTC_C_RTCC1_RWST_Msk        (0x2UL)  /*!< RWST (Bitfield-Mask: 0x01)                            */
 #define R_RTC_C_RTCC1_RIFG_Pos        (3UL)    /*!< RIFG (Bit 3)                                          */
 #define R_RTC_C_RTCC1_RIFG_Msk        (0x8UL)  /*!< RIFG (Bitfield-Mask: 0x01)                            */
 #define R_RTC_C_RTCC1_WAFG_Pos        (4UL)    /*!< WAFG (Bit 4)                                          */
 #define R_RTC_C_RTCC1_WAFG_Msk        (0x10UL) /*!< WAFG (Bitfield-Mask: 0x01)                            */
 #define R_RTC_C_RTCC1_WALIE_Pos       (6UL)    /*!< WALIE (Bit 6)                                         */
 #define R_RTC_C_RTCC1_WALIE_Msk       (0x40UL) /*!< WALIE (Bitfield-Mask: 0x01)                           */
 #define R_RTC_C_RTCC1_WALE_Pos        (7UL)    /*!< WALE (Bit 7)                                          */
 #define R_RTC_C_RTCC1_WALE_Msk        (0x80UL) /*!< WALE (Bitfield-Mask: 0x01)                            */

/** @} */ /* End of group PosMask_peripherals */

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R7FA0E107_H */

/** @} */ /* End of group R7FA0E107 */

/** @} */ /* End of group Renesas Electronics Corporation */
